#include "Base.h"

#include "SConjuntoReferencias.h"



static int AliasElementoEs ( SConjuntoReferencias * p_cnjObj, int iElem, const char * p_cEsperado )
{
	return ( CadComparar ( (char *) SCnjRefAliasElemento ( p_cnjObj, iElem ), (char *) p_cEsperado ) == COMP_IGUAL );
}



static int TestSCnjRefOperaciones01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCnjRefOperaciones 01:\n" );

	/* Los datos ( externos ) viven en la pila del test; el conjunto posee las referencias. */
	int iApple = 10;
	int iBanana = 20;
	int iCherry = 30;
	SConjuntoReferencias * p_cnjObj = SCnjRefCrear ();
	if ( ES_VALIDO ( p_cnjObj ) )
	{
		if ( ( SCnjRefEsValido ( p_cnjObj ) != 1 ) || ( SCnjRefEstaVacio ( p_cnjObj ) != 1 ) )
		{
			printf( "Error caso 1: el conjunto recien creado deberia ser valido y estar vacio\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Se insertan en desorden; el conjunto los mantiene ordenados por alias. */
		if ( ( SCnjRefInsertarExt ( p_cnjObj, "banana", &iBanana ) != 1 ) ||
			 ( SCnjRefInsertarExt ( p_cnjObj, "apple", &iApple ) != 1 ) ||
			 ( SCnjRefInsertarExt ( p_cnjObj, "cherry", &iCherry ) != 1 ) )
		{
			printf( "Error caso 2: se esperaba poder insertar las tres referencias\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCnjRefNumElementos ( p_cnjObj ) != 3 )
		{
			printf( "Error caso 3: el conjunto deberia tener 3 elementos\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Orden alfabetico por alias. */
		if ( ( ! AliasElementoEs ( p_cnjObj, 0, "apple" ) ) ||
			 ( ! AliasElementoEs ( p_cnjObj, 1, "banana" ) ) ||
			 ( ! AliasElementoEs ( p_cnjObj, 2, "cherry" ) ) )
		{
			printf( "Error caso 4: las referencias deberian quedar ordenadas por alias\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Los datos siguen a su alias. */
		if ( SCnjRefDatosElemento ( p_cnjObj, 0 ) != (void *) &iApple )
		{
			printf( "Error caso 5: los datos del indice 0 deberian ser los de \"apple\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SCnjRefExiste ( p_cnjObj, "banana" ) != 1 ) || ( SCnjRefExiste ( p_cnjObj, "grape" ) != 0 ) )
		{
			printf( "Error caso 6: existe deberia encontrar \"banana\" y no \"grape\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Buscar devuelve la referencia, la del conjunto; si no esta, nulo. */
		if ( ( SRefObtenerDatos ( SCnjRefBuscar ( p_cnjObj, "cherry" ) ) != (void *) &iCherry ) ||
			 ( SCnjRefBuscar ( p_cnjObj, "grape" ) != NULL ) )
		{
			printf( "Error caso 7: buscar \"cherry\" deberia dar sus datos y \"grape\" nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Eliminar por alias. */
		if ( ( SCnjRefEliminar ( p_cnjObj, "apple" ) != 1 ) ||
			 ( SCnjRefNumElementos ( p_cnjObj ) != 2 ) || ( ! AliasElementoEs ( p_cnjObj, 0, "banana" ) ) )
		{
			printf( "Error caso 8: tras eliminar \"apple\" la cabeza deberia ser \"banana\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SCnjRefVaciar ( p_cnjObj );
		if ( SCnjRefEstaVacio ( p_cnjObj ) != 1 )
		{
			printf( "Error caso 9: tras vaciar el conjunto deberia estar vacio\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el conjunto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SCnjRefDestruir ( &p_cnjObj );

	if ( ES_VALIDO ( p_cnjObj ) )
	{
		printf( "Error caso 10: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

/* Es un conjunto: un alias repetido no entra, y se queda la primera
   referencia. Insertar no se queda con la que rechaza; InsertarExt la
   destruye. */
static int TestSCnjRefRepetidos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCnjRefRepetidos 01:\n" );

	int iUno = 1;
	int iDos = 2;
	SConjuntoReferencias * p_cnjObj = SCnjRefCrear ();
	SReferencia * p_refRepetida = SRefCrear ( "uno", &iDos );
	SReferencia * p_refSinDatos = SRefCrear ( "tres", NULL );
	if ( ES_VALIDO ( p_cnjObj ) && ES_VALIDO ( p_refRepetida ) && ES_VALIDO ( p_refSinDatos ) )
	{
		if ( ( SCnjRefInsertarExt ( p_cnjObj, "uno", &iUno ) != 1 ) ||
			 ( SCnjRefInsertarExt ( p_cnjObj, "uno", &iDos ) != 0 ) ||
			 ( SCnjRefInsertar ( p_cnjObj, p_refRepetida ) != 0 ) )
		{
			printf( "Error caso 1: se esperaba 1 y luego 0 para el alias repetido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SCnjRefNumElementos ( p_cnjObj ) != 1 ) || ( SCnjRefDatosElemento ( p_cnjObj, 0 ) != (void *) &iUno ) )
		{
			printf( "Error caso 2: deberia quedar solo \"uno\" con sus primeros datos\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Una referencia sin datos no es valida y no entra. */
		if ( ( SCnjRefInsertar ( p_cnjObj, p_refSinDatos ) != 0 ) || ( SCnjRefInsertar ( p_cnjObj, NULL ) != 0 ) ||
			 ( SCnjRefInsertarExt ( p_cnjObj, NULL, &iUno ) != 0 ) || ( SCnjRefNumElementos ( p_cnjObj ) != 1 ) )
		{
			printf( "Error caso 3: una referencia sin datos, nula o sin alias no deberia entrar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Eliminar lo que no esta da 0 sin tocar nada. */
		if ( ( SCnjRefEliminar ( p_cnjObj, "dos" ) != 0 ) || ( SCnjRefEliminarElem ( p_cnjObj, 5 ) != 0 ) ||
			 ( SCnjRefEliminarElem ( p_cnjObj, -1 ) != 0 ) || ( SCnjRefEliminar ( p_cnjObj, NULL ) != 0 ) ||
			 ( SCnjRefNumElementos ( p_cnjObj ) != 1 ) )
		{
			printf( "Error caso 4: eliminar lo que no esta deberia dar 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SCnjRefEliminarElem ( p_cnjObj, 0 ) != 1 ) || ( SCnjRefEstaVacio ( p_cnjObj ) != 1 ) ||
			 ( SCnjRefExiste ( p_cnjObj, "uno" ) != 0 ) )
		{
			printf( "Error caso 5: eliminar la posicion 0 deberia vaciarlo\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el conjunto o las referencias\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SRefDestruir ( &p_refRepetida );
	SRefDestruir ( &p_refSinDatos );
	SCnjRefDestruir ( &p_cnjObj );
	return ( iRes );
}

static int TestSCnjRefInvalidos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCnjRefInvalidos 01:\n" );

	if ( SCnjRefEsValido ( NULL ) != 0 )
	{
		printf( "Error caso 1: un conjunto nulo no deberia ser valido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ( SCnjRefExiste ( NULL, "x" ) != 0 ) || ( SCnjRefNumElementos ( NULL ) != 0 ) ||
		 ( SCnjRefEstaVacio ( NULL ) != 1 ) || ES_VALIDO ( SCnjRefBuscar ( NULL, "x" ) ) ||
		 ES_VALIDO ( SCnjRefAliasElemento ( NULL, 0 ) ) || ES_VALIDO ( SCnjRefDatosElemento ( NULL, 0 ) ) ||
		 ( SCnjRefVaciar ( NULL ) != 0 ) )
	{
		printf( "Error caso 2: con un conjunto nulo se esperaba 0, vacio o nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SConjuntoReferencias * p_cnjNula = NULL;
	SCnjRefDestruir ( &p_cnjNula );
	return ( iRes );
}



int TestSConjuntoReferencias ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SConjuntoReferencias]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSCnjRefOperaciones01 () == BOOL_VAL_CIERTO ) &&
			( TestSCnjRefRepetidos01 () == BOOL_VAL_CIERTO ) &&
			( TestSCnjRefInvalidos01 () == BOOL_VAL_CIERTO ) )
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
