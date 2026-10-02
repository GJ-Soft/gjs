#include "SIndiceLiterales.h"
          
#include "TiposDatosConfig.h"



static int _SLczComparar ( void * p_vVal1, void * p_vVal2 )
{
    int 			iRes;
    SLocalizador * 	p_lczVal1 = (SLocalizador *) p_vVal1;
    SLocalizador * 	p_lczVal2 = (SLocalizador *) p_vVal2;
    iRes = SLczComparar ( p_lczVal1, p_lczVal2 );
	if ( iRes == COMP_MENOR ) 
	{
		iRes = -1;
	}
	else if ( iRes == COMP_MAYOR ) 
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
    return ( iRes );
}

SIndiceLiterales * SIndLitCrear ()
{
	SIndiceLiterales * p_indlObj;
	
	p_indlObj = (SIndiceLiterales *) MemReservar ( sizeof ( SIndiceLiterales ) );
	if ( ES_VALIDO ( p_indlObj ) )
	{
		p_indlObj->p_cnjpDatos = SCnjpCrear ( _SLczComparar );
		if ( ES_VALIDO ( p_indlObj->p_cnjpDatos ) )
		{
			SCnjpDesactivarLiberacionMemoria ( p_indlObj->p_cnjpDatos );
		}
		else
		{
			MemLiberar ( (void **) &p_indlObj );
		}
	}
	return ( p_indlObj );
}

void SIndLitDestruir ( SIndiceLiterales ** p_p_indlObj )
{
	SIndiceLiterales * p_indlObj;
	
	if ( ES_VALIDO ( p_p_indlObj ) )
	{
		p_indlObj = *p_p_indlObj;
		if ( ES_VALIDO ( p_indlObj ) )
		{
			SIndLitVaciar ( p_indlObj );
			SCnjpDestruir ( &(p_indlObj->p_cnjpDatos) );
			MemLiberar ( (void **) p_p_indlObj );
		}
	}
}

