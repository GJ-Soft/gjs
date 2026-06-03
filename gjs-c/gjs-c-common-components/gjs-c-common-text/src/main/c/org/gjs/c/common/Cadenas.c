/******************************************************************************/
/*                                Cadenas.cpp                                 */
/*----------------------------------------------------------------------------*/
/* Librería:  GTexto                                                          */
/* Versión:   1.0.0                                                           */
/* Fecha:     30/06/2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Fichero de código fuente que contiene la implementación de las rutinas     */
/* de carácter general de manejo de cadenas.                                  */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#include "TextoConfig.h"
#include "Cadenas.h"
#include "ExpresionesRegulares.h"





static char * CadComponerVarArgExt ( char cSep, char cIni, char cFin, va_list valArgumentos );
static char * CadComponerVarArg ( char cSep, va_list valArgumentos );
static int _EsCadenaValida ( char * p_cCad );



char * CadCrearExt ( int iTam, char cCarRelleno )
{
	char * p_cRes;

	p_cRes = CadCrear ( iTam );
	CadLimpiarExt ( p_cRes, cCarRelleno, iTam );
	return ( p_cRes );
}

char * CadCrearConFormato ( const char * p_cFormato, ... )
{
	char *		p_cRes;
	va_list		valArgumentos;

	va_start ( valArgumentos,  p_cFormato );
	p_cRes = CadCrearConFormatoExt ( p_cFormato, valArgumentos );
	va_end ( valArgumentos );
	return ( p_cRes );
}

