/******************************************************************************/
/*                              CGestorSignals.h                              */
/*----------------------------------------------------------------------------*/
/* Librería:  Sistema                                                         */
/* Versión:   3.0.0                                                           */
/* Fecha:     25/03/2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Fichero de cabecera que contiene la definición de la clase de datos        */
/* CGestorSignals, que facilita la programación de los diferentes "signals"   */
/* del sistema para el proceso en curso.                                      */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#ifndef _ORG_GJS_C_CC_CPP_CGESTORSIGNALS_H
#define _ORG_GJS_C_CC_CPP_CGESTORSIGNALS_H



#include <SistemaSignals.h>



#if ( defined ( SIGNALS_PERMITIDOS ) )


namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {






class CGestorSignals 
{
private:
	PPRCI				p_procRutAtencion;
	PPRCI				p_procRutExterna;			
	PPRCV				p_p_procRutSignals [ SIS_NUM_SIGNALS ];
	PPRCI				p_p_procRutDefSignals [ SIS_NUM_SIGNALS ];
	int					p_iActSignals [ SIS_NUM_SIGNALS ];

	int					iCorrecto;
	
	CGestorSignals *	p_gsigSig;

public:
	CGestorSignals ();
	CGestorSignals ( PPRCI _p_procRutExterna );

	~CGestorSignals ();
	/* Es dueña de los manejadores de señales que instala y lo libera en el destructor: una copia
	   implícita compartiría los punteros y los liberaría dos veces. */
	CGestorSignals ( const CGestorSignals & ) = delete;
	CGestorSignals & operator= ( const CGestorSignals & ) = delete;

	PPRCI RutinaExterna ();
	void EstablecerRutinaExterna ( PPRCI _p_procRutExterna );

	PPRCV RutinaAtencion ( int iSignal );
	void AsignarRutinaAtencion ( int iSignal, PPRCV _p_procRutAtencion, int _iActiva = 1 );
	void DesasignarRutinaAtencion ( int iSignal );
	//void AsignarRutinaPorDefecto ( int iSignal );

	void ActivarSignal ( int iSignal );
	void DesactivarSignal ( int iSignal );
	int EstaSignalActivado ( int iSignal );

	int EsValido ();

	void Procesar ( int iSignal );

	//void AsignarRutinaFinalizacion ( PPRCV _p_procRutAtencion );
	//void DesasignarRutinaFinalizacion ();
	//void AsignarRutinaAlarma ( PPRCV _p_procRutAtencion );
	//void DesasignarRutinaAlarma ();
	//void AsignarRutinaDesconexionTerminal ( PPRCV _p_procRutAtencion );
	//void DesasignarRutinaDesconexionTerminal ();
	//void AsignarRutinaErrorComaFlotante ( PPRCV _p_procRutAtencion );
	//void DesasignarRutinaErrorComaFlotante ();
	//void AsignarRutinaInstruccionIlegal ( PPRCV _p_procRutAtencion );
	//void DesasignarRutinaInstruccionIlegal ();
	//void AsignarRutinaErrorMemoria ( PPRCV _p_procRutAtencion );
	//void DesasignarRutinaErrorMemoria ();
	//void AsignarRutinaErrorBus ( PPRCV _p_procRutAtencion );
	//void DesasignarRutinaErrorBus ();
	//void AsignarRutinaErrorTuberia ( PPRCV _p_procRutAtencion );
	//void DesasignarRutinaErrorTuberia ();
	//void AsignarRutinaInterrupcionTerminal ( PPRCV _p_procRutAtencion );
	//void DesasignarRutinaInterrupcionTerminal ();
	//void AsignarRutinaUsuario1 ( PPRCV _p_procRutAtencion );
	//void DesasignarRutinaUsuario1 ();
	//void AsignarRutinaUsuario2 ( PPRCV _p_procRutAtencion );
	//void DesasignarRutinaUsuario2 ();

private:
	void Inicializar ();
	void Finalizar ();
};



 			}
		}
	}
}


#endif

#endif

