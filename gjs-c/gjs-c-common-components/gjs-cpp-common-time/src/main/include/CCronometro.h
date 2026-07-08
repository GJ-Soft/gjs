/******************************************************************************/
/*                               CCronometro.h                                */
/*----------------------------------------------------------------------------*/
/* Librería:  Tiempo                                                          */
/* Versión:   3.0.0                                                           */
/* Fecha:     25/03/2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Fichero de cabecera que contiene la definición de la clase de datos        */
/* CCronometro, que implementa un temporizador basado en las primitivas       */
/* de temporización del sistema operativo.                                    */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#ifndef _ORG_GJS_C_CC_CPP_CCRONOMETRO_H
#define _ORG_GJS_C_CC_CPP_CCRONOMETRO_H


#include <chrono>




namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {



class CCronometro
{
private:
	std::chrono::system_clock::time_point * p_tpTiempoIni;


public:
	CCronometro ();

	~CCronometro ();

	void Iniciar ();
	long long Parar ();

	long long Computo ();
};



 			}
		}
	}
}




#endif


