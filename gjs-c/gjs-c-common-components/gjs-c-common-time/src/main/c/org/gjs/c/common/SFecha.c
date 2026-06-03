
#include "SFecha.h"

#include "TiempoNumerico.h"
#include "TiempoSistema.h"
#include "Fechas.h"
#include "TiempoConfig.h"



SFecha * SFecCrearDef ()
{
	SFecha * p_fecObj;
	
	p_fecObj = (SFecha *) MemReservar ( sizeof ( SFecha ) );
	if ( ES_VALIDO ( p_fecObj ) )
	{
		SFecEstablecerValorDeHoy ( p_fecObj );
	}
	return ( p_fecObj );
}

SFecha * SFecCrear ( long lValor )
{
	SFecha * p_fecObj;
	
	p_fecObj = (SFecha *) MemReservar ( sizeof ( SFecha ) );
	if ( ES_VALIDO ( p_fecObj ) )
	{
		SFecEstablecer ( p_fecObj, lValor );
	}
	return ( p_fecObj );
}

SFecha * SFecCrearLit ( const char * p_cValor )
{
	SFecha * p_fecObj;
	
	p_fecObj = (SFecha *) MemReservar ( sizeof ( SFecha ) );
	if ( ES_VALIDO ( p_fecObj ) )
	{
		SFecEstablecerLit ( p_fecObj, p_cValor );
	}
	return ( p_fecObj );
}

void SFecDestruir ( SFecha ** p_p_fecObj )
{
	SFecha * p_fecObj;
	
	if ( ES_VALIDO ( p_p_fecObj ) )
	{
		p_fecObj = *p_p_fecObj;

		if ( ES_VALIDO ( p_fecObj ) )
		{
			MemLiberar ( (void **) p_p_fecObj );
		}
	}
}

