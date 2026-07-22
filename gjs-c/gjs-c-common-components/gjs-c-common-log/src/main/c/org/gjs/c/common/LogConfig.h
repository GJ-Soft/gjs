#ifndef _ORG_GJS_C_CC_C_LOG_CONFIG_H
#define _ORG_GJS_C_CC_C_LOG_CONFIG_H

#include <Base.h>


#include <Texto.h>
#include <Tiempo.h>
#include <Ficheros.h>
#include <Sistema.h>
#include <Aplicacion.h>


#include <NivelesLog.h>

	
#define LOG_MAX_TAM_LINEA					511
#define LOG_MAX_LINEAS						30000
#define LOG_PREF_NOM_FICHERO_DEF			"Log"
#define LOG_EXT_NOM_FICHERO_DEF				"log"
#define LOG_FORM_NOM_FICHERO_DEF			"%s%s.log"  // Proceso, Fecha-hora.
#define LOG_MIN_TAM_NOM_FICHERO_DEF			18
#define LOG_FORMATO_LINEA					"[%s: %s] - %s"  // Proceso, Fecha-hora, Texto.
#define LOG_FORMATO_LINEA_2					"[%s] - %s"  // Fecha-hora, Texto.


#define LOG_MSJ_TXT_INICIO					"Iniciado bloque de anotacion en el fichero"
#define LOG_MSJ_TXT_FINAL					"Finalizado bloque de anotacion en el fichero"

#define LOG_TXT_NIVEL_INFORMACION			"INFOR"
#define LOG_TXT_NIVEL_AVISO					"AVISO"
#define LOG_TXT_NIVEL_ERROR					"ERROR"

#define LOG_TXT_CONSULTA_SQL				"Consulta SQL"
#define LOG_TXT_CONSULTA_CAMPOS_SQL			"Campos"
#define LOG_TXT_CONSULTA_TABLAS_SQL			"Tablas"
#define LOG_TXT_CONSULTA_CONDIC_SQL			"Condiciones"

#define LOG_TXT_NOMBRE_DEFECTO				"aplicacion"



#endif
