#include "SConversor.h"


#include "Memoria.h"
#include "ConversionesTipos.h"
#include "CadenasBase.h"







#define NOMBRE_CLASE				"SConversor"
#define TAM_CLASE					sizeof ( SConversor )




static void Inicializar ( SConversor * p_convObj );
static void InicializarCadena ( SConversor * p_convObj );




SConversor * SConvCrearDef ()
{
	SConversor * p_convObj;

	p_convObj = (SConversor *) MemReservar ( sizeof ( SConversor ) );
	if ( ES_VALIDO ( p_convObj ) )
	{
		Inicializar ( p_convObj );
	}
	return ( p_convObj );
}

SConversor * SConvCrearEntero ( int iValor )
{
	SConversor * p_convObj;

	p_convObj = SConvCrearDef ();
	SConvEstablecerValor ( p_convObj, iValor );
	return ( p_convObj );
}

SConversor * SConvCrearEnteroLargo ( long lValor )
{
	SConversor * p_convObj;

	p_convObj = SConvCrearDef ();
	SConvEstablecerValor ( p_convObj, lValor );
	return ( p_convObj );
}

SConversor * SConvCrearEnteroSinSigno ( unsigned int uiValor )
{
	SConversor * p_convObj;

	p_convObj = SConvCrearDef ();
	SConvEstablecerValor ( p_convObj, uiValor );
	return ( p_convObj );
}

SConversor * SConvCrearEnteroLargoSinSigno ( unsigned long ulValor )
{
	SConversor * p_convObj;

	p_convObj = SConvCrearDef ();
	SConvEstablecerValor ( p_convObj, ulValor );
	return ( p_convObj );
}

SConversor * SConvCrearReal ( float fValor )
{
	SConversor * p_convObj;

	p_convObj = SConvCrearDef ();
	SConvEstablecerValor ( p_convObj, fValor );
	return ( p_convObj );
}

SConversor * SConvCrearRealDoble ( double dValor )
{
	SConversor * p_convObj;

	p_convObj = SConvCrearDef ();
	SConvEstablecerValor ( p_convObj, dValor );
	return ( p_convObj );
}

SConversor * SConvCrearCadena ( char * p_cValor )
{
	SConversor * p_convObj;

	p_convObj = SConvCrearDef ();
	SConvEstablecerValor ( p_convObj, p_cValor );
	return ( p_convObj );
}

SConversor * SConvCrearCadenaConstante ( const char * p_cValor )
{
	SConversor * p_convObj;

	p_convObj = SConvCrearDef ();
	SConvEstablecerValor ( p_convObj, p_cValor );
	return ( p_convObj );
}

SConversor * SConvCrearEnteroDobleLargo ( long long llValor )
{
	SConversor * p_convObj;

	p_convObj = SConvCrearDef ();
	SConvEstablecerValor ( p_convObj, llValor );
	return ( p_convObj );
}

SConversor * SConvCrearEnteroDobleLargoSinSigno ( unsigned long long ullValor )
{
	SConversor * p_convObj;

	p_convObj = SConvCrearDef ();
	SConvEstablecerValor ( p_convObj, ullValor );
	return ( p_convObj );
}


void SConvDestruir ( SConversor ** p_p_convObj )
{
	SConversor * p_convObj;

	if ( ES_VALIDO ( p_p_convObj ) )
	{
		p_convObj = *p_p_convObj;

		if ( ES_VALIDO ( p_convObj ) )
		{
			MemLiberar ( (void **) &(p_convObj->p_cValor) );
			MemLiberar ( (void **) p_p_convObj );
		}
	}
}

int SConvEntero ( SConversor * p_convObj )
{
	if ( ES_VALIDO ( p_convObj ) )
	{
		return ( p_convObj->iValor );
	}
	else
	{
		return ( 0 );
	}
}

long SConvEnteroLargo ( SConversor * p_convObj )
{
	if ( ES_VALIDO ( p_convObj ) )
	{
		return ( p_convObj->lValor );
	}
	else
	{
		return ( 0 );
	}
}

unsigned int SConvEnteroSinSigno ( SConversor * p_convObj )
{
	if ( ES_VALIDO ( p_convObj ) )
	{
		return ( p_convObj->uiValor );
	}
	else
	{
		return ( 0 );
	}
}

unsigned long SConvEnteroLargoSinSigno ( SConversor * p_convObj )
{
	if ( ES_VALIDO ( p_convObj ) )
	{
		return ( p_convObj->ulValor );
	}
	else
	{
		return ( 0 );
	}
}

float SConvReal ( SConversor * p_convObj )
{
	if ( ES_VALIDO ( p_convObj ) )
	{
		return ( p_convObj->fValor );
	}
	else
	{
		return ( 0 );
	}
}

double SConvRealDoble ( SConversor * p_convObj )
{
	if ( ES_VALIDO ( p_convObj ) )
	{
		return ( p_convObj->dValor );
	}
	else
	{
		return ( 0 );
	}
}

