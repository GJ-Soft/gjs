#include "Base.h"

#include "SistemaSignals.h"



static int TestSisSigNombre01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SisSigNombre 01:\n" );
	/* SisSigNombre / SisSigDescripcion no dependen de que los signals esten
	   permitidos: mapean por identificador en cualquier plataforma. */
	if ( ES_NULO ( SisSigNombre ( SIS_SIG_ABORTAR ) ) || ( strcmp ( SisSigNombre ( SIS_SIG_ABORTAR ), SIS_SIG_NOM_ABORTAR ) != 0 ) )
	{
		printf( "Error caso 1: se esperaba \"%s\"\n", SIS_SIG_NOM_ABORTAR );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_NULO ( SisSigNombre ( SIS_SIG_INTERRUPCION ) ) || ( strcmp ( SisSigNombre ( SIS_SIG_INTERRUPCION ), SIS_SIG_NOM_INTERRUPCION ) != 0 ) )
	{
		printf( "Error caso 2: se esperaba \"%s\"\n", SIS_SIG_NOM_INTERRUPCION );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( SisSigNombre ( -1 ) ) )
	{
		printf( "Error caso 3: se esperaba nulo para signal no valido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_NULO ( SisSigDescripcion ( SIS_SIG_ABORTAR ) ) )
	{
		printf( "Error caso 4: se esperaba descripcion no nula\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( SisSigDescripcion ( 999 ) ) )
	{
		printf( "Error caso 5: se esperaba descripcion nula para signal no valido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSisSigMensaje01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SisSigMensaje 01:\n" );
	char * p_cMsj = SisSigMensaje ( SIS_SIG_FINALIZACION );
	if ( ES_NULO ( p_cMsj ) )
	{
		printf( "Error caso 1: se esperaba mensaje no nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	MemLiberar ( (void **) &p_cMsj );
	return ( iRes );
}

static int TestSisSigCodigo01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SisSigCodigo 01:\n" );
	/* El resultado de estas rutinas depende de la plataforma: en WIN los signals
	   no estan permitidos y devuelven -1 / 0; en POSIX si. Se comprueba la
	   coherencia con SisSigEstanPermitidos en tiempo de ejecucion. */
	if ( SisSigEstanPermitidos () == 1 )
	{
		int iCod = SisSigCodigo ( SIS_SIG_ABORTAR );
		if ( iCod < 0 )
		{
			printf( "Error caso 1: se esperaba codigo valido para ABORTAR\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SisSigId ( iCod ) != SIS_SIG_ABORTAR )
		{
			printf( "Error caso 2: SisSigId no invierte SisSigCodigo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SisSigEsValida ( SIS_SIG_ABORTAR ) != 1 )
		{
			printf( "Error caso 3: se esperaba signal valida\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SisSigEsProgramable ( SIS_SIG_FINALIZACION_OBLIGADA ) != 0 )
		{
			printf( "Error caso 4: FINALIZACION_OBLIGADA no debe ser programable\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		if ( SisSigCodigo ( SIS_SIG_ABORTAR ) != -1 )
		{
			printf( "Error caso 1: sin signals permitidos se esperaba -1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SisSigEsValida ( SIS_SIG_ABORTAR ) != 0 )
		{
			printf( "Error caso 2: sin signals permitidos se esperaba no valida\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	return ( iRes );
}



int TestSistemaSignals ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SistemaSignals]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSisSigNombre01 () == BOOL_VAL_CIERTO ) &&
			( TestSisSigMensaje01 () == BOOL_VAL_CIERTO ) &&
			( TestSisSigCodigo01 () == BOOL_VAL_CIERTO ) )
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
