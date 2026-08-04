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
				Tipo ( const Tipo & _tipo );
				explicit Tipo ( const Tipo * _tipo );
				virtual ~Tipo ();

			protected:
				virtual long getHash() const override;

			public:
				TipoDatos getTipo () const;
				void setTipo ( TipoDatos valor );

				void Asignar ( const Tipo & _tipo );
				void Asignar ( const Tipo * _tipo );

				Tipo * Clonar();

				virtual bool EsValido () const;
				bool isEntero () const;
				bool isReal () const;
				bool isCadena () const;
				bool isBooleano () const;

				bool EsCompatible ( const Tipo & _tipo ) const;
				bool EsCompatible ( const Tipo * _tipo ) const;
				bool EsCompatible ( const std::string & sValor ) const;

				virtual std::string toString () override;

				Tipo & operator=( const Tipo & _tipo );
				bool operator== ( const Tipo & obj ) const;
				bool operator!= ( const Tipo & obj ) const;

			};

 			}
		}
	}
}



#endif
