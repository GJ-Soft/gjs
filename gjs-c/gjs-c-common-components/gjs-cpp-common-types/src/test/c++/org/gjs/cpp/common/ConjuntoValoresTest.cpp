#include "CppCommonTypes.h"




using namespace std;
using namespace org::gjs::cpp::common;




static bool TestConjuntoValores01 ()
{
	cout << "Test ConjuntoValores 01:" << endl;
	bool bRes = true;

	try
	{
		ConjuntoValores * conjunto = new ConjuntoValores();
		if ( !conjunto->EsValido() || 
			 ( conjunto->NumValores() != 0 ) )
		{
			cout << "Error caso 1: Valida=" << ToString( conjunto->EsValido() ) << "; NumValores=" << conjunto->NumValores() << endl;
			bRes = false;
		}
		conjunto->InsertarValor( "Nombre", new Valor( "Vladimiro" ) ); 
		Valor * valor1 = conjunto->getValor( "Nombre" ); 
		Valor * valor2 = conjunto->getValor( "Arlaukas" ); 
		if ( !conjunto->EsValido() || 
			 ( conjunto->NumValores() != 1 ) ||
			 ( valor1 == NULL ) || 
			 ( valor2 != NULL ) )
		{
			cout << "Error caso 2: Valida=" << ToString( conjunto->EsValido() ) << "; NumValores=" << conjunto->NumValores() << endl;
			bRes = false;
		}

		conjunto->InsertarValor( "Apellido", "Putin" ); 
		conjunto->InsertarValor( "Contador", 0 ); 
		conjunto->InsertarValor( "Acumulado", -37.02 ); 
		conjunto->InsertarValor( "TieneLorako", false ); 
		valor1 = conjunto->getValor( "Nombre" ); 
		valor2 = conjunto->getValor( "Apellido" ); 
		Valor * valor3 = conjunto->getValor( "Contador" ); 
		Valor * valor4 = conjunto->getValor( "Acumulado" ); 
		Valor * valor5 = conjunto->getValor( "TieneLorako" ); 
		if ( !conjunto->EsValido() || 
			 ( conjunto->NumValores() != 5 ) ||
			 ( valor1 == NULL ) || 
			 ( valor2 == NULL ) ||
			 ( valor3 == NULL ) || 
			 ( valor4 == NULL )  || 
			 ( valor5 == NULL ) )
		{
			cout << "Error caso 3: Valida=" << ToString( conjunto->EsValido() ) << "; NumValores=" << conjunto->NumValores() << endl;
			cout << "\tValor1=" << ( ( valor1 != NULL ) ? valor1->getValor() : "NULO" ) << endl;
			cout << "\tValor2=" << ( ( valor2 != NULL ) ? valor2->getValor() : "NULO" ) << endl;
			cout << "\tValor3=" << ( ( valor3 != NULL ) ? valor3->getValor() : "NULO" ) << endl;
			cout << "\tValor4=" << ( ( valor4 != NULL ) ? valor4->getValor() : "NULO" ) << endl;
			cout << "\tValor5=" << ( ( valor5 != NULL ) ? valor5->getValor() : "NULO" ) << endl;
			bRes = false;
		}
		if ( bRes )
		{
			if ( ( valor1->getValor().compare( "Vladimiro" ) != 0 ) || 
				 ( valor2->getValor().compare( "Putin" ) != 0 ) ||
				 ( valor3->getValor().compare( "0" ) != 0 ) || 
				 ! valor4->getValor().starts_with( "-37.02" ) || 
				 ( valor5->getValor().compare( "Falso" ) != 0 ) )
			{
				cout << "Error caso 3b: [" << valor1->getValor() << "]-[" << valor2->getValor() << "]-[" << 
							valor3->getValor() << "]-[" << valor4->getValor() << "]-[" << valor5->getValor() << "]" << endl;
				bRes = false;
			}
		}

		conjunto->EliminarValor( "Acumulado" ); 
		valor1 = conjunto->getValor( "Nombre" ); 
		valor2 = conjunto->getValor( "Apellido" ); 
		valor3 = conjunto->getValor( "Contador" ); 
		valor4 = conjunto->getValor( "Acumulado" ); 
		valor5 = conjunto->getValor( "TieneLorako" ); 
		if ( !conjunto->EsValido() || 
			 ( conjunto->NumValores() != 4 ) ||
			 ( valor1 == NULL ) || 
			 ( valor2 == NULL ) ||
			 ( valor3 == NULL ) || 
			 ( valor4 != NULL )  || 
			 ( valor5 == NULL ) )
		{
			cout << "Error caso 4: Valida=" << ToString( conjunto->EsValido() ) << "; NumValores=" << conjunto->NumValores() << endl;
			cout << "\tValor1=" << ( ( valor1 != NULL ) ? valor1->getValor() : "NULO" ) << endl;
			cout << "\tValor2=" << ( ( valor2 != NULL ) ? valor2->getValor() : "NULO" ) << endl;
			cout << "\tValor3=" << ( ( valor3 != NULL ) ? valor3->getValor() : "NULO" ) << endl;
			cout << "\tValor4=" << ( ( valor4 != NULL ) ? valor4->getValor() : "NULO" ) << endl;
			cout << "\tValor5=" << ( ( valor5 != NULL ) ? valor5->getValor() : "NULO" ) << endl;
			bRes = false;
		}
		if ( bRes )
		{
			if ( ( valor1->getValor().compare( "Vladimiro" ) != 0 ) || 
				 ( valor2->getValor().compare( "Putin" ) != 0 ) ||
				 ( valor3->getValor().compare( "0" ) != 0 ) || 
				 ( valor5->getValor().compare( "Falso" ) != 0 ) )
			{
				cout << "Error caso 4b: [" << valor1->getValor() << "]-[" << valor2->getValor() << "]-[" << 
							valor3->getValor() << "]-[" << valor5->getValor() << "]" << endl;
				bRes = false;
			}
		}
		
		conjunto->LimpiarValores();
		if ( !conjunto->EsValido() || 
			 ( conjunto->NumValores() != 0 ) )
		{
			cout << "Error caso 5: Valida=" << ToString( conjunto->EsValido() ) << "; NumValores=" << conjunto->NumValores() << endl;
			bRes = false;
		}
		delete conjunto;
	}
	catch ( exception & ex )
	{
		cout << "Se ha producido una excepcion :" << ex.what () << endl;
		bRes = false;
	}
	catch ( ... )
	{
		cout << "Excepcion indefinida" << endl;
		bRes = false;
	}
	return( bRes );
}

