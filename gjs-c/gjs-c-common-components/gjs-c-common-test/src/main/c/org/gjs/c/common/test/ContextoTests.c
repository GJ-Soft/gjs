#include "ContextoTests.h"
#include "CTestConfig.h"


#define TEST_FIC_PROPIEDADES	"./../internal/test.properties"

		
		
static SPropiedades * 	_g_p_propContexto = NULL;		
static int 				_iControlAcceso = 0;
static int				_iEntornoTestInicializado = 0;


	
#if ( defined ( SIGNALS_PERMITIDOS ) )
void _TestSignalHandler ( int iSignal )
{
	// sigaction entrega el codigo de interrupcion del sistema operativo, mientras que
	// las rutinas SisSig* trabajan con los identificadores internos SIS_SIG_*: hay
	// que convertir con SisSigId, o el nombre que sale no es el de la interrupcion
	// recibida. Se evita ademas SisSigMensaje, que reserva memoria, cosa que no es
	// segura dentro de un manejador de interrupciones.
	int iId = SisSigId ( iSignal );
	SisConAsincEscribirConFormato ( "%sRecibida interrupcion: %s(%d): %s%s\n", ANSI_ROJO, SisSigNombre ( iId ), iSignal, SisSigDescripcion ( iId ), ANSI_RESETEAR );
	_exit ( -1 );
}		
#endif


void _PrepararContexto ()
{
	if ( ES_NULO ( _g_p_propContexto ) )
	{
		char * p_cDir = SisDirectorioActual ();
		char * p_cFic = SisResolverDirectorioRelativo ( p_cDir, TEST_FIC_PROPIEDADES );
		_g_p_propContexto = SPropCrear ( p_cFic );	
		MemLiberar ( (void **) &p_cDir );
		MemLiberar ( (void **) &p_cFic );
	}
}	

void _LiberarContexto ()
{
	if ( ES_VALIDO ( _g_p_propContexto ) )
	{
		SPropDestruir ( &_g_p_propContexto );	
	}
}	
		


void InicializarEntorno ()
{
	tas ( &_iControlAcceso );
	if ( _iEntornoTestInicializado <= 0 )
	{
#     if ( defined ( SIGNALS_PERMITIDOS ) )
		SisEstablecerManejadorInterrupciones( _TestSignalHandler );
#     endif
		_PrepararContexto();
		_iEntornoTestInicializado = 1;
	}
	else
	{
		_iEntornoTestInicializado = _iEntornoTestInicializado + 1;
	}
	printf ( "** CONTADOR=%d\n", _iEntornoTestInicializado );
		fflush(stdout);
	tar	( &_iControlAcceso );
}

void FinalizarEntorno ()
{
	tas ( &_iControlAcceso );
	if ( _iEntornoTestInicializado > 0 )
	{
		_iEntornoTestInicializado = _iEntornoTestInicializado - 1;
		printf ( "** CONTADOR=%d\n", _iEntornoTestInicializado );
		fflush(stdout);
		if ( _iEntornoTestInicializado == 0 )
		{
			_LiberarContexto();
#     if ( defined ( SIGNALS_PERMITIDOS ) )
			SisLimpiarManejadorInterrupciones ();
			// SisEstablecerManejadorInterrupcionesDefecto ();
#     endif
		}
	}
	tar	( &_iControlAcceso );
}
	

char * DirectorioProyecto ()
{
	const char * 	p_cValor;
	char * 			p_cDir;
	
	if ( ES_VALIDO ( _g_p_propContexto ) )
	{
		if ( SPropExistePropiedad ( _g_p_propContexto, "project.basedir" ) == 1 )
		{
			p_cValor = SPropObtPropiedad ( _g_p_propContexto, "project.basedir" );
			p_cDir = SisRutaEstiloSistema ( p_cValor );
		}
		else
		{
			p_cDir = NULL;
		}
	}
	else
	{
		p_cDir = NULL;
	}
	if ( CadLongitud ( p_cDir ) <= 0 )
	{
		MemLiberarCadena ( &p_cDir );
		p_cDir = SisResolverDirectorioRelativo ( SisDirectorioActual(), "./../../.." );
	}
	return ( p_cDir );
}

char * DirectorioTrabajo ()
{
	const char * 	p_cValor;
	char * 			p_cDir;
	
	if ( ES_VALIDO ( _g_p_propContexto ) )
	{
		if ( SPropExistePropiedad ( _g_p_propContexto, "project.build.directory" ) == 1 )
		{
			p_cValor = SPropObtPropiedad ( _g_p_propContexto, "project.build.directory" );
			p_cDir = SisRutaEstiloSistema ( p_cValor );
		}
		else
		{
			p_cDir = NULL;
		}
	}
	else
	{
		p_cDir = NULL;
	}
	if ( CadLongitud ( p_cDir ) <= 0 )
	{
		MemLiberarCadena ( &p_cDir );
		p_cDir = SisResolverDirectorioRelativo ( SisDirectorioActual(), "./../.." );
	}
	return ( p_cDir );
}
				
char * DirectorioTest ()
{
	const char * 	p_cValor;
	char * 			p_cDir;
	
	if ( ES_VALIDO ( _g_p_propContexto ) )
	{
		if ( SPropExistePropiedad ( _g_p_propContexto, "project.build.testDirectory" ) == 1 )
		{
			p_cValor = SPropObtPropiedad ( _g_p_propContexto, "project.build.testDirectory" );
			p_cDir = SisRutaEstiloSistema ( p_cValor );
			
		}
		else
		{
			p_cDir = NULL;
		}
	}
	else
	{
		p_cDir = NULL;
	}
	if ( CadLongitud ( p_cDir ) <= 0 )
	{
		MemLiberarCadena ( &p_cDir );
		p_cDir = SisResolverDirectorioRelativo ( SisDirectorioActual(), "./.." );
	}
	return ( p_cDir );
}

char * DirectorioTestRecursos()
{
	char * p_cDir = DirectorioTest ();
	char * p_cRes = SisResolverDirectorioRelativo ( p_cDir, "./resources" );
	MemLiberar ( (void **) &p_cDir );
	return ( p_cRes );
}

char * DirectorioTestResultados()
{
	char * p_cDir = DirectorioTest ();
	char * p_cRes = SisResolverDirectorioRelativo ( p_cDir, "./results" );
	MemLiberar ( (void **) &p_cDir );
	return ( p_cRes );
}

