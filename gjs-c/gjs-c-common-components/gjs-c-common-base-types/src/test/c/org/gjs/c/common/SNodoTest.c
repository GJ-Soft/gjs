#include "Base.h"

#include "SNodo.h"



/* Cuelga un hijo de un nodo: lo empadrona y lo inserta ( como hace SArbEnraizar ). */
static void ColgarHijo ( SNodo * p_nodPadre, SNodo * p_nodHijo )
{
	SNodEmpadronar ( p_nodHijo, p_nodPadre );
	SNodInsertarHijo ( p_nodPadre, p_nodHijo );
}



static int TestSNodCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SNodCrear 01:\n" );

	SNodo * p_nodObj = SNodCrearEntero ( 42 );
	if ( ES_NULO ( p_nodObj ) )
	{
		printf( "Error caso 1: no se esperaba nulo al crear\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SNodEsValido ( p_nodObj ) != 1 )
		{
			printf( "Error caso 2: el nodo recien creado deberia ser valido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SNodEntero ( p_nodObj ) != 42 )
		{
			printf( "Error caso 3: se esperaba el valor 42\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SNodTienePadre ( p_nodObj ) != 0 ) || ( SNodTieneHijos ( p_nodObj ) != 0 ) )
		{
			printf( "Error caso 4: el nodo no deberia tener padre ni hijos\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	SNodDestruir ( &p_nodObj, 1 );

	if ( ES_VALIDO ( p_nodObj ) )
	{
		printf( "Error caso 5: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( SNodCrear ( 0 ) ) )
	{
		printf( "Error caso 6: se esperaba nulo al crear con tam 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSNodArbol01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SNodArbol 01:\n" );

	/* Nodo 1 con tres hijos 2, 3, 4. */
	SNodo * p_n1 = SNodCrearEntero ( 1 );
	if ( ES_VALIDO ( p_n1 ) )
	{
		SNodo * p_n2 = SNodCrearEntero ( 2 );
		SNodo * p_n4 = SNodCrearEntero ( 4 );
		ColgarHijo ( p_n1, p_n2 );
		ColgarHijo ( p_n1, SNodCrearEntero ( 3 ) );
		ColgarHijo ( p_n1, p_n4 );

		if ( SNodNumHijos ( p_n1 ) != 3 )
		{
			printf( "Error caso 1: se esperaban 3 hijos: %d\n", SNodNumHijos ( p_n1 ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SNodEntero ( SNodHijo ( p_n1, 0 ) ) != 2 ) ||
			 ( SNodEntero ( SNodHijo ( p_n1, 1 ) ) != 3 ) ||
			 ( SNodEntero ( SNodHijo ( p_n1, 2 ) ) != 4 ) )
		{
			printf( "Error caso 2: los hijos deberian ser 2, 3 y 4 en ese orden\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( SNodHijo ( p_n1, 3 ) ) )
		{
			printf( "Error caso 3: un indice de hijo fuera de rango deberia dar nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Enlace hacia el padre. */
		if ( ( SNodPadre ( p_n2 ) != p_n1 ) || ( SNodTienePadre ( p_n2 ) != 1 ) )
		{
			printf( "Error caso 4: el hijo deberia tener como padre el nodo 1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Hermandad y orden. */
		if ( ( SNodTieneHermanos ( p_n2 ) != 1 ) || ( SNodTieneHermanosDer ( p_n2 ) != 1 ) )
		{
			printf( "Error caso 5: el 2 deberia tener hermanos, con alguno a la derecha\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SNodTieneHermanosDer ( p_n4 ) != 0 ) || ( SNodTieneHermanosIzq ( p_n4 ) != 1 ) )
		{
			printf( "Error caso 6: el 4 ( ultimo hijo ) solo deberia tener hermanos a la izquierda\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SNodOrdenDelHijo ( p_n1, p_n4 ) != 2 )
		{
			printf( "Error caso 7: el 4 deberia ser el hijo de orden 2\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Metricas. */
		if ( SNodNodosInferiores ( p_n1 ) != 3 )
		{
			printf( "Error caso 8: se esperaban 3 nodos inferiores: %d\n", SNodNodosInferiores ( p_n1 ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SNodNivelesInferiores ( p_n1 ) != 1 )
		{
			printf( "Error caso 9: se esperaba 1 nivel inferior: %d\n", SNodNivelesInferiores ( p_n1 ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SNodProfundidad ( p_n1 ) != 0 ) || ( SNodProfundidad ( p_n2 ) != 1 ) )
		{
			printf( "Error caso 10: la profundidad de raiz/hijo deberia ser 0/1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* SNodEsHijo: cierto para un hijo, falso para la raiz. */
		if ( ( SNodEsHijo ( p_n2 ) != 1 ) || ( SNodEsHijo ( p_n1 ) != 0 ) )
		{
			printf( "Error caso 11: el 2 deberia ser hijo y la raiz no\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el nodo raiz\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SNodDestruir ( &p_n1, 1 );
	return ( iRes );
}

static int TestSNodEliminar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SNodEliminar 01:\n" );

	SNodo * p_n1 = SNodCrearEntero ( 1 );
	if ( ES_VALIDO ( p_n1 ) )
	{
		ColgarHijo ( p_n1, SNodCrearEntero ( 2 ) );
		ColgarHijo ( p_n1, SNodCrearEntero ( 3 ) );
		ColgarHijo ( p_n1, SNodCrearEntero ( 4 ) );

		/* Eliminar el hijo del medio ( liberandolo ); el resto se recoloca. */
		if ( SNodEliminarHijo ( p_n1, 1, 1 ) != 1 )
		{
			printf( "Error caso 1: se esperaba resultado 1 al eliminar el hijo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SNodNumHijos ( p_n1 ) != 2 )
		{
			printf( "Error caso 2: deberian quedar 2 hijos\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SNodEntero ( SNodHijo ( p_n1, 0 ) ) != 2 ) || ( SNodEntero ( SNodHijo ( p_n1, 1 ) ) != 4 ) )
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
	SNodDestruir ( &p_n1, 1 );
	return ( iRes );
}

static int TestSNodDuplicar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SNodDuplicar 01:\n" );

	SNodo * p_nodObj = SNodCrearEntero ( 777 );
	if ( ES_VALIDO ( p_nodObj ) )
	{
		SNodo * p_nodDup = SNodDuplicar ( p_nodObj );
		if ( ES_NULO ( p_nodDup ) )
		{
			printf( "Error caso 1: no se esperaba nulo al duplicar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		else
		{
			if ( SNodEntero ( p_nodDup ) != 777 )
			{
				printf( "Error caso 2: el duplicado deberia contener 777\n" );
				iRes = BOOL_VAL_FALSO;
			}
			SNodEstablecerEntero ( p_nodObj, 888 );
			if ( SNodEntero ( p_nodDup ) != 777 )
			{
				printf( "Error caso 3: el duplicado no deberia compartir datos con el original\n" );
				iRes = BOOL_VAL_FALSO;
			}
			SNodDestruir ( &p_nodDup, 1 );
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el nodo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SNodDestruir ( &p_nodObj, 1 );
	return ( iRes );
}

static int TestSNodInvalidos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SNodInvalidos 01:\n" );

	if ( SNodEsValido ( NULL ) != 0 )
	{
		printf( "Error caso 1: un nodo nulo no deberia ser valido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SNodNumHijos ( NULL ) != 0 )
	{
		printf( "Error caso 2: un nodo nulo no deberia tener hijos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SNodNodosInferiores ( NULL ) != 0 )
	{
		printf( "Error caso 3: un nodo nulo no deberia tener nodos inferiores\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SNodo * p_nodNulo = NULL;
	SNodDestruir ( &p_nodNulo, 1 );
	return ( iRes );
}



int TestSNodo ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SNodo]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSNodCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSNodArbol01 () == BOOL_VAL_CIERTO ) &&
			( TestSNodEliminar01 () == BOOL_VAL_CIERTO ) &&
			( TestSNodDuplicar01 () == BOOL_VAL_CIERTO ) &&
			( TestSNodInvalidos01 () == BOOL_VAL_CIERTO ) )
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
