
#include "SGestorSignals.h"

#include "SistemaConfig.h"


#if ( defined ( SIGNALS_PERMITIDOS ) )


static void SGesSigInicializar ( SGestorSignals * p_gesigObj );
static void SGesSigFinalizar ( SGestorSignals * p_gesigObj );


static void _SisSigRutinaAtencionGeneral ( int iCod );


// NOTA: Si un proceso crea un gestor de signals y ya existe otro, se encadenan el uno al otro:
static SGestorSignals * 		p_gsigActivo = NULL;
static volatile sig_atomic_t	g_iSisGesSigEsperar = 0;



SGestorSignals * SGesSigCrear ( PPRCI fRutExterna )
{
	SGestorSignals * p_gesigObj;
	
	p_gesigObj = (SGestorSignals *) MemReservar ( sizeof ( SGestorSignals ) );
	if ( ES_VALIDO ( p_gesigObj ) )
	{
		g_iSisGesSigEsperar = 1;
		SGesSigInicializar ( p_gesigObj );
		SGesSigEstablecerRutinaExterna ( p_gesigObj, fRutExterna );
		if ( ES_VALIDO ( p_gsigActivo ) )
		{
			p_gesigObj->p_gesigSiguiente = (struct _SGestorSignals *) p_gsigActivo;
		}
		else
		{
			p_gesigObj->p_gesigSiguiente = NULL;
		}
		p_gsigActivo = p_gesigObj;
		g_iSisGesSigEsperar = 0;
	}
	return ( p_gesigObj );
}

void SGesSigDestruir ( SGestorSignals ** p_p_gesigObj )
{
	SGestorSignals * p_gesigObj;
	
	if ( ES_VALIDO ( p_p_gesigObj ) )
	{
		p_gesigObj = *p_p_gesigObj;
		if ( ES_VALIDO ( p_gesigObj ) )
		{
			SGesSigFinalizar ( p_gesigObj );
			MemLiberar ( (void **) p_p_gesigObj );
		}
	}
}

PPRCI SGesSigRutinaExterna ( SGestorSignals * p_gesigObj )
{
	PPRCI fRes;
	
	if ( ES_VALIDO ( p_gesigObj ) )
	{
		fRes = p_gesigObj->fRutExterna;
	}
	else
	{
		fRes = NULL;
	}
	return ( fRes );
}

void SGesSigEstablecerRutinaExterna ( SGestorSignals * p_gesigObj, PPRCI fRutExterna )
{
	if ( ES_VALIDO ( p_gesigObj ) )
	{
		p_gesigObj->fRutExterna = fRutExterna;
	}
}

PPRCV SGesSigRutinaAtencion ( SGestorSignals * p_gesigObj, int iSignal )
{
	PPRCV	fRes;

	if ( ES_VALIDO ( p_gesigObj ) && ( iSignal >= 0 ) && ( iSignal < SIS_NUM_SIGNALS ) )
	{
		if ( SisSigEsProgramable ( iSignal ) == 1 )
		{
			fRes = p_gesigObj->p_fRutSignals [ iSignal ];
		}
		else
		{
			fRes = NULL;
		}
	}
	else
	{
		fRes = NULL;
	}
	return ( fRes );
}

void SGesSigAsignarRutinaAtencion ( SGestorSignals * p_gesigObj, int iSignal, PPRCV fRutAtencion, int iActiva )
{
	if ( ES_VALIDO ( p_gesigObj ) && ( iSignal >= 0 ) && ( iSignal < SIS_NUM_SIGNALS ) )
	{
		if ( SisSigEsProgramable ( iSignal ) == 1 )
		{
			p_gesigObj->p_fRutSignals [ iSignal ] = fRutAtencion;
			if ( iActiva == 1 )
			{
				p_gesigObj->p_iActSignals [ iSignal ] = 1;
			}
			else
			{
				p_gesigObj->p_iActSignals [ iSignal ] = 0;
			}
		}
	}
}

void SGesSigDesasignarRutinaAtencion ( SGestorSignals * p_gesigObj, int iSignal )
{
	if ( ES_VALIDO ( p_gesigObj ) && ( iSignal >= 0 ) && ( iSignal < SIS_NUM_SIGNALS ) )
	{
		p_gesigObj->p_fRutSignals [ iSignal ] = NULL;
		p_gesigObj->p_iActSignals [ iSignal ] = 0;
	}
}

