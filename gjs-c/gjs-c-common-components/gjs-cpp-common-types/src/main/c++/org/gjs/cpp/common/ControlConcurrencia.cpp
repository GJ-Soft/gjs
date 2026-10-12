
#include "ControlConcurrencia.h"
#include <Cadenas.h>
#include <ToString.h>
#include <Concatenar.h>



using namespace org::gjs::cpp::common;
using namespace std;



namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {

ControlConcurrencia::ControlConcurrencia ()
{
}

ControlConcurrencia::~ControlConcurrencia ()
{
}

void ControlConcurrencia::Bloquear()
{
	thread::id idActual = this_thread::get_id();
	// Si este hilo ya es el dueno, la llamada es reentrante y no se vuelve a
	// tomar el cerrojo (evita el autobloqueo con un mutex no recursivo).
	if ( idBloqueante.load() != idActual )
	{
		mtxAcceso.lock();
		idBloqueante.store( idActual );
	}
	iProfundidad = iProfundidad + 1;
}

void ControlConcurrencia::Desbloquear()
{
	thread::id idActual = this_thread::get_id();
	if ( idBloqueante.load() == idActual )
	{
		/* Se suelta al deshacer el ultimo Bloquear, no el primero. Antes no
		   se contaba: en un Bloquear / Bloquear / Desbloquear el cerrojo
		   quedaba libre mientras el exterior seguia creyendose dentro, y otro
		   hilo podia entrar a la vez. */
		iProfundidad = iProfundidad - 1;
		if ( iProfundidad == 0 )
		{
			idBloqueante.store( thread::id() );
			mtxAcceso.unlock();
		}
	}
}

 			}
		}
	}
}