int SIndLitEsValido ( SIndiceLiterales * p_indlObj )
{
	int iRes;

	if ( ES_VALIDO ( p_indlObj ) )
	{
		iRes = SCnjpEsValido ( p_indlObj->p_cnjpDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SIndLitEstaVacio ( SIndiceLiterales * p_indlObj )
{
	int iRes;

	if ( ES_VALIDO ( p_indlObj ) )
	{
		iRes = SCnjpEstaVacio ( p_indlObj->p_cnjpDatos );
	}
	else
	{
		iRes = 1;
	}
	return ( iRes );
}

int SIndLitNumElementos ( SIndiceLiterales * p_indlObj )
{
	int iRes;

	if ( ES_VALIDO ( p_indlObj ) )
	{
		iRes = SCnjpNumElementos ( p_indlObj->p_cnjpDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

SLocalizador * SIndLitElemento ( SIndiceLiterales * p_indlObj, int iElem )
{
	SLocalizador * p_lczRes;

	if ( ES_VALIDO ( p_indlObj ) )
	{
		p_lczRes = (SLocalizador *) SCnjpElemento ( p_indlObj->p_cnjpDatos, iElem );
	}
	else
	{
		p_lczRes = NULL;
	}
	return ( p_lczRes );
}

const char * SIndLitElementoClave ( SIndiceLiterales * p_indlObj, int iElem )
{
	const char *	p_cRes;
	SLocalizador * 	p_lczElem;

	p_lczElem = SIndLitElemento ( p_indlObj, iElem );
	if ( ES_VALIDO ( p_lczElem ) )
	{
		p_cRes = SLczClave ( p_lczElem );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

unsigned long SIndLitElementoPosicion ( SIndiceLiterales * p_indlObj, int iElem )
{
	unsigned long	ulRes;
	SLocalizador * 	p_lczElem;

	p_lczElem = SIndLitElemento ( p_indlObj, iElem );
	if ( ES_VALIDO ( p_lczElem ) )
	{
		ulRes = SLczPosicion ( p_lczElem );
	}
	else
	{
		ulRes = SLCZ_SIN_POSICION;
	}
	return ( ulRes );
}

int SIndLitInsertar ( SIndiceLiterales * p_indlObj, SLocalizador * p_lczDato )
{
	int		iRes;

	if ( ES_VALIDO ( p_indlObj ) && ( SLczEsValido ( p_lczDato ) == 1 ) )
	{
		if ( SCnjpInsertarElem ( p_indlObj->p_cnjpDatos, (byte *) p_lczDato ) == 1 )
		{
			iRes = 1;
		}
		else
		{
			iRes = -1;
		}
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int SIndLitInsertarExt ( SIndiceLiterales * p_indlObj, const char * p_cClave, unsigned long ulPosicion )
{
	int				iRes;
	SLocalizador *	p_lczElem;

	if ( ES_VALIDO ( p_indlObj ) )
	{
		p_lczElem = SLczCrearExt ( p_cClave, ulPosicion );
		iRes = SIndLitInsertar ( p_indlObj, p_lczElem );
		/* Si no entra ( clave repetida, o localizador no valido ) sigue
		   siendo nuestro: se destruye para no perderlo. */
		if ( iRes != 1 )
		{
			SLczDestruir ( &p_lczElem );
		}
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int SIndLitEliminar ( SIndiceLiterales * p_indlObj, int iElem )
{
	int 			iRes;
	SLocalizador *	p_lczElem;

	if ( ES_VALIDO ( p_indlObj ) )
	{
		p_lczElem = SIndLitElemento ( p_indlObj, iElem );
		iRes = SCnjpEliminarElem ( p_indlObj->p_cnjpDatos, iElem );
		if ( iRes == 1 )
		{
			SLczDestruir ( &p_lczElem );
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SIndLitEliminarClave ( SIndiceLiterales * p_indlObj, const char * p_cClave )
{
	return ( SIndLitEliminar ( p_indlObj, SIndLitBuscar ( p_indlObj, p_cClave ) ) );
}

int SIndLitVaciar ( SIndiceLiterales * p_indlObj )
{
	int iRes;
	int	iError;

	if ( ES_VALIDO ( p_indlObj ) )
	{
		iError = 0;
		while ( ( SIndLitEstaVacio ( p_indlObj ) == 0 ) && ( iError == 0 ) )
		{
			if ( SIndLitEliminar ( p_indlObj, 0 ) != 1 )
			{
				iError = 1;
			}
		}
		iRes = SCnjpVaciar ( p_indlObj->p_cnjpDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SIndLitExiste ( SIndiceLiterales * p_indlObj, const char * p_cClave )
{
	int iRes;

	if ( SIndLitBuscar ( p_indlObj, p_cClave ) >= 0 )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SIndLitBuscar ( SIndiceLiterales * p_indlObj, const char * p_cClave )
{
	int				iRes;
	SLocalizador *	p_lczSonda;
	
	if ( ES_VALIDO ( p_indlObj ) ) 
	{
		/* El comparador del conjunto recibe SLocalizador, no la cadena: se
		   busca con un localizador sonda. Basta la clave: las comparaciones
		   no miran la posicion. */
		p_lczSonda = SLczCrear ( p_cClave );
		if ( ES_VALIDO ( p_lczSonda ) )
		{
			iRes = SCnjpBuscar ( p_indlObj->p_cnjpDatos, (byte *) p_lczSonda );
			SLczDestruir ( &p_lczSonda );
		}
		else
		{
			iRes = -1;
		}
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

unsigned long SIndLitPosicion ( SIndiceLiterales * p_indlObj, const char * p_cClave )
{
	unsigned long ulRes;

	if ( ES_VALIDO ( p_indlObj ) ) 
	{
		ulRes = SLczPosicion ( SIndLitElemento ( p_indlObj, SIndLitBuscar ( p_indlObj, p_cClave ) ) );
	}
	else
	{
		ulRes = SLCZ_SIN_POSICION;
	}
	return ( ulRes );
}
