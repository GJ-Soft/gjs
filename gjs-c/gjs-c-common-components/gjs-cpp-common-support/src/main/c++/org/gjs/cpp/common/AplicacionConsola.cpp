/******************************************************************************/
/*                           AplicacionConsola.cpp                            */
/*----------------------------------------------------------------------------*/
/* Libreria:  Aplicacion                                                      */
/* Version:   3.0.0                                                           */
/* Fecha:     25/03/2008                                                      */
/* Autor:     Gines Jimenez Sanchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripcion:                                                               */
/* Fichero de codigo fuente que contiene la implementacion de algunas         */
/* rutinas para manejo de la consola.                                         */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/
#include "AplicacionConsola.h"


#include "CommonSupportConfig.h"



using namespace std;

namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {




static bool	g_bAplicConsolaDisponible = false;




// PENDIENTE: Como determinar si es WIN en modo consola o no?
//  PENDIENTE: Refinar para el caso GNU/UNIX y completar para el caso VC
bool AplicConAbrir ()
{
#  if ( !defined ( WIN ) )
	int				iFilDesc;
	struct termios	trmioConsola;
#  endif

	if ( !g_bAplicConsolaDisponible )
	{
#	  if ( defined ( WIN ) )
		AllocConsole ();
#	 else
#	   if ( defined ( VC ) )
		iFilDesc = _open ( "/dev/tty", O_RDWR );
		_dup2 ( iFilDesc, 0 );
		_dup2 ( iFilDesc, 1 );
		_dup2 ( iFilDesc, 2 );

		stdin = _fdopen ( 0, "r" );
		stdout = _fdopen ( 1, "w" );
		stderr = _fdopen ( 2, "w" );

		_setlinebuf ( stdin );
		_setlinebuf ( stdout );
		_setbuf ( stderr, NULL );
#	   else // GNU:
		iFilDesc = open ( "/dev/tty", O_RDWR );
		tcgetattr ( iFilDesc, &trmioConsola );

		dup2 ( iFilDesc, 0 );
		dup2 ( iFilDesc, 1 );
		dup2 ( iFilDesc, 2 );

		setvbuf ( stdin, NULL, _IOLBF, 0 );
		setvbuf ( stdout, NULL, _IOLBF, 0 );
		setbuf ( stderr, NULL );

		tcsetattr ( iFilDesc, TCSANOW, &trmioConsola );
#	   endif
#	 endif
		g_bAplicConsolaDisponible = true;
	}
	return ( g_bAplicConsolaDisponible );
}

// NOTA: En modo de depuracion 2 no se permite cerrar la consola (es importante).
void AplicConCerrar ()
{
#  if ( !defined ( MODO_DEPURACION_2 ) )
	if ( g_bAplicConsolaDisponible )
	{
#	  if ( defined ( WIN ) )
		FreeConsole ();
#	 else
		fclose ( stdin );
		fclose ( stdout );
		fclose ( stderr );
#	 endif
		g_bAplicConsolaDisponible = false;
	}
#  endif
}

bool AplicConEstaAbierta ()
{
	return ( g_bAplicConsolaDisponible );
}

int AplicConAncho ()
{
	int	iRes = 0;

	if ( g_bAplicConsolaDisponible )
	{
#	  if ( defined ( WIN ) )
		HANDLE						hConsola = GetStdHandle ( STD_OUTPUT_HANDLE );
		CONSOLE_SCREEN_BUFFER_INFO	csbiObj;
		// Se usa la ventana visible ( no el buffer ) y se comprueba el retorno.
		if ( GetConsoleScreenBufferInfo ( hConsola, &csbiObj ) )
		{
			iRes = csbiObj.srWindow.Right - csbiObj.srWindow.Left + 1;
		}
#	  else
		struct winsize	wsObj;
		if ( isatty ( STDOUT_FILENO ) && ( ioctl ( STDOUT_FILENO, TIOCGWINSZ, &wsObj ) == 0 ) )
		{
			iRes = (int) wsObj.ws_col;
		}
#	  endif
	}
	return ( iRes );
}

// Ancho "efectivo": el real de la consola, o CON_ANCHO_DEFECTO si no hay terminal
// ( p.ej. con la salida redirigida en el build de tests ).
static int _AplicConAnchoEfectivo ()
{
	int iAncho = AplicConAncho ();
	return ( ( iAncho > 0 ) ? iAncho : CON_ANCHO_DEFECTO );
}

void AplicConLimpiar ()
{
# if ( defined ( WIN ) )
	HANDLE						hConsola;
	COORD						coordPos;
	DWORD						dwCont;
	CONSOLE_SCREEN_BUFFER_INFO	csbiObj;
# endif

	if ( g_bAplicConsolaDisponible )
	{
#	  if ( defined ( WIN ) )
		hConsola = GetStdHandle ( STD_OUTPUT_HANDLE );
		coordPos.X = 0;
		coordPos.Y = 0;
		dwCont = 0;
		GetConsoleScreenBufferInfo ( hConsola, &csbiObj );
		FillConsoleOutputCharacter ( hConsola, ' ', csbiObj.dwSize.X * csbiObj.dwSize.Y, coordPos, &dwCont );
		SetConsoleCursorPosition ( hConsola, coordPos );
#	  else
		printf ( "\e[2J" );
#	  endif
	}
}

int AplicConLeerNumero ()
{
# if ( defined ( VC ) )
	int		iValor;
# else
	char	cValor;
# endif
	int		iRes;

	if ( g_bAplicConsolaDisponible )
	{
#	  if ( defined ( VC ) )
		iRes = -1;
		while ( iRes == -1 )
		{
			while ( kbhit () == 0 )
			{
			}
			iValor = getche ();
			if ( iValor == 0 )
			{
				iValor = getche ();
			}
			else if ( ( iValor >= ((int) '0') ) && ( iValor <= ((int) '9') ) )
			{
				iRes = iValor - ((int) '0');
			}
		}
#	  else
#	   if ( defined ( UNICODE ) )
		cValor = getwchar ();
#	   else
		cValor = getchar ();
#	   endif
		if ( ( cValor >= '0' ) && ( cValor <= '9' ) )
		{
			iRes = ((int) cValor) - ((int) '0');
		}
		else
		{
			iRes = -1;
		}
#	  endif
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int AplicConLeerNumeroEntre ( int iMin, int iMax )
{
	int iRes;

	iRes = -1;
	while ( ( iRes < iMin ) && ( iRes > iMax ) )
	{
		iRes = AplicConLeerNumero ();
		if ( ( iRes < iMin ) && ( iRes > iMax ) )
		{
			printf ( "\b" );
		}
	}
	return ( iRes );
}

string * AplicConLeerCadena ()
{
	int			iFinal;
	int			iCar;
# if ( defined ( VC ) )
	char		cValor;
	int			iValor;
# endif
	vector<char> buffer = vector<char> ( CON_MAX_TAM_CADENA );
	iCar = 0;
	iFinal = 0;
	while ( ( iFinal == 0 ) && ( iCar < CON_MAX_TAM_CADENA ) )
	{
#	  if ( defined ( VC ) )
		while ( kbhit () == 0 )
		{
		}
		iValor = getche ();
		if ( ( iValor == 13 ) || ( iValor == 0 ) )
		{
			iFinal = 1;
		}
		else if ( iValor == 8 )
		{
			if ( iCar > 0 )
			{
				iCar = iCar - 1;
			}
		}
		else
		{
			cValor = (char) iValor;
			buffer [ iCar ] = cValor;
			iCar = iCar + 1;
		}
#	  else
		// PENDIENTE:
		iFinal = 1;
#	  endif
	}
	return ( new string ( buffer.data() ) );
}

void AplicConEsperarRetorno ()
{
	int			iFinal;
# if ( defined ( VC ) )
	int			iValor;
# endif

	iFinal = 0;
	while ( iFinal == 0  )
	{
#	  if ( defined ( VC ) )
		while ( kbhit () == 0 )
		{
		}
		iValor = getche ();
		if ( iValor == 13 )
		{
			iFinal = 1;
		}
		else
		{
			cout << "\b";
		}
#	  else
		// PENDIENTE:
		iFinal = 1;
#	  endif
	}
}


// Dibuja una linea de ancho completo con una cadena ( admite caracteres de dibujo
// multi-byte, que cuentan como una columna ).
static bool _AplicConDibujarLineaCadena ( const char * p_cCar )
{
	bool bRes = false;

	if ( g_bAplicConsolaDisponible )
	{
		int iAncho = _AplicConAnchoEfectivo ();
		for ( int i = 0; i < iAncho; i = i + 1 )
		{
			cout << p_cCar;
		}
		bRes = true;
	}
	return ( bRes );
}

// Dibuja una caja con los caracteres de borde indicados ( minimo 2x2 ).
static bool _AplicConDibujarCaja ( int iAlto, int iAncho, int iColIni,
		const char * p_cSupIzq, const char * p_cSupDer,
		const char * p_cInfIzq, const char * p_cInfDer,
		const char * p_cHor, const char * p_cVer )
{
	int iCol;
	int iFil;
	bool bRes = false;

	if ( ( iAlto > 1 ) && ( iAncho > 1 ) && ( iColIni >= 0 ) &&
		 ( iColIni + iAncho <= _AplicConAnchoEfectivo () ) )
	{
		// Linea superior.
		iCol = 0;
		while ( iCol < iColIni ) { cout << " "; iCol = iCol + 1; }
		cout << p_cSupIzq;
		iCol = iColIni + 1;
		while ( iCol < iColIni + iAncho - 1 ) { cout << p_cHor; iCol = iCol + 1; }
		cout << p_cSupDer << endl;

		// Lineas intermedias.
		iFil = 1;
		while ( iFil < iAlto - 1 )
		{
			iCol = 0;
			while ( iCol < iColIni ) { cout << " "; iCol = iCol + 1; }
			cout << p_cVer;
			iCol = iColIni + 1;
			while ( iCol < iColIni + iAncho - 1 ) { cout << " "; iCol = iCol + 1; }
			cout << p_cVer << endl;
			iFil = iFil + 1;
		}

		// Linea inferior.
		iCol = 0;
		while ( iCol < iColIni ) { cout << " "; iCol = iCol + 1; }
		cout << p_cInfIzq;
		iCol = iColIni + 1;
		while ( iCol < iColIni + iAncho - 1 ) { cout << p_cHor; iCol = iCol + 1; }
		cout << p_cInfDer;

		bRes = true;
	}
	return ( bRes );
}

bool AplicConDibujarLinea ( char cCar )
{
	// Linea de ancho completo ( se corrigio el off-by-one: antes 80,1 -> 81 no dibujaba ).
	return ( AplicConDibujarLineaExt ( _AplicConAnchoEfectivo (), 0, cCar ) );
}

bool AplicConDibujarLineaExt ( int iAncho, int iColIni, char cCar )
{
	int iCol;
	bool bRes = false;

	if ( ( iAncho > 0 ) && ( iColIni >= 0 ) && ( iColIni + iAncho <= _AplicConAnchoEfectivo () ) )
	{
		iCol = 0;
		while ( iCol < iColIni )
		{
			cout << " ";
			iCol = iCol + 1;
		}
		while ( iCol < iColIni + iAncho )
		{
			cout << cCar;
			iCol = iCol + 1;
		}
		bRes = true;
	}
	return ( bRes );
}

bool AplicConDibujarLineaSimple ()
{
	return ( _AplicConDibujarLineaCadena ( _CON_BRD_S_HOR ) );
}

bool AplicConDibujarLineaDoble ()
{
	return ( _AplicConDibujarLineaCadena ( _CON_BRD_D_HOR ) );
}

bool AplicConDibujarRectangulo ( int iAlto, int iAncho, int iColIni )
{
	return ( _AplicConDibujarCaja ( iAlto, iAncho, iColIni,
		_CON_BRD_S_SUP_IZQ, _CON_BRD_S_SUP_DER, _CON_BRD_S_INF_IZQ, _CON_BRD_S_INF_DER,
		_CON_BRD_S_HOR, _CON_BRD_S_VER ) );
}

bool AplicConDibujarRectanguloDoble ( int iAlto, int iAncho, int iColIni )
{
	return ( _AplicConDibujarCaja ( iAlto, iAncho, iColIni,
		_CON_BRD_D_SUP_IZQ, _CON_BRD_D_SUP_DER, _CON_BRD_D_INF_IZQ, _CON_BRD_D_INF_DER,
		_CON_BRD_D_HOR, _CON_BRD_D_VER ) );
}


 			}
		}
	}
}
