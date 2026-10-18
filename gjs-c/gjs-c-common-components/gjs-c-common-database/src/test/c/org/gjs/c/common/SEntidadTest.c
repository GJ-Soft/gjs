#include "Base.h"

#include "SEntidad.h"





static int TestSEntCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SEntCrear 01:\n" );
# if ( defined ( MODO_DEPURACION ) )
	unsigned long ulBloquesAntes = MemNumBloquesActuales ();
# endif

	/* Por defecto el id vale 0, que todavia no es un identificador asignado. */
	SEntidad * p_entObj = SEntCrearDef ();
	if ( ES_VALIDO ( p_entObj ) )
	{
		if ( SEntValorId ( p_entObj ) != 0 )
		{
			printf( "Error caso 1: se esperaba id 0: %lu\n", SEntValorId ( p_entObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntEsValida ( p_entObj ) != 0 )
		{
			printf( "Error caso 2: una entidad con id 0 no deberia ser valida\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la entidad por defecto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SEntDestruir ( &p_entObj );

	/* Con id y sin contenido: el contenido es opcional, asi que es valida. */
	p_entObj = SEntCrear ( 42 );
	if ( ES_VALIDO ( p_entObj ) )
	{
		if ( SEntValorId ( p_entObj ) != 42 )
		{
			printf( "Error caso 3: se esperaba id 42: %lu\n", SEntValorId ( p_entObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntEsValida ( p_entObj ) != 1 )
		{
			printf( "Error caso 4: con id y sin contenido deberia ser valida\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( SEntContenido ( p_entObj ) ) )
		{
			printf( "Error caso 5: se esperaba contenido nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la entidad con id\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SEntDestruir ( &p_entObj );

	/* Con contenido: la entidad se queda con el SPtr y lo destruye con ella. */
	char * p_cCarga = CadDuplicar ( "carga" );
	SPtr * p_ptrCarga = SPtrCrearDef ( p_cCarga );
	p_entObj = SEntCrearExt ( 7, p_ptrCarga );
	if ( ES_VALIDO ( p_entObj ) )
	{
		if ( SEntContenido ( p_entObj ) != (void *) p_cCarga )
		{
			printf( "Error caso 6: se esperaba el contenido que se paso al crear\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la entidad con contenido\n" );
		iRes = BOOL_VAL_FALSO;
		SPtrDestruir ( &p_ptrCarga );
	}
	SEntDestruir ( &p_entObj );
	if ( ES_VALIDO ( p_entObj ) )
	{
		printf( "Error caso 7: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}

	/* Sin SPtr de contenido no hay entidad; CrearExt libera el id que habia creado. */
	p_entObj = SEntCrearExt ( 7, NULL );
	if ( ES_VALIDO ( p_entObj ) )
	{
		printf( "Error caso 8: crear con SPtr nulo deberia dar nulo\n" );
		iRes = BOOL_VAL_FALSO;
		SEntDestruir ( &p_entObj );
	}
# if ( defined ( MODO_DEPURACION ) )
	/* Destruir la entidad libera tambien el contenido. */
	if ( MemNumBloquesActuales () != ulBloquesAntes )
	{
		printf( "Error caso 9: quedan %ld bloques sin liberar\n", (long) ( MemNumBloquesActuales () - ulBloquesAntes ) );
		iRes = BOOL_VAL_FALSO;
	}
# endif
	return ( iRes );
}

static int TestSEntEncapsular01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SEntEncapsular 01:\n" );

	/* Encapsular toma la propiedad del SId que se le entrega. */
	SEntidad * p_entObj = SEntEncapsular ( SIdCrear ( 9 ) );
	if ( ES_VALIDO ( p_entObj ) )
	{
		if ( SEntValorId ( p_entObj ) != 9 )
		{
			printf( "Error caso 1: se esperaba id 9: %lu\n", SEntValorId ( p_entObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_NULO ( SEntId ( p_entObj ) ) )
		{
			printf( "Error caso 2: se esperaba el SId interno\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo encapsular\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SEntDestruir ( &p_entObj );

	/* Sin identificador no hay entidad. */
	p_entObj = SEntEncapsular ( NULL );
	if ( ES_VALIDO ( p_entObj ) )
	{
		printf( "Error caso 3: encapsular sin id deberia dar nulo\n" );
		iRes = BOOL_VAL_FALSO;
		SEntDestruir ( &p_entObj );
	}
	return ( iRes );
}

static int TestSEntEstablecer01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SEntEstablecer 01:\n" );
# if ( defined ( MODO_DEPURACION ) )
	unsigned long ulBloquesAntes = MemNumBloquesActuales ();
# endif

	SEntidad * p_entObj = SEntCrear ( 1 );
	SId * p_idOtro = SIdCrear ( 55 );
	if ( ES_VALIDO ( p_entObj ) && ES_VALIDO ( p_idOtro ) )
	{
		/* El retorno dice si se guardo, no si la entidad quedo completa. */
		if ( SEntEstablecerValorId ( p_entObj, 99 ) != 1 )
		{
			printf( "Error caso 1: se esperaba 1 al establecer el valor del id\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntValorId ( p_entObj ) != 99 )
		{
			printf( "Error caso 2: se esperaba id 99: %lu\n", SEntValorId ( p_entObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		/* EstablecerId copia el valor: el SId de fuera sigue siendo del llamante. */
		if ( SEntEstablecerId ( p_entObj, p_idOtro ) != 1 )
		{
			printf( "Error caso 3: se esperaba 1 al establecer el id\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntValorId ( p_entObj ) != 55 )
		{
			printf( "Error caso 4: se esperaba id 55: %lu\n", SEntValorId ( p_entObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntId ( p_entObj ) == p_idOtro )
		{
			printf( "Error caso 5: no deberia haberse quedado con el SId de fuera\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Establecer el contenido lo guarda en el SPtr, que destruye el anterior. */
		char * p_cUno = CadDuplicar ( "uno" );
		char * p_cDos = CadDuplicar ( "dos" );
		if ( SEntEstablecerContenido ( p_entObj, p_cUno ) != 1 )
		{
			printf( "Error caso 6: se esperaba 1 al establecer el contenido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntContenido ( p_entObj ) != (void *) p_cUno )
		{
			printf( "Error caso 7: se esperaba el contenido establecido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntEstablecerContenido ( p_entObj, p_cDos ) != 1 )
		{
			printf( "Error caso 8: se esperaba 1 al cambiar el contenido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntContenido ( p_entObj ) != (void *) p_cDos )
		{
			printf( "Error caso 9: se esperaba el contenido nuevo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntEstablecerContenido ( p_entObj, NULL ) != 1 )
		{
			printf( "Error caso 10: se esperaba 1 al vaciar el contenido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntTieneContenido ( p_entObj ) != 0 )
		{
			printf( "Error caso 11: tras establecer nulo no deberia tener contenido\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear los objetos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SEntDestruir ( &p_entObj );
	SIdDestruir ( &p_idOtro );

	/* Sobre una entidad nula debe fallar. */
	if ( SEntEstablecerValorId ( NULL, 1 ) != 0 )
	{
		printf( "Error caso 12: establecer sobre una entidad nula deberia fallar\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SEntEstablecerContenido ( NULL, NULL ) != 0 )
	{
		printf( "Error caso 13: establecer contenido en una entidad nula deberia fallar\n" );
		iRes = BOOL_VAL_FALSO;
	}
# if ( defined ( MODO_DEPURACION ) )
	/* Cada contenido sustituido se libero al cambiarlo. */
	if ( MemNumBloquesActuales () != ulBloquesAntes )
	{
		printf( "Error caso 14: quedan %ld bloques sin liberar\n", (long) ( MemNumBloquesActuales () - ulBloquesAntes ) );
		iRes = BOOL_VAL_FALSO;
	}
# endif
	return ( iRes );
}

/* SEntAsignarContenido cambia el SPtr entero: destruye el anterior y se queda
   con el nuevo. Con el mismo SPtr que ya tiene no hace nada. */
static int TestSEntAsignarContenido01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SEntAsignarContenido 01:\n" );
# if ( defined ( MODO_DEPURACION ) )
	unsigned long ulBloquesAntes = MemNumBloquesActuales ();
# endif
	SEntidad * p_entObj = SEntCrear ( 3 );
	if ( ES_VALIDO ( p_entObj ) )
	{
		char * p_cUno = CadDuplicar ( "uno" );
		SPtr * p_ptrUno = SPtrCrearDef ( p_cUno );
		if ( SEntAsignarContenido ( p_entObj, p_ptrUno ) != 1 )
		{
			printf( "Error caso 1: se esperaba 1 al asignar el contenido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntContenido ( p_entObj ) != (void *) p_cUno )
		{
			printf( "Error caso 2: se esperaba el contenido asignado\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntAsignarContenido ( p_entObj, p_ptrUno ) != 1 )
		{
			printf( "Error caso 3: se esperaba 1 al asignar el mismo SPtr\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntContenido ( p_entObj ) != (void *) p_cUno )
		{
			printf( "Error caso 4: asignar el mismo SPtr no deberia destruirlo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		char * p_cDos = CadDuplicar ( "dos" );
		if ( SEntAsignarContenido ( p_entObj, SPtrCrearDef ( p_cDos ) ) != 1 )
		{
			printf( "Error caso 5: se esperaba 1 al asignar otro SPtr\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntContenido ( p_entObj ) != (void *) p_cDos )
		{
			printf( "Error caso 6: se esperaba el contenido del SPtr nuevo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Sin SPtr no se cambia nada. */
		if ( SEntAsignarContenido ( p_entObj, NULL ) != 0 )
		{
			printf( "Error caso 7: asignar un SPtr nulo deberia fallar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntContenido ( p_entObj ) != (void *) p_cDos )
		{
			printf( "Error caso 8: tras fallar deberia conservar el contenido\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la entidad\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SEntDestruir ( &p_entObj );

	/* Sobre una entidad nula falla, y el SPtr sigue siendo del llamante. */
	SPtr * p_ptrSuelto = SPtrCrearDef ( NULL );
	if ( SEntAsignarContenido ( NULL, p_ptrSuelto ) != 0 )
	{
		printf( "Error caso 9: asignar en una entidad nula deberia fallar\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SPtrDestruir ( &p_ptrSuelto );
# if ( defined ( MODO_DEPURACION ) )
	if ( MemNumBloquesActuales () != ulBloquesAntes )
	{
		printf( "Error caso 10: quedan %ld bloques sin liberar\n", (long) ( MemNumBloquesActuales () - ulBloquesAntes ) );
		iRes = BOOL_VAL_FALSO;
	}
# endif
	return ( iRes );
}

static int TestSEntComparaciones01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SEntComparaciones 01:\n" );

	SEntidad * p_entA = SEntCrear ( 10 );
	SEntidad * p_entB = SEntCrear ( 20 );
	if ( ES_VALIDO ( p_entA ) && ES_VALIDO ( p_entB ) )
	{
		if ( SEntEsMenor ( p_entA, p_entB ) != 1 )
		{
			printf( "Error caso 1: 10 deberia ser menor que 20\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntEsMayor ( p_entB, p_entA ) != 1 )
		{
			printf( "Error caso 2: 20 deberia ser mayor que 10\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntEsIgual ( p_entA, p_entB ) != 0 )
		{
			printf( "Error caso 3: 10 y 20 no deberian ser iguales\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntEsIgualNum ( p_entA, 10 ) != 1 )
		{
			printf( "Error caso 4: deberia ser igual a 10\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntEstaEnRangoNum ( p_entA, 5, 15 ) != 1 )
		{
			printf( "Error caso 5: 10 deberia estar en el rango ( 5, 15 )\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntEstaEnRangoIgNum ( p_entA, 10, 15 ) != 1 )
		{
			printf( "Error caso 6: 10 deberia estar en el rango cerrado [ 10, 15 ]\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Comparacion de tres vias, y el orden con nulos. */
		if ( SEntComparar ( p_entA, p_entB ) != COMP_MENOR )
		{
			printf( "Error caso 7: 10 frente a 20 deberia dar COMP_MENOR: %d\n", SEntComparar ( p_entA, p_entB ) );
			iRes = BOOL_VAL_FALSO;
		}
		SEntEstablecerValorId ( p_entB, 10 );
		if ( SEntComparar ( p_entA, p_entB ) != COMP_IGUAL )
		{
			printf( "Error caso 8: dos ids iguales deberian dar COMP_IGUAL: %d\n", SEntComparar ( p_entA, p_entB ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntEsIgual ( p_entA, p_entB ) != 1 )
		{
			printf( "Error caso 9: deberian ser iguales tras igualar el id\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntComparar ( p_entA, NULL ) != COMP_MAYOR )
		{
			printf( "Error caso 10: frente a una entidad nula deberia dar COMP_MAYOR\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntComparar ( NULL, p_entA ) != COMP_MENOR )
		{
			printf( "Error caso 11: una entidad nula deberia dar COMP_MENOR\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntComparar ( NULL, NULL ) != COMP_IGUAL )
		{
			printf( "Error caso 12: dos entidades nulas deberian dar COMP_IGUAL\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear las entidades\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SEntDestruir ( &p_entA );
	SEntDestruir ( &p_entB );
	return ( iRes );
}

static int TestSEntHash01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SEntHash 01:\n" );

	SEntidad * p_entA = SEntCrear ( 12345 );
	SEntidad * p_entB = SEntCrear ( 12345 );
	SEntEstablecerContenido ( p_entA, CadDuplicar ( "uno" ) );
	SEntEstablecerContenido ( p_entB, CadDuplicar ( "dos" ) );
	if ( ES_VALIDO ( p_entA ) && ES_VALIDO ( p_entB ) )
	{
		/* Contrato hash-igualdad: si son iguales, mismo hash. El contenido no
		   entra en la identidad, asi que tampoco entra en el hash. */
		if ( SEntEsIgual ( p_entA, p_entB ) != 1 )
		{
			printf( "Error caso 1: mismo id deberia ser igual\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntHash ( p_entA ) != SEntHash ( p_entB ) )
		{
			printf( "Error caso 2: entidades iguales deberian tener el mismo hash\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Cambiar el id cambia el hash. */
		SEntEstablecerValorId ( p_entB, 999 );
		if ( SEntHash ( p_entA ) == SEntHash ( p_entB ) )
		{
			printf( "Error caso 3: ids distintos deberian dar hash distinto\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear las entidades\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SEntDestruir ( &p_entA );
	SEntDestruir ( &p_entB );
	return ( iRes );
}



/* SEntTieneContenido: 1 con contenido, 0 sin el y 0 con NULL. Destruir libera
   tambien el contenido. */
static int TestSEntTieneContenido01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SEntTieneContenido 01:\n" );
	void * p_vDato = MemReservar ( 16 );

	SEntidad * p_entObj = SEntEncapsularExt ( SIdCrear ( 9 ), SPtrCrearDef ( p_vDato ) );
	if ( SEntTieneContenido ( p_entObj ) != 1 )
	{
		printf( "Error caso 1: con contenido se esperaba 1\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SEntDestruir ( &p_entObj );

	p_entObj = SEntEncapsular ( SIdCrear ( 9 ) );
	if ( SEntTieneContenido ( p_entObj ) != 0 )
	{
		printf( "Error caso 2: sin contenido se esperaba 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SEntDestruir ( &p_entObj );

	if ( SEntTieneContenido ( NULL ) != 0 )
	{
		printf( "Error caso 3: con NULL se esperaba 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

/* SEntPtr envuelve la entidad en un SPtr con SEntDestruir como destructor: al
   destruir el SPtr se libera la entidad y, con ella, su contenido. Con
   MODO_DEPURACION se comprueba que no queda memoria reservada. */
/* Destructor de prueba: cuenta las llamadas y libera como el de por defecto. */
static int iNumDestrucciones = 0;

static void DestructorContador ( void ** p_p_vObj )
{
	iNumDestrucciones = iNumDestrucciones + 1;
	MemLiberar ( p_p_vObj );
}

static int TestSEntEstablecerContenidoExt01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SEntEstablecerContenidoExt 01:\n" );
# if ( defined ( MODO_DEPURACION ) )
	unsigned long ulBloquesAntes = MemNumBloquesActuales ();
# endif
	iNumDestrucciones = 0;
	SEntidad * p_entObj = SEntCrear ( 3 );
	if ( ES_VALIDO ( p_entObj ) )
	{
		char * p_cUno = CadDuplicar ( "uno" );
		if ( SEntEstablecerContenidoExt ( p_entObj, p_cUno, DestructorContador ) != 1 )
		{
			printf( "Error caso 1: se esperaba 1 al establecer con destructor\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntContenido ( p_entObj ) != (void *) p_cUno )
		{
			printf( "Error caso 2: se esperaba el contenido establecido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Con el mismo objeto solo cambia el destructor: no se destruye. */
		if ( SEntEstablecerContenidoExt ( p_entObj, p_cUno, DestructorContador ) != 1 )
		{
			printf( "Error caso 3: se esperaba 1 al establecer el mismo objeto\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( iNumDestrucciones != 0 )
		{
			printf( "Error caso 4: el mismo objeto no deberia destruirse: %d\n", iNumDestrucciones );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntContenido ( p_entObj ) != (void *) p_cUno )
		{
			printf( "Error caso 5: se esperaba conservar el mismo contenido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Sin destructor falla, tambien con el mismo objeto. */
		if ( SEntEstablecerContenidoExt ( p_entObj, p_cUno, NULL ) != 0 )
		{
			printf( "Error caso 6: sin destructor deberia fallar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		char * p_cTres = CadDuplicar ( "tres" );
		if ( SEntEstablecerContenidoExt ( p_entObj, p_cTres, NULL ) != 0 )
		{
			printf( "Error caso 7: sin destructor deberia fallar con otro objeto\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntContenido ( p_entObj ) != (void *) p_cUno )
		{
			printf( "Error caso 8: tras fallar deberia conservar el contenido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		MemLiberar ( (void **) &p_cTres );
		/* Establecer sin Ext usa el destructor fijado con Ext. */
		char * p_cDos = CadDuplicar ( "dos" );
		if ( SEntEstablecerContenido ( p_entObj, p_cDos ) != 1 )
		{
			printf( "Error caso 9: se esperaba 1 al establecer otro contenido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( iNumDestrucciones != 1 )
		{
			printf( "Error caso 10: se esperaba 1 llamada al destructor: %d\n", iNumDestrucciones );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la entidad\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SEntDestruir ( &p_entObj );
	if ( iNumDestrucciones != 2 )
	{
		printf( "Error caso 11: destruir la entidad deberia usar su destructor: %d\n", iNumDestrucciones );
		iRes = BOOL_VAL_FALSO;
	}

	/* Sobre una entidad nula falla, y el objeto sigue siendo del llamante. */
	char * p_cSuelto = CadDuplicar ( "suelto" );
	if ( SEntEstablecerContenidoExt ( NULL, p_cSuelto, DestructorContador ) != 0 )
	{
		printf( "Error caso 12: establecer en una entidad nula deberia fallar\n" );
		iRes = BOOL_VAL_FALSO;
	}
	MemLiberar ( (void **) &p_cSuelto );
# if ( defined ( MODO_DEPURACION ) )
	if ( MemNumBloquesActuales () != ulBloquesAntes )
	{
		printf( "Error caso 13: quedan %ld bloques sin liberar\n", (long) ( MemNumBloquesActuales () - ulBloquesAntes ) );
		iRes = BOOL_VAL_FALSO;
	}
# endif
	ErrLimpiar ();
	return ( iRes );
}

static int TestSEntPtr01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SEntPtr 01:\n" );
# if ( defined ( MODO_DEPURACION ) )
	unsigned long ulBloquesAntes = MemNumBloquesActuales ();
# endif
	SEntidad * p_entObj = SEntCrear ( 5 );
	SEntEstablecerContenido ( p_entObj, CadDuplicar ( "carga" ) );
	SPtr * p_ptrObj = SEntPtr ( p_entObj );
	if ( ES_NULO ( p_ptrObj ) )
	{
		printf( "Error caso 1: no se esperaba nulo al crear el SPtr\n" );
		iRes = BOOL_VAL_FALSO;
		SEntDestruir ( &p_entObj );
	}
	else
	{
		if ( SPtrEsValido ( p_ptrObj ) != 1 )
		{
			printf( "Error caso 2: el SPtr deberia ser valido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SPtrObjeto ( p_ptrObj ) != p_entObj )
		{
			printf( "Error caso 3: el SPtr deberia envolver la misma SEntidad\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* La SEntidad pasa a ser del SPtr: se libera con el, no por separado. */
		SPtrDestruir ( &p_ptrObj );
		if ( ES_VALIDO ( p_ptrObj ) )
		{
			printf( "Error caso 4: se esperaba puntero nulo tras destruir\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
# if ( defined ( MODO_DEPURACION ) )
	if ( MemNumBloquesActuales () != ulBloquesAntes )
	{
		printf( "Error caso 5: quedan %ld bloques sin liberar\n", (long) ( MemNumBloquesActuales () - ulBloquesAntes ) );
		iRes = BOOL_VAL_FALSO;
	}
# endif
	return ( iRes );
}

/* Con objeto nulo, SEntPtr da un SPtr vacio: hay que destruirlo igualmente.
   Con MODO_DEPURACION se comprueba que no queda memoria reservada. */
static int TestSEntPtrNulo01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SEntPtrNulo 01:\n" );
# if ( defined ( MODO_DEPURACION ) )
	unsigned long ulBloquesAntes = MemNumBloquesActuales ();
# endif
	SPtr * p_ptrObj = SEntPtr ( NULL );
	if ( ES_NULO ( p_ptrObj ) )
	{
		printf( "Error caso 1: con objeto nulo se esperaba un SPtr vacio, no nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SPtrEstaVacio ( p_ptrObj ) != 1 )
		{
			printf( "Error caso 2: con objeto nulo el SPtr deberia estar vacio\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SPtrDestruir ( &p_ptrObj );
	}
# if ( defined ( MODO_DEPURACION ) )
	if ( MemNumBloquesActuales () != ulBloquesAntes )
	{
		printf( "Error caso 3: quedan %ld bloques sin liberar\n", (long) ( MemNumBloquesActuales () - ulBloquesAntes ) );
		iRes = BOOL_VAL_FALSO;
	}
# endif
	ErrLimpiar ();
	return ( iRes );
}

int TestSEntidad ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SEntidad]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSEntCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSEntTieneContenido01 () == BOOL_VAL_CIERTO ) &&
			( TestSEntEncapsular01 () == BOOL_VAL_CIERTO ) &&
			( TestSEntEstablecer01 () == BOOL_VAL_CIERTO ) &&
			( TestSEntAsignarContenido01 () == BOOL_VAL_CIERTO ) &&
			( TestSEntEstablecerContenidoExt01 () == BOOL_VAL_CIERTO ) &&
			( TestSEntComparaciones01 () == BOOL_VAL_CIERTO ) &&
			( TestSEntHash01 () == BOOL_VAL_CIERTO ) &&
			( TestSEntPtr01 () == BOOL_VAL_CIERTO ) &&
			( TestSEntPtrNulo01 () == BOOL_VAL_CIERTO ) )
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
