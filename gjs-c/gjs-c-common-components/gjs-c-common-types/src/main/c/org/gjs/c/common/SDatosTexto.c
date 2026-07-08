

#include "SDatosTexto.h"

#include "TiposDatosConfig.h"
#include <TiposBasicosConstantes.h>

static void SDatTxtVerificarTam ( SDatosTexto * p_datObj, int iTamReq );


SDatosTexto * SDatTxtCrearDef ()
{
	return ( SDatTxtCrear ( 0, 0 ) );
}

SDatosTexto * SDatTxtCrear ( int iTam, int iTamFijo )
{
	SDatosTexto * p_datObj;
	
	if ( iTam > 0 )
	{
		p_datObj = (SDatosTexto *) MemReservar ( sizeof ( SDatosTexto ) );
		if ( ES_VALIDO ( p_datObj ) )
		{
			p_datObj->p_datTexto = SDatCrear ( iTam );
			if ( iTamFijo == 1 )
			{
				p_datObj->iTamFijo = 1;
			}
			else
			{
				p_datObj->iTamFijo = 0;
			}
			p_datObj->iPos = 0;
			p_datObj->iPrimerLibre = 0;
		}
	}
	else
	{
		p_datObj = NULL;
	}
	return ( p_datObj );
}

SDatosTexto * SDatTxtEncapsular ( SDatos * p_datTexto, int iTamFijo )
{
	SDatosTexto * p_datObj;
	
    if ( ES_VALIDO ( p_datTexto ) )
    {
		p_datObj = (SDatosTexto *) MemReservar ( sizeof ( SDatosTexto ) );
		if ( ES_VALIDO ( p_datObj ) )
		{
			p_datObj->p_datTexto = p_datTexto;
			if ( iTamFijo == 1 )
			{
				p_datObj->iTamFijo = 1;
			}
			else
			{
				p_datObj->iTamFijo = 0;
			}
			p_datObj->iPos = 0;
			p_datObj->iPrimerLibre = SDatPosicionPrimerNulo ( p_datObj->p_datTexto );
		}
	}
	else
	{
		p_datObj = NULL;
	}
	return ( p_datObj );
}
	
void SDatTxtDesturir ( SDatosTexto ** p_p_datObj )
{
    SDatosTexto *  p_datObj;
    
    if ( ES_VALIDO ( p_p_datObj ) )
    {
        p_datObj = *p_p_datObj;
		if ( ES_VALIDO ( p_datObj ) )
		{
			SDatDestruir ( &(p_datObj->p_datTexto) );
			MemLiberar ( (void **) p_p_datObj );
		}
    }    
}

