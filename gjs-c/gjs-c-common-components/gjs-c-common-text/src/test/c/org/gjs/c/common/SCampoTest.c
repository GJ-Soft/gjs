#include "Base.h"

#include "SCampo.h"
#include "ValidacionCadenas.h"
#include "TextoConstantes.h"



/* Validacion a medida, para comprobar que SCampo respeta la que le den. */
static int EsLongitudPar ( SCadena * p_cadObj )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) && ( ( SCadLongitud ( p_cadObj ) % 2 ) == 0 ) )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}



static int TestSCampCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCampCrear 01:\n" );

	SCampo * p_campObj = SCampCrear ( SCadEsCodigoValido, 20 );
	if ( ES_NULO ( p_campObj ) )
	{
		printf( "Error caso 1: no se esperaba nulo al crear\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SCampMaxLongitud ( p_campObj ) != 20 )
		{
			printf( "Error caso 2: la longitud maxima deberia ser 20: %d\n", SCampMaxLongitud ( p_campObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCampLongitud ( p_campObj ) != 0 )
		{
			printf( "Error caso 3: la longitud inicial deberia ser 0: %d\n", SCampLongitud ( p_campObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCampEstaVacio ( p_campObj ) != 1 )
		{
			printf( "Error caso 4: el campo recien creado deberia estar vacio\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Vacio no supera la validacion de codigo, que exige longitud. */
		if ( SCampEsValido ( p_campObj ) != 0 )
		{
			printf( "Error caso 5: un campo de codigo vacio no deberia ser valido\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	SCampDestruir ( &p_campObj );

	if ( ES_VALIDO ( p_campObj ) )
	{
		printf( "Error caso 6: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}

	/* Sin funcion de validacion no hay campo. */
	SCampo * p_campSinVal = SCampCrear ( NULL, 20 );
	if ( ES_VALIDO ( p_campSinVal ) )
	{
		printf( "Error caso 7: no deberia crearse un campo sin funcion de validacion\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SCampDestruir ( &p_campSinVal );

	/* Ni con una longitud maxima no positiva. */
	SCampo * p_campSinTam = SCampCrear ( SCadEsCodigoValido, 0 );
	if ( ES_VALIDO ( p_campSinTam ) )
	{
		printf( "Error caso 8: no deberia crearse un campo de longitud maxima 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SCampDestruir ( &p_campSinTam );

	/* La variante por defecto usa NOM_MAX_TAM_DEF. */
	SCampo * p_campDef = SCampCrearDef ( SCadEsCodigoValido );
	if ( ES_VALIDO ( p_campDef ) )
	{
		if ( SCampMaxLongitud ( p_campDef ) != NOM_MAX_TAM_DEF )
		{
			printf( "Error caso 9: la longitud maxima por defecto deberia ser %d: %d\n",
					NOM_MAX_TAM_DEF, SCampMaxLongitud ( p_campDef ) );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 10: no se pudo crear el campo por defecto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SCampDestruir ( &p_campDef );
	return ( iRes );
}

static int TestSCampEstablecer01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCampEstablecer 01:\n" );

	SCampo * p_campObj = SCampCrear ( SCadEsCodigoValido, 20 );
	if ( ES_VALIDO ( p_campObj ) )
	{
		if ( SCampEstablecerLit ( p_campObj, "COD1" ) != 1 )
		{
			printf( "Error caso 1: se esperaba resultado 1 al establecer un codigo valido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCampLongitud ( p_campObj ) != 4 )
		{
			printf( "Error caso 2: la longitud deberia ser 4: %d\n", SCampLongitud ( p_campObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( CadComparar ( (char *) SCampValorLit ( p_campObj ), "COD1" ) != COMP_IGUAL )
		{
			printf( "Error caso 3: se esperaba \"COD1\": [%s]\n", SCampValorLit ( p_campObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCampEsValido ( p_campObj ) != 1 )
		{
			printf( "Error caso 4: \"COD1\" deberia superar la validacion\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCampEstaVacio ( p_campObj ) != 0 )
		{
			printf( "Error caso 5: el campo no deberia estar vacio tras establecerlo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Un valor que no supera la validacion se establece igualmente: el   */
		/* retorno 0 dice que lo que hay dentro no es valido, no que no haya */
		/* entrado.                                                          */
		if ( SCampEstablecerLit ( p_campObj, "1COD" ) != 0 )
		{
			printf( "Error caso 6: se esperaba resultado 0 con un codigo que empieza por digito\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( CadComparar ( (char *) SCampValorLit ( p_campObj ), "1COD" ) != COMP_IGUAL )
		{
			printf( "Error caso 7: el valor invalido deberia haberse establecido: [%s]\n", SCampValorLit ( p_campObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCampEsValido ( p_campObj ) != 0 )
		{
			printf( "Error caso 8: el campo no deberia darse por valido con \"1COD\" dentro\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Uno mas largo que el tope, en cambio, no llega a entrar. */
		if ( SCampEstablecerLit ( p_campObj, "UNCODIGODEMASIADOLARGOPARAVEINTE" ) != 0 )
		{
			printf( "Error caso 9: un valor que excede el tope no deberia aceptarse\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( CadComparar ( (char *) SCampValorLit ( p_campObj ), "1COD" ) != COMP_IGUAL )
		{
			printf( "Error caso 10: el valor anterior deberia seguir intacto: [%s]\n", SCampValorLit ( p_campObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		/* Desde una SCadena. */
		SCadena * p_cadValor = SCadGenerar ( "OTRO2" );
		if ( ES_VALIDO ( p_cadValor ) )
		{
			if ( SCampEstablecer ( p_campObj, p_cadValor ) != 1 )
			{
				printf( "Error caso 11: se esperaba resultado 1 al establecer desde una SCadena\n" );
				iRes = BOOL_VAL_FALSO;
			}
			if ( SCampEsIgualCad ( p_campObj, p_cadValor ) != 1 )
			{
				printf( "Error caso 12: el campo deberia ser igual a la cadena establecida\n" );
				iRes = BOOL_VAL_FALSO;
			}
		}
		else
		{
			printf( "Error caso 0: no se pudo generar la cadena de valor\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SCadDestruir ( &p_cadValor );

		SCampLimpiar ( p_campObj );
		if ( SCampEstaVacio ( p_campObj ) != 1 )
		{
			printf( "Error caso 13: el campo deberia estar vacio tras limpiar\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el campo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SCampDestruir ( &p_campObj );
	return ( iRes );
}

static int TestSCampValidacionPropia01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCampValidacionPropia 01:\n" );

	SCampo * p_campObj = SCampCrear ( EsLongitudPar, 10 );
	if ( ES_VALIDO ( p_campObj ) )
	{
		if ( SCampEstablecerLit ( p_campObj, "abcd" ) != 1 )
		{
			printf( "Error caso 1: un valor de longitud par deberia aceptarse\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCampEstablecerLit ( p_campObj, "abc" ) != 0 )
		{
			printf( "Error caso 2: se esperaba resultado 0 con un valor de longitud impar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Aqui el campo vacio si es valido: la longitud 0 es par. */
		SCampLimpiar ( p_campObj );
		if ( SCampEsValido ( p_campObj ) != 1 )
		{
			printf( "Error caso 3: el campo vacio deberia superar esta validacion\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el campo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SCampDestruir ( &p_campObj );
	return ( iRes );
}

static int TestSCampComparaciones01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCampComparaciones 01:\n" );

	SCampo * p_campA = SCampCrear ( SCadEsCodigoValido, 20 );
	SCampo * p_campB = SCampCrear ( SCadEsCodigoValido, 20 );
	if ( ES_VALIDO ( p_campA ) && ES_VALIDO ( p_campB ) &&
		 ( SCampEstablecerLit ( p_campA, "AAA" ) == 1 ) &&
		 ( SCampEstablecerLit ( p_campB, "BBB" ) == 1 ) )
	{
		if ( SCampEsMenor ( p_campA, p_campB ) != 1 )
		{
			printf( "Error caso 1: \"AAA\" deberia ser menor que \"BBB\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCampEsMayor ( p_campB, p_campA ) != 1 )
		{
			printf( "Error caso 2: \"BBB\" deberia ser mayor que \"AAA\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCampEsIgual ( p_campA, p_campB ) != 0 )
		{
			printf( "Error caso 3: \"AAA\" y \"BBB\" no deberian ser iguales\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCampEsDiferente ( p_campA, p_campB ) != 1 )
		{
			printf( "Error caso 4: \"AAA\" y \"BBB\" deberian ser diferentes\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCampEsIgualLit ( p_campA, "AAA" ) != 1 )
		{
			printf( "Error caso 5: \"AAA\" deberia ser igual al literal \"AAA\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCampEsMenorLit ( p_campA, "BBB" ) != 1 )
		{
			printf( "Error caso 6: \"AAA\" deberia ser menor que el literal \"BBB\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCampEsMayorLit ( p_campB, "AAA" ) != 1 )
		{
			printf( "Error caso 7: \"BBB\" deberia ser mayor que el literal \"AAA\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCampEsDiferenteLit ( p_campA, "BBB" ) != 1 )
		{
			printf( "Error caso 8: \"AAA\" deberia ser diferente del literal \"BBB\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* La comparacion de tres estados. */
		if ( SCampComparar ( p_campA, p_campB ) != COMP_MENOR )
		{
			printf( "Error caso 9: se esperaba COMP_MENOR: %d\n", SCampComparar ( p_campA, p_campB ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCampComparar ( p_campB, p_campA ) != COMP_MAYOR )
		{
			printf( "Error caso 10: se esperaba COMP_MAYOR: %d\n", SCampComparar ( p_campB, p_campA ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCampComparar ( p_campA, p_campA ) != COMP_IGUAL )
		{
			printf( "Error caso 11: se esperaba COMP_IGUAL: %d\n", SCampComparar ( p_campA, p_campA ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCampCompararLit ( p_campA, "AAA" ) != COMP_IGUAL )
		{
			printf( "Error caso 12: se esperaba COMP_IGUAL contra el literal\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCampCompararCad ( p_campA, SCampValor ( p_campB ) ) != COMP_MENOR )
		{
			printf( "Error caso 13: se esperaba COMP_MENOR contra la cadena\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Un campo valido es mayor que uno nulo, y dos nulos son iguales. */
		if ( SCampComparar ( p_campA, NULL ) != COMP_MAYOR )
		{
			printf( "Error caso 14: un campo valido deberia ser mayor que uno nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCampComparar ( NULL, p_campB ) != COMP_MENOR )
		{
			printf( "Error caso 15: un campo nulo deberia ser menor que uno valido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCampComparar ( NULL, NULL ) != COMP_IGUAL )
		{
			printf( "Error caso 16: dos campos nulos deberian ser iguales\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Las expresiones regulares llegan hasta la cadena interna. */
		if ( SCampCumpleExpReg ( p_campA, "AA?" ) != 1 )
		{
			printf( "Error caso 17: \"AAA\" deberia cumplir el patron \"AA?\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCampCumpleExpReg ( p_campA, "BB?" ) != 0 )
		{
			printf( "Error caso 18: \"AAA\" no deberia cumplir el patron \"BB?\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron preparar los campos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SCampDestruir ( &p_campA );
	SCampDestruir ( &p_campB );
	return ( iRes );
}

static int TestSCampAsignarDuplicar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCampAsignarDuplicar 01:\n" );

	SCampo * p_campObj = SCampCrear ( SCadEsCodigoValido, 20 );
	if ( ES_VALIDO ( p_campObj ) && ( SCampEstablecerLit ( p_campObj, "ORIGEN1" ) == 1 ) )
	{
		SCampo * p_campCopia = SCampDuplicar ( p_campObj );
		if ( ES_VALIDO ( p_campCopia ) )
		{
			if ( SCampEsIgual ( p_campCopia, p_campObj ) != 1 )
			{
				printf( "Error caso 1: la copia deberia ser igual al original\n" );
				iRes = BOOL_VAL_FALSO;
			}
			if ( SCampMaxLongitud ( p_campCopia ) != SCampMaxLongitud ( p_campObj ) )
			{
				printf( "Error caso 2: la copia deberia conservar la longitud maxima\n" );
				iRes = BOOL_VAL_FALSO;
			}
			/* La copia es independiente. */
			SCampLimpiar ( p_campCopia );
			if ( SCampEstaVacio ( p_campObj ) != 0 )
			{
				printf( "Error caso 3: limpiar la copia no deberia vaciar el original\n" );
				iRes = BOOL_VAL_FALSO;
			}
			/* Y se puede volver a llenar por asignacion. */
			if ( SCampAsignar ( p_campCopia, p_campObj ) != 1 )
			{
				printf( "Error caso 4: se esperaba resultado 1 al asignar\n" );
				iRes = BOOL_VAL_FALSO;
			}
			if ( SCampEsIgual ( p_campCopia, p_campObj ) != 1 )
			{
				printf( "Error caso 5: la copia deberia volver a ser igual al original\n" );
				iRes = BOOL_VAL_FALSO;
			}
		}
		else
		{
			printf( "Error caso 0: no se pudo duplicar el campo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SCampDestruir ( &p_campCopia );
	}
	else
	{
		printf( "Error caso 0: no se pudo preparar el campo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SCampDestruir ( &p_campObj );

	if ( ES_VALIDO ( SCampDuplicar ( NULL ) ) )
	{
		printf( "Error caso 6: duplicar un campo nulo deberia devolver nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}



int TestSCampo ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SCampo]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSCampCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSCampEstablecer01 () == BOOL_VAL_CIERTO ) &&
			( TestSCampValidacionPropia01 () == BOOL_VAL_CIERTO ) &&
			( TestSCampComparaciones01 () == BOOL_VAL_CIERTO ) &&
			( TestSCampAsignarDuplicar01 () == BOOL_VAL_CIERTO ) )
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
