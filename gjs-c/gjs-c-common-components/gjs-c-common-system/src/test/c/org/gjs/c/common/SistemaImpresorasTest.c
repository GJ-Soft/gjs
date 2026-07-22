#include "Base.h"

#include "SistemaImpresoras.h"



static int TestSisImpresoras01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SisImpresoras 01:\n" );
	/* Las rutinas de impresoras solo existen bajo WIN. No se lanza ninguna
	   impresion real: SisImprimir con texto nulo devuelve 0 sin mostrar dialogo. */
#if ( defined ( WIN ) )
	if ( SisImpresionPosible () != 1 )
	{
		printf( "Error caso 1: se esperaba que la impresion sea posible\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SisImprimir ( NULL ) != 0 )
	{
		printf( "Error caso 2: se esperaba 0 al imprimir texto nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
#endif
	return ( iRes );
}



int TestSistemaImpresoras ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SistemaImpresoras]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSisImpresoras01 () == BOOL_VAL_CIERTO ) )
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
