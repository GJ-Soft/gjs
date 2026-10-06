#include "Base.h"

#include "SGestorSignals.h"



/* El gestor de signals solo esta disponible en POSIX; bajo WIN la cabecera no
   expone ni el tipo ni las rutinas, asi que el test es un exito trivial. */

#if ( defined ( POSIX ) )

static int TestSGesSigCicloVida01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SGesSigCicloVida 01:\n" );
	SGestorSignals * p_gesigObj = SGesSigCrear ( NULL );
	if ( ES_NULO ( p_gesigObj ) )
	{
		printf( "Error caso 0: no se pudo crear el gestor de signals\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( ES_VALIDO ( SGesSigRutinaExterna ( p_gesigObj ) ) )
		{
			printf( "Error caso 1: no deberia haber rutina externa inicial\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Se asigna la rutina de atencion como activa para un signal programable;
		   basta con NULL para comprobar la gestion del estado activado. */
		SGesSigAsignarRutinaAtencion ( p_gesigObj, SIS_SIG_USUARIO_1, NULL, 1 );
		if ( SGesSigEstaSignalActivado ( p_gesigObj, SIS_SIG_USUARIO_1 ) != 1 )
		{
			printf( "Error caso 2: el signal deberia constar activado\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SGesSigDesactivarSignal ( p_gesigObj, SIS_SIG_USUARIO_1 );
		if ( SGesSigEstaSignalActivado ( p_gesigObj, SIS_SIG_USUARIO_1 ) != 0 )
		{
			printf( "Error caso 3: el signal deberia constar desactivado\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	/* Regresion: con un indice fuera de rango se leia la tabla de rutinas por
	   defecto fuera de sus limites. Ahora no hace nada. */
	SGesSigProcesar ( p_gesigObj, -1 );
	SGesSigProcesar ( p_gesigObj, SIS_NUM_SIGNALS );
	SGesSigDestruir ( &p_gesigObj );
	return ( iRes );
}

static int TestSGesSigNulo01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SGesSigNulo 01:\n" );
	if ( SGesSigEsValido ( NULL ) != 0 )
	{
		printf( "Error caso 1: un gestor nulo no debe ser valido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( SGesSigRutinaExterna ( NULL ) ) )
	{
		printf( "Error caso 2: se esperaba rutina externa nula para gestor nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SGesSigEstaSignalActivado ( NULL, SIS_SIG_USUARIO_1 ) != 0 )
	{
		printf( "Error caso 3: un gestor nulo no debe tener signals activados\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

#endif



int TestSGestorSignals ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SGestorSignals]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
#if ( defined ( POSIX ) )
	if ( ( TestSGesSigCicloVida01 () == BOOL_VAL_CIERTO ) &&
			( TestSGesSigNulo01 () == BOOL_VAL_CIERTO ) )
	{
		printf ( "%sResultado: OK%s\n", ANSI_VERDE, ANSI_RESETEAR );
	}
	else
	{
		printf ( "%sResultado: KO%s\n", ANSI_ROJO, ANSI_RESETEAR );
		iRes = BOOL_VAL_FALSO;
	}
#else
	printf ( "SGestorSignals solo disponible en POSIX: no aplica en esta plataforma.\n" );
	printf ( "%sResultado: OK%s\n", ANSI_VERDE, ANSI_RESETEAR );
#endif
	printf ( "%s[Fin]%s\n", ANSI_AMARILLO, ANSI_RESETEAR );
	return ( iRes );
}
