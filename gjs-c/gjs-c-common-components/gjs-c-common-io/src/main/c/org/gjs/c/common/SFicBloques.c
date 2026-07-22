
#include "SFicBloques.h"

#include "FicherosConfig.h"



#define FIC_BLOQ_TAM_INFO_CABECERA			(2 * sizeof ( unsigned long ) )
#define FIC_BLOQ_POS_TAM_BLOQUE				0
#define FIC_BLOQ_POS_NUM_BLOQUES			sizeof ( unsigned long )



int _SFicBloqActualizarInfoCabecera ( SFicBloques * p_ficObj ); 
int _SFicBloqCargarInfoCabecera ( SFicBloques * p_ficObj );




SFicBloques * SFicBloqCrear ( const char * p_cRuta, unsigned long ulTamBloque, unsigned long ulTamDatosCab )
{
	SFicBloques * p_ficObj;
	
	p_ficObj = (SFicBloques *) MemReservar ( sizeof ( SFicBloques ) );
	if ( ES_VALIDO ( p_ficObj ) )
	{
		p_ficObj->ulTamBloque = ulTamBloque;
		p_ficObj->ulNumBloques = 0;
		p_ficObj->p_ficObj = SFicEncCrear ( p_cRuta, ulTamDatosCab + FIC_BLOQ_TAM_INFO_CABECERA );
		if ( ES_VALIDO ( p_ficObj->p_ficObj ) )
		{
			if ( SFicEncAbrirExt ( p_ficObj->p_ficObj, 1 ) == 1 )
			{
				if ( _SFicBloqActualizarInfoCabecera ( p_ficObj ) == 1 )
				{
					SFicEncCerrar ( p_ficObj->p_ficObj );
				}
				else
				{
					SFicBloqDestruir ( &p_ficObj );
				}
			}
			else
			{
				SFicBloqDestruir ( &p_ficObj );
			}
		}
	}
	else
	{
		p_ficObj = NULL;
	}
	return ( p_ficObj );
}

SFicBloques * SFicBloqAsignar ( const char * p_cRuta )
{
	SFicBloques *	p_ficObj;
	
	p_ficObj = (SFicBloques *) MemReservar ( sizeof ( SFicBloques ) );
	if ( ES_VALIDO ( p_ficObj ) )
	{
		p_ficObj->p_ficObj = SFicEncAsignar ( p_cRuta );
		if ( ES_VALIDO ( p_ficObj->p_ficObj ) )
		{
			if ( _SFicBloqCargarInfoCabecera ( p_ficObj ) == 0 )
			{
				SFicBloqDestruir ( &p_ficObj );
			}
		}
		else
		{
			SFicBloqDestruir ( &p_ficObj );
		}
	}
	else
	{
		p_ficObj = NULL;
	}
	return ( p_ficObj );
}

SFicBloques * SFicBloqCrearExt ( const char * p_cDir, const char * p_cFic, unsigned long ulTamBloque, unsigned long ulTamDatosCab, int iNumMagico )
{
	SFicBloques * p_ficObj;
	
	p_ficObj = (SFicBloques *) MemReservar ( sizeof ( SFicBloques ) );
	if ( ES_VALIDO ( p_ficObj ) )
	{
		p_ficObj->ulTamBloque = ulTamBloque;
		p_ficObj->ulNumBloques = 0;
		p_ficObj->p_ficObj = SFicEncCrearExt ( p_cDir, p_cFic, ulTamDatosCab + FIC_BLOQ_TAM_INFO_CABECERA, iNumMagico );
	}
	else
	{
		p_ficObj = NULL;
	}
	return ( p_ficObj );
}

SFicBloques * SFicBloqAsignarExt ( const char * p_cDir, const char * p_cFic, int iNumMagico )
{
	SFicBloques *	p_ficObj;
	
	p_ficObj = (SFicBloques *) MemReservar ( sizeof ( SFicBloques ) );
	if ( ES_VALIDO ( p_ficObj ) )
	{
		p_ficObj->p_ficObj = SFicEncAsignarExt ( p_cDir, p_cFic, iNumMagico );
		if ( ES_VALIDO ( p_ficObj->p_ficObj ) )
		{
			if ( _SFicBloqCargarInfoCabecera ( p_ficObj ) == 0 )
			{
				SFicBloqDestruir ( &p_ficObj );
			}
		}
	}
	else
	{
		p_ficObj = NULL;
	}
	return ( p_ficObj );
}

