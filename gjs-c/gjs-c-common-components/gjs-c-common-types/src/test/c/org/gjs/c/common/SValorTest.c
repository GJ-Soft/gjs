#include "Base.h"

#include "SValor.h"



static int TestSValEntero01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SValEntero 01:\n" );
	SValor * p_valObj = SValCrearEntero ( 42 );
	if ( ES_VALIDO ( p_valObj ) )
	{
		if ( SValValorEntero ( p_valObj ) != 42 )
		{
			printf( "Error caso 1: se esperaba 42: %ld\n", SValValorEntero ( p_valObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SValTipo ( p_valObj ) != TIP_NUMERO_ENTERO )
		{
			printf( "Error caso 2: se esperaba tipo entero: %d\n", SValTipo ( p_valObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SValEsEntero ( p_valObj ) != 1 )
		{
			printf( "Error caso 3: se esperaba es entero\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SValEsValido ( p_valObj ) != 1 )
		{
			printf( "Error caso 4: se esperaba valido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SValEsIgualValorEntero ( p_valObj, 42 ) != 1 )
		{
			printf( "Error caso 5: se esperaba igual a 42\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SValEstablecerValorEntero ( p_valObj, -7 );
		if ( SValValorEntero ( p_valObj ) != -7 )
		{
			printf( "Error caso 6: se esperaba -7 tras establecer: %ld\n", SValValorEntero ( p_valObj ) );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el objeto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SValDestruir ( &p_valObj );
	return ( iRes );
}

static int TestSValLiteral01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SValLiteral 01:\n" );
	SValor * p_valObj = SValCrearLiteral ( "hola" );
	if ( ES_VALIDO ( p_valObj ) )
	{
		if ( SValEsCadena ( p_valObj ) != 1 )
		{
			printf( "Error caso 1: se esperaba es cadena\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_NULO ( SValValorLiteral ( p_valObj ) ) || ( CadComparar ( SValValorLiteral ( p_valObj ), "hola" ) != COMP_IGUAL ) )
		{
			printf( "Error caso 2: se esperaba valor \"hola\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SValTieneValor ( p_valObj ) != 1 )
		{
			printf( "Error caso 3: se esperaba que tiene valor\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el objeto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SValDestruir ( &p_valObj );
	return ( iRes );
}

static int TestSValDuplicar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SValDuplicar 01:\n" );
	SValor * p_valObj = SValCrearEntero ( 100 );
	if ( ES_VALIDO ( p_valObj ) )
	{
		SValor * p_valDup = SValDuplicar ( p_valObj );
		if ( ES_VALIDO ( p_valDup ) )
		{
			if ( SValEsIgual ( p_valObj, p_valDup ) != 1 )
			{
				printf( "Error caso 1: se esperaba duplicado igual\n" );
				iRes = BOOL_VAL_FALSO;
			}
			if ( SValValorEntero ( p_valDup ) != 100 )
			{
				printf( "Error caso 2: se esperaba 100 en el duplicado: %ld\n", SValValorEntero ( p_valDup ) );
				iRes = BOOL_VAL_FALSO;
			}
		}
		else
		{
			printf( "Error caso 1: no se pudo duplicar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SValDestruir ( &p_valDup );
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el objeto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SValDestruir ( &p_valObj );
	return ( iRes );
}

static int TestSValNulo01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SValNulo 01:\n" );
	if ( SValEsValido ( NULL ) != 0 )
	{
		printf( "Error caso 1: se esperaba no valido con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SValTipo ( NULL ) != 0 )
	{
		printf( "Error caso 2: se esperaba tipo 0 con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SValValorEntero ( NULL ) != 0 )
	{
		printf( "Error caso 3: se esperaba valor 0 con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

/* SValPtr envuelve el objeto en un SPtr con SValDestruir como destructor: al
   destruir el SPtr se libera tambien el SValor. Con MODO_DEPURACION se comprueba
   que no queda memoria reservada. */
static int TestSValPtr01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SValPtr 01:\n" );
# if ( defined ( MODO_DEPURACION ) )
	unsigned long ulBloquesAntes = MemNumBloquesActuales ();
# endif
	SValor * p_valObj = SValCrearEntero ( 42 );
	SPtr * p_ptrObj = SValPtr ( p_valObj );
	if ( ES_NULO ( p_ptrObj ) )
	{
		printf( "Error caso 1: no se esperaba nulo al crear el SPtr\n" );
		iRes = BOOL_VAL_FALSO;
		SValDestruir ( &p_valObj );
	}
	else
	{
		if ( SPtrEsValido ( p_ptrObj ) != 1 )
		{
			printf( "Error caso 2: el SPtr deberia ser valido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SPtrObjeto ( p_ptrObj ) != p_valObj )
		{
			printf( "Error caso 3: el SPtr deberia envolver el mismo SValor\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* El SValor pasa a ser del SPtr: se libera con el, no por separado. */
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

/* Con objeto nulo, SValPtr da un SPtr vacio: hay que destruirlo igualmente.
   Con MODO_DEPURACION se comprueba que no queda memoria reservada. */
static int TestSValPtrNulo01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SValPtrNulo 01:\n" );
# if ( defined ( MODO_DEPURACION ) )
	unsigned long ulBloquesAntes = MemNumBloquesActuales ();
# endif
	SPtr * p_ptrObj = SValPtr ( NULL );
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



int TestSValor ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SValor]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSValEntero01 () == BOOL_VAL_CIERTO ) &&
			( TestSValLiteral01 () == BOOL_VAL_CIERTO ) &&
			( TestSValDuplicar01 () == BOOL_VAL_CIERTO ) &&
			( TestSValNulo01 () == BOOL_VAL_CIERTO ) &&
			( TestSValPtr01 () == BOOL_VAL_CIERTO ) &&
			( TestSValPtrNulo01 () == BOOL_VAL_CIERTO ) )
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
