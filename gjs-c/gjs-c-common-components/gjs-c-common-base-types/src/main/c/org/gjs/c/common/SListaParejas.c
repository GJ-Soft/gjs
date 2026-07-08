#include "SListaParejas.h"

#include "TiposBasicosConfig.h"




SListaParejas * SLisPrjCrear ()
{
	SListaParejas * p_lisObj;
	
	p_lisObj = (SListaParejas *) MemReservar ( sizeof ( SListaParejas ) );
	if ( ES_VALIDO ( p_lisObj ) )
	{
		p_lisObj->p_lisDatos = SLispCrear ();
		SLispDesactivarLiberacionMemoria ( p_lisObj->p_lisDatos );
	}
	return ( p_lisObj );
}

void SLisPrjDestruir ( SListaParejas ** p_p_lisObj )
{
	SListaParejas * p_lisObj;
	
	if ( ES_VALIDO ( p_p_lisObj ) )
	{
		p_lisObj = *p_p_lisObj;

		if ( ES_VALIDO ( p_lisObj ) )
		{
			SLisPrjVaciar ( p_lisObj );
			SLispDestruir ( &(p_lisObj->p_lisDatos) );
			MemLiberar ( (void **) p_p_lisObj );
		}
	}
}

int SLisPrjEsValida ( SListaParejas * p_lisObj )
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

int SLisPrjEstaVacia ( SListaParejas * p_lisObj )
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

int SLisPrjNumElementos ( SListaParejas * p_lisObj )
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

SPareja * SLisPrjElemento ( SListaParejas * p_lisObj, int iElem )
{
	SPareja *	p_prjRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		p_prjRes = (SPareja *) SLispElemento ( p_lisObj->p_lisDatos, iElem );
	}
	else
	{
		p_prjRes = NULL;
	}
	return ( p_prjRes );
}

int SLisPrjInsertar ( SListaParejas * p_lisObj, SPareja * p_prjDatos )
{
	int iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iRes = SLispInsertar ( p_lisObj->p_lisDatos, ( byte * ) p_prjDatos );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int SLisPrjInsertarExt ( SListaParejas * p_lisObj, void * p_vPrimero, void * p_vSegundo )
{
	int 		iRes;
	SPareja * 	p_prjObj;
	
	p_prjObj = SPrjCrearSoloPtr ( p_vPrimero, p_vSegundo );
	if ( ES_VALIDO ( p_prjObj ) )
	{
		iRes = SLisPrjInsertar ( p_lisObj, p_prjObj );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLisPrjVaciar ( SListaParejas * p_lisObj )
{
	int 		iRes;
	int			iNumElems;
	SPareja * 	p_prjObj;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iNumElems = SLisPrjNumElementos ( p_lisObj );
		for ( int iElem = 0; iElem < iNumElems; iElem = iElem + 1 )
		{
			p_prjObj = SLisPrjElemento ( p_lisObj, iElem );
			SPrjDestruir ( &p_prjObj );
		}
		iRes = SLispVaciar ( p_lisObj->p_lisDatos );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int SLisPrjEliminarElem ( SListaParejas * p_lisObj, int iElem )
{
	int 		iRes;
	SPareja * 	p_prjObj;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		p_prjObj = SLisPrjElemento ( p_lisObj, iElem );
		SPrjDestruir ( &p_prjObj );
		iRes = SLispEliminarElem ( p_lisObj->p_lisDatos, iElem );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}