SFicBloques * SFicBloqCrearRuta ( SRuta * p_rutRuta, unsigned long ulTamBloque, unsigned long ulTamDatosCab )
{
	SFicBloques *	p_ficObj;
	char *			p_cRuta;
	
	if ( SRutEsValida ( p_rutRuta ) == 1 )
	{
		if ( SRutEsFichero ( p_rutRuta ) == 1 )
		{
			p_cRuta = SRutRutaAbsolutaLit ( p_rutRuta );
			if ( SRutExiste ( p_rutRuta ) == 1 )
			{
				p_ficObj = SFicBloqAsignar ( p_cRuta );
			}
			else
			{
				p_ficObj = SFicBloqCrear ( p_cRuta, ulTamBloque, ulTamDatosCab );
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

void SFicBloqDestruir ( SFicBloques ** p_p_ficObj )
{
	SFicBloques * p_ficObj;
	
	if ( ES_VALIDO ( p_p_ficObj ) )
	{
		p_ficObj = *p_p_ficObj;

		if ( ES_VALIDO ( p_ficObj ) )
		{
			SFicEncDestruir ( &(p_ficObj->p_ficObj) );
			MemLiberar ( (void **)p_p_ficObj );
		}
	}
}

void SFicBloqEliminar ( SFicBloques ** p_p_ficObj )
{
	SFicBloques * p_ficObj;
	
	if ( ES_VALIDO ( p_p_ficObj ) )
	{
		p_ficObj = *p_p_ficObj;

		if ( ES_VALIDO ( p_ficObj ) )
		{
			SFicEncEliminar ( &(p_ficObj->p_ficObj) );
			SFicBloqDestruir ( p_p_ficObj );
		}
	}
}

int SFicBloqEsValido ( SFicBloques * p_ficObj )
{
	int iRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		if ( ( p_ficObj->ulTamBloque > 0 ) && ( SFicEncEsValido ( p_ficObj->p_ficObj ) == 1 ) )
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

const char * SFicBloqRuta ( SFicBloques * p_ficObj )
{
	const char * p_cRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		p_cRes = SFicEncRuta ( p_ficObj->p_ficObj );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

char * SFicBloqDirectorio ( SFicBloques * p_ficObj )
{
	char * p_cRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		p_cRes = SFicEncDirectorio ( p_ficObj->p_ficObj );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

char * SFicBloqFichero ( SFicBloques * p_ficObj )
{
	char * p_cRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		p_cRes = SFicEncFichero ( p_ficObj->p_ficObj );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

int SFicBloqEstablecerRuta ( SFicBloques * p_ficObj, const char * p_cRuta )
{
	int iRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		iRes = SFicEncEstablecerRuta ( p_ficObj->p_ficObj, p_cRuta );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SFicBloqEstablecerRutaExt ( SFicBloques * p_ficObj, const char * p_cDir, const char * p_cFic )
{
	int iRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		iRes = SFicEncEstablecerRutaExt ( p_ficObj->p_ficObj, p_cDir, p_cFic );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SFicBloqTieneNumeroMagico ( SFicBloques * p_ficObj )
{
	int iRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		iRes = SFicEncTieneNumeroMagico ( p_ficObj->p_ficObj );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

unsigned long SFicBloqNumeroMagico ( SFicBloques * p_ficObj )
{
	unsigned long ulRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		ulRes = SFicEncNumeroMagico ( p_ficObj->p_ficObj );
	}
	else
	{
		ulRes = 0;
	}
	return ( ulRes );
}

int SFicBloqEstablecerNumeroMagico ( SFicBloques * p_ficObj, unsigned long ulNumero )
{
	int iRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		iRes = SFicEncEstablecerNumeroMagico (  p_ficObj->p_ficObj, ulNumero );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

unsigned long SFicBloqTamDatosCabecera ( SFicBloques * p_ficObj )
{
	unsigned long ulRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		ulRes = SFicEncTamCabecera ( p_ficObj->p_ficObj ) - FIC_BLOQ_TAM_INFO_CABECERA;
	}
	else
	{
		ulRes = 0;
	}
	return ( ulRes );
}

int SFicBloqEstablecerTamDatosCabecera ( SFicBloques * p_ficObj, unsigned long ulTam )
{
	int iRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		iRes = SFicEncEstablecerTamCabecera ( p_ficObj->p_ficObj, ulTam + FIC_BLOQ_TAM_INFO_CABECERA );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

unsigned long SFicBloqTamBloque ( SFicBloques * p_ficObj )
{
	unsigned long ulRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		ulRes = p_ficObj->ulTamBloque;
	}
	else
	{
		ulRes = 0;
	}
	return ( ulRes );
}

int SFicBloqEstablecerTamBloque ( SFicBloques * p_ficObj, unsigned long ulTam )
{
	int iRes;

	if ( ES_VALIDO ( p_ficObj ) && ( ulTam > 0 ) )
	{
		if ( SFicEncEstaAbierto ( p_ficObj->p_ficObj ) == 0 )
		{
			p_ficObj->ulTamBloque = ulTam;
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

int SFicBloqAbrir ( SFicBloques * p_ficObj )
{
	return ( SFicBloqAbrirExt ( p_ficObj, 0 ) );
}

int SFicBloqAbrirExt ( SFicBloques * p_ficObj, int iVaciar )
{
	int	iRes;

	if ( SFicBloqEsValido ( p_ficObj ) == 1 )
	{
		if ( SFicEncAbrirExt ( p_ficObj->p_ficObj, iVaciar ) == 1 )
		{
			if ( iVaciar == 1 )
			{
				p_ficObj->ulNumBloques = 0;
				iRes = _SFicBloqActualizarInfoCabecera ( p_ficObj );
			}
			else
			{
				iRes = _SFicBloqCargarInfoCabecera ( p_ficObj );
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

int SFicBloqCerrar ( SFicBloques * p_ficObj )
{
	int iRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		iRes = SFicEncCerrar ( p_ficObj->p_ficObj );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SFicBloqEstaAbierto ( SFicBloques * p_ficObj )
{
	int iRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		iRes = SFicEncEstaAbierto ( p_ficObj->p_ficObj );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

unsigned long SFicBloqTam  ( SFicBloques * p_ficObj )
{
	unsigned long  ulRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		ulRes = SFicEncTam  ( p_ficObj->p_ficObj );
	}
	else
	{
		ulRes = 0;
	}
	return ( ulRes );
}

unsigned long SFicBloqTamDatos  ( SFicBloques * p_ficObj )
{
	unsigned long  ulRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		ulRes = p_ficObj->ulNumBloques * p_ficObj->ulTamBloque; //SFicBloqTam  ( p_ficObj->p_ficObj ) - SFicBloqPosInicialDatos ( p_ficObj );
	}
	else
	{
		ulRes = 0;
	}
	return ( ulRes );
}

unsigned long SFicBloqNumBloques  ( SFicBloques * p_ficObj )
{
	unsigned long  ulRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		ulRes = p_ficObj->ulNumBloques; 
	}
	else
	{
		ulRes = 0;
	}
	return ( ulRes );
}

int SFicBloqEstaVacio ( SFicBloques * p_ficObj )
{
	int iRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		if ( SFicBloqTamDatos ( p_ficObj ) == 0 )
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

byte * SFicBloqLeerDatosCabecera ( SFicBloques * p_ficObj )
{
	unsigned long	ulTam;
	byte *			p_byContenido;

	ulTam = SFicBloqTamDatosCabecera ( p_ficObj ); 
	if (  ulTam > 0 )
	{
		p_byContenido = (byte *) MemReservar ( ulTam );
		if ( ES_VALIDO ( p_byContenido ) )
		{
			if ( SFicBloqLeerDatosCabeceraExt ( p_ficObj, p_byContenido ) == 0 )
			{
				MemLiberar ( (void **) &p_byContenido );
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

int SFicBloqLeerDatosCabeceraExt ( SFicBloques * p_ficObj, byte * p_byContenido )
{
	int				iRes;
	unsigned long	ulTam;
	byte *			p_byCabecera;	

	ulTam = SFicBloqTamDatosCabecera ( p_ficObj ); 
	if ( ES_VALIDO ( p_byContenido ) && ( ulTam > 0 ) )
	{
		p_byCabecera = SFicEncLeerCabecera ( p_ficObj->p_ficObj );
		if ( ES_VALIDO ( p_byCabecera ) )
		{
			iRes = 1;
			MemCopiar ( p_byContenido, &(p_byCabecera [ FIC_BLOQ_TAM_INFO_CABECERA ]), ulTam ); 
			MemLiberar ( (void **) &p_byCabecera );
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

int SFicBloqEscribirDatosCabecera ( SFicBloques * p_ficObj, byte * p_byContenido )
{
	int				iRes;
	unsigned long	ulTam;
	byte *			p_byCabecera;	

	ulTam = SFicBloqTamDatosCabecera ( p_ficObj ); 
	if (  ( ulTam > 0 ) && ES_VALIDO ( p_byContenido ) )
	{
		p_byCabecera = SFicEncLeerCabecera ( p_ficObj->p_ficObj );
		if ( ES_VALIDO ( p_byCabecera ) )
		{
			MemCopiar ( &(p_byCabecera [ FIC_BLOQ_TAM_INFO_CABECERA ]), p_byContenido, ulTam ); 

			if ( SFicEncEscribirCabecera ( p_ficObj->p_ficObj, p_byCabecera ) == 1 )
			{
				iRes = 1;
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
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

byte * SFicBloqLeer ( SFicBloques * p_ficObj, unsigned long ulBloque )
{
	byte * p_byContenido;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		if ( ( ulBloque < p_ficObj->ulNumBloques ) && ( SFicEncEstaAbierto ( p_ficObj->p_ficObj ) == 1 ) )
		{
			p_byContenido = (byte *) MemReservar ( p_ficObj->ulTamBloque );
			if ( ES_VALIDO ( p_byContenido ) )
			{
				if ( SFicBloqLeerExt ( p_ficObj, ulBloque, p_byContenido ) == 0 )
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

int SFicBloqLeerExt ( SFicBloques * p_ficObj, unsigned long ulBloque, byte * p_byContenido )
{
	int				iRes;
	unsigned long	ulPos;
	unsigned long	ulTam;

	if ( ES_VALIDO ( p_ficObj ) && ES_VALIDO ( p_byContenido ) )
	{
		if ( ( ulBloque < p_ficObj->ulNumBloques ) && ( SFicEncEstaAbierto ( p_ficObj->p_ficObj ) == 1 ) )
		{
			ulTam = p_ficObj->ulTamBloque;
			ulPos = ulBloque * p_ficObj->ulTamBloque;
			if ( SFicEncLeerBufferEn ( p_ficObj->p_ficObj, ulPos, p_byContenido, &ulTam ) == 1 )
			{
				if ( ulTam == p_ficObj->ulTamBloque )
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

int SFicBloqEscribir ( SFicBloques * p_ficObj, unsigned long ulBloque, byte * p_byContenido )
{
	int				iRes;
	unsigned long	ulPos;
	unsigned long	ulTam;

	if ( ES_VALIDO ( p_ficObj ) && ES_VALIDO ( p_byContenido ) )
	{
		if ( SFicEncEstaAbierto ( p_ficObj->p_ficObj ) == 1 )
		{
			ulTam = p_ficObj->ulTamBloque;
			ulPos = ulBloque * p_ficObj->ulTamBloque;
			if ( SFicEncEscribirBufferEn ( p_ficObj->p_ficObj, ulPos, p_byContenido, &ulTam ) == 1 )
			{
				if ( ulTam == p_ficObj->ulTamBloque )
				{
					iRes = 1;
					if ( ulBloque >= p_ficObj->ulNumBloques ) 
					{
						p_ficObj->ulNumBloques = ulBloque + 1;
						if ( _SFicBloqActualizarInfoCabecera ( p_ficObj ) == 0 )
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

int SFicBloqLimpiar ( SFicBloques * p_ficObj, unsigned long ulBloque )
{
	byte *			p_byContenido;
	unsigned long	ulTam;
	unsigned long	ulPos;
	int				iRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		if ( ( ulBloque < p_ficObj->ulNumBloques ) && ( SFicEncEstaAbierto ( p_ficObj->p_ficObj ) == 1 ) )
		{
			p_byContenido = (byte *) MemReservar ( p_ficObj->ulTamBloque );
			if ( ES_VALIDO ( p_byContenido ) )
			{
				ulTam = p_ficObj->ulTamBloque;
				ulPos = ulBloque * p_ficObj->ulTamBloque;
				if ( SFicEncEscribirBufferEn ( p_ficObj->p_ficObj, ulPos, p_byContenido, &ulTam ) == 1 )
				{
					if ( ulTam == p_ficObj->ulTamBloque )
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
				MemLiberar ( (void **) &p_byContenido );
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

int SFicBloqLeerParte ( SFicBloques * p_ficObj, unsigned long ulBloque, unsigned long ulDespl, unsigned long ulTam, byte * p_byContenido )
{
	int				iRes;
	unsigned long	ulPos;

	if ( ES_VALIDO ( p_ficObj ) && ES_VALIDO ( p_byContenido ) )
	{
		if ( ( ulBloque < p_ficObj->ulNumBloques ) && ( SFicEncEstaAbierto ( p_ficObj->p_ficObj ) == 1 ) &&
			 ( ulDespl + ulTam <= p_ficObj->ulTamBloque ) )
		{
			ulPos = ulBloque * p_ficObj->ulTamBloque + ulDespl;
			if ( SFicEncLeerBufferEn ( p_ficObj->p_ficObj, ulPos, p_byContenido, &ulTam ) == 1 )
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

int SFicBloqEscribirParte ( SFicBloques * p_ficObj, unsigned long ulBloque, unsigned long ulDespl, unsigned long ulTam, byte * p_byContenido )
{
	int				iRes;
	unsigned long	ulPos;

	if ( ES_VALIDO ( p_ficObj ) && ES_VALIDO ( p_byContenido ) )
	{
		if ( ( ulBloque < p_ficObj->ulNumBloques ) && ( SFicEncEstaAbierto ( p_ficObj->p_ficObj ) == 1 ) &&
			 ( ulDespl + ulTam <= p_ficObj->ulTamBloque ) )
		{
			ulPos = ulBloque * p_ficObj->ulTamBloque + ulDespl;
			if ( SFicEncEscribirBufferEn ( p_ficObj->p_ficObj, ulPos, p_byContenido, &ulTam ) == 1 )
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

int _SFicBloqActualizarInfoCabecera ( SFicBloques * p_ficObj )
{
	int		iRes;
	byte *	p_byCabecera;	

	if ( ES_VALIDO ( p_ficObj ) )
	{
		p_byCabecera = SFicEncCrearBufferCabecera ( p_ficObj->p_ficObj );
		if ( ES_VALIDO ( p_byCabecera ) )
		{
			MemCopiar ( &(p_byCabecera [ FIC_BLOQ_POS_TAM_BLOQUE ]), &(p_ficObj->ulTamBloque), sizeof ( unsigned long ) ); 
			MemCopiar ( &(p_byCabecera [ FIC_BLOQ_POS_NUM_BLOQUES ]), &(p_ficObj->ulNumBloques), sizeof ( unsigned long ) );

			iRes = SFicEncEscribirCabecera ( p_ficObj->p_ficObj, p_byCabecera );
			MemLiberar ( (void **) &p_byCabecera );
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

int _SFicBloqCargarInfoCabecera ( SFicBloques * p_ficObj )
{
	int		iRes;
	byte *	p_byCabecera;	

	if ( ES_VALIDO ( p_ficObj ) )
	{
		p_byCabecera = SFicEncLeerCabecera ( p_ficObj->p_ficObj );
		if ( ES_VALIDO ( p_byCabecera ) )
		{
			MemCopiar ( &(p_ficObj->ulTamBloque), &(p_byCabecera [ FIC_BLOQ_POS_TAM_BLOQUE ]), sizeof ( unsigned long ) ); 
			MemCopiar ( &(p_ficObj->ulNumBloques), &(p_byCabecera [ FIC_BLOQ_POS_NUM_BLOQUES ]), sizeof ( unsigned long ) );

			MemLiberar ( (void **) &p_byCabecera );
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

