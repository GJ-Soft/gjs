#include "Base.h"

#include "SListaOrdenadaPtr.h"



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

static int ValorElem ( SListaOrdenadaPtr * p_lisObj, int iElem )
{
	return ( *( (int *) SLispOrdElemento ( p_lisObj, iElem ) ) );
}

static int ValorActual ( SListaOrdenadaPtr * p_lisObj )
{
	return ( *( (int *) SLispOrdActual ( p_lisObj ) ) );
}

/* Comprueba numero y orden de los valores, sin desreferenciar un nulo. */
static int VerificarOrdenada ( SListaOrdenadaPtr * p_lisObj, int * p_iEsperados, int iNum )
{
	int iRes = BOOL_VAL_CIERTO;

	if ( SLispOrdNumElementos ( p_lisObj ) != iNum )
	{
		printf( "  Verificacion: se esperaban %d elementos: %d\n", iNum, SLispOrdNumElementos ( p_lisObj ) );
		iRes = BOOL_VAL_FALSO;
	}
	int iPos = 0;
	while ( ( iPos < iNum ) && ( iRes == BOOL_VAL_CIERTO ) )
	{
		byte * p_byDato = SLispOrdElemento ( p_lisObj, iPos );
		if ( ES_NULO ( p_byDato ) || ( *( (int *) p_byDato ) != p_iEsperados [ iPos ] ) )
		{
			printf( "  Verificacion: en pos %d se esperaba %d\n", iPos, p_iEsperados [ iPos ] );
			iRes = BOOL_VAL_FALSO;
		}
		iPos = iPos + 1;
	}
	return ( iRes );
}

static int VerificarLista ( SListaPtr * p_lisObj, int * p_iEsperados, int iNum )
{
	int iRes = BOOL_VAL_CIERTO;

	if ( SLispNumElementos ( p_lisObj ) != iNum )
	{
		printf( "  Verificacion: se esperaban %d elementos: %d\n", iNum, SLispNumElementos ( p_lisObj ) );
		iRes = BOOL_VAL_FALSO;
	}
	int iPos = 0;
	while ( ( iPos < iNum ) && ( iRes == BOOL_VAL_CIERTO ) )
	{
		byte * p_byDato = SLispElemento ( p_lisObj, iPos );
		if ( ES_NULO ( p_byDato ) || ( *( (int *) p_byDato ) != p_iEsperados [ iPos ] ) )
		{
			printf( "  Verificacion: en pos %d se esperaba %d\n", iPos, p_iEsperados [ iPos ] );
			iRes = BOOL_VAL_FALSO;
		}
		iPos = iPos + 1;
	}
	return ( iRes );
}

/* SListaPtr sin ordenar, duena de sus datos. */
static SListaPtr * CrearListaEnteros ( int * p_iValores, int iNum )
{
	SListaPtr * p_lisObj = SLispCrear ();
	int iPos = 0;
	while ( ES_VALIDO ( p_lisObj ) && ( iPos < iNum ) )
	{
		SLispInsertarAlFinal ( p_lisObj, CrearDatoEntero ( p_iValores [ iPos ] ) );
		iPos = iPos + 1;
	}
	return ( p_lisObj );
}

/* Duplica sumando 100, para ver en el resultado que la copia la hizo ella. */
static byte * DuplicarEnteroMas100 ( byte * p_byDato )
{
	return ( CrearDatoEntero ( *( (int *) p_byDato ) + 100 ) );
}

/* Falla al copiar el 20: provoca una copia a medias. */
static byte * DuplicarFallaEn20 ( byte * p_byDato )
{
	byte * p_byRes;

	if ( *( (int *) p_byDato ) == 20 )
	{
		p_byRes = NULL;
	}
	else
	{
		p_byRes = CrearDatoEntero ( *( (int *) p_byDato ) );
	}
	return ( p_byRes );
}