char * CadCrearConFormatoExt ( const char * p_cFormato, va_list valArgumentos )
{
	char *	p_cRes;
	int		iLong;

	if ( ES_VALIDO ( p_cFormato ) )
	{
		iLong = CAD_MAX_TAM; 
		p_cRes = CadCrear ( iLong );
		if ( ES_VALIDO ( p_cRes ) )
		{
			if ( CadCopiarConFormatoExt ( p_cRes, p_cFormato, valArgumentos ) == 0 )
			{
				MemLiberar ( (void **) &p_cRes );
			}
		}
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

int CadLimpiar ( char * p_cAsciiz )
{
	return ( CadLimpiarExt ( p_cAsciiz, ' ', -1 ) );
}

int CadLimpiarDesde ( char * p_cAsciiz, int iPos )
{
	return ( CadLimpiarDesdeExt ( p_cAsciiz, iPos, ' ', -1 ) );
}

int CadLimpiarHasta ( char * p_cAsciiz, int iPos )
{
	return ( CadLimpiarHastaExt ( p_cAsciiz, iPos, ' ', -1 ) );
}

int CadLimpiarExt ( char * p_cAsciiz, char cRelleno, int iMax )
{
	int iRes;
	int iCar;
	int iLong;

	iLong = CadLongitudSeg ( p_cAsciiz, iMax ); 
	if ( iLong >= 0 ) 
	{
		iRes = 1;
		for ( iCar = 0; iCar < iLong;  iCar = iCar + 1 )  
		{
			p_cAsciiz [ iCar ] = cRelleno;
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int CadLimpiarDesdeExt ( char * p_cAsciiz, int iPos, char cRelleno, int iMax )
{
	int iRes;
	int iCar;
	int iLong;

	iLong = CadLongitudSeg ( p_cAsciiz, iMax ); 
	if ( ( iLong >= 0 ) && ( iMax > 0 ) ) 
	{
		iRes = 1;
		for ( iCar = iPos; iCar < iMax;  iCar = iCar + 1 )  
		{
			p_cAsciiz [ iCar ] = cRelleno;
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int CadLimpiarHastaExt ( char * p_cAsciiz, int iPos, char cRelleno, int iMax )
{
	int iRes;
	int iCar;
	int iLong;

	if ( ( cRelleno == (char) 0 ) && ( iPos > 0 ) )
	{
		CadInicializar ( p_cAsciiz, iMax );
		iRes = 1;
	}
	else
	{
		iLong = CadLongitudSeg ( p_cAsciiz, iMax ); 
		if ( ( iLong >= 0 ) && ( iPos > 0 ) && ( iPos < iMax ) ) 
		{
			iRes = 1;
			for ( iCar = 0; iCar < iPos;  iCar = iCar + 1 )  
			{
				p_cAsciiz [ iCar ] = cRelleno;
			}
		}
		else
		{
			iRes = 0;
		}
	}
	return ( iRes );
}

int CadEstaVacia ( const char * p_cAsciiz )
{
	return ( CadEstaVaciaExt ( p_cAsciiz, -1 ) );
}

int CadEstaVaciaExt ( const char * p_cAsciiz, int iMax )
{
	int iRes;
	int iLong;

	iLong = CadLongitudSeg ( p_cAsciiz, iMax ); 
	if ( iLong <= 0 ) 
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

char CadCaracter ( const char * p_cAsciiz, int iCar )
{
	return ( CadCaracterExt ( p_cAsciiz, iCar, -1 ) ); 
}

int CadEstablecerCaracter ( char * p_cAsciiz, int iCar, char cVal )
{
	return ( CadEstablecerCaracterExt ( p_cAsciiz, iCar, cVal, -1 ) ); 
}

char CadCaracterExt ( const char * p_cAsciiz, int iCar, int iMax )
{
	char	cRes;
	int		iLong;

	iLong = CadLongitudSeg ( p_cAsciiz, iMax ); 
	if ( ( iCar >= 0 ) && ( iCar < iLong ) )
	{
		cRes = p_cAsciiz [ iCar ];
	}
	else
	{
		cRes = (char) 0;
	}
	return ( cRes );
}

int CadEstablecerCaracterExt ( char * p_cAsciiz, int iCar, char cVal, int iMax )
{
	int iRes;
	int iLong;

	iLong = CadLongitudSeg ( p_cAsciiz, iMax ); 
	if ( ( iLong >= 0 ) && ( iCar >= 0 ) &&  ( ( iCar < iLong ) || 
			( ( iCar == iLong ) && ( iMax == -1 ) ) )  && ( cVal != (char)0 ) )
	{
		p_cAsciiz [ iCar ] = cVal;
		if ( iCar == iLong ) 
		{
			p_cAsciiz [ iCar + 1 ] =  (char) 0;
		}
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int CadCopiar ( char * p_cAsciiz1, const char * p_cAsciiz2 )
{
	return ( CadCopiarExt ( p_cAsciiz1, p_cAsciiz2, -1, -1 ) );
}

int CadConcatenar ( char * p_cAsciiz1, const char * p_cAsciiz2 )
{
	return ( CadConcatenarExt ( p_cAsciiz1, p_cAsciiz2, -1, -1 ) );
}

int CadCopiarCaracter ( char * p_cAsciiz1, char cVal )
{
	return ( CadCopiarCaracterExt ( p_cAsciiz1, cVal, -1 ) );
}

int CadConcatenarCaracter ( char * p_cAsciiz1, char cVal )
{
	return ( CadConcatenarCaracterExt ( p_cAsciiz1, cVal, -1 ) );
}

int CadCopiarExt ( char * p_cAsciiz1, const char * p_cAsciiz2, int iMax1, int iMax2 ) 
{
	int iRes;
	int	iCar;
	int iLong1;
	int iLong2;
	int iMax;

	iLong1 = CadLongitudSeg ( p_cAsciiz1, iMax1 ); 
	iLong2 = CadLongitudSeg ( p_cAsciiz2, iMax2 ); 
	if ( ( iLong1 >= 0 ) && ( iLong2 >= 0 ) ) 
	{
		if ( iMax1 < 0 ) 
		{
			iMax = iLong2;
		}
		else
		{
			if ( iLong2 <= iMax1 ) 
			{
				iMax = iLong2;
			}
			else
			{
				iMax = iMax1;
			}
		}
		iRes = 1;
		for ( iCar = 0; iCar < iMax;  iCar = iCar + 1 )  
		{
			p_cAsciiz1 [ iCar ] = p_cAsciiz2 [ iCar ];
		}
		p_cAsciiz1 [ iMax ] = (char) 0;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int CadConcatenarExt ( char * p_cAsciiz1, const char * p_cAsciiz2, int iMax1, int iMax2 ) 
{
	int iRes;
	int	iCar;
	int iLong1;
	int iLong2;
	int iMax;

	iLong1 = CadLongitudSeg ( p_cAsciiz1, iMax1 ); 
	iLong2 = CadLongitudSeg ( p_cAsciiz2, iMax2 ); 
	if ( ( iLong1 >= 0 ) && ( iLong2 > 0 ) && ( ( iMax1 == -1 ) || ( iLong1 < iMax1 ) )  )
	{
		iRes = 1;
		if ( iMax1 > 0 )
		{
			if ( iLong1 + iLong2 < iMax1 )
			{
				iMax = iLong1 + iLong2;
			}
			else
			{
				iMax = iMax1;
			}
		}
		else
		{
			iMax = iLong1 + iLong2;
		}
		for ( iCar = iLong1; iCar < iMax;  iCar = iCar + 1 )  
		{
			p_cAsciiz1 [ iCar ] = p_cAsciiz2 [ iCar - iLong1 ];
		}
		p_cAsciiz1 [ iMax ] = (char) 0;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int CadCopiarCaracterExt ( char * p_cAsciiz1, char cVal, int iMax1 ) 
{
	int iRes;
	int	iCar;
	int iLong1;

	iLong1 = CadLongitudSeg ( p_cAsciiz1, iMax1 ); 
	if ( iLong1 >= 1 ) 
	{
		p_cAsciiz1 [ 0 ] = cVal;
		iRes = 1;
		for ( iCar = 1; iCar < iLong1; iCar = iCar + 1 )  
		{
			p_cAsciiz1 [ iCar ] = (char) 0;
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int CadConcatenarCaracterExt ( char * p_cAsciiz1, char cVal, int iMax1 ) 
{
	int iRes;
	int iLong1;

	iLong1 = CadLongitudSeg ( p_cAsciiz1, iMax1 ); 
	if ( ( iLong1 >= 0 ) && ( ( iLong1 < iMax1 ) || ( iMax1 < 0 ) ) ) 
	{
		iRes = 1;
		p_cAsciiz1 [ iLong1 ] = cVal;
		p_cAsciiz1 [ iLong1 + 1 ] = (char) 0;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int CadCopiarConFormato ( char * p_cAsciiz1, const char * p_cFormato, ... )
{
	int			iRes;
	va_list		valArgumentos;

	va_start ( valArgumentos,  p_cFormato );
	iRes = CadCopiarConFormatoExt ( p_cAsciiz1, p_cFormato, valArgumentos );
	va_end ( valArgumentos );
	return ( iRes );
}

int CadConcatenarConFormato ( char * p_cAsciiz1, const char * p_cFormato, ... )
{
	int			iRes;
	va_list		valArgumentos;

	va_start ( valArgumentos,  p_cFormato );
	iRes = CadConcatenarConFormatoExt ( p_cAsciiz1, p_cFormato, valArgumentos );
	va_end ( valArgumentos );
	return ( iRes );
}

int CadCopiarConFormatoExt ( char * p_cAsciiz1, const char * p_cFormato, va_list valArgumentos )
{
	int			iRes;
	char *		p_cCadena;

	if ( ES_VALIDO ( p_cAsciiz1 ) && ES_VALIDO ( p_cFormato ) )
	{
		p_cCadena = CadCrear ( CAD_TAM_DEFECTO );
		if ( ES_VALIDO ( p_cCadena ) )
		{
			if ( FrmCadena ( p_cCadena, p_cFormato, valArgumentos, CAD_TAM_DEFECTO ) == 1 )
			{
				iRes = CadCopiar ( p_cAsciiz1, p_cCadena );
			}
			else
			{
				iRes = 0;
			}
			MemLiberar ( (void **) &p_cCadena );
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

int CadConcatenarConFormatoExt ( char * p_cAsciiz1, const char * p_cFormato, va_list valArgumentos )
{
	int			iRes;
	char *		p_cCadena;

	if ( ES_VALIDO ( p_cAsciiz1 ) && ES_VALIDO ( p_cFormato ) )
	{
		p_cCadena = CadCrear ( CAD_TAM_DEFECTO );
		if ( ES_VALIDO ( p_cCadena ) )
		{
			if ( FrmCadena ( p_cCadena, p_cFormato, valArgumentos, CAD_TAM_DEFECTO ) == 1 )
			{
				iRes = CadConcatenar ( p_cAsciiz1, p_cCadena );
			}
			else
			{
				iRes = 0;
			}
			MemLiberar ( (void **) &p_cCadena );
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

int CadUniCopiar ( unichar * p_cAsciiz1, const unichar * p_cAsciiz2 )
{
	return ( CadUniCopiarExt ( p_cAsciiz1, p_cAsciiz2, -1, -1 ) );
}

int CadUniConcatenar ( unichar * p_cAsciiz1, const unichar * p_cAsciiz2 )
{
	return ( CadUniConcatenarExt ( p_cAsciiz1, p_cAsciiz2, -1, -1 ) );
}

int CadUniCopiarExt ( unichar * p_ucValor1, const unichar * p_ucValor2, int iMax1, int iMax2 )
{
	int iRes;
	int	iCar;
	int iLong1;
	int iLong2;
	int iMax;

	iLong1 = CadUniLongitudSeg ( p_ucValor1, iMax1 ); 
	iLong2 = CadUniLongitudSeg ( p_ucValor2, iMax2 ); 
	if ( ( iLong1 >= 0 ) && ( iLong2 >= 0 ) ) 
	{
		if ( iMax1 < 0 ) 
		{
			iMax = iLong2;
		}
		else
		{
			if ( iLong2 <= iMax1 ) 
			{
				iMax = iLong2;
			}
			else
			{
				iMax = iMax1;
			}
		}
		iRes = 1;
		for ( iCar = 0; iCar < iMax;  iCar = iCar + 1 )  
		{
			p_ucValor1 [ iCar ] = p_ucValor2 [ iCar ];
		}
		p_ucValor1 [ iMax ] = (unichar) 0;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int CadUniConcatenarExt ( unichar * p_ucValor1, const unichar * p_ucValor2, int iMax1, int iMax2 )
{
	int iRes;
	int	iCar;
	int iLong1;
	int iLong2;
	int iMax;

	iLong1 = CadUniLongitudSeg ( p_ucValor1, iMax1 ); 
	iLong2 = CadUniLongitudSeg ( p_ucValor2, iMax2 ); 
	if ( ( iLong1 >= 0 ) && ( iLong2 >= 0 ) && ( ( iMax1 == -1 ) || ( iLong1 < iMax1 ) )  )
	{
		iRes = 1;
		if ( iMax1 > 0 )
		{
			if ( iLong1 + iLong2 < iMax1 )
			{
				iMax = iLong1 + iLong2;
			}
			else
			{
				iMax = iMax1;
			}
		}
		else
		{
			iMax = iLong1 + iLong2;
		}
		for ( iCar = iLong1; iCar < iMax;  iCar = iCar + 1 )  
		{
			p_ucValor1 [ iCar ] = p_ucValor2 [ iCar - iLong1 ];
		}
		p_ucValor1 [ iMax ] = (unichar) 0;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int CadUniCopiarCadExt ( unichar * p_ucValor1, const char * p_cAsciiz2, int iMax1, int iMax2 )
{
	int iRes;
	int	iCar;
	int iLong1;
	int iLong2;
	int iMax;

	iLong1 = CadUniLongitudSeg ( p_ucValor1, iMax1 ); 
	iLong2 = CadLongitudSeg ( p_cAsciiz2, iMax2 ); 
	if ( ( iLong1 >= 0 ) && ( iLong2 >= 0 ) ) 
	{
		if ( iMax1 < 0 ) 
		{
			iMax = iLong2;
		}
		else
		{
			if ( iLong2 <= iMax1 ) 
			{
				iMax = iLong2;
			}
			else
			{
				iMax = iMax1;
			}
		}
		iRes = 1;
		for ( iCar = 0; iCar < iMax;  iCar = iCar + 1 )  
		{
			p_ucValor1 [ iCar ] = AsciiAUnicode ( p_cAsciiz2 [ iCar ] );
		}
		p_ucValor1 [ iMax ] = (unichar) 0;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int CadUniConcatenarCadExt ( unichar * p_ucValor1, const char * p_cAsciiz2, int iMax1, int iMax2 )
{
	int iRes;
	int	iCar;
	int iLong1;
	int iLong2;
	int iMax;

	iLong1 = CadUniLongitudSeg ( p_ucValor1, iMax1 ); 
	iLong2 = CadLongitudSeg ( p_cAsciiz2, iMax2 ); 
	if ( ( iLong1 >= 0 ) && ( iLong2 >= 0 ) && ( ( iMax1 == -1 ) || ( iLong1 < iMax1 ) )  )
	{
		iRes = 1;
		if ( iMax1 > 0 )
		{
			if ( iLong1 + iLong2 < iMax1 )
			{
				iMax = iLong1 + iLong2;
			}
			else
			{
				iMax = iMax1;
			}
		}
		else
		{
			iMax = iLong1 + iLong2;
		}
		for ( iCar = iLong1; iCar < iMax;  iCar = iCar + 1 )  
		{
			p_ucValor1 [ iCar ] = AsciiAUnicode ( p_cAsciiz2 [ iCar - iLong1 ] );
		}
		p_ucValor1 [ iMax ] = (unichar) 0;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int CadInsertar ( char * p_cAsciiz1, int iPos, const char * p_cAsciiz2 )
{
	return ( CadInsertarExt ( p_cAsciiz1, iPos, p_cAsciiz2, -1, -1 ) ) ;
}

int CadInsertarCaracter ( char * p_cAsciiz1, int iPos, char cVal )
{
	return ( CadInsertarCaracterExt ( p_cAsciiz1, iPos, cVal, -1 ) ) ;
}

int CadEscribir ( char * p_cAsciiz1, int iPos, const char * p_cAsciiz2 )
{
	return ( CadEscribirExt ( p_cAsciiz1, iPos, p_cAsciiz2, -1, -1 ) ) ;
}

int CadEscribirCaracter ( char * p_cAsciiz1, int iPos, char cVal )
{
	return ( CadEscribirCaracterExt ( p_cAsciiz1, iPos, cVal, -1 ) ) ;
}

int CadInsertarExt ( char * p_cAsciiz1, int iPos, const char * p_cAsciiz2, int iMax1, int iMax2 ) 
{
	int iRes;
	int	iCar;
	int iLong1;
	int iLong2;
	int	iLongIns;
	int iMax;

	iLong1 = CadLongitudSeg ( p_cAsciiz1, iMax1 ); 
	iLong2 = CadLongitudSeg ( p_cAsciiz2, iMax2 ); 
	if ( ( iLong1 >= 0 ) && ( iLong2 >= 0 ) && ( iPos >= 0 ) ) 
	{
		if ( iLong2 == 0 )
		{
			iRes = 1;
		}
		else if ( ( iLong1 == 0 ) || ( iPos >= iLong1 ) )
		{
			iRes = CadConcatenarExt ( p_cAsciiz1, p_cAsciiz2, iMax1, iMax2 );
		}
		else 
		{
			if ( iMax1 < 0 ) 
			{
				iMax = iLong1;
			}
			else
			{
				iMax = iMax1;
			}

			if ( iMax2 < 0 ) 
			{
				iLongIns = iLong2;
			}
			else
			{
				iLongIns = iMax2;
			}
			if ( iPos + iLongIns > iMax )
			{
				iLongIns = iMax - iPos;
			}

			iRes = 1;
			for ( iCar = iMax - 1; iCar >= iPos + iLongIns; iCar = iCar - 1 )  
			{
				p_cAsciiz1 [ iCar ] = p_cAsciiz1 [ iCar - iLongIns ];
			}
			for ( iCar = 0; iCar < iLongIns; iCar = iCar + 1 )  
			{
				p_cAsciiz1 [ iPos + iCar ] = p_cAsciiz2 [ iCar ];
			}

			if ( iMax > iLong1 )
			{
				p_cAsciiz1 [ iMax ] = (char)0;
			}
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int CadInsertarCaracterExt ( char * p_cAsciiz1, int iPos, char cVal, int iMax1 ) 
{
	int iRes;
	int	iCar;
	int iLong1;
	int iMax;

	iLong1 = CadLongitudSeg ( p_cAsciiz1, iMax1 ); 
	if ( ( iLong1 >= 0 ) && ( iPos >= 0 ) ) 
	{
		if ( ( iLong1 == 0 ) || ( iPos >= iLong1 ) )
		{
			iRes = CadConcatenarCaracterExt ( p_cAsciiz1, cVal, iMax1 );
		}
		else 
		{
			if ( iMax1 < 0 ) 
			{
				iMax = iLong1;
			}
			else
			{
				iMax = iMax1;
			}

			iRes = 1;
			for ( iCar = iMax - 1; iCar >= iPos ; iCar = iCar - 1 )  
			{
				p_cAsciiz1 [ iCar ] = p_cAsciiz1 [ iCar - 1 ];
			}
			p_cAsciiz1 [ iPos ] = cVal;

			if ( iMax > iLong1 )
			{
				p_cAsciiz1 [ iMax ] = (char)0;
			}
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int CadEscribirExt ( char * p_cAsciiz1, int iPos, const char * p_cAsciiz2, int iMax1, int iMax2 ) 
{
	int iRes;
	int	iCar;
	int iLong1;
	int iLong2;
	int	iLongEsc;

	iLong1 = CadLongitudSeg ( p_cAsciiz1, iMax1 ); 
	iLong2 = CadLongitudSeg ( p_cAsciiz2, iMax2 ); 
	if ( ( iLong1 >= 0 ) && ( iLong2 >= 0 ) && ( iPos >= 0 ) && ( iPos < iLong1 ) ) 
	{
		if ( iLong2 == 0 )
		{
			iRes = 1;
		}
		else 
		{
			if ( iMax2 < 0 ) 
			{
				iLongEsc = iLong2;
			}
			else
			{
				iLongEsc = iMax2;
			}
			if ( iPos + iLongEsc > iLong1 )
			{
				iLongEsc = iLong1 - iPos;
			}

			iRes = 1;
			for ( iCar = 0; iCar < iLongEsc; iCar = iCar + 1 )  
			{
				p_cAsciiz1 [ iPos + iCar ] = p_cAsciiz2 [ iCar ];
			}
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int CadEscribirCaracterExt ( char * p_cAsciiz1, int iPos, char cVal, int iMax1 ) 
{
	int iRes;
	int iLong1;

	iLong1 = CadLongitudSeg ( p_cAsciiz1, iMax1 ); 
	if ( ( iLong1 >= 0 ) && ( iPos >= 0 ) && ( iPos < iLong1 ) ) 
	{
		iRes = 1;
		p_cAsciiz1 [ iPos ] = cVal;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int CadEliminarBlancosLaterales ( char * p_cAsciiz )
{
	return ( CadEliminarBlancosLateralesExt ( p_cAsciiz, -1 ) );
}

int CadEliminarBlancosIzq ( char * p_cAsciiz )
{
	return ( CadEliminarBlancosIzqExt ( p_cAsciiz, -1 ) );
}

int CadEliminarBlancosDer ( char * p_cAsciiz )
{
	return ( CadEliminarBlancosDerExt ( p_cAsciiz, -1 ) );
}

int CadFormatearBlancos ( char * p_cAsciiz )
{
	return ( CadFormatearBlancosExt ( p_cAsciiz, -1 ) );
}

int CadEliminarBlancosLateralesExt ( char * p_cAsciiz, int iMax )
{
	int iRes;

	if ( ( CadEliminarBlancosIzqExt ( p_cAsciiz, iMax ) == 1 ) &&
		 ( CadEliminarBlancosDerExt ( p_cAsciiz, iMax ) == 1 ) )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int CadEliminarBlancosIzqExt ( char * p_cAsciiz, int iMax )
{
	int iRes;
	int iLong;
	int	iCarVal;
	int iPos;

	iLong = CadLongitudSeg ( p_cAsciiz, iMax ); 
	if ( iLong > 0 ) 
	{
		iCarVal = 0;
		while ( ( iCarVal < iLong ) && ( p_cAsciiz [ iCarVal ] == ' ' )  )
		{
			iCarVal = iCarVal + 1;
		}
		if ( iCarVal > 0 )
		{
			for ( iPos = 0; iPos < iLong - iCarVal; iPos = iPos + 1 ) 
			{	
				p_cAsciiz [ iPos ] = p_cAsciiz [ iCarVal + iPos ]; 
			}		
			p_cAsciiz [ iLong - iCarVal ] = (char) 0;
		}
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int CadEliminarBlancosDerExt ( char * p_cAsciiz, int iMax )
{
	int iRes;
	int iLong;
	int	iCarVal;

	iLong = CadLongitudSeg ( p_cAsciiz, iMax ); 
	if ( iLong > 0 ) 
	{
		iCarVal = iLong - 1;
		while ( ( iCarVal >= 0 ) && ( p_cAsciiz [ iCarVal ] == ' ' ) )
		{
			iCarVal = iCarVal - 1;
		}
		p_cAsciiz [ iCarVal + 1 ] = (char) 0;
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int CadFormatearBlancosExt ( char * p_cAsciiz, int iMax )
{
	int iRes;
	int iLong;
	int	iCar;
	int	iCarVal;
	int iBlanco;

	if ( CadEliminarBlancosLateralesExt ( p_cAsciiz, iMax ) == 1 )
	{
		iLong = CadLongitudSeg ( p_cAsciiz, iMax ); 
		iCarVal = 0;
		iBlanco = 0;
		for ( iCar = 0; iCar < iLong; iCar = iCar + 1 )
		{
			if ( p_cAsciiz [ iCar ] == ' ' )
			{
				if ( iBlanco == 0 )
				{
					iBlanco = 1;
					p_cAsciiz [ iCarVal ] = p_cAsciiz [ iCar ];
				}
				else
				{
					continue;
				}
			}
			else
			{
				iBlanco = 0;
				if ( iCarVal != iCar )
				{
					p_cAsciiz [ iCarVal ] = p_cAsciiz [ iCar ];
				}
			}
			iCarVal = iCarVal + 1;
		}
		p_cAsciiz [ iCarVal ] = (char) 0;
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int CadContieneBlancos ( const char * p_cAsciiz )
{
	return ( CadContieneBlancosExt ( p_cAsciiz, -1 ) );
}

int CadContieneTabuladores ( const char * p_cAsciiz )
{
	return ( CadContieneTabuladoresExt ( p_cAsciiz, -1 ) );
}

int CadContieneCaracteresNoImprimibles ( const char * p_cAsciiz )
{
	return ( CadContieneCaracteresNoImprimiblesExt ( p_cAsciiz, -1 ) );
}

int CadContieneCaracteresNoAlfanumericos ( const char * p_cAsciiz )
{
	return ( CadContieneCaracteresNoAlfanumericosExt ( p_cAsciiz, -1 ) );
}

int CadContieneCaracteresNoEstandar ( const char * p_cAsciiz )
{
	return ( CadContieneCaracteresNoEstandarExt ( p_cAsciiz, -1 ) );
}

int CadContieneBlancosExt ( const char * p_cAsciiz, int iMax )
{
	int				iRes;
	int				iLong;
	int				iCar;
	unsigned int	uiVal;

	iLong = CadLongitudSeg ( p_cAsciiz, iMax ); 
	if ( iLong > 0 ) 
	{
		iCar = 0;
		iRes = 0;
		while ( ( iCar < iLong ) && ( iRes == 0 ) ) 
		{
			uiVal = (unsigned int) p_cAsciiz [ iCar ];
			if ( uiVal == 32 ) 
			{
				iRes = 1;
			}
			iCar = iCar + 1;
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int CadContieneTabuladoresExt ( const char * p_cAsciiz, int iMax )
{
	int				iRes;
	int				iLong;
	int				iCar;
	unsigned int	uiVal;

	iLong = CadLongitudSeg ( p_cAsciiz, iMax ); 
	if ( iLong > 0 ) 
	{
		iCar = 0;
		iRes = 0;
		while ( ( iCar < iLong ) && ( iRes == 0 ) ) 
		{
			uiVal = (unsigned int) p_cAsciiz [ iCar ];
			if ( uiVal == 9 ) 
			{
				iRes = 1;
			}
			iCar = iCar + 1;
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int CadContieneCaracteresNoImprimiblesExt ( const char * p_cAsciiz, int iMax )
{
	int				iRes;
	int				iLong;
	int				iCar;
	unsigned int	uiVal;

	iLong = CadLongitudSeg ( p_cAsciiz, iMax ); 
	if ( iLong > 0 ) 
	{
		iCar = 0;
		iRes = 0;
		while ( ( iCar < iLong ) && ( iRes == 0 ) ) 
		{
			uiVal = (unsigned int) p_cAsciiz [ iCar ];
			if ( ( ( uiVal < 32 ) && ( uiVal != 9 ) ) || 
				 ( uiVal == 127 ) )  
			{
				iRes = 1;
			}
			iCar = iCar + 1;
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int CadContieneCaracteresNoAlfanumericosExt ( const char * p_cAsciiz, int iMax )
{
	int				iRes;
	int				iLong;
	int				iCar;
	unsigned int	uiVal;

	iLong = CadLongitudSeg ( p_cAsciiz, iMax ); 
	if ( iLong > 0 ) 
	{
		iCar = 0;
		iRes = 0;
		while ( ( iCar < iLong ) && ( iRes == 0 ) ) 
		{
			uiVal = (unsigned int) p_cAsciiz [ iCar ];
			if ( ( uiVal < 32 ) || ( uiVal == 127 ) )  
			{
				iRes = 1;
			}
			iCar = iCar + 1;
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int CadContieneCaracteresNoEstandarExt ( const char * p_cAsciiz, int iMax )
{
	int				iRes;
	int				iLong;
	int				iCar;
	unsigned int	uiVal;

	iLong = CadLongitudSeg ( p_cAsciiz, iMax ); 
	if ( iLong > 0 ) 
	{
		iCar = 0;
		iRes = 0;
		while ( ( iCar < iLong ) && ( iRes == 0 ) ) 
		{
			uiVal = (unsigned int) p_cAsciiz [ iCar ];
			if ( uiVal > 127 )  
			{
				iRes = 1;
			}
			iCar = iCar + 1;
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int CadCoherenciaParentesis ( const char * p_cAsciiz )
{
	return ( CadCoherenciaParentesisExt ( p_cAsciiz, -1 ) );
}

int CadCoherenciaLlaves ( const char * p_cAsciiz )
{
	return ( CadCoherenciaLlavesExt ( p_cAsciiz, -1 ) );
}

int CadCoherenciaCorchetes ( const char * p_cAsciiz )
{
	return ( CadCoherenciaCorchetesExt ( p_cAsciiz, -1 ) );
}

int CadCoherenciaParejaSignos ( const char * p_cAsciiz, char cSigAp, char cSigCl )
{
	return ( CadCoherenciaParejaSignosExt ( p_cAsciiz, cSigAp, cSigCl, -1 ) );
}

int CadCoherenciaParentesisExt ( const char * p_cAsciiz, int iMax )
{
	return ( CadCoherenciaParejaSignosExt ( p_cAsciiz, '(', ')', iMax ) );
}

int CadCoherenciaLlavesExt ( const char * p_cAsciiz, int iMax  )
{
	return ( CadCoherenciaParejaSignosExt ( p_cAsciiz, '{', '}', iMax ) );
}

int CadCoherenciaCorchetesExt ( const char * p_cAsciiz, int iMax  )
{
	return ( CadCoherenciaParejaSignosExt ( p_cAsciiz, '[', ']', iMax ) );
}

int CadCoherenciaParejaSignosExt ( const char * p_cAsciiz, char cSigAp, char cSigCl, int iMax )
{
	int	iRes;
	int	iLong;
	int	iCar;
	int	iAbiertos;

	iLong = CadLongitudSeg ( p_cAsciiz, iMax ); 
	if ( iLong > 0 ) 
	{
		iAbiertos = 0;
		iCar = 0;
		iRes = 1;
		while ( ( iCar < iLong ) && ( iRes == 1 ) ) 
		{
			if ( p_cAsciiz [ iCar ] == cSigAp )
			{
				iAbiertos = iAbiertos + 1;
			}
			else if ( p_cAsciiz [ iCar ] == cSigCl )
			{
				if ( iAbiertos > 0 )
				{
					iAbiertos = iAbiertos - 1;
				}
				else
				{
					iRes = 0;
				}
			}
			iCar = iCar + 1;
		}
		if ( iAbiertos > 0 )
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

int CadEliminarCaracter ( char * p_cAsciiz, int iCar )
{
	return ( CadEliminarCaracterExt ( p_cAsciiz, iCar, -1 ) );
}

int CadEliminarCaracteres ( char * p_cAsciiz, int iPosIni, int iNumCars )
{
	return ( CadEliminarCaracteresExt ( p_cAsciiz, iPosIni, iNumCars, -1 ) );
}

int CadEliminarPrimerosCaracteres ( char * p_cAsciiz, int iNumCars )
{
	return ( CadEliminarPrimerosCaracteresExt ( p_cAsciiz, iNumCars, -1 ) );
}

int CadEliminarUltimosCaracteres ( char * p_cAsciiz, int iNumCars )
{
	return ( CadEliminarUltimosCaracteresExt ( p_cAsciiz, iNumCars, -1 ) );
}

int CadEliminarApariciones ( char * p_cAsciiz1, const char * p_cAsciiz2 )
{
	return ( CadEliminarAparicionesExt ( p_cAsciiz1, p_cAsciiz2, -1, -1 ) );
}

int CadEliminarAparicionesCaracter ( char * p_cAsciiz, char cVal )
{
	return ( CadEliminarAparicionesCaracterExt ( p_cAsciiz, cVal, -1 ) );
}

int CadEliminarBlancos ( char * p_cAsciiz )
{
	return ( CadEliminarBlancosExt ( p_cAsciiz, -1 ) );
}

int CadEliminarTabuladores ( char * p_cAsciiz )
{
	return ( CadEliminarTabuladoresExt ( p_cAsciiz, -1 ) );
}

int CadEliminarCaracteresNoImprimibles ( char * p_cAsciiz )
{
	return ( CadEliminarCaracteresNoImprimiblesExt ( p_cAsciiz, -1 ) );
}

int CadEliminarCaracteresNoAlfanumericos ( char * p_cAsciiz )
{
	return ( CadEliminarCaracteresNoAlfanumericosExt ( p_cAsciiz, -1 ) );
}

int CadEliminarCaracteresNoEstandar ( char * p_cAsciiz )
{
	return ( CadEliminarCaracteresNoEstandarExt ( p_cAsciiz, -1 ) );
}

int CadEliminarCaracterExt ( char * p_cAsciiz, int iCar, int iMax )
{
	return ( CadEliminarCaracteresExt ( p_cAsciiz, iCar, 1, iMax ) );
}

int CadEliminarCaracteresExt ( char * p_cAsciiz, int iPosIni, int iNumCars, int iMax )
{
	int iRes;
	int iLong;
	int iPos;

	iLong = CadLongitudSeg ( p_cAsciiz, iMax ); 
	if ( ( iPosIni >= 0 ) && ( iPosIni < iLong ) ) 
	{
		if ( iPosIni + iNumCars > iLong )
		{
			iNumCars = iLong - iPosIni;
		}
		for ( iPos = iPosIni; iPos < iLong - iNumCars; iPos = iPos + 1 )
		{
			p_cAsciiz [ iPos ] = p_cAsciiz [ iPos + iNumCars ];
		}
		p_cAsciiz [ iLong - iNumCars ] = (char) 0;
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int CadEliminarPrimerosCaracteresExt ( char * p_cAsciiz, int iNumCars, int iMax )
{
	return ( CadEliminarCaracteresExt ( p_cAsciiz, 0, iNumCars, iMax ) );
}

int CadEliminarUltimosCaracteresExt ( char * p_cAsciiz, int iNumCars, int iMax )
{
	int iLong;
	int iPosIni;	

	iLong = CadLongitudSeg ( p_cAsciiz, iMax ); 
	iPosIni = iLong - iNumCars;
	if ( iPosIni < 0 )
	{
		iPosIni = 0;
	}
	return ( CadEliminarCaracteresExt ( p_cAsciiz, iPosIni, iNumCars, iMax ) );
}

int CadEliminarAparicionesExt ( char * p_cAsciiz1, const char * p_cAsciiz2, int iMax1, int iMax2 )
{
	int iRes;
	int	iCar;
	int	iPos;
	int iDesp;
	int iLong1;
	int iLong2;

	iLong1 = CadLongitudSeg ( p_cAsciiz1, iMax1 ); 
	iLong2 = CadLongitudSeg ( p_cAsciiz2, iMax2 ); 
	if ( ( iLong1 > 0 ) && ( iLong2 > 0 ) && ( iLong2 < iLong1 ) )
	{
		iPos = 0;
		iDesp = 0;
		while ( ( iPos >= 0 ) && ( iLong1 > iLong2 ) )
		{
			iPos = CadBuscarExt ( p_cAsciiz1, p_cAsciiz2, iPos, iMax1, iMax2 );
			if ( iPos >= 0 )
			{
				iDesp = iDesp + iLong2;
				for ( iCar = iPos; iCar < iLong1 - iDesp; iCar = iCar + 1 )
				{
					p_cAsciiz1 [ iCar ] = p_cAsciiz1 [ iCar + iDesp ];
				}
				p_cAsciiz1 [ iLong1 - iDesp ] = (char) 0;
				iLong1 = iLong1 - iLong2;
			}
		}
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int CadEliminarAparicionesCaracterExt ( char * p_cAsciiz, char cVal, int iMax )
{
	int iRes;
	int iLong;
	int	iCar;
	int iDesp;

	iLong = CadLongitudSeg ( p_cAsciiz, iMax ); 
	if ( ( iLong > 0 ) && ( cVal != (char) 0 ) ) 
	{
		iDesp = 0;
		for ( iCar = 0; iCar < iLong; iCar = iCar + 1 )
		{
			if ( p_cAsciiz [ iCar ] == cVal )
			{
				iDesp = iDesp + 1;
			}
			else
			{
				p_cAsciiz [ iCar - iDesp ] =  p_cAsciiz [ iCar ];
			}
		}
		p_cAsciiz [ iLong - iDesp ] = (char) 0;
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int CadEliminarBlancosExt ( char * p_cAsciiz, int iMax )
{
	return ( CadEliminarAparicionesCaracterExt ( p_cAsciiz, ' ', iMax ) );
}

int CadEliminarTabuladoresExt ( char * p_cAsciiz, int iMax )
{
	return ( CadEliminarAparicionesCaracterExt ( p_cAsciiz, (char) 9, iMax ) );
}

int CadEliminarCaracteresNoImprimiblesExt ( char * p_cAsciiz, int iMax )
{
	int				iRes;
	int				iLong;
	int				iCar;
	int				iCarVal;
	unsigned int	uiVal;

	iLong = CadLongitudSeg ( p_cAsciiz, iMax ); 
	if ( iLong > 0 ) 
	{
		iCarVal = 0;
		for ( iCar = 0; iCar < iLong; iCar = iCar + 1 )
		{
			uiVal = (unsigned int) p_cAsciiz [ iCar ];
			if ( ( ( uiVal >= 32 ) && ( uiVal != 127 ) ) || 
				 ( uiVal == 9 ) )
			{
				p_cAsciiz [ iCarVal ] = p_cAsciiz [ iCar ];
				iCarVal = iCarVal + 1;
			}
		}
		p_cAsciiz [ iCarVal ] = (char) 0;
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int CadEliminarCaracteresNoAlfanumericosExt ( char * p_cAsciiz, int iMax )
{
	int				iRes;
	int				iLong;
	int				iCar;
	int				iCarVal;
	unsigned int	uiVal;

	iLong = CadLongitudSeg ( p_cAsciiz, iMax ); 
	if ( iLong > 0 ) 
	{
		iCarVal = 0;
		for ( iCar = 0; iCar < iLong; iCar = iCar + 1 )
		{
			uiVal = (unsigned int) p_cAsciiz [ iCar ];
			if ( ( uiVal >= 32 ) && ( uiVal != 127 ) ) 
			{
				p_cAsciiz [ iCarVal ] = p_cAsciiz [ iCar ];
				iCarVal = iCarVal + 1;
			}
		}
		p_cAsciiz [ iCarVal ] = (char) 0;
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int CadEliminarCaracteresNoEstandarExt ( char * p_cAsciiz, int iMax )
{
	int				iRes;
	int				iLong;
	int				iCar;
	int				iCarVal;
	unsigned int	uiVal;

	iLong = CadLongitudSeg ( p_cAsciiz, iMax ); 
	if ( iLong > 0 ) 
	{
		iCarVal = 0;
		for ( iCar = 0; iCar < iLong; iCar = iCar + 1 )
		{
			uiVal = (unsigned int) p_cAsciiz [ iCar ];
			if ( uiVal < 128 ) 
			{
				p_cAsciiz [ iCarVal ] = p_cAsciiz [ iCar ];
				iCarVal = iCarVal + 1;
			}
		}
		p_cAsciiz [ iCarVal ] = (char) 0;
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

char * CadExtraer ( const char * p_cAsciiz, int iPos, int iTam )
{
	return ( CadExtraerExt ( p_cAsciiz, iPos, iTam, -1 ) );
}

char * CadExtraerPrimeros ( const char * p_cAsciiz, int iTam )
{
	return ( CadExtraerPrimerosExt ( p_cAsciiz, iTam, -1 ) );
}

char * CadExtraerUltimos ( const char * p_cAsciiz, int iTam )
{
	return ( CadExtraerUltimosExt ( p_cAsciiz, iTam, -1 ) );
}

char * CadExtraerDesdeCaracter ( const char * p_cAsciiz, char cVal )
{
	return ( CadExtraerDesdeCaracterExt ( p_cAsciiz, cVal, 1, 0, -1 ) );
}

char * CadExtraerHastaCaracter ( const char * p_cAsciiz, char cVal )
{
	return ( CadExtraerHastaCaracterExt ( p_cAsciiz, cVal, 1, 0, -1 ) );
}

int CadEliminarDesdeCaracter ( char * p_cAsciiz, char cVal )
{
	return ( CadEliminarDesdeCaracterExt ( p_cAsciiz, cVal, 1, 0, -1 ) );
}

int CadEliminarHastaCaracter ( char * p_cAsciiz, char cVal )
{
	return ( CadEliminarHastaCaracterExt ( p_cAsciiz, cVal, 1, 0, -1 ) );
}

char * CadExtraerExt ( const char * p_cAsciiz, int iPos, int iTam, int iMax )
{
	char *	p_cRes;
	int			iLong;
	int			iCar;

	iLong = CadLongitudSeg ( p_cAsciiz, iMax ); 
	if ( ( iPos >= 0 ) && ( iPos < iLong ) )
	{
		if ( iPos + iTam > iLong )
		{
			iTam = iLong - iPos;
		}
		if ( iTam > 0 )
		{
			p_cRes = CadCrear ( iTam );
			if ( ES_VALIDO ( p_cRes ) )
			{
				for ( iCar = 0; iCar < iTam; iCar = iCar + 1 )
				{
					p_cRes [ iCar ] = p_cAsciiz [ iPos + iCar ];
				}
				p_cRes [ iTam ] = (char) 0;
			}
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

char * CadExtraerPrimerosExt ( const char * p_cAsciiz, int iTam, int iMax )
{
	return ( CadExtraerExt ( p_cAsciiz, 0, iTam, iMax ) );
}

char * CadExtraerUltimosExt ( const char * p_cAsciiz, int iTam, int iMax )
{
	int	iLong;
	int iPosIni;	

	iLong = CadLongitudSeg ( p_cAsciiz, iMax ); 
	iPosIni = iLong - iTam;
	if ( iPosIni < 0 )
	{
		iPosIni = 0;
	}
	return ( CadExtraerExt ( p_cAsciiz, iPosIni, iTam, iMax ) );
}


char * CadExtraerDesdeCaracterExt ( const char * p_cAsciiz, char cVal, int iIncluir, int iAparicion, int iMax )
{
	char *	p_cRes;
	int		iLong;
	int		iPos;

	iLong = CadLongitudSeg ( p_cAsciiz, iMax ); 
	if ( ( iLong > 0 ) && ( cVal != (char) 0 ) && ( iAparicion > 0 ) ) 
	{
		iPos = 0;
		while ( ( iAparicion > 0 ) && ( iPos >= 0 ) && ( iPos < iLong ) )
		{
			iPos = CadBuscarCaracterExt ( p_cAsciiz, cVal, iPos, iMax );
			iAparicion = iAparicion - 1;
		}
		if ( iPos >= 0 )
		{
			if ( iIncluir == 1 )
			{
				p_cRes = CadExtraer ( p_cAsciiz, iPos, iLong - iPos );
			}
			else
			{
				p_cRes = CadExtraer ( p_cAsciiz, iPos + 1, iLong - iPos - 1 );
			}
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

char * CadExtraerHastaCaracterExt ( const char * p_cAsciiz, char cVal, int iIncluir, int iAparicion, int iMax )
{
	char *	p_cRes;
	int		iLong;
	int		iPos;

	iLong = CadLongitudSeg ( p_cAsciiz, iMax ); 
	if ( ( iLong > 0 ) && ( cVal != (char) 0 ) && ( iAparicion > 0 ) ) 
	{
		iPos = -1;
		while ( ( iAparicion > 0 ) && ( iPos >= 0 ) && ( iPos < iLong ) )
		{
			iPos = CadBuscarCaracterExt ( p_cAsciiz, cVal, iPos + 1, iMax );
			iAparicion = iAparicion - 1;
		}
		if ( iPos >= 0 )
		{
			if ( iIncluir == 1 )
			{
				p_cRes = CadExtraer ( p_cAsciiz, 0, iPos + 1 );
			}
			else
			{
				p_cRes = CadExtraer ( p_cAsciiz, 0, iPos );
			}
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

int CadEliminarDesdeCaracterExt ( char * p_cAsciiz, char cVal, int iIncluir, int iAparicion, int iMax )
{
	int		iRes;
	int		iLong;
	int		iPos;

	iLong = CadLongitudSeg ( p_cAsciiz, iMax ); 
	if ( ( iLong > 0 ) && ( cVal != (char) 0 ) && ( iAparicion > 0 ) ) 
	{
		iPos = 0;
		while ( ( iAparicion > 0 ) && ( iPos >= 0 ) && ( iPos < iLong ) )
		{
			iPos = CadBuscarCaracterExt ( p_cAsciiz, cVal, iPos, iMax );
			iAparicion = iAparicion - 1;
		}
		if ( iPos >= 0 )
		{
			if ( iIncluir == 1 )
			{
				iRes = CadEliminarUltimosCaracteres ( p_cAsciiz, iLong - iPos );
			}
			else
			{
				iRes = CadEliminarUltimosCaracteres ( p_cAsciiz, iLong - iPos - 1 );
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
	return ( iRes );
}

int CadEliminarHastaCaracterExt ( char * p_cAsciiz, char cVal, int iIncluir, int iAparicion, int iMax )
{
	int		iRes;
	int		iLong;
	int		iPos;

	iLong = CadLongitudSeg ( p_cAsciiz, iMax ); 
	if ( ( iLong > 0 ) && ( cVal != (char) 0 ) && ( iAparicion > 0 ) ) 
	{
		iPos = 0;
		while ( ( iAparicion > 0 ) && ( iPos >= 0 ) && ( iPos < iLong ) )
		{
			iPos = CadBuscarCaracterExt ( p_cAsciiz, cVal, iPos, iMax );
			iAparicion = iAparicion - 1;
		}
		if ( iPos >= 0 )
		{
			if ( iIncluir == 1 )
			{
				iRes = CadEliminarPrimerosCaracteres ( p_cAsciiz, iPos );
			}
			else
			{
				iRes = CadEliminarPrimerosCaracteres ( p_cAsciiz, iPos - 1 );
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
	return ( iRes );
}

int CadCompararSinDistinguirTipoLetra ( const char * p_cAsciiz1, const char * p_cAsciiz2 )
{
	return ( CadCompararSinDistinguirTipoLetraExt ( p_cAsciiz1, p_cAsciiz2, -1, -1 ) );
}

int CadCompararSinDistinguirTipoLetraExt ( const char * p_cAsciiz1, const char * p_cAsciiz2, int iMax1, int iMax2 )
{
	int iRes;
	int iCar;
	int iLong1;
	int iLong2;

	iLong1 = CadLongitudSeg ( p_cAsciiz1, iMax1 ); 
	iLong2 = CadLongitudSeg ( p_cAsciiz2, iMax2 ); 
	if ( ( iLong1 > 0 ) && ( iLong2 > 0 ) )
	{
		if ( iLong1 == iLong2 )
		{
			iRes = 1;
			iCar = 0; 
			while ( ( iCar < iLong1 ) && ( iRes == 1 ) )  
			{
				if ( ASCIILetraMinAMay ( p_cAsciiz1 [ iCar ] ) < ASCIILetraMinAMay ( p_cAsciiz2 [ iCar ] ) )
				{
					iRes = 2;
				}
				else if ( ASCIILetraMinAMay ( p_cAsciiz1 [ iCar ] ) > ASCIILetraMinAMay ( p_cAsciiz2 [ iCar ] ) )
				{
					iRes = 3;
				}
				iCar = iCar + 1;
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
	return ( iRes );
}

int CadCompararParcial ( const char * p_cAsciiz1, const char * p_cAsciiz2, int iMinCars )
{
	return ( CadCompararParcialExt ( p_cAsciiz1, p_cAsciiz2, iMinCars, 0, -1, -1 ) );
}

int CadEsIgual ( const char * p_cAsciiz1, const char * p_cAsciiz2 )
{
	return ( CadEsIgualExt ( p_cAsciiz1, p_cAsciiz2, -1, -1 ) );
}

int CadEsMenor ( const char * p_cAsciiz1, const char * p_cAsciiz2 )
{
	return ( CadEsMenorExt ( p_cAsciiz1, p_cAsciiz2, -1, -1 ) );
}

int CadEsMayor ( const char * p_cAsciiz1, const char * p_cAsciiz2 )
{
	return ( CadEsMayorExt ( p_cAsciiz1, p_cAsciiz2, -1, -1 ) );
}

int CadEsMenorIg ( const char * p_cAsciiz1, const char * p_cAsciiz2 )
{
	return ( CadEsMenorIgExt ( p_cAsciiz1, p_cAsciiz2, -1, -1 ) );
}

int CadEsMayorIg ( const char * p_cAsciiz1, const char * p_cAsciiz2 )
{
	return ( CadEsMayorIgExt ( p_cAsciiz1, p_cAsciiz2, -1, -1 ) );
}

int CadCompararParcialExt ( const char * p_cAsciiz1, const char * p_cAsciiz2, int iMinCars, int iDistinguir, int iMax1, int iMax2 )
{
	int iRes;
	int iCar;
	int iLong1;
	int iLong2;
	int iNumCars;

	iLong1 = CadLongitudSeg ( p_cAsciiz1, iMax1 ); 
	iLong2 = CadLongitudSeg ( p_cAsciiz2, iMax2 ); 
	if ( ( iLong1 > 0 ) && ( iLong2 > 0 ) )
	{
		iNumCars = 0;
		if ( ( iMinCars < 0 ) || ( iMinCars >= iLong2 ) )
		{
			if ( iLong1 == iLong2 )
			{
				iRes = 1;
				iNumCars = iLong1;
			}
			else
			{
				iRes = 0;
			}
		}
		else if ( iMinCars > iLong1 )
		{
			iRes = 0;
		}
		else
		{
			iNumCars = MIN ( iLong1, iLong2 );
			iRes = 1;
		}

		iCar = 0; 
		while ( ( iCar < iNumCars ) && ( iRes == 1 ) )  
		{
			if ( iDistinguir == 1 )
			{
				if ( p_cAsciiz1 [ iCar ] != p_cAsciiz2 [ iCar ] )
				{
					iRes = 0;
				}
			}
			else
			{
				if ( ASCIILetraMinAMay ( p_cAsciiz1 [ iCar ] ) != ASCIILetraMinAMay ( p_cAsciiz2 [ iCar ] ) )
				{
					iRes = 0;
				}
			}

			iCar = iCar + 1;
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int CadEsIgualExt ( const char * p_cAsciiz1, const char * p_cAsciiz2, int iMax1, int iMax2 )
{
	int iRes;

	if ( CadCompararExt ( p_cAsciiz1, p_cAsciiz2, iMax1, iMax2 ) == 1 )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int CadEsMenorExt ( const char * p_cAsciiz1, const char * p_cAsciiz2, int iMax1, int iMax2 )
{
	int iRes;

	if ( CadCompararExt ( p_cAsciiz1, p_cAsciiz2, iMax1, iMax2 ) == 2 )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int CadEsMayorExt ( const char * p_cAsciiz1, const char * p_cAsciiz2, int iMax1, int iMax2 )
{
	int iRes;

	if ( CadCompararExt ( p_cAsciiz1, p_cAsciiz2, iMax1, iMax2 ) == 3 )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int CadEsMenorIgExt ( const char * p_cAsciiz1, const char * p_cAsciiz2, int iMax1, int iMax2 )
{
	int iRes;
	int iCmp;

	iCmp = CadCompararExt ( p_cAsciiz1, p_cAsciiz2, iMax1, iMax2 );
	if ( ( iCmp == 1 ) || ( iCmp == 2 ) )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int CadEsMayorIgExt ( const char * p_cAsciiz1, const char * p_cAsciiz2, int iMax1, int iMax2 )
{
	int iRes;
	int iCmp;

	iCmp = CadCompararExt ( p_cAsciiz1, p_cAsciiz2, iMax1, iMax2 );
	if ( ( iCmp == 1 ) || ( iCmp == 3 ) )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int CadEsNumerica ( const char * p_cAsciiz )
{
	return ( CadEsNumericaExt ( p_cAsciiz, -1 ) );
}

int CadEsNumeroEntero ( const char * p_cAsciiz )
{
	return ( CadEsNumeroEnteroExt ( p_cAsciiz, -1 ) );
}

int CadEsNumeroReal ( const char * p_cAsciiz )
{
	return ( CadEsNumeroRealExt ( p_cAsciiz, -1 ) );
}

int CadEsNumeroHexadecimal ( const char * p_cAsciiz )
{
	return ( CadEsNumeroHexadecimalExt ( p_cAsciiz, -1 ) );
}

int CadEsToken ( const char * p_cAsciiz )
{
	return ( CadEsTokenExt ( p_cAsciiz, -1 ) );
}

int CadEsNumericaExt ( const char * p_cAsciiz, int iMax )
{
	int iRes;
	int iCar;
	int iLong;

	iLong = CadLongitudSeg ( p_cAsciiz, iMax ); 
	if ( iLong > 0 ) 
	{
		iRes = 1;
		iCar = 0; 
		while ( ( iCar < iLong ) && ( iRes == 1 ) )  
		{
			if ( ( ASCIIEsDigito ( p_cAsciiz [ iCar ] ) == 0 ) &&
				 ( p_cAsciiz [ iCar ] != ASCII_PUNTO ) &&
				 ( p_cAsciiz [ iCar ] != ASCII_MENOS ) )
			{
				iRes = 0;
			}
			iCar = iCar + 1;
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int CadEsNumeroEnteroExt ( const char * p_cAsciiz, int iMax )
{
	int iRes;
	int iCar;
	int iLong;

	iLong = CadLongitudSeg ( p_cAsciiz, iMax ); 
	if ( iLong > 0 ) 
	{
		iRes = 1;
		iCar = 0; 
		while ( ( iCar < iLong ) && ( iRes == 1 ) )  
		{
			if ( ( ASCIIEsDigito ( p_cAsciiz [ iCar ] ) == 0 ) &&
				 ( p_cAsciiz [ iCar ] != ASCII_MENOS ) )
			{
				iRes = 0;
			}
			iCar = iCar + 1;
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int CadEsNumeroRealExt ( const char * p_cAsciiz, int iMax )
{
	return ( CadEsNumericaExt ( p_cAsciiz, iMax ) );
}

int CadEsNumeroHexadecimalExt ( const char * p_cAsciiz, int iMax )
{
	int iRes;
	int iCar;
	int iLong;

	iLong = CadLongitudSeg ( p_cAsciiz, iMax ); 
	if ( iLong > 0 ) 
	{
		iRes = 1;
		iCar = 0; 
		while ( ( iCar < iLong ) && ( iRes == 1 ) )  
		{
			if ( HexEsValido ( p_cAsciiz [ iCar ] ) == 0 ) 
			{
				iRes = 0;
			}
			iCar = iCar + 1;
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int CadEsTokenExt ( const char * p_cAsciiz, int iMax )
{
	int iRes;
	int iCar;
	int iLong;

	iLong = CadLongitudSeg ( p_cAsciiz, iMax ); 
	if ( iLong > 0 ) 
	{
		if ( ASCIIEsValidoInicioToken ( p_cAsciiz [ 0 ] ) == 1 )
		{
			iRes = 1;
			iCar = 1; 
			while ( ( iCar < iLong ) && ( iRes == 1 ) )  
			{
				if ( ASCIIEsValidoToken ( p_cAsciiz [ iCar ] ) == 0 ) 
				{
					iRes = 0;
				}
				iCar = iCar + 1;
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
	return ( iRes );
}

int CadContiene ( const char * p_cAsciiz1, const char * p_cAsciiz2 )
{
	return  ( CadContieneExt ( p_cAsciiz1, p_cAsciiz2, -1, -1 ) );
}

int CadEmpiezaPor ( const char * p_cAsciiz1, const char * p_cAsciiz2 )
{
	return  ( CadEmpiezaPorExt ( p_cAsciiz1, p_cAsciiz2, -1, -1 ) );
}

int CadAcabaPor ( const char * p_cAsciiz1, const char * p_cAsciiz2 )
{
	return  ( CadAcabaPorExt ( p_cAsciiz1, p_cAsciiz2, -1, -1 ) );
}

int CadBuscar ( const char * p_cAsciiz1, const char * p_cAsciiz2, int iPos )
{
	return  ( CadBuscarExt ( p_cAsciiz1, p_cAsciiz2, iPos, -1, -1 ) );
}

int CadBuscarDesc ( const char * p_cAsciiz1, const char * p_cAsciiz2, int iPos )
{
	return  ( CadBuscarDescExt ( p_cAsciiz1, p_cAsciiz2, iPos, -1, -1 ) );
}

int CadContar ( const char * p_cAsciiz1, const char * p_cAsciiz2 )
{
	return  ( CadContarExt ( p_cAsciiz1, p_cAsciiz2, -1, -1 ) );
}

int CadReemplazar ( char * p_cAsciiz1, const char * p_cAsciiz2, const char * p_cAsciiz3 )
{
	return  ( CadReemplazarExt ( p_cAsciiz1, p_cAsciiz2, p_cAsciiz3, -1, -1, -1 ) );
}

int CadContieneExt ( const char * p_cAsciiz1, const char * p_cAsciiz2, int iMax1, int iMax2 )
{
	int iRes;

	if ( CadBuscarExt ( p_cAsciiz1, p_cAsciiz2, 0, iMax1, iMax2 ) >= 0 )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int CadEmpiezaPorExt ( const char * p_cAsciiz1, const char * p_cAsciiz2, int iMax1, int iMax2 )
{
	int iRes;

	if ( CadBuscarExt ( p_cAsciiz1, p_cAsciiz2, 0, iMax1, iMax2 ) == 0 )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int CadAcabaPorExt ( const char * p_cAsciiz1, const char * p_cAsciiz2, int iMax1, int iMax2 )
{
	int iRes;
	int iLong1;
	int iLong2;

	iLong1 = CadLongitudSeg ( p_cAsciiz1, iMax1 ); 
	iLong2 = CadLongitudSeg ( p_cAsciiz2, iMax2 ); 
	if ( CadBuscarDescExt ( p_cAsciiz1, p_cAsciiz2, iLong1, iMax1, iMax2 ) == iLong1 - iLong2 )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int CadBuscarExt ( const char * p_cAsciiz1, const char * p_cAsciiz2, int iPos, int iMax1, int iMax2 )
{
	int iRes;
	int iLong1;
	int iLong2;
	int iEnc;
	int iCar;
	int iDesp;

	iLong1 = CadLongitudSeg ( p_cAsciiz1, iMax1 ); 
	iLong2 = CadLongitudSeg ( p_cAsciiz2, iMax2 ); 
	if ( ( iLong1 > 0 ) && ( iLong2 > 0 ) && ( iPos >= 0 ) && ( iPos + iLong2 <= iLong1 ) )
	{
		iCar = iPos;
		iDesp = 0;
		iEnc = 0;
		while ( ( iCar + iDesp < iLong1 ) && ( iEnc == 0 ) )
		{
			if ( p_cAsciiz1 [ iCar + iDesp ] == p_cAsciiz2 [ iDesp ] )
			{
				iDesp = iDesp + 1;
				if ( iDesp >= iLong2 )
				{
					iEnc = 1;
				}
			}
			else
			{
				iCar = iCar + 1;
				iDesp = 0;
			}
		}
		if ( iEnc == 1 )
		{
			iRes = iCar;
		}
		else
		{
			iRes = -1;
		}
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int CadBuscarDescExt ( const char * p_cAsciiz1, const char * p_cAsciiz2, int iPos, int iMax1, int iMax2 )
{
	int iRes;
	int iLong1;
	int iLong2;
	int iEnc;
	int iCar;
	int iDesp;

	iLong1 = CadLongitudSeg ( p_cAsciiz1, iMax1 ); 
	iLong2 = CadLongitudSeg ( p_cAsciiz2, iMax2 ); 
	if ( iPos == - 1 )
	{
		iPos = iLong1 - 1;
	}
	if ( ( iLong1 > 0 ) && ( iLong2 > 0 ) && ( iPos >= 0 ) && ( iPos - iLong2 >= 0 ) )
	{
		iCar = iPos - iLong2;
		iDesp = 0;
		iEnc = 0;
		while ( ( iCar + iDesp < iLong1 ) && ( iCar >= 0 ) && ( iEnc == 0 ) )
		{
			if ( p_cAsciiz1 [ iCar + iDesp ] == p_cAsciiz2 [ iDesp ] )
			{
				iDesp = iDesp + 1;
				if ( iDesp >= iLong2 )
				{
					iEnc = 1;
				}
			}
			else
			{
				iCar = iCar - 1;
				iDesp = 0;
			}
		}
		if ( iEnc == 1 )
		{
			iRes = iCar;
		}
		else
		{
			iRes = -1;
		}
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int CadContarExt ( const char * p_cAsciiz1, const char * p_cAsciiz2, int iMax1, int iMax2 )
{
	int iRes;
	int iLong1;
	int iLong2;
	int iPos;

	iLong1 = CadLongitudSeg ( p_cAsciiz1, iMax1 ); 
	iLong2 = CadLongitudSeg ( p_cAsciiz2, iMax2 ); 
	if ( ( iLong1 > 0 ) && ( iLong2 > 0 ) )
	{
		iRes = 0;
		iPos = 0;
		while ( ( iPos >= 0 ) && ( iPos < iLong1 ) )
		{
			iPos = CadBuscarExt ( p_cAsciiz1, p_cAsciiz2, iPos, iMax1, iMax2 );
			if ( iPos >= 0 )
			{
				iRes = iRes + 1;
				iPos = iPos + iLong2;
			}
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int CadReemplazarExt ( char * p_cAsciiz1, const char * p_cAsciiz2, const char * p_cAsciiz3, int iMax1, int iMax2, int iMax3 )
{
	int		iTot;
	int		iPos;
	int		iPosAnt;
	int		iLong1;
	int		iLong2;
	int		iLong3;
	int		iRes;
	char *	p_cNueva;
	char *	p_cParteCop;

	iLong1 = CadLongitudSeg ( p_cAsciiz1, iMax1 ); 
	iLong2 = CadLongitudSeg ( p_cAsciiz2, iMax2 ); 
	iLong3 = CadLongitudSeg ( p_cAsciiz3, iMax3 ); 
	if ( ( iLong1 > 0 ) && ( iLong2 > 0 ) && ( iLong3 >= 0 ) && ( iLong2 < iLong1 ) )
	{
		p_cNueva = CadCrear ( CAD_MAX_TAM );
		if ( ES_VALIDO ( p_cNueva ) )
		{
			iRes = 1;
			iTot = 0;
			iPos = 0;
			while ( ( iPos >= 0 ) && ( iPos < iLong1 ) && ( iRes == 1 ) )
			{
				iPosAnt = iPos;
				iPos = CadBuscarExt ( p_cAsciiz1, p_cAsciiz2, iPos, iMax1, iMax2 );
				if ( iPos >= 0 )
				{
					p_cParteCop = CadExtraerExt ( p_cAsciiz1, iPosAnt, iPos - iPosAnt, iMax1 );
					if ( ES_VALIDO ( p_cParteCop ) )
					{
						if ( CadConcatenarExt ( p_cNueva, p_cParteCop, iMax1, iPos - iPosAnt ) == 1 )
						{
							if ( CadConcatenarExt ( p_cNueva, p_cAsciiz3, iMax1, iMax3 ) == 1 )
							{
								iPos = iPos + iLong2; 
								iTot = iTot + 1;
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
						MemLiberar ( (void **) &p_cParteCop );
					}
					else
					{
						iRes = 0;
					}
				}
			}
			if ( ( iRes == 1 ) && ( iPos < iLong1 ) )
			{
				p_cParteCop = CadExtraerUltimosExt ( p_cAsciiz1, iLong1 - iPos, iMax1 );
				if ( ES_VALIDO ( p_cParteCop ) )
				{
					if ( CadConcatenarExt ( p_cNueva, p_cParteCop, iMax1, iLong1 - iPos ) == 1 )
					{
						CadLimpiarExt ( p_cAsciiz1, ' ', iMax1);
						CadCopiarExt ( p_cAsciiz1, p_cNueva, iMax1, iLong1 );
					}
					else
					{
						iRes = 0;
					}
					MemLiberar ( (void **) &p_cParteCop );
				}
				else
				{
					iRes = 0;
				}
			}
			if ( ( iRes == 1 ) && ( iTot > 0 ) )
			{
				CadCopiar ( p_cAsciiz1, p_cNueva );
			}
			MemLiberar ( (void **) &p_cNueva );
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

int CadContieneCaracter ( const char * p_cAsciiz, char cVal )
{
	return ( CadContieneCaracterExt ( p_cAsciiz, cVal, -1 ) );
}

int CadEmpiezaPorCaracter ( const char * p_cAsciiz, char cVal )
{
	return ( CadEmpiezaPorCaracterExt ( p_cAsciiz, cVal, -1 ) );
}

int CadAcabaPorCaracter ( const char * p_cAsciiz, char cVal )
{
	return ( CadAcabaPorCaracterExt ( p_cAsciiz, cVal, -1 ) );
}

int CadBuscarCaracter ( const char * p_cAsciiz, char cVal, int iPos )
{
	return ( CadBuscarCaracterExt ( p_cAsciiz, cVal, iPos, -1 ) );
}

int CadBuscarDescCaracter ( const char * p_cAsciiz, char cVal, int iPos )
{
	return ( CadBuscarDescCaracterExt ( p_cAsciiz, cVal, iPos, -1 ) );
}

int CadBuscarCaracterDiferente ( const char * p_cAsciiz, char cVal, int iPos )
{
	return ( CadBuscarCaracterDiferenteExt ( p_cAsciiz, cVal, iPos, -1 ) );
}

int CadBuscarDescCaracterDiferente ( const char * p_cAsciiz, char cVal, int iPos )
{
	return ( CadBuscarDescCaracterDiferenteExt ( p_cAsciiz, cVal, iPos, -1 ) );
}

int CadContarCaracter ( const char * p_cAsciiz, char cVal )
{
	return ( CadContarCaracterExt ( p_cAsciiz, cVal, -1 ) );
}

int CadReemplazarCaracter ( char * p_cAsciiz, char cVal, char cRes )
{
	return ( CadReemplazarCaracterExt ( p_cAsciiz, cVal, cRes, -1 ) );
}

int CadContieneCaracterExt ( const char * p_cAsciiz, char cVal, int iMax )
{
	int iRes;
	int iCar;
	int iLong;

	iLong = CadLongitudSeg ( p_cAsciiz, iMax ); 
	if ( iLong > 0 ) 
	{
		iRes = 0;
		iCar = 0; 
		while ( ( iCar < iLong ) && ( iRes == 0 ) )  
		{
			if ( p_cAsciiz [ iCar ] == cVal )
			{
				iRes = 1;
			}
			iCar = iCar + 1;
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int CadEmpiezaPorCaracterExt ( const char * p_cAsciiz, char cVal, int iMax )
{
	int iRes;
	int iLong;

	iLong = CadLongitudSeg ( p_cAsciiz, iMax ); 
	if ( iLong > 0 ) 
	{
		if ( p_cAsciiz [ 0 ] == cVal )
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

int CadAcabaPorCaracterExt ( const char * p_cAsciiz, char cVal, int iMax )
{
	int iRes;
	int iLong;

	iLong = CadLongitudSeg ( p_cAsciiz, iMax ); 
	if ( iLong > 0 ) 
	{
		if ( p_cAsciiz [ iLong - 1 ] == cVal )
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

int CadBuscarCaracterExt ( const char * p_cAsciiz, char cVal, int iPos, int iMax )
{
	int iRes;
	int iLong;
	int iEnc;
	int iCar;

	iLong = CadLongitudSeg ( p_cAsciiz, iMax ); 
	if ( ( iLong > 0 ) && ( iPos >= 0 ) && ( iPos < iLong ) && ( cVal != (char) 0 ) )
	{
		iCar = iPos;
		iEnc = 0;
		while ( ( iCar < iLong ) && ( iEnc == 0 ) )
		{
			if ( p_cAsciiz [ iCar ] == cVal )
			{
				iEnc = 1;
			}
			else
			{
				iCar = iCar + 1;
			}
		}
		if ( iEnc == 1 )
		{
			iRes = iCar;
		}
		else
		{
			iRes = -1;
		}
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int CadBuscarDescCaracterExt ( const char * p_cAsciiz, char cVal, int iPos, int iMax )
{
	int iRes;
	int iLong;
	int iEnc;
	int iCar;

	iLong = CadLongitudSeg ( p_cAsciiz, iMax ); 
	if ( iPos == - 1 )
	{
		iPos = iLong - 1;
	}
	if ( ( iLong > 0 ) && ( iPos >= 0 ) && ( iPos < iLong ) && ( cVal != (char) 0 ) )
	{
		iCar = iPos;
		iEnc = 0;
		while ( ( iCar >= 0 ) && ( iEnc == 0 ) )
		{
			if ( p_cAsciiz [ iCar ] == cVal )
			{
				iEnc = 1;
			}
			else
			{
				iCar = iCar - 1;
			}
		}
		if ( iEnc == 1 )
		{
			iRes = iCar;
		}
		else
		{
			iRes = -1;
		}
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int CadBuscarCaracterDiferenteExt ( const char * p_cAsciiz, char cVal, int iPos, int iMax )
{
	int iRes;
	int iLong;
	int iEnc;
	int iCar;

	iLong = CadLongitudSeg ( p_cAsciiz, iMax ); 
	if ( ( iLong > 0 ) && ( iPos >= 0 ) && ( iPos < iLong ) && ( cVal != (char) 0 ) )
	{
		iCar = iPos;
		iEnc = 0;
		while ( ( iCar < iLong ) && ( iEnc == 0 ) )
		{
			if ( p_cAsciiz [ iCar ] != cVal )
			{
				iEnc = 1;
			}
			else
			{
				iCar = iCar + 1;
			}
		}
		if ( iEnc == 1 )
		{
			iRes = iCar;
		}
		else
		{
			iRes = -1;
		}
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int CadBuscarDescCaracterDiferenteExt ( const char * p_cAsciiz, char cVal, int iPos, int iMax )
{
	int iRes;
	int iLong;
	int iEnc;
	int iCar;

	iLong = CadLongitudSeg ( p_cAsciiz, iMax ); 
	if ( iPos == - 1 )
	{
		iPos = iLong - 1;
	}
	if ( ( iLong > 0 ) && ( iPos >= 0 ) && ( iPos < iLong ) && ( cVal != (char) 0 ) )
	{
		iCar = iPos;
		iEnc = 0;
		while ( ( iCar >= 0 ) && ( iEnc == 0 ) )
		{
			if ( p_cAsciiz [ iCar ] != cVal )
			{
				iEnc = 1;
			}
			else
			{
				iCar = iCar - 1;
			}
		}
		if ( iEnc == 1 )
		{
			iRes = iCar;
		}
		else
		{
			iRes = -1;
		}
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int CadContarCaracterExt ( const char * p_cAsciiz, char cVal, int iMax )
{
	int iRes;
	int iLong;
	int iCar;

	iLong = CadLongitudSeg ( p_cAsciiz, iMax ); 
	if ( ( iLong > 0 ) && ( cVal != (char) 0 ) )
	{
		iRes = 0;
		for ( iCar = 0; iCar < iLong; iCar = iCar + 1 ) 
		{
			if ( p_cAsciiz [ iCar ] == cVal )
			{
				iRes = iRes + 1;
			}
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int CadReemplazarCaracterExt ( char * p_cAsciiz, char cVal, char cRes, int iMax )
{
	int iRes;
	int iLong;
	int iCar;

	iLong = CadLongitudSeg ( p_cAsciiz, iMax ); 
	if ( ( iLong > 0 ) && ( cVal != (char) 0 ) && ( cRes != (char) 0 ) )
	{
		iRes = 0;
		for ( iCar = 0; iCar < iLong; iCar = iCar + 1 ) 
		{
			if ( p_cAsciiz [ iCar ] == cVal )
			{
				p_cAsciiz [ iCar ] = cRes;
				iRes = iRes + 1;
			}
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int CadInvertir ( char * p_cAsciiz )
{
	return ( CadInvertirExt ( p_cAsciiz, -1 ));
}

int CadConvertirAMayusculas ( char * p_cAsciiz )
{
	return ( CadConvertirAMayusculasExt ( p_cAsciiz, -1 ));
}

int CadConvertirAMinusculas ( char * p_cAsciiz )
{
	return ( CadConvertirAMinusculasExt ( p_cAsciiz, -1 ));
}

int CadConvertirACapitales ( char * p_cAsciiz )
{
	return ( CadConvertirACapitalesExt ( p_cAsciiz, -1 ));
}

int CadInvertirExt ( char * p_cAsciiz, int iMax )
{
	int		iRes;
	int		iLong;
	char cCar;
	int		iCar;

	iLong = CadLongitudSeg ( p_cAsciiz, iMax ); 
	if ( iLong > 0 ) 
	{
		iCar = 0; 
		while ( iCar < iLong - iCar - 1 )  
		{
			cCar = p_cAsciiz [ iCar ];
			p_cAsciiz [ iCar ] = p_cAsciiz [ iLong - iCar - 1 ];
			p_cAsciiz [ iLong - iCar - 1 ] = cCar;
			iCar = iCar + 1;
		}
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int CadConvertirAMayusculasExt ( char * p_cAsciiz, int iMax )
{
	int iRes;
	int iLong;
	int iCar;

	iLong = CadLongitudSeg ( p_cAsciiz, iMax ); 
	if ( iLong > 0 ) 
	{
		for ( iCar = 0; iCar < iLong; iCar = iCar + 1 ) 
		{
			p_cAsciiz [ iCar ] = ASCIILetraMinAMay ( p_cAsciiz [ iCar ] );
		}
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int CadConvertirAMinusculasExt ( char * p_cAsciiz, int iMax )
{
	int iRes;
	int iLong;
	int iCar;

	iLong = CadLongitudSeg ( p_cAsciiz, iMax ); 
	if ( iLong > 0 ) 
	{
		for ( iCar = 0; iCar < iLong; iCar = iCar + 1 ) 
		{
			p_cAsciiz [ iCar ] = ASCIILetraMayAMin ( p_cAsciiz [ iCar ] );
		}
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int CadConvertirACapitalesExt ( char * p_cAsciiz, int iMax )
{
	int iInicio;
	int iPunto;
	int iRes;
	int iLong;
	int iCar;

	iLong = CadLongitudSeg ( p_cAsciiz, iMax ); 
	if ( iLong > 0 ) 
	{
		iInicio = 1;
		iPunto = 0;
		for ( iCar = 0; iCar < iLong; iCar = iCar + 1 ) 
		{
			if ( ASCIIEsLetra ( p_cAsciiz [ iCar ] ) == 1 )
			{
				if ( iInicio ==  1 )
				{
					p_cAsciiz [ iCar ] = ASCIILetraMinAMay ( p_cAsciiz [ iCar ] );
					iInicio = 0;
				}
				else if ( iPunto == 1 )
				{
					p_cAsciiz [ iCar ] = ASCIILetraMinAMay ( p_cAsciiz [ iCar ] );
					iPunto = 0;
				}
				else
				{
					p_cAsciiz [ iCar ] = ASCIILetraMayAMin ( p_cAsciiz [ iCar ] );
				}
			}
			else if ( p_cAsciiz [ iCar ] == '.' )
			{
				iPunto = 1;
			}
		}
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int CadCumpleExpReg ( const char * p_cAsciiz, const char * p_cExpReg )
{
	return ( CadCumpleExpRegExt ( p_cAsciiz, p_cExpReg, -1 ) );
}

int CadCumpleExpRegExt ( const char * p_cAsciiz, const char * p_cExpReg, int iMax )
{
	int iRes;
	int iLongCad;
	int iLongExpReg;

 	iLongCad = CadLongitudSeg ( p_cAsciiz, iMax ); 
	iLongExpReg = CadLongitud ( p_cExpReg ); 
	if ( ( iLongCad > 0 ) && ( iLongExpReg > 0 ) )
	{
		iRes = ExpRegSeCumple ( p_cExpReg, p_cAsciiz );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int CadNumCaracteres ( const char * p_cAsciiz )
{
	return ( CadNumCaracteresExt ( p_cAsciiz, -1 ) );
}

int CadNumPalabras ( const char * p_cAsciiz )
{
	return ( CadNumPalabrasSep ( p_cAsciiz, ' ' ) );
}

char * CadPalabra ( const char * p_cAsciiz, int iPalabra )
{
	return ( CadPalabraSep ( p_cAsciiz, iPalabra, ' ' ) );
}

int CadNumPalabrasSep ( const char * p_cAsciiz, char cSep )
{
	return ( CadNumPalabrasSepExt ( p_cAsciiz, cSep,0, -1 ) );
}

char * CadPalabraSep  ( const char * p_cAsciiz, int iPalabra, char cSep )
{
	return ( CadPalabraSepExt ( p_cAsciiz, iPalabra, cSep,0, -1 ) );
}

int CadNumPalabrasSepLit ( const char * p_cAsciiz, const char * p_cSep )
{
	return ( CadNumPalabrasSepLitExt ( p_cAsciiz, p_cSep, -1 ) );
}

char * CadPalabraSepLit ( const char * p_cAsciiz, int iPalabra, const char * p_cSep )
{
	return ( CadPalabraSepLitExt ( p_cAsciiz, iPalabra, p_cSep, -1 ) );
}

int CadNumCaracteresExt ( const char * p_cAsciiz, int iMax )
{
	int iRes;
	int iLong;
	int iCar;

	iLong = CadLongitudSeg ( p_cAsciiz, iMax ); 
	if ( iLong > 0 )  
	{
		iRes = 0;
		iCar = 0;
		while ( iCar < iLong )
		{
			if ( ( ASCIIEsLetra ( p_cAsciiz [ iCar ] ) == 1 ) ||
				 ( ASCIIEsDigito ( p_cAsciiz [ iCar ] ) == 1 ) )
			{
				iRes = iRes + 1;
			}
			iCar = iCar + 1;
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int CadNumPalabrasExt ( const char* p_cAsciiz, int iSepararSignos, int iMax )
{
	return ( CadNumPalabrasSepExt ( p_cAsciiz, ' ', iSepararSignos, iMax ) );
}

char* CadPalabraExt ( const char* p_cAsciiz, int iPalabra, int iSepararSignos, int iMax )
{
	return ( CadPalabraSepExt ( p_cAsciiz, iPalabra, ' ', iSepararSignos, iMax ) );
}

int CadNumPalabrasSepExt ( const char * p_cAsciiz, char cSep, int iSepararSignos, int iMax )
{
	int iRes;
	int iLong;
	int iCar;

	iLong = CadLongitudSeg ( p_cAsciiz, iMax ); 
	if ( ( iLong > 0 ) && ( cSep != (char) 0 ) ) 
	{
		iRes = 0;
		iCar = 0;
		while ( iCar < iLong )
		{
			if ( p_cAsciiz [ iCar ] == cSep )
			{
				iRes = iRes + 1;
			}
			else if ( ( iSepararSignos == 1 ) && ( ASCIIEsSigno ( p_cAsciiz [ iCar ] ) == 1 ) )
			{
				iRes = iRes + 1;
			}
			iCar = iCar + 1;
		}
		if ( ( p_cAsciiz [ iLong - 1 ] != cSep ) || ( ( iSepararSignos == 1 ) && ( ASCIIEsSigno ( p_cAsciiz [ iLong - 1 ] ) != 1 ) ) )
		{
			iRes = iRes + 1;
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

char * CadPalabraSepExt ( const char * p_cAsciiz, int iPalabra, char cSep, int iSepararSignos, int iMax )
{
	char *	p_cRes;
	int			iLong;
	int			iCar;
	int			iCont;
	int			iPosIni;
	int			iPosFin;
	int			iEnc;
	int			iCambio;

	iLong = CadLongitudSeg ( p_cAsciiz, iMax ); 
	if ( ( iLong > 0 ) && ( iPalabra >= 0 ) && ( cSep != (char) 0 ) ) 
	{
		iPosIni = 0;
		iPosFin = -1;
		iCar = 0;
		iCont = 0;
		iEnc = 0;
		while ( ( iCar < iLong ) && ( iEnc == 0 ) )
		{
			iCambio = 0;
			if ( p_cAsciiz [ iCar ] == cSep )
			{
				iCambio = 1;
			}
			else if ( ( iSepararSignos == 1 ) && ( ASCIIEsSigno ( p_cAsciiz [ iCar ] ) == 1 ) )
			{
				iCambio = 1;
			}
			else if ( iCar == iLong - 1 )
			{
				iCar = iLong;
				iCambio = 1;
			}
			if ( iCambio == 1 )
			{
				iPosFin = iCar - 1;
				if ( iCont == iPalabra )
				{
					iEnc = 1;
				}
				else
				{
					iPosIni = iPosFin + 2;
					iCont = iCont + 1;
				}
			}
			iCar = iCar + 1;
		}

		if ( iEnc == 1 )
		{
			if ( iPosFin >= iPosIni )
			{
				p_cRes = CadExtraerExt ( p_cAsciiz, iPosIni, iPosFin - iPosIni + 1, iMax );
			}
			else
			{
				p_cRes = NULL ;
			}
		}
		else
		{
			p_cRes = NULL ;
		}
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

int CadNumPalabrasSepLitExt ( const char * p_cAsciiz, const char * p_cSep, int iMax )
{
	int iRes;
	int iLong;
	int iLongSep;
	int iCar;

	iLong = CadLongitudSeg ( p_cAsciiz, iMax ); 
	iLongSep = CadLongitud ( p_cSep ); 
	if ( ( iLong > 0 ) && ( iLongSep > 0 ) ) 
	{
		iRes = 0;
		iCar = 0;
		while ( iCar < iLong )
		{
			iCar = CadBuscar ( p_cAsciiz, p_cSep, iCar );
			if ( iCar > 0 )
			{
				iRes = iRes + 1;
				iCar = iCar + iLongSep;
			}
			else 
			{
				iRes = iRes + 1;
				iCar = iLong;
			}
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

char * CadPalabraSepLitExt ( const char * p_cAsciiz, int iPalabra, const char * p_cSep, int iMax )
{
	char *	p_cRes;
	int 	iPal;
	int 	iLong;
	int 	iLongSep;
	int 	iCarIni;
	int 	iCarFin;

	iLong = CadLongitudSeg ( p_cAsciiz, iMax ); 
	iLongSep = CadLongitud ( p_cSep ); 
	if ( ( iLong > 0 ) && ( iLongSep > 0 ) ) 
	{
		iPal = 0;
		iCarIni = 0;
		p_cRes = NULL;
		while ( ( iCarIni < iLong ) && ( p_cRes == NULL ) )
		{
			iCarFin = CadBuscar ( p_cAsciiz, p_cSep, iCarIni );
			if ( iCarFin < 0 )
			{
				iCarFin = iLong - 1;
			}
			if ( iPal == iPalabra )
			{
				p_cRes = CadExtraer ( p_cAsciiz, iCarIni, iCarFin - iCarIni );
			}
			iPal = iPal + 1;
			iCarIni = iCarFin + iLongSep;
		}
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

double CadValorNumerico ( const char * p_cAsciiz )
{
	int				iLong;
	double			dValor;
	double			dPeso;
	int				iCar;
	unsigned int	uiCar;

	if ( ES_VALIDO ( p_cAsciiz ) )
	{
		dValor = 0.0;
		dPeso = 1.0;
		iLong = CadLongitud ( p_cAsciiz );
		if ( iLong > 6 )
		{
			iLong = 6;
		}
		for ( iCar = 0; iCar < iLong; iCar = iCar + 1 )
		{
			uiCar = (unsigned int)((unsigned char)p_cAsciiz [ iCar ]);
			dValor = dValor + ( (double) ( uiCar ) * dPeso );
			dPeso = dPeso * 256.0;
		}
	}
	else
	{
		dValor = -1.0;
	}
	return ( dValor );
}

char * CadEquivalente ( double dValor )
{
	double		dResto;
	int			iLong;
	char *		p_cRes;
	int			iCar;
	signed char	scCar;
	double		dCar;

	if ( dValor > 0.0 )
	{
		iLong = 0;
		dResto = dValor;
		while ( dResto > 256.0 )
		{
			dResto = dResto / 256.0;
			iLong = iLong + 1;
		}
		if ( dResto > 0.0 )
		{
			iLong = iLong + 1;
		}

		p_cRes = CadCrear ( iLong );
		if ( ES_VALIDO ( p_cRes ) )
		{
			iCar = 0;
			while ( iCar < iLong )
			{
				dCar = fmod ( dValor, 256.0 );
				dValor = dValor/ 256.0;
				scCar = (signed char) dCar;
				p_cRes [ iCar ] = (char) scCar;
				iCar = iCar + 1;
			}
		}
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

char * CadComponer ( const char * p_cAsciiz1, const char * p_cAsciiz2, char cSep )
{
	int		iLong1;
	int		iLong2;
	char *	p_cRes;

	iLong1 = CadLongitud ( p_cAsciiz1 ); 
	iLong2 = CadLongitud ( p_cAsciiz2 ); 

	if ( iLong1 + iLong2 > 0 )
	{
		p_cRes = CadCrear ( iLong1 + iLong2 + 1 );
		if ( ES_VALIDO ( p_cRes ) )
		{
			if ( iLong1 > 0 )
			{
				CadCopiar ( p_cRes, p_cAsciiz1 );
			}
			if ( ( iLong1 > 0 ) && ( iLong2 > 0 ) )
			{
				CadConcatenarCaracter ( p_cRes, cSep );
			}
			CadConcatenar ( p_cRes, p_cAsciiz2 );
		}
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

char * CadComponerEnvolviendo ( char cSep, char cIni, char cFin, ... )
{
	char *	p_cRes;
	va_list	valArgumentos;

	va_start ( valArgumentos, cFin );
	p_cRes = CadComponerVarArgExt ( cSep, cIni, cFin, valArgumentos );
	va_end ( valArgumentos );
	return ( p_cRes );
}

static char * CadComponerVarArgExt ( char cSep, char cIni, char cFin, va_list valArgumentos )
{
	char *	p_cCad;
	char *	p_cArg;
	char *	p_cRes;
	int		iLong;
	int		iFinal;

	p_cCad = CadCrear ( CAD_MAX_TAM );
	if ( ES_VALIDO ( p_cCad ) )
	{
		if ( cIni != ' ' )
		{
			CadCopiarCaracter ( p_cCad, cIni );
		}
		iFinal = 0;
		iLong = 1;
		while ( iFinal == 0 )
		{
			p_cArg = va_arg ( valArgumentos, char * );
			if ( _EsCadenaValida ( p_cArg ) == 1 )
			{
				if ( iLong + CadLongitud (  p_cArg ) + 1 < CAD_MAX_TAM )
				{
					if ( iLong > 1 )
					{
						CadConcatenarCaracter ( p_cCad, cSep );
						iLong = iLong + 1;
					}
					CadConcatenar ( p_cCad, p_cArg );
					iLong = iLong + CadLongitud (  p_cArg );
				}
				else
				{
					iFinal = 1;
				}
			}
			else
			{
				iFinal = 1;
			}
		}

		if ( iLong < CAD_MAX_TAM )
		{
			if ( cFin != ' ' )
			{
				CadConcatenarCaracter ( p_cCad, cFin );
			}
		}

		p_cRes = CadDuplicar ( p_cCad );
		MemLiberar ( (void **) &p_cCad );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

char * CadComponerVarios ( char cSep, ... )
{
	char *	p_cRes;
	va_list	valArgumentos;

	va_start ( valArgumentos,  cSep );
	p_cRes = CadComponerVarArg ( cSep, valArgumentos );
	va_end ( valArgumentos );
	return ( p_cRes );
}


int CadAplicarTrans ( char * p_cAsciiz, PFUNCHARC p_fTrans )
{
	return ( CadAplicarTransExt ( p_cAsciiz, p_fTrans, -1 ) );
}

char * CadTransformar ( const char * p_cAsciiz, PFUNCHARC p_fTrans )
{
	return ( CadTransformarExt ( p_cAsciiz, p_fTrans, -1 ) );
}

int CadCumpleCondCar ( const char * p_cAsciiz, PFUNINTC p_fVerif )
{
	return ( CadCumpleCondCarExt ( p_cAsciiz, p_fVerif, -1 ) );
}

int CadAplicarTransExt ( char * p_cAsciiz, PFUNCHARC p_fTrans, int iMax )
{
	int iRes;
	int iLong;
	int iCar;

	if ( p_fTrans != NULL )
	{
		iLong = CadLongitudSeg ( p_cAsciiz, iMax ); 
		iRes = 1;
		iCar = 0;
		while ( iCar < iLong )
		{
			p_cAsciiz [ iCar ] = p_fTrans ( p_cAsciiz [ iCar ] );
			iCar = iCar + 1;
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

char * CadTransformarExt ( const char * p_cAsciiz, PFUNCHARC p_fTrans, int iMax )
{
	char * p_cRes;
	int iLong;
	int iCar;

	if ( p_fTrans != NULL )
	{
		iLong = CadLongitudSeg ( p_cAsciiz, iMax ); 
		p_cRes = CadCrear ( iLong );
		if ( ES_VALIDO ( p_cRes ) )
		{
			iCar = 0;
			while ( iCar < iLong )
			{
				p_cRes [ iCar ] = p_fTrans ( p_cAsciiz [ iCar ] );
				iCar = iCar + 1;
			}
		}
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

int CadCumpleCondCarExt ( const char * p_cAsciiz, PFUNINTC p_fVerif, int iMax )
{
	int iRes;
	int iLong;
	int iCar;

	if ( p_fVerif != NULL )
	{
		iLong = CadLongitudSeg ( p_cAsciiz, iMax ); 
		if ( iLong > 0 )
		{
			iCar = 0;
			while ( ( iCar < iLong ) && ( p_fVerif ( p_cAsciiz [ iCar ] ) == 0 ) )
			{
				iCar = iCar + 1;
			}
			if ( p_fVerif ( p_cAsciiz [ iCar ] ) == 1 )
			{
				iRes = iCar;
			}
			else
			{
				iRes = -1;
			}
		}
		else
		{
			iRes = -1;
		}
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}


static char * CadComponerVarArg ( char cSep, va_list valArgumentos )
{
	return ( CadComponerVarArgExt ( cSep, ' ', ' ', valArgumentos ) );
}

char * CadEnvolver ( const char * p_cAsciiz, char cIniFin )
{
	int		iLong;
	char *	p_cRes;

	iLong = CadLongitud ( p_cAsciiz ); 
	p_cRes = CadCrear ( iLong + 2 );
	if ( ES_VALIDO ( p_cRes ) )
	{
		CadCopiarCaracter ( p_cRes, cIniFin );	
		CadConcatenar ( p_cRes, p_cAsciiz );
		CadConcatenarCaracter ( p_cRes, cIniFin );	
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

int CadEsTokenValido ( const char * p_cAsciiz )
{
	return ( CadEsTokenValidoExt ( p_cAsciiz, -1 ) );
}

int CadEsIdentificadorValido ( const char * p_cAsciiz )
{
	return ( CadEsIdentificadorValidoExt ( p_cAsciiz, -1 ) );
}

int CadEsTokenValidoExt ( const char * p_cAsciiz, int iMax )
{
	int		iPos;
	int		iRes;
	int		iLong;

	iLong = CadLongitudSeg ( p_cAsciiz, iMax );
	if ( iLong > 0 )
	{
		if ( ASCIIEsValidoInicioToken ( p_cAsciiz [ 0 ] ) == 1 )
		{
			iPos = 1;
			iRes = 1;
			while ( ( iRes == 1 ) && ( iPos < iLong ) )
			{
				if ( ASCIIEsValidoToken ( p_cAsciiz [ iPos ] ) == 0  )
				{
					iRes = 0;
				}
				iPos = iPos + 1;
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
	return ( iRes );
}

int CadEsIdentificadorValidoExt ( const char * p_cAsciiz, int iMax )
{
	int		iPos;
	int		iRes;
	int		iLong;

	iLong = CadLongitudSeg ( p_cAsciiz, iMax );
	if ( iLong > 0 )
	{
		iPos = 0;
		iRes = 1;
		while ( ( iRes == 1 ) && ( iPos < iLong ) )
		{
			if ( ASCIIEsValidoIdentificador ( p_cAsciiz [ iPos ] ) == 0  )
			{
				iRes = 0;
			}
			iPos = iPos + 1;
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}


/* NOTA: Esta rutina es una estimación. Habría que hacerlo utilizando la codificación interna
   de representación de tipos */
static int _EsCadenaValida ( char * p_cCad )
{
	int		iPos;
	int		iRes;
	byte	byCod;

	if ( ES_VALIDO ( p_cCad ) )
	{
		iPos = 0;
		iRes = 1;
		while ( ( *( p_cCad + iPos ) != (char) 0 ) && ( iPos < CAD_BASE_MAX_TAM ) )
		{
			byCod = (byte)(*( p_cCad + iPos ));
			if ( ( byCod == 127 )  || ( ( byCod < 32 ) &&  ( ( byCod < 8 ) || ( byCod > 13 ) ) ) )
			{
				iRes = 0;
			}
			iPos = iPos + 1;
		}
		if ( iPos >= CAD_BASE_MAX_TAM ) 
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

const char * CadValorNulo ()
{
	return ( VALOR_NULO );
}

void CadImprimirExt ( const char * p_cAsciiz, const char * p_cEtiqueta, char cSep, int iEnvolver )
{
	const char * p_cVal;
	const char * p_cEtiq;
	
	if ( ES_VALIDO ( p_cAsciiz ) )
	{
		p_cVal = p_cAsciiz;
	}
	else
	{
		p_cVal = VALOR_NULO;
	}
	if ( ES_VALIDO ( p_cEtiqueta ) )
	{
		p_cEtiq = p_cEtiqueta;
	}
	else
	{
		p_cEtiq = VALOR_NULO;
	}
	if ( iEnvolver == 1 )
	{
		printf ( "%s%c[%s]\n", p_cEtiq, cSep, p_cVal );
	}
	else
	{
		printf ( "%s%c%s\n", p_cEtiq, cSep, p_cVal );
	}
}

void CadImprimirXml ( const char * p_cAsciiz, const char * p_cEtiqueta )
{
	const char * p_cVal;
	const char * p_cEtiq;
	
	if ( ES_VALIDO ( p_cAsciiz ) )
	{
		p_cVal = p_cAsciiz;
	}
	else
	{
		p_cVal = VALOR_NULO;
	}
	if ( ES_VALIDO ( p_cEtiqueta ) )
	{
		p_cEtiq = p_cEtiqueta;
	}
	else
	{
		p_cEtiq = VALOR_NULO;
	}
	printf ( "<%s>%s</%s>\n", p_cEtiq, p_cVal, p_cEtiq );
}

void CadImprimirJson ( const char * p_cAsciiz, const char * p_cEtiqueta )
{
	const char * p_cVal;
	const char * p_cEtiq;
	
	if ( ES_VALIDO ( p_cAsciiz ) )
	{
		p_cVal = p_cAsciiz;
	}
	else
	{
		p_cVal = VALOR_NULO;
	}
	if ( ES_VALIDO ( p_cEtiqueta ) )
	{
		p_cEtiq = p_cEtiqueta;
	}
	else
	{
		p_cEtiq = VALOR_NULO;
	}
	printf ( "\"%s\": \"%s\"\n", p_cEtiq, p_cVal );
}