static bool TestConjuntoValores02 ()
{
	cout << "Test ConjuntoValores 02:" << endl;
	bool bRes = true;

	try
	{
		ConjuntoValores * conjunto = new ConjuntoValores( { "Nombre", "Apellido", "Contador", "Acumulado" }, false );
		Valor * valor1 = conjunto->getValor( "Nombre" ); 
		Valor * valor2 = conjunto->getValor( "Apellido" ); 
		Valor * valor3 = conjunto->getValor( "Contador" ); 
		Valor * valor4 = conjunto->getValor( "Acumulado" );
 		if ( !conjunto->EsValido() || 
			 ( conjunto->NumValores() != 4 ) ||
			 ( valor1 == NULL )||
			 ( valor2 == NULL )||
			 ( valor3 == NULL )||
			 ( valor4 == NULL ) )
		{
			cout << "Error caso 1: Valida=" << ToString( conjunto->EsValido() ) << "; NumValores=" << conjunto->NumValores() << endl;
			bRes = false;
		}
		if ( bRes )
		{
			if ( !valor1->EsNulo() || 
				 !valor2->EsNulo()||
				  !valor3->EsNulo() || 
				  !valor4->EsNulo() )
			{
				cout << "Error caso 1b: [" << valor1->getValor() << "]-[" << valor2->getValor() << "]-[" << 
							valor3->getValor() << "]-[" << valor4->getValor() << "]" << endl;
				bRes = false;
			}
		}
		conjunto->getValor( "Nombre" )->setValor( "Vladimiro" ); 
		conjunto->getValor( "Apellido" )->setValor( "Putin" ); 
		conjunto->getValor( "Contador" )->setValor( 0 ); 
		conjunto->getValor( "Acumulado" )->setValor( -37.02 ); 
		if ( ( valor1->getValor().compare( "Vladimiro" ) != 0 ) || 
			 ( valor2->getValor().compare( "Putin" ) != 0 ) ||
			 ( valor3->getValor().compare( "0" ) != 0 ) || 
			 ! valor4->getValor().starts_with( "-37.02" ) )
		{
			cout << "Error caso 2: [" << valor1->getValor() << "]-[" << valor2->getValor() << "]-[" << 
						valor3->getValor() << "]-[" << valor4->getValor() << "]" << endl;
			bRes = false;
		}
		conjunto->EliminarValor( "Acumulado" ); 
		if ( !conjunto->EsValido() || 
			 ( conjunto->NumValores() != 4 ) )
		{
			cout << "Error caso 2: Valida=" << ToString( conjunto->EsValido() ) << "; NumValores=" << conjunto->NumValores() << endl;
			bRes = false;
		}
		
		conjunto->LimpiarValores();
		if ( !conjunto->EsValido() || 
			 ( conjunto->NumValores() != 4 ) )
		{
			cout << "Error caso 3: Valida=" << ToString( conjunto->EsValido() ) << "; NumValores=" << conjunto->NumValores() << endl;
			bRes = false;
		}
		delete conjunto;
	}
	catch ( exception & ex )
	{
		cout << "Se ha producido una excepcion :" << ex.what () << endl;
		bRes = false;
	}
	catch ( ... )
	{
		cout << "Excepcion indefinida" << endl;
		bRes = false;
	}
	return( bRes );
}

