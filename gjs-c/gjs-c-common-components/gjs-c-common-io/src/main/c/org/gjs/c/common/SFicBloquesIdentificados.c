
#include "SFicBloquesIdentificados.h"

#include "FicherosConfig.h"



#define FIC_BLOQID_TAM_INFO_CABECERA			(2 * sizeof ( unsigned long ) )
#define FIC_BLOQID_POS_MIN_ID					0
#define FIC_BLOQID_POS_MAX_ID					sizeof(unsigned long)



int _SFicBloqIdActualizarInfoCabecera ( SFicBloquesIdentificados * p_ficObj ); 
int _SFicBloqIdCargarInfoCabecera ( SFicBloquesIdentificados * p_ficObj );
int _SFicBloqIdActualizarValores ( SFicBloquesIdentificados * p_ficObj );




SFicBloquesIdentificados * SFicBloqIdCrear ( const char * p_cRuta, unsigned long ulTamDatosBloque, unsigned long ulTamDatosCab )
{
	SFicBloquesIdentificados * p_ficObj;
	
	p_ficObj= (SFicBloquesIdentificados *) MemReservar ( sizeof ( SFicBloquesIdentificados ) );
	if ( ES_VALIDO ( p_ficObj ) )
	{
		p_ficObj->ulMinId = 0;
		p_ficObj->ulMaxId = 0;
		p_ficObj->p_ficObj = SFicBloqCrear ( p_cRuta, ulTamDatosBloque + FIC_BLOQID_TAM_ID, ulTamDatosCab + FIC_BLOQID_TAM_INFO_CABECERA );
	}
	else
	{
		p_ficObj = NULL;
	}
	return ( p_ficObj );
}

SFicBloquesIdentificados * SFicBloqIdAsignar ( const char * p_cRuta )
{
	SFicBloquesIdentificados *	p_ficObj;
	
	p_ficObj = (SFicBloquesIdentificados *) MemReservar ( sizeof ( SFicBloquesIdentificados ) );
	if ( ES_VALIDO ( p_ficObj ) )
	{
		p_ficObj->p_ficObj = SFicBloqAsignar ( p_cRuta );
		if ( ES_VALIDO ( p_ficObj->p_ficObj ) )
		{
			if ( _SFicBloqIdCargarInfoCabecera ( p_ficObj ) == 0 )
			{
				SFicBloqIdDestruir ( &p_ficObj );
			}
		}
		else
		{
			SFicBloqIdDestruir ( &p_ficObj );
		}
	}
	else
	{
		p_ficObj = NULL;
	}
	return ( p_ficObj );
}

SFicBloquesIdentificados * SFicBloqIdCrearExt ( const char * p_cDir, const char * p_cFic, unsigned long ulTamDatosBloque, unsigned long ulTamDatosCab, int iNumMagico )
{
	SFicBloquesIdentificados * p_ficObj;
	
	p_ficObj= (SFicBloquesIdentificados *) MemReservar ( sizeof ( SFicBloquesIdentificados ) );
	if ( ES_VALIDO ( p_ficObj ) )
	{
		p_ficObj->ulMinId = 0;
		p_ficObj->ulMaxId = 0;
		p_ficObj->p_ficObj = SFicBloqCrearExt ( p_cDir, p_cFic, ulTamDatosBloque + FIC_BLOQID_TAM_ID, ulTamDatosCab + FIC_BLOQID_TAM_INFO_CABECERA, iNumMagico );
	}
	else
	{
		p_ficObj = NULL;
	}
	return ( p_ficObj );
}

SFicBloquesIdentificados * SFicBloqIdAsignarExt ( const char * p_cDir, const char * p_cFic, int iNumMagico )
{
	SFicBloquesIdentificados *	p_ficObj;
	
	p_ficObj = (SFicBloquesIdentificados *) MemReservar ( sizeof ( SFicBloquesIdentificados ) );
	if ( ES_VALIDO ( p_ficObj ) )
	{
		p_ficObj->p_ficObj = SFicBloqAsignarExt ( p_cDir, p_cFic, iNumMagico );
		if ( ES_VALIDO ( p_ficObj->p_ficObj ) )
		{
			if ( _SFicBloqIdCargarInfoCabecera ( p_ficObj ) == 0 )
			{
				SFicBloqIdDestruir ( &p_ficObj );
			}
		}
	}
	else
	{
		p_ficObj = NULL;
	}
	return ( p_ficObj );
}

