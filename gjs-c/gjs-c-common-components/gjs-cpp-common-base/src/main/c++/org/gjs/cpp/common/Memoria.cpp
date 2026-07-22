
#include "Memoria.h"
#include "Excepcion.h"

#include "BaseConfig.h"





/* Mensajes de error auxiliares par finalizar la ejecuci�n: */
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




void * MemReservar ( int iNumBytes )
{
	void *	p_vBloque;
#  if ( defined ( WIN ) )
	HANDLE  hMem;
#  endif

	if ( iNumBytes > 0 )
	{
#	  if ( defined ( WIN ) )
		hMem = GetProcessHeap ();
		if ( hMem != NULL )
		{
			p_vBloque = (void *) HeapAlloc ( hMem, HEAP_ZERO_MEMORY, iNumBytes );
			if ( ES_VALIDO ( p_vBloque ) )
			{
#			  if ( defined ( MODO_DEPURACION ) )
				_MemBloqueReservado ( p_vBloque, (unsigned long) iNumBytes );
#			  endif
			}
			else
			{
				if ( HeapValidate ( hMem, 0, NULL ) == FALSE )
				{
					// Error grave por heap del proceso corrupto:
					throw ( Excepcion ( "Memoria", "MemReservar", "Memoria invalida" ) );
				}
				else
				{
					throw ( Excepcion ( "Memoria", "MemReservar", "Memoria insuficiente" ) );
				}
			}
		}
		else
		{
			p_vBloque = NULL;
			throw ( Excepcion ( "Memoria", "MemReservar", "Memoria invalida" ) );
		}
#	  else
		p_vBloque = (void *) malloc ( iNumBytes );
		if ( ES_VALIDO ( p_vBloque ) )
		{
			memset ( p_vBloque, 0, iNumBytes );
#		  if ( defined ( MODO_DEPURACION ) )
			_MemBloqueReservado ( p_vBloque, (unsigned long) iNumBytes );
#		  endif
		}
		else
		{
			throw ( Excepcion ( "Memoria", "MemReservar", "Memoria insuficiente" ) );
		}
#	  endif
	}
	else
	{
		p_vBloque = NULL;
		//throw ( Excepcion ( "Memoria", "MemReservar", "Error de parametros" ) );
	}
	return ( p_vBloque );
}


int MemLiberar ( void ** p_p_vBloque )
{
	int				iRes;
	void *			p_vBloque;
#  if ( defined ( WIN ) )
	HANDLE			hMem;
#  endif
#  if ( defined ( MODO_DEPURACION ) )
	int				iNumBytes;
#  endif

	if ( ES_VALIDO ( p_p_vBloque ) )
	{
		p_vBloque = *p_p_vBloque;
		if ( ES_VALIDO ( p_vBloque ) )
		{
#		  if ( defined ( WIN ) )
			hMem = GetProcessHeap ();
			if ( hMem != NULL )
			{
#			  if ( defined ( MODO_DEPURACION ) )
				iNumBytes = HeapSize ( hMem, 0, (LPVOID) p_vBloque );
#			  endif
				HeapFree ( hMem, 0, (LPVOID) p_vBloque );
#			  if ( defined ( MODO_DEPURACION ) )
				_MemBloqueLiberado ( p_vBloque, (unsigned long) iNumBytes );
#			  endif
				iRes = 1;
			}
			else
			{
				iRes = 0;
				// throw ( Excepcion ( "Memoria", "MemLiberar", "Memoria invalida" ) );
			}
			*p_p_vBloque = NULL;

#		  elif ( defined ( GNU ) )

			iRes = 1;
#		  if ( defined ( MODO_DEPURACION ) )
				iNumBytes = malloc_usable_size ( p_vBloque );
#		  endif
            free ( p_vBloque );
			*p_p_vBloque = NULL;
#		  if ( defined ( MODO_DEPURACION ) )
 			_MemBloqueLiberado ( p_vBloque, (unsigned long) iNumBytes );
#		  endif

#		  else // No GNU:
			iRes = 1;
#		  if ( defined ( MODO_DEPURACION ) )
				iNumBytes = malloc_usable_size ( p_vBloque );
#		  endif
			free ( p_vBloque );
			*p_p_vBloque = NULL;
#		   if ( defined ( MODO_DEPURACION ) )
			_MemBloqueLiberado ( p_vBloque, (unsigned long) iNumBytes );
#		   endif
#		 endif
		}
		else
		{
			// Ya es un puntero nulo o no valido:
			iRes = 1;
			*p_p_vBloque = NULL;
		}
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


