
#include "SDivisor.h"
#include "Cadenas.h"

#include "TextoConfig.h"


int _SDivCalcularTam ( SDivisor * p_divObj, int iParteIni );

SDivisor * SDivCrear ( char cSeparador )
{
	SDivisor * p_divObj;
	
	p_divObj = (SDivisor *) MemReservar ( sizeof ( SDivisor ) );
	if ( ES_VALIDO ( p_divObj ) )
	{
        p_divObj->cSeparador = cSeparador;
        p_divObj->p_secPartes = SSecLitCrear ();
        p_divObj->p_cTexto = NULL;
	}
	else
	{
		p_divObj = NULL;
	}
	return ( p_divObj );
}

SDivisor * SDivCrearExt ( char cSeparador, const char * p_cTexto )
{
	SDivisor * p_divObj;
	
	p_divObj = SDivCrear ( cSeparador );
	if ( ES_VALIDO ( p_divObj ) )
	{
		SDivInicializar ( p_divObj,  p_cTexto );
	}
	else
	{
		p_divObj = NULL;
	}
	return ( p_divObj );
}

void SDivDestruir ( SDivisor ** p_p_divObj )
{
	SDivisor * p_divObj;
	
	if ( ES_VALIDO ( p_p_divObj ) )
	{
		p_divObj = * p_p_divObj;

		if ( ES_VALIDO ( p_divObj ) )
		{
			MemLiberar ( (void **) &(p_divObj->p_cTexto) );
			SSecLitDestruir ( &(p_divObj->p_secPartes) );
			MemLiberar ( (void **) p_p_divObj );
		}
	}
}

