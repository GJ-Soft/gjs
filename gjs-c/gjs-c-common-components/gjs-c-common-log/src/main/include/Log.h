#ifndef _ORG_GJS_C_CC_C_LOG_LOG_H
#define _ORG_GJS_C_CC_C_LOG_LOG_H


#include <NivelesLog.h>




#define LOG_PROP_FICHERO				"logFilename"
#define LOG_PROP_DIRECTORIO				"logDirectory"

#define LOG_VAR_DIRECTORIO				"LOG_DIR"




map<string, string> LogPropiedadesDefecto ( const char * p_cNombreFichero = "", const char * p_cDirectorio = "" );

bool LogIni ();
bool LogIni ( const char * p_cRutaFicheroCfg );

// TODO: Por un bug en log4cxx no funciona la substitucion de propiedades y no se pueden usar xml de configuración customizados
bool LogIni ( map<string, string> & mapPropiedades );
bool LogIni ( const char * p_cRutaFicheroCfg, map<string, string> & mapPropiedades );

bool LogIniConsola ( bool bSoloMensaje = false );
bool LogIniFichero ( const char * p_cFicLog, bool consola = false );

void LogFin ();

void LogInfo ( const char * p_cMensaje );
void LogDepuracion ( const char * p_cMensaje );
void LogTraza ( const char * p_cMensaje );
void LogAviso ( const char * p_cMensaje );
void LogError ( const char * p_cMensaje );
void LogFatal ( const char * p_cMensaje );

int LogGetNivel ();
void LogSetNivel ( int iNivel );

#endif
