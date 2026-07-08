
#include "SFicEncabezado.h"

#include "FicherosConfig.h"


#define FIC_ENC_TAM_INFO_CABECERA			sizeof ( unsigned long )


int _SFicEncEscribirCabeceraInicial ( SFicEncabezado * p_ficObj, unsigned long ulNumMagico );
int _SFicEncProcesarCabecera ( SFicEncabezado * p_ficObj );
unsigned long _SFicEncPosInicialDatos ( SFicEncabezado * p_ficObj );




SFicEncabezado * SFicEncCrear ( const char * p_cRuta, unsigned long ulTamCabecera )
{
	SFicEncabezado * p_ficObj;
	
	p_ficObj= (SFicEncabezado *) MemReservar ( sizeof ( SFicEncabezado ) );
	if ( ES_VALIDO ( p_ficObj ) )
	{
		p_ficObj->ulTamCabecera = ulTamCabecera;
		p_ficObj->iNumMagico = 1;
		p_ficObj->p_ficObj = SFicAlCrear ( p_cRuta );
	}
	else
	{
		p_ficObj = NULL;
	}
	return ( p_ficObj );
}

SFicEncabezado * SFicEncAsignar ( const char * p_cRuta )
{
	SFicEncabezado *	p_ficObj;
	unsigned long		ulPos;
	unsigned long		ulTam;
	
	p_ficObj= (SFicEncabezado *) MemReservar ( sizeof ( SFicEncabezado ) );
	if ( ES_VALIDO ( p_ficObj ) )
	{
		p_ficObj->p_ficObj = SFicAlCrear ( p_cRuta );
		p_ficObj->iNumMagico = 1;

		if ( SFicAlAbrirExt ( p_ficObj->p_ficObj, 0 ) == 1 )
		{
			if ( p_ficObj->iNumMagico == 0 )
			{
				ulPos = 0;
			}
			else
			{
				ulPos = sizeof ( unsigned long );
			}
			ulTam = sizeof ( unsigned long );
			SFicAlCerrar ( p_ficObj->p_ficObj );
			if ( SFicAlLeerBufferEn ( p_ficObj->p_ficObj, ulPos, (byte *) &(p_ficObj->ulTamCabecera), &ulTam ) == 0 )
			{
				SFicEncDestruir ( &p_ficObj );
			}	
		}
		else
		{
			p_ficObj = NULL;
		}
	}
	return ( p_ficObj );
}

SFicEncabezado * SFicEncCrearExt ( const char * p_cDir, const char * p_cFic, unsigned long ulTamCabecera, int iNumMagico )
{
	SFicEncabezado * p_ficObj;
	
	p_ficObj= (SFicEncabezado *) MemReservar ( sizeof ( SFicEncabezado ) );
	if ( ES_VALIDO ( p_ficObj ) )
	{
		p_ficObj->ulTamCabecera = ulTamCabecera;
		p_ficObj->iNumMagico = iNumMagico;
		p_ficObj->p_ficObj = SFicAlCrearExt ( p_cDir, p_cFic );
	}
	else
	{
		p_ficObj = NULL;
	}
	return ( p_ficObj );
}

SFicEncabezado * SFicEncAsignarExt ( const char * p_cDir, const char * p_cFic, int iNumMagico )
{
	SFicEncabezado *	p_ficObj;
	unsigned long		ulPos;
	unsigned long		ulTam;
	
	p_ficObj= (SFicEncabezado *) MemReservar ( sizeof ( SFicEncabezado ) );
	if ( ES_VALIDO ( p_ficObj ) )
	{
		p_ficObj->p_ficObj = SFicAlCrearExt ( p_cDir, p_cFic );
		p_ficObj->iNumMagico = iNumMagico;

		if ( SFicAlAbrirExt ( p_ficObj->p_ficObj, 0 ) == 1 )
		{
			if ( p_ficObj->iNumMagico == 0 )
			{
				ulPos = 0;
			}
			else
			{
				ulPos = sizeof ( unsigned long );
			}
			ulTam = sizeof ( unsigned long );
			if ( SFicAlLeerBufferEn ( p_ficObj->p_ficObj, ulPos, (byte *) &(p_ficObj->ulTamCabecera), &ulTam ) == 0 )
			{
				SFicEncDestruir ( &p_ficObj );
			}	
		}
		else
		{
			p_ficObj = NULL;
		}
	}
	return ( p_ficObj );
}

