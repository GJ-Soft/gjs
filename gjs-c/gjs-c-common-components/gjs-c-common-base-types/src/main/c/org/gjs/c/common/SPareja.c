#include "SPareja.h"



#include "TiposBasicosConfig.h"



SPareja * SPrjCrear ( void * p_vPrimero, void * p_vSegundo, int iLiberar )
{
	SPareja * p_prjObj;
	
	if ( ES_VALIDO ( p_vPrimero ) && ES_VALIDO ( p_vSegundo ) && BOOL_VALIDO ( iLiberar ) )
	{
		p_prjObj = (SPareja *) MemReservar ( sizeof ( SPareja ) );
		if ( ES_VALIDO ( p_prjObj ) )
		{
			p_prjObj->p_vPrimero = p_vPrimero;
			p_prjObj->p_vSegundo = p_vSegundo;
			p_prjObj->iLiberar = iLiberar;
		}
	}
	else
	{
		p_prjObj = NULL;
	}
	return ( p_prjObj );
}

SPareja * SPrjCrearGestionando ( void * p_vPrimero, void * p_vSegundo )
{
	return ( SPrjCrear ( p_vPrimero, p_vSegundo, 1 ) );
}

SPareja * SPrjCrearSoloPtr ( void * p_vPrimero, void * p_vSegundo )
{
	return ( SPrjCrear ( p_vPrimero, p_vSegundo, 0 ) );
}

void SPrjDestruir ( SPareja ** p_p_prjObj )
{
	SPareja * p_prjObj;
	
	if ( ES_VALIDO ( p_p_prjObj ) )
	{
		p_prjObj = *p_p_prjObj;

		if ( ES_VALIDO ( p_prjObj ) )
		{
			if ( p_prjObj->iLiberar == 1 )
			{
				MemLiberar ( (void **) &(p_prjObj->p_vPrimero) );
				MemLiberar ( (void **) &( p_prjObj->p_vSegundo ) );
			}
			MemLiberar ( (void **) p_p_prjObj );
		}
	}
}

int SPrjEsValido ( SPareja * p_prjObj )
{
	int iRes;

	if ( ES_VALIDO ( p_prjObj ) )
	{
		if ( ES_VALIDO ( p_prjObj->p_vPrimero ) && ES_VALIDO ( p_prjObj->p_vSegundo ) )
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

void * SPrjObtenerPrimero ( SPareja * p_prjObj )
{
	void * p_vRes;

	if ( ES_VALIDO ( p_prjObj ) )
	{
		p_vRes = p_prjObj->p_vPrimero;
	}
	else
	{
		p_vRes = NULL;
	}
	return ( p_vRes );
}

void * SPrjObtenerSegundo ( SPareja * p_prjObj )
{
	void * p_vRes;

	if ( ES_VALIDO ( p_prjObj ) )
	{
		p_vRes = p_prjObj->p_vSegundo;
	}
	else
	{
		p_vRes = NULL;
	}
	return ( p_vRes );
}

void SPrjEstablecerPrimero ( SPareja * p_prjObj, void * p_vDatos )
{
	if ( ES_VALIDO ( p_prjObj ) && ES_VALIDO ( p_vDatos ) )
	{
		if ( p_prjObj->iLiberar == 1 )
		{
			MemLiberar ( (void **) &(p_prjObj->p_vPrimero) );
		}

		p_prjObj->p_vPrimero = p_vDatos;
	}
}

void SPrjEstablecerSegundo ( SPareja * p_prjObj, void * p_vDatos )
{
	if ( ES_VALIDO ( p_prjObj ) && ES_VALIDO ( p_vDatos ) )
	{
		if ( p_prjObj->iLiberar == 1 )
		{
			MemLiberar ( ( void ** ) &( p_prjObj->p_vSegundo ) );
		}

		p_prjObj->p_vSegundo = p_vDatos;
	}
}

int	SPrjLiberacionMemoriaActivada ( SPareja * p_prjObj )
{
	int iRes;

	if ( ES_VALIDO ( p_prjObj ) )
	{
		iRes = p_prjObj->iLiberar;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

void SPrjActivarLiberacionMemoria ( SPareja * p_prjObj )
{
	if ( ES_VALIDO ( p_prjObj ) )
	{
		p_prjObj->iLiberar = 1;
	}
}

void SPrjDesactivarLiberacionMemoria ( SPareja * p_prjObj )
{
	if ( ES_VALIDO ( p_prjObj ) )
	{
		p_prjObj->iLiberar = 0;
	}
}



