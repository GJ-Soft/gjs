#include "Base.h"

#include "SGeneradorId.h"



static int TestSGenIdCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SGenIdCrear 01:\n" );

	SGeneradorId * p_genidObj = SGenIdCrearDef ();
	if ( ES_NULO ( p_genidObj ) )
	{
		printf( "Error caso 1: no se esperaba nulo al crear por defecto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SGenIdEsValido ( p_genidObj ) != 1 )
		{
			printf( "Error caso 2: el generador por defecto deberia ser valido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Por defecto: id inicial 1, sin id final ( 0 ) y sin ninguno usado. */
		if ( ( SGenIdInicial ( p_genidObj ) != 1 ) || ( SGenIdUltimo ( p_genidObj ) != 0 ) )
		{
			printf( "Error caso 3: se esperaba inicial 1 y ultimo 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	SGenIdDestruir ( &p_genidObj );

	if ( ES_VALIDO ( p_genidObj ) )
	{
		printf( "Error caso 4: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSGenIdGenerar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SGenIdGenerar 01:\n" );

	SGeneradorId * p_genidObj = SGenIdCrearDef ();
	if ( ES_VALIDO ( p_genidObj ) )
	{
		/* Sig consulta el siguiente sin consumirlo. */
		if ( SGenIdSig ( p_genidObj ) != 1 )
		{
			printf( "Error caso 1: el primer id deberia ser 1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SGenIdUltimo ( p_genidObj ) != 0 )
		{
			printf( "Error caso 2: Sig no deberia consumir el id\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* AsignarSig consume y devuelve ids consecutivos. */
		if ( ( SGenIdAsignarSig ( p_genidObj ) != 1 ) || ( SGenIdAsignarSig ( p_genidObj ) != 2 ) )
		{
			printf( "Error caso 3: se esperaban los ids 1 y 2\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SGenIdUltimo ( p_genidObj ) != 2 )
		{
			printf( "Error caso 4: el ultimo id asignado deberia ser 2\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Iniciar reinicia la generacion. */
		SGenIdIniciar ( p_genidObj );
		if ( SGenIdAsignarSig ( p_genidObj ) != 1 )
		{
			printf( "Error caso 5: tras iniciar deberia volver a empezar en 1\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el generador\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SGenIdDestruir ( &p_genidObj );
	return ( iRes );
}

static int TestSGenIdRango01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SGenIdRango 01:\n" );

	/* Generador acotado: inicial 1, ultimo 0 ( ninguno ), final 3. */
	SGeneradorId * p_genidObj = SGenIdCrear ( 1, 0, 3 );
	if ( ES_VALIDO ( p_genidObj ) )
	{
		/* Consume 1, 2, 3 y despues vuelve al inicial. */
		if ( ( SGenIdAsignarSig ( p_genidObj ) != 1 ) ||
			 ( SGenIdAsignarSig ( p_genidObj ) != 2 ) ||
			 ( SGenIdAsignarSig ( p_genidObj ) != 3 ) )
		{
			printf( "Error caso 1: se esperaban los ids 1, 2 y 3\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SGenIdAsignarSig ( p_genidObj ) != 1 )
		{
			printf( "Error caso 2: tras el id final deberia volver al inicial\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el generador acotado\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SGenIdDestruir ( &p_genidObj );
	return ( iRes );
}

static int TestSGenIdDuplicar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SGenIdDuplicar 01:\n" );

	SGeneradorId * p_genidObj = SGenIdCrearDef ();
	if ( ES_VALIDO ( p_genidObj ) )
	{
		SGenIdAsignarSig ( p_genidObj );
		SGenIdAsignarSig ( p_genidObj );

		SGeneradorId * p_genidDup = SGenIdDuplicar ( p_genidObj );
		if ( ES_NULO ( p_genidDup ) )
		{
			printf( "Error caso 1: no se esperaba nulo al duplicar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		else
		{
			if ( SGenIdEsIgual ( p_genidObj, p_genidDup ) != 1 )
			{
				printf( "Error caso 2: el duplicado deberia ser igual al original\n" );
				iRes = BOOL_VAL_FALSO;
			}
			/* Copia independiente: avanzar el original no afecta al duplicado. */
			SGenIdAsignarSig ( p_genidObj );
			if ( SGenIdEsIgual ( p_genidObj, p_genidDup ) != 0 )
			{
				printf( "Error caso 3: el duplicado no deberia avanzar con el original\n" );
				iRes = BOOL_VAL_FALSO;
			}
			SGenIdDestruir ( &p_genidDup );
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el generador\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SGenIdDestruir ( &p_genidObj );
	return ( iRes );
}

static int TestSGenIdInvalidos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SGenIdInvalidos 01:\n" );

	if ( SGenIdEsValido ( NULL ) != 0 )
	{
		printf( "Error caso 1: un generador nulo no deberia ser valido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SGenIdAsignarSig ( NULL ) != 0 )
	{
		printf( "Error caso 2: asignar en un generador nulo deberia devolver 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SGeneradorId * p_genidNulo = NULL;
	SGenIdDestruir ( &p_genidNulo );
	return ( iRes );
}



int TestSGeneradorId ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SGeneradorId]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSGenIdCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSGenIdGenerar01 () == BOOL_VAL_CIERTO ) &&
			( TestSGenIdRango01 () == BOOL_VAL_CIERTO ) &&
			( TestSGenIdDuplicar01 () == BOOL_VAL_CIERTO ) &&
			( TestSGenIdInvalidos01 () == BOOL_VAL_CIERTO ) )
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
