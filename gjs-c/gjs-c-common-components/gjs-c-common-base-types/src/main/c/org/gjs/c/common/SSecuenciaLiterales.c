#include "SSecuenciaLiterales.h"

#include "TiposBasicosConfig.h"



SSecuenciaLiterales * SSecLitCrear ()
{
	SSecuenciaLiterales * p_secObj;
	
	p_secObj = (SSecuenciaLiterales *) MemReservar ( sizeof ( SSecuenciaLiterales ) );
	if ( ES_VALIDO ( p_secObj ) )
	{
		p_secObj->p_secDatos = SSecpCrear ();
		SSecpActivarLiberacionMemoria ( p_secObj->p_secDatos );
	}
	return ( p_secObj );
}

void SSecLitDestruir ( SSecuenciaLiterales ** p_p_secObj )
{
	SSecuenciaLiterales * p_secObj;
	
	if ( ES_VALIDO ( p_p_secObj ) )
	{
		p_secObj = *p_p_secObj;

		if ( ES_VALIDO ( p_secObj ) )
		{
			SSecpDestruir ( &(p_secObj->p_secDatos) );
			MemLiberar ( (void **) p_p_secObj );
		}
	}
}

int SSecLitEsValida ( SSecuenciaLiterales * p_secObj )
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

int SSecLitEstaVacia ( SSecuenciaLiterales * p_secObj )
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

int SSecLitNumElementos ( SSecuenciaLiterales * p_secObj )
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

char * SSecLitElemento ( SSecuenciaLiterales * p_secObj, int iElem )
{
	char *	p_cRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		p_cRes = (char *) SSecpElemento ( p_secObj->p_secDatos, iElem );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

int SSecLitInsertar ( SSecuenciaLiterales * p_secObj, const char * p_cDatos )
{
	int		iRes;
	char *	p_cElem;

	if ( ES_VALIDO ( p_secObj ) && ES_VALIDO ( p_cDatos ) )
	{
		p_cElem = CadDuplicar ( p_cDatos );
		if ( ES_VALIDO ( p_cElem ) )
		{
			iRes = SSecpInsertar ( p_secObj->p_secDatos, (byte *) p_cElem );
			if ( iRes != 1 )
			{
				MemLiberar ( (void **) &p_cElem );
			}
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

int SSecLitEliminar ( SSecuenciaLiterales * p_secObj, int iElem )
{
	int iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		iRes = SSecpEliminar ( p_secObj->p_secDatos, iElem );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SSecLitVaciar ( SSecuenciaLiterales * p_secObj )
{
	int iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		iRes = SSecpVaciar ( p_secObj->p_secDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SSecLitExiste ( SSecuenciaLiterales * p_secObj, const char * p_cDato )
{
	int iRes;
	int iElem;
	int iNumElems;

	if ( ES_VALIDO ( p_secObj ) && ES_VALIDO ( p_cDato )  ) 
	{
		iRes = 0;
		iElem = 0;
		iNumElems = SSecLitNumElementos ( p_secObj );
		while ( ( iElem < iNumElems ) && ( iRes == 0 ) )
		{
			if ( CadComparar ( SSecLitElemento ( p_secObj, iElem ), p_cDato ) == COMP_IGUAL )
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

int SSecLitBuscar ( SSecuenciaLiterales * p_secObj, const char * p_cDato )
{
	int iRes;
	int iElem;
	int iNumElems;

	if ( ES_VALIDO ( p_secObj ) && ES_VALIDO ( p_cDato )  ) 
	{
		iRes = -1;
		iElem = 0;
		iNumElems = SSecLitNumElementos ( p_secObj );
		while ( ( iElem < iNumElems ) && ( iRes < 0 ) )
		{
			if ( CadComparar ( SSecLitElemento ( p_secObj, iElem ), p_cDato ) == COMP_IGUAL )
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


