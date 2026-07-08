#include "SIdAdap.h"

#include "TiposDatosConfig.h"


SIdAdap * SIdAdpCrear ( int iTam )
{
	return ( SIdAdpCrearExt ( iTam, NULL ) );
}

SIdAdap * SIdAdpCrearExt ( int iTam, const char * p_cPatron )
{
	SIdAdap * p_idObj;
	
	if ( ( iTam > 0 ) && ( PatEsValido ( p_cPatron ) == 1 ) )
	{
		if ( CadLongitud ( p_cPatron ) == iTam )
		{
			p_idObj = (SIdAdap *) MemReservar ( sizeof ( SIdAdap ) );
			if ( ES_VALIDO ( p_idObj ) )
			{
				p_idObj->iTam = iTam;
				p_idObj->p_cPatron = CadDuplicar ( p_cPatron );
				p_idObj->p_cValor = PatValorInicial ( p_idObj->p_cPatron );
			}
		}
		else
		{
			p_idObj = NULL;
		}
	}
	else
	{
		p_idObj = NULL;
	}
	return ( p_idObj );
}

void SIdAdpDestruir ( SIdAdap ** p_p_idObj )
{
	SIdAdap * p_idObj;
	
	if ( ES_VALIDO ( p_p_idObj ) )
	{
		p_idObj = *p_p_idObj;

		if ( ES_VALIDO ( p_idObj ) )
		{
			MemLiberar ( (void **) &(p_idObj->p_cPatron) );
			MemLiberar ( (void **) &(p_idObj->p_cValor) );
			MemLiberar ( (void **) p_p_idObj );
		}
	}
}

