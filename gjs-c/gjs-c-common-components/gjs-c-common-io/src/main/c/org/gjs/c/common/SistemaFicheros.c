/***************************************************************************/
/*                        SistemaFicheros.c                                */
/*-------------------------------------------------------------------------*/
/* Librer�a: Sistema                                                       */
/* Versi�n:  1.1.0                                                         */
/* Fecha:    26/10/2006                                                    */
/* Autor:    Gin�s Jim�nez S�nchez                                         */
/*-------------------------------------------------------------------------*/
/* Descripci�n:                                                            */
/* Fichero de c�digo fuente que contiene la implementaci�n de las rutinas  */
/* de car�cter general de operaciones con el sistema de ficheros.          */
/* Mantiene un objeto global privado de clase CSistemaFicheros que puede   */
/* utilizarse para moverse por el �rbol de directorios.                    */
/*-------------------------------------------------------------------------*/
/* NOTA DEL AUTOR:                                                         */
/* Este m�dulo est� extra�do de una librer�a m�s completa creada por el    */
/* mismo autor. Por favor, el autor ruega que se le informe de cualquier   */
/* error detectado, as� como cualquier a�adido o modificaci�n realizado.   */
/* Pueden reportar de los mismos enviando un correo electr�nico a la       */
/* direcci�n: gines_jimenez@safe-mail.net. Gracias.                        */
/***************************************************************************/


#include "SistemaFicheros.h"

#include "FicherosConfig.h"

#include <SBuffer.h>



#define MAX_PARTES 256

// PENDIENTe: En unix/linux SisExisteFichero no distingue entre ficheros y directorios lo que puede
// llevar a confusi�n.


