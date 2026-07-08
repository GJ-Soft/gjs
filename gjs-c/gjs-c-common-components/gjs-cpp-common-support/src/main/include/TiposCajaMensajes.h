/***************************************************************************/
/*                         TiposCajaMensajes.h                             */
/*-------------------------------------------------------------------------*/
/* Librería: CajaMensajes                                                  */
/* Versión:  2.0.0                                                         */
/* Fecha:    01/09/2007                                                    */
/* Autor:    Ginés Jiménez Sánchez                                         */
/*-------------------------------------------------------------------------*/
/* Descripción:                                                            */
/* Fichero de cabecera que contiene la definición de los diferentes tipos  */
/* de caja de mensajes del sistema.                                        */
/*-------------------------------------------------------------------------*/
/*                    gines_jimenez@safe-mail.net                          */
/***************************************************************************/

#ifndef _ORG_GJS_C_CC_CPP_TIPOSCAJAMENSAJES_H
#define _ORG_GJS_C_CC_CPP_TIPOSCAJAMENSAJES_H



#define TIP_CAJ_MSJ_INFORMACION					0
#define TIP_CAJ_MSJ_PREGUNTA					1
#define TIP_CAJ_MSJ_PREGUNTA_OKCAN				2
#define TIP_CAJ_MSJ_PREGUNTA_REINCAN			3
#define TIP_CAJ_MSJ_PREGUNTA_SINOCAN			4
#define TIP_CAJ_MSJ_AVISO						5
#define TIP_CAJ_MSJ_AVISO_OKCAN					6
#define TIP_CAJ_MSJ_AVISO_REINCAN				7
#define TIP_CAJ_MSJ_AVISO_ABRREINIGN			8
#define TIP_CAJ_MSJ_ERROR						9
#define TIP_CAJ_MSJ_ERROR_OKCAN					10
#define TIP_CAJ_MSJ_ERROR_REINCAN				11
#define TIP_CAJ_MSJ_ERROR_ABRREINIGN			12






namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {




bool TipCajMsjEsValido ( int iTipo );


 			}
		}
	}
}




#endif
