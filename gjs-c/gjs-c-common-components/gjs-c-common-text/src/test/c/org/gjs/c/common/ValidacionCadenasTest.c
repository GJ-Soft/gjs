#include "Base.h"

#include "ValidacionCadenas.h"



static int TestCadEsCodigoValido01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test CadEsCodigoValido 01:\n" );

	/* Alfanumerico y empezando por letra. */
	if ( CadEsCodigoValido ( "ABC123" ) != 1 )
	{
		printf( "Error caso 1: \"ABC123\" deberia ser un codigo valido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* La raya inferior y los dos puntos cuentan como alfanumericos. */
	if ( CadEsCodigoValido ( "cod_1" ) != 1 )
	{
		printf( "Error caso 2: \"cod_1\" deberia ser un codigo valido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* Un codigo no puede empezar por digito. */
	if ( CadEsCodigoValido ( "1ABC" ) != 0 )
	{
		printf( "Error caso 3: \"1ABC\" no deberia ser un codigo valido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* Un codigo no admite espacios. */
	if ( CadEsCodigoValido ( "AB C" ) != 0 )
	{
		printf( "Error caso 4: \"AB C\" no deberia ser un codigo valido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* Ni signos de puntuacion. */
	if ( CadEsCodigoValido ( "AB-C" ) != 0 )
	{
		printf( "Error caso 5: \"AB-C\" no deberia ser un codigo valido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* Un codigo vacio no es valido. */
	if ( CadEsCodigoValido ( "" ) != 0 )
	{
		printf( "Error caso 6: la cadena vacia no deberia ser un codigo valido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( CadEsCodigoValido ( NULL ) != 0 )
	{
		printf( "Error caso 7: un puntero nulo no deberia ser un codigo valido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestCadEsNombreValido01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test CadEsNombreValido 01:\n" );

	if ( CadEsNombreValido ( "importe_total" ) != 1 )
	{
		printf( "Error caso 1: \"importe_total\" deberia ser un nombre valido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* Un nombre, a diferencia de un codigo, admite signos de puntuacion. */
	if ( CadEsNombreValido ( "importe-total" ) != 1 )
	{
		printf( "Error caso 2: \"importe-total\" deberia ser un nombre valido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* Pero no espacios. */
	if ( CadEsNombreValido ( "con espacio" ) != 0 )
	{
		printf( "Error caso 3: \"con espacio\" no deberia ser un nombre valido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* Ni empezar por algo que no sea letra. */
	if ( CadEsNombreValido ( "1nombre" ) != 0 )
	{
		printf( "Error caso 4: \"1nombre\" no deberia ser un nombre valido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* Ni caracteres no imprimibles. */
	if ( CadEsNombreValido ( "nombre\x01" ) != 0 )
	{
		printf( "Error caso 5: un nombre con un caracter de control no deberia ser valido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* Ni caracteres fuera del ASCII de 7 bits. */
	if ( CadEsNombreValido ( "nombre\xF1" ) != 0 )
	{
		printf( "Error caso 6: un nombre con un caracter no estandar no deberia ser valido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( CadEsNombreValido ( "" ) != 0 )
	{
		printf( "Error caso 7: la cadena vacia no deberia ser un nombre valido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( CadEsNombreValido ( NULL ) != 0 )
	{
		printf( "Error caso 8: un puntero nulo no deberia ser un nombre valido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestCadEsDescripcionValida01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test CadEsDescripcionValida 01:\n" );

	/* Una descripcion admite espacios y puntuacion. */
	if ( CadEsDescripcionValida ( "Una descripcion, con comas." ) != 1 )
	{
		printf( "Error caso 1: la descripcion deberia ser valida\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* El tabulador se considera imprimible. */
	if ( CadEsDescripcionValida ( "con\ttabulador" ) != 1 )
	{
		printf( "Error caso 2: el tabulador deberia admitirse en una descripcion\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* El salto de linea no. */
	if ( CadEsDescripcionValida ( "primera\nsegunda" ) != 0 )
	{
		printf( "Error caso 3: el salto de linea no deberia admitirse en una descripcion\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* Una descripcion vacia es valida: no se le exige longitud. */
	if ( CadEsDescripcionValida ( "" ) != 1 )
	{
		printf( "Error caso 4: la descripcion vacia deberia ser valida\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( CadEsDescripcionValida ( NULL ) != 0 )
	{
		printf( "Error caso 5: un puntero nulo no deberia ser una descripcion valida\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSCadValidaciones01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCadValidaciones 01:\n" );

	SCadena * p_cadCod = SCadGenerar ( "COD1" );
	SCadena * p_cadNom = SCadGenerar ( "importe_total" );
	SCadena * p_cadDesc = SCadGenerar ( "Importe total de la factura" );
	if ( ES_VALIDO ( p_cadCod ) && ES_VALIDO ( p_cadNom ) && ES_VALIDO ( p_cadDesc ) )
	{
		if ( SCadEsCodigoValido ( p_cadCod ) != 1 )
		{
			printf( "Error caso 1: \"COD1\" deberia ser un codigo valido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCadEsNombreValido ( p_cadNom ) != 1 )
		{
			printf( "Error caso 2: \"importe_total\" deberia ser un nombre valido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCadEsDescripcionValida ( p_cadDesc ) != 1 )
		{
			printf( "Error caso 3: la descripcion deberia ser valida\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Una descripcion con espacios no vale ni como codigo ni como nombre. */
		if ( SCadEsCodigoValido ( p_cadDesc ) != 0 )
		{
			printf( "Error caso 4: la descripcion no deberia valer como codigo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCadEsNombreValido ( p_cadDesc ) != 0 )
		{
			printf( "Error caso 5: la descripcion no deberia valer como nombre\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Un nombre con raya inferior si vale como codigo. */
		if ( SCadEsCodigoValido ( p_cadNom ) != 1 )
		{
			printf( "Error caso 6: \"importe_total\" deberia valer como codigo\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron generar las cadenas\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SCadDestruir ( &p_cadCod );
	SCadDestruir ( &p_cadNom );
	SCadDestruir ( &p_cadDesc );

	/* Una cadena vacia solo es valida como descripcion. */
	SCadena * p_cadVacia = SCadCrear ( 20 );
	if ( ES_VALIDO ( p_cadVacia ) )
	{
		if ( SCadEsCodigoValido ( p_cadVacia ) != 0 )
		{
			printf( "Error caso 7: la cadena vacia no deberia ser un codigo valido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCadEsNombreValido ( p_cadVacia ) != 0 )
		{
			printf( "Error caso 8: la cadena vacia no deberia ser un nombre valido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCadEsDescripcionValida ( p_cadVacia ) != 1 )
		{
			printf( "Error caso 9: la cadena vacia deberia ser una descripcion valida\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la cadena vacia\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SCadDestruir ( &p_cadVacia );

	/* Ninguna validacion acepta un puntero nulo. */
	if ( ( SCadEsCodigoValido ( NULL ) != 0 ) ||
		 ( SCadEsNombreValido ( NULL ) != 0 ) ||
		 ( SCadEsDescripcionValida ( NULL ) != 0 ) )
	{
		printf( "Error caso 10: un puntero nulo no deberia superar ninguna validacion\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}



int TestValidacionCadenas ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test ValidacionCadenas]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestCadEsCodigoValido01 () == BOOL_VAL_CIERTO ) &&
			( TestCadEsNombreValido01 () == BOOL_VAL_CIERTO ) &&
			( TestCadEsDescripcionValida01 () == BOOL_VAL_CIERTO ) &&
			( TestSCadValidaciones01 () == BOOL_VAL_CIERTO ) )
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
