#include "Base.h"

#include "ZonasHorarias.h"



static int TestZnhValida01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test ZnhValida 01:\n" );

	if ( ZnhEsValida ( ZNH_UTC ) != 1 )
	{
		printf( "Error caso 1: UTC deberia ser valida\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ZnhEsValida ( ZNH_UTC_M1 ) != 1 )
	{
		printf( "Error caso 2: UTC-1 deberia ser valida\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* zonas especiales con desfase no exacto */
	if ( ZnhEsValida ( ZNH_NST ) != 1 )
	{
		printf( "Error caso 3: NST deberia ser valida\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ZnhEsValida ( ZNH_ACST ) != 1 )
	{
		printf( "Error caso 4: ACST deberia ser valida\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ZnhEsValida ( 25 ) != 0 )
	{
		printf( "Error caso 5: 25 no deberia ser valida\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ZnhEsValida ( ZNH_NINGUNA ) != 0 )
	{
		printf( "Error caso 6: ninguna no deberia ser valida\n" );
		iRes = BOOL_VAL_FALSO;
	}

	return ( iRes );
}



static int TestZnhId01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test ZnhId 01:\n" );

	if ( ZnhId ( 30, 0, 0 ) != 2 )
	{
		printf( "Error caso 1: se esperaba 2: %d\n", ZnhId ( 30, 0, 0 ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ZnhId ( 200, 0, 0 ) != -1 )
	{
		printf( "Error caso 2: fuera de rango deberia dar -1\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ZnhIdAng ( 30.0 ) != 2 )
	{
		printf( "Error caso 3: se esperaba 2\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* el huso de una zona es su valor modulo 100 */
	if ( ZnhHuso ( ZNH_NST ) != 22 )
	{
		printf( "Error caso 4: huso de NST deberia ser 22: %d\n", ZnhHuso ( ZNH_NST ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ZnhHuso ( ZNH_UTC_2 ) != 2 )
	{
		printf( "Error caso 5: huso de UTC+2 deberia ser 2\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ZnhHuso ( 25 ) != -1 )
	{
		printf( "Error caso 6: zona invalida deberia dar -1\n" );
		iRes = BOOL_VAL_FALSO;
	}

	return ( iRes );
}



static int TestZnhUTC01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test ZnhUTC 01:\n" );

	if ( ZnhEsUTCMas ( ZNH_UTC ) != 1 )
	{
		printf( "Error caso 1: UTC deberia ser UTC+\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ZnhEsUTCMas ( ZNH_UTC_12 ) != 1 )
	{
		printf( "Error caso 2: UTC+12 deberia ser UTC+\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ZnhEsUTCMenos ( ZNH_UTC_M12 ) != 1 )
	{
		printf( "Error caso 3: UTC-12 deberia ser UTC-\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ZnhEsUTCMas ( ZNH_UTC_M12 ) != 0 )
	{
		printf( "Error caso 4: UTC-12 no deberia ser UTC+\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ZnhDiferenciaHorasUTCExacta ( ZNH_UTC_2 ) != 1 )
	{
		printf( "Error caso 5: UTC+2 deberia tener desfase exacto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ZnhDiferenciaHorasUTCExacta ( ZNH_NST ) != 0 )
	{
		printf( "Error caso 6: NST no deberia tener desfase exacto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ZnhDiferenciaHorasUTC ( ZNH_UTC ) != 0 )
	{
		printf( "Error caso 7: desfase de UTC deberia ser 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ZnhDiferenciaHorasUTC ( ZNH_UTC_3 ) != 3 )
	{
		printf( "Error caso 8: desfase de UTC+3 deberia ser 3: %d\n", ZnhDiferenciaHorasUTC ( ZNH_UTC_3 ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ZnhDiferenciaHorasUTC ( ZNH_UTC_M12 ) != -12 )
	{
		printf( "Error caso 9: desfase de UTC-12 deberia ser -12\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ZnhDiferenciaMinutosUTC ( ZNH_UTC_3 ) != 180 )
	{
		printf( "Error caso 10: desfase en minutos de UTC+3 deberia ser 180: %d\n", ZnhDiferenciaMinutosUTC ( ZNH_UTC_3 ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ZnhDiferenciaHoras ( ZNH_UTC_1, ZNH_UTC_2 ) != 1 )
	{
		printf( "Error caso 11: diferencia entre UTC+1 y UTC+2 deberia ser 1\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ZnhDiferenciaMinutos ( ZNH_UTC_1, ZNH_UTC_2 ) != 60 )
	{
		printf( "Error caso 12: diferencia en minutos deberia ser 60\n" );
		iRes = BOOL_VAL_FALSO;
	}

	return ( iRes );
}



int TestZonasHorarias ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test ZonasHorarias]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestZnhValida01 () == BOOL_VAL_CIERTO ) &&
			( TestZnhId01 () == BOOL_VAL_CIERTO ) &&
			( TestZnhUTC01 () == BOOL_VAL_CIERTO ) )
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
