#include "Base.h"

#include "SHoja.h"


/* Primer valor que un long con signo ya no puede representar: LONG_MAX + 1.
   Vale igual con long de 4 bytes ( Windows ) que de 8 ( Cygwin, Linux ). */
#define ULONG_MITAD		( (unsigned long) LONG_MAX + 1UL )



static int TestSHojCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SHojCrear 01:\n" );
	SHoja * p_hojObj = SHojCrear ( 5 );
	if ( ES_VALIDO ( p_hojObj ) )
	{
		if ( SHojEsValida ( p_hojObj ) != 1 )
		{
			printf( "Error caso 1: se esperaba valida\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SHojEstaVacia ( p_hojObj ) != 1 )
		{
			printf( "Error caso 2: se esperaba vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SHojNumElementos ( p_hojObj ) != 0 )
		{
			printf( "Error caso 3: se esperaban 0 elementos: %d\n", SHojNumElementos ( p_hojObj ) );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el objeto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SHojDestruir ( &p_hojObj );
	return ( iRes );
}

static int TestSHojInsertar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SHojInsertar 01:\n" );
	SHoja * p_hojObj = SHojCrear ( 5 );
	if ( ES_VALIDO ( p_hojObj ) )
	{
		SHojInsertar ( p_hojObj, "bbb", 10 );
		SHojInsertar ( p_hojObj, "aaa", 5 );
		if ( SHojNumElementos ( p_hojObj ) != 2 )
		{
			printf( "Error caso 1: se esperaban 2 elementos: %d\n", SHojNumElementos ( p_hojObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SHojExiste ( p_hojObj, "aaa" ) != 1 )
		{
			printf( "Error caso 2: se esperaba que exista \"aaa\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SHojExiste ( p_hojObj, "zzz" ) != 0 )
		{
			printf( "Error caso 3: no se esperaba que exista \"zzz\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SHojBuscar ( p_hojObj, "aaa" ) != 5 )
		{
			printf( "Error caso 4: se esperaba posicion 5 para \"aaa\": %lu\n", SHojBuscar ( p_hojObj, "aaa" ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SHojBuscar ( p_hojObj, "bbb" ) != 10 )
		{
			printf( "Error caso 5: se esperaba posicion 10 para \"bbb\": %lu\n", SHojBuscar ( p_hojObj, "bbb" ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SHojEliminar ( p_hojObj, "aaa" ) != 1 )
		{
			printf( "Error caso 6: se esperaba eliminar correcto\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SHojNumElementos ( p_hojObj ) != 1 )
		{
			printf( "Error caso 7: se esperaba 1 elemento: %d\n", SHojNumElementos ( p_hojObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SHojExiste ( p_hojObj, "aaa" ) != 0 )
		{
			printf( "Error caso 8: no se esperaba que exista \"aaa\" tras eliminar\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el objeto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SHojDestruir ( &p_hojObj );
	return ( iRes );
}

static int TestSHojCompleta01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SHojCompleta 01:\n" );
	SHoja * p_hojObj = SHojCrear ( 2 );
	if ( ES_VALIDO ( p_hojObj ) )
	{
		SHojInsertar ( p_hojObj, "aaa", 1 );
		SHojInsertar ( p_hojObj, "bbb", 2 );
		if ( SHojCompleta ( p_hojObj ) != 1 )
		{
			printf( "Error caso 1: se esperaba completa\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* La hoja esta llena: una nueva insercion debe fallar (-1). */
		if ( SHojInsertar ( p_hojObj, "ccc", 3 ) != -1 )
		{
			printf( "Error caso 2: se esperaba fallo al insertar en hoja completa\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el objeto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SHojDestruir ( &p_hojObj );
	return ( iRes );
}

static int TestSHojMinMax01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SHojMinMax 01:\n" );
	SHoja * p_hojObj = SHojCrear ( 5 );
	if ( ES_VALIDO ( p_hojObj ) )
	{
		/* Se insertan en desorden: min y max deben reflejar el orden de las claves. */
		SHojInsertar ( p_hojObj, "mmm", 1 );
		SHojInsertar ( p_hojObj, "aaa", 2 );
		SHojInsertar ( p_hojObj, "zzz", 3 );
		SHojInsertar ( p_hojObj, "ppp", 4 );
		if ( ES_NULO ( SHojMinClave ( p_hojObj ) ) || ( CadComparar ( SHojMinClave ( p_hojObj ), "aaa" ) != COMP_IGUAL ) )
		{
			printf( "Error caso 1: se esperaba clave minima \"aaa\": [%s]\n", ES_VALIDO ( SHojMinClave ( p_hojObj ) ) ? SHojMinClave ( p_hojObj ) : "(nulo)" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_NULO ( SHojMaxClave ( p_hojObj ) ) || ( CadComparar ( SHojMaxClave ( p_hojObj ), "zzz" ) != COMP_IGUAL ) )
		{
			printf( "Error caso 2: se esperaba clave maxima \"zzz\": [%s]\n", ES_VALIDO ( SHojMaxClave ( p_hojObj ) ) ? SHojMaxClave ( p_hojObj ) : "(nulo)" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el objeto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SHojDestruir ( &p_hojObj );
	return ( iRes );
}

static int TestSHojNulo01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SHojNulo 01:\n" );
	if ( SHojEsValida ( NULL ) != 0 )
	{
		printf( "Error caso 1: se esperaba no valida con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SHojNumElementos ( NULL ) != 0 )
	{
		printf( "Error caso 2: se esperaban 0 elementos con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SHojBuscar ( NULL, "aaa" ) != SLCZ_SIN_POSICION )
	{
		printf( "Error caso 3: se esperaba SLCZ_SIN_POSICION al buscar en nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

/* Posiciones que no caben en un long con signo, y en un int. Antes Insertar
   y Modificar recibian un int y Buscar lo devolvia. */
static int TestSHojFrontera01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SHojFrontera 01:\n" );
	SHoja * p_hojObj = SHojCrear ( 5 );
	if ( ES_VALIDO ( p_hojObj ) )
	{
		SHojInsertar ( p_hojObj, "aaa", ULONG_MITAD );
		SHojInsertar ( p_hojObj, "bbb", 3000000000UL );
		if ( SHojBuscar ( p_hojObj, "aaa" ) != ULONG_MITAD )
		{
			printf( "Error caso 1: se esperaba %lu para \"aaa\": %lu\n", ULONG_MITAD, SHojBuscar ( p_hojObj, "aaa" ) );
			iRes = BOOL_VAL_FALSO;
		}
		/* 3 000 000 000 no cabe en un int de 32 bits. */
		if ( SHojBuscar ( p_hojObj, "bbb" ) != 3000000000UL )
		{
			printf( "Error caso 2: se esperaba 3000000000 para \"bbb\": %lu\n", SHojBuscar ( p_hojObj, "bbb" ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SHojModificar ( p_hojObj, "aaa", ULONG_MAX - 1UL ) != 1 ) ||
			 ( SHojBuscar ( p_hojObj, "aaa" ) != ULONG_MAX - 1UL ) )
		{
			printf( "Error caso 3: tras modificar se esperaba ULONG_MAX - 1: %lu\n", SHojBuscar ( p_hojObj, "aaa" ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SHojBuscar ( p_hojObj, "zzz" ) != SLCZ_SIN_POSICION )
		{
			printf( "Error caso 4: una clave que no esta deberia dar SLCZ_SIN_POSICION: %lu\n", SHojBuscar ( p_hojObj, "zzz" ) );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la hoja\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SHojDestruir ( &p_hojObj );
	return ( iRes );
}

int TestSHoja ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SHoja]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSHojCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSHojInsertar01 () == BOOL_VAL_CIERTO ) &&
			( TestSHojCompleta01 () == BOOL_VAL_CIERTO ) &&
			( TestSHojMinMax01 () == BOOL_VAL_CIERTO ) &&
			( TestSHojNulo01 () == BOOL_VAL_CIERTO ) &&
			( TestSHojFrontera01 () == BOOL_VAL_CIERTO ) )
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
