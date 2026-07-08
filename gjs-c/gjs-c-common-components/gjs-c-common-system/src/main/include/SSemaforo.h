#ifndef _ORG_GJS_C_CC_SSEMAFORO_H
#define _ORG_GJS_C_CC_SSEMAFORO_H


#include <BaseConfig.h>


# if ( defined ( WIN ) )
#	include <winnt.h>
# else
#	include <semaphore.h>
# endif




typedef struct 
{
# if ( defined ( WIN ) )
	HANDLE	hSemaforo;
# elif ( defined ( POSIX ) )
	sem_t *	p_semObj;
# else
	int		iSemaforo;
# endif
	int   	iAlta;
	long   	lValMax;
	char * 	p_cNombre;
	int   	iCreado;
} SSemaforo;


SSemaforo * SSemCrear ( const char * p_cNombre );
SSemaforo * SSemCrearExt ( const char * p_cNombre, long lValorMaximo );

void SSemDestruir ( SSemaforo ** p_p_semObj );

const char * SSemNombre ( SSemaforo * p_semObj );
long SSemValorMaximo ( SSemaforo * p_semObj );

int SSemEsValido ( SSemaforo * p_semObj );
int SSemEstaCreado ( SSemaforo * p_semObj );

int SSemAbrir ( SSemaforo * p_semObj );
int SSemInicializar ( SSemaforo * p_semObj );

int SSemAlta ( SSemaforo * p_semObj, int iEsperar );
int SSemBaja ( SSemaforo * p_semObj );
int SSemDadoDeAlta ( SSemaforo * p_semObj );



#endif 
