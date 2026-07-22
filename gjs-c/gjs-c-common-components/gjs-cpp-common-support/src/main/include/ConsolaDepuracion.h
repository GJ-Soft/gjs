

#ifndef _CONSOLADEPURACION_H
#define _CONSOLADEPURACION_H






#define	DEP_INIFUN			ConDepEscribirLinea ("<Mod: {}; Fun: {}> - INICIO", __FILE__, __FUNCTION__ )
#define	DEP_FINFUN			ConDepEscribirLinea ("<Mod: {}; Fun: {}> - FIN", __FILE__, __FUNCTION__ )



#include <string>
#include <format>



namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {



bool ConDepAbrir ();
void ConDepCerrar ();
bool ConDepEstaAbierta ();

// Escritores base ( definidos en el .cpp ).
bool ConDepEscribir ( const std::string & sTexto );
bool ConDepEscribirLinea ( const std::string & sTexto );

// Variantes con formato: definidas aqui ( una plantilla debe ser visible en el
// punto de instanciacion ) delegando en std::vformat + el escritor base.
template<typename... Args> bool ConDepEscribir ( const std::string & sFormato, Args&&... argumentos )
{
	return ( ConDepEscribir ( std::vformat ( sFormato, std::make_format_args ( argumentos... ) ) ) );
}
template<typename... Args> bool ConDepEscribirLinea ( const std::string & sFormato, Args&&... argumentos )
{
	return ( ConDepEscribirLinea ( std::vformat ( sFormato, std::make_format_args ( argumentos... ) ) ) );
}


 			}
		}
	}
}

#endif

