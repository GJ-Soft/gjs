#include "CppBase.h"

#include <iostream>
#include <chrono>
#include <ctime>
#include <csignal>
#include <cerrno>


using namespace std;
using namespace org::gjs::cpp::common;


static bool TestNombreSistema01 ()
{
	cout << "Test NombreSistema01:" << endl;
	bool bRes = true;

	try
	{
		string sNom = NombreSistema ();
		cout << "Sistema: [" << sNom << "]" << endl;
	}
	catch ( ... )
	{
		cout << "Error al recuperar el nombre del sistema" << endl;
		bRes = false;
	}
	return( bRes );
}

static bool TestNombreSistema02 ()
{
	cout << "Test NombreSistema02:" << endl;
	bool bRes = true;

	try
	{
		cout << "EsWindows: [" << EsWindows() << "]" << endl;
		cout << "EsCygwin : [" << EsCygwin() << "]" << endl;
		cout << "EsMinGW  : [" << EsMinGW() << "]" << endl;
		cout << "EsLinux  : [" << EsLinux() << "]" << endl;
		cout << "EsUnix   : [" << EsUnix() << "]" << endl;
		cout << "EsMac    : [" << EsMac() << "]" << endl;
	}
	catch ( ... )
	{
		cout << "Error al recuperar el nombre del sistema" << endl;
		bRes = false;
	}
	return( bRes );
}

static bool TestDirectorioActual01 ()
{
	cout << "Test DirectorioActual01:" << endl;
	bool bRes = true;
	string sDir1 ( "" );
	string sDir2 ( "" );

	try
	{
		sDir1 = DirectorioActual ();
		cout << "Directorio actual: [" << sDir1 << "]" << endl;
	}
	catch ( ... )
	{
		cout << "Error al recuperar el directorio actual" << endl;
		bRes = false;
	}
	if ( bRes )
	{
		try
		{
			EstablecerDirectorio ( "/" );
			sDir2 = DirectorioActual();
			/* "/" es la raiz de la unidad actual, y cada plataforma la escribe a
			   su manera: "/" en POSIX y "C:\\" en Windows. Comparar con "/" a
			   secas daba KO en Windows por un directorio que era el correcto. Se
			   comprueba lo que de verdad se pedia: que el directorio actual haya
			   pasado a ser una raiz, sea cual sea su forma. */
			filesystem::path pathDir2 ( sDir2 );
			if ( pathDir2 != pathDir2.root_path () )
			{
				cout << "Directorio actual establecido con errores: [" << sDir2 << "]" << endl;
				bRes = false;
			}
			EstablecerDirectorio ( sDir1 );
		}
		catch ( ... )
		{
			cout << "Error al establecer directorio actual" << endl;
			bRes = false;
		}
	}
	else
	{
		cout << "Error al recuperar el directorio actual" << endl;
		bRes = false;
	}
	return( bRes );
}

static bool TestResolverDirectorioRelativo01 ()
{
	cout << "Test ResolverDirectorioRelativo01:" << endl;
	bool bRes = true;
	string sDirBase = "/subdir1/subdir2/subdir3";
	string sDir0 = ( "/aye" );
	string sDir1 = ( "./../aye" );
	string sDir2 ( "../.././aye/aye" );

	try
	{
		string sRes = ResolverDirectorioRelativo ( sDirBase, sDir0 );
		if ( sRes.compare( sDirBase ) != 0 )
		{
			cout << "Error caso 1: [" << sRes << "]" << endl;
		}
		sRes = ResolverDirectorioRelativo ( sDirBase, "." );
		if ( sRes.compare( sRes ) != 0 )
		{
			cout << "Error caso 2: [" << sRes << "]" << endl;
		}
		sRes = ResolverDirectorioRelativo ( sDirBase, ".." );
		if ( sRes.compare( "/subdir1/subdir2" ) != 0 )
		{
			cout << "Error caso 3: [" << sRes << "]" << endl;
		}
		sRes = ResolverDirectorioRelativo ( sDirBase, sDir1 );
		if ( sRes.compare( "/subdir1/subdir2/aye" ) != 0 )
		{
			cout << "Error caso 4: [" << sRes << "]" << endl;
		}
		sRes = ResolverDirectorioRelativo ( sDirBase, sDir2 );
		if ( sRes.compare( "/subdir1/aye/aye" ) != 0 )
		{
			cout << "Error caso 5: [" << sRes << "]" << endl;
		}
	}
	catch ( ... )
	{
		cout << "Error inesperado" << endl;
		bRes = false;
	}
	return( bRes );
}

