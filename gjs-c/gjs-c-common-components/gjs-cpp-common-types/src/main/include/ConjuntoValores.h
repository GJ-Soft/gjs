#ifndef _ORG_GJS_C_CC_CPP_CONJUNTO_VALORES_H
#define _ORG_GJS_C_CC_CPP_CONJUNTO_VALORES_H

#include <map>
#include <list>
#include <initializer_list>
#include <Valor.h>
#include <IToString.h>




namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {

			class ConjuntoValores : public IToString
			{
			private:
				std::map<std::string, Valor *>	mapValores;
				bool 							bPermiteInsercion = true;

			public:
				ConjuntoValores ();
				ConjuntoValores ( const std::initializer_list<std::string> & lisAtributos, bool _bPermiteInsercion = false );
				ConjuntoValores ( const std::list<std::string> & lisAtributos, bool _bPermiteInsercion = false );
				ConjuntoValores ( const std::string & sRuta, bool _bPermiteInsercion = false );
				virtual ~ConjuntoValores ();

			protected:
				virtual long getHash() const;

			public:
				int NumValores () const;
				Valor * getValor ( const std::string & sAtributo );
				bool ExisteValor( const std::string & sAtributo );
				void InsertarValor ( const std::string & sAtributo, Valor * valor );
				void InsertarValor ( const std::string & sAtributo, const std::string & sValor );
				void InsertarValor ( const std::string & sAtributo, const char * p_cValor );
				void InsertarValor ( const std::string & sAtributo, bool _valor );
				void InsertarValor ( const std::string & sAtributo, short _valor );
				void InsertarValor ( const std::string & sAtributo, int _valor );
				void InsertarValor ( const std::string & sAtributo, long _valor );
				void InsertarValor ( const std::string & sAtributo, long long _valor );
				void InsertarValor ( const std::string & sAtributo, unsigned short _valor );
				void InsertarValor ( const std::string & sAtributo, unsigned int _valor );
				void InsertarValor ( const std::string & sAtributo, unsigned long _valor );
				void InsertarValor ( const std::string & sAtributo, unsigned long long _valor );
				void InsertarValor ( const std::string & sAtributo, float _valor );
				void InsertarValor ( const std::string & sAtributo, double _valor );
				void InsertarValor ( const std::string & sAtributo, long double _valor );
				void InsertarValor ( const std::string & sAtributo, char _valor );
				void InsertarValor ( const std::string & sAtributo, unsigned char _valor );
				void EliminarValor ( const std::string & sAtributo );
				void LimpiarValores ();

				bool Cargar( const std::string & sRuta );

				virtual bool EsValido () const;

				virtual std::string toString () override;

			};

 			}
		}
	}
}



#endif
