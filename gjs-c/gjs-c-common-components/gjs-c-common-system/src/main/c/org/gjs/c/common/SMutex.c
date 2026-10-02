

#include "SMutex.h"

#include "SistemaConfig.h"





void _SMtxInicializar ( SMutex * p_mtxObj, int iMaxVal );
void _SMtxFinalizar ( SMutex * p_mtxObj );




SMutex * SMtxCrear ( const char * p_cNombre )
{
	return ( SMtxCrearExt ( p_cNombre, 1 ) );
}

SMutex * SMtxCrearExt ( const char * p_cNombre, int iMaxVal )
{
	SMutex * p_mtxObj;
	
	p_mtxObj = (SMutex *) MemReservar ( sizeof ( SMutex ) );
	if ( ES_VALIDO ( p_mtxObj ) )
	{
#  if ( defined ( POSIX ) )
        if ( CadEmpiezaPor ( p_cNombre,  "/" ) == 0 )
        {
			p_mtxObj->p_cNombre = CadCrear ( CadLongitud ( p_cNombre ) + 1 );
			CadCopiarConFormato ( p_mtxObj->p_cNombre, "/%s", p_cNombre);
        }
		else
		{
			p_mtxObj->p_cNombre = CadDuplicar ( p_cNombre );
		}
#  else
		p_mtxObj->p_cNombre = CadDuplicar ( p_cNombre );
#  endif
        _SMtxInicializar ( p_mtxObj, iMaxVal );
	}
	return ( p_mtxObj );
}

void SMtxDestruir ( SMutex ** p_p_mtxObj )
{
	SMutex * p_mtxObj;
	
	if ( ES_VALIDO ( p_p_mtxObj ) )
	{
		p_mtxObj = *p_p_mtxObj;
		if ( ES_VALIDO ( p_mtxObj ) )
		{
			_SMtxFinalizar (  p_mtxObj );
			MemLiberar ( (void **) &(p_mtxObj->p_cNombre) );
			MemLiberar ( (void **) p_p_mtxObj );
		}
	}
}

