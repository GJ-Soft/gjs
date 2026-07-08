#include "CommonIoConfig.h"

#include "URI.h"



using namespace std;
using namespace org::gjs::cpp::common;


namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {

URI::URI()
{
}

URI::URI( const string & sURI )
{
	setURI( sURI );
}

URI::URI( const string & sURL, const string & sURN )
{
	setURI( sURL, sURN );
}

URI::~URI()
{
	LimpiarParametros();
}

string URI::getProtocolo()
{
	return( sProtocolo );
}

string URI::getDominio()
{
	return( sDominio );
}

string URI::getPuerto()
{
	return( sPuerto );
}

string URI::getRuta()
{
	return( sRuta );
}

const vector<string> & URI::getParametros()
{
	return( mapParametros.getKeys() );
}

void URI::setProtocolo( const string & valor )
{
	sProtocolo = valor;
}

void URI::setDominio( const string & valor )
{
	sDominio = valor;
}

void URI::setPuerto( const string & valor )
{
	sPuerto = valor;
}

void URI::setRuta( const string & valor )
{
	sRuta = valor;
}

void URI::setParametros( const string & valor )
{
	LimpiarParametros();
	string sParametros = Trim( valor );
	if ( EmpiezaPor( valor, "?" ) )
	{
		sParametros = sParametros.substr( 1 );
	}
	vector<string> vecParametros = Separar( sParametros, { "&" } );
	for ( string sParametro : vecParametros )
	{
		size_t pos = sParametro.find( "=" );
		if ( pos != string::npos )
		{
			string sNombre = sParametro.substr( 0, pos );
			string sValor = sParametro.substr( pos + 1 );
			addParametro( sNombre, sValor);
		}
	}
}

bool URI::ExisteParametro( const string & sNombre )
{
	return( mapParametros.exists( sNombre ) );
}

string URI::getValorParametro( const string & sNombre )
{
	string sRes( "" );
	try
	{
		sRes = mapParametros[ sNombre ];
	}
	catch( ... )
	{
	}
	return( sRes );
}

void URI::EliminarParametro( const string & sNombre )
{
	mapParametros.erase( sNombre );
}

int URI::NumParametros()
{
	return ( mapParametros.size() );
}

void URI::LimpiarParametros()
{
	mapParametros.clear();
}

void URI::addParametro( const string & sNombre, const string & sValor )
{
	mapParametros.push_back( sNombre, sValor );
}

string URI::getURL()
{
	string sDireccion = sDominio;
	if ( EsNatural( sPuerto ) )
	{
		sDireccion = Concatenar( sDominio, ":", sPuerto );
	}
	string sURL = Concatenar( sDireccion );
	if ( sProtocolo.size() > 0 ) 
	{
		sURL = Concatenar( sProtocolo, "://", sURL );
	}
	return( sURL );
}

string URI::getURN()
{
	string sParametros = "";
	if ( mapParametros.size() > 0 )
	{
		bool bIni = true;
		sParametros = "?";
		for ( const string & sNombre : mapParametros.getKeys() )
		{
			if ( !bIni )
			{
				sParametros = Concatenar( sParametros, "&" );
			}
			sParametros = Concatenar( sParametros, sNombre, "=", mapParametros[ sNombre ] );	
			bIni = false;
		}
	}
	string sURN;
	if ( sRuta.size() > 0 ) 
	{
		sURN = Concatenar( "/", sRuta );
	}
	sURN = Concatenar( sURN, sParametros ); 
	return( sURN );
}

string URI::toString()
{
	return( Concatenar( getURL(), getURN() ) );
}

void URI::setURI( const string & sURI )
{
	sProtocolo = "";
	sPuerto = "";
	sDominio = "";
	sRuta = "";
	LimpiarParametros();
	string sCadenaURI = Trim( sURI );  
	if ( EsURI( sCadenaURI ) )
	{
		size_t posProc = 0;
		size_t pos1 = sCadenaURI.find( "://" );
		if ( pos1 != string::npos )
		{
			sProtocolo = sCadenaURI.substr( 0, pos1 );
			posProc = pos1 + 3;
		}
		size_t pos2 = sCadenaURI.find( ":", posProc );
		size_t pos3 = sCadenaURI.find( "/", posProc );
		size_t pos4 = sCadenaURI.find( "?", posProc );
		if ( pos2 != string::npos )
		{
			sDominio = sCadenaURI.substr( posProc, pos2 - posProc  );
			if ( pos3 != string::npos )
			{
				sPuerto = sCadenaURI.substr( pos2 + 1, pos3 - pos2 - 1 );
				posProc = pos3 + 1;
			}
			else if ( pos4 != string::npos )
			{
				sPuerto = sCadenaURI.substr( pos2 + 1, pos4 - pos2 - 1 );
				posProc = pos4 + 1;
			}
			else
			{
				sPuerto = sCadenaURI.substr( pos2 + 1 );
				posProc = string::npos;
			}
		}
		else if ( pos3 != string::npos )
		{
			sDominio = sCadenaURI.substr( posProc, pos3 - posProc );
		}
		else if ( pos4 != string::npos )
		{
			sDominio = sCadenaURI.substr( posProc, pos4 - posProc );
		}		
		else 
		{
			sDominio = sCadenaURI.substr( posProc );
		}		
		if ( pos3 != string::npos )
		{
			if ( pos4 != string::npos )
			{
				sRuta = sCadenaURI.substr( pos3 + 1, pos4 - pos3 - 1 );
			}		
			else 
			{
				sRuta = sCadenaURI.substr( pos3 + 1 );
			}
		}
		if ( pos4 != string::npos )
		{
			string sParametros = sCadenaURI.substr( pos4 + 1 );
			setParametros( sParametros );
		}
		if ( ( sProtocolo.size() == 0 ) && EmpiezaPor( sDominio, "www." ) )
		{
			sProtocolo = "http";
		}
	}
	else
	{
		cout << "NO ES URI: [" << sURI << "]" << endl;
	}
}

void URI::setURI( const string & sURL, const string & sURN )
{
	string sURLAux = sURL;
	string sURNAux = sURN;
	if ( TerminaPor( sURL, "/" ) )
	{
		sURLAux = sURL.substr( 0, sURL.size() - 1 );
	}
	if ( EmpiezaPor( sURN, "/" ) )
	{
		sURNAux = sURN.substr( 1 );
	}
	setURI( Concatenar( sURLAux, "/", sURNAux ) );
}

bool URI::EsValido()
{
	string sURI = toString();
	return ( EsURI( sURI ) && mapParametros.isValid() );
}

 			}
		}
	}
}