const char * SConvCadena ( SConversor * p_convObj )
{
	if ( ES_VALIDO ( p_convObj ) )
	{
		return ( p_convObj->p_cValor );
	}
	else
	{
		return ( NULL );
	}
}

const char * SConvCadenaHex ( SConversor * p_convObj )
{
	if ( ES_VALIDO ( p_convObj ) )
	{
		return ( ConvEnteroLargoSinSignoACadenaHex ( p_convObj->ulValor ) );
	}
	else
	{
		return ( 0 );
	}
}

long long SConvEnteroDobleLargo ( SConversor * p_convObj )
{
	if ( ES_VALIDO ( p_convObj ) )
	{
		return ( p_convObj->llValor );
	}
	else
	{
		return ( 0 );
	}
}

unsigned long long SConvEnteroDobleLargoSinSigno ( SConversor * p_convObj )
{
	if ( ES_VALIDO ( p_convObj ) )
	{
		return ( p_convObj->ullValor );
	}
	else
	{
		return ( 0 );
	}
}

void SConvEstablecerValorEntero ( SConversor * p_convObj, int iValor )
{
	const char *	p_cAux;
	int				iCar;

	if ( ES_VALIDO ( p_convObj ) )
	{
		p_convObj->iConvValida = 1;
		p_convObj->iValor = iValor;
		p_convObj->lValor = (long) iValor;
		p_convObj->llValor = (long long) iValor;

		if ( iValor >= 0 )
		{
			p_convObj->uiValor = (unsigned int) p_convObj->iValor;
			p_convObj->ulValor = (unsigned long) p_convObj->iValor;
			p_convObj->ullValor = (unsigned long long) iValor;
		}
		else
		{
			p_convObj->iConvValida = 0;
			p_convObj->uiValor = 0;
			p_convObj->ulValor = 0;
			p_convObj->ullValor = 0;
		}
		p_convObj->dValor = (double) ( p_convObj->iValor );
		p_convObj->fValor = (float) ( p_convObj->iValor );

		InicializarCadena ( p_convObj );
		p_cAux = ConvEnteroACadena ( p_convObj->iValor );

		if ( ES_VALIDO ( p_cAux ) )
		{
			for ( iCar = 0; iCar < CadLongitudSeg ( p_cAux, CONV_MAX_TAM_CADENA ); iCar = iCar + 1 )
			{
				p_convObj->p_cValor [ iCar ] = p_cAux [ iCar ];
			}
			p_convObj->p_cValor [ iCar ] = (char) 0;
			MemLiberar ( (void **) &p_cAux );
		}
		else
		{
			p_convObj->iConvValida = 0;
		}
	}
}

void SConvEstablecerValorEnteroLargo ( SConversor * p_convObj, long lValor )
{
	const char *	p_cAux;
	int				iCar;

	if ( ES_VALIDO ( p_convObj ) )
	{
		p_convObj->iConvValida = 1;
		p_convObj->lValor = lValor;
		p_convObj->llValor = (long long) p_convObj->lValor;
		if ( ( p_convObj->lValor >= INT_MIN ) && ( p_convObj->lValor <= INT_MAX ) )
		{
			p_convObj->iValor = (int) p_convObj->lValor;
		}
		else
		{
			p_convObj->iConvValida = 0;
			p_convObj->iValor = 0;
		}
		if ( ( p_convObj->lValor >= 0 ) && ( (unsigned long) p_convObj->lValor <= (unsigned long) UINT_MAX ) )
		{
			p_convObj->uiValor = (unsigned int) p_convObj->lValor;
		}
		else
		{
			p_convObj->iConvValida = 0;
			p_convObj->uiValor = 0;
		}
		if ( p_convObj->lValor >= 0 )
		{
			p_convObj->ulValor = (unsigned long) p_convObj->lValor;
			p_convObj->ullValor = (unsigned long long) lValor;
		}
		else
		{
			p_convObj->iConvValida = 0;
			p_convObj->ulValor = 0;
			p_convObj->ullValor = 0;
		}
		p_convObj->dValor = (double) ( p_convObj->lValor );
		p_convObj->fValor = (float) ( p_convObj->lValor );

		InicializarCadena ( p_convObj );
		p_cAux = ConvEnteroLargoACadena ( p_convObj->lValor );
		if ( ES_VALIDO ( p_cAux ) )
		{
			for ( iCar = 0; iCar < CadLongitudSeg ( p_cAux, CONV_MAX_TAM_CADENA ); iCar = iCar + 1 )
			{
				p_convObj->p_cValor [ iCar ] = p_cAux [ iCar ];
			}
			p_convObj->p_cValor [ iCar ] = (char) 0;
			MemLiberar ( (void **) &p_cAux );
		}
		else
		{
			p_convObj->iConvValida = 0;
		}
	}
}

