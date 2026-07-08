#ifndef _ORG_GJS_C_CC_CPP_SIMBOLOS_H
#define _ORG_GJS_C_CC_CPP_SIMBOLOS_H

#include <string>
#include <vector>
#include <list>
#include <initializer_list>
#include <ostream>



namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {

			// TODO: Completar
			class Simbolos
			{
			private:
				std::vector<std::string> vecContenido;

			public:
				Simbolos ();
				explicit Simbolos ( const std::initializer_list<std::string> & args );
				explicit Simbolos ( const std::list<std::string> & args );
				explicit Simbolos ( const std::vector<std::string> & args );

				int Tam ();
				std::string Simbolo ( int i );
				void Insertar ( const std::string & simbolo );

				std::string& operator[] ( int i );

				friend std::ostream& operator<< ( std::ostream & strm, const Simbolos & simbolos );
			};

 			}
		}
	}
}

#endif
