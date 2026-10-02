
#include "SUbicacion.h"

#include "TiposDatosConfig.h"









SUbicacion * SUbcCrearDef () 
{
	SUbicacion * p_ubcObj;
	
	p_ubcObj = (SUbicacion *) MemReservar ( sizeof ( SUbicacion ) );
	if ( ES_VALIDO ( p_ubcObj ) )
	{
		SUbcEstablecer ( p_ubcObj, SUBC_SIN_POSICION, 0 );
	}
	return ( p_ubcObj );
}

SUbicacion * SUbcCrear ( unsigned long ulPos, unsigned long ulTam ) 
{
	SUbicacion * p_ubcObj;
	
	p_ubcObj = (SUbicacion *) MemReservar ( sizeof ( SUbicacion ) );
	if ( ES_VALIDO ( p_ubcObj ) )
	{
		SUbcEstablecer ( p_ubcObj, ulPos, ulTam );
	}
	return ( p_ubcObj );
}

void SUbcDestruir ( SUbicacion ** p_p_ubcObj )
{
	if ( ES_VALIDO ( p_p_ubcObj ) )
	{
		MemLiberar ( (void **) p_p_ubcObj );
	}
}

unsigned long SUbcPos ( SUbicacion * p_ubcObj )
{
	unsigned long ulRes;
	
	if ( ES_VALIDO ( p_ubcObj ) )
	{
		ulRes = p_ubcObj->ulPos;
	}
	else
	{
		ulRes = SUBC_SIN_POSICION;
	}
	return ( ulRes );
}

unsigned long SUbcTam ( SUbicacion * p_ubcObj )
{
	unsigned long ulRes;
	
	if ( ES_VALIDO ( p_ubcObj ) )
	{
		ulRes = p_ubcObj->ulTam;
	}
	else
	{
		ulRes = 0;
	}
	return ( ulRes );
}

void SUbcEstablecer ( SUbicacion * p_ubcObj, unsigned long ulPos, unsigned long ulTam )
{
	if ( ES_VALIDO ( p_ubcObj ) )
	{
		p_ubcObj->ulPos = ulPos;
		p_ubcObj->ulTam = ulTam;
	}
}

void SUbcEstablecerPos ( SUbicacion * p_ubcObj, unsigned long ulPos )
{
	if ( ES_VALIDO ( p_ubcObj ) )
	{
		p_ubcObj->ulPos = ulPos;
	}
}

void SUbcEstablecerTam ( SUbicacion * p_ubcObj, unsigned long ulTam )
{
	if ( ES_VALIDO ( p_ubcObj ) )
	{
		p_ubcObj->ulTam = ulTam;
	}
}

int SUbcDesplazar ( SUbicacion * p_ubcObj, long lDesp )
{
	int				iRes;
	unsigned long	ulMagnitud;

	if ( ES_VALIDO ( p_ubcObj ) )
	{
		/* Una ubicacion sin posicion no se desplaza. */
		if ( p_ubcObj->ulPos != SUBC_SIN_POSICION )
		{
			if ( lDesp >= 0 )
			{
				/* Hacia delante, sin llegar a la marca SUBC_SIN_POSICION. */
				if ( (unsigned long) lDesp < SUBC_SIN_POSICION - p_ubcObj->ulPos )
				{
					p_ubcObj->ulPos = p_ubcObj->ulPos + (unsigned long) lDesp;
					iRes = 1;
				}
				else
				{
					iRes = 0;
				}
			}
			else
			{
				/* Hacia atras, sin pasar de 0. La magnitud se calcula como
				   -( lDesp + 1 ) + 1 porque -LONG_MIN no cabe en un long. */
				ulMagnitud = (unsigned long) ( - ( lDesp + 1 ) ) + 1UL;
				if ( ulMagnitud <= p_ubcObj->ulPos )
				{
					p_ubcObj->ulPos = p_ubcObj->ulPos - ulMagnitud;
					iRes = 1;
				}
				else
				{
					iRes = 0;
				}
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
	return ( iRes );
}

int SUbcEsValida ( SUbicacion * p_ubcObj )
{
	int iRes;

	if ( ES_VALIDO ( p_ubcObj ) )
	{
		if ( ( p_ubcObj->ulPos != SUBC_SIN_POSICION ) && ( p_ubcObj->ulTam > 0 ) )
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



