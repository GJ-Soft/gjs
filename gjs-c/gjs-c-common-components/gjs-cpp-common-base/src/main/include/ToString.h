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
			template<typename... Args> std::string ToString ( const std::string & sFormato, Args&&... argumentos );

			}
		}
	}
}

#endif
