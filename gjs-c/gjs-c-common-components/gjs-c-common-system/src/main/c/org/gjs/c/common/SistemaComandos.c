/******************************************************************************/
/*                            SistemaComandos.cpp                             */
/*----------------------------------------------------------------------------*/
/* Librería:  Sistema                                                         */
/* Versión:   3.0.0                                                           */
/* Fecha:     25/03/2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Fichero de código fuente que contiene la implementación de la algunas      */
/* rutinas para el ejecución directa de comandos y programas externos.        */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/



#include "SistemaComandos.h"
#include "SistemaTiempo.h"

#include "SistemaConfig.h"



//NOTA: El para´me, int iSegundoPlano s´polo sirve poara unix

int SisEjecutarComando ( const char * p_cComando, const char * p_cParametros, int iSegundoPlano )
{
	int			iRes;
#  if ( defined ( WIN ) )
	HINSTANCE	hinsExec;
	HWND		hwndProceso;
#  else 
	int			iResSys;
	char *		p_cOrden;
#  endif

	if ( ES_VALIDO ( p_cComando ) )
	{
#	  if ( defined ( WIN ) )
#	  if ( defined ( _EXE_H ) )
		hwndProceso = ExeVentanaPrincipal ();
#	  else
		hwndProceso = GetForegroundWindow ();
#	  endif
		// PENDIENTE: Mejorar separando el directorio del programa y de los parámetros:
		//hinsExec = ShellExecute ( hwndProceso, "open", p_cComando, NULL, NULL, SW_SHOW );
		//hinsExec = ShellExecute ( hwndProceso, "open", p_cComando, p_cParametros, NULL, SW_SHOW );
		hinsExec = ShellExecute ( hwndProceso, "open", p_cComando, p_cParametros, NULL, SW_HIDE );
		if ( (INT_PTR)hinsExec > 32 )
		{
			SisEsperar ( 10 );
			iRes = 1;
		}
		else
		{
			iRes = 0;
		}
#	  else 
		if ( ES_VALIDO ( p_cParametros ) )
		{
			p_cOrden = CadCrear ( CadLongitud ( p_cComando ) + CadLongitud ( p_cParametros ) + 3 );
			if ( ES_VALIDO ( p_cOrden ) )
			{
				if ( CadCopiar ( p_cOrden, p_cComando ) == 1 )
				{
					if ( CadConcatenar ( p_cOrden, " " ) == 1 )
					{
						if ( CadConcatenar ( p_cOrden, p_cParametros ) == 1 )
						{
							if ( iSegundoPlano == 1 )
							{
								if ( CadConcatenar ( p_cOrden, " &" ) == 1 )
								{
									iRes = 1;
								}
								else
								{
									iRes = 0;
								}
							}
							else
							{
								iRes = 1;
							}
						}
						else
						{
							iRes = 0;
						}
					}
					else
					{
						iRes = 0;
					}
				}
				else
				{
					iRes = 0;
				}
			}
			else
			{
				iRes = 0;
			}
		}
		else
		{
			p_cOrden = CadDuplicar ( p_cComando );
			if ( ES_VALIDO ( p_cOrden ) )
			{
				iRes = 1;
			}
			else
			{
				iRes = 0;
			}
		}
		if ( iRes == 1 )
		{
			errno = 0;
			iResSys = system ( p_cOrden );
			if ( iResSys == - 1 ) 
			{
				iRes = 0;
			}
			else
			{
				if ( iSegundoPlano == 1 )
				{
					SisEsperar ( 1000 );
				}
				// Comprobamos si el comando terminó correctamente
				if ( WIFEXITED ( iResSys ) )
				{
					int iCodigoSalida = WEXITSTATUS ( iResSys );
					if ( iCodigoSalida == 0 )
					{
						iRes = 1; // El comando se ejecutó y devolvió ÉXITO (0)
					}
					else
					{
						iRes = 0; // El comando se ejecutó pero devolvió un código de ERROR (ej. 1, 2, 5...)
					}
				}
				else
				{
					iRes = 0; // El proceso no terminó normalmente (ej. fue matado por una señal)
				}
			}
		}
		MemLiberar ( (void **) &p_cOrden );
#	  endif
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