int SDatTxtEstablecerTam ( SDatosTexto * p_datObj, int iTam )
{
	int		iRes;

	if ( ES_VALIDO ( p_datObj ) )
	{
		if ( ( p_datObj->iTamFijo == 0 ) || ( SDatTam ( p_datObj->p_datTexto ) == 0 ) )
		{
			if ( iTam < 0 )
			{
				iTam = 0;
			}
			if ( iTam > SDatTam ( p_datObj->p_datTexto ) ) 
			{
				SDatRedimensionar ( p_datObj->p_datTexto, iTam, 1 );
			}
			else if ( iTam > p_datObj->iPrimerLibre )
			{
				SDatRedimensionar ( p_datObj->p_datTexto, iTam, 1 );
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

int SDatTxtEsDeTamFijo ( SDatosTexto * p_datObj )
{
	int		iRes;

	if ( ES_VALIDO ( p_datObj ) )
	{
		iRes = p_datObj->iTamFijo;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

void SDatTxtActivarTamFijo ( SDatosTexto * p_datObj )
{
	if ( ES_VALIDO ( p_datObj ) )
	{
		p_datObj->iTamFijo = 1;
	}
}

void SDatTxtDesactivarTamFijo ( SDatosTexto * p_datObj )
{
	if ( ES_VALIDO ( p_datObj ) )
	{
		p_datObj->iTamFijo = 0;
	}
}

int SDatTxtEstaVacio ( SDatosTexto * p_datObj )
{
	int iRes;

	if ( ES_VALIDO ( p_datObj ) )
	{
		if ( SDatTam ( p_datObj->p_datTexto ) == 0 )
		{
			p_datObj->iPrimerLibre = 0;
			p_datObj->iPos = 0;
			iRes = 1;
		}
		else if ( p_datObj->iPrimerLibre > 0 )
		{
			iRes = 0;
		}
		else
		{
			iRes = 1;
		}
	}
	else
	{
		iRes = 1;
	}
	return ( iRes );
}

int SDatTxtEstaLleno ( SDatosTexto * p_datObj )
{
	int iRes;

	if ( ES_VALIDO ( p_datObj ) )
	{
		if ( SDatTam ( p_datObj->p_datTexto ) == 0 )
		{
			p_datObj->iPrimerLibre = 0;
			p_datObj->iPos = 0;
			iRes = 1;
		}
		else if ( p_datObj->iPrimerLibre >= SDatTam ( p_datObj->p_datTexto ) )
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

int SDatTxtEstablecerCaracterEnPos ( SDatosTexto * p_datObj, int iPos, char cVal )
{
	int		iRes;

	if ( ES_VALIDO ( p_datObj ) )
	{
		iRes = SDatEstablecerByte ( p_datObj->p_datTexto, iPos, (byte) cVal );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

char SDatTxtCaracter ( SDatosTexto * p_datObj, int iPos )
{
	char	cVal;

	if ( ES_VALIDO ( p_datObj ) )
	{
		cVal = (char) SDatByte ( p_datObj->p_datTexto, iPos );
	}
	else
	{
		cVal = (char) 0;
	}
	return ( cVal );
}

int SDatTxtAsignarContenidoLit ( SDatosTexto * p_datObj, const char * p_cTexto )
{
	int iRes;
	int iTam;
	
	if ( ES_VALIDO ( p_datObj ) )
	{
		iTam = CadLongitud ( p_cTexto ) + 1;
		iRes = SDatAsignarContenido ( p_datObj->p_datTexto, (byte *) p_cTexto, iTam );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SDatTxtAsignarContenidoEnPosLit ( SDatosTexto * p_datObj, int iPos, const char * p_cTexto )
{
	int iRes;
	int iTam;
	
	if ( ES_VALIDO ( p_datObj ) )
	{
		iTam = CadLongitud ( p_cTexto ) + 1;
		iRes = SDatAsignarContenidoEnPos ( p_datObj->p_datTexto, iPos, (byte *) p_cTexto, iTam );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SDatTxtAsignarContenido ( SDatosTexto * p_datObj, SCadena * p_cadTexto )
{
	int iRes;
	
	if ( ES_VALIDO ( p_cadTexto ) )
	{
		iRes = SDatTxtAsignarContenidoEnPos ( p_datObj, 0, p_cadTexto );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SDatTxtAsignarContenidoEnPos ( SDatosTexto * p_datObj, int iPos, SCadena * p_cadTexto )
{
	int iRes;
	
	if ( ES_VALIDO ( p_cadTexto ) )
	{
		iRes = SDatTxtAsignarContenidoEnPos ( p_datObj, iPos, p_cadTexto );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}
	
SDatos * SDatTxtDatos ( SDatosTexto * p_datObj )
{
	SDatos * p_datRes;

	if ( ES_VALIDO ( p_datObj ) )
	{
		p_datRes = p_datObj->p_datTexto;
	}
	else
	{
		p_datRes = NULL;
	}
	return ( p_datRes );
}

int SDatTxtAsignar ( SDatosTexto * p_datObj, SDatosTexto * p_datValor )
{
	int iRes;

	if ( ES_VALIDO ( p_datObj ) && ES_VALIDO ( p_datValor ) )
	{
		SDatRedimensionar ( p_datObj->p_datTexto, SDatTxtTam ( p_datValor ), 1 );
		p_datObj->iTamFijo = SDatTxtEsDeTamFijo ( p_datValor );
		if ( SDatAsignar ( p_datObj->p_datTexto, SDatTxtDatos ( p_datValor ) ) == 1 )
		{
			p_datObj->iPrimerLibre = SDatPosicionPrimerNulo ( p_datObj->p_datTexto );
			p_datObj->iPos = p_datObj->iPrimerLibre;
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

int SDatTxtAsignarDat ( SDatosTexto * p_datObj, SDatos * p_datValor )
{
	int iRes;

	if ( ES_VALIDO ( p_datObj ) && ES_VALIDO ( p_datValor ) )
	{
		if ( SDatAsignar ( p_datObj->p_datTexto, p_datValor ) == 1 )
		{
			p_datObj->iPrimerLibre = SDatPosicionPrimerNulo ( p_datObj->p_datTexto );
			p_datObj->iPos = p_datObj->iPrimerLibre;
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

SDatosTexto * SDatTxtDuplicar ( SDatosTexto * p_datObj )
{
	SDatosTexto * p_datCopia;

	if ( ES_VALIDO ( p_datObj ) )
	{
		p_datCopia = SDatTxtCrear ( SDatTam ( p_datObj->p_datTexto ), SDatTxtEsDeTamFijo ( p_datObj ) );
		if ( ES_VALIDO ( p_datCopia ) )
		{
			SDatTxtAsignar ( p_datCopia, p_datObj );
		}
	}
	else
	{
		p_datCopia = NULL;
	}
	return ( p_datCopia );
}

SDatos * SDatTxtDuplicarDatos ( SDatosTexto * p_datObj )
{
	SDatos * p_datRes;

	if ( ES_VALIDO ( p_datObj ) )
	{
		p_datRes = SDatDuplicar ( p_datObj->p_datTexto );
	}
	else
	{
		p_datRes = NULL;
	}
	return ( p_datRes );
}

int SDatTxtLongitud ( SDatosTexto * p_datObj )
{
	int iRes;
	
	if ( ES_VALIDO ( p_datObj ) )
	{
		iRes = p_datObj->iPrimerLibre;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}
	
int SDatTxtPosicion ( SDatosTexto * p_datObj )
{
	int iRes;
	
	if ( ES_VALIDO ( p_datObj ) )
	{
		iRes = p_datObj->iPos;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}
	
int SDatTxtPosicionar ( SDatosTexto * p_datObj, int iPos )
{
	int iRes;
	
	if ( ES_VALIDO ( p_datObj ) )
	{
		if ( ( iPos >= 0 ) && ( iPos < SDatTam ( p_datObj->p_datTexto ) )  && ( iPos <= p_datObj->iPrimerLibre ) )
		{
			p_datObj->iPos = iPos;
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
	
void SDatTxtPosicionarEnInicio ( SDatosTexto * p_datObj )
{
	SDatTxtPosicionar ( p_datObj, 0 );
}

void SDatTxtPosicionarEnFinal ( SDatosTexto * p_datObj )
{
	if ( ES_VALIDO ( p_datObj ) )
	{
		SDatTxtPosicionar ( p_datObj, p_datObj->iPrimerLibre );
	}
}

int SDatTxtEscribirCar ( SDatosTexto * p_datObj, char cVal )
{
	int iRes;

	if ( ES_VALIDO ( p_datObj ) )
	{
		if ( ( p_datObj->iPos >= 0 ) && ( p_datObj->iPos < SDatTam ( p_datObj->p_datTexto ) ) )
		{
			iRes = SDatEstablecerByte ( p_datObj->p_datTexto, p_datObj->iPos, (byte) cVal );
			p_datObj->iPos = p_datObj->iPos + 1;
			if ( p_datObj->iPos > p_datObj->iPrimerLibre )
			{
				p_datObj->iPrimerLibre = p_datObj->iPos;
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

int SDatTxtEscribirLit ( SDatosTexto * p_datObj, const char * p_cTexto )
{
	return ( SDatTxtAsignarContenidoLit ( p_datObj, p_cTexto ) );
}

int SDatTxtEscribir ( SDatosTexto * p_datObj, SCadena * p_cadTexto )
{
	return ( SDatTxtAsignarContenido ( p_datObj, p_cadTexto ) );
}

int SDatTxtEscribirLineaLit ( SDatosTexto * p_datObj, const char * p_cTexto )
{
	int iRes;
	
	if ( ES_VALIDO ( p_datObj ) )
	{
		if ( ES_VALIDO ( p_cTexto  ) )
		{
			if ( SDatTxtEscribirLit ( p_datObj, p_cTexto ) == 1 )
			{
				iRes = SDatTxtEscribirCar ( p_datObj, '\n' );
			}
			else
			{
				iRes = 0;
			}
		}
		else
		{
			iRes = SDatTxtEscribirCar ( p_datObj, '\n' );
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SDatTxtEscribirLinea ( SDatosTexto * p_datObj, SCadena * p_cadTexto )
{
	int iRes;
	
	if ( ES_VALIDO ( p_datObj ) )
	{
		if ( ES_VALIDO ( p_cadTexto  ) )
		{
			if ( SDatTxtEscribir ( p_datObj, p_cadTexto ) == 1 )
			{
				iRes = SDatTxtEscribirCar ( p_datObj, '\n' );
			}
			else
			{
				iRes = 0;
			}
		}
		else
		{
			iRes = SDatTxtEscribirCar ( p_datObj, '\n' );
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SDatTxtEscribirSaltoLinea ( SDatosTexto * p_datObj )
{
	return ( SDatTxtEscribirCar ( p_datObj, '\n' ) );
}

int SDatTxtEscribirEspacio ( SDatosTexto * p_datObj )
{
	return ( SDatTxtEscribirEspacios ( p_datObj, 1 ) );
}

int SDatTxtEscribirEspacios ( SDatosTexto * p_datObj, int iNum )
{
	int iEspacio;
	int iRes;

	if ( ES_VALIDO ( p_datObj ) )
	{
		iRes = 1;
		iEspacio = 0;
		while ( ( iEspacio < iNum ) && ( iRes == 1 ) )
		{
			SDatTxtEscribirCar ( p_datObj, ' ' );
			iEspacio = iEspacio + 1;
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SDatTxtTam ( SDatosTexto * p_datObj )
{
	int iRes;
	
	if ( ES_VALIDO ( p_datObj ) )
	{
		iRes = SDatTam ( p_datObj->p_datTexto );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

void SDatTxtLimpiar ( SDatosTexto * p_datObj )
{
	if ( ES_VALIDO ( p_datObj ) )
	{
		SDatLimpiar ( p_datObj->p_datTexto );
		p_datObj->iPos = 0;
		p_datObj->iPrimerLibre = 0;
	}
}

void SDatTxtLiberar ( SDatosTexto * p_datObj )
{
	if ( ES_VALIDO ( p_datObj ) )
	{
		SDatLiberar ( p_datObj->p_datTexto );
		p_datObj->iPos = 0;
		p_datObj->iPrimerLibre = 0;
	}
}

SCadena * SDatTxtContenido ( SDatosTexto * p_datObj )
{
	SCadena *	p_cadRes;
	char *		p_cBuffer;

	if ( SDatTxtEstaVacio ( p_datObj ) == 0 )
	{
		p_cBuffer = (char *) SDatContenido ( p_datObj->p_datTexto );
		if ( ES_VALIDO ( p_cBuffer ) )
		{
			p_cadRes = SCadGenerar ( p_cBuffer );
		}
		else
		{
			p_cadRes = NULL;
		}
	}
	else
	{
		p_cadRes = NULL;
	}
	return ( p_cadRes );
}

char * SDatTxtContenidoValor ( SDatosTexto * p_datObj )
{
	char *	p_cBuffer;
	
	if ( SDatTxtEstaVacio ( p_datObj ) == 0 )
	{
		p_cBuffer = (char *) SDatContenido ( p_datObj->p_datTexto );
	}
	else
	{
		p_cBuffer = NULL;
	}
	return ( p_cBuffer );
}

char * SDatTxtDuplicarContenidoValor ( SDatosTexto * p_datObj )
{
	char *	p_cBuffer;
	
	if ( SDatTxtEstaVacio ( p_datObj ) == 0 )
	{
		p_cBuffer = CadDuplicar ( (char *) SDatContenido ( p_datObj->p_datTexto ) );
	}
	else
	{
		p_cBuffer = NULL;
	}
	return ( p_cBuffer );
}

int SDatTxtNumLineas ( SDatosTexto * p_datObj )
{
	int		iNumLineas;
	int		iCar;
	char *	p_cBuffer;
	char	cVal;
	
	if ( SDatTxtEstaVacio ( p_datObj ) == 0 )
	{
		p_cBuffer = (char *) SDatContenido ( p_datObj->p_datTexto );
		if ( ES_VALIDO ( p_cBuffer ) )
		{
			iNumLineas = 0;
			for ( iCar = 0; iCar < p_datObj->iPrimerLibre; iCar = iCar + 1 )
			{
				cVal = p_cBuffer [ iCar ];
				if ( cVal == 0x0A )
				{
					iNumLineas = iNumLineas + 1;
				}
			}
			if ( ( p_datObj->iPrimerLibre > 0 ) && ( iNumLineas == 0 ) )
			{
				iNumLineas = 1;
			}
		}
		else
		{
			iNumLineas = 0;
		}
	}
	else
	{
		iNumLineas = 0;
	}
	return ( iNumLineas );
}

SCadena * SDatTxtLinea ( SDatosTexto * p_datObj, int iLinea )
{
	SCadena *	p_cadRes;
	int			iNumLineas;
	int			iCar;
	int			iCarIni;
	int			iLong;
	int			iLin;
	char *		p_cBuffer;
	char		cVal;

	iNumLineas = SDatTxtNumLineas ( p_datObj );
	if ( ( iLinea >= 0 ) && ( iLinea < iNumLineas ) )
	{
		p_cBuffer = (char *) SDatContenido ( p_datObj->p_datTexto );
		if ( ES_VALIDO ( p_cBuffer ) )
		{
			iLin = 0;
			iCar = 0;
			while ( ( iCar < p_datObj->iPrimerLibre ) && ( iLin < iLinea ) )
			{
				cVal = p_cBuffer [ iCar ];
				if ( cVal == 0x0A )
				{
					iLin = iLin + 1;
				}
				iCar = iCar + 1;
			}
			if ( iLin == iLinea )
			{
				iCarIni = iCar;
				while ( ( iCar < p_datObj->iPrimerLibre ) && ( iLin == iLinea ) )
				{
					cVal = p_cBuffer [ iCar ];
					if ( cVal == 0x0A )
					{
						iLin = iLin + 1;
					}
					iCar = iCar + 1;
				}
				iLong = iCar - iCarIni - 1;
				p_cadRes = SCadCrear ( iLong );
				if ( ES_VALIDO ( p_cadRes ) )
				{
					iCar = 0;
					while ( iCar < iLong ) 
					{
						cVal = p_cBuffer [ iCarIni + iCar ];
						SCadEstablecerCaracter ( p_cadRes, iCar, cVal );
						iCar = iCar + 1;
					}
				}
			}
			else
			{
				p_cadRes = NULL;
			}
		}
		else
		{
			p_cadRes = NULL;
		}
	}
	else
	{
		p_cadRes = NULL;
	}
	return ( p_cadRes );
}

void SDatTxtImprimir ( SDatosTexto * p_datObj )
{
	int		iCar;
	char *	p_cBuffer;
	char	cValor;

	if ( ES_VALIDO ( p_datObj ) )
	{
		printf ( "\n * Contenido del buffer de texto: \n\n" );
		if ( p_datObj->iPrimerLibre > 0 )
		{
			p_cBuffer = (char *) SDatContenido ( p_datObj->p_datTexto );
			if ( ES_VALIDO ( p_cBuffer ) )
			{
				for ( iCar = 0; iCar < p_datObj->iPrimerLibre; iCar = iCar + 1 )
				{
					cValor = p_cBuffer [ iCar ];
					printf ( "%c", cValor );
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

static void SDatTxtVerificarTam ( SDatosTexto * p_datObj, int iTamReq )
{
	int iBloques;

	if ( ES_VALIDO ( p_datObj ) )
	{
		if ( p_datObj->iTamFijo == 0 )
		{
			if ( iTamReq > SDatTam ( p_datObj->p_datTexto ) )
			{
				iBloques = 1 + ((iTamReq - SDatTam ( p_datObj->p_datTexto )) / DAT_TAM_BLOQUE_DEF);
				SDatRedimensionar ( p_datObj->p_datTexto, iTamReq + iBloques * DAT_TAM_BLOQUE_DEF, 1 );
			}
		}
	}
}




