#include "Base.h"

#include "SSecuenciaPtr.h"



static byte * CrearDatoEntero ( int iValor )
{
	int * p_iDato = (int *) MemReservar ( sizeof ( int ) );
	if ( ES_VALIDO ( p_iDato ) )
	{
		*p_iDato = iValor;
	}
	return ( (byte *) p_iDato );
}

static int ValorElem ( SSecuenciaPtr * p_secObj, int iElem )
{
	return ( *( (int *) SSecpElemento ( p_secObj, iElem ) ) );
}



/* Igualdad "modulo 10": con ella 12 y 2 son iguales y por bytes no. */
static int SonIgualesMod10 ( byte * p_byDato1, byte * p_byDato2 )
{
	return ( ( ( *( (int *) p_byDato1 ) % 10 ) == ( *( (int *) p_byDato2 ) % 10 ) ) ? 1 : 0 );
}

/* Duplica sumando 100, para ver en el resultado que la copia la hizo ella. */
static byte * DuplicarEnteroMas100 ( byte * p_byDato )
{
	return ( CrearDatoEntero ( *( (int *) p_byDato ) + 100 ) );
}

/* Con la liberacion activada: los datos son de la secuencia. */
static SSecuenciaPtr * CrearSecEnteros ( int * p_iValores, int iNum )
{
	SSecuenciaPtr * p_secObj = SSecpCrear ();
	int iPos = 0;
	while ( ES_VALIDO ( p_secObj ) && ( iPos < iNum ) )
	{
		SSecpInsertar ( p_secObj, CrearDatoEntero ( p_iValores [ iPos ] ) );
		iPos = iPos + 1;
	}
	return ( p_secObj );
}

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

/* Recorre la lista por la cadena comprobando numero y orden de los valores. */
static int VerificarLista ( SListaPtr * p_lisObj, int * p_iEsperados, int iNum )
{
	int iRes = BOOL_VAL_CIERTO;
	if ( SLispNumElementos ( p_lisObj ) != iNum )
	{
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		SElementoPtr * p_elpObj = SLispElementoPtr ( p_lisObj, 0 );
		int iPos = 0;
		while ( ( iRes == BOOL_VAL_CIERTO ) && ( iPos < iNum ) )
		{
			if ( ES_NULO ( p_elpObj ) )
			{
				iRes = BOOL_VAL_FALSO;
			}
			else
			{
				if ( *( (int *) SElpDatos ( p_elpObj ) ) != p_iEsperados [ iPos ] )
				{
					iRes = BOOL_VAL_FALSO;
				}
				p_elpObj = SElpSucesor ( p_elpObj );
			}
			iPos = iPos + 1;
		}
	}
	return ( iRes );
}

