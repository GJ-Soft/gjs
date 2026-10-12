
/* BaseConfig.h va PRIMERO, antes que cualquier otra cabecera: en modo WIN es
   quien mete winsock2.h, y tiene que llegar antes de que nada arrastre
   sys/types.h. El <string> de las cabeceras de aqui abajo ya lo hace, via
   pthread.h, y entonces Cygwin declara el select POSIX y winsock2 choca. */
#include "BaseConfig.h"

#include "Memoria.h"
#include "Excepcion.h"

#include <new>





/* Mensajes de error auxiliares par finalizar la ejecución: */
#define ERR_GRAVE_TXT_MEMORIA				"Error grave de memoria: se ha corrompido el 'heap' del proceso."










namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {


#if ( defined ( MODO_DEPURACION ) )

extern void _MemBloqueReservado ( void * p_vDir, unsigned long ulTam );
extern void _MemBloqueLiberado ( void * p_vDir, unsigned long ulTam );

#endif




/* Con new[] y delete[], igual en todos los modos. Antes era malloc / free en
   POSIX y HeapAlloc / HeapFree en WIN. Los bloques son unsigned char [], asi que
   solo los libera MemLiberar: ni delete sin [], ni free.

   En MODO_DEPURACION se cuentan los bloques, pero ya no los bytes liberados:
   de un bloque de new[] no se puede preguntar el tamano, que antes se sacaba
   de malloc_usable_size o de HeapSize. */
void * MemReservar ( int iNumBytes )
{
	void *	p_vBloque = NULL;

	if ( iNumBytes > 0 )
	{
		// Los () finales lo dejan a cero, como antes el memset o HEAP_ZERO_MEMORY.
		p_vBloque = new ( std::nothrow ) unsigned char [ iNumBytes ] ();
		if ( ES_VALIDO ( p_vBloque ) )
		{
#		  if ( defined ( MODO_DEPURACION ) )
			_MemBloqueReservado ( p_vBloque, (unsigned long) iNumBytes );
#		  endif
		}
		else
		{
			throw ( Excepcion ( "Memoria", "MemReservar", "Memoria insuficiente" ) );
		}
	}
	else
	{
		//throw ( Excepcion ( "Memoria", "MemReservar", "Error de parametros" ) );
	}
	return ( p_vBloque );
}


int MemLiberar ( void ** p_p_vBloque )
{
	int				iRes;

	if ( ES_VALIDO ( p_p_vBloque ) )
	{
		void * p_vBloque = *p_p_vBloque;
		if ( ES_VALIDO ( p_vBloque ) )
		{
			// El aviso va antes de liberar: despues, el valor del puntero ya es
			// indeterminado, y _MemBloqueLiberado lo imprime y lo busca.
#		  if ( defined ( MODO_DEPURACION ) )
			_MemBloqueLiberado ( p_vBloque, 0 );
#		  endif
			delete [] static_cast < unsigned char * > ( p_vBloque );
		}
		// Si ya era nulo no hay nada que liberar, y tambien vale.
		iRes = 1;
		*p_p_vBloque = NULL;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

void MemLimpiar ( void * p_vBloque, int iNumBytes )
{
	if ( ( iNumBytes > 0 ) && ES_VALIDO ( p_vBloque ) )
	{
#	  if ( defined ( WIN ) )
		//if ( IsBadWritePtr ( p_vBloque, 1 ) == 0 )
		//{
		ZeroMemory ( (LPVOID) p_vBloque, iNumBytes  );
		//}
#	  else
		memset ( p_vBloque, 0, iNumBytes );
#	  endif
	}
	else
	{
		// throw ( Excepcion ( "Memoria", "MemLimpiar", "Error de parametros" ) );
	}
}


            }
		}
	}
}


