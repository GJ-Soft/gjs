#include "Base.h"

#include "SSecuenciaId.h"


/* Bloques reservados ahora. El contador solo existe con MODO_DEPURACION: sin
   el da siempre 0 y las comprobaciones de memoria no miran nada. */
static unsigned long BloquesActuales ()
{
# if ( defined ( MODO_DEPURACION ) )
	return ( MemNumBloquesActuales () );
# else
	return ( 0 );
# endif
}



/* Compara el contenido de la secuencia, en orden, con los valores esperados:
   por SSecIdElemento ( SId nuevo, que se destruye ) y por SSecIdValorElemento. */
static int ContenidoEs ( SSecuenciaId * p_secObj, unsigned long * p_ulEsperados, int iNum )
{
	int iRes = BOOL_VAL_CIERTO;

	if ( SSecIdNumElementos ( p_secObj ) != iNum )
	{
		printf( "   se esperaban %d elementos: %d\n", iNum, SSecIdNumElementos ( p_secObj ) );
		iRes = BOOL_VAL_FALSO;
	}
	int iPos = 0;
	while ( ( iPos < iNum ) && ( iRes == BOOL_VAL_CIERTO ) )
	{
		SId * p_idElem = SSecIdElemento ( p_secObj, iPos );
		if ( ES_NULO ( p_idElem ) || ( SIdValor ( p_idElem ) != p_ulEsperados [ iPos ] ) ||
			 ( SSecIdValorElemento ( p_secObj, iPos ) != p_ulEsperados [ iPos ] ) )
		{
			printf( "   en la posicion %d se esperaba %lu\n", iPos, p_ulEsperados [ iPos ] );
			iRes = BOOL_VAL_FALSO;
		}
		SIdDestruir ( &p_idElem );
		iPos = iPos + 1;
	}
	return ( iRes );
}

static SSecuenciaId * CrearSecuencia ( unsigned long * p_ulValores, int iNum )
{
	SSecuenciaId * p_secObj = SSecIdCrear ();
	int iPos = 0;
	while ( ES_VALIDO ( p_secObj ) && ( iPos < iNum ) )
	{
		SSecIdInsertarExt ( p_secObj, p_ulValores [ iPos ] );
		iPos = iPos + 1;
	}
	return ( p_secObj );
}



