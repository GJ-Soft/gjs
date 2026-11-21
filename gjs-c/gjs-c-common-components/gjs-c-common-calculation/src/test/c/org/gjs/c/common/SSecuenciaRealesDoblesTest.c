#include "Base.h"

#include "SSecuenciaRealesDobles.h"
#include "CalculoOperaciones.h"



static int TestSSecRealdCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SSecRealdCrear 01:\n" );

	SSecuenciaRealesDobles * p_secObj = SSecRealdCrear ();
	if ( ES_NULO ( p_secObj ) )
	{
		printf( "Error caso 1: no se esperaba nulo al crear\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SSecRealdEsValida ( p_secObj ) != 1 )
		{
			printf( "Error caso 2: la secuencia recien creada deberia ser valida\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SSecRealdNumElementos ( p_secObj ) != 0 )
		{
			printf( "Error caso 3: el numero de elementos deberia ser 0: %d\n", SSecRealdNumElementos ( p_secObj ) );
			iRes = BOOL_VAL_FALSO;
		}
	}
	SSecRealdDestruir ( &p_secObj );

	if ( ES_VALIDO ( p_secObj ) )
	{
		printf( "Error caso 4: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSSecRealdInsertar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SSecRealdInsertar 01:\n" );

	SSecuenciaRealesDobles * p_secObj = SSecRealdCrear ();
	if ( ES_VALIDO ( p_secObj ) )
	{
		SSecRealdInsertar ( p_secObj, 10.0 );
		SSecRealdInsertar ( p_secObj, 20.0 );
		SSecRealdInsertar ( p_secObj, 30.0 );

		if ( SSecRealdNumElementos ( p_secObj ) != 3 )
		{
			printf( "Error caso 1: se esperaban 3 elementos: %d\n", SSecRealdNumElementos ( p_secObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SSecRealdExiste ( p_secObj, 20.0 ) != 1 )
		{
			printf( "Error caso 2: 20 deberia existir en la secuencia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SSecRealdExiste ( p_secObj, 99.0 ) != 0 )
		{
			printf( "Error caso 3: 99 no deberia existir en la secuencia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Modificar y releer el elemento 0. */
		if ( SSecRealdModificar ( p_secObj, 0, 99.0 ) != 1 )
		{
			printf( "Error caso 4: se esperaba resultado 1 al modificar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( MatEsIgual ( SSecRealdElemento ( p_secObj, 0 ), 99.0 ) != 1 )
		{
			printf( "Error caso 5: el elemento 0 deberia ser 99: %f\n", SSecRealdElemento ( p_secObj, 0 ) );
			iRes = BOOL_VAL_FALSO;
		}
		/* Eliminar reduce el numero de elementos. */
		SSecRealdEliminar ( p_secObj, 0 );
		if ( SSecRealdNumElementos ( p_secObj ) != 2 )
		{
			printf( "Error caso 6: deberian quedar 2 elementos: %d\n", SSecRealdNumElementos ( p_secObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		SSecRealdVaciar ( p_secObj );
		if ( SSecRealdNumElementos ( p_secObj ) != 0 )
		{
			printf( "Error caso 7: la secuencia deberia quedar vacia tras vaciarla\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la secuencia\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SSecRealdDestruir ( &p_secObj );
	return ( iRes );
}

static SSecuenciaRealesDobles * CrearSec ( double * p_dValores, int iNum )
{
	SSecuenciaRealesDobles * p_secObj = SSecRealdCrear ();
	int iPos = 0;
	while ( ES_VALIDO ( p_secObj ) && ( iPos < iNum ) )
	{
		SSecRealdInsertar ( p_secObj, p_dValores [ iPos ] );
		iPos = iPos + 1;
	}
	return ( p_secObj );
}

static SListaRealesDobles * CrearLista ( double * p_dValores, int iNum )
{
	SListaRealesDobles * p_lisObj = SLisRealdCrear ();
	int iPos = 0;
	while ( ES_VALIDO ( p_lisObj ) && ( iPos < iNum ) )
	{
		SLisRealdInsertarAlFinal ( p_lisObj, p_dValores [ iPos ] );
		iPos = iPos + 1;
	}
	return ( p_lisObj );
}

/* Comprueba numero y orden de los valores, con la igualdad de la libreria. */
static int VerificarSec ( SSecuenciaRealesDobles * p_secObj, double * p_dEsperados, int iNum )
{
	int iRes = BOOL_VAL_CIERTO;

	if ( ( SSecRealdEsValida ( p_secObj ) != 1 ) || ( SSecRealdNumElementos ( p_secObj ) != iNum ) )
	{
		printf( "  Verificacion: se esperaban %d elementos: %d\n", iNum, SSecRealdNumElementos ( p_secObj ) );
		iRes = BOOL_VAL_FALSO;
	}
	int iPos = 0;
	while ( ( iPos < iNum ) && ( iRes == BOOL_VAL_CIERTO ) )
	{
		if ( MatEsIgual ( SSecRealdElemento ( p_secObj, iPos ), p_dEsperados [ iPos ] ) != 1 )
		{
			printf( "  Verificacion: en pos %d se esperaba %g: %g\n", iPos, p_dEsperados [ iPos ], SSecRealdElemento ( p_secObj, iPos ) );
			iRes = BOOL_VAL_FALSO;
		}
		iPos = iPos + 1;
	}
	return ( iRes );
}

/* Igual, para una lista. */
static int VerificarLista ( SListaRealesDobles * p_lisObj, double * p_dEsperados, int iNum )
{
	int iRes = BOOL_VAL_CIERTO;

	if ( ( SLisRealdEsValida ( p_lisObj ) != 1 ) || ( SLisRealdNumElementos ( p_lisObj ) != iNum ) )
	{
		printf( "  Verificacion: se esperaban %d elementos: %d\n", iNum, SLisRealdNumElementos ( p_lisObj ) );
		iRes = BOOL_VAL_FALSO;
	}
	int iPos = 0;
	while ( ( iPos < iNum ) && ( iRes == BOOL_VAL_CIERTO ) )
	{
		if ( MatEsIgual ( SLisRealdElemento ( p_lisObj, iPos ), p_dEsperados [ iPos ] ) != 1 )
		{
			printf( "  Verificacion: en pos %d se esperaba %g: %g\n", iPos, p_dEsperados [ iPos ], SLisRealdElemento ( p_lisObj, iPos ) );
			iRes = BOOL_VAL_FALSO;
		}
		iPos = iPos + 1;
	}
	return ( iRes );
}

/* Funciones de conjunto, contra valores ABSOLUTOS y con decimales: un Min o un
   Max que truncasen a int, o un centinela mal puesto, compilarian sin avisar. */
static int TestSSecRealdConjunto01 ()
{
	int							iRes = BOOL_VAL_CIERTO;
	double						dMin;
	double						dMax;
	double						dMed;
	SSecuenciaRealesDobles *	p_objObj;
	SSecuenciaRealesDobles *	p_objUnicos;

	printf( "Test SSecRealdConjunto 01:\n" );

	/* { 5.5, 2.25, 9.75, 5.5 }: cuatro elementos, con el 5.5 repetido. */
	double dVal [ 4 ] = { 5.5, 2.25, 9.75, 5.5 };
	p_objObj = CrearSec ( dVal, 4 );
	if ( ( MatEsIgual ( SSecRealdMin ( p_objObj ), 2.25 ) != 1 ) || ( MatEsIgual ( SSecRealdMax ( p_objObj ), 9.75 ) != 1 ) )
	{
		printf( "Error caso 1: minimo y maximo deberian ser 2.25 y 9.75: %g y %g\n", SSecRealdMin ( p_objObj ), SSecRealdMax ( p_objObj ) );
		iRes = BOOL_VAL_FALSO;
	}
	SSecRealdObtenerParametros ( p_objObj, &dMin, &dMax, &dMed );
	if ( ( MatEsIgual ( dMin, 2.25 ) != 1 ) || ( MatEsIgual ( dMax, 9.75 ) != 1 ) || ( MatEsIgual ( dMed, 5.75 ) != 1 ) )
	{
		printf( "Error caso 2: ObtenerParametros deberia dar 2.25, 9.75 y 5.75: %g, %g y %g\n", dMin, dMax, dMed );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SSecRealdTieneRepetidos ( p_objObj ) != 1 )
	{
		printf( "Error caso 3: deberia detectar repetidos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	p_objUnicos = SSecRealdExtraerUnicos ( p_objObj );
	double dEspUnicos [ 3 ] = { 5.5, 2.25, 9.75 };
	if ( ( VerificarSec ( p_objUnicos, dEspUnicos, 3 ) != BOOL_VAL_CIERTO ) || ( SSecRealdTieneRepetidos ( p_objUnicos ) != 0 ) )
	{
		printf( "Error caso 4: los unicos deberian ser { 5.5, 2.25, 9.75 }, en el orden de aparicion\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SSecRealdDestruir ( &p_objUnicos );
	if ( ( SSecRealdDefinidaPositiva ( p_objObj ) != 1 ) || ( SSecRealdSemidefinidaPositiva ( p_objObj ) != 1 ) )
	{
		printf( "Error caso 5: todos positivos: definida y semidefinida\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SSecRealdDestruir ( &p_objObj );

	/* Todos negativos: el maximo es negativo. */
	double dNeg [ 2 ] = { -2.5, -1.5 };
	p_objObj = CrearSec ( dNeg, 2 );
	if ( ( MatEsIgual ( SSecRealdMax ( p_objObj ), -1.5 ) != 1 ) || ( MatEsIgual ( SSecRealdMin ( p_objObj ), -2.5 ) != 1 ) ||
		 ( SSecRealdDefinidaPositiva ( p_objObj ) != 0 ) || ( SSecRealdSemidefinidaPositiva ( p_objObj ) != 0 ) )
	{
		printf( "Error caso 6: con { -2.5, -1.5 } se esperaba maximo -1.5, minimo -2.5 y ni definida ni semidefinida\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SSecRealdDestruir ( &p_objObj );

	/* Vacia: ni division por cero ni valores sin inicializar. */
	p_objObj = SSecRealdCrear ();
	dMin = 7.0;
	dMax = 7.0;
	dMed = 7.0;
	SSecRealdObtenerParametros ( p_objObj, &dMin, &dMax, &dMed );
	if ( ( MatEsIgual ( dMed, 0.0 ) != 1 ) || ( dMin != DBL_MAX ) || ( dMax != -DBL_MAX ) ||
		 ( SSecRealdTieneRepetidos ( p_objObj ) != 0 ) )
	{
		printf( "Error caso 7: vacia: media 0, minimo DBL_MAX, maximo -DBL_MAX y sin repetidos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SSecRealdDestruir ( &p_objObj );

	if ( ( MatEsIgual ( SSecRealdMin ( NULL ), 0.0 ) != 1 ) || ES_VALIDO ( SSecRealdExtraerUnicos ( NULL ) ) )
	{
		printf( "Error caso 8: con objeto nulo se esperaba 0 y nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	ErrLimpiar ();
	return ( iRes );
}

/* La igualdad es la de MatEsIgual en todas, tambien en las que comparan con
   otra secuencia o lista: 0.1 + 0.2 es 0.3, y 1.0 + 1e-9 es 1.0, pero 1.001
   no. */
static int TestSSecRealdTolerancia01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SSecRealdTolerancia 01:\n" );

	double dVal [ 4 ] = { 0.1 + 0.2, 1.0, 1.0 + 1e-9, 1.001 };
	double dTres [ 1 ] = { 0.3 };
	double dUno [ 1 ] = { 1.0 };
	double dEspI [ 2 ] = { 1.0, 1.0 };
	double dEspD [ 2 ] = { 0.3, 1.001 };
	SSecuenciaRealesDobles * p_secObj = CrearSec ( dVal, 4 );
	SSecuenciaRealesDobles * p_secTres = CrearSec ( dTres, 1 );
	SSecuenciaRealesDobles * p_secUno = CrearSec ( dUno, 1 );
	SListaRealesDobles * p_lisTres = CrearLista ( dTres, 1 );
	SListaRealesDobles * p_lisUno = CrearLista ( dUno, 1 );
	SSecuenciaRealesDobles * p_secRes = NULL;
	if ( ES_VALIDO ( p_secObj ) && ES_VALIDO ( p_secTres ) && ES_VALIDO ( p_secUno ) && ES_VALIDO ( p_lisTres ) &&
		 ES_VALIDO ( p_lisUno ) )
	{
		if ( ( SSecRealdExiste ( p_secObj, 0.3 ) != 1 ) || ( SSecRealdExistenTodos ( p_secObj, p_secTres ) != 1 ) ||
			 ( SSecRealdExistenTodosLista ( p_secObj, p_lisTres ) != 1 ) || ( SSecRealdExisteAlgunoLista ( p_secObj, p_lisTres ) != 1 ) )
		{
			printf( "Error caso 1: 0.3 deberia encontrarse igual con Existe y con las de secuencia y lista\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SSecRealdRepeticiones ( p_secObj, 1.0 ) != 2 ) || ( SSecRealdTieneRepetidos ( p_secObj ) != 1 ) )
		{
			printf( "Error caso 2: 1.0 y 1.0 + 1e-9 son repetidos\n" );
			iRes = BOOL_VAL_FALSO;
		}
		p_secRes = SSecRealdInterseccion ( p_secObj, p_secUno );
		if ( VerificarSec ( p_secRes, dEspI, 2 ) != BOOL_VAL_CIERTO )
		{
			printf( "Error caso 3: la interseccion con { 1.0 } deberia dar los dos casi 1.0\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SSecRealdDestruir ( &p_secRes );
		p_secRes = SSecRealdDiferenciaLista ( p_secObj, p_lisUno );
		if ( VerificarSec ( p_secRes, dEspD, 2 ) != BOOL_VAL_CIERTO )
		{
			printf( "Error caso 4: la diferencia con { 1.0 } deberia ser { 0.3, 1.001 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SSecRealdDestruir ( &p_secRes );
		/* Extraer se lleva los dos casi 1.0. */
		p_secRes = SSecRealdExtraerLista ( p_secObj, p_lisUno );
		if ( ( VerificarSec ( p_secRes, dEspI, 2 ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarSec ( p_secObj, dEspD, 2 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 5: se esperaba sacar los dos casi 1.0 y dejar { 0.3, 1.001 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SSecRealdDestruir ( &p_secRes );
		/* Positividad con tolerancia: un 1e-9 cuenta como cero. */
		SSecRealdVaciar ( p_secObj );
		SSecRealdInsertar ( p_secObj, 2.0 );
		SSecRealdInsertar ( p_secObj, 1e-9 );
		if ( ( SSecRealdDefinidaPositiva ( p_secObj ) != 0 ) || ( SSecRealdSemidefinidaPositiva ( p_secObj ) != 1 ) )
		{
			printf( "Error caso 6: con { 2.0, 1e-9 } se esperaba semidefinida y no definida\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear las secuencias o las listas\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SSecRealdDestruir ( &p_secObj );
	SSecRealdDestruir ( &p_secTres );
	SSecRealdDestruir ( &p_secUno );
	SLisRealdDestruir ( &p_lisTres );
	SLisRealdDestruir ( &p_lisUno );
	return ( iRes );
}

/* CrearDesdeLista copia; Secuencia y Lista dan lo de dentro. Repetidos con
   BuscarPrimero / BuscarSiguiente y Repeticiones. */
static int TestSSecRealdBuscarSiguiente01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SSecRealdBuscarSiguiente 01:\n" );

	double dVal [ 6 ] = { 20.5, 10.5, 20.5, 30.5, 20.5, 40.5 };
	SListaRealesDobles * p_lisVal = CrearLista ( dVal, 6 );
	SSecuenciaRealesDobles * p_secObj = NULL;
	if ( ES_VALIDO ( p_lisVal ) )
	{
		p_secObj = SSecRealdCrearDesdeLista ( p_lisVal );
		/* Son copias: vaciar la lista no toca la secuencia. */
		SLisRealdVaciar ( p_lisVal );
		if ( VerificarSec ( p_secObj, dVal, 6 ) != BOOL_VAL_CIERTO )
		{
			printf( "Error caso 1: la secuencia deberia tener sus propias copias de los 6\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_NULO ( SSecRealdSecuencia ( p_secObj ) ) ||
			 ( SSecRealdLista ( p_secObj ) != SSecLista ( SSecRealdSecuencia ( p_secObj ) ) ) ||
			 ( SLisNumElementos ( SSecRealdLista ( p_secObj ) ) != 6 ) )
		{
			printf( "Error caso 2: Secuencia y Lista deberian dar la secuencia interna y su lista\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SSecRealdBuscarPrimero ( p_secObj, 20.5 ) != 0 ) ||
			 ( SSecRealdBuscarSiguiente ( p_secObj, 20.5, 0 ) != 2 ) ||
			 ( SSecRealdBuscarSiguiente ( p_secObj, 20.5, 2 ) != 4 ) ||
			 ( SSecRealdBuscarSiguiente ( p_secObj, 20.5, 4 ) != -1 ) ||
			 ( SSecRealdBuscarSiguiente ( p_secObj, 20.5, 1 ) != 2 ) ||
			 ( SSecRealdBuscarSiguiente ( p_secObj, 20.5, -2 ) != -1 ) ||
			 ( SSecRealdBuscar ( p_secObj, 40.5 ) != 5 ) )
		{
			printf( "Error caso 3: el 20.5 deberia estar en 0, 2 y 4, y el 40.5 en la 5\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SSecRealdRepeticiones ( p_secObj, 20.5 ) != 3 ) ||
			 ( SSecRealdRepeticiones ( p_secObj, 99.5 ) != 0 ) ||
			 ( SSecRealdBuscar ( p_secObj, 99.5 ) != -1 ) )
		{
			printf( "Error caso 4: el 20.5 deberia estar 3 veces y el 99.5 ninguna\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( SSecRealdCrearDesdeLista ( NULL ) ) || ES_VALIDO ( SSecRealdSecuencia ( NULL ) ) ||
			 ES_VALIDO ( SSecRealdLista ( NULL ) ) || ( SSecRealdRepeticiones ( NULL, 20.5 ) != 0 ) ||
			 ( SSecRealdBuscarSiguiente ( NULL, 20.5, -1 ) != -1 ) || ( SSecRealdBuscar ( NULL, 20.5 ) != -1 ) )
		{
			printf( "Error caso 5: con un nulo se esperaba nulo, 0 al contar y -1 al buscar\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la lista\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisRealdDestruir ( &p_lisVal );
	SSecRealdDestruir ( &p_secObj );
	return ( iRes );
}

/* ListaReald da una lista con COPIAS: cambiarla no toca la secuencia. */
static int TestSSecRealdListaReald01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SSecRealdListaReald 01:\n" );

	double dV [ 3 ] = { 5.5, 1.5, 5.5 };
	double dEsp [ 4 ] = { 5.5, 1.5, 5.5, 8.5 };
	SSecuenciaRealesDobles * p_secObj = CrearSec ( dV, 3 );
	SListaRealesDobles * p_lisRes = NULL;
	if ( ES_VALIDO ( p_secObj ) )
	{
		p_lisRes = SSecRealdListaReald ( p_secObj );
		if ( VerificarLista ( p_lisRes, dV, 3 ) != BOOL_VAL_CIERTO )
		{
			printf( "Error caso 1: la lista deberia ser { 5.5, 1.5, 5.5 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisRealdInsertarAlFinal ( p_lisRes, 8.5 ) != 1 ) ||
			 ( VerificarLista ( p_lisRes, dEsp, 4 ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarSec ( p_secObj, dV, 3 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 2: insertar en la lista no deberia tocar la secuencia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( SSecRealdListaReald ( NULL ) ) )
		{
			printf( "Error caso 3: con una secuencia nula se esperaba nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la secuencia\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisRealdDestruir ( &p_lisRes );
	SSecRealdDestruir ( &p_secObj );
	return ( iRes );
}

/* Pertenencia; Concatenar copia, Eliminar destruye todas las apariciones y
   Extraer mueve. */
static int TestSSecRealdOperacionesListas01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SSecRealdOperacionesListas 01:\n" );

	double dVal [ 5 ] = { 1.5, 2.5, 3.5, 2.5, 4.5 };
	double d29 [ 2 ] = { 2.5, 9.5 };
	double d43 [ 2 ] = { 4.5, 3.5 };
	double d9 [ 1 ] = { 9.5 };
	double d1 [ 1 ] = { 1.5 };
	SSecuenciaRealesDobles * p_secObj = CrearSec ( dVal, 5 );
	SSecuenciaRealesDobles * p_sec29 = CrearSec ( d29, 2 );
	SSecuenciaRealesDobles * p_sec9 = CrearSec ( d9, 1 );
	SListaRealesDobles * p_lis43 = CrearLista ( d43, 2 );
	SListaRealesDobles * p_lis9 = CrearLista ( d9, 1 );
	SListaRealesDobles * p_lis1 = CrearLista ( d1, 1 );
	SSecuenciaRealesDobles * p_secRes = NULL;
	if ( ES_VALIDO ( p_secObj ) && ES_VALIDO ( p_sec29 ) && ES_VALIDO ( p_sec9 ) && ES_VALIDO ( p_lis43 ) &&
		 ES_VALIDO ( p_lis9 ) && ES_VALIDO ( p_lis1 ) )
	{
		if ( ( SSecRealdExistenTodos ( p_secObj, p_sec29 ) != 0 ) || ( SSecRealdExisteAlguno ( p_secObj, p_sec29 ) != 1 ) ||
			 ( SSecRealdExistenTodosLista ( p_secObj, p_lis43 ) != 1 ) || ( SSecRealdExisteAlgunoLista ( p_secObj, p_lis9 ) != 0 ) )
		{
			printf( "Error caso 1: se esperaba 0, 1, 1 y 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Concatenar copia: la lista y la otra secuencia no cambian. */
		double dEsp2 [ 9 ] = { 1.5, 2.5, 3.5, 2.5, 4.5, 4.5, 3.5, 2.5, 9.5 };
		if ( ( SSecRealdConcatenarLista ( p_secObj, p_lis43 ) != 1 ) ||
			 ( SSecRealdConcatenar ( p_secObj, p_sec29 ) != 1 ) ||
			 ( VerificarSec ( p_secObj, dEsp2, 9 ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarLista ( p_lis43, d43, 2 ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarSec ( p_sec29, d29, 2 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 2: se esperaban copias al final y los valores sin tocar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Eliminar quita todas las apariciones. */
		double dEsp3 [ 4 ] = { 1.5, 2.5, 2.5, 2.5 };
		if ( ( SSecRealdEliminarLista ( p_secObj, p_lis43 ) != 1 ) ||
			 ( SSecRealdEliminarSecuencia ( p_secObj, p_sec9 ) != 1 ) ||
			 ( VerificarSec ( p_secObj, dEsp3, 4 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 3: deberia quedar { 1.5, 2.5, 2.5, 2.5 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Extraer mueve, todas las apariciones de cada valor. */
		double dEsp4 [ 3 ] = { 2.5, 2.5, 2.5 };
		p_secRes = SSecRealdExtraerLista ( p_secObj, p_lis1 );
		if ( ( VerificarSec ( p_secRes, d1, 1 ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarSec ( p_secObj, dEsp4, 3 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 4: se esperaba sacar el 1.5 y dejar { 2.5, 2.5, 2.5 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SSecRealdDestruir ( &p_secRes );
		p_secRes = SSecRealdExtraerSecuencia ( p_secObj, p_sec29 );
		if ( ( VerificarSec ( p_secRes, dEsp4, 3 ) != BOOL_VAL_CIERTO ) ||
			 ( SSecRealdNumElementos ( p_secObj ) != 0 ) )
		{
			printf( "Error caso 5: se esperaba sacar los tres 2.5 y dejarla vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SSecRealdDestruir ( &p_secRes );
		if ( ( SSecRealdExistenTodos ( NULL, p_sec29 ) != 0 ) || ( SSecRealdExisteAlgunoLista ( p_sec29, NULL ) != 0 ) ||
			 ( SSecRealdConcatenarLista ( p_sec29, NULL ) != 0 ) || ( SSecRealdConcatenar ( NULL, p_sec9 ) != 0 ) ||
			 ( SSecRealdConcatenar ( p_sec29, p_sec29 ) != 0 ) ||
			 ( SSecRealdEliminarSecuencia ( p_sec29, p_sec29 ) != 0 ) || ( SSecRealdEliminarLista ( NULL, p_lis9 ) != 0 ) ||
			 ES_VALIDO ( SSecRealdExtraerSecuencia ( p_sec29, p_sec29 ) ) ||
			 ES_VALIDO ( SSecRealdExtraerLista ( p_sec29, NULL ) ) ||
			 ( VerificarSec ( p_sec29, d29, 2 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 6: con nulos o la misma secuencia se esperaba 0 o nulo sin cambios\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear las secuencias o las listas\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SSecRealdDestruir ( &p_secObj );
	SSecRealdDestruir ( &p_sec29 );
	SSecRealdDestruir ( &p_sec9 );
	SLisRealdDestruir ( &p_lis43 );
	SLisRealdDestruir ( &p_lis9 );
	SLisRealdDestruir ( &p_lis1 );
	ErrLimpiar ();
	return ( iRes );
}

/* Union es concatenacion; Interseccion y Diferencia, en el orden de V1. Las
   tres con copias, sin tocar las de entrada. */
static int TestSSecRealdUnion01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SSecRealdUnion 01:\n" );

	double dV1 [ 4 ] = { 1.5, 2.5, 3.5, 4.5 };
	double dV2 [ 3 ] = { 4.5, 2.5, 5.5 };
	double dEspU [ 7 ] = { 1.5, 2.5, 3.5, 4.5, 4.5, 2.5, 5.5 };
	double dEspI [ 2 ] = { 2.5, 4.5 };
	double dEspD [ 2 ] = { 1.5, 3.5 };
	SSecuenciaRealesDobles * p_sec1 = CrearSec ( dV1, 4 );
	SSecuenciaRealesDobles * p_sec2 = CrearSec ( dV2, 3 );
	SListaRealesDobles * p_lis2 = CrearLista ( dV2, 3 );
	SSecuenciaRealesDobles * p_secU = NULL;
	SSecuenciaRealesDobles * p_secI = NULL;
	SSecuenciaRealesDobles * p_secD = NULL;
	SSecuenciaRealesDobles * p_secUL = NULL;
	SSecuenciaRealesDobles * p_secIL = NULL;
	SSecuenciaRealesDobles * p_secDL = NULL;
	if ( ES_VALIDO ( p_sec1 ) && ES_VALIDO ( p_sec2 ) && ES_VALIDO ( p_lis2 ) )
	{
		p_secU = SSecRealdUnion ( p_sec1, p_sec2 );
		p_secI = SSecRealdInterseccion ( p_sec1, p_sec2 );
		p_secD = SSecRealdDiferencia ( p_sec1, p_sec2 );
		if ( ( VerificarSec ( p_secU, dEspU, 7 ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarSec ( p_secI, dEspI, 2 ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarSec ( p_secD, dEspD, 2 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 1: con secuencias se esperaba la concatenacion, { 2.5, 4.5 } y { 1.5, 3.5 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		p_secUL = SSecRealdUnionLista ( p_sec1, p_lis2 );
		p_secIL = SSecRealdInterseccionLista ( p_sec1, p_lis2 );
		p_secDL = SSecRealdDiferenciaLista ( p_sec1, p_lis2 );
		if ( ( VerificarSec ( p_secUL, dEspU, 7 ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarSec ( p_secIL, dEspI, 2 ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarSec ( p_secDL, dEspD, 2 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 2: con listas se esperaba la concatenacion, { 2.5, 4.5 } y { 1.5, 3.5 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( VerificarSec ( p_sec1, dV1, 4 ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarSec ( p_sec2, dV2, 3 ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarLista ( p_lis2, dV2, 3 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 3: las de entrada no deberian cambiar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( SSecRealdUnion ( p_sec1, NULL ) ) || ES_VALIDO ( SSecRealdInterseccion ( NULL, p_sec2 ) ) ||
			 ES_VALIDO ( SSecRealdDiferencia ( p_sec1, NULL ) ) || ES_VALIDO ( SSecRealdUnionLista ( NULL, p_lis2 ) ) ||
			 ES_VALIDO ( SSecRealdInterseccionLista ( p_sec1, NULL ) ) || ES_VALIDO ( SSecRealdDiferenciaLista ( NULL, p_lis2 ) ) )
		{
			printf( "Error caso 4: con nulos se esperaba nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear las secuencias o la lista\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SSecRealdDestruir ( &p_secU );
	SSecRealdDestruir ( &p_secI );
	SSecRealdDestruir ( &p_secD );
	SSecRealdDestruir ( &p_secUL );
	SSecRealdDestruir ( &p_secIL );
	SSecRealdDestruir ( &p_secDL );
	SSecRealdDestruir ( &p_sec1 );
	SSecRealdDestruir ( &p_sec2 );
	SLisRealdDestruir ( &p_lis2 );
	ErrLimpiar ();
	return ( iRes );
}

/* Secuencia con el numero de valores pedido, en orden; 0 valores dan una
   secuencia vacia, y el vector nulo o un numero negativo, nulo. */
static int TestSSecRealdCrearDesdeVector01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SSecRealdCrearDesdeVector 01:\n" );

	double dVal [ 4 ] = { 0.0, -DBL_MAX, DBL_MAX, -5.25 };
	SSecuenciaRealesDobles * p_secObj = SSecRealdCrearDesdeVector ( dVal, 4 );
	if ( VerificarSec ( p_secObj, dVal, 4 ) != BOOL_VAL_CIERTO )
	{
		printf( "Error caso 1: se esperaba { 0, -DBL_MAX, DBL_MAX, -5.25 }\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SSecuenciaRealesDobles * p_secParcial = SSecRealdCrearDesdeVector ( dVal, 2 );
	if ( VerificarSec ( p_secParcial, dVal, 2 ) != BOOL_VAL_CIERTO )
	{
		printf( "Error caso 2: con 2 valores se esperaban los dos primeros\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SSecuenciaRealesDobles * p_secVacia = SSecRealdCrearDesdeVector ( dVal, 0 );
	if ( ES_NULO ( p_secVacia ) || ( SSecRealdEsValida ( p_secVacia ) != 1 ) ||
		 ( SSecRealdNumElementos ( p_secVacia ) != 0 ) )
	{
		printf( "Error caso 3: con 0 valores se esperaba una secuencia vacia\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( SSecRealdCrearDesdeVector ( NULL, 2 ) ) || ES_VALIDO ( SSecRealdCrearDesdeVector ( dVal, -1 ) ) )
	{
		printf( "Error caso 4: con el vector nulo o un numero negativo se esperaba nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SSecRealdDestruir ( &p_secObj );
	SSecRealdDestruir ( &p_secParcial );
	SSecRealdDestruir ( &p_secVacia );
	return ( iRes );
}

static double SiguienteValor ( int * p_iCont )
{
	*p_iCont = *p_iCont + 1;
	return ( *p_iCont + 0.5 );
}

/* Cualquier numero de valores, el 0 incluido, sin marca de fin; cada
   argumento se evalua una sola vez. */
static int TestSSecRealdCrearConValores01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SSecRealdCrearConValores 01:\n" );

	double dVal [ 5 ] = { 5.5, 0.0, 7.0, -3.25, 0.0 };
	SSecuenciaRealesDobles * p_secObj = SSecRealdCrearConValores ( 5.5, 0, 7, -3.25, 0.0 );
	if ( VerificarSec ( p_secObj, dVal, 5 ) != BOOL_VAL_CIERTO )
	{
		printf( "Error caso 1: se esperaba { 5.5, 0, 7, -3.25, 0 }\n" );
		iRes = BOOL_VAL_FALSO;
	}
	double dCero [ 1 ] = { 0.0 };
	SSecuenciaRealesDobles * p_secCero = SSecRealdCrearConValores ( 0.0 );
	if ( VerificarSec ( p_secCero, dCero, 1 ) != BOOL_VAL_CIERTO )
	{
		printf( "Error caso 2: se esperaba { 0 }\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* El orden en que se evaluan los inicializadores no esta fijado: se
	   comprueba el numero de llamadas y que esten los tres valores. */
	int iCont = 0;
	SSecuenciaRealesDobles * p_secLlamadas = SSecRealdCrearConValores ( SiguienteValor ( &iCont ), SiguienteValor ( &iCont ), SiguienteValor ( &iCont ) );
	if ( iCont != 3 )
	{
		printf( "Error caso 3: se esperaban 3 llamadas\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ( SSecRealdNumElementos ( p_secLlamadas ) != 3 ) || ( SSecRealdExiste ( p_secLlamadas, 1.5 ) != 1 ) ||
		 ( SSecRealdExiste ( p_secLlamadas, 2.5 ) != 1 ) || ( SSecRealdExiste ( p_secLlamadas, 3.5 ) != 1 ) )
	{
		printf( "Error caso 4: se esperaban los valores 1.5, 2.5 y 3.5\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SSecRealdDestruir ( &p_secObj );
	SSecRealdDestruir ( &p_secCero );
	SSecRealdDestruir ( &p_secLlamadas );
	return ( iRes );
}



int TestSSecuenciaRealesDobles ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SSecuenciaRealesDobles]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSSecRealdCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSSecRealdInsertar01 () == BOOL_VAL_CIERTO ) &&
			( TestSSecRealdConjunto01 () == BOOL_VAL_CIERTO ) &&
			( TestSSecRealdTolerancia01 () == BOOL_VAL_CIERTO ) &&
			( TestSSecRealdBuscarSiguiente01 () == BOOL_VAL_CIERTO ) &&
			( TestSSecRealdListaReald01 () == BOOL_VAL_CIERTO ) &&
			( TestSSecRealdOperacionesListas01 () == BOOL_VAL_CIERTO ) &&
			( TestSSecRealdUnion01 () == BOOL_VAL_CIERTO ) &&
			( TestSSecRealdCrearDesdeVector01 () == BOOL_VAL_CIERTO ) &&
			( TestSSecRealdCrearConValores01 () == BOOL_VAL_CIERTO ) )
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
