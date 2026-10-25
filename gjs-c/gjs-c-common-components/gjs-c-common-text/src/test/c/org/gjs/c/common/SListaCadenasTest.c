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



static int TestSLisCadEstablecer01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisCadEstablecer 01:\n" );
# if ( defined ( MODO_DEPURACION ) )
	unsigned long ulBloquesAntes = MemNumBloquesActuales ();
# endif

	SListaCadenas * p_lisObj = SLisCadCrear ();
	if ( ES_VALIDO ( p_lisObj ) )
	{
		SLisCadInsertarAlFinal ( p_lisObj, SCadGenerar ( "uno" ) );
		SLisCadInsertarAlFinal ( p_lisObj, SCadGenerar ( "dos" ) );
		SLisCadInsertarAlFinal ( p_lisObj, SCadGenerar ( "tres" ) );

		/* Por indice: la nueva sustituye a la anterior, que la lista destruye. */
		SCadena * p_cadNueva = SCadGenerar ( "DOS" );
		if ( ( SLisCadEstablecerElem ( p_lisObj, 1, p_cadNueva ) != 1 ) ||
			 ( SLisCadElemento ( p_lisObj, 1 ) != p_cadNueva ) )
		{
			printf( "Error caso 1: la posicion 1 deberia tener la cadena nueva\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Establecer la misma que ya estaba no la destruye. */
		if ( ( SLisCadEstablecerElem ( p_lisObj, 1, p_cadNueva ) != 1 ) ||
			 ( SCadEsIgualLiteral ( SLisCadElemento ( p_lisObj, 1 ), "DOS" ) != 1 ) )
		{
			printf( "Error caso 2: establecer la misma cadena no deberia destruirla\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Sobre el cursor: igual que por indice. */
		SLisCadMoverA ( p_lisObj, 2 );
		p_cadNueva = SCadGenerar ( "TRES" );
		if ( ( SLisCadEstablecer ( p_lisObj, p_cadNueva ) != 1 ) ||
			 ( SLisCadElemento ( p_lisObj, 2 ) != p_cadNueva ) )
		{
			printf( "Error caso 3: el actual deberia ser la cadena nueva\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisCadMoverA ( p_lisObj, 2 );
		if ( ( SLisCadEstablecer ( p_lisObj, p_cadNueva ) != 1 ) ||
			 ( SCadEsIgualLiteral ( SLisCadElemento ( p_lisObj, 2 ), "TRES" ) != 1 ) )
		{
			printf( "Error caso 4: establecer la misma cadena no deberia destruirla\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Si falla ( cadena nula ), la actual sigue en la lista y entera. */
		SLisCadMoverA ( p_lisObj, 0 );
		SCadena * p_cadActual = SLisCadActual ( p_lisObj );
		if ( SLisCadEstablecer ( p_lisObj, NULL ) != 0 )
		{
			printf( "Error caso 5: establecer una cadena nula deberia devolver 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisCadElemento ( p_lisObj, 0 ) != p_cadActual ) ||
			 ( SCadEsIgualLiteral ( p_cadActual, "uno" ) != 1 ) )
		{
			printf( "Error caso 6: si falla, la cadena actual deberia seguir intacta\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la lista\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisCadDestruir ( &p_lisObj );
# if ( defined ( MODO_DEPURACION ) )
	/* Las sustituidas se destruyeron al cambiarlas. */
	if ( MemNumBloquesActuales () != ulBloquesAntes )
	{
		printf( "Error caso 7: quedan %ld bloques sin liberar\n", (long) ( MemNumBloquesActuales () - ulBloquesAntes ) );
		iRes = BOOL_VAL_FALSO;
	}
# endif
	return ( iRes );
}

static int TestSLisCadExtraerElem01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisCadExtraerElem 01:\n" );

	SListaCadenas * p_lisObj = SLisCadCrear ();
	if ( ES_VALIDO ( p_lisObj ) )
	{
		/* Lista vacia: no hay nada que extraer. */
		if ( ES_VALIDO ( SLisCadExtraerElem ( p_lisObj, 0 ) ) )
		{
			printf( "Error caso 1: extraer de una lista vacia deberia devolver nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisCadInsertarAlFinal ( p_lisObj, SCadGenerar ( "uno" ) );
		SLisCadInsertarAlFinal ( p_lisObj, SCadGenerar ( "dos" ) );
		SLisCadInsertarAlFinal ( p_lisObj, SCadGenerar ( "tres" ) );
		SLisCadInsertarAlFinal ( p_lisObj, SCadGenerar ( "cuatro" ) );

		/* Se extrae la misma cadena que habia, no una copia, y sigue viva. */
		SCadena * p_cadEsp = SLisCadElemento ( p_lisObj, 1 );
		SCadena * p_cadExt = SLisCadExtraerElem ( p_lisObj, 1 );
		if ( ES_NULO ( p_cadExt ) || ( p_cadExt != p_cadEsp ) )
		{
			printf( "Error caso 2: se esperaba extraer la cadena de la posicion 1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCadEsIgualLiteral ( p_cadExt, "dos" ) != 1 )
		{
			printf( "Error caso 3: la cadena extraida deberia seguir valiendo \"dos\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisCadNumElementos ( p_lisObj ) != 3 ) ||
			 ( SCadEsIgualLiteral ( SLisCadElemento ( p_lisObj, 0 ), "uno" ) != 1 ) ||
			 ( SCadEsIgualLiteral ( SLisCadElemento ( p_lisObj, 1 ), "tres" ) != 1 ) ||
			 ( SCadEsIgualLiteral ( SLisCadElemento ( p_lisObj, 2 ), "cuatro" ) != 1 ) )
		{
			printf( "Error caso 4: tras extraer deberian quedar \"uno\", \"tres\" y \"cuatro\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* La extraida es ya del llamador. */
		SCadDestruir ( &p_cadExt );

		/* Los extremos. */
		p_cadExt = SLisCadExtraerElem ( p_lisObj, 0 );
		if ( SCadEsIgualLiteral ( p_cadExt, "uno" ) != 1 )
		{
			printf( "Error caso 5: extraer la posicion 0 deberia dar \"uno\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SCadDestruir ( &p_cadExt );
		p_cadExt = SLisCadExtraerElem ( p_lisObj, SLisCadNumElementos ( p_lisObj ) - 1 );
		if ( SCadEsIgualLiteral ( p_cadExt, "cuatro" ) != 1 )
		{
			printf( "Error caso 6: extraer la ultima posicion deberia dar \"cuatro\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SCadDestruir ( &p_cadExt );
		if ( ( SLisCadNumElementos ( p_lisObj ) != 1 ) ||
			 ( SCadEsIgualLiteral ( SLisCadElemento ( p_lisObj, 0 ), "tres" ) != 1 ) )
		{
			printf( "Error caso 7: deberia quedar solo \"tres\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Posiciones fuera de rango: nulo, y la lista no cambia. */
		if ( ES_VALIDO ( SLisCadExtraerElem ( p_lisObj, -1 ) ) || ES_VALIDO ( SLisCadExtraerElem ( p_lisObj, 1 ) ) )
		{
			printf( "Error caso 8: extraer fuera de rango deberia devolver nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisCadNumElementos ( p_lisObj ) != 1 )
		{
			printf( "Error caso 9: extraer fuera de rango no deberia cambiar la lista\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* La extraida se puede volver a insertar: la lista la toma de nuevo. */
		p_cadExt = SLisCadExtraerElem ( p_lisObj, 0 );
		if ( ( SLisCadEstaVacia ( p_lisObj ) != 1 ) || ( SLisCadInsertarAlFinal ( p_lisObj, p_cadExt ) != 1 ) )
		{
			printf( "Error caso 10: la cadena extraida deberia poder volver a insertarse\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( SLisCadExtraerElem ( NULL, 0 ) ) )
		{
			printf( "Error caso 11: extraer de una lista nula deberia devolver nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la lista\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisCadDestruir ( &p_lisObj );
	return ( iRes );
}



int TestSListaCadenas ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SListaCadenas]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSLisCadCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisCadInsertar01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisCadCursor01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisCadEstablecer01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisCadExtraerElem01 () == BOOL_VAL_CIERTO ) )
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
