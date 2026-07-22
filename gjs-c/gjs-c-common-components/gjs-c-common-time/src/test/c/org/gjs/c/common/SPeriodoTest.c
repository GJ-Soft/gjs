#include "Base.h"

#include "SPeriodo.h"



static int TestSPerdCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	SPeriodo * p_perdObj;
	printf( "Test SPerdCrear 01:\n" );

	p_perdObj = SPerdCrear ( TIP_PERIOD_MENSUAL, 20240115 );
	if ( ES_NULO ( p_perdObj ) )
	{
		printf( "Error caso 0: no se pudo crear el periodo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SPerdEsValido ( p_perdObj ) != 1 )
		{
			printf( "Error caso 1: el periodo deberia ser valido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SPerdPeriodicidad ( p_perdObj ) != TIP_PERIOD_MENSUAL )
		{
			printf( "Error caso 2: la periodicidad deberia ser mensual\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SPerdEsMensual ( p_perdObj ) != 1 )
		{
			printf( "Error caso 3: deberia ser mensual\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SPerdEsAnual ( p_perdObj ) != 0 )
		{
			printf( "Error caso 4: no deberia ser anual\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SPerdFechaOcurrencia ( p_perdObj ) != 20240115 )
		{
			printf( "Error caso 5: la fecha de ocurrencia deberia ser 20240115: %ld\n", SPerdFechaOcurrencia ( p_perdObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		/* la proxima ocurrencia mensual es un mes despues */
		if ( SPerdFechaProximaOcurrencia ( p_perdObj ) != 20240215 )
		{
			printf( "Error caso 6: la proxima ocurrencia deberia ser 20240215: %ld\n", SPerdFechaProximaOcurrencia ( p_perdObj ) );
			iRes = BOOL_VAL_FALSO;
		}
	}
	SPerdDestruir ( (SPeriodo **) &p_perdObj );
	if ( ES_VALIDO ( p_perdObj ) )
	{
		printf( "Error caso 7: tras destruir el puntero deberia ser nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}

	/* periodicidad invalida -> objeto nulo */
	p_perdObj = SPerdCrear ( 99, 20240115 );
	if ( ES_VALIDO ( p_perdObj ) )
	{
		printf( "Error caso 8: periodicidad invalida deberia dar nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SPerdDestruir ( (SPeriodo **) &p_perdObj );

	/* fecha invalida -> objeto nulo */
	p_perdObj = SPerdCrear ( TIP_PERIOD_MENSUAL, 20241301 );
	if ( ES_VALIDO ( p_perdObj ) )
	{
		printf( "Error caso 9: fecha invalida deberia dar nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SPerdDestruir ( (SPeriodo **) &p_perdObj );

	/* comportamiento defensivo con nulo */
	if ( SPerdEsValido ( NULL ) != 0 )
	{
		printf( "Error caso 10: SPerdEsValido de nulo deberia dar 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SPerdPeriodicidad ( NULL ) != TIP_PERIOD_NINGUNO )
	{
		printf( "Error caso 11: SPerdPeriodicidad de nulo deberia dar ninguno\n" );
		iRes = BOOL_VAL_FALSO;
	}

	return ( iRes );
}



static int TestSPerdProxima01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	SPeriodo * p_perdObj;
	printf( "Test SPerdProxima 01:\n" );

	p_perdObj = SPerdCrear ( TIP_PERIOD_ANUAL, 20240115 );
	if ( ES_VALIDO ( p_perdObj ) )
	{
		if ( SPerdFechaProximaOcurrencia ( p_perdObj ) != 20250115 )
		{
			printf( "Error caso 1: proxima anual deberia ser 20250115: %ld\n", SPerdFechaProximaOcurrencia ( p_perdObj ) );
			iRes = BOOL_VAL_FALSO;
		}
	}
	SPerdDestruir ( (SPeriodo **) &p_perdObj );

	p_perdObj = SPerdCrear ( TIP_PERIOD_TRIMESTRAL, 20240115 );
	if ( ES_VALIDO ( p_perdObj ) )
	{
		if ( SPerdFechaProximaOcurrencia ( p_perdObj ) != 20240415 )
		{
			printf( "Error caso 2: proxima trimestral deberia ser 20240415: %ld\n", SPerdFechaProximaOcurrencia ( p_perdObj ) );
			iRes = BOOL_VAL_FALSO;
		}
	}
	SPerdDestruir ( (SPeriodo **) &p_perdObj );

	p_perdObj = SPerdCrear ( TIP_PERIOD_SEMANAL, 20240115 );
	if ( ES_VALIDO ( p_perdObj ) )
	{
		if ( SPerdFechaProximaOcurrencia ( p_perdObj ) != 20240122 )
		{
			printf( "Error caso 3: proxima semanal deberia ser 20240122: %ld\n", SPerdFechaProximaOcurrencia ( p_perdObj ) );
			iRes = BOOL_VAL_FALSO;
		}
	}
	SPerdDestruir ( (SPeriodo **) &p_perdObj );

	p_perdObj = SPerdCrear ( TIP_PERIOD_DIARIO, 20240115 );
	if ( ES_VALIDO ( p_perdObj ) )
	{
		if ( SPerdFechaProximaOcurrencia ( p_perdObj ) != 20240116 )
		{
			printf( "Error caso 4: proxima diaria deberia ser 20240116: %ld\n", SPerdFechaProximaOcurrencia ( p_perdObj ) );
			iRes = BOOL_VAL_FALSO;
		}
	}
	SPerdDestruir ( (SPeriodo **) &p_perdObj );

	return ( iRes );
}



static int TestSPerdOcurrencias01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	SPeriodo * p_perdObj;
	printf( "Test SPerdOcurrencias 01:\n" );

	p_perdObj = SPerdCrear ( TIP_PERIOD_MENSUAL, 20240115 );
	if ( ES_NULO ( p_perdObj ) )
	{
		printf( "Error caso 0: no se pudo crear el periodo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		/* un mes y un dia despues ya ha ocurrido */
		if ( SPerdOcurreHastaFecha ( p_perdObj, 20240216 ) != 1 )
		{
			printf( "Error caso 1: hasta 20240216 deberia haber ocurrido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* antes de un mes no ha ocurrido */
		if ( SPerdOcurreHastaFecha ( p_perdObj, 20240210 ) != 0 )
		{
			printf( "Error caso 2: hasta 20240210 no deberia haber ocurrido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* la misma fecha de ocurrencia inicial no cuenta */
		if ( SPerdOcurreHastaFecha ( p_perdObj, 20240115 ) != 0 )
		{
			printf( "Error caso 3: hasta 20240115 no deberia haber ocurrido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* entre 20240215 y 20240416 ocurre 3 veces (feb, mar, abr) */
		if ( SPerdVecesQueOcurreHastaFecha ( p_perdObj, 20240416 ) != 3 )
		{
			printf( "Error caso 4: deberia ocurrir 3 veces: %d\n", SPerdVecesQueOcurreHastaFecha ( p_perdObj, 20240416 ) );
			iRes = BOOL_VAL_FALSO;
		}
		/* actualizar avanza la fecha de ocurrencia a la ultima anterior a la fecha dada */
		if ( SPerdActualizarHastaFecha ( p_perdObj, 20240416 ) != 3 )
		{
			printf( "Error caso 5: actualizar deberia avanzar 3 veces\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SPerdFechaOcurrencia ( p_perdObj ) != 20240515 )
		{
			printf( "Error caso 6: tras actualizar la ocurrencia deberia ser 20240515: %ld\n", SPerdFechaOcurrencia ( p_perdObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		/* iniciar reestablece la fecha de ocurrencia */
		SPerdIniciar ( p_perdObj, 20240301 );
		if ( SPerdFechaOcurrencia ( p_perdObj ) != 20240301 )
		{
			printf( "Error caso 7: tras iniciar la ocurrencia deberia ser 20240301: %ld\n", SPerdFechaOcurrencia ( p_perdObj ) );
			iRes = BOOL_VAL_FALSO;
		}
	}
	SPerdDestruir ( (SPeriodo **) &p_perdObj );

	return ( iRes );
}



int TestSPeriodo ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SPeriodo]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSPerdCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSPerdProxima01 () == BOOL_VAL_CIERTO ) &&
			( TestSPerdOcurrencias01 () == BOOL_VAL_CIERTO ) )
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
