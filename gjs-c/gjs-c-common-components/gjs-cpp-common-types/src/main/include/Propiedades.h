#ifndef _ORG_GJS_C_CC_CPP_PROPIEDADES_H
#define _ORG_GJS_C_CC_CPP_PROPIEDADES_H

#include <NoEncontradoExcepcion.h>

#include <string>
#include <vector>
#include <map>



namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {

			class Propiedades
			{
			private:
				std::vector<std::string> vecClaves;
				std::map<std::string, std::string> mapPropiedades;

			public:
				Propiedades();
				explicit Propiedades( const std::string & sRuta );
				virtual ~Propiedades();

				std::string getPropiedad( const std::string & sClave ) const;
				std::string getPropiedad( const std::string & sClave, const std::string & sValorDef ) const;
				void setPropiedad( const std::string & sClave, const std::string & sValor );

				std::vector<std::string> getPropiedades() const;
				bool ExistePropiedad( const std::string & sClave ) const;
				int NumPropiedades() const;

				void EliminarPropiedad( const std::string& sClave );

				bool Cargar( const std::string & sRuta );
				bool Guardar(  const std::string & sRuta );

			private:
				bool EsPropiedad( const std::string & sLinea );
				std::pair<std::string, std::string> ParsearPropiedad( const std::string & sLinea );

			};

 			}
		}
	}
}


#endif
