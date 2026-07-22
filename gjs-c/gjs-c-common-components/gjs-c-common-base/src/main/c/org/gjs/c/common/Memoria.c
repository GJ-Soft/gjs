/******************************************************************************/
/*                                Memoria.cpp                                 */
/*----------------------------------------------------------------------------*/
/* Librería:  GBase                                                           */
/* Versión:   1.0.0                                                           */
/* Fecha:     28/06/2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Fichero de código fuente que contiene la implementación de las rutinas     */
/* para reservar, liberar y trabajar con espacios de memoria.                 */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#include "Memoria.h"

#include "BaseErrores.h"
#include "Finalizacion.h"
#include "Errores.h"




// Limites por defecto (solo se consideran casos 64 y 32 bits):
#if ( defined ( A64 ) )
#	if ( defined ( WIN ) )

#		define MEM_LIM_INF							0x0000000000010000ULL
#		define MEM_LIM_SUP							0x00007FFFFFFFFFFFULL
												  
#	else 

#		define MEM_LIM_INF							0x0000000000010000ULL
#		define MEM_LIM_SUP							0x00007FFFFFFFFFFFULL

#	endif
#else 
#	if ( defined ( WIN ) )

#		define MEM_LIM_INF							0x00010000UL
#		define MEM_LIM_SUP							0x7FFFFFFFUL
												  
#	else 

#		define MEM_LIM_INF							0x00010000UL
#		define MEM_LIM_SUP							0x7FFFFFFFUL

#	endif
#endif	



/* Mensajes de error auxiliares par finalizar la ejecución: */
#define ERR_GRAVE_TXT_MEMORIA				"Error grave de memoria: se ha corrompido el 'heap' del proceso."











#if ( defined ( MODO_DEPURACION ) )

extern void _MemBloqueReservado ( void * p_vDir, unsigned long ulTam );
extern void _MemBloqueLiberado ( void * p_vDir, unsigned long ulTam );

#endif




// Pendientew: Para el caso de WINDOWS una rutina que utilice HeapWalk para liberar todos los bloques de memoria pendientes
// de ser liberados:

//PENDIENTE: Info memoria: The HeapWalk function enumerates the memory blocks in a specified heap.



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
					ERROR_ESTABLECER ( ERR_MEMORIA_INVALIDA );
					FinalizarEjecucion ( ERR_GRAVE_TXT_MEMORIA );
				}
				else
				{
					ERROR_ESTABLECER ( ERR_MEMORIA_INSUFICIENTE );
				}
			}
		}
		else
		{
			p_vBloque = NULL;
			ERROR_ESTABLECER ( ERR_MEMORIA_INVALIDA );
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
			ERROR_ESTABLECER ( ERR_MEMORIA_INSUFICIENTE );
		}
#	  endif
	}
	else
	{
		p_vBloque = NULL;
		ERROR_ESTABLECER ( ERR_PARAMETROS );
	}
	return ( p_vBloque );
}

void * MemReservarVector ( int iNumElems, int iNumBytesElem )
{
	return ( MemReservar ( iNumElems * iNumBytesElem ) );
}

void * MemReservarTabla ( int iNumFilas, int iNumColumnas, int iNumBytesElem )
{
	return ( MemReservar ( iNumFilas * iNumColumnas * iNumBytesElem ) );
}

