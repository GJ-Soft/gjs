#include "Base.h"

#include "SConjuntoEntidades.h"



static int IdEs ( SEntidad * p_entObj, unsigned long ulId )
{
	return ( ES_VALIDO ( p_entObj ) && ( SEntValorId ( p_entObj ) == ulId ) );
}

/* Inserta 20, 30 y 10 en desorden: el conjunto queda 10, 20, 30. */
static void LlenarConjunto ( SConjuntoEntidades * p_cnjObj )
{
	SCnjEntInsertar ( p_cnjObj, SEntCrear ( 20 ) );
	SCnjEntInsertar ( p_cnjObj, SEntCrear ( 30 ) );
	SCnjEntInsertar ( p_cnjObj, SEntCrear ( 10 ) );
}



static int TestSCnjEntCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCnjEntCrear 01:\n" );
# if ( defined ( MODO_DEPURACION ) )
	unsigned long ulBloquesAntes = MemNumBloquesActuales ();
# endif

	SConjuntoEntidades * p_cnjObj = SCnjEntCrear ();
	if ( ES_NULO ( p_cnjObj ) )
	{
		printf( "Error caso 1: no se esperaba nulo al crear\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SCnjEntEsValido ( p_cnjObj ) != 1 )
		{
			printf( "Error caso 2: el conjunto recien creado deberia ser valido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SCnjEntEstaVacio ( p_cnjObj ) != 1 ) || ( SCnjEntNumElementos ( p_cnjObj ) != 0 ) )
		{
			printf( "Error caso 3: el conjunto recien creado deberia estar vacio\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( SCnjEntPrimero ( p_cnjObj ) ) || ES_VALIDO ( SCnjEntUltimo ( p_cnjObj ) ) )
		{
			printf( "Error caso 4: un conjunto vacio no tiene primero ni ultimo\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	SCnjEntDestruir ( &p_cnjObj );
	if ( ES_VALIDO ( p_cnjObj ) )
	{
		printf( "Error caso 5: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
# if ( defined ( MODO_DEPURACION ) )
	if ( MemNumBloquesActuales () != ulBloquesAntes )
	{
		printf( "Error caso 6: quedan %ld bloques sin liberar\n", (long) ( MemNumBloquesActuales () - ulBloquesAntes ) );
		iRes = BOOL_VAL_FALSO;
	}
# endif
	return ( iRes );
}

static int TestSCnjEntInsertar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCnjEntInsertar 01:\n" );
# if ( defined ( MODO_DEPURACION ) )
	unsigned long ulBloquesAntes = MemNumBloquesActuales ();
# endif

	SConjuntoEntidades * p_cnjObj = SCnjEntCrear ();
	if ( ES_VALIDO ( p_cnjObj ) )
	{
		/* El conjunto guarda el puntero, sin copiar, y ordena por id. */
		SEntidad * p_entVeinte = SEntCrear ( 20 );
		if ( ( SCnjEntInsertar ( p_cnjObj, p_entVeinte ) != 1 ) ||
			 ( SCnjEntInsertar ( p_cnjObj, SEntCrear ( 30 ) ) != 1 ) ||
			 ( SCnjEntInsertar ( p_cnjObj, SEntCrear ( 10 ) ) != 1 ) )
		{
			printf( "Error caso 1: se esperaba poder insertar las tres entidades\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SCnjEntNumElementos ( p_cnjObj ) != 3 ) ||
			 ( ! IdEs ( SCnjEntElemento ( p_cnjObj, 0 ), 10 ) ) ||
			 ( ! IdEs ( SCnjEntElemento ( p_cnjObj, 1 ), 20 ) ) ||
			 ( ! IdEs ( SCnjEntElemento ( p_cnjObj, 2 ), 30 ) ) )
		{
			printf( "Error caso 2: las entidades deberian quedar ordenadas por id ( 10, 20, 30 )\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCnjEntElemento ( p_cnjObj, 1 ) != p_entVeinte )
		{
			printf( "Error caso 3: el conjunto deberia guardar la misma entidad, no una copia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Un id ya presente se rechaza, y la entidad sigue siendo del llamador. */
		SEntidad * p_entDup = SEntCrear ( 20 );
		if ( SCnjEntInsertar ( p_cnjObj, p_entDup ) != -1 )
		{
			printf( "Error caso 4: insertar un id duplicado deberia devolver -1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SCnjEntNumElementos ( p_cnjObj ) != 3 ) || ( ! IdEs ( p_entDup, 20 ) ) )
		{
			printf( "Error caso 5: el duplicado no deberia entrar ni tocarse\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SEntDestruir ( &p_entDup );
		if ( SCnjEntInsertar ( p_cnjObj, NULL ) != -1 )
		{
			printf( "Error caso 6: insertar una entidad nula deberia devolver -1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( ! IdEs ( SCnjEntPrimero ( p_cnjObj ), 10 ) ) || ( ! IdEs ( SCnjEntUltimo ( p_cnjObj ), 30 ) ) )
		{
			printf( "Error caso 7: el primero deberia ser el 10 y el ultimo el 30\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el conjunto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* Destruir el conjunto destruye sus entidades. */
	SCnjEntDestruir ( &p_cnjObj );
# if ( defined ( MODO_DEPURACION ) )
	if ( MemNumBloquesActuales () != ulBloquesAntes )
	{
		printf( "Error caso 8: quedan %ld bloques sin liberar\n", (long) ( MemNumBloquesActuales () - ulBloquesAntes ) );
		iRes = BOOL_VAL_FALSO;
	}
# endif
	return ( iRes );
}

static int TestSCnjEntBuscar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCnjEntBuscar 01:\n" );
# if ( defined ( MODO_DEPURACION ) )
	unsigned long ulBloquesAntes = MemNumBloquesActuales ();
# endif

	SConjuntoEntidades * p_cnjObj = SCnjEntCrear ();
	SEntidad * p_entBuscar = SEntCrear ( 20 );
	SId * p_idBuscar = SIdCrear ( 30 );
	if ( ES_VALIDO ( p_cnjObj ) && ES_VALIDO ( p_entBuscar ) && ES_VALIDO ( p_idBuscar ) )
	{
		LlenarConjunto ( p_cnjObj );

		/* Por identificador: la entidad buscada no es ninguna de las del conjunto. */
		if ( ( SCnjEntExiste ( p_cnjObj, p_entBuscar ) != 1 ) || ( SCnjEntBuscar ( p_cnjObj, p_entBuscar ) != 1 ) ||
			 ( SCnjEntPosicion ( p_cnjObj, p_entBuscar ) != 1 ) )
		{
			printf( "Error caso 1: la entidad 20 deberia estar en la posicion 1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SCnjEntExisteId ( p_cnjObj, p_idBuscar ) != 1 ) || ( SCnjEntBuscarId ( p_cnjObj, p_idBuscar ) != 2 ) )
		{
			printf( "Error caso 2: el id 30 deberia estar en la posicion 2\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SCnjEntExisteValorId ( p_cnjObj, 10 ) != 1 ) || ( SCnjEntBuscarValorId ( p_cnjObj, 10 ) != 0 ) )
		{
			printf( "Error caso 3: el valor 10 deberia estar en la posicion 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Lo que no esta: menor que el minimo, intermedio y mayor que el maximo. */
		unsigned long ulAusentes [ 3 ] = { 5, 15, 99 };
		int iAus = 0;
		while ( iAus < 3 )
		{
			SEntEstablecerValorId ( p_entBuscar, ulAusentes [ iAus ] );
			SIdEstablecer ( p_idBuscar, ulAusentes [ iAus ] );
			if ( ( SCnjEntExiste ( p_cnjObj, p_entBuscar ) != 0 ) || ( SCnjEntBuscar ( p_cnjObj, p_entBuscar ) != -1 ) ||
				 ( SCnjEntPosicion ( p_cnjObj, p_entBuscar ) != -1 ) ||
				 ( SCnjEntExisteId ( p_cnjObj, p_idBuscar ) != 0 ) || ( SCnjEntBuscarId ( p_cnjObj, p_idBuscar ) != -1 ) ||
				 ( SCnjEntExisteValorId ( p_cnjObj, ulAusentes [ iAus ] ) != 0 ) ||
				 ( SCnjEntBuscarValorId ( p_cnjObj, ulAusentes [ iAus ] ) != -1 ) )
			{
				printf( "Error caso 4: el %lu no deberia encontrarse\n", ulAusentes [ iAus ] );
				iRes = BOOL_VAL_FALSO;
			}
			iAus = iAus + 1;
		}
		/* El id 0 no es un identificador asignado: nunca se encuentra. */
		if ( ( SCnjEntExisteValorId ( p_cnjObj, 0 ) != 0 ) || ( SCnjEntBuscarValorId ( p_cnjObj, 0 ) != -1 ) )
		{
			printf( "Error caso 5: el id 0 no deberia encontrarse\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Nulos: "no esta" es -1, no 0, que seria la primera posicion. */
		if ( ( SCnjEntExiste ( p_cnjObj, NULL ) != 0 ) || ( SCnjEntBuscar ( p_cnjObj, NULL ) != -1 ) ||
			 ( SCnjEntPosicion ( p_cnjObj, NULL ) != -1 ) ||
			 ( SCnjEntExisteId ( p_cnjObj, NULL ) != 0 ) || ( SCnjEntBuscarId ( p_cnjObj, NULL ) != -1 ) )
		{
			printf( "Error caso 6: con un dato nulo no deberia encontrarse nada\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SCnjEntBuscar ( NULL, p_entBuscar ) != -1 ) || ( SCnjEntBuscarValorId ( NULL, 10 ) != -1 ) ||
			 ( SCnjEntPosicion ( NULL, p_entBuscar ) != -1 ) )
		{
			printf( "Error caso 7: en un conjunto nulo buscar deberia devolver -1\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear el conjunto o los datos de busqueda\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SCnjEntDestruir ( &p_cnjObj );
	SEntDestruir ( &p_entBuscar );
	SIdDestruir ( &p_idBuscar );
# if ( defined ( MODO_DEPURACION ) )
	/* Las entidades de sonda de ExisteValorId y BuscarValorId se destruyen dentro. */
	if ( MemNumBloquesActuales () != ulBloquesAntes )
	{
		printf( "Error caso 8: quedan %ld bloques sin liberar\n", (long) ( MemNumBloquesActuales () - ulBloquesAntes ) );
		iRes = BOOL_VAL_FALSO;
	}
# endif
	return ( iRes );
}

static int TestSCnjEntEliminar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCnjEntEliminar 01:\n" );
# if ( defined ( MODO_DEPURACION ) )
	unsigned long ulBloquesAntes = MemNumBloquesActuales ();
# endif

	SConjuntoEntidades * p_cnjObj = SCnjEntCrear ();
	if ( ES_VALIDO ( p_cnjObj ) )
	{
		LlenarConjunto ( p_cnjObj );

		/* Eliminar destruye la entidad. */
		if ( SCnjEntEliminar ( p_cnjObj, 1 ) != 1 )
		{
			printf( "Error caso 1: se esperaba resultado 1 al eliminar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SCnjEntNumElementos ( p_cnjObj ) != 2 ) || ( SCnjEntExisteValorId ( p_cnjObj, 20 ) != 0 ) )
		{
			printf( "Error caso 2: tras eliminar el 20 ya no deberia estar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SCnjEntEliminar ( p_cnjObj, -1 ) != 0 ) || ( SCnjEntEliminar ( p_cnjObj, 2 ) != 0 ) )
		{
			printf( "Error caso 3: eliminar fuera de rango deberia devolver 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* El id eliminado puede volver a entrar. */
		if ( SCnjEntInsertar ( p_cnjObj, SEntCrear ( 20 ) ) != 1 )
		{
			printf( "Error caso 4: se esperaba poder reinsertar el 20\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SCnjEntVaciar ( p_cnjObj ) != 1 ) || ( SCnjEntEstaVacio ( p_cnjObj ) != 1 ) )
		{
			printf( "Error caso 5: tras vaciar el conjunto deberia estar vacio\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Tras vaciar sigue siendo utilizable. */
		LlenarConjunto ( p_cnjObj );
		if ( SCnjEntNumElementos ( p_cnjObj ) != 3 )
		{
			printf( "Error caso 6: tras vaciar deberia poder llenarse de nuevo\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el conjunto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SCnjEntDestruir ( &p_cnjObj );
# if ( defined ( MODO_DEPURACION ) )
	if ( MemNumBloquesActuales () != ulBloquesAntes )
	{
		printf( "Error caso 7: quedan %ld bloques sin liberar\n", (long) ( MemNumBloquesActuales () - ulBloquesAntes ) );
		iRes = BOOL_VAL_FALSO;
	}
# endif
	return ( iRes );
}

static int TestSCnjEntExtraer01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCnjEntExtraer 01:\n" );
# if ( defined ( MODO_DEPURACION ) )
	unsigned long ulBloquesAntes = MemNumBloquesActuales ();
# endif

	SConjuntoEntidades * p_cnjObj = SCnjEntCrear ();
	if ( ES_VALIDO ( p_cnjObj ) )
	{
		if ( ES_VALIDO ( SCnjEntExtraer ( p_cnjObj, 0 ) ) )
		{
			printf( "Error caso 1: extraer de un conjunto vacio deberia devolver nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		LlenarConjunto ( p_cnjObj );

		/* Sale la misma entidad, viva; desde ahora es del llamador. */
		SEntidad * p_entEsp = SCnjEntElemento ( p_cnjObj, 1 );
		SEntidad * p_entExt = SCnjEntExtraer ( p_cnjObj, 1 );
		if ( ES_NULO ( p_entExt ) || ( p_entExt != p_entEsp ) || ( ! IdEs ( p_entExt, 20 ) ) )
		{
			printf( "Error caso 2: se esperaba extraer el 20 de la posicion 1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SCnjEntNumElementos ( p_cnjObj ) != 2 ) || ( SCnjEntExiste ( p_cnjObj, p_entExt ) != 0 ) )
		{
			printf( "Error caso 3: tras extraer el 20 ya no deberia estar en el conjunto\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( SCnjEntExtraer ( p_cnjObj, -1 ) ) || ES_VALIDO ( SCnjEntExtraer ( p_cnjObj, 2 ) ) )
		{
			printf( "Error caso 4: extraer fuera de rango deberia devolver nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCnjEntNumElementos ( p_cnjObj ) != 2 )
		{
			printf( "Error caso 5: extraer fuera de rango no deberia cambiar el conjunto\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Se puede devolver al conjunto, que la toma otra vez y la coloca en su sitio. */
		if ( ES_VALIDO ( p_entExt ) )
		{
			if ( SCnjEntInsertar ( p_cnjObj, p_entExt ) != 1 )
			{
				printf( "Error caso 6: la entidad extraida deberia poder volver a insertarse\n" );
				iRes = BOOL_VAL_FALSO;
				SEntDestruir ( &p_entExt );
			}
			else if ( SCnjEntElemento ( p_cnjObj, 1 ) != p_entExt )
			{
				printf( "Error caso 7: al reinsertarla deberia volver a la posicion 1\n" );
				iRes = BOOL_VAL_FALSO;
			}
		}
		/* Una extraida que no se devuelve la destruye el llamador. */
		p_entExt = SCnjEntExtraer ( p_cnjObj, 0 );
		if ( ! IdEs ( p_entExt, 10 ) )
		{
			printf( "Error caso 8: extraer la posicion 0 deberia dar el 10\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SEntDestruir ( &p_entExt );
		if ( ES_VALIDO ( SCnjEntExtraer ( NULL, 0 ) ) )
		{
			printf( "Error caso 9: extraer de un conjunto nulo deberia devolver nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el conjunto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SCnjEntDestruir ( &p_cnjObj );
# if ( defined ( MODO_DEPURACION ) )
	if ( MemNumBloquesActuales () != ulBloquesAntes )
	{
		printf( "Error caso 10: quedan %ld bloques sin liberar\n", (long) ( MemNumBloquesActuales () - ulBloquesAntes ) );
		iRes = BOOL_VAL_FALSO;
	}
# endif
	return ( iRes );
}

static int TestSCnjEntInvalidos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCnjEntInvalidos 01:\n" );

	if ( ( SCnjEntEsValido ( NULL ) != 0 ) || ( SCnjEntNumElementos ( NULL ) != 0 ) || ( SCnjEntEstaVacio ( NULL ) != 1 ) )
	{
		printf( "Error caso 1: un conjunto nulo no es valido, tiene 0 elementos y esta vacio\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( SCnjEntElemento ( NULL, 0 ) ) || ES_VALIDO ( SCnjEntPrimero ( NULL ) ) || ES_VALIDO ( SCnjEntUltimo ( NULL ) ) )
	{
		printf( "Error caso 2: un conjunto nulo no tiene elementos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SEntidad * p_entObj = SEntCrear ( 1 );
	if ( SCnjEntInsertar ( NULL, p_entObj ) != -1 )
	{
		printf( "Error caso 3: insertar en un conjunto nulo deberia devolver -1\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SEntDestruir ( &p_entObj );
	if ( ( SCnjEntEliminar ( NULL, 0 ) != 0 ) || ( SCnjEntVaciar ( NULL ) != 0 ) )
	{
		printf( "Error caso 4: eliminar o vaciar un conjunto nulo deberia devolver 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SConjuntoEntidades * p_cnjNulo = NULL;
	SCnjEntDestruir ( &p_cnjNulo );
	SCnjEntDestruir ( NULL );
	return ( iRes );
}



int TestSConjuntoEntidades ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SConjuntoEntidades]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSCnjEntCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSCnjEntInsertar01 () == BOOL_VAL_CIERTO ) &&
			( TestSCnjEntBuscar01 () == BOOL_VAL_CIERTO ) &&
			( TestSCnjEntEliminar01 () == BOOL_VAL_CIERTO ) &&
			( TestSCnjEntExtraer01 () == BOOL_VAL_CIERTO ) &&
			( TestSCnjEntInvalidos01 () == BOOL_VAL_CIERTO ) )
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