static bool TestExisteDirectorio01 ()
{
	cout << "Test ExisteDirectorio01:" << endl;
	bool bRes = true;
	string sDir1 ( "" );
	string sDir2 ( "" );
	string sDir3 ( "/noexiste" );
	string sDir4 ( "" );
	string sSubdir( "" );

	try
	{
		sDir1 = DirectorioActual ();
		sDir2 = sDir1 + "/../data/directorio-vacio";
		sDir4 = sDir1 + "/../data/fichero-vacio.txt";

		if ( ! ExisteDirectorio ( sDir1 ) )
		{
			cout << "Dice que no existe el directorio actual: [" << sDir1 << "]" << endl;
			bRes = false;
		}
		if ( ! ExisteDirectorio ( sDir2 ) )
		{
			cout << "Dice que no existe el directorio de recursos: [" << sDir2 << "]" << endl;
			bRes = false;
		}
		if ( ExisteDirectorio ( sDir3 ) )
		{
			cout << "Dice que existe el directorio: [" << sDir3 << "]" << endl;
			bRes = false;
		}
		if ( ExisteDirectorio ( sDir4 ) )
		{
			cout << "Dice que el fichero es un directorio: [" << sDir4 << "]" << endl;
			bRes = false;
		}
		sSubdir = "../data/directorio-vacio";
		if ( ! ExisteDirectorio ( sSubdir ) )
		{
			cout << "Dice que no existe el subdirectorio de recursos: [" << sSubdir << "]" << endl;
			bRes = false;
		}
	}
	catch ( ... )
	{
		cout << "Error al consultar la existencia del directorio" << endl;
		bRes = false;
	}
	return( bRes );
}

static bool TestExisteFichero01 ()
{
	cout << "Test ExisteFichero01:" << endl;
	bool bRes = true;
	string sFic1 ( "../data/fichero-vacio.txt" );
	string sFic2 ( "./noexiste.txt" );
	string sFic3 ( "../data" );

	try
	{
		if ( ! ExisteFichero ( sFic1 ) )
		{
			cout << "Dice que no existe el fichero: [" << sFic1 << "]" << endl;
			bRes = false;
		}
		if ( ExisteFichero ( sFic2 ) )
		{
			cout << "Dice que existe el fichero: [" << sFic2 << "]" << endl;
			bRes = false;
		}
		if ( ExisteFichero ( sFic3 ) )
		{
			cout << "Dice que el directorio es un fichero: [" << sFic3 << "]" << endl;
			bRes = false;
		}
	}
	catch ( ... )
	{
		cout << "Error al consultar la existencia del fichero" << endl;
		bRes = false;
	}
	return( bRes );
}

