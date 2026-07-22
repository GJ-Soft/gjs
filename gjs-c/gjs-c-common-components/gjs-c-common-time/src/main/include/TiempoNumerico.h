/******************************************************************************/
/*                              TiempoNumerico.h                              */
/*----------------------------------------------------------------------------*/
/* Librería:  Tiempo                                                          */
/* Versión:   3.0.0                                                           */
/* Fecha:     25/03/2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Fichero de cabecera que contiene los prototipos de unas cuantas rutinas    */
/* para la transformación de fechas y horas en formato numérico pero que      */
/* es manejable numéricamente, en otro que sí lo es. Tambien incluyen otras   */
/* rutinas para operar con fechas, así como algunas de consulta sobre el      */
/* calendario.                                                                */
/* El tiempo numéricamente manejable es un valor continuo en segundos o       */
/* días que han transcurrido desde el primer segundo del año 1 de nuestro     */
/* calendario.                                                                */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#ifndef _ORG_GJS_C_CC_TIEMPONUMERICO_H
#define _ORG_GJS_C_CC_TIEMPONUMERICO_H



#include <Precompilacion.h>








// ALgunas rutinas generales:
unsigned long TiempoNumSegundos ( int iD, int iH, int iMi, int iS );
long TiempoHoraSolarEsp ( long lFecha, long lHora );





// Tiempo formateado:
double TmpFormConstruir ( long lFecha, long lHora );
double TmpFormConstruirExt ( int iA, int iM, int iD, int iH, int iMi, int iS );

void TmpFormDescomponer ( double dTiempo, long * p_lFecha, long * p_lHora );
void TmpFormDescomponerExt ( double dTiempo, int * p_iA, int * p_iM, int * p_iD, int * p_iH, int * p_iMi, int * p_iS );

#if ( defined ( LLONG ) )
llong TmpFormConstruirLL ( long lFecha, long lHora );
llong TmpFormConstruirExtLL ( int iA, int iM, int iD, int iH, int iMi, int iS );
      
void TmpFormDescomponerLL ( llong llTiempo, long * p_lFecha, long * p_lHora );
void TmpFormDescomponerExtLL ( llong llTiempo, int * p_iA, int * p_iM, int * p_iD, int * p_iH, int * p_iMi, int * p_iS );

#endif

double TmpFormObtenerValor ( double dTiempo );
double TmpFormEstablecerValor ( double dValor );
int TmpFormEsValido ( double dTiempo );

long TmpFormFecha ( double dTiempo );
long TmpFormHora ( double dTiempo );

int TmpFormAnos ( double dTiempo );
int TmpFormMeses ( double dTiempo );
int TmpFormDias ( double dTiempo );
int TmpFormHoras ( double dTiempo);
int TmpFormMinutos ( double dTiempo );
int TmpFormSegundos ( double dTiempo );

#if ( defined ( LLONG ) )

double TmpFormObtenerValorLL ( llong llTiempo );
llong TmpFormEstablecerValorLL ( double dValor );
int TmpFormEsValidoLL ( llong llTiempo );

long TmpFormFechaLL ( llong llTiempo );
long TmpFormHoraLL ( llong llTiempo );

int TmpFormAnosLL ( llong llTiempo );
int TmpFormMesesLL ( llong llTiempo );
int TmpFormDiasLL ( llong llTiempo );
int TmpFormHorasLL ( llong llTiempo);
int TmpFormMinutosLL ( llong llTiempo );
int TmpFormSegundosLL ( llong llTiempo );

#endif




#endif


