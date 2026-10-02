#include "Base.h"

#include "SLocalizadorExt.h"


/* Primer valor que un long con signo ya no puede representar: LONG_MAX + 1.
   Vale igual con long de 4 bytes ( Windows ) que de 8 ( Cygwin, Linux ). */
#define ULONG_MITAD		( (unsigned long) LONG_MAX + 1UL )



static int TestSLczExtCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLczExtCrear 01:\n" );
	SLocalizadorExt * p_lczeObj = SLczExtCrear ( "clave" );
	if ( ES_VALIDO ( p_lczeObj ) )
	{
		if ( ES_NULO ( SLczExtClave ( p_lczeObj ) ) || ( CadComparar ( SLczExtClave ( p_lczeObj ), "clave" ) != COMP_IGUAL ) )
		{
			printf( "Error caso 1: se esperaba clave \"clave\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLczExtNumPosiciones ( p_lczeObj ) != 0 )
		{
			printf( "Error caso 2: se esperaba 0 posiciones: %d\n", SLczExtNumPosiciones ( p_lczeObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		/* Sin posiciones aun no es valido. */
		if ( SLczExtEsValido ( p_lczeObj ) != 0 )
		{
			printf( "Error caso 3: se esperaba no valido (sin posiciones)\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el objeto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLczExtDestruir ( &p_lczeObj );
	return ( iRes );
}

static int TestSLczExtPosiciones01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLczExtPosiciones 01:\n" );
	SLocalizadorExt * p_lczeObj = SLczExtCrear ( "clave" );
	if ( ES_VALIDO ( p_lczeObj ) )
	{
		if ( SLczExtInsertarPosicion ( p_lczeObj, 5 ) != 1 )
		{
			printf( "Error caso 1: se esperaba insertar posicion correcto\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLczExtNumPosiciones ( p_lczeObj ) != 1 )
		{
			printf( "Error caso 2: se esperaba 1 posicion: %d\n", SLczExtNumPosiciones ( p_lczeObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLczExtPosicionPrinc ( p_lczeObj ) != 5 )
		{
			printf( "Error caso 3: se esperaba posicion principal 5: %lu\n", SLczExtPosicionPrinc ( p_lczeObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLczExtEsValido ( p_lczeObj ) != 1 )
		{
			printf( "Error caso 4: se esperaba valido con una posicion\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLczExtInsertarPosicion ( p_lczeObj, 9 );
		if ( SLczExtNumPosiciones ( p_lczeObj ) != 2 )
		{
			printf( "Error caso 5: se esperaban 2 posiciones: %d\n", SLczExtNumPosiciones ( p_lczeObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLczExtPosicion ( p_lczeObj, 1 ) != 9 )
		{
			printf( "Error caso 6: se esperaba posicion 1 == 9: %lu\n", SLczExtPosicion ( p_lczeObj, 1 ) );
			iRes = BOOL_VAL_FALSO;
		}
		SLczExtEstablecerPosicionPrinc ( p_lczeObj, 7 );
		if ( SLczExtPosicionPrinc ( p_lczeObj ) != 7 )
		{
			printf( "Error caso 7: se esperaba posicion principal 7: %lu\n", SLczExtPosicionPrinc ( p_lczeObj ) );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el objeto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLczExtDestruir ( &p_lczeObj );
	return ( iRes );
}

static int TestSLczExtNulo01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLczExtNulo 01:\n" );
	if ( SLczExtEsValido ( NULL ) != 0 )
	{
		printf( "Error caso 1: se esperaba no valido con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SLczExtNumPosiciones ( NULL ) != 0 )
	{
		printf( "Error caso 2: se esperaban 0 posiciones con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SLczExtInsertarPosicion ( NULL, 1 ) != 0 )
	{
		printf( "Error caso 3: se esperaba fallo con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

/* La frontera del tipo, y los indices fuera de rango: la lista sin signo
   devuelve 0 fuera de rango, que es una posicion valida, asi que aqui tiene
   que salir la marca SLCZ_SIN_POSICION. */
static int TestSLczExtFrontera01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLczExtFrontera 01:\n" );
	SLocalizadorExt * p_lczeObj = SLczExtCrear ( "clave" );
	if ( ES_VALIDO ( p_lczeObj ) )
	{
		if ( SLczExtPosicionPrinc ( p_lczeObj ) != SLCZ_SIN_POSICION )
		{
			printf( "Error caso 1: sin posiciones la principal deberia ser la marca: %lu\n", SLczExtPosicionPrinc ( p_lczeObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		SLczExtInsertarPosicion ( p_lczeObj, ULONG_MITAD );
		SLczExtInsertarPosicion ( p_lczeObj, 0UL );
		if ( SLczExtPosicionPrinc ( p_lczeObj ) != ULONG_MITAD )
		{
			printf( "Error caso 2: la principal deberia ser %lu: %lu\n", ULONG_MITAD, SLczExtPosicionPrinc ( p_lczeObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		/* El 0 es una posicion como otra cualquiera. */
		if ( ( SLczExtPosicion ( p_lczeObj, 1 ) != 0UL ) || ( SLczExtEsValido ( p_lczeObj ) != 1 ) )
		{
			printf( "Error caso 3: la posicion 1 deberia ser 0 y el localizador valido: %lu\n", SLczExtPosicion ( p_lczeObj, 1 ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLczExtPosicion ( p_lczeObj, 2 ) != SLCZ_SIN_POSICION )
		{
			printf( "Error caso 4: fuera de rango se esperaba la marca: %lu\n", SLczExtPosicion ( p_lczeObj, 2 ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLczExtPosicion ( p_lczeObj, -1 ) != SLCZ_SIN_POSICION )
		{
			printf( "Error caso 5: con indice negativo se esperaba la marca: %lu\n", SLczExtPosicion ( p_lczeObj, -1 ) );
			iRes = BOOL_VAL_FALSO;
		}
		/* El duplicado conserva las dos posiciones. */
		SLocalizadorExt * p_lczeDup = SLczExtDuplicar ( p_lczeObj );
		if ( ( SLczExtNumPosiciones ( p_lczeDup ) != 2 ) ||
			 ( SLczExtPosicion ( p_lczeDup, 0 ) != ULONG_MITAD ) ||
			 ( SLczExtPosicion ( p_lczeDup, 1 ) != 0UL ) )
		{
			printf( "Error caso 6: el duplicado deberia tener { %lu, 0 }\n", ULONG_MITAD );
			iRes = BOOL_VAL_FALSO;
		}
		SLczExtDestruir ( &p_lczeDup );
		/* Con la marca entre sus posiciones deja de ser valido. */
		SLczExtInsertarPosicion ( p_lczeObj, SLCZ_SIN_POSICION );
		if ( SLczExtEsValido ( p_lczeObj ) != 0 )
		{
			printf( "Error caso 7: con una posicion a SLCZ_SIN_POSICION no deberia ser valido\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el objeto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLczExtDestruir ( &p_lczeObj );

	if ( SLczExtPosicionPrinc ( NULL ) != SLCZ_SIN_POSICION )
	{
		printf( "Error caso 8: con nulo se esperaba SLCZ_SIN_POSICION\n" );
		iRes = BOOL_VAL_FALSO;
	}
	ErrLimpiar ();
	return ( iRes );
}

/* Establecer sobre un localizador recien creado, sin posiciones: no hay
   elemento 0 que modificar, asi que la principal tiene que anadirse. Y una
   segunda vez tiene que sustituirla, no anadir otra. */
static int TestSLczExtEstablecer01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLczExtEstablecer 01:\n" );
	SLocalizadorExt * p_lczeObj = SLczExtCrear ( NULL );
	if ( ES_VALIDO ( p_lczeObj ) )
	{
		if ( SLczExtEstablecer ( p_lczeObj, "clave", 5UL ) != 1 )
		{
			printf( "Error caso 1: establecer sobre un localizador vacio deberia funcionar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLczExtNumPosiciones ( p_lczeObj ) != 1 ) || ( SLczExtPosicionPrinc ( p_lczeObj ) != 5UL ) )
		{
			printf( "Error caso 2: se esperaba una posicion, la 5: %d y %lu\n",
					SLczExtNumPosiciones ( p_lczeObj ), SLczExtPosicionPrinc ( p_lczeObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLczExtEsValido ( p_lczeObj ) != 1 )
		{
			printf( "Error caso 3: tras establecer deberia ser valido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* La segunda vez sustituye la principal. */
		if ( SLczExtEstablecer ( p_lczeObj, "otra", ULONG_MITAD ) != 1 )
		{
			printf( "Error caso 4: el segundo establecer deberia funcionar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLczExtNumPosiciones ( p_lczeObj ) != 1 ) || ( SLczExtPosicionPrinc ( p_lczeObj ) != ULONG_MITAD ) )
		{
			printf( "Error caso 5: se esperaba una posicion, la %lu: %d y %lu\n", ULONG_MITAD,
					SLczExtNumPosiciones ( p_lczeObj ), SLczExtPosicionPrinc ( p_lczeObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLczExtEsIgualLit ( p_lczeObj, "otra" ) != 1 )
		{
			printf( "Error caso 6: la clave deberia ser \"otra\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el objeto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLczExtDestruir ( &p_lczeObj );

	/* Lo mismo por EstablecerPosicionPrinc directamente. */
	p_lczeObj = SLczExtCrear ( "clave" );
	if ( ES_VALIDO ( p_lczeObj ) )
	{
		if ( ( SLczExtEstablecerPosicionPrinc ( p_lczeObj, 0UL ) != 1 ) ||
			 ( SLczExtNumPosiciones ( p_lczeObj ) != 1 ) ||
			 ( SLczExtPosicionPrinc ( p_lczeObj ) != 0UL ) )
		{
			printf( "Error caso 7: la principal 0 deberia poder fijarse sin posiciones previas\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el objeto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLczExtDestruir ( &p_lczeObj );

	if ( SLczExtEstablecer ( NULL, "clave", 5UL ) != 0 )
	{
		printf( "Error caso 8: con nulo se esperaba fallo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	ErrLimpiar ();
	return ( iRes );
}

/* Las mismas comparaciones que en SLocalizador. Un SLocalizadorExt solo es
   valido con al menos una posicion, y las comparaciones lo exigen. */
static int TestSLczExtComparar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLczExtComparar 01:\n" );
	SLocalizadorExt * p_lczeManzana = SLczExtCrear ( NULL );
	SLocalizadorExt * p_lczePera = SLczExtCrear ( NULL );
	SLocalizadorExt * p_lczeManzanaMay = SLczExtCrear ( NULL );
	SLczExtEstablecer ( p_lczeManzana, "manzana", 1UL );
	SLczExtEstablecer ( p_lczePera, "pera", 2UL );
	SLczExtEstablecer ( p_lczeManzanaMay, "Manzana", 3UL );

	if ( ( SLczExtEsMenor ( p_lczeManzana, p_lczePera ) != 1 ) ||
		 ( SLczExtEsMayor ( p_lczePera, p_lczeManzana ) != 1 ) )
	{
		printf( "Error caso 1: \"manzana\" deberia ser menor que \"pera\" y \"pera\" mayor\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ( SLczExtEsMenor ( p_lczePera, p_lczeManzana ) != 0 ) ||
		 ( SLczExtEsMayor ( p_lczeManzana, p_lczePera ) != 0 ) ||
		 ( SLczExtEsIgual ( p_lczeManzana, p_lczePera ) != 0 ) )
	{
		printf( "Error caso 2: las comparaciones inversas deberian ser falsas\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ( SLczExtEsIgual ( p_lczeManzana, p_lczeManzanaMay ) != 0 ) ||
		 ( SLczExtEsIgualExt ( p_lczeManzana, p_lczeManzanaMay, 0 ) != 1 ) ||
		 ( SLczExtEsMenorExt ( p_lczeManzanaMay, p_lczePera, 0 ) != 1 ) ||
		 ( SLczExtEsMayorExt ( p_lczePera, p_lczeManzanaMay, 0 ) != 1 ) )
	{
		printf( "Error caso 3: la distincion de mayusculas no cuadra\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ( SLczExtComparar ( p_lczeManzana, p_lczePera ) != COMP_MENOR ) ||
		 ( SLczExtComparar ( p_lczePera, p_lczeManzana ) != COMP_MAYOR ) ||
		 ( SLczExtCompararExt ( p_lczeManzana, p_lczeManzanaMay, 0 ) != COMP_IGUAL ) )
	{
		printf( "Error caso 4: Comparar deberia dar MENOR, MAYOR e IGUAL\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ( SLczExtEsMenorLit ( p_lczeManzana, "pera" ) != 1 ) ||
		 ( SLczExtEsMayorLit ( p_lczePera, "manzana" ) != 1 ) ||
		 ( SLczExtEsIgualLit ( p_lczeManzana, "manzana" ) != 1 ) ||
		 ( SLczExtCompararLit ( p_lczeManzana, "manzana" ) != COMP_IGUAL ) ||
		 ( SLczExtEsIgualLitExt ( p_lczeManzana, "MANZANA", 0 ) != 1 ) ||
		 ( SLczExtCompararLitExt ( p_lczeManzana, "MANZANA", 0 ) != COMP_IGUAL ) )
	{
		printf( "Error caso 5: las comparaciones con literal no cuadran\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ( SLczExtEsIgual ( NULL, NULL ) != 1 ) ||
		 ( SLczExtEsMenor ( NULL, p_lczeManzana ) != 1 ) ||
		 ( SLczExtEsMayor ( p_lczeManzana, NULL ) != 1 ) ||
		 ( SLczExtComparar ( NULL, p_lczeManzana ) != COMP_MENOR ) ||
		 ( SLczExtComparar ( p_lczeManzana, NULL ) != COMP_MAYOR ) ||
		 ( SLczExtComparar ( NULL, NULL ) != COMP_IGUAL ) )
	{
		printf( "Error caso 6: las comparaciones con nulo no cuadran\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* Se compara por clave: sin posiciones tambien compara. */
	SLocalizadorExt * p_lczeSinPos = SLczExtCrear ( "pera" );
	if ( ( SLczExtEsValido ( p_lczeSinPos ) != 0 ) ||
		 ( SLczExtEsIgualLit ( p_lczeSinPos, "pera" ) != 1 ) ||
		 ( SLczExtEsIgual ( p_lczeSinPos, p_lczePera ) != 1 ) ||
		 ( SLczExtComparar ( p_lczeManzana, p_lczeSinPos ) != COMP_MENOR ) )
	{
		printf( "Error caso 7: sin posiciones deberia compararse por la clave\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLczExtDestruir ( &p_lczeSinPos );
	SLczExtDestruir ( &p_lczeManzana );
	SLczExtDestruir ( &p_lczePera );
	SLczExtDestruir ( &p_lczeManzanaMay );
	return ( iRes );
}

int TestSLocalizadorExt ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SLocalizadorExt]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSLczExtCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSLczExtPosiciones01 () == BOOL_VAL_CIERTO ) &&
			( TestSLczExtNulo01 () == BOOL_VAL_CIERTO ) &&
			( TestSLczExtFrontera01 () == BOOL_VAL_CIERTO ) &&
			( TestSLczExtEstablecer01 () == BOOL_VAL_CIERTO ) &&
			( TestSLczExtComparar01 () == BOOL_VAL_CIERTO ) )
	{
		printf ( "%sResultado: OK%s\n", ANSI_VERDE, ANSI_RESETEAR );
	}
	else
	{
		printf ( "%sResultado: KO%s\n", ANSI_ROJO, ANSI_RESETEAR );
		iRes = BOOL_VAL_FALSO;
	}
	printf ( "%s[Fin]%s\n", ANSI_AMARILLO, ANSI_RESETEAR );
	return ( iRes );
}
