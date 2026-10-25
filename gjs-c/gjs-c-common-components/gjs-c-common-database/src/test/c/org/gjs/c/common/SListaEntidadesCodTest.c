#include "Base.h"

#include "SListaEntidadesCod.h"



#define TAM_CODIGO		10

static SEntidadCod * CrearEntidad ( const char * p_cCodigo )
{
	return ( SEntCodCrearLit ( p_cCodigo, TAM_CODIGO ) );
}

static int CodigoEs ( SEntidadCod * p_entcObj, const char * p_cCodigo )
{
	return ( SEntCodEsIgualLit ( p_entcObj, p_cCodigo ) == 1 );
}

/* Llena la lista con ALFA, BETA, GAMMA, en ese orden. La lista se queda con las entidades. */
static void LlenarLista ( SListaEntidadesCod * p_lisObj )
{
	SLisEntCodInsertarAlFinal ( p_lisObj, CrearEntidad ( "ALFA" ) );
	SLisEntCodInsertarAlFinal ( p_lisObj, CrearEntidad ( "BETA" ) );
	SLisEntCodInsertarAlFinal ( p_lisObj, CrearEntidad ( "GAMMA" ) );
}



static int TestSLisEntCodCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisEntCodCrear 01:\n" );
# if ( defined ( MODO_DEPURACION ) )
	unsigned long ulBloquesAntes = MemNumBloquesActuales ();
