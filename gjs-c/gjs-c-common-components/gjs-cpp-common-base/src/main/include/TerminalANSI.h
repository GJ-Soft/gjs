#ifndef _ORG_GJS_C_CC_CPP_TERMINALANSI_H
#define _ORG_GJS_C_CC_CPP_TERMINALANSI_H


#include <string>
#include <iostream>



namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {
                namespace ANSI
                {

				const std::string RESETEAR( "\033[0m" );
				const std::string NEGRITA_INI ( "\033[0;1m" );
				const std::string SUBRAYADO_INI ( "\033[0;4m" );
				const std::string INVERSO_INI ( "\033[0;7m" );
				const std::string NEGRITA_FIN ( "\033[0;21m" );
				const std::string SUBRAYADO_FIN ( "\033[0;24m" );
				const std::string INVERSO_FIN ( "\033[0;27m" );

				const std::string NEGRO ( "\033[0;30m" );
				const std::string ROJO ( "\033[0;31m" );
				const std::string VERDE ( "\033[0;32m" );
				const std::string AMARILLO ( "\033[0;33m" );
				const std::string AZUL ( "\033[0;34m" );
				const std::string MAGENTA ( "\033[0;35m" );
				const std::string CIAN ( "\033[0;36m" );
				const std::string BLANCO ( "\033[0;37m" );

				const std::string FONDO_NEGRO ( "\033[0;40m" );
				const std::string FONDO_ROJO ( "\033[0;41m" );
				const std::string FONDO_VERDE ( "\033[0;42m" );
				const std::string FONDO_AMARILLO ( "\033[0;43m" );
				const std::string FONDO_AZUL ( "\033[0;44m" );
				const std::string FONDO_MAGENTA ( "\033[0;45m" );
				const std::string FONDO_CIAN ( "\033[0;46m" );
				const std::string FONDO_BLANCO ( "\033[0;47m" );

                }
            }
		}
	}
}

#endif
