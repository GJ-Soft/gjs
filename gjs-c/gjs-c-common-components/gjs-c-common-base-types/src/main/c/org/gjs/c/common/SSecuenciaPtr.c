#include "SSecuenciaPtr.h"


#include "TiposBasicosConfig.h"




SSecuenciaPtr * SSecpCrear ()
{
	SSecuenciaPtr * p_secObj;
	
	p_secObj = (SSecuenciaPtr *) MemReservar ( sizeof ( SSecuenciaPtr ) );
	if ( ES_VALIDO ( p_secObj ) )
	{
		p_secObj->p_lisObjetos = SLispCrear ();
	}
	return ( p_secObj );
}

void SSecpDestruir ( SSecuenciaPtr ** p_p_secObj )
{
	SSecuenciaPtr * p_secObj;
	
	if ( ES_VALIDO ( p_p_secObj ) )
	{
		p_secObj = *p_p_secObj;

		if ( ES_VALIDO ( p_secObj ) )
		{
			SLispDestruir ( &(p_secObj->p_lisObjetos) );
			MemLiberar ( (void **) p_p_secObj );
		}
	}
}

int SSecpEsValida ( SSecuenciaPtr * p_secObj )
{
	int iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		iRes = SLispEsValida ( p_secObj->p_lisObjetos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SSecpNumElementos ( SSecuenciaPtr * p_secObj )
{
	int iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		iRes = SLispNumElementos ( p_secObj->p_lisObjetos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SSecpEstaVacia ( SSecuenciaPtr * p_secObj )
{
	int iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		iRes = SLispEstaVacia ( p_secObj->p_lisObjetos );
	}
	else
	{
		iRes = 1;
	}
	return ( iRes );
}
byte * SSecpElemento ( SSecuenciaPtr * p_secObj, int iElem )
{
	byte * p_byRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		p_byRes = SLispElemento ( p_secObj->p_lisObjetos, iElem );
	}
	else
	{
		p_byRes = NULL;
	}
	return ( p_byRes );
}

int SSecpInsertar ( SSecuenciaPtr * p_secObj, byte * p_byDatos )
{
	int iRes;

	if ( ( SSecpEsValida ( p_secObj ) == 1 ) && ES_VALIDO ( p_byDatos ) )
	{
		iRes = SLispInsertarAlFinal ( p_secObj->p_lisObjetos, p_byDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SSecpEliminar ( SSecuenciaPtr * p_secObj, int iElem )
{
	int	iRes;

	if ( SSecpEsValida ( p_secObj ) == 1 ) 
	{
		iRes = SLispEliminarElem ( p_secObj->p_lisObjetos, iElem );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SSecpVaciar ( SSecuenciaPtr * p_secObj )
{
	int	iRes;

	if ( SSecpEsValida ( p_secObj ) == 1 ) 
	{
		iRes = SLispVaciar ( p_secObj->p_lisObjetos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

SListaPtr * SSecpLista ( SSecuenciaPtr * p_secObj )
{
	SListaPtr * p_lisRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		p_lisRes = p_secObj->p_lisObjetos;
	}
	else
	{
		p_lisRes = NULL;
	}
	return ( p_lisRes );
}

int	SSecpLiberacionMemoriaActivada ( SSecuenciaPtr * p_secObj )
{
	int	iRes;

	if ( SSecpEsValida ( p_secObj ) == 1 ) 
	{
		iRes = SLispLiberacionMemoriaActivada ( p_secObj->p_lisObjetos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

void SSecpActivarLiberacionMemoria ( SSecuenciaPtr * p_secObj )
{
	if ( SSecpEsValida ( p_secObj ) == 1 ) 
	{
		SLispActivarLiberacionMemoria ( p_secObj->p_lisObjetos );
	}
}

void SSecpDesactivarLiberacionMemoria ( SSecuenciaPtr * p_secObj )
{
	if ( SSecpEsValida ( p_secObj ) == 1 ) 
	{
		SLispDesactivarLiberacionMemoria ( p_secObj->p_lisObjetos );
	}
}

