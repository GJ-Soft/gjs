#include "Base.h"

#include "UTC.h"



static int TestUTCHoraLocal01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test UTCHoraLocal 01:\n" );

	/* 12:00:00 UTC en la zona UTC+2 son las 14:00:00 locales */
	if ( UTCObtenerHoraLocal ( 120000, ZNH_UTC_2 ) != 140000 )
	{
		printf( "Error caso 1: se esperaba 140000: %ld\n", UTCObtenerHoraLocal ( 120000, ZNH_UTC_2 ) );
		iRes = BOOL_VAL_FALSO;
	}
	/* con acarreo de dia: 23:00:00 + 2h = 01:00:00 */
	if ( UTCObtenerHoraLocal ( 230000, ZNH_UTC_2 ) != 10000 )
	{
		printf( "Error caso 2: se esperaba 10000: %ld\n", UTCObtenerHoraLocal ( 230000, ZNH_UTC_2 ) );
		iRes = BOOL_VAL_FALSO;
	}
	/* zona invalida -> -1 */
	if ( UTCObtenerHoraLocal ( 120000, 25 ) != -1 )
	{
		printf( "Error caso 3: zona invalida deberia dar -1\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* hora invalida -> -1 */
	if ( UTCObtenerHoraLocal ( 250000, ZNH_UTC_2 ) != -1 )
	{
		printf( "Error caso 4: hora invalida deberia dar -1\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* operacion inversa: 14:00:00 locales en UTC+2 son las 12:00:00 UTC */
	if ( UTCEstablecerHoraLocal ( 140000, ZNH_UTC_2 ) != 120000 )
	{
		printf( "Error caso 5: se esperaba 120000: %ld\n", UTCEstablecerHoraLocal ( 140000, ZNH_UTC_2 ) );
		iRes = BOOL_VAL_FALSO;
	}

	return ( iRes );
}



int TestUTC ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test UTC]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestUTCHoraLocal01 () == BOOL_VAL_CIERTO ) )
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
