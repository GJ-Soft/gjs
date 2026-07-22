#include "Base.h"
#include "Texto.h"

#include "SistemaFicheros.h"
#include "TestConfig.h"



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
	printf ( "1----------------------- Eliminar\n" );
	SisEliminarFichero ( p_cFichero );

	printf ( "2----------------------- Crear\n" );
	if ( SisCrearFichero ( p_cFichero ) != 1 )
	{
		printf( "Error caso 1: no se pudo crear el fichero: %s\n", p_cFichero );
		iRes = BOOL_VAL_FALSO;
	} 
	else
	{
		printf ( "3----------------------- Existe\n" );
		if ( SisExisteFichero ( p_cFichero ) != 1 )
		{
			printf( "Error caso 2: se esperaba que exista el fichero: %s\n", p_cFichero );
			iRes = BOOL_VAL_FALSO;
		}
		printf ( "4----------------------- Eliminar\n" );
		if ( SisEliminarFichero ( p_cFichero ) != 1 )
		{
			printf( "Error caso 3: no se pudo eliminar el fichero: %s\n", p_cFichero );
			iRes = BOOL_VAL_FALSO;
		}
		printf ( "5----------------------- Existe\n" );
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
			( TestSisNulo01 () == BOOL_VAL_CIERTO ) )
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
