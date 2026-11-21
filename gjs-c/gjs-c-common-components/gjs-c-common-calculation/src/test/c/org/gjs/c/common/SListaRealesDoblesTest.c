#include "Base.h"

#include "SListaRealesDobles.h"
#include "CalculoOperaciones.h"



/* Recorre la lista comprobando numero y orden de los valores, con la
   igualdad de la libreria. */
static int VerificarContenido ( SListaRealesDobles * p_lisObj, double * p_dEsperados, int iNum )
{
	int iRes = BOOL_VAL_CIERTO;

	if ( SLisRealdNumElementos ( p_lisObj ) != iNum )
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

static SListaRealesDobles * CrearListaReald ( double * p_dValores, int iNum )
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



static int TestSLisRealdCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisRealdCrear 01:\n" );

	SListaRealesDobles * p_lisObj = SLisRealdCrear ();
	if ( ES_NULO ( p_lisObj ) )
	{
		printf( "Error caso 1: no se esperaba nulo al crear\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SLisRealdEsValida ( p_lisObj ) != 1 )
		{
			printf( "Error caso 2: la lista recien creada deberia ser valida\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisRealdEstaVacia ( p_lisObj ) != 1 )
		{
			printf( "Error caso 3: la lista recien creada deberia estar vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisRealdNumElementos ( p_lisObj ) != 0 )
		{
			printf( "Error caso 4: el numero de elementos deberia ser 0: %d\n", SLisRealdNumElementos ( p_lisObj ) );
			iRes = BOOL_VAL_FALSO;
		}
	}
	SLisRealdDestruir ( &p_lisObj );

	if ( ES_VALIDO ( p_lisObj ) )
	{
		printf( "Error caso 5: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSLisRealdInsertar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisRealdInsertar 01:\n" );

	SListaRealesDobles * p_lisObj = SLisRealdCrear ();
	if ( ES_VALIDO ( p_lisObj ) )
	{
		SLisRealdInsertarAlFinal ( p_lisObj, 10.0 );
		SLisRealdInsertarAlFinal ( p_lisObj, 20.0 );
		SLisRealdInsertarAlFinal ( p_lisObj, 30.0 );

		if ( SLisRealdNumElementos ( p_lisObj ) != 3 )
		{
			printf( "Error caso 1: se esperaban 3 elementos: %d\n", SLisRealdNumElementos ( p_lisObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( MatEsIgual ( SLisRealdElemento ( p_lisObj, 0 ), 10.0 ) != 1 )
		{
			printf( "Error caso 2: el elemento 0 deberia ser 10: %f\n", SLisRealdElemento ( p_lisObj, 0 ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( MatEsIgual ( SLisRealdElemento ( p_lisObj, 2 ), 30.0 ) != 1 )
		{
			printf( "Error caso 3: el elemento 2 deberia ser 30: %f\n", SLisRealdElemento ( p_lisObj, 2 ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisRealdExiste ( p_lisObj, 20.0 ) != 1 )
		{
			printf( "Error caso 4: 20 deberia existir en la lista\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisRealdExiste ( p_lisObj, 99.0 ) != 0 )
		{
			printf( "Error caso 5: 99 no deberia existir en la lista\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisRealdVaciar ( p_lisObj );
		if ( SLisRealdNumElementos ( p_lisObj ) != 0 )
		{
			printf( "Error caso 6: la lista deberia quedar vacia tras vaciarla\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la lista\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisRealdDestruir ( &p_lisObj );
	return ( iRes );
}

static int TestSLisRealdCursor01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisRealdCursor 01:\n" );

	SListaRealesDobles * p_lisObj = SLisRealdCrear ();
	if ( ES_VALIDO ( p_lisObj ) )
	{
		SLisRealdInsertarAlFinal ( p_lisObj, 10.0 );
		SLisRealdInsertarAlFinal ( p_lisObj, 20.0 );

		SLisRealdInicio ( p_lisObj );
		if ( MatEsIgual ( SLisRealdActual ( p_lisObj ), 10.0 ) != 1 )
		{
			printf( "Error caso 1: el actual al inicio deberia ser 10: %f\n", SLisRealdActual ( p_lisObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		SLisRealdSiguiente ( p_lisObj );
		if ( MatEsIgual ( SLisRealdActual ( p_lisObj ), 20.0 ) != 1 )
		{
			printf( "Error caso 2: el siguiente deberia ser 20: %f\n", SLisRealdActual ( p_lisObj ) );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la lista\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisRealdDestruir ( &p_lisObj );
	return ( iRes );
}

/* EstablecerElem cambia el valor de esa posicion y nada mas; fuera de rango
   o con la lista nula da -1. */
static int TestSLisRealdEstablecerElem01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisRealdEstablecerElem 01:\n" );

	double dVal [ 3 ] = { 1.5, 2.5, 3.5 };
	double dEsp [ 3 ] = { 1.5, -7.25, 3.5 };
	SListaRealesDobles * p_lisObj = CrearListaReald ( dVal, 3 );
	if ( ES_VALIDO ( p_lisObj ) )
	{
		if ( ( SLisRealdEstablecerElem ( p_lisObj, 1, -7.25 ) != 1 ) ||
			 ( VerificarContenido ( p_lisObj, dEsp, 3 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 1: se esperaba { 1.5, -7.25, 3.5 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisRealdEstablecerElem ( p_lisObj, 3, 9.0 ) != -1 ) ||
			 ( SLisRealdEstablecerElem ( NULL, 0, 9.0 ) != -1 ) ||
			 ( VerificarContenido ( p_lisObj, dEsp, 3 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 2: fuera de rango o con la lista nula se esperaba -1 sin cambios\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la lista\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisRealdDestruir ( &p_lisObj );
	return ( iRes );
}

/* Funciones de conjunto. Se comprueban contra valores ABSOLUTOS y con
   decimales: un Min o un Max que truncasen a int, o un centinela mal puesto
   ( DBL_MIN es el menor POSITIVO, no el minimo ), compilarian sin avisar. */
static int TestSLisRealdConjunto01 ()
{
	int						iRes = BOOL_VAL_CIERTO;
	double					dMin;
	double					dMax;
	double					dMed;
	SListaRealesDobles *	p_objObj;
	SListaRealesDobles *	p_objUnicos;

	printf( "Test SLisRealdConjunto 01:\n" );

	/* { 5.5, 2.25, 9.75, 5.5 }: cuatro elementos, con el 5.5 repetido. */
	p_objObj = SLisRealdCrear ();
	SLisRealdInsertar ( p_objObj, 5.5 );
	SLisRealdInsertar ( p_objObj, 2.25 );
	SLisRealdInsertar ( p_objObj, 9.75 );
	SLisRealdInsertar ( p_objObj, 5.5 );

	if ( MatEsIgual ( SLisRealdMin ( p_objObj ), 2.25 ) != 1 )
	{
		printf( "Error caso 1: el minimo deberia ser 2.25: %g\n", SLisRealdMin ( p_objObj ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( MatEsIgual ( SLisRealdMax ( p_objObj ), 9.75 ) != 1 )
	{
		printf( "Error caso 2: el maximo deberia ser 9.75: %g\n", SLisRealdMax ( p_objObj ) );
		iRes = BOOL_VAL_FALSO;
	}
	SLisRealdObtenerParametros ( p_objObj, &dMin, &dMax, &dMed );
	if ( ( MatEsIgual ( dMin, 2.25 ) != 1 ) || ( MatEsIgual ( dMax, 9.75 ) != 1 ) )
	{
		printf( "Error caso 3: ObtenerParametros deberia dar 2.25 y 9.75: %g y %g\n", dMin, dMax );
		iRes = BOOL_VAL_FALSO;
	}
	if ( MatEsIgual ( dMed, 5.75 ) != 1 )
	{
		printf( "Error caso 4: la media deberia ser 5.75: %g\n", dMed );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SLisRealdTieneRepetidos ( p_objObj ) != 1 )
	{
		printf( "Error caso 5: deberia detectar repetidos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	p_objUnicos = SLisRealdExtraerUnicos ( p_objObj );
	double dEspUnicos [ 3 ] = { 5.5, 2.25, 9.75 };
	if ( ES_NULO ( p_objUnicos ) || ( VerificarContenido ( p_objUnicos, dEspUnicos, 3 ) != BOOL_VAL_CIERTO ) ||
		 ( SLisRealdTieneRepetidos ( p_objUnicos ) != 0 ) )
	{
		printf( "Error caso 6: los unicos deberian ser { 5.5, 2.25, 9.75 }, en el orden de aparicion\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisRealdDestruir ( &p_objUnicos );
	if ( ( SLisRealdDefinidaPositiva ( p_objObj ) != 1 ) || ( SLisRealdSemidefinidaPositiva ( p_objObj ) != 1 ) )
	{
		printf( "Error caso 7: todos positivos: definida y semidefinida\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisRealdDestruir ( &p_objObj );

	/* Todos negativos: el maximo es negativo. Con DBL_MIN de centinela saldria
	   un positivo minusculo. */
	double dNeg [ 2 ] = { -2.5, -1.5 };
	p_objObj = CrearListaReald ( dNeg, 2 );
	if ( ( MatEsIgual ( SLisRealdMax ( p_objObj ), -1.5 ) != 1 ) || ( MatEsIgual ( SLisRealdMin ( p_objObj ), -2.5 ) != 1 ) )
	{
		printf( "Error caso 8: con { -2.5, -1.5 } se esperaba maximo -1.5 y minimo -2.5: %g y %g\n",
				SLisRealdMax ( p_objObj ), SLisRealdMin ( p_objObj ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ( SLisRealdDefinidaPositiva ( p_objObj ) != 0 ) || ( SLisRealdSemidefinidaPositiva ( p_objObj ) != 0 ) )
	{
		printf( "Error caso 9: con negativos ni definida ni semidefinida\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisRealdDestruir ( &p_objObj );

	/* Lista vacia: ni division por cero ni valores sin inicializar. */
	p_objObj = SLisRealdCrear ();
	dMin = 7.0;
	dMax = 7.0;
	dMed = 7.0;
	SLisRealdObtenerParametros ( p_objObj, &dMin, &dMax, &dMed );
	if ( ( MatEsIgual ( dMed, 0.0 ) != 1 ) || ( dMin != DBL_MAX ) || ( dMax != -DBL_MAX ) )
	{
		printf( "Error caso 10: con 0 elementos se esperaba media 0, minimo DBL_MAX y maximo -DBL_MAX\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SLisRealdTieneRepetidos ( p_objObj ) != 0 )
	{
		printf( "Error caso 11: una coleccion vacia no tiene repetidos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisRealdDestruir ( &p_objObj );

	/* Objeto invalido: ni cuelga ni inventa. */
	if ( ( MatEsIgual ( SLisRealdMin ( NULL ), 0.0 ) != 1 ) || ES_VALIDO ( SLisRealdExtraerUnicos ( NULL ) ) )
	{
		printf( "Error caso 12: con objeto nulo se esperaba 0 y nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	ErrLimpiar ();
	return ( iRes );
}

/* La igualdad entre reales es la de MatEsIgual en TODAS las funciones: lo que
   encuentra Existe lo encuentran tambien ExistenTodos, Repeticiones, Eliminar
   o Interseccion. 0.1 + 0.2 no es 0.3 en binario, pero es igual con la
   tolerancia; 1.0 y 1.001 no lo son. */
static int TestSLisRealdTolerancia01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisRealdTolerancia 01:\n" );

	double dSuma = 0.1 + 0.2;
	double dVal [ 4 ] = { dSuma, 1.0, 1.0 + 1e-9, 1.001 };
	double dTres [ 1 ] = { 0.3 };
	double dUno [ 1 ] = { 1.0 };
	SListaRealesDobles * p_lisObj = CrearListaReald ( dVal, 4 );
	SListaRealesDobles * p_lisTres = CrearListaReald ( dTres, 1 );
	SListaRealesDobles * p_lisUno = CrearListaReald ( dUno, 1 );
	SListaRealesDobles * p_lisRes = NULL;
	if ( ES_VALIDO ( p_lisObj ) && ES_VALIDO ( p_lisTres ) && ES_VALIDO ( p_lisUno ) )
	{
		if ( dSuma == 0.3 )
		{
			printf( "Aviso: en esta plataforma 0.1 + 0.2 es exactamente 0.3; el caso 1 no prueba nada\n" );
		}
		if ( ( SLisRealdExiste ( p_lisObj, 0.3 ) != 1 ) || ( SLisRealdBuscar ( p_lisObj, 0.3 ) != 0 ) ||
			 ( SLisRealdExistenTodos ( p_lisObj, p_lisTres ) != 1 ) || ( SLisRealdExisteAlguno ( p_lisObj, p_lisTres ) != 1 ) )
		{
			printf( "Error caso 1: 0.3 deberia encontrarse igual con Existe, Buscar, ExistenTodos y ExisteAlguno\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* 1.0 y 1.0 + 1e-9 son el mismo valor; 1.001 no. */
		if ( ( SLisRealdRepeticiones ( p_lisObj, 1.0 ) != 2 ) || ( SLisRealdBuscarSiguiente ( p_lisObj, 1.0, 1 ) != 2 ) ||
			 ( SLisRealdBuscarSiguiente ( p_lisObj, 1.0, 2 ) != -1 ) || ( SLisRealdRepeticiones ( p_lisObj, 1.001 ) != 1 ) )
		{
			printf( "Error caso 2: el 1.0 deberia estar 2 veces ( en 1 y 2 ) y el 1.001 una\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisRealdTieneRepetidos ( p_lisObj ) != 1 )
		{
			printf( "Error caso 3: 1.0 y 1.0 + 1e-9 son repetidos\n" );
			iRes = BOOL_VAL_FALSO;
		}
		p_lisRes = SLisRealdExtraerUnicos ( p_lisObj );
		double dEspUnicos [ 3 ] = { 0.3, 1.0, 1.001 };
		if ( ES_NULO ( p_lisRes ) || ( VerificarContenido ( p_lisRes, dEspUnicos, 3 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 4: los unicos deberian ser { 0.3, 1.0, 1.001 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisRealdDestruir ( &p_lisRes );

		/* Interseccion y Diferencia con la misma igualdad. */
		p_lisRes = SLisRealdInterseccion ( p_lisObj, p_lisUno );
		double dEspI [ 2 ] = { 1.0, 1.0 };
		if ( ES_NULO ( p_lisRes ) || ( VerificarContenido ( p_lisRes, dEspI, 2 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 5: la interseccion con { 1.0 } deberia dar los dos casi 1.0\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisRealdDestruir ( &p_lisRes );
		p_lisRes = SLisRealdDiferencia ( p_lisObj, p_lisUno );
		double dEspD [ 2 ] = { 0.3, 1.001 };
		if ( ES_NULO ( p_lisRes ) || ( VerificarContenido ( p_lisRes, dEspD, 2 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 6: la diferencia con { 1.0 } deberia ser { 0.3, 1.001 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisRealdDestruir ( &p_lisRes );

		/* Eliminar se lleva los dos casi 1.0 y deja el 1.001. */
		if ( ( SLisRealdEliminarLista ( p_lisObj, p_lisUno ) != 1 ) ||
			 ( VerificarContenido ( p_lisObj, dEspD, 2 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 7: tras eliminar el 1.0 deberia quedar { 0.3, 1.001 }\n" );
			iRes = BOOL_VAL_FALSO;
		}

		/* Positividad con tolerancia: un 1e-9 cuenta como cero. */
		SLisRealdVaciar ( p_lisObj );
		SLisRealdInsertarAlFinal ( p_lisObj, 2.0 );
		SLisRealdInsertarAlFinal ( p_lisObj, 1e-9 );
		if ( ( SLisRealdDefinidaPositiva ( p_lisObj ) != 0 ) || ( SLisRealdSemidefinidaPositiva ( p_lisObj ) != 1 ) )
		{
			printf( "Error caso 8: con { 2.0, 1e-9 } se esperaba semidefinida y no definida\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisRealdEstablecerElem ( p_lisObj, 1, -1e-9 );
		if ( SLisRealdSemidefinidaPositiva ( p_lisObj ) != 1 )
		{
			printf( "Error caso 9: un -1e-9 tambien cuenta como cero: semidefinida\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear las listas\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisRealdDestruir ( &p_lisObj );
	SLisRealdDestruir ( &p_lisTres );
	SLisRealdDestruir ( &p_lisUno );
	return ( iRes );
}

/* Las de orden, que solo tienen las listas. */
static int TestSLisRealdOrden01 ()
{
	int						iRes = BOOL_VAL_CIERTO;
	SListaRealesDobles *	p_lisObj;
	SListaRealesDobles *	p_lisOrd;

	printf( "Test SLisRealdOrden 01:\n" );

	double dVal [ 4 ] = { 5.5, 2.25, 9.75, 5.5 };
	double dEsp [ 4 ] = { 2.25, 5.5, 5.5, 9.75 };
	p_lisObj = CrearListaReald ( dVal, 4 );

	if ( SLisRealdEstaOrdenada ( p_lisObj ) != 0 )
	{
		printf( "Error caso 1: esa lista no esta ordenada\n" );
		iRes = BOOL_VAL_FALSO;
	}
	p_lisOrd = SLisRealdOrdenar ( p_lisObj );
	if ( ES_NULO ( p_lisOrd ) || ( VerificarContenido ( p_lisOrd, dEsp, 4 ) != BOOL_VAL_CIERTO ) ||
		 ( SLisRealdEstaOrdenada ( p_lisOrd ) != 1 ) )
	{
		printf( "Error caso 2: Ordenar deberia dar { 2.25, 5.5, 5.5, 9.75 }\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisRealdDestruir ( &p_lisOrd );
	if ( VerificarContenido ( p_lisObj, dVal, 4 ) != BOOL_VAL_CIERTO )
	{
		printf( "Error caso 3: Ordenar no deberia modificar la lista de entrada\n" );
		iRes = BOOL_VAL_FALSO;
	}

	/* ExtraerUnicosExt ( , 1 ) devuelve los unicos YA ordenados. */
	p_lisOrd = SLisRealdExtraerUnicosExt ( p_lisObj, 1 );
	double dEspUnicos [ 3 ] = { 2.25, 5.5, 9.75 };
	if ( ES_NULO ( p_lisOrd ) || ( VerificarContenido ( p_lisOrd, dEspUnicos, 3 ) != BOOL_VAL_CIERTO ) )
	{
		printf( "Error caso 4: con iOrdenar = 1 se esperaba { 2.25, 5.5, 9.75 }\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisRealdDestruir ( &p_lisOrd );

	/* InsertarOrdenado en una ordenada: al principio, en medio y al final. */
	double dEspIns [ 7 ] = { -1.0, 2.25, 5.5, 5.5, 7.0, 9.75, 12.5 };
	p_lisOrd = SLisRealdOrdenar ( p_lisObj );
	if ( ( SLisRealdInsertarOrdenado ( p_lisOrd, 7.0 ) != 1 ) || ( SLisRealdInsertarOrdenado ( p_lisOrd, -1.0 ) != 1 ) ||
		 ( SLisRealdInsertarOrdenado ( p_lisOrd, 12.5 ) != 1 ) ||
		 ( VerificarContenido ( p_lisOrd, dEspIns, 7 ) != BOOL_VAL_CIERTO ) )
	{
		printf( "Error caso 5: se esperaba { -1, 2.25, 5.5, 5.5, 7, 9.75, 12.5 }\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisRealdDestruir ( &p_lisOrd );

	/* Dos casi iguales en cualquier orden no la desordenan. */
	double dCasi [ 3 ] = { 1.0, 1.0 - 1e-9, 2.0 };
	SListaRealesDobles * p_lisCasi = CrearListaReald ( dCasi, 3 );
	if ( SLisRealdEstaOrdenada ( p_lisCasi ) != 1 )
	{
		printf( "Error caso 6: { 1.0, 1.0 - 1e-9, 2.0 } esta ordenada con la tolerancia\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisRealdDestruir ( &p_lisCasi );
	if ( ( SLisRealdEstaOrdenada ( NULL ) != 0 ) || ES_VALIDO ( SLisRealdOrdenar ( NULL ) ) ||
		 ( SLisRealdInsertarOrdenado ( NULL, 1.0 ) != 0 ) )
	{
		printf( "Error caso 7: con la lista nula se esperaba 0 o nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisRealdDestruir ( &p_lisObj );
	ErrLimpiar ();
	return ( iRes );
}

/* Un valor en la posicion 0 y otro que es el ULTIMO de los valores. */
static int TestSLisRealdExisten01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisRealdExisten 01:\n" );

	double dVal [ 3 ] = { 10.5, 20.5, 30.5 };
	double dV1 [ 2 ] = { 10.5, 30.5 };
	double dV2 [ 2 ] = { 10.5, 99.5 };
	double dV3 [ 2 ] = { 99.5, 30.5 };
	double dV4 [ 2 ] = { 98.5, 99.5 };
	SListaRealesDobles * p_lisObj = CrearListaReald ( dVal, 3 );
	SListaRealesDobles * p_lis1 = CrearListaReald ( dV1, 2 );
	SListaRealesDobles * p_lis2 = CrearListaReald ( dV2, 2 );
	SListaRealesDobles * p_lis3 = CrearListaReald ( dV3, 2 );
	SListaRealesDobles * p_lis4 = CrearListaReald ( dV4, 2 );
	SListaRealesDobles * p_lisVacia = SLisRealdCrear ();
	if ( ES_VALIDO ( p_lisObj ) && ES_VALIDO ( p_lis1 ) && ES_VALIDO ( p_lis2 ) &&
		 ES_VALIDO ( p_lis3 ) && ES_VALIDO ( p_lis4 ) && ES_VALIDO ( p_lisVacia ) )
	{
		if ( SLisRealdExistenTodos ( p_lisObj, p_lis1 ) != 1 )
		{
			printf( "Error caso 1: { 10.5, 30.5 } estan todos\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisRealdExistenTodos ( p_lisObj, p_lis2 ) != 0 )
		{
			printf( "Error caso 2: en { 10.5, 99.5 } falta el 99.5\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisRealdExisteAlguno ( p_lisObj, p_lis2 ) != 1 )
		{
			printf( "Error caso 3: de { 10.5, 99.5 } esta el 10.5, en la posicion 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisRealdExisteAlguno ( p_lisObj, p_lis3 ) != 1 )
		{
			printf( "Error caso 4: de { 99.5, 30.5 } esta el 30.5, el ultimo de los valores\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisRealdExisteAlguno ( p_lisObj, p_lis4 ) != 0 ) ||
			 ( SLisRealdExistenTodos ( p_lisObj, p_lis4 ) != 0 ) )
		{
			printf( "Error caso 5: de { 98.5, 99.5 } no esta ninguno\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisRealdExistenTodos ( p_lisObj, p_lisVacia ) != 1 ) ||
			 ( SLisRealdExisteAlguno ( p_lisObj, p_lisVacia ) != 0 ) )
		{
			printf( "Error caso 6: con valores vacios, Todos da 1 y Alguno 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisRealdExistenTodos ( NULL, p_lis1 ) != 0 ) ||
			 ( SLisRealdExisteAlguno ( p_lisObj, NULL ) != 0 ) )
		{
			printf( "Error caso 7: con listas nulas se esperaba 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear las listas\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisRealdDestruir ( &p_lisObj );
	SLisRealdDestruir ( &p_lis1 );
	SLisRealdDestruir ( &p_lis2 );
	SLisRealdDestruir ( &p_lis3 );
	SLisRealdDestruir ( &p_lis4 );
	SLisRealdDestruir ( &p_lisVacia );
	return ( iRes );
}

static int TestSLisRealdInsertarLista01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisRealdInsertarLista 01:\n" );

	double dDest [ 2 ] = { 1.5, 2.5 };
	double dVal [ 3 ] = { 7.5, 8.5, 9.5 };
	SListaRealesDobles * p_lisObj = CrearListaReald ( dDest, 2 );
	SListaRealesDobles * p_lisVal = CrearListaReald ( dVal, 3 );
	if ( ES_VALIDO ( p_lisObj ) && ES_VALIDO ( p_lisVal ) )
	{
		/* Mueve detras del cursor, en su orden, y deja los valores vacios. */
		SLisRealdMoverA ( p_lisObj, 0 );
		if ( SLisRealdInsertarLista ( p_lisObj, p_lisVal ) != 1 )
		{
			printf( "Error caso 1: se esperaba resultado 1 al insertar la lista\n" );
			iRes = BOOL_VAL_FALSO;
		}
		double dEsp1 [ 5 ] = { 1.5, 7.5, 8.5, 9.5, 2.5 };
		if ( VerificarContenido ( p_lisObj, dEsp1, 5 ) != BOOL_VAL_CIERTO )
		{
			printf( "Error caso 2: se esperaba { 1.5, 7.5, 8.5, 9.5, 2.5 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisRealdEstaVacia ( p_lisVal ) != 1 ) || ( SLisRealdEsValida ( p_lisVal ) != 1 ) )
		{
			printf( "Error caso 3: la lista de valores deberia quedar vacia y valida\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Concatenar va al final, este donde este el cursor. */
		SLisRealdInsertarAlFinal ( p_lisVal, 5.5 );
		SLisRealdInsertarAlFinal ( p_lisVal, 6.5 );
		SLisRealdMoverA ( p_lisObj, 1 );
		if ( SLisRealdConcatenarLista ( p_lisObj, p_lisVal ) != 1 )
		{
			printf( "Error caso 4: se esperaba resultado 1 al concatenar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		double dEsp2 [ 7 ] = { 1.5, 7.5, 8.5, 9.5, 2.5, 5.5, 6.5 };
		if ( ( VerificarContenido ( p_lisObj, dEsp2, 7 ) != BOOL_VAL_CIERTO ) ||
			 ( SLisRealdEstaVacia ( p_lisVal ) != 1 ) )
		{
			printf( "Error caso 5: se esperaba { 1.5, 7.5, 8.5, 9.5, 2.5, 5.5, 6.5 } y los valores vacios\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisRealdInsertarLista ( p_lisObj, NULL ) != 0 ) ||
			 ( SLisRealdConcatenarLista ( NULL, p_lisVal ) != 0 ) ||
			 ( SLisRealdConcatenarLista ( p_lisObj, p_lisObj ) != 0 ) )
		{
			printf( "Error caso 6: con listas nulas o la misma lista se esperaba 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear las listas\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisRealdDestruir ( &p_lisObj );
	SLisRealdDestruir ( &p_lisVal );
	return ( iRes );
}

static int TestSLisRealdListaDup01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisRealdListaDup 01:\n" );

	double dDest [ 2 ] = { 1.5, 2.5 };
	double dVal [ 2 ] = { 7.5, 8.5 };
	SListaRealesDobles * p_lisObj = CrearListaReald ( dDest, 2 );
	SListaRealesDobles * p_lisVal = CrearListaReald ( dVal, 2 );
	if ( ES_VALIDO ( p_lisObj ) && ES_VALIDO ( p_lisVal ) )
	{
		SLisRealdMoverA ( p_lisObj, 0 );
		if ( SLisRealdInsertarListaDup ( p_lisObj, p_lisVal ) != 1 )
		{
			printf( "Error caso 1: se esperaba resultado 1 al insertar copias\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SLisRealdConcatenarListaDup ( p_lisObj, p_lisVal ) != 1 )
		{
			printf( "Error caso 2: se esperaba resultado 1 al concatenar copias\n" );
			iRes = BOOL_VAL_FALSO;
		}
		double dEsp [ 6 ] = { 1.5, 7.5, 8.5, 2.5, 7.5, 8.5 };
		if ( VerificarContenido ( p_lisObj, dEsp, 6 ) != BOOL_VAL_CIERTO )
		{
			printf( "Error caso 3: se esperaba { 1.5, 7.5, 8.5, 2.5, 7.5, 8.5 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Los valores quedan intactos, y son copias: cambiar una no toca el original. */
		SLisRealdEstablecerElem ( p_lisObj, 1, 70.5 );
		if ( VerificarContenido ( p_lisVal, dVal, 2 ) != BOOL_VAL_CIERTO )
		{
			printf( "Error caso 4: los valores deberian seguir { 7.5, 8.5 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisRealdInsertarListaDup ( p_lisObj, NULL ) != 0 ) ||
			 ( SLisRealdConcatenarListaDup ( NULL, p_lisVal ) != 0 ) )
		{
			printf( "Error caso 5: con listas nulas se esperaba 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear las listas\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisRealdDestruir ( &p_lisObj );
	SLisRealdDestruir ( &p_lisVal );
	return ( iRes );
}

static int TestSLisRealdExtraerLista01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisRealdExtraerLista 01:\n" );

	double dVal [ 6 ] = { 20.5, 10.5, 20.5, 30.5, 40.5, 20.5 };
	double dBus [ 4 ] = { 20.5, 40.5, 99.5, 20.5 };
	SListaRealesDobles * p_lisObj = CrearListaReald ( dVal, 6 );
	SListaRealesDobles * p_lisBus = CrearListaReald ( dBus, 4 );
	SListaRealesDobles * p_lisRes = NULL;
	if ( ES_VALIDO ( p_lisObj ) && ES_VALIDO ( p_lisBus ) )
	{
		/* Todas las apariciones de cada valor buscado, en el orden de los
		   buscados: el 20.5 esta tres veces y sale entero con el primero; el 99.5
		   no esta. */
		p_lisRes = SLisRealdExtraerLista ( p_lisObj, p_lisBus );
		double dEspRes [ 4 ] = { 20.5, 20.5, 20.5, 40.5 };
		double dEspObj [ 2 ] = { 10.5, 30.5 };
		if ( ES_NULO ( p_lisRes ) || ( SLisRealdEsValida ( p_lisRes ) != 1 ) ||
			 ( VerificarContenido ( p_lisRes, dEspRes, 4 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 1: se esperaba extraer { 20.5, 20.5, 20.5, 40.5 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( VerificarContenido ( p_lisObj, dEspObj, 2 ) != BOOL_VAL_CIERTO )
		{
			printf( "Error caso 2: en el origen deberia quedar { 10.5, 30.5 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( SLisRealdExtraerLista ( p_lisObj, p_lisObj ) ) ||
			 ES_VALIDO ( SLisRealdExtraerLista ( NULL, p_lisBus ) ) ||
			 ( VerificarContenido ( p_lisObj, dEspObj, 2 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 3: con la misma lista o una nula se esperaba nulo sin cambios\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear las listas\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisRealdDestruir ( &p_lisObj );
	SLisRealdDestruir ( &p_lisBus );
	SLisRealdDestruir ( &p_lisRes );
	return ( iRes );
}

/* Destruye todas las apariciones de cada valor buscado; los valores no cambian. */
static int TestSLisRealdEliminarLista01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisRealdEliminarLista 01:\n" );

	double dVal [ 6 ] = { 20.5, 10.5, 20.5, 30.5, 40.5, 20.5 };
	double dBus [ 4 ] = { 20.5, 40.5, 99.5, 20.5 };
	SListaRealesDobles * p_lisObj = CrearListaReald ( dVal, 6 );
	SListaRealesDobles * p_lisBus = CrearListaReald ( dBus, 4 );
	SListaRealesDobles * p_lisVacia = SLisRealdCrear ();
	if ( ES_VALIDO ( p_lisObj ) && ES_VALIDO ( p_lisBus ) && ES_VALIDO ( p_lisVacia ) )
	{
		if ( SLisRealdEliminarLista ( p_lisObj, p_lisBus ) != 1 )
		{
			printf( "Error caso 1: se esperaba 1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		double dEspObj [ 2 ] = { 10.5, 30.5 };
		if ( VerificarContenido ( p_lisObj, dEspObj, 2 ) != BOOL_VAL_CIERTO )
		{
			printf( "Error caso 2: deberia quedar { 10.5, 30.5 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( VerificarContenido ( p_lisBus, dBus, 4 ) != BOOL_VAL_CIERTO )
		{
			printf( "Error caso 3: los valores no deberian cambiar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Ya no queda ninguno: no hay nada que eliminar, y no es un error. */
		if ( ( SLisRealdEliminarLista ( p_lisObj, p_lisBus ) != 1 ) ||
			 ( SLisRealdEliminarLista ( p_lisObj, p_lisVacia ) != 1 ) ||
			 ( VerificarContenido ( p_lisObj, dEspObj, 2 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 4: sin nada que eliminar se esperaba 1 sin cambios\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisRealdEliminarLista ( p_lisObj, p_lisObj ) != 0 ) ||
			 ( VerificarContenido ( p_lisObj, dEspObj, 2 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 5: con la misma lista se esperaba 0 sin cambios\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisRealdEliminarLista ( p_lisObj, NULL ) != 0 ) || ( SLisRealdEliminarLista ( NULL, p_lisBus ) != 0 ) )
		{
			printf( "Error caso 6: con una lista nula se esperaba 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear las listas\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisRealdDestruir ( &p_lisObj );
	SLisRealdDestruir ( &p_lisBus );
	SLisRealdDestruir ( &p_lisVacia );
	return ( iRes );
}

static int TestSLisRealdOperacionesListas01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisRealdOperacionesListas 01:\n" );

	double dV1 [ 4 ] = { 1.5, 2.5, 3.5, 4.5 };
	double dV2 [ 3 ] = { 4.5, 2.5, 5.5 };
	SListaRealesDobles * p_lis1 = CrearListaReald ( dV1, 4 );
	SListaRealesDobles * p_lis2 = CrearListaReald ( dV2, 3 );
	SListaRealesDobles * p_lisVacia = SLisRealdCrear ();
	if ( ES_VALIDO ( p_lis1 ) && ES_VALIDO ( p_lis2 ) && ES_VALIDO ( p_lisVacia ) )
	{
		/* La union es concatenacion: el 2.5 y el 4.5 salen dos veces. */
		SListaRealesDobles * p_lisRes = SLisRealdUnion ( p_lis1, p_lis2 );
		double dEspU [ 7 ] = { 1.5, 2.5, 3.5, 4.5, 4.5, 2.5, 5.5 };
		if ( ES_NULO ( p_lisRes ) || ( SLisRealdEsValida ( p_lisRes ) != 1 ) ||
			 ( VerificarContenido ( p_lisRes, dEspU, 7 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 1: la union deberia ser { 1.5, 2.5, 3.5, 4.5, 4.5, 2.5, 5.5 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisRealdDestruir ( &p_lisRes );

		/* Interseccion y diferencia, las dos en el orden de V1. */
		p_lisRes = SLisRealdInterseccion ( p_lis1, p_lis2 );
		double dEspI [ 2 ] = { 2.5, 4.5 };
		if ( ES_NULO ( p_lisRes ) || ( VerificarContenido ( p_lisRes, dEspI, 2 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 2: la interseccion deberia ser { 2.5, 4.5 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisRealdDestruir ( &p_lisRes );

		p_lisRes = SLisRealdDiferencia ( p_lis1, p_lis2 );
		double dEspD [ 2 ] = { 1.5, 3.5 };
		if ( ES_NULO ( p_lisRes ) || ( VerificarContenido ( p_lisRes, dEspD, 2 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 3: la diferencia deberia ser { 1.5, 3.5 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisRealdDestruir ( &p_lisRes );

		if ( ( VerificarContenido ( p_lis1, dV1, 4 ) != BOOL_VAL_CIERTO ) ||
			 ( VerificarContenido ( p_lis2, dV2, 3 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 4: las listas de entrada no deberian cambiar\n" );
			iRes = BOOL_VAL_FALSO;
		}

		/* Con una vacia: lista nueva, valida y vacia; no nulo. */
		p_lisRes = SLisRealdInterseccion ( p_lis1, p_lisVacia );
		if ( ES_NULO ( p_lisRes ) || ( SLisRealdEsValida ( p_lisRes ) != 1 ) || ( SLisRealdEstaVacia ( p_lisRes ) != 1 ) )
		{
			printf( "Error caso 5: la interseccion con una vacia deberia ser una lista vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisRealdDestruir ( &p_lisRes );
		p_lisRes = SLisRealdDiferencia ( p_lis1, p_lisVacia );
		if ( ES_NULO ( p_lisRes ) || ( VerificarContenido ( p_lisRes, dV1, 4 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 6: V1 menos una vacia deberia ser V1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisRealdDestruir ( &p_lisRes );

		if ( ES_VALIDO ( SLisRealdUnion ( p_lis1, NULL ) ) ||
			 ES_VALIDO ( SLisRealdInterseccion ( NULL, p_lis2 ) ) ||
			 ES_VALIDO ( SLisRealdDiferencia ( p_lis1, NULL ) ) )
		{
			printf( "Error caso 7: con listas nulas se esperaba nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear las listas\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisRealdDestruir ( &p_lis1 );
	SLisRealdDestruir ( &p_lis2 );
	SLisRealdDestruir ( &p_lisVacia );
	ErrLimpiar ();
	return ( iRes );
}

/* La copia tiene los mismos valores en el mismo orden, con los extremos del
   tipo; cambiarla no toca el original, ni se mueve su cursor. */
static int TestSLisRealdDuplicar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisRealdDuplicar 01:\n" );

	double dVal [ 4 ] = { 0.0, -DBL_MAX, DBL_MAX, -5.25 };
	SListaRealesDobles * p_lisObj = CrearListaReald ( dVal, 4 );
	SListaRealesDobles * p_lisVacia = SLisRealdCrear ();
	SListaRealesDobles * p_lisDup = NULL;
	SListaRealesDobles * p_lisDupVacia = NULL;
	if ( ES_VALIDO ( p_lisObj ) && ES_VALIDO ( p_lisVacia ) )
	{
		SLisRealdMoverA ( p_lisObj, 1 );
		p_lisDup = SLisRealdDuplicar ( p_lisObj );
		if ( SLisRealdPosicion ( p_lisObj ) != 1 )
		{
			printf( "Error caso 1: el cursor del original deberia seguir en 1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_NULO ( p_lisDup ) || ( p_lisDup == p_lisObj ) ||
			 ( VerificarContenido ( p_lisDup, dVal, 4 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 2: la copia deberia ser otra lista con { 0, -DBL_MAX, DBL_MAX, -5.25 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SLisRealdEstablecerElem ( p_lisDup, 2, 99.5 );
		if ( VerificarContenido ( p_lisObj, dVal, 4 ) != BOOL_VAL_CIERTO )
		{
			printf( "Error caso 3: cambiar la copia no deberia tocar el original\n" );
			iRes = BOOL_VAL_FALSO;
		}
		p_lisDupVacia = SLisRealdDuplicar ( p_lisVacia );
		if ( ES_NULO ( p_lisDupVacia ) || ( SLisRealdEsValida ( p_lisDupVacia ) != 1 ) ||
			 ( SLisRealdNumElementos ( p_lisDupVacia ) != 0 ) )
		{
			printf( "Error caso 4: la copia de una vacia deberia ser otra vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( SLisRealdDuplicar ( NULL ) ) )
		{
			printf( "Error caso 5: con una lista nula se esperaba nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear las listas\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisRealdDestruir ( &p_lisObj );
	SLisRealdDestruir ( &p_lisVacia );
	SLisRealdDestruir ( &p_lisDup );
	SLisRealdDestruir ( &p_lisDupVacia );
	return ( iRes );
}

/* Copia el numero de valores pedido, en orden y con el cursor al inicio; 0
   valores dan una lista vacia, y el vector nulo o un numero negativo, nulo. */
static int TestSLisRealdCrearDesdeVector01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisRealdCrearDesdeVector 01:\n" );

	double dVal [ 4 ] = { 0.0, -DBL_MAX, DBL_MAX, -5.25 };
	SListaRealesDobles * p_lisObj = SLisRealdCrearDesdeVector ( dVal, 4 );
	if ( ES_NULO ( p_lisObj ) || ( VerificarContenido ( p_lisObj, dVal, 4 ) != BOOL_VAL_CIERTO ) )
	{
		printf( "Error caso 1: se esperaba { 0, -DBL_MAX, DBL_MAX, -5.25 }\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SLisRealdPosicion ( p_lisObj ) != 0 )
	{
		printf( "Error caso 2: el cursor deberia estar en 0: %d\n", SLisRealdPosicion ( p_lisObj ) );
		iRes = BOOL_VAL_FALSO;
	}
	SListaRealesDobles * p_lisParcial = SLisRealdCrearDesdeVector ( dVal, 2 );
	if ( ES_NULO ( p_lisParcial ) || ( VerificarContenido ( p_lisParcial, dVal, 2 ) != BOOL_VAL_CIERTO ) )
	{
		printf( "Error caso 3: con 2 valores se esperaba { 0, -DBL_MAX }\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SListaRealesDobles * p_lisVacia = SLisRealdCrearDesdeVector ( dVal, 0 );
	if ( ES_NULO ( p_lisVacia ) || ( SLisRealdEsValida ( p_lisVacia ) != 1 ) ||
		 ( SLisRealdNumElementos ( p_lisVacia ) != 0 ) )
	{
		printf( "Error caso 4: con 0 valores se esperaba una lista vacia\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( SLisRealdCrearDesdeVector ( NULL, 2 ) ) )
	{
		printf( "Error caso 5: con el vector nulo se esperaba nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( SLisRealdCrearDesdeVector ( dVal, -1 ) ) )
	{
		printf( "Error caso 6: con un numero negativo se esperaba nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisRealdDestruir ( &p_lisObj );
	SLisRealdDestruir ( &p_lisParcial );
	SLisRealdDestruir ( &p_lisVacia );
	return ( iRes );
}

static double Siguiente ( int * p_iCont )
{
	*p_iCont = *p_iCont + 1;
	return ( *p_iCont + 0.5 );
}

/* Cualquier numero de valores, el 0 incluido, sin marca de fin; cada
   argumento se evalua una sola vez. Un entero pasado a la macro se convierte
   a double. */
static int TestSLisRealdCrearConValores01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisRealdCrearConValores 01:\n" );

	double dVal [ 5 ] = { 5.5, 0.0, 7.0, -3.25, 0.0 };
	SListaRealesDobles * p_lisObj = SLisRealdCrearConValores ( 5.5, 0, 7, -3.25, 0.0 );
	if ( ES_NULO ( p_lisObj ) || ( VerificarContenido ( p_lisObj, dVal, 5 ) != BOOL_VAL_CIERTO ) )
	{
		printf( "Error caso 1: se esperaba { 5.5, 0, 7, -3.25, 0 }\n" );
		iRes = BOOL_VAL_FALSO;
	}
	double dCero [ 1 ] = { 0.0 };
	SListaRealesDobles * p_lisCero = SLisRealdCrearConValores ( 0.0 );
	if ( ES_NULO ( p_lisCero ) || ( VerificarContenido ( p_lisCero, dCero, 1 ) != BOOL_VAL_CIERTO ) )
	{
		printf( "Error caso 2: se esperaba { 0 }\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* El orden en que se evaluan los inicializadores no esta fijado: se
	   comprueba el numero de llamadas y que esten los tres valores. */
	int iCont = 0;
	SListaRealesDobles * p_lisLlamadas = SLisRealdCrearConValores ( Siguiente ( &iCont ), Siguiente ( &iCont ), Siguiente ( &iCont ) );
	if ( iCont != 3 )
	{
		printf( "Error caso 3: se esperaban 3 llamadas: %d\n", iCont );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ( SLisRealdNumElementos ( p_lisLlamadas ) != 3 ) || ( SLisRealdExiste ( p_lisLlamadas, 1.5 ) != 1 ) ||
		 ( SLisRealdExiste ( p_lisLlamadas, 2.5 ) != 1 ) || ( SLisRealdExiste ( p_lisLlamadas, 3.5 ) != 1 ) )
	{
		printf( "Error caso 4: se esperaban los valores 1.5, 2.5 y 3.5\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisRealdDestruir ( &p_lisObj );
	SLisRealdDestruir ( &p_lisCero );
	SLisRealdDestruir ( &p_lisLlamadas );
	return ( iRes );
}

/* Repetidos con BuscarPrimero / BuscarSiguiente y Repeticiones. */
static int TestSLisRealdRepeticiones01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisRealdRepeticiones 01:\n" );

	double dVal [ 6 ] = { 20.5, 10.5, 20.5, 30.5, 20.5, 40.5 };
	SListaRealesDobles * p_lisObj = CrearListaReald ( dVal, 6 );
	SListaRealesDobles * p_lisVacia = SLisRealdCrear ();
	if ( ES_VALIDO ( p_lisObj ) && ES_VALIDO ( p_lisVacia ) )
	{
		if ( ( SLisRealdBuscarPrimero ( p_lisObj, 20.5 ) != 0 ) ||
			 ( SLisRealdBuscarSiguiente ( p_lisObj, 20.5, 0 ) != 2 ) ||
			 ( SLisRealdBuscarSiguiente ( p_lisObj, 20.5, 2 ) != 4 ) ||
			 ( SLisRealdBuscarSiguiente ( p_lisObj, 20.5, 4 ) != -1 ) )
		{
			printf( "Error caso 1: el 20.5 deberia estar en 0, 2 y 4\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Desde la posicion siguiente, no desde la misma. */
		if ( ( SLisRealdBuscarSiguiente ( p_lisObj, 20.5, 1 ) != 2 ) ||
			 ( SLisRealdBuscarSiguiente ( p_lisObj, 20.5, 5 ) != -1 ) ||
			 ( SLisRealdBuscarSiguiente ( p_lisObj, 20.5, -2 ) != -1 ) ||
			 ( SLisRealdBuscar ( p_lisObj, 20.5 ) != 0 ) ||
			 ( SLisRealdBuscar ( p_lisObj, 40.5 ) != 5 ) )
		{
			printf( "Error caso 2: detras de la 1 esta en la 2, y Buscar es BuscarPrimero\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisRealdRepeticiones ( p_lisObj, 20.5 ) != 3 ) ||
			 ( SLisRealdRepeticiones ( p_lisObj, 40.5 ) != 1 ) ||
			 ( SLisRealdRepeticiones ( p_lisObj, 99.5 ) != 0 ) ||
			 ( SLisRealdBuscarPrimero ( p_lisObj, 99.5 ) != -1 ) )
		{
			printf( "Error caso 3: el 20.5 deberia estar 3 veces, el 40.5 una y el 99.5 ninguna\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SLisRealdRepeticiones ( p_lisVacia, 20.5 ) != 0 ) || ( SLisRealdBuscarPrimero ( p_lisVacia, 20.5 ) != -1 ) ||
			 ( SLisRealdRepeticiones ( NULL, 20.5 ) != 0 ) || ( SLisRealdBuscarSiguiente ( NULL, 20.5, -1 ) != -1 ) ||
			 ( SLisRealdBuscar ( NULL, 20.5 ) != -1 ) )
		{
			printf( "Error caso 4: vacia o nula se esperaba 0 al contar y -1 al buscar\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear las listas\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisRealdDestruir ( &p_lisObj );
	SLisRealdDestruir ( &p_lisVacia );
	return ( iRes );
}

/* Encapsular se queda con la SLista que se le da, sin copiarla, y la
   destruye con ella; con una nula devuelve NULL. */
static int TestSLisRealdEncapsular01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SLisRealdEncapsular 01:\n" );

	double dV [ 3 ] = { 7.5, 2.5, 7.5 };
	SListaRealesDobles * p_lisCopia = CrearListaReald ( dV, 3 );
	SListaRealesDobles * p_lisRes = NULL;
	if ( ES_VALIDO ( p_lisCopia ) )
	{
		/* Se le quita la SLista a p_lisCopia para encapsularla. */
		SLista * p_lisDatos = p_lisCopia->p_lisDatos;
		p_lisCopia->p_lisDatos = NULL;
		p_lisRes = SLisRealdEncapsular ( p_lisDatos );
		if ( ES_NULO ( p_lisRes ) || ( p_lisRes->p_lisDatos != p_lisDatos ) ||
			 ( VerificarContenido ( p_lisRes, dV, 3 ) != BOOL_VAL_CIERTO ) )
		{
			printf( "Error caso 1: deberia envolver esa misma lista, con { 7.5, 2.5, 7.5 }\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( SLisRealdEncapsular ( NULL ) ) )
		{
			printf( "Error caso 2: con una lista nula se esperaba nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la lista\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLisRealdDestruir ( &p_lisRes );
	SLisRealdDestruir ( &p_lisCopia );
	return ( iRes );
}



int TestSListaRealesDobles ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SListaRealesDobles]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSLisRealdCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisRealdInsertar01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisRealdCursor01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisRealdEstablecerElem01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisRealdConjunto01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisRealdTolerancia01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisRealdOrden01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisRealdExisten01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisRealdInsertarLista01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisRealdListaDup01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisRealdExtraerLista01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisRealdEliminarLista01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisRealdOperacionesListas01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisRealdDuplicar01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisRealdCrearDesdeVector01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisRealdCrearConValores01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisRealdRepeticiones01 () == BOOL_VAL_CIERTO ) &&
			( TestSLisRealdEncapsular01 () == BOOL_VAL_CIERTO ) )
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
