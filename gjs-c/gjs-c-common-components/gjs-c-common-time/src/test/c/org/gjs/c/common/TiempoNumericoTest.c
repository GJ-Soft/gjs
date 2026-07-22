#include "Base.h"

#include "TiempoNumerico.h"



static int TestTiempoNumSegundos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test TiempoNumSegundos 01:\n" );

	/* 1 dia + 1 hora + 1 min + 1 seg = 86400 + 3600 + 60 + 1 = 90061 */
	if ( TiempoNumSegundos ( 1, 1, 1, 1 ) != 90061 )
	{
		printf( "Error caso 1: se esperaba 90061: %lu\n", TiempoNumSegundos ( 1, 1, 1, 1 ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( TiempoNumSegundos ( 0, 0, 0, 0 ) != 0 )
	{
		printf( "Error caso 2: se esperaba 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( TiempoNumSegundos ( 1, 0, 0, 0 ) != 86400 )
	{
		printf( "Error caso 3: se esperaba 86400\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( TiempoNumSegundos ( 0, 1, 0, 0 ) != 3600 )
	{
		printf( "Error caso 4: se esperaba 3600\n" );
		iRes = BOOL_VAL_FALSO;
	}

	return ( iRes );
}



static int TestTmpFormConstruir01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	double dTmp;
	long lFecha = 0;
	long lHora = 0;
	printf( "Test TmpFormConstruir 01:\n" );

	/* fecha 20240101 y hora 120000 -> 20240101 * 1000000 + 120000 */
	dTmp = TmpFormConstruir ( 20240101, 120000 );
	if ( ( dTmp < 20240101119999.0 ) || ( dTmp > 20240101120001.0 ) )
	{
		printf( "Error caso 1: valor construido incorrecto: %f\n", dTmp );
		iRes = BOOL_VAL_FALSO;
	}
	/* fecha invalida -> 0 */
	if ( TmpFormConstruir ( 20241301, 120000 ) != 0 )
	{
		printf( "Error caso 2: fecha invalida deberia dar 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* hora invalida -> 0 */
	if ( TmpFormConstruir ( 20240101, 250000 ) != 0 )
	{
		printf( "Error caso 3: hora invalida deberia dar 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	dTmp = TmpFormConstruirExt ( 2024, 1, 1, 12, 0, 0 );
	if ( ( dTmp < 20240101119999.0 ) || ( dTmp > 20240101120001.0 ) )
	{
		printf( "Error caso 4: valor construido ext incorrecto: %f\n", dTmp );
		iRes = BOOL_VAL_FALSO;
	}
	TmpFormDescomponer ( dTmp, &lFecha, &lHora );
	if ( ( lFecha != 20240101 ) || ( lHora != 120000 ) )
	{
		printf( "Error caso 5: descomponer -> %ld %ld\n", lFecha, lHora );
		iRes = BOOL_VAL_FALSO;
	}

	return ( iRes );
}



static int TestTmpFormComponentes01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	double dTmp;
	printf( "Test TmpFormComponentes 01:\n" );

	dTmp = TmpFormConstruir ( 20240102, 133045 );
	if ( TmpFormFecha ( dTmp ) != 20240102 )
	{
		printf( "Error caso 1: fecha deberia ser 20240102: %ld\n", TmpFormFecha ( dTmp ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( TmpFormHora ( dTmp ) != 133045 )
	{
		printf( "Error caso 2: hora deberia ser 133045: %ld\n", TmpFormHora ( dTmp ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( TmpFormAnos ( dTmp ) != 2024 )
	{
		printf( "Error caso 3: anos deberia ser 2024\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( TmpFormMeses ( dTmp ) != 1 )
	{
		printf( "Error caso 4: meses deberia ser 1\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( TmpFormDias ( dTmp ) != 2 )
	{
		printf( "Error caso 5: dias deberia ser 2\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( TmpFormHoras ( dTmp ) != 13 )
	{
		printf( "Error caso 6: horas deberia ser 13\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( TmpFormMinutos ( dTmp ) != 30 )
	{
		printf( "Error caso 7: minutos deberia ser 30\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( TmpFormSegundos ( dTmp ) != 45 )
	{
		printf( "Error caso 8: segundos deberia ser 45\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( TmpFormEsValido ( dTmp ) != 1 )
	{
		printf( "Error caso 9: el tiempo deberia ser valido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( TmpFormEsValido ( 0 ) != 0 )
	{
		printf( "Error caso 10: 0 no deberia ser valido\n" );
		iRes = BOOL_VAL_FALSO;
	}

	return ( iRes );
}



int TestTiempoNumerico ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test TiempoNumerico]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestTiempoNumSegundos01 () == BOOL_VAL_CIERTO ) &&
			( TestTmpFormConstruir01 () == BOOL_VAL_CIERTO ) &&
			( TestTmpFormComponentes01 () == BOOL_VAL_CIERTO ) )
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
