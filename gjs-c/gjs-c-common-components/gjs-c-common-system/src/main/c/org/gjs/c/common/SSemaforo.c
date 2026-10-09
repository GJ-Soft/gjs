#include "SSemaforo.h"

#include "SistemaConfig.h"



SSemaforo * SSemCrear ( const char * p_cNombre )
{
	return ( SSemCrearExt ( p_cNombre, 1 ) );
}

SSemaforo * SSemCrearExt ( const char * p_cNombre, long lValorMaximo )
{
	SSemaforo * p_semObj;
	
	p_semObj = (SSemaforo *) MemReservar ( sizeof ( SSemaforo ) );
	if ( ES_VALIDO ( p_semObj ) )
	{
		p_semObj->iAlta = 0;
		p_semObj->iCreado = 0;
		/* Debe fijarse tambien para los semaforos con nombre: SSemInicializar
		   (WIN) usa lValMax como contador maximo de CreateSemaphore y 0 es
		   invalido. */
		p_semObj->lValMax = ( lValorMaximo > 0 ) ? lValorMaximo : 0;
#	 if ( defined ( POSIX ) )
        if ( ( CadLongitud ( p_cNombre ) > 0 ) && ( CadEmpiezaPor ( p_cNombre,  "/" ) == 0 ) )
        {
			p_semObj->p_cNombre = CadCrear ( CadLongitud ( p_cNombre ) + 1 );
			CadCopiarConFormato ( p_semObj->p_cNombre, "/%s", p_cNombre );
        }
		else
		{
			p_semObj->p_cNombre = CadDuplicar ( p_cNombre );
		}
#	 else
		p_semObj->p_cNombre = CadDuplicar ( p_cNombre );
# 	 endif
		if ( CadLongitud ( p_semObj->p_cNombre ) > 0 )
		{
#	 if ( defined ( WIN ) )
			/* Y nada mas: OpenSemaphore ya deja el manejador a NULL si falla, asi que
			   no hay que normalizar nada. La rama POSIX de abajo si lo necesita porque
			   sem_open no devuelve NULL sino SEM_FAILED. */
			p_semObj->hSemaforo = OpenSemaphore ( SYNCHRONIZE, 0, p_semObj->p_cNombre );
#	 elif ( defined ( POSIX ) )
			p_semObj->p_semObj = sem_open ( p_semObj->p_cNombre, 0 );
			if ( p_semObj->p_semObj == SEM_FAILED )
			{
				p_semObj->p_semObj = NULL;
			}
#    else
		// TODO:
#    endif
		}
		else
		{
			if ( lValorMaximo > 0 )
			{
				p_semObj->lValMax = lValorMaximo;
#	 if ( defined ( WIN ) )
				p_semObj->hSemaforo = CreateSemaphore ( NULL, p_semObj->lValMax, p_semObj->lValMax, p_semObj->p_cNombre );
#	 elif ( defined ( POSIX ) )
				//  Al ser anónimo, necesitamos reservar memoria para el propio sem_t interno
				p_semObj->p_semObj = (sem_t *) MemReservar ( sizeof ( sem_t ) );
				if ( ES_VALIDO ( p_semObj->p_semObj ) )
				{
					// Inicializamos el semáforo. Usamos '0' asumiendo que es para hilos mutuos.
					// Si requieres que sea entre procesos distintos, este parámetro debe ser 1.
					if ( sem_init ( p_semObj->p_semObj, 0, p_semObj->lValMax ) != 0 )
					{
						MemLiberar ( (void **) &(p_semObj->p_semObj) );
					}
				}
#    else
#    endif

#	 if ( defined ( WIN ) )
				if ( ES_MANEJADOR_VALIDO ( p_semObj->hSemaforo ) )
#	 elif ( defined ( POSIX ) )
				if ( ES_VALIDO ( p_semObj->p_semObj ) )
#    else
				if ( p_semObj->iSemaforo > 0 )
#    endif
				{
					p_semObj->iCreado = 1;
				}
			}
			else
			{
				p_semObj->lValMax = 0;
#	 if ( defined ( WIN ) )
				p_semObj->hSemaforo = NULL;
#	 elif ( defined ( POSIX ) )
				p_semObj->p_semObj = NULL;
#    else
				p_semObj->iSemaforo = -1;
#    endif
			}
		}
	}
	else
	{
		p_semObj = NULL;
	}
	return ( p_semObj );
}

