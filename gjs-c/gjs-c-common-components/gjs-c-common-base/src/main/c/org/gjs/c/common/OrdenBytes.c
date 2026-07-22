/******************************************************************************/
/*                               OrdenBytes.cpp                               */
/*----------------------------------------------------------------------------*/
/* Librería:  GBase                                                           */
/* Versión:   1.0.0                                                           */
/* Fecha:     28/06/2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Fichero de código fuente que contiene la implementación de las rutinas     */
/* para detectar el orden de bytes en memoria de la máquina: big endian,      */
/* little endian o mixto.                                                     */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#include "OrdenBytes.h"



#include "BaseConfig.h"
#include "Memoria.h"
#include "Errores.h"






static int	g_iNumBytesOrden = 4;
static int	g_iOrdenBytes = -1;
static int	g_pOrdenBytes [ 4 ] = { 0, 1, 2, 3 };






static void CalcularOrdenBytes ()
{ 
# if ( defined ( GNU ) && defined ( BYTE_ORDER ) )
#  if ( BYTE_ORDER == LITTLE_ENDIAN )
	g_iOrdenBytes =  BYTE_ORDEN_NORMAL;
#  elif ( BYTE_ORDER == BIG_ENDIAN )
	g_iOrdenBytes = BYTE_ORDEN_INVERTIDO;
#  elif ( BYTE_ORDER == PDP_ENDIAN )
	g_iOrdenBytes =  BYTE_ORDEN_MIXTO;
#  else
#   if ( defined ( BYTE4 ) )
	byte4			by4Endian;
	byte *	p_byValor;
	int		iByte;

	g_iNumBytesOrden = 4;
	by4Endian = 0x01020304; 
	p_byValor = (byte *)(&by4Endian);

	for ( iByte = 0; iByte < g_iNumBytesOrden; iByte = iByte + 1 )
	{
		g_pOrdenBytes [ iByte ] = *( p_byValor + iByte );
	}
	if ( g_pOrdenBytes [ 0 ] == 1 )
	{
		g_iOrdenBytes =  BYTE_ORDEN_NORMAL;
	}
	else if ( g_pOrdenBytes [ 0 ] == 4 )
	{
		g_iOrdenBytes = BYTE_ORDEN_INVERTIDO;
	}
	else
	{
		g_iOrdenBytes =  BYTE_ORDEN_MIXTO;
	}
#   elif ( defined ( BYTE2 ) )
	byte2			by2Endian;
	byte *	p_byValor;
	int		iByte;

	g_iNumBytesOrden = 2;
	by2Endian = 0x0102;
	p_byValor = (byte *)(&by2Endian);

	for ( iByte = 0; iByte < g_iNumBytesOrden; iByte = iByte + 1 )
	{
		g_pOrdenBytes [ iByte ] = *( p_byValor + iByte );
	}
	if ( g_pOrdenBytes [ 0 ] == 1 )
	{
		g_iOrdenBytes =  BYTE_ORDEN_NORMAL;
	}
 	else
	{
		g_iOrdenBytes = BYTE_ORDEN_INVERTIDO;
	}
#   else
	g_iOrdenBytes = BYTE_ORDEN_INVERTIDO;
#   endif

#  endif
#else
#  if ( defined ( BYTE4 ) )
	byte4			by4Endian;
	byte *	p_byValor;
	int		iByte;

	g_iNumBytesOrden = 4;
	by4Endian = 0x01020304; 
	p_byValor = (byte *)(&by4Endian);

	for ( iByte = 0; iByte < g_iNumBytesOrden; iByte = iByte + 1 )
	{
		g_pOrdenBytes [ iByte ] = *( p_byValor + iByte );
	}
	if ( g_pOrdenBytes [ 0 ] == 1 )
	{
		g_iOrdenBytes =  BYTE_ORDEN_NORMAL;
	}
	else if ( g_pOrdenBytes [ 0 ] == 4 )
	{
		g_iOrdenBytes = BYTE_ORDEN_INVERTIDO;
	}
	else
	{
		g_iOrdenBytes =  BYTE_ORDEN_MIXTO;
	}
#  elif ( defined ( BYTE2 ) )
	byte2			by2Endian;
	byte *	p_byValor;
	int		iByte;

	g_iNumBytesOrden = 2;
	by2Endian = 0x0102;
	p_byValor = (byte *)(&by2Endian);

	for ( iByte = 0; iByte < g_iNumBytesOrden; iByte = iByte + 1 )
	{
		g_pOrdenBytes [ iByte ] = *( p_byValor + iByte );
	}
	if ( g_pOrdenBytes [ 0 ] == 1 )
	{
		g_iOrdenBytes =  BYTE_ORDEN_NORMAL;
	}
	else
	{
		g_iOrdenBytes = BYTE_ORDEN_INVERTIDO;
	}
#  else
	g_iOrdenBytes = BYTE_ORDEN_INVERTIDO;
#  endif
# endif
}


