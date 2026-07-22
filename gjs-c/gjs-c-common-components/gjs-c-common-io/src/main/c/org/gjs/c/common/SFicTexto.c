
#include "SFicTexto.h"

#include "FicherosConfig.h"



#define FIC_TXT_MAX_TAM_LINEA					511							





SFicTexto * SFicTxtCrear ( const char * p_cRuta )
{
	SFicTexto *			p_ficObj;
	SFicSecuencial *	p_ficSec; 
	
	p_ficSec = SFicSecCrear ( p_cRuta );
	if ( ES_VALIDO ( p_ficSec ) )
	{
		p_ficObj= (SFicTexto *) MemReservar ( sizeof ( SFicTexto ) );
		if ( ES_VALIDO ( p_ficObj ) )
		{
			p_ficObj->iEstilo = EST_FTXT_DOS;
			p_ficObj->p_ficObj = p_ficSec;
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

SFicTexto * SFicTxtCrearExt ( const char * p_cDir, const char * p_cFic, int iEstilo )
{
	SFicTexto *			p_ficObj;
	SFicSecuencial *	p_ficSec; 
	
	if ( EstFicTxtEsValido ( iEstilo ) == 1 )
	{
		p_ficSec = SFicSecCrearExt ( p_cDir, p_cFic );
		if ( ES_VALIDO ( p_ficSec ) )
		{
			p_ficObj= (SFicTexto *) MemReservar ( sizeof ( SFicTexto ) );
			if ( ES_VALIDO ( p_ficObj ) )
			{
				p_ficObj->iEstilo = iEstilo;
				p_ficObj->p_ficObj = p_ficSec;
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
	}
	else
	{
		p_ficObj = NULL;
	}
	return ( p_ficObj );
}

SFicTexto * SFicTxtCrearRuta ( SRuta * p_rutRuta  )
{
	SFicTexto *	p_ficObj;
	char *		p_cRuta;
	
	if ( SRutEsValida ( p_rutRuta ) == 1 )
	{
		if ( SRutEsFichero ( p_rutRuta ) == 1 )
		{
			p_cRuta = SRutRutaAbsolutaLit ( p_rutRuta );
			p_ficObj = SFicTxtCrear ( p_cRuta );
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


void SFicTxtDestruir ( SFicTexto ** p_p_ficObj )
{
	SFicTexto * p_ficObj;
	
	if ( ES_VALIDO ( p_p_ficObj ) )
	{
		p_ficObj = *p_p_ficObj;

		if ( ES_VALIDO ( p_ficObj ) )
		{
			SFicSecDestruir ( &(p_ficObj->p_ficObj) );
			MemLiberar ( (void **)p_p_ficObj );
		}
	}
}

void SFicTxtEliminar ( SFicTexto ** p_p_ficObj )
{
	SFicTexto * p_ficObj;
	
	if ( ES_VALIDO ( p_p_ficObj ) )
	{
		p_ficObj = *p_p_ficObj;

		if ( ES_VALIDO ( p_ficObj ) )
		{
			SFicSecEliminar ( &(p_ficObj->p_ficObj) );
			SFicTxtDestruir ( p_p_ficObj );
		}
	}
}

int SFicTxtEsValido ( SFicTexto * p_ficObj )
{
	int iRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		if ( ( SFicSecEsValido ( p_ficObj->p_ficObj ) == 1 ) &&
			 ( EstFicTxtEsValido ( p_ficObj->iEstilo ) == 1 ) )
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

const char * SFicTxtRuta ( SFicTexto * p_ficObj )
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

char * SFicTxtDirectorio ( SFicTexto * p_ficObj )
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

char * SFicTxtFichero ( SFicTexto * p_ficObj ) 
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

int SFicTxtEstablecerRuta ( SFicTexto * p_ficObj, const char * p_cRuta )
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

int SFicTxtEstablecerRutaExt ( SFicTexto * p_ficObj, const char * p_cDir, const char * p_cFic )
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

int SFicTxtEstilo ( SFicTexto * p_ficObj )
{
	int iRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		iRes = p_ficObj->iEstilo;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SFicTxtEsEstiloUNIX ( SFicTexto * p_ficObj )
{
	int iRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		if ( p_ficObj->iEstilo == EST_FTXT_UNIX )
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

int SFicTxtEsEstiloDOS ( SFicTexto * p_ficObj )
{
	int iRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		if ( p_ficObj->iEstilo == EST_FTXT_DOS )
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

int SFicTxtAbrir ( SFicTexto * p_ficObj, int iModo )
{
	int iRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		iRes = SFicSecAbrir ( p_ficObj->p_ficObj, iModo );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SFicTxtCerrar ( SFicTexto * p_ficObj )
{
	int iRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		iRes = SFicSecCerrar ( p_ficObj->p_ficObj );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SFicTxtEstaAbierto ( SFicTexto * p_ficObj )
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

int SFicTxtModoApertura ( SFicTexto * p_ficObj )
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

int SFicTxtEstaAbiertoParaLectura ( SFicTexto * p_ficObj )
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

int SFicTxtEstaAbiertoParaEscritura ( SFicTexto * p_ficObj )
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

int SFicTxtEstaEnFinal ( SFicTexto * p_ficObj )
{
	int iRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		iRes = SFicSecEstaEnFinal ( p_ficObj->p_ficObj );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}


char SFicTxtLeer ( SFicTexto * p_ficObj )
{
	char cRes;

	cRes = (char) 0x00;
	if ( ES_VALIDO ( p_ficObj ) )
	{
		if ( SFicSecEstaAbiertoParaLectura ( p_ficObj->p_ficObj )  == 1 ) 
		{
			cRes = (char) SFicSecLeer ( p_ficObj->p_ficObj );
		}
	}
	return ( cRes );
}

char * SFicTxtLeerLinea ( SFicTexto * p_ficObj )
{
	char	cVal;
	char *	p_cRes;
	char *	p_cAux;
	int		iCar;
	int		iFinal;
	int		iSalto;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		if ( SFicSecEstaAbiertoParaLectura ( p_ficObj->p_ficObj )  == 1 ) 
		{
			p_cAux = CadCrear ( FIC_TXT_MAX_TAM_LINEA );
			if ( ES_VALIDO ( p_cAux ) )
			{
				iFinal = 0;
				iSalto = 0;
				iCar = 0;
				while ( ( iSalto == 0 ) && ( iFinal == 0 ) && ( iCar < FIC_TXT_MAX_TAM_LINEA ) )
				{
					cVal = (char) SFicSecLeer ( p_ficObj->p_ficObj );
					if ( cVal == (char) 0x00 )
					{
						iFinal = 1;
					}
					else
					{
						if ( p_ficObj->iEstilo == EST_FTXT_UNIX )
						{
							if ( cVal == (char) 0x0A )
							{
								iSalto = 1;
							}
							else
							{
								p_cAux [ iCar ] = cVal;
								iCar = iCar + 1;
							}
						}
						else
						{
							if ( cVal == (char) 0x0D )
							{
								iSalto = 1;
							}
							else if ( cVal != (char) 0x0A )
							{
								p_cAux [ iCar ] = cVal;
								iCar = iCar + 1;
							}
						}
					}
				}

				if ( ( iFinal == 0 ) || ( iCar > 0 ) )
				{
					p_cRes = CadDuplicar ( p_cAux );
				}
				else
				{
					p_cRes = NULL;
				}
				MemLiberar ( (void **) &p_cAux );
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

int SFicTxtEscribirCaracter ( SFicTexto * p_ficObj, char cValor )
{
	int iRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		iRes = SFicSecEscribir ( p_ficObj->p_ficObj, (byte) cValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SFicTxtEscribir ( SFicTexto * p_ficObj, const char * p_cCadena )
{
	int				iRes;
	unsigned long	ulTam;

	if ( ES_VALIDO ( p_ficObj ) && ES_VALIDO ( p_cCadena ) )
	{
		ulTam = CadLongitud ( p_cCadena );
		if ( SFicSecEscribirBuffer ( p_ficObj->p_ficObj, (byte *) p_cCadena, &ulTam ) == 1 )
		{
			if ( ulTam == (unsigned long) CadLongitud ( p_cCadena ) )
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


int SFicTxtEscribirLinea ( SFicTexto * p_ficObj, const char * p_cLinea )
{
	int				iRes;
	unsigned long	ulTam;

	if ( ES_VALIDO ( p_ficObj ) && ES_VALIDO ( p_cLinea ) )
	{
		ulTam = CadLongitud ( p_cLinea );
		if ( SFicSecEscribirBuffer ( p_ficObj->p_ficObj, (byte *) p_cLinea, &ulTam ) == 1 )
		{
			if ( ulTam == (unsigned long) CadLongitud ( p_cLinea ) )
			{
				if ( p_ficObj->iEstilo == EST_FTXT_UNIX ) 
				{
					iRes = SFicSecEscribir ( p_ficObj->p_ficObj, 0x0A );
				}
				else
				{
					if ( SFicSecEscribir ( p_ficObj->p_ficObj, 0x0D ) == 1 )
					{
						iRes = SFicSecEscribir ( p_ficObj->p_ficObj, 0x0A );
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
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SFicTxtEscribirSaltoLinea ( SFicTexto * p_ficObj )
{
	int	iRes;

	if ( ES_VALIDO ( p_ficObj )  )
	{
		if ( p_ficObj->iEstilo == EST_FTXT_UNIX ) 
		{
			iRes = SFicSecEscribir ( p_ficObj->p_ficObj, 0x0A );
		}
		else
		{
			if ( SFicSecEscribir ( p_ficObj->p_ficObj, 0x0A ) == 1 )
			{
				iRes = SFicSecEscribir ( p_ficObj->p_ficObj, 0x0D );
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

int SFicTxtEscribirEspacios ( SFicTexto * p_ficObj, int iNum )
{
	int		iRes;
	char	cVal;
	int		iCar;

	if ( ES_VALIDO ( p_ficObj ) && ( iNum >= 0 ) )
	{
		iRes = 1;
		iCar = 0;
		cVal = ' ';
		while ( ( iRes == 1 ) && ( iCar < iNum ) )
		{
			iRes = SFicSecEscribir ( p_ficObj->p_ficObj, (byte) cVal );
			iCar = iCar + 1;
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SFicTxtEscribirTabulador ( SFicTexto * p_ficObj )
{
	int		iRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		iRes = SFicSecEscribir ( p_ficObj->p_ficObj, 0x09 );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SFicTxtEscribirEntreComparadores ( SFicTexto * p_ficObj, const char * p_cCadena )
{
	int		iRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		if ( SFicTxtEscribirCaracter ( p_ficObj, '<' ) == 1 )
		{
			if ( SFicTxtEscribir ( p_ficObj, p_cCadena ) == 1 )
			{
				iRes =  SFicTxtEscribirCaracter ( p_ficObj, '>' );
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
