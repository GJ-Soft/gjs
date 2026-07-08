#include "Base.h"

#include "SSecuenciaPtr.h"



static byte * CrearDatoEntero ( int iValor )
{
	int * p_iDato = (int *) MemReservar ( sizeof ( int ) );
	if ( ES_VALIDO ( p_iDato ) )
	{
		*p_iDato = iValor;
	}
	return ( (byte *) p_iDato );
}

static int ValorElem ( SSecuenciaPtr * p_secObj, int iElem )
{
	return ( *( (int *) SSecpElemento ( p_secObj, iElem ) ) );
}



static int TestSSecpOperaciones01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SSecpOperaciones 01:\n" );

	/* Los datos los posee el test ( se desactiva la liberacion de la secuencia ). */
	byte * p_d1 = CrearDatoEntero ( 10 );
	byte * p_d2 = CrearDatoEntero ( 20 );
	byte * p_d3 = CrearDatoEntero ( 30 );
	SSecuenciaPtr * p_secObj = SSecpCrear ();
	if ( ES_VALIDO ( p_secObj ) && ES_VALIDO ( p_d1 ) && ES_VALIDO ( p_d2 ) && ES_VALIDO ( p_d3 ) )
	{
		SSecpDesactivarLiberacionMemoria ( p_secObj );

		if ( ( SSecpInsertar ( p_secObj, p_d1 ) != 1 ) ||
			 ( SSecpInsertar ( p_secObj, p_d2 ) != 1 ) ||
			 ( SSecpInsertar ( p_secObj, p_d3 ) != 1 ) )
		{
			printf( "Error caso 1: se esperaba poder insertar los tres datos\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SSecpNumElementos ( p_secObj ) != 3 ) || ( ValorElem ( p_secObj, 1 ) != 20 ) )
		{
			printf( "Error caso 2: deberia haber 3 elementos y el del indice 1 valer 20\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SSecpEstaVacia ( p_secObj ) != 0 ) || ( SSecpElemento ( p_secObj, 0 ) != p_d1 ) )
		{
			printf( "Error caso 3: la secuencia no deberia estar vacia y el elemento 0 ser p_d1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Eliminar el primero ( sin liberar, la liberacion esta desactivada ). */
		if ( ( SSecpEliminar ( p_secObj, 0 ) != 1 ) ||
			 ( SSecpNumElementos ( p_secObj ) != 2 ) || ( ValorElem ( p_secObj, 0 ) != 20 ) )
		{
			printf( "Error caso 4: tras eliminar el primero deberian quedar 20 y 30\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SSecpVaciar ( p_secObj );
		if ( SSecpNumElementos ( p_secObj ) != 0 )
		{
			printf( "Error caso 5: tras vaciar no deberia quedar ningun elemento\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear la secuencia o los datos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SSecpDestruir ( &p_secObj );
	/* El test libera sus propios datos. */
	MemLiberar ( (void **) &p_d1 );
	MemLiberar ( (void **) &p_d2 );
	MemLiberar ( (void **) &p_d3 );
	return ( iRes );
}

static int TestSSecpInvalidos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SSecpInvalidos 01:\n" );

	if ( SSecpEsValida ( NULL ) != 0 )
	{
		printf( "Error caso 1: una secuencia nula no deberia ser valida\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SSecpNumElementos ( NULL ) != 0 )
	{
		printf( "Error caso 2: una secuencia nula deberia tener 0 elementos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( SSecpElemento ( NULL, 0 ) ) )
	{
		printf( "Error caso 3: el elemento de una secuencia nula deberia ser nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SSecuenciaPtr * p_secNula = NULL;
	SSecpDestruir ( &p_secNula );
	return ( iRes );
}



int TestSSecuenciaPtr ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SSecuenciaPtr]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSSecpOperaciones01 () == BOOL_VAL_CIERTO ) &&
			( TestSSecpInvalidos01 () == BOOL_VAL_CIERTO ) )
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
