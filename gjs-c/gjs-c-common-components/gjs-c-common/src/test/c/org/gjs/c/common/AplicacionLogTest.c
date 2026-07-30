#include "Base.h"

#include "AplicacionLog.h"
#include "NivelesLog.h"



static int TestAplicLogCicloVida01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test AplicLogCicloVida 01:\n" );
	/* Estado inicial: sin inicializar. */
	if ( AplicLogEstaInicializado () != 0 )
	{
		printf( "Error caso 1: el log de aplicacion no deberia estar inicializado\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( AplicLogActivado () != 0 )
	{
		printf( "Error caso 2: el log no deberia estar activado sin inicializar\n" );
		iRes = BOOL_VAL_FALSO;
	}

	/* Inicializacion: crea el fichero de log (con fecha) en el directorio actual. */
	if ( AplicLogInicializarDef ( "aplictest" ) != 1 )
	{
		printf( "Error caso 3: no se pudo inicializar el log de aplicacion\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( AplicLogEstaInicializado () != 1 )
	{
		printf( "Error caso 4: el log deberia constar inicializado\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( AplicLogActivado () != 1 )
	{
		printf( "Error caso 5: el log deberia estar activado tras inicializar\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( AplicLogNivel () != LOG_NIVEL_DEFECTO )
	{
		printf( "Error caso 6: se esperaba el nivel por defecto: %d\n", AplicLogNivel () );
		iRes = BOOL_VAL_FALSO;
	}
	if ( AplicLogEstablecerNivel ( LOG_NIVEL_AVISO ) != 1 )
	{
		printf( "Error caso 7: no se pudo establecer el nivel AVISO\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( AplicLogNivel () != LOG_NIVEL_AVISO )
	{
		printf( "Error caso 8: el nivel deberia ser AVISO\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( AplicLogAnotarForzado ( "Linea de prueba del log de aplicacion" ) != 1 )
	{
		printf( "Error caso 9: se esperaba 1 al anotar en el log\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* Elimina el fichero de log del disco y deja el subsistema sin inicializar. */
	AplicLogEliminar ();
	if ( AplicLogEstaInicializado () != 0 )
	{
		printf( "Error caso 10: tras eliminar no deberia estar inicializado\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}



int TestAplicacionLog ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test AplicacionLog]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( TestAplicLogCicloVida01 () == BOOL_VAL_CIERTO )
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
