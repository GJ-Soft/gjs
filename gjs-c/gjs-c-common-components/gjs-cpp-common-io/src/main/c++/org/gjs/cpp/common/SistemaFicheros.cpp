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


#include "SistemaFicheros.h"

#include "CommonIoConfig.h"


// PENDIENTe: En unix/linux SisExisteFichero no distingue entre ficheros y directorios lo que puede
// llevar a confusión.


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






bool SisEsDirectorioValido ( const string & sDirectorio )
{
	bool bRes = false;

# if ( defined ( WIN ) )
	if ( CumpleExpresionRegular ( sDirectorio, SF_PATRON_DIRECTORIO_WIN )  || 
		 CumpleExpresionRegular ( sDirectorio, SF_PATRON_DIRECTORIO_WIN_2 ) )
# else
	if ( CumpleExpresionRegular ( sDirectorio, SF_PATRON_DIRECTORIO ) )
# endif
	{
		bRes = true;
	}
	return ( bRes );
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
	iLong = sDirectorio.length();
	iPos = BuscarDesdeAtrasCaracter ( sDirectorio, cSep, iLong - 2 );
	if ( ( iPos > 1 ) && ( iPos < iLong - 2 ) )
	{
		sRes = sDirectorio.substr( 0, iPos );
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

	if ( !sExtension.empty() )
	{
		sFichero = format( SF_MASCARA_FICHERO, sNombre, sExtension );
	}
	else
	{
		sFichero = string( sExtension );
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
		iPos =BuscarDesdeAtrasCaracter ( sRuta, cSep ); 
		sRes = sRuta.substr( 0, iPos );
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
		iPos =BuscarDesdeAtrasCaracter ( sRuta, cSep ); 
		sRes = sRuta.substr ( sRuta.length() - iPos - 1 );
	}
	return ( sRes );
}

int SisRutaNumSubdirectorios ( const string & sRuta )
{
	int		iRes = 0;
	string	sDirectorio = SisRutaDirectorio ( sRuta );
	if ( ! sDirectorio.empty() )
	{
		iRes = SisDirectorioNumSubdirectorios ( sDirectorio );
	}
	return ( iRes );
}

string SisRutaSubdirectorio ( const string & sRuta, int iNivel )
{
	string 	sRes = "";
	string	sDirectorio = SisRutaDirectorio ( sRuta );
	if ( ! sDirectorio.empty() )
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
		if ( SisEsDirectorioValido ( sDirectorio ) )
		{
			sRuta = format ( SF_MASCARA_RUTA, sDirectorio, sFichero );
		}
		else
		{
			sRuta = format ( SF_MASCARA_RUTA, SF_DIR_ACTUAL, sFichero );
		}
	}
	else
	{
		if ( SisEsDirectorioValido ( sDirectorio ) )
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
		string sDirComp = SisComponerRuta ( sDirectorio, sSubdirectorio );
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
	return ( ReemplazarTodos ( sRuta, '\\', '/' ) );
}

bool SisEsRutaValida ( const string & sRuta )
{
	bool bRes = false;
	
#     if ( defined ( WIN ) )
	if ( CumpleExpresionRegular ( sRuta, SF_PATRON_RUTA_WIN ) ||  
		 CumpleExpresionRegular ( sRuta, SF_PATRON_RUTA_WIN_2 ) ||
		 CumpleExpresionRegular ( sRuta, SF_PATRON_RUTA_REL_WIN ) ||  
		 CumpleExpresionRegular ( sRuta, SF_PATRON_RUTA_REL_WIN_2 ) ||  
		 CumpleExpresionRegular ( sRuta, SF_PATRON_RUTA_REL_WIN_3 ) ||  
		 CumpleExpresionRegular ( sRuta, SF_PATRON_RUTA_REL_WIN_4 ) )  
#     else
	if ( CumpleExpresionRegular ( sRuta, SF_PATRON_RUTA ) ||  
		 CumpleExpresionRegular ( sRuta, SF_PATRON_RUTA_REL ) ||  
		 CumpleExpresionRegular ( sRuta, SF_PATRON_RUTA_REL_2 ) )  
#     endif
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
		sDirectorio = fs::current_path().string();
	}
	catch (...) {
	}
	return ( sDirectorio ); 
}

bool SisEstDirectorioActual ( const string & sDirectorio )
{
	bool bRes = false;

	try 
	{
		fs::path sActual = fs::current_path();
		fs::current_path( sDirectorio );
		bRes = true;
	}
	catch (...) 
	{
	}
	return ( bRes );
}

string SisCadenaDirectorioSistema ()
{
	vector<char> buffer(  SF_MAX_TAM_RUTA );					
	unsigned int uiTam = 0;
	
# if ( defined ( WIN ) )
	uiTam = GetSystemDirectoryA( buffer.data(), buffer.size() );
# else
	// PENDIENTE
# endif
	return ( string( buffer.data(), uiTam ) );
}

