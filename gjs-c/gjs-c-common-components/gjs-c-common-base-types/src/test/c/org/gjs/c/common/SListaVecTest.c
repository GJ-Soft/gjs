#include "Base.h"

#include "SListaVec.h"



static int TestSVLisOperaciones01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SVLisOperaciones 01:\n" );

	/* Valores en la pila del test; la lista guarda punteros sin liberarlos ( iLiberar = 0 ). */
	int iA = 1;
	int iB = 2;
	int iC = 3;
	int iD = 4;
	int iE = 5;
	int iF = 6;
	SVLista * p_lisObj = SVLisCrear ( 5, 0 );
	if ( ES_VALIDO ( p_lisObj ) )
	{
		if ( ( SVLisEsValida ( p_lisObj ) != 1 ) || ( SVLisEstaVacia ( p_lisObj ) != 1 ) ||
			 ( SVLisMaxElementos ( p_lisObj ) != 5 ) )
		{
			printf( "Error caso 1: la lista recien creada deberia ser valida, vacia y de maximo 5\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Insertar tres elementos ( se encadenan en orden ). */
		if ( ( SVLisInsertar ( p_lisObj, &iA ) != 1 ) ||
			 ( SVLisInsertar ( p_lisObj, &iB ) != 1 ) ||
			 ( SVLisInsertar ( p_lisObj, &iC ) != 1 ) )
		{
			printf( "Error caso 2: se esperaba poder insertar los tres elementos\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SVLisNumElementos ( p_lisObj ) != 3 ) || ( SVLisEstaVacia ( p_lisObj ) != 0 ) )
		{
			printf( "Error caso 3: la lista deberia tener 3 elementos\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SVLisElemento ( p_lisObj, 0 ) != (void *) &iA ) ||
			 ( SVLisElemento ( p_lisObj, 1 ) != (void *) &iB ) ||
			 ( SVLisElemento ( p_lisObj, 2 ) != (void *) &iC ) )
		{
			printf( "Error caso 4: los elementos deberian recuperarse en orden A, B, C\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Recorrido con cursor. */
		SVLisInicio ( p_lisObj );
		if ( ( SVLisElementoActual ( p_lisObj ) != (void *) &iA ) || ( SVListaEstaEnPrincipio ( p_lisObj ) != 1 ) )
		{
			printf( "Error caso 5: el inicio deberia ser A\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SVLisSiguiente ( p_lisObj );
		if ( SVLisElementoActual ( p_lisObj ) != (void *) &iB )
		{
			printf( "Error caso 6: el siguiente del inicio deberia ser B\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SVLisFinal ( p_lisObj );
		if ( ( SVLisElementoActual ( p_lisObj ) != (void *) &iC ) || ( SVListaEstaEnFinal ( p_lisObj ) != 1 ) )
		{
			printf( "Error caso 7: el final deberia ser C\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Llenar hasta el maximo. */
		SVLisInsertar ( p_lisObj, &iD );
		SVLisInsertar ( p_lisObj, &iE );
		if ( ( SVLisNumElementos ( p_lisObj ) != 5 ) || ( SVLisEstaLlena ( p_lisObj ) != 1 ) )
		{
			printf( "Error caso 8: la lista deberia estar llena con 5 elementos\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Insertar en una lista llena debe fallar. */
		if ( SVLisInsertar ( p_lisObj, &iF ) == 1 )
		{
			printf( "Error caso 9: insertar en una lista llena no deberia tener exito\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Eliminar el primero ( valida el resultado 1 corregido ). */
		if ( ( SVLisEliminar ( p_lisObj, 0 ) != 1 ) ||
			 ( SVLisNumElementos ( p_lisObj ) != 4 ) || ( SVLisElemento ( p_lisObj, 0 ) != (void *) &iB ) )
		{
			printf( "Error caso 10: tras eliminar el primero la cabeza deberia ser B\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SVLisVaciar ( p_lisObj );
		if ( ( SVLisEstaVacia ( p_lisObj ) != 1 ) || ( SVLisNumElementos ( p_lisObj ) != 0 ) )
		{
			printf( "Error caso 11: tras vaciar la lista deberia estar vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la lista\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SVLisDestruir ( &p_lisObj );

	if ( ES_VALIDO ( p_lisObj ) )
	{
		printf( "Error caso 12: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSVLisInvalidos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SVLisInvalidos 01:\n" );

	int iX = 7;

	if ( SVLisEsValida ( NULL ) != 0 )
	{
		printf( "Error caso 1: una lista nula no deberia ser valida\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SVLisNumElementos ( NULL ) != 0 )
	{
		printf( "Error caso 2: una lista nula deberia tener 0 elementos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SVLisInsertar ( NULL, &iX ) == 1 )
	{
		printf( "Error caso 3: insertar en una lista nula no deberia tener exito\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* Crear con maximo 0 debe fallar. */
	if ( ES_VALIDO ( SVLisCrear ( 0, 0 ) ) )
	{
		printf( "Error caso 4: crear con maximo 0 deberia fallar\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SVLista * p_lisNula = NULL;
	SVLisDestruir ( &p_lisNula );
	return ( iRes );
}



int TestSListaVec ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SListaVec]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSVLisOperaciones01 () == BOOL_VAL_CIERTO ) &&
			( TestSVLisInvalidos01 () == BOOL_VAL_CIERTO ) )
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
