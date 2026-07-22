#include "Base.h"

#include "SFechaHora.h"



static int TestSFecHorCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	SFechaHora * p_fecObj;
	printf( "Test SFecHorCrear 01:\n" );

	p_fecObj = SFecHorCrearFecHor ( 20240102, 133045 );
	if ( ES_NULO ( p_fecObj ) )
	{
		printf( "Error caso 0: no se pudo crear la fecha-hora\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SFecHorValorFecha ( p_fecObj ) != 20240102 )
		{
			printf( "Error caso 1: fecha deberia ser 20240102: %ld\n", SFecHorValorFecha ( p_fecObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SFecHorValorHora ( p_fecObj ) != 133045 )
		{
			printf( "Error caso 2: hora deberia ser 133045: %ld\n", SFecHorValorHora ( p_fecObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SFecHorAAAA ( p_fecObj ) != 2024 ) || ( SFecHorMM ( p_fecObj ) != 1 ) || ( SFecHorDD ( p_fecObj ) != 2 ) )
		{
			printf( "Error caso 3: componentes de fecha incorrectos: %d %d %d\n", SFecHorAAAA ( p_fecObj ), SFecHorMM ( p_fecObj ), SFecHorDD ( p_fecObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SFecHorHH ( p_fecObj ) != 13 ) || ( SFecHorMI ( p_fecObj ) != 30 ) || ( SFecHorSS ( p_fecObj ) != 45 ) )
		{
			printf( "Error caso 4: componentes de hora incorrectos: %d %d %d\n", SFecHorHH ( p_fecObj ), SFecHorMI ( p_fecObj ), SFecHorSS ( p_fecObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SFecHorTieneValor ( p_fecObj ) != 1 )
		{
			printf( "Error caso 5: deberia tener valor\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SFecHorEsValida ( p_fecObj ) != 1 )
		{
			printf( "Error caso 6: deberia ser valida\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SFecHorEstablecerFecHor ( p_fecObj, 20240101, 120000 ) != 1 )
		{
			printf( "Error caso 7: SFecHorEstablecerFecHor deberia devolver 1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SFecHorValorFecha ( p_fecObj ) != 20240101 )
		{
			printf( "Error caso 8: el valor no se actualizo\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	SFecHorDestruir ( (SFechaHora **) &p_fecObj );
	if ( ES_VALIDO ( p_fecObj ) )
	{
		printf( "Error caso 9: tras destruir el puntero deberia ser nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}

	/* fecha invalida: queda sin valor */
	p_fecObj = SFecHorCrearFecHor ( 20241301, 120000 );
	if ( ES_NULO ( p_fecObj ) )
	{
		printf( "Error caso 10: SFecHorCrearFecHor deberia reservar el objeto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SFecHorTieneValor ( p_fecObj ) != 0 )
		{
			printf( "Error caso 11: fecha invalida no deberia tener valor\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	SFecHorDestruir ( (SFechaHora **) &p_fecObj );

	/* comportamiento defensivo con nulo */
	if ( SFecHorValor ( NULL ) != 0.0 )
	{
		printf( "Error caso 12: SFecHorValor de nulo deberia dar 0.0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SFecHorEsValida ( NULL ) != 0 )
	{
		printf( "Error caso 13: SFecHorEsValida de nulo deberia dar 0\n" );
		iRes = BOOL_VAL_FALSO;
	}

	return ( iRes );
}



static int TestSFecHorComparar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	SFechaHora * p_fecA;
	SFechaHora * p_fecB;
	double dValA;
	printf( "Test SFecHorComparar 01:\n" );

	p_fecA = SFecHorCrearFecHor ( 20240101, 120000 );
	p_fecB = SFecHorCrearFecHor ( 20240101, 130000 );
	if ( ES_NULO ( p_fecA ) || ES_NULO ( p_fecB ) )
	{
		printf( "Error caso 0: no se pudieron crear las fechas-hora\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		dValA = SFecHorValor ( p_fecA );
		if ( SFecHorEsMenor ( p_fecA, p_fecB ) != 1 )
		{
			printf( "Error caso 1: A deberia ser menor que B\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SFecHorEsMayor ( p_fecB, p_fecA ) != 1 )
		{
			printf( "Error caso 2: B deberia ser mayor que A\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SFecHorEsIgual ( p_fecA, p_fecA ) != 1 )
		{
			printf( "Error caso 3: A deberia ser igual a A\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SFecHorEsDiferente ( p_fecA, p_fecB ) != 1 )
		{
			printf( "Error caso 4: A deberia ser diferente de B\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SFecHorEsIgualValor ( p_fecA, dValA ) != 1 )
		{
			printf( "Error caso 5: A deberia ser igual a su propio valor\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	SFecHorDestruir ( (SFechaHora **) &p_fecA );
	SFecHorDestruir ( (SFechaHora **) &p_fecB );

	return ( iRes );
}



static int TestSFecHorFormato01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	SFecha * p_fecha;
	SHora * p_hora;
	SFechaHora * p_fecObj;
	char * p_cRes;
	printf( "Test SFecHorFormato 01:\n" );

	p_fecha = SFecCrear ( 20240102 );
	p_hora = SHorCrear ( 133045 );
	p_fecObj = SFecHorCrearFechaHora ( p_fecha, p_hora );
	if ( ES_NULO ( p_fecObj ) )
	{
		printf( "Error caso 0: no se pudo crear la fecha-hora\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SFecHorValorFecha ( p_fecObj ) != 20240102 )
		{
			printf( "Error caso 1: fecha deberia ser 20240102\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* formato numerico de la fecha: YYYYMMDD */
		p_cRes = SFecHorFechaForm ( p_fecObj, FEC_FORMATO_NUMERICO );
		if ( ES_NULO ( p_cRes ) || ( CadComparar ( p_cRes, "20240102" ) != COMP_IGUAL ) )
		{
			printf( "Error caso 2: se esperaba \"20240102\": [%s]\n", ES_VALIDO ( p_cRes ) ? p_cRes : "(nulo)" );
			iRes = BOOL_VAL_FALSO;
		}
		MemLiberar ( (void **) &p_cRes );
		/* formato numerico de la hora: HHMMSS */
		p_cRes = SFecHorHoraForm ( p_fecObj, FEC_FORMATO_NUMERICO );
		if ( ES_NULO ( p_cRes ) || ( CadComparar ( p_cRes, "133045" ) != COMP_IGUAL ) )
		{
			printf( "Error caso 3: se esperaba \"133045\": [%s]\n", ES_VALIDO ( p_cRes ) ? p_cRes : "(nulo)" );
			iRes = BOOL_VAL_FALSO;
		}
		MemLiberar ( (void **) &p_cRes );
		/* formato numerico combinado: YYYYMMDDHHMMSS */
		p_cRes = SFecHorFechaHoraForm ( p_fecObj, FEC_FORMATO_NUMERICO );
		if ( ES_NULO ( p_cRes ) || ( CadComparar ( p_cRes, "20240102133045" ) != COMP_IGUAL ) )
		{
			printf( "Error caso 4: se esperaba \"20240102133045\": [%s]\n", ES_VALIDO ( p_cRes ) ? p_cRes : "(nulo)" );
			iRes = BOOL_VAL_FALSO;
		}
		MemLiberar ( (void **) &p_cRes );
	}
	SFecHorDestruir ( (SFechaHora **) &p_fecObj );
	SFecDestruir ( (SFecha **) &p_fecha );
	SHorDestruir ( (SHora **) &p_hora );

	return ( iRes );
}



int TestSFechaHora ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SFechaHora]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSFecHorCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSFecHorComparar01 () == BOOL_VAL_CIERTO ) &&
			( TestSFecHorFormato01 () == BOOL_VAL_CIERTO ) )
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
