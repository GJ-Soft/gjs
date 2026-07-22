#include "Base.h"


#include "SistemaTiposErrores.h"
#include "SistemaErrores.h"



static int TestSisErrLimpiar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SisErrLimpiar 01:\n" );
	SisErrLimpiar ();
	if ( SisHaHabidoError () != 0 )
	{
		printf( "Error caso 1: tras limpiar no debe haber error\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SisHayError ( 0 ) != 0 )
	{
		printf( "Error caso 2: SisHayError(0) debe ser 0 tras limpiar\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SisErrCodigo () != 0 )
	{
		printf( "Error caso 3: el codigo de error debe ser 0 tras limpiar: %d\n", SisErrCodigo () );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SisErrTipo () != SIS_TIP_ERR_NINGUNO )
	{
		printf( "Error caso 4: el tipo de error debe ser NINGUNO tras limpiar\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_NULO ( SisErrDescripcion () ) )
	{
		printf( "Error caso 5: se esperaba descripcion no nula\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSisErrMensaje01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SisErrMensaje 01:\n" );
	SisErrLimpiar ();
	char * p_cMsj = SisErrMensaje ( 1 );
	if ( ES_NULO ( p_cMsj ) )
	{
		printf( "Error caso 1: se esperaba mensaje no nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	MemLiberar ( (void **) &p_cMsj );
	if ( SisMaxError () <= 0 )
	{
		printf( "Error caso 2: se esperaba SisMaxError > 0: %d\n", SisMaxError () );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}



int TestSistemaErrores ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SistemaErrores]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSisErrLimpiar01 () == BOOL_VAL_CIERTO ) &&
			( TestSisErrMensaje01 () == BOOL_VAL_CIERTO ) )
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
