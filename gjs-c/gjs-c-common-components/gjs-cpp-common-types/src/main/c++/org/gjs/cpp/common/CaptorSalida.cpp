#include "CommonTypesConfig.h"
#include "CaptorSalida.h"
#include <Sistema.h>


using namespace std;

namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {

CaptorSalida::CaptorSalida ()
{
}

CaptorSalida::~CaptorSalida ()
{
	Fin ();
	vecLineas.clear ();
}

void CaptorSalida::Ini ()
{
	if ( ! bActivado )
	{
		p_bufViejo = cout.rdbuf ();
		cout.rdbuf ( ssContenido.rdbuf () );
		vecLineas.clear ();
		bActivado = true;
	}
}

void CaptorSalida::Fin ()
{
	if ( bActivado )
	{
		string sLinea;
		while ( std::getline ( ssContenido, sLinea ) )
		{
			vecLineas.push_back ( sLinea );
		}
		cout.rdbuf ( p_bufViejo );
		p_bufViejo = NULL;
		cout << ssContenido.str ();
		ssContenido.clear ();
		bActivado = false;
	}
}

bool CaptorSalida::EstaActivado ()
{
	return ( bActivado );
}

vector<string> CaptorSalida::getLineas ()
{
	return ( vecLineas );
}

 			}
		}
	}
}
