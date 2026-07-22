#include "Base.h"

#include "SCadena.h"



static int TestSCadCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCadCrear 01:\n" );

	SCadena * p_cadObj = SCadCrear ( 20 );
	if ( ES_NULO ( p_cadObj ) )
	{
		printf( "Error caso 1: no se esperaba nulo al crear\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		/* Una cadena recien creada es valida y esta vacia. */
		if ( SCadEsValida ( p_cadObj ) != 1 )
		{
			printf( "Error caso 2: la cadena recien creada deberia ser valida\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCadEstaVacia ( p_cadObj ) != 1 )
		{
			printf( "Error caso 3: la cadena recien creada deberia estar vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCadLongitud ( p_cadObj ) != 0 )
		{
			printf( "Error caso 4: la longitud inicial deberia ser 0: %d\n", SCadLongitud ( p_cadObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCadMaxTam ( p_cadObj ) != 20 )
		{
			printf( "Error caso 5: el tamano maximo deberia ser 20: %d\n", SCadMaxTam ( p_cadObj ) );
			iRes = BOOL_VAL_FALSO;
		}
	}
	SCadDestruir ( &p_cadObj );

	if ( ES_VALIDO ( p_cadObj ) )
	{
		printf( "Error caso 6: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* Crear con longitud no positiva devuelve nulo. */
	SCadena * p_cadNula = SCadCrear ( 0 );
	if ( ES_VALIDO ( p_cadNula ) )
	{
		printf( "Error caso 7: crear con longitud 0 deberia devolver nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SCadDestruir ( &p_cadNula );
	return ( iRes );
}

static int TestSCadGenerar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCadGenerar 01:\n" );

	SCadena * p_cadObj = SCadGenerar ( "Hola" );
	if ( ES_VALIDO ( p_cadObj ) )
	{
		if ( SCadEstaVacia ( p_cadObj ) != 0 )
		{
			printf( "Error caso 1: la cadena generada no deberia estar vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCadLongitud ( p_cadObj ) != 4 )
		{
			printf( "Error caso 2: la longitud deberia ser 4: %d\n", SCadLongitud ( p_cadObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCadEsIgualLiteral ( p_cadObj, "Hola" ) != 1 )
		{
			printf( "Error caso 3: el valor deberia ser \"Hola\": [%s]\n", SCadValor ( p_cadObj ) );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo generar la cadena\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SCadDestruir ( &p_cadObj );
	return ( iRes );
}

static int TestSCadCopiarConcatenar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCadCopiarConcatenar 01:\n" );

	SCadena * p_cadObj = SCadCrear ( 30 );
	if ( ES_VALIDO ( p_cadObj ) )
	{
		if ( SCadCopiarLiteral ( p_cadObj, "Hola" ) != 1 )
		{
			printf( "Error caso 1: se esperaba resultado 1 al copiar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCadConcatenarLiteral ( p_cadObj, " mundo" ) != 1 )
		{
			printf( "Error caso 2: se esperaba resultado 1 al concatenar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCadEsIgualLiteral ( p_cadObj, "Hola mundo" ) != 1 )
		{
			printf( "Error caso 3: se esperaba \"Hola mundo\": [%s]\n", SCadValor ( p_cadObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCadLongitud ( p_cadObj ) != 10 )
		{
			printf( "Error caso 4: la longitud deberia ser 10: %d\n", SCadLongitud ( p_cadObj ) );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la cadena\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SCadDestruir ( &p_cadObj );
	return ( iRes );
}

static int TestSCadComparaciones01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCadComparaciones 01:\n" );

	SCadena * p_cadA = SCadGenerar ( "abc" );
	SCadena * p_cadB = SCadGenerar ( "abd" );
	if ( ES_VALIDO ( p_cadA ) && ES_VALIDO ( p_cadB ) )
	{
		if ( SCadEsMenor ( p_cadA, p_cadB ) != 1 )
		{
			printf( "Error caso 1: \"abc\" deberia ser menor que \"abd\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCadEsMayor ( p_cadB, p_cadA ) != 1 )
		{
			printf( "Error caso 2: \"abd\" deberia ser mayor que \"abc\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCadEsIgual ( p_cadA, p_cadB ) != 0 )
		{
			printf( "Error caso 3: \"abc\" y \"abd\" no deberian ser iguales\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Distincion de mayusculas activa por defecto. */
		if ( SCadEsIgualLiteral ( p_cadA, "ABC" ) != 0 )
		{
			printf( "Error caso 4: con distincion activa \"abc\" no es igual a \"ABC\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron generar las cadenas\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SCadDestruir ( &p_cadA );
	SCadDestruir ( &p_cadB );
	return ( iRes );
}

static int TestSCadEmpiezaAcaba01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCadEmpiezaAcaba 01:\n" );

	SCadena * p_cadObj = SCadGenerar ( "Hola mundo" );
	if ( ES_VALIDO ( p_cadObj ) )
	{
		if ( SCadEmpiezaPorLiteral ( p_cadObj, "Hola" ) != 1 )
		{
			printf( "Error caso 1: deberia empezar por \"Hola\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCadAcabaPorLiteral ( p_cadObj, "mundo" ) != 1 )
		{
			printf( "Error caso 2: deberia acabar por \"mundo\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCadEmpiezaPorLiteral ( p_cadObj, "mundo" ) != 0 )
		{
			printf( "Error caso 3: no deberia empezar por \"mundo\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo generar la cadena\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SCadDestruir ( &p_cadObj );
	return ( iRes );
}

static int TestSCadTransformar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCadTransformar 01:\n" );

	SCadena * p_cadObj = SCadGenerar ( "abc" );
	if ( ES_VALIDO ( p_cadObj ) )
	{
		if ( SCadInvertir ( p_cadObj ) != 1 )
		{
			printf( "Error caso 1: se esperaba resultado 1 al invertir\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCadEsIgualLiteral ( p_cadObj, "cba" ) != 1 )
		{
			printf( "Error caso 2: se esperaba \"cba\": [%s]\n", SCadValor ( p_cadObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		SCadConvertirAMayusculas ( p_cadObj );
		if ( SCadEsIgualLiteral ( p_cadObj, "CBA" ) != 1 )
		{
			printf( "Error caso 3: se esperaba \"CBA\": [%s]\n", SCadValor ( p_cadObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		SCadConvertirAMinusculas ( p_cadObj );
		if ( SCadEsIgualLiteral ( p_cadObj, "cba" ) != 1 )
		{
			printf( "Error caso 4: se esperaba \"cba\": [%s]\n", SCadValor ( p_cadObj ) );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo generar la cadena\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SCadDestruir ( &p_cadObj );
	return ( iRes );
}

static int TestSCadCaracter01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCadCaracter 01:\n" );

	SCadena * p_cadObj = SCadGenerar ( "Hola" );
	if ( ES_VALIDO ( p_cadObj ) )
	{
		if ( SCadCaracter ( p_cadObj, 0 ) != 'H' )
		{
			printf( "Error caso 1: se esperaba 'H': %c\n", SCadCaracter ( p_cadObj, 0 ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCadEstablecerCaracter ( p_cadObj, 0, 'J' ) != 1 )
		{
			printf( "Error caso 2: se esperaba resultado 1 al establecer el caracter\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCadEsIgualLiteral ( p_cadObj, "Jola" ) != 1 )
		{
			printf( "Error caso 3: se esperaba \"Jola\": [%s]\n", SCadValor ( p_cadObj ) );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo generar la cadena\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SCadDestruir ( &p_cadObj );

	/* Comportamiento defensivo con entrada nula. */
	if ( SCadLongitud ( NULL ) != 0 )
	{
		printf( "Error caso 4: la longitud de una cadena nula deberia ser 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SCadEsValida ( NULL ) != 0 )
	{
		printf( "Error caso 5: una cadena nula no deberia ser valida\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}



static int TestSCadGenerarConFormato01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCadGenerarConFormato 01:\n" );

	/* Varios argumentos de distinto tipo: si la lista de argumentos se
	   pierde por el camino, el resultado no coincide con lo esperado. */
	SCadena * p_cadObj = SCadGenerarConFormato ( "%d-%s-%d", 42, "abc", 7 );
	if ( ES_VALIDO ( p_cadObj ) )
	{
		if ( SCadEsIgualLiteral ( p_cadObj, "42-abc-7" ) != 1 )
		{
			printf( "Error caso 1: se esperaba \"42-abc-7\": [%s]\n", SCadValor ( p_cadObj ) );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo generar la cadena con formato\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SCadDestruir ( &p_cadObj );

	/* Un unico argumento tipo cadena. */
	SCadena * p_cadUno = SCadGenerarConFormato ( "Hola %s", "mundo" );
	if ( ES_VALIDO ( p_cadUno ) )
	{
		if ( SCadEsIgualLiteral ( p_cadUno, "Hola mundo" ) != 1 )
		{
			printf( "Error caso 2: se esperaba \"Hola mundo\": [%s]\n", SCadValor ( p_cadUno ) );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 3: no se pudo generar la cadena con un argumento\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SCadDestruir ( &p_cadUno );

	/* Varios enteros consecutivos. */
	SCadena * p_cadNums = SCadGenerarConFormato ( "%d,%d,%d,%d", 1, 22, 333, 4444 );
	if ( ES_VALIDO ( p_cadNums ) )
	{
		if ( SCadEsIgualLiteral ( p_cadNums, "1,22,333,4444" ) != 1 )
		{
			printf( "Error caso 4: se esperaba \"1,22,333,4444\": [%s]\n", SCadValor ( p_cadNums ) );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 5: no se pudo generar la cadena de enteros\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SCadDestruir ( &p_cadNums );

	return ( iRes );
}



int TestSCadena ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SCadena]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSCadCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSCadGenerar01 () == BOOL_VAL_CIERTO ) &&
			( TestSCadCopiarConcatenar01 () == BOOL_VAL_CIERTO ) &&
			( TestSCadComparaciones01 () == BOOL_VAL_CIERTO ) &&
			( TestSCadEmpiezaAcaba01 () == BOOL_VAL_CIERTO ) &&
			( TestSCadTransformar01 () == BOOL_VAL_CIERTO ) &&
			( TestSCadCaracter01 () == BOOL_VAL_CIERTO ) &&
			( TestSCadGenerarConFormato01 () == BOOL_VAL_CIERTO ) )
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