int BytesOrden4 ()
{
	int iRes;

	if ( g_iOrdenBytes < 0 )
	{
		CalcularOrdenBytes ();
	}
	if ( g_iNumBytesOrden == 4 )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int BytesOrden2 ()
{
	int iRes;

	if ( g_iOrdenBytes < 0 )
	{
		CalcularOrdenBytes ();
	}
	if ( g_iNumBytesOrden == 2 )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int BytesOrdenNormal ()
{
	int iRes;

	if ( g_iOrdenBytes < 0 )
	{
		CalcularOrdenBytes ();
	}
	if ( g_iOrdenBytes ==  BYTE_ORDEN_NORMAL )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int BytesOrdenInvertido ()
{
	int iRes;

	if ( g_iOrdenBytes < 0 )
	{
		CalcularOrdenBytes ();
	}
	if ( g_iOrdenBytes ==  BYTE_ORDEN_INVERTIDO )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int BytesOrdenMixto ()
{
	int iRes;

	if ( g_iOrdenBytes < 0 )
	{
		CalcularOrdenBytes ();
	}
	if ( g_iOrdenBytes ==  BYTE_ORDEN_MIXTO )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int * BytesOrden ()
{
	if ( g_iOrdenBytes < 0 )
	{
		CalcularOrdenBytes ();
	}
	return ( g_pOrdenBytes );
}

int BytesInvertir ( byte * p_byValor, int iTam, int iSoloSiOrdenInvertido )
{
   int		iByte;
    byte	byTemp;
	int		iRes;

	if ( g_iOrdenBytes < 0 )
	{
		CalcularOrdenBytes ();
	}
	if ( ES_VALIDO ( p_byValor ) && ( iTam > 1 ) && 
		 ( ( iSoloSiOrdenInvertido != 1 ) || ( g_iOrdenBytes == BYTE_ORDEN_INVERTIDO ) ) )
	{
		for ( iByte = 0; iByte < iTam/2; iByte = iByte + 1 )
		{
			byTemp = p_byValor [ iByte ];
			p_byValor [ iByte ] = p_byValor [ iTam - iByte - 1 ];
			p_byValor [ iTam - iByte - 1 ] = byTemp;
		}
		iRes = 1;
	}
	else
	{
		iRes = 0;
		ERROR_ESTABLECER ( ERR_PARAMETROS );
	}
	return ( iRes );
}

int BytesInvertirEntero ( int * p_iValor, int iSoloSiOrdenInvertido )
{
	return ( BytesInvertir ( (byte *) p_iValor, sizeof ( int ), iSoloSiOrdenInvertido ) );
}

int BytesInvertirEnteroLargo ( long * p_lValor, int iSoloSiOrdenInvertido )
{
	return ( BytesInvertir ( (byte *) p_lValor, sizeof ( long ), iSoloSiOrdenInvertido ) );
}

int BytesInvertirReal ( float * p_fValor, int iSoloSiOrdenInvertido )
{
	return ( BytesInvertir ( (byte *) p_fValor, sizeof ( float ), iSoloSiOrdenInvertido ) );
}

int BytesInvertirRealDoble ( double * p_dValor, int iSoloSiOrdenInvertido )
{
	return ( BytesInvertir ( (byte *) p_dValor, sizeof ( double ), iSoloSiOrdenInvertido ) );
}

int BytesInvertirCaracter ( unichar * p_cValor, int iSoloSiOrdenInvertido )
{
	return ( BytesInvertir ( (byte *) p_cValor, sizeof ( unichar ), iSoloSiOrdenInvertido ) );
}

int BytesPonerEnOrdenInvertido ( byte * p_byValor, int iTam ) 
{
	int iRes;

	if ( g_iOrdenBytes < 0 )
	{
		CalcularOrdenBytes ();
	}
	if ( g_iOrdenBytes == BYTE_ORDEN_NORMAL ) 
	{
		iRes = BytesInvertir ( p_byValor, iTam, 0 );
	}
	else
	{
		iRes = 1;
	}
	return ( iRes );
}

int BytesPonerEnOrdenInvertidoEntero ( int * p_iValor )
{
	int iRes;

	if ( g_iOrdenBytes < 0 )
	{
		CalcularOrdenBytes ();
	}
	if ( g_iOrdenBytes == BYTE_ORDEN_NORMAL ) 
	{
		iRes = BytesInvertirEntero ( p_iValor, 0 );
	}
	else
	{
		iRes = 1;
	}
	return ( iRes );
}

int BytesPonerEnOrdenInvertidoEnteroLargo ( long * p_lValor )
{
	int iRes;

	if ( g_iOrdenBytes < 0 )
	{
		CalcularOrdenBytes ();
	}
	if ( g_iOrdenBytes == BYTE_ORDEN_NORMAL ) 
	{
		iRes = BytesInvertirEnteroLargo ( p_lValor, 0 );
	}
	else
	{
		iRes = 1;
	}
	return ( iRes );
}

int BytesPonerEnOrdenInvertidoReal ( float * p_fValor )
{
	int iRes;

	if ( g_iOrdenBytes < 0 )
	{
		CalcularOrdenBytes ();
	}
	if ( g_iOrdenBytes == BYTE_ORDEN_NORMAL ) 
	{
		iRes = BytesInvertirReal ( p_fValor, 0 );
	}
	else
	{
		iRes = 1;
	}
	return ( iRes );
}

int BytesPonerEnOrdenInvertidoRealDoble ( double * p_dValor )
{
	int iRes;

	if ( g_iOrdenBytes < 0 )
	{
		CalcularOrdenBytes ();
	}
	if ( g_iOrdenBytes == BYTE_ORDEN_NORMAL ) 
	{
		iRes = BytesInvertirRealDoble ( p_dValor, 0 );
	}
	else
	{
		iRes = 1;
	}
	return ( iRes );
}

int BytesPonerEnOrdenInvertidoCaracter ( unichar * p_cValor )
{
	int iRes;

	if ( g_iOrdenBytes < 0 )
	{
		CalcularOrdenBytes ();
	}
	if ( g_iOrdenBytes == BYTE_ORDEN_NORMAL ) 
	{
		iRes = BytesInvertirCaracter ( p_cValor, 0 );
	}
	else
	{
		iRes = 1;
	}
	return ( iRes );
}

int BytesPonerEnOrdenNormal ( byte * p_byValor, int iTam ) 
{
	return ( BytesInvertir ( p_byValor, iTam, 1 ) );
}

int BytesPonerEnOrdenNormalEntero ( int * p_iValor )
{
	return ( BytesInvertirEntero ( p_iValor, 1 ) );
}

int BytesPonerEnOrdenNormalEnteroLargo ( long * p_lValor )
{
	return ( BytesInvertirEnteroLargo ( p_lValor, 1 ) );
}

int BytesPonerEnOrdenNormalReal ( float * p_fValor )
{
	return ( BytesInvertirReal ( p_fValor, 1 ) );
}

int BytesPonerEnOrdenNormalRealDoble ( double * p_dValor )
{
	return ( BytesInvertirRealDoble ( p_dValor, 1 ) );
}

int BytesPonerEnOrdenNormalCaracter ( unichar * p_cValor )
{
	return ( BytesInvertirCaracter ( p_cValor, 1 ) );
}

int BytesOrdenar ( byte * p_byValor, int iTam, int iOrden )
{
	int iRes;

	if ( g_iOrdenBytes < 0 )
	{
		CalcularOrdenBytes ();
	}
	if ( ES_VALIDO ( p_byValor ) && ( iTam > 1 ) && ( g_iOrdenBytes != iOrden ) )
	{
		iRes = BytesInvertir ( p_byValor, iTam, 0 );
	}
	else
	{
		iRes = 1;
	}
	return ( iRes );
}

int BytesOrdenarEntero ( int * p_iValor, int iOrden )
{
	return ( BytesOrdenar ( (byte *) p_iValor, sizeof ( int ), iOrden ) );
}

int BytesOrdenarEnteroLargo ( long * p_lValor, int iOrden )
{
	return ( BytesOrdenar ( (byte *) p_lValor, sizeof ( long ), iOrden ) );
}

int BytesOrdenarReal ( float * p_fValor, int iOrden )
{
	return ( BytesOrdenar ( (byte *) p_fValor, sizeof ( float ), iOrden ) );
}

int BytesOrdenarRealDoble ( double * p_dValor, int iOrden )
{
	return ( BytesOrdenar ( (byte *) p_dValor, sizeof ( double ), iOrden ) );
}

int BytesOrdenarCaracter ( unichar * p_cValor, int iOrden )
{
	return ( BytesOrdenar ( (byte *) p_cValor, sizeof ( unichar ), iOrden ) );
}








