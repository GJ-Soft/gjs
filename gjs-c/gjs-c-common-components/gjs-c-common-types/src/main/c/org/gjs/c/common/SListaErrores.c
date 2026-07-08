#include "SListaErrores.h"

#include "TiposDatosConfig.h"




SListaErrores * SLisErrCrear ()
{
	SListaErrores * p_lisObj;
	
	p_lisObj = (SListaErrores *) MemReservar ( sizeof ( SListaErrores ) );
	if ( ES_VALIDO ( p_lisObj ) )
	{
		p_lisObj->p_lisErrores = SLispCrear ();
		SLispDesactivarLiberacionMemoria ( p_lisObj->p_lisErrores );
	}
	return ( p_lisObj );
}

void SLisErrDestruir ( SListaErrores ** p_p_lisObj )
{
	SListaErrores * p_lisObj;
	
	if ( ES_VALIDO ( p_p_lisObj ) )
	{
		p_lisObj = *p_p_lisObj;
		if ( ES_VALIDO ( p_lisObj ) )
		{
			SLisErrVaciar ( p_lisObj );
			SLispDestruir ( &(p_lisObj->p_lisErrores) );
			MemLiberar ( (void **) p_p_lisObj );
		}
	}
}

int SLisErrEsValida ( SListaErrores * p_lisObj )
{
	int iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iRes = SLispEsValida ( p_lisObj->p_lisErrores );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLisErrEstaVacia ( SListaErrores * p_lisObj )
{
	int iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iRes = SLispEstaVacia ( p_lisObj->p_lisErrores );
	}
	else
	{
		iRes = 1;
	}
	return ( iRes );
}

