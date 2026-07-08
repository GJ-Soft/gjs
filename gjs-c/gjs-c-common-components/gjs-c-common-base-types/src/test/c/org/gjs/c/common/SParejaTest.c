#include "Base.h"

#include "SPareja.h"



static void * CrearDatoEntero ( int iValor )
{
	int * p_iDato = (int *) MemReservar ( sizeof ( int ) );
	if ( ES_VALIDO ( p_iDato ) )
	{
		*p_iDato = iValor;
	}
	return ( (void *) p_iDato );
}



static int TestSPrjCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SPrjCrear 01:\n" );

	/* Gestionando: la pareja se hace duena de los dos datos. */
	SPareja * p_prjObj = SPrjCrearGestionando ( CrearDatoEntero ( 10 ), CrearDatoEntero ( 20 ) );
	if ( ES_NULO ( p_prjObj ) )
	{
		printf( "Error caso 1: no se esperaba nulo al crear\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SPrjEsValido ( p_prjObj ) != 1 )
		{
			printf( "Error caso 2: la pareja recien creada deberia ser valida\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( *( (int *) SPrjObtenerPrimero ( p_prjObj ) ) != 10 ) ||
			 ( *( (int *) SPrjObtenerSegundo ( p_prjObj ) ) != 20 ) )
		{
			printf( "Error caso 3: se esperaban los valores 10 y 20\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SPrjLiberacionMemoriaActivada ( p_prjObj ) != 1 )
		{
			printf( "Error caso 4: la liberacion deberia estar activada ( gestionando )\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	SPrjDestruir ( &p_prjObj );

	if ( ES_VALIDO ( p_prjObj ) )
	{
		printf( "Error caso 5: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* Crear con datos nulos debe fallar. */
	if ( ES_VALIDO ( SPrjCrearGestionando ( NULL, NULL ) ) )
	{
		printf( "Error caso 6: se esperaba nulo al crear con datos nulos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSPrjEstablecer01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SPrjEstablecer 01:\n" );

	SPareja * p_prjObj = SPrjCrearGestionando ( CrearDatoEntero ( 10 ), CrearDatoEntero ( 20 ) );
	if ( ES_VALIDO ( p_prjObj ) )
	{
		/* Establecer libera el dato anterior ( gestionando ) y coloca el nuevo. */
		SPrjEstablecerPrimero ( p_prjObj, CrearDatoEntero ( 30 ) );
		if ( *( (int *) SPrjObtenerPrimero ( p_prjObj ) ) != 30 )
		{
			printf( "Error caso 1: el primero deberia ser ahora 30\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SPrjEstablecerSegundo ( p_prjObj, CrearDatoEntero ( 40 ) );
		if ( *( (int *) SPrjObtenerSegundo ( p_prjObj ) ) != 40 )
		{
			printf( "Error caso 2: el segundo deberia ser ahora 40\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la pareja\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SPrjDestruir ( &p_prjObj );
	return ( iRes );
}

static int TestSPrjSoloPtr01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SPrjSoloPtr 01:\n" );

	void * p_d1 = CrearDatoEntero ( 10 );
	void * p_d2 = CrearDatoEntero ( 20 );

	/* SoloPtr: la pareja NO gestiona la memoria de los datos. */
	SPareja * p_prjObj = SPrjCrearSoloPtr ( p_d1, p_d2 );
	if ( ES_VALIDO ( p_prjObj ) )
	{
		if ( SPrjLiberacionMemoriaActivada ( p_prjObj ) != 0 )
		{
			printf( "Error caso 1: la liberacion no deberia estar activada ( solo ptr )\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SPrjDestruir ( &p_prjObj );
		/* Al destruir no se liberan los datos: siguen siendo validos. */
		if ( *( (int *) p_d1 ) != 10 )
		{
			printf( "Error caso 2: los datos no deberian haberse liberado\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la pareja\n" );
		iRes = BOOL_VAL_FALSO;
	}
	MemLiberar ( (void **) &p_d1 );
	MemLiberar ( (void **) &p_d2 );
	return ( iRes );
}

static int TestSPrjInvalidos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SPrjInvalidos 01:\n" );

	if ( SPrjEsValido ( NULL ) != 0 )
	{
		printf( "Error caso 1: una pareja nula no deberia ser valida\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( SPrjObtenerPrimero ( NULL ) ) )
	{
		printf( "Error caso 2: el primero de una pareja nula deberia ser nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SPareja * p_prjNula = NULL;
	SPrjDestruir ( &p_prjNula );
	return ( iRes );
}



int TestSPareja ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SPareja]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSPrjCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSPrjEstablecer01 () == BOOL_VAL_CIERTO ) &&
			( TestSPrjSoloPtr01 () == BOOL_VAL_CIERTO ) &&
			( TestSPrjInvalidos01 () == BOOL_VAL_CIERTO ) )
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