int SDivEsValido ( SDivisor * p_divObj )
{
	int iRes;

	if ( ES_VALIDO ( p_divObj ) )
	{
		if ( ( ASCIIEsImprimible ( p_divObj->cSeparador ) == 1 ) &&
               ( SSecLitEsValida ( p_divObj->p_secPartes ) == 1 ) )
		{
			if ( ES_VALIDO ( p_divObj->p_cTexto ) )
			{
				if ( SSecLitNumElementos ( p_divObj->p_secPartes ) == CadNumPalabrasSep ( p_divObj->p_cTexto, p_divObj->cSeparador ) )
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
	return ( iRes );
}


int SDivTieneTexto ( SDivisor * p_divObj )
{
	int iRes;

	if ( ES_VALIDO ( p_divObj ) )
	{
		if ( ES_VALIDO ( p_divObj->p_cTexto ) )
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

char SDivSeparador ( SDivisor * p_divObj )
{
	char cRes;

	if ( ES_VALIDO ( p_divObj ) )
	{
		cRes = p_divObj->cSeparador;
	}
	else
	{
		cRes = '\0';
	}
	return ( cRes );
}

const char * SDivTexto ( SDivisor * p_divObj )
{
	const char * p_cRes;

	if ( ES_VALIDO ( p_divObj ) )
	{
		p_cRes = p_divObj->p_cTexto;
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

int SDivInicializar ( SDivisor * p_divObj, const char * p_cTexto )
{
	int iRes;

	if ( ES_VALIDO ( p_divObj ) )
	{
        MemLiberar ( (void **) &(p_divObj->p_cTexto) );
		if ( ( ASCIIEsImprimible ( p_divObj->cSeparador ) == 1 ) &&
               ( SSecLitEsValida ( p_divObj->p_secPartes ) == 1 ) )
		{
			p_divObj->p_cTexto = CadDuplicar ( p_cTexto );
			SSecLitVaciar ( p_divObj->p_secPartes );
			for ( int iParte = 0; iParte < CadNumPalabrasSep ( p_divObj->p_cTexto, p_divObj->cSeparador ); iParte = iParte + 1 )
			{
				char * p_cParte = CadPalabraSep ( p_divObj->p_cTexto, iParte, p_divObj->cSeparador );
				SSecLitInsertar ( p_divObj->p_secPartes, p_cParte );
				MemLiberar ( (void **) &p_cParte );
			}
			iRes = SDivEsValido ( p_divObj );
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

int SDivInicializarExt ( SDivisor * p_divObj, char cSeparador, const char * p_cTexto )
{
	int iRes;

	if ( ES_VALIDO ( p_divObj ) )
	{
		p_divObj->cSeparador = cSeparador;
		iRes = SDivInicializar ( p_divObj, p_cTexto );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

SSecuenciaLiterales * SDivPartes ( SDivisor * p_divObj )
{
	SSecuenciaLiterales * p_secRes;

	if ( ES_VALIDO ( p_divObj ) )
	{
        p_secRes = p_divObj->p_secPartes;
	}
	else
	{
		p_secRes = NULL;
	}
	return ( p_secRes );
}

int SDivNumPartes ( SDivisor * p_divObj )
{
    int iRes;

    if ( ES_VALIDO ( p_divObj ) )
	{
        iRes = SSecLitNumElementos ( p_divObj->p_secPartes );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

const char * SDivParte ( SDivisor * p_divObj, int iParte )
{
    const char * p_cRes;

    if ( ES_VALIDO ( p_divObj ) )
	{
        p_cRes = (const char *) SSecLitElemento ( p_divObj->p_secPartes, iParte );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

char * SDivSubtexto ( SDivisor * p_divObj )
{
	return ( SDivSubtextoExt ( p_divObj, 1 ) );
}

char * SDivSubtextoExt ( SDivisor * p_divObj, int iAvances )
{
    char * 	p_cRes;
	int 	iNumPartes;

    if ( ES_VALIDO ( p_divObj ) ) 
	{
		iNumPartes = SDivNumPartes ( p_divObj );
		if ( ( iAvances >= 0 ) && ( iAvances < iNumPartes ) )
		{
			p_cRes = CadCrear ( _SDivCalcularTam ( p_divObj, iAvances ) );
			for ( int iParte = 0; iParte < iNumPartes - iAvances; iParte = iParte + 1 )
			{
				char * p_cParte = SSecLitElemento ( p_divObj->p_secPartes, iAvances + iParte );
				if ( iParte > 0 ) 
				{
				   CadConcatenarCaracter ( p_cRes, p_divObj->cSeparador );
				}
				CadConcatenar ( p_cRes, p_cParte );
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

SDivisor * SDivSubdivisor ( SDivisor * p_divObj )
{
	return ( SDivSubdivisorExt ( p_divObj, 1 ) );
}

SDivisor * SDivSubdivisorExt ( SDivisor * p_divObj, int iAvances )
{
    SDivisor * 	p_divRes;
	char * 		p_cSubtexto;

    if ( ES_VALIDO ( p_divObj ) ) 
	{
		p_cSubtexto = SDivSubtextoExt ( p_divObj, iAvances );
		if ( ES_VALIDO ( p_cSubtexto ) ) 
		{
			p_divRes = SDivCrearExt ( p_divObj->cSeparador, p_cSubtexto );	
			MemLiberar ( (void **) &p_cSubtexto );
		}
		else
		{
			p_divRes = NULL;
		}
	}
	else
	{
		p_divRes = NULL;
	}
	return ( p_divRes );
}

int _SDivCalcularTam ( SDivisor * p_divObj, int iParteIni )
{
	int iRes;
	int iNumPartes;

	iRes = 0;
    if ( ES_VALIDO ( p_divObj ) ) 
	{
		iNumPartes = SDivNumPartes ( p_divObj );
		if ( ( iParteIni >= 0 ) && ( iParteIni < iNumPartes ) )
		{
			for ( int iParte = 0; iParte < iNumPartes - iParteIni; iParte = iParte + 1 )
			{
				iRes = iRes + CadLongitud ( SSecLitElemento ( p_divObj->p_secPartes, iParteIni + iParte ) );
				if ( iParte > 0 ) 
				{
				   iRes = iRes + 1;
				}
			}
		}
	}
	return ( iRes );
}


