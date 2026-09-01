/******************************************************************************/
/*                         SimulacionUsuarioConsola.h                         */
/*----------------------------------------------------------------------------*/
/* Libreria:  Support                                                         */
/*----------------------------------------------------------------------------*/
/* Descripcion:                                                               */
/* Utilidad para TESTS: simula una entrada de usuario por consola para probar */
/* codigo que lee de stdin de forma bloqueante ( p. ej. el getchar() de       */
/* CajMsjMostrar en POSIX ). Version C++ de la clase homonima del modulo C.   */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#ifndef _ORG_GJS_C_CC_CPP_SIMULACIONUSUARIOCONSOLA_H
#define _ORG_GJS_C_CC_CPP_SIMULACIONUSUARIOCONSOLA_H


#include <string>


namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {



// Engancha stdin a una tuberia precargada con sEntrada + retorno ( "" simula
// pulsar solo <retorno> ). El extremo de escritura se cierra tras escribir, de
// modo que el lector ve la entrada y despues EOF: nunca se queda bloqueado,
// aunque lea de mas. Hay que llamar a RestaurarEntradaConsola tras la lectura
// para devolver stdin a su estado original. Devuelve true si prepara la entrada
// y false en caso de error. Vale en los cuatro modos de compilacion.
bool SimularEntradaConsola ( const std::string & sEntrada );

// Deshace la redireccion, devolviendo stdin a su descriptor original. Es inocuo
// llamarla si no habia simulacion activa.
void RestaurarEntradaConsola ();



 			}
		}
	}
}


#endif
