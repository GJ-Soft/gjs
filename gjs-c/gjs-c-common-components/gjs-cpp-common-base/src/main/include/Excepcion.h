#ifndef _ORG_GJS_C_CC_CPP_EXCEPCION_H
#define _ORG_GJS_C_CC_CPP_EXCEPCION_H

#include <string>
#include <stdexcept>




namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {

			class Excepcion : public std::runtime_error
			{
			private:
				std::string sModulo;
				std::string sRutina;
				std::string sMensaje;

			public:
				Excepcion ( const std::string & _sModulo, const std::string & _sRutina, const std::string & _sMensaje );
				Excepcion ( const std::string & _sModulo, const std::string & _sRutina, const std::string & _sMensaje, const std::exception & ex );
				Excepcion ( const std::string & _sModulo, const std::string & _sRutina, const std::exception & ex );

				std::string getModulo () const;
				std::string getRutina () const;
				std::string getMensaje () const;

				const char * what () const noexcept;
				std::string whatExt () const;

				std::exception & toException();

			};

            }
		}
	}
}

#endif
