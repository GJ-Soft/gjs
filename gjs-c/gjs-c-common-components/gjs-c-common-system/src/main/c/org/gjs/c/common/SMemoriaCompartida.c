#include "SMemoriaCompartida.h"
#include "SistemaInformacion.h"

#include "SistemaConfig.h"

#include <SistemaFicheros.h>



SMemoriaCompartida * SMemCmpCrear ( const char * p_cNombre, int iTam )
{
	SMemoriaCompartida * p_memcObj;
	
	p_memcObj = (SMemoriaCompartida *) MemReservar ( sizeof ( SMemoriaCompartida ) );
	if ( ES_VALIDO ( p_memcObj ) )
	{
		p_memcObj->p_mutexObj = SMtxCrear ( p_cNombre );
		if ( SMtxEsValido ( p_memcObj->p_mutexObj ) == 1 )
		{
	#	  if ( defined ( WIN ) )
			p_memcObj->hFichero = NULL;
	#	  else
			p_memcObj->iFichero = 0;
	#	  endif
			p_memcObj->p_vDatos = NULL;	
			if ( iTam > 0 )
			{
				p_memcObj->iNumBytes = iTam;
			}
			else
			{
				p_memcObj->iNumBytes = 0;
			}
		}
		else
		{
			SMemCmpDestruir ( &p_memcObj );
		}
	}
	return ( p_memcObj );
}

void SMemCmpDestruir ( SMemoriaCompartida ** p_p_memcObj )
{
	SMemoriaCompartida * p_memcObj;
	
	if ( ES_VALIDO ( p_p_memcObj ) )
	{
		p_memcObj = *p_p_memcObj;
		if ( ES_VALIDO ( p_memcObj ) )
		{
			SMemCmpCerrar ( p_memcObj );
			SMtxDestruir ( &(p_memcObj->p_mutexObj) );
			MemLiberar ( (void **) p_p_memcObj );
		}
	}
}

