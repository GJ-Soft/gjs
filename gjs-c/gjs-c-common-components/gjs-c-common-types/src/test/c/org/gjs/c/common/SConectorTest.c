#include "Base.h"

#include "SConector.h"



static int TestSCnctCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCnctCrear 01:\n" );
	byte * p_byObjeto = (byte *) MemReservar ( 8 );
	SConector * p_cnctObj = SCnctCrearExt ( p_byObjeto, 7 );
	if ( ES_VALIDO ( p_cnctObj ) )
	{
		if ( SCnctObjeto ( p_cnctObj ) != p_byObjeto )
		{
			printf( "Error caso 1: el objeto no coincide\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCnctTipo ( p_cnctObj ) != 7 )
		{
			printf( "Error caso 2: se esperaba tipo 7: %d\n", SCnctTipo ( p_cnctObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCnctEsValido ( p_cnctObj ) != 1 )
		{
			printf( "Error caso 3: se esperaba valido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SCnctEstablecerTipo ( p_cnctObj, 3 );
		if ( SCnctTipo ( p_cnctObj ) != 3 )
		{
			printf( "Error caso 4: se esperaba tipo 3: %d\n", SCnctTipo ( p_cnctObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		/* SCnctDestruir solo libera el conector: el contenido sigue siendo nuestro. */
		SCnctDestruir ( &p_cnctObj );
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el objeto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	MemLiberar ( (void **) &p_byObjeto );
	return ( iRes );
}

/* SCnctDestruir libera solo el conector y SCnctDestruirExt ( ..., 1 ) tambien el
   contenido. Se comprueba por el numero de bloques, asi que solo con
   MODO_DEPURACION. */
static int TestSCnctDestruir01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCnctDestruir 01:\n" );
# if ( defined ( MODO_DEPURACION ) )
	unsigned long ulBloquesAntes = MemNumBloquesActuales ();
	byte * p_byObjeto = (byte *) MemReservar ( 8 );
	SConector * p_cnctObj = SCnctCrear ( p_byObjeto );
	SCnctDestruir ( &p_cnctObj );
	if ( ES_VALIDO ( p_cnctObj ) )
	{
		printf( "Error caso 1: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( MemNumBloquesActuales () != ulBloquesAntes + 1 )
	{
		printf( "Error caso 2: SCnctDestruir no deberia liberar el contenido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	MemLiberar ( (void **) &p_byObjeto );

	p_byObjeto = (byte *) MemReservar ( 8 );
	p_cnctObj = SCnctCrear ( p_byObjeto );
	SCnctDestruirExt ( &p_cnctObj, 1 );
	if ( ES_VALIDO ( p_cnctObj ) )
	{
		printf( "Error caso 3: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( MemNumBloquesActuales () != ulBloquesAntes )
	{
		printf( "Error caso 4: SCnctDestruirExt ( ..., 1 ) deberia liberar el contenido\n" );
		iRes = BOOL_VAL_FALSO;
	}
# endif
	return ( iRes );
}

static int TestSCnctCrear02 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCnctCrear 02:\n" );
	byte * p_byObjeto = (byte *) MemReservar ( 8 );
	SConector * p_cnctObj = SCnctCrear ( p_byObjeto );
	if ( ES_VALIDO ( p_cnctObj ) )
	{
		if ( SCnctTipo ( p_cnctObj ) != 0 )
		{
			printf( "Error caso 1: se esperaba tipo por defecto 0: %d\n", SCnctTipo ( p_cnctObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCnctEsValido ( p_cnctObj ) != 1 )
		{
			printf( "Error caso 2: se esperaba valido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SCnctLimpiar ( p_cnctObj );
		if ( ES_VALIDO ( SCnctObjeto ( p_cnctObj ) ) )
		{
			printf( "Error caso 3: se esperaba objeto nulo tras limpiar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCnctEsValido ( p_cnctObj ) != 0 )
		{
			printf( "Error caso 4: se esperaba no valido tras limpiar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* El contenido ya se ha desligado con limpiar: no destruirlo desde el conector. */
		SCnctDestruirExt ( &p_cnctObj, 0 );
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el objeto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	MemLiberar ( (void **) &p_byObjeto );
	return ( iRes );
}

static int TestSCnctNulo01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCnctNulo 01:\n" );
	if ( ES_VALIDO ( SCnctObjeto ( NULL ) ) )
	{
		printf( "Error caso 1: se esperaba objeto nulo con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SCnctTipo ( NULL ) != 0 )
	{
		printf( "Error caso 2: se esperaba tipo 0 con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SCnctEsValido ( NULL ) != 0 )
	{
		printf( "Error caso 3: se esperaba no valido con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SCnctEstablecerTipo ( NULL, 1 ) != 0 )
	{
		printf( "Error caso 4: se esperaba fallo con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

/* SCnctPtr envuelve el objeto en un SPtr con SCnctDestruir como destructor: al
   destruir el SPtr se libera tambien el SConector, pero no su contenido, que se
   libera aparte. Con MODO_DEPURACION se comprueba que no queda memoria reservada. */
static int TestSCnctPtr01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCnctPtr 01:\n" );
# if ( defined ( MODO_DEPURACION ) )
	unsigned long ulBloquesAntes = MemNumBloquesActuales ();
# endif
	byte * p_byObjeto = (byte *) MemReservar ( 8 );
	SConector * p_cnctObj = SCnctCrear ( p_byObjeto );
	SPtr * p_ptrObj = SCnctPtr ( p_cnctObj );
	if ( ES_NULO ( p_ptrObj ) )
	{
		printf( "Error caso 1: no se esperaba nulo al crear el SPtr\n" );
		iRes = BOOL_VAL_FALSO;
		SCnctDestruir ( &p_cnctObj );
	}
	else
	{
		if ( SPtrEsValido ( p_ptrObj ) != 1 )
		{
			printf( "Error caso 2: el SPtr deberia ser valido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SPtrObjeto ( p_ptrObj ) != p_cnctObj )
		{
			printf( "Error caso 3: el SPtr deberia envolver el mismo SConector\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* El SConector pasa a ser del SPtr: se libera con el, no por separado. */
		SPtrDestruir ( &p_ptrObj );
		if ( ES_VALIDO ( p_ptrObj ) )
		{
			printf( "Error caso 4: se esperaba puntero nulo tras destruir\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	MemLiberar ( (void **) &p_byObjeto );
# if ( defined ( MODO_DEPURACION ) )
	if ( MemNumBloquesActuales () != ulBloquesAntes )
	{
		printf( "Error caso 5: quedan %ld bloques sin liberar\n", (long) ( MemNumBloquesActuales () - ulBloquesAntes ) );
		iRes = BOOL_VAL_FALSO;
	}
# endif
	return ( iRes );
}

/* Con objeto nulo, SCnctPtr da un SPtr vacio: hay que destruirlo igualmente.
   Con MODO_DEPURACION se comprueba que no queda memoria reservada. */
static int TestSCnctPtrNulo01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCnctPtrNulo 01:\n" );
# if ( defined ( MODO_DEPURACION ) )
	unsigned long ulBloquesAntes = MemNumBloquesActuales ();
# endif
	SPtr * p_ptrObj = SCnctPtr ( NULL );
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



int TestSConector ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SConector]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSCnctCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSCnctCrear02 () == BOOL_VAL_CIERTO ) &&
			( TestSCnctDestruir01 () == BOOL_VAL_CIERTO ) &&
			( TestSCnctNulo01 () == BOOL_VAL_CIERTO ) &&
			( TestSCnctPtr01 () == BOOL_VAL_CIERTO ) &&
			( TestSCnctPtrNulo01 () == BOOL_VAL_CIERTO ) )
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
