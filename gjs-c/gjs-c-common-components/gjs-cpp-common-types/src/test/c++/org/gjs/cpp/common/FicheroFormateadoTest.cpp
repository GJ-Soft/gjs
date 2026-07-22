#include "CppCommonTypes.h"




using namespace std;
using namespace org::gjs::cpp::common;




static bool TestFicheroFormateado01 ()
{
	cout << "Test FicheroFormateado 01:" << endl;
	bool bRes = true;

	FicheroTSV * fichero = NULL;
	try
	{
		fichero = new FicheroTSV();
		if ( fichero->NumLineas() != 0 ) 
		{
			cout << "Error caso 1" << endl;
			bRes = false;
		}
		fichero->Cargar( "../data/valores-vacio.tsv" ); 
		if ( fichero->NumLineas() != 0 ) 
		{
			cout << "Error caso 2" << endl;
			bRes = false;
		}
		fichero->Cargar( "../data/valores.tsv" ); 
		if ( fichero->NumLineas() != 3 ) 
		{
			cout << "Error caso 3: Lineas=" << fichero->NumLineas() << endl;
			bRes = false;
		}
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
	try
	{
		vector<string> vecLinea = fichero->Linea( -1 );
		bRes = false;
	}
	catch ( Excepcion & ex )
	{
		cout << "Recibida excepcion :" << ex.what () << endl;
		bRes = true;
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
	try
	{
		vector<string> vecLinea = fichero->Linea( 10 );
		bRes = false;
	}
	catch ( Excepcion & ex )
	{
		cout << "Recibida excepcion :" << ex.what () << endl;
		bRes = true;
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
	try
	{
		string sCampo = fichero->Campo( 1, -1 );
		bRes = false;
	}
	catch ( Excepcion & ex )
	{
		cout << "Recibida excepcion :" << ex.what () << endl;
		bRes = true;
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
	try
	{
		string sCampo = fichero->Campo( 1, 7 );
		bRes = false;
	}
	catch ( Excepcion & ex )
	{
		cout << "Recibida excepcion :" << ex.what () << endl;
		bRes = true;
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
	try
	{
		if ( ( fichero->NumCamposLinea( 0 ) != 2 ) ||
			 ( fichero->NumCamposLinea( 1 ) != 2 ) ||
			 ( fichero->NumCamposLinea( 2 ) != 2 )  ) 
		{
			cout << "Error caso 3: Campos de lineas incorrectos 1" << endl;
			bRes = false;
		}
		if ( ( fichero->Campo( 0, 0 ).compare( "atributo1" ) != 0 ) || ( fichero->Campo( 0, 1 ).compare( "valor1" ) != 0 ) ||
			 ( fichero->Campo( 1, 0 ).compare( "atributo2" ) != 0 ) || ( fichero->Campo( 1, 1 ).compare( "115" ) != 0 ) ||
			 ( fichero->Campo( 2, 0 ).compare( "atributo3" ) != 0 ) || ( fichero->Campo( 2, 1 ).compare( "0,01" ) != 0 ) ) 
		{
			cout << "Error caso 3: Valores incorrectos 1" << endl;
			cout << "[" << fichero->Campo( 0, 0 ) << "]-[" << fichero->Campo( 0, 1 ) << "]" << endl;
			cout << "[" << fichero->Campo( 1, 0 ) << "]-[" << fichero->Campo( 1, 1 ) << "]" << endl;
			cout << "[" << fichero->Campo( 2, 0 ) << "]-[" << fichero->Campo( 2, 1 ) << "]" << endl;
			bRes = false;
		}
		vector<string> vecLinea1 = fichero->Linea( 0 );
		vector<string> vecLinea2 = fichero->Linea( 1 );
		vector<string> vecLinea3 = fichero->Linea( 2 );
		if ( ( vecLinea1.size() != 2 ) ||
			 ( vecLinea2.size() != 2 ) ||
			 ( vecLinea3.size() != 2 )  ) 
		{
			cout << "Error caso 3: Campos de lineas incorrectos 2" << endl;
			bRes = false;
		}
		if ( ( fichero->Campo( 0, 0 ).compare( vecLinea1[ 0 ] ) != 0 ) || ( fichero->Campo( 0, 1 ).compare( vecLinea1[ 1 ] ) != 0 ) ||
			 ( fichero->Campo( 1, 0 ).compare( vecLinea2[ 0 ] ) != 0 ) || ( fichero->Campo( 1, 1 ).compare( vecLinea2[ 1 ] ) != 0 ) ||
			 ( fichero->Campo( 2, 0 ).compare( vecLinea3[ 0 ] ) != 0 ) || ( fichero->Campo( 2, 1 ).compare( vecLinea3[ 1 ] ) != 0 ) ) 
		{
			cout << "Error caso 3: Valores incorrectos 2" << endl;
			bRes = false;
		}
		delete fichero;
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

static bool TestFicheroFormateado02 ()
{
	cout << "Test FicheroFormateado 02:" << endl;
	bool bRes = true;

	FicheroCSV * fichero = NULL;
	try
	{
		fichero = new FicheroCSV();
		if ( fichero->NumLineas() != 0 ) 
		{
			cout << "Error caso 1" << endl;
			bRes = false;
		}
		fichero->Cargar( "../data/valores-vacio.csv" ); 
		if ( fichero->NumLineas() != 0 ) 
		{
			cout << "Error caso 2" << endl;
			bRes = false;
		}
		fichero->Cargar( "../data/valores.csv" ); 
		if ( fichero->NumLineas() != 3 ) 
		{
			cout << "Error caso 3: Lineas=" << fichero->NumLineas() << endl;
			bRes = false;
		}
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
	try
	{
		vector<string> vecLinea = fichero->Linea( -1 );
		bRes = false;
	}
	catch ( Excepcion & ex )
	{
		cout << "Recibida excepcion :" << ex.what () << endl;
		bRes = true;
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
	try
	{
		vector<string> vecLinea = fichero->Linea( 10 );
		bRes = false;
	}
	catch ( Excepcion & ex )
	{
		cout << "Recibida excepcion :" << ex.what () << endl;
		bRes = true;
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
	try
	{
		string sCampo = fichero->Campo( 1, -1 );
		bRes = false;
	}
	catch ( Excepcion & ex )
	{
		cout << "Recibida excepcion :" << ex.what () << endl;
		bRes = true;
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
	try
	{
		string sCampo = fichero->Campo( 1, 7 );
		bRes = false;
	}
	catch ( Excepcion & ex )
	{
		cout << "Recibida excepcion :" << ex.what () << endl;
		bRes = true;
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
	try
	{
		if ( ( fichero->NumCamposLinea( 0 ) != 2 ) ||
			 ( fichero->NumCamposLinea( 1 ) != 2 ) ||
			 ( fichero->NumCamposLinea( 2 ) != 3 )  ) 
		{
			cout << "Error caso 3: Campos de lineas incorrectos 1" << endl;
			cout << "Linea 1: " << fichero->NumCamposLinea( 0 ) << endl;
			cout << "Linea 2: " << fichero->NumCamposLinea( 1 ) << endl;
			cout << "Linea 3: " << fichero->NumCamposLinea( 2 ) << endl;
			bRes = false;
		}
		if ( ( fichero->Campo( 0, 0 ).compare( "atributo1" ) != 0 ) || ( fichero->Campo( 0, 1 ).compare( "valor1" ) != 0 ) ||
			 ( fichero->Campo( 1, 0 ).compare( "atributo2" ) != 0 ) || ( fichero->Campo( 1, 1 ).compare( "115" ) != 0 ) ||
			 ( fichero->Campo( 2, 0 ).compare( "atributo3" ) != 0 ) || ( fichero->Campo( 2, 1 ).compare( "0" ) != 0 ) ||
			 ( fichero->Campo( 2, 2 ).compare( "01" ) != 0 ) ) 
		{
			cout << "Error caso 3: Valores incorrectos 1" << endl;
			cout << "[" << fichero->Campo( 0, 0 ) << "]-[" << fichero->Campo( 0, 1 ) << "]" << endl;
			cout << "[" << fichero->Campo( 1, 0 ) << "]-[" << fichero->Campo( 1, 1 ) << "]" << endl;
			cout << "[" << fichero->Campo( 2, 0 ) << "]-[" << fichero->Campo( 2, 1 ) << "]-[" << fichero->Campo( 2, 2 ) << "]" << endl;
			bRes = false;
		}
		vector<string> vecLinea1 = fichero->Linea( 0 );
		vector<string> vecLinea2 = fichero->Linea( 1 );
		vector<string> vecLinea3 = fichero->Linea( 2 );
		if ( ( vecLinea1.size() != 2 ) ||
			 ( vecLinea2.size() != 2 ) ||
			 ( vecLinea3.size() != 3 )  ) 
		{
			cout << "Error caso 3: Campos de lineas incorrectos 2" << endl;
			bRes = false;
		}
		if ( ( fichero->Campo( 0, 0 ).compare( vecLinea1[ 0 ] ) != 0 ) || ( fichero->Campo( 0, 1 ).compare( vecLinea1[ 1 ] ) != 0 ) ||
			 ( fichero->Campo( 1, 0 ).compare( vecLinea2[ 0 ] ) != 0 ) || ( fichero->Campo( 1, 1 ).compare( vecLinea2[ 1 ] ) != 0 ) ||
			 ( fichero->Campo( 2, 0 ).compare( vecLinea3[ 0 ] ) != 0 ) || ( fichero->Campo( 2, 1 ).compare( vecLinea3[ 1 ] ) != 0 ) ||
			 ( fichero->Campo( 2, 2 ).compare( vecLinea3[ 2 ] ) != 0 ) ) 
		{
			cout << "Error caso 3: Valores incorrectos 2" << endl;
			bRes = false;
		}
		delete fichero;
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

static bool TestFicheroFormateado03 ()
{
	cout << "Test FicheroFormateado 03:" << endl;
	bool bRes = true;

	FicheroTSV * fichero = NULL;
	try
	{
		fichero = new FicheroTSV();
		fichero->Cargar( "../data/valores2.tsv" ); 
		if ( fichero->NumLineas() != 3 ) 
		{
			cout << "Error caso 3: Lineas=" << fichero->NumLineas() << endl;
			bRes = false;
		}
		if ( ( fichero->NumCamposLinea( 0 ) != 3 ) ||
			 ( fichero->NumCamposLinea( 1 ) != 3 ) ||
			 ( fichero->NumCamposLinea( 2 ) != 3 )  ) 
		{
			cout << "Error caso 3: Campos de lineas incorrectos 1" << endl;
			cout << "Linea 1: " << fichero->NumCamposLinea( 0 ) << endl;
			cout << "Linea 2: " << fichero->NumCamposLinea( 1 ) << endl;
			cout << "Linea 3: " << fichero->NumCamposLinea( 2 ) << endl;
			bRes = false;
		}
		else
		{
			if ( ( fichero->Campo( 0, 0 ).compare( "atributo1" ) != 0 ) || ( fichero->Campo( 0, 1 ).compare( "valor11" ) != 0 ) || ( fichero->Campo( 0, 2 ).compare( "valor12" ) != 0 ) ||
				 ( fichero->Campo( 1, 0 ).compare( "atributo2" ) != 0 ) || ( fichero->Campo( 1, 1 ).compare( "" ) != 0 ) || ( fichero->Campo( 1, 2 ).compare( "valor22" ) != 0 ) ||
				 ( fichero->Campo( 2, 0 ).compare( "atributo3" ) != 0 ) || ( fichero->Campo( 2, 1 ).compare( "valor31" ) != 0 ) || ( fichero->Campo( 2, 2 ).compare( "" ) != 0 ) ) 
			{
				cout << "Error caso 3: Valores incorrectos 1" << endl;
				cout << "[" << fichero->Campo( 0, 0 ) << "]-[" << fichero->Campo( 0, 1 ) << "]-[" << fichero->Campo( 0, 2 ) << "]" << endl;
				cout << "[" << fichero->Campo( 1, 0 ) << "]-[" << fichero->Campo( 1, 1 ) << "]-[" << fichero->Campo( 1, 2 ) << "]" << endl;
				cout << "[" << fichero->Campo( 2, 0 ) << "]-[" << fichero->Campo( 2, 1 ) << "]-[" << fichero->Campo( 2, 2 ) << "]" << endl;
				bRes = false;
			}
		}
		delete fichero;
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

bool TestFicheroFormateado ()
{
	bool bRes = true;
	cout << endl << ANSI::AMARILLO << "[Test FicheroFormateado]" << ANSI::RESETEAR << endl;
	if ( TestFicheroFormateado01() )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout  << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}
	if ( TestFicheroFormateado02() )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout  << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}
	if ( TestFicheroFormateado03() )
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
