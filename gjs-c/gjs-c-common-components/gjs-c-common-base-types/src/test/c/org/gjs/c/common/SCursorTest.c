#include "Base.h"

#include "SCursor.h"



static int TestSCurCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCurCrear 01:\n" );

	SCursor * p_curObj = SCurCrear ( 2, 5 );
	if ( ES_NULO ( p_curObj ) )
	{
		printf( "Error caso 1: no se esperaba nulo al crear\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( ( SCurLinea ( p_curObj ) != 2 ) || ( SCurColumna ( p_curObj ) != 5 ) )
		{
			printf( "Error caso 2: se esperaba linea 2 y columna 5\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCurEsValido ( p_curObj ) != 1 )
		{
			printf( "Error caso 3: el cursor con coordenadas positivas deberia ser valido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Establecer una coordenada negativa lo hace invalido. */
		if ( SCurEstablecerLinea ( p_curObj, -1 ) != 0 )
		{
			printf( "Error caso 4: establecer una linea negativa deberia dar cursor invalido\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	SCurDestruir ( &p_curObj );

	if ( ES_VALIDO ( p_curObj ) )
	{
		printf( "Error caso 5: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSCurComparar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCurComparar 01:\n" );

	SCursor * p_c1 = SCurCrear ( 1, 5 );
	SCursor * p_c2 = SCurCrear ( 2, 3 );
	if ( ES_VALIDO ( p_c1 ) && ES_VALIDO ( p_c2 ) )
	{
		/* Orden lexicografico: primero por linea, luego por columna. */
		if ( SCurEsMenor ( p_c1, p_c2 ) != 1 )
		{
			printf( "Error caso 1: ( 1, 5 ) deberia ser menor que ( 2, 3 )\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCurEsMayor ( p_c2, p_c1 ) != 1 )
		{
			printf( "Error caso 2: ( 2, 3 ) deberia ser mayor que ( 1, 5 )\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Misma linea, distinta columna. */
		if ( SCurEsMenorExt ( p_c1, 1, 6 ) != 1 )
		{
			printf( "Error caso 3: ( 1, 5 ) deberia ser menor que ( 1, 6 )\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Asignar copia las coordenadas y los deja iguales. */
		SCurAsignar ( p_c1, p_c2 );
		if ( SCurEsIgual ( p_c1, p_c2 ) != 1 )
		{
			printf( "Error caso 4: tras asignar deberian ser iguales\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear los cursores\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SCurDestruir ( &p_c1 );
	SCurDestruir ( &p_c2 );
	return ( iRes );
}

static int TestSCurDuplicar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCurDuplicar 01:\n" );

	SCursor * p_curObj = SCurCrear ( 4, 8 );
	if ( ES_VALIDO ( p_curObj ) )
	{
		SCursor * p_curDup = SCurDuplicar ( p_curObj );
		if ( ES_NULO ( p_curDup ) )
		{
			printf( "Error caso 1: no se esperaba nulo al duplicar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		else
		{
			if ( SCurEsIgual ( p_curObj, p_curDup ) != 1 )
			{
				printf( "Error caso 2: el duplicado deberia ser igual al original\n" );
				iRes = BOOL_VAL_FALSO;
			}
			/* Copia independiente. */
			SCurEstablecer ( p_curObj, 0, 0 );
			if ( SCurEsIgual ( p_curObj, p_curDup ) != 0 )
			{
				printf( "Error caso 3: modificar el original no deberia afectar al duplicado\n" );
				iRes = BOOL_VAL_FALSO;
			}
			SCurDestruir ( &p_curDup );
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el cursor\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SCurDestruir ( &p_curObj );
	return ( iRes );
}

static int TestSCurInvalidos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCurInvalidos 01:\n" );

	if ( SCurEsValido ( NULL ) != 0 )
	{
		printf( "Error caso 1: un cursor nulo no deberia ser valido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SCurLinea ( NULL ) != -1 )
	{
		printf( "Error caso 2: la linea de un cursor nulo deberia ser -1\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SCursor * p_curNulo = NULL;
	SCurDestruir ( &p_curNulo );
	return ( iRes );
}



int TestSCursor ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SCursor]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSCurCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSCurComparar01 () == BOOL_VAL_CIERTO ) &&
			( TestSCurDuplicar01 () == BOOL_VAL_CIERTO ) &&
			( TestSCurInvalidos01 () == BOOL_VAL_CIERTO ) )
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
