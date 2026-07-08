

#include "SDatos.h"


#include "TiposBasicosConfig.h"




SDatos * SDatCrear ( int iTam )
{
	SDatos * p_datObj;

	if ( iTam > 0 )
	{
		p_datObj = (SDatos *) MemReservar ( sizeof ( SDatos ) );
		if ( ES_VALIDO ( p_datObj ) )
		{
			p_datObj->p_bufDatos = SBufCrear ( iTam );
			if ( ES_NULO ( p_datObj->p_bufDatos ) )
			{
				MemLiberar ( (void **) &p_datObj );
			}
		}
	}
	else
	{
		p_datObj = NULL;
	}
	return ( p_datObj );
}

void SDatDestruir ( SDatos ** p_p_datObj )
{
    SDatos *  p_datObj;

    if ( ES_VALIDO ( p_p_datObj ) )
    {
        p_datObj = *p_p_datObj;
		if ( ES_VALIDO ( p_datObj ) )
		{
			SBufDestruir ( &(p_datObj->p_bufDatos) );
			MemLiberar ( (void **) p_p_datObj );
		}
    }
}

int SDatEsValido ( SDatos * p_datObj )
{
	int		iRes;

	if ( ES_VALIDO ( p_datObj ) )
	{
		iRes = SBufEsValido ( p_datObj->p_bufDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SDatEstablecerByte ( SDatos * p_datObj, int iPos, byte byVal )
{
	int		iRes;

	if ( ES_VALIDO ( p_datObj ) )
	{
		iRes = SBufEscribir ( p_datObj->p_bufDatos, iPos, byVal );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

byte SDatByte ( SDatos * p_datObj, int iPos )
{
	byte	byVal;

	if ( ES_VALIDO ( p_datObj ) )
	{
		byVal = SBufLeer ( p_datObj->p_bufDatos, iPos );
	}
	else
	{
		byVal = (byte) 0;
	}
	return ( byVal );
}

int SDatAsignarContenido ( SDatos * p_datObj, byte * p_byDatos, int iTam )
{
	int iRes;

	if ( ES_VALIDO ( p_datObj ) )
	{
		iRes = SDatAsignarContenidoEnPos ( p_datObj, 0, p_byDatos, iTam );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SDatAsignarContenidoEnPos ( SDatos * p_datObj, int iPos, byte * p_byDatos, int iTam )
{
	int				iRes;
	unsigned long	ulTam;

	if ( ES_VALIDO ( p_datObj ) )
	{
		ulTam = iTam;
		iRes = SBufEscribirBuffer ( p_datObj->p_bufDatos, iPos, p_byDatos, &ulTam );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

byte * SDatContenido ( SDatos * p_datObj )
{
	byte * p_byRes;

	if ( ES_VALIDO ( p_datObj ) )
	{
		p_byRes = SBufDireccion ( p_datObj->p_bufDatos );
	}
	else
	{
		p_byRes = NULL;
	}
	return ( p_byRes );
}

byte * SDatContenidoEnPos ( SDatos * p_datObj, int iPos, int iTam )
{
	byte *	p_byRes;

	if ( ES_VALIDO ( p_datObj ) )
	{
		if ( iPos + iTam <= SBufTam ( p_datObj->p_bufDatos ) )
		{
			p_byRes = SBufDireccion ( p_datObj->p_bufDatos );
			if ( ES_VALIDO ( p_byRes ) )
			{
				p_byRes = p_byRes + iPos;
			}
			else
			{
				p_byRes = NULL;
			}
		}
		else
		{
			p_byRes = NULL;
		}
	}
	else
	{
		p_byRes = NULL;
	}
	return ( p_byRes );
}

int SDatAsignar ( SDatos * p_datObj, SDatos * p_datValor )
{
	int iRes;

	if ( ES_VALIDO ( p_datObj ) && ES_VALIDO ( p_datValor ) )
	{
		if ( SDatRedimensionar ( p_datObj, SDatTam ( p_datValor ), 0 ) == 1 )
		{
			iRes = SDatAsignarContenido ( p_datObj, SDatContenido ( p_datValor ), SDatTam ( p_datValor ) );
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

int SDatCopiar ( SDatos * p_datObj, SDatos * p_datValor )
{
	return ( SDatCopiarEnPos ( p_datObj, 0, p_datValor ) );
}

int SDatCopiarEnPos ( SDatos * p_datObj, int iPos, SDatos * p_datValor )
{
	int	iRes;

	if ( ES_VALIDO ( p_datObj ) )
	{
		if ( ES_VALIDO ( p_datValor ) && ( iPos >= 0 ) && ( iPos < SBufTam ( p_datObj->p_bufDatos ) ) )
		{
			if ( iPos + SDatTam ( p_datValor ) <= SBufTam ( p_datObj->p_bufDatos ) )
			{
				iRes = SDatAsignarContenidoEnPos ( p_datObj, iPos, SDatContenido ( p_datValor ), SDatTam ( p_datValor ) );
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
	return ( iRes );
}

byte * SDatDuplicarContenido ( SDatos * p_datObj )
{
	byte * p_byRes;

	if ( ES_VALIDO ( p_datObj ) )
	{
		p_byRes = SBufDuplicarValor ( p_datObj->p_bufDatos );
	}
	else
	{
		p_byRes = NULL;
	}
	return ( p_byRes );
}

byte * SDatDuplicarContenidoEnPos ( SDatos * p_datObj, int iPos, int iTam )
{
	byte * p_byRes;

	if ( ES_VALIDO ( p_datObj ) )
	{
		p_byRes = SBufDuplicarContenido ( p_datObj->p_bufDatos, iPos, iTam );
	}
	else
	{
		p_byRes = NULL;
	}
	return ( p_byRes );
}

SDatos * SDatDuplicar ( SDatos * p_datObj )
{
	SDatos * p_datCopia;

	if ( ES_VALIDO ( p_datObj ) )
	{
		p_datCopia = SDatCrear ( SBufTam ( p_datObj->p_bufDatos ) );
		if ( ES_VALIDO ( p_datCopia ) )
		{
			SDatAsignarContenido ( p_datCopia, SBufDireccion ( p_datObj->p_bufDatos ), SBufTam ( p_datObj->p_bufDatos ) );
		}
	}
	else
	{
		p_datCopia = NULL;
	}
	return ( p_datCopia );
}

SDatos * SDatExtraer ( SDatos * p_datObj, int iTam )
{
	return ( SDatExtraerEnPos ( p_datObj, 0, iTam ) );
}

SDatos * SDatExtraerEnPos ( SDatos * p_datObj, int iPos, int iTam )
{
	SDatos *	p_datRes;
	byte *		p_vDatos;

	if ( ES_VALIDO ( p_datObj ) )
	{
		if ( ( iPos >= 0 ) && ( iPos + iTam <= SBufTam ( p_datObj->p_bufDatos ) ) )
		{
			p_datRes = SDatCrear ( iTam );
			if ( ES_VALIDO ( p_datRes ) )
			{
				p_vDatos = SBufDireccion ( p_datObj->p_bufDatos ) + iPos;
				if ( SDatAsignarContenido ( p_datRes, p_vDatos, iTam ) == 0 )
				{
					SDatDestruir ( &p_datRes );
				}
			}
			else
			{
				p_datRes = NULL;
			}
		}
		else
		{
			p_datRes = NULL;
		}
	}
	else
	{
		p_datRes = NULL;
	}
	return ( p_datRes );
}

char * SDatExtraerCadena ( SDatos * p_datObj, int iTam )
{
	return ( SDatExtraerCadenaEnPos ( p_datObj, 0, iTam ) );
}

char * SDatExtraerCadenaEnPos ( SDatos * p_datObj, int iPos, int iTam )
{
	int			iCar;
	char *	p_cRes;
	byte *		p_vDatos;

	if ( ES_VALIDO ( p_datObj ) )
	{
		if ( ( iPos >= 0 ) && ( iPos + iTam <= SBufTam ( p_datObj->p_bufDatos ) ) )
		{
			p_cRes = CadCrear ( iTam );
			if ( ES_VALIDO ( p_cRes ) )
			{
				p_vDatos = SBufDireccion ( p_datObj->p_bufDatos ) + iPos;
				for ( iCar = 0; iCar < iTam; iCar = iCar + 1 )
				{
					p_cRes [ iCar ] = (char) *(p_vDatos + iCar);
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
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

SDatos * SDatExtraerHastaNulo ( SDatos * p_datObj, int iIncluirNulo )
{
	int			iPos;
	SDatos *	p_datRes;

	if ( ES_VALIDO ( p_datObj ) )
	{
		iIncluirNulo = BoolNormalizar ( iIncluirNulo );
		iPos = SDatPosicionPrimerNulo ( p_datObj );
		if ( ( iPos > 0 ) && ( iPos < SBufTam ( p_datObj->p_bufDatos ) ) )
		{
			p_datRes = SDatExtraerEnPos ( p_datObj, 0, iPos + iIncluirNulo );
		}
		else
		{
			p_datRes = NULL;
		}
	}
	else
	{
		p_datRes = NULL;
	}
	return ( p_datRes );
}

int SDatTam ( SDatos * p_datObj )
{
	int iRes;

	if ( ES_VALIDO ( p_datObj ) )
	{
		iRes = SBufTam ( p_datObj->p_bufDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SDatPosicionPrimerNulo ( SDatos * p_datObj )
{
	int iRes;

	if ( ES_VALIDO ( p_datObj ) )
	{
		iRes = SBufPosicionPrimerNulo ( p_datObj->p_bufDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

void SDatLimpiar ( SDatos * p_datObj )
{
	if ( ES_VALIDO ( p_datObj ) )
	{
		SBufLimpiar ( p_datObj->p_bufDatos );
	}
}

void SDatLiberar ( SDatos * p_datObj )
{
	if ( ES_VALIDO ( p_datObj ) )
	{
		SBufDestruir ( &(p_datObj->p_bufDatos) );
	}
}

int  SDatInicializar ( SDatos * p_datObj,  int iTam )
{
	int iRes;

	if ( ES_VALIDO ( p_datObj ) )
	{
		iRes = SBufInicializar ( p_datObj->p_bufDatos, iTam );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SDatRedimensionar ( SDatos * p_datObj, int iTam, int iConservarCont )
{
	int iRes;

	if ( ES_VALIDO ( p_datObj ) )
	{
		iRes = SBufRedimensionar ( p_datObj->p_bufDatos, iTam, iConservarCont );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

char * SDatCadenaHex ( SDatos * p_datObj )
{
	int		iCar;
	byte *	p_byBuffer;
	byte	byValor;
	char *	p_cHex;
	char	p_cVal [ 2 ];

	if ( ES_VALIDO ( p_datObj ) )
	{
		if ( SBufTam ( p_datObj->p_bufDatos ) > 0 )
		{
			p_byBuffer = SBufDireccion ( p_datObj->p_bufDatos );
			if ( ES_VALIDO ( p_byBuffer ) )
			{
				p_cHex = CadCrear ( SBufTam ( p_datObj->p_bufDatos ) * 2 );
				if ( ES_VALIDO ( p_cHex ) )
				{
					for ( iCar = 0; iCar < SBufTam ( p_datObj->p_bufDatos ); iCar = iCar + 1 )
					{
						byValor = p_byBuffer [ iCar ];
						ByteAHex ( byValor, p_cVal );
						p_cHex [ iCar * 2 ] = p_cVal [ 0 ];
						p_cHex [ iCar * 2 + 1 ] = p_cVal [ 1 ];
					}
				}
				else
				{
					p_cHex = NULL;
				}
			}
			else
			{
				p_cHex = NULL;
			}
		}
		else
		{
			p_cHex = NULL;
		}
	}
	else
	{
		p_cHex = NULL;
	}
	return ( p_cHex );
}

int SDatAsignarCadenaHex ( SDatos * p_datObj, const char * p_cHex )
{
	int			iByte;
	int			iError;
	int			iTam;
	byte *		p_byBuffer;
	byte		byValor;
	int			iRes;
	char		p_cVal [ 2 ];

	if ( ES_VALIDO ( p_datObj ) && ES_VALIDO ( p_cHex ) )
	{
		iTam = CadLongitud ( p_cHex );
		if ( ( iTam > 0 ) && ( iTam % 2 == 0 ) )
		{
			p_byBuffer = (byte *)MemReservar ( iTam / 2 );
			if ( ES_VALIDO ( p_byBuffer ) )
			{
				iByte = 0;
				iError = 0;
				while ( ( iByte < iTam / 2 ) && ( iError == 0 ) )
				{
					p_cVal [ 0 ] = p_cHex [ iByte * 2 ];
					p_cVal [ 1 ] = p_cHex [ iByte * 2 + 1 ];
					if ( ( HexEsValido ( p_cVal [ 0 ] ) == 1 ) &&
						 ( HexEsValido ( p_cVal [ 1 ] ) == 1 ) )
					{
						byValor = HexAByte ( p_cVal );
						p_byBuffer [ iByte ] = byValor;
					}
					else
					{
						iError = 1;
					}
					iByte = iByte + 1;
				}
				if ( iError == 0 )
				{
					iRes = SDatAsignarContenido ( p_datObj, p_byBuffer, iTam / 2 );
				}
				else
				{
					iRes = 0;
				}
				MemLiberar ( (void **)&p_byBuffer );
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
	return ( iRes );
}

void SDatImprimir ( SDatos * p_datObj )
{
	int		iCar;
	byte *	p_byBuffer;
	byte	byValor;

	if ( ES_VALIDO ( p_datObj ) )
	{
		printf ( "\n * Contenido del buffer: \n\n" );
		if ( SBufTam ( p_datObj->p_bufDatos ) > 0 )
		{
			p_byBuffer = SBufDireccion ( p_datObj->p_bufDatos );
			if ( ES_VALIDO ( p_byBuffer ) )
			{
				for ( iCar = 0; iCar < SBufTam ( p_datObj->p_bufDatos ); iCar = iCar + 1 )
				{
					byValor = p_byBuffer [ iCar ];
					printf ( "%02X ", byValor );
					if ( iCar % 16 == 15 )
					{
						printf ( "\n" );
					}
				}
			}
			else
			{
				printf ( "  El buffer está erróneo.\n" );
			}
		}
		else
		{
			printf ( "  El buffer está vacío.\n" );
		}
	}
	else
	{
		printf ( "  El buffer es nulo.\n" );
	}
	printf ( "\n\n" );
}


unsigned int SDatHash ( SDatos * p_datObj )
{
	unsigned int uiRes = 0;

	if ( ES_VALIDO ( p_datObj ) )
	{
		uiRes = SBufHash ( p_datObj->p_bufDatos );
	}
	return ( uiRes );
}


