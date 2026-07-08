#include "SVectorCadenas.h"

#include "TiposDatosConfig.h"



SVectorCadenas * SVecCadCrear ( int iNumElementos )
{
	SVectorCadenas * p_vecObj;
	
	if ( iNumElementos > 0 )
	{
		p_vecObj = (SVectorCadenas *) MemReservar ( sizeof ( SVectorCadenas ) );
		if ( ES_VALIDO ( p_vecObj ) )
		{
			p_vecObj->p_vecDatos = SVecpCrear ( iNumElementos );
			if ( ES_VALIDO ( p_vecObj->p_vecDatos ) )
			{
				SVecpDesactivarLiberacionMemoria ( p_vecObj->p_vecDatos );
			}
			else
			{
				MemLiberar ( (void **) &p_vecObj );
			}
		}
	}
	else
	{
		p_vecObj = NULL;
	}
	return ( p_vecObj );
}

void SVecCadDestruir ( SVectorCadenas ** p_p_vecObj )
{
	SVectorCadenas * p_vecObj;
	
	if ( ES_VALIDO ( p_p_vecObj ) )
	{
		p_vecObj = *p_p_vecObj;

		if ( ES_VALIDO ( p_vecObj ) )
		{
			SVecpDestruir ( &(p_vecObj->p_vecDatos) );
			MemLiberar ( (void **) p_p_vecObj );
		}
	}
}

int SVecCadEsValido ( SVectorCadenas * p_vecObj )
{
	int iRes;

	if ( ES_VALIDO ( p_vecObj ) )
	{
		iRes = SVecpEsValido ( p_vecObj->p_vecDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SVecCadNumElementos ( SVectorCadenas * p_vecObj )
{
	int iRes;

	if ( ES_VALIDO ( p_vecObj ) )
	{
		iRes = SVecpNumElementos ( p_vecObj->p_vecDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

SCadena * SVecCadElemento ( SVectorCadenas * p_vecObj, int iElem )
{
	SCadena *	p_cRes;

	if ( ES_VALIDO ( p_vecObj ) )
	{
		p_cRes = (SCadena *) SVecpElemento ( p_vecObj->p_vecDatos, iElem );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

int SVecCadAsignar ( SVectorCadenas * p_vecObj, int iElem, SCadena * p_cadDato )
{
	int		iRes;

	if ( ES_VALIDO ( p_vecObj ) && ES_VALIDO ( p_cadDato ) )
	{
		iRes = SVecpAsignar ( p_vecObj->p_vecDatos, iElem, (byte *) p_cadDato );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SVecCadAsignarDup ( SVectorCadenas * p_vecObj, int iElem, SCadena * p_cadDato )
{
	int			iRes;
	SCadena *	p_cadElem;

	if ( ES_VALIDO ( p_cadDato ) )
	{
		p_cadElem = SCadDuplicar ( p_cadDato );
		if ( ES_VALIDO ( p_cadElem ) )
		{
			iRes = SVecCadAsignar ( p_vecObj, iElem, p_cadElem );
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

int SVecCadLimpiarElemento ( SVectorCadenas * p_vecObj, int iElem )
{
	int 		iRes;
	SCadena *	p_cadObj;

	if ( ES_VALIDO ( p_vecObj ) )
	{
		p_cadObj = SVecCadElemento ( p_vecObj, iElem );
		if ( ES_VALIDO ( p_cadObj ) ) 
		{
			iRes = SVecpLimpiarElemento ( p_vecObj->p_vecDatos, iElem );
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

int SVecCadLimpiar ( SVectorCadenas * p_vecObj )
{
	int 		iRes;
	int 		iNumElems;
	SCadena *	p_cadObj;

	if ( ES_VALIDO ( p_vecObj ) )
	{
		iNumElems = SVecCadNumElementos ( p_vecObj );
		for ( int iElem = 0; iElem < iNumElems; iElem = iElem + 1 )
		{
			p_cadObj = SVecCadElemento ( p_vecObj, iElem );
			SCadDestruir ( &p_cadObj );
		}
		iRes = SVecpLimpiar ( p_vecObj->p_vecDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SVecCadExiste ( SVectorCadenas * p_vecObj, SCadena * p_cadDato )
{
	int iRes;
	int iElem;
	int iNumElems;

	if ( ES_VALIDO ( p_vecObj ) && ES_VALIDO ( p_cadDato )  ) 
	{
		iRes = 0;
		iElem = 0;
		iNumElems = SVecCadNumElementos ( p_vecObj );
		while ( ( iElem < iNumElems ) && ( iRes == 0 ) )
		{
			if ( SCadEsIgual ( SVecCadElemento ( p_vecObj, iElem ), p_cadDato ) == 1 )
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
