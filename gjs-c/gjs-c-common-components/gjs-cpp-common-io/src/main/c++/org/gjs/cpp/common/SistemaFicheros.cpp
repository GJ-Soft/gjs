/***************************************************************************/
/*                        SistemaFicheros.cpp                              */
/*-------------------------------------------------------------------------*/
/* Librería: Sistema                                                       */
/* Versión:  1.1.0                                                         */
/* Fecha:    26/10/2006                                                    */
/* Autor:    Ginés Jiménez Sánchez                                         */
/*-------------------------------------------------------------------------*/
/* Descripción:                                                            */
/* Fichero de código fuente que contiene la implementación de las rutinas  */
/* de carácter general de operaciones con el sistema de ficheros.          */
/* Mantiene un objeto global privado de clase CSistemaFicheros que puede   */
/* utilizarse para moverse por el árbol de directorios.                    */
/*-------------------------------------------------------------------------*/
/* NOTA DEL AUTOR:                                                         */
/* Este módulo está extraído de una librería más completa creada por el    */
/* mismo autor. Por favor, el autor ruega que se le informe de cualquier   */
/* error detectado, así como cualquier añadido o modificación realizado.   */
/* Pueden reportar de los mismos enviando un correo electrónico a la       */
/* dirección: gines_jimenez@safe-mail.net. Gracias.                        */
/***************************************************************************/

/*-------------------------------------------------------------------------*/
/* NOTA DE PORTABILIDAD (adaptación C++):                                   */
/* Este módulo se apoya en una librería de cadenas C++ (todavía por crear)  */
/* con estas funciones auxiliares sobre std::string:                       */
/*   bool        CumpleExpresionRegular ( const string&, const string& );   */
/*   bool        ContieneCaracter       ( const string&, char );            */
/*   int         NumPalabras            ( const string&, char sep );        */
/*   string      ExtraerPalabra         ( const string&, int, char sep );   */
/*   int         BuscarDesdeAtrasCaracter( const string&, char [, int] );   */
/*   string      SubcadenaDesde         ( const string&, char );            */
/*   string      ReemplazarTodos        ( const string&, from, to );        */
/*   string      ReemplazarTodos     ( const string&, char, char );         */
/* CommonIoConfig.h debe proporcionar las constantes SF_* (equivalentes a   */
/* FicherosConfig.h de la versión C).                                       */
/*-------------------------------------------------------------------------*/


#include "CommonIoConfig.h"

#include "SistemaFicheros.h"
#include "SistemaFicherosWin32.h"

#include <filesystem>
#include <fstream>
#include <sstream>
#include <vector>


using namespace std;

namespace fs = std::filesystem;

