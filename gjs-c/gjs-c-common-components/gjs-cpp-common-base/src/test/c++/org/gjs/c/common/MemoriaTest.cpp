#include "CppBase.h"


#include <iostream>



using namespace std;
using namespace org::gjs::cpp::common;





static bool TestMemoria01 ()
{
	cout << "Test Memoria01:" << endl;
	bool bRes = true;

	// Peticiones de tamano no positivo: deben devolver NULL, nunca basura.
	void * p_vNulo = MemReservar ( 0 );
	if ( p_vNulo != NULL )
	{
		cout << "Error caso 1: reserva de 0 bytes no es NULL" << endl;
		bRes = false;
	}
	p_vNulo = MemReservar ( -5 );
	if ( p_vNulo != NULL )
	{
		cout << "Error caso 2: reserva negativa no es NULL" << endl;
		bRes = false;
	}
	return ( bRes );
}

static bool TestMemoria02 ()
{
	cout << "Test Memoria02:" << endl;
	bool bRes = true;

	// Reserva valida: memoria no nula e inicializada a cero.
	int iNumBytes = 16;
	unsigned char * p_ucBloque = (unsigned char *) MemReservar ( iNumBytes );
	if ( p_ucBloque == NULL )
	{
		cout << "Error caso 1: no se ha podido reservar" << endl;
		bRes = false;
	}
	else
	{
		for ( int i = 0; i < iNumBytes; i = i + 1 )
		{
			if ( p_ucBloque[ i ] != 0 )
			{
				cout << "Error caso 2: memoria no inicializada a cero" << endl;
				bRes = false;
			}
		}
		// Escribir, limpiar y comprobar que queda a cero de nuevo.
		for ( int i = 0; i < iNumBytes; i = i + 1 )
		{
			p_ucBloque[ i ] = (unsigned char) ( i + 1 );
		}
		MemLimpiar ( p_ucBloque, iNumBytes );
		for ( int i = 0; i < iNumBytes; i = i + 1 )
		{
			if ( p_ucBloque[ i ] != 0 )
			{
				cout << "Error caso 3: MemLimpiar no ha puesto a cero" << endl;
				bRes = false;
			}
		}
		// Liberar: debe devolver 1 y dejar el puntero a NULL.
		int iLib = MemLiberar ( (void **) &p_ucBloque );
		if ( iLib != 1 )
		{
			cout << "Error caso 4: MemLiberar no ha devuelto 1" << endl;
			bRes = false;
		}
		if ( p_ucBloque != NULL )
		{
			cout << "Error caso 5: MemLiberar no ha anulado el puntero" << endl;
			bRes = false;
		}
	}
	return ( bRes );
}

static bool TestMemoria03 ()
{
	cout << "Test Memoria03:" << endl;
	bool bRes = true;

	// Liberar un puntero ya nulo es una operacion valida (idempotente).
	void * p_vBloque = NULL;
	int iLib = MemLiberar ( &p_vBloque );
	if ( iLib != 1 )
	{
		cout << "Error caso 1: liberar puntero nulo deberia devolver 1" << endl;
		bRes = false;
	}
	if ( p_vBloque != NULL )
	{
		cout << "Error caso 2: el puntero deberia seguir a NULL" << endl;
		bRes = false;
	}
	// Un doble puntero nulo es invalido: devuelve 0.
	iLib = MemLiberar ( NULL );
	if ( iLib != 0 )
	{
		cout << "Error caso 3: doble puntero nulo deberia devolver 0" << endl;
		bRes = false;
	}
	return ( bRes );
}

bool TestMemoria ()
{
	bool bRes = true;
	cout << endl << ANSI::AMARILLO << "[Test Memoria]" << ANSI::RESETEAR << endl;
	if ( TestMemoria01() )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout  << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}
	if ( TestMemoria02() )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout  << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}
	if ( TestMemoria03() )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout  << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}
	cout << ANSI::AMARILLO << "[Fin]" << ANSI::RESETEAR << endl;
	return ( bRes );
}
