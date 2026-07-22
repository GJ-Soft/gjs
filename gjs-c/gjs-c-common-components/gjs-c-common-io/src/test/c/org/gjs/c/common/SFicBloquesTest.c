#include "Base.h"

#include "SFicBloques.h"
#include "SistemaFicheros.h"
#include "TestConfig.h"



static int TestSFicBloqEscribirLeer01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SFicBloqEscribirLeer 01:\n" );
	byte p_byB0[ 4 ] = { 0x10, 0x11, 0x12, 0x13 };
	byte p_byB1[ 4 ] = { 0x20, 0x21, 0x22, 0x23 };
	byte p_byCab[ 2 ] = { 0xAB, 0xCD };
	SisCrearDirectorio ( FIC_TEST_DIR_RESULTS );
	/* Bloques de 4 bytes y 2 bytes de datos de cabecera. */
	SFicBloques * p_ficObj = SFicBloqCrear ( FIC_TEST_DIR_RESULTS "/sfbloq_test.bin", 4, 2 );
	if ( ES_VALIDO ( p_ficObj ) )
	{
		if ( SFicBloqTamBloque ( p_ficObj ) != 4 )
		{
			printf( "Error caso 1: se esperaba tam de bloque 4: %lu\n", SFicBloqTamBloque ( p_ficObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SFicBloqTamDatosCabecera ( p_ficObj ) != 2 )
		{
			printf( "Error caso 2: se esperaba tam datos de cabecera 2: %lu\n", SFicBloqTamDatosCabecera ( p_ficObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SFicBloqAbrirExt ( p_ficObj, 1 ) != 1 )
		{
			printf( "Error caso 3: no se pudo abrir el fichero\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SFicBloqNumBloques ( p_ficObj ) != 0 )
		{
			printf( "Error caso 4: se esperaban 0 bloques: %lu\n", SFicBloqNumBloques ( p_ficObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SFicBloqEstaVacio ( p_ficObj ) != 1 )
		{
			printf( "Error caso 5: se esperaba vacio\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Escribir dos bloques. */
		if ( ( SFicBloqEscribir ( p_ficObj, 0, p_byB0 ) != 1 ) ||
			 ( SFicBloqEscribir ( p_ficObj, 1, p_byB1 ) != 1 ) )
		{
			printf( "Error caso 6: no se pudieron escribir los bloques\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SFicBloqNumBloques ( p_ficObj ) != 2 )
		{
			printf( "Error caso 7: se esperaban 2 bloques: %lu\n", SFicBloqNumBloques ( p_ficObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SFicBloqEstaVacio ( p_ficObj ) != 0 )
		{
			printf( "Error caso 8: no se esperaba vacio\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Los datos de cabecera se escriben tras los bloques: al extender el
		   numero de bloques la cabecera se reinicializa a cero. */
		if ( SFicBloqEscribirDatosCabecera ( p_ficObj, p_byCab ) != 1 )
		{
			printf( "Error caso 9: no se pudieron escribir los datos de cabecera\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Releer y verificar los bloques. */
		byte * p_byLeido1 = SFicBloqLeer ( p_ficObj, 1 );
		if ( ES_NULO ( p_byLeido1 ) )
		{
			printf( "Error caso 10: no se pudo leer el bloque 1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		else
		{
			for ( int iByte = 0; iByte < 4; iByte = iByte + 1 )
			{
				if ( p_byLeido1[ iByte ] != p_byB1[ iByte ] )
				{
					printf( "Error caso 11: bloque 1 byte %d se esperaba 0x%02X: 0x%02X\n", iByte, (int) p_byB1[ iByte ], (int) p_byLeido1[ iByte ] );
					iRes = BOOL_VAL_FALSO;
				}
			}
			MemLiberar ( (void **) &p_byLeido1 );
		}
		byte * p_byLeido0 = SFicBloqLeer ( p_ficObj, 0 );
		if ( ES_NULO ( p_byLeido0 ) )
		{
			printf( "Error caso 12: no se pudo leer el bloque 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
		else
		{
			for ( int iByte = 0; iByte < 4; iByte = iByte + 1 )
			{
				if ( p_byLeido0[ iByte ] != p_byB0[ iByte ] )
				{
					printf( "Error caso 13: bloque 0 byte %d se esperaba 0x%02X: 0x%02X\n", iByte, (int) p_byB0[ iByte ], (int) p_byLeido0[ iByte ] );
					iRes = BOOL_VAL_FALSO;
				}
			}
			MemLiberar ( (void **) &p_byLeido0 );
		}
		/* Releer y verificar los datos de cabecera. */
		byte * p_byCabLeida = SFicBloqLeerDatosCabecera ( p_ficObj );
		if ( ES_NULO ( p_byCabLeida ) )
		{
			printf( "Error caso 14: no se pudieron leer los datos de cabecera\n" );
			iRes = BOOL_VAL_FALSO;
		}
		else
		{
			if ( ( p_byCabLeida[ 0 ] != 0xAB ) || ( p_byCabLeida[ 1 ] != 0xCD ) )
			{
				printf( "Error caso 15: datos de cabecera erroneos: 0x%02X 0x%02X\n", (int) p_byCabLeida[ 0 ], (int) p_byCabLeida[ 1 ] );
				iRes = BOOL_VAL_FALSO;
			}
			MemLiberar ( (void **) &p_byCabLeida );
		}
		SFicBloqCerrar ( p_ficObj );

		SFicBloqEliminar ( &p_ficObj );
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el objeto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSFicBloqNulo01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SFicBloqNulo 01:\n" );
	if ( SFicBloqEsValido ( NULL ) != 0 )
	{
		printf( "Error caso 1: se esperaba no valido con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SFicBloqAbrir ( NULL ) != 0 )
	{
		printf( "Error caso 2: se esperaba fallo al abrir nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SFicBloqNumBloques ( NULL ) != 0 )
	{
		printf( "Error caso 3: se esperaban 0 bloques con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( SFicBloqLeer ( NULL, 0 ) ) )
	{
		printf( "Error caso 4: se esperaba lectura nula con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSFicBloqAsignarVacio01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SFicBloqAsignarVacio 01:\n" );
	/* Asignar sobre un fichero vacio no debe dar un objeto valido. */
	SFicBloques * p_ficObj = SFicBloqAsignar ( FIC_TEST_FIC_VACIO );
	if ( SFicBloqEsValido ( p_ficObj ) != 0 )
	{
		printf( "Error caso 1: no se esperaba objeto valido desde un fichero vacio\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* Recurso de entrada compartido: solo destruir, nunca eliminar. */
	SFicBloqDestruir ( &p_ficObj );
	return ( iRes );
}

int TestSFicBloques ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SFicBloques]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSFicBloqEscribirLeer01 () == BOOL_VAL_CIERTO ) &&
			( TestSFicBloqAsignarVacio01 () == BOOL_VAL_CIERTO ) &&
			( TestSFicBloqNulo01 () == BOOL_VAL_CIERTO ) )
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