namespace org
{
	namespace gjs
	{
		namespace cpp
		{
			namespace common
			{


// Auxiliar local: divide la cadena por el separador descartando los tokens vacíos
// (equivalente a la semántica de "palabras" de CadNumPalabrasSep / CadPalabraSep).
static vector<string> SisDividirEnPartes ( const string & sCadena, char cSep )
{
	vector<string>	vecPartes;
	stringstream	ss ( sCadena );
	string			sParte;

	while ( getline ( ss, sParte, cSep ) )
	{
		if ( ! sParte.empty () )
		{
			vecPartes.push_back ( sParte );
		}
	}
	return ( vecPartes );
}


bool SisEsSubdirectorioValido ( const string & sSubdirectorio )
{
	bool bRes = false;

	if ( CumpleExpresionRegular ( sSubdirectorio, SF_PATRON_SUBDIRECTORIO ) )
	{
		bRes = true;
	}
	return ( bRes );
}

bool SisEsFicheroValido ( const string & sFichero )
{
	bool bRes = false;

	if ( CumpleExpresionRegular ( sFichero, SF_PATRON_FICHERO ) ||
		 CumpleExpresionRegular ( sFichero, SF_PATRON_FICHERO_2 ) )
	{
		bRes = true;
	}
	return ( bRes );
}

int SisFicheroTieneExtension ( const string & sFichero )
{
	bool bRes = false;

	if ( CumpleExpresionRegular ( sFichero, SF_PATRON_FICHERO ) )
	{
		bRes = true;
	}
	return ( bRes );
}

int SisDirectorioNumSubdirectorios ( const string & sDirectorio )
{
	int iRes;

	if ( ContieneCaracter ( sDirectorio, SF_DIR_SEPARADOR ) )
	{
		iRes = NumPalabras ( sDirectorio, SF_DIR_SEPARADOR );
	}
	else if ( ContieneCaracter ( sDirectorio, SF_DIR_SEPARADOR_WIN ) )
	{
		iRes = NumPalabras ( sDirectorio, SF_DIR_SEPARADOR_WIN );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

string SisDirectorioSubdirectorio ( const string & sDirectorio, int iNivel )
{
	string 		sRes  = "";
	int			iSubdir;
	char		cSep;
	int			iNumSubdirs;

	iNumSubdirs = SisDirectorioNumSubdirectorios ( sDirectorio );
	if ( iNumSubdirs > 1 )
	{
		if ( ContieneCaracter ( sDirectorio, SF_DIR_SEPARADOR ) )
		{
			cSep = SF_DIR_SEPARADOR;
		}
		else
		{
			cSep = SF_DIR_SEPARADOR_WIN;
		}
		if ( iNivel == -1 )
		{
			iSubdir = iNumSubdirs - 1;
		}
		else
		{
			iSubdir = iNivel;
		}

		if ( ( iSubdir >= 0 ) && ( iSubdir < iNumSubdirs ) )
		{
			sRes = ExtraerPalabra ( sDirectorio, iSubdir, cSep );
		}
	}
	return ( sRes );
}

string SisDirectorioSuperior ( const string & sDirectorio )
{
	string 	sRes = "";
	char	cSep;
	int		iPos;
	int		iLong;

	if ( ContieneCaracter ( sDirectorio, SF_DIR_SEPARADOR ) )
	{
		cSep = SF_DIR_SEPARADOR;
	}
	else
	{
		cSep = SF_DIR_SEPARADOR_WIN;
	}
	iLong = (int) sDirectorio.length ();
	iPos = BuscarDesdeAtrasCaracter ( sDirectorio, cSep, iLong - 2 );
	if ( ( iPos > 1 ) && ( iPos < iLong - 2 ) )
	{
		sRes = sDirectorio.substr ( 0, iPos );
	}
	return ( sRes );
}

string SisFicheroExtension ( const string & sFichero )
{
	string sRes = "";

	if ( CumpleExpresionRegular ( sFichero, SF_PATRON_FICHERO ) )
	{
		sRes = SubcadenaDesde ( sFichero, SF_FIC_SEPARADOR );
	}
	return ( sRes );
}

string SisFicheroNombre ( const string & sFichero )
{
	string 	sRes = "";
	char	cSep;
	int		iPosIni;
	int		iPosFin;

	if ( CumpleExpresionRegular ( sFichero, SF_PATRON_FICHERO ) )
	{
		if ( ContieneCaracter ( sFichero, SF_DIR_SEPARADOR ) )
		{
			cSep = SF_DIR_SEPARADOR;
		}
		else
		{
			cSep = SF_DIR_SEPARADOR_WIN;
		}
		iPosIni = BuscarDesdeAtrasCaracter ( sFichero, cSep ) + 1;
		iPosFin = BuscarDesdeAtrasCaracter ( sFichero, SF_FIC_SEPARADOR );
		sRes = sFichero.substr ( iPosIni, iPosFin - iPosIni );
	}
	return ( sRes );
}

string SisComponerFichero ( const string & sNombre, const string & sExtension )
{
	string sFichero;

	// Nombre + '.' + extensión; si no hay extensión, sólo el nombre (equivalente
	// a CadDuplicar ( p_cNombre ) de la versión C).
	if ( ! sExtension.empty () )
	{
		sFichero = sNombre + SF_FIC_SEPARADOR + sExtension;
	}
	else
	{
		sFichero = sNombre;
	}
	return ( sFichero );
}

string SisRutaDirectorio ( const string & sRuta )
{
	string 	sRes = "";
	int		iPos;
	char	cSep;

	if ( SisEsRutaValida ( sRuta ) )
	{
		if ( ContieneCaracter ( sRuta, SF_DIR_SEPARADOR ) )
		{
			cSep = SF_DIR_SEPARADOR;
		}
		else
		{
			cSep = SF_DIR_SEPARADOR_WIN;
		}
		iPos = BuscarDesdeAtrasCaracter ( sRuta, cSep );
		sRes = sRuta.substr ( 0, iPos );
	}
	return ( sRes );
}

string SisRutaFichero ( const string & sRuta )
{
	string 	sRes = "";
	int		iPos;
	char	cSep;

	if ( SisEsRutaValida ( sRuta ) )
	{
		if ( ContieneCaracter ( sRuta, SF_DIR_SEPARADOR ) )
		{
			cSep = SF_DIR_SEPARADOR;
		}
		else
		{
			cSep = SF_DIR_SEPARADOR_WIN;
		}
		iPos = BuscarDesdeAtrasCaracter ( sRuta, cSep );
		// El nombre de fichero es todo lo que hay tras el último separador.
		sRes = sRuta.substr ( iPos + 1 );
	}
	return ( sRes );
}

int SisRutaNumSubdirectorios ( const string & sRuta )
{
	int		iRes = 0;
	string	sDirectorio = SisRutaDirectorio ( sRuta );
	if ( ! sDirectorio.empty () )
	{
		iRes = SisDirectorioNumSubdirectorios ( sDirectorio );
	}
	return ( iRes );
}

string SisRutaSubdirectorio ( const string & sRuta, int iNivel )
{
	string 	sRes = "";
	string	sDirectorio = SisRutaDirectorio ( sRuta );
	if ( ! sDirectorio.empty () )
	{
		sRes = SisDirectorioSubdirectorio ( sDirectorio, iNivel );
	}
	return ( sRes );
}

string SisComponerRuta ( const string & sDirectorio, const string & sFichero, int iDirActualPorDef )
{
	string sRuta = "";

	if ( SisEsFicheroValido ( sFichero ) || SisEsSubdirectorioValido ( sFichero ) )
	{
		if ( SisEsRutaValida ( sDirectorio ) )
		{
			sRuta = sDirectorio + SF_DIR_SEPARADOR + sFichero;
		}
		else
		{
			sRuta = string ( SF_DIR_ACTUAL ) + SF_DIR_SEPARADOR + sFichero;
		}
	}
	else
	{
		if ( SisEsRutaValida ( sDirectorio ) )
		{
			sRuta = string ( sDirectorio );
		}
		else
		{
			if ( iDirActualPorDef )
			{
				sRuta = string ( SF_DIR_ACTUAL );
			}
		}
	}
	return ( sRuta );
}

string SisComponerRutaExt ( const string & sDirectorio, const string & sSubdirectorio, const string & sFichero, int iDirActualPorDef )
{
	string sRuta;

	if ( SisEsSubdirectorioValido ( sSubdirectorio ) )
	{
		string sDirComp = SisComponerRuta ( sDirectorio, sSubdirectorio, 0 );
		sRuta = SisComponerRuta ( sDirComp, sFichero, iDirActualPorDef );
	}
	else
	{
		sRuta = SisComponerRuta ( sDirectorio, sFichero, iDirActualPorDef );
	}
	return ( sRuta );
}

string SisNormalizarRuta ( const string & sRuta )
{
	return ( ReemplazarTodos ( ReemplazarTodos ( sRuta, "\\\\", "/" ), '\\', '/' ) );
}

string SisNormalizarRutaWindows ( const string & sRuta )
{
	return ( ReemplazarTodos ( ReemplazarTodos ( ReemplazarTodos ( sRuta, "\\\\", "\\" ), "\\:", ":" ), '/', '\\' ) );
}


bool SisEsRutaValida ( const string & sRuta )
{
	bool 	bRes = false;
	bool	bWindows = false;
	string 	sRutaNorm;

	if ( ! sRuta.empty () )
	{
		if ( ContieneCaracter ( sRuta, '\\' ) ||
			 ( ( sRuta.length () > 1 ) && ( sRuta.at ( 1 ) == ':' ) ) )
		{
			sRutaNorm = SisNormalizarRutaWindows ( sRuta );
			bWindows = true;
		}
		else
		{
			sRutaNorm = SisNormalizarRuta ( sRuta );
		}
		if ( bWindows )
		{
			if ( CumpleExpresionRegular ( sRutaNorm, SF_PATRON_RUTA_WIN ) ||
				 CumpleExpresionRegular ( sRutaNorm, SF_PATRON_RUTA_REL_WIN ) ||
				 CumpleExpresionRegular ( sRutaNorm, SF_PATRON_RUTA_REL_WIN_2 ) )
			{
				bRes = true;
			}
		}
		else
		{
			if ( CumpleExpresionRegular ( sRutaNorm, SF_PATRON_RUTA ) ||
				 CumpleExpresionRegular ( sRutaNorm, SF_PATRON_RUTA_REL ) ||
				 CumpleExpresionRegular ( sRutaNorm, SF_PATRON_RUTA_REL_2 ) )
			{
				bRes = true;
			}
		}
	}
	return ( bRes );
}

bool SisEsRutaValidaSistema ( const string & sRuta )
{
	string 	sRutaNorm;
	bool 	bRes = false;

# if ( defined ( CYGWIN ) )
	sRutaNorm = SisNormalizarRuta ( sRuta );
	if ( CumpleExpresionRegular ( sRutaNorm, SF_PATRON_RUTA ) ||
		 CumpleExpresionRegular ( sRutaNorm, SF_PATRON_RUTA_REL ) ||
		 CumpleExpresionRegular ( sRutaNorm, SF_PATRON_RUTA_REL_2 ) )
# elif ( defined ( WIN ) )
	sRutaNorm = SisNormalizarRutaWindows ( sRuta );
	if ( CumpleExpresionRegular ( sRutaNorm, SF_PATRON_RUTA_WIN ) ||
		 CumpleExpresionRegular ( sRutaNorm, SF_PATRON_RUTA_REL_WIN ) ||
		 CumpleExpresionRegular ( sRutaNorm, SF_PATRON_RUTA_REL_WIN_2 ) )
# else
	sRutaNorm = SisNormalizarRuta ( sRuta );
	if ( CumpleExpresionRegular ( sRutaNorm, SF_PATRON_RUTA ) ||
		 CumpleExpresionRegular ( sRutaNorm, SF_PATRON_RUTA_REL ) ||
		 CumpleExpresionRegular ( sRutaNorm, SF_PATRON_RUTA_REL_2 ) )
#     endif
	{
		bRes = true;
	}
	return ( bRes );
}

bool SisRutaEsEstiloWindows ( const string & sRuta )
{
	bool bRes = false;

	if ( SisEsRutaValida ( sRuta ) )
	{
		if ( ContieneCaracter ( sRuta, '\\' ) ||
			 ( ( sRuta.length () > 1 ) && ( sRuta.at ( 1 ) == ':' ) ) )
		{
			bRes = true;
		}
	}
	return ( bRes );
}

string SisRutaEstiloWindows ( const string & sRuta )
{
	return ( SisRutaEstiloWindowsExt ( sRuta, 'C' ) );
}

string SisRutaEstiloWindowsExt ( const string & sRuta, char cUnidad )
{
	string	sResultado = "";

	if ( SisEsRutaValida ( sRuta ) && isalpha ( cUnidad ) )
	{
		if ( ! SisRutaEsEstiloWindows ( sRuta ) )
		{
			vector<string>	vecPartes = SisDividirEnPartes ( sRuta, '/' );
			bool			bRelativa = SisEsRutaRelativa ( sRuta );

			/* La unidad solo se antepone si la ruta es ABSOLUTA. Antes se ponia
			   siempre, y toda ruta relativa salia convertida en otra cosa: "../log"
			   daba "C:\\..\log", que no existe, y por ahi SisExisteDirectorio
			   contestaba que no a directorios que si estaban. La version C de este
			   mismo modulo ya lo hacia bien: la comprobacion se perdio al pasarlo a
			   C++.

			   De paso desaparece la barra doble: el ":\\" de aqui y el '\\' del
			   bucle se sumaban, y "/tmp" salia como "C:\\tmp". */
			if ( ! bRelativa )
			{
				sResultado.push_back ( static_cast<char>(toupper ( cUnidad )) );
				sResultado.append ( ":" );
			}
			for ( size_t i = 0; i < vecPartes.size (); i = i + 1 )
			{
				if ( ( ! bRelativa ) || ( i > 0 ) )
				{
					sResultado.push_back ( '\\' );
				}
				sResultado.append ( vecPartes [ i ] );
			}
		}
		else
		{
			sResultado.append ( sRuta );
		}
	}
	return ( sResultado );
}

string SisRutaEstiloUnix ( const string & sRuta )
{
	string	sResultado = "";

	if ( SisEsRutaValida ( sRuta ) )
	{
		if ( SisRutaEsEstiloWindows ( sRuta ) )
		{
			string sRutaCopia = ReemplazarTodos ( ReemplazarTodos ( sRuta, '/', '\\' ), "\\\\", "\\" );

			bool bEsAbsoluto = CumpleExpresionRegular ( sRutaCopia, SF_PATRON_RUTA_WIN );
			int  iParteIni   = bEsAbsoluto ? 1 : 0;
			// Se divide por '\\' de forma coherente (la versión C original dividía por
			// '\\' pero extraña las palabras con '/'; corregido en ambas versiones).
			vector<string> vecPartes = SisDividirEnPartes ( sRutaCopia, '\\' );

			if ( bEsAbsoluto )
			{
				sResultado.push_back ( '/' );
			}
			for ( size_t i = (size_t) iParteIni; i < vecPartes.size (); i = i + 1 )
			{
				if ( (int) i > iParteIni )
				{
					sResultado.push_back ( '/' );
				}
				sResultado.append ( vecPartes [ i ] );
			}
		}
		else
		{
			sResultado.append ( sRuta );
		}
	}
	return ( sResultado );
}

string SisRutaEstiloCygwin ( const string & sRuta )
{
	string	sResultado = "";

	if ( SisEsRutaValida ( sRuta ) )
	{
		if ( SisRutaEsEstiloWindows ( sRuta ) )
		{
			// Aseguramos que todo esta en Windows
			string	sRutaCopia   = SisNormalizarRutaWindows ( sRuta );
			bool	bEsAbsoluto  = CumpleExpresionRegular ( sRutaCopia, SF_PATRON_RUTA_WIN );
			int		iParteIni    = bEsAbsoluto ? 1 : 0;
			char	cUnidad      = sRutaCopia.empty () ? 0 : sRutaCopia.at ( 0 );
			vector<string> vecPartes = SisDividirEnPartes ( sRutaCopia, '\\' );

			if ( bEsAbsoluto )
			{
				sResultado.append ( "/cygdrive/" );
				sResultado.push_back ( static_cast<char>(tolower ( cUnidad )));
			}
			for ( size_t i = (size_t) iParteIni; i < vecPartes.size (); i = i + 1 )
			{
				// En ruta absoluta hay que separar también la primera parte del prefijo
				// "/cygdrive/<unidad>"; en relativa, no lleva '/' inicial.
				if ( ( (int) i > iParteIni ) || bEsAbsoluto )
				{
					sResultado.push_back ( '/' );
				}
				sResultado.append ( vecPartes [ i ] );
			}
		}
		else
		{
			sResultado.append ( sRuta );
		}
	}
	return ( sResultado );
}

string SisRutaEstiloSistema ( const string & sRuta )
{
	string sResultado;

# if ( defined ( CYGWIN ) )
	sResultado = SisRutaEstiloCygwin ( sRuta );
# elif ( defined ( WIN ) )
	sResultado = SisRutaEstiloWindows ( sRuta );
# else
	sResultado = SisRutaEstiloUnix ( sRuta );
# endif
	return ( sResultado );
}

bool SisEsRutaAbsoluta ( const string & sRuta )
{
	string	sRutaNorm;
	bool	bRes = false;

	if ( SisRutaEsEstiloWindows ( sRuta ) )
	{
		sRutaNorm = SisNormalizarRutaWindows ( sRuta );
	}
	else
	{
		sRutaNorm = SisNormalizarRuta ( sRuta );
	}
	if ( CumpleExpresionRegular ( sRutaNorm, SF_PATRON_RUTA ) ||
		 CumpleExpresionRegular ( sRutaNorm, SF_PATRON_RUTA_WIN ) )
	{
		bRes = true;
	}
	return ( bRes );
}

bool SisEsRutaRelativa ( const string & sRuta )
{
	string	sRutaNorm;
	bool	bRes = false;

	if ( SisRutaEsEstiloWindows ( sRuta ) )
	{
		sRutaNorm = SisNormalizarRutaWindows ( sRuta );
	}
	else
	{
		sRutaNorm = SisNormalizarRuta ( sRuta );
	}
	if ( CumpleExpresionRegular ( sRutaNorm, SF_PATRON_RUTA_REL ) ||
		 CumpleExpresionRegular ( sRutaNorm, SF_PATRON_RUTA_REL_2 ) ||
		 CumpleExpresionRegular ( sRutaNorm, SF_PATRON_RUTA_REL_WIN ) ||
		 CumpleExpresionRegular ( sRutaNorm, SF_PATRON_RUTA_REL_WIN_2 ) )
	{
		bRes = true;
	}
	return ( bRes );
}


string SisDirectorioActual ()
{
	string sDirectorio = "";
	try
	{
		sDirectorio = fs::current_path ().string ();
	}
	catch ( ... )
	{
	}
	return ( sDirectorio );
}

bool SisEstDirectorioActual ( const string & sDirectorio )
{
	bool bRes = false;
	string sDirNorm = SisRutaEstiloSistema ( sDirectorio );

	try
	{
		fs::current_path ( sDirNorm );
		bRes = true;
	}
	catch ( ... )
	{
	}
	return ( bRes );
}

/* Solo en Windows: el "directorio del sistema" es C:\Windows\System32, un
   concepto que no tiene equivalente en POSIX. Su gemela del stack C,
   SisDirectorioSistema, ya estaba declarada solo bajo WIN. */
#if ( defined ( WIN ) )
string SisCadenaDirectorioSistema ()
{
	vector<char> buffer ( SF_MAX_TAM_RUTA );
	unsigned int uiTam = GetSystemDirectoryA ( buffer.data (), (UINT) buffer.size () );
	return ( string ( buffer.data (), uiTam ) );
}
#endif

string SisCadenaDirectorioFuentes ()
{
	return ( string ( "" ) );
}

bool SisExisteFichero ( const string & sRuta )
{
	bool bRes = false;
	string sRutaNorm = SisRutaEstiloSistema ( sRuta );

	try
	{
		/* Se pregunta "existe y NO es un directorio". Con is_regular_file no
		   valia: es mas estricto y dejaba fuera FIFOs, sockets y dispositivos,
		   que si cuentan como fichero. Mismo criterio que la rama POSIX de
		   SisExisteFichero del stack C. */
		fs::path ruta ( sRutaNorm );
		if ( fs::exists ( ruta ) )
		{
			bRes = ( ! fs::is_directory ( ruta ) );
		}
	}
	catch ( ... )
	{
	}
	return ( bRes );
}

bool SisExisteFicheroExt ( const string & sDirectorio, const string & sFichero )
{
	return ( SisExisteFichero ( SisComponerRuta ( sDirectorio, sFichero, 0 ) ) );
}

bool SisExisteDirectorio ( const string & sRuta )
{
	bool bRes = false;
	string sRutaNorm = SisRutaEstiloSistema ( sRuta );

	try
	{
		fs::path ruta ( sRutaNorm );
		if ( fs::exists ( ruta ) )
		{
			bRes = fs::is_directory ( ruta );
		}
	}
	catch ( ... )
	{
	}
	return ( bRes );
}

bool SisExisteDirectorioExt ( const string & sDirectorio, const string & sSubdirectorio )
{
	return ( SisExisteDirectorio ( SisComponerRuta ( sDirectorio, sSubdirectorio, 0 ) ) );
}

bool SisCrearFichero ( const string & sRuta )
{
	bool bRes = false;
	string sRutaNorm = SisRutaEstiloSistema ( sRuta );

	try
	{
		if ( ! SisExisteFichero ( sRutaNorm ) )
		{
			ofstream archivo ( sRutaNorm );
			if ( archivo.is_open () )
			{
				archivo.close ();
				bRes = true;
			}
		}
	}
	catch ( ... )
	{
	}
	return ( bRes );
}

bool SisCrearFicheroExt ( const string & sDirectorio, const string & sFichero )
{
	return ( SisCrearFichero ( SisComponerRuta ( sDirectorio, sFichero, 0 ) ) );
}

bool SisCrearDirectorio ( const string & sDirectorio )
{
	bool bRes = false;
	string sDirNorm = SisRutaEstiloSistema ( sDirectorio );

	try
	{
		fs::path directorio ( sDirNorm );
		bRes = ( fs::create_directories ( directorio ) );
	}
	catch ( ... )
	{
	}
	return ( bRes );
}

bool SisCrearDirectorioExt ( const string & sDirectorio, const string & sSubdirectorio )
{
	return ( SisCrearDirectorio ( SisComponerRuta ( sDirectorio, sSubdirectorio, 0 ) ) );
}

bool SisEliminarFichero ( const string & sRuta )
{
	bool bRes = false;
	string sRutaNorm = SisRutaEstiloSistema ( sRuta );

	try
	{
		fs::path ruta ( sRutaNorm );
		bRes = ( fs::remove ( ruta ) );
	}
	catch ( ... )
	{
	}
	return ( bRes );
}

bool SisEliminarFicheroExt ( const string & sDirectorio, const string & sFichero )
{
	return ( SisEliminarFichero ( SisComponerRuta ( sDirectorio, sFichero, 0 ) ) );
}

string SisMascaraBusquedaEnDirectorio ( const string & sDirectorio )
{
	string sRes;

	if ( ! sDirectorio.empty () )
	{
		sRes = sDirectorio + SF_DIR_SEPARADOR + SF_MASCARA_BUSQUEDA;
	}
	else
	{
		sRes = string ( SF_MASCARA_BUSQUEDA );
	}
	return ( sRes );
}

bool SisEliminarDirectorio ( const string & sDirectorio )
{
	bool bRes = false;
	string sDirNorm = SisRutaEstiloSistema ( sDirectorio );

	try
	{
		fs::path directorio ( sDirNorm );
		bRes = ( fs::remove_all ( directorio ) > 0 );
	}
	catch ( ... )
	{
	}
	return ( bRes );
}

bool SisEliminarDirectorioExt ( const string & sDirectorio, const string & sSubdirectorio )
{
	return ( SisEliminarDirectorio ( SisComponerRuta ( sDirectorio, sSubdirectorio, 0 ) ) );
}

bool SisVaciarDirectorio ( const string & sDirectorio )
{
	bool bRes = false;
	string sDirNorm = SisRutaEstiloSistema ( sDirectorio );

	try
	{
		fs::path directorio ( sDirNorm );
		if ( fs::exists ( directorio ) && fs::is_directory ( directorio ) )
		{
			for ( const auto & entrada : fs::directory_iterator ( directorio ) )
			{
				fs::remove_all ( entrada.path () );
			}
			bRes = true;
		}
	}
	catch ( ... )
	{
	}
	return ( bRes );
}

bool SisVaciarDirectorioExt ( const string & sDirectorio, const string & sSubdirectorio )
{
	return ( SisVaciarDirectorio ( SisComponerRuta ( sDirectorio, sSubdirectorio, 0 ) ) );
}

bool SisCopiarFichero ( const string & sRutaOrig, const string & sRutaDest, bool bEliminar )
{
	bool bRes = false;
	string sRutaOrigNorm = SisRutaEstiloSistema ( sRutaOrig );
	string sRutaDestNorm = SisRutaEstiloSistema ( sRutaDest );

	try
	{
		fs::path origen ( sRutaOrigNorm );
		fs::path destino ( sRutaDestNorm );

		// bEliminar actúa como "sobrescribir el destino si existe".
		if ( bEliminar )
		{
			fs::copy_file ( origen, destino, fs::copy_options::overwrite_existing );
			bRes = true;
		}
		else
		{
			if ( ! fs::exists ( destino ) )
			{
				fs::copy_file ( origen, destino );
				bRes = true;
			}
		}
	}
	catch ( ... )
	{
	}
	return ( bRes );
}

bool SisCopiarFicheroExt ( const string & sDirOrig, const string & sFicOrig, const string & sDirDest, const string & sFicDest, bool bEliminar )
{
	// Si no se indica fichero destino se reutiliza el nombre de origen (como en la versión C).
	const string & sFicD = sFicDest.empty () ? sFicOrig : sFicDest;
	return ( SisCopiarFichero ( SisComponerRuta ( sDirOrig, sFicOrig, 0 ),
		SisComponerRuta ( sDirDest, sFicD, 0 ), bEliminar ) );
}

bool SisMoverFichero ( const string & sRutaOrig, const string & sRutaDest, bool bEliminar )
{
	bool bRes = false;
	string sRutaOrigNorm = SisRutaEstiloSistema ( sRutaOrig );
	string sRutaDestNorm = SisRutaEstiloSistema ( sRutaDest );

	try
	{
		fs::path origen ( sRutaOrigNorm );
		fs::path destino ( sRutaDestNorm );

		if ( fs::exists ( destino ) )
		{
			if ( ! bEliminar )
			{
				// Destino ya existe y no se permite sobrescribir.
				return ( false );
			}
			fs::remove ( destino );
		}
		fs::rename ( origen, destino );
		bRes = true;
	}
	catch ( ... )
	{
	}
	return ( bRes );
}

bool SisMoverFicheroExt ( const string & sDirOrig, const string & sFicOrig,
                       const string & sDirDest, const string & sFicDest, bool bEliminar )
{
	const string & sFicD = sFicDest.empty () ? sFicOrig : sFicDest;
	return ( SisMoverFichero ( SisComponerRuta ( sDirOrig, sFicOrig, 0 ),
		SisComponerRuta ( sDirDest, sFicD, 0 ), bEliminar ) );
}

bool SisRutaComprimida ( const string & sRuta )
{
	bool bRes = false;
	string sRutaNorm = SisRutaEstiloSistema ( sRuta );

# if ( defined ( WIN ) || defined ( CYGWIN ) )
	unsigned int	uiAtributos;

	uiAtributos = SFW32Atributos ( sRutaNorm.c_str () );
	if ( uiAtributos != SFW32_ATRIB_INVALIDO )
	{
		if ( ( uiAtributos & SFW32_ATRIB_COMPRIMIDO ) == SFW32_ATRIB_COMPRIMIDO )
		{
			bRes = true;
		}
	}

# else
	// LIMITACION CONOCIDA, no un descuido: en POSIX puro ( Linux ) se contesta
	// que no. Decidido asi el 2026-09-19.
	// Los atributos son del sistema de ficheros, no del sistema operativo, asi
	// que en CYGWIN SI se resuelven, por la rama de arriba. Sobre Linux habria
	// que preguntarselo al montaje en tiempo de ejecucion ( ntfs-3g los expone
	// como el atributo extendido system.ntfs_attrib ) y solo valdria sobre
	// montajes NTFS. Se deja asi a proposito porque el modo Linux todavia no
	// existe en el build; cuando exista se revisa entero, y con el la cuestion
	// de fondo: que este false no distingue "no lo tiene" de "aqui no se puede
	// saber".
# endif
	return ( bRes );
}

bool SisRutaEncriptada ( const string & sRuta )
{
	bool bRes = false;
	string sRutaNorm = SisRutaEstiloSistema ( sRuta );

# if ( defined ( WIN ) || defined ( CYGWIN ) )
	unsigned int	uiAtributos;

	uiAtributos = SFW32Atributos ( sRutaNorm.c_str () );
	if ( uiAtributos != SFW32_ATRIB_INVALIDO )
	{
		if ( ( uiAtributos & SFW32_ATRIB_ENCRIPTADO ) == SFW32_ATRIB_ENCRIPTADO )
		{
			bRes = true;
		}
	}

# else
	// LIMITACION CONOCIDA, no un descuido: en POSIX puro ( Linux ) se contesta
	// que no. Decidido asi el 2026-09-19.
	// Los atributos son del sistema de ficheros, no del sistema operativo, asi
	// que en CYGWIN SI se resuelven, por la rama de arriba. Sobre Linux habria
	// que preguntarselo al montaje en tiempo de ejecucion ( ntfs-3g los expone
	// como el atributo extendido system.ntfs_attrib ) y solo valdria sobre
	// montajes NTFS. Se deja asi a proposito porque el modo Linux todavia no
	// existe en el build; cuando exista se revisa entero, y con el la cuestion
	// de fondo: que este false no distingue "no lo tiene" de "aqui no se puede
	// saber".
# endif
	return ( bRes );
}

bool SisRutaOculta ( const string & sRuta )
{
	bool bRes = false;
	string sRutaNorm = SisRutaEstiloSistema ( sRuta );

# if ( defined ( WIN ) )
	unsigned int	uiAtributos;

	uiAtributos = SFW32Atributos ( sRutaNorm.c_str () );
	if ( uiAtributos != SFW32_ATRIB_INVALIDO )
	{
		if ( ( uiAtributos & SFW32_ATRIB_OCULTO ) == SFW32_ATRIB_OCULTO )
		{
			bRes = true;
		}
	}
# else
	// En POSIX "oculto" no es un atributo del fichero sino una convencion del
	// nombre: lo esta el que empieza por punto. El directorio actual ( "." ) y
	// el padre ( ".." ) no cuentan, igual que hace ls.
	// Esta rama la usa tambien Cygwin-POSIX, donde conviven dos nociones de
	// "oculto" que NO se solapan: el punto y el atributo de NTFS ( medido: un
	// fichero con punto delante no queda marcado en NTFS ). Se elige el punto
	// a proposito, que es la semantica del modo en que se compilo. En
	// Windows puro manda el atributo, que es la rama de arriba.
	if ( access ( sRutaNorm.c_str (), F_OK ) == 0 )
	{
		string sFichero = fs::path ( sRutaNorm ).filename ().string ();

		if ( ! sFichero.empty () )
		{
			if ( sFichero [ 0 ] == SF_FIC_SEPARADOR )
			{
				if ( sFichero != SF_DIR_ACTUAL )
				{
					if ( sFichero != SF_DIR_PADRE )
					{
						bRes = true;
					}
				}
			}
		}
	}
# endif
	return ( bRes );
}


bool SisFicheroEsAccesible ( const string & sRuta )
{
	bool bRes = false;
	string sRutaNorm = SisRutaEstiloSistema ( sRuta );

# if ( defined ( WIN ) )
	unsigned int	uiAtributos;

	uiAtributos = SFW32Atributos ( sRutaNorm.c_str () );
	if ( uiAtributos != SFW32_ATRIB_INVALIDO )
	{
		// Accesible == NO está offline.
		if ( ( uiAtributos & SFW32_ATRIB_FUERA_DE_LINEA ) != SFW32_ATRIB_FUERA_DE_LINEA )
		{
			bRes = true;
		}
	}

# else
	// En POSIX no existe el "fuera de linea" de Windows. Lo que si se puede
	// preguntar es lo que la funcion promete: si el proceso puede leer la ruta.
	// <filesystem> no vale para esto: status ().permissions () dice que bits
	// tiene el fichero, no si ESTE proceso puede con el.
	// La usa tambien Cygwin-POSIX, por lo mismo que SisRutaDeSoloLectura.
	if ( access ( sRutaNorm.c_str (), R_OK ) == 0 )
	{
		bRes = true;
	}
# endif
	return ( bRes );
}

bool SisRutaDeSoloLectura ( const string & sRuta )
{
	bool bRes = false;
	string sRutaNorm = SisRutaEstiloSistema ( sRuta );

# if ( defined ( WIN ) )
	unsigned int	uiAtributos;

	uiAtributos = SFW32Atributos ( sRutaNorm.c_str () );
	if ( uiAtributos != SFW32_ATRIB_INVALIDO )
	{
		if ( ( uiAtributos & SFW32_ATRIB_SOLO_LECTURA ) == SFW32_ATRIB_SOLO_LECTURA )
		{
			bRes = true;
		}
	}

# else
	// "Solo lectura" en POSIX es no tener permiso de escritura. Se comprueba
	// antes que la ruta exista: una ruta que no esta no es de solo lectura.
	// Se usa access y no <filesystem> por lo mismo que en SisFicheroEsAccesible:
	// el bit owner_write es el del propietario, y quien pregunta puede no serlo.
	// Ojo: access mira el usuario REAL del proceso, asi que ejecutando como
	// root sale que se puede escribir aunque el modo sea 0444.
	// Esta rama la usa tambien Cygwin-POSIX, y ahi es MEJOR que la de Win32:
	// medido, access ve tanto el atributo de solo lectura de NTFS ( que Cygwin
	// refleja en el modo ) como un chmod 0444 que no llega a tocar NTFS.
	if ( access ( sRutaNorm.c_str (), F_OK ) == 0 )
	{
		if ( access ( sRutaNorm.c_str (), W_OK ) != 0 )
		{
			bRes = true;
		}
	}
# endif
	return ( bRes );
}

bool SisRutaDelSistema ( const string & sRuta )
{
	bool bRes = false;
	string sRutaNorm = SisRutaEstiloSistema ( sRuta );

# if ( defined ( WIN ) || defined ( CYGWIN ) )
	unsigned int	uiAtributos;

	uiAtributos = SFW32Atributos ( sRutaNorm.c_str () );
	if ( uiAtributos != SFW32_ATRIB_INVALIDO )
	{
		if ( ( uiAtributos & SFW32_ATRIB_SISTEMA ) == SFW32_ATRIB_SISTEMA )
		{
			bRes = true;
		}
	}

# else
	// LIMITACION CONOCIDA, no un descuido: en POSIX puro ( Linux ) se contesta
	// que no. Decidido asi el 2026-09-19.
	// Los atributos son del sistema de ficheros, no del sistema operativo, asi
	// que en CYGWIN SI se resuelven, por la rama de arriba. Sobre Linux habria
	// que preguntarselo al montaje en tiempo de ejecucion ( ntfs-3g los expone
	// como el atributo extendido system.ntfs_attrib ) y solo valdria sobre
	// montajes NTFS. Se deja asi a proposito porque el modo Linux todavia no
	// existe en el build; cuando exista se revisa entero, y con el la cuestion
	// de fondo: que este false no distingue "no lo tiene" de "aqui no se puede
	// saber".
# endif
	return ( bRes );
}

bool SisFicheroEsTemporal ( const string & sRuta )
{
	bool bRes = false;
	string sRutaNorm = SisRutaEstiloSistema ( sRuta );

# if ( defined ( WIN ) || defined ( CYGWIN ) )
	unsigned int	uiAtributos;

	uiAtributos = SFW32Atributos ( sRutaNorm.c_str () );
	if ( uiAtributos != SFW32_ATRIB_INVALIDO )
	{
		if ( ( uiAtributos & SFW32_ATRIB_TEMPORAL ) == SFW32_ATRIB_TEMPORAL )
		{
			bRes = true;
		}
	}

# else
	try
	{
		/* LIMITACION CONOCIDA, igual que en los demas atributos de NTFS: en
		   POSIX puro no hay marca de "fichero temporal", asi que se contesta
		   otra cosa parecida —si esta colgando del directorio temporal—, que
		   NO es lo mismo. En Cygwin si se lee el atributo de verdad, por la
		   rama de arriba. */
		fs::path ruta = fs::path ( sRutaNorm ).lexically_normal ();
		fs::path dirTemp = fs::temp_directory_path ().lexically_normal ();

		/* Por componentes, no como texto: comparar prefijos daba por temporal
		   "/tmpx/a" o "/tmp2/a" cuando el temporal es "/tmp". Si el directorio
		   acaba en separador se le quita, o su ultimo componente seria vacio y
		   nada colgaria de el. Cuelga si la ruta relativa no sube ( ".." ) y no
		   es el propio directorio ( "." ). */
		if ( ! dirTemp.has_filename () )
		{
			dirTemp = dirTemp.parent_path ();
		}
		fs::path relativa = ruta.lexically_relative ( dirTemp );
		if ( ! relativa.empty () )
		{
			const fs::path primero = *relativa.begin ();
			if ( primero != ".." )
			{
				if ( primero != "." )
				{
					bRes = true;
				}
			}
		}
	}
	catch ( ... )
	{
	}
# endif
	return ( bRes );
}

bool SisFicheroAsociadoAAplicacion ( const string & sRuta )
{
	bool bRes = false;
	string sRutaNorm = SisRutaEstiloSistema ( sRuta );

# if ( defined ( WIN ) || defined ( CYGWIN ) )
	unsigned int	uiAtributos;

	uiAtributos = SFW32Atributos ( sRutaNorm.c_str () );
	if ( uiAtributos != SFW32_ATRIB_INVALIDO )
	{
		if ( ( uiAtributos & SFW32_ATRIB_PUNTO_ANALISIS ) == SFW32_ATRIB_PUNTO_ANALISIS )
		{
			bRes = true;
		}
	}

# else
	// LIMITACION CONOCIDA, no un descuido: en POSIX puro ( Linux ) se contesta
	// que no. Decidido asi el 2026-09-19.
	// Los atributos son del sistema de ficheros, no del sistema operativo, asi
	// que en CYGWIN SI se resuelven, por la rama de arriba. Sobre Linux habria
	// que preguntarselo al montaje en tiempo de ejecucion ( ntfs-3g los expone
	// como el atributo extendido system.ntfs_attrib ) y solo valdria sobre
	// montajes NTFS. Se deja asi a proposito porque el modo Linux todavia no
	// existe en el build; cuando exista se revisa entero, y con el la cuestion
	// de fondo: que este false no distingue "no lo tiene" de "aqui no se puede
	// saber".
# endif
	return ( bRes );
}

bool SisFicheroConOptimizacionEspacial ( const string & sRuta )
{
	bool bRes = false;
	string sRutaNorm = SisRutaEstiloSistema ( sRuta );

# if ( defined ( WIN ) || defined ( CYGWIN ) )
	unsigned int	uiAtributos;

	uiAtributos = SFW32Atributos ( sRutaNorm.c_str () );
	if ( uiAtributos != SFW32_ATRIB_INVALIDO )
	{
		if ( ( uiAtributos & SFW32_ATRIB_DISPERSO ) == SFW32_ATRIB_DISPERSO )
		{
			bRes = true;
		}
	}

# else
	// LIMITACION CONOCIDA, no un descuido: en POSIX puro ( Linux ) se contesta
	// que no. Decidido asi el 2026-09-19.
	// Los atributos son del sistema de ficheros, no del sistema operativo, asi
	// que en CYGWIN SI se resuelven, por la rama de arriba. Sobre Linux habria
	// que preguntarselo al montaje en tiempo de ejecucion ( ntfs-3g los expone
	// como el atributo extendido system.ntfs_attrib ) y solo valdria sobre
	// montajes NTFS. Se deja asi a proposito porque el modo Linux todavia no
	// existe en el build; cuando exista se revisa entero, y con el la cuestion
	// de fondo: que este false no distingue "no lo tiene" de "aqui no se puede
	// saber".
# endif
	return ( bRes );
}

bool SisRutaDesactivarModoSoloLectura ( const string & sRuta )
{
	bool bRes = false;
	string sRutaNorm = SisRutaEstiloSistema ( sRuta );

# if ( defined ( WIN ) )
	unsigned int	uiAtributos;
	unsigned int	uiMascara;

	uiAtributos = SFW32Atributos ( sRutaNorm.c_str () );
	if ( uiAtributos != SFW32_ATRIB_INVALIDO )
	{
		uiMascara = SFW32_ATRIB_SOLO_LECTURA;
		uiMascara = 0xFFFFFFFF ^ uiMascara;
		uiAtributos = uiAtributos & uiMascara;
		if ( SFW32PonerAtributos ( sRutaNorm.c_str (), uiAtributos ) )
		{
			bRes = true;
		}
	}
# else
	// Quitar el solo lectura en POSIX es dar permiso de escritura. Solo al
	// propietario: tocar tambien el de grupo, como se hacia antes, abre mas de
	// lo que se pide. Se mira que la ruta exista para no usar la excepcion
	// como via normal cuando simplemente no esta.
	// La usa tambien Cygwin-POSIX: medido, ahi fs::permissions limpia ademas
	// el atributo de solo lectura de NTFS, asi que cubre los dos casos.
	try
	{
		fs::path ruta ( sRutaNorm );

		if ( fs::exists ( ruta ) )
		{
			fs::permissions ( ruta, fs::perms::owner_write, fs::perm_options::add );
			bRes = true;
		}
	}
	catch ( ... )
	{
	}
# endif
	return ( bRes );
}

bool SisEsFicheroC ( const string & sRuta )
{
	bool bRes = false;

	string sFichero = SisRutaFichero ( sRuta );
	string sExt = SisFicheroExtension ( sFichero );
	if ( ! sExt.empty () )
	{
		bRes = ( ( sExt == EXT_FIC_CABECERA_C ) ||
			( sExt == EXT_FIC_CODIGO_C ) ||
			( sExt == EXT_FIC_CODIGO_C_2 ) ||
			( sExt == EXT_FIC_CODIGO_C_3 ) ||
			( sExt == EXT_FIC_CODIGO_C_4 ) );
	}
	return ( bRes );
}

bool SisEsFicheroCodigoC ( const string & sRuta )
{
	bool bRes = false;

	string sFichero = SisRutaFichero ( sRuta );
	string sExt = SisFicheroExtension ( sFichero );
	if ( ! sExt.empty () )
	{
		bRes = ( ( sExt == EXT_FIC_CODIGO_C ) ||
				( sExt == EXT_FIC_CODIGO_C_2 ) ||
				( sExt == EXT_FIC_CODIGO_C_3 ) ||
				( sExt == EXT_FIC_CODIGO_C_4 ) );
	}
	return ( bRes );
}

bool SisEsFicheroCabeceraC ( const string & sRuta )
{
	bool bRes = false;

	string sFichero = SisRutaFichero ( sRuta );
	string sExt = SisFicheroExtension ( sFichero );
	if ( ! sExt.empty () )
	{
		bRes = ( sExt == EXT_FIC_CABECERA_C );
	}
	return ( bRes );
}

bool SisEsFicheroXML ( const string & sRuta )
{
	bool bRes = false;

	string sFichero = SisRutaFichero ( sRuta );
	string sExt = SisFicheroExtension ( sFichero );
	if ( ! sExt.empty () )
	{
		bRes = ( sExt == EXT_FIC_XML );
	}
	return ( bRes );
}

bool SisEsFicheroHTML ( const string & sRuta )
{
	bool bRes = false;

	string sFichero = SisRutaFichero ( sRuta );
	string sExt = SisFicheroExtension ( sFichero );
	if ( ! sExt.empty () )
	{
		bRes = ( ( sExt == EXT_FIC_HTML ) ||
				( sExt == EXT_FIC_HTML_2 ) );
	}
	return ( bRes );
}

bool SisEsFicheroSHP ( const string & sRuta )
{
	bool bRes = false;

	string sFichero = SisRutaFichero ( sRuta );
	string sExt = SisFicheroExtension ( sFichero );
	if ( ! sExt.empty () )
	{
		bRes = ( sExt == EXT_FIC_SHAPE );
	}
	return ( bRes );
}

bool SisEsFicheroDBF ( const string & sRuta )
{
	bool bRes = false;

	string sFichero = SisRutaFichero ( sRuta );
	string sExt = SisFicheroExtension ( sFichero );
	if ( ! sExt.empty () )
	{
		bRes = ( sExt == EXT_FIC_DBASE );
	}
	return ( bRes );
}

string SisResolverDirectorioRelativo ( const string & sRutaBase, const string & sRutaRelativa )
{
	string sRes = "";

	if ( SisEsRutaAbsoluta ( sRutaBase ) && SisEsRutaRelativa ( sRutaRelativa ) )
	{
		string	sRutaBaseCopia;
		string	sRutaRelativaCopia;
		bool	bWindows;
		char	cSep;
		char	cUnidad = 0;

		if ( SisRutaEsEstiloWindows ( sRutaBase ) )
		{
			sRutaBaseCopia     = SisRutaEstiloWindows ( sRutaBase );
			sRutaRelativaCopia = SisRutaEstiloWindows ( sRutaRelativa );
			bWindows = true;
			cSep     = '\\';
			if ( ! sRutaBaseCopia.empty () )
			{
				cUnidad        = sRutaBaseCopia.at ( 0 );
				sRutaBaseCopia = ( sRutaBaseCopia.length () > 2 ) ? sRutaBaseCopia.substr ( 2 ) : string ( "" );
			}
		}
		else
		{
			sRutaBaseCopia     = SisRutaEstiloUnix ( sRutaBase );
			sRutaRelativaCopia = SisRutaEstiloUnix ( sRutaRelativa );
			bWindows = false;
			cSep     = '/';
		}

		if ( ! sRutaBaseCopia.empty () && ! sRutaRelativaCopia.empty () &&
			 ( sRutaBaseCopia.at ( 0 ) == cSep ) && ( sRutaRelativaCopia.at ( 0 ) == '.' ) )
		{
			string			sResultado = "";
			if ( bWindows )
			{
				sResultado.push_back ( cUnidad );
				sResultado.push_back ( ':' );
			}

			vector<string>	vecPartesBase = SisDividirEnPartes ( sRutaBaseCopia, cSep );
			vector<string>	vecPartesRel  = SisDividirEnPartes ( sRutaRelativaCopia, cSep );

			int iPartes    = (int) vecPartesBase.size ();
			int iPartesRel = (int) vecPartesRel.size ();
			int iCount     = iPartes;

			// Consumir los "." y ".." iniciales de la ruta relativa subiendo por la base.
			int  iCountRel = 0;
			bool bFinBucle = false;
			while ( ( iCountRel < iPartesRel ) && ! bFinBucle )
			{
				if ( vecPartesRel [ iCountRel ] == ".." )
				{
					if ( iCount > 0 )
					{
						iCount = iCount - 1;
					}
					iCountRel = iCountRel + 1;
				}
				else if ( vecPartesRel [ iCountRel ] != "." )
				{
					bFinBucle = true;
				}
				else
				{
					iCountRel = iCountRel + 1;
				}
			}

			// Reconstruir la parte de la base que sobrevive.
			for ( int i = 0; i < iPartes; i = i + 1 )
			{
				if ( i < iCount )
				{
					sResultado.push_back ( cSep );
					sResultado.append ( vecPartesBase [ i ] );
				}
			}

		// Añadir el resto de la ruta relativa.
			while ( iCountRel < iPartesRel )
			{
				sResultado.push_back ( cSep );
				sResultado.append ( vecPartesRel [ iCountRel ] );
				iCountRel = iCountRel + 1;
			}

			if ( sResultado.empty () )
			{
				sResultado.push_back ( cSep );
			}
			sRes = sResultado;
		}
	}
	return ( sRes );
}


string SisDirectorioRaiz ()
{
# if ( defined ( CYGWIN ) )
	return ( string ( "/" ) );
# elif ( defined ( WIN ) )
	return ( string ( "C:\\" ) );
# else
	return ( string ( "/" ) );
# endif
}

# if ( defined ( WIN ) || defined ( CYGWIN ) )
string SisDirectorioRaizExt ( char cUnidad )
{
# if ( defined ( CYGWIN ) )
	return ( string ( "/cygdrive/" ) + static_cast<char>(tolower ( cUnidad )) );
# else
	return ( string ( 1, cUnidad ) + ":\\" );
# endif
}
# endif

char SisSeparadorRutaFicheros ()
{
	return ( SIS_SEPARADOR_PATH );
}


			}
		}
	}
}
