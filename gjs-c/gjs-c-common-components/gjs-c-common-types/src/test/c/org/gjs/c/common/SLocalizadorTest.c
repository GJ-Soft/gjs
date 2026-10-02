#include "Base.h"

#include "SLocalizador.h"


/* Primer valor que un long con signo ya no puede representar: LONG_MAX + 1.
   Vale igual con long de 4 bytes ( Windows ) que de 8 ( Cygwin, Linux ). */
#define ULONG_MITAD		( (unsigned long) LONG_MAX + 1UL )



static int TestSLczCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLczCrear 01:\n" );
	SLocalizador * p_lczObj = SLczCrear ( "clave" );
	if ( ES_VALIDO ( p_lczObj ) )
	{
		if ( ES_NULO ( SLczClave ( p_lczObj ) ) || ( CadComparar ( SLczClave ( p_lczObj ), "clave" ) != COMP_IGUAL ) )
		{
			printf( "Error caso 1: se esperaba clave \"clave\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Recien creado no tiene posicion, por lo que aun no es valido. */
		if ( SLczEsValido ( p_lczObj ) != 0 )
		{
			printf( "Error caso 2: se esperaba no valido (sin posicion)\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el objeto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLczDestruir ( &p_lczObj );
	return ( iRes );
}

static int TestSLczEstablecer01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLczEstablecer 01:\n" );
	SLocalizador * p_lczObj = SLczCrear ( NULL );
	if ( ES_VALIDO ( p_lczObj ) )
	{
		if ( SLczEstablecer ( p_lczObj, "manzana", 7 ) != 1 )
		{
			printf( "Error caso 1: se esperaba establecer correcto\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLczPosicion ( p_lczObj ) != 7 )
		{
			printf( "Error caso 2: se esperaba posicion 7: %lu\n", SLczPosicion ( p_lczObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLczEsValido ( p_lczObj ) != 1 )
		{
			printf( "Error caso 3: se esperaba valido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLczEstablecerPosicion ( p_lczObj, 12 ) != 1 )
		{
			printf( "Error caso 4: se esperaba establecer posicion correcto\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLczPosicion ( p_lczObj ) != 12 )
		{
			printf( "Error caso 5: se esperaba posicion 12: %lu\n", SLczPosicion ( p_lczObj ) );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el objeto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLczDestruir ( &p_lczObj );
	return ( iRes );
}

static int TestSLczComparar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLczComparar 01:\n" );
	SLocalizador * p_lczObj = SLczCrear ( NULL );
	if ( ES_VALIDO ( p_lczObj ) )
	{
		SLczEstablecer ( p_lczObj, "manzana", 3 );
		if ( SLczEsIgualLit ( p_lczObj, "manzana" ) != 1 )
		{
			printf( "Error caso 1: se esperaba igual a \"manzana\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLczEsMenorLit ( p_lczObj, "pera" ) != 1 )
		{
			printf( "Error caso 2: se esperaba menor que \"pera\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLczEsMayorLit ( p_lczObj, "limon" ) != 1 )
		{
			printf( "Error caso 3: se esperaba mayor que \"limon\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el objeto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLczDestruir ( &p_lczObj );
	return ( iRes );
}

static int TestSLczDuplicar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLczDuplicar 01:\n" );
	SLocalizador * p_lczObj = SLczCrear ( NULL );
	if ( ES_VALIDO ( p_lczObj ) )
	{
		SLczEstablecer ( p_lczObj, "clave", 4 );
		SLocalizador * p_lczDup = SLczDuplicar ( p_lczObj );
		if ( ES_VALIDO ( p_lczDup ) )
		{
			if ( SLczEsIgualLit ( p_lczDup, "clave" ) != 1 )
			{
				printf( "Error caso 1: el duplicado no conserva la clave\n" );
				iRes = BOOL_VAL_FALSO;
			}
			if ( SLczPosicion ( p_lczDup ) != 4 )
			{
				printf( "Error caso 2: el duplicado no conserva la posicion: %lu\n", SLczPosicion ( p_lczDup ) );
				iRes = BOOL_VAL_FALSO;
			}
		}
		else
		{
			printf( "Error caso 1: no se pudo duplicar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLczDestruir ( &p_lczDup );
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el objeto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLczDestruir ( &p_lczObj );
	return ( iRes );
}

static int TestSLczNulo01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLczNulo 01:\n" );
	if ( SLczEsValido ( NULL ) != 0 )
	{
		printf( "Error caso 1: se esperaba no valido con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SLczEstablecer ( NULL, "clave", 1 ) != 0 )
	{
		printf( "Error caso 2: se esperaba fallo con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( SLczClave ( NULL ) ) )
	{
		printf( "Error caso 3: se esperaba clave nula con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

/* La frontera del tipo: posiciones que no caben en un long con signo, y la
   marca SLCZ_SIN_POSICION. */
static int TestSLczFrontera01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLczFrontera 01:\n" );
	SLocalizador * p_lczObj = SLczCrear ( "clave" );
	if ( ES_VALIDO ( p_lczObj ) )
	{
		if ( SLczPosicion ( p_lczObj ) != SLCZ_SIN_POSICION )
		{
			printf( "Error caso 1: recien creado deberia no tener posicion: %lu\n", SLczPosicion ( p_lczObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		/* LONG_MAX + 1 era negativo con la posicion en long. */
		SLczEstablecerPosicion ( p_lczObj, ULONG_MITAD );
		if ( ( SLczPosicion ( p_lczObj ) != ULONG_MITAD ) || ( SLczEsValido ( p_lczObj ) != 1 ) )
		{
			printf( "Error caso 2: LONG_MAX + 1 deberia ser una posicion valida: %lu\n", SLczPosicion ( p_lczObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		/* La ultima posicion guardable es la anterior a la marca. */
		SLczEstablecerPosicion ( p_lczObj, ULONG_MAX - 1UL );
		if ( SLczEsValido ( p_lczObj ) != 1 )
		{
			printf( "Error caso 3: ULONG_MAX - 1 deberia ser una posicion valida\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLczEstablecerPosicion ( p_lczObj, SLCZ_SIN_POSICION );
		if ( SLczEsValido ( p_lczObj ) != 0 )
		{
			printf( "Error caso 4: con la marca SLCZ_SIN_POSICION no deberia ser valido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* El duplicado conserva la posicion grande. */
		SLczEstablecerPosicion ( p_lczObj, ULONG_MITAD );
		SLocalizador * p_lczDup = SLczDuplicar ( p_lczObj );
		if ( SLczPosicion ( p_lczDup ) != ULONG_MITAD )
		{
			printf( "Error caso 5: el duplicado deberia tener posicion %lu: %lu\n", ULONG_MITAD, SLczPosicion ( p_lczDup ) );
			iRes = BOOL_VAL_FALSO;
		}
		SLczDestruir ( &p_lczDup );
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el objeto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLczDestruir ( &p_lczObj );

	if ( SLczPosicion ( NULL ) != SLCZ_SIN_POSICION )
	{
		printf( "Error caso 6: con nulo se esperaba SLCZ_SIN_POSICION\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSLczCrearExt01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLczCrearExt 01:\n" );
	SLocalizador * p_lczObj = SLczCrearExt ( "clave", 7UL );
	if ( ES_VALIDO ( p_lczObj ) )
	{
		if ( ( SLczEsValido ( p_lczObj ) != 1 ) || ( SLczPosicion ( p_lczObj ) != 7UL ) ||
			 ( SLczEsIgualLit ( p_lczObj, "clave" ) != 1 ) )
		{
			printf( "Error caso 1: se esperaba valido, con clave \"clave\" y posicion 7: %lu\n", SLczPosicion ( p_lczObj ) );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el objeto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLczDestruir ( &p_lczObj );

	/* Sin clave se crea, pero no es valido. */
	p_lczObj = SLczCrearExt ( NULL, 7UL );
	if ( ES_NULO ( p_lczObj ) || ( SLczEsValido ( p_lczObj ) != 0 ) )
	{
		printf( "Error caso 2: sin clave deberia crearse y no ser valido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLczDestruir ( &p_lczObj );

	/* Con la marca de sin posicion tampoco es valido. */
	p_lczObj = SLczCrearExt ( "clave", SLCZ_SIN_POSICION );
	if ( ES_NULO ( p_lczObj ) || ( SLczEsValido ( p_lczObj ) != 0 ) )
	{
		printf( "Error caso 3: con SLCZ_SIN_POSICION no deberia ser valido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLczDestruir ( &p_lczObj );

	/* Una clave que no es un token valido no se acepta. */
	p_lczObj = SLczCrearExt ( "", 7UL );
	if ( ES_VALIDO ( p_lczObj ) )
	{
		printf( "Error caso 4: con clave vacia no deberia crearse\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLczDestruir ( &p_lczObj );
	return ( iRes );
}

/* Comparaciones entre localizadores. EsMenor y EsMayor llamaban a la de
   igualdad, asi que "manzana" < "pera" salia falso: los casos 1 a 4 lo
   cazan. Por defecto se distinguen mayusculas; las Ext con 0 no. */
static int TestSLczComparar02 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLczComparar 02:\n" );
	SLocalizador * p_lczManzana = SLczCrearExt ( "manzana", 1UL );
	SLocalizador * p_lczPera = SLczCrearExt ( "pera", 2UL );
	SLocalizador * p_lczManzanaMay = SLczCrearExt ( "Manzana", 3UL );
	SLocalizador * p_lczOtraManzana = SLczCrearExt ( "manzana", 9UL );

	if ( SLczEsMenor ( p_lczManzana, p_lczPera ) != 1 )
	{
		printf( "Error caso 1: \"manzana\" deberia ser menor que \"pera\"\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SLczEsMayor ( p_lczPera, p_lczManzana ) != 1 )
	{
		printf( "Error caso 2: \"pera\" deberia ser mayor que \"manzana\"\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ( SLczEsMenor ( p_lczPera, p_lczManzana ) != 0 ) || ( SLczEsMayor ( p_lczManzana, p_lczPera ) != 0 ) )
	{
		printf( "Error caso 3: las comparaciones inversas deberian ser falsas\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ( SLczEsMenor ( p_lczManzana, p_lczOtraManzana ) != 0 ) || ( SLczEsMayor ( p_lczManzana, p_lczOtraManzana ) != 0 ) )
	{
		printf( "Error caso 4: con la misma clave no deberia ser ni menor ni mayor\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* La igualdad es por clave: la posicion no cuenta. */
	if ( SLczEsIgual ( p_lczManzana, p_lczOtraManzana ) != 1 )
	{
		printf( "Error caso 5: misma clave con distinta posicion deberia ser igual\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SLczEsIgual ( p_lczManzana, p_lczManzanaMay ) != 0 )
	{
		printf( "Error caso 6: por defecto \"manzana\" y \"Manzana\" son distintas\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ( SLczEsIgualExt ( p_lczManzana, p_lczManzanaMay, 0 ) != 1 ) ||
		 ( SLczEsMenorExt ( p_lczManzanaMay, p_lczPera, 0 ) != 1 ) ||
		 ( SLczEsMayorExt ( p_lczPera, p_lczManzanaMay, 0 ) != 1 ) )
	{
		printf( "Error caso 7: sin distinguir mayusculas \"Manzana\" es igual a \"manzana\" y menor que \"pera\"\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ( SLczComparar ( p_lczManzana, p_lczPera ) != COMP_MENOR ) ||
		 ( SLczComparar ( p_lczPera, p_lczManzana ) != COMP_MAYOR ) ||
		 ( SLczComparar ( p_lczManzana, p_lczOtraManzana ) != COMP_IGUAL ) )
	{
		printf( "Error caso 8: Comparar deberia dar MENOR, MAYOR e IGUAL\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ( SLczCompararExt ( p_lczManzana, p_lczManzanaMay, 0 ) != COMP_IGUAL ) ||
		 ( SLczCompararExt ( p_lczManzana, p_lczManzanaMay, 1 ) == COMP_IGUAL ) )
	{
		printf( "Error caso 9: CompararExt deberia distinguir mayusculas solo con 1\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* Con literal. */
	if ( ( SLczEsMenorLit ( p_lczManzana, "pera" ) != 1 ) ||
		 ( SLczEsMayorLit ( p_lczPera, "manzana" ) != 1 ) ||
		 ( SLczCompararLit ( p_lczManzana, "manzana" ) != COMP_IGUAL ) ||
		 ( SLczEsIgualLitExt ( p_lczManzana, "MANZANA", 0 ) != 1 ) ||
		 ( SLczCompararLitExt ( p_lczManzana, "MANZANA", 0 ) != COMP_IGUAL ) )
	{
		printf( "Error caso 10: las comparaciones con literal no cuadran\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* El nulo va delante de cualquier localizador, y dos nulos son iguales. */
	if ( ( SLczEsIgual ( NULL, NULL ) != 1 ) ||
		 ( SLczEsMenor ( NULL, p_lczManzana ) != 1 ) ||
		 ( SLczEsMayor ( p_lczManzana, NULL ) != 1 ) ||
		 ( SLczEsIgual ( p_lczManzana, NULL ) != 0 ) )
	{
		printf( "Error caso 11: las comparaciones con nulo no cuadran\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ( SLczComparar ( NULL, NULL ) != COMP_IGUAL ) ||
		 ( SLczComparar ( NULL, p_lczManzana ) != COMP_MENOR ) ||
		 ( SLczComparar ( p_lczManzana, NULL ) != COMP_MAYOR ) ||
		 ( SLczCompararLit ( p_lczManzana, NULL ) != COMP_MAYOR ) )
	{
		printf( "Error caso 12: Comparar con nulo deberia ordenar el nulo delante\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* Se compara por clave: un localizador sin posicion tambien compara. */
	SLocalizador * p_lczSinPos = SLczCrear ( "pera" );
	if ( ( SLczEsValido ( p_lczSinPos ) != 0 ) ||
		 ( SLczEsIgualLit ( p_lczSinPos, "pera" ) != 1 ) ||
		 ( SLczEsIgual ( p_lczSinPos, p_lczPera ) != 1 ) ||
		 ( SLczEsMayor ( p_lczSinPos, p_lczManzana ) != 1 ) ||
		 ( SLczComparar ( p_lczManzana, p_lczSinPos ) != COMP_MENOR ) )
	{
		printf( "Error caso 13: sin posicion deberia compararse por la clave\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* Sin clave no es comparable: Comparar lo ordena delante, como al nulo. */
	SLocalizador * p_lczSinClave = SLczCrearExt ( NULL, 4UL );
	if ( ( SLczEsIgualLit ( p_lczSinClave, "pera" ) != 0 ) ||
		 ( SLczComparar ( p_lczSinClave, p_lczPera ) != COMP_MENOR ) ||
		 ( SLczComparar ( p_lczPera, p_lczSinClave ) != COMP_MAYOR ) )
	{
		printf( "Error caso 14: sin clave deberia ordenarse delante\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLczDestruir ( &p_lczSinPos );
	SLczDestruir ( &p_lczSinClave );
	SLczDestruir ( &p_lczManzana );
	SLczDestruir ( &p_lczPera );
	SLczDestruir ( &p_lczManzanaMay );
	SLczDestruir ( &p_lczOtraManzana );
	return ( iRes );
}

int TestSLocalizador ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SLocalizador]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSLczCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSLczEstablecer01 () == BOOL_VAL_CIERTO ) &&
			( TestSLczComparar01 () == BOOL_VAL_CIERTO ) &&
			( TestSLczDuplicar01 () == BOOL_VAL_CIERTO ) &&
			( TestSLczNulo01 () == BOOL_VAL_CIERTO ) &&
			( TestSLczFrontera01 () == BOOL_VAL_CIERTO ) &&
			( TestSLczCrearExt01 () == BOOL_VAL_CIERTO ) &&
			( TestSLczComparar02 () == BOOL_VAL_CIERTO ) )
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
