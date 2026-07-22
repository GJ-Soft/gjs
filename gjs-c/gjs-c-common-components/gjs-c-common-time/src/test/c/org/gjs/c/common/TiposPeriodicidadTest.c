#include "Base.h"

#include "TiposPeriodicidad.h"



static int TestTipPeriodValido01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test TipPeriodValido 01:\n" );

	if ( TipPeriodEsValido ( TIP_PERIOD_DIARIO ) != 1 )
	{
		printf( "Error caso 1: DIARIO deberia ser valido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( TipPeriodEsValido ( TIP_PERIOD_SEMANAL ) != 1 )
	{
		printf( "Error caso 2: SEMANAL deberia ser valido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( TipPeriodEsValido ( TIP_PERIOD_MENSUAL ) != 1 )
	{
		printf( "Error caso 3: MENSUAL deberia ser valido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( TipPeriodEsValido ( TIP_PERIOD_ANUAL ) != 1 )
	{
		printf( "Error caso 4: ANUAL deberia ser valido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( TipPeriodEsValido ( TIP_PERIOD_TRIMESTRAL ) != 1 )
	{
		printf( "Error caso 5: TRIMESTRAL deberia ser valido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( TipPeriodEsValido ( TIP_PERIOD_NINGUNO ) != 0 )
	{
		printf( "Error caso 6: NINGUNO no deberia ser valido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( TipPeriodEsValido ( 99 ) != 0 )
	{
		printf( "Error caso 7: 99 no deberia ser valido\n" );
		iRes = BOOL_VAL_FALSO;
	}

	return ( iRes );
}



static int TestTipPeriodEs01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test TipPeriodEs 01:\n" );

	if ( TipPeriodEsDiario ( TIP_PERIOD_DIARIO ) != 1 )
	{
		printf( "Error caso 1: EsDiario de DIARIO deberia dar 1\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( TipPeriodEsSemanal ( TIP_PERIOD_SEMANAL ) != 1 )
	{
		printf( "Error caso 2: EsSemanal de SEMANAL deberia dar 1\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( TipPeriodEsMensual ( TIP_PERIOD_MENSUAL ) != 1 )
	{
		printf( "Error caso 3: EsMensual de MENSUAL deberia dar 1\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( TipPeriodEsAnual ( TIP_PERIOD_ANUAL ) != 1 )
	{
		printf( "Error caso 4: EsAnual de ANUAL deberia dar 1\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( TipPeriodEsTrimestral ( TIP_PERIOD_TRIMESTRAL ) != 1 )
	{
		printf( "Error caso 5: EsTrimestral de TRIMESTRAL deberia dar 1\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* discriminacion cruzada */
	if ( TipPeriodEsDiario ( TIP_PERIOD_SEMANAL ) != 0 )
	{
		printf( "Error caso 6: EsDiario de SEMANAL deberia dar 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( TipPeriodEsAnual ( TIP_PERIOD_MENSUAL ) != 0 )
	{
		printf( "Error caso 7: EsAnual de MENSUAL deberia dar 0\n" );
		iRes = BOOL_VAL_FALSO;
	}

	return ( iRes );
}



int TestTiposPeriodicidad ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test TiposPeriodicidad]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestTipPeriodValido01 () == BOOL_VAL_CIERTO ) &&
			( TestTipPeriodEs01 () == BOOL_VAL_CIERTO ) )
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
