#include "SListaEntidadesCod.h"

#include "TiposBaseDatosConfig.h"




SListaEntidadesCod * SLisEntCodCrear ()
{
	SListaEntidadesCod * p_lisObj;
	
	p_lisObj = (SListaEntidadesCod *) MemReservar ( sizeof ( SListaEntidadesCod ) );
	if ( ES_VALIDO ( p_lisObj ) )
	{
		p_lisObj->p_lisDatos = SLispCrear ();
		if ( ES_VALIDO ( p_lisObj->p_lisDatos ) )
		{
			SLispDesactivarLiberacionMemoria ( p_lisObj->p_lisDatos );
		}
		else
		{
			MemLiberar ( (void **) &p_lisObj );
		}
	}
	return ( p_lisObj );
}

void SLisEntCodDestruir ( SListaEntidadesCod ** p_p_lisObj )
{
	SListaEntidadesCod * p_lisObj;
	
	if ( ES_VALIDO ( p_p_lisObj ) )
	{
		p_lisObj = *p_p_lisObj;

		if ( ES_VALIDO ( p_lisObj ) )
		{
			SLisEntCodVaciar ( p_lisObj );
			SLispDestruir ( &(p_lisObj->p_lisDatos) );
			MemLiberar ( (void **) p_p_lisObj );
		}
	}
}

