#include "Base.h"

#include "SistemaProcesos.h"
#include "SistemaTiempo.h"

#include <pthread.h>



static int TestSisProcesoActual01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SisProcesoActual 01:\n" );
	if ( SisPID () <= 0 )
	{
		printf( "Error caso 1: se esperaba PID del proceso actual > 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	char * p_cPID = SisPIDCadena ();
	if ( ES_NULO ( p_cPID ) )
	{
		printf( "Error caso 2: se esperaba la cadena de PID no nula\n" );
		iRes = BOOL_VAL_FALSO;
	}
	MemLiberar ( (void **) &p_cPID );
	if ( SisTID () == 0 )
	{
		printf( "Error caso 3: se esperaba TID del hilo actual distinto de 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	char * p_cTID = SisTIDCadena ();
	if ( ES_NULO ( p_cTID ) )
	{
		printf( "Error caso 4: se esperaba la cadena de TID no nula\n" );
		iRes = BOOL_VAL_FALSO;
	}
	MemLiberar ( (void **) &p_cTID );
	return ( iRes );
}

static int TestSisProcesoExiste01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SisProcesoExiste 01:\n" );
#if ( defined ( WIN ) )
	if ( SisExisteProceso ( SisPID () ) != 1 )
	{
		printf( "Error caso 1: el proceso actual deberia existir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SisProcesoEnEjecucion ( SisPID () ) != 1 )
	{
		printf( "Error caso 2: el proceso actual deberia estar en ejecucion\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SisNumProcesos () <= 0 )
	{
		printf( "Error caso 3: se esperaba numero de procesos > 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
#endif
	return ( iRes );
}



/* ---------------------------------------------------------------------------
   Hilos. El apreton de manos va con condicion, no con esperas al tuntun: un
   test de concurrencia que duerme un rato "por si acaso" falla una vez de cada
   veinte en la maquina de compilacion.
   --------------------------------------------------------------------------- */

static pthread_mutex_t	_mtxPrueba = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t	_cndPrueba = PTHREAD_COND_INITIALIZER;
static int				_iHiloArrancado = 0;
static int				_iHiloPuedeSalir = 0;

# if ( defined ( WIN ) )
static int _FuncionHiloPrueba ( void * p_vParam )
# else
static void * _FuncionHiloPrueba ( void * p_vParam )
# endif
{
	( void ) p_vParam;

	pthread_mutex_lock ( &_mtxPrueba );
	_iHiloArrancado = 1;
	pthread_cond_broadcast ( &_cndPrueba );
	while ( _iHiloPuedeSalir == 0 )
	{
		pthread_cond_wait ( &_cndPrueba, &_mtxPrueba );
	}
	pthread_mutex_unlock ( &_mtxPrueba );

# if ( defined ( WIN ) )
	return ( 0 );
# else
	return ( NULL );
# endif
}

/* Espera a que el hilo se de de baja del registro, con tope: el aviso de que ha
   terminado lo da el propio hilo al volver, y la baja ocurre justo despues, asi
   que hay una ventana corta que no se puede sincronizar desde fuera. */
static int _EsperarBajaHilo ( thread thTID )
{
	int iIntento;

	for ( iIntento = 0; iIntento < 200; iIntento = iIntento + 1 )
	{
		if ( SisExisteHilo ( thTID ) == 0 )
		{
			return ( BOOL_VAL_CIERTO );
		}
		SisEsperar ( 10 );
	}
	return ( BOOL_VAL_FALSO );
}

static int TestSisHilos01 ()
{
	int		iRes = BOOL_VAL_CIERTO;
	int		iAntes;
	thread	thTID;

	printf( "Test SisHilos 01:\n" );
	_iHiloArrancado = 0;
	_iHiloPuedeSalir = 0;

	iAntes = SisNumHilos ();
	thTID = SisCrearHilo ( _FuncionHiloPrueba, NULL, 0 );
	if ( thTID == ( thread ) 0 )
	{
		printf( "Error caso 1: no se pudo crear el hilo\n" );
		return ( BOOL_VAL_FALSO );
	}
	if ( thTID == SisTID () )
	{
		printf( "Error caso 2: el hilo nuevo no puede tener el id del principal\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* Se espera a que arranque de verdad antes de mirar el registro. */
	pthread_mutex_lock ( &_mtxPrueba );
	while ( _iHiloArrancado == 0 )
	{
		pthread_cond_wait ( &_cndPrueba, &_mtxPrueba );
	}
	pthread_mutex_unlock ( &_mtxPrueba );

	if ( SisExisteHilo ( thTID ) == 0 )
	{
		printf( "Error caso 3: el hilo deberia existir mientras corre\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SisNumHilos () != ( iAntes + 1 ) )
	{
		printf( "Error caso 4: se esperaban %d hilos: %d\n", iAntes + 1, SisNumHilos () );
		iRes = BOOL_VAL_FALSO;
	}
	/* Se le deja salir. */
	pthread_mutex_lock ( &_mtxPrueba );
	_iHiloPuedeSalir = 1;
	pthread_cond_broadcast ( &_cndPrueba );
	pthread_mutex_unlock ( &_mtxPrueba );

	if ( _EsperarBajaHilo ( thTID ) == BOOL_VAL_FALSO )
	{
		printf( "Error caso 5: el hilo no se dio de baja del registro\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else if ( SisNumHilos () != iAntes )
	{
		printf( "Error caso 6: el contador no volvio a %d: %d\n", iAntes, SisNumHilos () );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSisHilos02 ()
{
	int		iRes = BOOL_VAL_CIERTO;
	thread	thVacio = ( thread ) 0;

	printf( "Test SisHilos 02:\n" );
	if ( SisCrearHilo ( NULL, NULL, 0 ) != thVacio )
	{
		printf( "Error caso 1: crear con funcion nula deberia dar el id vacio\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SisExisteHilo ( thVacio ) != 0 )
	{
		printf( "Error caso 2: el id vacio no deberia existir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SisExisteHilo ( SisTID () ) != 0 )
	{
		printf( "Error caso 3: el hilo principal no lo creo esta API\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SisCambiarASiguienteHilo () != 1 )
	{
		printf( "Error caso 4: ceder el turno no puede fallar\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SisHiloPrioridad ( thVacio ) != 0 )
	{
		printf( "Error caso 5: la prioridad de un id desconocido deberia ser 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SisHiloTiempoCPU ( thVacio ) != 0 )
	{
		printf( "Error caso 6: el tiempo de CPU de un id desconocido deberia ser 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SisFinalizarHilo ( thVacio ) != 0 )
	{
		printf( "Error caso 7: finalizar un id desconocido deberia dar 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
# if ( !defined ( WIN ) )
	/* Sin soporte por contrato en POSIX: si algun dia se implementan, avisa. */
	if ( SisSuspenderHilo ( thVacio ) != 0 )
	{
		printf( "Error caso 8: suspender no esta soportado en POSIX\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SisReanudarHilo ( thVacio ) != 0 )
	{
		printf( "Error caso 9: reanudar no esta soportado en POSIX\n" );
		iRes = BOOL_VAL_FALSO;
	}
# endif
	return ( iRes );
}

int TestSistemaProcesos ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SistemaProcesos]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSisProcesoActual01 () == BOOL_VAL_CIERTO ) &&
			( TestSisProcesoExiste01 () == BOOL_VAL_CIERTO ) &&
			( TestSisHilos01 () == BOOL_VAL_CIERTO ) &&
			( TestSisHilos02 () == BOOL_VAL_CIERTO ) )
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