const char * SMemCmpNombre ( SMemoriaCompartida * p_memcObj )
{
	const char * p_cRes;
	
	if ( ES_VALIDO ( p_memcObj ) )
	{
		p_cRes = SMtxNombre ( p_memcObj->p_mutexObj );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

void SMemCmpEstablecerNombre ( SMemoriaCompartida * p_memcObj, const char * p_cNombre )
{
	if ( ES_VALIDO ( p_memcObj ) )
	{
		if ( SMemCmpEstaAbierta ( p_memcObj ) == 0 ) 
		{
			// PENDIENTE:
			//SMtxEstablecerNombre ( p_memcObj->p_mutexObj, p_cNombre );
		}
	}
}

int SMemCmpTam ( SMemoriaCompartida * p_memcObj )
{
	int iRes;
	
	if ( ES_VALIDO ( p_memcObj ) )
	{
		iRes = p_memcObj->iNumBytes;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

void SMemCmpEstablecerTam ( SMemoriaCompartida * p_memcObj, int iTam )
{
	if ( ES_VALIDO ( p_memcObj ) && ( iTam >= 0 ) )
	{
		if ( SMemCmpEstaAbierta ( p_memcObj ) == 0 ) 
		{
			p_memcObj->iNumBytes = iTam;
		}
	}
}


void * SMemCmpDatos ( SMemoriaCompartida * p_memcObj )
{
	void * p_vRes;
	
	if ( SMemCmpHayAcceso ( p_memcObj ) == 1 )
	{
			p_vRes = p_memcObj->p_vDatos;
	}
	else
	{
		p_vRes = NULL;
	}
	return ( p_vRes );
}

int SMemCmpAbrir ( SMemoriaCompartida * p_memcObj )
{
	char *	p_cRuta;
	int 	iRes;
	int 	iCreado;

	if ( ES_VALIDO ( p_memcObj ) )
	{
		if ( ( SMemCmpEstaAbierta ( p_memcObj ) == 0 ) && ( SMtxEsValido ( p_memcObj->p_mutexObj ) == 1 ) &&
			 ( p_memcObj->iNumBytes > 0 ) )
		{
			if ( SMtxAcceder ( p_memcObj->p_mutexObj ) == 1 )
			{
				p_cRuta = SisComponerRuta ( SisDirectorioTemporal (), SMtxNombre ( p_memcObj->p_mutexObj ), 0 );
				if ( ES_VALIDO ( p_cRuta ) )
				{
					iRes = 1;
					iCreado = 0;
		#		  if ( defined ( WIN ) )
					p_memcObj->hFichero = CreateFileMapping ( INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, (DWORD) p_memcObj->iNumBytes, (LPSTR) SMtxNombre ( p_memcObj->p_mutexObj ) );
					if ( ES_VALIDO ( p_memcObj->hFichero ) )
					{
						iCreado = 1;
					}
					else
					{
						p_memcObj->hFichero = OpenFileMapping ( FILE_MAP_ALL_ACCESS, FALSE, (LPSTR) SMtxNombre ( p_memcObj->p_mutexObj ) );
					}
					if ( ES_NULO ( p_memcObj->hFichero ) )
		#		  elif ( defined ( POSIX ) )
					p_memcObj->iFichero = shm_open( SMtxNombre ( p_memcObj->p_mutexObj ), O_CREAT | O_EXCL | O_RDWR, 0660 );
					if ( p_memcObj->iFichero >= 0 )
					{
						iCreado = 1;
						ftruncate ( p_memcObj->iFichero, p_memcObj->iNumBytes );
					}
					else
					{
						p_memcObj->iFichero = shm_open( SMtxNombre ( p_memcObj->p_mutexObj ), O_RDWR, 0 );
					}
					if ( p_memcObj->iFichero < 0 )
		#		  else
					p_memcObj->iFichero = open ( p_cRuta, O_CREAT | O_EXCL | O_RDWR, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP );
					if ( p_memcObj->iFichero >= 0 )
					{
						iCreado = 1;
						lseek ( p_memcObj->iFichero, p_memcObj->iNumBytes - 1, SEEK_SET );
						char c = ' ';
						write ( p_memcObj->iFichero, &c, 1 );
					}
					else
					{
						p_memcObj->iFichero = open ( p_cRuta, O_RDWR, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP );
					}
					if ( lseek ( p_memcObj->iFichero, 0, SEEK_END ) < p_memcObj->iNumBytes )
					{
						close ( p_memcObj->iFichero );
						p_memcObj->iFichero = -1;
					}
					if ( p_memcObj->iFichero < 0 )
		#		  endif
					{
						SMtxDejarLibre ( p_memcObj->p_mutexObj );
						iRes = 0;
					}
					else
					{
		#		  if ( defined ( WIN ) )
						p_memcObj->p_vDatos = (void *) MapViewOfFile ( p_memcObj->hFichero, FILE_MAP_WRITE, 0, 0, (DWORD) p_memcObj->iNumBytes );
						if ( p_memcObj->p_vDatos == NULL ) {
		#		  else
						p_memcObj->p_vDatos = (void *) mmap( 0, p_memcObj->iNumBytes, PROT_READ | PROT_WRITE, MAP_SHARED, p_memcObj->iFichero, 0 );
		#			if ( defined ( POSIX ) )
						if ( p_memcObj->p_vDatos == MAP_FAILED ) {
		#			else		
						if ( p_memcObj->p_vDatos == NULL ) {
		#			endif		
		#		  endif
							p_memcObj->p_vDatos = NULL;
						}
						if ( ES_NULO ( p_memcObj->p_vDatos ) )
						{
							iRes = 0;
							SMtxDejarLibre ( p_memcObj->p_mutexObj );
		#		  if ( defined ( WIN ) )
							CloseHandle ( p_memcObj->hFichero );
							p_memcObj->hFichero = NULL;
		#		  else
							close ( p_memcObj->iFichero );
							p_memcObj->iFichero = -1;
		#		  	if ( defined ( POSIX ) )
							shm_unlink ( SMtxNombre ( p_memcObj->p_mutexObj ) );
		#			endif
		#		  endif
						}
					}
					if ( iRes == 0 )
					{
						if ( iCreado == 1 )
						{
							SisEliminarFichero ( p_cRuta );
						}
					}
					MemLiberar ( (void **) &p_cRuta );
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

int SMemCmpAbrirExt ( SMemoriaCompartida * p_memcObj, const char * p_cNombre, int iTam )
{
	int iRes;

	if ( ES_VALIDO ( p_memcObj ) )
	{
		SMemCmpEstablecerNombre ( p_memcObj, p_cNombre );
		SMemCmpEstablecerTam ( p_memcObj, iTam );
		iRes = SMemCmpAbrir ( p_memcObj );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

void SMemCmpCerrar ( SMemoriaCompartida * p_memcObj )
{
	if ( SMemCmpEstaAbierta ( p_memcObj ) == 1 )
	{
		SMtxDejarLibre ( p_memcObj->p_mutexObj );
#	  if ( defined ( WIN ) )
		UnmapViewOfFile ( (LPVOID) p_memcObj->p_vDatos );
		CloseHandle ( p_memcObj->hFichero );
		p_memcObj->hFichero = NULL;
#	  else
		munmap ( p_memcObj->p_vDatos, p_memcObj->iNumBytes );
		close ( p_memcObj->iFichero );
		p_memcObj->iFichero = -1;
#	   if ( defined ( POSIX ) )
		shm_unlink ( SMtxNombre ( p_memcObj->p_mutexObj ) );
#	   endif
#	  endif
		p_memcObj->p_vDatos = NULL;
	}
}

int SMemCmpEsValida ( SMemoriaCompartida * p_memcObj )
{
	int iRes;

	if ( ES_VALIDO ( p_memcObj ) )
	{
		if ( ( SMtxEsValido ( p_memcObj->p_mutexObj ) == 1 ) && ( p_memcObj->iNumBytes > 0 ) )
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

int SMemCmpEstaAbierta ( SMemoriaCompartida * p_memcObj )
{
	int iRes;

	if ( SMemCmpEsValida ( p_memcObj ) == 1 )
	{
		iRes = SMtxHaSidoCreado ( p_memcObj->p_mutexObj );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SMemCmpEsperarAcceso ( SMemoriaCompartida * p_memcObj )
{
	int iRes;

	if ( SMemCmpEstaAbierta ( p_memcObj ) == 1 )
	{
		iRes = SMtxEsperarAcceso ( p_memcObj->p_mutexObj );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SMemCmpAcceder ( SMemoriaCompartida * p_memcObj )
{
	int iRes;

	if ( SMemCmpEstaAbierta ( p_memcObj ) == 1 )
	{
		iRes = SMtxAcceder ( p_memcObj->p_mutexObj );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SMemCmpDejarLibre ( SMemoriaCompartida * p_memcObj )
{
	int iRes;

	if ( SMemCmpEstaAbierta ( p_memcObj ) == 1)
	{
		iRes = SMtxDejarLibre ( p_memcObj->p_mutexObj );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SMemCmpHayAcceso ( SMemoriaCompartida * p_memcObj )
{
	int iRes;

	if ( SMemCmpEstaAbierta ( p_memcObj ) == 1)
	{
		iRes = SMtxHayAcceso ( p_memcObj->p_mutexObj );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}


