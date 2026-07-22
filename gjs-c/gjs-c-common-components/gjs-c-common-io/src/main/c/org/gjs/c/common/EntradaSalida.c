#include "EntradaSalida.h"

#include "FicherosConfig.h"


/* 0 = cerrado, 1 = abierto pero redirigido, 2 = abierto y es terminal */
int SisEstadoDescriptor ( int iDescriptor )
{
	int iRes;
	
#if ( defined ( WIN ) )
      intptr_t h = _get_osfhandle ( iDescriptor );
      if ( ( h == -1 ) || ( h == -2 ) )
      {
			iRes = 0;          /* sin descriptor / sin consola */
      }
# if ( defined ( CYGWIN ) )
      else if ( isatty ( iDescriptor ) )
# else
      else if ( _isatty ( iDescriptor ) )
# endif
      {
			iRes = 2;          /* consola */
      }
#else
	if ( fcntl ( iDescriptor, F_GETFD ) == -1 )   /* errno == EBADF */
	{
		iRes = 0;
	}
	else if ( isatty ( iDescriptor ) == 1 )
	{
		iRes = 2;
	}
#endif
	else
	{
		iRes = 1;
	}
    return ( iRes );
}

int SisObtenerDescriptor ( FILE * p_fObj )
{
	int iRes; 
	
	if ( ES_VALIDO ( p_fObj ) )
	{
		iRes = fileno ( p_fObj );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}		


int SisAsincEscribir ( int iDescriptor, const char * p_cText )
{
	int iRes; 
	int iBytes;
	int	iLong;
	
	if ( ( iDescriptor >= 0 ) && ES_VALIDO ( p_cText ) )
	{
		iLong = CadLongitud ( p_cText );
#if ( defined ( WIN ) )
		DWORD dwBytes = 0;
		if ( WriteFile( (HANDLE) _get_osfhandle( iDescriptor ), p_cText, (DWORD) iLong, (LPDWORD) &dwBytes, NULL ) != 0 )
		{
			iBytes = (int) dwBytes;
		}
		else
		{
			iBytes = -1;
		}
#else
		iBytes = write ( iDescriptor, p_cText, iLong );
#endif
		if ( iBytes >= iLong )
		{
			iRes = 1;
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
	return ( iRes );
}		

int SisAsincEscribirConFormato ( int iDescriptor, const char * p_cFormato, ... )
{
	int 		iRes; 
	va_list		valArgumentos;
	
	if ( ES_VALIDO ( p_cFormato ) )
	{
		va_start ( valArgumentos,  p_cFormato );
		iRes = SisAsincEscribirConFormatoExt ( iDescriptor, p_cFormato, valArgumentos );
		va_end ( valArgumentos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}		

int SisAsincEscribirConFormatoExt ( int iDescriptor, const char * p_cFormato, va_list valArgumentos )
{
	int 		iRes; 
	char *		p_cText;
	
	if ( ES_VALIDO ( p_cFormato ) )
	{
		p_cText = CadCrearConFormatoExt ( p_cFormato, valArgumentos );
		if ( ES_VALIDO ( p_cText ) )
		{
			iRes = SisAsincEscribir ( iDescriptor, p_cText );
			MemLiberarCadena ( &p_cText );
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
	return ( iRes );
}		

int SisConAsincEscribir ( const char * p_cText )
{
	return ( SisAsincEscribir ( SisObtenerDescriptor ( stdout ), p_cText ) );
}

int SisConAsincEscribirConFormato ( const char * p_cFormato, ... )
{
	int 		iRes; 
	va_list		valArgumentos;
	
	if ( ES_VALIDO ( p_cFormato ) )
	{
		va_start ( valArgumentos,  p_cFormato );
		iRes = SisConAsincEscribirConFormatoExt ( p_cFormato, valArgumentos );
		va_end ( valArgumentos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SisConAsincEscribirConFormatoExt ( const char * p_cFormato, va_list valArgumentos )
{
	return ( SisAsincEscribirConFormatoExt ( SisObtenerDescriptor ( stdout ), p_cFormato, valArgumentos ) );
}

