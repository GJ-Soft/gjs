#include "CppCommonIo.h"
#include <CppBase.h>




using namespace std;
using namespace org::gjs::cpp::common;




static bool TestSisComponer01 ()
{
	cout << "Test SisComponer 01:" << endl;
	bool bRes = true;

	if ( SisComponerFichero ( "datos", "txt" ) != "datos.txt" )
	{
		cout << "Error caso 1: [" << SisComponerFichero ( "datos", "txt" ) << "]" << endl;
		bRes = false;
	}
	// Sin extension se devuelve solo el nombre.
	if ( SisComponerFichero ( "informe", "" ) != "informe" )
	{
		cout << "Error caso 2: [" << SisComponerFichero ( "informe", "" ) << "]" << endl;
		bRes = false;
	}
	if ( SisComponerFichero ( "archivo", "bin" ) != "archivo.bin" )
	{
		cout << "Error caso 3: [" << SisComponerFichero ( "archivo", "bin" ) << "]" << endl;
		bRes = false;
	}
	return ( bRes );
}

static bool TestSisNormalizar01 ()
{
	cout << "Test SisNormalizar 01:" << endl;
	bool bRes = true;

	// Estilo Windows -> Unix: todas las barras invertidas pasan a '/'.
	if ( SisNormalizarRuta ( "C:\\Users\\gjs\\datos.txt" ) != "C:/Users/gjs/datos.txt" )
	{
		cout << "Error caso 1: [" << SisNormalizarRuta ( "C:\\Users\\gjs\\datos.txt" ) << "]" << endl;
		bRes = false;
	}
	// Una ruta ya en estilo Unix se mantiene igual.
	if ( SisNormalizarRuta ( "ya/es/unix" ) != "ya/es/unix" )
	{
		cout << "Error caso 2: [" << SisNormalizarRuta ( "ya/es/unix" ) << "]" << endl;
		bRes = false;
	}
	// Estilo Unix -> Windows: las barras pasan a '\'.
	if ( SisNormalizarRutaWindows ( "carpeta/sub/f.txt" ) != "carpeta\\sub\\f.txt" )
	{
		cout << "Error caso 3: [" << SisNormalizarRutaWindows ( "carpeta/sub/f.txt" ) << "]" << endl;
		bRes = false;
	}
	return ( bRes );
}

static bool TestSisEntorno01 ()
{
	cout << "Test SisEntorno 01:" << endl;
	bool bRes = true;

	// El separador de rutas del sistema es '/' o '\'.
	char cSep = SisSeparadorRutaFicheros ();
	if ( ( cSep != '/' ) && ( cSep != '\\' ) )
	{
		cout << "Error caso 1: separador de rutas inesperado: [" << cSep << "]" << endl;
		bRes = false;
	}
	// El directorio actual no deberia ser vacio.
	string sActual = SisDirectorioActual ();
	if ( sActual.empty () )
	{
		cout << "Error caso 2: el directorio actual no deberia ser vacio" << endl;
		bRes = false;
	}
	// Establecer el directorio actual a su valor actual no debe fallar ( no cambia nada ).
	if ( ! SisEstDirectorioActual ( sActual ) )
	{
		cout << "Error caso 3: no se pudo restablecer el directorio actual" << endl;
		bRes = false;
	}
	// El directorio raiz no deberia ser vacio.
	if ( SisDirectorioRaiz ().empty () )
	{
		cout << "Error caso 4: el directorio raiz no deberia ser vacio" << endl;
		bRes = false;
	}
	return ( bRes );
}

