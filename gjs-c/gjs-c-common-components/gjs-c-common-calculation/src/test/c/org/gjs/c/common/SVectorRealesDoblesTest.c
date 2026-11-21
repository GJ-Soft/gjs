#include "Base.h"

#include "SVectorRealesDobles.h"
#include "CalculoOperaciones.h"



static int TestSVecRealdCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SVecRealdCrear 01:\n" );

	SVectorRealesDobles * p_vecObj = SVecRealdCrear ( 3 );
	if ( ES_NULO ( p_vecObj ) )
	{
		printf( "Error caso 1: no se esperaba nulo al crear\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SVecRealdEsValido ( p_vecObj ) != 1 )
		{
			printf( "Error caso 2: el vector recien creado deberia ser valido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SVecRealdNumElementos ( p_vecObj ) != 3 )
		{
			printf( "Error caso 3: deberia tener 3 elementos: %d\n", SVecRealdNumElementos ( p_vecObj ) );
			iRes = BOOL_VAL_FALSO;
		}
	}
	SVecRealdDestruir ( &p_vecObj );

	if ( ES_VALIDO ( p_vecObj ) )
	{
		printf( "Error caso 4: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSVecRealdAsignar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SVecRealdAsignar 01:\n" );

	SVectorRealesDobles * p_vecObj = SVecRealdCrear ( 3 );
	if ( ES_VALIDO ( p_vecObj ) )
	{
		if ( SVecRealdAsignar ( p_vecObj, 0, 1.5 ) != 1 )
		{
			printf( "Error caso 1: se esperaba resultado 1 al asignar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SVecRealdAsignar ( p_vecObj, 2, 3.0 );
		if ( MatEsIgual ( SVecRealdElemento ( p_vecObj, 0 ), 1.5 ) != 1 )
		{
			printf( "Error caso 2: el elemento 0 deberia ser 1.5: %f\n", SVecRealdElemento ( p_vecObj, 0 ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( MatEsIgual ( SVecRealdElemento ( p_vecObj, 2 ), 3.0 ) != 1 )
		{
			printf( "Error caso 3: el elemento 2 deberia ser 3.0: %f\n", SVecRealdElemento ( p_vecObj, 2 ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SVecRealdExiste ( p_vecObj, 1.5 ) != 1 )
		{
			printf( "Error caso 4: 1.5 deberia existir en el vector\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SVecRealdExiste ( p_vecObj, 99.0 ) != 0 )
		{
			printf( "Error caso 5: 99 no deberia existir en el vector\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el vector\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SVecRealdDestruir ( &p_vecObj );
	return ( iRes );
}

static int VerificarVec ( SVectorRealesDobles * p_vecObj, double * p_dEsperados, int iNum )
{
	int iRes = BOOL_VAL_CIERTO;

	if ( SVecRealdNumElementos ( p_vecObj ) != iNum )
	{
		printf( "  Verificacion: se esperaban %d posiciones: %d\n", iNum, SVecRealdNumElementos ( p_vecObj ) );
		iRes = BOOL_VAL_FALSO;
	}
	int iPos = 0;
	while ( ( iPos < iNum ) && ( iRes == BOOL_VAL_CIERTO ) )
	{
		if ( MatEsIgual ( SVecRealdElemento ( p_vecObj, iPos ), p_dEsperados [ iPos ] ) != 1 )
		{
			printf( "  Verificacion: en pos %d se esperaba %g: %g\n", iPos, p_dEsperados [ iPos ], SVecRealdElemento ( p_vecObj, iPos ) );
			iRes = BOOL_VAL_FALSO;
		}
		iPos = iPos + 1;
	}
	return ( iRes );
}

/* Una posicion por valor, en orden; 0 valores, el vector nulo o un numero
   negativo dan nulo: un vector no tiene 0 posiciones. */
static int TestSVecRealdCrearDesdeVector01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SVecRealdCrearDesdeVector 01:\n" );

	double dVal [ 4 ] = { 0.0, -DBL_MAX, DBL_MAX, -5.25 };
	SVectorRealesDobles * p_vecObj = SVecRealdCrearDesdeVector ( dVal, 4 );
	if ( ES_NULO ( p_vecObj ) || ( VerificarVec ( p_vecObj, dVal, 4 ) != BOOL_VAL_CIERTO ) )
	{
		printf( "Error caso 1: se esperaba { 0, -DBL_MAX, DBL_MAX, -5.25 }\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SVectorRealesDobles * p_vecParcial = SVecRealdCrearDesdeVector ( dVal, 2 );
	if ( ES_NULO ( p_vecParcial ) || ( VerificarVec ( p_vecParcial, dVal, 2 ) != BOOL_VAL_CIERTO ) )
	{
		printf( "Error caso 2: con 2 valores se esperaba { 0, -DBL_MAX }\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( SVecRealdCrearDesdeVector ( dVal, 0 ) ) )
	{
		printf( "Error caso 3: con 0 valores se esperaba nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( SVecRealdCrearDesdeVector ( NULL, 2 ) ) )
	{
		printf( "Error caso 4: con el vector nulo se esperaba nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( SVecRealdCrearDesdeVector ( dVal, -1 ) ) )
	{
		printf( "Error caso 5: con un numero negativo se esperaba nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SVecRealdDestruir ( &p_vecObj );
	SVecRealdDestruir ( &p_vecParcial );
	ErrLimpiar ();
	return ( iRes );
}

static double SiguienteValor ( int * p_iCont )
{
	*p_iCont = *p_iCont + 1;
	return ( *p_iCont + 0.5 );
}

/* Cualquier numero de valores, el 0 incluido, sin marca de fin; cada
   argumento se evalua una sola vez. */
static int TestSVecRealdCrearConValores01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SVecRealdCrearConValores 01:\n" );

	double dVal [ 5 ] = { 5.5, 0.0, 7.0, -3.25, 0.0 };
	SVectorRealesDobles * p_vecObj = SVecRealdCrearConValores ( 5.5, 0, 7, -3.25, 0.0 );
	if ( ES_NULO ( p_vecObj ) || ( VerificarVec ( p_vecObj, dVal, 5 ) != BOOL_VAL_CIERTO ) )
	{
		printf( "Error caso 1: se esperaba { 5.5, 0, 7, -3.25, 0 }\n" );
		iRes = BOOL_VAL_FALSO;
	}
	double dCero [ 1 ] = { 0.0 };
	SVectorRealesDobles * p_vecCero = SVecRealdCrearConValores ( 0.0 );
	if ( ES_NULO ( p_vecCero ) || ( VerificarVec ( p_vecCero, dCero, 1 ) != BOOL_VAL_CIERTO ) )
	{
		printf( "Error caso 2: se esperaba { 0 }\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* El orden en que se evaluan los inicializadores no esta fijado: se
	   comprueba el numero de llamadas y que esten los tres valores. */
	int iCont = 0;
	SVectorRealesDobles * p_vecLlamadas = SVecRealdCrearConValores ( SiguienteValor ( &iCont ), SiguienteValor ( &iCont ), SiguienteValor ( &iCont ) );
	if ( iCont != 3 )
	{
		printf( "Error caso 3: se esperaban 3 llamadas: %d\n", iCont );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ( SVecRealdNumElementos ( p_vecLlamadas ) != 3 ) || ( SVecRealdExiste ( p_vecLlamadas, 1.5 ) != 1 ) ||
		 ( SVecRealdExiste ( p_vecLlamadas, 2.5 ) != 1 ) || ( SVecRealdExiste ( p_vecLlamadas, 3.5 ) != 1 ) )
	{
		printf( "Error caso 4: se esperaban los valores 1.5, 2.5 y 3.5\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SVecRealdDestruir ( &p_vecObj );
	SVecRealdDestruir ( &p_vecCero );
	SVecRealdDestruir ( &p_vecLlamadas );
	return ( iRes );
}



int TestSVectorRealesDobles ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SVectorRealesDobles]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSVecRealdCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSVecRealdAsignar01 () == BOOL_VAL_CIERTO ) &&
			( TestSVecRealdCrearDesdeVector01 () == BOOL_VAL_CIERTO ) &&
			( TestSVecRealdCrearConValores01 () == BOOL_VAL_CIERTO ) )
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
