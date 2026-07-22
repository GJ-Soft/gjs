#include "Base.h"

#include "TiempoSistema.h"

#include "Fechas.h"
#include "Horas.h"



static int TestTiempoHoyAhora01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	long lHoy;
	long lAhora;
	printf( "Test TiempoHoyAhora 01:\n" );

	/* la fecha del sistema debe tener formato de fecha valido */
	lHoy = TiempoHoy ();
	if ( FecFormEsValida ( lHoy ) != 1 )
	{
		printf( "Error caso 1: la fecha de hoy no es valida: %ld\n", lHoy );
		iRes = BOOL_VAL_FALSO;
	}
	/* la hora del sistema debe tener formato de hora valido */
	lAhora = TiempoAhora ();
	if ( HorFormEsValida ( lAhora ) != 1 )
	{
		printf( "Error caso 2: la hora de ahora no es valida: %ld\n", lAhora );
		iRes = BOOL_VAL_FALSO;
	}
	/* la fecha-hora combinada debe ser positiva */
	if ( TiempoHoyAhora () <= 0 )
	{
		printf( "Error caso 3: TiempoHoyAhora deberia ser positivo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* esperar 0 segundos no debe fallar */
	TiempoEsperar ( 0 );

	return ( iRes );
}



int TestTiempoSistema ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test TiempoSistema]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestTiempoHoyAhora01 () == BOOL_VAL_CIERTO ) )
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
