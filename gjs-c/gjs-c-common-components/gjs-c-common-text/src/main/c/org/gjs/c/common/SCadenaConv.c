#include "SCadenaConv.h"
#include "Cadenas.h"

#include "TextoConfig.h"


SCadenaConv * SCadcCrearDef () 
{
	SCadenaConv * p_cadObj;

	p_cadObj = (SCadenaConv *) MemReservar ( sizeof ( SCadenaConv ) );
	if ( ES_VALIDO ( p_cadObj ) )
	{
		p_cadObj->p_cadInfo = SCadCrearDef ();
		p_cadObj->p_convValores = SConvCrearDef ();
	}
	return ( p_cadObj );
}

SCadenaConv * SCadcCrear  ( int iLong )
{
	SCadenaConv * p_cadObj;

	p_cadObj = (SCadenaConv *) MemReservar ( sizeof ( SCadenaConv ) );
	if ( ES_VALIDO ( p_cadObj ) )
	{
		p_cadObj->p_cadInfo = SCadCrear ( iLong );
		p_cadObj->p_convValores = SConvCrearDef ();
	}
	return ( p_cadObj );
}

SCadenaConv * SCadcCrearLit  ( const char * p_cValor )
{
	SCadenaConv * p_cadObj;

	p_cadObj = (SCadenaConv *) MemReservar ( sizeof ( SCadenaConv ) );
	if ( ES_VALIDO ( p_cadObj ) )
	{
		p_cadObj->p_cadInfo = SCadGenerar ( p_cValor );
		p_cadObj->p_convValores = SConvCrearDef ();
	}
	return ( p_cadObj );
}

SCadenaConv * SCadcCrearCad ( SCadena * p_cadValor )
{
	SCadenaConv * p_cadObj;

	p_cadObj = SCadcCrearDef ();
	if ( ES_VALIDO ( p_cadObj ) )
	{
		SCadAsignar ( p_cadObj->p_cadInfo, p_cadValor );
	}
	return ( p_cadObj );
}

SCadenaConv * SCadcEncapsular ( SCadena * p_cadValor )
{
	SCadenaConv * p_cadObj;

	if ( ES_VALIDO ( p_cadValor ) )
	{
		p_cadObj = (SCadenaConv *) MemReservar ( sizeof ( SCadenaConv ) );
		if ( ES_VALIDO ( p_cadObj ) )
		{
			p_cadObj->p_cadInfo = p_cadValor;
			p_cadObj->p_convValores = SConvCrearDef ();
		}
	}
	else
	{
		p_cadObj = NULL;
	}
	return ( p_cadObj );
}

void SCadcDestruir ( SCadenaConv ** p_p_cadObj )
{
	SCadenaConv * p_cadObj;
	
	if ( ES_VALIDO ( p_p_cadObj ) )
	{
		p_cadObj = *p_p_cadObj;

		if ( ES_VALIDO ( p_cadObj ) )
		{
			SCadDestruir ( &(p_cadObj->p_cadInfo) );
			SConvDestruir ( &(p_cadObj->p_convValores) );
			MemLiberar ( (void **) p_p_cadObj );
		}
	}
}

int SCadcInicializar ( SCadenaConv * p_cadObj, int iLong )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = SCadInicializar ( p_cadObj->p_cadInfo, iLong );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadcVaciar ( SCadenaConv * p_cadObj )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = SCadVaciar ( p_cadObj->p_cadInfo );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadcEsValida ( SCadenaConv * p_cadObj )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = SCadEsValida ( p_cadObj->p_cadInfo );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadcEsNula ( SCadenaConv * p_cadObj )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = SCadEsNula ( p_cadObj->p_cadInfo );
	}
	else
	{
		iRes = 1;
	}
	return ( iRes );
}

int SCadcEstaVacia ( SCadenaConv * p_cadObj )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = SCadEstaVacia ( p_cadObj->p_cadInfo );
	}
	else
	{
		iRes = 1;
	}
	return ( iRes );
}

int SCadcLimpiar ( SCadenaConv * p_cadObj )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = SCadLimpiar ( p_cadObj->p_cadInfo );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadcLlenar ( SCadenaConv * p_cadObj, char cVal )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = SCadLlenar ( p_cadObj->p_cadInfo, cVal );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadcLimpiarDesde ( SCadenaConv * p_cadObj, int iPos )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = SCadLimpiarDesde ( p_cadObj->p_cadInfo, iPos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadcLlenarDesde ( SCadenaConv * p_cadObj, int iPos, char cVal )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = SCadLlenarDesde ( p_cadObj->p_cadInfo, iPos, cVal );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

char SCadcCaracter ( SCadenaConv * p_cadObj, int iCar )
{
	char cRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		cRes = SCadCaracter ( p_cadObj->p_cadInfo, iCar );
	}
	else
	{
		cRes = (char) 0;
	}
	return ( cRes );
}

