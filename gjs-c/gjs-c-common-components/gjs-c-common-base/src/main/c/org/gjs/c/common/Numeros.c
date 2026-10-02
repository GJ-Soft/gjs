/******************************************************************************/
/*                                Numeros.cpp                                 */
/*----------------------------------------------------------------------------*/
/* Librería:  GBase                                                           */
/* Versión:   1.0.0                                                           */
/* Fecha:     28/06/2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Fichero de código fuente que contiene la implementación de las rutinas     */
/* de carácter general de manejo de los formatos numéricos de la máquina.     */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#include "Numeros.h"


#include "BaseConfig.h"




int NumDigitosEntero ( int iVal )
{
	return ( NumDigitosEnteroLargo ( (long) iVal ) );
}

int NumDigitosEnteroLargo ( long lVal )
{
	int iDigs;

	if ( lVal == 0 )
	{
		iDigs = 1;
	}
	else
	{
		if ( lVal < 0 )
		{
			if ( lVal == LONG_MIN )
			{
				lVal = LONG_MAX;
			}
			else
			{
				lVal = (-1) * lVal;
			}
		}
		iDigs = 0;
		while ( lVal > 0 )
		{
			iDigs = iDigs + 1;
			lVal = lVal / 10;
		}
	}
	return ( iDigs );
}

int NumDigitosEnteroDobleLargo ( long long llVal )
{
	int iDigs;

	if ( llVal == 0 )
	{
		iDigs = 1;
	}
	else
	{
		if ( llVal < 0 )
		{
			if ( llVal == LLONG_MIN )
			{
				llVal = LLONG_MAX;
			}
			else
			{
				llVal = (-1) * llVal;
			}
		}
		iDigs = 0;
		while ( llVal > 0 )
		{
			iDigs = iDigs + 1;
			llVal = llVal / 10;
		}
	}
	return ( iDigs );
}

int NumDigitosEnteroDobleLargoSinSigno ( unsigned long long ullVal )
{
	int iDigs;

	if ( ullVal == 0 )
	{
		iDigs = 1;
	}
	else
	{
		iDigs = 0;
		while ( ullVal > 0 )
		{
			iDigs = iDigs + 1;
			ullVal = ullVal / 10;
		}
	}
	return ( iDigs );
}

int NumDigitosEnteroSinSigno ( unsigned int uiVal )
{
	return ( NumDigitosEnteroLargoSinSigno ( (unsigned long) uiVal ) );
}

int NumDigitosEnteroLargoSinSigno ( unsigned long ulVal )
{
	int iDigs;

	if ( ulVal == 0 )
	{
		iDigs = 1;
	}
	else
	{
		iDigs = 0;
		while ( ulVal > 0 )
		{
			iDigs = iDigs + 1;
			ulVal = ulVal / 10;
		}
	}
	return ( iDigs );
}

int NumDigitosReal ( float fVal )
{
	float	fParteEnt;
	float	fParteDec;
	int		iDigs;
	int		iDigsDec;

	if ( fVal == 0 )
	{
		iDigs = 1;
	}
	else
	{
		if ( fVal < 0 )
		{
			fVal = (-1) * fVal;
		}
		fParteEnt = NumParteEnteraReal( fVal );
		fParteDec = NumParteDecimalReal ( fVal );

		if ( fParteEnt == 0.0 )
		{
			iDigs = 1;
		}
		else
		{
			iDigs = 0;
		}
		while ( ( fParteEnt > 0.0 ) && ( iDigs < FLT_MANT_DIG ) )
		{
			iDigs = iDigs + 1;
			fParteEnt = NumParteEnteraReal ( fParteEnt / 10 );
		}
		if ( fParteDec == 0.0 )
		{
			iDigs = iDigs + 1;
		}
		else
		{
			while ( NumParteEnteraReal ( fParteDec * 10 ) == 0.0 )
			{
				iDigs = iDigs + 1;
				fParteDec = NumParteDecimalReal ( fParteDec * 10 );
			}
			iDigsDec = 0;
			while ( ( fParteDec > 0.0 ) && ( iDigsDec < FLT_DIG ) )
			{
				iDigs = iDigs + 1;
				iDigsDec = iDigsDec + 1;
				fParteDec = NumParteDecimalReal ( fParteDec * 10 );
			}
		}
	}
	return ( iDigs );
}

