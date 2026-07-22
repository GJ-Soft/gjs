#include "Base.h"

#include "ConsolaDepuracion.h"
#include "CEntorno.h"



static int TestConDepFueraModoTest01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test ConDepFueraModoTest 01:\n" );
	/* Fuera de modo test todas las rutinas son no-op seguras (no tocan la
	   consola ni bloquean). NO se prueba ConDepEsperar (bloquea con getchar). */
	EntDesactivarModoTest ();
	if ( ConDepEstaAbierta () != 0 )
	{
		printf( "Error caso 1: la consola de depuracion no deberia estar abierta\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ConDepAbrir () != 1 )
	{
		printf( "Error caso 2: fuera de modo test ConDepAbrir debe devolver 1\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ConDepEscribirLinea ( "linea fuera de modo test" ) != 1 )
	{
		printf( "Error caso 3: fuera de modo test ConDepEscribirLinea debe devolver 1\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestConDepModoTest01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test ConDepModoTest 01:\n" );
	EntActivarModoTest ();
	if ( ConDepAbrir () != 1 )
	{
		printf( "Error caso 1: no se pudo abrir la consola de depuracion\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ConDepEstaAbierta () != 1 )
	{
		printf( "Error caso 2: la consola de depuracion deberia estar abierta\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* Se ejercita la escritura (imprime por consola). No se asera el retorno:
	   ConDepEscribirLinea dimensiona un buffer con AplicConAncho(), que devuelve
	   0 con la salida redirigida. */
	ConDepEscribirLinea ( "linea de depuracion" );
	ConDepCerrar ();
	if ( ConDepEstaAbierta () != 0 )
	{
		printf( "Error caso 3: tras cerrar no deberia estar abierta\n" );
		iRes = BOOL_VAL_FALSO;
	}
	EntDesactivarModoTest ();
	return ( iRes );
}



int TestConsolaDepuracion ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test ConsolaDepuracion]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestConDepFueraModoTest01 () == BOOL_VAL_CIERTO ) &&
			( TestConDepModoTest01 () == BOOL_VAL_CIERTO ) )
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