static bool TestVariableEntorno01 ()
{
	cout << "Test VariableEntorno01:" << endl;
	bool bRes = true;
	try
	{
		string sVarEx ( "TMP" );
		string sVar1 ( "VARIABLE_TEST1" );
		string sVar2 ( "VARIABLE_TEST2" );
		string sValEx ( "/cygdrive/c/Temp"  );
		string sVal1 ( "Valor1"  );
		string sVal2 ( "Valor 2"  );

		string sValRet = VariableEntorno ( sVarEx );
		if ( sValRet.size () > 0 )
		{
			cout << "La variable de entorno [" << sVarEx << "] tiene valor [" << sValRet << "]" << endl;
		}
		else
		{
			cout << "La variable de entorno [" << sVarEx << "] no se ha leido bien" << endl;
			bRes = false;
		}
		try
		{
			EliminarVariableEntorno ( sVar1 );
		}
		catch ( const Excepcion & ex )
		{
			cout << "Error al eliminar la variable de entorno [" << sVar1 << "]: " << ex.what () << endl;
			bRes = false;
		}
		if ( bRes )
		{
			sValRet = VariableEntorno ( sVar1 );
			if ( sValRet.size () > 0 )
			{
				cout << "La variable de entorno [" << sVar1 << "] con valor [" << sValRet << "] no deberia existir" << endl;
				bRes = false;
			}
		}
		try
		{
			EstablecerVariableEntorno ( sVar1, sVal1 );
		}
		catch ( const Excepcion & ex )
		{
			cout << "Caso1 : Error al establecer la variable de entorno [" << sVar1 << "]: " << ex.what () << endl;
			bRes = false;
		}
		if ( bRes )
		{
			string sValRet = VariableEntorno ( sVar1 );
			if ( sValRet != sVal1 )
			{
				cout << "Caso 1: La variable de entorno [" << sVar1 << "] se ha recuperado con valor erroneo: [" << sValRet << "]" << endl;
				bRes = false;
			}
		}
		try
		{
			EstablecerVariableEntorno ( sVar1, sVal2 );
		}
		catch ( const Excepcion & ex )
		{
			cout << "Caso2 : Error al establecer la variable de entorno [" << sVar1 << "]: " << ex.what () << endl;
			bRes = false;
		}
		if ( bRes )
		{
			string sValRet = VariableEntorno ( sVar1 );
			if ( sValRet != sVal2 )
			{
				cout << "Caso 3: La variable de entorno [" << sVar1 << "] se ha recuperado con valor erroneo: [" << sValRet << "]" << endl;
				bRes = false;
			}
		}
		if ( bRes )
		{
			try
			{
				EliminarVariableEntorno ( sVar1 );
			}
			catch ( const Excepcion & ex )
			{
				cout << "Error al eliminar la variable de entorno: "<< ex.what () << endl;
				bRes = false;
			}
		}
		if ( bRes )
		{
			sValRet = VariableEntorno ( sVar1 );
			if ( sValRet.size () > 0 )
			{
				cout << "La variable de entorno [" << sVar1 << "] con valor [" << sValRet << "] no deberia existir" << endl;
				bRes = false;
			}
		}
		try
		{
			EstablecerVariableEntorno ( sVar2, "" );
		}
		catch ( const Excepcion & ex )
		{
			cout << "Caso1 : Error al establecer la variable de entorno [" << sVar2 << "]: " << ex.what () << endl;
			bRes = false;
		}
		if ( bRes )
		{
			string sValRet = VariableEntorno ( sVar1 );
			if ( sValRet != "" )
			{
				cout << "Caso 1: La variable de entorno [" << sVar2 << "] se ha recuperado con valor erroneo: [" << sValRet << "]" << endl;
				bRes = false;
			}
		}
	}
	catch ( ... )
	{
		cout << "Error al operar con las variables de entorno" << endl;
		bRes = false;
	}
	return( bRes );
}

static bool TestEsperar01 ()
{
	cout << "Test Esperar01:" << endl;
	bool bRes = true;
	try
	{
		chrono::time_point<chrono::system_clock> ini = chrono::system_clock::now();
		Esperar ( 1237 );
		chrono::time_point<chrono::system_clock> fin = chrono::system_clock::now();

		chrono::duration<double> intervalo = fin - ini;
		cout << "Tiempo espera=1.237 Tiempo medido=" << intervalo.count () << endl;
 		if ( ! real::equalsWithPrec ( intervalo.count (), 1.237, 2 ) )
		{
			cout << "Tiempo de espera incorrecto" << endl;
			bRes = false;
		}
	}
	catch ( ... )
	{
		cout << "Error al hacer el test de la espera" << endl;
		bRes = false;
	}
	return( bRes );
}

