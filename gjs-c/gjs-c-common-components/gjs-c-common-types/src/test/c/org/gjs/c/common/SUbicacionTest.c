#include "Base.h"

#include "SUbicacion.h"


/* Primer valor que un long con signo ya no puede representar: LONG_MAX + 1.
   Vale igual con long de 4 bytes ( Windows ) que de 8 ( Cygwin, Linux ). */
#define ULONG_MITAD		( (unsigned long) LONG_MAX + 1UL )



static int TestSUbcCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SUbcCrear 01:\n" );
	SUbicacion * p_ubcObj = SUbcCrear ( 10, 100 );
	if ( ES_VALIDO ( p_ubcObj ) )
	{
		if ( SUbcPos ( p_ubcObj ) != 10 )
		{
			printf( "Error caso 1: se esperaba pos 10: %lu\n", SUbcPos ( p_ubcObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SUbcTam ( p_ubcObj ) != 100 )
		{
			printf( "Error caso 2: se esperaba tam 100: %lu\n", SUbcTam ( p_ubcObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SUbcEsValida ( p_ubcObj ) != 1 )
		{
			printf( "Error caso 3: se esperaba valida\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el objeto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SUbcDestruir ( &p_ubcObj );
	return ( iRes );
}

static int TestSUbcCrearDef01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SUbcCrearDef 01:\n" );
	SUbicacion * p_ubcObj = SUbcCrearDef ();
	if ( ES_VALIDO ( p_ubcObj ) )
	{
		if ( SUbcEsValida ( p_ubcObj ) != 0 )
		{
			printf( "Error caso 1: se esperaba no valida (tam 0)\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SUbcPos ( p_ubcObj ) != SUBC_SIN_POSICION )
		{
			printf( "Error caso 2: se esperaba sin posicion: %lu\n", SUbcPos ( p_ubcObj ) );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el objeto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SUbcDestruir ( &p_ubcObj );
	return ( iRes );
}

static int TestSUbcEstablecer01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SUbcEstablecer 01:\n" );
	SUbicacion * p_ubcObj = SUbcCrearDef ();
	if ( ES_VALIDO ( p_ubcObj ) )
	{
		SUbcEstablecer ( p_ubcObj, 20, 40 );
		if ( ( SUbcPos ( p_ubcObj ) != 20 ) || ( SUbcTam ( p_ubcObj ) != 40 ) )
		{
			printf( "Error caso 1: se esperaba pos 20 tam 40: %lu %lu\n", SUbcPos ( p_ubcObj ), SUbcTam ( p_ubcObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		SUbcEstablecerPos ( p_ubcObj, 5 );
		if ( SUbcPos ( p_ubcObj ) != 5 )
		{
			printf( "Error caso 2: se esperaba pos 5: %lu\n", SUbcPos ( p_ubcObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		SUbcEstablecerTam ( p_ubcObj, 8 );
		if ( SUbcTam ( p_ubcObj ) != 8 )
		{
			printf( "Error caso 3: se esperaba tam 8: %lu\n", SUbcTam ( p_ubcObj ) );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el objeto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SUbcDestruir ( &p_ubcObj );
	return ( iRes );
}

static int TestSUbcDesplazar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SUbcDesplazar 01:\n" );
	SUbicacion * p_ubcObj = SUbcCrear ( 10, 100 );
	if ( ES_VALIDO ( p_ubcObj ) )
	{
		if ( SUbcDesplazar ( p_ubcObj, 5 ) != 1 )
		{
			printf( "Error caso 1: se esperaba desplazamiento correcto\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SUbcPos ( p_ubcObj ) != 15 )
		{
			printf( "Error caso 2: se esperaba pos 15: %lu\n", SUbcPos ( p_ubcObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SUbcDesplazar ( p_ubcObj, -100 ) != 0 )
		{
			printf( "Error caso 3: se esperaba desplazamiento rechazado (pos negativa)\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SUbcPos ( p_ubcObj ) != 15 )
		{
			printf( "Error caso 4: se esperaba pos sin cambios 15: %lu\n", SUbcPos ( p_ubcObj ) );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el objeto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SUbcDestruir ( &p_ubcObj );
	return ( iRes );
}

static int TestSUbcNulo01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SUbcNulo 01:\n" );
	if ( SUbcEsValida ( NULL ) != 0 )
	{
		printf( "Error caso 1: se esperaba no valida con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SUbcDesplazar ( NULL, 5 ) != 0 )
	{
		printf( "Error caso 2: se esperaba fallo con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

/* La frontera del tipo. El desplazamiento sigue siendo long con signo, y la
   posicion ya no: se comprueba cruzar LONG_MAX en los dos sentidos, no pasar
   de 0 ni llegar a la marca, y el caso de LONG_MIN, cuya magnitud no cabe en
   un long. */
static int TestSUbcFrontera01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SUbcFrontera 01:\n" );
	SUbicacion * p_ubcObj = SUbcCrear ( (unsigned long) LONG_MAX, ULONG_MITAD );
	if ( ES_VALIDO ( p_ubcObj ) )
	{
		if ( SUbcTam ( p_ubcObj ) != ULONG_MITAD )
		{
			printf( "Error caso 1: se esperaba tam %lu: %lu\n", ULONG_MITAD, SUbcTam ( p_ubcObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		/* Cruzar LONG_MAX hacia delante. */
		if ( ( SUbcDesplazar ( p_ubcObj, 1 ) != 1 ) || ( SUbcPos ( p_ubcObj ) != ULONG_MITAD ) )
		{
			printf( "Error caso 2: desde LONG_MAX + 1 deberia quedar en %lu: %lu\n", ULONG_MITAD, SUbcPos ( p_ubcObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		/* LONG_MIN desde LONG_MAX + 1 deja justo 0. */
		if ( ( SUbcDesplazar ( p_ubcObj, LONG_MIN ) != 1 ) || ( SUbcPos ( p_ubcObj ) != 0UL ) )
		{
			printf( "Error caso 3: con LONG_MIN deberia quedar en 0: %lu\n", SUbcPos ( p_ubcObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		/* Por debajo de 0, no. */
		if ( ( SUbcDesplazar ( p_ubcObj, -1 ) != 0 ) || ( SUbcPos ( p_ubcObj ) != 0UL ) )
		{
			printf( "Error caso 4: desde 0 no deberia retroceder: %lu\n", SUbcPos ( p_ubcObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		/* Hasta ULONG_MAX - 1 si, hasta la marca no. */
		SUbcEstablecerPos ( p_ubcObj, ULONG_MAX - 2UL );
		if ( ( SUbcDesplazar ( p_ubcObj, 1 ) != 1 ) || ( SUbcPos ( p_ubcObj ) != ULONG_MAX - 1UL ) )
		{
			printf( "Error caso 5: deberia llegar a ULONG_MAX - 1: %lu\n", SUbcPos ( p_ubcObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SUbcDesplazar ( p_ubcObj, 1 ) != 0 ) || ( SUbcPos ( p_ubcObj ) != ULONG_MAX - 1UL ) )
		{
			printf( "Error caso 6: no deberia llegar a la marca SUBC_SIN_POSICION: %lu\n", SUbcPos ( p_ubcObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SUbcEsValida ( p_ubcObj ) != 1 )
		{
			printf( "Error caso 7: con posicion ULONG_MAX - 1 deberia ser valida\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Una ubicacion sin posicion ni es valida ni se desplaza. */
		SUbcEstablecerPos ( p_ubcObj, SUBC_SIN_POSICION );
		if ( SUbcEsValida ( p_ubcObj ) != 0 )
		{
			printf( "Error caso 8: sin posicion no deberia ser valida\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SUbcDesplazar ( p_ubcObj, -5 ) != 0 ) || ( SUbcPos ( p_ubcObj ) != SUBC_SIN_POSICION ) )
		{
			printf( "Error caso 9: sin posicion no deberia desplazarse: %lu\n", SUbcPos ( p_ubcObj ) );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el objeto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SUbcDestruir ( &p_ubcObj );

	if ( SUbcPos ( NULL ) != SUBC_SIN_POSICION )
	{
		printf( "Error caso 10: con nulo se esperaba SUBC_SIN_POSICION\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

int TestSUbicacion ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SUbicacion]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSUbcCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSUbcCrearDef01 () == BOOL_VAL_CIERTO ) &&
			( TestSUbcEstablecer01 () == BOOL_VAL_CIERTO ) &&
			( TestSUbcDesplazar01 () == BOOL_VAL_CIERTO ) &&
			( TestSUbcNulo01 () == BOOL_VAL_CIERTO ) &&
			( TestSUbcFrontera01 () == BOOL_VAL_CIERTO ) )
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
