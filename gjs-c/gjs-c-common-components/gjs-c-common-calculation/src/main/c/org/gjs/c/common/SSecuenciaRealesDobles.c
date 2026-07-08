#include "SSecuenciaRealesDobles.h"

#include "CalculoConfig.h"
#include "CalculoOperaciones.h"



SSecuenciaRealesDobles * SSecRealdCrear ()
{
	SSecuenciaRealesDobles * p_secObj;
	
	p_secObj = (SSecuenciaRealesDobles *) MemReservar ( sizeof ( SSecuenciaRealesDobles ) );
	if ( ES_VALIDO ( p_secObj ) )
	{
		p_secObj->p_secDatos = SSecCrear ();
	}
	return ( p_secObj );
}

void SSecRealdDestruir ( SSecuenciaRealesDobles ** p_p_secObj )
{
	SSecuenciaRealesDobles * p_secObj;
	
	if ( ES_VALIDO ( p_p_secObj ) )
	{
		p_secObj = *p_p_secObj;

		if ( ES_VALIDO ( p_secObj ) )
		{
			SSecDestruir ( &(p_secObj->p_secDatos) );
			MemLiberar ( (void **) p_p_secObj );
		}
	}
}

int SSecRealdEsValida ( SSecuenciaRealesDobles * p_secObj )
{
	int iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		iRes = SSecEsValida ( p_secObj->p_secDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SSecRealdEstaVacia ( SSecuenciaRealesDobles * p_secObj )
{
	int iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		iRes = SSecEstaVacia ( p_secObj->p_secDatos );
	}
	else
	{
		iRes = 1;
	}
	return ( iRes );
}

int SSecRealdNumElementos ( SSecuenciaRealesDobles * p_secObj )
{
	int iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		iRes = SSecNumElementos ( p_secObj->p_secDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

double SSecRealdElemento ( SSecuenciaRealesDobles * p_secObj, int iElem )
{
	double		dRes;
	SElemento *	p_elmObj;

	if ( ES_VALIDO ( p_secObj ) )
	{
		p_elmObj = SSecElemento ( p_secObj->p_secDatos, iElem );
		if ( ES_VALIDO ( p_elmObj ) )
		{
			dRes = SElmRealDoble ( p_elmObj );
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

int SSecRealdInsertar ( SSecuenciaRealesDobles * p_secObj, double dDato )
{
	int			iRes;
	SElemento *	p_elmObj;

	if ( ES_VALIDO ( p_secObj ) )
	{
		p_elmObj = SElmCrearRealDoble ();
		if ( ES_VALIDO ( p_elmObj ) )
		{
			if ( SElmEscribirRealDoble ( p_elmObj, dDato ) == 1 )
			{
				iRes = SSecInsertar ( p_secObj->p_secDatos, p_elmObj );
			}
			else
			{
				iRes = -1;
			}
			if ( iRes != 1 )
			{
				SElmDestruir ( &p_elmObj );
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

int SSecRealdModificar ( SSecuenciaRealesDobles * p_secObj, int iElem, double dDato )
{
	int			iRes;
	SElemento *	p_elmObj;

	if ( ES_VALIDO ( p_secObj ) )
	{
		p_elmObj = SSecElemento ( p_secObj->p_secDatos, iElem );
		if ( ES_VALIDO ( p_elmObj ) )
		{
			iRes = SElmEscribirRealDoble ( p_elmObj, dDato );
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

int SSecRealdEliminar ( SSecuenciaRealesDobles * p_secObj, int iElem )
{
	int iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		iRes = SSecEliminar ( p_secObj->p_secDatos, iElem );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SSecRealdVaciar ( SSecuenciaRealesDobles * p_secObj )
{
	int iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		iRes = SSecVaciar ( p_secObj->p_secDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SSecRealdExiste ( SSecuenciaRealesDobles * p_secObj, double dDato )
{
	int iRes;
	int iElem;
	int iNumElems;

	if ( ES_VALIDO ( p_secObj ) ) 
	{
		iRes = 0;
		iElem = 0;
		iNumElems = SSecRealdNumElementos ( p_secObj );
		while ( ( iElem < iNumElems ) && ( iRes == 0 ) )
		{
			if ( MatEsIgual ( SSecRealdElemento ( p_secObj, iElem ), dDato ) == 1 )
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

