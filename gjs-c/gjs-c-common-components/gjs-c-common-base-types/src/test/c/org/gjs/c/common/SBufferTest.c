#include "Base.h"

#include "SBuffer.h"



static int TestSBufCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SBufCrear 01:\n" );

	SBuffer * p_bufObj = SBufCrear ( 16 );
	if ( ES_NULO ( p_bufObj ) )
	{
		printf( "Error caso 1: no se esperaba nulo al crear\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SBufEsValido ( p_bufObj ) != 1 )
		{
			printf( "Error caso 2: el buffer recien creado deberia ser valido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SBufTam ( p_bufObj ) != 16 )
		{
			printf( "Error caso 3: se esperaba tam 16: %lu\n", SBufTam ( p_bufObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_NULO ( SBufDireccion ( p_bufObj ) ) )
		{
			printf( "Error caso 4: la direccion no deberia ser nula\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* La memoria del buffer debe venir a cero. */
		if ( SBufLeer ( p_bufObj, 0 ) != 0x00 )
		{
			printf( "Error caso 5: el contenido inicial deberia ser cero\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	SBufDestruir ( &p_bufObj );

	if ( ES_VALIDO ( p_bufObj ) )
	{
		printf( "Error caso 6: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* Crear con tam 0 debe fallar. */
	if ( ES_VALIDO ( SBufCrear ( 0 ) ) )
	{
		printf( "Error caso 7: se esperaba nulo al crear con tam 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSBufEscribirLeer01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SBufEscribirLeer 01:\n" );

	SBuffer * p_bufObj = SBufCrear ( 4 );
	if ( ES_VALIDO ( p_bufObj ) )
	{
		if ( SBufEscribir ( p_bufObj, 1, 0xAB ) != 1 )
		{
			printf( "Error caso 1: se esperaba resultado 1 al escribir\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SBufLeer ( p_bufObj, 1 ) != 0xAB )
		{
			printf( "Error caso 2: se esperaba 0xAB al leer\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Fuera de rango: escribir falla y leer devuelve 0x00. */
		if ( SBufEscribir ( p_bufObj, 4, 0xFF ) != 0 )
		{
			printf( "Error caso 3: escribir fuera de rango deberia fallar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SBufLeer ( p_bufObj, 4 ) != 0x00 )
		{
			printf( "Error caso 4: leer fuera de rango deberia devolver 0x00\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el buffer\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SBufDestruir ( &p_bufObj );
	return ( iRes );
}

static int TestSBufEscribirLeerBuffer01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SBufEscribirLeerBuffer 01:\n" );

	byte byOrig [ 3 ] = { 0xAA, 0xBB, 0xCC };
	SBuffer * p_bufObj = SBufCrear ( 8 );
	if ( ES_VALIDO ( p_bufObj ) )
	{
		unsigned long ulTam = 3;
		if ( SBufEscribirBuffer ( p_bufObj, 2, byOrig, &ulTam ) != 1 )
		{
			printf( "Error caso 1: se esperaba resultado 1 al escribir buffer\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SBufLeer ( p_bufObj, 2 ) != 0xAA ) ||
			 ( SBufLeer ( p_bufObj, 3 ) != 0xBB ) ||
			 ( SBufLeer ( p_bufObj, 4 ) != 0xCC ) )
		{
			printf( "Error caso 2: el buffer no se escribio en la posicion correcta\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Leer de vuelta lo escrito. */
		byte byLeido [ 3 ] = { 0, 0, 0 };
		unsigned long ulLeer = 3;
		if ( SBufLeerBuffer ( p_bufObj, 2, byLeido, &ulLeer ) != 1 )
		{
			printf( "Error caso 3: se esperaba resultado 1 al leer buffer\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( byLeido [ 0 ] != 0xAA ) || ( byLeido [ 1 ] != 0xBB ) || ( byLeido [ 2 ] != 0xCC ) )
		{
			printf( "Error caso 4: el contenido leido no coincide con el escrito\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Leer mas alla del final trunca el tam al espacio disponible. */
		unsigned long ulTrunc = 10;
		if ( SBufLeerBuffer ( p_bufObj, 6, byLeido, &ulTrunc ) != 1 )
		{
			printf( "Error caso 5: se esperaba resultado 1 al leer con truncado\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ulTrunc != 2 )
		{
			printf( "Error caso 6: el tam deberia truncarse a 2: %lu\n", ulTrunc );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el buffer\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SBufDestruir ( &p_bufObj );
	return ( iRes );
}

static int TestSBufLimpiar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SBufLimpiar 01:\n" );

	SBuffer * p_bufObj = SBufCrear ( 4 );
	if ( ES_VALIDO ( p_bufObj ) )
	{
		SBufEscribir ( p_bufObj, 0, 0xFF );
		SBufEscribir ( p_bufObj, 3, 0xFF );
		if ( SBufLimpiar ( p_bufObj ) != 1 )
		{
			printf( "Error caso 1: se esperaba resultado 1 al limpiar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SBufLeer ( p_bufObj, 0 ) != 0x00 ) || ( SBufLeer ( p_bufObj, 3 ) != 0x00 ) )
		{
			printf( "Error caso 2: el buffer no quedo a cero tras limpiar\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el buffer\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SBufDestruir ( &p_bufObj );
	return ( iRes );
}

static int TestSBufPosicionPrimerNulo01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SBufPosicionPrimerNulo 01:\n" );

	SBuffer * p_bufObj = SBufCrear ( 8 );
	if ( ES_VALIDO ( p_bufObj ) )
	{
		/* Buffer a cero: el primer nulo esta en la posicion 0. */
		if ( SBufPosicionPrimerNulo ( p_bufObj ) != 0 )
		{
			printf( "Error caso 1: se esperaba primer nulo en 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SBufEscribir ( p_bufObj, 0, 'a' );
		SBufEscribir ( p_bufObj, 1, 'b' );
		SBufEscribir ( p_bufObj, 2, 'c' );
		if ( SBufPosicionPrimerNulo ( p_bufObj ) != 3 )
		{
			printf( "Error caso 2: se esperaba primer nulo en 3: %lu\n", SBufPosicionPrimerNulo ( p_bufObj ) );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el buffer\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SBufDestruir ( &p_bufObj );
	return ( iRes );
}

static int TestSBufDuplicar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SBufDuplicar 01:\n" );

	SBuffer * p_bufObj = SBufCrear ( 4 );
	if ( ES_VALIDO ( p_bufObj ) )
	{
		SBufEscribir ( p_bufObj, 0, 0x10 );
		SBufEscribir ( p_bufObj, 1, 0x20 );

		/* SBufDuplicarValor: copia independiente de todo el contenido. */
		byte * p_byDup = SBufDuplicarValor ( p_bufObj );
		if ( ES_NULO ( p_byDup ) )
		{
			printf( "Error caso 1: no se esperaba nulo al duplicar valor\n" );
			iRes = BOOL_VAL_FALSO;
		}
		else
		{
			if ( ( p_byDup [ 0 ] != 0x10 ) || ( p_byDup [ 1 ] != 0x20 ) )
			{
				printf( "Error caso 2: el valor duplicado no coincide\n" );
				iRes = BOOL_VAL_FALSO;
			}
			/* Modificar el original no debe afectar a la copia. */
			SBufEscribir ( p_bufObj, 0, 0xFF );
			if ( p_byDup [ 0 ] != 0x10 )
			{
				printf( "Error caso 3: la copia no deberia compartir memoria con el original\n" );
				iRes = BOOL_VAL_FALSO;
			}
			MemLiberar ( (void **) &p_byDup );
		}

		/* SBufDuplicarContenido: copia de un tramo. */
		byte * p_byTramo = SBufDuplicarContenido ( p_bufObj, 1, 2 );
		if ( ES_NULO ( p_byTramo ) )
		{
			printf( "Error caso 4: no se esperaba nulo al duplicar contenido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		else
		{
			if ( p_byTramo [ 0 ] != 0x20 )
			{
				printf( "Error caso 5: el tramo duplicado no coincide\n" );
				iRes = BOOL_VAL_FALSO;
			}
			MemLiberar ( (void **) &p_byTramo );
		}
		/* Duplicar un tramo fuera de rango debe devolver nulo. */
		if ( ES_VALIDO ( SBufDuplicarContenido ( p_bufObj, 3, 4 ) ) )
		{
			printf( "Error caso 6: duplicar un tramo desbordado deberia devolver nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el buffer\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SBufDestruir ( &p_bufObj );
	return ( iRes );
}

static int TestSBufRedimensionar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SBufRedimensionar 01:\n" );

	SBuffer * p_bufObj = SBufCrear ( 4 );
	if ( ES_VALIDO ( p_bufObj ) )
	{
		SBufEscribir ( p_bufObj, 0, 0x55 );

		/* Conservando el contenido. */
		if ( SBufRedimensionar ( p_bufObj, 16, 1 ) != 1 )
		{
			printf( "Error caso 1: se esperaba resultado 1 al redimensionar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SBufTam ( p_bufObj ) != 16 )
		{
			printf( "Error caso 2: se esperaba tam 16: %lu\n", SBufTam ( p_bufObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SBufLeer ( p_bufObj, 0 ) != 0x55 )
		{
			printf( "Error caso 3: no se conservo el contenido tras redimensionar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Reinicializar ( sin conservar ) deja el buffer a cero. */
		if ( SBufInicializar ( p_bufObj, 8 ) != 1 )
		{
			printf( "Error caso 4: se esperaba resultado 1 al inicializar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SBufTam ( p_bufObj ) != 8 ) || ( SBufLeer ( p_bufObj, 0 ) != 0x00 ) )
		{
			printf( "Error caso 5: inicializar deberia dejar el buffer a cero con el nuevo tam\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el buffer\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SBufDestruir ( &p_bufObj );
	return ( iRes );
}

static int TestSBufInvalidos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SBufInvalidos 01:\n" );

	if ( SBufEsValido ( NULL ) != 0 )
	{
		printf( "Error caso 1: un buffer nulo no deberia ser valido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SBufTam ( NULL ) != 0 )
	{
		printf( "Error caso 2: el tam de un buffer nulo deberia ser 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SBufEscribir ( NULL, 0, 0xFF ) != 0 )
	{
		printf( "Error caso 3: escribir en buffer nulo deberia fallar\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SBuffer * p_bufNulo = NULL;
	SBufDestruir ( &p_bufNulo );
	return ( iRes );
}



int TestSBuffer ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SBuffer]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSBufCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSBufEscribirLeer01 () == BOOL_VAL_CIERTO ) &&
			( TestSBufEscribirLeerBuffer01 () == BOOL_VAL_CIERTO ) &&
			( TestSBufLimpiar01 () == BOOL_VAL_CIERTO ) &&
			( TestSBufPosicionPrimerNulo01 () == BOOL_VAL_CIERTO ) &&
			( TestSBufDuplicar01 () == BOOL_VAL_CIERTO ) &&
			( TestSBufRedimensionar01 () == BOOL_VAL_CIERTO ) &&
			( TestSBufInvalidos01 () == BOOL_VAL_CIERTO ) )
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
