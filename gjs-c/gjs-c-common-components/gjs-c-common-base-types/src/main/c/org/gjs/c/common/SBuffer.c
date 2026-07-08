
#include "SBuffer.h"


#include "TiposBasicosConfig.h"



SBuffer * SBufCrear ( unsigned long	ulTam )
{
	SBuffer * p_bufObj;
	
	if ( ulTam > 0 )
	{
		p_bufObj= (SBuffer *) MemReservar ( sizeof ( SBuffer ) );
		if ( ES_VALIDO ( p_bufObj ) )
		{
			p_bufObj->p_byContenido = (byte *) MemReservar ( ulTam );
			if ( ES_VALIDO ( p_bufObj->p_byContenido ) )
			{
				p_bufObj->ulTam = ulTam;
			}
			else
			{
				p_bufObj->ulTam = 0;
			}
		}
	}
	else
	{
		p_bufObj = NULL;
	}
	return ( p_bufObj );
}

void SBufDestruir ( SBuffer ** p_p_bufObj )
{
	SBuffer * p_bufObj;
	
	if ( ES_VALIDO ( p_p_bufObj ) )
	{
		p_bufObj = *p_p_bufObj;

		if ( ES_VALIDO ( p_bufObj ) )
		{
			MemLiberar ( (void **) &(p_bufObj->p_byContenido) );
			MemLiberar ( (void **) p_p_bufObj );
		}
	}
}

