#include "Base.h"

#include "SistemaInformacion.h"
#include "TiposSistema.h"



static int TestSisTipo01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SisTipo 01:\n" );
	if ( TipSisEsValido ( SisTipo () ) != 1 )
	{
		printf( "Error caso 1: SisTipo debe devolver un tipo valido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* Exactamente uno de los cuatro predicados de tipo debe ser cierto. */
	int iSuma = SisEsWindows () + SisEsPosix () + SisEsDos () + SisEsMackintosh ();
	if ( iSuma != 1 )
	{
		printf( "Error caso 2: se esperaba exactamente un tipo de sistema: %d\n", iSuma );
		iRes = BOOL_VAL_FALSO;
	}
#if ( defined ( WIN ) )
	if ( SisTipo () != TIP_SIS_WINDOWS )
	{
		printf( "Error caso 3: en WIN se esperaba tipo WINDOWS\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SisIntegraGUI () != 1 )
	{
		printf( "Error caso 4: en WIN se esperaba integracion GUI\n" );
		iRes = BOOL_VAL_FALSO;
	}
#endif
	return ( iRes );
}

static int TestSisMemoriaInfo01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SisMemoriaInfo 01:\n" );
	if ( SisTamPagina () == 0 )
	{
		printf( "Error caso 1: se esperaba tam de pagina > 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SisMemTamBloqueMinimo () == 0 )
	{
		printf( "Error caso 2: se esperaba tam de bloque minimo > 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
#if ( defined ( WIN ) )
	if ( SisNumProcesadores () < 1 )
	{
		printf( "Error caso 3: se esperaba al menos un procesador\n" );
		iRes = BOOL_VAL_FALSO;
	}
	char * p_cDir = (char *) SisDirectorioTemporal ();
	if ( ES_NULO ( p_cDir ) )
	{
		printf( "Error caso 4: se esperaba directorio temporal no nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	MemLiberar ( (void **) &p_cDir );
#endif
	return ( iRes );
}



int TestSistemaInformacion ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SistemaInformacion]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSisTipo01 () == BOOL_VAL_CIERTO ) &&
			( TestSisMemoriaInfo01 () == BOOL_VAL_CIERTO ) )
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
