#include "CppTestConfig.h"
#include "UtilesTest.h"



using namespace std;
using namespace org::gjs::cpp::common;
using namespace org::gjs::cpp::common::log;


namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {
				namespace test
				{

void VerificarValor ( const string & sInfoCaso, const string & sResultado, const string & sEsperado, bool & bRes )
{
	LogInfo ( Concatenar( "    Caso: [", sInfoCaso, "]: Resultado: [", sResultado, "]" ) );
	if ( sResultado.size () != sEsperado.size () )
	{
		LogError ( Concatenar( "    -> longitud incorrecta (esperada ", ToString( sEsperado.size () ), ")" ) );
		bRes = false;
	}	
	if ( sResultado != sEsperado )
	{
		LogError ( Concatenar( "    -> valor inesperado (esperado [", sEsperado, "])" ) );
		bRes = false;
	}	
}

void VerificarValor ( const string & sInfoCaso, const string & sResultado, const char * p_cEsperado, bool & bRes )
{
	VerificarValor ( sInfoCaso, sResultado, ToString ( p_cEsperado ), bRes );
}

void VerificarValor ( const string & sInfoCaso, const char * p_cResultado, const char * p_cEsperado, bool & bRes )
{
	VerificarValor ( sInfoCaso, ToString ( p_cResultado ), ToString ( p_cEsperado ), bRes );
}

void VerificarValor ( const string & sInfoCaso, long lResultado, long lEsperado, bool & bRes )
{
	LogInfo ( Concatenar( "    Caso: [", sInfoCaso, "]: Resultado: [", ToString ( lResultado ), "]" ) );
	if ( lResultado != lEsperado )
	{
		LogError ( "    -> valor inesperado" );
		bRes = false;
	}	
}

void VerificarValor ( const string & sInfoCaso, long lResultado, int iEsperado, bool & bRes )	
{
	VerificarValor ( sInfoCaso, lResultado, (long) iEsperado, bRes );
}

void VerificarValor ( const string & sInfoCaso, int iResultado, int iEsperado, bool & bRes )		
{
	VerificarValor ( sInfoCaso, (long) iResultado, (long) iEsperado, bRes );
}

void VerificarValor ( const string & sInfoCaso, bool bResultado, bool bEsperado, bool & bRes )		
{
	LogInfo ( Concatenar( "    Caso: [", sInfoCaso, "]: Resultado: [", ToString ( bResultado ), "]" ) );
	if ( bResultado != bEsperado )
	{
		LogError ( "    -> valor inesperado" );
		bRes = false;
	}	
}

void VerificarValor ( const string & sInfoCaso, double dResultado, double dEsperado, bool & bRes )
{
	LogInfo ( Concatenar( "    Caso: [", sInfoCaso, "]: Resultado: [", ToString ( dResultado ), "]" ) );
	if ( ! EsIgual ( dResultado, dEsperado ) )
	{
		LogError ( "    -> valor inesperado" );
		bRes = false;
	}	
}

void VerificarValor ( const string & sInfoCaso, float fResultado, float fEsperado, bool & bRes )		
{
	VerificarValor ( sInfoCaso, (double) fResultado, (double) fEsperado, bRes );
}

void VerificarValor ( const string & sInfoCaso, const wstring & sResultado, const wstring & sEsperado, bool & bRes )
{
	LogInfo ( Concatenar( "    Caso: [", sInfoCaso, "]: Resultado: [", ToString ( sResultado ), "]" ) );
	if ( sResultado.size () != sEsperado.size () )
	{
		LogError ( Concatenar( "    -> longitud incorrecta (esperada ", ToString( sEsperado.size () ), ")" ) );
		bRes = false;
	}	
	if ( sResultado != sEsperado )
	{
		LogError ( Concatenar( "    -> valor inesperado (esperado [", ToString( sEsperado ), "])" ) );
		bRes = false;
	}	
}

void VerificarValor ( const string & sInfoCaso, const wstring & sResultado, const wchar_t * p_cEsperado, bool & bRes )	
{
	VerificarValor ( sInfoCaso, sResultado, wstring ( p_cEsperado ), bRes );
}

void VerificarValor ( const string & sInfoCaso, const wchar_t * p_cResultado, const wchar_t * p_cEsperado, bool & bRes )
{
	VerificarValor ( sInfoCaso, wstring( p_cResultado ), wstring ( p_cEsperado ), bRes );
}

void VerificarValor ( const string & sInfoCaso, IComparable & objResultado, IComparable & objEsperado, bool & bRes )		
{
	LogInfo ( Concatenar( "    Caso: [", sInfoCaso, "]: Resultado: [", ToString ( objResultado.Base() ), "]" ) );
	if ( objResultado != objEsperado )
	{
		LogError ( Concatenar( "    -> valor inesperado (esperado [", ToString( objEsperado.Base() ), "])" ) );
		bRes = false;
	}	
}

void VerificarValor ( const string & sInfoCaso, IComparable * objResultado, IComparable * objEsperado, bool & bRes )		
{
	if ( ( objResultado != NULL ) && ( objEsperado != NULL ) )
	{
		VerificarValor ( sInfoCaso, *objResultado, *objEsperado, bRes );
	}
	else
	{
		LogInfo ( Concatenar( "    Caso: [", sInfoCaso, "]: Resultado: [", ( (objResultado == NULL) ? "NULO" : "NO NULO" ), "]" ) );
		if ( objResultado != objEsperado )
		{
			LogError ( Concatenar( "    -> valor inesperado (esperado [", ( (objEsperado == NULL) ? "NULO" : "NO NULO" ), "])" ) );
			bRes = false;
		}	
	}	
}

void VerificarEsCierto ( const string & sInfoCaso, bool bResultado, bool & bRes )
{
	LogInfo ( Concatenar( "    Caso: [", sInfoCaso, "]: Resultado: [", ToString ( bResultado ), "]" ) );
	if ( !bResultado ) 
	{
		LogError ( Concatenar( "    -> valor inesperado (esperado [", ToString ( true ), "])" ) );
		bRes = false;
	}	
}

void VerificarEsFalso ( const string & sInfoCaso, bool bResultado, bool & bRes )
{
	LogInfo ( Concatenar( "    Caso: [", sInfoCaso, "]: Resultado: [", ToString ( bResultado ), "]" ) );
	if ( bResultado ) 
	{
		LogError ( Concatenar( "    -> valor inesperado (esperado [", ToString ( false ), "])" ) );
		bRes = false;
	}	
}

void VerificarEsNulo ( const string & sInfoCaso, void * p_vResultado, bool & bRes )
{
	LogInfo ( Concatenar( "    Caso: [", sInfoCaso, "]: Resultado: [", ( (p_vResultado == NULL) ? "NULO" : "NO NULO" ), "]" ) );
	if ( p_vResultado != NULL ) 
	{
		LogError ( Concatenar( "    -> valor inesperado (esperado [NULO])" ) );
		bRes = false;
	}	
}

void VerificarNoEsNulo ( const string & sInfoCaso, void * p_vResultado, bool & bRes )
{
	LogInfo ( Concatenar( "    Caso: [", sInfoCaso, "]: Resultado: [", ( (p_vResultado == NULL) ? "NULO" : "NO NULO" ), "]" ) );
	if ( p_vResultado == NULL ) 
	{
		LogError ( Concatenar( "    -> valor inesperado (esperado [NO NULO])" ) );
		bRes = false;
	}	
}

void VerificarExistenciaFichero ( const string & sRuta, bool & bRes )
{
	string sRes = "Existe";
	if ( !ExisteFichero( sRuta ) )
	{
		sRes = "No existe";
		bRes = false;
	}
	LogInfo ( Concatenar( "    Fichero: [", sRuta, "]: ", sRes ) );
}

void VerificarFichero ( const string & sRuta, int iLineasEsperadas, bool & bRes )
{
	LogInfo ( Concatenar( "    Fichero: [", sRuta, "]: " ) );
	vector<string> vecContenido = LeerFichero( sRuta );
	if ( vecContenido.size () != iLineasEsperadas )
	{
		LogError ( Concatenar( "    -> numero de lineas incorrecto( ", ToString( vecContenido.size () ), ")" )  );
		bRes = false;
	}	
}

void VerificarFichero ( const string & sRuta, vector<string> & vecLineas, bool & bRes )
{
	LogInfo ( Concatenar( "    Fichero: [", sRuta, "]: " ) );
	vector<string> vecContenido = LeerFichero( sRuta );
	if ( vecContenido.size () != vecLineas.size () )
	{
		LogError ( Concatenar( "    -> numero de lineas incorrecto(", ToString( vecContenido.size () ), ")" )  );
		bRes = false;
	}	
	else
	{
		for ( int i = 0; i < vecContenido.size(); i = i + 1 )
		{
			string sLinea = vecContenido[ i ];
			string sEsperada = vecLineas[ i ];
			if ( sLinea != sEsperada )
			{
				LogError ( Concatenar( "    -> linea ", ToString( i + 1 ), " incorrecta: [", sLinea ,"] - [", sEsperada ,"]" ) );
				bRes = false;
			}
		}
	}	
}

void VerificarFichero ( const string & sRuta, const char * p_cEsperado, bool & bRes )
{
	LogInfo ( Concatenar( "    Fichero: [", sRuta, "]: " ) );
	vector<string> vecContenido = LeerFichero( sRuta );
	string sContenido = ToString( vecContenido );
	string sEsperado = string( p_cEsperado );
	if ( sContenido != sEsperado )
	{
		LogError ( Concatenar( "    -> contenido incorrecta: [", sContenido ,"]" ) );
		bRes = false;
	}
}

void VerificarFichero ( const string & sRuta, const string & sRutaEsperado, bool & bRes )
{
	LogInfo ( Concatenar( "    Fichero: [", sRuta, "]: " ) );
	if ( !FicherosIguales ( sRuta, sRutaEsperado ) )
	{
		LogError ( Concatenar( "    -> contenido diferente del de: [", sRutaEsperado ,"]" ) );
		bRes = false;
	}
}

				}
 			}
		}
	}
}
