#include "Base.h"

#include "SCodigo.h"
#include "ValidacionCadenas.h"
#include "TextoConstantes.h"



static int TestSCodCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCodCrear 01:\n" );

	SCodigo * p_codObj = SCodCrear ( 20 );
	if ( ES_NULO ( p_codObj ) )
	{
		printf( "Error caso 1: no se esperaba nulo al crear\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SCodMaxLongitud ( p_codObj ) != 20 )
		{
			printf( "Error caso 2: la longitud maxima deberia ser 20: %d\n", SCodMaxLongitud ( p_codObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCodLongitud ( p_codObj ) != 0 )
		{
			printf( "Error caso 3: la longitud inicial deberia ser 0: %d\n", SCodLongitud ( p_codObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCodEstaVacio ( p_codObj ) != 1 )
		{
			printf( "Error caso 4: el codigo recien creado deberia estar vacio\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Un codigo vacio no supera la validacion. */
		if ( SCodEsValido ( p_codObj ) != 0 )
		{
			printf( "Error caso 5: un codigo vacio no deberia ser valido\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	SCodDestruir ( &p_codObj );

	if ( ES_VALIDO ( p_codObj ) )
	{
		printf( "Error caso 6: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}

	SCodigo * p_codSinTam = SCodCrear ( 0 );
	if ( ES_VALIDO ( p_codSinTam ) )
	{
		printf( "Error caso 7: no deberia crearse un codigo de longitud maxima 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SCodDestruir ( &p_codSinTam );

	SCodigo * p_codDef = SCodCrearDef ();
	if ( ES_VALIDO ( p_codDef ) )
	{
		if ( SCodMaxLongitud ( p_codDef ) != COD_MAX_TAM_DEF )
		{
			printf( "Error caso 8: la longitud maxima por defecto deberia ser %d: %d\n",
					COD_MAX_TAM_DEF, SCodMaxLongitud ( p_codDef ) );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 9: no se pudo crear el codigo por defecto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SCodDestruir ( &p_codDef );
	return ( iRes );
}

static int TestSCodCrearValor01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCodCrearValor 01:\n" );

	/* Con valor, el tope se ajusta a la longitud del valor. */
	SCodigo * p_codObj = SCodCrearValorLit ( "COD1" );
	if ( ES_VALIDO ( p_codObj ) )
	{
		if ( SCodEsIgualLit ( p_codObj, "COD1" ) != 1 )
		{
			printf( "Error caso 1: se esperaba \"COD1\": [%s]\n", SCodValorLit ( p_codObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCodMaxLongitud ( p_codObj ) != 4 )
		{
			printf( "Error caso 2: la longitud maxima deberia ser 4: %d\n", SCodMaxLongitud ( p_codObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCodEsValido ( p_codObj ) != 1 )
		{
			printf( "Error caso 3: \"COD1\" deberia ser un codigo valido\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el codigo con valor\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SCodDestruir ( &p_codObj );

	/* Un valor que no supera la validacion no llega a crear el objeto. */
	SCodigo * p_codMal = SCodCrearValorLit ( "1COD" );
	if ( ES_VALIDO ( p_codMal ) )
	{
		printf( "Error caso 4: un codigo que empieza por digito no deberia crearse\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SCodDestruir ( &p_codMal );

	/* La variante Ext fija el tope aparte del valor. */
	SCodigo * p_codExt = SCodCrearValorLitExt ( "COD1", 20 );
	if ( ES_VALIDO ( p_codExt ) )
	{
		if ( SCodMaxLongitud ( p_codExt ) != 20 )
		{
			printf( "Error caso 5: la longitud maxima deberia ser 20: %d\n", SCodMaxLongitud ( p_codExt ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCodLongitud ( p_codExt ) != 4 )
		{
			printf( "Error caso 6: la longitud deberia ser 4: %d\n", SCodLongitud ( p_codExt ) );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el codigo con valor y tope\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SCodDestruir ( &p_codExt );

	/* Y las mismas dos desde una SCadena. */
	SCadena * p_cadValor = SCadGenerar ( "COD2" );
	SCodigo * p_codCad = SCodCrearValorExt ( p_cadValor, 20 );
	if ( ES_VALIDO ( p_codCad ) && ES_VALIDO ( p_cadValor ) )
	{
		if ( SCodEsIgualCad ( p_codCad, p_cadValor ) != 1 )
		{
			printf( "Error caso 7: el codigo deberia ser igual a la cadena de origen\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el codigo desde una SCadena\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SCodDestruir ( &p_codCad );
	SCadDestruir ( &p_cadValor );
	return ( iRes );
}

static int TestSCodEstablecer01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCodEstablecer 01:\n" );

	SCodigo * p_codObj = SCodCrear ( 20 );
	if ( ES_VALIDO ( p_codObj ) )
	{
		if ( SCodEstablecerLit ( p_codObj, "COD1" ) != 1 )
		{
			printf( "Error caso 1: se esperaba resultado 1 al establecer un codigo valido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( CadComparar ( (char *) SCodValorLit ( p_codObj ), "COD1" ) != COMP_IGUAL )
		{
			printf( "Error caso 2: se esperaba \"COD1\": [%s]\n", SCodValorLit ( p_codObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCodLongitud ( p_codObj ) != 4 )
		{
			printf( "Error caso 3: la longitud deberia ser 4: %d\n", SCodLongitud ( p_codObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		/* Un codigo no admite espacios: entra, pero el codigo no es valido. */
		if ( SCodEstablecerLit ( p_codObj, "COD 1" ) != 0 )
		{
			printf( "Error caso 4: se esperaba resultado 0 con un codigo con espacios\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCodEsValido ( p_codObj ) != 0 )
		{
			printf( "Error caso 5: el codigo no deberia darse por valido con \"COD 1\" dentro\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Ni empezar por digito. */
		if ( SCodEstablecerLit ( p_codObj, "1COD" ) != 0 )
		{
			printf( "Error caso 6: se esperaba resultado 0 con un codigo que empieza por digito\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Lo que excede el tope, en cambio, no llega a entrar. */
		if ( SCodEstablecerLit ( p_codObj, "UNCODIGODEMASIADOLARGOPARAVEINTE" ) != 0 )
		{
			printf( "Error caso 7: un codigo que excede el tope no deberia aceptarse\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( CadComparar ( (char *) SCodValorLit ( p_codObj ), "1COD" ) != COMP_IGUAL )
		{
			printf( "Error caso 8: el valor anterior deberia seguir intacto: [%s]\n", SCodValorLit ( p_codObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		SCodLimpiar ( p_codObj );
		if ( SCodEstaVacio ( p_codObj ) != 1 )
		{
			printf( "Error caso 9: el codigo deberia estar vacio tras limpiar\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el codigo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SCodDestruir ( &p_codObj );
	return ( iRes );
}

static int TestSCodComparaciones01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCodComparaciones 01:\n" );

	SCodigo * p_codA = SCodCrearValorLitExt ( "AAA", 20 );
	SCodigo * p_codB = SCodCrearValorLitExt ( "BBB", 20 );
	if ( ES_VALIDO ( p_codA ) && ES_VALIDO ( p_codB ) )
	{
		if ( SCodEsMenor ( p_codA, p_codB ) != 1 )
		{
			printf( "Error caso 1: \"AAA\" deberia ser menor que \"BBB\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCodEsMayor ( p_codB, p_codA ) != 1 )
		{
			printf( "Error caso 2: \"BBB\" deberia ser mayor que \"AAA\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCodEsIgual ( p_codA, p_codB ) != 0 )
		{
			printf( "Error caso 3: \"AAA\" y \"BBB\" no deberian ser iguales\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCodEsDiferente ( p_codA, p_codB ) != 1 )
		{
			printf( "Error caso 4: \"AAA\" y \"BBB\" deberian ser diferentes\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCodEsIgualLit ( p_codA, "AAA" ) != 1 )
		{
			printf( "Error caso 5: \"AAA\" deberia ser igual al literal \"AAA\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCodEsMenorLit ( p_codA, "BBB" ) != 1 )
		{
			printf( "Error caso 6: \"AAA\" deberia ser menor que el literal \"BBB\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCodEsMayorLit ( p_codB, "AAA" ) != 1 )
		{
			printf( "Error caso 7: \"BBB\" deberia ser mayor que el literal \"AAA\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCodEsDiferenteLit ( p_codA, "BBB" ) != 1 )
		{
			printf( "Error caso 8: \"AAA\" deberia ser diferente del literal \"BBB\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCodComparar ( p_codA, p_codB ) != COMP_MENOR )
		{
			printf( "Error caso 9: se esperaba COMP_MENOR: %d\n", SCodComparar ( p_codA, p_codB ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCodComparar ( p_codB, p_codA ) != COMP_MAYOR )
		{
			printf( "Error caso 10: se esperaba COMP_MAYOR: %d\n", SCodComparar ( p_codB, p_codA ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCodComparar ( p_codA, p_codA ) != COMP_IGUAL )
		{
			printf( "Error caso 11: se esperaba COMP_IGUAL: %d\n", SCodComparar ( p_codA, p_codA ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCodCompararLit ( p_codA, "AAA" ) != COMP_IGUAL )
		{
			printf( "Error caso 12: se esperaba COMP_IGUAL contra el literal\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCodCompararCad ( p_codA, SCodValor ( p_codB ) ) != COMP_MENOR )
		{
			printf( "Error caso 13: se esperaba COMP_MENOR contra la cadena\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCodComparar ( p_codA, NULL ) != COMP_MAYOR )
		{
			printf( "Error caso 14: un codigo valido deberia ser mayor que uno nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCodComparar ( NULL, p_codB ) != COMP_MENOR )
		{
			printf( "Error caso 15: un codigo nulo deberia ser menor que uno valido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCodComparar ( NULL, NULL ) != COMP_IGUAL )
		{
			printf( "Error caso 16: dos codigos nulos deberian ser iguales\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCodCumpleExpReg ( p_codA, "AA?" ) != 1 )
		{
			printf( "Error caso 17: \"AAA\" deberia cumplir el patron \"AA?\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear los codigos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SCodDestruir ( &p_codA );
	SCodDestruir ( &p_codB );
	return ( iRes );
}

static int TestSCodCampo01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCodCampo 01:\n" );

	SCodigo * p_codObj = SCodCrearValorLitExt ( "AAA", 20 );
	SCampo * p_campObj = SCampCrear ( SCadEsCodigoValido, 20 );
	if ( ES_VALIDO ( p_codObj ) && ES_VALIDO ( p_campObj ) &&
		 ( SCampEstablecerLit ( p_campObj, "BBB" ) == 1 ) )
	{
		if ( SCodEsMenorCampo ( p_codObj, p_campObj ) != 1 )
		{
			printf( "Error caso 1: \"AAA\" deberia ser menor que el campo \"BBB\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCodEsMayorCampo ( p_codObj, p_campObj ) != 0 )
		{
			printf( "Error caso 2: \"AAA\" no deberia ser mayor que el campo \"BBB\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCodEsIgualCampo ( p_codObj, p_campObj ) != 0 )
		{
			printf( "Error caso 3: \"AAA\" y el campo \"BBB\" no deberian ser iguales\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCodEsDiferenteCampo ( p_codObj, p_campObj ) != 1 )
		{
			printf( "Error caso 4: \"AAA\" y el campo \"BBB\" deberian ser diferentes\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCodCompararCampo ( p_codObj, p_campObj ) != COMP_MENOR )
		{
			printf( "Error caso 5: se esperaba COMP_MENOR contra el campo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Asignar desde un campo trae su valor. */
		if ( SCodAsignarCampo ( p_codObj, p_campObj ) != 1 )
		{
			printf( "Error caso 6: se esperaba resultado 1 al asignar desde el campo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCodEsIgualCampo ( p_codObj, p_campObj ) != 1 )
		{
			printf( "Error caso 7: el codigo deberia ser igual al campo tras asignarlo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCodCompararCampo ( p_codObj, p_campObj ) != COMP_IGUAL )
		{
			printf( "Error caso 8: se esperaba COMP_IGUAL tras asignar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCodCompararCampo ( p_codObj, NULL ) != COMP_MAYOR )
		{
			printf( "Error caso 9: un codigo valido deberia ser mayor que un campo nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron preparar el codigo y el campo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SCodDestruir ( &p_codObj );
	SCampDestruir ( &p_campObj );
	return ( iRes );
}

static int TestSCodAsignarDuplicar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCodAsignarDuplicar 01:\n" );

	SCodigo * p_codObj = SCodCrearValorLitExt ( "ORIGEN1", 20 );
	if ( ES_VALIDO ( p_codObj ) )
	{
		SCodigo * p_codCopia = SCodDuplicar ( p_codObj );
		if ( ES_VALIDO ( p_codCopia ) )
		{
			if ( SCodEsIgual ( p_codCopia, p_codObj ) != 1 )
			{
				printf( "Error caso 1: la copia deberia ser igual al original\n" );
				iRes = BOOL_VAL_FALSO;
			}
			if ( SCodMaxLongitud ( p_codCopia ) != SCodMaxLongitud ( p_codObj ) )
			{
				printf( "Error caso 2: la copia deberia conservar la longitud maxima\n" );
				iRes = BOOL_VAL_FALSO;
			}
			/* La copia es independiente del original. */
			SCodLimpiar ( p_codCopia );
			if ( SCodEstaVacio ( p_codObj ) != 0 )
			{
				printf( "Error caso 3: limpiar la copia no deberia vaciar el original\n" );
				iRes = BOOL_VAL_FALSO;
			}
			if ( SCodAsignar ( p_codCopia, p_codObj ) != 1 )
			{
				printf( "Error caso 4: se esperaba resultado 1 al asignar\n" );
				iRes = BOOL_VAL_FALSO;
			}
			if ( SCodEsIgual ( p_codCopia, p_codObj ) != 1 )
			{
				printf( "Error caso 5: la copia deberia volver a ser igual al original\n" );
				iRes = BOOL_VAL_FALSO;
			}
		}
		else
		{
			printf( "Error caso 0: no se pudo duplicar el codigo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SCodDestruir ( &p_codCopia );
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el codigo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SCodDestruir ( &p_codObj );

	if ( ES_VALIDO ( SCodDuplicar ( NULL ) ) )
	{
		printf( "Error caso 6: duplicar un codigo nulo deberia devolver nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}



int TestSCodigo ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SCodigo]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSCodCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSCodCrearValor01 () == BOOL_VAL_CIERTO ) &&
			( TestSCodEstablecer01 () == BOOL_VAL_CIERTO ) &&
			( TestSCodComparaciones01 () == BOOL_VAL_CIERTO ) &&
			( TestSCodCampo01 () == BOOL_VAL_CIERTO ) &&
			( TestSCodAsignarDuplicar01 () == BOOL_VAL_CIERTO ) )
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
