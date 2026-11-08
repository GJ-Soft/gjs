#include "SConjuntoEntidadesCod.h"
          
#include "TiposBaseDatosConfig.h"


static int _SEntCodComparar ( void * p_vVal1, void * p_vVal2 )
{
	int 		iRes;
	SEntidadCod * 	p_entcVal1 = (SEntidadCod *) p_vVal1;
	SEntidadCod * 	p_entcVal2 = (SEntidadCod *) p_vVal2;
	iRes = SEntCodComparar ( p_entcVal1, p_entcVal2 );
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


SConjuntoEntidadesCod * SCnjEntCodCrear ()
{
	SConjuntoEntidadesCod * p_cnjObj;
	
	p_cnjObj = (SConjuntoEntidadesCod *) MemReservar ( sizeof ( SConjuntoEntidadesCod ) );
	if ( ES_VALIDO ( p_cnjObj ) )
	{
		p_cnjObj->p_cnjDatos = SCnjpCrear ( _SEntCodComparar );
		SCnjpDesactivarLiberacionMemoria ( p_cnjObj->p_cnjDatos );
	}
	return ( p_cnjObj );
}

void SCnjEntCodDestruir ( SConjuntoEntidadesCod ** p_p_cnjObj )
{
	SConjuntoEntidadesCod * p_cnjObj;
	
	if ( ES_VALIDO ( p_p_cnjObj ) )
	{
		p_cnjObj = *p_p_cnjObj;

		if ( ES_VALIDO ( p_cnjObj ) )
		{
			SCnjEntCodVaciar ( p_cnjObj );
			SCnjpDestruir ( &(p_cnjObj->p_cnjDatos) );
			MemLiberar ( (void **) p_p_cnjObj );
		}
	}
}

int SCnjEntCodEsValido ( SConjuntoEntidadesCod * p_cnjObj )
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

int SCnjEntCodEstaVacio ( SConjuntoEntidadesCod * p_cnjObj )
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

int SCnjEntCodNumElementos ( SConjuntoEntidadesCod * p_cnjObj )
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

SEntidadCod * SCnjEntCodElemento ( SConjuntoEntidadesCod * p_cnjObj, int iElem )
{
	SEntidadCod *	p_cRes;

	if ( ES_VALIDO ( p_cnjObj ) )
	{
		p_cRes = (SEntidadCod *) SCnjpElemento ( p_cnjObj->p_cnjDatos, iElem );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

SEntidadCod * SCnjEntCodPrimero ( SConjuntoEntidadesCod * p_cnjObj )
{
	SEntidadCod * p_cRes;

	if ( ES_VALIDO ( p_cnjObj ) )
	{
		p_cRes = (SEntidadCod *) SCnjpPrimero ( p_cnjObj->p_cnjDatos );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

SEntidadCod * SCnjEntCodUltimo ( SConjuntoEntidadesCod * p_cnjObj )
{
	SEntidadCod * p_cRes;

	if ( ES_VALIDO ( p_cnjObj ) )
	{
		p_cRes = (SEntidadCod *) SCnjpUltimo ( p_cnjObj->p_cnjDatos );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

int SCnjEntCodPosicion ( SConjuntoEntidadesCod * p_cnjObj, SEntidadCod * p_entcDato )
{
	int iRes;

	if ( ES_VALIDO ( p_cnjObj ) )
	{
		iRes = SCnjpPosicion ( p_cnjObj->p_cnjDatos, (byte *) p_entcDato );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int SCnjEntCodInsertar ( SConjuntoEntidadesCod * p_cnjObj, SEntidadCod * p_entcDato )
{
	int			iRes;

	if ( ES_VALIDO ( p_cnjObj ) && ES_VALIDO ( p_entcDato ) )
	{
		iRes = SCnjpInsertarElem ( p_cnjObj->p_cnjDatos, (byte *) p_entcDato );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int SCnjEntCodEliminar ( SConjuntoEntidadesCod * p_cnjObj, int iElem )
{
	int 		iRes;
	SEntidadCod * 	p_entcObj;

	if ( ES_VALIDO ( p_cnjObj ) )
	{
		p_entcObj = SCnjEntCodElemento ( p_cnjObj, iElem );
		if ( ES_VALIDO ( p_entcObj ) )
		{
			iRes = SCnjpEliminarElem ( p_cnjObj->p_cnjDatos, iElem );
			if ( iRes == 1 )
			{
				SEntCodDestruir ( &p_entcObj );
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

SEntidadCod * SCnjEntCodExtraer ( SConjuntoEntidadesCod * p_cnjObj, int iElem )
{
	SEntidadCod * 	p_entcRes;

	if ( ES_VALIDO ( p_cnjObj ) )
	{
		p_entcRes = SCnjEntCodElemento ( p_cnjObj, iElem );
		if ( ES_VALIDO ( p_entcRes ) )
		{
			if ( SCnjpEliminarElem ( p_cnjObj->p_cnjDatos, iElem ) != 1 )
			{
				p_entcRes = NULL;
			}
		}
	}
	else
	{
		p_entcRes = NULL;
	}
	return ( p_entcRes );
}

int SCnjEntCodVaciar ( SConjuntoEntidadesCod * p_cnjObj )
{
	int 		iRes;
	SEntidadCod * 	p_entcObj;
	int			iNumElems;

	if ( ES_VALIDO ( p_cnjObj ) )
	{
		iNumElems = SCnjEntCodNumElementos ( p_cnjObj );
		for ( int iElem = 0; iElem < iNumElems; iElem = iElem + 1 )
		{
			p_entcObj = SCnjEntCodElemento ( p_cnjObj, iElem );
			SEntCodDestruir ( &p_entcObj );
		}
		iRes = SCnjpVaciar ( p_cnjObj->p_cnjDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCnjEntCodExiste ( SConjuntoEntidadesCod * p_cnjObj, SEntidadCod * p_entcDato )
{
	int iRes;

	if ( ES_VALIDO ( p_cnjObj ) )
	{
		iRes = SCnjpExiste ( p_cnjObj->p_cnjDatos, (byte *) p_entcDato );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCnjEntCodBuscar ( SConjuntoEntidadesCod * p_cnjObj, SEntidadCod * p_entcDato )
{
	int iRes;

	if ( ES_VALIDO ( p_cnjObj ) )
	{
		iRes = SCnjpBuscar ( p_cnjObj->p_cnjDatos, (byte *) p_entcDato );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int SCnjEntCodExisteCodigo ( SConjuntoEntidadesCod * p_cnjObj, SCodigo * p_codEntidad )
{
	int iRes;

	if ( SCnjEntCodBuscarCodigo ( p_cnjObj, p_codEntidad ) >= 0 )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCnjEntCodBuscarCodigo ( SConjuntoEntidadesCod * p_cnjObj, SCodigo * p_codEntidad )
{
	int iRes;

	if ( ES_VALIDO ( p_codEntidad ) )
	{
		iRes = SCnjEntCodBuscarValorCodigoLit ( p_cnjObj, SCodValorLit ( p_codEntidad ) );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int SCnjEntCodExisteValorCodigo ( SConjuntoEntidadesCod * p_cnjObj, SCadena * p_cadValor )
{
	int iRes;

	if ( SCnjEntCodBuscarValorCodigo ( p_cnjObj, p_cadValor ) >= 0 )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCnjEntCodBuscarValorCodigo ( SConjuntoEntidadesCod * p_cnjObj, SCadena * p_cadValor )
{
	int iRes;

	if ( ES_VALIDO ( p_cadValor ) )
	{
		iRes = SCnjEntCodBuscarValorCodigoLit ( p_cnjObj, SCadValorConstante ( p_cadValor ) );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int SCnjEntCodExisteValorCodigoLit ( SConjuntoEntidadesCod * p_cnjObj, const char * p_cValor )
{
	int iRes;

	if ( SCnjEntCodBuscarValorCodigoLit ( p_cnjObj, p_cValor ) >= 0 )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCnjEntCodBuscarValorCodigoLit ( SConjuntoEntidadesCod * p_cnjObj, const char * p_cValor )
{
	int 			iRes;
	SEntidadCod * 	p_entcRef;

	/* SConjuntoPtr solo compara contra otro elemento: se busca con una entidad de sonda.
	   El tope es la longitud exacta del literal. Si no es un codigo valido ( vacio, no
	   empieza por letra, no alfanumerico ) la sonda no se crea y no se encuentra nada,
	   que es lo correcto: un codigo asi no puede estar en el conjunto. */
	if ( ES_VALIDO ( p_cnjObj ) && ( CadLongitud ( p_cValor ) > 0 ) )
	{
		p_entcRef = SEntCodCrearLit ( p_cValor, CadLongitud ( p_cValor ) );
		if ( ES_VALIDO ( p_entcRef ) )
		{
			iRes = SCnjEntCodBuscar ( p_cnjObj, p_entcRef );
			SEntCodDestruir ( &p_entcRef );
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
