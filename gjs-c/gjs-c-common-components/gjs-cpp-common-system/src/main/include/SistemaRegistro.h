/******************************************************************************/
/*                             SistemaRegistro.h                              */
/*----------------------------------------------------------------------------*/
/* Librería:  Sistema                                                         */
/* Versión:   3.0.0                                                           */
/* Fecha:     25/03/2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Fichero de cabecera que contiene la definición de algunas rutinas de       */
/* carácter general de manejo del registro de Windows.                        */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#ifndef _ORG_GJS_C_CC_CPP_SISTEMAREGISTRO_H
#define _ORG_GJS_C_CC_CPP_SISTEMAREGISTRO_H



#include <Precompilacion.h>

#if ( defined ( WIN ) )

/* HKEY y los demas tipos del registro salen de windows.h, que entra por
   BaseConfig.h. Precompilacion.h por si solo no lo trae. */
#include <BaseConfig.h>

#include <RegistroConstantes.h>

#include <string>


namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {


/* Las cadenas entran por referencia constante y salen por valor. Una cadena
   vacia, o un cero en las numericas, quiere decir que no se encontro. El int
   que la version C usaba como cierto/falso pasa a bool.

   El selector de clave principal ( las REG_CLV_* de RegistroConstantes.h ) va
   como argumento con valor por defecto. La cabecera de 2008 traia dos funciones
   por operacion, la simple y la Ext, pero la implementacion las tiene fundidas
   desde hace tiempo en una sola con el selector al final: con el valor por
   defecto se conservan las dos formas de llamarla sin duplicar nada. Mismo
   idioma que el SisEjecutarComando de SistemaComandos.h. */
bool SisRegExisteClave ( const std::string & sClave, int iClavePrinc = REG_CLV_LOCAL_MACHINE );
bool SisRegCrearClave ( const std::string & sClave, int iClavePrinc = REG_CLV_LOCAL_MACHINE );
bool SisRegEliminarClave ( const std::string & sClave, int iClavePrinc = REG_CLV_LOCAL_MACHINE );

std::string SisRegObtValorCadena ( const std::string & sClave, const std::string & sValor, int iClavePrinc = REG_CLV_LOCAL_MACHINE );
unsigned long SisRegObtValorNumerico ( const std::string & sClave, const std::string & sValor, int iClavePrinc = REG_CLV_LOCAL_MACHINE );

bool SisRegEstValorCadena ( const std::string & sClave, const std::string & sValor, const std::string & sDato, int iClavePrinc = REG_CLV_LOCAL_MACHINE );
bool SisRegEstValorNumerico ( const std::string & sClave, const std::string & sValor, unsigned long ulDato, int iClavePrinc = REG_CLV_LOCAL_MACHINE );
bool SisRegCrearValorCadena ( const std::string & sClave, const std::string & sValor, const std::string & sDato, int iClavePrinc = REG_CLV_LOCAL_MACHINE );
bool SisRegCrearValorNumerico ( const std::string & sClave, const std::string & sValor, unsigned long ulDato, int iClavePrinc = REG_CLV_LOCAL_MACHINE );



/* Rutinas gestion del registro: */
HKEY SisRegClaveInfoClases ();
HKEY SisRegClaveInfoConfigActual ();
HKEY SisRegClaveInfoUsuarioActual ();
HKEY SisRegClaveInfoLocal ();
HKEY SisRegClaveInfoUsuarios ();
/* Comentadas en el .cpp desde 2008: llaman a SisRegOpenCurrentUser y
   SisRegOpenUserClassesRoot, que no existen en ninguna parte. Se quedan como
   estaban, declaradas no estarian implementadas. */
//HKEY SisRegAbrirUsuarioActual ( bool bSoloLectura );
//HKEY SisRegAbrirClasesUsuarioActual ( bool bSoloLectura );
HKEY SisRegCrear ( HKEY hkeyPadre, const std::string & sClave );
/* El acceso por defecto es KEY_READ y no KEY_ALL_ACCESS, que es lo que pedia
   antes sin opcion: sobre HKEY_LOCAL_MACHINE eso exige administrador, asi que un
   proceso normal no podia ni leer. Quien vaya a escribir pasa KEY_ALL_ACCESS, o
   KEY_WRITE, o lo que necesite. */
HKEY SisRegAbrir ( HKEY hkeyPadre, const std::string & sClave, REGSAM samAcceso = KEY_READ );
void SisRegCerrar ( HKEY hkeyClave );
bool SisRegEsClaveValida ( HKEY hkeyClave );
long SisRegNumSubclaves ( HKEY hkeyClave );
bool SisRegTieneSubclaves ( HKEY hkeyClave );
long SisRegNumValores ( HKEY hkeyClave );
bool SisRegTieneValores ( HKEY hkeyClave );
bool SisRegExisteSubclave ( HKEY hkeyClave, const std::string & sSubclave );
bool SisRegExisteValor ( HKEY hkeyClave, const std::string & sNomValor );
bool SisRegEliminarSubclave ( HKEY hkeyClave, const std::string & sSubclave );
bool SisRegEliminarTodasSubclaves ( HKEY hkeyClave );

/* Las de consulta devuelven si lo consiguieron y dejan el dato en el parametro
   de salida. Desaparece el uiMaxTamValor de la version C: lo que limitaba era el
   buffer del llamante, y std::string no lo necesita. De paso se arregla una
   falta de const-correccion que venia de origen: el parametro de salida estaba
   declarado const char * y la implementacion le quitaba el const con un cast a
   BYTE * para que RegQueryValueEx escribiera dentro. */
bool SisRegConsultarClave ( HKEY hkeyClave, std::string & sValor );
bool SisRegConsultarClaveEnt ( HKEY hkeyClave, DWORD & dwValor );
bool SisRegEstablecerClave ( HKEY hkeyClave, const std::string & sValor );
bool SisRegEstablecerClaveEnt ( HKEY hkeyClave, DWORD dwValor );
bool SisRegConsultarValor ( HKEY hkeyClave, const std::string & sNomValor, std::string & sValor );
bool SisRegConsultarValorEnt ( HKEY hkeyClave, const std::string & sNomValor, DWORD & dwValor );
bool SisRegEstablecerValor ( HKEY hkeyClave, const std::string & sNomValor, const std::string & sValor );
bool SisRegEstablecerValorEnt ( HKEY hkeyClave, const std::string & sNomValor, DWORD dwValor );
bool SisRegEliminarValor ( HKEY hkeyClave, const std::string & sNomValor );
bool SisRegEliminarTodosValores ( HKEY hkeyClave );
bool SisRegEliminarContenido ( HKEY hkeyClave );
bool SisRegImportarFichero ( HKEY hkeyPadre, const std::string & sClave, const std::string & sFichero );
bool SisRegExportarFichero ( HKEY hkeyClave, const std::string & sFichero );



/* Rutinas de alto nivel para módulos DLL. Los nombres son los de la
   implementacion ( SisRegRegistrar... ), no los de la cabecera de 2008
   ( SisRegistrar... ): el prefijo SisReg es el del resto del modulo. El GUID va
   por referencia constante, que son 16 bytes y no hay que copiarlos. */
bool SisRegRegistrarModulo ( const GUID & guidModulo, const std::string & sFicModulo, const std::string & sVersion );
bool SisRegRegistrarGUID ( const GUID & guidCodigo, const std::string & sNombre, const std::string & sDescripcion,
						   const GUID & guidModulo, const std::string & sFicModulo, const std::string & sVersion );

void SisRegDesregistrarModulo ( const GUID & guidModulo, const std::string & sVersion );
/* sFicModulo entra aqui, y en SisRegEstaRegistradoGUID, porque el ProgId se arma
   con el: SisRegRegistrarGUID lo escribe como ficheroModulo.nombre. Sin ese dato
   estas dos lo reconstruian como nombre.nombre y no encontraban nada de lo que
   habia registrado la otra. */
void SisRegDesregistrarGUID ( const GUID & guidCodigo, const std::string & sNombre,
							  const std::string & sFicModulo );


bool SisRegEstaRegistradoModulo ( const GUID & guidModulo );
bool SisRegEstaRegistradoGUID ( const GUID & guidCodigo, const std::string & sNombre,
								const std::string & sFicModulo );




 			}
		}
	}
}


#endif

#endif