void SConvEstablecerValorEnteroSinSigno ( SConversor * p_convObj, unsigned int uiValor )
{
	const char *	p_cAux;
	int				iCar;

	if ( ES_VALIDO ( p_convObj ) )
	{
		p_convObj->iConvValida = 1;
		p_convObj->uiValor = uiValor;
		p_convObj->ulValor = (unsigned long) uiValor;
		p_convObj->ullValor = (unsigned long long) uiValor;
		p_convObj->llValor = (long long) uiValor;
		if ( p_convObj->uiValor <= INT_MAX )
		{
			p_convObj->iValor = (int) uiValor;
		}
		else
		{
			p_convObj->iConvValida = 0;
			p_convObj->iValor = 0;
		}
		if ( p_convObj->uiValor <= LONG_MAX )
		{
			p_convObj->lValor = (long) p_convObj->uiValor;
		}
		else
		{
			p_convObj->iConvValida = 0;
			p_convObj->lValor = 0;
		}
		p_convObj->dValor = (double) ( p_convObj->uiValor );
		p_convObj->fValor = (float) ( p_convObj->uiValor );

		InicializarCadena ( p_convObj );
		p_cAux = ConvEnteroACadena ( p_convObj->iValor );
		if ( ES_VALIDO ( p_cAux ) )
		{
			for ( iCar = 0; iCar < CadLongitudSeg ( p_cAux, CONV_MAX_TAM_CADENA ); iCar = iCar + 1 )
			{
				p_convObj->p_cValor [ iCar ] = p_cAux [ iCar ];
			}
			p_convObj->p_cValor [ iCar ] = (char) 0;
			MemLiberar ( (void **) &p_cAux );
		}
		else
		{
			p_convObj->iConvValida = 0;
		}
	}
}

void SConvEstablecerValorEnteroLargoSinSigno ( SConversor * p_convObj, unsigned long ulValor )
{
	const char *	p_cAux;
	int				iCar;

	if ( ES_VALIDO ( p_convObj ) )
	{
		p_convObj->iConvValida = 1;
		p_convObj->ulValor = ulValor;
		p_convObj->ullValor = (unsigned long long) ulValor;
		p_convObj->llValor = (long long) ulValor;
		if ( ( p_convObj->ulValor <= UINT_MAX ) )
		{
			p_convObj->uiValor = (unsigned int) ulValor;
		}
		else
		{
			p_convObj->iConvValida = 0;
			p_convObj->uiValor = 0;
		}
		if ( p_convObj->ulValor <= INT_MAX )
		{
			p_convObj->iValor = (int) p_convObj->ulValor;
		}
		else
		{
			p_convObj->iConvValida = 0;
			p_convObj->iValor = 0;
		}
		if ( p_convObj->ulValor <= LONG_MAX )
		{
			p_convObj->lValor = (long) p_convObj->ulValor;
		}
		else
		{
			p_convObj->iConvValida = 0;
			p_convObj->lValor = 0;
		}
		p_convObj->dValor = (double) ( p_convObj->ulValor );
		p_convObj->fValor = (float) ( p_convObj->ulValor );
		InicializarCadena ( p_convObj );
		p_cAux = ConvEnteroLargoACadena ( p_convObj->lValor );
		if ( ES_VALIDO ( p_cAux ) )
		{
			for ( iCar = 0; iCar < CadLongitudSeg ( p_cAux, CONV_MAX_TAM_CADENA ) ; iCar = iCar + 1 )
			{
				p_convObj->p_cValor [ iCar ] = p_cAux [ iCar ];
			}
			p_convObj->p_cValor [ iCar ] = (char) 0;
			MemLiberar ( (void **) &p_cAux );
		}
		else
		{
			p_convObj->iConvValida = 0;
		}
	}
}

