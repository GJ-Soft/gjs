/******************************************************************************/
/*                             SistemaSignals.cpp                             */
/*----------------------------------------------------------------------------*/
/* Librer�a:  Sistema                                                         */
/* Versi�n:   3.0.0                                                           */
/* Fecha:     25/03/2008                                                      */
/* Autor:     Gin�s Jim�nez S�nchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripci�n:                                                               */
/* Fichero de c�digo fuente que contiene la implementaci�n de las rutinas     */
/* de car�cter general para la gesti�n y el manejo de "signals".              */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#include "CommonSystemConfig.h"
#include "SistemaSignals.h"


#if ( defined ( SIGNALS_PERMITIDOS ) )

#include "SistemaProcesos.h"



using namespace std;

namespace org
{
	namespace gjs
	{
		namespace cpp
		{
			namespace common
			{



int SisSigCodigo ( int iSignal )
{
	int iRes = -1;

	if ( iSignal == SIS_SIG_ABORTAR )
	{
		iRes = SIS_COD_SIG_ABORTAR;
	}
	else if ( iSignal == SIS_SIG_ALARMA )
	{
		iRes = SIS_COD_SIG_ALARMA;
	}
	else if ( iSignal == SIS_SIG_ERROR_COMA_FLOTANTE )
	{
		iRes = SIS_COD_SIG_ERROR_COMA_FLOTANTE;
	}
	else if ( iSignal == SIS_SIG_TERMINAL_DESCONECTADO )
	{
		iRes = SIS_COD_SIG_TERMINAL_DESCONECTADO;
	}
	else if ( iSignal == SIS_SIG_INSTRUCCION_ILEGAL )
	{
		iRes = SIS_COD_SIG_INSTRUCCION_ILEGAL;
	}
	else if ( iSignal == SIS_SIG_INTERRUPCION )
	{
		iRes = SIS_COD_SIG_INTERRUPCION;
	}
	else if ( iSignal == SIS_SIG_FINALIZACION_OBLIGADA )
	{
		iRes = SIS_COD_SIG_FINALIZACION_OBLIGADA;
	}
	else if ( iSignal == SIS_SIG_ERROR_TUBERIA )
	{
		iRes = SIS_COD_SIG_ERROR_TUBERIA;
	}
	else if ( iSignal == SIS_SIG_SALIR )
	{
		iRes = SIS_COD_SIG_SALIR;
	}
	else if ( iSignal == SIS_SIG_REFERENCIA_MEMORIA_INVALIDA )
	{
		iRes = SIS_COD_SIG_REFERENCIA_MEMORIA_INVALIDA;
	}
	else if ( iSignal == SIS_SIG_FINALIZACION )
	{
		iRes = SIS_COD_SIG_FINALIZACION;
	}
	else if ( iSignal == SIS_SIG_USUARIO_1 )
	{
		iRes = SIS_COD_SIG_USUARIO_1;
	}
	else if ( iSignal == SIS_SIG_USUARIO_2 )
	{
		iRes = SIS_COD_SIG_USUARIO_2;
	}
	else if ( iSignal == SIS_SIG_TEMPORIZADOR )
	{
		iRes = SIS_COD_SIG_TEMPORIZADOR;
	}
	else if ( iSignal == SIS_SIG_DEPURACION )
	{
		iRes = SIS_COD_SIG_DEPURACION;
	}
#  if ( defined ( POSIX ) )
	else if ( iSignal == SIS_SIG_ERROR_BUS )
	{
		iRes = SIS_COD_SIG_ERROR_BUS;
	}
	else if ( iSignal == SIS_SIG_CAMBIO_ESTADO_HIJO )
	{
		iRes = SIS_COD_SIG_CAMBIO_ESTADO_HIJO;
	}
	else if ( iSignal == SIS_SIG_CONTINUAR )
	{
		iRes = SIS_COD_SIG_CONTINUAR;
	}
	else if ( iSignal == SIS_SIG_PARAR )
	{
		iRes = SIS_COD_SIG_PARAR;
	}
	else if ( iSignal == SIS_SIG_PARAR_TECLADO )
	{
		iRes = SIS_COD_SIG_PARAR_TECLADO;
	}
	else if ( iSignal == SIS_SIG_LECTURA_SEGUNDO_PLANO )
	{
		iRes = SIS_COD_SIG_LECTURA_SEGUNDO_PLANO;
	}
	else if ( iSignal == SIS_SIG_ESCRITURA_SEGUNDO_PLANO )
	{
		iRes = SIS_COD_SIG_ESCRITURA_SEGUNDO_PLANO;
	}
	else if ( iSignal == SIS_SIG_AVISO_SOCKET )
	{
		iRes = SIS_COD_SIG_AVISO_SOCKET;
	}
	else if ( iSignal == SIS_SIG_ERROR_LIMITE_CPU )
	{
		iRes = SIS_COD_SIG_ERROR_LIMITE_CPU;
	}
	else if ( iSignal == SIS_SIG_ERROR_TAM_FICHERO )
	{
		iRes = SIS_COD_SIG_ERROR_TAM_FICHERO;
	}
	else if ( iSignal == SIS_SIG_TEMPORIZADOR_VIRTUAL )
	{
		iRes = SIS_COD_SIG_TEMPORIZADOR_VIRTUAL;
	}
	else if ( iSignal == SIS_SIG_CAMBIO_TAM_VENTANA )
	{
		iRes = SIS_COD_SIG_CAMBIO_TAM_VENTANA;
	}
	else if ( iSignal == SIS_SIG_EVENTO_ENTRADA_SALIDA )
	{
		iRes = SIS_COD_SIG_EVENTO_ENTRADA_SALIDA;
	}
	else if ( iSignal == SIS_SIG_ERROR_REINICIO_SISTEMA )
	{
		iRes = SIS_COD_SIG_ERROR_REINICIO_SISTEMA;
	}
	else if ( iSignal == SIS_SIG_ERROR_LLAMADA_SISTEMA )
	{
		iRes = SIS_COD_SIG_ERROR_LLAMADA_SISTEMA;
	}
#  endif
	return ( iRes );
}

int SisSigId ( int iCod )
{
	int iRes = -1;

	// -1 no es un codigo de senal: es la marca de "en esta plataforma esa
	// senal no existe", y en Windows la llevan ocho de las quince a la vez.
	// Sin esta guarda caeria en la primera rama que valga -1 ( ALARMA ) y
	// devolveria una senal plausible pero equivocada.
	if ( iCod == -1 )
	{
		iRes = -1;
	}
	else if ( iCod == SIS_COD_SIG_ABORTAR )
	{
		iRes = SIS_SIG_ABORTAR;
	}
	else if ( iCod == SIS_COD_SIG_ALARMA )
	{
		iRes = SIS_SIG_ALARMA;
	}
	else if ( iCod == SIS_COD_SIG_ERROR_COMA_FLOTANTE )
	{
		iRes = SIS_SIG_ERROR_COMA_FLOTANTE;
	}
	else if ( iCod == SIS_COD_SIG_TERMINAL_DESCONECTADO )
	{
		iRes = SIS_SIG_TERMINAL_DESCONECTADO;
	}
	else if ( iCod == SIS_COD_SIG_INSTRUCCION_ILEGAL )
	{
		iRes = SIS_SIG_INSTRUCCION_ILEGAL;
	}
	else if ( iCod == SIS_COD_SIG_INTERRUPCION )
	{
		iRes = SIS_SIG_INTERRUPCION;
	}
	else if ( iCod == SIS_COD_SIG_FINALIZACION_OBLIGADA )
	{
		iRes = SIS_SIG_FINALIZACION_OBLIGADA;
	}
	else if ( iCod == SIS_COD_SIG_ERROR_TUBERIA )
	{
		iRes = SIS_SIG_ERROR_TUBERIA;
	}
	else if ( iCod == SIS_COD_SIG_SALIR )
	{
		iRes = SIS_SIG_SALIR;
	}
	else if ( iCod == SIS_COD_SIG_REFERENCIA_MEMORIA_INVALIDA )
	{
		iRes = SIS_SIG_REFERENCIA_MEMORIA_INVALIDA;
	}
	else if ( iCod == SIS_COD_SIG_FINALIZACION )
	{
		iRes = SIS_SIG_FINALIZACION;
	}
	else if ( iCod == SIS_COD_SIG_USUARIO_1 )
	{
		iRes = SIS_SIG_USUARIO_1;
	}
	else if ( iCod == SIS_COD_SIG_USUARIO_2 )
	{
		iRes = SIS_SIG_USUARIO_2;
	}
	else if ( iCod == SIS_COD_SIG_TEMPORIZADOR )
	{
		iRes = SIS_SIG_TEMPORIZADOR;
	}
	else if ( iCod == SIS_COD_SIG_DEPURACION )
	{
		iRes = SIS_SIG_DEPURACION;
	}
#  if ( defined ( POSIX ) )
	else if ( iCod == SIS_COD_SIG_ERROR_BUS )
	{
		iRes = SIS_SIG_ERROR_BUS;
	}
	else if ( iCod == SIS_COD_SIG_CAMBIO_ESTADO_HIJO )
	{
		iRes = SIS_SIG_CAMBIO_ESTADO_HIJO;
	}
	else if ( iCod == SIS_COD_SIG_CONTINUAR )
	{
		iRes = SIS_SIG_CONTINUAR;
	}
	else if ( iCod == SIS_COD_SIG_PARAR )
	{
		iRes = SIS_SIG_PARAR;
	}
	else if ( iCod == SIS_COD_SIG_PARAR_TECLADO )
	{
		iRes = SIS_SIG_PARAR_TECLADO;
	}
	else if ( iCod == SIS_COD_SIG_LECTURA_SEGUNDO_PLANO )
	{
		iRes = SIS_SIG_LECTURA_SEGUNDO_PLANO;
	}
	else if ( iCod == SIS_COD_SIG_ESCRITURA_SEGUNDO_PLANO )
	{
		iRes = SIS_SIG_ESCRITURA_SEGUNDO_PLANO;
	}
	else if ( iCod == SIS_COD_SIG_AVISO_SOCKET )
	{
		iRes = SIS_SIG_AVISO_SOCKET;
	}
	else if ( iCod == SIS_COD_SIG_ERROR_LIMITE_CPU )
	{
		iRes = SIS_SIG_ERROR_LIMITE_CPU;
	}
	else if ( iCod == SIS_COD_SIG_ERROR_TAM_FICHERO )
	{
		iRes = SIS_SIG_ERROR_TAM_FICHERO;
	}
	else if ( iCod == SIS_COD_SIG_TEMPORIZADOR_VIRTUAL )
	{
		iRes = SIS_SIG_TEMPORIZADOR_VIRTUAL;
	}
	else if ( iCod == SIS_COD_SIG_CAMBIO_TAM_VENTANA )
	{
		iRes = SIS_SIG_CAMBIO_TAM_VENTANA;
	}
	else if ( iCod == SIS_COD_SIG_EVENTO_ENTRADA_SALIDA )
	{
		iRes = SIS_SIG_EVENTO_ENTRADA_SALIDA;
	}
	else if ( iCod == SIS_COD_SIG_ERROR_REINICIO_SISTEMA )
	{
		iRes = SIS_SIG_ERROR_REINICIO_SISTEMA;
	}
	else if ( iCod == SIS_COD_SIG_ERROR_LLAMADA_SISTEMA )
	{
		iRes = SIS_SIG_ERROR_LLAMADA_SISTEMA;
	}
#  endif
	return ( iRes );
}

bool SisSigEsProgramable ( int iSignal )
{
	bool bRes = false;

#  if ( defined ( POSIX ) )
	if ( ( iSignal != SIS_SIG_FINALIZACION_OBLIGADA ) &&
		 ( iSignal != SIS_SIG_PARAR ) )
#  else
	if ( iSignal != SIS_SIG_FINALIZACION_OBLIGADA )
#  endif
	{
		bRes = true;
	}
	return ( bRes );
}

bool SisSigEsValida ( int iSignal )
{
	bool bRes = false;

	int iCod = SisSigCodigo ( iSignal );
	bRes = ( iCod >= 0 );
	return ( bRes );
}

string SisSigDescripcion ( int iSignal )
{
	if ( iSignal == SIS_SIG_ABORTAR )
	{
		return ( string ( SIS_SIG_TXT_ABORTAR ) );
	}
	else if ( iSignal == SIS_SIG_ALARMA )
	{
		return ( string ( SIS_SIG_TXT_ALARMA ) );
	}
	else if ( iSignal == SIS_SIG_ERROR_COMA_FLOTANTE )
	{
		return ( string ( SIS_SIG_TXT_ERROR_COMA_FLOTANTE ) );
	}
	else if ( iSignal == SIS_SIG_TERMINAL_DESCONECTADO )
	{
		return ( string ( SIS_SIG_TXT_TERMINAL_DESCONECTADO ) );
	}
	else if ( iSignal == SIS_SIG_INSTRUCCION_ILEGAL )
	{
		return ( string ( SIS_SIG_TXT_INSTRUCCION_ILEGAL ) );
	}
	else if ( iSignal == SIS_SIG_INTERRUPCION )
	{
		return ( string ( SIS_SIG_TXT_INTERRUPCION ) );
	}
	else if ( iSignal == SIS_SIG_FINALIZACION_OBLIGADA )
	{
		return ( string ( SIS_SIG_TXT_FINALIZACION_OBLIGADA ) );
	}
	else if ( iSignal == SIS_SIG_ERROR_TUBERIA )
	{
		return ( string ( SIS_SIG_TXT_ERROR_TUBERIA ) );
	}
	else if ( iSignal == SIS_SIG_SALIR )
	{
		return ( string ( SIS_SIG_TXT_SALIR ) );
	}
	else if ( iSignal == SIS_SIG_REFERENCIA_MEMORIA_INVALIDA )
	{
		return ( string ( SIS_SIG_TXT_REFERENCIA_MEMORIA_INVALIDA ) );
	}
	else if ( iSignal == SIS_SIG_FINALIZACION )
	{
		return ( string ( SIS_SIG_TXT_FINALIZACION ) );
	}
	else if ( iSignal == SIS_SIG_USUARIO_1 )
	{
		return ( string ( SIS_SIG_TXT_USUARIO_1 ) );
	}
	else if ( iSignal == SIS_SIG_USUARIO_2 )
	{
		return ( string ( SIS_SIG_TXT_USUARIO_2 ) );
	}
	else if ( iSignal == SIS_SIG_TEMPORIZADOR )
	{
		return ( string ( SIS_SIG_TXT_TEMPORIZADOR ) );
	}
	else if ( iSignal == SIS_SIG_DEPURACION )
	{
		return ( string ( SIS_SIG_TXT_DEPURACION ) );
	}
#  if ( defined ( POSIX ) )
	else if ( iSignal == SIS_SIG_ERROR_BUS )
	{
		return ( string ( SIS_SIG_TXT_ERROR_BUS ) );
	}
	else if ( iSignal == SIS_SIG_CAMBIO_ESTADO_HIJO )
	{
		return ( string ( SIS_SIG_TXT_CAMBIO_ESTADO_HIJO ) );
	}
	else if ( iSignal == SIS_SIG_CONTINUAR )
	{
		return ( string ( SIS_SIG_TXT_CONTINUAR ) );
	}
	else if ( iSignal == SIS_SIG_PARAR )
	{
		return ( string ( SIS_SIG_TXT_PARAR ) );
	}
	else if ( iSignal == SIS_SIG_PARAR_TECLADO )
	{
		return ( string ( SIS_SIG_TXT_PARAR_TECLADO ) );
	}
	else if ( iSignal == SIS_SIG_LECTURA_SEGUNDO_PLANO )
	{
		return ( string ( SIS_SIG_TXT_LECTURA_SEGUNDO_PLANO ) );
	}
	else if ( iSignal == SIS_SIG_ESCRITURA_SEGUNDO_PLANO )
	{
		return ( string ( SIS_SIG_TXT_ESCRITURA_SEGUNDO_PLANO ) );
	}
	else if ( iSignal == SIS_SIG_AVISO_SOCKET )
	{
		return ( string ( SIS_SIG_TXT_AVISO_SOCKET ) );
	}
	else if ( iSignal == SIS_SIG_ERROR_LIMITE_CPU )
	{
		return ( string ( SIS_SIG_TXT_ERROR_LIMITE_CPU ) );
	}
	else if ( iSignal == SIS_SIG_ERROR_TAM_FICHERO )
	{
		return ( string ( SIS_SIG_TXT_ERROR_TAM_FICHERO ) );
	}
	else if ( iSignal == SIS_SIG_TEMPORIZADOR_VIRTUAL )
	{
		return ( string ( SIS_SIG_TXT_TEMPORIZADOR_VIRTUAL ) );
	}
	else if ( iSignal == SIS_SIG_CAMBIO_TAM_VENTANA )
	{
		return ( string ( SIS_SIG_TXT_CAMBIO_TAM_VENTANA ) );
	}
	else if ( iSignal == SIS_SIG_EVENTO_ENTRADA_SALIDA )
	{
		return ( string ( SIS_SIG_TXT_EVENTO_ENTRADA_SALIDA ) );
	}
	else if ( iSignal == SIS_SIG_ERROR_REINICIO_SISTEMA )
	{
		return ( string ( SIS_SIG_TXT_ERROR_REINICIO_SISTEMA ) );
	}
	else if ( iSignal == SIS_SIG_ERROR_LLAMADA_SISTEMA )
	{
		return ( string ( SIS_SIG_TXT_ERROR_LLAMADA_SISTEMA ) );
	}
#  endif
	else
	{
		return ( "" );
	}
}

bool SisSigEnviar ( long lPID, int iSignal )
{
	bool bRes = false;

	int iCod = SisSigCodigo ( iSignal );
	if ( ( lPID >= 0 ) && ( iCod >= 0 ) )
	{
		// TODO
		//kill ( lPID, iCod );
		//bRes = true;
	}
	return ( bRes );
}

bool SisSigAutoenviar ( int iSignal )
{
	return ( SisSigEnviar ( SisPID (), iSignal ) );
}

bool SisSigAdmiteEspera ()
{
	bool bRes = false;
	static int	iPrueba = -1;
	time_t		tiAntes;
	time_t		tiDespues;

	if ( iPrueba < 0 )
	{
		time ( &tiAntes );
		alarm ( 2 );
		if ( pause () == 0 )
		{
			time ( &tiDespues );
			bRes = ( tiDespues - tiAntes >= 1 );
		}
		iPrueba = (int) bRes;
	}
	return ( bRes );
}


bool SisDesactivarSignal ( int iSignal, PPRCI * p_p_procRutAnterior )
{
	bool bRes = false;
	PPRCI	p_procRutAnt;

	if ( SisSigEsProgramable ( iSignal ) )
	{
		int iCod = SisSigCodigo ( iSignal );
		if ( iCod >= 0 )
		{
			p_procRutAnt = signal ( iCod, SIG_IGN );
			if ( p_procRutAnt != SIG_ERR )
			{
				bRes = true;
				if ( ES_VALIDO ( p_p_procRutAnterior ) )
				{
					*p_p_procRutAnterior = p_procRutAnt;
				}
			}
		}
	}
	return ( bRes );
}

bool SisAsignarSignal ( int iSignal, PPRCI p_procRutAtencion, PPRCI * p_p_procRutAnterior )
{
	PPRCI	p_procRutAnt;
	bool bRes = false;

	if ( SisSigEsProgramable ( iSignal ) )
	{
		int iCod = SisSigCodigo ( iSignal );
		if ( iCod >= 0 )
		{
			if ( ES_VALIDO ( p_procRutAtencion ) )
			{
				p_procRutAnt = signal ( iCod, p_procRutAtencion );
			}
			else
			{
				p_procRutAnt = signal ( iCod, SIG_DFL );
			}
			if ( p_procRutAnt != SIG_ERR )
			{
				if ( ES_VALIDO ( p_p_procRutAnterior ) )
				{
					*p_p_procRutAnterior = p_procRutAnt;
				}
				bRes = true;
			}
		}
	}
	return ( bRes );
}


			}
		}
	}
}


#endif
