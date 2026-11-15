#include "Base.h"

#include "SSecuenciaUnica.h"



static SElemento * CrearEntero ( int iDato )
{
	SElemento * p_elmObj = SElmCrearEntero ();
	if ( ES_VALIDO ( p_elmObj ) )
	{
		SElmEscribirEntero ( p_elmObj, iDato );
	}
	return ( p_elmObj );
}

static SLista * CrearLista ( int * p_iValores, int iNum )
{
	SLista * p_lisObj = SLisCrear ();
	int iPos = 0;
	while ( ES_VALIDO ( p_lisObj ) && ( iPos < iNum ) )
	{
		SLisInsertarAlFinal ( p_lisObj, CrearEntero ( p_iValores [ iPos ] ) );
		iPos = iPos + 1;
	}
	return ( p_lisObj );
}

static SSecuenciaUnica * CrearSec ( int * p_iValores, int iNum )
{
	SSecuenciaUnica * p_secObj = SSecUnCrear ();
	int iPos = 0;
	while ( ES_VALIDO ( p_secObj ) && ( iPos < iNum ) )
	{
		SSecUnInsertar ( p_secObj, CrearEntero ( p_iValores [ iPos ] ) );
		iPos = iPos + 1;
	}
	return ( p_secObj );
}

/* Comprueba numero y orden de los enteros de una lista. */
static int VerificarLista ( SLista * p_lisObj, int * p_iEsperados, int iNum )
{
	int iRes = BOOL_VAL_CIERTO;

	if ( SLisNumElementos ( p_lisObj ) != iNum )
	{
		printf( "  Verificacion: se esperaban %d elementos: %d\n", iNum, SLisNumElementos ( p_lisObj ) );
		iRes = BOOL_VAL_FALSO;
	}
	int iPos = 0;
	SElemento * p_elmObj = SLisElemento ( p_lisObj, 0 );
	while ( ( iPos < iNum ) && ( iRes == BOOL_VAL_CIERTO ) )
	{
		if ( ES_NULO ( p_elmObj ) || ( SElmEntero ( p_elmObj ) != p_iEsperados [ iPos ] ) )
		{
			printf( "  Verificacion: en pos %d se esperaba %d\n", iPos, p_iEsperados [ iPos ] );
			iRes = BOOL_VAL_FALSO;
		}
		else
		{
			p_elmObj = SElmSucesor ( p_elmObj );
		}
		iPos = iPos + 1;
	}
	return ( iRes );
}

