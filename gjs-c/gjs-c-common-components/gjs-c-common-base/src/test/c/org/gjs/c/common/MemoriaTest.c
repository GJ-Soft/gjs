#include "Base.h"

#include "Memoria.h"



static int TestMemReservar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test MemReservar 01:\n" );
	byte * p_byBloque = (byte *) MemReservar ( 16 );
	if ( ES_NULO ( p_byBloque ) )
	{
		printf( "Error caso 1: no se esperaba nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		/* La memoria reservada debe venir inicializada a cero. */
		int iByte;
		for ( iByte = 0; iByte < 16; iByte = iByte + 1 )
		{
			if ( p_byBloque [ iByte ] != 0 )
			{
				printf( "Error caso 2: la memoria no esta a cero en la posicion %d\n", iByte );
				iRes = BOOL_VAL_FALSO;
			}
		}
	}
	MemLiberar ( (void **) &p_byBloque );

	/* Reservar 0 o menos bytes debe fallar. */
	if ( ES_VALIDO ( MemReservar ( 0 ) ) )
	{
		printf( "Error caso 3: se esperaba nulo al reservar 0 bytes\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestMemLiberar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test MemLiberar 01:\n" );
	byte * p_byBloque = (byte *) MemReservar ( 8 );
	int iLib = MemLiberar ( (void **) &p_byBloque );
	if ( iLib != 1 )
	{
		printf( "Error caso 1: se esperaba resultado 1: %d\n", iLib );
		iRes = BOOL_VAL_FALSO;
	}
	/* Tras liberar, el puntero debe quedar a nulo. */
	if ( ES_VALIDO ( p_byBloque ) )
	{
		printf( "Error caso 2: se esperaba puntero nulo tras liberar\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* Liberar un puntero ya nulo debe ser inocuo (resultado 1). */
	if ( MemLiberar ( (void **) &p_byBloque ) != 1 )
	{
		printf( "Error caso 3: se esperaba resultado 1 al liberar nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestMemLimpiarLlenar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test MemLimpiarLlenar 01:\n" );
	byte * p_byBloque = (byte *) MemReservar ( 4 );
	if ( ES_VALIDO ( p_byBloque ) )
	{
		MemLlenar ( p_byBloque, 0xAB, 4 );
		if ( ( p_byBloque[ 0 ] != 0xAB ) || ( p_byBloque[ 3 ] != 0xAB ) )
		{
			printf( "Error caso 1: la memoria no se lleno correctamente\n" );
			iRes = BOOL_VAL_FALSO;
		}
		MemLimpiar ( p_byBloque, 4 );
		if ( ( p_byBloque[ 0 ] != 0 ) || ( p_byBloque[ 3 ] != 0 ) )
		{
			printf( "Error caso 2: la memoria no se limpio correctamente\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo reservar memoria\n" );
		iRes = BOOL_VAL_FALSO;
	}
	MemLiberar ( (void **) &p_byBloque );
	return ( iRes );
}

static int TestMemCopiarIgual01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test MemCopiarIgual 01:\n" );
	byte byOrig [ 4 ] = { 0x10, 0x20, 0x30, 0x40 };
	byte byDest [ 4 ] = { 0, 0, 0, 0 };

	MemCopiar ( byDest, byOrig, 4 );
	if ( MemEsIgual ( byDest, byOrig, 4 ) != 1 )
	{
		printf( "Error caso 1: los bloques deberian ser iguales tras copiar\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* Bloques distintos. */
	byDest [ 2 ] = 0xFF;
	if ( MemEsIgual ( byDest, byOrig, 4 ) != 0 )
	{
		printf( "Error caso 2: los bloques no deberian ser iguales\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestMemRedimensionar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test MemRedimensionar 01:\n" );
	byte * p_byBloque = (byte *) MemReservar ( 4 );
	if ( ES_VALIDO ( p_byBloque ) )
	{
		p_byBloque [ 0 ] = 0x55;
		int iRed = MemRedimensionar ( (void **) &p_byBloque, 16 );
		if ( iRed != 1 )
		{
			printf( "Error caso 1: se esperaba resultado 1: %d\n", iRed );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_NULO ( p_byBloque ) )
		{
			printf( "Error caso 2: no se esperaba nulo tras redimensionar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		else if ( p_byBloque [ 0 ] != 0x55 )
		{
			printf( "Error caso 3: no se conservo el contenido tras redimensionar\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo reservar memoria\n" );
		iRes = BOOL_VAL_FALSO;
	}
	MemLiberar ( (void **) &p_byBloque );
	return ( iRes );
}

static int TestMemEsValida01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test MemEsValida 01:\n" );
	if ( MemEsValida ( NULL ) != 0 )
	{
		printf( "Error caso 1: un puntero nulo no es una direccion valida\n" );
		iRes = BOOL_VAL_FALSO;
	}
	byte * p_byBloque = (byte *) MemReservar ( 8 );
	if ( MemEsValida ( p_byBloque ) != 1 )
	{
		printf( "Error caso 2: se esperaba una direccion valida\n" );
		iRes = BOOL_VAL_FALSO;
	}
	MemLiberar ( (void **) &p_byBloque );
	return ( iRes );
}



int TestMemoria ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test Memoria]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	ErrLimpiar ();
	if ( ( TestMemReservar01 () == BOOL_VAL_CIERTO ) &&
			( TestMemLiberar01 () == BOOL_VAL_CIERTO ) &&
			( TestMemLimpiarLlenar01 () == BOOL_VAL_CIERTO ) &&
			( TestMemCopiarIgual01 () == BOOL_VAL_CIERTO ) &&
			( TestMemRedimensionar01 () == BOOL_VAL_CIERTO ) &&
			( TestMemEsValida01 () == BOOL_VAL_CIERTO ) )
	{
		printf ( "%sResultado: OK%s\n", ANSI_VERDE, ANSI_RESETEAR );
	}
	else
	{
		printf ( "%sResultado: KO%s\n", ANSI_ROJO, ANSI_RESETEAR );
		iRes = BOOL_VAL_FALSO;
	}
	ErrLimpiar ();
	printf ( "%s[Fin]%s\n", ANSI_AMARILLO, ANSI_RESETEAR );
	return ( iRes );
}
