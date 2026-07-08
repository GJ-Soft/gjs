#include "SPilaCadenas.h"

#include "TiposDatosConfig.h"



SPilaCadenas * SPilCadCrear ()
{
	SPilaCadenas * p_pilObj;
	
	p_pilObj = (SPilaCadenas *) MemReservar ( sizeof ( SPilaCadenas ) );
	if ( ES_VALIDO ( p_pilObj ) )
	{
		p_pilObj->p_pilDatos = SPilpCrear ();
		if ( ES_VALIDO ( p_pilObj->p_pilDatos ) )
		{
			SPilpDesactivarLiberacionMemoria ( p_pilObj->p_pilDatos );
		}
		else
		{
			MemLiberar ( (void **) &p_pilObj );
		}
	}
	return ( p_pilObj );
}

void SPilCadDestruir ( SPilaCadenas ** p_p_pilObj )
{
	SPilaCadenas * p_pilObj;
	
	if ( ES_VALIDO ( p_p_pilObj ) )
	{
		p_pilObj = *p_p_pilObj;

		if ( ES_VALIDO ( p_pilObj ) )
		{
			SPilCadVaciar ( p_pilObj );
			SPilpDestruir ( &(p_pilObj->p_pilDatos), 0 );
			MemLiberar ( (void **) p_p_pilObj );
		}
	}
}

int SPilCadEsValida ( SPilaCadenas * p_pilObj )
{
	int iRes;

	if ( ES_VALIDO ( p_pilObj ) )
	{
		iRes = SPilpEsValida ( p_pilObj->p_pilDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SPilCadEstaVacia ( SPilaCadenas * p_pilObj )
{
	int iRes;

	if ( ES_VALIDO ( p_pilObj ) )
	{
		iRes = SPilpEstaVacia ( p_pilObj->p_pilDatos );
	}
	else
	{
		iRes = 1;
	}
	return ( iRes );
}

int SPilCadNumElementos ( SPilaCadenas * p_pilObj )
{
	int iRes;

	if ( ES_VALIDO ( p_pilObj ) )
	{
		iRes = SPilpNumElementos ( p_pilObj->p_pilDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

SCadena * SPilCadPrimero ( SPilaCadenas * p_pilObj )
{
	SCadena *	p_cadRes;

	if ( ES_VALIDO ( p_pilObj ) )
	{
		p_cadRes = (SCadena *) SPilpPrimero ( p_pilObj->p_pilDatos );
	}
	else
	{
		p_cadRes = NULL;
	}
	return ( p_cadRes );
}

SCadena * SPilCadDesapilar ( SPilaCadenas * p_pilObj )
{
	SCadena * p_cadRes;

	if ( ES_VALIDO ( p_pilObj ) )
	{
		p_cadRes = (SCadena *) SPilpDesapilar ( p_pilObj->p_pilDatos );
	}
	else
	{
		p_cadRes = NULL;
	}
	return ( p_cadRes );
}

int SPilCadApilar ( SPilaCadenas * p_pilObj, SCadena * p_cadDato )
{
	int			iRes;

	if ( ES_VALIDO ( p_pilObj ) && ES_VALIDO ( p_cadDato ) )
	{
		iRes = SPilpApilar ( p_pilObj->p_pilDatos, (byte *) p_cadDato );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SPilCadApilarLit ( SPilaCadenas * p_pilObj, const char * p_cDato )
{
	int			iRes;
	SCadena *	p_cadValor;

	p_cadValor = SCadGenerar( p_cDato );
	iRes = SPilCadApilar ( p_pilObj, p_cadValor );
	if ( iRes != 1 )
	{
		SCadDestruir ( &p_cadValor );
	}
	return ( iRes  );  
}

int SPilCadApilarDup ( SPilaCadenas * p_pilObj, SCadena * p_cadDato )
{
	int			iRes;
	SCadena *	p_cadValor;

	p_cadValor = SCadDuplicar ( p_cadDato );
	iRes = SPilCadApilar ( p_pilObj, p_cadValor );
	if ( iRes != 1 )
	{
		SCadDestruir ( &p_cadValor );
	}
	return ( iRes );
}


int SPilCadEliminarPrimero ( SPilaCadenas * p_pilObj )
{
	int iRes;

	if ( ES_VALIDO ( p_pilObj ) )
	{
		iRes = SPilpEliminarPrimero ( p_pilObj->p_pilDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SPilCadVaciar ( SPilaCadenas * p_pilObj )
{
	SCadena * 	p_cadObj;
	int 		iRes;

	if ( ES_VALIDO ( p_pilObj ) )
	{
		while ( SPilCadEstaVacia ( p_pilObj ) == 0 )
		{
			p_cadObj = SPilCadDesapilar ( p_pilObj );
			SCadDestruir ( &p_cadObj );
		}
		iRes = SPilpVaciar ( p_pilObj->p_pilDatos, 0 );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

