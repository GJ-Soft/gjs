/******************************************************************************/
/*                            CVariablesEntorno.h                             */
/*----------------------------------------------------------------------------*/
/* Librería:  Sistema                                                         */
/* Versión:   3.0.0                                                           */
/* Fecha:     25/03/2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Fichero de cabecera que contiene la definición de la clase de datos        */
/* CVariablesEntorno, que facilita el trabajo con las variables de entorno    */
/* del sistema operativo.                                                     */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#ifndef _ORG_GJS_C_CC_CPP_CVARIABLESENTORNO_H
#define _ORG_GJS_C_CC_CPP_CVARIABLESENTORNO_H




#include <string>



namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {





class CVariablesEntorno
{
public:
	CVariablesEntorno ();

	~CVariablesEntorno ();

	std::string * ObtValor ( const std::string & sVariable ) const;
	bool LimpiarValor ( const std::string & sVariable );
	bool EstValor ( const std::string & sVariable, const std::string & sValor );
	bool ExisteVariable ( const std::string & sVariable );
};




 			}
		}
	}
}




#endif