void SConvEstablecerValorReal ( SConversor * p_convObj, float fValor )
{
	const char *	p_cAux;
	int				iCar;

	if ( ES_VALIDO ( p_convObj ) )
	{
		p_convObj->iConvValida = 1;
		p_convObj->fValor = fValor;
		p_convObj->dValor = (double) p_convObj->fValor;
		if ( ( p_convObj->fValor >= LLONG_MIN ) && ( p_convObj->fValor <= LLONG_MAX ) )
		{
			p_convObj->llValor = ConvRealAEnteroDobleLargo ( p_convObj->fValor, 0 );
		}
		else
		{
			p_convObj->iConvValida = 0;
			p_convObj->llValor = 0;
		}
		if ( ( p_convObj->fValor >= LONG_MIN ) && ( p_convObj->fValor <= LONG_MAX ) )
		{
			p_convObj->lValor = ConvRealAEnteroLargo ( p_convObj->fValor, 0 );
			if ( ( p_convObj->fValor >= INT_MIN ) && ( p_convObj->fValor <= INT_MAX ) )
			{
				p_convObj->iValor = (int) p_convObj->lValor;
			}
			else
			{
				p_convObj->iConvValida = 0;
				p_convObj->iValor = 0;
			}
		}
		else
		{
			p_convObj->iConvValida = 0;
			p_convObj->lValor = 0;
			p_convObj->iValor = 0;
		}
		if ( p_convObj->fValor >= 0 )
		{
			if ( ( p_convObj->fValor <= ULONG_MAX ) )
			{
				p_convObj->ulValor = ConvRealAEnteroDobleLargoSinSigno ( p_convObj->fValor, 0 );
			}
			else
			{
				p_convObj->iConvValida = 0;
				p_convObj->ullValor = 0;
			}				
			if ( ( p_convObj->fValor <= ULONG_MAX ) )
			{
				p_convObj->ulValor = ConvRealAEnteroLargoSinSigno ( p_convObj->fValor, 0 );
				if ( p_convObj->fValor <= UINT_MAX )
				{
					p_convObj->uiValor = (unsigned int) p_convObj->ulValor;
				}
				else
				{
					p_convObj->iConvValida = 0;
					p_convObj->uiValor = 0;
				}
			}
			else
			{
				p_convObj->iConvValida = 0;
				p_convObj->uiValor = 0;
				p_convObj->ulValor = 0;
			}
		}
		else
		{
			p_convObj->iConvValida = 0;
			p_convObj->uiValor = 0;
			p_convObj->ulValor = 0;
			p_convObj->ullValor = 0;
		}
		InicializarCadena ( p_convObj );
		p_cAux = ConvRealACadena ( p_convObj->fValor );
		if ( ES_VALIDO ( p_cAux ) )
		{
			for ( iCar = 0; iCar < CadLongitudSeg ( p_cAux, CONV_MAX_TAM_CADENA ); iCar = iCar + 1 )
			{
				p_convObj->p_cValor [ iCar ] = p_cAux [ iCar ];
			}
			p_convObj->p_cValor [ iCar ] = (char) 0;
			MemLiberar ( (void **) &p_cAux );
		}
		else
		{
			p_convObj->iConvValida = 0;
		}
	}
}

void SConvEstablecerValorRealDoble ( SConversor * p_convObj, double dValor )
{
	const char *	p_cAux;
	int				iCar;

	if ( ES_VALIDO ( p_convObj ) )
	{
		p_convObj->iConvValida = 1;
		p_convObj->dValor = dValor;
		if ( ( p_convObj->dValor >= LLONG_MIN ) && ( p_convObj->dValor <= LLONG_MAX ) )
		{
			p_convObj->llValor = ConvRealDobleAEnteroDobleLargo ( p_convObj->dValor, 0 );
		}
		else
		{
			p_convObj->iConvValida = 0;
			p_convObj->llValor = 0;
		}
		if ( ( fabs ( p_convObj->dValor ) >= FLT_MIN ) && ( fabs ( p_convObj->dValor ) <= FLT_MAX ) )
		{
			p_convObj->fValor = (float) p_convObj->dValor;
		}
		else
		{
			p_convObj->iConvValida = 0;
			p_convObj->fValor = 0.0;
		}
		if ( ( p_convObj->dValor >= LONG_MIN ) && ( p_convObj->dValor <= LONG_MAX ) )
		{
			p_convObj->lValor = ConvRealDobleAEnteroLargo ( p_convObj->dValor, 0 );
			if ( ( p_convObj->dValor >= INT_MIN ) && ( p_convObj->dValor <= INT_MAX ) )
			{
				p_convObj->iValor = (int) p_convObj->lValor;
			}
			else
			{
				p_convObj->iConvValida = 0;
				p_convObj->iValor = 0;
			}
		}
		else
		{
			p_convObj->iConvValida = 0;
			p_convObj->lValor = 0;
			p_convObj->iValor = 0;
		}
		if ( p_convObj->dValor >= 0 )
		{
			if ( ( p_convObj->fValor <= ULONG_MAX ) )
			{
				p_convObj->ulValor = ConvRealDobleAEnteroDobleLargoSinSigno ( p_convObj->fValor, 0 );
			}
			else
			{
				p_convObj->iConvValida = 0;
				p_convObj->ullValor = 0;
			}				
			if ( ( p_convObj->fValor <= ULONG_MAX ) )
			{
				p_convObj->ulValor = ConvRealDobleAEnteroLargoSinSigno ( p_convObj->dValor, 0 );
				if ( p_convObj->dValor <= UINT_MAX )
				{
					p_convObj->uiValor = (unsigned int) p_convObj->ulValor;
				}
				else
				{
					p_convObj->iConvValida = 0;
					p_convObj->uiValor = 0;
				}
			}
			else
			{
				p_convObj->iConvValida = 0;
				p_convObj->uiValor = 0;
				p_convObj->ulValor = 0;
			}
		}
		InicializarCadena ( p_convObj );
		p_cAux = ConvRealDobleACadena ( p_convObj->dValor );
		if ( ES_VALIDO ( p_cAux ) )
		{
			for ( iCar = 0; iCar < CadLongitudSeg ( p_cAux, CONV_MAX_TAM_CADENA ); iCar = iCar + 1 )
			{
				p_convObj->p_cValor [ iCar ] = p_cAux [ iCar ];
			}
			p_convObj->p_cValor [ iCar ] = (char) 0;
			MemLiberar ( (void **) &p_cAux );
		}
		else
		{
			p_convObj->iConvValida = 0;
		}
	}
}

