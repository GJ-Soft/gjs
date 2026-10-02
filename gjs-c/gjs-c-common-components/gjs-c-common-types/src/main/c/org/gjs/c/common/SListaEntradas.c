#include "SListaEntradas.h"

#include "TiposDatosConfig.h"




SListaEntradas * SLisEtrCrear ()
{
	SListaEntradas * p_lisObj;
	
	p_lisObj = (SListaEntradas *) MemReservar ( sizeof ( SListaEntradas ) );
	if ( ES_VALIDO ( p_lisObj ) )
	{
		p_lisObj->p_lisDatos = SLispCrear ();
		SLispDesactivarLiberacionMemoria ( p_lisObj->p_lisDatos );
	}
	return ( p_lisObj );
}

void SLisEtrDestruir ( SListaEntradas ** p_p_lisObj )
{
	SListaEntradas * p_lisObj;
	
	if ( ES_VALIDO ( p_p_lisObj ) )
	{
		p_lisObj = *p_p_lisObj;

		if ( ES_VALIDO ( p_lisObj ) )
		{
			SLisEtrVaciar ( p_lisObj );
			SLispDestruir ( &(p_lisObj->p_lisDatos) );
			MemLiberar ( (void **) p_p_lisObj );
		}
	}
}

int SLisEtrEsValida ( SListaEntradas * p_lisObj )
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

int SLisEtrEstaVacia ( SListaEntradas * p_lisObj )
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

int SLisEtrNumElementos ( SListaEntradas * p_lisObj )
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

int SLisEtrExiste ( SListaEntradas * p_lisObj, const char * p_cNombre )
{
	int iRes;
	int iElem;
	int iNumElems;

	if ( ES_VALIDO ( p_lisObj ) && ES_VALIDO ( p_cNombre ) )
	{
		iRes = 0;
		iElem = 0;
		iNumElems = SLisEtrNumElementos ( p_lisObj );
		while ( ( iElem < iNumElems ) && ( iRes == 0 ) )
		{
			if ( CadComparar ( SEtrNombre ( SLisEtrElemento ( p_lisObj, iElem ) ), p_cNombre ) == COMP_IGUAL )
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


SEntrada * SLisEtrBuscar ( SListaEntradas * p_lisObj, const char * p_cNombre )
{
	SEntrada *	p_etrRes;
	int			iEnc;
	int			iElem;
	int 		iNumElems;

	if ( ES_VALIDO ( p_lisObj ) && ES_VALIDO ( p_cNombre ) )
	{
		iEnc = 0;
		iElem = 0;
		iNumElems = SLisEtrNumElementos ( p_lisObj );
		while ( ( iElem < iNumElems ) && ( iEnc == 0 ) )
		{
			p_etrRes = SLisEtrElemento ( p_lisObj, iElem );
			if ( CadComparar ( SEtrNombre ( p_etrRes ), p_cNombre ) == COMP_IGUAL )
			{
				iEnc = 1;
			}
			iElem = iElem + 1;
		}
		if ( iEnc == 0 )
		{
			p_etrRes = NULL;
		}
	}
	else
	{
		p_etrRes = NULL;
	}
	return ( p_etrRes );
}

SEntrada * SLisEtrElemento ( SListaEntradas * p_lisObj, int iElem )
{
	SEntrada *	p_etrRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		p_etrRes = (SEntrada *) SLispElemento ( p_lisObj->p_lisDatos, iElem );
	}
	else
	{
		p_etrRes = NULL;
	}
	return ( p_etrRes );
}

const char * SLisEtrNombreElemento ( SListaEntradas * p_lisObj, int iElem )
{
	const char * p_cRes;

	SEntrada * p_etrRes = SLisEtrElemento ( p_lisObj, iElem );
	if ( ES_VALIDO ( p_lisObj ) )
	{
		p_cRes = SEtrNombre ( p_etrRes );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

const char * SLisEtrDefinicionElemento ( SListaEntradas * p_lisObj, int iElem )
{
	const char * p_cRes;

	SEntrada * p_etrRes = SLisEtrElemento ( p_lisObj, iElem );
	if ( ES_VALIDO ( p_lisObj ) )
	{
		p_cRes = SEtrDefinicion ( p_etrRes );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

int SLisEtrInsertar ( SListaEntradas * p_lisObj, SEntrada * p_etrDatos )
{
	int iRes;
	if ( ES_VALIDO ( p_lisObj ) && ES_VALIDO ( p_etrDatos ) )
	{
		SLispInicio ( p_lisObj->p_lisDatos );
		while ( SEtrEsMenor ( ( SEntrada * ) SLispActual ( p_lisObj->p_lisDatos ), p_etrDatos ) &&
			( SLispEstaEnFinal ( p_lisObj->p_lisDatos ) == 0 ) )
		{
			SLispSiguiente ( p_lisObj->p_lisDatos );
		}
		if ( SLispEstaEnFinal ( p_lisObj->p_lisDatos ) == 1 )
		{
			iRes = SLispInsertar ( p_lisObj->p_lisDatos, ( byte * ) p_etrDatos );
		}
		else
		{
			iRes = SLispInsertarDelante ( p_lisObj->p_lisDatos, ( byte * ) p_etrDatos );
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLisEtrInsertarExt ( SListaEntradas * p_lisObj, const char * p_cNombre, const char * p_cDefinicion )
{
	return ( SLisEtrInsertar ( p_lisObj, SEtrCrearExt ( p_cNombre, p_cDefinicion ) ) );
}

int SLisEtrEliminar ( SListaEntradas * p_lisObj, const char * p_cNombre )
{
	int			iEnc;
	int			iElem;
	int			iRes;
	int 		iNumElems;
	SEntrada *	p_etrRes;

	if ( ES_VALIDO ( p_lisObj ) && ES_VALIDO ( p_cNombre ) )
	{
		iEnc = 0;
		iElem = 0;
		iRes = 0;
		iNumElems = SLisEtrNumElementos ( p_lisObj );
		while ( ( iElem < iNumElems ) && ( iEnc == 0 ) )
		{
			p_etrRes = SLisEtrElemento ( p_lisObj, iElem );
			if ( CadComparar ( SEtrNombre ( p_etrRes ), p_cNombre ) == COMP_IGUAL )
			{
				iEnc = 1;
				iRes = SLisEtrEliminarElem ( p_lisObj, iElem );
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

int SLisEtrEliminarElem ( SListaEntradas * p_lisObj, int iElem )
{
	int 		iRes;
	SEntrada * 	p_etrObj;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		p_etrObj = SLisEtrElemento ( p_lisObj, iElem );
		SEtrDestruir ( &p_etrObj );
		iRes = SLispEliminarElem ( p_lisObj->p_lisDatos, iElem );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLisEtrVaciar ( SListaEntradas * p_lisObj )
{
	int 		iRes;
	int 		iNumElems;
	SEntrada * 	p_etrObj;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iNumElems = SLisEtrNumElementos ( p_lisObj );
		for ( int iElem = 0; iElem < iNumElems; iElem = iElem + 1 )
		{
			p_etrObj = SLisEtrElemento ( p_lisObj, iElem );
			SEtrDestruir ( &p_etrObj );
		}
		iRes = SLispVaciar ( p_lisObj->p_lisDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}




