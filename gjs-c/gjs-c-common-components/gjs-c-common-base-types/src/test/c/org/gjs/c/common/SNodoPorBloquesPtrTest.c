#include "Base.h"

#include "SNodoPorBloquesPtr.h"



static byte * CrearDatoEntero ( int iValor )
{
	int * p_iDato = (int *) MemReservar ( sizeof ( int ) );
	if ( ES_VALIDO ( p_iDato ) )
	{
		*p_iDato = iValor;
	}
	return ( (byte *) p_iDato );
}

static int ValorNodo ( SNodoBlqPtr * p_nodpObj )
{
	return ( *( (int *) SNodBlqPtrDatos ( p_nodpObj ) ) );
}



static int TestSNodBlqPtrCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SNodBlqPtrCrear 01:\n" );

	SNodoBlqPtr * p_nodpObj = SNodBlqPtrCrear ( CrearDatoEntero ( 42 ), 1 );
	if ( ES_NULO ( p_nodpObj ) )
	{
		printf( "Error caso 1: no se esperaba nulo al crear\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SNodBlqPtrEsValido ( p_nodpObj ) != 1 )
		{
			printf( "Error caso 2: el nodo recien creado deberia ser valido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ValorNodo ( p_nodpObj ) != 42 )
		{
			printf( "Error caso 3: se esperaba el valor 42\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SNodBlqPtrTienePadre ( p_nodpObj ) != 0 ) || ( SNodBlqPtrTieneHijos ( p_nodpObj ) != 0 ) )
		{
			printf( "Error caso 4: el nodo no deberia tener padre ni hijos\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	SNodBlqPtrDestruir ( &p_nodpObj, 1 );

	if ( ES_VALIDO ( p_nodpObj ) )
	{
		printf( "Error caso 5: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( SNodBlqPtrCrear ( NULL, 1 ) ) )
	{
		printf( "Error caso 6: se esperaba nulo al crear con datos nulos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSNodBlqPtrArbol01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SNodBlqPtrArbol 01:\n" );

	SNodoBlqPtr * p_n1 = SNodBlqPtrCrear ( CrearDatoEntero ( 1 ), 1 );
	if ( ES_VALIDO ( p_n1 ) )
	{
		SNodoBlqPtr * p_n2 = SNodBlqPtrCrear ( CrearDatoEntero ( 2 ), 1 );
		SNodoBlqPtr * p_n4 = SNodBlqPtrCrear ( CrearDatoEntero ( 4 ), 1 );
		SNodBlqPtrInsertarHijo ( p_n1, p_n2 );
		SNodBlqPtrInsertarHijo ( p_n1, SNodBlqPtrCrear ( CrearDatoEntero ( 3 ), 1 ) );
		SNodBlqPtrInsertarHijo ( p_n1, p_n4 );

		if ( SNodBlqPtrNumHijos ( p_n1 ) != 3 )
		{
			printf( "Error caso 1: se esperaban 3 hijos: %d\n", SNodBlqPtrNumHijos ( p_n1 ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( ValorNodo ( SNodBlqPtrHijo ( p_n1, 0 ) ) != 2 ) ||
			 ( ValorNodo ( SNodBlqPtrHijo ( p_n1, 1 ) ) != 3 ) ||
			 ( ValorNodo ( SNodBlqPtrHijo ( p_n1, 2 ) ) != 4 ) )
		{
			printf( "Error caso 2: los hijos deberian ser 2, 3 y 4 en ese orden\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SNodBlqPtrPadre ( p_n2 ) != p_n1 ) || ( SNodBlqPtrTienePadre ( p_n2 ) != 1 ) )
		{
			printf( "Error caso 3: el hijo deberia tener como padre el nodo 1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SNodBlqPtrTieneHermanos ( p_n2 ) != 1 ) || ( SNodBlqPtrTieneHermanosDer ( p_n2 ) != 1 ) )
		{
			printf( "Error caso 4: el 2 deberia tener hermanos, con alguno a la derecha\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SNodBlqPtrOrdenDelHijo ( p_n1, p_n4 ) != 2 )
		{
			printf( "Error caso 5: el 4 deberia ser el hijo de orden 2\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SNodBlqPtrNodosInferiores ( p_n1 ) != 3 )
		{
			printf( "Error caso 6: se esperaban 3 nodos inferiores: %d\n", SNodBlqPtrNodosInferiores ( p_n1 ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SNodBlqPtrNivelesInferiores ( p_n1 ) != 1 )
		{
			printf( "Error caso 7: se esperaba 1 nivel inferior: %d\n", SNodBlqPtrNivelesInferiores ( p_n1 ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SNodBlqPtrProfundidad ( p_n1 ) != 0 ) || ( SNodBlqPtrProfundidad ( p_n2 ) != 1 ) )
		{
			printf( "Error caso 8: la profundidad de raiz/hijo deberia ser 0/1\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el nodo raiz\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SNodBlqPtrDestruir ( &p_n1, 1 );
	return ( iRes );
}

static int TestSNodBlqPtrEliminar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SNodBlqPtrEliminar 01:\n" );

	SNodoBlqPtr * p_n1 = SNodBlqPtrCrear ( CrearDatoEntero ( 1 ), 1 );
	if ( ES_VALIDO ( p_n1 ) )
	{
		SNodBlqPtrInsertarHijo ( p_n1, SNodBlqPtrCrear ( CrearDatoEntero ( 2 ), 1 ) );
		SNodBlqPtrInsertarHijo ( p_n1, SNodBlqPtrCrear ( CrearDatoEntero ( 3 ), 1 ) );
		SNodBlqPtrInsertarHijo ( p_n1, SNodBlqPtrCrear ( CrearDatoEntero ( 4 ), 1 ) );

		if ( SNodBlqPtrEliminarHijo ( p_n1, 1, 1 ) != 1 )
		{
			printf( "Error caso 1: se esperaba resultado 1 al eliminar el hijo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SNodBlqPtrNumHijos ( p_n1 ) != 2 )
		{
			printf( "Error caso 2: deberian quedar 2 hijos\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( ValorNodo ( SNodBlqPtrHijo ( p_n1, 0 ) ) != 2 ) || ( ValorNodo ( SNodBlqPtrHijo ( p_n1, 1 ) ) != 4 ) )
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
	SNodBlqPtrDestruir ( &p_n1, 1 );
	return ( iRes );
}

static int TestSNodBlqPtrInvalidos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SNodBlqPtrInvalidos 01:\n" );

	if ( SNodBlqPtrEsValido ( NULL ) != 0 )
	{
		printf( "Error caso 1: un nodo nulo no deberia ser valido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SNodBlqPtrNumHijos ( NULL ) != 0 )
	{
		printf( "Error caso 2: un nodo nulo no deberia tener hijos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SNodBlqPtrNodosInferiores ( NULL ) != 0 )
	{
		printf( "Error caso 3: un nodo nulo no deberia tener nodos inferiores\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SNodoBlqPtr * p_nodpNulo = NULL;
	SNodBlqPtrDestruir ( &p_nodpNulo, 1 );
	return ( iRes );
}



int TestSNodoPorBloquesPtr ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SNodoPorBloquesPtr]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSNodBlqPtrCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSNodBlqPtrArbol01 () == BOOL_VAL_CIERTO ) &&
			( TestSNodBlqPtrEliminar01 () == BOOL_VAL_CIERTO ) &&
			( TestSNodBlqPtrInvalidos01 () == BOOL_VAL_CIERTO ) )
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
