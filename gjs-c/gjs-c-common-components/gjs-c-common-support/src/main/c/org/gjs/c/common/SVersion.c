#include "SVersion.h"

#include "AplicacionConfig.h"





SVersion * SVerCrearDef ()
{
	SVersion * p_verObj;
	
	p_verObj = (SVersion *) MemReservar ( sizeof ( SVersion ) );
	if ( ES_VALIDO ( p_verObj ) )
	{
		p_verObj->iVersion = 1;
		p_verObj->iSubversion = 0;
		p_verObj->iRevision = 0;
		p_verObj->p_fecVersion = SFecCrearDef ();
		if ( ES_NULO ( p_verObj->p_fecVersion ) )
		{
			SVerDestruir ( &p_verObj );
		}
	}
	return ( p_verObj );
}

SVersion * SVerCrear ( int iVersion, int iSubversion, int iRevision, long lFecVersion ) 
{
	SVersion * p_verObj;
	
	if ( ( iVersion > 0 ) && ( iSubversion >= 0 ) && ( iRevision >= 0 ) && ( FecFormEsValida ( lFecVersion ) == 1 ) )
	{
		p_verObj = (SVersion *) MemReservar ( sizeof ( SVersion ) );
		if ( ES_VALIDO ( p_verObj ) )
		{
			p_verObj->iVersion = iVersion;
			p_verObj->iSubversion = iSubversion;
			p_verObj->iRevision = iRevision;
			p_verObj->p_fecVersion = SFecCrear ( lFecVersion );
			if ( ES_NULO ( p_verObj->p_fecVersion ) )
			{
				SVerDestruir ( &p_verObj );
			}
		}
	}
	else
	{
		p_verObj = NULL;
	}
	return ( p_verObj );
}

SVersion * SVerCrearExt ( int iVersion, int iSubversion, int iRevision, SFecha * p_fecVersion ) 
{
	SVersion * p_verObj;
	
	if ( ( iVersion > 0 ) && ( iSubversion >= 0 ) && ( iRevision >= 0 ) && ( SFecEsValida ( p_fecVersion ) == 1 ) )
	{
		p_verObj = (SVersion *) MemReservar ( sizeof ( SVersion ) );
		if ( ES_VALIDO ( p_verObj ) )
		{
			p_verObj->iVersion = iVersion;
			p_verObj->iSubversion = iSubversion;
			p_verObj->iRevision = iRevision;
			p_verObj->p_fecVersion = SFecCrear ( SFecValor ( p_fecVersion ) );
			if ( ES_NULO ( p_verObj->p_fecVersion ) )
			{
				SVerDestruir ( &p_verObj );
			}
		}
	}
	else
	{
		p_verObj = NULL;
	}
	return ( p_verObj );
}

void SVerDestruir ( SVersion ** p_p_verObj )
{
	SVersion * p_verObj;
	
	if ( ES_VALIDO ( p_p_verObj ) )
	{
		p_verObj = *p_p_verObj;

		if ( ES_VALIDO ( p_verObj ) )
		{
			SFecDestruir ( &(p_verObj->p_fecVersion) );
			MemLiberar ( (void **) p_p_verObj );
		}
	}
}