const char * SMtxNombre ( SMutex * p_mtxObj )
{
	const char * p_cRes;
	
	if ( ES_VALIDO ( p_mtxObj ) )
	{
		p_cRes = p_mtxObj->p_cNombre;
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

int SMtxEsValido ( SMutex * p_mtxObj )
{
	int iRes;

	if ( ES_VALIDO ( p_mtxObj ) )
	{
#	  if ( defined ( WIN ) )
		if ( ES_MANEJADOR_VALIDO ( p_mtxObj->hMutex ) )
#	  elif ( defined ( POSIX ) )
		// NOTA: Es una dirección de un espacio reservado del sistema:
		if ( p_mtxObj->p_semMutex != NULL )
#	 else
		if ( p_mtxObj->iMutex >= 0 )
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
		
int SMtxHayAcceso ( SMutex * p_mtxObj )
{
	int iRes;

	if ( ES_VALIDO ( p_mtxObj ) )
	{
		iRes = p_mtxObj->iAcceso;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SMtxHaSidoCreado ( SMutex * p_mtxObj )
{
	int iRes;

	if ( ES_VALIDO ( p_mtxObj ) )
	{
		iRes = p_mtxObj->iCreado;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SMtxEsperarAcceso ( SMutex * p_mtxObj )
{
	int		iRes;
# if ( defined ( WIN ) )
	DWORD	dwRes;
# endif

	if ( SMtxEsValido ( p_mtxObj ) == 1 ) 
	{
		if ( p_mtxObj->iAcceso == 0 )
		{
#		  if ( defined ( WIN ) )
			dwRes = WaitForSingleObject ( p_mtxObj->hMutex, INFINITE );
			if ( dwRes == WAIT_OBJECT_0 )
#		  elif ( defined ( POSIX ) )
			if ( sem_wait ( p_mtxObj->p_semMutex ) == 0 )
#		  else
			if ( 0 )
#		  endif
			{
				p_mtxObj->iAcceso = 1;
				iRes = 1;
			}
			else
			{
				iRes = 0;
			}
		}
		else
		{
			iRes = 1;
		}

		if ( iRes == 1 )
		{
			p_mtxObj->iNivelesAcceso = p_mtxObj->iNivelesAcceso + 1;
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SMtxAcceder ( SMutex * p_mtxObj )
{
    int     iRes;
# if ( defined ( WIN ) )
    DWORD   dwRes;
# endif

	if ( SMtxEsValido ( p_mtxObj ) == 1 ) 
	{
		if ( p_mtxObj->iAcceso == 0 )
        {
#         if ( defined ( WIN ) )
			dwRes = WaitForSingleObject ( p_mtxObj->hMutex, 1 );
            if ( dwRes == WAIT_OBJECT_0 )
#         elif ( defined ( POSIX ) )
             if ( sem_trywait ( p_mtxObj->p_semMutex ) == 0 )
#         else
			if ( 0 )
#         endif
			{
				p_mtxObj->iAcceso = 1;
                iRes = 1;
			}
			else
			{
				iRes = 0;
			}
		}
		else
		{
			 iRes = 1;
		}

		if ( iRes == 1 )
		{
			p_mtxObj->iNivelesAcceso = p_mtxObj->iNivelesAcceso + 1;
		}
    }
    else
    {
        iRes = 0;
    }
    return ( iRes );
}

int SMtxDejarLibre ( SMutex * p_mtxObj )
{
	int	iRes;

	if ( SMtxEsValido ( p_mtxObj ) == 1 ) 
	{
		if ( p_mtxObj->iAcceso == 1 )
		{
			p_mtxObj->iNivelesAcceso = p_mtxObj->iNivelesAcceso - 1;

			if ( p_mtxObj->iNivelesAcceso <= 0 )
			{
#			  if ( defined ( WIN ) )
				if ( ReleaseMutex ( p_mtxObj->hMutex ) != 0 )
#			  elif ( defined ( POSIX ) )
				if ( sem_post ( p_mtxObj->p_semMutex ) == 0 )
#			  else
				if ( 1 )
#			  endif
				{
					p_mtxObj->iAcceso = 0;
					iRes = 1;
					p_mtxObj->iNivelesAcceso = 0;
				}
				else
				{
					p_mtxObj->iNivelesAcceso = 1;
					iRes = 0;
				}
			}
			else
			{
				iRes = 1;
			}
		}
		else
		{
			iRes = 1;
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

void _SMtxInicializar ( SMutex * p_mtxObj, int iMaxVal )
{
	if ( ES_VALIDO ( p_mtxObj ) )
	{
#	 if ( defined ( WIN ) )
		p_mtxObj->hMutex = NULL;
#	 elif ( defined ( POSIX ) )
		p_mtxObj->p_semMutex = NULL;
#	 else
		p_mtxObj->iMutex = -1;
#	 endif
		p_mtxObj->iAcceso = 0;
		p_mtxObj->iCreado = 0;
		p_mtxObj->iNivelesAcceso = 0;

#	  if ( defined ( WIN ) )
		p_mtxObj->hMutex = OpenMutex ( SYNCHRONIZE, TRUE, p_mtxObj->p_cNombre );
		if ( ES_MANEJADOR_NULO ( p_mtxObj->hMutex ) )
		{
			p_mtxObj->hMutex = CreateMutex ( NULL, FALSE, p_mtxObj->p_cNombre );
			if ( ES_MANEJADOR_VALIDO ( p_mtxObj->hMutex ) )
			{
				p_mtxObj->iCreado = 1;
			}
		}
		if ( ES_MANEJADOR_VALIDO ( p_mtxObj->hMutex ) )
		{
			if ( iMaxVal <= 0 )
			{
				p_mtxObj->iNivelesAcceso = 1;
			}
		}
#	  elif ( defined ( POSIX ) )
		p_mtxObj->p_semMutex = sem_open ( p_mtxObj->p_cNombre, 0x0 );
		if ( p_mtxObj->p_semMutex == SEM_FAILED )
		{
			p_mtxObj->p_semMutex = sem_open ( p_mtxObj->p_cNombre, O_CREAT, 0777, iMaxVal );
			if ( p_mtxObj->p_semMutex == SEM_FAILED )
			{
				p_mtxObj->p_semMutex = NULL;
			}
			else
			{
				p_mtxObj->iCreado = 1;
			}
		}
		if ( ES_VALIDO ( p_mtxObj->p_semMutex ) )
		{
			if ( iMaxVal <= 0 )
			{
				p_mtxObj->iNivelesAcceso = 1;
			}
		}
#  else
		p_mtxObj->iMutex = -1;
#  endif
	}
}

void _SMtxFinalizar ( SMutex * p_mtxObj )
{
	if ( ES_VALIDO ( p_mtxObj ) )
	{
		SMtxDejarLibre ( p_mtxObj );
#	  if ( defined ( WIN ) )
		if (ES_MANEJADOR_VALIDO ( p_mtxObj->hMutex ) )
		{
			CloseHandle ( p_mtxObj->hMutex );
		}
#	  elif ( defined ( POSIX ) )
		if ( p_mtxObj->p_semMutex != NULL )
		{
			sem_close ( p_mtxObj->p_semMutex );
			p_mtxObj->p_semMutex = NULL;
		}
		if ( p_mtxObj->iCreado == 1 )
		{
			sem_unlink ( p_mtxObj->p_cNombre );
		}
#	  else
		p_mtxObj->iMutex = -1;
#	 endif
	}
}

