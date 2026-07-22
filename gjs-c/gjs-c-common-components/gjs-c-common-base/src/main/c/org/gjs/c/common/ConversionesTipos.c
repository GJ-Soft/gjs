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


// PENDIENTE: Al convertir desde cadena asegurarse de que el número de dígitos no sobrepasa el máximo.


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

#if ( defined ( LLONG ) )
llong ConvRealAEnteroDobleLargo ( float fVal, int iTruncar )
{
	llong	llRes;
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
		llRes = (llong) fEntero;
	}
	return ( llRes );
}

ullong ConvRealAEnteroDobleLargoSinSigno ( float fVal, int iTruncar )
{
	ullong	ullRes;
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
		ullRes = (ullong) fEntero;
	}
	else
	{
		ullRes = 0;
	}
	return ( ullRes );
}
#endif

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

#if ( defined ( LLONG ) )
llong ConvRealDobleAEnteroDobleLargo ( double dVal, int iTruncar )
{
	llong	llRes;
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
		llRes = (llong) dEntero;
	}
	return ( llRes );
}

ullong ConvRealDobleAEnteroDobleLargoSinSigno ( double dVal, int iTruncar )
{
	ullong	ullRes;
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
		ullRes = (ullong) dEntero;
	}
	else
	{
		ullRes = 0;
	}
	return ( ullRes );
}
#endif

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

unsigned int ConvCadenaAEnteroSinSigno ( const char * p_cVal )
{
	unsigned int uiVal;

	if ( ES_VALIDO ( p_cVal ) )
	{
		sscanf ( p_cVal, "%u", &uiVal );
	}
	else
	{
		uiVal = 0;
	}
	return ( uiVal );
}

unsigned long ConvCadenaAEnteroLargoSinSigno ( const char * p_cVal )
{
	unsigned long ulVal;

	if ( ES_VALIDO ( p_cVal ) )
	{
		sscanf ( p_cVal, "%lu", &ulVal );
	}
	else
	{
		ulVal = 0;
	}
	return ( ulVal );
}

int	ConvCadenaAEntero ( const char * p_cVal )
{
	int iVal;

	if ( ES_VALIDO ( p_cVal ) )
	{
		sscanf ( p_cVal, "%d", &iVal );
	}
	else
	{
		iVal = 0;
	}
	return ( iVal );
}

long ConvCadenaAEnteroLargo ( const char * p_cVal )
{
	long lVal;

	if ( ES_VALIDO ( p_cVal ) )
	{
		sscanf ( p_cVal, "%ld", &lVal );
	}
	else
	{
		lVal = 0;
	}
	return ( lVal );
}

#if ( defined ( LLONG ) )
llong ConvCadenaAEnteroDobleLargo ( const char * p_cVal )
{
	llong	llVal;
	int		iPos;
	llong	llPeso;
	int		iRes;
	int		iDig;
	int		iPosMin;

	if ( ES_VALIDO ( p_cVal ) )
	{
		iPos = CadLongitud ( p_cVal ) - 1;
		llVal = 0;
		llPeso = 1;
		if ( p_cVal [ 0 ] == '-' )
		{
			iPosMin = 1;
		}
		else
		{
			iPosMin = 0;
		}
		iRes = 1;
		while ( ( iPos >= iPosMin ) && ( iRes == 1 ) )
		{
			if ( ( p_cVal [ iPos ] >= '0' ) && ( p_cVal [ iPos ] <= '9' ) )
			{
				iDig = ((int) p_cVal [ iPos ]) - ((int) '0');
				llVal = llVal + iDig * llPeso;
				llPeso = llPeso * 10;
				iPos = iPos - 1;
			}
			else
			{
				iRes = 0;
			}
		}	
		if ( iRes == 0 )
		{
			llVal = 0;
		}
		else if ( p_cVal [ 0 ] == '-' )
		{
			llVal = - llVal;
		}
	}
	else
	{
		llVal = 0;
	}
	return ( llVal );
}

ullong ConvCadenaAEnteroDobleLargoSinSigno ( const char * p_cVal )
{
	llong	ullVal;
	int		iPos;
	llong	ullPeso;
	int		iRes;
	int		iDig;

	if ( ES_VALIDO ( p_cVal ) )
	{
		iPos = CadLongitud ( p_cVal ) - 1;
		ullVal = 0;
		ullPeso = 1;
		iRes = 1;
		while ( ( iPos >= 0 ) && ( iRes == 1 ) )
		{
			if ( ( p_cVal [ iPos ] >= '0' ) && ( p_cVal [ iPos ] <= '9' ) )
			{
				iDig = ((int) p_cVal [ iPos ]) - ((int) '0');
				ullVal = ullVal + iDig * ullPeso;
				ullPeso = ullPeso * 10;
				iPos = iPos - 1;
			}
			else
			{
				iRes = 0;
			}
		}	
		if ( iRes == 0 )
		{
			ullVal = 0;
		}
	}
	else
	{
		ullVal = 0;
	}
	return ( ullVal );
}
#endif

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

#if ( defined ( LLONG ) )
char * ConvEnteroDobleLargoACadena ( llong llVal )
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

char * ConvEnteroDobleLargoSinSignoACadena ( ullong ullVal )
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
#endif

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
	unsigned int uiVal;

	if ( ES_VALIDO ( p_cVal ) )
	{
		if ( p_cVal [ 0 ] == '&' )
		{
			sscanf ( p_cVal, "&%x", &uiVal );
		}
		else
		{
			sscanf ( p_cVal, "%x", &uiVal );
		}
	}
	else
	{
		uiVal = 0;
	}
	return ( uiVal );
}

unsigned long ConvCadenaHexAEnteroLargoSinSigno ( const char * p_cVal )
{
	unsigned long ulVal;

	if ( ES_VALIDO ( p_cVal ) )
	{
		if ( p_cVal [ 0 ] == '&' )
		{
			sscanf ( p_cVal, "&%lx", &ulVal );
		}
		else
		{
			sscanf ( p_cVal, "%lx", &ulVal );
		}
	}
	else
	{
		ulVal = 0;
	}
	return ( ulVal );
}

int	ConvCadenaHexAEntero ( const char * p_cVal )
{
	return ( (int) ConvCadenaHexAEnteroSinSigno ( p_cVal ) );
}

long ConvCadenaHexAEnteroLargo ( const char * p_cVal )
{
	return ( (long) ConvCadenaHexAEnteroLargoSinSigno ( p_cVal ) );
}

#if ( defined ( LLONG ) )
ullong ConvCadenaHexAEnteroDobleLargoSinSigno ( const char * p_cVal )
{
	ullong ullVal;

	if ( ES_VALIDO ( p_cVal ) )
	{
		if ( p_cVal [ 0 ] == '&' )
		{
			sscanf ( p_cVal, "&%llx", &ullVal );
		}
		else
		{
			sscanf ( p_cVal, "%llx", &ullVal );
		}
	}
	else
	{
		ullVal = 0;
	}
	return ( ullVal );
}

llong ConvCadenaHexAEnteroDobleLargo( const char * p_cVal )
{
	return ( (llong) ConvCadenaHexAEnteroLargoSinSigno ( p_cVal ) );
}
#endif


