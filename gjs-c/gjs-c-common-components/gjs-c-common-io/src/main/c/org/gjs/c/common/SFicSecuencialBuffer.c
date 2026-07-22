
#include "SFicSecuencialBuffer.h"

#include "FicherosConfig.h"




int _SFicSecBufCargarBuffer ( SFicSecuencialBuffer * p_ficObj );
int _SFicSecBufGuardarBuffer ( SFicSecuencialBuffer * p_ficObj );



SFicSecuencialBuffer * SFicSecBufCrear ( const char * p_cRuta, unsigned long ulTamBuf )
{
	SFicSecuencialBuffer * p_ficObj;
	
	p_ficObj= (SFicSecuencialBuffer *) MemReservar ( sizeof ( SFicSecuencialBuffer ) );
	if ( ES_VALIDO ( p_ficObj ) )
	{
		p_ficObj->p_bufObj = SBufCrear ( ulTamBuf );
		p_ficObj->p_ficObj = SFicSecCrear ( p_cRuta );
		p_ficObj->ulPosBuf = 0;
		p_ficObj->ulLonBuf = 0;
	}
	else
	{
		p_ficObj = NULL;
	}
	return ( p_ficObj );
}

SFicSecuencialBuffer * SFicSecBufCrearExt ( const char * p_cDir, const char * p_cFic, unsigned long ulTamBuf )
{
	SFicSecuencialBuffer * p_ficObj;
	
	p_ficObj= (SFicSecuencialBuffer *) MemReservar ( sizeof ( SFicSecuencialBuffer ) );
	if ( ES_VALIDO ( p_ficObj ) )
	{
		p_ficObj->p_bufObj = SBufCrear ( ulTamBuf );
		p_ficObj->p_ficObj = SFicSecCrearExt ( p_cDir, p_cFic );
		p_ficObj->ulPosBuf = 0;
		p_ficObj->ulLonBuf = 0;
	}
	else
	{
		p_ficObj = NULL;
	}
	return ( p_ficObj );
}

