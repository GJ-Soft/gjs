#include "SCadenaNumerica.h"
#include "TextoConfig.h"






SCadenaNumerica * SCadnCrearDef ()
{
	SCadenaNumerica * p_cadObj;

	p_cadObj = (SCadenaNumerica *) MemReservar ( sizeof ( SCadenaNumerica ) );
	if ( ES_VALIDO ( p_cadObj ) )
	{
		p_cadObj->p_cadInfo = SCadcCrear ( CAD_NUM_TAM_DEFECTO );
		p_cadObj->iVal = 0;
		p_cadObj->iCeros = 0;
		p_cadObj->iAlin = TXT_ALIN_DERECHA;
		SCadcCopiarEntero( p_cadObj->p_cadInfo, p_cadObj->iVal );
	}
	return ( p_cadObj );
}

SCadenaNumerica * SCadnCrear  ( int iTam ) 
{
	SCadenaNumerica * p_cadObj;

	p_cadObj = (SCadenaNumerica *) MemReservar ( sizeof ( SCadenaNumerica ) );
	if ( ES_VALIDO ( p_cadObj ) )
	{
		p_cadObj->p_cadInfo = SCadcCrear ( iTam );
		p_cadObj->iVal = 0;
		p_cadObj->iCeros = 0;
		p_cadObj->iAlin = TXT_ALIN_DERECHA;
		SCadcCopiarEntero( p_cadObj->p_cadInfo, p_cadObj->iVal );
	}
	return ( p_cadObj );
}

SCadenaNumerica * SCadnCrearValor  ( int iTam, int iVal ) 
{
	SCadenaNumerica * p_cadObj;

	p_cadObj = (SCadenaNumerica *) MemReservar ( sizeof ( SCadenaNumerica ) );
	if ( ES_VALIDO ( p_cadObj ) )
	{
		p_cadObj->p_cadInfo = SCadcCrear ( iTam );
		p_cadObj->iVal = iVal;
		p_cadObj->iCeros = 0;
		p_cadObj->iAlin = TXT_ALIN_DERECHA;
		SCadcCopiarEntero( p_cadObj->p_cadInfo, iVal );
	}
	return ( p_cadObj );
}

void SCadnDestruir ( SCadenaNumerica ** p_p_cadObj )
{
	SCadenaNumerica * p_cadObj;
	
	if ( ES_VALIDO ( p_p_cadObj ) )
	{
		p_cadObj = *p_p_cadObj;

		if ( ES_VALIDO ( p_cadObj ) )
		{
			SCadcDestruir ( &(p_cadObj->p_cadInfo ) );
			MemLiberar ( (void **) p_p_cadObj );
		}
	}
}

SCadenaConv * SCadnCadenaConv ( SCadenaNumerica * p_cadObj )
{
	SCadenaConv * p_cadRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		p_cadRes = p_cadObj->p_cadInfo;
	}
	else
	{
		p_cadRes = NULL;
	}
	return ( p_cadRes );
}

int SCadnObtValor ( SCadenaNumerica * p_cadObj )
{
	if ( ES_VALIDO ( p_cadObj ) )
	{
		return ( p_cadObj->iVal );
	}
	else
	{
		return ( 0 );
	}
}

void SCadnEstablecerValor (  SCadenaNumerica * p_cadObj, int iVal )
{
	if ( ES_VALIDO ( p_cadObj ) )
	{
		p_cadObj->iVal = iVal;
		SCadcCopiarEntero( p_cadObj->p_cadInfo, iVal );
	}
}

void SCadnEstablecerValorLit (  SCadenaNumerica * p_cadObj,const char * p_cVal )
{
	if ( ES_VALIDO ( p_cadObj ) )
	{
		SCadcCopiarLit ( p_cadObj->p_cadInfo, p_cVal );
		if ( SCadcEsNumerica ( p_cadObj->p_cadInfo ) == 1 )
		{
			p_cadObj->iVal = SCadcValorEntero ( p_cadObj->p_cadInfo );
		}
		else
		{
			p_cadObj->iVal =  0;
			SCadcCopiarEntero( p_cadObj->p_cadInfo, p_cadObj->iVal );
		}
	}
}

void SCadnAlinearDerecha ( SCadenaNumerica * p_cadObj )
{
	if ( ES_VALIDO ( p_cadObj ) )
	{
		p_cadObj->iAlin = TXT_ALIN_DERECHA;
	}
}

void SCadnAlinearIzquierda ( SCadenaNumerica * p_cadObj )
{
	if ( ES_VALIDO ( p_cadObj ) )
	{
		p_cadObj->iAlin = TXT_ALIN_IZQUIERDA;
	}
}

void SCadnActivarCompletarConCeros ( SCadenaNumerica * p_cadObj )
{
	if ( ES_VALIDO ( p_cadObj ) )
	{
		p_cadObj->iCeros = 1;
	}
}

void SCadnDesactivarCompletarConCeros ( SCadenaNumerica * p_cadObj )
{
	if ( ES_VALIDO ( p_cadObj ) )
	{
		p_cadObj->iCeros = 0;
	}
}

SCadenaNumerica * SCadnDuplicar ( SCadenaNumerica * p_cadObj )
{
	SCadenaNumerica * p_cadCopia;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		p_cadCopia = SCadnCrearValor ( SCadMaxTam ( SCadcCadena ( p_cadObj->p_cadInfo ) ), p_cadObj->iVal );
		if ( ES_VALIDO ( p_cadCopia ) )
		{
			p_cadCopia->iCeros = p_cadObj->iCeros;
			p_cadCopia->iAlin = p_cadObj->iAlin;
		}
	}
	else
	{
		p_cadCopia = NULL;
	}
	return ( p_cadCopia );
}