SFicBloquesIdentificados * SFicBloqIdCrearRuta ( SRuta * p_rutRuta, unsigned long ulTamDatosBloque, unsigned long ulTamDatosCab )
{
	SFicBloquesIdentificados *	p_ficObj;
	char *						p_cRuta;
	
	if ( SRutEsValida ( p_rutRuta ) == 1 )
	{
		if ( SRutEsFichero ( p_rutRuta ) == 1 )
		{
			p_cRuta = SRutRutaAbsolutaLit ( p_rutRuta );
			if ( SRutExiste ( p_rutRuta ) == 1 )
			{
				p_ficObj = SFicBloqIdAsignar ( p_cRuta );
			}
			else
			{
				p_ficObj = SFicBloqIdCrear ( p_cRuta, ulTamDatosBloque, ulTamDatosCab );
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

void SFicBloqIdDestruir ( SFicBloquesIdentificados ** p_p_ficObj )
{
	SFicBloquesIdentificados * p_ficObj;
	
	if ( ES_VALIDO ( p_p_ficObj ) )
	{
		p_ficObj = *p_p_ficObj;

		if ( ES_VALIDO ( p_ficObj ) )
		{
			SFicBloqDestruir ( &(p_ficObj->p_ficObj) );
			MemLiberar ( (void **) p_p_ficObj );
		}
	}
}

void SFicBloqIdEliminar ( SFicBloquesIdentificados ** p_p_ficObj )
{
	SFicBloquesIdentificados * p_ficObj;
	
	if ( ES_VALIDO ( p_p_ficObj ) )
	{
		p_ficObj = *p_p_ficObj;

		if ( ES_VALIDO ( p_ficObj ) )
		{
			SFicBloqEliminar ( &(p_ficObj->p_ficObj) );
			SFicBloqIdDestruir ( p_p_ficObj );
		}
	}
}

int SFicBloqIdEsValido ( SFicBloquesIdentificados * p_ficObj )
{
	int iRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		iRes = SFicBloqEsValido ( p_ficObj->p_ficObj );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

const char * SFicBloqIdRuta ( SFicBloquesIdentificados * p_ficObj )
{
	const char * p_cRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		p_cRes = SFicBloqRuta ( p_ficObj->p_ficObj );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

char * SFicBloqIdDirectorio ( SFicBloquesIdentificados * p_ficObj )
{
	char * p_cRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		p_cRes = SFicBloqDirectorio ( p_ficObj->p_ficObj );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

char * SFicBloqIdFichero ( SFicBloquesIdentificados * p_ficObj )
{
	char * p_cRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		p_cRes = SFicBloqFichero ( p_ficObj->p_ficObj );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

int SFicBloqIdEstablecerRuta ( SFicBloquesIdentificados * p_ficObj, const char * p_cRuta )
{
	int iRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		iRes = SFicBloqEstablecerRuta ( p_ficObj->p_ficObj, p_cRuta );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SFicBloqIdEstablecerRutaExt ( SFicBloquesIdentificados * p_ficObj, const char * p_cDir, const char * p_cFic )
{
	int iRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		iRes = SFicBloqEstablecerRutaExt ( p_ficObj->p_ficObj, p_cDir, p_cFic );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SFicBloqIdTieneNumeroMagico ( SFicBloquesIdentificados * p_ficObj )
{
	int iRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		iRes = SFicBloqTieneNumeroMagico ( p_ficObj->p_ficObj );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

unsigned long SFicBloqIdNumeroMagico ( SFicBloquesIdentificados * p_ficObj )
{
	unsigned long ulRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		ulRes = SFicBloqNumeroMagico ( p_ficObj->p_ficObj );
	}
	else
	{
		ulRes = 0;
	}
	return ( ulRes );
}

int SFicBloqIdEstablecerNumeroMagico ( SFicBloquesIdentificados * p_ficObj, unsigned long ulNumero )
{
	int iRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		iRes = SFicBloqEstablecerNumeroMagico (  p_ficObj->p_ficObj, ulNumero );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

unsigned long SFicBloqIdTamDatosCabecera ( SFicBloquesIdentificados * p_ficObj )
{
	unsigned long ulRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		ulRes = SFicBloqTamDatosCabecera ( p_ficObj->p_ficObj ) - FIC_BLOQID_TAM_INFO_CABECERA;
	}
	else
	{
		ulRes = 0;
	}
	return ( ulRes );
}

int SFicBloqIdEstablecerTamDatosCabecera ( SFicBloquesIdentificados * p_ficObj, unsigned long ulTam )
{
	int iRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		iRes = SFicBloqEstablecerTamDatosCabecera ( p_ficObj->p_ficObj, ulTam + FIC_BLOQID_TAM_INFO_CABECERA );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

unsigned long SFicBloqIdTamBloque ( SFicBloquesIdentificados * p_ficObj )
{
	unsigned long ulRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		ulRes = SFicBloqTamBloque ( p_ficObj->p_ficObj ) - FIC_BLOQID_TAM_ID;
	}
	else
	{
		ulRes = 0;
	}
	return ( ulRes );
}

unsigned long SFicBloqIdTamDatosBloque ( SFicBloquesIdentificados * p_ficObj )
{
	unsigned long ulRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		ulRes = SFicBloqTamBloque ( p_ficObj->p_ficObj ) - FIC_BLOQID_TAM_ID;
	}
	else
	{
		ulRes = 0;
	}
	return ( ulRes );
}

int SFicBloqIdEstablecerTamDatosBloque ( SFicBloquesIdentificados * p_ficObj, unsigned long ulTam )
{
	int iRes;

	if ( ES_VALIDO ( p_ficObj ) && ( ulTam > 0 ) )
	{
		iRes = SFicBloqEstablecerTamBloque ( p_ficObj->p_ficObj, ulTam + FIC_BLOQID_TAM_ID );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SFicBloqIdAbrir ( SFicBloquesIdentificados * p_ficObj )
{
	return ( SFicBloqIdAbrirExt ( p_ficObj, 0 ) );
}

int SFicBloqIdAbrirExt ( SFicBloquesIdentificados * p_ficObj, int iVaciar )
{
	int	iRes;

	if ( SFicBloqIdEsValido ( p_ficObj ) == 1 )
	{
		if ( SFicBloqAbrirExt ( p_ficObj->p_ficObj, iVaciar ) == 1 )
		{
			if ( iVaciar == 1 )
			{
				p_ficObj->ulMaxId = 0;
				p_ficObj->ulMinId = 0;
				iRes = _SFicBloqIdActualizarInfoCabecera ( p_ficObj );
			}
			else
			{
				iRes = _SFicBloqIdCargarInfoCabecera ( p_ficObj );
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

int SFicBloqIdCerrar ( SFicBloquesIdentificados * p_ficObj )
{
	int iRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		iRes = SFicBloqCerrar ( p_ficObj->p_ficObj );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SFicBloqIdEstaAbierto ( SFicBloquesIdentificados * p_ficObj )
{
	int iRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		iRes = SFicBloqEstaAbierto ( p_ficObj->p_ficObj );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

unsigned long SFicBloqIdMinId ( SFicBloquesIdentificados * p_ficObj )
{
	unsigned long  ulRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		ulRes = p_ficObj->ulMinId;
	}
	else
	{
		ulRes = 0;
	}
	return ( ulRes );
}

unsigned long SFicBloqIdMaxId ( SFicBloquesIdentificados * p_ficObj )
{
	unsigned long  ulRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		ulRes = p_ficObj->ulMaxId;
	}
	else
	{
		ulRes = 0;
	}
	return ( ulRes );
}

unsigned long SFicBloqIdTam  ( SFicBloquesIdentificados * p_ficObj )
{
	unsigned long  ulRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		ulRes = SFicBloqTam  ( p_ficObj->p_ficObj );
	}
	else
	{
		ulRes = 0;
	}
	return ( ulRes );
}

unsigned long SFicBloqIdTamDatos  ( SFicBloquesIdentificados * p_ficObj )
{
	unsigned long  ulRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		ulRes = SFicBloqNumBloques ( p_ficObj->p_ficObj ) * SFicBloqTamBloque ( p_ficObj->p_ficObj );
	}
	else
	{
		ulRes = 0;
	}
	return ( ulRes );
}

unsigned long SFicBloqIdNumBloques  ( SFicBloquesIdentificados * p_ficObj )
{
	unsigned long  ulRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		ulRes = SFicBloqNumBloques ( p_ficObj->p_ficObj );
	}
	else
	{
		ulRes = 0;
	}
	return ( ulRes );
}

int SFicBloqIdEstaVacio ( SFicBloquesIdentificados * p_ficObj )
{
	int iRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		if ( SFicBloqIdTamDatos ( p_ficObj ) == 0 )
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

byte * SFicBloqIdLeerDatosCabecera ( SFicBloquesIdentificados * p_ficObj )
{
	unsigned long	ulTam;
	byte *			p_byContenido;
	byte *			p_byCabecera;	

	ulTam = SFicBloqIdTamDatosCabecera ( p_ficObj ); 
	if (  ulTam > 0 )
	{
		p_byCabecera = SFicBloqLeerDatosCabecera ( p_ficObj->p_ficObj );
		if ( ES_VALIDO ( p_byCabecera ) )
		{
			p_byContenido = (byte *) MemReservar ( ulTam );
			if ( ES_VALIDO ( p_byContenido ) )
			{
				MemCopiar ( p_byContenido, &(p_byCabecera [ FIC_BLOQID_TAM_INFO_CABECERA ]), ulTam ); 
			}
			MemLiberar ( (void **) &p_byCabecera );
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

int SFicBloqIdEscribirDatosCabecera ( SFicBloquesIdentificados * p_ficObj, byte * p_byContenido )
{
	int				iRes;
	unsigned long	ulTam;
	byte *			p_byCabecera;	

	ulTam = SFicBloqIdTamDatosCabecera ( p_ficObj ); 
	if (  ( ulTam > 0 ) && ES_VALIDO ( p_byContenido ) )
	{
		p_byCabecera = SFicBloqLeerDatosCabecera ( p_ficObj->p_ficObj );
		if ( ES_VALIDO ( p_byCabecera ) )
		{
			MemCopiar ( &(p_byCabecera [ FIC_BLOQID_TAM_INFO_CABECERA ]), p_byContenido, ulTam ); 
			if ( SFicBloqEscribirDatosCabecera ( p_ficObj->p_ficObj, p_byCabecera ) == 1 )
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

unsigned long SFicBloqIdLeerId ( SFicBloquesIdentificados * p_ficObj, unsigned long ulBloque )
{
	unsigned long	ulId;
	byte *			p_byBloque;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		p_byBloque = SFicBloqLeer ( p_ficObj->p_ficObj, ulBloque );
		if ( ES_VALIDO ( p_byBloque ) )
		{
			MemCopiar ( &ulId, p_byBloque, FIC_BLOQID_TAM_ID );
			MemLiberar ( (void **) &p_byBloque );
		}
		else
		{
			ulId = 0;
		}
	}
	else
	{
		ulId = 0;
	}
	return ( ulId );
}

int SFicBloqIdExisteId ( SFicBloquesIdentificados * p_ficObj, unsigned long ulId )
{
	unsigned long	ulBloque;			
	unsigned long	ulIdBloq;
	byte *			p_byBloque;
	int				iEnc;
	int				iError;
	int				iRes;

	if ( ES_VALIDO ( p_ficObj ) && ( ulId != FIC_BLOQID_IDNULO ) )
	{
		if ( SFicBloqEstaAbierto ( p_ficObj->p_ficObj ) == 1 )
		{
			if ( ( ulId == p_ficObj->ulMinId ) || ( ulId == p_ficObj->ulMaxId ) )
			{
				iRes = 1;
			}
			else if ( ( ulId > p_ficObj->ulMinId ) && ( ulId < p_ficObj->ulMaxId ) )
			{
				p_byBloque = (byte *) MemReservar ( SFicBloqTamBloque ( p_ficObj->p_ficObj ) );
				if ( ES_VALIDO ( p_byBloque ) )
				{
					iEnc = 0;
					iError = 0;
					ulBloque = 0;
					while ( ( iEnc == 0 ) && ( iError == 0 ) && ( ulBloque < SFicBloqNumBloques ( p_ficObj->p_ficObj ) ) )
					{
						if ( SFicBloqLeerExt ( p_ficObj->p_ficObj, ulBloque, p_byBloque ) == 1 )
						{
							MemCopiar ( &ulIdBloq, p_byBloque, FIC_BLOQID_TAM_ID );
							if ( ulIdBloq == ulId )
							{
								iEnc = 1;
							}
							else
							{
								ulBloque = ulBloque + 1;
							}
						}
						else
						{
							iError = 1;
						}
					}

					MemLiberar ( (void **) &p_byBloque );

					if ( iError == 0 )
					{
						if ( iEnc == 1 )
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

unsigned long SFicBloqIdBloqueId ( SFicBloquesIdentificados * p_ficObj, unsigned long ulId )
{
	unsigned long	ulBloque;			
	unsigned long	ulIdBloq;
	byte *			p_byBloque;
	int				iEnc;
	int				iError;

	if ( ES_VALIDO ( p_ficObj ) && ( ulId != FIC_BLOQID_IDNULO ) )
	{
		if ( SFicBloqEstaAbierto ( p_ficObj->p_ficObj ) == 1 )
		{
			if ( ( ulId >= p_ficObj->ulMinId ) && ( ulId <= p_ficObj->ulMaxId ) )
			{
				p_byBloque = (byte *) MemReservar ( SFicBloqTamBloque ( p_ficObj->p_ficObj ) );
				if ( ES_VALIDO ( p_byBloque ) )
				{
					iEnc = 0;
					iError = 0;
					ulBloque = 0;
					while ( ( iEnc == 0 ) && ( iError == 0 ) && ( ulBloque < SFicBloqNumBloques ( p_ficObj->p_ficObj ) ) )
					{
						if ( SFicBloqLeerExt ( p_ficObj->p_ficObj, ulBloque, p_byBloque ) == 1 )
						{
							MemCopiar ( &ulIdBloq, p_byBloque, FIC_BLOQID_TAM_ID );
							if ( ulIdBloq == ulId )
							{
								iEnc = 1;
							}
							else
							{
								ulBloque = ulBloque + 1;
							}
						}
						else
						{
							iError = 1;
						}
					}

					MemLiberar ( (void **) &p_byBloque );

					if ( iError == 0 )
					{
						if ( iEnc == 0 )
						{
							ulBloque = FIC_BLOQID_IDNULO;
						}
					}
					else
					{
						ulBloque = FIC_BLOQID_IDNULO;
					}
				}
				else
				{
					ulBloque = FIC_BLOQID_IDNULO;
				}
			}
			else
			{
				ulBloque = FIC_BLOQID_IDNULO;
			}
		}
		else
		{
			ulBloque = FIC_BLOQID_IDNULO;
		}
	}
	else
	{
		ulBloque = FIC_BLOQID_IDNULO;
	}
	return ( ulBloque );
}

byte * SFicBloqIdLeer ( SFicBloquesIdentificados * p_ficObj, unsigned long ulId )
{
	byte * p_byContenido;

	if ( ES_VALIDO ( p_ficObj ) && ( ulId != FIC_BLOQID_IDNULO ) )
	{
		if ( SFicBloqEstaAbierto ( p_ficObj->p_ficObj ) == 1 )
		{
			p_byContenido = (byte *) MemReservar ( SFicBloqTamBloque ( p_ficObj->p_ficObj ) - FIC_BLOQID_TAM_ID );
			if ( ES_VALIDO ( p_byContenido ) )
			{
				if ( SFicBloqIdLeerExt ( p_ficObj, ulId, p_byContenido ) == 0 )
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

int SFicBloqIdLeerExt ( SFicBloquesIdentificados * p_ficObj, unsigned long ulId, byte * p_byContenido )
{
	byte *			p_byBloque;
	unsigned long	ulBloque;			
	unsigned long	ulIdBloq;
	int				iEnc;
	int				iError;
	int				iRes;

	if ( ES_VALIDO ( p_ficObj ) && ( ulId != FIC_BLOQID_IDNULO ) )
	{
		if ( SFicBloqEstaAbierto ( p_ficObj->p_ficObj ) == 1 )
		{
			if ( ( ulId >= p_ficObj->ulMinId ) && ( ulId <= p_ficObj->ulMaxId ) )
			{
				p_byBloque = (byte *) MemReservar ( SFicBloqTamBloque ( p_ficObj->p_ficObj ) );
				if ( ES_VALIDO ( p_byBloque ) ) 
				{
					iEnc = 0;
					iError = 0;
					ulBloque = 0;
					while ( ( iEnc == 0 ) && ( iError == 0 ) && ( ulBloque < SFicBloqNumBloques ( p_ficObj->p_ficObj ) ) )
					{
						if ( SFicBloqLeerExt ( p_ficObj->p_ficObj, ulBloque, p_byBloque ) == 1 )
						{
							MemCopiar ( &ulIdBloq, p_byBloque, FIC_BLOQID_TAM_ID );
							if ( ulIdBloq == ulId )
							{
								iEnc = 1;
							}
							else
							{
								ulBloque = ulBloque + 1;
							}
						}
						else
						{
							iError = 1;
						}
					}

					if ( ( iError == 0 ) && ( iEnc == 1 ) )
					{
						MemCopiar ( p_byContenido, &(p_byBloque [ FIC_BLOQID_TAM_ID ]), SFicBloqTamBloque ( p_ficObj->p_ficObj ) - FIC_BLOQID_TAM_ID );
						iRes = 1;
					}
					else
					{
						iRes = 0;
					}
					MemLiberar ( (void **) &p_byBloque );
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

int SFicBloqIdModificar ( SFicBloquesIdentificados * p_ficObj, unsigned long ulId, byte * p_byContenido )
{
	byte *			p_byBloque;
	unsigned long	ulBloque;			
	unsigned long	ulIdBloq;
	int				iRes;
	int				iEnc;
	int				iError;

	if ( ES_VALIDO ( p_ficObj ) && ES_VALIDO ( p_byContenido ) && ( ulId != FIC_BLOQID_IDNULO ) )
	{
		if ( SFicBloqEstaAbierto ( p_ficObj->p_ficObj ) == 1 )
		{
			if ( ( ulId >= p_ficObj->ulMinId ) && ( ulId <= p_ficObj->ulMaxId ) )
			{
				p_byBloque = (byte *) MemReservar ( SFicBloqTamBloque ( p_ficObj->p_ficObj ) );
				if ( ES_VALIDO ( p_byBloque ) ) 
				{
					iEnc = 0;
					iError = 0;
					ulBloque = 0;
					while ( ( iEnc == 0 ) && ( iError == 0 ) && ( ulBloque < SFicBloqNumBloques ( p_ficObj->p_ficObj ) ) )
					{
						if ( SFicBloqLeerExt ( p_ficObj->p_ficObj, ulBloque, p_byBloque ) == 1 )
						{
							MemCopiar ( &ulIdBloq, p_byBloque, FIC_BLOQID_TAM_ID );
							if ( ulIdBloq == ulId )
							{
								iEnc = 1;
							}
							else
							{
								ulBloque = ulBloque + 1;
							}
						}
						else
						{
							iError = 1;
						}
					}

					if ( ( iError == 0 ) && ( iEnc == 1 ) )
					{
						MemCopiar ( &(p_byBloque [ FIC_BLOQID_TAM_ID ]), p_byContenido, SFicBloqTamBloque ( p_ficObj->p_ficObj ) - FIC_BLOQID_TAM_ID );
						iRes = SFicBloqEscribir ( p_ficObj->p_ficObj, ulBloque, p_byBloque );
					}
					else
					{
						iRes = 0;
					}
					MemLiberar ( (void **) &p_byBloque );
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

int SFicBloqIdInsertar ( SFicBloquesIdentificados * p_ficObj, unsigned long ulId, byte * p_byContenido )
{
	byte *			p_byBloque;
	unsigned long	ulBloque;			
	unsigned long	ulIdBloq;
	int				iRes;
	unsigned long	ulPrimerNulo;
	int				iEnc;
	int				iError;

	if ( ES_VALIDO ( p_ficObj ) && ES_VALIDO ( p_byContenido ) && ( ulId != FIC_BLOQID_IDNULO ) )
	{
		if ( SFicBloqEstaAbierto ( p_ficObj->p_ficObj ) == 1 )
		{
			p_byBloque = (byte *) MemReservar ( SFicBloqTamBloque ( p_ficObj->p_ficObj ) );
			if ( ES_VALIDO ( p_byBloque ) ) 
			{
				ulPrimerNulo = FIC_BLOQID_IDNULO;
				iEnc = 0;
				iError = 0;
				ulBloque = 0;
				while ( ( iEnc == 0 ) && ( iError == 0 ) && ( ulBloque < SFicBloqNumBloques ( p_ficObj->p_ficObj ) ) )
				{
					if ( SFicBloqLeerExt ( p_ficObj->p_ficObj, ulBloque, p_byBloque ) == 1 )
					{
						MemCopiar ( &ulIdBloq, p_byBloque, FIC_BLOQID_TAM_ID );
						if ( ulIdBloq == ulId )
						{
							iEnc = 1;
						}
						else if ( ulIdBloq == FIC_BLOQID_IDNULO )
						{
							ulPrimerNulo = ulBloque;
						}
						else
						{
							ulBloque = ulBloque + 1;
						}
					}
					else
					{
						iError = 1;
					}
				}

				if ( ( iError == 0 ) && ( iEnc == 0 ) )
				{
					MemCopiar ( &(p_byBloque [ 0 ]), (void *) &ulId, FIC_BLOQID_TAM_ID );
					MemCopiar ( &(p_byBloque [ FIC_BLOQID_TAM_ID ]), p_byContenido, SFicBloqTamBloque ( p_ficObj->p_ficObj ) - FIC_BLOQID_TAM_ID );

					if ( ulPrimerNulo == FIC_BLOQID_IDNULO )
					{
						ulBloque = SFicBloqNumBloques ( p_ficObj->p_ficObj );
					}
					else
					{
						ulBloque = ulPrimerNulo;
					}

					if ( SFicBloqEscribir ( p_ficObj->p_ficObj, ulBloque, p_byBloque ) == 1 )
					{
						if ( SFicBloqNumBloques ( p_ficObj->p_ficObj ) == 1 )
						{
							p_ficObj->ulMinId = ulId;
							p_ficObj->ulMaxId = ulId;
						}
						else
						{
							if ( ulId < p_ficObj->ulMinId ) 
							{
								p_ficObj->ulMinId = ulId;
							}
							else if ( ulId > p_ficObj->ulMaxId )
							{
								p_ficObj->ulMaxId = ulId;
							}
						}
						iRes = 1;
					}
					else
					{
						iRes = 0;
					}
					MemLiberar ( (void **) &p_byBloque );
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

int SFicBloqIdSuprimir ( SFicBloquesIdentificados * p_ficObj, unsigned long ulId )
{
	byte *			p_byBloque;
	unsigned long	ulBloque;			
	unsigned long	ulIdBloq;
	int				iRes;
	int				iEnc;
	int				iError;

	if ( ES_VALIDO ( p_ficObj ) && ( ulId != FIC_BLOQID_IDNULO ) )
	{
		if ( SFicBloqEstaAbierto ( p_ficObj->p_ficObj ) == 1 )
		{
			if ( ( ulId >= p_ficObj->ulMinId ) && ( ulId <= p_ficObj->ulMaxId ) )
			{
				p_byBloque = (byte *) MemReservar ( SFicBloqTamBloque ( p_ficObj->p_ficObj ) );
				if ( ES_VALIDO ( p_byBloque ) ) 
				{
					iEnc = 0;
					iError = 0;
					ulBloque = 0;
					while ( ( iEnc == 0 ) && ( iError == 0 ) && ( ulBloque < SFicBloqNumBloques ( p_ficObj->p_ficObj ) ) )
					{
						if ( SFicBloqLeerExt ( p_ficObj->p_ficObj, ulBloque, p_byBloque ) == 1 )
						{
							MemCopiar ( &ulIdBloq, p_byBloque, FIC_BLOQID_TAM_ID );
							if ( ulIdBloq == ulId )
							{
								iEnc = 1;
							}
							else
							{
								ulBloque = ulBloque + 1;
							}
						}
						else
						{
							iError = 1;
						}
					}

					if ( ( iError == 0 ) && ( iEnc == 1 ) )
					{
						ulIdBloq = FIC_BLOQID_IDNULO;
						MemLimpiar ( p_byBloque, SFicBloqTamBloque ( p_ficObj->p_ficObj ) );
						MemCopiar ( p_byBloque, &ulIdBloq, FIC_BLOQID_TAM_ID );
						iRes = SFicBloqEscribir ( p_ficObj->p_ficObj, ulBloque, p_byBloque );
						if ( iRes == 1 )
						{
							if ( ( ulId == p_ficObj->ulMinId ) || ( ulId == p_ficObj->ulMaxId ) )
							{
								if ( _SFicBloqIdActualizarValores ( p_ficObj ) == 1 )
								{
									iRes = _SFicBloqIdActualizarInfoCabecera ( p_ficObj ); 
								}
								else
								{
									iRes = 0;
								}
							}
						}
					}
					else
					{
						iRes = 0;
					}
					MemLiberar ( (void **) &p_byBloque );
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

byte * SFicBloqIdLeerBloque ( SFicBloquesIdentificados * p_ficObj, unsigned long ulBloque )
{
	byte *	p_byBloque;
	byte *	p_byContenido;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		p_byBloque = SFicBloqLeer ( p_ficObj->p_ficObj, ulBloque );
		if ( ES_VALIDO ( p_byBloque ) )
		{
			p_byContenido = (byte *) MemReservar ( SFicBloqTamBloque ( p_ficObj->p_ficObj ) - FIC_BLOQID_TAM_ID );
			if ( ES_VALIDO ( p_byContenido ) )
			{
				MemCopiar ( p_byContenido, &(p_byBloque [ FIC_BLOQID_TAM_ID ]), SFicBloqTamBloque ( p_ficObj->p_ficObj ) - FIC_BLOQID_TAM_ID );
			}
			MemLiberar ( (void **) &p_byBloque );
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

int SFicBloqIdLeerBloqueExt ( SFicBloquesIdentificados * p_ficObj, unsigned long ulBloque, unsigned long * p_ulId, byte * p_byContenido )
{
	byte *	p_byBloque;
	int		iRes;

	if ( ES_VALIDO ( p_ficObj ) && ES_VALIDO ( p_ulId ) && ES_VALIDO ( p_byContenido ) )
	{
		p_byBloque = SFicBloqLeer ( p_ficObj->p_ficObj, ulBloque );
		if ( ES_VALIDO ( p_byBloque ) )
		{
			p_byContenido = (byte *) MemReservar ( SFicBloqTamBloque ( p_ficObj->p_ficObj ) - FIC_BLOQID_TAM_ID );
			if ( ES_VALIDO ( p_byContenido ) )
			{
				MemCopiar ( (void *) p_ulId, &(p_byBloque [ 0 ]), FIC_BLOQID_TAM_ID );
				MemCopiar ( p_byContenido, &(p_byBloque [ FIC_BLOQID_TAM_ID ]), SFicBloqTamBloque ( p_ficObj->p_ficObj ) - FIC_BLOQID_TAM_ID );
				iRes = 1;
			}
			MemLiberar ( (void **) &p_byBloque );
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

int SFicBloqIdEscribirBloque ( SFicBloquesIdentificados * p_ficObj, unsigned long ulBloque, byte * p_byContenido )
{
	byte *	p_byBloque;
	int		iRes;

	if ( ES_VALIDO ( p_ficObj ) && ES_VALIDO ( p_byContenido ) )
	{
		if ( ulBloque < SFicBloqNumBloques ( p_ficObj->p_ficObj ) )
		{
			p_byBloque = SFicBloqLeer ( p_ficObj->p_ficObj, ulBloque );
			if ( ES_VALIDO ( p_byBloque ) )
			{
				MemCopiar ( &(p_byBloque [ FIC_BLOQID_TAM_ID ]), p_byContenido, SFicBloqTamBloque ( p_ficObj->p_ficObj ) - FIC_BLOQID_TAM_ID );
				iRes = SFicBloqEscribir ( p_ficObj->p_ficObj, ulBloque, p_byBloque );
				MemLiberar ( (void **) &p_byBloque );
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

int _SFicBloqIdActualizarInfoCabecera ( SFicBloquesIdentificados * p_ficObj )
{
	int		iRes;
	byte *	p_byCabecera;	

	if ( ES_VALIDO ( p_ficObj ) )
	{
		p_byCabecera = SFicBloqLeerDatosCabecera ( p_ficObj->p_ficObj );
		if ( ES_VALIDO ( p_byCabecera ) )
		{
			MemCopiar ( &(p_byCabecera [ FIC_BLOQID_POS_MIN_ID ]), &(p_ficObj->ulMinId), sizeof ( unsigned long ) ); 
			MemCopiar ( &(p_byCabecera [ FIC_BLOQID_POS_MAX_ID ]), &(p_ficObj->ulMaxId), sizeof ( unsigned long ) );

			iRes = SFicBloqEscribirDatosCabecera ( p_ficObj->p_ficObj, p_byCabecera );
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

int _SFicBloqIdCargarInfoCabecera ( SFicBloquesIdentificados * p_ficObj )
{
	int		iRes;
	byte *	p_byCabecera;	

	if ( ES_VALIDO ( p_ficObj ) )
	{
		p_byCabecera = SFicBloqLeerDatosCabecera ( p_ficObj->p_ficObj );
		if ( ES_VALIDO ( p_byCabecera ) )
		{
			MemCopiar ( &(p_ficObj->ulMinId), &(p_byCabecera [ FIC_BLOQID_POS_MIN_ID ]), sizeof ( unsigned long ) ); 
			MemCopiar ( &(p_ficObj->ulMaxId), &(p_byCabecera [ FIC_BLOQID_POS_MAX_ID ]), sizeof ( unsigned long ) );

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

int _SFicBloqIdActualizarValores ( SFicBloquesIdentificados * p_ficObj )
{
	int				iRes;
	byte *			p_byBloque;
	int				iError;
	unsigned long	ulBloque;
	unsigned long	ulIdBloq;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		p_byBloque = (byte *) MemReservar ( SFicBloqTamBloque ( p_ficObj->p_ficObj ) );
		if ( ES_VALIDO ( p_byBloque ) )
		{
			p_ficObj->ulMinId = FIC_BLOQID_IDNULO;
			p_ficObj->ulMaxId = 0;
			iError = 0;
			ulBloque = 0;
			while ( ( iError == 0 ) && ( ulBloque < SFicBloqNumBloques ( p_ficObj->p_ficObj ) ) )
			{
				if ( SFicBloqLeerExt ( p_ficObj->p_ficObj, ulBloque, p_byBloque ) == 1 )
				{
					MemCopiar ( &ulIdBloq, p_byBloque, FIC_BLOQID_TAM_ID );
					if ( ulIdBloq != FIC_BLOQID_IDNULO )
					{
						if ( p_ficObj->ulMinId > ulIdBloq )
						{
							p_ficObj->ulMinId = ulIdBloq;
						}
						if ( p_ficObj->ulMaxId < ulIdBloq )
						{
							p_ficObj->ulMaxId = ulIdBloq;
						}
					}
				}
				else
				{
					iError = 1;
				}
				ulBloque = ulBloque + 1;
			}
			MemLiberar ( (void **) &p_byBloque );
			if ( iError == 0 )
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
