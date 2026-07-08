#include "SListaEntradasExt.h"

#include "TiposDatosConfig.h"




SListaEntradasExt * SLisEtxCrear ()
{
	SListaEntradasExt * p_lisObj;
	
	p_lisObj = (SListaEntradasExt *) MemReservar ( sizeof ( SListaEntradasExt ) );
	if ( ES_VALIDO ( p_lisObj ) )
	{
		p_lisObj->p_lisDatos = SLispCrear ();
		SLispDesactivarLiberacionMemoria ( p_lisObj->p_lisDatos );
	}
	return ( p_lisObj );
}

void SLisEtxDestruir ( SListaEntradasExt ** p_p_lisObj )
{
	SListaEntradasExt * p_lisObj;
	
	if ( ES_VALIDO ( p_p_lisObj ) )
	{
		p_lisObj = *p_p_lisObj;

		if ( ES_VALIDO ( p_lisObj ) )
		{
			SLisEtxVaciar ( p_lisObj );
			SLispDestruir ( &(p_lisObj->p_lisDatos) );
			MemLiberar ( (void **) p_p_lisObj );
		}
	}
}

int SLisEtxEsValida ( SListaEntradasExt * p_lisObj )
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

int SLisEtxEstaVacia ( SListaEntradasExt * p_lisObj )
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

int SLisEtxNumElementos ( SListaEntradasExt * p_lisObj )
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

SEntradaExt * SLisEtxElemento ( SListaEntradasExt * p_lisObj, int iElem )
{
	SEntradaExt *	p_etxRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		p_etxRes = (SEntradaExt *) SLispElemento ( p_lisObj->p_lisDatos, iElem );
	}
	else
	{
		p_etxRes = NULL;
	}
	return ( p_etxRes );
}

int SLisEtxInsertar ( SListaEntradasExt * p_lisObj, SEntradaExt * p_etxDatos )
{
	int iRes;

	if ( ES_VALIDO ( p_lisObj ) && ES_VALIDO ( p_etxDatos ) )
	{
		SLispInicio ( p_lisObj->p_lisDatos );
		while ( SEtxEsMenor ( ( SEntradaExt * ) SLispActual ( p_lisObj->p_lisDatos ), p_etxDatos ) &&
			( SLispEstaEnFinal ( p_lisObj->p_lisDatos ) == 0 ) )
		{
			SLispSiguiente ( p_lisObj->p_lisDatos );
		}
		if ( SLispEstaEnFinal ( p_lisObj->p_lisDatos ) == 1 )
		{
			iRes = SLispInsertar ( p_lisObj->p_lisDatos, ( byte * ) p_etxDatos );
		}
		else
		{
			iRes = SLispInsertarDelante ( p_lisObj->p_lisDatos, ( byte * ) p_etxDatos );
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLisEtxVaciar ( SListaEntradasExt * p_lisObj )
{
	int		 		iRes;
	int 			iNumElems;
	SEntradaExt * 	p_etxObj;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iNumElems = SLisEtxNumElementos ( p_lisObj );
		for ( int iElem = 0; iElem < iNumElems; iElem = iElem + 1 )
		{
			p_etxObj = SLisEtxElemento ( p_lisObj, iElem );
			SEtxDestruir ( &p_etxObj );
		}
		iRes = SLispVaciar ( p_lisObj->p_lisDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLisEtxEliminar ( SListaEntradasExt * p_lisObj, const char * p_cNombre )
{
	int				iEnc;
	int				iElem;
	int				iRes;
	int 			iNumElems;
	SEntradaExt *	p_etxRes;

	if ( ES_VALIDO ( p_lisObj ) && ES_VALIDO ( p_cNombre ) )
	{
		iEnc = 0;
		iElem = 0;
		iRes = 0;
		iNumElems = SLisEtxNumElementos ( p_lisObj );
		while ( ( iElem < iNumElems ) && ( iEnc == 0 ) )
		{
			p_etxRes = SLisEtxElemento ( p_lisObj, iElem );
			if ( CadComparar ( SEtxNombre ( p_etxRes ), p_cNombre ) == COMP_IGUAL ) 
			{
				iEnc = 1;
			}
			if ( iEnc == 1 )
			{
				iRes = SLisEtxEliminarElem ( p_lisObj, iElem );
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

int SLisEtxEliminarElem ( SListaEntradasExt * p_lisObj, int iElem )
{
	int 			iRes;
	SEntradaExt * 	p_etxObj;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		p_etxObj = SLisEtxElemento ( p_lisObj, iElem );
		SEtxDestruir ( &p_etxObj );
		iRes = SLispEliminarElem ( p_lisObj->p_lisDatos, iElem );
	}
	else
	{
		iRes = 0;
		iRes = 0;
	}
	return ( iRes );
}

int SLisEtxExiste ( SListaEntradasExt * p_lisObj, const char * p_cNombre )
{
	int iRes;
	int iElem;
	int iNumElems;

	if ( ES_VALIDO ( p_lisObj ) && ES_VALIDO ( p_cNombre )  )
	{
		iRes = 0;
		iElem = 0;
		iNumElems = SLisEtxNumElementos ( p_lisObj );
		while ( ( iElem < iNumElems ) && ( iRes == 0 ) )
		{
			if ( CadComparar ( SEtxNombre ( SLisEtxElemento ( p_lisObj, iElem ) ), p_cNombre ) == COMP_IGUAL )
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



