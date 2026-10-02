/******************************************************************************/
/*                            SistemaRegistro.cpp                             */
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


#include "CommonSystemConfig.h"

#include "SistemaRegistro.h"

using namespace std;


namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {


static HKEY SisRegClavePrincipal ( int iClavePrinc );



bool SisRegExisteClave ( const string & sClave, int iClavePrinc )
{
	bool	bRes;
	int		iResWin;
	HKEY	hkeyPrinc;
	HKEY	hkeyOpen;

	if ( ! sClave.empty () )
	{
		hkeyPrinc = SisRegClavePrincipal ( iClavePrinc );
		iResWin = RegOpenKey ( hkeyPrinc, sClave.c_str (), &hkeyOpen );
		if ( iResWin == ERROR_SUCCESS )
		{
			bRes = true;
			RegCloseKey ( hkeyOpen );
		}
		else
		{
			bRes = false;
		}
	}
	else
	{
		bRes = false;
	}
	return ( bRes );
}

bool SisRegCrearClave ( const string & sClave, int iClavePrinc )
{
	bool	bRes;
	int		iResWin;
	HKEY	hkeyPrinc;
	HKEY	hkeyOpen;

	if ( ! sClave.empty () )
	{
		hkeyPrinc = SisRegClavePrincipal ( iClavePrinc );
		iResWin = RegCreateKey ( hkeyPrinc, sClave.c_str (), &hkeyOpen );
		if ( iResWin == ERROR_SUCCESS )
		{
			bRes = true;
			RegCloseKey ( hkeyOpen );
		}
		else
		{
			bRes = false;
		}
	}
	else
	{
		bRes = false;
	}
	return ( bRes );
}

bool SisRegEliminarClave ( const string & sClave, int iClavePrinc )
{
	bool	bRes;
	int		iResWin;
	HKEY	hkeyPrinc;

	if ( ! sClave.empty () )
	{
		hkeyPrinc = SisRegClavePrincipal ( iClavePrinc );
		iResWin = RegDeleteKey ( hkeyPrinc, sClave.c_str () );
		bRes = ( iResWin == ERROR_SUCCESS );
	}
	else
	{
		bRes = false;
	}
	return ( bRes );
}

/* Cadena vacia si no se encontro el valor. La version C reservaba un buffer con
   MemReservar y lo duplicaba con CadDuplicar, dejando al llamante la carga de
   liberarlo; aqui el buffer es el propio string, que se dimensiona antes de la
   llamada y se recorta despues con lo que diga Windows. */
string SisRegObtValorCadena ( const string & sClave, const string & sValor, int iClavePrinc )
{
	string			sRes ( "" );
	int				iResWin;
	HKEY			hkeyPrinc;
	HKEY			hkeyOpen;
	unsigned long	ulTamBuffer;
	DWORD			dwTipo;

	if ( ( ! sClave.empty () ) && ( ! sValor.empty () ) )
	{
		hkeyPrinc = SisRegClavePrincipal ( iClavePrinc );
		iResWin = RegOpenKey ( hkeyPrinc, sClave.c_str (), &hkeyOpen );
		if ( iResWin == ERROR_SUCCESS )
		{
			string sBuffer ( SIS_MAX_TAM_VALOR_REG + 1, 0 );

			dwTipo = REG_SZ;
			ulTamBuffer = (unsigned long) sBuffer.size ();
			iResWin = RegQueryValueEx ( hkeyOpen, sValor.c_str (), NULL, &dwTipo,
										(LPBYTE) sBuffer.data (), &ulTamBuffer );
			if ( iResWin == ERROR_SUCCESS )
			{
				/* ulTamBuffer vuelve con los bytes escritos, terminador incluido
				   si el valor lo llevaba. Se recorta por el primer cero, que es lo
				   que hacia el CadDuplicar de antes. */
				sBuffer.resize ( ulTamBuffer );
				sRes = sBuffer.c_str ();
			}
			RegCloseKey ( hkeyOpen );
		}
	}
	return ( sRes );
}

unsigned long SisRegObtValorNumerico ( const string & sClave, const string & sValor, int iClavePrinc )
{
	unsigned long	ulRes = 0;
	int				iResWin;
	HKEY			hkeyPrinc;
	HKEY			hkeyOpen;
	DWORD			dwBuffer;
	unsigned long	ulTamBuffer;
	DWORD			dwTipo;

	if ( ( ! sClave.empty () ) && ( ! sValor.empty () ) )
	{
		hkeyPrinc = SisRegClavePrincipal ( iClavePrinc );
		iResWin = RegOpenKey ( hkeyPrinc, sClave.c_str (), &hkeyOpen );
		if ( iResWin == ERROR_SUCCESS )
		{
			dwTipo = REG_DWORD;
			dwBuffer = 0;
			ulTamBuffer = sizeof ( DWORD );
			iResWin = RegQueryValueEx ( hkeyOpen, sValor.c_str (), NULL, &dwTipo,
										(LPBYTE) &dwBuffer, &ulTamBuffer );
			if ( iResWin == ERROR_SUCCESS )
			{
				ulRes = (unsigned long) dwBuffer;
			}
			/* El RegCloseKey estaba FUERA de este if, asi que cuando RegOpenKey
			   fallaba se cerraba un HKEY sin inicializar. */
			RegCloseKey ( hkeyOpen );
		}
	}
	return ( ulRes );
}

/* La version C admitia un puntero nulo en el dato para borrar el valor. Con
   std::string eso ya no se puede expresar, y tampoco hace falta: para borrar
   esta SisRegEliminarValor. Una cadena vacia es ahora un valor vacio, que es un
   REG_SZ perfectamente legitimo. */
bool SisRegEstValorCadena ( const string & sClave, const string & sValor, const string & sDato, int iClavePrinc )
{
	bool	bRes = false;
	int		iResWin;
	HKEY	hkeyPrinc;
	HKEY	hkeyOpen;

	if ( ( ! sClave.empty () ) && ( ! sValor.empty () ) )
	{
		hkeyPrinc = SisRegClavePrincipal ( iClavePrinc );
		iResWin = RegOpenKey ( hkeyPrinc, sClave.c_str (), &hkeyOpen );
		if ( iResWin == ERROR_SUCCESS )
		{
			/* El buffer intermedio de MemReservar / MemCopiar sobra: c_str () ya
			   da una zona contigua y terminada en cero. */
			iResWin = RegSetValueEx ( hkeyOpen, sValor.c_str (), 0, REG_SZ,
									  (const BYTE *) sDato.c_str (),
									  (DWORD) ( sDato.size () + 1 ) );
			bRes = ( iResWin == ERROR_SUCCESS );
			RegCloseKey ( hkeyOpen );
		}
	}
	return ( bRes );
}

bool SisRegEstValorNumerico ( const string & sClave, const string & sValor, unsigned long ulDato, int iClavePrinc )
{
	bool	bRes = false;
	int		iResWin;
	HKEY	hkeyPrinc;
	HKEY	hkeyOpen;
	DWORD	dwBuffer;

	if ( ( ! sClave.empty () ) && ( ! sValor.empty () ) )
	{
		hkeyPrinc = SisRegClavePrincipal ( iClavePrinc );
		iResWin = RegOpenKey ( hkeyPrinc, sClave.c_str (), &hkeyOpen );
		if ( iResWin == ERROR_SUCCESS )
		{
			dwBuffer = (DWORD) ulDato;
			iResWin = RegSetValueEx ( hkeyOpen, sValor.c_str (), 0, REG_DWORD,
									  (const BYTE *) &dwBuffer, sizeof ( DWORD ) );
			bRes = ( iResWin == ERROR_SUCCESS );
			RegCloseKey ( hkeyOpen );
		}
	}
	return ( bRes );
}

bool SisRegCrearValorCadena ( const string & sClave, const string & sValor, const string & sDato, int iClavePrinc )
{
	bool bRes = false;

	if ( SisRegCrearClave ( sClave, iClavePrinc ) )
	{
		bRes = SisRegEstValorCadena ( sClave, sValor, sDato, iClavePrinc );
	}
	return ( bRes );
}

bool SisRegCrearValorNumerico ( const string & sClave, const string & sValor, unsigned long ulDato, int iClavePrinc )
{
	bool bRes = false;

	if ( SisRegCrearClave ( sClave, iClavePrinc ) )
	{
		bRes = SisRegEstValorNumerico ( sClave, sValor, ulDato, iClavePrinc );
	}
	return ( bRes );
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


/* SisRegAbrirUsuarioActual y SisRegAbrirClasesUsuarioActual estaban aqui
   comentadas desde el origen, porque llaman a SisRegOpenCurrentUser y
   SisRegOpenUserClassesRoot, que no existen en ninguna parte. Se quedan fuera,
   y por eso tampoco se declaran en la cabecera. */


HKEY SisRegCrear ( HKEY hkeyPadre, const string & sClave )
{
	HKEY				hkeyClave = NULL;
	LONG				lRet;
	DWORD				dwRet;
	SECURITY_ATTRIBUTES	secatrInfo;

	if ( hkeyPadre != NULL )
	{
		secatrInfo.bInheritHandle = 0;
		secatrInfo.nLength = sizeof ( SECURITY_ATTRIBUTES );
		secatrInfo.lpSecurityDescriptor = NULL;

		lRet = RegCreateKeyEx ( hkeyPadre, sClave.c_str (), 0, NULL,
								REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS,
								&secatrInfo, &hkeyClave, &dwRet );

		/* Se conserva el criterio del origen: si la clave no existia se
		   devuelve NULL. Lo que si se arregla es que antes se perdia el HKEY
		   recien creado, que quedaba abierto para siempre. */
		if ( ( lRet == ERROR_SUCCESS ) && ( dwRet == REG_CREATED_NEW_KEY ) )
		{
			RegCloseKey ( hkeyClave );
			hkeyClave = NULL;
		}
		else if ( lRet != ERROR_SUCCESS )
		{
			hkeyClave = NULL;
		}
	}
	return ( hkeyClave );
}

HKEY SisRegAbrir ( HKEY hkeyPadre, const string & sClave, REGSAM samAcceso )
{
	HKEY	hkeyClave = NULL;
	LONG	lRet;

	if ( hkeyPadre != NULL )
	{
		/* samAcceso, que por defecto es KEY_READ. Estaba clavado a KEY_ALL_ACCESS,
		   y eso sobre HKEY_LOCAL_MACHINE devuelve ERROR_ACCESS_DENIED salvo que el
		   proceso sea administrador: comprobado, con KEY_READ la misma clave abre
		   sin problema. La funcion era inutil para leer. */
		lRet = RegOpenKeyEx ( hkeyPadre, sClave.c_str (), 0, samAcceso, &hkeyClave );
		if ( lRet != ERROR_SUCCESS )
		{
			hkeyClave = NULL;
		}
	}
	return ( hkeyClave );
}

void SisRegCerrar ( HKEY hkeyClave )
{
	if ( hkeyClave != NULL )
	{
		RegCloseKey ( hkeyClave );
	}
}

bool SisRegEsClaveValida ( HKEY hkeyClave )
{
	return ( hkeyClave != NULL );
}


/* Las cuatro consultas de abajo repetian la misma llamada a RegQueryInfoKey con
   sus diez parametros y sus diez variables locales. Aqui se pide una vez y se
   devuelve lo unico que miraban: cuantas subclaves y cuantos valores hay. */
static bool _SisRegInfoClave ( HKEY hkeyClave, DWORD & dwNumSubclaves, DWORD & dwNumValores )
{
	bool		bRes = false;
	DWORD		dwReservado;
	DWORD		dwMaxTamSubclave;
	DWORD		dwMaxTamClases;
	DWORD		dwMaxTamNombreValor;
	DWORD		dwMaxTamValor;
	DWORD		dwTamDescSeguridad;
	FILETIME	ftimUltEscritura;

	dwNumSubclaves = 0;
	dwNumValores = 0;
	if ( hkeyClave != NULL )
	{
		bRes = ( RegQueryInfoKey ( hkeyClave, NULL, NULL, &dwReservado,
								   &dwNumSubclaves, &dwMaxTamSubclave, &dwMaxTamClases,
								   &dwNumValores, &dwMaxTamNombreValor, &dwMaxTamValor,
								   &dwTamDescSeguridad, &ftimUltEscritura ) == ERROR_SUCCESS );
	}
	return ( bRes );
}

long SisRegNumSubclaves ( HKEY hkeyClave )
{
	long	lRes = -1;
	DWORD	dwNumSubclaves;
	DWORD	dwNumValores;

	if ( _SisRegInfoClave ( hkeyClave, dwNumSubclaves, dwNumValores ) )
	{
		lRes = (long) dwNumSubclaves;
	}
	return ( lRes );
}

bool SisRegTieneSubclaves ( HKEY hkeyClave )
{
	DWORD	dwNumSubclaves;
	DWORD	dwNumValores;

	return ( _SisRegInfoClave ( hkeyClave, dwNumSubclaves, dwNumValores ) &&
			 ( dwNumSubclaves > 0 ) );
}

long SisRegNumValores ( HKEY hkeyClave )
{
	long	lRes = -1;
	DWORD	dwNumSubclaves;
	DWORD	dwNumValores;

	if ( _SisRegInfoClave ( hkeyClave, dwNumSubclaves, dwNumValores ) )
	{
		lRes = (long) dwNumValores;
	}
	return ( lRes );
}

bool SisRegTieneValores ( HKEY hkeyClave )
{
	DWORD	dwNumSubclaves;
	DWORD	dwNumValores;

	return ( _SisRegInfoClave ( hkeyClave, dwNumSubclaves, dwNumValores ) &&
			 ( dwNumValores > 0 ) );
}

bool SisRegExisteSubclave ( HKEY hkeyClave, const string & sSubclave )
{
	bool	bRes = false;
	HKEY	hkeySubclave;
	LONG	lRet;

	if ( hkeyClave != NULL )
	{
		/* Habia aqui un 'hkeyClave = NULL;' justo despues de comprobar que NO
		   era nula, que dejaba el RegOpenKeyEx abriendo desde una clave nula:
		   la funcion contestaba que no existe ninguna subclave. */
		lRet = RegOpenKeyEx ( hkeyClave, sSubclave.c_str (), 0, KEY_ALL_ACCESS, &hkeySubclave );
		if ( lRet == ERROR_SUCCESS )
		{
			RegCloseKey ( hkeySubclave );
			bRes = true;
		}
	}
	return ( bRes );
}

bool SisRegExisteValor ( HKEY hkeyClave, const string & sNomValor )
{
	bool	bRes = false;
	DWORD	dwTam;
	DWORD	dwTipo;
	LONG	lRet;

	if ( ( hkeyClave != NULL ) && ( ! sNomValor.empty () ) )
	{
		/* Dos arreglos. Habia un 'iRes = 1;' suelto detras del if que lo pisaba
		   todo: la funcion decia que si a cualquier nombre. Y solo daba por
		   existente el valor si era REG_DWORD, con lo que un REG_SZ contaba como
		   inexistente. Aqui basta con que la consulta salga bien, sea del tipo
		   que sea; el tamano se pide a NULL, que es como se pregunta sin leer. */
		dwTam = 0;
		lRet = RegQueryValueEx ( hkeyClave, sNomValor.c_str (), 0, &dwTipo, NULL, &dwTam );
		bRes = ( lRet == ERROR_SUCCESS );
	}
	return ( bRes );
}

bool SisRegEliminarSubclave ( HKEY hkeyClave, const string & sSubclave )
{
	bool bRes = false;

	if ( ( hkeyClave != NULL ) && ( ! sSubclave.empty () ) )
	{
		bRes = ( RegDeleteKey ( hkeyClave, sSubclave.c_str () ) == ERROR_SUCCESS );
	}
	return ( bRes );
}

bool SisRegEliminarTodasSubclaves ( HKEY hkeyClave )
{
	bool	bRes = false;
	TCHAR	cDeposito [ REG_MAX_TAM_CLAVE + 1 ];
	DWORD	dwTamDep;

	if ( hkeyClave != NULL )
	{
		bRes = true;
		dwTamDep = REG_MAX_TAM_CLAVE + 1;
		while ( bRes &&
				( RegEnumKeyEx ( hkeyClave, 0, cDeposito, &dwTamDep,
								 NULL, NULL, NULL, NULL ) == ERROR_SUCCESS ) )
		{
			bRes = ( RegDeleteKey ( hkeyClave, cDeposito ) == ERROR_SUCCESS );
			/* Al final del bucle se reponia el tamano a 256, un numero suelto que
			   no tiene que ver con el buffer: REG_MAX_TAM_CLAVE + 1 son 64, asi
			   que a partir de la segunda vuelta se le decia a RegEnumKeyEx que
			   tenia cuatro veces mas sitio del que hay. */
			dwTamDep = REG_MAX_TAM_CLAVE + 1;
		}
	}
	return ( bRes );
}

/* Aviso comun a las ocho de aqui abajo: cuando los argumentos no valian, todas
   devolvian EXITO ( iRes = 1 en la rama else ). Era el mismo copia y pega ocho
   veces. Ahora contestan que no, que es lo que significa no haber hecho nada. */

bool SisRegConsultarClave ( HKEY hkeyClave, string & sValor )
{
	bool	bRes = false;
	LONG	lRet;
	DWORD	dwTam;
	DWORD	dwTipo;

	sValor.clear ();
	if ( hkeyClave != NULL )
	{
		string sBuffer ( REG_MAX_TAM_VALOR + 1, 0 );

		dwTam = (DWORD) sBuffer.size ();
		lRet = RegQueryValueEx ( hkeyClave, NULL, 0, &dwTipo,
								 (LPBYTE) sBuffer.data (), &dwTam );
		if ( ( lRet == ERROR_SUCCESS ) && ( dwTipo == REG_SZ ) )
		{
			sBuffer.resize ( dwTam );
			sValor = sBuffer.c_str ();
			bRes = true;
		}
	}
	return ( bRes );
}

bool SisRegConsultarClaveEnt ( HKEY hkeyClave, DWORD & dwValor )
{
	bool	bRes = false;
	LONG	lRet;
	DWORD	dwTam;
	DWORD	dwTipo;

	dwValor = 0;
	if ( hkeyClave != NULL )
	{
		dwTam = sizeof ( DWORD );
		lRet = RegQueryValueEx ( hkeyClave, NULL, 0, &dwTipo, (LPBYTE) &dwValor, &dwTam );
		bRes = ( ( lRet == ERROR_SUCCESS ) && ( dwTipo == REG_DWORD ) );
	}
	return ( bRes );
}

bool SisRegEstablecerClave ( HKEY hkeyClave, const string & sValor )
{
	bool	bRes = false;
	LONG	lRet;

	if ( hkeyClave != NULL )
	{
		lRet = RegSetValueEx ( hkeyClave, NULL, 0, REG_SZ,
							   (const BYTE *) sValor.c_str (),
							   (DWORD) ( sValor.size () + 1 ) );
		bRes = ( lRet == ERROR_SUCCESS );
	}
	return ( bRes );
}

bool SisRegEstablecerClaveEnt ( HKEY hkeyClave, DWORD dwValor )
{
	bool	bRes = false;
	LONG	lRet;

	if ( hkeyClave != NULL )
	{
		/* El tipo era REG_SZ, escribiendo los cuatro bytes de un DWORD como si
		   fueran texto. Quien lo leyera despues con SisRegConsultarClaveEnt, que
		   si exige REG_DWORD, no lo encontraba nunca. */
		lRet = RegSetValueEx ( hkeyClave, NULL, 0, REG_DWORD,
							   (const BYTE *) &dwValor, sizeof ( DWORD ) );
		bRes = ( lRet == ERROR_SUCCESS );
	}
	return ( bRes );
}

bool SisRegConsultarValor ( HKEY hkeyClave, const string & sNomValor, string & sValor )
{
	bool	bRes = false;
	LONG	lRet;
	DWORD	dwTam;
	DWORD	dwTipo;

	sValor.clear ();
	if ( ( hkeyClave != NULL ) && ( ! sNomValor.empty () ) )
	{
		string sBuffer ( REG_MAX_TAM_VALOR + 1, 0 );

		dwTam = (DWORD) sBuffer.size ();
		lRet = RegQueryValueEx ( hkeyClave, sNomValor.c_str (), 0, &dwTipo,
								 (LPBYTE) sBuffer.data (), &dwTam );
		if ( ( lRet == ERROR_SUCCESS ) && ( dwTipo == REG_SZ ) )
		{
			sBuffer.resize ( dwTam );
			sValor = sBuffer.c_str ();
			bRes = true;
		}
	}
	return ( bRes );
}

bool SisRegConsultarValorEnt ( HKEY hkeyClave, const string & sNomValor, DWORD & dwValor )
{
	bool	bRes = false;
	LONG	lRet;
	DWORD	dwTam;
	DWORD	dwTipo;

	dwValor = 0;
	if ( ( hkeyClave != NULL ) && ( ! sNomValor.empty () ) )
	{
		dwTam = sizeof ( DWORD );
		lRet = RegQueryValueEx ( hkeyClave, sNomValor.c_str (), 0, &dwTipo,
								 (LPBYTE) &dwValor, &dwTam );
		bRes = ( ( lRet == ERROR_SUCCESS ) && ( dwTipo == REG_DWORD ) );
	}
	return ( bRes );
}

bool SisRegEstablecerValor ( HKEY hkeyClave, const string & sNomValor, const string & sValor )
{
	bool	bRes = false;
	LONG	lRet;

	if ( ( hkeyClave != NULL ) && ( ! sNomValor.empty () ) )
	{
		lRet = RegSetValueEx ( hkeyClave, sNomValor.c_str (), 0, REG_SZ,
							   (const BYTE *) sValor.c_str (),
							   (DWORD) ( sValor.size () + 1 ) );
		bRes = ( lRet == ERROR_SUCCESS );
	}
	return ( bRes );
}

bool SisRegEstablecerValorEnt ( HKEY hkeyClave, const string & sNomValor, DWORD dwValor )
{
	bool	bRes = false;
	LONG	lRet;

	if ( ( hkeyClave != NULL ) && ( ! sNomValor.empty () ) )
	{
		/* Mismo REG_SZ sobre un DWORD que en SisRegEstablecerClaveEnt. */
		lRet = RegSetValueEx ( hkeyClave, sNomValor.c_str (), 0, REG_DWORD,
							   (const BYTE *) &dwValor, sizeof ( DWORD ) );
		bRes = ( lRet == ERROR_SUCCESS );
	}
	return ( bRes );
}

bool SisRegEliminarValor ( HKEY hkeyClave, const string & sNomValor )
{
	bool bRes = false;

	if ( ( hkeyClave != NULL ) && ( ! sNomValor.empty () ) )
	{
		bRes = ( RegDeleteValue ( hkeyClave, sNomValor.c_str () ) == ERROR_SUCCESS );
	}
	return ( bRes );
}

bool SisRegEliminarTodosValores ( HKEY hkeyClave )
{
	bool	bRes = false;
	TCHAR	cDeposito [ REG_MAX_TAM_CLAVE + 1 ];
	DWORD	dwTamDep;

	if ( hkeyClave != NULL )
	{
		bRes = true;
		dwTamDep = REG_MAX_TAM_CLAVE + 1;
		while ( bRes &&
				( RegEnumValue ( hkeyClave, 0, cDeposito, &dwTamDep,
								 NULL, NULL, NULL, NULL ) == ERROR_SUCCESS ) )
		{
			bRes = ( RegDeleteValue ( hkeyClave, cDeposito ) == ERROR_SUCCESS );
			/* El mismo 256 de SisRegEliminarTodasSubclaves. */
			dwTamDep = REG_MAX_TAM_CLAVE + 1;
		}
	}
	return ( bRes );
}

bool SisRegEliminarContenido ( HKEY hkeyClave )
{
	bool bRes = false;

	if ( hkeyClave != NULL )
	{
		bRes = ( RegSetValueEx ( hkeyClave, NULL, 0, REG_SZ, NULL, 0 ) == ERROR_SUCCESS );
	}
	return ( bRes );
}

bool SisRegImportarFichero ( HKEY hkeyPadre, const string & sClave, const string & sFichero )
{
	bool bRes = false;

	if ( ( hkeyPadre != NULL ) && ( ! sClave.empty () ) && ( ! sFichero.empty () ) )
	{
		/* La condicion estaba al reves: devolvia cierto cuando RegLoadKey
		   FALLABA, y falso cuando cargaba bien. */
		bRes = ( RegLoadKey ( hkeyPadre, sClave.c_str (), sFichero.c_str () ) == ERROR_SUCCESS );
	}
	return ( bRes );
}

bool SisRegExportarFichero ( HKEY hkeyClave, const string & sFichero )
{
	bool bRes = false;

	if ( ( hkeyClave != NULL ) && ( ! sFichero.empty () ) )
	{
		bRes = ( RegSaveKey ( hkeyClave, sFichero.c_str (), NULL ) == ERROR_SUCCESS );
	}
	return ( bRes );
}


/* Rutinas de alto nivel para módulos DLL: */

/* GUID en texto. Las seis rutinas de aqui abajo repetian este par de llamadas
   sobre un buffer CHAR fijo, y dos de ellas pedian DOS guids reutilizando el
   mismo puntero: el primer StringFromCLSID se perdia sin CoTaskMemFree. Aqui la
   memoria se suelta siempre antes de salir. */
static string _SisRegGuidCadena ( const GUID & guid )
{
	string		sRes ( "" );
	WCHAR *		p_wcGuid = NULL;

	if ( StringFromCLSID ( guid, &p_wcGuid ) == S_OK )
	{
		int iTam = WideCharToMultiByte ( CP_ACP, 0, p_wcGuid, -1, NULL, 0, NULL, NULL );

		if ( iTam > 1 )
		{
			/* iTam cuenta el terminador; el string lo pone por su cuenta. */
			sRes.resize ( iTam - 1 );
			WideCharToMultiByte ( CP_ACP, 0, p_wcGuid, -1, sRes.data (), iTam, NULL, NULL );
		}
		CoTaskMemFree ( p_wcGuid );
	}
	return ( sRes );
}

/* Crea la subclave y le escribe su valor por defecto, que es lo que hacian una y
   otra vez los bloques de RegistrarModulo y RegistrarGUID: RegCreateKey,
   RegSetValueEx sobre el valor sin nombre, y RegCloseKey. */
static bool _SisRegCrearConTexto ( HKEY hkeyPadre, const string & sSubclave, const string & sTexto )
{
	bool	bRes = false;
	HKEY	hkeyNueva;

	if ( RegCreateKey ( hkeyPadre, sSubclave.c_str (), &hkeyNueva ) == ERROR_SUCCESS )
	{
		bRes = SisRegEstablecerClave ( hkeyNueva, sTexto );
		RegCloseKey ( hkeyNueva );
	}
	return ( bRes );
}


bool SisRegRegistrarModulo ( const GUID & guidModulo, const string & sFicModulo, const string & sVersion )
{
	bool	bRes = false;
	string	sGuid = _SisRegGuidCadena ( guidModulo );
	HKEY	hkeyLibs;
	HKEY	hkeyModulo;
	HKEY	hkeyVersion;
	HKEY	hkeyRevision;

	if ( ! sGuid.empty () )
	{
		if ( RegCreateKey ( HKEY_CLASSES_ROOT, REG_SEC_LIBRERIAS, &hkeyLibs ) == ERROR_SUCCESS )
		{
			if ( RegCreateKey ( hkeyLibs, sGuid.c_str (), &hkeyModulo ) == ERROR_SUCCESS )
			{
				if ( RegCreateKey ( hkeyModulo, sVersion.c_str (), &hkeyVersion ) == ERROR_SUCCESS )
				{
					SisRegEstablecerClave ( hkeyVersion, sFicModulo );

					if ( RegCreateKey ( hkeyVersion, REG_LIB_REVISION_DEF, &hkeyRevision ) == ERROR_SUCCESS )
					{
						bRes = _SisRegCrearConTexto ( hkeyRevision, REG_CLV_LIB_FICHERO, sFicModulo );
						bRes = _SisRegCrearConTexto ( hkeyRevision, REG_CLV_LIB_ATRIBUTOS, REG_VAL_NUM_DEF ) && bRes;
						bRes = _SisRegCrearConTexto ( hkeyRevision, REG_CLV_LIB_FIC_AYUDA, REG_VAL_DEF ) && bRes;
						RegCloseKey ( hkeyRevision );
					}
					RegCloseKey ( hkeyVersion );
				}
				RegCloseKey ( hkeyModulo );
			}
			RegCloseKey ( hkeyLibs );
		}
	}
	return ( bRes );
}

bool SisRegRegistrarGUID ( const GUID & guidCodigo, const string & sNombre, const string & sDescripcion,
						   const GUID & guidModulo, const string & sFicModulo, const string & sVersion )
{
	bool	bRes = false;
	string	sGuid = _SisRegGuidCadena ( guidCodigo );
	string	sGuidMod = _SisRegGuidCadena ( guidModulo );
	HKEY	hkeyClases;
	HKEY	hkeyClase;

	/* Los dos ProgId se armaban con sprintf sobre buffers de 1024 sin comprobar
	   que cupieran. Son dos concatenaciones, y asi no hay buffer que desbordar.
	   Los formatos REG_PROG_ID_FORMATO y REG_PROG_ID_ACT_FORMATO de
	   RegistroConstantes.h quedan sin usar por lo mismo. */
	string	sProgId = sFicModulo + "." + sNombre;
	string	sProgIdAct = sProgId + "." + to_string ( REG_CLS_VERSION_DEF );

	if ( ( ! sGuid.empty () ) && ( ! sGuidMod.empty () ) )
	{
		if ( RegCreateKey ( HKEY_CLASSES_ROOT, REG_SEC_CLASES, &hkeyClases ) == ERROR_SUCCESS )
		{
			if ( RegCreateKey ( hkeyClases, sGuid.c_str (), &hkeyClase ) == ERROR_SUCCESS )
			{
				SisRegEstablecerClave ( hkeyClase, sDescripcion );

				bRes = _SisRegCrearConTexto ( hkeyClase, REG_CLV_CLS_CAT_IMP, REG_VAL_DEF );
				bRes = _SisRegCrearConTexto ( hkeyClase, REG_CLV_CLS_SERVIDOR, sFicModulo ) && bRes;
				bRes = _SisRegCrearConTexto ( hkeyClase, REG_CLV_CLS_PROG_ID, sProgIdAct ) && bRes;
				/* Esta creaba la clave en hkeyProgId, que ya estaba usada y cerrada,
				   y luego escribia y cerraba hkeyIndProgId, que seguia a NULL: el
				   VersionIndependentProgId no se escribia nunca y el HKEY se perdia. */
				bRes = _SisRegCrearConTexto ( hkeyClase, REG_CLV_CLS_IND_PROG_ID, sProgId ) && bRes;
				bRes = _SisRegCrearConTexto ( hkeyClase, REG_CLV_CLS_LIBRERIA, sGuidMod ) && bRes;
				bRes = _SisRegCrearConTexto ( hkeyClase, REG_CLV_CLS_VERSION, sVersion ) && bRes;

				RegCloseKey ( hkeyClase );

				/* ProgId con version. */
				if ( RegCreateKey ( HKEY_CLASSES_ROOT, sProgId.c_str (), &hkeyClase ) == ERROR_SUCCESS )
				{
					SisRegEstablecerClave ( hkeyClase, sDescripcion );
					bRes = _SisRegCrearConTexto ( hkeyClase, REG_CLV_CLS_ID, sGuid ) && bRes;
					bRes = _SisRegCrearConTexto ( hkeyClase, REG_CLV_VERSION_ACT, sProgIdAct ) && bRes;
					/* Este RegCloseKey faltaba: el HKEY quedaba abierto. */
					RegCloseKey ( hkeyClase );
				}
				else
				{
					bRes = false;
				}

				/* ProgId independiente de version. */
				if ( RegCreateKey ( HKEY_CLASSES_ROOT, sProgIdAct.c_str (), &hkeyClase ) == ERROR_SUCCESS )
				{
					SisRegEstablecerClave ( hkeyClase, sDescripcion );
					bRes = _SisRegCrearConTexto ( hkeyClase, REG_CLV_CLS_ID, sGuid ) && bRes;
					RegCloseKey ( hkeyClase );
				}
				else
				{
					bRes = false;
				}
			}
			RegCloseKey ( hkeyClases );
		}
	}
	return ( bRes );
}


void SisRegDesregistrarModulo ( const GUID & guidModulo, const string & sVersion )
{
	string	sGuid = _SisRegGuidCadena ( guidModulo );
	HKEY	hkeyLibs;
	HKEY	hkeyModulo;
	HKEY	hkeyVersion;
	HKEY	hkeyRevision;

	if ( ! sGuid.empty () )
	{
		if ( RegOpenKeyEx ( HKEY_CLASSES_ROOT, REG_SEC_LIBRERIAS, 0, KEY_WRITE, &hkeyLibs ) == ERROR_SUCCESS )
		{
			if ( RegOpenKeyEx ( hkeyLibs, sGuid.c_str (), 0, KEY_WRITE, &hkeyModulo ) == ERROR_SUCCESS )
			{
				if ( RegOpenKeyEx ( hkeyModulo, sVersion.c_str (), 0, KEY_WRITE, &hkeyVersion ) == ERROR_SUCCESS )
				{
					if ( RegOpenKeyEx ( hkeyVersion, REG_LIB_REVISION_DEF, 0, KEY_WRITE, &hkeyRevision ) == ERROR_SUCCESS )
					{
						RegDeleteKey ( hkeyRevision, REG_CLV_LIB_FICHERO );
						RegDeleteKey ( hkeyRevision, REG_CLV_LIB_ATRIBUTOS );
						RegDeleteKey ( hkeyRevision, REG_CLV_LIB_FIC_AYUDA );
						RegCloseKey ( hkeyRevision );
					}
					RegDeleteKey ( hkeyVersion, REG_LIB_REVISION_DEF );
					RegCloseKey ( hkeyVersion );
				}
				RegDeleteKey ( hkeyModulo, sVersion.c_str () );
				RegCloseKey ( hkeyModulo );
			}
			RegDeleteKey ( hkeyLibs, sGuid.c_str () );
			RegCloseKey ( hkeyLibs );
		}
	}
}

/* El ProgId se arma igual que en SisRegRegistrarGUID: ficheroModulo.nombre. De
   ahi que la firma reciba sFicModulo. Antes salia de sNombre + "." + sNombre,
   porque el fichero no entraba, y esta rutina no encontraba lo que habia
   registrado la otra salvo que nombre y fichero coincidieran. */
void SisRegDesregistrarGUID ( const GUID & guidCodigo, const string & sNombre,
							  const string & sFicModulo )
{
	string	sGuid = _SisRegGuidCadena ( guidCodigo );
	string	sProgId = sFicModulo + "." + sNombre;
	string	sProgIdAct = sProgId + "." + to_string ( REG_CLS_VERSION_DEF );
	HKEY	hkeyClases;
	HKEY	hkeyClase;

	if ( ! sGuid.empty () )
	{
		if ( RegOpenKeyEx ( HKEY_CLASSES_ROOT, REG_SEC_CLASES, 0, KEY_WRITE, &hkeyClases ) == ERROR_SUCCESS )
		{
			/* Abria desde hkeyClase, que en ese punto valia NULL, en vez de desde
			   hkeyClases: no llegaba a borrar nada de la clase. */
			if ( RegOpenKeyEx ( hkeyClases, sGuid.c_str (), 0, KEY_WRITE, &hkeyClase ) == ERROR_SUCCESS )
			{
				RegDeleteKey ( hkeyClase, REG_CLV_CLS_CAT_IMP );
				RegDeleteKey ( hkeyClase, REG_CLV_CLS_SERVIDOR );
				RegDeleteKey ( hkeyClase, REG_CLV_CLS_PROG_ID );
				RegDeleteKey ( hkeyClase, REG_CLV_CLS_LIBRERIA );
				RegDeleteKey ( hkeyClase, REG_CLV_CLS_VERSION );
				RegCloseKey ( hkeyClase );
			}
			RegDeleteKey ( hkeyClases, sGuid.c_str () );
			RegCloseKey ( hkeyClases );

			if ( RegOpenKeyEx ( HKEY_CLASSES_ROOT, sProgId.c_str (), 0, KEY_WRITE, &hkeyClase ) == ERROR_SUCCESS )
			{
				RegDeleteKey ( hkeyClase, REG_CLV_CLS_ID );
				RegDeleteKey ( hkeyClase, REG_CLV_VERSION_ACT );
				RegCloseKey ( hkeyClase );
			}
			RegDeleteKey ( HKEY_CLASSES_ROOT, sProgId.c_str () );

			if ( RegOpenKeyEx ( HKEY_CLASSES_ROOT, sProgIdAct.c_str (), 0, KEY_WRITE, &hkeyClase ) == ERROR_SUCCESS )
			{
				RegDeleteKey ( hkeyClase, REG_CLV_CLS_ID );
				RegCloseKey ( hkeyClase );
			}
			/* El borrado final repetia sProgId, asi que el ProgId con version se
			   quedaba sin borrar. */
			RegDeleteKey ( HKEY_CLASSES_ROOT, sProgIdAct.c_str () );
		}
	}
}

bool SisRegEstaRegistradoModulo ( const GUID & guidModulo )
{
	bool	bRes = false;
	string	sGuid = _SisRegGuidCadena ( guidModulo );
	HKEY	hkeyLibs;
	HKEY	hkeyModulo;

	if ( ! sGuid.empty () )
	{
		if ( RegOpenKeyEx ( HKEY_CLASSES_ROOT, REG_SEC_LIBRERIAS, 0, KEY_READ, &hkeyLibs ) == ERROR_SUCCESS )
		{
			if ( RegOpenKeyEx ( hkeyLibs, sGuid.c_str (), 0, KEY_READ, &hkeyModulo ) == ERROR_SUCCESS )
			{
				bRes = true;
				RegCloseKey ( hkeyModulo );
			}
			RegCloseKey ( hkeyLibs );
		}
	}
	return ( bRes );
}

/* Se llamaba EstaRegistradoGUID, sin el prefijo SisReg del resto del modulo y
   sin declarar en ninguna cabecera: no habia forma de llegar a ella desde fuera.
   El ProgId, como en SisRegDesregistrarGUID: ficheroModulo.nombre. */
bool SisRegEstaRegistradoGUID ( const GUID & guidCodigo, const string & sNombre,
								const string & sFicModulo )
{
	bool	bRes = false;
	string	sGuid = _SisRegGuidCadena ( guidCodigo );
	string	sProgId = sFicModulo + "." + sNombre;
	string	sProgIdAct = sProgId + "." + to_string ( REG_CLS_VERSION_DEF );
	HKEY	hkeyClases;
	HKEY	hkeyClase;

	if ( ! sGuid.empty () )
	{
		if ( RegOpenKeyEx ( HKEY_CLASSES_ROOT, REG_SEC_CLASES, 0, KEY_READ, &hkeyClases ) == ERROR_SUCCESS )
		{
			/* Mismo NULL que en SisRegDesregistrarGUID: abria desde hkeyClase. */
			if ( RegOpenKeyEx ( hkeyClases, sGuid.c_str (), 0, KEY_READ, &hkeyClase ) == ERROR_SUCCESS )
			{
				RegCloseKey ( hkeyClase );
				if ( RegOpenKeyEx ( HKEY_CLASSES_ROOT, sProgId.c_str (), 0, KEY_READ, &hkeyClase ) == ERROR_SUCCESS )
				{
					RegCloseKey ( hkeyClase );
					if ( RegOpenKeyEx ( HKEY_CLASSES_ROOT, sProgIdAct.c_str (), 0, KEY_READ, &hkeyClase ) == ERROR_SUCCESS )
					{
						bRes = true;
						RegCloseKey ( hkeyClase );
					}
				}
			}
			RegCloseKey ( hkeyClases );
		}
	}
	return ( bRes );
}


            }
		}
	}
}


#endif