SFicSecuencialBuffer * SFicSecBufCrearRuta ( SRuta * p_rutRuta, unsigned long ulTamBuf )
{
	SFicSecuencialBuffer *	p_ficObj;
	char *					p_cRuta;
	
	if ( SRutEsValida ( p_rutRuta ) == 1 )
	{
		if ( SRutEsFichero ( p_rutRuta ) == 1 )
		{
			p_cRuta = SRutRutaAbsolutaLit ( p_rutRuta );
			p_ficObj = SFicSecBufCrear ( p_cRuta, ulTamBuf );
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

void SFicSecBufDestruir ( SFicSecuencialBuffer ** p_p_ficObj )
{
	SFicSecuencialBuffer * p_ficObj;
	
	if ( ES_VALIDO ( p_p_ficObj ) )
	{
		p_ficObj = *p_p_ficObj;

		if ( ES_VALIDO ( p_ficObj ) )
		{
			SFicSecDestruir ( &(p_ficObj->p_ficObj) );
			SBufDestruir ( &(p_ficObj->p_bufObj) );
			MemLiberar ( (void **)p_p_ficObj );
		}
	}
}

void SFicSecBufEliminar ( SFicSecuencialBuffer ** p_p_ficObj )
{
	SFicSecuencialBuffer * p_ficObj;
	
	if ( ES_VALIDO ( p_p_ficObj ) )
	{
		p_ficObj = *p_p_ficObj;

		if ( ES_VALIDO ( p_ficObj ) )
		{
			SFicSecEliminar ( &(p_ficObj->p_ficObj) );
			SFicSecBufDestruir ( p_p_ficObj );
		}
	}
}

int SFicSecBufEsValido ( SFicSecuencialBuffer * p_ficObj )
{
	int iRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		if ( ES_VALIDO ( p_ficObj->p_ficObj ) && ES_VALIDO ( p_ficObj->p_bufObj ) )
		{
			if ( ( SFicSecEsValido ( p_ficObj->p_ficObj ) == 1 ) &&
				 ( SBufEsValido ( p_ficObj->p_bufObj ) == 1 ) )
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

const char * SFicSecBufRuta ( SFicSecuencialBuffer * p_ficObj )
{
	const char * p_cRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		p_cRes = SFicSecRuta ( p_ficObj->p_ficObj );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

char * SFicSecBufDirectorio ( SFicSecuencialBuffer * p_ficObj )
{
	char * p_cRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		p_cRes = SFicSecDirectorio ( p_ficObj->p_ficObj );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

char * SFicSecBufFichero ( SFicSecuencialBuffer * p_ficObj )
{
	char * p_cRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		p_cRes = SFicSecFichero ( p_ficObj->p_ficObj );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

int SFicSecBufEstablecerRuta ( SFicSecuencialBuffer * p_ficObj, const char * p_cRuta )
{
	int iRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		iRes = SFicSecEstablecerRuta ( p_ficObj->p_ficObj, p_cRuta );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SFicSecBufEstablecerRutaExt ( SFicSecuencialBuffer * p_ficObj, const char * p_cDir, const char * p_cFic )
{
	int iRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		iRes = SFicSecEstablecerRutaExt ( p_ficObj->p_ficObj, p_cDir, p_cFic );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

unsigned long SFicSecBufTamBuffer ( SFicSecuencialBuffer * p_ficObj )
{
	unsigned long ulRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		ulRes = SBufTam ( p_ficObj->p_bufObj );
	}
	else
	{
		ulRes = 0;
	}
	return ( ulRes );
}

int SFicSecBufAbrir ( SFicSecuencialBuffer * p_ficObj, int iModo )
{
	int iRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		iRes = SFicSecAbrir ( p_ficObj->p_ficObj, iModo );
		if ( iRes == 1 )
		{
			SBufLimpiar ( p_ficObj->p_bufObj );
			p_ficObj->ulPosBuf = 0;
			if ( iModo == MOD_APR_LECTURA )
			{
				p_ficObj->ulLonBuf = 0;
			}
			else
			{
				p_ficObj->ulLonBuf = SBufTam ( p_ficObj->p_bufObj );
			}
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SFicSecBufCerrar ( SFicSecuencialBuffer * p_ficObj )
{
	int iRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		if ( SFicSecEstaAbiertoParaEscritura ( p_ficObj->p_ficObj ) == 1 ) 
		{
			if ( p_ficObj->ulPosBuf > 0 )
			{
				if ( _SFicSecBufGuardarBuffer ( p_ficObj ) == 1 )
				{
					iRes = SFicSecCerrar ( p_ficObj->p_ficObj );
				}
				else
				{
					iRes = 0;
				}
			}
			else
			{
				iRes = SFicSecCerrar ( p_ficObj->p_ficObj );
			}
		}
		else
		{
			iRes = SFicSecCerrar ( p_ficObj->p_ficObj );
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SFicSecBufEstaAbierto ( SFicSecuencialBuffer * p_ficObj )
{
	int iRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		iRes = SFicSecEstaAbierto ( p_ficObj->p_ficObj );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SFicSecBufModoApertura ( SFicSecuencialBuffer * p_ficObj )
{
	int iRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		iRes = SFicSecModoApertura ( p_ficObj->p_ficObj );
	}
	else
	{
		iRes = MOD_APR_NINGUNO;
	}
	return ( iRes );
}

int SFicSecBufEstaAbiertoParaLectura ( SFicSecuencialBuffer * p_ficObj )
{
	int iRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		iRes = SFicSecEstaAbiertoParaLectura ( p_ficObj->p_ficObj );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SFicSecBufEstaAbiertoParaEscritura ( SFicSecuencialBuffer * p_ficObj )
{
	int iRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		iRes = SFicSecEstaAbiertoParaEscritura ( p_ficObj->p_ficObj );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SFicSecBufEstaEnFinal ( SFicSecuencialBuffer * p_ficObj )
{
	int iRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		if ( SFicSecEstaEnFinal ( p_ficObj->p_ficObj ) == 1 )
		{
			if ( p_ficObj->ulPosBuf >= p_ficObj->ulLonBuf )
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


byte SFicSecBufLeer ( SFicSecuencialBuffer * p_ficObj )
{
	byte byRes;

	byRes = 0x00;
	if ( ES_VALIDO ( p_ficObj ) )
	{
		if ( SFicSecEstaAbiertoParaLectura ( p_ficObj->p_ficObj ) == 1 ) 
		{
			if ( ( p_ficObj->ulLonBuf == 0 ) || ( p_ficObj->ulPosBuf == p_ficObj->ulLonBuf ) )
			{
				if ( _SFicSecBufCargarBuffer ( p_ficObj ) == 1 )
				{
					byRes = SBufLeer ( p_ficObj->p_bufObj, p_ficObj->ulPosBuf );
					p_ficObj->ulPosBuf = p_ficObj->ulPosBuf + 1;
				}
			}
			else
			{
				byRes = SBufLeer ( p_ficObj->p_bufObj, p_ficObj->ulPosBuf );
				p_ficObj->ulPosBuf = p_ficObj->ulPosBuf + 1;
			}
		}
	}
	return ( byRes );
}

int SFicSecBufLeerBuffer ( SFicSecuencialBuffer * p_ficObj, byte * p_byContenido, unsigned long * p_ulTam )
{
	int				iRes;
	unsigned long	ulRestante;
	unsigned long	ulTam;
	int				iFinal;

	if ( ES_VALIDO ( p_ficObj ) && ES_VALIDO ( p_byContenido ) && ES_VALIDO ( p_ulTam ) )
	{
		if ( ( *p_ulTam > 0 ) && ( SFicSecEstaAbiertoParaLectura ( p_ficObj->p_ficObj ) == 1 ) )
		{
			ulRestante = *p_ulTam;
			iFinal = 0;
			iRes = 1;
			while ( ( ulRestante > 0 ) && ( iFinal == 0 ) && ( iRes == 1 ) )
			{
				if ( ulRestante > p_ficObj->ulLonBuf - p_ficObj->ulPosBuf )
				{
					ulTam = p_ficObj->ulLonBuf - p_ficObj->ulPosBuf;
				}
				else
				{
					ulTam = ulRestante;
				}
				if ( SBufLeerBuffer ( p_ficObj->p_bufObj, p_ficObj->ulPosBuf, p_byContenido, &ulTam ) == 1 )
				{
					ulRestante = ulRestante - ulTam;
					if ( ulRestante == 0 )
					{
						p_ficObj->ulPosBuf = p_ficObj->ulPosBuf + ulTam;
						iFinal = 1;
					}
					else
					{
						if ( SFicSecEstaEnFinal ( p_ficObj->p_ficObj ) == 0 )
						{
							if ( _SFicSecBufCargarBuffer ( p_ficObj ) == 0 )
							{
								iRes = 0;
							}
						}
						else
						{
							iFinal = 1;
							*p_ulTam = *p_ulTam - ulRestante;
						}
					}
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

int SFicSecBufEscribir ( SFicSecuencialBuffer * p_ficObj, byte byValor )
{
	int iRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		if ( SFicSecEstaAbiertoParaEscritura ( p_ficObj->p_ficObj ) == 1 ) 
		{
			if ( SBufEscribir ( p_ficObj->p_bufObj, p_ficObj->ulPosBuf, byValor ) == 1 )
			{
				p_ficObj->ulPosBuf = p_ficObj->ulPosBuf + 1;
				if ( p_ficObj->ulPosBuf == SBufTam ( p_ficObj->p_bufObj ) )
				{
					if ( _SFicSecBufGuardarBuffer ( p_ficObj ) == 1 )
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

int SFicSecBufEscribirBuffer ( SFicSecuencialBuffer * p_ficObj, byte * p_byContenido, unsigned long * p_ulTam )
{
	int				iRes;
	unsigned long	ulRestante;
	unsigned long	ulTam;
	unsigned long	ulTamBuf;

	if ( ES_VALIDO ( p_ficObj ) && ES_VALIDO ( p_byContenido ) && ES_VALIDO ( p_ulTam ) )
	{
		ulTamBuf = SBufTam ( p_ficObj->p_bufObj );
		if ( ( *p_ulTam > 0 ) && ( SFicSecEstaAbiertoParaEscritura ( p_ficObj->p_ficObj ) == 1 ) && ( ulTamBuf > 0 ) )
		{
			ulTam = ( *p_ulTam / ulTamBuf ) * ulTamBuf;
			ulRestante = *p_ulTam - ulTam;

			if ( SFicSecEscribirBuffer ( p_ficObj->p_ficObj, p_byContenido, &ulTam ) == 1 )
			{
				if ( ulRestante > 0 )
				{
					if ( SBufEscribirBuffer ( p_ficObj->p_bufObj, 0, &(p_byContenido [ ulTam ]), &ulRestante ) == 1 )
					{
						p_ficObj->ulPosBuf = ulRestante;
						iRes = 1;
					}
					else
					{
						iRes = 0;
					}
				}
				else
				{
					p_ficObj->ulPosBuf = 0;
					iRes = 1;
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

int _SFicSecBufCargarBuffer ( SFicSecuencialBuffer * p_ficObj )
{
	int				iRes;
	unsigned long	ulTam;
	byte *			p_byBuffer;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		ulTam = SBufTam ( p_ficObj->p_bufObj );
		p_byBuffer = SBufDireccion ( p_ficObj->p_bufObj );

		if ( ES_VALIDO ( p_byBuffer ) && ( ulTam > 0 ) )
		{
			SBufLimpiar ( p_ficObj->p_bufObj );
			if ( SFicSecLeerBuffer ( p_ficObj->p_ficObj, p_byBuffer, &ulTam ) == 1 )
			{
				p_ficObj->ulLonBuf = ulTam;
				p_ficObj->ulPosBuf = 0;
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

int _SFicSecBufGuardarBuffer ( SFicSecuencialBuffer * p_ficObj )
{
	int				iRes;
	unsigned long	ulTam;
	byte *			p_byBuffer;

	if ( ES_VALIDO ( p_ficObj ) ) 
	{
		if ( ( p_ficObj->ulPosBuf > 0 ) && ( p_ficObj->ulPosBuf <= p_ficObj->ulLonBuf ) )
		{
			ulTam = p_ficObj->ulPosBuf;
			p_byBuffer = SBufDireccion ( p_ficObj->p_bufObj );

			if ( ES_VALIDO ( p_byBuffer ) && ( ulTam > 0 ) )
			{
				if ( SFicSecEscribirBuffer ( p_ficObj->p_ficObj, p_byBuffer, &ulTam ) == 1 )
				{
					SBufLimpiar ( p_ficObj->p_bufObj );
					p_ficObj->ulPosBuf = 0;
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
