/******************************************************************************/
/*                              CadenasBase.cpp                               */
/*----------------------------------------------------------------------------*/
/* Librería:  GBase                                                           */
/* Versión:   1.0.0                                                           */
/* Fecha:     28/06/2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Fichero de código fuente que contiene la implementación de las rutinas     */
/* generales para el manejo general de cadenas.                               */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#include "CadenasBase.h"



#include "BaseConfig.h"
#include "Memoria.h"
#include "Errores.h"


#define ASCII_MIN_LETRA_MIN 		ASCII_A_MIN
#define ASCII_MAX_LETRA_MIN 		ASCII_Z_MIN
#define ASCII_MIN_LETRA_MAY			ASCII_A_MAY
#define ASCII_MAX_LETRA_MAY 		ASCII_Z_MAY
#define ASCII_MIN_NUMERO			ASCII_0
#define ASCII_MAX_NUMERO 			ASCII_9





char * CadCrear ( int iLong )
{
	char *	p_cCad;
	int		iPos;

	p_cCad = NULL;
	if ( iLong >= 0 )
	{
		p_cCad = (char *) MemReservar ( ( iLong + 1 ) * sizeof ( char ) );
		if ( ES_VALIDO ( p_cCad ) )
		{
			for ( iPos = 0; iPos <= iLong; iPos = iPos + 1 ) 
			{	
				p_cCad [ iPos ] = (char) 0; 
			}
		}
		else
		{
			ERROR_ESTABLECER ( ERR_MEMORIA_INSUFICIENTE );
		}
	}
	else
	{
		ERROR_ESTABLECER ( ERR_PARAMETROS );
	}
	return ( p_cCad );
}

int CadLongitud ( const char * p_cAsciiz )
{
	int iMax;
	int iTam;
	int iCar;
	int iFin;

	iCar = 0;
	iTam = 0;
	iFin = 0;
	if ( ES_VALIDO ( p_cAsciiz ) ) 
	{ 
		iMax = CAD_BASE_MAX_TAM;
		while ( ( iCar < iMax ) && ( iFin == 0 ) )
		{
			if ( p_cAsciiz [ iCar ] == (char) 0 )
			{
				iFin = 1;
			}
			else
			{
				iTam = iTam + 1;
			}
			iCar = iCar +1;
		}
	}
	else
	{
		iTam = -1;
		ERROR_ESTABLECER ( ERR_PARAMETROS );
	}
	return ( iTam );
}

int CadLongitudSeg ( const char * p_cAsciiz, int iMax )
{
	int iTam;
	int iCar;
	int iFin;

	iCar = 0;
	iTam = 0;
	iFin = 0;
	if ( ES_VALIDO ( p_cAsciiz ) ) 
	{
		if ( ( iMax < 0 ) || ( iMax > CAD_BASE_MAX_TAM ) )
		{
			iMax = CAD_BASE_MAX_TAM;
		}
		while ( ( iCar < iMax ) && ( iFin == 0 ) )
		{
			if ( p_cAsciiz [ iCar ] == (char) 0 )
			{
				iFin = 1;
			}
			else
			{
				iTam = iTam + 1;
			}
			iCar = iCar +1;
		}
	}
	else
	{
		iTam = -1;
		ERROR_ESTABLECER ( ERR_PARAMETROS );
	}
	return ( iTam );
}

void CadInicializar ( char * p_cAsciiz, int iMax )
{
	int	iMax1;
	int	iPos;
	int iFin;

	if ( ES_VALIDO ( p_cAsciiz ) )
	{
		if ( iMax > 0 ) 
		{
			iMax1 = iMax;
		}
		else
		{
			iMax1 = CAD_BASE_MAX_TAM;
		}
		iFin = 0;
		iPos = 0;
		while ( ( iPos < iMax1 ) && ( iFin == 0 ) )
		{
			if ( ( iMax <= 0 ) && ( p_cAsciiz [ iPos ] != (char) 0 ) )
			{
				iFin = 1;
			}
			else
			{
				p_cAsciiz [ iPos ] = (char) 0; 
			}
			iPos = iPos + 1; 
		}
	}
	else
	{
		ERROR_ESTABLECER ( ERR_PARAMETROS );
	}
}

char * CadDuplicar ( const char * p_cAsciiz )
{
	int		iLong;
	int		iPos;
	char *	p_cCopia;

	iLong = CadLongitud ( p_cAsciiz ); 
	if ( iLong >= 0 )
	{
		p_cCopia = CadCrear ( iLong );
		if ( ES_VALIDO ( p_cCopia ) )
		{
			for ( iPos = 0; iPos < iLong; iPos = iPos + 1 ) 
			{	
				p_cCopia [ iPos ] = p_cAsciiz [ iPos ]; 
			}
			p_cCopia [ iLong ] = (char) 0;
		}
		else
		{
			ERROR_ESTABLECER ( ERR_MEMORIA_INSUFICIENTE );
		}
	}
	else
	{
		ERROR_ESTABLECER ( ERR_PARAMETROS );
		p_cCopia = NULL;
	}
	return ( p_cCopia );
}

