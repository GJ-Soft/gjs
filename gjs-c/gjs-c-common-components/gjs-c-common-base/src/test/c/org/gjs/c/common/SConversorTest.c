#include "Base.h"

#include "SConversor.h"



static int TestSConversor01 ()
{
	printf( "Test SConversor 01:\n" );
	int iRes = BOOL_VAL_CIERTO;
	SConversor * p_obj1 = SConvCrearDef ();
	if ( BOOL_ES_CIERTO ( SConvConversionValida ( p_obj1 ) ) )
	{
		printf( "Error caso 1\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SConvDestruir ( &p_obj1 );
	if ( p_obj1 != NULL )
	{
		printf( "Error al liberar\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSConvEntero01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SConvEntero 01:\n" );
	/* Un entero positivo produce una conversion valida. */
	SConversor * p_obj = SConvCrearEntero ( 1234 );
	if ( SConvConversionValida ( p_obj ) != 1 )
	{
		printf( "Error caso 1: se esperaba conversion valida\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SConvEntero ( p_obj ) != 1234 )
	{
		printf( "Error caso 2: se esperaba 1234: %d\n", SConvEntero ( p_obj ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SConvEnteroLargo ( p_obj ) != 1234L )
	{
		printf( "Error caso 3: se esperaba 1234: %ld\n", SConvEnteroLargo ( p_obj ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_NULO ( SConvCadena ( p_obj ) ) || ( strcmp ( SConvCadena ( p_obj ), "1234" ) != 0 ) )
	{
		printf( "Error caso 4: se esperaba \"1234\": [%s]\n",
				ES_VALIDO ( SConvCadena ( p_obj ) ) ? SConvCadena ( p_obj ) : "(nulo)" );
		iRes = BOOL_VAL_FALSO;
	}
	SConvDestruir ( &p_obj );

	/* Un entero negativo no da conversion valida (no cabe en los tipos sin signo). */
	SConversor * p_objNeg = SConvCrearEntero ( -7 );
	if ( SConvConversionValida ( p_objNeg ) != 0 )
	{
		printf( "Error caso 5: se esperaba conversion no valida para negativo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SConvEntero ( p_objNeg ) != -7 )
	{
		printf( "Error caso 6: se esperaba -7: %d\n", SConvEntero ( p_objNeg ) );
		iRes = BOOL_VAL_FALSO;
	}
	SConvDestruir ( &p_objNeg );

	/* Sobre un puntero nulo devuelve 0 sin fallar. */
	if ( SConvEntero ( NULL ) != 0 )
	{
		printf( "Error caso 7: se esperaba 0 para puntero nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSConvReal01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SConvReal 01:\n" );
	SConversor * p_obj = SConvCrearReal ( 2.5f );
	if ( SConvReal ( p_obj ) != 2.5f )
	{
		printf( "Error caso 1: se esperaba 2.5: %f\n", SConvReal ( p_obj ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SConvRealDoble ( p_obj ) != 2.5 )
	{
		printf( "Error caso 2: se esperaba 2.5: %f\n", SConvRealDoble ( p_obj ) );
		iRes = BOOL_VAL_FALSO;
	}
	SConvDestruir ( &p_obj );
	return ( iRes );
}

static int TestSConvCadena01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SConvCadena 01:\n" );
	/* Una cadena numerica se convierte a entero. */
	SConversor * p_obj = SConvCrearCadena ( "255" );
	if ( SConvEsCadenaNumerica ( p_obj ) != 1 )
	{
		printf( "Error caso 1: se esperaba cadena numerica\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SConvEsCadenaNumericaEntera ( p_obj ) != 1 )
	{
		printf( "Error caso 2: se esperaba cadena numerica entera\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SConvEntero ( p_obj ) != 255 )
	{
		printf( "Error caso 3: se esperaba 255: %d\n", SConvEntero ( p_obj ) );
		iRes = BOOL_VAL_FALSO;
	}
	SConvDestruir ( &p_obj );

	/* Una cadena no numerica no da conversion valida. */
	SConversor * p_objNo = SConvCrearCadena ( "hola" );
	if ( SConvEsCadenaNumerica ( p_objNo ) != 0 )
	{
		printf( "Error caso 4: no se esperaba cadena numerica\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SConvConversionValida ( p_objNo ) != 0 )
	{
		printf( "Error caso 5: se esperaba conversion no valida\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SConvDestruir ( &p_objNo );
	return ( iRes );
}

static int TestSConvEstablecerValor01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SConvEstablecerValor 01:\n" );
	SConversor * p_obj = SConvCrearDef ();
	SConvEstablecerValorEntero ( p_obj, 42 );
	if ( SConvEntero ( p_obj ) != 42 )
	{
		printf( "Error caso 1: se esperaba 42: %d\n", SConvEntero ( p_obj ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SConvConversionValida ( p_obj ) != 1 )
	{
		printf( "Error caso 2: se esperaba conversion valida\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* Se reutiliza el mismo objeto con un valor nuevo. */
	SConvEstablecerValorEntero ( p_obj, 100 );
	if ( SConvEntero ( p_obj ) != 100 )
	{
		printf( "Error caso 3: se esperaba 100: %d\n", SConvEntero ( p_obj ) );
		iRes = BOOL_VAL_FALSO;
	}
	SConvDestruir ( &p_obj );
	return ( iRes );
}



int TestSConversor ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SConversor]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSConversor01 () == BOOL_VAL_CIERTO ) &&
			( TestSConvEntero01 () == BOOL_VAL_CIERTO ) &&
			( TestSConvReal01 () == BOOL_VAL_CIERTO ) &&
			( TestSConvCadena01 () == BOOL_VAL_CIERTO ) &&
			( TestSConvEstablecerValor01 () == BOOL_VAL_CIERTO ) )
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
