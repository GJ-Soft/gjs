#ifndef _ORG_GJS_C_CC_SPERIODO_H
#define _ORG_GJS_C_CC_SPERIODO_H






#include <TiposPeriodicidad.h>




typedef struct 
{
	int				iPeriodicidad;
	long			lFechaOcurrencia;

} SPeriodo; 




SPeriodo * SPerdCrear ( int iPeriodicidad, long lFechaInicial );

void SPerdDestruir ( SPeriodo ** p_perdObj );

int SPerdEsValido ( SPeriodo * p_perdObj );

int SPerdPeriodicidad ( SPeriodo * p_perdObj );

int SPerdEsAnual ( SPeriodo * p_perdObj );
int SPerdEsMensual ( SPeriodo * p_perdObj );
int SPerdEsTrimestral ( SPeriodo * p_perdObj );
int SPerdEsSemanal ( SPeriodo * p_perdObj );
int SPerdEsDiario ( SPeriodo * p_perdObj );

int SPerdHaOcurrido ( SPeriodo * p_perdObj );
long SPerdFechaOcurrencia ( SPeriodo * p_perdObj );
long SPerdFechaProximaOcurrencia ( SPeriodo * p_perdObj );
int SPerdOcurreHastaFecha ( SPeriodo * p_perdObj, long lFecha );
int SPerdVecesQueOcurreHastaFecha ( SPeriodo * p_perdObj, long lFecha );
int SPerdVecesQueHaOcurrido ( SPeriodo * p_perdObj );

void SPerdIniciar ( SPeriodo * p_perdObj, long lFechaInicial );
int SPerdActualizarHastaFecha ( SPeriodo * p_perdObj, long lFecha ); 
int SPerdActualizarHastaHoy ( SPeriodo * p_perdObj ); 

#endif
