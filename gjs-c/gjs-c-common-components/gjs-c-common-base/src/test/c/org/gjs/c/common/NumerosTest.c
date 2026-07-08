#include "Base.h"

#include "Numeros.h"



static int TestNumDigitosEntero01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test NumDigitosEntero 01:\n" );
	int iDigs = NumDigitosEntero ( 0 );
	if ( iDigs != 1 )
	{
		printf( "Error caso 1: se esperaba 1: %d\n", iDigs );
		iRes = BOOL_VAL_FALSO;
	}
	iDigs = NumDigitosEntero ( 5 );
	if ( iDigs != 1 )
	{
		printf( "Error caso 2: se esperaba 1: %d\n", iDigs );
		iRes = BOOL_VAL_FALSO;
	}
	iDigs = NumDigitosEntero ( 12345 );
	if ( iDigs != 5 )
	{
		printf( "Error caso 3: se esperaba 5: %d\n", iDigs );
		iRes = BOOL_VAL_FALSO;
	}
	iDigs = NumDigitosEntero ( -12345 );
	if ( iDigs != 5 )
	{
		printf( "Error caso 4: se esperaba 5: %d\n", iDigs );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestNumDigitosEnteroLargo01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test NumDigitosEnteroLargo 01:\n" );
	int iDigs = NumDigitosEnteroLargo ( 0L );
	if ( iDigs != 1 )
	{
		printf( "Error caso 1: se esperaba 1: %d\n", iDigs );
		iRes = BOOL_VAL_FALSO;
	}
	iDigs = NumDigitosEnteroLargo ( 1000L );
	if ( iDigs != 4 )
	{
		printf( "Error caso 2: se esperaba 4: %d\n", iDigs );
		iRes = BOOL_VAL_FALSO;
	}
	iDigs = NumDigitosEnteroLargo ( -100L );
	if ( iDigs != 3 )
	{
		printf( "Error caso 3: se esperaba 3: %d\n", iDigs );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestNumDigitosEnteroSinSigno01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test NumDigitosEnteroSinSigno 01:\n" );
	int iDigs = NumDigitosEnteroSinSigno ( 0 );
	if ( iDigs != 1 )
	{
		printf( "Error caso 1: se esperaba 1: %d\n", iDigs );
		iRes = BOOL_VAL_FALSO;
	}
	iDigs = NumDigitosEnteroSinSigno ( 987654 );
	if ( iDigs != 6 )
	{
		printf( "Error caso 2: se esperaba 6: %d\n", iDigs );
		iRes = BOOL_VAL_FALSO;
	}
	iDigs = NumDigitosEnteroLargoSinSigno ( 10UL );
	if ( iDigs != 2 )
	{
		printf( "Error caso 3: se esperaba 2: %d\n", iDigs );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

#if ( defined ( LLONG ) )
static int TestNumDigitosEnteroDobleLargo01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test NumDigitosEnteroDobleLargo 01:\n" );
	int iDigs = NumDigitosEnteroDobleLargo ( (llong) 0 );
	if ( iDigs != 1 )
	{
		printf( "Error caso 1: se esperaba 1: %d\n", iDigs );
		iRes = BOOL_VAL_FALSO;
	}
	iDigs = NumDigitosEnteroDobleLargo ( (llong) 1234567890 );
	if ( iDigs != 10 )
	{
		printf( "Error caso 2: se esperaba 10: %d\n", iDigs );
		iRes = BOOL_VAL_FALSO;
	}
	iDigs = NumDigitosEnteroDobleLargoSinSigno ( (ullong) 100 );
	if ( iDigs != 3 )
	{
		printf( "Error caso 3: se esperaba 3: %d\n", iDigs );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}
#endif

static int TestNumParteEnteraReal01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test NumParteEnteraReal 01:\n" );
	float fVal = NumParteEnteraReal ( 3.75f );
	if ( fVal != 3.0f )
	{
		printf( "Error caso 1: se esperaba 3.0: %f\n", fVal );
		iRes = BOOL_VAL_FALSO;
	}
	fVal = NumParteEnteraReal ( -3.75f );
	if ( fVal != -3.0f )
	{
		printf( "Error caso 2: se esperaba -3.0: %f\n", fVal );
		iRes = BOOL_VAL_FALSO;
	}
	fVal = NumParteEnteraReal ( 0.0f );
	if ( fVal != 0.0f )
	{
		printf( "Error caso 3: se esperaba 0.0: %f\n", fVal );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestNumParteDecimalReal01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test NumParteDecimalReal 01:\n" );
	float fVal = NumParteDecimalReal ( 3.75f );
	if ( fVal != 0.75f )
	{
		printf( "Error caso 1: se esperaba 0.75: %f\n", fVal );
		iRes = BOOL_VAL_FALSO;
	}
	fVal = NumParteDecimalReal ( -3.75f );
	if ( fVal != -0.75f )
	{
		printf( "Error caso 2: se esperaba -0.75: %f\n", fVal );
		iRes = BOOL_VAL_FALSO;
	}
	fVal = NumParteDecimalReal ( 5.0f );
	if ( fVal != 0.0f )
	{
		printf( "Error caso 3: se esperaba 0.0: %f\n", fVal );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestNumParteRealDoble01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test NumParteRealDoble 01:\n" );
	double dVal = NumParteEnteraRealDoble ( 12.25 );
	if ( dVal != 12.0 )
	{
		printf( "Error caso 1: se esperaba 12.0: %f\n", dVal );
		iRes = BOOL_VAL_FALSO;
	}
	dVal = NumParteDecimalRealDoble ( 12.25 );
	if ( dVal != 0.25 )
	{
		printf( "Error caso 2: se esperaba 0.25: %f\n", dVal );
		iRes = BOOL_VAL_FALSO;
	}
	dVal = NumParteEnteraRealDoble ( -12.25 );
	if ( dVal != -12.0 )
	{
		printf( "Error caso 3: se esperaba -12.0: %f\n", dVal );
		iRes = BOOL_VAL_FALSO;
	}
	dVal = NumParteDecimalRealDoble ( -12.25 );
	if ( dVal != -0.25 )
	{
		printf( "Error caso 4: se esperaba -0.25: %f\n", dVal );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestNumDigitosReal01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test NumDigitosReal 01:\n" );
	int iDigs = NumDigitosReal ( 0.0f );
	if ( iDigs != 1 )
	{
		printf( "Error caso 1: se esperaba 1: %d\n", iDigs );
		iRes = BOOL_VAL_FALSO;
	}
	iDigs = NumDigitosRealDoble ( 0.0 );
	if ( iDigs != 1 )
	{
		printf( "Error caso 2: se esperaba 1: %d\n", iDigs );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}



int TestNumeros ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test Numeros]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestNumDigitosEntero01 () == BOOL_VAL_CIERTO ) &&
			( TestNumDigitosEnteroLargo01 () == BOOL_VAL_CIERTO ) &&
			( TestNumDigitosEnteroSinSigno01 () == BOOL_VAL_CIERTO ) &&
#if ( defined ( LLONG ) )
			( TestNumDigitosEnteroDobleLargo01 () == BOOL_VAL_CIERTO ) &&
#endif
			( TestNumParteEnteraReal01 () == BOOL_VAL_CIERTO ) &&
			( TestNumParteDecimalReal01 () == BOOL_VAL_CIERTO ) &&
			( TestNumParteRealDoble01 () == BOOL_VAL_CIERTO ) &&
			( TestNumDigitosReal01 () == BOOL_VAL_CIERTO ) )
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