void SConvEstablecerValorCadena ( SConversor * p_convObj, char * p_cValor )
{
	SConvEstablecerValorCadenaConstante ( p_convObj, (const char *) p_cValor );
}

void SConvEstablecerValorCadenaConstante ( SConversor * p_convObj, const char * p_cValor )
{
	char *		p_cUltimoConvertido;
	int			iCar;
	int			iCarVal;
	int			iIni;

	if ( ES_VALIDO ( p_convObj ) )
	{
		p_convObj->iConvValida = 1;
		InicializarCadena ( p_convObj );

		if ( ES_VALIDO ( p_cValor ) )
		{
			iIni = 1;
			iCarVal = 0;
			for ( iCar = 0; iCar < CadLongitudSeg ( p_cValor, CONV_MAX_TAM_CADENA ); iCar = iCar + 1 )
			{
				if ( ( iIni == 1 ) && ( p_cValor [ iCar ] != '0' ) )
				{
					iIni = 0;
				}
				if ( iIni == 0 )
				{
					p_convObj->p_cValor [ iCarVal ] = p_cValor [ iCar ];
					iCarVal = iCarVal + 1;
				}
			}
			if ( iCarVal == 0 )
			{
				p_convObj->p_cValor [ 0 ] = '0';
				iCarVal = 1;
			}
			p_convObj->p_cValor [ iCarVal ] = (char) 0;
		}

		if ( SConvEsCadenaNumerica ( p_convObj ) == 1 )
		{
			p_cUltimoConvertido = NULL;
			p_convObj->dValor = strtod ( p_convObj->p_cValor, &p_cUltimoConvertido );
			if ( ( fabs ( p_convObj->dValor ) >= FLT_MIN ) && ( fabs ( p_convObj->dValor ) <= FLT_MAX ) )
			{
				p_convObj->fValor = (float) p_convObj->dValor;
			}
			else
			{
				p_convObj->iConvValida = 0;
				p_convObj->fValor = 0.0;
			}
			if ( ( p_convObj->dValor >= LLONG_MIN ) && ( p_convObj->dValor <= LLONG_MAX ) )
			{
				p_convObj->llValor = (long long) p_convObj->dValor;
			}
			else
			{
				p_convObj->iConvValida = 0;
				p_convObj->llValor = 0;
			}
			if ( ( p_convObj->dValor >= LONG_MIN ) && ( p_convObj->dValor <= LONG_MAX ) )
			{
				p_convObj->lValor = (long) p_convObj->dValor;
				if ( ( p_convObj->dValor >= INT_MIN ) && ( p_convObj->dValor <= INT_MAX ) )
				{
					p_convObj->iValor = (int) p_convObj->dValor;
				}
				else
				{
					p_convObj->iConvValida = 0;
					p_convObj->iValor = 0;
				}
			}
			else
			{
				p_convObj->iConvValida = 0;
				p_convObj->lValor = 0;
				p_convObj->iValor = 0;
			}
			if ( p_convObj->dValor >= 0 )
			{
				if ( p_convObj->fValor <= ULONG_MAX )
				{
					p_convObj->ulValor = ConvRealDobleAEnteroDobleLargoSinSigno ( p_convObj->fValor, 0 );
				}
				else
				{
					p_convObj->iConvValida = 0;
					p_convObj->ullValor = 0;
				}				
				if ( p_convObj->fValor <= ULONG_MAX )
				{
					p_convObj->ulValor = ConvRealDobleAEnteroLargoSinSigno ( p_convObj->dValor, 0 );
					if ( p_convObj->dValor <= UINT_MAX )
					{
						p_convObj->uiValor = (unsigned int) p_convObj->ulValor;
					}
					else
					{
						p_convObj->iConvValida = 0;
						p_convObj->uiValor = 0;
					}
				}
				else
				{
					p_convObj->iConvValida = 0;
					p_convObj->uiValor = 0;
					p_convObj->ulValor = 0;
				}
				// p_cUltimoConvertido 
				if ( *p_cUltimoConvertido != '\0' )
				{
					p_convObj->iConvValida = 0;
				}
			}
		}
		else if ( SConvEsCadenaNumericaHexadecimal ( p_convObj ) == 1 )
		{
			p_convObj->ullValor = ConvCadenaHexAEnteroDobleLargoSinSigno ( p_cValor );
			if ( ( p_convObj->ullValor <= LLONG_MAX ) )
			{
				p_convObj->llValor = (long long) p_convObj->ullValor;
			}
			else
			{
				p_convObj->iConvValida = 0;
				p_convObj->llValor = 0;
				p_convObj->ullValor = 0;
			}
			p_convObj->ulValor = ConvCadenaHexAEnteroLargoSinSigno ( p_cValor );
			if ( ( p_convObj->ulValor <= UINT_MAX ) )
			{
				p_convObj->uiValor = (unsigned int) p_convObj->ulValor;
			}
			else
			{
				p_convObj->iConvValida = 0;
				p_convObj->uiValor = 0;
			}
			if ( p_convObj->ulValor <= INT_MAX )
			{
				p_convObj->iValor = (int) p_convObj->ulValor;
			}
			else
			{
				p_convObj->iConvValida = 0;
				p_convObj->iValor = 0;
			}
			if ( p_convObj->ulValor <= LONG_MAX )
			{
				p_convObj->lValor = (long) p_convObj->ulValor;
			}
			else
			{
				p_convObj->iConvValida = 0;
				p_convObj->lValor = 0;
			}
			p_convObj->dValor = (double) ( p_convObj->ulValor );
			p_convObj->fValor = (float) ( p_convObj->ulValor );
		}
		else
		{
			p_convObj->llValor = 0;
			p_convObj->ullValor = 0;
			p_convObj->dValor = 0.0;
			p_convObj->fValor = 0.0;
			p_convObj->lValor = 0;
			p_convObj->iValor = 0;
			p_convObj->ulValor = 0;
			p_convObj->uiValor = 0;
			p_convObj->iConvValida = 0;
		}
	}
}

