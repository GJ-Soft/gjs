#include "SVectorEnteros.h"

#include "TiposBasicosConfig.h"




SVectorEnteros * SVecEntCrear ( int iNumElementos )
{
	SVectorEnteros * p_vecObj;
	
	if ( iNumElementos > 0 )
	{
		p_vecObj = (SVectorEnteros *) MemReservar ( sizeof ( SVectorEnteros ) );
		if ( ES_VALIDO ( p_vecObj ) )
		{
			p_vecObj->p_vecDatos = SVecCrear ( iNumElementos );
			if ( ES_NULO ( p_vecObj->p_vecDatos ) )
			{
				SVecEntDestruir ( &p_vecObj );
			}
		}
	}
	else
	{
		p_vecObj = NULL;
	}
	return ( p_vecObj );
}

void SVecEntDestruir ( SVectorEnteros ** p_p_vecObj )
{
	SVectorEnteros * p_vecObj;
	
	if ( ES_VALIDO ( p_p_vecObj ) )
	{
		p_vecObj = *p_p_vecObj;

		if ( ES_VALIDO ( p_vecObj ) )
		{
			SVecDestruir ( &(p_vecObj->p_vecDatos) );
			MemLiberar ( (void **) p_p_vecObj );
		}
	}
}

int SVecEntEsValido ( SVectorEnteros * p_vecObj )
{
	int iRes;

	if ( ES_VALIDO ( p_vecObj ) )
	{
		iRes = SVecEsValido ( p_vecObj->p_vecDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SVecEntNumElementos ( SVectorEnteros * p_vecObj )
{
	int iRes;

	if ( ES_VALIDO ( p_vecObj ) )
	{
		iRes = SVecNumElementos ( p_vecObj->p_vecDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SVecEntElemento ( SVectorEnteros * p_vecObj, int iElem )
{
	int				iRes;
	SContenido *	p_conObj;

	if ( ES_VALIDO ( p_vecObj ) )
	{
		p_conObj = SVecElemento ( p_vecObj->p_vecDatos, iElem );
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

int SVecEntAsignar ( SVectorEnteros * p_vecObj, int iElem, int iDato )
{
	int				iRes;
	SContenido *	p_conObj;
	int				iCreado;

	if ( ES_VALIDO ( p_vecObj ) )
	{
		if ( ( iElem >= 0 ) && ( iElem < SVecNumElementos ( p_vecObj->p_vecDatos ) ) )
		{
			p_conObj = SVecElemento ( p_vecObj->p_vecDatos, iElem );
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
						iRes = SVecAsignar ( p_vecObj->p_vecDatos, iElem, p_conObj );
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

int SVecEntInicializar ( SVectorEnteros * p_vecObj )
{
	int iRes;
	int iElem;
	int iNumElems;

	if ( ES_VALIDO ( p_vecObj ) )
	{
		iRes = 1;
		iElem = 0;
		iNumElems = SVecEntNumElementos ( p_vecObj );
		while ( ( iElem < iNumElems ) && ( iRes == 1 ) )
		{
			iRes = SVecEntAsignar ( p_vecObj, iElem, 0 );
			iElem = iElem + 1;
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SVecEntExiste ( SVectorEnteros * p_vecObj, int iDato )
{
	int iRes;
	int iElem;
	int iNumElems;

	if ( ES_VALIDO ( p_vecObj )  ) 
	{
		iRes = 0;
		iElem = 0;
		iNumElems = SVecEntNumElementos ( p_vecObj );
		while ( ( iElem < iNumElems ) && ( iRes == 0 ) )
		{
			if ( SVecEntElemento ( p_vecObj, iElem ) == iDato )
			{
				iRes = 1;
			}
			iElem = iElem + 1;
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}
