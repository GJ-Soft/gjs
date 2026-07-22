#include "CommonTypesConfig.h"
#include "MemoriaGlobal.h"


using namespace std;
using namespace org::gjs::cpp::common;


namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {

static map<string, string> mapMemoriaGlobal;


void MemGlobGuardar ( const string & sClave, const string & sValor )
{
	mapMemoriaGlobal [ sClave ] = sValor;
}

string MemGlobRecuperar ( const string & sClave )
{
	string sValor( "" );
	// Usar find (no operator[]) para no insertar una entrada vacia si la clave
	// no existe.
	map<string, string>::const_iterator it = mapMemoriaGlobal.find ( sClave );
	if ( it != mapMemoriaGlobal.end () )
	{
		sValor = it->second;
	}
	return ( sValor );
}

void MemGlobEliminar ( const string & sClave )
{
	mapMemoriaGlobal.erase ( sClave );
}

bool MemGlobExiste ( const string & sClave )
{
	return ( mapMemoriaGlobal.contains ( sClave ) );
}

void MemGlobLimpiar ()
{
	mapMemoriaGlobal.clear ();
}

 			}
		}
	}
}