/*
void SGesSigAsignarRutinaPorDefecto ( SGestorSignals * p_gesigObj, int iSignal )
{
	int iCod;
	
	if ( ES_VALIDO ( p_gesigObj ) && ( iSignal >= 0 ) && ( iSignal < SIS_NUM_SIGNALS ) )
	{
		if ( ES_NULO ( p_gesigObj->fRutAtencion ) )
		{
			p_gesigObj->fRutAtencion = &(_SisSigRutinaAtencionGeneral);
		}
		p_gesigObj->p_fRutSignals [ iSignal ] = NULL;
		if ( EstaSignalActivado ( iSignal ) == 1 )
		{
			iCod = SisSigCodigo ( iSignal );
			signal ( iCod, SIG_DFL );
		}
	}
}
*/

void SGesSigActivarSignal ( SGestorSignals * p_gesigObj, int iSignal )
{
	if ( ES_VALIDO ( p_gesigObj ) && ( iSignal >= 0 ) && ( iSignal < SIS_NUM_SIGNALS ) )
	{
		if ( SisSigEsProgramable ( iSignal ) == 1 )
		{
			if ( ES_VALIDO ( p_gesigObj->p_fRutSignals [ iSignal ] ) )
			{
				p_gesigObj->p_iActSignals [ iSignal ] = 1;
			}
			else
			{
				p_gesigObj->p_iActSignals [ iSignal ] = 0;
			}
		}
	}
}

void SGesSigDesactivarSignal ( SGestorSignals * p_gesigObj, int iSignal )
{
	if ( ES_VALIDO ( p_gesigObj ) && ( iSignal >= 0 ) && ( iSignal < SIS_NUM_SIGNALS ) )
	{
		p_gesigObj->p_iActSignals [ iSignal ] = 0;
	}
}

