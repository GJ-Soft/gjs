#include "Base.h"

#include "Horas.h"



static int TestHorConstruir01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	int iH = 0;
	int iM = 0;
	int iS = 0;
	printf( "Test HorConstruir 01:\n" );

	if ( HorFormConstruir ( 1, 2, 3 ) != 10203 )
	{
		printf( "Error caso 1: se esperaba 10203: %ld\n", HorFormConstruir ( 1, 2, 3 ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( HorFormConstruir ( 23, 59, 59 ) != 235959 )
	{
		printf( "Error caso 2: se esperaba 235959\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* hora invalida -> -1 */
	if ( HorFormConstruir ( 24, 0, 0 ) != -1 )
	{
		printf( "Error caso 3: 24:00:00 deberia dar -1\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( HorEsValida ( 23, 59, 59 ) != 1 )
	{
		printf( "Error caso 4: 23:59:59 deberia ser valida\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( HorEsValida ( 24, 0, 0 ) != 0 )
	{
		printf( "Error caso 5: 24:00:00 no deberia ser valida\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( HorFormEsValida ( 235959 ) != 1 )
	{
		printf( "Error caso 6: 235959 deberia ser valida\n" );
		iRes = BOOL_VAL_FALSO;
	}
	HorFormDescomponer ( 102030, &iH, &iM, &iS );
	if ( ( iH != 10 ) || ( iM != 20 ) || ( iS != 30 ) )
	{
		printf( "Error caso 7: descomponer 102030 -> %d %d %d\n", iH, iM, iS );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ( HorFormHoras ( 235959 ) != 23 ) ||
		 ( HorFormMinutos ( 235959 ) != 59 ) ||
		 ( HorFormSegundos ( 235959 ) != 59 ) )
	{
		printf( "Error caso 8: horas/minutos/segundos de 235959 incorrectos\n" );
		iRes = BOOL_VAL_FALSO;
	}

	return ( iRes );
}



static int TestHorNum01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test HorNum 01:\n" );

	if ( HorNumMinutos ( 1, 30, 0 ) != 90 )
	{
		printf( "Error caso 1: se esperaba 90: %d\n", HorNumMinutos ( 1, 30, 0 ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( HorNumSegundos ( 1, 0, 0 ) != 3600 )
	{
		printf( "Error caso 2: se esperaba 3600: %d\n", HorNumSegundos ( 1, 0, 0 ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( HorFormNumMinutos ( 13000 ) != 90 )
	{
		printf( "Error caso 3: se esperaba 90\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( HorFormNumSegundos ( 10000 ) != 3600 )
	{
		printf( "Error caso 4: se esperaba 3600\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* hora invalida -> 0 */
	if ( HorNumMinutos ( 24, 0, 0 ) != 0 )
	{
		printf( "Error caso 5: hora invalida deberia dar 0\n" );
		iRes = BOOL_VAL_FALSO;
	}

	return ( iRes );
}



static int TestHorSumarRestar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test HorSumarRestar 01:\n" );

	if ( HorFormSumar ( 100000, 20000 ) != 120000 )
	{
		printf( "Error caso 1: se esperaba 120000: %ld\n", HorFormSumar ( 100000, 20000 ) );
		iRes = BOOL_VAL_FALSO;
	}
	/* acarreo de dia: la suma no cabe en 24h -> -1 */
	if ( HorFormSumar ( 230000, 20000 ) != -1 )
	{
		printf( "Error caso 2: acarreo deberia dar -1: %ld\n", HorFormSumar ( 230000, 20000 ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( HorFormRestar ( 120000, 20000 ) != 100000 )
	{
		printf( "Error caso 3: se esperaba 100000: %ld\n", HorFormRestar ( 120000, 20000 ) );
		iRes = BOOL_VAL_FALSO;
	}

	return ( iRes );
}



static int TestHorValor01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	double dValor;
	int iH = 0;
	int iM = 0;
	int iS = 0;
	printf( "Test HorValor 01:\n" );

	if ( HorValEsValido ( 12.5 ) != 1 )
	{
		printf( "Error caso 1: 12.5 deberia ser valido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( HorValEsValido ( 24.0 ) != 0 )
	{
		printf( "Error caso 2: 24.0 no deberia ser valido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( HorValEsValido ( -1.0 ) != 0 )
	{
		printf( "Error caso 3: -1.0 no deberia ser valido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	dValor = HorObtenerValor ( 12, 0, 0 );
	if ( ( dValor < 11.9999 ) || ( dValor > 12.0001 ) )
	{
		printf( "Error caso 4: se esperaba 12.0: %f\n", dValor );
		iRes = BOOL_VAL_FALSO;
	}
	dValor = HorObtenerValor ( 1, 30, 0 );
	if ( ( dValor < 1.4999 ) || ( dValor > 1.5001 ) )
	{
		printf( "Error caso 5: se esperaba 1.5: %f\n", dValor );
		iRes = BOOL_VAL_FALSO;
	}
	dValor = HorFormObtenerValor ( 13000 );
	if ( ( dValor < 1.4999 ) || ( dValor > 1.5001 ) )
	{
		printf( "Error caso 6: se esperaba 1.5 (form): %f\n", dValor );
		iRes = BOOL_VAL_FALSO;
	}
	/* hora invalida -> -1.0 */
	if ( HorObtenerValor ( 24, 0, 0 ) != -1.0 )
	{
		printf( "Error caso 7: hora invalida deberia dar -1.0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* HorEstablecerValor devuelve 1 para valor valido; se comprueban horas y minutos */
	if ( HorEstablecerValor ( 1.5, &iH, &iM, &iS ) != 1 )
	{
		printf( "Error caso 8: HorEstablecerValor deberia devolver 1\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ( iH != 1 ) || ( iM != 30 ) )
	{
		printf( "Error caso 9: se esperaba 1h 30m: %dh %dm\n", iH, iM );
		iRes = BOOL_VAL_FALSO;
	}

	return ( iRes );
}



int TestHoras ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test Horas]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestHorConstruir01 () == BOOL_VAL_CIERTO ) &&
			( TestHorNum01 () == BOOL_VAL_CIERTO ) &&
			( TestHorSumarRestar01 () == BOOL_VAL_CIERTO ) &&
			( TestHorValor01 () == BOOL_VAL_CIERTO ) )
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
