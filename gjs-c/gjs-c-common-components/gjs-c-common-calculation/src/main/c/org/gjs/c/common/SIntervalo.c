
#include "SIntervalo.h"

#include "CalculoConfig.h"


SIntervalo * SIntvCrear ( double dMin, double dMax )
{
	SIntervalo * p_intvObj;
	
	if ( dMin <= dMax )
	{
		p_intvObj= (SIntervalo *) MemReservar ( sizeof ( SIntervalo ) );
		if ( ES_VALIDO ( p_intvObj ) )
		{
			p_intvObj->dMax = dMax;
			p_intvObj->dMin = dMin;
			p_intvObj->iNumDivisiones = 0;
			p_intvObj->p_dDivisiones = NULL;
		}
	}
	else
	{
		p_intvObj = NULL;
	}
	return ( p_intvObj );
}

SIntervalo * SIntvCrearExt ( double dMin, double dMax, int iValores, ... )
{
	SIntervalo *	p_intvObj;
	va_list			valDivisiones;
	double 			dValor;
	double 			dValorAnt;
	int				iValor;
	int				iError;

	p_intvObj= SIntvCrear ( dMin, dMax );
	if ( ES_VALIDO ( p_intvObj ) )
	{
		if ( iValores > 0 )
		{
			va_start ( valDivisiones, iValores );
			p_intvObj->p_dDivisiones = (double *) MemReservar ( iValores * sizeof ( double ) );
			if ( ES_VALIDO ( p_intvObj->p_dDivisiones ) )
			{
				p_intvObj->iNumDivisiones = iValores;
				iError = 0;
				iValor = 0; 
				dValorAnt = p_intvObj->dMin;
				while ( ( iError == 0 ) && ( iValor < iValores ) )
				{
					dValor = va_arg ( valDivisiones, double );
					if ( ( dValor > dValorAnt ) && ( dValor < p_intvObj->dMax ) )
					{
						p_intvObj->p_dDivisiones [ iValor ] = dValor;
						dValorAnt = dValor;
					}
					else
					{
						iError = 1;
					}
					iValor = iValor + 1;
				}
				if ( iError == 1 )
				{
					SIntvDestruir ( &p_intvObj );
				}
			}
			else
			{
				SIntvDestruir ( &p_intvObj );
			}
			va_end ( valDivisiones );
		}
	}
	return ( p_intvObj );
}

SIntervalo * SIntvCrearSimetrico ( double dMax )
{
	return ( SIntvCrear ( -dMax, dMax ) );
}

SIntervalo * SIntvCrearDesdeCero ( double dMax )
{
	return ( SIntvCrear ( 0.0, dMax ) );
}

SIntervalo * SIntvCrearUnidad ()
{
	return ( SIntvCrear ( 0.0, 1.0 ) );
}

SIntervalo * SIntvCrearCentena ()
{
	return ( SIntvCrear ( 0.0, 100.0 ) );
}

SIntervalo * SIntvCrearPunto ( double dValor )
{
	return ( SIntvCrear ( dValor, dValor ) );
}

void SIntvDestruir ( SIntervalo ** p_p_intvObj )
{
	SIntervalo * p_intvObj;
	
	if ( ES_VALIDO ( p_p_intvObj ) )
	{
		p_intvObj = *p_p_intvObj;

		if ( ES_VALIDO ( p_intvObj ) )
		{
			MemLiberar ( (void **) &(p_intvObj->p_dDivisiones) );
			MemLiberar ( (void **) p_p_intvObj );
		}
	}
}

double SIntvMin ( SIntervalo * p_intvObj )
{
	double dRes;

	if ( ES_VALIDO ( p_intvObj ) )
	{
		dRes = p_intvObj->dMin;
	}
	else
	{
		dRes = 0.0;
	}
	return ( dRes );
}

double SIntvMax ( SIntervalo * p_intvObj )
{
	double dRes;

	if ( ES_VALIDO ( p_intvObj ) )
	{
		dRes = p_intvObj->dMax;
	}
	else
	{
		dRes = 0.0;
	}
	return ( dRes );
}

