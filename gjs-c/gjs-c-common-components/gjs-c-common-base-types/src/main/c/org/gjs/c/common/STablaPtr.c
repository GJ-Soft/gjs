#include "STablaPtr.h"



#include "TiposBasicosConfig.h"



STablaPtr * STabpCrear ( int iNumFilas, int iNumColumnas )
{
	STablaPtr * p_tabObj;
	
	if ( ( iNumFilas > 0 ) && ( iNumColumnas > 0 ) )
	{
		p_tabObj = (STablaPtr *) MemReservar ( sizeof ( STablaPtr ) );
		if ( ES_VALIDO ( p_tabObj ) )
		{
			p_tabObj->iNumFilas = iNumFilas;
			p_tabObj->iNumColumnas = iNumColumnas;
			p_tabObj->p_vecElementos = SVecpCrear ( iNumFilas * iNumColumnas );
			if ( ES_NULO ( p_tabObj->p_vecElementos ) ) 
			{
				STabpDestruir ( &p_tabObj );
			}
		}
	}
	else
	{
		p_tabObj = NULL;
	}
	return ( p_tabObj );
}

void STabpDestruir ( STablaPtr ** p_p_tabObj )
{
	STablaPtr * p_tabObj;
	
	if ( ES_VALIDO ( p_p_tabObj ) )
	{
		p_tabObj = *p_p_tabObj;

		if ( ES_VALIDO ( p_tabObj ) )
		{
			SVecpDestruir ( &(p_tabObj->p_vecElementos) );
			MemLiberar ( (void **) p_p_tabObj );
		}
	}
}

int STabpEsValida ( STablaPtr * p_tabObj )
{
	int iRes;

	if ( ES_VALIDO ( p_tabObj ) )
	{
		iRes = SVecpEsValido ( p_tabObj->p_vecElementos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int STabpNumFilas ( STablaPtr * p_tabObj )
{
	int iRes;

	if ( ES_VALIDO ( p_tabObj ) )
	{
		iRes = p_tabObj->iNumFilas;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int STabpNumColumnas ( STablaPtr * p_tabObj )
{
	int iRes;

	if ( ES_VALIDO ( p_tabObj ) )
	{
		iRes = p_tabObj->iNumColumnas;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int STabpNumElementos ( STablaPtr * p_tabObj )
{
	int iRes;

	if ( ES_VALIDO ( p_tabObj ) )
	{
		iRes = p_tabObj->iNumFilas * p_tabObj->iNumColumnas;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

byte * STabpElemento ( STablaPtr * p_tabObj, int iFila, int iColumna )
{
	int		iElem;
	byte *	p_byRes;

	if ( STabpEsValida ( p_tabObj ) == 1 ) 
	{
		if ( ( iFila >= 0 ) && ( iFila < p_tabObj->iNumFilas ) &&
			 ( iColumna >= 0 ) && ( iColumna < p_tabObj->iNumColumnas ) )
		{
			iElem = iFila * p_tabObj->iNumColumnas + iColumna;
			p_byRes = SVecpElemento ( p_tabObj->p_vecElementos, iElem );
		}
		else
		{
			p_byRes = NULL;
		}
	}
	else
	{
		p_byRes = NULL;
	}
	return ( p_byRes );
}

int STabpAsignar ( STablaPtr * p_tabObj, int iFila, int iColumna, byte * p_byElem )
{
	int	iElem;
	int	iRes;

	if ( STabpEsValida ( p_tabObj ) == 1 ) 
	{
		if ( ( iFila >= 0 ) && ( iFila < p_tabObj->iNumFilas ) &&
			 ( iColumna >= 0 ) && ( iColumna < p_tabObj->iNumColumnas ) )
		{
			iElem = iFila * p_tabObj->iNumColumnas + iColumna;
			iRes = SVecpAsignar ( p_tabObj->p_vecElementos, iElem, p_byElem );
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

int STabpLimpiarElemento ( STablaPtr * p_tabObj, int iFila, int iColumna )
{
	int	iElem;
	int iRes;			

	if ( STabpEsValida ( p_tabObj ) == 1 ) 
	{
		if ( ( iFila >= 0 ) && ( iFila < p_tabObj->iNumFilas ) &&
			 ( iColumna >= 0 ) && ( iColumna < p_tabObj->iNumColumnas ) )
		{
			iElem = iFila * p_tabObj->iNumColumnas + iColumna;
			iRes = SVecpLimpiarElemento ( p_tabObj->p_vecElementos, iElem );
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

int STabpLimpiar ( STablaPtr * p_tabObj )
{
	int	iRes;

	if ( ES_VALIDO ( p_tabObj ) )
	{
		iRes = SVecpLimpiar ( p_tabObj->p_vecElementos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

SVectorPtr * STabpVector ( STablaPtr * p_tabObj )
{
	SVectorPtr * p_vecRes;

	if ( ES_VALIDO ( p_tabObj ) )
	{
		p_vecRes = p_tabObj->p_vecElementos;
	}
	else
	{
		p_vecRes = NULL;
	}
	return ( p_vecRes );
}

int	STabpLiberacionMemoriaActivada ( STablaPtr * p_tabObj )
{
	int	iRes;

	if ( STabpEsValida ( p_tabObj ) == 1 ) 
	{
		iRes = SVecpLiberacionMemoriaActivada ( p_tabObj->p_vecElementos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

void STabpActivarLiberacionMemoria ( STablaPtr * p_tabObj )
{
	if ( STabpEsValida ( p_tabObj ) == 1 ) 
	{
		SVecpActivarLiberacionMemoria ( p_tabObj->p_vecElementos );
	}
}

void STabpDesactivarLiberacionMemoria ( STablaPtr * p_tabObj )
{
	if ( STabpEsValida ( p_tabObj ) == 1 ) 
	{
		SVecpDesactivarLiberacionMemoria ( p_tabObj->p_vecElementos );
	}
}
