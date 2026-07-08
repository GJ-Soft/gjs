#include "Base.h"

#include "SDivisor.h"



static int TestSDivCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SDivCrear 01:\n" );

	SDivisor * p_divObj = SDivCrear ( ',' );
	if ( ES_NULO ( p_divObj ) )
	{
		printf( "Error caso 1: no se esperaba nulo al crear\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SDivEsValido ( p_divObj ) != 1 )
		{
			printf( "Error caso 2: el divisor recien creado deberia ser valido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SDivSeparador ( p_divObj ) != ',' )
		{
			printf( "Error caso 3: el separador deberia ser ',': %c\n", SDivSeparador ( p_divObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SDivTieneTexto ( p_divObj ) != 0 )
		{
			printf( "Error caso 4: un divisor sin inicializar no deberia tener texto\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	SDivDestruir ( &p_divObj );

	if ( ES_VALIDO ( p_divObj ) )
	{
		printf( "Error caso 5: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSDivPartes01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SDivPartes 01:\n" );

	SDivisor * p_divObj = SDivCrearExt ( ',', "uno,dos,tres" );
	if ( ES_VALIDO ( p_divObj ) )
	{
		if ( SDivTieneTexto ( p_divObj ) != 1 )
		{
			printf( "Error caso 1: el divisor deberia tener texto\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SDivNumPartes ( p_divObj ) != 3 )
		{
			printf( "Error caso 2: se esperaban 3 partes: %d\n", SDivNumPartes ( p_divObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( CadComparar ( (char *) SDivParte ( p_divObj, 0 ), "uno" ) != COMP_IGUAL )
		{
			printf( "Error caso 3: la parte 0 deberia ser \"uno\": [%s]\n", SDivParte ( p_divObj, 0 ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( CadComparar ( (char *) SDivParte ( p_divObj, 2 ), "tres" ) != COMP_IGUAL )
		{
			printf( "Error caso 4: la parte 2 deberia ser \"tres\": [%s]\n", SDivParte ( p_divObj, 2 ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( CadComparar ( (char *) SDivTexto ( p_divObj ), "uno,dos,tres" ) != COMP_IGUAL )
		{
			printf( "Error caso 5: el texto deberia ser \"uno,dos,tres\": [%s]\n", SDivTexto ( p_divObj ) );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el divisor\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SDivDestruir ( &p_divObj );
	return ( iRes );
}

static int TestSDivSubtexto01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SDivSubtexto 01:\n" );

	SDivisor * p_divObj = SDivCrearExt ( ',', "uno,dos,tres" );
	if ( ES_VALIDO ( p_divObj ) )
	{
		/* El subtexto omite la primera parte. */
		char * p_cSub = SDivSubtexto ( p_divObj );
		if ( ES_VALIDO ( p_cSub ) )
		{
			if ( CadComparar ( p_cSub, "dos,tres" ) != COMP_IGUAL )
			{
				printf( "Error caso 1: se esperaba \"dos,tres\": [%s]\n", p_cSub );
				iRes = BOOL_VAL_FALSO;
			}
		}
		else
		{
			printf( "Error caso 1: no se pudo obtener el subtexto\n" );
			iRes = BOOL_VAL_FALSO;
		}
		MemLiberar ( (void **) &p_cSub );
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el divisor\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SDivDestruir ( &p_divObj );
	return ( iRes );
}



int TestSDivisor ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SDivisor]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSDivCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSDivPartes01 () == BOOL_VAL_CIERTO ) &&
			( TestSDivSubtexto01 () == BOOL_VAL_CIERTO ) )
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
