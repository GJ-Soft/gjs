#ifndef _ORG_GJS_C_CC_CPP_CONCATENAR_H
#define _ORG_GJS_C_CC_CPP_CONCATENAR_H

#include <string>
#include <list>
#include <initializer_list>
#include <sstream>





namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {

			std::string Concatenar ( const std::initializer_list<std::string> & args );
			std::string Concatenar ( const std::list<std::string> & args );

			/* La definicion va aqui, en la cabecera, y no en Concatenar.cpp: una
			   plantilla solo se instancia donde se ve su cuerpo. Definida en el
			   .cpp habia que enumerar a mano cada combinacion de tipos que algun
			   dia fuese a usar alguien, y eran 2.136 instanciaciones explicitas
			   ( el 97% de las 2.208 lineas del fichero ), que ademas solo cubrian
			   string / char * / const char * hasta diez argumentos. Ahora vale
			   cualquier tipo con operator<< y cualquier numero de argumentos.

			   _Concatenar ya no es static: en una cabecera eso daria una copia por
			   unidad de compilacion. El guion bajo sigue marcando que es interna. */
			template<typename T> void _Concatenar ( std::stringstream & ss, T arg )
			{
				ss << arg;
			}

			template<typename T, typename... Types> void _Concatenar ( std::stringstream & ss, T primero, Types... siguientes )
			{
				ss << primero;
				_Concatenar ( ss, siguientes... );
			}

			template<typename... Types> std::string Concatenar ( Types... args )
			{
				std::stringstream ss;

				_Concatenar ( ss, args... );
				return ( ss.str () );
			}

 			}
		}
	}
}

#endif
