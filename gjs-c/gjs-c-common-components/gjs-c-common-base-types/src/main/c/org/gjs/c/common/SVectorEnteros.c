#include "SVectorEnteros.h"

#include "TiposBasicosConfig.h"




SVectorEnteros * SVecIntCrear ( int iNumElementos )
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
				SVecIntDestruir ( &p_vecObj );
			}
		}
	}
	else
	{
		p_vecObj = NULL;
	}
	return ( p_vecObj );
}

/* Vector de iNumValores posiciones con los primeros valores de p_iValores,
   en orden. NULL si el vector es nulo, el numero no es positivo (un vector no
   tiene 0 posiciones) o falla alguna asignacion. */
SVectorEnteros * SVecIntCrearDesdeVector ( const int * p_iValores, int iNumValores )
{
	SVectorEnteros *	p_vecRes;
	int		iPos;
	int		iError;

	if ( ES_VALIDO ( p_iValores ) )
	{
		p_vecRes = SVecIntCrear ( iNumValores );
		if ( ES_VALIDO ( p_vecRes ) )
		{
			iError = 0;
			iPos = 0;
			while ( ( iError == 0 ) && ( iPos < iNumValores ) )
			{
				if ( SVecIntAsignar ( p_vecRes, iPos, p_iValores [ iPos ] ) == 1 )
				{
					iPos = iPos + 1;
				}
				else
				{
					iError = 1;
				}
			}
			if ( iError == 1 )
			{
				SVecIntDestruir ( &p_vecRes );
			}
		}
	}
	else
	{
		p_vecRes = NULL;
	}
	return ( p_vecRes );
}

void SVecIntDestruir ( SVectorEnteros ** p_p_vecObj )
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

int SVecIntEsValido ( SVectorEnteros * p_vecObj )
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

int SVecIntNumElementos ( SVectorEnteros * p_vecObj )
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

int SVecIntElemento ( SVectorEnteros * p_vecObj, int iElem )
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

int SVecIntAsignar ( SVectorEnteros * p_vecObj, int iElem, int iDato )
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

int SVecIntInicializar ( SVectorEnteros * p_vecObj )
{
	int iRes;
	int iElem;
	int iNumElems;

	if ( ES_VALIDO ( p_vecObj ) )
	{
		iRes = 1;
		iElem = 0;
		iNumElems = SVecIntNumElementos ( p_vecObj );
		while ( ( iElem < iNumElems ) && ( iRes == 1 ) )
		{
			iRes = SVecIntAsignar ( p_vecObj, iElem, 0 );
			iElem = iElem + 1;
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SVecIntExiste ( SVectorEnteros * p_vecObj, int iDato )
{
	int iRes;
	int iElem;
	int iNumElems;

	if ( ES_VALIDO ( p_vecObj )  ) 
	{
		iRes = 0;
		iElem = 0;
		iNumElems = SVecIntNumElementos ( p_vecObj );
		while ( ( iElem < iNumElems ) && ( iRes == 0 ) )
		{
			if ( SVecIntElemento ( p_vecObj, iElem ) == iDato )
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
