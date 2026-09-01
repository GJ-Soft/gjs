#include "Base.h"

#include "SDescripcion.h"
#include "ValidacionCadenas.h"
#include "TextoConstantes.h"



static int TestSDescCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SDescCrear 01:\n" );

	SDescripcion * p_descObj = SDescCrear ( 50 );
	if ( ES_NULO ( p_descObj ) )
	{
		printf( "Error caso 1: no se esperaba nulo al crear\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SDescEstaVacia ( p_descObj ) != 1 )
		{
			printf( "Error caso 2: la descripcion recien creada deberia estar vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SDescLongitud ( p_descObj ) != 0 )
		{
			printf( "Error caso 3: la longitud inicial deberia ser 0: %d\n", SDescLongitud ( p_descObj ) );
			iRes = BOOL_VAL_FALSO;
		}
	}
	SDescDestruir ( &p_descObj );

	if ( ES_VALIDO ( p_descObj ) )
	{
		printf( "Error caso 4: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSDescEstablecer01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SDescEstablecer 01:\n" );

	SDescripcion * p_descObj = SDescCrear ( 50 );
	if ( ES_VALIDO ( p_descObj ) )
	{
		/* Una descripcion admite espacios. */
		if ( SDescEstablecerLit ( p_descObj, "Una descripcion" ) != 1 )
		{
			printf( "Error caso 1: se esperaba resultado 1 al establecer la descripcion\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SDescEstaVacia ( p_descObj ) != 0 )
		{
			printf( "Error caso 2: la descripcion no deberia estar vacia tras establecerla\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( CadComparar ( (char *) SDescValorLit ( p_descObj ), "Una descripcion" ) != COMP_IGUAL )
		{
			printf( "Error caso 3: se esperaba \"Una descripcion\": [%s]\n", SDescValorLit ( p_descObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SDescLongitud ( p_descObj ) != 15 )
		{
			printf( "Error caso 4: la longitud deberia ser 15: %d\n", SDescLongitud ( p_descObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		SDescLimpiar ( p_descObj );
		if ( SDescEstaVacia ( p_descObj ) != 1 )
		{
			printf( "Error caso 5: la descripcion deberia estar vacia tras limpiar\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la descripcion\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SDescDestruir ( &p_descObj );
	return ( iRes );
}

static int TestSDescCrearValor01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SDescCrearValor 01:\n" );

	/* El tope por defecto es DESC_MAX_TAM_DEF, no el de los nombres. */
	SDescripcion * p_descDef = SDescCrearDef ();
	if ( ES_VALIDO ( p_descDef ) )
	{
		if ( SDescMaxLongitud ( p_descDef ) != DESC_MAX_TAM_DEF )
		{
			printf( "Error caso 1: la longitud maxima por defecto deberia ser %d: %d\n",
					DESC_MAX_TAM_DEF, SDescMaxLongitud ( p_descDef ) );
			iRes = BOOL_VAL_FALSO;
		}
		/* Una descripcion vacia si es valida: no se le exige longitud. */
		if ( SDescEsValida ( p_descDef ) != 1 )
		{
			printf( "Error caso 2: una descripcion vacia deberia ser valida\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la descripcion por defecto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SDescDestruir ( &p_descDef );

	SDescripcion * p_descObj = SDescCrearValorLit ( "Una descripcion" );
	if ( ES_VALIDO ( p_descObj ) )
	{
		if ( SDescEsIgualLit ( p_descObj, "Una descripcion" ) != 1 )
		{
			printf( "Error caso 3: se esperaba \"Una descripcion\": [%s]\n", SDescValorLit ( p_descObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SDescMaxLongitud ( p_descObj ) != 15 )
		{
			printf( "Error caso 4: la longitud maxima deberia ser 15: %d\n", SDescMaxLongitud ( p_descObj ) );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la descripcion con valor\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SDescDestruir ( &p_descObj );

	/* Un salto de linea no es imprimible, asi que no supera la validacion. */
	SDescripcion * p_descMal = SDescCrearValorLit ( "primera\nsegunda" );
	if ( ES_VALIDO ( p_descMal ) )
	{
		printf( "Error caso 5: una descripcion con salto de linea no deberia crearse\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SDescDestruir ( &p_descMal );

	SDescripcion * p_descExt = SDescCrearValorLitExt ( "Corta", 50 );
	if ( ES_VALIDO ( p_descExt ) )
	{
		if ( SDescMaxLongitud ( p_descExt ) != 50 )
		{
			printf( "Error caso 6: la longitud maxima deberia ser 50: %d\n", SDescMaxLongitud ( p_descExt ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SDescLongitud ( p_descExt ) != 5 )
		{
			printf( "Error caso 7: la longitud deberia ser 5: %d\n", SDescLongitud ( p_descExt ) );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la descripcion con valor y tope\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SDescDestruir ( &p_descExt );
	return ( iRes );
}

static int TestSDescComparaciones01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SDescComparaciones 01:\n" );

	SDescripcion * p_descA = SDescCrearValorLitExt ( "Aaa", 50 );
	SDescripcion * p_descB = SDescCrearValorLitExt ( "Bbb", 50 );
	if ( ES_VALIDO ( p_descA ) && ES_VALIDO ( p_descB ) )
	{
		if ( SDescEsMenor ( p_descA, p_descB ) != 1 )
		{
			printf( "Error caso 1: \"Aaa\" deberia ser menor que \"Bbb\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SDescEsMayor ( p_descB, p_descA ) != 1 )
		{
			printf( "Error caso 2: \"Bbb\" deberia ser mayor que \"Aaa\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SDescEsIgual ( p_descA, p_descB ) != 0 )
		{
			printf( "Error caso 3: \"Aaa\" y \"Bbb\" no deberian ser iguales\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SDescEsDiferente ( p_descA, p_descB ) != 1 )
		{
			printf( "Error caso 4: \"Aaa\" y \"Bbb\" deberian ser diferentes\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SDescEsIgualLit ( p_descA, "Aaa" ) != 1 )
		{
			printf( "Error caso 5: \"Aaa\" deberia ser igual al literal \"Aaa\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SDescEsMenorCad ( p_descA, SDescValor ( p_descB ) ) != 1 )
		{
			printf( "Error caso 6: \"Aaa\" deberia ser menor que la cadena \"Bbb\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SDescComparar ( p_descA, p_descB ) != COMP_MENOR )
		{
			printf( "Error caso 7: se esperaba COMP_MENOR: %d\n", SDescComparar ( p_descA, p_descB ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SDescComparar ( p_descB, p_descA ) != COMP_MAYOR )
		{
			printf( "Error caso 8: se esperaba COMP_MAYOR: %d\n", SDescComparar ( p_descB, p_descA ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SDescComparar ( p_descA, p_descA ) != COMP_IGUAL )
		{
			printf( "Error caso 9: se esperaba COMP_IGUAL: %d\n", SDescComparar ( p_descA, p_descA ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SDescCompararLit ( p_descA, "Aaa" ) != COMP_IGUAL )
		{
			printf( "Error caso 10: se esperaba COMP_IGUAL contra el literal\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SDescCompararCad ( p_descA, SDescValor ( p_descB ) ) != COMP_MENOR )
		{
			printf( "Error caso 11: se esperaba COMP_MENOR contra la cadena\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SDescComparar ( p_descA, NULL ) != COMP_MAYOR )
		{
			printf( "Error caso 12: una descripcion valida deberia ser mayor que una nula\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SDescComparar ( NULL, p_descB ) != COMP_MENOR )
		{
			printf( "Error caso 13: una descripcion nula deberia ser menor que una valida\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SDescComparar ( NULL, NULL ) != COMP_IGUAL )
		{
			printf( "Error caso 14: dos descripciones nulas deberian ser iguales\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SDescCumpleExpReg ( p_descA, "Aa?" ) != 1 )
		{
			printf( "Error caso 15: \"Aaa\" deberia cumplir el patron \"Aa?\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear las descripciones\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SDescDestruir ( &p_descA );
	SDescDestruir ( &p_descB );
	return ( iRes );
}

static int TestSDescCampo01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SDescCampo 01:\n" );

	SDescripcion * p_descObj = SDescCrearValorLitExt ( "Aaa", 50 );
	SCampo * p_campObj = SCampCrear ( SCadEsDescripcionValida, 50 );
	if ( ES_VALIDO ( p_descObj ) && ES_VALIDO ( p_campObj ) &&
		 ( SCampEstablecerLit ( p_campObj, "Bbb" ) == 1 ) )
	{
		if ( SDescEsMenorCampo ( p_descObj, p_campObj ) != 1 )
		{
			printf( "Error caso 1: \"Aaa\" deberia ser menor que el campo \"Bbb\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SDescEsMayorCampo ( p_descObj, p_campObj ) != 0 )
		{
			printf( "Error caso 2: \"Aaa\" no deberia ser mayor que el campo \"Bbb\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SDescEsIgualCampo ( p_descObj, p_campObj ) != 0 )
		{
			printf( "Error caso 3: \"Aaa\" y el campo \"Bbb\" no deberian ser iguales\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SDescEsDiferenteCampo ( p_descObj, p_campObj ) != 1 )
		{
			printf( "Error caso 4: \"Aaa\" y el campo \"Bbb\" deberian ser diferentes\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SDescCompararCampo ( p_descObj, p_campObj ) != COMP_MENOR )
		{
			printf( "Error caso 5: se esperaba COMP_MENOR contra el campo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SDescAsignarCampo ( p_descObj, p_campObj ) != 1 )
		{
			printf( "Error caso 6: se esperaba resultado 1 al asignar desde el campo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SDescEsIgualCampo ( p_descObj, p_campObj ) != 1 )
		{
			printf( "Error caso 7: la descripcion deberia ser igual al campo tras asignarlo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SDescCompararCampo ( p_descObj, NULL ) != COMP_MAYOR )
		{
			printf( "Error caso 8: una descripcion valida deberia ser mayor que un campo nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron preparar la descripcion y el campo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SDescDestruir ( &p_descObj );
	SCampDestruir ( &p_campObj );
	return ( iRes );
}

static int TestSDescAsignarDuplicar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SDescAsignarDuplicar 01:\n" );

	SDescripcion * p_descObj = SDescCrearValorLitExt ( "Descripcion original", 50 );
	if ( ES_VALIDO ( p_descObj ) )
	{
		SDescripcion * p_descCopia = SDescDuplicar ( p_descObj );
		if ( ES_VALIDO ( p_descCopia ) )
		{
			if ( SDescEsIgual ( p_descCopia, p_descObj ) != 1 )
			{
				printf( "Error caso 1: la copia deberia ser igual al original\n" );
				iRes = BOOL_VAL_FALSO;
			}
			if ( SDescMaxLongitud ( p_descCopia ) != SDescMaxLongitud ( p_descObj ) )
			{
				printf( "Error caso 2: la copia deberia conservar la longitud maxima\n" );
				iRes = BOOL_VAL_FALSO;
			}
			SDescLimpiar ( p_descCopia );
			if ( SDescEstaVacia ( p_descObj ) != 0 )
			{
				printf( "Error caso 3: limpiar la copia no deberia vaciar el original\n" );
				iRes = BOOL_VAL_FALSO;
			}
			if ( SDescAsignar ( p_descCopia, p_descObj ) != 1 )
			{
				printf( "Error caso 4: se esperaba resultado 1 al asignar\n" );
				iRes = BOOL_VAL_FALSO;
			}
			if ( SDescEsIgual ( p_descCopia, p_descObj ) != 1 )
			{
				printf( "Error caso 5: la copia deberia volver a ser igual al original\n" );
				iRes = BOOL_VAL_FALSO;
			}
		}
		else
		{
			printf( "Error caso 0: no se pudo duplicar la descripcion\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SDescDestruir ( &p_descCopia );
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la descripcion\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SDescDestruir ( &p_descObj );

	if ( ES_VALIDO ( SDescDuplicar ( NULL ) ) )
	{
		printf( "Error caso 6: duplicar una descripcion nula deberia devolver nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}



int TestSDescripcion ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SDescripcion]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSDescCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSDescEstablecer01 () == BOOL_VAL_CIERTO ) &&
			( TestSDescCrearValor01 () == BOOL_VAL_CIERTO ) &&
			( TestSDescComparaciones01 () == BOOL_VAL_CIERTO ) &&
			( TestSDescCampo01 () == BOOL_VAL_CIERTO ) &&
			( TestSDescAsignarDuplicar01 () == BOOL_VAL_CIERTO ) )
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
