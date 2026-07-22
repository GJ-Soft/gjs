#include "Base.h"

#include "EntradaSalida.h"
#include "SistemaFicheros.h"
#include "TestConfig.h"



static int TestSisAsincEscribir01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SisAsincEscribir 01:\n" );
	SisCrearDirectorio ( FIC_TEST_DIR_RESULTS );
	/* Se escribe a traves del descriptor de un fichero y se relee. */
	FILE * p_fEscritura = fopen ( FIC_TEST_DIR_RESULTS "/es_test.txt", "wb" );
	if ( ES_VALIDO ( p_fEscritura ) )
	{
		int iDescriptor = SisObtenerDescriptor ( p_fEscritura );
		if ( iDescriptor < 0 )
		{
			printf( "Error caso 1: se esperaba un descriptor valido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SisAsincEscribir ( iDescriptor, "hola" ) != 1 )
		{
			printf( "Error caso 2: no se pudo escribir en el descriptor\n" );
			iRes = BOOL_VAL_FALSO;
		}
		fclose ( p_fEscritura );

		FILE * p_fLectura = fopen ( FIC_TEST_DIR_RESULTS "/es_test.txt", "rb" );
		if ( ES_VALIDO ( p_fLectura ) )
		{
			char p_cBuffer[ 8 ] = { 0 };
			fread ( p_cBuffer, 1, 4, p_fLectura );
			if ( CadComparar ( p_cBuffer, "hola" ) != COMP_IGUAL )
			{
				printf( "Error caso 3: se esperaba \"hola\": [%s]\n", p_cBuffer );
				iRes = BOOL_VAL_FALSO;
			}
			fclose ( p_fLectura );
		}
		else
		{
			printf( "Error caso 3: no se pudo reabrir el fichero para lectura\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SisEliminarFichero ( FIC_TEST_DIR_RESULTS "/es_test.txt" );
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el fichero\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSisAsincEscribirNulo01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SisAsincEscribirNulo 01:\n" );
	if ( SisObtenerDescriptor ( NULL ) != -1 )
	{
		printf( "Error caso 1: se esperaba descriptor -1 con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SisAsincEscribir ( -1, "x" ) != 0 )
	{
		printf( "Error caso 2: se esperaba fallo con descriptor -1\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SisAsincEscribir ( 1, NULL ) != 0 )
	{
		printf( "Error caso 3: se esperaba fallo con texto nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* Escritura vacia a consola: no imprime nada y devuelve exito. */
	if ( SisConAsincEscribir ( "" ) != 1 )
	{
		printf( "Error caso 4: se esperaba exito al escribir vacio en consola\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

int TestEntradaSalida ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test EntradaSalida]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSisAsincEscribir01 () == BOOL_VAL_CIERTO ) &&
			( TestSisAsincEscribirNulo01 () == BOOL_VAL_CIERTO ) )
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