static int TestSSecIdCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SSecIdCrear 01:\n" );

	unsigned long ulBloquesAntes = BloquesActuales ();
	SSecuenciaId * p_secObj = SSecIdCrear ();
	if ( ES_VALIDO ( p_secObj ) )
	{
		if ( ( SSecIdEsValida ( p_secObj ) != 1 ) || ( SSecIdEstaVacia ( p_secObj ) != 1 ) ||
			 ( SSecIdNumElementos ( p_secObj ) != 0 ) )
		{
			printf( "Error caso 1: recien creada deberia ser valida y estar vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_NULO ( SSecIdSecuencia ( p_secObj ) ) || ( SSecEsValida ( SSecIdSecuencia ( p_secObj ) ) != 1 ) )
		{
			printf( "Error caso 2: deberia exponer una SSecuencia valida\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( SSecIdElemento ( p_secObj, 0 ) ) || ( SSecIdValorElemento ( p_secObj, 0 ) != 0 ) )
		{
			printf( "Error caso 3: vacia, el elemento 0 deberia ser NULL y su valor 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la secuencia\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SSecIdDestruir ( &p_secObj );
	if ( ES_VALIDO ( p_secObj ) )
	{
		printf( "Error caso 4: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( BloquesActuales () != ulBloquesAntes )
	{
		printf( "Error caso 5: quedan %ld bloques sin liberar\n", (long) ( BloquesActuales () - ulBloquesAntes ) );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

/* En orden de insercion y con repetidos, sin ordenar. */
static int TestSSecIdInsertar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SSecIdInsertar 01:\n" );

	unsigned long ulBloquesAntes = BloquesActuales ();
	SSecuenciaId * p_secObj = SSecIdCrear ();
	SId * p_id20 = SIdCrear ( 20UL );
	if ( ES_VALIDO ( p_secObj ) && ES_VALIDO ( p_id20 ) )
	{
		if ( ( SSecIdInsertarExt ( p_secObj, 300UL ) != 1 ) || ( SSecIdInsertar ( p_secObj, p_id20 ) != 1 ) ||
			 ( SSecIdInsertarExt ( p_secObj, ULONG_MAX ) != 1 ) || ( SSecIdInsertar ( p_secObj, p_id20 ) != 1 ) ||
			 ( SSecIdInsertarExt ( p_secObj, 0UL ) != 1 ) || ( SSecIdInsertarExt ( p_secObj, 20UL ) != 1 ) )
		{
			printf( "Error caso 1: se esperaba 1 en cada insercion, tambien las repetidas\n" );
			iRes = BOOL_VAL_FALSO;
		}
		unsigned long ulEsp [ 6 ] = { 300UL, 20UL, ULONG_MAX, 20UL, 0UL, 20UL };
		if ( ContenidoEs ( p_secObj, ulEsp, 6 ) == BOOL_VAL_FALSO )
		{
			printf( "Error caso 2: se esperaba { 300, 20, ULONG_MAX, 20, 0, 20 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SSecIdEstaVacia ( p_secObj ) != 0 ) || ( SSecNumElementos ( SSecIdSecuencia ( p_secObj ) ) != 6 ) )
		{
			printf( "Error caso 3: no deberia estar vacia, y la SSecuencia deberia tener 6\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear la secuencia o el SId\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SIdDestruir ( &p_id20 );
	SSecIdDestruir ( &p_secObj );
	if ( BloquesActuales () != ulBloquesAntes )
	{
		printf( "Error caso 4: quedan %ld bloques sin liberar\n", (long) ( BloquesActuales () - ulBloquesAntes ) );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

/* Guarda copias: los SId siguen siendo del llamante, se pueden cambiar o
   destruir sin que la secuencia lo note, y SSecIdElemento da SId nuevos. */
static int TestSSecIdCopias01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SSecIdCopias 01:\n" );

	unsigned long ulBloquesAntes = BloquesActuales ();
	SSecuenciaId * p_secObj = SSecIdCrear ();
	SId * p_id300 = SIdCrear ( 300UL );
	SId * p_id10 = SIdCrear ( 10UL );
	if ( ES_VALIDO ( p_secObj ) && ES_VALIDO ( p_id300 ) && ES_VALIDO ( p_id10 ) )
	{
		SSecIdInsertar ( p_secObj, p_id300 );
		SSecIdInsertar ( p_secObj, p_id10 );
		if ( ( SIdEsValido ( p_id300 ) != 1 ) || ( SIdValor ( p_id300 ) != 300UL ) )
		{
			printf( "Error caso 1: el SId insertado deberia seguir intacto\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SIdEstablecer ( p_id300, 999UL );
		SIdDestruir ( &p_id10 );
		unsigned long ulEsp [ 2 ] = { 300UL, 10UL };
		if ( ContenidoEs ( p_secObj, ulEsp, 2 ) == BOOL_VAL_FALSO )
		{
			printf( "Error caso 2: se esperaba { 300, 10 } tras cambiar y destruir los originales\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SId * p_idElem1 = SSecIdElemento ( p_secObj, 0 );
		SId * p_idElem2 = SSecIdElemento ( p_secObj, 0 );
		if ( ES_NULO ( p_idElem1 ) || ES_NULO ( p_idElem2 ) || ( p_idElem1 == p_idElem2 ) || ( p_idElem1 == p_id300 ) )
		{
			printf( "Error caso 3: SSecIdElemento deberia dar un SId nuevo cada vez\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SIdEstablecer ( p_idElem1, 5UL );
		if ( SSecIdValorElemento ( p_secObj, 0 ) != 300UL )
		{
			printf( "Error caso 4: cambiar el SId devuelto no deberia cambiar la secuencia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SIdDestruir ( &p_idElem1 );
		SIdDestruir ( &p_idElem2 );
		SElemento * p_elmDato = SSecElemento ( SSecIdSecuencia ( p_secObj ), 1 );
		if ( SBlqTam ( SElmDatos ( p_elmDato ) ) != SIdTamBloqueBin () )
		{
			printf( "Error caso 5: cada elemento deberia medir SIdTamBloqueBin: %d\n", SBlqTam ( SElmDatos ( p_elmDato ) ) );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear la secuencia o los SId\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SIdDestruir ( &p_id300 );
	SIdDestruir ( &p_id10 );
	SSecIdDestruir ( &p_secObj );
	if ( BloquesActuales () != ulBloquesAntes )
	{
		printf( "Error caso 6: quedan %ld bloques sin liberar\n", (long) ( BloquesActuales () - ulBloquesAntes ) );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

/* Busca por contenido, con un SId que no esta en la secuencia y por valor;
   recorre los repetidos con BuscarPrimero / BuscarSiguiente. */
static int TestSSecIdBuscar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SSecIdBuscar 01:\n" );

	unsigned long ulBloquesAntes = BloquesActuales ();
	unsigned long ulVal [ 6 ] = { 20UL, 10UL, 20UL, 30UL, 20UL, 40UL };
	SSecuenciaId * p_secObj = CrearSecuencia ( ulVal, 6 );
	SSecuenciaId * p_secVacia = SSecIdCrear ();
	SId * p_id20 = SIdCrear ( 20UL );
	SId * p_id99 = SIdCrear ( 99UL );
	if ( ES_VALIDO ( p_secObj ) && ES_VALIDO ( p_secVacia ) && ES_VALIDO ( p_id20 ) && ES_VALIDO ( p_id99 ) )
	{
		if ( ( SSecIdBuscarPrimero ( p_secObj, p_id20 ) != 0 ) ||
			 ( SSecIdBuscarSiguiente ( p_secObj, p_id20, 0 ) != 2 ) ||
			 ( SSecIdBuscarSiguiente ( p_secObj, p_id20, 2 ) != 4 ) ||
			 ( SSecIdBuscarSiguiente ( p_secObj, p_id20, 4 ) != -1 ) )
		{
			printf( "Error caso 1: el 20 deberia estar en 0, 2 y 4\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SSecIdBuscarPrimeroExt ( p_secObj, 20UL ) != 0 ) ||
			 ( SSecIdBuscarSiguienteExt ( p_secObj, 20UL, 0 ) != 2 ) ||
			 ( SSecIdBuscarSiguienteExt ( p_secObj, 20UL, 2 ) != 4 ) ||
			 ( SSecIdBuscarSiguienteExt ( p_secObj, 20UL, 4 ) != -1 ) )
		{
			printf( "Error caso 2: por valor, el 20 deberia estar en 0, 2 y 4\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Desde la posicion siguiente, no desde la misma. */
		if ( ( SSecIdBuscarSiguiente ( p_secObj, p_id20, 1 ) != 2 ) || ( SSecIdBuscarSiguienteExt ( p_secObj, 20UL, 3 ) != 4 ) ||
			 ( SSecIdBuscar ( p_secObj, p_id20 ) != 0 ) || ( SSecIdBuscarExt ( p_secObj, 40UL ) != 5 ) ||
			 ( SSecIdBuscarSiguiente ( p_secObj, p_id20, -1 ) != 0 ) )
		{
			printf( "Error caso 3: detras de la 1 el 20 esta en la 2, Buscar es BuscarPrimero y el 40 esta en la 5\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SSecIdRepeticiones ( p_secObj, p_id20 ) != 3 ) || ( SSecIdRepeticionesExt ( p_secObj, 20UL ) != 3 ) ||
			 ( SSecIdRepeticionesExt ( p_secObj, 10UL ) != 1 ) ||
			 ( SSecIdExiste ( p_secObj, p_id20 ) != 1 ) || ( SSecIdExisteExt ( p_secObj, 30UL ) != 1 ) )
		{
			printf( "Error caso 4: el 20 deberia estar 3 veces y el 10 una\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SSecIdRepeticiones ( p_secObj, p_id99 ) != 0 ) || ( SSecIdExiste ( p_secObj, p_id99 ) != 0 ) ||
			 ( SSecIdBuscar ( p_secObj, p_id99 ) != -1 ) || ( SSecIdBuscarPrimero ( p_secObj, p_id99 ) != -1 ) ||
			 ( SSecIdExisteExt ( p_secObj, 0UL ) != 0 ) || ( SSecIdBuscarExt ( p_secObj, ULONG_MAX ) != -1 ) ||
			 ( SSecIdRepeticionesExt ( p_secObj, 99UL ) != 0 ) )
		{
			printf( "Error caso 5: 99, 0 y ULONG_MAX no deberian estar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SSecIdRepeticiones ( p_secVacia, p_id20 ) != 0 ) || ( SSecIdExiste ( p_secVacia, p_id20 ) != 0 ) ||
			 ( SSecIdBuscarPrimero ( p_secVacia, p_id20 ) != -1 ) )
		{
			printf( "Error caso 6: en una secuencia vacia no deberia estar nada\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SSecIdBuscarSiguiente ( p_secObj, p_id20, 5 ) != -1 ) ||
			 ( SSecIdBuscarSiguiente ( p_secObj, p_id20, -2 ) != -1 ) )
		{
			printf( "Error caso 7: desde el final o con una posicion menor que -1 se esperaba -1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		unsigned long ulBloquesLleno = BloquesActuales ();
		SSecIdRepeticiones ( p_secObj, p_id20 );
		SSecIdBuscarSiguienteExt ( p_secObj, 20UL, 0 );
		SSecIdExisteExt ( p_secObj, 99UL );
		if ( BloquesActuales () != ulBloquesLleno )
		{
			printf( "Error caso 8: buscar deja %ld bloques\n", (long) ( BloquesActuales () - ulBloquesLleno ) );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear las secuencias o los SId\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SIdDestruir ( &p_id20 );
	SIdDestruir ( &p_id99 );
	SSecIdDestruir ( &p_secObj );
	SSecIdDestruir ( &p_secVacia );
	if ( BloquesActuales () != ulBloquesAntes )
	{
		printf( "Error caso 9: quedan %ld bloques sin liberar\n", (long) ( BloquesActuales () - ulBloquesAntes ) );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSSecIdEliminar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SSecIdEliminar 01:\n" );

	unsigned long ulBloquesAntes = BloquesActuales ();
	unsigned long ulVal [ 5 ] = { 10UL, 20UL, 30UL, 20UL, 50UL };
	SSecuenciaId * p_secObj = CrearSecuencia ( ulVal, 5 );
	if ( ES_VALIDO ( p_secObj ) )
	{
		if ( ( SSecIdEliminarElem ( p_secObj, 1 ) != 1 ) || ( SSecIdEliminarElem ( p_secObj, 4 ) != 0 ) ||
			 ( SSecIdEliminarElem ( p_secObj, -1 ) != 0 ) )
		{
			printf( "Error caso 1: eliminar la posicion 1 deberia dar 1, y la 4 y la -1 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
		unsigned long ulEsp1 [ 4 ] = { 10UL, 30UL, 20UL, 50UL };
		if ( ContenidoEs ( p_secObj, ulEsp1, 4 ) == BOOL_VAL_FALSO )
		{
			printf( "Error caso 2: se esperaba { 10, 30, 20, 50 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SSecIdRepeticionesExt ( p_secObj, 20UL ) != 1 ) || ( SSecIdBuscarExt ( p_secObj, 20UL ) != 2 ) )
		{
			printf( "Error caso 3: deberia quedar un 20, en la posicion 2\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SSecIdVaciar ( p_secObj ) != 1 ) || ( SSecIdEstaVacia ( p_secObj ) != 1 ) ||
			 ( SSecIdEsValida ( p_secObj ) != 1 ) )
		{
			printf( "Error caso 4: tras vaciar deberia estar vacia y seguir valida\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SSecIdInsertarExt ( p_secObj, 7UL ) != 1 ) || ( SSecIdValorElemento ( p_secObj, 0 ) != 7UL ) )
		{
			printf( "Error caso 5: tras vaciar se deberia poder insertar\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la secuencia\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SSecIdDestruir ( &p_secObj );
	if ( BloquesActuales () != ulBloquesAntes )
	{
		printf( "Error caso 6: quedan %ld bloques sin liberar\n", (long) ( BloquesActuales () - ulBloquesAntes ) );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSSecIdNulos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SSecIdNulos 01:\n" );

	SSecuenciaId * p_secObj = SSecIdCrear ();
	SId * p_idObj = SIdCrear ( 1UL );
	SSecIdInsertarExt ( p_secObj, 1UL );

	if ( ( SSecIdEsValida ( NULL ) != 0 ) || ( SSecIdEstaVacia ( NULL ) != 1 ) || ( SSecIdNumElementos ( NULL ) != 0 ) ||
		 ( SSecIdExiste ( NULL, p_idObj ) != 0 ) || ( SSecIdBuscar ( NULL, p_idObj ) != -1 ) ||
		 ( SSecIdRepeticiones ( NULL, p_idObj ) != 0 ) || ( SSecIdBuscarPrimero ( NULL, p_idObj ) != -1 ) ||
		 ( SSecIdBuscarSiguiente ( NULL, p_idObj, -1 ) != -1 ) ||
		 ( SSecIdExisteExt ( NULL, 1UL ) != 0 ) || ( SSecIdBuscarExt ( NULL, 1UL ) != -1 ) ||
		 ( SSecIdRepeticionesExt ( NULL, 1UL ) != 0 ) || ( SSecIdBuscarPrimeroExt ( NULL, 1UL ) != -1 ) ||
		 ( SSecIdBuscarSiguienteExt ( NULL, 1UL, -1 ) != -1 ) ||
		 ES_VALIDO ( SSecIdElemento ( NULL, 0 ) ) || ( SSecIdValorElemento ( NULL, 0 ) != 0 ) ||
		 ( SSecIdInsertar ( NULL, p_idObj ) != 0 ) || ( SSecIdInsertarExt ( NULL, 1UL ) != 0 ) ||
		 ( SSecIdEliminarElem ( NULL, 0 ) != 0 ) || ( SSecIdVaciar ( NULL ) != 0 ) ||
		 ES_VALIDO ( SSecIdSecuencia ( NULL ) ) )
	{
		printf( "Error caso 1: con una secuencia nula se esperaba 0, -1, vacia o NULL\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ( SSecIdExiste ( p_secObj, NULL ) != 0 ) || ( SSecIdBuscar ( p_secObj, NULL ) != -1 ) ||
		 ( SSecIdRepeticiones ( p_secObj, NULL ) != 0 ) || ( SSecIdBuscarPrimero ( p_secObj, NULL ) != -1 ) ||
		 ( SSecIdBuscarSiguiente ( p_secObj, NULL, -1 ) != -1 ) || ( SSecIdInsertar ( p_secObj, NULL ) != 0 ) )
	{
		printf( "Error caso 2: con un SId nulo se esperaba 0 o -1\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SSecIdNumElementos ( p_secObj ) != 1 )
	{
		printf( "Error caso 3: con nulos no deberia cambiar el contenido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SSecIdDestruir ( NULL );
	SSecuenciaId * p_secNula = NULL;
	SSecIdDestruir ( &p_secNula );
	SIdDestruir ( &p_idObj );
	SSecIdDestruir ( &p_secObj );
	return ( iRes );
}



int TestSSecuenciaId ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SSecuenciaId]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSSecIdCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSSecIdInsertar01 () == BOOL_VAL_CIERTO ) &&
			( TestSSecIdCopias01 () == BOOL_VAL_CIERTO ) &&
			( TestSSecIdBuscar01 () == BOOL_VAL_CIERTO ) &&
			( TestSSecIdEliminar01 () == BOOL_VAL_CIERTO ) &&
			( TestSSecIdNulos01 () == BOOL_VAL_CIERTO ) )
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
