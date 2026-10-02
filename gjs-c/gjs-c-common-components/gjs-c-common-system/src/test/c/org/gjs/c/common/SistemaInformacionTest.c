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



static int TestSisOrdenBytes01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	int iOrden;
	printf( "Test SisOrdenBytes 01:\n" );
	iOrden = SisOrdenBytes ();
	if ( ( iOrden != 0 ) && ( iOrden != 1 ) )
	{
		printf( "Error caso 1: orden de bytes no reconocido: %d\n", iOrden );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SisOrdenBytesEsNormal () == SisOrdenBytesEsInvertido () )
	{
		printf( "Error caso 2: el orden no puede ser normal e invertido a la vez\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSisArquitectura01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	int iPalabra;
	printf( "Test SisArquitectura 01:\n" );
	iPalabra = SisTamPalabraMemoria ();
	if ( ( iPalabra != 4 ) && ( iPalabra != 8 ) )
	{
		printf( "Error caso 1: tam de palabra inesperado: %d\n", iPalabra );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SisEsArquitectura64Bits () == SisEsArquitectura32Bits () )
	{
		printf( "Error caso 2: no puede ser de 32 y de 64 bits a la vez\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SisEsArquitectura64Bits () != ( iPalabra == 8 ) )
	{
		printf( "Error caso 3: EsArquitectura64Bits incoherente con el tam de palabra\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SisAdmiteSubprocesos () != 1 )
	{
		printf( "Error caso 4: se esperaba admision de subprocesos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSisNombres01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	const char * p_cSistema;
	const char * p_cVersion;
	char * p_cDir;
	printf( "Test SisNombres 01:\n" );
	p_cSistema = SisSistema ();
	if ( ES_NULO ( p_cSistema ) || ( p_cSistema [ 0 ] == 0 ) )
	{
		printf( "Error caso 1: se esperaba un nombre de sistema no vacio\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* SisVersion devuelve NULL en Windows nativo a proposito, asi que aqui solo se
	   comprueba que, si contesta, no conteste con la cadena vacia. */
	p_cVersion = SisVersion ();
	if ( ES_VALIDO ( p_cVersion ) && ( p_cVersion [ 0 ] == 0 ) )
	{
		printf( "Error caso 2: la version no puede ser la cadena vacia\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* SisDirectorioSistema solo existe en WIN: se apoya en GetWindowsDirectory,
	   y asi esta declarada e implementada. */
#if ( defined ( WIN ) )
	p_cDir = (char *) SisDirectorioSistema ();
	if ( ES_NULO ( p_cDir ) )
	{
		printf( "Error caso 3: se esperaba directorio del sistema no nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	MemLiberar ( (void **) &p_cDir );
#else
	(void) p_cDir;
#endif
	return ( iRes );
}

/* Comprobaciones de RANGO, no de valor: lo que devuelven estas depende de la
   maquina y de los limites del usuario. Lo que se verifica es que contesten algo
   plausible, en vez del 0 que devolvian cuando las guardas estaban invertidas. */
static int TestSisLimites01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	double dVelocidad;
	printf( "Test SisLimites 01:\n" );
	dVelocidad = SisVelocidadCPU ();
	if ( ( dVelocidad < 100.0 ) || ( dVelocidad > 100000.0 ) )
	{
		printf( "Error caso 1: velocidad fuera de rango: %f MHz\n", dVelocidad );
		iRes = BOOL_VAL_FALSO;
	}
#if ( defined ( POSIX ) )
	long lTotales;
	long lUtilizados;
	long lDisponibles;

	lTotales = SisDescriptoresESTotalesProceso ();
	if ( lTotales <= 0 )
	{
		printf( "Error caso 2: se esperaban descriptores totales > 0: %ld\n", lTotales );
		iRes = BOOL_VAL_FALSO;
	}
	lUtilizados = SisDescriptoresESUtilizadosProceso ();
	if ( ( lUtilizados < 0 ) || ( lUtilizados > lTotales ) )
	{
		printf( "Error caso 3: descriptores usados fuera de rango: %ld\n", lUtilizados );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SisMaxNumProcesosPorUsuario () <= 0 )
	{
		printf( "Error caso 4: se esperaba un maximo de procesos > 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	lDisponibles = SisDescriptoresESDisponiblesProceso ();
	if ( lDisponibles != ( lTotales - lUtilizados ) )
	{
		printf( "Error caso 5: disponibles no cuadra con totales menos usados\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SisMaxTamFicheroProceso () == 0 )
	{
		printf( "Error caso 6: se esperaba un maximo de tam de fichero distinto de 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* Los limites tienen tres respuestas: un valor, LONG_MAX ( sin limite ) y
	   -1 ( no se sabe ). El -1 NO vale aqui: getrlimit no falla en un sistema
	   sano, y hasta el 2026-09-19 estas dos lo devolvian en el caso normal,
	   porque el RLIM_INFINITY de getrlimit se convertia en -1 al pasarlo a
	   long. Este caso es el que impide que vuelva a pasar. */
	if ( SisMaxTamFicheroProceso () == -1 )
	{
		printf( "Error caso 7: SisMaxTamFicheroProceso dice que no lo sabe\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SisMaxTiempoCPUProceso () == -1 )
	{
		printf( "Error caso 8: SisMaxTiempoCPUProceso dice que no lo sabe\n" );
		iRes = BOOL_VAL_FALSO;
	}
#endif
	return ( iRes );
}


int TestSistemaInformacion ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SistemaInformacion]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSisTipo01 () == BOOL_VAL_CIERTO ) &&
			( TestSisMemoriaInfo01 () == BOOL_VAL_CIERTO ) &&
			( TestSisOrdenBytes01 () == BOOL_VAL_CIERTO ) &&
			( TestSisArquitectura01 () == BOOL_VAL_CIERTO ) &&
			( TestSisNombres01 () == BOOL_VAL_CIERTO ) &&
			( TestSisLimites01 () == BOOL_VAL_CIERTO ) )
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
