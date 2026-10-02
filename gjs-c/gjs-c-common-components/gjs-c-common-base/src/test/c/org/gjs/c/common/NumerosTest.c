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

static int TestNumDigitosEnteroDobleLargo01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test NumDigitosEnteroDobleLargo 01:\n" );
	int iDigs = NumDigitosEnteroDobleLargo ( (long long) 0 );
	if ( iDigs != 1 )
	{
		printf( "Error caso 1: se esperaba 1: %d\n", iDigs );
		iRes = BOOL_VAL_FALSO;
	}
	iDigs = NumDigitosEnteroDobleLargo ( (long long) 1234567890 );
	if ( iDigs != 10 )
	{
		printf( "Error caso 2: se esperaba 10: %d\n", iDigs );
		iRes = BOOL_VAL_FALSO;
	}
	iDigs = NumDigitosEnteroDobleLargoSinSigno ( (unsigned long long) 100 );
	if ( iDigs != 3 )
	{
		printf( "Error caso 3: se esperaba 3: %d\n", iDigs );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

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



/* Los maximos por tipo. Los valores no son arbitrarios: son los digitos del
   valor mas grande de cada tipo en una maquina de 64 bits, y estan puestos a
   proposito como numeros literales. Si alguien vuelve a truncar el parametro a
   int —que es lo que pasaba hasta el 2026-09-19, y hacia que seis de las ocho
   devolvieran los digitos de -1— estos casos lo cazan. */
static int TestMaxDigitosEntero01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	int iEsperado;

	printf ( "Test MaxDigitos enteros 01:\n" );

	if ( MaxDigitosEntero () != 10 )
	{
		printf ( "Error caso 1: MaxDigitosEntero dio %d, se esperaba 10\n", MaxDigitosEntero () );
		iRes = BOOL_VAL_FALSO;
	}
	if ( MaxDigitosEnteroSinSigno () != 10 )
	{
		printf ( "Error caso 2: MaxDigitosEnteroSinSigno dio %d, se esperaba 10\n",
				 MaxDigitosEnteroSinSigno () );
		iRes = BOOL_VAL_FALSO;
	}
	/* OJO: long NO mide lo mismo en todas partes. Cygwin y Linux son LP64 y lo
	   hacen de 8 bytes ( 19 y 20 digitos ); Windows es LLP64 y lo deja en 4,
	   los mismos que int ( 10 y 10 ). Medido el 2026-09-19. Por eso se espera
	   segun el tamano del tipo y no un numero fijo: puesto a mano, este caso
	   fallaba en Windows. */
	iEsperado = ( sizeof ( long ) >= 8 ) ? 19 : 10;
	if ( MaxDigitosEnteroLargo () != iEsperado )
	{
		printf ( "Error caso 3: MaxDigitosEnteroLargo dio %d, se esperaba %d\n",
				 MaxDigitosEnteroLargo (), iEsperado );
		iRes = BOOL_VAL_FALSO;
	}
	iEsperado = ( sizeof ( unsigned long ) >= 8 ) ? 20 : 10;
	if ( MaxDigitosEnteroLargoSinSigno () != iEsperado )
	{
		printf ( "Error caso 4: MaxDigitosEnteroLargoSinSigno dio %d, se esperaba %d\n",
				 MaxDigitosEnteroLargoSinSigno (), iEsperado );
		iRes = BOOL_VAL_FALSO;
	}
	if ( MaxDigitosEnteroDobleLargo () != 19 )
	{
		printf ( "Error caso 5: MaxDigitosEnteroDobleLargo dio %d, se esperaba 19\n",
				 MaxDigitosEnteroDobleLargo () );
		iRes = BOOL_VAL_FALSO;
	}
	if ( MaxDigitosEnteroDobleLargoSinSigno () != 20 )
	{
		printf ( "Error caso 6: MaxDigitosEnteroDobleLargoSinSigno dio %d, se esperaba 20\n",
				 MaxDigitosEnteroDobleLargoSinSigno () );
		iRes = BOOL_VAL_FALSO;
	}
	/* Sin signo nunca puede dar menos que con signo: es el mismo ancho sin
	   gastar un bit en el signo. */
	if ( MaxDigitosEnteroLargoSinSigno () < MaxDigitosEnteroLargo () )
	{
		printf ( "Error caso 7: el largo sin signo no puede tener menos digitos que el largo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

/* Los dos "maximos de digitos" de la coma flotante. Lo que este caso protege
   no son los numeros, es la DIFERENCIA: Reproducir tiene que ser mayor que
   Significativos, porque hacen falta mas digitos para reconstruir el binario
   que los que el usuario puede dar por buenos. Si alguien los iguala, se
   pierden datos al serializar y no se entera nadie. */
static int TestMaxDigitosReal01 ()
{
	int iRes = BOOL_VAL_CIERTO;

	printf ( "Test MaxDigitos reales 01:\n" );

	if ( MaxDigitosSignificativosReal () != 6 )
	{
		printf ( "Error caso 1: MaxDigitosSignificativosReal dio %d, se esperaba 6\n",
				 MaxDigitosSignificativosReal () );
		iRes = BOOL_VAL_FALSO;
	}
	if ( MaxDigitosSignificativosRealDoble () != 15 )
	{
		printf ( "Error caso 2: MaxDigitosSignificativosRealDoble dio %d, se esperaba 15\n",
				 MaxDigitosSignificativosRealDoble () );
		iRes = BOOL_VAL_FALSO;
	}
	if ( MaxDigitosReproducirReal () != 9 )
	{
		printf ( "Error caso 3: MaxDigitosReproducirReal dio %d, se esperaba 9\n",
				 MaxDigitosReproducirReal () );
		iRes = BOOL_VAL_FALSO;
	}
	if ( MaxDigitosReproducirRealDoble () != 17 )
	{
		printf ( "Error caso 4: MaxDigitosReproducirRealDoble dio %d, se esperaba 17\n",
				 MaxDigitosReproducirRealDoble () );
		iRes = BOOL_VAL_FALSO;
	}
	if ( MaxDigitosReproducirReal () <= MaxDigitosSignificativosReal () )
	{
		printf ( "Error caso 5: Reproducir tiene que ser MAYOR que Significativos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( MaxDigitosReproducirRealDoble () <= MaxDigitosSignificativosRealDoble () )
	{
		printf ( "Error caso 6: Reproducir tiene que ser MAYOR que Significativos ( doble )\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

/* Y la comprobacion que de verdad justifica que existan las dos: un valor
   escrito con los digitos de Reproducir vuelve a ser el mismo; con los de
   Significativos, no tiene por que. Se usa 0.1, que no es representable en
   binario y por eso lo destapa. */
static int TestMaxDigitosReal02 ()
{
	int		iRes = BOOL_VAL_CIERTO;
	char	cBuf [ 64 ];
	float	fOrig;
	float	fVuelta;

	printf ( "Test MaxDigitos reales 02 ( ida y vuelta ):\n" );

	fOrig = 0.1f;
	snprintf ( cBuf, sizeof ( cBuf ), "%.*g", MaxDigitosReproducirReal (), ( double ) fOrig );
	fVuelta = (float) atof ( cBuf );
	if ( fVuelta != fOrig )
	{
		printf ( "Error caso 1: con %d digitos [%s] no vuelve igual\n",
				 MaxDigitosReproducirReal (), cBuf );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

/* El exponente maximo. Lo que fija el caso es que sea el decimal y no el
   binario: los de float.h son FLT_MAX_10_EXP = 38 y DBL_MAX_10_EXP = 308,
   frente a los binarios FLT_MAX_EXP = 128 y DBL_MAX_EXP = 1024. */
static int TestMaxExponente01 ()
{
	int iRes = BOOL_VAL_CIERTO;

	printf ( "Test MaxExponente 01:\n" );

	if ( MaxExponenteReal () != 38 )
	{
		printf ( "Error caso 1: MaxExponenteReal dio %d, se esperaba 38\n", MaxExponenteReal () );
		iRes = BOOL_VAL_FALSO;
	}
	if ( MaxExponenteRealDoble () != 308 )
	{
		printf ( "Error caso 2: MaxExponenteRealDoble dio %d, se esperaba 308\n",
				 MaxExponenteRealDoble () );
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
			( TestNumDigitosEnteroDobleLargo01 () == BOOL_VAL_CIERTO ) &&
			( TestNumParteEnteraReal01 () == BOOL_VAL_CIERTO ) &&
			( TestNumParteDecimalReal01 () == BOOL_VAL_CIERTO ) &&
			( TestNumParteRealDoble01 () == BOOL_VAL_CIERTO ) &&
			( TestNumDigitosReal01 () == BOOL_VAL_CIERTO ) &&
			( TestMaxDigitosEntero01 () == BOOL_VAL_CIERTO ) &&
			( TestMaxDigitosReal01 () == BOOL_VAL_CIERTO ) &&
			( TestMaxDigitosReal02 () == BOOL_VAL_CIERTO ) &&
			( TestMaxExponente01 () == BOOL_VAL_CIERTO ) )
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
