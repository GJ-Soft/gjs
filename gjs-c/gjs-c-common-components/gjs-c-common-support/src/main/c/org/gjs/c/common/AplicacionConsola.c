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




// PENDIENTE: ¿Como determinar si es WIN en modo consola o no?
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
		// PENDIENTE: Quizás aquí haya que utilizar conio.h (evitar se puede):
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
		iRes = 1;
	}
	else
	{
		iRes = 1;
	}
	return ( iRes );
}

// NOTA: En modo de depuración 2 no se permite cerrar la consola (es importante).
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
		GetConsoleScreenBufferInfo ( hConsola, &csbiObj );
		iRes = csbiObj.dwSize.X;

#	  else
		// PENDIENTE
		iRes = 0;
#	  endif
	}
	else
	{
		iRes = 0;
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

int AplicConDibujarLinea ( char cCar )
{   
	return ( AplicConDibujarLineaExt ( 80, 1, cCar ) );
}

int AplicConDibujarLineaExt ( int iAncho, int iColIni, char cCar )
{   
	int iCol;
	int iRes;

	if ( ( iAncho > 0 ) && ( iColIni >= 0 ) && ( iColIni + iAncho < 80 ) )
	{
		iCol = 0; 
		while ( iCol < iColIni )
		{
			printf ( " " );
			iCol = iCol + 1;
		}
		while ( iCol < iColIni + iAncho )
		{
			printf ( "%c", cCar ); 
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

int AplicConDibujarRectangulo ( int iAlto, int iAncho, int iColIni )
{   
	int iCol;
	int iFil;
	int iRes;

	if ( ( iAlto > 0 ) && ( iAncho > 0 ) && ( iColIni >= 0 ) && ( iColIni + iAncho < 80 ) )
	{
		iCol = 0; 
		while ( iCol < iColIni )
		{
			printf ( " " );
			iCol = iCol + 1;
		}
		while ( iCol < iColIni + iAncho )
		{
			printf ( "_" ); 
			iCol = iCol + 1;
		}

		iFil = 1;
		while ( iFil < iAlto - 1 )
		{
			printf ( "\n" );
			iCol = 0; 
			while ( iCol < iColIni )
			{
				printf ( " " );
				iCol = iCol + 1;
			}
			printf ( "|" ); 
			iCol = iCol + 1;
			while ( iCol < iColIni + iAncho - 1 )
			{
				printf ( " " ); 
				iCol = iCol + 1;
			}
			printf ( "|" ); 
		
			iFil = iFil + 1;
		}
		printf ( "\n" );

		iCol = 0; 
		while ( iCol < iColIni )
		{
			printf ( " " );
			iCol = iCol + 1;
		}
		while ( iCol < iColIni + iAncho )
		{
			printf ( "_" ); 
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

