#include "Base.h"

#include "SListaCadenas.h"



static int TestSLisCadCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisCadCrear 01:\n" );

	SListaCadenas * p_lisObj = SLisCadCrear ();
	if ( ES_NULO ( p_lisObj ) )
	{
		printf( "Error caso 1: no se esperaba nulo al crear\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SLisCadEsValida ( p_lisObj ) != 1 )
		{
			printf( "Error caso 2: la lista recien creada deberia ser valida\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisCadEstaVacia ( p_lisObj ) != 1 )
		{
			printf( "Error caso 3: la lista recien creada deberia estar vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisCadNumElementos ( p_lisObj ) != 0 )
		{
			printf( "Error caso 4: el numero de elementos deberia ser 0: %d\n", SLisCadNumElementos ( p_lisObj ) );
			iRes = BOOL_VAL_FALSO;
		}
	}
	SLisCadDestruir ( &p_lisObj );

	if ( ES_VALIDO ( p_lisObj ) )
	{
		printf( "Error caso 5: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSLisCadInsertar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisCadInsertar 01:\n" );

	SListaCadenas * p_lisObj = SLisCadCrear ();
	SCadena * p_cadUno = SCadGenerar ( "uno" );
	SCadena * p_cadDos = SCadGenerar ( "dos" );
	SCadena * p_cadTres = SCadGenerar ( "tres" );
	if ( ES_VALIDO ( p_lisObj ) && ES_VALIDO ( p_cadUno ) &&
			ES_VALIDO ( p_cadDos ) && ES_VALIDO ( p_cadTres ) )
	{
		/* Se insertan duplicados: la lista gestiona sus propias copias. */
		SLisCadInsertarDupAlFinal ( p_lisObj, p_cadUno );
		SLisCadInsertarDupAlFinal ( p_lisObj, p_cadDos );
		SLisCadInsertarDupAlFinal ( p_lisObj, p_cadTres );

		if ( SLisCadNumElementos ( p_lisObj ) != 3 )
		{
			printf( "Error caso 1: se esperaban 3 elementos: %d\n", SLisCadNumElementos ( p_lisObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisCadEstaVacia ( p_lisObj ) != 0 )
		{
			printf( "Error caso 2: la lista no deberia estar vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCadEsIgualLiteral ( SLisCadElemento ( p_lisObj, 0 ), "uno" ) != 1 )
		{
			printf( "Error caso 3: el elemento 0 deberia ser \"uno\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCadEsIgualLiteral ( SLisCadElemento ( p_lisObj, 2 ), "tres" ) != 1 )
		{
			printf( "Error caso 4: el elemento 2 deberia ser \"tres\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Busquedas. */
		if ( SLisCadBuscarExt ( p_lisObj, "dos" ) != 1 )
		{
			printf( "Error caso 5: \"dos\" deberia estar en la posicion 1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisCadBuscarExt ( p_lisObj, "cuatro" ) != -1 )
		{
			printf( "Error caso 6: \"cuatro\" no deberia encontrarse\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisCadExiste ( p_lisObj, p_cadTres ) != 1 )
		{
			printf( "Error caso 7: \"tres\" deberia existir en la lista\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Vaciar. */
		SLisCadVaciar ( p_lisObj );
		if ( SLisCadNumElementos ( p_lisObj ) != 0 )
		{
			printf( "Error caso 8: la lista deberia quedar vacia tras vaciarla\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear la lista o las cadenas\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisCadDestruir ( &p_lisObj );
	SCadDestruir ( &p_cadUno );
	SCadDestruir ( &p_cadDos );
	SCadDestruir ( &p_cadTres );
	return ( iRes );
}

static int TestSLisCadCursor01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisCadCursor 01:\n" );

	SListaCadenas * p_lisObj = SLisCadCrear ();
	SCadena * p_cadUno = SCadGenerar ( "uno" );
	SCadena * p_cadDos = SCadGenerar ( "dos" );
	if ( ES_VALIDO ( p_lisObj ) && ES_VALIDO ( p_cadUno ) && ES_VALIDO ( p_cadDos ) )
	{
		SLisCadInsertarDupAlFinal ( p_lisObj, p_cadUno );
		SLisCadInsertarDupAlFinal ( p_lisObj, p_cadDos );

		SLisCadInicio ( p_lisObj );
		if ( SCadEsIgualLiteral ( SLisCadActual ( p_lisObj ), "uno" ) != 1 )
		{
			printf( "Error caso 1: el actual al inicio deberia ser \"uno\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisCadSiguiente ( p_lisObj );
		if ( SCadEsIgualLiteral ( SLisCadActual ( p_lisObj ), "dos" ) != 1 )
		{
			printf( "Error caso 2: el siguiente deberia ser \"dos\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear la lista o las cadenas\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisCadDestruir ( &p_lisObj );
	SCadDestruir ( &p_cadUno );
	SCadDestruir ( &p_cadDos );
	return ( iRes );
}



int TestSListaCadenas ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SListaCadenas]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSLisCadCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisCadInsertar01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisCadCursor01 () == BOOL_VAL_CIERTO ) )
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
