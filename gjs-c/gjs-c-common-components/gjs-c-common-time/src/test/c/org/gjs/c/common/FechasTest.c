#include "Base.h"

#include "Fechas.h"



static int TestFecConstruir01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	int iA = 0;
	int iM = 0;
	int iD = 0;
	printf( "Test FecConstruir 01:\n" );

	if ( FecFormConstruir ( 2024, 2, 29 ) != 20240229 )
	{
		printf( "Error caso 1: se esperaba 20240229: %ld\n", FecFormConstruir ( 2024, 2, 29 ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( FecFormConstruir ( 2000, 1, 1 ) != 20000101 )
	{
		printf( "Error caso 2: se esperaba 20000101\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* 2023 no es bisiesto: 29 de febrero invalido */
	if ( FecFormConstruir ( 2023, 2, 29 ) != 0 )
	{
		printf( "Error caso 3: fecha invalida deberia dar 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( FecEsValida ( 2024, 2, 29 ) != 1 )
	{
		printf( "Error caso 4: 29/02/2024 deberia ser valida\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( FecEsValida ( 2023, 2, 29 ) != 0 )
	{
		printf( "Error caso 5: 29/02/2023 no deberia ser valida\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( FecEsValida ( 2024, 13, 1 ) != 0 )
	{
		printf( "Error caso 6: mes 13 no deberia ser valido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( FecFormEsValida ( 20240229 ) != 1 )
	{
		printf( "Error caso 7: 20240229 deberia ser valida\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( FecFormEsValida ( 20230229 ) != 0 )
	{
		printf( "Error caso 8: 20230229 no deberia ser valida\n" );
		iRes = BOOL_VAL_FALSO;
	}
	FecFormDescomponer ( 20240229, &iA, &iM, &iD );
	if ( ( iA != 2024 ) || ( iM != 2 ) || ( iD != 29 ) )
	{
		printf( "Error caso 9: descomponer 20240229 -> %d %d %d\n", iA, iM, iD );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ( FecFormAnos ( 20240229 ) != 2024 ) ||
		 ( FecFormMeses ( 20240229 ) != 2 ) ||
		 ( FecFormDias ( 20240229 ) != 29 ) )
	{
		printf( "Error caso 10: anos/meses/dias de 20240229 incorrectos\n" );
		iRes = BOOL_VAL_FALSO;
	}

	return ( iRes );
}



static int TestFecNumDias01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test FecNumDias 01:\n" );

	/* 1 de enero es el dia 1 del ano */
	if ( FecNumDiasAnualesHasta ( 2024, 1, 1 ) != 1 )
	{
		printf( "Error caso 1: se esperaba 1: %d\n", FecNumDiasAnualesHasta ( 2024, 1, 1 ) );
		iRes = BOOL_VAL_FALSO;
	}
	/* 1 de febrero de 2024: enero tiene 31 dias, +1 = 32 */
	if ( FecNumDiasAnualesHasta ( 2024, 2, 1 ) != 32 )
	{
		printf( "Error caso 2: se esperaba 32: %d\n", FecNumDiasAnualesHasta ( 2024, 2, 1 ) );
		iRes = BOOL_VAL_FALSO;
	}
	/* 31 de diciembre de 2024 (bisiesto): quedan 0 dias */
	if ( FecNumDiasAnualesDesde ( 2024, 12, 31 ) != 0 )
	{
		printf( "Error caso 3: se esperaba 0: %d\n", FecNumDiasAnualesDesde ( 2024, 12, 31 ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( FecFormNumDiasAnualesHasta ( 20240201 ) != 32 )
	{
		printf( "Error caso 4: se esperaba 32\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( FecFormNumDiasAnualesDesde ( 20241231 ) != 0 )
	{
		printf( "Error caso 5: se esperaba 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* fecha invalida -> 0 */
	if ( FecNumDiasAnualesHasta ( 2024, 13, 1 ) != 0 )
	{
		printf( "Error caso 6: fecha invalida deberia dar 0\n" );
		iRes = BOOL_VAL_FALSO;
	}

	return ( iRes );
}



static int TestFecDiferencia01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test FecDiferencia 01:\n" );

	if ( FecDiferencia ( 2024, 1, 2, 2024, 1, 1 ) != 1 )
	{
		printf( "Error caso 1: se esperaba 1: %d\n", FecDiferencia ( 2024, 1, 2, 2024, 1, 1 ) );
		iRes = BOOL_VAL_FALSO;
	}
	/* enero tiene 31 dias */
	if ( FecDiferencia ( 2024, 2, 1, 2024, 1, 1 ) != 31 )
	{
		printf( "Error caso 2: se esperaba 31: %d\n", FecDiferencia ( 2024, 2, 1, 2024, 1, 1 ) );
		iRes = BOOL_VAL_FALSO;
	}
	/* signo negativo cuando la primera es menor */
	if ( FecDiferencia ( 2024, 1, 1, 2024, 1, 2 ) != -1 )
	{
		printf( "Error caso 3: se esperaba -1: %d\n", FecDiferencia ( 2024, 1, 1, 2024, 1, 2 ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( FecFormDiferencia ( 20240201, 20240101 ) != 31 )
	{
		printf( "Error caso 4: se esperaba 31\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* fecha invalida -> 0 */
	if ( FecDiferencia ( 2024, 13, 1, 2024, 1, 1 ) != 0 )
	{
		printf( "Error caso 5: fecha invalida deberia dar 0\n" );
		iRes = BOOL_VAL_FALSO;
	}

	return ( iRes );
}



static int TestFecOperaciones01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test FecOperaciones 01:\n" );

	if ( FecFormSumarDias ( 20240101, 1 ) != 20240102 )
	{
		printf( "Error caso 1: se esperaba 20240102: %ld\n", FecFormSumarDias ( 20240101, 1 ) );
		iRes = BOOL_VAL_FALSO;
	}
	/* cambio de mes: 31 de enero + 1 dia = 1 de febrero */
	if ( FecFormSumarDias ( 20240131, 1 ) != 20240201 )
	{
		printf( "Error caso 2: se esperaba 20240201: %ld\n", FecFormSumarDias ( 20240131, 1 ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( FecFormRestarDias ( 20240102, 1 ) != 20240101 )
	{
		printf( "Error caso 3: se esperaba 20240101: %ld\n", FecFormRestarDias ( 20240102, 1 ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( FecFormSumarAnos ( 20240115, 1 ) != 20250115 )
	{
		printf( "Error caso 4: se esperaba 20250115: %ld\n", FecFormSumarAnos ( 20240115, 1 ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( FecFormRestarAnos ( 20240115, 1 ) != 20230115 )
	{
		printf( "Error caso 5: se esperaba 20230115: %ld\n", FecFormRestarAnos ( 20240115, 1 ) );
		iRes = BOOL_VAL_FALSO;
	}

	return ( iRes );
}



static int TestFecComparar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test FecComparar 01:\n" );

	if ( FecEsIgual ( 2024, 1, 1, 2024, 1, 1 ) != 1 )
	{
		printf( "Error caso 1: fechas iguales\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( FecEsMenor ( 2024, 1, 1, 2024, 1, 2 ) != 1 )
	{
		printf( "Error caso 2: 01 < 02\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( FecEsMayor ( 2024, 2, 1, 2024, 1, 1 ) != 1 )
	{
		printf( "Error caso 3: febrero > enero\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( FecEsMenorIgual ( 2024, 1, 1, 2024, 1, 1 ) != 1 )
	{
		printf( "Error caso 4: menor o igual con iguales\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( FecEsMayorIgual ( 2024, 1, 1, 2024, 1, 1 ) != 1 )
	{
		printf( "Error caso 5: mayor o igual con iguales\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( FecFormEsIgual ( 20240101, 20240101 ) != 1 )
	{
		printf( "Error caso 6: form iguales\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( FecFormEsMenor ( 20240101, 20240102 ) != 1 )
	{
		printf( "Error caso 7: form menor\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( FecFormEsMayor ( 20240102, 20240101 ) != 1 )
	{
		printf( "Error caso 8: form mayor\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( FecFormEsMenorIgual ( 20240101, 20240101 ) != 1 )
	{
		printf( "Error caso 9: form menor o igual\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( FecFormEsMayorIgual ( 20240101, 20240101 ) != 1 )
	{
		printf( "Error caso 10: form mayor o igual\n" );
		iRes = BOOL_VAL_FALSO;
	}

	return ( iRes );
}



static int TestFecValor01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	double dValor;
	printf( "Test FecValor 01:\n" );

	if ( FecValEsValido ( 2024.5 ) != 1 )
	{
		printf( "Error caso 1: 2024.5 deberia ser valido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( FecValEsValido ( 0.5 ) != 0 )
	{
		printf( "Error caso 2: 0.5 no deberia ser valido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( FecValEsValido ( -2.0 ) != 1 )
	{
		printf( "Error caso 3: -2.0 deberia ser valido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* el valor numerico del 1 de enero de 2024 esta entre 2024 y 2025 */
	dValor = FecObtenerValor ( 2024, 1, 1 );
	if ( ( dValor < 2024.0 ) || ( dValor >= 2025.0 ) )
	{
		printf( "Error caso 4: valor fuera de rango: %f\n", dValor );
		iRes = BOOL_VAL_FALSO;
	}
	/* fecha invalida -> -1.0 */
	if ( FecObtenerValor ( 2024, 13, 1 ) != -1.0 )
	{
		printf( "Error caso 5: fecha invalida deberia dar -1.0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	dValor = FecFormObtenerValor ( 20240101 );
	if ( ( dValor < 2024.0 ) || ( dValor >= 2025.0 ) )
	{
		printf( "Error caso 6: valor form fuera de rango: %f\n", dValor );
		iRes = BOOL_VAL_FALSO;
	}

	return ( iRes );
}



int TestFechas ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test Fechas]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestFecConstruir01 () == BOOL_VAL_CIERTO ) &&
			( TestFecNumDias01 () == BOOL_VAL_CIERTO ) &&
			( TestFecDiferencia01 () == BOOL_VAL_CIERTO ) &&
			( TestFecOperaciones01 () == BOOL_VAL_CIERTO ) &&
			( TestFecComparar01 () == BOOL_VAL_CIERTO ) &&
			( TestFecValor01 () == BOOL_VAL_CIERTO ) )
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
