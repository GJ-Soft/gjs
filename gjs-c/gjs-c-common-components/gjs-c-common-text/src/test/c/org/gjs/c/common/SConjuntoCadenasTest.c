#include "Base.h"

#include "SConjuntoCadenas.h"



static int ElementoEs ( SConjuntoCadenas * p_cnjObj, int iElem, const char * p_cEsperado )
{
	return ( SCadEsIgualLiteral ( SCnjCadElemento ( p_cnjObj, iElem ), p_cEsperado ) == 1 );
}

/* Inserta copias de las tres cadenas en desorden: quedan apple, banana, cherry. */
static void LlenarConjunto ( SConjuntoCadenas * p_cnjObj )
{
	SCadena * p_cadObj;

	p_cadObj = SCadGenerar ( "banana" );
	SCnjCadInsertarDup ( p_cnjObj, p_cadObj );
	SCadDestruir ( &p_cadObj );
	p_cadObj = SCadGenerar ( "cherry" );
	SCnjCadInsertarDup ( p_cnjObj, p_cadObj );
	SCadDestruir ( &p_cadObj );
	p_cadObj = SCadGenerar ( "apple" );
	SCnjCadInsertarDup ( p_cnjObj, p_cadObj );
	SCadDestruir ( &p_cadObj );
}



