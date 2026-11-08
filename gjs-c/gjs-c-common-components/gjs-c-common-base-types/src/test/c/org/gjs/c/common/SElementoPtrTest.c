#include "Base.h"

#include "SElementoPtr.h"



static byte * CrearDatoEntero ( int iValor )
{
	int * p_iDato = (int *) MemReservar ( sizeof ( int ) );
	if ( ES_VALIDO ( p_iDato ) )
	{
		*p_iDato = iValor;
	}
	return ( (byte *) p_iDato );
}

static int ValorElp ( SElementoPtr * p_elpObj )
{
	return ( *( (int *) SElpDatos ( p_elpObj ) ) );
}



static int TestSElpCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SElpCrear 01:\n" );

	SElementoPtr * p_elpObj = SElpCrear ( CrearDatoEntero ( 42 ), 1 );
	if ( ES_NULO ( p_elpObj ) )
	{
		printf( "Error caso 1: no se esperaba nulo al crear\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( ( SElpEsValido ( p_elpObj ) != 1 ) || ( ValorElp ( p_elpObj ) != 42 ) )
		{
			printf( "Error caso 2: el elemento deberia ser valido y contener 42\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SElpLiberacionMemoriaActivada ( p_elpObj ) != 1 )
		{
			printf( "Error caso 3: la liberacion de memoria deberia estar activada\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Modificar libera los datos anteriores y guarda los nuevos. */
		if ( ( SElpModificar ( p_elpObj, CrearDatoEntero ( 99 ), 1 ) != 1 ) || ( ValorElp ( p_elpObj ) != 99 ) )
		{
			printf( "Error caso 4: modificar deberia dejar el valor en 99\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	SElpDestruir ( &p_elpObj );

	if ( ES_VALIDO ( p_elpObj ) )
	{
		printf( "Error caso 5: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* Crear con datos nulos debe fallar. */
	if ( ES_VALIDO ( SElpCrear ( NULL, 0 ) ) )
	{
		printf( "Error caso 6: se esperaba nulo al crear con datos nulos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSElpEncadenar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SElpEncadenar 01:\n" );

	SElementoPtr * p_a = SElpCrear ( CrearDatoEntero ( 1 ), 1 );
	SElementoPtr * p_b = SElpCrear ( CrearDatoEntero ( 2 ), 1 );
	if ( ES_VALIDO ( p_a ) && ES_VALIDO ( p_b ) )
	{
		/* Encadenar A -> B enlaza en ambos sentidos. */
		if ( SElpEncadenarSucesor ( p_a, p_b ) != 1 )
		{
			printf( "Error caso 1: se esperaba resultado 1 al encadenar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SElpSucesor ( p_a ) != p_b ) || ( SElpAntecesor ( p_b ) != p_a ) )
		{
			printf( "Error caso 2: el enlace deberia ser bidireccional\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SElpTieneSucesor ( p_a ) != 1 ) || ( SElpTieneAntecesor ( p_b ) != 1 ) || ( SElpTieneAntecesor ( p_a ) != 0 ) )
		{
			printf( "Error caso 3: A deberia tener sucesor y B antecesor\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Desencadenar A lo separa de B en ambos sentidos. */
		SElpDesencadenar ( p_a );
		if ( ( SElpTieneSucesor ( p_a ) != 0 ) || ( SElpTieneAntecesor ( p_b ) != 0 ) )
		{
			printf( "Error caso 4: tras desencadenar no deberia quedar enlace\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear los elementos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SElpDestruir ( &p_a );
	SElpDestruir ( &p_b );
	return ( iRes );
}

static int TestSElpEsIgualDuplicar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SElpEsIgualDuplicar 01:\n" );

	SElementoPtr * p_a = SElpCrear ( CrearDatoEntero ( 42 ), 1 );
	byte * p_buf = CrearDatoEntero ( 42 );
	byte * p_buf99 = CrearDatoEntero ( 99 );
	if ( ES_VALIDO ( p_a ) && ES_VALIDO ( p_buf ) && ES_VALIDO ( p_buf99 ) )
	{
		if ( ( SElpEsIgualDatos ( p_a, p_buf, sizeof ( int ) ) != 1 ) ||
			 ( SElpEsIgualDatos ( p_a, p_buf99, sizeof ( int ) ) != 0 ) )
		{
			printf( "Error caso 1: la comparacion de contenido deberia distinguir 42 de 99\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Duplicar copia el CONTENIDO a un bloque propio, que libera el duplicado. */
		SElementoPtr * p_dup = SElpDuplicar ( p_a, sizeof ( int ) );
		if ( ES_NULO ( p_dup ) )
		{
			printf( "Error caso 2: no se esperaba nulo al duplicar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		else
		{
			if ( SElpDatos ( p_dup ) == SElpDatos ( p_a ) )
			{
				printf( "Error caso 3: el duplicado no deberia compartir el bloque de datos\n" );
				iRes = BOOL_VAL_FALSO;
			}
			if ( ValorElp ( p_dup ) != 42 )
			{
				printf( "Error caso 4: el duplicado deberia valer 42: %d\n", ValorElp ( p_dup ) );
				iRes = BOOL_VAL_FALSO;
			}
			if ( SElpLiberacionMemoriaActivada ( p_dup ) != 1 )
			{
				printf( "Error caso 5: el duplicado deberia liberar su copia\n" );
				iRes = BOOL_VAL_FALSO;
			}
			/* Tocar la copia no cambia el original. */
			*( (int *) SElpDatos ( p_dup ) ) = 7;
			if ( ValorElp ( p_a ) != 42 )
			{
				printf( "Error caso 6: modificar el duplicado ha cambiado el original: %d\n", ValorElp ( p_a ) );
				iRes = BOOL_VAL_FALSO;
			}
			SElpDestruir ( &p_dup );
		}
		/* Sin bytes que copiar no hay duplicado. */
		SElementoPtr * p_dup0 = SElpDuplicar ( p_a, 0 );
		if ( ES_VALIDO ( p_dup0 ) )
		{
			printf( "Error caso 7: con 0 bytes se esperaba nulo\n" );
			iRes = BOOL_VAL_FALSO;
			SElpDestruir ( &p_dup0 );
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear el elemento o los buffers\n" );
		iRes = BOOL_VAL_FALSO;
	}
	MemLiberar ( (void **) &p_buf );
	MemLiberar ( (void **) &p_buf99 );
	SElpDestruir ( &p_a );
	ErrLimpiar ();
	return ( iRes );
}

static int SonIgualesEnteros ( byte * p_byDato1, byte * p_byDato2 )
{
	return ( ( *( (int *) p_byDato1 ) == *( (int *) p_byDato2 ) ) ? 1 : 0 );
}

/* Igualdad "modulo 10": distingue las Ext de las que comparan bytes, que con
   12 y 2 darian distinto. */
static int SonIgualesMod10 ( byte * p_byDato1, byte * p_byDato2 )
{
	return ( ( ( *( (int *) p_byDato1 ) % 10 ) == ( *( (int *) p_byDato2 ) % 10 ) ) ? 1 : 0 );
}

/* Duplica sumando 100, para poder ver que la copia la ha hecho esta funcion. */
static byte * DuplicarEnteroMas100 ( byte * p_byDato )
{
	return ( CrearDatoEntero ( *( (int *) p_byDato ) + 100 ) );
}

static int TestSElpEsIgualExt01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SElpEsIgualExt 01:\n" );

	SElementoPtr * p_12 = SElpCrear ( CrearDatoEntero ( 12 ), 1 );
	SElementoPtr * p_2 = SElpCrear ( CrearDatoEntero ( 2 ), 1 );
	SElementoPtr * p_13 = SElpCrear ( CrearDatoEntero ( 13 ), 1 );
	byte * p_buf22 = CrearDatoEntero ( 22 );
	if ( ES_VALIDO ( p_12 ) && ES_VALIDO ( p_2 ) && ES_VALIDO ( p_13 ) && ES_VALIDO ( p_buf22 ) )
	{
		if ( SElpEsIgual ( p_12, p_2, sizeof ( int ) ) != 0 )
		{
			printf( "Error caso 1: por bytes 12 y 2 son distintos\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SElpEsIgualExt ( p_12, p_2, SonIgualesMod10 ) != 1 )
		{
			printf( "Error caso 2: con la comparacion modulo 10, 12 y 2 son iguales\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SElpEsIgualExt ( p_12, p_13, SonIgualesMod10 ) != 0 )
		{
			printf( "Error caso 3: con la comparacion modulo 10, 12 y 13 son distintos\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SElpEsIgualDatosExt ( p_12, p_buf22, SonIgualesMod10 ) != 1 )
		{
			printf( "Error caso 4: con la comparacion modulo 10, 12 y el dato 22 son iguales\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SElpEsIgualDatosExt ( p_12, p_buf22, SonIgualesEnteros ) != 0 )
		{
			printf( "Error caso 5: como enteros, 12 y el dato 22 son distintos\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Sin funcion de comparacion, o con objetos nulos, no hay igualdad. */
		if ( ( SElpEsIgualExt ( p_12, p_12, NULL ) != 0 ) ||
			 ( SElpEsIgualExt ( NULL, p_12, SonIgualesEnteros ) != 0 ) ||
			 ( SElpEsIgualDatosExt ( p_12, NULL, SonIgualesEnteros ) != 0 ) )
		{
			printf( "Error caso 6: con parametros nulos se esperaba 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear los elementos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	MemLiberar ( (void **) &p_buf22 );
	SElpDestruir ( &p_12 );
	SElpDestruir ( &p_2 );
	SElpDestruir ( &p_13 );
	return ( iRes );
}

static int TestSElpDuplicarExt01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SElpDuplicarExt 01:\n" );

	/* El original NO libera ( dato en la pila ): la copia si, porque es suya. */
	int iDato = 5;
	SElementoPtr * p_a = SElpCrear ( (byte *) &iDato, 0 );
	if ( ES_VALIDO ( p_a ) )
	{
		SElementoPtr * p_dup = SElpDuplicarExt ( p_a, DuplicarEnteroMas100 );
		if ( ES_NULO ( p_dup ) )
		{
			printf( "Error caso 1: no se esperaba nulo al duplicar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		else
		{
			if ( ValorElp ( p_dup ) != 105 )
			{
				printf( "Error caso 2: la copia la hace fDuplicar, se esperaba 105: %d\n", ValorElp ( p_dup ) );
				iRes = BOOL_VAL_FALSO;
			}
			if ( SElpLiberacionMemoriaActivada ( p_dup ) != 1 )
			{
				printf( "Error caso 3: el duplicado deberia liberar su copia\n" );
				iRes = BOOL_VAL_FALSO;
			}
			if ( SElpTieneAntecesor ( p_dup ) || SElpTieneSucesor ( p_dup ) )
			{
				printf( "Error caso 4: el duplicado deberia salir desencadenado\n" );
				iRes = BOOL_VAL_FALSO;
			}
			SElpDestruir ( &p_dup );
		}
		if ( ES_VALIDO ( SElpDuplicarExt ( p_a, NULL ) ) )
		{
			printf( "Error caso 5: sin funcion de duplicado se esperaba nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el elemento\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SElpDestruir ( &p_a );
	return ( iRes );
}

static int TestSElpDeposicionar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SElpDeposicionar 01:\n" );

	SElementoPtr * p_A = SElpCrear ( CrearDatoEntero ( 1 ), 1 );
	SElementoPtr * p_B = SElpCrear ( CrearDatoEntero ( 2 ), 1 );
	SElementoPtr * p_C = SElpCrear ( CrearDatoEntero ( 3 ), 1 );
	if ( ES_VALIDO ( p_A ) && ES_VALIDO ( p_B ) && ES_VALIDO ( p_C ) )
	{
		/* A - B - C, y se reengancha A - C a mano, como hace la lista al extraer B. */
		SElpEncadenarSucesor ( p_A, p_B );
		SElpEncadenarSucesor ( p_B, p_C );
		p_A->p_elpSig = (void *) p_C;
		p_C->p_elpAnt = (void *) p_A;

		SElpDeposicionar ( p_B );
		if ( SElpTieneAntecesor ( p_B ) || SElpTieneSucesor ( p_B ) )
		{
			printf( "Error caso 1: B deberia quedar sin enlaces\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Lo que lo distingue de SElpDesencadenar: A - C sigue entero. */
		if ( ( SElpSucesor ( p_A ) != p_C ) || ( SElpAntecesor ( p_C ) != p_A ) )
		{
			printf( "Error caso 2: el enlace A - C no deberia haberse tocado\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SElpDeposicionar ( NULL );
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear los elementos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SElpDestruir ( &p_A );
	SElpDestruir ( &p_B );
	SElpDestruir ( &p_C );
	return ( iRes );
}

static int TestSElpInvalidos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SElpInvalidos 01:\n" );

	if ( SElpEsValido ( NULL ) != 0 )
	{
		printf( "Error caso 1: un elemento nulo no deberia ser valido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( SElpDatos ( NULL ) ) )
	{
		printf( "Error caso 2: los datos de un elemento nulo deberian ser nulos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SElementoPtr * p_elpNulo = NULL;
	SElpDestruir ( &p_elpNulo );
	return ( iRes );
}





/* Los saltos de mas de un eslabon. El caso de iInc = 2 en adelante es el que
   importa: la primera version de estas funciones avanzaba siempre desde el
   elemento original en vez de desde el que ya habia alcanzado, con lo que
   acababa en el vecino inmediato para cualquier iInc. Con iInc = 1 eso da el
   resultado bueno, asi que un test que solo probase el vecino no habria
   detectado nada. */
static int TestSElpAntecesorSucesorExt01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SElpAntecesorSucesorExt 01:\n" );

	/* Cadena de cuatro: A - B - C - D */
	SElementoPtr * p_A = SElpCrear ( CrearDatoEntero ( 1 ), 1 );
	SElementoPtr * p_B = SElpCrear ( CrearDatoEntero ( 1 ), 1 );
	SElementoPtr * p_C = SElpCrear ( CrearDatoEntero ( 1 ), 1 );
	SElementoPtr * p_D = SElpCrear ( CrearDatoEntero ( 1 ), 1 );
	if ( ES_VALIDO ( p_A ) && ES_VALIDO ( p_B ) && ES_VALIDO ( p_C ) && ES_VALIDO ( p_D ) )
	{
		SElpEncadenarSucesor ( p_A, p_B );
		SElpEncadenarSucesor ( p_B, p_C );
		SElpEncadenarSucesor ( p_C, p_D );

		/* Un solo eslabon: lo mismo que las versiones simples. */
		if ( SElpSucesorExt ( p_A, 1 ) != p_B )
		{
			printf( "Error caso 1: a un eslabon de A deberia estar B\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SElpAntecesorExt ( p_D, 1 ) != p_C )
		{
			printf( "Error caso 2: a un eslabon hacia atras de D deberia estar C\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Dos y tres: aqui es donde se ve si avanza de verdad. */
		if ( SElpSucesorExt ( p_A, 2 ) != p_C )
		{
			printf( "Error caso 3: a dos eslabones de A deberia estar C\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SElpSucesorExt ( p_A, 3 ) != p_D )
		{
			printf( "Error caso 4: a tres eslabones de A deberia estar D\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SElpAntecesorExt ( p_D, 3 ) != p_A )
		{
			printf( "Error caso 5: a tres eslabones hacia atras de D deberia estar A\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Salirse de la cadena da nulo, no el ultimo ni basura. */
		if ( ES_VALIDO ( SElpSucesorExt ( p_A, 4 ) ) )
		{
			printf( "Error caso 6: pasado el final deberia dar nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( SElpAntecesorExt ( p_A, 1 ) ) )
		{
			printf( "Error caso 7: A no tiene antecesor\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Cero eslabones es el propio elemento; negativo, nulo. */
		if ( SElpSucesorExt ( p_B, 0 ) != p_B )
		{
			printf( "Error caso 8: con iInc = 0 se espera el propio elemento\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SElpAntecesorExt ( p_B, 0 ) != p_B )
		{
			printf( "Error caso 8b: con iInc = 0 se espera el propio elemento\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( SElpAntecesorExt ( p_B, -1 ) ) )
		{
			printf( "Error caso 9: con iInc negativo se espera nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Objeto invalido. */
		if ( ES_VALIDO ( SElpSucesorExt ( NULL, 1 ) ) )
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
		SElpDestruir ( &p_A );
	SElpDestruir ( &p_B );
	SElpDestruir ( &p_C );
	SElpDestruir ( &p_D );
	ErrLimpiar ();
	return ( iRes );
}


int TestSElementoPtr ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SElementoPtr]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSElpCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSElpEncadenar01 () == BOOL_VAL_CIERTO ) &&
			( TestSElpEsIgualDuplicar01 () == BOOL_VAL_CIERTO ) &&
			( TestSElpEsIgualExt01 () == BOOL_VAL_CIERTO ) &&
			( TestSElpDuplicarExt01 () == BOOL_VAL_CIERTO ) &&
			( TestSElpDeposicionar01 () == BOOL_VAL_CIERTO ) &&
			( TestSElpInvalidos01 () == BOOL_VAL_CIERTO )  &&
			( TestSElpAntecesorSucesorExt01 () == BOOL_VAL_CIERTO ) )
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
