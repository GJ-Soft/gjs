#include "Base.h"

#include "Cadenas.h"



static int TestCadCopiarConFormato01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test CadCopiarConFormato 01:\n" );
	char * p_cDestino = CadCrear ( 30 );
	if ( p_cDestino != NULL )
	{
		int iResult = CadCopiarConFormato ( p_cDestino, "Entero=%d", 1 );
		if ( iResult == 1 )
		{
			if ( CadComparar ( p_cDestino, "Entero=1" ) != COMP_IGUAL )
			{
				printf( "Error caso 1: La cadena formateada no es la esperada: [%s]\n", p_cDestino );
				iRes = BOOL_VAL_FALSO;
			}
		}
		else
		{
			printf( "Error: Se esperada resultado 1 pero se ha recibido %d\n", iResult );
			iRes = BOOL_VAL_FALSO;
		}
		CadLimpiar ( p_cDestino );
		iResult = CadCopiarConFormato ( p_cDestino, "Cadena=%s", "Valor" );
		if ( iResult == 1 )
		{
			if ( CadComparar ( p_cDestino, "Cadena=Valor" ) != COMP_IGUAL )
			{
			printf( "Error caso 2: La cadena formateada no es la esperada: [%s]\n", p_cDestino );
				iRes = BOOL_VAL_FALSO;
			}
		}
		else
		{
			printf( "Error: Se esperada resultado 1 pero se ha recibido %d\n", iResult );
			iRes = BOOL_VAL_FALSO;
		}
		CadLimpiar ( p_cDestino );
		iResult = CadCopiarConFormato ( p_cDestino, "Real=%f", 1.01 );
		if ( iResult == 1 )
		{
			if ( CadComparar ( p_cDestino, "Real=1.010000" ) != COMP_IGUAL )
			{
			printf( "Error caso 3: La cadena formateada no es la esperada: [%s]\n", p_cDestino );
				iRes = BOOL_VAL_FALSO;
			}
		}
		else
		{
			printf( "Error: Se esperada resultado 1 pero se ha recibido %d\n", iResult );
			iRes = BOOL_VAL_FALSO;
		}
		MemLiberar ( (void **) &p_cDestino );
	}
	else
	{
		printf( "Error: No se ha podido crear el objeto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestCadCopiarConcatenar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test CadCopiarConcatenar 01:\n" );

	char * p_cBuf = CadCrear ( 50 );
	if ( ES_VALIDO ( p_cBuf ) )
	{
		CadCopiar ( p_cBuf, "Hola" );
		if ( CadComparar ( p_cBuf, "Hola" ) != COMP_IGUAL )
		{
			printf( "Error caso 1: se esperaba \"Hola\": [%s]\n", p_cBuf );
			iRes = BOOL_VAL_FALSO;
		}
		CadConcatenar ( p_cBuf, " mundo" );
		if ( CadComparar ( p_cBuf, "Hola mundo" ) != COMP_IGUAL )
		{
			printf( "Error caso 2: se esperaba \"Hola mundo\": [%s]\n", p_cBuf );
			iRes = BOOL_VAL_FALSO;
		}
		CadConcatenarCaracter ( p_cBuf, '!' );
		if ( CadComparar ( p_cBuf, "Hola mundo!" ) != COMP_IGUAL )
		{
			printf( "Error caso 3: se esperaba \"Hola mundo!\": [%s]\n", p_cBuf );
			iRes = BOOL_VAL_FALSO;
		}
		CadCopiarCaracter ( p_cBuf, 'X' );
		if ( CadComparar ( p_cBuf, "X" ) != COMP_IGUAL )
		{
			printf( "Error caso 4: se esperaba \"X\": [%s]\n", p_cBuf );
			iRes = BOOL_VAL_FALSO;
		}
		MemLiberar ( (void **) &p_cBuf );
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el buffer\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestCadInsertarEscribir01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test CadInsertarEscribir 01:\n" );

	char * p_cBuf = CadCrear ( 50 );
	if ( ES_VALIDO ( p_cBuf ) )
	{
		/* Insertar desplaza el resto ( se indica la capacidad del buffer ). */
		CadCopiar ( p_cBuf, "Hola" );
		CadInsertarExt ( p_cBuf, 2, "XX", 50, -1 );
		if ( CadComparar ( p_cBuf, "HoXXla" ) != COMP_IGUAL )
		{
			printf( "Error caso 1: se esperaba \"HoXXla\": [%s]\n", p_cBuf );
			iRes = BOOL_VAL_FALSO;
		}
		/* Escribir sobrescribe en la posicion indicada. */
		CadCopiar ( p_cBuf, "Hola" );
		CadEscribir ( p_cBuf, 1, "YY" );
		if ( CadComparar ( p_cBuf, "HYYa" ) != COMP_IGUAL )
		{
			printf( "Error caso 2: se esperaba \"HYYa\": [%s]\n", p_cBuf );
			iRes = BOOL_VAL_FALSO;
		}
		MemLiberar ( (void **) &p_cBuf );
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el buffer\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestCadComparar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test CadComparar 01:\n" );

	if ( CadEsIgual ( "abc", "abc" ) != 1 )
	{
		printf( "Error caso 1: \"abc\" deberia ser igual a \"abc\"\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( CadEsMenor ( "abc", "abd" ) != 1 )
	{
		printf( "Error caso 2: \"abc\" deberia ser menor que \"abd\"\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( CadEsMayor ( "abd", "abc" ) != 1 )
	{
		printf( "Error caso 3: \"abd\" deberia ser mayor que \"abc\"\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* Comparacion sin distinguir mayusculas: 1 = COMP_IGUAL. */
	if ( CadCompararSinDistinguirTipoLetra ( "Hola", "hola" ) != COMP_IGUAL )
	{
		printf( "Error caso 4: \"Hola\" y \"hola\" deberian ser iguales sin distinguir tipo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* Comparacion parcial de los primeros N caracteres. */
	if ( CadCompararParcial ( "hola", "hoja", 2 ) != 1 )
	{
		printf( "Error caso 5: \"ho\" deberia coincidir en los 2 primeros caracteres\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( CadCompararParcial ( "hola", "xyza", 2 ) != 0 )
	{
		printf( "Error caso 6: \"ho\" y \"xy\" no deberian coincidir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( CadCompararSinDistinguirTipoLetra ( "Hola", "hola mundo" ) != COMP_MENOR )
	{
		printf( "Error caso 7: \"Hola\" deberia ser menor que \"hola mundo\"\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( CadCompararSinDistinguirTipoLetra ( "HoLA Mundo", "hola " ) != COMP_MAYOR )
	{
		printf( "Error caso 8: \"HoLA Mundo\" deberia ser mayor que \"hola \"\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( CadCompararSinDistinguirTipoLetra ( "Holas", "h0las" ) != COMP_MAYOR )
	{
		printf( "Error caso 9: \"Holas\" deberia ser mayor que \"h0las\"\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( CadCompararSinDistinguirTipoLetra ( "h0las", "Holas" ) != COMP_MENOR )
	{
		printf( "Error caso 10: \"h0las\" deberia ser menor que \"Holas\"\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestCadBuscar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test CadBuscar 01:\n" );

	if ( CadContiene ( "hola mundo", "mundo" ) != 1 )
	{
		printf( "Error caso 1: \"hola mundo\" deberia contener \"mundo\"\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( CadContiene ( "hola mundo", "xyz" ) != 0 )
	{
		printf( "Error caso 2: \"hola mundo\" no deberia contener \"xyz\"\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( CadEmpiezaPor ( "hola mundo", "hola" ) != 1 )
	{
		printf( "Error caso 3: deberia empezar por \"hola\"\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( CadAcabaPor ( "hola mundo", "mundo" ) != 1 )
	{
		printf( "Error caso 4: deberia acabar por \"mundo\"\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( CadBuscar ( "hola mundo", "mundo", 0 ) != 5 )
	{
		printf( "Error caso 5: \"mundo\" deberia estar en la posicion 5: %d\n", CadBuscar ( "hola mundo", "mundo", 0 ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( CadBuscar ( "hola", "xyz", 0 ) != -1 )
	{
		printf( "Error caso 6: \"xyz\" no deberia encontrarse\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( CadContar ( "abcabc", "bc" ) != 2 )
	{
		printf( "Error caso 7: \"bc\" deberia aparecer 2 veces: %d\n", CadContar ( "abcabc", "bc" ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( CadContieneCaracter ( "hola", 'l' ) != 1 )
	{
		printf( "Error caso 8: \"hola\" deberia contener 'l'\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( CadBuscarCaracter ( "hola", 'l', 0 ) != 2 )
	{
		printf( "Error caso 9: 'l' deberia estar en la posicion 2: %d\n", CadBuscarCaracter ( "hola", 'l', 0 ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( CadContarCaracter ( "banana", 'a' ) != 3 )
	{
		printf( "Error caso 10: 'a' deberia aparecer 3 veces: %d\n", CadContarCaracter ( "banana", 'a' ) );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestCadReemplazar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test CadReemplazar 01:\n" );

	char * p_cBuf = CadCrear ( 50 );
	if ( ES_VALIDO ( p_cBuf ) )
	{
		CadCopiar ( p_cBuf, "abcabc" );
		CadReemplazar ( p_cBuf, "b", "X" );
		if ( CadComparar ( p_cBuf, "aXcaXc" ) != COMP_IGUAL )
		{
			printf( "Error caso 1: se esperaba \"aXcaXc\": [%s]\n", p_cBuf );
			iRes = BOOL_VAL_FALSO;
		}
		CadCopiar ( p_cBuf, "hola" );
		CadReemplazarCaracter ( p_cBuf, 'o', '0' );
		if ( CadComparar ( p_cBuf, "h0la" ) != COMP_IGUAL )
		{
			printf( "Error caso 2: se esperaba \"h0la\": [%s]\n", p_cBuf );
			iRes = BOOL_VAL_FALSO;
		}
		MemLiberar ( (void **) &p_cBuf );
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el buffer\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestCadEliminar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test CadEliminar 01:\n" );

	char * p_cBuf = CadCrear ( 50 );
	if ( ES_VALIDO ( p_cBuf ) )
	{
		CadCopiar ( p_cBuf, "hola" );
		CadEliminarCaracter ( p_cBuf, 0 );
		if ( CadComparar ( p_cBuf, "ola" ) != COMP_IGUAL )
		{
			printf( "Error caso 1: se esperaba \"ola\": [%s]\n", p_cBuf );
			iRes = BOOL_VAL_FALSO;
		}
		CadCopiar ( p_cBuf, "hola" );
		CadEliminarPrimerosCaracteres ( p_cBuf, 2 );
		if ( CadComparar ( p_cBuf, "la" ) != COMP_IGUAL )
		{
			printf( "Error caso 2: se esperaba \"la\": [%s]\n", p_cBuf );
			iRes = BOOL_VAL_FALSO;
		}
		CadCopiar ( p_cBuf, "hola" );
		CadEliminarUltimosCaracteres ( p_cBuf, 2 );
		if ( CadComparar ( p_cBuf, "ho" ) != COMP_IGUAL )
		{
			printf( "Error caso 3: se esperaba \"ho\": [%s]\n", p_cBuf );
			iRes = BOOL_VAL_FALSO;
		}
		CadCopiar ( p_cBuf, "banana" );
		CadEliminarAparicionesCaracter ( p_cBuf, 'a' );
		if ( CadComparar ( p_cBuf, "bnn" ) != COMP_IGUAL )
		{
			printf( "Error caso 4: se esperaba \"bnn\": [%s]\n", p_cBuf );
			iRes = BOOL_VAL_FALSO;
		}
		MemLiberar ( (void **) &p_cBuf );
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el buffer\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestCadBlancos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test CadBlancos 01:\n" );

	char * p_cBuf = CadCrear ( 50 );
	if ( ES_VALIDO ( p_cBuf ) )
	{
		CadCopiar ( p_cBuf, "  hola  " );
		CadEliminarBlancosLaterales ( p_cBuf );
		if ( CadComparar ( p_cBuf, "hola" ) != COMP_IGUAL )
		{
			printf( "Error caso 1: se esperaba \"hola\": [%s]\n", p_cBuf );
			iRes = BOOL_VAL_FALSO;
		}
		CadCopiar ( p_cBuf, "a b c" );
		CadEliminarBlancos ( p_cBuf );
		if ( CadComparar ( p_cBuf, "abc" ) != COMP_IGUAL )
		{
			printf( "Error caso 2: se esperaba \"abc\": [%s]\n", p_cBuf );
			iRes = BOOL_VAL_FALSO;
		}
		MemLiberar ( (void **) &p_cBuf );
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el buffer\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( CadContieneBlancos ( "a b" ) != 1 )
	{
		printf( "Error caso 3: \"a b\" deberia contener blancos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( CadContieneBlancos ( "ab" ) != 0 )
	{
		printf( "Error caso 4: \"ab\" no deberia contener blancos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestCadExtraer01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test CadExtraer 01:\n" );

	char * p_cSub = CadExtraer ( "hola mundo", 5, 5 );
	if ( ES_VALIDO ( p_cSub ) )
	{
		if ( CadComparar ( p_cSub, "mundo" ) != COMP_IGUAL )
		{
			printf( "Error caso 1: se esperaba \"mundo\": [%s]\n", p_cSub );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 1: no se pudo extraer la subcadena\n" );
		iRes = BOOL_VAL_FALSO;
	}
	MemLiberar ( (void **) &p_cSub );

	char * p_cPri = CadExtraerPrimeros ( "hola", 2 );
	if ( ES_VALIDO ( p_cPri ) )
	{
		if ( CadComparar ( p_cPri, "ho" ) != COMP_IGUAL )
		{
			printf( "Error caso 2: se esperaba \"ho\": [%s]\n", p_cPri );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 2: no se pudieron extraer los primeros caracteres\n" );
		iRes = BOOL_VAL_FALSO;
	}
	MemLiberar ( (void **) &p_cPri );

	char * p_cUlt = CadExtraerUltimos ( "hola", 2 );
	if ( ES_VALIDO ( p_cUlt ) )
	{
		if ( CadComparar ( p_cUlt, "la" ) != COMP_IGUAL )
		{
			printf( "Error caso 3: se esperaba \"la\": [%s]\n", p_cUlt );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 3: no se pudieron extraer los ultimos caracteres\n" );
		iRes = BOOL_VAL_FALSO;
	}
	MemLiberar ( (void **) &p_cUlt );
	return ( iRes );
}

static int TestCadTransformar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test CadTransformar 01:\n" );

	char * p_cBuf = CadCrear ( 50 );
	if ( ES_VALIDO ( p_cBuf ) )
	{
		CadCopiar ( p_cBuf, "abc" );
		CadInvertir ( p_cBuf );
		if ( CadComparar ( p_cBuf, "cba" ) != COMP_IGUAL )
		{
			printf( "Error caso 1: se esperaba \"cba\": [%s]\n", p_cBuf );
			iRes = BOOL_VAL_FALSO;
		}
		CadCopiar ( p_cBuf, "hola" );
		CadConvertirAMayusculas ( p_cBuf );
		if ( CadComparar ( p_cBuf, "HOLA" ) != COMP_IGUAL )
		{
			printf( "Error caso 2: se esperaba \"HOLA\": [%s]\n", p_cBuf );
			iRes = BOOL_VAL_FALSO;
		}
		CadConvertirAMinusculas ( p_cBuf );
		if ( CadComparar ( p_cBuf, "hola" ) != COMP_IGUAL )
		{
			printf( "Error caso 3: se esperaba \"hola\": [%s]\n", p_cBuf );
			iRes = BOOL_VAL_FALSO;
		}
		/* Capitaliza el inicio y tras un punto ( no cada palabra ). */
		CadCopiar ( p_cBuf, "hola mundo" );
		CadConvertirACapitales ( p_cBuf );
		if ( CadComparar ( p_cBuf, "Hola mundo" ) != COMP_IGUAL )
		{
			printf( "Error caso 4: se esperaba \"Hola mundo\": [%s]\n", p_cBuf );
			iRes = BOOL_VAL_FALSO;
		}
		MemLiberar ( (void **) &p_cBuf );
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el buffer\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestCadNumericas01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test CadNumericas 01:\n" );

	if ( CadEsNumerica ( "123" ) != 1 )
	{
		printf( "Error caso 1: \"123\" deberia ser numerica\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( CadEsNumerica ( "12.5" ) != 1 )
	{
		printf( "Error caso 2: \"12.5\" deberia ser numerica\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( CadEsNumerica ( "abc" ) != 0 )
	{
		printf( "Error caso 3: \"abc\" no deberia ser numerica\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( CadEsNumeroEntero ( "123" ) != 1 )
	{
		printf( "Error caso 4: \"123\" deberia ser entero\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( CadEsNumeroEntero ( "12.5" ) != 0 )
	{
		printf( "Error caso 5: \"12.5\" no deberia ser entero\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( CadEsNumeroReal ( "12.5" ) != 1 )
	{
		printf( "Error caso 6: \"12.5\" deberia ser real\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( CadEsNumeroHexadecimal ( "1AF" ) != 1 )
	{
		printf( "Error caso 7: \"1AF\" deberia ser hexadecimal\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( CadEsNumeroHexadecimal ( "xyz" ) != 0 )
	{
		printf( "Error caso 8: \"xyz\" no deberia ser hexadecimal\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( CadEsToken ( "hola" ) != 1 )
	{
		printf( "Error caso 9: \"hola\" deberia ser un token\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( CadEsToken ( "1abc" ) != 0 )
	{
		printf( "Error caso 10: \"1abc\" no deberia ser un token\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestCadPalabras01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test CadPalabras 01:\n" );

	if ( CadNumPalabras ( "hola mundo cruel" ) != 3 )
	{
		printf( "Error caso 1: se esperaban 3 palabras: %d\n", CadNumPalabras ( "hola mundo cruel" ) );
		iRes = BOOL_VAL_FALSO;
	}
	char * p_cPal = CadPalabra ( "hola mundo cruel", 1 );
	if ( ES_VALIDO ( p_cPal ) )
	{
		if ( CadComparar ( p_cPal, "mundo" ) != COMP_IGUAL )
		{
			printf( "Error caso 2: la palabra 1 deberia ser \"mundo\": [%s]\n", p_cPal );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 2: no se pudo extraer la palabra\n" );
		iRes = BOOL_VAL_FALSO;
	}
	MemLiberar ( (void **) &p_cPal );

	if ( CadNumPalabrasSep ( "a,b,c", ',' ) != 3 )
	{
		printf( "Error caso 3: se esperaban 3 partes: %d\n", CadNumPalabrasSep ( "a,b,c", ',' ) );
		iRes = BOOL_VAL_FALSO;
	}
	char * p_cSep = CadPalabraSep ( "a,b,c", 1, ',' );
	if ( ES_VALIDO ( p_cSep ) )
	{
		if ( CadComparar ( p_cSep, "b" ) != COMP_IGUAL )
		{
			printf( "Error caso 4: la parte 1 deberia ser \"b\": [%s]\n", p_cSep );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 4: no se pudo extraer la parte\n" );
		iRes = BOOL_VAL_FALSO;
	}
	MemLiberar ( (void **) &p_cSep );
	return ( iRes );
}

static int TestCadCoherencia01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test CadCoherencia 01:\n" );

	if ( CadCoherenciaParentesis ( "(a(b))" ) != 1 )
	{
		printf( "Error caso 1: \"(a(b))\" deberia ser coherente\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( CadCoherenciaParentesis ( "(a" ) != 0 )
	{
		printf( "Error caso 2: \"(a\" no deberia ser coherente\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( CadCoherenciaLlaves ( "{x}" ) != 1 )
	{
		printf( "Error caso 3: \"{x}\" deberia ser coherente\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( CadCoherenciaCorchetes ( "[x" ) != 0 )
	{
		printf( "Error caso 4: \"[x\" no deberia ser coherente\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestCadComponer01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test CadComponer 01:\n" );

	char * p_cComp = CadComponer ( "uno", "dos", '-' );
	if ( ES_VALIDO ( p_cComp ) )
	{
		if ( CadComparar ( p_cComp, "uno-dos" ) != COMP_IGUAL )
		{
			printf( "Error caso 1: se esperaba \"uno-dos\": [%s]\n", p_cComp );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 1: no se pudo componer\n" );
		iRes = BOOL_VAL_FALSO;
	}
	MemLiberar ( (void **) &p_cComp );

	char * p_cEnv = CadEnvolver ( "abc", '#' );
	if ( ES_VALIDO ( p_cEnv ) )
	{
		if ( CadComparar ( p_cEnv, "#abc#" ) != COMP_IGUAL )
		{
			printf( "Error caso 2: se esperaba \"#abc#\": [%s]\n", p_cEnv );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 2: no se pudo envolver\n" );
		iRes = BOOL_VAL_FALSO;
	}
	MemLiberar ( (void **) &p_cEnv );
	return ( iRes );
}

static int TestCadToken01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test CadToken 01:\n" );

	if ( CadEsTokenValido ( "hola" ) != 1 )
	{
		printf( "Error caso 1: \"hola\" deberia ser un token valido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( CadEsTokenValido ( "1abc" ) != 0 )
	{
		printf( "Error caso 2: \"1abc\" no deberia ser un token valido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( CadEsIdentificadorValido ( "variable" ) != 1 )
	{
		printf( "Error caso 3: \"variable\" deberia ser un identificador valido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* CadValorNumerico compone un valor a partir de los codigos ASCII. */
	if ( (int) CadValorNumerico ( "A" ) != 65 )
	{
		printf( "Error caso 4: el valor numerico de \"A\" deberia ser 65: %d\n", (int) CadValorNumerico ( "A" ) );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}



int TestCadenas ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test Cadenas]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestCadCopiarConFormato01 () == BOOL_VAL_CIERTO ) &&
			( TestCadCopiarConcatenar01 () == BOOL_VAL_CIERTO ) &&
			( TestCadInsertarEscribir01 () == BOOL_VAL_CIERTO ) &&
			( TestCadComparar01 () == BOOL_VAL_CIERTO ) &&
			( TestCadBuscar01 () == BOOL_VAL_CIERTO ) &&
			( TestCadReemplazar01 () == BOOL_VAL_CIERTO ) &&
			( TestCadEliminar01 () == BOOL_VAL_CIERTO ) &&
			( TestCadBlancos01 () == BOOL_VAL_CIERTO ) &&
			( TestCadExtraer01 () == BOOL_VAL_CIERTO ) &&
			( TestCadTransformar01 () == BOOL_VAL_CIERTO ) &&
			( TestCadNumericas01 () == BOOL_VAL_CIERTO ) &&
			( TestCadPalabras01 () == BOOL_VAL_CIERTO ) &&
			( TestCadCoherencia01 () == BOOL_VAL_CIERTO ) &&
			( TestCadComponer01 () == BOOL_VAL_CIERTO ) &&
			( TestCadToken01 () == BOOL_VAL_CIERTO ) )
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
