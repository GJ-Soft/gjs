
#if ( defined( _WIN32 ) || defined( _WIN64 ) || defined( _WINRT_DLL ) || defined ( __CYGWIN__ ) )

#include <windows.h>

#include "CommonTypesConfig.h"
#include "WinHerramientas.h"


#include <Excepcion.h>
#include <ToString.h>
#include <Concatenar.h>



using namespace std;


namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {

typedef int(__stdcall *LPFNDLLFUNC1)();

bool DLLEjecutar ( std::string sRutaDLL, std::string sFuncion )
{
	bool bRes = false;
	HINSTANCE hDLL = NULL;
	try
	{
		hDLL = LoadLibrary ( sRutaDLL.c_str() );
		if ( hDLL != NULL )
		{
			LPFNDLLFUNC1 lpfnDllFunc = (LPFNDLLFUNC1) GetProcAddress ( hDLL, sFuncion.c_str() );
			if ( lpfnDllFunc != NULL )
			{
				lpfnDllFunc ();
			}
			else
			{
				throw ( Excepcion ( "Windows", "DLLEjecutar", Concatenar ( "Error al ejecutar la funcion ", sFuncion, " de la la DLL ", sRutaDLL, ": ", ToString ( GetLastError() ) ) ) );
			}
			FreeLibrary( hDLL );
		}
		else
		{
			throw ( Excepcion ( "Windows", "DLLEjecutar", Concatenar ( "Error al cargar la DLL ", sRutaDLL, ": ", ToString ( GetLastError() ) ) ) );
		}
	}
	catch ( ... )
	{
		if ( hDLL != NULL )
		{
			FreeLibrary( hDLL );
		}
		throw ( Excepcion ( "Windows", "DLLEjecutar", Concatenar ( "Error inesperado al ejecutar la funcion ", sFuncion, " de la la DLL ", sRutaDLL ) ) );
	}

	return ( bRes );
}

 			}
		}
	}
}

#endif
