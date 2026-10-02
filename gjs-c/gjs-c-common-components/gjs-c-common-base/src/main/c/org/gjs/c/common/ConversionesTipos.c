/******************************************************************************/
/*                           ConversionesTipos.cpp                            */
/*----------------------------------------------------------------------------*/
/* Librería:  GBase                                                           */
/* Versión:   1.0.0                                                           */
/* Fecha:     28/06/2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Fichero de código fuente que contiene la implementación de las rutinas     */
/* generales de conversión entre tipos de datos básicos.                      */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#include "ConversionesTipos.h"

#include "BaseConfig.h"
#include "Memoria.h"
#include "CadenasBase.h"
#include "Numeros.h"
#include "Errores.h"

#include <errno.h>		/* ERANGE, para detectar el desbordamiento */



char ConvDigitoACaracter ( int iDigito )
{
	char cRes;

	if ( ( iDigito >= 0 ) && ( iDigito <= 9 ) )
	{
		cRes = (char) (((unsigned char ) '0') + ((unsigned char) iDigito));
	}
	else
	{
		cRes = ' ';
	}
	return ( cRes );
}

int ConvCaracterADigito ( char cDigito )
{
	int iRes;

	if ( ( cDigito >= '0' ) && ( cDigito <= '9' ) )
	{
		iRes = (int) (((unsigned char) cDigito) - ((unsigned char ) '0'));
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int ConvRealAEntero ( float fVal, int iTruncar )
{
	return ( (int) ConvRealAEnteroLargo ( fVal, iTruncar ) );
}

long long ConvRealAEnteroDobleLargo ( float fVal, int iTruncar )
{
	long long	llRes;
	float	fEntero;

	fEntero = NumParteEnteraReal ( fVal );
	if ( iTruncar == 0 )
	{
		if ( fVal >= 0.0 )
		{
			if ( fVal - fEntero >= 0.5 )
			{
				fEntero = (float) ceil ( fVal );
			}
		}
		else
		{
			if ( fVal - fEntero <= -0.5 )
			{
				fEntero = (float) floor ( fVal );
			}
		}
	}
	if ( fEntero > LLONG_MAX )
	{
		llRes = LLONG_MAX;
	}
	else if ( fEntero < LLONG_MIN )
	{
		llRes = LLONG_MIN;
	}
	else
	{
		llRes = (long long) fEntero;
	}
	return ( llRes );
}

unsigned long long ConvRealAEnteroDobleLargoSinSigno ( float fVal, int iTruncar )
{
	unsigned long long	ullRes;
	float	fEntero;

	fEntero = NumParteEnteraReal ( fVal );
	if ( iTruncar == 0 )
	{
		if ( fVal >= 0.0 )
		{
			if ( fVal - fEntero >= 0.5 )
			{
				fEntero = (float) ceil ( fVal );
			}
		}
		else
		{
			if ( fVal - fEntero <= -0.5 )
			{
				fEntero = (float) floor ( fVal );
			}
		}
	}
	if ( fEntero > ULLONG_MAX )
	{
		ullRes = ULLONG_MAX;
	}
	else if ( fEntero > 0 )
	{
		ullRes = (unsigned long long) fEntero;
	}
	else
	{
		ullRes = 0;
	}
	return ( ullRes );
}

long ConvRealAEnteroLargo ( float fVal, int iTruncar )
{
	long	lRes;
	float	fEntero;

	fEntero = NumParteEnteraReal ( fVal );
	if ( iTruncar == 0 )
	{
		if ( fVal >= 0.0 )
		{
			if ( fVal - fEntero >= 0.5 )
			{
				fEntero = (float) ceil ( fVal );
			}
		}
		else
		{
			if ( fVal - fEntero <= -0.5 )
			{
				fEntero = (float) floor ( fVal );
			}
		}
	}
	if ( fEntero > LONG_MAX )
	{
		lRes = LONG_MAX;
	}
	else if ( fEntero < LONG_MIN )
	{
		lRes = LONG_MIN;
	}
	else
	{
		lRes = (long) fEntero;
	}
	return ( lRes );
}

int ConvRealDobleAEntero ( double dVal, int iTruncar )
{
	return ( (int) ConvRealDobleAEnteroLargo ( dVal, iTruncar ) );
}

long long ConvRealDobleAEnteroDobleLargo ( double dVal, int iTruncar )
{
	long long	llRes;
	double	dEntero;

	dEntero = NumParteEnteraRealDoble ( dVal );
	if ( iTruncar == 0 )
	{
		if ( dVal >= 0.0 )
		{
			if ( dVal - dEntero >= 0.5 )
			{
				dEntero = ceil ( dVal );
			}
		}
		else
		{
			if ( dVal - dEntero <= -0.5 )
			{
				dEntero = floor ( dVal );
			}
		}
	}
	if ( dEntero > LLONG_MAX )
	{
		llRes = LLONG_MAX;
	}
	else if ( dEntero < LLONG_MIN )
	{
		llRes = LLONG_MIN;
	}
	else
	{
		llRes = (long long) dEntero;
	}
	return ( llRes );
}

unsigned long long ConvRealDobleAEnteroDobleLargoSinSigno ( double dVal, int iTruncar )
{
	unsigned long long	ullRes;
	double	dEntero;

	dEntero = NumParteEnteraRealDoble ( dVal );
	if ( iTruncar == 0 )
	{
		if ( dVal >= 0.0 )
		{
			if ( dVal - dEntero >= 0.5 )
			{
				dEntero = ceil ( dVal );
			}
		}
		else
		{
			if ( dVal - dEntero <= -0.5 )
			{
				dEntero = floor ( dVal );
			}
		}
	}
	if ( dEntero > ULLONG_MAX )
	{
		ullRes = ULLONG_MAX;
	}
	else if ( dEntero > 0 )
	{
		ullRes = (unsigned long long) dEntero;
	}
	else
	{
		ullRes = 0;
	}
	return ( ullRes );
}

long ConvRealDobleAEnteroLargo ( double dVal, int iTruncar )
{
	long	lRes;
	double	dEntero;

	dEntero = NumParteEnteraRealDoble ( dVal );
	if ( iTruncar == 0 )
	{
		if ( dVal >= 0.0 )
		{
			if ( dVal - dEntero >= 0.5 )
			{
				dEntero = ceil ( dVal );
			}
		}
		else
		{
			if ( dVal - dEntero <= -0.5 )
			{
				dEntero = floor ( dVal );
			}
		}
	}
	if ( dEntero > LONG_MAX )
	{
		lRes = LONG_MAX;
	}
	else if ( dEntero < LONG_MIN )
	{
		lRes = LONG_MIN;
	}
	else
	{
		lRes = (long) dEntero;
	}
	return ( lRes );
}

unsigned int ConvRealAEnteroSinSigno ( float fVal, int iTruncar )
{
	return ( (unsigned int) ConvRealAEnteroLargoSinSigno ( fVal, iTruncar ) );
}

unsigned long ConvRealAEnteroLargoSinSigno ( float fVal, int iTruncar )
{
	return ( ConvRealDobleAEnteroLargoSinSigno ( (double) fVal, iTruncar ) );
}

unsigned int ConvRealDobleAEnteroSinSigno ( double dVal, int iTruncar )
{
	return ( (unsigned int) ConvRealDobleAEnteroLargoSinSigno ( dVal, iTruncar ) );
}

unsigned long ConvRealDobleAEnteroLargoSinSigno ( double dVal, int iTruncar )
{
	unsigned long	ulRes;
	double			dEntero;

	dEntero = NumParteEnteraRealDoble ( dVal );
	if ( iTruncar == 0 )
	{
		if ( dVal >= 0.0 )
		{
			if ( dVal - dEntero >= 0.5 )
			{
				dEntero = ceil ( dVal );
			}
		}
		else
		{
			if ( dVal - dEntero <= -0.5 )
			{
				dEntero = floor ( dVal );
			}
		}
	}
	if ( dEntero > ULONG_MAX )
	{
		ulRes = ULONG_MAX;
	}
	else
	{
		ulRes = (unsigned long) dEntero;
	}
	return ( ulRes );
}

/* --- Conversiones de cadena a numero ----------------------------------------
   Todas tienen el mismo contrato: devuelven 0 si la cadena no es un numero del
   tipo pedido, y eso incluye el desbordamiento.

   Se usa la familia strtol y no sscanf, y el motivo no es de estilo: ante un
   desbordamiento, sscanf con "%d" es COMPORTAMIENTO INDEFINIDO segun el
   estandar, no un error que se pueda detectar. strtol lo senala con
   errno == ERANGE, y de paso deja en el puntero de fin donde acabo el numero,
   con lo que tambien se caza la basura del final: "12abc", que sscanf aceptaba
   devolviendo 12, aqui se rechaza.

   Antes habia una comprobacion de longitud contra MaxDigitos*, y no bastaba:
   "9999999999" tiene diez digitos, los mismos que INT_MAX, y no cabe en un
   int. Ya no hace falta. */

#define CONV_BASE_DECIMAL		10
#define CONV_BASE_HEX			16

/* El '&' inicial es la notacion hexadecimal de Basic: "&FF" es lo mismo que
   "FF". Se admite solo en la primera posicion, como hasta ahora. Devuelve
   donde empieza el numero de verdad. */
static const char * _ConvSaltarPrefijoHex ( const char * p_cVal )
{
	const char *	p_cRes;

	if ( p_cVal [ 0 ] == '&' )
	{
		p_cRes = p_cVal + 1;
	}
	else
	{
		p_cRes = p_cVal;
	}
	return ( p_cRes );
}

/* Las conversiones sin signo tienen que rechazar el menos A MANO: strtoul y
   strtoull lo ACEPTAN y devuelven el complemento, sin senalar error ninguno.
   Comprobado el 2026-09-19: strtoul ( "-1" ) devuelve 18446744073709551615 y
   deja errno a cero. Hay que saltarse los blancos igual que hace strtoul para
   llegar al signo. */
static int _ConvNoEmpiezaPorMenos ( const char * p_cVal )
{
	int				iRes;
	const char *	p_cPrimero;

	p_cPrimero = p_cVal;
	while ( ( *p_cPrimero == ' ' ) || ( *p_cPrimero == ASCII_TAB ) )
	{
		p_cPrimero = p_cPrimero + 1;
	}
	if ( *p_cPrimero == '-' )
	{
		iRes = 0;
	}
	else
	{
		iRes = 1;
	}
	return ( iRes );
}

unsigned int ConvCadenaAEnteroSinSigno ( const char * p_cVal )
{
	unsigned int 	uiRes;
	unsigned long	ulVal;
	char *			p_cFin;

	uiRes = 0;
	if ( ES_VALIDO ( p_cVal ) )
	{
		if ( _ConvNoEmpiezaPorMenos ( p_cVal ) == 1 )
		{
			errno = 0;
			ulVal = strtoul ( p_cVal, &p_cFin, CONV_BASE_DECIMAL );
			if ( p_cFin != p_cVal )
			{
				if ( *p_cFin == ASCII_NUL )
				{
					if ( errno != ERANGE )
					{
						if ( ulVal <= ( unsigned long ) UINT_MAX )
						{
							uiRes = ( unsigned int ) ulVal;
						}
						else
						{
							ERROR_ESTABLECER ( ERR_CONVERSION_IMPOSIBLE );
						}
					}
					else
					{
						ERROR_ESTABLECER ( ERR_CONVERSION_IMPOSIBLE );
					}
				}
				else
				{
					ERROR_ESTABLECER ( ERR_CONVERSION_IMPOSIBLE );
				}
			}
			else
			{
				ERROR_ESTABLECER ( ERR_CONVERSION_IMPOSIBLE );
			}
		}
		else
		{
			ERROR_ESTABLECER ( ERR_CONVERSION_IMPOSIBLE );
		}
	}
	else
	{
		ERROR_ESTABLECER ( ERR_PARAMETROS );
	}
	return ( uiRes );
}

unsigned long ConvCadenaAEnteroLargoSinSigno ( const char * p_cVal )
{
	unsigned long 	ulRes;
	unsigned long	ulVal;
	char *			p_cFin;

	ulRes = 0;
	if ( ES_VALIDO ( p_cVal ) )
	{
		if ( _ConvNoEmpiezaPorMenos ( p_cVal ) == 1 )
		{
			errno = 0;
			ulVal = strtoul ( p_cVal, &p_cFin, CONV_BASE_DECIMAL );
			if ( p_cFin != p_cVal )
			{
				if ( *p_cFin == ASCII_NUL )
				{
					if ( errno != ERANGE )
					{
						ulRes = ulVal;
					}
					else
					{
						ERROR_ESTABLECER ( ERR_CONVERSION_IMPOSIBLE );
					}
				}
				else
				{
					ERROR_ESTABLECER ( ERR_CONVERSION_IMPOSIBLE );
				}
			}
			else
			{
				ERROR_ESTABLECER ( ERR_CONVERSION_IMPOSIBLE );
			}
		}
		else
		{
			ERROR_ESTABLECER ( ERR_CONVERSION_IMPOSIBLE );
		}
	}
	else
	{
		ERROR_ESTABLECER ( ERR_PARAMETROS );
	}
	return ( ulRes );
}

int	ConvCadenaAEntero ( const char * p_cVal )
{
	int		iRes;
	long	lVal;
	char *	p_cFin;

	iRes = 0;
	if ( ES_VALIDO ( p_cVal ) )
	{
		errno = 0;
		lVal = strtol ( p_cVal, &p_cFin, CONV_BASE_DECIMAL );
		if ( p_cFin != p_cVal )
		{
			if ( *p_cFin == ASCII_NUL )
			{
				if ( errno != ERANGE )
				{
					/* strtol devuelve long, que en 64 bits es mas ancho que
					   int: el rango hay que comprobarlo aparte. */
					if ( ( lVal >= ( long ) INT_MIN ) && ( lVal <= ( long ) INT_MAX ) )
					{
						iRes = ( int ) lVal;
					}
					else
					{
						ERROR_ESTABLECER ( ERR_CONVERSION_IMPOSIBLE );
					}
				}
				else
				{
					ERROR_ESTABLECER ( ERR_CONVERSION_IMPOSIBLE );
				}
			}
			else
			{
				ERROR_ESTABLECER ( ERR_CONVERSION_IMPOSIBLE );
			}
		}
		else
		{
			ERROR_ESTABLECER ( ERR_CONVERSION_IMPOSIBLE );
		}
	}
	else
	{
		ERROR_ESTABLECER ( ERR_PARAMETROS );
	}
	return ( iRes );
}

long ConvCadenaAEnteroLargo ( const char * p_cVal )
{
	long 	lRes;
	long	lVal;
	char *	p_cFin;

	lRes = 0;
	if ( ES_VALIDO ( p_cVal ) )
	{
		errno = 0;
		lVal = strtol ( p_cVal, &p_cFin, CONV_BASE_DECIMAL );
		if ( p_cFin != p_cVal )
		{
			if ( *p_cFin == ASCII_NUL )
			{
				if ( errno != ERANGE )
				{
					lRes = lVal;
				}
				else
				{
					ERROR_ESTABLECER ( ERR_CONVERSION_IMPOSIBLE );
				}
			}
			else
			{
				ERROR_ESTABLECER ( ERR_CONVERSION_IMPOSIBLE );
			}
		}
		else
		{
			ERROR_ESTABLECER ( ERR_CONVERSION_IMPOSIBLE );
		}
	}
	else
	{
		ERROR_ESTABLECER ( ERR_PARAMETROS );
	}
	return ( lRes );
}

long long ConvCadenaAEnteroDobleLargo ( const char * p_cVal )
{
	long long	llRes;
	long long	llVal;
	char *	p_cFin;

	llRes = 0;
	if ( ES_VALIDO ( p_cVal ) )
	{
		errno = 0;
		llVal = strtoll ( p_cVal, &p_cFin, CONV_BASE_DECIMAL );
		if ( p_cFin != p_cVal )
		{
			if ( *p_cFin == ASCII_NUL )
			{
				if ( errno != ERANGE )
				{
					llRes = llVal;
				}
				else
				{
					ERROR_ESTABLECER ( ERR_CONVERSION_IMPOSIBLE );
				}
			}
			else
			{
				ERROR_ESTABLECER ( ERR_CONVERSION_IMPOSIBLE );
			}
		}
		else
		{
			ERROR_ESTABLECER ( ERR_CONVERSION_IMPOSIBLE );
		}
	}
	else
	{
		ERROR_ESTABLECER ( ERR_PARAMETROS );
	}
	return ( llRes );
}

unsigned long long ConvCadenaAEnteroDobleLargoSinSigno ( const char * p_cVal )
{
	unsigned long long	ullRes;
	unsigned long long	ullVal;
	char *	p_cFin;

	ullRes = 0;
	if ( ES_VALIDO ( p_cVal ) )
	{
		if ( _ConvNoEmpiezaPorMenos ( p_cVal ) == 1 )
		{
			errno = 0;
			ullVal = strtoull ( p_cVal, &p_cFin, CONV_BASE_DECIMAL );
			if ( p_cFin != p_cVal )
			{
				if ( *p_cFin == ASCII_NUL )
				{
					if ( errno != ERANGE )
					{
						ullRes = ullVal;
					}
					else
					{
						ERROR_ESTABLECER ( ERR_CONVERSION_IMPOSIBLE );
					}
				}
				else
				{
					ERROR_ESTABLECER ( ERR_CONVERSION_IMPOSIBLE );
				}
			}
			else
			{
				ERROR_ESTABLECER ( ERR_CONVERSION_IMPOSIBLE );
			}
		}
		else
		{
			ERROR_ESTABLECER ( ERR_CONVERSION_IMPOSIBLE );
		}
	}
	else
	{
		ERROR_ESTABLECER ( ERR_PARAMETROS );
	}
	return ( ullRes );
}

float ConvCadenaAReal ( const char * p_cVal )
{
	float	fRes;
	float	fVal;
	char *	p_cFin;

	fRes = 0.0f;
	if ( ES_VALIDO ( p_cVal ) )
	{
		errno = 0;
		fVal = strtof ( p_cVal, &p_cFin );
		if ( p_cFin != p_cVal )
		{
			if ( *p_cFin == ASCII_NUL )
			{
				/* ERANGE aqui cubre las dos puntas: desbordamiento por arriba
				   ( devolveria HUGE_VALF ) y por abajo. En los dos casos el
				   numero no es representable y se contesta 0, como el resto de
				   la familia. */
				if ( errno != ERANGE )
				{
					fRes = fVal;
				}
				else
				{
					ERROR_ESTABLECER ( ERR_CONVERSION_IMPOSIBLE );
				}
			}
			else
			{
				ERROR_ESTABLECER ( ERR_CONVERSION_IMPOSIBLE );
			}
		}
		else
		{
			ERROR_ESTABLECER ( ERR_CONVERSION_IMPOSIBLE );
		}
	}
	else
	{
		ERROR_ESTABLECER ( ERR_PARAMETROS );
	}
	return ( fRes );
}

double ConvCadenaARealDoble ( const char * p_cVal )
{
	double	dRes;
	double	dVal;
	char *	p_cFin;

	dRes = 0.0;
	if ( ES_VALIDO ( p_cVal ) )
	{
		errno = 0;
		dVal = strtod ( p_cVal, &p_cFin );
		if ( p_cFin != p_cVal )
		{
			if ( *p_cFin == ASCII_NUL )
			{
				if ( errno != ERANGE )
				{
					dRes = dVal;
				}
				else
				{
					ERROR_ESTABLECER ( ERR_CONVERSION_IMPOSIBLE );
				}
			}
			else
			{
				ERROR_ESTABLECER ( ERR_CONVERSION_IMPOSIBLE );
			}
		}
		else
		{
			ERROR_ESTABLECER ( ERR_CONVERSION_IMPOSIBLE );
		}
	}
	else
	{
		ERROR_ESTABLECER ( ERR_PARAMETROS );
	}
	return ( dRes );
}

char * ConvEnteroACadena ( int iVal )
{
	return ( ConvEnteroLargoACadena ( (long) iVal ) );
}

char * ConvEnteroLargoACadena ( long lVal )
{
	int			iDig;
	int			iPosMin;
	int			iPos;
	int			iOrden;
	int			iTam;
	char *		p_cRes;
	int			iDec;		

	iOrden = NumDigitosEnteroLargo ( lVal );
	if ( lVal < 0 )
	{
		iTam = iOrden + 2;
	}
	else
	{
		iTam = iOrden + 1;
	}
	iDec = 0;
	p_cRes = CadCrear ( iTam - 1 );
	if ( ES_VALIDO ( p_cRes ) )
	{
		if ( lVal < 0 )
		{
			p_cRes [ 0 ] = '-';
			if ( lVal == LONG_MIN )
			{
				lVal = LONG_MAX;
				iDec = 1;
			}
			else
			{
				lVal = (-1) * lVal;
			}
			iPosMin = 1;
		}
		else
		{
			iPosMin = 0;
		}
		if ( lVal == 0 )
		{
			p_cRes [ 0 ] = (char) 48;
		}
		else
		{
			iPos = iTam - 2;
			while ( ( lVal > 0 ) && ( iPos >= iPosMin ) )
			{
				iDig = lVal % 10;
				lVal = lVal / 10;
				if ( iPos == iTam - 2 )
				{
					if ( iDec == 1 )
					{
						iDig = iDig + 1;
					}
				}
				p_cRes [ iPos ] = (char) ( 48 + iDig );
				iPos = iPos - 1;
			}	
			if ( lVal > 0 )
			{
				/* Error : */
				MemLiberar ( (void **) &p_cRes );
				p_cRes = NULL;
			}
		}
	}
	return ( p_cRes );
}

char * ConvEnteroSinSignoACadena ( unsigned int uiVal )
{
	return ( ConvEnteroLargoSinSignoACadena ( (unsigned long) uiVal ) );
}

char * ConvEnteroLargoSinSignoACadena ( unsigned long ulVal )
{
	int			iDig;
	int			iPosMin;
	int			iPos;
	int			iOrden;
	int			iTam;
	char *	p_cRes;
	int			iDec;		

	iOrden = NumDigitosEnteroLargoSinSigno ( ulVal );
	iTam = iOrden + 1;
	iDec = 0;
	p_cRes = CadCrear ( iTam - 1 );
	if ( ES_VALIDO ( p_cRes ) )
	{
		iPosMin = 0;
		if ( ulVal == 0 )
		{
			p_cRes [ 0 ] = (char) 48;
		}
		else
		{
			iPos = iTam - 2;
			while ( ( ulVal > 0 ) && ( iPos >= iPosMin ) )
			{
				iDig = ulVal % 10;
				ulVal = ulVal / 10;
				if ( iPos == iTam - 2 )
				{
					if ( iDec == 1 )
					{
						iDig = iDig + 1;
					}
				}
				p_cRes [ iPos ] = (char) ( 48 + iDig );
				iPos = iPos - 1;
			}	
			if ( ulVal > 0 )
			{
				/* Error : */
				MemLiberar ( (void **) &p_cRes );
				p_cRes = NULL;
			}
		}
	}
	return ( p_cRes );
}

char * ConvEnteroDobleLargoACadena ( long long llVal )
{
	int			iDig;
	int			iPosMin;
	int			iPos;
	int			iOrden;
	int			iTam;
	char *		p_cRes;
	int			iDec;		

	iOrden = NumDigitosEnteroDobleLargo ( llVal );
	if ( llVal < 0 )
	{
		iTam = iOrden + 2;	
	}
	else
	{
		iTam = iOrden + 1;
	}
	iDec = 0;
	p_cRes = CadCrear ( iTam - 1 );
	if ( ES_VALIDO ( p_cRes ) )
	{
		if ( llVal < 0 )
		{
			p_cRes [ 0 ] = '-';
			if ( llVal == LLONG_MIN )
			{
				llVal = LLONG_MAX;
				iDec = 1;
			}
			else
			{
				llVal = (-1) * llVal;
			}
			iPosMin = 1;
		}
		else
		{
			iPosMin = 0;
		}
		if ( llVal == 0 )
		{
			p_cRes [ 0 ] = (char) 48;
		}
		else
		{
			iPos = iTam - 2;
			while ( ( llVal > 0 ) && ( iPos >= iPosMin ) )
			{
				iDig = (int) ( llVal % 10 );
				llVal = llVal / 10;
				if ( iPos == iTam - 2 )
				{
					if ( iDec == 1 )
					{
						iDig = iDig + 1;
					}
				}
				p_cRes [ iPos ] = (char) ( 48 + iDig );
				iPos = iPos - 1;
			}	
			if ( llVal > 0 )
			{
				/* Error : */
				MemLiberar ( (void **) &p_cRes );
				p_cRes = NULL;
			}
		}
	}
	return ( p_cRes );
}

char * ConvEnteroDobleLargoSinSignoACadena ( unsigned long long ullVal )
{
	int			iDig;
	int			iPosMin;
	int			iPos;
	int			iOrden;
	int			iTam;
	char *		p_cRes;
	int			iDec;		

	iOrden = NumDigitosEnteroDobleLargoSinSigno ( ullVal );
	iTam = iOrden + 1;
	iDec = 0;
	p_cRes = CadCrear ( iTam - 1 );
	if ( ES_VALIDO ( p_cRes ) )
	{
		iPosMin = 0;
		if ( ullVal == 0 )
		{
			p_cRes [ 0 ] = (char) 48;
		}
		else
		{
			iPos = iTam - 2;
			while ( ( ullVal > 0 ) && ( iPos >= iPosMin ) )
			{
				iDig = (int) ( ullVal % 10 );
				ullVal = ullVal / 10;
				if ( iPos == iTam - 2 )
				{
					if ( iDec == 1 )
					{
						iDig = iDig + 1;
					}
				}
				p_cRes [ iPos ] = (char) ( 48 + iDig );
				iPos = iPos - 1;
			}	
			if ( ullVal > 0 )
			{
				/* Error : */
				MemLiberar ( (void **) &p_cRes );
				p_cRes = NULL;
			}
		}
	}
	return ( p_cRes );
}

char * ConvRealACadena ( float fVal )
{
	char *	p_cRes;
	float	fParteEnt;
	float	fParteDec;
	int		iDig;
	int		iPosMin;
	int		iPosPunto;
	int		iPos;
	int		iOrden;
	int		iTam;
	int		iDecimales;

	if ( fVal == 0.0 )
	{
		iOrden = 2;
		iDecimales = 1;
		fParteEnt = 0.0;
		fParteDec = 0.0;
	}
	else
	{
		iOrden = NumDigitosReal ( fVal );
		fParteEnt = NumParteEnteraReal( fVal );
		fParteDec = NumParteDecimalReal ( fVal );
		if ( fParteDec == 0.0 )
		{
			iDecimales = 1;
		}
		else
		{
			iDecimales = NumDigitosReal ( fParteDec ) - 1;
		}
	}
	if ( fVal < 0 )
	{
		iTam = iOrden + 2;	
	}
	else
	{
		iTam = iOrden + 1;
	}
	p_cRes = CadCrear ( iTam );
	if ( ES_VALIDO ( p_cRes ) )
	{
		if ( fVal < 0 )
		{
			p_cRes [ 0 ] = '-';
			fParteEnt = (-1) * fParteEnt;
			fParteDec = (-1) * fParteDec;
			iPosMin = 1;
		}
		else
		{
			iPosMin = 0;
		}
		if ( fParteEnt == 0.0 )
		{
			p_cRes [ iPosMin ] = '0';
			iPosPunto = iPosMin + 1;
		}
		else
		{
			iPosPunto = iTam - iDecimales - 1;
		}
		p_cRes [ iPosPunto ] = '.';
		iPos = iPosPunto - 1;
		while ( ( fParteEnt > 0.0 ) && ( iPos >= iPosMin ) )
		{
			iDig = (int) ( fParteEnt - ( 10 * NumParteEnteraReal ( fParteEnt / 10 ) ) );
			fParteEnt = fParteEnt / 10;
			p_cRes [ iPos ] = (char) ( 48 + iDig );
			iPos = iPos - 1;
		}
		if ( ( fParteEnt == 0.0 ) || ( iPos < iPosMin ) )
		{
			if ( fParteDec == 0.0 )
			{
				p_cRes [ iPosPunto + 1 ] = '0';
			}
			else
			{
				iPos = iPosPunto + 1;
				while ( ( fParteDec > 0.0 ) && ( iPos < iTam - 1 ) )
				{	
					if ( iPos < iTam - 2 )
					{
						iDig = (int) NumParteEnteraReal ( fParteDec * 10 );
					}
					else
					{
						iDig = ConvRealAEntero ( fParteDec * 10, 0 );
						if ( iDig == 10 )
						{
							//printf ( "HAY ACCARREO!!!\n" );
							// Acarreo:
							iPos = iPos - 1;
							while ( ( iPos > iPosPunto ) && ( p_cRes [ iPos ] == '9' ) )
							{
								iPos = iPos - 1;
							}
							if ( iPos > iPosPunto )
							{
								p_cRes [ iPos ] = (char) ( (int)(p_cRes [ iPos ]) + 1 );
								p_cRes [ iPos + 1 ] = (char) 0;
							}
							else
							{
								p_cRes [ iPosPunto + 1 ] = '0';
								iPos = iPosPunto - 1;
								while ( ( iPos >= iPosMin ) && ( p_cRes [ iPos ] == '9' ) )
								{
									p_cRes [ iPos ] = '0';
									iPos = iPos - 1;
								}
								if ( iPos >= iPosMin )
								{
									p_cRes [ iPos ] = (char) ( (int)(p_cRes [ iPos ]) + 1 );
								}
								else
								{
									// Error de tama?o por acarreo:
									//printf ( "ACARREO M?XIMO!\n" );
								}
							}
							iPos = iTam - 1;
							break;
						}
					}
					fParteDec = NumParteDecimalReal ( fParteDec * 10 );
					p_cRes [ iPos ] = (char) ( 48 + iDig );
					iPos = iPos + 1;
				}
				if ( iPos < iTam - 1 )
				{
					/* Error : */
					MemLiberar ( (void **) &p_cRes );
					p_cRes = NULL;
				}
			}
		}
		else
		{
			/* Error : */
			MemLiberar ( (void **) &p_cRes );
			p_cRes = NULL;
		}
	}
	return ( p_cRes );
}

char * ConvRealDobleACadena ( double dVal )
{
	char *	p_cRes;
	double	dParteEnt;
	double	dParteDec;
	int		iDig;
	int		iPosMin;
	int		iPosPunto;
	int		iPos;
	int		iOrden;
	int		iTam;
	int		iDecimales;

	if ( dVal == 0.0 )
	{
		iOrden = 2;
		iDecimales = 1;
		dParteEnt = 0.0;
		dParteDec = 0.0;
	}
	else
	{
		iOrden = NumDigitosRealDoble ( dVal );
		dParteEnt = NumParteEnteraRealDoble ( dVal );
		dParteDec = NumParteDecimalRealDoble ( dVal );
		if ( dParteDec == 0.0 )
		{
			iDecimales = 1;
		}
		else
		{
			iDecimales = NumDigitosRealDoble ( dParteDec ) - 1;
		}
	}
	if ( dVal < 0 )
	{
		iTam = iOrden + 2;	
	}
	else
	{
		iTam = iOrden + 1;
	}
	p_cRes = CadCrear ( iTam );
	if ( ES_VALIDO ( p_cRes ) )
	{
		if ( dVal < 0 )
		{
			p_cRes [ 0 ] = '-';
			dParteEnt = (-1) * dParteEnt;
			dParteDec = (-1) * dParteDec;
			iPosMin = 1;
		}
		else
		{
			iPosMin = 0;
		}
		if ( dParteEnt == 0.0 )
		{
			p_cRes [ iPosMin ] = '0';
			iPosPunto = iPosMin + 1;
		}
		else
		{
			iPosPunto = iTam - iDecimales - 1;
		}
		p_cRes [ iPosPunto ] = '.';
		iPos = iPosPunto - 1;
		while ( ( dParteEnt > 0.0 ) && ( iPos >= iPosMin ) )
		{
			iDig = (int) ( dParteEnt - ( 10 * NumParteEnteraRealDoble ( dParteEnt / 10 ) ) );
			dParteEnt = dParteEnt / 10;
			p_cRes [ iPos ] = (char) ( 48 + iDig );
			iPos = iPos - 1;
		}
		if ( ( dParteEnt == 0.0 ) || ( iPos < iPosMin ) )
		{
			if ( dParteDec == 0.0 )
			{
				p_cRes [ iPosPunto + 1 ] = '0';
			}
			else
			{
				iPos = iPosPunto + 1;
				while ( ( dParteDec > 0.0 ) && ( iPos < iTam ) )
				{	
					if ( iPos < iTam - 1 )
					{
						iDig = (int) NumParteEnteraRealDoble ( dParteDec * 10 );
					}
					else
					{
						iDig = ConvRealDobleAEntero ( dParteDec * 10, 0 );
						if ( iDig == 10 )
						{
							//printf ( "HAY ACCARREO!!!\n" );
							// Acarreo:
							iPos = iPos - 1;
							while ( (iPos > iPosPunto ) && ( p_cRes [ iPos ] == '9' ) )
							{
								iPos = iPos - 1;
							}
							if ( iPos > iPosPunto )
							{
								p_cRes [ iPos ] = (char) ( (int)(p_cRes [ iPos ]) + 1 );
								p_cRes [ iPos + 1 ] = (char) 0;
							}
							else
							{
								p_cRes [ iPosPunto + 1 ] = '0';
								iPos = iPosPunto - 1;
								while ( ( iPos >= iPosMin ) && ( p_cRes [ iPos ] == '9' ) )
								{
									p_cRes [ iPos ] = '0';
									iPos = iPos - 1;
								}
								if ( iPos >= iPosMin )
								{
									p_cRes [ iPos ] = (char) ( (int)(p_cRes [ iPos ]) + 1 );
								}
								else
								{
									// Error de tama?o por acarreo:
									//printf ( "ACARREO M?XIMO!\n" );
								}
							}
							iPos = iTam - 1;
							break;
						}
					}
					dParteDec = NumParteDecimalRealDoble ( dParteDec * 10 );
					p_cRes [ iPos ] = (char) ( 48 + iDig );
					iPos = iPos + 1;
				}
				if ( iPos < iTam - 1 )
				{
					/* Error : */
					MemLiberar ( (void **) &p_cRes );
					p_cRes = NULL;
				}
			}
		}
		else
		{
			/* Error : */
			MemLiberar ( (void **) &p_cRes );
			p_cRes = NULL;
		}
	}
	return ( p_cRes );
}


char * ConvEnteroACadenaHex ( int iVal )
{
	char *	p_cRes;

	if ( iVal >= 0 )
	{
		p_cRes = ConvEnteroSinSignoACadenaHex ( (unsigned int) iVal );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

char * ConvEnteroLargoACadenaHex ( long lVal )
{
	char *	p_cRes;

	if ( lVal >= 0 )
	{
		p_cRes = ConvEnteroLargoSinSignoACadenaHex ( (unsigned long) lVal );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

char * ConvEnteroSinSignoACadenaHex ( unsigned int uiVal )
{
	int		iTam;
	char *	p_cRes;

	iTam = NumDigitosEnteroSinSigno ( (unsigned int)( uiVal/16  ) ) + 2;
	p_cRes = CadCrear ( iTam );
	if ( ES_VALIDO ( p_cRes ) )
	{
		sprintf ( p_cRes, "&%0X", uiVal );
	}
	return ( p_cRes );
}

char * ConvEnteroLargoSinSignoACadenaHex ( unsigned long ulVal )
{
	int		iTam;
	char *	p_cRes;

	iTam = NumDigitosEnteroLargoSinSigno ( (unsigned long)( ulVal/16  ) ) + 2;
	p_cRes = CadCrear ( iTam );
	if ( ES_VALIDO ( p_cRes ) )
	{
		sprintf ( p_cRes, "&%0lX", ulVal );
	}
	return ( p_cRes );
}

unsigned int ConvCadenaHexAEnteroSinSigno ( const char * p_cVal )
{
	unsigned int	uiRes;
	unsigned long	ulVal;
	const char *	p_cNumero;
	char *			p_cFin;

	uiRes = 0;
	if ( ES_VALIDO ( p_cVal ) )
	{
		p_cNumero = _ConvSaltarPrefijoHex ( p_cVal );
		if ( _ConvNoEmpiezaPorMenos ( p_cNumero ) == 1 )
		{
			errno = 0;
			ulVal = strtoul ( p_cNumero, &p_cFin, CONV_BASE_HEX );
			if ( p_cFin != p_cNumero )
			{
				if ( *p_cFin == ASCII_NUL )
				{
					if ( errno != ERANGE )
					{
						if ( ulVal <= ( unsigned long ) UINT_MAX )
						{
							uiRes = ( unsigned int ) ulVal;
						}
						else
						{
							ERROR_ESTABLECER ( ERR_CONVERSION_IMPOSIBLE );
						}
					}
					else
					{
						ERROR_ESTABLECER ( ERR_CONVERSION_IMPOSIBLE );
					}
				}
				else
				{
					ERROR_ESTABLECER ( ERR_CONVERSION_IMPOSIBLE );
				}
			}
			else
			{
				ERROR_ESTABLECER ( ERR_CONVERSION_IMPOSIBLE );
			}
		}
		else
		{
			ERROR_ESTABLECER ( ERR_CONVERSION_IMPOSIBLE );
		}
	}
	else
	{
		ERROR_ESTABLECER ( ERR_PARAMETROS );
	}
	return ( uiRes );
}

unsigned long ConvCadenaHexAEnteroLargoSinSigno ( const char * p_cVal )
{
	unsigned long	ulRes;
	unsigned long	ulVal;
	const char *	p_cNumero;
	char *			p_cFin;

	ulRes = 0;
	if ( ES_VALIDO ( p_cVal ) )
	{
		p_cNumero = _ConvSaltarPrefijoHex ( p_cVal );
		if ( _ConvNoEmpiezaPorMenos ( p_cNumero ) == 1 )
		{
			errno = 0;
			ulVal = strtoul ( p_cNumero, &p_cFin, CONV_BASE_HEX );
			if ( p_cFin != p_cNumero )
			{
				if ( *p_cFin == ASCII_NUL )
				{
					if ( errno != ERANGE )
					{
						ulRes = ulVal;
					}
					else
					{
						ERROR_ESTABLECER ( ERR_CONVERSION_IMPOSIBLE );
					}
				}
				else
				{
					ERROR_ESTABLECER ( ERR_CONVERSION_IMPOSIBLE );
				}
			}
			else
			{
				ERROR_ESTABLECER ( ERR_CONVERSION_IMPOSIBLE );
			}
		}
		else
		{
			ERROR_ESTABLECER ( ERR_CONVERSION_IMPOSIBLE );
		}
	}
	else
	{
		ERROR_ESTABLECER ( ERR_PARAMETROS );
	}
	return ( ulRes );
}

int	ConvCadenaHexAEntero ( const char * p_cVal )
{
	return ( (int) ConvCadenaHexAEnteroSinSigno ( p_cVal ) );
}

long ConvCadenaHexAEnteroLargo ( const char * p_cVal )
{
	return ( (long) ConvCadenaHexAEnteroLargoSinSigno ( p_cVal ) );
}

unsigned long long ConvCadenaHexAEnteroDobleLargoSinSigno ( const char * p_cVal )
{
	unsigned long long	ullRes;
	unsigned long long	ullVal;
	const char *		p_cNumero;
	char *				p_cFin;

	ullRes = 0;
	if ( ES_VALIDO ( p_cVal ) )
	{
		p_cNumero = _ConvSaltarPrefijoHex ( p_cVal );
		if ( _ConvNoEmpiezaPorMenos ( p_cNumero ) == 1 )
		{
			errno = 0;
			ullVal = strtoull ( p_cNumero, &p_cFin, CONV_BASE_HEX );
			if ( p_cFin != p_cNumero )
			{
				if ( *p_cFin == ASCII_NUL )
				{
					if ( errno != ERANGE )
					{
						ullRes = ullVal;
					}
					else
					{
						ERROR_ESTABLECER ( ERR_CONVERSION_IMPOSIBLE );
					}
				}
				else
				{
					ERROR_ESTABLECER ( ERR_CONVERSION_IMPOSIBLE );
				}
			}
			else
			{
				ERROR_ESTABLECER ( ERR_CONVERSION_IMPOSIBLE );
			}
		}
		else
		{
			ERROR_ESTABLECER ( ERR_CONVERSION_IMPOSIBLE );
		}
	}
	else
	{
		ERROR_ESTABLECER ( ERR_PARAMETROS );
	}
	return ( ullRes );
}

long long ConvCadenaHexAEnteroDobleLargo( const char * p_cVal )
{
	return ( (long long) ConvCadenaHexAEnteroDobleLargoSinSigno ( p_cVal ) );
}


