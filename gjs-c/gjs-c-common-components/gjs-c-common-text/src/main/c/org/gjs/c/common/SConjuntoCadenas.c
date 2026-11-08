#include "SConjuntoCadenas.h"
          
#include "TextoConfig.h"


static int _SCadComparar ( void * p_vVal1, void * p_vVal2 )
{
	int 		iRes;
	SCadena * 	p_cadVal1 = (SCadena *) p_vVal1;
	SCadena * 	p_cadVal2 = (SCadena *) p_vVal2;
	iRes = SCadComparar ( p_cadVal1, p_cadVal2 );
	if ( iRes == COMP_MENOR ) 
	{
		iRes = -1;
	}
	else if ( iRes == COMP_MAYOR ) 
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}


SConjuntoCadenas * SCnjCadCrear ()
{
	SConjuntoCadenas * p_cnjObj;
	
	p_cnjObj = (SConjuntoCadenas *) MemReservar ( sizeof ( SConjuntoCadenas ) );
	if ( ES_VALIDO ( p_cnjObj ) )
	{
		p_cnjObj->p_cnjDatos = SCnjpCrear ( _SCadComparar );
		SCnjpDesactivarLiberacionMemoria ( p_cnjObj->p_cnjDatos );
	}
	return ( p_cnjObj );
}

void SCnjCadDestruir ( SConjuntoCadenas ** p_p_cnjObj )
{
	SConjuntoCadenas * p_cnjObj;
	
	if ( ES_VALIDO ( p_p_cnjObj ) )
	{
		p_cnjObj = *p_p_cnjObj;

		if ( ES_VALIDO ( p_cnjObj ) )
		{
			SCnjCadVaciar ( p_cnjObj );
			SCnjpDestruir ( &(p_cnjObj->p_cnjDatos) );
			MemLiberar ( (void **) p_p_cnjObj );
		}
	}
}

int SCnjCadEsValido ( SConjuntoCadenas * p_cnjObj )
{
	int iRes;

	if ( ES_VALIDO ( p_cnjObj ) )
	{
		iRes = SCnjpEsValido ( p_cnjObj->p_cnjDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCnjCadEstaVacio ( SConjuntoCadenas * p_cnjObj )
{
	int iRes;

	if ( ES_VALIDO ( p_cnjObj ) )
	{
		iRes = SCnjpEstaVacio ( p_cnjObj->p_cnjDatos );
	}
	else
	{
		iRes = 1;
	}
	return ( iRes );
}

int SCnjCadNumElementos ( SConjuntoCadenas * p_cnjObj )
{
	int iRes;

	if ( ES_VALIDO ( p_cnjObj ) )
	{
		iRes = SCnjpNumElementos ( p_cnjObj->p_cnjDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

SCadena * SCnjCadElemento ( SConjuntoCadenas * p_cnjObj, int iElem )
{
	SCadena *	p_cRes;

	if ( ES_VALIDO ( p_cnjObj ) )
	{
		p_cRes = (SCadena *) SCnjpElemento ( p_cnjObj->p_cnjDatos, iElem );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

SCadena * SCnjCadPrimero ( SConjuntoCadenas * p_cnjObj )
{
	SCadena * p_cRes;

	if ( ES_VALIDO ( p_cnjObj ) )
	{
		p_cRes = (SCadena *) SCnjpPrimero ( p_cnjObj->p_cnjDatos );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

SCadena * SCnjCadUltimo ( SConjuntoCadenas * p_cnjObj )
{
	SCadena * p_cRes;

	if ( ES_VALIDO ( p_cnjObj ) )
	{
		p_cRes = (SCadena *) SCnjpUltimo ( p_cnjObj->p_cnjDatos );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

int SCnjCadPosicion ( SConjuntoCadenas * p_cnjObj, SCadena * p_cadDato )
{
	int iRes;

	if ( ES_VALIDO ( p_cnjObj ) )
	{
		iRes = SCnjpPosicion ( p_cnjObj->p_cnjDatos, (byte *) p_cadDato );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int SCnjCadInsertar ( SConjuntoCadenas * p_cnjObj, SCadena * p_cadDato )
{
	int		iRes;

	if ( ES_VALIDO ( p_cnjObj ) && ES_VALIDO ( p_cadDato ) )
	{
		iRes = SCnjpInsertarElem ( p_cnjObj->p_cnjDatos, (byte *) p_cadDato );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int SCnjCadInsertarDup ( SConjuntoCadenas * p_cnjObj, SCadena * p_cadDato )
{
	int			iRes;
	SCadena *	p_cadElem;

	if ( ES_VALIDO ( p_cnjObj ) && ES_VALIDO ( p_cadDato ) )
	{
		p_cadElem = SCadDuplicar ( p_cadDato );
		if ( ES_VALIDO ( p_cadElem ) )
		{
			iRes = SCnjpInsertarElem ( p_cnjObj->p_cnjDatos, (byte *) p_cadElem );
			if ( iRes != 1 )
			{
				SCadDestruir ( &p_cadElem );
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

int SCnjCadEliminar ( SConjuntoCadenas * p_cnjObj, int iElem )
{
	int 		iRes;
	SCadena * 	p_cadObj;

	if ( ES_VALIDO ( p_cnjObj ) )
	{
		p_cadObj = SCnjCadElemento ( p_cnjObj, iElem );
		if ( ES_VALIDO ( p_cadObj ) )
		{
			iRes = SCnjpEliminarElem ( p_cnjObj->p_cnjDatos, iElem );
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

SCadena * SCnjCadExtraer ( SConjuntoCadenas * p_cnjObj, int iElem )
{
	SCadena * 	p_cadRes;

	if ( ES_VALIDO ( p_cnjObj ) )
	{
		p_cadRes = SCnjCadElemento ( p_cnjObj, iElem );
		if ( ES_VALIDO ( p_cadRes ) )
		{
			if ( SCnjpEliminarElem ( p_cnjObj->p_cnjDatos, iElem ) != 1 )
			{
				p_cadRes = NULL;
			}
		}
	}
	else
	{
		p_cadRes = NULL;
	}
	return ( p_cadRes );
}

int SCnjCadVaciar ( SConjuntoCadenas * p_cnjObj )
{
	int 		iRes;
	SCadena * 	p_cadObj;
	int			iNumElems;

	if ( ES_VALIDO ( p_cnjObj ) )
	{
		iNumElems = SCnjCadNumElementos ( p_cnjObj );
		for ( int iElem = 0; iElem < iNumElems; iElem = iElem + 1 )
		{
			p_cadObj = SCnjCadElemento ( p_cnjObj, iElem );
			SCadDestruir ( &p_cadObj );
		}
		iRes = SCnjpVaciar ( p_cnjObj->p_cnjDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCnjCadExiste ( SConjuntoCadenas * p_cnjObj, SCadena * p_cadDato )
{
	int iRes;

	if ( ES_VALIDO ( p_cnjObj ) ) 
	{
		iRes = SCnjpExiste ( p_cnjObj->p_cnjDatos, (byte *) p_cadDato );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCnjCadBuscar ( SConjuntoCadenas * p_cnjObj, SCadena * p_cadDato )
{
	int iRes;
	
	if ( ES_VALIDO ( p_cnjObj ) ) 
	{
		iRes = SCnjpBuscar ( p_cnjObj->p_cnjDatos, (byte *) p_cadDato );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}
