#ifndef _ORG_GJS_C_CC_CPP_VALOR_H
#define _ORG_GJS_C_CC_CPP_VALOR_H

#include <string>
#include <IComparable.h>


namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {

			class Valor : public IComparable
			{
			private:
				std::string 	sDato;
				bool			bNulo;

			public:
				Valor ();
				explicit Valor ( const std::string & _sDato );
				explicit Valor ( const char * p_cValor );
				explicit Valor ( bool _valor );
				explicit Valor ( short _valor );
				explicit Valor ( int _valor );
				explicit Valor ( long _valor );
				explicit Valor ( long long _valor );
				explicit Valor ( unsigned short _valor );
				explicit Valor ( unsigned int _valor );
				explicit Valor ( unsigned long _valor );
				explicit Valor ( unsigned long long _valor );
				explicit Valor ( float _valor );
				explicit Valor ( double _valor );
				explicit Valor ( long double _valor );
				explicit Valor ( char _valor );
				explicit Valor ( unsigned char _valor );
				Valor ( Valor & obj );
				explicit Valor ( Valor * obj );
				virtual ~Valor ();

			public:
				virtual long getHash() const override;

			public:
				bool EsNulo () const;
				void Anular ();

				std::string getValor () const;
				bool getValorBool () const;
				long getValorEntero () const;
				long long getValorEnteroLargo () const;
				double getValorReal () const;
				long double getValorRealLargo () const;

				void setValor ( const std::string & sValor );
				void setValor ( const char * p_cValor );
				void setValor ( bool _valor );
				void setValor ( short _valor );
				void setValor ( int _valor );
				void setValor ( long _valor );
				void setValor ( long long _valor );
				void setValor ( unsigned short _valor );
				void setValor ( unsigned int _valor );
				void setValor ( unsigned long _valor );
				void setValor ( unsigned long long _valor );
				void setValor ( float _valor );
				void setValor ( double _valor );
				void setValor ( long double _valor );
				void setValor ( char _valor );
				void setValor ( unsigned char _valor );

				void Asignar ( Valor & obj );
				void Asignar ( Valor * obj );

				Valor * Clonar();

				virtual bool EsValido () const;

				virtual std::string toString () override;

				Valor & operator=( Valor & obj );
				bool operator== ( Valor & obj );
				bool operator!= ( Valor & obj );
			};

 			}
		}
	}
}



#endif
