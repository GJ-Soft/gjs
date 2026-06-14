
#include "SPeriodo.h"
#include "TiempoSistema.h"
#include "Fechas.h"
#include "TiempoConfig.h"




static long FechaSigOcurrencia ( int iPeriodicidad, long lFecha );



SPeriodo * SPerdCrear ( int iPeriodicidad, long lFechaInicial  )
{
	SPeriodo *	p_perdObj;
	
	if ( ( TipPeriodEsValido ( iPeriodicidad ) == 1 ) && ( FecFormEsValida ( lFechaInicial ) == 1 ) )
	{
		p_perdObj= (SPeriodo *) MemReservar ( sizeof ( SPeriodo ) );
		if ( ES_VALIDO ( p_perdObj ) )
		{
			p_perdObj->iPeriodicidad = iPeriodicidad;
			p_perdObj->lFechaOcurrencia = lFechaInicial;
		}
	}
	else
	{
		p_perdObj = NULL;
	}
	return ( p_perdObj );
}

void SPerdDestruir ( SPeriodo ** p_p_perdObj )
{
	SPeriodo * p_perdObj;
	
	if ( ES_VALIDO ( p_p_perdObj ) )
	{
		p_perdObj = *p_p_perdObj;

		if ( ES_VALIDO ( p_perdObj ) )
		{
			MemLiberar ( (void **) p_p_perdObj );
		}
	}
}

