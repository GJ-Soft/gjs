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


#include "CommonSystemConfig.h"


#include "SistemaComandos.h"
#include "SistemaTiempo.h"




using namespace std;

namespace org
{
	namespace gjs
	{
		namespace cpp
		{
			namespace common
			{



//NOTA: El para´me, int iSegundoPlano s´polo sirve poara unix

bool SisEjecutarComando ( const string & sComando, const string & sParametros, int iSegundoPlano )
{
	bool		bRes = false;
#  if ( defined ( WIN ) )
	HINSTANCE	hinsExec;
	HWND		hwndProceso;
#  else 
	int			iResSys;
#  endif

	if ( ! sComando.empty () )
	{
#	  if ( defined ( WIN ) )
#	  if ( defined ( _EXE_H ) )
		hwndProceso = ExeVentanaPrincipal ();
#	  else
		hwndProceso = GetForegroundWindow ();
#	  endif
		hinsExec = ShellExecute ( hwndProceso, "open", sComando.c_str(), sParametros.c_str(), NULL, SW_HIDE);
		if ( (INT_PTR)hinsExec > 32 )
		{
			SisEsperar ( 10 );
			bRes = true;
		}
#	  else 
		string sOrden = sComando;
		if ( ! sParametros.empty () )
		{
			/* Sin el string de mas: declaraba otra variable y los parametros se perdian. */
			sOrden = format ( "{} {}", sOrden, sParametros );
		}
		if ( iSegundoPlano == 1 )
		{
			sOrden = format ( "{} &", sOrden );
		}
		errno = 0;
		iResSys = system ( sOrden.c_str () );
		// Comprobamos si el comando terminó correctamente
		if ( WIFEXITED ( iResSys ) )
		{
			int iCodigoSalida = WEXITSTATUS ( iResSys );
			if ( iCodigoSalida == 0 )
			{
				bRes = true; // El comando se ejecutó y devolvió ÉXITO (0)
			}
		}
#	  endif
	}
	return ( bRes );
}


			}
		}
	}
}

