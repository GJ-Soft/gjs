#include "SSecuenciaGeneradoresId.h"

#include "TiposDatosConfig.h"


SSecuenciaGeneradoresId * SSecGenIdCrear ()
{
	SSecuenciaGeneradoresId * p_secObj;
	
	p_secObj = (SSecuenciaGeneradoresId *) MemReservar ( sizeof ( SSecuenciaGeneradoresId ) );
	if ( ES_VALIDO ( p_secObj ) )
	{
		p_secObj->p_secDatos = SSecpCrear ();
		SSecpDesactivarLiberacionMemoria ( p_secObj->p_secDatos );
	}
	return ( p_secObj );
}

void SSecGenIdDestruir ( SSecuenciaGeneradoresId ** p_p_secObj )
{
	SSecuenciaGeneradoresId * p_secObj;
	
	if ( ES_VALIDO ( p_p_secObj ) )
	{
		p_secObj = *p_p_secObj;

		if ( ES_VALIDO ( p_secObj ) )
		{
			SSecGenIdVaciar ( p_secObj );
			SSecpDestruir ( &(p_secObj->p_secDatos) );
			MemLiberar ( (void **) p_p_secObj );
		}
	}
}

int SSecGenIdEsValida ( SSecuenciaGeneradoresId * p_secObj )
{
	int iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		iRes = SSecpEsValida ( p_secObj->p_secDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SSecGenIdEstaVacia ( SSecuenciaGeneradoresId * p_secObj )
{
	int iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		iRes = SSecpEstaVacia ( p_secObj->p_secDatos );
	}
	else
	{
		iRes = 1;
	}
	return ( iRes );
}

int SSecGenIdNumElementos ( SSecuenciaGeneradoresId * p_secObj )
{
	int iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		iRes = SSecpNumElementos ( p_secObj->p_secDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

SGeneradorId * SSecGenIdElemento ( SSecuenciaGeneradoresId * p_secObj, int iElem )
{
	SGeneradorId *	p_cRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		p_cRes = (SGeneradorId *) SSecpElemento ( p_secObj->p_secDatos, iElem );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

int SSecGenIdInsertar ( SSecuenciaGeneradoresId * p_secObj, SGeneradorId * p_genidDatos )
{
	int	iRes;

	if ( ES_VALIDO ( p_secObj ) && ES_VALIDO ( p_genidDatos ) )
	{
		iRes = SSecpInsertar ( p_secObj->p_secDatos, (byte *) p_genidDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SSecGenIdEliminar ( SSecuenciaGeneradoresId * p_secObj, int iElem )
{
	int 			iRes;
	SGeneradorId * 	p_genidObj;

	if ( ES_VALIDO ( p_secObj ) )
	{
		p_genidObj = SSecGenIdElemento ( p_secObj, iElem );
		if ( ES_VALIDO ( p_genidObj ) ) 
		{
			iRes = SSecpEliminar ( p_secObj->p_secDatos, iElem );
			if ( iRes == 1 ) 
			{
				SGenIdDestruir ( &p_genidObj );	
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

int SSecGenIdVaciar ( SSecuenciaGeneradoresId * p_secObj )
{
	int 			iRes;
	int 			iNumElems;
	SGeneradorId * 	p_genidObj;
	

	if ( ES_VALIDO ( p_secObj ) )
	{
		iNumElems = SSecGenIdNumElementos ( p_secObj );
		for ( int iElem = 0; iElem < iNumElems; iElem = iElem + 1 )
		{
			p_genidObj = SSecGenIdElemento ( p_secObj, iElem );
			SGenIdDestruir ( &p_genidObj );
		}
		iRes = SSecpVaciar ( p_secObj->p_secDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}
