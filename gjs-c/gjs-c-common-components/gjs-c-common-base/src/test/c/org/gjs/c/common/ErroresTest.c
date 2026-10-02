#include "Base.h"

#include "Errores.h"
#include "BaseErrores.h"



static int TestErrEstablecer01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test ErrEstablecer 01:\n" );
	ErrLimpiar ();
	/* Sin error, no debe haberlo. */
	if ( ErrHayError () != 0 )
	{
		printf( "Error caso 1: no deberia haber error tras limpiar\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ErrCodigo () != ERR_OK )
	{
		printf( "Error caso 2: se esperaba ERR_OK: %d\n", ErrCodigo () );
		iRes = BOOL_VAL_FALSO;
	}

	/* Se establece un error predefinido. */
	ERROR_ESTABLECER ( ERR_PARAMETROS );
	if ( ErrHayError () != 1 )
	{
		printf( "Error caso 3: se esperaba que hubiese error\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ErrCodigo () != ERR_PARAMETROS )
	{
		printf( "Error caso 4: se esperaba ERR_PARAMETROS: %d\n", ErrCodigo () );
		iRes = BOOL_VAL_FALSO;
	}
	/* Para un error predefinido debe haber descripcion y modulo. */
	if ( ES_NULO ( ErrDescripcion () ) )
	{
		printf( "Error caso 5: se esperaba una descripcion\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_NULO ( ErrModulo () ) )
	{
		printf( "Error caso 6: se esperaba un modulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ErrLinea () == 0 )
	{
		printf( "Error caso 7: se esperaba un numero de linea\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestErrLimpiar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test ErrLimpiar 01:\n" );
	ERROR_ESTABLECER ( ERR_MEMORIA_INSUFICIENTE );
	ErrLimpiar ();
	if ( ErrHayError () != 0 )
	{
		printf( "Error caso 1: no deberia haber error tras limpiar\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ErrCodigo () != ERR_OK )
	{
		printf( "Error caso 2: se esperaba ERR_OK: %d\n", ErrCodigo () );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ErrLinea () != 0 )
	{
		printf( "Error caso 3: se esperaba linea 0: %u\n", ErrLinea () );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestErrEstablecerConFormato01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test ErrEstablecerConFormato 01:\n" );
	ErrLimpiar ();
	/* Un codigo no predefinido con descripcion formateada. */
	ErrEstablecerConFormato ( __FILE__, __LINE__, ERR_IMPOSIBLE_ABRIR_FICHERO,
			"No se pudo abrir el fichero numero %d", 7 );
	if ( ErrCodigo () != ERR_IMPOSIBLE_ABRIR_FICHERO )
	{
		printf( "Error caso 1: se esperaba ERR_IMPOSIBLE_ABRIR_FICHERO: %d\n", ErrCodigo () );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_NULO ( ErrDescripcion () ) )
	{
		printf( "Error caso 2: se esperaba una descripcion formateada\n" );
		iRes = BOOL_VAL_FALSO;
	}
	ErrLimpiar ();
	return ( iRes );
}

static int TestErrMensaje01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test ErrMensaje 01:\n" );
	ErrLimpiar ();
	/* Sin error, ErrMensaje devuelve nulo. */
	const char * p_cMsj = ErrMensaje ();
	if ( ES_VALIDO ( p_cMsj ) )
	{
		printf( "Error caso 1: se esperaba nulo cuando no hay error\n" );
		iRes = BOOL_VAL_FALSO;
	}
	MemLiberar ( (void **) &p_cMsj );

	/* Con un error establecido devuelve una cadena. */
	ERROR_ESTABLECER ( ERR_PARAMETROS );
	p_cMsj = ErrMensaje ();
	if ( ES_NULO ( p_cMsj ) || ( CadLongitud ( p_cMsj ) == 0 ) )
	{
		printf( "Error caso 2: se esperaba un mensaje de error\n" );
		iRes = BOOL_VAL_FALSO;
	}
	MemLiberar ( (void **) &p_cMsj );

	/* Liberar el mensaje no debe afectar al error global. */
	if ( ErrCodigo () != ERR_PARAMETROS )
	{
		printf( "Error caso 3: el codigo no deberia cambiar: %d\n", ErrCodigo () );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_NULO ( ErrDescripcion () ) )
	{
		printf( "Error caso 4: la descripcion global no deberia perderse\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* Una segunda llamada sigue funcionando (sin doble liberacion). */
	p_cMsj = ErrMensaje ();
	if ( ES_NULO ( p_cMsj ) )
	{
		printf( "Error caso 5: se esperaba de nuevo un mensaje\n" );
		iRes = BOOL_VAL_FALSO;
	}
	MemLiberar ( (void **) &p_cMsj );

	/* ErrLimpiar tras usar ErrMensaje no debe provocar problemas. */
	ErrLimpiar ();
	if ( ErrHayError () != 0 )
	{
		printf( "Error caso 6: no deberia haber error tras limpiar\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestErrImprimir01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test ErrImprimir 01:\n" );
	ErrLimpiar ();
	ERROR_ESTABLECER ( ERR_MEMORIA_INVALIDA );
	/* Se comprueba que imprime y que el estado sigue coherente despues. */
	ErrImprimir ();
	if ( ErrCodigo () != ERR_MEMORIA_INVALIDA )
	{
		printf( "Error caso 1: el codigo no deberia cambiar tras imprimir: %d\n", ErrCodigo () );
		iRes = BOOL_VAL_FALSO;
	}
	ErrLimpiar ();
	if ( ErrHayError () != 0 )
	{
		printf( "Error caso 2: no deberia haber error tras limpiar\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}



/* Los codigos estan declarados en BaseErrores.h, pero eso no basta: hasta que
   no aparecen en _ErrPredefinido y _ErrDescripcion, ErrDescripcion devuelve
   NULL y ErrImprimir no dice nada util. Son dos funciones distintas y es facil
   dar de alta el codigo en una y olvidarse de la otra.

   Aqui va la lista COMPLETA de los que deben tener descripcion. Al anadir un
   codigo predefinido hay que anadirlo tambien aqui; si se olvida el alta, este
   caso se pone rojo. */
static int TestErrCodigosDadosDeAlta01 ()
{
	int		iRes = BOOL_VAL_CIERTO;
	int		iCodigos [] = { ERR_OK,
							ERR_MEMORIA_INVALIDA,
							ERR_MEMORIA_INSUFICIENTE,
							ERR_MEMORIA_PROCESO,
							ERR_PARAMETROS,
							ERR_POSICION_INVALIDA,
							ERR_ESTRUCTURA_INVALIDA,
							ERR_CONVERSION_IMPOSIBLE,
							ERR_GENERAL_OPERATIVO };
	int		iNumCodigos = (int) ( sizeof ( iCodigos ) / sizeof ( iCodigos [ 0 ] ) );
	int		iIdx;

	printf ( "Test ErrCodigosDadosDeAlta 01:\n" );

	for ( iIdx = 0; iIdx < iNumCodigos; iIdx = iIdx + 1 )
	{
		ErrLimpiar ();
		ErrEstablecer ( __FILE__, __LINE__, iCodigos [ iIdx ] );
		if ( ErrCodigo () != iCodigos [ iIdx ] )
		{
			printf( "Error caso 1: se esperaba el codigo %d: %d\n",
					iCodigos [ iIdx ], ErrCodigo () );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_NULO ( ErrDescripcion () ) )
		{
			printf( "Error caso 2: el codigo %d no tiene descripcion\n", iCodigos [ iIdx ] );
			iRes = BOOL_VAL_FALSO;
		}
		else if ( CadLongitud ( ErrDescripcion () ) == 0 )
		{
			printf( "Error caso 3: el codigo %d tiene la descripcion vacia\n", iCodigos [ iIdx ] );
			iRes = BOOL_VAL_FALSO;
		}
	}
	ErrLimpiar ();
	return ( iRes );
}

int TestErrores ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test Errores]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestErrEstablecer01 () == BOOL_VAL_CIERTO ) &&
			( TestErrLimpiar01 () == BOOL_VAL_CIERTO ) &&
			( TestErrEstablecerConFormato01 () == BOOL_VAL_CIERTO ) &&
			( TestErrMensaje01 () == BOOL_VAL_CIERTO ) &&
			( TestErrImprimir01 () == BOOL_VAL_CIERTO ) &&
			( TestErrCodigosDadosDeAlta01 () == BOOL_VAL_CIERTO ) )
	{
		printf ( "%sResultado: OK%s\n", ANSI_VERDE, ANSI_RESETEAR );
	}
	else
	{
		printf ( "%sResultado: KO%s\n", ANSI_ROJO, ANSI_RESETEAR );
		iRes = BOOL_VAL_FALSO;
	}
	ErrLimpiar ();
	printf ( "%s[Fin]%s\n", ANSI_AMARILLO, ANSI_RESETEAR );
	return ( iRes );
}
