#include "SLocalizador.h"

#include "TiposDatosConfig.h"


SLocalizador * SLczCrearDef ()
{
	return ( SLczCrear ( NULL ) );
}

SLocalizador * SLczCrear ( const char * p_cClave )
{
	SLocalizador * p_lczObj;
	
	p_lczObj = (SLocalizador *) MemReservar ( sizeof ( SLocalizador ) );
	if ( ES_VALIDO ( p_lczObj ) )
	{
		p_lczObj->p_cClave = NULL;
		p_lczObj->iPosicion = -1;
		if ( SLczEstablecerClave ( p_lczObj,  p_cClave ) == 0 )
		{
			SLczDestruir ( &p_lczObj );
		}
	}
	return ( p_lczObj );
}

void SLczDestruir ( SLocalizador ** p_p_lczObj )
{
	SLocalizador * p_lczObj;
	
	if ( ES_VALIDO ( p_p_lczObj ) )
	{
		p_lczObj = *p_p_lczObj;

		if ( ES_VALIDO ( p_lczObj ) )
		{
			MemLiberar ( (void **) &(p_lczObj->p_cClave) );
			MemLiberar ( (void **) p_p_lczObj );
		}
	}
}

int SLczEsValido ( SLocalizador * p_lczObj )
{
	int iRes;

	if ( ES_VALIDO ( p_lczObj ) )
	{
		if ( ( CadEsTokenValido ( p_lczObj->p_cClave ) == 1 ) &&
			 ( p_lczObj->iPosicion > 0 ) )
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

const char * SLczClave ( SLocalizador * p_lczObj )
{
	const char * p_cRes;

	if ( ES_VALIDO ( p_lczObj ) )
	{
		p_cRes = p_lczObj->p_cClave;
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

int SLczPosicion ( SLocalizador * p_lczObj )
{
	int iRes;

	if ( ES_VALIDO ( p_lczObj ) )
	{
		iRes = p_lczObj->iPosicion;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLczEstablecer ( SLocalizador * p_lczObj, const char * p_cClave, int iPosicion )
{
	int iRes;

	if ( ES_VALIDO ( p_lczObj ) )
	{
		if ( SLczEstablecerClave ( p_lczObj, p_cClave ) == 1 ) 
		{
			p_lczObj->iPosicion = iPosicion;
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


int SLczEstablecerClave ( SLocalizador * p_lczObj, const char * p_cClave )
{
	int iRes;

	if ( ES_VALIDO ( p_lczObj ) )
	{
		if ( CadEsTokenValido ( p_cClave ) == 1 )
		{
			MemLiberar ( (void **) &(p_lczObj->p_cClave) );
			p_lczObj->p_cClave = CadDuplicar ( p_cClave ); 
			if ( ES_VALIDO ( p_lczObj->p_cClave ) )
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
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}


int SLczEstablecerPosicion ( SLocalizador * p_lczObj, int iPosicion )
{
	int iRes;

	if ( ES_VALIDO ( p_lczObj ) )
	{
		p_lczObj->iPosicion = iPosicion;
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

SLocalizador * SLczDuplicar (  SLocalizador * p_lczObj )
{
	SLocalizador * p_lczRes;

	if ( ES_VALIDO ( p_lczObj ) )
	{
		p_lczRes = SLczCrear ( p_lczObj->p_cClave );
		if ( ES_VALIDO ( p_lczRes ) )
		{
			SLczEstablecerPosicion ( p_lczRes, p_lczObj->iPosicion );
		}
	}
	else
	{
		p_lczRes = NULL;
	}
	return ( p_lczRes );
}

int SLczEsIgual ( SLocalizador * p_lczObj, const char * p_cClave )
{
	int iRes;

	if ( ( SLczEsValido ( p_lczObj ) == 1 ) && ( CadEsTokenValido ( p_cClave ) == 1 ) )
	{
		if ( CadCompararSinDistinguirTipoLetra ( p_lczObj->p_cClave, p_cClave ) == COMP_IGUAL )
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

int SLczEsMenor ( SLocalizador * p_lczObj, const char * p_cClave )
{
	int iRes;

	if ( ( SLczEsValido ( p_lczObj ) == 1 ) && ( CadEsTokenValido ( p_cClave ) == 1 ) )
	{
		if ( CadCompararSinDistinguirTipoLetra ( p_lczObj->p_cClave, p_cClave ) == COMP_MENOR )
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

int SLczEsMayor ( SLocalizador * p_lczObj, const char * p_cClave )
{
	int iRes;

	if ( ( SLczEsValido ( p_lczObj ) == 1 ) && ( CadEsTokenValido ( p_cClave ) == 1 ) )
	{
		if ( CadCompararSinDistinguirTipoLetra ( p_lczObj->p_cClave, p_cClave ) == COMP_MAYOR )
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


