#ifndef _ORG_GJS_C_CC_CPP_COMANDO_H
#define _ORG_GJS_C_CC_CPP_COMANDO_H


#include <initializer_list>
#include <string>
#include <vector>



namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {

			class Comando
			{
			private:
				std::string 				sComando;
				std::vector<std::string>	vecArgumentos;
				
			public:
				Comando();
				Comando( const std::string & _sComando, const std::initializer_list<std::string> & lisArgumentos );
				Comando( const std::string & sExpresion );
				virtual ~Comando();

				virtual bool EsValido();
				
				const std::string & getComando();
				void setComando( const std::string & sValor );
				bool isComando( const std::string & sValor );
				
				int NumArgumentos() const;
				const std::string & getArgumento( int iArg );
				void addArgumento( const std::string & sArgumento );
				
				void Inicializar();
				void InicializarArgumentos();
				void Asignar( const std::string & _sComando, const std::initializer_list<std::string> & lisArgumentos );
				void Procesar( const std::string & sExpresion );
				
				virtual std::string toString();

			};

 			}
		}
	}
}


#endif