static int TestSCnjCadCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCnjCadCrear 01:\n" );

	SConjuntoCadenas * p_cnjObj = SCnjCadCrear ();
	if ( ES_NULO ( p_cnjObj ) )
	{
		printf( "Error caso 1: no se esperaba nulo al crear\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SCnjCadEsValido ( p_cnjObj ) != 1 )
		{
			printf( "Error caso 2: el conjunto recien creado deberia ser valido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCnjCadEstaVacio ( p_cnjObj ) != 1 )
		{
			printf( "Error caso 3: el conjunto recien creado deberia estar vacio\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCnjCadNumElementos ( p_cnjObj ) != 0 )
		{
			printf( "Error caso 4: el numero de elementos deberia ser 0: %d\n", SCnjCadNumElementos ( p_cnjObj ) );
			iRes = BOOL_VAL_FALSO;
		}
	}
	SCnjCadDestruir ( &p_cnjObj );

	if ( ES_VALIDO ( p_cnjObj ) )
	{
		printf( "Error caso 5: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSCnjCadInsertar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCnjCadInsertar 01:\n" );

	/* SCnjCadInsertar se queda con la cadena: el test no destruye las insertadas. */
	SConjuntoCadenas * p_cnjObj = SCnjCadCrear ();
	SCadena * p_cadBanana = SCadGenerar ( "banana" );
	SCadena * p_cadApple = SCadGenerar ( "apple" );
	SCadena * p_cadCherry = SCadGenerar ( "cherry" );
	SCadena * p_cadDup = SCadGenerar ( "apple" );
	if ( ES_VALIDO ( p_cnjObj ) && ES_VALIDO ( p_cadBanana ) && ES_VALIDO ( p_cadApple ) &&
			ES_VALIDO ( p_cadCherry ) && ES_VALIDO ( p_cadDup ) )
	{
		/* Se insertan en desorden; el conjunto los mantiene ordenados. */
		if ( ( SCnjCadInsertar ( p_cnjObj, p_cadBanana ) != 1 ) ||
			 ( SCnjCadInsertar ( p_cnjObj, p_cadApple ) != 1 ) ||
			 ( SCnjCadInsertar ( p_cnjObj, p_cadCherry ) != 1 ) )
		{
			printf( "Error caso 1: se esperaba poder insertar las tres cadenas\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCnjCadNumElementos ( p_cnjObj ) != 3 )
		{
			printf( "Error caso 2: se esperaban 3 elementos: %d\n", SCnjCadNumElementos ( p_cnjObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( ! ElementoEs ( p_cnjObj, 0, "apple" ) ) ||
			 ( ! ElementoEs ( p_cnjObj, 1, "banana" ) ) ||
			 ( ! ElementoEs ( p_cnjObj, 2, "cherry" ) ) )
		{
			printf( "Error caso 3: los elementos deberian estar en orden alfabetico\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Sin copia: el elemento es la misma cadena que se inserto. */
		if ( SCnjCadElemento ( p_cnjObj, 0 ) != p_cadApple )
		{
			printf( "Error caso 4: SCnjCadInsertar no deberia copiar la cadena\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Un valor ya presente se rechaza, y la cadena sigue siendo del llamador. */
		if ( SCnjCadInsertar ( p_cnjObj, p_cadDup ) != -1 )
		{
			printf( "Error caso 5: insertar un valor duplicado deberia devolver -1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCnjCadNumElementos ( p_cnjObj ) != 3 )
		{
			printf( "Error caso 6: el conjunto no deberia crecer con un duplicado\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCadEsIgualLiteral ( p_cadDup, "apple" ) != 1 )
		{
			printf( "Error caso 7: la cadena rechazada deberia seguir intacta\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCnjCadInsertar ( p_cnjObj, NULL ) != -1 )
		{
			printf( "Error caso 8: insertar una cadena nula deberia devolver -1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SCadDestruir ( &p_cadDup );
		SCnjCadDestruir ( &p_cnjObj );
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear el conjunto o las cadenas\n" );
		iRes = BOOL_VAL_FALSO;
		SCnjCadDestruir ( &p_cnjObj );
		SCadDestruir ( &p_cadBanana );
		SCadDestruir ( &p_cadApple );
		SCadDestruir ( &p_cadCherry );
		SCadDestruir ( &p_cadDup );
	}
	return ( iRes );
}

static int TestSCnjCadInsertarDup01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCnjCadInsertarDup 01:\n" );

	SConjuntoCadenas * p_cnjObj = SCnjCadCrear ();
	SCadena * p_cadObj = SCadGenerar ( "banana" );
	if ( ES_VALIDO ( p_cnjObj ) && ES_VALIDO ( p_cadObj ) )
	{
		if ( SCnjCadInsertarDup ( p_cnjObj, p_cadObj ) != 1 )
		{
			printf( "Error caso 1: se esperaba resultado 1 al insertar una copia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Se guarda una copia: otro puntero con el mismo valor. */
		SCadena * p_cadElem = SCnjCadElemento ( p_cnjObj, 0 );
		if ( ES_NULO ( p_cadElem ) || ( p_cadElem == p_cadObj ) )
		{
			printf( "Error caso 2: SCnjCadInsertarDup deberia guardar una copia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ! ElementoEs ( p_cnjObj, 0, "banana" ) )
		{
			printf( "Error caso 3: la copia deberia valer \"banana\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* La copia rechazada se libera dentro; el conjunto no crece. */
		if ( SCnjCadInsertarDup ( p_cnjObj, p_cadObj ) == 1 )
		{
			printf( "Error caso 4: insertar un valor duplicado no deberia tener exito\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCnjCadNumElementos ( p_cnjObj ) != 1 )
		{
			printf( "Error caso 5: el conjunto no deberia crecer con un duplicado\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Cambiar la original no toca la copia del conjunto. */
		SCadAsignarLiteral ( p_cadObj, "zzz" );
		if ( ! ElementoEs ( p_cnjObj, 0, "banana" ) )
		{
			printf( "Error caso 6: la copia no deberia cambiar al cambiar la original\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCnjCadInsertarDup ( p_cnjObj, NULL ) != -1 )
		{
			printf( "Error caso 7: insertar una cadena nula deberia devolver -1\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear el conjunto o la cadena\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SCnjCadDestruir ( &p_cnjObj );
	SCadDestruir ( &p_cadObj );
	return ( iRes );
}

static int TestSCnjCadPrimeroUltimo01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCnjCadPrimeroUltimo 01:\n" );

	SConjuntoCadenas * p_cnjObj = SCnjCadCrear ();
	if ( ES_VALIDO ( p_cnjObj ) )
	{
		/* Vacio: no hay ni primero ni ultimo. */
		if ( ES_VALIDO ( SCnjCadPrimero ( p_cnjObj ) ) || ES_VALIDO ( SCnjCadUltimo ( p_cnjObj ) ) )
		{
			printf( "Error caso 1: primero y ultimo de un conjunto vacio deberian ser nulos\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Con un solo elemento, primero y ultimo son la misma cadena. */
		SCnjCadInsertar ( p_cnjObj, SCadGenerar ( "banana" ) );
		if ( SCadEsIgualLiteral ( SCnjCadPrimero ( p_cnjObj ), "banana" ) != 1 )
		{
			printf( "Error caso 2: con un elemento, el primero deberia ser \"banana\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCnjCadUltimo ( p_cnjObj ) != SCnjCadPrimero ( p_cnjObj ) )
		{
			printf( "Error caso 3: con un elemento, el ultimo deberia ser el mismo que el primero\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Se insertan por fuera de los extremos: primero y ultimo siguen el orden alfabetico. */
		SCnjCadInsertar ( p_cnjObj, SCadGenerar ( "cherry" ) );
		SCnjCadInsertar ( p_cnjObj, SCadGenerar ( "apple" ) );
		if ( SCadEsIgualLiteral ( SCnjCadPrimero ( p_cnjObj ), "apple" ) != 1 )
		{
			printf( "Error caso 4: el primero deberia ser \"apple\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCadEsIgualLiteral ( SCnjCadUltimo ( p_cnjObj ), "cherry" ) != 1 )
		{
			printf( "Error caso 5: el ultimo deberia ser \"cherry\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( SCnjCadPrimero ( NULL ) ) || ES_VALIDO ( SCnjCadUltimo ( NULL ) ) )
		{
			printf( "Error caso 6: primero y ultimo de un conjunto nulo deberian ser nulos\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el conjunto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SCnjCadDestruir ( &p_cnjObj );
	return ( iRes );
}

static int TestSCnjCadBuscar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCnjCadBuscar 01:\n" );

	SConjuntoCadenas * p_cnjObj = SCnjCadCrear ();
	SCadena * p_cadBuscar = SCadGenerar ( "banana" );
	if ( ES_VALIDO ( p_cnjObj ) && ES_VALIDO ( p_cadBuscar ) )
	{
		/* Vacio: nada existe ni tiene posicion. */
		if ( ( SCnjCadExiste ( p_cnjObj, p_cadBuscar ) != 0 ) ||
			 ( SCnjCadBuscar ( p_cnjObj, p_cadBuscar ) != -1 ) ||
			 ( SCnjCadPosicion ( p_cnjObj, p_cadBuscar ) != -1 ) )
		{
			printf( "Error caso 1: en un conjunto vacio no deberia encontrarse nada\n" );
			iRes = BOOL_VAL_FALSO;
		}
		LlenarConjunto ( p_cnjObj );

		/* Busqueda por valor: p_cadBuscar no es ninguna de las cadenas del conjunto. */
		if ( SCnjCadExiste ( p_cnjObj, p_cadBuscar ) != 1 )
		{
			printf( "Error caso 2: \"banana\" deberia existir\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCnjCadBuscar ( p_cnjObj, p_cadBuscar ) != 1 )
		{
			printf( "Error caso 3: buscar \"banana\" deberia devolver el indice 1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCnjCadPosicion ( p_cnjObj, p_cadBuscar ) != 1 )
		{
			printf( "Error caso 4: la posicion de \"banana\" deberia ser 1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SCnjCadPosicion ( p_cnjObj, SCnjCadPrimero ( p_cnjObj ) ) != 0 ) ||
			 ( SCnjCadPosicion ( p_cnjObj, SCnjCadUltimo ( p_cnjObj ) ) != 2 ) )
		{
			printf( "Error caso 5: el primero y el ultimo deberian estar en las posiciones 0 y 2\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Valores que no estan: menor que el minimo, intermedio, prefijo y mayor que el maximo. */
		const char * p_cAusentes [ 4 ] = { "aaa", "blueberry", "ban", "grape" };
		int iAus = 0;
		while ( iAus < 4 )
		{
			SCadena * p_cadAus = SCadGenerar ( p_cAusentes [ iAus ] );
			if ( ( SCnjCadExiste ( p_cnjObj, p_cadAus ) != 0 ) ||
				 ( SCnjCadBuscar ( p_cnjObj, p_cadAus ) != -1 ) ||
				 ( SCnjCadPosicion ( p_cnjObj, p_cadAus ) != -1 ) )
			{
				printf( "Error caso 6: \"%s\" no deberia encontrarse\n", p_cAusentes [ iAus ] );
				iRes = BOOL_VAL_FALSO;
			}
			SCadDestruir ( &p_cadAus );
			iAus = iAus + 1;
		}
		if ( ( SCnjCadExiste ( p_cnjObj, NULL ) != 0 ) ||
			 ( SCnjCadBuscar ( p_cnjObj, NULL ) != -1 ) ||
			 ( SCnjCadPosicion ( p_cnjObj, NULL ) != -1 ) )
		{
			printf( "Error caso 7: una cadena nula no deberia encontrarse\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear el conjunto o la cadena\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SCnjCadDestruir ( &p_cnjObj );
	SCadDestruir ( &p_cadBuscar );
	return ( iRes );
}

static int TestSCnjCadEliminar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCnjCadEliminar 01:\n" );

	SConjuntoCadenas * p_cnjObj = SCnjCadCrear ();
	if ( ES_VALIDO ( p_cnjObj ) )
	{
		LlenarConjunto ( p_cnjObj );

		/* Eliminar el del medio ( "banana" ). */
		if ( SCnjCadEliminar ( p_cnjObj, 1 ) != 1 )
		{
			printf( "Error caso 1: se esperaba resultado 1 al eliminar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SCnjCadNumElementos ( p_cnjObj ) != 2 ) ||
			 ( ! ElementoEs ( p_cnjObj, 0, "apple" ) ) ||
			 ( ! ElementoEs ( p_cnjObj, 1, "cherry" ) ) )
		{
			printf( "Error caso 2: tras eliminar deberian quedar \"apple\" y \"cherry\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Posiciones fuera de rango: no se elimina nada. */
		if ( ( SCnjCadEliminar ( p_cnjObj, -1 ) != 0 ) || ( SCnjCadEliminar ( p_cnjObj, 2 ) != 0 ) )
		{
			printf( "Error caso 3: eliminar fuera de rango deberia devolver 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCnjCadNumElementos ( p_cnjObj ) != 2 )
		{
			printf( "Error caso 4: eliminar fuera de rango no deberia cambiar el conjunto\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* El valor eliminado se puede volver a insertar. */
		SCadena * p_cadObj = SCadGenerar ( "banana" );
		if ( SCnjCadInsertarDup ( p_cnjObj, p_cadObj ) != 1 )
		{
			printf( "Error caso 5: se esperaba poder reinsertar \"banana\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SCadDestruir ( &p_cadObj );

		if ( SCnjCadVaciar ( p_cnjObj ) != 1 )
		{
			printf( "Error caso 6: se esperaba resultado 1 al vaciar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCnjCadEstaVacio ( p_cnjObj ) != 1 )
		{
			printf( "Error caso 7: tras vaciar el conjunto deberia estar vacio\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Tras vaciar sigue siendo utilizable. */
		LlenarConjunto ( p_cnjObj );
		if ( SCnjCadNumElementos ( p_cnjObj ) != 3 )
		{
			printf( "Error caso 8: tras vaciar deberia poder llenarse de nuevo\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el conjunto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SCnjCadDestruir ( &p_cnjObj );
	return ( iRes );
}

static int TestSCnjCadExtraer01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCnjCadExtraer 01:\n" );

	SConjuntoCadenas * p_cnjObj = SCnjCadCrear ();
	if ( ES_VALIDO ( p_cnjObj ) )
	{
		/* Conjunto vacio: no hay nada que extraer. */
		if ( ES_VALIDO ( SCnjCadExtraer ( p_cnjObj, 0 ) ) )
		{
			printf( "Error caso 1: extraer de un conjunto vacio deberia devolver nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		LlenarConjunto ( p_cnjObj );

		/* Se extrae la misma cadena que habia, no una copia, y sigue viva. */
		SCadena * p_cadEsp = SCnjCadElemento ( p_cnjObj, 1 );
		SCadena * p_cadExt = SCnjCadExtraer ( p_cnjObj, 1 );
		if ( ES_NULO ( p_cadExt ) || ( p_cadExt != p_cadEsp ) )
		{
			printf( "Error caso 2: se esperaba extraer la cadena de la posicion 1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCadEsIgualLiteral ( p_cadExt, "banana" ) != 1 )
		{
			printf( "Error caso 3: la cadena extraida deberia seguir valiendo \"banana\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SCnjCadNumElementos ( p_cnjObj ) != 2 ) ||
			 ( ! ElementoEs ( p_cnjObj, 0, "apple" ) ) ||
			 ( ! ElementoEs ( p_cnjObj, 1, "cherry" ) ) )
		{
			printf( "Error caso 4: tras extraer deberian quedar \"apple\" y \"cherry\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCnjCadExiste ( p_cnjObj, p_cadExt ) != 0 )
		{
			printf( "Error caso 5: la cadena extraida ya no deberia estar en el conjunto\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Posiciones fuera de rango: nulo, y el conjunto no cambia. */
		if ( ES_VALIDO ( SCnjCadExtraer ( p_cnjObj, -1 ) ) || ES_VALIDO ( SCnjCadExtraer ( p_cnjObj, 2 ) ) )
		{
			printf( "Error caso 6: extraer fuera de rango deberia devolver nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCnjCadNumElementos ( p_cnjObj ) != 2 )
		{
			printf( "Error caso 7: extraer fuera de rango no deberia cambiar el conjunto\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* La extraida se puede volver a insertar: el conjunto la toma de nuevo. */
		if ( SCnjCadInsertar ( p_cnjObj, p_cadExt ) != 1 )
		{
			printf( "Error caso 8: la cadena extraida deberia poder volver a insertarse\n" );
			iRes = BOOL_VAL_FALSO;
			SCadDestruir ( &p_cadExt );
		}
		else if ( SCnjCadElemento ( p_cnjObj, 1 ) != p_cadExt )
		{
			printf( "Error caso 9: al reinsertarla deberia volver a la posicion 1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Los extremos; las extraidas son ya del llamador. */
		p_cadExt = SCnjCadExtraer ( p_cnjObj, 0 );
		if ( SCadEsIgualLiteral ( p_cadExt, "apple" ) != 1 )
		{
			printf( "Error caso 10: extraer la posicion 0 deberia dar \"apple\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SCadDestruir ( &p_cadExt );
		p_cadExt = SCnjCadExtraer ( p_cnjObj, SCnjCadNumElementos ( p_cnjObj ) - 1 );
		if ( SCadEsIgualLiteral ( p_cadExt, "cherry" ) != 1 )
		{
			printf( "Error caso 11: extraer la ultima posicion deberia dar \"cherry\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SCadDestruir ( &p_cadExt );
		if ( ( SCnjCadNumElementos ( p_cnjObj ) != 1 ) || ( ! ElementoEs ( p_cnjObj, 0, "banana" ) ) )
		{
			printf( "Error caso 12: deberia quedar solo \"banana\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( SCnjCadExtraer ( NULL, 0 ) ) )
		{
			printf( "Error caso 13: extraer de un conjunto nulo deberia devolver nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el conjunto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SCnjCadDestruir ( &p_cnjObj );
	return ( iRes );
}

static int TestSCnjCadInvalidos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCnjCadInvalidos 01:\n" );

	SCadena * p_cadObj = SCadGenerar ( "banana" );
	if ( SCnjCadEsValido ( NULL ) != 0 )
	{
		printf( "Error caso 1: un conjunto nulo no deberia ser valido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SCnjCadNumElementos ( NULL ) != 0 )
	{
		printf( "Error caso 2: un conjunto nulo deberia tener 0 elementos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SCnjCadEstaVacio ( NULL ) != 1 )
	{
		printf( "Error caso 3: un conjunto nulo deberia considerarse vacio\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( SCnjCadElemento ( NULL, 0 ) ) )
	{
		printf( "Error caso 4: el elemento de un conjunto nulo deberia ser nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ( SCnjCadInsertar ( NULL, p_cadObj ) != -1 ) || ( SCnjCadInsertarDup ( NULL, p_cadObj ) != -1 ) )
	{
		printf( "Error caso 5: insertar en un conjunto nulo deberia devolver -1\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ( SCnjCadEliminar ( NULL, 0 ) != 0 ) || ( SCnjCadVaciar ( NULL ) != 0 ) )
	{
		printf( "Error caso 6: eliminar o vaciar un conjunto nulo deberia devolver 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ( SCnjCadExiste ( NULL, p_cadObj ) != 0 ) ||
		 ( SCnjCadBuscar ( NULL, p_cadObj ) != -1 ) ||
		 ( SCnjCadPosicion ( NULL, p_cadObj ) != -1 ) )
	{
		printf( "Error caso 7: en un conjunto nulo no deberia encontrarse nada\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SConjuntoCadenas * p_cnjNulo = NULL;
	SCnjCadDestruir ( &p_cnjNulo );
	SCnjCadDestruir ( NULL );
	SCadDestruir ( &p_cadObj );
	return ( iRes );
}



int TestSConjuntoCadenas ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SConjuntoCadenas]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSCnjCadCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSCnjCadInsertar01 () == BOOL_VAL_CIERTO ) &&
			( TestSCnjCadInsertarDup01 () == BOOL_VAL_CIERTO ) &&
			( TestSCnjCadPrimeroUltimo01 () == BOOL_VAL_CIERTO ) &&
			( TestSCnjCadBuscar01 () == BOOL_VAL_CIERTO ) &&
			( TestSCnjCadEliminar01 () == BOOL_VAL_CIERTO ) &&
			( TestSCnjCadExtraer01 () == BOOL_VAL_CIERTO ) &&
			( TestSCnjCadInvalidos01 () == BOOL_VAL_CIERTO ) )
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