void SConvEstablecerValorCadenaHex ( SConversor * p_convObj, char * p_cValor )
{
	SConvEstablecerValorCadenaHexConstante ( p_convObj, (const char *) p_cValor );
}

void SConvEstablecerValorCadenaHexConstante ( SConversor * p_convObj, const char * p_cValor )
{
	int		iCar;
	int		iCarVal;
	int		iIni;

	if ( ES_VALIDO ( p_convObj ) )
	{
		p_convObj->iConvValida = 1;
		InicializarCadena ( p_convObj );

		if ( ES_VALIDO ( p_cValor ) )
		{
			iIni = 1;
			iCarVal = 0;
			for ( iCar = 0; iCar < CadLongitudSeg ( p_cValor, CONV_MAX_TAM_CADENA ); iCar = iCar + 1 )
			{
				if ( ( iIni == 1 ) && ( p_cValor [ iCar ] != '0' ) )
				{
					iIni = 0;
				}
				if ( iIni == 0 )
				{
					p_convObj->p_cValor [ iCarVal ] = p_cValor [ iCar ];
					iCarVal = iCarVal + 1;
				}
			}
			if ( iCarVal == 0 )
			{
				p_convObj->p_cValor [ 0 ] = '0';
				iCarVal = 1;
			}
			p_convObj->p_cValor [ iCarVal ] = (char) 0;
		}

		if ( SConvEsCadenaNumericaHexadecimal ( p_convObj ) == 1 )
		{
			p_convObj->ulValor = ConvCadenaHexAEnteroLargoSinSigno ( p_cValor );
			if ( ( p_convObj->ulValor <= UINT_MAX ) )
			{
				p_convObj->uiValor = (unsigned int) p_convObj->ulValor;
			}
			else
			{
				p_convObj->iConvValida = 0;
				p_convObj->uiValor = 0;
			}
			if ( p_convObj->ulValor <= INT_MAX )
			{
				p_convObj->iValor = (int) p_convObj->ulValor;
			}
			else
			{
				p_convObj->iConvValida = 0;
				p_convObj->iValor = 0;
			}
			if ( p_convObj->ulValor <= LONG_MAX )
			{
				p_convObj->lValor = (long) p_convObj->ulValor;
			}
			else
			{
				p_convObj->iConvValida = 0;
				p_convObj->lValor = 0;
			}
			p_convObj->dValor = (double) ( p_convObj->ulValor );
			p_convObj->fValor = (float) ( p_convObj->ulValor );
		}
		else
		{
			p_convObj->llValor = 0;
			p_convObj->ullValor = 0;
			p_convObj->dValor = 0.0;
			p_convObj->fValor = 0.0;
			p_convObj->lValor = 0;
			p_convObj->iValor = 0;
			p_convObj->ulValor = 0;
			p_convObj->uiValor = 0;
			p_convObj->iConvValida = 0;
		}
	}
}

