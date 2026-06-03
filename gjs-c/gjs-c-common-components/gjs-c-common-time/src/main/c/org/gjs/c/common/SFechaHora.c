#include "SFechaHora.h"

#include "TiempoNumerico.h"
#include "TiempoSistema.h"
#include "TiempoConfig.h"

SFechaHora * SFecHorCrearDef ()
{
	SFechaHora * p_fecObj;
	
	p_fecObj = (SFechaHora *) MemReservar ( sizeof ( SFechaHora ) );
	if ( ES_VALIDO ( p_fecObj ) )
	{
		SFecHorEstablecerValorDeAhora ( p_fecObj );
	}
	return ( p_fecObj );
}

SFechaHora * SFecHorCrearFecha ( SFecha * p_fecValor )
{
	SFechaHora * p_fecObj;
	
	p_fecObj = (SFechaHora *) MemReservar ( sizeof ( SFechaHora ) );
	if ( ES_VALIDO ( p_fecObj ) )
	{
		SFecHorEstablecer ( p_fecObj, TmpFormConstruir ( SFecValor ( p_fecValor ), 0 ) );
	}
	return ( p_fecObj );
}

SFechaHora * SFecHorCrearFechaHora ( SFecha * p_fecValor, SHora * p_horValor )
{
	SFechaHora * p_fecObj;
	
	p_fecObj = (SFechaHora *) MemReservar ( sizeof ( SFechaHora ) );
	if ( ES_VALIDO ( p_fecObj ) )
	{
		SFecHorEstablecer ( p_fecObj, TmpFormConstruir ( SFecValor ( p_fecValor ), SHorValor ( p_horValor ) ) );
	}
	return ( p_fecObj );
}

SFechaHora * SFecHorCrear ( double dValor )
{
	SFechaHora * p_fecObj;
	
	p_fecObj = (SFechaHora *) MemReservar ( sizeof ( SFechaHora ) );
	if ( ES_VALIDO ( p_fecObj ) )
	{
		SFecHorEstablecer ( p_fecObj, dValor );
	}
	return ( p_fecObj );
}

SFechaHora * SFecHorCrearFecHor ( long lFecha, long lHora )
{
	SFechaHora * p_fecObj;

	p_fecObj = ( SFechaHora * ) MemReservar ( sizeof ( SFechaHora ) );
	if ( ES_VALIDO ( p_fecObj ) )
	{
		SFecHorEstablecerFecHor ( p_fecObj, lFecha, lHora );
	}
	return ( p_fecObj );
}

SFechaHora * SFecHorCrearLit ( const char * p_cValor )
{
	SFechaHora * p_fecObj;
	
	p_fecObj = (SFechaHora *) MemReservar ( sizeof ( SFechaHora ) );
	if ( ES_VALIDO ( p_fecObj ) )
	{
		SFecHorEstablecerLit ( p_fecObj, p_cValor );
	}
	return ( p_fecObj );
}

void SFecHorDestruir ( SFechaHora ** p_p_fecObj )
{
	SFechaHora * p_fecObj;
	
	if ( ES_VALIDO ( p_p_fecObj ) )
	{
		p_fecObj = *p_p_fecObj;

		if ( ES_VALIDO ( p_fecObj ) )
		{
			MemLiberar ( (void **) p_p_fecObj );
		}
	}
}

