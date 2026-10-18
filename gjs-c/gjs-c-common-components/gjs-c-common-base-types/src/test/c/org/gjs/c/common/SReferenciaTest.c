#include "Base.h"

#include "SReferencia.h"



static int AliasEs ( SReferencia * p_refObj, const char * p_cAlias )
{
	return ( CadComparar ( (char *) SRefObtenerAlias ( p_refObj ), (char *) p_cAlias ) == COMP_IGUAL );
}



static int TestSRefCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SRefCrear 01:\n" );

	int iDato = 123;
	SReferencia * p_refObj = SRefCrear ( "ref1", &iDato );
	if ( ES_NULO ( p_refObj ) )
	{
		printf( "Error caso 1: no se esperaba nulo al crear\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SRefEsValida ( p_refObj ) != 1 )
		{
			printf( "Error caso 2: la referencia recien creada deberia ser valida\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ! AliasEs ( p_refObj, "ref1" ) )
		{
			printf( "Error caso 3: el alias deberia ser \"ref1\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SRefObtenerDatos ( p_refObj ) != &iDato )
		{
			printf( "Error caso 4: los datos deberian apuntar al entero dado\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Cambiar el alias ( se duplica el nuevo ). */
		if ( ( SRefEstablecerAlias ( p_refObj, "ref2" ) != 1 ) || ( ! AliasEs ( p_refObj, "ref2" ) ) )
		{
			printf( "Error caso 5: el alias deberia poder cambiarse a \"ref2\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	SRefDestruir ( &p_refObj );

	if ( ES_VALIDO ( p_refObj ) )
	{
		printf( "Error caso 6: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* Crear con alias nulo debe fallar. */
	if ( ES_VALIDO ( SRefCrear ( NULL, &iDato ) ) )
	{
		printf( "Error caso 7: se esperaba nulo al crear con alias nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSRefComparar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SRefComparar 01:\n" );

	int iDato = 1;
	SReferencia * p_r1 = SRefCrear ( "aaa", &iDato );
	SReferencia * p_r2 = SRefCrear ( "bbb", &iDato );
	if ( ES_VALIDO ( p_r1 ) && ES_VALIDO ( p_r2 ) )
	{
		/* Comparacion por alias. */
		if ( SRefEsMenor ( p_r1, p_r2 ) != 1 )
		{
			printf( "Error caso 1: \"aaa\" deberia ser menor que \"bbb\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SRefEsMayor ( p_r2, p_r1 ) != 1 )
		{
			printf( "Error caso 2: \"bbb\" deberia ser mayor que \"aaa\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SRefEsIgualLit ( p_r1, "aaa" ) != 1 )
		{
			printf( "Error caso 3: la referencia deberia ser igual al literal \"aaa\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Mismo alias -> mismo hash. */
		SReferencia * p_r3 = SRefCrear ( "aaa", &iDato );
		if ( ES_VALIDO ( p_r3 ) )
		{
			if ( SRefHash ( p_r1 ) != SRefHash ( p_r3 ) )
			{
				printf( "Error caso 4: dos referencias con el mismo alias deberian tener el mismo hash\n" );
				iRes = BOOL_VAL_FALSO;
			}
			SRefDestruir ( &p_r3 );
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear las referencias\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SRefDestruir ( &p_r1 );
	SRefDestruir ( &p_r2 );
	return ( iRes );
}

static int TestSRefDuplicar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SRefDuplicar 01:\n" );

	int iDato = 7;
	SReferencia * p_refObj = SRefCrear ( "orig", &iDato );
	if ( ES_VALIDO ( p_refObj ) )
	{
		SReferencia * p_refDup = SRefDuplicar ( p_refObj );
		if ( ES_NULO ( p_refDup ) )
		{
			printf( "Error caso 1: no se esperaba nulo al duplicar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		else
		{
			if ( ( SRefEsIgual ( p_refObj, p_refDup ) != 1 ) || ( SRefObtenerDatos ( p_refDup ) != &iDato ) )
			{
				printf( "Error caso 2: el duplicado deberia tener el mismo alias y los mismos datos\n" );
				iRes = BOOL_VAL_FALSO;
			}
			/* Copia independiente del alias: cambiar el original no afecta al duplicado. */
			SRefEstablecerAlias ( p_refObj, "otro" );
			if ( ! AliasEs ( p_refDup, "orig" ) )
			{
				printf( "Error caso 3: el alias del duplicado no deberia cambiar con el original\n" );
				iRes = BOOL_VAL_FALSO;
			}
			SRefDestruir ( &p_refDup );
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la referencia\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SRefDestruir ( &p_refObj );
	return ( iRes );
}

static int TestSRefInvalidos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SRefInvalidos 01:\n" );

	if ( SRefEsValida ( NULL ) != 0 )
	{
		printf( "Error caso 1: una referencia nula no deberia ser valida\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( SRefObtenerAlias ( NULL ) ) )
	{
		printf( "Error caso 2: el alias de una referencia nula deberia ser nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SReferencia * p_refNula = NULL;
	SRefDestruir ( &p_refNula );
	return ( iRes );
}

/* SRefPtr envuelve el objeto en un SPtr con SRefDestruir como destructor: al
   destruir el SPtr se libera tambien el SReferencia. Con MODO_DEPURACION se comprueba
   que no queda memoria reservada. */
static int TestSRefPtr01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SRefPtr 01:\n" );
# if ( defined ( MODO_DEPURACION ) )
	unsigned long ulBloquesAntes = MemNumBloquesActuales ();
# endif
	SReferencia * p_refObj = SRefCrear ( "ref1", (void *) "dato" );
	SPtr * p_ptrObj = SRefPtr ( p_refObj );
	if ( ES_NULO ( p_ptrObj ) )
	{
		printf( "Error caso 1: no se esperaba nulo al crear el SPtr\n" );
		iRes = BOOL_VAL_FALSO;
		SRefDestruir ( &p_refObj );
	}
	else
	{
		if ( SPtrEsValido ( p_ptrObj ) != 1 )
		{
			printf( "Error caso 2: el SPtr deberia ser valido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SPtrObjeto ( p_ptrObj ) != p_refObj )
		{
			printf( "Error caso 3: el SPtr deberia envolver el mismo SReferencia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* El SReferencia pasa a ser del SPtr: se libera con el, no por separado. */
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

/* Con objeto nulo, SRefPtr da un SPtr vacio: hay que destruirlo igualmente.
   Con MODO_DEPURACION se comprueba que no queda memoria reservada. */
static int TestSRefPtrNulo01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SRefPtrNulo 01:\n" );
# if ( defined ( MODO_DEPURACION ) )
	unsigned long ulBloquesAntes = MemNumBloquesActuales ();
# endif
	SPtr * p_ptrObj = SRefPtr ( NULL );
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





int TestSReferencia ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SReferencia]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSRefCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSRefComparar01 () == BOOL_VAL_CIERTO ) &&
			( TestSRefDuplicar01 () == BOOL_VAL_CIERTO ) &&
			( TestSRefInvalidos01 () == BOOL_VAL_CIERTO ) &&
			( TestSRefPtr01 () == BOOL_VAL_CIERTO ) &&
			( TestSRefPtrNulo01 () == BOOL_VAL_CIERTO ) )
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
