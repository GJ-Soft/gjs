#include "Base.h"

#include "SConjuntoPtr.h"



static int CompararEnteros ( void * p_v1, void * p_v2 )
{
	int iRes;
	int i1 = *( (int *) p_v1 );
	int i2 = *( (int *) p_v2 );

	if ( i1 < i2 )
	{
		iRes = -1;
	}
	else if ( i1 > i2 )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

static byte * CrearDatoEntero ( int iValor )
{
	int * p_iDato = (int *) MemReservar ( sizeof ( int ) );
	if ( ES_VALIDO ( p_iDato ) )
	{
		*p_iDato = iValor;
	}
	return ( (byte *) p_iDato );
}

static int ValorElem ( SConjuntoPtr * p_cnjObj, int iElem )
{
	return ( *( (int *) SCnjpElemento ( p_cnjObj, iElem ) ) );
}



static int TestSCnjpOperaciones01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCnjpOperaciones 01:\n" );

	/* La memoria de los datos la gestiona el test ( liberacion desactivada ). */
	byte * p_d1 = CrearDatoEntero ( 10 );
	byte * p_d2 = CrearDatoEntero ( 20 );
	byte * p_d3 = CrearDatoEntero ( 10 );
	byte * p_q99 = CrearDatoEntero ( 99 );
	SConjuntoPtr * p_cnjObj = SCnjpCrear ( CompararEnteros );
	if ( ES_VALIDO ( p_cnjObj ) && ES_VALIDO ( p_d1 ) && ES_VALIDO ( p_d2 ) && ES_VALIDO ( p_d3 ) && ES_VALIDO ( p_q99 ) )
	{
		SCnjpDesactivarLiberacionMemoria ( p_cnjObj );

		if ( ( SCnjpInsertarElem ( p_cnjObj, p_d1 ) != 1 ) || ( SCnjpInsertarElem ( p_cnjObj, p_d2 ) != 1 ) )
		{
			printf( "Error caso 1: se esperaba poder insertar 10 y 20\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Un valor ya presente ( 10 ) se rechaza: semantica de conjunto. */
		if ( SCnjpInsertarElem ( p_cnjObj, p_d3 ) == 1 )
		{
			printf( "Error caso 2: insertar un valor duplicado no deberia tener exito\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCnjpNumElementos ( p_cnjObj ) != 2 )
		{
			printf( "Error caso 3: el conjunto deberia tener 2 elementos\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Los elementos quedan ordenados. */
		if ( ( ValorElem ( p_cnjObj, 0 ) != 10 ) || ( ValorElem ( p_cnjObj, 1 ) != 20 ) )
		{
			printf( "Error caso 4: los elementos deberian estar ordenados ( 10, 20 )\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SCnjpExiste ( p_cnjObj, p_d1 ) != 1 ) || ( SCnjpExiste ( p_cnjObj, p_q99 ) != 0 ) )
		{
			printf( "Error caso 5: existe deberia encontrar 10 y no 99\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCnjpBuscar ( p_cnjObj, p_d2 ) != 1 )
		{
			printf( "Error caso 6: buscar 20 deberia devolver el indice 1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Eliminar el primero. */
		SCnjpEliminarElem ( p_cnjObj, 0 );
		if ( ( SCnjpNumElementos ( p_cnjObj ) != 1 ) || ( ValorElem ( p_cnjObj, 0 ) != 20 ) )
		{
			printf( "Error caso 7: tras eliminar el 10 deberia quedar solo el 20\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SCnjpVaciar ( p_cnjObj );
		if ( SCnjpNumElementos ( p_cnjObj ) != 0 )
		{
			printf( "Error caso 8: tras vaciar no deberia quedar ningun elemento\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear el conjunto o los datos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SCnjpDestruir ( &p_cnjObj );
	/* El test libera sus propios datos. */
	MemLiberar ( (void **) &p_d1 );
	MemLiberar ( (void **) &p_d2 );
	MemLiberar ( (void **) &p_d3 );
	MemLiberar ( (void **) &p_q99 );
	return ( iRes );
}

static int TestSCnjpInvalidos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCnjpInvalidos 01:\n" );

	if ( SCnjpEsValido ( NULL ) != 0 )
	{
		printf( "Error caso 1: un conjunto nulo no deberia ser valido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SCnjpNumElementos ( NULL ) != 0 )
	{
		printf( "Error caso 2: un conjunto nulo deberia tener 0 elementos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SCnjpEstaVacio ( NULL ) != 1 )
	{
		printf( "Error caso 3: un conjunto nulo deberia considerarse vacio\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SConjuntoPtr * p_cnjNulo = NULL;
	SCnjpDestruir ( &p_cnjNulo );
	return ( iRes );
}



int TestSConjuntoPtr ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SConjuntoPtr]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSCnjpOperaciones01 () == BOOL_VAL_CIERTO ) &&
			( TestSCnjpInvalidos01 () == BOOL_VAL_CIERTO ) )
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
