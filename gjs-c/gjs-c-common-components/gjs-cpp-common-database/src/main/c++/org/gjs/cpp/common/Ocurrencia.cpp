#include "CommonDatabaseConfig.h"

#include "Ocurrencia.h"



using namespace org::gjs::cpp::common;
using namespace std;



namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {

Ocurrencia::Ocurrencia ( Entidad * _entidad ) : ListaValores( ( ( _entidad != NULL ) ? _entidad->NumAtributos() : 0 ), false )
{
	 entidad = _entidad;
}

Ocurrencia::Ocurrencia( Ocurrencia * obj )
	: ListaValores( ( ( obj != NULL ) && ( obj->getEntidad() != NULL ) ) ? obj->getEntidad()->NumAtributos() : 0, false )
{
	entidad = ( obj != NULL ) ? obj->getEntidad() : NULL;
	Asignar( obj );
}

Ocurrencia::Ocurrencia( Ocurrencia & obj )
	: ListaValores( ( obj.getEntidad() != NULL ) ? obj.getEntidad()->NumAtributos() : 0, false )
{
	entidad = obj.getEntidad();
	Asignar( obj );
}

Ocurrencia::~Ocurrencia ()
{
}

long Ocurrencia::getHash () const
{
	long lHash = 0;
	if ( entidad != NULL )
	{
		lHash = ( entidad->getHash() * 100000 ) + ListaValores::getHash();
	}
	return( lHash );
}

Entidad * Ocurrencia::getEntidad () const
{
	return( entidad );
}

bool Ocurrencia::EsValida ()
{
	bool bRes = false;
	if ( entidad != NULL )
	{
		bRes = entidad->EsValida() && ListaValores::EsValida() && ( entidad->NumAtributos() == ListaValores::NumValores () );
		if ( bRes )
		{
			for ( int i = 0; i < ListaValores::NumValores(); i = i + 1 )
			{
				Atributo * atributo = entidad->getAtributo( i );
				Valor * valor = ListaValores::getValor( i );
				bRes = bRes && atributo->EsCompatible( valor );
			}
		}
	}
	return( bRes );
}

bool Ocurrencia::EsCompatible ( Entidad & obj )
{
	bool bRes = false;
	if ( EsValida() && obj.EsValida() )
	{
		bRes = entidad->EsCompatible ( obj );
	}
	return ( bRes );
}

bool Ocurrencia::EsCompatible ( Entidad * obj )
{
	bool bRes = false;
	if ( obj != NULL )
	{
		bRes = EsCompatible ( *obj );
	}
	return ( bRes );
}

bool Ocurrencia::EsCompatible ( Ocurrencia & obj )
{
	bool bRes = false;
	if ( obj.EsValida() )
	{
		bRes = EsCompatible( obj.getEntidad () );
	}
	return ( bRes );
}

bool Ocurrencia::EsCompatible ( Ocurrencia * obj )
{
	bool bRes = false;
	if ( obj != NULL )
	{
		bRes = EsCompatible ( *obj );
	}
	return ( bRes );
}

Valor * Ocurrencia::getValor ( const string & sAtributo )
{
	Valor * valor = NULL;
	if ( entidad != NULL )
	{
		valor = getValor( entidad->getIndiceAtributo( sAtributo ) );
	}
	return ( valor );
}

Valor * Ocurrencia::getValor ( int iIndice )
{
	return ( ListaValores::getValor ( iIndice ) );
}

void Ocurrencia::Asignar( Ocurrencia & obj )
{
	/* La compatibilidad se comprueba sobre la estructura (entidad) y el tamano,
	   no sobre la validez de los valores de destino: una ocurrencia recien creada
	   tiene valores nulos (invalida) pero debe poder recibir una copia. */
	if ( obj.EsValida() && ( entidad != NULL ) &&
			entidad->EsCompatible( obj.getEntidad() ) &&
			( NumValores() == obj.NumValores() ) )
	{
		for ( int iInd = 0; iInd < NumValores(); iInd = iInd + 1 )
		{
			Valor * valor = ListaValores::getValor( iInd );
			valor->Asignar( obj.getValor( iInd ) );
		}
	}
}

void Ocurrencia::Asignar( Ocurrencia * obj )
{
	if ( obj != NULL )
	{
		Asignar( *obj );
	}
}

Ocurrencia * Ocurrencia::Clonar()
{
	Ocurrencia * ocurCopia = new Ocurrencia( entidad );
	ocurCopia->Asignar( this );
	return ( ocurCopia );
}

string Ocurrencia::toString ()
{
	try
	{
		return ( Concatenar( "[Ocurrencia={Entidad=[", getEntidad()->toString(), "]; Valores=", ListaValores::toString(), "}]" ) );
	}
	catch (...)
	{
		return ( Concatenar( "[Ocurrencia=[Object Error]]" ) );
	}
}

Ocurrencia & Ocurrencia::operator=( Ocurrencia & obj )
{
	Asignar( obj );
	return ( *this );
}

bool Ocurrencia::operator== ( Ocurrencia & obj )
{
	return ( IComparable::operator==( obj ) );
}

bool Ocurrencia::operator!= ( Ocurrencia & obj )
{
	return ( IComparable::operator!=( obj ) );
}

 			}
		}
	}
}
