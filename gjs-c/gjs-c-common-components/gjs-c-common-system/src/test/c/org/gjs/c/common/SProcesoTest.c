#include "Base.h"

#include "SProceso.h"
#include "SistemaProcesos.h"



static int TestSPrcCicloVida01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SPrcCicloVida 01:\n" );
	SProceso * p_prcObj = SPrcCrear ();
	if ( ES_NULO ( p_prcObj ) )
	{
		printf( "Error caso 0: no se pudo crear el proceso\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SPrcPID ( p_prcObj ) <= 0 )
		{
			printf( "Error caso 1: se esperaba un PID > 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SPrcPID ( p_prcObj ) != SisPID () )
		{
			printf( "Error caso 2: el PID del objeto debe coincidir con el del proceso actual\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	SPrcDestruir ( &p_prcObj );
	return ( iRes );
}

static int TestSPrcNulo01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SPrcNulo 01:\n" );
	if ( SPrcPID ( NULL ) != -1 )
	{
		printf( "Error caso 1: se esperaba -1 en el PID de un proceso nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}



int TestSProceso ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SProceso]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSPrcCicloVida01 () == BOOL_VAL_CIERTO ) &&
			( TestSPrcNulo01 () == BOOL_VAL_CIERTO ) )
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
