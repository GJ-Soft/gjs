#ifndef _ORG_GJS_C_CC_CPP_OCURRENCIA_H
#define _ORG_GJS_C_CC_CPP_OCURRENCIA_H

#include <string>
#include <Entidad.h>
#include <ListaValores.h>



namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {

			class Ocurrencia : public ListaValores, public IComparable
			{
			private:
				Entidad * entidad;

			public:
				explicit Ocurrencia ( Entidad * _entidad );
				explicit Ocurrencia( Ocurrencia * obj );
				Ocurrencia( Ocurrencia & obj );
				virtual ~Ocurrencia ();

			protected:
				virtual long getHash() const override;

			public:
				Entidad * getEntidad () const;

				virtual bool EsValida ();
				bool EsCompatible ( Entidad & obj );
				bool EsCompatible ( Entidad * obj );
				bool EsCompatible ( Ocurrencia & obj );
				bool EsCompatible ( Ocurrencia * obj );

				Valor * getValor ( const std::string & sAtributo );
				Valor * getValor ( int iIndice );

				void Asignar ( Ocurrencia & obj );
				void Asignar ( Ocurrencia * obj );

				Ocurrencia * Clonar();

				virtual std::string toString () override;

				Ocurrencia & operator=( Ocurrencia & obj );
				bool operator== ( Ocurrencia & obj );
				bool operator!= ( Ocurrencia & obj );

			};

 			}
		}
	}
}




#endif
