#include "Base.h"

#include "SistemaProcesos.h"



static int TestSisProcesoActual01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SisProcesoActual 01:\n" );
	if ( SisPID () <= 0 )
	{
		printf( "Error caso 1: se esperaba PID del proceso actual > 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	char * p_cPID = SisPIDCadena ();
	if ( ES_NULO ( p_cPID ) )
	{
		printf( "Error caso 2: se esperaba la cadena de PID no nula\n" );
		iRes = BOOL_VAL_FALSO;
	}
	MemLiberar ( (void **) &p_cPID );
	if ( SisTID () == 0 )
	{
		printf( "Error caso 3: se esperaba TID del hilo actual distinto de 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	char * p_cTID = SisTIDCadena ();
	if ( ES_NULO ( p_cTID ) )
	{
		printf( "Error caso 4: se esperaba la cadena de TID no nula\n" );
		iRes = BOOL_VAL_FALSO;
	}
	MemLiberar ( (void **) &p_cTID );
	return ( iRes );
}

static int TestSisProcesoExiste01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SisProcesoExiste 01:\n" );
#if ( defined ( WIN ) )
	if ( SisExisteProceso ( SisPID () ) != 1 )
	{
		printf( "Error caso 1: el proceso actual deberia existir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SisProcesoEnEjecucion ( SisPID () ) != 1 )
	{
		printf( "Error caso 2: el proceso actual deberia estar en ejecucion\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SisNumProcesos () <= 0 )
	{
		printf( "Error caso 3: se esperaba numero de procesos > 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
#endif
	return ( iRes );
}



int TestSistemaProcesos ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SistemaProcesos]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSisProcesoActual01 () == BOOL_VAL_CIERTO ) &&
			( TestSisProcesoExiste01 () == BOOL_VAL_CIERTO ) )
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
