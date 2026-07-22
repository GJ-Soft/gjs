/******************************************************************************/
/*                                  Byte.cpp                                  */
/*----------------------------------------------------------------------------*/
/* Librería:  GBase                                                           */
/* Versión:   1.0.0                                                           */
/* Fecha:     28/06/2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Fichero de código fuente que contiene la implementación de las rutinas     */
/* de carácter general de manejo de bytes.                                    */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#include "Byte.h"

#include "Memoria.h"
#include "CadenasBase.h"
#include "Hexadecimal.h"



/* Máscaras de obtenciónde los dos nibbles contenidos en un byte. */
#define BYTE_MASC_NIBBLE_SUP     0xF0
#define BYTE_MASC_NIBBLE_INF     0x0F

/* Desplazamientos de los dos nibbles en un byte. */
#define BYTE_DESP_NIBBLE_SUP     0x10
#define BYTE_DESP_NIBBLE_INF     0x01





nibble ByteNibbleInferior ( byte byDato )
{
	return ( (nibble) ( byDato & BYTE_MASC_NIBBLE_INF ) );
}


nibble ByteNibbleSuperior ( byte byDato )
{
	return ( (nibble) ( ( byDato & BYTE_MASC_NIBBLE_SUP ) / BYTE_DESP_NIBBLE_SUP ) );
}


byte ByteComponer ( nibble nibSup, nibble nibInf )
{
	return ( (byte) ( ( ( nibSup & BYTE_MASC_NIBBLE_INF ) * BYTE_DESP_NIBBLE_SUP ) | ( nibInf & BYTE_MASC_NIBBLE_INF ) ) ); 
}

char * ByteAHex ( byte byValor, char * p_cValor )
{
	int			iVal1;
	int			iVal0;
	char *	p_cRes;

	if ( ES_VALIDO ( p_cValor ) )
	{
		p_cRes = p_cValor;
	}
	else
	{
		p_cRes = CadCrear ( 2 );
	}
	if ( ES_VALIDO ( p_cRes ) )
	{
		iVal1 = byValor / 0x10;
		iVal0 = byValor % 0x10;
		p_cRes [ 0 ] = HexDigito ( iVal1 );
		p_cRes [ 1 ] = HexDigito ( iVal0 );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

byte HexAByte ( const char * p_cValor )
{
	int		iVal1;
	int		iVal0;
	byte	byRes;

	if ( ES_VALIDO ( p_cValor ) )
	{
		iVal1 = HexValor ( p_cValor [ 0 ] );
		iVal0 = HexValor ( p_cValor [ 1 ] );
		if ( ( HexEsNumValido ( iVal0 ) == 1 ) && ( HexEsNumValido ( iVal1 ) == 1 ) )
		{
			byRes = (byte)( ( iVal1 * 0x10 ) + iVal0 );
		}
		else
		{
			byRes = 0x0;
		}
	}
	else
	{
		byRes = 0x0;
	}
	return ( byRes );
}







