#include "Base.h"

#include "SPuntoND.h"
#include "CalculoOperaciones.h"



static int VerificarPnt ( SPuntoND * p_pntObj, const double * p_dEsperados, int iNum )
{
	int iRes = BOOL_VAL_CIERTO;

	if ( SPntNDDim ( p_pntObj ) != iNum )
	{
		printf( "  Verificacion: se esperaban %d dimensiones: %d\n", iNum, SPntNDDim ( p_pntObj ) );
		iRes = BOOL_VAL_FALSO;
	}
	int iCoord = 1;
	while ( ( iCoord <= iNum ) && ( iRes == BOOL_VAL_CIERTO ) )
	{
		if ( MatEsIgual ( SPntNDX ( p_pntObj, iCoord ), p_dEsperados [ iCoord - 1 ] ) != 1 )
		{
			printf( "  Verificacion: en la coordenada %d se esperaba %g: %g\n", iCoord, p_dEsperados [ iCoord - 1 ], SPntNDX ( p_pntObj, iCoord ) );
			iRes = BOOL_VAL_FALSO;
		}
		iCoord = iCoord + 1;
	}
	return ( iRes );
}

static int VerificarVec ( SVectorND * p_vecObj, const double * p_dEsperados, int iNum )
{
	int iRes = BOOL_VAL_CIERTO;

	if ( SVecNDDim ( p_vecObj ) != iNum )
	{
		printf( "  Verificacion: se esperaban %d dimensiones: %d\n", iNum, SVecNDDim ( p_vecObj ) );
		iRes = BOOL_VAL_FALSO;
	}
	int iCoord = 1;
	while ( ( iCoord <= iNum ) && ( iRes == BOOL_VAL_CIERTO ) )
	{
		if ( MatEsIgual ( SVecNDX ( p_vecObj, iCoord ), p_dEsperados [ iCoord - 1 ] ) != 1 )
		{
			printf( "  Verificacion: en la coordenada %d se esperaba %g: %g\n", iCoord, p_dEsperados [ iCoord - 1 ], SVecNDX ( p_vecObj, iCoord ) );
			iRes = BOOL_VAL_FALSO;
		}
		iCoord = iCoord + 1;
	}
	return ( iRes );
}

