#include "Base.h"

#include "SistemaSincronizacion.h"



static int TestSisVariableSinc01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SisVariableSinc 01:\n" );
#if ( defined ( WIN ) )
	varsinc vsVariable = 0;
	/* Activar sobre una variable libre debe tener exito. */
	if ( SisActivarVariableSinc ( &vsVariable ) != 1 )
	{
		printf( "Error caso 1: se esperaba activar la variable libre\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* Una segunda activacion sin liberar debe fallar (ya esta activa). */
	if ( SisActivarVariableSinc ( &vsVariable ) != 0 )
	{
		printf( "Error caso 2: no se esperaba reactivar una variable ya activa\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SisDesactivarVariableSinc ( &vsVariable ) != 1 )
	{
		printf( "Error caso 3: se esperaba desactivar la variable\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SisEsperarYActivarVariableSinc ( &vsVariable ) != 1 )
	{
		printf( "Error caso 4: se esperaba esperar y activar con exito\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SisDesactivarVariableSinc ( &vsVariable ) != 1 )
	{
		printf( "Error caso 5: se esperaba desactivar tras esperar y activar\n" );
		iRes = BOOL_VAL_FALSO;
	}
#else
	varsinc vsVariable;
	if ( SisInicializarVariableSinc ( &vsVariable ) != 1 )
	{
		printf( "Error caso 1: se esperaba inicializar la variable de sincronizacion\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SisActivarVariableSinc ( &vsVariable ) != 1 )
	{
		printf( "Error caso 2: se esperaba activar la variable libre\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SisDesactivarVariableSinc ( &vsVariable ) != 1 )
	{
		printf( "Error caso 3: se esperaba desactivar la variable\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* Regresion: en POSIX no se asignaba el resultado y se devolvia basura. */
	if ( SisEsperarYActivarVariableSinc ( &vsVariable ) != 1 )
	{
		printf( "Error caso 4: se esperaba esperar y activar con exito\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SisDesactivarVariableSinc ( &vsVariable ) != 1 )
	{
		printf( "Error caso 5: se esperaba desactivar tras esperar y activar\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SisFinalizarVariableSinc ( &vsVariable ) != 1 )
	{
		printf( "Error caso 6: se esperaba finalizar la variable\n" );
		iRes = BOOL_VAL_FALSO;
	}
#endif
	return ( iRes );
}

static int TestSisVariableSincNulo01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SisVariableSincNulo 01:\n" );
	if ( SisActivarVariableSinc ( NULL ) != 0 )
	{
		printf( "Error caso 1: se esperaba 0 al activar variable nula\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SisDesactivarVariableSinc ( NULL ) != 0 )
	{
		printf( "Error caso 2: se esperaba 0 al desactivar variable nula\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}



int TestSistemaSincronizacion ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SistemaSincronizacion]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSisVariableSinc01 () == BOOL_VAL_CIERTO ) &&
			( TestSisVariableSincNulo01 () == BOOL_VAL_CIERTO ) )
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