static bool _bTestTestEstablecerManejadorInterrupciones01 = false;

void SignalHandlerTestEstablecerManejadorInterrupciones01( int signal )
{
	cout << "INTERRUPCION RECIBIDA POR MANEJADOR TEST=" << signal << endl;
	_bTestTestEstablecerManejadorInterrupciones01 = ! _bTestTestEstablecerManejadorInterrupciones01;
}

static bool TestEstablecerManejadorInterrupciones01 ()
{
	cout << "Test EstablecerManejadorInterrupciones01:" << endl;
	bool bRes = true;
	try
	{
		EstablecerManejadorInterrupciones ( SignalHandlerTestEstablecerManejadorInterrupciones01 );
		cout << "Lanzando SIGINT" << endl;
		raise ( SIGINT );
	}
	catch ( ... )
	{
		cout << "Error al testear el manejador de inteerupciones" << endl;
		bRes = false;
	}
	return( bRes );
}

static bool TestEstablecerManejadorInterrupciones02 ()
{
	cout << "Test EstablecerManejadorInterrupciones02" << endl;
	bool bRes = true;
	try
	{
		EstablecerManejadorInterrupcionesDefecto ();
		cout << "Lanzando SIGINT" << endl;
		raise ( SIGINT );
	}
	catch ( ... )
	{
		cout << "Error al testear el manejador de inteerupciones" << endl;
		bRes = false;
	}
	return( bRes );
}

static bool TestAhora01 ()
{
	cout << "Test Ahora01:" << endl;
	bool bRes = true;

	try
	{
		string sAhora = ToString( Ahora() );
		cout << "Hora actual: [" << sAhora << "]" << endl;
	}
	catch ( ... )
	{
		cout << "Error al recuperar la hora local del sistema" << endl;
		bRes = false;
	}
	return( bRes );
}

static bool TestPuedeLiberarse01 ()
{
	cout << "Test PuedeLiberarse01:" << endl;
	bool bRes = true;
	InicializarBase();
	
	int  iTest1 = 0;
	string sTest1( "noliberable" );
	int * iTest2 = (int *) malloc( sizeof( int ) );
	string * sTest2 = new string( "liberable" );

	try
	{
 		if ( PuedeLiberarse( &iTest1 ) )
		{
			cout << "Error caso 1" << endl;
			bRes = false;
		}
 		if ( PuedeLiberarse( &sTest1 ) )
		{
			cout << "Error caso 2" << endl;
			bRes = false;
		}
		if ( !PuedeLiberarse( iTest2 ) )
		{
			cout << "Error caso 3" << endl;
			bRes = false;
		}
 		if ( !PuedeLiberarse( sTest2 ) )
		{
			cout << "Error caso 4" << endl;
			bRes = false;
		}
	}
	catch ( ... )
	{
		cout << "Error al recuperar la hora local del sistema" << endl;
		bRes = false;
	}
	return( bRes );
}

static bool TestEjecutarComando01 ()
{
	cout << "Test EjecutarComando01:" << endl;
	bool bRes = true;

	try
	{
		string sRes( "" );
		if ( EsWindows() )
		{
			sRes = EjecutarComando( "systeminfo" );
		}
		else
		{
			sRes = EjecutarComando( "uname -a" );
		}
		cout << "Info sistema:" << endl << sRes << endl << "----------------------------------------------------------------" << endl;
		if ( sRes.size() == 0 )
		{
			cout << "Error: No se ha recogido el resultado" << endl;
			bRes = false;
		}
	}
	catch ( ... )
	{
		cout << "Error al recuperar la hora local del sistema" << endl;
		bRes = false;
	}
	return( bRes );
}


