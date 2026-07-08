#ifndef _ORG_GJS_C_CC_CPP_CADENAS_H
#define _ORG_GJS_C_CC_CPP_CADENAS_H

#include <string>
#include <initializer_list>
#include <list>
#include <vector>




namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {
			std::string ToLowerCase ( const std::string & sCadena );
			std::string ToUpperCase ( const std::string & sCadena );

            std::string ReemplazarTodos ( const std::string & sCadena, char cBuscar, char cReemplazo );
			std::string ReemplazarTodos ( const std::string & sCadena, const std::string & sBuscar, const std::string & sReemplazo );
			std::string EliminarTodos ( const std::string & sCadena, char cBuscar );
			std::string EliminarTodos ( const std::string & sCadena, const std::string & sBuscar );

            std::string FormatearBlancos ( const std::string & sCadena );

			// TODO: Falta el test de esta
			bool ContieneCaracter ( const std::string & sCadena, char c );
			
            bool ContieneBlancos ( const std::string & sCadena );
            bool ContieneTabuladores ( const std::string & sCadena );
            bool ContieneCaracteresNoImprimibles ( const std::string & sCadena );
            bool ContieneCaracteresNoAlfanumericos ( const std::string & sCadena );
            bool ContieneCaracteresNoImprimibles ( const std::string & sCadena );
            bool ContieneCaracteresNoEstandar ( const std::string & sCadena );

            bool CoherenciaParentesis ( const std::string & sCadena );
            bool CoherenciaLlaves ( const std::string & sCadena );
            bool CoherenciaCorchetes ( const std::string & sCadena );
            bool CoherenciaParejaSignos ( const std::string & sCadena, char cSigAp, char cSigCl );

            std::string EliminarCaracter ( const std::string & sCadena, int iCar );
            std::string EliminarCaracteres ( const std::string & sCadena, int iPosIni, int iNumCars );
            std::string EliminarPrimerosCaracteres ( const std::string & sCadena, int iNumCars );
            std::string EliminarUltimosCaracteres ( const std::string & sCadena, int iNumCars );
            std::string EliminarApariciones ( const std::string & sCadena1, const std::string & sCadena2 );
            std::string EliminarBlancos ( const std::string & sCadena );
            std::string EliminarTabuladores ( const std::string & sCadena );
            std::string EliminarCaracteresNoAlfanumericos ( const std::string & sCadena );
            std::string EliminarCaracteresNoImprimibles ( const std::string & sCadena );
            std::string EliminarCaracteresNoEstandar ( const std::string & sCadena );
			std::string Limpiar( const std::string & sCadena );

			std::string SubcadenaHasta ( const std::string & sCadena, char cBuscar );
			std::string SubcadenaDesde ( const std::string & sCadena, char cBuscar );

			std::string LTrim( const std::string & sCadena );
			std::string RTrim( const std::string & sCadena );
			std::string Trim( const std::string & sCadena );

			bool TieneEspacios ( const std::string & sCadena );
			bool EmpiezaPor ( const std::string & sCadena, const std::string & sPrefijo );
			bool TerminaPor ( const std::string & sCadena, const std::string & sSufijo );
			bool TerminaEnSaltoLinea ( const std::string & sCadena );

			std::string EliminarUltimoSaltoLinea( const std::string & sCadena );

			bool SonIgualesIn ( const std::string & sCadena1, const std::string & sCadena2 );

			bool EsPalabra ( const std::string & sCadena );
			bool EsToken ( const std::string & sCadena );
			bool EsNombreFichero ( const std::string & sCadena );
			bool EsNatural ( const std::string & sCadena );
			bool EsEntero ( const std::string & sCadena );
			bool EsReal ( const std::string & sCadena );
			bool EsBooleano ( const std::string & sCadena );
			bool EsURL ( const std::string & sCadena );
			bool EsURN ( const std::string & sCadena );
			bool EsURI ( const std::string & sCadena );

			size_t BuscarPrimero( const std::string & sCadena, const std::initializer_list<std::string> & delimitadores, size_t * tamDelim = NULL, size_t posIni = 0 );
			size_t BuscarPrimero( const std::string & sCadena, const std::list<std::string> & delimitadores, size_t * tamDelim = NULL, size_t posIni = 0 );
			// TODO: Falta el test de esta
			size_t BuscarDesdeAtrasCaracter( const std::string & sCadena, char c, size_t desde = std::string::npos );

			std::vector<std::string> Separar ( std::string sCadena, const std::initializer_list<std::string> & delimitadores = { " " } );
			std::vector<std::string> Separar ( std::string sCadena, const std::list<std::string> & delimitadores );

			// TODO: Falta el test de estas
			int NumPalabras( const std::string & cadena, char delimitador );
			std::string ExtraerPalabra( const std::string & sCadena, int iPos, char cDelimitador ); 
		
 			}
		}
	}
}

#endif
