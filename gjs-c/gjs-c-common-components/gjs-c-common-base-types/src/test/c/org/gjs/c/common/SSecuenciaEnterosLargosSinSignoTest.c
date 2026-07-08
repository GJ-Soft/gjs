#include "Base.h"

#include "SSecuenciaEnterosLargosSinSigno.h"



static int TestSSecEntLSSOperaciones01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SSecEntLSSOperaciones 01:\n" );

	SSecuenciaEnterosLargosSinSigno * p_secObj = SSecEntLSSCrear ();
	if ( ES_VALIDO ( p_secObj ) )
	{
		if ( ( SSecEntLSSEsValida ( p_secObj ) != 1 ) || ( SSecEntLSSNumElementos ( p_secObj ) != 0 ) )
		{
			printf( "Error caso 1: la secuencia recien creada deberia ser valida y vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SSecEntLSSInsertar ( p_secObj, 100UL ) != 1 ) ||
			 ( SSecEntLSSInsertar ( p_secObj, 200UL ) != 1 ) ||
			 ( SSecEntLSSInsertar ( p_secObj, 300UL ) != 1 ) )
		{
			printf( "Error caso 2: se esperaba poder insertar los tres valores\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SSecEntLSSNumElementos ( p_secObj ) != 3 ) || ( SSecEntLSSElemento ( p_secObj, 1 ) != 200UL ) )
		{
			printf( "Error caso 3: deberia haber 3 elementos y el del indice 1 ser 200\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SSecEntLSSExiste ( p_secObj, 300UL ) != 1 ) || ( SSecEntLSSExiste ( p_secObj, 7UL ) != 0 ) )
		{
			printf( "Error caso 4: existe deberia encontrar 300 y no 7\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SSecEntLSSEliminar ( p_secObj, 0 ) != 1 ) ||
			 ( SSecEntLSSNumElementos ( p_secObj ) != 2 ) || ( SSecEntLSSElemento ( p_secObj, 0 ) != 200UL ) )
		{
			printf( "Error caso 5: tras eliminar el primero deberian quedar 200 y 300\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SSecEntLSSVaciar ( p_secObj );
		if ( SSecEntLSSNumElementos ( p_secObj ) != 0 )
		{
			printf( "Error caso 6: tras vaciar no deberia quedar ningun elemento\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la secuencia\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SSecEntLSSDestruir ( &p_secObj );

	if ( ES_VALIDO ( p_secObj ) )
	{
		printf( "Error caso 7: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSSecEntLSSInvalidos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SSecEntLSSInvalidos 01:\n" );

	if ( SSecEntLSSEsValida ( NULL ) != 0 )
	{
		printf( "Error caso 1: una secuencia nula no deberia ser valida\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SSecEntLSSNumElementos ( NULL ) != 0 )
	{
		printf( "Error caso 2: una secuencia nula deberia tener 0 elementos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SSecuenciaEnterosLargosSinSigno * p_secNula = NULL;
	SSecEntLSSDestruir ( &p_secNula );
	return ( iRes );
}



int TestSSecuenciaEnterosLargosSinSigno ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SSecuenciaEnterosLargosSinSigno]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSSecEntLSSOperaciones01 () == BOOL_VAL_CIERTO ) &&
			( TestSSecEntLSSInvalidos01 () == BOOL_VAL_CIERTO ) )
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
