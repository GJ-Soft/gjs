#include "Base.h"

#include "SistemaRed.h"



static int TestSisRedNombre01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SisRedNombre 01:\n" );
	char * p_cNombre = SisRedNombreOrdenador ();
	if ( ES_NULO ( p_cNombre ) )
	{
		printf( "Error caso 1: se esperaba nombre de ordenador no nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	MemLiberar ( (void **) &p_cNombre );
	return ( iRes );
}

static int TestSisRedNulo01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SisRedNulo 01:\n" );
	if ( SisRedServidorEsAccesible ( NULL ) != 0 )
	{
		printf( "Error caso 1: se esperaba 0 con servidor nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SisRedEstacionEsAccesible ( NULL ) != 0 )
	{
		printf( "Error caso 2: se esperaba 0 con estacion nula\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SisRedEnviarMensaje ( NULL, NULL, NULL ) != 0 )
	{
		printf( "Error caso 3: se esperaba 0 al enviar mensaje con datos nulos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}



int TestSistemaRed ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SistemaRed]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSisRedNombre01 () == BOOL_VAL_CIERTO ) &&
			( TestSisRedNulo01 () == BOOL_VAL_CIERTO ) )
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
