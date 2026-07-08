
#include "SConector.h"

#include "TiposDatosConfig.h"






SConector * SCnctCrear ( void * p_vObjeto )
{
	return ( SCnctCrearExt ( p_vObjeto, 0 ) );
}

SConector * SCnctCrearExt ( void * p_vObjeto, int iTipo )
{
	SConector * p_cnctObj;
	
	p_cnctObj = (SConector *) MemReservar ( sizeof ( SConector ) );
	if ( p_cnctObj != NULL )
	{
		p_cnctObj->p_vObjeto = p_vObjeto;
		p_cnctObj->iTipo = iTipo;
	}
	return ( p_cnctObj );
}

void SCnctDestruir ( SConector ** p_p_cnctObj )
{
	SCnctDestruirExt ( p_p_cnctObj, 1 );
}

void SCnctDestruirExt ( SConector ** p_p_cnctObj, int iDestruirContenido )
{
    SConector *   p_cnctObj;
    
    if ( ES_VALIDO ( p_p_cnctObj ) )
    {
        p_cnctObj = *p_p_cnctObj;
 		if ( ES_VALIDO ( p_cnctObj ) )
		{
			if ( iDestruirContenido == 1 )
			{
				MemLiberar ( (void **) &(p_cnctObj->p_vObjeto) );
			}
			MemLiberar ( (void **) p_p_cnctObj );
		}
    }    
}

int SCnctEsValido ( SConector * p_cnctObj )
{
	int iRes;

	if ( ES_VALIDO ( p_cnctObj ) )
	{
		if ( ES_VALIDO ( p_cnctObj->p_vObjeto ) )
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

void * SCnctObjeto ( SConector * p_cnctObj )
{
	void * p_vRes;

	if ( ES_VALIDO ( p_cnctObj ) )
	{
		p_vRes = p_cnctObj->p_vObjeto;
	}
	else
	{
		p_vRes = NULL;
	}
	return ( p_vRes );
}

int SCnctEstablecer ( SConector * p_cnctObj, void * p_vObjeto, int iTipo )
{
	int iRes;

	if ( ES_VALIDO ( p_cnctObj ) )
	{
		p_cnctObj->p_vObjeto = p_vObjeto;
		p_cnctObj->iTipo = iTipo;
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCnctTipo ( SConector * p_cnctObj )
{
	int iRes;

     if ( ES_VALIDO ( p_cnctObj ) )
     {
     	iRes = p_cnctObj->iTipo;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCnctEstablecerObjeto( SConector * p_cnctObj, void * p_vObjeto )
{
	int iRes;

	if ( ES_VALIDO ( p_cnctObj ) )
	{
		p_cnctObj->p_vObjeto = p_vObjeto;
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCnctEstablecerTipo ( SConector * p_cnctObj, int iTipo )
{
	int iRes;

	if ( ES_VALIDO ( p_cnctObj ) )
	{
		p_cnctObj->iTipo = iTipo;
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

void SCnctLimpiar ( SConector * p_cnctObj )
{
     if ( ES_VALIDO ( p_cnctObj ) )
     {
     	p_cnctObj->p_vObjeto = NULL;
     }
}

