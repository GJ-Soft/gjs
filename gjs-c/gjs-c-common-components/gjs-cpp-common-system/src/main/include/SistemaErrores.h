#ifndef _ORG_GJS_C_CC_CPP_SISTEMAERRORES_H
#define _ORG_GJS_C_CC_CPP_SISTEMAERRORES_H




#include <string>

#include <SistemaTiposErrores.h>



namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {

bool SisHayError ( int iRefrescar = 1 );
bool SisHayErrorDeMemoriaAgotada ( int iRefrescar = 1 );
int SisErrTipo ();
int SisErrCodigo ();
std::string SisErrDescripcion (); // int iError = 0 );
std::string SisErrMensaje ( int iMostrarCodigo = 0 ); 
std::string SisErrMensajeExt ( const std::string & sModulo = "", const std::string & sRutina = "" ); 
void SisErrImprimir (); 
void SisErrLimpiar ();

int SisMaxError ();

void SisErrApilar ( const std::string & sModulo = "", const std::string & sRutina = "", int iRefrescar = 1 );
void SisErrImprimirPila ();
void SisErrLimpiarPila ();


 			}
		}
	}
}

#endif