void SConvEstablecerValorEnteroDobleLargo ( SConversor * p_convObj, long long llValor )
{
	const char *	p_cAux;
	int				iCar;

	if ( ES_VALIDO ( p_convObj ) )
	{
		p_convObj->iConvValida = 1;
		p_convObj->llValor = llValor;
		if ( ( p_convObj->llValor >= LONG_MIN ) && ( p_convObj->llValor <= LONG_MAX ) )
		{
			p_convObj->lValor = (long) p_convObj->llValor;
		}
		else
		{
			p_convObj->iConvValida = 0;
			p_convObj->lValor = 0;
		}
		if ( ( p_convObj->llValor >= INT_MIN ) && ( p_convObj->llValor <= INT_MAX ) )
		{
			p_convObj->iValor = (int) p_convObj->llValor;
		}
		else
		{
			p_convObj->iConvValida = 0;
			p_convObj->iValor = 0;
		}
		if ( ( p_convObj->llValor >= 0 ) && ( (unsigned long long) p_convObj->llValor <= (unsigned long long) UINT_MAX ) )
		{
			p_convObj->uiValor = (unsigned int) p_convObj->llValor;
		}
		else
		{
			p_convObj->iConvValida = 0;
			p_convObj->uiValor = 0;
		}
		if ( p_convObj->llValor >= 0 )
		{
			p_convObj->ulValor = (unsigned long) p_convObj->llValor;
		}
		else
		{
			p_convObj->iConvValida = 0;
			p_convObj->ulValor = 0;
		}
		p_convObj->dValor = (double) ( p_convObj->llValor );
		p_convObj->fValor = (float) ( p_convObj->llValor );

		InicializarCadena ( p_convObj );
		p_cAux = ConvEnteroDobleLargoACadena ( p_convObj->llValor );
		if ( ES_VALIDO ( p_cAux ) )
		{
			for ( iCar = 0; iCar < CadLongitudSeg ( p_cAux, CONV_MAX_TAM_CADENA ); iCar = iCar + 1 )
			{
				p_convObj->p_cValor [ iCar ] = p_cAux [ iCar ];
			}
			p_convObj->p_cValor [ iCar ] = (char) 0;
			MemLiberar ( (void **) &p_cAux );
		}
		else
		{
			p_convObj->iConvValida = 0;
		}
	}
}

void SConvEstablecerValorEnteroDobleLargoSinSigno ( SConversor * p_convObj, unsigned long long ullValor )
{
	const char *	p_cAux;
	int				iCar;

	if ( ES_VALIDO ( p_convObj ) )
	{
		p_convObj->iConvValida = 1;
		p_convObj->ullValor = ullValor;
		if ( p_convObj->ullValor <= LLONG_MAX )
		{
			p_convObj->llValor = (long long) p_convObj->ullValor;
		}
		else
		{
			p_convObj->iConvValida = 0;
			p_convObj->llValor = 0;
		}
		if ( ( p_convObj->llValor >= LONG_MIN ) && ( p_convObj->llValor <= LONG_MAX ) )
		{
			p_convObj->lValor = (long) p_convObj->llValor;
		}
		else
		{
			p_convObj->iConvValida = 0;
			p_convObj->lValor = 0;
		}
		if ( ( p_convObj->llValor >= INT_MIN ) && ( p_convObj->llValor <= INT_MAX ) )
		{
			p_convObj->iValor = (int) p_convObj->llValor;
		}
		else
		{
			p_convObj->iConvValida = 0;
			p_convObj->iValor = 0;
		}
		if ( ( p_convObj->llValor >= 0 ) && ( (unsigned long long) p_convObj->llValor <= (unsigned long long) UINT_MAX ) )
		{
			p_convObj->uiValor = (unsigned int) p_convObj->llValor;
		}
		else
		{
			p_convObj->iConvValida = 0;
			p_convObj->uiValor = 0;
		}
		if ( p_convObj->llValor >= 0 )
		{
			p_convObj->ulValor = (unsigned long) p_convObj->llValor;
		}
		else
		{
			p_convObj->iConvValida = 0;
			p_convObj->ulValor = 0;
		}
		p_convObj->dValor = (double) ( p_convObj->llValor );
		p_convObj->fValor = (float) ( p_convObj->llValor );

		InicializarCadena ( p_convObj );
		p_cAux = ConvEnteroDobleLargoSinSignoACadena ( p_convObj->ullValor );
		if ( ES_VALIDO ( p_cAux ) )
		{
			for ( iCar = 0; iCar < CadLongitudSeg ( p_cAux, CONV_MAX_TAM_CADENA ); iCar = iCar + 1 )
			{
				p_convObj->p_cValor [ iCar ] = p_cAux [ iCar ];
			}
			p_convObj->p_cValor [ iCar ] = (char) 0;
			MemLiberar ( (void **) &p_cAux );
		}
		else
		{
			p_convObj->iConvValida = 0;
		}
	}
}


