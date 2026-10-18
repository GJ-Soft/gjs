#include "Base.h"

#include "STexto.h"



static int TestSTxtCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test STxtCrear 01:\n" );

	STexto * p_txtObj = STxtCrear ();
	if ( ES_NULO ( p_txtObj ) )
	{
		printf( "Error caso 1: no se esperaba nulo al crear\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( STxtEsValido ( p_txtObj ) != 1 )
		{
			printf( "Error caso 2: el texto recien creado deberia ser valido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( STxtNumLineas ( p_txtObj ) != 0 )
		{
			printf( "Error caso 3: el texto recien creado deberia tener 0 lineas: %d\n", STxtNumLineas ( p_txtObj ) );
			iRes = BOOL_VAL_FALSO;
		}
	}
	STxtDestruir ( &p_txtObj );

	if ( ES_VALIDO ( p_txtObj ) )
	{
		printf( "Error caso 4: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSTxtInicializar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test STxtInicializar 01:\n" );

	STexto * p_txtObj = STxtCrear ();
	if ( ES_VALIDO ( p_txtObj ) )
	{
		/* El texto se divide en lineas por el salto de linea. */
		STxtInicializar ( p_txtObj, "linea1\nlinea2\nlinea3" );
		if ( STxtNumLineas ( p_txtObj ) != 3 )
		{
			printf( "Error caso 1: se esperaban 3 lineas: %d\n", STxtNumLineas ( p_txtObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCadEsIgualLiteral ( STxtLinea ( p_txtObj, 0 ), "linea1" ) != 1 )
		{
			printf( "Error caso 2: la linea 0 deberia ser \"linea1\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCadEsIgualLiteral ( STxtLinea ( p_txtObj, 2 ), "linea3" ) != 1 )
		{
			printf( "Error caso 3: la linea 2 deberia ser \"linea3\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Vaciar deja el texto sin lineas. */
		STxtVaciar ( p_txtObj );
		if ( STxtNumLineas ( p_txtObj ) != 0 )
		{
			printf( "Error caso 4: el texto deberia quedar sin lineas tras vaciarlo: %d\n", STxtNumLineas ( p_txtObj ) );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el texto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	STxtDestruir ( &p_txtObj );
	return ( iRes );
}

/* STxtPtr envuelve el objeto en un SPtr con STxtDestruir como destructor: al
   destruir el SPtr se libera tambien el STexto. Con MODO_DEPURACION se comprueba
   que no queda memoria reservada. */
static int TestSTxtPtr01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test STxtPtr 01:\n" );
# if ( defined ( MODO_DEPURACION ) )
	unsigned long ulBloquesAntes = MemNumBloquesActuales ();
# endif
	STexto * p_txtObj = STxtCrear ();
	SPtr * p_ptrObj = STxtPtr ( p_txtObj );
	if ( ES_NULO ( p_ptrObj ) )
	{
		printf( "Error caso 1: no se esperaba nulo al crear el SPtr\n" );
		iRes = BOOL_VAL_FALSO;
		STxtDestruir ( &p_txtObj );
	}
	else
	{
		if ( SPtrEsValido ( p_ptrObj ) != 1 )
		{
			printf( "Error caso 2: el SPtr deberia ser valido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SPtrObjeto ( p_ptrObj ) != p_txtObj )
		{
			printf( "Error caso 3: el SPtr deberia envolver el mismo STexto\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* El STexto pasa a ser del SPtr: se libera con el, no por separado. */
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

/* Con objeto nulo, STxtPtr da un SPtr vacio: hay que destruirlo igualmente.
   Con MODO_DEPURACION se comprueba que no queda memoria reservada. */
static int TestSTxtPtrNulo01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test STxtPtrNulo 01:\n" );
# if ( defined ( MODO_DEPURACION ) )
	unsigned long ulBloquesAntes = MemNumBloquesActuales ();
# endif
	SPtr * p_ptrObj = STxtPtr ( NULL );
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





int TestSTexto ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test STexto]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSTxtCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSTxtInicializar01 () == BOOL_VAL_CIERTO ) &&
			( TestSTxtPtr01 () == BOOL_VAL_CIERTO ) &&
			( TestSTxtPtrNulo01 () == BOOL_VAL_CIERTO ) )
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
