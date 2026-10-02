#include "CommonTypesConfig.h"
#include <Prototipos.h>

#include "MapaVector.h"



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

template <class T> MapaVector<T>::MapaVector()
{
}

template <class T> MapaVector<T>::~MapaVector()
{
	clear();
}

template <class T> size_t MapaVector<T>::size() const noexcept
{
	return( vecOrden.size() );
}

template <class T> bool MapaVector<T>::empty() const noexcept
{
	return( vecOrden.empty() );
}

template <class T> bool MapaVector<T>::isValid() const noexcept
{
	bool bRes = ( vecOrden.size() == mapObjetos.size() );
	size_t pos = 0;
	while ( bRes && ( pos < vecOrden.size() ) )
	{
		string sClave = vecOrden[ pos ];
		bRes = ( mapObjetos.find( sClave ) != mapObjetos.end() );
		pos = pos + 1;
	}
	return ( bRes );
}

template <class T> bool MapaVector<T>::exists( const string & sClave )
{
	return( mapObjetos.find( sClave ) != mapObjetos.end() );
}

template <class T> T& MapaVector<T>::at( size_t pos )
{
	if ( pos >= vecOrden.size() )
	{
		throw range_error( "Valor no encontrado" );
	}
	return( mapObjetos.find( vecOrden.at( pos ) )->second );
}

template <class T> T& MapaVector<T>::find( const string & sClave )
{
	typename unordered_map<string, T>::iterator it = mapObjetos.find( sClave );
	if ( it == mapObjetos.end() )
	{
		throw range_error( "Valor no encontrado" );
	}
	return( it->second );
}

template <class T> const vector<string> & MapaVector<T>::getKeys()
{
	return( vecOrden );
}

template <class T> void MapaVector<T>::push_back( const string & sClave, const T & obj )
{
	if ( mapObjetos.find( sClave ) == mapObjetos.end() )
	{
		vecOrden.push_back( sClave );
	}
	mapObjetos[ sClave ] = obj;
}

template <class T> void MapaVector<T>::push_back( const string & sClave, T & obj )
{
	if ( mapObjetos.find( sClave ) == mapObjetos.end() )
	{
		vecOrden.push_back( sClave );
	}
	mapObjetos[ sClave ] = obj;
}

template <class T> void MapaVector<T>::pop_back()
{
	if ( vecOrden.size() > 0 )
	{
		typename unordered_map<string, T>::iterator it = mapObjetos.find( vecOrden[ vecOrden.size() - 1 ] );
		if ( it != mapObjetos.end() )
		{
			mapObjetos.erase( it );
		}
		vecOrden.pop_back();
	}
}

template <class T> void MapaVector<T>::erase( size_t pos )
{
	if ( ( pos >= 0 ) && ( pos < vecOrden.size() ) )
	{
		typename unordered_map<string, T>::iterator it = mapObjetos.find( vecOrden[ pos ] );
		if ( it != mapObjetos.end() )
		{
			mapObjetos.erase( it );
		}
		vecOrden.erase( vecOrden.begin() + pos );
	}
}

template <class T> void MapaVector<T>::erase( const string & sClave )
{
	if ( vecOrden.size() > 0 )
	{
		typename unordered_map<string, T>::iterator itObjetos = mapObjetos.find( sClave );
		if ( itObjetos != mapObjetos.end() )
		{
			mapObjetos.erase( itObjetos );
		}
		bool bEnc = false;
		vector<string>::iterator itOrden = vecOrden.begin();
		while ( !bEnc && ( itOrden != vecOrden.end() ) )
		{
			if ( itOrden->compare( sClave ) == 0 )
			{
				/* erase invalida el iterador que recibe, y el ++ de despues se hacia
				   igual sobre el ya muerto: comportamiento indefinido. El bucle salia
				   por bEnc, pero el incremento ya se habia ejecutado. Se recoge lo que
				   devuelve erase, que es un iterador valido al elemento siguiente. */
				itOrden = vecOrden.erase( itOrden );
				bEnc = true;
			}
			else
			{
				++itOrden;
			}
		}
	}
}


template <class T> void MapaVector<T>::clear() noexcept
{
	vecOrden.clear();
	mapObjetos.clear();
}

template <class T> T& MapaVector<T>::operator[]( size_t pos )
{
	return( at( pos ) );
}

template <class T> T& MapaVector<T>::operator[]( const string & sClave )
{
	return( find( sClave ) );
}


template class MapaVector<string>;

//#include <memory>

//template class MapaVector<unique_ptr<FUNCION_BOOL>>;
template class MapaVector<FUNCION_BOOL>;

 			}
		}
	}
}
