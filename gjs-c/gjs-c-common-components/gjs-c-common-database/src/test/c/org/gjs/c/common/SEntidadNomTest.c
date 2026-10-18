#include "Base.h"

#include "SEntidadNom.h"



static int TestSEntNomCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SEntNomCrear 01:\n" );
# if ( defined ( MODO_DEPURACION ) )
	unsigned long ulBloquesAntes = MemNumBloquesActuales ();
# endif

	/* Por defecto: id 0 y nombre vacio, asi que aun no es valida. */
	SEntidadNom * p_entnObj = SEntNomCrearDef ();
	if ( ES_VALIDO ( p_entnObj ) )
	{
		if ( SEntNomValorId ( p_entnObj ) != 0 )
		{
			printf( "Error caso 1: se esperaba id 0: %lu\n", SEntNomValorId ( p_entnObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntNomEsValida ( p_entnObj ) != 0 )
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
	SEntNomDestruir ( &p_entnObj );

	/* Con id y nombre. La validez la da el identificador, no el nombre. */
	p_entnObj = SEntNomCrearLit ( 42, "cliente_uno" );
	if ( ES_VALIDO ( p_entnObj ) )
	{
		if ( SEntNomValorId ( p_entnObj ) != 42 )
		{
			printf( "Error caso 3: se esperaba id 42: %lu\n", SEntNomValorId ( p_entnObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( CadComparar ( SEntNomValorNombreLit ( p_entnObj ), "cliente_uno" ) != COMP_IGUAL )
		{
			printf( "Error caso 4: se esperaba nombre \"cliente_uno\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntNomEsValida ( p_entnObj ) != 1 )
		{
			printf( "Error caso 5: con id asignado deberia ser valida\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_NULO ( SEntNomBase ( p_entnObj ) ) )
		{
			printf( "Error caso 6: se esperaba la entidad base\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la entidad con nombre\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SEntNomDestruir ( &p_entnObj );

	/* Con contenido: la entidad se queda con el SPtr y lo destruye con ella. */
	char * p_cCarga = CadDuplicar ( "carga" );
	SPtr * p_ptrCarga = SPtrCrearDef ( p_cCarga );
	p_entnObj = SEntNomCrearLitExt ( 7, "cliente_dos", p_ptrCarga );
	if ( ES_VALIDO ( p_entnObj ) )
	{
		if ( SEntNomContenido ( p_entnObj ) != (void *) p_cCarga )
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
	SEntNomDestruir ( &p_entnObj );
	if ( ES_VALIDO ( p_entnObj ) )
	{
		printf( "Error caso 8: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}

	/* Sin SPtr de contenido no hay entidad; SEntNomCrearLitExt libera lo que habia creado. */
	p_entnObj = SEntNomCrearLitExt ( 7, "cliente_dos", NULL );
	if ( ES_VALIDO ( p_entnObj ) )
	{
		printf( "Error caso 9: crear con SPtr nulo deberia dar nulo\n" );
		iRes = BOOL_VAL_FALSO;
		SEntNomDestruir ( &p_entnObj );
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

static int TestSEntNomNombreOpcional01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SEntNomNombreOpcional 01:\n" );

	/* Un nombre con blancos no supera la validacion de SNombre. La entidad se
	   crea igualmente: solo se exige el id, y en lugar del nombre invalido se
	   pone uno vacio. */
	SEntidadNom * p_entnObj = SEntNomCrearLit ( 5, "con blanco" );
	if ( ES_VALIDO ( p_entnObj ) )
	{
		if ( ES_NULO ( SEntNomNombre ( p_entnObj ) ) )
		{
			printf( "Error caso 1: se esperaba un SNombre vacio, no nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( CadLongitud ( SEntNomValorNombreLit ( p_entnObj ) ) != 0 )
		{
			printf( "Error caso 2: se esperaba el nombre vacio\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Vacio no es lo mismo que valido: el nombre no pasa SNomEsValido. */
		if ( SNomEsValido ( SEntNomNombre ( p_entnObj ) ) != 0 )
		{
			printf( "Error caso 3: un nombre vacio no deberia ser valido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Pero la entidad si lo es: la validez es cosa del identificador. */
		if ( SEntNomEsValida ( p_entnObj ) != 1 )
		{
			printf( "Error caso 4: deberia ser valida aunque el nombre este vacio\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Y como el SNombre existe, se le puede poner uno despues. */
		if ( SEntNomEstablecerValorNombreLit ( p_entnObj, "cliente_uno" ) != 1 )
		{
			printf( "Error caso 5: se esperaba poder establecer el nombre despues\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( CadComparar ( SEntNomValorNombreLit ( p_entnObj ), "cliente_uno" ) != COMP_IGUAL )
		{
			printf( "Error caso 6: se esperaba nombre \"cliente_uno\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la entidad\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SEntNomDestruir ( &p_entnObj );

	/* Sin identificador no hay entidad, aunque el nombre sea correcto. Y al
	   fallar, Encapsular no se queda con el nombre: sigue siendo del llamante,
	   que es quien lo destruye. */
	SNombre * p_nomSuelto = SNomCrearValorLit ( "cliente_uno" );
	p_entnObj = SEntNomEncapsular ( NULL, p_nomSuelto );
	if ( ES_VALIDO ( p_entnObj ) )
	{
		printf( "Error caso 7: encapsular sin id deberia dar nulo\n" );
		iRes = BOOL_VAL_FALSO;
		SEntNomDestruir ( &p_entnObj );
	}
	SNomDestruir ( &p_nomSuelto );
	return ( iRes );
}

static int TestSEntNomEstablecer01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SEntNomEstablecer 01:\n" );

	SEntidadNom * p_entnObj = SEntNomCrearLit ( 1, "cliente_uno" );
	if ( ES_VALIDO ( p_entnObj ) )
	{
		if ( SEntNomEstablecerValorId ( p_entnObj, 99 ) != 1 )
		{
			printf( "Error caso 1: se esperaba 1 al establecer el valor del id\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntNomValorId ( p_entnObj ) != 99 )
		{
			printf( "Error caso 2: se esperaba id 99: %lu\n", SEntNomValorId ( p_entnObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntNomEstablecerValorNombreLit ( p_entnObj, "cliente_dos" ) != 1 )
		{
			printf( "Error caso 3: se esperaba 1 al establecer el nombre\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( CadComparar ( SEntNomValorNombreLit ( p_entnObj ), "cliente_dos" ) != COMP_IGUAL )
		{
			printf( "Error caso 4: se esperaba nombre \"cliente_dos\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* El cambio de id se ve tambien desde la base, que es el mismo objeto. */
		if ( SEntValorId ( SEntNomBase ( p_entnObj ) ) != 99 )
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
	SEntNomDestruir ( &p_entnObj );
	return ( iRes );
}

static int TestSEntNomIdentidad01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SEntNomIdentidad 01:\n" );

	/* Mismo id y distinto nombre: la identidad es el id, y nada mas. */
	SEntidadNom * p_entnA = SEntNomCrearLit ( 10, "cliente_uno" );
	SEntidadNom * p_entnB = SEntNomCrearLit ( 10, "cliente_dos" );
	if ( ES_VALIDO ( p_entnA ) && ES_VALIDO ( p_entnB ) )
	{
		if ( SEntNomEsIgual ( p_entnA, p_entnB ) != 1 )
		{
			printf( "Error caso 1: mismo id deberia ser igual pese al nombre\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Contrato hash-igualdad: si son iguales, mismo hash. El nombre es
		   mutable, asi que no puede entrar en el reparto. */
		if ( SEntNomHash ( p_entnA ) != SEntNomHash ( p_entnB ) )
		{
			printf( "Error caso 2: entidades iguales deberian tener el mismo hash\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Y reparte igual que su base, para poder convivir en la misma tabla. */
		if ( SEntNomHash ( p_entnA ) != SEntHash ( SEntNomBase ( p_entnA ) ) )
		{
			printf( "Error caso 3: deberia repartir igual que su entidad base\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Cambiar el nombre no cambia ni la identidad ni el hash. */
		SEntNomEstablecerValorNombreLit ( p_entnA, "cliente_tres" );
		if ( SEntNomHash ( p_entnA ) != SEntNomHash ( p_entnB ) )
		{
			printf( "Error caso 4: cambiar el nombre no deberia cambiar el hash\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Ids distintos: ya no son iguales. */
		SEntNomEstablecerValorId ( p_entnB, 20 );
		if ( SEntNomEsIgual ( p_entnA, p_entnB ) != 0 )
		{
			printf( "Error caso 5: ids distintos no deberian ser iguales\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntNomEsMenor ( p_entnA, p_entnB ) != 1 )
		{
			printf( "Error caso 6: 10 deberia ser menor que 20\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntNomEsIgualNum ( p_entnA, 10 ) != 1 )
		{
			printf( "Error caso 7: deberia ser igual a 10\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Contra la clase base, por el id. */
		if ( SEntNomEsIgualEnt ( p_entnA, SEntNomBase ( p_entnB ) ) != 0 )
		{
			printf( "Error caso 8: no deberia ser igual a una base con otro id\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear las entidades\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SEntNomDestruir ( &p_entnA );
	SEntNomDestruir ( &p_entnB );
	return ( iRes );
}

static int TestSEntNomComparar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SEntNomComparar 01:\n" );

	/* Nombres "cliente_a" y "cliente_b" para que el orden alfabetico del
	   desempate no dependa de como se lean. */
	SEntidadNom * p_entnA = SEntNomCrearLit ( 10, "cliente_a" );
	SEntidadNom * p_entnB = SEntNomCrearLit ( 20, "cliente_b" );
	if ( ES_VALIDO ( p_entnA ) && ES_VALIDO ( p_entnB ) )
	{
		if ( SEntNomComparar ( p_entnA, p_entnB ) != COMP_MENOR )
		{
			printf( "Error caso 1: 10 frente a 20 deberia dar COMP_MENOR: %d\n", SEntNomComparar ( p_entnA, p_entnB ) );
			iRes = BOOL_VAL_FALSO;
		}
		/* Con el mismo id, Comparar desempata por nombre. Es deliberado y
		   provisional: sirve para ordenar listas cuyos ids aun no estan
		   asignados o estan repetidos. No es el criterio de identidad, que es
		   solo el id: por eso EsIgual sigue diciendo que son iguales. */
		SEntNomEstablecerValorId ( p_entnB, 10 );
		if ( SEntNomComparar ( p_entnA, p_entnB ) != COMP_MENOR )
		{
			printf( "Error caso 2: con el mismo id deberia desempatar por nombre: %d\n", SEntNomComparar ( p_entnA, p_entnB ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntNomEsIgual ( p_entnA, p_entnB ) != 1 )
		{
			printf( "Error caso 3: el desempate no deberia afectar a EsIgual\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Mismo id y mismo nombre: iguales tambien para Comparar. */
		SEntNomEstablecerValorNombreLit ( p_entnB, "cliente_a" );
		if ( SEntNomComparar ( p_entnA, p_entnB ) != COMP_IGUAL )
		{
			printf( "Error caso 4: mismo id y nombre deberia dar COMP_IGUAL: %d\n", SEntNomComparar ( p_entnA, p_entnB ) );
			iRes = BOOL_VAL_FALSO;
		}
		/* Orden con nulos. */
		if ( SEntNomComparar ( p_entnA, NULL ) != COMP_MAYOR )
		{
			printf( "Error caso 5: frente a una entidad nula deberia dar COMP_MAYOR\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntNomComparar ( NULL, p_entnA ) != COMP_MENOR )
		{
			printf( "Error caso 6: una entidad nula deberia dar COMP_MENOR\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntNomComparar ( NULL, NULL ) != COMP_IGUAL )
		{
			printf( "Error caso 7: dos entidades nulas deberian dar COMP_IGUAL\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntNomCompararNum ( p_entnA, 5 ) != COMP_MAYOR )
		{
			printf( "Error caso 8: 10 frente a 5 deberia dar COMP_MAYOR: %d\n", SEntNomCompararNum ( p_entnA, 5 ) );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear las entidades\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SEntNomDestruir ( &p_entnA );
	SEntNomDestruir ( &p_entnB );
	return ( iRes );
}



/* SEntNomTieneContenido: 1 con contenido, 0 sin el y 0 con NULL. Destruir libera
   tambien el contenido. */
static int TestSEntNomTieneContenido01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SEntNomTieneContenido 01:\n" );
	void * p_vDato = MemReservar ( 16 );

	SEntidadNom * p_entnObj = SEntNomEncapsularExt ( SIdCrear ( 9 ), SNomCrearValorLit ( "cliente_a" ), SPtrCrearDef ( p_vDato ) );
	if ( SEntNomTieneContenido ( p_entnObj ) != 1 )
	{
		printf( "Error caso 1: con contenido se esperaba 1\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SEntNomDestruir ( &p_entnObj );

	p_entnObj = SEntNomEncapsular ( SIdCrear ( 9 ), SNomCrearValorLit ( "cliente_a" ) );
	if ( SEntNomTieneContenido ( p_entnObj ) != 0 )
	{
		printf( "Error caso 2: sin contenido se esperaba 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SEntNomDestruir ( &p_entnObj );

	if ( SEntNomTieneContenido ( NULL ) != 0 )
	{
		printf( "Error caso 3: con NULL se esperaba 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

/* SEntNomAsignarContenido cambia el SPtr entero: destruye el anterior y se queda
   con el nuevo. Con el mismo SPtr que ya tiene no hace nada. */
static int TestSEntNomAsignarContenido01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SEntNomAsignarContenido 01:\n" );
# if ( defined ( MODO_DEPURACION ) )
	unsigned long ulBloquesAntes = MemNumBloquesActuales ();
# endif
	SEntidadNom * p_entnObj = SEntNomCrearLit ( 3, "cliente_a" );
	if ( ES_VALIDO ( p_entnObj ) )
	{
		char * p_cUno = CadDuplicar ( "uno" );
		SPtr * p_ptrUno = SPtrCrearDef ( p_cUno );
		if ( SEntNomAsignarContenido ( p_entnObj, p_ptrUno ) != 1 )
		{
			printf( "Error caso 1: se esperaba 1 al asignar el contenido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntNomContenido ( p_entnObj ) != (void *) p_cUno )
		{
			printf( "Error caso 2: se esperaba el contenido asignado\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntNomAsignarContenido ( p_entnObj, p_ptrUno ) != 1 )
		{
			printf( "Error caso 3: se esperaba 1 al asignar el mismo SPtr\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntNomContenido ( p_entnObj ) != (void *) p_cUno )
		{
			printf( "Error caso 4: asignar el mismo SPtr no deberia destruirlo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		char * p_cDos = CadDuplicar ( "dos" );
		if ( SEntNomAsignarContenido ( p_entnObj, SPtrCrearDef ( p_cDos ) ) != 1 )
		{
			printf( "Error caso 5: se esperaba 1 al asignar otro SPtr\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntNomContenido ( p_entnObj ) != (void *) p_cDos )
		{
			printf( "Error caso 6: se esperaba el contenido del SPtr nuevo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Sin SPtr no se cambia nada. */
		if ( SEntNomAsignarContenido ( p_entnObj, NULL ) != 0 )
		{
			printf( "Error caso 7: asignar un SPtr nulo deberia fallar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntNomContenido ( p_entnObj ) != (void *) p_cDos )
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
	SEntNomDestruir ( &p_entnObj );

	/* Sobre una entidad nula falla, y el SPtr sigue siendo del llamante. */
	SPtr * p_ptrSuelto = SPtrCrearDef ( NULL );
	if ( SEntNomAsignarContenido ( NULL, p_ptrSuelto ) != 0 )
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

/* SEntNomPtr envuelve la entidad en un SPtr con SEntNomDestruir como destructor: al
   destruir el SPtr se libera la entidad y, con ella, su contenido. Con
   MODO_DEPURACION se comprueba que no queda memoria reservada. */
/* Destructor de prueba: cuenta las llamadas y libera como el de por defecto. */
static int iNumDestrucciones = 0;

static void DestructorContador ( void ** p_p_vObj )
{
	iNumDestrucciones = iNumDestrucciones + 1;
	MemLiberar ( p_p_vObj );
}

static int TestSEntNomEstablecerContenidoExt01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SEntNomEstablecerContenidoExt 01:\n" );
# if ( defined ( MODO_DEPURACION ) )
	unsigned long ulBloquesAntes = MemNumBloquesActuales ();
# endif
	iNumDestrucciones = 0;
	SEntidadNom * p_entnObj = SEntNomCrearLit ( 3, "cliente_a" );
	if ( ES_VALIDO ( p_entnObj ) )
	{
		char * p_cUno = CadDuplicar ( "uno" );
		if ( SEntNomEstablecerContenidoExt ( p_entnObj, p_cUno, DestructorContador ) != 1 )
		{
			printf( "Error caso 1: se esperaba 1 al establecer con destructor\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntNomContenido ( p_entnObj ) != (void *) p_cUno )
		{
			printf( "Error caso 2: se esperaba el contenido establecido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Con el mismo objeto solo cambia el destructor: no se destruye. */
		if ( SEntNomEstablecerContenidoExt ( p_entnObj, p_cUno, DestructorContador ) != 1 )
		{
			printf( "Error caso 3: se esperaba 1 al establecer el mismo objeto\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( iNumDestrucciones != 0 )
		{
			printf( "Error caso 4: el mismo objeto no deberia destruirse: %d\n", iNumDestrucciones );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntNomContenido ( p_entnObj ) != (void *) p_cUno )
		{
			printf( "Error caso 5: se esperaba conservar el mismo contenido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Sin destructor falla, tambien con el mismo objeto. */
		if ( SEntNomEstablecerContenidoExt ( p_entnObj, p_cUno, NULL ) != 0 )
		{
			printf( "Error caso 6: sin destructor deberia fallar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		char * p_cTres = CadDuplicar ( "tres" );
		if ( SEntNomEstablecerContenidoExt ( p_entnObj, p_cTres, NULL ) != 0 )
		{
			printf( "Error caso 7: sin destructor deberia fallar con otro objeto\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntNomContenido ( p_entnObj ) != (void *) p_cUno )
		{
			printf( "Error caso 8: tras fallar deberia conservar el contenido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		MemLiberar ( (void **) &p_cTres );
		/* Establecer sin Ext usa el destructor fijado con Ext. */
		char * p_cDos = CadDuplicar ( "dos" );
		if ( SEntNomEstablecerContenido ( p_entnObj, p_cDos ) != 1 )
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
	SEntNomDestruir ( &p_entnObj );
	if ( iNumDestrucciones != 2 )
	{
		printf( "Error caso 11: destruir la entidad deberia usar su destructor: %d\n", iNumDestrucciones );
		iRes = BOOL_VAL_FALSO;
	}

	/* Sobre una entidad nula falla, y el objeto sigue siendo del llamante. */
	char * p_cSuelto = CadDuplicar ( "suelto" );
	if ( SEntNomEstablecerContenidoExt ( NULL, p_cSuelto, DestructorContador ) != 0 )
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

static int TestSEntNomPtr01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SEntNomPtr 01:\n" );
# if ( defined ( MODO_DEPURACION ) )
	unsigned long ulBloquesAntes = MemNumBloquesActuales ();
# endif
	SEntidadNom * p_entnObj = SEntNomCrearLit ( 3, "cliente_a" );
	SEntNomEstablecerContenido ( p_entnObj, CadDuplicar ( "carga" ) );
	SPtr * p_ptrObj = SEntNomPtr ( p_entnObj );
	if ( ES_NULO ( p_ptrObj ) )
	{
		printf( "Error caso 1: no se esperaba nulo al crear el SPtr\n" );
		iRes = BOOL_VAL_FALSO;
		SEntNomDestruir ( &p_entnObj );
	}
	else
	{
		if ( SPtrEsValido ( p_ptrObj ) != 1 )
		{
			printf( "Error caso 2: el SPtr deberia ser valido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SPtrObjeto ( p_ptrObj ) != p_entnObj )
		{
			printf( "Error caso 3: el SPtr deberia envolver la misma SEntidadNom\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* La SEntidadNom pasa a ser del SPtr: se libera con el, no por separado. */
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

/* Con objeto nulo, SEntNomPtr da un SPtr vacio: hay que destruirlo igualmente.
   Con MODO_DEPURACION se comprueba que no queda memoria reservada. */
static int TestSEntNomPtrNulo01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SEntNomPtrNulo 01:\n" );
# if ( defined ( MODO_DEPURACION ) )
	unsigned long ulBloquesAntes = MemNumBloquesActuales ();
# endif
	SPtr * p_ptrObj = SEntNomPtr ( NULL );
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

int TestSEntidadNom ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SEntidadNom]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSEntNomCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSEntNomTieneContenido01 () == BOOL_VAL_CIERTO ) &&
			( TestSEntNomNombreOpcional01 () == BOOL_VAL_CIERTO ) &&
			( TestSEntNomEstablecer01 () == BOOL_VAL_CIERTO ) &&
			( TestSEntNomIdentidad01 () == BOOL_VAL_CIERTO ) &&
			( TestSEntNomComparar01 () == BOOL_VAL_CIERTO ) &&
			( TestSEntNomAsignarContenido01 () == BOOL_VAL_CIERTO ) &&
			( TestSEntNomEstablecerContenidoExt01 () == BOOL_VAL_CIERTO ) &&
			( TestSEntNomPtr01 () == BOOL_VAL_CIERTO ) &&
			( TestSEntNomPtrNulo01 () == BOOL_VAL_CIERTO ) )
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
