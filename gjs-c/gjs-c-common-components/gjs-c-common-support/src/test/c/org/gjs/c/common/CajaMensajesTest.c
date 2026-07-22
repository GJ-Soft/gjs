#include "Base.h"

#include "CajaMensajes.h"
#include "SimulacionUsuarioConsola.h"
#include "TestConfig.h"



static int TestCajMsjMostrarDefensivo01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test CajMsjMostrarDefensivo 01:\n" );
	/* Solo se prueban las ramas que NO abren el dialogo modal (WIN) ni esperan
	   una pulsacion por consola (POSIX): mensaje nulo o tipo no valido. */
	if ( CajMsjMostrar ( TIP_CAJ_MSJ_INFORMACION, "Titulo", NULL ) != 0 )
	{
		printf( "Error caso 1: se esperaba 0 con mensaje nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( CajMsjMostrar ( 99, "Titulo", "Mensaje" ) != 0 )
	{
		printf( "Error caso 2: se esperaba 0 con tipo no valido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( CajMsjMostrarConFormato ( 99, "Titulo", "Valor: %d", 7 ) != 0 )
	{
		printf( "Error caso 3: se esperaba 0 con tipo no valido (con formato)\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestCajMsjMostrarPositivo01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test CajMsjMostrarPositivo 01:\n" );
	/* En POSIX, CajMsjMostrar imprime la caja y bloquea con getchar(). Se simula
	   que el usuario pulsa <retorno> para poder probar el camino de exito. En WIN
	   la caja es un dialogo modal (MessageBox), que no se puede simular asi. */
#if ( !defined ( WIN ) )
	if ( SimularEntradaConsola ( "" ) != 1 )
	{
		printf( "Error caso 0: no se pudo preparar la entrada simulada\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( CajMsjMostrar ( TIP_CAJ_MSJ_INFORMACION, "Titulo", "Mensaje de prueba" ) != 1 )
		{
			printf( "Error caso 1: se esperaba 1 al mostrar la caja de informacion\n" );
			iRes = BOOL_VAL_FALSO;
		}
		RestaurarEntradaConsola ();
	}
#endif
	return ( iRes );
}

static int TestCajMsjMostrarError01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test CajMsjMostrarError 01:\n" );
	/* Un tipo de error se dibuja con borde doble; se simula <retorno> igual que en
	   el caso positivo para no bloquear en el getchar() de POSIX. */
#if ( !defined ( WIN ) )
	if ( SimularEntradaConsola ( "" ) != 1 )
	{
		printf( "Error caso 0: no se pudo preparar la entrada simulada\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( CajMsjMostrar ( TIP_CAJ_MSJ_ERROR, "Error", "Algo ha fallado" ) != 1 )
		{
			printf( "Error caso 1: se esperaba 1 al mostrar la caja de error\n" );
			iRes = BOOL_VAL_FALSO;
		}
		RestaurarEntradaConsola ();
	}
#endif
	return ( iRes );
}



int TestCajaMensajes ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test CajaMensajes]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestCajMsjMostrarDefensivo01 () == BOOL_VAL_CIERTO ) &&
			( TestCajMsjMostrarPositivo01 () == BOOL_VAL_CIERTO ) &&
			( TestCajMsjMostrarError01 () == BOOL_VAL_CIERTO ) )
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
