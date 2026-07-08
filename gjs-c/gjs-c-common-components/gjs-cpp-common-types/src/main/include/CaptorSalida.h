#ifndef _ORG_GJS_C_CC_CPP_CAPTORSALIDA_H
#define _ORG_GJS_C_CC_CPP_CAPTORSALIDA_H

#include <string>
#include <sstream>
#include <vector>




namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {

			class CaptorSalida
			{
			private:
				std::streambuf * 			p_bufViejo = NULL;
				std::stringstream 			ssContenido;

				bool 						bActivado = false;
				std::vector<std::string> 	vecLineas;

			public:
				CaptorSalida ();
				~CaptorSalida ();

				void Ini ();
				void Fin ();
				bool EstaActivado ();

				std::vector<std::string> getLineas ();
			};

 			}
		}
	}
}

#endif
