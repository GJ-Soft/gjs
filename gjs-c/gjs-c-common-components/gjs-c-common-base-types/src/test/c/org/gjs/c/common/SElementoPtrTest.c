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
		if ( ( SElpEsIgualExt ( p_a, p_buf, sizeof ( int ) ) != 1 ) ||
			 ( SElpEsIgualExt ( p_a, p_buf99, sizeof ( int ) ) != 0 ) )
		{
			printf( "Error caso 1: la comparacion de contenido deberia distinguir 42 de 99\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Duplicar comparte el puntero a los datos y no libera ( iLiberar = 0 ). */
		SElementoPtr * p_dup = SElpDuplicar ( p_a );
		if ( ES_NULO ( p_dup ) )
		{
			printf( "Error caso 2: no se esperaba nulo al duplicar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		else
		{
			if ( ( SElpDatos ( p_dup ) != SElpDatos ( p_a ) ) || ( SElpLiberacionMemoriaActivada ( p_dup ) != 0 ) )
			{
				printf( "Error caso 3: el duplicado deberia compartir los datos sin liberarlos\n" );
				iRes = BOOL_VAL_FALSO;
			}
			SElpDestruir ( &p_dup );
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



int TestSElementoPtr ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SElementoPtr]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSElpCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSElpEncadenar01 () == BOOL_VAL_CIERTO ) &&
			( TestSElpEsIgualDuplicar01 () == BOOL_VAL_CIERTO ) &&
			( TestSElpInvalidos01 () == BOOL_VAL_CIERTO ) )
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