int SPerdEsValido ( SPeriodo * p_perdObj )
{
	int iRes;

	if ( ES_VALIDO ( p_perdObj ) )
	{
		if ( TipPeriodEsValido ( p_perdObj->iPeriodicidad ) == 1 )
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

int SPerdPeriodicidad ( SPeriodo * p_perdObj )
{
	int iRes;

	if ( ES_VALIDO ( p_perdObj ) )
	{
		iRes = p_perdObj->iPeriodicidad;
	}
	else
	{
		iRes = TIP_PERIOD_NINGUNO;
	}
	return ( iRes );
}

int SPerdEsAnual ( SPeriodo * p_perdObj )
{
	int iRes;

	if ( ES_VALIDO ( p_perdObj ) )
	{
		iRes =  TipPeriodEsAnual ( p_perdObj->iPeriodicidad );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SPerdEsMensual ( SPeriodo * p_perdObj )
{
	int iRes;

	if ( ES_VALIDO ( p_perdObj ) )
	{
		iRes =  TipPeriodEsMensual ( p_perdObj->iPeriodicidad );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SPerdEsTrimestral ( SPeriodo * p_perdObj )
{
	int iRes;

	if ( ES_VALIDO ( p_perdObj ) )
	{
		iRes =  TipPeriodEsTrimestral ( p_perdObj->iPeriodicidad );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SPerdEsSemanal ( SPeriodo * p_perdObj )
{
	int iRes;

	if ( ES_VALIDO ( p_perdObj ) )
	{
		iRes =  TipPeriodEsSemanal ( p_perdObj->iPeriodicidad );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SPerdEsDiario ( SPeriodo * p_perdObj )
{
	int iRes;

	if ( ES_VALIDO ( p_perdObj ) )
	{
		iRes =  TipPeriodEsDiario ( p_perdObj->iPeriodicidad );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SPerdHaOcurrido ( SPeriodo * p_perdObj )
{
	return ( SPerdOcurreHastaFecha ( p_perdObj, FecFormEstablecerValor ( TiempoHoyAhora () ) ) );
}

long SPerdFechaOcurrencia ( SPeriodo * p_perdObj )
{
	long lRes;

	if ( ES_VALIDO ( p_perdObj ) )
	{
		lRes =  p_perdObj->lFechaOcurrencia;
	}
	else
	{
		lRes = 0;
	}
	return ( lRes );
}

long SPerdFechaProximaOcurrencia ( SPeriodo * p_perdObj )
{
	long 	lRes;

	if ( ES_VALIDO ( p_perdObj ) )
	{
		lRes = FechaSigOcurrencia ( p_perdObj->iPeriodicidad, p_perdObj->lFechaOcurrencia );
	}
	else
	{
		lRes = 0;
	}
	return ( lRes );
}

int SPerdOcurreHastaFecha ( SPeriodo * p_perdObj, long lFecha )
{
	int 	iRes;

	if ( ES_VALIDO ( p_perdObj ) )
	{
		if ( FecFormEsValida ( p_perdObj->lFechaOcurrencia ) == 1 ) 
		{
			if ( TipPeriodEsAnual ( p_perdObj->iPeriodicidad ) == 1 )
			{
				if ( FecFormAnos ( lFecha ) - FecFormAnos ( p_perdObj->lFechaOcurrencia ) > 1 ) 
				{
					iRes = 1;
				}
				else if ( FecFormAnos ( lFecha ) - FecFormAnos ( p_perdObj->lFechaOcurrencia ) == 1 ) 
				{
					if ( FecFormMeses ( lFecha ) > FecFormMeses ( p_perdObj->lFechaOcurrencia ) )
					{
						iRes = 1;
					}
					else if ( FecFormMeses ( lFecha ) == FecFormMeses ( p_perdObj->lFechaOcurrencia ) )
					{
						if ( FecFormDias ( lFecha ) >= FecFormDias ( p_perdObj->lFechaOcurrencia ) )
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
			}
			else if ( TipPeriodEsTrimestral ( p_perdObj->iPeriodicidad ) == 1 )
			{
				if ( FecFormAnos ( lFecha ) - FecFormAnos ( p_perdObj->lFechaOcurrencia ) > 1 ) 
				{
					iRes = 1;
				}
				else if ( FecFormAnos ( lFecha ) - FecFormAnos ( p_perdObj->lFechaOcurrencia ) == 1 ) 
				{
					if ( 12 + FecFormMeses ( lFecha ) - FecFormMeses ( p_perdObj->lFechaOcurrencia ) > 3 )
					{
						iRes = 1;
					}
					else if ( 12 + FecFormMeses ( lFecha ) - FecFormMeses ( p_perdObj->lFechaOcurrencia ) == 3 )
					{
						if ( FecFormDias ( lFecha ) >= FecFormDias ( p_perdObj->lFechaOcurrencia ) )
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
				else if ( FecFormAnos ( lFecha ) - FecFormAnos ( p_perdObj->lFechaOcurrencia ) == 0 ) 
				{
					if ( FecFormMeses ( lFecha ) - FecFormMeses ( p_perdObj->lFechaOcurrencia ) > 3 )
					{
						iRes = 1;
					}
					else if ( FecFormMeses ( lFecha ) - FecFormMeses ( p_perdObj->lFechaOcurrencia ) == 3 )
					{
						if ( FecFormDias ( lFecha ) >= FecFormDias ( p_perdObj->lFechaOcurrencia ) )
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
			}
			else if ( TipPeriodEsMensual ( p_perdObj->iPeriodicidad ) == 1 )
			{
				if ( FecFormAnos ( lFecha ) - FecFormAnos ( p_perdObj->lFechaOcurrencia ) > 1 ) 
				{
					iRes = 1;
				}
				else if ( FecFormAnos ( lFecha ) - FecFormAnos ( p_perdObj->lFechaOcurrencia ) == 1 ) 
				{
					if ( 12 - FecFormMeses ( lFecha ) + FecFormMeses ( p_perdObj->lFechaOcurrencia ) > 1 )
					{
						iRes = 1;
					}
					else if ( 12 - FecFormMeses ( lFecha ) + FecFormMeses ( p_perdObj->lFechaOcurrencia ) == 1 )
					{
						if ( FecFormDias ( lFecha ) >= FecFormDias ( p_perdObj->lFechaOcurrencia ) )
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
				else if ( FecFormAnos ( lFecha ) - FecFormAnos ( p_perdObj->lFechaOcurrencia ) == 0 ) 
				{
					if ( FecFormMeses ( lFecha ) - FecFormMeses ( p_perdObj->lFechaOcurrencia ) > 1 )
					{
						iRes = 1;
					}
					else if ( FecFormMeses ( lFecha ) - FecFormMeses ( p_perdObj->lFechaOcurrencia ) == 1 )
					{
						if ( FecFormDias ( lFecha ) >= FecFormDias ( p_perdObj->lFechaOcurrencia ) )
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
			}
			else if ( TipPeriodEsSemanal ( p_perdObj->iPeriodicidad ) == 1 )
			{
				
				if ( FecFormDiferencia ( lFecha, p_perdObj->lFechaOcurrencia ) >= 7 ) 
				{
					iRes = 1;
				}
				else
				{
					iRes = 0;
				}
			}
			else if ( TipPeriodEsDiario ( p_perdObj->iPeriodicidad ) == 1 )
			{
				if ( FecFormDiferencia ( lFecha, p_perdObj->lFechaOcurrencia ) >= 1 ) 
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
				iRes = 1;
			}
		}
		else
		{
			iRes = 1;
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SPerdVecesQueOcurreHastaFecha ( SPeriodo * p_perdObj, long lFecha )
{
	int 	iRes;
	long 	lSigFecha;
	
	if ( ES_VALIDO ( p_perdObj ) )
	{
		if ( FecFormEsValida ( p_perdObj->lFechaOcurrencia ) == 1 ) 
		{
			lSigFecha = FechaSigOcurrencia ( p_perdObj->iPeriodicidad, p_perdObj->lFechaOcurrencia );
			iRes = 0;
			while ( lFecha - lSigFecha > 0 )
			{
				iRes = iRes + 1;
				lSigFecha = FechaSigOcurrencia ( p_perdObj->iPeriodicidad, lSigFecha );
			}
		}
		else
		{
			iRes = 1;
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SPerdVecesQueHaOcurrido ( SPeriodo * p_perdObj )
{
	return ( SPerdVecesQueOcurreHastaFecha ( p_perdObj, TiempoHoyAhora () ) );
}

int SPerdActualizarHastaFecha ( SPeriodo * p_perdObj, long lFecha )
{
	int 	iRes;
	long 	lSigFecha;
	
	if ( ES_VALIDO ( p_perdObj ) && ( FecFormEsValida ( lFecha ) == 1 ) )
	{
		if ( FecFormEsValida ( p_perdObj->lFechaOcurrencia ) == 1 ) 
		{
			lSigFecha = FechaSigOcurrencia ( p_perdObj->iPeriodicidad, p_perdObj->lFechaOcurrencia );
			iRes = 0;
			while ( lFecha - lSigFecha > 0 )
			{
				iRes = iRes + 1;
				lSigFecha = FechaSigOcurrencia ( p_perdObj->iPeriodicidad, lSigFecha );
			}
			if ( iRes > 0 )
			{
				p_perdObj->lFechaOcurrencia = lSigFecha;
			}
		}
		else
		{
			iRes = 1;
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

void SPerdIniciar ( SPeriodo * p_perdObj, long lFechaInicial )
{
	if ( ES_VALIDO ( p_perdObj ) )
	{
		if ( lFechaInicial <= 0 )
		{
			p_perdObj->lFechaOcurrencia = FecFormEstablecerValor ( TiempoHoyAhora () );
		}
		else
		{
			p_perdObj->lFechaOcurrencia = lFechaInicial;
		}
	}
}

int SPerdActualizarHastaHoy ( SPeriodo * p_perdObj ) 
{
	return ( SPerdActualizarHastaFecha ( p_perdObj, FecFormEstablecerValor ( TiempoHoyAhora () ) ) );
} 

static long FechaSigOcurrencia ( int iPeriodicidad, long lFecha )
{
	long 	lRes;
	int		iA;
	int		iM;
	int		iD;

	if ( ( TipPeriodEsValido ( iPeriodicidad ) == 1 ) && ( FecFormEsValida ( lFecha ) == 1 ) )
	{
		FecFormDescomponer ( lFecha, &iA, &iM, &iD );
		if ( TipPeriodEsAnual ( iPeriodicidad ) == 1 )
		{
			lRes = FecFormConstruir ( iA + 1, iM, iD );
		}
		else if ( TipPeriodEsTrimestral ( iPeriodicidad ) == 1 )
		{
			iM = iM + 3;
			if ( iM > 12 )
			{
				iM = iM - 12;
				iA = iA + 1;
			}
			lRes = FecFormConstruir ( iA, iM, iD );
		}
		else if ( TipPeriodEsMensual ( iPeriodicidad ) == 1 )
		{
			iM = iM + 1;
			if ( iM > 12 )
			{
				iM = iM - 12;
				iA = iA + 1;
			}
			lRes = FecFormConstruir ( iA, iM, iD );
		}
		else if ( TipPeriodEsSemanal ( iPeriodicidad ) == 1 )
		{
			FecSumar ( &iA, &iM, &iD, 0, 0, 7 );
			lRes = FecFormConstruir ( iA, iM, iD );
		}
		else if ( TipPeriodEsDiario ( iPeriodicidad ) == 1 )
		{
			FecSumar ( &iA, &iM, &iD, 0, 0, 1 );
			lRes = FecFormConstruir ( iA, iM, iD );
		}
		else
		{
			lRes = FecFormEstablecerValor ( TiempoHoyAhora () );
		}
	}
	else
	{
		lRes = 0;
	}
	return ( lRes );
}

