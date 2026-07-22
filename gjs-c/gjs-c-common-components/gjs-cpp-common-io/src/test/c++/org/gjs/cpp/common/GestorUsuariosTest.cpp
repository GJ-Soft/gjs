#include "CppCommonIo.h"
#include <CppBase.h>




using namespace std;
using namespace org::gjs::cpp::common;




static bool TestGestorUsuarios01 ()
{
	cout << "Test GestorUsuarios 01:" << endl;
	bool bRes = true;

	try
	{
		GestorUsuarios * gestor = new GestorUsuarios();
		if ( gestor->NumUsuarios() != 0 )
		{
			cout << "Error caso 1: NumUsuarios=" << gestor->NumUsuarios() << endl;
			bRes = false;
		}
		if ( gestor->Alta( "Nombre Invalido", "Clavexx" ) )
		{
			cout << "Error caso 1: Usuario invalido" << endl;
			bRes = false;
		}
		if ( gestor->Alta( "Vladimiro", "Clave invalida" ) )
		{
			cout << "Error caso 1: Clave invalida" << endl;
			bRes = false;
		}
		if ( !gestor->Alta( "Vladimiro", "", "vladimiro" ) )
		{
			cout << "Error caso 2: Usuario=Vladimiro" << endl;
			bRes = false;
		}
		if ( !gestor->Alta( "Volodimiro", "patin1", "vladimiro" ) )
		{
			cout << "Error caso 2: Usuario=Volodimir" << endl;
			bRes = false;
		}
		if ( !gestor->Existe( "Vladimiro" ) || !gestor->Existe( "Volodimiro" ) || gestor->Existe( "payaso" ) ||
				gestor->NumUsuarios() != 2 )
		{
			cout << "Error caso 2: NumUsuarios=" << gestor->NumUsuarios() << endl;
			bRes = false;
		}
		if ( bRes )
		{
			if ( 
				 !gestor->Validar( "Vladimiro" ) ||
				 !gestor->Validar( "Volodimiro", "patin1" ) ||
				 gestor->Validar( "Vladimiro", "tetsuo" ) ||
				 gestor->Validar( "Volodimiro", "kaneda" ) ) 
			{
				cout << "Error caso 2: Validacion incorrecta" << endl;
				bRes = false;
			}

			gestor->Baja( "Vladimiro" ); 
			if ( gestor->Existe( "Vladimiro" ) || !gestor->Existe( "Volodimiro" ) ||
					gestor->NumUsuarios() != 1 )
			{
				cout << "Error caso 3: NumUsuarios=" << gestor->NumUsuarios() << endl;
				bRes = false;
			}
			
			gestor->Limpiar();
			if ( gestor->Existe( "Vladimiro" ) || gestor->Existe( "Volodimiro" ) ||
					gestor->NumUsuarios() != 0 )
			{
				cout << "Error caso 4: NumUsuarios=" << gestor->NumUsuarios() << endl;
				bRes = false;
			}
		}
		delete gestor;
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

static bool TestGestorUsuarios02 ()
{
	cout << "Test GestorUsuarios 02:" << endl;
	bool bRes = true;

	try
	{
		GestorUsuarios * gestor = new GestorUsuarios( "../data/vacio.info" );
		if ( gestor->NumUsuarios() != 0 )
		{
			cout << "Error caso 1: NumUsuarios=" << gestor->NumUsuarios() << endl;
			bRes = false;
		}
		delete gestor;
		
		gestor = new GestorUsuarios( "../data/usuarios.info" );
		if ( gestor->NumUsuarios() != 3 )
		{
			cout << "Error caso 2: NumUsuarios=" << gestor->NumUsuarios() << endl;
			bRes = false;
		}
		if ( !gestor->Validar( "vladimiro", "patin1" ) ||
			 !gestor->Validar( "volodimir" ) ||
			 !gestor->Validar( "jarjarbinks", "panagiotas" ) ) 
		{
			cout << "Error caso 2: Validacion incorrecta" << endl;
			cout << "Vladimiro: " << gestor->Validar( "vladimiro", "patin1" ) << endl;
			cout << "Volodimiro: " << gestor->Validar( "volodimir" ) << endl;
			cout << "JarJarBinks " << gestor->Validar( "jarjarbinks", "panagiotas" ) << endl;
			bRes = false;
		}
		if ( ( gestor->Subdirectorio( "vladimiro" ).compare( "vladimir" ) != 0 ) ||
			 ( gestor->Subdirectorio( "volodimir" ).compare( "volodimir" ) != 0 ) ||
			 ( gestor->Subdirectorio( "jarjarbinks" ).compare( "" ) != 0 ) ) 
		{
			cout << "Error caso 2: Directorios incorrectos" << endl;
			bRes = false;
		}
		delete gestor;
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

bool TestGestorUsuarios ()
{
	bool bRes = true;
	cout << endl << ANSI::AMARILLO << "[Test GestorUsuarios]" << ANSI::RESETEAR << endl;
	if ( TestGestorUsuarios01() )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout  << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}
	if ( TestGestorUsuarios02() )
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
