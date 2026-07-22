#include "Base.h"

#include "SEntrada.h"



static int TestSEtrCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SEtrCrear 01:\n" );
	SEntrada * p_etrObj = SEtrCrearExt ( "entrada", "una definicion" );
	if ( ES_VALIDO ( p_etrObj ) )
	{
		if ( ES_NULO ( SEtrNombre ( p_etrObj ) ) || ( CadComparar ( SEtrNombre ( p_etrObj ), "entrada" ) != COMP_IGUAL ) )
		{
			printf( "Error caso 1: se esperaba nombre \"entrada\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_NULO ( SEtrDefinicion ( p_etrObj ) ) || ( CadComparar ( SEtrDefinicion ( p_etrObj ), "una definicion" ) != COMP_IGUAL ) )
		{
			printf( "Error caso 2: se esperaba definicion \"una definicion\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEtrEsValido ( p_etrObj ) != 1 )
		{
			printf( "Error caso 3: se esperaba valido\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el objeto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SEtrDestruir ( &p_etrObj );
	return ( iRes );
}

static int TestSEtrEstablecer01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SEtrEstablecer 01:\n" );
	SEntrada * p_etrObj = SEtrCrearDef ();
	if ( ES_VALIDO ( p_etrObj ) )
	{
		if ( SEtrEstablecer ( p_etrObj, "clave", "valor" ) != 1 )
		{
			printf( "Error caso 1: se esperaba establecer correcto\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( CadComparar ( SEtrNombre ( p_etrObj ), "clave" ) != COMP_IGUAL )
		{
			printf( "Error caso 2: se esperaba nombre \"clave\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEtrEstablecerDefinicion ( p_etrObj, "otro valor" ) != 1 )
		{
			printf( "Error caso 3: se esperaba establecer definicion correcto\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( CadComparar ( SEtrDefinicion ( p_etrObj ), "otro valor" ) != COMP_IGUAL )
		{
			printf( "Error caso 4: se esperaba definicion \"otro valor\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el objeto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SEtrDestruir ( &p_etrObj );
	return ( iRes );
}

static int TestSEtrComparar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SEtrComparar 01:\n" );
	SEntrada * p_etrObj = SEtrCrearExt ( "manzana", "fruta" );
	if ( ES_VALIDO ( p_etrObj ) )
	{
		if ( SEtrEsIgualLit ( p_etrObj, "manzana" ) != 1 )
		{
			printf( "Error caso 1: se esperaba igual a \"manzana\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEtrEsMenorLit ( p_etrObj, "pera" ) != 1 )
		{
			printf( "Error caso 2: se esperaba menor que \"pera\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEtrEsMayorLit ( p_etrObj, "limon" ) != 1 )
		{
			printf( "Error caso 3: se esperaba mayor que \"limon\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SEntrada * p_etrDup = SEtrDuplicar ( p_etrObj );
		if ( ES_VALIDO ( p_etrDup ) )
		{
			if ( SEtrEsIgual ( p_etrObj, p_etrDup ) != 1 )
			{
				printf( "Error caso 4: se esperaba duplicado igual\n" );
				iRes = BOOL_VAL_FALSO;
			}
		}
		else
		{
			printf( "Error caso 4: no se pudo duplicar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SEtrDestruir ( &p_etrDup );
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el objeto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SEtrDestruir ( &p_etrObj );
	return ( iRes );
}

static int TestSEtrNulo01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SEtrNulo 01:\n" );
	if ( SEtrEsValido ( NULL ) != 0 )
	{
		printf( "Error caso 1: se esperaba no valido con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( SEtrNombre ( NULL ) ) )
	{
		printf( "Error caso 2: se esperaba nombre nulo con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SEtrEstablecer ( NULL, "a", "b" ) != 0 )
	{
		printf( "Error caso 3: se esperaba fallo con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

int TestSEntrada ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SEntrada]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSEtrCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSEtrEstablecer01 () == BOOL_VAL_CIERTO ) &&
			( TestSEtrComparar01 () == BOOL_VAL_CIERTO ) &&
			( TestSEtrNulo01 () == BOOL_VAL_CIERTO ) )
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
