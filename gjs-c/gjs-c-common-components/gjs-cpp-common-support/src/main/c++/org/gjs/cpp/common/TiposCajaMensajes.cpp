/***************************************************************************/
/*                         TiposCajaMensajes.cpp                           */
/*-------------------------------------------------------------------------*/
/* Librería: CajaMensajes                                                  */
/* Versión:  2.0.0                                                         */
/* Fecha:    01/09/2007                                                    */
/* Autor:    Ginés Jiménez Sánchez                                         */
/*-------------------------------------------------------------------------*/
/* Descripción:                                                            */
/* Fichero de código fuente que contiene la implementación de las rutinas  */
/* de carácter general de manejo de los identificadores de tipos de        */
/* cajas de mensajes.                                                      */
/*-------------------------------------------------------------------------*/
/*                    gines_jimenez@safe-mail.net                          */
/***************************************************************************/

#include "TiposCajaMensajes.h"



#include "CommonSupportConfig.h"







using namespace std;

namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {





bool TipCajMsjEsValido ( int iTipo )
{
	return ( ( iTipo == TIP_CAJ_MSJ_INFORMACION ) ||
		 ( iTipo == TIP_CAJ_MSJ_PREGUNTA ) ||
		 ( iTipo == TIP_CAJ_MSJ_PREGUNTA_OKCAN ) ||
		 ( iTipo == TIP_CAJ_MSJ_PREGUNTA_REINCAN ) ||
		 ( iTipo == TIP_CAJ_MSJ_PREGUNTA_SINOCAN ) ||
		 ( iTipo == TIP_CAJ_MSJ_AVISO ) || 
		 ( iTipo == TIP_CAJ_MSJ_AVISO_OKCAN ) || 
		 ( iTipo == TIP_CAJ_MSJ_AVISO_REINCAN ) || 
		 ( iTipo == TIP_CAJ_MSJ_AVISO_ABRREINIGN ) || 
		 ( iTipo == TIP_CAJ_MSJ_ERROR ) ||
		 ( iTipo == TIP_CAJ_MSJ_ERROR_OKCAN ) ||
		 ( iTipo == TIP_CAJ_MSJ_ERROR_REINCAN ) ||
		 ( iTipo == TIP_CAJ_MSJ_ERROR_ABRREINIGN ) );
}

bool TipCajMsjEsValido ( TipoCajaMensajes tipo )
{
	return ( TipCajMsjEsValido ( (int) tipo ) );
}



 			}
		}
	}
}
