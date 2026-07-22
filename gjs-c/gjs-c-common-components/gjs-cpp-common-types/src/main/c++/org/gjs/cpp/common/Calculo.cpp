#include "CommonTypesConfig.h"
#include "Calculo.h"

#include <cstdlib>
#include <random>



using namespace std;


namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {

const double EPSILON = numeric_limits<double>::epsilon();

double Epsilon()
{
	return ( EPSILON );
}

double GenerarNumeroAleatorio()
{
	static bool bSembrado = false;
	if ( ! bSembrado )
	{
		srand ( (unsigned) time( 0 ) );
		bSembrado = true;
	}
	// Division en coma flotante para obtener un valor en [0.0, 1.0):
	return ( (double) rand() / ( (double) RAND_MAX + 1.0 ) );
}


bool EsIgual( double dA, double dB )
{
	return ( fabs( dA - dB ) <= EPSILON );
}

bool EsMayor( double dA, double dB )
{
	return ( ( dA - dB ) > EPSILON );
}

bool EsMenor( double dA, double dB )
{
	return ( ( dB - dA ) > EPSILON );
}

 			}
		}
	}
}
