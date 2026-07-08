#include "BaseConfig.h"
#include "Sistema.h"

#include "Excepcion.h"
#include "ToString.h"
#include "Concatenar.h"
#include "Cadenas.h"
#include <sys/utsname.h>
#include <stdlib.h>

#include <csignal>
#include <csetjmp>

#include <netdb.h>
#include <arpa/inet.h>


#if ( defined ( POSIX ) )
extern char ** environ;
#endif


#if ( defined ( WIN ) )
#  	define 	MAX_ENV_VALUE 	32767
#endif

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
	struct utsname sysinfo;
    if ( uname ( &sysinfo ) == 0 )
	{
		return ( string ( sysinfo.sysname ) );
	}
	#pragma GCC diagnostic push
	#pragma GCC diagnostic ignored "-Wterminate"
	throw ( Excepcion ( "Sistema", "NombreSistema", "Error llamando a uname" ) );
	#pragma GCC diagnostic pop
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



void EstablecerVariableEntorno ( const string & sNombre, const string & sValor )
{
	const char * p_cNombre = sNombre.c_str();
	const char * p_cValor = sValor.c_str();
#if ( defined ( POSIX ) )
#  if  ( defined ( CYGWIN ) )
	if ( ( p_cNombre != NULL ) && ( p_cValor != NULL ) )
	{
		int iTamNombre = strlen( p_cNombre );
		if ( iTamNombre > 0 )
		{
			try
			{
				int iTamEnvValor = iTamNombre + strlen( p_cValor ) + 1;
				char * p_cEnvValor = (char *) malloc ( iTamEnvValor + 1 );
				memset( p_cEnvValor, 0x0, iTamEnvValor + 1 );
				sprintf( p_cEnvValor, "%s=%s", p_cNombre, p_cValor );
				int iTam = 0;
				int iPos = -1;
				bool bFound = false;
				for ( char **env = environ; *env != NULL; env++ )
				{
					if ( !bFound && ( iPos < 0 ) && ( *env == INVALID_POSITION ) )
					{
						iPos = iTam;
					}
					if ( !bFound && ( strlen( *env ) > iTamNombre ) &&
						 ( strncmp( p_cNombre, *env, iTamNombre ) == 0 ) &&
						 ( (*env)[ iTamNombre ] == '=' )  )
					{
						iPos = iTam;
						break;
					}
					iTam = iTam + 1;
				}
				if ( iPos < 0 )
				{
					iPos = iTam;
					environ = (char **) realloc( environ, (iTam + 1) * sizeof (char *) );
					environ[ iTam + 1 ] = NULL;
				}
				else if ( environ[ iPos ] != INVALID_POSITION )
				{
					free( environ[ iPos ] );
				}
				environ[ iPos ] = p_cEnvValor;
			}
			catch ( const exception & ex )
			{
				throw ( Excepcion ( "Sistema", "EstablecerVariableEntorno", Concatenar ( "Imposible establecer la variable de entorno ", p_cNombre ), ex ) );
			}
		}
		else
		{
			throw ( Excepcion ( "Sistema", "EstablecerVariableEntorno", "Imposible establecer la variable de entorno con nombre vacio" ) );
		}
	}
	else
	{
		throw ( Excepcion ( "Sistema", "EstablecerVariableEntorno", "Imposible establecer la variable de entorno con algun parametro NULO" ) );
	}
#  else
	if ( setenv ( p_cNombre, p_cValor, 1 ) != 0 )
	{
		throw ( Excepcion ( "Sistema", "EstablecerVariableEntorno", Concatenar ( "Imposible establecer la variable de entorno ", p_cNombre, ". Error=", ToString ( errno ) ) ) );
	}
#  endif
#else
	printf ( "*** SETENVIRONMENT %s=%s\n", p_cNombre, p_cValor);
	if ( SetEnvironmentVariableA ( p_cNombre, p_cValor ) == 0 )
	{
		throw ( Excepcion ( "Sistema", "EstablecerVariableEntorno", Concatenar ( "Imposible establecer la variable de entorno ", p_cNombre, ". Error=", ToString ( GetLastError() ) ) ) );
	}
	printf("RESULT=%s\n", getenv(p_cNombre));
	fflush(stdout);
#endif
}

void EliminarVariableEntorno ( const string & sNombre )
{
	const char * p_cNombre = sNombre.c_str();
#if ( defined ( POSIX ) )
#  if  ( defined ( CYGWIN ) )
	if ( p_cNombre != NULL )
	{
		int iTamNombre = strlen( p_cNombre );
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
				if ( iPos > 0 )
				{
					if ( environ[ iPos ] != INVALID_POSITION )
					{
						free( environ[ iPos ] );
						environ[ iPos ] = (char *) INVALID_POSITION;
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

        int parsed = sscanf( line.c_str(), "%lx-%lx %7s %15s %15s %lu %255s",
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

int ResolverIP( const string & sIP )
{
	int iIP = INADDR_ANY;
	if ( sIP.size() > 0 )
	{
		struct sockaddr_in inaddr;

		memset ((char * ) &inaddr, 0, sizeof( inaddr ) );
		inaddr.sin_addr.s_addr = inet_addr( sIP.c_str() );
		if ( (int)( inaddr.sin_addr.s_addr ) == -1 )
		{
			struct hostent *hostp = gethostbyname( sIP.c_str() );
			if ( hostp != NULL )
			{
				if ( hostp->h_addrtype == AF_INET)
				{
					memcpy( (char * ) &inaddr.sin_addr, (char * ) hostp->h_addr, sizeof( inaddr.sin_addr ) );
					iIP = inaddr.sin_addr.s_addr;
				}
			}
		}
		else
		{
			iIP = inaddr.sin_addr.s_addr;
		}
	}
	return( iIP );
}

string EjecutarComando ( const string & sComando )
{
    char sFicTemporal [ L_tmpnam ];
    tmpnam ( sFicTemporal );
    string sCmd = sComando + " >> " + sFicTemporal;
    system( sCmd.c_str() );
    ifstream ifFichero( sFicTemporal, ios::in | ios::binary );
    string sResultado;
    if ( ifFichero )
	{
        while ( !ifFichero.eof() )
		{
			char c =  ifFichero.get();
			if ( (int) c > 0 )
			{
				sResultado.push_back( c );
			}
		}
        ifFichero.close();
    }
    remove( sFicTemporal );
    return( EliminarUltimoSaltoLinea( sResultado ) );
}


            }
		}
	}
}
