#include "Base.h"
#include "Texto.h"

#include "SEntidadCod.h"




static int TestSEntCodCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SEntCodCrear 01:\n" );
# if ( defined ( MODO_DEPURACION ) )
	unsigned long ulBloquesAntes = MemNumBloquesActuales ();
# endif

	/* Por defecto el codigo esta vacio, y un codigo vacio no es valido. */
	SEntidadCod * p_entcObj = SEntCodCrearDef ( COD_MAX_TAM_DEF );
	if ( ES_VALIDO ( p_entcObj ) )
	{
		if ( SEntCodEsValida ( p_entcObj ) != 0 )
		{
			printf( "Error caso 1: con el codigo vacio no deberia ser valida\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la entidad por defecto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SEntCodDestruir ( &p_entcObj );

	/* Con codigo y sin contenido: el contenido es opcional. */
	p_entcObj = SEntCodCrearLit ( "COD001", COD_MAX_TAM_DEF );
	if ( ES_VALIDO ( p_entcObj ) )
	{
		if ( CadComparar ( SEntCodValorCodigoLit ( p_entcObj ), "COD001" ) != COMP_IGUAL )
		{
			printf( "Error caso 2: se esperaba codigo \"COD001\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntCodEsValida ( p_entcObj ) != 1 )
		{
			printf( "Error caso 3: con codigo y sin contenido deberia ser valida\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( SEntCodContenido ( p_entcObj ) ) )
		{
			printf( "Error caso 4: se esperaba contenido nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la entidad con codigo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SEntCodDestruir ( &p_entcObj );

	/* Con contenido: la entidad se queda con el SPtr y lo destruye con ella. */
	char * p_cCarga = CadDuplicar ( "carga" );
	SPtr * p_ptrCarga = SPtrCrearDef ( p_cCarga );
	p_entcObj = SEntCodCrearLitExt ( "COD002", COD_MAX_TAM_DEF, p_ptrCarga );
	if ( ES_VALIDO ( p_entcObj ) )
	{
		if ( SEntCodContenido ( p_entcObj ) != (void *) p_cCarga )
		{
			printf( "Error caso 5: se esperaba el contenido que se paso al crear\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la entidad con contenido\n" );
		iRes = BOOL_VAL_FALSO;
		SPtrDestruir ( &p_ptrCarga );
	}
	SEntCodDestruir ( &p_entcObj );
	if ( ES_VALIDO ( p_entcObj ) )
	{
		printf( "Error caso 6: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}

	/* Sin identificador no hay entidad. */
	p_entcObj = SEntCodEncapsular ( NULL );
	if ( ES_VALIDO ( p_entcObj ) )
	{
		printf( "Error caso 7: encapsular sin codigo deberia dar nulo\n" );
		iRes = BOOL_VAL_FALSO;
		SEntCodDestruir ( &p_entcObj );
	}

	/* Sin SPtr de contenido tampoco; CrearLitExt libera el codigo que habia creado. */
	p_entcObj = SEntCodCrearLitExt ( "COD003", COD_MAX_TAM_DEF, NULL );
	if ( ES_VALIDO ( p_entcObj ) )
	{
		printf( "Error caso 8: crear con SPtr nulo deberia dar nulo\n" );
		iRes = BOOL_VAL_FALSO;
		SEntCodDestruir ( &p_entcObj );
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

static int TestSEntCodEstablecer01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SEntCodEstablecer 01:\n" );
# if ( defined ( MODO_DEPURACION ) )
	unsigned long ulBloquesAntes = MemNumBloquesActuales ();
# endif

	SEntidadCod * p_entcObj = SEntCodCrearLit ( "COD001", COD_MAX_TAM_DEF );
	if ( ES_VALIDO ( p_entcObj ) )
	{
		/* El retorno dice si se guardo, no si la entidad quedo completa. */
		if ( SEntCodEstablecerValorCodigoLit ( p_entcObj, "COD999" ) != 1 )
		{
			printf( "Error caso 1: se esperaba 1 al establecer el codigo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( CadComparar ( SEntCodValorCodigoLit ( p_entcObj ), "COD999" ) != COMP_IGUAL )
		{
			printf( "Error caso 2: se esperaba codigo \"COD999\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Establecer el contenido lo guarda en el SPtr, que destruye el anterior. */
		char * p_cUno = CadDuplicar ( "uno" );
		if ( SEntCodEstablecerContenido ( p_entcObj, p_cUno ) != 1 )
		{
			printf( "Error caso 3: se esperaba 1 al establecer el contenido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntCodContenido ( p_entcObj ) != (void *) p_cUno )
		{
			printf( "Error caso 4: se esperaba el contenido nuevo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntCodEstablecerContenido ( p_entcObj, CadDuplicar ( "dos" ) ) != 1 )
		{
			printf( "Error caso 5: se esperaba 1 al cambiar el contenido\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la entidad\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SEntCodDestruir ( &p_entcObj );

	/* Sobre una entidad nula debe fallar. */
	if ( SEntCodEstablecerValorCodigoLit ( NULL, "COD001" ) != 0 )
	{
		printf( "Error caso 6: establecer sobre una entidad nula deberia fallar\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SEntCodEstablecerContenido ( NULL, NULL ) != 0 )
	{
		printf( "Error caso 7: establecer contenido en una entidad nula deberia fallar\n" );
		iRes = BOOL_VAL_FALSO;
	}
# if ( defined ( MODO_DEPURACION ) )
	/* El contenido sustituido se libero al cambiarlo. */
	if ( MemNumBloquesActuales () != ulBloquesAntes )
	{
		printf( "Error caso 8: quedan %ld bloques sin liberar\n", (long) ( MemNumBloquesActuales () - ulBloquesAntes ) );
		iRes = BOOL_VAL_FALSO;
	}
# endif
	return ( iRes );
}

static int TestSEntCodComparaciones01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SEntCodComparaciones 01:\n" );

	SEntidadCod * p_entcA = SEntCodCrearLit ( "CODA", COD_MAX_TAM_DEF );
	SEntidadCod * p_entcB = SEntCodCrearLit ( "CODB", COD_MAX_TAM_DEF );
	if ( ES_VALIDO ( p_entcA ) && ES_VALIDO ( p_entcB ) )
	{
		if ( SEntCodEsMenor ( p_entcA, p_entcB ) != 1 )
		{
			printf( "Error caso 1: CODA deberia ser menor que CODB\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntCodEsMayor ( p_entcB, p_entcA ) != 1 )
		{
			printf( "Error caso 2: CODB deberia ser mayor que CODA\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntCodEsIgual ( p_entcA, p_entcB ) != 0 )
		{
			printf( "Error caso 3: CODA y CODB no deberian ser iguales\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntCodEsIgualLit ( p_entcA, "CODA" ) != 1 )
		{
			printf( "Error caso 4: deberia ser igual al literal CODA\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntCodComparar ( p_entcA, p_entcB ) != COMP_MENOR )
		{
			printf( "Error caso 5: CODA frente a CODB deberia dar COMP_MENOR: %d\n", SEntCodComparar ( p_entcA, p_entcB ) );
			iRes = BOOL_VAL_FALSO;
		}
		SEntCodEstablecerValorCodigoLit ( p_entcB, "CODA" );
		if ( SEntCodComparar ( p_entcA, p_entcB ) != COMP_IGUAL )
		{
			printf( "Error caso 6: dos codigos iguales deberian dar COMP_IGUAL: %d\n", SEntCodComparar ( p_entcA, p_entcB ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntCodEsIgual ( p_entcA, p_entcB ) != 1 )
		{
			printf( "Error caso 7: deberian ser iguales tras igualar el codigo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Orden con nulos. */
		if ( SEntCodComparar ( p_entcA, NULL ) != COMP_MAYOR )
		{
			printf( "Error caso 8: frente a una entidad nula deberia dar COMP_MAYOR\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntCodComparar ( NULL, p_entcA ) != COMP_MENOR )
		{
			printf( "Error caso 9: una entidad nula deberia dar COMP_MENOR\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntCodComparar ( NULL, NULL ) != COMP_IGUAL )
		{
			printf( "Error caso 10: dos entidades nulas deberian dar COMP_IGUAL\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear las entidades\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SEntCodDestruir ( &p_entcA );
	SEntCodDestruir ( &p_entcB );
	return ( iRes );
}

static int TestSEntCodHash01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SEntCodHash 01:\n" );

	SEntidadCod * p_entcA = SEntCodCrearLit ( "COD001", COD_MAX_TAM_DEF );
	SEntidadCod * p_entcB = SEntCodCrearLit ( "COD001", COD_MAX_TAM_DEF );
	SEntCodEstablecerContenido ( p_entcA, CadDuplicar ( "uno" ) );
	SEntCodEstablecerContenido ( p_entcB, CadDuplicar ( "dos" ) );
	if ( ES_VALIDO ( p_entcA ) && ES_VALIDO ( p_entcB ) )
	{
		/* Contrato hash-igualdad: el contenido no entra en la identidad, asi
		   que tampoco entra en el hash. */
		if ( SEntCodEsIgual ( p_entcA, p_entcB ) != 1 )
		{
			printf( "Error caso 1: mismo codigo deberia ser igual\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntCodHash ( p_entcA ) != SEntCodHash ( p_entcB ) )
		{
			printf( "Error caso 2: entidades iguales deberian tener el mismo hash\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SEntCodEstablecerValorCodigoLit ( p_entcB, "COD999" );
		if ( SEntCodHash ( p_entcA ) == SEntCodHash ( p_entcB ) )
		{
			printf( "Error caso 3: codigos distintos deberian dar hash distinto\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear las entidades\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SEntCodDestruir ( &p_entcA );
	SEntCodDestruir ( &p_entcB );
	return ( iRes );
}



/* SEntCodTieneContenido: 1 con contenido, 0 sin el y 0 con NULL. Destruir libera
   tambien el contenido. */
static int TestSEntCodTieneContenido01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SEntCodTieneContenido 01:\n" );
	void * p_vDato = MemReservar ( 16 );

	SEntidadCod * p_entcObj = SEntCodEncapsularExt ( SCodCrearValorLitExt ( "COD001", COD_MAX_TAM_DEF ), SPtrCrearDef ( p_vDato ) );
	if ( SEntCodTieneContenido ( p_entcObj ) != 1 )
	{
		printf( "Error caso 1: con contenido se esperaba 1\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SEntCodDestruir ( &p_entcObj );

	p_entcObj = SEntCodEncapsular ( SCodCrearValorLitExt ( "COD001", COD_MAX_TAM_DEF ) );
	if ( SEntCodTieneContenido ( p_entcObj ) != 0 )
	{
		printf( "Error caso 2: sin contenido se esperaba 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SEntCodDestruir ( &p_entcObj );

	if ( SEntCodTieneContenido ( NULL ) != 0 )
	{
		printf( "Error caso 3: con NULL se esperaba 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

/* SEntCodAsignarContenido cambia el SPtr entero: destruye el anterior y se queda
   con el nuevo. Con el mismo SPtr que ya tiene no hace nada. */
static int TestSEntCodAsignarContenido01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SEntCodAsignarContenido 01:\n" );
# if ( defined ( MODO_DEPURACION ) )
	unsigned long ulBloquesAntes = MemNumBloquesActuales ();
# endif
	SEntidadCod * p_entcObj = SEntCodCrearLit ( "COD001", COD_MAX_TAM_DEF );
	if ( ES_VALIDO ( p_entcObj ) )
	{
		char * p_cUno = CadDuplicar ( "uno" );
		SPtr * p_ptrUno = SPtrCrearDef ( p_cUno );
		if ( SEntCodAsignarContenido ( p_entcObj, p_ptrUno ) != 1 )
		{
			printf( "Error caso 1: se esperaba 1 al asignar el contenido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntCodContenido ( p_entcObj ) != (void *) p_cUno )
		{
			printf( "Error caso 2: se esperaba el contenido asignado\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntCodAsignarContenido ( p_entcObj, p_ptrUno ) != 1 )
		{
			printf( "Error caso 3: se esperaba 1 al asignar el mismo SPtr\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntCodContenido ( p_entcObj ) != (void *) p_cUno )
		{
			printf( "Error caso 4: asignar el mismo SPtr no deberia destruirlo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		char * p_cDos = CadDuplicar ( "dos" );
		if ( SEntCodAsignarContenido ( p_entcObj, SPtrCrearDef ( p_cDos ) ) != 1 )
		{
			printf( "Error caso 5: se esperaba 1 al asignar otro SPtr\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntCodContenido ( p_entcObj ) != (void *) p_cDos )
		{
			printf( "Error caso 6: se esperaba el contenido del SPtr nuevo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Sin SPtr no se cambia nada. */
		if ( SEntCodAsignarContenido ( p_entcObj, NULL ) != 0 )
		{
			printf( "Error caso 7: asignar un SPtr nulo deberia fallar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntCodContenido ( p_entcObj ) != (void *) p_cDos )
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
	SEntCodDestruir ( &p_entcObj );

	/* Sobre una entidad nula falla, y el SPtr sigue siendo del llamante. */
	SPtr * p_ptrSuelto = SPtrCrearDef ( NULL );
	if ( SEntCodAsignarContenido ( NULL, p_ptrSuelto ) != 0 )
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

/* SEntCodPtr envuelve la entidad en un SPtr con SEntCodDestruir como destructor: al
   destruir el SPtr se libera la entidad y, con ella, su contenido. Con
   MODO_DEPURACION se comprueba que no queda memoria reservada. */
/* Destructor de prueba: cuenta las llamadas y libera como el de por defecto. */
static int iNumDestrucciones = 0;

static void DestructorContador ( void ** p_p_vObj )
{
	iNumDestrucciones = iNumDestrucciones + 1;
	MemLiberar ( p_p_vObj );
}

static int TestSEntCodEstablecerContenidoExt01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SEntCodEstablecerContenidoExt 01:\n" );
# if ( defined ( MODO_DEPURACION ) )
	unsigned long ulBloquesAntes = MemNumBloquesActuales ();
# endif
	iNumDestrucciones = 0;
	SEntidadCod * p_entcObj = SEntCodCrearLit ( "COD001", COD_MAX_TAM_DEF );
	if ( ES_VALIDO ( p_entcObj ) )
	{
		char * p_cUno = CadDuplicar ( "uno" );
		if ( SEntCodEstablecerContenidoExt ( p_entcObj, p_cUno, DestructorContador ) != 1 )
		{
			printf( "Error caso 1: se esperaba 1 al establecer con destructor\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntCodContenido ( p_entcObj ) != (void *) p_cUno )
		{
			printf( "Error caso 2: se esperaba el contenido establecido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Con el mismo objeto solo cambia el destructor: no se destruye. */
		if ( SEntCodEstablecerContenidoExt ( p_entcObj, p_cUno, DestructorContador ) != 1 )
		{
			printf( "Error caso 3: se esperaba 1 al establecer el mismo objeto\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( iNumDestrucciones != 0 )
		{
			printf( "Error caso 4: el mismo objeto no deberia destruirse: %d\n", iNumDestrucciones );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntCodContenido ( p_entcObj ) != (void *) p_cUno )
		{
			printf( "Error caso 5: se esperaba conservar el mismo contenido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Sin destructor falla, tambien con el mismo objeto. */
		if ( SEntCodEstablecerContenidoExt ( p_entcObj, p_cUno, NULL ) != 0 )
		{
			printf( "Error caso 6: sin destructor deberia fallar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		char * p_cTres = CadDuplicar ( "tres" );
		if ( SEntCodEstablecerContenidoExt ( p_entcObj, p_cTres, NULL ) != 0 )
		{
			printf( "Error caso 7: sin destructor deberia fallar con otro objeto\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntCodContenido ( p_entcObj ) != (void *) p_cUno )
		{
			printf( "Error caso 8: tras fallar deberia conservar el contenido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		MemLiberar ( (void **) &p_cTres );
		/* Establecer sin Ext usa el destructor fijado con Ext. */
		char * p_cDos = CadDuplicar ( "dos" );
		if ( SEntCodEstablecerContenido ( p_entcObj, p_cDos ) != 1 )
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
	SEntCodDestruir ( &p_entcObj );
	if ( iNumDestrucciones != 2 )
	{
		printf( "Error caso 11: destruir la entidad deberia usar su destructor: %d\n", iNumDestrucciones );
		iRes = BOOL_VAL_FALSO;
	}

	/* Sobre una entidad nula falla, y el objeto sigue siendo del llamante. */
	char * p_cSuelto = CadDuplicar ( "suelto" );
	if ( SEntCodEstablecerContenidoExt ( NULL, p_cSuelto, DestructorContador ) != 0 )
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

static int TestSEntCodPtr01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SEntCodPtr 01:\n" );
# if ( defined ( MODO_DEPURACION ) )
	unsigned long ulBloquesAntes = MemNumBloquesActuales ();
# endif
	SEntidadCod * p_entcObj = SEntCodCrearLit ( "COD001", COD_MAX_TAM_DEF );
	SEntCodEstablecerContenido ( p_entcObj, CadDuplicar ( "carga" ) );
	SPtr * p_ptrObj = SEntCodPtr ( p_entcObj );
	if ( ES_NULO ( p_ptrObj ) )
	{
		printf( "Error caso 1: no se esperaba nulo al crear el SPtr\n" );
		iRes = BOOL_VAL_FALSO;
		SEntCodDestruir ( &p_entcObj );
	}
	else
	{
		if ( SPtrEsValido ( p_ptrObj ) != 1 )
		{
			printf( "Error caso 2: el SPtr deberia ser valido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SPtrObjeto ( p_ptrObj ) != p_entcObj )
		{
			printf( "Error caso 3: el SPtr deberia envolver la misma SEntidadCod\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* La SEntidadCod pasa a ser del SPtr: se libera con el, no por separado. */
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

/* Con objeto nulo, SEntCodPtr da un SPtr vacio: hay que destruirlo igualmente.
   Con MODO_DEPURACION se comprueba que no queda memoria reservada. */
static int TestSEntCodPtrNulo01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SEntCodPtrNulo 01:\n" );
# if ( defined ( MODO_DEPURACION ) )
	unsigned long ulBloquesAntes = MemNumBloquesActuales ();
# endif
	SPtr * p_ptrObj = SEntCodPtr ( NULL );
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

int TestSEntidadCod ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SEntidadCod]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSEntCodCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSEntCodTieneContenido01 () == BOOL_VAL_CIERTO ) &&
			( TestSEntCodEstablecer01 () == BOOL_VAL_CIERTO ) &&
			( TestSEntCodComparaciones01 () == BOOL_VAL_CIERTO ) &&
			( TestSEntCodHash01 () == BOOL_VAL_CIERTO ) &&
			( TestSEntCodAsignarContenido01 () == BOOL_VAL_CIERTO ) &&
			( TestSEntCodEstablecerContenidoExt01 () == BOOL_VAL_CIERTO ) &&
			( TestSEntCodPtr01 () == BOOL_VAL_CIERTO ) &&
			( TestSEntCodPtrNulo01 () == BOOL_VAL_CIERTO ) )
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
