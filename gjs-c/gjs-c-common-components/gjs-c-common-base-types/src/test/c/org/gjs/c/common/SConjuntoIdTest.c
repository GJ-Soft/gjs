#include "Base.h"

#include "SConjuntoId.h"


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



/* Compara el contenido del conjunto, en orden, con los valores esperados:
   por SCnjIdElemento ( SId nuevo, que se destruye ) y por SCnjIdValorElemento. */
static int ContenidoEs ( SConjuntoId * p_cnjObj, unsigned long * p_ulEsperados, int iNum )
{
	int iRes = BOOL_VAL_CIERTO;

	if ( SCnjIdNumElementos ( p_cnjObj ) != iNum )
	{
		printf( "   se esperaban %d elementos: %d\n", iNum, SCnjIdNumElementos ( p_cnjObj ) );
		iRes = BOOL_VAL_FALSO;
	}
	int iPos = 0;
	while ( ( iPos < iNum ) && ( iRes == BOOL_VAL_CIERTO ) )
	{
		SId * p_idElem = SCnjIdElemento ( p_cnjObj, iPos );
		if ( ES_NULO ( p_idElem ) || ( SIdValor ( p_idElem ) != p_ulEsperados [ iPos ] ) ||
			 ( SCnjIdValorElemento ( p_cnjObj, iPos ) != p_ulEsperados [ iPos ] ) )
		{
			printf( "   en la posicion %d se esperaba %lu\n", iPos, p_ulEsperados [ iPos ] );
			iRes = BOOL_VAL_FALSO;
		}
		SIdDestruir ( &p_idElem );
		iPos = iPos + 1;
	}
	return ( iRes );
}



