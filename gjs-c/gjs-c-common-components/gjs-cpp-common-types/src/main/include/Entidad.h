#ifndef _ORG_GJS_C_CC_CPP_ENTIDAD_H
#define _ORG_GJS_C_CC_CPP_ENTIDAD_H

#include <string>
#include <map>
#include <vector>
#include <Atributo.h>
#include <Valor.h>
#include <IComparable.h>



namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {

			class Entidad : public IComparable
			{
			private:
				std::string							sNombre;
				std::map<std::string, Atributo *>	mapDefinicion;

			public:
				Entidad ();
				explicit Entidad ( const std::string & _sNombre );
				Entidad ( const Entidad & obj );
				explicit Entidad ( const Entidad * obj );
				virtual ~Entidad ();

			public:
				virtual long getHash() const override;

			public:
				std::string getNombre () const;
				void setNombre ( const std::string & sValor );

				virtual bool EsValida () const;

				int NumAtributos ();
				bool TieneAtributo ( const std::string & sAtributo );
				Atributo * getAtributo ( const std::string & sAtributo );
				Atributo * getAtributo ( int iIndice );
				std::vector<std::string> * ListaAtributos ();
				int getIndiceAtributo ( const std::string & sAtributo );
				void InsertarAtributo ( Atributo * atributo );
				void InsertarAtributo ( TipoDatos tipo, const std::string & sAtributo, bool bAnulable =  true );
				void InsertarAtributo ( Tipo & tipo, const std::string & sAtributo, bool bAnulable =  true );
				void EliminarAtributo ( const std::string & sAtributo );
				void EliminarAtributo ( int iIndice );
				void LimpiarAtributos ();

				bool EsCompatible ( const Entidad & obj ) const;
				bool EsCompatible ( const Entidad * obj ) const;

				void Asignar ( const Entidad & obj );
				void Asignar ( const Entidad * obj );

				Entidad * Clonar();

				virtual std::string toString () override;

				Entidad & operator=( const Entidad & obj );
				bool operator== ( const Entidad & obj ) const;
				bool operator!= ( const Entidad & obj ) const;
			};

 			}
		}
	}
}



#endif
