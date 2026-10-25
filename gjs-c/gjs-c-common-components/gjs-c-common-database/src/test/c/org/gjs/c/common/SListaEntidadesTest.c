#include "Base.h"

#include "SListaEntidades.h"



static int IdEs ( SEntidad * p_entObj, unsigned long ulId )
{
	return ( ES_VALIDO ( p_entObj ) && ( SEntValorId ( p_entObj ) == ulId ) );
}

/* Llena la lista con 10, 20, 30, en ese orden. La lista se queda con las entidades. */
static void LlenarLista ( SListaEntidades * p_lisObj )
{
	SLisEntInsertarAlFinal ( p_lisObj, SEntCrear ( 10 ) );
	SLisEntInsertarAlFinal ( p_lisObj, SEntCrear ( 20 ) );
	SLisEntInsertarAlFinal ( p_lisObj, SEntCrear ( 30 ) );
}



static int TestSLisEntCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisEntCrear 01:\n" );
# if ( defined ( MODO_DEPURACION ) )
	unsigned long ulBloquesAntes = MemNumBloquesActuales ();
# endif

	SListaEntidades * p_lisObj = SLisEntCrear ();
	if ( ES_NULO ( p_lisObj ) )
	{
		printf( "Error caso 1: no se esperaba nulo al crear\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SLisEntEsValida ( p_lisObj ) != 1 )
		{
			printf( "Error caso 2: la lista recien creada deberia ser valida\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisEntEstaVacia ( p_lisObj ) != 1 ) || ( SLisEntNumElementos ( p_lisObj ) != 0 ) )
		{
			printf( "Error caso 3: la lista recien creada deberia estar vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	SLisEntDestruir ( &p_lisObj );
	if ( ES_VALIDO ( p_lisObj ) )
	{
		printf( "Error caso 4: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
# if ( defined ( MODO_DEPURACION ) )
	if ( MemNumBloquesActuales () != ulBloquesAntes )
	{
		printf( "Error caso 5: quedan %ld bloques sin liberar\n", (long) ( MemNumBloquesActuales () - ulBloquesAntes ) );
		iRes = BOOL_VAL_FALSO;
	}
# endif
	return ( iRes );
}

static int TestSLisEntInsertar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisEntInsertar 01:\n" );
# if ( defined ( MODO_DEPURACION ) )
	unsigned long ulBloquesAntes = MemNumBloquesActuales ();
# endif

	SListaEntidades * p_lisObj = SLisEntCrear ();
	if ( ES_VALIDO ( p_lisObj ) )
	{
		/* La lista guarda el puntero, sin copiar. */
		SEntidad * p_entVeinte = SEntCrear ( 20 );
		if ( SLisEntInsertarAlFinal ( p_lisObj, p_entVeinte ) != 1 )
		{
			printf( "Error caso 1: se esperaba poder insertar al final\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisEntElemento ( p_lisObj, 0 ) != p_entVeinte )
		{
			printf( "Error caso 2: la lista deberia guardar la misma entidad, no una copia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisEntInsertarAlInicio ( p_lisObj, SEntCrear ( 10 ) );
		SLisEntInsertarAlFinal ( p_lisObj, SEntCrear ( 40 ) );
		/* Tras la posicion 1 ( el 20 ). */
		SLisEntInsertarElem ( p_lisObj, 1, SEntCrear ( 30 ) );

		unsigned long ulEsp [ 4 ] = { 10, 20, 30, 40 };
		int iPos = 0;
		if ( SLisEntNumElementos ( p_lisObj ) != 4 )
		{
			printf( "Error caso 3: se esperaban 4 elementos: %d\n", SLisEntNumElementos ( p_lisObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		while ( ( iPos < 4 ) && ( iRes == BOOL_VAL_CIERTO ) )
		{
			if ( ! IdEs ( SLisEntElemento ( p_lisObj, iPos ), ulEsp [ iPos ] ) )
			{
				printf( "Error caso 4: en la posicion %d se esperaba el id %lu\n", iPos, ulEsp [ iPos ] );
				iRes = BOOL_VAL_FALSO;
			}
			iPos = iPos + 1;
		}
		if ( SLisEntInsertarAlFinal ( p_lisObj, NULL ) != 0 )
		{
			printf( "Error caso 5: insertar una entidad nula deberia devolver 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( SLisEntElemento ( p_lisObj, 4 ) ) || ES_VALIDO ( SLisEntElemento ( p_lisObj, -1 ) ) )
		{
			printf( "Error caso 6: fuera de rango el elemento deberia ser nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la lista\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* Destruir la lista destruye sus entidades. */
	SLisEntDestruir ( &p_lisObj );
# if ( defined ( MODO_DEPURACION ) )
	if ( MemNumBloquesActuales () != ulBloquesAntes )
	{
		printf( "Error caso 7: quedan %ld bloques sin liberar\n", (long) ( MemNumBloquesActuales () - ulBloquesAntes ) );
		iRes = BOOL_VAL_FALSO;
	}
# endif
	return ( iRes );
}

static int TestSLisEntCursor01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisEntCursor 01:\n" );

	SListaEntidades * p_lisObj = SLisEntCrear ();
	if ( ES_VALIDO ( p_lisObj ) )
	{
		LlenarLista ( p_lisObj );

		SLisEntInicio ( p_lisObj );
		if ( ( SLisEntPosicion ( p_lisObj ) != 0 ) || ( ! IdEs ( SLisEntActual ( p_lisObj ), 10 ) ) ||
			 ( SLisEntEstaEnInicio ( p_lisObj ) != 1 ) )
		{
			printf( "Error caso 1: al inicio el actual deberia ser el 10\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisEntSiguiente ( p_lisObj );
		if ( ( SLisEntPosicion ( p_lisObj ) != 1 ) || ( ! IdEs ( SLisEntActual ( p_lisObj ), 20 ) ) )
		{
			printf( "Error caso 2: tras avanzar el actual deberia ser el 20\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisEntFinal ( p_lisObj );
		if ( ( SLisEntPosicion ( p_lisObj ) != 2 ) || ( ! IdEs ( SLisEntActual ( p_lisObj ), 30 ) ) ||
			 ( SLisEntEstaEnFinal ( p_lisObj ) != 1 ) )
		{
			printf( "Error caso 3: al final el actual deberia ser el 30\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisEntAnterior ( p_lisObj );
		if ( ! IdEs ( SLisEntActual ( p_lisObj ), 20 ) )
		{
			printf( "Error caso 4: tras retroceder el actual deberia ser el 20\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisEntMoverA ( p_lisObj, 0 );
		if ( ! IdEs ( SLisEntActual ( p_lisObj ), 10 ) )
		{
			printf( "Error caso 5: tras mover a 0 el actual deberia ser el 10\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Insertar sobre el cursor: detras y delante del actual. */
		if ( SLisEntInsertarDetras ( p_lisObj, SEntCrear ( 15 ) ) != 1 )
		{
			printf( "Error caso 6: se esperaba poder insertar detras del actual\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisEntMoverA ( p_lisObj, 0 );
		if ( SLisEntInsertarDelante ( p_lisObj, SEntCrear ( 5 ) ) != 1 )
		{
			printf( "Error caso 7: se esperaba poder insertar delante del actual\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisEntNumElementos ( p_lisObj ) != 5 ) ||
			 ( ! IdEs ( SLisEntElemento ( p_lisObj, 0 ), 5 ) ) ||
			 ( ! IdEs ( SLisEntElemento ( p_lisObj, 1 ), 10 ) ) ||
			 ( ! IdEs ( SLisEntElemento ( p_lisObj, 2 ), 15 ) ) )
		{
			printf( "Error caso 8: deberian quedar 5, 10, 15, 20 y 30\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Sin posicion: nada es actual y no se puede insertar sobre el cursor. */
		SLisEntDeposicionar ( p_lisObj );
		if ( ( SLisEntEsNulo ( p_lisObj ) != 1 ) || ES_VALIDO ( SLisEntActual ( p_lisObj ) ) )
		{
			printf( "Error caso 9: tras deposicionar no deberia haber actual\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SEntidad * p_entFuera = SEntCrear ( 99 );
		if ( SLisEntInsertarDetras ( p_lisObj, p_entFuera ) != 0 )
		{
			printf( "Error caso 10: sin posicion no deberia poder insertarse sobre el cursor\n" );
			iRes = BOOL_VAL_FALSO;
		}
		else
		{
			/* No se inserto: sigue siendo del test. */
			SEntDestruir ( &p_entFuera );
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la lista\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisEntDestruir ( &p_lisObj );
	return ( iRes );
}

static int TestSLisEntEstablecer01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisEntEstablecer 01:\n" );
# if ( defined ( MODO_DEPURACION ) )
	unsigned long ulBloquesAntes = MemNumBloquesActuales ();
# endif

	SListaEntidades * p_lisObj = SLisEntCrear ();
	if ( ES_VALIDO ( p_lisObj ) )
	{
		LlenarLista ( p_lisObj );

		/* Por indice: la nueva sustituye a la anterior, que la lista destruye. */
		SEntidad * p_entNueva = SEntCrear ( 21 );
		if ( ( SLisEntEstablecerElem ( p_lisObj, 1, p_entNueva ) != 1 ) ||
			 ( SLisEntElemento ( p_lisObj, 1 ) != p_entNueva ) )
		{
			printf( "Error caso 1: la posicion 1 deberia tener la entidad nueva\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Establecer la misma que ya estaba no la destruye. */
		if ( ( SLisEntEstablecerElem ( p_lisObj, 1, p_entNueva ) != 1 ) ||
			 ( ! IdEs ( SLisEntElemento ( p_lisObj, 1 ), 21 ) ) )
		{
			printf( "Error caso 2: establecer la misma entidad no deberia destruirla\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Fuera de rango: no se establece y la entidad sigue siendo del llamador. */
		SEntidad * p_entFuera = SEntCrear ( 99 );
		if ( SLisEntEstablecerElem ( p_lisObj, 3, p_entFuera ) != 0 )
		{
			printf( "Error caso 3: establecer fuera de rango deberia devolver 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
		else
		{
			SEntDestruir ( &p_entFuera );
		}

		/* Sobre el cursor: igual que por indice. */
		SLisEntMoverA ( p_lisObj, 2 );
		p_entNueva = SEntCrear ( 31 );
		if ( ( SLisEntEstablecer ( p_lisObj, p_entNueva ) != 1 ) ||
			 ( SLisEntElemento ( p_lisObj, 2 ) != p_entNueva ) )
		{
			printf( "Error caso 4: el actual deberia ser la entidad nueva\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisEntMoverA ( p_lisObj, 2 );
		if ( ( SLisEntEstablecer ( p_lisObj, p_entNueva ) != 1 ) ||
			 ( ! IdEs ( SLisEntElemento ( p_lisObj, 2 ), 31 ) ) )
		{
			printf( "Error caso 5: establecer la misma entidad no deberia destruirla\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Si falla ( entidad nula ), la actual sigue en la lista y entera. */
		SLisEntMoverA ( p_lisObj, 0 );
		SEntidad * p_entActual = SLisEntActual ( p_lisObj );
		if ( SLisEntEstablecer ( p_lisObj, NULL ) != 0 )
		{
			printf( "Error caso 6: establecer una entidad nula deberia devolver 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisEntElemento ( p_lisObj, 0 ) != p_entActual ) || ( ! IdEs ( p_entActual, 10 ) ) )
		{
			printf( "Error caso 7: si falla, la entidad actual deberia seguir intacta\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisEntNumElementos ( p_lisObj ) != 3 )
		{
			printf( "Error caso 8: establecer no deberia cambiar el numero de elementos\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la lista\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisEntDestruir ( &p_lisObj );
# if ( defined ( MODO_DEPURACION ) )
	/* Las sustituidas se destruyeron al cambiarlas. */
	if ( MemNumBloquesActuales () != ulBloquesAntes )
	{
		printf( "Error caso 9: quedan %ld bloques sin liberar\n", (long) ( MemNumBloquesActuales () - ulBloquesAntes ) );
		iRes = BOOL_VAL_FALSO;
	}
# endif
	return ( iRes );
}

static int TestSLisEntEliminar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisEntEliminar 01:\n" );
# if ( defined ( MODO_DEPURACION ) )
	unsigned long ulBloquesAntes = MemNumBloquesActuales ();
# endif

	SListaEntidades * p_lisObj = SLisEntCrear ();
	if ( ES_VALIDO ( p_lisObj ) )
	{
		LlenarLista ( p_lisObj );

		if ( SLisEntEliminarElem ( p_lisObj, 1 ) != 1 )
		{
			printf( "Error caso 1: se esperaba resultado 1 al eliminar por indice\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisEntNumElementos ( p_lisObj ) != 2 ) ||
			 ( ! IdEs ( SLisEntElemento ( p_lisObj, 0 ), 10 ) ) ||
			 ( ! IdEs ( SLisEntElemento ( p_lisObj, 1 ), 30 ) ) )
		{
			printf( "Error caso 2: tras eliminar deberian quedar el 10 y el 30\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisEntEliminarElem ( p_lisObj, -1 ) != 0 ) || ( SLisEntEliminarElem ( p_lisObj, 2 ) != 0 ) )
		{
			printf( "Error caso 3: eliminar fuera de rango deberia devolver 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Sobre el cursor. */
		SLisEntFinal ( p_lisObj );
		if ( ( SLisEntEliminar ( p_lisObj ) != 1 ) ||
			 ( SLisEntNumElementos ( p_lisObj ) != 1 ) || ( ! IdEs ( SLisEntElemento ( p_lisObj, 0 ), 10 ) ) )
		{
			printf( "Error caso 4: tras eliminar el actual deberia quedar solo el 10\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisEntDeposicionar ( p_lisObj );
		if ( SLisEntEliminar ( p_lisObj ) != 0 )
		{
			printf( "Error caso 5: sin posicion no deberia eliminarse nada\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisEntVaciar ( p_lisObj ) != 1 ) || ( SLisEntEstaVacia ( p_lisObj ) != 1 ) )
		{
			printf( "Error caso 6: tras vaciar la lista deberia estar vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la lista\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisEntDestruir ( &p_lisObj );
# if ( defined ( MODO_DEPURACION ) )
	if ( MemNumBloquesActuales () != ulBloquesAntes )
	{
		printf( "Error caso 7: quedan %ld bloques sin liberar\n", (long) ( MemNumBloquesActuales () - ulBloquesAntes ) );
		iRes = BOOL_VAL_FALSO;
	}
# endif
	return ( iRes );
}

static int TestSLisEntExtraerElem01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisEntExtraerElem 01:\n" );
# if ( defined ( MODO_DEPURACION ) )
	unsigned long ulBloquesAntes = MemNumBloquesActuales ();
# endif

	SListaEntidades * p_lisObj = SLisEntCrear ();
	if ( ES_VALIDO ( p_lisObj ) )
	{
		if ( ES_VALIDO ( SLisEntExtraerElem ( p_lisObj, 0 ) ) )
		{
			printf( "Error caso 1: extraer de una lista vacia deberia devolver nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		LlenarLista ( p_lisObj );

		/* Sale la misma entidad, viva; desde ahora es del llamador. */
		SEntidad * p_entEsp = SLisEntElemento ( p_lisObj, 1 );
		SEntidad * p_entExt = SLisEntExtraerElem ( p_lisObj, 1 );
		if ( ES_NULO ( p_entExt ) || ( p_entExt != p_entEsp ) || ( ! IdEs ( p_entExt, 20 ) ) )
		{
			printf( "Error caso 2: se esperaba extraer el 20 de la posicion 1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisEntNumElementos ( p_lisObj ) != 2 ) || ( SLisEntExisteValorId ( p_lisObj, 20 ) != 0 ) )
		{
			printf( "Error caso 3: tras extraer el 20 ya no deberia estar en la lista\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( SLisEntExtraerElem ( p_lisObj, -1 ) ) || ES_VALIDO ( SLisEntExtraerElem ( p_lisObj, 2 ) ) )
		{
			printf( "Error caso 4: extraer fuera de rango deberia devolver nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisEntNumElementos ( p_lisObj ) != 2 )
		{
			printf( "Error caso 5: extraer fuera de rango no deberia cambiar la lista\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Se puede devolver a la lista, que la toma otra vez. */
		if ( ES_VALIDO ( p_entExt ) )
		{
			if ( SLisEntInsertarAlFinal ( p_lisObj, p_entExt ) != 1 )
			{
				printf( "Error caso 6: la entidad extraida deberia poder volver a insertarse\n" );
				iRes = BOOL_VAL_FALSO;
				SEntDestruir ( &p_entExt );
			}
		}
		/* Una extraida que no se devuelve la destruye el llamador. */
		p_entExt = SLisEntExtraerElem ( p_lisObj, 0 );
		if ( ! IdEs ( p_entExt, 10 ) )
		{
			printf( "Error caso 7: extraer la posicion 0 deberia dar el 10\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SEntDestruir ( &p_entExt );
		if ( ES_VALIDO ( SLisEntExtraerElem ( NULL, 0 ) ) )
		{
			printf( "Error caso 8: extraer de una lista nula deberia devolver nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la lista\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisEntDestruir ( &p_lisObj );
# if ( defined ( MODO_DEPURACION ) )
	if ( MemNumBloquesActuales () != ulBloquesAntes )
	{
		printf( "Error caso 9: quedan %ld bloques sin liberar\n", (long) ( MemNumBloquesActuales () - ulBloquesAntes ) );
		iRes = BOOL_VAL_FALSO;
	}
# endif
	return ( iRes );
}

static int TestSLisEntBuscar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisEntBuscar 01:\n" );
# if ( defined ( MODO_DEPURACION ) )
	unsigned long ulBloquesAntes = MemNumBloquesActuales ();
# endif

	SListaEntidades * p_lisObj = SLisEntCrear ();
	SEntidad * p_entBuscar = SEntCrear ( 20 );
	SId * p_idBuscar = SIdCrear ( 30 );
	if ( ES_VALIDO ( p_lisObj ) && ES_VALIDO ( p_entBuscar ) && ES_VALIDO ( p_idBuscar ) )
	{
		LlenarLista ( p_lisObj );

		/* Por identificador: la entidad buscada no es ninguna de las de la lista. */
		if ( ( SLisEntExiste ( p_lisObj, p_entBuscar ) != 1 ) || ( SLisEntBuscar ( p_lisObj, p_entBuscar ) != 1 ) )
		{
			printf( "Error caso 1: la entidad 20 deberia estar en la posicion 1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisEntExisteId ( p_lisObj, p_idBuscar ) != 1 ) || ( SLisEntBuscarId ( p_lisObj, p_idBuscar ) != 2 ) )
		{
			printf( "Error caso 2: el id 30 deberia estar en la posicion 2\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisEntExisteValorId ( p_lisObj, 10 ) != 1 ) || ( SLisEntBuscarValorId ( p_lisObj, 10 ) != 0 ) )
		{
			printf( "Error caso 3: el valor 10 deberia estar en la posicion 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Lo que no esta. */
		SEntEstablecerValorId ( p_entBuscar, 99 );
		SIdEstablecer ( p_idBuscar, 99 );
		if ( ( SLisEntExiste ( p_lisObj, p_entBuscar ) != 0 ) || ( SLisEntBuscar ( p_lisObj, p_entBuscar ) != -1 ) ||
			 ( SLisEntExisteId ( p_lisObj, p_idBuscar ) != 0 ) || ( SLisEntBuscarId ( p_lisObj, p_idBuscar ) != -1 ) ||
			 ( SLisEntExisteValorId ( p_lisObj, 99 ) != 0 ) || ( SLisEntBuscarValorId ( p_lisObj, 99 ) != -1 ) )
		{
			printf( "Error caso 4: el 99 no deberia encontrarse\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* El id 0 no es un identificador asignado: nunca se encuentra. */
		if ( ( SLisEntExisteValorId ( p_lisObj, 0 ) != 0 ) || ( SLisEntBuscarValorId ( p_lisObj, 0 ) != -1 ) )
		{
			printf( "Error caso 5: el id 0 no deberia encontrarse\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Nulos: "no esta" es -1, no 0, que seria la primera posicion. */
		if ( ( SLisEntExiste ( p_lisObj, NULL ) != 0 ) || ( SLisEntBuscar ( p_lisObj, NULL ) != -1 ) ||
			 ( SLisEntExisteId ( p_lisObj, NULL ) != 0 ) || ( SLisEntBuscarId ( p_lisObj, NULL ) != -1 ) )
		{
			printf( "Error caso 6: con un dato nulo no deberia encontrarse nada\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisEntBuscar ( NULL, p_entBuscar ) != -1 ) || ( SLisEntBuscarValorId ( NULL, 10 ) != -1 ) )
		{
			printf( "Error caso 7: en una lista nula buscar deberia devolver -1\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear la lista o los datos de busqueda\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisEntDestruir ( &p_lisObj );
	SEntDestruir ( &p_entBuscar );
	SIdDestruir ( &p_idBuscar );
# if ( defined ( MODO_DEPURACION ) )
	if ( MemNumBloquesActuales () != ulBloquesAntes )
	{
		printf( "Error caso 8: quedan %ld bloques sin liberar\n", (long) ( MemNumBloquesActuales () - ulBloquesAntes ) );
		iRes = BOOL_VAL_FALSO;
	}
# endif
	return ( iRes );
}

static int TestSLisEntInvalidos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisEntInvalidos 01:\n" );

	if ( ( SLisEntEsValida ( NULL ) != 0 ) || ( SLisEntNumElementos ( NULL ) != 0 ) || ( SLisEntEstaVacia ( NULL ) != 1 ) )
	{
		printf( "Error caso 1: una lista nula no es valida, tiene 0 elementos y esta vacia\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( SLisEntElemento ( NULL, 0 ) ) || ES_VALIDO ( SLisEntActual ( NULL ) ) || ( SLisEntPosicion ( NULL ) != -1 ) )
	{
		printf( "Error caso 2: una lista nula no tiene elementos ni posicion\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ( SLisEntEliminarElem ( NULL, 0 ) != 0 ) || ( SLisEntEliminar ( NULL ) != 0 ) || ( SLisEntVaciar ( NULL ) != 0 ) )
	{
		printf( "Error caso 3: eliminar o vaciar una lista nula deberia devolver 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* El cursor sobre una lista nula no hace nada. */
	SLisEntInicio ( NULL );
	SLisEntFinal ( NULL );
	SLisEntSiguiente ( NULL );
	SLisEntAnterior ( NULL );
	SLisEntMoverA ( NULL, 0 );
	SLisEntDeposicionar ( NULL );
	SListaEntidades * p_lisNula = NULL;
	SLisEntDestruir ( &p_lisNula );
	SLisEntDestruir ( NULL );
	return ( iRes );
}



int TestSListaEntidades ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SListaEntidades]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSLisEntCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisEntInsertar01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisEntCursor01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisEntEstablecer01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisEntEliminar01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisEntExtraerElem01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisEntBuscar01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisEntInvalidos01 () == BOOL_VAL_CIERTO ) )
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
