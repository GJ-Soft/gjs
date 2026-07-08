#include "SSecuencia.h"


#include "TiposBasicosConfig.h"




SSecuencia * SSecCrear ()
{
	SSecuencia * p_secObj;
	
	p_secObj = (SSecuencia *) MemReservar ( sizeof ( SSecuencia ) );
	if ( ES_VALIDO ( p_secObj ) )
	{
		p_secObj->p_lisObjetos = SLisCrear ();
	}
	return ( p_secObj );
}

void SSecDestruir ( SSecuencia ** p_p_secObj )
{
	SSecuencia * p_secObj;
	
	if ( ES_VALIDO ( p_p_secObj ) )
	{
		p_secObj = *p_p_secObj;

		if ( ES_VALIDO ( p_secObj ) )
		{
			SLisDestruir ( &(p_secObj->p_lisObjetos) );
			MemLiberar ( (void **) p_p_secObj );
		}
	}
}

int SSecEsValida ( SSecuencia * p_secObj )
{
	int iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		iRes = SLisEsValida ( p_secObj->p_lisObjetos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SSecNumElementos ( SSecuencia * p_secObj )
{
	int iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		iRes = SLisNumElementos ( p_secObj->p_lisObjetos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SSecEstaVacia ( SSecuencia * p_secObj )
{
	int iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		iRes = SLisEstaVacia ( p_secObj->p_lisObjetos );
	}
	else
	{
		iRes = 1;
	}
	return ( iRes );
}

SElemento * SSecElemento ( SSecuencia * p_secObj, int iElem )
{
	SElemento * p_elmRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		p_elmRes = SLisElemento ( p_secObj->p_lisObjetos, iElem );
	}
	else
	{
		p_elmRes = NULL;
	}
	return ( p_elmRes );
}

int SSecInsertar ( SSecuencia * p_secObj, SElemento * p_elmObj )
{
	int iRes;

	if ( ( SSecEsValida ( p_secObj ) == 1 ) && ES_VALIDO ( p_elmObj ) )
	{
		iRes = SLisInsertarAlFinal ( p_secObj->p_lisObjetos, p_elmObj );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SSecEliminar ( SSecuencia * p_secObj, int iElem )
{
	int	iRes;

	if ( SSecEsValida ( p_secObj ) == 1 ) 
	{
		iRes = SLisEliminarElem ( p_secObj->p_lisObjetos, iElem );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SSecVaciar ( SSecuencia * p_secObj )
{
	int	iRes;

	if ( SSecEsValida ( p_secObj ) == 1 ) 
	{
		iRes = SLisVaciar ( p_secObj->p_lisObjetos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

SLista * SSecLista ( SSecuencia * p_secObj )
{
	SLista * p_lisRes;

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
