#include "Base.h"

#include "SBloque.h"



static int TestSBlqCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SBlqCrear 01:\n" );

	SBloque * p_blqObj = SBlqCrear ( 8 );
	if ( ES_NULO ( p_blqObj ) )
	{
		printf( "Error caso 1: no se esperaba nulo al crear\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SBlqEsValido ( p_blqObj ) != 1 )
		{
			printf( "Error caso 2: el bloque recien creado deberia ser valido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SBlqTam ( p_blqObj ) != 8 )
		{
			printf( "Error caso 3: se esperaba tam 8: %d\n", SBlqTam ( p_blqObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_NULO ( SBlqDatos ( p_blqObj ) ) )
		{
			printf( "Error caso 4: los datos no deberian ser nulos\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* La memoria reservada por el bloque debe venir a cero. */
		if ( SBlqLeerByte ( p_blqObj, 0 ) != 0x00 )
		{
			printf( "Error caso 5: el contenido inicial deberia ser cero\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Un bloque creado gestiona su propia memoria. */
		if ( SBlqLiberacionMemoriaActivada ( p_blqObj ) != 1 )
		{
			printf( "Error caso 6: la liberacion de memoria deberia estar activada\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	SBlqDestruir ( &p_blqObj );

	/* Tras destruir, el puntero debe quedar a nulo. */
	if ( ES_VALIDO ( p_blqObj ) )
	{
		printf( "Error caso 7: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}

	/* Crear con tam <= 0 debe fallar. */
	if ( ES_VALIDO ( SBlqCrear ( 0 ) ) )
	{
		printf( "Error caso 8: se esperaba nulo al crear con tam 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( SBlqCrear ( -4 ) ) )
	{
		printf( "Error caso 9: se esperaba nulo al crear con tam negativo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSBlqAsignar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SBlqAsignar 01:\n" );

	byte * p_byDatos = (byte *) MemReservar ( 4 );
	if ( ES_NULO ( p_byDatos ) )
	{
		printf( "Error caso 0: no se pudo reservar memoria de apoyo\n" );
		return ( BOOL_VAL_FALSO );
	}
	p_byDatos [ 0 ] = 0x11;

	/* Asignar sin ceder la propiedad de la memoria ( iLiberar = 0 ). */
	SBloque * p_blqObj = SBlqAsignar ( p_byDatos, 4, 0 );
	if ( ES_NULO ( p_blqObj ) )
	{
		printf( "Error caso 1: no se esperaba nulo al asignar\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SBlqDatos ( p_blqObj ) != p_byDatos )
		{
			printf( "Error caso 2: el bloque deberia apuntar a la memoria asignada\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SBlqLiberacionMemoriaActivada ( p_blqObj ) != 0 )
		{
			printf( "Error caso 3: la liberacion de memoria no deberia estar activada\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	/* Al destruir con iLiberar = 0, la memoria externa sigue siendo valida. */
	SBlqDestruir ( &p_blqObj );
	if ( p_byDatos [ 0 ] != 0x11 )
	{
		printf( "Error caso 4: la memoria externa no deberia haberse alterado\n" );
		iRes = BOOL_VAL_FALSO;
	}
	MemLiberar ( (void **) &p_byDatos );
	return ( iRes );
}

static int TestSBlqEscribirLeerByte01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SBlqEscribirLeerByte 01:\n" );

	SBloque * p_blqObj = SBlqCrear ( 4 );
	if ( ES_VALIDO ( p_blqObj ) )
	{
		if ( SBlqEscribirByte ( p_blqObj, 2, 0xAB ) != 1 )
		{
			printf( "Error caso 1: se esperaba resultado 1 al escribir\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SBlqLeerByte ( p_blqObj, 2 ) != 0xAB )
		{
			printf( "Error caso 2: se esperaba 0xAB al leer\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Fuera de rango: escribir devuelve 0 y leer devuelve 0x00. */
		if ( SBlqEscribirByte ( p_blqObj, 4, 0xFF ) != 0 )
		{
			printf( "Error caso 3: escribir fuera de rango deberia fallar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SBlqEscribirByte ( p_blqObj, -1, 0xFF ) != 0 )
		{
			printf( "Error caso 4: escribir en posicion negativa deberia fallar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SBlqLeerByte ( p_blqObj, 4 ) != 0x00 )
		{
			printf( "Error caso 5: leer fuera de rango deberia devolver 0x00\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el bloque\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SBlqDestruir ( &p_blqObj );
	return ( iRes );
}

static int TestSBlqEnteros01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SBlqEnteros 01:\n" );

	/* Escribir/leer un entero sobre un bloque del tamano justo. */
	SBloque * p_blqObj = SBlqCrearEntero ();
	if ( ES_VALIDO ( p_blqObj ) )
	{
		if ( SBlqTam ( p_blqObj ) != (int) sizeof ( int ) )
		{
			printf( "Error caso 1: el tam deberia ser sizeof(int)\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SBlqEscribirEntero ( p_blqObj, 12345 ) != 1 )
		{
			printf( "Error caso 2: se esperaba resultado 1 al escribir entero\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SBlqEntero ( p_blqObj ) != 12345 )
		{
			printf( "Error caso 3: se esperaba 12345: %d\n", SBlqEntero ( p_blqObj ) );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el bloque entero\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SBlqDestruir ( &p_blqObj );

	/* Escribir un entero sobre un bloque de tam incompatible debe fallar. */
	SBloque * p_blqPeq = SBlqCrear ( 1 );
	if ( ES_VALIDO ( p_blqPeq ) )
	{
		if ( SBlqEscribirEntero ( p_blqPeq, 7 ) != 0 )
		{
			printf( "Error caso 4: escribir entero en bloque incompatible deberia fallar\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	SBlqDestruir ( &p_blqPeq );
	return ( iRes );
}

static int TestSBlqEscribirBuffer01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SBlqEscribirBuffer 01:\n" );

	byte byOrig [ 3 ] = { 0xAA, 0xBB, 0xCC };
	SBloque * p_blqObj = SBlqCrear ( 8 );
	if ( ES_VALIDO ( p_blqObj ) )
	{
		if ( SBlqEscribirBuffer ( p_blqObj, 2, byOrig, 3 ) != 1 )
		{
			printf( "Error caso 1: se esperaba resultado 1 al escribir buffer\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SBlqLeerByte ( p_blqObj, 2 ) != 0xAA ) ||
			 ( SBlqLeerByte ( p_blqObj, 3 ) != 0xBB ) ||
			 ( SBlqLeerByte ( p_blqObj, 4 ) != 0xCC ) )
		{
			printf( "Error caso 2: el buffer no se escribio en la posicion correcta\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Lo de alrededor debe seguir a cero. */
		if ( ( SBlqLeerByte ( p_blqObj, 1 ) != 0x00 ) || ( SBlqLeerByte ( p_blqObj, 5 ) != 0x00 ) )
		{
			printf( "Error caso 3: se altero memoria fuera del rango escrito\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Escribir mas alla del final debe fallar. */
		if ( SBlqEscribirBuffer ( p_blqObj, 6, byOrig, 3 ) != 0 )
		{
			printf( "Error caso 4: escribir desbordando el bloque deberia fallar\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el bloque\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SBlqDestruir ( &p_blqObj );
	return ( iRes );
}

static int TestSBlqCopiarIgual01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SBlqCopiarIgual 01:\n" );

	byte byDatos [ 4 ] = { 0x01, 0x02, 0x03, 0x04 };
	SBloque * p_blqA = SBlqCrear ( 4 );
	SBloque * p_blqB = SBlqCrear ( 4 );
	if ( ES_VALIDO ( p_blqA ) && ES_VALIDO ( p_blqB ) )
	{
		/* Volcar datos externos y comprobar igualdad con SBlqEsIgualExt. */
		if ( SBlqCopiarDe ( p_blqA, byDatos ) != 1 )
		{
			printf( "Error caso 1: se esperaba resultado 1 en CopiarDe\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SBlqEsIgualExt ( p_blqA, byDatos ) != 1 )
		{
			printf( "Error caso 2: el bloque deberia ser igual a los datos externos\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Copiar de bloque a bloque y comprobar igualdad. */
		if ( SBlqCopiar ( p_blqB, p_blqA ) != 1 )
		{
			printf( "Error caso 3: se esperaba resultado 1 en Copiar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SBlqEsIgual ( p_blqA, p_blqB ) != 1 )
		{
			printf( "Error caso 4: los bloques deberian ser iguales\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Al modificar uno, dejan de ser iguales ( copia independiente ). */
		SBlqEscribirByte ( p_blqB, 0, 0xFF );
		if ( SBlqEsIgual ( p_blqA, p_blqB ) != 0 )
		{
			printf( "Error caso 5: los bloques no deberian ser iguales tras modificar\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear los bloques\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SBlqDestruir ( &p_blqA );
	SBlqDestruir ( &p_blqB );
	return ( iRes );
}

static int TestSBlqDuplicar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SBlqDuplicar 01:\n" );

	byte byDatos [ 4 ] = { 0x10, 0x20, 0x30, 0x40 };
	SBloque * p_blqObj = SBlqCrear ( 4 );
	if ( ES_VALIDO ( p_blqObj ) )
	{
		SBlqCopiarDe ( p_blqObj, byDatos );

		SBloque * p_blqDup = SBlqDuplicar ( p_blqObj );
		if ( ES_NULO ( p_blqDup ) )
		{
			printf( "Error caso 1: no se esperaba nulo al duplicar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		else
		{
			if ( SBlqEsIgual ( p_blqObj, p_blqDup ) != 1 )
			{
				printf( "Error caso 2: el duplicado deberia ser igual al original\n" );
				iRes = BOOL_VAL_FALSO;
			}
			/* Debe ser una copia independiente: modificar el original no afecta al duplicado. */
			SBlqEscribirByte ( p_blqObj, 0, 0xFF );
			if ( SBlqLeerByte ( p_blqDup, 0 ) != 0x10 )
			{
				printf( "Error caso 3: el duplicado no deberia compartir memoria con el original\n" );
				iRes = BOOL_VAL_FALSO;
			}
			SBlqDestruir ( &p_blqDup );
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el bloque\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SBlqDestruir ( &p_blqObj );
	return ( iRes );
}

static int TestSBlqVolcar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SBlqVolcar 01:\n" );

	byte byOrig [ 3 ] = { 0xAA, 0xBB, 0xCC };
	SBloque * p_blqDest = SBlqCrear ( 8 );
	SBloque * p_blqDatos = SBlqCrear ( 3 );
	if ( ES_VALIDO ( p_blqDest ) && ES_VALIDO ( p_blqDatos ) )
	{
		SBlqCopiarDe ( p_blqDatos, byOrig );

		/* Volcar en una posicion distinta de 0 debe respetar iPos. */
		if ( SBlqVolcar ( p_blqDest, 2, p_blqDatos ) != 1 )
		{
			printf( "Error caso 1: se esperaba resultado 1 al volcar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SBlqLeerByte ( p_blqDest, 2 ) != 0xAA ) ||
			 ( SBlqLeerByte ( p_blqDest, 3 ) != 0xBB ) ||
			 ( SBlqLeerByte ( p_blqDest, 4 ) != 0xCC ) )
		{
			printf( "Error caso 2: los datos no se volcaron en la posicion 2\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* La posicion 0 no deberia haberse tocado. */
		if ( SBlqLeerByte ( p_blqDest, 0 ) != 0x00 )
		{
			printf( "Error caso 3: no se esperaba escritura en la posicion 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Volcar desbordando el destino debe fallar. */
		if ( SBlqVolcar ( p_blqDest, 7, p_blqDatos ) != 0 )
		{
			printf( "Error caso 4: volcar desbordando deberia fallar\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear los bloques\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SBlqDestruir ( &p_blqDest );
	SBlqDestruir ( &p_blqDatos );
	return ( iRes );
}

static int TestSBlqExtraer01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SBlqExtraer 01:\n" );

	byte byDatos [ 8 ] = { 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17 };
	SBloque * p_blqObj = SBlqCrear ( 8 );
	if ( ES_VALIDO ( p_blqObj ) )
	{
		SBlqCopiarDe ( p_blqObj, byDatos );

		/* Extraer desde una posicion distinta de 0 debe funcionar. */
		SBloque * p_blqExt = SBlqExtraer ( p_blqObj, 3, 2 );
		if ( ES_NULO ( p_blqExt ) )
		{
			printf( "Error caso 1: no se esperaba nulo al extraer\n" );
			iRes = BOOL_VAL_FALSO;
		}
		else
		{
			if ( SBlqTam ( p_blqExt ) != 2 )
			{
				printf( "Error caso 2: se esperaba tam 2: %d\n", SBlqTam ( p_blqExt ) );
				iRes = BOOL_VAL_FALSO;
			}
			if ( ( SBlqLeerByte ( p_blqExt, 0 ) != 0x13 ) ||
				 ( SBlqLeerByte ( p_blqExt, 1 ) != 0x14 ) )
			{
				printf( "Error caso 3: el contenido extraido no coincide con el origen\n" );
				iRes = BOOL_VAL_FALSO;
			}
			SBlqDestruir ( &p_blqExt );
		}
		/* Extraer fuera de rango debe devolver nulo. */
		if ( ES_VALIDO ( SBlqExtraer ( p_blqObj, 7, 4 ) ) )
		{
			printf( "Error caso 4: extraer desbordando deberia devolver nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el bloque\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SBlqDestruir ( &p_blqObj );
	return ( iRes );
}

static int TestSBlqLimpiar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SBlqLimpiar 01:\n" );

	byte byDatos [ 4 ] = { 0xFF, 0xFF, 0xFF, 0xFF };
	SBloque * p_blqObj = SBlqCrear ( 4 );
	if ( ES_VALIDO ( p_blqObj ) )
	{
		SBlqCopiarDe ( p_blqObj, byDatos );
		if ( SBlqLimpiar ( p_blqObj ) != 1 )
		{
			printf( "Error caso 1: se esperaba resultado 1 al limpiar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SBlqLeerByte ( p_blqObj, 0 ) != 0x00 ) || ( SBlqLeerByte ( p_blqObj, 3 ) != 0x00 ) )
		{
			printf( "Error caso 2: el bloque no quedo a cero tras limpiar\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el bloque\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SBlqDestruir ( &p_blqObj );
	return ( iRes );
}

static int TestSBlqInvalidos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SBlqInvalidos 01:\n" );

	/* Las operaciones sobre un bloque nulo deben ser defensivas. */
	if ( SBlqEsValido ( NULL ) != 0 )
	{
		printf( "Error caso 1: un bloque nulo no deberia ser valido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SBlqTam ( NULL ) != 0 )
	{
		printf( "Error caso 2: el tam de un bloque nulo deberia ser 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( SBlqDatos ( NULL ) ) )
	{
		printf( "Error caso 3: los datos de un bloque nulo deberian ser nulos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SBlqEscribirByte ( NULL, 0, 0xFF ) != 0 )
	{
		printf( "Error caso 4: escribir en bloque nulo deberia fallar\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* Destruir un puntero nulo debe ser inocuo. */
	SBloque * p_blqNulo = NULL;
	SBlqDestruir ( &p_blqNulo );
	return ( iRes );
}

static int CadenaEs ( char * p_cCad, const char * p_cEsperada )
{
	return ( ES_VALIDO ( p_cCad ) && ( CadComparar ( p_cCad, p_cEsperada ) == COMP_IGUAL ) );
}

static int TestSBlqLeerEnPos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SBlqLeerEnPos 01:\n" );

	SBloque * p_blqObj = SBlqCrear ( 48 );
	if ( ES_VALIDO ( p_blqObj ) )
	{
		/* Posiciones sin alinear a proposito. */
		SBlqEscribirEnteroEnPos ( p_blqObj, 1, -12345 );
		SBlqEscribirEnteroSinSignoEnPos ( p_blqObj, 5, 4000000000U );
		SBlqEscribirRealEnPos ( p_blqObj, 9, 1.25f );
		SBlqEscribirRealDobleEnPos ( p_blqObj, 13, -2.5 );
		SBlqEscribirEnteroLargoEnPos ( p_blqObj, 21, -7L );
		SBlqEscribirEnteroLargoSinSignoEnPos ( p_blqObj, 29, ULONG_MAX );

		if ( SBlqLeerEnteroEnPos ( p_blqObj, 1 ) != -12345 )
		{
			printf( "Error caso 1: se esperaba -12345: %d\n", SBlqLeerEnteroEnPos ( p_blqObj, 1 ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SBlqLeerEnteroSinSignoEnPos ( p_blqObj, 5 ) != 4000000000U )
		{
			printf( "Error caso 2: se esperaba 4000000000: %u\n", SBlqLeerEnteroSinSignoEnPos ( p_blqObj, 5 ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SBlqLeerRealEnPos ( p_blqObj, 9 ) != 1.25f )
		{
			printf( "Error caso 3: se esperaba 1.25\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SBlqLeerRealDobleEnPos ( p_blqObj, 13 ) != -2.5 )
		{
			printf( "Error caso 4: se esperaba -2.5\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SBlqLeerEnteroLargoEnPos ( p_blqObj, 21 ) != -7L )
		{
			printf( "Error caso 5: se esperaba -7: %ld\n", SBlqLeerEnteroLargoEnPos ( p_blqObj, 21 ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SBlqLeerEnteroLargoSinSignoEnPos ( p_blqObj, 29 ) != ULONG_MAX )
		{
			printf( "Error caso 6: se esperaba ULONG_MAX: %lu\n", SBlqLeerEnteroLargoSinSignoEnPos ( p_blqObj, 29 ) );
			iRes = BOOL_VAL_FALSO;
		}
		/* El entero de la posicion 1 ocupa los bytes 1 a 4, en little endian. */
		if ( ( SBlqLeerByte ( p_blqObj, 1 ) != 0xC7 ) || ( SBlqLeerByte ( p_blqObj, 2 ) != 0xCF ) ||
			 ( SBlqLeerByte ( p_blqObj, 3 ) != 0xFF ) || ( SBlqLeerByte ( p_blqObj, 4 ) != 0xFF ) )
		{
			printf( "Error caso 7: los bytes de -12345 deberian ser C7 CF FF FF\n" );
			iRes = BOOL_VAL_FALSO;
		}

		/* Fuera del bloque: 0 y ERR_LECTURA_MEMORIA. */
		ErrLimpiar ();
		if ( SBlqLeerEnteroEnPos ( p_blqObj, 45 ) != 0 )
		{
			printf( "Error caso 8: un entero que se sale del bloque deberia leer 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ErrCodigo () != ERR_LECTURA_MEMORIA )
		{
			printf( "Error caso 9: se esperaba ERR_LECTURA_MEMORIA: %d\n", ErrCodigo () );
			iRes = BOOL_VAL_FALSO;
		}
		ErrLimpiar ();
		/* El ultimo entero que cabe si se lee. */
		if ( SBlqLeerEnteroEnPos ( p_blqObj, 44 ) != 0 )
		{
			printf( "Error caso 10: el final del bloque esta a cero\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ErrCodigo () != ERR_OK )
		{
			printf( "Error caso 11: leer el ultimo entero no deberia anotar error: %d\n", ErrCodigo () );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SBlqLeerRealDobleEnPos ( p_blqObj, -1 ) != 0 )
		{
			printf( "Error caso 12: una posicion negativa deberia leer 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SBlqLeerEnteroLargoEnPos ( NULL, 0 ) != 0 )
		{
			printf( "Error caso 13: un bloque nulo deberia leer 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
		ErrLimpiar ();
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el bloque\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SBlqDestruir ( &p_blqObj );
	return ( iRes );
}

static int TestSBlqLeerBuffer01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SBlqLeerBuffer 01:\n" );

	byte byOrig [ 5 ] = { 10, 20, 30, 40, 50 };
	byte byDest [ 5 ] = { 0, 0, 0, 0, 0 };
	SBloque * p_blqObj = SBlqCrear ( 5 );
	if ( ES_VALIDO ( p_blqObj ) )
	{
		SBlqEscribirBuffer ( p_blqObj, 0, byOrig, 5 );
		if ( SBlqLeerBuffer ( p_blqObj, 1, byDest, 3 ) != 1 )
		{
			printf( "Error caso 1: se esperaba 1 al leer 3 bytes desde la 1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( byDest [ 0 ] != 20 ) || ( byDest [ 1 ] != 30 ) || ( byDest [ 2 ] != 40 ) || ( byDest [ 3 ] != 0 ) )
		{
			printf( "Error caso 2: se esperaba 20, 30, 40 y el resto intacto\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SBlqLeerBuffer ( p_blqObj, 3, byDest, 3 ) != 0 )
		{
			printf( "Error caso 3: leer pasado el final deberia fallar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SBlqLeerBuffer ( p_blqObj, 0, byDest, 5 ) != 1 )
		{
			printf( "Error caso 4: leer el bloque entero deberia funcionar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SBlqLeerBuffer ( p_blqObj, 0, byDest, 0 ) != 0 )
		{
			printf( "Error caso 5: leer 0 bytes deberia fallar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SBlqLeerBuffer ( p_blqObj, -1, byDest, 1 ) != 0 )
		{
			printf( "Error caso 6: una posicion negativa deberia fallar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Sin desbordar al sumar posicion y tamano. */
		if ( SBlqLeerBuffer ( p_blqObj, INT_MAX, byDest, 1 ) != 0 )
		{
			printf( "Error caso 7: una posicion enorme deberia fallar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SBlqLeerBuffer ( p_blqObj, 0, NULL, 1 ) != 0 )
		{
			printf( "Error caso 8: un destino nulo deberia fallar\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el bloque\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SBlqDestruir ( &p_blqObj );
	return ( iRes );
}

static int TestSBlqCadenaEnPos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SBlqCadenaEnPos 01:\n" );

	SBloque * p_blqObj = SBlqCrear ( 10 );
	if ( ES_VALIDO ( p_blqObj ) )
	{
		for ( int i = 0; i < 10; i = i + 1 )
		{
			SBlqEscribirByte ( p_blqObj, i, 'x' );
		}
		if ( SBlqEscribirCadenaEnPos ( p_blqObj, 2, "hola" ) != 1 )
		{
			printf( "Error caso 1: se esperaba 1 al escribir la cadena\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Escribe tambien el nulo, en la posicion 6. */
		if ( SBlqLeerByte ( p_blqObj, 6 ) != 0x00 )
		{
			printf( "Error caso 2: se esperaba el nulo en la posicion 6\n" );
			iRes = BOOL_VAL_FALSO;
		}
		char * p_cCad = SBlqLeerCadenaEnPos ( p_blqObj, 2 );
		if ( ! CadenaEs ( p_cCad, "hola" ) )
		{
			printf( "Error caso 3: se esperaba \"hola\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		MemLiberarCadena ( &p_cCad );

		p_cCad = SBlqLeerCadenaEnPos ( p_blqObj, 4 );
		if ( ! CadenaEs ( p_cCad, "la" ) )
		{
			printf( "Error caso 4: desde la posicion 4 se esperaba \"la\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		MemLiberarCadena ( &p_cCad );

		/* Sin nulo hasta el final del bloque: NULL, sin leer fuera. */
		ErrLimpiar ();
		p_cCad = SBlqLeerCadenaEnPos ( p_blqObj, 7 );
		if ( ES_VALIDO ( p_cCad ) )
		{
			printf( "Error caso 5: sin nulo dentro del bloque se esperaba NULL\n" );
			iRes = BOOL_VAL_FALSO;
			MemLiberarCadena ( &p_cCad );
		}
		if ( ErrCodigo () != ERR_LECTURA_MEMORIA )
		{
			printf( "Error caso 6: se esperaba ERR_LECTURA_MEMORIA: %d\n", ErrCodigo () );
			iRes = BOOL_VAL_FALSO;
		}
		ErrLimpiar ();

		/* "hola" mas el nulo son 5 bytes: en la posicion 6 no caben. */
		if ( SBlqEscribirCadenaEnPos ( p_blqObj, 6, "hola" ) != 0 )
		{
			printf( "Error caso 7: la cadena no cabe y deberia fallar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SBlqEscribirCadenaEnPos ( p_blqObj, 5, "hola" ) != 1 )
		{
			printf( "Error caso 8: en la posicion 5 cabe justa\n" );
			iRes = BOOL_VAL_FALSO;
		}

		/* La cadena vacia es solo el nulo. */
		if ( SBlqEscribirCadenaEnPos ( p_blqObj, 0, "" ) != 1 )
		{
			printf( "Error caso 9: la cadena vacia deberia escribirse\n" );
			iRes = BOOL_VAL_FALSO;
		}
		p_cCad = SBlqLeerCadenaEnPos ( p_blqObj, 0 );
		if ( ! CadenaEs ( p_cCad, "" ) )
		{
			printf( "Error caso 10: se esperaba la cadena vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		MemLiberarCadena ( &p_cCad );

		if ( ES_VALIDO ( SBlqLeerCadenaEnPos ( p_blqObj, 10 ) ) )
		{
			printf( "Error caso 11: fuera del bloque se esperaba NULL\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SBlqEscribirCadenaEnPos ( p_blqObj, 0, NULL ) != 0 )
		{
			printf( "Error caso 12: escribir una cadena nula deberia fallar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		ErrLimpiar ();
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el bloque\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SBlqDestruir ( &p_blqObj );
	return ( iRes );
}

static int TestSBlqSecuencialExt01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SBlqSecuencialExt 01:\n" );

	/* byte + int + unsigned long + double + "gjs" con nulo + float */
	int iTamUl = (int) sizeof ( unsigned long );
	int iFin = 1 + 4 + iTamUl + 8 + 4 + 4;
	int iPos;
	SBloque * p_blqObj = SBlqCrear ( iFin );
	if ( ES_VALIDO ( p_blqObj ) )
	{
		iPos = 0;
		if ( SBlqEscribirByteExt ( p_blqObj, &iPos, 0x7F ) != 1 || iPos != 1 )
		{
			printf( "Error caso 1: tras el byte se esperaba la posicion 1: %d\n", iPos );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SBlqEscribirEnteroEnPosExt ( p_blqObj, &iPos, 42 ) != 1 || iPos != 5 )
		{
			printf( "Error caso 2: tras el entero se esperaba la posicion 5: %d\n", iPos );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SBlqEscribirEnteroLargoSinSignoEnPosExt ( p_blqObj, &iPos, ULONG_MAX ) != 1 || iPos != 5 + iTamUl )
		{
			printf( "Error caso 3: tras el largo sin signo se esperaba la posicion %d: %d\n", 5 + iTamUl, iPos );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SBlqEscribirRealDobleEnPosExt ( p_blqObj, &iPos, -0.5 ) != 1 || iPos != 13 + iTamUl )
		{
			printf( "Error caso 4: tras el doble se esperaba la posicion %d: %d\n", 13 + iTamUl, iPos );
			iRes = BOOL_VAL_FALSO;
		}
		/* La cadena avanza tambien el nulo. */
		if ( SBlqEscribirCadenaEnPosExt ( p_blqObj, &iPos, "gjs" ) != 1 || iPos != 17 + iTamUl )
		{
			printf( "Error caso 5: tras la cadena se esperaba la posicion %d: %d\n", 17 + iTamUl, iPos );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SBlqEscribirRealEnPosExt ( p_blqObj, &iPos, 3.0f ) != 1 || iPos != iFin )
		{
			printf( "Error caso 6: tras el real se esperaba la posicion %d: %d\n", iFin, iPos );
			iRes = BOOL_VAL_FALSO;
		}
		/* Lleno: falla y la posicion no se mueve. */
		if ( SBlqEscribirByteExt ( p_blqObj, &iPos, 1 ) != 0 || iPos != iFin )
		{
			printf( "Error caso 7: con el bloque lleno deberia fallar sin mover la posicion: %d\n", iPos );
			iRes = BOOL_VAL_FALSO;
		}

		iPos = 0;
		if ( SBlqLeerByteExt ( p_blqObj, &iPos ) != 0x7F )
		{
			printf( "Error caso 8: se esperaba el byte 0x7F\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SBlqLeerEnteroEnPosExt ( p_blqObj, &iPos ) != 42 )
		{
			printf( "Error caso 9: se esperaba 42\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SBlqLeerEnteroLargoSinSignoEnPosExt ( p_blqObj, &iPos ) != ULONG_MAX )
		{
			printf( "Error caso 10: se esperaba ULONG_MAX\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SBlqLeerRealDobleEnPosExt ( p_blqObj, &iPos ) != -0.5 )
		{
			printf( "Error caso 11: se esperaba -0.5\n" );
			iRes = BOOL_VAL_FALSO;
		}
		char * p_cCad = SBlqLeerCadenaEnPosExt ( p_blqObj, &iPos );
		if ( ! CadenaEs ( p_cCad, "gjs" ) )
		{
			printf( "Error caso 12: se esperaba \"gjs\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		MemLiberarCadena ( &p_cCad );
		if ( SBlqLeerRealEnPosExt ( p_blqObj, &iPos ) != 3.0f )
		{
			printf( "Error caso 13: se esperaba 3.0 justo despues de la cadena\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( iPos != iFin )
		{
			printf( "Error caso 14: al terminar se esperaba la posicion %d: %d\n", iFin, iPos );
			iRes = BOOL_VAL_FALSO;
		}

		/* Al final: lectura fallida, 0 y sin moverse. */
		ErrLimpiar ();
		if ( SBlqLeerEnteroEnPosExt ( p_blqObj, &iPos ) != 0 || iPos != iFin )
		{
			printf( "Error caso 15: leer al final deberia dar 0 sin mover la posicion: %d\n", iPos );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ErrCodigo () != ERR_LECTURA_MEMORIA )
		{
			printf( "Error caso 16: se esperaba ERR_LECTURA_MEMORIA: %d\n", ErrCodigo () );
			iRes = BOOL_VAL_FALSO;
		}
		ErrLimpiar ();

		/* Las otras parejas, de una en una. */
		iPos = 0;
		SBlqEscribirEnteroLargoEnPosExt ( p_blqObj, &iPos, -99L );
		SBlqEscribirEnteroSinSignoEnPosExt ( p_blqObj, &iPos, 3000000000U );
		iPos = 0;
		if ( SBlqLeerEnteroLargoEnPosExt ( p_blqObj, &iPos ) != -99L )
		{
			printf( "Error caso 17: se esperaba -99\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SBlqLeerEnteroSinSignoEnPosExt ( p_blqObj, &iPos ) != 3000000000U )
		{
			printf( "Error caso 18: se esperaba 3000000000\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( iPos != (int) sizeof ( long ) + 4 )
		{
			printf( "Error caso 19: se esperaba la posicion %d: %d\n", (int) sizeof ( long ) + 4, iPos );
			iRes = BOOL_VAL_FALSO;
		}

		/* Sin posicion no se hace nada. */
		if ( SBlqEscribirEnteroEnPosExt ( p_blqObj, NULL, 1 ) != 0 )
		{
			printf( "Error caso 20: sin posicion deberia fallar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( SBlqLeerCadenaEnPosExt ( p_blqObj, NULL ) ) )
		{
			printf( "Error caso 21: sin posicion se esperaba NULL\n" );
			iRes = BOOL_VAL_FALSO;
		}
		ErrLimpiar ();
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el bloque\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SBlqDestruir ( &p_blqObj );
	return ( iRes );
}

static int TestSBlqVolcarExtraerExt01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SBlqVolcarExtraerExt 01:\n" );

	byte byDatos [ 3 ] = { 7, 8, 9 };
	int iPos;
	SBloque * p_blqObj = SBlqCrear ( 8 );
	SBloque * p_blqDatos = SBlqCrear ( 3 );
	if ( ES_VALIDO ( p_blqObj ) && ES_VALIDO ( p_blqDatos ) )
	{
		SBlqCopiarDe ( p_blqDatos, byDatos );
		iPos = 2;
		if ( SBlqVolcarExt ( p_blqObj, &iPos, p_blqDatos ) != 1 || iPos != 5 )
		{
			printf( "Error caso 1: tras volcar 3 bytes en la 2 se esperaba la posicion 5: %d\n", iPos );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SBlqLeerByte ( p_blqObj, 2 ) != 7 ) || ( SBlqLeerByte ( p_blqObj, 4 ) != 9 ) )
		{
			printf( "Error caso 2: los bytes volcados no estan en su sitio\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* No cabe: falla sin mover. */
		iPos = 6;
		if ( SBlqVolcarExt ( p_blqObj, &iPos, p_blqDatos ) != 0 || iPos != 6 )
		{
			printf( "Error caso 3: si no cabe deberia fallar sin mover la posicion: %d\n", iPos );
			iRes = BOOL_VAL_FALSO;
		}

		iPos = 2;
		SBloque * p_blqExtr = SBlqExtraerExt ( p_blqObj, &iPos, 3 );
		if ( ES_NULO ( p_blqExtr ) )
		{
			printf( "Error caso 4: no se esperaba nulo al extraer\n" );
			iRes = BOOL_VAL_FALSO;
		}
		else
		{
			if ( SBlqEsIgual ( p_blqExtr, p_blqDatos ) != 1 )
			{
				printf( "Error caso 5: lo extraido deberia ser 7, 8, 9\n" );
				iRes = BOOL_VAL_FALSO;
			}
			if ( iPos != 5 )
			{
				printf( "Error caso 6: tras extraer se esperaba la posicion 5: %d\n", iPos );
				iRes = BOOL_VAL_FALSO;
			}
		}
		SBlqDestruir ( &p_blqExtr );

		iPos = 6;
		if ( ES_VALIDO ( SBlqExtraerExt ( p_blqObj, &iPos, 3 ) ) || iPos != 6 )
		{
			printf( "Error caso 7: extraer fuera deberia dar NULL sin mover la posicion: %d\n", iPos );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( SBlqExtraerExt ( p_blqObj, NULL, 3 ) ) )
		{
			printf( "Error caso 8: sin posicion se esperaba NULL\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SBlqVolcarExt ( p_blqObj, NULL, p_blqDatos ) != 0 )
		{
			printf( "Error caso 9: sin posicion deberia fallar\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear los bloques\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SBlqDestruir ( &p_blqObj );
	SBlqDestruir ( &p_blqDatos );
	return ( iRes );
}



int TestSBloque ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SBloque]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSBlqCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSBlqAsignar01 () == BOOL_VAL_CIERTO ) &&
			( TestSBlqEscribirLeerByte01 () == BOOL_VAL_CIERTO ) &&
			( TestSBlqEnteros01 () == BOOL_VAL_CIERTO ) &&
			( TestSBlqEscribirBuffer01 () == BOOL_VAL_CIERTO ) &&
			( TestSBlqCopiarIgual01 () == BOOL_VAL_CIERTO ) &&
			( TestSBlqDuplicar01 () == BOOL_VAL_CIERTO ) &&
			( TestSBlqVolcar01 () == BOOL_VAL_CIERTO ) &&
			( TestSBlqExtraer01 () == BOOL_VAL_CIERTO ) &&
			( TestSBlqLimpiar01 () == BOOL_VAL_CIERTO ) &&
			( TestSBlqInvalidos01 () == BOOL_VAL_CIERTO ) &&
			( TestSBlqLeerEnPos01 () == BOOL_VAL_CIERTO ) &&
			( TestSBlqLeerBuffer01 () == BOOL_VAL_CIERTO ) &&
			( TestSBlqCadenaEnPos01 () == BOOL_VAL_CIERTO ) &&
			( TestSBlqSecuencialExt01 () == BOOL_VAL_CIERTO ) &&
			( TestSBlqVolcarExtraerExt01 () == BOOL_VAL_CIERTO ) )
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
