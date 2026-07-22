#include "Base.h"

#include "AplicacionInformacion.h"



static int TestAplicInicializar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test AplicInicializar 01:\n" );
	/* Se pasa iConsola = 1 a proposito: con 0, AplicInicializar cierra la consola
	   (en POSIX hace fclose de stdout) y romperia el resto de la suite. */
	if ( AplicInicializar ( "MiAplicacion", 3, 2, 1, 20080325, 1 ) != 1 )
	{
		printf( "Error caso 1: no se pudo inicializar la aplicacion\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( AplicEstaInicializada () != 1 )
	{
		printf( "Error caso 2: la aplicacion deberia constar inicializada\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( AplicVersion () != 3 )
	{
		printf( "Error caso 3: se esperaba version 3: %d\n", AplicVersion () );
		iRes = BOOL_VAL_FALSO;
	}
	if ( AplicSubversion () != 2 )
	{
		printf( "Error caso 4: se esperaba subversion 2: %d\n", AplicSubversion () );
		iRes = BOOL_VAL_FALSO;
	}
	if ( AplicRevision () != 1 )
	{
		printf( "Error caso 5: se esperaba revision 1: %d\n", AplicRevision () );
		iRes = BOOL_VAL_FALSO;
	}
	if ( AplicPID () <= 0 )
	{
		printf( "Error caso 6: se esperaba PID > 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	char * p_cNombre = (char *) AplicNombre ();
	if ( ES_NULO ( p_cNombre ) || ( strcmp ( p_cNombre, "MiAplicacion" ) != 0 ) )
	{
		printf( "Error caso 7: se esperaba nombre \"MiAplicacion\": [%s]\n", ES_VALIDO ( p_cNombre ) ? p_cNombre : "(nulo)" );
		iRes = BOOL_VAL_FALSO;
	}
	MemLiberar ( (void **) &p_cNombre );
	char * p_cVer = (char *) AplicCadenaVersion ();
	if ( ES_NULO ( p_cVer ) || ( strcmp ( p_cVer, "3.2.1" ) != 0 ) )
	{
		printf( "Error caso 8: se esperaba cadena de version \"3.2.1\": [%s]\n", ES_VALIDO ( p_cVer ) ? p_cVer : "(nulo)" );
		iRes = BOOL_VAL_FALSO;
	}
	MemLiberar ( (void **) &p_cVer );

	/* Reinicializar sin finalizar antes debe fallar. */
	if ( AplicInicializar ( "Otra", 1, 0, 0, 20080325, 1 ) != 0 )
	{
		printf( "Error caso 9: no se esperaba reinicializar una aplicacion ya inicializada\n" );
		iRes = BOOL_VAL_FALSO;
	}

	AplicFinalizar ();
	if ( AplicEstaInicializada () != 0 )
	{
		printf( "Error caso 10: tras finalizar no deberia constar inicializada\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( AplicPID () != -1 )
	{
		printf( "Error caso 11: tras finalizar el PID deberia ser -1\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}



int TestAplicacionInformacion ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test AplicacionInformacion]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestAplicInicializar01 () == BOOL_VAL_CIERTO ) )
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
