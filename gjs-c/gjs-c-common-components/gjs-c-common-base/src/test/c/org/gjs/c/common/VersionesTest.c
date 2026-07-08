#include "Base.h"

#include "Versiones.h"



static int TestVersCadena01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test VersCadena 01:\n" );
	char * p_cRes = NULL;

	p_cRes = VersCadena ( 1, -1, -1, -1 );
	if ( ES_NULO ( p_cRes ) || ( strcmp ( p_cRes, "1" ) != 0 ) )
	{
		printf( "Error caso 1: se esperaba \"1\": [%s]\n", ES_VALIDO ( p_cRes ) ? p_cRes : "(nulo)" );
		iRes = BOOL_VAL_FALSO;
	}
	MemLiberar ( (void **) &p_cRes );

	p_cRes = VersCadena ( 1, 2, -1, -1 );
	if ( ES_NULO ( p_cRes ) || ( strcmp ( p_cRes, "1.2" ) != 0 ) )
	{
		printf( "Error caso 2: se esperaba \"1.2\": [%s]\n", ES_VALIDO ( p_cRes ) ? p_cRes : "(nulo)" );
		iRes = BOOL_VAL_FALSO;
	}
	MemLiberar ( (void **) &p_cRes );

	p_cRes = VersCadena ( 1, 2, 3, -1 );
	if ( ES_NULO ( p_cRes ) || ( strcmp ( p_cRes, "1.2.3" ) != 0 ) )
	{
		printf( "Error caso 3: se esperaba \"1.2.3\": [%s]\n", ES_VALIDO ( p_cRes ) ? p_cRes : "(nulo)" );
		iRes = BOOL_VAL_FALSO;
	}
	MemLiberar ( (void **) &p_cRes );

	p_cRes = VersCadena ( 1, 2, 3, 4 );
	if ( ES_NULO ( p_cRes ) || ( strcmp ( p_cRes, "1.2.3.4" ) != 0 ) )
	{
		printf( "Error caso 4: se esperaba \"1.2.3.4\": [%s]\n", ES_VALIDO ( p_cRes ) ? p_cRes : "(nulo)" );
		iRes = BOOL_VAL_FALSO;
	}
	MemLiberar ( (void **) &p_cRes );

	/* Una version negativa debe fallar. */
	p_cRes = VersCadena ( -1, -1, -1, -1 );
	if ( ES_VALIDO ( p_cRes ) )
	{
		printf( "Error caso 5: se esperaba nulo para version negativa\n" );
		iRes = BOOL_VAL_FALSO;
	}
	MemLiberar ( (void **) &p_cRes );

	return ( iRes );
}

static int TestVersProcesar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test VersProcesar 01:\n" );
	int iVersion = -1;
	int iSubversion = -1;
	int iRevision = -1;
	int iCorreccion = -1;

	int iProc = VersProcesar ( "1.2.3.4", &iVersion, &iSubversion, &iRevision, &iCorreccion );
	if ( iProc != 1 )
	{
		printf( "Error caso 1: se esperaba resultado 1: %d\n", iProc );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ( iVersion != 1 ) || ( iSubversion != 2 ) || ( iRevision != 3 ) || ( iCorreccion != 4 ) )
	{
		printf( "Error caso 2: se esperaba 1.2.3.4: %d.%d.%d.%d\n",
				iVersion, iSubversion, iRevision, iCorreccion );
		iRes = BOOL_VAL_FALSO;
	}

	/* Version parcial. */
	iVersion = -1;
	iSubversion = -1;
	if ( VersProcesar ( "2.5", &iVersion, &iSubversion, NULL, NULL ) != 1 )
	{
		printf( "Error caso 3: se esperaba resultado 1\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ( iVersion != 2 ) || ( iSubversion != 5 ) )
	{
		printf( "Error caso 4: se esperaba 2.5: %d.%d\n", iVersion, iSubversion );
		iRes = BOOL_VAL_FALSO;
	}

	/* Cadena nula debe fallar. */
	if ( VersProcesar ( NULL, &iVersion, &iSubversion, &iRevision, &iCorreccion ) != 0 )
	{
		printf( "Error caso 5: se esperaba resultado 0 para cadena nula\n" );
		iRes = BOOL_VAL_FALSO;
	}
	ErrLimpiar ();
	return ( iRes );
}

static int TestVersIdaYVuelta01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test VersIdaYVuelta 01:\n" );
	int iVersion = -1;
	int iSubversion = -1;
	int iRevision = -1;
	int iCorreccion = -1;

	char * p_cVers = VersCadena ( 3, 1, 0, 12 );
	if ( VersProcesar ( p_cVers, &iVersion, &iSubversion, &iRevision, &iCorreccion ) != 1 )
	{
		printf( "Error caso 1: no se pudo procesar la cadena generada\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ( iVersion != 3 ) || ( iSubversion != 1 ) || ( iRevision != 0 ) || ( iCorreccion != 12 ) )
	{
		printf( "Error caso 2: se esperaba 3.1.0.12: %d.%d.%d.%d\n",
				iVersion, iSubversion, iRevision, iCorreccion );
		iRes = BOOL_VAL_FALSO;
	}
	MemLiberar ( (void **) &p_cVers );
	return ( iRes );
}



int TestVersiones ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test Versiones]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestVersCadena01 () == BOOL_VAL_CIERTO ) &&
			( TestVersProcesar01 () == BOOL_VAL_CIERTO ) &&
			( TestVersIdaYVuelta01 () == BOOL_VAL_CIERTO ) )
	{
		printf ( "%sResultado: OK%s\n", ANSI_VERDE, ANSI_RESETEAR );
	}
	else
	{
		printf ( "%sResultado: KO%s\n", ANSI_ROJO, ANSI_RESETEAR );
		iRes = BOOL_VAL_FALSO;
	}
	ErrLimpiar ();
	printf ( "%s[Fin]%s\n", ANSI_AMARILLO, ANSI_RESETEAR );
	return ( iRes );
}