int SFecHorEstablecer ( SFechaHora * p_fecObj, double dValor )
{
	int iRes;

	if ( ES_VALIDO ( p_fecObj ) )
	{
		if ( TmpFormEsValido ( dValor ) == 1 )
		{
			iRes = 1;
			p_fecObj->dValor = dValor;
		}
		else
		{
			iRes = 0;
			p_fecObj->dValor = 0;
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SFecHorEstablecerFecHor ( SFechaHora * p_fecObj, long lFecha, long lHora )
{
	return ( SFecHorEstablecer ( p_fecObj, TmpFormConstruir ( lFecha, lHora ) ) );
}


int SFecHorEstablecerLit ( SFechaHora * p_fecObj, const char * p_cValor )
{
	return ( SFecHorEstablecer ( p_fecObj, atof ( p_cValor ) ) );
}

int SFecHorTieneValor ( SFechaHora * p_fecObj )
{
	int iRes;

	if ( ES_VALIDO ( p_fecObj ) )
	{
		if ( p_fecObj->dValor > 0 )
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

int SFecHorEsValida ( SFechaHora * p_fecObj )
{
	int iRes;

	if ( ES_VALIDO ( p_fecObj ) )
	{
		iRes = TmpFormEsValido ( p_fecObj->dValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SFecHorAAAA ( SFechaHora * p_fecObj )
{
	int	iRes;

	if ( ES_VALIDO ( p_fecObj ) )
	{
		iRes = TmpFormAnos ( p_fecObj->dValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SFecHorMM ( SFechaHora * p_fecObj )
{
	int	iRes;

	if ( ES_VALIDO ( p_fecObj ) )
	{
		iRes = TmpFormMeses ( p_fecObj->dValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SFecHorDD ( SFechaHora * p_fecObj )
{
	int	iRes;

	if ( ES_VALIDO ( p_fecObj ) )
	{
		iRes = TmpFormDias ( p_fecObj->dValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SFecHorHH ( SFechaHora * p_fecObj )
{
	int	iRes;

	if ( ES_VALIDO ( p_fecObj ) )
	{
		iRes = TmpFormHoras ( p_fecObj->dValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SFecHorMI ( SFechaHora * p_fecObj )
{
	int	iRes;

	if ( ES_VALIDO ( p_fecObj ) )
	{
		iRes = TmpFormMinutos ( p_fecObj->dValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SFecHorSS ( SFechaHora * p_fecObj )
{
	int	iRes;

	if ( ES_VALIDO ( p_fecObj ) )
	{
		iRes = TmpFormSegundos ( p_fecObj->dValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

long SFecHorValorFecha ( SFechaHora * p_fecObj )
{
	long lRes;

	if ( ES_VALIDO ( p_fecObj ) )
	{
		lRes = TmpFormFecha ( p_fecObj->dValor );
	}
	else
	{
		lRes = 0;
	}
	return ( lRes );
}

long SFecHorValorHora ( SFechaHora * p_fecObj )
{
	long lRes;

	if ( ES_VALIDO ( p_fecObj ) )
	{
		lRes = TmpFormHora ( p_fecObj->dValor );
	}
	else
	{
		lRes = 0;
	}
	return ( lRes );
}

double SFecHorValor ( SFechaHora * p_fecObj )
{
	double dRes;

	if ( ES_VALIDO ( p_fecObj ) )
	{
		dRes = p_fecObj->dValor;
	}
	else
	{
		dRes = 0.0;
	}
	return ( dRes );
}

double SFecHorValorNumerico ( SFechaHora * p_fecObj )
{
	double dRes;

	if ( ES_VALIDO ( p_fecObj ) )
	{
		dRes = TmpFormObtenerValor ( p_fecObj->dValor );
	}
	else
	{
		dRes = 0.0;
	}
	return ( dRes );
}

char * SFecHorFecha ( SFechaHora * p_fecObj )
{
	return ( SFecHorFechaForm ( p_fecObj, FEC_FORMATO_NORMAL ) );
}

char * SFecHorHora ( SFechaHora * p_fecObj )
{
	return ( SFecHorHoraForm ( p_fecObj, FEC_FORMATO_NORMAL ) );
}

char * SFecHorFechaHora ( SFechaHora * p_fecObj )
{
	return ( SFecHorFechaHoraForm ( p_fecObj, FEC_FORMATO_NORMAL ) );
}

char * SFecHorFechaForm ( SFechaHora * p_fecObj, int iFormato )
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
				CadCopiarConFormato ( p_cRes, FEC_FORMATO_FECHA_NUM, SFecHorAAAA ( p_fecObj ), SFecHorMM ( p_fecObj ), SFecHorDD ( p_fecObj ) );
			}
		}
		else
		{
			iTam = FEC_TAM_FECHA_FORMATO_DEF;
			p_cRes = CadCrear ( iTam );
			if ( ES_VALIDO ( p_cRes ) )
			{
				CadCopiarConFormato ( p_cRes, FEC_FORMATO_FECHA_DEF, SFecHorAAAA ( p_fecObj ), SFecHorMM ( p_fecObj ), SFecHorDD ( p_fecObj ) );
			}
		}
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

char * SFecHorHoraForm ( SFechaHora * p_fecObj, int iFormato )
{
	int		iTam;
	char *	p_cRes;

	if ( ES_VALIDO ( p_fecObj ) )
	{
		if ( iFormato == FEC_FORMATO_NUMERICO )
		{
			iTam = FEC_TAM_HORA_FORMATO_NUM;
			p_cRes = CadCrear ( iTam );
			if ( ES_VALIDO ( p_cRes ) )
			{
				CadCopiarConFormato ( p_cRes, FEC_FORMATO_HORA_NUM, SFecHorHH ( p_fecObj ), SFecHorMI ( p_fecObj ), SFecHorSS ( p_fecObj ) );
			}
		}
		else
		{
			iTam = FEC_TAM_HORA_FORMATO_DEF;
			p_cRes = CadCrear ( iTam );
			if ( ES_VALIDO ( p_cRes ) )
			{
				CadCopiarConFormato ( p_cRes, FEC_FORMATO_HORA_DEF, SFecHorHH ( p_fecObj ), SFecHorMI ( p_fecObj ), SFecHorSS ( p_fecObj ) );
			}
		}
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

char * SFecHorFechaHoraForm ( SFechaHora * p_fecObj, int iFormato )
{
	int		iTam;
	char *	p_cFecha;
	char *	p_cHora;
	char *	p_cRes;

	p_cFecha = SFecHorFechaForm ( p_fecObj, iFormato );
	p_cHora = SFecHorHoraForm ( p_fecObj, iFormato );
	if ( ES_VALIDO ( p_cFecha ) && ES_VALIDO ( p_cHora ) )
	{
		if ( iFormato == FEC_FORMATO_NUMERICO )
		{
			iTam = FEC_TAM_FECHA_HORA_FORMATO_NUM;
		}
		else
		{
			iTam = FEC_TAM_FECHA_HORA_FORMATO_DEF;
		}

		p_cRes = CadCrear ( iTam );
		if ( ES_VALIDO ( p_cRes ) )
		{
			CadCopiar ( p_cRes, p_cFecha );
			if ( iFormato != FEC_FORMATO_NUMERICO )
			{
				CadConcatenarCaracter ( p_cRes, ' ' );
			}
			CadConcatenar ( p_cRes, p_cHora );
		}
	}
	else
	{
		p_cRes = NULL;
	}
	MemLiberar ( (void **) &p_cFecha );
	MemLiberar ( (void **) &p_cHora );
	return ( p_cRes );
}

void SFecHorEstablecerValorDeAhora ( SFechaHora * p_fecObj )
{
	if ( ES_VALIDO ( p_fecObj ) )
	{
		p_fecObj->dValor =  TiempoHoyAhora ();
	}
}

int SFecHorEsIgual ( SFechaHora * p_fecObj, SFechaHora * p_fecValor )
{
	int iRes;

	if ( ES_VALIDO ( p_fecObj ) && ES_VALIDO ( p_fecValor ) )
	{
		iRes = SFecHorEsIgualValor ( p_fecObj, SFecHorValor ( p_fecValor ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SFecHorEsMenor ( SFechaHora * p_fecObj, SFechaHora * p_fecValor )
{
	int iRes;

	if ( ES_VALIDO ( p_fecObj ) && ES_VALIDO ( p_fecValor ) )
	{
		iRes = SFecHorEsMenorValor ( p_fecObj, SFecHorValor ( p_fecValor ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SFecHorEsMayor ( SFechaHora * p_fecObj, SFechaHora * p_fecValor )
{
	int iRes;

	if ( ES_VALIDO ( p_fecObj ) && ES_VALIDO ( p_fecValor ) )
	{
		iRes = SFecHorEsMayorValor ( p_fecObj, SFecHorValor ( p_fecValor ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SFecHorEsDiferente ( SFechaHora * p_fecObj, SFechaHora * p_fecValor )
{
	int iRes;

	if ( ES_VALIDO ( p_fecObj ) && ES_VALIDO ( p_fecValor ) )
	{
		iRes = SFecHorEsDiferenteValor ( p_fecObj, SFecHorValor ( p_fecValor ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SFecHorEsIgualFecha ( SFechaHora * p_fecObj, SFecha * p_fecValor )
{
	int iRes;

	if ( ES_VALIDO ( p_fecObj ) && ES_VALIDO ( p_fecValor ) )
	{
		iRes = SFecHorEsIgualValor ( p_fecObj, SFecValor ( p_fecValor ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SFecHorEsMenorFecha ( SFechaHora * p_fecObj, SFecha * p_fecValor )
{
	int iRes;

	if ( ES_VALIDO ( p_fecObj ) && ES_VALIDO ( p_fecValor ) )
	{
		iRes = SFecHorEsMenorValor ( p_fecObj, SFecValor ( p_fecValor ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SFecHorEsMayorFecha ( SFechaHora * p_fecObj, SFecha * p_fecValor )
{
	int iRes;

	if ( ES_VALIDO ( p_fecObj ) && ES_VALIDO ( p_fecValor ) )
	{
		iRes = SFecHorEsMayorValor ( p_fecObj, SFecValor ( p_fecValor ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SFecHorEsDiferenteFecha ( SFechaHora * p_fecObj, SFecha * p_fecValor )
{
	int iRes;

	if ( ES_VALIDO ( p_fecObj ) && ES_VALIDO ( p_fecValor ) )
	{
		iRes = SFecHorEsDiferenteValor ( p_fecObj, SFecValor ( p_fecValor ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SFecHorEsIgualLit ( SFechaHora * p_fecObj, const char * p_cValor )
{
	double	dValAux;
	int		iRes;

	if ( ES_VALIDO ( p_fecObj ) && ES_VALIDO ( p_cValor ) )
	{
		dValAux = atof ( p_cValor );
		iRes = SFecHorEsIgualValor ( p_fecObj, dValAux );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SFecHorEsMenorLit ( SFechaHora * p_fecObj, const char * p_cValor )
{
	double	dValAux;
	int		iRes;

	if ( ES_VALIDO ( p_fecObj ) && ES_VALIDO ( p_cValor ) )
	{
		dValAux = atof ( p_cValor );
		iRes = SFecHorEsMenorValor ( p_fecObj, dValAux );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SFecHorEsMayorLit ( SFechaHora * p_fecObj, const char * p_cValor )
{
	double	dValAux;
	int		iRes;

	if ( ES_VALIDO ( p_fecObj ) && ES_VALIDO ( p_cValor ) )
	{
		dValAux = atof ( p_cValor );
		iRes = SFecHorEsMayorValor ( p_fecObj, dValAux );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SFecHorEsDiferenteLit ( SFechaHora * p_fecObj, const char * p_cValor )
{
	double	dValAux;
	int		iRes;

	if ( ES_VALIDO ( p_fecObj ) && ES_VALIDO ( p_cValor ) )
	{
		dValAux = atof ( p_cValor );
		iRes = SFecHorEsDiferenteValor ( p_fecObj, dValAux );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SFecHorEsIgualValor ( SFechaHora * p_fecObj, double dValor )
{
	int iRes;
	
	if ( ES_VALIDO ( p_fecObj ) )
	{
		if ( SFecHorValorNumerico ( p_fecObj ) == TmpFormObtenerValor ( dValor ) )
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

int SFecHorEsMenorValor ( SFechaHora * p_fecObj, double dValor )
{
	int iRes;
	
	if ( ES_VALIDO ( p_fecObj ) )
	{
		if ( SFecHorValorNumerico ( p_fecObj ) < TmpFormObtenerValor ( dValor ) )
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

int SFecHorEsMayorValor ( SFechaHora * p_fecObj, double dValor )
{
	int iRes;
	
	if ( ES_VALIDO ( p_fecObj ) )
	{
		if ( SFecHorValorNumerico ( p_fecObj ) > TmpFormObtenerValor ( dValor ) )
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

int SFecHorEsDiferenteValor ( SFechaHora * p_fecObj, double dValor )
{
	int iRes;
	
	if ( ES_VALIDO ( p_fecObj ) )
	{
		if ( SFecHorValorNumerico ( p_fecObj ) != TmpFormObtenerValor ( dValor ) )
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

double SFecHorDiferencia ( SFechaHora * p_fecObj, SFechaHora * p_fecValor )
{
	double dRes;

	if ( ES_VALIDO ( p_fecObj ) && ES_VALIDO ( p_fecValor ) )
	{
		dRes = SFecHorDiferenciaValor ( p_fecObj, SFecHorValor ( p_fecValor ) );
	}
	else
	{
		dRes = 0;
	}
	return ( dRes );
}

double SFecHorDiferenciaLit ( SFechaHora * p_fecObj, const char * p_cValor )
{
	double dRes;
	double dValAux;

	if ( ES_VALIDO ( p_fecObj ) )
	{
		dValAux = atof ( p_cValor );
		dRes = SFecHorDiferenciaValor ( p_fecObj, dValAux );
	}
	else
	{
		dRes = 0;
	}
	return ( dRes );
}

double SFecHorDiferenciaValor ( SFechaHora * p_fecObj, double dValor )
{
	double dRes;

	if ( ES_VALIDO ( p_fecObj ) )
	{
		dRes = SFecHorValorNumerico ( p_fecObj ) - TmpFormObtenerValor ( dValor );
	}
	else
	{
		dRes = 0;
	}
	return ( dRes );
}



