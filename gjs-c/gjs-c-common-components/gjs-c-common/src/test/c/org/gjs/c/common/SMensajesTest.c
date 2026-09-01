#include "Base.h"

#include "SMensajes.h"



static int TestSMsjsCicloVida01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SMsjCicloVida 01:\n" );
	SMensajes * p_msjObj = SMsjsCrear ();
	if ( ES_NULO ( p_msjObj ) )
	{
		printf( "Error caso 0: no se pudo crear el objeto de mensajes\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SMsjsNumMensajes ( p_msjObj ) != 0 )
		{
			printf( "Error caso 1: un objeto recien creado no debe tener mensajes\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SMsjsInsertarLit ( p_msjObj, 100, "MensajeCien" ) != 1 )
		{
			printf( "Error caso 2: no se pudo insertar el mensaje 100\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SMsjsNumMensajes ( p_msjObj ) != 1 )
		{
			printf( "Error caso 3: se esperaba 1 mensaje\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SMsjsExisteCodigo ( p_msjObj, 100 ) != 1 )
		{
			printf( "Error caso 4: el codigo 100 deberia existir\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SMsjsExisteCodigo ( p_msjObj, 999 ) != 0 )
		{
			printf( "Error caso 5: el codigo 999 no deberia existir\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SCadena * p_cadTexto = SMsjsTexto ( p_msjObj, 100 );
		if ( ES_NULO ( p_cadTexto ) || ( strcmp ( SCadValorConstante ( p_cadTexto ), "MensajeCien" ) != 0 ) )
		{
			printf( "Error caso 6: se esperaba el texto \"MensajeCien\": [%s]\n", SCadValorConstante ( p_cadTexto ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( SMsjsTexto ( p_msjObj, 999 ) ) )
		{
			printf( "Error caso 7: se esperaba texto nulo para un codigo inexistente\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* No se admiten codigos duplicados. */
		if ( SMsjsInsertarLit ( p_msjObj, 100, "Otro" ) != 0 )
		{
			printf( "Error caso 8: no se debe admitir un codigo duplicado\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* El codigo 0 no es valido. */
		if ( SMsjsInsertarLit ( p_msjObj, 0, "Cero" ) != 0 )
		{
			printf( "Error caso 9: no se debe admitir el codigo 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Segundo mensaje y limpieza. */
		SMsjsInsertarLit ( p_msjObj, 200, "MensajeDoscientos" );
		if ( SMsjsNumMensajes ( p_msjObj ) != 2 )
		{
			printf( "Error caso 10: se esperaban 2 mensajes\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SMsjsLimpiar ( p_msjObj );
		if ( SMsjsNumMensajes ( p_msjObj ) != 0 )
		{
			printf( "Error caso 11: tras limpiar no debe haber mensajes\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	SMsjsDestruir ( &p_msjObj );
	return ( iRes );
}

static int TestSMsjsNulo01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SMsjsNulo 01:\n" );
	if ( SMsjsNumMensajes ( NULL ) != 0 )
	{
		printf( "Error caso 1: se esperaban 0 mensajes con objeto nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SMsjsExisteCodigo ( NULL, 1 ) != 0 )
	{
		printf( "Error caso 2: se esperaba 0 al comprobar codigo en objeto nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( SMsjsTexto ( NULL, 1 ) ) )
	{
		printf( "Error caso 3: se esperaba texto nulo en objeto nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SMsjsInsertarLit ( NULL, 1, "x" ) != 0 )
	{
		printf( "Error caso 4: se esperaba 0 al insertar en objeto nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}



int TestSMensajes ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SMensajes]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSMsjsCicloVida01 () == BOOL_VAL_CIERTO ) &&
			( TestSMsjsNulo01 () == BOOL_VAL_CIERTO ) )
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
