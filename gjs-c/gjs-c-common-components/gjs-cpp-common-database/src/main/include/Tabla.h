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
				/* Es dueña de sus Ocurrencia * y lo libera en el destructor: una copia
				   implícita compartiría los punteros y los liberaría dos veces. */
				Tabla ( const Tabla & ) = delete;
				Tabla & operator= ( const Tabla & ) = delete;

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