int SCadcEstablecerCaracter ( SCadenaConv * p_cadObj, int iCar, char cVal )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = SCadEstablecerCaracter ( p_cadObj->p_cadInfo, iCar, cVal );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadcLongitud ( SCadenaConv * p_cadObj )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = SCadLongitud ( p_cadObj->p_cadInfo );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadcMaxTam ( SCadenaConv * p_cadObj )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = SCadMaxTam ( p_cadObj->p_cadInfo );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadcEspacioLibre ( SCadenaConv * p_cadObj )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = SCadEspacioLibre ( p_cadObj->p_cadInfo );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadcInsertar ( SCadenaConv * p_cadObj, int iPos, SCadenaConv * p_cadValor )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = SCadInsertar ( p_cadObj->p_cadInfo, iPos, SCadcCadena ( p_cadValor ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadcInsertarCad ( SCadenaConv * p_cadObj, int iPos, SCadena * p_cadValor )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = SCadInsertar ( p_cadObj->p_cadInfo, iPos, p_cadValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadcInsertarLit ( SCadenaConv * p_cadObj, int iPos, const char * p_cValor )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = SCadInsertarLiteral( p_cadObj->p_cadInfo, iPos, p_cValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadcInsertarCaracter ( SCadenaConv * p_cadObj, int iPos, char cValor )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = SCadInsertarCaracter ( p_cadObj->p_cadInfo, iPos, cValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadcEscribir ( SCadenaConv * p_cadObj, int iPos, SCadenaConv * p_cadValor )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = SCadEscribir ( p_cadObj->p_cadInfo, iPos, SCadcCadena ( p_cadValor ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadcEscribirCad ( SCadenaConv * p_cadObj, int iPos, SCadena * p_cadValor )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = SCadEscribir ( p_cadObj->p_cadInfo, iPos, p_cadValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadcEscribirLit ( SCadenaConv * p_cadObj, int iPos, const char * p_cValor )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = SCadEscribirLiteral ( p_cadObj->p_cadInfo, iPos, p_cValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadcEscribirCaracter ( SCadenaConv * p_cadObj, int iPos, char cValor )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = SCadEscribirCaracter ( p_cadObj->p_cadInfo, iPos, cValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadcAsignar ( SCadenaConv * p_cadObj, SCadenaConv * p_cadValor )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = SCadAsignar ( p_cadObj->p_cadInfo, SCadcCadena ( p_cadValor ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadcAsignarCad ( SCadenaConv * p_cadObj, SCadena * p_cadValor )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = SCadAsignar ( p_cadObj->p_cadInfo, p_cadValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadcAsignarLit ( SCadenaConv * p_cadObj, const char * p_cValor )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = SCadAsignarLiteral ( p_cadObj->p_cadInfo, p_cValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

char * SCadcValor ( SCadenaConv * p_cadObj )
{
	char * p_cRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		p_cRes = SCadValor ( p_cadObj->p_cadInfo );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

const char * SCadcValorConstante ( SCadenaConv * p_cadObj )
{
	const char * p_cRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		p_cRes = SCadValorConstante ( p_cadObj->p_cadInfo );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

SCadena * SCadcCadena ( SCadenaConv * p_cadObj )
{
	SCadena * p_cadRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		p_cadRes = p_cadObj->p_cadInfo;
	}
	else
	{
		p_cadRes = NULL;
	}
	return ( p_cadRes );
}

int SCadcValorEntero ( SCadenaConv * p_cadObj )
{
	int iValor;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		if ( SCadcEsNumerica ( p_cadObj ) == 1 )
		{
			iValor = SConvEntero ( p_cadObj->p_convValores );
		}
		else
		{
			iValor = 0;
		}
	}
	else
	{
		iValor = 0;
	}
	return ( iValor );
}

long SCadcValorEnteroLargo ( SCadenaConv * p_cadObj )
{
	long lValor;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		if ( SCadcEsNumerica ( p_cadObj ) == 1 )
		{
			lValor = SConvEnteroLargo ( p_cadObj->p_convValores );
		}
		else
		{
			lValor = 0;
		}
	}
	else
	{
		lValor = 0;
	}
	return ( lValor );
}

long long SCadcValorEnteroDobleLargo ( SCadenaConv * p_cadObj )
{
	long long llValor;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		if ( SCadcEsNumerica ( p_cadObj ) == 1 )
		{
			llValor = SConvEnteroDobleLargo ( p_cadObj->p_convValores );
		}
		else
		{
			llValor = 0;
		}
	}
	else
	{
		llValor = 0;
	}
	return ( llValor );
}

unsigned int SCadcValorEnteroSinSigno ( SCadenaConv * p_cadObj )
{
	unsigned int uiValor;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		if ( SCadcEsNumerica ( p_cadObj ) == 1 )
		{
			uiValor = SConvEnteroSinSigno ( p_cadObj->p_convValores );
		}
		else
		{
			uiValor = 0;
		}
	}
	else
	{
		uiValor = 0;
	}
	return ( uiValor );
}

unsigned long SCadcValorEnteroLargoSinSigno ( SCadenaConv * p_cadObj )
{
	unsigned long ulValor;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		if ( SCadcEsNumerica ( p_cadObj ) == 1 )
		{
			ulValor = SConvEnteroLargoSinSigno ( p_cadObj->p_convValores );
		}
		else
		{
			ulValor = 0;
		}
	}
	else
	{
		ulValor = 0;
	}
	return ( ulValor );
}

int SCadcValorEnteroConvirtiendoDeHexadecimal ( SCadenaConv * p_cadObj )
{
	int	iValor;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		if ( SCadcEsNumericaHexadecimal ( p_cadObj ) == 1 )
		{
			iValor = SConvEntero ( p_cadObj->p_convValores );
		}
		else
		{
			iValor = 0;
		}
	}
	else
	{
		iValor = 0;
	}
	return ( iValor );
}

long SCadcValorEnteroLargoConvirtiendoDeHexadecimal ( SCadenaConv * p_cadObj )
{
	long lValor;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		if ( SCadcEsNumericaHexadecimal ( p_cadObj ) == 1 )
		{
			lValor = SConvEnteroLargo ( p_cadObj->p_convValores );
		}
		else
		{
			lValor = 0;
		}
	}
	else
	{
		lValor = 0;
	}
	return ( lValor );
}

float SCadcValorReal ( SCadenaConv * p_cadObj )
{
	float fValor;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		if ( SCadcEsNumerica ( p_cadObj ) == 1 )
		{
			fValor = SConvReal ( p_cadObj->p_convValores );
		}
		else
		{
			fValor = 0.0;
		}
	}
	else
	{
		fValor = 0.0;
	}
	return ( fValor );
}

double SCadcValorRealDoble ( SCadenaConv * p_cadObj )
{
	double dValor;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		if ( SCadcEsNumerica ( p_cadObj ) == 1 )
		{
			dValor = SConvRealDoble ( p_cadObj->p_convValores );
		}
		else
		{
			dValor = 0.0;
		}
	}
	else
	{
		dValor = 0.0;
	}
	return ( dValor );
}

void SCadcCopiarLit ( SCadenaConv * p_cadObj, const char * p_cValor )
{
	if ( ES_VALIDO ( p_cadObj ) )
	{
		SCadCopiarLiteral ( p_cadObj->p_cadInfo, p_cValor );
	}
}

void SCadcConcatenarLit ( SCadenaConv * p_cadObj, const char * p_cValor )
{
	if ( ES_VALIDO ( p_cadObj ) )
	{
		SCadConcatenarLiteral ( p_cadObj->p_cadInfo, p_cValor );
	}
}

void SCadcCopiarCad ( SCadenaConv * p_cadObj, SCadena * p_cadValor )
{
	if ( ES_VALIDO ( p_cadObj ) )
	{
		SCadCopiar ( p_cadObj->p_cadInfo, p_cadValor );
	}
}

void SCadcConcatenarCad ( SCadenaConv * p_cadObj, SCadena * p_cadValor )
{
	if ( ES_VALIDO ( p_cadObj ) )
	{
		SCadConcatenar ( p_cadObj->p_cadInfo, p_cadValor );
	}
}

void SCadcCopiar ( SCadenaConv * p_cadObj, SCadenaConv * p_cadValor )
{
	if ( ES_VALIDO ( p_cadObj ) )
	{
		SCadCopiar ( p_cadObj->p_cadInfo, SCadcCadena ( p_cadValor ) );
	}
}

void SCadcConcatenar ( SCadenaConv * p_cadObj, SCadenaConv * p_cadValor )
{
	if ( ES_VALIDO ( p_cadObj ) )
	{
		SCadConcatenar ( p_cadObj->p_cadInfo, SCadcCadena ( p_cadValor ) );
	}
}

void SCadcCopiarCaracter ( SCadenaConv * p_cadObj, char cValor )
{
	if ( ES_VALIDO ( p_cadObj ) )
	{
		SCadCopiarCaracter ( p_cadObj->p_cadInfo, cValor );
	}
}

void SCadcConcatenarCaracter ( SCadenaConv * p_cadObj, char cValor )
{
	if ( ES_VALIDO ( p_cadObj ) )
	{
		SCadConcatenarCaracter ( p_cadObj->p_cadInfo, cValor );
	}
}

void SCadcCopiarEntero ( SCadenaConv * p_cadObj, int iValor )
{
	if ( ES_VALIDO ( p_cadObj ) )
	{
		SConvEstablecerValorEntero ( p_cadObj->p_convValores,  iValor );
		SCadCopiarLiteral ( p_cadObj->p_cadInfo, SConvCadena ( p_cadObj->p_convValores ) );
	}
}

void SCadcConcatenarEntero ( SCadenaConv * p_cadObj, int iValor )
{
	if ( ES_VALIDO ( p_cadObj ) )
	{
		SConvEstablecerValorEntero ( p_cadObj->p_convValores,  iValor );
		SCadConcatenarLiteral ( p_cadObj->p_cadInfo, SConvCadena ( p_cadObj->p_convValores ) );
	}
}

void SCadcCopiarEnteroLargo ( SCadenaConv * p_cadObj, long lValor )
{
	if ( ES_VALIDO ( p_cadObj ) )
	{
		SConvEstablecerValorEnteroLargo ( p_cadObj->p_convValores,  lValor );
		SCadCopiarLiteral ( p_cadObj->p_cadInfo, SConvCadena ( p_cadObj->p_convValores ) );
	}
}

void SCadcConcatenarEnteroLargo ( SCadenaConv * p_cadObj, long lValor )
{
	if ( ES_VALIDO ( p_cadObj ) )
	{
		SConvEstablecerValorEnteroLargo ( p_cadObj->p_convValores,  lValor );
		SCadConcatenarLiteral ( p_cadObj->p_cadInfo, SConvCadena ( p_cadObj->p_convValores ) );
	}
}

void SCadcCopiarEnteroSinSigno( SCadenaConv * p_cadObj, unsigned int uiValor )
{
	if ( ES_VALIDO ( p_cadObj ) )
	{
		SConvEstablecerValorEnteroSinSigno ( p_cadObj->p_convValores,  uiValor );
		SCadCopiarLiteral ( p_cadObj->p_cadInfo, SConvCadena ( p_cadObj->p_convValores ) );
	}
}

void SCadcConcatenarEnteroSinSigno ( SCadenaConv * p_cadObj, unsigned int uiValor )
{
	if ( ES_VALIDO ( p_cadObj ) )
	{
		SConvEstablecerValorEnteroSinSigno ( p_cadObj->p_convValores,  uiValor );
		SCadConcatenarLiteral ( p_cadObj->p_cadInfo, SConvCadena ( p_cadObj->p_convValores ) );
	}
}

void SCadcCopiarEnteroLargoSinSigno ( SCadenaConv * p_cadObj, unsigned long ulValor )
{
	if ( ES_VALIDO ( p_cadObj ) )
	{
		SConvEstablecerValorEnteroLargoSinSigno ( p_cadObj->p_convValores,  ulValor );
		SCadCopiarLiteral ( p_cadObj->p_cadInfo, SConvCadena ( p_cadObj->p_convValores ) );
	}
}

void SCadcConcatenarEnteroLargoSinSigno ( SCadenaConv * p_cadObj, unsigned long ulValor )
{
	if ( ES_VALIDO ( p_cadObj ) )
	{
		SConvEstablecerValorEnteroLargoSinSigno ( p_cadObj->p_convValores,  ulValor );
		SCadConcatenarLiteral ( p_cadObj->p_cadInfo, SConvCadena ( p_cadObj->p_convValores ) );
	}
}

void SCadcCopiarReal ( SCadenaConv * p_cadObj, float fValor )
{
	if ( ES_VALIDO ( p_cadObj ) )
	{
		SConvEstablecerValorReal ( p_cadObj->p_convValores,  fValor );
		SCadCopiarLiteral ( p_cadObj->p_cadInfo, SConvCadena ( p_cadObj->p_convValores ) );
	}
}

void SCadcConcatenarReal ( SCadenaConv * p_cadObj, float fValor )
{
	if ( ES_VALIDO ( p_cadObj ) )
	{
		SConvEstablecerValorReal ( p_cadObj->p_convValores,  fValor );
		SCadConcatenarLiteral ( p_cadObj->p_cadInfo, SConvCadena ( p_cadObj->p_convValores ) );
	}
}

void SCadcCopiarRealDoble ( SCadenaConv * p_cadObj, double dValor )
{
	if ( ES_VALIDO ( p_cadObj ) )
	{
		SConvEstablecerValorRealDoble ( p_cadObj->p_convValores,  dValor );
		SCadCopiarLiteral ( p_cadObj->p_cadInfo, SConvCadena ( p_cadObj->p_convValores ) );
	}
}

void SCadcConcatenarRealDoble ( SCadenaConv * p_cadObj, double dValor )
{
	if ( ES_VALIDO ( p_cadObj ) )
	{
		SConvEstablecerValorRealDoble ( p_cadObj->p_convValores,  dValor );
		SCadConcatenarLiteral ( p_cadObj->p_cadInfo, SConvCadena ( p_cadObj->p_convValores ) );
	}
}

void SCadcCopiarEnteroDobleLargo ( SCadenaConv * p_cadObj, long long llValor )
{
	if ( ES_VALIDO ( p_cadObj ) )
	{
		SConvEstablecerValorEnteroDobleLargo( p_cadObj->p_convValores,  llValor );
		SCadCopiarLiteral ( p_cadObj->p_cadInfo, SConvCadena ( p_cadObj->p_convValores ) );
	}
}

void SCadcConcatenarEnteroDobleLargo ( SCadenaConv * p_cadObj, long long llValor )
{
	if ( ES_VALIDO ( p_cadObj ) )
	{
		SConvEstablecerValorEnteroDobleLargo ( p_cadObj->p_convValores,  llValor );
		SCadConcatenarLiteral ( p_cadObj->p_cadInfo, SConvCadena ( p_cadObj->p_convValores ) );
	}
}


int SCadcCopiarConFormato ( SCadenaConv * p_cadObj, const char * p_cFormato, ... )
{
	int		iRes;
	va_list valArgumentos;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		if ( ES_VALIDO ( p_cFormato ) )
		{
			va_start ( valArgumentos,  p_cFormato );
			iRes = SCadcCopiarConFormatoExt ( p_cadObj, p_cFormato, valArgumentos );
			va_end ( valArgumentos );
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

int SCadcConcatenarConFormato ( SCadenaConv * p_cadObj, const char * p_cFormato, ... )
{
	int		iRes;
	va_list valArgumentos;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		if ( ES_VALIDO ( p_cFormato ) )
		{
			va_start ( valArgumentos,  p_cFormato );
			iRes = SCadcConcatenarConFormatoExt ( p_cadObj, p_cFormato, valArgumentos );
			va_end ( valArgumentos );
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

int SCadcCopiarConFormatoExt ( SCadenaConv * p_cadObj, const char * p_cFormato, va_list valArgumentos )
{
	int		iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = SCadCopiarConFormatoExt ( p_cadObj->p_cadInfo, p_cFormato, valArgumentos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadcConcatenarConFormatoExt ( SCadenaConv * p_cadObj, const char * p_cFormato, va_list valArgumentos )
{
	int		iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = SCadConcatenarConFormatoExt ( p_cadObj->p_cadInfo, p_cFormato, valArgumentos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadcEsNumerica ( SCadenaConv * p_cadObj )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		SConvEstablecerValor ( p_cadObj->p_convValores,  SCadValor ( p_cadObj->p_cadInfo ) );
		if ( ( SConvEsCadenaNumerica ( p_cadObj->p_convValores ) == 1 ) ||
			 ( SConvEsCadenaNumericaHexadecimal ( p_cadObj->p_convValores ) == 1 ) )
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

int SCadcEsNumericaEntera ( SCadenaConv * p_cadObj )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		SConvEstablecerValor ( p_cadObj->p_convValores,  SCadValor ( p_cadObj->p_cadInfo ) );
		if ( SConvEsCadenaNumericaEntera ( p_cadObj->p_convValores ) == 1 ) 
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

int SCadcEsNumericaReal ( SCadenaConv * p_cadObj )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		SConvEstablecerValor ( p_cadObj->p_convValores,  SCadValor ( p_cadObj->p_cadInfo ) );
		if ( SConvEsCadenaNumericaReal ( p_cadObj->p_convValores ) == 1 ) 
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

int SCadcEsNumericaHexadecimal ( SCadenaConv * p_cadObj )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		SConvEstablecerValor ( p_cadObj->p_convValores,  SCadValor ( p_cadObj->p_cadInfo ) );
		if ( SConvEsCadenaNumericaHexadecimal ( p_cadObj->p_convValores ) == 1 )
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

SCadenaConv * SCadcExtraer ( SCadenaConv * p_cadObj, int iPos, int iLong )
{
	SCadenaConv	*	p_cadSubcadena;	
	char *	p_cSubcadena;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		p_cSubcadena = CadExtraerExt ( SCadValorConstante ( p_cadObj->p_cadInfo ), iPos, iLong,  SCadMaxTam ( p_cadObj->p_cadInfo ) );
		if ( ES_VALIDO ( p_cSubcadena ) ) 
		{
			p_cadSubcadena = SCadcCrearLit ( p_cSubcadena );
			MemLiberar ( (void **) &p_cSubcadena );
		}
		else
		{
			p_cadSubcadena = NULL;
		}
	}
	else
	{
		p_cadSubcadena = NULL;
	}
	return ( p_cadSubcadena );
}

SCadenaConv * SCadcExtraerPrimeros ( SCadenaConv * p_cadObj, int iLong )
{
	return ( SCadcExtraer ( p_cadObj, 0, iLong ) );
}

SCadenaConv * SCadcExtraerUltimos ( SCadenaConv * p_cadObj, int iLong )
{
	if ( ES_VALIDO ( p_cadObj ) )
	{
		return ( SCadcExtraer ( p_cadObj, SCadLongitud ( p_cadObj->p_cadInfo ) - iLong, iLong ) );
	}
	else
	{
		return ( NULL );
	}
}

SCadenaConv * SCadcExtraerDesdeCaracter ( SCadenaConv * p_cadObj, char cVal )
{
	return ( SCadcExtraerDesdeCaracterExt ( p_cadObj, cVal, 1 ) );
}

SCadenaConv * SCadcExtraerHastaCaracter ( SCadenaConv * p_cadObj, char cVal )
{
	return ( SCadcExtraerHastaCaracterExt ( p_cadObj, cVal, 1 ) );
}

SCadenaConv * SCadcExtraerDesdeCaracterExt ( SCadenaConv * p_cadObj, char cVal, int iIncluir )
{
	SCadenaConv	*	p_cadSubcadena;	
	char *	p_cSubcadena;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		p_cSubcadena = CadExtraerDesdeCaracterExt ( SCadValorConstante ( p_cadObj->p_cadInfo ), cVal, iIncluir, 0,  SCadMaxTam ( p_cadObj->p_cadInfo ) );
		if ( ES_VALIDO ( p_cSubcadena ) ) 
		{
			p_cadSubcadena = SCadcCrearLit ( p_cSubcadena );
			MemLiberar ( (void **) &p_cSubcadena );
		}
		else
		{
			p_cadSubcadena = NULL;
		}
	}
	else
	{
		p_cadSubcadena = NULL;
	}
	return ( p_cadSubcadena );
}

SCadenaConv * SCadcExtraerHastaCaracterExt ( SCadenaConv * p_cadObj, char cVal, int iIncluir )
{
	SCadenaConv	*	p_cadSubcadena;	
	char *	p_cSubcadena;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		p_cSubcadena = CadExtraerHastaCaracterExt ( SCadValorConstante ( p_cadObj->p_cadInfo ), cVal, iIncluir, 0,  SCadMaxTam ( p_cadObj->p_cadInfo ) );
		if ( ES_VALIDO ( p_cSubcadena ) ) 
		{
			p_cadSubcadena = SCadcCrearLit ( p_cSubcadena );
			MemLiberar ( (void **) &p_cSubcadena );
		}
		else
		{
			p_cadSubcadena = NULL;
		}
	}
	else
	{
		p_cadSubcadena = NULL;
	}
	return ( p_cadSubcadena );
}

SCadenaConv * SCadcPalabra ( SCadenaConv * p_cadObj, int iPalabra )
{
	char * p_cPalabra;
	SCadenaConv * p_cadPalabra;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		p_cPalabra = CadPalabraExt ( SCadValorConstante ( p_cadObj->p_cadInfo ), iPalabra, 0,  SCadMaxTam ( p_cadObj->p_cadInfo ) );
		if ( ES_VALIDO ( p_cPalabra ) )
		{
			p_cadPalabra = SCadcCrearLit ( p_cPalabra );
			if ( ES_VALIDO ( p_cadPalabra ) )
			{
				SCadEliminarBlancosLaterales ( SCadcCadena ( p_cadPalabra ) );
			}
			MemLiberar ( (void **) &p_cPalabra );
		}
		else
		{
			p_cadPalabra = NULL;
		}
	}
	else
	{
		p_cadPalabra = NULL;
	}
	return ( p_cadPalabra );
}

SCadenaConv * SCadcPalabraSep ( SCadenaConv * p_cadObj, int iPalabra, char cSep )
{
	char * p_cPalabra;
	SCadenaConv * p_cadPalabra;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		p_cPalabra = CadPalabraSepExt ( SCadValorConstante ( p_cadObj->p_cadInfo ), iPalabra, cSep, 0,  SCadMaxTam ( p_cadObj->p_cadInfo ) );
		if ( ES_VALIDO ( p_cPalabra ) )
		{
			p_cadPalabra = SCadcCrearLit ( p_cPalabra );
			if ( ES_VALIDO ( p_cadPalabra ) )
			{
				SCadEliminarBlancosLaterales ( SCadcCadena ( p_cadPalabra ) );
			}
			MemLiberar ( (void **) &p_cPalabra );
		}
		else
		{
			p_cadPalabra = NULL;
		}
	}
	else
	{
		p_cadPalabra = NULL;
	}
	return ( p_cadPalabra );
}

SCadenaConv * SCadcPalabraExt ( SCadenaConv * p_cadObj, int iPalabra, int iSepararSignos )
{
	char * p_cPalabra;
	SCadenaConv * p_cadPalabra;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		p_cPalabra =  CadPalabraSepExt ( SCadValorConstante ( p_cadObj->p_cadInfo ), iPalabra, ' ', iSepararSignos,  SCadMaxTam ( p_cadObj->p_cadInfo ) );
		if ( ES_VALIDO ( p_cPalabra ) )
		{
			p_cadPalabra = SCadcCrearLit ( p_cPalabra );
			if ( ES_VALIDO ( p_cadPalabra ) )
			{
				SCadEliminarBlancosLaterales ( SCadcCadena ( p_cadPalabra ) );
			}
			MemLiberar ( (void **) &p_cPalabra );
		}
		else
		{
			p_cadPalabra = NULL;
		}
	}
	else
	{
		p_cadPalabra = NULL;
	}
	return ( p_cadPalabra );
}

SCadenaConv * SCadcPalabraSepExt ( SCadenaConv * p_cadObj, int iPalabra, char cSep, int iSepararSignos )
{
	char * p_cPalabra;
	SCadenaConv * p_cadPalabra;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		p_cPalabra = CadPalabraSepExt ( SCadValorConstante ( p_cadObj->p_cadInfo ), iPalabra, cSep, iSepararSignos,  SCadMaxTam ( p_cadObj->p_cadInfo ) );
		if ( ES_VALIDO ( p_cPalabra ) )
		{
			p_cadPalabra = SCadcCrearLit ( p_cPalabra );
			if ( ES_VALIDO ( p_cadPalabra ) )
			{
				SCadEliminarBlancosLaterales ( SCadcCadena ( p_cadPalabra ) );
			}
			MemLiberar ( (void **) &p_cPalabra );
		}
		else
		{
			p_cadPalabra = NULL;
		}
	}
	else
	{
		p_cadPalabra = NULL;
	}
	return ( p_cadPalabra );
}

SCadenaConv * SCadcDuplicar ( SCadenaConv * p_cadObj )
{
	SCadenaConv * p_cadCopia;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		p_cadCopia = SCadcCrearLit ( SCadValorConstante ( p_cadObj->p_cadInfo ) );
	}
	else
	{ 
		p_cadCopia = NULL;
	}
	return ( p_cadCopia );
}

char * SCadcDuplicarValor ( SCadenaConv * p_cadObj )
{
	char * p_cCopia;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		p_cCopia = SCadDuplicarValor ( p_cadObj->p_cadInfo );
	}
	else
	{ 
		p_cCopia = NULL;
	}
	return ( p_cCopia );
}

char * SCadcCadenaHexadecimal ( SCadenaConv * p_cadObj )
{
	char * p_cCopia;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		p_cCopia = SCadCadenaHexadecimal ( p_cadObj->p_cadInfo );
	}
	else
	{ 
		p_cCopia = NULL;
	}
	return ( p_cCopia );
}

int SCadcAsignarCadenaHexadecimal ( SCadenaConv * p_cadObj, const char * p_cValorHex )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = SCadAsignarCadenaHexadecimal ( p_cadObj->p_cadInfo, p_cValorHex );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadcExpander ( SCadenaConv * p_cadObj )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = SCadExpander ( p_cadObj->p_cadInfo );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadcExpanderCaracter ( SCadenaConv * p_cadObj, char cVal )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = SCadExpanderCaracter ( p_cadObj->p_cadInfo, cVal );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadcContraer ( SCadenaConv * p_cadObj )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = SCadContraer ( p_cadObj->p_cadInfo );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadcContraerCaracter ( SCadenaConv * p_cadObj, char cVal )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = SCadContraerCaracter ( p_cadObj->p_cadInfo, cVal );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadcEliminarBlancosLaterales ( SCadenaConv * p_cadObj )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = SCadEliminarBlancosLaterales ( p_cadObj->p_cadInfo );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadcEliminarBlancosIzq ( SCadenaConv * p_cadObj )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = SCadEliminarBlancosIzq ( p_cadObj->p_cadInfo );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadcEliminarBlancosDer ( SCadenaConv * p_cadObj )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = SCadEliminarBlancosDer ( p_cadObj->p_cadInfo );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadcFormatearBlancos ( SCadenaConv * p_cadObj )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = SCadFormatearBlancos ( p_cadObj->p_cadInfo );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadcContieneBlancos ( SCadenaConv * p_cadObj )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = SCadContieneBlancos ( p_cadObj->p_cadInfo );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadcContieneTabuladores ( SCadenaConv * p_cadObj )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = SCadContieneTabuladores ( p_cadObj->p_cadInfo );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadcContieneCaracteresNoImprimibles ( SCadenaConv * p_cadObj )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = SCadContieneCaracteresNoImprimibles ( p_cadObj->p_cadInfo );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadcContieneCaracteresNoAlfanumericos ( SCadenaConv * p_cadObj )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = SCadContieneCaracteresNoAlfanumericos ( p_cadObj->p_cadInfo );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadcContieneCaracteresNoEstandar ( SCadenaConv * p_cadObj )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = SCadContieneCaracteresNoEstandar ( p_cadObj->p_cadInfo );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadcEliminarCaracter ( SCadenaConv * p_cadObj, int iCar )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = SCadEliminarCaracter ( p_cadObj->p_cadInfo, iCar );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadcEliminarCaracteres ( SCadenaConv * p_cadObj, int iPosIni, int iNumCars )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = SCadEliminarCaracteres ( p_cadObj->p_cadInfo, iPosIni, iNumCars );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadcEliminarPrimerosCaracteres ( SCadenaConv * p_cadObj, int iNumCars )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = SCadEliminarPrimerosCaracteres ( p_cadObj->p_cadInfo, iNumCars );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadcEliminarUltimosCaracteres ( SCadenaConv * p_cadObj, int iNumCars )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = SCadEliminarUltimosCaracteres ( p_cadObj->p_cadInfo, iNumCars);
	}
	else
	{iRes = 0;
	}
	return ( iRes );
}

int SCadcEliminarApariciones ( SCadenaConv * p_cadObj, SCadenaConv * p_cadValor )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = SCadEliminarApariciones ( p_cadObj->p_cadInfo, SCadcCadena ( p_cadValor ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadcEliminarAparicionesCad ( SCadenaConv * p_cadObj, SCadena * p_cadValor )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = SCadEliminarApariciones ( p_cadObj->p_cadInfo, p_cadValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadcEliminarAparicionesCaracter ( SCadenaConv * p_cadObj, char cCar )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = SCadEliminarAparicionesCaracter ( p_cadObj->p_cadInfo, cCar );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadcEliminarAparicionesLit ( SCadenaConv * p_cadObj, const char * p_cValor )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = SCadEliminarAparicionesLiteral ( p_cadObj->p_cadInfo, p_cValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadcEliminarBlancos ( SCadenaConv * p_cadObj )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = SCadEliminarBlancos ( p_cadObj->p_cadInfo );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadcEliminarTabuladores ( SCadenaConv * p_cadObj )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = SCadEliminarTabuladores ( p_cadObj->p_cadInfo );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadcEliminarCaracteresNoImprimibles ( SCadenaConv * p_cadObj )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = SCadEliminarCaracteresNoImprimibles ( p_cadObj->p_cadInfo );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadcEliminarCaracteresNoAlfanumericos ( SCadenaConv * p_cadObj )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = SCadEliminarCaracteresNoAlfanumericos ( p_cadObj->p_cadInfo );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadcEliminarCaracteresNoEstandar ( SCadenaConv * p_cadObj )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = SCadEliminarCaracteresNoEstandar ( p_cadObj->p_cadInfo );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadcAlinearIzq ( SCadenaConv * p_cadObj )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = SCadAlinearIzq ( p_cadObj->p_cadInfo );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadcAlinearDer ( SCadenaConv * p_cadObj )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = SCadAlinearDer ( p_cadObj->p_cadInfo );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadcAlinearIzqRellenando ( SCadenaConv * p_cadObj, char cVal )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = SCadAlinearIzqRellenando ( p_cadObj->p_cadInfo, cVal );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadcAlinearDerRellenando ( SCadenaConv * p_cadObj, char cVal )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = SCadAlinearDerRellenando ( p_cadObj->p_cadInfo, cVal );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadcInvertir ( SCadenaConv * p_cadObj )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = SCadInvertir ( p_cadObj->p_cadInfo );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadcConvertirAMayusculas ( SCadenaConv * p_cadObj )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = SCadInvertir ( p_cadObj->p_cadInfo );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadcConvertirAMinusculas ( SCadenaConv * p_cadObj )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = SCadInvertir ( p_cadObj->p_cadInfo );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadcConvertirACapitales ( SCadenaConv * p_cadObj )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = SCadConvertirACapitales ( p_cadObj->p_cadInfo );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadcTraducirLetrasConSigno ( SCadenaConv * p_cadObj )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = SCadTraducirLetrasConSigno ( p_cadObj->p_cadInfo );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadcCorrespondeAValorNulo ( SCadenaConv * p_cadObj )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = SCadCorrespondeAValorNulo ( p_cadObj->p_cadInfo );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadcContieneValoresNulos ( SCadenaConv * p_cadObj )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = SCadContieneValoresNulos ( p_cadObj->p_cadInfo );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadcEliminarValoresNulos ( SCadenaConv * p_cadObj )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = SCadEliminarValoresNulos ( p_cadObj->p_cadInfo );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadcExisteCad ( SCadenaConv * p_cadObj, SCadena * p_cadValor )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = SCadExiste ( p_cadObj->p_cadInfo, p_cadValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadcExiste ( SCadenaConv * p_cadObj, SCadenaConv * p_cadValor )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = SCadExiste ( p_cadObj->p_cadInfo, SCadcCadena ( p_cadValor ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadcBuscarCad ( SCadenaConv * p_cadObj, SCadena * p_cadValor, int iPosIni )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = SCadBuscar ( p_cadObj->p_cadInfo, p_cadValor, iPosIni );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadcBuscar ( SCadenaConv * p_cadObj, SCadenaConv * p_cadValor, int iPosIni )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = SCadBuscar ( p_cadObj->p_cadInfo, SCadcCadena ( p_cadValor ), iPosIni );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadcBuscarDescCad ( SCadenaConv * p_cadObj, SCadena * p_cadValor, int iPosIni )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = SCadBuscarDesc ( p_cadObj->p_cadInfo, p_cadValor, iPosIni );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadcBuscarDesc ( SCadenaConv * p_cadObj, SCadenaConv * p_cadValor, int iPosIni )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = SCadBuscarDesc ( p_cadObj->p_cadInfo, SCadcCadena ( p_cadValor ), iPosIni );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadcContarCad ( SCadenaConv * p_cadObj, SCadena * p_cadValor )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = SCadContar ( p_cadObj->p_cadInfo, p_cadValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadcContar ( SCadenaConv * p_cadObj, SCadenaConv * p_cadValor )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = SCadContar ( p_cadObj->p_cadInfo, SCadcCadena ( p_cadValor ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadcReemplazarCad ( SCadenaConv * p_cadObj, SCadena * p_cadValor, SCadena * p_cadReemp )
{
	return ( SCadcReemplazarCadExt ( p_cadObj, p_cadValor, p_cadReemp, 0 ) );
}

int SCadcReemplazar ( SCadenaConv * p_cadObj, SCadenaConv * p_cadValor, SCadenaConv * p_cadReemp )
{
	return ( SCadcReemplazarExt ( p_cadObj, p_cadValor, p_cadReemp, 0 ) );
}

int SCadcReemplazarCadExt ( SCadenaConv * p_cadObj, SCadena * p_cadValor, SCadena * p_cadReemp, int iExpander )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = SCadReemplazarExt ( p_cadObj->p_cadInfo, p_cadValor, p_cadReemp, iExpander );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadcReemplazarExt ( SCadenaConv * p_cadObj, SCadenaConv * p_cadValor, SCadenaConv * p_cadReemp, int iExpander )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = SCadReemplazarExt ( p_cadObj->p_cadInfo, SCadcCadena ( p_cadValor ), SCadcCadena ( p_cadReemp ), iExpander );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadcExisteCaracter ( SCadenaConv * p_cadObj, char cVal )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = SCadExisteCaracter ( p_cadObj->p_cadInfo, cVal );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadcBuscarCaracter ( SCadenaConv * p_cadObj, char cVal, int iPosIni )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = SCadBuscarCaracter ( p_cadObj->p_cadInfo, cVal, iPosIni );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadcBuscarCaracterDesc ( SCadenaConv * p_cadObj, char cVal, int iPosIni )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = SCadBuscarCaracterDesc ( p_cadObj->p_cadInfo, cVal, iPosIni );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadcContarCaracter ( SCadenaConv * p_cadObj, char cVal )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = SCadContarCaracter ( p_cadObj->p_cadInfo, cVal );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadcReemplazarCaracter ( SCadenaConv * p_cadObj, char cVal, char cReemp )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = SCadReemplazarCaracter ( p_cadObj->p_cadInfo, cVal, cReemp );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadcBuscarCaracterDiferente ( SCadenaConv * p_cadObj, char cVal, int iPosIni )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = SCadBuscarCaracterDiferente ( p_cadObj->p_cadInfo, cVal, iPosIni );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadcBuscarCaracterDiferenteDesc ( SCadenaConv * p_cadObj, char cVal, int iPosIni )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = SCadBuscarCaracterDiferenteDesc ( p_cadObj->p_cadInfo, cVal, iPosIni );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadcExisteLit ( SCadenaConv * p_cadObj, const char * p_cValor )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = SCadExisteLiteral ( p_cadObj->p_cadInfo, p_cValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadcBuscarLit ( SCadenaConv * p_cadObj, const char * p_cValor, int iPosIni )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = SCadBuscarLiteral ( p_cadObj->p_cadInfo, p_cValor, iPosIni );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadcBuscarLitDesc ( SCadenaConv * p_cadObj, const char * p_cValor, int iPosIni )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = SCadBuscarLiteralDesc ( p_cadObj->p_cadInfo, p_cValor, iPosIni );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadcContarLit ( SCadenaConv * p_cadObj, const char * p_cValor )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = SCadContarLiteral ( p_cadObj->p_cadInfo, p_cValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadcReemplazarLit ( SCadenaConv * p_cadObj, const char * p_cValor, const char * p_cReemp )
{
	return ( SCadcReemplazarLitExt ( p_cadObj, p_cValor, p_cReemp, 0 ) );
}

int SCadcReemplazarLitExt ( SCadenaConv* p_cadObj, const char* p_cValor, const char* p_cReemp, int iExpander )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = SCadReemplazarLiteralExt ( p_cadObj->p_cadInfo, p_cValor, p_cReemp, iExpander );
	}
	else
	{
		iRes = 0;
	}
	return (iRes);
}

int SCadcEsIgual ( SCadenaConv * p_cadObj, SCadenaConv * p_cadValor )
{
	return ( SCadcEsIgualCad ( p_cadObj, SCadcCadena ( p_cadValor ) ) );
}

int SCadcEsMenor ( SCadenaConv * p_cadObj, SCadenaConv * p_cadValor )
{
	return ( SCadcEsMenorCad ( p_cadObj, SCadcCadena ( p_cadValor ) ) );
}

int SCadcEsMayor ( SCadenaConv * p_cadObj, SCadenaConv * p_cadValor )
{
	return ( SCadcEsMayorCad ( p_cadObj, SCadcCadena ( p_cadValor ) ) );
}

int SCadcEsDiferente ( SCadenaConv * p_cadObj, SCadenaConv * p_cadValor )
{
	return ( SCadcEsDiferenteCad ( p_cadObj, SCadcCadena ( p_cadValor ) ) );
}

int SCadcEsIgualCad ( SCadenaConv * p_cadObj, SCadena * p_cadValor )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = SCadEsIgual ( p_cadObj->p_cadInfo, p_cadValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadcEsMenorCad ( SCadenaConv * p_cadObj, SCadena * p_cadValor )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = SCadEsMenor ( p_cadObj->p_cadInfo, p_cadValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadcEsMayorCad ( SCadenaConv * p_cadObj, SCadena * p_cadValor )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = SCadEsMayor ( p_cadObj->p_cadInfo, p_cadValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadcEsDiferenteCad ( SCadenaConv * p_cadObj, SCadena * p_cadValor )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = SCadEsDiferente ( p_cadObj->p_cadInfo, p_cadValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadcEsIgualLit ( SCadenaConv * p_cadObj, const char * p_cValor )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = SCadEsIgualLiteral ( p_cadObj->p_cadInfo, p_cValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadcEsMenorLit ( SCadenaConv * p_cadObj, const char * p_cValor )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = SCadEsMenorLiteral ( p_cadObj->p_cadInfo, p_cValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadcEsMayorLit ( SCadenaConv * p_cadObj, const char * p_cValor )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = SCadEsMayorLiteral ( p_cadObj->p_cadInfo, p_cValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadcEsDiferenteLit ( SCadenaConv * p_cadObj, const char * p_cValor )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = SCadEsDiferenteLiteral ( p_cadObj->p_cadInfo, p_cValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadcEmpiezaPor ( SCadenaConv * p_cadObj, SCadenaConv * p_cadValor )
{
	return ( SCadcEmpiezaPorCad ( p_cadObj, SCadcCadena ( p_cadValor ) ) );
}

int SCadcEmpiezaPorCad ( SCadenaConv * p_cadObj, SCadena * p_cadValor )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = SCadEmpiezaPor ( p_cadObj->p_cadInfo, p_cadValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadcEmpiezaPorLit ( SCadenaConv * p_cadObj, const char * p_cValor )	
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = SCadEmpiezaPorLiteral ( p_cadObj->p_cadInfo, p_cValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadcAcabaPor ( SCadenaConv * p_cadObj, SCadenaConv * p_cadValor )
{
	return ( SCadcAcabaPorCad ( p_cadObj, SCadcCadena ( p_cadValor ) ) );
}

int SCadcAcabaPorCad ( SCadenaConv * p_cadObj, SCadena * p_cadValor )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = SCadAcabaPor ( p_cadObj->p_cadInfo, p_cadValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCadcAcabaPorLit ( SCadenaConv * p_cadObj, const char * p_cValor )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		iRes = SCadAcabaPorLiteral ( p_cadObj->p_cadInfo, p_cValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}