int SisEsSubdirectorioValido ( const char * p_cSubdirectorio )
{
	int iRes;

	if ( ES_VALIDO ( p_cSubdirectorio ) )
	{
		if ( CadCumpleExpReg ( p_cSubdirectorio, SF_PATRON_SUBDIRECTORIO ) == 1 )
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

int SisEsFicheroValido ( const char * p_cFichero )
{
	int iRes;

	if ( ES_VALIDO ( p_cFichero ) )
	{
		if ( ( CadCumpleExpReg ( p_cFichero, SF_PATRON_FICHERO ) == 1 ) ||
			 ( CadCumpleExpReg ( p_cFichero, SF_PATRON_FICHERO_2 ) == 1 ) )
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

int SisFicheroTieneExtension ( const char * p_cFichero )
{
	int iRes;

	if ( ES_VALIDO ( p_cFichero ) )
	{
		if ( CadCumpleExpReg ( p_cFichero, SF_PATRON_FICHERO ) == 1 ) 
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

int SisDirectorioNumSubdirectorios ( const char * p_cDirectorio )
{
	int iRes;

	if ( ES_VALIDO ( p_cDirectorio ) )
	{
		if ( CadContieneCaracter ( p_cDirectorio, SF_DIR_SEPARADOR ) == 1 )
		{
			iRes = CadNumPalabrasExt ( p_cDirectorio, SF_DIR_SEPARADOR, 0 );
		}
		else if ( CadContieneCaracter ( p_cDirectorio, SF_DIR_SEPARADOR_WIN ) == 1 )
		{
			iRes = CadNumPalabrasExt ( p_cDirectorio, SF_DIR_SEPARADOR_WIN, 0 );
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

char * SisDirectorioSubdirectorio ( const char * p_cDirectorio )
{
	return ( SisDirectorioSubdirectorioExt ( p_cDirectorio, -1 ) );
}

char * SisDirectorioSubdirectorioExt ( const char * p_cDirectorio, int iNivel )
{
	char *	p_cRes;
	int		iSubdir;
	char	cSep;
	int		iNumSubdirs;

	iNumSubdirs = SisDirectorioNumSubdirectorios ( p_cDirectorio );
	if ( iNumSubdirs > 1 )
	{
		if ( CadContieneCaracter ( p_cDirectorio, SF_DIR_SEPARADOR ) == 1 )
		{
			cSep = SF_DIR_SEPARADOR;
		}
		else
		{
			cSep = SF_DIR_SEPARADOR_WIN;
		}
		if ( iNivel == -1 )
		{
			iSubdir = iNumSubdirs - 1;
		}
		else 
		{
			iSubdir = iNivel;
		}
			 
		if ( ( iSubdir >= 0) && ( iSubdir < iNumSubdirs ) )
		{
			p_cRes = CadPalabraExt ( p_cDirectorio, iSubdir, cSep, 0 );
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

char * SisDirectorioSuperior ( const char * p_cDirectorio )
{
	char *	p_cRes;
	char	cSep;
	int		iPos;
	int		iLong;

	if ( ES_VALIDO ( p_cDirectorio ) )
	{
		if ( CadContieneCaracter ( p_cDirectorio, SF_DIR_SEPARADOR ) == 1 )
		{
			cSep = SF_DIR_SEPARADOR;
		}
		else
		{
			cSep = SF_DIR_SEPARADOR_WIN;
		}
		iLong = CadLongitud ( p_cDirectorio );
		iPos = CadBuscarDescCaracter ( p_cDirectorio, cSep, iLong - 2 );
		if ( ( iPos > 1 ) && ( iPos < iLong - 2 ) )
		{
			p_cRes = CadExtraerPrimeros ( p_cDirectorio, iPos );
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

char * SisFicheroExtension ( const char * p_cFichero )
{
	char *	p_cRes;

	if ( ES_VALIDO ( p_cFichero ) )
	{
		if ( CadCumpleExpReg ( p_cFichero, SF_PATRON_FICHERO ) == 1 ) 
		{
			p_cRes = CadExtraerDesdeCaracterExt ( p_cFichero, SF_FIC_SEPARADOR, 0, -1, -1 );
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

char * SisFicheroNombre ( const char * p_cFichero )
{
	char *	p_cRes;
	char		cSep;
	int			iPosIni;
	int			iPosFin;

	if ( ES_VALIDO ( p_cFichero ) )
	{
		if ( CadCumpleExpReg ( p_cFichero, SF_PATRON_FICHERO ) == 1 ) 
		{
			if ( CadContieneCaracter ( p_cFichero, SF_DIR_SEPARADOR ) == 1 )
			{
				cSep = SF_DIR_SEPARADOR;
			}
			else
			{
				cSep = SF_DIR_SEPARADOR_WIN;
			}
			iPosIni = CadBuscarDescCaracter ( p_cFichero, cSep, -1 ) + 1; 
			iPosFin = CadBuscarDescCaracter ( p_cFichero, SF_FIC_SEPARADOR, -1 ); 
			p_cRes = CadExtraer ( p_cFichero, iPosIni, iPosFin - iPosIni );
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

char * SisComponerFichero ( const char * p_cNombre, const char * p_cExtension )
{
	char * p_cFichero;

	if ( ES_VALIDO ( p_cNombre ) && ES_VALIDO ( p_cExtension ) )
	{
		p_cFichero = CadCrear ( CadLongitud ( p_cNombre ) + CadLongitud ( p_cExtension ) + 1 );
		if ( ES_VALIDO ( p_cFichero ) )
		{
			CadCopiarConFormato ( p_cFichero, SF_MASCARA_FICHERO, p_cNombre, p_cExtension );
		}
	}
	else
	{
		p_cFichero = CadDuplicar ( p_cNombre );
	}
	return ( p_cFichero );
}

char * SisRutaDirectorio ( const char * p_cRuta )
{
	char *	p_cRes;
	int		iPos;
	char	cSep;

	if ( SisEsRutaValida ( p_cRuta ) == 1 ) 
	{
		if ( CadContieneCaracter ( p_cRuta, SF_DIR_SEPARADOR ) == 1 )
		{
			cSep = SF_DIR_SEPARADOR;
		}
		else
		{
			cSep = SF_DIR_SEPARADOR_WIN;
		}
		iPos = CadBuscarDescCaracter ( p_cRuta, cSep, -1 ); 
		p_cRes = CadExtraerPrimeros ( p_cRuta, iPos );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

char * SisRutaFichero ( const char * p_cRuta )
{
	char *	p_cRes;
	int			iPos;
	char		cSep;

	if ( SisEsRutaValida ( p_cRuta ) == 1 ) 
	{
		if ( CadContieneCaracter ( p_cRuta, SF_DIR_SEPARADOR ) == 1 )
		{
			cSep = SF_DIR_SEPARADOR;
		}
		else
		{
			cSep = SF_DIR_SEPARADOR_WIN;
		}
		iPos = CadBuscarDescCaracter ( p_cRuta, cSep, -1 ); 
		p_cRes = CadExtraerUltimos ( p_cRuta, CadLongitud ( p_cRuta ) - iPos - 1 );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

int SisRutaNumSubdirectorios ( const char * p_cRuta )
{
	int			iRes;
	char *	p_cDirectorio;

	p_cDirectorio = SisRutaDirectorio ( p_cRuta );
	if ( ES_VALIDO ( p_cDirectorio ) )
	{
		iRes = SisDirectorioNumSubdirectorios ( p_cDirectorio );
		MemLiberar ( (void **) &p_cDirectorio );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

char * SisRutaSubdirectorio ( const char * p_cRuta )
{
	return ( SisRutaSubdirectorioExt ( p_cRuta, 0 ) );
}

char * SisRutaSubdirectorioExt ( const char * p_cRuta, int iNivel )
{
	char *	p_cRes;
	char *	p_cDirectorio;

	p_cDirectorio = SisRutaDirectorio ( p_cRuta );
	if ( ES_VALIDO ( p_cDirectorio ) )
	{
		p_cRes = SisDirectorioSubdirectorioExt ( p_cDirectorio, iNivel );
		MemLiberar ( (void **) &p_cDirectorio );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

char * SisComponerRuta ( const char * p_cDirectorio, const char * p_cFichero, int iDirActualPorDef )
{
	char * p_cRuta;

	if ( ( SisEsFicheroValido ( p_cFichero ) == 1 ) || ( SisEsSubdirectorioValido ( p_cFichero ) == 1 ) )
	{
		if ( SisEsRutaValida ( p_cDirectorio ) == 1 )
		{
			p_cRuta = CadCrear ( CadLongitud ( p_cDirectorio ) + CadLongitud ( p_cFichero ) + 1 );
			if ( ES_VALIDO ( p_cRuta ) )
			{
				CadCopiarConFormato ( p_cRuta, SF_MASCARA_RUTA, p_cDirectorio, p_cFichero );
			}
		}
		else
		{
			p_cRuta = CadCrear ( CadLongitud ( p_cFichero ) + 3 );
			if ( ES_VALIDO ( p_cRuta ) )
			{
				CadCopiarConFormato ( p_cRuta, SF_MASCARA_RUTA, SF_DIR_ACTUAL, p_cFichero );
			}
		}
	}
	else
	{
		if ( SisEsRutaValida ( p_cDirectorio ) == 1 )
		{
			p_cRuta = CadDuplicar ( p_cDirectorio );
		}
		else
		{
			if ( iDirActualPorDef == 1 )
			{
				p_cRuta = CadDuplicar ( SF_DIR_ACTUAL );
			}
			else
			{
				p_cRuta = NULL;
			}
		}
	}
	return ( p_cRuta );
}

char * SisComponerRutaExt ( const char * p_cDirectorio, const char * p_cSubdirectorio, const char * p_cFichero, int iDirActualPorDef )
{
	char * p_cDirComp;
	char * p_cRuta;

	if ( SisEsSubdirectorioValido ( p_cSubdirectorio ) == 1 )
	{
		p_cDirComp = SisComponerRuta ( p_cDirectorio, p_cSubdirectorio, 0 );
		p_cRuta = SisComponerRuta ( p_cDirComp, p_cFichero, iDirActualPorDef );
		MemLiberar ( (void **) &p_cDirComp );
	}
	else
	{
		p_cRuta = SisComponerRuta ( p_cDirectorio, p_cFichero, iDirActualPorDef );
	}
	return ( p_cRuta );
}


void SisNormalizarRutaWindows ( char * p_cRuta )
{
	CadReemplazarCaracter ( p_cRuta, '/', '\\' );
	CadReemplazar ( p_cRuta, "\\:", ":" );
	CadReemplazar ( p_cRuta, "\\\\", "\\" );
}

void SisNormalizarRuta ( char * p_cRuta )
{
	CadReemplazar ( p_cRuta, "\\\\", "/" );
	CadReemplazarCaracter ( p_cRuta, '\\', '/' );
}

int SisEsRutaValida ( const char * p_cRuta )
{
	char * 	p_cRutaNorm;
	int		iWindows;	
	int 	iRes;

	if ( ES_VALIDO ( p_cRuta ) )
	{
		p_cRutaNorm = CadDuplicar ( p_cRuta );
		if ( ES_VALIDO ( p_cRutaNorm ) )
		{
			if ( ( CadContieneCaracter  ( p_cRuta, '\\' ) == 1 ) ||
				 ( CadCaracter ( p_cRuta, 1 ) == ':' ) )
			{
				SisNormalizarRutaWindows ( p_cRutaNorm );
				iWindows = 1;
			}
			else
			{
				SisNormalizarRuta ( p_cRutaNorm );
				iWindows = 0;
			}
			if ( iWindows == 0 )
			{
				if ( ( CadCumpleExpReg ( p_cRutaNorm, SF_PATRON_RUTA ) == 1 ) ||  
					 ( CadCumpleExpReg ( p_cRutaNorm, SF_PATRON_RUTA_REL ) == 1 ) ||  
					 ( CadCumpleExpReg ( p_cRutaNorm, SF_PATRON_RUTA_REL_2 ) == 1 ) )  
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
				if ( ( CadCumpleExpReg ( p_cRutaNorm, SF_PATRON_RUTA_WIN ) == 1 ) ||  
					 ( CadCumpleExpReg ( p_cRutaNorm, SF_PATRON_RUTA_REL_WIN ) == 1 ) ||  
					 ( CadCumpleExpReg ( p_cRutaNorm, SF_PATRON_RUTA_REL_WIN_2 ) == 1 ) )  
				{
					iRes = 1;
				}
				else
				{
					iRes = 0;
				}
			}
			MemLiberarCadena ( &p_cRutaNorm );
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

int SisEsRutaAbsoluta ( const char * p_cRuta )
{
	char * 	p_cRutaNorm;	
	int 	iRes;

	p_cRutaNorm = CadDuplicar ( p_cRuta );	
	if ( SisRutaEsEstiloWindows  ( p_cRutaNorm ) == 1 )
	{
		SisNormalizarRutaWindows ( p_cRutaNorm );
	}
	else
	{
		SisNormalizarRuta ( p_cRutaNorm );
	}
	if ( ( CadCumpleExpReg ( p_cRutaNorm, SF_PATRON_RUTA ) == 1 ) ||  
		 ( CadCumpleExpReg ( p_cRutaNorm, SF_PATRON_RUTA_WIN ) == 1 ) )  
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	MemLiberarCadena ( &p_cRutaNorm );
	return ( iRes );
}

int SisEsRutaRelativa ( const char * p_cRuta )
{
	char * 	p_cRutaNorm;	
	int 	iRes;

	p_cRutaNorm = CadDuplicar ( p_cRuta );	
	if ( SisRutaEsEstiloWindows  ( p_cRutaNorm ) == 1 )
	{
		SisNormalizarRutaWindows ( p_cRutaNorm );
	}
	else
	{
		SisNormalizarRuta ( p_cRutaNorm );
	}
	if ( ( CadCumpleExpReg ( p_cRutaNorm, SF_PATRON_RUTA_REL ) == 1 ) ||  
		 ( CadCumpleExpReg ( p_cRutaNorm, SF_PATRON_RUTA_REL_2 ) == 1 ) ||
		 ( CadCumpleExpReg ( p_cRutaNorm, SF_PATRON_RUTA_REL_WIN ) == 1 ) ||  
		 ( CadCumpleExpReg ( p_cRutaNorm, SF_PATRON_RUTA_REL_WIN_2 ) == 1 ) )  
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	MemLiberarCadena ( &p_cRutaNorm );
	return ( iRes );
}

int SisEsRutaValidaSistema ( const char * p_cRuta )
{
	char * 	p_cRutaNorm;	
	int 	iRes;

	p_cRutaNorm = CadDuplicar ( p_cRuta );	
# if ( defined ( CYGWIN ) )
	SisNormalizarRuta ( p_cRutaNorm );
	if ( ( CadCumpleExpReg ( p_cRutaNorm, SF_PATRON_RUTA ) == 1 ) ||  
		 ( CadCumpleExpReg ( p_cRutaNorm, SF_PATRON_RUTA_REL ) == 1 ) ||  
		 ( CadCumpleExpReg ( p_cRutaNorm, SF_PATRON_RUTA_REL_2 ) == 1 ) )  
# elif ( defined ( WIN ) )
	SisNormalizarRutaWindows ( p_cRutaNorm );
	if ( ( CadCumpleExpReg ( p_cRutaNorm, SF_PATRON_RUTA_WIN ) == 1 ) ||  
		 ( CadCumpleExpReg ( p_cRutaNorm, SF_PATRON_RUTA_REL_WIN ) == 1 ) ||  
		 ( CadCumpleExpReg ( p_cRutaNorm, SF_PATRON_RUTA_REL_WIN_2 ) == 1 ) )  
# else
	SisNormalizarRuta ( p_cRutaNorm );
	if ( ( CadCumpleExpReg ( p_cRutaNorm, SF_PATRON_RUTA ) == 1 ) ||  
		 ( CadCumpleExpReg ( p_cRutaNorm, SF_PATRON_RUTA_REL ) == 1 ) ||  
		 ( CadCumpleExpReg ( p_cRutaNorm, SF_PATRON_RUTA_REL_2 ) == 1 ) )  
#     endif
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	MemLiberarCadena ( &p_cRutaNorm );
	return ( iRes );
}

int SisRutaEsEstiloWindows ( const char * p_cRuta )
{
	int iRes;

	if ( SisEsRutaValida ( p_cRuta ) == 1 )
	{
		if ( ( CadContieneCaracter  ( p_cRuta, '\\' ) == 1 ) ||
			 ( CadCaracter ( p_cRuta, 1 ) == ':' ) )
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

char * SisRutaEstiloWindows ( const char * p_cRuta )
{
	return ( SisRutaEstiloWindowsExt ( p_cRuta, 'C' ) );
}

char * SisRutaEstiloWindowsExt ( const char * p_cRuta, char cUnidad )
{
	char *	p_cResultado;
	char **	p_p_cPartes;
	int		iCount;
	int		iPartes;
	int 	iRelativa;

	if ( ( SisEsRutaValida ( p_cRuta ) == 1 ) && ( ASCIIEsLetra ( cUnidad ) == 1 ) )
	{
		p_cResultado = CadCrear ( MAXPATHLEN - 1 );
		if ( SisRutaEsEstiloWindows ( p_cRuta ) == 0 )
		{
			p_p_cPartes = (char **) MemReservar ( MAX_PARTES * sizeof ( char * ) );
			iPartes = CadNumPalabrasSep ( p_cRuta, '/' );
			for ( iCount = 0; iCount < iPartes; iCount = iCount + 1 )
			{
				p_p_cPartes [ iCount ] = CadPalabraSep ( p_cRuta, iCount, '/' );
			}
				
			if ( SisEsRutaRelativa ( p_cRuta ) == 0 )
			{
				CadConcatenarCaracter ( p_cResultado, ASCIILetraMinAMay ( cUnidad ) );
				CadConcatenar ( p_cResultado, ":" );
				iRelativa = 0;
			}
			else
			{
				iRelativa = 1;
			}
			for ( int i = 0; i < iPartes; i = i + 1 )
			{
				if ( ( iRelativa == 0 ) || ( i > 0 ) )
				{
					CadConcatenarCaracter ( p_cResultado, '\\' );
				}
				CadConcatenar ( p_cResultado, p_p_cPartes [ i ] );
				MemLiberar ( ( void ** ) &(p_p_cPartes [ i ]) );
			}
			MemLiberar ( ( void ** ) &p_p_cPartes );
		}
		else
		{
			CadConcatenar ( p_cResultado, p_cRuta );
			SisNormalizarRutaWindows ( p_cResultado );
		}
	}
	else
	{
		ERROR_ESTABLECER ( ERR_PARAMETROS );
		p_cResultado = NULL;
	}
	return ( p_cResultado );
}

char * SisRutaEstiloUnix ( const char * p_cRuta )
{
	char *	p_cRutaCopia;
	char *	p_cResultado;
	char *  p_cParte;
	int		iParteIni;
	int		iEsAbsoluto;
	int		iPartes;

	if ( SisEsRutaValida ( p_cRuta ) == 1 )
	{
		p_cResultado = CadCrear ( MAXPATHLEN - 1 );
		if ( SisRutaEsEstiloWindows ( p_cRuta ) == 1 )
		{
			p_cRutaCopia = CadDuplicar ( p_cRuta );
			if ( ES_VALIDO ( p_cRutaCopia ) )
			{
				CadReemplazarCaracter ( p_cRutaCopia, '/', '\\' );
				CadReemplazar ( p_cRutaCopia, "\\\\", "\\" );
				
				if ( CadCumpleExpReg ( p_cRutaCopia, SF_PATRON_RUTA_WIN ) == 1 )
				{
					iParteIni = 1;
					iEsAbsoluto = 1;
				}
				else
				{
					iParteIni = 0;
					iEsAbsoluto = 0;
				}
				iPartes = CadNumPalabrasSep ( p_cRutaCopia, '\\' );
				if ( iEsAbsoluto == 1 )
				{
					CadConcatenarCaracter ( p_cResultado, '/' );
				}
				for ( int i = iParteIni; i < iPartes; i = i + 1 )
				{
					if ( i > iParteIni )
					{
						CadConcatenarCaracter ( p_cResultado, '/' );
					}
					p_cParte = CadPalabraSep ( p_cRutaCopia, i, '\\' );
					CadConcatenar ( p_cResultado, p_cParte );
					MemLiberarCadena ( &p_cParte );
				}
				MemLiberarCadena ( &p_cRutaCopia );
			}
			else
			{
				p_cResultado = NULL;
			}
		}
		else
		{
			CadConcatenar ( p_cResultado, p_cRuta );
			SisNormalizarRuta ( p_cResultado );
		}
	}
	else
	{
		ERROR_ESTABLECER ( ERR_PARAMETROS );
		p_cResultado = NULL;
	}
	return ( p_cResultado );
}

char * SisRutaEstiloCygwin ( const char * p_cRuta )
{
	char *	p_cRutaCopia;
	char *	p_cResultado;
	char *  p_cParte;
	int		iParteIni;
	int		iEsAbsoluto;
	int		iPartes;
	char	cUnidad;

	if ( SisEsRutaValida ( p_cRuta ) == 1 )
	{
		p_cResultado = CadCrear ( MAXPATHLEN - 1 );
		if ( SisRutaEsEstiloWindows ( p_cRuta ) == 1 )
		{
			p_cRutaCopia = CadDuplicar ( p_cRuta );
			if ( ES_VALIDO ( p_cRutaCopia ) )
			{
				// Aseguramos que todo esta en Windows
				SisNormalizarRutaWindows ( p_cRutaCopia );
				if ( CadCumpleExpReg ( p_cRutaCopia, SF_PATRON_RUTA_WIN ) == 1 ) 
				{
					iParteIni = 1;
					iEsAbsoluto = 1;
					cUnidad = CadCaracter ( p_cRutaCopia, 0 );
				}
				else
				{
					iParteIni = 0;
					iEsAbsoluto = 0;
				}
				iPartes = CadNumPalabrasSep ( p_cRutaCopia, '\\' );
				if ( iEsAbsoluto == 1 )
				{
					CadConcatenar ( p_cResultado, "/cygdrive/" );
					CadConcatenarCaracter ( p_cResultado, ASCIILetraMayAMin ( cUnidad ) );
					CadConcatenarCaracter ( p_cResultado, '/' );
				}
				for ( int i = iParteIni; i < iPartes; i = i + 1 )
				{
					if ( i > iParteIni )
					{
						CadConcatenarCaracter ( p_cResultado, '/' );
					}
					p_cParte = CadPalabraSep ( p_cRutaCopia, i, '\\' );
					CadConcatenar ( p_cResultado, p_cParte );
					MemLiberarCadena ( &p_cParte );
				}
				MemLiberarCadena ( &p_cRutaCopia );
			}
			else
			{
				p_cResultado = NULL;
			}
		}
		else
		{
			CadConcatenar ( p_cResultado, p_cRuta );
			SisNormalizarRuta ( p_cResultado );
		}
	}
	else
	{
		ERROR_ESTABLECER ( ERR_PARAMETROS );
		p_cResultado = NULL;
	}
	return ( p_cResultado );
}

char * SisRutaEstiloSistema ( const char * p_cRuta )
{
	char *	p_cResultado;
	
# if ( defined ( WIN ) )
	p_cResultado = SisRutaEstiloWindows ( p_cRuta );
# elif ( defined ( CYGWIN ) )
	p_cResultado = SisRutaEstiloCygwin ( p_cRuta );
# else
	p_cResultado = SisRutaEstiloUnix ( p_cRuta );
# endif	
	return ( p_cResultado );
}

char * SisDirectorioActual ()
{
	char *		p_cRes;
	SBuffer	*	p_bufDatos;

	p_bufDatos = SBufCrear ( SF_MAX_TAM_RUTA );
	if ( ES_VALIDO ( p_bufDatos ) )
	{
# if ( defined ( WIN ) )
		if ( GetCurrentDirectory ( (DWORD) SBufTam ( p_bufDatos ), (LPSTR) SBufDireccion ( p_bufDatos ) ) > 0 )
		{
			p_cRes = SBufDuplicarCadena ( p_bufDatos );
		}
		else
		{
			p_cRes = NULL;
		}
# else
		if ( getcwd ( (char *) SBufDireccion ( p_bufDatos ), SBufTam ( p_bufDatos ) ) != NULL )
		{
			p_cRes = SBufDuplicarCadena ( p_bufDatos );
		}
		else
		{
			p_cRes = NULL;
		}
# endif
		SBufDestruir ( &p_bufDatos );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

int SisEstDirectorioActual ( const char * p_cDirectorio )
{
	int iRes;

	if ( ES_VALIDO ( p_cDirectorio ) )
	{
#	  if ( defined ( WIN ) )
		if ( SetCurrentDirectory ( p_cDirectorio ) != 0 )
#	  else
		if ( chdir ( p_cDirectorio ) == 0 )
#	  endif
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

const char * SisCadenaDirectorioSistema ()
{
	const char *	p_cRes;
	SBuffer	*		p_bufDatos;
	
	p_bufDatos = SBufCrear ( SF_MAX_TAM_RUTA );
	if ( ES_VALIDO ( p_bufDatos ) )
	{
#	 if ( defined ( WIN ) )
		GetSystemDirectory ( (LPTSTR) SBufDireccion ( p_bufDatos ), (UINT) SBufTam ( p_bufDatos ) );
		p_cRes = SBufDuplicarCadena ( p_bufDatos );
#	 else
		p_cRes = NULL;
#	 endif

		SBufDestruir ( &p_bufDatos );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

const char * SisCadenaDirectorioFuentes ()
{
	const char * p_cRes;

	p_cRes = NULL;
	return ( p_cRes );
}

int SisExisteFichero ( const char * p_cRuta )
{
	int			iRes;
	char *		p_cRutaNorm;
# if ( defined ( WIN ) )
	DWORD		dwAtributos;
# else
	struct stat statInfo;
# endif

	p_cRutaNorm = SisRutaEstiloSistema ( p_cRuta );
	if ( ES_VALIDO ( p_cRutaNorm ) )
	{
#	 if ( defined ( WIN ) )
		dwAtributos = GetFileAttributes ( p_cRutaNorm );
		if ( dwAtributos == INVALID_FILE_ATTRIBUTES )
		{
			iRes = 0;
		}
		else 
		{
			if ( ( dwAtributos & FILE_ATTRIBUTE_DIRECTORY ) == FILE_ATTRIBUTE_DIRECTORY )
			{
				iRes = 0;
			}
			else
			{
				iRes = 1;
			}
		}

#	 else
		memset ( &statInfo, 0, sizeof(struct stat) );
		if ( stat ( p_cRutaNorm, &statInfo ) < 0 )
		{
			  iRes = 0;
		}
		else 
		{
			iRes = 1;
		}
#	 endif
		MemLiberarCadena ( &p_cRutaNorm );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SisExisteFicheroExt ( const char * p_cDirectorio, const char * p_cFichero )
{
	int		iRes;
	char *	p_cRuta;

	p_cRuta = SisComponerRuta ( p_cDirectorio, p_cFichero, 0 );
	if ( ES_VALIDO ( p_cRuta ) )
	{
		iRes = SisExisteFichero ( p_cRuta );
		MemLiberar ( (void **) &p_cRuta );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SisExisteDirectorio ( const char * p_cRuta )
{
	int			iRes;
	char *		p_cRutaNorm;

# if ( defined ( WIN ) )
	DWORD		dwAtributos;
# else
	struct stat statInfo;
# endif

	p_cRutaNorm = SisRutaEstiloSistema ( p_cRuta );
	if ( ES_VALIDO ( p_cRutaNorm ) )
	{
	
#	 if ( defined ( WIN ) )
		dwAtributos = GetFileAttributes ( p_cRutaNorm );
		if ( dwAtributos == INVALID_FILE_ATTRIBUTES )
		{
			iRes = 0;
		}
		else
		{
			if ( ( dwAtributos  & FILE_ATTRIBUTE_DIRECTORY ) == FILE_ATTRIBUTE_DIRECTORY )
			{
				iRes = 1;
			}
			else
			{
				iRes = 0;
			}
		}

#	 else
		memset ( &statInfo, 0, sizeof(struct stat) );
		if ( stat ( p_cRutaNorm, &statInfo ) != 0 )
		{
			  iRes = 0;
		}
		else 
		{
			if ( ( statInfo.st_mode & S_IFDIR ) == S_IFDIR )
			{
				iRes = 1;
			}
			else
			{
				iRes = 0;
			}
		}
# endif
		MemLiberarCadena ( &p_cRutaNorm );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SisExisteDirectorioExt ( const char * p_cDirectorio, const char * p_cSubdirectorio )
{
	int		iRes;
	char *	p_cRuta;

	p_cRuta = SisComponerRuta ( p_cDirectorio, p_cSubdirectorio, 0 );
	if ( ES_VALIDO ( p_cRuta ) )
	{
		iRes = SisExisteDirectorio ( p_cRuta );
		MemLiberar ( (void **) &p_cRuta );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SisCrearFichero ( const char * p_cRuta )
{
	FILE *	p_fObj;
	int		iRes;
	char *	p_cRutaNorm;

	if ( SisExisteFichero ( p_cRuta ) == 0 )
	{
		p_cRutaNorm = SisRutaEstiloSistema ( p_cRuta );
		if ( ES_VALIDO ( p_cRutaNorm ) )
		{	
			p_fObj = fopen ( p_cRutaNorm, "a" );
			if ( ES_VALIDO ( p_fObj ) )
			{
				fclose ( p_fObj );
				iRes = 1;
			}
			else
			{
				iRes = 0;
			}
			MemLiberarCadena ( &p_cRutaNorm );
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

int SisCrearFicheroExt ( const char * p_cDirectorio, const char * p_cFichero )
{
	int		iRes;
	char *	p_cRuta;

	p_cRuta = SisComponerRuta ( p_cDirectorio, p_cFichero, 0 );
	if ( ES_VALIDO ( p_cRuta ) )
	{
		iRes = SisCrearFichero ( p_cRuta );
		MemLiberar ( (void **) &p_cRuta );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SisCrearDirectorio ( const char * p_cDirectorio )
{
	int		iRes;
	char *	p_cRutaNorm;

	if ( SisExisteDirectorio ( p_cDirectorio ) == 0 )
	{
		p_cRutaNorm = SisRutaEstiloSistema ( p_cDirectorio );
		if ( ES_VALIDO ( p_cRutaNorm ) )
		{	
#		  if ( defined ( WIN ) )
			if ( CreateDirectory ( (LPCSTR) p_cRutaNorm, NULL ) != 0 )		
#		  else
			if ( mkdir ( p_cRutaNorm,  S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH ) == 0 )
#		  endif
			{
				iRes = 1;
			}
			else
			{
				iRes = 0;
			}
			MemLiberarCadena ( &p_cRutaNorm );
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

int SisCrearDirectorioExt ( const char * p_cDirectorio, const char * p_cSubdirectorio )
{
	int		iRes;
	char *	p_cRuta;

	p_cRuta = SisComponerRuta ( p_cDirectorio, p_cSubdirectorio, 0 );
	if ( ES_VALIDO ( p_cRuta ) )
	{
		iRes = SisCrearDirectorio ( p_cRuta );
		MemLiberar ( (void **) &p_cRuta );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SisEliminarFichero ( const char * p_cRuta )
{
	int			iRes;
	char *		p_cRutaNorm;

	if ( SisExisteFichero ( p_cRuta ) == 1 )
	{
		p_cRutaNorm = SisRutaEstiloSistema ( p_cRuta );
		if ( ES_VALIDO ( p_cRutaNorm ) )
		{	
#		  if ( defined ( WIN ) )
			if ( DeleteFile ( (LPCSTR) p_cRutaNorm ) != 0 )		
#		  else
			if ( remove ( p_cRutaNorm ) == 0 )
#		  endif
			{
				iRes = 1;
			}
			else
			{
				iRes = 0;
			}
			MemLiberarCadena ( &p_cRutaNorm );
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

int SisEliminarFicheroExt ( const char * p_cDirectorio, const char * p_cFichero )
{
	int		iRes;
	char *	p_cRuta;

	p_cRuta = SisComponerRuta ( p_cDirectorio, p_cFichero, 0 );
	if ( ES_VALIDO ( p_cRuta ) )
	{
		iRes = SisEliminarFichero ( p_cRuta );
		MemLiberar ( (void **) &p_cRuta );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

const char * SisMascaraBusquedaEnDirectorio ( const char * p_cDirectorio )
{
	char * p_cRes;

	if ( ES_VALIDO ( p_cDirectorio ) )
	{
		p_cRes = CadCrear ( CadLongitud ( p_cDirectorio ) + 4 );
		if ( ES_VALIDO ( p_cRes ) )
		{
			CadCopiar ( p_cRes, p_cDirectorio );
			CadConcatenarCaracter ( p_cRes, SF_DIR_SEPARADOR );
			CadConcatenar ( p_cRes, SF_MASCARA_BUSQUEDA );
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
	return ( (const char *) p_cRes );
}

int SisEliminarDirectorio ( const char * p_cDirectorio )
{
	int		iRes;
	char *	p_cRutaNorm;

	if ( SisExisteDirectorio ( p_cDirectorio ) == 1 )
	{
		p_cRutaNorm = SisRutaEstiloSistema ( p_cDirectorio );
		if ( ES_VALIDO ( p_cRutaNorm ) )
		{	
#		  if ( defined ( WIN ) )
			if ( RemoveDirectory ( (LPCSTR) p_cRutaNorm ) != 0 )		
#		  else
			if ( rmdir ( p_cRutaNorm ) == 0 )
#		  endif
			{
				iRes = 1;
			}
			else
			{
				iRes = 0;
			}
			MemLiberarCadena ( &p_cRutaNorm );
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

int SisEliminarDirectorioExt ( const char * p_cDirectorio, const char * p_cSubdirectorio )
{
	int			iRes;
	char *	p_cRuta;

	p_cRuta = SisComponerRuta ( p_cDirectorio, p_cSubdirectorio, 0 );
	if ( ES_VALIDO ( p_cRuta ) )
	{
		iRes = SisEliminarDirectorio ( p_cRuta );
		MemLiberar ( (void **) &p_cRuta );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SisVaciarDirectorio ( const char * p_cDirectorio )
{
	int					iRes;
	char *				p_cRutaNorm;
# if ( defined ( WIN ) )
	const char *		p_cMascBusqueda;
	WIN32_FIND_DATA		fndfildatObj;
	HANDLE				hBusqueda;
	int					iResBusq;
# else
   DIR * p_dirInfo;
    struct dirent *		p_directInfo;
# endif

	if ( SisExisteDirectorio ( p_cDirectorio ) == 1 )
	{
		p_cRutaNorm = SisRutaEstiloSistema ( p_cDirectorio );
		if ( ES_VALIDO ( p_cRutaNorm ) )
		{	
#		  if ( defined ( WIN ) )

			p_cMascBusqueda = SisMascaraBusquedaEnDirectorio ( p_cRutaNorm );
			if ( ES_VALIDO ( p_cMascBusqueda ) )
			{
				hBusqueda = FindFirstFile ( p_cMascBusqueda, &fndfildatObj );
				if ( hBusqueda != INVALID_HANDLE_VALUE ) 
				{
					iRes = 1;
					iResBusq = 1;
					while ( ( iResBusq != 0 ) && ( iRes == 1 ) )
					{
						if ( fndfildatObj.cFileName [ 0 ] != '.' )
						{
							if ( SisExisteFicheroExt ( p_cRutaNorm, fndfildatObj.cFileName ) == 1 )
							{
								if ( SisEliminarFicheroExt ( p_cRutaNorm, fndfildatObj.cFileName ) == 0 )
								{
									iRes = 0;
								}
							}
						}
						iResBusq = FindNextFile ( hBusqueda, &fndfildatObj );
					}
					if ( ( iResBusq == 0 ) && ( GetLastError () !=  ERROR_NO_MORE_FILES ) )
					{
						iRes = 0;
					}
					FindClose ( hBusqueda );
				}
				else
				{
					iRes = 0;
				}
				MemLiberar ( (void **) &p_cMascBusqueda );
			}
			else
			{
				iRes = 0;
			}

#		  else

			p_dirInfo = opendir ( p_cRutaNorm );
			if ( ES_VALIDO ( p_dirInfo ) )
			{
				iRes = 1;
				p_directInfo = readdir ( p_dirInfo );
				while ( ES_VALIDO ( p_directInfo ) )
				{
					if ( p_directInfo->d_name [ 0 ] != '.' )
					{
						if ( SisExisteFicheroExt ( p_cRutaNorm, p_directInfo->d_name ) == 1 )
						{
							if ( SisEliminarFicheroExt ( p_cRutaNorm, p_directInfo->d_name ) == 0 )
							{
								iRes = 0;
							}
						}
					}
					p_directInfo = readdir ( p_dirInfo );
				}
				closedir ( p_dirInfo );
			}
			else
			{
				iRes = 0;
			}

#		  endif
			MemLiberarCadena ( &p_cRutaNorm );
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

int SisVaciarDirectorioExt ( const char * p_cDirectorio, const char * p_cSubdirectorio )
{
	int		iRes;
	char *	p_cRuta;

	p_cRuta = SisComponerRuta ( p_cDirectorio, p_cSubdirectorio,0 );
	if ( ES_VALIDO ( p_cRuta ) )
	{
		iRes = SisVaciarDirectorio ( p_cRuta );
		MemLiberar ( (void **) &p_cRuta );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SisCopiarFichero ( const char * p_cRutaOrig, const char * p_cRutaDest )
{
	int		iRes;
	char *	p_cRutaOrigNorm;
	char *	p_cRutaDestNorm;

	if ( SisExisteFichero ( p_cRutaOrig ) == 1 ) 
	{
		p_cRutaOrigNorm = SisRutaEstiloSistema ( p_cRutaOrig );
		p_cRutaDestNorm = SisRutaEstiloSistema ( p_cRutaDest );
		if ( ES_VALIDO ( p_cRutaOrigNorm ) && ES_VALIDO ( p_cRutaDestNorm ) )
		{	
			SisEliminarFichero ( p_cRutaDestNorm );
#		  if ( defined ( WIN ) )
			if ( CopyFile ( (LPCSTR) p_cRutaOrigNorm, (LPCSTR) p_cRutaDestNorm, TRUE ) != 0 )		
#		  else
			FILE *		p_fOrig;
			FILE *		p_fDest;
			char		c;

			p_fOrig = fopen ( p_cRutaOrigNorm, "rb" );
			p_fDest = fopen ( p_cRutaDestNorm, "wb" );
			if ( ES_VALIDO ( p_fOrig ) && ES_VALIDO ( p_fDest ) )
			{
				int iFin = 1;
				while ( iFin == 0 )
				{
					fread ( (void *) &c, 1, sizeof ( char ), p_fOrig );
					if ( feof ( p_fOrig ) == 0 )
					{
						fwrite ( (void *) &c, 1, sizeof ( char ), p_fDest );
					}
					else
					{
						iFin = 1;
					}
				}
				iRes = 1;
			}
			else
			{
				iRes = 0;
			}
			if ( ES_VALIDO ( p_fOrig ) ) 
			{
				fclose ( p_fOrig );
			}
			if ( ES_VALIDO ( p_fDest ) ) 
			{
				fclose ( p_fDest );
			}
			if ( iRes == 1 )
#		  endif
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
		MemLiberarCadena ( &p_cRutaOrigNorm );
		MemLiberarCadena ( &p_cRutaDestNorm );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SisCopiarFicheroExt ( const char * p_cDirOrig, const char * p_cFicOrig, const char * p_cDirDest, const char * p_cFicDest, int iEliminar )
{
	int		iRes;
	char *	p_cRutaOrig;
	char *	p_cRutaDest;

	if ( ES_VALIDO ( p_cDirOrig ) && ES_VALIDO ( p_cFicOrig ) && ES_VALIDO ( p_cDirDest ) )
	{
		p_cRutaOrig = SisComponerRuta ( p_cDirOrig, p_cFicOrig, 0 );
		if ( ES_VALIDO ( p_cFicDest ) )
		{
			p_cRutaDest = SisComponerRuta ( p_cDirDest, p_cFicDest, 0 );
		}
		else
		{
			p_cRutaDest = SisComponerRuta ( p_cDirDest, p_cFicOrig, 0 );
		}
		if ( ES_VALIDO ( p_cRutaOrig ) && ES_VALIDO ( p_cRutaDest ) )
		{
			iRes = SisCopiarFichero ( p_cRutaOrig, p_cRutaDest );
			if ( ( iRes == 1 ) && ( iEliminar == 1 ) )
			{
				SisEliminarFichero ( p_cRutaOrig );
			}
			MemLiberar ( (void **) &p_cRutaOrig );
			MemLiberar ( (void **) &p_cRutaDest );
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

int SisMoverFichero ( const char * p_cRutaOrig, const char * p_cRutaDest, int iEliminar )
{
	int		iRes;
	char *	p_cRutaOrigNorm;
	char *	p_cRutaDestNorm;

	if ( SisExisteFichero ( p_cRutaOrig ) == 1 ) 
	{
		if ( iEliminar == 1 )
		{
			SisEliminarFichero ( p_cRutaDest );
		}
		p_cRutaOrigNorm = SisRutaEstiloSistema ( p_cRutaOrig );
		p_cRutaDestNorm = SisRutaEstiloSistema ( p_cRutaDest );
		if ( ES_VALIDO ( p_cRutaOrigNorm ) && ES_VALIDO ( p_cRutaDestNorm ) )
		{	
#		  if ( defined ( WIN ) )
			if ( MoveFile ( (LPCSTR) p_cRutaOrigNorm, (LPCSTR) p_cRutaDestNorm ) != 0 )		
#		  else
			if ( rename ( p_cRutaOrigNorm, p_cRutaDestNorm ) == 0 )
#		  endif
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
		MemLiberarCadena ( &p_cRutaOrigNorm );
		MemLiberarCadena ( &p_cRutaDestNorm );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

/*
DWORD GetFileSize(
  HANDLE hFile,  // handle of file to get size of
  LPDWORD lpFileSizeHigh 
                 // pointer to high-order word for file size
);

DWORD GetFileType(
  HANDLE hFile   // file handle
);
 
FILE_TYPE_UNKNOWN The type of the specified file is unknown. 
FILE_TYPE_DISK The specified file is a disk file. 
FILE_TYPE_CHAR The specified file is a character file, typically an LPT device or a console. 
FILE_TYPE_PIPE The specified file is either a named or anonymous pipe. 

BOOL GetFileAttributesEx(
  LPCTSTR lpFileName,        // pointer to string that specifies a 
                             // file or directory
  GET_FILEEX_INFO_LEVELS fInfoLevelId, 
                             // value that specifies the type of 
                             // attribute information to obtain
  LPVOID lpFileInformation   // pointer to buffer to receive 
                             // attribute information
);

typedef enum _GET_FILEEX_INFO_LEVELS { 
    GetFileExInfoStandard 
} GET_FILEEX_INFO_LEVELS ; 


BOOL GetFileInformationByHandle(
  HANDLE hFile,                                  // handle of file 
  LPBY_HANDLE_FILE_INFORMATION lpFileInformation // pointer to structure
);
 
typedef struct _BY_HANDLE_FILE_INFORMATION { // bhfi 
    DWORD    dwFileAttributes; 
    FILETIME ftCreationTime; 
    FILETIME ftLastAccessTime; 
    FILETIME ftLastWriteTime; 
    DWORD    dwVolumeSerialNumber; 
    DWORD    nFileSizeHigh; 
    DWORD    nFileSizeLow; 
    DWORD    nNumberOfLinks; 
    DWORD    nFileIndexHigh; 
    DWORD    nFileIndexLow; 
} BY_HANDLE_FILE_INFORMATION; 
 

 
*/

int SisMoverFicheroExt ( const char * p_cDirOrig, const char * p_cFicOrig, const char * p_cDirDest, const char * p_cFicDest, int iEliminar )
{
	int		iRes;
	char *	p_cRutaOrig;
	char *	p_cRutaDest;

	if ( ES_VALIDO ( p_cDirOrig ) && ES_VALIDO ( p_cFicOrig ) && ES_VALIDO ( p_cDirDest ) )
	{
		p_cRutaOrig = SisComponerRuta ( p_cDirOrig, p_cFicOrig, 0 );
		if ( ES_VALIDO ( p_cFicDest ) )
		{
			p_cRutaDest = SisComponerRuta ( p_cDirDest, p_cFicDest, 0 );
		}
		else
		{
			p_cRutaDest = SisComponerRuta ( p_cDirDest, p_cFicOrig, 0 );
		}
		if ( ES_VALIDO ( p_cRutaOrig ) && ES_VALIDO ( p_cRutaDest ) )
		{
			iRes = SisMoverFichero ( p_cRutaOrig, p_cRutaDest, iEliminar );
			MemLiberar ( (void **) &p_cRutaOrig );
			MemLiberar ( (void **) &p_cRutaDest );
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

// PENDIENTE: UNIX/Linux
int SisRutaComprimida ( const char * p_cRuta )
{
	int		iRes;
	char *	p_cRutaNorm;

# if ( defined ( WIN ) )
	DWORD		dwAtributos;
# else
	//struct stat statInfo;
# endif

	p_cRutaNorm = SisRutaEstiloSistema ( p_cRuta );
	if ( ES_VALIDO ( p_cRutaNorm ) )
	{	
#	 if ( defined ( WIN ) )
		dwAtributos = GetFileAttributes ( p_cRutaNorm );
		if ( dwAtributos == INVALID_FILE_ATTRIBUTES )
		{
			iRes = 0;
		}
		else 
		{
			if ( ( dwAtributos  & FILE_ATTRIBUTE_COMPRESSED ) == FILE_ATTRIBUTE_COMPRESSED )
			{
				iRes = 1;
			}
			else
			{
				iRes = 0;
			}
		}

#	 else
	/*
		memset ( &statInfo, 0, sizeof(struct stat) );
		if ( stat ( p_cRutaNorm, &statInfo ) != 0 )
		{
			  iRes = 0;
		}
		else 
		{
			if ( ( statInfo.st_mode & S_IFDIR ) == S_IFDIR )
			{
				iRes = 1;
			}
			else
			{
				iRes = 0;
			}
		}
	*/
# endif
		MemLiberarCadena ( &p_cRutaNorm );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

// PENDIENTE: UNIX/Linux
int SisRutaEncriptada ( const char * p_cRuta )
{
	int		iRes;
	char *	p_cRutaNorm;

# if ( defined ( WIN ) )
	DWORD		dwAtributos;
# else
	//struct stat statInfo;
# endif

	p_cRutaNorm = SisRutaEstiloSistema ( p_cRuta );
	if ( ES_VALIDO ( p_cRutaNorm ) )
	{	
#	 if ( defined ( WIN ) )

		dwAtributos = GetFileAttributes ( p_cRutaNorm );
		if ( dwAtributos == INVALID_FILE_ATTRIBUTES )
		{
			iRes = 0;
		}
		else 
		{
			if ( ( dwAtributos  & FILE_ATTRIBUTE_ENCRYPTED ) == FILE_ATTRIBUTE_ENCRYPTED )
			{
				iRes = 1;
			}
			else
			{
				iRes = 0;
			}
		}

#	 else
	/*
		memset ( &statInfo, 0, sizeof(struct stat) );
		if ( stat ( p_cRutaNorm, &statInfo ) != 0 )
		{
			  iRes = 0;
		}
		else 
		{
			if ( ( statInfo.st_mode & S_IFDIR ) == S_IFDIR )
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
		iRes = 1;
	}
	*/
		iRes = 0;
#	 endif
		MemLiberarCadena ( &p_cRutaNorm );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

// PENDIENTE: UNIX/Linux
int SisRutaOculta ( const char * p_cRuta )
{
	int		iRes;
	char *	p_cRutaNorm;

# if ( defined ( WIN ) )
	DWORD		dwAtributos;
# else
	//struct stat statInfo;
# endif

	p_cRutaNorm = SisRutaEstiloSistema ( p_cRuta );
	if ( ES_VALIDO ( p_cRutaNorm ) )
	{	
#	 if ( defined ( WIN ) )

		dwAtributos = GetFileAttributes ( p_cRutaNorm );
		if ( dwAtributos == INVALID_FILE_ATTRIBUTES )
		{
			iRes = 0;
		}
		else 
		{
			if ( ( dwAtributos  & FILE_ATTRIBUTE_HIDDEN ) == FILE_ATTRIBUTE_HIDDEN )
			{
				iRes = 1;
			}
			else
			{
				iRes = 0;
			}
		}

#	 else
	/*
		memset ( &statInfo, 0, sizeof(struct stat) );
		if ( stat ( p_cRutaNorm, &statInfo ) != 0 )
		{
			  iRes = 0;
		}
		else 
		{
			if ( ( statInfo.st_mode & S_IFDIR ) == S_IFDIR )
			{
				iRes = 1;
			}
			else
			{
				iRes = 0;
			}
		}
	*/
		iRes = 0;
#	 endif
		MemLiberarCadena ( &p_cRutaNorm );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

// PENDIENTE: UNIX/Linux
int SisFicheroEsAccesible ( const char * p_cRuta )
{
	int		iRes;
	char *	p_cRutaNorm;

# if ( defined ( WIN ) )
	DWORD		dwAtributos;
# else
	//struct stat statInfo;
# endif

	p_cRutaNorm = SisRutaEstiloSistema ( p_cRuta );
	if ( ES_VALIDO ( p_cRutaNorm ) )
	{	
#	 if ( defined ( WIN ) )
		dwAtributos = GetFileAttributes ( p_cRutaNorm );
		if ( dwAtributos == INVALID_FILE_ATTRIBUTES )
		{
			iRes = 0;
		}
		else 
		{
			if ( ( dwAtributos  & FILE_ATTRIBUTE_OFFLINE ) == FILE_ATTRIBUTE_OFFLINE )
			{
				iRes = 0;
			}
			else
			{
				iRes = 1;
			}
		}

# else
	/*
		memset ( &statInfo, 0, sizeof(struct stat) );
		if ( stat ( p_cRutaNorm, &statInfo ) != 0 )
		{
			  iRes = 0;
		}
		else 
		{
			if ( ( statInfo.st_mode & S_IFDIR ) == S_IFDIR )
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
		iRes = 1;
	}
	*/
		iRes = 0;
#	 endif
		MemLiberarCadena ( &p_cRutaNorm );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

// PENDIENTE: UNIX/Linux
int SisRutaDeSoloLectura ( const char * p_cRuta )
{
	int		iRes;
	char *	p_cRutaNorm;

# if ( defined ( WIN ) )
	DWORD		dwAtributos;
# else
	//struct stat statInfo;
# endif

	p_cRutaNorm = SisRutaEstiloSistema ( p_cRuta );
	if ( ES_VALIDO ( p_cRutaNorm ) )
	{	
#	 if ( defined ( WIN ) )
		dwAtributos = GetFileAttributes ( p_cRutaNorm );
		if ( dwAtributos == INVALID_FILE_ATTRIBUTES )
		{
			iRes = 0;
		}
		else 
		{
			if ( ( dwAtributos  & FILE_ATTRIBUTE_READONLY ) == FILE_ATTRIBUTE_READONLY )
			{
				iRes = 1;
			}
			else
			{
				iRes = 0;
			}
		}

#	 else
	/*
		memset ( &statInfo, 0, sizeof(struct stat) );
		if ( stat ( p_cRutaNorm, &statInfo ) != 0 )
		{
			  iRes = 0;
		}
		else 
		{
			if ( ( statInfo.st_mode & S_IFDIR ) == S_IFDIR )
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
		iRes = 1;
	}
	*/
		iRes = 0;
#	 endif
		MemLiberarCadena ( &p_cRutaNorm );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

// PENDIENTE: UNIX/Linux
int SisRutaDelSistema ( const char * p_cRuta )
{
	int		iRes;
	char *	p_cRutaNorm;

# if ( defined ( WIN ) )
	DWORD		dwAtributos;
# else
	//struct stat statInfo;
# endif

	p_cRutaNorm = SisRutaEstiloSistema ( p_cRuta );
	if ( ES_VALIDO ( p_cRutaNorm ) )
	{	
#	 if ( defined ( WIN ) )
		dwAtributos = GetFileAttributes ( p_cRutaNorm );
		if ( dwAtributos == INVALID_FILE_ATTRIBUTES )
		{
			iRes = 0;
		}
		else 
		{
			if ( ( dwAtributos  & FILE_ATTRIBUTE_SYSTEM ) == FILE_ATTRIBUTE_SYSTEM )
			{
				iRes = 1;
			}
			else
			{
				iRes = 0;
			}
		}

#	 else
	/*
		memset ( &statInfo, 0, sizeof(struct stat) );
		if ( stat ( p_cRutaNorm, &statInfo ) != 0 )
		{
			  iRes = 0;
		}
		else 
		{
			if ( ( statInfo.st_mode & S_IFDIR ) == S_IFDIR )
			{
				iRes = 1;
			}
			else
			{
				iRes = 0;
			}
		}
	}
	*/
		iRes = 0;
#	 endif
		MemLiberarCadena ( &p_cRutaNorm );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

// PENDIENTE: UNIX/Linux
int SisFicheroEsTemporal ( const char * p_cRuta )
{
	int		iRes;
	char *	p_cRutaNorm;

# if ( defined ( WIN ) )
	DWORD		dwAtributos;
# else
	//struct stat statInfo;
# endif

	p_cRutaNorm = SisRutaEstiloSistema ( p_cRuta );
	if ( ES_VALIDO ( p_cRutaNorm ) )
	{	
#	 if ( defined ( WIN ) )
		dwAtributos = GetFileAttributes ( p_cRutaNorm );
		if ( dwAtributos == INVALID_FILE_ATTRIBUTES )
		{
			iRes = 0;
		}
		else 
		{
			if ( ( dwAtributos  & FILE_ATTRIBUTE_TEMPORARY ) == FILE_ATTRIBUTE_TEMPORARY )
			{
				iRes = 1;
			}
			else
			{
				iRes = 0;
			}
		}

#	 else
	/*
		memset ( &statInfo, 0, sizeof(struct stat) );
		if ( stat ( p_cRutaNorm, &statInfo ) != 0 )
		{
			  iRes = 0;
		}
		else 
		{
			if ( ( statInfo.st_mode & S_IFDIR ) == S_IFDIR )
			{
				iRes = 1;
			}
			else
			{
				iRes = 0;
			}
		}
	*/
		iRes = 0;
#	 endif
		MemLiberarCadena ( &p_cRutaNorm );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

// PENDIENTE: UNIX/Linux
int SisFicheroAsociadoAAplicacion ( const char * p_cRuta )
{
	int		iRes;
	char *	p_cRutaNorm;

# if ( defined ( WIN ) )
	DWORD		dwAtributos;
# else
	//struct stat statInfo;
# endif

	p_cRutaNorm = SisRutaEstiloSistema ( p_cRuta );
	if ( ES_VALIDO ( p_cRutaNorm ) )
	{	
#	 if ( defined ( WIN ) )
		dwAtributos = GetFileAttributes ( p_cRutaNorm );
		if ( dwAtributos == INVALID_FILE_ATTRIBUTES )
		{
			iRes = 0;
		}
		else 
		{
			if ( ( dwAtributos  & FILE_ATTRIBUTE_REPARSE_POINT ) == FILE_ATTRIBUTE_REPARSE_POINT )
			{
				iRes = 1;
			}
			else
			{
				iRes = 0;
			}
		}

#	 else
	// �Utilizar el comando du -h?
		iRes = 0;
#	 endif
		MemLiberarCadena ( &p_cRutaNorm );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SisFicheroConOptimizacionEspacial ( const char * p_cRuta )
{
	int		iRes;
	char *	p_cRutaNorm;

# if ( defined ( WIN ) )
	DWORD		dwAtributos;
# else
	//struct stat statInfo;
# endif

	p_cRutaNorm = SisRutaEstiloSistema ( p_cRuta );
	if ( ES_VALIDO ( p_cRutaNorm ) )
	{	
#	 if ( defined ( WIN ) )
		dwAtributos = GetFileAttributes ( p_cRutaNorm );
		if ( dwAtributos == INVALID_FILE_ATTRIBUTES )
		{
			iRes = 0;
		}
		else 
		{
			if ( ( dwAtributos  & FILE_ATTRIBUTE_SPARSE_FILE ) == FILE_ATTRIBUTE_SPARSE_FILE )
			{
				iRes = 1;
			}
			else
			{
				iRes = 0;
			}
		}
#	 else
	// Figura de Windows:
		iRes = 0;
#	 endif
		MemLiberarCadena ( &p_cRutaNorm );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SisRutaDesactivarModoSoloLectura ( const char * p_cRuta )
{
	int		iRes;
	char *	p_cRutaNorm;

# if ( defined ( WIN ) )
	DWORD		dwAtributos;
	DWORD		dwMascara;
# else
	//struct stat statInfo;
# endif

	p_cRutaNorm = SisRutaEstiloSistema ( p_cRuta );
	if ( ES_VALIDO ( p_cRutaNorm ) )
	{	
#	 if ( defined ( WIN ) )
		dwAtributos = GetFileAttributes ( p_cRutaNorm );
		if ( dwAtributos == INVALID_FILE_ATTRIBUTES )
		{
			iRes = 0;
		}
		else 
		{
			dwMascara = FILE_ATTRIBUTE_READONLY;
			dwMascara = 0xFFFFFFFF ^ dwMascara;
			dwAtributos = dwAtributos & dwMascara;
			if ( SetFileAttributes ( p_cRuta, dwAtributos ) != 0 )
			{
				iRes = 1;
			}
			else
			{
				iRes = 0;
			}
		}

#	 else
	/*
		memset ( &statInfo, 0, sizeof(struct stat) );
		if ( stat ( p_cRutaNorm, &statInfo ) != 0 )
		{
			  iRes = 0;
		}
		else 
		{
			if ( ( statInfo.st_mode & S_IFDIR ) == S_IFDIR )
			{
				iRes = 1;
			}
			else
			{
				iRes = 0;
			}
		}
	*/
		iRes = 0;
#	 endif
		MemLiberarCadena ( &p_cRutaNorm );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SisEsFicheroC ( const char * p_cRuta )
{
	int		iRes;
	char *	p_cFichero;
	char *	p_cExt;

	p_cFichero = SisRutaFichero ( p_cRuta );
	if ( ES_VALIDO ( p_cFichero ) )
	{
		p_cExt = SisFicheroExtension ( p_cFichero );
		if ( ES_VALIDO ( p_cExt ) )
		{
			if ( ( CadEsIgual ( p_cExt, EXT_FIC_CABECERA_C ) == 1 ) ||
				 ( CadEsIgual ( p_cExt, EXT_FIC_CODIGO_C ) == 1 ) ||
				 ( CadEsIgual ( p_cExt, EXT_FIC_CODIGO_C_2 ) == 1 ) ||
				 ( CadEsIgual ( p_cExt, EXT_FIC_CODIGO_C_3 ) == 1 ) ||
				 ( CadEsIgual ( p_cExt, EXT_FIC_CODIGO_C_4 ) == 1 ) )
			{
				iRes = 1;
			}
			else
			{	
				iRes = 0;
			}
			MemLiberar ( (void **) &p_cExt );
		}
		else
		{
			iRes = 0;
		}
		MemLiberar ( (void **) &p_cFichero );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SisEsFicheroCodigoC ( const char * p_cRuta )
{
	int		iRes;
	char *	p_cFichero;
	char *	p_cExt;

	p_cFichero = SisRutaFichero ( p_cRuta );
	if ( ES_VALIDO ( p_cFichero ) )
	{
		p_cExt = SisFicheroExtension ( p_cFichero );
		if ( ES_VALIDO ( p_cExt ) )
		{
			if ( ( CadEsIgual ( p_cExt,  EXT_FIC_CODIGO_C ) == 1 ) ||
				 ( CadEsIgual ( p_cExt, EXT_FIC_CODIGO_C_2 ) == 1 ) ||
				 ( CadEsIgual ( p_cExt, EXT_FIC_CODIGO_C_3 ) == 1 ) ||
				 ( CadEsIgual ( p_cExt, EXT_FIC_CODIGO_C_4 ) == 1 ) )
			{
				iRes = 1;
			}
			else
			{	
				iRes = 0;
			}
			MemLiberar ( (void **) &p_cExt );
		}
		else
		{
			iRes = 0;
		}
		MemLiberar ( (void **) &p_cFichero );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SisEsFicheroCabeceraC ( const char * p_cRuta )
{
	int		iRes;
	char *	p_cFichero;
	char *	p_cExt;

	p_cFichero = SisRutaFichero ( p_cRuta );
	if ( ES_VALIDO ( p_cFichero ) )
	{
		p_cExt = SisFicheroExtension ( p_cFichero );
		if ( ES_VALIDO ( p_cExt ) )
		{
			if ( CadEsIgual ( p_cExt, EXT_FIC_CABECERA_C ) == 1 )
			{
				iRes = 1;
			}
			else
			{	
				iRes = 0;
			}
			MemLiberar ( (void **) &p_cExt );
		}
		else
		{
			iRes = 0;
		}
		MemLiberar ( (void **) &p_cFichero );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SisEsFicheroXML ( const char * p_cRuta )
{
	int		iRes;
	char *	p_cFichero;
	char *	p_cExt;

	p_cFichero = SisRutaFichero ( p_cRuta );
	if ( ES_VALIDO ( p_cFichero ) )
	{
		p_cExt = SisFicheroExtension ( p_cFichero );
		if ( ES_VALIDO ( p_cExt ) )
		{
			if ( CadEsIgual ( p_cExt, EXT_FIC_XML ) == 1 ) 
			{
				iRes = 1;
			}
			else
			{	
				iRes = 0;
			}
			MemLiberar ( (void **) &p_cExt );
		}
		else
		{
			iRes = 0;
		}
		MemLiberar ( (void **) &p_cFichero );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SisEsFicheroHTML ( const char * p_cRuta )
{
	int		iRes;
	char *	p_cFichero;
	char *	p_cExt;

	p_cFichero = SisRutaFichero ( p_cRuta );
	if ( ES_VALIDO ( p_cFichero ) )
	{
		p_cExt = SisFicheroExtension ( p_cFichero );
		if ( ES_VALIDO ( p_cExt ) )
		{
			if ( ( CadEsIgual ( p_cExt, EXT_FIC_HTML ) == 1 ) ||
				 ( CadEsIgual ( p_cExt,  EXT_FIC_HTML_2 ) == 1 ) )
			{
				iRes = 1;
			}
			else
			{	
				iRes = 0;
			}
			MemLiberar ( (void **) &p_cExt );
		}
		else
		{
			iRes = 0;
		}
		MemLiberar ( (void **) &p_cFichero );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SisEsFicheroSHP ( const char * p_cRuta )
{
	int		iRes;
	char *	p_cFichero;
	char *	p_cExt;

	p_cFichero = SisRutaFichero ( p_cRuta );
	if ( ES_VALIDO ( p_cFichero ) )
	{
		p_cExt = SisFicheroExtension ( p_cFichero );
		if ( ES_VALIDO ( p_cExt ) )
		{
			if ( CadEsIgual ( p_cExt, EXT_FIC_SHAPE ) == 1 )
			{
				iRes = 1;
			}
			else
			{	
				iRes = 0;
			}
			MemLiberar ( (void **) &p_cExt );
		}
		else
		{
			iRes = 0;
		}
		MemLiberar ( (void **) &p_cFichero );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SisEsFicheroDBF ( const char * p_cRuta )
{
	int		iRes;
	char *	p_cFichero;
	char *	p_cExt;

	p_cFichero = SisRutaFichero ( p_cRuta );
	if ( ES_VALIDO ( p_cFichero ) )
	{
		p_cExt = SisFicheroExtension ( p_cFichero );
		if ( ES_VALIDO ( p_cExt ) )
		{
			if ( CadEsIgual ( p_cExt, EXT_FIC_DBASE ) == 1 )
			{
				iRes = 1;
			}
			else
			{	
				iRes = 0;
			}
			MemLiberar ( (void **) &p_cExt );
		}
		else
		{
			iRes = 0;
		}
		MemLiberar ( (void **) &p_cFichero );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

char * SisResolverDirectorioRelativo ( const char * p_cRutaBase, const char * p_cRutaRelativa )
{
	char *	p_cRutaBaseCopia;
	char *	p_cRutaRelativaCopia;
	char *	p_cResultado;
	char *	p_cRes;
	char **	p_p_cPartes;
	char *	p_cToken;
	int		iCount;
	int		iCountRel;
	int		iPartes;
	int		iPartesRel;
	int 	iFinBucle;
	int 	iWindows;
	char	cSep;
	char 	cUnidad;

	if ( ( SisEsRutaAbsoluta ( p_cRutaBase ) == 1 ) && 
			( SisEsRutaRelativa ( p_cRutaRelativa ) == 1 ) )
	{
		if ( SisRutaEsEstiloWindows ( p_cRutaBase ) == 1 ) 
		{
			p_cRutaBaseCopia = SisRutaEstiloWindows ( p_cRutaBase );
			p_cRutaRelativaCopia = SisRutaEstiloWindows ( p_cRutaRelativa );
			iWindows = 1;
			cSep = '\\';
			cUnidad = CadCaracter ( p_cRutaBaseCopia, 0 );
			CadEliminarPrimerosCaracteres ( p_cRutaBaseCopia, 2 );
		}
		else
		{
			p_cRutaBaseCopia = SisRutaEstiloUnix ( p_cRutaBase );
			p_cRutaRelativaCopia = SisRutaEstiloUnix ( p_cRutaRelativa );
			iWindows = 0;
			cSep = '/';
		}
		if ( ES_VALIDO ( p_cRutaBaseCopia ) && ES_VALIDO ( p_cRutaRelativaCopia ) )
		{
			if ( ( CadEmpiezaPorCaracter ( p_cRutaBaseCopia, cSep ) == 1 ) &&
				 ( CadEmpiezaPorCaracter ( p_cRutaRelativaCopia, '.' ) == 1 ) )
			{
				p_cResultado = CadCrear ( MAXPATHLEN - 1 );
				if ( iWindows == 1 )
				{
					CadConcatenarConFormato ( p_cResultado, "%c:", cUnidad );
				}
				p_p_cPartes = (char **) MemReservar ( MAX_PARTES * sizeof ( char * ) );
				iPartes = CadNumPalabrasSep ( p_cRutaBaseCopia, cSep );
				for ( iCount = 0; iCount < iPartes; iCount = iCount + 1 )
				{
					p_p_cPartes [ iCount ] = CadPalabraSep ( p_cRutaBaseCopia, iCount, cSep );
				}
				
				iPartesRel = CadNumPalabrasSep ( p_cRutaRelativaCopia, cSep );
				iCountRel = 0; 
				iFinBucle = 0;
				while ( ( iCountRel < iPartesRel ) && ( iFinBucle == 0 ) )
				{
					p_cToken = CadPalabraSep ( p_cRutaRelativaCopia, iCountRel, cSep );
					if ( CadEsIgual ( p_cToken, ".." ) == 1 )
					{
						if ( iCount > 0 )
						{
							iCount = iCount - 1;
						}
						iCountRel = iCountRel + 1 ;
					}
					else if ( CadEsIgual ( p_cToken, "." ) == 0 )
					{
						iFinBucle = 1;
					}
					else 
					{
						iCountRel = iCountRel + 1 ;
					}
					MemLiberar ( ( void ** ) &p_cToken );
				}
				for ( int i = 0; i < iPartes; i = i + 1 )
				{
					if ( i < iCount )
					{
						CadConcatenarCaracter ( p_cResultado, cSep );
						CadConcatenar ( p_cResultado, p_p_cPartes [ i ] );
					}
					MemLiberar ( ( void ** ) &(p_p_cPartes [ i ]) );
				}
				MemLiberar ( ( void ** ) &p_p_cPartes );
				while ( iCountRel < iPartesRel )
				{
					p_cToken = CadPalabraSep ( p_cRutaRelativaCopia, iCountRel, cSep );
					CadConcatenarCaracter ( p_cResultado, cSep );
					CadConcatenar ( p_cResultado, p_cToken );
					MemLiberar ( ( void ** ) &p_cToken );
					iCountRel = iCountRel + 1 ;
				}
				if ( CadLongitud ( p_cResultado ) == 0 )
				{
					CadConcatenarCaracter ( p_cResultado, cSep );
				}
				p_cRes = p_cResultado;
			}
			else
			{
				ERROR_ESTABLECER ( ERR_PARAMETROS );
				p_cRes = NULL;
			}
		}
		else
		{
			p_cRes = NULL;
		}
		MemLiberar ( ( void ** ) &p_cRutaBaseCopia );
		MemLiberar ( ( void ** ) &p_cRutaRelativaCopia );
	}
	else
	{
		ERROR_ESTABLECER ( ERR_PARAMETROS );
		p_cRes = NULL;
	}
	return ( p_cRes );
}


char * SisDirectorioRaiz ()
{
#if ( defined ( WIN ) )
	return ( CadDuplicar ( "C:\\" ) );
#else
	return ( CadDuplicar ( "/" ) );
#endif
}

#if ( defined ( WIN ) )
char * SisDirectorioRaizExt ( char cUnidad )
{
#if ( defined ( CYGWIN ) )
	return ( CadCrearConFormato ( "/cygdrive/%c", cUnidad ) );
#else
	return ( CadCrearConFormato ( "%c:\\", cUnidad ) );
#endif
}
#endif

char SisSeparadorRutaFicheros ()
{
	return ( SIS_SEPARADOR_PATH );
}

