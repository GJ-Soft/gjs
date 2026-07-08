#include "CommonIoConfig.h"

#include "Comando.h"



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

Comando::Comando()
{
}

Comando::Comando( const string & _sComando, const initializer_list<string> & lisArgumentos )
{
	Asignar( _sComando, lisArgumentos );
}

Comando::Comando( const string & sExpresion )
{
	Procesar( sExpresion );
}

Comando::~Comando()
{
	Inicializar();
}


bool Comando::EsValido()
{
	bool bRes = EsToken( sComando );
	for ( string & sArg : vecArgumentos )
	{
		bRes = bRes && !sArg.empty();
	}
	return ( bRes );
}

const string & Comando::getComando()
{
	return( sComando );
}

void Comando::setComando( const string & sValor )
{
	sComando = sValor;
}

bool Comando::isComando( const string & sValor )
{
	return( sComando.compare( sValor ) == 0 );
}

int Comando::NumArgumentos() const
{
	return( vecArgumentos.size() );
}

const string & Comando::getArgumento( int iArg )
{
	if ( ( iArg >= 0 ) && ( iArg < vecArgumentos.size() ) )
	{
		return( vecArgumentos[ iArg ] );
	}
	return( CADENA_VACIA );
}

void Comando::addArgumento( const string & sArgumento )
{
	vecArgumentos.push_back( sArgumento );
}

void Comando::Inicializar()
{
	sComando.clear();
	vecArgumentos.clear();	
}

void Comando::InicializarArgumentos()
{
	vecArgumentos.clear();	
}

void Comando::Asignar( const string & _sComando, const initializer_list<string> & lisArgumentos )
{
	Inicializar();
	setComando( _sComando );
	for ( const string & sArg : lisArgumentos )
	{
		addArgumento( sArg );
	}	
}

void Comando::Procesar( const string & sExpresion )
{
	Inicializar();
	vector<string> vecCampos = Separar( Limpiar( sExpresion ) );
	if ( vecCampos.size() > 0 )
	{
		setComando( vecCampos[ 0 ] );
		for ( int iArg = 1; iArg < vecCampos.size(); iArg = iArg + 1 )
		{
			addArgumento( vecCampos [ iArg ] );
		}
	}
}

string Comando::toString()
{
	try
	{
		ostringstream conv;

		conv << sComando;
		for ( string & sArg : vecArgumentos )
		{
			if ( !sArg.empty() )
			{	
				conv << " " << sArg;
			}
		}
		return ( conv.str () );
	}
	catch (...)
	{
		return ( string( "[Object Error]" ) );
	}
}

 			}
		}
	}
}


