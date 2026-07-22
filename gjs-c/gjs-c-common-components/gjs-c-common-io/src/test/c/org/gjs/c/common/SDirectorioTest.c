#include "Base.h"

#include "SDirectorio.h"
#include "SistemaFicheros.h"



static int TestSDirEnumerar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SDirEnumerar 01:\n" );
	/* Se trabaja sobre un directorio absoluto (el de trabajo) porque la validez
	   de directorio depende del patron del sistema (unidad en Windows). */
	char * p_cBase = SisDirectorioActual ();
	printf ( "Directorio actual: %s\n", p_cBase );
	char * p_cDirTest = SisResolverDirectorioRelativo ( p_cBase, "./data/sdir_test" );
	printf ( "Directorio test: %s\n", p_cDirTest );
	if ( ES_VALIDO ( p_cBase ) && ES_VALIDO ( p_cDirTest ) )
	{
		SDirectorio * p_dirObj = SDirCrearLit ( p_cDirTest );
		if ( ES_VALIDO ( p_dirObj ) )
		{
			if ( SDirEsValido ( p_dirObj ) != 1 )
			{
				printf( "Error caso 1: se esperaba directorio valido\n" );
				iRes = BOOL_VAL_FALSO;
			}
			if ( ES_NULO ( SDirNombre ( p_dirObj ) ) || ( SCadLongitud ( SDirNombre ( p_dirObj ) ) <= 0 ) )
			{
				printf( "Error caso 2: se esperaba nombre de directorio no vacio\n" );
				iRes = BOOL_VAL_FALSO;
			}
			if ( SDirNumEntradas ( p_dirObj ) != 2 )
			{
				printf( "Error caso 3: se esperaban 2 entradas: %d\n", SDirNumEntradas ( p_dirObj ) );
				iRes = BOOL_VAL_FALSO;
			}
			int iEncUno = 0;
			int iEncDos = 0;
			for ( int iEnt = 0; iEnt < SDirNumEntradas ( p_dirObj ); iEnt = iEnt + 1 )
			{
				SEntradaDirectorio * p_entdirObj = SDirEntrada ( p_dirObj, iEnt );
				if ( ( SEntDirEsFichero ( p_entdirObj ) == 1 ) && ES_VALIDO ( SEntDirEntradaLit ( p_entdirObj ) ) )
				{
					if ( CadComparar ( SEntDirEntradaLit ( p_entdirObj ), "uno.txt" ) == COMP_IGUAL )
					{
						iEncUno = 1;
					}
					if ( CadComparar ( SEntDirEntradaLit ( p_entdirObj ), "dos.txt" ) == COMP_IGUAL )
					{
						iEncDos = 1;
					}
				}
			}
			if ( ( iEncUno != 1 ) || ( iEncDos != 1 ) )
			{
				printf( "Error caso 4: no se encontraron las dos entradas esperadas\n" );
				iRes = BOOL_VAL_FALSO;
			}
			SDirDestruir ( &p_dirObj );
		}
		else
		{
			printf( "Error caso 0: no se pudo crear el objeto directorio\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo obtener el directorio de trabajo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	MemLiberar ( (void **) &p_cBase );
	MemLiberar ( (void **) &p_cDirTest );
	return ( iRes );
}

static int TestSDirNulo01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SDirNulo 01:\n" );
	if ( SDirEsValido ( NULL ) != 0 )
	{
		printf( "Error caso 1: se esperaba no valido con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SDirNumEntradas ( NULL ) != 0 )
	{
		printf( "Error caso 2: se esperaban 0 entradas con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( SDirEntrada ( NULL, 0 ) ) )
	{
		printf( "Error caso 3: se esperaba entrada nula con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( SDirNombre ( NULL ) ) )
	{
		printf( "Error caso 4: se esperaba nombre nulo con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

int TestSDirectorio ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SDirectorio]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSDirEnumerar01 () == BOOL_VAL_CIERTO ) &&
			( TestSDirNulo01 () == BOOL_VAL_CIERTO ) )
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
