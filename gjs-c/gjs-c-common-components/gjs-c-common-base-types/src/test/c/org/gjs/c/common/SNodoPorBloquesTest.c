#include "Base.h"

#include "SNodoPorBloques.h"



static SNodoBlq * CrearNodoEntero ( int iValor )
{
	SNodoBlq * p_nodObj = SNodBlqCrearEntero ();
	if ( ES_VALIDO ( p_nodObj ) )
	{
		SNodBlqEscribirEntero ( p_nodObj, iValor );
	}
	return ( p_nodObj );
}



static int TestSNodBlqCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SNodBlqCrear 01:\n" );

	SNodoBlq * p_nodObj = CrearNodoEntero ( 42 );
	if ( ES_NULO ( p_nodObj ) )
	{
		printf( "Error caso 1: no se esperaba nulo al crear\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SNodBlqEsValido ( p_nodObj ) != 1 )
		{
			printf( "Error caso 2: el nodo recien creado deberia ser valido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SNodBlqEntero ( p_nodObj ) != 42 )
		{
			printf( "Error caso 3: se esperaba el valor 42\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SNodBlqTienePadre ( p_nodObj ) != 0 ) || ( SNodBlqTieneHijos ( p_nodObj ) != 0 ) )
		{
			printf( "Error caso 4: el nodo no deberia tener padre ni hijos\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	SNodBlqDestruir ( &p_nodObj, 1 );

	if ( ES_VALIDO ( p_nodObj ) )
	{
		printf( "Error caso 5: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( SNodBlqCrear ( 0 ) ) )
	{
		printf( "Error caso 6: se esperaba nulo al crear con tam 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSNodBlqArbol01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SNodBlqArbol 01:\n" );

	SNodoBlq * p_n1 = CrearNodoEntero ( 1 );
	if ( ES_VALIDO ( p_n1 ) )
	{
		SNodoBlq * p_n2 = CrearNodoEntero ( 2 );
		SNodoBlq * p_n4 = CrearNodoEntero ( 4 );
		if ( SNodBlqInsertarHijo ( p_n1, p_n2 ) == 0 )
		{
			printf( "Error insertando hijo 1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SNodBlqInsertarHijo ( p_n1, CrearNodoEntero ( 3 ) ) == 0 )
		{
			printf( "Error insertando hijo 2\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SNodBlqInsertarHijo ( p_n1, p_n4 ) == 0 )
		{
			printf( "Error insertando hijo 3\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SNodBlqNumHijos ( p_n1 ) != 3 )
		{
			printf( "Error caso 1: se esperaban 3 hijos: %d\n", SNodBlqNumHijos ( p_n1 ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SNodBlqEntero ( SNodBlqHijo ( p_n1, 0 ) ) != 2 ) ||
			 ( SNodBlqEntero ( SNodBlqHijo ( p_n1, 1 ) ) != 3 ) ||
			 ( SNodBlqEntero ( SNodBlqHijo ( p_n1, 2 ) ) != 4 ) )
		{
			printf( "Error caso 2: los hijos deberian ser 2, 3 y 4 en ese orden\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SNodBlqPadre ( p_n2 ) != p_n1 ) || ( SNodBlqTienePadre ( p_n2 ) != 1 ) )
		{
			printf( "Error caso 3: el hijo deberia tener como padre el nodo 1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SNodBlqTieneHermanos ( p_n2 ) != 1 ) || ( SNodBlqTieneHermanosDer ( p_n2 ) != 1 ) )
		{
			printf( "Error caso 4: el 2 deberia tener hermanos, con alguno a la derecha\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SNodBlqNodosInferiores ( p_n1 ) != 3 )
		{
			printf( "Error caso 5: se esperaban 3 nodos inferiores: %d\n", SNodBlqNodosInferiores ( p_n1 ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SNodBlqNivelesInferiores ( p_n1 ) != 1 )
		{
			printf( "Error caso 6: se esperaba 1 nivel inferior: %d\n", SNodBlqNivelesInferiores ( p_n1 ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SNodBlqProfundidad ( p_n1 ) != 0 ) || ( SNodBlqProfundidad ( p_n2 ) != 1 ) )
		{
			printf( "Error caso 7: la profundidad de raiz/hijo deberia ser 0/1\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el nodo raiz\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SNodBlqDestruir ( &p_n1, 1 );
	return ( iRes );
}

static int TestSNodBlqEliminar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SNodBlqEliminar 01:\n" );

	SNodoBlq * p_n1 = CrearNodoEntero ( 1 );
	if ( ES_VALIDO ( p_n1 ) )
	{
		if ( SNodBlqInsertarHijo ( p_n1, CrearNodoEntero ( 2 ) ) == 0 )
		{
			printf( "Error insertando hijo 1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SNodBlqInsertarHijo ( p_n1, CrearNodoEntero ( 3 ) ) == 0 )
		{
			printf( "Error insertando hijo 2\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SNodBlqInsertarHijo ( p_n1, CrearNodoEntero ( 4 ) ) == 0 )
		{
			printf( "Error insertando hijo 3\n" );
			iRes = BOOL_VAL_FALSO;
		}

		if ( SNodBlqEliminarHijo ( p_n1, 1, 1 ) != 1 )
		{
			printf( "Error caso 1: se esperaba resultado 1 al eliminar el hijo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SNodBlqNumHijos ( p_n1 ) != 2 )
		{
			printf( "Error caso 2: deberian quedar 2 hijos\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SNodBlqEntero ( SNodBlqHijo ( p_n1, 0 ) ) != 2 ) || ( SNodBlqEntero ( SNodBlqHijo ( p_n1, 1 ) ) != 4 ) )
		{
			printf( "Error caso 3: tras eliminar el 3, deberian quedar el 2 y el 4. Quedan %d y %d\n", SNodBlqEntero ( SNodBlqHijo ( p_n1, 0 ) ), SNodBlqEntero ( SNodBlqHijo ( p_n1, 1 ) ) );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el nodo raiz\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SNodBlqDestruir ( &p_n1, 1 );
	return ( iRes );
}

static int TestSNodBlqDuplicar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SNodBlqDuplicar 01:\n" );

	SNodoBlq * p_nodObj = CrearNodoEntero ( 777 );
	if ( ES_VALIDO ( p_nodObj ) )
	{
		SNodoBlq * p_nodDup = SNodBlqDuplicar ( p_nodObj );
		if ( ES_NULO ( p_nodDup ) )
		{
			printf( "Error caso 1: no se esperaba nulo al duplicar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		else
		{
			if ( SNodBlqEntero ( p_nodDup ) != 777 )
			{
				printf( "Error caso 2: el duplicado deberia contener 777\n" );
				iRes = BOOL_VAL_FALSO;
			}
			/* Copia independiente: modificar el original no afecta al duplicado. */
			SNodBlqEscribirEntero ( p_nodObj, 888 );
			if ( SNodBlqEntero ( p_nodDup ) != 777 )
			{
				printf( "Error caso 3: el duplicado no deberia compartir datos con el original\n" );
				iRes = BOOL_VAL_FALSO;
			}
			SNodBlqDestruir ( &p_nodDup, 1 );
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el nodo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SNodBlqDestruir ( &p_nodObj, 1 );
	return ( iRes );
}

static int TestSNodBlqInvalidos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SNodBlqInvalidos 01:\n" );

	if ( SNodBlqEsValido ( NULL ) != 0 )
	{
		printf( "Error caso 1: un nodo nulo no deberia ser valido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SNodBlqNumHijos ( NULL ) != 0 )
	{
		printf( "Error caso 2: un nodo nulo no deberia tener hijos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SNodBlqNodosInferiores ( NULL ) != 0 )
	{
		printf( "Error caso 3: un nodo nulo no deberia tener nodos inferiores\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SNodoBlq * p_nodNulo = NULL;
	SNodBlqDestruir ( &p_nodNulo, 1 );
	return ( iRes );
}



int TestSNodoPorBloques ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SNodoPorBloques]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSNodBlqCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSNodBlqArbol01 () == BOOL_VAL_CIERTO ) &&
			( TestSNodBlqEliminar01 () == BOOL_VAL_CIERTO ) &&
			( TestSNodBlqDuplicar01 () == BOOL_VAL_CIERTO ) &&
			( TestSNodBlqInvalidos01 () == BOOL_VAL_CIERTO ) )
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
