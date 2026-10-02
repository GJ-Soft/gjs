#include "SLocalizadorExt.h"
#include "SLocalizador.h"

#include "TiposDatosConfig.h"



static int _SLczExtEsComparable ( SLocalizadorExt * p_lczeObj )
{
	int iRes;

	if ( ES_VALIDO ( p_lczeObj ) )
	{
		iRes = CadEsTokenValido ( p_lczeObj->p_cClave );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}


SLocalizadorExt * SLczExtCrear ( const char * p_cClave )
{
	SLocalizadorExt * p_lczeObj;
	
	p_lczeObj = (SLocalizadorExt *) MemReservar ( sizeof ( SLocalizadorExt ) );
	if ( ES_VALIDO ( p_lczeObj ) )
	{
		p_lczeObj->p_cClave = NULL;
		p_lczeObj->p_lisPosiciones = SLisEntLssCrear ();
		if ( ES_VALIDO ( p_cClave ) )
		{
			if ( SLczExtEstablecerClave ( p_lczeObj,  p_cClave ) == 0 )
			{
				SLczExtDestruir ( &p_lczeObj );
			}
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
			SLisEntLssDestruir ( &(p_lczeObj->p_lisPosiciones) );
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
			 ( SLisEntLssNumElementos ( p_lczeObj->p_lisPosiciones ) > 0 ) )
		{
			if ( SLisEntLssExiste ( p_lczeObj->p_lisPosiciones, SLCZ_SIN_POSICION ) == 0 )
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

unsigned long SLczExtPosicionPrinc ( SLocalizadorExt * p_lczeObj )
{
	return ( SLczExtPosicion ( p_lczeObj, 0 ) );
}

int SLczExtEstablecer ( SLocalizadorExt * p_lczeObj, const char * p_cClave, unsigned long ulPosicion )
{
	int iRes;

	if ( ES_VALIDO ( p_lczeObj ) )
	{
		if ( ( SLczExtEstablecerClave ( p_lczeObj, p_cClave ) == 1 ) &&
			 ( SLczExtEstablecerPosicionPrinc ( p_lczeObj, ulPosicion ) == 1 ) )
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

int SLczExtEstablecerPosicionPrinc ( SLocalizadorExt * p_lczeObj, unsigned long ulPosicion )
{
	int iRes;

	if ( ES_VALIDO ( p_lczeObj ) )
	{
		/* Sin posiciones todavia no hay elemento 0 que establecer: la
		   principal se anade. */
		if ( SLisEntLssEstaVacia ( p_lczeObj->p_lisPosiciones ) == 1 )
		{
			iRes = SLisEntLssInsertarAlFinal ( p_lczeObj->p_lisPosiciones, ulPosicion );
		}
		else
		{
			iRes = SLczExtEstablecerPosicion ( p_lczeObj, 0, ulPosicion );
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLczExtNumPosiciones ( SLocalizadorExt * p_lczeObj )
{
	int iRes;

	if ( ES_VALIDO ( p_lczeObj ) )
	{
		iRes = SLisEntLssNumElementos ( p_lczeObj->p_lisPosiciones );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

unsigned long SLczExtPosicion ( SLocalizadorExt * p_lczeObj, int iPos )
{
	unsigned long ulRes;

	if ( ES_VALIDO ( p_lczeObj ) )
	{
		if ( iPos >= 0 )
		{
			if ( iPos < SLisEntLssNumElementos ( p_lczeObj->p_lisPosiciones ) )
			{
				ulRes = SLisEntLssElemento ( p_lczeObj->p_lisPosiciones, iPos );
			}
			else
			{
				ulRes = SLCZ_SIN_POSICION;
			}
		}
		else
		{
			ulRes = SLCZ_SIN_POSICION;
		}
	}
	else
	{
		ulRes = SLCZ_SIN_POSICION;
	}
	return ( ulRes );
}

int SLczExtEstablecerPosicion ( SLocalizadorExt * p_lczeObj, int iPos, unsigned long ulPosicion ) 
{
	int iRes;

	if ( ES_VALIDO ( p_lczeObj ) )
	{
		iRes = SLisEntLssEstablecerElem ( p_lczeObj->p_lisPosiciones, iPos, ulPosicion );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLczExtInsertarPosicion ( SLocalizadorExt * p_lczeObj, unsigned long ulPosicion )
{
	int iRes;

	if ( ES_VALIDO ( p_lczeObj ) )
	{
		iRes = SLisEntLssInsertarAlFinal ( p_lczeObj->p_lisPosiciones, ulPosicion );
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


int SLczExtEsIgual ( SLocalizadorExt * p_lczeObj, SLocalizadorExt * p_lczeValor )
{
	return ( SLczExtEsIgualExt ( p_lczeObj, p_lczeValor, 1 ) );
}
		
int SLczExtEsMenor ( SLocalizadorExt * p_lczeObj, SLocalizadorExt * p_lczeValor )
{
	return ( SLczExtEsMenorExt ( p_lczeObj, p_lczeValor, 1 ) );
}
		
int SLczExtEsMayor ( SLocalizadorExt * p_lczeObj, SLocalizadorExt * p_lczeValor )
{
	return ( SLczExtEsMayorExt ( p_lczeObj, p_lczeValor, 1 ) );
}
		
int SLczExtEsIgualLit ( SLocalizadorExt * p_lczeObj, const char * p_cClave )
{
	return ( SLczExtEsIgualLitExt ( p_lczeObj, p_cClave, 1 ) );
}

int SLczExtEsMenorLit ( SLocalizadorExt * p_lczeObj, const char * p_cClave )
{
	return ( SLczExtEsMenorLitExt ( p_lczeObj, p_cClave, 1 ) );
}

int SLczExtEsMayorLit ( SLocalizadorExt * p_lczeObj, const char * p_cClave )
{
	return ( SLczExtEsMayorLitExt ( p_lczeObj, p_cClave, 1 ) );
}

int SLczExtComparar ( SLocalizadorExt * p_lczeObj, SLocalizadorExt * p_lczeValor )
{
	return ( SLczExtCompararExt ( p_lczeObj, p_lczeValor, 1 ) );
}
		
int SLczExtCompararLit ( SLocalizadorExt * p_lczeObj, const char * p_cClave )
{
	return ( SLczExtCompararLitExt ( p_lczeObj, p_cClave, 1 ) );
}

int SLczExtEsIgualExt ( SLocalizadorExt * p_lczeObj, SLocalizadorExt * p_lczeValor, int iDistinguir )
{
	int iRes;

	if ( ES_VALIDO ( p_lczeObj ) && ES_VALIDO ( p_lczeValor ) )
	{
		iRes = SLczExtEsIgualLitExt ( p_lczeObj, SLczExtClave ( p_lczeValor ), iDistinguir );
	}
	else if ( ES_NULO ( p_lczeObj ) && ES_NULO ( p_lczeValor ) )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}
		
int SLczExtEsMenorExt ( SLocalizadorExt * p_lczeObj, SLocalizadorExt * p_lczeValor, int iDistinguir )
{
	int iRes;

	if ( ES_VALIDO ( p_lczeObj ) && ES_VALIDO ( p_lczeValor ) )
	{
		iRes = SLczExtEsMenorLitExt ( p_lczeObj, SLczExtClave ( p_lczeValor ), iDistinguir );
	}
	else if ( ES_NULO ( p_lczeObj ) && ES_VALIDO ( p_lczeValor ) )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}
		
int SLczExtEsMayorExt ( SLocalizadorExt * p_lczeObj, SLocalizadorExt * p_lczeValor, int iDistinguir )
{
	int iRes;

	if ( ES_VALIDO ( p_lczeObj ) && ES_VALIDO ( p_lczeValor ) )
	{
		iRes = SLczExtEsMayorLitExt ( p_lczeObj, SLczExtClave ( p_lczeValor ), iDistinguir );
	}
	else if ( ES_VALIDO ( p_lczeObj ) && ES_NULO ( p_lczeValor ) )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}
		
int SLczExtEsIgualLitExt ( SLocalizadorExt * p_lczeObj, const char * p_cClave, int iDistinguir )
{
	int iRes;

	if ( ( _SLczExtEsComparable ( p_lczeObj ) == 1 ) && ( CadEsTokenValido ( p_cClave ) == 1 ) )
	{
		if ( iDistinguir == 0 )
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
			if ( CadComparar ( p_lczeObj->p_cClave, p_cClave ) == COMP_IGUAL )
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

int SLczExtEsMenorLitExt ( SLocalizadorExt * p_lczeObj, const char * p_cClave, int iDistinguir )
{
	int iRes;

	if ( ( _SLczExtEsComparable ( p_lczeObj ) == 1 ) && ( CadEsTokenValido ( p_cClave ) == 1 ) )
	{
		if ( iDistinguir == 0 )
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
			if ( CadComparar ( p_lczeObj->p_cClave, p_cClave ) == COMP_MENOR )
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

int SLczExtEsMayorLitExt ( SLocalizadorExt * p_lczeObj, const char * p_cClave, int iDistinguir )
{
	int iRes;

	if ( ( _SLczExtEsComparable ( p_lczeObj ) == 1 ) && ( CadEsTokenValido ( p_cClave ) == 1 ) )
	{
		if ( iDistinguir == 0 )
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
			if ( CadComparar ( p_lczeObj->p_cClave, p_cClave ) == COMP_MAYOR )
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

int SLczExtCompararExt ( SLocalizadorExt * p_lczeObj, SLocalizadorExt * p_lczeValor, int iDistinguir )
{
	int iRes;

	if ( ES_VALIDO ( p_lczeObj ) && ES_VALIDO ( p_lczeValor ) )
	{
		iRes = SLczExtCompararLitExt ( p_lczeObj, SLczExtClave ( p_lczeValor ), iDistinguir );
	}
	else if ( ES_NULO ( p_lczeObj ) && ES_NULO ( p_lczeValor ) )
	{
		iRes = COMP_IGUAL;
	}
	else if ( ES_VALIDO ( p_lczeObj ) ) 
	{
		iRes = COMP_MAYOR;
	}
	else 
	{
		iRes = COMP_MENOR;
	}
	return ( iRes );
}
		
int SLczExtCompararLitExt ( SLocalizadorExt * p_lczeObj, const char * p_cClave, int iDistinguir )
{
	int iRes;

	if ( ( _SLczExtEsComparable ( p_lczeObj ) == 1 ) && ( CadEsTokenValido ( p_cClave ) == 1 ) )
	{
		if ( iDistinguir == 0 )
		{
			iRes = CadCompararSinDistinguirTipoLetra ( p_lczeObj->p_cClave, p_cClave );
		}
		else
		{
			iRes = CadComparar ( p_lczeObj->p_cClave, p_cClave );
		}
	}
	else if ( _SLczExtEsComparable ( p_lczeObj ) == 1 ) 
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


