#include <CppTest.h>

#include <iostream>


using namespace std;
using namespace org::gjs::cpp::common;
using namespace org::gjs::cpp::common::test;



extern bool TestCasoTest ();
extern bool TestCasoTestAislado ();
extern bool TestTest ();
extern bool TestUtilesTest ();
extern bool TestBancoTests ();
extern bool TestContextoTest ();
extern bool TestEjemplo1 ();
extern bool TestEjemplo2 ();


int main ( int argc, char * argv[] )
{
	int iRes = 0;
	EntInicializar ( true, "Test", 1, 0 );
	EstablecerManejadorInterrupcionesDefecto ();

	BancoTests * p_banTests = new BancoTests ();
	p_banTests->NuevoTest ( "UtilesTestTest", TestUtilesTest );
	p_banTests->NuevoTest ( "CasoTestTest", TestCasoTest );
	p_banTests->NuevoTest ( "CasoTestAisladoTest", TestCasoTestAislado );
	p_banTests->NuevoTest ( "TestTest", TestTest );
	p_banTests->NuevoTest ( "BancoTestsTest", TestBancoTests );
	p_banTests->NuevoTest ( "ContextoTestTest", TestContextoTest );
	p_banTests->NuevoTest ( "Ejemplo1Test", TestEjemplo1 );
	p_banTests->NuevoTest ( "Ejemplo2Test", TestEjemplo2 );
	string sTest ( "null" );
	if ( argc > 1 )
	{
		sTest = argv[ 1 ];
	}
	if ( p_banTests->Ejecutar ( sTest ) )
	{
		iRes = 0;
	}
	else
	{
		iRes = -1;
	}
	delete p_banTests;
	EntFinalizar ();
	return ( iRes );
}
