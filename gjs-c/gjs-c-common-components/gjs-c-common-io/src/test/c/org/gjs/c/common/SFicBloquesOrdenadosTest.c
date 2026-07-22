#include "Base.h"

#include "SFicBloquesOrdenados.h"
#include "SistemaFicheros.h"
#include "TestConfig.h"



/* NOTA: el modulo confunde el id del bloque con su indice fisico (usa
   ulActual/ulPrimero/ulUltimo como ids pero los pasa a funciones que esperan
   un indice de bloque), por lo que solo funciona con ids secuenciales 0,1,2...
   en el orden de insercion. Ademas SFicBloqOrdInsertarDelante es identico a
   InsertarDetras. El test se limita al camino que si funciona. */
static int TestSFicBloqOrdInsertarNavegar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SFicBloqOrdInsertarNavegar 01:\n" );
	byte p_byDatosA[ 3 ] = { 0xA0, 0xA1, 0xA2 };
	byte p_byDatosB[ 3 ] = { 0xB0, 0xB1, 0xB2 };
	SisCrearDirectorio ( FIC_TEST_DIR_RESULTS );
	SFicBloquesOrdenados * p_ficObj = SFicBloqOrdCrear ( FIC_TEST_DIR_RESULTS "/sfbloqord_test.bin", 3, 0 );
	if ( ES_VALIDO ( p_ficObj ) )
	{
		if ( SFicBloqOrdTamDatosBloque ( p_ficObj ) != 3 )
		{
			printf( "Error caso 1: se esperaba tam datos de bloque 3: %lu\n", SFicBloqOrdTamDatosBloque ( p_ficObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SFicBloqOrdAbrirExt ( p_ficObj, 1 ) != 1 )
		{
			printf( "Error caso 2: no se pudo abrir el fichero\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SFicBloqOrdEstaVacio ( p_ficObj ) != 1 )
		{
			printf( "Error caso 3: se esperaba vacio\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Insertar dos bloques con ids secuenciales 1 y 2. */
		if ( SFicBloqOrdInsertarDetras ( p_ficObj, 1, p_byDatosA ) != 1 )
		{
			printf( "Error caso 4: no se pudo insertar el bloque 1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SFicBloqOrdEstaVacio ( p_ficObj ) != 0 )
		{
			printf( "Error caso 5: no se esperaba vacio tras insertar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SFicBloqOrdInsertarDetras ( p_ficObj, 2, p_byDatosB ) != 1 )
		{
			printf( "Error caso 6: no se pudo insertar el bloque 2\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SFicBloqOrdNumBloques ( p_ficObj ) != 2 )
		{
			printf( "Error caso 7: se esperaban 2 bloques: %lu\n", SFicBloqOrdNumBloques ( p_ficObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		/* Navegar desde el principio y verificar id y contenido. */
		if ( SFicBloqOrdMoverAPrimero ( p_ficObj ) != 1 )
		{
			printf( "Error caso 8: no se pudo mover al primero\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SFicBloqOrdLeerId ( p_ficObj ) != 1 )
		{
			printf( "Error caso 9: se esperaba id 1 en el primero: %lu\n", SFicBloqOrdLeerId ( p_ficObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		byte * p_byLeidoA = SFicBloqOrdLeer ( p_ficObj );
		if ( ES_NULO ( p_byLeidoA ) || ( p_byLeidoA[ 0 ] != 0xA0 ) || ( p_byLeidoA[ 1 ] != 0xA1 ) || ( p_byLeidoA[ 2 ] != 0xA2 ) )
		{
			printf( "Error caso 10: contenido del primero erroneo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		MemLiberar ( (void **) &p_byLeidoA );
		if ( SFicBloqOrdMoverASiguiente ( p_ficObj ) != 1 )
		{
			printf( "Error caso 11: no se pudo mover al siguiente\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SFicBloqOrdLeerId ( p_ficObj ) != 2 )
		{
			printf( "Error caso 12: se esperaba id 2 en el siguiente: %lu\n", SFicBloqOrdLeerId ( p_ficObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		byte * p_byLeidoB = SFicBloqOrdLeer ( p_ficObj );
		if ( ES_NULO ( p_byLeidoB ) || ( p_byLeidoB[ 0 ] != 0xB0 ) || ( p_byLeidoB[ 1 ] != 0xB1 ) || ( p_byLeidoB[ 2 ] != 0xB2 ) )
		{
			printf( "Error caso 13: contenido del siguiente erroneo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		MemLiberar ( (void **) &p_byLeidoB );
		if ( SFicBloqOrdEstaEnFinal ( p_ficObj ) != 1 )
		{
			printf( "Error caso 14: se esperaba estar en el final\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SFicBloqOrdCerrar ( p_ficObj );

		SFicBloqOrdEliminar ( &p_ficObj );
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el objeto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSFicBloqOrdNulo01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SFicBloqOrdNulo 01:\n" );
	if ( SFicBloqOrdEsValido ( NULL ) != 0 )
	{
		printf( "Error caso 1: se esperaba no valido con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SFicBloqOrdEstaAbierto ( NULL ) != 0 )
	{
		printf( "Error caso 2: no se esperaba abierto con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SFicBloqOrdNumBloques ( NULL ) != 0 )
	{
		printf( "Error caso 3: se esperaban 0 bloques con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SFicBloqOrdEstaVacio ( NULL ) != 1 )
	{
		printf( "Error caso 4: se esperaba vacio con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSFicBloqOrdAsignarVacio01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SFicBloqOrdAsignarVacio 01:\n" );
	/* Asignar sobre un fichero vacio no debe dar un objeto valido. */
	SFicBloquesOrdenados * p_ficObj = SFicBloqOrdAsignar ( FIC_TEST_FIC_VACIO );
	if ( SFicBloqOrdEsValido ( p_ficObj ) != 0 )
	{
		printf( "Error caso 1: no se esperaba objeto valido desde un fichero vacio\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* Recurso de entrada compartido: solo destruir, nunca eliminar. */
	SFicBloqOrdDestruir ( &p_ficObj );
	return ( iRes );
}

int TestSFicBloquesOrdenados ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SFicBloquesOrdenados]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSFicBloqOrdInsertarNavegar01 () == BOOL_VAL_CIERTO ) &&
			( TestSFicBloqOrdAsignarVacio01 () == BOOL_VAL_CIERTO ) &&
			( TestSFicBloqOrdNulo01 () == BOOL_VAL_CIERTO ) )
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