static int TestSPntNDCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SPntNDCrear 01:\n" );

	double dCeros [ 2 ] = { 0.0, 0.0 };
	SPuntoND * p_pntObj = SPntNDCrear ( 2 );
	if ( ( SPntNDEsValido ( p_pntObj ) != 1 ) || ( VerificarPnt ( p_pntObj, dCeros, 2 ) != BOOL_VAL_CIERTO ) )
	{
		printf( "Error caso 1: se esperaba un punto valido en el origen de 2 dimensiones\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( SPntNDCrear ( 0 ) ) || ES_VALIDO ( SPntNDCrearExt ( 2, NULL ) ) )
	{
		printf( "Error caso 2: sin dimensiones o sin valores se esperaba nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	double dVal [ 3 ] = { -1.5, 0.25, 8.0 };
	SPuntoND * p_pntVal = SPntNDCrearConValores ( -1.5, 0.25, 8.0 );
	if ( VerificarPnt ( p_pntVal, dVal, 3 ) != BOOL_VAL_CIERTO )
	{
		printf( "Error caso 3: se esperaba ( -1.5, 0.25, 8 )\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ( SPntNDEstablecerX ( p_pntVal, 3, 9.5 ) != 1 ) || ( SPntNDEstablecerX ( p_pntVal, 4, 1.0 ) != 0 ) ||
		 ( MatEsIgual ( SPntNDX ( p_pntVal, 3 ), 9.5 ) != 1 ) || ( MatEsIgual ( SPntNDX ( p_pntVal, 0 ), 0.0 ) != 1 ) )
	{
		printf( "Error caso 4: las coordenadas van de 1 a 3\n" );
		iRes = BOOL_VAL_FALSO;
	}
	double * p_dBuf = (double *) MemReservar ( 2 * sizeof ( double ) );
	p_dBuf [ 0 ] = 7.0;
	p_dBuf [ 1 ] = -7.0;
	SPuntoND * p_pntEnc = SPntNDEncapsular ( 2, p_dBuf );
	if ( ( SPntNDEsValido ( p_pntEnc ) != 1 ) || ( MatEsIgual ( SPntNDX ( p_pntEnc, 2 ), -7.0 ) != 1 ) )
	{
		printf( "Error caso 5: el punto encapsulado deberia usar el array que se le da\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SPntNDDestruir ( &p_pntObj );
	SPntNDDestruir ( &p_pntVal );
	SPntNDDestruir ( &p_pntEnc );
	if ( ES_VALIDO ( p_pntObj ) || ES_VALIDO ( p_pntEnc ) )
	{
		printf( "Error caso 6: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

/* Se comparan todas las coordenadas, la ultima incluida, con tolerancia. */
static int TestSPntNDComparar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SPntNDComparar 01:\n" );

	SPuntoND * p_pntA = SPntNDCrearConValores ( 1.0, 2.0, 3.0 );
	SPuntoND * p_pntUltima = SPntNDCrearConValores ( 1.0, 2.0, 4.0 );
	SPuntoND * p_pntCasi = SPntNDCrearConValores ( 1.0, 2.0, 3.0 + 1e-9 );
	SPuntoND * p_pnt2D = SPntNDCrearConValores ( 1.0, 2.0 );
	SPuntoND * p_pntX = SPntNDCrearConValores ( 1.0, 0.0 );
	SPuntoND * p_pntY = SPntNDCrearConValores ( 0.0, 1.0 );
	SPuntoND * p_pntLejos = SPntNDCrearConValores ( 0.0, 2.0 );

	if ( SPntNDEsIgual ( p_pntA, p_pntUltima ) != 0 )
	{
		printf( "Error caso 1: distintos en la ultima coordenada no son iguales\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SPntNDEsIgual ( p_pntA, p_pntCasi ) != 1 )
	{
		printf( "Error caso 2: con una diferencia de 1e-9 son iguales\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ( SPntNDEsIgual ( p_pntA, p_pnt2D ) != 0 ) || ( SPntNDEsCompatible ( p_pntA, p_pnt2D ) != 0 ) )
	{
		printf( "Error caso 3: con dimensiones distintas no son iguales ni compatibles\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ( SPntNDEsMenor ( p_pntX, p_pntLejos ) != 1 ) || ( SPntNDEsMayor ( p_pntLejos, p_pntX ) != 1 ) ||
		 ( SPntNDEsMayor ( p_pntX, p_pntLejos ) != 0 ) )
	{
		printf( "Error caso 4: ( 1, 0 ) esta mas cerca del origen que ( 0, 2 )\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ( SPntNDEsMenor ( p_pntX, p_pntY ) != 0 ) || ( SPntNDEsMayor ( p_pntX, p_pntY ) != 0 ) ||
		 ( SPntNDEsIgual ( p_pntX, p_pntY ) != 0 ) )
	{
		printf( "Error caso 5: a la misma distancia no son ni menores, ni mayores, ni iguales\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SPntNDDestruir ( &p_pntA );
	SPntNDDestruir ( &p_pntUltima );
	SPntNDDestruir ( &p_pntCasi );
	SPntNDDestruir ( &p_pnt2D );
	SPntNDDestruir ( &p_pntX );
	SPntNDDestruir ( &p_pntY );
	SPntNDDestruir ( &p_pntLejos );
	return ( iRes );
}

static int TestSPntNDDistancia01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SPntNDDistancia 01:\n" );

	SPuntoND * p_pnt3D = SPntNDCrearConValores ( 1.0, -2.0, 2.0 );
	SPuntoND * p_pnt4D = SPntNDCrearConValores ( 1.0, 1.0, -1.0, 1.0 );
	SPuntoND * p_pntA = SPntNDCrearConValores ( 1.0, 1.0 );
	SPuntoND * p_pntB = SPntNDCrearConValores ( 4.0, 5.0 );

	if ( MatEsIgual ( SPntNDDistanciaAlOrigen ( p_pnt3D ), 3.0 ) != 1 )
	{
		printf( "Error caso 1: ( 1, -2, 2 ) esta a 3 del origen: %g\n", SPntNDDistanciaAlOrigen ( p_pnt3D ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( MatEsIgual ( SPntNDDistanciaAlOrigen ( p_pnt4D ), 2.0 ) != 1 )
	{
		printf( "Error caso 2: ( 1, 1, -1, 1 ) esta a 2 del origen: %g\n", SPntNDDistanciaAlOrigen ( p_pnt4D ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ( MatEsIgual ( SPntNDDistancia ( p_pntA, p_pntB ), 5.0 ) != 1 ) || ( MatEsIgual ( SPntNDDistancia ( p_pntB, p_pntA ), 5.0 ) != 1 ) )
	{
		printf( "Error caso 3: de ( 1, 1 ) a ( 4, 5 ) hay 5: %g\n", SPntNDDistancia ( p_pntA, p_pntB ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ( MatEsIgual ( SPntNDDistancia ( p_pntA, p_pnt3D ), -1.0 ) != 1 ) || ( MatEsIgual ( SPntNDDistanciaAlOrigen ( NULL ), -1.0 ) != 1 ) )
	{
		printf( "Error caso 4: sin puntos compatibles se esperaba -1\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SPntNDDestruir ( &p_pnt3D );
	SPntNDDestruir ( &p_pnt4D );
	SPntNDDestruir ( &p_pntA );
	SPntNDDestruir ( &p_pntB );
	return ( iRes );
}

/* Vector, VectorHacia y Desplazar recorren todas las coordenadas, sin
   desplazarlas. */
static int TestSPntNDVectores01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SPntNDVectores 01:\n" );

	SPuntoND * p_pntA = SPntNDCrearConValores ( 1.0, 2.0, 3.0 );
	SPuntoND * p_pntB = SPntNDCrearConValores ( 4.0, 6.0, 8.0 );
	SPuntoND * p_pnt2D = SPntNDCrearConValores ( 4.0, 6.0 );

	double dA [ 3 ] = { 1.0, 2.0, 3.0 };
	SVectorND * p_vecA = SPntNDVector ( p_pntA );
	if ( VerificarVec ( p_vecA, dA, 3 ) != BOOL_VAL_CIERTO )
	{
		printf( "Error caso 1: el vector de ( 1, 2, 3 ) deberia ser ( 1, 2, 3 )\n" );
		iRes = BOOL_VAL_FALSO;
	}
	double dAB [ 3 ] = { 3.0, 4.0, 5.0 };
	SVectorND * p_vecAB = SPntNDVectorHacia ( p_pntA, p_pntB );
	if ( VerificarVec ( p_vecAB, dAB, 3 ) != BOOL_VAL_CIERTO )
	{
		printf( "Error caso 2: de ( 1, 2, 3 ) a ( 4, 6, 8 ) se esperaba ( 3, 4, 5 )\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( SPntNDVectorHacia ( p_pntA, p_pnt2D ) ) )
	{
		printf( "Error caso 3: con dimensiones distintas se esperaba nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SVectorND * p_vecDesp = SVecNDCrearConValores ( 1.0, -1.0, 0.5 );
	double dDesp [ 3 ] = { 2.0, 1.0, 3.5 };
	if ( ( SPntNDDesplazar ( p_pntA, p_vecDesp ) != 1 ) || ( VerificarPnt ( p_pntA, dDesp, 3 ) != BOOL_VAL_CIERTO ) )
	{
		printf( "Error caso 4: desplazado deberia quedar en ( 2, 1, 3.5 ) y devolver 1\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SVectorND * p_vec2D = SVecNDCrearConValores ( 1.0, 1.0 );
	if ( ( SPntNDDesplazar ( p_pntA, p_vec2D ) != 0 ) || ( VerificarPnt ( p_pntA, dDesp, 3 ) != BOOL_VAL_CIERTO ) )
	{
		printf( "Error caso 5: con un vector de otra dimension se esperaba 0 y el punto sin tocar\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SPuntoND * p_pntDup = SPntNDDuplicar ( p_pntB );
	SPntNDEstablecerX ( p_pntB, 1, 0.0 );
	double dB [ 3 ] = { 4.0, 6.0, 8.0 };
	if ( VerificarPnt ( p_pntDup, dB, 3 ) != BOOL_VAL_CIERTO )
	{
		printf( "Error caso 6: el duplicado no deberia cambiar con el original\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ( SPntNDAsignar ( p_pntB, p_pntDup ) != 1 ) || ( VerificarPnt ( p_pntB, dB, 3 ) != BOOL_VAL_CIERTO ) ||
		 ( SPntNDAsignar ( p_pntB, p_pnt2D ) != 0 ) )
	{
		printf( "Error caso 7: asignar copia entre puntos compatibles y falla con los demas\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SPntNDDestruir ( &p_pntA );
	SPntNDDestruir ( &p_pntB );
	SPntNDDestruir ( &p_pnt2D );
	SPntNDDestruir ( &p_pntDup );
	SVecNDDestruir ( &p_vecA );
	SVecNDDestruir ( &p_vecAB );
	SVecNDDestruir ( &p_vecDesp );
	SVecNDDestruir ( &p_vec2D );
	return ( iRes );
}



int TestSPuntoND ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SPuntoND]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSPntNDCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSPntNDComparar01 () == BOOL_VAL_CIERTO ) &&
			( TestSPntNDDistancia01 () == BOOL_VAL_CIERTO ) &&
			( TestSPntNDVectores01 () == BOOL_VAL_CIERTO ) )
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
