#include "Base.h"

#include "SFicSecuencial.h"
#include "SistemaFicheros.h"
#include "TestConfig.h"



static int TestSFicSecEscribirLeer01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SFicSecEscribirLeer 01:\n" );
	SisCrearDirectorio ( FIC_TEST_DIR_RESULTS );
	SFicSecuencial * p_ficObj = SFicSecCrear ( FIC_TEST_DIR_RESULTS "/sfsec_test.bin" );
	if ( ES_VALIDO ( p_ficObj ) )
	{
		/* Escritura (vaciando el fichero para partir de cero). */
		if ( SFicSecAbrir ( p_ficObj, MOD_APR_REESCRITURA ) != 1 )
		{
			printf( "Error caso 1: no se pudo abrir para escritura\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SFicSecEstaAbierto ( p_ficObj ) != 1 )
		{
			printf( "Error caso 2: se esperaba abierto\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SFicSecEstaAbiertoParaEscritura ( p_ficObj ) != 1 )
		{
			printf( "Error caso 3: se esperaba abierto para escritura\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SFicSecModoApertura ( p_ficObj ) != MOD_APR_REESCRITURA )
		{
			printf( "Error caso 4: se esperaba modo escritura: %d\n", SFicSecModoApertura ( p_ficObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SFicSecEscribir ( p_ficObj, 0x41 ) != 1 )
		{
			printf( "Error caso 5: no se pudo escribir el primer byte\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SFicSecEscribir ( p_ficObj, 0x42 ) != 1 )
		{
			printf( "Error caso 6: no se pudo escribir el segundo byte\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SFicSecCerrar ( p_ficObj );
		if ( SFicSecEstaAbierto ( p_ficObj ) != 0 )
		{
			printf( "Error caso 7: se esperaba cerrado tras cerrar\n" );
			iRes = BOOL_VAL_FALSO;
		}

		/* Lectura y verificacion del contenido escrito. */
		if ( SFicSecAbrir ( p_ficObj, MOD_APR_LECTURA ) != 1 )
		{
			printf( "Error caso 8: no se pudo abrir para lectura\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SFicSecEstaAbiertoParaLectura ( p_ficObj ) != 1 )
		{
			printf( "Error caso 9: se esperaba abierto para lectura\n" );
			iRes = BOOL_VAL_FALSO;
		}
		byte byUno = SFicSecLeer ( p_ficObj );
		byte byDos = SFicSecLeer ( p_ficObj );
		if ( byUno != 0x41 )
		{
			printf( "Error caso 10: se esperaba 0x41: 0x%02X\n", (int) byUno );
			iRes = BOOL_VAL_FALSO;
		}
		if ( byDos != 0x42 )
		{
			printf( "Error caso 11: se esperaba 0x42: 0x%02X\n", (int) byDos );
			iRes = BOOL_VAL_FALSO;
		}
		SFicSecCerrar ( p_ficObj );

		/* Eliminar borra el fichero y libera el objeto. */
		SFicSecEliminar ( &p_ficObj );
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el objeto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSFicSecNulo01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SFicSecNulo 01:\n" );
	if ( SFicSecEsValido ( NULL ) != 0 )
	{
		printf( "Error caso 1: se esperaba no valido con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SFicSecAbrir ( NULL, MOD_APR_LECTURA ) != 0 )
	{
		printf( "Error caso 2: se esperaba fallo al abrir nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SFicSecEscribir ( NULL, 0x00 ) != 0 )
	{
		printf( "Error caso 3: se esperaba fallo al escribir en nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SFicSecEstaAbierto ( NULL ) != 0 )
	{
		printf( "Error caso 4: no se esperaba abierto con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSFicSecFicheroVacio01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SFicSecFicheroVacio 01:\n" );
	SFicSecuencial * p_ficObj = SFicSecCrear ( FIC_TEST_FIC_VACIO );
	if ( ES_VALIDO ( p_ficObj ) )
	{
		if ( SFicSecAbrir ( p_ficObj, MOD_APR_LECTURA ) != 1 )
		{
			printf( "Error caso 1: no se pudo abrir el fichero vacio para lectura\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* En un fichero vacio no hay nada que leer. */
		if ( SFicSecLeer ( p_ficObj ) != 0x00 )
		{
			printf( "Error caso 2: se esperaba 0x00 al leer de un fichero vacio\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SFicSecEstaEnFinal ( p_ficObj ) != 1 )
		{
			printf( "Error caso 3: se esperaba estar en el final\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SFicSecCerrar ( p_ficObj );
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el objeto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* El fichero vacio es un recurso de entrada compartido: solo se destruye
	   el objeto, nunca se elimina el fichero. */
	SFicSecDestruir ( &p_ficObj );
	return ( iRes );
}


static int TestSFicSecEstaEnFinal01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SFicSecEstaEnFinal 01:\n" );
	SFicSecuencial * p_ficObj = SFicSecCrearExt ( FIC_TEST_DIR_DATA, "ejemploUNIX.txt" );
	if ( ES_VALIDO ( p_ficObj ) )
	{
		if ( SFicSecAbrir ( p_ficObj, MOD_APR_LECTURA ) != 1 )
		{
			printf( "Error caso 1: no se pudo abrir el fichero vacio para lectura\n" );
			iRes = BOOL_VAL_FALSO;
		}
		else
		{
			while ( SFicSecLeer ( p_ficObj ) != 0x00 )
			{
			}
			if ( SFicSecEstaEnFinal ( p_ficObj ) == 0 )
			{
				printf( "Error caso 2: se esperaba estar en el final\n" );
				iRes = BOOL_VAL_FALSO;
			}
			SFicSecCerrar ( p_ficObj );
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el objeto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* El fichero vacio es un recurso de entrada compartido: solo se destruye
	   el objeto, nunca se elimina el fichero. */
	SFicSecDestruir ( &p_ficObj );
	return ( iRes );
}

int TestSFicSecuencial ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SFicSecuencial]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSFicSecEscribirLeer01 () == BOOL_VAL_CIERTO ) &&
			( TestSFicSecFicheroVacio01 () == BOOL_VAL_CIERTO ) &&
			( TestSFicSecNulo01 () == BOOL_VAL_CIERTO ) && 
			( TestSFicSecEstaEnFinal01 () == BOOL_VAL_CIERTO ) )
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
