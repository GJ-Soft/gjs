#include "Base.h"

#include "SContenido.h"



static int TestSConCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SConCrear 01:\n" );

	SContenido * p_conObj = SConCrearEntero ();
	if ( ES_NULO ( p_conObj ) )
	{
		printf( "Error caso 1: no se esperaba nulo al crear\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SConEsValido ( p_conObj ) != 1 )
		{
			printf( "Error caso 2: el contenido recien creado deberia ser valido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SConTieneDatos ( p_conObj ) != 1 )
		{
			printf( "Error caso 3: el contenido deberia tener datos\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_NULO ( SConDatos ( p_conObj ) ) )
		{
			printf( "Error caso 4: los datos no deberian ser nulos\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	SConDestruir ( &p_conObj );

	if ( ES_VALIDO ( p_conObj ) )
	{
		printf( "Error caso 5: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* Crear con tam 0 debe fallar. */
	if ( ES_VALIDO ( SConCrear ( 0 ) ) )
	{
		printf( "Error caso 6: se esperaba nulo al crear con tam 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSConEnteros01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SConEnteros 01:\n" );

	SContenido * p_conObj = SConCrearEntero ();
	if ( ES_VALIDO ( p_conObj ) )
	{
		if ( SConEscribirEntero ( p_conObj, 4321 ) != 1 )
		{
			printf( "Error caso 1: se esperaba resultado 1 al escribir entero\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SConEntero ( p_conObj ) != 4321 )
		{
			printf( "Error caso 2: se esperaba 4321: %d\n", SConEntero ( p_conObj ) );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el contenido entero\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SConDestruir ( &p_conObj );

	/* Roundtrip de real doble. */
	SContenido * p_conReal = SConCrearRealDoble ();
	if ( ES_VALIDO ( p_conReal ) )
	{
		SConEscribirRealDoble ( p_conReal, 3.5 );
		if ( SConRealDoble ( p_conReal ) != 3.5 )
		{
			printf( "Error caso 3: se esperaba 3.5 en el real doble\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	SConDestruir ( &p_conReal );
	return ( iRes );
}

static int TestSConDuplicar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SConDuplicar 01:\n" );

	SContenido * p_conObj = SConCrearEntero ();
	if ( ES_VALIDO ( p_conObj ) )
	{
		SConEscribirEntero ( p_conObj, 777 );

		SContenido * p_conDup = SConDuplicar ( p_conObj );
		if ( ES_NULO ( p_conDup ) )
		{
			printf( "Error caso 1: no se esperaba nulo al duplicar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		else
		{
			if ( SConEntero ( p_conDup ) != 777 )
			{
				printf( "Error caso 2: el duplicado deberia contener 777\n" );
				iRes = BOOL_VAL_FALSO;
			}
			/* Copia independiente: modificar el original no afecta al duplicado. */
			SConEscribirEntero ( p_conObj, 888 );
			if ( SConEntero ( p_conDup ) != 777 )
			{
				printf( "Error caso 3: el duplicado no deberia compartir datos con el original\n" );
				iRes = BOOL_VAL_FALSO;
			}
			SConDestruir ( &p_conDup );
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el contenido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SConDestruir ( &p_conObj );
	return ( iRes );
}

static int TestSConEncapsular01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SConEncapsular 01:\n" );

	SBloque * p_blqObj = SBlqCrear ( 4 );
	if ( ES_VALIDO ( p_blqObj ) )
	{
		SContenido * p_conObj = SConEncapsular ( p_blqObj );
		if ( ES_NULO ( p_conObj ) )
		{
			printf( "Error caso 1: no se esperaba nulo al encapsular\n" );
			iRes = BOOL_VAL_FALSO;
			SBlqDestruir ( &p_blqObj );
		}
		else
		{
			if ( SConDatos ( p_conObj ) != p_blqObj )
			{
				printf( "Error caso 2: el contenido deberia envolver el bloque dado\n" );
				iRes = BOOL_VAL_FALSO;
			}
			/* El contenido gestiona el bloque: destruirlo lo libera tambien. */
			SConDestruir ( &p_conObj );
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el bloque\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSConInvalidos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SConInvalidos 01:\n" );

	if ( SConEsValido ( NULL ) != 0 )
	{
		printf( "Error caso 1: un contenido nulo no deberia ser valido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( SConDatos ( NULL ) ) )
	{
		printf( "Error caso 2: los datos de un contenido nulo deberian ser nulos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SConEscribirEntero ( NULL, 1 ) != 0 )
	{
		printf( "Error caso 3: escribir en un contenido nulo deberia fallar\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SContenido * p_conNulo = NULL;
	SConDestruir ( &p_conNulo );
	return ( iRes );
}



int TestSContenido ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SContenido]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSConCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSConEnteros01 () == BOOL_VAL_CIERTO ) &&
			( TestSConDuplicar01 () == BOOL_VAL_CIERTO ) &&
			( TestSConEncapsular01 () == BOOL_VAL_CIERTO ) &&
			( TestSConInvalidos01 () == BOOL_VAL_CIERTO ) )
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
