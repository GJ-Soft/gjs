#include "CommonTypesConfig.h"
#include "ArbolBin.h"


using namespace std;



namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {

ArbolBin::ArbolBin ()
{
	nodoRaiz = NULL;
}

ArbolBin::ArbolBin ( NodoBin * nodo )
{
	nodoRaiz = nodo;
}

ArbolBin::ArbolBin ( void * datos )
{
	nodoRaiz = new NodoBin( datos );
}

ArbolBin::~ArbolBin ()
{
	Vaciar ();
	if ( nodoRaiz != NULL )
	{
		delete nodoRaiz;
	}
}

bool ArbolBin::TieneRaiz ()
{
	return ( nodoRaiz != NULL );
}

int ArbolBin::Tam ()
{
	int iRes = 0;
	if ( nodoRaiz != NULL )
	{
		iRes = 1;
		if ( nodoRaiz->TieneHijoIzq() )
		{
			iRes = iRes + nodoRaiz->getHijoIzq()->Tam();
		}
		if ( nodoRaiz->TieneHijoDer() )
		{
			iRes = iRes + nodoRaiz->getHijoDer()->Tam();
		}
	}
	return ( iRes );
}

int ArbolBin::Profundidad ()
{
	int iRes = 0;
	if ( nodoRaiz != NULL )
	{
		int iResIzq = 0;
		int iResDer = 0;
		if ( nodoRaiz->TieneHijoIzq () )
		{
			iResIzq = 1 + nodoRaiz->getHijoIzq()->Profundidad ();
		}
		if ( nodoRaiz->TieneHijoDer () )
		{
			iResDer = 1 + nodoRaiz->getHijoDer()->Profundidad ();
		}
		iRes = max( iResIzq, iResDer );
	}
	return ( iRes );
}

NodoBin * ArbolBin::getRaiz()
{
	return ( nodoRaiz );
}

void ArbolBin::setRaiz( NodoBin * nodo )
{
	nodoRaiz = nodo;
}

void ArbolBin::setRaiz( void * datos )
{
	if ( nodoRaiz != NULL )
	{
		Vaciar();
	}
	nodoRaiz = new NodoBin ( datos );
}

void ArbolBin::EmpadrarPorDer( NodoBin * nodo )
{
	if ( nodo != NULL )
	{
		nodo->setHijoDer( nodoRaiz );
		nodoRaiz->setPadre( nodo );
		nodoRaiz = nodo;
	}
}

void ArbolBin::EmpadrarPorDer( void * datos )
{
	EmpadrarPorDer( new NodoBin( datos ) );
}

void ArbolBin::EmpadrarPorIzq( NodoBin * nodo )
{
	if ( nodo != NULL )
	{
		nodo->setHijoIzq( nodoRaiz );
		nodoRaiz->setPadre( nodo );
		nodoRaiz = nodo;
	}
}

void ArbolBin::EmpadrarPorIzq( void * datos )
{
	EmpadrarPorIzq( new NodoBin( datos ) );
}

void ArbolBin::Vaciar()
{
	if ( nodoRaiz != NULL )
	{
		// Al borrar cada ArbolBin hijo su destructor vacia recursivamente su
		// subarbol; asi no se fugan los objetos ArbolBin envoltorio.
		if ( nodoRaiz->TieneHijoDer() )
		{
			delete nodoRaiz->getHijoDer();
		}
		if ( nodoRaiz->TieneHijoIzq() )
		{
			delete nodoRaiz->getHijoIzq();
		}
		delete nodoRaiz;
		nodoRaiz = NULL;
	}
}

NodoBin * ArbolBin::PrimeroPreorden ()
{
	return ( nodoRaiz );
}

NodoBin * ArbolBin::PrimeroPostorden ()
{
	NodoBin * nodo = NULL;
	if ( TieneRaiz () )
	{
	    nodo = nodoRaiz;
		if ( nodo->TieneHijoIzq () )
		{
			nodo = nodo->getHijoIzq ()->PrimeroPostorden ();
		}
		else if ( nodo->TieneHijoDer () )
		{
			nodo = nodo->getHijoDer ()->PrimeroPostorden ();
		}
		else
		{
			nodo = nodoRaiz;
		}
	}
	return ( nodo );
}

NodoBin * ArbolBin::PrimeroInorden ()
{
	NodoBin * nodo = NULL;
	if ( TieneRaiz () )
	{
	    nodo = nodoRaiz;
		if ( nodo->TieneHijoIzq () )
		{
			nodo = nodo->getHijoIzq ()->PrimeroInorden ();
		}
		else
		{
			nodo = nodoRaiz;
		}
	}
	return ( nodo );
}

string ArbolBin::toString()
{
	if ( TieneRaiz () )
	{
        return ( nodoRaiz->toString() );
	}
	return ( "null" );
}

 			}
		}
	}
}
