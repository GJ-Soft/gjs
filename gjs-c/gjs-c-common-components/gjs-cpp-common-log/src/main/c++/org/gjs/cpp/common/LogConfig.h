#ifndef _ORG_GJS_C_CC_CPP_LOG_CONFIG_H
#define _ORG_GJS_C_CC_CPP_LOG_CONFIG_H



#include <CppBase.h>
#include <CppCommonIo.h>
#include <CppCommonSystem.h>
#include <CppCommonTime.h>
#include <CppCommonSupport.h>

#include <locale.h>
#include <fstream>


/* Claves del fichero de configuracion. */
#define LOG_PROP_CONSOLA_ACTIVA			"log.consola.activa"
#define LOG_PROP_FICHERO_ACTIVO			"log.fichero.activo"
#define LOG_PROP_NOMBRE					"log.nombre"
#define LOG_PROP_DIRECTORIO				"log.directorio"

#define LOG_FIC_CFG_DEF					"config/logjs.properties"

#define LOG_TMP_RECONFIGURACION			3600000

#define LOG_PATRON_DEF 					"[%d{yyyy-MM-dd HH:mm:ss}] %c %-5p - %m%n"
#define	LOG_PATRON_FECHA_DEF			"'.'yyyy-MM-dd"
#define LOG_PATRON_CONSOLA_MIN			"%m%n"

#define LOG_MAX_TAM_LINEA					511
#define LOG_MAX_LINEAS						30000
#define LOG_MAX_LINEAS_MENSAJE				10
/* Mismo valor que LOG_TXT_NOMBRE_DEFECTO del stack C, para que las dos
   implementaciones escriban lo mismo cuando nadie da nombre. */
#define LOG_TXT_NOMBRE_DEFECTO				"aplicacion"

#define LOG_PREF_NOM_FICHERO_DEF			"Log"
/* Para nombres de fichero: sin ":" ni espacios, que no valen en Windows. */
/* Sin segundos a proposito: el time_point de FechaHora tiene precision de
   nanosegundos y %S los saca todos, con lo que cada arranque creaba un
   fichero distinto con un nombre como ...-170001.506208900.log. */
#define LOG_FORMATO_FECHA_FICHERO			"{:%Y%m%d-%H%M}"
#define LOG_EXT_NOM_FICHERO_DEF				"log"
#define LOG_FORM_NOM_FICHERO_DEF			"%s%s.log"  // Proceso, Fecha-hora.
#define LOG_MIN_TAM_NOM_FICHERO_DEF			18
#define LOG_FORMATO_LINEA					"[%s: %s] - %s"  // Proceso, Fecha-hora, Texto.
#define LOG_FORMATO_LINEA_2					"[%s] - %s"  // Fecha-hora, Texto.


#define LOG_MSJ_TXT_INICIO					"Iniciado bloque de anotacion en el fichero"
#define LOG_MSJ_TXT_FINAL					"Finalizado bloque de anotacion en el fichero"
/* Formato de std::format: FechaHora::Cadena lo pasa a vformat. */
#define LOG_FORMATO_FECHA_HORA				"{:%Y-%m-%d %H:%M:%S}"
/* Minimo de texto por linea, para que la particion avance aunque la
   cabecera sea mas larga que la linea. */
#define LOG_MIN_TAM_TEXTO_LINEA				32

#define LOG_MSJ_TXT_TRUNCADO				"(mensaje truncado: demasiadas lineas)"
#define LOG_MSJ_TXT_CAMBIO_FICHERO			"(Continua en el fichero siguiente)."
#define LOG_MSJ_TXT_CONTINUACION_FICHERO	"(Continuacion del fichero anterior)."

#define LOG_TXT_NIVEL_INFORMACION			"INFOR"
#define LOG_TXT_NIVEL_AVISO					"AVISO"
#define LOG_TXT_NIVEL_ERROR					"ERROR"
#define LOG_TXT_NIVEL_DEPURACION			"DEPUR"
#define LOG_TXT_NIVEL_TRAZA					"TRAZA"
#define LOG_TXT_NIVEL_TODOS					"TODOS"
#define LOG_TXT_NIVEL_NINGUNO				"NINGU"






#endif
