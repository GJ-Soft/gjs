#include <CTest.h>


#define  NOMBRE_MODULO 			"UtilesTest"



/* Prueba los verificadores de UtilesTest comprobando que dejan *iRes intacto
   cuando la comprobacion pasa y lo ponen a 0 cuando falla. */
static int CasoUtilesTest_01 ()
{
	int iCaso = 1;
	int iRes;
	int iValor = 7;

	printf( "Test CasoUtilesTest_01:\n" );

	iRes = 1;	VerificarValorLit ( "lit-igual", "abc", "abc", &iRes );
	if ( iRes != 1 ) { iCaso = 0; }
	iRes = 1;	VerificarValorLit ( "lit-distinto", "abc", "xyz", &iRes );
	if ( iRes != 0 ) { iCaso = 0; }
	iRes = 1;	VerificarValorLit ( "lit-longitud", "abc", "ab", &iRes );
	if ( iRes != 0 ) { iCaso = 0; }

	iRes = 1;	VerificarValorEntero ( "entero-igual", 5, 5, &iRes );
	if ( iRes != 1 ) { iCaso = 0; }
	iRes = 1;	VerificarValorEntero ( "entero-distinto", 5, 6, &iRes );
	if ( iRes != 0 ) { iCaso = 0; }

	iRes = 1;	VerificarValorEnteroLargo ( "largo-igual", 100L, 100L, &iRes );
	if ( iRes != 1 ) { iCaso = 0; }
	iRes = 1;	VerificarValorEnteroLargo ( "largo-distinto", 100L, 200L, &iRes );
	if ( iRes != 0 ) { iCaso = 0; }

	iRes = 1;	VerificarValorRealDoble ( "real-igual", 2.5, 2.5, &iRes );
	if ( iRes != 1 ) { iCaso = 0; }

	iRes = 1;	VerificarEsCierto ( "cierto-1", 1, &iRes );
	if ( iRes != 1 ) { iCaso = 0; }
	iRes = 1;	VerificarEsCierto ( "cierto-0", 0, &iRes );
	if ( iRes != 0 ) { iCaso = 0; }

	iRes = 1;	VerificarEsFalso ( "falso-0", 0, &iRes );
	if ( iRes != 1 ) { iCaso = 0; }
	iRes = 1;	VerificarEsFalso ( "falso-1", 1, &iRes );
	if ( iRes != 0 ) { iCaso = 0; }

	iRes = 1;	VerificarNoEsNulo ( "nonulo-ptr", &iValor, &iRes );
	if ( iRes != 1 ) { iCaso = 0; }
	iRes = 1;	VerificarNoEsNulo ( "nonulo-nulo", NULL, &iRes );
	if ( iRes != 0 ) { iCaso = 0; }

	iRes = 1;	VerificarEsNulo ( "nulo-nulo", NULL, &iRes );
	if ( iRes != 1 ) { iCaso = 0; }
	iRes = 1;	VerificarEsNulo ( "nulo-ptr", &iValor, &iRes );
	if ( iRes != 0 ) { iCaso = 0; }

	return ( iCaso );
}


int TestUtilesTest ()
{
	int iRes;

	STest * testModulo = STestCrear ( NOMBRE_MODULO );
	STestNuevoCaso ( testModulo, "CasoUtilesTest_01", CasoUtilesTest_01 );

	iRes = STestEjecutar ( testModulo );
	STestDestruir ( &testModulo );
	return ( iRes );
}
