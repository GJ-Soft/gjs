
#include "SEntidadNom.h"

#include "TiposBaseDatosConfig.h"





SEntidadNom * SEntNomCrearDef ()
{
	SEntidadNom *  p_entnObj;
    SId *          p_idEntidad;
    SNombre *      p_nomEntidad;

    p_idEntidad = SIdCrearDef ();
    p_nomEntidad = SNomCrearDef ();
    p_entnObj = SEntNomEncapsularExt ( p_idEntidad, p_nomEntidad, NULL );
    if ( ES_NULO ( p_entnObj ) )
    {
        SIdDestruir ( &p_idEntidad );
        SNomDestruir ( &p_nomEntidad );
    }
    return ( p_entnObj );
}

SEntidadNom * SEntNomCrear ( unsigned long ulId, SCadena * p_cadNombre )
{
	return ( SEntNomCrearExt ( ulId, p_cadNombre, NULL ) );
}

SEntidadNom * SEntNomCrearLit ( unsigned long ulId, const char * p_cNombre )
{
	return ( SEntNomCrearLitExt ( ulId, p_cNombre, NULL ) );
}

SEntidadNom * SEntNomCrearExt ( unsigned long ulId, SCadena * p_cadNombre, void * p_vContenido )
{
	SEntidadNom *  p_entnObj;
    SId *          p_idEntidad;
    SNombre *      p_nomEntidad;

    p_idEntidad = SIdCrear ( ulId );
    p_nomEntidad = SNomCrearValor ( p_cadNombre );
    p_entnObj = SEntNomEncapsularExt ( p_idEntidad, p_nomEntidad, p_vContenido );
    if ( ES_NULO ( p_entnObj ) )
    {
        SIdDestruir ( &p_idEntidad );
        SNomDestruir ( &p_nomEntidad );
    }
    return ( p_entnObj );
}

SEntidadNom * SEntNomCrearLitExt ( unsigned long ulId, const char * p_cNombre, void * p_vContenido )
{
	SEntidadNom *  p_entnObj;
    SId *          p_idEntidad;
    SNombre *      p_nomEntidad;

    p_idEntidad = SIdCrear ( ulId );
    p_nomEntidad = SNomCrearValorLit ( p_cNombre );
    p_entnObj = SEntNomEncapsularExt ( p_idEntidad, p_nomEntidad, p_vContenido );
    if ( ES_NULO ( p_entnObj ) )
    {
        SIdDestruir ( &p_idEntidad );
        SNomDestruir ( &p_nomEntidad );
    }
    return ( p_entnObj );
}

SEntidadNom * SEntNomEncapsular ( SId * p_idEntidad, SNombre * p_nomEntidad )
{
	return ( SEntNomEncapsularExt ( p_idEntidad, p_nomEntidad, NULL ) );
}

SEntidadNom * SEntNomEncapsularExt ( SId * p_idEntidad, SNombre * p_nomEntidad, void * p_vContenido )
{
	SEntidadNom *	p_entnObj;
	
    if ( ES_VALIDO ( p_idEntidad ) )
    {
        p_entnObj = (SEntidadNom *) MemReservar ( sizeof ( SEntidadNom ) );
        if ( ES_VALIDO ( p_entnObj ) )
        {
            p_entnObj->p_entInfo = SEntEncapsularExt ( p_idEntidad, p_vContenido );
            if ( ES_VALIDO ( p_entnObj->p_entInfo ) )
            {
				if ( ES_VALIDO ( p_nomEntidad ) )
				{
					p_entnObj->p_nomEntidad = p_nomEntidad;
				}
				else
				{
					p_entnObj->p_nomEntidad = SNomCrearDef ();					
				}
			}
            else
            {
                MemLiberar ( (void **) &p_entnObj );
            }
        }
    }
    else
    {
        p_entnObj = NULL;
    }
	return ( p_entnObj );
}

