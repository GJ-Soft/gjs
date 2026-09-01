#include "Base.h"

#include "SNombre.h"
#include "ValidacionCadenas.h"
#include "TextoConstantes.h"



static int TestSNomCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SNomCrear 01:\n" );

	SNombre * p_nomObj = SNomCrear ( 30 );
	if ( ES_NULO ( p_nomObj ) )
	{
		printf( "Error caso 1: no se esperaba nulo al crear\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SNomEstaVacio ( p_nomObj ) != 1 )
		{
			printf( "Error caso 2: el nombre recien creado deberia estar vacio\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SNomLongitud ( p_nomObj ) != 0 )
		{
			printf( "Error caso 3: la longitud inicial deberia ser 0: %d\n", SNomLongitud ( p_nomObj ) );
			iRes = BOOL_VAL_FALSO;
		}
	}
	SNomDestruir ( &p_nomObj );

	if ( ES_VALIDO ( p_nomObj ) )
	{
		printf( "Error caso 4: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSNomEstablecer01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SNomEstablecer 01:\n" );

	SNombre * p_nomObj = SNomCrear ( 30 );
	if ( ES_VALIDO ( p_nomObj ) )
	{
		if ( SNomEstablecerLit ( p_nomObj, "Juan" ) != 1 )
		{
			printf( "Error caso 1: se esperaba resultado 1 al establecer un nombre valido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SNomEstaVacio ( p_nomObj ) != 0 )
		{
			printf( "Error caso 2: el nombre no deberia estar vacio tras establecerlo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( CadComparar ( (char *) SNomValorLit ( p_nomObj ), "Juan" ) != COMP_IGUAL )
		{
			printf( "Error caso 3: se esperaba \"Juan\": [%s]\n", SNomValorLit ( p_nomObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		/* Un nombre con espacios no es valido: entra, pero devuelve 0. */
		if ( SNomEstablecerLit ( p_nomObj, "con espacio" ) != 0 )
		{
			printf( "Error caso 4: se esperaba resultado 0 con un nombre con espacios\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SNomEsValido ( p_nomObj ) != 0 )
		{
			printf( "Error caso 5: el nombre no deberia darse por valido con un blanco dentro\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Un nombre que no empieza por letra tampoco es valido. */
		if ( SNomEstablecerLit ( p_nomObj, "1nombre" ) != 0 )
		{
			printf( "Error caso 6: se esperaba resultado 0 con un nombre que empieza por digito\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Limpiar deja el nombre vacio. */
		SNomLimpiar ( p_nomObj );
		if ( SNomEstaVacio ( p_nomObj ) != 1 )
		{
			printf( "Error caso 7: el nombre deberia estar vacio tras limpiar\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el nombre\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SNomDestruir ( &p_nomObj );
	return ( iRes );
}

static int TestSNomCrearValor01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SNomCrearValor 01:\n" );

	/* El tope por defecto es NOM_MAX_TAM_DEF. */
	SNombre * p_nomDef = SNomCrearDef ();
	if ( ES_VALIDO ( p_nomDef ) )
	{
		if ( SNomMaxLongitud ( p_nomDef ) != NOM_MAX_TAM_DEF )
		{
			printf( "Error caso 1: la longitud maxima por defecto deberia ser %d: %d\n",
					NOM_MAX_TAM_DEF, SNomMaxLongitud ( p_nomDef ) );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el nombre por defecto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SNomDestruir ( &p_nomDef );

	/* Con valor, el tope se ajusta a la longitud del valor. */
	SNombre * p_nomObj = SNomCrearValorLit ( "importe_total" );
	if ( ES_VALIDO ( p_nomObj ) )
	{
		if ( SNomEsIgualLit ( p_nomObj, "importe_total" ) != 1 )
		{
			printf( "Error caso 2: se esperaba \"importe_total\": [%s]\n", SNomValorLit ( p_nomObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SNomMaxLongitud ( p_nomObj ) != 13 )
		{
			printf( "Error caso 3: la longitud maxima deberia ser 13: %d\n", SNomMaxLongitud ( p_nomObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SNomEsValido ( p_nomObj ) != 1 )
		{
			printf( "Error caso 4: \"importe_total\" deberia ser un nombre valido\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el nombre con valor\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SNomDestruir ( &p_nomObj );

	/* Un valor que no supera la validacion no llega a crear el objeto. */
	SNombre * p_nomMal = SNomCrearValorLit ( "con espacio" );
	if ( ES_VALIDO ( p_nomMal ) )
	{
		printf( "Error caso 5: un nombre con espacios no deberia crearse\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SNomDestruir ( &p_nomMal );

	/* La variante Ext fija el tope aparte del valor. */
	SNombre * p_nomExt = SNomCrearValorLitExt ( "Juan", 30 );
	if ( ES_VALIDO ( p_nomExt ) )
	{
		if ( SNomMaxLongitud ( p_nomExt ) != 30 )
		{
			printf( "Error caso 6: la longitud maxima deberia ser 30: %d\n", SNomMaxLongitud ( p_nomExt ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SNomLongitud ( p_nomExt ) != 4 )
		{
			printf( "Error caso 7: la longitud deberia ser 4: %d\n", SNomLongitud ( p_nomExt ) );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el nombre con valor y tope\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SNomDestruir ( &p_nomExt );
	return ( iRes );
}

static int TestSNomComparaciones01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SNomComparaciones 01:\n" );

	SNombre * p_nomA = SNomCrearValorLitExt ( "Ana", 30 );
	SNombre * p_nomB = SNomCrearValorLitExt ( "Bea", 30 );
	if ( ES_VALIDO ( p_nomA ) && ES_VALIDO ( p_nomB ) )
	{
		if ( SNomEsMenor ( p_nomA, p_nomB ) != 1 )
		{
			printf( "Error caso 1: \"Ana\" deberia ser menor que \"Bea\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SNomEsMayor ( p_nomB, p_nomA ) != 1 )
		{
			printf( "Error caso 2: \"Bea\" deberia ser mayor que \"Ana\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SNomEsIgual ( p_nomA, p_nomB ) != 0 )
		{
			printf( "Error caso 3: \"Ana\" y \"Bea\" no deberian ser iguales\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SNomEsDiferente ( p_nomA, p_nomB ) != 1 )
		{
			printf( "Error caso 4: \"Ana\" y \"Bea\" deberian ser diferentes\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SNomEsIgualLit ( p_nomA, "Ana" ) != 1 )
		{
			printf( "Error caso 5: \"Ana\" deberia ser igual al literal \"Ana\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SNomEsMenorCad ( p_nomA, SNomValor ( p_nomB ) ) != 1 )
		{
			printf( "Error caso 6: \"Ana\" deberia ser menor que la cadena \"Bea\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SNomComparar ( p_nomA, p_nomB ) != COMP_MENOR )
		{
			printf( "Error caso 7: se esperaba COMP_MENOR: %d\n", SNomComparar ( p_nomA, p_nomB ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SNomComparar ( p_nomB, p_nomA ) != COMP_MAYOR )
		{
			printf( "Error caso 8: se esperaba COMP_MAYOR: %d\n", SNomComparar ( p_nomB, p_nomA ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SNomComparar ( p_nomA, p_nomA ) != COMP_IGUAL )
		{
			printf( "Error caso 9: se esperaba COMP_IGUAL: %d\n", SNomComparar ( p_nomA, p_nomA ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SNomCompararLit ( p_nomA, "Ana" ) != COMP_IGUAL )
		{
			printf( "Error caso 10: se esperaba COMP_IGUAL contra el literal\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SNomCompararCad ( p_nomA, SNomValor ( p_nomB ) ) != COMP_MENOR )
		{
			printf( "Error caso 11: se esperaba COMP_MENOR contra la cadena\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SNomComparar ( p_nomA, NULL ) != COMP_MAYOR )
		{
			printf( "Error caso 12: un nombre valido deberia ser mayor que uno nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SNomComparar ( NULL, p_nomB ) != COMP_MENOR )
		{
			printf( "Error caso 13: un nombre nulo deberia ser menor que uno valido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SNomComparar ( NULL, NULL ) != COMP_IGUAL )
		{
			printf( "Error caso 14: dos nombres nulos deberian ser iguales\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SNomCumpleExpReg ( p_nomA, "An?" ) != 1 )
		{
			printf( "Error caso 15: \"Ana\" deberia cumplir el patron \"An?\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear los nombres\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SNomDestruir ( &p_nomA );
	SNomDestruir ( &p_nomB );
	return ( iRes );
}

static int TestSNomCampo01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SNomCampo 01:\n" );

	SNombre * p_nomObj = SNomCrearValorLitExt ( "Ana", 30 );
	SCampo * p_campObj = SCampCrear ( SCadEsNombreValido, 30 );
	if ( ES_VALIDO ( p_nomObj ) && ES_VALIDO ( p_campObj ) &&
		 ( SCampEstablecerLit ( p_campObj, "Bea" ) == 1 ) )
	{
		if ( SNomEsMenorCampo ( p_nomObj, p_campObj ) != 1 )
		{
			printf( "Error caso 1: \"Ana\" deberia ser menor que el campo \"Bea\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SNomEsMayorCampo ( p_nomObj, p_campObj ) != 0 )
		{
			printf( "Error caso 2: \"Ana\" no deberia ser mayor que el campo \"Bea\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SNomEsIgualCampo ( p_nomObj, p_campObj ) != 0 )
		{
			printf( "Error caso 3: \"Ana\" y el campo \"Bea\" no deberian ser iguales\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SNomEsDiferenteCampo ( p_nomObj, p_campObj ) != 1 )
		{
			printf( "Error caso 4: \"Ana\" y el campo \"Bea\" deberian ser diferentes\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SNomCompararCampo ( p_nomObj, p_campObj ) != COMP_MENOR )
		{
			printf( "Error caso 5: se esperaba COMP_MENOR contra el campo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SNomAsignarCampo ( p_nomObj, p_campObj ) != 1 )
		{
			printf( "Error caso 6: se esperaba resultado 1 al asignar desde el campo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SNomEsIgualCampo ( p_nomObj, p_campObj ) != 1 )
		{
			printf( "Error caso 7: el nombre deberia ser igual al campo tras asignarlo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SNomCompararCampo ( p_nomObj, NULL ) != COMP_MAYOR )
		{
			printf( "Error caso 8: un nombre valido deberia ser mayor que un campo nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron preparar el nombre y el campo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SNomDestruir ( &p_nomObj );
	SCampDestruir ( &p_campObj );
	return ( iRes );
}

static int TestSNomAsignarDuplicar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SNomAsignarDuplicar 01:\n" );

	SNombre * p_nomObj = SNomCrearValorLitExt ( "Original", 30 );
	if ( ES_VALIDO ( p_nomObj ) )
	{
		SNombre * p_nomCopia = SNomDuplicar ( p_nomObj );
		if ( ES_VALIDO ( p_nomCopia ) )
		{
			if ( SNomEsIgual ( p_nomCopia, p_nomObj ) != 1 )
			{
				printf( "Error caso 1: la copia deberia ser igual al original\n" );
				iRes = BOOL_VAL_FALSO;
			}
			if ( SNomMaxLongitud ( p_nomCopia ) != SNomMaxLongitud ( p_nomObj ) )
			{
				printf( "Error caso 2: la copia deberia conservar la longitud maxima\n" );
				iRes = BOOL_VAL_FALSO;
			}
			SNomLimpiar ( p_nomCopia );
			if ( SNomEstaVacio ( p_nomObj ) != 0 )
			{
				printf( "Error caso 3: limpiar la copia no deberia vaciar el original\n" );
				iRes = BOOL_VAL_FALSO;
			}
			if ( SNomAsignar ( p_nomCopia, p_nomObj ) != 1 )
			{
				printf( "Error caso 4: se esperaba resultado 1 al asignar\n" );
				iRes = BOOL_VAL_FALSO;
			}
			if ( SNomEsIgual ( p_nomCopia, p_nomObj ) != 1 )
			{
				printf( "Error caso 5: la copia deberia volver a ser igual al original\n" );
				iRes = BOOL_VAL_FALSO;
			}
		}
		else
		{
			printf( "Error caso 0: no se pudo duplicar el nombre\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SNomDestruir ( &p_nomCopia );
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el nombre\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SNomDestruir ( &p_nomObj );

	if ( ES_VALIDO ( SNomDuplicar ( NULL ) ) )
	{
		printf( "Error caso 6: duplicar un nombre nulo deberia devolver nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}



int TestSNombre ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SNombre]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSNomCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSNomEstablecer01 () == BOOL_VAL_CIERTO ) &&
			( TestSNomCrearValor01 () == BOOL_VAL_CIERTO ) &&
			( TestSNomComparaciones01 () == BOOL_VAL_CIERTO ) &&
			( TestSNomCampo01 () == BOOL_VAL_CIERTO ) &&
			( TestSNomAsignarDuplicar01 () == BOOL_VAL_CIERTO ) )
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
