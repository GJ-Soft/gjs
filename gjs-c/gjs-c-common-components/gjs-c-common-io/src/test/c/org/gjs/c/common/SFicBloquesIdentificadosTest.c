#include "Base.h"

#include "SFicBloquesIdentificados.h"
#include "SistemaFicheros.h"
#include "TestConfig.h"



static int TestSFicBloqIdInsertarLeer01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SFicBloqIdInsertarLeer 01:\n" );
	byte p_byD10[ 3 ] = { 0xA0, 0xA1, 0xA2 };
	byte p_byD20[ 3 ] = { 0xB0, 0xB1, 0xB2 };
	byte p_byD5[ 3 ]  = { 0xC0, 0xC1, 0xC2 };
	byte p_byMod[ 3 ] = { 0xD0, 0xD1, 0xD2 };
	SisCrearDirectorio ( FIC_TEST_DIR_RESULTS );
	/* 3 bytes de datos por bloque (aparte del identificador). */
	SFicBloquesIdentificados * p_ficObj = SFicBloqIdCrear ( FIC_TEST_DIR_RESULTS "/sfbloqid_test.bin", 3, 0 );
	if ( ES_VALIDO ( p_ficObj ) )
	{
		if ( SFicBloqIdTamDatosBloque ( p_ficObj ) != 3 )
		{
			printf( "Error caso 1: se esperaba tam datos de bloque 3: %lu\n", SFicBloqIdTamDatosBloque ( p_ficObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SFicBloqIdAbrirExt ( p_ficObj, 1 ) != 1 )
		{
			printf( "Error caso 2: no se pudo abrir el fichero\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SFicBloqIdEstaVacio ( p_ficObj ) != 1 )
		{
			printf( "Error caso 3: se esperaba vacio\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Insertar tres bloques con identificadores en desorden. */
		if ( ( SFicBloqIdInsertar ( p_ficObj, 10, p_byD10 ) != 1 ) ||
			 ( SFicBloqIdInsertar ( p_ficObj, 20, p_byD20 ) != 1 ) ||
			 ( SFicBloqIdInsertar ( p_ficObj, 5, p_byD5 ) != 1 ) )
		{
			printf( "Error caso 4: no se pudieron insertar los bloques\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SFicBloqIdNumBloques ( p_ficObj ) != 3 )
		{
			printf( "Error caso 5: se esperaban 3 bloques: %lu\n", SFicBloqIdNumBloques ( p_ficObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SFicBloqIdMinId ( p_ficObj ) != 5 )
		{
			printf( "Error caso 6: se esperaba min id 5: %lu\n", SFicBloqIdMinId ( p_ficObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SFicBloqIdMaxId ( p_ficObj ) != 20 )
		{
			printf( "Error caso 7: se esperaba max id 20: %lu\n", SFicBloqIdMaxId ( p_ficObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SFicBloqIdExisteId ( p_ficObj, 10 ) != 1 )
		{
			printf( "Error caso 8: se esperaba que exista el id 10\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SFicBloqIdExisteId ( p_ficObj, 99 ) != 0 )
		{
			printf( "Error caso 9: no se esperaba que exista el id 99\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Leer por identificador. */
		byte * p_byLeido = SFicBloqIdLeer ( p_ficObj, 20 );
		if ( ES_NULO ( p_byLeido ) || ( p_byLeido[ 0 ] != 0xB0 ) || ( p_byLeido[ 1 ] != 0xB1 ) || ( p_byLeido[ 2 ] != 0xB2 ) )
		{
			printf( "Error caso 10: datos del id 20 erroneos\n" );
			iRes = BOOL_VAL_FALSO;
		}
		MemLiberar ( (void **) &p_byLeido );
		/* Modificar y releer. */
		if ( SFicBloqIdModificar ( p_ficObj, 10, p_byMod ) != 1 )
		{
			printf( "Error caso 11: no se pudo modificar el id 10\n" );
			iRes = BOOL_VAL_FALSO;
		}
		byte * p_byMod10 = SFicBloqIdLeer ( p_ficObj, 10 );
		if ( ES_NULO ( p_byMod10 ) || ( p_byMod10[ 0 ] != 0xD0 ) || ( p_byMod10[ 1 ] != 0xD1 ) || ( p_byMod10[ 2 ] != 0xD2 ) )
		{
			printf( "Error caso 12: datos del id 10 tras modificar erroneos\n" );
			iRes = BOOL_VAL_FALSO;
		}
		MemLiberar ( (void **) &p_byMod10 );
		/* Suprimir y comprobar que se recalcula el minimo. */
		if ( SFicBloqIdSuprimir ( p_ficObj, 5 ) != 1 )
		{
			printf( "Error caso 13: no se pudo suprimir el id 5\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SFicBloqIdExisteId ( p_ficObj, 5 ) != 0 )
		{
			printf( "Error caso 14: no se esperaba que exista el id 5 tras suprimir\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SFicBloqIdMinId ( p_ficObj ) != 10 )
		{
			printf( "Error caso 15: se esperaba min id 10 tras suprimir: %lu\n", SFicBloqIdMinId ( p_ficObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		SFicBloqIdCerrar ( p_ficObj );

		SFicBloqIdEliminar ( &p_ficObj );
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el objeto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSFicBloqIdNulo01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SFicBloqIdNulo 01:\n" );
	if ( SFicBloqIdEsValido ( NULL ) != 0 )
	{
		printf( "Error caso 1: se esperaba no valido con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SFicBloqIdAbrir ( NULL ) != 0 )
	{
		printf( "Error caso 2: se esperaba fallo al abrir nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SFicBloqIdExisteId ( NULL, 1 ) != 0 )
	{
		printf( "Error caso 3: no se esperaba existencia con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( SFicBloqIdLeer ( NULL, 1 ) ) )
	{
		printf( "Error caso 4: se esperaba lectura nula con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSFicBloqIdAsignarVacio01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SFicBloqIdAsignarVacio 01:\n" );
	/* Asignar sobre un fichero vacio no debe dar un objeto valido. */
	SFicBloquesIdentificados * p_ficObj = SFicBloqIdAsignar ( FIC_TEST_FIC_VACIO );
	if ( SFicBloqIdEsValido ( p_ficObj ) != 0 )
	{
		printf( "Error caso 1: no se esperaba objeto valido desde un fichero vacio\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* Recurso de entrada compartido: solo destruir, nunca eliminar. */
	SFicBloqIdDestruir ( &p_ficObj );
	return ( iRes );
}

int TestSFicBloquesIdentificados ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SFicBloquesIdentificados]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSFicBloqIdInsertarLeer01 () == BOOL_VAL_CIERTO ) &&
			( TestSFicBloqIdAsignarVacio01 () == BOOL_VAL_CIERTO ) &&
			( TestSFicBloqIdNulo01 () == BOOL_VAL_CIERTO ) )
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
