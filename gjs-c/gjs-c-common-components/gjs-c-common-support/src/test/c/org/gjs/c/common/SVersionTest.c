#include "Base.h"

#include "SVersion.h"



static int TestSVerCicloVida01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SVerCicloVida 01:\n" );
	/* SVerCrearDef usa la fecha actual (siempre valida) y version 1.0.0. */
	SVersion * p_verObj = SVerCrearDef ();
	if ( ES_NULO ( p_verObj ) )
	{
		printf( "Error caso 0: no se pudo crear la version por defecto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SVerVersion ( p_verObj ) != 1 )
		{
			printf( "Error caso 1: se esperaba version 1: %d\n", SVerVersion ( p_verObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SVerSubversion ( p_verObj ) != 0 )
		{
			printf( "Error caso 2: se esperaba subversion 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SVerEsValida ( p_verObj ) != 1 )
		{
			printf( "Error caso 3: se esperaba una version valida\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Setters. */
		if ( SVerEstablecerVersion ( p_verObj, 5 ) != 1 )
		{
			printf( "Error caso 4: no se pudo establecer la version\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SVerEstablecerSubversion ( p_verObj, 4 ) != 1 )
		{
			printf( "Error caso 5: no se pudo establecer la subversion\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SVerEstablecerRevision ( p_verObj, 3 ) != 1 )
		{
			printf( "Error caso 6: no se pudo establecer la revision\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SVerVersion ( p_verObj ) != 5 ) || ( SVerSubversion ( p_verObj ) != 4 ) || ( SVerRevision ( p_verObj ) != 3 ) )
		{
			printf( "Error caso 7: los valores no coinciden con lo establecido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Una version <= 0 no es valida. */
		if ( SVerEstablecerVersion ( p_verObj, 0 ) != 0 )
		{
			printf( "Error caso 8: no se esperaba aceptar una version 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	SVerDestruir ( &p_verObj );
	return ( iRes );
}

static int TestSVerCadena01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SVerCadena 01:\n" );
	SVersion * p_verObj = SVerCrear ( 3, 2, 1, 20080325 );
	if ( ES_NULO ( p_verObj ) )
	{
		printf( "Error caso 0: no se pudo crear la version 3.2.1 con fecha 20080325\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		char * p_cLarga = SVerCadenaVersion ( p_verObj, 0 );
		if ( ES_NULO ( p_cLarga ) || ( strcmp ( p_cLarga, "3.2.1" ) != 0 ) )
		{
			printf( "Error caso 1: se esperaba \"3.2.1\": [%s]\n", ES_VALIDO ( p_cLarga ) ? p_cLarga : "(nulo)" );
			iRes = BOOL_VAL_FALSO;
		}
		MemLiberar ( (void **) &p_cLarga );
		char * p_cCorta = SVerCadenaVersion ( p_verObj, 1 );
		if ( ES_NULO ( p_cCorta ) || ( strcmp ( p_cCorta, "3.2" ) != 0 ) )
		{
			printf( "Error caso 2: se esperaba \"3.2\": [%s]\n", ES_VALIDO ( p_cCorta ) ? p_cCorta : "(nulo)" );
			iRes = BOOL_VAL_FALSO;
		}
		MemLiberar ( (void **) &p_cCorta );
		if ( SVerValorFecha ( p_verObj ) <= 0 )
		{
			printf( "Error caso 3: se esperaba un valor de fecha > 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
		char * p_cFecha = SVerCadenaFecha ( p_verObj );
		if ( ES_NULO ( p_cFecha ) )
		{
			printf( "Error caso 4: se esperaba cadena de fecha no nula\n" );
			iRes = BOOL_VAL_FALSO;
		}
		MemLiberar ( (void **) &p_cFecha );
	}
	SVerDestruir ( &p_verObj );
	return ( iRes );
}

static int TestSVerNulo01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SVerNulo 01:\n" );
	if ( SVerVersion ( NULL ) != -1 )
	{
		printf( "Error caso 1: se esperaba -1 en la version de un objeto nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SVerEsValida ( NULL ) != 0 )
	{
		printf( "Error caso 2: un objeto nulo no debe ser una version valida\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SVerEstablecerVersion ( NULL, 2 ) != 0 )
	{
		printf( "Error caso 3: se esperaba 0 al establecer version en un objeto nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* Fecha no valida: no se puede crear. */
	if ( ES_VALIDO ( SVerCrear ( 0, 0, 0, 20080325 ) ) )
	{
		printf( "Error caso 4: no se esperaba crear una version con numero de version 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}



int TestSVersion ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SVersion]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSVerCicloVida01 () == BOOL_VAL_CIERTO ) &&
			( TestSVerCadena01 () == BOOL_VAL_CIERTO ) &&
			( TestSVerNulo01 () == BOOL_VAL_CIERTO ) )
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
