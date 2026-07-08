#ifndef _ORG_GJS_C_CC_CPP_SISTEMA_H
#define _ORG_GJS_C_CC_CPP_SISTEMA_H

#include <string>
#include <ctime>
#include <thread>




namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {


			typedef void (*SIGNAL_HANDLER)( int );

			std::string NombreSistema ();
			bool EsWindows ();
			bool EsCygwin ();
			bool EsMinGW ();
			bool EsLinux ();
			bool EsUnix ();
			bool EsMac ();

			std::string DirectorioActual ();
			std::string ResolverDirectorioRelativo ( std::string sRutaBase, std::string sRutaRelativa );
			void EstablecerDirectorio( const std::string & sRuta );

			bool ExisteFichero ( const std::string & sRuta );
			bool ExisteDirectorio ( const std::string & sRuta );

			std::string VariableEntorno ( const std::string & sNombre );
			void EstablecerVariableEntorno ( const std::string & sNombre, const std::string & sValor );
			void EliminarVariableEntorno ( const std::string & sNombre );

			void Esperar ( long lMiliseg );

			void EstablecerManejadorInterrupciones ( SIGNAL_HANDLER fManejador );
			void EstablecerManejadorInterrupcionesDefecto ();
			void LimpiarManejadorInterrupciones ();
			//void GrabarRetornoAPrograma();
			//void RetornarAPrograma ();

			time_t Ahora ();

			void InicializarBase();
			bool PuedeLiberarse ( const void * ptr );

			int ResolverIP( const std::string & sIP );

			std::string EjecutarComando ( const std::string & sComando );

            }
		}
	}
}

#endif
