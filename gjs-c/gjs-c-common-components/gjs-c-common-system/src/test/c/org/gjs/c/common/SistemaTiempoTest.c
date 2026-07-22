#include "Base.h"

#include "SistemaTiempo.h"



static int TestSisCiclosCPU01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SisCiclosCPU 01:\n" );
	uint64_t ui64Ini = SisCiclosCPU ();
	SisEsperar ( 2 );
	uint64_t ui64Fin = SisCiclosCPU ();
	if ( ui64Fin <= ui64Ini )
	{
		printf( "Error caso 1: el contador de ciclos debe avanzar tras la espera\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSisEsperar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SisEsperar 01:\n" );
	/* Una espera con valor no positivo no debe hacer nada ni fallar. */
	SisEsperar ( 0 );
	SisEsperar ( -5 );
	uint64_t ui64Ini = SisCiclosCPU ();
	SisEsperar ( 5 );
	uint64_t ui64Fin = SisCiclosCPU ();
	if ( ui64Fin <= ui64Ini )
	{
		printf( "Error caso 1: se esperaba avance de ciclos tras esperar 5 ms\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}



int TestSistemaTiempo ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SistemaTiempo]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSisCiclosCPU01 () == BOOL_VAL_CIERTO ) &&
			( TestSisEsperar01 () == BOOL_VAL_CIERTO ) )
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
