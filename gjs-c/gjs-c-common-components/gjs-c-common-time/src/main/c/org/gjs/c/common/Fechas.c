
#include "Fechas.h"
#include "Calendario.h"
#include "TiempoConfig.h"




long FecFormConstruir ( int iA, int iM, int iD )
{
	long lRes;

	if ( FecEsValida ( iA, iM, iD ) == 1 )
	{
		lRes = iA * 10000 + iM * 100 + iD;
	}
	else
	{
		lRes = 0;
	}
	return ( lRes );
}

int FecEsValida ( int iA, int iM, int iD )
{
	int iRes;

	if ( ( iA != 0 ) && ( iM >= 1 ) && ( iM <= 12 ) &&
		 ( iD >= 1 ) && ( iD <= CalendDiasMes ( iA, iM ) ) )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int FecFormEsValida ( long lFecha )
{
	int	iRes;
	int iA = 0;
	int iM = 0;
	int iD = 0;

	FecFormDescomponer ( lFecha, &iA, &iM, &iD );
	iRes = FecEsValida ( iA, iM, iD );
	return ( iRes );
}

void FecFormDescomponer ( long lFecha, int * p_iA, int * p_iM, int * p_iD )
{
	long lAux;

	if ( ( lFecha >= 0 ) && ( lFecha < 10000000 ) && 
		 ES_VALIDO ( p_iA ) && ES_VALIDO ( p_iM ) && ES_VALIDO ( p_iD ) )
	{
		*p_iA = lFecha / 10000;
		lAux = lFecha % 10000;
		*p_iM = lAux / 100;
		*p_iD = lAux % 100;
	} 
}

int FecFormAnos ( long lFecha )
{
 	return ( lFecha / 10000 );
}

int FecFormMeses ( long lFecha )
{
 	return ( ( lFecha % 10000 ) / 100 );
}

int FecFormDias ( long lFecha )
{
 	return ( lFecha % 100 );
}

int FecNumDiasAnualesHasta ( int iA, int iM, int iD ) 
{
	int iRes;

	if ( FecEsValida ( iA, iM, iD ) == 1 )
	{
		iRes = CalendDiasAnualesHastaElMes ( iA, iM ) + iD;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int FecNumDiasAnualesDesde ( int iA, int iM, int iD ) 
{
	int iRes;

	if ( FecEsValida ( iA, iM, iD ) == 1 )
	{
		iRes = CalendDiasAnualesDesdeElMes ( iA, iM ) +  CalendDiasMes ( iA, iM ) - iD;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int FecFormNumDiasAnualesHasta ( long lFecha )
{
	int iRes;
	int iA = 0;
	int iM = 0;
	int iD = 0;

	FecFormDescomponer ( lFecha, &iA, &iM, &iD );
	iRes = FecNumDiasAnualesHasta ( iA, iM, iD );
	return ( iRes );
}

int FecFormNumDiasAnualesDesde ( long lFecha )
{
	int iRes;
	int iA = 0;
	int iM = 0;
	int iD = 0;

	FecFormDescomponer ( lFecha, &iA, &iM, &iD );
	iRes = FecNumDiasAnualesDesde ( iA, iM, iD );
	return ( iRes );
}

int FecDiferencia ( int iA1, int iM1, int iD1, int iA2, int iM2, int iD2 )
{
	int iRes;
	int iSigno;
	int iAy;
	int iMy;
	int iDy;
	int iAn;
	int iMn;
	int iDn;

	if ( ( FecEsValida ( iA1, iM1, iD1 ) == 1 ) && ( FecEsValida ( iA2, iM2, iD2 ) == 1 ) )
	{
		if ( FecEsMayorIgual ( iA1, iM1, iD1, iA2, iM2, iD2 ) )
		{
			iSigno = 1;
			iAy = iA1;
			iMy = iM1;
			iDy = iD1;
			iAn = iA2;
			iMn = iM2;
			iDn = iD2;
		}
		else
		{
			iSigno = -1;
			iAy = iA2;
			iMy = iM2;
			iDy = iD2;
			iAn = iA1;
			iMn = iM1;
			iDn = iD1;
		}
		if ( iAy == iAn )
		{
			iRes = FecNumDiasAnualesHasta ( iAy, iMy, iDy ) - FecNumDiasAnualesHasta ( iAn, iMn, iDn );
		}
		else
		{
			iRes = FecNumDiasAnualesDesde ( iAn, iMn, iDn );
			for ( int iAAAA	= iAn + 1; iAAAA < iAy; iAAAA = iAAAA + 1 )
			{
				iRes = iRes + CalendDiasAno ( iAAAA );
			}
			iRes = iRes + FecNumDiasAnualesHasta ( iAy, iMy, iDy );
		}
		iRes = iSigno * iRes;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int FecFormDiferencia ( long lFecha1, long lFecha2 )
{
	int iRes;
	int iA1 = 0;
	int iM1 = 0;
	int iD1 = 0;
	int iA2 = 0;
	int iM2 = 0;
	int iD2 = 0;

	FecFormDescomponer ( lFecha1, &iA1, &iM1, &iD1 );
	FecFormDescomponer ( lFecha2, &iA2, &iM2, &iD2 );
	iRes = FecDiferencia ( iA1, iM1, iD1, iA2, iM2, iD2 );
	return ( iRes );
}

int FecSumar ( int * p_iA, int * p_iM, int * p_iD, int iA, int iM, int iD )
{
	int iRes;

	if ( ES_VALIDO ( p_iA ) && ES_VALIDO ( p_iM ) && ES_VALIDO ( p_iD ) )
	{
		if ( FecEsValida ( *p_iA, *p_iM, *p_iD ) == 1 )
		{
			*p_iD = *p_iD + iD;
			if ( *p_iD > CalendDiasMes ( *p_iA, *p_iM ) )
			{
				*p_iD = *p_iD - CalendDiasMes ( *p_iA, *p_iM );
				*p_iM = *p_iM + 1;
			}
			*p_iM = *p_iM + iM;
			if ( *p_iM > 12 )
			{
				*p_iM = *p_iM - 12;
				*p_iA = *p_iA + 1;
			}
			*p_iA = *p_iA + iA;
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

int FecRestar ( int * p_iA, int * p_iM, int * p_iD, int iA, int iM, int iD )
{
	int iRes;

	if ( ES_VALIDO ( p_iA ) && ES_VALIDO ( p_iM ) && ES_VALIDO ( p_iD ) )
	{
		if ( FecEsValida ( *p_iA, *p_iM, *p_iD ) == 1 )
		{
			*p_iD = *p_iD - iD;
			*p_iM = *p_iM - iM;
			*p_iA = *p_iA - iA;

			if ( *p_iD <= 0 )
			{
				*p_iD = CalendDiasMes ( *p_iA, *p_iM ) + *p_iD;
				*p_iM = *p_iM - 1;
			}
			if ( *p_iM <= 0 )
			{
				*p_iM = 12 + *p_iM;
				*p_iA = *p_iA - 1;
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

long FecFormSumar ( long lFecha, int iA, int iM, int iD )
{
	long	lRes;
	int		iA1 = 0;
	int		iM1 = 0;
	int		iD1 = 0;

	FecFormDescomponer ( lFecha, &iA1, &iM1, &iD1 );
	if ( FecSumar ( &iA1, &iM1, &iD1, iA, iM, iD ) == 1 )
	{
		lRes = FecFormConstruir ( iA1, iM1, iD1 );
	}
	else
	{
		lRes = -1;
	}
	return ( lRes );
}

long FecFormRestar ( long lFecha, int iA, int iM, int iD )
{
	long	lRes;
	int		iA1 = 0;
	int		iM1 = 0;
	int		iD1 = 0;

	FecFormDescomponer ( lFecha, &iA1, &iM1, &iD1 );
	if ( FecRestar ( &iA1, &iM1, &iD1, iA, iM, iD ) == 1 )
	{
		lRes = FecFormConstruir ( iA1, iM1, iD1 );
	}
	else
	{
		lRes = -1;
	}
	return ( lRes );
}

int FecSumarDias ( int * p_iA, int * p_iM, int * p_iD, int iD )
{
	int iRes;
	int iDiasMes;

	if ( ES_VALIDO ( p_iA ) && ES_VALIDO ( p_iM ) && ES_VALIDO ( p_iD ) )
	{
		if ( FecEsValida ( *p_iA, *p_iM, *p_iD ) == 1 )
		{
			while ( iD > 0 ) 
			{
				iDiasMes = CalendDiasMes ( *p_iA, *p_iM );
				if ( iDiasMes - *p_iD > iD )
				{
					*p_iD = *p_iD + iD;
					iD = 0;
				}
				else
				{
					*p_iD = 1;
					iD = iD - iDiasMes + *p_iD - 1;
					*p_iM = *p_iM + 1;
					if ( *p_iM == 13 )
					{
						*p_iA = *p_iA + 1;
						*p_iM = 1;
					}
				}
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

int FecRestarDias ( int * p_iA, int * p_iM, int * p_iD, int iD )
{
	return ( FecSumarDias (  p_iA, p_iM, p_iD, -iD ) );
}

int FecSumarMeses ( int * p_iA, int * p_iM, int * p_iD, int iM )
{
	int iRes;

	if ( ES_VALIDO ( p_iA ) && ES_VALIDO ( p_iM ) && ES_VALIDO ( p_iD ) )
	{
		if ( FecEsValida ( *p_iA, *p_iM, *p_iD ) == 1 )
		{
			*p_iA = *p_iA + ( *p_iM + iM ) / 12;
			*p_iM = ( ( *p_iM + iM ) % 12 ) + 1;
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

int FecRestarMeses ( int * p_iA, int * p_iM, int * p_iD, int iM )
{
	return ( FecSumarMeses ( p_iA, p_iM, p_iD, -iM ) );
}

int FecSumarAnos ( int * p_iA, int * p_iM, int * p_iD, int iA )
{
	int iRes;

	if ( ES_VALIDO ( p_iA ) && ES_VALIDO ( p_iM ) && ES_VALIDO ( p_iD ) )
	{
		if ( FecEsValida ( *p_iA, *p_iM, *p_iD ) == 1 )
		{
			*p_iA = *p_iA + iA;
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

int FecRestarAnos ( int * p_iA, int * p_iM, int * p_iD, int iA )
{
	return ( FecSumarAnos ( p_iA, p_iM, p_iD, -iA ) );
}

long FecFormSumarDias ( long lFecha, int iD )
{
	long	lRes;
	int		iA1 = 0;
	int		iM1 = 0;
	int		iD1 = 0;

	FecFormDescomponer ( lFecha, &iA1, &iM1, &iD1 );
	if ( FecSumarDias ( &iA1, &iM1, &iD1, iD ) == 1 )
	{
		lRes = FecFormConstruir ( iA1, iM1, iD1 );
	}
	else
	{
		lRes = -1;
	}
	return ( lRes );
}

long FecFormRestarDias ( long lFecha, int iD )
{
	return ( FecFormSumarDias ( lFecha, -iD ) );
}

long FecFormSumarMeses ( long lFecha, int iM )
{
	long	lRes;
	int		iA1 = 0;
	int		iM1 = 0;
	int		iD1 = 0;

	FecFormDescomponer ( lFecha, &iA1, &iM1, &iD1 );
	if ( FecSumarMeses ( &iA1, &iM1, &iD1, iM ) == 1 )
	{
		lRes = FecFormConstruir ( iA1, iM1, iD1 );
	}
	else
	{
		lRes = -1;
	}
	return ( lRes );
}

long FecFormRestarMeses ( long lFecha, int iM )
{
	return ( FecFormSumarMeses ( lFecha, -iM ) );
}

long FecFormSumarAnos ( long lFecha, int iA )
{
	return ( lFecha + iA * 10000 );
}

long FecFormRestarAnos ( long lFecha, int iA )
{
	return ( FecFormSumarAnos ( lFecha, -iA ) );
}

int FecValEsValido ( double dValor )
{
	int iRes;

	if ( ( dValor >= 1.0 ) || ( dValor <= -1.0 ) )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int FecEsIgual ( int iA1, int iM1, int iD1, int iA2, int iM2, int iD2 )
{
	int iRes;
	
	if ( ( iA1 == iA2 ) && ( iM1 == iM2 ) && ( iD1 == iD2 ) )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}
	
int FecFormEsIgual ( long lFecha1, long lFecha2 )
{
	int iRes;
	
	if ( lFecha1 == lFecha2 )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}
	
int FecEsMenor ( int iA1, int iM1, int iD1, int iA2, int iM2, int iD2 )
{
	int iRes;
	
	if ( iA1 < iA2 )
	{
		iRes = 1;
	}
	else if ( iA1 == iA2 )
	{
		if ( iM1 < iM2 ) 
		{
			iRes = 1;
		}
		else if ( iM1 == iM2 )
		{
			if ( iD1 < iD2 ) 
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
	return ( iRes );
}

int FecFormEsMenor ( long lFecha1, long lFecha2 )
{
	int iRes;
	
	if ( lFecha1 < lFecha2 )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}
	
int FecEsMayor ( int iA1, int iM1, int iD1, int iA2, int iM2, int iD2 )
{
	int iRes;
	
	if ( iA1 > iA2 )
	{
		iRes = 1;
	}
	else if ( iA1 == iA2 )
	{
		if ( iM1 > iM2 ) 
		{
			iRes = 1;
		}
		else if ( iM1 == iM2 )
		{
			if ( iD1 > iD2 ) 
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
	return ( iRes );
}

int FecFormEsMayor ( long lFecha1, long lFecha2 )
{
	int iRes;
	
	if ( lFecha1 > lFecha2 )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}
	
int FecEsMenorIgual ( int iA1, int iM1, int iD1, int iA2, int iM2, int iD2 )
{
	int iRes;
	
	if ( ( FecEsMenor ( iA1, iM1, iD1, iA2, iM2, iD2 ) == 1 ) ||
			( FecEsIgual ( iA1, iM1, iD1, iA2, iM2, iD2 ) == 1 ) )
	{
		iRes = 1;
	}
	else 
	{
		iRes = 0;
	}
	return ( iRes );
}

int FecFormEsMenorIgual ( long lFecha1, long lFecha2 )
{
	int iRes;
	
	if ( lFecha1 <= lFecha2 )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}
	
int FecEsMayorIgual ( int iA1, int iM1, int iD1, int iA2, int iM2, int iD2 )
{
	int iRes;
	
	if ( ( FecEsMayor ( iA1, iM1, iD1, iA2, iM2, iD2 ) == 1 ) ||
			( FecEsIgual ( iA1, iM1, iD1, iA2, iM2, iD2 ) == 1 ) )
	{
		iRes = 1;
	}
	else 
	{
		iRes = 0;
	}
	return ( iRes );
}

int FecFormEsMayorIgual ( long lFecha1, long lFecha2 )
{
	int iRes;
	
	if ( lFecha1 >= lFecha2 )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}
	
double FecObtenerValor ( int iA, int iM, int iD )
{
	double dRes;

	if ( FecEsValida ( iA, iM, iD ) == 1 )
	{
		dRes = iA * 1.0 + FecNumDiasAnualesHasta ( iA, iM, iD ) / CalendDiasAno ( iA );
	}
	else
	{
		dRes = -1.0;
	}
	return ( dRes );
}

double FecFormObtenerValor ( long lFecha )
{
	double	dRes;
	int		iA = 0;
	int		iM = 0;
	int		iD = 0;

	FecFormDescomponer ( lFecha, &iA, &iM, &iD );
	dRes = FecObtenerValor ( iA, iM, iD );
	return ( dRes );
}

int FecEstablecerValor ( double dValor, int * p_iA, int * p_iM, int * p_iD )
{
	double	dDias;
	int		iRes;

	if ( ( FecValEsValido ( dValor ) == 1 ) && 
		   ES_VALIDO ( p_iA ) && ES_VALIDO ( p_iM ) && ES_VALIDO ( p_iD ) )
	{
		*p_iA = ConvRealDobleAEntero ( dValor, 1 );
		dDias = ( dValor - *p_iA * 1.0 ) * CalendDiasAno ( *p_iA ); 
		*p_iM = 1;
		while ( ( dDias > CalendDiasMes ( *p_iA, *p_iM ) ) && ( *p_iM <= 12 ) )
		{
			dDias = dDias - CalendDiasMes ( *p_iA, *p_iM ) * 1.0;
			*p_iM = *p_iM + 1;
		}
		if ( *p_iM <= 12 )
		{
			*p_iD = ConvRealDobleAEntero ( dDias, 0 );
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

long FecFormEstablecerValor ( double dValor )
{
	long	lRes;
	int		iA = 0;
	int		iM = 0;
	int		iD = 0;

	if ( FecEstablecerValor ( dValor, &iA, &iM, &iD ) == 1 )
	{
		lRes = FecFormConstruir ( iA, iM, iD );
	}
	else
	{
		lRes = -1;
	}
	return ( lRes );
}







