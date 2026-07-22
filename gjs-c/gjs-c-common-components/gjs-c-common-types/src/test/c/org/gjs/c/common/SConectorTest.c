#include "Base.h"

#include "SConector.h"



static int TestSCnctCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCnctCrear 01:\n" );
	byte * p_byObjeto = (byte *) MemReservar ( 8 );
	SConector * p_cnctObj = SCnctCrearExt ( p_byObjeto, 7 );
	if ( ES_VALIDO ( p_cnctObj ) )
	{
		if ( SCnctObjeto ( p_cnctObj ) != p_byObjeto )
		{
			printf( "Error caso 1: el objeto no coincide\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCnctTipo ( p_cnctObj ) != 7 )
		{
			printf( "Error caso 2: se esperaba tipo 7: %d\n", SCnctTipo ( p_cnctObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCnctEsValido ( p_cnctObj ) != 1 )
		{
			printf( "Error caso 3: se esperaba valido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SCnctEstablecerTipo ( p_cnctObj, 3 );
		if ( SCnctTipo ( p_cnctObj ) != 3 )
		{
			printf( "Error caso 4: se esperaba tipo 3: %d\n", SCnctTipo ( p_cnctObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		/* SCnctDestruir libera tambien el contenido por defecto. */
		SCnctDestruir ( &p_cnctObj );
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el objeto\n" );
		iRes = BOOL_VAL_FALSO;
		MemLiberar ( (void **) &p_byObjeto );
	}
	return ( iRes );
}

static int TestSCnctCrear02 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCnctCrear 02:\n" );
	byte * p_byObjeto = (byte *) MemReservar ( 8 );
	SConector * p_cnctObj = SCnctCrear ( p_byObjeto );
	if ( ES_VALIDO ( p_cnctObj ) )
	{
		if ( SCnctTipo ( p_cnctObj ) != 0 )
		{
			printf( "Error caso 1: se esperaba tipo por defecto 0: %d\n", SCnctTipo ( p_cnctObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCnctEsValido ( p_cnctObj ) != 1 )
		{
			printf( "Error caso 2: se esperaba valido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SCnctLimpiar ( p_cnctObj );
		if ( ES_VALIDO ( SCnctObjeto ( p_cnctObj ) ) )
		{
			printf( "Error caso 3: se esperaba objeto nulo tras limpiar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCnctEsValido ( p_cnctObj ) != 0 )
		{
			printf( "Error caso 4: se esperaba no valido tras limpiar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* El contenido ya se ha desligado con limpiar: no destruirlo desde el conector. */
		SCnctDestruirExt ( &p_cnctObj, 0 );
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el objeto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	MemLiberar ( (void **) &p_byObjeto );
	return ( iRes );
}

static int TestSCnctNulo01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCnctNulo 01:\n" );
	if ( ES_VALIDO ( SCnctObjeto ( NULL ) ) )
	{
		printf( "Error caso 1: se esperaba objeto nulo con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SCnctTipo ( NULL ) != 0 )
	{
		printf( "Error caso 2: se esperaba tipo 0 con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SCnctEsValido ( NULL ) != 0 )
	{
		printf( "Error caso 3: se esperaba no valido con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SCnctEstablecerTipo ( NULL, 1 ) != 0 )
	{
		printf( "Error caso 4: se esperaba fallo con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

int TestSConector ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SConector]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSCnctCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSCnctCrear02 () == BOOL_VAL_CIERTO ) &&
			( TestSCnctNulo01 () == BOOL_VAL_CIERTO ) )
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
