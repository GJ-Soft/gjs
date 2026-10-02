#ifndef _ORG_GJS_C_CC_CPP_LOG_NIVEL_LOG_H
#define _ORG_GJS_C_CC_CPP_LOG_NIVEL_LOG_H


#include <string>

/* Hace falta para el using de mas abajo, y ademas deja esta cabecera
   autosuficiente. */
#include <ToString.h>



namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {
                namespace log
                {
					
/* Los valores llevan prefijo NIVEL_ por una razon concreta: ERROR a secas
   choca con la macro de Windows. wingdi.h ( que entra con windows.h, y que
   WIN32_LEAN_AND_MEAN NO excluye ) hace #define ERROR 0, asi que el
   enumerado se convertia en "0 = 5," y no compilaba. */
enum NivelLog
{
	NIVEL_TODOS = 0,
	NIVEL_TRAZA = 1,
	NIVEL_DEPURACION = 2,
	NIVEL_INFORMACION = 3,
	NIVEL_AVISO = 4,
	NIVEL_ERROR = 5,
	NIVEL_NINGUNO = 6
};

NivelLog ToNivelLog ( int iNivel );
int ToInt ( NivelLog nivel );
std::string ToString ( NivelLog nivel );

/* Declarar ToString aqui esconde TODAS las de common para el codigo de este
   espacio: la busqueda no cualificada para en el primer ambito donde encuentra
   el nombre. Con esto vuelven a estar visibles y conviven como sobrecargas. */
using org::gjs::cpp::common::ToString;
			 
                }
            }
        }
    }
}

#endif
