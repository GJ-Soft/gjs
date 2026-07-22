/******************************************************************************/
/*                              InfoMemoria.cpp                               */
/*----------------------------------------------------------------------------*/
/* Librer�a:  GBase                                                           */
/* Versi�n:   1.0.0                                                           */
/* Fecha:     28/06/2008                                                      */
/* Autor:     Gin�s Jim�nez S�nchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripci�n:                                                               */
/* Fichero de c�digo fuente que contiene la implementaci�n de las rutinas     */
/* de consulta de la memoria din�mica reservada utilizando MemReservar, o     */
/* mediante objetos de clases que hereden de CClase.                          */
/* Tambi�n contiene rutinas para actualizar los contadores internos, que      */
/* son internas de la librer�a y no deben conocerse desde fuera.              */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#include "InfoMemoria.h"


//PENDIENTE: incorporar y adaptar a la informacion de mallinfo para GNU:




#if ( defined ( MODO_DEPURACION ) )


using namespace std;



namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {


/* Variables y tipos globales que podr�n servir el el futuro para controlar la utilizaci�n de memoria: */
static unsigned long g_ulNumBloquesReservados = 0;
static unsigned long g_ulNumBloquesLiberados = 0;
static unsigned long g_ulNumBloques = 0;
static unsigned long g_ulTamBloques = 0;

/* Contadores de la memoria ocupada por los objetos (clases que heredan de Depurador): */
static unsigned long g_ulNumObjetos = 0;
static unsigned long g_ulTamObjetos = 0;


#if ( defined ( MODO_DEPURACION_2 ) )

#	define _MEM_MAX_BLOQUES				65536

	static int _g_iGesMemIniciado = 0;

	typedef struct
	{
		void *			p_vDireccion;
		unsigned long	ulTam;
		int				iLiberado;
	} _SMemBloque;


	static _SMemBloque _g_p_mblqTabla [ _MEM_MAX_BLOQUES ]; 
	static int _g_iNumBloques;

	void _GesMemInicializar ();
	int _GesMemBuscar ( void * p_vDir );
	void _GesMemReservar ( void * p_vDir, unsigned long ulTam );
	void _GesMemLiberar ( void * p_vDir );

#endif



// PENDIENTE:
// 3) De momento no se contabiliza la memoria reservada para GNU-unix/linux/dos al
// no tener una rutina similar a _msize o HeapSize.



unsigned long MemReservadaBloques ()
{
	return ( g_ulTamBloques );
}

unsigned long MemReservadaObjetos ()
{
	return ( g_ulTamObjetos );
}

unsigned long MemReservadaTotal ()
{
	return ( g_ulTamBloques + g_ulTamObjetos );
}

unsigned long MemNumObjetosActuales ()
{
	return ( g_ulNumObjetos );
}

unsigned long MemNumBloquesReservados ()
{
	return ( g_ulNumBloquesReservados );
}

unsigned long MemNumBloquesLiberados ()
{
	return ( g_ulNumBloquesLiberados );
}

unsigned long MemNumBloquesActuales ()
{
	return ( g_ulNumBloques );
}

void _MemBloqueReservado ( void * p_vDir, unsigned long ulTam )
{
# if ( defined ( MODO_DEPURACION_2 ) )
	cout << "  { Reservado bloque memoria. Dir=" << (unsigned int) p_vDir << " Tam=" << ulTam << " }" << endl; 
	//fprintf ( stdout, "  { Reservado bloque memoria. Dir=%X Tam=%lu }\n", (unsigned int) p_vDir, ulTam ); 
	_GesMemReservar ( p_vDir, ulTam );
	// Poner aqu� las direcciones cr�ticas que se quieran seguir:
	/*
	if ( ( ( (unsigned int) p_vDir == 0x14B820 ) && ( ulTam == 36 ) ) ||
		 ( ( (unsigned int) p_vDir == 0x148288 ) && ( ulTam == 20 ) ) ||
		 ( ( (unsigned int) p_vDir == 0x1ACA08 ) && ( ulTam == 5 ) ) )
	{
		fprintf ( stdout, " ***** Direccion critica *****\n" );
		//char c = getchar ();
	}
	*/
# endif
	g_ulTamBloques = g_ulTamBloques + ulTam;
	g_ulNumBloques = g_ulNumBloques + 1;
	g_ulNumBloquesReservados = g_ulNumBloquesReservados + 1;
}

void _MemBloqueLiberado ( void * p_vDir, unsigned long ulTam )
{
# if ( defined ( MODO_DEPURACION_2 ) )
	cout << "{ Liberado bloque memoria. Dir=" << (unsigned int) p_vDir << " Tam=" << ulTam << " }" << endl; 
	//fprintf ( stdout, "  { Liberado bloque memoria. Dir=%X Tam=%lu }\n", (unsigned int) p_vDir, ulTam ); 
	_GesMemLiberar ( p_vDir );
# endif
	if ( g_ulTamBloques > ulTam )
	{
		g_ulTamBloques = g_ulTamBloques - ulTam;
	}
	else
	{
		g_ulTamBloques = 0;
	}
	g_ulNumBloquesLiberados = g_ulNumBloquesLiberados + 1;
	if ( g_ulNumBloques > 0 )
	{
		g_ulNumBloques = g_ulNumBloques - 1;
	}
}


void _MemObjetoCreado ( unsigned long ulTam, unsigned int uiObjetos )
{
	(void) uiObjetos;
	g_ulTamObjetos = g_ulTamObjetos + ulTam;
	g_ulNumObjetos = g_ulNumObjetos + 1;
}

void _MemObjetoDestruido ( unsigned long ulTam, unsigned int uiObjetos )
{
	(void) uiObjetos;
	if ( g_ulTamObjetos > ulTam )
	{
		g_ulTamObjetos = g_ulTamObjetos - ulTam;
	}
	else
	{
		g_ulTamObjetos = 0;
	}
	if ( g_ulNumObjetos > 0 )
	{
		g_ulNumObjetos = g_ulNumObjetos - 1;
	}
}


#if ( defined ( MODO_DEPURACION_2 ) )

void _GesMemInicializar ()
{
	int iBloque;

	for ( iBloque = 0; iBloque < _MEM_MAX_BLOQUES; iBloque = iBloque + 1 )
	{
		_g_p_mblqTabla [ iBloque ].p_vDireccion = NULL;
		_g_p_mblqTabla [ iBloque ].ulTam = 0;
		_g_p_mblqTabla [ iBloque ].iLiberado = 0;
	}
	_g_iGesMemIniciado = 1;
}

int _GesMemBuscar ( void * p_vDir )
{
	int iBloque;
	int iEnc;

	if ( _g_iGesMemIniciado == 1 )
	{
		iBloque = 0; 
		iEnc = 0;
		while ( ( iBloque < _g_iNumBloques ) && ( iEnc == 0 ) ) 
		{
			if ( _g_p_mblqTabla [ iBloque ].p_vDireccion == p_vDir )
			{
				iEnc = 1;
			}
			else
			{
				iBloque = iBloque + 1;
			}
		}
		if ( iEnc == 0 )
		{
			iBloque = -1;
		}
	}
	else
	{
		iBloque = -1;
	}
	return ( iBloque );
}

void _GesMemReservar ( void * p_vDir, unsigned long ulTam )
{
	int iBloque;

	if ( _g_iGesMemIniciado == 0 )
	{
		_GesMemInicializar ();
	}

	iBloque = _GesMemBuscar ( p_vDir );
	if ( iBloque < 0 ) 
	{
		if ( _g_iNumBloques < _MEM_MAX_BLOQUES )
		{
			_g_iNumBloques = _g_iNumBloques + 1;
			iBloque = _g_iNumBloques - 1;
			_g_p_mblqTabla [ iBloque ].p_vDireccion = p_vDir;
			_g_p_mblqTabla [ iBloque ].iLiberado = 0;
			_g_p_mblqTabla [ iBloque ].ulTam = ulTam;
		}
	}
	else
	{
		_g_p_mblqTabla [ iBloque ].iLiberado = 0;
		_g_p_mblqTabla [ iBloque ].ulTam = ulTam;
	}
}

void _GesMemLiberar ( void * p_vDir )
{
	int iBloque;

	if ( _g_iGesMemIniciado == 1 )
	{
		iBloque = _GesMemBuscar ( p_vDir );
		if ( iBloque >= 0 ) 
		{
			_g_p_mblqTabla [ iBloque ].iLiberado = 1;
		}
	}
}


#endif



void MemImprimirInforme ( int iMostrarBloques )
{
	cout << endl;
	cout << " * Informe de estado de la memoria:" << endl;
	cout <<  string(70, '-') << endl;
	cout << " Bloques actuales    : " << g_ulNumBloques << endl;
	cout << " Bloques reservados  : " << g_ulNumBloquesReservados << endl;
	cout << " Bloques liberados   : " << g_ulNumBloquesLiberados << endl;
	cout << " Memoria bloques     : " << g_ulTamBloques << endl;

# if ( defined ( MODO_DEPURACION_2 ) )
	if ( ( g_ulNumBloques > 0 ) && ( iMostrarBloques == 1 ) )
	{
		int iBloque;

		cout << endl;
		cout << " Bloques no liberados:\n" << endl;
		for ( iBloque = 0; iBloque < _g_iNumBloques; iBloque = iBloque + 1 )
		{
			if ( ( _g_p_mblqTabla [ iBloque ].p_vDireccion != NULL ) && ( _g_p_mblqTabla [ iBloque ].iLiberado == 0 ) )
			{
				cout << "   Direccion: " << hex
					<< (uintptr_t) _g_p_mblqTabla [ iBloque ].p_vDireccion
					<< dec << " (Tam= " << _g_p_mblqTabla [ iBloque ].ulTam << ")" << endl;
			}
		}
	}
# endif

	cout << string(70, '-') << endl;
}




 			}
		}
	}
}


#endif
 







