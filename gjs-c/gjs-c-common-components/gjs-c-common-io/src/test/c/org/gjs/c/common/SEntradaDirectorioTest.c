#include "Base.h"

#include "SEntradaDirectorio.h"



static int TestSEntDirFichero01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SEntDirFichero 01:\n" );
	SEntradaDirectorio * p_entdirObj = SEntDirCrearFicheroLit ( "datos.txt" );
	if ( ES_VALIDO ( p_entdirObj ) )
	{
		if ( SEntDirEsFichero ( p_entdirObj ) != 1 )
		{
			printf( "Error caso 1: se esperaba que sea fichero\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntDirEsDirectorio ( p_entdirObj ) != 0 )
		{
			printf( "Error caso 2: no se esperaba que sea directorio\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntDirEsValida ( p_entdirObj ) != 1 )
		{
			printf( "Error caso 3: se esperaba valida\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_NULO ( SEntDirEntradaLit ( p_entdirObj ) ) || ( CadComparar ( SEntDirEntradaLit ( p_entdirObj ), "datos.txt" ) != COMP_IGUAL ) )
		{
			printf( "Error caso 4: se esperaba entrada \"datos.txt\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el objeto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SEntDirDestruir ( &p_entdirObj );
	return ( iRes );
}

static int TestSEntDirDirectorio01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SEntDirDirectorio 01:\n" );
	SEntradaDirectorio * p_entdirObj = SEntDirCrearDirectorioLit ( "subdir" );
	if ( ES_VALIDO ( p_entdirObj ) )
	{
		if ( SEntDirEsDirectorio ( p_entdirObj ) != 1 )
		{
			printf( "Error caso 1: se esperaba que sea directorio\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntDirEsFichero ( p_entdirObj ) != 0 )
		{
			printf( "Error caso 2: no se esperaba que sea fichero\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_NULO ( SEntDirEntradaLit ( p_entdirObj ) ) || ( CadComparar ( SEntDirEntradaLit ( p_entdirObj ), "subdir" ) != COMP_IGUAL ) )
		{
			printf( "Error caso 3: se esperaba entrada \"subdir\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el objeto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SEntDirDestruir ( &p_entdirObj );
	return ( iRes );
}

static int TestSEntDirNulo01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SEntDirNulo 01:\n" );
	if ( SEntDirEsValida ( NULL ) != 0 )
	{
		printf( "Error caso 1: se esperaba no valida con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SEntDirEsFichero ( NULL ) != 0 )
	{
		printf( "Error caso 2: no se esperaba fichero con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SEntDirEsDirectorio ( NULL ) != 0 )
	{
		printf( "Error caso 3: no se esperaba directorio con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( SEntDirEntradaLit ( NULL ) ) )
	{
		printf( "Error caso 4: se esperaba entrada nula con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

int TestSEntradaDirectorio ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SEntradaDirectorio]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSEntDirFichero01 () == BOOL_VAL_CIERTO ) &&
			( TestSEntDirDirectorio01 () == BOOL_VAL_CIERTO ) &&
			( TestSEntDirNulo01 () == BOOL_VAL_CIERTO ) )
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
