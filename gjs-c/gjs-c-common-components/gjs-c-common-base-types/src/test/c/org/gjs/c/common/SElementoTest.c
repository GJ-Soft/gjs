#include "Base.h"

#include "SElemento.h"



static int TestSElmCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SElmCrear 01:\n" );

	SElemento * p_elmObj = SElmCrear ( 8 );
	if ( ES_NULO ( p_elmObj ) )
	{
		printf( "Error caso 1: no se esperaba nulo al crear\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SElmEsValido ( p_elmObj ) != 1 )
		{
			printf( "Error caso 2: el elemento recien creado deberia ser valido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SElmTieneDatos ( p_elmObj ) != 1 )
		{
			printf( "Error caso 3: el elemento deberia tener datos\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Un elemento recien creado no esta encadenado. */
		if ( SElmTieneAntecesor ( p_elmObj ) != 0 )
		{
			printf( "Error caso 4: no deberia tener antecesor\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SElmTieneSucesor ( p_elmObj ) != 0 )
		{
			printf( "Error caso 5: no deberia tener sucesor\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	SElmDestruir ( &p_elmObj );

	if ( ES_VALIDO ( p_elmObj ) )
	{
		printf( "Error caso 6: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* Crear con tam 0 debe fallar. */
	if ( ES_VALIDO ( SElmCrear ( 0 ) ) )
	{
		printf( "Error caso 7: se esperaba nulo al crear con tam 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSElmEnteros01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SElmEnteros 01:\n" );

	SElemento * p_elmObj = SElmCrearEntero ();
	if ( ES_VALIDO ( p_elmObj ) )
	{
		if ( SElmEscribirEntero ( p_elmObj, 4321 ) != 1 )
		{
			printf( "Error caso 1: se esperaba resultado 1 al escribir entero\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SElmEntero ( p_elmObj ) != 4321 )
		{
			printf( "Error caso 2: se esperaba 4321: %d\n", SElmEntero ( p_elmObj ) );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el elemento entero\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SElmDestruir ( &p_elmObj );

	/* Roundtrip de real doble. */
	SElemento * p_elmReal = SElmCrearRealDoble ();
	if ( ES_VALIDO ( p_elmReal ) )
	{
		SElmEscribirRealDoble ( p_elmReal, 3.5 );
		if ( SElmRealDoble ( p_elmReal ) != 3.5 )
		{
			printf( "Error caso 3: se esperaba 3.5 en el real doble\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	SElmDestruir ( &p_elmReal );
	return ( iRes );
}

static int TestSElmEncapsular01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SElmEncapsular 01:\n" );

	/* Encapsular un bloque: el elemento pasa a gestionarlo. */
	SBloque * p_blqObj = SBlqCrear ( 4 );
	if ( ES_VALIDO ( p_blqObj ) )
	{
		SElemento * p_elmObj = SElmEncapsular ( p_blqObj );
		if ( ES_NULO ( p_elmObj ) )
		{
			printf( "Error caso 1: no se esperaba nulo al encapsular\n" );
			iRes = BOOL_VAL_FALSO;
			SBlqDestruir ( &p_blqObj );
		}
		else
		{
			if ( SElmDatos ( p_elmObj ) != p_blqObj )
			{
				printf( "Error caso 2: el elemento deberia envolver el bloque dado\n" );
				iRes = BOOL_VAL_FALSO;
			}
			/* El elemento gestiona el bloque: destruirlo lo libera tambien. */
			SElmDestruir ( &p_elmObj );
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el bloque\n" );
		iRes = BOOL_VAL_FALSO;
	}

	/* Encapsular memoria externa sin cederla ( iLiberar = 0 ). */
	byte * p_byDatos = (byte *) MemReservar ( 4 );
	if ( ES_VALIDO ( p_byDatos ) )
	{
		p_byDatos [ 0 ] = 0x33;
		SElemento * p_elmDir = SElmEncapsularDir ( p_byDatos, 4, 0 );
		if ( ES_VALIDO ( p_elmDir ) )
		{
			if ( SElmLiberacionMemoriaActivada ( p_elmDir ) != 0 )
			{
				printf( "Error caso 3: la liberacion de memoria no deberia estar activada\n" );
				iRes = BOOL_VAL_FALSO;
			}
			SElmDestruir ( &p_elmDir );
			/* La memoria externa debe seguir siendo valida. */
			if ( p_byDatos [ 0 ] != 0x33 )
			{
				printf( "Error caso 4: la memoria externa no deberia haberse alterado\n" );
				iRes = BOOL_VAL_FALSO;
			}
		}
		MemLiberar ( (void **) &p_byDatos );
	}
	return ( iRes );
}

static int TestSElmEncadenar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SElmEncadenar 01:\n" );

	SElemento * p_elmA = SElmCrearEntero ();
	SElemento * p_elmB = SElmCrearEntero ();
	if ( ES_VALIDO ( p_elmA ) && ES_VALIDO ( p_elmB ) )
	{
		/* Encadenar B como sucesor de A enlaza ambos sentidos. */
		if ( SElmEncadenarSucesor ( p_elmA, p_elmB ) != 1 )
		{
			printf( "Error caso 1: se esperaba resultado 1 al encadenar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SElmSucesor ( p_elmA ) != p_elmB )
		{
			printf( "Error caso 2: B deberia ser el sucesor de A\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SElmAntecesor ( p_elmB ) != p_elmA )
		{
			printf( "Error caso 3: A deberia ser el antecesor de B\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Encadenar un antecesor NULL debe dejar el enlace a NULL ( no ser un no-op ). */
		SElmEncadenarAntecesor ( p_elmB, NULL );
		if ( SElmTieneAntecesor ( p_elmB ) != 0 )
		{
			printf( "Error caso 4: B no deberia tener antecesor tras encadenar NULL\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( SElmAntecesor ( p_elmB ) ) )
		{
			printf( "Error caso 5: el antecesor de B deberia ser nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Encadenar un sucesor NULL en A tambien limpia el enlace. */
		SElmEncadenarSucesor ( p_elmA, NULL );
		if ( SElmTieneSucesor ( p_elmA ) != 0 )
		{
			printf( "Error caso 6: A no deberia tener sucesor tras encadenar NULL\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear los elementos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SElmDestruir ( &p_elmA );
	SElmDestruir ( &p_elmB );
	return ( iRes );
}

static int TestSElmDesencadenar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SElmDesencadenar 01:\n" );

	SElemento * p_elmA = SElmCrearEntero ();
	SElemento * p_elmB = SElmCrearEntero ();
	if ( ES_VALIDO ( p_elmA ) && ES_VALIDO ( p_elmB ) )
	{
		SElmEncadenarSucesor ( p_elmA, p_elmB );

		/* Desencadenar desliga el elemento de sus vecinos ( y no debe colgarse ). */
		SElmDesencadenar ( p_elmA );
		if ( SElmTieneSucesor ( p_elmA ) != 0 )
		{
			printf( "Error caso 1: A no deberia tener sucesor tras desencadenar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SElmTieneAntecesor ( p_elmB ) != 0 )
		{
			printf( "Error caso 2: B no deberia tener antecesor tras desencadenar A\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear los elementos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SElmDestruir ( &p_elmA );
	SElmDestruir ( &p_elmB );
	return ( iRes );
}

static int TestSElmIgualdad01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SElmIgualdad 01:\n" );

	SElemento * p_elmA = SElmCrearEntero ();
	SElemento * p_elmB = SElmCrearEntero ();
	if ( ES_VALIDO ( p_elmA ) && ES_VALIDO ( p_elmB ) )
	{
		SElmEscribirEntero ( p_elmA, 100 );
		SElmEscribirEntero ( p_elmB, 100 );
		if ( SElmEsIgual ( p_elmA, p_elmB ) != 1 )
		{
			printf( "Error caso 1: los elementos deberian ser iguales\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SElmEscribirEntero ( p_elmB, 200 );
		if ( SElmEsIgual ( p_elmA, p_elmB ) != 0 )
		{
			printf( "Error caso 2: los elementos no deberian ser iguales\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear los elementos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SElmDestruir ( &p_elmA );
	SElmDestruir ( &p_elmB );
	return ( iRes );
}

static int TestSElmDuplicar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SElmDuplicar 01:\n" );

	SElemento * p_elmObj = SElmCrearEntero ();
	if ( ES_VALIDO ( p_elmObj ) )
	{
		SElmEscribirEntero ( p_elmObj, 777 );

		SElemento * p_elmDup = SElmDuplicar ( p_elmObj );
		if ( ES_NULO ( p_elmDup ) )
		{
			printf( "Error caso 1: no se esperaba nulo al duplicar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		else
		{
			if ( SElmEntero ( p_elmDup ) != 777 )
			{
				printf( "Error caso 2: el duplicado deberia contener 777\n" );
				iRes = BOOL_VAL_FALSO;
			}
			/* Copia independiente: modificar el original no afecta al duplicado. */
			SElmEscribirEntero ( p_elmObj, 888 );
			if ( SElmEntero ( p_elmDup ) != 777 )
			{
				printf( "Error caso 3: el duplicado no deberia compartir datos con el original\n" );
				iRes = BOOL_VAL_FALSO;
			}
			/* Destruir ambos no debe provocar un doble free ( datos independientes ). */
			SElmDestruir ( &p_elmDup );
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el elemento\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SElmDestruir ( &p_elmObj );
	return ( iRes );
}

static int TestSElmInvalidos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SElmInvalidos 01:\n" );

	if ( SElmEsValido ( NULL ) != 0 )
	{
		printf( "Error caso 1: un elemento nulo no deberia ser valido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( SElmDatos ( NULL ) ) )
	{
		printf( "Error caso 2: los datos de un elemento nulo deberian ser nulos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SElmEscribirEntero ( NULL, 1 ) != 0 )
	{
		printf( "Error caso 3: escribir en elemento nulo deberia fallar\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SElemento * p_elmNulo = NULL;
	SElmDestruir ( &p_elmNulo );
	return ( iRes );
}





/* Los saltos de mas de un eslabon. El caso de iInc = 2 en adelante es el que
   importa: la primera version de estas funciones avanzaba siempre desde el
   elemento original en vez de desde el que ya habia alcanzado, con lo que
   acababa en el vecino inmediato para cualquier iInc. Con iInc = 1 eso da el
   resultado bueno, asi que un test que solo probase el vecino no habria
   detectado nada. */
static int TestSElmAntecesorSucesorExt01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SElmAntecesorSucesorExt 01:\n" );

	/* Cadena de cuatro: A - B - C - D */
	SElemento * p_A = SElmCrearEntero ();
	SElemento * p_B = SElmCrearEntero ();
	SElemento * p_C = SElmCrearEntero ();
	SElemento * p_D = SElmCrearEntero ();
	if ( ES_VALIDO ( p_A ) && ES_VALIDO ( p_B ) && ES_VALIDO ( p_C ) && ES_VALIDO ( p_D ) )
	{
		SElmEncadenarSucesor ( p_A, p_B );
		SElmEncadenarSucesor ( p_B, p_C );
		SElmEncadenarSucesor ( p_C, p_D );

		/* Un solo eslabon: lo mismo que las versiones simples. */
		if ( SElmSucesorExt ( p_A, 1 ) != p_B )
		{
			printf( "Error caso 1: a un eslabon de A deberia estar B\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SElmAntecesorExt ( p_D, 1 ) != p_C )
		{
			printf( "Error caso 2: a un eslabon hacia atras de D deberia estar C\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Dos y tres: aqui es donde se ve si avanza de verdad. */
		if ( SElmSucesorExt ( p_A, 2 ) != p_C )
		{
			printf( "Error caso 3: a dos eslabones de A deberia estar C\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SElmSucesorExt ( p_A, 3 ) != p_D )
		{
			printf( "Error caso 4: a tres eslabones de A deberia estar D\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SElmAntecesorExt ( p_D, 3 ) != p_A )
		{
			printf( "Error caso 5: a tres eslabones hacia atras de D deberia estar A\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Salirse de la cadena da nulo, no el ultimo ni basura. */
		if ( ES_VALIDO ( SElmSucesorExt ( p_A, 4 ) ) )
		{
			printf( "Error caso 6: pasado el final deberia dar nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( SElmAntecesorExt ( p_A, 1 ) ) )
		{
			printf( "Error caso 7: A no tiene antecesor\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Cero eslabones es el propio elemento; negativo, nulo. */
		if ( SElmSucesorExt ( p_B, 0 ) != p_B )
		{
			printf( "Error caso 8: con iInc = 0 se espera el propio elemento\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SElmAntecesorExt ( p_B, 0 ) != p_B )
		{
			printf( "Error caso 8b: con iInc = 0 se espera el propio elemento\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( SElmAntecesorExt ( p_B, -1 ) ) )
		{
			printf( "Error caso 9: con iInc negativo se espera nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Objeto invalido. */
		if ( ES_VALIDO ( SElmSucesorExt ( NULL, 1 ) ) )
		{
			printf( "Error caso 10: con objeto nulo se espera nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear los cuatro elementos\n" );
		iRes = BOOL_VAL_FALSO;
	}
		SElmDestruir ( &p_A );
	SElmDestruir ( &p_B );
	SElmDestruir ( &p_C );
	SElmDestruir ( &p_D );
	ErrLimpiar ();
	return ( iRes );
}


int TestSElemento ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SElemento]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSElmCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSElmEnteros01 () == BOOL_VAL_CIERTO ) &&
			( TestSElmEncapsular01 () == BOOL_VAL_CIERTO ) &&
			( TestSElmEncadenar01 () == BOOL_VAL_CIERTO ) &&
			( TestSElmDesencadenar01 () == BOOL_VAL_CIERTO ) &&
			( TestSElmIgualdad01 () == BOOL_VAL_CIERTO ) &&
			( TestSElmDuplicar01 () == BOOL_VAL_CIERTO ) &&
			( TestSElmInvalidos01 () == BOOL_VAL_CIERTO )  &&
			( TestSElmAntecesorSucesorExt01 () == BOOL_VAL_CIERTO ) )
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
