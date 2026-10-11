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
	/* Un generador por hilo, sembrado una vez desde random_device. Con rand ()
	   y srand ( time ( 0 ) ) el estado era uno para todo el proceso: dos hilos
	   se pisaban, y la semilla tocaba la de cualquier otro codigo que usara rand.
	   No es para criptografia: para eso hace falta un generador seguro. */
	thread_local mt19937_64 generador ( random_device {} () );
	uniform_real_distribution < double > distribucion ( 0.0, 1.0 );

	return ( distribucion ( generador ) );
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