char * CadDuplicarSeg ( const char * p_cAsciiz, int iMax )
{
	int		iLong;
	int		iPos;
	char *	p_cCopia;

	iLong = CadLongitudSeg ( p_cAsciiz, iMax ); 
	if ( iLong >= 0 )
	{
		p_cCopia = CadCrear ( iLong );
		if ( ES_VALIDO ( p_cCopia ) )
		{
			for ( iPos = 0; iPos < iLong; iPos = iPos + 1 ) 
			{	
				p_cCopia [ iPos ] = p_cAsciiz [ iPos ]; 
			}
			p_cCopia [ iLong ] = (char) 0;
		}
		else
		{
			ERROR_ESTABLECER ( ERR_MEMORIA_INSUFICIENTE );
		}
	}
	else
	{
		ERROR_ESTABLECER ( ERR_PARAMETROS );
		p_cCopia = NULL;
	}
	return ( p_cCopia );
}

unichar * CadUniCrear ( int iLong )
{
# if ( defined ( MODO_UNICODE ) )
	unichar *	p_ucCad;
	int			iPos;
# endif 

# if ( !defined ( MODO_UNICODE ) )
	return ( (unichar *) CadCrear ( iLong ) );
# else
	p_ucCad = NULL;
	if ( iLong >= 0 )
	{
		p_ucCad = (unichar *) MemReservar ( ( iLong + 1 ) * sizeof ( unichar ) );
		if ( ES_VALIDO ( p_ucCad ) )
		{
			for ( iPos = 0; iPos <= iLong; iPos = iPos + 1 ) 
			{	
				p_ucCad [ iPos ] = (unichar) 0; 
			}
		}
		else
		{
			ERROR_ESTABLECER ( ERR_MEMORIA_INSUFICIENTE );
		}
	}
	else
	{
		ERROR_ESTABLECER ( ERR_PARAMETROS );
	}
	return ( p_ucCad );
# endif 
}

int CadUniLongitud ( const unichar * p_ucValor )
{
	int	iMax;
	int iTam;
	int iCar;
	int iFin;

	iCar = 0;
	iTam = 0;
	iFin = 0;
	if ( ES_VALIDO ( p_ucValor ) ) 
	{ 
		iMax = CAD_BASE_MAX_TAM;
		while ( ( iCar < iMax ) && ( iFin == 0 ) )
		{
			if ( p_ucValor [ iCar ] == (unichar) 0 )
			{
				iFin = 1;
			}
			else
			{
				iTam = iTam + 1;
			}
			iCar = iCar +1;
		}
	}
	else
	{
		iTam = -1;
		ERROR_ESTABLECER ( ERR_PARAMETROS );
	}
	return ( iTam );
}

int CadUniLongitudSeg ( const unichar * p_ucValor, int iMax )
{
	int iTam;
	int iCar;
	int iFin;

	iCar = 0;
	iTam = 0;
	iFin = 0;
	if ( ES_VALIDO ( p_ucValor ) ) 
	{ 
		if ( ( iMax < 0 ) || ( iMax > CAD_BASE_MAX_TAM ) )
		{
			iMax = CAD_BASE_MAX_TAM;
		}
		while ( ( iCar < iMax ) && ( iFin == 0 ) )
		{
			if ( p_ucValor [ iCar ] == (unichar) 0 )
			{
				iFin = 1;
			}
			else
			{
				iTam = iTam + 1;
			}
			iCar = iCar +1;
		}
	}
	else
	{
		iTam = -1;
		ERROR_ESTABLECER ( ERR_PARAMETROS );
	}
	return ( iTam );
}

void CadUniInicializar ( unichar * p_ucValor, int iMax )
{
	int	iMax1;
	int	iPos;
	int	iFin;

	if ( ES_VALIDO ( p_ucValor ) )
	{
		if ( iMax > 0 ) 
		{
			iMax1 = iMax;
		}
		else
		{
			iMax1 = CAD_BASE_MAX_TAM;
		}
		iFin = 0;
		iPos = 0;
		while ( ( iPos < iMax1 ) && ( iFin == 0 ) )
		{
			if ( ( iMax <= 0 ) && ( p_ucValor [ iPos ] != (unichar) 0 ) )
			{
				iFin = 1;
			}
			else
			{
				p_ucValor [ iPos ] = (unichar) 0; 
			}
			iPos = iPos + 1; 
		}
	}
	else
	{
		ERROR_ESTABLECER ( ERR_PARAMETROS );
	}
}

