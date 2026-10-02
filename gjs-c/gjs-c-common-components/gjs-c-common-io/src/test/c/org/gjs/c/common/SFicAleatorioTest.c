#include "Base.h"

#include "SFicAleatorio.h"
#include "SistemaFicheros.h"
#include "TestConfig.h"



static int TestSFicAlEscribirLeer01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SFicAlEscribirLeer 01:\n" );
	SisCrearDirectorio ( FIC_TEST_DIR_RESULTS );
	SFicAleatorio * p_ficObj = SFicAlCrear ( FIC_TEST_DIR_RESULTS "/sfal_test.bin" );
	if ( ES_VALIDO ( p_ficObj ) )
	{
		/* Apertura en modo lectura/escritura, vaciando el fichero. */
		if ( SFicAlAbrirExt ( p_ficObj, 1 ) != 1 )
		{
			printf( "Error caso 1: no se pudo abrir el fichero\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SFicAlEstaAbierto ( p_ficObj ) != 1 )
		{
			printf( "Error caso 2: se esperaba abierto\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Escritura en posiciones concretas (acceso aleatorio). */
		if ( ( SFicAlEscribirEn ( p_ficObj, 0, 0xAA ) != 1 ) ||
			 ( SFicAlEscribirEn ( p_ficObj, 1, 0xBB ) != 1 ) ||
			 ( SFicAlEscribirEn ( p_ficObj, 2, 0xCC ) != 1 ) )
		{
			printf( "Error caso 3: no se pudieron escribir los bytes\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SFicAlTam ( p_ficObj ) != 3 )
		{
			printf( "Error caso 4: se esperaba tam 3: %lu\n", SFicAlTam ( p_ficObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		/* Lectura en desorden: se comprueba el acceso aleatorio. */
		if ( SFicAlLeerEn ( p_ficObj, 2 ) != 0xCC )
		{
			printf( "Error caso 5: se esperaba 0xCC en la posicion 2\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SFicAlLeerEn ( p_ficObj, 0 ) != 0xAA )
		{
			printf( "Error caso 6: se esperaba 0xAA en la posicion 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Lectura secuencial desde una posicion: avanza el cursor. */
		if ( SFicAlPosicionar ( p_ficObj, 1 ) != 1 )
		{
			printf( "Error caso 7: no se pudo posicionar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SFicAlLeer ( p_ficObj ) != 0xBB )
		{
			printf( "Error caso 8: se esperaba 0xBB en la posicion 1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SFicAlPos ( p_ficObj ) != 2 )
		{
			printf( "Error caso 9: se esperaba posicion 2 tras leer: %lu\n", SFicAlPos ( p_ficObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		SFicAlCerrar ( p_ficObj );

		SFicAlEliminar ( &p_ficObj );
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el objeto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

/* Posiciones por encima de 2 GiB. Situarse mas alla del final no escribe
   nada, asi que el fichero sigue teniendo 10 bytes: la prueba no ocupa
   disco. 3 000 000 000 no cabe en un int ( SFicAlTam guardaba ahi la
   posicion y la restauraba mal ) ni en el long de 32 bits de Windows ( donde
   fseek fallaba y SFicAlPosicionar devolvia 1 igualmente ). */
static int TestSFicAlPosicion64 ()
{
	int				iRes = BOOL_VAL_CIERTO;
	unsigned long	ulTam;
	byte			byDatos [ 10 ] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

	printf( "Test SFicAlPosicion 64:\n" );
	SisCrearDirectorio ( FIC_TEST_DIR_RESULTS );
	SFicAleatorio * p_ficObj = SFicAlCrear ( FIC_TEST_DIR_RESULTS "/sfal_test64.bin" );
	if ( ES_VALIDO ( p_ficObj ) )
	{
		SFicAlAbrirExt ( p_ficObj, 1 );
		ulTam = 10;
		if ( ( SFicAlEscribirBufferEn ( p_ficObj, 0, byDatos, &ulTam ) != 1 ) || ( ulTam != 10 ) )
		{
			printf( "Error caso 1: no se pudieron escribir los 10 bytes\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SFicAlPosicionar ( p_ficObj, 3000000000UL ) != 1 )
		{
			printf( "Error caso 2: deberia poder situarse en 3000000000\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SFicAlPos ( p_ficObj ) != 3000000000UL )
		{
			printf( "Error caso 3: se esperaba posicion 3000000000: %lu\n", SFicAlPos ( p_ficObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		/* El tamano no cambia por situarse mas alla del final, y consultarlo
		   deja la posicion donde estaba. */
		if ( SFicAlTam ( p_ficObj ) != 10 )
		{
			printf( "Error caso 4: se esperaba tam 10: %lu\n", SFicAlTam ( p_ficObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SFicAlPos ( p_ficObj ) != 3000000000UL )
		{
			printf( "Error caso 5: SFicAlTam deberia restaurar la posicion 3000000000: %lu\n", SFicAlPos ( p_ficObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SFicAlMoverAFinal ( p_ficObj ) != 1 ) || ( SFicAlPos ( p_ficObj ) != 10 ) )
		{
			printf( "Error caso 6: al final deberia estar en 10: %lu\n", SFicAlPos ( p_ficObj ) );
			iRes = BOOL_VAL_FALSO;
		}
# if ( defined ( POSIX ) )
		/* Fuera de Windows el desplazamiento ( off_t ) es con signo y del
		   mismo ancho que unsigned long: ULONG_MAX no cabe. Se rechaza sin
		   mover el cursor ni escribir en otro sitio. En Windows unsigned long
		   mide 32 bits y cabe entero en __int64, asi que ahi no hay caso. */
		if ( SFicAlPosicionar ( p_ficObj, ULONG_MAX ) != 0 )
		{
			printf( "Error caso 7: ULONG_MAX no deberia ser una posicion alcanzable\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SFicAlPos ( p_ficObj ) != 10 )
		{
			printf( "Error caso 8: el intento fallido no deberia mover el cursor: %lu\n", SFicAlPos ( p_ficObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SFicAlEscribirEn ( p_ficObj, ULONG_MAX, 0xEE ) != 0 )
		{
			printf( "Error caso 9: escribir en ULONG_MAX deberia fallar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SFicAlTam ( p_ficObj ) != 10 )
		{
			printf( "Error caso 10: la escritura fallida no deberia escribir en otro sitio: tam %lu\n", SFicAlTam ( p_ficObj ) );
			iRes = BOOL_VAL_FALSO;
		}
# endif
		SFicAlCerrar ( p_ficObj );
		SFicAlEliminar ( &p_ficObj );
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el objeto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSFicAlNulo01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SFicAlNulo 01:\n" );
	if ( SFicAlEsValido ( NULL ) != 0 )
	{
		printf( "Error caso 1: se esperaba no valido con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SFicAlAbrir ( NULL ) != 0 )
	{
		printf( "Error caso 2: se esperaba fallo al abrir nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SFicAlEscribirEn ( NULL, 0, 0x00 ) != 0 )
	{
		printf( "Error caso 3: se esperaba fallo al escribir en nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SFicAlEstaAbierto ( NULL ) != 0 )
	{
		printf( "Error caso 4: no se esperaba abierto con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

int TestSFicAleatorio ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SFicAleatorio]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSFicAlEscribirLeer01 () == BOOL_VAL_CIERTO ) &&
			( TestSFicAlPosicion64 () == BOOL_VAL_CIERTO ) &&
			( TestSFicAlNulo01 () == BOOL_VAL_CIERTO ) )
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
