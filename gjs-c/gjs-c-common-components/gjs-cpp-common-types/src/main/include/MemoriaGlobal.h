#ifndef _ORG_GJS_C_CC_CPP_MEMORIAGLOBAL_H
#define _ORG_GJS_C_CC_CPP_MEMORIAGLOBAL_H

#include <string>
#include <list>



namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {

			void MemGlobGuardar ( const std::string & sClave, const std::string & sValor );
			std::string MemGlobRecuperar ( const std::string & sClave );
			void MemGlobEliminar ( const std::string & sClave );
			bool MemGlobExiste ( const std::string & sClave );

			void MemGlobLimpiar ();

 			}
		}
	}
}

#endif
