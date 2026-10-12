
#include "SEntidad.h"

#include "TiposBaseDatosConfig.h"



SEntidad * SEntCrearDef ()
{
	SEntidad *  p_entObj;
    SId *       p_idEntidad;

    p_idEntidad = SIdCrearDef ();
    p_entObj = SEntEncapsularExt ( p_idEntidad, NULL );
    if ( ES_NULO ( p_entObj ) )
    {
        SIdDestruir ( &p_idEntidad );
    }
    return ( p_entObj );
}

SEntidad * SEntCrear ( unsigned long ulId )
{
	return ( SEntCrearExt ( ulId, NULL ) );
}

SEntidad * SEntCrearExt ( unsigned long ulId, void * p_vContenido )
{
	SEntidad *  p_entObj;
    SId *       p_idEntidad;

    p_idEntidad = SIdCrear ( ulId );
    p_entObj = SEntEncapsularExt ( p_idEntidad, p_vContenido );
    if ( ES_NULO ( p_entObj ) )
    {
        SIdDestruir ( &p_idEntidad );
    }
    return ( p_entObj );
}

SEntidad * SEntEncapsular ( SId * p_idEntidad )
{
	return ( SEntEncapsularExt ( p_idEntidad, NULL ) );
}

SEntidad * SEntEncapsularExt ( SId * p_idEntidad, void * p_vContenido )
{
	SEntidad *	p_entObj;
	
    if ( ES_VALIDO ( p_idEntidad ) )
    {
        p_entObj= (SEntidad *) MemReservar ( sizeof ( SEntidad ) );
        if ( ES_VALIDO ( p_entObj ) )
        {
            p_entObj->p_idEntidad = p_idEntidad;
            p_entObj->p_vContenido = p_vContenido;
        }
    }
    else
    {
        p_entObj = NULL;
    }
	return ( p_entObj );
}

void * SEntDestruir ( SEntidad ** p_p_entObj )
{
	SEntidad *  p_entObj;
    void *      p_vRes;

	if ( ES_VALIDO ( p_p_entObj ) )
	{
		p_entObj = *p_p_entObj;

		if ( ES_VALIDO ( p_entObj ) )
		{
			p_vRes = p_entObj->p_vContenido;
            SIdDestruir ( &(p_entObj->p_idEntidad) );
			MemLiberar ( (void **) p_p_entObj );
		}
        else
        {
            p_vRes = NULL;
        }
	}
    else
    {
        p_vRes = NULL;
    }
    return ( p_vRes );
}

