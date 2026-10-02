#include "Base.h"

#include "Calendario.h"



static int TestCalendValido01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test CalendValido 01:\n" );

	if ( CalendEsValido ( 2024, 2, 29 ) != 1 )
	{
		printf( "Error caso 1: 29/02/2024 deberia ser valido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( CalendEsValido ( 2023, 2, 29 ) != 0 )
	{
		printf( "Error caso 2: 29/02/2023 no deberia ser valido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* dias eliminados por la reforma gregoriana (5..14 de octubre de 1582) */
	if ( CalendEsValido ( 1582, 10, 10 ) != 0 )
	{
		printf( "Error caso 3: 10/10/1582 no deberia ser valido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( CalendEsValido ( 1582, 10, 4 ) != 1 )
	{
		printf( "Error caso 4: 04/10/1582 deberia ser valido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( CalendEsValido ( 1582, 10, 15 ) != 1 )
	{
		printf( "Error caso 5: 15/10/1582 deberia ser valido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( CalendEsMenor ( 2024, 1, 1, 2024, 1, 2 ) != 1 )
	{
		printf( "Error caso 6: 01 < 02\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( CalendEsIgual ( 2024, 1, 1, 2024, 1, 1 ) != 1 )
	{
		printf( "Error caso 7: fechas iguales\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( CalendEsMayor ( 2024, 2, 1, 2024, 1, 1 ) != 1 )
	{
		printf( "Error caso 8: febrero > enero\n" );
		iRes = BOOL_VAL_FALSO;
	}

	return ( iRes );
}



static int TestCalendBisiesto01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test CalendBisiesto 01:\n" );

	if ( CalendEsBisiesto ( 2024 ) != 1 )
	{
		printf( "Error caso 1: 2024 es bisiesto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( CalendEsBisiesto ( 2023 ) != 0 )
	{
		printf( "Error caso 2: 2023 no es bisiesto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( CalendEsBisiesto ( 1900 ) != 0 )
	{
		printf( "Error caso 3: 1900 no es bisiesto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( CalendEsBisiesto ( 2000 ) != 1 )
	{
		printf( "Error caso 4: 2000 es bisiesto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( CalendDiasAno ( 2024 ) != 366 )
	{
		printf( "Error caso 5: 2024 tiene 366 dias: %d\n", CalendDiasAno ( 2024 ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( CalendDiasAno ( 2023 ) != 365 )
	{
		printf( "Error caso 6: 2023 tiene 365 dias\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* 1582 pierde 10 dias por la reforma: 355 */
	if ( CalendDiasAno ( 1582 ) != 355 )
	{
		printf( "Error caso 7: 1582 tiene 355 dias: %d\n", CalendDiasAno ( 1582 ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( CalendDiasMes ( 2024, 2 ) != 29 )
	{
		printf( "Error caso 8: febrero 2024 tiene 29 dias\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( CalendDiasMes ( 2023, 2 ) != 28 )
	{
		printf( "Error caso 9: febrero 2023 tiene 28 dias\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( CalendDiasMes ( 2024, 4 ) != 30 )
	{
		printf( "Error caso 10: abril tiene 30 dias\n" );
		iRes = BOOL_VAL_FALSO;
	}

	return ( iRes );
}



static int TestCalendDias01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test CalendDias 01:\n" );

	/* hasta marzo de 2024: enero (31) + febrero (29) = 60 */
	if ( CalendDiasAnualesHastaElMes ( 2024, 3 ) != 60 )
	{
		printf( "Error caso 1: se esperaba 60: %d\n", CalendDiasAnualesHastaElMes ( 2024, 3 ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( CalendDiasAnualesHastaElMes ( 2024, 1 ) != 0 )
	{
		printf( "Error caso 2: se esperaba 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* desde diciembre no queda ningun mes posterior */
	if ( CalendDiasAnualesDesdeElMes ( 2024, 12 ) != 0 )
	{
		printf( "Error caso 3: se esperaba 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* desde noviembre queda diciembre (31) */
	if ( CalendDiasAnualesDesdeElMes ( 2024, 11 ) != 31 )
	{
		printf( "Error caso 4: se esperaba 31: %d\n", CalendDiasAnualesDesdeElMes ( 2024, 11 ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( CalendDiasHastaElAno ( 1 ) != 0 )
	{
		printf( "Error caso 5: se esperaba 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* el ano 1 no es bisiesto: 365 dias hasta el ano 2 */
	if ( CalendDiasHastaElAno ( 2 ) != 365 )
	{
		printf( "Error caso 6: se esperaba 365: %ld\n", CalendDiasHastaElAno ( 2 ) );
		iRes = BOOL_VAL_FALSO;
	}
	/* fecha invalida -> 0 */
	if ( CalendDiasTranscurridos ( 2024, 13, 1, 2024, 1, 1 ) != 0 )
	{
		printf( "Error caso 7: fecha invalida deberia dar 0\n" );
		iRes = BOOL_VAL_FALSO;
	}

	return ( iRes );
}



static int TestCalendSemana01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	int iDia;
	int iSuma;
	printf( "Test CalendSemana 01:\n" );

	/* para una fecha valida el dia de la semana esta en el rango [0, 6] */
	iDia = CalendDiaSemana ( 2024, 1, 1 );
	if ( ( iDia < 0 ) || ( iDia > 6 ) )
	{
		printf( "Error caso 1: dia de la semana fuera de rango: %d\n", iDia );
		iRes = BOOL_VAL_FALSO;
	}
	/* fecha invalida -> -1 */
	if ( CalendDiaSemana ( 2024, 13, 1 ) != -1 )
	{
		printf( "Error caso 2: fecha invalida deberia dar -1\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* exactamente uno de los siete predicados de dia debe ser cierto */
	iSuma = CalendDiaEsLunes ( 2024, 1, 1 ) + CalendDiaEsMartes ( 2024, 1, 1 ) +
			CalendDiaEsMiercoles ( 2024, 1, 1 ) + CalendDiaEsJueves ( 2024, 1, 1 ) +
			CalendDiaEsViernes ( 2024, 1, 1 ) + CalendDiaEsSabado ( 2024, 1, 1 ) +
			CalendDiaEsDomingo ( 2024, 1, 1 );
	if ( iSuma != 1 )
	{
		printf( "Error caso 3: solo un dia de la semana deberia ser cierto: %d\n", iSuma );
		iRes = BOOL_VAL_FALSO;
	}
	/* dias consecutivos deben dar dias de la semana consecutivos (modulo 7) */
	if ( ( ( CalendDiaSemana ( 2024, 1, 1 ) + 1 ) % 7 ) != CalendDiaSemana ( 2024, 1, 2 ) )
	{
		printf( "Error caso 4: 02/01/2024 deberia ser el dia siguiente a 01/01/2024\n" );
		iRes = BOOL_VAL_FALSO;
	}

	return ( iRes );
}



static int TestCalendSistema01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test CalendSistema 01:\n" );

	/* despues del 16/03/1940 -> UTC */
	if ( CalendSistemaHorarioUTC ( 2024, 1, 1 ) != 1 )
	{
		printf( "Error caso 1: 2024 deberia ser UTC\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* entre 1901 y 1940 -> GMT */
	if ( CalendSistemaHorarioGMT ( 1920, 1, 1 ) != 1 )
	{
		printf( "Error caso 2: 1920 deberia ser GMT\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* antes de 1901 -> MMT */
	if ( CalendSistemaHorarioMMT ( 1800, 1, 1 ) != 1 )
	{
		printf( "Error caso 3: 1800 deberia ser MMT\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( CalendEsDiaCambioASistemaHorarioUTC ( 1940, 3, 16 ) != 1 )
	{
		printf( "Error caso 4: 16/03/1940 deberia ser cambio a UTC\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( CalendEsDiaCambioASistemaHorarioGMT ( 1901, 1, 1 ) != 1 )
	{
		printf( "Error caso 5: 01/01/1901 deberia ser cambio a GMT\n" );
		iRes = BOOL_VAL_FALSO;
	}

	return ( iRes );
}



static int TestCalendCambioHorario01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	int iDiaVer;
	int iDiaInv;
	printf( "Test CalendCambioHorario 01:\n" );

	/* desde 1996 el cambio a horario de verano es en marzo y a invierno en octubre */
	if ( CalendMesCambioAHorarioVerano ( 2024 ) != 3 )
	{
		printf( "Error caso 1: se esperaba mes 3: %d\n", CalendMesCambioAHorarioVerano ( 2024 ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( CalendMesCambioAHorarioInvierno ( 2024 ) != 10 )
	{
		printf( "Error caso 2: se esperaba mes 10: %d\n", CalendMesCambioAHorarioInvierno ( 2024 ) );
		iRes = BOOL_VAL_FALSO;
	}
	/* el cambio es el ultimo domingo del mes: dia en [24, 31] y ha de ser domingo */
	iDiaVer = CalendDiaCambioAHorarioVerano ( 2024 );
	if ( ( iDiaVer < 24 ) || ( iDiaVer > 31 ) )
	{
		printf( "Error caso 3: dia de cambio a verano fuera de rango: %d\n", iDiaVer );
		iRes = BOOL_VAL_FALSO;
	}
	if ( CalendDiaEsDomingo ( 2024, 3, iDiaVer ) != 1 )
	{
		printf( "Error caso 4: el dia de cambio a verano deberia ser domingo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	iDiaInv = CalendDiaCambioAHorarioInvierno ( 2024 );
	if ( ( iDiaInv < 24 ) || ( iDiaInv > 31 ) )
	{
		printf( "Error caso 5: dia de cambio a invierno fuera de rango: %d\n", iDiaInv );
		iRes = BOOL_VAL_FALSO;
	}
	if ( CalendDiaEsDomingo ( 2024, 10, iDiaInv ) != 1 )
	{
		printf( "Error caso 6: el dia de cambio a invierno deberia ser domingo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* coherencia con el predicado EsDiaCambio... */
	if ( CalendEsDiaCambioAHorarioVerano ( 2024, 3, iDiaVer ) != 1 )
	{
		printf( "Error caso 7: EsDiaCambioAHorarioVerano deberia dar 1 para el dia calculado\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( CalendEsDiaCambioAHorarioInvierno ( 2024, 10, iDiaInv ) != 1 )
	{
		printf( "Error caso 8: EsDiaCambioAHorarioInvierno deberia dar 1 para el dia calculado\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( CalendEsDiaCambioAHorarioVerano ( 2024, 6, 1 ) != 0 )
	{
		printf( "Error caso 9: 01/06/2024 no es cambio a verano\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* 30/06/1972 es dia de segundo intercalar */
	if ( CalendEsDiaDeSegundoIntercalar ( 1972, 6, 30 ) != 1 )
	{
		printf( "Error caso 10: 30/06/1972 deberia ser segundo intercalar\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( CalendEsDiaDeSegundoIntercalar ( 2024, 1, 1 ) != 0 )
	{
		printf( "Error caso 11: 01/01/2024 no es segundo intercalar\n" );
		iRes = BOOL_VAL_FALSO;
	}

	return ( iRes );
}




/* Dias de la semana REALES. El test 01 comprueba cosas consistentes consigo
   mismas —que el valor este en [0,6], que solo uno de los siete predicados sea
   cierto, que dos dias seguidos den valores seguidos— y las cuatro las pasa
   igual de bien una funcion desplazada un numero fijo de dias, que es justo lo
   que pasaba hasta el 2026-09-20: CalendDiaSemana fallaba en TODAS las fechas,
   tres posiciones, y ningun test se enteraba.

   Los valores de abajo son historicos, del calendario gregoriano proleptico.
   Los indices son los de TiempoConfig.h, que el test no puede incluir por ser
   privada: lunes 0, martes 1, miercoles 2, jueves 3, viernes 4, sabado 5 y
   domingo 6.

   Se cubren los dos calendarios. Las anteriores al 15 de octubre de 1582 son
   JULIANAS y no coinciden con lo que diria una libreria moderna sobre esa misma
   fecha, porque casi todas usan el gregoriano proleptico. Las dos de referencia
   son hechos historicos comprobables: la batalla de Hastings fue en sabado y
   Colon llego en viernes. */
static int TestCalendSemana02 ()
{
	int			iRes = BOOL_VAL_CIERTO;
	int			iDia;
	int			i;
	static const int p_iCasos [] [ 4 ] = {
		/* ano,  mes, dia, dia de la semana */
		/* Anteriores a la reforma, o sea calendario JULIANO: */
		{ 1000,  1,  1, 0 },		/* lunes     */
		{ 1066, 10, 14, 5 },		/* sabado, la batalla de Hastings */
		{ 1200,  6, 15, 3 },		/* jueves    */
		{ 1492, 10, 12, 4 },		/* viernes, la llegada de Colon */
		{ 1500,  1,  1, 2 },		/* miercoles */
		{ 1581,  1,  1, 6 },		/* domingo   */
		{ 1582, 10,  4, 3 },		/* jueves, el ultimo dia juliano en Espana */
		/* Posteriores, o sea GREGORIANO: */
		{ 1583,  1,  1, 5 },		/* sabado    */
		{ 1600,  2, 29, 1 },		/* martes    */
		{ 1700,  3,  1, 0 },		/* lunes     */
		{ 1800,  1,  1, 2 },		/* miercoles */
		{ 1900,  1,  1, 0 },		/* lunes     */
		{ 1944,  6,  6, 1 },		/* martes, el desembarco de Normandia */
		{ 2000,  1,  1, 5 },		/* sabado    */
		{ 2000,  2, 29, 1 },		/* martes    */
		{ 2024,  2, 29, 3 },		/* jueves    */
		{ 2025,  3, 30, 6 },		/* domingo   */
		{ 2025, 10, 26, 6 },		/* domingo   */
		{ 2100,  1,  1, 4 }			/* viernes   */
	};
	printf( "Test CalendSemana 02:\n" );

	for ( i = 0; i < (int) ( sizeof ( p_iCasos ) / sizeof ( p_iCasos [ 0 ] ) ); i = i + 1 )
	{
		iDia = CalendDiaSemana ( p_iCasos [ i ] [ 0 ], p_iCasos [ i ] [ 1 ], p_iCasos [ i ] [ 2 ] );
		if ( iDia != p_iCasos [ i ] [ 3 ] )
		{
			printf( "Error caso %d: %02d/%02d/%04d deberia dar %d y da %d\n",
					i + 1, p_iCasos [ i ] [ 2 ], p_iCasos [ i ] [ 1 ],
					p_iCasos [ i ] [ 0 ], p_iCasos [ i ] [ 3 ], iDia );
			iRes = BOOL_VAL_FALSO;
		}
	}
	return ( iRes );
}


/* Dias y meses de cambio horario REALES, uno por cada una de las cinco epocas
   que distingue el codigo: las tablas de 1918-1949, la interrupcion de
   1950-1973, las tablas de 1974-1980, la regla de septiembre de 1981-1995 y la
   de octubre de 1996 en adelante.

   Contrastados el 2026-09-20 contra los datos de IANA ( zdump -v Europe/Madrid ).
   Las tablas guardan EL DIA EN QUE EL RELOJ CAMBIA, no la vispera. */
static int TestCalendCambioHorario02 ()
{
	int			iRes = BOOL_VAL_CIERTO;
	int			i;
	static const int p_iCasos [] [ 5 ] = {
		/* ano, mes ver, dia ver, mes inv, dia inv */
		{ 1918,  4, 16, 10,  7 },
		{ 1944,  4, 16, 10,  1 },
		{ 1960, -1, -1, -1, -1 },	/* de 1950 a 1973 no hubo cambio horario */
		{ 1975,  4, 13, 10,  5 },
		{ 1985,  3, 31,  9, 29 },	/* de 1981 a 1995 la vuelta era en septiembre */
		{ 2025,  3, 30, 10, 26 }
	};
	printf( "Test CalendCambioHorario 02:\n" );

	for ( i = 0; i < (int) ( sizeof ( p_iCasos ) / sizeof ( p_iCasos [ 0 ] ) ); i = i + 1 )
	{
		int iA = p_iCasos [ i ] [ 0 ];
		if ( CalendMesCambioAHorarioVerano ( iA ) != p_iCasos [ i ] [ 1 ] )
		{
			printf( "Error caso %d: mes de cambio a verano de %04d deberia ser %d y es %d\n",
					i + 1, iA, p_iCasos [ i ] [ 1 ], CalendMesCambioAHorarioVerano ( iA ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( CalendDiaCambioAHorarioVerano ( iA ) != p_iCasos [ i ] [ 2 ] )
		{
			printf( "Error caso %d: dia de cambio a verano de %04d deberia ser %d y es %d\n",
					i + 1, iA, p_iCasos [ i ] [ 2 ], CalendDiaCambioAHorarioVerano ( iA ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( CalendMesCambioAHorarioInvierno ( iA ) != p_iCasos [ i ] [ 3 ] )
		{
			printf( "Error caso %d: mes de cambio a invierno de %04d deberia ser %d y es %d\n",
					i + 1, iA, p_iCasos [ i ] [ 3 ], CalendMesCambioAHorarioInvierno ( iA ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( CalendDiaCambioAHorarioInvierno ( iA ) != p_iCasos [ i ] [ 4 ] )
		{
			printf( "Error caso %d: dia de cambio a invierno de %04d deberia ser %d y es %d\n",
					i + 1, iA, p_iCasos [ i ] [ 4 ], CalendDiaCambioAHorarioInvierno ( iA ) );
			iRes = BOOL_VAL_FALSO;
		}
	}
	return ( iRes );
}


/* CalendAplicarUnaHoraMas: 1 si en esa fecha rige el HORARIO DE VERANO. Ojo con
   el sentido, que estuvo invertido de 1996 en adelante hasta el 2026-09-20 y
   nadie lo vio porque no habia ni un test que llamase a esta funcion.

   Se prueban los dos dias de cada frontera —el ultimo de invierno y el primero
   de verano— en las cinco epocas, mas tres fechas de control en anos sin cambio
   horario. El dia del cambio cuenta como lo que EMPIEZA. */
static int TestCalendAplicarUnaHoraMas01 ()
{
	int			iRes = BOOL_VAL_CIERTO;
	int			iVal;
	int			i;
	static const int p_iCasos [] [ 4 ] = {
		/* ano, mes, dia, esperado */
		{ 1917,  7,  1, 0 },		/* antes de 1918 no existia el cambio horario */
		{ 1918,  4, 15, 0 },
		{ 1918,  4, 16, 1 },
		{ 1918, 10,  6, 1 },
		{ 1918, 10,  7, 0 },
		{ 1940,  7,  1, 0 },		/* el adelanto de 1940 NO fue estacional: fue el
									   paso definitivo a UTC+1, y lo lleva
									   CalendSistemaHorarioUTC */
		{ 1944,  4, 15, 0 },
		{ 1944,  4, 16, 1 },
		{ 1944,  9, 30, 1 },
		{ 1944, 10,  1, 0 },
		{ 1960,  7,  1, 0 },		/* de 1950 a 1973, sin cambio horario */
		{ 1974,  4, 13, 0 },
		{ 1974,  4, 14, 1 },
		{ 1974, 10,  5, 1 },
		{ 1974, 10,  6, 0 },
		{ 1985,  3, 30, 0 },
		{ 1985,  3, 31, 1 },
		{ 1985,  9, 28, 1 },
		{ 1985,  9, 29, 0 },
		{ 2025,  3, 29, 0 },
		{ 2025,  3, 30, 1 },
		{ 2025, 10, 25, 1 },
		{ 2025, 10, 26, 0 }
	};
	printf( "Test CalendAplicarUnaHoraMas 01:\n" );

	for ( i = 0; i < (int) ( sizeof ( p_iCasos ) / sizeof ( p_iCasos [ 0 ] ) ); i = i + 1 )
	{
		iVal = CalendAplicarUnaHoraMas ( p_iCasos [ i ] [ 0 ], p_iCasos [ i ] [ 1 ], p_iCasos [ i ] [ 2 ] );
		if ( iVal != p_iCasos [ i ] [ 3 ] )
		{
			printf( "Error caso %d: %02d/%02d/%04d deberia dar %d y da %d\n",
					i + 1, p_iCasos [ i ] [ 2 ], p_iCasos [ i ] [ 1 ],
					p_iCasos [ i ] [ 0 ], p_iCasos [ i ] [ 3 ], iVal );
			iRes = BOOL_VAL_FALSO;
		}
	}
	return ( iRes );
}


int TestCalendario ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test Calendario]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestCalendValido01 () == BOOL_VAL_CIERTO ) &&
			( TestCalendBisiesto01 () == BOOL_VAL_CIERTO ) &&
			( TestCalendDias01 () == BOOL_VAL_CIERTO ) &&
			( TestCalendSemana01 () == BOOL_VAL_CIERTO ) &&
			( TestCalendSistema01 () == BOOL_VAL_CIERTO ) &&
			( TestCalendCambioHorario01 () == BOOL_VAL_CIERTO ) &&
			( TestCalendSemana02 () == BOOL_VAL_CIERTO ) &&
			( TestCalendCambioHorario02 () == BOOL_VAL_CIERTO ) &&
			( TestCalendAplicarUnaHoraMas01 () == BOOL_VAL_CIERTO ) )
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
