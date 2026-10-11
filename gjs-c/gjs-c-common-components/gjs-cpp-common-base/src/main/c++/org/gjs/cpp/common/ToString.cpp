#include "BaseConfig.h"
#include "ToString.h"
#include "Sistema.h"

//#include <locale>
//#include <codecvt>



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

string ToString ( IToString & t )
{
	try
	{
		ostringstream conv;

		conv << t.toString();
		return ( conv.str () );
	}
	catch (...)
	{
		return ( string( "[Object Error]" ) );
	}
}

string ToString ( IToString * t )
{
	if ( t != NULL )
	{
	    return ( ToString( *t ) );
	}
	else
	{
		return ( string( "[Object Error]" ) );
	}
}

string ToString ( bool t )
{
	if ( t )
	{
		return ( string( "Cierto" ) );
	}
	else
	{
		return ( string( "Falso" ) );
	}
}

string ToString ( wstring t )
{
	return ( string( t.begin(), t.end() ) );
}

string ToString ( wchar_t * t )
{
	return ( ToString ( wstring( t ) ) );
}

string ToString ( const wchar_t * t )
{
	return ( ToString ( wstring( t ) ) );
}

// string ToString ( const char t[] )
// {
//     if ( t != NULL ) {
//         return ( string ( t ) );
//     } else {
// 		return ( string( "[Object Error]" ) );
// 	}
// }

// string ToString ( char t[] )
// {
// 	return ( ToString ( (const char *) t ) );
// }


string ToString ( const unsigned char t[] )
{
    /* reinterpret_cast, no static_cast: el parametro es const unsigned char *,
       y pasarlo a const char * es reinterpretar los bytes, no convertirlos. El
       cast al estilo C lo hacia igual pero sin decirlo. */
    return ( ToString ( reinterpret_cast < const char * > ( t ) ) );
}

string ToString ( const tm * t )
{
	char buffer [ 9 ];
	strftime ( buffer, 9, "%H:%M:%S", t );
	return ( ToString ( buffer ) );
}

string ToTimeString ( time_t t )
{
	/* Cadena vacia si la hora no se puede convertir: strftime con el NULL que
	   devolvia localtime en ese caso era comportamiento indefinido. */
	string	sRes;
	tm		tmValor;

	if ( HoraLocal ( t, tmValor ) )
	{
		char buffer [ 9 ];
		strftime ( buffer, sizeof ( buffer ), "%H:%M:%S", &tmValor );
		sRes = ToString ( buffer );
	}
	return ( sRes );
}

template <typename T>
string _ToString ( T t )
{
	try
	{
		ostringstream conv;

		conv << t;
		return ( conv.str () );
	}
	catch (...)
	{
		return ( string( "[Object Error]" ) );
	}
}

string ToString ( short t ) {
    return _ToString<short>( t );
}

string ToString ( int t ) {
    return _ToString<int>( t );
}


string ToString ( long t ) {
    return _ToString<long>( t );
}


string ToString ( long long t ) {
    return _ToString<long long>( t );
}


string ToString ( unsigned short t ) {
    return _ToString<unsigned short>( t );
}


string ToString ( unsigned int t ) {
    return _ToString<unsigned int>( t );
}


string ToString ( unsigned long t ) {
    return _ToString<unsigned long>( t );
}


string ToString ( unsigned long long t ) {
    return _ToString<unsigned long long>( t );
}


string ToString ( float t ) {
    return _ToString<float>( t );
}


string ToString ( double t ) {
	try
	{
		array<char, 32> buf;
		to_chars_result result = std::to_chars(buf.data(), buf.data() + buf.size(),
									   t, std::chars_format::general, numeric_limits<double>::max_digits10 );
		if ( result.ec != std::errc{} )
		{
			throw std::runtime_error ( "to_chars fallo" );
		}
		return string( buf.data(), result.ptr );
	}
	catch (...)
	{
		return ( string( "[Object Error]" ) );
	}
}


string ToString ( long double t ) {
	try
	{
		array<char, 32> buf;
		to_chars_result result = std::to_chars(buf.data(), buf.data() + buf.size(),
									   t, std::chars_format::general, numeric_limits<long double>::max_digits10 );
		if ( result.ec != std::errc{} )
		{
			throw std::runtime_error ( "to_chars fallo" );
		}
		return string( buf.data(), result.ptr );
	}
	catch (...)
	{
		return ( string( "[Object Error]" ) );
	}
}


string ToString ( char t ) {
    return _ToString<char>( t );
}


string ToString ( unsigned char t ) {
    return _ToString<unsigned char>( t );
}


string ToString ( char * t ) {
    return _ToString<char *>( t );
}


string ToString ( const char * t ) {
    return _ToString<const char *>( t );
}




template <typename T>
string ToString ( list<T> & lista )
{
	try
	{
		ostringstream conv;

		for ( auto & linea : lista )
		{
			conv << linea << endl;
		}
		return ( conv.str () );
	}
	catch (...)
	{
		return ( string( "[Object Error]" ) );
	}
}

template <typename T>
string ToString ( list<T> * lista )
{
	if ( lista != NULL )
	{
		return ( ToString ( *lista ) );
	}
	else
	{
		return ( string( "[Object Error]" ) );
	}
}

template <typename T>
string ToString ( vector<T> & vector )
{
	try
	{
		ostringstream conv;

		for ( auto & linea : vector )
		{
			conv << linea << endl;
		}
		return ( conv.str () );
	}
	catch (...)
	{
		return ( string( "[Object Error]" ) );
	}
}

template <typename T>
string ToString ( vector<T> * vector )
{
	if ( vector != NULL )
	{
		return ( ToString ( *vector ) );
	}
	else
	{
		return ( string( "[Object Error]" ) );
	}
}

template <typename T>
string ToString ( map<string, T> & mapa )
{
	try
	{
		ostringstream conv;

		for ( auto & linea : mapa )
		{
			conv << linea.first << "=" << linea.second << endl;
		}
		return ( conv.str () );
	}
	catch (...)
	{
		return ( string( "[Object Error]" ) );
	}
}

template <typename T>
string ToString ( map<string, T> * mapa )
{
	if ( mapa != NULL )
	{
		return ( ToString ( *mapa ) );
	}
	else
	{
		return ( string( "[Object Error]" ) );
	}
}

/* La variadica ToString ( sFormato, ... ) esta definida en ToString.h: aqui no
   se instanciaba para nadie de fuera, y ademas usaba format con una cadena de
   formato de tiempo de ejecucion, que no compila. */


template string ToString ( list<string> & );
template string ToString ( list<string> * );
template string ToString ( vector<string> & );
template string ToString ( vector<string> * );
template string ToString ( map<string, string> & );
template string ToString ( map<string, string> * );


			}
		}
	}
}
