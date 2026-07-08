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
	try
	{
		sValor = mapMemoriaGlobal [ sClave ];
	}
	catch ( ... )
	{
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
