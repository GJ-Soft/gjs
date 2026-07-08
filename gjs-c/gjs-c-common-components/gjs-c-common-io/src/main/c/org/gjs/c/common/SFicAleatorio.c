
#include "SFicAleatorio.h"

#include "FicherosConfig.h"



SFicAleatorio * SFicAlCrear ( const char * p_cRuta )
{
	SFicAleatorio * p_ficObj;
	
	p_ficObj= (SFicAleatorio *) MemReservar ( sizeof ( SFicAleatorio ) );
	if ( ES_VALIDO ( p_ficObj ) )
	{
		p_ficObj->iAbierto = 0;
		p_ficObj->p_cRuta = NULL;
		p_ficObj->p_fObj = NULL;

		SFicAlEstablecerRuta ( p_ficObj, p_cRuta );
	}
	else
	{
		p_ficObj = NULL;
	}
	return ( p_ficObj );
}

SFicAleatorio * SFicAlCrearExt ( const char * p_cDir, const char * p_cFic )
{
	SFicAleatorio * p_ficObj;
	
	p_ficObj= (SFicAleatorio *) MemReservar ( sizeof ( SFicAleatorio ) );
	if ( ES_VALIDO ( p_ficObj ) )
	{
		p_ficObj->iAbierto = 0;
		p_ficObj->p_cRuta = NULL;
		p_ficObj->p_fObj = NULL;

		SFicAlEstablecerRutaExt ( p_ficObj, p_cDir, p_cFic );
	}
	else
	{
		p_ficObj = NULL;
	}
	return ( p_ficObj );
}

