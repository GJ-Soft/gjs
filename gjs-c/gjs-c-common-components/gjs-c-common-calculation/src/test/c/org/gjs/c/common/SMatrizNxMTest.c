#include "Base.h"

#include "SMatrizNxM.h"
#include "CalculoOperaciones.h"

/* Los valores esperados de determinantes, adjuntos e inversas se calcularon
   aparte, con fracciones exactas y desarrollo de Laplace. */



static int VerificarMat ( SMatrizNxM * p_matObj, const double * p_dEsperados, int iFilas, int iColumnas )
{
	int iRes = BOOL_VAL_CIERTO;

	if ( ( SMatNxMFilas ( p_matObj ) != iFilas ) || ( SMatNxMColumnas ( p_matObj ) != iColumnas ) )
	{
		printf( "  Verificacion: se esperaba %dx%d: %dx%d\n", iFilas, iColumnas, SMatNxMFilas ( p_matObj ), SMatNxMColumnas ( p_matObj ) );
		iRes = BOOL_VAL_FALSO;
	}
	int iF = 1;
	while ( ( iF <= iFilas ) && ( iRes == BOOL_VAL_CIERTO ) )
	{
		int iC = 1;
		while ( ( iC <= iColumnas ) && ( iRes == BOOL_VAL_CIERTO ) )
		{
			double dEsp = p_dEsperados [ ( iF - 1 ) * iColumnas + iC - 1 ];
			if ( MatEsIgual ( SMatNxMX ( p_matObj, iF, iC ), dEsp ) != 1 )
			{
				printf( "  Verificacion: en ( %d, %d ) se esperaba %g: %g\n", iF, iC, dEsp, SMatNxMX ( p_matObj, iF, iC ) );
				iRes = BOOL_VAL_FALSO;
			}
			iC = iC + 1;
		}
		iF = iF + 1;
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

static const double M23 [ 6 ] = { 1.0, 2.0, 3.0,
								  4.0, 5.0, 6.0 };

static int TestSMatNxMCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SMatNxMCrear 01:\n" );

	double dCeros [ 6 ] = { 0.0 };
	SMatrizNxM * p_matCero = SMatNxMCrear ( 2, 3 );
	if ( ( SMatNxMEsValida ( p_matCero ) != 1 ) || ( VerificarMat ( p_matCero, dCeros, 2, 3 ) != BOOL_VAL_CIERTO ) )
	{
		printf( "Error caso 1: se esperaba una matriz valida 2x3 de ceros\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( SMatNxMCrear ( 0, 3 ) ) || ES_VALIDO ( SMatNxMCrear ( 2, 0 ) ) || ES_VALIDO ( SMatNxMCrearExt ( 2, 3, NULL ) ) )
	{
		printf( "Error caso 2: sin filas, sin columnas o sin valores se esperaba nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SMatrizNxM * p_matObj = SMatNxMCrearExt ( 2, 3, M23 );
	if ( ( VerificarMat ( p_matObj, M23, 2, 3 ) != BOOL_VAL_CIERTO ) || ( MatEsIgual ( SMatNxMX ( p_matObj, 2, 1 ), 4.0 ) != 1 ) )
	{
		printf( "Error caso 3: los valores van fila a fila\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ( MatEsIgual ( SMatNxMX ( p_matObj, 3, 1 ), 0.0 ) != 1 ) || ( MatEsIgual ( SMatNxMX ( p_matObj, 1, 0 ), 0.0 ) != 1 ) ||
		 ( SMatNxMEstablecerX ( p_matObj, 1, 4, 9.0 ) != 0 ) || ( SMatNxMEstablecerX ( p_matObj, 2, 3, 9.0 ) != 1 ) ||
		 ( MatEsIgual ( SMatNxMX ( p_matObj, 2, 3 ), 9.0 ) != 1 ) )
	{
		printf( "Error caso 4: las filas van de 1 a 2 y las columnas de 1 a 3\n" );
		iRes = BOOL_VAL_FALSO;
	}
	double * p_dFila = SMatNxMValoresFila ( p_matObj, 2 );
	if ( ES_NULO ( p_dFila ) || ( MatEsIgual ( p_dFila [ 0 ], 4.0 ) != 1 ) || ES_VALIDO ( SMatNxMValoresFila ( p_matObj, 3 ) ) )
	{
		printf( "Error caso 5: ValoresFila de la fila 2 empieza en el 4\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SMatNxMDestruir ( &p_matCero );
	SMatNxMDestruir ( &p_matObj );
	if ( ES_VALIDO ( p_matObj ) || ( SMatNxMEsValida ( NULL ) != 0 ) || ( SMatNxMFilas ( NULL ) != 0 ) )
	{
		printf( "Error caso 6: tras destruir se esperaba nulo, y la nula no es valida\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSMatNxMUnosIdentidad01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SMatNxMUnosIdentidad 01:\n" );

	double dUnos [ 6 ] = { 1.0, 1.0, 1.0, 1.0, 1.0, 1.0 };
	SMatrizNxM * p_matUnos = SMatNxMUnos ( 2, 3 );
	if ( VerificarMat ( p_matUnos, dUnos, 2, 3 ) != BOOL_VAL_CIERTO )
	{
		printf( "Error caso 1: se esperaba una 2x3 de unos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	double dI3 [ 9 ] = { 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0 };
	SMatrizNxM * p_matI3 = SMatNxMIdentidad ( 3, 3 );
	if ( ( VerificarMat ( p_matI3, dI3, 3, 3 ) != BOOL_VAL_CIERTO ) || ( SMatNxMEsDiagonal ( p_matI3 ) != 1 ) )
	{
		printf( "Error caso 2: se esperaba la identidad 3x3\n" );
		iRes = BOOL_VAL_FALSO;
	}
	double dI23 [ 6 ] = { 1.0, 0.0, 0.0, 0.0, 1.0, 0.0 };
	SMatrizNxM * p_matI23 = SMatNxMIdentidad ( 2, 3 );
	if ( VerificarMat ( p_matI23, dI23, 2, 3 ) != BOOL_VAL_CIERTO )
	{
		printf( "Error caso 3: en una 2x3 la diagonal tiene dos unos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ( SMatNxMInicializarCero ( p_matUnos ) != 1 ) || ( MatEsIgual ( SMatNxMX ( p_matUnos, 2, 3 ), 0.0 ) != 1 ) )
	{
		printf( "Error caso 4: InicializarCero deja todo a 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SMatNxMDestruir ( &p_matUnos );
	SMatNxMDestruir ( &p_matI3 );
	SMatNxMDestruir ( &p_matI23 );
	return ( iRes );
}

/* Una fila tiene tantos elementos como columnas, y una columna tantos como
   filas: tambien en matrices no cuadradas. */
static int TestSMatNxMFilasColumnas01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SMatNxMFilasColumnas 01:\n" );

	SMatrizNxM * p_matObj = SMatNxMCrearExt ( 2, 3, M23 );
	double dFila2 [ 3 ] = { 4.0, 5.0, 6.0 };
	SVectorND * p_vecFila = SMatNxMVectorFila ( p_matObj, 2 );
	if ( VerificarVec ( p_vecFila, dFila2, 3 ) != BOOL_VAL_CIERTO )
	{
		printf( "Error caso 1: la fila 2 es ( 4, 5, 6 )\n" );
		iRes = BOOL_VAL_FALSO;
	}
	double dCol3 [ 2 ] = { 3.0, 6.0 };
	SVectorND * p_vecCol = SMatNxMVectorColumna ( p_matObj, 3 );
	if ( VerificarVec ( p_vecCol, dCol3, 2 ) != BOOL_VAL_CIERTO )
	{
		printf( "Error caso 2: la columna 3 es ( 3, 6 )\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( SMatNxMVectorFila ( p_matObj, 3 ) ) || ES_VALIDO ( SMatNxMVectorColumna ( p_matObj, 4 ) ) )
	{
		printf( "Error caso 3: fuera de rango se esperaba nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SVectorND * p_vec3 = SVecNDCrearConValores ( 7.0, 8.0, 9.0 );
	SVectorND * p_vec2 = SVecNDCrearConValores ( 10.0, 11.0 );
	if ( ( SMatNxMEsCompatibleFila ( p_matObj, p_vec3 ) != 1 ) || ( SMatNxMEsCompatibleFila ( p_matObj, p_vec2 ) != 0 ) ||
		 ( SMatNxMEsCompatibleColumna ( p_matObj, p_vec2 ) != 1 ) || ( SMatNxMEsCompatibleColumna ( p_matObj, p_vec3 ) != 0 ) )
	{
		printf( "Error caso 4: en una 2x3 caben filas de 3 y columnas de 2\n" );
		iRes = BOOL_VAL_FALSO;
	}
	double dAsig [ 6 ] = { 7.0, 10.0, 9.0, 4.0, 11.0, 6.0 };
	if ( ( SMatNxMAsignarVectorFila ( p_matObj, 1, p_vec3 ) != 1 ) || ( SMatNxMAsignarVectorColumna ( p_matObj, 2, p_vec2 ) != 1 ) ||
		 ( VerificarMat ( p_matObj, dAsig, 2, 3 ) != BOOL_VAL_CIERTO ) )
	{
		printf( "Error caso 5: tras asignar la fila 1 y la columna 2 se esperaba ( 7, 10, 9 / 4, 11, 6 )\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ( SMatNxMAsignarVectorFila ( p_matObj, 1, p_vec2 ) != 0 ) || ( SMatNxMAsignarVectorColumna ( p_matObj, 1, p_vec3 ) != 0 ) ||
		 ( SMatNxMAsignarVectorFila ( p_matObj, 3, p_vec3 ) != 0 ) || ( VerificarMat ( p_matObj, dAsig, 2, 3 ) != BOOL_VAL_CIERTO ) )
	{
		printf( "Error caso 6: con vectores que no caben o fuera de rango se esperaba 0 y la matriz sin tocar\n" );
		iRes = BOOL_VAL_FALSO;
	}
	double dTras [ 6 ] = { 7.0, 4.0, 10.0, 11.0, 9.0, 6.0 };
	SMatrizNxM * p_matTras = SMatNxMTranspuesta ( p_matObj );
	if ( VerificarMat ( p_matTras, dTras, 3, 2 ) != BOOL_VAL_CIERTO )
	{
		printf( "Error caso 7: la traspuesta de una 2x3 es una 3x2\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SMatNxMDestruir ( &p_matObj );
	SMatNxMDestruir ( &p_matTras );
	SVecNDDestruir ( &p_vecFila );
	SVecNDDestruir ( &p_vecCol );
	SVecNDDestruir ( &p_vec3 );
	SVecNDDestruir ( &p_vec2 );
	return ( iRes );
}

/* De cualquier tamano, no solo 3x3, y con o sin intercambio de filas. */
static int TestSMatNxMDeterminante01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SMatNxMDeterminante 01:\n" );

	double d1 [ 1 ] = { 5.0 };
	double d2 [ 4 ] = { 3.0, 8.0, 4.0, 6.0 };
	double d3 [ 9 ] = { 6.0, 1.0, 1.0, 4.0, -2.0, 5.0, 2.0, 8.0, 7.0 };
	double d4 [ 16 ] = { 1.0, 0.0, 2.0, -1.0, 3.0, 0.0, 0.0, 5.0, 2.0, 1.0, 4.0, -3.0, 1.0, 0.0, 5.0, 0.0 };
	double dSing [ 9 ] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };
	double dPerm [ 4 ] = { 0.0, 1.0, 1.0, 0.0 };
	SMatrizNxM * p_mat1 = SMatNxMCrearExt ( 1, 1, d1 );
	SMatrizNxM * p_mat2 = SMatNxMCrearExt ( 2, 2, d2 );
	SMatrizNxM * p_mat3 = SMatNxMCrearExt ( 3, 3, d3 );
	SMatrizNxM * p_mat4 = SMatNxMCrearExt ( 4, 4, d4 );
	SMatrizNxM * p_matSing = SMatNxMCrearExt ( 3, 3, dSing );
	SMatrizNxM * p_matPerm = SMatNxMCrearExt ( 2, 2, dPerm );
	SMatrizNxM * p_mat23 = SMatNxMCrearExt ( 2, 3, M23 );
	ErrLimpiar ();

	if ( MatEsIgual ( SMatNxMDeterminante ( p_mat1 ), 5.0 ) != 1 )
	{
		printf( "Error caso 1: el determinante de ( 5 ) es 5: %g\n", SMatNxMDeterminante ( p_mat1 ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( MatEsIgual ( SMatNxMDeterminante ( p_mat2 ), -14.0 ) != 1 )
	{
		printf( "Error caso 2: el de la 2x2 es -14: %g\n", SMatNxMDeterminante ( p_mat2 ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( MatEsIgual ( SMatNxMDeterminante ( p_mat3 ), -306.0 ) != 1 )
	{
		printf( "Error caso 3: el de la 3x3 es -306: %g\n", SMatNxMDeterminante ( p_mat3 ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( MatEsIgual ( SMatNxMDeterminante ( p_mat4 ), 30.0 ) != 1 )
	{
		printf( "Error caso 4: el de la 4x4 es 30: %g\n", SMatNxMDeterminante ( p_mat4 ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( MatEsIgual ( SMatNxMDeterminante ( p_matSing ), 0.0 ) != 1 )
	{
		printf( "Error caso 5: el de una singular es 0: %g\n", SMatNxMDeterminante ( p_matSing ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( MatEsIgual ( SMatNxMDeterminante ( p_matPerm ), -1.0 ) != 1 )
	{
		printf( "Error caso 6: con un cero en el primer pivote el determinante es -1: %g\n", SMatNxMDeterminante ( p_matPerm ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ErrHayError () != 0 )
	{
		printf( "Error caso 6b: con matrices cuadradas no deberia quedar error\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ( MatEsIgual ( SMatNxMDeterminante ( p_mat23 ), -1.0 ) != 1 ) || ( MatEsIgual ( SMatNxMDeterminante ( NULL ), -1.0 ) != 1 ) )
	{
		printf( "Error caso 7: sin matriz cuadrada se esperaba -1\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ( ErrHayError () != 1 ) || ( ErrCodigo () != ERR_PARAMETROS ) )
	{
		printf( "Error caso 7b: sin matriz cuadrada deberia quedar ERR_PARAMETROS\n" );
		iRes = BOOL_VAL_FALSO;
	}
	ErrLimpiar ();
	if ( VerificarMat ( p_mat3, d3, 3, 3 ) != BOOL_VAL_CIERTO )
	{
		printf( "Error caso 8: calcular el determinante no deberia cambiar la matriz\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SMatNxMDestruir ( &p_mat1 );
	SMatNxMDestruir ( &p_mat2 );
	SMatNxMDestruir ( &p_mat3 );
	SMatNxMDestruir ( &p_mat4 );
	SMatNxMDestruir ( &p_matSing );
	SMatNxMDestruir ( &p_matPerm );
	SMatNxMDestruir ( &p_mat23 );
	return ( iRes );
}

static int TestSMatNxMAdjuntos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SMatNxMAdjuntos 01:\n" );

	double dA [ 9 ] = { 1.0, 2.0, 3.0, 0.0, 4.0, 5.0, 1.0, 0.0, 6.0 };
	double dCof [ 9 ] = { 24.0, 5.0, -4.0, -12.0, 3.0, 2.0, -2.0, -5.0, 4.0 };
	double dAdj [ 9 ] = { 24.0, -12.0, -2.0, 5.0, 3.0, -5.0, -4.0, 2.0, 4.0 };
	double dB [ 4 ] = { 1.0, 2.0, 3.0, 4.0 };
	double d1 [ 1 ] = { 7.0 };
	SMatrizNxM * p_matA = SMatNxMCrearExt ( 3, 3, dA );
	SMatrizNxM * p_matB = SMatNxMCrearExt ( 2, 2, dB );
	SMatrizNxM * p_mat1 = SMatNxMCrearExt ( 1, 1, d1 );

	int iF = 1;
	while ( iF <= 3 )
	{
		int iC = 1;
		while ( iC <= 3 )
		{
			if ( MatEsIgual ( SMatNxMAdjunto ( p_matA, iF, iC ), dCof [ ( iF - 1 ) * 3 + iC - 1 ] ) != 1 )
			{
				printf( "Error caso 1: el adjunto ( %d, %d ) deberia ser %g: %g\n", iF, iC, dCof [ ( iF - 1 ) * 3 + iC - 1 ], SMatNxMAdjunto ( p_matA, iF, iC ) );
				iRes = BOOL_VAL_FALSO;
			}
			iC = iC + 1;
		}
		iF = iF + 1;
	}
	if ( ( MatEsIgual ( SMatNxMAdjunto ( p_matB, 1, 1 ), 4.0 ) != 1 ) || ( MatEsIgual ( SMatNxMAdjunto ( p_matB, 1, 2 ), -3.0 ) != 1 ) ||
		 ( MatEsIgual ( SMatNxMAdjunto ( p_matB, 2, 1 ), -2.0 ) != 1 ) || ( MatEsIgual ( SMatNxMAdjunto ( p_matB, 2, 2 ), 1.0 ) != 1 ) )
	{
		printf( "Error caso 2: los adjuntos de ( 1, 2 / 3, 4 ) son ( 4, -3 / -2, 1 )\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ( MatEsIgual ( SMatNxMAdjunto ( p_mat1, 1, 1 ), 1.0 ) != 1 ) || ( MatEsIgual ( SMatNxMAdjunto ( p_matA, 4, 1 ), -1.0 ) != 1 ) )
	{
		printf( "Error caso 3: el adjunto de una 1x1 es 1, y fuera de rango -1\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SMatrizNxM * p_matAdj = SMatNxMAdjunta ( p_matA );
	if ( VerificarMat ( p_matAdj, dAdj, 3, 3 ) != BOOL_VAL_CIERTO )
	{
		printf( "Error caso 4: la adjunta es la traspuesta de los adjuntos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SMatNxMDestruir ( &p_matA );
	SMatNxMDestruir ( &p_matB );
	SMatNxMDestruir ( &p_mat1 );
	SMatNxMDestruir ( &p_matAdj );
	return ( iRes );
}

/* La inversa de una matriz no simetrica, y que A * A^-1 es la identidad. */
static int TestSMatNxMInversa01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SMatNxMInversa 01:\n" );

	double dA [ 9 ] = { 1.0, 2.0, 3.0, 0.0, 4.0, 5.0, 1.0, 0.0, 6.0 };
	double dInv [ 9 ] = { 24.0 / 22.0, -12.0 / 22.0, -2.0 / 22.0,
						  5.0 / 22.0, 3.0 / 22.0, -5.0 / 22.0,
						  -4.0 / 22.0, 2.0 / 22.0, 4.0 / 22.0 };
	double dI3 [ 9 ] = { 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0 };
	double dSing [ 9 ] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };
	double dPerm [ 4 ] = { 0.0, 1.0, 1.0, 0.0 };
	SMatrizNxM * p_matA = SMatNxMCrearExt ( 3, 3, dA );
	SMatrizNxM * p_matSing = SMatNxMCrearExt ( 3, 3, dSing );
	SMatrizNxM * p_matPerm = SMatNxMCrearExt ( 2, 2, dPerm );
	SMatrizNxM * p_mat23 = SMatNxMCrearExt ( 2, 3, M23 );

	SMatrizNxM * p_matInv = SMatNxMInversa ( p_matA );
	if ( VerificarMat ( p_matInv, dInv, 3, 3 ) != BOOL_VAL_CIERTO )
	{
		printf( "Error caso 1: no es la inversa esperada\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SMatrizNxM * p_matProd = SMatNxMMultiplicar ( p_matA, p_matInv );
	if ( VerificarMat ( p_matProd, dI3, 3, 3 ) != BOOL_VAL_CIERTO )
	{
		printf( "Error caso 2: A por su inversa deberia ser la identidad\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SMatrizNxM * p_matInvPerm = SMatNxMInversa ( p_matPerm );
	if ( VerificarMat ( p_matInvPerm, dPerm, 2, 2 ) != BOOL_VAL_CIERTO )
	{
		printf( "Error caso 3: la permutacion ( 0, 1 / 1, 0 ) es su propia inversa\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( SMatNxMInversa ( p_matSing ) ) || ES_VALIDO ( SMatNxMInversa ( p_mat23 ) ) || ES_VALIDO ( SMatNxMInversa ( NULL ) ) )
	{
		printf( "Error caso 4: una singular o no cuadrada no tiene inversa\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( VerificarMat ( p_matA, dA, 3, 3 ) != BOOL_VAL_CIERTO )
	{
		printf( "Error caso 5: calcular la inversa no deberia cambiar la matriz\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SMatNxMDestruir ( &p_matA );
	SMatNxMDestruir ( &p_matSing );
	SMatNxMDestruir ( &p_matPerm );
	SMatNxMDestruir ( &p_mat23 );
	SMatNxMDestruir ( &p_matInv );
	SMatNxMDestruir ( &p_matProd );
	SMatNxMDestruir ( &p_matInvPerm );
	return ( iRes );
}

static int TestSMatNxMMultiplicar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SMatNxMMultiplicar 01:\n" );

	double d32 [ 6 ] = { 7.0, 8.0, 9.0, 10.0, 11.0, 12.0 };
	double dProd [ 4 ] = { 58.0, 64.0, 139.0, 154.0 };
	SMatrizNxM * p_mat23 = SMatNxMCrearExt ( 2, 3, M23 );
	SMatrizNxM * p_mat32 = SMatNxMCrearExt ( 3, 2, d32 );

	SMatrizNxM * p_matProd = SMatNxMMultiplicar ( p_mat23, p_mat32 );
	if ( VerificarMat ( p_matProd, dProd, 2, 2 ) != BOOL_VAL_CIERTO )
	{
		printf( "Error caso 1: el producto 2x3 por 3x2 es ( 58, 64 / 139, 154 )\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( SMatNxMMultiplicar ( p_mat23, p_mat23 ) ) || ( SMatNxMPuedeMultiplicar ( p_mat23, p_mat23 ) != 0 ) )
	{
		printf( "Error caso 2: una 2x3 no se puede multiplicar por otra 2x3\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SVectorND * p_vecDer = SVecNDCrearConValores ( 1.0, 0.0, -1.0 );
	SVectorND * p_vecIzq = SVecNDCrearConValores ( 1.0, 2.0 );
	double dMv [ 2 ] = { -2.0, -2.0 };
	double dvM [ 3 ] = { 9.0, 12.0, 15.0 };
	SVectorND * p_vecMv = SMatNxMMultiplicarPorDer ( p_mat23, p_vecDer );
	if ( VerificarVec ( p_vecMv, dMv, 2 ) != BOOL_VAL_CIERTO )
	{
		printf( "Error caso 3: M * ( 1, 0, -1 ) es ( -2, -2 )\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SVectorND * p_vecvM = SMatNxMMultiplicarPorIzq ( p_mat23, p_vecIzq );
	if ( VerificarVec ( p_vecvM, dvM, 3 ) != BOOL_VAL_CIERTO )
	{
		printf( "Error caso 4: ( 1, 2 ) * M es ( 9, 12, 15 )\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( SMatNxMMultiplicarPorDer ( p_mat23, p_vecIzq ) ) || ES_VALIDO ( SMatNxMMultiplicarPorIzq ( p_mat23, p_vecDer ) ) )
	{
		printf( "Error caso 5: con un vector que no encaja se esperaba nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SMatNxMDestruir ( &p_mat23 );
	SMatNxMDestruir ( &p_mat32 );
	SMatNxMDestruir ( &p_matProd );
	SVecNDDestruir ( &p_vecDer );
	SVecNDDestruir ( &p_vecIzq );
	SVecNDDestruir ( &p_vecMv );
	SVecNDDestruir ( &p_vecvM );
	return ( iRes );
}

static int TestSMatNxMSumar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SMatNxMSumar 01:\n" );

	SMatrizNxM * p_matA = SMatNxMCrearExt ( 2, 3, M23 );
	SMatrizNxM * p_matUnos = SMatNxMUnos ( 2, 3 );
	SMatrizNxM * p_mat32 = SMatNxMUnos ( 3, 2 );

	double dSuma [ 6 ] = { 2.0, 3.0, 4.0, 5.0, 6.0, 7.0 };
	if ( ( SMatNxMSumar ( p_matA, p_matUnos ) != 1 ) || ( VerificarMat ( p_matA, dSuma, 2, 3 ) != BOOL_VAL_CIERTO ) )
	{
		printf( "Error caso 1: sumar unos deberia dar ( 2, 3, 4 / 5, 6, 7 )\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ( SMatNxMRestar ( p_matA, p_matUnos ) != 1 ) || ( VerificarMat ( p_matA, M23, 2, 3 ) != BOOL_VAL_CIERTO ) )
	{
		printf( "Error caso 2: restarlos deberia devolver la original\n" );
		iRes = BOOL_VAL_FALSO;
	}
	double dPor [ 6 ] = { -0.5, -1.0, -1.5, -2.0, -2.5, -3.0 };
	if ( ( SMatNxMMultiplicarEscalar ( p_matA, -0.5 ) != 1 ) || ( VerificarMat ( p_matA, dPor, 2, 3 ) != BOOL_VAL_CIERTO ) )
	{
		printf( "Error caso 3: por -0.5 deberia dar ( -0.5, -1, -1.5 / -2, -2.5, -3 )\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ( SMatNxMSumar ( p_matA, p_mat32 ) != 0 ) || ( SMatNxMRestar ( p_matA, p_mat32 ) != 0 ) ||
		 ( SMatNxMAsignar ( p_matA, p_mat32 ) != 0 ) || ( VerificarMat ( p_matA, dPor, 2, 3 ) != BOOL_VAL_CIERTO ) )
	{
		printf( "Error caso 4: con dimensiones distintas se esperaba 0 y la matriz sin tocar\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SMatrizNxM * p_matDup = SMatNxMDuplicar ( p_matA );
	SMatNxMInicializarUnos ( p_matA );
	if ( VerificarMat ( p_matDup, dPor, 2, 3 ) != BOOL_VAL_CIERTO )
	{
		printf( "Error caso 5: el duplicado no deberia cambiar con el original\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SMatNxMDestruir ( &p_matA );
	SMatNxMDestruir ( &p_matUnos );
	SMatNxMDestruir ( &p_mat32 );
	SMatNxMDestruir ( &p_matDup );
	return ( iRes );
}

static int TestSMatNxMEsDiagonal01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SMatNxMEsDiagonal 01:\n" );

	double dDiag [ 4 ] = { 2.0, 1e-9, 0.0, -3.0 };
	double dNoDiag [ 4 ] = { 2.0, 0.1, 0.0, -3.0 };
	SMatrizNxM * p_matDiag = SMatNxMCrearExt ( 2, 2, dDiag );
	SMatrizNxM * p_matNoDiag = SMatNxMCrearExt ( 2, 2, dNoDiag );
	SMatrizNxM * p_mat23 = SMatNxMIdentidad ( 2, 3 );

	if ( SMatNxMEsDiagonal ( p_matDiag ) != 1 )
	{
		printf( "Error caso 1: con 1e-9 fuera de la diagonal es diagonal\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SMatNxMEsDiagonal ( p_matNoDiag ) != 0 )
	{
		printf( "Error caso 2: con 0.1 fuera de la diagonal no lo es\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ( SMatNxMEsDiagonal ( p_mat23 ) != 0 ) || ( SMatNxMEsCuadrada ( p_mat23 ) != 0 ) || ( SMatNxMEsCuadrada ( p_matDiag ) != 1 ) )
	{
		printf( "Error caso 3: una 2x3 no es cuadrada ni diagonal\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SMatNxMDestruir ( &p_matDiag );
	SMatNxMDestruir ( &p_matNoDiag );
	SMatNxMDestruir ( &p_mat23 );
	return ( iRes );
}

static int TestSMatNxMEncapsular01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SMatNxMEncapsular 01:\n" );

	double * p_dBuf = (double *) MemReservar ( 4 * sizeof ( double ) );
	p_dBuf [ 0 ] = 1.0;
	p_dBuf [ 1 ] = 2.0;
	p_dBuf [ 2 ] = 3.0;
	p_dBuf [ 3 ] = 4.0;
	SMatrizNxM * p_matObj = SMatNxMEncapsular ( 2, 2, p_dBuf );
	if ( ( SMatNxMValores ( p_matObj ) != p_dBuf ) || ( MatEsIgual ( SMatNxMX ( p_matObj, 2, 1 ), 3.0 ) != 1 ) )
	{
		printf( "Error caso 1: la matriz encapsulada deberia usar el array que se le da\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( SMatNxMEncapsular ( 2, 2, NULL ) ) || ES_VALIDO ( SMatNxMEncapsular ( 0, 2, p_dBuf ) ) )
	{
		printf( "Error caso 2: sin array o sin filas se esperaba nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SMatNxMDestruir ( &p_matObj );
	return ( iRes );
}



int TestSMatrizNxM ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SMatrizNxM]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSMatNxMCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSMatNxMUnosIdentidad01 () == BOOL_VAL_CIERTO ) &&
			( TestSMatNxMFilasColumnas01 () == BOOL_VAL_CIERTO ) &&
			( TestSMatNxMDeterminante01 () == BOOL_VAL_CIERTO ) &&
			( TestSMatNxMAdjuntos01 () == BOOL_VAL_CIERTO ) &&
			( TestSMatNxMInversa01 () == BOOL_VAL_CIERTO ) &&
			( TestSMatNxMMultiplicar01 () == BOOL_VAL_CIERTO ) &&
			( TestSMatNxMSumar01 () == BOOL_VAL_CIERTO ) &&
			( TestSMatNxMEsDiagonal01 () == BOOL_VAL_CIERTO ) &&
			( TestSMatNxMEncapsular01 () == BOOL_VAL_CIERTO ) )
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
