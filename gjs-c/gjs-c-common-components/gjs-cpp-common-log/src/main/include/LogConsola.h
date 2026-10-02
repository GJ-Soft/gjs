#ifndef _ORG_GJS_C_CC_CPP_LOG_LOG_CONSOLA_H
#define _ORG_GJS_C_CC_CPP_LOG_LOG_CONSOLA_H

#include <LogEncabezado.h>





namespace org
{
	namespace gjs
	{
		namespace cpp
		{
			namespace common
			{		
				namespace log
				{

class LogConsola : public LogEncabezado
{
	public:
		LogConsola ();
		LogConsola ( std::string sNomProceso );
		virtual ~LogConsola() = default;					

	protected:
		bool Inicializar () override;
		void LogInterno ( const std::string & sMensaje ) override;
};


                }
            }
        }
    }
}

#endif