/* Una orden con salida conocida: la misma en cmd.exe que en sh. Se compara
   entera, no solo que haya algo, y sin el salto de linea final que quita la
   propia funcion ( "\r\n" en Windows, "\n" en POSIX ). */
/* HoraLocal y ToTimeString contra valores absolutos: con TZ a UTC, el instante
   1000000000 es el 2001-09-09 a las 01:46:40. El TZ de antes se restaura. Va
   por EstablecerVariableEntorno, que en WIN tiene que llegar a la copia del
   entorno que lee _tzset. */
static void _FijarZonaHoraria ( const char * p_cValor )
{
	if ( p_cValor != NULL )
	{
		EstablecerVariableEntorno ( "TZ", p_cValor );
	}
	else
	{
		EliminarVariableEntorno ( "TZ" );
	}
#if ( defined ( WIN ) )
	_tzset ();
#else
	tzset ();
#endif
}

/* Lo que se establece con EstablecerVariableEntorno lo tiene que ver getenv, que
   es por donde lo leen CVariablesEntorno, el stack C y el runtime ( la zona
   horaria, por ejemplo ). En WIN no lo veia: se escribia solo en el bloque Win32.
   Y al eliminarla tiene que desaparecer de las dos lecturas. */
static bool TestVariableEntorno02 ()
{
	cout << "Test VariableEntorno02:" << endl;
	bool bRes = true;
	const string sVar ( "GJS_VARIABLE_TEST_GETENV" );

	try
	{
		EstablecerVariableEntorno ( sVar, "valor con espacios" );
		const char * p_cValor = getenv ( sVar.c_str () );
		if ( ( p_cValor == NULL ) || ( string ( p_cValor ) != "valor con espacios" ) )
		{
			cout << "Error caso 1: getenv no ve la variable establecida: ["
				 << ( p_cValor != NULL ? p_cValor : "(null)" ) << "]" << endl;
			bRes = false;
		}
		if ( VariableEntorno ( sVar ) != "valor con espacios" )
		{
			cout << "Error caso 2: VariableEntorno dio [" << VariableEntorno ( sVar ) << "]" << endl;
			bRes = false;
		}
		EliminarVariableEntorno ( sVar );
		p_cValor = getenv ( sVar.c_str () );
		if ( ( p_cValor != NULL ) && ( p_cValor [ 0 ] != '\0' ) )
		{
			cout << "Error caso 3: getenv sigue viendo la variable eliminada: [" << p_cValor << "]" << endl;
			bRes = false;
		}
		if ( ! VariableEntorno ( sVar ).empty () )
		{
			cout << "Error caso 4: VariableEntorno sigue viendo la variable eliminada" << endl;
			bRes = false;
		}
	}
	catch ( const Excepcion & ex )
	{
		cout << "Error: excepcion " << ex.what () << endl;
		bRes = false;
	}
	return( bRes );
}

static bool TestHoraLocal01 ()
{
	cout << "Test HoraLocal01:" << endl;
	bool bRes = true;

	const char *	p_cTzPrevio = getenv ( "TZ" );
	const bool		bHabiaTz = ( p_cTzPrevio != NULL );
	const string	sTzPrevio ( bHabiaTz ? p_cTzPrevio : "" );

	_FijarZonaHoraria ( "UTC0" );

	tm tmValor;
	if ( ! HoraLocal ( (time_t) 1000000000, tmValor ) )
	{
		cout << "Error caso 1: HoraLocal no pudo convertir" << endl;
		bRes = false;
	}
	else if ( ( tmValor.tm_year != 101 ) || ( tmValor.tm_mon != 8 ) || ( tmValor.tm_mday != 9 ) ||
			  ( tmValor.tm_hour != 1 ) || ( tmValor.tm_min != 46 ) || ( tmValor.tm_sec != 40 ) )
	{
		cout << "Error caso 2: se esperaba 2001-09-09 01:46:40 y se ha obtenido "
			 << ( tmValor.tm_year + 1900 ) << "-" << ( tmValor.tm_mon + 1 ) << "-" << tmValor.tm_mday << " "
			 << tmValor.tm_hour << ":" << tmValor.tm_min << ":" << tmValor.tm_sec << endl;
		bRes = false;
	}
	string sHora = ToTimeString ( (time_t) 1000000000 );
	if ( sHora != "01:46:40" )
	{
		cout << "Error caso 3: ToTimeString dio [" << sHora << "], se esperaba [01:46:40]" << endl;
		bRes = false;
	}

	_FijarZonaHoraria ( bHabiaTz ? sTzPrevio.c_str () : NULL );
	return( bRes );
}


