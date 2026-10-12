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
		g_bAplicConsolaDisponible = true;
#	 else
		/* Sin terminal ( un servicio, una tuberia, la integracion continua ) open
		   devuelve -1, y se seguia adelante: tcgetattr dejaba la termios sin
		   rellenar, los dup2 fallaban, tcsetattr escribia esa basura y la consola
		   se daba por disponible. */
		iFilDesc = open ( "/dev/tty", O_RDWR );
		if ( iFilDesc >= 0 )
		{
			tcgetattr ( iFilDesc, &trmioConsola );

			dup2 ( iFilDesc, 0 );
			dup2 ( iFilDesc, 1 );
			dup2 ( iFilDesc, 2 );
			/* El descriptor de open no se cerraba nunca ( la version C si lo
			   hacia ). Si estaba cerrado alguno de los estandar, open devuelve
			   justo ese numero: entonces ya es uno de los de la consola y no se
			   cierra. */
			if ( iFilDesc > 2 )
			{
				close ( iFilDesc );
			}

			setvbuf ( stdin, NULL, _IOLBF, 0 );
			setvbuf ( stdout, NULL, _IOLBF, 0 );
			setbuf ( stderr, NULL );

			/* Sobre el 0: iFilDesc ya puede estar cerrado. */
			tcsetattr ( 0, TCSANOW, &trmioConsola );
			g_bAplicConsolaDisponible = true;
		}
#	 endif
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
		printf ( "\x1b[2J" );
#	  endif
	}
}

/* Lee el primer caracter de la linea y consume el resto, incluido el retorno,
   para no dejarlo en la entrada y que lo recoja la lectura siguiente. Devuelve
   ese primer caracter, o EOF si no habia nada que leer. */
static int _AplicConLeerLineaPrimerCar ()
{
	int		iPrimero;
	int		iCar;

#  if ( defined ( UNICODE ) )
	iPrimero = getwchar ();
#  else
	iPrimero = getchar ();
#  endif
	iCar = iPrimero;
	while ( ( iCar != '\n' ) && ( iCar != EOF ) )
	{
#	  if ( defined ( UNICODE ) )
		iCar = getwchar ();
#	  else
		iCar = getchar ();
#	  endif
	}
	return ( iPrimero );
}


int AplicConLeerNumero ()
{
	int		iPrimero;
	int		iRes;

	iRes = -1;
	if ( g_bAplicConsolaDisponible )
	{
		iPrimero = _AplicConLeerLineaPrimerCar ();
		if ( ( iPrimero >= ((int) '0') ) && ( iPrimero <= ((int) '9') ) )
		{
			iRes = iPrimero - ((int) '0');
		}
	}
	return ( iRes );
}

int AplicConLeerNumeroEntre ( int iMin, int iMax )
{
	int iRes;
	int iFinal;

	iRes = -1;
	iFinal = 0;
	// El corte era ( iRes < iMin ) && ( iRes > iMax ), que no puede cumplirse
	// nunca: el bucle no se ejecutaba y la funcion devolvia -1 siempre. La
	// version C ya tenia el || correcto.
	while ( ( ( iRes < iMin ) || ( iRes > iMax ) ) && ( iFinal == 0 ) )
	{
		iRes = AplicConLeerNumero ();
		if ( ( iRes < iMin ) || ( iRes > iMax ) )
		{
			// Sin esto, con la entrada agotada getchar devuelve EOF sin fin y
			// el bucle no saldria nunca.
			if ( feof ( stdin ) != 0 )
			{
				iFinal = 1;
			}
			else
			{
				printf ( "\b" );
			}
		}
	}
	return ( iRes );
}

string * AplicConLeerCadena ()
{
	string		sLinea;

	if ( !getline ( cin, sLinea ) )
	{
		// Fin de entrada o error: cadena vacia.
		sLinea.clear ();
	}
	if ( sLinea.length () > (size_t) CON_MAX_TAM_CADENA )
	{
		sLinea = sLinea.substr ( 0, CON_MAX_TAM_CADENA );
	}
	return ( new string ( sLinea ) );
}

void AplicConEsperarRetorno ()
{
	cin.get ();
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
