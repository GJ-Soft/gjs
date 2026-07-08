#include "SLocalizadorExt.h"

#include "TiposDatosConfig.h"


SLocalizadorExt * SLczExtCrearDef ()
{
	return ( SLczExtCrear ( NULL ) );
}

SLocalizadorExt * SLczExtCrear ( const char * p_cClave )
{
	SLocalizadorExt * p_lczeObj;
	
	p_lczeObj = (SLocalizadorExt *) MemReservar ( sizeof ( SLocalizadorExt ) );
	if ( ES_VALIDO ( p_lczeObj ) )
	{
		p_lczeObj->p_cClave = NULL;
		p_lczeObj->p_lisPosiciones = SLisEntCrear ();
		if ( SLczExtEstablecerClave ( p_lczeObj,  p_cClave ) == 0 )
		{
			SLczExtDestruir ( &p_lczeObj );
		}
	}
	return ( p_lczeObj );
}

void SLczExtDestruir ( SLocalizadorExt ** p_p_lczeObj )
{
	SLocalizadorExt * p_lczeObj;
	
	if ( ES_VALIDO ( p_p_lczeObj ) )
	{
		p_lczeObj = *p_p_lczeObj;

		if ( ES_VALIDO ( p_lczeObj ) )
		{
			SLisEntDestruir ( &(p_lczeObj->p_lisPosiciones) );
			MemLiberar ( (void **) &(p_lczeObj->p_cClave) );
			MemLiberar ( (void **) p_p_lczeObj );
		}
	}
}

int SLczExtEsValido ( SLocalizadorExt * p_lczeObj )
{
	int iRes;

	if ( ES_VALIDO ( p_lczeObj ) )
	{
		if ( ( CadEsTokenValido ( p_lczeObj->p_cClave ) == 1 )&&
			 ( SLisEntNumElementos ( p_lczeObj->p_lisPosiciones ) > 0 ) )
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

const char * SLczExtClave ( SLocalizadorExt * p_lczeObj )
{
	const char * p_cRes;

	if ( ES_VALIDO ( p_lczeObj ) )
	{
		p_cRes = p_lczeObj->p_cClave;
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

int SLczExtPosicionPrinc ( SLocalizadorExt * p_lczeObj )
{
	int iRes;

	if ( ES_VALIDO ( p_lczeObj ) )
	{
		iRes = SLisEntElemento ( p_lczeObj->p_lisPosiciones, 0 );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int SLczExtEstablecer ( SLocalizadorExt * p_lczeObj, const char * p_cClave, int iPosicion )
{
	int iRes;

	if ( ES_VALIDO ( p_lczeObj ) )
	{
		if ( ( SLczExtEstablecerClave ( p_lczeObj, p_cClave ) == 1 ) &&
			 ( SLczExtEstablecerPosicionPrinc ( p_lczeObj, iPosicion ) == 1 ) )
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


int SLczExtEstablecerClave ( SLocalizadorExt * p_lczeObj, const char * p_cClave )
{
	int iRes;

	if ( ES_VALIDO ( p_lczeObj ) )
	{
		if ( CadEsTokenValido ( p_cClave ) == 1 )
		{
			MemLiberar ( (void **) &(p_lczeObj->p_cClave) );
			p_lczeObj->p_cClave = CadDuplicar ( p_cClave ); 
			if ( ES_VALIDO ( p_lczeObj->p_cClave ) )
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

int SLczExtEstablecerPosicionPrinc ( SLocalizadorExt * p_lczeObj, int iPosicion )
{
	return ( SLczExtEstablecerPosicion ( p_lczeObj, 0, iPosicion ) );
}

int SLczExtNumPosiciones ( SLocalizadorExt * p_lczeObj )
{
	int iRes;

	if ( ES_VALIDO ( p_lczeObj ) )
	{
		iRes = SLisEntNumElementos ( p_lczeObj->p_lisPosiciones );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLczExtPosicion ( SLocalizadorExt * p_lczeObj, int iPos )
{
	int iRes;

	if ( ES_VALIDO ( p_lczeObj ) )
	{
		iRes = SLisEntElemento ( p_lczeObj->p_lisPosiciones, iPos );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int SLczExtEstablecerPosicion ( SLocalizadorExt * p_lczeObj, int iPos, int iPosicion ) 
{
	int iRes;

	if ( ES_VALIDO ( p_lczeObj ) )
	{
		iRes = SLisEntEstablecerElem ( p_lczeObj->p_lisPosiciones, iPos, iPosicion );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLczExtInsertarPosicion ( SLocalizadorExt * p_lczeObj, int iPosicion )
{
	int iRes;

	if ( ES_VALIDO ( p_lczeObj ) )
	{
		iRes = SLisEntInsertarAlFinal ( p_lczeObj->p_lisPosiciones, iPosicion );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

SLocalizadorExt * SLczExtDuplicar (  SLocalizadorExt * p_lczeObj )
{
	int					iPos;
	SLocalizadorExt * 	p_lczeRes;

	if ( ES_VALIDO ( p_lczeObj ) )
	{
		p_lczeRes = SLczExtCrear ( p_lczeObj->p_cClave );
		if ( ES_VALIDO ( p_lczeRes ) )
		{
			for ( iPos = 0; iPos < SLczExtNumPosiciones ( p_lczeObj ); iPos = iPos + 1 )
			{
				SLczExtInsertarPosicion ( p_lczeRes, SLczExtPosicion ( p_lczeObj, iPos ) );
			}
		}
	}
	else
	{
		p_lczeRes = NULL;
	}
	return ( p_lczeRes );
}

int SLczExtEsIgual ( SLocalizadorExt * p_lczeObj, const char * p_cClave )
{
	int iRes;

	if ( ( SLczExtEsValido ( p_lczeObj ) == 1 ) && ( CadEsTokenValido ( p_cClave ) == 1 ) )
	{
		if ( CadCompararSinDistinguirTipoLetra ( p_lczeObj->p_cClave, p_cClave ) == COMP_IGUAL )
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

int SLczExtEsMenor ( SLocalizadorExt * p_lczeObj, const char * p_cClave )
{
	int iRes;

	if ( ( SLczExtEsValido ( p_lczeObj ) == 1 ) && ( CadEsTokenValido ( p_cClave ) == 1 ) )
	{
		if ( CadCompararSinDistinguirTipoLetra ( p_lczeObj->p_cClave, p_cClave ) == COMP_MENOR )
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

int SLczExtEsMayor ( SLocalizadorExt * p_lczeObj, const char * p_cClave )
{
	int iRes;

	if ( ( SLczExtEsValido ( p_lczeObj ) == 1 ) && ( CadEsTokenValido ( p_cClave ) == 1 ) )
	{
		if ( CadCompararSinDistinguirTipoLetra ( p_lczeObj->p_cClave, p_cClave ) == COMP_MAYOR )
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