int MemRedimensionar ( void ** p_p_vBloque, int iNumBytes )
{
	void *	p_vBloque;
	int		iRes;
#  if ( defined ( WIN ) )
	HANDLE  hMem;
#  endif

	iRes = 0;
	if ( iNumBytes > 0 )
	{
		p_vBloque = *p_p_vBloque;
		if ( ES_NULO ( p_vBloque ) )
		{
			*p_p_vBloque = MemReservar ( iNumBytes );
			if ( ES_VALIDO ( *p_p_vBloque ) )
			{
				iRes = 1;
			}
			else
			{
				iRes = 0;
			}
		}
		else
		{

#	  if ( defined ( WIN ) )
			hMem = GetProcessHeap ();
			if ( hMem != NULL )
			{
				*p_p_vBloque = (void *) HeapReAlloc ( hMem, HEAP_ZERO_MEMORY, p_vBloque, iNumBytes );
				if ( ES_VALIDO ( *p_p_vBloque ) )
				{
					iRes = 1;
#				  if ( defined ( MODO_DEPURACION ) )
					_MemBloqueReservado ( *p_p_vBloque, (unsigned long) iNumBytes );
#				  endif
				}
				else
				{
					if ( HeapValidate ( hMem, 0, NULL ) == FALSE )
					{
						// Error grave por heap del proceso corrupto:
						ERROR_ESTABLECER ( ERR_MEMORIA_INVALIDA );
						FinalizarEjecucion ( ERR_GRAVE_TXT_MEMORIA );
					}
					else
					{
						ERROR_ESTABLECER ( ERR_MEMORIA_INSUFICIENTE );
					}
				}
			}
			else
			{
				ERROR_ESTABLECER ( ERR_MEMORIA_INVALIDA );
			}
#	  else
			*p_p_vBloque = (void *) realloc ( p_vBloque, iNumBytes );
			if ( ES_VALIDO ( p_p_vBloque ) )
			{
				iRes = 1;
#			  if ( defined ( MODO_DEPURACION ) )
				_MemBloqueReservado ( *p_p_vBloque, (unsigned long) iNumBytes );
#			  endif
			}
			else
			{
				ERROR_ESTABLECER ( ERR_MEMORIA_INSUFICIENTE );
			}
#	  endif
		}
	}
	else
	{
		ERROR_ESTABLECER ( ERR_PARAMETROS );
	}
	return ( iRes );
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
		if ( MemEsValida ( p_vBloque ) == 1 )
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
				//ERROR_ESTABLECER ( ERR_MEMORIA_INVALIDA );
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

int MemLiberarCadena ( char ** p_p_cCadena )
{
	return ( MemLiberar ( (void **) p_p_cCadena ) );
}

int MemLiberarUnicode ( unichar ** p_p_cCadena )
{
#  if ( defined ( WIN ) )
	int		iByte;
	int		iRes;
	void *	p_vBloque;
	byte *	p_byBloque;
	int		iNumBytes;
	HANDLE  hMem;

	if ( ES_VALIDO ( p_p_cCadena ) )
	{
		p_vBloque = (void *) *p_p_cCadena;
		if ( MemEsValida ( p_vBloque ) == 1 )
		{
			p_byBloque = (byte *) p_vBloque;
			if ( *(p_byBloque + 1) == 0x00 )
			{
				// Puede ser unicode:
				iByte = 0;
				while ( *(p_byBloque + iByte) != 0x00 )
				{
					*(p_byBloque + iByte + 1) = 0x20;
					iByte = iByte + 2;
				}
				*(p_byBloque + iByte) = 0x20;

				hMem = GetProcessHeap ();
				if ( hMem != NULL )
				{
					iNumBytes = HeapSize ( hMem, 0, (LPVOID) p_vBloque );
					if ( iNumBytes > 0 )
					{
						HeapFree ( hMem, 0, (LPVOID) p_vBloque );
#					  if ( defined ( MODO_DEPURACION ) )
				 		_MemBloqueLiberado ( p_vBloque, (unsigned long) iNumBytes );
#					  endif
						*p_p_cCadena = NULL;
						iRes = 1;
					}
					else
					{
						iRes = 0;
						ERROR_ESTABLECER ( ERR_MEMORIA_INVALIDA );
					}
				}
				else
				{
					iRes = 0;
				}
			}
			else
			{
				// No es unicode:
				iRes = MemLiberar ( (void **) p_p_cCadena );
			}
		}
		else
		{
			// Ya es un puntero nulo o no valido:
			iRes = 1;
			*p_p_cCadena = NULL;
			ERROR_ESTABLECER ( ERR_MEMORIA_INVALIDA );
		}
	}
	else
	{
		iRes = 0;
		ERROR_ESTABLECER ( ERR_PARAMETROS );
	}
	return ( iRes );
# else
	return ( MemLiberar ( (void **) p_p_cCadena ) );
# endif
}

void MemLimpiar ( void * p_vBloque, int iNumBytes )
{
	if ( ( iNumBytes > 0 ) && ( MemEsValida ( p_vBloque ) == 1 ) )
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
		ERROR_ESTABLECER ( ERR_PARAMETROS );
	}
}

void MemLlenar ( void * p_vBloque, byte byValor, int iNumBytes )
{
	if ( ( iNumBytes > 0 ) && ( MemEsValida ( p_vBloque ) == 1 ) )
	{
#	  if ( defined ( WIN ) )
		FillMemory ( (LPVOID) p_vBloque, iNumBytes, byValor );
#	  else
		memset ( p_vBloque, byValor, iNumBytes );
#	  endif
	}
	else
	{
		ERROR_ESTABLECER ( ERR_PARAMETROS );
	}
}

void MemCopiar ( void * p_vDest, void * p_vOrig, int iNumBytes )
{
	if ( ( iNumBytes > 0 ) && ES_VALIDO ( p_vDest ) && ES_VALIDO ( p_vOrig ) &&
		 ( MemEsValida ( p_vDest ) == 1 ) )
	{
#	  if ( defined ( WIN ) )
		CopyMemory ( (LPVOID) p_vDest, (CONST VOID *) p_vOrig, iNumBytes  );
#	  else
		memcpy ( p_vDest, p_vOrig, iNumBytes );
#	  endif
	}
	else
	{
		ERROR_ESTABLECER ( ERR_PARAMETROS );
	}
}


int MemEsValida ( void * p_vDireccion )
{
	int	iRes;

	if ( ES_VALIDO ( p_vDireccion ) )
	{
		if ( ( (uintptr_t) p_vDireccion >= (uintptr_t) MEM_LIM_INF ) && ( (uintptr_t)  p_vDireccion <= (uintptr_t) MEM_LIM_SUP ) )
		{
#	  if ( defined ( VC ) )
			if ( IsBadReadPtr ( p_vDireccion, sizeof ( unsigned int ) ) == 0 )
			{
				iRes = 1;
			}
			else
			{
				iRes = 0;
			}
#	  else
			iRes = 1;
#	  endif
		}
		else
		{
			iRes = 0;
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}


int MemEsIgual ( void * p_vBloque1, void * p_vBloque2, int iNumBytes )
{
	int		iRes;
	int 	iByte;
	byte * 	p_byBloque1;
	byte * 	p_byBloque2;

	if ( ES_VALIDO ( p_vBloque1 ) && ES_VALIDO ( p_vBloque2 ) && ( iNumBytes >= 0 ) )
	{
		iRes = 1;
		iByte = 0;
		p_byBloque1 = (byte *) p_vBloque1;
		p_byBloque2 = (byte *) p_vBloque2;
		while ( ( iByte < iNumBytes ) && ( iRes == 1 ) )
		{
			if ( p_byBloque1 [ iByte ] !=  p_byBloque2 [ iByte ] )
			{
				iRes = 0;
			}
			iByte = iByte + 1;
		}	
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}


/*
byte MemValorByte ( unsigned long ulDireccion )
{
	byte	byRes;
	byte *	p_byValor;

	p_byValor = (byte *) ulDireccion;
	if ( MemValida ( p_byValor ) == 1 )
	{
		byRes = * p_byValor;
	}
	else
	{
		byRes = 0x00;
	}
	return ( byRes );
}
*/



