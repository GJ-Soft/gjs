#ifndef _ORG_GJS_C_CC_CPP_CONTROL_CONCURRENCIA_H
#define _ORG_GJS_C_CC_CPP_CONTROL_CONCURRENCIA_H

#include <mutex>
#include <thread>
#include <atomic>



namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {

			class ControlConcurrencia
			{
			private:
				std::mutex 						mtxAcceso;
				// Dueno del bloqueo (o thread::id() si esta libre). Atomico para
				// poder consultarlo sin cerrojo sin incurrir en carrera de datos.
				std::atomic<std::thread::id> 	idBloqueante { std::thread::id() };

			public:
				ControlConcurrencia ();
				virtual ~ControlConcurrencia ();

			protected:
				void Bloquear();
				void Desbloquear();
			};

 			}
		}
	}
}



#endif
