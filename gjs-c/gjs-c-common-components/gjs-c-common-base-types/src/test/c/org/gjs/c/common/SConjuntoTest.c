#include "Base.h"

#include "SConjunto.h"



static int CompararEnteros ( void * p_vVal1, void * p_vVal2 )
{
	int iVal1 = *( (int *) p_vVal1 );
	int iVal2 = *( (int *) p_vVal2 );
	int iRes = 0;

	if ( iVal1 < iVal2 )
	{
		iRes = -1;
	}
	else if ( iVal1 > iVal2 )
	{
		iRes = 1;
	}
	return ( iRes );
}

static SElemento * CrearElementoEntero ( int iValor )
{
	SElemento * p_elmObj = SElmCrearEntero ();
	if ( ES_VALIDO ( p_elmObj ) )
	{
		SElmEscribirEntero ( p_elmObj, iValor );
	}
	return ( p_elmObj );
}



static int TestSCnjCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCnjCrear 01:\n" );

	SConjunto * p_cnjObj = SCnjCrear ( CompararEnteros );
	if ( ES_NULO ( p_cnjObj ) )
	{
		printf( "Error caso 1: no se esperaba nulo al crear\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SCnjEsValido ( p_cnjObj ) != 1 )
		{
			printf( "Error caso 2: el conjunto recien creado deberia ser valido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCnjEstaVacio ( p_cnjObj ) != 1 )
		{
			printf( "Error caso 3: el conjunto recien creado deberia estar vacio\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCnjNumElementos ( p_cnjObj ) != 0 )
		{
			printf( "Error caso 4: se esperaban 0 elementos\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	SCnjDestruir ( &p_cnjObj );

	if ( ES_VALIDO ( p_cnjObj ) )
	{
		printf( "Error caso 5: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSCnjInsertar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCnjInsertar 01:\n" );

	SConjunto * p_cnjObj = SCnjCrear ( CompararEnteros );
	if ( ES_VALIDO ( p_cnjObj ) )
	{
		/* Se insertan desordenados; el conjunto los mantiene ordenados y sin repetir. */
		if ( SCnjInsertarElem ( p_cnjObj, CrearElementoEntero ( 30 ) ) != 1 )
		{
			printf( "Error caso 1: se esperaba resultado 1 al insertar el primero\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SCnjInsertarElem ( p_cnjObj, CrearElementoEntero ( 10 ) );
		SCnjInsertarElem ( p_cnjObj, CrearElementoEntero ( 20 ) );

		if ( SCnjNumElementos ( p_cnjObj ) != 3 )
		{
			printf( "Error caso 2: se esperaban 3 elementos\n" );
			iRes = BOOL_VAL_FALSO;
		}
		int iEsp [ 3 ] = { 10, 20, 30 };
		int iPos = 0;
		while ( ( iPos < 3 ) && ( iRes == BOOL_VAL_CIERTO ) )
		{
			SElemento * p_elmObj = SCnjElemento ( p_cnjObj, iPos );
			if ( ES_NULO ( p_elmObj ) || ( SElmEntero ( p_elmObj ) != iEsp [ iPos ] ) )
			{
				printf( "Error caso 3: en la posicion %d se esperaba %d\n", iPos, iEsp [ iPos ] );
				iRes = BOOL_VAL_FALSO;
			}
			iPos = iPos + 1;
		}
		/* Insertar un duplicado no debe anadirse; el conjunto no toma el elemento. */
		SElemento * p_elmDup = CrearElementoEntero ( 20 );
		if ( SCnjInsertarElem ( p_cnjObj, p_elmDup ) != -1 )
		{
			printf( "Error caso 4: insertar un duplicado deberia devolver -1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SElmDestruir ( &p_elmDup );
		if ( SCnjNumElementos ( p_cnjObj ) != 3 )
		{
			printf( "Error caso 5: el conjunto no deberia crecer con un duplicado\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el conjunto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SCnjDestruir ( &p_cnjObj );
	return ( iRes );
}

static int TestSCnjExiste01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCnjExiste 01:\n" );

	SConjunto * p_cnjObj = SCnjCrear ( CompararEnteros );
	if ( ES_VALIDO ( p_cnjObj ) )
	{
		SCnjInsertarElem ( p_cnjObj, CrearElementoEntero ( 10 ) );
		SCnjInsertarElem ( p_cnjObj, CrearElementoEntero ( 20 ) );
		SCnjInsertarElem ( p_cnjObj, CrearElementoEntero ( 30 ) );

		SBloque * p_blqBuscar = SBlqCrearEntero ();
		if ( ES_VALIDO ( p_blqBuscar ) )
		{
			SBlqEscribirEntero ( p_blqBuscar, 20 );
			if ( SCnjExiste ( p_cnjObj, p_blqBuscar ) != 1 )
			{
				printf( "Error caso 1: el 20 deberia existir\n" );
				iRes = BOOL_VAL_FALSO;
			}
			if ( SCnjBuscar ( p_cnjObj, p_blqBuscar ) != 1 )
			{
				printf( "Error caso 2: el 20 deberia estar en la posicion 1\n" );
				iRes = BOOL_VAL_FALSO;
			}
			/* Mayor que el maximo: no existe ( valida el arreglo de la busqueda ). */
			SBlqEscribirEntero ( p_blqBuscar, 99 );
			if ( SCnjExiste ( p_cnjObj, p_blqBuscar ) != 0 )
			{
				printf( "Error caso 3: el 99 no deberia existir\n" );
				iRes = BOOL_VAL_FALSO;
			}
		}
		SBlqDestruir ( &p_blqBuscar );
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el conjunto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SCnjDestruir ( &p_cnjObj );
	return ( iRes );
}

static int TestSCnjExisteExt01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCnjExisteExt 01:\n" );

	SConjunto * p_cnjObj = SCnjCrear ( CompararEnteros );
	if ( ES_VALIDO ( p_cnjObj ) )
	{
		SCnjInsertarElem ( p_cnjObj, CrearElementoEntero ( 10 ) );
		SCnjInsertarElem ( p_cnjObj, CrearElementoEntero ( 20 ) );
		SCnjInsertarElem ( p_cnjObj, CrearElementoEntero ( 30 ) );

		int iBuscar = 20;
		if ( SCnjExisteExt ( p_cnjObj, (byte *) &iBuscar ) != 1 )
		{
			printf( "Error caso 1: el 20 deberia existir\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCnjBuscarExt ( p_cnjObj, (byte *) &iBuscar ) != 1 )
		{
			printf( "Error caso 2: el 20 deberia estar en la posicion 1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Mayor que el maximo: no existe. */
		iBuscar = 99;
		if ( SCnjExisteExt ( p_cnjObj, (byte *) &iBuscar ) != 0 )
		{
			printf( "Error caso 3: el 99 no deberia existir\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el conjunto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SCnjDestruir ( &p_cnjObj );
	return ( iRes );
}

static int TestSCnjEliminar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCnjEliminar 01:\n" );

	SConjunto * p_cnjObj = SCnjCrear ( CompararEnteros );
	if ( ES_VALIDO ( p_cnjObj ) )
	{
		SCnjInsertarElem ( p_cnjObj, CrearElementoEntero ( 10 ) );
		SCnjInsertarElem ( p_cnjObj, CrearElementoEntero ( 20 ) );
		SCnjInsertarElem ( p_cnjObj, CrearElementoEntero ( 30 ) );

		SCnjEliminarElem ( p_cnjObj, 1 );
		if ( SCnjNumElementos ( p_cnjObj ) != 2 )
		{
			printf( "Error caso 1: se esperaban 2 elementos tras eliminar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* El 20 ya no debe existir. */
		SBloque * p_blqBuscar = SBlqCrearEntero ();
		if ( ES_VALIDO ( p_blqBuscar ) )
		{
			SBlqEscribirEntero ( p_blqBuscar, 20 );
			if ( SCnjExiste ( p_cnjObj, p_blqBuscar ) != 0 )
			{
				printf( "Error caso 2: el 20 no deberia existir tras eliminarlo\n" );
				iRes = BOOL_VAL_FALSO;
			}
		}
		SBlqDestruir ( &p_blqBuscar );

		if ( SCnjVaciar ( p_cnjObj ) != 1 )
		{
			printf( "Error caso 3: se esperaba resultado 1 al vaciar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCnjEstaVacio ( p_cnjObj ) != 1 )
		{
			printf( "Error caso 4: el conjunto deberia quedar vacio\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el conjunto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SCnjDestruir ( &p_cnjObj );
	return ( iRes );
}

static int TestSCnjInvalidos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCnjInvalidos 01:\n" );

	if ( SCnjEsValido ( NULL ) != 0 )
	{
		printf( "Error caso 1: un conjunto nulo no deberia ser valido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SCnjNumElementos ( NULL ) != 0 )
	{
		printf( "Error caso 2: el numero de elementos de un conjunto nulo deberia ser 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SCnjEstaVacio ( NULL ) != 1 )
	{
		printf( "Error caso 3: un conjunto nulo deberia considerarse vacio\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SConjunto * p_cnjNulo = NULL;
	SCnjDestruir ( &p_cnjNulo );
	return ( iRes );
}



int TestSConjunto ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SConjunto]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSCnjCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSCnjInsertar01 () == BOOL_VAL_CIERTO ) &&
			( TestSCnjExiste01 () == BOOL_VAL_CIERTO ) &&
			( TestSCnjExisteExt01 () == BOOL_VAL_CIERTO ) &&
			( TestSCnjEliminar01 () == BOOL_VAL_CIERTO ) &&
			( TestSCnjInvalidos01 () == BOOL_VAL_CIERTO ) )
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