static int TestSLispOrdInsertar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLispOrdInsertar 01:\n" );

	/* La memoria de los datos la gestiona el test ( liberacion desactivada ). */
	byte * p_d10 = CrearDatoEntero ( 10 );
	byte * p_d20 = CrearDatoEntero ( 20 );
	byte * p_d30 = CrearDatoEntero ( 30 );
	byte * p_q99 = CrearDatoEntero ( 99 );
	byte * p_q5 = CrearDatoEntero ( 5 );
	SListaOrdenadaPtr * p_lisObj = SLispOrdCrear ( CompararEnteros );
	if ( ES_VALIDO ( p_lisObj ) && ES_VALIDO ( p_d10 ) && ES_VALIDO ( p_d20 ) &&
		 ES_VALIDO ( p_d30 ) && ES_VALIDO ( p_q99 ) && ES_VALIDO ( p_q5 ) )
	{
		SLispOrdDesactivarLiberacionMemoria ( p_lisObj );

		if ( ( SLispOrdEsValida ( p_lisObj ) != 1 ) || ( SLispOrdEstaVacia ( p_lisObj ) != 1 ) )
		{
			printf( "Error caso 1: la lista recien creada deberia ser valida y estar vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Buscar en una lista vacia debe devolver -1 ( valida el arreglo de Buscar ). */
		if ( SLispOrdBuscar ( p_lisObj, p_d10 ) != -1 )
		{
			printf( "Error caso 2: buscar en una lista vacia deberia devolver -1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Se insertan en desorden; la lista los mantiene ordenados. */
		SLispOrdInsertarElem ( p_lisObj, p_d20 );
		SLispOrdInsertarElem ( p_lisObj, p_d10 );
		SLispOrdInsertarElem ( p_lisObj, p_d30 );
		if ( SLispOrdNumElementos ( p_lisObj ) != 3 )
		{
			printf( "Error caso 3: la lista deberia tener 3 elementos\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( ValorElem ( p_lisObj, 0 ) != 10 ) || ( ValorElem ( p_lisObj, 1 ) != 20 ) || ( ValorElem ( p_lisObj, 2 ) != 30 ) )
		{
			printf( "Error caso 4: los elementos deberian quedar ordenados ( 10, 20, 30 )\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Buscar: encontrado devuelve indice; no encontrado ( mayor o menor que todos ) devuelve -1. */
		if ( SLispOrdBuscar ( p_lisObj, p_d20 ) != 1 )
		{
			printf( "Error caso 5: buscar 20 deberia devolver el indice 1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLispOrdBuscar ( p_lisObj, p_q99 ) != -1 ) || ( SLispOrdBuscar ( p_lisObj, p_q5 ) != -1 ) )
		{
			printf( "Error caso 6: buscar valores fuera del rango deberia devolver -1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Eliminar el del medio ( 20 ). */
		SLispOrdEliminarElem ( p_lisObj, 1 );
		if ( ( SLispOrdNumElementos ( p_lisObj ) != 2 ) || ( ValorElem ( p_lisObj, 1 ) != 30 ) )
		{
			printf( "Error caso 7: tras eliminar el 20 deberian quedar 10 y 30\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear la lista o los datos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLispOrdDestruir ( &p_lisObj );
	/* El test libera sus propios datos. */
	MemLiberar ( (void **) &p_d10 );
	MemLiberar ( (void **) &p_d20 );
	MemLiberar ( (void **) &p_d30 );
	MemLiberar ( (void **) &p_q99 );
	MemLiberar ( (void **) &p_q5 );
	return ( iRes );
}

static int TestSLispOrdCursor01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLispOrdCursor 01:\n" );

	byte * p_d10 = CrearDatoEntero ( 10 );
	byte * p_d20 = CrearDatoEntero ( 20 );
	byte * p_d30 = CrearDatoEntero ( 30 );
	SListaOrdenadaPtr * p_lisObj = SLispOrdCrear ( CompararEnteros );
	if ( ES_VALIDO ( p_lisObj ) && ES_VALIDO ( p_d10 ) && ES_VALIDO ( p_d20 ) && ES_VALIDO ( p_d30 ) )
	{
		SLispOrdDesactivarLiberacionMemoria ( p_lisObj );
		SLispOrdInsertarElem ( p_lisObj, p_d30 );
		SLispOrdInsertarElem ( p_lisObj, p_d10 );
		SLispOrdInsertarElem ( p_lisObj, p_d20 );

		/* Recorrido con cursor: inicio -> siguiente -> final. */
		SLispOrdInicio ( p_lisObj );
		if ( ( ValorActual ( p_lisObj ) != 10 ) || ( SLispOrdEstaEnInicio ( p_lisObj ) != 1 ) )
		{
			printf( "Error caso 1: el inicio deberia ser 10\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLispOrdSiguiente ( p_lisObj );
		if ( ValorActual ( p_lisObj ) != 20 )
		{
			printf( "Error caso 2: el siguiente del inicio deberia ser 20\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLispOrdFinal ( p_lisObj );
		if ( ( ValorActual ( p_lisObj ) != 30 ) || ( SLispOrdEstaEnFinal ( p_lisObj ) != 1 ) )
		{
			printf( "Error caso 3: el final deberia ser 30\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear la lista o los datos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLispOrdDestruir ( &p_lisObj );
	MemLiberar ( (void **) &p_d10 );
	MemLiberar ( (void **) &p_d20 );
	MemLiberar ( (void **) &p_d30 );
	return ( iRes );
}

static int TestSLispOrdInvalidos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLispOrdInvalidos 01:\n" );

	if ( SLispOrdEsValida ( NULL ) != 0 )
	{
		printf( "Error caso 1: una lista nula no deberia ser valida\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SLispOrdNumElementos ( NULL ) != 0 )
	{
		printf( "Error caso 2: una lista nula deberia tener 0 elementos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SListaOrdenadaPtr * p_lisNula = NULL;
	SLispOrdDestruir ( &p_lisNula );
	return ( iRes );
}


/* Encapsular se queda con el comparador ( lo destruye la lista ) y, si falla,
   no lo toca: aqui uno no valido en la pila, que no se puede liberar. */
static int TestSLispOrdEncapsular01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLispOrdEncapsular 01:\n" );

	SComparador * p_cmpObj = SCmpCrear ( CompararEnteros );
	SListaOrdenadaPtr * p_lisObj = SLispOrdEncapsular ( p_cmpObj );
	if ( ES_VALIDO ( p_lisObj ) )
	{
		if ( ( SLispOrdEsValida ( p_lisObj ) != 1 ) || ( SLispOrdEstaVacia ( p_lisObj ) != 1 ) ||
			 ( p_lisObj->p_cmpObj != p_cmpObj ) || ( SLispOrdLiberacionMemoriaActivada ( p_lisObj ) != 1 ) )
		{
			printf( "Error caso 1: se esperaba una lista vacia, duena de sus datos y con ese comparador\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLispOrdInsertarElem ( p_lisObj, CrearDatoEntero ( 20 ) );
		SLispOrdInsertarElem ( p_lisObj, CrearDatoEntero ( 10 ) );
		int iEsp [ 2 ] = { 10, 20 };
		if ( VerificarOrdenada ( p_lisObj, iEsp, 2 ) != BOOL_VAL_CIERTO )
		{
			printf( "Error caso 2: se esperaba { 10, 20 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SComparador cmpMalo = { NULL };
		if ( ES_VALIDO ( SLispOrdEncapsular ( &cmpMalo ) ) || ES_VALIDO ( SLispOrdEncapsular ( NULL ) ) )
		{
			printf( "Error caso 3: con un comparador no valido o nulo se esperaba nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo encapsular\n" );
		iRes = BOOL_VAL_FALSO;
		SCmpDestruir ( &p_cmpObj );
	}
	/* Destruye tambien p_cmpObj. */
	SLispOrdDestruir ( &p_lisObj );
	return ( iRes );
}

/* Ordena copias de los datos, duena de ellas; la lista de valores no cambia.
   Si falla una copia se queda con lo copiado y deja ERR_COPIA_LISTA. */
static int TestSLispOrdCrearDesdeLista01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLispOrdCrearDesdeLista 01:\n" );

	int iVal [ 4 ] = { 30, 10, 20, 10 };
	SListaPtr * p_lisVal = CrearListaEnteros ( iVal, 4 );
	SListaPtr * p_lisVacia = SLispCrear ();
	SListaOrdenadaPtr * p_lisObj = NULL;
	SListaOrdenadaPtr * p_lisExt = NULL;
	SListaOrdenadaPtr * p_lisMedias = NULL;
	SListaOrdenadaPtr * p_lisDeVacia = NULL;
	if ( ES_VALIDO ( p_lisVal ) && ES_VALIDO ( p_lisVacia ) )
	{
		p_lisObj = SLispOrdCrearDesdeLista ( p_lisVal, CompararEnteros, sizeof ( int ) );
		int iEsp [ 4 ] = { 10, 10, 20, 30 };
		if ( ES_NULO ( p_lisObj ) || ( VerificarOrdenada ( p_lisObj, iEsp, 4 ) != BOOL_VAL_CIERTO ) ||
			 ( SLispOrdLiberacionMemoriaActivada ( p_lisObj ) != 1 ) )
		{
			printf( "Error caso 1: se esperaba { 10, 10, 20, 30 }, duena de sus datos\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( VerificarLista ( p_lisVal, iVal, 4 ) != BOOL_VAL_CIERTO ) ||
			 ( SLispOrdElemento ( p_lisObj, 3 ) == SLispElemento ( p_lisVal, 0 ) ) )
		{
			printf( "Error caso 2: los valores deberian quedar intactos y sin compartir datos\n" );
			iRes = BOOL_VAL_FALSO;
		}
		p_lisExt = SLispOrdCrearDesdeListaExt ( p_lisVal, CompararEnteros, DuplicarEnteroMas100 );
		int iEspExt [ 4 ] = { 110, 110, 120, 130 };
		if ( ES_NULO ( p_lisExt ) || ( VerificarOrdenada ( p_lisExt, iEspExt, 4 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 3: con fDuplicar se esperaba { 110, 110, 120, 130 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Se copian 30 y 10, falla el 20 y se para. */
		ErrLimpiar ();
		p_lisMedias = SLispOrdCrearDesdeListaExt ( p_lisVal, CompararEnteros, DuplicarFallaEn20 );
		int iEspMedias [ 2 ] = { 10, 30 };
		if ( ES_NULO ( p_lisMedias ) || ( VerificarOrdenada ( p_lisMedias, iEspMedias, 2 ) != BOOL_VAL_CIERTO ) ||
			 ( ErrCodigo () != ERR_COPIA_LISTA ) )
		{
			printf( "Error caso 4: se esperaba { 10, 30 } con ERR_COPIA_LISTA (Error=%d)\n", ErrCodigo () );
			iRes = BOOL_VAL_FALSO;
		}
		ErrLimpiar ();
		p_lisDeVacia = SLispOrdCrearDesdeLista ( p_lisVacia, CompararEnteros, sizeof ( int ) );
		if ( ES_NULO ( p_lisDeVacia ) || ( SLispOrdEsValida ( p_lisDeVacia ) != 1 ) ||
			 ( SLispOrdNumElementos ( p_lisDeVacia ) != 0 ) )
		{
			printf( "Error caso 5: de una lista vacia se esperaba otra vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( SLispOrdCrearDesdeLista ( NULL, CompararEnteros, sizeof ( int ) ) ) ||
			 ES_VALIDO ( SLispOrdCrearDesdeLista ( p_lisVal, NULL, sizeof ( int ) ) ) ||
			 ES_VALIDO ( SLispOrdCrearDesdeLista ( p_lisVal, CompararEnteros, 0 ) ) ||
			 ES_VALIDO ( SLispOrdCrearDesdeListaExt ( p_lisVal, CompararEnteros, NULL ) ) )
		{
			printf( "Error caso 6: sin lista, funcion, tamano o fDuplicar se esperaba nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear las listas\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLispDestruir ( &p_lisVal );
	SLispDestruir ( &p_lisVacia );
	SLispOrdDestruir ( &p_lisObj );
	SLispOrdDestruir ( &p_lisExt );
	SLispOrdDestruir ( &p_lisMedias );
	SLispOrdDestruir ( &p_lisDeVacia );
	ErrLimpiar ();
	return ( iRes );
}

/* La copia tiene su propio comparador y sus propios datos, y es duena de ellos
   aunque el original no lo sea. El cursor del original no se mueve. */
static int TestSLispOrdDuplicar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLispOrdDuplicar 01:\n" );

	int iVal [ 3 ] = { 30, 10, 20 };
	SListaPtr * p_lisVal = CrearListaEnteros ( iVal, 3 );
	SListaOrdenadaPtr * p_lisObj = SLispOrdCrearDesdeLista ( p_lisVal, CompararEnteros, sizeof ( int ) );
	SListaOrdenadaPtr * p_lisAjena = SLispOrdCrear ( CompararEnteros );
	byte * p_byAjeno = CrearDatoEntero ( 5 );
	SListaOrdenadaPtr * p_lisDup = NULL;
	SListaOrdenadaPtr * p_lisExt = NULL;
	SListaOrdenadaPtr * p_lisDupAjena = NULL;
	if ( ES_VALIDO ( p_lisObj ) && ES_VALIDO ( p_lisAjena ) && ES_VALIDO ( p_byAjeno ) )
	{
		SLispOrdMoverA ( p_lisObj, 1 );
		p_lisDup = SLispOrdDuplicar ( p_lisObj, sizeof ( int ) );
		p_lisExt = SLispOrdDuplicarExt ( p_lisObj, DuplicarEnteroMas100 );
		if ( SLispOrdPosicion ( p_lisObj ) != 1 )
		{
			printf( "Error caso 1: el cursor del original deberia seguir en 1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		int iEsp [ 3 ] = { 10, 20, 30 };
		if ( ES_NULO ( p_lisDup ) || ( p_lisDup == p_lisObj ) ||
			 ( VerificarOrdenada ( p_lisDup, iEsp, 3 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 2: la copia deberia ser otra lista con { 10, 20, 30 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		else
		{
			if ( ( p_lisDup->p_cmpObj == p_lisObj->p_cmpObj ) ||
				 ( SLispOrdElemento ( p_lisDup, 0 ) == SLispOrdElemento ( p_lisObj, 0 ) ) )
			{
				printf( "Error caso 3: la copia no deberia compartir comparador ni datos\n" );
				iRes = BOOL_VAL_FALSO;
			}
			SLispOrdDestruir ( &p_lisObj );
			SLispOrdInsertarElem ( p_lisDup, CrearDatoEntero ( 15 ) );
			int iEsp2 [ 4 ] = { 10, 15, 20, 30 };
			if ( VerificarOrdenada ( p_lisDup, iEsp2, 4 ) != BOOL_VAL_CIERTO )
			{
				printf( "Error caso 4: sin el original la copia deberia seguir ordenando\n" );
				iRes = BOOL_VAL_FALSO;
			}
		}
		int iEspExt [ 3 ] = { 110, 120, 130 };
		if ( ES_NULO ( p_lisExt ) || ( VerificarOrdenada ( p_lisExt, iEspExt, 3 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 5: con fDuplicar se esperaba { 110, 120, 130 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* El dato de la ajena es del test: la copia tiene el suyo y lo libera. */
		SLispOrdDesactivarLiberacionMemoria ( p_lisAjena );
		SLispOrdInsertarElem ( p_lisAjena, p_byAjeno );
		p_lisDupAjena = SLispOrdDuplicar ( p_lisAjena, sizeof ( int ) );
		int iEspAjena [ 1 ] = { 5 };
		if ( ES_NULO ( p_lisDupAjena ) || ( VerificarOrdenada ( p_lisDupAjena, iEspAjena, 1 ) != BOOL_VAL_CIERTO ) ||
			 ( SLispOrdElemento ( p_lisDupAjena, 0 ) == p_byAjeno ) ||
			 ( SLispOrdLiberacionMemoriaActivada ( p_lisDupAjena ) != 1 ) )
		{
			printf( "Error caso 6: la copia de una lista no duena deberia tener sus datos y liberarlos\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( SLispOrdDuplicar ( NULL, sizeof ( int ) ) ) ||
			 ES_VALIDO ( SLispOrdDuplicarExt ( NULL, DuplicarEnteroMas100 ) ) ||
			 ES_VALIDO ( SLispOrdDuplicarExt ( p_lisDup, NULL ) ) ||
			 ES_VALIDO ( SLispOrdDuplicar ( p_lisDup, 0 ) ) )
		{
			printf( "Error caso 7: con una lista nula, sin fDuplicar o sin bytes se esperaba nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear las listas\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLispDestruir ( &p_lisVal );
	SLispOrdDestruir ( &p_lisObj );
	SLispOrdDestruir ( &p_lisAjena );
	SLispOrdDestruir ( &p_lisDup );
	SLispOrdDestruir ( &p_lisExt );
	SLispOrdDestruir ( &p_lisDupAjena );
	MemLiberar ( (void **) &p_byAjeno );
	ErrLimpiar ();
	return ( iRes );
}

static int TestSLispOrdDuplicarLista01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLispOrdDuplicarLista 01:\n" );

	int iVal [ 3 ] = { 30, 10, 20 };
	SListaPtr * p_lisVal = CrearListaEnteros ( iVal, 3 );
	SListaOrdenadaPtr * p_lisObj = SLispOrdCrearDesdeLista ( p_lisVal, CompararEnteros, sizeof ( int ) );
	SListaPtr * p_lisRes = NULL;
	SListaPtr * p_lisExt = NULL;
	if ( ES_VALIDO ( p_lisObj ) )
	{
		p_lisRes = SLispOrdDuplicarLista ( p_lisObj, sizeof ( int ) );
		int iEsp [ 3 ] = { 10, 20, 30 };
		if ( ES_NULO ( p_lisRes ) || ( VerificarLista ( p_lisRes, iEsp, 3 ) != BOOL_VAL_CIERTO ) ||
			 ( SLispLiberacionMemoriaActivada ( p_lisRes ) != 1 ) )
		{
			printf( "Error caso 1: se esperaba una SListaPtr con { 10, 20, 30 }, duena de sus datos\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLispElemento ( p_lisRes, 0 ) == SLispOrdElemento ( p_lisObj, 0 ) ) ||
			 ( p_lisRes == p_lisObj->p_lispContenido ) )
		{
			printf( "Error caso 2: se esperaba una copia, no el contenido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		p_lisExt = SLispOrdDuplicarListaExt ( p_lisObj, DuplicarEnteroMas100 );
		int iEspExt [ 3 ] = { 110, 120, 130 };
		if ( ES_NULO ( p_lisExt ) || ( VerificarLista ( p_lisExt, iEspExt, 3 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 3: con fDuplicar se esperaba { 110, 120, 130 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( SLispOrdDuplicarLista ( NULL, sizeof ( int ) ) ) ||
			 ES_VALIDO ( SLispOrdDuplicarListaExt ( NULL, DuplicarEnteroMas100 ) ) ||
			 ES_VALIDO ( SLispOrdDuplicarListaExt ( p_lisObj, NULL ) ) )
		{
			printf( "Error caso 4: con una lista nula o sin fDuplicar se esperaba nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la lista\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLispDestruir ( &p_lisVal );
	SLispOrdDestruir ( &p_lisObj );
	SLispDestruir ( &p_lisRes );
	SLispDestruir ( &p_lisExt );
	ErrLimpiar ();
	return ( iRes );
}

/* Compara por decenas: 11 y 13 son iguales. Para ver que manda el comparador. */
static int CompararDecenas ( void * p_v1, void * p_v2 )
{
	int iRes;
	int i1 = *( (int *) p_v1 ) / 10;
	int i2 = *( (int *) p_v2 ) / 10;

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

/* Ordenada con copias de los valores, duena de ellas. */
static SListaOrdenadaPtr * CrearOrdenadaEnteros ( int * p_iValores, int iNum, PFUNINTPVPV fComparar )
{
	SListaPtr * p_lisVal = CrearListaEnteros ( p_iValores, iNum );
	SListaOrdenadaPtr * p_lisRes = SLispOrdCrearDesdeLista ( p_lisVal, fComparar, sizeof ( int ) );
	SLispDestruir ( &p_lisVal );
	return ( p_lisRes );
}

/* Vacia, con su propio comparador: sigue ordenando sin el ejemplo. */
static int TestSLispOrdCrearIgual01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLispOrdCrearIgual 01:\n" );

	int iVal [ 2 ] = { 30, 10 };
	SListaOrdenadaPtr * p_lisEje = CrearOrdenadaEnteros ( iVal, 2, CompararEnteros );
	SListaOrdenadaPtr * p_lisObj = NULL;
	if ( ES_VALIDO ( p_lisEje ) )
	{
		p_lisObj = SLispOrdCrearIgual ( p_lisEje );
		if ( ES_NULO ( p_lisObj ) || ( SLispOrdEsValida ( p_lisObj ) != 1 ) ||
			 ( SLispOrdNumElementos ( p_lisObj ) != 0 ) )
		{
			printf( "Error caso 1: se esperaba una lista valida y vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		else
		{
			if ( p_lisObj->p_cmpObj == p_lisEje->p_cmpObj )
			{
				printf( "Error caso 2: no deberia compartir el comparador\n" );
				iRes = BOOL_VAL_FALSO;
			}
			SLispOrdDestruir ( &p_lisEje );
			SLispOrdInsertarElem ( p_lisObj, CrearDatoEntero ( 20 ) );
			SLispOrdInsertarElem ( p_lisObj, CrearDatoEntero ( 5 ) );
			int iEsp [ 2 ] = { 5, 20 };
			if ( VerificarOrdenada ( p_lisObj, iEsp, 2 ) != BOOL_VAL_CIERTO )
			{
				printf( "Error caso 3: sin el ejemplo deberia seguir ordenando\n" );
				iRes = BOOL_VAL_FALSO;
			}
		}
		if ( ES_VALIDO ( SLispOrdCrearIgual ( NULL ) ) )
		{
			printf( "Error caso 4: con una lista nula se esperaba nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la lista\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLispOrdDestruir ( &p_lisEje );
	SLispOrdDestruir ( &p_lisObj );
	return ( iRes );
}

/* Las dos formas, con SListaOrdenadaPtr y con SListaPtr. El cursor no se mueve. */
static int TestSLispOrdExistenTodos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLispOrdExistenTodos 01:\n" );

	int iObj [ 3 ] = { 30, 10, 20 };
	int iTodos [ 2 ] = { 30, 10 };
	int iAlguno [ 2 ] = { 40, 10 };
	int iNinguno [ 2 ] = { 50, 40 };
	SListaOrdenadaPtr * p_lisObj = CrearOrdenadaEnteros ( iObj, 3, CompararEnteros );
	SListaOrdenadaPtr * p_lisTodos = CrearOrdenadaEnteros ( iTodos, 2, CompararEnteros );
	SListaOrdenadaPtr * p_lisAlguno = CrearOrdenadaEnteros ( iAlguno, 2, CompararEnteros );
	SListaOrdenadaPtr * p_lisNinguno = CrearOrdenadaEnteros ( iNinguno, 2, CompararEnteros );
	SListaOrdenadaPtr * p_lisVacia = SLispOrdCrear ( CompararEnteros );
	SListaPtr * p_lisTodosL = CrearListaEnteros ( iTodos, 2 );
	SListaPtr * p_lisAlgunoL = CrearListaEnteros ( iAlguno, 2 );
	SListaPtr * p_lisNingunoL = CrearListaEnteros ( iNinguno, 2 );
	SListaPtr * p_lisVaciaL = SLispCrear ();
	if ( ES_VALIDO ( p_lisObj ) && ES_VALIDO ( p_lisTodos ) && ES_VALIDO ( p_lisAlguno ) &&
		 ES_VALIDO ( p_lisNinguno ) && ES_VALIDO ( p_lisVacia ) && ES_VALIDO ( p_lisTodosL ) &&
		 ES_VALIDO ( p_lisAlgunoL ) && ES_VALIDO ( p_lisNingunoL ) && ES_VALIDO ( p_lisVaciaL ) )
	{
		SLispOrdMoverA ( p_lisObj, 1 );
		if ( ( SLispOrdExistenTodos ( p_lisObj, p_lisTodos ) != 1 ) ||
			 ( SLispOrdExisteAlguno ( p_lisObj, p_lisTodos ) != 1 ) )
		{
			printf( "Error caso 1: { 10, 30 } estan todos\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLispOrdExistenTodos ( p_lisObj, p_lisAlguno ) != 0 ) ||
			 ( SLispOrdExisteAlguno ( p_lisObj, p_lisAlguno ) != 1 ) )
		{
			printf( "Error caso 2: de { 10, 40 } solo esta alguno\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLispOrdExistenTodos ( p_lisObj, p_lisNinguno ) != 0 ) ||
			 ( SLispOrdExisteAlguno ( p_lisObj, p_lisNinguno ) != 0 ) )
		{
			printf( "Error caso 3: de { 40, 50 } no esta ninguno\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLispOrdExistenTodos ( p_lisObj, p_lisVacia ) != 1 ) ||
			 ( SLispOrdExisteAlguno ( p_lisObj, p_lisVacia ) != 0 ) )
		{
			printf( "Error caso 4: con una vacia, todos 1 y alguno 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLispOrdExistenTodosLista ( p_lisObj, p_lisTodosL ) != 1 ) ||
			 ( SLispOrdExisteAlgunoLista ( p_lisObj, p_lisTodosL ) != 1 ) ||
			 ( SLispOrdExistenTodosLista ( p_lisObj, p_lisAlgunoL ) != 0 ) ||
			 ( SLispOrdExisteAlgunoLista ( p_lisObj, p_lisAlgunoL ) != 1 ) ||
			 ( SLispOrdExistenTodosLista ( p_lisObj, p_lisNingunoL ) != 0 ) ||
			 ( SLispOrdExisteAlgunoLista ( p_lisObj, p_lisNingunoL ) != 0 ) ||
			 ( SLispOrdExistenTodosLista ( p_lisObj, p_lisVaciaL ) != 1 ) ||
			 ( SLispOrdExisteAlgunoLista ( p_lisObj, p_lisVaciaL ) != 0 ) )
		{
			printf( "Error caso 5: las de SListaPtr deberian dar lo mismo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLispOrdExistenTodos ( p_lisObj, NULL ) != 0 ) ||
			 ( SLispOrdExisteAlguno ( p_lisObj, NULL ) != 0 ) ||
			 ( SLispOrdExistenTodos ( NULL, p_lisTodos ) != 0 ) ||
			 ( SLispOrdExisteAlguno ( NULL, p_lisTodos ) != 0 ) ||
			 ( SLispOrdExistenTodosLista ( p_lisObj, NULL ) != 0 ) ||
			 ( SLispOrdExisteAlgunoLista ( NULL, p_lisTodosL ) != 0 ) )
		{
			printf( "Error caso 6: con una lista nula se esperaba 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLispOrdPosicion ( p_lisObj ) != 1 )
		{
			printf( "Error caso 7: el cursor deberia seguir en 1\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear las listas\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLispOrdDestruir ( &p_lisObj );
	SLispOrdDestruir ( &p_lisTodos );
	SLispOrdDestruir ( &p_lisAlguno );
	SLispOrdDestruir ( &p_lisNinguno );
	SLispOrdDestruir ( &p_lisVacia );
	SLispDestruir ( &p_lisTodosL );
	SLispDestruir ( &p_lisAlgunoL );
	SLispDestruir ( &p_lisNingunoL );
	SLispDestruir ( &p_lisVaciaL );
	return ( iRes );
}

/* Mueven: los datos son los mismos y el origen queda vacio. */
static int TestSLispOrdInsertarLista01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLispOrdInsertarLista 01:\n" );

	int iObj [ 2 ] = { 30, 10 };
	int iVal [ 3 ] = { 40, 20, 5 };
	SListaOrdenadaPtr * p_lisObj = CrearOrdenadaEnteros ( iObj, 2, CompararEnteros );
	SListaOrdenadaPtr * p_lisValOrd = CrearOrdenadaEnteros ( iVal, 3, CompararEnteros );
	SListaPtr * p_lisVal = CrearListaEnteros ( iVal, 3 );
	if ( ES_VALIDO ( p_lisObj ) && ES_VALIDO ( p_lisValOrd ) && ES_VALIDO ( p_lisVal ) )
	{
		byte * p_by5 = SLispOrdElemento ( p_lisValOrd, 0 );
		if ( SLispOrdInsertarListaOrd ( p_lisObj, p_lisValOrd ) != 1 )
		{
			printf( "Error caso 1: se esperaba 1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		int iEsp [ 5 ] = { 5, 10, 20, 30, 40 };
		if ( VerificarOrdenada ( p_lisObj, iEsp, 5 ) != BOOL_VAL_CIERTO )
		{
			printf( "Error caso 2: se esperaba { 5, 10, 20, 30, 40 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLispOrdNumElementos ( p_lisValOrd ) != 0 ) || ( SLispOrdElemento ( p_lisObj, 0 ) != p_by5 ) )
		{
			printf( "Error caso 3: los datos se deberian haber movido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		byte * p_by40 = SLispElemento ( p_lisVal, 0 );
		if ( SLispOrdInsertarLista ( p_lisObj, p_lisVal ) != 1 )
		{
			printf( "Error caso 4: se esperaba 1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		int iEsp2 [ 8 ] = { 5, 5, 10, 20, 20, 30, 40, 40 };
		if ( VerificarOrdenada ( p_lisObj, iEsp2, 8 ) != BOOL_VAL_CIERTO )
		{
			printf( "Error caso 5: se esperaba { 5, 5, 10, 20, 20, 30, 40, 40 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Los iguales van detras de los que ya estaban. */
		if ( ( SLispNumElementos ( p_lisVal ) != 0 ) || ( SLispOrdElemento ( p_lisObj, 7 ) != p_by40 ) )
		{
			printf( "Error caso 6: los datos se deberian haber movido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLispOrdInsertarListaOrd ( p_lisObj, p_lisValOrd ) != 1 ) ||
			 ( SLispOrdInsertarLista ( p_lisObj, p_lisVal ) != 1 ) ||
			 ( SLispOrdNumElementos ( p_lisObj ) != 8 ) )
		{
			printf( "Error caso 7: de una vacia se esperaba 1 sin cambios\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLispOrdInsertarListaOrd ( p_lisObj, p_lisObj ) != 0 ) ||
			 ( SLispOrdInsertarLista ( p_lisObj, p_lisObj->p_lispContenido ) != 0 ) ||
			 ( VerificarOrdenada ( p_lisObj, iEsp2, 8 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 8: con la misma lista se esperaba 0 sin cambios\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLispOrdInsertarListaOrd ( p_lisObj, NULL ) != 0 ) ||
			 ( SLispOrdInsertarListaOrd ( NULL, p_lisValOrd ) != 0 ) ||
			 ( SLispOrdInsertarLista ( p_lisObj, NULL ) != 0 ) ||
			 ( SLispOrdInsertarLista ( NULL, p_lisVal ) != 0 ) )
		{
			printf( "Error caso 9: con una lista nula se esperaba 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear las listas\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLispOrdDestruir ( &p_lisObj );
	SLispOrdDestruir ( &p_lisValOrd );
	SLispDestruir ( &p_lisVal );
	return ( iRes );
}

/* Copian ( iNumBytes o fDuplicar ): el origen no cambia y los datos son otros. */
static int TestSLispOrdInsertarListaDup01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLispOrdInsertarListaDup 01:\n" );

	int iObj [ 2 ] = { 30, 10 };
	int iVal [ 2 ] = { 40, 20 };
	int iFalla [ 3 ] = { 10, 20, 30 };
	SListaOrdenadaPtr * p_lisObj = CrearOrdenadaEnteros ( iObj, 2, CompararEnteros );
	SListaOrdenadaPtr * p_lisExt = CrearOrdenadaEnteros ( iObj, 2, CompararEnteros );
	SListaOrdenadaPtr * p_lisFalla = SLispOrdCrear ( CompararEnteros );
	SListaOrdenadaPtr * p_lisValOrd = CrearOrdenadaEnteros ( iVal, 2, CompararEnteros );
	SListaPtr * p_lisVal = CrearListaEnteros ( iVal, 2 );
	SListaPtr * p_lisValFalla = CrearListaEnteros ( iFalla, 3 );
	if ( ES_VALIDO ( p_lisObj ) && ES_VALIDO ( p_lisExt ) && ES_VALIDO ( p_lisFalla ) &&
		 ES_VALIDO ( p_lisValOrd ) && ES_VALIDO ( p_lisVal ) && ES_VALIDO ( p_lisValFalla ) )
	{
		if ( SLispOrdInsertarListaOrdDup ( p_lisObj, p_lisValOrd, sizeof ( int ) ) != 1 )
		{
			printf( "Error caso 1: se esperaba 1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		int iEsp [ 4 ] = { 10, 20, 30, 40 };
		int iOrd [ 2 ] = { 20, 40 };
		if ( ( VerificarOrdenada ( p_lisObj, iEsp, 4 ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarOrdenada ( p_lisValOrd, iOrd, 2 ) != BOOL_VAL_CIERTO ) ||
			 ( SLispOrdElemento ( p_lisObj, 1 ) == SLispOrdElemento ( p_lisValOrd, 0 ) ) )
		{
			printf( "Error caso 2: se esperaban copias en { 10, 20, 30, 40 } y el origen igual\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLispOrdInsertarListaDup ( p_lisObj, p_lisVal, sizeof ( int ) ) != 1 )
		{
			printf( "Error caso 3: se esperaba 1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		int iEsp2 [ 6 ] = { 10, 20, 20, 30, 40, 40 };
		if ( ( VerificarOrdenada ( p_lisObj, iEsp2, 6 ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarLista ( p_lisVal, iVal, 2 ) != BOOL_VAL_CIERTO ) ||
			 ( SLispOrdElemento ( p_lisObj, 5 ) == SLispElemento ( p_lisVal, 0 ) ) )
		{
			printf( "Error caso 4: se esperaban copias en { 10, 20, 20, 30, 40, 40 } y el origen igual\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* La Ext copia con fDuplicar: los valores llegan con 100 mas. */
		if ( ( SLispOrdInsertarListaOrdDupExt ( p_lisExt, p_lisValOrd, DuplicarEnteroMas100 ) != 1 ) ||
			 ( SLispOrdInsertarListaDupExt ( p_lisExt, p_lisVal, DuplicarEnteroMas100 ) != 1 ) )
		{
			printf( "Error caso 5: se esperaba 1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		int iEsp3 [ 6 ] = { 10, 30, 120, 120, 140, 140 };
		if ( VerificarOrdenada ( p_lisExt, iEsp3, 6 ) != BOOL_VAL_CIERTO )
		{
			printf( "Error caso 6: se esperaba { 10, 30, 120, 120, 140, 140 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		ErrLimpiar ();
		int iEsp4 [ 1 ] = { 10 };
		if ( ( SLispOrdInsertarListaDupExt ( p_lisFalla, p_lisValFalla, DuplicarFallaEn20 ) != 0 ) ||
			 ( ErrCodigo () != ERR_COPIA_OBJETO ) ||
			 ( VerificarOrdenada ( p_lisFalla, iEsp4, 1 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 7: al fallar en el 20 se esperaba 0, ERR_COPIA_OBJETO y { 10 } (Error=%d)\n", ErrCodigo () );
			iRes = BOOL_VAL_FALSO;
		}
		ErrLimpiar ();
		if ( ( SLispOrdInsertarListaDup ( p_lisFalla, p_lisVal, 0 ) != 0 ) ||
			 ( ErrCodigo () != ERR_COPIA_OBJETO ) )
		{
			printf( "Error caso 8: sin bytes se esperaba 0 con ERR_COPIA_OBJETO (Error=%d)\n", ErrCodigo () );
			iRes = BOOL_VAL_FALSO;
		}
		ErrLimpiar ();
		if ( ( SLispOrdInsertarListaOrdDup ( p_lisObj, p_lisObj, sizeof ( int ) ) != 0 ) ||
			 ( SLispOrdInsertarListaDup ( p_lisObj, p_lisObj->p_lispContenido, sizeof ( int ) ) != 0 ) ||
			 ( SLispOrdInsertarListaOrdDupExt ( p_lisObj, p_lisObj, DuplicarEnteroMas100 ) != 0 ) ||
			 ( SLispOrdInsertarListaDupExt ( p_lisObj, p_lisObj->p_lispContenido, DuplicarEnteroMas100 ) != 0 ) ||
			 ( VerificarOrdenada ( p_lisObj, iEsp2, 6 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 9: con la misma lista se esperaba 0 sin cambios\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLispOrdInsertarListaOrdDup ( p_lisObj, NULL, sizeof ( int ) ) != 0 ) ||
			 ( SLispOrdInsertarListaDup ( NULL, p_lisVal, sizeof ( int ) ) != 0 ) ||
			 ( SLispOrdInsertarListaOrdDupExt ( NULL, p_lisValOrd, DuplicarEnteroMas100 ) != 0 ) ||
			 ( SLispOrdInsertarListaDupExt ( p_lisObj, NULL, DuplicarEnteroMas100 ) != 0 ) )
		{
			printf( "Error caso 10: con una lista nula se esperaba 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear las listas\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLispOrdDestruir ( &p_lisObj );
	SLispOrdDestruir ( &p_lisExt );
	SLispOrdDestruir ( &p_lisFalla );
	SLispOrdDestruir ( &p_lisValOrd );
	SLispDestruir ( &p_lisVal );
	SLispDestruir ( &p_lisValFalla );
	ErrLimpiar ();
	return ( iRes );
}

/* Saca todas las apariciones de cada valor, moviendolas, a una lista nueva que
   hereda la liberacion. */
static int TestSLispOrdExtraerLista01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLispOrdExtraerLista 01:\n" );

	int iObj [ 6 ] = { 40, 20, 10, 30, 20, 20 };
	int iValOrd [ 3 ] = { 50, 40, 20 };
	int iVal [ 4 ] = { 20, 10, 20, 50 };
	int iAjena [ 1 ] = { 20 };
	SListaOrdenadaPtr * p_lisObj = CrearOrdenadaEnteros ( iObj, 6, CompararEnteros );
	SListaOrdenadaPtr * p_lisValOrd = CrearOrdenadaEnteros ( iValOrd, 3, CompararEnteros );
	SListaPtr * p_lisVal = CrearListaEnteros ( iVal, 4 );
	SListaPtr * p_lisValAjena = CrearListaEnteros ( iAjena, 1 );
	/* Datos del test: la lista no es duena de ellos. */
	byte * p_d10 = CrearDatoEntero ( 10 );
	byte * p_d20 = CrearDatoEntero ( 20 );
	byte * p_d20b = CrearDatoEntero ( 20 );
	SListaOrdenadaPtr * p_lisAjena = SLispOrdCrear ( CompararEnteros );
	SListaOrdenadaPtr * p_lisRes = NULL;
	SListaOrdenadaPtr * p_lisRes2 = NULL;
	SListaOrdenadaPtr * p_lisRes3 = NULL;
	if ( ES_VALIDO ( p_lisObj ) && ES_VALIDO ( p_lisValOrd ) && ES_VALIDO ( p_lisVal ) &&
		 ES_VALIDO ( p_lisValAjena ) && ES_VALIDO ( p_lisAjena ) )
	{
		/* p_lisObj = { 10, 20, 20, 20, 30, 40 } */
		byte * p_by40 = SLispOrdElemento ( p_lisObj, 5 );
		p_lisRes = SLispOrdExtraerListaOrd ( p_lisObj, p_lisValOrd );
		int iEsp [ 4 ] = { 20, 20, 20, 40 };
		if ( ES_NULO ( p_lisRes ) || ( VerificarOrdenada ( p_lisRes, iEsp, 4 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 1: se esperaba { 20, 20, 20, 40 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		else
		{
			if ( ( SLispOrdElemento ( p_lisRes, 3 ) != p_by40 ) || ( p_lisRes->p_cmpObj == p_lisObj->p_cmpObj ) ||
				 ( SLispOrdLiberacionMemoriaActivada ( p_lisRes ) != 1 ) )
			{
				printf( "Error caso 2: se esperaba el mismo dato, otro comparador y la liberacion activada\n" );
				iRes = BOOL_VAL_FALSO;
			}
		}
		int iQueda [ 2 ] = { 10, 30 };
		if ( ( VerificarOrdenada ( p_lisObj, iQueda, 2 ) != BOOL_VAL_CIERTO ) ||
			 ( SLispOrdNumElementos ( p_lisValOrd ) != 3 ) )
		{
			printf( "Error caso 3: deberian quedar { 10, 30 } y los valores sin tocar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		p_lisRes2 = SLispOrdExtraerLista ( p_lisObj, p_lisVal );
		int iEsp2 [ 1 ] = { 10 };
		int iQueda2 [ 1 ] = { 30 };
		if ( ES_NULO ( p_lisRes2 ) || ( VerificarOrdenada ( p_lisRes2, iEsp2, 1 ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarOrdenada ( p_lisObj, iQueda2, 1 ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarLista ( p_lisVal, iVal, 4 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 4: se esperaba { 10 } y que quedara { 30 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLispOrdDesactivarLiberacionMemoria ( p_lisAjena );
		SLispOrdInsertarElem ( p_lisAjena, p_d10 );
		SLispOrdInsertarElem ( p_lisAjena, p_d20 );
		SLispOrdInsertarElem ( p_lisAjena, p_d20b );
		p_lisRes3 = SLispOrdExtraerLista ( p_lisAjena, p_lisValAjena );
		if ( ES_NULO ( p_lisRes3 ) || ( SLispOrdNumElementos ( p_lisRes3 ) != 2 ) ||
			 ( SLispOrdElemento ( p_lisRes3, 0 ) != p_d20 ) ||
			 ( SLispOrdElemento ( p_lisRes3, 1 ) != p_d20b ) ||
			 ( SLispOrdLiberacionMemoriaActivada ( p_lisRes3 ) != 0 ) )
		{
			printf( "Error caso 5: de una lista sin liberacion se esperaban los dos 20 en otra sin liberacion\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( SLispOrdExtraerListaOrd ( p_lisObj, p_lisObj ) ) ||
			 ES_VALIDO ( SLispOrdExtraerLista ( p_lisObj, p_lisObj->p_lispContenido ) ) ||
			 ( VerificarOrdenada ( p_lisObj, iQueda2, 1 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 6: con la misma lista se esperaba nulo sin cambios\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( SLispOrdExtraerListaOrd ( p_lisObj, NULL ) ) ||
			 ES_VALIDO ( SLispOrdExtraerListaOrd ( NULL, p_lisValOrd ) ) ||
			 ES_VALIDO ( SLispOrdExtraerLista ( p_lisObj, NULL ) ) ||
			 ES_VALIDO ( SLispOrdExtraerLista ( NULL, p_lisVal ) ) )
		{
			printf( "Error caso 7: con una lista nula se esperaba nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear las listas\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLispOrdDestruir ( &p_lisObj );
	SLispOrdDestruir ( &p_lisValOrd );
	SLispDestruir ( &p_lisVal );
	SLispDestruir ( &p_lisValAjena );
	SLispOrdDestruir ( &p_lisAjena );
	SLispOrdDestruir ( &p_lisRes );
	SLispOrdDestruir ( &p_lisRes2 );
	SLispOrdDestruir ( &p_lisRes3 );
	MemLiberar ( (void **) &p_d10 );
	MemLiberar ( (void **) &p_d20 );
	MemLiberar ( (void **) &p_d20b );
	return ( iRes );
}

/* La union es la concatenacion, ordenada: lo comun sale dos veces. */
static int TestSLispOrdUnion01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLispOrdUnion 01:\n" );

	int iVal1 [ 2 ] = { 30, 10 };
	int iVal2 [ 2 ] = { 30, 20 };
	int iValL [ 2 ] = { 25, 5 };
	SListaOrdenadaPtr * p_lisVal1 = CrearOrdenadaEnteros ( iVal1, 2, CompararEnteros );
	SListaOrdenadaPtr * p_lisVal2 = CrearOrdenadaEnteros ( iVal2, 2, CompararEnteros );
	SListaPtr * p_lisValL = CrearListaEnteros ( iValL, 2 );
	SListaOrdenadaPtr * p_lisRes [ 5 ] = { NULL, NULL, NULL, NULL, NULL };
	if ( ES_VALIDO ( p_lisVal1 ) && ES_VALIDO ( p_lisVal2 ) && ES_VALIDO ( p_lisValL ) )
	{
		p_lisRes [ 0 ] = SLispOrdUnion ( p_lisVal1, p_lisVal2, sizeof ( int ) );
		int iEsp [ 4 ] = { 10, 20, 30, 30 };
		if ( ES_NULO ( p_lisRes [ 0 ] ) || ( VerificarOrdenada ( p_lisRes [ 0 ], iEsp, 4 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 1: se esperaba { 10, 20, 30, 30 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		else
		{
			if ( ( SLispOrdElemento ( p_lisRes [ 0 ], 0 ) == SLispOrdElemento ( p_lisVal1, 0 ) ) ||
				 ( p_lisRes [ 0 ]->p_cmpObj == p_lisVal1->p_cmpObj ) )
			{
				printf( "Error caso 2: se esperaban copias y otro comparador\n" );
				iRes = BOOL_VAL_FALSO;
			}
		}
		int iOrd1 [ 2 ] = { 10, 30 };
		int iOrd2 [ 2 ] = { 20, 30 };
		if ( ( VerificarOrdenada ( p_lisVal1, iOrd1, 2 ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarOrdenada ( p_lisVal2, iOrd2, 2 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 3: los valores no deberian cambiar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		p_lisRes [ 1 ] = SLispOrdUnionLista ( p_lisVal1, p_lisValL, sizeof ( int ) );
		int iEsp2 [ 4 ] = { 5, 10, 25, 30 };
		if ( ES_NULO ( p_lisRes [ 1 ] ) || ( VerificarOrdenada ( p_lisRes [ 1 ], iEsp2, 4 ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarLista ( p_lisValL, iValL, 2 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 4: se esperaba { 5, 10, 25, 30 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		p_lisRes [ 2 ] = SLispOrdUnion ( p_lisVal1, p_lisVal1, sizeof ( int ) );
		int iEsp3 [ 4 ] = { 10, 10, 30, 30 };
		if ( ES_NULO ( p_lisRes [ 2 ] ) || ( VerificarOrdenada ( p_lisRes [ 2 ], iEsp3, 4 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 5: consigo misma se esperaba { 10, 10, 30, 30 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Las Ext copian con fDuplicar: todo llega con 100 mas. */
		p_lisRes [ 3 ] = SLispOrdUnionExt ( p_lisVal1, p_lisVal2, DuplicarEnteroMas100 );
		p_lisRes [ 4 ] = SLispOrdUnionListaExt ( p_lisVal1, p_lisValL, DuplicarEnteroMas100 );
		int iEsp4 [ 4 ] = { 110, 120, 130, 130 };
		int iEsp5 [ 4 ] = { 105, 110, 125, 130 };
		if ( ES_NULO ( p_lisRes [ 3 ] ) || ( VerificarOrdenada ( p_lisRes [ 3 ], iEsp4, 4 ) != BOOL_VAL_CIERTO ) ||
			 ES_NULO ( p_lisRes [ 4 ] ) || ( VerificarOrdenada ( p_lisRes [ 4 ], iEsp5, 4 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 6: las Ext deberian dar { 110, 120, 130, 130 } y { 105, 110, 125, 130 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( SLispOrdUnionExt ( p_lisVal1, p_lisVal2, DuplicarFallaEn20 ) ) ||
			 ES_VALIDO ( SLispOrdUnion ( p_lisVal1, p_lisVal2, 0 ) ) ||
			 ES_VALIDO ( SLispOrdUnionExt ( p_lisVal1, p_lisVal2, NULL ) ) )
		{
			printf( "Error caso 7: si falla una copia o no hay como copiar se esperaba nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( SLispOrdUnion ( p_lisVal1, NULL, sizeof ( int ) ) ) ||
			 ES_VALIDO ( SLispOrdUnion ( NULL, p_lisVal2, sizeof ( int ) ) ) ||
			 ES_VALIDO ( SLispOrdUnionLista ( p_lisVal1, NULL, sizeof ( int ) ) ) ||
			 ES_VALIDO ( SLispOrdUnionListaExt ( NULL, p_lisValL, DuplicarEnteroMas100 ) ) )
		{
			printf( "Error caso 8: con una lista nula se esperaba nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear las listas\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLispOrdDestruir ( &p_lisVal1 );
	SLispOrdDestruir ( &p_lisVal2 );
	SLispDestruir ( &p_lisValL );
	int iPos = 0;
	while ( iPos < 5 )
	{
		SLispOrdDestruir ( &( p_lisRes [ iPos ] ) );
		iPos = iPos + 1;
	}
	ErrLimpiar ();
	return ( iRes );
}

/* Interseccion y diferencia: copias de los de V1, segun el comparador de V1.
   Con una SListaPtr se busca uno a uno; con otra ordenada, en paralelo. */
static int TestSLispOrdInterseccion01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLispOrdInterseccion 01:\n" );

	int iVal1 [ 4 ] = { 30, 20, 10, 20 };
	int iVal2 [ 3 ] = { 40, 30, 20 };
	SListaOrdenadaPtr * p_lisVal1 = CrearOrdenadaEnteros ( iVal1, 4, CompararEnteros );
	SListaOrdenadaPtr * p_lisVal2 = CrearOrdenadaEnteros ( iVal2, 3, CompararEnteros );
	SListaPtr * p_lisVal2L = CrearListaEnteros ( iVal2, 3 );
	SListaPtr * p_lisVaciaL = SLispCrear ();
	SListaOrdenadaPtr * p_lisRes [ 8 ] = { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL };
	if ( ES_VALIDO ( p_lisVal1 ) && ES_VALIDO ( p_lisVal2 ) && ES_VALIDO ( p_lisVal2L ) && ES_VALIDO ( p_lisVaciaL ) )
	{
		int iInt [ 3 ] = { 20, 20, 30 };
		int iDif [ 1 ] = { 10 };
		p_lisRes [ 0 ] = SLispOrdInterseccion ( p_lisVal1, p_lisVal2, sizeof ( int ) );
		p_lisRes [ 1 ] = SLispOrdDiferencia ( p_lisVal1, p_lisVal2, sizeof ( int ) );
		p_lisRes [ 2 ] = SLispOrdInterseccionLista ( p_lisVal1, p_lisVal2L, sizeof ( int ) );
		p_lisRes [ 3 ] = SLispOrdDiferenciaLista ( p_lisVal1, p_lisVal2L, sizeof ( int ) );
		if ( ES_NULO ( p_lisRes [ 0 ] ) || ( VerificarOrdenada ( p_lisRes [ 0 ], iInt, 3 ) != BOOL_VAL_CIERTO ) ||
			 ES_NULO ( p_lisRes [ 2 ] ) || ( VerificarOrdenada ( p_lisRes [ 2 ], iInt, 3 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 1: se esperaba la interseccion { 20, 20, 30 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_NULO ( p_lisRes [ 1 ] ) || ( VerificarOrdenada ( p_lisRes [ 1 ], iDif, 1 ) != BOOL_VAL_CIERTO ) ||
			 ES_NULO ( p_lisRes [ 3 ] ) || ( VerificarOrdenada ( p_lisRes [ 3 ], iDif, 1 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 2: se esperaba la diferencia { 10 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( p_lisRes [ 0 ] ) )
		{
			if ( ( SLispOrdElemento ( p_lisRes [ 0 ], 0 ) == SLispOrdElemento ( p_lisVal1, 1 ) ) ||
				 ( p_lisRes [ 0 ]->p_cmpObj == p_lisVal1->p_cmpObj ) ||
				 ( SLispOrdLiberacionMemoriaActivada ( p_lisRes [ 0 ] ) != 1 ) )
			{
				printf( "Error caso 3: se esperaban copias propias y otro comparador\n" );
				iRes = BOOL_VAL_FALSO;
			}
		}
		/* Las Ext copian con fDuplicar: llegan con 100 mas. */
		p_lisRes [ 4 ] = SLispOrdInterseccionExt ( p_lisVal1, p_lisVal2, DuplicarEnteroMas100 );
		p_lisRes [ 5 ] = SLispOrdDiferenciaExt ( p_lisVal1, p_lisVal2, DuplicarEnteroMas100 );
		p_lisRes [ 6 ] = SLispOrdInterseccionListaExt ( p_lisVal1, p_lisVal2L, DuplicarEnteroMas100 );
		p_lisRes [ 7 ] = SLispOrdDiferenciaListaExt ( p_lisVal1, p_lisVal2L, DuplicarEnteroMas100 );
		int iIntExt [ 3 ] = { 120, 120, 130 };
		int iDifExt [ 1 ] = { 110 };
		if ( ES_NULO ( p_lisRes [ 4 ] ) || ( VerificarOrdenada ( p_lisRes [ 4 ], iIntExt, 3 ) != BOOL_VAL_CIERTO ) ||
			 ES_NULO ( p_lisRes [ 5 ] ) || ( VerificarOrdenada ( p_lisRes [ 5 ], iDifExt, 1 ) != BOOL_VAL_CIERTO ) ||
			 ES_NULO ( p_lisRes [ 6 ] ) || ( VerificarOrdenada ( p_lisRes [ 6 ], iIntExt, 3 ) != BOOL_VAL_CIERTO ) ||
			 ES_NULO ( p_lisRes [ 7 ] ) || ( VerificarOrdenada ( p_lisRes [ 7 ], iDifExt, 1 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 4: las Ext deberian dar { 120, 120, 130 } y { 110 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		int iOrd1 [ 4 ] = { 10, 20, 20, 30 };
		if ( ( VerificarOrdenada ( p_lisVal1, iOrd1, 4 ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarLista ( p_lisVal2L, iVal2, 3 ) != BOOL_VAL_CIERTO ) ||
			 ( SLispOrdNumElementos ( p_lisVal2 ) != 3 ) )
		{
			printf( "Error caso 5: los valores no deberian cambiar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( SLispOrdInterseccionExt ( p_lisVal1, p_lisVal2, DuplicarFallaEn20 ) ) ||
			 ES_VALIDO ( SLispOrdDiferenciaListaExt ( p_lisVal1, p_lisVaciaL, DuplicarFallaEn20 ) ) ||
			 ES_VALIDO ( SLispOrdInterseccion ( p_lisVal1, p_lisVal2, 0 ) ) ||
			 ES_VALIDO ( SLispOrdDiferenciaLista ( p_lisVal1, p_lisVal2L, 0 ) ) ||
			 ES_VALIDO ( SLispOrdInterseccionExt ( p_lisVal1, p_lisVal2, NULL ) ) ||
			 ES_VALIDO ( SLispOrdDiferenciaListaExt ( p_lisVal1, p_lisVal2L, NULL ) ) )
		{
			printf( "Error caso 6: si falla una copia o no hay como copiar se esperaba nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( SLispOrdInterseccion ( p_lisVal1, NULL, sizeof ( int ) ) ) ||
			 ES_VALIDO ( SLispOrdInterseccion ( NULL, p_lisVal2, sizeof ( int ) ) ) ||
			 ES_VALIDO ( SLispOrdDiferencia ( p_lisVal1, NULL, sizeof ( int ) ) ) ||
			 ES_VALIDO ( SLispOrdDiferenciaLista ( NULL, p_lisVal2L, sizeof ( int ) ) ) ||
			 ES_VALIDO ( SLispOrdInterseccionListaExt ( p_lisVal1, NULL, DuplicarEnteroMas100 ) ) ||
			 ES_VALIDO ( SLispOrdDiferenciaExt ( NULL, p_lisVal2, DuplicarEnteroMas100 ) ) )
		{
			printf( "Error caso 7: con una lista nula se esperaba nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear las listas\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLispOrdDestruir ( &p_lisVal1 );
	SLispOrdDestruir ( &p_lisVal2 );
	SLispDestruir ( &p_lisVal2L );
	SLispDestruir ( &p_lisVaciaL );
	int iPos = 0;
	while ( iPos < 8 )
	{
		SLispOrdDestruir ( &( p_lisRes [ iPos ] ) );
		iPos = iPos + 1;
	}
	return ( iRes );
}

/* En paralelo: repetidos en las dos, valores que se pasan del final de la
   otra, vacias y la misma lista. Con otro comparador en la segunda se busca
   uno a uno, con el de la primera. */
static int TestSLispOrdInterseccion02 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLispOrdInterseccion 02:\n" );

	int iVal1 [ 7 ] = { 50, 10, 35, 5, 20, 10, 40 };
	int iVal2 [ 5 ] = { 45, 10, 40, 30, 10 };
	int iDec1 [ 2 ] = { 25, 11 };
	int iDec2 [ 1 ] = { 13 };
	SListaOrdenadaPtr * p_lisVal1 = CrearOrdenadaEnteros ( iVal1, 7, CompararEnteros );
	SListaOrdenadaPtr * p_lisVal2 = CrearOrdenadaEnteros ( iVal2, 5, CompararEnteros );
	SListaOrdenadaPtr * p_lisVacia = SLispOrdCrear ( CompararEnteros );
	SListaOrdenadaPtr * p_lisDec1 = CrearOrdenadaEnteros ( iDec1, 2, CompararEnteros );
	SListaOrdenadaPtr * p_lisDec2 = CrearOrdenadaEnteros ( iDec2, 1, CompararDecenas );
	SListaOrdenadaPtr * p_lisRes [ 10 ] = { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL };
	if ( ES_VALIDO ( p_lisVal1 ) && ES_VALIDO ( p_lisVal2 ) && ES_VALIDO ( p_lisVacia ) &&
		 ES_VALIDO ( p_lisDec1 ) && ES_VALIDO ( p_lisDec2 ) )
	{
		/* p_lisVal1 = { 5, 10, 10, 20, 35, 40, 50 }, p_lisVal2 = { 10, 10, 30, 40, 45 } */
		SLispOrdMoverA ( p_lisVal1, 2 );
		SLispOrdMoverA ( p_lisVal2, 3 );
		int iInt [ 3 ] = { 10, 10, 40 };
		int iDif [ 4 ] = { 5, 20, 35, 50 };
		p_lisRes [ 0 ] = SLispOrdInterseccion ( p_lisVal1, p_lisVal2, sizeof ( int ) );
		p_lisRes [ 1 ] = SLispOrdDiferencia ( p_lisVal1, p_lisVal2, sizeof ( int ) );
		if ( ES_NULO ( p_lisRes [ 0 ] ) || ( VerificarOrdenada ( p_lisRes [ 0 ], iInt, 3 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 1: se esperaba la interseccion { 10, 10, 40 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_NULO ( p_lisRes [ 1 ] ) || ( VerificarOrdenada ( p_lisRes [ 1 ], iDif, 4 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 2: se esperaba la diferencia { 5, 20, 35, 50 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLispOrdPosicion ( p_lisVal1 ) != 2 ) || ( SLispOrdPosicion ( p_lisVal2 ) != 3 ) )
		{
			printf( "Error caso 3: los cursores no se deberian mover\n" );
			iRes = BOOL_VAL_FALSO;
		}
		int iOrd1 [ 7 ] = { 5, 10, 10, 20, 35, 40, 50 };
		p_lisRes [ 2 ] = SLispOrdInterseccion ( p_lisVal1, p_lisVacia, sizeof ( int ) );
		p_lisRes [ 3 ] = SLispOrdDiferencia ( p_lisVal1, p_lisVacia, sizeof ( int ) );
		p_lisRes [ 4 ] = SLispOrdInterseccion ( p_lisVacia, p_lisVal1, sizeof ( int ) );
		p_lisRes [ 5 ] = SLispOrdDiferencia ( p_lisVacia, p_lisVal1, sizeof ( int ) );
		if ( ES_NULO ( p_lisRes [ 2 ] ) || ( SLispOrdNumElementos ( p_lisRes [ 2 ] ) != 0 ) ||
			 ES_NULO ( p_lisRes [ 3 ] ) || ( VerificarOrdenada ( p_lisRes [ 3 ], iOrd1, 7 ) != BOOL_VAL_CIERTO ) ||
			 ES_NULO ( p_lisRes [ 4 ] ) || ( SLispOrdNumElementos ( p_lisRes [ 4 ] ) != 0 ) ||
			 ES_NULO ( p_lisRes [ 5 ] ) || ( SLispOrdNumElementos ( p_lisRes [ 5 ] ) != 0 ) )
		{
			printf( "Error caso 4: con vacias se esperaban { }, la primera, { } y { }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		p_lisRes [ 6 ] = SLispOrdInterseccion ( p_lisVal1, p_lisVal1, sizeof ( int ) );
		p_lisRes [ 7 ] = SLispOrdDiferencia ( p_lisVal1, p_lisVal1, sizeof ( int ) );
		if ( ES_NULO ( p_lisRes [ 6 ] ) || ( VerificarOrdenada ( p_lisRes [ 6 ], iOrd1, 7 ) != BOOL_VAL_CIERTO ) ||
			 ES_NULO ( p_lisRes [ 7 ] ) || ( SLispOrdNumElementos ( p_lisRes [ 7 ] ) != 0 ) )
		{
			printf( "Error caso 5: consigo misma se esperaba ella entera y { }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Por decenas 11 y 13 serian iguales, pero manda el comparador de la primera. */
		int iDecDif [ 2 ] = { 11, 25 };
		p_lisRes [ 8 ] = SLispOrdInterseccion ( p_lisDec1, p_lisDec2, sizeof ( int ) );
		p_lisRes [ 9 ] = SLispOrdDiferencia ( p_lisDec1, p_lisDec2, sizeof ( int ) );
		if ( ES_NULO ( p_lisRes [ 8 ] ) || ( SLispOrdNumElementos ( p_lisRes [ 8 ] ) != 0 ) ||
			 ES_NULO ( p_lisRes [ 9 ] ) || ( VerificarOrdenada ( p_lisRes [ 9 ], iDecDif, 2 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 6: con otro comparador en la segunda se esperaba { } y { 11, 25 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear las listas\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLispOrdDestruir ( &p_lisVal1 );
	SLispOrdDestruir ( &p_lisVal2 );
	SLispOrdDestruir ( &p_lisVacia );
	SLispOrdDestruir ( &p_lisDec1 );
	SLispOrdDestruir ( &p_lisDec2 );
	int iPos = 0;
	while ( iPos < 10 )
	{
		SLispOrdDestruir ( &( p_lisRes [ iPos ] ) );
		iPos = iPos + 1;
	}
	return ( iRes );
}


/* 1 solo con el cursor sobre un elemento: no en una vacia, ni deposicionada,
   ni con la lista nula. */
/* Busca por el contenido de un elemento con el comparador de la lista: con
   CompararDecenas el 25 es igual que el 20. */
static int TestSLispOrdBuscarPtr01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLispOrdBuscarPtr 01:\n" );

	int iVal [ 4 ] = { 30, 20, 10, 20 };
	SListaOrdenadaPtr * p_lisObj = CrearOrdenadaEnteros ( iVal, 4, CompararEnteros );
	SListaOrdenadaPtr * p_lisDec = CrearOrdenadaEnteros ( iVal, 4, CompararDecenas );
	SElementoPtr * p_elp20 = SElpCrear ( CrearDatoEntero ( 20 ), 1 );
	SElementoPtr * p_elp25 = SElpCrear ( CrearDatoEntero ( 25 ), 1 );
	SElementoPtr * p_elp99 = SElpCrear ( CrearDatoEntero ( 99 ), 1 );
	if ( ES_VALIDO ( p_lisObj ) && ES_VALIDO ( p_lisDec ) && ES_VALIDO ( p_elp20 ) &&
		 ES_VALIDO ( p_elp25 ) && ES_VALIDO ( p_elp99 ) )
	{
		/* { 10, 20, 20, 30 }: el primero igual. */
		if ( SLispOrdBuscarPtr ( p_lisObj, p_elp20 ) != 1 )
		{
			printf( "Error caso 1: el 20 deberia estar en la posicion 1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLispOrdBuscarPtr ( p_lisObj, p_elp25 ) != -1 ) || ( SLispOrdBuscarPtr ( p_lisObj, p_elp99 ) != -1 ) )
		{
			printf( "Error caso 2: ni el 25 ni el 99 deberian encontrarse\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLispOrdBuscarPtr ( p_lisDec, p_elp25 ) != 1 )
		{
			printf( "Error caso 3: por decenas el 25 deberia encontrarse en la posicion 1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLispOrdBuscarPtr ( p_lisObj, NULL ) != -1 ) || ( SLispOrdBuscarPtr ( NULL, p_elp20 ) != -1 ) )
		{
			printf( "Error caso 4: con un nulo se esperaba -1\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear las listas o los elementos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SElpDestruir ( &p_elp20 );
	SElpDestruir ( &p_elp25 );
	SElpDestruir ( &p_elp99 );
	SLispOrdDestruir ( &p_lisObj );
	SLispOrdDestruir ( &p_lisDec );
	return ( iRes );
}

/* Destruye todas las apariciones de cada valor buscado; la igualdad la decide
   el comparador, y sin liberacion no se liberan los datos. */
static int TestSLispOrdEliminarLista01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLispOrdEliminarLista 01:\n" );

	int iObj [ 6 ] = { 40, 20, 10, 30, 20, 20 };
	int iValOrd [ 3 ] = { 50, 40, 20 };
	int iVal [ 4 ] = { 20, 10, 20, 50 };
	int iDec [ 4 ] = { 33, 12, 25, 35 };
	int iValDec [ 2 ] = { 39, 21 };
	int iAjena [ 1 ] = { 20 };
	SListaOrdenadaPtr * p_lisObj = CrearOrdenadaEnteros ( iObj, 6, CompararEnteros );
	SListaOrdenadaPtr * p_lisValOrd = CrearOrdenadaEnteros ( iValOrd, 3, CompararEnteros );
	SListaPtr * p_lisVal = CrearListaEnteros ( iVal, 4 );
	SListaOrdenadaPtr * p_lisDec = CrearOrdenadaEnteros ( iDec, 4, CompararDecenas );
	SListaPtr * p_lisValDec = CrearListaEnteros ( iValDec, 2 );
	SListaPtr * p_lisValAjena = CrearListaEnteros ( iAjena, 1 );
	/* Datos del test: la lista no es duena de ellos. */
	byte * p_d10 = CrearDatoEntero ( 10 );
	byte * p_d20 = CrearDatoEntero ( 20 );
	byte * p_d20b = CrearDatoEntero ( 20 );
	SListaOrdenadaPtr * p_lisAjena = SLispOrdCrear ( CompararEnteros );
	if ( ES_VALIDO ( p_lisObj ) && ES_VALIDO ( p_lisValOrd ) && ES_VALIDO ( p_lisVal ) &&
		 ES_VALIDO ( p_lisDec ) && ES_VALIDO ( p_lisValDec ) && ES_VALIDO ( p_lisValAjena ) &&
		 ES_VALIDO ( p_lisAjena ) )
	{
		/* p_lisObj = { 10, 20, 20, 20, 30, 40 }: se van los tres 20; el 50 no esta
		   y se ignora. */
		int iQueda [ 2 ] = { 10, 30 };
		if ( ( SLispOrdEliminarListaOrd ( p_lisObj, p_lisValOrd ) != 1 ) ||
			 ( VerificarOrdenada ( p_lisObj, iQueda, 2 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 1: se esperaba 1 y que quedara { 10, 30 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		int iEspValOrd [ 3 ] = { 20, 40, 50 };
		if ( VerificarOrdenada ( p_lisValOrd, iEspValOrd, 3 ) != BOOL_VAL_CIERTO )
		{
			printf( "Error caso 2: los valores no deberian cambiar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Que el 20 este dos veces en los valores no elimina mas: queda { 30 }. */
		int iQueda2 [ 1 ] = { 30 };
		if ( ( SLispOrdEliminarLista ( p_lisObj, p_lisVal ) != 1 ) ||
			 ( VerificarOrdenada ( p_lisObj, iQueda2, 1 ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarLista ( p_lisVal, iVal, 4 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 3: se esperaba 1 y que quedara { 30 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Ya no queda ninguno: no hay nada que eliminar, y no es un error. */
		if ( ( SLispOrdEliminarLista ( p_lisObj, p_lisVal ) != 1 ) ||
			 ( VerificarOrdenada ( p_lisObj, iQueda2, 1 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 4: sin nada que eliminar se esperaba 1 sin cambios\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Por decenas el 39 es igual que el 33 y el 35, y el 21 que el 25. */
		int iQuedaDec [ 1 ] = { 12 };
		if ( ( SLispOrdEliminarLista ( p_lisDec, p_lisValDec ) != 1 ) ||
			 ( VerificarOrdenada ( p_lisDec, iQuedaDec, 1 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 5: por decenas deberia quedar { 12 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Sin liberacion los dos 20 salen de la lista pero no se liberan: se liberan abajo. */
		SLispOrdDesactivarLiberacionMemoria ( p_lisAjena );
		SLispOrdInsertarElem ( p_lisAjena, p_d10 );
		SLispOrdInsertarElem ( p_lisAjena, p_d20 );
		SLispOrdInsertarElem ( p_lisAjena, p_d20b );
		if ( ( SLispOrdEliminarLista ( p_lisAjena, p_lisValAjena ) != 1 ) ||
			 ( SLispOrdNumElementos ( p_lisAjena ) != 1 ) ||
			 ( SLispOrdElemento ( p_lisAjena, 0 ) != p_d10 ) || ( *( (int *) p_d20 ) != 20 ) ||
			 ( *( (int *) p_d20b ) != 20 ) )
		{
			printf( "Error caso 6: sin liberacion se esperaba quitar los dos 20 sin liberarlos\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLispOrdEliminarListaOrd ( p_lisObj, p_lisObj ) != 0 ) ||
			 ( SLispOrdEliminarLista ( p_lisObj, p_lisObj->p_lispContenido ) != 0 ) ||
			 ( VerificarOrdenada ( p_lisObj, iQueda2, 1 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 7: con la misma lista se esperaba 0 sin cambios\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLispOrdEliminarListaOrd ( p_lisObj, NULL ) != 0 ) ||
			 ( SLispOrdEliminarListaOrd ( NULL, p_lisValOrd ) != 0 ) ||
			 ( SLispOrdEliminarLista ( p_lisObj, NULL ) != 0 ) ||
			 ( SLispOrdEliminarLista ( NULL, p_lisVal ) != 0 ) )
		{
			printf( "Error caso 8: con una lista nula se esperaba 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear las listas\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLispOrdDestruir ( &p_lisObj );
	SLispOrdDestruir ( &p_lisValOrd );
	SLispDestruir ( &p_lisVal );
	SLispOrdDestruir ( &p_lisDec );
	SLispDestruir ( &p_lisValDec );
	SLispDestruir ( &p_lisValAjena );
	SLispOrdDestruir ( &p_lisAjena );
	MemLiberar ( (void **) &p_d10 );
	MemLiberar ( (void **) &p_d20 );
	MemLiberar ( (void **) &p_d20b );
	return ( iRes );
}

/* Repetidos en una ordenada: estan juntos y la igualdad la decide el
   comparador. Con un dato y con un elemento. */
static int TestSLispOrdBuscarSiguiente01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLispOrdBuscarSiguiente 01:\n" );

	int iVal [ 6 ] = { 40, 20, 10, 20, 30, 20 };
	int iDec [ 5 ] = { 12, 25, 21, 33, 28 };
	int iVeinte = 20;
	int iDiez = 10;
	int iCuarenta = 40;
	int iVeinticinco = 25;
	int iCinco = 5;
	int iNoventa = 99;
	SListaOrdenadaPtr * p_lisObj = CrearOrdenadaEnteros ( iVal, 6, CompararEnteros );
	SListaOrdenadaPtr * p_lisDec = CrearOrdenadaEnteros ( iDec, 5, CompararDecenas );
	SElementoPtr * p_elp20 = SElpCrear ( CrearDatoEntero ( 20 ), 1 );
	SElementoPtr * p_elp24 = SElpCrear ( CrearDatoEntero ( 24 ), 1 );
	if ( ES_VALIDO ( p_lisObj ) && ES_VALIDO ( p_lisDec ) && ES_VALIDO ( p_elp20 ) && ES_VALIDO ( p_elp24 ) )
	{
		/* p_lisObj = { 10, 20, 20, 20, 30, 40 } */
		if ( ( SLispOrdBuscarPrimero ( p_lisObj, (byte *) &iVeinte ) != 1 ) ||
			 ( SLispOrdBuscarSiguiente ( p_lisObj, (byte *) &iVeinte, 1 ) != 2 ) ||
			 ( SLispOrdBuscarSiguiente ( p_lisObj, (byte *) &iVeinte, 2 ) != 3 ) ||
			 ( SLispOrdBuscarSiguiente ( p_lisObj, (byte *) &iVeinte, 3 ) != -1 ) )
		{
			printf( "Error caso 1: el 20 deberia estar en 1, 2 y 3\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLispOrdBuscarPrimeroPtr ( p_lisObj, p_elp20 ) != 1 ) ||
			 ( SLispOrdBuscarSiguientePtr ( p_lisObj, p_elp20, 1 ) != 2 ) ||
			 ( SLispOrdBuscarSiguientePtr ( p_lisObj, p_elp20, 3 ) != -1 ) ||
			 ( SLispOrdBuscar ( p_lisObj, (byte *) &iVeinte ) != 1 ) ||
			 ( SLispOrdBuscarPtr ( p_lisObj, p_elp20 ) != 1 ) )
		{
			printf( "Error caso 2: por elemento, lo mismo; y Buscar es BuscarPrimero\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLispOrdBuscarSiguiente ( p_lisObj, (byte *) &iVeinte, 0 ) != 1 ) ||
			 ( SLispOrdBuscarSiguiente ( p_lisObj, (byte *) &iVeinte, 4 ) != -1 ) ||
			 ( SLispOrdBuscarSiguiente ( p_lisObj, (byte *) &iVeinte, 5 ) != -1 ) ||
			 ( SLispOrdBuscarSiguiente ( p_lisObj, (byte *) &iVeinte, -2 ) != -1 ) )
		{
			printf( "Error caso 3: detras de la 0 se esperaba la 1, y detras de la 4 nada\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLispOrdRepeticiones ( p_lisObj, (byte *) &iVeinte ) != 3 ) ||
			 ( SLispOrdRepeticionesPtr ( p_lisObj, p_elp20 ) != 3 ) ||
			 ( SLispOrdExiste ( p_lisObj, (byte *) &iVeinte ) != 1 ) ||
			 ( SLispOrdExistePtr ( p_lisObj, p_elp20 ) != 1 ) )
		{
			printf( "Error caso 4: el 20 deberia estar 3 veces\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLispOrdRepeticiones ( p_lisObj, (byte *) &iDiez ) != 1 ) ||
			 ( SLispOrdRepeticiones ( p_lisObj, (byte *) &iCuarenta ) != 1 ) ||
			 ( SLispOrdRepeticiones ( p_lisObj, (byte *) &iVeinticinco ) != 0 ) ||
			 ( SLispOrdExiste ( p_lisObj, (byte *) &iVeinticinco ) != 0 ) ||
			 ( SLispOrdRepeticiones ( p_lisObj, (byte *) &iCinco ) != 0 ) ||
			 ( SLispOrdRepeticiones ( p_lisObj, (byte *) &iNoventa ) != 0 ) )
		{
			printf( "Error caso 5: el 10 y el 40 una vez; el 25, el 5 y el 99 ninguna\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Por decenas: { 12, 25, 21, 28, 33 }; el 24 es igual que los tres veintes. */
		if ( ( SLispOrdRepeticionesPtr ( p_lisDec, p_elp24 ) != 3 ) ||
			 ( SLispOrdBuscarPrimeroPtr ( p_lisDec, p_elp24 ) != 1 ) ||
			 ( SLispOrdBuscarSiguientePtr ( p_lisDec, p_elp24, 3 ) != -1 ) )
		{
			printf( "Error caso 6: por decenas el 24 deberia estar 3 veces, de la 1 a la 3\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLispOrdBuscarSiguiente ( NULL, (byte *) &iVeinte, -1 ) != -1 ) ||
			 ( SLispOrdBuscarSiguiente ( p_lisObj, NULL, -1 ) != -1 ) ||
			 ( SLispOrdBuscarSiguientePtr ( p_lisObj, NULL, -1 ) != -1 ) ||
			 ( SLispOrdRepeticiones ( NULL, (byte *) &iVeinte ) != 0 ) ||
			 ( SLispOrdRepeticiones ( p_lisObj, NULL ) != 0 ) ||
			 ( SLispOrdRepeticionesPtr ( p_lisObj, NULL ) != 0 ) ||
			 ( SLispOrdExiste ( p_lisObj, NULL ) != 0 ) ||
			 ( SLispOrdExistePtr ( NULL, p_elp20 ) != 0 ) )
		{
			printf( "Error caso 7: con un nulo se esperaba -1 al buscar y 0 al contar\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear las listas o los elementos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SElpDestruir ( &p_elp20 );
	SElpDestruir ( &p_elp24 );
	SLispOrdDestruir ( &p_lisObj );
	SLispOrdDestruir ( &p_lisDec );
	return ( iRes );
}

static int TestSLispOrdEstaPosicionada01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLispOrdEstaPosicionada 01:\n" );

	SListaOrdenadaPtr * p_lisObj = SLispOrdCrear ( CompararEnteros );
	if ( ES_VALIDO ( p_lisObj ) )
	{
		if ( SLispOrdEstaPosicionada ( p_lisObj ) != 0 )
		{
			printf( "Error caso 1: una lista vacia no deberia estar posicionada\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLispOrdInsertarElem ( p_lisObj, CrearDatoEntero ( 10 ) );
		SLispOrdInsertarElem ( p_lisObj, CrearDatoEntero ( 20 ) );
		SLispOrdInicio ( p_lisObj );
		if ( SLispOrdEstaPosicionada ( p_lisObj ) != 1 )
		{
			printf( "Error caso 2: tras Inicio deberia estar posicionada\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLispOrdSiguiente ( p_lisObj );
		SLispOrdSiguiente ( p_lisObj );
		if ( SLispOrdEstaPosicionada ( p_lisObj ) != 0 )
		{
			printf( "Error caso 3: pasado el ultimo no deberia estar posicionada\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLispOrdFinal ( p_lisObj );
		SLispOrdDeposicionar ( p_lisObj );
		if ( SLispOrdEstaPosicionada ( p_lisObj ) != 0 )
		{
			printf( "Error caso 4: tras Deposicionar no deberia estar posicionada\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLispOrdEstaPosicionada ( NULL ) != 0 )
		{
			printf( "Error caso 5: con una lista nula se esperaba 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la lista\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLispOrdDestruir ( &p_lisObj );
	return ( iRes );
}

/* ExtraerElem saca el dato de la posicion sin liberarlo, y la lista sigue
   ordenada. */
static int TestSLispOrdExtraerElem01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLispOrdExtraerElem 01:\n" );

	SListaOrdenadaPtr * p_lisObj = SLispOrdCrear ( CompararEnteros );
	byte * p_byDato = NULL;
	if ( ES_VALIDO ( p_lisObj ) )
	{
		SLispOrdInsertarElem ( p_lisObj, CrearDatoEntero ( 30 ) );
		SLispOrdInsertarElem ( p_lisObj, CrearDatoEntero ( 10 ) );
		SLispOrdInsertarElem ( p_lisObj, CrearDatoEntero ( 20 ) );
		p_byDato = SLispOrdExtraerElem ( p_lisObj, 1 );
		int iEsp1 [ 2 ] = { 10, 30 };
		if ( ES_NULO ( p_byDato ) || ( *( (int *) p_byDato ) != 20 ) ||
			 ( VerificarOrdenada ( p_lisObj, iEsp1, 2 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 1: se esperaba extraer el 20 y dejar { 10, 30 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* El dato es ahora del que llama. */
		MemLiberar ( (void **) &p_byDato );
		if ( ES_VALIDO ( SLispOrdExtraerElem ( p_lisObj, 2 ) ) ||
			 ES_VALIDO ( SLispOrdExtraerElem ( NULL, 0 ) ) ||
			 ( VerificarOrdenada ( p_lisObj, iEsp1, 2 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 2: con nulo o fuera de rango se esperaba nulo sin cambios\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la lista\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLispOrdDestruir ( &p_lisObj );
	return ( iRes );
}

int TestSListaOrdenadaPtr ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SListaOrdenadaPtr]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSLispOrdInsertar01 () == BOOL_VAL_CIERTO ) &&
			( TestSLispOrdCursor01 () == BOOL_VAL_CIERTO ) &&
			( TestSLispOrdInvalidos01 () == BOOL_VAL_CIERTO ) &&
			( TestSLispOrdEncapsular01 () == BOOL_VAL_CIERTO ) &&
			( TestSLispOrdCrearDesdeLista01 () == BOOL_VAL_CIERTO ) &&
			( TestSLispOrdDuplicar01 () == BOOL_VAL_CIERTO ) &&
			( TestSLispOrdDuplicarLista01 () == BOOL_VAL_CIERTO ) &&
			( TestSLispOrdCrearIgual01 () == BOOL_VAL_CIERTO ) &&
			( TestSLispOrdExistenTodos01 () == BOOL_VAL_CIERTO ) &&
			( TestSLispOrdInsertarLista01 () == BOOL_VAL_CIERTO ) &&
			( TestSLispOrdInsertarListaDup01 () == BOOL_VAL_CIERTO ) &&
			( TestSLispOrdExtraerLista01 () == BOOL_VAL_CIERTO ) &&
			( TestSLispOrdEliminarLista01 () == BOOL_VAL_CIERTO ) &&
			( TestSLispOrdBuscarPtr01 () == BOOL_VAL_CIERTO ) &&
			( TestSLispOrdBuscarSiguiente01 () == BOOL_VAL_CIERTO ) &&
			( TestSLispOrdUnion01 () == BOOL_VAL_CIERTO ) &&
			( TestSLispOrdInterseccion01 () == BOOL_VAL_CIERTO ) &&
			( TestSLispOrdInterseccion02 () == BOOL_VAL_CIERTO ) &&
			( TestSLispOrdEstaPosicionada01 () == BOOL_VAL_CIERTO ) &&
			( TestSLispOrdExtraerElem01 () == BOOL_VAL_CIERTO ) )
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
