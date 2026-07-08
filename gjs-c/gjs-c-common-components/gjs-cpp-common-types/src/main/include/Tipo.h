#ifndef _ORG_GJS_C_CC_CPP_TIPO_H
#define _ORG_GJS_C_CC_CPP_TIPO_H

#include <string>
#include <TipoDatos.h>
#include <IComparable.h>



namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {

			class Tipo : public IComparable
			{
			private:
				TipoDatos		tipo;

			public:
				Tipo ();
				explicit Tipo ( TipoDatos _tipo );
				Tipo ( Tipo & _tipo );
				explicit Tipo ( Tipo * _tipo );
				virtual ~Tipo ();

			protected:
				virtual long getHash() const override;

			public:
				TipoDatos getTipo () const;
				void setTipo ( TipoDatos valor );

				void Asignar ( Tipo & _tipo );
				void Asignar ( Tipo * _tipo );

				Tipo * Clonar();

				virtual bool EsValido () const;
				bool isEntero () const;
				bool isReal () const;
				bool isCadena () const;
				bool isBooleano () const;

				bool EsCompatible ( Tipo & _tipo ) const;
				bool EsCompatible ( Tipo * _tipo ) const;
				bool EsCompatible ( const std::string & sValor ) const;

				virtual std::string toString () override;

				Tipo & operator=( Tipo & _tipo );
				bool operator== ( Tipo & obj );
				bool operator!= ( Tipo & obj );

			};

 			}
		}
	}
}



#endif
