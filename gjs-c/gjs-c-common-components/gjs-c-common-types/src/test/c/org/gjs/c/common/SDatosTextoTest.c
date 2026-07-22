#include "Base.h"

#include "SDatosTexto.h"



static int TestSDatTxtCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SDatTxtCrear 01:\n" );
	SDatosTexto * p_datObj = SDatTxtCrear ( 64, 0 );
	if ( ES_VALIDO ( p_datObj ) )
	{
		if ( SDatTxtEsDeTamFijo ( p_datObj ) != 0 )
		{
			printf( "Error caso 1: no se esperaba tam fijo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SDatTxtEstaVacio ( p_datObj ) != 1 )
		{
			printf( "Error caso 2: se esperaba vacio\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SDatTxtLongitud ( p_datObj ) != 0 )
		{
			printf( "Error caso 3: se esperaba longitud 0: %d\n", SDatTxtLongitud ( p_datObj ) );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el objeto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SDatTxtDestruir ( &p_datObj );
	return ( iRes );
}

static int TestSDatTxtCrear02 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SDatTxtCrear 02:\n" );
	/* Un tamano no positivo no debe crear objeto. */
	SDatosTexto * p_datObj = SDatTxtCrear ( 0, 0 );
	if ( ES_VALIDO ( p_datObj ) )
	{
		printf( "Error caso 1: no se esperaba crear con tam 0\n" );
		iRes = BOOL_VAL_FALSO;
		SDatTxtDestruir ( &p_datObj );
	}
	return ( iRes );
}

static int TestSDatTxtTamFijo01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SDatTxtTamFijo 01:\n" );
	SDatosTexto * p_datObj = SDatTxtCrear ( 32, 0 );
	if ( ES_VALIDO ( p_datObj ) )
	{
		SDatTxtActivarTamFijo ( p_datObj );
		if ( SDatTxtEsDeTamFijo ( p_datObj ) != 1 )
		{
			printf( "Error caso 1: se esperaba tam fijo tras activar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SDatTxtDesactivarTamFijo ( p_datObj );
		if ( SDatTxtEsDeTamFijo ( p_datObj ) != 0 )
		{
			printf( "Error caso 2: no se esperaba tam fijo tras desactivar\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el objeto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SDatTxtDestruir ( &p_datObj );
	return ( iRes );
}

static int TestSDatTxtContenido01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SDatTxtContenido 01:\n" );
	SDatosTexto * p_datObj = SDatTxtCrear ( 64, 0 );
	if ( ES_VALIDO ( p_datObj ) )
	{
		if ( SDatTxtAsignarContenidoLit ( p_datObj, "hola mundo" ) != 1 )
		{
			printf( "Error caso 1: no se pudo asignar el contenido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SDatTxtLongitud ( p_datObj ) != 10 )
		{
			printf( "Error caso 2: se esperaba longitud 10: %d\n", SDatTxtLongitud ( p_datObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SDatTxtEstaVacio ( p_datObj ) != 0 )
		{
			printf( "Error caso 3: no se esperaba vacio tras asignar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		char * p_cContenido = SDatTxtContenidoValor ( p_datObj );
		if ( ES_NULO ( p_cContenido ) || ( CadComparar ( p_cContenido, "hola mundo" ) != COMP_IGUAL ) )
		{
			printf( "Error caso 4: se esperaba contenido \"hola mundo\": [%s]\n", ES_VALIDO ( p_cContenido ) ? p_cContenido : "(nulo)" );
			iRes = BOOL_VAL_FALSO;
		}
		SDatTxtLimpiar ( p_datObj );
		if ( SDatTxtEstaVacio ( p_datObj ) != 1 )
		{
			printf( "Error caso 5: se esperaba vacio tras limpiar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SDatTxtLongitud ( p_datObj ) != 0 )
		{
			printf( "Error caso 6: se esperaba longitud 0 tras limpiar: %d\n", SDatTxtLongitud ( p_datObj ) );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el objeto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SDatTxtDestruir ( &p_datObj );
	return ( iRes );
}

static int TestSDatTxtNulo01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SDatTxtNulo 01:\n" );
	if ( SDatTxtEstaVacio ( NULL ) != 1 )
	{
		printf( "Error caso 1: se esperaba vacio con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SDatTxtLongitud ( NULL ) != 0 )
	{
		printf( "Error caso 2: se esperaba longitud 0 con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

int TestSDatosTexto ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SDatosTexto]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSDatTxtCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSDatTxtCrear02 () == BOOL_VAL_CIERTO ) &&
			( TestSDatTxtTamFijo01 () == BOOL_VAL_CIERTO ) &&
			( TestSDatTxtContenido01 () == BOOL_VAL_CIERTO ) &&
			( TestSDatTxtNulo01 () == BOOL_VAL_CIERTO ) )
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
