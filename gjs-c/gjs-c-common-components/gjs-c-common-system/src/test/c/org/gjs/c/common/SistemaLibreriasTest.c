#include "Base.h"

#include "SistemaLibrerias.h"



static int TestSisLibCargada01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SisLibCargada 01:\n" );
#if ( defined ( WIN ) )
	/* kernel32 siempre esta cargada en un proceso Windows. */
	if ( SisLibEstaCargada ( "kernel32" ) != 1 )
	{
		printf( "Error caso 1: se esperaba kernel32 cargada\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SisLibCargar ( "kernel32" ) != 1 )
	{
		printf( "Error caso 2: cargar una libreria ya cargada debe devolver 1\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SisLibEstaCargada ( "gjs_libreria_inexistente_xyz" ) != 0 )
	{
		printf( "Error caso 3: no se esperaba cargada una libreria inexistente\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_NULO ( SisLibPrimitiva ( "kernel32", "Sleep" ) ) )
	{
		printf( "Error caso 4: se esperaba resolver la primitiva Sleep\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( SisLibPrimitiva ( "kernel32", "PrimitivaInexistente_XYZ" ) ) )
	{
		printf( "Error caso 5: no se esperaba resolver una primitiva inexistente\n" );
		iRes = BOOL_VAL_FALSO;
	}
	char * p_cRuta = SisLibRutaFichero ( "kernel32" );
	if ( ES_NULO ( p_cRuta ) )
	{
		printf( "Error caso 6: se esperaba ruta de fichero de kernel32\n" );
		iRes = BOOL_VAL_FALSO;
	}
	MemLiberar ( (void **) &p_cRuta );
#endif
	return ( iRes );
}

static int TestSisLibNulo01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SisLibNulo 01:\n" );
	if ( SisLibEstaCargada ( NULL ) != 0 )
	{
		printf( "Error caso 1: se esperaba 0 al comprobar libreria nula\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SisLibCargar ( NULL ) != 0 )
	{
		printf( "Error caso 2: se esperaba 0 al cargar libreria nula\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( SisLibPrimitiva ( NULL, NULL ) ) )
	{
		printf( "Error caso 3: se esperaba nulo al resolver primitiva con nulos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}



int TestSistemaLibrerias ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SistemaLibrerias]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSisLibCargada01 () == BOOL_VAL_CIERTO ) &&
			( TestSisLibNulo01 () == BOOL_VAL_CIERTO ) )
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
