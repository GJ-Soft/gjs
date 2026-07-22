#include "Base.h"

#include "Gradianes.h"
#include "ConstantesMatematicas.h"
#include "CalculoOperaciones.h"



static int TestGradValido01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test GradValido 01:\n" );

	if ( GradEsValido ( 45, 30, 0 ) != 1 )
	{
		printf( "Error caso 1: 45o 30' 0'' deberia ser valido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* Los minutos deben estar en [0, 60). */
	if ( GradEsValido ( 45, 70, 0 ) != 0 )
	{
		printf( "Error caso 2: 70 minutos no deberian ser validos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* Los segundos deben estar en [0, 60). */
	if ( GradEsValido ( 45, 0, 70 ) != 0 )
	{
		printf( "Error caso 3: 70 segundos no deberian ser validos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestGradConversion01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test GradConversion 01:\n" );

	if ( MatEsIgual ( GradObtenerAngulo ( 90, 0, 0 ), 90.0 ) != 1 )
	{
		printf( "Error caso 1: 90o deberian ser 90 grados decimales: %f\n", GradObtenerAngulo ( 90, 0, 0 ) );
		iRes = BOOL_VAL_FALSO;
	}
	/* 30 minutos son medio grado. */
	if ( MatEsIgual ( GradObtenerAngulo ( 0, 30, 0 ), 0.5 ) != 1 )
	{
		printf( "Error caso 2: 30' deberian ser 0.5 grados: %f\n", GradObtenerAngulo ( 0, 30, 0 ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( MatEsIgual ( GradObtenerRadianes ( 180, 0, 0 ), PI ) != 1 )
	{
		printf( "Error caso 3: 180o deberian ser PI radianes: %f\n", GradObtenerRadianes ( 180, 0, 0 ) );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestGradValor01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test GradValor 01:\n" );

	if ( GradObtenerValor ( 45, 30, 15 ) != 453015 )
	{
		printf( "Error caso 1: se esperaba 453015: %ld\n", GradObtenerValor ( 45, 30, 15 ) );
		iRes = BOOL_VAL_FALSO;
	}
	int iGrad = 0;
	int iMin = 0;
	int iSeg = 0;
	if ( GradEstablecerValor ( 453015, &iGrad, &iMin, &iSeg ) != 1 )
	{
		printf( "Error caso 2: se esperaba resultado 1 al establecer el valor\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ( iGrad != 45 ) || ( iMin != 30 ) || ( iSeg != 15 ) )
	{
		printf( "Error caso 3: se esperaba 45/30/15: %d/%d/%d\n", iGrad, iMin, iSeg );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}



static int TestGradSegundos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	int iGrad = 0;
	int iMin = 0;
	int iSeg = 0;
	printf( "Test GradSegundos 01:\n" );

	/* Los segundos se redondean con acarreo: 59.8'' redondea a 60'' y arrastra
	   +1 al minuto, dando 0o 1' 0'' ( triple valido ), no (0,0,60). */
	if ( GradEstablecerAngulo ( 59.8 / 3600.0, &iGrad, &iMin, &iSeg ) != 1 )
	{
		printf( "Error caso 1: establecer 59.8'' deberia devolver 1\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ( iGrad != 0 ) || ( iMin != 1 ) || ( iSeg != 0 ) )
	{
		printf( "Error caso 2: 59.8'' deberian redondear con acarreo a 0/1/0: %d/%d/%d\n", iGrad, iMin, iSeg );
		iRes = BOOL_VAL_FALSO;
	}
	if ( GradEsValido ( iGrad, iMin, iSeg ) != 1 )
	{
		printf( "Error caso 3: el triple resultante deberia ser valido: %d/%d/%d\n", iGrad, iMin, iSeg );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}



int TestGradianes ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test Gradianes]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestGradValido01 () == BOOL_VAL_CIERTO ) &&
			( TestGradConversion01 () == BOOL_VAL_CIERTO ) &&
			( TestGradValor01 () == BOOL_VAL_CIERTO ) &&
			( TestGradSegundos01 () == BOOL_VAL_CIERTO ) )
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
