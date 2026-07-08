#include "Base.h"

#include "SDescripcion.h"



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
		if ( SDescEstaVacio ( p_descObj ) != 1 )
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
		if ( SDescEstablecer ( p_descObj, "Una descripcion" ) != 1 )
		{
			printf( "Error caso 1: se esperaba resultado 1 al establecer la descripcion\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SDescEstaVacio ( p_descObj ) != 0 )
		{
			printf( "Error caso 2: la descripcion no deberia estar vacia tras establecerla\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( CadComparar ( (char *) SDescValorConstante ( p_descObj ), "Una descripcion" ) != COMP_IGUAL )
		{
			printf( "Error caso 3: se esperaba \"Una descripcion\": [%s]\n", SDescValorConstante ( p_descObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SDescLongitud ( p_descObj ) != 15 )
		{
			printf( "Error caso 4: la longitud deberia ser 15: %d\n", SDescLongitud ( p_descObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		SDescLimpiar ( p_descObj );
		if ( SDescEstaVacio ( p_descObj ) != 1 )
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



int TestSDescripcion ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SDescripcion]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSDescCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSDescEstablecer01 () == BOOL_VAL_CIERTO ) )
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
