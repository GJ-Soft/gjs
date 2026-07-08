#include "Base.h"

#include "SInterfaz.h"
#include <TiposPrimitiva.h>



static int NombreEs ( const char * p_cNombre, const char * p_cEsperado )
{
	return ( CadComparar ( (char *) p_cNombre, (char *) p_cEsperado ) == COMP_IGUAL );
}



static int TestSIntrfzCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SIntrfzCrear 01:\n" );

	SInterfaz * p_intrfzObj = SIntrfzCrear ( 1, "IEjemplo" );
	if ( ES_NULO ( p_intrfzObj ) )
	{
		printf( "Error caso 1: no se esperaba nulo al crear\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SIntrfzEsValido ( p_intrfzObj ) != 1 )
		{
			printf( "Error caso 2: la interfaz recien creada deberia ser valida\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SIntrfzId ( p_intrfzObj ) != 1 ) || ( ! NombreEs ( SIntrfzNombre ( p_intrfzObj ), "IEjemplo" ) ) )
		{
			printf( "Error caso 3: id/nombre deberian ser 1 y \"IEjemplo\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SIntrfzNumPrimitivas ( p_intrfzObj ) != 0 )
		{
			printf( "Error caso 4: una interfaz recien creada no deberia tener primitivas\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	SIntrfzDestruir ( &p_intrfzObj );

	if ( ES_VALIDO ( p_intrfzObj ) )
	{
		printf( "Error caso 5: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSIntrfzPrimitivas01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SIntrfzPrimitivas 01:\n" );

	SInterfaz * p_intrfzObj = SIntrfzCrear ( 1, "IEjemplo" );
	if ( ES_VALIDO ( p_intrfzObj ) )
	{
		if ( ( SIntrfzCrearPrimitiva ( p_intrfzObj, "op1", TIP_PRIM_FUNCION ) != 1 ) ||
			 ( SIntrfzCrearPrimitiva ( p_intrfzObj, "op2", TIP_PRIM_PROCEDIMIENTO ) != 1 ) )
		{
			printf( "Error caso 1: se esperaba poder crear las dos primitivas\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SIntrfzNumPrimitivas ( p_intrfzObj ) != 2 )
		{
			printf( "Error caso 2: la interfaz deberia tener 2 primitivas\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Acceso a las primitivas por indice ( 0-based ). */
		if ( ( ! NombreEs ( SDefPrimNombre ( SIntrfzPrimitiva ( p_intrfzObj, 0 ) ), "op1" ) ) ||
			 ( ! NombreEs ( SDefPrimNombre ( SIntrfzPrimitiva ( p_intrfzObj, 1 ) ), "op2" ) ) )
		{
			printf( "Error caso 3: las primitivas deberian llamarse \"op1\" y \"op2\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SDefPrimEsFuncion ( SIntrfzPrimitiva ( p_intrfzObj, 0 ) ) != 1 )
		{
			printf( "Error caso 4: la primera primitiva deberia ser una funcion\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la interfaz\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SIntrfzDestruir ( &p_intrfzObj );
	return ( iRes );
}

static int TestSIntrfzInvalidos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SIntrfzInvalidos 01:\n" );

	if ( ES_VALIDO ( SIntrfzCrear ( 0, "x" ) ) )
	{
		printf( "Error caso 1: crear con id 0 deberia fallar\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SIntrfzEsValido ( NULL ) != 0 )
	{
		printf( "Error caso 2: una interfaz nula no deberia ser valida\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SInterfaz * p_intrfzNula = NULL;
	SIntrfzDestruir ( &p_intrfzNula );
	return ( iRes );
}



int TestSInterfaz ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SInterfaz]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSIntrfzCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSIntrfzPrimitivas01 () == BOOL_VAL_CIERTO ) &&
			( TestSIntrfzInvalidos01 () == BOOL_VAL_CIERTO ) )
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