SFicEncabezado * SFicEncCrearRuta ( SRuta * p_rutRuta, unsigned long ulTamCabecera )
{
	SFicEncabezado *	p_ficObj;
	char *				p_cRuta;
	
	if ( SRutEsValida ( p_rutRuta ) == 1 )
	{
		if ( SRutEsFichero ( p_rutRuta ) == 1 )
		{
			p_cRuta = SRutRutaAbsolutaLit ( p_rutRuta );
			if ( SRutExiste ( p_rutRuta ) == 1 )
			{
				p_ficObj = SFicEncAsignar ( p_cRuta );
			}
			else
			{
				p_ficObj = SFicEncCrear ( p_cRuta, ulTamCabecera );
			}
			MemLiberar ( (void **) &p_cRuta );
		}
		else
		{
			p_ficObj = NULL;
		}
	}
	else
	{
		p_ficObj = NULL;
	}
	return ( p_ficObj );
}

void SFicEncDestruir ( SFicEncabezado ** p_p_ficObj )
{
	SFicEncabezado * p_ficObj;
	
	if ( ES_VALIDO ( p_p_ficObj ) )
	{
		p_ficObj = *p_p_ficObj;

		if ( ES_VALIDO ( p_ficObj ) )
		{
			SFicAlDestruir ( &(p_ficObj->p_ficObj) );
			MemLiberar ( (void **)p_p_ficObj );
		}
	}
}

void SFicEncEliminar ( SFicEncabezado ** p_p_ficObj )
{
	SFicEncabezado * p_ficObj;
	
	if ( ES_VALIDO ( p_p_ficObj ) )
	{
		p_ficObj = *p_p_ficObj;

		if ( ES_VALIDO ( p_ficObj ) )
		{
			SFicAlEliminar ( &(p_ficObj->p_ficObj) );
			SFicEncDestruir ( p_p_ficObj );
		}
	}
}

