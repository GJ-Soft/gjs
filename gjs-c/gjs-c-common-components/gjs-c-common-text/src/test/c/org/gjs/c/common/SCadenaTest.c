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



static int TestSCadComparar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCadComparar 01:\n" );

	SCadena * p_cadA = SCadGenerar ( "abc" );
	SCadena * p_cadB = SCadGenerar ( "abd" );
	if ( ES_VALIDO ( p_cadA ) && ES_VALIDO ( p_cadB ) )
	{
		/* Comparacion de tres estados entre dos SCadena. */
		if ( SCadComparar ( p_cadA, p_cadB ) != COMP_MENOR )
		{
			printf( "Error caso 1: se esperaba COMP_MENOR: %d\n", SCadComparar ( p_cadA, p_cadB ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCadComparar ( p_cadB, p_cadA ) != COMP_MAYOR )
		{
			printf( "Error caso 2: se esperaba COMP_MAYOR: %d\n", SCadComparar ( p_cadB, p_cadA ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCadComparar ( p_cadA, p_cadA ) != COMP_IGUAL )
		{
			printf( "Error caso 3: se esperaba COMP_IGUAL: %d\n", SCadComparar ( p_cadA, p_cadA ) );
			iRes = BOOL_VAL_FALSO;
		}
		/* Y contra un literal. */
		if ( SCadCompararLiteral ( p_cadA, "abd" ) != COMP_MENOR )
		{
			printf( "Error caso 4: se esperaba COMP_MENOR contra el literal\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCadCompararLiteral ( p_cadB, "abc" ) != COMP_MAYOR )
		{
			printf( "Error caso 5: se esperaba COMP_MAYOR contra el literal\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCadCompararLiteral ( p_cadA, "abc" ) != COMP_IGUAL )
		{
			printf( "Error caso 6: se esperaba COMP_IGUAL contra el literal\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Una cadena valida es mayor que una nula. */
		if ( SCadComparar ( p_cadA, NULL ) != COMP_MAYOR )
		{
			printf( "Error caso 7: una cadena valida deberia ser mayor que una nula\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCadComparar ( NULL, p_cadB ) != COMP_MENOR )
		{
			printf( "Error caso 8: una cadena nula deberia ser menor que una valida\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCadComparar ( NULL, NULL ) != COMP_IGUAL )
		{
			printf( "Error caso 9: dos cadenas nulas deberian ser iguales\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCadCompararLiteral ( p_cadA, NULL ) != COMP_MAYOR )
		{
			printf( "Error caso 10: una cadena valida deberia ser mayor que un literal nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCadCompararLiteral ( NULL, "abc" ) != COMP_MENOR )
		{
			printf( "Error caso 11: una cadena nula deberia ser menor que un literal valido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCadCompararLiteral ( NULL, NULL ) != COMP_IGUAL )
		{
			printf( "Error caso 12: dos valores nulos deberian ser iguales\n" );
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

/* SCadEsMenor y SCadEsMayor ( y sus Ig y Literal ) siguen el orden de SCadComparar:
   el de diccionario, no primero por longitud. "b" va detras de "aa" aunque sea mas
   corta, y un prefijo va delante. */
static int TestSCadComparaciones02 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCadComparaciones 02:\n" );

	SCadena * p_cadCorta = SCadGenerar ( "b" );
	SCadena * p_cadLarga = SCadGenerar ( "aa" );
	SCadena * p_cadAlfa = SCadGenerar ( "alfa" );
	if ( ES_VALIDO ( p_cadCorta ) && ES_VALIDO ( p_cadLarga ) && ES_VALIDO ( p_cadAlfa ) )
	{
		if ( SCadEsMenor ( p_cadCorta, p_cadLarga ) != 0 )
		{
			printf( "Error caso 1: \"b\" no deberia ser menor que \"aa\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCadEsMayor ( p_cadCorta, p_cadLarga ) != 1 )
		{
			printf( "Error caso 2: \"b\" deberia ser mayor que \"aa\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCadEsMenor ( p_cadLarga, p_cadCorta ) != 1 )
		{
			printf( "Error caso 3: \"aa\" deberia ser menor que \"b\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCadEsMayorIg ( p_cadCorta, p_cadLarga ) != 1 )
		{
			printf( "Error caso 4: \"b\" deberia ser mayor o igual que \"aa\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCadEsMenorIg ( p_cadCorta, p_cadLarga ) != 0 )
		{
			printf( "Error caso 5: \"b\" no deberia ser menor o igual que \"aa\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Un prefijo va delante. */
		if ( SCadEsMenorLiteral ( p_cadAlfa, "alfabeto" ) != 1 )
		{
			printf( "Error caso 6: \"alfa\" deberia ser menor que \"alfabeto\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCadEsMayorLiteral ( p_cadAlfa, "alf" ) != 1 )
		{
			printf( "Error caso 7: \"alfa\" deberia ser mayor que \"alf\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Contra la vacia. */
		if ( SCadEsMayorLiteral ( p_cadAlfa, "" ) != 1 )
		{
			printf( "Error caso 8: \"alfa\" deberia ser mayor que \"\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Igual no es ni menor ni mayor. */
		if ( SCadEsMenorLiteral ( p_cadAlfa, "alfa" ) != 0 )
		{
			printf( "Error caso 9: \"alfa\" no deberia ser menor que si misma\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCadEsMayorLiteral ( p_cadAlfa, "alfa" ) != 0 )
		{
			printf( "Error caso 10: \"alfa\" no deberia ser mayor que si misma\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Con distincion, 'a' va detras de 'B'; sin ella, delante. */
		if ( SCadEsMayorLiteral ( p_cadAlfa, "BETA" ) != 1 )
		{
			printf( "Error caso 11: distinguiendo, \"alfa\" deberia ser mayor que \"BETA\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SCadDesactivarDistincionTipoLetra ( p_cadAlfa );
		if ( SCadEsMenorLiteral ( p_cadAlfa, "BETA" ) != 1 )
		{
			printf( "Error caso 12: sin distinguir, \"alfa\" deberia ser menor que \"BETA\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCadEsMenorIgLiteral ( p_cadAlfa, "ALFA" ) != 1 )
		{
			printf( "Error caso 13: sin distinguir, \"alfa\" deberia ser menor o igual que \"ALFA\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Con un nulo por medio, los predicados dan 0. */
		if ( SCadEsMenorLiteral ( p_cadAlfa, NULL ) != 0 )
		{
			printf( "Error caso 14: con un literal nulo deberia dar 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCadEsMayor ( NULL, p_cadAlfa ) != 0 )
		{
			printf( "Error caso 15: con una cadena nula deberia dar 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron generar las cadenas\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SCadDestruir ( &p_cadCorta );
	SCadDestruir ( &p_cadLarga );
	SCadDestruir ( &p_cadAlfa );
	return ( iRes );
}

/* SCadComparar y SCadCompararLiteral siguen la distincion de mayusculas de la
   primera cadena, como SCadEsIgual. "alfa" y "BETA" ordenan al reves segun se
   distinga o no: 'a' va detras de 'B' en ASCII, pero A va antes que B. */
static int TestSCadComparar02 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCadComparar 02:\n" );

	SCadena * p_cadA = SCadGenerar ( "alfa" );
	SCadena * p_cadB = SCadGenerar ( "ALFA" );
	SCadena * p_cadVacia = SCadCrear ( 10 );
	if ( ES_VALIDO ( p_cadA ) && ES_VALIDO ( p_cadB ) && ES_VALIDO ( p_cadVacia ) )
	{
		/* Distinguiendo, que es como nace la cadena. */
		if ( SCadCompararLiteral ( p_cadA, "ALFA" ) != COMP_MAYOR )
		{
			printf( "Error caso 1: distinguiendo, \"alfa\" deberia ser mayor que \"ALFA\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCadCompararLiteral ( p_cadA, "BETA" ) != COMP_MAYOR )
		{
			printf( "Error caso 2: distinguiendo, \"alfa\" deberia ser mayor que \"BETA\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Sin distinguir. */
		SCadDesactivarDistincionTipoLetra ( p_cadA );
		if ( SCadCompararLiteral ( p_cadA, "ALFA" ) != COMP_IGUAL )
		{
			printf( "Error caso 3: sin distinguir, \"alfa\" deberia ser igual a \"ALFA\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCadCompararLiteral ( p_cadA, "BETA" ) != COMP_MENOR )
		{
			printf( "Error caso 4: sin distinguir, \"alfa\" deberia ser menor que \"BETA\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCadCompararLiteral ( p_cadA, "ALFAS" ) != COMP_MENOR )
		{
			printf( "Error caso 5: sin distinguir, \"alfa\" deberia ser menor que \"ALFAS\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Coincide con SCadEsIgualLiteral. */
		if ( SCadEsIgualLiteral ( p_cadA, "ALFA" ) != 1 )
		{
			printf( "Error caso 6: sin distinguir, SCadEsIgualLiteral deberia dar 1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Manda la primera cadena: p_cadB sigue distinguiendo. */
		if ( SCadComparar ( p_cadA, p_cadB ) != COMP_IGUAL )
		{
			printf( "Error caso 7: con la primera sin distinguir deberian ser iguales\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCadComparar ( p_cadB, p_cadA ) != COMP_MENOR )
		{
			printf( "Error caso 8: con la primera distinguiendo, \"ALFA\" deberia ser menor\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* La vacia, sin distinguir. */
		SCadDesactivarDistincionTipoLetra ( p_cadVacia );
		if ( SCadCompararLiteral ( p_cadVacia, "" ) != COMP_IGUAL )
		{
			printf( "Error caso 9: sin distinguir, la vacia deberia ser igual a \"\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCadCompararLiteral ( p_cadVacia, "a" ) != COMP_MENOR )
		{
			printf( "Error caso 10: sin distinguir, la vacia deberia ser menor que \"a\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCadComparar ( p_cadA, p_cadVacia ) != COMP_MAYOR )
		{
			printf( "Error caso 11: sin distinguir, \"alfa\" deberia ser mayor que la vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Y al volver a activarla, vuelve el orden ASCII. */
		SCadActivarDistincionTipoLetra ( p_cadA );
		if ( SCadCompararLiteral ( p_cadA, "ALFA" ) != COMP_MAYOR )
		{
			printf( "Error caso 12: distinguiendo otra vez, \"alfa\" deberia ser mayor que \"ALFA\"\n" );
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
	SCadDestruir ( &p_cadVacia );
	return ( iRes );
}

/* SCadPtr envuelve el objeto en un SPtr con SCadDestruir como destructor: al
   destruir el SPtr se libera tambien el SCadena. Con MODO_DEPURACION se comprueba
   que no queda memoria reservada. */
static int TestSCadPtr01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCadPtr 01:\n" );
# if ( defined ( MODO_DEPURACION ) )
	unsigned long ulBloquesAntes = MemNumBloquesActuales ();
# endif
	SCadena * p_cadObj = SCadCrear ( 16 );
	SPtr * p_ptrObj = SCadPtr ( p_cadObj );
	if ( ES_NULO ( p_ptrObj ) )
	{
		printf( "Error caso 1: no se esperaba nulo al crear el SPtr\n" );
		iRes = BOOL_VAL_FALSO;
		SCadDestruir ( &p_cadObj );
	}
	else
	{
		if ( SPtrEsValido ( p_ptrObj ) != 1 )
		{
			printf( "Error caso 2: el SPtr deberia ser valido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SPtrObjeto ( p_ptrObj ) != p_cadObj )
		{
			printf( "Error caso 3: el SPtr deberia envolver el mismo SCadena\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* El SCadena pasa a ser del SPtr: se libera con el, no por separado. */
		SPtrDestruir ( &p_ptrObj );
		if ( ES_VALIDO ( p_ptrObj ) )
		{
			printf( "Error caso 4: se esperaba puntero nulo tras destruir\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
# if ( defined ( MODO_DEPURACION ) )
	if ( MemNumBloquesActuales () != ulBloquesAntes )
	{
		printf( "Error caso 5: quedan %ld bloques sin liberar\n", (long) ( MemNumBloquesActuales () - ulBloquesAntes ) );
		iRes = BOOL_VAL_FALSO;
	}
# endif
	return ( iRes );
}

/* Con objeto nulo, SCadPtr da un SPtr vacio: hay que destruirlo igualmente.
   Con MODO_DEPURACION se comprueba que no queda memoria reservada. */
static int TestSCadPtrNulo01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCadPtrNulo 01:\n" );
# if ( defined ( MODO_DEPURACION ) )
	unsigned long ulBloquesAntes = MemNumBloquesActuales ();
# endif
	SPtr * p_ptrObj = SCadPtr ( NULL );
	if ( ES_NULO ( p_ptrObj ) )
	{
		printf( "Error caso 1: con objeto nulo se esperaba un SPtr vacio, no nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SPtrEstaVacio ( p_ptrObj ) != 1 )
		{
			printf( "Error caso 2: con objeto nulo el SPtr deberia estar vacio\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SPtrDestruir ( &p_ptrObj );
	}
# if ( defined ( MODO_DEPURACION ) )
	if ( MemNumBloquesActuales () != ulBloquesAntes )
	{
		printf( "Error caso 3: quedan %ld bloques sin liberar\n", (long) ( MemNumBloquesActuales () - ulBloquesAntes ) );
		iRes = BOOL_VAL_FALSO;
	}
# endif
	ErrLimpiar ();
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
			( TestSCadComparaciones02 () == BOOL_VAL_CIERTO ) &&
			( TestSCadComparar01 () == BOOL_VAL_CIERTO ) &&
			( TestSCadComparar02 () == BOOL_VAL_CIERTO ) &&
			( TestSCadEmpiezaAcaba01 () == BOOL_VAL_CIERTO ) &&
			( TestSCadTransformar01 () == BOOL_VAL_CIERTO ) &&
			( TestSCadCaracter01 () == BOOL_VAL_CIERTO ) &&
			( TestSCadGenerarConFormato01 () == BOOL_VAL_CIERTO ) &&
			( TestSCadPtr01 () == BOOL_VAL_CIERTO ) &&
			( TestSCadPtrNulo01 () == BOOL_VAL_CIERTO ) )
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
