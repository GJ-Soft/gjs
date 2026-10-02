#ifndef _ORG_GJS_C_CC_CPP_LOG_LOG_ENCABEZADO_H
#define _ORG_GJS_C_CC_CPP_LOG_LOG_ENCABEZADO_H



#include <LogAppender.h>





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

class LogEncabezado : public LogAppender
{
	private:
		std::string	sNomProceso;
		bool    	bEncabezado;
		bool    	bAnotarTipoMensaje;
		bool    	bPartirLinea;
		
	public:
		LogEncabezado ();
		LogEncabezado ( std::string	sNombre );
		virtual ~LogEncabezado() = default;					

		const std::string NombreProceso ();
		void EstablecerNombreProceso ( const std::string & sNombre );

		void ActivarEncabezadoLinea ();
		void DesactivarEncabezadoLinea ();
		bool EncabezadoLineaActivado ();
		void ActivarAnotacionTipoMensaje ();
		void DesactivarAnotacionTipoMensaje ();
		bool AnotacionTipoMensajeActivada ();
		void ActivarParticionLinea ();
		void DesactivarParticionLinea ();
		bool ParticionLineaActivada ();

	protected:
		/* Redefine el gancho de LogAppender: dos parametros y override, o no
		   estaria redefiniendo nada y la clase seguiria siendo abstracta por el. */
		std::string FormatearMensaje ( NivelLog nivel, const std::string & sMensaje ) override;
};

			   }
		   }
		}
	}
}

#endif