static bool TestSisFicherosE2E01 ()
{
	cout << "Test SisFicherosE2E 01:" << endl;
	bool bRes = true;

	// Se trabaja siempre dentro de un subdirectorio del directorio de trabajo.
	const string sDir  ( "resultsSisFic" );
	const string sFicA ( "resultsSisFic/a.txt" );
	const string sFicB ( "resultsSisFic/b.txt" );
	const string sFicC ( "resultsSisFic/c.txt" );
/*
	try
	{
		// Limpieza previa por si quedo de una ejecucion anterior.
		SisEliminarDirectorio ( sDir );

		// Crear directorio.
		if ( ! SisCrearDirectorio ( sDir ) )
		{
			cout << "Error caso 1: no se pudo crear el directorio" << endl;
			bRes = false;
		}
		if ( ! SisExisteDirectorio ( sDir ) )
		{
			cout << "Error caso 2: el directorio deberia existir" << endl;
			bRes = false;
		}
		// Un directorio no es un fichero regular.
		if ( SisExisteFichero ( sDir ) )
		{
			cout << "Error caso 3: un directorio no deberia detectarse como fichero" << endl;
			bRes = false;
		}

		// Crear fichero.
		if ( ! SisCrearFichero ( sFicA ) )
		{
			cout << "Error caso 4: no se pudo crear el fichero" << endl;
			bRes = false;
		}
		if ( ! SisExisteFichero ( sFicA ) )
		{
			cout << "Error caso 5: el fichero deberia existir" << endl;
			bRes = false;
		}
		// Crear un fichero que ya existe debe devolver falso.
		if ( SisCrearFichero ( sFicA ) )
		{
			cout << "Error caso 6: crear un fichero existente deberia devolver falso" << endl;
			bRes = false;
		}

		// Copiar.
		if ( ! SisCopiarFichero ( sFicA, sFicB ) )
		{
			cout << "Error caso 7: no se pudo copiar el fichero" << endl;
			bRes = false;
		}
		if ( ! SisExisteFichero ( sFicB ) )
		{
			cout << "Error caso 8: la copia deberia existir" << endl;
			bRes = false;
		}

		// Mover.
		if ( ! SisMoverFichero ( sFicB, sFicC ) )
		{
			cout << "Error caso 9: no se pudo mover el fichero" << endl;
			bRes = false;
		}
		if ( SisExisteFichero ( sFicB ) )
		{
			cout << "Error caso 10: el origen del movimiento no deberia existir" << endl;
			bRes = false;
		}
		if ( ! SisExisteFichero ( sFicC ) )
		{
			cout << "Error caso 11: el destino del movimiento deberia existir" << endl;
			bRes = false;
		}

		// Eliminar fichero.
		if ( ! SisEliminarFichero ( sFicA ) )
		{
			cout << "Error caso 12: no se pudo eliminar el fichero" << endl;
			bRes = false;
		}
		if ( SisExisteFichero ( sFicA ) )
		{
			cout << "Error caso 13: el fichero eliminado no deberia existir" << endl;
			bRes = false;
		}

		// Vaciar directorio.
		if ( ! SisVaciarDirectorio ( sDir ) )
		{
			cout << "Error caso 14: no se pudo vaciar el directorio" << endl;
			bRes = false;
		}
		if ( SisExisteFichero ( sFicC ) )
		{
			cout << "Error caso 15: tras vaciar, el fichero no deberia existir" << endl;
			bRes = false;
		}

		// Eliminar directorio.
		if ( ! SisEliminarDirectorio ( sDir ) )
		{
			cout << "Error caso 16: no se pudo eliminar el directorio" << endl;
			bRes = false;
		}
		if ( SisExisteDirectorio ( sDir ) )
		{
			cout << "Error caso 17: el directorio eliminado no deberia existir" << endl;
			bRes = false;
		}
	}
	catch ( exception & ex )
	{
		cout << "Se ha producido una excepcion: " << ex.what () << endl;
		bRes = false;
		SisEliminarDirectorio ( sDir );
	}
*/
	return ( bRes );
}



