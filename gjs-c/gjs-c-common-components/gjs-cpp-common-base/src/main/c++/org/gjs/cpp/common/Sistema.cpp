#include "BaseConfig.h"
#include "Sistema.h"

#include "Excepcion.h"
#include "ToString.h"
#include "Concatenar.h"
#include "Cadenas.h"
#if ( ! defined ( WIN ) )
#	include <sys/utsname.h>
#endif
#include <stdlib.h>

#include <csignal>
#include <csetjmp>
#include <cinttypes>

#if ( defined ( WIN ) )
#  	define 	MAX_ENV_VALUE 	32767
#endif

#define SIS_MAX_TAM_VARIABLE			255
#define SIS_MAX_TAM_VALOR				255



using namespace std;

namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {


string NombreSistema ()
{
#if ( defined ( WIN ) )
	/* Windows no tiene uname (). El stack C hace lo mismo en SisSistema ():
	   devolver el nombre a secas, que es lo que consultan EsWindows () y
	   companeras. Bajo Cygwin no se entra aqui, y uname da CYGWIN_NT-... */
	return ( string ( "Windows" ) );
#else
	struct utsname sysinfo;
    if ( uname ( &sysinfo ) == 0 )
	{
		return ( string ( sysinfo.sysname ) );
	}
	#pragma GCC diagnostic push
	#pragma GCC diagnostic ignored "-Wterminate"
	throw ( Excepcion ( "Sistema", "NombreSistema", "Error llamando a uname" ) );
	#pragma GCC diagnostic pop
#endif
}

bool EsWindows ()
{
	string sSistema = NombreSistema ();
	return ( sSistema.find ( "Windows" ) == 0 );
}

bool EsCygwin ()
{
	string sSistema = NombreSistema ();
	return ( sSistema.find ( "CYGWIN" ) == 0 );
}

bool EsMinGW ()
{
	string sSistema = NombreSistema ();
	return ( sSistema.find ( "MINGW" ) == 0 );
}

bool EsLinux ()
{
	string sSistema = NombreSistema ();
	return ( sSistema.find ( "Linux" ) == 0 );
}

bool EsUnix ()
{
	string sSistema = NombreSistema ();
	return ( ( sSistema.find ( "GNU" ) == 0 ) ||
			 ( sSistema.find ( "FreeBSD" ) == 0 ) ||
			 ( sSistema.find ( "HP-UX " ) == 0 ) ||
			 ( sSistema.find ( "AIX" ) == 0 ) ||
			 ( sSistema.find ( "OpenBSD" ) == 0 ) ||
			 ( sSistema.find ( "SunOS" ) == 0 )
			);
}

bool EsMac ()
{
	string sSistema = NombreSistema ();
	return ( sSistema.find ( "Darwin" ) == 0 );
}

string DirectorioActual ()
{
	filesystem::path cwd = filesystem::current_path();
	return ( cwd.string() );
}

string ResolverDirectorioRelativo ( string sRutaBase, string sRutaRelativa )
{
	filesystem::path cwd = sRutaBase;
	if ( EmpiezaPor( sRutaRelativa, "." ) || EmpiezaPor( sRutaRelativa, ".." ) )
	{
		vector<string> vecSubdirectorios = Separar( sRutaRelativa, { "/" } );
		for ( string sSubdir : vecSubdirectorios )
		{
			if ( sSubdir.compare( ".." ) == 0 )
			{
				cwd = cwd.parent_path();
			}
			else if ( sSubdir.compare( "." ) != 0 )
			{
				cwd = cwd / sSubdir;
			}
		}
	}
	return ( cwd.string() );
}

void EstablecerDirectorio ( const string & sRuta )
{
	try
	{
		filesystem::path pathRuta( sRuta );
		if ( pathRuta.is_relative() )
		{
			pathRuta = filesystem::current_path () / pathRuta;
		}
		filesystem::current_path ( pathRuta );
	}
	catch ( const exception & ex )
	{
		throw ( Excepcion ( "Sistema", "EstablecerDirectorio", Concatenar( "No se ha podido establecer la ruta [", sRuta, "]" ), ex ) );
	}
}

bool ExisteFichero ( const string & sRuta )
{
	bool bRes = false;
	if ( filesystem::exists( sRuta ) )
	{
		bRes = filesystem::is_regular_file ( sRuta );
	}
	return ( bRes );
}

bool ExisteDirectorio ( const string & sRuta )
{
	bool bRes = false;
	if ( filesystem::exists( sRuta ) )
	{
		bRes = filesystem::is_directory ( sRuta );
	}
	return ( bRes );
}

string VariableEntorno ( const string & sNombre )
{
	string sRes ( "" );
#if ( defined ( POSIX ) )
	char * p_cValor;
#endif

#if ( defined ( POSIX ) )
	p_cValor = getenv ( sNombre.c_str () );
	if ( p_cValor != NULL )
	{
		sRes = string ( p_cValor );
	}
#else
 	vector<char> buffer ( MAX_ENV_VALUE );
	GetEnvironmentVariableA ( sNombre.c_str (),  (LPSTR) buffer.data (), (DWORD) buffer.size () );
	sRes = string ( buffer.data () );
#endif
	return ( sRes );
}

/*
 * La variable environ en CYGWIN admite realloc de espacio de memoria limitado. De momento
 * evitamos el realloc a menor espacio, por lo que usamos un mecanismo de invalidación de
 * posiciones típico.
 * SÓLO DEBE USARSE PARA TEST
 */
const char * INVALID_POSITION = "XXX";

#define _ENTORNO_FORM_EST_VARIABLE		"%s=%s"
#define _ENTORNO_MAX_TAM_CAD_DEF		( SIS_MAX_TAM_VARIABLE + SIS_MAX_TAM_VALOR + 1 )

void EstablecerVariableEntorno ( const string & sNombre, const string & sValor )
{
	if ( !sNombre.empty () )
	{
		const char * p_cNombre = sNombre.c_str();
		const char * p_cValor = sValor.c_str();
		
#	if ( defined ( WIN) )
		if ( SetEnvironmentVariableA ( p_cNombre, p_cValor ) == 0 )
		{
			throw ( Excepcion ( "Sistema", "EstablecerVariableEntorno", Concatenar ( "Imposible establecer la variable de entorno ", p_cNombre, ". Error=", ToString ( GetLastError() ) ) ) );
		}
#	else
	if ( setenv ( p_cNombre, p_cValor, 1 ) != 0 )
	{
		throw ( Excepcion ( "Sistema", "EstablecerVariableEntorno", Concatenar ( "Imposible establecer la variable de entorno ", p_cNombre, ". Error=", ToString ( errno ) ) ) );
	}
	/*
		char * p_cVarEnt = (char *) malloc ( _ENTORNO_MAX_TAM_CAD_DEF + 1 );
		if ( ES_VALIDO ( p_cVarEnt ) )
		{
			if ( ES_NULO ( p_cValor ) )
			{
				snprintf ( p_cVarEnt, _ENTORNO_MAX_TAM_CAD_DEF, _ENTORNO_FORM_EST_VARIABLE, p_cNombre, "" );
			}
			else
			{
				snprintf ( p_cVarEnt, _ENTORNO_MAX_TAM_CAD_DEF, _ENTORNO_FORM_EST_VARIABLE, p_cNombre, p_cValor );
			}
			
			if ( putenv ( p_cVarEnt ) != 0 )
			{
				throw ( Excepcion ( "Sistema", "EstablecerVariableEntorno", Concatenar ( "Imposible establecer la variable de entorno ", p_cNombre, ". Error=", ToString ( errno ) ) ) );
			}
			free ( p_cVarEnt );
		}
		else
		{
			throw ( Excepcion ( "Sistema", "EstablecerVariableEntorno", Concatenar ( "Imposible establecer la variable de entorno ", p_cNombre, ". Error=", ToString ( errno ) ) ) );
		}
		*/
#	endif
	}
	else
	{
		throw ( Excepcion ( "Sistema", "EstablecerVariableEntorno", "Imposible establecer una variable de entorno vacia" ) );
	}
}

void EliminarVariableEntorno ( const string & sNombre )
{
	const char * p_cNombre = sNombre.c_str();
#if ( defined ( POSIX ) )
#  if  ( defined ( CYGWIN ) )
	if ( p_cNombre != NULL )
	{
		/* size_t, que es lo que devuelve strlen y lo que piden strncmp y el indice. */
		size_t iTamNombre = strlen( p_cNombre );
		if ( iTamNombre > 0 )
		{
			try
			{
				int iTam = 0;
				int iPos = -1;
				for ( char **env = environ; *env != NULL; env++ )
				{
					if ( ( iPos < 0 ) && ( strlen( *env ) > iTamNombre ) &&
						 ( strncmp( p_cNombre, *env, iTamNombre ) == 0 ) &&
						 ( (*env)[ iTamNombre ] == '=' )  )
					{
						iPos = iTam;
						break;
					}
					iTam = iTam + 1;
				}
				if ( iPos >= 0 )
				{
					if ( environ[ iPos ] != INVALID_POSITION )
					{
						free( environ[ iPos ] );
						/* const_cast, no un cast a secas, porque eso es justo lo que pasa
						   aqui: INVALID_POSITION es un const char * que apunta al literal
						   "XXX" ( linea 190 ), y se guarda en environ, que es char **.
						   Explicitarlo deja a la vista lo que el cast tapaba.

						   NOTA DE DISENO, no trabajo pendiente: el centinela en si es
						   discutible, pero funciona. La entrada queda
						   como "XXX", que no es una variable de entorno valida ( no lleva
						   '=' ), y la comparacion de arriba es de PUNTEROS contra el mismo
						   literal: solo funciona porque este codigo es el unico que lo
						   escribe. Si algun dia alguien hace free () de esa entrada,
						   estaria liberando un literal. */
						environ[ iPos ] = const_cast < char * > ( INVALID_POSITION );
					}
				}
			}
			catch ( const exception & ex )
			{
				throw ( Excepcion ( "Sistema", "EstablecerVariableEntorno", Concatenar ( "Imposible establecer la variable de entorno ", p_cNombre ), ex ) );
			}
		}
}
#  else
	if ( unsetenv ( p_cNombre ) != 0 )
	{
		throw ( Excepcion ( "Sistema", "EstablecerVariableEntorno", Concatenar ( "Imposible eliminar la variable de entorno ", p_cNombre, ". Error=", ToString ( errno ) ) ) );
	}
# endif
#else
	if ( SetEnvironmentVariableA ( p_cNombre, NULL ) == 0 )
	{
		throw ( Excepcion ( "Sistema", "EstablecerVariableEntorno", Concatenar ( "Imposible eliminar la variable de entorno ", p_cNombre, ". Error=", ToString ( errno ) ) ) );
	}
#endif
}

void Esperar ( long lMiliseg )
{
	this_thread::sleep_for ( chrono::milliseconds ( lMiliseg ) );
}


//static bool _bRetornar = false;
//static jmp_buf _entornoRetorno;

void SignalHandlerPorDefecto ( int signal )
{
	cout << "INTERRUPCION RECIBIDA=" << signal << endl;
	//if ( signal == SIGABRT )
	//{
	//	RetornarAPrograma ();
	//}
}

//void GrabarRetornoAPrograma()
//{
//	_bRetornar = true;
//	setjmp( _entornoRetorno );
//}

//void RetornarAPrograma ()
//{
//	if ( _bRetornar )
//	{
//		_bRetornar = false;
//		cout << "retornando" << endl;
//		longjmp( _entornoRetorno, 1 );
//	}
//}

void EstablecerManejadorInterrupciones ( SIGNAL_HANDLER fManejador )
{
	signal( SIGTERM, fManejador );
	signal( SIGSEGV, fManejador );
	signal( SIGINT, fManejador );
	signal( SIGILL, fManejador );
	signal( SIGABRT, fManejador );
	signal( SIGFPE, fManejador );
}

void EstablecerManejadorInterrupcionesDefecto ()
{
	EstablecerManejadorInterrupciones( SignalHandlerPorDefecto );
}

void LimpiarManejadorInterrupciones ()
{
	EstablecerManejadorInterrupciones( NULL );
}

time_t Ahora ()
{
	chrono::system_clock::time_point ahora = chrono::system_clock::now();
	return ( chrono::system_clock::to_time_t( ahora ) );
}


static void * _inicio_heap = NULL;

void InicializarBase ()
{
	if ( _inicio_heap == NULL )
	{
		_inicio_heap = malloc( sizeof( int ) );
	}
}

#if ( defined ( WIN ) )

bool PuedeLiberarse ( const void * ptr )
{
	/* Windows no tiene /proc/self/maps: en nativo el fichero no existe, el ifstream
	   fallaba en silencio y la funcion contestaba CIERTO a nada, asi que ningun
	   puntero del monton se daba por liberable. VirtualQuery da esa misma
	   informacion region a region ( donde empieza, cuanto ocupa, con que permisos
	   y de que tipo es ), que es lo que se leia de cada linea del fichero.

	   Se exige que la region este reservada y accesible ( MEM_COMMIT ), que sea
	   privada ( MEM_PRIVATE descarta el codigo y los datos estaticos de los
	   modulos, que son MEM_IMAGE ) y de lectura/escritura. La pila del hilo cumple
	   las tres, asi que se descarta aparte con los limites que publica el TEB. Lo
	   que pasa los dos filtros es memoria del monton. */
	if ( ptr == NULL )
	{
		return ( false );
	}

	MEMORY_BASIC_INFORMATION mbiRegion;
	if ( VirtualQuery ( ptr, &mbiRegion, sizeof ( mbiRegion ) ) == 0 )
	{
		return ( false );
	}
	if ( ( mbiRegion.State != MEM_COMMIT ) || ( mbiRegion.Type != MEM_PRIVATE ) )
	{
		return ( false );
	}

	/* Los 8 bits bajos llevan el permiso; los altos, modificadores como
	   PAGE_GUARD o PAGE_NOCACHE, que aqui no vienen al caso. */
	DWORD dwPermiso = ( mbiRegion.Protect & 0xFF );
	if ( ( dwPermiso != PAGE_READWRITE ) && ( dwPermiso != PAGE_EXECUTE_READWRITE ) )
	{
		return ( false );
	}

	/* NtCurrentTeb () no depende de la version de Windows, al contrario que
	   GetCurrentThreadStackLimits (), que pide _WIN32_WINNT 0x0602 y aqui esta
	   puesto a 0x0500 ( ver Precompilacion.h ). El TEB empieza por su NT_TIB. */
	const NT_TIB *	p_tibHilo = reinterpret_cast < const NT_TIB * > ( NtCurrentTeb () );
	uintptr_t		uipDireccion = reinterpret_cast < uintptr_t > ( ptr );
	if ( ( uipDireccion >= reinterpret_cast < uintptr_t > ( p_tibHilo->StackLimit ) ) &&
		 ( uipDireccion <  reinterpret_cast < uintptr_t > ( p_tibHilo->StackBase ) ) )
	{
		return ( false );
	}
	return ( true );
}

#else

bool PuedeLiberarse ( const void * ptr )
{
    uintptr_t addr = reinterpret_cast<uintptr_t>(ptr);
    std::ifstream maps( "/proc/self/maps" );
    std::string line;

	bool bRes = false;
    while ( !bRes && std::getline ( maps, line ) ) 
	{
        uintptr_t start, end;
        char perms[8] = {};
        char offset[16] = {};
        char dev[16] = {};
        unsigned long inode = 0;
        char pathname[256] = {};

        /* %llx pide un unsigned long long *, y start / end son uintptr_t. En x86-64
           los dos miden 8 bytes y colaba, pero es el tipo equivocado: en una
           plataforma de 32 bits sscanf escribiria 8 bytes sobre una variable de 4.
           SCNxPTR es el especificador que corresponde a uintptr_t en cada una. */
        int parsed = sscanf( line.c_str(), "%" SCNxPTR "-%" SCNxPTR " %7s %15s %15s %lu %255s",
                            &start, &end, perms, offset, dev, &inode, pathname );

        // Cubrir [heap] explícito
        bool is_named_heap = ( parsed >= 7 && strcmp( pathname, "[heap]" ) == 0 );

        // Cubrir mmap anónimo rw-p sin nombre (bloques grandes de malloc)
        // inode == 0 descarta ficheros mapeados
        // parsed < 7 significa que no hay pathname en absoluto
        bool is_anon_rw = (strcmp(perms, "rw-p") == 0)
                          && (inode == 0)
                          && (parsed < 7 || pathname[0] == '\0');

        bRes = ( is_named_heap || is_anon_rw ) && ( addr >= start ) && ( addr < end );
	}
    return ( bRes );
}

#endif

string EjecutarComando ( const string & sComando )
{
	/* tmpnam () da un nombre unico, pero en Windows lo da en la RAIZ de la unidad
	   actual ( "\s15ok." ), donde un usuario normal no puede crear ficheros: la
	   redireccion fallaba con "El cliente no dispone de un privilegio requerido",
	   el fichero no llegaba a existir y la funcion devolvia la cadena vacia. Se
	   conserva el nombre, que es lo unico que se le pedia, y se lleva al directorio
	   temporal de verdad; temp_directory_path () lo resuelve en las dos plataformas
	   ( TMP / TMPDIR ). El punto final que anade tmpnam en Windows se cambia por
	   una extension, que un nombre acabado en punto no es valido. */
	char sFicTemporal [ L_tmpnam ];
	tmpnam ( sFicTemporal );
	filesystem::path pathTemporal = filesystem::temp_directory_path () /
									( filesystem::path ( sFicTemporal ).stem ().string () + ".tmp" );

	/* Entrecomillada: la ruta temporal lleva espacios muy a menudo, y sin comillas
	   el interprete de ordenes parte la redireccion por el primero. */
	string sCmd = sComando + " >> \"" + pathTemporal.string () + "\"";
	system ( sCmd.c_str () );
	ifstream ifFichero ( pathTemporal, ios::in | ios::binary );
	string sResultado;
	if ( ifFichero )
	{
		/* El bucle anterior leia byte a byte y se quedaba solo con los que daban
		   ( int ) c mayor que cero, para descartar el centinela de EOF. Pero char
		   es con signo en gcc, asi que ese filtro se llevaba por delante TODO byte
		   >= 0x80: en una salida en castellano desaparecian los acentos, y quedaba
		   "Versin del sistema operativo". rdbuf () vuelca el fichero entero, sin
		   centinela que descartar y sin mirar el signo de nada. */
		ostringstream ossContenido;
		ossContenido << ifFichero.rdbuf ();
		sResultado = ossContenido.str ();
		ifFichero.close ();
	}
	filesystem::remove ( pathTemporal );
    return( EliminarUltimoSaltoLinea( sResultado ) );
}


            }
		}
	}
}