int SVerVersion ( SVersion * p_verObj )
{
	int iRes;

	if ( ES_VALIDO ( p_verObj ) )
	{
		iRes = p_verObj->iVersion;
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int SVerSubversion ( SVersion * p_verObj )
{
	int iRes;

	if ( ES_VALIDO ( p_verObj ) )
	{
		iRes = p_verObj->iSubversion;
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int SVerRevision ( SVersion * p_verObj )
{
	int iRes;

	if ( ES_VALIDO ( p_verObj ) )
	{
		iRes = p_verObj->iRevision;
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

SFecha * SVerFecha ( SVersion * p_verObj )
{
	SFecha * p_fecRes;

	if ( ES_VALIDO ( p_verObj ) )
	{
		p_fecRes = p_verObj->p_fecVersion;
	}
	else
	{
		p_fecRes = NULL;
	}
	return ( p_fecRes );
}

char * SVerCadenaVersion ( SVersion * p_verObj, int iCorta )
{
	int		iTam;
	char *	p_cRes;

	if ( ES_VALIDO ( p_verObj ) )
	{
		if ( ( iCorta == 0 ) && ( p_verObj->iRevision >= 0 ) )
		{
			iTam = NumDigitosEntero ( p_verObj->iVersion ) + NumDigitosEntero ( p_verObj->iSubversion ) + NumDigitosEntero ( p_verObj->iRevision ) + 2;
			p_cRes = CadCrear ( iTam );
			if ( ES_VALIDO ( p_cRes ) )
			{
				CadCopiarConFormato ( p_cRes, VER_FORM_CADENA, p_verObj->iVersion, p_verObj->iSubversion, p_verObj->iRevision );
			}
		}
		else
		{
			iTam = NumDigitosEntero ( p_verObj->iVersion ) + NumDigitosEntero ( p_verObj->iSubversion ) + 1;
			p_cRes = CadCrear ( iTam );
			if ( ES_VALIDO ( p_cRes ) )
			{
				CadCopiarConFormato ( p_cRes, VER_FORM_CADENA_CORTO, p_verObj->iVersion, p_verObj->iSubversion );
			}
		}
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

char * SVerCadenaFecha ( SVersion * p_verObj )
{
	char *	p_cRes;

	if ( ES_VALIDO ( p_verObj ) )
	{
		p_cRes = SFecFechaForm ( p_verObj->p_fecVersion, FEC_FORMATO_NUMERICO );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

long SVerValorFecha ( SVersion * p_verObj )
{
	long lRes;

	if ( ES_VALIDO ( p_verObj ) )
	{
		lRes = SFecValor ( p_verObj->p_fecVersion );
	}
	else
	{
		lRes = -1;
	}
	return ( lRes );
}

int SVerEsValida ( SVersion * p_verObj )
{
	int iRes;

	if ( ES_VALIDO ( p_verObj ) )
	{
		if ( ( p_verObj->iVersion > 0 ) && ( p_verObj->iSubversion >= 0 ) && 
			 ( SFecEsValida ( p_verObj->p_fecVersion ) == 1 ) )
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

int SVerEstablecerVersion ( SVersion * p_verObj, int iVersion )
{
	int iRes;

	if ( ES_VALIDO ( p_verObj ) )
	{
		if ( iVersion > 0 )
		{
			p_verObj->iVersion = iVersion;
			iRes = 1;
		}
		else
		{
			p_verObj->iVersion = 0;
			iRes = 0;
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SVerEstablecerSubversion ( SVersion * p_verObj, int iSubversion )
{
	int iRes;

	if ( ES_VALIDO ( p_verObj ) )
	{
		if ( iSubversion >= 0 )
		{
			p_verObj->iSubversion = iSubversion;
			iRes = 1;
		}
		else
		{
			p_verObj->iSubversion = -1;
			iRes = 0;
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SVerEstablecerRevision ( SVersion * p_verObj, int iRevision )
{
	int iRes;

	if ( ES_VALIDO ( p_verObj ) )
	{
		if ( iRevision >= 0 )
		{
			p_verObj->iRevision = iRevision;
			iRes = 1;
		}
		else
		{
			p_verObj->iRevision = -1;
			iRes = 0;
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SVerEstablecerFechaEnteroLargo ( SVersion * p_verObj, long lFecVersion )
{
	int iRes;

	if ( ES_VALIDO ( p_verObj ) )
	{
		if ( SFecEstablecer ( p_verObj->p_fecVersion, lFecVersion ) == 1 )
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

int SVerEstablecerFecha ( SVersion * p_verObj, SFecha * p_fecVersion )
{
	int iRes;

	if ( ES_VALIDO ( p_verObj ) )
	{
		if ( SFecEstablecer ( p_verObj->p_fecVersion, SFecValor ( p_fecVersion ) ) == 1 )
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

int SVerEstablecer ( SVersion * p_verObj, int iVersion, int iSubversion, int iRevision, long lFecVersion )
{
	int iRes;

	iRes = SVerEstablecerVersion ( p_verObj, iVersion ) +
		   SVerEstablecerSubversion ( p_verObj, iSubversion ) +
		   SVerEstablecerRevision ( p_verObj, iRevision ) +
		   SVerEstablecerFechaEnteroLargo ( p_verObj, lFecVersion );

	if ( iRes == 4 )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SVerEstablecerExt ( SVersion * p_verObj, int iVersion, int iSubversion, int iRevision, SFecha * p_fecVersion ) 
{
	int iRes;

	iRes = SVerEstablecerVersion ( p_verObj, iVersion ) +
		   SVerEstablecerSubversion ( p_verObj, iSubversion ) +
		   SVerEstablecerRevision ( p_verObj, iRevision ) +
		   SVerEstablecerFecha ( p_verObj, p_fecVersion );

	if ( iRes == 4 )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

void SVerImprimir ( SVersion * p_verObj )
{
	char * p_cFecha;

	if ( ES_VALIDO ( p_verObj ) )
	{
		p_cFecha = SFecFechaForm ( p_verObj->p_fecVersion, FEC_FORMATO_NUMERICO );
		if ( ES_VALIDO ( p_cFecha ) )
		{
			printf ( VER_FORM_MENSAJE, p_verObj->iVersion, p_verObj->iSubversion,p_verObj-> iRevision, p_cFecha );
			MemLiberar ( (void **) p_cFecha );
		}
		else
		{
			printf ( VER_FORM_MENSAJE, p_verObj->iVersion, p_verObj->iSubversion, p_verObj->iRevision, VER_TXT_FECHA_NULA );
		}
	}
}




