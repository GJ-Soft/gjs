/******************************************************************************/
/*                               Mensajes.cpp                                */
/*----------------------------------------------------------------------------*/
/* Librer�a:  Aplicacion                                                      */
/* Versi�n:   3.0.0                                                           */
/* Fecha:     25/03/2008                                                      */
/* Autor:     Gin�s Jim�nez S�nchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripci�n:                                                               */
/* Fichero de c�digo fuente que contiene la implementaci�n de la clase de     */
/* datos CMesnajes.                                                           */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#include "CppCommonConfig.h"
#include "Mensajes.h"



using namespace std;



namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {



Mensajes::Mensajes () 
{
	mapMensajes = map<int, string> ();	
}

Mensajes::~Mensajes ()
{
	Limpiar ();
}

bool Mensajes::Insertar ( int iCodigo, const string & sTexto )
{
	bool bRes = false;

	if ( ( iCodigo >= 0 ) && ! sTexto.empty() )
	{
		mapMensajes [ iCodigo ] = sTexto;
		bRes = true;
	}
	return ( bRes );
}

bool Mensajes::ExisteCodigo ( int iCodigo ) const
{
	return ( mapMensajes.contains( iCodigo ) );
}

int Mensajes::NumMensajes () const
{
	return ( mapMensajes.size() );
}


const string Mensajes::Texto ( int iCodigo ) const
{
	string sValor = "";
	try 
	{
        sValor = mapMensajes.at( iCodigo );
    }
    catch ( const out_of_range & e )
	{
    }
	return ( sValor );
}

void Mensajes::Limpiar ()
{
	mapMensajes.clear ();
}

bool Mensajes::Cargar ( const string & sFichero )
{
	bool bRes = false;
    std::ifstream fichero ( sFichero ); 
    if ( fichero.is_open() ) 
	{
		string sLinea;

		while ( getline ( fichero, sLinea ) )
		{
			/* Se sanea quitando caracteres no imprimibles (incluido el CR final),
			   pero SIN eliminar la coma separadora ni los espacios del mensaje. */
			sLinea = EliminarCaracteresNoEstandar ( sLinea );
			sLinea = Trim ( sLinea );
			if ( !sLinea.empty () )
			{
				size_t posSep = sLinea.find( ',', 0 );
				if ( posSep	!= string::npos ) 
				{
					string sCodigo = Trim ( sLinea.substr( 0, posSep ) );
					string sMensaje = Trim ( sLinea.substr( posSep + 1 ) );
					if ( EsEntero ( sCodigo ) ) 
					{
						int iCodigo = (int) ToInt( sCodigo );
						mapMensajes [ iCodigo ] = sMensaje;
					}	
				}
			}
		}
		fichero.close();
		bRes = true;
	}
	return ( bRes );
}

string Mensajes::operator [] ( int iCodigo ) const
{
	return ( Texto ( iCodigo ) );
}



 			}
		}
	}
}


