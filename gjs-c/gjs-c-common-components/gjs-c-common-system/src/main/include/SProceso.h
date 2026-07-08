
#ifndef _ORG_GJS_C_CC_SPROCESO_H
#define _ORG_GJS_C_CC_SPROCESO_H








//#include <SCanalComunicacion.h>
//#include <SDatos.h>






typedef struct 
{
	//int		iPIDProcesoPadre;
	long			lPID;
	//int		p_iProcesosHijos [ ENTORNO_MAX_PROCESOS_HIJOS ];
	//int		iNumProcesosHijos;

	//SCanalComunicacion * p_cancomPadre;
	//SCanalComunicacion * * p_pcancomHijos [ ENTORNO_MAX_PROCESOS_HIJOS ];
} SProceso ;


SProceso * SPrcCrear ();

void SPrcDestruir ( SProceso ** p_p_concicObj );


long SPrcPID ( SProceso * p_concicObj );
/*int SPrcPIDPadre ( SProceso * p_concicObj );
//int SPrcNumHijos ( SProceso * p_concicObj );
int SPrcTienePadre ( SProceso * p_concicObj );
int SPrcTieneHijos ( SProceso * p_concicObj );
int SPrcPIDHijo ( SProceso * p_concicObj, int iHijo );

int SPrcAdmiteCrearProcesosHijos ( SProceso * p_concicObj );

int	SPrcDormir ( SProceso * p_concicObj );
int SPrcFinalizar ( SProceso * p_concicObj, int iSinFin );

int SPrcCrearHijo ( SProceso * p_concicObj, int iAbrirCanal );
int SPrcEsperarHijo ( SProceso * p_concicObj, int iHijo );
int SPrcEsperarTodosHijos ( SProceso * p_concicObj );
int SPrcAvisarHijo ( SProceso * p_concicObj, int iHijo );
int SPrcAvisarTodosHijos ( SProceso * p_concicObj );
int SPrcFinalizarHijo ( SProceso * p_concicObj, int iHijo );

int SPrcEstaCanalConPadreAbierto ( SProceso * p_concicObj );
int SPrcEstaCanalConHijoAbierto ( SProceso * p_concicObj, int iHijo );
int SPrcEnviarAlPadre ( SProceso * p_concicObj, SDatos * p_datInfo );
int SPrcRecibirDelPadre ( SProceso * p_concicObj, SDatos * p_datInfo );
int SPrcEnviarAlHijo ( SProceso * p_concicObj, int iHijo, SDatos * p_datInfo );
int SPrcRecibirDelHijo ( SProceso * p_concicObj, int iHijo, SDatos * p_datInfo );
*/







#endif

