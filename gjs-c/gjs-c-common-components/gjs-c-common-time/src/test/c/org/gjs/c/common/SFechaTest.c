#include "Base.h"

#include "SFecha.h"



static int TestSFecCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	SFecha * p_fecObj;
	printf( "Test SFecCrear 01:\n" );

	p_fecObj = SFecCrear ( 20240229 );
	if ( ES_NULO ( p_fecObj ) )
	{
		printf( "Error caso 0: no se pudo crear la fecha\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SFecValor ( p_fecObj ) != 20240229 )
		{
			printf( "Error caso 1: se esperaba 20240229: %ld\n", SFecValor ( p_fecObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SFecEsValida ( p_fecObj ) != 1 )
		{
			printf( "Error caso 2: la fecha deberia ser valida\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SFecTieneValor ( p_fecObj ) != 1 )
		{
			printf( "Error caso 3: la fecha deberia tener valor\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SFecAAAA ( p_fecObj ) != 2024 ) || ( SFecMM ( p_fecObj ) != 2 ) || ( SFecDD ( p_fecObj ) != 29 ) )
		{
			printf( "Error caso 4: componentes incorrectos: %d %d %d\n", SFecAAAA ( p_fecObj ), SFecMM ( p_fecObj ), SFecDD ( p_fecObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		/* cambiar el valor */
		if ( SFecEstablecer ( p_fecObj, 20200215 ) != 1 )
		{
			printf( "Error caso 5: SFecEstablecer deberia devolver 1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SFecValor ( p_fecObj ) != 20200215 )
		{
			printf( "Error caso 6: el valor no se actualizo\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	SFecDestruir ( (SFecha **) &p_fecObj );
	if ( ES_VALIDO ( p_fecObj ) )
	{
		printf( "Error caso 7: tras destruir el puntero deberia ser nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}

	/* crear a partir de literal */
	p_fecObj = SFecCrearLit ( "20240101" );
	if ( ES_NULO ( p_fecObj ) )
	{
		printf( "Error caso 8: no se pudo crear la fecha desde literal\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SFecValor ( p_fecObj ) != 20240101 )
		{
			printf( "Error caso 9: se esperaba 20240101: %ld\n", SFecValor ( p_fecObj ) );
			iRes = BOOL_VAL_FALSO;
		}
	}
	SFecDestruir ( (SFecha **) &p_fecObj );

	/* fecha invalida: queda sin valor */
	p_fecObj = SFecCrear ( 20241301 );
	if ( ES_NULO ( p_fecObj ) )
	{
		printf( "Error caso 10: SFecCrear deberia reservar el objeto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SFecTieneValor ( p_fecObj ) != 0 )
		{
			printf( "Error caso 11: fecha invalida no deberia tener valor\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SFecEsValida ( p_fecObj ) != 0 )
		{
			printf( "Error caso 12: fecha invalida no deberia ser valida\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	SFecDestruir ( (SFecha **) &p_fecObj );

	/* comportamiento defensivo con nulo */
	if ( SFecValor ( NULL ) != 0 )
	{
		printf( "Error caso 13: SFecValor de nulo deberia dar 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SFecEsValida ( NULL ) != 0 )
	{
		printf( "Error caso 14: SFecEsValida de nulo deberia dar 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SFecAAAA ( NULL ) != -1 )
	{
		printf( "Error caso 15: SFecAAAA de nulo deberia dar -1\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SFecEstablecer ( NULL, 20240101 ) != 0 )
	{
		printf( "Error caso 16: SFecEstablecer de nulo deberia dar 0\n" );
		iRes = BOOL_VAL_FALSO;
	}

	return ( iRes );
}



static int TestSFecComparar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	SFecha * p_fecA;
	SFecha * p_fecB;
	printf( "Test SFecComparar 01:\n" );

	p_fecA = SFecCrear ( 20240101 );
	p_fecB = SFecCrear ( 20240102 );
	if ( ES_NULO ( p_fecA ) || ES_NULO ( p_fecB ) )
	{
		printf( "Error caso 0: no se pudieron crear las fechas\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SFecEsMenor ( p_fecA, p_fecB ) != 1 )
		{
			printf( "Error caso 1: A deberia ser menor que B\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SFecEsMayor ( p_fecB, p_fecA ) != 1 )
		{
			printf( "Error caso 2: B deberia ser mayor que A\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SFecEsIgual ( p_fecA, p_fecA ) != 1 )
		{
			printf( "Error caso 3: A deberia ser igual a A\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SFecEsDiferente ( p_fecA, p_fecB ) != 1 )
		{
			printf( "Error caso 4: A deberia ser diferente de B\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SFecEsMenorValor ( p_fecA, 20240102 ) != 1 )
		{
			printf( "Error caso 5: A deberia ser menor que el valor 20240102\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SFecEsIgualValor ( p_fecA, 20240101 ) != 1 )
		{
			printf( "Error caso 6: A deberia ser igual al valor 20240101\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SFecEsMenorLit ( p_fecA, "20240102" ) != 1 )
		{
			printf( "Error caso 7: A deberia ser menor que el literal 20240102\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SFecEsIgualLit ( p_fecA, "20240101" ) != 1 )
		{
			printf( "Error caso 8: A deberia ser igual al literal 20240101\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	SFecDestruir ( (SFecha **) &p_fecA );
	SFecDestruir ( (SFecha **) &p_fecB );

	return ( iRes );
}



static int TestSFecDiferenciaFormato01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	SFecha * p_fecA;
	SFecha * p_fecB;
	char * p_cRes;
	printf( "Test SFecDiferenciaFormato 01:\n" );

	p_fecA = SFecCrear ( 20240105 );
	p_fecB = SFecCrear ( 20240101 );
	if ( ES_NULO ( p_fecA ) || ES_NULO ( p_fecB ) )
	{
		printf( "Error caso 0: no se pudieron crear las fechas\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		/* la diferencia es la resta numerica de los valores YYYYMMDD */
		if ( SFecDiferenciaValor ( p_fecA, 20240101 ) != 4 )
		{
			printf( "Error caso 1: se esperaba 4: %ld\n", SFecDiferenciaValor ( p_fecA, 20240101 ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SFecDiferencia ( p_fecA, p_fecB ) != 4 )
		{
			printf( "Error caso 2: se esperaba 4\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SFecDiferenciaLit ( p_fecA, "20240101" ) != 4 )
		{
			printf( "Error caso 3: se esperaba 4\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* formato numerico: YYYYMMDD */
		p_cRes = SFecFechaForm ( p_fecA, FEC_FORMATO_NUMERICO );
		if ( ES_NULO ( p_cRes ) )
		{
			printf( "Error caso 4: SFecFechaForm devolvio nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		else if ( CadComparar ( p_cRes, "20240105" ) != COMP_IGUAL )
		{
			printf( "Error caso 5: se esperaba \"20240105\": [%s]\n", ES_VALIDO ( p_cRes ) ? p_cRes : "(nulo)" );
			iRes = BOOL_VAL_FALSO;
		}
		MemLiberar ( (void **) &p_cRes );
		/* formato por defecto: solo se comprueba que no es nulo */
		p_cRes = SFecFecha ( p_fecA );
		if ( ES_NULO ( p_cRes ) )
		{
			printf( "Error caso 6: SFecFecha devolvio nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		MemLiberar ( (void **) &p_cRes );
	}
	SFecDestruir ( (SFecha **) &p_fecA );
	SFecDestruir ( (SFecha **) &p_fecB );

	return ( iRes );
}



int TestSFecha ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SFecha]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSFecCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSFecComparar01 () == BOOL_VAL_CIERTO ) &&
			( TestSFecDiferenciaFormato01 () == BOOL_VAL_CIERTO ) )
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
