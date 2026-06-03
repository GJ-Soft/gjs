#include "SHora.h"

#include "Horas.h"
#include "TiempoSistema.h"
#include "TiempoConfig.h"

SHora * SHorCrearDef ()
{
	SHora * p_horObj;
	
	p_horObj = (SHora *) MemReservar ( sizeof ( SHora ) );
	if ( ES_VALIDO ( p_horObj ) )
	{
		SHorEstablecerValorDeAhora ( p_horObj );
	}
	return ( p_horObj );
}

SHora * SHorCrear ( long lValor )
{
	SHora * p_horObj;
	
	p_horObj = (SHora *) MemReservar ( sizeof ( SHora ) );
	if ( ES_VALIDO ( p_horObj ) )
	{
		SHorEstablecer ( p_horObj, lValor );
	}
	return ( p_horObj );
}

SHora * SHorCrearLit ( const char * p_cValor )
{
	SHora * p_horObj;
	
	p_horObj = (SHora *) MemReservar ( sizeof ( SHora ) );
	if ( ES_VALIDO ( p_horObj ) )
	{
		SHorEstablecerLit ( p_horObj, p_cValor );
	}
	return ( p_horObj );
}

void SHorDestruir ( SHora ** p_p_horObj )
{
	SHora * p_horObj;
	
	if ( ES_VALIDO ( p_p_horObj ) )
	{
		p_horObj = *p_p_horObj;

		if ( ES_VALIDO ( p_horObj ) )
		{
			MemLiberar ( (void **) p_p_horObj );
		}
	}
}

