#include "Base.h"

#include "NivelesLog.h"



static int TestNivelLogEsValido01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test NivelLogEsValido 01:\n" );
	/* Valido = [LOG_NIVEL_MIN (INFORMACION=1) .. LOG_NIVEL_MAX (FORZADO=100)]. */
	if ( NivelLogEsValido ( LOG_NIVEL_INFORMACION ) != 1 )
	{
		printf( "Error caso 1: se esperaba valido para INFORMACION\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( NivelLogEsValido ( LOG_NIVEL_ERROR ) != 1 )
	{
		printf( "Error caso 2: se esperaba valido para ERROR\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( NivelLogEsValido ( LOG_NIVEL_FORZADO ) != 1 )
	{
		printf( "Error caso 3: se esperaba valido para FORZADO\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* DEPURACION (0) queda por debajo del minimo -> no valido. */
	if ( NivelLogEsValido ( LOG_NIVEL_DEPURACION ) != 0 )
	{
		printf( "Error caso 4: no se esperaba valido para DEPURACION\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( NivelLogEsValido ( LOG_NIVEL_NINGUNO ) != 0 )
	{
		printf( "Error caso 5: no se esperaba valido para NINGUNO\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( NivelLogEsValido ( 101 ) != 0 )
	{
		printf( "Error caso 6: no se esperaba valido para 101\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestNivelLogEsEstablecible01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test NivelLogEsEstablecible 01:\n" );
	/* Establecible = NINGUNO o [MIN..MAX]. */
	if ( NivelLogEsEstablecible ( LOG_NIVEL_NINGUNO ) != 1 )
	{
		printf( "Error caso 1: se esperaba establecible para NINGUNO\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( NivelLogEsEstablecible ( LOG_NIVEL_INFORMACION ) != 1 )
	{
		printf( "Error caso 2: se esperaba establecible para INFORMACION\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( NivelLogEsEstablecible ( LOG_NIVEL_FORZADO ) != 1 )
	{
		printf( "Error caso 3: se esperaba establecible para FORZADO\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( NivelLogEsEstablecible ( LOG_NIVEL_DEPURACION ) != 0 )
	{
		printf( "Error caso 4: no se esperaba establecible para DEPURACION\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( NivelLogEsEstablecible ( -2 ) != 0 )
	{
		printf( "Error caso 5: no se esperaba establecible para -2\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( NivelLogEsEstablecible ( 101 ) != 0 )
	{
		printf( "Error caso 6: no se esperaba establecible para 101\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}



int TestNivelesLog ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test NivelesLog]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestNivelLogEsValido01 () == BOOL_VAL_CIERTO ) &&
			( TestNivelLogEsEstablecible01 () == BOOL_VAL_CIERTO ) )
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
