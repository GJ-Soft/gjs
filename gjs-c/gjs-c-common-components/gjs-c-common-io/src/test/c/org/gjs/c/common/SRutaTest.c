#include "Base.h"

#include "SRuta.h"



static int TestSRutCrearFichero01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SRutCrearFichero 01:\n" );
	SRuta * p_rutObj = SRutCrearFicheroLit ( "/tmp", "datos.txt" );
	if ( ES_VALIDO ( p_rutObj ) )
	{
		if ( SRutEsFichero ( p_rutObj ) != 1 )
		{
			printf( "Error caso 1: se esperaba que sea fichero\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SRutEsDirectorio ( p_rutObj ) != 0 )
		{
			printf( "Error caso 2: no se esperaba que sea directorio\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_NULO ( SRutDirectorioLit ( p_rutObj ) ) || ( CadComparar ( SRutDirectorioLit ( p_rutObj ), "/tmp" ) != COMP_IGUAL ) )
		{
			printf( "Error caso 3: se esperaba directorio \"/tmp\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_NULO ( SRutFicheroLit ( p_rutObj ) ) || ( CadComparar ( SRutFicheroLit ( p_rutObj ), "datos.txt" ) != COMP_IGUAL ) )
		{
			printf( "Error caso 4: se esperaba fichero \"datos.txt\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el objeto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SRutDestruir ( &p_rutObj );
	return ( iRes );
}

static int TestSRutCrearDirectorio01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SRutCrearDirectorio 01:\n" );
	SRuta * p_rutObj = SRutCrearDirectorioLit ( "/tmp/datos" );
	if ( ES_VALIDO ( p_rutObj ) )
	{
		if ( SRutEsDirectorio ( p_rutObj ) != 1 )
		{
			printf( "Error caso 1: se esperaba que sea directorio\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SRutEsFichero ( p_rutObj ) != 0 )
		{
			printf( "Error caso 2: no se esperaba que sea fichero\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( SRutFicheroLit ( p_rutObj ) ) )
		{
			printf( "Error caso 3: se esperaba fichero nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el objeto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SRutDestruir ( &p_rutObj );
	return ( iRes );
}

static int TestSRutExtension01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SRutExtension 01:\n" );
	SRuta * p_rutObj = SRutCrearFicheroLit ( "/tmp", "datos.txt" );
	if ( ES_VALIDO ( p_rutObj ) )
	{
		if ( SRutTieneExtension ( p_rutObj ) != 1 )
		{
			printf( "Error caso 1: se esperaba que tenga extension\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SRutTieneExtensionExt ( p_rutObj, "txt" ) != 1 )
		{
			printf( "Error caso 2: se esperaba extension \"txt\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SRutTieneExtensionExt ( p_rutObj, "bin" ) != 0 )
		{
			printf( "Error caso 3: no se esperaba extension \"bin\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		char * p_cSinExt = SRutFicheroSinExtensionLit ( p_rutObj );
		if ( ES_NULO ( p_cSinExt ) || ( CadComparar ( p_cSinExt, "datos" ) != COMP_IGUAL ) )
		{
			printf( "Error caso 4: se esperaba fichero sin extension \"datos\": [%s]\n", ES_VALIDO ( p_cSinExt ) ? p_cSinExt : "(nulo)" );
			iRes = BOOL_VAL_FALSO;
		}
		MemLiberar ( (void **) &p_cSinExt );
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el objeto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SRutDestruir ( &p_rutObj );
	return ( iRes );
}

static int TestSRutExtension02 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SRutExtension 02:\n" );
	/* Fichero sin extension. */
	SRuta * p_rutObj = SRutCrearFicheroLit ( "/tmp", "datos" );
	if ( ES_VALIDO ( p_rutObj ) )
	{
		if ( SRutTieneExtension ( p_rutObj ) != 0 )
		{
			printf( "Error caso 1: no se esperaba que tenga extension\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SRutAgregarExtensionLit ( p_rutObj, "txt" ) != 1 )
		{
			printf( "Error caso 2: se esperaba agregar extension correcto\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( CadComparar ( SRutFicheroLit ( p_rutObj ), "datos.txt" ) != COMP_IGUAL )
		{
			printf( "Error caso 3: se esperaba fichero \"datos.txt\": %s\n", SRutFicheroLit ( p_rutObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SRutTieneExtension ( p_rutObj ) != 1 )
		{
			printf( "Error caso 4: se esperaba que tenga extension tras agregar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SRutEliminarExtension ( p_rutObj ) != 1 )
		{
			printf( "Error caso 5: se esperaba eliminar extension correcto\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( CadComparar ( SRutFicheroLit ( p_rutObj ), "datos" ) != COMP_IGUAL )
		{
			printf( "Error caso 6: se esperaba fichero \"datos\" tras eliminar extension: %s\n", SRutFicheroLit ( p_rutObj ) );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el objeto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SRutDestruir ( &p_rutObj );
	return ( iRes );
}

static int TestSRutEstablecer01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SRutEstablecer 01:\n" );
	SRuta * p_rutObj = SRutCrearFicheroLit ( "/tmp", "datos.txt" );
	if ( ES_VALIDO ( p_rutObj ) )
	{
		if ( SRutEstablecerFicheroLit ( p_rutObj, "otro.bin" ) != 1 )
		{
			printf( "Error caso 1: se esperaba establecer fichero correcto\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( CadComparar ( SRutFicheroLit ( p_rutObj ), "otro.bin" ) != COMP_IGUAL )
		{
			printf( "Error caso 2: se esperaba fichero \"otro.bin\": %s\n", SRutFicheroLit ( p_rutObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		SRuta * p_rutDup = SRutDuplicar ( p_rutObj );
		if ( ES_VALIDO ( p_rutDup ) )
		{
			if ( CadComparar ( SRutFicheroLit ( p_rutDup ), "otro.bin" ) != COMP_IGUAL )
			{
				printf( "Error caso 3: el duplicado no conserva el fichero\n" );
				iRes = BOOL_VAL_FALSO;
			}
			if ( CadComparar ( SRutDirectorioLit ( p_rutDup ), "/tmp" ) != COMP_IGUAL )
			{
				printf( "Error caso 4: el duplicado no conserva el directorio\n" );
				iRes = BOOL_VAL_FALSO;
			}
		}
		else
		{
			printf( "Error caso 3: no se pudo duplicar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SRutDestruir ( &p_rutDup );
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el objeto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SRutDestruir ( &p_rutObj );
	return ( iRes );
}

static int TestSRutValida01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SRutValida 01:\n" );
	/* La validez del directorio depende del patron del sistema: en Windows
	   se exige unidad, en POSIX una ruta que empiece por '/'. */
#if defined ( WIN )
	SRuta * p_rutObj = SRutCrearFicheroLit ( "C:\\Temp", "datos.txt" );
#else
	SRuta * p_rutObj = SRutCrearFicheroLit ( "/tmp", "datos.txt" );
#endif
	if ( ES_VALIDO ( p_rutObj ) )
	{
		if ( SRutEsFicheroValido ( p_rutObj ) != 1 )
		{
			printf( "Error caso 1: se esperaba fichero valido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SRutEsDirectorioValido ( p_rutObj ) != 1 )
		{
			printf( "Error caso 2: se esperaba directorio valido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SRutEsValida ( p_rutObj ) != 1 )
		{
			printf( "Error caso 3: se esperaba ruta valida\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el objeto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SRutDestruir ( &p_rutObj );
	return ( iRes );
}

static int TestSRutNulo01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SRutNulo 01:\n" );
	if ( SRutEsValida ( NULL ) != 0 )
	{
		printf( "Error caso 1: se esperaba no valida con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SRutEsFichero ( NULL ) != 0 )
	{
		printf( "Error caso 2: se esperaba no fichero con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( SRutFicheroLit ( NULL ) ) )
	{
		printf( "Error caso 3: se esperaba fichero nulo con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

/* Estilo del directorio. Antes las dos funciones usaban expresiones PCRE
   que este motor no entiende y daban siempre 0. Un directorio sin
   separadores ni unidad es de los dos estilos; uno que mezcla, de ninguno. */
static int TestSRutEstilo01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SRutEstilo 01:\n" );
	SRuta * p_rutObj = SRutCrearDirectorioLit ( "/tmp" );
	SRutEstablecerDirectorioLit ( p_rutObj, "/tmp" );
	if ( ( SRutEsEstiloUNIX ( p_rutObj ) != 1 ) || ( SRutEsEstiloDOS ( p_rutObj ) != 0 ) )
	{
		printf( "Error caso 1: [/tmp] se esperaba UNIX 1 y DOS 0: %d y %d\n",
				SRutEsEstiloUNIX ( p_rutObj ), SRutEsEstiloDOS ( p_rutObj ) );
		iRes = BOOL_VAL_FALSO;
	}
	SRutEstablecerDirectorioLit ( p_rutObj, "/tmp/datos" );
	if ( ( SRutEsEstiloUNIX ( p_rutObj ) != 1 ) || ( SRutEsEstiloDOS ( p_rutObj ) != 0 ) )
	{
		printf( "Error caso 2: [/tmp/datos] se esperaba UNIX 1 y DOS 0: %d y %d\n",
				SRutEsEstiloUNIX ( p_rutObj ), SRutEsEstiloDOS ( p_rutObj ) );
		iRes = BOOL_VAL_FALSO;
	}
	SRutEstablecerDirectorioLit ( p_rutObj, "/" );
	if ( ( SRutEsEstiloUNIX ( p_rutObj ) != 1 ) || ( SRutEsEstiloDOS ( p_rutObj ) != 0 ) )
	{
		printf( "Error caso 3: [/] se esperaba UNIX 1 y DOS 0: %d y %d\n",
				SRutEsEstiloUNIX ( p_rutObj ), SRutEsEstiloDOS ( p_rutObj ) );
		iRes = BOOL_VAL_FALSO;
	}
	SRutEstablecerDirectorioLit ( p_rutObj, "./a" );
	if ( ( SRutEsEstiloUNIX ( p_rutObj ) != 1 ) || ( SRutEsEstiloDOS ( p_rutObj ) != 0 ) )
	{
		printf( "Error caso 4: [./a] se esperaba UNIX 1 y DOS 0: %d y %d\n",
				SRutEsEstiloUNIX ( p_rutObj ), SRutEsEstiloDOS ( p_rutObj ) );
		iRes = BOOL_VAL_FALSO;
	}
	SRutEstablecerDirectorioLit ( p_rutObj, "../a/b" );
	if ( ( SRutEsEstiloUNIX ( p_rutObj ) != 1 ) || ( SRutEsEstiloDOS ( p_rutObj ) != 0 ) )
	{
		printf( "Error caso 5: [../a/b] se esperaba UNIX 1 y DOS 0: %d y %d\n",
				SRutEsEstiloUNIX ( p_rutObj ), SRutEsEstiloDOS ( p_rutObj ) );
		iRes = BOOL_VAL_FALSO;
	}
	SRutEstablecerDirectorioLit ( p_rutObj, "C:\\Temp" );
	if ( ( SRutEsEstiloUNIX ( p_rutObj ) != 0 ) || ( SRutEsEstiloDOS ( p_rutObj ) != 1 ) )
	{
		printf( "Error caso 6: [C:\\Temp] se esperaba UNIX 0 y DOS 1: %d y %d\n",
				SRutEsEstiloUNIX ( p_rutObj ), SRutEsEstiloDOS ( p_rutObj ) );
		iRes = BOOL_VAL_FALSO;
	}
	SRutEstablecerDirectorioLit ( p_rutObj, "C:\\" );
	if ( ( SRutEsEstiloUNIX ( p_rutObj ) != 0 ) || ( SRutEsEstiloDOS ( p_rutObj ) != 1 ) )
	{
		printf( "Error caso 7: [C:\\] se esperaba UNIX 0 y DOS 1: %d y %d\n",
				SRutEsEstiloUNIX ( p_rutObj ), SRutEsEstiloDOS ( p_rutObj ) );
		iRes = BOOL_VAL_FALSO;
	}
	SRutEstablecerDirectorioLit ( p_rutObj, "C:" );
	if ( ( SRutEsEstiloUNIX ( p_rutObj ) != 0 ) || ( SRutEsEstiloDOS ( p_rutObj ) != 1 ) )
	{
		printf( "Error caso 8: [C:] se esperaba UNIX 0 y DOS 1: %d y %d\n",
				SRutEsEstiloUNIX ( p_rutObj ), SRutEsEstiloDOS ( p_rutObj ) );
		iRes = BOOL_VAL_FALSO;
	}
	SRutEstablecerDirectorioLit ( p_rutObj, "\\\\srv\\sh" );
	if ( ( SRutEsEstiloUNIX ( p_rutObj ) != 0 ) || ( SRutEsEstiloDOS ( p_rutObj ) != 1 ) )
	{
		printf( "Error caso 9: [\\\\srv\\sh] se esperaba UNIX 0 y DOS 1: %d y %d\n",
				SRutEsEstiloUNIX ( p_rutObj ), SRutEsEstiloDOS ( p_rutObj ) );
		iRes = BOOL_VAL_FALSO;
	}
	SRutEstablecerDirectorioLit ( p_rutObj, "..\\a" );
	if ( ( SRutEsEstiloUNIX ( p_rutObj ) != 0 ) || ( SRutEsEstiloDOS ( p_rutObj ) != 1 ) )
	{
		printf( "Error caso 10: [..\\a] se esperaba UNIX 0 y DOS 1: %d y %d\n",
				SRutEsEstiloUNIX ( p_rutObj ), SRutEsEstiloDOS ( p_rutObj ) );
		iRes = BOOL_VAL_FALSO;
	}
	SRutEstablecerDirectorioLit ( p_rutObj, "tmp" );
	if ( ( SRutEsEstiloUNIX ( p_rutObj ) != 1 ) || ( SRutEsEstiloDOS ( p_rutObj ) != 1 ) )
	{
		printf( "Error caso 11: [tmp] se esperaba UNIX 1 y DOS 1: %d y %d\n",
				SRutEsEstiloUNIX ( p_rutObj ), SRutEsEstiloDOS ( p_rutObj ) );
		iRes = BOOL_VAL_FALSO;
	}
	SRutEstablecerDirectorioLit ( p_rutObj, "C:/dir" );
	if ( ( SRutEsEstiloUNIX ( p_rutObj ) != 0 ) || ( SRutEsEstiloDOS ( p_rutObj ) != 0 ) )
	{
		printf( "Error caso 12: [C:/dir] se esperaba UNIX 0 y DOS 0: %d y %d\n",
				SRutEsEstiloUNIX ( p_rutObj ), SRutEsEstiloDOS ( p_rutObj ) );
		iRes = BOOL_VAL_FALSO;
	}
	SRutEstablecerDirectorioLit ( p_rutObj, "a/b\\c" );
	if ( ( SRutEsEstiloUNIX ( p_rutObj ) != 0 ) || ( SRutEsEstiloDOS ( p_rutObj ) != 0 ) )
	{
		printf( "Error caso 13: [a/b\\c] se esperaba UNIX 0 y DOS 0: %d y %d\n",
				SRutEsEstiloUNIX ( p_rutObj ), SRutEsEstiloDOS ( p_rutObj ) );
		iRes = BOOL_VAL_FALSO;
	}
	/* Sin directorio no es de ningun estilo. */
	SRutEstablecerDirectorioLit ( p_rutObj, "" );
	if ( ( SRutEsEstiloUNIX ( p_rutObj ) != 0 ) || ( SRutEsEstiloDOS ( p_rutObj ) != 0 ) )
	{
		printf( "Error caso 15: un directorio vacio no deberia ser de ningun estilo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SRutDestruir ( &p_rutObj );
	if ( ( SRutEsEstiloUNIX ( NULL ) != 0 ) || ( SRutEsEstiloDOS ( NULL ) != 0 ) )
	{
		printf( "Error caso 14: con nulo se esperaba 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

int TestSRuta ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SRuta]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSRutCrearFichero01 () == BOOL_VAL_CIERTO ) &&
			( TestSRutCrearDirectorio01 () == BOOL_VAL_CIERTO ) &&
			( TestSRutExtension01 () == BOOL_VAL_CIERTO ) &&
			( TestSRutExtension02 () == BOOL_VAL_CIERTO ) &&
			( TestSRutEstablecer01 () == BOOL_VAL_CIERTO ) &&
			( TestSRutValida01 () == BOOL_VAL_CIERTO ) &&
			( TestSRutNulo01 () == BOOL_VAL_CIERTO ) &&
			( TestSRutEstilo01 () == BOOL_VAL_CIERTO ) )
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