static bool TestConjuntoValores03 ()
{
	cout << "Test ConjuntoValores 03:" << endl;
	bool bRes = true;

	try
	{
		ConjuntoValores * conjunto = new ConjuntoValores( "../../test-classes/data/valores-vacio.tsv" );
		if ( conjunto->NumValores() != 0 )
		{
			cout << "Error caso 1: NumValores=" << conjunto->NumValores() << endl;
			bRes = false;
		}
		delete conjunto;
		
		conjunto = new ConjuntoValores( "../../test-classes/data/valores.tsv" );
		if ( conjunto->NumValores() != 3 )
		{
			cout << "Error caso 2: NumValores=" << conjunto->NumValores() << endl;
			bRes = false;
		}
		if ( ( conjunto->getValor( "atributo1" )->getValor().compare( "valor1" ) != 0 ) ||
			 ( conjunto->getValor( "atributo2" )->getValor().compare( "115" )!= 0 ) ||
			 ( conjunto->getValor( "atributo3" )->getValor().compare( "0,01" ) != 0 ) ) 
		{
			cout << "Error caso 2: Valores incorrectos" << endl;
			bRes = false;
		}
		delete conjunto;
	}
	catch ( exception & ex )
	{
		cout << "Se ha producido una excepcion :" << ex.what () << endl;
		bRes = false;
	}
	catch ( ... )
	{
		cout << "Excepcion indefinida" << endl;
		bRes = false;
	}
	return( bRes );
}


bool TestConjuntoValores ()
{
	bool bRes = true;
	cout << endl << ANSI::AMARILLO << "[Test ConjuntoValores]" << ANSI::RESETEAR << endl;
	if ( TestConjuntoValores01() )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout  << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}
	if ( TestConjuntoValores02() )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout  << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}
	if ( TestConjuntoValores03() )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout  << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}
	cout << ANSI::AMARILLO << "[Fin]" << ANSI::RESETEAR << endl;	
	return ( bRes );
}
