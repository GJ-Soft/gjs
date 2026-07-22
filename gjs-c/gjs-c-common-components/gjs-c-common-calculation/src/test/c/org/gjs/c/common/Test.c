#include "Base.h"



#define NUM_TESTS        14

extern int TestAngulos ();
extern int TestRadianes ();
extern int TestGradianes ();
extern int TestEpsilon ();
extern int TestCalculoOperaciones ();
extern int TestSIntervalo ();
extern int TestSFormaLineal ();
extern int TestSExtremoDominioReal ();
extern int TestSFuncionReal ();
extern int TestSListaRealesDobles ();
extern int TestSVectorRealesDobles ();
extern int TestSPilaRealesDobles ();
extern int TestSSecuenciaRealesDobles ();
extern int TestSTablaRealesDobles ();


char ** testArrayInit ()
{
    char ** p_p_cTests = (char **) MemReservar ( NUM_TESTS * sizeof( char *));
    p_p_cTests[ 0 ] = CadDuplicar ( "AngulosTest" );
    p_p_cTests[ 1 ] = CadDuplicar ( "RadianesTest" );
    p_p_cTests[ 2 ] = CadDuplicar ( "GradianesTest" );
    p_p_cTests[ 3 ] = CadDuplicar ( "EpsilonTest" );
    p_p_cTests[ 4 ] = CadDuplicar ( "CalculoOperacionesTest" );
    p_p_cTests[ 5 ] = CadDuplicar ( "SIntervaloTest" );
    p_p_cTests[ 6 ] = CadDuplicar ( "SFormaLinealTest" );
    p_p_cTests[ 7 ] = CadDuplicar ( "SExtremoDominioRealTest" );
    p_p_cTests[ 8 ] = CadDuplicar ( "SFuncionRealTest" );
    p_p_cTests[ 9 ] = CadDuplicar ( "SListaRealesDoblesTest" );
    p_p_cTests[ 10 ] = CadDuplicar ( "SVectorRealesDoblesTest" );
    p_p_cTests[ 11 ] = CadDuplicar ( "SPilaRealesDoblesTest" );
    p_p_cTests[ 12 ] = CadDuplicar ( "SSecuenciaRealesDoblesTest" );
    p_p_cTests[ 13 ] = CadDuplicar ( "STablaRealesDoblesTest" );
    return p_p_cTests;
}

PFUNINTV * functionArrayInit ()
{
    PFUNINTV* p_fTests = (PFUNINTV *) MemReservar ( NUM_TESTS * sizeof( PFUNINTV ));
    p_fTests[ 0 ] = TestAngulos;
    p_fTests[ 1 ] = TestRadianes;
    p_fTests[ 2 ] = TestGradianes;
    p_fTests[ 3 ] = TestEpsilon;
    p_fTests[ 4 ] = TestCalculoOperaciones;
    p_fTests[ 5 ] = TestSIntervalo;
    p_fTests[ 6 ] = TestSFormaLineal;
    p_fTests[ 7 ] = TestSExtremoDominioReal;
    p_fTests[ 8 ] = TestSFuncionReal;
    p_fTests[ 9 ] = TestSListaRealesDobles;
    p_fTests[ 10 ] = TestSVectorRealesDobles;
    p_fTests[ 11 ] = TestSPilaRealesDobles;
    p_fTests[ 12 ] = TestSSecuenciaRealesDobles;
    p_fTests[ 13 ] = TestSTablaRealesDobles;
    return p_fTests;
}

void freeArrays ( char ** p_p_cTests, PFUNINTV* p_fTests )
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

	printf ( "%s[Inicio de los test]%s\n", ANSI_AZUL, ANSI_RESETEAR );
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
			printf ( "%sTest [%s] no encontrado.%s\n", ANSI_ROJO, p_cTest, ANSI_RESETEAR );
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
	printf ( "%s[Fin de los test]%s\n", ANSI_AZUL, ANSI_RESETEAR );
	if ( iRes == 0 )
	{
		printf ("%sResultado global: OK%s\n", ANSI_VERDE, ANSI_RESETEAR );
	}
	else
	{
		printf ("%sResultado global: KO%s\n", ANSI_ROJO, ANSI_RESETEAR );
	}
	fflush ( stdout );
	return ( iRes );
}