bool SisExisteFichero ( const string & sRuta )
{
	bool bRes = false;
	try 
	{
		fs::path ruta( sRuta );
		if ( fs::exists( ruta ) ) 
		{
			bRes = fs::is_regular_file(ruta);
		}
	}
	catch (...) 
	{
	}
	return ( bRes );
}

bool SisExisteFicheroExt ( const string & sDirectorio, const string & sFichero )
{
	return ( SisExisteFichero ( SisComponerRuta ( sDirectorio, sFichero ) ) );
}

bool SisExisteDirectorio ( const string & sRuta )
{
	bool bRes = false;
	try 
	{
		fs::path ruta( sRuta );
		if ( fs::exists( ruta ) ) 
		{
			bRes = fs::is_directory(ruta);
		}
	}
	catch (...) 
	{
	}
	return ( bRes );
}

bool SisExisteDirectorioExt ( const string & sDirectorio, const string & sSubdirectorio )
{
	return ( SisExisteDirectorio ( SisComponerRuta ( sDirectorio, sSubdirectorio ) ) );
}

bool SisCrearFichero ( const string & sRuta )
{
	bool bRes = false;
	try 
	{
		ofstream archivo( sRuta );
		if ( archivo.is_open() ) 
		{
			archivo.close();
			bRes = true;
		}
	}
	catch (...) 
	{
	}
	return ( bRes );
}

bool SisCrearFicheroExt ( const string & sDirectorio, const string & sFichero )
{
	return ( SisCrearFichero ( SisComponerRuta ( sDirectorio, sFichero ) ) );
}

bool SisCrearDirectorio ( const string & sDirectorio )
{
	bool bRes = false;
	try 
	{
		fs::path directorio ( sDirectorio );
		bRes = ( fs::create_directories( directorio ) );
	}
	catch (...) 
	{
	}
	return ( bRes );
}

bool SisCrearDirectorioExt ( const string & sDirectorio, const string & sSubdirectorio )
{
	return ( SisCrearDirectorio ( SisComponerRuta ( sDirectorio, sSubdirectorio ) ) );
}

bool SisEliminarFichero ( const string & sRuta )
{
	bool bRes = false;
	try 
	{
		fs::path ruta ( sRuta );
		bRes = ( fs::remove( ruta ) );
	}
	catch (...) 
	{
	}
	return ( bRes );
}

bool SisEliminarFicheroExt ( const string & sDirectorio, const string & sFichero )
{
	return ( SisEliminarFichero ( SisComponerRuta ( sDirectorio, sFichero ) ) );
}

