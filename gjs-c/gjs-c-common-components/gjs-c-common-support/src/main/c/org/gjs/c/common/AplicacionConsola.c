/******************************************************************************/
/*                           AplicacionConsola.cpp                            */
/*----------------------------------------------------------------------------*/
/* Librería:  Aplicacion                                                      */
/* Versión:   3.0.0                                                           */
/* Fecha:     25/03/2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Fichero de código fuente que contiene la implementación de algunas         */
/* rutinas para manejo de la consola.                                         */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/
#include "AplicacionConsola.h"


#include "AplicacionConfig.h"







static int	g_iAplicConsolaDisponible = 1;




int AplicConAbrir ()
{
	int				iRes;
#  if ( !defined ( WIN ) )
	int				iFilDesc;
	struct termios	trmioConsola;
#  endif

	if ( g_iAplicConsolaDisponible == 0 )
	{
#	  if ( defined ( WIN ) )
		AllocConsole ();
#	 else
		iFilDesc = open ( "/dev/tty", O_RDWR );
		tcgetattr ( iFilDesc, &trmioConsola ); 

		dup2 ( iFilDesc, 0 );
		dup2 ( iFilDesc, 1 );
		dup2 ( iFilDesc, 2 );
		close( iFilDesc );
		
		setlinebuf ( stdin );
		setlinebuf ( stdout );
		setbuf ( stderr, NULL );
  
		/* Sobre el descriptor 0, NO sobre iFilDesc: ese ya se cerro unas
		   lineas mas arriba, en cuanto se duplico en 0, 1 y 2. Tal y como
		   estaba, tcsetattr fallaba con EBADF —nadie mira el retorno— y los
		   atributos del terminal no se restauraban nunca. */
		tcsetattr ( 0, TCSANOW, &trmioConsola );
#	 endif
		/* Tras abrir (o reabrir tras un AplicConCerrar) la consola queda
		   disponible; sin esto EstaAbierta/Ancho seguirian viendo 0 y un
		   Cerrar posterior no liberaria la consola. */
		g_iAplicConsolaDisponible = 1;
		iRes = 1;
	}
	else
	{
		iRes = 1;
	}
	return ( iRes );
}

// NOTA: En modo de depuraci�n 2 no se permite cerrar la consola (es importante).
void AplicConCerrar ()
{
#  if ( !defined ( MODO_DEPURACION_2 ) )
	if ( g_iAplicConsolaDisponible == 1 )
	{
#	  if ( defined ( WIN ) )
		FreeConsole ();
#	 else
		fclose ( stdin );
		fclose ( stdout );
		fclose ( stderr );
#	 endif
		g_iAplicConsolaDisponible = 0;
	}
#  endif
}

int AplicConEstaAbierta ()
{
	return ( g_iAplicConsolaDisponible );
}

int AplicConAncho ()
{
	int							iRes;
# if ( defined ( WIN ) )
	HANDLE						hConsola;
	CONSOLE_SCREEN_BUFFER_INFO	csbiObj;
# endif

	if ( g_iAplicConsolaDisponible == 1 )
	{
#	  if ( defined ( WIN ) )
		hConsola = GetStdHandle ( STD_OUTPUT_HANDLE );
		if ( GetConsoleScreenBufferInfo ( hConsola, &csbiObj ) != 0 )
		{
			/* Ancho de la ventana visible (no el del buffer, que puede diferir). */
			iRes = csbiObj.srWindow.Right - csbiObj.srWindow.Left + 1;
		}
		else
		{
			iRes = 0;
		}

#	  else
		struct winsize wsInfo;
		if ( ( isatty ( STDOUT_FILENO ) ) &&
			( ioctl ( STDOUT_FILENO, TIOCGWINSZ, &wsInfo ) == 0 ) &&
			( wsInfo.ws_col > 0 ) )
		{
			iRes = (int) wsInfo.ws_col;
		}
		else
		{
			iRes = 0;   /* sin terminal (p. ej. salida redirigida) */
		}
#	  endif
	}
	else
	{
		iRes = 0;
	}
	if ( iRes <= 0 )
	{
		iRes = CON_ANCHO_DEFECTO;
	}
	return ( iRes );
}

