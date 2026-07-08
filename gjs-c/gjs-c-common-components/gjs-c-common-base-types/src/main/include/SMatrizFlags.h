#ifndef _ORG_GJS_C_CC_C_COMMON_SMATRIZFLAGS_H
#define _ORG_GJS_C_CC_C_COMMON_SMATRIZFLAGS_H




#include <SBuffer.h>





typedef struct
{
	SBuffer *			p_bufContenido;
	unsigned long		ulNumFilas;
	unsigned long		ulNumColumnas;

} SMatrizFlags;






SMatrizFlags * SMatFlgCrear ( unsigned long	ulNumFilas, unsigned long ulNumColumnas ); 

void SMatFlgDestruir ( SMatrizFlags ** p_p_matfObj );

int SMatFlgEsValida ( SMatrizFlags * p_matfObj ); 
unsigned long SMatFlgNumFilas ( SMatrizFlags * p_matfObj ); 
unsigned long SMatFlgNumColumnas ( SMatrizFlags * p_matfObj ); 


int SMatFlgFlag ( SMatrizFlags * p_matfObj, unsigned long ulFil, unsigned long ulCol );
int SMatFlgFlagEstaActivo ( SMatrizFlags * p_matfObj, unsigned long ulFil, unsigned long ulCol );
int SMatFlgActivarFlag ( SMatrizFlags * p_matfObj, unsigned long ulFil, unsigned long ulCol );
int SMatFlgDesactivarFlag ( SMatrizFlags * p_matfObj, unsigned long ulFil, unsigned long ulCol );

int SMatFlgLimpiar ( SMatrizFlags * p_matfObj );

#endif

