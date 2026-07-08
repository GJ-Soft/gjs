#include "SConjunto.h"


#include "TiposBasicosConfig.h"





SConjunto * SCnjCrear ( PFUNINTPVPV fComparar )
{
	SConjunto * p_cnjObj;
	
	p_cnjObj = (SConjunto *) MemReservar ( sizeof ( SConjunto ) );
	if ( ES_VALIDO ( p_cnjObj ) )
	{
		p_cnjObj->p_lisContenido = SLisOrdCrear ( fComparar );
	}
	return ( p_cnjObj );
}

void SCnjDestruir ( SConjunto ** p_p_cnjObj )
{
	SConjunto * p_cnjObj;
	
	if ( ES_VALIDO ( p_p_cnjObj ) )
	{
		p_cnjObj = *p_p_cnjObj;

		if ( ES_VALIDO ( p_cnjObj ) )
		{
			SLisOrdDestruir ( &(p_cnjObj->p_lisContenido) );
			MemLiberar ( (void **) p_p_cnjObj );
		}
	}
}

int SCnjEsValido ( SConjunto * p_cnjObj )
{
	int iRes;

	if ( ES_VALIDO ( p_cnjObj ) )
	{
		if ( SLisOrdEsValida ( p_cnjObj->p_lisContenido ) == 1 )
		{
			iRes = 1;
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

int SCnjNumElementos ( SConjunto * p_cnjObj )
{
	int iRes;

	if ( ES_VALIDO ( p_cnjObj ) )
	{
		iRes = SLisOrdNumElementos ( p_cnjObj->p_lisContenido );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCnjEstaVacio ( SConjunto * p_cnjObj )
{
	int iRes;

	if ( ES_VALIDO ( p_cnjObj ) )
	{
		iRes = SLisOrdEstaVacia ( p_cnjObj->p_lisContenido );
	}
	else
	{
		iRes = 1;
	}
	return ( iRes );
}

SElemento * SCnjElemento ( SConjunto * p_cnjObj, int iElem )
{
	SElemento * p_elmRes;

	if ( ES_VALIDO ( p_cnjObj ) )
	{
		p_elmRes = SLisOrdElemento ( p_cnjObj->p_lisContenido, iElem );
	}
	else
	{
		p_elmRes = NULL;
	}
	return ( p_elmRes );
}

int SCnjInsertarElem ( SConjunto * p_cnjObj, SElemento * p_elmObj )
{
	int iRes;

	if ( ( SCnjEsValido ( p_cnjObj ) == 1 ) && ( SElmEsValido ( p_elmObj ) == 1 ) )
	{
		if ( SCnjExiste ( p_cnjObj, SElmDatos ( p_elmObj ) ) == 0 )
		{
			iRes = SLisOrdInsertarElem ( p_cnjObj->p_lisContenido, p_elmObj );
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

int SCnjEliminarElem ( SConjunto * p_cnjObj, int iElem )
{
	int	iRes;

	if ( SCnjEsValido ( p_cnjObj ) == 1 ) 
	{
		iRes = SLisOrdEliminarElem ( p_cnjObj->p_lisContenido, iElem );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCnjVaciar ( SConjunto * p_cnjObj )
{
	int	iRes;

	if ( SCnjEsValido ( p_cnjObj ) == 1 ) 
	{
		iRes = SLisOrdVaciar ( p_cnjObj->p_lisContenido );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCnjExiste ( SConjunto * p_cnjObj, SBloque * p_blqDatos )
{
	int			iRes;

	if ( SCnjEsValido ( p_cnjObj ) == 1 )
	{
		if ( SLisOrdBuscar ( p_cnjObj->p_lisContenido, p_blqDatos ) >= 0 )
		{
			iRes = 1;
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

int SCnjExisteExt ( SConjunto * p_cnjObj, byte * p_byDatos )
{
	int			iRes;

	if ( SCnjEsValido ( p_cnjObj ) == 1 )
	{
		if ( SLisOrdBuscarExt ( p_cnjObj->p_lisContenido, p_byDatos ) >= 0 )
		{
			iRes = 1;
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

int SCnjBuscar ( SConjunto * p_cnjObj, SBloque * p_blqDatos )
{
	int			iRes;

	if ( SCnjEsValido ( p_cnjObj ) == 1 )
	{
		iRes = SLisOrdBuscar ( p_cnjObj->p_lisContenido, p_blqDatos );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int SCnjBuscarExt ( SConjunto * p_cnjObj, byte * p_byDatos )
{
	int			iRes;

	if ( SCnjEsValido ( p_cnjObj ) == 1 )
	{
		iRes = SLisOrdBuscarExt ( p_cnjObj->p_lisContenido, p_byDatos );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

SElemento * SCnjBuscarElem ( SConjunto * p_cnjObj, SBloque * p_blqDatos )
{
	SElemento * p_elmRes;
	int			iElem;

	if ( SCnjEsValido ( p_cnjObj ) == 1 )
	{
		iElem = SLisOrdBuscar ( p_cnjObj->p_lisContenido, p_blqDatos );
		if ( iElem >= 0 )
		{
			p_elmRes = SLisOrdElemento ( p_cnjObj->p_lisContenido, iElem );
		}
		else
		{
			p_elmRes = NULL;
		}
	}
	else
	{
		p_elmRes = NULL;
	}
	return ( p_elmRes );
}

SElemento * SCnjBuscarElemExt ( SConjunto * p_cnjObj, byte * p_byDatos )
{
	SElemento * p_elmRes;
	int			iElem;

	if ( SCnjEsValido ( p_cnjObj ) == 1 )
	{
		iElem = SLisOrdBuscarExt ( p_cnjObj->p_lisContenido, p_byDatos );
		if ( iElem >= 0 )
		{
			p_elmRes = SLisOrdElemento ( p_cnjObj->p_lisContenido, iElem );
		}
		else
		{
			p_elmRes = NULL;
		}
	}
	else
	{
		p_elmRes = NULL;
	}
	return ( p_elmRes );
}



