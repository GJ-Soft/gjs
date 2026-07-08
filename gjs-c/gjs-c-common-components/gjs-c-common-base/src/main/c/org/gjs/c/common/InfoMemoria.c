/******************************************************************************/
/*                              InfoMemoria.cpp                               */
/*----------------------------------------------------------------------------*/
/* Librería:  GBase                                                           */
/* Versión:   1.0.0                                                           */
/* Fecha:     28/06/2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Fichero de código fuente que contiene la implementación de las rutinas     */
/* de consulta de la memoria dinámica reservada utilizando MemReservar, o     */
/* mediante objetos de clases que hereden de CClase.                          */
/* También contiene rutinas para actualizar los contadores internos, que      */
/* son internas de la librería y no deben conocerse desde fuera.              */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#include "InfoMemoria.h"


//PENDIENTE: incorporar y adaptar a la informacion de mallinfo para GNU:




#if ( defined ( MODO_DEPURACION ) )


unsigned long g_ulNumBloquesReservados = 0;
unsigned long g_ulNumBloquesLiberados = 0;
unsigned long g_ulNumBloques = 0;
unsigned long g_ulTamBloques = 0;


#if ( defined ( MODO_DEPURACION_2 ) )

#	define _MEM_MAX_BLOQUES				65536

	static int _g_iGesMemIniciado = 0;

	typedef struct
	{
		void *			p_vDireccion;
		unsigned long	ulTam;
		int				iLiberado;
	} _SMemBloque;


	_SMemBloque _g_p_mblqTabla [ _MEM_MAX_BLOQUES ]; 
	int _g_iNumBloques;

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

unsigned long MemReservadaTotal ()
{
	return ( g_ulTamBloques );
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
	printf ( "  { Reservado bloque memoria. Dir=%X Tam=%lu }\n", (unsigned int) p_vDir, ulTam ); 
	//fprintf ( stdout, "  { Reservado bloque memoria. Dir=%X Tam=%lu }\n", (unsigned int) p_vDir, ulTam ); 
	_GesMemReservar ( p_vDir, ulTam );
	// Poner aquí las direcciones críticas que se quieran seguir:
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
	printf ( "  { Liberado bloque memoria. Dir=%X Tam=%lu }\n", (unsigned int) p_vDir, ulTam ); 
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
	printf ( "\n" );
	printf ( " * Informe de estado de la memoria:\n" );
	printf (  " -----------------------------------------------------------------------\n" );
	printf ( " Bloques actuales    : [%lu]\n", g_ulNumBloques );
	//printf ( " Bloques reservados  : [%lu]\n", g_ulNumBloquesReservados );
	//printf ( " Bloques liberados   : [%lu]\n", g_ulNumBloquesLiberados );
	printf ( " Memoria bloques     : [%lu]\n", g_ulTamBloques );

# if ( defined ( MODO_DEPURACION_2 ) )
	if ( ( g_ulNumBloques > 0 ) && ( iMostrarBloques == 1 ) )
	{
		int iBloque;

		printf ( "\n" );
		printf ( " Bloques no liberados:\n" );
		for ( iBloque = 0; iBloque < _g_iNumBloques; iBloque = iBloque + 1 )
		{
			if ( ( _g_p_mblqTabla [ iBloque ].p_vDireccion != NULL ) && ( _g_p_mblqTabla [ iBloque ].iLiberado == 0 ) )
			{
				printf ( "   Direccion: %X  (Tam= %lu)\n", (unsigned int) _g_p_mblqTabla [ iBloque ].p_vDireccion, _g_p_mblqTabla [ iBloque ].ulTam );
			}
		}
	}
# endif

	printf ( " -----------------------------------------------------------------------\n\n" );
}

#endif
 