void SSemDestruir ( SSemaforo ** p_p_semObj )
{
	SSemaforo * p_semObj;
	
	if ( ES_VALIDO ( p_p_semObj ) )
	{
		p_semObj = *p_p_semObj;
		if ( ES_VALIDO ( p_semObj ) )
		{
#		 if ( defined ( WIN ) )
			if ( ES_MANEJADOR_VALIDO ( p_semObj->hSemaforo ) )
			{
				CloseHandle ( p_semObj->hSemaforo );
			}
#		 elif ( defined ( POSIX ) )
			if ( p_semObj->p_semObj != NULL )
			{
				sem_close ( p_semObj->p_semObj );
				p_semObj->p_semObj = NULL;
			}
			if ( ( p_semObj->iCreado == 1 ) && ( CadLongitud ( p_semObj->p_cNombre ) > 0 ) )
			{
				sem_unlink ( p_semObj->p_cNombre );
			}
#		 else
			p_semObj->iSemaforo = -1;
#		 endif
			MemLiberar ( (void **) &(p_semObj->p_cNombre) );
			MemLiberar ( (void **) p_p_semObj );
		}
	}
}

const char * SSemNombre ( SSemaforo * p_semObj )
{
	const char * p_cRes;
	
	if ( ES_VALIDO ( p_semObj ) )
	{
		p_cRes = p_semObj->p_cNombre;
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

int SSemEsValido ( SSemaforo * p_semObj )
{
	int iRes;

	if ( ES_VALIDO ( p_semObj ) )
	{
#	 if ( defined ( WIN ) )
		if ( ES_MANEJADOR_VALIDO ( p_semObj->hSemaforo ) )
#	 elif ( defined ( POSIX ) )
		// NOTA: Es una dirección de un espacio reservado del sistema:
		if ( p_semObj->p_semObj != NULL )
#	 else
		if ( p_semObj->iSemaforo >= 0 )
#	 endif
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
		iRes = 0;
	}
	return ( iRes );
}
		
long SSemValorMaximo ( SSemaforo * p_semObj )
{
	long lRes;

	if ( ES_VALIDO ( p_semObj ) )
	{
		lRes = p_semObj->lValMax;
	}
	else
	{
		lRes = 0;
	}
	return ( lRes );
}

int SSemEstaCreado ( SSemaforo * p_semObj )
{
	int iRes;

	if ( ES_VALIDO ( p_semObj ) )
	{
		iRes = p_semObj->iCreado;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SSemAbrir ( SSemaforo * p_semObj )
{
	int iRes;

	if ( ES_VALIDO ( p_semObj ) )
	{
		p_semObj->iCreado = 0;
		if ( CadLongitud ( p_semObj->p_cNombre ) > 0 )
		{
#		  if ( defined ( WIN ) )
			if ( ES_MANEJADOR_NULO ( p_semObj->hSemaforo ) )
			{
				p_semObj->hSemaforo = OpenSemaphore ( SYNCHRONIZE, 0, p_semObj->p_cNombre );
				/* La de fuera comprueba que NO estuviera ya abierto; esta comprueba que
				   la apertura haya ido bien. Las dos son ES_MANEJADOR_*, que es lo que
				   toca con un HANDLE, pero no dicen lo mismo. */
				if ( ES_MANEJADOR_VALIDO ( p_semObj->hSemaforo ) )
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
				iRes = 0;
			}
#		  elif ( defined ( POSIX ) )
			/* El guardian de la rama WIN: si el semaforo ya esta en uso no se toca y
			   se devuelve 0. Aqui no estaba, asi que un segundo SSemAbrir pisaba el
			   descriptor anterior y lo perdia sin cerrarlo. */
			if ( ES_NULO ( p_semObj->p_semObj ) )
			{
				p_semObj->p_semObj = sem_open ( p_semObj->p_cNombre, 0x0 );
				if ( p_semObj->p_semObj == SEM_FAILED )
				{
					p_semObj->p_semObj = NULL;
				}
				if ( ES_VALIDO ( p_semObj->p_semObj ) )
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
				iRes = 0;
			}
#		  else
			p_semObj->iSemaforo = -1;
			iRes = 0;
#		  endif
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

int SSemInicializar ( SSemaforo * p_semObj )
{
	int iRes;

	if ( ES_VALIDO ( p_semObj ) )
	{
		p_semObj->iCreado = 0;
		if ( CadLongitud ( p_semObj->p_cNombre ) > 0 )
		{
#		  if ( defined ( WIN ) )
			if ( ES_MANEJADOR_NULO ( p_semObj->hSemaforo ) ) 
			{
				p_semObj->hSemaforo = CreateSemaphore ( NULL, p_semObj->lValMax, p_semObj->lValMax, p_semObj->p_cNombre );
				if ( ES_MANEJADOR_VALIDO ( p_semObj->hSemaforo ) )
				{
					p_semObj->iCreado = 1;
					iRes = 1;
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
#		  elif ( defined ( POSIX ) )
			/* Mismo guardian que la rama WIN de aqui arriba: si ya esta en uso, no se
			   toca y se devuelve 0. */
			if ( ES_NULO ( p_semObj->p_semObj ) )
			{
				p_semObj->p_semObj = sem_open ( p_semObj->p_cNombre, O_CREAT, 0777, p_semObj->lValMax );
				if ( p_semObj->p_semObj == SEM_FAILED )
				{
					p_semObj->p_semObj = NULL;
				}
				if ( ES_VALIDO ( p_semObj->p_semObj ) )
				{
					p_semObj->iCreado = 1;
					iRes = 1;
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
#		  else
			p_semObj->iSemaforo = -1;
			iRes = 0;
#		  endif
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

int SSemAlta ( SSemaforo * p_semObj, int iEsperar )
{
	int 	iRes;
# if ( defined ( WIN ) )
	DWORD 	dwRet;
	DWORD 	dwEspera;
# endif
	if ( SSemEsValido ( p_semObj ) == 1 )
	{
		if ( p_semObj->iAlta == 1 )
		{
			iRes = 1;
		}
		else 
		{
#		  if ( defined ( WIN ) )
			dwEspera = 0;
			dwRet = WaitForSingleObject ( p_semObj->hSemaforo, dwEspera );
			if ( dwRet == WAIT_OBJECT_0 )
			{
				iRes = 1;
				p_semObj->iAlta = 1;
			}
			else
			{
				iRes = 0;
			}
#         elif ( defined ( POSIX ) )
			if ( iEsperar == 0 )
			{
				if ( sem_trywait ( p_semObj->p_semObj ) == 0 )
				{
					iRes = 1;
					p_semObj->iAlta = 1;
				}
				else
				{
					iRes = 0;
				}
			}
			else
			{
				if ( sem_wait ( p_semObj->p_semObj ) == 0 )
				{
					iRes = 1;
					p_semObj->iAlta = 1;
				}
				else
				{
					iRes = 0;
				}
			}
#         else
			iRes = 0;
#         endif
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SSemBaja ( SSemaforo * p_semObj )
{
	int iRes;

	if ( SSemEsValido ( p_semObj ) == 1 )
	{
		if ( p_semObj->iAlta == 0 )
		{
			iRes = 1;
		}
		else 
		{
#		  if ( defined ( WIN ) )
			long lValor;
		
			if ( ReleaseSemaphore ( p_semObj->hSemaforo, 1, &lValor ) != 0 )
#		  elif ( defined ( POSIX ) )
			if ( sem_post ( p_semObj->p_semObj ) == 0 )
#		  else
			if ( 1 )
#		  endif
			{
				iRes = 1;
				p_semObj->iAlta = 0;
			}
			else
			{
				iRes = 0;
			}
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SSemDadoDeAlta ( SSemaforo * p_semObj )
{
	int iRes;
	
	if ( ES_VALIDO ( p_semObj ) )
	{
		iRes = p_semObj->iAlta;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