void AplicConLimpiar ()
{
# if ( defined ( WIN ) )
	HANDLE						hConsola;
	COORD						coordPos;
	DWORD						dwCont;
	CONSOLE_SCREEN_BUFFER_INFO	csbiObj;
# endif

	if ( g_iAplicConsolaDisponible == 1 )
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
   para no dejarlo en stdin y que lo recoja la lectura siguiente. Devuelve ese
   primer caracter, o EOF si no habia nada que leer. */
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
	if ( g_iAplicConsolaDisponible == 1 )
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
	while ( ( ( iRes < iMin ) || ( iRes > iMax ) ) && ( iFinal == 0 ) )
	{
		iRes = AplicConLeerNumero ();
		if ( ( iRes < iMin ) || ( iRes > iMax ) )
		{
			/* Sin esto, con la entrada agotada getchar devuelve EOF sin fin y
			   el bucle no salia nunca. */
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

char * AplicConLeerCadena ()
{
	int			iLong;
	char *		p_cRes;
	char *		p_cCadena;

	/* CadCrear ( n ) reserva n + 1 y lo deja a cero, asi que cabe el terminador. */
	p_cCadena = CadCrear ( CON_MAX_TAM_CADENA );
	if ( ES_VALIDO ( p_cCadena ) )
	{
		if ( ES_VALIDO ( fgets ( p_cCadena, CON_MAX_TAM_CADENA + 1, stdin ) ) )
		{
			/* fgets se trae el retorno dentro de la cadena: se quita. */
			iLong = CadLongitud ( p_cCadena );
			if ( ( iLong > 0 ) && ( p_cCadena [ iLong - 1 ] == '\n' ) )
			{
				p_cCadena [ iLong - 1 ] = '\0';
			}
		}
		else
		{
			/* Fin de entrada o error: cadena vacia. */
			p_cCadena [ 0 ] = '\0';
		}
	}
	p_cRes = CadDuplicar ( p_cCadena );
	MemLiberar ( (void **) &p_cCadena );
	return ( p_cRes );
}

void AplicConEsperarRetorno ()
{
    getchar ();
}

/* Los caracteres de dibujo de bordes (_CON_BRD_*) se definen en AplicacionConfig.h. */

static int _AplicConDibujarLineaExt ( int iAncho, int iColIni, const char * p_cCod )
{   
	int iCol;
	int iRes;

	if ( ( iAncho > 0 ) && ( iColIni >= 0 ) && ( iColIni + iAncho <= AplicConAncho () ) )
	{
		iCol = 0; 
		while ( iCol < iColIni )
		{
			printf ( " " );
			iCol = iCol + 1;
		}
		while ( iCol < iColIni + iAncho )
		{
			printf ( "%s", p_cCod ); 
			iCol = iCol + 1;
		}

		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}


int AplicConDibujarLinea ( char cCar )
{   
	return ( AplicConDibujarLineaExt ( AplicConAncho (), 0, cCar ) );
}

int AplicConDibujarLineaDiscontinua ()
{   
	return ( AplicConDibujarLineaDiscontinuaExt ( AplicConAncho (), 0 ) );
}

int AplicConDibujarLineaSimple ()
{   
	return ( AplicConDibujarLineaSimpleExt ( AplicConAncho (), 0 ) );
}

int AplicConDibujarLineaDoble ()
{   
	return ( AplicConDibujarLineaDobleExt ( AplicConAncho (), 0 ) );
}

int AplicConDibujarLineaExt ( int iAncho, int iColIni, char cCar )
{   
	int 	iRes;
	char *	p_cCod;
	
	p_cCod = CadCrearConFormato ( "%c", cCar );
	iRes = _AplicConDibujarLineaExt ( iAncho, iColIni, p_cCod );
	MemLiberarCadena ( &p_cCod );
	return ( iRes );
}

int AplicConDibujarLineaDiscontinuaExt ( int iAncho, int iColIni )
{   
	return ( AplicConDibujarLineaExt ( iAncho, iColIni, '-' ) );
}

int AplicConDibujarLineaSimpleExt ( int iAncho, int iColIni )
{   
	return ( _AplicConDibujarLineaExt ( iAncho, iColIni, _CON_BRD_S_HOR ) );
}

int AplicConDibujarLineaDobleExt ( int iAncho, int iColIni )
{   
	return ( _AplicConDibujarLineaExt ( iAncho, iColIni, _CON_BRD_D_HOR ) );
}


/* Dibuja una caja con las esquinas y lados indicados. iAlto/iAncho incluyen el
   borde; iColIni es la columna de inicio. No imprime salto de linea final (como
   el resto de rutinas de dibujo). Devuelve 1 si dibuja, 0 si los parametros no
   son validos (el minimo es una caja de 2x2). */
static int _AplicConDibujarCaja ( int iAlto, int iAncho, int iColIni,
								  const char * p_cSupIzq, const char * p_cSupDer,
								  const char * p_cInfIzq, const char * p_cInfDer,
								  const char * p_cHor, const char * p_cVer )
{
	int iCol;
	int iFil;
	int iRes;

	if ( ( iAlto > 1 ) && ( iAncho > 1 ) && ( iColIni >= 0 ) && ( iColIni + iAncho <= AplicConAncho () ) )
	{
		/* Linea superior: esquina + horizontales + esquina. */
		for ( iCol = 0; iCol < iColIni; iCol = iCol + 1 )
		{
			printf ( " " );
		}
		printf ( "%s", p_cSupIzq );
		for ( iCol = 0; iCol < iAncho - 2; iCol = iCol + 1 )
		{
			printf ( "%s", p_cHor );
		}
		printf ( "%s", p_cSupDer );

		/* Lineas intermedias: vertical + huecos + vertical. */
		for ( iFil = 1; iFil < iAlto - 1; iFil = iFil + 1 )
		{
			printf ( "\n" );
			for ( iCol = 0; iCol < iColIni; iCol = iCol + 1 )
			{
				printf ( " " );
			}
			printf ( "%s", p_cVer );
			for ( iCol = 0; iCol < iAncho - 2; iCol = iCol + 1 )
			{
				printf ( " " );
			}
			printf ( "%s", p_cVer );
		}

		/* Linea inferior: esquina + horizontales + esquina. */
		printf ( "\n" );
		for ( iCol = 0; iCol < iColIni; iCol = iCol + 1 )
		{
			printf ( " " );
		}
		printf ( "%s", p_cInfIzq );
		for ( iCol = 0; iCol < iAncho - 2; iCol = iCol + 1 )
		{
			printf ( "%s", p_cHor );
		}
		printf ( "%s", p_cInfDer );

		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int AplicConDibujarRectangulo ( int iAlto, int iAncho, int iColIni )
{
	return ( _AplicConDibujarCaja ( iAlto, iAncho, iColIni,
									_CON_BRD_S_SUP_IZQ, _CON_BRD_S_SUP_DER,
									_CON_BRD_S_INF_IZQ, _CON_BRD_S_INF_DER,
									_CON_BRD_S_HOR, _CON_BRD_S_VER ) );
}

int AplicConDibujarRectanguloDoble ( int iAlto, int iAncho, int iColIni )
{
	return ( _AplicConDibujarCaja ( iAlto, iAncho, iColIni,
									_CON_BRD_D_SUP_IZQ, _CON_BRD_D_SUP_DER,
									_CON_BRD_D_INF_IZQ, _CON_BRD_D_INF_DER,
									_CON_BRD_D_HOR, _CON_BRD_D_VER ) );
}

