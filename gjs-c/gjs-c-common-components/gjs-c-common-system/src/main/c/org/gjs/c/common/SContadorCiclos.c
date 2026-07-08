#include "SContadorCiclos.h"

#include "SistemaTiempo.h"
#include "SistemaConfig.h"


SContadorCiclos * SConCicCrear ()
{
	SContadorCiclos * p_concicObj;
	
	p_concicObj = (SContadorCiclos *) MemReservar ( sizeof ( SContadorCiclos ) );
	if ( ES_VALIDO ( p_concicObj ) )
	{
		p_concicObj->iIniciado = 0;
		p_concicObj->ui64CicloIni = 0;
		p_concicObj->ui64NumCiclos = 0;
	}
	return ( p_concicObj );
}

void SConCicDestruir ( SContadorCiclos ** p_p_concicObj )
{
	SContadorCiclos * p_concicObj;
	
	if ( ES_VALIDO ( p_p_concicObj ) )
	{
		p_concicObj = *p_p_concicObj;
		if ( ES_VALIDO ( p_concicObj ) )
		{
			MemLiberar ( (void **) p_p_concicObj );
		}
	}
}

void SConCicIniciar ( SContadorCiclos * p_concicObj )
{
	if ( ES_VALIDO ( p_concicObj ) )
	{
		if ( p_concicObj->iIniciado == 0 )
		{
			p_concicObj->ui64NumCiclos = 0;
			p_concicObj->ui64CicloIni = SisCiclosCPU ();
			p_concicObj->iIniciado = 1;
		}
	}

}
uint64_t SConCicValor ( SContadorCiclos * p_concicObj )
{
	uint64_t ui64Res;

	if ( ES_VALIDO ( p_concicObj ) )
	{
		if ( p_concicObj->iIniciado == 1 )
		{
			p_concicObj->ui64NumCiclos = SisCiclosCPU () - p_concicObj->ui64CicloIni;
		}
		ui64Res = p_concicObj->ui64NumCiclos;
	}
	else
	{
		ui64Res = 0;
	}
	return ( ui64Res );
}

uint64_t SConCicParar ( SContadorCiclos * p_concicObj )
{
	uint64_t ui64Res;

	if ( ES_VALIDO ( p_concicObj ) )
	{
		if ( p_concicObj->iIniciado == 1 )
		{
			p_concicObj->ui64NumCiclos = SisCiclosCPU () - p_concicObj->ui64CicloIni;
			p_concicObj->iIniciado = 0;
			ui64Res = p_concicObj->ui64NumCiclos;
		}
		else
		{
			ui64Res = 0;
		}
	}
	else
	{
		ui64Res = 0;
	}
	return ( ui64Res );
}

int SConCicEstaContando ( SContadorCiclos * p_concicObj )
{
	int iRes;

	if ( ES_VALIDO ( p_concicObj ) )
	{
		iRes = p_concicObj->iIniciado;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