static bool TestSisValidez01 ()
{
	cout << "Test SisValidez 01:" << endl;
	bool bRes = true;

	// Rutas validas ( unix y windows ) y no validas.
	if ( ! SisEsRutaValida ( "/home/gjs/f.txt" ) )
	{
		cout << "Error caso 1: /home/gjs/f.txt deberia ser una ruta valida" << endl;
		bRes = false;
	}
	if ( ! SisEsRutaValida ( "./config/app.xml" ) )
	{
		cout << "Error caso 2: ./config/app.xml deberia ser una ruta valida" << endl;
		bRes = false;
	}
	if ( ! SisEsRutaValida ( "C:\\Users\\gjs\\f.txt" ) )
	{
		cout << "Error caso 3: una ruta windows deberia ser valida" << endl;
		bRes = false;
	}
	if ( SisEsRutaValida ( "" ) )
	{
		cout << "Error caso 4: la cadena vacia no es una ruta valida" << endl;
		bRes = false;
	}
	// Un nombre suelto ( sin separadores ni prefijo ) no es una ruta.
	if ( SisEsRutaValida ( "solounnombre" ) )
	{
		cout << "Error caso 5: un nombre suelto no es una ruta valida" << endl;
		bRes = false;
	}

	// Fichero valido: con o sin extension; vacio no.
	if ( ! SisEsFicheroValido ( "datos.txt" ) )
	{
		cout << "Error caso 6: datos.txt deberia ser un fichero valido" << endl;
		bRes = false;
	}
	if ( ! SisEsFicheroValido ( "sinpunto" ) )
	{
		cout << "Error caso 7: sinpunto deberia ser un fichero valido ( sin extension )" << endl;
		bRes = false;
	}
	if ( SisEsFicheroValido ( "" ) )
	{
		cout << "Error caso 8: la cadena vacia no es un fichero valido" << endl;
		bRes = false;
	}

	// Subdirectorio: cualquier cadena no vacia.
	if ( ! SisEsSubdirectorioValido ( "sub" ) )
	{
		cout << "Error caso 9: sub deberia ser un subdirectorio valido" << endl;
		bRes = false;
	}
	if ( SisEsSubdirectorioValido ( "" ) )
	{
		cout << "Error caso 10: la cadena vacia no es un subdirectorio valido" << endl;
		bRes = false;
	}

	// Tiene extension: solo si hay 'nombre.ext'.
	if ( SisFicheroTieneExtension ( "datos.txt" ) == 0 )
	{
		cout << "Error caso 11: datos.txt deberia tener extension" << endl;
		bRes = false;
	}
	if ( SisFicheroTieneExtension ( "sinpunto" ) != 0 )
	{
		cout << "Error caso 12: sinpunto no deberia tener extension" << endl;
		bRes = false;
	}
	return ( bRes );
}

static bool TestSisComponentes01 ()
{
	cout << "Test SisComponentes 01:" << endl;
	bool bRes = true;

	// Extension y nombre de un fichero.
	if ( SisFicheroExtension ( "datos.txt" ) != "txt" )
	{
		cout << "Error caso 1: [" << SisFicheroExtension ( "datos.txt" ) << "]" << endl;
		bRes = false;
	}
	// Sin punto no hay extension.
	if ( ! SisFicheroExtension ( "sinextension" ).empty () )
	{
		cout << "Error caso 2: [" << SisFicheroExtension ( "sinextension" ) << "]" << endl;
		bRes = false;
	}
	if ( SisFicheroNombre ( "datos.txt" ) != "datos" )
	{
		cout << "Error caso 3: [" << SisFicheroNombre ( "datos.txt" ) << "]" << endl;
		bRes = false;
	}
	// Inversa: nombre + extension recompone el fichero.
	if ( SisComponerFichero ( SisFicheroNombre ( "informe.pdf" ), SisFicheroExtension ( "informe.pdf" ) ) != "informe.pdf" )
	{
		cout << "Error caso 4: no se recompuso informe.pdf" << endl;
		bRes = false;
	}

	// Fichero y directorio de una ruta.
	if ( SisRutaFichero ( "/home/datos.txt" ) != "datos.txt" )
	{
		cout << "Error caso 5: [" << SisRutaFichero ( "/home/datos.txt" ) << "]" << endl;
		bRes = false;
	}
	if ( SisRutaDirectorio ( "/home/datos.txt" ) != "/home" )
	{
		cout << "Error caso 6: [" << SisRutaDirectorio ( "/home/datos.txt" ) << "]" << endl;
		bRes = false;
	}
	// Directorio + separador + fichero reconstruye la ruta.
	if ( SisRutaDirectorio ( "/home/datos.txt" ) + "/" + SisRutaFichero ( "/home/datos.txt" ) != "/home/datos.txt" )
	{
		cout << "Error caso 7: no se reconstruyo la ruta" << endl;
		bRes = false;
	}

	// Numero de subdirectorios: 0 si no hay separadores, > 0 si los hay.
	if ( SisDirectorioNumSubdirectorios ( "sinbarras" ) != 0 )
	{
		cout << "Error caso 8: sin separadores deberian ser 0 subdirectorios" << endl;
		bRes = false;
	}
	if ( SisDirectorioNumSubdirectorios ( "/home/gjs/data" ) <= 0 )
	{
		cout << "Error caso 9: con separadores deberia haber subdirectorios" << endl;
		bRes = false;
	}
	return ( bRes );
}

