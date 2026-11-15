#include "Base.h"

#include "SSecuenciaUnicaPtr.h"



#define TAM_ENTERO		( (int) sizeof ( int ) )



static byte * NuevoEntero ( int iDato )
{
	int * p_iRes = (int *) MemReservar ( sizeof ( int ) );
	if ( ES_VALIDO ( p_iRes ) )
	{
		*p_iRes = iDato;
	}
	return ( (byte *) p_iRes );
}

static int Entero ( byte * p_byDatos )
{
	int iRes = -999;
	if ( ES_VALIDO ( p_byDatos ) )
	{
		iRes = *( (int *) p_byDatos );
	}
	return ( iRes );
}

/* Igualdad y copia de cadenas para las Ext. */
static int SonIgualesCad ( byte * p_byCad1, byte * p_byCad2 )
{
	return ( CadComparar ( (char *) p_byCad1, (char *) p_byCad2 ) == COMP_IGUAL );
}

static byte * DuplicarCad ( byte * p_byCad )
{
	return ( (byte *) CadDuplicar ( (char *) p_byCad ) );
}

static SListaPtr * CrearLista ( int * p_iValores, int iNum )
{
	SListaPtr * p_lisObj = SLispCrear ();
	int iPos = 0;
	while ( ES_VALIDO ( p_lisObj ) && ( iPos < iNum ) )
	{
		SLispInsertarAlFinal ( p_lisObj, NuevoEntero ( p_iValores [ iPos ] ) );
		iPos = iPos + 1;
	}
	return ( p_lisObj );
}

static SListaPtr * CrearListaCad ( const char ** p_p_cValores, int iNum )
{
	SListaPtr * p_lisObj = SLispCrear ();
	int iPos = 0;
	while ( ES_VALIDO ( p_lisObj ) && ( iPos < iNum ) )
	{
		SLispInsertarAlFinal ( p_lisObj, (byte *) CadDuplicar ( p_p_cValores [ iPos ] ) );
		iPos = iPos + 1;
	}
	return ( p_lisObj );
}

static SSecuenciaUnicaPtr * CrearSec ( int * p_iValores, int iNum )
{
	SSecuenciaUnicaPtr * p_secObj = SSecpUnCrear ();
	int iPos = 0;
	while ( ES_VALIDO ( p_secObj ) && ( iPos < iNum ) )
	{
		SSecpUnInsertar ( p_secObj, NuevoEntero ( p_iValores [ iPos ] ), TAM_ENTERO );
		iPos = iPos + 1;
	}
	return ( p_secObj );
}

static int VerificarLista ( SListaPtr * p_lisObj, int * p_iEsperados, int iNum )
{
	int iRes = BOOL_VAL_CIERTO;

	if ( SLispNumElementos ( p_lisObj ) != iNum )
	{
		printf( "  Verificacion: se esperaban %d elementos: %d\n", iNum, SLispNumElementos ( p_lisObj ) );
		iRes = BOOL_VAL_FALSO;
	}
	int iPos = 0;
	SElementoPtr * p_elpObj = SLispElementoPtr ( p_lisObj, 0 );
	while ( ( iPos < iNum ) && ( iRes == BOOL_VAL_CIERTO ) )
	{
		if ( ES_NULO ( p_elpObj ) || ( Entero ( SElpDatos ( p_elpObj ) ) != p_iEsperados [ iPos ] ) )
		{
			printf( "  Verificacion: en pos %d se esperaba %d\n", iPos, p_iEsperados [ iPos ] );
			iRes = BOOL_VAL_FALSO;
		}
		else
		{
			p_elpObj = SElpSucesor ( p_elpObj );
		}
		iPos = iPos + 1;
	}
	return ( iRes );
}

