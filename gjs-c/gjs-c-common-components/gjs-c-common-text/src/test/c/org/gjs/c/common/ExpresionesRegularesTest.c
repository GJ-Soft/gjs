#include "Base.h"
#include "Cadenas.h"
#include "ExpresionesRegulares.h"

static int TestExpRegSeCumpleAlInicio01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test ExpRegSeCumpleAlInicio 01 (literal coincide al inicio):\n" );
	if ( ExpRegSeCumpleAlInicio ( "Hola", "HolaMundo" ) != BOOL_VAL_CIERTO )
	{
		printf( "Error caso 1: Se esperaba CIERTO para patron [Hola] en cadena [HolaMundo]\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ExpRegSeCumpleAlInicio ( "Mundo", "HolaMundo" ) != BOOL_VAL_FALSO )
	{
		printf( "Error caso 2: Se esperaba FALSO para patron [Mundo] en cadena [HolaMundo]\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ExpRegSeCumpleAlInicio ( "HolaMundo", "HolaMundo" ) != BOOL_VAL_CIERTO )
	{
		printf( "Error caso 3: Se esperaba CIERTO para patron [HolaMundo] en cadena [HolaMundo]\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestExpRegSeCumpleAlInicio02 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test ExpRegSeCumpleAlInicio 02 (comodin ?):\n" );
	if ( ExpRegSeCumpleAlInicio ( "Ho?a", "HolaMundo" ) != BOOL_VAL_CIERTO )
	{
		printf( "Error caso 1: Se esperaba CIERTO para patron [Ho?a] en cadena [HolaMundo]\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ExpRegSeCumpleAlInicio ( "?ola", "HolaMundo" ) != BOOL_VAL_CIERTO )
	{
		printf( "Error caso 2: Se esperaba CIERTO para patron [?ola] en cadena [HolaMundo]\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ExpRegSeCumpleAlInicio ( "????", "HolaMundo" ) != BOOL_VAL_CIERTO )
	{
		printf( "Error caso 3: Se esperaba CIERTO para patron [????] en cadena [HolaMundo]\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ExpRegSeCumpleAlInicio ( "?????Mundo", "Hola Mundo" ) != BOOL_VAL_CIERTO )
	{
		printf( "Error caso 4: Se esperaba CIERTO para patron [?????Mundo] en cadena [HolaMundo]\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ExpRegSeCumpleAlInicio ( "???? Mundo", "Hola Mundo" ) != BOOL_VAL_CIERTO )
	{
		printf( "Error caso 4: Se esperaba CIERTO para patron [?????Mundo] en cadena [HolaMundo]\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ExpRegSeCumpleAlInicio ( "?X", "HolaMundo" ) != BOOL_VAL_FALSO )
	{
		printf( "Error caso 5: Se esperaba FALSO para patron [?X] en cadena [HolaMundo]\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestExpRegSeCumpleAlInicio03 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test ExpRegSeCumpleAlInicio 03 (comodin *):\n" );
	if ( ExpRegSeCumpleAlInicio ( "*", "HolaMundo" ) != BOOL_VAL_CIERTO )
	{
		printf( "Error caso 1: Se esperaba CIERTO para patron [*] en cadena [HolaMundo]\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ExpRegSeCumpleAlInicio ( "Hola*", "HolaMundo" ) != BOOL_VAL_CIERTO )
	{
		printf( "Error caso 2: Se esperaba CIERTO para patron [Hola*] en cadena [HolaMundo]\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ExpRegSeCumpleAlInicio ( "H*Mundo", "HolaMundo" ) != BOOL_VAL_CIERTO )
	{
		printf( "Error caso 3: Se esperaba CIERTO para patron [H*Mundo] en cadena [HolaMundo]\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ExpRegSeCumpleAlInicio ( "X*", "HolaMundo" ) != BOOL_VAL_FALSO )
	{
		printf( "Error caso 4: Se esperaba FALSO para patron [X*] en cadena [HolaMundo]\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestExpRegSeCumpleAlInicio04 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test ExpRegSeCumpleAlInicio 04 (literales con comilla simple):\n" );
	/* El caracter especial entre comillas simples se trata como literal */
	if ( ExpRegSeCumpleAlInicio ( "'?'BC", "?BC" ) != BOOL_VAL_CIERTO )
	{
		printf( "Error caso 1: Se esperaba CIERTO para patron ['?'BC] en cadena [?BC]\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ExpRegSeCumpleAlInicio ( "'*'", "HolaMundo" ) != BOOL_VAL_FALSO )
	{
		printf( "Error caso 2: Se esperaba FALSO para patron ['*'] en cadena [HolaMundo]\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ExpRegSeCumpleAlInicio ( "'*'", "*" ) != BOOL_VAL_CIERTO )
	{
		printf( "Error caso 3: Se esperaba CIERTO para patron ['*'] en cadena [*]\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestExpRegSeCumple01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test ExpRegSeCumple 01 (literal coincidencia exacta):\n" );
	if ( ExpRegSeCumple ( "HolaMundo", "HolaMundo" ) != BOOL_VAL_CIERTO )
	{
		printf( "Error caso 1: Se esperaba CIERTO para patron [HolaMundo] en cadena [HolaMundo]\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ExpRegSeCumple ( "Hola", "HolaMundo" ) != BOOL_VAL_FALSO )
	{
		printf( "Error caso 2: Se esperaba FALSO para patron [Hola] en cadena [HolaMundo] (coincidencia parcial)\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ExpRegSeCumple ( "HolaMundoX", "HolaMundo" ) != BOOL_VAL_FALSO )
	{
		printf( "Error caso 3: Se esperaba FALSO para patron [HolaMundoX] en cadena [HolaMundo]\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ExpRegSeCumple ( "HolaMundo", "HolaMundoX" ) != BOOL_VAL_FALSO )
	{
		printf( "Error caso 4: Se esperaba FALSO para patron [HolaMundo] en cadena [HolaMundoX]\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ExpRegSeCumple ( "Hola'Mu'ndo", "HolaMundo" ) != BOOL_VAL_CIERTO )
	{
		printf( "Error caso 1: Se esperaba CIERTO para patron [Hola'Mu'ndo] en cadena [HolaMundo]\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ExpRegSeCumple ( "Hola'M'undo", "HolaMundo" ) != BOOL_VAL_CIERTO )
	{
		printf( "Error caso 1: Se esperaba CIERTO para patron [Hola'M'undo] en cadena [HolaMundo]\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ExpRegSeCumple ( "Hola''Mundo", "HolaMundo" ) != BOOL_VAL_CIERTO )
	{
		printf( "Error caso 1: Se esperaba CIERTO para patron [Hola''Mundo] en cadena [HolaMundo]\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ExpRegSeCumple ( "Hola'Mu'n'do", "HolaMundo" ) != BOOL_VAL_FALSO )
	{
		printf( "Error caso 1: Se esperaba FALSO para patron [Hola'Mu'n'do] en cadena [HolaMundo]\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ExpRegSeCumple ( "Hola'M'und'o'", "HolaMundo" ) != BOOL_VAL_CIERTO )
	{
		printf( "Error caso 1: Se esperaba CIERTO para patron [Hola'M'und'o'] en cadena [HolaMundo]\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestExpRegSeCumple02 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test ExpRegSeCumple 02 (comodin ?):\n" );
	if ( ExpRegSeCumple ( "????Mundo", "HolaMundo" ) != BOOL_VAL_CIERTO )
	{
		printf( "Error caso 1: Se esperaba CIERTO para patron [????Mundo] en cadena [HolaMundo]\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ExpRegSeCumple ( "???Mundo", "HolaMundo" ) != BOOL_VAL_FALSO )
	{
		printf( "Error caso 2: Se esperaba FALSO para patron [???Mundo] en cadena [HolaMundo] (longitud incorrecta)\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ExpRegSeCumple ( "?????????", "HolaMundo" ) != BOOL_VAL_CIERTO )
	{
		printf( "Error caso 3: Se esperaba CIERTO para patron [?????????] en cadena [HolaMundo]\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestExpRegSeCumple03 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test ExpRegSeCumple 03 (comodin *):\n" );
	if ( ExpRegSeCumple ( "*", "HolaMundo" ) != BOOL_VAL_CIERTO )
	{
		printf( "Error caso 1: Se esperaba CIERTO para patron [*] en cadena [HolaMundo]\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ExpRegSeCumple ( "Hola*Mundo", "HolaMundo" ) != BOOL_VAL_CIERTO )
	{
		printf( "Error caso 2: Se esperaba CIERTO para patron [Hola*Mundo] en cadena [HolaMundo]\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ExpRegSeCumple ( "Hola*Mundo", "HolaGranMundo" ) != BOOL_VAL_CIERTO )
	{
		printf( "Error caso 3: Se esperaba CIERTO para patron [Hola*Mundo] en cadena [HolaGranMundo]\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ExpRegSeCumple ( "Hola*", "HolaMundo" ) != BOOL_VAL_CIERTO )
	{
		printf( "Error caso 4: Se esperaba CIERTO para patron [Hola*] en cadena [HolaMundo]\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ExpRegSeCumple ( "*Mundo", "HolaMundo" ) != BOOL_VAL_CIERTO )
	{
		printf( "Error caso 5: Se esperaba CIERTO para patron [*Mundo] en cadena [HolaMundo]\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ExpRegSeCumple ( "X*", "HolaMundo" ) != BOOL_VAL_FALSO )
	{
		printf( "Error caso 6: Se esperaba FALSO para patron [X*] en cadena [HolaMundo]\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestExpRegSeCumple04 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test ExpRegSeCumple 04 (rutas patron [/(?*/)(?*)]):\n" );
	if ( ExpRegSeCumple ( "/(?*/)(?*)", "/" ) != BOOL_VAL_CIERTO )
	{
		printf( "Error caso 1: Se esperaba CIERTO para patron [/(?*/)(?*)] en ruta [/]\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ExpRegSeCumple ( "/(?*/)(?*)", "/directorio" ) != BOOL_VAL_CIERTO )
	{
		printf( "Error caso 2: Se esperaba CIERTO para patron [/(?*/)(?*)] en ruta [/directorio]\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ExpRegSeCumple ( "/(?*/)(?*)", "/directorio/subdirectorio" ) != BOOL_VAL_CIERTO )
	{
		printf( "Error caso 3: Se esperaba CIERTO para patron [/(?*/)(?*)] en ruta [/directorio/subdirectorio]\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ExpRegSeCumple ( "/(?*/)(?*)", "/directorio/subdirectorio/fichero.txt" ) != BOOL_VAL_CIERTO )
	{
		printf( "Error caso 4: Se esperaba CIERTO para patron [/(/?*)] en ruta [/directorio/subdirectorio/fichero.txt]\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ExpRegSeCumple ( "/(?*/)(?*)", "/directorio/subdirectorio/.fichero" ) != BOOL_VAL_CIERTO )
	{
		printf( "Error caso 5: Se esperaba CIERTO para patron [/(?*/)(?*)] en ruta [/directorio/subdirectorio/.fichero]\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ExpRegSeCumple ( "/(?*/)(?*)", "./directorio" ) != BOOL_VAL_FALSO )
	{
		printf( "Error caso 6: Se esperaba FALSO para patron [/(?*/)(?*)] en ruta [./directorio]\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ExpRegSeCumple ( "/(?*/)(?*)", "../directorio" ) != BOOL_VAL_FALSO )
	{
		printf( "Error caso 7: Se esperaba FALSO para patron [/(?*/)(?*)] en ruta [../directorio]\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ExpRegSeCumple ( "/(?*/)(?*)", "C:\\directorio\\subdirectorio\\fichero.txt" ) != BOOL_VAL_FALSO )
	{
		printf( "Error caso 8: Se esperaba FALSO para patron [/(?*/)(?*)] en ruta [C:\\directorio\\subdirectorio\\fichero.txt]\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestExpRegSeCumple05 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test ExpRegSeCumple 05 (rutas patron [.(/?*)]):\n" );
	if ( ExpRegSeCumple ( ".(/?*)", "." ) != BOOL_VAL_CIERTO )
	{
		printf( "Error caso 1: Se esperaba CIERTO para patron [.(/?*)] en ruta [.]\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ExpRegSeCumple ( ".(/?*)", "./directorio" ) != BOOL_VAL_CIERTO )
	{
		printf( "Error caso 2: Se esperaba CIERTO para patron [.(/?*)] en ruta [./directorio]\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ExpRegSeCumple ( ".(/?*)", "./directorio/subdirectorio" ) != BOOL_VAL_CIERTO )
	{
		printf( "Error caso 3: Se esperaba CIERTO para patron [.(/?*)] en ruta [./directorio/subdirectorio]\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ExpRegSeCumple ( ".(/?*)", "./directorio/subdirectorio/fichero.txt" ) != BOOL_VAL_CIERTO )
	{
		printf( "Error caso 4: Se esperaba CIERTO para patron [.(/?*)] en ruta [./directorio/subdirectorio/fichero.txt]\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ExpRegSeCumple ( ".(/?*)", "./directorio/subdirectorio/.fichero" ) != BOOL_VAL_CIERTO )
	{
		printf( "Error caso 5: Se esperaba CIERTO para patron [.(/?*)] en ruta [./directorio/subdirectorio/.fichero]\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ExpRegSeCumple ( ".(/?*)", "../directorio" ) != BOOL_VAL_FALSO )
	{
		printf( "Error caso 6: Se esperaba FALSO para patron [.(/?*)] en ruta [../directorio]\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ExpRegSeCumple ( ".(/?*)", "/directorio" ) != BOOL_VAL_FALSO )
	{
		printf( "Error caso 7: Se esperaba FALSO para patron [.(/?*)] en ruta [/directorio]\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ExpRegSeCumple ( ".(/?*)", ".\\directorio\\subdirectorio\\fichero.txt" ) != BOOL_VAL_FALSO )
	{
		printf( "Error caso 8: Se esperaba FALSO para patron [.(/?*)] en ruta [.\\directorio\\subdirectorio\\fichero.txt]\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestExpRegSeCumple06 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test ExpRegSeCumple 06 (rutas patron [..(/?*)]):\n" );
	if ( ExpRegSeCumple ( "..(/?*)", ".." ) != BOOL_VAL_CIERTO )
	{
		printf( "Error caso 1: Se esperaba CIERTO para patron [..(/?*)] en ruta [..]\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ExpRegSeCumple ( "..(/?*)", "../directorio" ) != BOOL_VAL_CIERTO )
	{
		printf( "Error caso 2: Se esperaba CIERTO para patron [..(/?*)] en ruta [../directorio]\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ExpRegSeCumple ( "..(/?*)", "../directorio/subdirectorio" ) != BOOL_VAL_CIERTO )
	{
		printf( "Error caso 3: Se esperaba CIERTO para patron [..(/?*)] en ruta [../directorio/subdirectorio]\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ExpRegSeCumple ( "..(/?*)", "../directorio/subdirectorio/fichero.txt" ) != BOOL_VAL_CIERTO )
	{
		printf( "Error caso 4: Se esperaba CIERTO para patron [..(/?*)] en ruta [../directorio/subdirectorio/fichero.txt]\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ExpRegSeCumple ( "..(/?*)", "../directorio/subdirectorio/.fichero" ) != BOOL_VAL_CIERTO )
	{
		printf( "Error caso 6: Se esperaba CIERTO para patron [..(/?*)] en ruta [/directorio/subdirectorio/.fichero]\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ExpRegSeCumple ( "..(/?*)", "./directorio" ) != BOOL_VAL_FALSO )
	{
		printf( "Error caso 6: Se esperaba FALSO para patron [..(/?*)] en ruta [./directorio]\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ExpRegSeCumple ( "..(/?*)", "/directorio" ) != BOOL_VAL_FALSO )
	{
		printf( "Error caso 7: Se esperaba FALSO para patron [..(/?*)] en ruta [/directorio]\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ExpRegSeCumple ( "..(/?*)", "..\\directorio\\subdirectorio\\fichero.txt" ) != BOOL_VAL_FALSO )
	{
		printf( "Error caso 8: Se esperaba FALSO para patron [..(/?*)] en ruta [..\\directorio\\subdirectorio\\fichero.txt]\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestExpRegSeCumple07 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test ExpRegSeCumple 07 (rutas patron [?:\\(?*\\)(?*)]):\n" );
	if ( ExpRegSeCumple ( "?:\\(?*\\)(?*)", "C:\\" ) != BOOL_VAL_CIERTO )
	{
		printf( "Error caso 1: Se esperaba CIERTO para patron [?:\\(?*\\)(?*)] en ruta [C:\\]\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ExpRegSeCumple ( "?:\\(?*\\)(?*)", "C:\\directorio" ) != BOOL_VAL_CIERTO )
	{
		printf( "Error caso 2: Se esperaba CIERTO para patron [?:\\(?*\\)(?*)] en ruta [C:\\directorio]\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ExpRegSeCumple ( "?:\\(?*\\)(?*)", "C:\\directorio\\subdirectorio" ) != BOOL_VAL_CIERTO )
	{
		printf( "Error caso 3: Se esperaba CIERTO para patron [?:\\(?*\\)(?*)] en ruta [C:\\directorio\\subdirectorio]\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ExpRegSeCumple ( "?:\\(?*\\)(?*)", "C:\\directorio\\subdirectorio\\fichero.txt" ) != BOOL_VAL_CIERTO )
	{
		printf( "Error caso 4: Se esperaba CIERTO para patron [?:\\(?*\\)(?*)] en ruta [C:\\directorio\\subdirectorio\\fichero.txt]\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ExpRegSeCumple ( "?:\\(?*\\)(?*)", "C:\\directorio\\subdirectorio\\.fichero" ) != BOOL_VAL_CIERTO )
	{
		printf( "Error caso 5: Se esperaba CIERTO para patron [?:\\(?*\\)(?*)] en ruta [C:\\directorio\\subdirectorio\\.fichero]\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ExpRegSeCumple ( "?:\\(?*\\)(?*)", ".\\directorio" ) != BOOL_VAL_FALSO )
	{
		printf( "Error caso 6: Se esperaba FALSO para patron [?:\\(?*\\)(?*)] en ruta [.\\directorio]\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ExpRegSeCumple ( "?:\\(?*\\)(?*)", "..\\directorio" ) != BOOL_VAL_FALSO )
	{
		printf( "Error caso 7: Se esperaba FALSO para patron [?:\\(?*\\)(?*)] en ruta [..\\directorio]\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ExpRegSeCumple ( "?:\\(?*\\)(?*)", "/directorio/subdirectorio/fichero.txt" ) != BOOL_VAL_FALSO )
	{
		printf( "Error caso 8: Se esperaba FALSO para patron [?:\\(?*\\)(?*)] en ruta [/directorio/subdirectorio/fichero.txt]\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestExpRegSeCumple08 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test ExpRegSeCumple 08 (rutas patron [.(\\?*)]):\n" );
	if ( ExpRegSeCumple ( ".(\\?*)", "." ) != BOOL_VAL_CIERTO )
	{
		printf( "Error caso 1: Se esperaba CIERTO para patron [.(\\?*)] en ruta [.]\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ExpRegSeCumple ( ".(\\?*)", ".\\directorio" ) != BOOL_VAL_CIERTO )
	{
		printf( "Error caso 2: Se esperaba CIERTO para patron [.(\\?*)] en ruta [.\\directorio]\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ExpRegSeCumple ( ".(\\?*)", ".\\directorio\\subdirectorio" ) != BOOL_VAL_CIERTO )
	{
		printf( "Error caso 3: Se esperaba CIERTO para patron [.(\\?*)] en ruta [.\\directorio\\subdirectorio]\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ExpRegSeCumple ( ".(\\?*)", ".\\directorio\\subdirectorio\\fichero.txt" ) != BOOL_VAL_CIERTO )
	{
		printf( "Error caso 4: Se esperaba CIERTO para patron [.(\\?*)] en ruta [.\\directorio\\subdirectorio\\fichero.txt]\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ExpRegSeCumple ( ".(\\?*)", ".\\directorio\\subdirectorio\\.fichero" ) != BOOL_VAL_CIERTO )
	{
		printf( "Error caso 5: Se esperaba CIERTO para patron [.(\\?*)] en ruta [.\\directorio\\subdirectorio\\.fichero]\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ExpRegSeCumple ( ".(\\?*)", "..\\directorio" ) != BOOL_VAL_FALSO )
	{
		printf( "Error caso 6: Se esperaba FALSO para patron [.(\\?*)] en ruta [..\\directorio]\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ExpRegSeCumple ( ".(\\?*)", "\\directorio" ) != BOOL_VAL_FALSO )
	{
		printf( "Error caso 7: Se esperaba FALSO para patron [.(\\?*)] en ruta [\\directorio]\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ExpRegSeCumple ( ".(\\?*)", "./directorio/subdirectorio/fichero.txt" ) != BOOL_VAL_FALSO )
	{
		printf( "Error caso 8: Se esperaba FALSO para patron [.(\\?*)] en ruta [./directorio/subdirectorio/fichero.txt]\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestExpRegSeCumple09 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test ExpRegSeCumple 09 (rutas patron [..(\\?*)]):\n" );
	if ( ExpRegSeCumple ( "..(\\?*)", ".." ) != BOOL_VAL_CIERTO )
	{
		printf( "Error caso 1: Se esperaba CIERTO para patron [..(\\?*)] en ruta [..]\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ExpRegSeCumple ( "..(\\?*)", "..\\directorio" ) != BOOL_VAL_CIERTO )
	{
		printf( "Error caso 2: Se esperaba CIERTO para patron [..(\\?*)] en ruta [..\\directorio]\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ExpRegSeCumple ( "..(\\?*)", "..\\directorio\\subdirectorio" ) != BOOL_VAL_CIERTO )
	{
		printf( "Error caso 3: Se esperaba CIERTO para patron [..(\\?*)] en ruta [..\\directorio\\subdirectorio]\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ExpRegSeCumple ( "..(\\?*)", "..\\directorio\\subdirectorio\\fichero.txt" ) != BOOL_VAL_CIERTO )
	{
		printf( "Error caso 4: Se esperaba CIERTO para patron [..(\\?*)] en ruta [..\\directorio\\subdirectorio\\fichero.txt]\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ExpRegSeCumple ( "..(\\?*)", "..\\directorio\\subdirectorio\\.fichero" ) != BOOL_VAL_CIERTO )
	{
		printf( "Error caso 6: Se esperaba CIERTO para patron [..(\\?*)] en ruta [\\directorio\\subdirectorio\\.fichero]\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ExpRegSeCumple ( "..(\\?*)", ".\\directorio" ) != BOOL_VAL_FALSO )
	{
		printf( "Error caso 6: Se esperaba FALSO para patron [..(\\?*)] en ruta [.\\directorio]\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ExpRegSeCumple ( "..(\\?*)", "\\directorio" ) != BOOL_VAL_FALSO )
	{
		printf( "Error caso 7: Se esperaba FALSO para patron [..(\\?*)] en ruta [\\directorio]\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ExpRegSeCumple ( "..(\\?*)", "../directorio/subdirectorio/fichero.txt" ) != BOOL_VAL_FALSO )
	{
		printf( "Error caso 8: Se esperaba FALSO para patron [..(\\?*)] en ruta [../directorio/subdirectorio/fichero.txt]\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

int TestExpresionesRegulares ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test ExpresionesRegulares]%s\n", ANSI_AMARILLO, ANSI_RESETEAR );
	if ( TestExpRegSeCumpleAlInicio01 () != BOOL_VAL_CIERTO )
	{
		printf ( "%sResultado: KO%s\n", ANSI_ROJO, ANSI_RESETEAR );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		printf ( "%sResultado: OK%s\n", ANSI_VERDE, ANSI_RESETEAR );
	}
	if ( TestExpRegSeCumpleAlInicio02 () != BOOL_VAL_CIERTO )
	{
		printf ( "%sResultado: KO%s\n", ANSI_ROJO, ANSI_RESETEAR );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		printf ( "%sResultado: OK%s\n", ANSI_VERDE, ANSI_RESETEAR );
	}
	if ( TestExpRegSeCumpleAlInicio03 () != BOOL_VAL_CIERTO )
	{
		printf ( "%sResultado: KO%s\n", ANSI_ROJO, ANSI_RESETEAR );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		printf ( "%sResultado: OK%s\n", ANSI_VERDE, ANSI_RESETEAR );
	}
	if ( TestExpRegSeCumpleAlInicio04 () != BOOL_VAL_CIERTO )
	{
		printf ( "%sResultado: KO%s\n", ANSI_ROJO, ANSI_RESETEAR );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		printf ( "%sResultado: OK%s\n", ANSI_VERDE, ANSI_RESETEAR );
	}
	if ( TestExpRegSeCumple01 () != BOOL_VAL_CIERTO )
	{
		printf ( "%sResultado: KO%s\n", ANSI_ROJO, ANSI_RESETEAR );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		printf ( "%sResultado: OK%s\n", ANSI_VERDE, ANSI_RESETEAR );
	}
	if ( TestExpRegSeCumple02 () != BOOL_VAL_CIERTO )
	{
		printf ( "%sResultado: KO%s\n", ANSI_ROJO, ANSI_RESETEAR );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		printf ( "%sResultado: OK%s\n", ANSI_VERDE, ANSI_RESETEAR );
	}
	if ( TestExpRegSeCumple03 () != BOOL_VAL_CIERTO )
	{
		printf ( "%sResultado: KO%s\n", ANSI_ROJO, ANSI_RESETEAR );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		printf ( "%sResultado: OK%s\n", ANSI_VERDE, ANSI_RESETEAR );
	}
	if ( TestExpRegSeCumple04 () != BOOL_VAL_CIERTO )
	{
		printf ( "%sResultado: KO%s\n", ANSI_ROJO, ANSI_RESETEAR );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		printf ( "%sResultado: OK%s\n", ANSI_VERDE, ANSI_RESETEAR );
	}
	if ( TestExpRegSeCumple05 () != BOOL_VAL_CIERTO )
	{
		printf ( "%sResultado: KO%s\n", ANSI_ROJO, ANSI_RESETEAR );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		printf ( "%sResultado: OK%s\n", ANSI_VERDE, ANSI_RESETEAR );
	}
	if ( TestExpRegSeCumple06 () != BOOL_VAL_CIERTO )
	{
		printf ( "%sResultado: KO%s\n", ANSI_ROJO, ANSI_RESETEAR );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		printf ( "%sResultado: OK%s\n", ANSI_VERDE, ANSI_RESETEAR );
	}
	if ( TestExpRegSeCumple07 () != BOOL_VAL_CIERTO )
	{
		printf ( "%sResultado: KO%s\n", ANSI_ROJO, ANSI_RESETEAR );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		printf ( "%sResultado: OK%s\n", ANSI_VERDE, ANSI_RESETEAR );
	}
	if ( TestExpRegSeCumple08 () != BOOL_VAL_CIERTO )
	{
		printf ( "%sResultado: KO%s\n", ANSI_ROJO, ANSI_RESETEAR );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		printf ( "%sResultado: OK%s\n", ANSI_VERDE, ANSI_RESETEAR );
	}
	if ( TestExpRegSeCumple09 () != BOOL_VAL_CIERTO )
	{
		printf ( "%sResultado: KO%s\n", ANSI_ROJO, ANSI_RESETEAR );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		printf ( "%sResultado: OK%s\n", ANSI_VERDE, ANSI_RESETEAR );
	}
	printf ( "%s[Fin]%s\n", ANSI_AMARILLO, ANSI_RESETEAR );
	return ( iRes );
}
