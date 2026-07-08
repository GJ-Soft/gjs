#include "Base.h"

#include "SDatos.h"



static int TestSDatCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SDatCrear 01:\n" );

	SDatos * p_datObj = SDatCrear ( 4 );
	if ( ES_NULO ( p_datObj ) )
	{
		printf( "Error caso 1: no se esperaba nulo al crear\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( ( SDatEsValido ( p_datObj ) != 1 ) || ( SDatTam ( p_datObj ) != 4 ) )
		{
			printf( "Error caso 2: se esperaba un dato valido de tamano 4\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SDatEstablecerByte ( p_datObj, 0, 0xAB ) != 1 ) || ( SDatByte ( p_datObj, 0 ) != 0xAB ) )
		{
			printf( "Error caso 3: escribir/leer el byte 0 deberia dar 0xAB\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	SDatDestruir ( &p_datObj );

	if ( ES_VALIDO ( p_datObj ) )
	{
		printf( "Error caso 4: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* Crear con tamano 0 debe fallar. */
	if ( ES_VALIDO ( SDatCrear ( 0 ) ) )
	{
		printf( "Error caso 5: se esperaba nulo al crear con tamano 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSDatContenido01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SDatContenido 01:\n" );

	byte p_byDatos [ 4 ] = { 0x01, 0x02, 0x03, 0x04 };
	SDatos * p_datObj = SDatCrear ( 4 );
	if ( ES_VALIDO ( p_datObj ) )
	{
		if ( SDatAsignarContenido ( p_datObj, p_byDatos, 4 ) != 1 )
		{
			printf( "Error caso 1: se esperaba resultado 1 al asignar el contenido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SDatByte ( p_datObj, 2 ) != 0x03 ) || ( SDatByte ( p_datObj, 3 ) != 0x04 ) )
		{
			printf( "Error caso 2: los bytes 2 y 3 deberian ser 0x03 y 0x04\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Duplicado independiente. */
		SDatos * p_datDup = SDatDuplicar ( p_datObj );
		if ( ES_NULO ( p_datDup ) )
		{
			printf( "Error caso 3: no se esperaba nulo al duplicar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		else
		{
			SDatEstablecerByte ( p_datObj, 0, 0xFF );
			if ( SDatByte ( p_datDup, 0 ) != 0x01 )
			{
				printf( "Error caso 4: modificar el original no deberia afectar al duplicado\n" );
				iRes = BOOL_VAL_FALSO;
			}
			SDatDestruir ( &p_datDup );
		}
		/* Extraer los 2 primeros bytes en un dato nuevo. */
		SDatos * p_datExt = SDatExtraer ( p_datObj, 2 );
		if ( ES_NULO ( p_datExt ) )
		{
			printf( "Error caso 5: no se esperaba nulo al extraer\n" );
			iRes = BOOL_VAL_FALSO;
		}
		else
		{
			if ( ( SDatTam ( p_datExt ) != 2 ) || ( SDatByte ( p_datExt, 1 ) != 0x02 ) )
			{
				printf( "Error caso 6: el extraido deberia tener tamano 2 y el byte 1 igual a 0x02\n" );
				iRes = BOOL_VAL_FALSO;
			}
			SDatDestruir ( &p_datExt );
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el dato\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SDatDestruir ( &p_datObj );
	return ( iRes );
}

static int TestSDatHex01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SDatHex 01:\n" );

	SDatos * p_datObj = SDatCrear ( 2 );
	if ( ES_VALIDO ( p_datObj ) )
	{
		/* Asignar desde cadena hexadecimal. */
		if ( SDatAsignarCadenaHex ( p_datObj, "0A0B" ) != 1 )
		{
			printf( "Error caso 1: se esperaba resultado 1 al asignar la cadena hex\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SDatByte ( p_datObj, 0 ) != 0x0A ) || ( SDatByte ( p_datObj, 1 ) != 0x0B ) )
		{
			printf( "Error caso 2: los bytes deberian ser 0x0A y 0x0B\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* La cadena hex del dato, reasignada a otro, debe reproducir el contenido. */
		char * p_cHex = SDatCadenaHex ( p_datObj );
		if ( ES_NULO ( p_cHex ) )
		{
			printf( "Error caso 3: no se esperaba nulo al obtener la cadena hex\n" );
			iRes = BOOL_VAL_FALSO;
		}
		else
		{
			SDatos * p_datVuelta = SDatCrear ( 2 );
			if ( ES_VALIDO ( p_datVuelta ) )
			{
				SDatAsignarCadenaHex ( p_datVuelta, p_cHex );
				if ( ( SDatByte ( p_datVuelta, 0 ) != 0x0A ) || ( SDatByte ( p_datVuelta, 1 ) != 0x0B ) )
				{
					printf( "Error caso 4: la ida y vuelta por cadena hex deberia conservar el contenido\n" );
					iRes = BOOL_VAL_FALSO;
				}
				SDatDestruir ( &p_datVuelta );
			}
			MemLiberar ( (void **) &p_cHex );
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el dato\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SDatDestruir ( &p_datObj );
	return ( iRes );
}

static int TestSDatInvalidos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SDatInvalidos 01:\n" );

	if ( SDatEsValido ( NULL ) != 0 )
	{
		printf( "Error caso 1: un dato nulo no deberia ser valido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SDatTam ( NULL ) != 0 )
	{
		printf( "Error caso 2: el tamano de un dato nulo deberia ser 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SDatos * p_datNulo = NULL;
	SDatDestruir ( &p_datNulo );
	return ( iRes );
}



int TestSDatos ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SDatos]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSDatCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSDatContenido01 () == BOOL_VAL_CIERTO ) &&
			( TestSDatHex01 () == BOOL_VAL_CIERTO ) &&
			( TestSDatInvalidos01 () == BOOL_VAL_CIERTO ) )
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
