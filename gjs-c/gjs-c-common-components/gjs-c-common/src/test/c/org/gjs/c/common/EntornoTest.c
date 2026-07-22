#include "Base.h"

#include "CEntorno.h"
#include "SistemaFicheros.h"



static int TestEntModoTest01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test EntModoTest 01:\n" );
	/* No se prueba EntInicializar/EntFinalizar (inicializacion global pesada:
	   crea directorios, inicializa la aplicacion y podria cerrar la consola). */
	if ( EntEstaInicializado () != 0 )
	{
		printf( "Error caso 1: el entorno no deberia estar inicializado\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( EntEstaEnModoTest () != 0 )
	{
		printf( "Error caso 2: el modo test no deberia estar activo por defecto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	EntActivarModoTest ();
	if ( EntEstaEnModoTest () != 1 )
	{
		printf( "Error caso 3: no se activo el modo test\n" );
		iRes = BOOL_VAL_FALSO;
	}
	EntDesactivarModoTest ();
	if ( EntEstaEnModoTest () != 0 )
	{
		printf( "Error caso 4: no se desactivo el modo test\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestEntDirectorio01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test EntDirectorio 01:\n" );
	/* Se usa el directorio actual (ya existe) para no crear nada nuevo. */
	char * p_cCwd = SisDirectorioActual ();
	if ( ES_NULO ( p_cCwd ) )
	{
		printf( "Error caso 0: no se pudo obtener el directorio actual\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		EntEstablecerDirectorioDatos ( p_cCwd );
		const char * p_cDir = EntDirectorioDatos ();
		if ( ES_NULO ( p_cDir ) || ( strcmp ( p_cDir, p_cCwd ) != 0 ) )
		{
			printf( "Error caso 1: el directorio de datos no coincide con el establecido\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	MemLiberar ( (void **) &p_cCwd );
	return ( iRes );
}



int TestEntorno ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test Entorno]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestEntModoTest01 () == BOOL_VAL_CIERTO ) &&
			( TestEntDirectorio01 () == BOOL_VAL_CIERTO ) )
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
