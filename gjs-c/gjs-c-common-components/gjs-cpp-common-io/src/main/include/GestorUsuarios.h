#ifndef _ORG_GJS_C_CC_CPP_GESTOR_USUARIOS_H
#define _ORG_GJS_C_CC_CPP_GESTOR_USUARIOS_H

#include <map>



namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {


			class GestorUsuarios 
			{
			private:
				std::map<std::string, std::pair<std::string, std::string>>	mapUsuarios;
				
			public:
				GestorUsuarios ();
				GestorUsuarios ( const std::string & sRuta );
				virtual ~GestorUsuarios ();
				
			public:
				int NumUsuarios () const;
				bool Alta( const std::string & sUsuario, const std::string & sClave = "", const std::string & sSubdirectorio = "" );
				void Baja( const std::string & sUsuario );				
				bool Existe( const std::string & sUsuario );
				bool Validar( const std::string & sUsuario, const std::string & sClave = "" );
				std::string Subdirectorio( const std::string & sUsuario );	
				void Limpiar ();
				
				bool Cargar( const std::string & sRuta );
				
			};
		
 			}
		}
	}
}




#endif