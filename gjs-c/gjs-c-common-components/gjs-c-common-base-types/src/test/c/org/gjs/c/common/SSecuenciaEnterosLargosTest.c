#include "Base.h"

#include "SSecuenciaEnterosLargos.h"



static int TestSSecEntLOperaciones01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SSecEntLOperaciones 01:\n" );

	SSecuenciaEnterosLargos * p_secObj = SSecEntLCrear ();
	if ( ES_VALIDO ( p_secObj ) )
	{
		if ( ( SSecEntLEsValida ( p_secObj ) != 1 ) || ( SSecEntLNumElementos ( p_secObj ) != 0 ) )
		{
			printf( "Error caso 1: la secuencia recien creada deberia ser valida y vacia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SSecEntLInsertar ( p_secObj, 100000L ) != 1 ) ||
			 ( SSecEntLInsertar ( p_secObj, 200000L ) != 1 ) ||
			 ( SSecEntLInsertar ( p_secObj, 300000L ) != 1 ) )
		{
			printf( "Error caso 2: se esperaba poder insertar los tres enteros largos\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SSecEntLNumElementos ( p_secObj ) != 3 ) || ( SSecEntLElemento ( p_secObj, 1 ) != 200000L ) )
		{
			printf( "Error caso 3: deberia haber 3 elementos y el del indice 1 ser 200000\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SSecEntLExiste ( p_secObj, 300000L ) != 1 ) || ( SSecEntLExiste ( p_secObj, 1L ) != 0 ) )
		{
			printf( "Error caso 4: existe deberia encontrar 300000 y no 1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SSecEntLEliminar ( p_secObj, 0 ) != 1 ) ||
			 ( SSecEntLNumElementos ( p_secObj ) != 2 ) || ( SSecEntLElemento ( p_secObj, 0 ) != 200000L ) )
		{
			printf( "Error caso 5: tras eliminar el primero deberian quedar 200000 y 300000\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SSecEntLVaciar ( p_secObj );
		if ( SSecEntLNumElementos ( p_secObj ) != 0 )
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
	SSecEntLDestruir ( &p_secObj );

	if ( ES_VALIDO ( p_secObj ) )
	{
		printf( "Error caso 7: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSSecEntLInvalidos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SSecEntLInvalidos 01:\n" );

	if ( SSecEntLEsValida ( NULL ) != 0 )
	{
		printf( "Error caso 1: una secuencia nula no deberia ser valida\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SSecEntLNumElementos ( NULL ) != 0 )
	{
		printf( "Error caso 2: una secuencia nula deberia tener 0 elementos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SSecuenciaEnterosLargos * p_secNula = NULL;
	SSecEntLDestruir ( &p_secNula );
	return ( iRes );
}



int TestSSecuenciaEnterosLargos ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SSecuenciaEnterosLargos]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSSecEntLOperaciones01 () == BOOL_VAL_CIERTO ) &&
			( TestSSecEntLInvalidos01 () == BOOL_VAL_CIERTO ) )
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