# endif

	SListaEntidadesCod * p_lisObj = SLisEntCodCrear ();
	if ( ES_NULO ( p_lisObj ) )
	{
		printf( "Error caso 1: no se esperaba nulo al crear\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SLisEntCodEsValida ( p_lisObj ) != 1 )
		{
			printf( "Error caso 2: la lista recien creada deberia ser valida\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisEntCodEstaVacia ( p_lisObj ) != 1 ) || ( SLisEntCodNumElementos ( p_lisObj ) != 0 ) )
		{
			printf( "Error caso 3: la lista recien creada deberia estar vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	SLisEntCodDestruir ( &p_lisObj );
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

static int TestSLisEntCodInsertar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisEntCodInsertar 01:\n" );
# if ( defined ( MODO_DEPURACION ) )
	unsigned long ulBloquesAntes = MemNumBloquesActuales ();
# endif

	SListaEntidadesCod * p_lisObj = SLisEntCodCrear ();
	if ( ES_VALIDO ( p_lisObj ) )
	{
		/* La lista guarda el puntero, sin copiar, y respeta el orden de insercion. */
		SEntidadCod * p_entcBeta = CrearEntidad ( "BETA" );
		if ( SLisEntCodInsertarAlFinal ( p_lisObj, p_entcBeta ) != 1 )
		{
			printf( "Error caso 1: se esperaba poder insertar al final\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisEntCodElemento ( p_lisObj, 0 ) != p_entcBeta )
		{
			printf( "Error caso 2: la lista deberia guardar la misma entidad, no una copia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisEntCodInsertarAlInicio ( p_lisObj, CrearEntidad ( "ALFA" ) );
		SLisEntCodInsertarAlFinal ( p_lisObj, CrearEntidad ( "DELTA" ) );
		/* Tras la posicion 1 ( BETA ). */
		SLisEntCodInsertarElem ( p_lisObj, 1, CrearEntidad ( "GAMMA" ) );
		/* La lista no ordena ni rechaza repetidos. */
		SLisEntCodInsertarAlFinal ( p_lisObj, CrearEntidad ( "ALFA" ) );

		const char * p_cEsp [ 5 ] = { "ALFA", "BETA", "GAMMA", "DELTA", "ALFA" };
		int iPos = 0;
		if ( SLisEntCodNumElementos ( p_lisObj ) != 5 )
		{
			printf( "Error caso 3: se esperaban 5 elementos: %d\n", SLisEntCodNumElementos ( p_lisObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		while ( ( iPos < 5 ) && ( iRes == BOOL_VAL_CIERTO ) )
		{
			if ( ! CodigoEs ( SLisEntCodElemento ( p_lisObj, iPos ), p_cEsp [ iPos ] ) )
			{
				printf( "Error caso 4: en la posicion %d se esperaba \"%s\"\n", iPos, p_cEsp [ iPos ] );
				iRes = BOOL_VAL_FALSO;
			}
			iPos = iPos + 1;
		}
		if ( SLisEntCodInsertarAlFinal ( p_lisObj, NULL ) != 0 )
		{
			printf( "Error caso 5: insertar una entidad nula deberia devolver 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( SLisEntCodElemento ( p_lisObj, 5 ) ) || ES_VALIDO ( SLisEntCodElemento ( p_lisObj, -1 ) ) )
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
	SLisEntCodDestruir ( &p_lisObj );
# if ( defined ( MODO_DEPURACION ) )
	if ( MemNumBloquesActuales () != ulBloquesAntes )
	{
		printf( "Error caso 7: quedan %ld bloques sin liberar\n", (long) ( MemNumBloquesActuales () - ulBloquesAntes ) );
		iRes = BOOL_VAL_FALSO;
	}
# endif
	return ( iRes );
}

static int TestSLisEntCodCursor01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisEntCodCursor 01:\n" );

	SListaEntidadesCod * p_lisObj = SLisEntCodCrear ();
	if ( ES_VALIDO ( p_lisObj ) )
	{
		LlenarLista ( p_lisObj );

		SLisEntCodInicio ( p_lisObj );
		if ( ( SLisEntCodPosicion ( p_lisObj ) != 0 ) || ( ! CodigoEs ( SLisEntCodActual ( p_lisObj ), "ALFA" ) ) ||
			 ( SLisEntCodEstaEnInicio ( p_lisObj ) != 1 ) )
		{
			printf( "Error caso 1: al inicio el actual deberia ser ALFA\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisEntCodSiguiente ( p_lisObj );
		if ( ( SLisEntCodPosicion ( p_lisObj ) != 1 ) || ( ! CodigoEs ( SLisEntCodActual ( p_lisObj ), "BETA" ) ) )
		{
			printf( "Error caso 2: tras avanzar el actual deberia ser BETA\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisEntCodFinal ( p_lisObj );
		if ( ( SLisEntCodPosicion ( p_lisObj ) != 2 ) || ( ! CodigoEs ( SLisEntCodActual ( p_lisObj ), "GAMMA" ) ) ||
			 ( SLisEntCodEstaEnFinal ( p_lisObj ) != 1 ) )
		{
			printf( "Error caso 3: al final el actual deberia ser GAMMA\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisEntCodAnterior ( p_lisObj );
		if ( ! CodigoEs ( SLisEntCodActual ( p_lisObj ), "BETA" ) )
		{
			printf( "Error caso 4: tras retroceder el actual deberia ser BETA\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Insertar sobre el cursor: detras y delante del actual. */
		SLisEntCodMoverA ( p_lisObj, 0 );
		if ( SLisEntCodInsertarDetras ( p_lisObj, CrearEntidad ( "ALFA2" ) ) != 1 )
		{
			printf( "Error caso 5: se esperaba poder insertar detras del actual\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisEntCodMoverA ( p_lisObj, 0 );
		if ( SLisEntCodInsertarDelante ( p_lisObj, CrearEntidad ( "ALFA0" ) ) != 1 )
		{
			printf( "Error caso 6: se esperaba poder insertar delante del actual\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisEntCodNumElementos ( p_lisObj ) != 5 ) ||
			 ( ! CodigoEs ( SLisEntCodElemento ( p_lisObj, 0 ), "ALFA0" ) ) ||
			 ( ! CodigoEs ( SLisEntCodElemento ( p_lisObj, 1 ), "ALFA" ) ) ||
			 ( ! CodigoEs ( SLisEntCodElemento ( p_lisObj, 2 ), "ALFA2" ) ) )
		{
			printf( "Error caso 7: deberian quedar ALFA0, ALFA, ALFA2, BETA y GAMMA\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Sin posicion: nada es actual y no se puede insertar sobre el cursor. */
		SLisEntCodDeposicionar ( p_lisObj );
		if ( ( SLisEntCodEsNulo ( p_lisObj ) != 1 ) || ES_VALIDO ( SLisEntCodActual ( p_lisObj ) ) )
		{
			printf( "Error caso 8: tras deposicionar no deberia haber actual\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SEntidadCod * p_entcFuera = CrearEntidad ( "ZETA" );
		if ( SLisEntCodInsertarDetras ( p_lisObj, p_entcFuera ) != 0 )
		{
			printf( "Error caso 9: sin posicion no deberia poder insertarse sobre el cursor\n" );
			iRes = BOOL_VAL_FALSO;
		}
		else
		{
			/* No se inserto: sigue siendo del test. */
			SEntCodDestruir ( &p_entcFuera );
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la lista\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisEntCodDestruir ( &p_lisObj );
	return ( iRes );
}

static int TestSLisEntCodEstablecer01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisEntCodEstablecer 01:\n" );
# if ( defined ( MODO_DEPURACION ) )
	unsigned long ulBloquesAntes = MemNumBloquesActuales ();
# endif

	SListaEntidadesCod * p_lisObj = SLisEntCodCrear ();
	if ( ES_VALIDO ( p_lisObj ) )
	{
		LlenarLista ( p_lisObj );

		/* Por indice: la nueva sustituye a la anterior, que la lista destruye. */
		SEntidadCod * p_entcNueva = CrearEntidad ( "BETA2" );
		if ( ( SLisEntCodEstablecerElem ( p_lisObj, 1, p_entcNueva ) != 1 ) ||
			 ( SLisEntCodElemento ( p_lisObj, 1 ) != p_entcNueva ) )
		{
			printf( "Error caso 1: la posicion 1 deberia tener la entidad nueva\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Establecer la misma que ya estaba no la destruye. */
		if ( ( SLisEntCodEstablecerElem ( p_lisObj, 1, p_entcNueva ) != 1 ) ||
			 ( ! CodigoEs ( SLisEntCodElemento ( p_lisObj, 1 ), "BETA2" ) ) )
		{
			printf( "Error caso 2: establecer la misma entidad no deberia destruirla\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Fuera de rango: no se establece y la entidad sigue siendo del llamador. */
		SEntidadCod * p_entcFuera = CrearEntidad ( "ZETA" );
		if ( SLisEntCodEstablecerElem ( p_lisObj, 3, p_entcFuera ) != 0 )
		{
			printf( "Error caso 3: establecer fuera de rango deberia devolver 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
		else
		{
			SEntCodDestruir ( &p_entcFuera );
		}

		/* Sobre el cursor: igual que por indice. */
		SLisEntCodMoverA ( p_lisObj, 2 );
		p_entcNueva = CrearEntidad ( "GAMMA2" );
		if ( ( SLisEntCodEstablecer ( p_lisObj, p_entcNueva ) != 1 ) ||
			 ( SLisEntCodElemento ( p_lisObj, 2 ) != p_entcNueva ) )
		{
			printf( "Error caso 4: el actual deberia ser la entidad nueva\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisEntCodMoverA ( p_lisObj, 2 );
		if ( ( SLisEntCodEstablecer ( p_lisObj, p_entcNueva ) != 1 ) ||
			 ( ! CodigoEs ( SLisEntCodElemento ( p_lisObj, 2 ), "GAMMA2" ) ) )
		{
			printf( "Error caso 5: establecer la misma entidad no deberia destruirla\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Si falla ( entidad nula ), la actual sigue en la lista y entera. */
		SLisEntCodMoverA ( p_lisObj, 0 );
		SEntidadCod * p_entcActual = SLisEntCodActual ( p_lisObj );
		if ( SLisEntCodEstablecer ( p_lisObj, NULL ) != 0 )
		{
			printf( "Error caso 6: establecer una entidad nula deberia devolver 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisEntCodElemento ( p_lisObj, 0 ) != p_entcActual ) || ( ! CodigoEs ( p_entcActual, "ALFA" ) ) )
		{
			printf( "Error caso 7: si falla, la entidad actual deberia seguir intacta\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisEntCodNumElementos ( p_lisObj ) != 3 )
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
	SLisEntCodDestruir ( &p_lisObj );
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

static int TestSLisEntCodEliminar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisEntCodEliminar 01:\n" );
# if ( defined ( MODO_DEPURACION ) )
	unsigned long ulBloquesAntes = MemNumBloquesActuales ();
# endif

	SListaEntidadesCod * p_lisObj = SLisEntCodCrear ();
	if ( ES_VALIDO ( p_lisObj ) )
	{
		LlenarLista ( p_lisObj );

		if ( SLisEntCodEliminarElem ( p_lisObj, 1 ) != 1 )
		{
			printf( "Error caso 1: se esperaba resultado 1 al eliminar por indice\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisEntCodNumElementos ( p_lisObj ) != 2 ) ||
			 ( ! CodigoEs ( SLisEntCodElemento ( p_lisObj, 0 ), "ALFA" ) ) ||
			 ( ! CodigoEs ( SLisEntCodElemento ( p_lisObj, 1 ), "GAMMA" ) ) )
		{
			printf( "Error caso 2: tras eliminar deberian quedar ALFA y GAMMA\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisEntCodEliminarElem ( p_lisObj, -1 ) != 0 ) || ( SLisEntCodEliminarElem ( p_lisObj, 2 ) != 0 ) )
		{
			printf( "Error caso 3: eliminar fuera de rango deberia devolver 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Sobre el cursor. */
		SLisEntCodFinal ( p_lisObj );
		if ( ( SLisEntCodEliminar ( p_lisObj ) != 1 ) ||
			 ( SLisEntCodNumElementos ( p_lisObj ) != 1 ) || ( ! CodigoEs ( SLisEntCodElemento ( p_lisObj, 0 ), "ALFA" ) ) )
		{
			printf( "Error caso 4: tras eliminar el actual deberia quedar solo ALFA\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisEntCodDeposicionar ( p_lisObj );
		if ( SLisEntCodEliminar ( p_lisObj ) != 0 )
		{
			printf( "Error caso 5: sin posicion no deberia eliminarse nada\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisEntCodVaciar ( p_lisObj ) != 1 ) || ( SLisEntCodEstaVacia ( p_lisObj ) != 1 ) )
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
	SLisEntCodDestruir ( &p_lisObj );
# if ( defined ( MODO_DEPURACION ) )
	if ( MemNumBloquesActuales () != ulBloquesAntes )
	{
		printf( "Error caso 7: quedan %ld bloques sin liberar\n", (long) ( MemNumBloquesActuales () - ulBloquesAntes ) );
		iRes = BOOL_VAL_FALSO;
	}
# endif
	return ( iRes );
}

static int TestSLisEntCodExtraerElem01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisEntCodExtraerElem 01:\n" );
# if ( defined ( MODO_DEPURACION ) )
	unsigned long ulBloquesAntes = MemNumBloquesActuales ();
# endif

	SListaEntidadesCod * p_lisObj = SLisEntCodCrear ();
	if ( ES_VALIDO ( p_lisObj ) )
	{
		if ( ES_VALIDO ( SLisEntCodExtraerElem ( p_lisObj, 0 ) ) )
		{
			printf( "Error caso 1: extraer de una lista vacia deberia devolver nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		LlenarLista ( p_lisObj );

		/* Sale la misma entidad, viva; desde ahora es del llamador. */
		SEntidadCod * p_entcEsp = SLisEntCodElemento ( p_lisObj, 1 );
		SEntidadCod * p_entcExt = SLisEntCodExtraerElem ( p_lisObj, 1 );
		if ( ES_NULO ( p_entcExt ) || ( p_entcExt != p_entcEsp ) || ( ! CodigoEs ( p_entcExt, "BETA" ) ) )
		{
			printf( "Error caso 2: se esperaba extraer BETA de la posicion 1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisEntCodNumElementos ( p_lisObj ) != 2 ) || ( SLisEntCodExisteValorCodigoLit ( p_lisObj, "BETA" ) != 0 ) )
		{
			printf( "Error caso 3: tras extraer BETA ya no deberia estar en la lista\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( SLisEntCodExtraerElem ( p_lisObj, -1 ) ) || ES_VALIDO ( SLisEntCodExtraerElem ( p_lisObj, 2 ) ) )
		{
			printf( "Error caso 4: extraer fuera de rango deberia devolver nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisEntCodNumElementos ( p_lisObj ) != 2 )
		{
			printf( "Error caso 5: extraer fuera de rango no deberia cambiar la lista\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Se puede devolver a la lista, que la toma otra vez. */
		if ( ES_VALIDO ( p_entcExt ) )
		{
			if ( SLisEntCodInsertarAlFinal ( p_lisObj, p_entcExt ) != 1 )
			{
				printf( "Error caso 6: la entidad extraida deberia poder volver a insertarse\n" );
				iRes = BOOL_VAL_FALSO;
				SEntCodDestruir ( &p_entcExt );
			}
		}
		/* Una extraida que no se devuelve la destruye el llamador. */
		p_entcExt = SLisEntCodExtraerElem ( p_lisObj, 0 );
		if ( ! CodigoEs ( p_entcExt, "ALFA" ) )
		{
			printf( "Error caso 7: extraer la posicion 0 deberia dar ALFA\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SEntCodDestruir ( &p_entcExt );
		if ( ES_VALIDO ( SLisEntCodExtraerElem ( NULL, 0 ) ) )
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
	SLisEntCodDestruir ( &p_lisObj );
# if ( defined ( MODO_DEPURACION ) )
	if ( MemNumBloquesActuales () != ulBloquesAntes )
	{
		printf( "Error caso 9: quedan %ld bloques sin liberar\n", (long) ( MemNumBloquesActuales () - ulBloquesAntes ) );
		iRes = BOOL_VAL_FALSO;
	}
# endif
	return ( iRes );
}

static int TestSLisEntCodBuscar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisEntCodBuscar 01:\n" );
# if ( defined ( MODO_DEPURACION ) )
	unsigned long ulBloquesAntes = MemNumBloquesActuales ();
# endif

	SListaEntidadesCod * p_lisObj = SLisEntCodCrear ();
	SEntidadCod * p_entcBuscar = CrearEntidad ( "BETA" );
	SCodigo * p_codBuscar = SCodCrearValorLit ( "GAMMA" );
	SCadena * p_cadBuscar = SCadGenerar ( "ALFA" );
	if ( ES_VALIDO ( p_lisObj ) && ES_VALIDO ( p_entcBuscar ) && ES_VALIDO ( p_codBuscar ) && ES_VALIDO ( p_cadBuscar ) )
	{
		LlenarLista ( p_lisObj );

		/* Por codigo: lo buscado no es ninguna de las entidades de la lista. */
		if ( ( SLisEntCodExiste ( p_lisObj, p_entcBuscar ) != 1 ) || ( SLisEntCodBuscar ( p_lisObj, p_entcBuscar ) != 1 ) )
		{
			printf( "Error caso 1: la entidad BETA deberia estar en la posicion 1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisEntCodExisteCodigo ( p_lisObj, p_codBuscar ) != 1 ) || ( SLisEntCodBuscarCodigo ( p_lisObj, p_codBuscar ) != 2 ) )
		{
			printf( "Error caso 2: el codigo GAMMA deberia estar en la posicion 2\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisEntCodExisteValorCodigo ( p_lisObj, p_cadBuscar ) != 1 ) ||
			 ( SLisEntCodBuscarValorCodigo ( p_lisObj, p_cadBuscar ) != 0 ) )
		{
			printf( "Error caso 3: la cadena ALFA deberia estar en la posicion 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisEntCodExisteValorCodigoLit ( p_lisObj, "GAMMA" ) != 1 ) ||
			 ( SLisEntCodBuscarValorCodigoLit ( p_lisObj, "GAMMA" ) != 2 ) )
		{
			printf( "Error caso 4: el literal GAMMA deberia estar en la posicion 2\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Lo que no esta: menor, intermedio, mayor y un prefijo. */
		const char * p_cAusentes [ 4 ] = { "AAA", "BAAA", "ZETA", "ALF" };
		int iAus = 0;
		while ( iAus < 4 )
		{
			SEntidadCod * p_entcAus = CrearEntidad ( p_cAusentes [ iAus ] );
			SCodigo * p_codAus = SCodCrearValorLit ( p_cAusentes [ iAus ] );
			SCadena * p_cadAus = SCadGenerar ( p_cAusentes [ iAus ] );
			if ( ES_NULO ( p_entcAus ) || ES_NULO ( p_codAus ) || ES_NULO ( p_cadAus ) )
			{
				printf( "Error caso 5: no se pudieron crear las sondas de \"%s\"\n", p_cAusentes [ iAus ] );
				iRes = BOOL_VAL_FALSO;
			}
			else if ( ( SLisEntCodExiste ( p_lisObj, p_entcAus ) != 0 ) || ( SLisEntCodBuscar ( p_lisObj, p_entcAus ) != -1 ) ||
					  ( SLisEntCodExisteCodigo ( p_lisObj, p_codAus ) != 0 ) || ( SLisEntCodBuscarCodigo ( p_lisObj, p_codAus ) != -1 ) ||
					  ( SLisEntCodExisteValorCodigo ( p_lisObj, p_cadAus ) != 0 ) ||
					  ( SLisEntCodBuscarValorCodigo ( p_lisObj, p_cadAus ) != -1 ) ||
					  ( SLisEntCodExisteValorCodigoLit ( p_lisObj, p_cAusentes [ iAus ] ) != 0 ) ||
					  ( SLisEntCodBuscarValorCodigoLit ( p_lisObj, p_cAusentes [ iAus ] ) != -1 ) )
			{
				printf( "Error caso 5: \"%s\" no deberia encontrarse\n", p_cAusentes [ iAus ] );
				iRes = BOOL_VAL_FALSO;
			}
			SEntCodDestruir ( &p_entcAus );
			SCodDestruir ( &p_codAus );
			SCadDestruir ( &p_cadAus );
			iAus = iAus + 1;
		}
		/* Literales que no son codigos validos: nunca se encuentran. */
		const char * p_cNoValidos [ 3 ] = { "", "1ABC", "AB-C" };
		int iNoVal = 0;
		while ( iNoVal < 3 )
		{
			if ( ( SLisEntCodExisteValorCodigoLit ( p_lisObj, p_cNoValidos [ iNoVal ] ) != 0 ) ||
				 ( SLisEntCodBuscarValorCodigoLit ( p_lisObj, p_cNoValidos [ iNoVal ] ) != -1 ) )
			{
				printf( "Error caso 6: \"%s\" no deberia encontrarse\n", p_cNoValidos [ iNoVal ] );
				iRes = BOOL_VAL_FALSO;
			}
			iNoVal = iNoVal + 1;
		}
		/* Nulos: "no esta" es -1, no 0, que seria la primera posicion. */
		if ( ( SLisEntCodExiste ( p_lisObj, NULL ) != 0 ) || ( SLisEntCodBuscar ( p_lisObj, NULL ) != -1 ) ||
			 ( SLisEntCodExisteCodigo ( p_lisObj, NULL ) != 0 ) || ( SLisEntCodBuscarCodigo ( p_lisObj, NULL ) != -1 ) ||
			 ( SLisEntCodExisteValorCodigo ( p_lisObj, NULL ) != 0 ) || ( SLisEntCodBuscarValorCodigo ( p_lisObj, NULL ) != -1 ) ||
			 ( SLisEntCodExisteValorCodigoLit ( p_lisObj, NULL ) != 0 ) || ( SLisEntCodBuscarValorCodigoLit ( p_lisObj, NULL ) != -1 ) )
		{
			printf( "Error caso 7: con un dato nulo no deberia encontrarse nada\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisEntCodBuscar ( NULL, p_entcBuscar ) != -1 ) || ( SLisEntCodBuscarValorCodigoLit ( NULL, "ALFA" ) != -1 ) )
		{
			printf( "Error caso 8: en una lista nula buscar deberia devolver -1\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear la lista o los datos de busqueda\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisEntCodDestruir ( &p_lisObj );
	SEntCodDestruir ( &p_entcBuscar );
	SCodDestruir ( &p_codBuscar );
	SCadDestruir ( &p_cadBuscar );
# if ( defined ( MODO_DEPURACION ) )
	if ( MemNumBloquesActuales () != ulBloquesAntes )
	{
		printf( "Error caso 9: quedan %ld bloques sin liberar\n", (long) ( MemNumBloquesActuales () - ulBloquesAntes ) );
		iRes = BOOL_VAL_FALSO;
	}
# endif
	return ( iRes );
}

static int TestSLisEntCodInvalidos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisEntCodInvalidos 01:\n" );

	if ( ( SLisEntCodEsValida ( NULL ) != 0 ) || ( SLisEntCodNumElementos ( NULL ) != 0 ) || ( SLisEntCodEstaVacia ( NULL ) != 1 ) )
	{
		printf( "Error caso 1: una lista nula no es valida, tiene 0 elementos y esta vacia\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( SLisEntCodElemento ( NULL, 0 ) ) || ES_VALIDO ( SLisEntCodActual ( NULL ) ) || ( SLisEntCodPosicion ( NULL ) != -1 ) )
	{
		printf( "Error caso 2: una lista nula no tiene elementos ni posicion\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ( SLisEntCodEliminarElem ( NULL, 0 ) != 0 ) || ( SLisEntCodEliminar ( NULL ) != 0 ) || ( SLisEntCodVaciar ( NULL ) != 0 ) )
	{
		printf( "Error caso 3: eliminar o vaciar una lista nula deberia devolver 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* El cursor sobre una lista nula no hace nada. */
	SLisEntCodInicio ( NULL );
	SLisEntCodFinal ( NULL );
	SLisEntCodSiguiente ( NULL );
	SLisEntCodAnterior ( NULL );
	SLisEntCodMoverA ( NULL, 0 );
	SLisEntCodDeposicionar ( NULL );
	SListaEntidadesCod * p_lisNula = NULL;
	SLisEntCodDestruir ( &p_lisNula );
	SLisEntCodDestruir ( NULL );
	return ( iRes );
}



int TestSListaEntidadesCod ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SListaEntidadesCod]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSLisEntCodCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisEntCodInsertar01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisEntCodCursor01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisEntCodEstablecer01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisEntCodEliminar01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisEntCodExtraerElem01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisEntCodBuscar01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisEntCodInvalidos01 () == BOOL_VAL_CIERTO ) )
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
