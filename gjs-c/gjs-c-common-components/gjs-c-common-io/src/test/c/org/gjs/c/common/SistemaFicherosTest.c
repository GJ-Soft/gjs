#include "Base.h"
#include "Texto.h"

#include "SistemaFicheros.h"
#include "TestConfig.h"

/* Para montar el caso de "solo lectura": ponerlo NO es parte de la API, lo
   tiene que hacer el propio test. Ver _PonerSoloLectura. */
#if ( ! defined ( WIN ) )
#	include <sys/stat.h>
#endif



static int TestSisNombreFichero01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SisNombreFichero 01:\n" );
	char * p_cFichero = SisComponerFichero ( "datos", "txt" );
	if ( ES_NULO ( p_cFichero ) || ( CadComparar ( p_cFichero, "datos.txt" ) != COMP_IGUAL ) )
	{
		printf( "Error caso 1: se esperaba \"datos.txt\": [%s]\n", ES_VALIDO ( p_cFichero ) ? p_cFichero : "(nulo)" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( p_cFichero ) )
	{
		if ( SisFicheroTieneExtension ( p_cFichero ) != 1 )
		{
			printf( "Error caso 2: se esperaba que tenga extension\n" );
			iRes = BOOL_VAL_FALSO;
		}
		char * p_cNombre = SisFicheroNombre ( p_cFichero );
		if ( ES_NULO ( p_cNombre ) || ( CadComparar ( p_cNombre, "datos" ) != COMP_IGUAL ) )
		{
			printf( "Error caso 3: se esperaba nombre \"datos\": [%s]\n", ES_VALIDO ( p_cNombre ) ? p_cNombre : "(nulo)" );
			iRes = BOOL_VAL_FALSO;
		}
		MemLiberar ( (void **) &p_cNombre );
	}
	MemLiberar ( (void **) &p_cFichero );

	if ( SisFicheroTieneExtension ( "datos" ) != 0 )
	{
		printf( "Error caso 4: no se esperaba extension en \"datos\"\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSisFichero01 ()
{
	char * 	p_cDirActual;
	char * 	p_cDirectorio;
	char * 	p_cFichero;
	int 	iRes = BOOL_VAL_CIERTO;
	
	printf( "Test SisFichero 01:\n" );
	p_cDirActual = SisDirectorioActual ();
	p_cDirectorio = SisResolverDirectorioRelativo ( p_cDirActual, FIC_TEST_DIR_RESULTS );
	p_cFichero = SisComponerRuta ( p_cDirectorio, "sisfic_test.tmp", 0 );
	printf ( "* ACTUAL: %s\n", p_cDirActual );
	printf ( "* DIRECTORIO: %s\n", p_cDirectorio );
	printf ( "* FICHERO: %s\n", p_cFichero );
//	SisCrearDirectorio ( p_cDirectorio );
	/* Punto de partida limpio. */
	SisEliminarFichero ( p_cFichero );
	if ( SisCrearFichero ( p_cFichero ) != 1 )
	{
		printf( "Error caso 1: no se pudo crear el fichero: %s\n", p_cFichero );
		iRes = BOOL_VAL_FALSO;
	} 
	else
	{
		if ( SisExisteFichero ( p_cFichero ) != 1 )
		{
			printf( "Error caso 2: se esperaba que exista el fichero: %s\n", p_cFichero );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SisEliminarFichero ( p_cFichero ) != 1 )
		{
			printf( "Error caso 3: no se pudo eliminar el fichero: %s\n", p_cFichero );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SisExisteFichero ( p_cFichero ) != 0 )
		{
			printf( "Error caso 4: no se esperaba que exista el fichero tras eliminar\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	MemLiberarCadena ( &p_cFichero );
	MemLiberarCadena ( &p_cDirectorio );
	MemLiberarCadena ( &p_cDirActual );
	return ( iRes );
}

static int TestSisDirectorio01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SisDirectorio 01:\n" );
	/* Punto de partida limpio. */
	SisEliminarDirectorio ( FIC_TEST_DIR_RESULTS "/sisdir_test" );

	if ( SisCrearDirectorio ( FIC_TEST_DIR_RESULTS "/sisdir_test" ) != 1 )
	{
		printf( "Error caso 1: no se pudo crear el directorio\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SisExisteDirectorio ( FIC_TEST_DIR_RESULTS "/sisdir_test" ) != 1 )
	{
		printf( "Error caso 2: se esperaba que exista el directorio\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SisEliminarDirectorio ( FIC_TEST_DIR_RESULTS "/sisdir_test" ) != 1 )
	{
		printf( "Error caso 3: no se pudo eliminar el directorio\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SisExisteDirectorio ( FIC_TEST_DIR_RESULTS "/sisdir_test" ) != 0 )
	{
		printf( "Error caso 4: no se esperaba que exista el directorio tras eliminar\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSisValido01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SisValido 01:\n" );
	if ( SisEsFicheroValido ( "datos.txt" ) != 1 )
	{
		printf( "Error caso 1: se esperaba fichero valido \"datos.txt\"\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* El patron de directorio depende del sistema (unidad en Windows). */
#if defined ( WIN )
	if ( SisEsRutaValida ( "C:\\Temp" ) != 1 )
#else
	if ( SisEsRutaValida ( "/tmp" ) != 1 )
#endif
	{
		printf( "Error caso 2: se esperaba directorio valido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSisNulo01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SisNulo 01:\n" );
	if ( SisExisteFichero ( NULL ) != 0 )
	{
		printf( "Error caso 1: no se esperaba que exista fichero nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SisEsFicheroValido ( NULL ) != 0 )
	{
		printf( "Error caso 2: no se esperaba fichero valido con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SisFicheroTieneExtension ( NULL ) != 0 )
	{
		printf( "Error caso 3: no se esperaba extension con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSisComponerRuta01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	char * p_cRuta;
	printf( "Test SisComponerRuta 01:\n" );

	/* El directorio valido depende del sistema (unidad en Windows). Se acepta
	   cualquier estilo de separador; para comparar se normaliza el resultado a '/'. */
#if defined ( WIN )
	const char * p_cDir     = "C:\\Temp";
	const char * p_cDirNorm = "C:/Temp";
#else
	const char * p_cDir     = "/tmp";
	const char * p_cDirNorm = "/tmp";
#endif

	/* Caso 1: directorio valido + fichero -> se combinan con un separador. */
	p_cRuta = SisComponerRuta ( p_cDir, "f.txt", 0 );
	if ( ES_VALIDO ( p_cRuta ) )
	{
		CadReemplazarCaracter ( p_cRuta, '\\', '/' );
		char * p_cEsperado = CadCrearConFormato ( "%s/%s", p_cDirNorm, "f.txt" );
		if ( CadComparar ( p_cRuta, p_cEsperado ) != COMP_IGUAL )
		{
			printf( "Error caso 1: se esperaba [%s]: [%s]\n", p_cEsperado, p_cRuta );
			iRes = BOOL_VAL_FALSO;
		}
		MemLiberarCadena ( &p_cEsperado );
	}
	else
	{
		printf( "Error caso 1: se esperaba ruta valida\n" );
		iRes = BOOL_VAL_FALSO;
	}
	MemLiberarCadena ( &p_cRuta );

	/* Caso 2: directorio invalido + fichero -> se antepone el directorio actual ".". */
	p_cRuta = SisComponerRuta ( "", "x.txt", 0 );
	if ( ES_VALIDO ( p_cRuta ) )
	{
		CadReemplazarCaracter ( p_cRuta, '\\', '/' );
		if ( CadComparar ( p_cRuta, "./x.txt" ) != COMP_IGUAL )
		{
			printf( "Error caso 2: se esperaba [./x.txt]: [%s]\n", p_cRuta );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 2: se esperaba ruta valida\n" );
		iRes = BOOL_VAL_FALSO;
	}
	MemLiberarCadena ( &p_cRuta );

	/* Caso 3: directorio valido + fichero vacio -> se devuelve solo el directorio. */
	p_cRuta = SisComponerRuta ( p_cDir, "", 0 );
	if ( ES_NULO ( p_cRuta ) || ( CadComparar ( p_cRuta, p_cDir ) != COMP_IGUAL ) )
	{
		printf( "Error caso 3: se esperaba [%s]: [%s]\n", p_cDir, ES_VALIDO ( p_cRuta ) ? p_cRuta : "(nulo)" );
		iRes = BOOL_VAL_FALSO;
	}
	MemLiberarCadena ( &p_cRuta );

	/* Caso 4: ni directorio ni fichero validos, con flag -> directorio actual ".". */
	p_cRuta = SisComponerRuta ( "", "", 1 );
	if ( ES_NULO ( p_cRuta ) || ( CadComparar ( p_cRuta, "." ) != COMP_IGUAL ) )
	{
		printf( "Error caso 4: se esperaba [.] con flag: [%s]\n", ES_VALIDO ( p_cRuta ) ? p_cRuta : "(nulo)" );
		iRes = BOOL_VAL_FALSO;
	}
	MemLiberarCadena ( &p_cRuta );

	/* Caso 5: ni directorio ni fichero validos, sin flag -> NULL. */
	p_cRuta = SisComponerRuta ( "", "", 0 );
	if ( ES_VALIDO ( p_cRuta ) )
	{
		printf( "Error caso 5: se esperaba NULL sin flag: [%s]\n", p_cRuta );
		iRes = BOOL_VAL_FALSO;
	}
	MemLiberarCadena ( &p_cRuta );

	return ( iRes );
}

static int TestSisResolverDirRelativo01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	char * p_cRes;
	printf( "Test SisResolverDirRelativo 01:\n" );

	/* Caso 1: "./../datos" sube un nivel (quita "proyecto") y desciende a "datos". */
	p_cRes = SisResolverDirectorioRelativo ( "/home/gjs/proyecto", "./../datos" );
	if ( ES_VALIDO ( p_cRes ) )
	{
		if ( CadEsIgual ( p_cRes, "/home/gjs/datos" ) != 1 )
		{
			printf( "Error caso 1: se esperaba /home/gjs/datos: [%s]\n", p_cRes );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 1: se esperaba resultado valido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	MemLiberarCadena ( &p_cRes );

	/* Caso 2: "./sub" desciende sin subir. */
	p_cRes = SisResolverDirectorioRelativo ( "/home/gjs/proyecto", "./sub" );
	if ( ES_NULO ( p_cRes ) )
	{
		printf( "Error caso 2: se esperaba resultado valido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( CadEsIgual ( p_cRes, "/home/gjs/proyecto/sub" ) != 1 )
		{
			printf( "Error caso 2: se esperaba /home/gjs/proyecto/sub: [%s]\n", p_cRes );
			iRes = BOOL_VAL_FALSO;
		}
	}
	MemLiberarCadena ( &p_cRes );

	/* Caso 3: "./../../otro" sube dos niveles (quita "proyecto" y "gjs"). */
	p_cRes = SisResolverDirectorioRelativo ( "/home/gjs/proyecto", "./../../otro" );
	if ( ES_NULO ( p_cRes ) )
	{
		printf( "Error caso 3: se esperaba resultado valido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( CadEsIgual ( p_cRes, "/home/otro" ) != 1 ) 
		{
			printf( "Error caso 3: se esperaba /home/otro: [%s]\n", p_cRes );
			iRes = BOOL_VAL_FALSO;
		}
	}
	MemLiberarCadena ( &p_cRes );

	/* Caso 4: base nula -> NULL. */
	if ( ES_VALIDO ( SisResolverDirectorioRelativo ( NULL, "./x" ) ) )
	{
		printf( "Error caso 4: se esperaba NULL con base nula\n" );
		iRes = BOOL_VAL_FALSO;
	}

	/* Caso 5: relativa que no empieza por '.' -> NULL. */
	p_cRes = SisResolverDirectorioRelativo ( "/home/gjs", "sinpunto" );
	if ( ES_VALIDO ( p_cRes ) )
	{
		printf( "Error caso 5: se esperaba NULL con relativa sin '.': [%s]\n", p_cRes );
		iRes = BOOL_VAL_FALSO;
	}
	MemLiberarCadena ( &p_cRes );

	/* Caso 6: Windows. */
	p_cRes = SisResolverDirectorioRelativo ( "C:\\home\\gjs\\proyecto", ".\\..\\datos" );
	if ( ES_VALIDO ( p_cRes ) )
	{
		if ( CadEsIgual ( p_cRes, "C:\\home\\gjs\\datos" ) != 1 ) 
		{
			printf( "Error caso 6: se esperaba C:\\home\\gjs\\datos: [%s]\n", p_cRes );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 6: se esperaba resultado valido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	MemLiberarCadena ( &p_cRes );

	/* Caso 7: DirActual. */
	char * p_cDirActual = SisDirectorioActual ();
	p_cRes = SisResolverDirectorioRelativo ( p_cDirActual, FIC_TEST_DIR_RESULTS );
	if ( ES_VALIDO ( p_cRes ) )
	{
		char * p_cResUnix = SisRutaEstiloUnix ( p_cRes );
		if ( CadAcabaPor ( p_cResUnix, "/target/test-nar/results" ) != 1 ) 
		{
			printf( "Error caso 7: se esperaba .../target/test-nar/results: [%s]\n", p_cResUnix );
			iRes = BOOL_VAL_FALSO;
		}
		MemLiberarCadena ( &p_cResUnix );
	}
	else
	{
		printf( "Error caso 7: se esperaba resultado valido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	MemLiberarCadena ( &p_cRes );
	return ( iRes );
}

/* --- Atributos de fichero ---------------------------------------------------
   Las nueve consultas de atributos tienen la misma forma, asi que se recorren
   con una tabla y el mensaje de error dice siempre que funcion fallo.
   SisRutaDesactivarModoSoloLectura no esta en la tabla porque modifica. */
typedef struct
{
	const char *	p_cNombre;
	int	( * pfnConsulta ) ( const char * );
	int				iEnFicheroNormal;	/* lo que debe dar en un fichero recien creado */
} SIS_ATRIBUTO;

static const SIS_ATRIBUTO g_atributos [] =
{
	{ "SisRutaComprimida",					SisRutaComprimida,					0 },
	{ "SisRutaEncriptada",					SisRutaEncriptada,					0 },
	{ "SisRutaOculta",						SisRutaOculta,						0 },
	{ "SisRutaDelSistema",					SisRutaDelSistema,					0 },
	{ "SisFicheroEsTemporal",				SisFicheroEsTemporal,				0 },
	{ "SisFicheroAsociadoAAplicacion",		SisFicheroAsociadoAAplicacion,		0 },
	{ "SisFicheroConOptimizacionEspacial",	SisFicheroConOptimizacionEspacial,	0 },
	{ "SisRutaDeSoloLectura",				SisRutaDeSoloLectura,				0 },
	{ "SisFicheroEsAccesible",				SisFicheroEsAccesible,				1 }
};

#define SIS_NUM_ATRIBUTOS	( sizeof ( g_atributos ) / sizeof ( g_atributos [ 0 ] ) )


/* Devuelve la ruta de un fichero de trabajo dentro del directorio de resultados. */
static char * _RutaDePrueba ( const char * p_cFichero )
{
	char *	p_cDirActual;
	char *	p_cDirectorio;
	char *	p_cRes;

	p_cDirActual = SisDirectorioActual ();
	p_cDirectorio = SisResolverDirectorioRelativo ( p_cDirActual, FIC_TEST_DIR_RESULTS );
	p_cRes = SisComponerRuta ( p_cDirectorio, p_cFichero, 0 );
	MemLiberarCadena ( &p_cDirectorio );
	MemLiberarCadena ( &p_cDirActual );
	return ( p_cRes );
}

/* Poner un fichero en solo lectura no es parte de la API: es el montaje del
   test. Y hay que hacerlo con las herramientas del modo en que se compila,
   porque en Cygwin un chmod 0444 NO enciende el atributo de NTFS ( medido ), y
   en modo WIN es justo ese atributo el que consulta la funcion. */
static int _PonerSoloLectura ( const char * p_cRuta )
{
	int		iRes;

# if ( defined ( WIN ) )
	DWORD	dwAtributos;

	dwAtributos = GetFileAttributes ( p_cRuta );
	if ( dwAtributos == INVALID_FILE_ATTRIBUTES )
	{
		iRes = 0;
	}
	else
	{
		if ( SetFileAttributes ( p_cRuta, dwAtributos | FILE_ATTRIBUTE_READONLY ) != 0 )
		{
			iRes = 1;
		}
		else
		{
			iRes = 0;
		}
	}
# else
	if ( chmod ( p_cRuta, 0444 ) == 0 )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
# endif
	return ( iRes );
}

# if ( defined ( WIN ) )
/* Solo hace falta en modo WIN: en POSIX "oculto" se consigue con el nombre. */
static int _PonerOculto ( const char * p_cRuta )
{
	int		iRes;
	DWORD	dwAtributos;

	dwAtributos = GetFileAttributes ( p_cRuta );
	if ( dwAtributos == INVALID_FILE_ATTRIBUTES )
	{
		iRes = 0;
	}
	else
	{
		if ( SetFileAttributes ( p_cRuta, dwAtributos | FILE_ATTRIBUTE_HIDDEN ) != 0 )
		{
			iRes = 1;
		}
		else
		{
			iRes = 0;
		}
	}
	return ( iRes );
}
# endif

/* Recorre la tabla comprobando que ninguna consulta dice que si. */
static int _AtributosTodosFalsos ( const char * p_cRuta, const char * p_cQue )
{
	int			iRes = BOOL_VAL_CIERTO;
	unsigned	uIdx;

	for ( uIdx = 0; uIdx < SIS_NUM_ATRIBUTOS; uIdx++ )
	{
		if ( g_atributos [ uIdx ].pfnConsulta ( p_cRuta ) != 0 )
		{
			printf ( "Error: %s ( %s ) dijo que si, se esperaba que no\n",
					 g_atributos [ uIdx ].p_cNombre, p_cQue );
			iRes = BOOL_VAL_FALSO;
		}
	}
	return ( iRes );
}


/* Una ruta que no existe y una ruta nula: ninguna consulta debe decir que si,
   y ninguna debe reventar. */
static int TestSisAtributos01 ()
{
	char *	p_cFichero;
	int		iRes = BOOL_VAL_CIERTO;

	printf ( "Test SisAtributos 01 ( ruta inexistente y ruta nula ):\n" );
	p_cFichero = _RutaDePrueba ( "atrib_no_existe.tmp" );
	SisEliminarFichero ( p_cFichero );

	if ( _AtributosTodosFalsos ( p_cFichero, "ruta inexistente" ) != BOOL_VAL_CIERTO )
	{
		iRes = BOOL_VAL_FALSO;
	}
	if ( _AtributosTodosFalsos ( NULL, "ruta nula" ) != BOOL_VAL_CIERTO )
	{
		iRes = BOOL_VAL_FALSO;
	}
	if ( SisRutaDesactivarModoSoloLectura ( p_cFichero ) != 0 )
	{
		printf ( "Error: SisRutaDesactivarModoSoloLectura de una ruta inexistente dijo que si\n" );
		iRes = BOOL_VAL_FALSO;
	}
	MemLiberarCadena ( &p_cFichero );
	return ( iRes );
}

/* Un fichero recien creado: legible, y sin ninguno de los demas atributos. */
static int TestSisAtributos02 ()
{
	char *		p_cFichero;
	int			iRes = BOOL_VAL_CIERTO;
	int			iObtenido;
	unsigned	uIdx;

	printf ( "Test SisAtributos 02 ( fichero normal ):\n" );
	p_cFichero = _RutaDePrueba ( "atrib_normal.tmp" );
	SisEliminarFichero ( p_cFichero );

	if ( SisCrearFichero ( p_cFichero ) != 1 )
	{
		printf ( "Error caso 1: no se pudo crear el fichero: %s\n", p_cFichero );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		for ( uIdx = 0; uIdx < SIS_NUM_ATRIBUTOS; uIdx++ )
		{
			iObtenido = g_atributos [ uIdx ].pfnConsulta ( p_cFichero );
			if ( iObtenido != g_atributos [ uIdx ].iEnFicheroNormal )
			{
				printf ( "Error caso 2: %s devolvio %d, se esperaba %d\n",
						 g_atributos [ uIdx ].p_cNombre, iObtenido,
						 g_atributos [ uIdx ].iEnFicheroNormal );
				iRes = BOOL_VAL_FALSO;
			}
		}
		SisEliminarFichero ( p_cFichero );
	}
	MemLiberarCadena ( &p_cFichero );
	return ( iRes );
}

/* El solo lectura, ida y vuelta: se pone, se detecta, se quita con la API y
   deja de detectarse. Es el unico atributo que la API sabe modificar. */
static int TestSisAtributos03 ()
{
	char *	p_cFichero;
	int		iRes = BOOL_VAL_CIERTO;

	printf ( "Test SisAtributos 03 ( solo lectura, ida y vuelta ):\n" );
	p_cFichero = _RutaDePrueba ( "atrib_solectura.tmp" );
	SisEliminarFichero ( p_cFichero );

	if ( SisCrearFichero ( p_cFichero ) != 1 )
	{
		printf ( "Error caso 1: no se pudo crear el fichero: %s\n", p_cFichero );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SisRutaDeSoloLectura ( p_cFichero ) != 0 )
		{
			printf ( "Error caso 2: un fichero recien creado no deberia ser de solo lectura\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( _PonerSoloLectura ( p_cFichero ) != 1 )
		{
			printf ( "Error caso 3: el propio test no pudo poner el solo lectura\n" );
			iRes = BOOL_VAL_FALSO;
		}
		else
		{
			if ( SisRutaDeSoloLectura ( p_cFichero ) != 1 )
			{
				printf ( "Error caso 4: no se detecto el solo lectura\n" );
				iRes = BOOL_VAL_FALSO;
			}
			/* Seguir siendo legible es parte del trato. */
			if ( SisFicheroEsAccesible ( p_cFichero ) != 1 )
			{
				printf ( "Error caso 5: un fichero de solo lectura sigue siendo legible\n" );
				iRes = BOOL_VAL_FALSO;
			}
			if ( SisRutaDesactivarModoSoloLectura ( p_cFichero ) != 1 )
			{
				printf ( "Error caso 6: SisRutaDesactivarModoSoloLectura fallo\n" );
				iRes = BOOL_VAL_FALSO;
			}
			if ( SisRutaDeSoloLectura ( p_cFichero ) != 0 )
			{
				printf ( "Error caso 7: seguia de solo lectura despues de desactivarlo\n" );
				iRes = BOOL_VAL_FALSO;
			}
		}
		/* Se borra despues de quitar el solo lectura, que si no Windows no deja. */
		SisEliminarFichero ( p_cFichero );
	}
	MemLiberarCadena ( &p_cFichero );
	return ( iRes );
}

/* "Oculto" no significa lo mismo en los dos mundos, y es a proposito: en WIN es
   el atributo de NTFS, y en POSIX ( Linux y Cygwin-POSIX ) es el punto delante
   del nombre. El caso fija las dos lecturas para que el dia que alguien las
   cambie se entere aqui. */
static int TestSisAtributos04 ()
{
	char *	p_cFichero;
	int		iRes = BOOL_VAL_CIERTO;
	int		iEsperado;

	printf ( "Test SisAtributos 04 ( oculto ):\n" );
	p_cFichero = _RutaDePrueba ( ".atrib_oculto.tmp" );
	SisEliminarFichero ( p_cFichero );

	if ( SisCrearFichero ( p_cFichero ) != 1 )
	{
		printf ( "Error caso 1: no se pudo crear el fichero: %s\n", p_cFichero );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
# if ( defined ( WIN ) )
		iEsperado = 0;
# else
		iEsperado = 1;
# endif
		if ( SisRutaOculta ( p_cFichero ) != iEsperado )
		{
			printf ( "Error caso 2: SisRutaOculta del fichero con punto devolvio %d, se esperaba %d\n",
					 SisRutaOculta ( p_cFichero ), iEsperado );
			iRes = BOOL_VAL_FALSO;
		}

# if ( defined ( WIN ) )
		/* Y con el atributo de NTFS puesto, que si lo vea. */
		if ( _PonerOculto ( p_cFichero ) != 1 )
		{
			printf ( "Error caso 3: el propio test no pudo poner el atributo de oculto\n" );
			iRes = BOOL_VAL_FALSO;
		}
		else
		{
			if ( SisRutaOculta ( p_cFichero ) != 1 )
			{
				printf ( "Error caso 4: SisRutaOculta no vio el atributo de NTFS\n" );
				iRes = BOOL_VAL_FALSO;
			}
		}
# endif
		SisEliminarFichero ( p_cFichero );
	}
	MemLiberarCadena ( &p_cFichero );
	return ( iRes );
}


int TestSistemaFicheros ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SistemaFicheros]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if (  ( TestSisNombreFichero01 () == BOOL_VAL_CIERTO ) &&
		 	( TestSisComponerRuta01 () == BOOL_VAL_CIERTO ) &&
		 	( TestSisResolverDirRelativo01 () == BOOL_VAL_CIERTO ) &&
			( TestSisFichero01 () == BOOL_VAL_CIERTO ) &&
			( TestSisDirectorio01 () == BOOL_VAL_CIERTO ) &&
			( TestSisValido01 () == BOOL_VAL_CIERTO ) &&
			( TestSisNulo01 () == BOOL_VAL_CIERTO ) &&
			( TestSisAtributos01 () == BOOL_VAL_CIERTO ) &&
			( TestSisAtributos02 () == BOOL_VAL_CIERTO ) &&
			( TestSisAtributos03 () == BOOL_VAL_CIERTO ) &&
			( TestSisAtributos04 () == BOOL_VAL_CIERTO ) )
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
