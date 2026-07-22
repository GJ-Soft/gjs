/******************************************************************************/
/*                             ASCIIEstandar.cpp                              */
/*----------------------------------------------------------------------------*/
/* Librer�a:  GBase                                                           */
/* Versi�n:   1.0.0                                                           */
/* Fecha:     28/06/2008                                                      */
/* Autor:     Gin�s Jim�nez S�nchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripci�n:                                                               */
/* Fichero de c�digo fuente que contiene la implementaci�n de las rutinas     */
/* de car�cter general de consulta y conversi�n de car�cteres en la           */
/* codificaci�n ASCII est�nar (0-127).                                        */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#include "BaseConfig.h"
#include "ASCIIEstandar.h"





using namespace std;


namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {



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


bool ASCIIEsCodigoControl ( char cVal )
{
	int iCod = ASCIICodigo ( cVal );
	return ( ( iCod <= ASCII_US ) || ( iCod == ASCII_DEL ) );
}


bool ASCIIEsNUL ( char cVal )
{
	int iCod = ASCIICodigo ( cVal );	
	return ( iCod == ASCII_NUL );
}


bool ASCIIEsSOH ( char cVal )
{
	int iCod = ASCIICodigo ( cVal );	
	return ( iCod == ASCII_SOH );
}


bool ASCIIEsSTX ( char cVal )
{
	int iCod = ASCIICodigo ( cVal );	
	return ( iCod == ASCII_STX );
}


bool ASCIIEsETX ( char cVal )
{
	int iCod = ASCIICodigo ( cVal );	
	return ( iCod == ASCII_ETX );
}


bool ASCIIEsEOT ( char cVal )
{
	int iCod = ASCIICodigo ( cVal );	
	return ( iCod == ASCII_EOT );
}


bool ASCIIEsENQ ( char cVal )
{
	int iCod = ASCIICodigo ( cVal );	
	return ( iCod == ASCII_ENQ );
}


bool ASCIIEsACK ( char cVal )
{
	int iCod = ASCIICodigo ( cVal );	
	return ( iCod == ASCII_ACK );
}


bool ASCIIEsBEL ( char cVal )
{
	int iCod = ASCIICodigo ( cVal );	
	return ( iCod == ASCII_BEL );
}


bool ASCIIEsBS  ( char cVal )
{
	int iCod = ASCIICodigo ( cVal );	
	return ( iCod == ASCII_BS );
}


bool ASCIIEsTAB ( char cVal )
{
	int iCod = ASCIICodigo ( cVal );	
	return ( iCod == ASCII_TAB );
}


bool ASCIIEsLF ( char cVal )
{
	int iCod = ASCIICodigo ( cVal );	
	return ( iCod == ASCII_LF );
}


bool ASCIIEsVT ( char cVal )
{
	int iCod = ASCIICodigo ( cVal );	
	return ( iCod == ASCII_VT );
}


bool ASCIIEsFF ( char cVal )
{
	int iCod = ASCIICodigo ( cVal );	
	return ( iCod == ASCII_FF );
}


bool ASCIIEsCR ( char cVal )
{
	int iCod = ASCIICodigo ( cVal );	
	return ( iCod == ASCII_CR );
}


bool ASCIIEsSO ( char cVal )
{
	int iCod = ASCIICodigo ( cVal );	
	return ( iCod == ASCII_SO );
}


bool ASCIIEsST ( char cVal )
{
	int iCod = ASCIICodigo ( cVal );	
	return ( iCod == ASCII_ST );
}


bool ASCIIEsSLE ( char cVal )
{
	int iCod = ASCIICodigo ( cVal );	
	return ( iCod == ASCII_SLE );
}


bool ASCIIEsDC1 ( char cVal )
{
	int iCod = ASCIICodigo ( cVal );	
	return ( iCod == ASCII_DC1 );
}


bool ASCIIEsDC2 ( char cVal )
{
	int iCod = ASCIICodigo ( cVal );	
	return ( iCod == ASCII_DC2 );
}


bool ASCIIEsDC3 ( char cVal )
{
	int iCod = ASCIICodigo ( cVal );	
	return ( iCod == ASCII_DC3 );
}


bool ASCIIEsDC4 ( char cVal )
{
	int iCod = ASCIICodigo ( cVal );	
	return ( iCod == ASCII_DC4 );
}


bool ASCIIEsNAK ( char cVal )
{
	int iCod = ASCIICodigo ( cVal );	
	return ( iCod == ASCII_NAK );
}


bool ASCIIEsSYN ( char cVal )
{
	int iCod = ASCIICodigo ( cVal );	
	return ( iCod == ASCII_SYN );
}


bool ASCIIEsETB ( char cVal )
{
	int iCod = ASCIICodigo ( cVal );	
	return ( iCod == ASCII_ETB );
}


bool ASCIIEsCAN ( char cVal )
{
	int iCod = ASCIICodigo ( cVal );	
	return ( iCod == ASCII_CAN );
}


bool ASCIIEsEM ( char cVal )
{
	int iCod = ASCIICodigo ( cVal );	
	return ( iCod == ASCII_EM );
}


bool ASCIIEsSTB ( char cVal )
{
	int iCod = ASCIICodigo ( cVal );	
	return ( iCod == ASCII_STB );
}


bool ASCIIEsESC ( char cVal )
{
	int iCod = ASCIICodigo ( cVal );	
	return ( iCod == ASCII_ESC );
}


bool ASCIIEsFS ( char cVal )
{
	int iCod = ASCIICodigo ( cVal );	
	return ( iCod == ASCII_FS );
}


bool ASCIIEsGS ( char cVal )
{
	int iCod = ASCIICodigo ( cVal );	
	return ( iCod == ASCII_GS );
}


bool ASCIIEsRS ( char cVal )
{
	int iCod = ASCIICodigo ( cVal );	
	return ( iCod == ASCII_RS );
}


bool ASCIIEsUS ( char cVal )
{
	int iCod = ASCIICodigo ( cVal );	
	return ( iCod == ASCII_US );
}


bool ASCIIEsDEL ( char cVal )
{
	int iCod = ASCIICodigo ( cVal );	
	return ( iCod == ASCII_DEL );
}



 			}
		}
	}
}







