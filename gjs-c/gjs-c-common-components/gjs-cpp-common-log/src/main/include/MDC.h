#ifndef _ORG_GJS_C_CC_CPP_LOG_MDC_H
#define _ORG_GJS_C_CC_CPP_LOG_MDC_H


#include <string>





namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {
                namespace MDC
                {
			void MDCGuardar ( const std::string & sClave, const std::string & sValor );
			std::string MDCRecuperar ( const std::string & sClave );
			void MDCEliminar ( const std::string & sClave );

			void MDCLimpiar ();
                }
            }
        }
    }
}

#endif