int SHorEstablecer ( SHora * p_horObj, long lValor )
{
	int iRes;

	if ( ES_VALIDO ( p_horObj ) )
	{
		if ( HorFormEsValida ( lValor ) == 1 )
		{
			iRes = 1;
			p_horObj->lValor = lValor;
		}
		else
		{
			iRes = 0;
			p_horObj->lValor = 0;
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SHorEstablecerLit ( SHora * p_horObj, const char * p_cValor )
{
	long lValor;
	int	 iRes;

	if ( ES_VALIDO ( p_horObj ) )
	{
		lValor = ConvCadenaAEnteroLargo ( p_cValor );
		if ( lValor > 0 )
		{
			iRes = SHorEstablecer ( p_horObj, lValor );
		}
		else
		{
			iRes = SHorEstablecer ( p_horObj, (long) 0 );
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SHorTieneValor ( SHora * p_horObj )
{
	int iRes;

	if ( ES_VALIDO ( p_horObj ) )
	{
		if ( p_horObj->lValor > 0 )
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

int SHorEsValida ( SHora * p_horObj )
{
	int iRes;

	if ( ES_VALIDO ( p_horObj ) )
	{
		iRes = HorFormEsValida ( p_horObj->lValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SHorHH ( SHora * p_horObj )
{
	int	iRes;

	if ( ES_VALIDO ( p_horObj ) )
	{
		iRes = HorFormHoras ( p_horObj->lValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SHorMI ( SHora * p_horObj )
{
	int	iRes;

	if ( ES_VALIDO ( p_horObj ) )
	{
		iRes = HorFormMinutos ( p_horObj->lValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SHorSS ( SHora * p_horObj )
{
	int	iRes;

	if ( ES_VALIDO ( p_horObj ) )
	{
		iRes = HorFormSegundos ( p_horObj->lValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

long SHorValor ( SHora * p_horObj )
{
	long lRes;

	if ( ES_VALIDO ( p_horObj ) )
	{
		lRes = p_horObj->lValor;
	}
	else
	{
		lRes = 0;
	}
	return ( lRes );
}

double SHorValorNumerico ( SHora * p_horObj )
{
	double dRes;

	if ( ES_VALIDO ( p_horObj ) )
	{
		dRes = HorFormObtenerValor ( p_horObj->lValor );
	}
	else
	{
		dRes = 0.0;
	}
	return ( dRes );
}

char * SHorHora ( SHora * p_horObj )
{
	return ( SHorHoraForm ( p_horObj, FEC_FORMATO_NORMAL ) );
}

char * SHorHoraForm ( SHora * p_horObj, int iFormato )
{
	int		iTam;
	char *	p_cRes;

	if ( ES_VALIDO ( p_horObj ) )
	{
		if ( iFormato == FEC_FORMATO_NUMERICO )
		{
			iTam = FEC_TAM_HORA_FORMATO_NUM;
			p_cRes = CadCrear ( iTam );
			if ( ES_VALIDO ( p_cRes ) )
			{
				CadCopiarConFormato ( p_cRes, FEC_FORMATO_HORA_NUM, SHorHH ( p_horObj ), SHorMI ( p_horObj ), SHorSS ( p_horObj ) );
			}
		}
		else
		{
			iTam = FEC_TAM_HORA_FORMATO_DEF;
			p_cRes = CadCrear ( iTam );
			if ( ES_VALIDO ( p_cRes ) )
			{
				CadCopiarConFormato ( p_cRes, FEC_FORMATO_HORA_DEF, SHorHH ( p_horObj ), SHorMI ( p_horObj ), SHorSS ( p_horObj ) );
			}
		}
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

void SHorEstablecerValorDeAhora ( SHora * p_horObj )
{
	if ( ES_VALIDO ( p_horObj ) )
	{
		p_horObj->lValor =  TiempoAhora ();
	}
}

int SHorEsIgual ( SHora * p_horObj, SHora * p_horValor )
{
	int iRes;

	if ( ES_VALIDO ( p_horObj ) && ES_VALIDO ( p_horValor ) )
	{
		iRes = SHorEsIgualValor ( p_horObj, SHorValor ( p_horValor ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SHorEsMenor ( SHora * p_horObj, SHora * p_horValor )
{
	int iRes;

	if ( ES_VALIDO ( p_horObj ) && ES_VALIDO ( p_horValor ) )
	{
		iRes = SHorEsMenorValor ( p_horObj, SHorValor ( p_horValor ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SHorEsMayor ( SHora * p_horObj, SHora * p_horValor )
{
	int iRes;

	if ( ES_VALIDO ( p_horObj ) && ES_VALIDO ( p_horValor ) )
	{
		iRes = SHorEsMayorValor ( p_horObj, SHorValor ( p_horValor ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SHorEsDiferente ( SHora * p_horObj, SHora * p_horValor )
{
	int iRes;

	if ( ES_VALIDO ( p_horObj ) && ES_VALIDO ( p_horValor ) )
	{
		iRes = SHorEsDiferenteValor ( p_horObj, SHorValor ( p_horValor ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SHorEsIgualLit ( SHora * p_horObj, const char * p_cValor )
{
	long lValor;
	int iRes;

	if ( ES_VALIDO ( p_horObj ) && ES_VALIDO ( p_cValor ) )
	{
		lValor = ConvCadenaAEnteroLargo ( p_cValor );
		iRes = SHorEsIgualValor ( p_horObj, lValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SHorEsMenorLit ( SHora * p_horObj, const char * p_cValor )
{
	long lValor;
	int iRes;

	if ( ES_VALIDO ( p_horObj ) && ES_VALIDO ( p_cValor ) )
	{
		lValor = ConvCadenaAEnteroLargo ( p_cValor );
		iRes = SHorEsMenorValor ( p_horObj, lValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SHorEsMayorLit ( SHora * p_horObj, const char * p_cValor )
{
	long lValor;
	int iRes;

	if ( ES_VALIDO ( p_horObj ) && ES_VALIDO ( p_cValor ) )
	{
		lValor = ConvCadenaAEnteroLargo ( p_cValor );
		iRes = SHorEsMayorValor ( p_horObj, lValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SHorEsDiferenteLit ( SHora * p_horObj, const char * p_cValor )
{
	long lValor;
	int iRes;

	if ( ES_VALIDO ( p_horObj ) && ES_VALIDO ( p_cValor ) )
	{
		lValor = ConvCadenaAEnteroLargo ( p_cValor );
		iRes = SHorEsDiferenteValor ( p_horObj, lValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SHorEsIgualValor ( SHora * p_horObj, long lValor )
{
	int iRes;
	
	if ( ES_VALIDO ( p_horObj ) )
	{
		if ( SHorValorNumerico ( p_horObj ) == HorFormObtenerValor ( lValor ) )
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

int SHorEsMenorValor ( SHora * p_horObj, long lValor )
{
	int iRes;
	
	if ( ES_VALIDO ( p_horObj ) )
	{
		if ( SHorValorNumerico ( p_horObj ) < HorFormObtenerValor ( lValor ) )
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

int SHorEsMayorValor ( SHora * p_horObj, long lValor )
{
	int iRes;
	
	if ( ES_VALIDO ( p_horObj ) )
	{
		if ( SHorValorNumerico ( p_horObj ) > HorFormObtenerValor ( lValor ) )
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

int SHorEsDiferenteValor ( SHora * p_horObj, long lValor )
{
	int iRes;
	
	if ( ES_VALIDO ( p_horObj ) )
	{
		if ( SHorValorNumerico ( p_horObj ) != HorFormObtenerValor ( lValor ) )
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

long SHorDiferencia ( SHora * p_horObj, SHora * p_horValor )
{
	return ( SHorDiferenciaValor ( p_horObj, SHorValor ( p_horValor ) ) );
}

long SHorDiferenciaLit ( SHora * p_horObj, const char * p_cValor )
{
	long lValor;

	lValor = ConvCadenaAEnteroLargo ( p_cValor );
	return ( SHorDiferenciaValor ( p_horObj, lValor ) );
}

long SHorDiferenciaValor ( SHora * p_horObj, long lValor )
{
	return ( SHorValor ( p_horObj ) - lValor );
}



