/******************************************************************************/
/*                               CArgumentos.h                                */
/*----------------------------------------------------------------------------*/
/* Librería:  Aplicacion                                                      */
/* Versión:   3.0.0                                                           */
/* Fecha:     25/03/2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Fichero de cabecera que contiene la definición de la clase de datos        */
/* CArgumentos, destinada a procesar la secuencia de parámetros que recibe    */
/* un programa desde la línea de comandos.                                    */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#ifndef _ORG_GJS_C_CC_CPP_CARGUMENTOS_H
#define _ORG_GJS_C_CC_CPP_CARGUMENTOS_H


#include <Precompilacion.h>

#include <string>
#include <vector>

#include <ArgumentoInvalidoExcepcion.h>





namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {

class Argumentos
{
private:
	std::vector<std::string> 	vecArgumentos;
	int			        		iNumArgumentos;

public:
# if ( defined ( WIN ) )
	Argumentos ();
#endif
	Argumentos ( int iNumArgs, char ** p_p_cArg );

	~Argumentos ();

	int NumArgumentos () const;
	std::string Argumento ( int iArg ) const;
	bool EsArgumentoNumerico ( int iArg ) const;
	int ArgumentoEntero ( int iArg ) const;
	long ArgumentoEnteroLargo ( int iArg ) const;
	float ArgumentoReal ( int iArg ) const;
	double ArgumentoRealDoble ( int iArg ) const;
};

 			}
		}
	}
}



#endif




