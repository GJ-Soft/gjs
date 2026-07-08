#include "Base.h"

#include "SDefDato.h"
#include <Tipos.h>



static int NombreEs ( const char * p_cNombre, const char * p_cEsperado )
{
	return ( CadComparar ( (char *) p_cNombre, (char *) p_cEsperado ) == COMP_IGUAL );
}



static int TestSDefDatValor01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SDefDatValor 01:\n" );

	/* Dato por valor: entero llamado "edad" con valor por defecto "0". */
	SDefDato * p_ddatObj = SDefDatCrear ( 1, "edad", TIP_NUMERO_ENTERO, 0, 0, 0, "0" );
	if ( ES_NULO ( p_ddatObj ) )
	{
		printf( "Error caso 1: no se esperaba nulo al crear\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SDefDatEsValido ( p_ddatObj ) != 1 )
		{
			printf( "Error caso 2: el dato recien creado deberia ser valido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SDefDatId ( p_ddatObj ) != 1 ) || ( SDefDatTipo ( p_ddatObj ) != TIP_NUMERO_ENTERO ) )
		{
			printf( "Error caso 3: id/tipo deberian ser 1 y entero\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ! NombreEs ( SDefDatNombre ( p_ddatObj ), "edad" ) )
		{
			printf( "Error caso 4: el nombre deberia ser \"edad\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SDefDatEsValor ( p_ddatObj ) != 1 ) || ( SDefDatEsReferencia ( p_ddatObj ) != 0 ) )
		{
			printf( "Error caso 5: deberia ser por valor y no por referencia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ! NombreEs ( SDefDatValorDefecto ( p_ddatObj ), "0" ) )
		{
			printf( "Error caso 6: el valor por defecto deberia ser \"0\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	SDefDatDestruir ( &p_ddatObj );

	if ( ES_VALIDO ( p_ddatObj ) )
	{
		printf( "Error caso 7: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSDefDatReferencia01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SDefDatReferencia 01:\n" );

	/* Dato por referencia: binario de 8 bytes ( sin valor por defecto ). */
	SDefDato * p_ddatObj = SDefDatCrear ( 2, "buf", TIP_BINARIO, 1, 8, 0, NULL );
	if ( ES_VALIDO ( p_ddatObj ) )
	{
		if ( ( SDefDatEsReferencia ( p_ddatObj ) != 1 ) || ( SDefDatEsValor ( p_ddatObj ) != 0 ) )
		{
			printf( "Error caso 1: deberia ser por referencia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SDefDatTam ( p_ddatObj ) != 8 )
		{
			printf( "Error caso 2: el tamano deberia ser 8\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Un dato por referencia no tiene valor por defecto. */
		if ( ES_VALIDO ( SDefDatValorDefecto ( p_ddatObj ) ) )
		{
			printf( "Error caso 3: un dato por referencia no deberia tener valor por defecto\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el dato binario\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SDefDatDestruir ( &p_ddatObj );
	return ( iRes );
}

static int TestSDefDatInvalidos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SDefDatInvalidos 01:\n" );

	/* Id 0 no es valido. */
	if ( ES_VALIDO ( SDefDatCrear ( 0, "x", TIP_NUMERO_ENTERO, 0, 0, 0, NULL ) ) )
	{
		printf( "Error caso 1: crear con id 0 deberia fallar\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* Binario sin tamano no es valido. */
	if ( ES_VALIDO ( SDefDatCrear ( 1, "x", TIP_BINARIO, 0, 0, 0, NULL ) ) )
	{
		printf( "Error caso 2: crear un binario sin tamano deberia fallar\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SDefDatEsValido ( NULL ) != 0 )
	{
		printf( "Error caso 3: un dato nulo no deberia ser valido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SDefDato * p_ddatNulo = NULL;
	SDefDatDestruir ( &p_ddatNulo );
	return ( iRes );
}



int TestSDefDato ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SDefDato]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSDefDatValor01 () == BOOL_VAL_CIERTO ) &&
			( TestSDefDatReferencia01 () == BOOL_VAL_CIERTO ) &&
			( TestSDefDatInvalidos01 () == BOOL_VAL_CIERTO ) )
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
