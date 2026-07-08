#include "SEntrada.h"

#include "TiposDatosConfig.h"

SEntrada * SEtrCrearDef ()
{
	return ( SEtrCrear ( NULL ) );
}

SEntrada * SEtrCrear ( const char * p_cNombre )
{
	SEntrada * p_etrObj;
	
	p_etrObj = (SEntrada *) MemReservar ( sizeof ( SEntrada ) );
	if ( ES_VALIDO ( p_etrObj ) )
	{
		p_etrObj->p_cNombre = NULL;
		p_etrObj->p_cDefinicion = NULL;
		if ( SEtrEstablecerNombre ( p_etrObj,  p_cNombre ) == 0 )
		{
			SEtrDestruir ( &p_etrObj );
		}
	}
	return ( p_etrObj );
}

SEntrada * SEtrCrearExt ( const char * p_cNombre, const char * p_cDefinicion )
{
	SEntrada * p_etrObj;

	p_etrObj = SEtrCrear ( p_cNombre );
	if ( ES_VALIDO ( p_etrObj ) )
	{
		if ( SEtrEstablecerDefinicion ( p_etrObj, p_cDefinicion ) == 0 )
		{
			SEtrDestruir ( &p_etrObj );
		}
	}
	return ( p_etrObj );
}

void SEtrDestruir ( SEntrada ** p_p_etrObj )
{
	SEntrada * p_etrObj;
	
	if ( ES_VALIDO ( p_p_etrObj ) )
	{
		p_etrObj = *p_p_etrObj;

		if ( ES_VALIDO ( p_etrObj ) )
		{
			MemLiberar ( (void **) &(p_etrObj->p_cNombre) );
			MemLiberar ( (void **) &(p_etrObj->p_cDefinicion) );
			MemLiberar ( (void **) p_p_etrObj );
		}
	}
}

int SEtrEsValido ( SEntrada * p_etrObj )
{
	int iRes;

	if ( ES_VALIDO ( p_etrObj ) )
	{
		if ( ( CadEsTokenValido ( p_etrObj->p_cNombre ) == 1 ) &&
			 ( CadLongitud ( p_etrObj->p_cDefinicion ) > 0 ) )
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

const char * SEtrNombre ( SEntrada * p_etrObj )
{
	const char * p_cRes;

	if ( ES_VALIDO ( p_etrObj ) )
	{
		p_cRes = p_etrObj->p_cNombre;
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

const char * SEtrDefinicion ( SEntrada * p_etrObj )
{
	const char * p_cRes;

	if ( ES_VALIDO ( p_etrObj ) )
	{
		p_cRes = (const char *) p_etrObj->p_cDefinicion;
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

int SEtrEstablecer ( SEntrada * p_etrObj, const char * p_cNombre, const char * p_cDefinicion )
{
	int iRes;

	if ( ES_VALIDO ( p_etrObj ) )
	{
		if ( ( SEtrEstablecerNombre ( p_etrObj, p_cNombre ) == 1 ) &&
			 ( SEtrEstablecerDefinicion ( p_etrObj, p_cDefinicion ) == 1 ) )
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


int SEtrEstablecerNombre ( SEntrada * p_etrObj, const char * p_cNombre )
{
	int iRes;

	if ( ES_VALIDO ( p_etrObj ) )
	{
		if ( CadEsTokenValido ( p_cNombre ) == 1 )
		{
			MemLiberar ( (void **) &(p_etrObj->p_cNombre) );
			p_etrObj->p_cNombre = CadDuplicar ( p_cNombre );
			if ( ES_VALIDO ( p_etrObj->p_cNombre ) )
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


int SEtrEstablecerDefinicion ( SEntrada * p_etrObj, const char * p_cDefinicion )
{
	int iRes;

	if ( ES_VALIDO ( p_etrObj ) )
	{
		MemLiberar ( (void **) &(p_etrObj->p_cDefinicion) );
		p_etrObj->p_cDefinicion = CadDuplicar ( p_cDefinicion );
		if ( ES_VALIDO ( p_etrObj->p_cDefinicion ) )
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

SEntrada * SEtrDuplicar (  SEntrada * p_etrObj )
{
	SEntrada * p_etrRes;

	if ( ES_VALIDO ( p_etrObj ) )
	{
		p_etrRes = SEtrCrear ( p_etrObj->p_cNombre );
		if ( ES_VALIDO ( p_etrRes ) )
		{
			SEtrEstablecerDefinicion ( p_etrRes, p_etrObj->p_cDefinicion );
		}
	}
	else
	{
		p_etrRes = NULL;
	}
	return ( p_etrRes );
}

int SEtrEsIgual ( SEntrada * p_etrObj1, SEntrada * p_etrObj2 )
{
	int iRes;

	if ( ( SEtrEsValido ( p_etrObj1 ) == 1 ) && ( SEtrEsValido ( p_etrObj2 ) == 1 ) )
	{
		if ( CadCompararSinDistinguirTipoLetra ( p_etrObj1->p_cNombre, p_etrObj2->p_cNombre ) == COMP_IGUAL )
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

int SEtrEsMenor ( SEntrada * p_etrObj1, SEntrada * p_etrObj2 )
{
	int iRes;

	if ( ( SEtrEsValido ( p_etrObj1 ) == 1 ) && ( SEtrEsValido ( p_etrObj2 ) == 1 ) )
	{
		if ( CadCompararSinDistinguirTipoLetra ( p_etrObj1->p_cNombre, p_etrObj2->p_cNombre ) == COMP_MENOR )
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

int SEtrEsMayor ( SEntrada * p_etrObj1, SEntrada * p_etrObj2 )
{
	int iRes;

	if ( ( SEtrEsValido ( p_etrObj1 ) == 1 ) && ( SEtrEsValido ( p_etrObj2 ) == 1 ) )
	{
		if ( CadCompararSinDistinguirTipoLetra ( p_etrObj1->p_cNombre, p_etrObj2->p_cNombre ) == COMP_MAYOR )
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

int SEtrEsIgualLit ( SEntrada * p_etrObj, const char * p_cNombre )
{
	int iRes;

	if ( ( SEtrEsValido ( p_etrObj ) == 1 ) && ( CadEsTokenValido ( p_cNombre ) == 1 ) )
	{
		if ( CadCompararSinDistinguirTipoLetra ( p_etrObj->p_cNombre, p_cNombre ) == COMP_IGUAL )
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

int SEtrEsMenorLit ( SEntrada * p_etrObj, const char * p_cNombre )
{
	int iRes;

	if ( ( SEtrEsValido ( p_etrObj ) == 1 ) && ( CadEsTokenValido ( p_cNombre ) == 1 ) )
	{
		if ( CadCompararSinDistinguirTipoLetra ( p_etrObj->p_cNombre, p_cNombre ) == COMP_MENOR )
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

int SEtrEsMayorLit ( SEntrada * p_etrObj, const char * p_cNombre )
{
	int iRes;

	if ( ( SEtrEsValido ( p_etrObj ) == 1 ) && ( CadEsTokenValido ( p_cNombre ) == 1 ) )
	{
		if ( CadCompararSinDistinguirTipoLetra ( p_etrObj->p_cNombre, p_cNombre ) == COMP_MAYOR )
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


