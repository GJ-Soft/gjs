#include "SConjuntoPtr.h"


#include "TiposBasicosConfig.h"







SConjuntoPtr * SCnjpCrear ( PFUNINTPVPV fComparar )
{
	SConjuntoPtr * p_cnjObj;
	
	p_cnjObj = (SConjuntoPtr *) MemReservar ( sizeof ( SConjuntoPtr ) );
	if ( ES_VALIDO ( p_cnjObj ) )
	{
		p_cnjObj->p_lispContenido = SLispOrdCrear ( fComparar );
	}
	return ( p_cnjObj );
}

void SCnjpDestruir ( SConjuntoPtr ** p_p_cnjObj )
{
	SConjuntoPtr * p_cnjObj;
	
	if ( ES_VALIDO ( p_p_cnjObj ) )
	{
		p_cnjObj = *p_p_cnjObj;

		if ( ES_VALIDO ( p_cnjObj ) )
		{
			SLispOrdDestruir ( &(p_cnjObj->p_lispContenido) );
			MemLiberar ( (void **) p_p_cnjObj );
		}
	}
}

int SCnjpEsValido ( SConjuntoPtr * p_cnjObj )
{
	int iRes;

	if ( ES_VALIDO ( p_cnjObj ) )
	{
		if ( SLispOrdEsValida ( p_cnjObj->p_lispContenido ) == 1 )
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

int SCnjpNumElementos ( SConjuntoPtr * p_cnjObj )
{
	int iRes;

	if ( ES_VALIDO ( p_cnjObj ) )
	{
		iRes = SLispOrdNumElementos ( p_cnjObj->p_lispContenido );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCnjpEstaVacio ( SConjuntoPtr * p_cnjObj )
{
	int iRes;

	if ( ES_VALIDO ( p_cnjObj ) )
	{
		iRes = SLispOrdEstaVacia ( p_cnjObj->p_lispContenido );
	}
	else
	{
		iRes = 1;
	}
	return ( iRes );
}

byte * SCnjpElemento ( SConjuntoPtr * p_cnjObj, int iElem )
{
	byte *	p_byRes;

	if ( ES_VALIDO ( p_cnjObj ) )
	{
		p_byRes = SLispOrdElemento ( p_cnjObj->p_lispContenido, iElem );
	}
	else
	{
		p_byRes = NULL;
	}
	return ( p_byRes );
}

int SCnjpInsertarElem ( SConjuntoPtr * p_cnjObj, byte * p_byDatos )
{
	int iRes;

	if ( ( SCnjpEsValido ( p_cnjObj ) == 1 ) && ES_VALIDO ( p_byDatos ) )
	{
		if ( SCnjpExiste ( p_cnjObj, p_byDatos ) == 0 )
		{
			iRes = SLispOrdInsertarElem ( p_cnjObj->p_lispContenido, p_byDatos );
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

int SCnjpEliminarElem ( SConjuntoPtr * p_cnjObj, int iElem )
{
	int	iRes;

	if ( SCnjpEsValido ( p_cnjObj ) == 1 ) 
	{
		iRes = SLispOrdEliminarElem ( p_cnjObj->p_lispContenido, iElem );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCnjpVaciar ( SConjuntoPtr * p_cnjObj )
{
	int	iRes;

	if ( SCnjpEsValido ( p_cnjObj ) == 1 ) 
	{
		iRes = SLispOrdVaciar ( p_cnjObj->p_lispContenido );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCnjpExiste ( SConjuntoPtr * p_cnjObj, byte * p_byDatos )
{
	int			iRes;

	if ( SCnjpEsValido ( p_cnjObj ) == 1 )
	{
		if ( SLispOrdBuscar ( p_cnjObj->p_lispContenido, p_byDatos ) >= 0 )
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

int SCnjpBuscar ( SConjuntoPtr * p_cnjObj, byte * p_byDatos )
{
	int			iRes;

	if ( SCnjpEsValido ( p_cnjObj ) == 1 )
	{
		iRes = SLispOrdBuscar ( p_cnjObj->p_lispContenido, p_byDatos );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

byte * SCnjpBuscarElem ( SConjuntoPtr * p_cnjObj, byte * p_byDatos )
{
	byte * 	p_byRes;
	int		iElem;

	if ( SCnjpEsValido ( p_cnjObj ) == 1 )
	{
		iElem = SLispOrdBuscar ( p_cnjObj->p_lispContenido, p_byDatos );
		if ( iElem >= 0 )
		{
			p_byRes = SLispOrdElemento ( p_cnjObj->p_lispContenido, iElem );
		}
		else
		{
			p_byRes = NULL;
		}
	}
	else
	{
		p_byRes = NULL;
	}
	return ( p_byRes );
}

int	SCnjpLiberacionMemoriaActivada ( SConjuntoPtr * p_cnjObj )
{
	int iRes;
	
	if ( ES_VALIDO ( p_cnjObj ) )
	{
		iRes = SLispOrdLiberacionMemoriaActivada ( p_cnjObj->p_lispContenido );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

void SCnjpActivarLiberacionMemoria ( SConjuntoPtr * p_cnjObj )
{
	if ( ES_VALIDO ( p_cnjObj ) )
	{
		SLispOrdActivarLiberacionMemoria ( p_cnjObj->p_lispContenido );
	}
}

void SCnjpDesactivarLiberacionMemoria ( SConjuntoPtr * p_cnjObj )
{
	if ( ES_VALIDO ( p_cnjObj ) )
	{
		SLispOrdDesactivarLiberacionMemoria ( p_cnjObj->p_lispContenido );
	}
}


