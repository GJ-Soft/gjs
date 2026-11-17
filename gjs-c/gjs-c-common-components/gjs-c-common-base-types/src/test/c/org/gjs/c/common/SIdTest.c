#include "Base.h"

#include "SId.h"



static int TestSIdCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SIdCrear 01:\n" );

	SId * p_idObj = SIdCrearDef ();
	if ( ES_NULO ( p_idObj ) )
	{
		printf( "Error caso 1: no se esperaba nulo al crear\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		/* Un id recien creado vale 0 y, por convenio, aun no es valido. */
		if ( SIdValor ( p_idObj ) != 0 )
		{
			printf( "Error caso 2: el valor inicial deberia ser 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SIdEsValido ( p_idObj ) != 0 )
		{
			printf( "Error caso 3: un id con valor 0 no deberia ser valido\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	SIdDestruir ( &p_idObj );

	if ( ES_VALIDO ( p_idObj ) )
	{
		printf( "Error caso 4: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSIdCrearValor01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SIdCrearValor 01:\n" );

	SId * p_idObj = SIdCrear ( 7 );
	if ( ES_NULO ( p_idObj ) )
	{
		printf( "Error caso 1: no se esperaba nulo al crear con valor\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SIdValor ( p_idObj ) != 7 )
		{
			printf( "Error caso 2: se esperaba valor 7: %lu\n", SIdValor ( p_idObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SIdEsValido ( p_idObj ) != 1 )
		{
			printf( "Error caso 3: un id con valor 7 deberia ser valido\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	SIdDestruir ( &p_idObj );

	/* Crear con 0 debe dejarlo igual que SIdCrearDef. */
	p_idObj = SIdCrear ( 0 );
	if ( ES_NULO ( p_idObj ) )
	{
		printf( "Error caso 4: no se esperaba nulo al crear con valor 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SIdValor ( p_idObj ) != 0 )
		{
			printf( "Error caso 5: se esperaba valor 0: %lu\n", SIdValor ( p_idObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SIdEsValido ( p_idObj ) != 0 )
		{
			printf( "Error caso 6: un id con valor 0 no deberia ser valido\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	SIdDestruir ( &p_idObj );
	return ( iRes );
}

static int TestSIdEstablecerValor01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SIdEstablecerValor 01:\n" );

	SId * p_idObj = SIdCrearDef ();
	if ( ES_VALIDO ( p_idObj ) )
	{
		if ( SIdEstablecer ( p_idObj, 42 ) != 1 )
		{
			printf( "Error caso 1: se esperaba resultado 1 al establecer\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SIdValor ( p_idObj ) != 42 )
		{
			printf( "Error caso 2: se esperaba valor 42: %lu\n", SIdValor ( p_idObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		/* Con un valor mayor que 0 ya es valido. */
		if ( SIdEsValido ( p_idObj ) != 1 )
		{
			printf( "Error caso 3: un id con valor 42 deberia ser valido\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el id\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SIdDestruir ( &p_idObj );

	/* Establecer sobre un id nulo debe fallar. */
	if ( SIdEstablecer ( NULL, 1 ) != 0 )
	{
		printf( "Error caso 4: establecer sobre un id nulo deberia fallar\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSIdComparaciones01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SIdComparaciones 01:\n" );

	SId * p_idA = SIdCrearDef ();
	SId * p_idB = SIdCrearDef ();
	if ( ES_VALIDO ( p_idA ) && ES_VALIDO ( p_idB ) )
	{
		SIdEstablecer ( p_idA, 10 );
		SIdEstablecer ( p_idB, 20 );

		if ( SIdEsMenor ( p_idA, p_idB ) != 1 )
		{
			printf( "Error caso 1: 10 deberia ser menor que 20\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SIdEsMayor ( p_idB, p_idA ) != 1 )
		{
			printf( "Error caso 2: 20 deberia ser mayor que 10\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SIdEsIgual ( p_idA, p_idB ) != 0 )
		{
			printf( "Error caso 3: 10 y 20 no deberian ser iguales\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SIdEstablecer ( p_idB, 10 );
		if ( SIdEsIgual ( p_idA, p_idB ) != 1 )
		{
			printf( "Error caso 4: ambos deberian ser iguales tras igualar el valor\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear los ids\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SIdDestruir ( &p_idA );
	SIdDestruir ( &p_idB );
	return ( iRes );
}

static int TestSIdComparacionesNum01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SIdComparacionesNum 01:\n" );

	SId * p_idObj = SIdCrearDef ();
	if ( ES_VALIDO ( p_idObj ) )
	{
		SIdEstablecer ( p_idObj, 50 );

		if ( SIdEsIgualNum ( p_idObj, 50 ) != 1 )
		{
			printf( "Error caso 1: deberia ser igual a 50\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SIdEsMenorNum ( p_idObj, 60 ) != 1 )
		{
			printf( "Error caso 2: 50 deberia ser menor que 60\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SIdEsMayorNum ( p_idObj, 40 ) != 1 )
		{
			printf( "Error caso 3: 50 deberia ser mayor que 40\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Rango abierto ( sin incluir extremos ). */
		if ( SIdEstaEnRangoNum ( p_idObj, 40, 60 ) != 1 )
		{
			printf( "Error caso 4: 50 deberia estar en el rango ( 40, 60 )\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SIdEstaEnRangoNum ( p_idObj, 50, 60 ) != 0 )
		{
			printf( "Error caso 5: 50 no deberia estar en el rango abierto ( 50, 60 )\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Rango cerrado ( incluyendo extremos ). */
		if ( SIdEstaEnRangoIgNum ( p_idObj, 50, 60 ) != 1 )
		{
			printf( "Error caso 6: 50 deberia estar en el rango cerrado [ 50, 60 ]\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el id\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SIdDestruir ( &p_idObj );
	return ( iRes );
}

static int TestSIdAsignar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SIdAsignar 01:\n" );

	SId * p_idA = SIdCrear ( 10 );
	SId * p_idB = SIdCrearDef ();
	if ( ES_VALIDO ( p_idA ) && ES_VALIDO ( p_idB ) )
	{
		if ( SIdAsignar ( p_idB, p_idA ) != 1 )
		{
			printf( "Error caso 1: se esperaba resultado 1 al asignar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SIdValor ( p_idB ) != 10 )
		{
			printf( "Error caso 2: se esperaba valor 10 en el destino: %lu\n", SIdValor ( p_idB ) );
			iRes = BOOL_VAL_FALSO;
		}
		/* El origen no se toca. */
		if ( SIdValor ( p_idA ) != 10 )
		{
			printf( "Error caso 3: el origen no deberia cambiar: %lu\n", SIdValor ( p_idA ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SIdEsIgual ( p_idA, p_idB ) != 1 )
		{
			printf( "Error caso 4: ambos deberian ser iguales tras asignar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Con algun operando nulo debe fallar y no tocar el destino. */
		if ( SIdAsignar ( p_idB, NULL ) != 0 )
		{
			printf( "Error caso 5: asignar desde un id nulo deberia fallar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SIdValor ( p_idB ) != 10 )
		{
			printf( "Error caso 6: el destino no deberia cambiar al fallar: %lu\n", SIdValor ( p_idB ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SIdAsignar ( NULL, p_idA ) != 0 )
		{
			printf( "Error caso 7: asignar sobre un id nulo deberia fallar\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear los ids\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SIdDestruir ( &p_idA );
	SIdDestruir ( &p_idB );
	return ( iRes );
}

static int TestSIdEstaEnRango01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SIdEstaEnRango 01:\n" );

	SId * p_idObj = SIdCrear ( 50 );
	SId * p_idInf = SIdCrear ( 40 );
	SId * p_idSup = SIdCrear ( 60 );
	SId * p_idCero = SIdCrearDef ();
	if ( ES_VALIDO ( p_idObj ) && ES_VALIDO ( p_idInf ) && ES_VALIDO ( p_idSup ) &&
		 ES_VALIDO ( p_idCero ) )
	{
		/* Rango abierto ( sin incluir extremos ). */
		if ( SIdEstaEnRango ( p_idObj, p_idInf, p_idSup ) != 1 )
		{
			printf( "Error caso 1: 50 deberia estar en el rango ( 40, 60 )\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SIdEstablecer ( p_idInf, 50 );
		if ( SIdEstaEnRango ( p_idObj, p_idInf, p_idSup ) != 0 )
		{
			printf( "Error caso 2: 50 no deberia estar en el rango abierto ( 50, 60 )\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Rango cerrado ( incluyendo extremos ). */
		if ( SIdEstaEnRangoIg ( p_idObj, p_idInf, p_idSup ) != 1 )
		{
			printf( "Error caso 3: 50 deberia estar en el rango cerrado [ 50, 60 ]\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Un extremo a 0 es un extremo legitimo: solo se mira el puntero. */
		if ( SIdEstaEnRango ( p_idObj, p_idCero, p_idSup ) != 1 )
		{
			printf( "Error caso 4: 50 deberia estar en el rango ( 0, 60 )\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SIdEstaEnRangoIg ( p_idObj, p_idCero, p_idSup ) != 1 )
		{
			printf( "Error caso 5: 50 deberia estar en el rango cerrado [ 0, 60 ]\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear los ids\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SIdDestruir ( &p_idObj );
	SIdDestruir ( &p_idInf );
	SIdDestruir ( &p_idSup );
	SIdDestruir ( &p_idCero );
	return ( iRes );
}

static int TestSIdComparar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SIdComparar 01:\n" );

	SId * p_idA = SIdCrear ( 10 );
	SId * p_idB = SIdCrear ( 20 );
	if ( ES_VALIDO ( p_idA ) && ES_VALIDO ( p_idB ) )
	{
		if ( SIdComparar ( p_idA, p_idB ) != COMP_MENOR )
		{
			printf( "Error caso 1: 10 frente a 20 deberia dar COMP_MENOR: %d\n", SIdComparar ( p_idA, p_idB ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SIdComparar ( p_idB, p_idA ) != COMP_MAYOR )
		{
			printf( "Error caso 2: 20 frente a 10 deberia dar COMP_MAYOR: %d\n", SIdComparar ( p_idB, p_idA ) );
			iRes = BOOL_VAL_FALSO;
		}
		SIdEstablecer ( p_idB, 10 );
		if ( SIdComparar ( p_idA, p_idB ) != COMP_IGUAL )
		{
			printf( "Error caso 3: dos ids iguales deberian dar COMP_IGUAL: %d\n", SIdComparar ( p_idA, p_idB ) );
			iRes = BOOL_VAL_FALSO;
		}
		/* Un operando no utilizable ordena antes. */
		if ( SIdComparar ( p_idA, NULL ) != COMP_MAYOR )
		{
			printf( "Error caso 4: frente a un id nulo deberia dar COMP_MAYOR\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SIdComparar ( NULL, p_idA ) != COMP_MENOR )
		{
			printf( "Error caso 5: un id nulo deberia dar COMP_MENOR\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SIdComparar ( NULL, NULL ) != COMP_IGUAL )
		{
			printf( "Error caso 6: dos ids nulos deberian dar COMP_IGUAL\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear los ids\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SIdDestruir ( &p_idA );
	SIdDestruir ( &p_idB );
	return ( iRes );
}

static int TestSIdCompararNum01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SIdCompararNum 01:\n" );

	SId * p_idObj = SIdCrear ( 50 );
	if ( ES_VALIDO ( p_idObj ) )
	{
		if ( SIdCompararNum ( p_idObj, 60 ) != COMP_MENOR )
		{
			printf( "Error caso 1: 50 frente a 60 deberia dar COMP_MENOR: %d\n", SIdCompararNum ( p_idObj, 60 ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SIdCompararNum ( p_idObj, 40 ) != COMP_MAYOR )
		{
			printf( "Error caso 2: 50 frente a 40 deberia dar COMP_MAYOR: %d\n", SIdCompararNum ( p_idObj, 40 ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SIdCompararNum ( p_idObj, 50 ) != COMP_IGUAL )
		{
			printf( "Error caso 3: 50 frente a 50 deberia dar COMP_IGUAL: %d\n", SIdCompararNum ( p_idObj, 50 ) );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el id\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SIdDestruir ( &p_idObj );

	/* Un id nulo ordena antes de cualquier valor. */
	if ( SIdCompararNum ( NULL, 50 ) != COMP_MENOR )
	{
		printf( "Error caso 4: un id nulo deberia dar COMP_MENOR\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSIdHash01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SIdHash 01:\n" );

	SId * p_idA = SIdCrearDef ();
	SId * p_idB = SIdCrearDef ();
	if ( ES_VALIDO ( p_idA ) && ES_VALIDO ( p_idB ) )
	{
		SIdEstablecer ( p_idA, 12345 );
		SIdEstablecer ( p_idB, 12345 );
		/* Mismo valor -> mismo hash. */
		if ( SIdHash ( p_idA ) != SIdHash ( p_idB ) )
		{
			printf( "Error caso 1: ids con el mismo valor deberian tener el mismo hash\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear los ids\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SIdDestruir ( &p_idA );
	SIdDestruir ( &p_idB );
	return ( iRes );
}

/* SIdPtr envuelve el id en un SPtr con SIdDestruir como destructor: al
   destruir el SPtr se libera tambien el SId. Con MODO_DEPURACION se comprueba
   que no queda memoria reservada. */
static int TestSIdPtr01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SIdPtr 01:\n" );
# if ( defined ( MODO_DEPURACION ) )
	unsigned long ulBloquesAntes = MemNumBloquesActuales ();
# endif
	SId * p_idObj = SIdCrear ( 42UL );
	SPtr * p_ptrObj = SIdPtr ( p_idObj );
	if ( ES_NULO ( p_ptrObj ) )
	{
		printf( "Error caso 1: no se esperaba nulo al crear el SPtr\n" );
		iRes = BOOL_VAL_FALSO;
		SIdDestruir ( &p_idObj );
	}
	else
	{
		if ( SPtrEsValido ( p_ptrObj ) != 1 )
		{
			printf( "Error caso 2: el SPtr deberia ser valido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SPtrObjeto ( p_ptrObj ) != p_idObj )
		{
			printf( "Error caso 3: el SPtr deberia envolver el mismo SId\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SIdValor ( (SId *) SPtrObjeto ( p_ptrObj ) ) != 42UL )
		{
			printf( "Error caso 4: el SId envuelto deberia valer 42\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* El SId pasa a ser del SPtr: se libera con el, no por separado. */
		SPtrDestruir ( &p_ptrObj );
		if ( ES_VALIDO ( p_ptrObj ) )
		{
			printf( "Error caso 5: se esperaba puntero nulo tras destruir\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
# if ( defined ( MODO_DEPURACION ) )
	if ( MemNumBloquesActuales () != ulBloquesAntes )
	{
		printf( "Error caso 6: quedan %ld bloques sin liberar\n", (long) ( MemNumBloquesActuales () - ulBloquesAntes ) );
		iRes = BOOL_VAL_FALSO;
	}
# endif
	return ( iRes );
}

/* Con objeto nulo, SIdPtr da un SPtr vacio: hay que destruirlo igualmente.
   Con MODO_DEPURACION se comprueba que no queda memoria reservada. */
static int TestSIdPtrNulo01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SIdPtrNulo 01:\n" );
# if ( defined ( MODO_DEPURACION ) )
	unsigned long ulBloquesAntes = MemNumBloquesActuales ();
# endif
	SPtr * p_ptrObj = SIdPtr ( NULL );
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

static int TestSIdBloqueBin01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SIdBloqueBin 01:\n" );

	int iTamBin = (int) sizeof ( unsigned long );
	SId * p_idObj = SIdCrear ( 123456789UL );
	SBloque * p_blqDatos = SIdBloqueBin ( p_idObj );
	if ( ES_NULO ( p_blqDatos ) )
	{
		printf( "Error caso 1: no se esperaba nulo al pasar a bloque\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SBlqTam ( p_blqDatos ) != iTamBin )
		{
			printf( "Error caso 2: se esperaba un bloque de %d bytes: %d\n", iTamBin, SBlqTam ( p_blqDatos ) );
			iRes = BOOL_VAL_FALSO;
		}
		/* 123456789 = 0x075BCD15, en little endian. */
		if ( ( SBlqLeerByte ( p_blqDatos, 0 ) != 0x15 ) || ( SBlqLeerByte ( p_blqDatos, 1 ) != 0xCD ) ||
			 ( SBlqLeerByte ( p_blqDatos, 2 ) != 0x5B ) || ( SBlqLeerByte ( p_blqDatos, 3 ) != 0x07 ) )
		{
			printf( "Error caso 3: los bytes deberian ser 15 CD 5B 07\n" );
			iRes = BOOL_VAL_FALSO;
		}

		SId * p_idLeido = SIdLeerDeBloqueBin ( p_blqDatos );
		if ( ES_NULO ( p_idLeido ) )
		{
			printf( "Error caso 4: no se esperaba nulo al leer del bloque\n" );
			iRes = BOOL_VAL_FALSO;
		}
		else if ( SIdValor ( p_idLeido ) != 123456789UL )
		{
			printf( "Error caso 5: se esperaba 123456789: %lu\n", SIdValor ( p_idLeido ) );
			iRes = BOOL_VAL_FALSO;
		}
		SIdDestruir ( &p_idLeido );

		/* Rellenar un bloque que ya existe, con el valor maximo. */
		SId * p_idMax = SIdCrear ( ULONG_MAX );
		if ( SIdLlenarBloqueBin ( p_idMax, p_blqDatos ) != 1 )
		{
			printf( "Error caso 6: se esperaba 1 al rellenar el bloque\n" );
			iRes = BOOL_VAL_FALSO;
		}
		p_idLeido = SIdLeerDeBloqueBin ( p_blqDatos );
		if ( ES_NULO ( p_idLeido ) || ( SIdValor ( p_idLeido ) != ULONG_MAX ) )
		{
			printf( "Error caso 7: se esperaba ULONG_MAX tras rellenar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SIdDestruir ( &p_idLeido );
		SIdDestruir ( &p_idMax );
	}
	SBlqDestruir ( &p_blqDatos );

	/* El bloque tiene que medir justo un unsigned long. */
	SBloque * p_blqMalo = SBlqCrear ( iTamBin + 1 );
	if ( SIdLlenarBloqueBin ( p_idObj, p_blqMalo ) != 0 )
	{
		printf( "Error caso 8: con un bloque de otro tamano deberia fallar\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( SIdLeerDeBloqueBin ( p_blqMalo ) ) )
	{
		printf( "Error caso 9: leer de un bloque de otro tamano deberia dar NULL\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SBlqDestruir ( &p_blqMalo );

	if ( ES_VALIDO ( SIdBloqueBin ( NULL ) ) )
	{
		printf( "Error caso 10: un identificador nulo deberia dar NULL\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( SIdLeerDeBloqueBin ( NULL ) ) )
	{
		printf( "Error caso 11: un bloque nulo deberia dar NULL\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SIdLlenarBloqueBin ( p_idObj, NULL ) != 0 )
	{
		printf( "Error caso 12: rellenar un bloque nulo deberia fallar\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SIdDestruir ( &p_idObj );
	ErrLimpiar ();
	return ( iRes );
}

/* Con unsigned long de 4 bytes, compararlo con 2^32 da siempre falso y el
   compilador avisa; como parametro unsigned long long no. */
static int EsDosA32 ( unsigned long long ullValor )
{
	return ( ullValor == 4294967296ULL );
}

/* Lo que mide SIdBloqueBin: el unsigned long de esta maquina. */
static int TestSIdTamBloqueBin01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SIdTamBloqueBin 01:\n" );

	int iTamEsperado = ( sizeof ( unsigned long ) == 8 ) ? 8 : 4;
	SId * p_idObj = SIdCrear ( 123456789UL );
	SBloque * p_blqDatos = SIdBloqueBin ( p_idObj );
	if ( ( SIdTamBloqueBin () != iTamEsperado ) || ( SBlqTam ( p_blqDatos ) != SIdTamBloqueBin () ) )
	{
		printf( "Error caso 1: se esperaba %d, y que fuera lo que mide SIdBloqueBin: %d %d\n", iTamEsperado, SIdTamBloqueBin (), SBlqTam ( p_blqDatos ) );
		iRes = BOOL_VAL_FALSO;
	}
	SBlqDestruir ( &p_blqDatos );
	SIdDestruir ( &p_idObj );
	return ( iRes );
}

static int TestSIdBloqueMplBin01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SIdBloqueMplBin 01:\n" );

	/* 8 bytes en todas las plataformas: 123456789 = 0x075BCD15. */
	SId * p_idObj = SIdCrear ( 123456789UL );
	SBloqueMultiPlataforma * p_blqDatos = SIdBloqueMplBin ( p_idObj );
	const byte byEsperados[] = { 0x15, 0xCD, 0x5B, 0x07, 0x00, 0x00, 0x00, 0x00 };
	if ( SBlqMplTam ( p_blqDatos ) != 8 )
	{
		printf( "Error caso 1: se esperaba un bloque de 8 bytes: %d\n", SBlqMplTam ( p_blqDatos ) );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		for ( int i = 0; i < 8; i = i + 1 )
		{
			if ( SBlqMplLeerByte ( p_blqDatos, i ) != byEsperados[ i ] )
			{
				printf( "Error caso 2: byte %d: se esperaba 0x%02X: 0x%02X\n", i, byEsperados[ i ], SBlqMplLeerByte ( p_blqDatos, i ) );
				iRes = BOOL_VAL_FALSO;
			}
		}
	}
	SId * p_idLeido = SIdLeerDeBloqueMplBin ( p_blqDatos );
	if ( ES_NULO ( p_idLeido ) || ( SIdValor ( p_idLeido ) != 123456789UL ) )
	{
		printf( "Error caso 3: se esperaba leer 123456789\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SIdDestruir ( &p_idLeido );

	/* Rellenar el mismo bloque con el maximo de esta maquina. */
	SId * p_idMax = SIdCrear ( ULONG_MAX );
	if ( SIdLlenarBloqueMplBin ( p_idMax, p_blqDatos ) != 1 )
	{
		printf( "Error caso 4: se esperaba 1 al rellenar el bloque\n" );
		iRes = BOOL_VAL_FALSO;
	}
	p_idLeido = SIdLeerDeBloqueMplBin ( p_blqDatos );
	if ( ES_NULO ( p_idLeido ) || ( SIdValor ( p_idLeido ) != ULONG_MAX ) )
	{
		printf( "Error caso 5: se esperaba ULONG_MAX tras rellenar\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SIdDestruir ( &p_idLeido );
	SIdDestruir ( &p_idMax );
	SBlqMplDestruir ( &p_blqDatos );

	/* Un bloque de 4 no vale, aunque sea lo que mide un unsigned long en Windows. */
	SBloqueMultiPlataforma * p_blqMalo = SBlqMplCrear ( 4 );
	ErrLimpiar ();
	if ( ( SIdLlenarBloqueMplBin ( p_idObj, p_blqMalo ) != 0 ) || ( ErrCodigo () != ERR_PARAMETROS ) )
	{
		printf( "Error caso 6: rellenar un bloque de 4 deberia dar 0 y ERR_PARAMETROS\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( SIdLeerDeBloqueMplBin ( p_blqMalo ) ) )
	{
		printf( "Error caso 7: leer de un bloque de 4 deberia dar NULL\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SBlqMplDestruir ( &p_blqMalo );

	/* 2^32, escrito por una maquina con unsigned long de 8. */
	byte byDosA32[] = { 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00 };
	p_blqDatos = SBlqMplCrear ( 8 );
	SBlqMplEscribirBuffer ( p_blqDatos, 0, byDosA32, 8 );
	ErrLimpiar ();
	p_idLeido = SIdLeerDeBloqueMplBin ( p_blqDatos );
	if ( sizeof ( unsigned long ) == 8 )
	{
		if ( ES_NULO ( p_idLeido ) || ( EsDosA32 ( SIdValor ( p_idLeido ) ) == BOOL_VAL_FALSO ) )
		{
			printf( "Error caso 8: con unsigned long de 8 bytes deberia leerse 2^32\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		if ( ES_VALIDO ( p_idLeido ) || ( ErrCodigo () != ERR_CONVERSION_IMPOSIBLE ) )
		{
			printf( "Error caso 9: con unsigned long de 4 bytes deberia dar NULL y ERR_CONVERSION_IMPOSIBLE: %d\n", ErrCodigo () );
			iRes = BOOL_VAL_FALSO;
		}
	}
	SIdDestruir ( &p_idLeido );
	SBlqMplDestruir ( &p_blqDatos );

	if ( ES_VALIDO ( SIdBloqueMplBin ( NULL ) ) || ES_VALIDO ( SIdLeerDeBloqueMplBin ( NULL ) ) ||
		 ( SIdLlenarBloqueMplBin ( p_idObj, NULL ) != 0 ) )
	{
		printf( "Error caso 10: con nulos deberia dar NULL o 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SIdDestruir ( &p_idObj );
	ErrLimpiar ();
	return ( iRes );
}



int TestSId ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SId]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSIdCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSIdCrearValor01 () == BOOL_VAL_CIERTO ) &&
			( TestSIdEstablecerValor01 () == BOOL_VAL_CIERTO ) &&
			( TestSIdComparaciones01 () == BOOL_VAL_CIERTO ) &&
			( TestSIdComparacionesNum01 () == BOOL_VAL_CIERTO ) &&
			( TestSIdAsignar01 () == BOOL_VAL_CIERTO ) &&
			( TestSIdEstaEnRango01 () == BOOL_VAL_CIERTO ) &&
			( TestSIdComparar01 () == BOOL_VAL_CIERTO ) &&
			( TestSIdCompararNum01 () == BOOL_VAL_CIERTO ) &&
			( TestSIdHash01 () == BOOL_VAL_CIERTO ) &&
			( TestSIdPtr01 () == BOOL_VAL_CIERTO ) &&
			( TestSIdPtrNulo01 () == BOOL_VAL_CIERTO ) &&
			( TestSIdBloqueBin01 () == BOOL_VAL_CIERTO ) &&
			( TestSIdBloqueMplBin01 () == BOOL_VAL_CIERTO ) &&
			( TestSIdTamBloqueBin01 () == BOOL_VAL_CIERTO ) )
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
