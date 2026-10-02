#include "Base.h"

#include "SFicTexto.h"
#include "SistemaFicheros.h"
#include "TestConfig.h"



static int TestSFicTxtEscribirLeer01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SFicTxtEscribirLeer 01:\n" );
	SisCrearDirectorio ( FIC_TEST_DIR_RESULTS );
	SFicTexto * p_ficObj = SFicTxtCrear ( FIC_TEST_DIR_RESULTS "/sftxt_test.txt" );
	if ( ES_VALIDO ( p_ficObj ) )
	{
		if ( SFicTxtEsEstiloDOS ( p_ficObj ) != 1 )
		{
			printf( "Error caso 1: se esperaba estilo DOS por defecto\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Escritura de dos lineas (vaciando el fichero). */
		if ( SFicTxtAbrir ( p_ficObj, MOD_APR_REESCRITURA ) != 1 )
		{
			printf( "Error caso 2: no se pudo abrir para escritura\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SFicTxtEscribirLinea ( p_ficObj, "primera" ) != 1 )
		{
			printf( "Error caso 3: no se pudo escribir la primera linea\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SFicTxtEscribirLinea ( p_ficObj, "segunda" ) != 1 )
		{
			printf( "Error caso 4: no se pudo escribir la segunda linea\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SFicTxtCerrar ( p_ficObj );

		/* Lectura y verificacion. */
		if ( SFicTxtAbrir ( p_ficObj, MOD_APR_LECTURA ) != 1 )
		{
			printf( "Error caso 5: no se pudo abrir para lectura\n" );
			iRes = BOOL_VAL_FALSO;
		}
		char * p_cLinea1 = SFicTxtLeerLinea ( p_ficObj );
		if ( ES_NULO ( p_cLinea1 ) || ( CadComparar ( p_cLinea1, "primera" ) != COMP_IGUAL ) )
		{
			printf( "Error caso 6: se esperaba \"primera\": [%s]\n", ES_VALIDO ( p_cLinea1 ) ? p_cLinea1 : "(nulo)" );
			iRes = BOOL_VAL_FALSO;
		}
		MemLiberar ( (void **) &p_cLinea1 );
		char * p_cLinea2 = SFicTxtLeerLinea ( p_ficObj );
		if ( ES_NULO ( p_cLinea2 ) || ( CadComparar ( p_cLinea2, "segunda" ) != COMP_IGUAL ) )
		{
			printf( "Error caso 7: se esperaba \"segunda\": [%s]\n", ES_VALIDO ( p_cLinea2 ) ? p_cLinea2 : "(nulo)" );
			iRes = BOOL_VAL_FALSO;
		}
		MemLiberar ( (void **) &p_cLinea2 );
		SFicTxtCerrar ( p_ficObj );

		/* Eliminar borra el fichero y libera el objeto. */
		SFicTxtEliminar ( &p_ficObj );
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el objeto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSFicTxtLeer01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SFicTxtLeer 01:\n" );
	SisCrearDirectorio ( FIC_TEST_DIR_RESULTS );
	SFicTexto * p_ficObj = SFicTxtCrearExt ( FIC_TEST_DIR_DATA, "ejemploDOS.txt", EST_FTXT_DOS );
	if ( ES_VALIDO ( p_ficObj ) )
	{
		if ( SFicTxtEsEstiloDOS ( p_ficObj ) != 1 )
		{
			printf( "Error caso 1: se esperaba estilo DOS\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Escritura de dos lineas (vaciando el fichero). */
		if ( SFicTxtAbrir ( p_ficObj, MOD_APR_LECTURA ) != 1 )
		{
			printf( "Error caso 2: no se pudo abrir para lectura\n" );
			iRes = BOOL_VAL_FALSO;
		} 
		else
		{
			char * p_cLinea1 = SFicTxtLeerLinea ( p_ficObj );
			if ( ES_NULO ( p_cLinea1 ) || ( CadComparar ( p_cLinea1, "Este es" ) != COMP_IGUAL ) )
			{
				printf( "Error caso 3: se esperaba \"Este es\": [%s]\n", ES_VALIDO ( p_cLinea1 ) ? p_cLinea1 : "(nulo)" );
				iRes = BOOL_VAL_FALSO;
			}
			MemLiberar ( (void **) &p_cLinea1 );
			if ( SFicTxtEstaEnFinal ( p_ficObj ) == 1 )
			{
				printf( "Error caso 4: No deberia haber llegado al final\n" );
				iRes = BOOL_VAL_FALSO;
			}
			char * p_cLinea2 = SFicTxtLeerLinea ( p_ficObj );
			if ( ES_NULO ( p_cLinea2 ) || ( CadComparar ( p_cLinea2, "un fichero" ) != COMP_IGUAL ) )
			{
				printf( "Error caso 5: se esperaba \"un fichero\": [%s]\n", ES_VALIDO ( p_cLinea2 ) ? p_cLinea2 : "(nulo)" );
				iRes = BOOL_VAL_FALSO;
			}
			MemLiberar ( (void **) &p_cLinea2 );
			char * p_cLinea3 = SFicTxtLeerLinea ( p_ficObj );
			if ( ES_NULO ( p_cLinea3 ) || ( CadComparar ( p_cLinea3, "de ejemplo" ) != COMP_IGUAL ) )
			{
				printf( "Error caso 6: se esperaba \"de ejemplo\": [%s]\n", ES_VALIDO ( p_cLinea3 ) ? p_cLinea3 : "(nulo)" );
				iRes = BOOL_VAL_FALSO;
			}
			MemLiberar ( (void **) &p_cLinea3 );
			char * p_cLinea4 = SFicTxtLeerLinea ( p_ficObj );
			if ( ES_NULO ( p_cLinea4 ) || ( CadComparar ( p_cLinea4, "en formato DOS" ) != COMP_IGUAL ) )
			{
				printf( "Error caso 7: se esperaba \"en formato DOS\": [%s]\n", ES_VALIDO ( p_cLinea4 ) ? p_cLinea4 : "(nulo)" );
				iRes = BOOL_VAL_FALSO;
			}
			MemLiberar ( (void **) &p_cLinea4 );
			char * p_cLinea5 = SFicTxtLeerLinea ( p_ficObj );
			if ( ES_VALIDO ( p_cLinea5 ) )
			{
				printf( "Error caso 8: se esperaba (nulo): [%s]\n", p_cLinea5 );
				iRes = BOOL_VAL_FALSO;
			}
			MemLiberar ( (void **) &p_cLinea5 );
			if ( SFicTxtEstaEnFinal ( p_ficObj ) == 0 )
			{
				printf( "Error caso 9: deberia haber llegado al final\n" );
				iRes = BOOL_VAL_FALSO;
			}
		}
		SFicTxtCerrar ( p_ficObj );
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el objeto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSFicTxtLeer02 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SFicTxtLeer 02:\n" );
	SisCrearDirectorio ( FIC_TEST_DIR_RESULTS );
	SFicTexto * p_ficObj = SFicTxtCrearExt ( FIC_TEST_DIR_DATA, "ejemploUNIX.txt", EST_FTXT_UNIX );
	if ( ES_VALIDO ( p_ficObj ) )
	{
		if ( SFicTxtEsEstiloUNIX ( p_ficObj ) != 1 )
		{
			printf( "Error caso 1: se esperaba estilo UNIX\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Escritura de dos lineas (vaciando el fichero). */
		if ( SFicTxtAbrir ( p_ficObj, MOD_APR_LECTURA ) != 1 )
		{
			printf( "Error caso 2: no se pudo abrir para lectura\n" );
			iRes = BOOL_VAL_FALSO;
		}
		else
		{
			char * p_cLinea1 = SFicTxtLeerLinea ( p_ficObj );
			if ( ES_NULO ( p_cLinea1 ) || ( CadComparar ( p_cLinea1, "Este es" ) != COMP_IGUAL ) )
			{
				printf( "Error caso 3: se esperaba \"Este es\": [%s]\n", ES_VALIDO ( p_cLinea1 ) ? p_cLinea1 : "(nulo)" );
				iRes = BOOL_VAL_FALSO;
			}
			MemLiberar ( (void **) &p_cLinea1 );
			if ( SFicTxtEstaEnFinal ( p_ficObj ) == 1 )
			{
				printf( "Error caso 4: No deberia haber llegado al final\n" );
				iRes = BOOL_VAL_FALSO;
			}
			char * p_cLinea2 = SFicTxtLeerLinea ( p_ficObj );
			if ( ES_NULO ( p_cLinea2 ) || ( CadComparar ( p_cLinea2, "un fichero" ) != COMP_IGUAL ) )
			{
				printf( "Error caso 5: se esperaba \"un fichero\": [%s]\n", ES_VALIDO ( p_cLinea2 ) ? p_cLinea2 : "(nulo)" );
				iRes = BOOL_VAL_FALSO;
			}
			MemLiberar ( (void **) &p_cLinea2 );
			char * p_cLinea3 = SFicTxtLeerLinea ( p_ficObj );
			if ( ES_NULO ( p_cLinea3 ) || ( CadComparar ( p_cLinea3, "de ejemplo" ) != COMP_IGUAL ) )
			{
				printf( "Error caso 6: se esperaba \"de ejemplo\": [%s]\n", ES_VALIDO ( p_cLinea3 ) ? p_cLinea3 : "(nulo)" );
				iRes = BOOL_VAL_FALSO;
			}
			MemLiberar ( (void **) &p_cLinea3 );
			char * p_cLinea4 = SFicTxtLeerLinea ( p_ficObj );
			if ( ES_NULO ( p_cLinea4 ) || ( CadComparar ( p_cLinea4, "en formato UNIX" ) != COMP_IGUAL ) )
			{
				printf( "Error caso 7: se esperaba \"en formato UNIX\": [%s]\n", ES_VALIDO ( p_cLinea4 ) ? p_cLinea4 : "(nulo)" );
				iRes = BOOL_VAL_FALSO;
			}
			MemLiberar ( (void **) &p_cLinea4 );
			char * p_cLinea5 = SFicTxtLeerLinea ( p_ficObj );
			if ( ES_VALIDO ( p_cLinea5 ) )
			{
				printf( "Error caso 8: se esperaba (nulo): [%s]\n", p_cLinea5 );
				iRes = BOOL_VAL_FALSO;
			}
			MemLiberar ( (void **) &p_cLinea5 );
			if ( SFicTxtEstaEnFinal ( p_ficObj ) == 0 )
			{
				printf( "Error caso 9: deberia haber llegado al final\n" );
				iRes = BOOL_VAL_FALSO;
			}
			SFicTxtCerrar ( p_ficObj );
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el objeto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSFicTxtLeer03 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SFicTxtLeer 03:\n" );
	SisCrearDirectorio ( FIC_TEST_DIR_RESULTS );
	SFicTexto * p_ficObj = SFicTxtCrearExt ( FIC_TEST_DIR_DATA, "ejemploUNIX.txt", EST_FTXT_DOS );
	if ( ES_VALIDO ( p_ficObj ) )
	{
		if ( SFicTxtEsEstiloDOS ( p_ficObj ) != 1 )
		{
			printf( "Error caso 1: se esperaba estilo DOS\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Escritura de dos lineas (vaciando el fichero). */
		if ( SFicTxtAbrir ( p_ficObj, MOD_APR_LECTURA ) != 1 )
		{
			printf( "Error caso 2: no se pudo abrir para lectura\n" );
			iRes = BOOL_VAL_FALSO;
		} 
		else 
		{
			if ( SFicTxtLecturaEstricta ( p_ficObj ) == 1 )
			{
				printf( "Error caso 3: Deberia ser de lectura no estricta por defecto\n" );
				iRes = BOOL_VAL_FALSO;
			}
			SFicTxtActivarLecturaEstricta ( p_ficObj );
			if ( SFicTxtLecturaEstricta ( p_ficObj ) == 0 )
			{
				printf( "Error caso 4: Deberia ser de lectura estricta\n" );
				iRes = BOOL_VAL_FALSO;
			}
			char * p_cLinea1 = SFicTxtLeerLinea ( p_ficObj );
			if ( ES_NULO ( p_cLinea1 ) || ( CadComparar ( p_cLinea1, "Este es\nun fichero\nde ejemplo\nen formato UNIX\n" ) != COMP_IGUAL ) )
			{
				printf( "Error caso 5: valor incorrecto: [%s]\n", ES_VALIDO ( p_cLinea1 ) ? p_cLinea1 : "(nulo)" );
				iRes = BOOL_VAL_FALSO;
			}
			MemLiberar ( (void **) &p_cLinea1 );
			char * p_cLinea2 = SFicTxtLeerLinea ( p_ficObj );
			if ( ES_VALIDO ( p_cLinea2 ) )
			{
				printf( "Error caso 6: se esperaba (nulo): [%s]\n", p_cLinea2 );
				iRes = BOOL_VAL_FALSO;
			}
			MemLiberar ( (void **) &p_cLinea2 );
			if ( SFicTxtEstaEnFinal ( p_ficObj ) == 0 )
			{
				printf( "Error caso 7: deberia haber llegado al final\n" );
				iRes = BOOL_VAL_FALSO;
			}
			SFicTxtCerrar ( p_ficObj );
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el objeto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSFicTxtLeer04 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SFicTxtLeer 04:\n" );
	SisCrearDirectorio ( FIC_TEST_DIR_RESULTS );
	SFicTexto * p_ficObj = SFicTxtCrearExt ( FIC_TEST_DIR_DATA, "ejemploUNIX.txt", EST_FTXT_DOS );
	if ( ES_VALIDO ( p_ficObj ) )
	{
		if ( SFicTxtEsEstiloDOS ( p_ficObj ) != 1 )
		{
			printf( "Error caso 1: se esperaba estilo DOS\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Escritura de dos lineas (vaciando el fichero). */
		if ( SFicTxtAbrir ( p_ficObj, MOD_APR_LECTURA ) != 1 )
		{
			printf( "Error caso 2: no se pudo abrir para lectura\n" );
			iRes = BOOL_VAL_FALSO;
		}
		else
		{
			SFicTxtDesactivarLecturaEstricta ( p_ficObj );
			if ( SFicTxtLecturaEstricta ( p_ficObj ) == 1 )
			{
				printf( "Error caso 3: Deberia ser de lectura no estricta\n" );
				iRes = BOOL_VAL_FALSO;
			}
			char * p_cLinea1 = SFicTxtLeerLinea ( p_ficObj );
			if ( ES_NULO ( p_cLinea1 ) || ( CadComparar ( p_cLinea1, "Este es" ) != COMP_IGUAL ) )
			{
				printf( "Error caso 4: se esperaba \"Este es\": [%s]\n", ES_VALIDO ( p_cLinea1 ) ? p_cLinea1 : "(nulo)" );
				iRes = BOOL_VAL_FALSO;
			}
			MemLiberar ( (void **) &p_cLinea1 );
			char * p_cLinea2 = SFicTxtLeerLinea ( p_ficObj );
			if ( ES_NULO ( p_cLinea2 ) || ( CadComparar ( p_cLinea2, "un fichero" ) != COMP_IGUAL ) )
			{
				printf( "Error caso 5: se esperaba \"un fichero\": [%s]\n", ES_VALIDO ( p_cLinea2 ) ? p_cLinea2 : "(nulo)" );
				iRes = BOOL_VAL_FALSO;
			}
			MemLiberar ( (void **) &p_cLinea2 );
			char * p_cLinea3 = SFicTxtLeerLinea ( p_ficObj );
			if ( ES_NULO ( p_cLinea3 ) || ( CadComparar ( p_cLinea3, "de ejemplo" ) != COMP_IGUAL ) )
			{
				printf( "Error caso 6: se esperaba \"de ejemplo\": [%s]\n", ES_VALIDO ( p_cLinea3 ) ? p_cLinea3 : "(nulo)" );
				iRes = BOOL_VAL_FALSO;
			}
			MemLiberar ( (void **) &p_cLinea3 );
			char * p_cLinea4 = SFicTxtLeerLinea ( p_ficObj );
			if ( ES_NULO ( p_cLinea4 ) || ( CadComparar ( p_cLinea4, "en formato UNIX" ) != COMP_IGUAL ) )
			{
				printf( "Error caso 7: se esperaba \"en formato UNIX\": [%s]\n", ES_VALIDO ( p_cLinea4 ) ? p_cLinea4 : "(nulo)" );
				iRes = BOOL_VAL_FALSO;
			}
			MemLiberar ( (void **) &p_cLinea4 );
			char * p_cLinea5 = SFicTxtLeerLinea ( p_ficObj );
			if ( ES_VALIDO ( p_cLinea5 ) )
			{
				printf( "Error caso 8: se esperaba (nulo): [%s]\n", p_cLinea5 );
				iRes = BOOL_VAL_FALSO;
			}
			MemLiberar ( (void **) &p_cLinea5 );
			if ( SFicTxtEstaEnFinal ( p_ficObj ) == 0 )
			{
				printf( "Error caso 9: deberia haber llegado al final\n" );
				iRes = BOOL_VAL_FALSO;
			}
			SFicTxtCerrar ( p_ficObj );
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el objeto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSFicTxtNulo01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SFicTxtNulo 01:\n" );
	if ( SFicTxtEsValido ( NULL ) != 0 )
	{
		printf( "Error caso 1: se esperaba no valido con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( SFicTxtLeerLinea ( NULL ) ) )
	{
		printf( "Error caso 2: se esperaba linea nula con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SFicTxtEscribirLinea ( NULL, "x" ) != 0 )
	{
		printf( "Error caso 3: se esperaba fallo al escribir en nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSFicTxtFicheroVacio01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SFicTxtFicheroVacio 01:\n" );
	SFicTexto * p_ficObj = SFicTxtCrear ( FIC_TEST_FIC_VACIO );
	if ( ES_VALIDO ( p_ficObj ) )
	{
		if ( SFicTxtAbrir ( p_ficObj, MOD_APR_LECTURA ) != 1 )
		{
			printf( "Error caso 1: no se pudo abrir el fichero vacio para lectura\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Un fichero vacio no tiene ninguna linea. */
		char * p_cLinea = SFicTxtLeerLinea ( p_ficObj );
		if ( ES_VALIDO ( p_cLinea ) )
		{
			printf( "Error caso 2: se esperaba linea nula en un fichero vacio: [%s]\n", p_cLinea );
			iRes = BOOL_VAL_FALSO;
			MemLiberar ( (void **) &p_cLinea );
		}
		SFicTxtCerrar ( p_ficObj );
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el objeto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* Recurso de entrada compartido: solo destruir, nunca eliminar. */
	SFicTxtDestruir ( &p_ficObj );
	return ( iRes );
}

int TestSFicTexto ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SFicTexto]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSFicTxtEscribirLeer01 () == BOOL_VAL_CIERTO ) &&
			( TestSFicTxtLeer01 () == BOOL_VAL_CIERTO ) &&
			( TestSFicTxtLeer02 () == BOOL_VAL_CIERTO ) &&
			( TestSFicTxtLeer03 () == BOOL_VAL_CIERTO ) &&
			( TestSFicTxtLeer04 () == BOOL_VAL_CIERTO ) &&
			( TestSFicTxtFicheroVacio01 () == BOOL_VAL_CIERTO ) &&
			( TestSFicTxtNulo01 () == BOOL_VAL_CIERTO ) )
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
