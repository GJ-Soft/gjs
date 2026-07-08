#include "Base.h"

#include "SNodoBin.h"



static int TestSNodBinCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SNodBinCrear 01:\n" );

	SNodoBin * p_nodbObj = SNodBinCrearEntero ( 42 );
	if ( ES_NULO ( p_nodbObj ) )
	{
		printf( "Error caso 1: no se esperaba nulo al crear\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SNodBinEsValido ( p_nodbObj ) != 1 )
		{
			printf( "Error caso 2: el nodo recien creado deberia ser valido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SNodBinEntero ( p_nodbObj ) != 42 )
		{
			printf( "Error caso 3: se esperaba el valor 42\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Un nodo recien creado no tiene padre ni hijos. */
		if ( ( SNodBinTienePadre ( p_nodbObj ) != 0 ) || ( SNodBinTieneHijos ( p_nodbObj ) != 0 ) )
		{
			printf( "Error caso 4: el nodo no deberia tener padre ni hijos\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	SNodBinDestruir ( &p_nodbObj, 1 );

	if ( ES_VALIDO ( p_nodbObj ) )
	{
		printf( "Error caso 5: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* Crear con tam 0 debe fallar. */
	if ( ES_VALIDO ( SNodBinCrearMem ( 0 ) ) )
	{
		printf( "Error caso 6: se esperaba nulo al crear con tam 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSNodBinArbol01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SNodBinArbol 01:\n" );

	SNodoBin * p_raiz = SNodBinCrearEntero ( 1 );
	if ( ES_VALIDO ( p_raiz ) )
	{
		/* Se cuelgan dos hijos ( sin liberar, no habia hijos previos ). */
		SNodBinEstHijoIzq ( p_raiz, SNodBinCrearEntero ( 2 ), 0 );
		SNodBinEstHijoDer ( p_raiz, SNodBinCrearEntero ( 3 ), 0 );

		SNodoBin * p_izq = SNodBinHijoIzq ( p_raiz );
		SNodoBin * p_der = SNodBinHijoDer ( p_raiz );

		if ( ( SNodBinEntero ( p_izq ) != 2 ) || ( SNodBinEntero ( p_der ) != 3 ) )
		{
			printf( "Error caso 1: los hijos deberian valer 2 y 3\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Enlace hacia el padre. */
		if ( ( SNodBinPadre ( p_izq ) != p_raiz ) || ( SNodBinTienePadre ( p_izq ) != 1 ) )
		{
			printf( "Error caso 2: el hijo izquierdo deberia tener como padre la raiz\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SNodBinEsHijoIzqDelPadre ( p_izq ) != 1 ) || ( SNodBinEsHijoDerDelPadre ( p_der ) != 1 ) )
		{
			printf( "Error caso 3: la relacion hijo-izq / hijo-der no es correcta\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Hermandad. */
		if ( ( SNodBinTieneHermano ( p_izq ) != 1 ) || ( SNodBinTieneHermanoDer ( p_izq ) != 1 ) )
		{
			printf( "Error caso 4: el hijo izquierdo deberia tener un hermano a la derecha\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Metricas del arbol. */
		if ( SNodBinNodosInferiores ( p_raiz ) != 2 )
		{
			printf( "Error caso 5: se esperaban 2 nodos inferiores: %d\n", SNodBinNodosInferiores ( p_raiz ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SNodBinNivelesInferiores ( p_raiz ) != 1 )
		{
			printf( "Error caso 6: se esperaba 1 nivel inferior\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SNodBinProfundidad ( p_raiz ) != 0 ) || ( SNodBinProfundidad ( p_izq ) != 1 ) )
		{
			printf( "Error caso 7: la profundidad de raiz/hijo deberia ser 0/1\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la raiz\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* Destruir la raiz destruye tambien el subarbol. */
	SNodBinDestruir ( &p_raiz, 1 );
	return ( iRes );
}

static int TestSNodBinEliminar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SNodBinEliminar 01:\n" );

	SNodoBin * p_raiz = SNodBinCrearEntero ( 1 );
	if ( ES_VALIDO ( p_raiz ) )
	{
		SNodBinEstHijoIzq ( p_raiz, SNodBinCrearEntero ( 2 ), 0 );
		SNodBinEstHijoDer ( p_raiz, SNodBinCrearEntero ( 3 ), 0 );

		/* Eliminar el hijo izquierdo ( liberandolo ). */
		if ( SNodBinEliminarHijoIzq ( p_raiz, 1 ) != 1 )
		{
			printf( "Error caso 1: se esperaba resultado 1 al eliminar el hijo izquierdo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SNodBinTieneHijoIzq ( p_raiz ) != 0 )
		{
			printf( "Error caso 2: la raiz ya no deberia tener hijo izquierdo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SNodBinTieneHijoDer ( p_raiz ) != 1 )
		{
			printf( "Error caso 3: la raiz deberia conservar el hijo derecho\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SNodBinNodosInferiores ( p_raiz ) != 1 )
		{
			printf( "Error caso 4: deberia quedar 1 nodo inferior\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la raiz\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SNodBinDestruir ( &p_raiz, 1 );
	return ( iRes );
}

static int TestSNodBinDuplicar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SNodBinDuplicar 01:\n" );

	SNodoBin * p_nodbObj = SNodBinCrearEntero ( 777 );
	if ( ES_VALIDO ( p_nodbObj ) )
	{
		SNodoBin * p_nodbDup = SNodBinDuplicar ( p_nodbObj );
		if ( ES_NULO ( p_nodbDup ) )
		{
			printf( "Error caso 1: no se esperaba nulo al duplicar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		else
		{
			if ( SNodBinEntero ( p_nodbDup ) != 777 )
			{
				printf( "Error caso 2: el duplicado deberia contener 777\n" );
				iRes = BOOL_VAL_FALSO;
			}
			/* Copia independiente: modificar el original no afecta al duplicado. */
			SNodBinEstablecerEntero ( p_nodbObj, 888 );
			if ( SNodBinEntero ( p_nodbDup ) != 777 )
			{
				printf( "Error caso 3: el duplicado no deberia compartir datos con el original\n" );
				iRes = BOOL_VAL_FALSO;
			}
			SNodBinDestruir ( &p_nodbDup, 1 );
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el nodo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SNodBinDestruir ( &p_nodbObj, 1 );
	return ( iRes );
}

static int TestSNodBinInvalidos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SNodBinInvalidos 01:\n" );

	if ( SNodBinEsValido ( NULL ) != 0 )
	{
		printf( "Error caso 1: un nodo nulo no deberia ser valido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SNodBinTieneHijos ( NULL ) != 0 )
	{
		printf( "Error caso 2: un nodo nulo no deberia tener hijos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SNodBinNodosInferiores ( NULL ) != 0 )
	{
		printf( "Error caso 3: un nodo nulo no deberia tener nodos inferiores\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SNodoBin * p_nodbNulo = NULL;
	SNodBinDestruir ( &p_nodbNulo, 1 );
	return ( iRes );
}



int TestSNodoBin ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SNodoBin]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSNodBinCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSNodBinArbol01 () == BOOL_VAL_CIERTO ) &&
			( TestSNodBinEliminar01 () == BOOL_VAL_CIERTO ) &&
			( TestSNodBinDuplicar01 () == BOOL_VAL_CIERTO ) &&
			( TestSNodBinInvalidos01 () == BOOL_VAL_CIERTO ) )
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
