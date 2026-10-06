/******************************************************************************/
/*                         SistemaSincronizacion.cpp                          */
/*----------------------------------------------------------------------------*/
/* Descripcion:                                                               */
/* Implementacion de las rutinas de sincronizacion ( variables de sincro-     */
/* nizacion basadas en spinlocks ). Adaptacion C++ de SistemaSincronizacion.c */
/*----------------------------------------------------------------------------*/

#include "CommonSystemConfig.h"

#include "SistemaSincronizacion.h"




using namespace std;

namespace org
{
	namespace gjs
	{
		namespace cpp
		{
			namespace common
			{


int SisActivarVariableSinc ( varsinc * p_vsVariable )
{
	int iRes;

	if ( ES_VALIDO ( p_vsVariable ) )
	{
#	  if ( defined ( WIN ) )
		if ( InterlockedExchange ( (LONG volatile *) p_vsVariable, 1 ) == 0 )
#	  else
		if ( pthread_spin_trylock ( p_vsVariable ) == 0 )
#	  endif
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
		iRes = 0;
	}
	return ( iRes );
}

int SisEsperarYActivarVariableSinc ( varsinc * p_vsVariable )
{
	int iRes;

	if ( ES_VALIDO ( p_vsVariable ) )
	{
#	  if ( defined ( WIN ) )
		while ( SisActivarVariableSinc ( p_vsVariable ) == 0 )
		{
		}
		iRes = 1;
#	  else
		if ( pthread_spin_lock ( p_vsVariable ) == 0 )
		{
			iRes = 1;
		}
		else
		{
			iRes = 0;
		}
#	  endif
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SisDesactivarVariableSinc ( varsinc * p_vsVariable )
{
	int iRes;

	if ( ES_VALIDO ( p_vsVariable ) )
	{
#	  if ( defined ( WIN ) )
		InterlockedExchange ( (LONG volatile *) p_vsVariable, 0 );
#	  else
		pthread_spin_unlock ( p_vsVariable );
#	  endif
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

#if ( !defined ( WIN ) )

void SisInicializarVariableSinc ( varsinc * p_vsVariable )
{
	if ( ES_VALIDO ( p_vsVariable ) )
	{
		pthread_spin_init ( p_vsVariable, PTHREAD_PROCESS_PRIVATE );
	}
}

void SisFinalizarVariableSinc ( varsinc * p_vsVariable )
{
	if ( ES_VALIDO ( p_vsVariable ) )
	{
		pthread_spin_destroy ( p_vsVariable );
	}
}

#endif


			}
		}
	}
}