int SEntEsValida ( SEntidad * p_entObj )
{
	int iRes;

	if ( ES_VALIDO ( p_entObj ) )
	{
		/* Solo el identificador. El contenido es opcional a proposito ( para eso
		   estan SEntCrear y SEntCrearExt ), asi que exigirlo aqui haria invalida
		   a toda entidad creada sin el. */
		if ( SIdEsValido ( p_entObj->p_idEntidad ) == 1 )
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

int SEntTieneContenido ( SEntidad * p_entObj )
{
	int iRes;

	if ( ES_VALIDO ( p_entObj ) )
	{
		if ( ES_VALIDO ( p_entObj->p_vContenido ) == 1 )
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

SId * SEntId ( SEntidad * p_entObj )
{
	SId * p_idRes;

	if ( ES_VALIDO ( p_entObj ) )
	{
		p_idRes = p_entObj->p_idEntidad;
	}
	else
	{
		p_idRes = NULL;
	}
	return ( p_idRes );
}

unsigned long SEntValorId ( SEntidad * p_entObj )
{
	unsigned long ulRes;

	if ( ES_VALIDO ( p_entObj ) )
	{
		ulRes = SIdValor ( p_entObj->p_idEntidad );
	}
	else
	{
		ulRes = 0;
	}
	return ( ulRes );
}

int SEntEstablecerId ( SEntidad * p_entObj, SId * p_idEntidad )
{
	int iRes;

	if ( ES_VALIDO ( p_entObj ) )
	{
		if ( SIdAsignar ( p_entObj->p_idEntidad, p_idEntidad ) == 1 )
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

int SEntEstablecerValorId ( SEntidad * p_entObj, unsigned long ulId )
{
	int iRes;

	if ( ES_VALIDO ( p_entObj ) )
	{
		if ( SIdEstablecer ( p_entObj->p_idEntidad, ulId ) == 1 )
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

void * SEntContenido ( SEntidad * p_entObj )
{
	void * p_vRes;

	if ( ES_VALIDO ( p_entObj ) )
	{
		p_vRes = p_entObj->p_vContenido;
	}
	else
	{
		p_vRes = NULL;
	}
	return ( p_vRes );
}

void * SEntEstablecerContenido ( SEntidad * p_entObj, void * p_vContenido )
{
	void * p_vRes;

	if ( ES_VALIDO ( p_entObj ) )
	{
		p_vRes = p_entObj->p_vContenido;
        p_entObj->p_vContenido = p_vContenido;
	}
	else
	{
		p_vRes = NULL;
	}
	return ( p_vRes );
}


int SEntEsIgual ( SEntidad * p_entObj, SEntidad * p_entVal )
{
	int iRes;

	if ( ES_VALIDO ( p_entObj ) && ES_VALIDO ( p_entVal ) )
	{
		iRes = SIdEsIgual ( p_entObj->p_idEntidad, SEntId ( p_entVal ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SEntEsMenor ( SEntidad * p_entObj, SEntidad * p_entVal )
{
	int iRes;

	if ( ES_VALIDO ( p_entObj ) && ES_VALIDO ( p_entVal ) )
	{
		iRes = SIdEsMenor ( p_entObj->p_idEntidad, SEntId ( p_entVal ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SEntEsMayor ( SEntidad * p_entObj, SEntidad * p_entVal )
{
	int iRes;

	if ( ES_VALIDO ( p_entObj ) && ES_VALIDO ( p_entVal ) )
	{
		iRes = SIdEsMayor ( p_entObj->p_idEntidad, SEntId ( p_entVal ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SEntEsMenorIg ( SEntidad * p_entObj, SEntidad * p_entVal )
{
	int iRes;

	if ( ES_VALIDO ( p_entObj ) && ES_VALIDO ( p_entVal ) )
	{
		iRes = SIdEsMenorIg ( p_entObj->p_idEntidad, SEntId ( p_entVal ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SEntEsMayorIg ( SEntidad * p_entObj, SEntidad * p_entVal )
{
	int iRes;

	if ( ES_VALIDO ( p_entObj ) && ES_VALIDO ( p_entVal ) )
	{
		iRes = SIdEsMayorIg ( p_entObj->p_idEntidad, SEntId ( p_entVal ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SEntEsIgualId ( SEntidad * p_entObj, SId * p_idVal )
{
	int iRes;

	if ( ES_VALIDO ( p_entObj ) && ES_VALIDO ( p_idVal ) )
	{
		iRes = SIdEsIgualNum ( p_entObj->p_idEntidad, SIdValor ( p_idVal ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SEntEsMenorId ( SEntidad * p_entObj, SId * p_idVal )
{
	int iRes;

	if ( ES_VALIDO ( p_entObj ) && ES_VALIDO ( p_idVal ) )
	{
		iRes = SIdEsMenorNum ( p_entObj->p_idEntidad, SIdValor ( p_idVal ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SEntEsMayorId ( SEntidad * p_entObj, SId * p_idVal )
{
	int iRes;

	if ( ES_VALIDO ( p_entObj ) && ES_VALIDO ( p_idVal ) )
	{
		iRes = SIdEsMayorNum ( p_entObj->p_idEntidad, SIdValor ( p_idVal ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SEntEstaEnRangoId ( SEntidad * p_entObj, SId * p_idVal1, SId * p_idVal2 )
{
	int iRes;

	if ( ES_VALIDO ( p_entObj ) && ( SIdEsValido ( p_idVal1 ) == 1 ) && 
		 ( SIdEsValido ( p_idVal2 ) == 1 ) )
	{
		iRes = SIdEstaEnRangoNum ( p_entObj->p_idEntidad, SIdValor ( p_idVal1 ), SIdValor ( p_idVal2 ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SEntEsMenorIgId ( SEntidad * p_entObj, SId * p_idVal )
{
	int iRes;

	if ( ES_VALIDO ( p_entObj ) && ES_VALIDO ( p_idVal ) )
	{
		iRes = SIdEsMenorIgNum ( p_entObj->p_idEntidad, SIdValor ( p_idVal ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SEntEsMayorIgId ( SEntidad * p_entObj, SId * p_idVal )
{
	int iRes;

	if ( ES_VALIDO ( p_entObj ) && ES_VALIDO ( p_idVal ) )
	{
		iRes = SIdEsMayorIgNum ( p_entObj->p_idEntidad, SIdValor ( p_idVal ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SEntEstaEnRangoIgId ( SEntidad * p_entObj, SId * p_idVal1, SId * p_idVal2 )
{
	int iRes;

	if ( ES_VALIDO ( p_entObj ) && ( SIdEsValido ( p_idVal1 ) == 1 ) && 
		 ( SIdEsValido ( p_idVal2 ) == 1 ) )
	{
		iRes = SIdEstaEnRangoIgNum ( p_entObj->p_idEntidad, SIdValor ( p_idVal1 ), SIdValor ( p_idVal2 ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SEntEsIgualNum ( SEntidad * p_entObj, unsigned long ulId )
{
	int iRes;

	if ( ES_VALIDO ( p_entObj ) ) 
	{
		iRes = SIdEsIgualNum ( p_entObj->p_idEntidad, ulId );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SEntEsMenorNum ( SEntidad * p_entObj, unsigned long ulId )
{
	int iRes;

	if ( ES_VALIDO ( p_entObj ) ) 
	{
		iRes = SIdEsMenorNum ( p_entObj->p_idEntidad, ulId );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SEntEsMayorNum ( SEntidad * p_entObj, unsigned long ulId )
{
	int iRes;

	if ( ES_VALIDO ( p_entObj ) ) 
	{
		iRes = SIdEsMayorNum ( p_entObj->p_idEntidad, ulId );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SEntEstaEnRangoNum ( SEntidad * p_entObj, unsigned long ulId1, unsigned long ulId2 )
{
	int iRes;

	if ( ES_VALIDO ( p_entObj ) ) 
	{
		iRes = SIdEstaEnRangoNum ( p_entObj->p_idEntidad, ulId1, ulId2 );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SEntEsMenorIgNum ( SEntidad * p_entObj, unsigned long ulId )
{
	int iRes;

	if ( ES_VALIDO ( p_entObj ) ) 
	{
		iRes = SIdEsMenorIgNum ( p_entObj->p_idEntidad, ulId );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SEntEsMayorIgNum ( SEntidad * p_entObj, unsigned long ulId )
{
	int iRes;

	if ( ES_VALIDO ( p_entObj ) ) 
	{
		iRes = SIdEsMayorIgNum ( p_entObj->p_idEntidad, ulId );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SEntEstaEnRangoIgNum ( SEntidad * p_entObj, unsigned long ulId1, unsigned long ulId2 )
{
	int iRes;

	if ( ES_VALIDO ( p_entObj ) ) 
	{
		iRes = SIdEstaEnRangoIgNum ( p_entObj->p_idEntidad, ulId1, ulId2 );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}


int SEntComparar ( SEntidad * p_entObj, SEntidad * p_entVal )
{
	int iRes;

	if ( ES_VALIDO ( p_entObj ) && ES_VALIDO ( p_entVal ) )
	{
		iRes = SEntCompararId ( p_entObj, SEntId ( p_entVal ) );
	}
	else if  ( ES_VALIDO ( p_entObj ) )
	{
		iRes = COMP_MAYOR;
	}
	else if  ( ES_VALIDO ( p_entVal ) )
	{
		iRes = COMP_MENOR;
	}
	else
	{
		iRes = COMP_IGUAL;
	}
	return ( iRes );
}

int SEntCompararId ( SEntidad * p_entObj, SId * p_idVal )
{
	int iRes;

	if ( ES_VALIDO ( p_entObj ) )
	{
		iRes = SIdComparar ( SEntId ( p_entObj ), p_idVal );
	}
	else if  ( ES_VALIDO ( p_idVal ) )
	{
		iRes = COMP_MENOR;
	}
	else
	{
		iRes = COMP_IGUAL;
	}
	return ( iRes );
}

int SEntCompararNum ( SEntidad * p_entObj, unsigned long ulId )
{
	int iRes;

	if ( ES_VALIDO ( p_entObj ) ) 
	{
		iRes = SIdCompararNum ( SEntId ( p_entObj ), ulId );
	}
	else
	{
		iRes = COMP_MENOR;
	}
	return ( iRes );
}

unsigned int SEntHash ( SEntidad * p_entObj )
{
	unsigned int uiRes = 0;

	if ( ES_VALIDO ( p_entObj ) )
	{
		uiRes = SIdHash ( p_entObj->p_idEntidad );
	}
	return ( uiRes );
}


