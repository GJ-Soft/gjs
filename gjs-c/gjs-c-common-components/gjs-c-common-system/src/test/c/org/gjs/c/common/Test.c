#include "Base.h"



#define NUM_TESTS        22

extern int TestTiposSistema ();
extern int TestSistemaSignals ();
extern int TestVariablesEntorno ();
extern int TestSistemaErrores ();
extern int TestSistemaTiempo ();
extern int TestSistemaInformacion ();
extern int TestSistemaMemoria ();
extern int TestSistemaProcesos ();
extern int TestSistemaComandos ();
extern int TestSistemaRed ();
extern int TestSistemaUsuario ();
extern int TestSistemaLibrerias ();
extern int TestSistemaImpresoras ();
extern int TestSistemaSincronizacion ();
extern int TestSContadorCiclos ();
extern int TestSTemporizador ();
extern int TestSProceso ();
extern int TestSMutex ();
extern int TestSSemaforo ();
extern int TestSMemoriaCompartida ();
extern int TestSRelojProgramable ();
extern int TestSGestorSignals ();

char ** testArrayInit ()
{
    char ** p_p_cTests = (char **) MemReservar ( NUM_TESTS * sizeof( char *));
    p_p_cTests[ 0 ] = CadDuplicar ( "TiposSistemaTest" );
    p_p_cTests[ 1 ] = CadDuplicar ( "SistemaSignalsTest" );
    p_p_cTests[ 2 ] = CadDuplicar ( "VariablesEntornoTest" );
    p_p_cTests[ 3 ] = CadDuplicar ( "SistemaErroresTest" );
    p_p_cTests[ 4 ] = CadDuplicar ( "SistemaTiempoTest" );
    p_p_cTests[ 5 ] = CadDuplicar ( "SistemaInformacionTest" );
    p_p_cTests[ 6 ] = CadDuplicar ( "SistemaMemoriaTest" );
    p_p_cTests[ 7 ] = CadDuplicar ( "SistemaProcesosTest" );
    p_p_cTests[ 8 ] = CadDuplicar ( "SistemaComandosTest" );
    p_p_cTests[ 9 ] = CadDuplicar ( "SistemaRedTest" );
    p_p_cTests[ 10 ] = CadDuplicar ( "SistemaUsuarioTest" );
    p_p_cTests[ 11 ] = CadDuplicar ( "SistemaLibreriasTest" );
    p_p_cTests[ 12 ] = CadDuplicar ( "SistemaImpresorasTest" );
    p_p_cTests[ 13 ] = CadDuplicar ( "SistemaSincronizacionTest" );
    p_p_cTests[ 14 ] = CadDuplicar ( "SContadorCiclosTest" );
    p_p_cTests[ 15 ] = CadDuplicar ( "STemporizadorTest" );
    p_p_cTests[ 16 ] = CadDuplicar ( "SProcesoTest" );
    p_p_cTests[ 17 ] = CadDuplicar ( "SMutexTest" );
    p_p_cTests[ 18 ] = CadDuplicar ( "SSemaforoTest" );
    p_p_cTests[ 19 ] = CadDuplicar ( "SMemoriaCompartidaTest" );
    p_p_cTests[ 20 ] = CadDuplicar ( "SRelojProgramableTest" );
    p_p_cTests[ 21 ] = CadDuplicar ( "SGestorSignalsTest" );
    return p_p_cTests;
}

PFUNINTV * functionArrayInit ()
{
    PFUNINTV* p_fTests = (PFUNINTV *) MemReservar ( NUM_TESTS * sizeof( PFUNINTV ));
    p_fTests[ 0 ] = TestTiposSistema;
    p_fTests[ 1 ] = TestSistemaSignals;
    p_fTests[ 2 ] = TestVariablesEntorno;
    p_fTests[ 3 ] = TestSistemaErrores;
    p_fTests[ 4 ] = TestSistemaTiempo;
    p_fTests[ 5 ] = TestSistemaInformacion;
    p_fTests[ 6 ] = TestSistemaMemoria;
    p_fTests[ 7 ] = TestSistemaProcesos;
    p_fTests[ 8 ] = TestSistemaComandos;
    p_fTests[ 9 ] = TestSistemaRed;
    p_fTests[ 10 ] = TestSistemaUsuario;
    p_fTests[ 11 ] = TestSistemaLibrerias;
    p_fTests[ 12 ] = TestSistemaImpresoras;
    p_fTests[ 13 ] = TestSistemaSincronizacion;
    p_fTests[ 14 ] = TestSContadorCiclos;
    p_fTests[ 15 ] = TestSTemporizador;
    p_fTests[ 16 ] = TestSProceso;
    p_fTests[ 17 ] = TestSMutex;
    p_fTests[ 18 ] = TestSSemaforo;
    p_fTests[ 19 ] = TestSMemoriaCompartida;
    p_fTests[ 20 ] = TestSRelojProgramable;
    p_fTests[ 21 ] = TestSGestorSignals;
    return p_fTests;
}

void freeArrays( char ** p_p_cTests, PFUNINTV* p_fTests )
{
    for ( int i = 0; i < NUM_TESTS; i = i + 1 ) {
        MemLiberar ( (void **) &(p_p_cTests[ i ]) );
    }
    MemLiberar ( (void **) p_p_cTests );
    MemLiberar ( (void **) &p_fTests );
}

int findTest ( char ** p_p_cTests, char * p_cTest )
{
    int iIndex = -1;
    int i = 0;
    while ( ( i < NUM_TESTS) && ( iIndex < 0 ) )
    {
        if ( CadComparar ( p_p_cTests[ i ], p_cTest ) == COMP_IGUAL )
        {
            iIndex = i;
        }
        i = i + 1;
    }
    return ( iIndex );
}

int main ( int argc, char * argv[] )
{
	int iRes = 0;

	char ** p_p_cTests = testArrayInit ();
    PFUNINTV * p_fTests = functionArrayInit ();

	char * p_cTest = 0x0;
	if ( argc > 1 )
	{
		p_cTest = argv[1];
	}
	if ( CadLongitud ( p_cTest ) > 0 )
	{
	    int iTest = findTest ( p_p_cTests, p_cTest );
		if ( iTest >= 0 )
		{
			PFUNINTV fTest = p_fTests[ iTest ];
			if( fTest () != 1 )
			{
				iRes = -1;
			}
		}
		else
		{
			printf( "Test [%s] no encontrado.", p_cTest );
			iRes = -1;
		}
		return( iRes );
	}

	for ( int iTest = 0; iTest < NUM_TESTS; iTest = iTest + 1 )
	{
		PFUNINTV fTest = p_fTests[ iTest ];
		if( fTest () != 1 )
		{
			iRes = -1;
		}
	}
	freeArrays( p_p_cTests, p_fTests );
	fflush ( stdout );
	return ( iRes );
}