int SFicEncEsValido ( SFicEncabezado * p_ficObj )
{
	int iRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		iRes = SFicAlEsValido ( p_ficObj->p_ficObj );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

const char * SFicEncRuta ( SFicEncabezado * p_ficObj )
{
	const char * p_cRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		p_cRes = SFicAlRuta ( p_ficObj->p_ficObj );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

char * SFicEncDirectorio ( SFicEncabezado * p_ficObj )
{
	char * p_cRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		p_cRes = SFicAlDirectorio ( p_ficObj->p_ficObj );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

char * SFicEncFichero ( SFicEncabezado * p_ficObj ) 
{
	char * p_cRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		p_cRes = SFicAlFichero ( p_ficObj->p_ficObj );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

int SFicEncEstablecerRuta ( SFicEncabezado * p_ficObj, const char * p_cRuta )
{
	int iRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		iRes = SFicAlEstablecerRuta ( p_ficObj->p_ficObj, p_cRuta );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SFicEncEstablecerRutaExt ( SFicEncabezado * p_ficObj, const char * p_cDir, const char * p_cFic )
{
	int iRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		iRes = SFicAlEstablecerRutaExt ( p_ficObj->p_ficObj, p_cDir, p_cFic );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SFicEncTieneNumeroMagico ( SFicEncabezado * p_ficObj )
{
	int iRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		iRes = p_ficObj->iNumMagico;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

unsigned long SFicEncNumeroMagico ( SFicEncabezado * p_ficObj )
{
	unsigned long ulRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		if ( ( p_ficObj->iNumMagico == 1 ) && ( SFicAlEstaAbierto ( p_ficObj->p_ficObj ) == 1 ) )
		{
			ulRes = SFicAlNumeroMagico ( p_ficObj->p_ficObj );
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
	return ( ulRes );
}

int SFicEncEstablecerNumeroMagico ( SFicEncabezado * p_ficObj, unsigned long ulNumero )
{
	int iRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		if ( ( p_ficObj->iNumMagico == 1 ) && ( SFicAlEstaAbierto ( p_ficObj->p_ficObj ) == 1 ) )
		{
			if ( SFicAlEstablecerNumeroMagico (  p_ficObj->p_ficObj, ulNumero ) == 1 )
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
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

unsigned long SFicEncTamCabecera ( SFicEncabezado * p_ficObj )
{
	unsigned long ulRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		ulRes = p_ficObj->ulTamCabecera;
	}
	else
	{
		ulRes = 0;
	}
	return ( ulRes );
}

int SFicEncEstablecerTamCabecera ( SFicEncabezado * p_ficObj, unsigned long ulTam )
{
	int iRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		if ( SFicAlEstaAbierto ( p_ficObj->p_ficObj ) == 0 )
		{
			p_ficObj->ulTamCabecera = ulTam;
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

int SFicEncAbrir ( SFicEncabezado * p_ficObj )
{
	return ( SFicEncAbrirExt ( p_ficObj, 0 ) );
}

int SFicEncAbrirExt ( SFicEncabezado * p_ficObj, int iVaciar )
{
	unsigned long	ulNumMagico;
	int				iRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		if ( SisExisteFichero ( SFicAlRuta ( p_ficObj->p_ficObj ) ) == 1 )
		{
			if ( SFicAlAbrirExt ( p_ficObj->p_ficObj, iVaciar ) == 1 )
			{
				if ( p_ficObj->iNumMagico == 1 )
				{
					ulNumMagico = SFicAlNumeroMagico ( p_ficObj->p_ficObj );
				}
				else
				{
					ulNumMagico = 0;
				}
				if ( iVaciar == 1 )
				{
					iRes = _SFicEncEscribirCabeceraInicial ( p_ficObj, ulNumMagico );
				}
				else
				{
					iRes = _SFicEncProcesarCabecera ( p_ficObj );
				}
			}
			else
			{
				iRes = 0;
			}
		}
		else
		{
			if ( SFicAlAbrirExt ( p_ficObj->p_ficObj, 1 ) == 1 )
			{
				iRes = _SFicEncEscribirCabeceraInicial ( p_ficObj, 0 );
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

int SFicEncCerrar ( SFicEncabezado * p_ficObj )
{
	int iRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		iRes = SFicAlCerrar ( p_ficObj->p_ficObj );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SFicEncEstaAbierto ( SFicEncabezado * p_ficObj )
{
	int iRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		iRes = SFicAlEstaAbierto ( p_ficObj->p_ficObj );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

unsigned long SFicEncTam  ( SFicEncabezado * p_ficObj )
{
	unsigned long  ulRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		ulRes = SFicAlTam  ( p_ficObj->p_ficObj );
	}
	else
	{
		ulRes = 0;
	}
	return ( ulRes );
}

unsigned long SFicEncTamDatos  ( SFicEncabezado * p_ficObj )
{
	unsigned long  ulRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		if ( SFicAlTam  ( p_ficObj->p_ficObj ) >= _SFicEncPosInicialDatos ( p_ficObj ) )
		{
			ulRes = SFicAlTam  ( p_ficObj->p_ficObj ) - _SFicEncPosInicialDatos ( p_ficObj );
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
	return ( ulRes );
}

int SFicEncEstaVacio ( SFicEncabezado * p_ficObj )
{
	int iRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		if ( SFicEncTamDatos ( p_ficObj ) == 0 )
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

unsigned long SFicEncPos ( SFicEncabezado * p_ficObj )
{
	unsigned long  ulRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		if ( SFicAlTam  ( p_ficObj->p_ficObj ) >= _SFicEncPosInicialDatos ( p_ficObj ) )
		{
			ulRes = SFicAlTam  ( p_ficObj->p_ficObj ) - _SFicEncPosInicialDatos ( p_ficObj );
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
	return ( ulRes );
}

int SFicEncPosicionar ( SFicEncabezado * p_ficObj, unsigned long ulPos )
{
	int iRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		iRes = SFicAlPosicionar ( p_ficObj->p_ficObj, ulPos + _SFicEncPosInicialDatos ( p_ficObj ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SFicEncMoverAInicio ( SFicEncabezado * p_ficObj )
{
	int	iRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		iRes = SFicAlPosicionar ( p_ficObj->p_ficObj, _SFicEncPosInicialDatos ( p_ficObj ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SFicEncMoverAFinal ( SFicEncabezado * p_ficObj )
{
	int iRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		iRes = SFicAlMoverAFinal ( p_ficObj->p_ficObj );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SFicEncEstaEnFinal ( SFicEncabezado * p_ficObj )
{
	int iRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		iRes = SFicAlEstaEnFinal ( p_ficObj->p_ficObj );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

byte * SFicEncLeerCabecera ( SFicEncabezado * p_ficObj )
{
	byte *			p_byContenido;
	unsigned long	ulTam;
	unsigned long	ulPos;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		ulTam = p_ficObj->ulTamCabecera;
		if ( ulTam > 0 )
		{
			p_byContenido = (byte *) MemReservar ( ulTam );
			if ( ES_VALIDO ( p_byContenido ) )
			{
				if ( p_ficObj->iNumMagico == 0 )
				{
					ulPos = FIC_ENC_TAM_INFO_CABECERA;
				}
				else
				{
					ulPos = FIC_ENC_TAM_INFO_CABECERA + sizeof ( unsigned long );
				}

				if ( SFicAlLeerBufferEn ( p_ficObj->p_ficObj, ulPos, p_byContenido, &ulTam ) == 1 )
				{
					if ( ulTam != p_ficObj->ulTamCabecera )
					{
						MemLiberar ( (void **) &p_byContenido );
					}
				}
				else
				{
					MemLiberar ( (void **) &p_byContenido );
				}
			}
		}
		else
		{
			p_byContenido = NULL;
		}
	}
	else
	{
		p_byContenido = NULL;
	}
	return ( p_byContenido );
}

byte * SFicEncCrearBufferCabecera( SFicEncabezado * p_ficObj )
{
	byte *			p_byContenido;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		if ( p_ficObj->ulTamCabecera > 0 )
		{
			p_byContenido = (byte *) MemReservar ( p_ficObj->ulTamCabecera );
		}
		else
		{
			p_byContenido = NULL;
		}
	}
	else
	{
		p_byContenido = NULL;
	}
	return ( p_byContenido );
}

int SFicEncEscribirCabecera ( SFicEncabezado * p_ficObj, byte * p_byCabecera )
{
	int				iRes;
	unsigned long	ulTam;
	unsigned long	ulPos;

	if ( ES_VALIDO ( p_ficObj ) && ES_VALIDO ( p_byCabecera ) )
	{
		ulTam = p_ficObj->ulTamCabecera;
		if ( ulTam > 0 )
		{
			if ( p_ficObj->iNumMagico == 0 )
			{
				ulPos = FIC_ENC_TAM_INFO_CABECERA;
			}
			else
			{
				ulPos = FIC_ENC_TAM_INFO_CABECERA + sizeof ( unsigned long );
			}

			if ( SFicAlEscribirBufferEn ( p_ficObj->p_ficObj, ulPos, p_byCabecera, &ulTam ) == 1 )
			{
				if ( ulTam == p_ficObj->ulTamCabecera )
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

byte SFicEncLeer ( SFicEncabezado * p_ficObj )
{
	byte			byRes;
	unsigned long	ulPos;
	unsigned long	ulPosMin;

	byRes = 0x00;
	if ( ES_VALIDO ( p_ficObj ) )
	{
		if ( SFicAlEstaAbierto ( p_ficObj->p_ficObj ) == 1 )
		{
			ulPos = SFicAlPos ( p_ficObj->p_ficObj );
			ulPosMin = _SFicEncPosInicialDatos ( p_ficObj );
			if ( ulPos < ulPosMin )
			{
				byRes = SFicAlLeerEn ( p_ficObj->p_ficObj, ulPosMin );
			}
			else
			{
				byRes = SFicAlLeer ( p_ficObj->p_ficObj );
			}
		}
	}
	return ( byRes );
}

int SFicEncLeerBuffer ( SFicEncabezado * p_ficObj, byte * p_byContenido, unsigned long * p_ulTam )
{
	int				iRes;
	unsigned long	ulPos;
	unsigned long	ulPosMin;

	if ( ES_VALIDO ( p_ficObj ) && ES_VALIDO ( p_byContenido ) && ES_VALIDO ( p_ulTam ) )
	{
		if ( SFicAlEstaAbierto ( p_ficObj->p_ficObj ) == 1 )
		{
			ulPos = SFicAlPos ( p_ficObj->p_ficObj );
			ulPosMin = _SFicEncPosInicialDatos ( p_ficObj );

			if ( ulPos < ulPosMin )
			{
				iRes = SFicAlLeerBufferEn ( p_ficObj->p_ficObj, ulPosMin, p_byContenido, p_ulTam );
			}
			else
			{
				iRes = SFicAlLeerBuffer ( p_ficObj->p_ficObj, p_byContenido, p_ulTam );
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

int SFicEncEscribir ( SFicEncabezado * p_ficObj, byte byValor )
{
	int				iRes;
	unsigned long	ulPos;
	unsigned long	ulPosMin;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		if ( SFicAlEstaAbierto ( p_ficObj->p_ficObj ) == 1 )
		{
			ulPos = SFicAlPos ( p_ficObj->p_ficObj );
			ulPosMin = _SFicEncPosInicialDatos ( p_ficObj );
			if ( ulPos < ulPosMin )
			{
				iRes = SFicAlEscribirEn ( p_ficObj->p_ficObj, ulPosMin, byValor );
			}
			else
			{
				iRes = SFicAlEscribir ( p_ficObj->p_ficObj, byValor );
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

int SFicEncEscribirBuffer ( SFicEncabezado * p_ficObj, byte * p_byContenido, unsigned long * p_ulTam )
{
	int				iRes;
	unsigned long	ulPos;
	unsigned long	ulPosMin;

	if ( ES_VALIDO ( p_ficObj ) && ES_VALIDO ( p_byContenido ) && ES_VALIDO ( p_ulTam ) )
	{
		if ( SFicAlEstaAbierto ( p_ficObj->p_ficObj ) == 1 )
		{
			ulPos = SFicAlPos ( p_ficObj->p_ficObj );
			ulPosMin = _SFicEncPosInicialDatos ( p_ficObj );
			if ( ulPos < ulPosMin )
			{
				iRes = SFicAlEscribirBufferEn ( p_ficObj->p_ficObj, ulPosMin, p_byContenido, p_ulTam );
			}
			else
			{
				iRes = SFicAlEscribirBuffer ( p_ficObj->p_ficObj, p_byContenido, p_ulTam );
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

byte SFicEncLeerEn ( SFicEncabezado * p_ficObj, unsigned long ulPos )
{
	byte byRes;

	byRes = 0x00;
	if ( ES_VALIDO ( p_ficObj ) )
	{
		byRes = SFicAlLeerEn ( p_ficObj->p_ficObj, ulPos + _SFicEncPosInicialDatos ( p_ficObj ) );
	}
	return ( byRes );
}

int SFicEncLeerBufferEn ( SFicEncabezado * p_ficObj, unsigned long ulPos, byte * p_byContenido, unsigned long * p_ulTam )
{
	int iRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		iRes = SFicAlLeerBufferEn ( p_ficObj->p_ficObj, ulPos + _SFicEncPosInicialDatos ( p_ficObj ), p_byContenido, p_ulTam );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SFicEncEscribirEn ( SFicEncabezado * p_ficObj, unsigned long ulPos, byte byValor )
{
	int iRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		iRes = SFicAlEscribirEn ( p_ficObj->p_ficObj, ulPos + _SFicEncPosInicialDatos ( p_ficObj ), byValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SFicEncEscribirBufferEn ( SFicEncabezado * p_ficObj, unsigned long ulPos, byte * p_byContenido, unsigned long * p_ulTam )
{
	int iRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		iRes = SFicAlEscribirBufferEn ( p_ficObj->p_ficObj, ulPos + _SFicEncPosInicialDatos ( p_ficObj ), p_byContenido, p_ulTam );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int _SFicEncEscribirCabeceraInicial ( SFicEncabezado * p_ficObj, unsigned long ulNumMagico )
{
	int				iRes;
	byte *			p_byCabecera;
	unsigned long	ulTam;
	unsigned long	ulPos;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		if ( SFicAlEstaAbierto ( p_ficObj->p_ficObj ) == 1 ) 
		{
			iRes = 1;
			if ( p_ficObj->iNumMagico == 1 )
			{
				ulPos = sizeof ( unsigned long );
				if ( SFicAlEstablecerNumeroMagico ( p_ficObj->p_ficObj, ulNumMagico ) == 0 )
				{
					iRes = 0;
				}
			}
			else
			{
				ulPos = 0;
			}

			if ( iRes == 1 )
			{
				ulTam = FIC_ENC_TAM_INFO_CABECERA;
				if ( SFicAlEscribirBufferEn ( p_ficObj->p_ficObj, ulPos, (byte *) &(p_ficObj->ulTamCabecera), &ulTam ) == 1 )
				{
					ulPos = ulPos + FIC_ENC_TAM_INFO_CABECERA;
				}
				else
				{
					iRes = 0;
				}
			}

			if ( ( iRes == 1 ) && ( p_ficObj->ulTamCabecera > 0 ) )
			{
				p_byCabecera = (byte *) MemReservar ( p_ficObj->ulTamCabecera );
				if ( ES_VALIDO ( p_byCabecera ) )
				{
					ulTam = p_ficObj->ulTamCabecera;
					if ( SFicAlEscribirBufferEn ( p_ficObj->p_ficObj, ulPos, p_byCabecera, &ulTam ) == 1 )
					{
						if ( ulTam != p_ficObj->ulTamCabecera )
						{
							iRes = 0;
						}
					}
					else
					{
						iRes = 0;
					}
					MemLiberar ( (void **) &p_byCabecera );
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
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int _SFicEncProcesarCabecera ( SFicEncabezado * p_ficObj )
{
	int				iRes;
	unsigned long	ulTam;
	unsigned long	ulPos;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		if ( SFicAlEstaAbierto ( p_ficObj->p_ficObj ) == 1 ) 
		{
			if ( SFicEncTieneNumeroMagico ( p_ficObj ) == 1 ) 
			{
				ulPos = sizeof ( unsigned long );
			}
			else
			{
				ulPos = 0;
			}

			ulTam = FIC_ENC_TAM_INFO_CABECERA;
			if ( SFicAlLeerBufferEn ( p_ficObj->p_ficObj, ulPos, (byte *) &(p_ficObj->ulTamCabecera), &ulTam ) == 1 )
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
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

unsigned long _SFicEncPosInicialDatos ( SFicEncabezado * p_ficObj )
{
	unsigned long  ulRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		ulRes = p_ficObj->ulTamCabecera + FIC_ENC_TAM_INFO_CABECERA;
		if ( p_ficObj->iNumMagico == 1 ) 
		{
			ulRes = ulRes + sizeof ( unsigned long );
		}
	}
	else
	{
		ulRes = 0;
	}
	return ( ulRes );
}
