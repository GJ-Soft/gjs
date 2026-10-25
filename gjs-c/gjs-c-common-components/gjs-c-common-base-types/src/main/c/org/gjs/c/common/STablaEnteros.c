#include "STablaEnteros.h"

#include "TiposBasicosConfig.h"




STablaEnteros * STabIntCrear ( int iNumFilas, int iNumColumnas )
{
	STablaEnteros * p_tabObj;
	
	if ( ( iNumFilas > 0 ) && ( iNumColumnas > 0 ) )
	{
		p_tabObj = (STablaEnteros *) MemReservar ( sizeof ( STablaEnteros ) );
		if ( ES_VALIDO ( p_tabObj ) )
		{
			p_tabObj->p_tabDatos = STabCrear ( iNumFilas, iNumColumnas );
			if ( ES_NULO ( p_tabObj->p_tabDatos ) )
			{
				STabIntDestruir ( &p_tabObj );
			}
		}
	}
	else
	{
		p_tabObj = NULL;
	}
	return ( p_tabObj );
}

void STabIntDestruir ( STablaEnteros ** p_p_tabObj )
{
	STablaEnteros * p_tabObj;
	
	if ( ES_VALIDO ( p_p_tabObj ) )
	{
		p_tabObj = *p_p_tabObj;

		if ( ES_VALIDO ( p_tabObj ) )
		{
			STabDestruir ( &(p_tabObj->p_tabDatos) );
			MemLiberar ( (void **) p_p_tabObj );
		}
	}
}

int STabIntEsValida ( STablaEnteros * p_tabObj )
{
	int iRes;

	if ( ES_VALIDO ( p_tabObj ) )
	{
		iRes = STabEsValida ( p_tabObj->p_tabDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int STabIntNumFilas ( STablaEnteros * p_tabObj )
{
	int iRes;

	if ( ES_VALIDO ( p_tabObj ) )
	{
		iRes = STabNumFilas ( p_tabObj->p_tabDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int STabIntNumColumnas ( STablaEnteros * p_tabObj )
{
	int iRes;

	if ( ES_VALIDO ( p_tabObj ) )
	{
		iRes = STabNumColumnas ( p_tabObj->p_tabDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int STabIntNumElementos ( STablaEnteros * p_tabObj )
{
	int iRes;

	if ( ES_VALIDO ( p_tabObj ) )
	{
		iRes = STabNumElementos ( p_tabObj->p_tabDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int STabIntElemento ( STablaEnteros * p_tabObj, int iFila, int iColumna )
{
	int			iRes;
	SContenido *	p_conObj;

	if ( ES_VALIDO ( p_tabObj ) )
	{
		p_conObj = STabElemento ( p_tabObj->p_tabDatos, iFila, iColumna );
		if ( ES_VALIDO ( p_conObj ) )
		{
			iRes = SConEntero ( p_conObj );
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

int STabIntAsignar ( STablaEnteros * p_tabObj, int iFila, int iColumna, int iDato )
{
	int				iRes;
	SContenido *	p_conObj;
	int				iCreado;

	if ( ES_VALIDO ( p_tabObj ) )
	{
		if ( ( iFila >= 0 ) && ( iFila < STabNumFilas ( p_tabObj->p_tabDatos ) ) &&
			 ( iColumna >= 0 ) && ( iColumna < STabNumColumnas ( p_tabObj->p_tabDatos ) ) )
		{
			p_conObj = STabElemento ( p_tabObj->p_tabDatos, iFila, iColumna );
			if ( ES_NULO ( p_conObj ) )
			{
				iCreado = 1;
				p_conObj = SConCrearEntero ();
			}
			else
			{
				iCreado = 0;
			}
			if ( ES_VALIDO ( p_conObj ) )
			{
				if ( SConEscribirEntero ( p_conObj, iDato ) == 1 )
				{
					if ( iCreado == 1 )
					{
						iRes = STabAsignar ( p_tabObj->p_tabDatos, iFila, iColumna, p_conObj );
					}
					else
					{
						iRes = 1;
					}
				}
				else
				{
					iRes = 0;
				}
				if ( ( iCreado == 1 ) && ( iRes != 1 ) )
				{
					SConDestruir ( &p_conObj );
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
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int STabIntInicializar ( STablaEnteros * p_tabObj )
{
	int iRes;
	int iFila;
	int iColumna;

	if ( ES_VALIDO ( p_tabObj ) )
	{
		iRes = 1;
		iFila = 0;
		while ( ( iFila < STabIntNumFilas ( p_tabObj ) ) && ( iRes == 1 ) )
		{
			iColumna = 0;
			while ( ( iColumna < STabIntNumColumnas ( p_tabObj ) ) && ( iRes == 1 ) )
			{
				iRes = STabIntAsignar ( p_tabObj, iFila, iColumna, 0 );
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

int STabIntExiste ( STablaEnteros * p_tabObj, int iDato )
{
	int iRes;
	int iFila;
	int iColumna;

	if ( ES_VALIDO ( p_tabObj ) ) 
	{
		iRes = 0;
		iFila = 0;
		while ( ( iFila < STabIntNumFilas ( p_tabObj ) ) && ( iRes == 0 ) )
		{
			iColumna = 0;
			while ( ( iColumna < STabIntNumColumnas ( p_tabObj ) ) && ( iRes == 0 ) )
			{
				if ( STabIntElemento ( p_tabObj, iFila, iColumna ) == iDato )
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
