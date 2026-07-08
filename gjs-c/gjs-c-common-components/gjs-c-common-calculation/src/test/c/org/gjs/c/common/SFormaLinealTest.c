#include "Base.h"

#include "SFormaLineal.h"
#include "CalculoOperaciones.h"



static int TestSFrmLinCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SFrmLinCrear 01:\n" );

	SFormaLineal * p_frmObj = SFrmLinCrear2 ( 2.0, 3.0 );
	if ( ES_NULO ( p_frmObj ) )
	{
		printf( "Error caso 1: no se esperaba nulo al crear\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SFrmLinEsValido ( p_frmObj ) != 1 )
		{
			printf( "Error caso 2: la forma lineal recien creada deberia ser valida\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SFrmLinNumVariables ( p_frmObj ) != 2 )
		{
			printf( "Error caso 3: deberia tener 2 variables: %d\n", SFrmLinNumVariables ( p_frmObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( MatEsIgual ( SFrmLinCoeficiente1 ( p_frmObj ), 2.0 ) != 1 )
		{
			printf( "Error caso 4: el primer coeficiente deberia ser 2: %f\n", SFrmLinCoeficiente1 ( p_frmObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( MatEsIgual ( SFrmLinCoeficiente2 ( p_frmObj ), 3.0 ) != 1 )
		{
			printf( "Error caso 5: el segundo coeficiente deberia ser 3: %f\n", SFrmLinCoeficiente2 ( p_frmObj ) );
			iRes = BOOL_VAL_FALSO;
		}
	}
	SFrmLinDestruir ( &p_frmObj );

	if ( ES_VALIDO ( p_frmObj ) )
	{
		printf( "Error caso 6: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSFrmLinEvaluar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SFrmLinEvaluar 01:\n" );

	SFormaLineal * p_frmObj = SFrmLinCrear2 ( 2.0, 3.0 );
	if ( ES_VALIDO ( p_frmObj ) )
	{
		/* 2*x1 + 3*x2 con ( 2, 3 ) = 4 + 9 = 13. */
		double dVals [ 2 ] = { 2.0, 3.0 };
		if ( MatEsIgual ( SFrmLinEvaluar ( p_frmObj, dVals ), 13.0 ) != 1 )
		{
			printf( "Error caso 1: la evaluacion deberia ser 13: %f\n", SFrmLinEvaluar ( p_frmObj, dVals ) );
			iRes = BOOL_VAL_FALSO;
		}
		/* 2*1 + 3*1 = 5. */
		if ( MatEsIgual ( SFrmLinEvaluarExt ( p_frmObj, 1.0, 1.0 ), 5.0 ) != 1 )
		{
			printf( "Error caso 2: la evaluacion deberia ser 5: %f\n", SFrmLinEvaluarExt ( p_frmObj, 1.0, 1.0 ) );
			iRes = BOOL_VAL_FALSO;
		}
		/* Multiplicar la forma por 2 duplica los coeficientes. */
		SFrmLinMultiplicar ( p_frmObj, 2.0 );
		if ( MatEsIgual ( SFrmLinCoeficiente1 ( p_frmObj ), 4.0 ) != 1 )
		{
			printf( "Error caso 3: el primer coeficiente deberia ser 4: %f\n", SFrmLinCoeficiente1 ( p_frmObj ) );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la forma lineal\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SFrmLinDestruir ( &p_frmObj );
	return ( iRes );
}



int TestSFormaLineal ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SFormaLineal]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSFrmLinCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSFrmLinEvaluar01 () == BOOL_VAL_CIERTO ) )
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
