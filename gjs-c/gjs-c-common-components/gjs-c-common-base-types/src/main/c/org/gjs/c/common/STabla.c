#include "STabla.h"


#include "TiposBasicosConfig.h"




STabla * STabCrear ( int iNumFilas, int iNumColumnas )
{
	STabla * p_tabObj;
	
	if ( ( iNumFilas > 0 ) && ( iNumColumnas > 0 ) )
	{
		p_tabObj = (STabla *) MemReservar ( sizeof ( STabla ) );
		if ( ES_VALIDO ( p_tabObj ) )
		{
			p_tabObj->iNumFilas = iNumFilas;
			p_tabObj->iNumColumnas = iNumColumnas;
			p_tabObj->p_vecElementos = SVecCrear ( iNumFilas * iNumColumnas );
			if ( ES_NULO ( p_tabObj->p_vecElementos ) ) 
			{
				STabDestruir ( &p_tabObj );
			}
		}
	}
	else
	{
		p_tabObj = NULL;
	}
	return ( p_tabObj );
}

void STabDestruir ( STabla ** p_p_tabObj )
{
	STabla * p_tabObj;
	
	if ( ES_VALIDO ( p_p_tabObj ) )
	{
		p_tabObj = *p_p_tabObj;

		if ( ES_VALIDO ( p_tabObj ) )
		{
			SVecDestruir ( &(p_tabObj->p_vecElementos) );
			MemLiberar ( (void **) p_p_tabObj );
		}
	}
}

int STabEsValida ( STabla * p_tabObj )
{
	int iRes;

	if ( ES_VALIDO ( p_tabObj ) )
	{
		iRes = SVecEsValido ( p_tabObj->p_vecElementos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int STabNumFilas ( STabla * p_tabObj )
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

int STabNumColumnas ( STabla * p_tabObj )
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

int STabNumElementos ( STabla * p_tabObj )
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

SContenido * STabElemento ( STabla * p_tabObj, int iFila, int iColumna )
{
	int				iElem;
	SContenido *	p_conRes;

	if ( STabEsValida ( p_tabObj ) == 1 ) 
	{
		if ( ( iFila >= 0 ) && ( iFila < p_tabObj->iNumFilas ) &&
			 ( iColumna >= 0 ) && ( iColumna < p_tabObj->iNumColumnas ) )
		{
			iElem = iFila * p_tabObj->iNumColumnas + iColumna;
			p_conRes = SVecElemento ( p_tabObj->p_vecElementos, iElem );
		}
		else
		{
			p_conRes = NULL;
		}
	}
	else
	{
		p_conRes = NULL;
	}
	return ( p_conRes );
}

int STabAsignar ( STabla * p_tabObj, int iFila, int iColumna, SContenido * p_conElem )
{
	int	iElem;
	int	iRes;

	if ( STabEsValida ( p_tabObj ) == 1 ) 
	{
		if ( ( iFila >= 0 ) && ( iFila < p_tabObj->iNumFilas ) &&
			 ( iColumna >= 0 ) && ( iColumna < p_tabObj->iNumColumnas ) )
		{
			iElem = iFila * p_tabObj->iNumColumnas + iColumna;
			iRes = SVecAsignar ( p_tabObj->p_vecElementos, iElem, p_conElem );
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

int STabLimpiarElemento ( STabla * p_tabObj, int iFila, int iColumna )
{
	int	iElem;
	int iRes;			

	if ( STabEsValida ( p_tabObj ) == 1 ) 
	{
		if ( ( iFila >= 0 ) && ( iFila < p_tabObj->iNumFilas ) &&
			 ( iColumna >= 0 ) && ( iColumna < p_tabObj->iNumColumnas ) )
		{
			iElem = iFila * p_tabObj->iNumColumnas + iColumna;
			iRes = SVecLimpiarElemento ( p_tabObj->p_vecElementos, iElem );
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

int STabLimpiar ( STabla * p_tabObj )
{
	int	iRes;

	if ( ES_VALIDO ( p_tabObj ) )
	{
		iRes = SVecLimpiar ( p_tabObj->p_vecElementos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

SVector * STabVector ( STabla * p_tabObj )
{
	SVector * p_vecRes;

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