int SIdAdpEsValido ( SIdAdap * p_idObj )
{
	int iRes;

	if ( ES_VALIDO ( p_idObj ) )
	{
		if ( ( p_idObj->iTam > 0 ) && ( PatEsValido ( p_idObj->p_cPatron ) == 1 ) &&
			 ( CadLongitud ( p_idObj->p_cPatron ) == p_idObj->iTam ) &&
			 ( CadLongitud ( p_idObj->p_cValor ) == p_idObj->iTam ) )
		{
			iRes = PatEvaluar ( p_idObj->p_cPatron, p_idObj->p_cValor );
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

int SIdAdpTam ( SIdAdap * p_idObj )
{
	int iRes;

	if ( ES_VALIDO ( p_idObj ) )
	{
		iRes = p_idObj->iTam;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

const char * SIdAdpPatron ( SIdAdap * p_idObj )
{
	const char * p_cRes;

	if ( ES_VALIDO ( p_idObj ) )
	{
		p_cRes = p_idObj->p_cPatron;
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

const char * SIdAdpValor ( SIdAdap * p_idObj )
{
	const char * p_cRes;

	if ( ES_VALIDO ( p_idObj ) )
	{
		p_cRes = (const char *) p_idObj->p_cValor;
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

int SIdAdpEstablecer ( SIdAdap * p_idObj, const char * p_cValor )
{
	int iRes;

	if ( ES_VALIDO ( p_idObj ) )
	{
		if ( PatEvaluar ( p_idObj->p_cPatron, p_cValor ) == 1 )
		{
			iRes = CadCopiar ( p_idObj->p_cValor, p_cValor );
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

int SIdAdpEstablecerValorInicial ( SIdAdap * p_idObj )
{
	int		iRes;
	char *	p_cValor;

	if ( ES_VALIDO ( p_idObj ) )
	{
		p_cValor = PatValorInicial ( p_idObj->p_cPatron );
		iRes = SIdAdpEstablecer ( p_idObj, p_cValor );
		MemLiberar ( (void **) &p_cValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SIdAdpEstablecerValorFinal ( SIdAdap * p_idObj ) 
{
	int		iRes;
	char *	p_cValor;

	if ( ES_VALIDO ( p_idObj ) )
	{
		p_cValor = PatValorFinal ( p_idObj->p_cPatron );
		iRes = SIdAdpEstablecer ( p_idObj, p_cValor );
		MemLiberar ( (void **) &p_cValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SIdAdpEsCompatible ( SIdAdap * p_idObj, SIdAdap * p_idValor )
{
	int iRes;

	if ( ( SIdAdpEsValido ( p_idObj ) == 1 ) && ( SIdAdpEsValido ( p_idValor ) == 1 ) )
	{
		if ( PatEsSubpatron ( p_idObj->p_cPatron, SIdAdpPatron ( p_idValor ) ) == 1 )
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

int SIdAdpEsCompatibleValor ( SIdAdap * p_idObj, const char * p_cValor )
{
	int iRes;

	if ( ( SIdAdpEsValido ( p_idObj ) == 1 ) && ES_VALIDO ( p_cValor ) )
	{
		if ( PatEvaluar ( p_idObj->p_cPatron, p_cValor ) == 1 )
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

int SIdAdpAsignar ( SIdAdap * p_idObj, SIdAdap * p_idValor ) 
{
	int iRes;

	if ( SIdAdpEsCompatible ( p_idObj, p_idValor ) == 1 ) 
	{
		iRes = SIdAdpEstablecer ( p_idObj, SIdAdpPatron ( p_idValor ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

SIdAdap * SIdAdpDuplicar (  SIdAdap * p_idObj )
{
	SIdAdap * p_idRes;

	if ( ES_VALIDO ( p_idObj ) )
	{
		p_idRes = SIdAdpCrearExt ( p_idObj->iTam, p_idObj->p_cPatron );
		if ( ES_VALIDO ( p_idRes ) )
		{
			SIdAdpEstablecer ( p_idRes, p_idObj->p_cValor );
		}
	}
	else
	{
		p_idRes = NULL;
	}
	return ( p_idRes );
}

int SIdAdpIncrementar ( SIdAdap * p_idObj )
{
	int iRes;

	if ( SIdAdpEsValido ( p_idObj ) == 1 ) 
	{
		iRes = PatIncrementarValor ( p_idObj->p_cPatron, p_idObj->p_cValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SIdAdpDecrementar ( SIdAdap * p_idObj )
{
	int iRes;

	if ( SIdAdpEsValido ( p_idObj ) == 1 ) 
	{
		iRes = PatDecrementarValor ( p_idObj->p_cPatron, p_idObj->p_cValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SIdAdpIncrementarDesde ( SIdAdap * p_idObj, int iPos )
{
	int iRes;

	if ( SIdAdpEsValido ( p_idObj ) == 1 ) 
	{
		iRes = PatIncrementarValorDesde ( p_idObj->p_cPatron, p_idObj->p_cValor, iPos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SIdAdpDecrementarDesde ( SIdAdap * p_idObj, int iPos )
{
	int iRes;

	if ( SIdAdpEsValido ( p_idObj ) == 1 ) 
	{
		iRes = PatDecrementarValorDesde ( p_idObj->p_cPatron, p_idObj->p_cValor, iPos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SIdAdpEsIgual ( SIdAdap * p_idObj, SIdAdap * p_idVal )
{
	int iRes;

	if ( ( SIdAdpEsValido ( p_idObj ) == 1 ) && ( SIdAdpEsCompatible ( p_idObj, p_idVal ) == 1 ) )
	{
		if ( CadCompararSinDistinguirTipoLetra ( p_idObj->p_cValor, SIdAdpValor ( p_idVal ) ) == COMP_IGUAL )
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

int SIdAdpEsMenor ( SIdAdap * p_idObj, SIdAdap * p_idVal )
{
	int iRes;

	if ( ( SIdAdpEsValido ( p_idObj ) == 1 ) && ( SIdAdpEsCompatible ( p_idObj, p_idVal ) == 1 ) )
	{
		if ( CadCompararSinDistinguirTipoLetra ( p_idObj->p_cValor, SIdAdpValor ( p_idVal ) ) == COMP_MENOR )
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

int SIdAdpEsMayor ( SIdAdap * p_idObj, SIdAdap * p_idVal )
{
	int iRes;

	if ( ( SIdAdpEsValido ( p_idObj ) == 1 ) && ( SIdAdpEsCompatible ( p_idObj, p_idVal ) == 1 ) )
	{
		if ( CadCompararSinDistinguirTipoLetra ( p_idObj->p_cValor, SIdAdpValor ( p_idVal ) ) == COMP_MAYOR )
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

int SIdAdpEstaEnRango ( SIdAdap * p_idObj, SIdAdap * p_idVal1, SIdAdap * p_idVal2 )
{
	int iRes;

	if ( ( SIdAdpEsValido ( p_idObj ) == 1 ) && ( SIdAdpEsCompatible ( p_idObj, p_idVal1 ) == 1 ) &&
		 ( SIdAdpEsCompatible ( p_idObj, p_idVal2 ) == 1 ) )
	{
		if ( ( CadCompararSinDistinguirTipoLetra ( p_idObj->p_cValor, SIdAdpValor ( p_idVal1 ) ) == COMP_MAYOR ) &&
			 ( CadCompararSinDistinguirTipoLetra ( p_idObj->p_cValor, SIdAdpValor ( p_idVal2 ) ) == COMP_MENOR ) )
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

int SIdAdpEsMenorIg ( SIdAdap * p_idObj, SIdAdap * p_idVal )
{
	int	iCmp;
	int iRes;

	if ( ( SIdAdpEsValido ( p_idObj ) == 1 ) && ( SIdAdpEsCompatible ( p_idObj, p_idVal ) == 1 ) )
	{
		iCmp = CadCompararSinDistinguirTipoLetra ( p_idObj->p_cValor, SIdAdpValor ( p_idVal ) );
		if ( ( iCmp == 1 ) || ( iCmp == 2 ) )
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

int SIdAdpEsMayorIg ( SIdAdap * p_idObj, SIdAdap * p_idVal )
{
	int iCmp;
	int iRes;

	if ( ( SIdAdpEsValido ( p_idObj ) == 1 ) && ( SIdAdpEsCompatible ( p_idObj, p_idVal ) == 1 ) )
	{
		iCmp = CadCompararSinDistinguirTipoLetra ( p_idObj->p_cValor, SIdAdpValor ( p_idVal ) );
		if ( ( iCmp == 1 ) || ( iCmp == 3 ) )
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

int SIdAdpEstaEnRangoIg ( SIdAdap * p_idObj, SIdAdap * p_idVal1, SIdAdap * p_idVal2 )
{
	int iCmp1;
	int iCmp2;
	int iRes;

	if ( ( SIdAdpEsValido ( p_idObj ) == 1 ) && ( SIdAdpEsCompatible ( p_idObj, p_idVal1 ) == 1 ) &&
		 ( SIdAdpEsCompatible ( p_idObj, p_idVal2 ) == 1 ) )
	{
		iCmp1 = CadCompararSinDistinguirTipoLetra ( p_idObj->p_cValor, SIdAdpValor ( p_idVal1 ) );
		iCmp2 = CadCompararSinDistinguirTipoLetra ( p_idObj->p_cValor, SIdAdpValor ( p_idVal2 ) );
		if ( ( ( iCmp1 == 1 ) || ( iCmp1 == 3 ) ) && ( ( iCmp2 == 1 ) || ( iCmp2 == 2 ) ) )
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

