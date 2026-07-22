/***************************************************************************/
/*                         TiposCajaMensajes.h                             */
/*-------------------------------------------------------------------------*/
/* Librer�a: CajaMensajes                                                  */
/* Versi�n:  2.0.0                                                         */
/* Fecha:    01/09/2007                                                    */
/* Autor:    Gin�s Jim�nez S�nchez                                         */
/*-------------------------------------------------------------------------*/
/* Descripci�n:                                                            */
/* Fichero de cabecera que contiene la definici�n de los diferentes tipos  */
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




// Tipos de caja de mensajes ( enum class por seguridad de tipos; los valores
// coinciden con los TIP_CAJ_MSJ_* de arriba, que se conservan por compatibilidad ).
enum class TipoCajaMensajes
{
	Informacion     = TIP_CAJ_MSJ_INFORMACION,
	Pregunta        = TIP_CAJ_MSJ_PREGUNTA,
	PreguntaOkCan   = TIP_CAJ_MSJ_PREGUNTA_OKCAN,
	PreguntaReinCan = TIP_CAJ_MSJ_PREGUNTA_REINCAN,
	PreguntaSiNoCan = TIP_CAJ_MSJ_PREGUNTA_SINOCAN,
	Aviso           = TIP_CAJ_MSJ_AVISO,
	AvisoOkCan      = TIP_CAJ_MSJ_AVISO_OKCAN,
	AvisoReinCan    = TIP_CAJ_MSJ_AVISO_REINCAN,
	AvisoAbrReinIgn = TIP_CAJ_MSJ_AVISO_ABRREINIGN,
	Error           = TIP_CAJ_MSJ_ERROR,
	ErrorOkCan      = TIP_CAJ_MSJ_ERROR_OKCAN,
	ErrorReinCan    = TIP_CAJ_MSJ_ERROR_REINCAN,
	ErrorAbrReinIgn = TIP_CAJ_MSJ_ERROR_ABRREINIGN
};

// Respuesta portable ( en WIN se deriva del boton pulsado; en consola POSIX,
// que es bloqueante hasta <retorno>, siempre es Aceptar ).
enum class RespuestaCajaMensajes
{
	Ninguna    = 0,   // no mostrada / tipo invalido
	Aceptar,          // OK / Si
	Cancelar,
	Reintentar,
	No,
	Abortar,
	Ignorar
};


bool TipCajMsjEsValido ( int iTipo );
bool TipCajMsjEsValido ( TipoCajaMensajes tipo );


 			}
		}
	}
}




#endif
