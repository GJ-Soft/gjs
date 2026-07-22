#include "Base.h"

#include "SFicSecuencialBuffer.h"
#include "SistemaFicheros.h"
#include "TestConfig.h"



static int TestSFicSecBufEscribirLeer01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SFicSecBufEscribirLeer 01:\n" );
	byte p_byEsperado[ 6 ] = { 0x10, 0x11, 0x12, 0x13, 0x14, 0x15 };
	SisCrearDirectorio ( FIC_TEST_DIR_RESULTS );
	/* Buffer pequeno (4) para forzar un volcado intermedio y otro al cerrar. */
	SFicSecuencialBuffer * p_ficObj = SFicSecBufCrear ( FIC_TEST_DIR_RESULTS "/sfsbuf_test.bin", 4 );
	if ( ES_VALIDO ( p_ficObj ) )
	{
		if ( SFicSecBufAbrir ( p_ficObj, MOD_APR_REESCRITURA ) != 1 )
		{
			printf( "Error caso 1: no se pudo abrir para escritura\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SFicSecBufEstaAbiertoParaEscritura ( p_ficObj ) != 1 )
		{
			printf( "Error caso 2: se esperaba abierto para escritura\n" );
			iRes = BOOL_VAL_FALSO;
		}
		for ( int iByte = 0; iByte < 6; iByte = iByte + 1 )
		{
			if ( SFicSecBufEscribir ( p_ficObj, p_byEsperado[ iByte ] ) != 1 )
			{
				printf( "Error caso 3: no se pudo escribir el byte %d\n", iByte );
				iRes = BOOL_VAL_FALSO;
			}
		}
		/* Cerrar vuelca el resto del buffer al fichero. */
		SFicSecBufCerrar ( p_ficObj );

		if ( SFicSecBufAbrir ( p_ficObj, MOD_APR_LECTURA ) != 1 )
		{
			printf( "Error caso 4: no se pudo abrir para lectura\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SFicSecBufEstaAbiertoParaLectura ( p_ficObj ) != 1 )
		{
			printf( "Error caso 5: se esperaba abierto para lectura\n" );
			iRes = BOOL_VAL_FALSO;
		}
		for ( int iByte = 0; iByte < 6; iByte = iByte + 1 )
		{
			byte byLeido = SFicSecBufLeer ( p_ficObj );
			if ( byLeido != p_byEsperado[ iByte ] )
			{
				printf( "Error caso 6: byte %d se esperaba 0x%02X: 0x%02X\n", iByte, (int) p_byEsperado[ iByte ], (int) byLeido );
				iRes = BOOL_VAL_FALSO;
			}
		}
		SFicSecBufCerrar ( p_ficObj );

		SFicSecBufEliminar ( &p_ficObj );
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el objeto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSFicSecBufNulo01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SFicSecBufNulo 01:\n" );
	if ( SFicSecBufEsValido ( NULL ) != 0 )
	{
		printf( "Error caso 1: se esperaba no valido con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SFicSecBufAbrir ( NULL, MOD_APR_LECTURA ) != 0 )
	{
		printf( "Error caso 2: se esperaba fallo al abrir nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SFicSecBufEscribir ( NULL, 0x00 ) != 0 )
	{
		printf( "Error caso 3: se esperaba fallo al escribir en nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SFicSecBufEstaAbierto ( NULL ) != 0 )
	{
		printf( "Error caso 4: no se esperaba abierto con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSFicSecBufFicheroVacio01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SFicSecBufFicheroVacio 01:\n" );
	SFicSecuencialBuffer * p_ficObj = SFicSecBufCrear ( FIC_TEST_FIC_VACIO, 4 );
	if ( ES_VALIDO ( p_ficObj ) )
	{
		if ( SFicSecBufAbrir ( p_ficObj, MOD_APR_LECTURA ) != 1 )
		{
			printf( "Error caso 1: no se pudo abrir el fichero vacio para lectura\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* En un fichero vacio no hay nada que leer. */
		if ( SFicSecBufLeer ( p_ficObj ) != 0x00 )
		{
			printf( "Error caso 2: se esperaba 0x00 al leer de un fichero vacio\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SFicSecBufEstaEnFinal ( p_ficObj ) != 1 )
		{
			printf( "Error caso 3: se esperaba estar en el final\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SFicSecBufCerrar ( p_ficObj );
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el objeto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* Recurso de entrada compartido: solo destruir, nunca eliminar. */
	SFicSecBufDestruir ( &p_ficObj );
	return ( iRes );
}

int TestSFicSecuencialBuffer ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SFicSecuencialBuffer]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSFicSecBufEscribirLeer01 () == BOOL_VAL_CIERTO ) &&
			( TestSFicSecBufFicheroVacio01 () == BOOL_VAL_CIERTO ) &&
			( TestSFicSecBufNulo01 () == BOOL_VAL_CIERTO ) )
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
