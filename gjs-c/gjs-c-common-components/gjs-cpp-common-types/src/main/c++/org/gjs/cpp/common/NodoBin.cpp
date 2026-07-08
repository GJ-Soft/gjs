#include "CommonTypesConfig.h"
#include "NodoBin.h"
#include "ArbolBin.h"
#include <ToString.h>
#include <Sistema.h>

using namespace std;


namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {

NodoBin::NodoBin ()
{
	datos = NULL;
	arbolDer = NULL;
	arbolIzq = NULL;
	nodoPadre = NULL;
}

NodoBin::NodoBin ( void * _datos )
{
	datos = _datos;
	arbolDer = NULL;
	arbolIzq = NULL;
	nodoPadre = NULL;
}

NodoBin::~NodoBin ()
{
	LiberarDatos ( datos );
}


void * NodoBin::getDatos()
{
	return ( datos );
}

void NodoBin::setDatos( void * _datos )
{
	LiberarDatos ( datos );
	datos = _datos;
}

bool NodoBin::EsValido ()
{
	return ( datos != NULL );
}

bool NodoBin::TieneHijoDer ()
{
	return ( arbolDer != NULL );
}

bool NodoBin::TieneHijoIzq ()
{
	return ( arbolIzq != NULL );
}

bool NodoBin::TieneHijos ()
{
	return ( ( arbolIzq != NULL ) || ( arbolDer != NULL ) );
}

bool NodoBin::TienePadre ()
{
	return ( nodoPadre != NULL );
}

bool NodoBin::EsHijoDer ()
{
	bool bRes = false;
	if ( TienePadre () )
	{
		bRes = ( getPadre()->getHijoDer()->getRaiz() == this );
	}
	return ( bRes );
}

bool NodoBin::EsHijoIzq ()
{
	bool bRes = false;
	if ( TienePadre () )
	{
		bRes = ( getPadre()->getHijoIzq()->getRaiz() == this );
	}
	return ( bRes );
}

ArbolBin * NodoBin::getHijoDer ()
{
	return ( arbolDer );
}

ArbolBin * NodoBin::getHijoIzq ()
{
	return ( arbolIzq );
}

NodoBin * NodoBin::getPadre ()
{
	return ( nodoPadre );
}

void NodoBin::setHijoDer ( ArbolBin * arbol, bool bLiberar )
{
	if ( bLiberar && ( arbolDer != NULL ) )
	{
		delete arbolDer;
	}
	arbolDer = arbol;
}

void NodoBin::setHijoIzq ( ArbolBin * arbol, bool bLiberar )
{
	if ( bLiberar && ( arbolIzq != NULL ) )
	{
		delete arbolIzq;
	}
	arbolIzq = arbol;
}

void NodoBin::setHijoDer ( NodoBin * nodo, bool bLiberar )
{
	setHijoDer ( new ArbolBin( nodo ), bLiberar );
}

void NodoBin::setHijoIzq ( NodoBin * nodo, bool bLiberar )
{
	setHijoIzq ( new ArbolBin( nodo ), bLiberar );
}

void NodoBin::setPadre ( NodoBin * nodo, bool bLiberar )
{
	if ( bLiberar && ( nodoPadre != NULL ) )
	{
		delete nodoPadre;
	}
	nodoPadre = nodo;
}

NodoBin * NodoBin::SigPreorden ()
{
	NodoBin * nodo = NULL;
	if ( TieneHijoIzq () )
	{
		nodo = getHijoIzq ()->PrimeroPreorden();
	}
	else if ( TieneHijoDer () )
	{
		nodo = getHijoDer ()->PrimeroPreorden();
	}
	else if ( TienePadre () )
	{
		if ( EsHijoIzq () )
		{
			nodo = nodo->getPadre ();
		}
		else
		{
			if ( nodo->getPadre()->TienePadre () )
			{
				nodo = nodo->getPadre ()->getPadre ();
			}
		}
		if ( nodo != NULL )
		{
			while ( !nodo->TieneHijoDer () )
			{
				nodo = nodo->getPadre ();
			}
			if ( nodo->TieneHijoDer () )
			{
				nodo = nodo->getHijoDer ()->PrimeroPreorden();
			}
			else
			{
				nodo = NULL;
			}
		}
	}
	return ( nodo );
}

NodoBin * NodoBin::SigPostorden ()
{
	NodoBin * nodo = getPadre ();
	if ( EsHijoIzq () )
	{
		if ( nodo->TieneHijoDer () )
		{
			nodo = nodo->getHijoDer ()->PrimeroPostorden();
		}
	}
	return ( nodo );
}

NodoBin * NodoBin::SigInorden ()
{
	NodoBin * nodo = NULL;
	if ( TieneHijoDer () )
	{
		nodo = getHijoDer ()->PrimeroInorden();
	}
	else if ( TienePadre () )
	{
		nodo = getPadre();
		if ( EsHijoDer () )
		{
			nodo = nodo->getPadre ();
			if ( nodo != NULL )
			{
				nodo = nodo->SigInorden ();
			}
		}
	}
	return ( nodo );
}

string NodoBin::toString()
{
	stringstream stream;
	stream << "[";
	if ( EsValido () )
	{
		if ( TieneHijoIzq () )
		{
			stream << getHijoIzq()->toString() << "-";
		}
		stream << DatosToString ( datos );
		if ( TieneHijoDer () )
		{
			stream << "-" << getHijoDer()->toString();
		}
	}
	else
	{
		stream << "INVAL";
	}
	stream << "]";
	return ( stream.str() );
}

void NodoBin::LiberarDatos( void * _datos )
{
	if ( PuedeLiberarse ( _datos ) )
	{
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdelete-incomplete"
		delete _datos;
#pragma GCC diagnostic pop
	}
}

string NodoBin::DatosToString( void * _datos )
{
	string sRes( "NULO" );
	if ( _datos != NULL )
	{
		sRes = ToString( (unsigned long) _datos );
	}
	return ( sRes );
}

 			}
		}
	}
}
