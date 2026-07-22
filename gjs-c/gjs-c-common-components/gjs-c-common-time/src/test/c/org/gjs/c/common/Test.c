#include "Base.h"


#define NUM_TESTS        17

extern int TestFechas ();
extern int TestHoras ();
extern int TestCalendario ();
extern int TestSistemasHorarios ();
extern int TestTiposPeriodicidad ();
extern int TestHusosHorarios ();
extern int TestZonasHorarias ();
extern int TestUTC ();
extern int TestTiempoNumerico ();
extern int TestTiempoSistema ();
extern int TestSFecha ();
extern int TestSHora ();
extern int TestSFechaHora ();
extern int TestSCronometro ();
extern int TestSReloj ();
extern int TestSPeriodo ();
extern int TestDeteccion ();

char ** testArrayInit ()
{
    char ** p_p_cTests = (char **) MemReservar ( NUM_TESTS * sizeof( char *));
    p_p_cTests[ 0 ] = CadDuplicar ( "FechasTest" );
    p_p_cTests[ 1 ] = CadDuplicar ( "HorasTest" );
    p_p_cTests[ 2 ] = CadDuplicar ( "CalendarioTest" );
    p_p_cTests[ 3 ] = CadDuplicar ( "SistemasHorariosTest" );
    p_p_cTests[ 4 ] = CadDuplicar ( "TiposPeriodicidadTest" );
    p_p_cTests[ 5 ] = CadDuplicar ( "HusosHorariosTest" );
    p_p_cTests[ 6 ] = CadDuplicar ( "ZonasHorariasTest" );
    p_p_cTests[ 7 ] = CadDuplicar ( "UTCTest" );
    p_p_cTests[ 8 ] = CadDuplicar ( "TiempoNumericoTest" );
    p_p_cTests[ 9 ] = CadDuplicar ( "TiempoSistemaTest" );
    p_p_cTests[ 10 ] = CadDuplicar ( "SFechaTest" );
    p_p_cTests[ 11 ] = CadDuplicar ( "SHoraTest" );
    p_p_cTests[ 12 ] = CadDuplicar ( "SFechaHoraTest" );
    p_p_cTests[ 13 ] = CadDuplicar ( "SCronometroTest" );
    p_p_cTests[ 14 ] = CadDuplicar ( "SRelojTest" );
    p_p_cTests[ 15 ] = CadDuplicar ( "SPeriodoTest" );
    p_p_cTests[ 16 ] = CadDuplicar ( "DeteccionTest" );
    return p_p_cTests;
}

PFUNINTV * functionArrayInit ()
{
    PFUNINTV* p_fTests = (PFUNINTV *) MemReservar ( NUM_TESTS * sizeof( PFUNINTV ));
    p_fTests[ 0 ] = TestFechas;
    p_fTests[ 1 ] = TestHoras;
    p_fTests[ 2 ] = TestCalendario;
    p_fTests[ 3 ] = TestSistemasHorarios;
    p_fTests[ 4 ] = TestTiposPeriodicidad;
    p_fTests[ 5 ] = TestHusosHorarios;
    p_fTests[ 6 ] = TestZonasHorarias;
    p_fTests[ 7 ] = TestUTC;
    p_fTests[ 8 ] = TestTiempoNumerico;
    p_fTests[ 9 ] = TestTiempoSistema;
    p_fTests[ 10 ] = TestSFecha;
    p_fTests[ 11 ] = TestSHora;
    p_fTests[ 12 ] = TestSFechaHora;
    p_fTests[ 13 ] = TestSCronometro;
    p_fTests[ 14 ] = TestSReloj;
    p_fTests[ 15 ] = TestSPeriodo;
    p_fTests[ 16 ] = TestDeteccion;
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
	freeArrays ( p_p_cTests, p_fTests );
	fflush ( stdout );
	return ( iRes );
}
