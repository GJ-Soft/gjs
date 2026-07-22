/******************************************************************************/
/*                             ASCIIEstandar.cpp                              */
/*----------------------------------------------------------------------------*/
/* Librería:  GBase                                                           */
/* Versión:   1.0.0                                                           */
/* Fecha:     28/06/2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Fichero de código fuente que contiene la implementación de las rutinas     */
/* de carácter general de consulta y conversión de carácteres en la           */
/* codificación ASCII estánar (0-127).                                        */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#include "ASCIIEstandar.h"






/* Rutinas: */
int ASCIICodigo ( char cVal )
{
	int iVal;

	iVal = (int) cVal;
	return ( iVal );
}


char ASCIICaracter ( int iCod )
{
	return ( (char) iCod );
}


int ASCIIEsCodigoControl ( char cVal )
{
	int iRes;
	int iCod;

	iCod = ASCIICodigo ( cVal );	
	if ( iCod < ASCII_US ) 
	{
		iRes = 1;
	}
	else if ( iCod == ASCII_DEL )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int ASCIIEsCodigoNoImprimible ( char cVal )
{
	int iRes;

	if ( ( ASCIIEsCodigoControl ( cVal ) == 1 ) &&
		( ASCIIEsCodigoControlImprimible ( cVal ) == 0 ) )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int ASCIIEsCodigoControlImprimible ( char cVal )
{
	int iRes; 
	int iCod;

	iCod = ASCIICodigo ( cVal );	
	if ( ( iCod == ASCII_TAB ) || 
		 ( iCod == ASCII_LF ) ||
		 ( iCod == ASCII_CR ) ||
		 ( iCod == ASCII_BS ) ||
		 ( iCod == ASCII_VT ) ||
		 ( iCod == ASCII_FF ) )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}
int ASCIIEsNUL ( char cVal )
{
	int iRes;
	int iCod;

	iCod = ASCIICodigo ( cVal );	
	if ( iCod == ASCII_NUL ) 
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}


int ASCIIEsSOH ( char cVal )
{
	int iRes;
	int iCod;

	iCod = ASCIICodigo ( cVal );	
	if ( iCod == ASCII_SOH ) 
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}


int ASCIIEsSTX ( char cVal )
{
	int iRes;
	int iCod;

	iCod = ASCIICodigo ( cVal );	
	if ( iCod == ASCII_STX ) 
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}


int ASCIIEsETX ( char cVal )
{
	int iRes;
	int iCod;

	iCod = ASCIICodigo ( cVal );	
	if ( iCod == ASCII_ETX ) 
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}


int ASCIIEsEOT ( char cVal )
{
	int iRes;
	int iCod;

	iCod = ASCIICodigo ( cVal );	
	if ( iCod == ASCII_EOT ) 
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}


int ASCIIEsENQ ( char cVal )
{
	int iRes;
	int iCod;

	iCod = ASCIICodigo ( cVal );	
	if ( iCod == ASCII_ENQ ) 
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}


int ASCIIEsACK ( char cVal )
{
	int iRes;
	int iCod;

	iCod = ASCIICodigo ( cVal );	
	if ( iCod == ASCII_ACK ) 
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}


int ASCIIEsBEL ( char cVal )
{
	int iRes;
	int iCod;

	iCod = ASCIICodigo ( cVal );	
	if ( iCod == ASCII_BEL ) 
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}


int ASCIIEsBS  ( char cVal )
{
	int iRes;
	int iCod;

	iCod = ASCIICodigo ( cVal );	
	if ( iCod == ASCII_BS ) 
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}


int ASCIIEsTAB ( char cVal )
{
	int iRes;
	int iCod;

	iCod = ASCIICodigo ( cVal );	
	if ( iCod == ASCII_TAB ) 
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}


int ASCIIEsLF ( char cVal )
{
	int iRes;
	int iCod;

	iCod = ASCIICodigo ( cVal );	
	if ( iCod == ASCII_LF ) 
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}


int ASCIIEsVT ( char cVal )
{
	int iRes;
	int iCod;

	iCod = ASCIICodigo ( cVal );	
	if ( iCod == ASCII_VT ) 
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}


int ASCIIEsFF ( char cVal )
{
	int iRes;
	int iCod;

	iCod = ASCIICodigo ( cVal );	
	if ( iCod == ASCII_FF ) 
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}


int ASCIIEsCR ( char cVal )
{
	int iRes;
	int iCod;

	iCod = ASCIICodigo ( cVal );	
	if ( iCod == ASCII_CR ) 
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}


int ASCIIEsSO ( char cVal )
{
	int iRes;
	int iCod;

	iCod = ASCIICodigo ( cVal );	
	if ( iCod == ASCII_SO ) 
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}


int ASCIIEsST ( char cVal )
{
	int iRes;
	int iCod;

	iCod = ASCIICodigo ( cVal );	
	if ( iCod == ASCII_ST ) 
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}


int ASCIIEsSLE ( char cVal )
{
	int iRes;
	int iCod;

	iCod = ASCIICodigo ( cVal );	
	if ( iCod == ASCII_SLE ) 
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}


int ASCIIEsDC1 ( char cVal )
{
	int iRes;
	int iCod;

	iCod = ASCIICodigo ( cVal );	
	if ( iCod == ASCII_DC1 ) 
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}


int ASCIIEsDC2 ( char cVal )
{
	int iRes;
	int iCod;

	iCod = ASCIICodigo ( cVal );	
	if ( iCod == ASCII_DC2 ) 
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}


int ASCIIEsDC3 ( char cVal )
{
	int iRes;
	int iCod;

	iCod = ASCIICodigo ( cVal );	
	if ( iCod == ASCII_DC3 ) 
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}


int ASCIIEsDC4 ( char cVal )
{
	int iRes;
	int iCod;

	iCod = ASCIICodigo ( cVal );	
	if ( iCod == ASCII_DC4 ) 
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}


int ASCIIEsNAK ( char cVal )
{
	int iRes;
	int iCod;

	iCod = ASCIICodigo ( cVal );	
	if ( iCod == ASCII_NAK ) 
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}


int ASCIIEsSYN ( char cVal )
{
	int iRes;
	int iCod;

	iCod = ASCIICodigo ( cVal );	
	if ( iCod == ASCII_SYN ) 
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}


int ASCIIEsETB ( char cVal )
{
	int iRes;
	int iCod;

	iCod = ASCIICodigo ( cVal );	
	if ( iCod == ASCII_ETB ) 
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}


int ASCIIEsCAN ( char cVal )
{
	int iRes;
	int iCod;

	iCod = ASCIICodigo ( cVal );	
	if ( iCod == ASCII_CAN ) 
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}


int ASCIIEsEM ( char cVal )
{
	int iRes;
	int iCod;

	iCod = ASCIICodigo ( cVal );	
	if ( iCod == ASCII_EM ) 
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}


int ASCIIEsSTB ( char cVal )
{
	int iRes;
	int iCod;

	iCod = ASCIICodigo ( cVal );	
	if ( iCod == ASCII_STB ) 
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}


int ASCIIEsESC ( char cVal )
{
	int iRes;
	int iCod;

	iCod = ASCIICodigo ( cVal );	
	if ( iCod == ASCII_ESC ) 
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}


int ASCIIEsFS ( char cVal )
{
	int iRes;
	int iCod;

	iCod = ASCIICodigo ( cVal );	
	if ( iCod == ASCII_FS ) 
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}


int ASCIIEsGS ( char cVal )
{
	int iRes;
	int iCod;

	iCod = ASCIICodigo ( cVal );	
	if ( iCod == ASCII_GS ) 
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}


int ASCIIEsRS ( char cVal )
{
	int iRes;
	int iCod;

	iCod = ASCIICodigo ( cVal );	
	if ( iCod == ASCII_RS )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}


int ASCIIEsUS ( char cVal )
{
	int iRes;
	int iCod;

	iCod = ASCIICodigo ( cVal );	
	if ( iCod == ASCII_US ) 
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}


int ASCIIEsDEL ( char cVal )
{
	int iRes;
	int iCod;

	iCod = ASCIICodigo ( cVal );	
	if ( iCod == ASCII_DEL ) 
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}








