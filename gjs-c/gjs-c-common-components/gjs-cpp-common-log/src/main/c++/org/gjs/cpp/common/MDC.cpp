#include "LogConfig.h"
#include "MDC.h"


using namespace std;



namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {
                namespace MDC
                {

/* Un mapa por hilo. thread_local se encarga de que cada hilo vea el suyo y de
   destruirlo cuando el hilo termina, asi que no hace falta ni el mapa de mapas,
   ni sincronizarlo, ni que nadie llame a MDCLimpiar para no dejar basura.

   El intento anterior con un mapa compartido no podia funcionar: volatile no da
   seguridad entre hilos en C++ ( solo limita optimizaciones ), y ademas impedia
   llamar a las funciones miembro del mapa, que no estan calificadas asi. */
static thread_local map<string, string> _mapMDCDatos;

void MDCGuardar ( const string & sClave, const string & sValor )
{
	_mapMDCDatos [ sClave ] = sValor;
}

string MDCRecuperar ( const string & sClave )
{
	string sRes ( "" );

	map<string, string>::const_iterator itDato = _mapMDCDatos.find ( sClave );
	if ( itDato != _mapMDCDatos.end () )
	{
		sRes = itDato->second;
	}
	return ( sRes );
}

void MDCEliminar ( const string & sClave )
{
	_mapMDCDatos.erase ( sClave );
}

void MDCLimpiar ()
{
	_mapMDCDatos.clear ();
}

                }
            }
        }
    }
}
