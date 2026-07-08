
#ifndef _ORG_GJS_C_CC_SMUTEX_H
#define _ORG_GJS_C_CC_SMUTEX_H




#include <BaseConfig.h>



# if ( defined ( WIN ) )
#	include <winnt.h>
# else
#	include <semaphore.h>
# endif







typedef struct 
{
	char *	p_cNombre; 
# if ( defined ( WIN ) )
	HANDLE	hMutex;
# elif ( defined ( POSIX ) )
	sem_t *	p_semMutex;
# else
	int		iMutex;
# endif

	int		iAcceso;
	int		iCreado;
	int		iNivelesAcceso;
	
} SMutex;


SMutex * SMtxCrear ( const char * p_cNombre );
SMutex * SMtxCrearExt ( const char * p_cNombre, int iMaxVal );

void SMtxDestruir ( SMutex ** p_p_mtxObj );

const char * SMtxNombre ( SMutex * p_mtxObj );

int SMtxEsValido ( SMutex * p_mtxObj );
int SMtxHayAcceso ( SMutex * p_mtxObj );
int	SMtxHaSidoCreado ( SMutex * p_mtxObj );

int SMtxEsperarAcceso ( SMutex * p_mtxObj );
int SMtxAcceder ( SMutex * p_mtxObj );
int SMtxDejarLibre ( SMutex * p_mtxObj );


#endif

