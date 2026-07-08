#include "Base.h"

#include "Intercambios.h"



static int TestIntercambiarCaracteres01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test IntercambiarCaracteres 01:\n" );
	char cA = 'A';
	char cB = 'B';
	IntercambiarCaracteres ( &cA, &cB );
	if ( ( cA != 'B' ) || ( cB != 'A' ) )
	{
		printf( "Error caso 1: se esperaba A=B y B=A: A=%c B=%c\n", cA, cB );
		iRes = BOOL_VAL_FALSO;
	}
	/* Con puntero nulo no debe modificar nada. */
	IntercambiarCaracteres ( &cA, NULL );
	if ( cA != 'B' )
	{
		printf( "Error caso 2: no se esperaba modificacion: A=%c\n", cA );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestIntercambiarEnteros01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test IntercambiarEnteros 01:\n" );
	int iA = 10;
	int iB = 20;
	IntercambiarEnteros ( &iA, &iB );
	if ( ( iA != 20 ) || ( iB != 10 ) )
	{
		printf( "Error caso 1: se esperaba A=20 y B=10: A=%d B=%d\n", iA, iB );
		iRes = BOOL_VAL_FALSO;
	}
	unsigned int uiA = 1;
	unsigned int uiB = 2;
	IntercambiarEnterosSinSigno ( &uiA, &uiB );
	if ( ( uiA != 2 ) || ( uiB != 1 ) )
	{
		printf( "Error caso 2: se esperaba A=2 y B=1: A=%u B=%u\n", uiA, uiB );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestIntercambiarEnterosLargos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test IntercambiarEnterosLargos 01:\n" );
	long lA = 100L;
	long lB = 200L;
	IntercambiarEnterosLargos ( &lA, &lB );
	if ( ( lA != 200L ) || ( lB != 100L ) )
	{
		printf( "Error caso 1: se esperaba A=200 y B=100: A=%ld B=%ld\n", lA, lB );
		iRes = BOOL_VAL_FALSO;
	}
	unsigned long ulA = 5UL;
	unsigned long ulB = 6UL;
	IntercambiarEnterosLargosSinSigno ( &ulA, &ulB );
	if ( ( ulA != 6UL ) || ( ulB != 5UL ) )
	{
		printf( "Error caso 2: se esperaba A=6 y B=5: A=%lu B=%lu\n", ulA, ulB );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestIntercambiarReales01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test IntercambiarReales 01:\n" );
	float fA = 1.5f;
	float fB = 2.5f;
	IntercambiarReales ( &fA, &fB );
	if ( ( fA != 2.5f ) || ( fB != 1.5f ) )
	{
		printf( "Error caso 1: se esperaba A=2.5 y B=1.5: A=%f B=%f\n", fA, fB );
		iRes = BOOL_VAL_FALSO;
	}
	double dA = 10.25;
	double dB = 20.75;
	IntercambiarRealesDobles ( &dA, &dB );
	if ( ( dA != 20.75 ) || ( dB != 10.25 ) )
	{
		printf( "Error caso 2: se esperaba A=20.75 y B=10.25: A=%f B=%f\n", dA, dB );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}



int TestIntercambios ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test Intercambios]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestIntercambiarCaracteres01 () == BOOL_VAL_CIERTO ) &&
			( TestIntercambiarEnteros01 () == BOOL_VAL_CIERTO ) &&
			( TestIntercambiarEnterosLargos01 () == BOOL_VAL_CIERTO ) &&
			( TestIntercambiarReales01 () == BOOL_VAL_CIERTO ) )
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
