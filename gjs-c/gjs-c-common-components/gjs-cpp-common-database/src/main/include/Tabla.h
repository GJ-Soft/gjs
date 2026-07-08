#ifndef _ORG_GJS_C_CC_CPP_TABLA_H
#define _ORG_GJS_C_CC_CPP_TABLA_H

#include <string>
#include <map>
#include <Entidad.h>
#include <Ocurrencia.h>



namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {

			class Tabla : public Entidad 
			{
			private:
				std::vector<Ocurrencia *>	vecContenido;
				
			public:
				explicit Tabla ( Entidad * entidad );
				explicit Tabla ( Entidad & entidad );
				virtual ~Tabla ();

			public:
				int NumOcurrencias () const;
				Ocurrencia * getOcurrencia ( int iIndice );
				Ocurrencia * Nueva ();
				void Insertar ( Ocurrencia * ocurrencia );
				void Eliminar ( int iIndice );
				void Vaciar ();
				
				virtual std::string toString () override;
				
			};
		
 			}
		}
	}
}




#endif