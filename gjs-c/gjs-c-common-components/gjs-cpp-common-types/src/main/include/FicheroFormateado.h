#ifndef _ORG_GJS_C_CC_CPP_FICHERO_FORMATEADO_H
#define _ORG_GJS_C_CC_CPP_FICHERO_FORMATEADO_H

#include <vector>
#include <list>
#include <initializer_list>
#include <Excepcion.h>



namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {

			// TODO: Rutinas de edición y guardado
			class FicheroFormateado
			{
			private:
				std::list<std::string> 					lisSeparadores;
				std::string 							sFichero;
				bool									bCargado = false;
				std::vector<std::vector<std::string>>	vecContenido;

			public:
				explicit FicheroFormateado ( const std::initializer_list<std::string> & delimitadores );
				virtual ~FicheroFormateado ();

			public:
				bool Cargar( const std::string & sRuta );
				//bool Cargar();
				//bool Guardar( const std::string & sRuta );
				//bool Guardar();

				std::string getRuta() const;

				int NumLineas() const;
				std::vector<std::string> & Linea( int iLinea );
				int NumCamposLinea( int iLinea ) const;
				std::string Campo( int iLinea, int iCampo );

			private:
				void Vaciar();

			};

			class FicheroTSV : public FicheroFormateado
			{
			public:
				FicheroTSV () : FicheroFormateado ( { "\t" } ) {};
			};

			class FicheroCSV : public FicheroFormateado
			{
			public:
				FicheroCSV () : FicheroFormateado ( { "," } ) {};
			};

			class FicheroDSV : public FicheroFormateado
			{
			public:
				FicheroDSV () : FicheroFormateado ( { ";" } ) {};
			};

 			}
		}
	}
}



#endif