int SLisErrContieneErrores ( SListaErrores * p_lisObj )
{
	int			iRes;
	int 		iElem;
	int			iNumElems;
	SError *	p_errRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iRes = 0;
		iElem = 0;
		iNumElems = SLisErrNumElementos ( p_lisObj );
		while ( ( iElem < iNumElems ) && ( iRes == 0 ) )
		{
			p_errRes = SLisErrElemento ( p_lisObj, iElem );
			if ( SErrEsAdvertencia ( p_errRes ) == 0 )
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

int SLisErrContieneAdvertencias ( SListaErrores * p_lisObj )
{
	int			iRes;
	int 		iElem;
	int			iNumElems;
	SError *	p_errRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iRes = 0;
		iElem = 0;
		iNumElems = SLisErrNumElementos ( p_lisObj );
		while ( ( iElem < iNumElems ) && ( iRes == 0 ) )
		{
			p_errRes = SLisErrElemento ( p_lisObj, iElem );
			if ( SErrEsAdvertencia ( p_errRes ) == 1 )
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

int SLisErrNumElementos ( SListaErrores * p_lisObj )
{
	int iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iRes = SLispNumElementos ( p_lisObj->p_lisErrores );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

SError * SLisErrElemento ( SListaErrores * p_lisObj, int iElem )
{
	SError *	p_errRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		p_errRes = (SError *) SLispElemento ( p_lisObj->p_lisErrores, iElem );
	}
	else
	{
		p_errRes = NULL;
	}
	return ( p_errRes );
}

const char * SLisErrCodigoElemento ( SListaErrores * p_lisObj, int iElem )
{
	const char * 	p_cRes;
	SError *		p_errObj;
	
	p_errObj = SLisErrElemento ( p_lisObj, iElem );
	if ( ES_VALIDO ( p_errObj ) )
	{
		p_cRes = SErrCodigo ( p_errObj );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

const char * SLisErrDescripcionElemento ( SListaErrores * p_lisObj, int iElem )
{
	const char * 	p_cRes;
	SError *		p_errObj;
	
	p_errObj = SLisErrElemento ( p_lisObj, iElem );
	if ( ES_VALIDO ( p_errObj ) )
	{
		p_cRes = SErrDescripcion ( p_errObj );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

int SLisErrInsertar ( SListaErrores * p_lisObj, SError * p_errObj )
{
	int iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iRes = SLispInsertarAlFinal ( p_lisObj->p_lisErrores, ( byte * ) p_errObj );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int SLisErrInsertarExt ( SListaErrores * p_lisObj, const char * p_cCodigo, const char * p_cDescripcion )
{
	int iRes;

	SError * p_errObj = SErrCrear ( p_cCodigo, p_cDescripcion );
	if ( ES_VALIDO ( p_errObj ) )
	{
		iRes = SLisErrInsertar ( p_lisObj, p_errObj );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int SLisErrVaciar ( SListaErrores * p_lisObj )
{
	int 		iRes;
	int			iNumElems;
	SError * 	p_errObj;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iNumElems = SLisErrNumElementos ( p_lisObj );
		for ( int iElem = 0; iElem < iNumElems; iElem = iElem + 1 )
		{
			p_errObj = SLisErrElemento ( p_lisObj, iElem );
			SErrDestruir ( &p_errObj );
		}
		iRes = SLispVaciar ( p_lisObj->p_lisErrores );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int SLisErrEliminar ( SListaErrores * p_lisObj, const char * p_cCodigo )
{
	int			iEnc;
	int			iElem;
	int			iRes;
	int			iNumElems;
	SError *	p_errRes;

	if ( ES_VALIDO ( p_lisObj ) && ES_VALIDO ( p_cCodigo ) )
	{
		iEnc = 0;
		iElem = 0;
		iRes = -1;
		iNumElems = SLisErrNumElementos ( p_lisObj );
		while ( ( iElem < iNumElems ) && ( iEnc == 0 ) )
		{
			p_errRes = SLisErrElemento ( p_lisObj, iElem );
			if ( CadComparar ( (char *) SErrCodigo ( p_errRes ), p_cCodigo ) == COMP_IGUAL ) 
			{
				iEnc = 1;
			}
			if ( iEnc == 1 )
			{
				iRes = SLisErrEliminarElem ( p_lisObj, iElem );
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

int SLisErrEliminarElem ( SListaErrores * p_lisObj, int iElem )
{
	int 		iRes;
	SError * 	p_errObj;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		p_errObj = SLisErrElemento ( p_lisObj, iElem );
		SErrDestruir ( &p_errObj );
		iRes = SLispEliminarElem ( p_lisObj->p_lisErrores, iElem );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int SLisErrExiste ( SListaErrores * p_lisObj, const char * p_cCodigo )
{
	int iRes;
	int iElem;
	int iNumElems;

	if ( ES_VALIDO ( p_lisObj ) && ES_VALIDO ( p_cCodigo )  )
	{
		iRes = 0;
		iElem = 0;
		iNumElems = SLisErrNumElementos ( p_lisObj );
		while ( ( iElem < iNumElems ) && ( iRes == 0 ) )
		{
			if ( CadComparar ( (char *) SErrCodigo ( SLisErrElemento ( p_lisObj, iElem ) ), p_cCodigo ) == COMP_IGUAL )
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

SError * SLisErrBuscar ( SListaErrores * p_lisObj, const char * p_cCodigo )
{
	SError *	p_errRes;
	int 		iElem;
	int			iNumElems;

	if ( ES_VALIDO ( p_lisObj ) && ES_VALIDO ( p_cCodigo )  )
	{
		p_errRes = NULL;
		iElem = 0;
		iNumElems = SLisErrNumElementos ( p_lisObj );
		while ( ( iElem < iNumElems ) && ( p_errRes == NULL ) )
		{
			if ( CadComparar ( (char *) SErrCodigo ( SLisErrElemento ( p_lisObj, iElem ) ), p_cCodigo ) == COMP_IGUAL )
			{
				p_errRes = SLisErrElemento ( p_lisObj, iElem );
			}
			iElem = iElem + 1;
		}
	}
	else
	{
		p_errRes = NULL;
	}
	return ( p_errRes );
}