static int TestSCnjIdCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCnjIdCrear 01:\n" );

	unsigned long ulBloquesAntes = BloquesActuales ();
	SConjuntoId * p_cnjObj = SCnjIdCrear ();
	if ( ES_VALIDO ( p_cnjObj ) )
	{
		if ( ( SCnjIdEsValido ( p_cnjObj ) != 1 ) || ( SCnjIdEstaVacio ( p_cnjObj ) != 1 ) ||
			 ( SCnjIdNumElementos ( p_cnjObj ) != 0 ) )
		{
			printf( "Error caso 1: recien creado deberia ser valido y estar vacio\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_NULO ( SCnjIdConjunto ( p_cnjObj ) ) || ( SCnjEsValido ( SCnjIdConjunto ( p_cnjObj ) ) != 1 ) )
		{
			printf( "Error caso 2: deberia exponer un SConjunto valido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( SCnjIdElemento ( p_cnjObj, 0 ) ) || ( SCnjIdValorElemento ( p_cnjObj, 0 ) != 0 ) )
		{
			printf( "Error caso 3: vacio, el elemento 0 deberia ser NULL y su valor 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el conjunto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SCnjIdDestruir ( &p_cnjObj );
	if ( ES_VALIDO ( p_cnjObj ) )
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

/* Guarda copias: los SId siguen siendo del llamante, se pueden cambiar o
   destruir sin que el conjunto lo note, y SCnjIdElemento da SId nuevos. */
static int TestSCnjIdCopias01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCnjIdCopias 01:\n" );

	unsigned long ulBloquesAntes = BloquesActuales ();
	SConjuntoId * p_cnjObj = SCnjIdCrear ();
	SId * p_id300 = SIdCrear ( 300UL );
	SId * p_id10 = SIdCrear ( 10UL );
	if ( ES_VALIDO ( p_cnjObj ) && ES_VALIDO ( p_id300 ) && ES_VALIDO ( p_id10 ) )
	{
		if ( ( SCnjIdInsertar ( p_cnjObj, p_id300 ) != 1 ) || ( SCnjIdInsertar ( p_cnjObj, p_id10 ) != 1 ) )
		{
			printf( "Error caso 1: se esperaba 1 al insertar 300 y 10\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SIdEsValido ( p_id300 ) != 1 ) || ( SIdValor ( p_id300 ) != 300UL ) )
		{
			printf( "Error caso 2: el SId insertado deberia seguir intacto\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Cambiar el original no cambia la copia. */
		SIdEstablecer ( p_id300, 999UL );
		unsigned long ulEsp [ 2 ] = { 10UL, 300UL };
		if ( ContenidoEs ( p_cnjObj, ulEsp, 2 ) == BOOL_VAL_FALSO )
		{
			printf( "Error caso 3: se esperaba { 10, 300 } aunque el original pase a 999\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCnjIdExisteExt ( p_cnjObj, 999UL ) != 0 )
		{
			printf( "Error caso 4: el 999 del original no deberia estar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Destruir el original tampoco. */
		SIdDestruir ( &p_id10 );
		if ( SCnjIdValorElemento ( p_cnjObj, 0 ) != 10UL )
		{
			printf( "Error caso 5: el 10 deberia seguir tras destruir su SId\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Cada SCnjIdElemento es un SId distinto, y cambiarlo no toca el conjunto. */
		SId * p_idElem1 = SCnjIdElemento ( p_cnjObj, 1 );
		SId * p_idElem2 = SCnjIdElemento ( p_cnjObj, 1 );
		if ( ES_NULO ( p_idElem1 ) || ES_NULO ( p_idElem2 ) || ( p_idElem1 == p_idElem2 ) || ( p_idElem1 == p_id300 ) )
		{
			printf( "Error caso 6: SCnjIdElemento deberia dar un SId nuevo cada vez\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SIdEstablecer ( p_idElem1, 5UL );
		if ( SCnjIdValorElemento ( p_cnjObj, 1 ) != 300UL )
		{
			printf( "Error caso 7: cambiar el SId devuelto no deberia cambiar el conjunto\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SIdDestruir ( &p_idElem1 );
		SIdDestruir ( &p_idElem2 );
		/* Lo guardado es SIdBloqueBin, ni mas ni menos. */
		SElemento * p_elmDato = SCnjElemento ( SCnjIdConjunto ( p_cnjObj ), 0 );
		if ( SBlqTam ( SElmDatos ( p_elmDato ) ) != SIdTamBloqueBin () )
		{
			printf( "Error caso 8: cada elemento deberia medir SIdTamBloqueBin: %d\n", SBlqTam ( SElmDatos ( p_elmDato ) ) );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear el conjunto o los SId\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SIdDestruir ( &p_id300 );
	SIdDestruir ( &p_id10 );
	SCnjIdDestruir ( &p_cnjObj );
	if ( BloquesActuales () != ulBloquesAntes )
	{
		printf( "Error caso 9: quedan %ld bloques sin liberar\n", (long) ( BloquesActuales () - ulBloquesAntes ) );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

/* El orden es el de SIdComparar, no el de los bytes guardados: en
   little-endian 256 es 00 01 ... y 1 es 01 00 ..., y comparando bytes el 256
   iria antes. */
static int TestSCnjIdOrden01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCnjIdOrden 01:\n" );

	unsigned long ulBloquesAntes = BloquesActuales ();
	SConjuntoId * p_cnjObj = SCnjIdCrear ();
	if ( ES_VALIDO ( p_cnjObj ) )
	{
		unsigned long ulIns [ 7 ] = { 256UL, 1UL, ULONG_MAX, 0UL, 65536UL, 2000000000UL, 255UL };
		int iPos = 0;
		while ( iPos < 7 )
		{
			if ( SCnjIdInsertarExt ( p_cnjObj, ulIns [ iPos ] ) != 1 )
			{
				printf( "Error caso 1: se esperaba 1 al insertar %lu\n", ulIns [ iPos ] );
				iRes = BOOL_VAL_FALSO;
			}
			iPos = iPos + 1;
		}
		unsigned long ulEsp [ 7 ] = { 0UL, 1UL, 255UL, 256UL, 65536UL, 2000000000UL, ULONG_MAX };
		if ( ContenidoEs ( p_cnjObj, ulEsp, 7 ) == BOOL_VAL_FALSO )
		{
			printf( "Error caso 2: se esperaba { 0, 1, 255, 256, 65536, 2000000000, ULONG_MAX }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SCnjIdBuscarExt ( p_cnjObj, 0UL ) != 0 ) || ( SCnjIdBuscarExt ( p_cnjObj, 256UL ) != 3 ) ||
			 ( SCnjIdBuscarExt ( p_cnjObj, ULONG_MAX ) != 6 ) )
		{
			printf( "Error caso 3: 0, 256 y ULONG_MAX deberian estar en 0, 3 y 6\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el conjunto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SCnjIdDestruir ( &p_cnjObj );
	if ( BloquesActuales () != ulBloquesAntes )
	{
		printf( "Error caso 4: quedan %ld bloques sin liberar\n", (long) ( BloquesActuales () - ulBloquesAntes ) );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

/* Un identificador igual a otro ya guardado no entra, venga en otro SId o por
   valor, y lo rechazado no deja memoria. */
static int TestSCnjIdRepetidos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCnjIdRepetidos 01:\n" );

	unsigned long ulBloquesAntes = BloquesActuales ();
	SConjuntoId * p_cnjObj = SCnjIdCrear ();
	SId * p_id20 = SIdCrear ( 20UL );
	SId * p_idOtro20 = SIdCrear ( 20UL );
	if ( ES_VALIDO ( p_cnjObj ) && ES_VALIDO ( p_id20 ) && ES_VALIDO ( p_idOtro20 ) )
	{
		SCnjIdInsertar ( p_cnjObj, p_id20 );
		SCnjIdInsertarExt ( p_cnjObj, 30UL );
		unsigned long ulBloquesLleno = BloquesActuales ();
		if ( ( SCnjIdInsertar ( p_cnjObj, p_id20 ) != 0 ) || ( SCnjIdInsertar ( p_cnjObj, p_idOtro20 ) != 0 ) ||
			 ( SCnjIdInsertarExt ( p_cnjObj, 20UL ) != 0 ) || ( SCnjIdInsertarExt ( p_cnjObj, 30UL ) != 0 ) )
		{
			printf( "Error caso 1: con un igual ya guardado se esperaba 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
		unsigned long ulEsp [ 2 ] = { 20UL, 30UL };
		if ( ContenidoEs ( p_cnjObj, ulEsp, 2 ) == BOOL_VAL_FALSO )
		{
			printf( "Error caso 2: se esperaba { 20, 30 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( BloquesActuales () != ulBloquesLleno )
		{
			printf( "Error caso 3: los rechazados dejan %ld bloques\n", (long) ( BloquesActuales () - ulBloquesLleno ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SIdValor ( p_idOtro20 ) != 20UL )
		{
			printf( "Error caso 4: el SId rechazado deberia seguir intacto\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear el conjunto o los SId\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SIdDestruir ( &p_id20 );
	SIdDestruir ( &p_idOtro20 );
	SCnjIdDestruir ( &p_cnjObj );
	if ( BloquesActuales () != ulBloquesAntes )
	{
		printf( "Error caso 5: quedan %ld bloques sin liberar\n", (long) ( BloquesActuales () - ulBloquesAntes ) );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

/* Buscan por contenido: vale un SId que no esta en el conjunto. */
static int TestSCnjIdBuscar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCnjIdBuscar 01:\n" );

	unsigned long ulBloquesAntes = BloquesActuales ();
	SConjuntoId * p_cnjObj = SCnjIdCrear ();
	SId * p_idSonda = SIdCrear ( 40UL );
	SId * p_idFalta = SIdCrear ( 35UL );
	if ( ES_VALIDO ( p_cnjObj ) && ES_VALIDO ( p_idSonda ) && ES_VALIDO ( p_idFalta ) )
	{
		SCnjIdInsertarExt ( p_cnjObj, 50UL );
		SCnjIdInsertarExt ( p_cnjObj, 30UL );
		SCnjIdInsertarExt ( p_cnjObj, 40UL );
		if ( ( SCnjIdExiste ( p_cnjObj, p_idSonda ) != 1 ) || ( SCnjIdBuscar ( p_cnjObj, p_idSonda ) != 1 ) ||
			 ( SCnjIdExisteExt ( p_cnjObj, 40UL ) != 1 ) || ( SCnjIdBuscarExt ( p_cnjObj, 40UL ) != 1 ) )
		{
			printf( "Error caso 1: el 40 deberia estar en la posicion 1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SCnjIdExiste ( p_cnjObj, p_idFalta ) != 0 ) || ( SCnjIdBuscar ( p_cnjObj, p_idFalta ) != -1 ) ||
			 ( SCnjIdExisteExt ( p_cnjObj, 35UL ) != 0 ) || ( SCnjIdBuscarExt ( p_cnjObj, 35UL ) != -1 ) ||
			 ( SCnjIdBuscarExt ( p_cnjObj, 0UL ) != -1 ) || ( SCnjIdBuscarExt ( p_cnjObj, ULONG_MAX ) != -1 ) )
		{
			printf( "Error caso 2: 35, 0 y ULONG_MAX no deberian encontrarse\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Buscar no se queda con nada. */
		unsigned long ulBloquesLleno = BloquesActuales ();
		SCnjIdExiste ( p_cnjObj, p_idSonda );
		SCnjIdBuscarExt ( p_cnjObj, 35UL );
		if ( BloquesActuales () != ulBloquesLleno )
		{
			printf( "Error caso 3: buscar deja %ld bloques\n", (long) ( BloquesActuales () - ulBloquesLleno ) );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear el conjunto o los SId\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SIdDestruir ( &p_idSonda );
	SIdDestruir ( &p_idFalta );
	SCnjIdDestruir ( &p_cnjObj );
	if ( BloquesActuales () != ulBloquesAntes )
	{
		printf( "Error caso 4: quedan %ld bloques sin liberar\n", (long) ( BloquesActuales () - ulBloquesAntes ) );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSCnjIdEliminar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCnjIdEliminar 01:\n" );

	unsigned long ulBloquesAntes = BloquesActuales ();
	SConjuntoId * p_cnjObj = SCnjIdCrear ();
	SId * p_id20 = SIdCrear ( 20UL );
	if ( ES_VALIDO ( p_cnjObj ) && ES_VALIDO ( p_id20 ) )
	{
		unsigned long ulIns [ 5 ] = { 10UL, 20UL, 30UL, 40UL, 50UL };
		int iPos = 0;
		while ( iPos < 5 )
		{
			SCnjIdInsertarExt ( p_cnjObj, ulIns [ iPos ] );
			iPos = iPos + 1;
		}
		/* Por SId, que no es el guardado. */
		if ( ( SCnjIdEliminar ( p_cnjObj, p_id20 ) != 1 ) || ( SCnjIdEliminar ( p_cnjObj, p_id20 ) != 0 ) )
		{
			printf( "Error caso 1: eliminar el 20 deberia dar 1, y repetirlo 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SCnjIdEliminarExt ( p_cnjObj, 50UL ) != 1 ) || ( SCnjIdEliminarExt ( p_cnjObj, 99UL ) != 0 ) )
		{
			printf( "Error caso 2: eliminar el 50 deberia dar 1, y el 99 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
		unsigned long ulEsp1 [ 3 ] = { 10UL, 30UL, 40UL };
		if ( ContenidoEs ( p_cnjObj, ulEsp1, 3 ) == BOOL_VAL_FALSO )
		{
			printf( "Error caso 3: se esperaba { 10, 30, 40 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SCnjIdEliminarElem ( p_cnjObj, 1 ) != 1 ) || ( SCnjIdEliminarElem ( p_cnjObj, 2 ) != 0 ) ||
			 ( SCnjIdEliminarElem ( p_cnjObj, -1 ) != 0 ) )
		{
			printf( "Error caso 4: eliminar la posicion 1 deberia dar 1, y la 2 y la -1 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
		unsigned long ulEsp2 [ 2 ] = { 10UL, 40UL };
		if ( ContenidoEs ( p_cnjObj, ulEsp2, 2 ) == BOOL_VAL_FALSO )
		{
			printf( "Error caso 5: se esperaba { 10, 40 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* El 20 eliminado se puede volver a insertar. */
		if ( ( SCnjIdInsertar ( p_cnjObj, p_id20 ) != 1 ) || ( SCnjIdBuscar ( p_cnjObj, p_id20 ) != 1 ) )
		{
			printf( "Error caso 6: el 20 deberia volver a entrar, en la posicion 1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SCnjIdVaciar ( p_cnjObj ) != 1 ) || ( SCnjIdEstaVacio ( p_cnjObj ) != 1 ) ||
			 ( SCnjIdEsValido ( p_cnjObj ) != 1 ) )
		{
			printf( "Error caso 7: tras vaciar deberia estar vacio y seguir valido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCnjIdInsertarExt ( p_cnjObj, 7UL ) != 1 )
		{
			printf( "Error caso 8: tras vaciar se deberia poder insertar\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear el conjunto o el SId\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SIdDestruir ( &p_id20 );
	SCnjIdDestruir ( &p_cnjObj );
	if ( BloquesActuales () != ulBloquesAntes )
	{
		printf( "Error caso 9: quedan %ld bloques sin liberar\n", (long) ( BloquesActuales () - ulBloquesAntes ) );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSCnjIdNulos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCnjIdNulos 01:\n" );

	SConjuntoId * p_cnjObj = SCnjIdCrear ();
	SId * p_idObj = SIdCrear ( 1UL );
	SCnjIdInsertarExt ( p_cnjObj, 1UL );

	if ( ( SCnjIdEsValido ( NULL ) != 0 ) || ( SCnjIdEstaVacio ( NULL ) != 1 ) || ( SCnjIdNumElementos ( NULL ) != 0 ) ||
		 ( SCnjIdExiste ( NULL, p_idObj ) != 0 ) || ( SCnjIdBuscar ( NULL, p_idObj ) != -1 ) ||
		 ( SCnjIdExisteExt ( NULL, 1UL ) != 0 ) || ( SCnjIdBuscarExt ( NULL, 1UL ) != -1 ) ||
		 ES_VALIDO ( SCnjIdElemento ( NULL, 0 ) ) || ( SCnjIdValorElemento ( NULL, 0 ) != 0 ) ||
		 ( SCnjIdInsertar ( NULL, p_idObj ) != 0 ) || ( SCnjIdInsertarExt ( NULL, 1UL ) != 0 ) ||
		 ( SCnjIdEliminar ( NULL, p_idObj ) != 0 ) || ( SCnjIdEliminarExt ( NULL, 1UL ) != 0 ) ||
		 ( SCnjIdEliminarElem ( NULL, 0 ) != 0 ) || ( SCnjIdVaciar ( NULL ) != 0 ) ||
		 ES_VALIDO ( SCnjIdConjunto ( NULL ) ) )
	{
		printf( "Error caso 1: con un conjunto nulo se esperaba 0, -1, vacio o NULL\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ( SCnjIdExiste ( p_cnjObj, NULL ) != 0 ) || ( SCnjIdBuscar ( p_cnjObj, NULL ) != -1 ) ||
		 ( SCnjIdInsertar ( p_cnjObj, NULL ) != 0 ) || ( SCnjIdEliminar ( p_cnjObj, NULL ) != 0 ) )
	{
		printf( "Error caso 2: con un SId nulo se esperaba 0 o -1\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SCnjIdNumElementos ( p_cnjObj ) != 1 )
	{
		printf( "Error caso 3: con nulos no deberia cambiar el contenido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SCnjIdDestruir ( NULL );
	SConjuntoId * p_cnjNulo = NULL;
	SCnjIdDestruir ( &p_cnjNulo );
	SIdDestruir ( &p_idObj );
	SCnjIdDestruir ( &p_cnjObj );
	return ( iRes );
}



int TestSConjuntoId ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SConjuntoId]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSCnjIdCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSCnjIdCopias01 () == BOOL_VAL_CIERTO ) &&
			( TestSCnjIdOrden01 () == BOOL_VAL_CIERTO ) &&
			( TestSCnjIdRepetidos01 () == BOOL_VAL_CIERTO ) &&
			( TestSCnjIdBuscar01 () == BOOL_VAL_CIERTO ) &&
			( TestSCnjIdEliminar01 () == BOOL_VAL_CIERTO ) &&
			( TestSCnjIdNulos01 () == BOOL_VAL_CIERTO ) )
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