unichar * CadUniDuplicar ( const unichar * p_ucValor )
{
	int		iLong;
	int		iPos;
	unichar *	p_cCopia;

	iLong = CadUniLongitud ( p_ucValor ); 
	if ( iLong >= 0 )
	{
		p_cCopia = CadUniCrear ( iLong );
		if ( ES_VALIDO ( p_cCopia ) )
		{
			for ( iPos = 0; iPos < iLong; iPos = iPos + 1 ) 
			{	
				p_cCopia [ iPos ] = p_ucValor [ iPos ]; 
			}
			p_cCopia [ iLong ] = (unichar) 0;
		}
		else
		{
			ERROR_ESTABLECER ( ERR_MEMORIA_INSUFICIENTE );
		}
	}
	else
	{
		ERROR_ESTABLECER ( ERR_PARAMETROS );
		p_cCopia = NULL;
	}
	return ( p_cCopia );
}

int CadComparar ( const char * p_cAsciiz1, const char * p_cAsciiz2 )
{
	return ( CadCompararExt ( p_cAsciiz1, p_cAsciiz2, -1, -1 ) );
}

int CadCompararExt ( const char * p_cAsciiz1, const char * p_cAsciiz2, int iMax1, int iMax2 )
{
	int iRes;
	int iCar;
	int iLong1;
	int iLong2;
	int iMinLong;

	if ( ES_VALIDO (  p_cAsciiz1 ) && ES_VALIDO (  p_cAsciiz2 ) ) 
	{
		iLong1 = CadLongitudSeg ( p_cAsciiz1, iMax1 ); 
		iLong2 = CadLongitudSeg ( p_cAsciiz2, iMax2 ); 
		iMinLong = MIN ( iLong1, iLong2 );

		iRes = COMP_IGUAL;
		iCar = 0; 
		while ( ( iCar < iMinLong ) && ( iRes == COMP_IGUAL ) )  
		{
			if ( p_cAsciiz1 [ iCar ] < p_cAsciiz2 [ iCar ] )
			{
				iRes = COMP_MENOR;
			}
			else if ( p_cAsciiz1 [ iCar ] > p_cAsciiz2 [ iCar ] )
			{
				iRes = COMP_MAYOR;
			}
			iCar = iCar + 1;
		}
		if ( iRes == COMP_IGUAL )
		{
			if ( iLong1 < iLong2 )
			{
				iRes = COMP_MENOR;
			} 
			else if ( iLong2 < iLong1 ) 
			{
				iRes = COMP_MAYOR;
			} 
		}
	}
	else if ( ES_NULO ( p_cAsciiz1 ) && ES_NULO ( p_cAsciiz2 ) ) 
	{
		iRes = COMP_IGUAL;
	} 
	else if ( ES_NULO ( p_cAsciiz1 ) )
	{
		iRes = COMP_MENOR;
	} 
	else 
	{
		iRes = COMP_MAYOR;
	} 
	return ( iRes );
}

int CadEsAlfanumericoValido ( const char * p_cAsciiz )
{
	return ( CadEsAlfanumericoValidoExt ( p_cAsciiz, -1 ) );
}

int CadEsAlfanumericoValidoExt ( const char * p_cAsciiz, int iMax )
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
			if ( !( ( ( p_cAsciiz [ iPos ] >= ASCII_MIN_LETRA_MAY ) && ( p_cAsciiz [ iPos ] <= ASCII_MAX_LETRA_MAY ) ) 
					|| ( ( p_cAsciiz [ iPos ] >= ASCII_MIN_LETRA_MIN ) && ( p_cAsciiz [ iPos ] <= ASCII_MAX_LETRA_MIN ) ) 
					|| ( ( p_cAsciiz [ iPos ] >= ASCII_MIN_NUMERO ) && ( p_cAsciiz [ iPos ] <= ASCII_MAX_NUMERO ) ) ) 
				)
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

const char * CadValorSeguro ( const char * p_cAsciiz )
{
	if ( ES_VALIDO ( p_cAsciiz ) )
	{
		return ( (const char *) p_cAsciiz );
	}
	else
	{
		return ( VALOR_NULO );
	}
}

void CadImprimir ( const char * p_cAsciiz )
{
	if ( ES_VALIDO ( p_cAsciiz ) )
	{
		printf ( "%s\n", p_cAsciiz );
	}
	else
	{
		printf ( "%s\n", VALOR_NULO );
	}
}

void CadImprimirEnLineas ( const char * p_cAsciiz, int iTamLinea )
{
	int iTam;
	
	if ( iTamLinea > 6 ) 
	{
		if ( ES_VALIDO ( p_cAsciiz ) )
		{
			iTam = CadLongitud ( p_cAsciiz );
			for ( int iCar = 0; iCar < iTam; iCar = iCar + iTamLinea) 
			{
				printf ( "%.*s\n", iTamLinea, p_cAsciiz + iCar );
			}
		}
		else
		{
			printf ( "%s\n", VALOR_NULO );
		}
	}
}






