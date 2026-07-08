/******************************************************************************/
/*                            SistemaRegistro.c                               */
/*----------------------------------------------------------------------------*/
/* Librería:  Sistema                                                         */
/* Versión:   3.0.0                                                           */
/* Fecha:     25/03/2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Fichero de código fuente que contiene la implementación de la algunas      */
/* rutinas generales de manejo del registro de Windows.                       */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#if ( defined ( WIN ) )


#include "SistemaRegistro.h"
#include "SistemaConfig.h"



static HKEY SisRegClavePrincipal ( int iClavePrinc );


int SisRegExisteClave ( const char * p_cClave )
{
	return ( SisRegExisteClaveExt ( p_cClave, REG_CLV_LOCAL_MACHINE ) );
}

int SisRegCrearClave ( const char * p_cClave )
{
	return ( SisRegCrearClaveExt ( p_cClave, REG_CLV_LOCAL_MACHINE ) );
}

int SisRegEliminarClave ( const char * p_cClave )
{
	return ( SisRegEliminarClaveExt ( p_cClave, REG_CLV_LOCAL_MACHINE ) );
}

int SisRegExisteClaveExt ( const char * p_cClave, int iClavePrinc )
{
	int				iResWin;
	int				iRes;
	HKEY			hkeyPrinc;
    HKEY			hkeyOpen;

	if ( ES_VALIDO ( p_cClave ) )
	{
		hkeyPrinc = SisRegClavePrincipal ( iClavePrinc );
		iResWin = RegOpenKeyEx ( hkeyPrinc, p_cClave, &hkeyOpen );
		if ( iResWin == ERROR_SUCCESS )
		{
			iRes = 1;
			RegCloseKey ( hkeyOpen );
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

int SisRegCrearClaveExt ( const char * p_cClave, int iClavePrinc )
{
	int				iResWin;
	int				iRes;
	HKEY			hkeyPrinc;
    HKEY			hkeyOpen;

	if ( ES_VALIDO ( p_cClave ) )
	{
		hkeyPrinc = SisRegClavePrincipal ( iClavePrinc );
		iResWin = RegCreateKeyEx ( hkeyPrinc, p_cClave, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hkeyOpen, NULL )
		if ( iResWin == ERROR_SUCCESS )
		{
			iRes = 1;
			RegCloseKey ( hkeyOpen );
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

int SisRegEliminarClaveExt ( const char * p_cClave, int iClavePrinc )
{
	int				iResWin;
	int				iRes;
	HKEY			hkeyPrinc;

	if ( ES_VALIDO ( p_cClave ) )
	{
		hkeyPrinc = SisRegClavePrincipal ( iClavePrinc );
		iResWin = RegDeleteKey ( hkeyPrinc, p_cClave );
		if ( iResWin == ERROR_SUCCESS )
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

const char * SisRegObtValorCadena ( const char * p_cClave, const char * p_cValor )
{
	return ( SisRegObtValorCadenaExt ( p_cClave, p_cValor, REG_CLV_LOCAL_MACHINE ) ); 
}

unsigned long SisRegObtValorNumerico ( const char * p_cClave, const char * p_cValor )
{
	return ( SisRegObtValorNumericoExt ( p_cClave, p_cValor, REG_CLV_LOCAL_MACHINE ) ); 
}

const char * SisRegObtValorCadenaExt ( const char * p_cClave, const char * p_cValor, int iClavePrinc )
{
	int				iResWin;
 	HKEY			hkeyPrinc;
	HKEY			hkeyOpen;
	byte *			p_byBuffer;
	unsigned long	ulTamBuffer;
	const char *	p_cRes;
	DWORD			dwTipo;

	if ( ES_VALIDO ( p_cClave ) && ES_VALIDO ( p_cValor ) )
	{
		hkeyPrinc = SisRegClavePrincipal ( iClavePrinc );
		iResWin = RegOpenKeyEx ( hkeyPrinc, p_cClave, 0, KEY_ALL_ACCESS, &hkeyOpen );
		if ( iResWin == ERROR_SUCCESS )
		{
			dwTipo = REG_SZ;
			ulTamBuffer = SIS_MAX_TAM_VALOR_REG + 1;
			p_byBuffer = (byte *) MemReservar ( SIS_MAX_TAM_VALOR_REG + 1 );
			if ( ES_VALIDO ( p_byBuffer ) )
			{
				iResWin = RegQueryValueEx ( hkeyOpen, (LPCSTR) p_cValor, NULL, &dwTipo, p_byBuffer, &ulTamBuffer );
				if ( iResWin == ERROR_SUCCESS )
				{
					p_cRes = CadDuplicar ( (char *) p_byBuffer );
				}
				else
				{
					p_cRes = NULL;
				}
				MemLiberar ( (void **) &p_byBuffer );
			}
			else
			{
				p_cRes = NULL;
			}
			RegCloseKey ( hkeyOpen );
		}
		else
		{
			p_cRes = NULL;
		}
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

unsigned long SisRegObtValorNumericoExt ( const char * p_cClave, const char * p_cValor, int iClavePrinc )
{
	int				iResWin;
    HKEY			hkeyOpen;
	HKEY			hkeyPrinc;
	DWORD			dwBuffer;
	unsigned long	ulTamBuffer;
	unsigned long	ulRes;
	DWORD			dwTipo;

	if ( ES_VALIDO ( p_cClave ) && ES_VALIDO ( p_cValor ) )
	{
		hkeyPrinc = SisRegClavePrincipal ( iClavePrinc );
		iResWin = RegOpenKeyEx ( hkeyPrinc, p_cClave, 0, KEY_ALL_ACCESS, &hkeyOpen );
		if ( iResWin == ERROR_SUCCESS )
		{
			dwTipo = REG_DWORD;
			dwBuffer = 0;
			ulTamBuffer = sizeof ( DWORD );
			iResWin = RegQueryValueEx ( hkeyOpen, (LPCSTR) p_cValor, NULL, &dwTipo, (byte *) &dwBuffer, &ulTamBuffer );
			if ( iResWin == ERROR_SUCCESS )
			{
				ulRes = (unsigned long) dwBuffer;
			}
			else
			{
				ulRes = 0;
			}
		}
		else
		{
			ulRes = 0;
		}
		RegCloseKey ( hkeyOpen );
	}
	else
	{
		ulRes = 0;
	}
	return ( ulRes );
}

int SisRegEstValorCadena ( const char * p_cClave, const char * p_cValor, const char * p_cDato )
{
	return ( SisRegEstValorCadenaExt ( p_cClave, p_cValor, REG_CLV_LOCAL_MACHINE ) ); 
}

int SisRegEstValorNumerico ( const char * p_cClave, const char * p_cValor, unsigned long ulDato )
{
	return ( SisRegEstValorNumericoExt ( p_cClave, p_cValor, REG_CLV_LOCAL_MACHINE ) ); 
}

int SisRegCrearValorCadena ( const char * p_cClave, const char * p_cValor, const char * p_cDato )
{
	return ( SisRegCrearValorCadenaExt ( p_cClave, p_cValor, REG_CLV_LOCAL_MACHINE ) ); 
}

int SisRegCrearValorNumerico ( const char * p_cClave, const char * p_cValor, unsigned long ulDato )
{
	return ( SisRegCrearValorNumericoExt ( p_cClave, p_cValor, REG_CLV_LOCAL_MACHINE ) ); 
}

int SisRegEstValorCadenaExt ( const char * p_cClave, const char * p_cValor, const char * p_cDato, int iClavePrinc )
{
	int				iResWin;
    HKEY			hkeyOpen;
	HKEY			hkeyPrinc;
	byte *			p_byBuffer;
	unsigned long	ulTamBuffer;
	int				iRes;
	DWORD			dwTipo;

	if ( ES_VALIDO ( p_cClave ) && ES_VALIDO ( p_cValor ) )
	{
		hkeyPrinc = SisRegClavePrincipal ( iClavePrinc );
		iResWin = RegOpenKeyEx ( hkeyPrinc, p_cClave, 0, KEY_ALL_ACCESS, &hkeyOpen );
		if ( iResWin == ERROR_SUCCESS )
		{
			if ( ES_VALIDO ( p_cDato ) )
			{
				dwTipo = REG_SZ;
				ulTamBuffer = CadLongitud ( p_cDato ) + 1;
				p_byBuffer = (byte *) MemReservar ( ulTamBuffer );
				if ( ES_VALIDO ( p_byBuffer ) )
				{
					if ( ulTamBuffer > 1 )
					{
						MemCopiar ( p_byBuffer, (void *) p_cDato, ulTamBuffer - 1 );
					}
					iResWin = RegSetValueEx ( hkeyOpen, (LPCSTR) p_cValor, NULL, dwTipo, p_byBuffer, ulTamBuffer );
					if ( iResWin == ERROR_SUCCESS )
					{
						iRes = 1;
					}
					else
					{
						iRes = 0;
					}
					MemLiberar ( (void **) &p_byBuffer );
				}
				else
				{
					iRes = 0;
				}
			}
			else
			{
				iResWin = RegDeleteValue ( hkeyOpen, (LPCSTR) p_cValor );
				if ( iResWin == ERROR_SUCCESS )
				{
					iRes = 1;
				}
				else
				{
					iRes = 0;
				}
			}
			RegCloseKey ( hkeyOpen );
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

int SisRegEstValorNumericoExt ( const char * p_cClave, const char * p_cValor, unsigned long ulDato, int iClavePrinc )
{
	int				iResWin;
    HKEY			hkeyOpen;
	HKEY			hkeyPrinc;
	DWORD			dwBuffer;
	unsigned long	ulTamBuffer;
	int				iRes;
	DWORD			dwTipo;

	if ( ES_VALIDO ( p_cClave ) && ES_VALIDO ( p_cValor ) )
	{
		hkeyPrinc = SisRegClavePrincipal ( iClavePrinc );
		iResWin = RegOpenKey ( hkeyPrinc, p_cClave, &hkeyOpen );
		if ( iResWin == ERROR_SUCCESS )
		{
			dwTipo = REG_DWORD;
			ulTamBuffer = sizeof ( DWORD );
			dwBuffer = (DWORD) ulDato;
			iResWin = RegSetValueEx ( hkeyOpen, (LPCSTR) p_cValor, NULL, dwTipo, (CONST BYTE *) &dwBuffer, ulTamBuffer );
			if ( iResWin == ERROR_SUCCESS )
			{
				iRes = 1;
			}
			else
			{
				iRes = 0;
			}
			RegCloseKey ( hkeyOpen );
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

int SisRegCrearValorCadenaExt ( const char * p_cClave, const char * p_cValor, const char * p_cDato, int iClavePrinc )
{
	int	iRes;

	if ( SisRegCrearClave ( p_cClave, iClavePrinc ) == 1 )
	{
		iRes = SisRegEstValorCadena ( p_cClave, p_cValor, p_cDato, iClavePrinc );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SisRegCrearValorNumericoExt ( const char * p_cClave, const char * p_cValor, unsigned long ulDato, int iClavePrinc )
{
	int	iRes;

	if ( SisRegCrearClave ( p_cClave, iClavePrinc ) == 1 )
	{
		iRes = SisRegEstValorNumerico ( p_cClave, p_cValor, ulDato, iClavePrinc );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

static HKEY SisRegClavePrincipal ( int iClavePrinc )
{
	HKEY hkeyRes;

	if ( iClavePrinc == REG_CLV_CLASSES_ROOT )
	{
		hkeyRes = HKEY_CLASSES_ROOT;
	}
	else if ( iClavePrinc == REG_CLV_CURRENT_CONFIG )
	{
		hkeyRes = HKEY_CURRENT_CONFIG;
	}
	else if ( iClavePrinc == REG_CLV_CURRENT_USER ) 
	{
		hkeyRes = HKEY_CURRENT_USER;
	}
	else if ( iClavePrinc == REG_CLV_LOCAL_MACHINE )
	{
		hkeyRes = HKEY_LOCAL_MACHINE;
	}
	else if ( iClavePrinc == REG_CLV_USERS )
	{
		hkeyRes = HKEY_USERS;
	}
	else
	{
		hkeyRes = HKEY_LOCAL_MACHINE;
	}
	return ( hkeyRes );
}





/* Rutinas generales: */
HKEY SisRegClaveInfoClases ()
{
	return ( HKEY_CLASSES_ROOT );
}


HKEY SisRegClaveInfoConfigActual ()
{
	return ( HKEY_CURRENT_CONFIG );
}


HKEY SisRegClaveInfoUsuarioActual ()
{
	return ( HKEY_CURRENT_USER );
}


HKEY SisRegClaveInfoLocal ()
{
	return ( HKEY_LOCAL_MACHINE );
}


HKEY SisRegClaveInfoUsuarios ()
{
	return ( HKEY_USERS );
}


/*
HKEY SisRegAbrirUsuarioActual ( int iSoloLectura )
{
	HKEY hkeyClave;
	LONG lRet;

	if ( iSoloLectura == 1 )
	{
		lRet = SisRegOpenCurrentUser ( KEY_READ, &hkeyClave );
	}
	else
	{
		lRet = SisRegOpenCurrentUser ( KEY_ALL_ACCESS, &hkeyClave );
	}

	if ( lRet != ERROR_SUCCESS )
	{
		hkeyClave = NULL;
	}

	return ( hkeyClave );
}


HKEY SisRegAbrirClasesUsuarioActual ( int iSoloLectura )
{
	HKEY hkeyClave;
	LONG lRet;

	if ( iSoloLectura == 1 )
	{
		lRet = SisRegOpenUserClassesRoot ( KEY_READ, &hkeyClave );
	}
	else
	{
		lRet = SisRegOpenUserClassesRoot ( KEY_ALL_ACCESS, &hkeyClave );
	}

	if ( lRet != ERROR_SUCCESS )
	{
		hkeyClave = NULL;
	}

	return ( hkeyClave );
}
*/

HKEY SisRegCrear ( HKEY hkeyPadre, const char * p_cClave )
{
	HKEY hkeyClave;
	LONG lRet;
	DWORD dwRet;
	SECURITY_ATTRIBUTES secatrInfo;

	if ( hkeyPadre != NULL )
	{
		hkeyClave = NULL;

		secatrInfo.bInheritHandle = 0;
		secatrInfo.nLength = sizeof ( SECURITY_ATTRIBUTES );
		secatrInfo.lpSecurityDescriptor = NULL;

		lRet = RegCreateKeyEx ( hkeyPadre, p_cClave, 0, NULL,
								REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, 
								&secatrInfo, &hkeyClave, &dwRet );

		if ( dwRet == REG_CREATED_NEW_KEY )
		{
			hkeyClave = NULL;
		}
		else if ( lRet != ERROR_SUCCESS )
		{
			hkeyClave = NULL;
		}
	}
	else
	{
		hkeyClave = NULL;
	}

	return ( hkeyClave );
}


HKEY SisRegAbrir ( HKEY hkeyPadre, const char * p_cClave )
{
	HKEY hkeyClave;
	LONG lRet;

	if ( hkeyPadre != NULL )
	{
		hkeyClave = NULL;
		lRet = RegOpenKeyEx ( hkeyPadre, p_cClave, 0, KEY_ALL_ACCESS, &hkeyClave );
		if ( lRet != ERROR_SUCCESS )
		{
			hkeyClave = NULL;
		}
	}
	else
	{
		hkeyClave = NULL;
	}

	return ( hkeyClave );
}


void SisRegCerrar ( HKEY hkeyClave )
{
	if ( ES_VALIDO ( hkeyClave ) )
	{
		RegCloseKey ( hkeyClave );
	}
}


int SisRegEsClaveValida ( HKEY hkeyClave )
{
	int iRes;

	if ( ES_VALIDO ( hkeyClave ) )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}

	return ( iRes );
}


LONG SisRegNumSubclaves ( HKEY hkeyClave )
{
	DWORD	 dwReservado;           
	DWORD	 dwNumSubclaves;         
	DWORD	 dwMaxTamSubclave;       
	DWORD	 dwMaxTamClases;         
	DWORD	 dwNumValores;           
	DWORD	 dwMaxTamNombreValor;    
	DWORD	 dwMaxTamValor;        
	DWORD	 dwTamDescSeguridad; 
	FILETIME ftimUltEscritura; 
	LONG	 lRet;
	LONG     lRes;

	if ( ES_VALIDO ( hkeyClave ) )
	{
		lRet = RegQueryInfoKey( hkeyClave, NULL, NULL, &dwReservado,             
								&dwNumSubclaves, &dwMaxTamSubclave, &dwMaxTamClases,         
								&dwNumValores, &dwMaxTamNombreValor, &dwMaxTamValor,         
								&dwTamDescSeguridad, &ftimUltEscritura );

		if ( lRet != ERROR_SUCCESS )
		{
			lRes = -1;
		}
		else
		{
			lRes = dwNumSubclaves;
		}
	}
	else
	{
		lRes = -1;
	}

	return ( lRes );
}


int SisRegTieneSubclaves ( HKEY hkeyClave )
{
	DWORD	 dwReservado;            
	DWORD	 dwNumSubclaves;         
	DWORD	 dwMaxTamSubclave;       
	DWORD	 dwMaxTamClases;         
	DWORD	 dwNumValores;           
	DWORD	 dwMaxTamNombreValor;    
	DWORD	 dwMaxTamValor;        
	DWORD	 dwTamDescSeguridad; 
	FILETIME ftimUltEscritura;  
	LONG	 lRet;
	int	 iRes;

	if ( ES_VALIDO ( hkeyClave ) )
	{
		lRet = RegQueryInfoKey( hkeyClave, NULL, NULL, &dwReservado,             
								&dwNumSubclaves, &dwMaxTamSubclave, &dwMaxTamClases,         
								&dwNumValores, &dwMaxTamNombreValor, &dwMaxTamValor,         
								&dwTamDescSeguridad, &ftimUltEscritura );
		if ( lRet != ERROR_SUCCESS )
		{
			iRes = 0;
		}
		else
		{
			if ( dwNumSubclaves > 0 )
			{
				iRes = 1;
			}
			else
			{
				iRes = 0;
			}
		}
	}
	else
	{
		iRes = 0;
	}

	return ( iRes );
}


LONG SisRegNumValores ( HKEY hkeyClave )
{
	DWORD	 dwReservado;            
	DWORD	 dwNumSubclaves;         
	DWORD	 dwMaxTamSubclave;       
	DWORD	 dwMaxTamClases;         
	DWORD	 dwNumValores;           
	DWORD	 dwMaxTamNombreValor;    
	DWORD	 dwMaxTamValor;        
	DWORD	 dwTamDescSeguridad; 
	FILETIME ftimUltEscritura;  
	LONG	 lRet;
	LONG     lRes;

	if ( ES_VALIDO ( hkeyClave ) )
	{
		lRet = RegQueryInfoKey( hkeyClave, NULL, NULL, &dwReservado,             
								&dwNumSubclaves, &dwMaxTamSubclave, &dwMaxTamClases,         
								&dwNumValores, &dwMaxTamNombreValor, &dwMaxTamValor,         
								&dwTamDescSeguridad, &ftimUltEscritura );

		if ( lRet != ERROR_SUCCESS )
		{
			lRes = -1;
		}
		else
		{
			lRes = dwNumValores;
		}
	}
	else
	{
		lRes = -1;
	}

	return ( lRes );
}


int SisRegTieneValores ( HKEY hkeyClave )
{
	DWORD	 dwReservado;            
	DWORD	 dwNumSubclaves;         
	DWORD	 dwMaxTamSubclave;       
	DWORD	 dwMaxTamClases;         
	DWORD	 dwNumValores;           
	DWORD	 dwMaxTamNombreValor;    
	DWORD	 dwMaxTamValor;        
	DWORD	 dwTamDescSeguridad; 
	FILETIME ftimUltEscritura;  
	LONG	 lRet;
	int	 iRes;

	if ( ES_VALIDO ( hkeyClave ) )
	{
		lRet = RegQueryInfoKey( hkeyClave, NULL, NULL, &dwReservado,             
								&dwNumSubclaves, &dwMaxTamSubclave, &dwMaxTamClases,         
								&dwNumValores, &dwMaxTamNombreValor, &dwMaxTamValor,         
								&dwTamDescSeguridad, &ftimUltEscritura );

		if ( lRet != ERROR_SUCCESS )
		{
			iRes = 0;
		}
		else
		{
			if ( dwNumValores > 0 )
			{
				iRes = 1;
			}
			else
			{
				iRes = 0;
			}
		}
	}
	else
	{
		iRes = 0;
	}

	return ( iRes );
}


int SisRegExisteSubclave ( HKEY hkeyClave, const char *p_cSubclave )
{
	HKEY hkeySubclave;
	LONG lRet;
	int iRes;

	if ( ES_VALIDO ( hkeyClave ) )
	{
		hkeySubclave = NULL;
		lRet = RegOpenKeyEx ( hkeyClave, p_cSubclave, 0, KEY_ALL_ACCESS, &hkeySubclave );
		if ( lRet == ERROR_SUCCESS )
		{
			RegCloseKey ( hkeySubclave );
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


int SisRegExisteValor ( HKEY hkeyClave, const char *p_cNomValor )
{
	int  iRes;
	DWORD dwTam;
	DWORD dwValor;
	LONG  lRet;
	DWORD dwTipo;

	if ( ( ES_VALIDO ( hkeyClave ) ) && ( p_cNomValor != NULL ) )
	{
		dwTam = sizeof ( DWORD );
		lRet = RegQueryValueEx ( hkeyClave, p_cNomValor, 0, &dwTipo, 
								 (BYTE*) &dwValor, &dwTam );

		if ( ( lRet == ERROR_SUCCESS ) && ( dwTipo == REG_DWORD ) )
		{
			iRes = 1;
		}
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}

	return ( iRes );
}


int SisRegEliminarSubclave ( HKEY hkeyClave, const char * p_cSubclave )
{
	int iRes;

	if ( ( ES_VALIDO ( hkeyClave ) ) && ( ES_VALIDO ( p_cSubclave ) ) )
	{
		if ( RegDeleteKey ( hkeyClave, p_cSubclave ) == ERROR_SUCCESS )
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


int SisRegEliminarTodasSubclaves ( HKEY hkeyClave )
{
	TCHAR p_cDeposito [ REG_MAX_TAM_CLAVE + 1 ];
	int iRes;
	LONG lRet;
	DWORD dwTamDep;
	DWORD dwIndex;

	if ( ES_VALIDO ( hkeyClave ) )
	{
		iRes = 1;
		dwTamDep = REG_MAX_TAM_CLAVE + 1;
		dwIndex = 0;
		while ( RegEnumKeyEx ( hkeyClave, dwIndex, p_cDeposito, &dwTamDep, NULL, NULL, NULL, NULL ) == ERROR_SUCCESS )
		{
			if ( RegDeleteKey ( hkeyClave, p_cDeposito ) != ERROR_SUCCESS )
			{
				iRes = 0;
				// Avanza para evitar bucle infinito si no se puede borrar
				dwIndex = dwIndex + 1; 
			}
			dwTamDep = REG_MAX_TAM_CLAVE + 1;
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}


int SisRegConsultarClave ( HKEY hkeyClave, const char * p_cValor, unsigned int uiMaxTamValor )
{
	int iRes;
	LONG lRet;
	DWORD dwTam;
	DWORD dwTipo;

	if ( ( ES_VALIDO ( hkeyClave ) ) && ( p_cValor != NULL ) && ( uiMaxTamValor > 0 ) )
	{
		dwTam = uiMaxTamValor;
		lRet = RegQueryValueEx ( hkeyClave, NULL, 0,  &dwTipo, 
								 (BYTE*) p_cValor, &dwTam );

		if ( ( lRet == ERROR_SUCCESS ) && ( dwTipo == REG_SZ ) )
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
		iRes = 1;
	}

	return ( iRes );
}

	
int SisRegConsultarClaveEnt ( HKEY hkeyClave, DWORD * pdwValor )
{
	int iRes;
	LONG lRet;
	DWORD dwTam;
	DWORD dwTipo;

	if ( ( ES_VALIDO ( hkeyClave ) ) && ( pdwValor != NULL ) )
	{
		dwTam = sizeof ( DWORD );
		lRet = RegQueryValueEx ( hkeyClave, NULL, 0, &dwTipo, 
								 (BYTE*) pdwValor, &dwTam );

		if ( ( lRet == ERROR_SUCCESS ) && ( dwTipo == REG_DWORD ) )
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
		iRes = 1;
	}

	return ( iRes );
}

	
int SisRegEstablecerClave ( HKEY hkeyClave, const char * p_cValor )
{
	int iRes;
	LONG lRet;
	DWORD dwTam;

	if ( ES_VALIDO ( hkeyClave ) )
	{
		dwTam = CadLongitud ( p_cValor ) + 1;
		lRet = RegSetValueEx ( hkeyClave, NULL, 0, (ULONG) REG_SZ, (BYTE*) p_cValor, dwTam );

		if ( lRet == ERROR_SUCCESS )
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
		iRes = 1;
	}

	return ( iRes );
}


int SisRegEstablecerClaveEnt ( HKEY hkeyClave, DWORD dwValor )
{
	int iRes;
	LONG lRet;

	if ( ES_VALIDO ( hkeyClave ) )
	{
		lRet = RegSetValueEx ( hkeyClave, NULL, 0, REG_SZ, (BYTE*) &dwValor, sizeof ( DWORD ) );
		if ( lRet == ERROR_SUCCESS )
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
		iRes = 1;
	}

	return ( iRes );
}


int SisRegConsultarValor ( HKEY hkeyClave, const char * p_cNomValor, const char * p_cValor, unsigned int uiMaxTamValor )
{
	int iRes;
	LONG lRet;
	DWORD dwTam;
	DWORD dwTipo;

	if ( ( ES_VALIDO ( hkeyClave ) ) && ( p_cNomValor != NULL ) &&
		 ( p_cValor != NULL ) && ( uiMaxTamValor > 0 ) )
	{
		dwTam = uiMaxTamValor;
		lRet = RegQueryValueEx ( hkeyClave, p_cNomValor, 0, &dwTipo, 
								 (BYTE*) p_cValor, &dwTam );

		if ( ( lRet == ERROR_SUCCESS ) && ( dwTipo == REG_SZ ) )
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
		iRes = 1;
	}

	return ( iRes );
}

	
int SisRegConsultarValorEnt ( HKEY hkeyClave, const char * p_cNomValor, DWORD * pdwValor )
{
	int iRes;
	LONG lRet;
	DWORD dwTam;
	DWORD dwTipo;

	if ( ( ES_VALIDO ( hkeyClave ) ) && ( p_cNomValor != NULL ) && ( pdwValor != NULL ) )
	{
		dwTam = sizeof ( DWORD );
		lRet = RegQueryValueEx ( hkeyClave, p_cNomValor, 0, &dwTipo, 
								 (BYTE*) pdwValor, &dwTam );

		if ( ( lRet == ERROR_SUCCESS ) && ( dwTipo == REG_DWORD ) )
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
		iRes = 1;
	}

	return ( iRes );
}
	
int SisRegEstablecerValor ( HKEY hkeyClave, const char * p_cNomValor, const char * p_cValor )
{
	int iRes;
	LONG lRet;
	DWORD dwTam;

	if ( ( ES_VALIDO ( hkeyClave ) ) && ( p_cNomValor != NULL ) )
	{
		dwTam = CadLongitud ( p_cValor ) + 1;
		lRet = RegSetValueEx ( hkeyClave, p_cNomValor, 0, REG_SZ, (BYTE*) p_cValor, dwTam );

		if ( lRet == ERROR_SUCCESS )
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
		iRes = 1;
	}

	return ( iRes );
}

int SisRegEstablecerValorEnt ( HKEY hkeyClave, const char * p_cNomValor, DWORD dwValor )
{
	int iRes;
	LONG lRet;

	if ( ( ES_VALIDO ( hkeyClave ) ) && ( p_cNomValor != NULL ) )
	{
		lRet = RegSetValueEx ( hkeyClave, p_cNomValor, 0, REG_SZ, (BYTE*) &dwValor, sizeof ( DWORD ) );

		if ( lRet == ERROR_SUCCESS )
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
		iRes = 1;
	}

	return ( iRes );
}

int SisRegEliminarValor ( HKEY hkeyClave, const char * p_cNomValor )
{
	int iRes;

	if ( ( ES_VALIDO ( hkeyClave ) ) && ( p_cNomValor != NULL ) )
	{
		if ( RegDeleteValue ( hkeyClave, p_cNomValor ) == ERROR_SUCCESS )
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

int SisRegEliminarTodosValores ( HKEY hkeyClave )
{
	TCHAR p_cDeposito [ REG_MAX_TAM_CLAVE + 1 ];
	DWORD dwTamDep;
	int iRes;
	LONG lRet;

	if ( ES_VALIDO ( hkeyClave ) )
	{
		iRes = 1;
		dwTamDep = REG_MAX_TAM_CLAVE + 1;
		while ( ( RegEnumValue ( hkeyClave, 0, p_cDeposito, &dwTamDep, NULL, NULL, NULL, NULL ) == ERROR_SUCCESS ) && ( iRes == 1 ) )
		{

			lRet = RegDeleteValue ( hkeyClave, p_cDeposito );
			if ( lRet != ERROR_SUCCESS )
			{
				iRes = 0;
			}
			dwTamDep = 256;
		}
	}
	else
	{
		iRes = 0;
	}

	return ( iRes );
}

int SisRegEliminarContenido ( HKEY hkeyClave )
{
	int iRes;
	LONG lRet;

	if ( ES_VALIDO ( hkeyClave ) )
	{
		lRet = RegSetValueEx ( hkeyClave, NULL, 0, REG_SZ, 
							  NULL, 0 );

		if ( lRet == ERROR_SUCCESS )
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
		iRes = 1;
	}

	return ( iRes );
}

int SisRegImportarFichero ( HKEY hkeyPadre, const char * p_cClave, const char * p_cFichero )
{
	int iRes;

	if ( ( hkeyPadre != NULL ) && ( p_cClave != NULL ) && ( p_cFichero != NULL ) )
	{

		if ( RegLoadKey ( hkeyPadre, p_cClave, p_cFichero ) != ERROR_SUCCESS )
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

int SisRegExportarFichero ( HKEY hkeyClave, const char * p_cFichero )
{
	int iRes;

	if ( ( ES_VALIDO ( hkeyClave ) ) && ( p_cFichero != NULL ) )
	{

		if ( RegSaveKey ( hkeyClave, p_cFichero, NULL ) == ERROR_SUCCESS )
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


/* Rutinas de alto nivel para módulos DLL: */
int SisRegRegistrarModulo ( const GUID guidModulo, const char * p_cFicModulo, const char * p_cVersion )
{
	int	iRes;
	WCHAR *	pswzGuid;
	LONG	lRet;
	HKEY	hkeyRaiz;
	HKEY	hkeyLibs;
	HKEY	hkeyModulo;
	HKEY    hkeyVersion;
	HKEY	hkeyRevision;
	HKEY	hkeyFichero;
	HKEY	hkeyFicAyuda;
	HKEY	hkeyAtributos;
	CHAR	p_cGuid [ REG_MAX_TAM_CLAVE + 1 ];

	
	iRes = 1;
		
	hkeyRaiz = NULL;
	hkeyLibs = NULL;
	hkeyModulo = NULL;
	hkeyVersion = NULL;
	hkeyRevision = NULL;
	hkeyFichero = NULL;
	hkeyFicAyuda = NULL;
	hkeyAtributos = NULL;

	ZeroMemory ( p_cGuid, REG_MAX_TAM_CLAVE + 1 );

	// Guid
	StringFromCLSID ( guidModulo, &pswzGuid );
		
	WideCharToMultiByte ( CP_ACP, 0, pswzGuid, -1, p_cGuid, 
						  REG_MAX_TAM_CLAVE, NULL, NULL);

	hkeyRaiz = HKEY_CLASSES_ROOT;

	lRet = RegCreateKeyEx ( hkeyRaiz, REG_SEC_LIBRERIAS, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hkeyLibs, NULL );

	if ( lRet == ERROR_SUCCESS )
	{
		lRet = RegCreateKeyEx ( hkeyLibs, p_cGuid, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hkeyModulo, NULL )

		if ( lRet == ERROR_SUCCESS )
		{	
			lRet = RegCreateKeyEx ( hkeyModulo, p_cVersion, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hkeyVersion, NULL );

			if ( lRet == ERROR_SUCCESS )
			{
				RegSetValueEx ( hkeyVersion, NULL, 0, REG_SZ, 
								(BYTE*) p_cFicModulo, CadLongitud ( p_cFicModulo ) + 1 );

				lRet = RegCreateKeyEx ( hkeyVersion, REG_LIB_REVISION_DEF, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hkeyRevision, NULL );

				if ( lRet == ERROR_SUCCESS )
				{

					lRet = RegCreateKeyEx ( hkeyRevision, REG_CLV_LIB_FICHERO, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hkeyFichero, NULL );

					if ( lRet == ERROR_SUCCESS )
					{
						RegSetValueEx ( hkeyFichero, NULL, 0, REG_SZ, 
										(BYTE*) p_cFicModulo, 
										CadLongitud ( p_cFicModulo ) + 1 );

						RegCloseKey ( hkeyFichero );
					}
					else
					{
						iRes = 0;
					}

					lRet = RegCreateKeyEx ( hkeyRevision, REG_CLV_LIB_ATRIBUTOS, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hkeyAtributos, NULL );

					if ( lRet == ERROR_SUCCESS )
					{
						RegSetValueEx ( hkeyAtributos, NULL, 0, REG_SZ, 
										(BYTE*) REG_VAL_NUM_DEF, 
										CadLongitud ( REG_VAL_NUM_DEF ) + 1 );

						RegCloseKey ( hkeyAtributos );
					}				
					else
					{
						iRes = 0;
					}

					lRet = RegCreateKeyEx ( hkeyRevision, REG_CLV_LIB_FIC_AYUDA, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hkeyFicAyuda, NULL );

					if ( lRet == ERROR_SUCCESS )
					{
						RegSetValueEx ( hkeyFicAyuda, NULL, 0, REG_SZ, 
										(BYTE*) REG_VAL_DEF, 
										CadLongitud ( REG_VAL_DEF ) + 1 );

						RegCloseKey ( hkeyFicAyuda );
					}				
					else
					{
						iRes = 0;
					}

					RegCloseKey ( hkeyRevision );
				}
				else
				{
					iRes = 0;
				}

				RegCloseKey ( hkeyVersion );
			}
			else
			{
				iRes = 0;
			}

			RegCloseKey ( hkeyModulo );

		}
		else
		{
			iRes = 0;
		}

		RegCloseKey ( hkeyLibs );
	}

	CoTaskMemFree ( pswzGuid );

	return ( iRes );
}


int SisRegRegistrarGUID ( const GUID guidCodigo, const char *p_cNombre, const char *p_cDescripcion,
							   const GUID guidModulo, const char *p_cFicModulo, const char * p_cVersion )
{
	int	iRes;
	WCHAR *	pswzGuid;
	LONG	lRet;
	HKEY	hkeyRaiz;
	HKEY	hkeyClases;
	HKEY	hkeyClase;
	HKEY	hkeyCatImp;
	HKEY	hkeyServidor;
	HKEY	hkeyProgId;
	HKEY	hkeyIndProgId;
	HKEY	hkeyVerCls;
	HKEY	hkeyLibreria;
	HKEY	hkeyClsId;
	HKEY	hkeyProgIdAct;
 
	CHAR	p_cGuid		 [ REG_MAX_TAM_CLAVE + 1 ];
	CHAR	p_cGuidMod	 [ REG_MAX_TAM_CLAVE + 1 ];
	CHAR	p_cProgId	 [ REG_MAX_TAM_VALOR + 1 ];
	CHAR	p_cProgIdAct	 [ REG_MAX_TAM_VALOR + 1 ];
	
	iRes = 1;
	
	hkeyRaiz = NULL;
	hkeyClases = NULL;
	hkeyClase = NULL;
	hkeyCatImp = NULL;
	hkeyServidor = NULL;
	hkeyProgId = NULL;
	hkeyIndProgId = NULL;
	hkeyVerCls = NULL;
	hkeyLibreria = NULL;
	hkeyClsId = NULL;
	hkeyProgIdAct = NULL;		

	ZeroMemory ( p_cGuid, REG_MAX_TAM_CLAVE + 1 );
	ZeroMemory ( p_cGuidMod, REG_MAX_TAM_CLAVE + 1 );
	ZeroMemory ( p_cProgId, REG_MAX_TAM_VALOR + 1 );
	ZeroMemory ( p_cProgIdAct, REG_MAX_TAM_VALOR + 1 );

	StringFromCLSID ( guidCodigo, &pswzGuid );
	
	WideCharToMultiByte ( CP_ACP, 0, pswzGuid, -1, p_cGuid, 
						  REG_MAX_TAM_CLAVE, NULL, NULL);

	StringFromCLSID ( guidModulo, &pswzGuid );
	
	WideCharToMultiByte ( CP_ACP, 0, pswzGuid, -1, p_cGuidMod, 
						  REG_MAX_TAM_CLAVE, NULL, NULL);

	sprintf ( p_cProgId, REG_PROG_ID_FORMATO, 
			  p_cFicModulo, 
			  p_cNombre );

	sprintf ( p_cProgIdAct, REG_PROG_ID_ACT_FORMATO, 
			  p_cFicModulo, 
			  p_cNombre,
			  REG_CLS_VERSION_DEF );

	hkeyRaiz = HKEY_CLASSES_ROOT;
	lRet = RegCreateKeyEx ( hkeyRaiz, REG_SEC_CLASES, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hkeyClases, NULL );

	if ( lRet == ERROR_SUCCESS )
	{

		lRet = RegCreateKeyEx ( hkeyClases, p_cGuid, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hkeyClase, NULL );

		if ( lRet == ERROR_SUCCESS )
		{	
			RegSetValueEx ( hkeyClase, NULL, 0, REG_SZ, 
							(BYTE*) p_cDescripcion, 
							CadLongitud ( p_cDescripcion ) + 1 );

			lRet = RegCreateKeyEx ( hkeyClase, REG_CLV_CLS_CAT_IMP, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hkeyCatImp, NULL );

			if ( lRet == ERROR_SUCCESS )
			{								
				RegSetValueEx ( hkeyCatImp, NULL, 0, REG_SZ, 
								(BYTE*) REG_VAL_DEF, 
								CadLongitud ( REG_VAL_DEF ) + 1 );
				
				RegCloseKey ( hkeyCatImp );
			}				
			else
			{
				iRes = 0;
			}

			lRet = RegCreateKeyEx ( hkeyClase, REG_CLV_CLS_SERVIDOR, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hkeyServidor, NULL );

			if ( lRet == ERROR_SUCCESS )
			{
				RegSetValueEx ( hkeyServidor, NULL, 0, REG_SZ, 
								(BYTE*) p_cFicModulo, 
								CadLongitud ( p_cFicModulo ) + 1 );
				
				RegCloseKey ( hkeyServidor );
			}				
			else
			{
				iRes = 0;
			}

			lRet = RegCreateKeyEx ( hkeyClase, REG_CLV_CLS_PROG_ID, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hkeyProgId, NULL );

			if ( lRet == ERROR_SUCCESS )
			{
				RegSetValueEx ( hkeyProgId, NULL, 0, REG_SZ, 
								(BYTE*) p_cProgIdAct, 
								CadLongitud ( p_cProgIdAct ) + 1 );
				
				RegCloseKey ( hkeyProgId );
			}				
			else
			{
				iRes = 0;
			}


			lRet = RegCreateKeyEx ( hkeyClase, REG_CLV_CLS_IND_PROG_ID, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hkeyProgId, NULL );

			if ( lRet == ERROR_SUCCESS )
			{
				RegSetValueEx ( hkeyIndProgId, NULL, 0, REG_SZ, 
								(BYTE*) p_cProgId, 
								CadLongitud ( p_cProgId ) + 1 );
				
				RegCloseKey ( hkeyIndProgId );
			}				
			else
			{
				iRes = 0;
			}

			lRet = RegCreateKeyEx ( hkeyClase, REG_CLV_CLS_LIBRERIA, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hkeyLibreria, NULL );

			if ( lRet == ERROR_SUCCESS )
			{
				RegSetValueEx ( hkeyLibreria, NULL, 0, REG_SZ, 
								(BYTE*) p_cGuidMod, 
								CadLongitud ( p_cGuidMod ) + 1 );

				RegCloseKey ( hkeyLibreria );
			}				
			else
			{
				iRes = 0;
			}

			lRet = RegCreateKeyEx ( hkeyClase, REG_CLV_CLS_VERSION, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hkeyVerCls, NULL );

			if ( lRet == ERROR_SUCCESS )
			{
				RegSetValueEx ( hkeyVerCls, NULL, 0, REG_SZ, 
								(BYTE*) p_cVersion, 
								CadLongitud ( p_cVersion ) + 1 );

				RegCloseKey ( hkeyVerCls );
			}				
			else
			{
				iRes = 0;
			}
			RegCloseKey ( hkeyClase );

			lRet = RegCreateKeyEx ( hkeyRaiz, p_cProgId, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hkeyClase, NULL );
			if ( lRet == ERROR_SUCCESS )
			{	
				RegSetValueEx ( hkeyClase, NULL, 0, REG_SZ, 
								(BYTE*) p_cDescripcion, 
								CadLongitud ( p_cDescripcion ) + 1 );

				lRet = RegCreateKeyEx ( hkeyClase, REG_CLV_CLS_ID, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hkeyClsId, NULL );

				if ( lRet == ERROR_SUCCESS )
				{								
					RegSetValueEx ( hkeyClsId, NULL, 0, REG_SZ, 
									(BYTE*) p_cGuid, 
									CadLongitud ( p_cGuid ) + 1 );
				}				
				else
				{
					iRes = 0;
				}

				lRet = RegCreateKeyEx ( hkeyClase, REG_CLV_VERSION_ACT, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hkeyProgIdAct, NULL );

				if ( lRet == ERROR_SUCCESS )
				{
					RegSetValueEx ( hkeyProgIdAct, NULL, 0, REG_SZ, 
									(BYTE*) p_cProgIdAct, 
									CadLongitud ( p_cProgIdAct ) + 1 );
								
					RegCloseKey ( hkeyProgIdAct );
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

			lRet = RegCreateKeyEx ( hkeyRaiz, p_cProgIdAct, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hkeyClase, NULL );

			if ( lRet == ERROR_SUCCESS )
			{	
				RegSetValueEx ( hkeyClase, NULL, 0, REG_SZ, 
								(BYTE*) p_cDescripcion, 
								CadLongitud ( p_cDescripcion ) + 1 );

				lRet = RegCreateKeyEx ( hkeyClase, REG_CLV_CLS_ID, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hkeyClsId, NULL );

				if ( lRet == ERROR_SUCCESS )
				{								
					RegSetValueEx ( hkeyClsId, NULL, 0, REG_SZ, 
									(BYTE*) p_cGuid, 
									CadLongitud ( p_cGuid ) + 1 );
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
			iRes = 0;
		}

	}
	else
	{
		iRes = 0;
	}
	CoTaskMemFree ( pswzGuid );
	return ( iRes );
}



void SisRegDesregistrarModulo ( const GUID guidModulo, const char * p_cVersion )
{
	WCHAR *	pswzGuid;
	LONG	lRet;
	HKEY	hkeyRaiz;
	HKEY	hkeyLibs;
	HKEY	hkeyModulo;
	HKEY    hkeyVersion;
	HKEY	hkeyRevision;
	CHAR	p_cGuid [ REG_MAX_TAM_CLAVE + 1 ];

	hkeyRaiz = NULL;
	hkeyLibs = NULL;
	hkeyModulo = NULL;
	hkeyVersion = NULL;
	hkeyRevision = NULL;

	ZeroMemory ( p_cGuid, REG_MAX_TAM_CLAVE + 1 );

	StringFromCLSID ( guidModulo, &pswzGuid );
	
	WideCharToMultiByte ( CP_ACP, 0, pswzGuid, -1, p_cGuid, 
						  REG_MAX_TAM_CLAVE, NULL, NULL);

	hkeyRaiz = HKEY_CLASSES_ROOT;
	lRet = RegOpenKeyEx ( hkeyRaiz, REG_SEC_LIBRERIAS, 0, KEY_WRITE, &hkeyLibs );

	if ( lRet == ERROR_SUCCESS )
	{
		lRet = RegOpenKeyEx ( hkeyLibs, p_cGuid, 0, KEY_WRITE, &hkeyModulo );

		if ( lRet == ERROR_SUCCESS )
		{	
			lRet = RegOpenKeyEx ( hkeyModulo, p_cVersion, 0, KEY_WRITE, &hkeyVersion );

			if ( lRet == ERROR_SUCCESS )
			{
				lRet = RegOpenKeyEx ( hkeyVersion, REG_LIB_REVISION_DEF, 
									  0, KEY_WRITE, &hkeyRevision );

				if ( lRet == ERROR_SUCCESS )
				{

					RegDeleteKey ( hkeyRevision, REG_CLV_LIB_FICHERO );
					RegDeleteKey ( hkeyRevision, REG_CLV_LIB_ATRIBUTOS );
					RegDeleteKey ( hkeyRevision, REG_CLV_LIB_FIC_AYUDA ); 
					RegCloseKey ( hkeyRevision );
				}

				RegDeleteKey ( hkeyVersion, REG_LIB_REVISION_DEF ); 
				RegCloseKey ( hkeyVersion );
			}

			RegDeleteKey ( hkeyModulo, p_cVersion );
			RegCloseKey ( hkeyModulo );
		}

		RegDeleteKey ( hkeyLibs, p_cGuid );
		RegCloseKey ( hkeyLibs );
	}

	CoTaskMemFree ( pswzGuid );
}


void SisRegDesregistrarGUID ( const GUID guidCodigo, const char *p_cNombre )
{
	WCHAR *	pswzGuid;
	LONG	lRet;
	HKEY	hkeyRaiz;
	HKEY	hkeyClases;
	HKEY	hkeyClase;
	CHAR	p_cGuid		 [ REG_MAX_TAM_CLAVE + 1 ];
	CHAR	p_cProgId	 [ REG_MAX_TAM_VALOR + 1 ];
	CHAR	p_cProgIdAct [ REG_MAX_TAM_VALOR + 1 ];

	hkeyRaiz = NULL;
	hkeyClases = NULL;
	hkeyClase = NULL;

	ZeroMemory ( p_cGuid, REG_MAX_TAM_CLAVE + 1 );
	ZeroMemory ( p_cProgId, REG_MAX_TAM_VALOR + 1 );
	ZeroMemory ( p_cProgIdAct, REG_MAX_TAM_VALOR + 1 );

	StringFromCLSID ( guidCodigo, &pswzGuid );
	
	WideCharToMultiByte ( CP_ACP, 0, pswzGuid, -1, p_cGuid, 
						  REG_MAX_TAM_CLAVE, NULL, NULL);

	sprintf ( p_cProgId, REG_PROG_ID_FORMATO, 
			  p_cNombre, 
			  p_cNombre );

	sprintf ( p_cProgIdAct, REG_PROG_ID_ACT_FORMATO, 
			  p_cNombre, 
			  p_cNombre,
			  REG_CLS_VERSION_DEF );

	hkeyRaiz = HKEY_CLASSES_ROOT;
	lRet = RegOpenKeyEx ( hkeyRaiz, REG_SEC_CLASES, 0, KEY_WRITE,
						  &hkeyClases );

	if ( lRet == ERROR_SUCCESS )
	{
		lRet = RegOpenKeyEx ( hkeyClases, p_cGuid, 0, KEY_WRITE, &hkeyClase );
		if ( lRet == ERROR_SUCCESS )
		{
			RegDeleteKey ( hkeyClase, REG_CLV_CLS_CAT_IMP );
			RegDeleteKey ( hkeyClase, REG_CLV_CLS_SERVIDOR );
			RegDeleteKey ( hkeyClase, REG_CLV_CLS_PROG_ID );
			RegDeleteKey ( hkeyClase, REG_CLV_CLS_LIBRERIA );
			RegDeleteKey ( hkeyClase, REG_CLV_CLS_VERSION ); 
			RegCloseKey ( hkeyClase );
		}

		RegDeleteKey ( hkeyClases, p_cGuid ); 
		RegCloseKey ( hkeyClases );

		lRet = RegOpenKeyEx ( hkeyRaiz, p_cProgId, 0, KEY_WRITE, &hkeyClase );
		if ( lRet == ERROR_SUCCESS )
		{	
			RegDeleteKey ( hkeyClase, REG_CLV_CLS_ID );
			RegDeleteKey ( hkeyClase, REG_CLV_VERSION_ACT );
			RegCloseKey ( hkeyClase );
		}
		RegDeleteKey ( hkeyRaiz, p_cProgId );

		lRet = RegOpenKeyEx ( hkeyRaiz, p_cProgIdAct, 0, KEY_WRITE, &hkeyClase );
		if ( lRet == ERROR_SUCCESS )
		{	
			RegDeleteKey ( hkeyClase, REG_CLV_CLS_ID );
			RegCloseKey ( hkeyClase );
		}

		RegDeleteKey ( hkeyRaiz, p_cProgId );
	}

	CoTaskMemFree ( pswzGuid );
}

int SisRegEstaRegistradoModulo ( const GUID guidModulo )
{
	int iRes;
	WCHAR *	pswzGuid;
	LONG	lRet;
	HKEY	hkeyRaiz;
	HKEY	hkeyLibs;
	HKEY	hkeyModulo;
	CHAR	p_cGuid [ REG_MAX_TAM_CLAVE + 1 ];

	iRes = 0;

	hkeyRaiz = NULL;
	hkeyLibs = NULL;
	hkeyModulo = NULL;

	ZeroMemory ( p_cGuid, REG_MAX_TAM_CLAVE + 1 );

	StringFromCLSID ( guidModulo, &pswzGuid );
	
	WideCharToMultiByte ( CP_ACP, 0, pswzGuid, -1, p_cGuid, 
						  REG_MAX_TAM_CLAVE, NULL, NULL);

	hkeyRaiz = HKEY_CLASSES_ROOT;
	lRet = RegOpenKeyEx ( hkeyRaiz, REG_SEC_LIBRERIAS, 0, KEY_WRITE, &hkeyLibs );

	if ( lRet == ERROR_SUCCESS )
	{
		lRet = RegOpenKeyEx ( hkeyLibs, p_cGuid, 0, KEY_WRITE, &hkeyModulo );

		if ( lRet == ERROR_SUCCESS )
		{	
			iRes = 1;
			RegCloseKey ( hkeyModulo );
		}
		RegCloseKey ( hkeyLibs );
	}

	CoTaskMemFree ( pswzGuid );

	return ( iRes );
}


int EstaRegistradoGUID ( const GUID guidCodigo, const char *p_cNombre )
{
	int	iRes;
	WCHAR *	pswzGuid;
	LONG	lRet;
	HKEY	hkeyRaiz;
	HKEY	hkeyClases;
	HKEY	hkeyClase;
	CHAR	p_cGuid		 [ REG_MAX_TAM_CLAVE + 1 ];
	CHAR	p_cProgId	 [ REG_MAX_TAM_VALOR + 1 ];
	CHAR	p_cProgIdAct	 [ REG_MAX_TAM_VALOR + 1 ];

	iRes = 0;
	hkeyRaiz = NULL;
	hkeyClases = NULL;
	hkeyClase = NULL;
	
	ZeroMemory ( p_cGuid, REG_MAX_TAM_CLAVE + 1 );
	ZeroMemory ( p_cProgId, REG_MAX_TAM_VALOR + 1 );
	ZeroMemory ( p_cProgIdAct, REG_MAX_TAM_VALOR + 1 );

	StringFromCLSID ( guidCodigo, &pswzGuid );
	
	WideCharToMultiByte ( CP_ACP, 0, pswzGuid, -1, p_cGuid, 
						  REG_MAX_TAM_CLAVE, NULL, NULL);

	sprintf ( p_cProgId, REG_PROG_ID_FORMATO, 
			  p_cNombre, 
			  p_cNombre );

	sprintf ( p_cProgIdAct, REG_PROG_ID_ACT_FORMATO, 
			  p_cNombre, 
			  p_cNombre,
			  REG_CLS_VERSION_DEF );

	hkeyRaiz = HKEY_CLASSES_ROOT;
	lRet = RegOpenKeyEx ( hkeyRaiz, REG_SEC_CLASES, 0, KEY_WRITE,
						  &hkeyClases );

	if ( lRet == ERROR_SUCCESS )
	{
		lRet = RegOpenKeyEx ( hkeyClase, p_cGuid, 0, KEY_WRITE, &hkeyClase );

		if ( lRet == ERROR_SUCCESS )
		{
			RegCloseKey ( hkeyClase );
			lRet = RegOpenKeyEx ( hkeyRaiz, p_cProgId, 0, KEY_WRITE, &hkeyClase );

			if ( lRet == ERROR_SUCCESS )
			{	
				RegCloseKey ( hkeyClase );
				lRet = RegOpenKeyEx ( hkeyRaiz, p_cProgIdAct, 0, KEY_WRITE, &hkeyClase );

				if ( lRet == ERROR_SUCCESS )
				{	
					iRes = 1;
					RegCloseKey ( hkeyClase );
				}
			}
		}

		RegCloseKey ( hkeyClases );
	}

	CoTaskMemFree ( pswzGuid );

	return ( iRes );
}


#endif

