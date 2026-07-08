#include "Base.h"

#include "SNodoBinPtr.h"



static byte * CrearDatoEntero ( int iValor )
{
	int * p_iDato = (int *) MemReservar ( sizeof ( int ) );
	if ( ES_VALIDO ( p_iDato ) )
	{
		*p_iDato = iValor;
	}
	return ( (byte *) p_iDato );
}

static int ValorNodo ( SNodoBinPtr * p_nodbpObj )
{
	return ( *( (int *) SNodBinPtrDatos ( p_nodbpObj ) ) );
}



static int TestSNodBinPtrCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SNodBinPtrCrear 01:\n" );

	SNodoBinPtr * p_nodbpObj = SNodBinPtrCrear ( CrearDatoEntero ( 42 ), 1 );
	if ( ES_NULO ( p_nodbpObj ) )
	{
		printf( "Error caso 1: no se esperaba nulo al crear\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SNodBinPtrEsValido ( p_nodbpObj ) != 1 )
		{
			printf( "Error caso 2: el nodo recien creado deberia ser valido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ValorNodo ( p_nodbpObj ) != 42 )
		{
			printf( "Error caso 3: se esperaba el valor 42\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SNodBinPtrTienePadre ( p_nodbpObj ) != 0 ) || ( SNodBinPtrTieneHijos ( p_nodbpObj ) != 0 ) )
		{
			printf( "Error caso 4: el nodo no deberia tener padre ni hijos\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	SNodBinPtrDestruir ( &p_nodbpObj, 1 );

	if ( ES_VALIDO ( p_nodbpObj ) )
	{
		printf( "Error caso 5: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( SNodBinPtrCrear ( NULL, 1 ) ) )
	{
		printf( "Error caso 6: se esperaba nulo al crear con datos nulos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSNodBinPtrArbol01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SNodBinPtrArbol 01:\n" );

	SNodoBinPtr * p_raiz = SNodBinPtrCrear ( CrearDatoEntero ( 1 ), 1 );
	if ( ES_VALIDO ( p_raiz ) )
	{
		SNodBinPtrEstHijoIzq ( p_raiz, SNodBinPtrCrear ( CrearDatoEntero ( 2 ), 1 ), 0 );
		SNodBinPtrEstHijoDer ( p_raiz, SNodBinPtrCrear ( CrearDatoEntero ( 3 ), 1 ), 0 );

		SNodoBinPtr * p_izq = SNodBinPtrHijoIzq ( p_raiz );
		SNodoBinPtr * p_der = SNodBinPtrHijoDer ( p_raiz );

		if ( ( ValorNodo ( p_izq ) != 2 ) || ( ValorNodo ( p_der ) != 3 ) )
		{
			printf( "Error caso 1: los hijos deberian valer 2 y 3\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SNodBinPtrPadre ( p_izq ) != p_raiz ) || ( SNodBinPtrTienePadre ( p_izq ) != 1 ) )
		{
			printf( "Error caso 2: el hijo izquierdo deberia tener como padre la raiz\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SNodBinPtrEsHijoIzqDelPadre ( p_izq ) != 1 ) || ( SNodBinPtrEsHijoDerDelPadre ( p_der ) != 1 ) )
		{
			printf( "Error caso 3: la relacion hijo-izq / hijo-der no es correcta\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SNodBinPtrTieneHermano ( p_izq ) != 1 )
		{
			printf( "Error caso 4: el hijo izquierdo deberia tener hermano\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SNodBinPtrNodosInferiores ( p_raiz ) != 2 )
		{
			printf( "Error caso 5: se esperaban 2 nodos inferiores: %d\n", SNodBinPtrNodosInferiores ( p_raiz ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SNodBinPtrNivelesInferiores ( p_raiz ) != 1 )
		{
			printf( "Error caso 6: se esperaba 1 nivel inferior: %d\n", SNodBinPtrNivelesInferiores ( p_raiz ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SNodBinPtrProfundidad ( p_raiz ) != 0 ) || ( SNodBinPtrProfundidad ( p_izq ) != 1 ) )
		{
			printf( "Error caso 7: la profundidad de raiz/hijo deberia ser 0/1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Eliminar el hijo izquierdo. */
		SNodBinPtrEliminarHijoIzq ( p_raiz, 1 );
		if ( ( SNodBinPtrTieneHijoIzq ( p_raiz ) != 0 ) || ( SNodBinPtrTieneHijoDer ( p_raiz ) != 1 ) )
		{
			printf( "Error caso 8: tras eliminar el izquierdo solo deberia quedar el derecho\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la raiz\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SNodBinPtrDestruir ( &p_raiz, 1 );
	return ( iRes );
}

static int TestSNodBinPtrInvalidos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SNodBinPtrInvalidos 01:\n" );

	if ( SNodBinPtrEsValido ( NULL ) != 0 )
	{
		printf( "Error caso 1: un nodo nulo no deberia ser valido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SNodBinPtrTieneHijos ( NULL ) != 0 )
	{
		printf( "Error caso 2: un nodo nulo no deberia tener hijos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SNodoBinPtr * p_nodbpNulo = NULL;
	SNodBinPtrDestruir ( &p_nodbpNulo, 1 );
	return ( iRes );
}



int TestSNodoBinPtr ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SNodoBinPtr]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSNodBinPtrCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSNodBinPtrArbol01 () == BOOL_VAL_CIERTO ) &&
			( TestSNodBinPtrInvalidos01 () == BOOL_VAL_CIERTO ) )
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
