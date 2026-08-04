#ifndef _ORG_GJS_C_CC_CPP_ATRIBUTO_H
#define _ORG_GJS_C_CC_CPP_ATRIBUTO_H

#include <string>
#include <Tipo.h>
#include <Valor.h>




namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {


			class Atributo : public Tipo
			{
			private:
				std::string 	sNombre;
				bool			bAnulable;

			public:
				Atributo ();
				Atributo ( TipoDatos _tipo, const std::string & _sNombre, bool _bAnulable =  true );
				Atributo ( const Tipo & _tipo, const std::string & _sNombre, bool _bAnulable =  true );
				Atributo ( const Atributo & atributo );
				explicit Atributo ( const Atributo * atributo );
				virtual ~Atributo ();

			public:
				virtual long getHash() const override;

			public:
				std::string getNombre () const;
				void setNombre ( const std::string & sValor );

				bool isAnulable () const;
				void setAnulable ( bool bValor );

				void Asignar ( const Atributo & atributo );
				void Asignar ( const Atributo * atributo );

				Atributo * Clonar();

				virtual bool EsValido () const override;

				bool EsCompatible ( const Atributo & atributo ) const;
				bool EsCompatible ( const Atributo * atributo ) const;
				bool EsCompatible ( const Valor & valor ) const;
				bool EsCompatible ( const Valor * valor ) const;

				virtual std::string toString () override;

				Atributo & operator=( const Atributo & atributo );
				bool operator== ( const Atributo & obj ) const;
				bool operator!= ( const Atributo & obj ) const;
			};

 			}
		}
	}
}



#endif
