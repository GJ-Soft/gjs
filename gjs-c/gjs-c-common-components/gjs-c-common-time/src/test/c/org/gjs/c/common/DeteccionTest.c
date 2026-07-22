#include "Base.h"

#include "Fechas.h"
#include "Horas.h"
#include "Calendario.h"



/*
 * Tests especificos para las zonas de codigo detectadas como problematicas.
 * A diferencia del resto de la bateria (tests de caracterizacion), estos
 * aseveran el comportamiento CORRECTO esperado: estan pensados para FALLAR
 * mientras la funcion tenga el defecto y PASAR una vez corregida.
 */



/* FecSumarMeses / FecFormSumarMeses: sumar N meses conservando el dia.
 * Defecto observado: el mes se calcula como ( ( *p_iM + iM ) % 12 ) + 1,
 * lo que introduce un desfase (sumar 0 meses ya cambia el mes). */
static int TestDetFecSumarMeses01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	int iA;
	int iM;
	int iD;
	printf( "Test DetFecSumarMeses 01:\n" );

	/* enero + 1 mes = febrero, mismo dia */
	if ( FecFormSumarMeses ( 20240115, 1 ) != 20240215 )
	{
		printf( "Error caso 1: se esperaba 20240215: %ld\n", FecFormSumarMeses ( 20240115, 1 ) );
		iRes = BOOL_VAL_FALSO;
	}
	/* sumar 0 meses debe dejar la fecha igual */
	if ( FecFormSumarMeses ( 20240115, 0 ) != 20240115 )
	{
		printf( "Error caso 2: se esperaba 20240115: %ld\n", FecFormSumarMeses ( 20240115, 0 ) );
		iRes = BOOL_VAL_FALSO;
	}
	/* sumar 12 meses = un ano exacto */
	if ( FecFormSumarMeses ( 20240115, 12 ) != 20250115 )
	{
		printf( "Error caso 3: se esperaba 20250115: %ld\n", FecFormSumarMeses ( 20240115, 12 ) );
		iRes = BOOL_VAL_FALSO;
	}
	/* con salto de ano: noviembre + 2 meses = enero del ano siguiente */
	if ( FecFormSumarMeses ( 20241115, 2 ) != 20250115 )
	{
		printf( "Error caso 4: se esperaba 20250115: %ld\n", FecFormSumarMeses ( 20241115, 2 ) );
		iRes = BOOL_VAL_FALSO;
	}
	/* FecRestarMeses es la operacion inversa */
	if ( FecFormRestarMeses ( 20240315, 1 ) != 20240215 )
	{
		printf( "Error caso 5: se esperaba 20240215: %ld\n", FecFormRestarMeses ( 20240315, 1 ) );
		iRes = BOOL_VAL_FALSO;
	}
	/* justo sumando 12 meses */
	if ( FecFormSumarMeses ( 20241115, 1 ) != 20241215 )
	{
		printf( "Error caso 5: se esperaba 20241215: %ld\n", FecFormSumarMeses ( 20241115, 1 ) );
		iRes = BOOL_VAL_FALSO;
	}
	/* version con punteros */
	iA = 2024;
	iM = 1;
	iD = 15;
	if ( FecSumarMeses ( &iA, &iM, &iD, 1 ) != 1 )
	{
		printf( "Error caso 7: FecSumarMeses deberia devolver 1\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ( iA != 2024 ) || ( iM != 2 ) || ( iD != 15 ) )
	{
		printf( "Error caso 8: se esperaba 2024/2/15: %d/%d/%d\n", iA, iM, iD );
		iRes = BOOL_VAL_FALSO;
	}

	return ( iRes );
}



/* FecSumarAnos (version con punteros): en el camino de exito no se asigna
 * iRes = 1, por lo que devuelve un valor sin inicializar. */
static int TestDetFecSumarAnos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	int iA;
	int iM;
	int iD;
	printf( "Test DetFecSumarAnos 01:\n" );

	iA = 2024;
	iM = 6;
	iD = 15;
	if ( FecSumarAnos ( &iA, &iM, &iD, 2 ) != 1 )
	{
		printf( "Error caso 1: FecSumarAnos deberia devolver 1\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ( iA != 2026 ) || ( iM != 6 ) || ( iD != 15 ) )
	{
		printf( "Error caso 2: se esperaba 2026/6/15: %d/%d/%d\n", iA, iM, iD );
		iRes = BOOL_VAL_FALSO;
	}
	/* sobre fecha invalida debe devolver 0 */
	iA = 2024;
	iM = 13;
	iD = 15;
	if ( FecSumarAnos ( &iA, &iM, &iD, 2 ) != 0 )
	{
		printf( "Error caso 3: sobre fecha invalida deberia devolver 0\n" );
		iRes = BOOL_VAL_FALSO;
	}

	return ( iRes );
}



/* HorEstablecerValor / HorFormEstablecerValor: convertir un valor en horas
 * (decimal) a H/M/S. Defecto observado: el calculo de los segundos usa *p_iM
 * en vez de *p_iH, produciendo segundos fuera de rango. */
static int TestDetHorEstablecerValor01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	int iH;
	int iM;
	int iS;
	printf( "Test DetHorEstablecerValor 01:\n" );

	/* 12.0 horas = 12:00:00 */
	if ( HorFormEstablecerValor ( 12.0 ) != 120000 )
	{
		printf( "Error caso 1: se esperaba 120000: %ld\n", HorFormEstablecerValor ( 12.0 ) );
		iRes = BOOL_VAL_FALSO;
	}
	/* 1.5 horas = 01:30:00 */
	if ( HorFormEstablecerValor ( 1.5 ) != 13000 )
	{
		printf( "Error caso 2: se esperaba 13000: %ld\n", HorFormEstablecerValor ( 1.5 ) );
		iRes = BOOL_VAL_FALSO;
	}
	/* 6.25 horas = 06:15:00 */
	if ( HorFormEstablecerValor ( 6.25 ) != 61500 )
	{
		printf( "Error caso 3: se esperaba 61500: %ld\n", HorFormEstablecerValor ( 6.25 ) );
		iRes = BOOL_VAL_FALSO;
	}
	/* version con punteros: 1.5 -> 1h 30m 0s */
	iH = 0;
	iM = 0;
	iS = 0;
	if ( HorEstablecerValor ( 1.5, &iH, &iM, &iS ) != 1 )
	{
		printf( "Error caso 4: HorEstablecerValor deberia devolver 1\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ( iH != 1 ) || ( iM != 30 ) || ( iS != 0 ) )
	{
		printf( "Error caso 5: se esperaba 1h 30m 0s: %dh %dm %ds\n", iH, iM, iS );
		iRes = BOOL_VAL_FALSO;
	}

	return ( iRes );
}



/* CalendDiasTranscurridos: numero de dias transcurridos entre dos fechas.
 * Defecto observado: contabiliza de mas el primer ano (doble conteo). */
static int TestDetCalendDiasTranscurridos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test DetCalendDiasTranscurridos 01:\n" );

	/* dias consecutivos: 1 dia */
	if ( CalendDiasTranscurridos ( 2024, 1, 1, 2024, 1, 2 ) != 1 )
	{
		printf( "Error caso 1: se esperaba 1: %ld\n", CalendDiasTranscurridos ( 2024, 1, 1, 2024, 1, 2 ) );
		iRes = BOOL_VAL_FALSO;
	}
	/* del 1 de enero al 1 de febrero: 31 dias */
	if ( CalendDiasTranscurridos ( 2024, 1, 1, 2024, 2, 1 ) != 31 )
	{
		printf( "Error caso 2: se esperaba 31: %ld\n", CalendDiasTranscurridos ( 2024, 1, 1, 2024, 2, 1 ) );
		iRes = BOOL_VAL_FALSO;
	}
	/* un ano bisiesto completo: 366 dias */
	if ( CalendDiasTranscurridos ( 2024, 1, 1, 2025, 1, 1 ) != 366 )
	{
		printf( "Error caso 3: se esperaba 366: %ld\n", CalendDiasTranscurridos ( 2024, 1, 1, 2025, 1, 1 ) );
		iRes = BOOL_VAL_FALSO;
	}
	/* cruce de fin de ano: 1 dia */
	if ( CalendDiasTranscurridos ( 2024, 12, 31, 2025, 1, 1 ) != 1 )
	{
		printf( "Error caso 4: se esperaba 1: %ld\n", CalendDiasTranscurridos ( 2024, 12, 31, 2025, 1, 1 ) );
		iRes = BOOL_VAL_FALSO;
	}

	return ( iRes );
}



/* CalendSegundosIntercalaresAcumulados: cuenta de segundos intercalares
 * acumulados hasta una fecha. Defecto observado: la condicion del bucle
 * (lFechaCmp <= tabla) y la del incremento (lFechaCmp > tabla) son
 * excluyentes, de modo que nunca incrementa y siempre devuelve 0. */
static int TestDetCalendSegundosIntercalares01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	int iAcum2024;
	int iAcum1973;
	printf( "Test DetCalendSegundosIntercalares 01:\n" );

	/* en 2024 ya hay varios segundos intercalares acumulados: debe ser > 0 */
	iAcum2024 = CalendSegundosIntercalaresAcumulados ( 2024, 1, 1 );
	if ( iAcum2024 <= 0 )
	{
		printf( "Error caso 1: en 2024 el acumulado deberia ser mayor que 0: %d\n", iAcum2024 );
		iRes = BOOL_VAL_FALSO;
	}
	/* el acumulado crece con el tiempo: 2024 > 1973 */
	iAcum1973 = CalendSegundosIntercalaresAcumulados ( 1973, 1, 1 );
	if ( iAcum2024 <= iAcum1973 )
	{
		printf( "Error caso 2: el acumulado deberia crecer con el tiempo: 2024=%d 1973=%d\n", iAcum2024, iAcum1973 );
		iRes = BOOL_VAL_FALSO;
	}
	/* antes del inicio de los segundos intercalares (1972) el acumulado es 0 */
	if ( CalendSegundosIntercalaresAcumulados ( 1970, 1, 1 ) != 0 )
	{
		printf( "Error caso 3: antes de 1972 el acumulado deberia ser 0\n" );
		iRes = BOOL_VAL_FALSO;
	}

	return ( iRes );
}



int TestDeteccion ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test Deteccion]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestDetFecSumarMeses01 () == BOOL_VAL_CIERTO ) &&
			( TestDetFecSumarAnos01 () == BOOL_VAL_CIERTO ) &&
			( TestDetHorEstablecerValor01 () == BOOL_VAL_CIERTO ) &&
			( TestDetCalendDiasTranscurridos01 () == BOOL_VAL_CIERTO ) &&
			( TestDetCalendSegundosIntercalares01 () == BOOL_VAL_CIERTO ) )
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