static bool TestSisClasificacion01 ()
{
	cout << "Test SisClasificacion 01:" << endl;
	bool bRes = true;

	// Cabecera C: solo '.h'.
	if ( ! SisEsFicheroCabeceraC ( "/inc/base.h" ) )
	{
		cout << "Error caso 1: base.h deberia ser cabecera C" << endl;
		bRes = false;
	}
	if ( SisEsFicheroCodigoC ( "/inc/base.h" ) )
	{
		cout << "Error caso 2: base.h no es codigo C ( es cabecera )" << endl;
		bRes = false;
	}
	if ( ! SisEsFicheroC ( "/inc/base.h" ) )
	{
		cout << "Error caso 3: base.h es un fichero C" << endl;
		bRes = false;
	}
	// Codigo C.
	if ( ! SisEsFicheroCodigoC ( "/src/main.cpp" ) )
	{
		cout << "Error caso 4: main.cpp deberia ser codigo C" << endl;
		bRes = false;
	}
	if ( SisEsFicheroCabeceraC ( "/src/main.cpp" ) )
	{
		cout << "Error caso 5: main.cpp no es cabecera C" << endl;
		bRes = false;
	}
	// HTML y XML.
	if ( ! SisEsFicheroHTML ( "/web/index.html" ) )
	{
		cout << "Error caso 6: index.html deberia ser HTML" << endl;
		bRes = false;
	}
	if ( ! SisEsFicheroHTML ( "/web/page.htm" ) )
	{
		cout << "Error caso 7: page.htm deberia ser HTML" << endl;
		bRes = false;
	}
	if ( ! SisEsFicheroXML ( "/cfg/app.xml" ) )
	{
		cout << "Error caso 8: app.xml deberia ser XML" << endl;
		bRes = false;
	}
	if ( SisEsFicheroXML ( "/src/main.cpp" ) )
	{
		cout << "Error caso 9: main.cpp no es XML" << endl;
		bRes = false;
	}
	return ( bRes );
}

static bool TestSisAbsRel01 ()
{
	cout << "Test SisAbsRel 01:" << endl;
	bool bRes = true;
	// Absoluta vs relativa ( estilo unix; build POSIX/Cygwin ).
	if ( ! SisEsRutaAbsoluta ( "/usr/local/bin" ) )
	{
		cout << "Error caso 1: /usr/local/bin deberia ser absoluta" << endl;
		bRes = false;
	}
	if ( SisEsRutaRelativa ( "/usr/local/bin" ) )
	{
		cout << "Error caso 2: /usr/local/bin no deberia ser relativa" << endl;
		bRes = false;
	}
	if ( ! SisEsRutaRelativa ( "./sub/f.txt" ) )
	{
		cout << "Error caso 3: ./sub/f.txt deberia ser relativa" << endl;
		bRes = false;
	}
	if ( SisEsRutaAbsoluta ( "./sub/f.txt" ) )
	{
		cout << "Error caso 4: ./sub/f.txt no deberia ser absoluta" << endl;
		bRes = false;
	}
	if ( ! SisEsRutaRelativa ( "../otro/f.txt" ) )
	{
		cout << "Error caso 5: ../otro/f.txt deberia ser relativa" << endl;
		bRes = false;
	}

	// Componer ruta: sin directorio valido se antepone el directorio actual.
	if ( SisComponerRuta ( "", "x.txt", 0 ) != "./x.txt" )
	{
		cout << "Error caso 6: [" << SisComponerRuta ( "", "x.txt", 0 ) << "]" << endl;
		bRes = false;
	}
	// Sin fichero ni directorio validos y con el flag: el directorio actual.
	if ( SisComponerRuta ( "", "", 1 ) != "." )
	{
		cout << "Error caso 7: [" << SisComponerRuta ( "", "", 1 ) << "]" << endl;
		bRes = false;
	}
	return ( bRes );
}



static string NormalizarSep ( string sRuta )
{
	for ( size_t i = 0; i < sRuta.size (); i = i + 1 )
	{
		if ( sRuta [ i ] == '\\' )
		{
			sRuta [ i ] = '/';
		}
	}
	return ( sRuta );
}

