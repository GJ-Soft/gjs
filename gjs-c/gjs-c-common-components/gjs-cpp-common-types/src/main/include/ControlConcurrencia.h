#ifndef _ORG_GJS_C_CC_CPP_CONTROL_CONCURRENCIA_H
#define _ORG_GJS_C_CC_CPP_CONTROL_CONCURRENCIA_H

#include <mutex>
#include <thread>



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
				std::mutex 			mtxAcceso;
				std::thread::id * 	idBloqueante = nullptr;

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
