#include "Base.h"

#include "SExtremoDominioReal.h"
#include "CalculoOperaciones.h"



static int TestSExdRCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SExdRCrear 01:\n" );

	SExtremoDominioReal * p_exdObj = SExdRCrear ( 5.0, 1 );
	if ( ES_NULO ( p_exdObj ) )
	{
		printf( "Error caso 1: no se esperaba nulo al crear\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SExdREsValido ( p_exdObj ) != 1 )
		{
			printf( "Error caso 2: el extremo recien creado deberia ser valido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( MatEsIgual ( SExdRValor ( p_exdObj ), 5.0 ) != 1 )
		{
			printf( "Error caso 3: el valor deberia ser 5: %f\n", SExdRValor ( p_exdObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SExdREstaIncluido ( p_exdObj ) != 1 )
		{
			printf( "Error caso 4: el extremo deberia estar incluido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SExdREsInfinito ( p_exdObj ) != 0 )
		{
			printf( "Error caso 5: un extremo finito no deberia ser infinito\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	SExdRDestruir ( &p_exdObj );

	if ( ES_VALIDO ( p_exdObj ) )
	{
		printf( "Error caso 6: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSExdRInfinito01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SExdRInfinito 01:\n" );

	SExtremoDominioReal * p_exdInf = SExdRCrearInfinito ();
	if ( ES_VALIDO ( p_exdInf ) )
	{
		if ( SExdREsInfinito ( p_exdInf ) != 1 )
		{
			printf( "Error caso 1: deberia ser infinito\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 1: no se pudo crear el extremo infinito\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SExdRDestruir ( &p_exdInf );

	SExtremoDominioReal * p_exdMenosInf = SExdRCrearMenosInfinito ();
	if ( ES_VALIDO ( p_exdMenosInf ) )
	{
		if ( SExdREsMenosInfinito ( p_exdMenosInf ) != 1 )
		{
			printf( "Error caso 2: deberia ser menos infinito\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 2: no se pudo crear el extremo menos infinito\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SExdRDestruir ( &p_exdMenosInf );
	return ( iRes );
}



int TestSExtremoDominioReal ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SExtremoDominioReal]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSExdRCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSExdRInfinito01 () == BOOL_VAL_CIERTO ) )
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