static bool TestSisComponerRuta01 ()
{
	cout << "Test SisComponerRuta 01:" << endl;
	bool bRes = true;

	// El directorio valido depende del sistema ( unidad en Windows ). Se acepta
	// cualquier estilo de separador; para comparar se normaliza a '/'.
#if defined ( WIN )
	const string sDir     ( "C:\\Temp" );
	const string sDirNorm ( "C:/Temp" );
#else
	const string sDir     ( "/tmp" );
	const string sDirNorm ( "/tmp" );
#endif

	// Caso 1: directorio valido + fichero -> se combinan con un separador.
	if ( NormalizarSep ( SisComponerRuta ( sDir, "f.txt", 0 ) ) != sDirNorm + "/f.txt" )
	{
		cout << "Error caso 1: [" << SisComponerRuta ( sDir, "f.txt", 0 ) << "]" << endl;
		bRes = false;
	}
	// Caso 2: directorio invalido + fichero -> se antepone el directorio actual ".".
	if ( NormalizarSep ( SisComponerRuta ( "", "x.txt", 0 ) ) != "./x.txt" )
	{
		cout << "Error caso 2: [" << SisComponerRuta ( "", "x.txt", 0 ) << "]" << endl;
		bRes = false;
	}
	// Caso 3: directorio valido + fichero vacio -> se devuelve solo el directorio.
	if ( SisComponerRuta ( sDir, "", 0 ) != sDir )
	{
		cout << "Error caso 3: [" << SisComponerRuta ( sDir, "", 0 ) << "]" << endl;
		bRes = false;
	}
	// Caso 4: nada valido, con flag -> directorio actual ".".
	if ( SisComponerRuta ( "", "", 1 ) != "." )
	{
		cout << "Error caso 4: [" << SisComponerRuta ( "", "", 1 ) << "]" << endl;
		bRes = false;
	}
	// Caso 5: nada valido, sin flag -> cadena vacia.
	if ( ! SisComponerRuta ( "", "", 0 ).empty () )
	{
		cout << "Error caso 5: [" << SisComponerRuta ( "", "", 0 ) << "]" << endl;
		bRes = false;
	}
	return ( bRes );
}

static bool TestSisResolverDirRelativo01 ()
{
	cout << "Test SisResolverDirRelativo 01:" << endl;
	bool bRes = true;

	// La base se da en estilo unix ( aceptado en cualquier plataforma ); la ruta
	// relativa empieza por "./" y usa ".." para subir de nivel. El estilo de salida
	// depende del sistema, asi que se normaliza a '/' y se comprueba por contenido.

	// Caso 1: "./../datos" sube un nivel ( quita "proyecto" ) y desciende a "datos".
	string sRes = NormalizarSep ( SisResolverDirectorioRelativo ( "/home/gjs/proyecto", "./../datos" ) );
	if ( ( sRes.find ( "home/gjs/datos" ) == string::npos ) ||
		 ( sRes.find ( "proyecto" ) != string::npos ) )
	{
		cout << "Error caso 1: [" << sRes << "]" << endl;
		bRes = false;
	}
	// Caso 2: "./sub" desciende sin subir.
	sRes = NormalizarSep ( SisResolverDirectorioRelativo ( "/home/gjs/proyecto", "./sub" ) );
	if ( sRes.find ( "home/gjs/proyecto/sub" ) == string::npos )
	{
		cout << "Error caso 2: [" << sRes << "]" << endl;
		bRes = false;
	}
	// Caso 3: "./../../otro" sube dos niveles ( quita "proyecto" y "gjs" ).
	sRes = NormalizarSep ( SisResolverDirectorioRelativo ( "/home/gjs/proyecto", "./../../otro" ) );
	if ( ( sRes.find ( "home/otro" ) == string::npos ) ||
		 ( sRes.find ( "gjs" ) != string::npos ) )
	{
		cout << "Error caso 3: [" << sRes << "]" << endl;
		bRes = false;
	}
	// Caso 4: relativa que no empieza por '.' -> cadena vacia.
	if ( ! SisResolverDirectorioRelativo ( "/home/gjs", "sinpunto" ).empty () )
	{
		cout << "Error caso 4: se esperaba vacio con relativa sin '.'" << endl;
		bRes = false;
	}
	return ( bRes );
}

bool TestSistemaFicheros ()
{
	bool bRes = true;
	cout << endl << ANSI::AMARILLO << "[Test SistemaFicheros]" << ANSI::RESETEAR << endl;
	if ( TestSisComponer01 () )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout  << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}
	if ( TestSisNormalizar01 () )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout  << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}
	if ( TestSisEntorno01 () )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout  << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}
	if ( TestSisFicherosE2E01 () )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout  << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}
	if ( TestSisValidez01 () )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout  << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}
	if ( TestSisComponentes01 () )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout  << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}
	if ( TestSisClasificacion01 () )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout  << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}
	if ( TestSisAbsRel01 () )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout  << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}
	if ( TestSisComponerRuta01 () )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout  << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}
	if ( TestSisResolverDirRelativo01 () )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout  << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}
	cout << ANSI::AMARILLO << "[Fin]" << ANSI::RESETEAR << endl;
	return ( bRes );
}
