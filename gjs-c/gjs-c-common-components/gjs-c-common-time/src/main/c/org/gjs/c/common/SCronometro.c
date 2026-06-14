
#include "SCronometro.h"

#include "TiempoNumerico.h"
#include "TiempoSistema.h"
#include "TiempoConfig.h"



SCronometro * SCronCrear ()
{
	SCronometro * p_cronObj;
	
	p_cronObj = (SCronometro *) MemReservar ( sizeof ( SCronometro ) );
	if ( ES_VALIDO ( p_cronObj ) )
	{
		p_cronObj->dTiempoIni = 0;
	}
	return ( p_cronObj );
}

void SCronDestruir ( SCronometro ** p_p_cronObj )
{
	SCronometro * p_cronObj;
	
	if ( ES_VALIDO ( p_p_cronObj ) )
	{
		p_cronObj = *p_p_cronObj;

		if ( ES_VALIDO ( p_cronObj ) )
		{
			MemLiberar ( (void **) p_p_cronObj );
		}
	}
}

void SCronIniciar ( SCronometro * p_cronObj )
{
	if ( ES_VALIDO ( p_cronObj ) )
	{
		p_cronObj->dTiempoIni = TiempoHoyAhora ();
	}
}

double SCronParar ( SCronometro * p_cronObj )
{
	double dRes;

	if ( ES_VALIDO ( p_cronObj ) )
	{
		dRes = SCronComputo ( p_cronObj );
		p_cronObj->dTiempoIni = 0;
	}
	else
	{
		dRes = 0;
	}
	return ( dRes );
}

double SCronComputo ( SCronometro * p_cronObj )
{
	double dTiempoFin;
	double dRes;

	if ( ES_VALIDO ( p_cronObj ) )
	{
		if ( p_cronObj->dTiempoIni > 0 )
		{
			dTiempoFin = TiempoHoyAhora ();
			dRes = TmpFormObtenerValor ( dTiempoFin ) - TmpFormObtenerValor ( p_cronObj->dTiempoIni );
		} 
		else
		{
			dRes = 0;
		}
	} 
	else
	{
		dRes = 0;
	}
	return ( dRes );
}

