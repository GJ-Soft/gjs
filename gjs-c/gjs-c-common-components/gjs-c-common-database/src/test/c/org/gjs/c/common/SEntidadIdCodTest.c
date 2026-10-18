#include "Base.h"
#include "Texto.h"

#include "SEntidadIdCod.h"



static int TestSEntIdCodCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SEntIdCodCrear 01:\n" );
# if ( defined ( MODO_DEPURACION ) )
	unsigned long ulBloquesAntes = MemNumBloquesActuales ();
# endif

	/* Por defecto: id 0, que todavia no es un identificador asignado. */
	SEntidadIdCod * p_enticObj = SEntIdCodCrearDef ( COD_MAX_TAM_DEF );
	if ( ES_VALIDO ( p_enticObj ) )
	{
		if ( SEntIdCodValorId ( p_enticObj ) != 0 )
		{
			printf( "Error caso 1: se esperaba id 0: %lu\n", SEntIdCodValorId ( p_enticObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntIdCodEsValida ( p_enticObj ) != 0 )
		{
			printf( "Error caso 2: con id 0 no deberia ser valida\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la entidad por defecto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SEntIdCodDestruir ( &p_enticObj );

	/* Con id y codigo. La validez la da el id, que es el identificador. */
	p_enticObj = SEntIdCodCrearLit ( 42, "COD001", COD_MAX_TAM_DEF );
	if ( ES_VALIDO ( p_enticObj ) )
	{
		if ( SEntIdCodValorId ( p_enticObj ) != 42 )
		{
			printf( "Error caso 3: se esperaba id 42: %lu\n", SEntIdCodValorId ( p_enticObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( CadComparar ( SEntIdCodValorCodigoLit ( p_enticObj ), "COD001" ) != COMP_IGUAL )
		{
			printf( "Error caso 4: se esperaba codigo \"COD001\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntIdCodEsValida ( p_enticObj ) != 1 )
		{
			printf( "Error caso 5: con id asignado deberia ser valida\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_NULO ( SEntIdCodBase ( p_enticObj ) ) )
		{
			printf( "Error caso 6: se esperaba la entidad base\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la entidad con codigo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SEntIdCodDestruir ( &p_enticObj );

	/* Con contenido: la entidad se queda con el SPtr y lo destruye con ella. */
	char * p_cCarga = CadDuplicar ( "carga" );
	SPtr * p_ptrCarga = SPtrCrearDef ( p_cCarga );
	p_enticObj = SEntIdCodCrearLitExt ( 7, "COD002", COD_MAX_TAM_DEF, p_ptrCarga );
	if ( ES_VALIDO ( p_enticObj ) )
	{
		if ( SEntIdCodContenido ( p_enticObj ) != (void *) p_cCarga )
		{
			printf( "Error caso 7: se esperaba el contenido que se paso al crear\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la entidad con contenido\n" );
		iRes = BOOL_VAL_FALSO;
		SPtrDestruir ( &p_ptrCarga );
	}
	SEntIdCodDestruir ( &p_enticObj );
	if ( ES_VALIDO ( p_enticObj ) )
	{
		printf( "Error caso 8: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}

	/* Sin SPtr de contenido no hay entidad; SEntIdCodCrearLitExt libera lo que habia creado. */
	p_enticObj = SEntIdCodCrearLitExt ( 7, "COD002", COD_MAX_TAM_DEF, NULL );
	if ( ES_VALIDO ( p_enticObj ) )
	{
		printf( "Error caso 9: crear con SPtr nulo deberia dar nulo\n" );
		iRes = BOOL_VAL_FALSO;
		SEntIdCodDestruir ( &p_enticObj );
	}
# if ( defined ( MODO_DEPURACION ) )
	/* Destruir la entidad libera tambien el contenido. */
	if ( MemNumBloquesActuales () != ulBloquesAntes )
	{
		printf( "Error caso 10: quedan %ld bloques sin liberar\n", (long) ( MemNumBloquesActuales () - ulBloquesAntes ) );
		iRes = BOOL_VAL_FALSO;
	}
# endif
	return ( iRes );
}

static int TestSEntIdCodCodigoObligatorio01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SEntIdCodCodigoObligatorio 01:\n" );

	/* A diferencia de SEntidadNom y SEntidadCodNom, aqui el codigo es el
	   segundo identificador y es obligatorio: un codigo que no supera la
	   validacion de SCodigo no da una entidad sin codigo, no da entidad. */
	SEntidadIdCod * p_enticObj = SEntIdCodCrearLit ( 5, "COD-001", COD_MAX_TAM_DEF );
	if ( ES_VALIDO ( p_enticObj ) )
	{
		printf( "Error caso 1: con un codigo invalido no deberia crearse la entidad\n" );
		iRes = BOOL_VAL_FALSO;
		SEntIdCodDestruir ( &p_enticObj );
	}

	/* Sin identificador tampoco, aunque el codigo sea correcto. Y al fallar,
	   Encapsular no se queda con el codigo: sigue siendo del llamante, que es
	   quien lo destruye. */
	SCodigo * p_codSuelto = SCodCrearValorLitExt ( "COD001", COD_MAX_TAM_DEF );
	p_enticObj = SEntIdCodEncapsular ( NULL, p_codSuelto );
	if ( ES_VALIDO ( p_enticObj ) )
	{
		printf( "Error caso 2: encapsular sin id deberia dar nulo\n" );
		iRes = BOOL_VAL_FALSO;
		SEntIdCodDestruir ( &p_enticObj );
	}
	SCodDestruir ( &p_codSuelto );

	/* Y al reves: con id valido pero sin codigo, tampoco. */
	SId * p_idSuelto = SIdCrear ( 5 );
	p_enticObj = SEntIdCodEncapsular ( p_idSuelto, NULL );
	if ( ES_VALIDO ( p_enticObj ) )
	{
		printf( "Error caso 3: encapsular sin codigo deberia dar nulo\n" );
		iRes = BOOL_VAL_FALSO;
		SEntIdCodDestruir ( &p_enticObj );
	}
	SIdDestruir ( &p_idSuelto );
	return ( iRes );
}

static int TestSEntIdCodEstablecer01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SEntIdCodEstablecer 01:\n" );

	SEntidadIdCod * p_enticObj = SEntIdCodCrearLit ( 1, "COD001", COD_MAX_TAM_DEF );
	if ( ES_VALIDO ( p_enticObj ) )
	{
		if ( SEntIdCodEstablecerValorId ( p_enticObj, 99 ) != 1 )
		{
			printf( "Error caso 1: se esperaba 1 al establecer el valor del id\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntIdCodValorId ( p_enticObj ) != 99 )
		{
			printf( "Error caso 2: se esperaba id 99: %lu\n", SEntIdCodValorId ( p_enticObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntIdCodEstablecerValorCodigoLit ( p_enticObj, "COD999" ) != 1 )
		{
			printf( "Error caso 3: se esperaba 1 al establecer el codigo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( CadComparar ( SEntIdCodValorCodigoLit ( p_enticObj ), "COD999" ) != COMP_IGUAL )
		{
			printf( "Error caso 4: se esperaba codigo \"COD999\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* El cambio de id se ve tambien desde la base, que es el mismo objeto. */
		if ( SEntValorId ( SEntIdCodBase ( p_enticObj ) ) != 99 )
		{
			printf( "Error caso 5: la base deberia ver el id nuevo\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la entidad\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SEntIdCodDestruir ( &p_enticObj );
	return ( iRes );
}

static int TestSEntIdCodIdentidad01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SEntIdCodIdentidad 01:\n" );

	/* Mismo id y distinto codigo: la identidad es el id, y nada mas. */
	SEntidadIdCod * p_enticA = SEntIdCodCrearLit ( 10, "CODA", COD_MAX_TAM_DEF );
	SEntidadIdCod * p_enticB = SEntIdCodCrearLit ( 10, "CODB", COD_MAX_TAM_DEF );
	if ( ES_VALIDO ( p_enticA ) && ES_VALIDO ( p_enticB ) )
	{
		if ( SEntIdCodEsIgual ( p_enticA, p_enticB ) != 1 )
		{
			printf( "Error caso 1: mismo id deberia ser igual pese al codigo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Contrato hash-igualdad: el codigo es mutable, asi que no puede entrar
		   en el reparto. */
		if ( SEntIdCodHash ( p_enticA ) != SEntIdCodHash ( p_enticB ) )
		{
			printf( "Error caso 2: entidades iguales deberian tener el mismo hash\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Y reparte igual que su base, para poder convivir en la misma tabla. */
		if ( SEntIdCodHash ( p_enticA ) != SEntHash ( SEntIdCodBase ( p_enticA ) ) )
		{
			printf( "Error caso 3: deberia repartir igual que su entidad base\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Cambiar el codigo no cambia ni la identidad ni el hash. */
		SEntIdCodEstablecerValorCodigoLit ( p_enticA, "CODC" );
		if ( SEntIdCodHash ( p_enticA ) != SEntIdCodHash ( p_enticB ) )
		{
			printf( "Error caso 4: cambiar el codigo no deberia cambiar el hash\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Ids distintos: ya no son iguales. */
		SEntIdCodEstablecerValorId ( p_enticB, 20 );
		if ( SEntIdCodEsIgual ( p_enticA, p_enticB ) != 0 )
		{
			printf( "Error caso 5: ids distintos no deberian ser iguales\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntIdCodEsMenor ( p_enticA, p_enticB ) != 1 )
		{
			printf( "Error caso 6: 10 deberia ser menor que 20\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntIdCodEsIgualNum ( p_enticA, 10 ) != 1 )
		{
			printf( "Error caso 7: deberia ser igual a 10\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear las entidades\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SEntIdCodDestruir ( &p_enticA );
	SEntIdCodDestruir ( &p_enticB );
	return ( iRes );
}

static int TestSEntIdCodComparar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SEntIdCodComparar 01:\n" );

	SEntidadIdCod * p_enticA = SEntIdCodCrearLit ( 10, "CODA", COD_MAX_TAM_DEF );
	SEntidadIdCod * p_enticB = SEntIdCodCrearLit ( 20, "CODB", COD_MAX_TAM_DEF );
	if ( ES_VALIDO ( p_enticA ) && ES_VALIDO ( p_enticB ) )
	{
		if ( SEntIdCodComparar ( p_enticA, p_enticB ) != COMP_MENOR )
		{
			printf( "Error caso 1: 10 frente a 20 deberia dar COMP_MENOR: %d\n", SEntIdCodComparar ( p_enticA, p_enticB ) );
			iRes = BOOL_VAL_FALSO;
		}
		/* Con el mismo id, Comparar desempata por codigo. Es deliberado y
		   provisional: sirve para ordenar listas cuyos ids aun no estan
		   asignados o estan repetidos. No es el criterio de identidad, que es
		   solo el id: por eso EsIgual sigue diciendo que son iguales. */
		SEntIdCodEstablecerValorId ( p_enticB, 10 );
		if ( SEntIdCodComparar ( p_enticA, p_enticB ) != COMP_MENOR )
		{
			printf( "Error caso 2: con el mismo id deberia desempatar por codigo: %d\n", SEntIdCodComparar ( p_enticA, p_enticB ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntIdCodEsIgual ( p_enticA, p_enticB ) != 1 )
		{
			printf( "Error caso 3: el desempate no deberia afectar a EsIgual\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Mismo id y mismo codigo: iguales tambien para Comparar. */
		SEntIdCodEstablecerValorCodigoLit ( p_enticB, "CODA" );
		if ( SEntIdCodComparar ( p_enticA, p_enticB ) != COMP_IGUAL )
		{
			printf( "Error caso 4: mismo id y codigo deberia dar COMP_IGUAL: %d\n", SEntIdCodComparar ( p_enticA, p_enticB ) );
			iRes = BOOL_VAL_FALSO;
		}
		/* Orden con nulos. */
		if ( SEntIdCodComparar ( p_enticA, NULL ) != COMP_MAYOR )
		{
			printf( "Error caso 5: frente a una entidad nula deberia dar COMP_MAYOR\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntIdCodComparar ( NULL, p_enticA ) != COMP_MENOR )
		{
			printf( "Error caso 6: una entidad nula deberia dar COMP_MENOR\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntIdCodComparar ( NULL, NULL ) != COMP_IGUAL )
		{
			printf( "Error caso 7: dos entidades nulas deberian dar COMP_IGUAL\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear las entidades\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SEntIdCodDestruir ( &p_enticA );
	SEntIdCodDestruir ( &p_enticB );
	return ( iRes );
}



/* SEntIdCodTieneContenido: 1 con contenido, 0 sin el y 0 con NULL. Destruir libera
   tambien el contenido. */
static int TestSEntIdCodTieneContenido01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SEntIdCodTieneContenido 01:\n" );
	void * p_vDato = MemReservar ( 16 );

	SEntidadIdCod * p_enticObj = SEntIdCodEncapsularExt ( SIdCrear ( 9 ), SCodCrearValorLitExt ( "COD001", COD_MAX_TAM_DEF ), SPtrCrearDef ( p_vDato ) );
	if ( SEntIdCodTieneContenido ( p_enticObj ) != 1 )
	{
		printf( "Error caso 1: con contenido se esperaba 1\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SEntIdCodDestruir ( &p_enticObj );

	p_enticObj = SEntIdCodEncapsular ( SIdCrear ( 9 ), SCodCrearValorLitExt ( "COD001", COD_MAX_TAM_DEF ) );
	if ( SEntIdCodTieneContenido ( p_enticObj ) != 0 )
	{
		printf( "Error caso 2: sin contenido se esperaba 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SEntIdCodDestruir ( &p_enticObj );

	if ( SEntIdCodTieneContenido ( NULL ) != 0 )
	{
		printf( "Error caso 3: con NULL se esperaba 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

/* SEntIdCodAsignarContenido cambia el SPtr entero: destruye el anterior y se queda
   con el nuevo. Con el mismo SPtr que ya tiene no hace nada. */
static int TestSEntIdCodAsignarContenido01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SEntIdCodAsignarContenido 01:\n" );
# if ( defined ( MODO_DEPURACION ) )
	unsigned long ulBloquesAntes = MemNumBloquesActuales ();
# endif
	SEntidadIdCod * p_enticObj = SEntIdCodCrearLit ( 3, "COD001", COD_MAX_TAM_DEF );
	if ( ES_VALIDO ( p_enticObj ) )
	{
		char * p_cUno = CadDuplicar ( "uno" );
		SPtr * p_ptrUno = SPtrCrearDef ( p_cUno );
		if ( SEntIdCodAsignarContenido ( p_enticObj, p_ptrUno ) != 1 )
		{
			printf( "Error caso 1: se esperaba 1 al asignar el contenido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntIdCodContenido ( p_enticObj ) != (void *) p_cUno )
		{
			printf( "Error caso 2: se esperaba el contenido asignado\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntIdCodAsignarContenido ( p_enticObj, p_ptrUno ) != 1 )
		{
			printf( "Error caso 3: se esperaba 1 al asignar el mismo SPtr\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntIdCodContenido ( p_enticObj ) != (void *) p_cUno )
		{
			printf( "Error caso 4: asignar el mismo SPtr no deberia destruirlo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		char * p_cDos = CadDuplicar ( "dos" );
		if ( SEntIdCodAsignarContenido ( p_enticObj, SPtrCrearDef ( p_cDos ) ) != 1 )
		{
			printf( "Error caso 5: se esperaba 1 al asignar otro SPtr\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntIdCodContenido ( p_enticObj ) != (void *) p_cDos )
		{
			printf( "Error caso 6: se esperaba el contenido del SPtr nuevo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Sin SPtr no se cambia nada. */
		if ( SEntIdCodAsignarContenido ( p_enticObj, NULL ) != 0 )
		{
			printf( "Error caso 7: asignar un SPtr nulo deberia fallar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntIdCodContenido ( p_enticObj ) != (void *) p_cDos )
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
	SEntIdCodDestruir ( &p_enticObj );

	/* Sobre una entidad nula falla, y el SPtr sigue siendo del llamante. */
	SPtr * p_ptrSuelto = SPtrCrearDef ( NULL );
	if ( SEntIdCodAsignarContenido ( NULL, p_ptrSuelto ) != 0 )
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

/* SEntIdCodPtr envuelve la entidad en un SPtr con SEntIdCodDestruir como destructor: al
   destruir el SPtr se libera la entidad y, con ella, su contenido. Con
   MODO_DEPURACION se comprueba que no queda memoria reservada. */
/* Destructor de prueba: cuenta las llamadas y libera como el de por defecto. */
static int iNumDestrucciones = 0;

static void DestructorContador ( void ** p_p_vObj )
{
	iNumDestrucciones = iNumDestrucciones + 1;
	MemLiberar ( p_p_vObj );
}

static int TestSEntIdCodEstablecerContenidoExt01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SEntIdCodEstablecerContenidoExt 01:\n" );
# if ( defined ( MODO_DEPURACION ) )
	unsigned long ulBloquesAntes = MemNumBloquesActuales ();
# endif
	iNumDestrucciones = 0;
	SEntidadIdCod * p_enticObj = SEntIdCodCrearLit ( 3, "COD001", COD_MAX_TAM_DEF );
	if ( ES_VALIDO ( p_enticObj ) )
	{
		char * p_cUno = CadDuplicar ( "uno" );
		if ( SEntIdCodEstablecerContenidoExt ( p_enticObj, p_cUno, DestructorContador ) != 1 )
		{
			printf( "Error caso 1: se esperaba 1 al establecer con destructor\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntIdCodContenido ( p_enticObj ) != (void *) p_cUno )
		{
			printf( "Error caso 2: se esperaba el contenido establecido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Con el mismo objeto solo cambia el destructor: no se destruye. */
		if ( SEntIdCodEstablecerContenidoExt ( p_enticObj, p_cUno, DestructorContador ) != 1 )
		{
			printf( "Error caso 3: se esperaba 1 al establecer el mismo objeto\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( iNumDestrucciones != 0 )
		{
			printf( "Error caso 4: el mismo objeto no deberia destruirse: %d\n", iNumDestrucciones );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntIdCodContenido ( p_enticObj ) != (void *) p_cUno )
		{
			printf( "Error caso 5: se esperaba conservar el mismo contenido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Sin destructor falla, tambien con el mismo objeto. */
		if ( SEntIdCodEstablecerContenidoExt ( p_enticObj, p_cUno, NULL ) != 0 )
		{
			printf( "Error caso 6: sin destructor deberia fallar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		char * p_cTres = CadDuplicar ( "tres" );
		if ( SEntIdCodEstablecerContenidoExt ( p_enticObj, p_cTres, NULL ) != 0 )
		{
			printf( "Error caso 7: sin destructor deberia fallar con otro objeto\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntIdCodContenido ( p_enticObj ) != (void *) p_cUno )
		{
			printf( "Error caso 8: tras fallar deberia conservar el contenido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		MemLiberar ( (void **) &p_cTres );
		/* Establecer sin Ext usa el destructor fijado con Ext. */
		char * p_cDos = CadDuplicar ( "dos" );
		if ( SEntIdCodEstablecerContenido ( p_enticObj, p_cDos ) != 1 )
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
	SEntIdCodDestruir ( &p_enticObj );
	if ( iNumDestrucciones != 2 )
	{
		printf( "Error caso 11: destruir la entidad deberia usar su destructor: %d\n", iNumDestrucciones );
		iRes = BOOL_VAL_FALSO;
	}

	/* Sobre una entidad nula falla, y el objeto sigue siendo del llamante. */
	char * p_cSuelto = CadDuplicar ( "suelto" );
	if ( SEntIdCodEstablecerContenidoExt ( NULL, p_cSuelto, DestructorContador ) != 0 )
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

static int TestSEntIdCodPtr01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SEntIdCodPtr 01:\n" );
# if ( defined ( MODO_DEPURACION ) )
	unsigned long ulBloquesAntes = MemNumBloquesActuales ();
# endif
	SEntidadIdCod * p_enticObj = SEntIdCodCrearLit ( 3, "COD001", COD_MAX_TAM_DEF );
	SEntIdCodEstablecerContenido ( p_enticObj, CadDuplicar ( "carga" ) );
	SPtr * p_ptrObj = SEntIdCodPtr ( p_enticObj );
	if ( ES_NULO ( p_ptrObj ) )
	{
		printf( "Error caso 1: no se esperaba nulo al crear el SPtr\n" );
		iRes = BOOL_VAL_FALSO;
		SEntIdCodDestruir ( &p_enticObj );
	}
	else
	{
		if ( SPtrEsValido ( p_ptrObj ) != 1 )
		{
			printf( "Error caso 2: el SPtr deberia ser valido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SPtrObjeto ( p_ptrObj ) != p_enticObj )
		{
			printf( "Error caso 3: el SPtr deberia envolver la misma SEntidadIdCod\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* La SEntidadIdCod pasa a ser del SPtr: se libera con el, no por separado. */
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

/* Con objeto nulo, SEntIdCodPtr da un SPtr vacio: hay que destruirlo igualmente.
   Con MODO_DEPURACION se comprueba que no queda memoria reservada. */
static int TestSEntIdCodPtrNulo01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SEntIdCodPtrNulo 01:\n" );
# if ( defined ( MODO_DEPURACION ) )
	unsigned long ulBloquesAntes = MemNumBloquesActuales ();
# endif
	SPtr * p_ptrObj = SEntIdCodPtr ( NULL );
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

int TestSEntidadIdCod ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SEntidadIdCod]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSEntIdCodCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSEntIdCodTieneContenido01 () == BOOL_VAL_CIERTO ) &&
			( TestSEntIdCodCodigoObligatorio01 () == BOOL_VAL_CIERTO ) &&
			( TestSEntIdCodEstablecer01 () == BOOL_VAL_CIERTO ) &&
			( TestSEntIdCodIdentidad01 () == BOOL_VAL_CIERTO ) &&
			( TestSEntIdCodComparar01 () == BOOL_VAL_CIERTO ) &&
			( TestSEntIdCodAsignarContenido01 () == BOOL_VAL_CIERTO ) &&
			( TestSEntIdCodEstablecerContenidoExt01 () == BOOL_VAL_CIERTO ) &&
			( TestSEntIdCodPtr01 () == BOOL_VAL_CIERTO ) &&
			( TestSEntIdCodPtrNulo01 () == BOOL_VAL_CIERTO ) )
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
