#ifndef _ORG_GJS_C_CC_SGESTORSIGNALS_H
#define _ORG_GJS_C_CC_SGESTORSIGNALS_H



#include <BaseConfig.h>


#include <SistemaSignals.h>


#if ( defined ( POSIX ) )

typedef struct _SGestorSignals
{
	PPRCI						fRutAtencion;
	PPRCI						fRutExterna;			
	PPRCV						p_fRutSignals [ SIS_NUM_SIGNALS ];
	PPRCI						p_fRutDefSignals [ SIS_NUM_SIGNALS ];
	int							p_iActSignals [ SIS_NUM_SIGNALS ];

	int							iCorrecto;
	struct _SGestorSignals *	p_gesigSiguiente;
} SGestorSignals;


SGestorSignals * SGesSigCrear ( PPRCI fRutExterna );

void SGesSigDestruir ( SGestorSignals ** p_p_concicObj );


PPRCI SGesSigRutinaExterna ( SGestorSignals * p_concicObj );
void SGesSigEstablecerRutinaExterna ( SGestorSignals * p_concicObj, PPRCI fRutExterna );

PPRCV SGesSigRutinaAtencion ( SGestorSignals * p_concicObj, int iSignal );
void SGesSigAsignarRutinaAtencion ( SGestorSignals * p_concicObj, int iSignal, PPRCV fRutAtencion, int iActiva );
void SGesSigDesasignarRutinaAtencion ( SGestorSignals * p_concicObj, int iSignal );
//void SGesSigAsignarRutinaPorDefecto ( SGestorSignals * p_concicObj, int iSignal );

void SGesSigActivarSignal ( SGestorSignals * p_concicObj, int iSignal );
void SGesSigDesactivarSignal ( SGestorSignals * p_concicObj, int iSignal );
int SGesSigEstaSignalActivado ( SGestorSignals * p_concicObj, int iSignal );

int SGesSigEsValido ( SGestorSignals * p_concicObj );

void SGesSigProcesar ( SGestorSignals * p_concicObj, int iSignal );

//void SGesSigAsignarRutinaFinalizacion ( SGestorSignals * p_concicObj, PPRCV fRutAtencion );
//void SGesSigDesasignarRutinaFinalizacion ( SGestorSignals * p_concicObj );
//void SGesSigAsignarRutinaAlarma ( SGestorSignals * p_concicObj, PPRCV fRutAtencion );
//void SGesSigDesasignarRutinaAlarma ( SGestorSignals * p_concicObj );
//void SGesSigAsignarRutinaDesconexionTerminal ( SGestorSignals * p_concicObj, PPRCV fRutAtencion );
//void SGesSigDesasignarRutinaDesconexionTerminal ( SGestorSignals * p_concicObj );
//void SGesSigAsignarRutinaErrorComaFlotante ( SGestorSignals * p_concicObj, PPRCV fRutAtencion );
//void SGesSigDesasignarRutinaErrorComaFlotante ( SGestorSignals * p_concicObj );
//void SGesSigAsignarRutinaInstruccionIlegal ( SGestorSignals * p_concicObj, PPRCV fRutAtencion );
//void SGesSigDesasignarRutinaInstruccionIlegal ( SGestorSignals * p_concicObj );
//void SGesSigAsignarRutinaErrorMemoria ( SGestorSignals * p_concicObj, PPRCV fRutAtencion );
//void SGesSigDesasignarRutinaErrorMemoria ( SGestorSignals * p_concicObj );
//void SGesSigAsignarRutinaErrorBus ( SGestorSignals * p_concicObj, PPRCV fRutAtencion );
//void SGesSigDesasignarRutinaErrorBus ( SGestorSignals * p_concicObj );
//void SGesSigAsignarRutinaErrorTuberia ( SGestorSignals * p_concicObj, PPRCV fRutAtencion );
//void SGesSigDesasignarRutinaErrorTuberia ( SGestorSignals * p_concicObj );
//void SGesSigAsignarRutinaInterrupcionTerminal ( SGestorSignals * p_concicObj, PPRCV fRutAtencion );
//void SGesSigDesasignarRutinaInterrupcionTerminal ( SGestorSignals * p_concicObj );
//void SGesSigAsignarRutinaUsuario1 ( SGestorSignals * p_concicObj, PPRCV fRutAtencion );
//void SGesSigDesasignarRutinaUsuario1 ( SGestorSignals * p_concicObj );
//void SGesSigAsignarRutinaUsuario2 ( SGestorSignals * p_concicObj, PPRCV fRutAtencion );
//void SGesSigDesasignarRutinaUsuario2 ( SGestorSignals * p_concicObj );



#endif

#endif