/* TextoErrno contra el texto exacto: el de ENOENT es el mismo en glibc, en la
   biblioteca de Cygwin y en el runtime de Microsoft. Un codigo absurdo no puede
   romper nada: o hay texto ( "Unknown error ..." ) o cadena vacia. */
static bool TestTextoErrno01 ()
{
	cout << "Test TextoErrno01:" << endl;
	bool bRes = true;

	string sTexto = TextoErrno ( ENOENT );
	if ( sTexto != "No such file or directory" )
	{
		cout << "Error caso 1: TextoErrno ( ENOENT ) dio [" << sTexto << "]" << endl;
		bRes = false;
	}
	sTexto = TextoErrno ( 987654 );
	cout << "Codigo inexistente: [" << sTexto << "]" << endl;
	return( bRes );
}


static bool TestEjecutarComando02 ()
{
	cout << "Test EjecutarComando02:" << endl;
	bool bRes = true;

	try
	{
		string sRes = EjecutarComando ( "echo hola" );
		if ( sRes != "hola" )
		{
			cout << "Error caso 1: se esperaba [hola] y se ha recibido [" << sRes << "]" << endl;
			bRes = false;
		}
	}
	catch ( ... )
	{
		cout << "Error caso 1: excepcion al ejecutar la orden" << endl;
		bRes = false;
	}
	return( bRes );
}


bool TestSistema ()
{
	bool bRes = true;
	cout << endl << ANSI::AMARILLO << "[Test Sistema]" << ANSI::RESETEAR << endl;
	if ( TestNombreSistema01() )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout  << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}
	if ( TestNombreSistema02() )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout  << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}
	if ( TestDirectorioActual01() )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout  << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}
	if ( TestResolverDirectorioRelativo01 () )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout  << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}
	if ( TestExisteDirectorio01() )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout  << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}
	if ( TestExisteFichero01() )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout  << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}
	if ( TestVariableEntorno01() )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout  << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}
	if ( TestEsperar01() )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout  << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}
	if ( TestAhora01() )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout  << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}
	if ( TestPuedeLiberarse01() )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout  << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}
	if ( TestEjecutarComando01() )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout  << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}
	if ( TestEjecutarComando02() )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout  << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}
	if ( TestVariableEntorno02() )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout  << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}
	if ( TestHoraLocal01() )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout  << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}
	if ( TestTextoErrno01() )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout  << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}
	if ( TestEstablecerManejadorInterrupciones01() )
	{
		if ( _bTestTestEstablecerManejadorInterrupciones01 )
		{
			cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
		}
		else
		{
			cout << "No se ha capturado el SIGINT" << endl;
			cout  << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
			bRes = false;
		}
	}
	else
	{
		cout  << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}
	if ( TestEstablecerManejadorInterrupciones02() )
	{
		if ( _bTestTestEstablecerManejadorInterrupciones01 )
		{
			cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
		}
		else
		{
			cout << "No se ha capturado el SIGINT o no se ha establecido el manejador de por defecto" << endl;
			cout  << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
			bRes = false;
		}
	}
	else
	{
		cout  << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}
	LimpiarManejadorInterrupciones ();
	return ( bRes );
}
