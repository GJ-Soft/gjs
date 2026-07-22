#include "TiposDatos.h"

#include "SAccion.h"



static int _TestSAccFuncion ( int iCodigo )
{
	return ( iCodigo + 1 );
}

static int TestSAccCrearCodigo01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SAccCrearCodigo 01:\n" );
	SAccion * p_accObj = SAccCrearExt ( TIP_ACC_CODIGO, 50, NULL );
	if ( ES_VALIDO ( p_accObj ) )
	{
		if ( SAccTipo ( p_accObj ) != TIP_ACC_CODIGO )
		{
			printf( "Error caso 1: se esperaba tipo codigo: %d\n", SAccTipo ( p_accObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SAccCodigo ( p_accObj ) != 50 )
		{
			printf( "Error caso 2: se esperaba codigo 50: %d\n", SAccCodigo ( p_accObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SAccRetornaCodigo ( p_accObj ) != 1 )
		{
			printf( "Error caso 3: se esperaba retorna codigo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SAccEsValida ( p_accObj ) != 1 )
		{
			printf( "Error caso 4: se esperaba valida\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SAccEjecutar ( p_accObj ) != 50 )
		{
			printf( "Error caso 5: se esperaba ejecutar == 50\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el objeto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SAccDestruir ( &p_accObj );
	return ( iRes );
}

static int TestSAccCrearFuncion01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SAccCrearFuncion 01:\n" );
	SAccion * p_accObj = SAccCrearExt ( TIP_ACC_FUNCION, 7, _TestSAccFuncion );
	if ( ES_VALIDO ( p_accObj ) )
	{
		if ( SAccEjecutaFuncion ( p_accObj ) != 1 )
		{
			printf( "Error caso 1: se esperaba ejecuta funcion\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SAccEsValida ( p_accObj ) != 1 )
		{
			printf( "Error caso 2: se esperaba valida\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SAccFuncion ( p_accObj ) != _TestSAccFuncion )
		{
			printf( "Error caso 3: la funcion no coincide\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SAccEjecutar ( p_accObj ) != 8 )
		{
			printf( "Error caso 4: se esperaba ejecutar == 8: %d\n", SAccEjecutar ( p_accObj ) );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el objeto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SAccDestruir ( &p_accObj );
	return ( iRes );
}

static int TestSAccCrearSalir01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SAccCrearSalir 01:\n" );
	SAccion * p_accObj = SAccCrear ( TIP_ACC_SALIR );
	if ( ES_VALIDO ( p_accObj ) )
	{
		if ( SAccOrdenaSalir ( p_accObj ) != 1 )
		{
			printf( "Error caso 1: se esperaba ordena salir\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SAccCodigo ( p_accObj ) != COD_ACC_SALIR )
		{
			printf( "Error caso 2: se esperaba codigo salir: %d\n", SAccCodigo ( p_accObj ) );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el objeto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SAccDestruir ( &p_accObj );

	/* Un tipo no valido no debe crear objeto. */
	SAccion * p_accNulo = SAccCrear ( TIP_ACC_NULO );
	if ( ES_VALIDO ( p_accNulo ) )
	{
		printf( "Error caso 3: no se esperaba crear con tipo nulo\n" );
		iRes = BOOL_VAL_FALSO;
		SAccDestruir ( &p_accNulo );
	}
	return ( iRes );
}

static int TestSAccDuplicar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SAccDuplicar 01:\n" );
	SAccion * p_accObj = SAccCrearExt ( TIP_ACC_CODIGO, 33, NULL );
	if ( ES_VALIDO ( p_accObj ) )
	{
		SAccion * p_accDup = SAccDuplicar ( p_accObj );
		if ( ES_VALIDO ( p_accDup ) )
		{
			if ( SAccTipo ( p_accDup ) != TIP_ACC_CODIGO )
			{
				printf( "Error caso 1: el duplicado no conserva el tipo\n" );
				iRes = BOOL_VAL_FALSO;
			}
			if ( SAccCodigo ( p_accDup ) != 33 )
			{
				printf( "Error caso 2: el duplicado no conserva el codigo: %d\n", SAccCodigo ( p_accDup ) );
				iRes = BOOL_VAL_FALSO;
			}
		}
		else
		{
			printf( "Error caso 1: no se pudo duplicar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SAccDestruir ( &p_accDup );
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el objeto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SAccDestruir ( &p_accObj );
	return ( iRes );
}

static int TestSAccNulo01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SAccNulo 01:\n" );
	if ( SAccEsValida ( NULL ) != 0 )
	{
		printf( "Error caso 1: se esperaba no valida con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SAccTipo ( NULL ) != TIP_ACC_NULO )
	{
		printf( "Error caso 2: se esperaba tipo nulo con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SAccCodigo ( NULL ) != -1 )
	{
		printf( "Error caso 3: se esperaba codigo -1 con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SAccEjecutar ( NULL ) != -1 )
	{
		printf( "Error caso 4: se esperaba ejecutar -1 con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

int TestSAccion ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SAccion]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSAccCrearCodigo01 () == BOOL_VAL_CIERTO ) &&
			( TestSAccCrearFuncion01 () == BOOL_VAL_CIERTO ) &&
			( TestSAccCrearSalir01 () == BOOL_VAL_CIERTO ) &&
			( TestSAccDuplicar01 () == BOOL_VAL_CIERTO ) &&
			( TestSAccNulo01 () == BOOL_VAL_CIERTO ) )
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
