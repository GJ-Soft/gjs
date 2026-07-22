/******************************************************************************/
/*                              Cronometro.cpp                               */
/*----------------------------------------------------------------------------*/
/* Librería:  Tiempo                                                          */
/* Versión:   3.0.0                                                           */
/* Fecha:     25/03/2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Fichero de código fuente que contiene la implementación de la clase de     */
/* datos Cronometro.                                                         */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#include "Cronometro.h"



#include "CommonTimeConfig.h"




using namespace std;



namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {


Cronometro::Cronometro ()
{
    p_tpTiempoIni = NULL;
}

Cronometro::~Cronometro ()
{
}

void Cronometro::Iniciar ()
{
    p_tpTiempoIni = new chrono::system_clock::time_point ( chrono::system_clock::now() );
}

long long  Cronometro::Parar ()
{
	long long llRes = Computo ();
	if ( ES_VALIDO( p_tpTiempoIni ) )
	{
	    delete p_tpTiempoIni;
	}
	p_tpTiempoIni = NULL;
	return ( llRes );
}

long long  Cronometro::Computo ()
{
	long long llRes = 0;
	if ( ES_VALIDO( p_tpTiempoIni ) )
	{
		chrono::system_clock::time_point tpTiempoFin = chrono::system_clock::now();
		chrono::system_clock::duration d = tpTiempoFin - *p_tpTiempoIni;
		llRes = (long long) (chrono::duration_cast<chrono::milliseconds>(d).count());
	}
	return ( llRes );
}



 			}
		}
	}
}