int SIntvEstablecerMin ( SIntervalo * p_intvObj, double dValor )
{
	int iRes;

	if ( ES_VALIDO ( p_intvObj ) )
	{
		p_intvObj->dMin = dValor;
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SIntvEstablecerMax ( SIntervalo * p_intvObj, double dValor )
{
	int iRes;

	if ( ES_VALIDO ( p_intvObj ) )
	{
		p_intvObj->dMax = dValor;
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

double SIntvLongitud ( SIntervalo * p_intvObj )
{
	double dRes;

	if ( ES_VALIDO ( p_intvObj ) )
	{
		dRes = fabs ( p_intvObj->dMax - p_intvObj->dMin );
	}
	else
	{
		dRes = 0.0;
	}
	return ( dRes );
}

int SIntvDividir ( SIntervalo * p_intvObj, int iValores, ... )
{
	int 		iRes;
	va_list		valDivisiones;
	double 		dValor;
	double 		dValorAnt;
	int			iValor;
	int			iError;

	if ( ES_VALIDO ( p_intvObj ) )
	{
		va_start ( valDivisiones, iValores );
		if ( iValores > 0 )
		{
			MemLiberar ( (void **) &(p_intvObj->p_dDivisiones) );
			p_intvObj->iNumDivisiones = 0;
			
			p_intvObj->p_dDivisiones = (double *) MemReservar ( iValores * sizeof ( double ) );
			if ( ES_VALIDO ( p_intvObj->p_dDivisiones ) )
			{
				p_intvObj->iNumDivisiones = iValores;
				iError = 0;
				iValor = 0; 
				dValorAnt = p_intvObj->dMin;
				while ( ( iError == 0 ) && ( iValor < iValores ) )
				{
					dValor = va_arg ( valDivisiones, double );
					if ( ( dValor > dValorAnt ) && ( dValor < p_intvObj->dMax ) )
					{
						p_intvObj->p_dDivisiones [ iValor ] = dValor;
						dValorAnt = dValor;
					}
					else
					{
						iError = 1;
					}
					iValor = iValor + 1;
				}
				if ( iError == 0 )
				{
					iRes = 1;
				}
				else
				{
					MemLiberar ( (void **) &(p_intvObj->p_dDivisiones) );
					p_intvObj->iNumDivisiones = 0;
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
	
		va_end ( valDivisiones );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SIntvDividirEquidistantemente ( SIntervalo * p_intvObj, int iNumSubintervalos )
{
	int 		iValores;
	int 		iRes;
	double 		dValor;
	int			iValor;

	if ( ES_VALIDO ( p_intvObj ) && ( iNumSubintervalos > 1 ) )
	{
		MemLiberar ( (void **) &(p_intvObj->p_dDivisiones) );
		p_intvObj->iNumDivisiones = 0;
		iValores = iNumSubintervalos - 1;
		p_intvObj->p_dDivisiones = (double *) MemReservar ( iValores * sizeof ( double ) );
		if ( ES_VALIDO ( p_intvObj->p_dDivisiones ) )
		{
			p_intvObj->iNumDivisiones = iValores;
			iValor = 0; 
			while ( iValor < iValores )
			{
				dValor = p_intvObj->dMin + iValor * ( p_intvObj->dMax - p_intvObj->dMin ) / iNumSubintervalos;
				p_intvObj->p_dDivisiones [ iValor ] = dValor;
				iValor = iValor + 1;
			}
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

void SIntvLimpiarDivisiones ( SIntervalo * p_intvObj )
{
	if ( ES_VALIDO ( p_intvObj ) )
	{
		MemLiberar ( (void **) &(p_intvObj->p_dDivisiones) );
		p_intvObj->iNumDivisiones = 0;
	}
}

int SIntvEsValido ( SIntervalo * p_intvObj )
{
	int iRes;

	if ( ES_VALIDO ( p_intvObj ) )
	{
		if ( ( p_intvObj->dMin <= p_intvObj->dMax ) &&
			 ( ( ( p_intvObj->iNumDivisiones > 0 ) && ES_VALIDO ( p_intvObj->p_dDivisiones ) ) || 
			   ( ( p_intvObj->iNumDivisiones == 0 ) && ES_NULO ( p_intvObj->p_dDivisiones ) ) ) )
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

int SIntvNumDivisiones ( SIntervalo * p_intvObj )
{
	int iRes;

	if ( ES_VALIDO ( p_intvObj ) )
	{
		iRes = p_intvObj->iNumDivisiones;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SIntvNumSubintervalos ( SIntervalo * p_intvObj )
{
	int iRes;

	if ( ES_VALIDO ( p_intvObj ) )
	{
		iRes = p_intvObj->iNumDivisiones + 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

SIntervalo * SIntvObtenerReflejo ( SIntervalo * p_intvObj )
{
	SIntervalo * p_intvRes;

	if ( SIntvEsValido ( p_intvObj ) == 1 )
	{
		p_intvRes= SIntvCrear ( -p_intvObj->dMax, -p_intvObj->dMin );
	}
	else
	{
		p_intvRes = NULL;
	}
	return ( p_intvRes );
}

SIntervalo * SIntvObtenerInverso ( SIntervalo * p_intvObj )
{
	SIntervalo * p_intvRes;

	if ( SIntvEsValido ( p_intvObj ) == 1 )
	{
		p_intvRes= SIntvCrear ( 1/ p_intvObj->dMax, 1/ p_intvObj->dMin );
	}
	else
	{
		p_intvRes = NULL;
	}
	return ( p_intvRes );
}

SIntervalo * SIntvSubintervalo ( SIntervalo * p_intvObj, int iSubintervalo )
{
	double 			dMax;
	double 			dMin;
	SIntervalo * 	p_intvRes;

	if ( SIntvEsValido ( p_intvObj ) == 1 )
	{
		if ( ( iSubintervalo >= 0 ) && ( iSubintervalo <= p_intvObj->iNumDivisiones ) )
		{
			if ( iSubintervalo == 0 )
			{
				dMin = p_intvObj->dMin;
				dMax = p_intvObj->p_dDivisiones [ 0 ];
			}
			else if ( iSubintervalo == p_intvObj->iNumDivisiones )
			{
				dMin = p_intvObj->p_dDivisiones [ iSubintervalo - 1 ];
				dMax = p_intvObj->p_dDivisiones [ iSubintervalo ];
			}
			else 
			{
				dMin =p_intvObj->p_dDivisiones [ iSubintervalo - 1 ];
				dMax = p_intvObj->dMax;
			}
			p_intvRes= SIntvCrear ( dMin, dMax );
		}
		else
		{
			p_intvRes = NULL;
		}
	}
	else
	{
		p_intvRes = NULL;
	}
	return ( p_intvRes );
}

double SIntvLongitudSubintervalo ( SIntervalo * p_intvObj, int iSubintervalo )
{
	double dMax;
	double dMin;
	double dRes;
	
	if ( SIntvEsValido ( p_intvObj ) == 1 )
	{
		if ( ( iSubintervalo >= 0 ) && ( iSubintervalo <= p_intvObj->iNumDivisiones ) )
		{
			if ( iSubintervalo == 0 )
			{
				dMin = p_intvObj->dMin;
				dMax = p_intvObj->p_dDivisiones [ 0 ];
			}
			else if ( iSubintervalo < p_intvObj->iNumDivisiones )
			{
				dMin = p_intvObj->p_dDivisiones [ iSubintervalo - 1 ];
				dMax = p_intvObj->p_dDivisiones [ iSubintervalo ];
			}
			else 
			{
				dMin =p_intvObj->p_dDivisiones [ iSubintervalo - 1 ];
				dMax = p_intvObj->dMax;
			}
			dRes= fabs ( dMax - dMin );
		}
		else
		{
			dRes = 0.0;
		}
	}
	else
	{
		dRes = 0.0;
	}
	return ( dRes );
}

double SIntvSubintervaloMin ( SIntervalo * p_intvObj, int iSubintervalo )
{
	double dRes;
	
	if ( SIntvEsValido ( p_intvObj ) == 1 )
	{
		if ( ( iSubintervalo >= 0 ) && ( iSubintervalo <= p_intvObj->iNumDivisiones ) )
		{
			if ( iSubintervalo == 0 )
			{
				dRes = p_intvObj->dMin;
			}
			else 
			{
				dRes =p_intvObj->p_dDivisiones [ iSubintervalo - 1 ];
			}
		}
		else
		{
			dRes = 0.0;
		}
	}
	else
	{
		dRes = 0.0;
	}
	return ( dRes );
}

double SIntvSubintervaloMax ( SIntervalo * p_intvObj, int iSubintervalo )
{
	double dRes;
	
	if ( SIntvEsValido ( p_intvObj ) == 1 )
	{
		if ( ( iSubintervalo >= 0 ) && ( iSubintervalo <= p_intvObj->iNumDivisiones ) )
		{
			if ( iSubintervalo < p_intvObj->iNumDivisiones )
			{
				dRes = p_intvObj->p_dDivisiones [ iSubintervalo ];
			}
			else 
			{
				dRes = p_intvObj->dMax;
			}
		}
		else
		{
			dRes = 0.0;
		}
	}
	else
	{
		dRes = 0.0;
	}
	return ( dRes );
}

int SIntvBuscarIntervalo ( SIntervalo * p_intvObj, double dValor )
{
	int 	iRes;
	int		iSubintervalo;

	if ( SIntvEsValido ( p_intvObj ) == 1 )
	{
		if ( ( dValor >= p_intvObj->dMin ) && ( dValor <= p_intvObj->dMax ) )
		{
			iRes = -1;
			iSubintervalo = 0;
			while ( ( iRes < 0 ) && ( iSubintervalo < p_intvObj->iNumDivisiones ) )
			{
				if ( dValor < p_intvObj->p_dDivisiones [ iSubintervalo ] )
				{
					iRes = iSubintervalo;
				}
				else
				{
					iSubintervalo = iSubintervalo + 1;
				}
			}
			if ( iRes < 0 )
			{
				iRes = p_intvObj->iNumDivisiones;
			}
		}
		else
		{
			iRes = -1;
		}
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}



