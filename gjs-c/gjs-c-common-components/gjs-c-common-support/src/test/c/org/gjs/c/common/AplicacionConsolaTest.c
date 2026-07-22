#include "Base.h"

#include "AplicacionConsola.h"



static int TestAplicConEstado01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test AplicConEstado 01:\n" );
	/* La consola arranca disponible. NO se cierra (en POSIX cerrar hace fclose
	   de stdout/stderr y romperia el resto de la suite). Tampoco se prueban las
	   rutinas de lectura, que bloquean esperando entrada. */
	if ( AplicConEstaAbierta () != 1 )
	{
		printf( "Error caso 1: se esperaba la consola abierta\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( AplicConAbrir () != 1 )
	{
		printf( "Error caso 2: se esperaba 1 al abrir una consola ya disponible\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestAplicConDibujar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test AplicConDibujar 01:\n" );
	if ( AplicConDibujarLineaExt ( 10, 0, '-' ) != 1 )
	{
		printf( "\nError caso 1a: se esperaba dibujar la linea\n" );
		iRes = BOOL_VAL_FALSO;
	}
	printf ( "\n" );
	if ( AplicConDibujarLineaDiscontinua () != 1 )
	{
		printf( "\nError caso 1b: se esperaba dibujar la linea\n" );
		iRes = BOOL_VAL_FALSO;
	}
	printf ( "\n" );
	if ( AplicConDibujarLineaSimple () != 1 )
	{
		printf( "\nError caso 1c: se esperaba dibujar la linea\n" );
		iRes = BOOL_VAL_FALSO;
	}
	printf ( "\n" );
	if ( AplicConDibujarLineaDoble () != 1 )
	{
		printf( "\nError caso 1d: se esperaba dibujar la linea\n" );
		iRes = BOOL_VAL_FALSO;
	}
	printf ( "\n" );
	if ( AplicConDibujarLineaExt ( 0, 0, '-' ) != 0 )
	{
		printf( "Error caso 2: se esperaba 0 con ancho no valido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( AplicConDibujarRectangulo ( 3, 10, 0 ) != 1 )
	{
		printf( "\nError caso 3: se esperaba dibujar el rectangulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	printf ( "\n" );
	if ( AplicConDibujarRectangulo ( 0, 10, 0 ) != 0 )
	{
		printf( "Error caso 4: se esperaba 0 con alto no valido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	printf ( "\n" );
	if ( AplicConDibujarRectanguloDoble ( 0, 10, 0 ) != 0 )
	{
		printf( "Error caso 5: se esperaba 0 con alto no valido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}



int TestAplicacionConsola ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test AplicacionConsola]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestAplicConEstado01 () == BOOL_VAL_CIERTO ) &&
			( TestAplicConDibujar01 () == BOOL_VAL_CIERTO ) )
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
