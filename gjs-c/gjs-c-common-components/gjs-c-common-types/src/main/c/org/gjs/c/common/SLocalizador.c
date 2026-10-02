#include "SLocalizador.h"

#include "TiposDatosConfig.h"


static int _SLczEsComparable ( SLocalizador * p_lczObj )
{
	int iRes;

	if ( ES_VALIDO ( p_lczObj ) )
	{
		iRes = CadEsTokenValido ( p_lczObj->p_cClave );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}




SLocalizador * SLczCrear ( const char * p_cClave )
{
	return ( SLczCrearExt ( p_cClave, SLCZ_SIN_POSICION ) );
}

SLocalizador * SLczCrearExt ( const char * p_cClave, unsigned long ulPosicion )
{
	SLocalizador * p_lczObj;
	
	p_lczObj = (SLocalizador *) MemReservar ( sizeof ( SLocalizador ) );
	if ( ES_VALIDO ( p_lczObj ) )
	{
		p_lczObj->p_cClave = NULL;
		p_lczObj->ulPosicion = ulPosicion;
		if ( ES_VALIDO ( p_cClave ) )
		{
			if ( SLczEstablecerClave ( p_lczObj,  p_cClave ) == 0 )
			{
				SLczDestruir ( &p_lczObj );
			}
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
			 ( p_lczObj->ulPosicion != SLCZ_SIN_POSICION ) )
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

unsigned long SLczPosicion ( SLocalizador * p_lczObj )
{
	unsigned long ulRes;

	if ( ES_VALIDO ( p_lczObj ) )
	{
		ulRes = p_lczObj->ulPosicion;
	}
	else
	{
		ulRes = SLCZ_SIN_POSICION;
	}
	return ( ulRes );
}

int SLczEstablecer ( SLocalizador * p_lczObj, const char * p_cClave, unsigned long ulPosicion )
{
	int iRes;

	if ( ES_VALIDO ( p_lczObj ) )
	{
		if ( SLczEstablecerClave ( p_lczObj, p_cClave ) == 1 ) 
		{
			p_lczObj->ulPosicion = ulPosicion;
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


int SLczEstablecerPosicion ( SLocalizador * p_lczObj, unsigned long ulPosicion )
{
	int iRes;

	if ( ES_VALIDO ( p_lczObj ) )
	{
		p_lczObj->ulPosicion = ulPosicion;
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
			SLczEstablecerPosicion ( p_lczRes, p_lczObj->ulPosicion );
		}
	}
	else
	{
		p_lczRes = NULL;
	}
	return ( p_lczRes );
}

int SLczEsIgual ( SLocalizador * p_lczObj, SLocalizador * p_lczValor )
{
	return ( SLczEsIgualExt ( p_lczObj, p_lczValor, 1 ) );
}
		
int SLczEsMenor ( SLocalizador * p_lczObj, SLocalizador * p_lczValor )
{
	return ( SLczEsMenorExt ( p_lczObj, p_lczValor, 1 ) );
}
		
int SLczEsMayor ( SLocalizador * p_lczObj, SLocalizador * p_lczValor )
{
	return ( SLczEsMayorExt ( p_lczObj, p_lczValor, 1 ) );
}
		
int SLczEsIgualLit ( SLocalizador * p_lczObj, const char * p_cClave )
{
	return ( SLczEsIgualLitExt ( p_lczObj, p_cClave, 1 ) );
}

int SLczEsMenorLit ( SLocalizador * p_lczObj, const char * p_cClave )
{
	return ( SLczEsMenorLitExt ( p_lczObj, p_cClave, 1 ) );
}

int SLczEsMayorLit ( SLocalizador * p_lczObj, const char * p_cClave )
{
	return ( SLczEsMayorLitExt ( p_lczObj, p_cClave, 1 ) );
}

int SLczComparar ( SLocalizador * p_lczObj, SLocalizador * p_lczValor )
{
	return ( SLczCompararExt ( p_lczObj, p_lczValor, 1 ) );
}
		
int SLczCompararLit ( SLocalizador * p_lczObj, const char * p_cClave )
{
	return ( SLczCompararLitExt ( p_lczObj, p_cClave, 1 ) );
}

int SLczEsIgualExt ( SLocalizador * p_lczObj, SLocalizador * p_lczValor, int iDistinguir )
{
	int iRes;

	if ( ES_VALIDO ( p_lczObj ) && ES_VALIDO ( p_lczValor ) )
	{
		iRes = SLczEsIgualLitExt ( p_lczObj, SLczClave ( p_lczValor ), iDistinguir );
	}
	else if ( ES_NULO ( p_lczObj ) && ES_NULO ( p_lczValor ) )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}
		
int SLczEsMenorExt ( SLocalizador * p_lczObj, SLocalizador * p_lczValor, int iDistinguir )
{
	int iRes;

	if ( ES_VALIDO ( p_lczObj ) && ES_VALIDO ( p_lczValor ) )
	{
		iRes = SLczEsMenorLitExt ( p_lczObj, SLczClave ( p_lczValor ), iDistinguir );
	}
	else if ( ES_NULO ( p_lczObj ) && ES_VALIDO ( p_lczValor ) )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}
		
int SLczEsMayorExt ( SLocalizador * p_lczObj, SLocalizador * p_lczValor, int iDistinguir )
{
	int iRes;

	if ( ES_VALIDO ( p_lczObj ) && ES_VALIDO ( p_lczValor ) )
	{
		iRes = SLczEsMayorLitExt ( p_lczObj, SLczClave ( p_lczValor ), iDistinguir );
	}
	else if ( ES_VALIDO ( p_lczObj ) && ES_NULO ( p_lczValor ) )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}
		
int SLczEsIgualLitExt ( SLocalizador * p_lczObj, const char * p_cClave, int iDistinguir )
{
	int iRes;

	if ( ( _SLczEsComparable ( p_lczObj ) == 1 ) && ( CadEsTokenValido ( p_cClave ) == 1 ) )
	{
		if ( iDistinguir == 0 )
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
			if ( CadComparar ( p_lczObj->p_cClave, p_cClave ) == COMP_IGUAL )
			{
				iRes = 1;
			}
			else
			{
				iRes = 0;
			}
		}	
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLczEsMenorLitExt ( SLocalizador * p_lczObj, const char * p_cClave, int iDistinguir )
{
	int iRes;

	if ( ( _SLczEsComparable ( p_lczObj ) == 1 ) && ( CadEsTokenValido ( p_cClave ) == 1 ) )
	{
		if ( iDistinguir == 0 )
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
			if ( CadComparar ( p_lczObj->p_cClave, p_cClave ) == COMP_MENOR )
			{
				iRes = 1;
			}
			else
			{
				iRes = 0;
			}
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLczEsMayorLitExt ( SLocalizador * p_lczObj, const char * p_cClave, int iDistinguir )
{
	int iRes;

	if ( ( _SLczEsComparable ( p_lczObj ) == 1 ) && ( CadEsTokenValido ( p_cClave ) == 1 ) )
	{
		if ( iDistinguir == 0 )
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
			if ( CadComparar ( p_lczObj->p_cClave, p_cClave ) == COMP_MAYOR )
			{
				iRes = 1;
			}
			else
			{
				iRes = 0;
			}
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLczCompararExt ( SLocalizador * p_lczObj, SLocalizador * p_lczValor, int iDistinguir )
{
	int iRes;

	if ( ES_VALIDO ( p_lczObj ) && ES_VALIDO ( p_lczValor ) )
	{
		iRes = SLczCompararLitExt ( p_lczObj, SLczClave ( p_lczValor ), iDistinguir );
	}
	else if ( ES_NULO ( p_lczObj ) && ES_NULO ( p_lczValor ) )
	{
		iRes = COMP_IGUAL;
	}
	else if ( ES_VALIDO ( p_lczObj ) ) 
	{
		iRes = COMP_MAYOR;
	}
	else 
	{
		iRes = COMP_MENOR;
	}
	return ( iRes );
}
		
int SLczCompararLitExt ( SLocalizador * p_lczObj, const char * p_cClave, int iDistinguir )
{
	int iRes;

	if ( ( _SLczEsComparable ( p_lczObj ) == 1 ) && ( CadEsTokenValido ( p_cClave ) == 1 ) )
	{
		if ( iDistinguir == 0 )
		{
			iRes = CadCompararSinDistinguirTipoLetra ( p_lczObj->p_cClave, p_cClave );
		}
		else
		{
			iRes = CadComparar ( p_lczObj->p_cClave, p_cClave );
		}
	}
	else if ( _SLczEsComparable ( p_lczObj ) == 1 ) 
	{
		iRes = COMP_MAYOR;
	}
	else if ( CadEsTokenValido ( p_cClave ) == 1 )
	{
		iRes = COMP_MENOR;
	}
	else 
	{
		iRes = COMP_IGUAL;
	}
	return ( iRes );
}


