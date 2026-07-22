
#include "SFicBloquesOrdenados.h"

#include "FicherosConfig.h"



#define FIC_BLOQORD_TAM_INFO_CABECERA			(2 * sizeof ( unsigned long ) )
#define FIC_BLOQORD_TAM_PUNTEROS				(2 * FIC_BLOQID_TAM_ID)
#define FIC_BLOQORD_POS_PRIMERO					0
#define FIC_BLOQORD_POS_ULTIMO					sizeof ( unsigned long )
#define FIC_BLOQORD_POS_ANT_BLOQUE				0
#define FIC_BLOQORD_POS_SIG_BLOQUE				FIC_BLOQID_TAM_ID
#define FIC_BLOQORD_POS_CONTENIDO_BLOQUE		(2 * FIC_BLOQID_TAM_ID)




int _SFicBloqOrdActualizarInfoCabecera ( SFicBloquesOrdenados * p_ficObj ); 
int _SFicBloqOrdCargarInfoCabecera ( SFicBloquesOrdenados * p_ficObj );
int _SFicBloqOrdLeerPunteros ( SFicBloquesOrdenados * p_ficObj, unsigned long ulBloque, unsigned long * p_ulAnt, unsigned long * p_ulSig );




SFicBloquesOrdenados * SFicBloqOrdCrear ( const char * p_cRuta, unsigned long ulTamDatosBloque, unsigned long ulTamDatosCab )
{
	SFicBloquesOrdenados * p_ficObj;
	
	p_ficObj= (SFicBloquesOrdenados *) MemReservar ( sizeof ( SFicBloquesOrdenados ) );
	if ( ES_VALIDO ( p_ficObj ) )
	{
		p_ficObj->ulPrimero = 0;
		p_ficObj->ulUltimo = 0;
		p_ficObj->ulActual = 0;
		p_ficObj->ulPosActual = 0;
		p_ficObj->p_ficObj = SFicBloqIdCrear ( p_cRuta, ulTamDatosBloque + FIC_BLOQORD_TAM_PUNTEROS, ulTamDatosCab + FIC_BLOQORD_TAM_INFO_CABECERA );
	}
	else
	{
		p_ficObj = NULL;
	}
	return ( p_ficObj );
}

SFicBloquesOrdenados * SFicBloqOrdAsignar ( const char * p_cRuta )
{
	SFicBloquesOrdenados *	p_ficObj;
	
	p_ficObj = (SFicBloquesOrdenados *) MemReservar ( sizeof ( SFicBloquesOrdenados ) );
	if ( ES_VALIDO ( p_ficObj ) )
	{
		p_ficObj->p_ficObj = SFicBloqIdAsignar ( p_cRuta );
		if ( ES_VALIDO ( p_ficObj->p_ficObj ) )
		{
			if ( _SFicBloqOrdCargarInfoCabecera ( p_ficObj ) == 1 )
			{
				p_ficObj->ulActual = p_ficObj->ulPrimero;
				p_ficObj->ulPosActual = 0;
			}
			else
			{
				SFicBloqOrdDestruir ( &p_ficObj );
			}
		}
		else
		{
			SFicBloqOrdDestruir ( &p_ficObj );
		}
	}
	else
	{
		p_ficObj = NULL;
	}
	return ( p_ficObj );
}

SFicBloquesOrdenados * SFicBloqOrdCrearExt ( const char * p_cDir, const char * p_cFic, unsigned long ulTamDatosBloque, unsigned long ulTamDatosCab, int iNumMagico )
{
	SFicBloquesOrdenados * p_ficObj;
	
	p_ficObj= (SFicBloquesOrdenados *) MemReservar ( sizeof ( SFicBloquesOrdenados ) );
	if ( ES_VALIDO ( p_ficObj ) )
	{
		p_ficObj->ulPrimero = 0;
		p_ficObj->ulUltimo = 0;
		p_ficObj->ulActual = 0;
		p_ficObj->ulPosActual = 0;
		p_ficObj->p_ficObj = SFicBloqIdCrearExt ( p_cDir, p_cFic, ulTamDatosBloque + FIC_BLOQORD_TAM_PUNTEROS, ulTamDatosCab + FIC_BLOQORD_TAM_INFO_CABECERA, iNumMagico );
	}
	else
	{
		p_ficObj = NULL;
	}
	return ( p_ficObj );
}

SFicBloquesOrdenados * SFicBloqOrdAsignarExt ( const char * p_cDir, const char * p_cFic, int iNumMagico )
{
	SFicBloquesOrdenados *	p_ficObj;
	
	p_ficObj = (SFicBloquesOrdenados *) MemReservar ( sizeof ( SFicBloquesOrdenados ) );
	if ( ES_VALIDO ( p_ficObj ) )
	{
		p_ficObj->p_ficObj = SFicBloqIdAsignarExt ( p_cDir, p_cFic, iNumMagico );
		if ( ES_VALIDO ( p_ficObj->p_ficObj ) )
		{
			if ( _SFicBloqOrdCargarInfoCabecera ( p_ficObj ) == 1 )
			{
				p_ficObj->ulActual = p_ficObj->ulPrimero;
				p_ficObj->ulPosActual = 0;
			}
			else
			{
				SFicBloqOrdDestruir ( &p_ficObj );
			}
		}
	}
	else
	{
		p_ficObj = NULL;
	}
	return ( p_ficObj );
}

