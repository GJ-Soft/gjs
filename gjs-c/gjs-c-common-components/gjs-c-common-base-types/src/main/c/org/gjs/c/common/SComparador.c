#include "SComparador.h"



#include "TiposBasicosConfig.h"


int _CompararLiterales ( void * p_vVal1, void * p_vVal2 )
{
	int iRes = CadComparar ( (char *) p_vVal1, (char *) p_vVal2 );
	if ( iRes == COMP_MENOR )
	{
		iRes = -1;
	}
	else if ( iRes == COMP_MAYOR )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int _CompararEnteros ( void * p_vVal1, void * p_vVal2 )
{
	int iRes = 0;
	long lVal1 = *((long *) p_vVal1);
	long lVal2 = *((long *) p_vVal2);
	
	if ( lVal1 < lVal2 )
	{
		iRes = -1;
	}
	else if ( lVal1 > lVal2 )
	{
		iRes = 1;
	}
	return ( iRes );
}

int _CompararReales ( void * p_vVal1, void * p_vVal2 )
{
	int iRes = 0;
	double dVal1 = *((double *) p_vVal1);
	double dVal2 = *((double *) p_vVal2);

	if ( dVal1 < dVal2 )
	{
		iRes = -1;
	}
	else if ( dVal1 > dVal2 )
	{
		iRes = 1;
	}
	return ( iRes );
}

SComparador * SCmpCrear ( PFUNINTPVPV fComparar )
{
	SComparador * p_cmpObj;
	
	if ( ES_VALIDO ( fComparar ) )
	{
		p_cmpObj = (SComparador *) MemReservar ( sizeof ( SComparador ) );
		if ( ES_VALIDO ( p_cmpObj ) )
		{
			p_cmpObj->fComparar = fComparar;
		}
	}
	else
	{
		p_cmpObj = NULL;
	}
	return ( p_cmpObj );
}

SComparador * SCmpEnteros ()
{
	return ( SCmpCrear ( _CompararEnteros ) );
}

SComparador * SCmpReales ()
{
	return ( SCmpCrear ( _CompararReales ) );
}

SComparador * SCmpLiterales ()
{
	return ( SCmpCrear ( _CompararLiterales ) );
}

void SCmpDestruir ( SComparador ** p_p_cmpObj )
{
	if ( ES_VALIDO ( p_p_cmpObj ) )
	{
		MemLiberar ( (void **) p_p_cmpObj );
	}
}

int SCmpEsValido ( SComparador * p_cmpObj )
{
	int iRes;

	if ( ES_VALIDO ( p_cmpObj ) )
	{
		if ( ES_VALIDO ( p_cmpObj->fComparar ) )
		{
			iRes = 1;
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

int SCmpEvaluar ( SComparador * p_cmpObj, void * p_vObj1, void * p_vObj2 )
{
	int iRes;

	if ( SCmpEsValido ( p_cmpObj ) == 1 )
	{
		iRes = p_cmpObj->fComparar ( p_vObj1, p_vObj2 );
	}
	else
	{
		ERROR_ESTABLECER( ERR_PARAMETROS );
		iRes = -1;
	}
	return ( iRes );
}

int SCmpEvaluarEsIgual ( SComparador * p_cmpObj, void * p_vObj1, void * p_vObj2 )
{
	int iRes;

	if ( SCmpEsValido ( p_cmpObj ) == 1 )
	{
		if ( p_cmpObj->fComparar ( p_vObj1, p_vObj2 ) == 0 )
		{
			iRes = 1;
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

int SCmpEvaluarEsMenor ( SComparador * p_cmpObj, void * p_vObj1, void * p_vObj2 )
{
	int iRes;

	if ( SCmpEsValido ( p_cmpObj ) == 1 )
	{
		if ( p_cmpObj->fComparar ( p_vObj1, p_vObj2 ) == -1 )
		{
			iRes = 1;
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

int SCmpEvaluarEsMayor ( SComparador * p_cmpObj, void * p_vObj1, void * p_vObj2 )
{
	int iRes;

	if ( SCmpEsValido ( p_cmpObj ) == 1 )
	{
		if ( p_cmpObj->fComparar ( p_vObj1, p_vObj2 ) == 1 )
		{
			iRes = 1;
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

int SCmpEvaluarEsDiferente ( SComparador * p_cmpObj, void * p_vObj1, void * p_vObj2 )
{
	int iRes;

	if ( SCmpEsValido ( p_cmpObj ) == 1 )
	{
		if ( p_cmpObj->fComparar ( p_vObj1, p_vObj2 ) != 0 )
		{
			iRes = 1;
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

int SCmpEvaluarBloque ( SComparador * p_cmpObj, SBloque * p_blqObj1, SBloque * p_blqObj2 )
{
	int iRes;

	if ( ES_VALIDO ( p_blqObj1 )  && ES_VALIDO ( p_blqObj2 ) )
	{
		if ( SBlqTam ( p_blqObj1 ) == SBlqTam ( p_blqObj2 ) )
		{
			iRes = SCmpEvaluar ( p_cmpObj, (void *) SBlqDatos ( p_blqObj1 ), (void *)  SBlqDatos ( p_blqObj2 ) );
		}
		else if ( SBlqTam ( p_blqObj1 ) > SBlqTam ( p_blqObj2 ) )
		{
			iRes = 1;
		}
		else // if ( SBlqTam ( p_blqObj1 ) < SBlqTam ( p_blqObj2 ) )
		{
			iRes = -1;
		}
	}
	else if ( ES_VALIDO ( p_blqObj1 ) )
	{
		iRes = 1;
	}
	else if ( ES_VALIDO ( p_blqObj2 ) )
	{
		iRes = -1;
	}
	else 
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCmpEvaluarBloqueEsIgual ( SComparador * p_cmpObj, SBloque * p_blqObj1, SBloque * p_blqObj2 )
{
	int iRes;

	if ( SCmpEvaluarBloque ( p_cmpObj, p_blqObj1, p_blqObj2 ) == 0 )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCmpEvaluarBloqueEsMayor ( SComparador * p_cmpObj, SBloque * p_blqObj1, SBloque * p_blqObj2 )
{
	int iRes;

	if ( SCmpEvaluarBloque ( p_cmpObj, p_blqObj1, p_blqObj2 ) == 1 )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCmpEvaluarBloqueEsMenor ( SComparador * p_cmpObj, SBloque * p_blqObj1, SBloque * p_blqObj2 )
{
	int iRes;

	if ( SCmpEvaluarBloque ( p_cmpObj, p_blqObj1, p_blqObj2 ) == -1 )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCmpEvaluarBloqueEsDiferente ( SComparador * p_cmpObj, SBloque * p_blqObj1, SBloque * p_blqObj2 )
{
	int iRes;

	if ( SCmpEvaluarBloque ( p_cmpObj, p_blqObj1, p_blqObj2 ) != 0 )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCmpEvaluarBloqueExt ( SComparador * p_cmpObj, SBloque * p_blqObj1, byte * p_byObj2 )
{
	int iRes;

	if ( ES_VALIDO ( p_blqObj1 )  && ES_VALIDO ( p_byObj2 ) )
	{
		iRes = SCmpEvaluar ( p_cmpObj, (void *) SBlqDatos ( p_blqObj1 ), (void *) p_byObj2 );
	}
	else if ( ES_VALIDO ( p_blqObj1 ) )
	{
		iRes = 1;
	}
	else if ( ES_VALIDO ( p_byObj2 ) )
	{
		iRes = -1;
	}
	else 
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCmpEvaluarBloqueEsIgualExt ( SComparador * p_cmpObj, SBloque * p_blqObj1, byte * p_byObj2 )
{
	int iRes;

	if ( SCmpEvaluarBloqueExt ( p_cmpObj, p_blqObj1, p_byObj2 ) == 0 )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCmpEvaluarBloqueEsMayorExt ( SComparador * p_cmpObj, SBloque * p_blqObj1, byte * p_byObj2 )
{
	int iRes;

	if ( SCmpEvaluarBloqueExt ( p_cmpObj, p_blqObj1, p_byObj2 ) == 1 )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCmpEvaluarBloqueEsMenorExt ( SComparador * p_cmpObj, SBloque * p_blqObj1, byte * p_byObj2 )
{
	int iRes;

	if ( SCmpEvaluarBloqueExt ( p_cmpObj, p_blqObj1, p_byObj2 ) == -1 )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCmpEvaluarBloqueEsDiferenteExt ( SComparador * p_cmpObj, SBloque * p_blqObj1, byte * p_byObj2 )
{
	int iRes;

	if ( SCmpEvaluarBloqueExt ( p_cmpObj, p_blqObj1, p_byObj2 ) != 0 )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

