#include "BaseConfig.h"
#include "Real.h"





using namespace std;



namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {
				namespace real
				{

constexpr double EPSILON_FLOAT = numeric_limits<float>::epsilon(); 
constexpr double EPSILON_DOUBLE = numeric_limits<double>::epsilon(); 
constexpr double EPSILON_LDOUBLE = numeric_limits<long double>::epsilon(); 


bool equals ( float fValor1, float fValor2, int iTolerancia )
{
    return abs( fValor1 - fValor2 ) <= EPSILON_FLOAT * max( abs( fValor1 ), abs( fValor2 ) ) * iTolerancia;
}

bool equals ( double dValor1, double dValor2, int iTolerancia )
{
    return abs( dValor1 - dValor2 ) <= EPSILON_DOUBLE * max( abs( dValor1 ), abs( dValor2 ) ) * iTolerancia;
}

bool equals ( long double ldValor1, long double ldValor2, int iTolerancia )
{
    return abs( ldValor1 - ldValor2 ) <= EPSILON_LDOUBLE * max( abs( ldValor1 ), abs( ldValor2 ) ) * iTolerancia;
}

bool equalsWithPrec ( float fValor1, float fValor2, int iDigitosSignificativos )
{
	bool bRes = false;
    if ( ( fValor1 != 0.0 ) && ( fValor2 != 0.0 ) ) {
		// Tolerancia relativa basada en dígitos significativos
		float fTolerancia = pow ( 10.0, -iDigitosSignificativos + 1 );
		// Usar el mayor de los dos como dReferencia para la comparación relativa
		float fReferencia = max ( abs ( fValor1 ), abs( fValor2 ) );
		if ( fReferencia != 0.0 )
		{
			bRes = abs( fValor1 - fValor2 ) / fReferencia < fTolerancia;
		}
		else
		{
			bRes = true;
		}
	}
	else
	{
		// Solo se consideran iguales si ambos son exactamente cero.
		bRes = ( fValor1 == 0.0 ) && ( fValor2 == 0.0 );
	}
    return ( bRes );
}

bool equalsWithPrec ( double dValor1, double dValor2, int iDigitosSignificativos )
{
	bool bRes = false;
    if ( ( dValor1 != 0.0 ) && ( dValor2 != 0.0 ) ) {
		// Tolerancia relativa basada en dígitos significativos
		double dTolerancia = pow ( 10.0, -iDigitosSignificativos + 1 );
		// Usar el mayor de los dos como dReferencia para la comparación relativa
		double dReferencia = max ( abs ( dValor1 ), abs( dValor2 ) );
		if ( dReferencia != 0.0 )
		{
			bRes = abs( dValor1 - dValor2 ) / dReferencia < dTolerancia;
		}
		else
		{
			bRes = true;
		}
	}
	else
	{
		// Solo se consideran iguales si ambos son exactamente cero.
		bRes = ( dValor1 == 0.0 ) && ( dValor2 == 0.0 );
	}
    return ( bRes );
}

bool equalsWithPrec ( long double ldValor1, long double ldValor2, int iDigitosSignificativos )
{
	bool bRes = false;
    if ( ( ldValor1 != 0.0 ) && ( ldValor2 != 0.0 ) ) {
		// Tolerancia relativa basada en dígitos significativos
		long double ldTolerancia = pow ( 10.0, -iDigitosSignificativos + 1 );
		// Usar el mayor de los dos como dReferencia para la comparación relativa
		long double ldReferencia = max ( abs ( ldValor1 ), abs( ldValor2 ) );
		if ( ldReferencia != 0.0 )
		{
			bRes = abs( ldValor1 - ldValor2 ) / ldReferencia < ldTolerancia;
		}
		else
		{
			bRes = true;
		}
	}
	else
	{
		// Solo se consideran iguales si ambos son exactamente cero.
		bRes = ( ldValor1 == 0.0 ) && ( ldValor2 == 0.0 );
	}
    return ( bRes );
}

				}
			}
		}
	}
}

