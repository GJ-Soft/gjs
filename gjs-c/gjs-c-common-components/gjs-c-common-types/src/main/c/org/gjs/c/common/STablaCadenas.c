#include "STablaCadenas.h"

#include "TiposDatosConfig.h"



STablaCadenas * STabCadCrear ( int iNumFilas, int iNumColumnas )
{
	STablaCadenas * p_tabObj;
	
	if ( ( iNumFilas > 0 ) && ( iNumColumnas > 0 ) )
	{
		p_tabObj = (STablaCadenas *) MemReservar ( sizeof ( STablaCadenas ) );
		if ( ES_VALIDO ( p_tabObj ) )
		{
			p_tabObj->p_tabDatos = STabpCrear ( iNumFilas, iNumColumnas );
			if ( ES_VALIDO ( p_tabObj->p_tabDatos ) )
			{
				STabpDesactivarLiberacionMemoria ( p_tabObj->p_tabDatos );
			}
			else
			{
				MemLiberar ( (void **) &p_tabObj );
			}
		}
	}
	else
	{
		p_tabObj = NULL;
	}
	return ( p_tabObj );
}

void STabCadDestruir ( STablaCadenas ** p_p_tabObj )
{
	STablaCadenas * p_tabObj;
	
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

int STabCadEsValida ( STablaCadenas * p_tabObj )
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

int STabCadNumFilas ( STablaCadenas * p_tabObj )
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

int STabCadNumColumnas ( STablaCadenas * p_tabObj )
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

int STabCadNumElementos ( STablaCadenas * p_tabObj )
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

SCadena * STabCadElemento ( STablaCadenas * p_tabObj, int iFila, int iColumna )
{
	SCadena *	p_cRes;

	if ( ES_VALIDO ( p_tabObj ) )
	{
		p_cRes = (SCadena *) STabpElemento ( p_tabObj->p_tabDatos, iFila, iColumna );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

int STabCadAsignar ( STablaCadenas * p_tabObj, int iFila, int iColumna, SCadena * p_cadDatos )
{
	int		iRes;

	if ( ES_VALIDO ( p_tabObj ) && ES_VALIDO ( p_cadDatos ) )
	{
		iRes = STabpAsignar ( p_tabObj->p_tabDatos, iFila, iColumna, (byte *) p_cadDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int STabCadAsignarDup ( STablaCadenas * p_tabObj, int iFila, int iColumna, SCadena * p_cadDatos )
{
	int			iRes;
	SCadena *	p_cadElem;

	if ( ES_VALIDO ( p_cadDatos ) )
	{
		p_cadElem = SCadDuplicar ( p_cadDatos );
		if ( ES_VALIDO ( p_cadElem ) )
		{
			iRes = STabCadAsignar ( p_tabObj, iFila, iColumna, p_cadElem );
			if ( iRes != 1 )
			{
				SCadDestruir ( &p_cadElem );
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

int STabCadLimpiarElemento ( STablaCadenas * p_tabObj, int iFila, int iColumna )
{
	SCadena *	p_cadObj;
	int 		iRes;

	if ( ES_VALIDO ( p_tabObj ) )
	{
		p_cadObj = STabCadElemento ( p_tabObj, iFila, iColumna );
		if ( ES_VALIDO ( p_cadObj ) ) 
		{
			iRes = STabpLimpiarElemento ( p_tabObj->p_tabDatos, iFila, iColumna );
			if ( iRes == 1 )
			{
				SCadDestruir ( &p_cadObj );	
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

int STabCadLimpiar ( STablaCadenas * p_tabObj )
{
	int 		iRes;
	SCadena *	p_cadObj;

	if ( ES_VALIDO ( p_tabObj ) )
	{
		for ( int iFila = 0; iFila < STabCadNumFilas ( p_tabObj ); iFila = iFila + 1 )
		{
			for ( int iColumna = 0; iColumna < STabCadNumColumnas ( p_tabObj ); iColumna = iColumna + 1 )
			{
				p_cadObj = STabCadElemento ( p_tabObj, iFila, iColumna );
				SCadDestruir ( &p_cadObj );
			}
		}
		iRes = STabpLimpiar ( p_tabObj->p_tabDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int STabCadExiste ( STablaCadenas * p_tabObj, SCadena * p_cadDato )
{
	int iRes;
	int iFila;
	int iColumna;

	if ( ES_VALIDO ( p_tabObj ) && ES_VALIDO ( p_cadDato )  ) 
	{
		iRes = 0;
		iRes = 0;
		iFila = 0;
		while ( ( iFila < STabCadNumFilas ( p_tabObj ) ) && ( iRes == 0 ) )
		{
			iColumna = 0;
			while ( ( iColumna < STabCadNumColumnas ( p_tabObj ) ) && ( iRes == 0 ) )
			{
				if ( SCadEsIgual ( STabCadElemento ( p_tabObj, iFila, iColumna ), p_cadDato ) == 1 )
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