void * SEntNomDestruir ( SEntidadNom ** p_p_entnObj )
{
	SEntidadNom *   p_entnObj;
    void *          p_vRes;

	if ( ES_VALIDO ( p_p_entnObj ) )
	{
		p_entnObj = *p_p_entnObj;

		if ( ES_VALIDO ( p_entnObj ) )
		{
			p_vRes = SEntDestruir ( &(p_entnObj->p_entInfo) );
            SNomDestruir ( &(p_entnObj->p_nomEntidad) );
			MemLiberar ( (void **) p_p_entnObj );
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

int SEntNomEsValida ( SEntidadNom * p_entnObj )
{
	int iRes;

	if ( ES_VALIDO ( p_entnObj ) )
	{
		/* Solo el identificador, delegando en la base. El nombre es opcional,
		   como el contenido: preguntarle a SNomEsValido si hace falta. */
		if ( SEntEsValida ( p_entnObj->p_entInfo ) == 1 )
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

int SEntNomTieneContenido ( SEntidadNom * p_entnObj )
{
	int iRes;

	if ( ES_VALIDO ( p_entnObj ) )
	{
		iRes = SEntTieneContenido ( p_entnObj->p_entInfo );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

SId * SEntNomId ( SEntidadNom * p_entnObj )
{
	SId * p_idRes;

	if ( ES_VALIDO ( p_entnObj ) )
	{
		p_idRes = SEntId ( p_entnObj->p_entInfo );
	}
	else
	{
		p_idRes = NULL;
	}
	return ( p_idRes );
}

unsigned long SEntNomValorId ( SEntidadNom * p_entnObj )
{
	unsigned long ulRes;

	if ( ES_VALIDO ( p_entnObj ) )
	{
		ulRes = SEntValorId ( p_entnObj->p_entInfo );
	}
	else
	{
		ulRes = 0;
	}
	return ( ulRes );
}

SNombre * SEntNomNombre ( SEntidadNom * p_entnObj )
{
	SNombre * p_nomRes;

	if ( ES_VALIDO ( p_entnObj ) )
	{
		p_nomRes = p_entnObj->p_nomEntidad;
	}
	else
	{
		p_nomRes = NULL;
	}
	return ( p_nomRes );
}

SCadena * SEntNomValorNombre ( SEntidadNom * p_entnObj )
{
	SCadena * p_cadRes;

	if ( ES_VALIDO ( p_entnObj ) )
	{
		p_cadRes = SNomValor ( p_entnObj->p_nomEntidad );
	}
	else
	{
		p_cadRes = NULL;
	}
	return ( p_cadRes );
}

const char * SEntNomValorNombreLit ( SEntidadNom * p_entnObj )
{
	const char * p_cRes;

	if ( ES_VALIDO ( p_entnObj ) )
	{
		p_cRes = SNomValorLit ( p_entnObj->p_nomEntidad );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

void * SEntNomContenido ( SEntidadNom * p_entnObj )
{
	void * p_vRes;

	if ( ES_VALIDO ( p_entnObj ) )
	{
		p_vRes = SEntContenido ( p_entnObj->p_entInfo );
	}
	else
	{
		p_vRes = NULL;
	}
	return ( p_vRes );
}

SEntidad * SEntNomBase ( SEntidadNom * p_entnObj )
{
	SEntidad * p_entRes;

	if ( ES_VALIDO ( p_entnObj ) )
	{
		p_entRes = p_entnObj->p_entInfo;
	}
	else
	{
		p_entRes = NULL;
	}
	return ( p_entRes );
}

int SEntNomEstablecerId ( SEntidadNom * p_entnObj, SId * p_idEntidad )
{
	int iRes;

	if ( ES_VALIDO ( p_entnObj ) )
	{
		if ( SEntEstablecerId ( p_entnObj->p_entInfo, p_idEntidad ) == 1 )
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

int SEntNomEstablecerValorId ( SEntidadNom * p_entnObj, unsigned long ulId )
{
	int iRes;

	if ( ES_VALIDO ( p_entnObj ) )
	{
		if ( SEntEstablecerValorId ( p_entnObj->p_entInfo, ulId ) == 1 )
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

void * SEntNomEstablecerContenido ( SEntidadNom * p_entnObj, void * p_vContenido )
{
	void * p_vRes;

	if ( ES_VALIDO ( p_entnObj ) )
	{
        p_vRes = SEntEstablecerContenido ( p_entnObj->p_entInfo, p_vContenido );
	}
	else
	{
		p_vRes = NULL;
	}
	return ( p_vRes );
}

int SEntNomEstablecerNombre ( SEntidadNom * p_entnObj, SNombre * p_nomEntidad )
{
	int iRes;

	if ( ES_VALIDO ( p_entnObj ) )
	{
		if ( SNomAsignar ( p_entnObj->p_nomEntidad, p_nomEntidad ) == 1 )
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

int SEntNomEstablecerValorNombre ( SEntidadNom * p_entnObj, SCadena * p_cadNombre )
{
	int iRes;

	if ( ES_VALIDO ( p_entnObj ) )
	{
		if ( SNomEstablecer ( p_entnObj->p_nomEntidad, p_cadNombre ) == 1 )
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

int SEntNomEstablecerValorNombreLit ( SEntidadNom * p_entnObj, const char * p_cNombre )
{
	int iRes;

	if ( ES_VALIDO ( p_entnObj ) )
	{
		if ( SNomEstablecerLit ( p_entnObj->p_nomEntidad, p_cNombre ) == 1 )
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

int SEntNomEsIgual ( SEntidadNom * p_entnObj, SEntidadNom * p_entnVal )
{
	int iRes;

	if ( ES_VALIDO ( p_entnObj ) && ES_VALIDO ( p_entnVal ) )
	{
		iRes = SIdEsIgual ( SEntNomId ( p_entnObj ), SEntNomId ( p_entnVal ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SEntNomEsMenor ( SEntidadNom * p_entnObj, SEntidadNom * p_entnVal )
{
	int iRes;

	if ( ES_VALIDO ( p_entnObj ) && ES_VALIDO ( p_entnVal ) )
	{
		iRes = SIdEsMenor ( SEntNomId ( p_entnObj ), SEntNomId ( p_entnVal ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SEntNomEsMayor ( SEntidadNom * p_entnObj, SEntidadNom * p_entnVal )
{
	int iRes;

	if ( ES_VALIDO ( p_entnObj ) && ES_VALIDO ( p_entnVal ) )
	{
		iRes = SIdEsMayor ( SEntNomId ( p_entnObj ), SEntNomId ( p_entnVal ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SEntNomEsMenorIg ( SEntidadNom * p_entnObj, SEntidadNom * p_entnVal )
{
	int iRes;

	if ( ES_VALIDO ( p_entnObj ) && ES_VALIDO ( p_entnVal ) )
	{
		iRes = SIdEsMenorIg ( SEntNomId ( p_entnObj ), SEntNomId ( p_entnVal ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SEntNomEsMayorIg ( SEntidadNom * p_entnObj, SEntidadNom * p_entnVal )
{
	int iRes;

	if ( ES_VALIDO ( p_entnObj ) && ES_VALIDO ( p_entnVal ) )
	{
		iRes = SIdEsMayorIg ( SEntNomId ( p_entnObj ), SEntNomId ( p_entnVal ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SEntNomEsIgualEnt ( SEntidadNom * p_entnObj, SEntidad * p_entVal )
{
	int iRes;

	if ( ES_VALIDO ( p_entnObj ) && ES_VALIDO ( p_entVal ) )
	{
		iRes = SIdEsIgual ( SEntNomId ( p_entnObj ), SEntId ( p_entVal ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SEntNomEsMenorEnt ( SEntidadNom * p_entnObj, SEntidad * p_entVal )
{
	int iRes;

	if ( ES_VALIDO ( p_entnObj ) && ES_VALIDO ( p_entVal ) )
	{
		iRes = SIdEsMenor ( SEntNomId ( p_entnObj ), SEntId ( p_entVal ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SEntNomEsMayorEnt ( SEntidadNom * p_entnObj, SEntidad * p_entVal )
{
	int iRes;

	if ( ES_VALIDO ( p_entnObj ) && ES_VALIDO ( p_entVal ) )
	{
		iRes = SIdEsMayor ( SEntNomId ( p_entnObj ), SEntId ( p_entVal ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SEntNomEsMenorIgEnt ( SEntidadNom * p_entnObj, SEntidad * p_entVal )
{
	int iRes;

	if ( ES_VALIDO ( p_entnObj ) && ES_VALIDO ( p_entVal ) )
	{
		iRes = SIdEsMenorIg ( SEntNomId ( p_entnObj ), SEntId ( p_entVal ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SEntNomEsMayorIgEnt ( SEntidadNom * p_entnObj, SEntidad * p_entVal )
{
	int iRes;

	if ( ES_VALIDO ( p_entnObj ) && ES_VALIDO ( p_entVal ) )
	{
		iRes = SIdEsMayorIg ( SEntNomId ( p_entnObj ), SEntId ( p_entVal ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SEntNomEsIgualId ( SEntidadNom * p_entnObj, SId * p_idVal )
{
	int iRes;

	if ( ES_VALIDO ( p_entnObj ) && ES_VALIDO ( p_idVal ) )
	{
		iRes = SIdEsIgualNum ( SEntNomId ( p_entnObj ), SIdValor ( p_idVal ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SEntNomEsMenorId ( SEntidadNom * p_entnObj, SId * p_idVal )
{
	int iRes;

	if ( ES_VALIDO ( p_entnObj ) && ES_VALIDO ( p_idVal ) )
	{
		iRes = SIdEsMenorNum ( SEntNomId ( p_entnObj ), SIdValor ( p_idVal ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SEntNomEsMayorId ( SEntidadNom * p_entnObj, SId * p_idVal )
{
	int iRes;

	if ( ES_VALIDO ( p_entnObj ) && ES_VALIDO ( p_idVal ) )
	{
		iRes = SIdEsMayorNum ( SEntNomId ( p_entnObj ), SIdValor ( p_idVal ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SEntNomEstaEnRangoId ( SEntidadNom * p_entnObj, SId * p_idVal1, SId * p_idVal2 )
{
	int iRes;

	if ( ES_VALIDO ( p_entnObj ) && ( SIdEsValido ( p_idVal1 ) == 1 ) && 
		 ( SIdEsValido ( p_idVal2 ) == 1 ) )
	{
		iRes = SIdEstaEnRangoNum ( SEntNomId ( p_entnObj ), SIdValor ( p_idVal1 ), SIdValor ( p_idVal2 ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SEntNomEsMenorIgId ( SEntidadNom * p_entnObj, SId * p_idVal )
{
	int iRes;

	if ( ES_VALIDO ( p_entnObj ) && ES_VALIDO ( p_idVal ) )
	{
		iRes = SIdEsMenorIgNum ( SEntNomId ( p_entnObj ), SIdValor ( p_idVal ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SEntNomEsMayorIgId ( SEntidadNom * p_entnObj, SId * p_idVal )
{
	int iRes;

	if ( ES_VALIDO ( p_entnObj ) && ES_VALIDO ( p_idVal ) )
	{
		iRes = SIdEsMayorIgNum ( SEntNomId ( p_entnObj ), SIdValor ( p_idVal ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SEntNomEstaEnRangoIgId ( SEntidadNom * p_entnObj, SId * p_idVal1, SId * p_idVal2 )
{
	int iRes;

	if ( ES_VALIDO ( p_entnObj ) && ( SIdEsValido ( p_idVal1 ) == 1 ) && 
		 ( SIdEsValido ( p_idVal2 ) == 1 ) )
	{
		iRes = SIdEstaEnRangoIgNum ( SEntNomId ( p_entnObj ), SIdValor ( p_idVal1 ), SIdValor ( p_idVal2 ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SEntNomEsIgualNum ( SEntidadNom * p_entnObj, unsigned long ulId )
{
	int iRes;

	if ( ES_VALIDO ( p_entnObj ) ) 
	{
		iRes = SIdEsIgualNum ( SEntNomId ( p_entnObj ), ulId );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SEntNomEsMenorNum ( SEntidadNom * p_entnObj, unsigned long ulId )
{
	int iRes;

	if ( ES_VALIDO ( p_entnObj ) ) 
	{
		iRes = SIdEsMenorNum ( SEntNomId ( p_entnObj ), ulId );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SEntNomEsMayorNum ( SEntidadNom * p_entnObj, unsigned long ulId )
{
	int iRes;

	if ( ES_VALIDO ( p_entnObj ) ) 
	{
		iRes = SIdEsMayorNum ( SEntNomId ( p_entnObj ), ulId );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SEntNomEstaEnRangoNum ( SEntidadNom * p_entnObj, unsigned long ulId1, unsigned long ulId2 )
{
	int iRes;

	if ( ES_VALIDO ( p_entnObj ) ) 
	{
		iRes = SIdEstaEnRangoNum ( SEntNomId ( p_entnObj ), ulId1, ulId2 );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SEntNomEsMenorIgNum ( SEntidadNom * p_entnObj, unsigned long ulId )
{
	int iRes;

	if ( ES_VALIDO ( p_entnObj ) ) 
	{
		iRes = SIdEsMenorIgNum ( SEntNomId ( p_entnObj ), ulId );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SEntNomEsMayorIgNum ( SEntidadNom * p_entnObj, unsigned long ulId )
{
	int iRes;

	if ( ES_VALIDO ( p_entnObj ) ) 
	{
		iRes = SIdEsMayorIgNum ( SEntNomId ( p_entnObj ), ulId );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SEntNomEstaEnRangoIgNum ( SEntidadNom * p_entnObj, unsigned long ulId1, unsigned long ulId2 )
{
	int iRes;

	if ( ES_VALIDO ( p_entnObj ) ) 
	{
		iRes = SIdEstaEnRangoIgNum ( SEntNomId ( p_entnObj ), ulId1, ulId2 );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SEntNomComparar ( SEntidadNom * p_entnObj, SEntidadNom * p_entnVal )
{
	int iRes;

	if ( ES_VALIDO ( p_entnObj ) && ES_VALIDO ( p_entnVal ) )
	{
        iRes = SEntCompararId ( p_entnObj->p_entInfo, SEntNomId ( p_entnVal ) );
		if ( iRes == COMP_IGUAL )
        {
            iRes = SNomComparar ( p_entnObj->p_nomEntidad, SEntNomNombre ( p_entnVal ) );
        }
	}
	else if  ( ES_VALIDO ( p_entnObj ) )
	{
		iRes = COMP_MAYOR;
	}
	else if  ( ES_VALIDO ( p_entnVal ) )
	{
		iRes = COMP_MENOR;
	}
	else
	{
		iRes = COMP_IGUAL;
	}
	return ( iRes );
}

int SEntNomCompararEnt ( SEntidadNom * p_entnObj, SEntidad * p_entVal )
{
	int iRes;

	if ( ES_VALIDO ( p_entnObj ) && ES_VALIDO ( p_entVal ) )
	{
		iRes = SEntComparar ( p_entnObj->p_entInfo, p_entVal );
	}
	else if  ( ES_VALIDO ( p_entnObj ) )
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

int SEntNomCompararId ( SEntidadNom * p_entnObj, SId * p_idVal )
{
	int iRes;

	if ( ES_VALIDO ( p_entnObj ) )
	{
		iRes = SIdComparar ( SEntNomId ( p_entnObj ), p_idVal );
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

int SEntNomCompararNum ( SEntidadNom * p_entnObj, unsigned long ulId )
{
	int iRes;

	if ( ES_VALIDO ( p_entnObj ) ) 
	{
		iRes = SIdCompararNum ( SEntNomId ( p_entnObj ), ulId );
	}
	else
	{
		iRes = COMP_MENOR;
	}
	return ( iRes );
}

unsigned int SEntNomHash ( SEntidadNom * p_entnObj )
{
	unsigned int uiRes = 0;

	if ( ES_VALIDO ( p_entnObj ) )
	{
		/* Solo el id, delegando en la clase base: el hash tiene que ir de la
		   mano de SEntNomEsIgual, que tampoco mira el nombre. Ademas el nombre
		   es mutable ( SEntNomEstablecerNombre y companeras ), asi que meterlo
		   aqui dejaria fuera de su cubeta a toda entidad a la que se le cambie.
		   Delegando, un SEntidadNom y su SEntidad base reparten igual. */
		uiRes = SEntHash ( p_entnObj->p_entInfo );
	}
	return ( uiRes );
}