SFicAleatorio * SFicAlCrearRuta ( SRuta * p_rutRuta )
{
	SFicAleatorio *	p_ficObj;
	char *			p_cRuta;
	
	if ( SRutEsValida ( p_rutRuta ) == 1 )
	{
		if ( SRutEsFichero ( p_rutRuta ) == 1 )
		{
			p_cRuta = SRutRutaAbsolutaLit ( p_rutRuta );
			p_ficObj = SFicAlCrear ( p_cRuta );
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

void SFicAlDestruir ( SFicAleatorio ** p_p_ficObj )
{
	SFicAleatorio * p_ficObj;
	
	if ( ES_VALIDO ( p_p_ficObj ) )
	{
		p_ficObj = *p_p_ficObj;

		if ( ES_VALIDO ( p_ficObj ) )
		{
			SFicAlCerrar ( p_ficObj );
			MemLiberar ( (void **) &(p_ficObj->p_cRuta) );
			MemLiberar ( (void **) p_p_ficObj );
		}
	}
}

void SFicAlEliminar ( SFicAleatorio ** p_p_ficObj )
{
	SFicAleatorio * p_ficObj;
	
	if ( ES_VALIDO ( p_p_ficObj ) )
	{
		p_ficObj = *p_p_ficObj;

		if ( ES_VALIDO ( p_ficObj ) )
		{
			SisEliminarFichero ( p_ficObj->p_cRuta );
			SFicAlDestruir ( p_p_ficObj );
		}
	}
}

int SFicAlEsValido ( SFicAleatorio * p_ficObj )
{
	int iRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		if ( ES_VALIDO ( p_ficObj->p_cRuta ) )
		{
			if ( p_ficObj->iAbierto == 1 )
			{
				if ( ES_VALIDO ( p_ficObj->p_fObj ) &&
					 ( SisExisteFichero ( p_ficObj->p_cRuta ) == 1 ) )
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
				if ( SisEsRutaValida ( p_ficObj->p_cRuta ) == 1 )
				{
					iRes = 1;
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

const char * SFicAlRuta ( SFicAleatorio * p_ficObj )
{
	const char * p_cRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		p_cRes = (const char *)(p_ficObj->p_cRuta);
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

char * SFicAlDirectorio ( SFicAleatorio * p_ficObj )
{
	char * p_cRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		p_cRes = SisRutaDirectorio ( p_ficObj->p_cRuta );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

char * SFicAlFichero ( SFicAleatorio * p_ficObj )
{
	char * p_cRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		p_cRes = SisRutaFichero ( p_ficObj->p_cRuta );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

int SFicAlEstablecerRuta ( SFicAleatorio * p_ficObj, const char * p_cRuta )
{
	int iRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		if ( p_ficObj->iAbierto == 0 )
		{
			MemLiberar ( (void **) &(p_ficObj->p_cRuta) );
			p_ficObj->p_cRuta = CadDuplicar ( p_cRuta );
			if ( SisEsRutaValida ( p_ficObj->p_cRuta ) == 1 )
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

int SFicAlEstablecerRutaExt ( SFicAleatorio * p_ficObj, const char * p_cDir, const char * p_cFic )
{
	int iRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		if ( p_ficObj->iAbierto == 0 )
		{
			MemLiberar ( (void **) &(p_ficObj->p_cRuta) );
			p_ficObj->p_cRuta = SisComponerRuta ( p_cDir, p_cFic, 0 );
			if ( SisEsRutaValida ( p_ficObj->p_cRuta ) == 1 )
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

int SFicAlAbrir ( SFicAleatorio * p_ficObj )
{
	return ( SFicAlAbrirExt ( p_ficObj, 0 ) );
}

int SFicAlAbrirExt ( SFicAleatorio * p_ficObj, int iVaciar )
{
	int iRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		if ( p_ficObj->iAbierto == 0 )
		{
			if ( SisExisteFichero ( p_ficObj->p_cRuta ) == 1 )
			{
				if ( iVaciar == 1 )
				{
					p_ficObj->p_fObj = fopen ( p_ficObj->p_cRuta, "w+b" );
				}
				else
				{
					p_ficObj->p_fObj = fopen ( p_ficObj->p_cRuta, "r+b" );
				}
			}
			else
			{
				p_ficObj->p_fObj = fopen ( p_ficObj->p_cRuta, "w+b" );
			}

			if ( ES_VALIDO ( p_ficObj->p_fObj ) )
			{
				iRes = 1;
				p_ficObj->iAbierto = 1;
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
	return ( iRes );
}

int SFicAlCerrar ( SFicAleatorio * p_ficObj )
{
	int iRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		if ( ( p_ficObj->iAbierto == 1 ) && ES_VALIDO ( p_ficObj->p_fObj ) )
		{
			if ( fclose ( p_ficObj->p_fObj ) == 0 )
			{
				p_ficObj->p_fObj = NULL;
				p_ficObj->iAbierto = 0;
				iRes = 1;
			}
			else
			{
				iRes = 0;
			}
		}
		else
		{
			p_ficObj->iAbierto = 0;
			iRes = 1;
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SFicAlEstaAbierto ( SFicAleatorio * p_ficObj )
{
	int iRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		if ( ( p_ficObj->iAbierto == 1 ) && ES_VALIDO ( p_ficObj->p_fObj ) )
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

unsigned long SFicAlTam  ( SFicAleatorio * p_ficObj )
{
	unsigned long  	ulRes;
	int				lPos;	

	if ( ES_VALIDO ( p_ficObj ) )
	{
		if ( ( p_ficObj->iAbierto == 1 ) && ES_VALIDO ( p_ficObj->p_fObj ) )
		{
			lPos = ftell ( p_ficObj->p_fObj );
			if ( lPos >= 0 )
			{
				fseek ( p_ficObj->p_fObj, 0, SEEK_END );
				ulRes = ftell ( p_ficObj->p_fObj );
				fseek ( p_ficObj->p_fObj, lPos, SEEK_SET );
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
	}
	else
	{
		ulRes = 0;
	}
	return ( ulRes );
}

int SFicAlEstaVacio ( SFicAleatorio * p_ficObj )
{
	int iRes;

	if ( SFicAlTam ( p_ficObj ) == 0 )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

unsigned long SFicAlPos ( SFicAleatorio * p_ficObj )
{
	unsigned long  ulRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		if ( ( p_ficObj->iAbierto == 1 ) && ES_VALIDO ( p_ficObj->p_fObj ) )
		{
			ulRes = ftell ( p_ficObj->p_fObj );
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

int SFicAlPosicionar ( SFicAleatorio * p_ficObj, unsigned long ulPos )
{
	int iRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		if ( ( p_ficObj->iAbierto == 1 ) && ES_VALIDO ( p_ficObj->p_fObj ) )
		{
			fseek ( p_ficObj->p_fObj, ulPos, SEEK_SET );
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

int SFicAlMoverAInicio ( SFicAleatorio * p_ficObj )
{
	return ( SFicAlMoverAInicioExt ( p_ficObj, 0 ) );
}

int SFicAlMoverAInicioExt ( SFicAleatorio * p_ficObj, int iSaltarNumMagico )
{
	int				iRes;
	unsigned long	ulPos;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		if ( ( p_ficObj->iAbierto == 1 ) && ES_VALIDO ( p_ficObj->p_fObj ) )
		{
			if ( iSaltarNumMagico == 1 )
			{
				ulPos = sizeof ( unsigned long );
			}
			else
			{
				ulPos = 0;
			}

			fseek ( p_ficObj->p_fObj, ulPos, SEEK_SET );
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

int SFicAlMoverAFinal ( SFicAleatorio * p_ficObj )
{
	int iRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		if ( ( p_ficObj->iAbierto == 1 ) && ES_VALIDO ( p_ficObj->p_fObj ) )
		{
			fseek ( p_ficObj->p_fObj, 0, SEEK_END );
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

int SFicAlEstaEnFinal ( SFicAleatorio * p_ficObj )
{
	int iRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		if ( ( p_ficObj->iAbierto == 1 ) && ES_VALIDO ( p_ficObj->p_fObj ) )
		{
			if ( SFicAlPos( p_ficObj ) >= SFicAlTam( p_ficObj )  )
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

byte SFicAlLeer ( SFicAleatorio * p_ficObj )
{
	byte byRes;

	byRes = 0x00;
	if ( ES_VALIDO ( p_ficObj ) )
	{
		if ( ( p_ficObj->iAbierto == 1 ) && ES_VALIDO ( p_ficObj->p_fObj ) )
		{
			fseek ( p_ficObj->p_fObj, 0, SEEK_CUR );
			fread ( &byRes, sizeof ( byte ), 1, p_ficObj->p_fObj );
		}
	}
	return ( byRes );
}

int SFicAlLeerBuffer ( SFicAleatorio * p_ficObj, byte * p_byContenido, unsigned long * p_ulTam )
{
	int iRes;

	if ( ES_VALIDO ( p_ficObj ) && ES_VALIDO ( p_byContenido ) && ES_VALIDO ( p_ulTam ) )
	{
		if ( ( *p_ulTam > 0 ) && ( p_ficObj->iAbierto == 1 ) && ES_VALIDO ( p_ficObj->p_fObj ) )
		{
			fseek ( p_ficObj->p_fObj, 0, SEEK_CUR );
			*p_ulTam = fread ( p_byContenido, sizeof ( byte ), *p_ulTam, p_ficObj->p_fObj );
			if ( *p_ulTam > 0 )
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

int SFicAlEscribir ( SFicAleatorio * p_ficObj, byte byValor )
{
	int iRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		if ( ( p_ficObj->iAbierto == 1 ) && ES_VALIDO ( p_ficObj->p_fObj ) )
		{
			fseek ( p_ficObj->p_fObj, 0, SEEK_CUR );
			if ( fwrite ( &byValor, sizeof ( byte ), 1, p_ficObj->p_fObj ) == 1 )
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

int SFicAlEscribirBuffer ( SFicAleatorio * p_ficObj, byte * p_byContenido, unsigned long * p_ulTam )
{
	int iRes;

	if ( ES_VALIDO ( p_ficObj ) && ES_VALIDO ( p_byContenido ) && ES_VALIDO ( p_ulTam ) )
	{
		if ( ( *p_ulTam > 0 ) && ( p_ficObj->iAbierto == 1 ) && ES_VALIDO ( p_ficObj->p_fObj ) )
		{
			fseek ( p_ficObj->p_fObj, 0, SEEK_CUR );
			*p_ulTam = fwrite ( p_byContenido, sizeof ( byte ), *p_ulTam, p_ficObj->p_fObj );
			if ( *p_ulTam > 0 )
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

byte SFicAlLeerEn ( SFicAleatorio * p_ficObj, unsigned long ulPos )
{
	byte byRes;

	byRes = 0x00;
	if ( ES_VALIDO ( p_ficObj ) )
	{
		if ( ( p_ficObj->iAbierto == 1 ) && ES_VALIDO ( p_ficObj->p_fObj ) )
		{
			fseek ( p_ficObj->p_fObj, ulPos, SEEK_SET );
			fread ( &byRes, sizeof ( byte ), 1, p_ficObj->p_fObj );
		}
	}
	return ( byRes );
}

int SFicAlLeerBufferEn ( SFicAleatorio * p_ficObj, unsigned long ulPos, byte * p_byContenido, unsigned long * p_ulTam )
{
	int iRes;

	if ( ES_VALIDO ( p_ficObj ) && ES_VALIDO ( p_byContenido ) && ES_VALIDO ( p_ulTam ) )
	{
		if ( ( *p_ulTam > 0 ) && ( p_ficObj->iAbierto == 1 ) && ES_VALIDO ( p_ficObj->p_fObj ) )
		{
			fseek ( p_ficObj->p_fObj, ulPos, SEEK_SET );
			*p_ulTam = fread ( p_byContenido, sizeof ( byte ), *p_ulTam, p_ficObj->p_fObj );
			if ( *p_ulTam > 0 )
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

int SFicAlEscribirEn ( SFicAleatorio * p_ficObj, unsigned long ulPos, byte byValor )
{
	int iRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		if ( ( p_ficObj->iAbierto == 1 ) && ES_VALIDO ( p_ficObj->p_fObj ) )
		{
			fseek ( p_ficObj->p_fObj, ulPos, SEEK_SET );
			if ( fwrite ( &byValor, sizeof ( byte ), 1, p_ficObj->p_fObj ) == 1 )
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

int SFicAlEscribirBufferEn ( SFicAleatorio * p_ficObj, unsigned long ulPos, byte * p_byContenido, unsigned long * p_ulTam )
{
	int iRes;

	if ( ES_VALIDO ( p_ficObj ) && ES_VALIDO ( p_byContenido ) && ES_VALIDO ( p_ulTam ) )
	{
		if ( ( *p_ulTam > 0 ) && ( p_ficObj->iAbierto == 1 ) && ES_VALIDO ( p_ficObj->p_fObj ) )
		{
			fseek ( p_ficObj->p_fObj, ulPos, SEEK_SET );
			*p_ulTam = fwrite ( p_byContenido, sizeof ( byte ), *p_ulTam, p_ficObj->p_fObj );
			if ( *p_ulTam > 0 )
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

unsigned long SFicAlNumeroMagico ( SFicAleatorio * p_ficObj )
{
	unsigned long ulRes;

	ulRes = 0x0000;
	if ( ES_VALIDO ( p_ficObj ) )
	{
		if ( ( p_ficObj->iAbierto == 1 ) && ES_VALIDO ( p_ficObj->p_fObj ) )
		{
			fseek ( p_ficObj->p_fObj, 0, SEEK_SET );
			fread ( &ulRes, sizeof ( unsigned long ), 1, p_ficObj->p_fObj );
		}
	}
	return ( ulRes );
}

int SFicAlEstablecerNumeroMagico ( SFicAleatorio * p_ficObj, unsigned long ulNumero )
{
	int iRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		if ( ( p_ficObj->iAbierto == 1 ) && ES_VALIDO ( p_ficObj->p_fObj ) )
		{
			fseek ( p_ficObj->p_fObj, 0, SEEK_SET );
			if ( fwrite ( &ulNumero, sizeof ( unsigned long ), 1, p_ficObj->p_fObj ) == 1 )
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
