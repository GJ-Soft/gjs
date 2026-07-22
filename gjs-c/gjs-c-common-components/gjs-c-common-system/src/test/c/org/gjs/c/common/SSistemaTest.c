#include "Base.h"

#include "SSistema.h"



static int TestSSisCicloVida01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SSisCicloVida 01:\n" );
	SSistema * p_sisObj = SSisCrear ();
	if ( ES_NULO ( p_sisObj ) )
	{
		printf( "Error caso 0: no se pudo crear el sistema\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( TipSisEsValido ( SSisTipo ( p_sisObj ) ) != 1 )
		{
			printf( "Error caso 1: SSisTipo debe devolver un tipo valido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* El orden de bytes detectado debe ser normal (0) o invertido (1). */
		if ( ( SSisOrdenBytes ( p_sisObj ) != 0 ) && ( SSisOrdenBytes ( p_sisObj ) != 1 ) )
		{
			printf( "Error caso 2: orden de bytes no reconocido: %d\n", SSisOrdenBytes ( p_sisObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SSisOrdenBytesEsNormal ( p_sisObj ) == SSisOrdenBytesEsInvertido ( p_sisObj ) )
		{
			printf( "Error caso 3: el orden de bytes no puede ser normal e invertido a la vez\n" );
			iRes = BOOL_VAL_FALSO;
		}
#if ( defined ( WIN ) )
		if ( SSisTipo ( p_sisObj ) != TIP_SIS_WINDOWS )
		{
			printf( "Error caso 4: en WIN se esperaba tipo WINDOWS\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SSisEsWindows ( p_sisObj ) != 1 )
		{
			printf( "Error caso 5: en WIN SSisEsWindows debe ser 1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SSisEsPosix ( p_sisObj ) != 0 )
		{
			printf( "Error caso 6: en WIN SSisEsPosix debe ser 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SSisAdmiteSubprocesos ( p_sisObj ) != 1 )
		{
			printf( "Error caso 7: en WIN se esperaba admision de subprocesos\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_NULO ( SSisDirSistema ( p_sisObj ) ) )
		{
			printf( "Error caso 8: en WIN se esperaba directorio del sistema no nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
#endif
	}
	SSisDestruir ( &p_sisObj );
	return ( iRes );
}

static int TestSSisNulo01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SSisNulo 01:\n" );
	if ( SSisTipo ( NULL ) != 0 )
	{
		printf( "Error caso 1: se esperaba 0 en el tipo de un sistema nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SSisEsWindows ( NULL ) != 0 )
	{
		printf( "Error caso 2: SSisEsWindows con nulo debe ser 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( SSisDirTemporal ( NULL ) ) )
	{
		printf( "Error caso 3: se esperaba nulo en el directorio temporal de un sistema nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}



int TestSSistema ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SSistema]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSSisCicloVida01 () == BOOL_VAL_CIERTO ) &&
			( TestSSisNulo01 () == BOOL_VAL_CIERTO ) )
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
