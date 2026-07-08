#include "Base.h"

#include "SNodoPtr.h"



/* Reserva un entero en memoria dinamica; el nodo lo gestiona ( iLiberar = 1 ). */
static byte * CrearDatoEntero ( int iValor )
{
	int * p_iDato = (int *) MemReservar ( sizeof ( int ) );
	if ( ES_VALIDO ( p_iDato ) )
	{
		*p_iDato = iValor;
	}
	return ( (byte *) p_iDato );
}

static int ValorNodo ( SNodoPtr * p_nodpObj )
{
	return ( *( (int *) SNodPtrDatos ( p_nodpObj ) ) );
}



static int TestSNodPtrCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SNodPtrCrear 01:\n" );

	SNodoPtr * p_nodpObj = SNodPtrCrear ( CrearDatoEntero ( 42 ), 1 );
	if ( ES_NULO ( p_nodpObj ) )
	{
		printf( "Error caso 1: no se esperaba nulo al crear\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SNodPtrEsValido ( p_nodpObj ) != 1 )
		{
			printf( "Error caso 2: el nodo recien creado deberia ser valido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ValorNodo ( p_nodpObj ) != 42 )
		{
			printf( "Error caso 3: se esperaba el valor 42\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SNodPtrTienePadre ( p_nodpObj ) != 0 ) || ( SNodPtrTieneHijos ( p_nodpObj ) != 0 ) )
		{
			printf( "Error caso 4: el nodo no deberia tener padre ni hijos\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	SNodPtrDestruir ( &p_nodpObj, 1 );

	if ( ES_VALIDO ( p_nodpObj ) )
	{
		printf( "Error caso 5: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* Crear con datos nulos debe fallar. */
	if ( ES_VALIDO ( SNodPtrCrear ( NULL, 1 ) ) )
	{
		printf( "Error caso 6: se esperaba nulo al crear con datos nulos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSNodPtrArbol01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SNodPtrArbol 01:\n" );

	SNodoPtr * p_n1 = SNodPtrCrear ( CrearDatoEntero ( 1 ), 1 );
	if ( ES_VALIDO ( p_n1 ) )
	{
		SNodoPtr * p_n2 = SNodPtrCrear ( CrearDatoEntero ( 2 ), 1 );
		SNodoPtr * p_n4 = SNodPtrCrear ( CrearDatoEntero ( 4 ), 1 );
		/* InsertarHijo empadrona al hijo y lo anade. */
		if ( SNodPtrInsertarHijo ( p_n1, p_n2 ) == 0 )
		{
			printf( "Error insertando hijo 1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SNodPtrInsertarHijo ( p_n1, SNodPtrCrear ( CrearDatoEntero ( 3 ), 1 ) ) == 0 )
		{
			printf( "Error insertando hijo 2\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SNodPtrInsertarHijo ( p_n1, p_n4 ) == 0 )
		{
			printf( "Error insertando hijo 3\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SNodPtrNumHijos ( p_n1 ) != 3 )
		{
			printf( "Error caso 1: se esperaban 3 hijos: %d\n", SNodPtrNumHijos ( p_n1 ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( ValorNodo ( SNodPtrHijo ( p_n1, 0 ) ) != 2 ) ||
			 ( ValorNodo ( SNodPtrHijo ( p_n1, 1 ) ) != 3 ) ||
			 ( ValorNodo ( SNodPtrHijo ( p_n1, 2 ) ) != 4 ) )
		{
			printf( "Error caso 2: los hijos deberian ser 2, 3 y 4 en ese orden\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SNodPtrPadre ( p_n2 ) != p_n1 ) || ( SNodPtrTienePadre ( p_n2 ) != 1 ) )
		{
			printf( "Error caso 3: el hijo deberia tener como padre el nodo 1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SNodPtrTieneHermanos ( p_n2 ) != 1 ) || ( SNodPtrTieneHermanosDer ( p_n2 ) != 1 ) )
		{
			printf( "Error caso 4: el 2 deberia tener hermanos, con alguno a la derecha\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SNodPtrOrdenDelHijo ( p_n1, p_n4 ) != 2 )
		{
			printf( "Error caso 5: el 4 deberia ser el hijo de orden 2\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SNodPtrNodosInferiores ( p_n1 ) != 3 )
		{
			printf( "Error caso 6: se esperaban 3 nodos inferiores: %d\n", SNodPtrNodosInferiores ( p_n1 ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SNodPtrNivelesInferiores ( p_n1 ) != 1 )
		{
			printf( "Error caso 7: se esperaba 1 nivel inferior: %d\n", SNodPtrNivelesInferiores ( p_n1 ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SNodPtrProfundidad ( p_n2 ) != 1 ) || ( SNodPtrEsHijo ( p_n2 ) != 1 ) || ( SNodPtrEsHijo ( p_n1 ) != 0 ) )
		{
			printf( "Error caso 8: el 2 deberia estar a profundidad 1 y ser hijo; la raiz no\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el nodo raiz\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SNodPtrDestruir ( &p_n1, 1 );
	return ( iRes );
}

static int TestSNodPtrEliminar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SNodPtrEliminar 01:\n" );

	SNodoPtr * p_n1 = SNodPtrCrear ( CrearDatoEntero ( 1 ), 1 );
	if ( ES_VALIDO ( p_n1 ) )
	{
		SNodPtrInsertarHijo ( p_n1, SNodPtrCrear ( CrearDatoEntero ( 2 ), 1 ) );
		SNodPtrInsertarHijo ( p_n1, SNodPtrCrear ( CrearDatoEntero ( 3 ), 1 ) );
		SNodPtrInsertarHijo ( p_n1, SNodPtrCrear ( CrearDatoEntero ( 4 ), 1 ) );

		if ( SNodPtrEliminarHijo ( p_n1, 1, 1 ) != 1 )
		{
			printf( "Error caso 1: se esperaba resultado 1 al eliminar el hijo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SNodPtrNumHijos ( p_n1 ) != 2 )
		{
			printf( "Error caso 2: deberian quedar 2 hijos\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( ValorNodo ( SNodPtrHijo ( p_n1, 0 ) ) != 2 ) || ( ValorNodo ( SNodPtrHijo ( p_n1, 1 ) ) != 4 ) )
		{
			printf( "Error caso 3: tras eliminar el 3, deberian quedar el 2 y el 4\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el nodo raiz\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SNodPtrDestruir ( &p_n1, 1 );
	return ( iRes );
}

static int TestSNodPtrInvalidos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SNodPtrInvalidos 01:\n" );

	if ( SNodPtrEsValido ( NULL ) != 0 )
	{
		printf( "Error caso 1: un nodo nulo no deberia ser valido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SNodPtrNumHijos ( NULL ) != 0 )
	{
		printf( "Error caso 2: un nodo nulo no deberia tener hijos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SNodPtrNodosInferiores ( NULL ) != 0 )
	{
		printf( "Error caso 3: un nodo nulo no deberia tener nodos inferiores\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SNodoPtr * p_nodpNulo = NULL;
	SNodPtrDestruir ( &p_nodpNulo, 1 );
	return ( iRes );
}



int TestSNodoPtr ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SNodoPtr]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSNodPtrCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSNodPtrArbol01 () == BOOL_VAL_CIERTO ) &&
			( TestSNodPtrEliminar01 () == BOOL_VAL_CIERTO ) &&
			( TestSNodPtrInvalidos01 () == BOOL_VAL_CIERTO ) )
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
