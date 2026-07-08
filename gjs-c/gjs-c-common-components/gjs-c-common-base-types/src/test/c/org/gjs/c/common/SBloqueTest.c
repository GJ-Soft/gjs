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
			( TestSBlqInvalidos01 () == BOOL_VAL_CIERTO ) )
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
