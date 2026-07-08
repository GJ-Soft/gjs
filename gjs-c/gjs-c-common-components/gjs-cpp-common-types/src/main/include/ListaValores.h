#ifndef _ORG_GJS_C_CC_CPP_LISTA_VALORES_H
#define _ORG_GJS_C_CC_CPP_LISTA_VALORES_H

#include <vector>
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

			class ListaValores : public IToString
			{
			private:
				std::vector<Valor *>	vecValores;
				bool 					bPermiteInsercion = true;

			public:
				ListaValores ();
				ListaValores ( int _iTam, bool _bPermiteInsercion = false );
				virtual ~ListaValores ();

			protected:
				virtual long getHash() const;

			public:
				int NumValores () const;
				Valor * getValor ( int iIndice );
				void InsertarValor ( Valor * valor );
				void InsertarValor ( const std::string & sValor );
				void InsertarValor ( const char * p_cValor );
				void InsertarValor ( bool _valor );
				void InsertarValor ( short _valor );
				void InsertarValor ( int _valor );
				void InsertarValor ( long _valor );
				void InsertarValor ( long long _valor );
				void InsertarValor ( unsigned short _valor );
				void InsertarValor ( unsigned int _valor );
				void InsertarValor ( unsigned long _valor );
				void InsertarValor ( unsigned long long _valor );
				void InsertarValor ( float _valor );
				void InsertarValor ( double _valor );
				void InsertarValor ( long double _valor );
				void InsertarValor ( char _valor );
				void InsertarValor ( unsigned char _valor );
				void EliminarValor ( int iIndice );
				void LimpiarValores ();

				virtual bool EsValida ();

				virtual std::string toString () override;

			};

 			}
		}
	}
}



#endif
