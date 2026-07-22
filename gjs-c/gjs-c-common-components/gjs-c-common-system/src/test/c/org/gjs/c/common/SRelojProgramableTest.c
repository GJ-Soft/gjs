#include "Base.h"

#include "SRelojProgramable.h"



static int TestSRljPrgCicloVida01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SRljPrgCicloVida 01:\n" );
	SRelojProgramable * p_rljprgObj = SRljPrgCrear ( 0 );
	if ( ES_NULO ( p_rljprgObj ) )
	{
		printf( "Error caso 0: no se pudo crear el reloj programable\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		/* Estado inicial: sin alarma activada. No se activa la alarma para no
		   lanzar el hilo de vigilancia. */
		if ( SRljPrgAlarmaActivada ( p_rljprgObj ) != 0 )
		{
			printf( "Error caso 1: un reloj recien creado no debe tener alarma activada\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SRljPrgHoraAlarma ( p_rljprgObj ) != -1 )
		{
			printf( "Error caso 2: la hora de alarma inicial deberia ser -1: %ld\n", SRljPrgHoraAlarma ( p_rljprgObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( SRljPrgProcedimientoAlarma ( p_rljprgObj ) ) )
		{
			printf( "Error caso 3: no deberia haber procedimiento de alarma inicial\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	SRljPrgDestruir ( &p_rljprgObj );
	return ( iRes );
}

static int TestSRljPrgNulo01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SRljPrgNulo 01:\n" );
	if ( SRljPrgAlarmaActivada ( NULL ) != 0 )
	{
		printf( "Error caso 1: un reloj nulo no debe tener alarma activada\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SRljPrgHoraAlarma ( NULL ) != 0 )
	{
		printf( "Error caso 2: se esperaba 0 en la hora de alarma de un reloj nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( SRljPrgProcedimientoAlarma ( NULL ) ) )
	{
		printf( "Error caso 3: se esperaba procedimiento nulo para reloj nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}



int TestSRelojProgramable ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SRelojProgramable]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSRljPrgCicloVida01 () == BOOL_VAL_CIERTO ) &&
			( TestSRljPrgNulo01 () == BOOL_VAL_CIERTO ) )
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