int SFecEstablecer ( SFecha * p_fecObj, long lValor )
{
	int iRes;

	if ( ES_VALIDO ( p_fecObj ) )
	{
		if ( FecFormEsValida ( lValor ) == 1 )
		{
			iRes = 1;
			p_fecObj->lValor = lValor;
		}
		else
		{
			iRes = 0;
			p_fecObj->lValor = 0;
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SFecEstablecerLit ( SFecha * p_fecObj, const char * p_cValor )
{
	long lValor;
	int	 iRes;

	if ( ES_VALIDO ( p_fecObj ) )
	{
		lValor = ConvCadenaAEnteroLargo ( p_cValor );
		if ( lValor > 0 )
		{
			iRes = SFecEstablecer ( p_fecObj, lValor );
		}
		else
		{
			iRes = SFecEstablecer ( p_fecObj, (long) 0 );
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SFecTieneValor ( SFecha * p_fecObj )
{
	int iRes;

	if ( ES_VALIDO ( p_fecObj ) )
	{
		if ( p_fecObj->lValor > 0 )
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

int SFecEsValida ( SFecha * p_fecObj )
{
	int iRes;

	if ( ES_VALIDO ( p_fecObj ) )
	{
		if ( FecFormEsValida ( p_fecObj->lValor ) == 1 )
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

long SFecValor ( SFecha * p_fecObj )
{
	long lRes;

	if ( ES_VALIDO ( p_fecObj ) )
	{
		lRes = p_fecObj->lValor;
	}
	else
	{
		lRes = 0;
	}
	return ( lRes );
}

double SFecValorNumerico ( SFecha * p_fecObj )
{
	double dRes;

	if ( ES_VALIDO ( p_fecObj ) )
	{
		dRes = FecFormObtenerValor ( p_fecObj->lValor );
	}
	else
	{
		dRes = 0.0;
	}
	return ( dRes );
}

char * SFecFecha ( SFecha * p_fecObj )
{
	return ( SFecFechaForm ( p_fecObj, FEC_FORMATO_NORMAL ) );
}

char * SFecFechaForm ( SFecha * p_fecObj, int iFormato )
{
	int		iTam;
	char *	p_cRes;

	if ( ES_VALIDO ( p_fecObj ) )
	{
		if ( iFormato == FEC_FORMATO_NUMERICO )
		{
			iTam = FEC_TAM_FECHA_FORMATO_NUM;
			p_cRes = CadCrear ( iTam );
			if ( ES_VALIDO ( p_cRes ) )
			{
				CadCopiarConFormato ( p_cRes, FEC_FORMATO_FECHA_NUM, SFecAAAA ( p_fecObj ), SFecMM ( p_fecObj ), SFecDD ( p_fecObj ) );
			}
		}
		else
		{
			iTam = FEC_TAM_FECHA_FORMATO_DEF;
			p_cRes = CadCrear ( iTam );
			if ( ES_VALIDO ( p_cRes ) )
			{
				CadCopiarConFormato ( p_cRes, FEC_FORMATO_FECHA_DEF, SFecAAAA ( p_fecObj ), SFecMM ( p_fecObj ), SFecDD ( p_fecObj ) );
			}
		}
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

int SFecAAAA ( SFecha * p_fecObj )
{
	int iRes;

	if ( ES_VALIDO ( p_fecObj ) )
	{
		iRes = FecFormAnos ( p_fecObj->lValor );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int SFecMM ( SFecha * p_fecObj )
{
	int iRes;

	if ( ES_VALIDO ( p_fecObj ) )
	{
		iRes = FecFormMeses ( p_fecObj->lValor );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int SFecDD ( SFecha * p_fecObj )
{
	int iRes;

	if ( ES_VALIDO ( p_fecObj ) )
	{
		iRes = FecFormDias ( p_fecObj->lValor );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

void SFecEstablecerValorDeHoy ( SFecha * p_fecObj )
{
	if ( ES_VALIDO ( p_fecObj ) )
	{
		p_fecObj->lValor = TiempoHoy ();
	}
}

int SFecEsIgual ( SFecha * p_fecObj, SFecha * p_fecValor )
{
	int iRes;

	if ( ES_VALIDO ( p_fecObj ) && ES_VALIDO ( p_fecValor ) )
	{
		iRes = SFecEsIgualValor ( p_fecObj, SFecValor ( p_fecValor ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SFecEsMenor ( SFecha * p_fecObj, SFecha * p_fecValor )
{
	int iRes;

	if ( ES_VALIDO ( p_fecObj ) && ES_VALIDO ( p_fecValor ) )
	{
		iRes = SFecEsMenorValor ( p_fecObj, SFecValor ( p_fecValor ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SFecEsMayor ( SFecha * p_fecObj, SFecha * p_fecValor )
{
	int iRes;

	if ( ES_VALIDO ( p_fecObj ) && ES_VALIDO ( p_fecValor ) )
	{
		iRes = SFecEsMayorValor ( p_fecObj, SFecValor ( p_fecValor ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SFecEsDiferente ( SFecha * p_fecObj, SFecha * p_fecValor )
{
	int iRes;

	if ( ES_VALIDO ( p_fecObj ) && ES_VALIDO ( p_fecValor ) )
	{
		iRes = SFecEsDiferenteValor ( p_fecObj, SFecValor ( p_fecValor ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SFecEsIgualLit ( SFecha * p_fecObj, const char * p_cValor )
{
	long lValor;
	int iRes;

	if ( ES_VALIDO ( p_fecObj ) && ES_VALIDO ( p_cValor ) )
	{
		lValor = ConvCadenaAEnteroLargo ( p_cValor );
		iRes = SFecEsIgualValor ( p_fecObj, lValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SFecEsMenorLit ( SFecha * p_fecObj, const char * p_cValor )
{
	long lValor;
	int iRes;

	if ( ES_VALIDO ( p_fecObj ) && ES_VALIDO ( p_cValor ) )
	{
		lValor = ConvCadenaAEnteroLargo ( p_cValor );
		iRes = SFecEsMenorValor ( p_fecObj, lValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SFecEsMayorLit ( SFecha * p_fecObj, const char * p_cValor )
{
	long lValor;
	int iRes;

	if ( ES_VALIDO ( p_fecObj ) && ES_VALIDO ( p_cValor ) )
	{
		lValor = ConvCadenaAEnteroLargo ( p_cValor );
		iRes = SFecEsMayorValor ( p_fecObj, lValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SFecEsDiferenteLit ( SFecha * p_fecObj, const char * p_cValor )
{
	long lValor;
	int iRes;

	if ( ES_VALIDO ( p_fecObj ) && ES_VALIDO ( p_cValor ) )
	{
		lValor = ConvCadenaAEnteroLargo ( p_cValor );
		iRes = SFecEsDiferenteValor ( p_fecObj, lValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SFecEsIgualValor ( SFecha * p_fecObj, long lValor )
{
	int iRes;
	
	if ( ES_VALIDO ( p_fecObj ) )
	{
		if ( SFecValorNumerico ( p_fecObj ) == FecFormObtenerValor ( lValor ) )
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

int SFecEsMenorValor ( SFecha * p_fecObj, long lValor )
{
	int iRes;
	
	if ( ES_VALIDO ( p_fecObj ) )
	{
		if ( SFecValorNumerico ( p_fecObj ) < FecFormObtenerValor ( lValor ) )
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

int SFecEsMayorValor ( SFecha * p_fecObj, long lValor )
{
	int iRes;
	
	if ( ES_VALIDO ( p_fecObj ) )
	{
		if ( SFecValorNumerico ( p_fecObj ) > FecFormObtenerValor ( lValor ) )
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

int SFecEsDiferenteValor ( SFecha * p_fecObj, long lValor )
{
	int iRes;
	
	if ( ES_VALIDO ( p_fecObj ) )
	{
		if ( SFecValorNumerico ( p_fecObj ) != FecFormObtenerValor ( lValor ) )
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

long SFecDiferencia ( SFecha * p_fecObj, SFecha * p_fecValor )
{
	return ( SFecDiferenciaValor ( p_fecObj, SFecValor ( p_fecValor ) ) );
}

long SFecDiferenciaLit ( SFecha * p_fecObj, const char * p_cValor )
{
	long lValor;

	lValor = ConvCadenaAEnteroLargo ( p_cValor );
	return ( SFecDiferenciaValor ( p_fecObj, lValor ) );
}

long SFecDiferenciaValor ( SFecha * p_fecObj, long lValor )
{
	return ( SFecValor ( p_fecObj ) - lValor );
}