static int VerificarSec ( SSecuenciaPtr * p_secObj, int * p_iEsperados, int iNum )
{
	int iRes;
	if ( SSecpEsValida ( p_secObj ) == 1 )
	{
		iRes = VerificarLista ( SSecpLista ( p_secObj ), p_iEsperados, iNum );
	}
	else
	{
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

/* Comprueba una secuencia devuelta por una operacion, que sea duena de sus
   datos, y la destruye. */
static int VerificarYDestruir ( SSecuenciaPtr ** p_p_secObj, int * p_iEsperados, int iNum )
{
	int iRes = VerificarSec ( *p_p_secObj, p_iEsperados, iNum );
	if ( SSecpLiberacionMemoriaActivada ( *p_p_secObj ) != 1 )
	{
		iRes = BOOL_VAL_FALSO;
	}
	SSecpDestruir ( p_p_secObj );
	return ( iRes );
}

static int TestSSecpOperaciones01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SSecpOperaciones 01:\n" );

	/* Los datos los posee el test ( se desactiva la liberacion de la secuencia ). */
	byte * p_d1 = CrearDatoEntero ( 10 );
	byte * p_d2 = CrearDatoEntero ( 20 );
	byte * p_d3 = CrearDatoEntero ( 30 );
	SSecuenciaPtr * p_secObj = SSecpCrear ();
	if ( ES_VALIDO ( p_secObj ) && ES_VALIDO ( p_d1 ) && ES_VALIDO ( p_d2 ) && ES_VALIDO ( p_d3 ) )
	{
		SSecpDesactivarLiberacionMemoria ( p_secObj );

		if ( ( SSecpInsertar ( p_secObj, p_d1 ) != 1 ) ||
			 ( SSecpInsertar ( p_secObj, p_d2 ) != 1 ) ||
			 ( SSecpInsertar ( p_secObj, p_d3 ) != 1 ) )
		{
			printf( "Error caso 1: se esperaba poder insertar los tres datos\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SSecpNumElementos ( p_secObj ) != 3 ) || ( ValorElem ( p_secObj, 1 ) != 20 ) )
		{
			printf( "Error caso 2: deberia haber 3 elementos y el del indice 1 valer 20\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SSecpEstaVacia ( p_secObj ) != 0 ) || ( SSecpElemento ( p_secObj, 0 ) != p_d1 ) )
		{
			printf( "Error caso 3: la secuencia no deberia estar vacia y el elemento 0 ser p_d1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Eliminar el primero ( sin liberar, la liberacion esta desactivada ). */
		if ( ( SSecpEliminar ( p_secObj, 0 ) != 1 ) ||
			 ( SSecpNumElementos ( p_secObj ) != 2 ) || ( ValorElem ( p_secObj, 0 ) != 20 ) )
		{
			printf( "Error caso 4: tras eliminar el primero deberian quedar 20 y 30\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SSecpVaciar ( p_secObj );
		if ( SSecpNumElementos ( p_secObj ) != 0 )
		{
			printf( "Error caso 5: tras vaciar no deberia quedar ningun elemento\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear la secuencia o los datos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SSecpDestruir ( &p_secObj );
	/* El test libera sus propios datos. */
	MemLiberar ( (void **) &p_d1 );
	MemLiberar ( (void **) &p_d2 );
	MemLiberar ( (void **) &p_d3 );
	return ( iRes );
}

/* CrearDesdeLista y Duplicar copian, con iNumBytes o con fDuplicar;
   EncapsularLista se queda con la lista. */
static int TestSSecpCrearDesdeLista01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SSecpCrearDesdeLista 01:\n" );

	int iVal [ 3 ] = { 10, 20, 30 };
	int iMas100 [ 3 ] = { 110, 120, 130 };
	SListaPtr * p_lisObj = CrearListaEnteros ( iVal, 3 );
	SListaPtr * p_lisEnc = CrearListaEnteros ( iVal, 3 );
	SSecuenciaPtr * p_secObj = NULL;
	SSecuenciaPtr * p_secRes = NULL;
	SSecuenciaPtr * p_secEnc = NULL;
	if ( ES_VALIDO ( p_lisObj ) && ES_VALIDO ( p_lisEnc ) )
	{
		p_secObj = SSecpCrearDesdeLista ( p_lisObj, sizeof ( int ) );
		if ( ( VerificarSec ( p_secObj, iVal, 3 ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarLista ( p_lisObj, iVal, 3 ) != BOOL_VAL_CIERTO ) ||
			 ( SSecpElemento ( p_secObj, 0 ) == SLispElemento ( p_lisObj, 0 ) ) ||
			 ( SSecpLiberacionMemoriaActivada ( p_secObj ) != 1 ) )
		{
			printf( "Error caso 1: se esperaban copias propias de { 10, 20, 30 } y la lista intacta\n" );
			iRes = BOOL_VAL_FALSO;
		}
		p_secRes = SSecpCrearDesdeListaExt ( p_lisObj, DuplicarEnteroMas100 );
		if ( VerificarYDestruir ( &p_secRes, iMas100, 3 ) != BOOL_VAL_CIERTO )
		{
			printf( "Error caso 2: con fDuplicar se esperaba { 110, 120, 130 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		p_secRes = SSecpDuplicar ( p_secObj, sizeof ( int ) );
		if ( ES_NULO ( p_secRes ) || ( SSecpElemento ( p_secRes, 0 ) == SSecpElemento ( p_secObj, 0 ) ) ||
			 ( VerificarYDestruir ( &p_secRes, iVal, 3 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 3: el duplicado deberia tener copias de { 10, 20, 30 }\n" );
			iRes = BOOL_VAL_FALSO;
			SSecpDestruir ( &p_secRes );
		}
		p_secRes = SSecpDuplicarExt ( p_secObj, DuplicarEnteroMas100 );
		if ( VerificarYDestruir ( &p_secRes, iMas100, 3 ) != BOOL_VAL_CIERTO )
		{
			printf( "Error caso 4: el duplicado con fDuplicar deberia ser { 110, 120, 130 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Encapsulada, la lista es de la secuencia: se destruye con ella. */
		p_secEnc = SSecpEncapsularLista ( p_lisEnc );
		if ( ES_NULO ( p_secEnc ) || ( SSecpLista ( p_secEnc ) != p_lisEnc ) )
		{
			printf( "Error caso 5: la secuencia deberia envolver la misma lista\n" );
			iRes = BOOL_VAL_FALSO;
			SLispDestruir ( &p_lisEnc );
		}
		if ( ES_VALIDO ( SSecpCrearDesdeLista ( NULL, sizeof ( int ) ) ) ||
			 ES_VALIDO ( SSecpCrearDesdeListaExt ( p_lisObj, NULL ) ) ||
			 ES_VALIDO ( SSecpEncapsularLista ( NULL ) ) ||
			 ES_VALIDO ( SSecpDuplicar ( NULL, sizeof ( int ) ) ) ||
			 ES_VALIDO ( SSecpDuplicarExt ( p_secObj, NULL ) ) )
		{
			printf( "Error caso 6: con un nulo se esperaba nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear las listas\n" );
		iRes = BOOL_VAL_FALSO;
		SLispDestruir ( &p_lisEnc );
	}
	SLispDestruir ( &p_lisObj );
	SSecpDestruir ( &p_secObj );
	SSecpDestruir ( &p_secEnc );
	return ( iRes );
}

/* Existen, Concatenar y Eliminar, con iNumBytes y con las Ext. */
static int TestSSecpOperacionesListas01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SSecpOperacionesListas 01:\n" );

	int iVal [ 4 ] = { 1, 2, 3, 4 };
	int iSec [ 2 ] = { 4, 2 };
	int iLis [ 2 ] = { 2, 5 };
	int iMod [ 2 ] = { 14, 22 };
	int iUno [ 1 ] = { 1 };
	int iDos [ 1 ] = { 2 };
	int iTres [ 1 ] = { 3 };
	int iCuatro [ 1 ] = { 4 };
	int iCinco [ 1 ] = { 5 };
	int iSeis [ 1 ] = { 6 };
	int iSiete [ 1 ] = { 7 };
	int iEli [ 3 ] = { 2, 4, 99 };
	int iDiecisiete [ 1 ] = { 17 };
	SSecuenciaPtr * p_secObj = CrearSecEnteros ( iVal, 4 );
	SSecuenciaPtr * p_secVal = CrearSecEnteros ( iSec, 2 );
	SListaPtr * p_lisVal = CrearListaEnteros ( iLis, 2 );
	SSecuenciaPtr * p_secMod = CrearSecEnteros ( iMod, 2 );
	SListaPtr * p_lisMod = CrearListaEnteros ( iMod, 2 );
	SSecuenciaPtr * p_secA = CrearSecEnteros ( iUno, 1 );
	SSecuenciaPtr * p_secMov = CrearSecEnteros ( iDos, 1 );
	SListaPtr * p_lisMov = CrearListaEnteros ( iTres, 1 );
	SSecuenciaPtr * p_secDup = CrearSecEnteros ( iCuatro, 1 );
	SListaPtr * p_lisDup = CrearListaEnteros ( iCinco, 1 );
	SSecuenciaPtr * p_secDupExt = CrearSecEnteros ( iSeis, 1 );
	SListaPtr * p_lisDupExt = CrearListaEnteros ( iSiete, 1 );
	SSecuenciaPtr * p_secEli = CrearSecEnteros ( iEli, 3 );
	SListaPtr * p_lisEli = CrearListaEnteros ( iCinco, 1 );
	SSecuenciaPtr * p_secEliExt = CrearSecEnteros ( iSeis, 1 );
	SListaPtr * p_lisEliExt = CrearListaEnteros ( iDiecisiete, 1 );
	if ( ES_VALIDO ( p_secObj ) && ES_VALIDO ( p_secVal ) && ES_VALIDO ( p_lisVal ) && ES_VALIDO ( p_secMod ) &&
		 ES_VALIDO ( p_lisMod ) && ES_VALIDO ( p_secA ) && ES_VALIDO ( p_secMov ) && ES_VALIDO ( p_lisMov ) &&
		 ES_VALIDO ( p_secDup ) && ES_VALIDO ( p_lisDup ) && ES_VALIDO ( p_secDupExt ) && ES_VALIDO ( p_lisDupExt ) &&
		 ES_VALIDO ( p_secEli ) && ES_VALIDO ( p_lisEli ) && ES_VALIDO ( p_secEliExt ) && ES_VALIDO ( p_lisEliExt ) )
	{
		if ( ( SSecpExistenTodos ( p_secObj, p_secVal, sizeof ( int ) ) != 1 ) ||
			 ( SSecpExisteAlguno ( p_secObj, p_secVal, sizeof ( int ) ) != 1 ) ||
			 ( SSecpExistenTodosLista ( p_secObj, p_lisVal, sizeof ( int ) ) != 0 ) ||
			 ( SSecpExisteAlgunoLista ( p_secObj, p_lisVal, sizeof ( int ) ) != 1 ) )
		{
			printf( "Error caso 1: { 4, 2 } estan todos; de { 2, 5 } solo alguno\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Por bytes el 14 y el 22 no estan; modulo 10 si. */
		if ( ( SSecpExistenTodos ( p_secObj, p_secMod, sizeof ( int ) ) != 0 ) ||
			 ( SSecpExistenTodosExt ( p_secObj, p_secMod, SonIgualesMod10 ) != 1 ) ||
			 ( SSecpExisteAlgunoExt ( p_secObj, p_secMod, SonIgualesMod10 ) != 1 ) ||
			 ( SSecpExistenTodosListaExt ( p_secObj, p_lisMod, SonIgualesMod10 ) != 1 ) ||
			 ( SSecpExisteAlgunoListaExt ( p_secObj, p_lisMod, SonIgualesMod10 ) != 1 ) )
		{
			printf( "Error caso 2: modulo 10 { 14, 22 } deberian estar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SSecpExistenTodos ( p_secObj, NULL, sizeof ( int ) ) != 0 ) ||
			 ( SSecpExisteAlgunoLista ( NULL, p_lisVal, sizeof ( int ) ) != 0 ) ||
			 ( SSecpExistenTodosExt ( p_secObj, p_secMod, NULL ) != 0 ) )
		{
			printf( "Error caso 3: con un nulo se esperaba 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Sin Dup se mueven; con Dup se copian, de iNumBytes o con fDuplicar. */
		int iEsp [ 7 ] = { 1, 2, 3, 4, 5, 106, 107 };
		if ( ( SSecpConcatenar ( p_secA, p_secMov ) != 1 ) ||
			 ( SSecpConcatenarLista ( p_secA, p_lisMov ) != 1 ) ||
			 ( SSecpConcatenarDup ( p_secA, p_secDup, sizeof ( int ) ) != 1 ) ||
			 ( SSecpConcatenarListaDup ( p_secA, p_lisDup, sizeof ( int ) ) != 1 ) ||
			 ( SSecpConcatenarDupExt ( p_secA, p_secDupExt, DuplicarEnteroMas100 ) != 1 ) ||
			 ( SSecpConcatenarListaDupExt ( p_secA, p_lisDupExt, DuplicarEnteroMas100 ) != 1 ) ||
			 ( VerificarSec ( p_secA, iEsp, 7 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 4: tras concatenar deberia quedar { 1, 2, 3, 4, 5, 106, 107 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SSecpEstaVacia ( p_secMov ) != 1 ) || ( SLispEstaVacia ( p_lisMov ) != 1 ) ||
			 ( VerificarSec ( p_secDup, iCuatro, 1 ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarLista ( p_lisDup, iCinco, 1 ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarSec ( p_secDupExt, iSeis, 1 ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarLista ( p_lisDupExt, iSiete, 1 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 5: las movidas deberian quedar vacias y las copiadas intactas\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SSecpConcatenar ( p_secA, p_secA ) != 0 ) ||
			 ( SSecpConcatenarListaDup ( p_secA, NULL, sizeof ( int ) ) != 0 ) ||
			 ( SSecpConcatenarDupExt ( NULL, p_secDup, DuplicarEnteroMas100 ) != 0 ) ||
			 ( VerificarSec ( p_secA, iEsp, 7 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 6: con la misma secuencia o una nula se esperaba 0 sin cambios\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Por bytes: el 99 no esta. Modulo 10: el 6 elimina el 106 y el 17 el 107. */
		int iQueda [ 4 ] = { 1, 3, 106, 107 };
		int iQuedaExt [ 2 ] = { 1, 3 };
		if ( ( SSecpEliminarSecuencia ( p_secA, p_secEli, sizeof ( int ) ) != 1 ) ||
			 ( SSecpEliminarLista ( p_secA, p_lisEli, sizeof ( int ) ) != 1 ) ||
			 ( VerificarSec ( p_secA, iQueda, 4 ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarSec ( p_secEli, iEli, 3 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 7: tras eliminar deberia quedar { 1, 3, 106, 107 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SSecpEliminarSecuenciaExt ( p_secA, p_secEliExt, SonIgualesMod10 ) != 1 ) ||
			 ( SSecpEliminarListaExt ( p_secA, p_lisEliExt, SonIgualesMod10 ) != 1 ) ||
			 ( VerificarSec ( p_secA, iQuedaExt, 2 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 8: modulo 10 deberia quedar { 1, 3 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SSecpEliminarSecuencia ( p_secA, p_secA, sizeof ( int ) ) != 0 ) ||
			 ( SSecpEliminarListaExt ( p_secA, p_lisEliExt, NULL ) != 0 ) ||
			 ( SSecpEliminarLista ( NULL, p_lisEli, sizeof ( int ) ) != 0 ) ||
			 ( VerificarSec ( p_secA, iQuedaExt, 2 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 9: con la misma secuencia o un nulo se esperaba 0 sin cambios\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear las secuencias\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SSecpDestruir ( &p_secObj );
	SSecpDestruir ( &p_secVal );
	SLispDestruir ( &p_lisVal );
	SSecpDestruir ( &p_secMod );
	SLispDestruir ( &p_lisMod );
	SSecpDestruir ( &p_secA );
	SSecpDestruir ( &p_secMov );
	SLispDestruir ( &p_lisMov );
	SSecpDestruir ( &p_secDup );
	SLispDestruir ( &p_lisDup );
	SSecpDestruir ( &p_secDupExt );
	SLispDestruir ( &p_lisDupExt );
	SSecpDestruir ( &p_secEli );
	SLispDestruir ( &p_lisEli );
	SSecpDestruir ( &p_secEliExt );
	SLispDestruir ( &p_lisEliExt );
	return ( iRes );
}

/* Saca todas las apariciones de cada valor, por bytes o con fSonIguales; si la de
   SListaPtr falla, nulo y no una secuencia sin lista. */
static int TestSSecpExtraerSecuencia01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SSecpExtraerSecuencia 01:\n" );

	int iVal [ 6 ] = { 20, 10, 20, 30, 40, 20 };
	int iBus [ 4 ] = { 20, 40, 99, 20 };
	int iTreinta [ 1 ] = { 30 };
	int iValExt [ 5 ] = { 12, 25, 33, 42, 13 };
	int iBusExt [ 2 ] = { 3, 2 };
	int iCinco [ 1 ] = { 5 };
	SSecuenciaPtr * p_secObj = CrearSecEnteros ( iVal, 6 );
	SSecuenciaPtr * p_secBus = CrearSecEnteros ( iBus, 4 );
	SListaPtr * p_lisBus = CrearListaEnteros ( iTreinta, 1 );
	SSecuenciaPtr * p_secObjExt = CrearSecEnteros ( iValExt, 5 );
	SSecuenciaPtr * p_secBusExt = CrearSecEnteros ( iBusExt, 2 );
	SListaPtr * p_lisBusExt = CrearListaEnteros ( iCinco, 1 );
	if ( ES_VALIDO ( p_secObj ) && ES_VALIDO ( p_secBus ) && ES_VALIDO ( p_lisBus ) &&
		 ES_VALIDO ( p_secObjExt ) && ES_VALIDO ( p_secBusExt ) && ES_VALIDO ( p_lisBusExt ) )
	{
		/* Todas las apariciones de cada valor buscado, en el orden de los buscados. */
		SSecuenciaPtr * p_secRes = SSecpExtraerSecuencia ( p_secObj, p_secBus, sizeof ( int ) );
		int iEspRes [ 4 ] = { 20, 20, 20, 40 };
		int iEspObj [ 2 ] = { 10, 30 };
		if ( ( VerificarYDestruir ( &p_secRes, iEspRes, 4 ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarSec ( p_secObj, iEspObj, 2 ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarSec ( p_secBus, iBus, 4 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 1: se esperaba extraer { 20, 20, 20, 40 } y dejar { 10, 30 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		p_secRes = SSecpExtraerLista ( p_secObj, p_lisBus, sizeof ( int ) );
		int iEspObj2 [ 1 ] = { 10 };
		if ( ( VerificarYDestruir ( &p_secRes, iTreinta, 1 ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarSec ( p_secObj, iEspObj2, 1 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 2: se esperaba extraer { 30 } y dejar { 10 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Modulo 10, en el orden de los buscados. */
		p_secRes = SSecpExtraerSecuenciaExt ( p_secObjExt, p_secBusExt, SonIgualesMod10 );
		int iEspResExt [ 4 ] = { 33, 13, 12, 42 };
		int iEspObjExt [ 1 ] = { 25 };
		if ( ( VerificarYDestruir ( &p_secRes, iEspResExt, 4 ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarSec ( p_secObjExt, iEspObjExt, 1 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 3: modulo 10 se esperaba extraer { 33, 13, 12, 42 } y dejar { 25 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		p_secRes = SSecpExtraerListaExt ( p_secObjExt, p_lisBusExt, SonIgualesMod10 );
		if ( ( VerificarYDestruir ( &p_secRes, iEspObjExt, 1 ) != BOOL_VAL_CIERTO ) ||
			 ( SSecpEstaVacia ( p_secObjExt ) != 1 ) )
		{
			printf( "Error caso 4: modulo 10 se esperaba extraer { 25 } y dejarla vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( SSecpExtraerSecuencia ( p_secObj, p_secObj, sizeof ( int ) ) ) ||
			 ES_VALIDO ( SSecpExtraerLista ( p_secObj, SSecpLista ( p_secObj ), sizeof ( int ) ) ) ||
			 ES_VALIDO ( SSecpExtraerLista ( p_secObj, NULL, sizeof ( int ) ) ) ||
			 ES_VALIDO ( SSecpExtraerSecuenciaExt ( p_secObj, p_secBus, NULL ) ) ||
			 ES_VALIDO ( SSecpExtraerListaExt ( NULL, p_lisBus, SonIgualesMod10 ) ) ||
			 ( VerificarSec ( p_secObj, iEspObj2, 1 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 5: con la misma secuencia o un nulo se esperaba nulo sin cambios\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear las secuencias\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SSecpDestruir ( &p_secObj );
	SSecpDestruir ( &p_secBus );
	SLispDestruir ( &p_lisBus );
	SSecpDestruir ( &p_secObjExt );
	SSecpDestruir ( &p_secBusExt );
	SLispDestruir ( &p_lisBusExt );
	return ( iRes );
}

/* Union, interseccion y diferencia, con secuencias y con listas, por bytes y
   con las Ext. */
static int TestSSecpConjuntos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SSecpConjuntos 01:\n" );

	int iV1 [ 4 ] = { 1, 2, 3, 4 };
	int iV2 [ 3 ] = { 4, 2, 5 };
	int iV3 [ 2 ] = { 14, 22 };
	SSecuenciaPtr * p_sec1 = CrearSecEnteros ( iV1, 4 );
	SSecuenciaPtr * p_sec2 = CrearSecEnteros ( iV2, 3 );
	SSecuenciaPtr * p_sec3 = CrearSecEnteros ( iV3, 2 );
	SListaPtr * p_lis2 = CrearListaEnteros ( iV2, 3 );
	SListaPtr * p_lis3 = CrearListaEnteros ( iV3, 2 );
	if ( ES_VALIDO ( p_sec1 ) && ES_VALIDO ( p_sec2 ) && ES_VALIDO ( p_sec3 ) &&
		 ES_VALIDO ( p_lis2 ) && ES_VALIDO ( p_lis3 ) )
	{
		int iUnion [ 7 ] = { 1, 2, 3, 4, 4, 2, 5 };
		int iInter [ 2 ] = { 2, 4 };
		int iDif [ 2 ] = { 1, 3 };
		int iUnionExt [ 6 ] = { 101, 102, 103, 104, 114, 122 };
		int iInterExt [ 2 ] = { 102, 104 };
		int iDifExt [ 2 ] = { 101, 103 };
		SSecuenciaPtr * p_secRes = SSecpUnion ( p_sec1, p_sec2, sizeof ( int ) );
		if ( VerificarYDestruir ( &p_secRes, iUnion, 7 ) != BOOL_VAL_CIERTO )
		{
			printf( "Error caso 1: la union deberia ser { 1, 2, 3, 4, 4, 2, 5 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		p_secRes = SSecpInterseccion ( p_sec1, p_sec2, sizeof ( int ) );
		if ( VerificarYDestruir ( &p_secRes, iInter, 2 ) != BOOL_VAL_CIERTO )
		{
			printf( "Error caso 2: la interseccion deberia ser { 2, 4 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		p_secRes = SSecpDiferencia ( p_sec1, p_sec2, sizeof ( int ) );
		if ( VerificarYDestruir ( &p_secRes, iDif, 2 ) != BOOL_VAL_CIERTO )
		{
			printf( "Error caso 3: la diferencia deberia ser { 1, 3 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		p_secRes = SSecpUnionLista ( p_sec1, p_lis2, sizeof ( int ) );
		if ( VerificarYDestruir ( &p_secRes, iUnion, 7 ) != BOOL_VAL_CIERTO )
		{
			printf( "Error caso 4: la union con la lista deberia ser { 1, 2, 3, 4, 4, 2, 5 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		p_secRes = SSecpInterseccionLista ( p_sec1, p_lis2, sizeof ( int ) );
		if ( VerificarYDestruir ( &p_secRes, iInter, 2 ) != BOOL_VAL_CIERTO )
		{
			printf( "Error caso 5: la interseccion con la lista deberia ser { 2, 4 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		p_secRes = SSecpDiferenciaLista ( p_sec1, p_lis2, sizeof ( int ) );
		if ( VerificarYDestruir ( &p_secRes, iDif, 2 ) != BOOL_VAL_CIERTO )
		{
			printf( "Error caso 6: la diferencia con la lista deberia ser { 1, 3 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Modulo 10 el 14 es el 4 y el 22 el 2; las copias suman 100. */
		p_secRes = SSecpUnionExt ( p_sec1, p_sec3, DuplicarEnteroMas100 );
		if ( VerificarYDestruir ( &p_secRes, iUnionExt, 6 ) != BOOL_VAL_CIERTO )
		{
			printf( "Error caso 7: la union Ext deberia ser { 101, 102, 103, 104, 114, 122 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		p_secRes = SSecpInterseccionExt ( p_sec1, p_sec3, SonIgualesMod10, DuplicarEnteroMas100 );
		if ( VerificarYDestruir ( &p_secRes, iInterExt, 2 ) != BOOL_VAL_CIERTO )
		{
			printf( "Error caso 8: la interseccion Ext deberia ser { 102, 104 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		p_secRes = SSecpDiferenciaExt ( p_sec1, p_sec3, SonIgualesMod10, DuplicarEnteroMas100 );
		if ( VerificarYDestruir ( &p_secRes, iDifExt, 2 ) != BOOL_VAL_CIERTO )
		{
			printf( "Error caso 9: la diferencia Ext deberia ser { 101, 103 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		p_secRes = SSecpUnionListaExt ( p_sec1, p_lis3, DuplicarEnteroMas100 );
		if ( VerificarYDestruir ( &p_secRes, iUnionExt, 6 ) != BOOL_VAL_CIERTO )
		{
			printf( "Error caso 10: la union Ext con la lista deberia ser { 101, 102, 103, 104, 114, 122 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		p_secRes = SSecpInterseccionListaExt ( p_sec1, p_lis3, SonIgualesMod10, DuplicarEnteroMas100 );
		if ( VerificarYDestruir ( &p_secRes, iInterExt, 2 ) != BOOL_VAL_CIERTO )
		{
			printf( "Error caso 11: la interseccion Ext con la lista deberia ser { 102, 104 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		p_secRes = SSecpDiferenciaListaExt ( p_sec1, p_lis3, SonIgualesMod10, DuplicarEnteroMas100 );
		if ( VerificarYDestruir ( &p_secRes, iDifExt, 2 ) != BOOL_VAL_CIERTO )
		{
			printf( "Error caso 12: la diferencia Ext con la lista deberia ser { 101, 103 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( VerificarSec ( p_sec1, iV1, 4 ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarSec ( p_sec3, iV3, 2 ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarLista ( p_lis3, iV3, 2 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 13: los operandos no deberian cambiar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( SSecpUnion ( p_sec1, NULL, sizeof ( int ) ) ) ||
			 ES_VALIDO ( SSecpUnion ( NULL, p_sec2, sizeof ( int ) ) ) ||
			 ES_VALIDO ( SSecpInterseccionLista ( p_sec1, NULL, sizeof ( int ) ) ) ||
			 ES_VALIDO ( SSecpDiferenciaListaExt ( NULL, p_lis3, SonIgualesMod10, DuplicarEnteroMas100 ) ) ||
			 ES_VALIDO ( SSecpUnionExt ( p_sec1, p_sec3, NULL ) ) ||
			 ES_VALIDO ( SSecpInterseccionExt ( p_sec1, p_sec3, NULL, DuplicarEnteroMas100 ) ) )
		{
			printf( "Error caso 14: con un nulo se esperaba nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear las secuencias\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SSecpDestruir ( &p_sec1 );
	SSecpDestruir ( &p_sec2 );
	SSecpDestruir ( &p_sec3 );
	SLispDestruir ( &p_lis2 );
	SLispDestruir ( &p_lis3 );
	return ( iRes );
}

/* Busca por bytes o con fSonIguales, con un dato o con un elemento. */
static int TestSSecpBuscar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SSecpBuscar 01:\n" );

	int iVal [ 4 ] = { 10, 25, 33, 25 };
	int iBuscar;
	SSecuenciaPtr * p_secObj = CrearSecEnteros ( iVal, 4 );
	SElementoPtr * p_elp33 = SElpCrear ( CrearDatoEntero ( 33 ), 1 );
	SElementoPtr * p_elp3 = SElpCrear ( CrearDatoEntero ( 3 ), 1 );
	if ( ES_VALIDO ( p_secObj ) && ES_VALIDO ( p_elp33 ) && ES_VALIDO ( p_elp3 ) )
	{
		/* El primero igual, aunque el 25 este dos veces. */
		iBuscar = 25;
		if ( SSecpBuscar ( p_secObj, (byte *) &iBuscar, sizeof ( int ) ) != 1 )
		{
			printf( "Error caso 1: el 25 deberia estar en la posicion 1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Por bytes el 5 no esta; modulo 10 casa con el 25. */
		iBuscar = 5;
		if ( ( SSecpBuscar ( p_secObj, (byte *) &iBuscar, sizeof ( int ) ) != -1 ) ||
			 ( SSecpBuscarExt ( p_secObj, (byte *) &iBuscar, SonIgualesMod10 ) != 1 ) )
		{
			printf( "Error caso 2: el 5 solo deberia encontrarse modulo 10, en la posicion 1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		iBuscar = 9;
		if ( SSecpBuscarExt ( p_secObj, (byte *) &iBuscar, SonIgualesMod10 ) != -1 )
		{
			printf( "Error caso 3: el 9 no deberia encontrarse\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SSecpBuscarPtr ( p_secObj, p_elp33, sizeof ( int ) ) != 2 ) ||
			 ( SSecpBuscarPtr ( p_secObj, p_elp3, sizeof ( int ) ) != -1 ) )
		{
			printf( "Error caso 4: por bytes el elemento 33 deberia estar en la 2 y el 3 no estar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SSecpBuscarExtPtr ( p_secObj, p_elp3, SonIgualesMod10 ) != 2 )
		{
			printf( "Error caso 5: modulo 10 el elemento 3 deberia casar con el 33 de la posicion 2\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SSecpBuscar ( NULL, (byte *) &iBuscar, sizeof ( int ) ) != -1 ) ||
			 ( SSecpBuscar ( p_secObj, NULL, sizeof ( int ) ) != -1 ) ||
			 ( SSecpBuscarExt ( p_secObj, (byte *) &iBuscar, NULL ) != -1 ) ||
			 ( SSecpBuscarPtr ( p_secObj, NULL, sizeof ( int ) ) != -1 ) ||
			 ( SSecpBuscarExtPtr ( NULL, p_elp3, SonIgualesMod10 ) != -1 ) ||
			 ( SSecpBuscarExtPtr ( p_secObj, p_elp3, NULL ) != -1 ) )
		{
			printf( "Error caso 6: con un nulo se esperaba -1\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear la secuencia o los elementos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SElpDestruir ( &p_elp33 );
	SElpDestruir ( &p_elp3 );
	SSecpDestruir ( &p_secObj );
	return ( iRes );
}

/* Recorre los repetidos con BuscarPrimero / BuscarSiguiente; Existe y
   Repeticiones. Por bytes y con fSonIguales, con un dato y con un elemento. */
static int TestSSecpBuscarSiguiente01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SSecpBuscarSiguiente 01:\n" );

	int iVal [ 6 ] = { 20, 11, 20, 30, 20, 41 };
	int iVeinte = 20;
	int iUno = 1;
	int iCero = 0;
	SSecuenciaPtr * p_secObj = CrearSecEnteros ( iVal, 6 );
	SElementoPtr * p_elp20 = SElpCrear ( CrearDatoEntero ( 20 ), 1 );
	SElementoPtr * p_elp1 = SElpCrear ( CrearDatoEntero ( 1 ), 1 );
	if ( ES_VALIDO ( p_secObj ) && ES_VALIDO ( p_elp20 ) && ES_VALIDO ( p_elp1 ) )
	{
		if ( ( SSecpBuscarPrimero ( p_secObj, (byte *) &iVeinte, sizeof ( int ) ) != 0 ) ||
			 ( SSecpBuscarSiguiente ( p_secObj, (byte *) &iVeinte, 0, sizeof ( int ) ) != 2 ) ||
			 ( SSecpBuscarSiguiente ( p_secObj, (byte *) &iVeinte, 2, sizeof ( int ) ) != 4 ) ||
			 ( SSecpBuscarSiguiente ( p_secObj, (byte *) &iVeinte, 4, sizeof ( int ) ) != -1 ) )
		{
			printf( "Error caso 1: por bytes el 20 deberia estar en 0, 2 y 4\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SSecpBuscarPrimeroPtr ( p_secObj, p_elp20, sizeof ( int ) ) != 0 ) ||
			 ( SSecpBuscarSiguientePtr ( p_secObj, p_elp20, 0, sizeof ( int ) ) != 2 ) ||
			 ( SSecpBuscarSiguientePtr ( p_secObj, p_elp20, 2, sizeof ( int ) ) != 4 ) ||
			 ( SSecpBuscarSiguientePtr ( p_secObj, p_elp20, 4, sizeof ( int ) ) != -1 ) )
		{
			printf( "Error caso 2: por elemento el 20 deberia estar en 0, 2 y 4\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Modulo 10 el 1 casa con el 11 y con el 41. */
		if ( ( SSecpBuscarPrimeroExt ( p_secObj, (byte *) &iUno, SonIgualesMod10 ) != 1 ) ||
			 ( SSecpBuscarSiguienteExt ( p_secObj, (byte *) &iUno, 1, SonIgualesMod10 ) != 5 ) ||
			 ( SSecpBuscarSiguienteExt ( p_secObj, (byte *) &iUno, 5, SonIgualesMod10 ) != -1 ) ||
			 ( SSecpBuscarPrimeroExtPtr ( p_secObj, p_elp1, SonIgualesMod10 ) != 1 ) ||
			 ( SSecpBuscarSiguienteExtPtr ( p_secObj, p_elp1, 1, SonIgualesMod10 ) != 5 ) ||
			 ( SSecpBuscarSiguienteExtPtr ( p_secObj, p_elp1, 5, SonIgualesMod10 ) != -1 ) )
		{
			printf( "Error caso 3: modulo 10 el 1 deberia estar en 1 y 5\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SSecpRepeticiones ( p_secObj, (byte *) &iVeinte, sizeof ( int ) ) != 3 ) ||
			 ( SSecpRepeticionesPtr ( p_secObj, p_elp20, sizeof ( int ) ) != 3 ) ||
			 ( SSecpRepeticionesExt ( p_secObj, (byte *) &iCero, SonIgualesMod10 ) != 4 ) ||
			 ( SSecpRepeticionesExtPtr ( p_secObj, p_elp1, SonIgualesMod10 ) != 2 ) ||
			 ( SSecpRepeticiones ( p_secObj, (byte *) &iUno, sizeof ( int ) ) != 0 ) )
		{
			printf( "Error caso 4: el 20 deberia estar 3 veces, y modulo 10 el 0 cuatro y el 1 dos\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SSecpExiste ( p_secObj, (byte *) &iVeinte, sizeof ( int ) ) != 1 ) ||
			 ( SSecpExistePtr ( p_secObj, p_elp20, sizeof ( int ) ) != 1 ) ||
			 ( SSecpExisteExt ( p_secObj, (byte *) &iUno, SonIgualesMod10 ) != 1 ) ||
			 ( SSecpExisteExtPtr ( p_secObj, p_elp1, SonIgualesMod10 ) != 1 ) ||
			 ( SSecpExiste ( p_secObj, (byte *) &iUno, sizeof ( int ) ) != 0 ) ||
			 ( SSecpExistePtr ( p_secObj, p_elp1, sizeof ( int ) ) != 0 ) )
		{
			printf( "Error caso 5: deberian existir el 20 y, modulo 10, el 1; por bytes el 1 no\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SSecpBuscar ( p_secObj, (byte *) &iVeinte, sizeof ( int ) ) != 0 ) ||
			 ( SSecpBuscarExtPtr ( p_secObj, p_elp1, SonIgualesMod10 ) != 1 ) ||
			 ( SSecpBuscarSiguiente ( p_secObj, (byte *) &iVeinte, 1, sizeof ( int ) ) != 2 ) ||
			 ( SSecpBuscarSiguiente ( p_secObj, (byte *) &iVeinte, -2, sizeof ( int ) ) != -1 ) )
		{
			printf( "Error caso 6: Buscar es BuscarPrimero, y se busca detras de iPos\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SSecpBuscarSiguiente ( NULL, (byte *) &iVeinte, -1, sizeof ( int ) ) != -1 ) ||
			 ( SSecpBuscarSiguientePtr ( p_secObj, NULL, -1, sizeof ( int ) ) != -1 ) ||
			 ( SSecpBuscarPrimeroExt ( p_secObj, (byte *) &iUno, NULL ) != -1 ) ||
			 ( SSecpRepeticiones ( NULL, (byte *) &iVeinte, sizeof ( int ) ) != 0 ) ||
			 ( SSecpRepeticionesExtPtr ( p_secObj, NULL, SonIgualesMod10 ) != 0 ) ||
			 ( SSecpExiste ( NULL, (byte *) &iVeinte, sizeof ( int ) ) != 0 ) ||
			 ( SSecpExisteExt ( p_secObj, (byte *) &iUno, NULL ) != 0 ) )
		{
			printf( "Error caso 7: con un nulo se esperaba -1 al buscar y 0 al contar\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear la secuencia o los elementos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SElpDestruir ( &p_elp20 );
	SElpDestruir ( &p_elp1 );
	SSecpDestruir ( &p_secObj );
	return ( iRes );
}

static int TestSSecpInvalidos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SSecpInvalidos 01:\n" );

	if ( SSecpEsValida ( NULL ) != 0 )
	{
		printf( "Error caso 1: una secuencia nula no deberia ser valida\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SSecpNumElementos ( NULL ) != 0 )
	{
		printf( "Error caso 2: una secuencia nula deberia tener 0 elementos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( SSecpElemento ( NULL, 0 ) ) )
	{
		printf( "Error caso 3: el elemento de una secuencia nula deberia ser nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SSecuenciaPtr * p_secNula = NULL;
	SSecpDestruir ( &p_secNula );
	return ( iRes );
}



/* InsertarPtr engancha un nodo al final; Extraer y ExtraerPtr sacan el de la
   posicion sin destruirlo: el dato, o el nodo suelto. */
static int TestSSecpExtraer01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SSecpExtraer 01:\n" );

	int iVal [ 4 ] = { 10, 20, 30, 40 };
	SSecuenciaPtr * p_secObj = CrearSecEnteros ( iVal, 4 );
	SElementoPtr * p_elpObj = NULL;
	byte * p_byDato = NULL;
	if ( ES_VALIDO ( p_secObj ) )
	{
		p_byDato = SSecpExtraer ( p_secObj, 1 );
		int iEsp1 [ 3 ] = { 10, 30, 40 };
		if ( ES_NULO ( p_byDato ) || ( *( (int *) p_byDato ) != 20 ) ||
			 ( VerificarSec ( p_secObj, iEsp1, 3 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 1: se esperaba extraer el 20 y dejar { 10, 30, 40 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* El dato es ahora del que llama. */
		MemLiberar ( (void **) &p_byDato );
		p_elpObj = SSecpExtraerPtr ( p_secObj, 0 );
		int iEsp2 [ 2 ] = { 30, 40 };
		if ( ES_NULO ( p_elpObj ) || ( *( (int *) SElpDatos ( p_elpObj ) ) != 10 ) ||
			 ( SElpTieneAntecesor ( p_elpObj ) != 0 ) || ( SElpTieneSucesor ( p_elpObj ) != 0 ) ||
			 ( VerificarSec ( p_secObj, iEsp2, 2 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 2: se esperaba extraer suelto el 10 y dejar { 30, 40 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		int iEsp3 [ 3 ] = { 30, 40, 10 };
		if ( ( SSecpInsertarPtr ( p_secObj, p_elpObj ) != 1 ) ||
			 ( VerificarSec ( p_secObj, iEsp3, 3 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 3: el nodo deberia volver al final: { 30, 40, 10 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		p_elpObj = NULL;
		/* Nulos y fuera de rango: nada cambia. */
		SElementoPtr * p_elpSuelto = SElpCrear ( CrearDatoEntero ( 50 ), 1 );
		if ( ES_VALIDO ( SSecpExtraer ( p_secObj, 3 ) ) ||
			 ES_VALIDO ( SSecpExtraer ( NULL, 0 ) ) ||
			 ES_VALIDO ( SSecpExtraerPtr ( p_secObj, -1 ) ) ||
			 ES_VALIDO ( SSecpExtraerPtr ( NULL, 0 ) ) ||
			 ( SSecpInsertarPtr ( p_secObj, NULL ) != 0 ) ||
			 ( SSecpInsertarPtr ( NULL, p_elpSuelto ) != 0 ) ||
			 ( VerificarSec ( p_secObj, iEsp3, 3 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 4: con nulos o fuera de rango se esperaba nulo o 0 sin cambios\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SElpDestruir ( &p_elpSuelto );
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la secuencia\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SElpDestruir ( &p_elpObj );
	SSecpDestruir ( &p_secObj );
	return ( iRes );
}

int TestSSecuenciaPtr ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SSecuenciaPtr]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSSecpOperaciones01 () == BOOL_VAL_CIERTO ) &&
			( TestSSecpCrearDesdeLista01 () == BOOL_VAL_CIERTO ) &&
			( TestSSecpBuscar01 () == BOOL_VAL_CIERTO ) &&
			( TestSSecpBuscarSiguiente01 () == BOOL_VAL_CIERTO ) &&
			( TestSSecpOperacionesListas01 () == BOOL_VAL_CIERTO ) &&
			( TestSSecpExtraerSecuencia01 () == BOOL_VAL_CIERTO ) &&
			( TestSSecpConjuntos01 () == BOOL_VAL_CIERTO ) &&
			( TestSSecpInvalidos01 () == BOOL_VAL_CIERTO ) &&
			( TestSSecpExtraer01 () == BOOL_VAL_CIERTO ) )
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
