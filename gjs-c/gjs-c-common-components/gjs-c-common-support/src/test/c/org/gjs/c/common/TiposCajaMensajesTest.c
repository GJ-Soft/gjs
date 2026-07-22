#include "Base.h"

#include "TiposCajaMensajes.h"



static int TestTipCajMsjEsValido01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test TipCajMsjEsValido 01:\n" );
	if ( TipCajMsjEsValido ( TIP_CAJ_MSJ_INFORMACION ) != 1 )
	{
		printf( "Error caso 1: se esperaba valido para INFORMACION\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( TipCajMsjEsValido ( TIP_CAJ_MSJ_PREGUNTA_SINOCAN ) != 1 )
	{
		printf( "Error caso 2: se esperaba valido para PREGUNTA_SINOCAN\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( TipCajMsjEsValido ( TIP_CAJ_MSJ_ERROR_ABRREINIGN ) != 1 )
	{
		printf( "Error caso 3: se esperaba valido para ERROR_ABRREINIGN\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( TipCajMsjEsValido ( -1 ) != 0 )
	{
		printf( "Error caso 4: no se esperaba valido para -1\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( TipCajMsjEsValido ( 13 ) != 0 )
	{
		printf( "Error caso 5: no se esperaba valido para 13 (fuera de rango)\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( TipCajMsjEsValido ( 99 ) != 0 )
	{
		printf( "Error caso 6: no se esperaba valido para 99\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}



int TestTiposCajaMensajes ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test TiposCajaMensajes]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestTipCajMsjEsValido01 () == BOOL_VAL_CIERTO ) )
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
