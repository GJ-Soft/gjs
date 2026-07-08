#include "Base.h"

#include "SVectorFlags.h"



static int TestSVecFlgCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SVecFlgCrear 01:\n" );

	SVectorFlags * p_vecfObj = SVecFlgCrear ( 8 );
	if ( ES_NULO ( p_vecfObj ) )
	{
		printf( "Error caso 1: no se esperaba nulo al crear\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SVecFlgEsValido ( p_vecfObj ) != 1 )
		{
			printf( "Error caso 2: el vector de flags recien creado deberia ser valido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SVecFlgNumFlags ( p_vecfObj ) != 8 )
		{
			printf( "Error caso 3: se esperaban 8 flags: %lu\n", SVecFlgNumFlags ( p_vecfObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		/* Todos los flags nacen inactivos. */
		if ( SVecFlgFlagEstaActivo ( p_vecfObj, 0 ) != 0 )
		{
			printf( "Error caso 4: los flags deberian nacer inactivos\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	SVecFlgDestruir ( &p_vecfObj );

	if ( ES_VALIDO ( p_vecfObj ) )
	{
		printf( "Error caso 5: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* Crear con 0 flags debe fallar. */
	if ( ES_VALIDO ( SVecFlgCrear ( 0 ) ) )
	{
		printf( "Error caso 6: se esperaba nulo al crear con 0 flags\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSVecFlgActivar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SVecFlgActivar 01:\n" );

	SVectorFlags * p_vecfObj = SVecFlgCrear ( 8 );
	if ( ES_VALIDO ( p_vecfObj ) )
	{
		if ( SVecFlgActivarFlag ( p_vecfObj, 3 ) != 1 )
		{
			printf( "Error caso 1: se esperaba resultado 1 al activar el flag\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SVecFlgFlagEstaActivo ( p_vecfObj, 3 ) != 1 )
		{
			printf( "Error caso 2: el flag 3 deberia estar activo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Los flags vecinos siguen inactivos. */
		if ( ( SVecFlgFlagEstaActivo ( p_vecfObj, 2 ) != 0 ) || ( SVecFlgFlagEstaActivo ( p_vecfObj, 4 ) != 0 ) )
		{
			printf( "Error caso 3: los flags vecinos no deberian activarse\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Desactivar. */
		if ( SVecFlgDesactivarFlag ( p_vecfObj, 3 ) != 1 )
		{
			printf( "Error caso 4: se esperaba resultado 1 al desactivar el flag\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SVecFlgFlagEstaActivo ( p_vecfObj, 3 ) != 0 )
		{
			printf( "Error caso 5: el flag 3 deberia estar inactivo tras desactivar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Activar fuera de rango debe fallar. */
		if ( SVecFlgActivarFlag ( p_vecfObj, 8 ) != 0 )
		{
			printf( "Error caso 6: activar un flag fuera de rango deberia fallar\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el vector de flags\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SVecFlgDestruir ( &p_vecfObj );
	return ( iRes );
}

static int TestSVecFlgLimpiar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SVecFlgLimpiar 01:\n" );

	SVectorFlags * p_vecfObj = SVecFlgCrear ( 8 );
	if ( ES_VALIDO ( p_vecfObj ) )
	{
		SVecFlgActivarFlag ( p_vecfObj, 1 );
		SVecFlgActivarFlag ( p_vecfObj, 5 );

		if ( SVecFlgLimpiar ( p_vecfObj ) != 1 )
		{
			printf( "Error caso 1: se esperaba resultado 1 al limpiar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SVecFlgFlagEstaActivo ( p_vecfObj, 1 ) != 0 ) || ( SVecFlgFlagEstaActivo ( p_vecfObj, 5 ) != 0 ) )
		{
			printf( "Error caso 2: todos los flags deberian quedar inactivos tras limpiar\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el vector de flags\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SVecFlgDestruir ( &p_vecfObj );
	return ( iRes );
}

static int TestSVecFlgEncapsular01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SVecFlgEncapsular 01:\n" );

	SBuffer * p_bufObj = SBufCrear ( 4 );
	if ( ES_VALIDO ( p_bufObj ) )
	{
		/* Encapsular un buffer valido: el vector de flags pasa a gestionarlo. */
		SVectorFlags * p_vecfObj = SVecFlgEncapsular ( p_bufObj );
		if ( ES_NULO ( p_vecfObj ) )
		{
			printf( "Error caso 1: no se esperaba nulo al encapsular\n" );
			iRes = BOOL_VAL_FALSO;
			SBufDestruir ( &p_bufObj );
		}
		else
		{
			if ( SVecFlgNumFlags ( p_vecfObj ) != 4 )
			{
				printf( "Error caso 2: se esperaban 4 flags: %lu\n", SVecFlgNumFlags ( p_vecfObj ) );
				iRes = BOOL_VAL_FALSO;
			}
			SVecFlgActivarFlag ( p_vecfObj, 2 );
			if ( SVecFlgFlagEstaActivo ( p_vecfObj, 2 ) != 1 )
			{
				printf( "Error caso 3: el flag 2 deberia estar activo\n" );
				iRes = BOOL_VAL_FALSO;
			}
			/* El vector gestiona el buffer: destruirlo lo libera tambien. */
			SVecFlgDestruir ( &p_vecfObj );
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el buffer\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSVecFlgInvalidos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SVecFlgInvalidos 01:\n" );

	if ( SVecFlgEsValido ( NULL ) != 0 )
	{
		printf( "Error caso 1: un vector de flags nulo no deberia ser valido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SVecFlgNumFlags ( NULL ) != 0 )
	{
		printf( "Error caso 2: el numero de flags de un vector nulo deberia ser 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SVecFlgActivarFlag ( NULL, 0 ) != 0 )
	{
		printf( "Error caso 3: activar un flag en un vector nulo deberia fallar\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SVectorFlags * p_vecfNulo = NULL;
	SVecFlgDestruir ( &p_vecfNulo );
	return ( iRes );
}



int TestSVectorFlags ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SVectorFlags]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSVecFlgCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSVecFlgActivar01 () == BOOL_VAL_CIERTO ) &&
			( TestSVecFlgLimpiar01 () == BOOL_VAL_CIERTO ) &&
			( TestSVecFlgEncapsular01 () == BOOL_VAL_CIERTO ) &&
			( TestSVecFlgInvalidos01 () == BOOL_VAL_CIERTO ) )
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
