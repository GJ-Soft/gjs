#include "STablaLiterales.h"

#include "TiposBasicosConfig.h"



STablaLiterales * STabLitCrear ( int iNumFilas, int iNumColumnas )
{
	STablaLiterales * p_tabObj;
	
	if ( ( iNumFilas > 0 ) && ( iNumColumnas > 0 ) )
	{
		p_tabObj = (STablaLiterales *) MemReservar ( sizeof ( STablaLiterales ) );
		if ( ES_VALIDO ( p_tabObj ) )
		{
			p_tabObj->p_tabDatos = STabpCrear ( iNumFilas, iNumColumnas );
			if ( ES_VALIDO ( p_tabObj->p_tabDatos ) )
			{
				STabpActivarLiberacionMemoria ( p_tabObj->p_tabDatos );
			}
			else
			{
				STabLitDestruir ( &p_tabObj );
			}
		}
	}
	else
	{
		p_tabObj = NULL;
	}
	return ( p_tabObj );
}

void STabLitDestruir ( STablaLiterales ** p_p_tabObj )
{
	STablaLiterales * p_tabObj;
	
	if ( ES_VALIDO ( p_p_tabObj ) )
	{
		p_tabObj = *p_p_tabObj;

		if ( ES_VALIDO ( p_tabObj ) )
		{
			STabpDestruir ( &(p_tabObj->p_tabDatos) );
			MemLiberar ( (void **) p_p_tabObj );
		}
	}
}

int STabLitEsValida ( STablaLiterales * p_tabObj )
{
	int iRes;

	if ( ES_VALIDO ( p_tabObj ) )
	{
		iRes = STabpEsValida ( p_tabObj->p_tabDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int STabLitNumFilas ( STablaLiterales * p_tabObj )
{
	int iRes;

	if ( ES_VALIDO ( p_tabObj ) )
	{
		iRes = STabpNumFilas ( p_tabObj->p_tabDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int STabLitNumColumnas ( STablaLiterales * p_tabObj )
{
	int iRes;

	if ( ES_VALIDO ( p_tabObj ) )
	{
		iRes = STabpNumColumnas ( p_tabObj->p_tabDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int STabLitNumElementos ( STablaLiterales * p_tabObj )
{
	int iRes;

	if ( ES_VALIDO ( p_tabObj ) )
	{
		iRes = STabpNumElementos ( p_tabObj->p_tabDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

char * STabLitElemento ( STablaLiterales * p_tabObj, int iFila, int iColumna )
{
	char *	p_cRes;

	if ( ES_VALIDO ( p_tabObj ) )
	{
		p_cRes = (char *) STabpElemento ( p_tabObj->p_tabDatos, iFila, iColumna );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

int STabLitAsignar ( STablaLiterales * p_tabObj, int iFila, int iColumna, char * p_cDatos )
{
	int		iRes;

	if ( ES_VALIDO ( p_tabObj ) && ES_VALIDO ( p_cDatos ) )
	{
		iRes = STabpAsignar ( p_tabObj->p_tabDatos, iFila, iColumna, (byte *) p_cDatos );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int STabLitAsignarDup ( STablaLiterales * p_tabObj, int iFila, int iColumna, const char * p_cDatos )
{
	int		iRes;
	char *	p_cElem;
	int		iActLib;

	if ( ES_VALIDO ( p_tabObj ) && ES_VALIDO ( p_cDatos ) )
	{
		p_cElem = CadDuplicar ( p_cDatos );
		if ( ES_VALIDO ( p_cElem ) )
		{
			iActLib = STabpLiberacionMemoriaActivada ( p_tabObj->p_tabDatos );
			STabpActivarLiberacionMemoria ( p_tabObj->p_tabDatos );
			iRes = STabpAsignar ( p_tabObj->p_tabDatos, iFila, iColumna, (byte *) p_cElem );
			if ( iRes != 1 )
			{
				MemLiberar ( (void **) &p_cElem );
			}
			if ( iActLib == 0 )
			{
				STabpDesactivarLiberacionMemoria ( p_tabObj->p_tabDatos );
			}
		}
		else
		{
			iRes = -1;
		}
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int STabLitLimpiarElemento ( STablaLiterales * p_tabObj, int iFila, int iColumna )
{
	int iRes;

	if ( ES_VALIDO ( p_tabObj ) )
	{
		iRes = STabpLimpiarElemento ( p_tabObj->p_tabDatos, iFila, iColumna );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int STabLitLimpiar ( STablaLiterales * p_tabObj )
{
	int iRes;

	if ( ES_VALIDO ( p_tabObj ) )
	{
		iRes = STabpLimpiar ( p_tabObj->p_tabDatos );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int	STabLitLiberacionMemoriaActivada ( STablaLiterales * p_tabObj )
{
	int	iRes;

	if ( ES_VALIDO ( p_tabObj ) ) 
	{
		iRes = STabpLiberacionMemoriaActivada ( p_tabObj->p_tabDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

void STabLitActivarLiberacionMemoria ( STablaLiterales * p_tabObj )
{
	if ( ES_VALIDO ( p_tabObj ) ) 
	{
		STabpActivarLiberacionMemoria ( p_tabObj->p_tabDatos );
	}
}

void STabLitDesactivarLiberacionMemoria ( STablaLiterales * p_tabObj )
{
	if ( ES_VALIDO ( p_tabObj ) ) 
	{
		STabpDesactivarLiberacionMemoria ( p_tabObj->p_tabDatos );
	}
}

int STabLitExiste ( STablaLiterales * p_tabObj, const char * p_cDato )
{
	int iRes;
	int iFila;
	int iColumna;

	if ( ES_VALIDO ( p_tabObj ) && ES_VALIDO ( p_cDato )  ) 
	{
		iRes = 0;
		iFila = 0;
		while ( ( iFila < STabLitNumFilas ( p_tabObj ) ) && ( iRes == 0 ) )
		{
			iColumna = 0;
			while ( ( iColumna < STabLitNumColumnas ( p_tabObj ) ) && ( iRes == 0 ) )
			{
				if ( CadComparar ( STabLitElemento ( p_tabObj, iFila, iColumna ), p_cDato ) == COMP_IGUAL )
				{
					iRes = 1;
				}
				iColumna = iColumna + 1;
			}
			iFila = iFila + 1;
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

