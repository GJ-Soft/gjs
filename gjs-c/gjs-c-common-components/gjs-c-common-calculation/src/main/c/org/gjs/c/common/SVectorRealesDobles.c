#include "SVectorRealesDobles.h"

#include "CalculoConfig.h"
#include "CalculoOperaciones.h"



SVectorRealesDobles * SVecRealdCrear ( int iNumElementos )
{
	SVectorRealesDobles * p_vecObj;
	
	if ( iNumElementos > 0 )
	{
		p_vecObj = (SVectorRealesDobles *) MemReservar ( sizeof ( SVectorRealesDobles ) );
		if ( ES_VALIDO ( p_vecObj ) )
		{
			p_vecObj->p_vecDatos = SVecCrear ( iNumElementos );
			if ( ES_NULO ( p_vecObj->p_vecDatos ) )
			{
				SVecRealdDestruir ( &p_vecObj );
			}
		}
	}
	else
	{
		p_vecObj = NULL;
	}
	return ( p_vecObj );
}

/* Vector de iNumValores posiciones con los primeros valores de p_dValores,
   en orden. NULL si el vector es nulo, el numero no es positivo (un vector no
   tiene 0 posiciones) o falla alguna asignacion. */
SVectorRealesDobles * SVecRealdCrearDesdeVector ( const double * p_dValores, int iNumValores )
{
	SVectorRealesDobles *	p_vecRes;
	int						iPos;
	int						iError;

	if ( ES_VALIDO ( p_dValores ) )
	{
		p_vecRes = SVecRealdCrear ( iNumValores );
		if ( ES_VALIDO ( p_vecRes ) )
		{
			iError = 0;
			iPos = 0;
			while ( ( iError == 0 ) && ( iPos < iNumValores ) )
			{
				if ( SVecRealdAsignar ( p_vecRes, iPos, p_dValores [ iPos ] ) == 1 )
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
				SVecRealdDestruir ( &p_vecRes );
			}
		}
	}
	else
	{
		p_vecRes = NULL;
	}
	return ( p_vecRes );
}

void SVecRealdDestruir ( SVectorRealesDobles ** p_p_vecObj )
{
	SVectorRealesDobles * p_vecObj;
	
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

int SVecRealdEsValido ( SVectorRealesDobles * p_vecObj )
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

int SVecRealdNumElementos ( SVectorRealesDobles * p_vecObj )
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

double SVecRealdElemento ( SVectorRealesDobles * p_vecObj, int iElem )
{
	double			dRes;
	SContenido *	p_conObj;

	if ( ES_VALIDO ( p_vecObj ) )
	{
		p_conObj = SVecElemento ( p_vecObj->p_vecDatos, iElem );
		if ( ES_VALIDO ( p_conObj ) )
		{
			dRes = SConRealDoble ( p_conObj );
		}
		else
		{
			dRes = 0;
		}
	}
	else
	{
		dRes = 0;
	}
	return ( dRes );
}

int SVecRealdAsignar ( SVectorRealesDobles * p_vecObj, int iElem, double dDato )
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
				p_conObj = SConCrearRealDoble ();
			}
			else
			{
				iCreado = 0;
			}
			if ( ES_VALIDO ( p_conObj ) )
			{
				if ( SConEscribirRealDoble ( p_conObj, dDato ) == 1 )
				{
					iRes = SVecAsignar ( p_vecObj->p_vecDatos, iElem, p_conObj );
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

int SVecRealdInicializar ( SVectorRealesDobles * p_vecObj )
{
	int iRes;
	int iElem;
	int iNumElems;

	if ( ES_VALIDO ( p_vecObj ) )
	{
		iRes = 1;
		iElem = 0;
		iNumElems = SVecRealdNumElementos ( p_vecObj );
		while ( ( iElem < iNumElems ) && ( iRes == 1 ) )
		{
			iRes = SVecRealdAsignar ( p_vecObj, iElem, 0 );
			iElem = iElem + 1;
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SVecRealdExiste ( SVectorRealesDobles * p_vecObj, double dDato )
{
	int iRes;
	int iElem;
	int iNumElems;

	if ( ES_VALIDO ( p_vecObj ) ) 
	{
		iRes = 0;
		iElem = 0;
		iNumElems = SVecRealdNumElementos ( p_vecObj );
		while ( ( iElem < iNumElems ) && ( iRes == 0 ) )
		{
			if ( MatEsIgual ( SVecRealdElemento ( p_vecObj, iElem ), dDato ) )
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
