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

static int TestSCnjpPrimeroUltimo01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCnjpPrimeroUltimo 01:\n" );

	/* La memoria de los datos la gestiona el test ( liberacion desactivada ). */
	byte * p_d10 = CrearDatoEntero ( 10 );
	byte * p_d20 = CrearDatoEntero ( 20 );
	byte * p_d30 = CrearDatoEntero ( 30 );
	SConjuntoPtr * p_cnjObj = SCnjpCrear ( CompararEnteros );
	if ( ES_VALIDO ( p_cnjObj ) && ES_VALIDO ( p_d10 ) && ES_VALIDO ( p_d20 ) && ES_VALIDO ( p_d30 ) )
	{
		SCnjpDesactivarLiberacionMemoria ( p_cnjObj );

		/* Vacio: no hay ni primero ni ultimo. */
		if ( ES_VALIDO ( SCnjpPrimero ( p_cnjObj ) ) )
		{
			printf( "Error caso 1: el primero de un conjunto vacio deberia ser nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( SCnjpUltimo ( p_cnjObj ) ) )
		{
			printf( "Error caso 2: el ultimo de un conjunto vacio deberia ser nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Con un solo elemento, primero y ultimo son el mismo puntero. */
		SCnjpInsertarElem ( p_cnjObj, p_d20 );
		if ( SCnjpPrimero ( p_cnjObj ) != p_d20 )
		{
			printf( "Error caso 3: con un elemento, el primero deberia ser el 20\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCnjpUltimo ( p_cnjObj ) != p_d20 )
		{
			printf( "Error caso 4: con un elemento, el ultimo deberia ser el 20\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Se insertan por fuera de los extremos: primero y ultimo siguen el orden, no la insercion. */
		SCnjpInsertarElem ( p_cnjObj, p_d30 );
		SCnjpInsertarElem ( p_cnjObj, p_d10 );
		if ( SCnjpPrimero ( p_cnjObj ) != p_d10 )
		{
			printf( "Error caso 5: el primero deberia ser el 10\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCnjpUltimo ( p_cnjObj ) != p_d30 )
		{
			printf( "Error caso 6: el ultimo deberia ser el 30\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Tras eliminar el ultimo, el nuevo ultimo es el 20. */
		SCnjpEliminarElem ( p_cnjObj, 2 );
		if ( SCnjpUltimo ( p_cnjObj ) != p_d20 )
		{
			printf( "Error caso 7: tras eliminar el 30, el ultimo deberia ser el 20\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( SCnjpPrimero ( NULL ) ) || ES_VALIDO ( SCnjpUltimo ( NULL ) ) )
		{
			printf( "Error caso 8: primero y ultimo de un conjunto nulo deberian ser nulos\n" );
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
	MemLiberar ( (void **) &p_d10 );
	MemLiberar ( (void **) &p_d20 );
	MemLiberar ( (void **) &p_d30 );
	return ( iRes );
}

static int TestSCnjpPosicion01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCnjpPosicion 01:\n" );

	/* La memoria de los datos la gestiona el test ( liberacion desactivada ). */
	byte * p_d10 = CrearDatoEntero ( 10 );
	byte * p_d20 = CrearDatoEntero ( 20 );
	byte * p_d30 = CrearDatoEntero ( 30 );
	byte * p_q20 = CrearDatoEntero ( 20 );
	byte * p_q = CrearDatoEntero ( 0 );
	SConjuntoPtr * p_cnjObj = SCnjpCrear ( CompararEnteros );
	if ( ES_VALIDO ( p_cnjObj ) && ES_VALIDO ( p_d10 ) && ES_VALIDO ( p_d20 ) && ES_VALIDO ( p_d30 ) &&
		 ES_VALIDO ( p_q20 ) && ES_VALIDO ( p_q ) )
	{
		SCnjpDesactivarLiberacionMemoria ( p_cnjObj );

		/* Vacio: nada tiene posicion. */
		if ( SCnjpPosicion ( p_cnjObj, p_d20 ) != -1 )
		{
			printf( "Error caso 1: en un conjunto vacio la posicion deberia ser -1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SCnjpInsertarElem ( p_cnjObj, p_d30 );
		SCnjpInsertarElem ( p_cnjObj, p_d10 );
		SCnjpInsertarElem ( p_cnjObj, p_d20 );

		if ( ( SCnjpPosicion ( p_cnjObj, p_d10 ) != 0 ) ||
			 ( SCnjpPosicion ( p_cnjObj, p_d20 ) != 1 ) ||
			 ( SCnjpPosicion ( p_cnjObj, p_d30 ) != 2 ) )
		{
			printf( "Error caso 2: 10, 20 y 30 deberian estar en las posiciones 0, 1 y 2\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Posicion por valor: otro puntero con el mismo dato da la misma posicion. */
		if ( SCnjpPosicion ( p_cnjObj, p_q20 ) != 1 )
		{
			printf( "Error caso 3: un 20 en otro puntero deberia dar la posicion 1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SCnjpPosicion ( p_cnjObj, SCnjpPrimero ( p_cnjObj ) ) != 0 ) ||
			 ( SCnjpPosicion ( p_cnjObj, SCnjpUltimo ( p_cnjObj ) ) != 2 ) )
		{
			printf( "Error caso 4: el primero y el ultimo deberian estar en las posiciones 0 y 2\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Valores que no estan: menor que el minimo, intermedio y mayor que el maximo. */
		*( (int *) p_q ) = 5;
		if ( SCnjpPosicion ( p_cnjObj, p_q ) != -1 )
		{
			printf( "Error caso 5: el 5 no deberia tener posicion\n" );
			iRes = BOOL_VAL_FALSO;
		}
		*( (int *) p_q ) = 15;
		if ( SCnjpPosicion ( p_cnjObj, p_q ) != -1 )
		{
			printf( "Error caso 6: el 15 no deberia tener posicion\n" );
			iRes = BOOL_VAL_FALSO;
		}
		*( (int *) p_q ) = 99;
		if ( SCnjpPosicion ( p_cnjObj, p_q ) != -1 )
		{
			printf( "Error caso 7: el 99 no deberia tener posicion\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCnjpPosicion ( p_cnjObj, NULL ) != -1 )
		{
			printf( "Error caso 8: un dato nulo no deberia tener posicion\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCnjpPosicion ( NULL, p_d20 ) != -1 )
		{
			printf( "Error caso 9: en un conjunto nulo la posicion deberia ser -1\n" );
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
	MemLiberar ( (void **) &p_d10 );
	MemLiberar ( (void **) &p_d20 );
	MemLiberar ( (void **) &p_d30 );
	MemLiberar ( (void **) &p_q20 );
	MemLiberar ( (void **) &p_q );
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
			( TestSCnjpPrimeroUltimo01 () == BOOL_VAL_CIERTO ) &&
			( TestSCnjpPosicion01 () == BOOL_VAL_CIERTO ) &&
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
