#include "Base.h"


#include "SistemaTiposErrores.h"
#include "SistemaErrores.h"

#if ( ! defined ( WIN ) )
#	include <errno.h>
#	include <pthread.h>
#endif



static int TestSisErrLimpiar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SisErrLimpiar 01:\n" );
	SisErrLimpiar ();
	if ( SisHaHabidoError () != 0 )
	{
		printf( "Error caso 1: tras limpiar no debe haber error\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SisHayError ( 0 ) != 0 )
	{
		printf( "Error caso 2: SisHayError(0) debe ser 0 tras limpiar\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SisErrCodigo () != 0 )
	{
		printf( "Error caso 3: el codigo de error debe ser 0 tras limpiar: %d\n", SisErrCodigo () );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SisErrTipo () != SIS_TIP_ERR_NINGUNO )
	{
		printf( "Error caso 4: el tipo de error debe ser NINGUNO tras limpiar\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_NULO ( SisErrDescripcion () ) )
	{
		printf( "Error caso 5: se esperaba descripcion no nula\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSisErrMensaje01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SisErrMensaje 01:\n" );
	SisErrLimpiar ();
	char * p_cMsj = SisErrMensaje ( 1 );
	if ( ES_NULO ( p_cMsj ) )
	{
		printf( "Error caso 1: se esperaba mensaje no nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	MemLiberar ( (void **) &p_cMsj );
	if ( SisMaxError () <= 0 )
	{
		printf( "Error caso 2: se esperaba SisMaxError > 0: %d\n", SisMaxError () );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}


/* Anota el error 2 ( ENOENT en POSIX, ERROR_FILE_NOT_FOUND en Windows ) como lo
   haria una llamada al sistema que falla. */
static void _AnotarError2 ()
{
#if ( defined ( WIN ) )
	SetLastError ( 2 );
#else
	errno = ENOENT;
#endif
	SisHayError ( 1 );
}

/* SisErrTipo () no puede cambiar el codigo del error que clasifica. Antes llamaba
   a SisMaxError (), que sondeaba usando la variable del ultimo error y la dejaba
   en el maximo mas uno. */
static int TestSisErrCodigo01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SisErrCodigo 01:\n" );
	_AnotarError2 ();
	if ( SisErrCodigo () != 2 )
	{
		printf( "Error caso 1: se esperaba el codigo 2 y es %d\n", SisErrCodigo () );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SisErrTipo () != SIS_TIP_ERR_SISTEMA )
	{
		printf( "Error caso 2: se esperaba un error de tipo SISTEMA\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SisErrCodigo () != 2 )
	{
		printf( "Error caso 3: SisErrTipo cambio el codigo: ahora es %d\n", SisErrCodigo () );
		iRes = BOOL_VAL_FALSO;
	}
	const char * p_cDesc = SisErrDescripcion ();
	if ( ( ES_NULO ( p_cDesc ) ) || ( CadLongitud ( p_cDesc ) == 0 ) )
	{
		printf( "Error caso 4: se esperaba la descripcion del error 2\n" );
		iRes = BOOL_VAL_FALSO;
	}
#if ( ! defined ( WIN ) )
	/* En POSIX el texto es el de strerror, en ingles en Cygwin y en Linux. */
	else if ( strcmp ( p_cDesc, "No such file or directory" ) != 0 )
	{
		printf( "Error caso 5: descripcion inesperada: [%s]\n", p_cDesc );
		iRes = BOOL_VAL_FALSO;
	}
#endif
	SisErrLimpiar ();
	return ( iRes );
}

#if ( ! defined ( WIN ) )
static void * _HiloLeeError ( void * p_vCodigo )
{
	*(int *) p_vCodigo = SisErrCodigo ();
	return ( NULL );
}

/* El ultimo error es de cada hilo, como errno: otro hilo no ve el que se
   acaba de anotar aqui. */
static int TestSisErrHilos01 ()
{
	int			iRes = BOOL_VAL_CIERTO;
	pthread_t	hilo;
	int			iCodigoOtroHilo = -1;

	printf( "Test SisErrHilos 01:\n" );
	_AnotarError2 ();
	if ( pthread_create ( &hilo, NULL, _HiloLeeError, &iCodigoOtroHilo ) != 0 )
	{
		printf( "Error caso 1: no se pudo crear el hilo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		pthread_join ( hilo, NULL );
		if ( iCodigoOtroHilo != 0 )
		{
			printf( "Error caso 2: otro hilo vio el error %d de este\n", iCodigoOtroHilo );
			iRes = BOOL_VAL_FALSO;
		}
	}
	if ( SisErrCodigo () != 2 )
	{
		printf( "Error caso 3: este hilo perdio su error: %d\n", SisErrCodigo () );
		iRes = BOOL_VAL_FALSO;
	}
	SisErrLimpiar ();
	return ( iRes );
}
#endif


int TestSistemaErrores ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SistemaErrores]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	int iHilos = BOOL_VAL_CIERTO;
#if ( ! defined ( WIN ) )
	iHilos = TestSisErrHilos01 ();
#endif
	if ( ( TestSisErrLimpiar01 () == BOOL_VAL_CIERTO ) &&
			( TestSisErrMensaje01 () == BOOL_VAL_CIERTO ) &&
			( TestSisErrCodigo01 () == BOOL_VAL_CIERTO ) &&
			( iHilos == BOOL_VAL_CIERTO ) )
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
