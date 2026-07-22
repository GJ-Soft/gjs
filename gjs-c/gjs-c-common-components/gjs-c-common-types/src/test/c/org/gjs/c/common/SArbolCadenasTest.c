#include "Base.h"

#include "SArbolCadenas.h"



static int TestSArbCadCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SArbCadCrear 01:\n" );
	SArbolCadenas * p_arbObj = SArbCadCrear ();
	if ( ES_VALIDO ( p_arbObj ) )
	{
		if ( SArbCadEstaVacio ( p_arbObj ) != 1 )
		{
			printf( "Error caso 1: se esperaba vacio\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SArbCadNumNodos ( p_arbObj ) != 0 )
		{
			printf( "Error caso 2: se esperaban 0 nodos: %d\n", SArbCadNumNodos ( p_arbObj ) );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el objeto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SArbCadDestruir ( &p_arbObj );
	return ( iRes );
}

static int TestSArbCadRaiz01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SArbCadRaiz 01:\n" );
	SArbolCadenas * p_arbObj = SArbCadCrear ();
	if ( ES_VALIDO ( p_arbObj ) )
	{
		/* El arbol toma la propiedad de las cadenas insertadas. */
		if ( SArbCadEstablecerRaiz ( p_arbObj, SCadGenerar ( "raiz" ) ) == 0 )
		{
			printf( "Error caso 1: no se pudo establecer la raiz\n" );
			iRes = BOOL_VAL_FALSO;
		}
		else
		{
			if ( SArbCadEstaVacio ( p_arbObj ) != 0 )
			{
				printf( "Error caso 1: no se esperaba vacio tras enraizar\n" );
				iRes = BOOL_VAL_FALSO;
			}
			if ( SCadEsIgualLiteral ( SArbCadRaiz ( p_arbObj ), "raiz" ) != 1 )
			{
				printf( "Error caso 2: se esperaba raiz \"raiz\", Resultado: %s\n", SCadValor ( SArbCadRaiz ( p_arbObj ) ) );
				iRes = BOOL_VAL_FALSO;
			}
			if ( SArbCadNumNodos ( p_arbObj ) != 1 )
			{
				printf( "Error caso 3: se esperaba 1 nodo: %d\n", SArbCadNumNodos ( p_arbObj ) );
				iRes = BOOL_VAL_FALSO;
			}
			SArbCadMoverARaiz ( p_arbObj );
			SArbCadActualInsertarHijo ( p_arbObj, SCadGenerar ( "hijo" ) );
			if ( SArbCadNumNodos ( p_arbObj ) != 2 )
			{
				printf( "Error caso 4: se esperaban 2 nodos: %d\n", SArbCadNumNodos ( p_arbObj ) );
				iRes = BOOL_VAL_FALSO;
			}
			if ( SArbCadActualNumHijos ( p_arbObj ) != 1 )
			{
				printf( "Error caso 5: se esperaba 1 hijo en la raiz: %d\n", SArbCadActualNumHijos ( p_arbObj ) );
				iRes = BOOL_VAL_FALSO;
			}
			SArbCadVaciar ( p_arbObj );
			if ( SArbCadEstaVacio ( p_arbObj ) != 1 )
			{
				printf( "Error caso 6: se esperaba vacio tras vaciar\n" );
				iRes = BOOL_VAL_FALSO;
			}
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el objeto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SArbCadDestruir ( &p_arbObj );
	return ( iRes );
}

static int TestSArbCadNulo01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SArbCadNulo 01:\n" );
	if ( SArbCadEstaVacio ( NULL ) != 1 )
	{
		printf( "Error caso 1: se esperaba vacio con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SArbCadNumNodos ( NULL ) != 0 )
	{
		printf( "Error caso 2: se esperaban 0 nodos con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( SArbCadRaiz ( NULL ) ) )
	{
		printf( "Error caso 3: se esperaba raiz nula con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

int TestSArbolCadenas ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SArbolCadenas]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSArbCadCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSArbCadRaiz01 () == BOOL_VAL_CIERTO ) &&
			( TestSArbCadNulo01 () == BOOL_VAL_CIERTO ) )
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
