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

/* La cadena vacia encaja con lo que admite vacio: *, ( x ) y ''. Hasta
   el 2026-10-01 no encajaba con nada, ni siquiera con "*". */
static int TestExpRegSeCumple10 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test ExpRegSeCumple 10 (cadena vacia):\n" );
	if ( ExpRegSeCumple ( "*", "" ) != BOOL_VAL_CIERTO )
	{
		printf( "Error caso 1: Se esperaba CIERTO para patron [*] en []\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ExpRegSeCumple ( "**", "" ) != BOOL_VAL_CIERTO )
	{
		printf( "Error caso 2: Se esperaba CIERTO para patron [**] en []\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ExpRegSeCumple ( "(a)", "" ) != BOOL_VAL_CIERTO )
	{
		printf( "Error caso 3: Se esperaba CIERTO para patron [(a)] en []\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ExpRegSeCumple ( "''", "" ) != BOOL_VAL_CIERTO )
	{
		printf( "Error caso 4: Se esperaba CIERTO para patron [''] en []\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ExpRegSeCumple ( "*(a)", "" ) != BOOL_VAL_CIERTO )
	{
		printf( "Error caso 5: Se esperaba CIERTO para patron [*(a)] en []\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ExpRegSeCumple ( "?", "" ) != BOOL_VAL_FALSO )
	{
		printf( "Error caso 6: Se esperaba FALSO para patron [?] en []\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ExpRegSeCumple ( "a*", "" ) != BOOL_VAL_FALSO )
	{
		printf( "Error caso 7: Se esperaba FALSO para patron [a*] en []\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ExpRegSeCumple ( "?*", "" ) != BOOL_VAL_FALSO )
	{
		printf( "Error caso 8: Se esperaba FALSO para patron [?*] en []\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ExpRegSeCumple ( "a", "" ) != BOOL_VAL_FALSO )
	{
		printf( "Error caso 9: Se esperaba FALSO para patron [a] en []\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

/* ( x ) es cero o mas repeticiones de x. Antes el bucle no avanzaba por la
   cadena y tomaba el 0/1 de ExpRegSeCumpleAlInicio por caracteres
   consumidos: (a) aceptaba "ab", (ab) aceptaba "abba" y (a)b rechazaba
   "aab". (a)a con "aa" necesita la vuelta atras: dejar una a al resto. */
static int TestExpRegSeCumple11 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test ExpRegSeCumple 11 (subpatrones: cero o mas repeticiones):\n" );
	if ( ExpRegSeCumple ( "(a)", "a" ) != BOOL_VAL_CIERTO )
	{
		printf( "Error caso 1: Se esperaba CIERTO para patron [(a)] en [a]\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ExpRegSeCumple ( "(a)", "aaa" ) != BOOL_VAL_CIERTO )
	{
		printf( "Error caso 2: Se esperaba CIERTO para patron [(a)] en [aaa]\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ExpRegSeCumple ( "(a)", "ab" ) != BOOL_VAL_FALSO )
	{
		printf( "Error caso 3: Se esperaba FALSO para patron [(a)] en [ab]\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ExpRegSeCumple ( "(a)", "b" ) != BOOL_VAL_FALSO )
	{
		printf( "Error caso 4: Se esperaba FALSO para patron [(a)] en [b]\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ExpRegSeCumple ( "(ab)", "abab" ) != BOOL_VAL_CIERTO )
	{
		printf( "Error caso 5: Se esperaba CIERTO para patron [(ab)] en [abab]\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ExpRegSeCumple ( "(ab)", "abba" ) != BOOL_VAL_FALSO )
	{
		printf( "Error caso 6: Se esperaba FALSO para patron [(ab)] en [abba]\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ExpRegSeCumple ( "(ab)", "aba" ) != BOOL_VAL_FALSO )
	{
		printf( "Error caso 7: Se esperaba FALSO para patron [(ab)] en [aba]\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ExpRegSeCumple ( "(a)b", "b" ) != BOOL_VAL_CIERTO )
	{
		printf( "Error caso 8: Se esperaba CIERTO para patron [(a)b] en [b]\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ExpRegSeCumple ( "(a)b", "aab" ) != BOOL_VAL_CIERTO )
	{
		printf( "Error caso 9: Se esperaba CIERTO para patron [(a)b] en [aab]\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ExpRegSeCumple ( "(a)a", "aa" ) != BOOL_VAL_CIERTO )
	{
		printf( "Error caso 10: Se esperaba CIERTO para patron [(a)a] en [aa]\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ExpRegSeCumple ( "x(a)", "xaa" ) != BOOL_VAL_CIERTO )
	{
		printf( "Error caso 11: Se esperaba CIERTO para patron [x(a)] en [xaa]\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ExpRegSeCumple ( "x(a)", "xab" ) != BOOL_VAL_FALSO )
	{
		printf( "Error caso 12: Se esperaba FALSO para patron [x(a)] en [xab]\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ExpRegSeCumple ( "x(ab)y", "xababy" ) != BOOL_VAL_CIERTO )
	{
		printf( "Error caso 13: Se esperaba CIERTO para patron [x(ab)y] en [xababy]\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ExpRegSeCumple ( "x(ab)y", "xaby" ) != BOOL_VAL_CIERTO )
	{
		printf( "Error caso 14: Se esperaba CIERTO para patron [x(ab)y] en [xaby]\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ExpRegSeCumple ( "(a)(b)", "aabb" ) != BOOL_VAL_CIERTO )
	{
		printf( "Error caso 15: Se esperaba CIERTO para patron [(a)(b)] en [aabb]\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ExpRegSeCumple ( "(a)(b)", "aba" ) != BOOL_VAL_FALSO )
	{
		printf( "Error caso 16: Se esperaba FALSO para patron [(a)(b)] en [aba]\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

/* Tras un *, el resto se probaba solo contra sufijos no vacios: si el resto
   era ( x ), que admite vacio, ?*(/?*) no encajaba con "tmp". */
static int TestExpRegSeCumple12 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test ExpRegSeCumple 12 (* seguido de algo que admite vacio):\n" );
	if ( ExpRegSeCumple ( "?*(/?*)", "tmp" ) != BOOL_VAL_CIERTO )
	{
		printf( "Error caso 1: Se esperaba CIERTO para patron [?*(/?*)] en [tmp]\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ExpRegSeCumple ( "?*(/?*)", "tmp/a" ) != BOOL_VAL_CIERTO )
	{
		printf( "Error caso 2: Se esperaba CIERTO para patron [?*(/?*)] en [tmp/a]\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ExpRegSeCumple ( "a*(b)", "ax" ) != BOOL_VAL_CIERTO )
	{
		printf( "Error caso 3: Se esperaba CIERTO para patron [a*(b)] en [ax]\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ExpRegSeCumple ( "a*(b)", "axbb" ) != BOOL_VAL_CIERTO )
	{
		printf( "Error caso 4: Se esperaba CIERTO para patron [a*(b)] en [axbb]\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ExpRegSeCumple ( "*(a)", "xyz" ) != BOOL_VAL_CIERTO )
	{
		printf( "Error caso 5: Se esperaba CIERTO para patron [*(a)] en [xyz]\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ExpRegSeCumple ( "(/)?*(/?*)", "/" ) != BOOL_VAL_CIERTO )
	{
		printf( "Error caso 6: Se esperaba CIERTO para patron [(/)?*(/?*)] en [/]\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ExpRegSeCumple ( "(/)?*(/?*)", "/tmp/datos" ) != BOOL_VAL_CIERTO )
	{
		printf( "Error caso 7: Se esperaba CIERTO para patron [(/)?*(/?*)] en [/tmp/datos]\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ExpRegSeCumple ( "(/)?*(/?*)", "" ) != BOOL_VAL_FALSO )
	{
		printf( "Error caso 8: Se esperaba FALSO para patron [(/)?*(/?*)] en []\n" );
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
	if ( TestExpRegSeCumple10 () != BOOL_VAL_CIERTO )
	{
		printf ( "%sResultado: KO%s\n", ANSI_ROJO, ANSI_RESETEAR );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		printf ( "%sResultado: OK%s\n", ANSI_VERDE, ANSI_RESETEAR );
	}
	if ( TestExpRegSeCumple11 () != BOOL_VAL_CIERTO )
	{
		printf ( "%sResultado: KO%s\n", ANSI_ROJO, ANSI_RESETEAR );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		printf ( "%sResultado: OK%s\n", ANSI_VERDE, ANSI_RESETEAR );
	}
	if ( TestExpRegSeCumple12 () != BOOL_VAL_CIERTO )
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
