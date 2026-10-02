/******************************************************************************/
/*                             CGestorSignals.cpp                             */
/*----------------------------------------------------------------------------*/
/* Librer�a:  Sistema                                                         */
/* Versi�n:   3.0.0                                                           */
/* Fecha:     25/03/2008                                                      */
/* Autor:     Gin�s Jim�nez S�nchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripci�n:                                                               */
/* Fichero de c�digo fuente que contiene la implementaci�n de la clase de     */
/* datos CGestorSignals.                                                      */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#include "CommonSystemConfig.h"
#include "CGestorSignals.h"






#if ( defined ( SIGNALS_PERMITIDOS ) )


using namespace std;

namespace org
{
	namespace gjs
	{
		namespace cpp
		{
			namespace common
			{




static void _SisSigRutinaAtencionGeneral ( int _iCod );


// NOTA: Si un proceso crea un gestor de signals y ya existe otro, se encadenan el uno al otro:
static CGestorSignals * p_gsigActivo = NULL;
static int				g_iSisGesSigEsperar = 0;






CGestorSignals::CGestorSignals () 
{
	g_iSisGesSigEsperar = 1;
	if ( ES_VALIDO ( p_gsigActivo ) )
	{
		p_gsigSig = p_gsigActivo;
	}
	else
	{
		p_gsigSig = NULL;
	}
	p_gsigActivo = this;
	Inicializar ();
	g_iSisGesSigEsperar = 0;
}

CGestorSignals::CGestorSignals ( PPRCI _p_procRutExterna ) 
{
	g_iSisGesSigEsperar = 1;
	if ( ES_VALIDO ( p_gsigActivo ) )
	{
		p_gsigSig = p_gsigActivo;
	}
	else
	{
		p_gsigSig = NULL;
	}
	p_gsigActivo = this;
	EstablecerRutinaExterna ( _p_procRutExterna );
	Inicializar ();
	g_iSisGesSigEsperar = 0;
}


CGestorSignals::~CGestorSignals ()
{
	Finalizar ();
}

PPRCI CGestorSignals::RutinaExterna ()
{
	return ( p_procRutExterna );
}

void CGestorSignals::EstablecerRutinaExterna ( PPRCI _p_procRutExterna )
{
	p_procRutExterna = _p_procRutExterna;
}

PPRCV CGestorSignals::RutinaAtencion ( int iSignal )
{
	PPRCV	p_procRes;

	if ( ( iSignal >= 0 ) && ( iSignal < SIS_NUM_SIGNALS ) )
	{
		if ( SisSigEsProgramable ( iSignal ) == 1 )
		{
			p_procRes = p_p_procRutSignals [ iSignal ];
		}
		else
		{
			p_procRes = NULL;
		}
	}
	else
	{
		p_procRes = NULL;
	}
	return ( p_procRes );
}

void CGestorSignals::AsignarRutinaAtencion ( int iSignal, PPRCV _p_procRutAtencion, int _iActiva )
{
	if ( ( iSignal >= 0 ) && ( iSignal < SIS_NUM_SIGNALS ) )
	{
		if ( SisSigEsProgramable ( iSignal ) == 1 )
		{
			p_p_procRutSignals [ iSignal ] = _p_procRutAtencion;
			if ( _iActiva == 1 )
			{
				p_iActSignals [ iSignal ] = 1;
			}
			else
			{
				p_iActSignals [ iSignal ] = 0;
			}
		}
	}
}

void CGestorSignals::DesasignarRutinaAtencion ( int iSignal )
{
	if ( ( iSignal >= 0 ) && ( iSignal < SIS_NUM_SIGNALS ) )
	{
		p_p_procRutSignals [ iSignal ] = NULL;
		p_iActSignals [ iSignal ] = 0;
	}
}

/*
void CGestorSignals::AsignarRutinaPorDefecto ( int iSignal )
{
	if ( ( iSignal >= 0 ) && ( iSignal < SIS_NUM_SIGNALS ) )
	{
		if ( ES_NULO ( p_procRutAtencion ) )
		{
			p_procRutAtencion = &(_SisSigRutinaAtencionGeneral);
		}
		p_p_procRutSignals [ iSignal ] = NULL;
		if ( EstaSignalActivado ( iSignal ) == 1 )
		{
			iCod = SisSigCodigo ( iSignal );
			signal ( iCod, SIG_DFL );
		}
	}
}
*/

void CGestorSignals::ActivarSignal ( int iSignal )
{
	if ( ( iSignal >= 0 ) && ( iSignal < SIS_NUM_SIGNALS ) )
	{
		if ( SisSigEsProgramable ( iSignal ) == 1 )
		{
			if ( ES_VALIDO ( p_p_procRutSignals [ iSignal ] ) )
			{
				p_iActSignals [ iSignal ] = 1;
			}
			else
			{
				p_iActSignals [ iSignal ] = 0;
			}
		}
	}
}

void CGestorSignals::DesactivarSignal ( int iSignal )
{
	if ( ( iSignal >= 0 ) && ( iSignal < SIS_NUM_SIGNALS ) )
	{
		p_iActSignals [ iSignal ] = 0;
	}
}

int CGestorSignals::EstaSignalActivado ( int iSignal )
{
	int iRes;

	if ( ( iSignal >= 0 ) && ( iSignal < SIS_NUM_SIGNALS ) )
	{
		iRes = p_iActSignals [ iSignal ];
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int CGestorSignals::EsValido ()
{
	return ( iCorrecto );
}

void CGestorSignals::Procesar ( int iSignal )
{
	PPRCV	p_procRutSignal;
	PPRCI	p_procRutDefSignal;

	if ( EstaSignalActivado ( iSignal ) == 1 )
	{
		p_procRutSignal = p_p_procRutSignals [ iSignal ];
		if ( ES_VALIDO ( p_procRutSignal ) )
		{
			(*p_procRutSignal) ();
		}
	}
	if ( ES_VALIDO ( p_gsigSig ) )
	{
		p_gsigSig->Procesar ( iSignal );
	}
	else if ( ES_VALIDO ( p_p_procRutDefSignals [ iSignal ] ) )
	{
		p_procRutDefSignal = p_p_procRutDefSignals [ iSignal ];
		if ( ES_VALIDO ( p_procRutDefSignal ) )
		{
			(*p_procRutDefSignal) ( SisSigCodigo ( iSignal ) );
		}
	}
}

/*
void CGestorSignals::AsignarRutinaFinalizacion ( PPRCV _p_procRutAtencion )
{
# if ( defined ( SIGNALS_PERMITIDOS ) )
	AsignarRutinaAtencion ( SIS_SIG_ABORTAR, _p_procRutAtencion );
	AsignarRutinaAtencion ( SIS_SIG_FINALIZACION_OBLIGADA, _p_procRutAtencion );
	AsignarRutinaAtencion ( SIS_SIG_SALIR, _p_procRutAtencion );
	AsignarRutinaAtencion ( SIS_SIG_FINALIZACION, _p_procRutAtencion );
# endif
}

void CGestorSignals::DesasignarRutinaFinalizacion ()
{
	AsignarRutinaFinalizacion ( NULL );
}

void CGestorSignals::AsignarRutinaAlarma ( PPRCV _p_procRutAtencion )
{
	AsignarRutinaAtencion ( SIS_SIG_ALARMA, _p_procRutAtencion );
}

void CGestorSignals::DesasignarRutinaAlarma ()
{
	AsignarRutinaAlarma ( NULL );
}

void CGestorSignals::AsignarRutinaDesconexionTerminal ( PPRCV _p_procRutAtencion )
{
	AsignarRutinaAtencion ( SIS_SIG_TERMINAL_DESCONECTADO, _p_procRutAtencion );
}

void CGestorSignals::DesasignarRutinaDesconexionTerminal ()
{
	AsignarRutinaDesconexionTerminal( NULL );
}

void CGestorSignals::AsignarRutinaErrorComaFlotante ( PPRCV _p_procRutAtencion )
{
	AsignarRutinaAtencion ( SIS_SIG_ERROR_COMA_FLOTANTE, _p_procRutAtencion );
}

void CGestorSignals::DesasignarRutinaErrorComaFlotante ()
{
	AsignarRutinaErrorComaFlotante ( NULL );
}

void CGestorSignals::AsignarRutinaInstruccionIlegal ( PPRCV _p_procRutAtencion )
{
	AsignarRutinaAtencion ( SIS_SIG_INSTRUCCION_ILEGAL, _p_procRutAtencion );
}

void CGestorSignals::DesasignarRutinaInstruccionIlegal ()
{
	AsignarRutinaInstruccionIlegal ( NULL );
}

void CGestorSignals::AsignarRutinaErrorMemoria ( PPRCV _p_procRutAtencion )
{
	AsignarRutinaAtencion ( SIS_SIG_REFERENCIA_MEMORIA_INVALIDA, _p_procRutAtencion );
}

void CGestorSignals::DesasignarRutinaErrorMemoria ()
{
	AsignarRutinaErrorMemoria ( NULL );
}

void CGestorSignals::AsignarRutinaErrorBus ( PPRCV _p_procRutAtencion )
{
	AsignarRutinaAtencion ( SIS_SIG_ERROR_BUS, _p_procRutAtencion );
}

void CGestorSignals::DesasignarRutinaErrorBus ()
{
	AsignarRutinaErrorBus ( NULL );
}

void CGestorSignals::AsignarRutinaErrorTuberia ( PPRCV _p_procRutAtencion )
{
	AsignarRutinaAtencion ( SIS_SIG_ERROR_TUBERIA, _p_procRutAtencion );
}

void CGestorSignals::DesasignarRutinaErrorTuberia ()
{
	AsignarRutinaErrorTuberia ( NULL );
}

void CGestorSignals::AsignarRutinaInterrupcionTerminal ( PPRCV _p_procRutAtencion )
{
	AsignarRutinaAtencion ( SIS_SIG_INTERRUPCION, _p_procRutAtencion );
}

void CGestorSignals::DesasignarRutinaInterrupcionTerminal ()
{
	AsignarRutinaInterrupcionTerminal ( NULL );
}

void CGestorSignals::AsignarRutinaUsuario1 ( PPRCV _p_procRutAtencion )
{
	AsignarRutinaAtencion ( SIS_SIG_USUARIO_1, _p_procRutAtencion );
}

void CGestorSignals::DesasignarRutinaUsuario1 ()
{
	AsignarRutinaUsuario1 ( NULL );
}

void CGestorSignals::AsignarRutinaUsuario2 ( PPRCV _p_procRutAtencion )
{
	AsignarRutinaAtencion ( SIS_SIG_USUARIO_2, _p_procRutAtencion );
}

void CGestorSignals::DesasignarRutinaUsuario2 ()
{
	AsignarRutinaUsuario2 ( NULL );
}
*/

void CGestorSignals::Inicializar ()
{
	int		iSignal;
	int		iCod;
	PPRCI	p_procAnterior;

	iCorrecto = 1;
	p_procRutAtencion = &(_SisSigRutinaAtencionGeneral);
	p_procRutExterna = NULL;

	for ( iSignal = 0; iSignal < SIS_NUM_SIGNALS; iSignal = iSignal + 1 )
	{
		iCod = SisSigCodigo ( iSignal );
		p_p_procRutSignals [ iSignal ] = NULL;
		p_p_procRutDefSignals [ iSignal ] = NULL;
		p_iActSignals [ iSignal ] = 0;

		if ( ( iCod >= 0 ) && ( SisSigEsProgramable ( iSignal ) == 1 ) )
		{
			p_procAnterior = signal ( iCod, p_procRutAtencion );
			if ( p_procAnterior != SIG_ERR ) 
			{
				if ( ES_NULO ( p_gsigSig ) ) 
				{
					p_p_procRutDefSignals [ iSignal ] = p_procAnterior;
				}
			}
			else
			{
				// La senal no se puede programar en esta plataforma ( codigo no
				// aceptado por signal() ): se ignora, sin invalidar el gestor.
				p_iActSignals [ iSignal ] = 0;
			}
		}
		//else
		//{
			// SIGNAL NO SOPORTADO POR EL SISTEMA:
		//}
	}
}

void CGestorSignals::Finalizar ()
{
	int iSignal;
	int iCod;

	p_procRutAtencion = NULL;
	p_procRutExterna = NULL;
	for ( iSignal = 0; iSignal < SIS_NUM_SIGNALS; iSignal = iSignal + 1 )
	{
		iCod = SisSigCodigo ( iSignal );
		p_p_procRutSignals [ iSignal ] = NULL;
		p_iActSignals [ iSignal ] = 0;
		if ( ES_NULO ( p_gsigSig ) )
		{
			signal ( iCod, p_p_procRutDefSignals [ iSignal ] );
		}
		else
		{
			signal ( iCod, SIG_DFL );
		}
	}
	p_gsigActivo = p_gsigSig;
}



static void _SisSigRutinaAtencionGeneral ( int _iCod )
{
	int		iSignal;
	PPRCI	p_procRutAtencion;
	int		iVal;

	p_procRutAtencion = &(_SisSigRutinaAtencionGeneral);
	iSignal = SisSigId ( _iCod );

	while ( g_iSisGesSigEsperar == 1 )
	{
		iVal = 1;	
	}
	if ( ( iSignal >= 0 ) && ( iSignal < SIS_NUM_SIGNALS ) &&
		 ( ES_VALIDO ( p_gsigActivo ) ) )
	{
		if ( ES_VALIDO ( p_gsigActivo->RutinaExterna () ) )
		{
			(*p_gsigActivo->RutinaExterna ()) ( iSignal );
		}
		p_gsigActivo->Procesar ( iSignal );
		signal ( _iCod, p_procRutAtencion );
	}
}



			}
		}
	}
}




#endif

