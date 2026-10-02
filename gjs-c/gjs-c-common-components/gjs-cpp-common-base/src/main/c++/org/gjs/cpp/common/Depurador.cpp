/* BaseConfig.h va PRIMERO, antes que cualquier otra cabecera: en modo WIN es
   quien mete winsock2.h, y tiene que llegar antes de que nada arrastre
   sys/types.h. El <string> de las cabeceras de aqui abajo ya lo hace, via
   pthread.h, y entonces Cygwin declara el select POSIX y winsock2 choca. */
#include "BaseConfig.h"

#include "Depurador.h"
#include "InfoMemoria.h"



using namespace std;


namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {






#if ( defined ( MODO_DEPURACION_2 ) )

#include <map>

	static int _g_iGesClsIniciado = 0;

	static map<string, int> _g_mapInstancias;

	void _GesClsInicializar ();
	int _GesClsBuscar ( const string & sNombre );
	void _GesClsAltaInstancia ( const string & sNombre );
	void _GesClsBajaInstancia ( const string & sNombre );


void _GesClsInicializar ()
{
	_g_mapInstancias.clear ();
	_g_iGesClsIniciado = 1;
}

int _GesClsBuscar ( const string & sNombre )
{
	int iRes = 0;
	map<string, int>::iterator it = _g_mapInstancias.find ( sNombre );
	if ( it != _g_mapInstancias.end () )
	{
		iRes = it->second;
	}
	return ( iRes );
}

void _GesClsAltaInstancia ( const string & sNombre )
{
	if ( _g_iGesClsIniciado == 0 )
	{
		_GesClsInicializar ();
	}
	_g_mapInstancias[ sNombre ] = _g_mapInstancias[ sNombre ] + 1;
}

void _GesClsBajaInstancia ( const string & sNombre )
{
	if ( _g_iGesClsIniciado == 1 )
	{
		map<string, int>::iterator it = _g_mapInstancias.find ( sNombre );
		if ( ( it != _g_mapInstancias.end () ) && ( it->second > 0 ) )
		{
			it->second = it->second - 1;
		}
	}
}

#endif






#if ( defined ( MODO_DEPURACION ) )

extern void _MemObjetoCreado ( unsigned long ulTam, unsigned int uiObjetos );
extern void _MemObjetoDestruido ( unsigned long ulTam, unsigned int uiObjetos );

#endif





Depurador::Depurador () : Objeto ()
{
#  if ( defined ( MODO_DEPURACION ) )
	p_vDirObjeto = (void *) this;
	iTamObjeto = 0;
	iObjetos = 0;
	iEliminando = 0;
	iError = 0;
	ActualizarObjeto ( Objeto::getTipo (), (void *) this, (int) Objeto::getTam () );
#  endif
}


Depurador::~Depurador ()
{
#if ( defined ( MODO_DEPURACION ) )
	if ( iEliminando == 0 )
	{
		iEliminando = 1;
		_MemObjetoDestruido ( (unsigned long) iTamObjeto, iObjetos );
#	  if ( defined ( MODO_DEPURACION_2 ) )
		string sNombre = Objeto::getTipo ();
		if ( iObjetos == 1 )
		{
			cout << "{Eliminando objeto de clase " << sNombre
				 << " (Tamano: " << iTamObjeto << ")}" << endl;
		}
		else
		{
			cout << "{Eliminando objeto de clase " << sNombre
				 << " compuesto por " << iObjetos << " objetos simples (Tamano: " << iTamObjeto << ")}" << endl;
		}
		cout << "\t[Objetos totales: " << MemNumObjetosActuales ()
			 << ", Memoria ocupada: " << MemReservadaObjetos () << "]" << endl;

		_GesClsBajaInstancia ( sNombre );
#	  endif
	}
#endif
}

#if ( defined ( MODO_DEPURACION ) )

bool Depurador::EsTipo ( const string & sNombre )
{
	bool bRes;

	if ( Objeto::getTipo().compare ( sNombre ) == 0 )
	{
		bRes = true;
	}
	else
	{
		bRes = false;
	}
	return ( bRes );
}

bool Depurador::EsTipo ( const char * p_cNombre )
{
	bool bRes;

	if ( ( p_cNombre != NULL ) && ( strcmp ( Objeto::getTipo().c_str(), p_cNombre ) == 0 ) )
	{
		bRes = true;
	}
	else
	{
		bRes = false;
	}
	return ( bRes );
}

int Depurador::NumObjetos ()
{
	return ( iObjetos );
}

void * Depurador::DireccionObjeto ()
{
	return ( p_vDirObjeto );
}

int Depurador::Error ()
{
	return ( iError );
}

void Depurador::EstablecerError ( int iError )
{
	this->iError = iError;
}

void Depurador::LimpiarError ()
{
	iError = 0;
}

void Depurador::ActualizarObjeto ( const string & sNombre, void * p_vDirObj, int iTamObj )
{
	if ( ES_VALIDO ( p_vDirObj ) && ( iTamObj > 0 ) )
	{
		iObjetos = iObjetos + 1;
		iTamObjeto = iTamObjeto + iTamObj;

		p_vDirObjeto = p_vDirObj;

#	  if ( defined ( MODO_DEPURACION ) )
		_MemObjetoCreado ( (unsigned long) iTamObj, iObjetos );

		cout << "{Creando objeto de clase " << sNombre << " (Tamano: " << iTamObjeto << ")}" << endl;
		if ( iObjetos == 1 ) 
		{
#		  if ( defined ( MODO_DEPURACION_2 ) )
			_GesClsAltaInstancia ( sNombre );
#		  endif
		}
		else
		{
#		  if ( defined ( MODO_DEPURACION_2 ) )
			_GesClsBajaInstancia ( sNombre );
			_GesClsAltaInstancia ( sNombre );
#		  endif
		}
#	  if ( defined ( MODO_DEPURACION_2 ) )
		cout << "\t[Objetos totales: "  << MemNumObjetosActuales () << " Memoria ocupada: " 
			<<  MemReservadaObjetos () << "]" << endl; 
#	  endif
	}
#endif
}	


#endif


void GesClsImprimirEstado ()
{
#	if ( defined ( MODO_DEPURACION_2 ) )
		if ( _g_iGesClsIniciado == 1 )
		{
			cout << endl << " * Lista de clases utilizadas: " << endl;
			cout << " " << string(70, '-') << endl;
			for ( const pair<const string, int>& par : _g_mapInstancias )
			{
				cout << " Clase: "  <<  left << setw(50) << par.first;
				cout << "Instancias: "  <<  par.second << endl;
			}
			cout << endl << "Total clases: "  << _g_mapInstancias.size() << endl;
			cout << " " << string(70, '-') << endl << endl;
		}
		else
		{
			cout << "Gestor de clases no inicializado" << endl;
		}
#	endif
}




 			}
		}
	}
}




