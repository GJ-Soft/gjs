#include "SSecuenciaCadenas.h"

#include "TiposDatosConfig.h"



SSecuenciaCadenas * SSecCadCrear ()
{
	SSecuenciaCadenas * p_secObj;
	
	p_secObj = (SSecuenciaCadenas *) MemReservar ( sizeof ( SSecuenciaCadenas ) );
	if ( ES_VALIDO ( p_secObj ) )
	{
		p_secObj->p_secDatos = SSecpCrear ();
		if ( ES_VALIDO ( p_secObj->p_secDatos ) )
		{
			SSecpDesactivarLiberacionMemoria ( p_secObj->p_secDatos );
		}
		else
		{
			MemLiberar ( (void **) &p_secObj );
		}
	}
	return ( p_secObj );
}

void SSecCadDestruir ( SSecuenciaCadenas ** p_p_secObj )
{
	SSecuenciaCadenas * p_secObj;
	
	if ( ES_VALIDO ( p_p_secObj ) )
	{
		p_secObj = *p_p_secObj;

		if ( ES_VALIDO ( p_secObj ) )
		{
			SSecpDestruir ( &(p_secObj->p_secDatos) );
			MemLiberar ( (void **) p_p_secObj );
		}
	}
}

int SSecCadEsValida ( SSecuenciaCadenas * p_secObj )
{
	int iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		iRes = SSecpEsValida ( p_secObj->p_secDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SSecCadEstaVacia ( SSecuenciaCadenas * p_secObj )
{
	int iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		iRes = SSecpEstaVacia ( p_secObj->p_secDatos );
	}
	else
	{
		iRes = 1;
	}
	return ( iRes );
}

int SSecCadNumElementos ( SSecuenciaCadenas * p_secObj )
{
	int iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		iRes = SSecpNumElementos ( p_secObj->p_secDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

SCadena * SSecCadElemento ( SSecuenciaCadenas * p_secObj, int iElem )
{
	SCadena *	p_cRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		p_cRes = (SCadena *) SSecpElemento ( p_secObj->p_secDatos, iElem );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

int SSecCadInsertar ( SSecuenciaCadenas * p_secObj, SCadena * p_cadDatos )
{
	int	iRes;

	if ( ES_VALIDO ( p_secObj ) && ES_VALIDO ( p_cadDatos ) )
	{
		iRes = SSecpInsertar ( p_secObj->p_secDatos, (byte *) p_cadDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SSecCadInsertarDup ( SSecuenciaCadenas * p_secObj, SCadena * p_cadDatos )
{
	int			iRes;
	SCadena *	p_cadElem;

	if ( ES_VALIDO ( p_cadDatos ) )
	{
		p_cadElem = SCadDuplicar ( p_cadDatos );
		if ( ES_VALIDO ( p_cadElem ) )
		{
			iRes = SSecCadInsertar ( p_secObj, p_cadElem );
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

int SSecCadEliminar ( SSecuenciaCadenas * p_secObj, int iElem )
{
	int 		iRes;
	SCadena *	p_cadObj;

	if ( ES_VALIDO ( p_secObj ) )
	{
		p_cadObj = SSecCadElemento ( p_secObj, iElem );
		if ( ES_VALIDO ( p_cadObj ) ) 
		{
			iRes = SSecpEliminar ( p_secObj->p_secDatos, iElem );
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

int SSecCadVaciar ( SSecuenciaCadenas * p_secObj )
{
	int 		iRes;
	int 		iNumElems;
	SCadena *	p_cadObj;
	
	if ( ES_VALIDO ( p_secObj ) )
	{
		iNumElems = SSecCadNumElementos ( p_secObj );
		for ( int iElem = 0; iElem < iNumElems; iElem = iElem + 1 )
		{
			p_cadObj = SSecCadElemento ( p_secObj, iElem );
			SCadDestruir ( &p_cadObj );
		}
		iRes = SSecpVaciar ( p_secObj->p_secDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SSecCadExiste ( SSecuenciaCadenas * p_secObj, SCadena * p_cadDato )
{
	int iRes;
	int iElem;
	int	iNumElems;

	if ( ES_VALIDO ( p_secObj ) && ES_VALIDO ( p_cadDato )  ) 
	{
		iRes = 0;
		iElem = 0;
		iNumElems = SSecCadNumElementos ( p_secObj );
		while ( ( iElem < iNumElems ) && ( iRes == 0 ) )
		{
			if ( SCadEsIgual ( SSecCadElemento ( p_secObj, iElem ), p_cadDato ) == 1 )
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


