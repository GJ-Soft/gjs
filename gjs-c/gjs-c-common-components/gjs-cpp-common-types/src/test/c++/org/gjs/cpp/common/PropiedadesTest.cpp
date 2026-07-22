#include "CppCommonTypes.h"




using namespace std;
using namespace org::gjs::cpp::common;




static bool TestPropiedades01 ()
{
	cout << "Test Propiedades 01:" << endl;
	bool bRes = true;

	try
	{
		Propiedades * propiedades = new Propiedades();
		if ( propiedades->getPropiedades().size() != 0 )
		{
			cout << "Error caso 1: NumPropiedades=" << propiedades->getPropiedades().size() << endl;
			bRes = false;
		}
		propiedades->setPropiedad( "Nombre", "Vladimiro" ); 
		if ( propiedades->getPropiedades().size() != 1 )
		{
			cout << "Error caso 2: NumPropiedades=" << propiedades->getPropiedades().size() << endl;
			bRes = false;
		}
		
		try
		{
			string valor = propiedades->getPropiedad( "Nombre" ); 
			if ( valor.compare( "Vladimiro" ) != 0 ) 
			{
				cout << "Error caso 2: Valor erroneo=[" << valor << "]" << endl;
				bRes = false;
			}
		}
		catch( NoEncontradoExcepcion & ex )
		{
			cout << "Error caso 2: Excepcion inesperada: " << ex.what() << endl;
			bRes = false;
		}

		try
		{
			string valor = propiedades->getPropiedad( "Apellido" ); 
			cout << "Error caso 2: Se esperaba excepcion" << endl;
			bRes = false;
		}
		catch( NoEncontradoExcepcion & ex )
		{
		}
		
 		propiedades->setPropiedad( "Apellido", "Putin" ); 
		if ( propiedades->getPropiedades().size() != 2 )
		{
			cout << "Error caso 3: NumPropiedades=" << propiedades->getPropiedades().size() << endl;
			bRes = false;
		}
		
		try
		{
			string valor = propiedades->getPropiedad( "Apellido" ); 
			if ( valor.compare( "Putin" ) != 0 ) 
			{
				cout << "Error caso 3: Valor erroneo=[" << valor << "]" << endl;
				bRes = false;
			}
		}
		catch( NoEncontradoExcepcion & ex )
		{
			cout << "Error caso 3: Excepcion inesperada: " << ex.what() << endl;
			bRes = false;
		}
		
		propiedades->EliminarPropiedad( "Nombre" ); 
		if ( propiedades->getPropiedades().size() != 1 )
		{
			cout << "Error caso 4: NumPropiedades=" << propiedades->getPropiedades().size() << endl;
			bRes = false;
		}
		
		try
		{
			string valor = propiedades->getPropiedad( "Nombre" ); 
			cout << "Error caso 4: Se esperaba excepcion" << endl;
			bRes = false;
		}
		catch( NoEncontradoExcepcion & ex )
		{
		}
		
		delete propiedades;
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

static bool TestPropiedades02 ()
{
	cout << "Test Propiedades 02:" << endl;
	bool bRes = true;
	string sFic1 ( "../data/ejemplo-vacio.properties" );
	string sFic2 ( "../data/ejemplo.properties" );
	string sFic3 ( "../data/inexistente.properties" );

	try
	{
		Propiedades * propiedades = new Propiedades( sFic1 );
		if ( propiedades->getPropiedades().size() != 0 )
		{
			cout << "Error caso 1: NumPropiedades=" << propiedades->getPropiedades().size() << endl;
			bRes = false;
		}
		if ( propiedades->Cargar( sFic3 ) )
		{
			cout << "Error caso 2: No deberia haber cargado el fichero" << endl;
			bRes = false;
		}
		if ( propiedades->getPropiedades().size() != 0 )
		{
			cout << "Error caso 2: NumPropiedades=" << propiedades->getPropiedades().size() << endl;
			bRes = false;
		}
		if ( propiedades->Cargar( sFic2 ) )
		{
			cout << "Error caso 3: No deberia haber cargado el fichero" << endl;
			bRes = false;
		}
		if ( propiedades->getPropiedades().size() != 4 )
		{
			cout << "Error caso 3: NumPropiedades=" << propiedades->getPropiedades().size() << endl;
			bRes = false;
		}
		try
		{
			string valor1 = propiedades->getPropiedad( "propiedad1" ); 
			string valor2 = propiedades->getPropiedad( "propiedad2" ); 
			string valor3 = propiedades->getPropiedad( "propiedad3" ); 
			string valor4 = propiedades->getPropiedad( "propiedad4" ); 
			if ( ( valor1.compare( "1500" ) != 0 ) ||
					( valor2.compare( "Volodimir Zelensky" ) != 0 ) ||
					( valor3.compare( "105.7" ) != 0 ) ||
					( valor4.compare( "" ) != 0 ) )
			{
				cout << "Error caso 3: Valores erroneos: [" << valor1 << "]-[" << valor2 << "]-[" << valor3 << "]-[" << valor4 << "]" << endl;
				bRes = false;
			}
		}
		catch( NoEncontradoExcepcion & ex )
		{
			cout << "Error caso 3: " << ex.what() << endl;
			bRes = false;
		}
		delete propiedades;
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

static bool TestPropiedades03 ()
{
	cout << "Test Propiedades 03:" << endl;
	bool bRes = true;
	string sFic1 ( "../results/ejemplo-guardado.properties" );

	try
	{
		Propiedades * propiedades = new Propiedades();
		propiedades->setPropiedad( "Nombre", "Volodimir" );
		propiedades->setPropiedad( "Apellido", "Zelensky" );
		propiedades->setPropiedad( "Motivo", "Invasión de Ucrania" );
		if ( ! propiedades->Guardar( sFic1 ) )
		{
			cout << "Error al guardar el fichero " << endl;
			bRes = false;
		}
		vector<string> lisRecuperado = LeerFichero ( sFic1 );
		if ( lisRecuperado.size() == 3 )
		{
			if ( ( lisRecuperado[ 0 ].compare( "Nombre = Volodimir" ) != 0 ) ||
					( lisRecuperado[ 1 ].compare( "Apellido = Zelensky" ) != 0 ) ||
					( lisRecuperado[ 2 ].compare( "Motivo = \"Invasión de Ucrania\"" ) != 0 ) )
			{
				cout << "Contenido erroneo: [" << lisRecuperado[ 0 ] << "]-[" << lisRecuperado[ 2 ] << "]" << endl;
				bRes = false;
			}
		}
		else
		{
			cout << "Numero de lineas incorrecto: " << lisRecuperado.size() << endl;
			bRes = false;
		}
		delete propiedades;
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

bool TestPropiedades ()
{
	bool bRes = true;
	cout << endl << ANSI::AMARILLO << "[Test Propiedades]" << ANSI::RESETEAR << endl;
	if ( TestPropiedades01() )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout  << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}
	if ( TestPropiedades02() )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout  << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}
	if ( TestPropiedades03() )
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
