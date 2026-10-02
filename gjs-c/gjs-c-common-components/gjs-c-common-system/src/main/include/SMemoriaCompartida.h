#ifndef _ORG_GJS_C_CC_SMEMORIACOMPARTIDA_H
#define	_ORG_GJS_C_CC_SMEMORIACOMPARTIDA_H




#include <BaseConfig.h>

#include <SMutex.h>



typedef struct   
{
		SMutex * p_mutexObj;
#	  if ( defined ( WIN ) )
		HANDLE	hFichero;
#	  else
		int		iFichero;
#	  endif
		void *	p_vDatos;
		int		iNumBytes;
		
} SMemoriaCompartida;		


SMemoriaCompartida * SMemCmpCrear ( const char * p_cNombre, int iTam );

void SMemCmpDestruir ( SMemoriaCompartida ** p_p_memcObj );

const char * SMemCmpNombre ( SMemoriaCompartida * p_memcObj );
int SMemCmpTam ( SMemoriaCompartida * p_memcObj );


void * SMemCmpDatos ( SMemoriaCompartida * p_memcObj );

int SMemCmpAbrir ( SMemoriaCompartida * p_memcObj );
void SMemCmpCerrar ( SMemoriaCompartida * p_memcObj );

int SMemCmpEsValida ( SMemoriaCompartida * p_memcObj );
int SMemCmpEstaAbierta ( SMemoriaCompartida * p_memcObj );

int SMemCmpEsperarAcceso ( SMemoriaCompartida * p_memcObj );
int SMemCmpAcceder ( SMemoriaCompartida * p_memcObj );
int SMemCmpDejarLibre ( SMemoriaCompartida * p_memcObj );
int SMemCmpHayAcceso ( SMemoriaCompartida * p_memcObj );

#endif 
