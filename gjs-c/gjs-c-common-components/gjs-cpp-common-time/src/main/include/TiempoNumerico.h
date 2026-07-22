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

#ifndef _ORG_GJS_C_CC_CPP_TIEMPONUMERICO_H
#define _ORG_GJS_C_CC_CPP_TIEMPONUMERICO_H



namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {








// ALgunas rutinas generales:
unsigned long TiempoNumSegundos ( int iD, int iH, int iMi, int iS );
long TiempoHoraSolarEsp ( long lFecha, long lHora );





// Tiempo formateado:
double TmpFormConstruir ( long lFecha, long lHora );
double TmpFormConstruirExt ( int iA, int iM, int iD, int iH, int iMi, int iS );

void TmpFormDescomponer ( double dTiempo, long * p_lFecha, long * p_lHora );
void TmpFormDescomponerExt ( double dTiempo, int * p_iA, int * p_iM, int * p_iD, int * p_iH, int * p_iMi, int * p_iS );


long long TmpFormConstruirLL ( long lFecha, long lHora );
long long TmpFormConstruirExtLL ( int iA, int iM, int iD, int iH, int iMi, int iS );
      
void TmpFormDescomponerLL ( long long llTiempo, long * p_lFecha, long * p_lHora );
void TmpFormDescomponerExtLL ( long long llTiempo, int * p_iA, int * p_iM, int * p_iD, int * p_iH, int * p_iMi, int * p_iS );



double TmpFormObtenerValor ( double dTiempo );
double TmpFormEstablecerValor ( double dValor );
bool TmpFormEsValido ( double dTiempo );

long TmpFormFecha ( double dTiempo );
long TmpFormHora ( double dTiempo );

int TmpFormAnos ( double dTiempo );
int TmpFormMeses ( double dTiempo );
int TmpFormDias ( double dTiempo );
int TmpFormHoras ( double dTiempo);
int TmpFormMinutos ( double dTiempo );
int TmpFormSegundos ( double dTiempo );



double TmpFormObtenerValorLL ( long long llTiempo );
long long TmpFormEstablecerValorLL ( double dValor );
bool TmpFormEsValidoLL ( long long llTiempo );

long TmpFormFechaLL ( long long llTiempo );
long TmpFormHoraLL ( long long llTiempo );

int TmpFormAnosLL ( long long llTiempo );
int TmpFormMesesLL ( long long llTiempo );
int TmpFormDiasLL ( long long llTiempo );
int TmpFormHorasLL ( long long llTiempo);
int TmpFormMinutosLL ( long long llTiempo );
int TmpFormSegundosLL ( long long llTiempo );





 			}
		}
	}
}


#endif