int SBufEsValido ( SBuffer * p_bufObj )
{
	int iRes;

	if ( ES_VALIDO ( p_bufObj ) )
	{
		if ( ES_VALIDO ( p_bufObj->p_byContenido ) &&
			 ( p_bufObj->ulTam > 0 ) )
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

unsigned long SBufTam ( SBuffer * p_bufObj )
{
	unsigned long ulRes;

	if ( ES_VALIDO ( p_bufObj ) )
	{
		ulRes = p_bufObj->ulTam;
	}
	else
	{
		ulRes = 0;
	}
	return ( ulRes );
}

byte * SBufDireccion ( SBuffer * p_bufObj )
{
	byte * p_byRes;

	if ( ES_VALIDO ( p_bufObj ) )
	{
		p_byRes = p_bufObj->p_byContenido;
	}
	else
	{
		p_byRes = NULL;
	}
	return ( p_byRes );
}

byte * SBufDuplicarValor ( SBuffer * p_bufObj )
{
	byte * p_byRes;

	if ( ES_VALIDO ( p_bufObj ) )
	{
		p_byRes = (byte *) MemReservar ( p_bufObj->ulTam );
		MemCopiar ( p_byRes, p_bufObj->p_byContenido, p_bufObj->ulTam );
	}
	else
	{
		p_byRes = NULL;
	}
	return ( p_byRes );
}

byte * SBufDuplicarContenido ( SBuffer * p_bufObj, unsigned long ulPos, unsigned long ulTam )
{
	byte * p_byRes;

	if ( ES_VALIDO ( p_bufObj ) && ( ulTam > 0 ) )
	{
		if ( ulPos + ulTam <= p_bufObj->ulTam ) 
		{
			p_byRes = (byte *) MemReservar ( ulTam );
			MemCopiar ( p_byRes, p_bufObj->p_byContenido + ulPos, ulTam );
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

char * SBufDuplicarCadena ( SBuffer * p_bufObj )
{
	char * p_cRes;
	
	if ( ES_VALIDO ( p_bufObj ) )
	{
		// Aseguramos que haya un nulo
		p_bufObj->p_byContenido [ p_bufObj->ulTam - 1 ] = 0x00; 
		p_cRes = (char *) SBufDuplicarContenido ( p_bufObj, 0, SBufPosicionPrimerNulo ( p_bufObj ) + 1 );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

byte SBufLeer ( SBuffer * p_bufObj, unsigned long ulPos )
{
	byte byRes;

	byRes = 0x00;
	if ( ES_VALIDO ( p_bufObj ) )
	{
		if ( ( ulPos < p_bufObj->ulTam ) && ES_VALIDO ( p_bufObj->p_byContenido ) )
		{
			byRes = p_bufObj->p_byContenido [ ulPos ];
		}
	}
	return ( byRes );
}

int SBufLeerBuffer ( SBuffer * p_bufObj, unsigned long ulPos, byte * p_byContenido, unsigned long * p_ulTam )
{
	int iRes;

	if ( ES_VALIDO ( p_bufObj ) && ES_VALIDO ( p_byContenido ) && ES_VALIDO ( p_ulTam ) )
	{
		if ( ( ulPos < p_bufObj->ulTam ) && ( *p_ulTam > 0 ) && ES_VALIDO ( p_bufObj->p_byContenido ) )
		{
			if ( ulPos + *p_ulTam >= p_bufObj->ulTam )
			{
				*p_ulTam = p_bufObj->ulTam - ulPos;
			}
			
			MemCopiar ( p_byContenido, &(p_bufObj->p_byContenido [ ulPos ]), *p_ulTam );
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

int SBufEscribir ( SBuffer * p_bufObj, unsigned long ulPos, byte byValor )
{
	int iRes;

	if ( ES_VALIDO ( p_bufObj ) )
	{
		if ( ( ulPos < p_bufObj->ulTam ) && ES_VALIDO ( p_bufObj->p_byContenido ) )
		{
			p_bufObj->p_byContenido [ ulPos ] = byValor;
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

int SBufEscribirBuffer ( SBuffer * p_bufObj, unsigned long ulPos, byte * p_byContenido, unsigned long * p_ulTam )
{
	int iRes;

	if ( ES_VALIDO ( p_bufObj ) && ES_VALIDO ( p_byContenido ) && ES_VALIDO ( p_ulTam ) )
	{
		if ( ( ulPos < p_bufObj->ulTam ) && ( *p_ulTam > 0 ) && ES_VALIDO ( p_bufObj->p_byContenido ) )
		{
			if ( ulPos + *p_ulTam >= p_bufObj->ulTam )
			{
				*p_ulTam = p_bufObj->ulTam - ulPos;
			}
			
			MemCopiar ( &(p_bufObj->p_byContenido [ ulPos ]), p_byContenido, *p_ulTam );
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

int SBufLimpiar ( SBuffer * p_bufObj )
{
	unsigned long	ulPos;
	int				iRes;

	if ( ES_VALIDO ( p_bufObj ) )
	{
		if ( ES_VALIDO ( p_bufObj->p_byContenido ) )
		{
			ulPos = 0;
			iRes = 1;
			while ( ulPos < p_bufObj->ulTam )
			{
				p_bufObj->p_byContenido [ ulPos ] = 0x00;
				ulPos = ulPos + 1;
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

unsigned long SBufPosicionPrimerNulo ( SBuffer * p_bufObj )
{
	unsigned long	ulPos;

	if ( ES_VALIDO ( p_bufObj ) )
	{
		if ( ES_VALIDO ( p_bufObj->p_byContenido ) )
		{
			ulPos = 0;
			while ( ( ulPos < p_bufObj->ulTam ) && ( p_bufObj->p_byContenido [ ulPos ] != 0x00 ) )
			{
				ulPos = ulPos + 1;
			}
		}
		else
		{
			ulPos = 0;
		}
	}
	else
	{
		ulPos = 0;
	}
	return ( ulPos );
}

int SBufInicializar ( SBuffer * p_bufObj, unsigned long	ulTam )
{
	return ( SBufRedimensionar ( p_bufObj, ulTam, 0 ) );
}

int SBufRedimensionar ( SBuffer * p_bufObj, unsigned long ulTam, int iConservarCont )
{
	int	iRes;

	if ( ES_VALIDO ( p_bufObj ) )
	{
		if ( iConservarCont == 0 )
		{
			MemLiberar ( (void **) &(p_bufObj->p_byContenido) );
			p_bufObj->p_byContenido = (byte *) MemReservar ( ulTam );
			if ( ES_VALIDO ( p_bufObj->p_byContenido ) )
			{
				p_bufObj->ulTam = ulTam;
				iRes = 1;
			}
			else
			{
				p_bufObj->ulTam = 0;
				iRes = 0;
			}
		}
		else
		{
			if ( MemRedimensionar ( (void **)&(p_bufObj->p_byContenido), ulTam ) == 1 )
			{
				p_bufObj->ulTam = ulTam;
				iRes = 1;
			}
			else
			{
				p_bufObj->ulTam = 0;
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

unsigned int SBufHash ( SBuffer * p_bufObj )
{
	unsigned int uiRes = 0;

	if ( ES_VALIDO ( p_bufObj ) )
	{
		uiRes = HashBinario ( p_bufObj->p_byContenido, p_bufObj->ulTam );
	}
	return ( uiRes );
}
