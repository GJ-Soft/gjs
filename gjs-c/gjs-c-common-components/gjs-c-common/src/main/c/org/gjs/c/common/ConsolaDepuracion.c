#include "ConsolaDepuracion.h"
#include "AplicacionConsola.h"

#include "CommonConfig.h"








static int	g_iConsolaDepuracionDisponible = 0;
static int	g_iConsolaDepuracionAbierta = 0;



extern int EntEstaEnModoTest ();



int ConDepAbrir ()
{
	int		iRes;

	if ( EntEstaEnModoTest () == 1 )
	{
		if ( g_iConsolaDepuracionDisponible == 0 )
		{
			if ( AplicConEstaAbierta ()  == 0 )
			{
				iRes = AplicConAbrir ();
				if ( iRes == 1 )
				{
					g_iConsolaDepuracionDisponible = 1;
					g_iConsolaDepuracionAbierta = 1;
				}
			}
			else
			{
				g_iConsolaDepuracionDisponible = 1;
				iRes = 1;
			}
		}
		else
		{
			iRes = 1;
		}
	}
	else
	{
		iRes = 1;
	}
	return ( iRes );
}

void ConDepCerrar ()
{
	if ( EntEstaEnModoTest () == 1 )
	{
		if ( g_iConsolaDepuracionDisponible == 1 )
		{
			if ( g_iConsolaDepuracionAbierta == 1 )
			{
				AplicConCerrar ();
			}
			g_iConsolaDepuracionDisponible = 0;
			g_iConsolaDepuracionAbierta = 0;
		}
	}
}

int ConDepEstaAbierta ()
{
	return ( g_iConsolaDepuracionDisponible );
}

void ConDepImprimir ( const char * p_cTexto, ... )
{
	va_list vaArgs;	
	
	if ( EntEstaEnModoTest () == 1 )
	{
		va_start ( vaArgs, p_cTexto );
		vprintf ( p_cTexto, vaArgs );
		va_end ( vaArgs );
		fflush ( stdout );
	}
}

int ConDepEscribir ( const char * p_cTexto, ... )
{
	int			iRes;
	char *		p_cValor;
	int			iAncho;
	va_list		valArgumentos;

	if ( EntEstaEnModoTest () == 1 )
	{
		if ( ( g_iConsolaDepuracionDisponible == 1 ) && ES_VALIDO ( p_cTexto ) )
		{
			iAncho = AplicConAncho ();
			p_cValor = CadCrear ( iAncho );
			if ( ES_VALIDO ( p_cValor ) )
			{
				va_start ( valArgumentos, p_cTexto );
				if ( FrmCadena ( p_cValor, p_cTexto, valArgumentos, iAncho ) == 1 )
				{
					iRes = 1;			
					/* p_cValor ya viene formateado: como formato, un % suyo leeria basura. */
					printf ( "%s", p_cValor );
				}
				else
				{
					iRes = 0;
				}
				va_end ( valArgumentos );
				MemLiberar ( (void **) &p_cValor );
				fflush ( stdout );
			}
			else
			{
				iRes = 0;
			}
		}
		else
		{
			iRes = 0;
		}
	}
	else
	{
		iRes = 1;
	}
	return ( iRes );
}

int ConDepEscribirLinea ( const char * p_cTexto, ... )
{
	int			iRes;
	char *		p_cValor;
	int			iAncho;
	va_list		valArgumentos;

	if ( EntEstaEnModoTest () == 1 )
	{
		if ( g_iConsolaDepuracionDisponible == 1 )
		{
			iAncho = AplicConAncho ();
			p_cValor = CadCrear ( iAncho );
			if ( ES_VALIDO ( p_cValor ) )
			{
				va_start ( valArgumentos, p_cTexto );
				if ( FrmCadena ( p_cValor, p_cTexto, valArgumentos, iAncho ) == 1 )
				{
					iRes = 1;			
					/* p_cValor ya viene formateado: como formato, un % suyo leeria basura. */
					printf ( "%s", p_cValor );
					printf ( "\n" );
				}
				else
				{
					iRes = 0;
				}
				va_end ( valArgumentos );
				MemLiberar ( (void **) &p_cValor );
				fflush ( stdout );
			}
			else
			{
				iRes = 0;
			}
		}
		else
		{
			iRes = 0;
		}
	}
	else
	{
		iRes = 1;
	}
	return ( iRes );
}

void ConDepEsperar ()
{
	if ( EntEstaEnModoTest () == 1 )
	{
		printf( "Presiona <Enter> para continuar..." );
		fflush ( stdout );
		AplicConEsperarRetorno ();
		printf ( "\n" );
	}
}