/******************************************************************************/
/*                             SistemaTiempo.cpp                              */
/*----------------------------------------------------------------------------*/
/* Librería:  Sistema                                                         */
/* Versión:   3.0.0                                                           */
/* Fecha:     25/03/2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Fichero de código fuente que contiene la implementación de las rutinas     */
/* de carácter general de manejo de tiempos y temporizaciones.                */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#include "CommonSystemConfig.h"

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




void SisEsperar ( int iMiliSegs )
{
	//timeval timeRetardo;
	
	if ( iMiliSegs > 0 )
	{
#  	  if ( defined ( WIN ) )
		Sleep ( (DWORD) iMiliSegs );
#	  else
		if ( iMiliSegs > 500 )
		{
			sleep ( iMiliSegs / 1000 + 1 );
		}
		else
		{

		}
# 	  endif
		//timeRetardo.tv_sec = 0;
		//timeRetardo.tv_usec = iMiliSegs;

		//select ( 0, 0, 0, 0, &timeRetardo );
	}
}



uint64_t SisCiclosCPU ()
{
	unsigned int uiLow;
	unsigned int uiHigh;

	__asm__ volatile (
		"cpuid\n\t"
		"rdtsc\n\t"
		: "=a"( uiLow ), "=d"( uiHigh )
		:
		: "%rbx", "%rcx"
		);

	return ( ( uint64_t ) uiHigh << 32 ) | uiLow;
}


 			}
		}
	}
}


