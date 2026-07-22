#include "Base.h"

#include "SistemaMemoria.h"



static int TestSisMemoriaTotal01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SisMemoriaTotal 01:\n" );
	if ( SisMemoriaTotal () == 0 )
	{
		printf( "Error caso 1: se esperaba memoria total > 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SisMemoriaFisicaTotal () == 0 )
	{
		printf( "Error caso 2: se esperaba memoria fisica total > 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
#if ( defined ( WIN ) )
	if ( SisMemoriaOcupada () > SisMemoriaTotal () )
	{
		printf( "Error caso 3: la memoria ocupada no debe superar la total\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SisMemoriaFisicaDisponible () > SisMemoriaFisicaTotal () )
	{
		printf( "Error caso 4: la fisica disponible no debe superar la fisica total\n" );
		iRes = BOOL_VAL_FALSO;
	}
#endif
	return ( iRes );
}

static int TestSisMemoriaPorc01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SisMemoriaPorc 01:\n" );
#if ( defined ( WIN ) )
	double dOcupada = SisMemoriaOcupadaPorc ();
	double dDisponible = SisMemoriaDisponiblePorc ();
	if ( ( dOcupada < 0.0 ) || ( dOcupada > 100.0 ) )
	{
		printf( "Error caso 1: porcentaje ocupada fuera de rango: %f\n", dOcupada );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ( dDisponible < 0.0 ) || ( dDisponible > 100.0 ) )
	{
		printf( "Error caso 2: porcentaje disponible fuera de rango: %f\n", dDisponible );
		iRes = BOOL_VAL_FALSO;
	}
#endif
	return ( iRes );
}



int TestSistemaMemoria ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SistemaMemoria]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSisMemoriaTotal01 () == BOOL_VAL_CIERTO ) &&
			( TestSisMemoriaPorc01 () == BOOL_VAL_CIERTO ) )
	{
		printf ( "%sResultado: OK%s\n", ANSI_VERDE, ANSI_RESETEAR );
	}
	else
	{
		printf ( "%sResultado: KO%s\n", ANSI_ROJO, ANSI_RESETEAR );
		iRes = BOOL_VAL_FALSO;
	}
	printf ( "%s[Fin]%s\n", ANSI_AMARILLO, ANSI_RESETEAR );
	return ( iRes );
}