int SLisEntCodEsValida ( SListaEntidadesCod * p_lisObj )
{
	int iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iRes = SLispEsValida ( p_lisObj->p_lisDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLisEntCodEstaVacia ( SListaEntidadesCod * p_lisObj )
{
	int iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iRes = SLispEstaVacia ( p_lisObj->p_lisDatos );
	}
	else
	{
		iRes = 1;
	}
	return ( iRes );
}

int SLisEntCodNumElementos ( SListaEntidadesCod * p_lisObj )
{
	int iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iRes = SLispNumElementos ( p_lisObj->p_lisDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

SEntidadCod * SLisEntCodElemento ( SListaEntidadesCod * p_lisObj, int iElem )
{
	SEntidadCod *	p_cRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		p_cRes = (SEntidadCod *) SLispElemento ( p_lisObj->p_lisDatos, iElem );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

int SLisEntCodEstablecerElem ( SListaEntidadesCod * p_lisObj, int iElem, SEntidadCod * p_entcDatos )
{
	int			iRes;
	SEntidadCod *	p_entcAnt;	

	if ( ES_VALIDO ( p_lisObj ) )
	{
		p_entcAnt = (SEntidadCod *) SLispElemento ( p_lisObj->p_lisDatos, iElem );
		if ( SLispEstablecerElem ( p_lisObj->p_lisDatos, iElem, (byte *) p_entcDatos ) == 1 )
		{
			iRes = 1;
			if ( p_entcAnt != p_entcDatos )
			{
				SEntCodDestruir ( &p_entcAnt );
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

int SLisEntCodInsertarElem ( SListaEntidadesCod * p_lisObj, int iPosAnt, SEntidadCod * p_entcDatos )
{
	int iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iRes = SLispInsertarElem ( p_lisObj->p_lisDatos, iPosAnt, (byte *) p_entcDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLisEntCodInsertarAlInicio ( SListaEntidadesCod * p_lisObj, SEntidadCod * p_entcDatos )
{
	return ( SLisEntCodInsertarElem ( p_lisObj, -1, p_entcDatos ) );
}

int SLisEntCodInsertarAlFinal ( SListaEntidadesCod * p_lisObj, SEntidadCod * p_entcDatos )
{
	int iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iRes = SLisEntCodInsertarElem ( p_lisObj, SLisEntCodNumElementos ( p_lisObj ), p_entcDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLisEntCodEliminarElem ( SListaEntidadesCod * p_lisObj, int iElem )
{
	int 		iRes;
	SEntidadCod * 	p_entcObj;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		p_entcObj = SLisEntCodElemento ( p_lisObj, iElem );
		if ( ES_VALIDO ( p_entcObj ) ) 
		{
			iRes = SLispEliminarElem ( p_lisObj->p_lisDatos, iElem );
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

SEntidadCod * SLisEntCodExtraerElem ( SListaEntidadesCod * p_lisObj, int iElem )
{
	SEntidadCod * 	p_entcRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		p_entcRes = SLisEntCodElemento ( p_lisObj, iElem );
		if ( ES_VALIDO ( p_entcRes ) )
		{
			if ( SLispEliminarElem ( p_lisObj->p_lisDatos, iElem ) != 1 )
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

int SLisEntCodVaciar ( SListaEntidadesCod * p_lisObj )
{
	int 		iRes;
	SEntidadCod * 	p_entcObj;
	int			iNumElems;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iNumElems = SLisEntCodNumElementos ( p_lisObj );
		for ( int iElem = 0; iElem < iNumElems; iElem = iElem + 1 )
		{
			p_entcObj = SLisEntCodElemento ( p_lisObj, iElem );
			SEntCodDestruir ( &p_entcObj );
		}
		iRes = SLispVaciar ( p_lisObj->p_lisDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLisEntCodPosicion ( SListaEntidadesCod * p_lisObj )
{
	int	iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iRes = SLispPosicion ( p_lisObj->p_lisDatos );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

SEntidadCod * SLisEntCodActual ( SListaEntidadesCod * p_lisObj )
{
	SEntidadCod *	p_cRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		p_cRes = (SEntidadCod *) SLispActual ( p_lisObj->p_lisDatos );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

void SLisEntCodInicio ( SListaEntidadesCod * p_lisObj )
{
	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		SLispInicio ( p_lisObj->p_lisDatos );
	}
}

void SLisEntCodFinal ( SListaEntidadesCod * p_lisObj )
{
	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		SLispFinal ( p_lisObj->p_lisDatos );
	}
}

void SLisEntCodSiguiente ( SListaEntidadesCod * p_lisObj )
{
	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		SLispSiguiente ( p_lisObj->p_lisDatos );
	}
}

void SLisEntCodAnterior ( SListaEntidadesCod * p_lisObj )
{
	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		SLispAnterior ( p_lisObj->p_lisDatos );
	}
}

void SLisEntCodMoverA ( SListaEntidadesCod * p_lisObj, int iElem )
{
	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		SLispMoverA ( p_lisObj->p_lisDatos, iElem );
	}
}

void SLisEntCodDeposicionar ( SListaEntidadesCod * p_lisObj )
{
	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		SLispDeposicionar ( p_lisObj->p_lisDatos );
	}
}

int SLisEntCodEsNulo ( SListaEntidadesCod * p_lisObj )
{
	int iRes;

	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		iRes = SLispEsNulo ( p_lisObj->p_lisDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLisEntCodEstaEnFinal ( SListaEntidadesCod * p_lisObj )
{
	int iRes;

	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		iRes = SLispEstaEnFinal ( p_lisObj->p_lisDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLisEntCodEstaEnInicio ( SListaEntidadesCod * p_lisObj )
{
	int iRes;

	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		iRes = SLispEstaEnInicio ( p_lisObj->p_lisDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLisEntCodEstablecer ( SListaEntidadesCod * p_lisObj, SEntidadCod * p_entcDatos )
{
	SEntidadCod *	p_entcAnt;  
	int			iRes;

	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		p_entcAnt = (SEntidadCod *) SLispActual ( p_lisObj->p_lisDatos );
		iRes = SLispEstablecer ( p_lisObj->p_lisDatos, (byte *) p_entcDatos );
		if ( ( iRes == 1 ) && ( p_entcAnt != p_entcDatos ) )
		{
			SEntCodDestruir ( &p_entcAnt );
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}


int SLisEntCodInsertar ( SListaEntidadesCod * p_lisObj, SEntidadCod * p_entcDatos )
{
	return ( SLisEntCodInsertarDetras ( p_lisObj, p_entcDatos ) );
}

int SLisEntCodInsertarDelante ( SListaEntidadesCod * p_lisObj, SEntidadCod * p_entcDatos )
{
	int iRes;

	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		iRes = SLispInsertarDelante ( p_lisObj->p_lisDatos, (byte *) p_entcDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLisEntCodInsertarDetras ( SListaEntidadesCod * p_lisObj, SEntidadCod * p_entcDatos )
{
	int iRes;

	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		iRes = SLispInsertarDetras ( p_lisObj->p_lisDatos, (byte *) p_entcDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLisEntCodEliminar ( SListaEntidadesCod * p_lisObj )
{
	int 		iRes;
	SEntidadCod * 	p_entcAnt;

	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		p_entcAnt = SLisEntCodActual ( p_lisObj );
		if ( ES_VALIDO ( p_entcAnt ) )
		{
			iRes = SLispEliminar ( p_lisObj->p_lisDatos );
			if ( iRes == 1 )
			{
				SEntCodDestruir ( &p_entcAnt );
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

int SLisEntCodExiste ( SListaEntidadesCod * p_lisObj, SEntidadCod * p_entcDatos )
{
	int iRes;

	if ( SLisEntCodBuscar ( p_lisObj, p_entcDatos ) >= 0 )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLisEntCodBuscar ( SListaEntidadesCod * p_lisObj, SEntidadCod * p_entcDatos )
{
	int iRes;

	if ( ES_VALIDO ( p_entcDatos ) )
	{
		iRes = SLisEntCodBuscarCodigo ( p_lisObj, SEntCodCodigo ( p_entcDatos ) );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int SLisEntCodExisteCodigo ( SListaEntidadesCod * p_lisObj, SCodigo * p_codEntidad )
{
	int iRes;

	if ( SLisEntCodBuscarCodigo ( p_lisObj, p_codEntidad ) >= 0 )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLisEntCodBuscarCodigo ( SListaEntidadesCod * p_lisObj, SCodigo * p_codEntidad )
{
	int iRes;

	if ( ES_VALIDO ( p_codEntidad ) )
	{
		iRes = SLisEntCodBuscarValorCodigoLit ( p_lisObj, SCodValorLit ( p_codEntidad ) );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int SLisEntCodExisteValorCodigo ( SListaEntidadesCod * p_lisObj, SCadena * p_cadValor )
{
	int iRes;

	if ( SLisEntCodBuscarValorCodigo ( p_lisObj, p_cadValor ) >= 0 )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLisEntCodBuscarValorCodigo ( SListaEntidadesCod * p_lisObj, SCadena * p_cadValor )
{
	int iRes;

	if ( ES_VALIDO ( p_cadValor ) )
	{
		iRes = SLisEntCodBuscarValorCodigoLit ( p_lisObj, SCadValorConstante ( p_cadValor ) );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int SLisEntCodExisteValorCodigoLit ( SListaEntidadesCod * p_lisObj, const char * p_cValor )
{
	int iRes;

	if ( SLisEntCodBuscarValorCodigoLit ( p_lisObj, p_cValor ) >= 0 )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLisEntCodBuscarValorCodigoLit ( SListaEntidadesCod * p_lisObj, const char * p_cValor )
{
	int iRes;
	int iElem;
	int	iNumElems;

	/* El codigo vacio no identifica a nadie, igual que el id 0 en SListaEntidades. */
	if ( ES_VALIDO ( p_lisObj ) && ( CadLongitud ( p_cValor ) > 0 ) )
	{
		iRes = -1;
		iElem = 0;
		iNumElems = SLisEntCodNumElementos ( p_lisObj );
		while ( ( iElem < iNumElems ) && ( iRes == -1 ) )
		{
			if ( SEntCodEsIgualLit ( SLisEntCodElemento ( p_lisObj, iElem ), p_cValor ) == 1 )
			{
				iRes = iElem;
			}
			iElem = iElem + 1;
		}
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}