int SConvEsCadenaNumerica ( SConversor * p_convObj )
{
	int iRes;
	int iCar;
	int iPunto;

	if ( ES_VALIDO ( p_convObj ) )
	{
		if ( ES_VALIDO ( p_convObj->p_cValor ) )
		{
			iCar = 0;
			iPunto = 0;
			iRes = 1;
			while ( ( iCar < CadLongitudSeg ( p_convObj->p_cValor, CONV_MAX_TAM_CADENA ) ) && ( iRes == 1 ) )
			{
				if ( (p_convObj->p_cValor [ iCar ] < '0' ) || (p_convObj->p_cValor [ iCar ] > '9' ) )
				{
					if  ( p_convObj->p_cValor [ iCar ] == '-' )
					{
						if  ( iCar > 0 )
						{
							iRes = 0;
						}
					}
					else if  ( ( p_convObj->p_cValor [ iCar ] == '.' ) || ( p_convObj->p_cValor [ iCar ] == ',' ) )
					{
						if  ( iPunto > 0 )
						{
							iRes = 0;
						}
						else
						{
							iPunto = 1;
						}
					}
					else
					{
						iRes = 0;
					}
				}
				iCar = iCar + 1;
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

int SConvEsCadenaNumericaEntera ( SConversor * p_convObj )
{
	int iRes;
	int iCar;

	if ( ES_VALIDO ( p_convObj ) )
	{
		if ( ES_VALIDO ( p_convObj->p_cValor ) )
		{
			iCar = 0;
			iRes = 1;
			while ( ( iCar < CadLongitudSeg ( p_convObj->p_cValor, CONV_MAX_TAM_CADENA ) ) && ( iRes == 1 ) )
			{
				if ( ( p_convObj->p_cValor [ iCar ] < '0' ) || ( p_convObj->p_cValor [ iCar ] > '9' )  )
				{
					if  ( p_convObj->p_cValor [ iCar ] == '-' )
					{
						if  ( iCar > 0 )
						{
							iRes = 0;
						}
					}
					else
					{
						iRes = 0;
					}
				}
				iCar = iCar + 1;
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

int SConvEsCadenaNumericaReal ( SConversor * p_convObj )
{
	return ( SConvEsCadenaNumerica ( p_convObj ) );
}

int SConvEsCadenaNumericaHexadecimal ( SConversor * p_convObj )
{
	int iRes;
	int iCar;
	int iLong;

	if ( ES_VALIDO ( p_convObj ) )
	{
		if ( ES_VALIDO ( p_convObj->p_cValor ) )
		{
			iLong =  CadLongitudSeg ( p_convObj->p_cValor, CONV_MAX_TAM_CADENA );
			if ( (iLong > 0 ) && ( p_convObj->p_cValor [ 0 ] == '&' ) )
			{
				iCar = 1;
			}
			else
			{
				iCar = 0;
			}
			iRes = 1;
			while ( ( iCar < iLong ) && ( iRes == 1 ) )
			{
				if ( ( ( p_convObj->p_cValor [ iCar ] < '0' ) || ( p_convObj->p_cValor [ iCar ] > '9' ) ) &&
					 ( p_convObj->p_cValor [ iCar ] != 'a' ) &&
					 ( p_convObj->p_cValor [ iCar ] != 'b' ) &&
					 ( p_convObj->p_cValor [ iCar ] != 'c' ) &&
					 ( p_convObj->p_cValor [ iCar ] != 'd' ) &&
					 ( p_convObj->p_cValor [ iCar ] != 'e' ) &&
					 ( p_convObj->p_cValor [ iCar ] != 'f' ) &&
					 ( p_convObj->p_cValor [ iCar ] != 'A' ) &&
					 ( p_convObj->p_cValor [ iCar ] != 'B' ) &&
					 ( p_convObj->p_cValor [ iCar ] != 'C' ) &&
					 ( p_convObj->p_cValor [ iCar ] != 'D' ) &&
					 ( p_convObj->p_cValor [ iCar ] != 'E' ) &&
					 ( p_convObj->p_cValor [ iCar ] != 'F' ) )
				{
					iRes = 0;
				}
				iCar = iCar + 1;
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

int SConvConversionValida ( SConversor * p_convObj )
{
	if ( ES_VALIDO ( p_convObj ) )
	{
		return ( p_convObj->iConvValida );
	}
	else
	{
		return ( 0 );
	}
}

void Inicializar ( SConversor * p_convObj )
{
	if ( ES_VALIDO ( p_convObj ) )
	{
		p_convObj->iConvValida = 0;
		p_convObj->iValor = 0;
		p_convObj->lValor = 0;
		p_convObj->uiValor = 0;
		p_convObj->ulValor = 0;
		p_convObj->fValor = 0.0;
		p_convObj->dValor = 0.0;
		p_convObj->p_cValor = NULL;
	}
}

void InicializarCadena ( SConversor * p_convObj )
{
	int iCar;

	if ( ES_VALIDO ( p_convObj ) )
	{
		if ( ES_NULO ( p_convObj->p_cValor ) )
		{
			p_convObj->p_cValor = CadCrear ( CONV_MAX_TAM_CADENA );
		}
		else if ( ES_VALIDO ( p_convObj->p_cValor ) )
		{
			for ( iCar = 0; iCar < CONV_MAX_TAM_CADENA; iCar = iCar + 1 )
			{
				p_convObj->p_cValor [ iCar ] = (char) 0;
			}
		}
	}
}


