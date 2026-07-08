#include "Base.h"

#include "SNombre.h"



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
		if ( SNomEstablecer ( p_nomObj, "Juan" ) != 1 )
		{
			printf( "Error caso 1: se esperaba resultado 1 al establecer un nombre valido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SNomEstaVacio ( p_nomObj ) != 0 )
		{
			printf( "Error caso 2: el nombre no deberia estar vacio tras establecerlo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( CadComparar ( (char *) SNomValorConstante ( p_nomObj ), "Juan" ) != COMP_IGUAL )
		{
			printf( "Error caso 3: se esperaba \"Juan\": [%s]\n", SNomValorConstante ( p_nomObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		/* Un nombre con espacios no es valido. */
		if ( SNomEstablecer ( p_nomObj, "con espacio" ) != 0 )
		{
			printf( "Error caso 4: un nombre con espacios no deberia aceptarse\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Un nombre que no empieza por letra no es valido. */
		if ( SNomEstablecer ( p_nomObj, "1nombre" ) != 0 )
		{
			printf( "Error caso 5: un nombre que empieza por digito no deberia aceptarse\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Limpiar deja el nombre vacio. */
		SNomLimpiar ( p_nomObj );
		if ( SNomEstaVacio ( p_nomObj ) != 1 )
		{
			printf( "Error caso 6: el nombre deberia estar vacio tras limpiar\n" );
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



int TestSNombre ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SNombre]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSNomCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSNomEstablecer01 () == BOOL_VAL_CIERTO ) )
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
