
#include "Horas.h"
#include "TiempoConfig.h"





long HorFormConstruir ( int iH, int iM, int iS )
{
	long lRes;

	if ( HorEsValida ( iH, iM, iS ) == 1 )
	{
		lRes = iH * 10000 + iM * 100 + iS;
	}
	else
	{
		lRes = -1;
	}
	return ( lRes );
}

int HorEsValida ( int iH, int iM, int iS )
{
	int iRes;

	if ( ( iH >= 0 ) && ( iH < 24 ) &&
		 ( iM >= 0 ) && ( iM < 60 ) &&
		 ( iS >= 0 ) && ( iS < 60 ) )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int HorFormEsValida ( long lHora )
{
	int	iRes;
	int iH = 0;
	int iM = 0;
	int iS = 0;

	HorFormDescomponer ( lHora, &iH, &iM, &iS );
	iRes = HorEsValida ( iH, iM, iS );
	return ( iRes );
}

void HorFormDescomponer ( long lHora, int * p_iH, int * p_iM, int * p_iS )
{
	long lAux;

	if ( ( lHora >= 0 ) && ( lHora < 1000000 ) && 
		 ES_VALIDO ( p_iH ) && ES_VALIDO ( p_iM ) && ES_VALIDO ( p_iS ) )
	{
		*p_iH = lHora / 10000;
		lAux = lHora % 10000;
		*p_iM = lAux / 100;
		*p_iS = lAux % 100;
	} 
}

int HorFormHoras ( long lHora )
{
 	return ( lHora / 10000 );
}

int HorFormMinutos ( long lHora )
{
 	return ( ( lHora % 10000 ) / 100 );
}

int HorFormSegundos ( long lHora )
{
 	return ( lHora % 100 );
}

int HorNumMinutos ( int iH, int iM, int iS ) 
{
	int iRes;

	if ( HorEsValida ( iH, iM, iS ) == 1 )
	{
		iRes = iH * 60 + iM;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int HorNumSegundos ( int iH, int iM, int iS ) 
{
	int iRes;

	if ( HorEsValida ( iH, iM, iS ) == 1 )
	{
		iRes = iH * 3600 + iM * 60 + iS;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int HorFormNumMinutos ( long lHora )
{
	int iRes;
	int iH = 0;
	int iM = 0;
	int iS = 0;

	HorFormDescomponer ( lHora, &iH, &iM, &iS );
	iRes = HorNumMinutos ( iH, iM, iS );
	return ( iRes );
}

int HorFormNumSegundos ( long lHora )
{
	int iRes;
	int iH = 0;
	int iM = 0;
	int iS = 0;

	HorFormDescomponer ( lHora, &iH, &iM, &iS );
	iRes = HorNumSegundos ( iH, iM, iS );
	return ( iRes );
}

int HorSumar ( int * p_iH, int * p_iM, int * p_iS, int iH, int iM, int iS )
{
	int iRes;

	if ( ES_VALIDO ( p_iH ) && ES_VALIDO ( p_iM ) && ES_VALIDO ( p_iS ) )
	{
		if ( ( HorEsValida ( *p_iH, *p_iM, *p_iS ) == 1 ) && ( HorEsValida ( iH, iM, iS ) == 1 ) )
		{
			*p_iS = *p_iS + iS;
			if ( *p_iS >= 60 )
			{
				*p_iS = *p_iS - 60;
				*p_iM = *p_iM + 1;
			}
			*p_iM = *p_iM + iM;
			if ( *p_iM >= 60 )
			{
				*p_iM = *p_iM - 60;
				*p_iH = *p_iH + 1;
			}
			*p_iH = *p_iH + iH;
			if ( *p_iH >= 24 )
			{
				// Acarreo:
				iRes = 2;
				*p_iH = *p_iH - 24;
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
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int HorRestar ( int * p_iH, int * p_iM, int * p_iS, int iH, int iM, int iS )
{
	int iRes;

	if ( ES_VALIDO ( p_iH ) && ES_VALIDO ( p_iM ) && ES_VALIDO ( p_iS ) )
	{
		if ( ( HorEsValida ( *p_iH, *p_iM, *p_iS ) == 1 ) && ( HorEsValida ( iH, iM, iS ) == 1 ) )
		{
			*p_iS = *p_iS - iS;
			if ( *p_iS < 0 )
			{
				*p_iS = 60 + *p_iS;
				*p_iM = *p_iM - 1;
			}
			*p_iM = *p_iM - iM;
			if ( *p_iM < 0 )
			{
				*p_iM = 60 + *p_iM;
				*p_iH = *p_iH - 1;
			}
			*p_iH = *p_iH - iH;
			if ( *p_iH < 0 )
			{
				// Acarreo:
				iRes = 2;
				*p_iH = 24 + *p_iH;
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
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

long HorFormSumar ( long lHora1, long lHora2 )
{
	long	lRes;
	int		iH1 = 0;
	int		iM1 = 0;
	int		iS1 = 0;
	int		iH2 = 0;
	int		iM2 = 0;
	int		iS2 = 0;

	HorFormDescomponer ( lHora1, &iH1, &iM1, &iS1 );
	HorFormDescomponer ( lHora2, &iH2, &iM2, &iS2 );
	if ( HorSumar ( &iH1, &iM1, &iS1, iH2, iM2, iS2 ) == 1 )
	{
		lRes = HorFormConstruir ( iH1, iM1, iS1 );
	}
	else
	{
		lRes = -1;
	}
	return ( lRes );
}

long HorFormRestar ( long lHora1, long lHora2 )
{
	long	lRes;
	int		iH1 = 0;
	int		iM1 = 0;
	int		iS1 = 0;
	int		iH2 = 0;
	int		iM2 = 0;
	int		iS2 = 0;

	HorFormDescomponer ( lHora1, &iH1, &iM1, &iS1 );
	HorFormDescomponer ( lHora2, &iH2, &iM2, &iS2 );
	if ( HorRestar ( &iH1, &iM1, &iS1, iH2, iM2, iS2 ) == 1 )
	{
		lRes = HorFormConstruir ( iH1, iM1, iS1 );
	}
	else
	{
		lRes = -1;
	}
	return ( lRes );
}

int HorValEsValido ( double dValor )
{
	int iRes;

	if ( ( dValor >= 0.0 ) && ( dValor < 24.0 ) )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

double HorObtenerValor ( int iH, int iM, int iS )
{
	double dRes;

	if ( HorEsValida ( iH, iM, iS ) == 1 )
	{
		dRes = iH * 1.0 + iM / 60.0 + iS / 3600.0;
	}
	else
	{
		dRes = -1.0;
	}
	return ( dRes );
}

double HorFormObtenerValor ( long lHora )
{
	double	dRes;
	int		iH = 0;
	int		iM = 0;
	int		iS = 0;

	HorFormDescomponer ( lHora, &iH, &iM, &iS );
	dRes = HorObtenerValor ( iH, iM, iS );
	return ( dRes );
}

int HorEstablecerValor ( double dValor, int * p_iH, int * p_iM, int * p_iS )
{
	double	dAux;
	int		iRes;

	if ( ( HorValEsValido ( dValor ) == 1 ) && 
		   ES_VALIDO ( p_iH ) && ES_VALIDO ( p_iM ) && ES_VALIDO ( p_iS ) )
	{
		*p_iH = ConvRealDobleAEntero ( dValor, 1 );
		dAux = ( dValor - *p_iH * 1.0 ) * 60; 
		*p_iM = ConvRealDobleAEntero ( dAux, 1 );
		dAux = ( dAux - *p_iM ) * 60; 
		*p_iS = ConvRealDobleAEntero ( dAux, 0 );
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

long HorFormEstablecerValor ( double dValor )
{
	long	lRes;
	int		iH = 0;
	int		iM = 0;
	int		iS = 0;

	if ( HorEstablecerValor ( dValor, &iH, &iM, &iS ) == 1 )
	{
		lRes = HorFormConstruir ( iH, iM, iS );
	}
	else
	{
		lRes = -1;
	}
	return ( lRes );
}


