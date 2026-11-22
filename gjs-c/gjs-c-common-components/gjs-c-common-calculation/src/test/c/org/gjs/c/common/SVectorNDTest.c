#include "Base.h"

#include "SVectorND.h"
#include "CalculoOperaciones.h"
#include "ConstantesMatematicas.h"

#include <float.h>



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

static int TestSVecNDCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SVecNDCrear 01:\n" );

	double dCeros [ 3 ] = { 0.0, 0.0, 0.0 };
	SVectorND * p_vecObj = SVecNDCrear ( 3 );
	if ( ( SVecNDEsValido ( p_vecObj ) != 1 ) || ( VerificarVec ( p_vecObj, dCeros, 3 ) != BOOL_VAL_CIERTO ) )
	{
		printf( "Error caso 1: se esperaba un vector valido de 3 ceros\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( SVecNDCrear ( 0 ) ) || ES_VALIDO ( SVecNDCrear ( -1 ) ) )
	{
		printf( "Error caso 2: con 0 o menos dimensiones se esperaba nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SVecNDDestruir ( &p_vecObj );
	if ( ES_VALIDO ( p_vecObj ) )
	{
		printf( "Error caso 3: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ( SVecNDEsValido ( NULL ) != 0 ) || ( SVecNDDim ( NULL ) != 0 ) )
	{
		printf( "Error caso 4: el vector nulo no es valido y tiene 0 dimensiones\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

/* Las coordenadas van de 1 a N: fuera de ese rango se lee 0 y no se escribe. */
static int TestSVecNDCoordenadas01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SVecNDCoordenadas 01:\n" );

	double dVal [ 3 ] = { 1.5, -2.25, 3.0 };
	SVectorND * p_vecObj = SVecNDCrearConValores ( 1.5, -2.25, 3.0 );
	if ( VerificarVec ( p_vecObj, dVal, 3 ) != BOOL_VAL_CIERTO )
	{
		printf( "Error caso 1: se esperaba { 1.5, -2.25, 3 }\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ( MatEsIgual ( SVecNDX ( p_vecObj, 0 ), 0.0 ) != 1 ) || ( MatEsIgual ( SVecNDX ( p_vecObj, 4 ), 0.0 ) != 1 ) )
	{
		printf( "Error caso 2: fuera de rango se esperaba leer 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ( SVecNDEstablecerX ( p_vecObj, 0, 9.0 ) != 0 ) || ( SVecNDEstablecerX ( p_vecObj, 4, 9.0 ) != 0 ) )
	{
		printf( "Error caso 3: fuera de rango no se deberia poder escribir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ( SVecNDEstablecerX ( p_vecObj, 3, 7.5 ) != 1 ) || ( MatEsIgual ( SVecNDX ( p_vecObj, 3 ), 7.5 ) != 1 ) )
	{
		printf( "Error caso 4: la ultima coordenada deberia poder escribirse\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( SVecNDCrearExt ( 2, NULL ) ) )
	{
		printf( "Error caso 5: sin valores se esperaba nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SVecNDDestruir ( &p_vecObj );

	double * p_dBuf = (double *) MemReservar ( 2 * sizeof ( double ) );
	p_dBuf [ 0 ] = 4.0;
	p_dBuf [ 1 ] = 5.0;
	SVectorND * p_vecEnc = SVecNDEncapsular ( 2, p_dBuf );
	if ( ( SVecNDValores ( p_vecEnc ) != p_dBuf ) || ( MatEsIgual ( SVecNDX ( p_vecEnc, 2 ), 5.0 ) != 1 ) )
	{
		printf( "Error caso 6: el vector encapsulado deberia usar el array que se le da\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( SVecNDEncapsular ( 2, NULL ) ) || ES_VALIDO ( SVecNDEncapsular ( 0, p_dBuf ) ) )
	{
		printf( "Error caso 7: sin array o sin dimensiones se esperaba nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SVecNDDestruir ( &p_vecEnc );
	return ( iRes );
}

/* El unitario puede estar en cualquier coordenada, la ultima incluida. */
static int TestSVecNDUnitario01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SVecNDUnitario 01:\n" );

	double dE3 [ 3 ] = { 0.0, 0.0, 1.0 };
	double dE1 [ 3 ] = { 1.0, 0.0, 0.0 };
	SVectorND * p_vecE3 = SVecNDUnitario ( 3, 3 );
	if ( VerificarVec ( p_vecE3, dE3, 3 ) != BOOL_VAL_CIERTO )
	{
		printf( "Error caso 1: se esperaba { 0, 0, 1 }\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SVectorND * p_vecE1 = SVecNDUnitario ( 3, 1 );
	if ( VerificarVec ( p_vecE1, dE1, 3 ) != BOOL_VAL_CIERTO )
	{
		printf( "Error caso 2: se esperaba { 1, 0, 0 }\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( SVecNDUnitario ( 3, 0 ) ) || ES_VALIDO ( SVecNDUnitario ( 3, 4 ) ) )
	{
		printf( "Error caso 3: con la coordenada fuera de rango se esperaba nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SVecNDDestruir ( &p_vecE3 );
	SVecNDDestruir ( &p_vecE1 );
	return ( iRes );
}

static int TestSVecNDOperaciones01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SVecNDOperaciones 01:\n" );

	SVectorND * p_vecA = SVecNDCrearConValores ( 1.0, 2.0, 3.0 );
	SVectorND * p_vecB = SVecNDCrearConValores ( 0.5, -1.0, 4.0 );
	SVectorND * p_vec2D = SVecNDCrearConValores ( 1.0, 1.0 );

	double dSuma [ 3 ] = { 1.5, 1.0, 7.0 };
	if ( ( SVecNDSumar ( p_vecA, p_vecB ) != 1 ) || ( VerificarVec ( p_vecA, dSuma, 3 ) != BOOL_VAL_CIERTO ) )
	{
		printf( "Error caso 1: la suma deberia ser { 1.5, 1, 7 }\n" );
		iRes = BOOL_VAL_FALSO;
	}
	double dResta [ 3 ] = { 1.0, 2.0, 3.0 };
	if ( ( SVecNDRestar ( p_vecA, p_vecB ) != 1 ) || ( VerificarVec ( p_vecA, dResta, 3 ) != BOOL_VAL_CIERTO ) )
	{
		printf( "Error caso 2: la resta deberia devolver { 1, 2, 3 }\n" );
		iRes = BOOL_VAL_FALSO;
	}
	double dPor [ 3 ] = { -2.5, -5.0, -7.5 };
	if ( ( SVecNDMultiplicar ( p_vecA, -2.5 ) != 1 ) || ( VerificarVec ( p_vecA, dPor, 3 ) != BOOL_VAL_CIERTO ) )
	{
		printf( "Error caso 3: por -2.5 deberia ser { -2.5, -5, -7.5 }\n" );
		iRes = BOOL_VAL_FALSO;
	}
	double dInv [ 3 ] = { 2.5, 5.0, 7.5 };
	if ( ( SVecNDInvertirDireccion ( p_vecA ) != 1 ) || ( VerificarVec ( p_vecA, dInv, 3 ) != BOOL_VAL_CIERTO ) )
	{
		printf( "Error caso 4: invertido deberia ser { 2.5, 5, 7.5 }\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ( SVecNDSumar ( p_vecA, p_vec2D ) != 0 ) || ( SVecNDRestar ( p_vecA, p_vec2D ) != 0 ) ||
		 ( SVecNDAsignar ( p_vecA, p_vec2D ) != 0 ) || ( SVecNDEsCompatible ( p_vecA, p_vec2D ) != 0 ) )
	{
		printf( "Error caso 5: con dimensiones distintas se esperaba 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	double dB [ 3 ] = { 0.5, -1.0, 4.0 };
	if ( ( SVecNDAsignar ( p_vecA, p_vecB ) != 1 ) || ( VerificarVec ( p_vecA, dB, 3 ) != BOOL_VAL_CIERTO ) )
	{
		printf( "Error caso 6: tras asignar deberia ser { 0.5, -1, 4 }\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SVectorND * p_vecDup = SVecNDDuplicar ( p_vecB );
	SVecNDEstablecerX ( p_vecB, 1, 100.0 );
	if ( VerificarVec ( p_vecDup, dB, 3 ) != BOOL_VAL_CIERTO )
	{
		printf( "Error caso 7: el duplicado no deberia cambiar con el original\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SVecNDDestruir ( &p_vecA );
	SVecNDDestruir ( &p_vecB );
	SVecNDDestruir ( &p_vec2D );
	SVecNDDestruir ( &p_vecDup );
	return ( iRes );
}

static int TestSVecNDNorma01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SVecNDNorma 01:\n" );

	SVectorND * p_vec2D = SVecNDCrearConValores ( 3.0, -4.0 );
	SVectorND * p_vec3D = SVecNDCrearConValores ( 1.0, 2.0, 2.0 );
	SVectorND * p_vecCero = SVecNDCrear ( 3 );
	if ( MatEsIgual ( SVecNDNorma ( p_vec2D ), 5.0 ) != 1 )
	{
		printf( "Error caso 1: la norma de ( 3, -4 ) es 5: %g\n", SVecNDNorma ( p_vec2D ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( MatEsIgual ( SVecNDNorma ( p_vec3D ), 3.0 ) != 1 )
	{
		printf( "Error caso 2: la norma de ( 1, 2, 2 ) es 3: %g\n", SVecNDNorma ( p_vec3D ) );
		iRes = BOOL_VAL_FALSO;
	}
	ErrLimpiar ();
	if ( MatEsIgual ( SVecNDNorma ( NULL ), -1.0 ) != 1 )
	{
		printf( "Error caso 3: la norma del vector nulo deberia ser -1\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ( ErrHayError () != 1 ) || ( ErrCodigo () != ERR_PARAMETROS ) )
	{
		printf( "Error caso 3b: la norma del vector nulo deberia dejar ERR_PARAMETROS\n" );
		iRes = BOOL_VAL_FALSO;
	}
	ErrLimpiar ();
	double dUnit [ 2 ] = { 0.6, -0.8 };
	SVecNDNorma ( p_vec2D );
	if ( ErrHayError () != 0 )
	{
		printf( "Error caso 3c: la norma de un vector valido no deberia dejar error\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ( SVecNDNormalizar ( p_vec2D ) != 1 ) || ( VerificarVec ( p_vec2D, dUnit, 2 ) != BOOL_VAL_CIERTO ) )
	{
		printf( "Error caso 4: normalizado deberia ser { 0.6, -0.8 }\n" );
		iRes = BOOL_VAL_FALSO;
	}
	double dCeros [ 3 ] = { 0.0, 0.0, 0.0 };
	if ( ( SVecNDNormalizar ( p_vecCero ) != 0 ) || ( VerificarVec ( p_vecCero, dCeros, 3 ) != BOOL_VAL_CIERTO ) )
	{
		printf( "Error caso 5: el vector cero no se puede normalizar y deberia quedar igual\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SVecNDDestruir ( &p_vec2D );
	SVecNDDestruir ( &p_vec3D );
	SVecNDDestruir ( &p_vecCero );
	return ( iRes );
}

static int TestSVecNDProductos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SVecNDProductos 01:\n" );

	SVectorND * p_vecA = SVecNDCrearConValores ( 1.0, 2.0, 3.0 );
	SVectorND * p_vecB = SVecNDCrearConValores ( 4.0, -5.0, 6.0 );
	SVectorND * p_vecC = SVecNDCrearConValores ( 2.0, 3.0, 4.0 );
	SVectorND * p_vecD = SVecNDCrearConValores ( 5.0, 6.0, 7.0 );
	SVectorND * p_vecI = SVecNDUnitario ( 3, 1 );
	SVectorND * p_vecJ = SVecNDUnitario ( 3, 2 );
	SVectorND * p_vec2D = SVecNDCrearConValores ( 1.0, 2.0 );
	SVectorND * p_vec2Db = SVecNDCrearConValores ( 3.0, 4.0 );

	/* 1*4 + 2*(-5) + 3*6 = 12 */
	if ( MatEsIgual ( SVecNDProductoEscalar ( p_vecA, p_vecB ), 12.0 ) != 1 )
	{
		printf( "Error caso 1: el producto escalar deberia ser 12: %g\n", SVecNDProductoEscalar ( p_vecA, p_vecB ) );
		iRes = BOOL_VAL_FALSO;
	}
	ErrLimpiar ();
	if ( MatEsIgual ( SVecNDProductoEscalar ( p_vecA, p_vec2D ), -1.0 ) != 1 )
	{
		printf( "Error caso 2: con dimensiones distintas el producto escalar deberia dar -1\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ( ErrHayError () != 1 ) || ( ErrCodigo () != ERR_PARAMETROS ) )
	{
		printf( "Error caso 2b: con dimensiones distintas deberia dejar ERR_PARAMETROS\n" );
		iRes = BOOL_VAL_FALSO;
	}
	ErrLimpiar ();
	double dK [ 3 ] = { 0.0, 0.0, 1.0 };
	SVectorND * p_vecK = SVecNDProductoVectorial ( p_vecI, p_vecJ );
	if ( VerificarVec ( p_vecK, dK, 3 ) != BOOL_VAL_CIERTO )
	{
		printf( "Error caso 3: i x j deberia ser k\n" );
		iRes = BOOL_VAL_FALSO;
	}
	double dCD [ 3 ] = { -3.0, 6.0, -3.0 };
	SVectorND * p_vecCD = SVecNDProductoVectorial ( p_vecC, p_vecD );
	if ( VerificarVec ( p_vecCD, dCD, 3 ) != BOOL_VAL_CIERTO )
	{
		printf( "Error caso 4: ( 2, 3, 4 ) x ( 5, 6, 7 ) deberia ser ( -3, 6, -3 )\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( SVecNDProductoVectorial ( p_vec2D, p_vec2Db ) ) || ES_VALIDO ( SVecNDProductoVectorial ( p_vecA, p_vec2D ) ) )
	{
		printf( "Error caso 5: fuera de 3 dimensiones el producto vectorial deberia ser nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SVecNDDestruir ( &p_vecA );
	SVecNDDestruir ( &p_vecB );
	SVecNDDestruir ( &p_vecC );
	SVecNDDestruir ( &p_vecD );
	SVecNDDestruir ( &p_vecI );
	SVecNDDestruir ( &p_vecJ );
	SVecNDDestruir ( &p_vecK );
	SVecNDDestruir ( &p_vecCD );
	SVecNDDestruir ( &p_vec2D );
	SVecNDDestruir ( &p_vec2Db );
	return ( iRes );
}

/* Dependientes si uno es multiplo del otro; ortogonales no lo son. */
static int TestSVecNDDependencia01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SVecNDDependencia 01:\n" );

	SVectorND * p_vecA = SVecNDCrearConValores ( 1.0, 2.0, 3.0 );
	SVectorND * p_vecMenosDosA = SVecNDCrearConValores ( -2.0, -4.0, -6.0 );
	SVectorND * p_vecCasiA = SVecNDCrearConValores ( 1.0, 2.0, 3.1 );
	SVectorND * p_vecCero = SVecNDCrear ( 3 );
	SVectorND * p_vecI = SVecNDUnitario ( 2, 1 );
	SVectorND * p_vecJ = SVecNDUnitario ( 2, 2 );
	SVectorND * p_vecGrande = SVecNDCrearConValores ( 1.0e4, 2.0e4 );
	SVectorND * p_vecGrande3 = SVecNDCrearConValores ( 3.0e4, 6.0e4 );

	if ( ( SVecNDEsLinealmenteDependiente ( p_vecA, p_vecMenosDosA ) != 1 ) ||
		 ( SVecNDEsLinealmenteIndependiente ( p_vecA, p_vecMenosDosA ) != 0 ) )
	{
		printf( "Error caso 1: ( 1, 2, 3 ) y ( -2, -4, -6 ) son dependientes\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ( SVecNDEsLinealmenteDependiente ( p_vecA, p_vecCasiA ) != 0 ) ||
		 ( SVecNDEsLinealmenteIndependiente ( p_vecA, p_vecCasiA ) != 1 ) )
	{
		printf( "Error caso 2: ( 1, 2, 3 ) y ( 1, 2, 3.1 ) son independientes\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ( SVecNDEsLinealmenteDependiente ( p_vecI, p_vecJ ) != 0 ) ||
		 ( SVecNDEsLinealmenteIndependiente ( p_vecI, p_vecJ ) != 1 ) )
	{
		printf( "Error caso 3: dos vectores ortogonales son independientes\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SVecNDEsLinealmenteDependiente ( p_vecA, p_vecCero ) != 1 )
	{
		printf( "Error caso 4: el vector cero es dependiente de cualquiera\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SVecNDEsLinealmenteDependiente ( p_vecGrande, p_vecGrande3 ) != 1 )
	{
		printf( "Error caso 5: la tolerancia no deberia depender del tamano de los vectores\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ( SVecNDEsLinealmenteDependiente ( p_vecA, p_vecI ) != 0 ) ||
		 ( SVecNDEsLinealmenteIndependiente ( p_vecA, p_vecI ) != 0 ) )
	{
		printf( "Error caso 6: con dimensiones distintas las dos deberian dar 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SVecNDDestruir ( &p_vecA );
	SVecNDDestruir ( &p_vecMenosDosA );
	SVecNDDestruir ( &p_vecCasiA );
	SVecNDDestruir ( &p_vecCero );
	SVecNDDestruir ( &p_vecI );
	SVecNDDestruir ( &p_vecJ );
	SVecNDDestruir ( &p_vecGrande );
	SVecNDDestruir ( &p_vecGrande3 );
	return ( iRes );
}

/* Las coordenadas de la pendiente y el angulo tambien van desde 1; el angulo
   conserva el cuadrante. */
static int TestSVecNDPendienteAngulo01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SVecNDPendienteAngulo 01:\n" );

	SVectorND * p_vecDiag = SVecNDCrearConValores ( 2.0, 2.0, 0.0 );
	SVectorND * p_vecIzq = SVecNDCrearConValores ( -1.0, 0.0 );
	SVectorND * p_vecTercer = SVecNDCrearConValores ( -1.0, -1.0 );
	SVectorND * p_vecArriba = SVecNDCrearConValores ( 0.0, 3.0 );
	SVectorND * p_vecAbajo = SVecNDCrearConValores ( 0.0, -3.0 );
	SVectorND * p_vecPend = SVecNDCrearConValores ( 4.0, 0.0, -2.0 );
	ErrLimpiar ();

	if ( ( MatEsIgual ( SVecNDPendiente ( p_vecDiag, 2, 1 ), 1.0 ) != 1 ) ||
		 ( MatEsIgual ( SVecNDAngulo ( p_vecDiag, 2, 1 ), PI_32 / 4 ) != 1 ) )
	{
		printf( "Error caso 1: ( 2, 2 ) tiene pendiente 1 y angulo PI/4\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( MatEsIgual ( SVecNDPendiente ( p_vecPend, 3, 1 ), -0.5 ) != 1 )
	{
		printf( "Error caso 2: en las coordenadas 1 y 3 de ( 4, 0, -2 ) la pendiente es -0.5: %g\n", SVecNDPendiente ( p_vecPend, 3, 1 ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( MatEsIgual ( SVecNDAngulo ( p_vecIzq, 2, 1 ), PI_32 ) != 1 )
	{
		printf( "Error caso 3: ( -1, 0 ) tiene angulo PI: %g\n", SVecNDAngulo ( p_vecIzq, 2, 1 ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( MatEsIgual ( SVecNDAngulo ( p_vecTercer, 2, 1 ), -3 * PI_32 / 4 ) != 1 )
	{
		printf( "Error caso 4: ( -1, -1 ) tiene angulo -3PI/4: %g\n", SVecNDAngulo ( p_vecTercer, 2, 1 ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ( SVecNDPendiente ( p_vecArriba, 2, 1 ) != DBL_MAX ) || ( MatEsIgual ( SVecNDAngulo ( p_vecArriba, 2, 1 ), PI_32 / 2 ) != 1 ) )
	{
		printf( "Error caso 5: ( 0, 3 ) tiene pendiente DBL_MAX y angulo PI/2\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ( SVecNDPendiente ( p_vecAbajo, 2, 1 ) != -DBL_MAX ) || ( MatEsIgual ( SVecNDAngulo ( p_vecAbajo, 2, 1 ), -PI_32 / 2 ) != 1 ) )
	{
		printf( "Error caso 6: ( 0, -3 ) tiene pendiente -DBL_MAX y angulo -PI/2\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ErrHayError () != 0 )
	{
		printf( "Error caso 6b: con coordenadas validas no deberia quedar error\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ( MatEsIgual ( SVecNDPendiente ( p_vecDiag, 2, 2 ), -1.0 ) != 1 ) || ( MatEsIgual ( SVecNDPendiente ( p_vecDiag, 4, 1 ), -1.0 ) != 1 ) ||
		 ( MatEsIgual ( SVecNDAngulo ( p_vecDiag, 0, 1 ), -1.0 ) != 1 ) )
	{
		printf( "Error caso 7: con coordenadas repetidas o fuera de rango se esperaba -1\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ( ErrHayError () != 1 ) || ( ErrCodigo () != ERR_PARAMETROS ) )
	{
		printf( "Error caso 7b: con coordenadas no validas deberia quedar ERR_PARAMETROS\n" );
		iRes = BOOL_VAL_FALSO;
	}
	ErrLimpiar ();
	SVecNDAngulo ( p_vecDiag, 1, 1 );
	if ( ( ErrHayError () != 1 ) || ( ErrCodigo () != ERR_PARAMETROS ) )
	{
		printf( "Error caso 8: el angulo con coordenadas repetidas deberia dejar ERR_PARAMETROS\n" );
		iRes = BOOL_VAL_FALSO;
	}
	ErrLimpiar ();
	SVecNDDestruir ( &p_vecDiag );
	SVecNDDestruir ( &p_vecIzq );
	SVecNDDestruir ( &p_vecTercer );
	SVecNDDestruir ( &p_vecArriba );
	SVecNDDestruir ( &p_vecAbajo );
	SVecNDDestruir ( &p_vecPend );
	return ( iRes );
}

/* Suma y Diferencia dan un vector nuevo y no tocan los que reciben. */
static int TestSVecNDSumaDiferencia01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SVecNDSumaDiferencia 01:\n" );

	SVectorND * p_vecX = SVecNDCrearConValores ( 1.0, 2.5, -3.0 );
	SVectorND * p_vecY = SVecNDCrearConValores ( 0.5, -1.0, 4.0 );
	SVectorND * p_vec2D = SVecNDCrearConValores ( 1.0, 1.0 );
	double dX [ 3 ] = { 1.0, 2.5, -3.0 };
	double dY [ 3 ] = { 0.5, -1.0, 4.0 };

	double dSuma [ 3 ] = { 1.5, 1.5, 1.0 };
	SVectorND * p_vecSuma = SVecNDSuma ( p_vecX, p_vecY );
	if ( VerificarVec ( p_vecSuma, dSuma, 3 ) != BOOL_VAL_CIERTO )
	{
		printf( "Error caso 1: la suma deberia ser { 1.5, 1.5, 1 }\n" );
		iRes = BOOL_VAL_FALSO;
	}
	double dDif [ 3 ] = { 0.5, 3.5, -7.0 };
	SVectorND * p_vecDif = SVecNDDiferencia ( p_vecX, p_vecY );
	if ( VerificarVec ( p_vecDif, dDif, 3 ) != BOOL_VAL_CIERTO )
	{
		printf( "Error caso 2: la diferencia deberia ser { 0.5, 3.5, -7 }\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ( VerificarVec ( p_vecX, dX, 3 ) != BOOL_VAL_CIERTO ) || ( VerificarVec ( p_vecY, dY, 3 ) != BOOL_VAL_CIERTO ) )
	{
		printf( "Error caso 3: los vectores de partida no deberian cambiar\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( SVecNDSuma ( p_vecX, p_vec2D ) ) || ES_VALIDO ( SVecNDDiferencia ( p_vecX, NULL ) ) )
	{
		printf( "Error caso 4: con vectores no compatibles se esperaba nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SVecNDDestruir ( &p_vecX );
	SVecNDDestruir ( &p_vecY );
	SVecNDDestruir ( &p_vec2D );
	SVecNDDestruir ( &p_vecSuma );
	SVecNDDestruir ( &p_vecDif );
	return ( iRes );
}



int TestSVectorND ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SVectorND]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSVecNDCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSVecNDCoordenadas01 () == BOOL_VAL_CIERTO ) &&
			( TestSVecNDUnitario01 () == BOOL_VAL_CIERTO ) &&
			( TestSVecNDOperaciones01 () == BOOL_VAL_CIERTO ) &&
			( TestSVecNDSumaDiferencia01 () == BOOL_VAL_CIERTO ) &&
			( TestSVecNDNorma01 () == BOOL_VAL_CIERTO ) &&
			( TestSVecNDProductos01 () == BOOL_VAL_CIERTO ) &&
			( TestSVecNDDependencia01 () == BOOL_VAL_CIERTO ) &&
			( TestSVecNDPendienteAngulo01 () == BOOL_VAL_CIERTO ) )
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
