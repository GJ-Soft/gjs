#include "Base.h"

#include "SFicEncabezado.h"
#include "SistemaFicheros.h"
#include "TestConfig.h"



static int TestSFicEncCabeceraDatos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SFicEncCabeceraDatos 01:\n" );
	byte p_byCab[ 4 ] = { 0x01, 0x02, 0x03, 0x04 };
	SisCrearDirectorio ( FIC_TEST_DIR_RESULTS );
	SFicEncabezado * p_ficObj = SFicEncCrear ( FIC_TEST_DIR_RESULTS "/sfenc_test.bin", 4 );
	if ( ES_VALIDO ( p_ficObj ) )
	{
		/* Apertura vaciando: escribe la cabecera inicial. */
		if ( SFicEncAbrirExt ( p_ficObj, 1 ) != 1 )
		{
			printf( "Error caso 1: no se pudo abrir el fichero\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SFicEncTamCabecera ( p_ficObj ) != 4 )
		{
			printf( "Error caso 2: se esperaba tam de cabecera 4: %lu\n", SFicEncTamCabecera ( p_ficObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SFicEncTieneNumeroMagico ( p_ficObj ) != 1 )
		{
			printf( "Error caso 3: se esperaba que tenga numero magico\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Escribir y releer la cabecera. */
		if ( SFicEncEscribirCabecera ( p_ficObj, p_byCab ) != 1 )
		{
			printf( "Error caso 4: no se pudo escribir la cabecera\n" );
			iRes = BOOL_VAL_FALSO;
		}
		byte * p_byLeida = SFicEncLeerCabecera ( p_ficObj );
		if ( ES_NULO ( p_byLeida ) )
		{
			printf( "Error caso 5: no se pudo leer la cabecera\n" );
			iRes = BOOL_VAL_FALSO;
		}
		else
		{
			for ( int iByte = 0; iByte < 4; iByte = iByte + 1 )
			{
				if ( p_byLeida[ iByte ] != p_byCab[ iByte ] )
				{
					printf( "Error caso 6: cabecera byte %d se esperaba 0x%02X: 0x%02X\n", iByte, (int) p_byCab[ iByte ], (int) p_byLeida[ iByte ] );
					iRes = BOOL_VAL_FALSO;
				}
			}
			MemLiberar ( (void **) &p_byLeida );
		}
		/* Escribir y releer datos (direccionamiento relativo al inicio de datos). */
		if ( ( SFicEncEscribirEn ( p_ficObj, 0, 0xAA ) != 1 ) ||
			 ( SFicEncEscribirEn ( p_ficObj, 1, 0xBB ) != 1 ) ||
			 ( SFicEncEscribirEn ( p_ficObj, 2, 0xCC ) != 1 ) )
		{
			printf( "Error caso 7: no se pudieron escribir los datos\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SFicEncTamDatos ( p_ficObj ) != 3 )
		{
			printf( "Error caso 8: se esperaba tam de datos 3: %lu\n", SFicEncTamDatos ( p_ficObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SFicEncLeerEn ( p_ficObj, 0 ) != 0xAA )
		{
			printf( "Error caso 9: se esperaba 0xAA en el dato 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SFicEncLeerEn ( p_ficObj, 2 ) != 0xCC )
		{
			printf( "Error caso 10: se esperaba 0xCC en el dato 2\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SFicEncCerrar ( p_ficObj );

		SFicEncEliminar ( &p_ficObj );
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el objeto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSFicEncNulo01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SFicEncNulo 01:\n" );
	if ( SFicEncEsValido ( NULL ) != 0 )
	{
		printf( "Error caso 1: se esperaba no valido con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SFicEncAbrir ( NULL ) != 0 )
	{
		printf( "Error caso 2: se esperaba fallo al abrir nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SFicEncEscribirEn ( NULL, 0, 0x00 ) != 0 )
	{
		printf( "Error caso 3: se esperaba fallo al escribir en nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SFicEncTamCabecera ( NULL ) != 0 )
	{
		printf( "Error caso 4: se esperaba tam de cabecera 0 con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSFicEncAsignarVacio01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SFicEncAsignarVacio 01:\n" );
	/* Asignar (abrir existente) sobre un fichero vacio: no tiene cabecera ni
	   numero magico, asi que no debe producir un objeto valido. */
	SFicEncabezado * p_ficObj = SFicEncAsignar ( FIC_TEST_FIC_VACIO );
	if ( SFicEncEsValido ( p_ficObj ) != 0 )
	{
		printf( "Error caso 1: no se esperaba objeto valido desde un fichero vacio\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* Recurso de entrada compartido: solo destruir, nunca eliminar. */
	SFicEncDestruir ( &p_ficObj );
	return ( iRes );
}

int TestSFicEncabezado ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SFicEncabezado]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSFicEncCabeceraDatos01 () == BOOL_VAL_CIERTO ) &&
			( TestSFicEncAsignarVacio01 () == BOOL_VAL_CIERTO ) &&
			( TestSFicEncNulo01 () == BOOL_VAL_CIERTO ) )
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
