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




// PENDIENTE: �Como determinar si es WIN en modo consola o no?
//  PENDIENTE: Refinar para el caso GNU/UNIX y completar para el caso VC
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
#	   if ( defined ( VC ) )
		// PENDIENTE: Quiz�s aqu� haya que utilizar conio.h (evitar se puede):
		iFilDesc = _open ( "/dev/tty", O_RDWR );
		_dup2 ( iFilDesc, 0 );
		_dup2 ( iFilDesc, 1 );
		_dup2 ( iFilDesc, 2 );
		close( iFilDesc );
		
		stdin = _fdopen ( 0, "r" );
		stdout = _fdopen ( 1, "w" );
		stderr = _fdopen ( 2, "w" );
  
		_setlinebuf ( stdin );
		_setlinebuf ( stdout );
		_setbuf ( stderr, NULL );
  
		//tcsetattr ( iFilDesc, TCSANOW, &console ); 
#	   else // GNU:
		// PENDIENTE: Verificar que sobra de todo esto:
		iFilDesc = open ( "/dev/tty", O_RDWR );
		tcgetattr ( iFilDesc, &trmioConsola ); 

		dup2 ( iFilDesc, 0 );
		dup2 ( iFilDesc, 1 );
		dup2 ( iFilDesc, 2 );
		close( iFilDesc );
		
		//stdin = fdopen ( 0, "r" );
		//p_fstdout = fdopen ( 1, "w" );
		//p_fstderr = fdopen ( 2, "w" );

		setlinebuf ( stdin );
		setlinebuf ( stdout );
		setbuf ( stderr, NULL );
  
		tcsetattr ( iFilDesc, TCSANOW, &trmioConsola ); 
#	   endif
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

	if ( g_iAplicConsolaDisponible == 1 )
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
	while ( ( iRes < iMin ) || ( iRes > iMax ) )
	{
		iRes = AplicConLeerNumero ();
		if ( ( iRes < iMin ) || ( iRes > iMax ) )
		{
			printf ( "\b" );
		}
	}
	return ( iRes );
}

char * AplicConLeerCadena ()
{
	int			iFinal;
	int			iCar;
# if ( defined ( VC ) )
	char		cValor;
	int			iValor;
# endif
	char *		p_cRes;
	char *		p_cCadena;

	p_cCadena = CadCrear ( CON_MAX_TAM_CADENA );
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
			p_cCadena [ iCar ] = cValor;
			iCar = iCar + 1;
		}
#	  else
		// PENDIENTE:
#	  endif
	}
	p_cRes = CadDuplicar ( p_cCadena );
	MemLiberar ( (void **) &p_cCadena );
	return ( p_cRes );
}

void AplicConEsperarRetorno ()
{
# if ( defined ( VC ) )
	int			iFinal;
	int			iValor;
# endif

# if ( defined ( VC ) )
	iFinal = 0;
	while ( iFinal == 0  )
	{
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
			printf ( "\b" );
		}
	}
# else
    getchar ();
# endif
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