static int VerificarSec ( SSecuenciaUnicaPtr * p_secObj, int * p_iEsperados, int iNum )
{
	int iRes;

	if ( SSecpUnEsValida ( p_secObj, TAM_ENTERO ) != 1 )
	{
		printf( "  Verificacion: la secuencia no es valida o tiene repetidos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		iRes = VerificarLista ( SSecpUnLista ( p_secObj ), p_iEsperados, iNum );
	}
	return ( iRes );
}

static int VerificarSecCad ( SSecuenciaUnicaPtr * p_secObj, const char ** p_p_cEsperados, int iNum )
{
	int iRes = BOOL_VAL_CIERTO;

	if ( ( SSecpUnEsValidaExt ( p_secObj, SonIgualesCad ) != 1 ) || ( SSecpUnNumElementos ( p_secObj ) != iNum ) )
	{
		printf( "  Verificacion: se esperaban %d cadenas distintas: %d\n", iNum, SSecpUnNumElementos ( p_secObj ) );
		iRes = BOOL_VAL_FALSO;
	}
	int iPos = 0;
	while ( ( iPos < iNum ) && ( iRes == BOOL_VAL_CIERTO ) )
	{
		if ( CadComparar ( (char *) SSecpUnElemento ( p_secObj, iPos ), p_p_cEsperados [ iPos ] ) != COMP_IGUAL )
		{
			printf( "  Verificacion: en pos %d se esperaba \"%s\"\n", iPos, p_p_cEsperados [ iPos ] );
			iRes = BOOL_VAL_FALSO;
		}
		iPos = iPos + 1;
	}
	return ( iRes );
}



/* Insertar no admite un dato que ya este: devuelve 0 y el dato sigue siendo
   del llamante. Las Ptr enganchan ese mismo elemento. */
static int TestSSecpUnInsertar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SSecpUnInsertar 01:\n" );

	SSecuenciaUnicaPtr * p_secObj = SSecpUnCrear ();
	byte * p_byRepetido = NuevoEntero ( 3 );
	byte * p_bySonda = NuevoEntero ( 1 );
	SElementoPtr * p_elpNuevo = SElpCrear ( NuevoEntero ( 8 ), 1 );
	SElementoPtr * p_elpRepetido = SElpCrear ( NuevoEntero ( 8 ), 1 );
	if ( ES_VALIDO ( p_secObj ) && ES_VALIDO ( p_byRepetido ) && ES_VALIDO ( p_bySonda ) &&
		 ES_VALIDO ( p_elpNuevo ) && ES_VALIDO ( p_elpRepetido ) )
	{
		if ( ( SSecpUnInsertar ( p_secObj, NuevoEntero ( 3 ), TAM_ENTERO ) != 1 ) ||
			 ( SSecpUnInsertar ( p_secObj, NuevoEntero ( 1 ), TAM_ENTERO ) != 1 ) ||
			 ( SSecpUnInsertar ( p_secObj, p_byRepetido, TAM_ENTERO ) != 0 ) )
		{
			printf( "Error caso 1: se esperaba 1, 1 y 0 para el 3 repetido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SSecpUnInsertarPtr ( p_secObj, p_elpNuevo, TAM_ENTERO ) != 1 ) ||
			 ( SSecpUnInsertarPtr ( p_secObj, p_elpRepetido, TAM_ENTERO ) != 0 ) ||
			 ( SSecpUnElementoPtr ( p_secObj, 2 ) != p_elpNuevo ) )
		{
			printf( "Error caso 2: InsertarPtr deberia enganchar ese elemento y rechazar el 8 repetido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		else
		{
			p_elpNuevo = NULL;
		}
		int iEsp [ 3 ] = { 3, 1, 8 };
		if ( VerificarSec ( p_secObj, iEsp, 3 ) != BOOL_VAL_CIERTO )
		{
			printf( "Error caso 3: deberia quedar { 3, 1, 8 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SSecpUnExiste ( p_secObj, p_bySonda, TAM_ENTERO ) != 1 ) || ( SSecpUnBuscar ( p_secObj, p_bySonda, TAM_ENTERO ) != 1 ) ||
			 ( SSecpUnExistePtr ( p_secObj, p_elpRepetido, TAM_ENTERO ) != 1 ) ||
			 ( SSecpUnBuscarPtr ( p_secObj, p_elpRepetido, TAM_ENTERO ) != 2 ) )
		{
			printf( "Error caso 4: el 1 deberia estar en la posicion 1 y el 8 en la 2\n" );
			iRes = BOOL_VAL_FALSO;
		}
		byte * p_byExt = SSecpUnExtraer ( p_secObj, 0 );
		if ( ( Entero ( p_byExt ) != 3 ) || ( SSecpUnNumElementos ( p_secObj ) != 2 ) )
		{
			printf( "Error caso 5: extraer la posicion 0 deberia dar el 3\n" );
			iRes = BOOL_VAL_FALSO;
		}
		MemLiberar ( (void **) &p_byExt );
		if ( SSecpUnInsertar ( p_secObj, p_byRepetido, TAM_ENTERO ) != 1 )
		{
			printf( "Error caso 6: tras extraer el 3 deberia poder volver a entrar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		else
		{
			p_byRepetido = NULL;
		}
		if ( ( SSecpUnEliminar ( p_secObj, 0 ) != 1 ) || ( SSecpUnExiste ( p_secObj, p_bySonda, TAM_ENTERO ) != 0 ) ||
			 ( SSecpUnVaciar ( p_secObj ) != 1 ) || ( SSecpUnEstaVacia ( p_secObj ) != 1 ) )
		{
			printf( "Error caso 7: eliminar el 1 y vaciar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SSecpUnInsertar ( NULL, p_bySonda, TAM_ENTERO ) != 0 ) || ( SSecpUnInsertar ( p_secObj, NULL, TAM_ENTERO ) != 0 ) ||
			 ( SSecpUnInsertarPtr ( p_secObj, NULL, TAM_ENTERO ) != 0 ) || ( SSecpUnBuscar ( NULL, p_bySonda, TAM_ENTERO ) != -1 ) ||
			 ( SSecpUnEsValida ( NULL, TAM_ENTERO ) != 0 ) || ( SSecpUnEsValidaExt ( p_secObj, NULL ) != 0 ) )
		{
			printf( "Error caso 8: con nulos se esperaba 0 o -1\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la secuencia o los datos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	MemLiberar ( (void **) &p_byRepetido );
	MemLiberar ( (void **) &p_bySonda );
	SElpDestruir ( &p_elpNuevo );
	SElpDestruir ( &p_elpRepetido );
	SSecpUnDestruir ( &p_secObj );
	return ( iRes );
}

/* Las Ext comparan y copian con las funciones que se les dan: aqui, cadenas
   por su contenido. */
static int TestSSecpUnExt01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SSecpUnExt 01:\n" );

	const char * p_cV [ 4 ] = { "b", "a", "b", "c" };
	const char * p_cEsp [ 3 ] = { "b", "a", "c" };
	const char * p_cEsp2 [ 4 ] = { "b", "a", "c", "d" };
	SListaPtr * p_lisVal = CrearListaCad ( p_cV, 4 );
	SSecuenciaUnicaPtr * p_secObj = NULL;
	SSecuenciaUnicaPtr * p_secDup = NULL;
	if ( ES_VALIDO ( p_lisVal ) )
	{
		p_secObj = SSecpUnCrearDesdeListaExt ( p_lisVal, SonIgualesCad, DuplicarCad );
		if ( ( VerificarSecCad ( p_secObj, p_cEsp, 3 ) != BOOL_VAL_CIERTO ) || ( SLispNumElementos ( p_lisVal ) != 4 ) ||
			 ( SSecpUnElemento ( p_secObj, 0 ) == SLispElemento ( p_lisVal, 0 ) ) )
		{
			printf( "Error caso 1: se esperaban copias de { b, a, c } y la lista sin tocar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Con otro bloque del mismo texto: es el mismo valor. */
		char * p_cOtraA = CadDuplicar ( "a" );
		if ( ( SSecpUnInsertarExt ( p_secObj, (byte *) p_cOtraA, SonIgualesCad ) != 0 ) ||
			 ( SSecpUnBuscarExt ( p_secObj, (byte *) p_cOtraA, SonIgualesCad ) != 1 ) ||
			 ( SSecpUnExisteExt ( p_secObj, (byte *) "d", SonIgualesCad ) != 0 ) ||
			 ( SSecpUnInsertarExt ( p_secObj, (byte *) CadDuplicar ( "d" ), SonIgualesCad ) != 1 ) ||
			 ( VerificarSecCad ( p_secObj, p_cEsp2, 4 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 2: la \"a\" repetida no deberia entrar y la \"d\" si\n" );
			iRes = BOOL_VAL_FALSO;
		}
		MemLiberar ( (void **) &p_cOtraA );
		p_secDup = SSecpUnDuplicarExt ( p_secObj, DuplicarCad );
		if ( ( VerificarSecCad ( p_secDup, p_cEsp2, 4 ) != BOOL_VAL_CIERTO ) ||
			 ( SSecpUnElemento ( p_secDup, 0 ) == SSecpUnElemento ( p_secObj, 0 ) ) )
		{
			printf( "Error caso 3: la copia deberia tener cadenas propias\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Por bytes, dos cadenas de un caracter con el mismo primer byte son
		   iguales: EsValida depende del criterio que se le pase. */
		if ( ( SSecpUnEsValidaExt ( p_secObj, SonIgualesCad ) != 1 ) || ( SSecpUnEsValida ( p_secObj, 1 ) != 1 ) ||
			 ( SSecpInsertar ( SSecpUnSecuencia ( p_secDup ), (byte *) CadDuplicar ( "a" ) ) != 1 ) ||
			 ( SSecpUnEsValidaExt ( p_secDup, SonIgualesCad ) != 0 ) )
		{
			printf( "Error caso 4: con una \"a\" metida por debajo no deberia ser valida\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la lista\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SSecpUnDestruir ( &p_secObj );
	SSecpUnDestruir ( &p_secDup );
	SLispDestruir ( &p_lisVal );
	return ( iRes );
}

/* Crear copia una vez cada valor; Concatenar mueve los que faltan y deja los
   demas en la de entrada; las Dup copian los que faltan. */
static int TestSSecpUnConcatenar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SSecpUnConcatenar 01:\n" );

	int iV [ 4 ] = { 2, 5, 2, 7 };
	int iEspC [ 3 ] = { 2, 5, 7 };
	int iV12 [ 2 ] = { 1, 2 };
	int iV2334 [ 4 ] = { 2, 3, 3, 4 };
	SListaPtr * p_lisCrear = CrearLista ( iV, 4 );
	SSecuenciaPtr * p_secCrear = SSecpCrearDesdeLista ( p_lisCrear, TAM_ENTERO );
	SSecuenciaUnicaPtr * p_secObj = CrearSec ( iV12, 2 );
	SSecuenciaUnicaPtr * p_secDup = CrearSec ( iV12, 2 );
	SListaPtr * p_lisVal = CrearLista ( iV2334, 4 );
	SListaPtr * p_lisDup = CrearLista ( iV2334, 4 );
	SSecuenciaUnicaPtr * p_secC1 = NULL;
	SSecuenciaUnicaPtr * p_secC2 = NULL;
	if ( ES_VALIDO ( p_lisCrear ) && ES_VALIDO ( p_secCrear ) && ES_VALIDO ( p_secObj ) && ES_VALIDO ( p_secDup ) &&
		 ES_VALIDO ( p_lisVal ) && ES_VALIDO ( p_lisDup ) )
	{
		p_secC1 = SSecpUnCrearDesdeLista ( p_lisCrear, TAM_ENTERO );
		p_secC2 = SSecpUnCrearDesdeSecuencia ( p_secCrear, TAM_ENTERO );
		if ( ( VerificarSec ( p_secC1, iEspC, 3 ) != BOOL_VAL_CIERTO ) || ( VerificarSec ( p_secC2, iEspC, 3 ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarLista ( p_lisCrear, iV, 4 ) != BOOL_VAL_CIERTO ) ||
			 ( SSecpUnElemento ( p_secC1, 0 ) == SLispElemento ( p_lisCrear, 0 ) ) )
		{
			printf( "Error caso 1: se esperaban copias de { 2, 5, 7 } y la lista sin tocar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		byte * p_byTres = SLispElemento ( p_lisVal, 1 );
		int iEsp1 [ 4 ] = { 1, 2, 3, 4 };
		int iQuedan [ 2 ] = { 2, 3 };
		if ( ( SSecpUnConcatenarLista ( p_secObj, p_lisVal, TAM_ENTERO ) != 1 ) ||
			 ( VerificarSec ( p_secObj, iEsp1, 4 ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarLista ( p_lisVal, iQuedan, 2 ) != BOOL_VAL_CIERTO ) ||
			 ( SSecpUnElemento ( p_secObj, 2 ) != p_byTres ) )
		{
			printf( "Error caso 2: se esperaba { 1, 2, 3, 4 }, el mismo 3 y { 2, 3 } en la lista\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SSecpUnConcatenarListaDup ( p_secDup, p_lisDup, TAM_ENTERO ) != 1 ) ||
			 ( VerificarSec ( p_secDup, iEsp1, 4 ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarLista ( p_lisDup, iV2334, 4 ) != BOOL_VAL_CIERTO ) ||
			 ( SSecpUnElemento ( p_secDup, 2 ) == SLispElemento ( p_lisDup, 1 ) ) )
		{
			printf( "Error caso 3: Dup deberia dar copias de { 1, 2, 3, 4 } sin tocar la lista\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SSecpUnConcatenar ( p_secObj, p_secC1, TAM_ENTERO ) != 1 ) || ( SSecpUnNumElementos ( p_secObj ) != 6 ) ||
			 ( SSecpUnNumElementos ( p_secC1 ) != 1 ) || ( SSecpUnConcatenarDup ( p_secDup, p_secObj, TAM_ENTERO ) != 1 ) ||
			 ( SSecpUnNumElementos ( p_secDup ) != 6 ) )
		{
			printf( "Error caso 4: con otras unicas deberian pasar el 5 y el 7\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SSecpUnConcatenarLista ( p_secObj, SSecpUnLista ( p_secObj ), TAM_ENTERO ) != 0 ) ||
			 ( SSecpUnConcatenarListaDup ( p_secObj, SSecpUnLista ( p_secObj ), TAM_ENTERO ) != 0 ) ||
			 ( SSecpUnConcatenar ( NULL, p_secDup, TAM_ENTERO ) != 0 ) || ( SSecpUnConcatenarSecuencia ( p_secObj, NULL, TAM_ENTERO ) != 0 ) ||
			 ( SSecpUnNumElementos ( p_secObj ) != 6 ) )
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
	SSecpUnDestruir ( &p_secC1 );
	SSecpUnDestruir ( &p_secC2 );
	SSecpUnDestruir ( &p_secObj );
	SSecpUnDestruir ( &p_secDup );
	SSecpDestruir ( &p_secCrear );
	SLispDestruir ( &p_lisCrear );
	SLispDestruir ( &p_lisVal );
	SLispDestruir ( &p_lisDup );
	return ( iRes );
}

/* Pertenencia, Eliminar y Extraer, que mueve a una secuencia unica nueva en
   el orden de los valores buscados. */
static int TestSSecpUnOperacionesListas01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SSecpUnOperacionesListas 01:\n" );

	int iV [ 5 ] = { 1, 2, 3, 4, 5 };
	int iV24 [ 2 ] = { 2, 4 };
	int iV29 [ 2 ] = { 2, 9 };
	int iV51 [ 2 ] = { 5, 1 };
	SSecuenciaUnicaPtr * p_secObj = CrearSec ( iV, 5 );
	SSecuenciaUnicaPtr * p_sec24 = CrearSec ( iV24, 2 );
	SListaPtr * p_lis29 = CrearLista ( iV29, 2 );
	SListaPtr * p_lis51 = CrearLista ( iV51, 2 );
	SSecuenciaUnicaPtr * p_secRes = NULL;
	if ( ES_VALIDO ( p_secObj ) && ES_VALIDO ( p_sec24 ) && ES_VALIDO ( p_lis29 ) && ES_VALIDO ( p_lis51 ) )
	{
		if ( ( SSecpUnExistenTodos ( p_secObj, p_sec24, TAM_ENTERO ) != 1 ) ||
			 ( SSecpUnExistenTodosLista ( p_secObj, p_lis29, TAM_ENTERO ) != 0 ) ||
			 ( SSecpUnExisteAlgunoLista ( p_secObj, p_lis29, TAM_ENTERO ) != 1 ) ||
			 ( SSecpUnExisteAlgunoSecuencia ( p_secObj, SSecpUnSecuencia ( p_sec24 ), TAM_ENTERO ) != 1 ) )
		{
			printf( "Error caso 1: se esperaba 1, 0, 1 y 1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		int iEsp2 [ 4 ] = { 1, 3, 4, 5 };
		if ( ( SSecpUnEliminarLista ( p_secObj, p_lis29, TAM_ENTERO ) != 1 ) ||
			 ( VerificarSec ( p_secObj, iEsp2, 4 ) != BOOL_VAL_CIERTO ) || ( VerificarLista ( p_lis29, iV29, 2 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 2: deberia quedar { 1, 3, 4, 5 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		byte * p_byCinco = SSecpUnElemento ( p_secObj, 3 );
		int iEsp3 [ 2 ] = { 3, 4 };
		p_secRes = SSecpUnExtraerLista ( p_secObj, p_lis51, TAM_ENTERO );
		if ( ( VerificarSec ( p_secRes, iV51, 2 ) != BOOL_VAL_CIERTO ) || ( SSecpUnElemento ( p_secRes, 0 ) != p_byCinco ) ||
			 ( VerificarSec ( p_secObj, iEsp3, 2 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 3: se esperaba sacar { 5, 1 } y dejar { 3, 4 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SSecpUnDestruir ( &p_secRes );
		int iQueda3 [ 1 ] = { 3 };
		p_secRes = SSecpUnExtraerSecuenciaUn ( p_secObj, p_sec24, TAM_ENTERO );
		if ( ( VerificarSec ( p_secRes, iV24 + 1, 1 ) != BOOL_VAL_CIERTO ) || ( VerificarSec ( p_secObj, iQueda3, 1 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 4: se esperaba sacar { 4 } y dejar { 3 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SSecpUnDestruir ( &p_secRes );
		if ( ( SSecpUnEliminarSecuenciaUn ( p_secObj, p_secObj, TAM_ENTERO ) != 0 ) ||
			 ES_VALIDO ( SSecpUnExtraerSecuenciaUn ( p_secObj, p_secObj, TAM_ENTERO ) ) ||
			 ( SSecpUnExistenTodos ( NULL, p_sec24, TAM_ENTERO ) != 0 ) || ( SSecpUnEliminarLista ( p_secObj, NULL, TAM_ENTERO ) != 0 ) ||
			 ( VerificarSec ( p_secObj, iQueda3, 1 ) != BOOL_VAL_CIERTO ) )
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
	SSecpUnDestruir ( &p_secObj );
	SSecpUnDestruir ( &p_sec24 );
	SLispDestruir ( &p_lis29 );
	SLispDestruir ( &p_lis51 );
	ErrLimpiar ();
	return ( iRes );
}

/* Union sin repetidos; Interseccion y Diferencia en el orden de la primera.
   Con enteros por bytes y con cadenas por contenido. */
static int TestSSecpUnUnion01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SSecpUnUnion 01:\n" );

	int iV1 [ 3 ] = { 1, 2, 3 };
	int iV2 [ 3 ] = { 3, 4, 1 };
	int iEspU [ 4 ] = { 1, 2, 3, 4 };
	int iEspI [ 2 ] = { 1, 3 };
	int iEspD [ 1 ] = { 2 };
	const char * p_cV1 [ 2 ] = { "x", "y" };
	const char * p_cV2 [ 2 ] = { "z", "x" };
	const char * p_cEspU [ 3 ] = { "x", "y", "z" };
	const char * p_cEspI [ 1 ] = { "x" };
	const char * p_cEspD [ 1 ] = { "y" };
	SSecuenciaUnicaPtr * p_sec1 = CrearSec ( iV1, 3 );
	SSecuenciaUnicaPtr * p_sec2 = CrearSec ( iV2, 3 );
	SListaPtr * p_lisCad1 = CrearListaCad ( p_cV1, 2 );
	SListaPtr * p_lisCad2 = CrearListaCad ( p_cV2, 2 );
	SSecuenciaUnicaPtr * p_secCad1 = SSecpUnCrearDesdeListaExt ( p_lisCad1, SonIgualesCad, DuplicarCad );
	SSecuenciaUnicaPtr * p_secCad2 = SSecpUnCrearDesdeListaExt ( p_lisCad2, SonIgualesCad, DuplicarCad );
	SSecuenciaUnicaPtr * p_secU = NULL;
	SSecuenciaUnicaPtr * p_secI = NULL;
	SSecuenciaUnicaPtr * p_secD = NULL;
	SSecuenciaUnicaPtr * p_secUC = NULL;
	SSecuenciaUnicaPtr * p_secIC = NULL;
	SSecuenciaUnicaPtr * p_secDC = NULL;
	if ( ES_VALIDO ( p_sec1 ) && ES_VALIDO ( p_sec2 ) && ES_VALIDO ( p_secCad1 ) && ES_VALIDO ( p_secCad2 ) )
	{
		p_secU = SSecpUnUnion ( p_sec1, p_sec2, TAM_ENTERO );
		p_secI = SSecpUnInterseccion ( p_sec1, p_sec2, TAM_ENTERO );
		p_secD = SSecpUnDiferencia ( p_sec1, p_sec2, TAM_ENTERO );
		if ( ( VerificarSec ( p_secU, iEspU, 4 ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarSec ( p_secI, iEspI, 2 ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarSec ( p_secD, iEspD, 1 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 1: se esperaba { 1, 2, 3, 4 }, { 1, 3 } y { 2 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( VerificarSec ( p_sec1, iV1, 3 ) != BOOL_VAL_CIERTO ) || ( VerificarSec ( p_sec2, iV2, 3 ) != BOOL_VAL_CIERTO ) ||
			 ES_NULO ( p_secU ) || ( SSecpUnElemento ( p_secU, 3 ) == SSecpUnElemento ( p_sec2, 1 ) ) )
		{
			printf( "Error caso 2: las de entrada no deberian cambiar y la union deberia tener copias\n" );
			iRes = BOOL_VAL_FALSO;
		}
		p_secUC = SSecpUnUnionExt ( p_secCad1, p_secCad2, SonIgualesCad, DuplicarCad );
		p_secIC = SSecpUnInterseccionExt ( p_secCad1, p_secCad2, SonIgualesCad, DuplicarCad );
		p_secDC = SSecpUnDiferenciaExt ( p_secCad1, p_secCad2, SonIgualesCad, DuplicarCad );
		if ( ( VerificarSecCad ( p_secUC, p_cEspU, 3 ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarSecCad ( p_secIC, p_cEspI, 1 ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarSecCad ( p_secDC, p_cEspD, 1 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 3: con cadenas se esperaba { x, y, z }, { x } y { y }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( SSecpUnUnion ( p_sec1, NULL, TAM_ENTERO ) ) || ES_VALIDO ( SSecpUnInterseccion ( NULL, p_sec2, TAM_ENTERO ) ) ||
			 ES_VALIDO ( SSecpUnDiferenciaExt ( p_secCad1, NULL, SonIgualesCad, DuplicarCad ) ) )
		{
			printf( "Error caso 4: con nulos se esperaba nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear las secuencias\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SSecpUnDestruir ( &p_secU );
	SSecpUnDestruir ( &p_secI );
	SSecpUnDestruir ( &p_secD );
	SSecpUnDestruir ( &p_secUC );
	SSecpUnDestruir ( &p_secIC );
	SSecpUnDestruir ( &p_secDC );
	SSecpUnDestruir ( &p_sec1 );
	SSecpUnDestruir ( &p_sec2 );
	SSecpUnDestruir ( &p_secCad1 );
	SSecpUnDestruir ( &p_secCad2 );
	SLispDestruir ( &p_lisCad1 );
	SLispDestruir ( &p_lisCad2 );
	return ( iRes );
}



int TestSSecuenciaUnicaPtr ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SSecuenciaUnicaPtr]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSSecpUnInsertar01 () == BOOL_VAL_CIERTO ) &&
			( TestSSecpUnExt01 () == BOOL_VAL_CIERTO ) &&
			( TestSSecpUnConcatenar01 () == BOOL_VAL_CIERTO ) &&
			( TestSSecpUnOperacionesListas01 () == BOOL_VAL_CIERTO ) &&
			( TestSSecpUnUnion01 () == BOOL_VAL_CIERTO ) )
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
