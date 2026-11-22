#include "Base.h"

#include "SMatrizCuadradaND.h"
#include "CalculoOperaciones.h"

/* Los valores esperados se calcularon aparte, con fracciones exactas. */



static int VerificarMat ( SMatrizCuadradaND * p_matObj, const double * p_dEsperados, int iDims )
{
	int iRes = BOOL_VAL_CIERTO;

	if ( SMatNDDim ( p_matObj ) != iDims )
	{
		printf( "  Verificacion: se esperaba dimension %d: %d\n", iDims, SMatNDDim ( p_matObj ) );
		iRes = BOOL_VAL_FALSO;
	}
	int iF = 1;
	while ( ( iF <= iDims ) && ( iRes == BOOL_VAL_CIERTO ) )
	{
		int iC = 1;
		while ( ( iC <= iDims ) && ( iRes == BOOL_VAL_CIERTO ) )
		{
			double dEsp = p_dEsperados [ ( iF - 1 ) * iDims + iC - 1 ];
			if ( MatEsIgual ( SMatNDX ( p_matObj, iF, iC ), dEsp ) != 1 )
			{
				printf( "  Verificacion: en ( %d, %d ) se esperaba %g: %g\n", iF, iC, dEsp, SMatNDX ( p_matObj, iF, iC ) );
				iRes = BOOL_VAL_FALSO;
			}
			iC = iC + 1;
		}
		iF = iF + 1;
	}
	return ( iRes );
}

static const double A3 [ 9 ] = { 1.0, 2.0, 3.0,
								 0.0, 4.0, 5.0,
								 1.0, 0.0, 6.0 };

