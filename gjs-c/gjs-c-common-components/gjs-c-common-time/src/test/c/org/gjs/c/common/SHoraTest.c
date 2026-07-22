#include "Base.h"

#include "SHora.h"



static int TestSHorCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	SHora * p_horObj;
	printf( "Test SHorCrear 01:\n" );

	p_horObj = SHorCrear ( 120000 );
	if ( ES_NULO ( p_horObj ) )
	{
		printf( "Error caso 0: no se pudo crear la hora\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SHorValor ( p_horObj ) != 120000 )
		{
			printf( "Error caso 1: se esperaba 120000: %ld\n", SHorValor ( p_horObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SHorEsValida ( p_horObj ) != 1 )
		{
			printf( "Error caso 2: la hora deberia ser valida\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SHorTieneValor ( p_horObj ) != 1 )
		{
			printf( "Error caso 3: la hora deberia tener valor\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SHorHH ( p_horObj ) != 12 ) || ( SHorMI ( p_horObj ) != 0 ) || ( SHorSS ( p_horObj ) != 0 ) )
		{
			printf( "Error caso 4: componentes incorrectos: %d %d %d\n", SHorHH ( p_horObj ), SHorMI ( p_horObj ), SHorSS ( p_horObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SHorEstablecer ( p_horObj, 83015 ) != 1 )
		{
			printf( "Error caso 5: SHorEstablecer deberia devolver 1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SHorValor ( p_horObj ) != 83015 )
		{
			printf( "Error caso 6: el valor no se actualizo\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	SHorDestruir ( (SHora **) &p_horObj );
	if ( ES_VALIDO ( p_horObj ) )
	{
		printf( "Error caso 7: tras destruir el puntero deberia ser nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}

	/* hora invalida: queda sin valor */
	p_horObj = SHorCrear ( 240000 );
	if ( ES_NULO ( p_horObj ) )
	{
		printf( "Error caso 8: SHorCrear deberia reservar el objeto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SHorTieneValor ( p_horObj ) != 0 )
		{
			printf( "Error caso 9: hora invalida no deberia tener valor\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	SHorDestruir ( (SHora **) &p_horObj );

	/* comportamiento defensivo con nulo */
	if ( SHorValor ( NULL ) != 0 )
	{
		printf( "Error caso 10: SHorValor de nulo deberia dar 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SHorEsValida ( NULL ) != 0 )
	{
		printf( "Error caso 11: SHorEsValida de nulo deberia dar 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SHorEstablecer ( NULL, 120000 ) != 0 )
	{
		printf( "Error caso 12: SHorEstablecer de nulo deberia dar 0\n" );
		iRes = BOOL_VAL_FALSO;
	}

	return ( iRes );
}



static int TestSHorComparar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	SHora * p_horA;
	SHora * p_horB;
	printf( "Test SHorComparar 01:\n" );

	p_horA = SHorCrear ( 100000 );
	p_horB = SHorCrear ( 120000 );
	if ( ES_NULO ( p_horA ) || ES_NULO ( p_horB ) )
	{
		printf( "Error caso 0: no se pudieron crear las horas\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SHorEsMenor ( p_horA, p_horB ) != 1 )
		{
			printf( "Error caso 1: A deberia ser menor que B\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SHorEsMayor ( p_horB, p_horA ) != 1 )
		{
			printf( "Error caso 2: B deberia ser mayor que A\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SHorEsIgual ( p_horA, p_horA ) != 1 )
		{
			printf( "Error caso 3: A deberia ser igual a A\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SHorEsDiferente ( p_horA, p_horB ) != 1 )
		{
			printf( "Error caso 4: A deberia ser diferente de B\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SHorEsMenorValor ( p_horA, 120000 ) != 1 )
		{
			printf( "Error caso 5: A deberia ser menor que el valor 120000\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SHorEsIgualValor ( p_horA, 100000 ) != 1 )
		{
			printf( "Error caso 6: A deberia ser igual al valor 100000\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SHorEsIgualLit ( p_horA, "100000" ) != 1 )
		{
			printf( "Error caso 7: A deberia ser igual al literal 100000\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	SHorDestruir ( (SHora **) &p_horA );
	SHorDestruir ( (SHora **) &p_horB );

	return ( iRes );
}



static int TestSHorDiferenciaFormato01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	SHora * p_horA;
	SHora * p_horB;
	char * p_cRes;
	printf( "Test SHorDiferenciaFormato 01:\n" );

	p_horA = SHorCrear ( 120000 );
	p_horB = SHorCrear ( 100000 );
	if ( ES_NULO ( p_horA ) || ES_NULO ( p_horB ) )
	{
		printf( "Error caso 0: no se pudieron crear las horas\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SHorDiferenciaValor ( p_horA, 100000 ) != 20000 )
		{
			printf( "Error caso 1: se esperaba 20000: %ld\n", SHorDiferenciaValor ( p_horA, 100000 ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SHorDiferencia ( p_horA, p_horB ) != 20000 )
		{
			printf( "Error caso 2: se esperaba 20000\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* formato numerico: HHMMSS */
		p_cRes = SHorHoraForm ( p_horA, FEC_FORMATO_NUMERICO );
		if ( ES_NULO ( p_cRes ) )
		{
			printf( "Error caso 3: SHorHoraForm devolvio nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		else if ( CadComparar ( p_cRes, "120000" ) != COMP_IGUAL )
		{
			printf( "Error caso 4: se esperaba \"120000\": [%s]\n", ES_VALIDO ( p_cRes ) ? p_cRes : "(nulo)" );
			iRes = BOOL_VAL_FALSO;
		}
		MemLiberar ( (void **) &p_cRes );
		p_cRes = SHorHora ( p_horA );
		if ( ES_NULO ( p_cRes ) )
		{
			printf( "Error caso 5: SHorHora devolvio nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		MemLiberar ( (void **) &p_cRes );
	}
	SHorDestruir ( (SHora **) &p_horA );
	SHorDestruir ( (SHora **) &p_horB );

	return ( iRes );
}



int TestSHora ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SHora]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSHorCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSHorComparar01 () == BOOL_VAL_CIERTO ) &&
			( TestSHorDiferenciaFormato01 () == BOOL_VAL_CIERTO ) )
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
