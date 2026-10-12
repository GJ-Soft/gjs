#include "Base.h"

#include "SEntidad.h"





static int TestSEntCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	char cCarga [] = "carga";
	printf( "Test SEntCrear 01:\n" );

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

	/* Con contenido: destruir lo devuelve sin tocarlo y anula el puntero. */
	p_entObj = SEntCrearExt ( 7, cCarga );
	if ( ES_VALIDO ( p_entObj ) )
	{
		if ( SEntContenido ( p_entObj ) != (void *) cCarga )
		{
			printf( "Error caso 6: se esperaba el contenido que se paso al crear\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la entidad con contenido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SEntDestruir ( &p_entObj ) != (void *) cCarga )
	{
		printf( "Error caso 7: destruir deberia devolver el contenido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( p_entObj ) )
	{
		printf( "Error caso 8: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
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
	char cUno [] = "uno";
	char cDos [] = "dos";
	printf( "Test SEntEstablecer 01:\n" );

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
		/* Establecer el contenido devuelve el anterior. */
		if ( ES_VALIDO ( SEntEstablecerContenido ( p_entObj, cUno ) ) )
		{
			printf( "Error caso 6: el contenido anterior deberia ser nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntEstablecerContenido ( p_entObj, cDos ) != (void *) cUno )
		{
			printf( "Error caso 7: se esperaba recuperar el contenido anterior\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntContenido ( p_entObj ) != (void *) cDos )
		{
			printf( "Error caso 8: se esperaba el contenido nuevo\n" );
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
		printf( "Error caso 9: establecer sobre una entidad nula deberia fallar\n" );
		iRes = BOOL_VAL_FALSO;
	}
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
	char cUno [] = "uno";
	char cDos [] = "dos";
	printf( "Test SEntHash 01:\n" );

	SEntidad * p_entA = SEntCrearExt ( 12345, cUno );
	SEntidad * p_entB = SEntCrearExt ( 12345, cDos );
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



/* SEntTieneContenido: 1 con contenido, 0 sin el y 0 con NULL. Destruir devuelve
   el contenido sin liberarlo, asi que lo libera el test. */
static int TestSEntTieneContenido01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SEntTieneContenido 01:\n" );
	void * p_vDato = MemReservar ( 16 );

	SEntidad * p_entObj = SEntEncapsularExt ( SIdCrear ( 9 ), p_vDato );
	if ( SEntTieneContenido ( p_entObj ) != 1 )
	{
		printf( "Error caso 1: con contenido se esperaba 1\n" );
		iRes = BOOL_VAL_FALSO;
	}
	void * p_vDevuelto = SEntDestruir ( &p_entObj );
	MemLiberar ( &p_vDevuelto );

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

int TestSEntidad ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SEntidad]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSEntCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSEntTieneContenido01 () == BOOL_VAL_CIERTO ) &&
			( TestSEntEncapsular01 () == BOOL_VAL_CIERTO ) &&
			( TestSEntEstablecer01 () == BOOL_VAL_CIERTO ) &&
			( TestSEntComparaciones01 () == BOOL_VAL_CIERTO ) &&
			( TestSEntHash01 () == BOOL_VAL_CIERTO ) )
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