static int TestSMatNDCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SMatNDCrear 01:\n" );

	double dCeros [ 4 ] = { 0.0 };
	SMatrizCuadradaND * p_matObj = SMatNDCrear ( 2 );
	if ( ( SMatNDEsValida ( p_matObj ) != 1 ) || ( VerificarMat ( p_matObj, dCeros, 2 ) != BOOL_VAL_CIERTO ) )
	{
		printf( "Error caso 1: se esperaba una 2x2 valida de ceros\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( SMatNDCrear ( 0 ) ) || ES_VALIDO ( SMatNDCrearExt ( 2, NULL ) ) )
	{
		printf( "Error caso 2: sin dimension o sin valores se esperaba nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	double dUnos [ 4 ] = { 1.0, 1.0, 1.0, 1.0 };
	double dI2 [ 4 ] = { 1.0, 0.0, 0.0, 1.0 };
	SMatrizCuadradaND * p_matUnos = SMatNDUnos ( 2 );
	SMatrizCuadradaND * p_matI2 = SMatNDIdentidad ( 2 );
	if ( ( VerificarMat ( p_matUnos, dUnos, 2 ) != BOOL_VAL_CIERTO ) || ( VerificarMat ( p_matI2, dI2, 2 ) != BOOL_VAL_CIERTO ) )
	{
		printf( "Error caso 3: Unos rellena con unos e Identidad da la identidad\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ( SMatNDEstablecerX ( p_matObj, 2, 2, 5.5 ) != 1 ) || ( SMatNDEstablecerX ( p_matObj, 3, 1, 1.0 ) != 0 ) ||
		 ( MatEsIgual ( SMatNDX ( p_matObj, 2, 2 ), 5.5 ) != 1 ) )
	{
		printf( "Error caso 4: las posiciones van de 1 a 2\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SMatNDDestruir ( &p_matObj );
	SMatNDDestruir ( &p_matUnos );
	SMatNDDestruir ( &p_matI2 );
	if ( ES_VALIDO ( p_matObj ) || ( SMatNDEsValida ( NULL ) != 0 ) || ( SMatNDDim ( NULL ) != 0 ) )
	{
		printf( "Error caso 5: tras destruir se esperaba nulo, y la nula no es valida\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

/* Encapsular solo acepta matrices cuadradas, y se queda con ellas. */
static int TestSMatNDEncapsular01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SMatNDEncapsular 01:\n" );

	SMatrizNxM * p_matCuad = SMatNxMCrearExt ( 3, 3, A3 );
	SMatrizNxM * p_mat23 = SMatNxMCrear ( 2, 3 );
	SMatrizCuadradaND * p_matObj = SMatNDEncapsular ( p_matCuad );
	if ( ( SMatNDMatrizNxM ( p_matObj ) != p_matCuad ) || ( VerificarMat ( p_matObj, A3, 3 ) != BOOL_VAL_CIERTO ) )
	{
		printf( "Error caso 1: deberia envolver la matriz que se le da\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( SMatNDEncapsular ( p_mat23 ) ) || ES_VALIDO ( SMatNDEncapsular ( NULL ) ) )
	{
		printf( "Error caso 2: con una matriz no cuadrada o nula se esperaba nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SMatrizCuadradaND * p_matI3 = SMatNDIdentidad ( 3 );
	if ( ( SMatNDAsignarNxM ( p_matI3, p_matCuad ) != 1 ) || ( VerificarMat ( p_matI3, A3, 3 ) != BOOL_VAL_CIERTO ) ||
		 ( SMatNDAsignarNxM ( p_matI3, p_mat23 ) != 0 ) )
	{
		printf( "Error caso 3: AsignarNxM copia de una 3x3 y falla con una 2x3\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SMatNDDestruir ( &p_matObj );
	SMatNDDestruir ( &p_matI3 );
	SMatNxMDestruir ( &p_mat23 );
	return ( iRes );
}

static int TestSMatNDCalculo01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SMatNDCalculo 01:\n" );

	double dAdj [ 9 ] = { 24.0, -12.0, -2.0, 5.0, 3.0, -5.0, -4.0, 2.0, 4.0 };
	double dInv [ 9 ] = { 24.0 / 22.0, -12.0 / 22.0, -2.0 / 22.0,
						  5.0 / 22.0, 3.0 / 22.0, -5.0 / 22.0,
						  -4.0 / 22.0, 2.0 / 22.0, 4.0 / 22.0 };
	double dTras [ 9 ] = { 1.0, 0.0, 1.0, 2.0, 4.0, 0.0, 3.0, 5.0, 6.0 };
	double dI3 [ 9 ] = { 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0 };
	double dSing [ 4 ] = { 1.0, 2.0, 2.0, 4.0 };
	SMatrizCuadradaND * p_matA = SMatNDCrearExt ( 3, A3 );
	SMatrizCuadradaND * p_matSing = SMatNDCrearExt ( 2, dSing );

	if ( ( MatEsIgual ( SMatNDDeterminante ( p_matA ), 22.0 ) != 1 ) || ( MatEsIgual ( SMatNDDeterminante ( p_matSing ), 0.0 ) != 1 ) )
	{
		printf( "Error caso 1: los determinantes son 22 y 0: %g, %g\n", SMatNDDeterminante ( p_matA ), SMatNDDeterminante ( p_matSing ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ( MatEsIgual ( SMatNDAdjunto ( p_matA, 2, 1 ), -12.0 ) != 1 ) || ( MatEsIgual ( SMatNDAdjunto ( p_matA, 3, 2 ), -5.0 ) != 1 ) )
	{
		printf( "Error caso 2: los adjuntos ( 2, 1 ) y ( 3, 2 ) son -12 y -5\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SMatrizCuadradaND * p_matAdj = SMatNDAdjunta ( p_matA );
	SMatrizCuadradaND * p_matInv = SMatNDInversa ( p_matA );
	SMatrizCuadradaND * p_matTras = SMatNDTranspuesta ( p_matA );
	SMatrizCuadradaND * p_matProd = SMatNDMultiplicar ( p_matInv, p_matA );
	if ( VerificarMat ( p_matAdj, dAdj, 3 ) != BOOL_VAL_CIERTO )
	{
		printf( "Error caso 3: no es la adjunta esperada\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( VerificarMat ( p_matInv, dInv, 3 ) != BOOL_VAL_CIERTO )
	{
		printf( "Error caso 4: no es la inversa esperada\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( VerificarMat ( p_matTras, dTras, 3 ) != BOOL_VAL_CIERTO )
	{
		printf( "Error caso 5: no es la traspuesta esperada\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ( VerificarMat ( p_matProd, dI3, 3 ) != BOOL_VAL_CIERTO ) || ( SMatNDEsDiagonal ( p_matProd ) != 1 ) )
	{
		printf( "Error caso 6: la inversa por A deberia ser la identidad\n" );
		iRes = BOOL_VAL_FALSO;
	}
	ErrLimpiar ();
	if ( MatEsIgual ( SMatNDDeterminante ( NULL ), -1.0 ) != 1 )
	{
		printf( "Error caso 6b: el determinante de la nula deberia ser -1\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ( ErrHayError () != 1 ) || ( ErrCodigo () != ERR_PARAMETROS ) )
	{
		printf( "Error caso 6c: el determinante de la nula deberia dejar ERR_PARAMETROS\n" );
		iRes = BOOL_VAL_FALSO;
	}
	ErrLimpiar ();
	if ( ES_VALIDO ( SMatNDInversa ( p_matSing ) ) || ES_VALIDO ( SMatNDInversa ( NULL ) ) )
	{
		printf( "Error caso 7: una singular o nula no tiene inversa\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SMatNDDestruir ( &p_matA );
	SMatNDDestruir ( &p_matSing );
	SMatNDDestruir ( &p_matAdj );
	SMatNDDestruir ( &p_matInv );
	SMatNDDestruir ( &p_matTras );
	SMatNDDestruir ( &p_matProd );
	return ( iRes );
}

static int TestSMatNDOperaciones01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SMatNDOperaciones 01:\n" );

	double dB [ 4 ] = { 1.0, 2.0, 3.0, 4.0 };
	SMatrizCuadradaND * p_matB = SMatNDCrearExt ( 2, dB );
	SMatrizCuadradaND * p_matI2 = SMatNDIdentidad ( 2 );
	SMatrizCuadradaND * p_matI3 = SMatNDIdentidad ( 3 );

	double dSuma [ 4 ] = { 2.0, 2.0, 3.0, 5.0 };
	if ( ( SMatNDSumar ( p_matB, p_matI2 ) != 1 ) || ( VerificarMat ( p_matB, dSuma, 2 ) != BOOL_VAL_CIERTO ) )
	{
		printf( "Error caso 1: B + I deberia ser ( 2, 2 / 3, 5 )\n" );
		iRes = BOOL_VAL_FALSO;
	}
	double dPor [ 4 ] = { 2.0, 4.0, 6.0, 8.0 };
	if ( ( SMatNDRestar ( p_matB, p_matI2 ) != 1 ) || ( SMatNDMultiplicarEscalar ( p_matB, 2.0 ) != 1 ) ||
		 ( VerificarMat ( p_matB, dPor, 2 ) != BOOL_VAL_CIERTO ) )
	{
		printf( "Error caso 2: ( B + I - I ) * 2 deberia ser ( 2, 4 / 6, 8 )\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ( SMatNDSumar ( p_matB, p_matI3 ) != 0 ) || ( SMatNDEsCompatible ( p_matB, p_matI3 ) != 0 ) ||
		 ( SMatNDAsignar ( p_matB, p_matI3 ) != 0 ) || ES_VALIDO ( SMatNDMultiplicar ( p_matB, p_matI3 ) ) )
	{
		printf( "Error caso 3: con dimensiones distintas se esperaba 0 o nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SVectorND * p_vec = SVecNDCrearConValores ( 1.0, -1.0 );
	SVectorND * p_vec3 = SVecNDCrearConValores ( 1.0, -1.0, 0.0 );
	SVectorND * p_vecDer = SMatNDMultiplicarPorDer ( p_matB, p_vec );
	SVectorND * p_vecIzq = SMatNDMultiplicarPorIzq ( p_matB, p_vec );
	if ( ( MatEsIgual ( SVecNDX ( p_vecDer, 1 ), -2.0 ) != 1 ) || ( MatEsIgual ( SVecNDX ( p_vecDer, 2 ), -2.0 ) != 1 ) )
	{
		printf( "Error caso 4: ( 2, 4 / 6, 8 ) * ( 1, -1 ) es ( -2, -2 )\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ( MatEsIgual ( SVecNDX ( p_vecIzq, 1 ), -4.0 ) != 1 ) || ( MatEsIgual ( SVecNDX ( p_vecIzq, 2 ), -4.0 ) != 1 ) )
	{
		printf( "Error caso 5: ( 1, -1 ) * ( 2, 4 / 6, 8 ) es ( -4, -4 )\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ( SMatNDEsVectorCompatible ( p_matB, p_vec ) != 1 ) || ( SMatNDEsVectorCompatible ( p_matB, p_vec3 ) != 0 ) ||
		 ES_VALIDO ( SMatNDMultiplicarPorDer ( p_matB, p_vec3 ) ) )
	{
		printf( "Error caso 6: en una 2x2 solo encajan vectores de 2\n" );
		iRes = BOOL_VAL_FALSO;
	}
	double dFilas [ 4 ] = { 1.0, -1.0, 6.0, 8.0 };
	SVectorND * p_vecCol = SMatNDVectorColumna ( p_matB, 2 );
	if ( ( SMatNDAsignarVectorFila ( p_matB, 1, p_vec ) != 1 ) || ( VerificarMat ( p_matB, dFilas, 2 ) != BOOL_VAL_CIERTO ) ||
		 ( MatEsIgual ( SVecNDX ( p_vecCol, 1 ), 4.0 ) != 1 ) || ( MatEsIgual ( SVecNDX ( p_vecCol, 2 ), 8.0 ) != 1 ) )
	{
		printf( "Error caso 7: filas y columnas como en SMatrizNxM\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SMatrizCuadradaND * p_matDup = SMatNDDuplicar ( p_matB );
	SMatNDInicializarCero ( p_matB );
	if ( ( VerificarMat ( p_matDup, dFilas, 2 ) != BOOL_VAL_CIERTO ) || ( MatEsIgual ( SMatNDX ( p_matB, 2, 2 ), 0.0 ) != 1 ) )
	{
		printf( "Error caso 8: el duplicado no deberia cambiar con el original\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SMatNDDestruir ( &p_matB );
	SMatNDDestruir ( &p_matI2 );
	SMatNDDestruir ( &p_matI3 );
	SMatNDDestruir ( &p_matDup );
	SVecNDDestruir ( &p_vec );
	SVecNDDestruir ( &p_vec3 );
	SVecNDDestruir ( &p_vecDer );
	SVecNDDestruir ( &p_vecIzq );
	SVecNDDestruir ( &p_vecCol );
	return ( iRes );
}



int TestSMatrizCuadradaND ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SMatrizCuadradaND]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSMatNDCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSMatNDEncapsular01 () == BOOL_VAL_CIERTO ) &&
			( TestSMatNDCalculo01 () == BOOL_VAL_CIERTO ) &&
			( TestSMatNDOperaciones01 () == BOOL_VAL_CIERTO ) )
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