string SisMascaraBusquedaEnDirectorio ( const string & sDirectorio )
{
	string sRes;

	if ( !sDirectorio.empty() )
	{
		sRes = format ( "%s/%s",  sDirectorio, SF_MASCARA_BUSQUEDA );
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
	try 
	{
		fs::path directorio ( sDirectorio );
		bRes = ( fs::remove_all( directorio ) > 0 );
	}
	catch (...) 
	{
	}
	return ( bRes );
}

bool SisEliminarDirectorioExt ( const string & sDirectorio, const string & sSubdirectorio )
{
	return ( SisEliminarDirectorio ( SisComponerRuta ( sDirectorio, sSubdirectorio ) ) );
}

bool SisVaciarDirectorio ( const string & sDirectorio )
{
	bool bRes = false;
	try 
	{
		fs::path directorio( sDirectorio );
		if ( fs::exists( directorio ) && fs::is_directory( directorio ) ) 
		{
			for ( const auto& entrada : fs::directory_iterator( directorio ) )
			{
				fs::remove_all( entrada.path() );
			}
			bRes = true;
		}
	}
	catch (...) 
	{
	}
	return ( bRes );
}

bool SisVaciarDirectorioExt ( const string & sDirectorio, const string & sSubdirectorio )
{
	return ( SisVaciarDirectorio ( SisComponerRuta ( sDirectorio, sSubdirectorio ) ) );
}

bool SisCopiarFichero ( const string & sRutaOrig, const string & sRutaDest, bool bEliminar )
{
	bool bRes = false;
	try 
	{
		fs::path origen( sRutaOrig );
		fs::path destino( sRutaDest );
		
		if ( bEliminar ) 
		{
			fs::copy_file( origen, destino, fs::copy_options::overwrite_existing );
		} 
		else 
		{
			if ( !fs::exists( destino) ) 
			{
				fs::copy_file( origen, destino );
			}
		}
		bRes = true;
	}
	catch (...) 
	{
	}
	return ( bRes );
}

bool SisCopiarFicheroExt ( const string & sDirOrig, const string & sFicOrig, const string & sDirDest, const string & sFicDest, bool bEliminar )
{
	return ( SisCopiarFichero ( SisComponerRuta ( sDirOrig, sFicOrig ),SisComponerRuta ( sDirDest, sFicDest ), bEliminar ) );
}

bool SisMoverFichero ( const string & sRutaOrig, const string & sRutaDest, bool bEliminar )
{
	bool bRes = false;
	try 
	{
		fs::path origen( sRutaOrig );
		fs::path destino( sRutaDest );
		
		if ( bEliminar || fs::exists( destino ) )  
		{
			fs::rename( origen, destino );
			bRes = true;
		}
	}
	catch (...) 
	{
	}
	return ( bRes );
}

bool SisMoverFicheroExt( const string & sDirOrig, const string & sFicOrig,
                       const string & sDirDest, const string & sFicDest, bool bEliminar)
{
	return ( SisMoverFichero ( SisComponerRuta ( sDirOrig, sFicOrig ),
		SisComponerRuta ( sDirDest, sFicDest ), bEliminar ) );
}

// PENDIENTE: UNIX/Linux
bool SisRutaComprimida ( const string & sRuta )
{
	bool bRes = false;

# if ( defined ( WIN ) )
	DWORD		dwAtributos;

	dwAtributos = GetFileAttributesA ( sRuta.c_str() );
	if ( dwAtributos != INVALID_FILE_ATTRIBUTES )
	{
		if ( ( dwAtributos & FILE_ATTRIBUTE_COMPRESSED ) == FILE_ATTRIBUTE_COMPRESSED )
		{
			bRes = true;
		}
	}

# else
	// PENDIENTE
# endif
	return ( bRes );
}

bool SisRutaEncriptada ( const string & sRuta )
{
	bool bRes = false;

# if ( defined ( WIN ) )
	DWORD		dwAtributos;

	dwAtributos = GetFileAttributesA ( sRuta.c_str() );
	if ( dwAtributos != INVALID_FILE_ATTRIBUTES )
	{
		if ( ( dwAtributos & FILE_ATTRIBUTE_ENCRYPTED ) == FILE_ATTRIBUTE_ENCRYPTED )
		{
			bRes = true;
		}
	}

# else
	// PENDIENTE
# endif
	return ( bRes );
}

bool SisRutaOculta ( const string & sRuta )
{
	bool bRes = false;

# if ( defined ( WIN ) )
	DWORD		dwAtributos;

	dwAtributos = GetFileAttributesA ( sRuta.c_str() );
	if ( dwAtributos != INVALID_FILE_ATTRIBUTES )
	{
		if ( ( dwAtributos & FILE_ATTRIBUTE_HIDDEN ) == FILE_ATTRIBUTE_HIDDEN )
		{
			bRes = true;
		}
	}
# else
	// PENDIENTE
# endif
	return ( bRes );
}


bool SisFicheroEsAccesible ( const string & sRuta )
{
	bool bRes = false;

# if ( defined ( WIN ) )
	DWORD		dwAtributos;

	dwAtributos = GetFileAttributesA ( sRuta.c_str() );
	if ( dwAtributos != INVALID_FILE_ATTRIBUTES )
	{
		if ( ( dwAtributos & FILE_ATTRIBUTE_OFFLINE ) == FILE_ATTRIBUTE_OFFLINE )
		{
			bRes = true;
		}
	}

# else
	try 
	{
		// TODO: No es exactamente lo mismo
		fs::path ruta( sRuta );
		fs::file_status estado = fs::status( ruta );
		
		// Verificar permisos de lectura
		auto permisos = estado.permissions();
		bRes = ( permisos != fs::perms::none );
	}
	catch (...) 
	{
	}
# endif
	return ( bRes );
}

bool SisRutaDeSoloLectura ( const string & sRuta )
{
	bool bRes = false;

	try 
	{
		// TODO: No es exactamente lo mismo
		fs::path ruta( sRuta );
		fs::file_status estado = fs::status( ruta );
		
		// Verificar permisos de lectura
		auto permisos = estado.permissions();
		bRes = ( ( permisos & fs::perms::owner_write ) == fs::perms::none );
	}
	catch (...) 
	{
	}
	return ( bRes );
}

bool SisRutaDelSistema ( const string & sRuta )
{
	bool bRes = false;

# if ( defined ( WIN ) )
	DWORD		dwAtributos;

	dwAtributos = GetFileAttributesA ( sRuta.c_str() );
	if ( dwAtributos != INVALID_FILE_ATTRIBUTES )
	{
		if ( ( dwAtributos & FILE_ATTRIBUTE_SYSTEM ) == FILE_ATTRIBUTE_SYSTEM )
		{
			bRes = true;
		}
	}

# else
	// PENDIENTE
# endif
	return ( bRes );
}

bool SisFicheroEsTemporal ( const string & sRuta )
{
	bool bRes = false;

# if ( defined ( WIN ) )
	DWORD		dwAtributos;

	dwAtributos = GetFileAttributesA ( sRuta.c_str() );
	if ( dwAtributos != INVALID_FILE_ATTRIBUTES )
	{
		if ( ( dwAtributos & FILE_ATTRIBUTE_TEMPORARY ) == FILE_ATTRIBUTE_TEMPORARY )
		{
			bRes = true;
		}
	}

# else
	try 
	{
		// TODO: No es exactamente lo mismo
		fs::path ruta( sRuta );
		fs::path dirTemp = fs::temp_directory_path();
		
		// Verificar si está en el directorio temporal
		bRes = ( ruta.string().find( dirTemp.string() ) == 0 );
	}
	catch (...) 
	{
	}
# endif
	return ( bRes );
}

bool SisFicheroAsociadoAAplicacion ( const string & sRuta )
{
	bool bRes = false;

# if ( defined ( WIN ) )
	DWORD		dwAtributos;

	dwAtributos = GetFileAttributesA ( sRuta.c_str() );
	if ( dwAtributos != INVALID_FILE_ATTRIBUTES )
	{
		if ( ( dwAtributos & FILE_ATTRIBUTE_REPARSE_POINT ) == FILE_ATTRIBUTE_REPARSE_POINT )
		{
			bRes = true;
		}
	}

# else
	// PENDIENTE
# endif
	return ( bRes );
}

bool SisFicheroConOptimizacionEspacial ( const string & sRuta )
{
	bool bRes = false;

# if ( defined ( WIN ) )
	DWORD		dwAtributos;

	dwAtributos = GetFileAttributesA ( sRuta.c_str() );
	if ( dwAtributos != INVALID_FILE_ATTRIBUTES )
	{
		if ( ( dwAtributos & FILE_ATTRIBUTE_SPARSE_FILE ) == FILE_ATTRIBUTE_SPARSE_FILE )
		{
			bRes = true;
		}
	}

# else
	// PENDIENTE
# endif
	return ( bRes );
}

bool SisRutaDesactivarModoSoloLectura ( const string & sRuta )
{
	bool bRes = false;

# if ( defined ( WIN ) )
	DWORD		dwAtributos;
	DWORD		dwMascara;

	dwAtributos = GetFileAttributes ( sRuta.c_str() );
	if ( dwAtributos != INVALID_FILE_ATTRIBUTES )
	{
		dwMascara = FILE_ATTRIBUTE_READONLY;
		dwMascara = 0xFFFFFFFF ^ dwMascara;
		dwAtributos = dwAtributos & dwMascara;
		if ( SetFileAttributes ( sRuta.c_str(), dwAtributos ) != 0 )
		{
			bRes = true;
		}
	}
# else
	try 
	{
		// NOTA: Esto debería sevir para todos los casos
		fs::path ruta( sRuta );
		
		// Añadir permisos de escritura
		fs::permissions( ruta,  
		                fs::perms::owner_write | fs::perms::group_write,
		                fs::perm_options::add );
		bRes = true;
	}
	catch (...)
	{
	}
# endif
	return ( bRes );
}

bool SisEsFicheroC ( const string & sRuta )
{
	bool bRes = false;

	string sFichero = SisRutaFichero ( sRuta );
	string sExt = SisRutaFichero ( sFichero );
	if ( ! sExt.empty() )
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
	string sExt = SisRutaFichero ( sFichero );
	if ( ! sExt.empty() )
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
	string sExt = SisRutaFichero ( sFichero );
	if ( ! sExt.empty() )
	{
		bRes = ( sExt == EXT_FIC_CABECERA_C );
	}
	return ( bRes );
}

bool SisEsFicheroXML ( const string & sRuta )
{
	bool bRes = false;

	string sFichero = SisRutaFichero ( sRuta );
	string sExt = SisRutaFichero ( sFichero );
	if ( ! sExt.empty() )
	{
		bRes = ( sExt == EXT_FIC_XML );
	}
	return ( bRes );
}

bool SisEsFicheroHTML ( const string & sRuta )
{
	bool bRes = false;

	string sFichero = SisRutaFichero ( sRuta );
	string sExt = SisRutaFichero ( sFichero );
	if ( ! sExt.empty() )
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
	string sExt = SisRutaFichero ( sFichero );
	if ( ! sExt.empty() )
	{
		bRes = ( sExt == EXT_FIC_SHAPE );
	}
	return ( bRes );
}

bool SisEsFicheroDBF ( const string & sRuta )
{
	bool bRes = false;

	string sFichero = SisRutaFichero ( sRuta );
	string sExt = SisRutaFichero ( sFichero );
	if ( ! sExt.empty() )
	{
		bRes = ( sExt == EXT_FIC_DBASE );
	}
	return ( bRes );
}



			}
		}
	}
}


