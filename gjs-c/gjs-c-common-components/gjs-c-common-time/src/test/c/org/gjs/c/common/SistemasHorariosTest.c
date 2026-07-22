#include "Base.h"

#include "SistemasHorarios.h"



static int TestSisHorNombreId01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SisHorNombreId 01:\n" );

	if ( CadComparar ( (char *) SisHorNombre ( SIS_HOR_UTC ), "UTC" ) != COMP_IGUAL )
	{
		printf( "Error caso 1: nombre de UTC deberia ser \"UTC\"\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( CadComparar ( (char *) SisHorNombre ( SIS_HOR_GMT ), "GMT" ) != COMP_IGUAL )
	{
		printf( "Error caso 2: nombre de GMT deberia ser \"GMT\"\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( CadComparar ( (char *) SisHorNombre ( SIS_HOR_MMT ), "Madrid MT" ) != COMP_IGUAL )
	{
		printf( "Error caso 3: nombre de MMT deberia ser \"Madrid MT\"\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( SisHorNombre ( 99 ) ) )
	{
		printf( "Error caso 4: nombre de id invalido deberia ser nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SisHorId ( "UTC" ) != SIS_HOR_UTC )
	{
		printf( "Error caso 5: id de \"UTC\" incorrecto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* comparacion sin distinguir mayusculas */
	if ( SisHorId ( "gmt" ) != SIS_HOR_GMT )
	{
		printf( "Error caso 6: id de \"gmt\" deberia ser GMT\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SisHorId ( "xxx" ) != SIS_HOR_NINGUNO )
	{
		printf( "Error caso 7: id de \"xxx\" deberia ser ninguno\n" );
		iRes = BOOL_VAL_FALSO;
	}

	return ( iRes );
}



static int TestSisHorEs01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SisHorEs 01:\n" );

	if ( SisHorEsValido ( SIS_HOR_UTC ) != 1 )
	{
		printf( "Error caso 1: UTC deberia ser valido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SisHorEsValido ( 99 ) != 0 )
	{
		printf( "Error caso 2: 99 no deberia ser valido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SisHorEsNulo ( SIS_HOR_NINGUNO ) != 1 )
	{
		printf( "Error caso 3: ninguno deberia ser nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SisHorEsNulo ( SIS_HOR_UTC ) != 0 )
	{
		printf( "Error caso 4: UTC no deberia ser nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SisHorEsUTC ( SIS_HOR_UTC ) != 1 )
	{
		printf( "Error caso 5: EsUTC de UTC deberia dar 1\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SisHorEsGMT ( SIS_HOR_GMT ) != 1 )
	{
		printf( "Error caso 6: EsGMT de GMT deberia dar 1\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SisHorEsMMT ( SIS_HOR_MMT ) != 1 )
	{
		printf( "Error caso 7: EsMMT de MMT deberia dar 1\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SisHorEsUTC ( SIS_HOR_GMT ) != 0 )
	{
		printf( "Error caso 8: EsUTC de GMT deberia dar 0\n" );
		iRes = BOOL_VAL_FALSO;
	}

	return ( iRes );
}



static int TestSisHorInicio01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SisHorInicio 01:\n" );

	if ( SisHorFechaInicio ( SIS_HOR_UTC ) != 19400316 )
	{
		printf( "Error caso 1: se esperaba 19400316: %ld\n", SisHorFechaInicio ( SIS_HOR_UTC ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SisHorFechaInicio ( SIS_HOR_GMT ) != 19010101 )
	{
		printf( "Error caso 2: se esperaba 19010101\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SisHorFechaInicio ( SIS_HOR_MMT ) != -1 )
	{
		printf( "Error caso 3: MMT no tiene fecha de inicio: -1\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SisHorHoraInicio ( SIS_HOR_UTC ) != 230000 )
	{
		printf( "Error caso 4: se esperaba 230000\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SisHorHoraInicio ( SIS_HOR_GMT ) != 0 )
	{
		printf( "Error caso 5: se esperaba 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SisHorFechaInicioUTC () != 19400316 )
	{
		printf( "Error caso 6: FechaInicioUTC incorrecta\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SisHorFechaInicioGMT () != 19010101 )
	{
		printf( "Error caso 7: FechaInicioGMT incorrecta\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SisHorHoraInicioUTC () != 230000 )
	{
		printf( "Error caso 8: HoraInicioUTC incorrecta\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SisHorHoraInicioGMT () != 0 )
	{
		printf( "Error caso 9: HoraInicioGMT incorrecta\n" );
		iRes = BOOL_VAL_FALSO;
	}

	return ( iRes );
}



int TestSistemasHorarios ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SistemasHorarios]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSisHorNombreId01 () == BOOL_VAL_CIERTO ) &&
			( TestSisHorEs01 () == BOOL_VAL_CIERTO ) &&
			( TestSisHorInicio01 () == BOOL_VAL_CIERTO ) )
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
