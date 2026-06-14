
#include "SReloj.h"

#include "TiempoSistema.h"
#include "Horas.h"
#include "TiempoConfig.h"


SReloj * SRljCrearDef ()
{
	SReloj * p_rljObj;
	
	p_rljObj = (SReloj *) MemReservar ( sizeof ( SReloj ) );
	if ( ES_VALIDO ( p_rljObj ) )
	{
		SRljSincronizarConSistema ( p_rljObj );
	}
	return ( p_rljObj );
}

SReloj * SRljCrear ( long lHora )
{
	SReloj * p_rljObj;
	
	p_rljObj = SRljCrearDef ();
	if ( ES_VALIDO ( p_rljObj ) )
	{
		SRljEstablecer ( p_rljObj, lHora );
	}
	return ( p_rljObj );
}

SReloj * SRljCrearHHMMSS ( int iHH, int iMI, int iSS )
{
	SReloj * p_rljObj;
	
	p_rljObj = SRljCrearDef ();
	if ( ES_VALIDO ( p_rljObj ) )
	{
		SRljEstablecerHHMMSS ( p_rljObj, iHH, iMI, iSS );
	}
	return ( p_rljObj );
}

void SRljDestruir ( SReloj ** p_p_rljObj )
{
	SReloj * p_rljObj;
	
	if ( ES_VALIDO ( p_p_rljObj ) )
	{
		p_rljObj = *p_p_rljObj;

		if ( ES_VALIDO ( p_rljObj ) )
		{
			MemLiberar ( (void **) p_p_rljObj );
		}
	}
}

long SRljHora ( SReloj * p_rljObj )
{
	long lRes;
	long lHoraSis;

	if ( ES_VALIDO ( p_rljObj ) )
	{
		lHoraSis = TiempoAhora ();
		if ( p_rljObj->dDesplazamiento != 0 )
		{
			lRes = HorFormEstablecerValor ( HorFormObtenerValor ( lHoraSis ) + p_rljObj->dDesplazamiento ); 
		}
		else
		{
			lRes = lHoraSis;
		}
	}
	else
	{
		lRes = -1;
	}
	return ( lRes );
}

long SRljHH ( SReloj * p_rljObj )
{
	long lRes;

	if ( ES_VALIDO ( p_rljObj ) )
	{
		lRes = HorFormHoras ( SRljHora ( p_rljObj ) );
	}
	else
	{
		lRes = -1;
	}
	return ( lRes );
}

long SRljMI ( SReloj * p_rljObj )
{
	long lRes;

	if ( ES_VALIDO ( p_rljObj ) )
	{
		lRes = HorFormMinutos ( SRljHora ( p_rljObj ) );
	}
	else
	{
		lRes = -1;
	}
	return ( lRes );
}

long SRljSS ( SReloj * p_rljObj )
{
	long lRes;

	if ( ES_VALIDO ( p_rljObj ) )
	{
		lRes = HorFormSegundos ( SRljHora ( p_rljObj ) );
	}
	else
	{
		lRes = -1;
	}
	return ( lRes );
}

void SRljEstablecer (  SReloj * p_rljObj, long lHora )
{
	double dHoraSis;

	if ( ES_VALIDO ( p_rljObj ) )
	{
		if ( HorFormEsValida ( lHora ) == 1 )
		{
			dHoraSis = HorFormObtenerValor ( TiempoAhora () );
			p_rljObj->dDesplazamiento = HorFormObtenerValor ( lHora ) - dHoraSis;
		}
	}
}

void SRljEstablecerHHMMSS ( SReloj * p_rljObj, int iHH, int iMI, int iSS )
{
	long	lHora;
	double	dHora;
	double	dHoraSis;

	if ( ES_VALIDO ( p_rljObj ) )
	{
		lHora = HorFormConstruir ( iHH, iMI, iSS );
		if ( HorFormEsValida ( lHora ) == 1 )
		{
			dHoraSis = HorFormObtenerValor ( TiempoAhora () );
			dHora = HorFormObtenerValor ( lHora );

			p_rljObj->dDesplazamiento = dHora - dHoraSis;
		}
	}
}

void SRljSincronizarConSistema ( SReloj * p_rljObj )
{
	if ( ES_VALIDO ( p_rljObj ) )
	{
		p_rljObj->dDesplazamiento = 0;
	}
}

void SRljSincronizarConSistemaExt ( SReloj * p_rljObj, long lHoraSis, long lHora )
{
	if ( ES_VALIDO ( p_rljObj ) )
	{
		if ( ( HorFormEsValida ( lHora ) == 1 ) && ( HorFormEsValida ( lHoraSis ) == 1 ) )
		{
			p_rljObj->dDesplazamiento = HorFormObtenerValor ( lHora ) - HorFormObtenerValor ( lHoraSis );
		}
	}
}