SFicBloquesOrdenados * SFicBloqOrdCrearRuta ( SRuta * p_rutRuta, unsigned long ulTamDatosBloque, unsigned long ulTamDatosCab )
{
	SFicBloquesOrdenados *	p_ficObj;
	char *					p_cRuta;
	
	if ( SRutEsValida ( p_rutRuta ) == 1 )
	{
		if ( SRutEsFichero ( p_rutRuta ) == 1 )
		{
			p_cRuta = SRutRutaAbsolutaLit ( p_rutRuta );
			if ( SRutExiste ( p_rutRuta ) == 1 )
			{
				p_ficObj = SFicBloqOrdAsignar ( p_cRuta );
			}
			else
			{
				p_ficObj = SFicBloqOrdCrear ( p_cRuta, ulTamDatosBloque, ulTamDatosCab );
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


void SFicBloqOrdDestruir ( SFicBloquesOrdenados ** p_p_ficObj )
{
	SFicBloquesOrdenados * p_ficObj;
	
	if ( ES_VALIDO ( p_p_ficObj ) )
	{
		p_ficObj = *p_p_ficObj;

		if ( ES_VALIDO ( p_ficObj ) )
		{
			SFicBloqIdDestruir ( &(p_ficObj->p_ficObj) );
			MemLiberar ( (void **) p_p_ficObj );
		}
	}
}

void SFicBloqOrdEliminar ( SFicBloquesOrdenados ** p_p_ficObj )
{
	SFicBloquesOrdenados * p_ficObj;
	
	if ( ES_VALIDO ( p_p_ficObj ) )
	{
		p_ficObj = *p_p_ficObj;

		if ( ES_VALIDO ( p_ficObj ) )
		{
			SFicBloqIdEliminar ( &(p_ficObj->p_ficObj) );
			SFicBloqOrdDestruir ( p_p_ficObj );
		}
	}
}

int SFicBloqOrdEsValido ( SFicBloquesOrdenados * p_ficObj )
{
	int iRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		iRes = SFicBloqIdEsValido ( p_ficObj->p_ficObj );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

const char * SFicBloqOrdRuta ( SFicBloquesOrdenados * p_ficObj )
{
	const char * p_cRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		p_cRes = SFicBloqIdRuta ( p_ficObj->p_ficObj );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

char * SFicBloqOrdDirectorio ( SFicBloquesOrdenados * p_ficObj ) 
{
	char * p_cRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		p_cRes = SFicBloqIdDirectorio ( p_ficObj->p_ficObj );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

char * SFicBloqOrdFichero ( SFicBloquesOrdenados * p_ficObj )
{
	char * p_cRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		p_cRes = SFicBloqIdFichero ( p_ficObj->p_ficObj );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

int SFicBloqOrdEstablecerRuta ( SFicBloquesOrdenados * p_ficObj, const char * p_cRuta )
{
	int iRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		iRes = SFicBloqIdEstablecerRuta ( p_ficObj->p_ficObj, p_cRuta );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SFicBloqOrdEstablecerRutaExt ( SFicBloquesOrdenados * p_ficObj, const char * p_cDir, const char * p_cFic )
{
	int iRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		iRes = SFicBloqIdEstablecerRutaExt ( p_ficObj->p_ficObj, p_cDir, p_cFic );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

unsigned long SFicBloqOrdNumeroMagico ( SFicBloquesOrdenados * p_ficObj )
{
	unsigned long ulRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		ulRes = SFicBloqIdNumeroMagico ( p_ficObj->p_ficObj );
	}
	else
	{
		ulRes = 0;
	}
	return ( ulRes );
}

int SFicBloqOrdEstablecerNumeroMagico ( SFicBloquesOrdenados * p_ficObj, unsigned long ulNumero )
{
	int iRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		iRes = SFicBloqIdEstablecerNumeroMagico (  p_ficObj->p_ficObj, ulNumero );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

unsigned long SFicBloqOrdTamDatosCabecera ( SFicBloquesOrdenados * p_ficObj )
{
	unsigned long ulRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		ulRes = SFicBloqIdTamDatosCabecera ( p_ficObj->p_ficObj ) - FIC_BLOQORD_TAM_INFO_CABECERA;
	}
	else
	{
		ulRes = 0;
	}
	return ( ulRes );
}

int SFicBloqOrdEstablecerTamDatosCabecera ( SFicBloquesOrdenados * p_ficObj, unsigned long ulTam )
{
	int iRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		iRes = SFicBloqIdEstablecerTamDatosCabecera ( p_ficObj->p_ficObj, ulTam + FIC_BLOQORD_TAM_INFO_CABECERA );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

unsigned long SFicBloqOrdTamBloque ( SFicBloquesOrdenados * p_ficObj )
{
	unsigned long ulRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		ulRes = SFicBloqIdTamBloque ( p_ficObj->p_ficObj );
	}
	else
	{
		ulRes = 0;
	}
	return ( ulRes );
}

unsigned long SFicBloqOrdTamDatosBloque ( SFicBloquesOrdenados * p_ficObj )
{
	unsigned long ulRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		ulRes = SFicBloqIdTamBloque ( p_ficObj->p_ficObj ) - FIC_BLOQORD_TAM_PUNTEROS;
	}
	else
	{
		ulRes = 0;
	}
	return ( ulRes );
}

int SFicBloqOrdEstablecerTamDatosBloque ( SFicBloquesOrdenados * p_ficObj, unsigned long ulTam )
{
	int iRes;

	if ( ES_VALIDO ( p_ficObj ) && ( ulTam > 0 ) )
	{
		iRes = SFicBloqIdEstablecerTamDatosBloque ( p_ficObj->p_ficObj, ulTam + FIC_BLOQORD_TAM_PUNTEROS );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SFicBloqOrdAbrir ( SFicBloquesOrdenados * p_ficObj )
{
	return ( SFicBloqOrdAbrirExt ( p_ficObj, 0 ) );
}

int SFicBloqOrdAbrirExt ( SFicBloquesOrdenados * p_ficObj, int iVaciar )
{
	int	iRes;

	if ( SFicBloqOrdEsValido ( p_ficObj ) == 1 )
	{
		if ( SFicBloqIdAbrirExt ( p_ficObj->p_ficObj, iVaciar ) == 1 )
		{
			if ( iVaciar == 1 )
			{
				p_ficObj->ulPrimero = 0;
				p_ficObj->ulUltimo = 0;
				p_ficObj->ulActual = 0;
				p_ficObj->ulPosActual = 0;
				iRes = _SFicBloqOrdActualizarInfoCabecera ( p_ficObj );
			}
			else
			{
				iRes = _SFicBloqOrdCargarInfoCabecera ( p_ficObj );
				p_ficObj->ulActual = p_ficObj->ulPrimero;
				p_ficObj->ulPosActual = 0;
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

int SFicBloqOrdCerrar ( SFicBloquesOrdenados * p_ficObj )
{
	int iRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		iRes = SFicBloqIdCerrar ( p_ficObj->p_ficObj );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SFicBloqOrdEstaAbierto ( SFicBloquesOrdenados * p_ficObj )
{
	int iRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		iRes = SFicBloqIdEstaAbierto ( p_ficObj->p_ficObj );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

unsigned long SFicBloqOrdMinId ( SFicBloquesOrdenados * p_ficObj )
{
	unsigned long  ulRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		ulRes = SFicBloqIdMinId ( p_ficObj->p_ficObj );
	}
	else
	{
		ulRes = 0;
	}
	return ( ulRes );
}

unsigned long SFicBloqOrdMaxId ( SFicBloquesOrdenados * p_ficObj )
{
	unsigned long  ulRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		ulRes = SFicBloqIdMaxId ( p_ficObj->p_ficObj );
	}
	else
	{
		ulRes = 0;
	}
	return ( ulRes );
}

unsigned long SFicBloqOrdTam  ( SFicBloquesOrdenados * p_ficObj )
{
	unsigned long  ulRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		ulRes = SFicBloqIdTam  ( p_ficObj->p_ficObj );
	}
	else
	{
		ulRes = 0;
	}
	return ( ulRes );
}

unsigned long SFicBloqOrdTamDatos  ( SFicBloquesOrdenados * p_ficObj )
{
	unsigned long  ulRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		ulRes = SFicBloqIdNumBloques ( p_ficObj->p_ficObj ) * SFicBloqIdTamBloque ( p_ficObj->p_ficObj );
	}
	else
	{
		ulRes = 0;
	}
	return ( ulRes );
}

unsigned long SFicBloqOrdNumBloques  ( SFicBloquesOrdenados * p_ficObj )
{
	unsigned long  ulRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		ulRes = SFicBloqIdNumBloques ( p_ficObj->p_ficObj );
	}
	else
	{
		ulRes = 0;
	}
	return ( ulRes );
}

int SFicBloqOrdEstaVacio ( SFicBloquesOrdenados * p_ficObj )
{
	int iRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		if ( SFicBloqIdEstaVacio ( p_ficObj->p_ficObj ) == 1 )
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

byte * SFicBloqOrdLeerDatosCabecera ( SFicBloquesOrdenados * p_ficObj )
{
	unsigned long	ulTam;
	byte *			p_byContenido;
	byte *			p_byCabecera;	

	ulTam = SFicBloqOrdTamDatosCabecera ( p_ficObj ); 
	if (  ulTam > 0 )
	{
		p_byCabecera = SFicBloqIdLeerDatosCabecera ( p_ficObj->p_ficObj );
		if ( ES_VALIDO ( p_byCabecera ) )
		{
			p_byContenido = (byte *) MemReservar ( ulTam );
			if ( ES_VALIDO ( p_byContenido ) )
			{
				MemCopiar ( p_byContenido, &(p_byCabecera [ FIC_BLOQORD_TAM_INFO_CABECERA ]), ulTam ); 
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

int SFicBloqOrdEscribirDatosCabecera ( SFicBloquesOrdenados * p_ficObj, byte * p_byContenido )
{
	int				iRes;
	unsigned long	ulTam;
	byte *			p_byCabecera;	

	ulTam = SFicBloqOrdTamDatosCabecera ( p_ficObj ); 
	if (  ( ulTam > 0 ) && ES_VALIDO ( p_byContenido ) )
	{
		p_byCabecera = SFicBloqIdLeerDatosCabecera ( p_ficObj->p_ficObj );
		if ( ES_VALIDO ( p_byCabecera ) )
		{
			MemCopiar ( &(p_byCabecera [ FIC_BLOQORD_TAM_INFO_CABECERA ]), p_byContenido, ulTam ); 
			if ( SFicBloqIdEscribirDatosCabecera ( p_ficObj->p_ficObj, p_byCabecera ) == 1 )
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

int SFicBloqOrdMoverAPrimero ( SFicBloquesOrdenados * p_ficObj )
{
	int iRes;

	if ( ( SFicBloqIdEstaAbierto ( p_ficObj->p_ficObj ) == 1 ) && ( SFicBloqIdEstaVacio ( p_ficObj->p_ficObj ) == 0 ) )
	{
		p_ficObj->ulActual = p_ficObj->ulPrimero;
		p_ficObj->ulPosActual = 0;
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SFicBloqOrdMoverAUltimo ( SFicBloquesOrdenados * p_ficObj )
{
	int iRes;

	if ( ( SFicBloqIdEstaAbierto ( p_ficObj->p_ficObj ) == 1 ) && ( SFicBloqIdEstaVacio ( p_ficObj->p_ficObj ) == 0 ) )
	{
		p_ficObj->ulActual = p_ficObj->ulUltimo;
		p_ficObj->ulPosActual = SFicBloqIdNumBloques ( p_ficObj->p_ficObj ) - 1;
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SFicBloqOrdMoverASiguiente ( SFicBloquesOrdenados * p_ficObj )
{
	int				iRes;
	unsigned long	ulAnt;
	unsigned long	ulSig;

	if ( ( SFicBloqIdEstaAbierto ( p_ficObj->p_ficObj ) == 1 ) && ( SFicBloqIdEstaVacio ( p_ficObj->p_ficObj ) == 0 ) )
	{
		if ( p_ficObj->ulActual != p_ficObj->ulUltimo )
		{
			if ( _SFicBloqOrdLeerPunteros ( p_ficObj, p_ficObj->ulActual, &ulAnt, &ulSig ) == 1 )
			{	
				p_ficObj->ulActual = ulSig;
				p_ficObj->ulPosActual = p_ficObj->ulPosActual + 1;
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

int SFicBloqOrdMoverAAnterior ( SFicBloquesOrdenados * p_ficObj )
{
	int				iRes;
	unsigned long	ulAnt;
	unsigned long	ulSig;

	if ( ( SFicBloqIdEstaAbierto ( p_ficObj->p_ficObj ) == 1 ) && ( SFicBloqIdEstaVacio ( p_ficObj->p_ficObj ) == 0 ) )
	{
		if ( p_ficObj->ulActual != p_ficObj->ulPrimero )
		{
			if ( _SFicBloqOrdLeerPunteros ( p_ficObj, p_ficObj->ulActual, &ulAnt, &ulSig ) == 1 )
			{	
				p_ficObj->ulActual = ulAnt;
				p_ficObj->ulPosActual = p_ficObj->ulPosActual - 1;
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

int SFicBloqOrdMoverAId ( SFicBloquesOrdenados * p_ficObj, unsigned long ulId )
{
	int				iEnc;
	int				iRes;
	unsigned long	ulIdAct;

	if ( ( SFicBloqIdEstaAbierto ( p_ficObj->p_ficObj ) == 1 ) && ( SFicBloqIdEstaVacio ( p_ficObj->p_ficObj ) == 0 ) )
	{
		SFicBloqOrdMoverAPrimero ( p_ficObj );
		iEnc = 0;
		iRes = 0;
		while ( ( SFicBloqOrdEstaEnFinal ( p_ficObj ) == 0 ) && ( iEnc == 0 ) )
		{
			ulIdAct = SFicBloqOrdLeerId ( p_ficObj );
			if ( ulIdAct == ulId )
			{
				iEnc = 1;
				iRes = 1;
			}
			else if ( ulIdAct > ulId )
			{
				iEnc = 1;
			}
			else
			{
				SFicBloqOrdMoverASiguiente ( p_ficObj );
			}
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}


int SFicBloqOrdEstaEnInicio ( SFicBloquesOrdenados * p_ficObj )
{
	int iRes;

	if ( ( SFicBloqIdEstaAbierto ( p_ficObj->p_ficObj ) == 1 ) && ( SFicBloqIdEstaVacio ( p_ficObj->p_ficObj ) == 0 ) )
	{
		if ( p_ficObj->ulActual == p_ficObj->ulPrimero )
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

int SFicBloqOrdEstaEnFinal ( SFicBloquesOrdenados * p_ficObj )
{
	int iRes;

	if ( ( SFicBloqIdEstaAbierto ( p_ficObj->p_ficObj ) == 1 ) && ( SFicBloqIdEstaVacio ( p_ficObj->p_ficObj ) == 0 ) )
	{
		if ( p_ficObj->ulActual == p_ficObj->ulUltimo )
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

int SFicBloqOrdEstaPosicionado ( SFicBloquesOrdenados * p_ficObj )
{
	int iRes;

	if ( ( SFicBloqIdEstaAbierto ( p_ficObj->p_ficObj ) == 1 ) && ( SFicBloqIdEstaVacio ( p_ficObj->p_ficObj ) == 0 ) &&
		 ( p_ficObj->ulPosActual < SFicBloqIdNumBloques ( p_ficObj->p_ficObj ) ) )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

unsigned long  SFicBloqOrdActual ( SFicBloquesOrdenados * p_ficObj )
{
	unsigned long	ulRes;

	if ( SFicBloqOrdEstaPosicionado ( p_ficObj ) == 1 )
	{
		ulRes = p_ficObj->ulPosActual;
	}
	else
	{
		ulRes = 0;
	}
	return ( ulRes );
}

unsigned long SFicBloqOrdLeerId ( SFicBloquesOrdenados * p_ficObj )
{
	unsigned long	ulId;
	unsigned long	ulBloque;

	if ( SFicBloqOrdEstaPosicionado ( p_ficObj ) == 1 )
	{
		ulBloque = SFicBloqIdBloqueId ( p_ficObj->p_ficObj, p_ficObj->ulActual );
		ulId = SFicBloqIdLeerId ( p_ficObj->p_ficObj, ulBloque );
	}
	else
	{
		ulId = 0;
	}
	return ( ulId );
}

int SFicBloqOrdExisteId ( SFicBloquesOrdenados * p_ficObj, unsigned long ulId )
{
	unsigned long	ulBloque;			
	unsigned long	ulIdBloq;
	unsigned long	ulAnt;
	unsigned long	ulSig;
	int				iEnc;
	int				iFin;
	int				iError;
	int				iRes;

	if ( ES_VALIDO ( p_ficObj ) && ( ulId != FIC_BLOQID_IDNULO ) )
	{
		if ( ( SFicBloqIdEstaAbierto ( p_ficObj->p_ficObj ) == 1 ) && ( SFicBloqIdEstaVacio ( p_ficObj->p_ficObj ) == 0 ) )
		{
			if ( ( ulId == SFicBloqIdMinId ( p_ficObj->p_ficObj ) ) || ( ulId == SFicBloqIdMaxId ( p_ficObj->p_ficObj ) ) )
			{
				iRes = 1;
			}
			else if ( ( ulId > SFicBloqIdMinId ( p_ficObj->p_ficObj ) ) && ( ulId < SFicBloqIdMaxId ( p_ficObj->p_ficObj ) ) )
			{
				iEnc = 0;
				iFin = 0;
				iError = 0;
				ulBloque = p_ficObj->ulPrimero;
				while ( ( iEnc == 0 ) && ( iFin == 0 ) && ( iError == 0 ) && ( ulBloque <= p_ficObj->ulUltimo ) )
				{
					ulIdBloq = SFicBloqIdLeerId ( p_ficObj->p_ficObj, ulBloque );
					if ( ulIdBloq == ulId )
					{
						iEnc = 1;
					}
					else if ( ulIdBloq > ulId )
					{
						iFin = 1;
					}
					else
					{
						if ( _SFicBloqOrdLeerPunteros ( p_ficObj, ulBloque, &ulAnt, &ulSig ) == 1 )
						{	
							ulBloque = ulSig;
							iRes = 1;
						}
						else
						{
							iError = 1;
						}
					}
				}

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
	return ( iRes );
}

byte * SFicBloqOrdLeer ( SFicBloquesOrdenados * p_ficObj )
{
	int				iTamCont;
	byte *			p_byBloque;
	byte *			p_byContenido;

	if ( SFicBloqOrdEstaPosicionado ( p_ficObj ) == 1 )
	{
		p_byBloque = SFicBloqIdLeer ( p_ficObj->p_ficObj, p_ficObj->ulActual );
		if ( ES_VALIDO ( p_byBloque ) )
		{
			iTamCont = SFicBloqIdTamBloque ( p_ficObj->p_ficObj ) - FIC_BLOQORD_TAM_PUNTEROS;
			p_byContenido = (byte *) MemReservar ( iTamCont );
			if ( ES_VALIDO ( p_byContenido ) )
			{
				MemCopiar ( p_byContenido, &(p_byBloque [ FIC_BLOQORD_POS_CONTENIDO_BLOQUE ]), iTamCont );
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

int SFicBloqOrdLeerExt ( SFicBloquesOrdenados * p_ficObj, byte * p_byContenido )
{
	int				iRes;
	int				iTamCont;
	byte *			p_byBloque;

	if ( ( SFicBloqOrdEstaPosicionado ( p_ficObj ) == 1 ) && ES_VALIDO ( p_byContenido ) )
	{
		p_byBloque = SFicBloqIdLeer ( p_ficObj->p_ficObj, p_ficObj->ulActual );
		if ( ES_VALIDO ( p_byBloque ) )
		{
			iTamCont = SFicBloqIdTamBloque ( p_ficObj->p_ficObj ) - FIC_BLOQORD_TAM_PUNTEROS;
			MemCopiar ( p_byContenido, &(p_byBloque [ FIC_BLOQORD_POS_CONTENIDO_BLOQUE ]), iTamCont );
			MemLiberar ( (void **) &p_byBloque );
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

int SFicBloqOrdModificar ( SFicBloquesOrdenados * p_ficObj, byte * p_byContenido )
{
	int				iRes;
	int				iTamCont;
	byte *			p_byBloque;

	if ( ( SFicBloqOrdEstaPosicionado ( p_ficObj ) == 1 ) && ES_VALIDO ( p_byContenido ) )
	{
		p_byBloque = SFicBloqIdLeer ( p_ficObj->p_ficObj, p_ficObj->ulActual );
		if ( ES_VALIDO ( p_byBloque ) )
		{
			iTamCont = SFicBloqIdTamBloque ( p_ficObj->p_ficObj ) - FIC_BLOQORD_TAM_PUNTEROS;
			MemCopiar ( &(p_byBloque [ FIC_BLOQORD_POS_CONTENIDO_BLOQUE ]), p_byContenido, iTamCont );
			iRes = SFicBloqIdEscribirBloque ( p_ficObj->p_ficObj, p_ficObj->ulActual, p_byBloque );
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

int SFicBloqOrdInsertar ( SFicBloquesOrdenados * p_ficObj, unsigned long ulId, byte * p_byContenido, int iDelante )
{
	int				iRes;
	byte *			p_byBloque;
	byte *			p_byBloqueAct;
	unsigned long	ulAnt;
	unsigned long	ulSig;
	int				iTamCont;
	int				iTamBloq;

	if ( ( SFicBloqOrdEstaAbierto ( p_ficObj ) == 1 ) && ES_VALIDO ( p_byContenido ) )
	{
		if ( SFicBloqIdExisteId ( p_ficObj->p_ficObj, ulId ) == 0 )
		{
			iTamBloq = SFicBloqIdTamBloque ( p_ficObj->p_ficObj );
			iTamCont = iTamBloq - FIC_BLOQORD_TAM_PUNTEROS;
			p_byBloque = (byte *) MemReservar ( iTamBloq );
			if ( ES_VALIDO ( p_byBloque ) )
			{
				MemCopiar ( &(p_byBloque [ FIC_BLOQORD_POS_CONTENIDO_BLOQUE ]), p_byContenido, iTamCont );

				if ( SFicBloqOrdNumBloques ( p_ficObj ) == 0 )
				{
					/* Caso inicial: */
					if ( SFicBloqIdInsertar ( p_ficObj->p_ficObj, ulId, p_byBloque ) == 1 )
					{
						p_ficObj->ulActual = ulId;
						p_ficObj->ulPrimero = ulId;
						p_ficObj->ulUltimo = ulId;
						iRes = _SFicBloqOrdActualizarInfoCabecera ( p_ficObj );
					}
					else
					{
						iRes = 0;
					}
				}
				else if ( SFicBloqOrdEstaPosicionado ( p_ficObj ) == 1 ) 
				{
					p_byBloqueAct = SFicBloqIdLeer ( p_ficObj->p_ficObj, p_ficObj->ulActual );
					if ( ES_VALIDO ( p_byBloqueAct ) )
					{
						MemCopiar ( &ulAnt, &(p_byBloqueAct [ FIC_BLOQORD_POS_ANT_BLOQUE ]), sizeof ( unsigned long ) ); 
						MemCopiar ( &ulSig, &(p_byBloqueAct [ FIC_BLOQORD_POS_SIG_BLOQUE ]), sizeof ( unsigned long ) );
						if ( iDelante == 1 )
						{
							MemCopiar ( &(p_byBloque [ FIC_BLOQORD_POS_ANT_BLOQUE ]), &ulAnt, sizeof ( unsigned long ) ); 
							MemCopiar ( &(p_byBloque [ FIC_BLOQORD_POS_SIG_BLOQUE ]), &(p_ficObj->ulActual), sizeof ( unsigned long ) );
							MemCopiar ( &(p_byBloqueAct [ FIC_BLOQORD_POS_ANT_BLOQUE ]), &ulId, sizeof ( unsigned long ) ); 
						}
						else
						{
							MemCopiar ( &(p_byBloque [ FIC_BLOQORD_POS_ANT_BLOQUE ]), &(p_ficObj->ulActual), sizeof ( unsigned long ) ); 
							MemCopiar ( &(p_byBloque [ FIC_BLOQORD_POS_SIG_BLOQUE ]), &ulSig, sizeof ( unsigned long ) );
							MemCopiar ( &(p_byBloqueAct [ FIC_BLOQORD_POS_SIG_BLOQUE ]), &ulId, sizeof ( unsigned long ) ); 
						}
						if ( SFicBloqIdModificar ( p_ficObj->p_ficObj, p_ficObj->ulActual, p_byBloqueAct ) == 1 )
						{
							if ( SFicBloqIdInsertar ( p_ficObj->p_ficObj, ulId, p_byBloque ) == 1 )
							{
								if ( p_ficObj->ulUltimo == p_ficObj->ulActual )
								{
									p_ficObj->ulUltimo = ulId;
									iRes = _SFicBloqOrdActualizarInfoCabecera ( p_ficObj );
								} 
								else 
								{
									iRes = 1;
								}
								p_ficObj->ulActual = ulId;
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
						MemLiberar ( (void **) &p_byBloqueAct );
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

int SFicBloqOrdInsertarDetras ( SFicBloquesOrdenados * p_ficObj, unsigned long ulId, byte * p_byContenido )
{
	return ( SFicBloqOrdInsertar ( p_ficObj, ulId, p_byContenido, 0 ) );
}

int SFicBloqOrdInsertarDelante ( SFicBloquesOrdenados * p_ficObj, unsigned long ulId, byte * p_byContenido )
{
	return ( SFicBloqOrdInsertar ( p_ficObj, ulId, p_byContenido, 0 ) );
}

int SFicBloqOrdSuprimir ( SFicBloquesOrdenados * p_ficObj )
{
	int				iRes;
	byte *			p_byBloqueAnt;
	byte *			p_byBloqueSig;
	byte *			p_byBloqueAct;
	unsigned long	ulAnt;
	unsigned long	ulSig;

	if ( SFicBloqOrdEstaPosicionado ( p_ficObj ) == 1 ) 
	{
		p_byBloqueAct = SFicBloqIdLeer ( p_ficObj->p_ficObj, p_ficObj->ulActual );
		if ( ES_VALIDO ( p_byBloqueAct ) )
		{
			MemCopiar ( &ulAnt, &(p_byBloqueAct [ FIC_BLOQORD_POS_ANT_BLOQUE ]), sizeof ( unsigned long ) ); 
			MemCopiar ( &ulSig, &(p_byBloqueAct [ FIC_BLOQORD_POS_SIG_BLOQUE ]), sizeof ( unsigned long ) );

			if ( ulAnt > 0 )
			{
				p_byBloqueAnt = SFicBloqIdLeer ( p_ficObj->p_ficObj, ulAnt );
				if ( ES_VALIDO ( p_byBloqueAnt ) )
				{
					MemCopiar ( &(p_byBloqueAnt [ FIC_BLOQORD_POS_SIG_BLOQUE ]), &ulSig, sizeof ( unsigned long ) ); 
					iRes = SFicBloqIdModificar ( p_ficObj->p_ficObj, ulAnt, p_byBloqueAnt );
					MemLiberar ( (void **) &p_byBloqueAnt );
				}
				else
				{
					iRes = 0;
				}
			}
			else
			{
				p_ficObj->ulPrimero = ulSig;
				iRes = _SFicBloqOrdActualizarInfoCabecera ( p_ficObj );
			}

			if ( iRes == 1 )
			{
				if ( ulSig > 0 ) 
				{
					p_byBloqueSig = SFicBloqIdLeer ( p_ficObj->p_ficObj, ulSig );
					if ( ES_VALIDO ( p_byBloqueSig ) )
					{
						MemCopiar ( &(p_byBloqueSig [ FIC_BLOQORD_POS_ANT_BLOQUE ]), &ulAnt, sizeof ( unsigned long ) ); 
						iRes = SFicBloqIdModificar ( p_ficObj->p_ficObj, ulSig, p_byBloqueSig );
						MemLiberar ( (void **) &p_byBloqueSig );
					}
					else
					{
						iRes = 0;
					}
				}
				else
				{
					p_ficObj->ulUltimo = ulAnt;
					iRes = _SFicBloqOrdActualizarInfoCabecera ( p_ficObj );
				}
			}
			if ( iRes == 1 )
			{
				if ( SFicBloqIdSuprimir ( p_ficObj->p_ficObj, p_ficObj->ulActual ) == 1 )
				{
					if ( ulSig > 0 )
					{
						p_ficObj->ulActual = ulSig;
					}
					else
					{
						p_ficObj->ulActual = ulAnt;
					}
				}
				else
				{
					iRes = 0;
				}
			}

			MemLiberar ( (void **) &p_byBloqueAct );
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

byte * SFicBloqOrdLeerPorId ( SFicBloquesOrdenados * p_ficObj, unsigned long ulId )
{
	byte * p_byContenido;

	if ( SFicBloqOrdMoverAId ( p_ficObj, ulId ) == 1 )
	{
		p_byContenido = SFicBloqOrdLeer ( p_ficObj );
	}
	else
	{
		p_byContenido = NULL;
	}
	return ( p_byContenido );
}

int SFicBloqOrdLeerPorIdExt ( SFicBloquesOrdenados * p_ficObj, unsigned long ulId, byte * p_byContenido )
{
	int	iRes;

	if ( SFicBloqOrdMoverAId ( p_ficObj, ulId ) == 1 )
	{
		iRes = SFicBloqOrdLeerExt ( p_ficObj, p_byContenido );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SFicBloqOrdModificarPorId ( SFicBloquesOrdenados * p_ficObj, unsigned long ulId, byte * p_byContenido )
{
	int	iRes;

	if ( SFicBloqOrdMoverAId ( p_ficObj, ulId ) == 1 )
	{
		iRes = SFicBloqOrdModificar ( p_ficObj, p_byContenido );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int _SFicBloqOrdActualizarInfoCabecera ( SFicBloquesOrdenados * p_ficObj )
{
	int		iRes;
	byte *	p_byCabecera;	

	if ( ES_VALIDO ( p_ficObj ) )
	{
		p_byCabecera = SFicBloqIdLeerDatosCabecera ( p_ficObj->p_ficObj );
		if ( ES_VALIDO ( p_byCabecera ) )
		{
			MemCopiar ( &(p_byCabecera [ FIC_BLOQORD_POS_PRIMERO ]), &(p_ficObj->ulPrimero), sizeof ( unsigned long ) ); 
			MemCopiar ( &(p_byCabecera [ FIC_BLOQORD_POS_ULTIMO ]), &(p_ficObj->ulUltimo), sizeof ( unsigned long ) );

			iRes = SFicBloqIdEscribirDatosCabecera ( p_ficObj->p_ficObj, p_byCabecera );
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

int _SFicBloqOrdCargarInfoCabecera ( SFicBloquesOrdenados * p_ficObj )
{
	int		iRes;
	byte *	p_byCabecera;	

	if ( ES_VALIDO ( p_ficObj ) )
	{
		p_byCabecera = SFicBloqIdLeerDatosCabecera ( p_ficObj->p_ficObj );
		if ( ES_VALIDO ( p_byCabecera ) )
		{
			MemCopiar ( &(p_ficObj->ulPrimero), &(p_byCabecera [ FIC_BLOQORD_POS_PRIMERO ]), sizeof ( unsigned long ) ); 
			MemCopiar ( &(p_ficObj->ulUltimo), &(p_byCabecera [ FIC_BLOQORD_POS_ULTIMO ]), sizeof ( unsigned long ) );

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

int _SFicBloqOrdLeerPunteros ( SFicBloquesOrdenados * p_ficObj, unsigned long ulBloque, unsigned long * p_ulAnt, unsigned long * p_ulSig )
{
	int		iRes;
	byte *	p_byBloque;	

	if ( ES_VALIDO ( p_ficObj ) && ES_VALIDO ( p_ulAnt ) && ES_VALIDO ( p_ulSig ) )
	{
		p_byBloque = SFicBloqIdLeer ( p_ficObj->p_ficObj, ulBloque );
		if ( ES_VALIDO ( p_byBloque ) )
		{
			MemCopiar ( p_ulAnt, &(p_byBloque [ FIC_BLOQORD_POS_ANT_BLOQUE ]), sizeof ( unsigned long ) ); 
			MemCopiar ( p_ulSig, &(p_byBloque [ FIC_BLOQORD_POS_SIG_BLOQUE ]), sizeof ( unsigned long ) );

			MemLiberar ( (void **) &p_byBloque );
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
