#include "Base.h"

#include "SEntrada.h"



static int TestSEtrCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SEtrCrear 01:\n" );
	SEntrada * p_etrObj = SEtrCrearExt ( "entrada", "una definicion" );
	if ( ES_VALIDO ( p_etrObj ) )
	{
		if ( ES_NULO ( SEtrNombre ( p_etrObj ) ) || ( CadComparar ( SEtrNombre ( p_etrObj ), "entrada" ) != COMP_IGUAL ) )
		{
			printf( "Error caso 1: se esperaba nombre \"entrada\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_NULO ( SEtrDefinicion ( p_etrObj ) ) || ( CadComparar ( SEtrDefinicion ( p_etrObj ), "una definicion" ) != COMP_IGUAL ) )
		{
			printf( "Error caso 2: se esperaba definicion \"una definicion\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEtrEsValido ( p_etrObj ) != 1 )
		{
			printf( "Error caso 3: se esperaba valido\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el objeto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SEtrDestruir ( &p_etrObj );
	return ( iRes );
}

static int TestSEtrEstablecer01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SEtrEstablecer 01:\n" );
	SEntrada * p_etrObj = SEtrCrearDef ();
	if ( ES_VALIDO ( p_etrObj ) )
	{
		if ( SEtrEstablecer ( p_etrObj, "clave", "valor" ) != 1 )
		{
			printf( "Error caso 1: se esperaba establecer correcto\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( CadComparar ( SEtrNombre ( p_etrObj ), "clave" ) != COMP_IGUAL )
		{
			printf( "Error caso 2: se esperaba nombre \"clave\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEtrEstablecerDefinicion ( p_etrObj, "otro valor" ) != 1 )
		{
			printf( "Error caso 3: se esperaba establecer definicion correcto\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( CadComparar ( SEtrDefinicion ( p_etrObj ), "otro valor" ) != COMP_IGUAL )
		{
			printf( "Error caso 4: se esperaba definicion \"otro valor\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el objeto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SEtrDestruir ( &p_etrObj );
	return ( iRes );
}

static int TestSEtrComparar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SEtrComparar 01:\n" );
	SEntrada * p_etrObj = SEtrCrearExt ( "manzana", "fruta" );
	if ( ES_VALIDO ( p_etrObj ) )
	{
		if ( SEtrEsIgualLit ( p_etrObj, "manzana" ) != 1 )
		{
			printf( "Error caso 1: se esperaba igual a \"manzana\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEtrEsMenorLit ( p_etrObj, "pera" ) != 1 )
		{
			printf( "Error caso 2: se esperaba menor que \"pera\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEtrEsMayorLit ( p_etrObj, "limon" ) != 1 )
		{
			printf( "Error caso 3: se esperaba mayor que \"limon\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SEntrada * p_etrDup = SEtrDuplicar ( p_etrObj );
		if ( ES_VALIDO ( p_etrDup ) )
		{
			if ( SEtrEsIgual ( p_etrObj, p_etrDup ) != 1 )
			{
				printf( "Error caso 4: se esperaba duplicado igual\n" );
				iRes = BOOL_VAL_FALSO;
			}
		}
		else
		{
			printf( "Error caso 4: no se pudo duplicar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SEtrDestruir ( &p_etrDup );
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el objeto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SEtrDestruir ( &p_etrObj );
	return ( iRes );
}

static int TestSEtrNulo01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SEtrNulo 01:\n" );
	if ( SEtrEsValido ( NULL ) != 0 )
	{
		printf( "Error caso 1: se esperaba no valido con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( SEtrNombre ( NULL ) ) )
	{
		printf( "Error caso 2: se esperaba nombre nulo con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SEtrEstablecer ( NULL, "a", "b" ) != 0 )
	{
		printf( "Error caso 3: se esperaba fallo con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

/* SEtrPtr envuelve el objeto en un SPtr con SEtrDestruir como destructor: al
   destruir el SPtr se libera tambien el SEntrada. Con MODO_DEPURACION se comprueba
   que no queda memoria reservada. */
static int TestSEtrPtr01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SEtrPtr 01:\n" );
# if ( defined ( MODO_DEPURACION ) )
	unsigned long ulBloquesAntes = MemNumBloquesActuales ();
# endif
	SEntrada * p_etrObj = SEtrCrearExt ( "entrada", "una definicion" );
	SPtr * p_ptrObj = SEtrPtr ( p_etrObj );
	if ( ES_NULO ( p_ptrObj ) )
	{
		printf( "Error caso 1: no se esperaba nulo al crear el SPtr\n" );
		iRes = BOOL_VAL_FALSO;
		SEtrDestruir ( &p_etrObj );
	}
	else
	{
		if ( SPtrEsValido ( p_ptrObj ) != 1 )
		{
			printf( "Error caso 2: el SPtr deberia ser valido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SPtrObjeto ( p_ptrObj ) != p_etrObj )
		{
			printf( "Error caso 3: el SPtr deberia envolver el mismo SEntrada\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* El SEntrada pasa a ser del SPtr: se libera con el, no por separado. */
		SPtrDestruir ( &p_ptrObj );
		if ( ES_VALIDO ( p_ptrObj ) )
		{
			printf( "Error caso 4: se esperaba puntero nulo tras destruir\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
# if ( defined ( MODO_DEPURACION ) )
	if ( MemNumBloquesActuales () != ulBloquesAntes )
	{
		printf( "Error caso 5: quedan %ld bloques sin liberar\n", (long) ( MemNumBloquesActuales () - ulBloquesAntes ) );
		iRes = BOOL_VAL_FALSO;
	}
# endif
	return ( iRes );
}

/* Con objeto nulo, SEtrPtr da un SPtr vacio: hay que destruirlo igualmente.
   Con MODO_DEPURACION se comprueba que no queda memoria reservada. */
static int TestSEtrPtrNulo01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SEtrPtrNulo 01:\n" );
# if ( defined ( MODO_DEPURACION ) )
	unsigned long ulBloquesAntes = MemNumBloquesActuales ();
# endif
	SPtr * p_ptrObj = SEtrPtr ( NULL );
	if ( ES_NULO ( p_ptrObj ) )
	{
		printf( "Error caso 1: con objeto nulo se esperaba un SPtr vacio, no nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SPtrEstaVacio ( p_ptrObj ) != 1 )
		{
			printf( "Error caso 2: con objeto nulo el SPtr deberia estar vacio\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SPtrDestruir ( &p_ptrObj );
	}
# if ( defined ( MODO_DEPURACION ) )
	if ( MemNumBloquesActuales () != ulBloquesAntes )
	{
		printf( "Error caso 3: quedan %ld bloques sin liberar\n", (long) ( MemNumBloquesActuales () - ulBloquesAntes ) );
		iRes = BOOL_VAL_FALSO;
	}
# endif
	ErrLimpiar ();
	return ( iRes );
}



int TestSEntrada ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SEntrada]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSEtrCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSEtrEstablecer01 () == BOOL_VAL_CIERTO ) &&
			( TestSEtrComparar01 () == BOOL_VAL_CIERTO ) &&
			( TestSEtrNulo01 () == BOOL_VAL_CIERTO ) &&
			( TestSEtrPtr01 () == BOOL_VAL_CIERTO ) &&
			( TestSEtrPtrNulo01 () == BOOL_VAL_CIERTO ) )
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