int SGesSigEstaSignalActivado ( SGestorSignals * p_gesigObj, int iSignal )
{
	int iRes;

	if ( ES_VALIDO ( p_gesigObj ) && ( iSignal >= 0 ) && ( iSignal < SIS_NUM_SIGNALS ) )
	{
		iRes = p_gesigObj->p_iActSignals [ iSignal ];
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SGesSigEsValido ( SGestorSignals * p_gesigObj )
{
	int iRes;

	if ( ES_VALIDO ( p_gesigObj ) )
	{
		iRes = p_gesigObj->iCorrecto;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

void SGesSigProcesar ( SGestorSignals * p_gesigObj, int iSignal )
{
	PPRCV	fRutSignal;
	PPRCI	fRutDefSignal;

	if ( ES_VALIDO ( p_gesigObj ) )
	{
		if ( ( iSignal >= 0 ) && ( iSignal < SIS_NUM_SIGNALS ) )
		{
			if ( SGesSigEstaSignalActivado ( p_gesigObj, iSignal ) == 1 )
			{
				fRutSignal = p_gesigObj->p_fRutSignals [ iSignal ];
				if ( ES_VALIDO ( fRutSignal ) )
				{
					(*fRutSignal) ();
				}
			}
			if ( ES_VALIDO ( p_gesigObj->p_gesigSiguiente ) )
			{
				SGesSigProcesar ( ( SGestorSignals * ) (p_gesigObj->p_gesigSiguiente), iSignal );
			}
			else if ( ES_VALIDO ( p_gesigObj->p_fRutDefSignals [ iSignal ] ) )
			{
				fRutDefSignal = p_gesigObj->p_fRutDefSignals [ iSignal ];
				if ( ES_VALIDO ( fRutDefSignal ) )
				{
					(*fRutDefSignal) ( SisSigCodigo ( iSignal ) );
				}
			}
		}
	}
}

/*
void SGesSigAsignarRutinaFinalizacion ( SGestorSignals * p_gesigObj, PPRCV fRutAtencion )
{
	SGesSigAsignarRutinaAtencion ( p_gesigObj, SIS_SIG_ABORTAR, fRutAtencion );
	SGesSigAsignarRutinaAtencion ( p_gesigObj, SIS_SIG_FINALIZACION_OBLIGADA, fRutAtencion );
	SGesSigAsignarRutinaAtencion ( p_gesigObj, SIS_SIG_SALIR, fRutAtencion );
	SGesSigAsignarRutinaAtencion ( p_gesigObj, SIS_SIG_FINALIZACION, fRutAtencion );
}

void SGesSigDesasignarRutinaFinalizacion ( SGestorSignals * p_gesigObj )
{
	SGesSigAsignarRutinaFinalizacion ( p_gesigObj, NULL );
}

void SGesSigAsignarRutinaAlarma ( SGestorSignals * p_gesigObj, PPRCV fRutAtencion )
{
	SGesSigAsignarRutinaAtencion ( p_gesigObj, SIS_SIG_ALARMA, fRutAtencion );
}

void SGesSigDesasignarRutinaAlarma ( SGestorSignals * p_gesigObj )
{
	SGesSigAsignarRutinaAlarma ( p_gesigObj, NULL );
}

void SGesSigAsignarRutinaDesconexionTerminal ( SGestorSignals * p_gesigObj, PPRCV fRutAtencion )
{
	SGesSigAsignarRutinaAtencion ( p_gesigObj, SIS_SIG_TERMINAL_DESCONECTADO, fRutAtencion );
}

void SGesSigDesasignarRutinaDesconexionTerminal ( SGestorSignals * p_gesigObj )
{
	SGesSigAsignarRutinaDesconexionTerminal( p_gesigObj, NULL );
}

void SGesSigAsignarRutinaErrorComaFlotante ( SGestorSignals * p_gesigObj, PPRCV fRutAtencion )
{
	SGesSigAsignarRutinaAtencion ( p_gesigObj, SIS_SIG_ERROR_COMA_FLOTANTE, fRutAtencion );
}

void SGesSigDesasignarRutinaErrorComaFlotante ( SGestorSignals * p_gesigObj )
{
	SGesSigAsignarRutinaErrorComaFlotante ( p_gesigObj, NULL );
}

void SGesSigAsignarRutinaInstruccionIlegal ( SGestorSignals * p_gesigObj, PPRCV fRutAtencion )
{
	SGesSigAsignarRutinaAtencion ( p_gesigObj, SIS_SIG_INSTRUCCION_ILEGAL, fRutAtencion );
}

void SGesSigDesasignarRutinaInstruccionIlegal ( SGestorSignals * p_gesigObj )
{
	SGesSigAsignarRutinaInstruccionIlegal ( p_gesigObj, NULL );
}

void SGesSigAsignarRutinaErrorMemoria ( SGestorSignals * p_gesigObj, PPRCV fRutAtencion )
{
	SGesSigAsignarRutinaAtencion ( p_gesigObj, SIS_SIG_REFERENCIA_MEMORIA_INVALIDA, fRutAtencion );
}

void SGesSigDesasignarRutinaErrorMemoria ( SGestorSignals * p_gesigObj )
{
	AsignarRutinaErrorMemoria ( p_gesigObj, NULL );
}

void SGesSigAsignarRutinaErrorBus ( SGestorSignals * p_gesigObj, PPRCV fRutAtencion )
{
	SGesSigAsignarRutinaAtencion ( p_gesigObj, SIS_SIG_ERROR_BUS, fRutAtencion );
}

void SGesSigDesasignarRutinaErrorBus ( SGestorSignals * p_gesigObj )
{
	SGesSigAsignarRutinaErrorBus ( p_gesigObj, NULL );
}

void SGesSigAsignarRutinaErrorTuberia ( SGestorSignals * p_gesigObj, PPRCV fRutAtencion )
{
	SGesSigAsignarRutinaAtencion ( p_gesigObj, SIS_SIG_ERROR_TUBERIA, fRutAtencion );
}

void SGesSigDesasignarRutinaErrorTuberia ( SGestorSignals * p_gesigObj )
{
	SGesSigAsignarRutinaErrorTuberia ( p_gesigObj, NULL );
}

void SGesSigAsignarRutinaInterrupcionTerminal ( SGestorSignals * p_gesigObj, PPRCV fRutAtencion )
{
	SGesSigAsignarRutinaAtencion ( p_gesigObj, SIS_SIG_INTERRUPCION, fRutAtencion );
}

void SGesSigDesasignarRutinaInterrupcionTerminal ( SGestorSignals * p_gesigObj )
{
	SGesSigAsignarRutinaInterrupcionTerminal ( p_gesigObj, NULL );
}

void SGesSigAsignarRutinaUsuario1 ( SGestorSignals * p_gesigObj, PPRCV fRutAtencion )
{
	SGesSigAsignarRutinaAtencion ( p_gesigObj, SIS_SIG_USUARIO_1, fRutAtencion );
}

void SGesSigDesasignarRutinaUsuario1 ( SGestorSignals * p_gesigObj )
{
	SGesSigAsignarRutinaUsuario1 ( p_gesigObj, NULL );
}

void SGesSigAsignarRutinaUsuario2 ( SGestorSignals * p_gesigObj, PPRCV fRutAtencion )
{
	SGesSigAsignarRutinaAtencion ( p_gesigObj, SIS_SIG_USUARIO_2, fRutAtencion );
}

void SGesSigDesasignarRutinaUsuario2 ( SGestorSignals * p_gesigObj )
{
	SGesSigAsignarRutinaUsuario2 ( p_gesigObj, NULL );
}
*/

static void SGesSigInicializar ( SGestorSignals * p_gesigObj )
{
	int		iSignal;
	int		iCod;
	PPRCI	fAnterior;

	if ( ES_VALIDO ( p_gesigObj ) )
	{
		p_gesigObj->iCorrecto = 1;
		p_gesigObj->fRutAtencion = &(_SisSigRutinaAtencionGeneral);
		p_gesigObj->fRutExterna = NULL;

		for ( iSignal = 0; iSignal < SIS_NUM_SIGNALS; iSignal = iSignal + 1 )
		{
			iCod = SisSigCodigo ( iSignal );
			p_gesigObj->p_fRutSignals [ iSignal ] = NULL;
			p_gesigObj->p_fRutDefSignals [ iSignal ] = NULL;
			p_gesigObj->p_iActSignals [ iSignal ] = 0;

			if ( ( iCod >= 0 ) && ( SisSigEsProgramable ( iSignal ) == 1 ) )
			{
				fAnterior = signal ( iCod, p_gesigObj->fRutAtencion );
				if ( fAnterior != SIG_ERR ) 
				{
					if ( ES_NULO ( p_gesigObj->p_gesigSiguiente ) ) 
					{
						p_gesigObj->p_fRutDefSignals [ iSignal ] = fAnterior;
					}
				}
				else
				{
					// Error:
					p_gesigObj->iCorrecto = 0;
				} 
			}
			//else
			//{
				// SIGNAL NO SOPORTADO POR EL SISTEMA:
			//}
		}
	}
}

static void SGesSigFinalizar ( SGestorSignals * p_gesigObj )
{
	int iSignal;
	int iCod;

	if ( ES_VALIDO ( p_gesigObj ) )
	{
		p_gesigObj->fRutAtencion = NULL;
		p_gesigObj->fRutExterna = NULL;
		for ( iSignal = 0; iSignal < SIS_NUM_SIGNALS; iSignal = iSignal + 1 )
		{
			iCod = SisSigCodigo ( iSignal );
			p_gesigObj->p_fRutSignals [ iSignal ] = NULL;
			p_gesigObj->p_iActSignals [ iSignal ] = 0;
			if ( ES_NULO ( p_gesigObj->p_gesigSiguiente ) )
			{
				signal ( iCod, p_gesigObj->p_fRutDefSignals [ iSignal ] );
			}
			else
			{
				signal ( iCod, SIG_DFL );
			}
		}
		// Recorrer la lista buscando el nodo anterior a p_gesigObj
		SGestorSignals * p_gesigAnterior = p_gsigActivo;
		while ( ES_VALIDO ( p_gesigAnterior ) && ( p_gesigAnterior->p_gesigSiguiente != (struct _SGestorSignals *) p_gesigObj ) )
		{
			p_gesigAnterior = p_gesigAnterior->p_gesigSiguiente;
		}
		if ( ES_VALIDO ( p_gesigAnterior ) )
		{
			p_gesigAnterior->p_gesigSiguiente = p_gesigObj->p_gesigSiguiente;
		}
	}
}

static void _SisSigRutinaAtencionGeneral ( int iCod )
{
	int		iSignal;
	PPRCI	fRutAtencion;
	int		__attribute__ ( ( unused ) ) iVal;

	fRutAtencion = &(_SisSigRutinaAtencionGeneral);
	iSignal = SisSigId ( iCod );

	iVal = 0;
	while ( g_iSisGesSigEsperar == 1 )
	{
		iVal = 1;	
	}
	if ( ( iSignal >= 0 ) && ( iSignal < SIS_NUM_SIGNALS ) &&
		 ( ES_VALIDO ( p_gsigActivo ) ) )
	{
		if ( ES_VALIDO ( SGesSigRutinaExterna ( p_gsigActivo ) ) )
		{
			(*SGesSigRutinaExterna ( p_gsigActivo )) ( iSignal );
		}
		SGesSigProcesar ( p_gsigActivo, iSignal );
		signal ( iCod, fRutAtencion );
	}
}


#endif

