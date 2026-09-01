#ifndef _ORG_GJS_C_CC_CPP_TOSTRING_H
#define _ORG_GJS_C_CC_CPP_TOSTRING_H


#include <string>
#include <list>
#include <vector>
#include <map>
#include <ctime>
#include <format>

#include <IToString.h>





namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {

			std::string ToString ( long t );
			std::string ToString ( bool t );
			std::string ToString ( std::wstring t );
			std::string ToString ( wchar_t * t );
			std::string ToString ( const wchar_t * t );
			std::string ToString ( const unsigned char t[] );
			std::string ToString ( const tm * t );

			std::string ToString ( IToString & t );
			std::string ToString ( IToString * t );

			std::string ToTimeString ( time_t t );

			template <typename T> std::string ToString ( std::list<T> & lista );
			template <typename T> std::string ToString ( std::list<T> * lista );
			template <typename T> std::string ToString ( std::vector<T> & vector );
			template <typename T> std::string ToString ( std::vector<T> * vector );
			template <typename T> std::string ToString ( std::map<std::string, T> & mapa );
			template <typename T> std::string ToString ( std::map<std::string, T> * mapa );

            std::string ToString ( short );
            std::string ToString ( int );
            std::string ToString ( long );
            std::string ToString ( long long );
            std::string ToString ( unsigned short );
            std::string ToString ( unsigned int );
            std::string ToString ( unsigned long );
            std::string ToString ( unsigned long long );
            std::string ToString ( float );
            std::string ToString ( double );
            std::string ToString ( long double );
            std::string ToString ( char );
            std::string ToString ( unsigned char );
            std::string ToString ( char * );
            std::string ToString ( const char * );
	
			// Pendiente de test
			/* La definicion va aqui, en la cabecera, y no en el .cpp: una plantilla
			   solo se instancia donde se ve su cuerpo, asi que definida en el .cpp
			   no la podia usar nadie de fuera del modulo.

			   Es vformat y no format porque sFormato llega en tiempo de ejecucion y
			   format exige que la cadena de formato sea una expresion constante. Y
			   los argumentos se pasan SIN forward: make_format_args toma referencias
			   no constantes, asi que necesita lvalues con nombre. */
			template<typename... Args> std::string ToString ( const std::string & sFormato, Args&&... argumentos )
			{
				return ( std::vformat ( sFormato, std::make_format_args ( argumentos... ) ) );
			}

			}
		}
	}
}

#endif
