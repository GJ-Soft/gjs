#ifndef _ES_INTERIOR_SOCKETEXCEPCION_H
#define _ES_INTERIOR_SOCKETEXCEPCION_H

#include <string>
#include <SistemaExcepcion.h>



namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {

			class SocketExcepcion : public SistemaExcepcion
			{
			
			public:
				SocketExcepcion ( const std::string & _sModulo, const std::string & _sRutina, int _iErrno );				
			};

 			}
		}
	}
}

#endif