static int VerificarSec ( SSecuenciaUnica * p_secObj, int * p_iEsperados, int iNum )
{
	int iRes = BOOL_VAL_CIERTO;

	if ( SSecUnEsValida ( p_secObj ) != 1 )
	{
		printf( "  Verificacion: la secuencia no es valida o tiene repetidos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		iRes = VerificarLista ( SSecUnLista ( p_secObj ), p_iEsperados, iNum );
	}
	return ( iRes );
}



/* Insertar no admite un valor que ya este: devuelve 0 y el elemento sigue
   siendo del llamante. */
static int TestSSecUnInsertar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SSecUnInsertar 01:\n" );

	SSecuenciaUnica * p_secObj = SSecUnCrear ();
	SElemento * p_elmRepetido = CrearEntero ( 3 );
	SElemento * p_elmSonda = CrearEntero ( 1 );
	if ( ES_VALIDO ( p_secObj ) && ES_VALIDO ( p_elmRepetido ) && ES_VALIDO ( p_elmSonda ) )
	{
		if ( ( SSecUnEsValida ( p_secObj ) != 1 ) || ( SSecUnEstaVacia ( p_secObj ) != 1 ) )
		{
			printf( "Error caso 1: la secuencia recien creada deberia ser valida y estar vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SSecUnInsertar ( p_secObj, CrearEntero ( 3 ) ) != 1 ) ||
			 ( SSecUnInsertar ( p_secObj, CrearEntero ( 1 ) ) != 1 ) ||
			 ( SSecUnInsertar ( p_secObj, p_elmRepetido ) != 0 ) )
		{
			printf( "Error caso 2: se esperaba 1, 1 y 0 para el 3 repetido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		int iEsp [ 2 ] = { 3, 1 };
		if ( VerificarSec ( p_secObj, iEsp, 2 ) != BOOL_VAL_CIERTO )
		{
			printf( "Error caso 3: deberia quedar { 3, 1 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SSecUnExiste ( p_secObj, p_elmSonda ) != 1 ) || ( SSecUnBuscar ( p_secObj, p_elmSonda ) != 1 ) ||
			 ( SSecUnBuscar ( p_secObj, p_elmRepetido ) != 0 ) )
		{
			printf( "Error caso 4: el 1 deberia estar en la posicion 1 y el 3 en la 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SElemento * p_elmExt = SSecUnExtraer ( p_secObj, 0 );
		if ( ES_NULO ( p_elmExt ) || ( SElmEntero ( p_elmExt ) != 3 ) || ( SSecUnNumElementos ( p_secObj ) != 1 ) )
		{
			printf( "Error caso 5: extraer la posicion 0 deberia dar el 3\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SElmDestruir ( &p_elmExt );
		/* Ya no esta: ahora si entra, al final. */
		if ( SSecUnInsertar ( p_secObj, p_elmRepetido ) != 1 )
		{
			printf( "Error caso 6: tras extraer el 3 deberia poder volver a entrar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		else
		{
			p_elmRepetido = NULL;
		}
		int iEsp2 [ 2 ] = { 1, 3 };
		if ( ( VerificarSec ( p_secObj, iEsp2, 2 ) != BOOL_VAL_CIERTO ) ||
			 ( SSecUnEliminar ( p_secObj, 0 ) != 1 ) || ( SSecUnExiste ( p_secObj, p_elmSonda ) != 0 ) )
		{
			printf( "Error caso 7: deberia quedar { 1, 3 } y luego eliminarse el 1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SSecUnVaciar ( p_secObj ) != 1 ) || ( SSecUnEstaVacia ( p_secObj ) != 1 ) )
		{
			printf( "Error caso 8: tras vaciar deberia estar vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SSecUnInsertar ( NULL, p_elmSonda ) != 0 ) || ( SSecUnInsertar ( p_secObj, NULL ) != 0 ) ||
			 ( SSecUnExiste ( NULL, p_elmSonda ) != 0 ) || ( SSecUnBuscar ( NULL, p_elmSonda ) != -1 ) ||
			 ( SSecUnEsValida ( NULL ) != 0 ) || ( SSecUnNumElementos ( NULL ) != 0 ) )
		{
			printf( "Error caso 9: con nulos se esperaba 0 o -1\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la secuencia o los elementos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SElmDestruir ( &p_elmRepetido );
	SElmDestruir ( &p_elmSonda );
	SSecUnDestruir ( &p_secObj );
	return ( iRes );
}

/* CrearDesdeLista y CrearDesdeSecuencia copian una vez cada valor, en el orden
   de su primera aparicion; Duplicar copia. EsValida detecta un repetido metido
   por la secuencia interna. */
static int TestSSecUnCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SSecUnCrear 01:\n" );

	int iV [ 5 ] = { 2, 5, 2, 7, 5 };
	int iEsp [ 3 ] = { 2, 5, 7 };
	SLista * p_lisVal = CrearLista ( iV, 5 );
	SSecuencia * p_secVal = SSecCrearDesdeLista ( p_lisVal );
	SSecuenciaUnica * p_secObj = NULL;
	SSecuenciaUnica * p_secSec = NULL;
	SSecuenciaUnica * p_secDup = NULL;
	if ( ES_VALIDO ( p_lisVal ) && ES_VALIDO ( p_secVal ) )
	{
		p_secObj = SSecUnCrearDesdeLista ( p_lisVal );
		p_secSec = SSecUnCrearDesdeSecuencia ( p_secVal );
		if ( ( VerificarSec ( p_secObj, iEsp, 3 ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarSec ( p_secSec, iEsp, 3 ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarLista ( p_lisVal, iV, 5 ) != BOOL_VAL_CIERTO ) ||
			 ( SSecUnElemento ( p_secObj, 0 ) == SLisElemento ( p_lisVal, 0 ) ) )
		{
			printf( "Error caso 1: se esperaban copias de { 2, 5, 7 } y la lista sin tocar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		p_secDup = SSecUnDuplicar ( p_secObj );
		if ( ( VerificarSec ( p_secDup, iEsp, 3 ) != BOOL_VAL_CIERTO ) ||
			 ( SSecUnElemento ( p_secDup, 0 ) == SSecUnElemento ( p_secObj, 0 ) ) )
		{
			printf( "Error caso 2: la copia deberia ser { 2, 5, 7 } con elementos propios\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Un repetido metido por debajo: deja de ser valida. */
		if ( ( SSecInsertar ( SSecUnSecuencia ( p_secDup ), CrearEntero ( 5 ) ) != 1 ) ||
			 ( SSecUnEsValida ( p_secDup ) != 0 ) )
		{
			printf( "Error caso 3: con un 5 repetido no deberia ser valida\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( SSecUnCrearDesdeLista ( NULL ) ) || ES_VALIDO ( SSecUnCrearDesdeSecuencia ( NULL ) ) ||
			 ES_VALIDO ( SSecUnDuplicar ( NULL ) ) )
		{
			printf( "Error caso 4: con nulos se esperaba nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear la lista o la secuencia\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SSecUnDestruir ( &p_secObj );
	SSecUnDestruir ( &p_secSec );
	SSecUnDestruir ( &p_secDup );
	SSecDestruir ( &p_secVal );
	SLisDestruir ( &p_lisVal );
	return ( iRes );
}

/* Concatenar mueve los que faltan y deja los demas en la de entrada; las Dup
   copian los que faltan sin tocarla. */
static int TestSSecUnConcatenar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SSecUnConcatenar 01:\n" );

	int iV12 [ 2 ] = { 1, 2 };
	int iV2334 [ 4 ] = { 2, 3, 3, 4 };
	int iV64 [ 2 ] = { 6, 4 };
	SSecuenciaUnica * p_secObj = CrearSec ( iV12, 2 );
	SSecuenciaUnica * p_secDup = CrearSec ( iV12, 2 );
	SLista * p_lisVal = CrearLista ( iV2334, 4 );
	SLista * p_lisDup = CrearLista ( iV2334, 4 );
	SSecuenciaUnica * p_sec64 = CrearSec ( iV64, 2 );
	if ( ES_VALIDO ( p_secObj ) && ES_VALIDO ( p_secDup ) && ES_VALIDO ( p_lisVal ) && ES_VALIDO ( p_lisDup ) && ES_VALIDO ( p_sec64 ) )
	{
		SElemento * p_elmTres = SLisElemento ( p_lisVal, 1 );
		int iEsp1 [ 4 ] = { 1, 2, 3, 4 };
		int iQuedan [ 2 ] = { 2, 3 };
		if ( ( SSecUnConcatenarLista ( p_secObj, p_lisVal ) != 1 ) ||
			 ( VerificarSec ( p_secObj, iEsp1, 4 ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarLista ( p_lisVal, iQuedan, 2 ) != BOOL_VAL_CIERTO ) ||
			 ( SSecUnElemento ( p_secObj, 2 ) != p_elmTres ) )
		{
			printf( "Error caso 1: se esperaba { 1, 2, 3, 4 }, el mismo 3 y { 2, 3 } en la lista\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Con otra unica: el 4 ya esta, pasa el 6. */
		int iEsp2 [ 5 ] = { 1, 2, 3, 4, 6 };
		int iQueda4 [ 1 ] = { 4 };
		if ( ( SSecUnConcatenar ( p_secObj, p_sec64 ) != 1 ) ||
			 ( VerificarSec ( p_secObj, iEsp2, 5 ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarSec ( p_sec64, iQueda4, 1 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 2: se esperaba { 1, 2, 3, 4, 6 } y { 4 } en la otra\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SSecUnConcatenarListaDup ( p_secDup, p_lisDup ) != 1 ) ||
			 ( VerificarSec ( p_secDup, iEsp1, 4 ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarLista ( p_lisDup, iV2334, 4 ) != BOOL_VAL_CIERTO ) ||
			 ( SSecUnElemento ( p_secDup, 2 ) == SLisElemento ( p_lisDup, 1 ) ) )
		{
			printf( "Error caso 3: Dup deberia dar copias de { 1, 2, 3, 4 } sin tocar la lista\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SSecUnConcatenarDup ( p_secDup, p_secObj ) != 1 ) || ( SSecUnNumElementos ( p_secDup ) != 5 ) ||
			 ( SSecUnNumElementos ( p_secObj ) != 5 ) )
		{
			printf( "Error caso 4: ConcatenarDup deberia anadir solo el 6\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SSecUnConcatenarLista ( p_secObj, SSecUnLista ( p_secObj ) ) != 0 ) ||
			 ( SSecUnConcatenarListaDup ( p_secObj, SSecUnLista ( p_secObj ) ) != 0 ) ||
			 ( SSecUnConcatenar ( NULL, p_sec64 ) != 0 ) || ( SSecUnConcatenarSecuencia ( p_secObj, NULL ) != 0 ) ||
			 ( SSecUnConcatenarSecuenciaDup ( p_secObj, NULL ) != 0 ) || ( VerificarSec ( p_secObj, iEsp2, 5 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 5: con la misma lista o nulos se esperaba 0 sin cambios\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear las secuencias o las listas\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SSecUnDestruir ( &p_secObj );
	SSecUnDestruir ( &p_secDup );
	SSecUnDestruir ( &p_sec64 );
	SLisDestruir ( &p_lisVal );
	SLisDestruir ( &p_lisDup );
	return ( iRes );
}

/* Pertenencia, Eliminar y Extraer, que mueve a una secuencia unica nueva en
   el orden de los valores buscados. */
static int TestSSecUnOperacionesListas01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SSecUnOperacionesListas 01:\n" );

	int iV [ 5 ] = { 1, 2, 3, 4, 5 };
	int iV24 [ 2 ] = { 2, 4 };
	int iV9 [ 1 ] = { 9 };
	int iV29 [ 2 ] = { 2, 9 };
	int iV51 [ 2 ] = { 5, 1 };
	SSecuenciaUnica * p_secObj = CrearSec ( iV, 5 );
	SSecuenciaUnica * p_sec24 = CrearSec ( iV24, 2 );
	SLista * p_lis9 = CrearLista ( iV9, 1 );
	SLista * p_lis29 = CrearLista ( iV29, 2 );
	SLista * p_lis51 = CrearLista ( iV51, 2 );
	SSecuencia * p_sec9 = SSecCrearDesdeLista ( p_lis9 );
	SSecuenciaUnica * p_secRes = NULL;
	if ( ES_VALIDO ( p_secObj ) && ES_VALIDO ( p_sec24 ) && ES_VALIDO ( p_lis9 ) && ES_VALIDO ( p_lis29 ) &&
		 ES_VALIDO ( p_lis51 ) && ES_VALIDO ( p_sec9 ) )
	{
		if ( ( SSecUnExistenTodos ( p_secObj, p_sec24 ) != 1 ) || ( SSecUnExisteAlguno ( p_secObj, p_sec24 ) != 1 ) ||
			 ( SSecUnExistenTodosLista ( p_secObj, p_lis29 ) != 0 ) || ( SSecUnExisteAlgunoLista ( p_secObj, p_lis29 ) != 1 ) ||
			 ( SSecUnExisteAlgunoSecuencia ( p_secObj, p_sec9 ) != 0 ) || ( SSecUnExistenTodosSecuencia ( p_secObj, p_sec9 ) != 0 ) )
		{
			printf( "Error caso 1: se esperaba 1, 1, 0, 1, 0 y 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
		int iEsp2 [ 4 ] = { 1, 3, 4, 5 };
		if ( ( SSecUnEliminarLista ( p_secObj, p_lis29 ) != 1 ) || ( SSecUnEliminarSecuencia ( p_secObj, p_sec9 ) != 1 ) ||
			 ( VerificarSec ( p_secObj, iEsp2, 4 ) != BOOL_VAL_CIERTO ) || ( VerificarLista ( p_lis29, iV29, 2 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 2: deberia quedar { 1, 3, 4, 5 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SElemento * p_elmCinco = SSecUnElemento ( p_secObj, 3 );
		int iEsp3 [ 2 ] = { 3, 4 };
		p_secRes = SSecUnExtraerLista ( p_secObj, p_lis51 );
		if ( ( VerificarSec ( p_secRes, iV51, 2 ) != BOOL_VAL_CIERTO ) || ( SSecUnElemento ( p_secRes, 0 ) != p_elmCinco ) ||
			 ( VerificarSec ( p_secObj, iEsp3, 2 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 3: se esperaba sacar { 5, 1 } y dejar { 3, 4 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SSecUnDestruir ( &p_secRes );
		int iQueda3 [ 1 ] = { 3 };
		p_secRes = SSecUnExtraerSecuenciaUn ( p_secObj, p_sec24 );
		if ( ( VerificarSec ( p_secRes, iV24 + 1, 1 ) != BOOL_VAL_CIERTO ) || ( VerificarSec ( p_secObj, iQueda3, 1 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 4: se esperaba sacar { 4 } y dejar { 3 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SSecUnDestruir ( &p_secRes );
		if ( ( SSecUnEliminarSecuenciaUn ( p_secObj, p_secObj ) != 0 ) || ES_VALIDO ( SSecUnExtraerSecuenciaUn ( p_secObj, p_secObj ) ) ||
			 ( SSecUnExistenTodos ( NULL, p_sec24 ) != 0 ) || ( SSecUnEliminarLista ( p_secObj, NULL ) != 0 ) ||
			 ES_VALIDO ( SSecUnExtraerSecuencia ( p_secObj, NULL ) ) || ( VerificarSec ( p_secObj, iQueda3, 1 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 5: con la misma secuencia o nulos se esperaba 0 o nulo sin cambios\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear las secuencias o las listas\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SSecUnDestruir ( &p_secObj );
	SSecUnDestruir ( &p_sec24 );
	SSecDestruir ( &p_sec9 );
	SLisDestruir ( &p_lis9 );
	SLisDestruir ( &p_lis29 );
	SLisDestruir ( &p_lis51 );
	ErrLimpiar ();
	return ( iRes );
}

/* Union sin repetidos: la primera y, detras, lo que falta de la segunda.
   Interseccion y Diferencia, en el orden de la primera. Todas con copias. */
static int TestSSecUnUnion01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SSecUnUnion 01:\n" );

	int iV1 [ 3 ] = { 1, 2, 3 };
	int iV2 [ 3 ] = { 3, 4, 1 };
	int iEspU [ 4 ] = { 1, 2, 3, 4 };
	int iEspI [ 2 ] = { 1, 3 };
	int iEspD [ 1 ] = { 2 };
	SSecuenciaUnica * p_sec1 = CrearSec ( iV1, 3 );
	SSecuenciaUnica * p_sec2 = CrearSec ( iV2, 3 );
	SSecuenciaUnica * p_secU = NULL;
	SSecuenciaUnica * p_secI = NULL;
	SSecuenciaUnica * p_secD = NULL;
	if ( ES_VALIDO ( p_sec1 ) && ES_VALIDO ( p_sec2 ) )
	{
		p_secU = SSecUnUnion ( p_sec1, p_sec2 );
		p_secI = SSecUnInterseccion ( p_sec1, p_sec2 );
		p_secD = SSecUnDiferencia ( p_sec1, p_sec2 );
		if ( ( VerificarSec ( p_secU, iEspU, 4 ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarSec ( p_secI, iEspI, 2 ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarSec ( p_secD, iEspD, 1 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 1: se esperaba { 1, 2, 3, 4 }, { 1, 3 } y { 2 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( VerificarSec ( p_sec1, iV1, 3 ) != BOOL_VAL_CIERTO ) || ( VerificarSec ( p_sec2, iV2, 3 ) != BOOL_VAL_CIERTO ) ||
			 ES_NULO ( p_secU ) || ( SSecUnElemento ( p_secU, 3 ) == SSecUnElemento ( p_sec2, 1 ) ) )
		{
			printf( "Error caso 2: las de entrada no deberian cambiar y la union deberia tener copias\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( SSecUnUnion ( p_sec1, NULL ) ) || ES_VALIDO ( SSecUnInterseccion ( NULL, p_sec2 ) ) ||
			 ES_VALIDO ( SSecUnDiferencia ( p_sec1, NULL ) ) )
		{
			printf( "Error caso 3: con nulos se esperaba nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear las secuencias\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SSecUnDestruir ( &p_secU );
	SSecUnDestruir ( &p_secI );
	SSecUnDestruir ( &p_secD );
	SSecUnDestruir ( &p_sec1 );
	SSecUnDestruir ( &p_sec2 );
	return ( iRes );
}



int TestSSecuenciaUnica ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SSecuenciaUnica]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSSecUnInsertar01 () == BOOL_VAL_CIERTO ) &&
			( TestSSecUnCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSSecUnConcatenar01 () == BOOL_VAL_CIERTO ) &&
			( TestSSecUnOperacionesListas01 () == BOOL_VAL_CIERTO ) &&
			( TestSSecUnUnion01 () == BOOL_VAL_CIERTO ) )
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
