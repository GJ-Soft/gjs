/******************************************************************************/
/*                              CTemporizador.h                               */
/*----------------------------------------------------------------------------*/
/* Librería:  Sistema                                                         */
/* Versión:   3.0.0                                                           */
/* Fecha:     25/03/2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Fichero de cabecera que contiene la definición de la clase de datos        */
/* CTemporizador, que implementa un temporizador basado en las primitivas     */
/* de temporización del sistema operativo.                                    */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#ifndef _ORG_GJS_C_CC_CPP_CTEMPORIZADOR_H
#define _ORG_GJS_C_CC_CPP_CTEMPORIZADOR_H




namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {





class CTemporizador
{
private:
	int iMiliSegs;

public:
	CTemporizador ();
	CTemporizador ( int iMiliSegundos );

	~CTemporizador ();

	int Intervalo ();
	void EstIntervalo ( int iMiliSegundos );

	void Esperar ();
	void Esperar ( int iMiliSegundos );
};




 			}
		}
	}
}




#endif