int NumDigitosRealDoble ( double dVal )
{
	double	dParteEnt;
	double	dParteDec;
	int		iDigs;
	int		iDigsDec;		

	if ( dVal == 0 )
	{
		iDigs = 1;
	}
	else
	{
		if ( dVal < 0 )
		{
			dVal = (-1) * dVal;
		}
		dParteEnt = NumParteEnteraRealDoble ( dVal );
		dParteDec = NumParteDecimalRealDoble ( dVal );

		if ( dParteEnt == 0.0 )
		{
			iDigs = 1;
		}
		else
		{
			iDigs = 0;
		}
		while ( ( dParteEnt > 0.0 ) && ( iDigs < DBL_MANT_DIG ) )
		{
			iDigs = iDigs + 1;
			dParteEnt = NumParteEnteraRealDoble ( dParteEnt / 10 );
		}
		if ( dParteDec == 0.0 )
		{
			iDigs = iDigs + 1;
		}
		else
		{
			while ( NumParteEnteraRealDoble ( dParteDec * 10 ) == 0.0 )
			{
				iDigs = iDigs + 1;
				dParteDec = NumParteDecimalRealDoble ( dParteDec * 10 );
			}
			iDigsDec = 0;
			while ( ( dParteDec > 0.0 ) && ( iDigsDec < DBL_DIG ) )
			{
				iDigs = iDigs + 1;
				iDigsDec = iDigsDec + 1;
				dParteDec = NumParteDecimalRealDoble ( dParteDec * 10 );
			}
		}
	}
	return ( iDigs );
}

float NumParteEnteraReal ( float fVal )
{
	float fRes;

	if ( fVal == 0.0 )
	{
		fRes = 0;
	}
	else
	{
		if ( fVal > 0 )
		{
			fRes = (float) floor ( fVal );
		}
		else
		{
			fRes = (float) ceil ( fVal );
		}
	}
	return ( fRes );
}

float NumParteDecimalReal( float fVal )
{
	float fRes;

	if ( fVal == 0.0 )
	{
		fRes = 0;
	}
	else
	{
		if ( fVal > 0 )
		{
			fRes = fVal - (float) floor ( fVal );
		}
		else
		{
			fRes = fVal - (float) ceil ( fVal );
		}
	}
	return ( fRes );
}

double NumParteEnteraRealDoble ( double dVal )
{
	double dRes;

	if ( dVal == 0.0 )
	{
		dRes = 0;
	}
	else
	{
		if ( dVal > 0 )
		{
			dRes = floor ( dVal );
		}
		else
		{
			dRes = ceil ( dVal );
		}
	}
	return ( dRes );
}

double NumParteDecimalRealDoble ( double dVal )
{
	double dRes;

	if ( dVal == 0.0 )
	{
		dRes = 0;
	}
	else
	{
		if ( dVal > 0 )
		{
			dRes = dVal - floor ( dVal );
		}
		else
		{
			dRes = dVal - ceil ( dVal );
		}
	}
	return ( dRes );
}

int MaxDigitosEntero ()
{
	return ( NumDigitosEntero ( INT_MAX ) );
}

int MaxDigitosEnteroLargo ()
{
	return ( NumDigitosEnteroLargo ( LONG_MAX ) );
}

int MaxDigitosEnteroDobleLargo ()
{
	return ( NumDigitosEnteroDobleLargo ( LLONG_MAX ) );
}

int MaxDigitosEnteroDobleLargoSinSigno ()
{
	return ( NumDigitosEnteroDobleLargoSinSigno ( ULLONG_MAX ) );
}

int MaxDigitosEnteroSinSigno ()
{
	return ( NumDigitosEnteroSinSigno ( UINT_MAX ) );
}

int MaxDigitosEnteroLargoSinSigno ()
{
	return ( NumDigitosEnteroLargoSinSigno ( ULONG_MAX ) );
}

/* Los digitos que el usuario puede escribir y recuperar intactos: la ida y
   vuelta decimal -> binario -> decimal. Ver el comentario de la cabecera. */
int MaxDigitosSignificativosReal ()
{
	return ( FLT_DIG );
}

int MaxDigitosSignificativosRealDoble ()
{
	return ( DBL_DIG );
}

/* Los digitos que hay que imprimir para no perder nada del valor que ya esta
   en memoria: la ida y vuelta binario -> decimal -> binario. Son mas que los
   significativos ( 9 frente a 6, 17 frente a 15 ), y es la cifra que hace
   falta al serializar. */
int MaxDigitosReproducirReal ()
{
	return ( FLT_DECIMAL_DIG );
}

int MaxDigitosReproducirRealDoble ()
{
	return ( DBL_DECIMAL_DIG );
}

/* La potencia de diez mas alta representable. No acota la longitud de una
   cadena valida: ver la cabecera. */
int MaxExponenteReal ()
{
	return ( FLT_MAX_10_EXP );
}

int MaxExponenteRealDoble ()
{
	return ( DBL_MAX_10_EXP );
}







