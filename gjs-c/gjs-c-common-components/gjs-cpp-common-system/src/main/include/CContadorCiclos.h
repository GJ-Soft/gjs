/******************************************************************************/
/*                              CContadorCiclos.h                             */
/*----------------------------------------------------------------------------*/
/* Librería:  Sistema                                                         */
/* Versión:   3.0.0                                                           */
/* Fecha:     25/03/2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Fichero de cabecera que contiene la definición de la clase de datos        */
/* CContadorCiclos, que implementa un temporizador basado en las primitivas   */
/* de temporización del sistema operativo.                                    */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#ifndef _ORG_GJS_C_CC_CPP_COMMON_CCONTADORCICLOS_H
#define _ORG_GJS_C_CC_CPP_COMMON_CCONTADORCICLOS_H




#include <stdint.h>



namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {



class CContadorCiclos
{
private:
	bool		bIniciado;
	uint64_t	ui64CicloIni;
	uint64_t	ui64NumCiclos;

public:
	CContadorCiclos ();

	~CContadorCiclos ();

	void Iniciar ();
	uint64_t Valor ();
	uint64_t Parar ();
	bool EstaContando ();
};




 			}
		}
	}
}




#endif

