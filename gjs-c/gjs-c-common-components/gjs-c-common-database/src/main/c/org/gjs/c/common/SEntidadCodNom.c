
#include "SEntidadCodNom.h"

#include "TiposBaseDatosConfig.h"



SEntidadCodNom * SEntCodNomCrearDef ( int iMaxTam )
{
	SEntidadCodNom *    p_entcnObj;
    SCodigo *           p_codEntidad;
    SNombre *           p_nomEntidad;

    p_codEntidad = SCodCrear ( iMaxTam );
    p_nomEntidad = SNomCrearDef ();
    p_entcnObj = SEntCodNomEncapsularExt ( p_codEntidad, p_nomEntidad, NULL );
    if ( ES_NULO ( p_entcnObj ) )
    {
        SCodDestruir ( &p_codEntidad );
        SNomDestruir ( &p_nomEntidad );
    }
    return ( p_entcnObj );
}

SEntidadCodNom * SEntCodNomCrear ( SCadena * p_cadValor, int iMaxTam, SCadena * p_cadNombre )
{
	return ( SEntCodNomCrearExt ( p_cadValor, iMaxTam, p_cadNombre, NULL ) );
}

SEntidadCodNom * SEntCodNomCrearLit ( const char * p_cValor, int iMaxTam, const char * p_cNombre )
{
	return ( SEntCodNomCrearLitExt ( p_cValor, iMaxTam, p_cNombre, NULL ) );
}

SEntidadCodNom * SEntCodNomCrearExt ( SCadena * p_cadValor, int iMaxTam, SCadena * p_cadNombre, void * p_vContenido )
{
	SEntidadCodNom *    p_entcnObj;
    SCodigo *           p_codEntidad;
    SNombre *           p_nomEntidad;

    p_codEntidad = SCodCrearValorExt ( p_cadValor, iMaxTam );
    p_nomEntidad = SNomCrearValor ( p_cadNombre );
    p_entcnObj = SEntCodNomEncapsularExt ( p_codEntidad, p_nomEntidad, p_vContenido );
    if ( ES_NULO ( p_entcnObj ) )
    {
        SCodDestruir ( &p_codEntidad );
        SNomDestruir ( &p_nomEntidad );
    }
    return ( p_entcnObj );
}

SEntidadCodNom * SEntCodNomCrearLitExt ( const char * p_cValor, int iMaxTam, const char * p_cNombre, void * p_vContenido )
{
	SEntidadCodNom *    p_entcnObj;
    SCodigo *           p_codEntidad;
    SNombre *           p_nomEntidad;

    p_codEntidad = SCodCrearValorLitExt ( p_cValor, iMaxTam );
    p_nomEntidad = SNomCrearValorLit ( p_cNombre );
    p_entcnObj = SEntCodNomEncapsularExt ( p_codEntidad, p_nomEntidad, p_vContenido );
    if ( ES_NULO ( p_entcnObj ) )
    {
        SCodDestruir ( &p_codEntidad );
        SNomDestruir ( &p_nomEntidad );
    }
    return ( p_entcnObj );
}

SEntidadCodNom * SEntCodNomEncapsular ( SCodigo * p_codEntidad, SNombre * p_nomEntidad )
{
	return ( SEntCodNomEncapsularExt ( p_codEntidad,  p_nomEntidad, NULL ) );
}

SEntidadCodNom * SEntCodNomEncapsularExt ( SCodigo * p_codEntidad, SNombre * p_nomEntidad, void * p_vContenido )
{
	SEntidadCodNom *	p_entcnObj;
	
    if ( ES_VALIDO ( p_codEntidad ) )
    {
        p_entcnObj = (SEntidadCodNom *) MemReservar ( sizeof ( SEntidadCodNom ) );
        if ( ES_VALIDO ( p_entcnObj ) )
        {
            p_entcnObj->p_entcInfo = SEntCodEncapsularExt ( p_codEntidad, p_vContenido );
            if ( ES_VALIDO ( p_entcnObj->p_entcInfo ) )
            {
				if ( ES_VALIDO ( p_nomEntidad ) )
				{
					p_entcnObj->p_nomEntidad = p_nomEntidad;
				}
				else
				{
					p_entcnObj->p_nomEntidad = SNomCrearDef ();					
				}
            }
            else
            {
                MemLiberar ( (void **) &p_entcnObj );
            }
        }
    }
    else
    {
        p_entcnObj = NULL;
    }
	return ( p_entcnObj );
}

void * SEntCodNomDestruir ( SEntidadCodNom ** p_p_entcnObj )
{
	SEntidadCodNom *   p_entcnObj;
    void *          p_vRes;

	if ( ES_VALIDO ( p_p_entcnObj ) )
	{
		p_entcnObj = *p_p_entcnObj;

		if ( ES_VALIDO ( p_entcnObj ) )
		{
			p_vRes = SEntCodDestruir ( &(p_entcnObj->p_entcInfo) );
            SNomDestruir ( &(p_entcnObj->p_nomEntidad) );
			MemLiberar ( (void **) p_p_entcnObj );
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

int SEntCodNomEsValida ( SEntidadCodNom * p_entcnObj )
{
	int iRes;

	if ( ES_VALIDO ( p_entcnObj ) )
	{
		/* Solo el identificador, delegando en la base. El nombre es opcional,
		   como el contenido: preguntarle a SNomEsValido si hace falta. */
		if ( SEntCodEsValida ( p_entcnObj->p_entcInfo ) == 1 )
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

SCodigo * SEntCodNomCodigo ( SEntidadCodNom * p_entcnObj )
{
	SCodigo * p_codRes;

	if ( ES_VALIDO ( p_entcnObj ) )
	{
		p_codRes = SEntCodCodigo ( p_entcnObj->p_entcInfo );
	}
	else
	{
		p_codRes = NULL;
	}
	return ( p_codRes );
}

SCadena * SEntCodNomValorCodigo ( SEntidadCodNom * p_entcnObj )
{
	SCadena * p_cadRes;

	if ( ES_VALIDO ( p_entcnObj ) )
	{
		p_cadRes = SEntCodValorCodigo ( p_entcnObj->p_entcInfo );
	}
	else
	{
		p_cadRes = NULL;
	}
	return ( p_cadRes );
}

const char * SEntCodNomValorCodigoLit ( SEntidadCodNom * p_entcnObj )
{
	const char * p_cRes;

	if ( ES_VALIDO ( p_entcnObj ) )
	{
		p_cRes = SEntCodValorCodigoLit ( p_entcnObj->p_entcInfo );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

SNombre * SEntCodNomNombre ( SEntidadCodNom * p_entcnObj )
{
	SNombre * p_nomRes;

	if ( ES_VALIDO ( p_entcnObj ) )
	{
		p_nomRes = p_entcnObj->p_nomEntidad;
	}
	else
	{
		p_nomRes = NULL;
	}
	return ( p_nomRes );
}

SCadena * SEntCodNomValorNombre ( SEntidadCodNom * p_entcnObj )
{
	SCadena * p_cadRes;

	if ( ES_VALIDO ( p_entcnObj ) )
	{
		p_cadRes = SNomValor ( p_entcnObj->p_nomEntidad );
	}
	else
	{
		p_cadRes = NULL;
	}
	return ( p_cadRes );
}

const char * SEntCodNomValorNombreLit ( SEntidadCodNom * p_entcnObj )
{
	const char * p_cRes;

	if ( ES_VALIDO ( p_entcnObj ) )
	{
		p_cRes = SNomValorLit ( p_entcnObj->p_nomEntidad );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

SEntidadCod * SEntCodNomBase ( SEntidadCodNom * p_entcnObj )
{
	SEntidadCod * p_entcRes;

	if ( ES_VALIDO ( p_entcnObj ) )
	{
		p_entcRes = p_entcnObj->p_entcInfo;
	}
	else
	{
		p_entcRes = NULL;
	}
	return ( p_entcRes );
}

int SEntCodNomEstablecerCodigo ( SEntidadCodNom * p_entcnObj, SCodigo * p_codEntidad )
{
	int iRes;

	if ( ES_VALIDO ( p_entcnObj ) )
	{
		if ( SEntCodEstablecerCodigo ( p_entcnObj->p_entcInfo, p_codEntidad ) == 1 )
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

int SEntCodNomEstablecerValorCodigo ( SEntidadCodNom * p_entcnObj, SCadena * p_cadValor )
{
	int iRes;

	if ( ES_VALIDO ( p_entcnObj ) )
	{
		if ( SEntCodEstablecerValorCodigo ( p_entcnObj->p_entcInfo, p_cadValor ) == 1 )
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

int SEntCodNomEstablecerValorCodigoLit ( SEntidadCodNom * p_entcnObj, const char * p_cValor )
{
	int iRes;

	if ( ES_VALIDO ( p_entcnObj ) )
	{
		if ( SEntCodEstablecerValorCodigoLit ( p_entcnObj->p_entcInfo, p_cValor ) == 1 )
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

void * SEntCodNomContenido ( SEntidadCodNom * p_entcnObj )
{
	void * p_vRes;

	if ( ES_VALIDO ( p_entcnObj ) )
	{
		p_vRes = SEntCodContenido ( p_entcnObj->p_entcInfo );
	}
	else
	{
		p_vRes = NULL;
	}
	return ( p_vRes );
}

void * SEntCodNomEstablecerContenido ( SEntidadCodNom * p_entcnObj, void * p_vContenido )
{
	void * p_vRes;

	if ( ES_VALIDO ( p_entcnObj ) )
	{
        p_vRes = SEntCodEstablecerContenido ( p_entcnObj->p_entcInfo, p_vContenido );
	}
	else
	{
		p_vRes = NULL;
	}
	return ( p_vRes );
}

int SEntCodNomEstablecerNombre ( SEntidadCodNom * p_entcnObj, SNombre * p_nomEntidad )
{
	int iRes;

	if ( ES_VALIDO ( p_entcnObj ) )
	{
		if ( SNomAsignar ( p_entcnObj->p_nomEntidad, p_nomEntidad ) == 1 )
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

int SEntCodNomEstablecerValorNombre ( SEntidadCodNom * p_entcnObj, SCadena * p_cadNombre )
{
	int iRes;

	if ( ES_VALIDO ( p_entcnObj ) )
	{
		if ( SNomEstablecer ( p_entcnObj->p_nomEntidad, p_cadNombre ) == 1 )
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

int SEntCodNomEstablecerValorNombreLit ( SEntidadCodNom * p_entcnObj, const char * p_cNombre )
{
	int iRes;

	if ( ES_VALIDO ( p_entcnObj ) )
	{
		if ( SNomEstablecerLit ( p_entcnObj->p_nomEntidad, p_cNombre ) == 1 )
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

int SEntCodNomEsIgual ( SEntidadCodNom * p_entcnObj, SEntidadCodNom * p_entcnVal )
{
	int iRes;

	if ( ES_VALIDO ( p_entcnObj ) && ES_VALIDO ( p_entcnVal ) )
	{
		iRes = SCodEsIgual ( SEntCodNomCodigo ( p_entcnObj ), SEntCodNomCodigo ( p_entcnVal ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SEntCodNomEsMenor ( SEntidadCodNom * p_entcnObj, SEntidadCodNom * p_entcnVal )
{
	int iRes;

	if ( ES_VALIDO ( p_entcnObj ) && ES_VALIDO ( p_entcnVal ) )
	{
		iRes = SCodEsMenor ( SEntCodNomCodigo ( p_entcnObj ), SEntCodNomCodigo ( p_entcnVal ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SEntCodNomEsMayor ( SEntidadCodNom * p_entcnObj, SEntidadCodNom * p_entcnVal )
{
	int iRes;

	if ( ES_VALIDO ( p_entcnObj ) && ES_VALIDO ( p_entcnVal ) )
	{
		iRes = SCodEsMayor ( SEntCodNomCodigo ( p_entcnObj ), SEntCodNomCodigo ( p_entcnVal ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SEntCodNomEsMenorIg ( SEntidadCodNom * p_entcnObj, SEntidadCodNom * p_entcnVal )
{
	int iRes;

	if ( ES_VALIDO ( p_entcnObj ) && ES_VALIDO ( p_entcnVal ) )
	{
		iRes = SCodEsMenorIg ( SEntCodNomCodigo ( p_entcnObj ), SEntCodNomCodigo ( p_entcnVal ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SEntCodNomEsMayorIg ( SEntidadCodNom * p_entcnObj, SEntidadCodNom * p_entcnVal )
{
	int iRes;

	if ( ES_VALIDO ( p_entcnObj ) && ES_VALIDO ( p_entcnVal ) )
	{
		iRes = SCodEsMayorIg ( SEntCodNomCodigo ( p_entcnObj ), SEntCodNomCodigo ( p_entcnVal ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SEntCodNomEsIgualEnt ( SEntidadCodNom * p_entcnObj, SEntidadCod * p_entcVal )
{
	int iRes;

	if ( ES_VALIDO ( p_entcnObj ) && ES_VALIDO ( p_entcVal ) )
	{
		iRes = SCodEsIgual ( SEntCodNomCodigo ( p_entcnObj ), SEntCodCodigo ( p_entcVal ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SEntCodNomEsMenorEnt ( SEntidadCodNom * p_entcnObj, SEntidadCod * p_entcVal )
{
	int iRes;

	if ( ES_VALIDO ( p_entcnObj ) && ES_VALIDO ( p_entcVal ) )
	{
		iRes = SCodEsMenor ( SEntCodNomCodigo ( p_entcnObj ), SEntCodCodigo ( p_entcVal ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SEntCodNomEsMayorEnt ( SEntidadCodNom * p_entcnObj, SEntidadCod * p_entcVal )
{
	int iRes;

	if ( ES_VALIDO ( p_entcnObj ) && ES_VALIDO ( p_entcVal ) )
	{
		iRes = SCodEsMayor ( SEntCodNomCodigo ( p_entcnObj ), SEntCodCodigo ( p_entcVal ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SEntCodNomEsMenorIgEnt ( SEntidadCodNom * p_entcnObj, SEntidadCod * p_entcVal )
{
	int iRes;

	if ( ES_VALIDO ( p_entcnObj ) && ES_VALIDO ( p_entcVal ) )
	{
		iRes = SCodEsMenorIg ( SEntCodNomCodigo ( p_entcnObj ), SEntCodCodigo ( p_entcVal ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SEntCodNomEsMayorIgEnt ( SEntidadCodNom * p_entcnObj, SEntidadCod * p_entcVal )
{
	int iRes;

	if ( ES_VALIDO ( p_entcnObj ) && ES_VALIDO ( p_entcVal ) )
	{
		iRes = SCodEsMayorIg ( SEntCodNomCodigo ( p_entcnObj ), SEntCodCodigo ( p_entcVal ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SEntCodNomEsIgualCodigo ( SEntidadCodNom * p_entcnObj, SCodigo * p_codVal )
{
	int iRes;

	if ( ES_VALIDO ( p_entcnObj ) && ES_VALIDO ( p_codVal ) )
	{
		iRes = SCodEsIgualLit ( SEntCodNomCodigo ( p_entcnObj ), SCodValorLit ( p_codVal ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SEntCodNomEsMenorCodigo ( SEntidadCodNom * p_entcnObj, SCodigo * p_codVal )
{
	int iRes;

	if ( ES_VALIDO ( p_entcnObj ) && ES_VALIDO ( p_codVal ) )
	{
		iRes = SCodEsMenorLit ( SEntCodNomCodigo ( p_entcnObj ), SCodValorLit ( p_codVal ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SEntCodNomEsMayorCodigo ( SEntidadCodNom * p_entcnObj, SCodigo * p_codVal )
{
	int iRes;

	if ( ES_VALIDO ( p_entcnObj ) && ES_VALIDO ( p_codVal ) )
	{
		iRes = SCodEsMayorLit ( SEntCodNomCodigo ( p_entcnObj ), SCodValorLit ( p_codVal ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SEntCodNomEsMenorIgCodigo ( SEntidadCodNom * p_entcnObj, SCodigo * p_codVal )
{
	int iRes;

	if ( ES_VALIDO ( p_entcnObj ) && ES_VALIDO ( p_codVal ) )
	{
		iRes = SCodEsMenorIgLit ( SEntCodNomCodigo ( p_entcnObj ), SCodValorLit ( p_codVal ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SEntCodNomEsMayorIgCodigo ( SEntidadCodNom * p_entcnObj, SCodigo * p_codVal )
{
	int iRes;

	if ( ES_VALIDO ( p_entcnObj ) && ES_VALIDO ( p_codVal ) )
	{
		iRes = SCodEsMayorIgLit ( SEntCodNomCodigo ( p_entcnObj ), SCodValorLit ( p_codVal ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SEntCodNomEsIgualCad ( SEntidadCodNom * p_entcnObj, SCadena * p_cadVal )
{
	int iRes;

	if ( ES_VALIDO ( p_entcnObj ) && ES_VALIDO ( p_cadVal ) )
	{
		iRes = SCodEsIgualCad ( SEntCodNomCodigo ( p_entcnObj ), p_cadVal );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SEntCodNomEsMenorCad ( SEntidadCodNom * p_entcnObj, SCadena * p_cadVal )
{
	int iRes;

	if ( ES_VALIDO ( p_entcnObj ) && ES_VALIDO ( p_cadVal ) )
	{
		iRes = SCodEsMenorCad ( SEntCodNomCodigo ( p_entcnObj ), p_cadVal );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SEntCodNomEsMayorCad ( SEntidadCodNom * p_entcnObj, SCadena * p_cadVal )
{
	int iRes;

	if ( ES_VALIDO ( p_entcnObj ) && ES_VALIDO ( p_cadVal ) )
	{
		iRes = SCodEsMayorCad ( SEntCodNomCodigo ( p_entcnObj ), p_cadVal );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SEntCodNomEsMenorIgCad ( SEntidadCodNom * p_entcnObj, SCadena * p_cadVal )
{
	int iRes;

	if ( ES_VALIDO ( p_entcnObj ) && ES_VALIDO ( p_cadVal ) )
	{
		iRes = SCodEsMenorIgCad ( SEntCodNomCodigo ( p_entcnObj ), p_cadVal );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SEntCodNomEsMayorIgCad ( SEntidadCodNom * p_entcnObj, SCadena * p_cadVal )
{
	int iRes;

	if ( ES_VALIDO ( p_entcnObj ) && ES_VALIDO ( p_cadVal ) )
	{
		iRes = SCodEsMayorIgCad ( SEntCodNomCodigo ( p_entcnObj ), p_cadVal );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SEntCodNomEsIgualLit ( SEntidadCodNom * p_entcnObj, const char * p_cVal )
{
	int iRes;

	if ( ES_VALIDO ( p_entcnObj ) ) 
	{
		iRes = SCodEsIgualLit ( SEntCodNomCodigo ( p_entcnObj ), p_cVal );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SEntCodNomEsMenorLit ( SEntidadCodNom * p_entcnObj, const char * p_cVal )
{
	int iRes;

	if ( ES_VALIDO ( p_entcnObj ) ) 
	{
		iRes = SCodEsMenorLit ( SEntCodNomCodigo ( p_entcnObj ), p_cVal );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SEntCodNomEsMayorLit ( SEntidadCodNom * p_entcnObj, const char * p_cVal )
{
	int iRes;

	if ( ES_VALIDO ( p_entcnObj ) ) 
	{
		iRes = SCodEsMayorLit ( SEntCodNomCodigo ( p_entcnObj ), p_cVal );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SEntCodNomEsMenorIgLit ( SEntidadCodNom * p_entcnObj, const char * p_cVal )
{
	int iRes;

	if ( ES_VALIDO ( p_entcnObj ) ) 
	{
		iRes = SCodEsMenorIgLit ( SEntCodNomCodigo ( p_entcnObj ), p_cVal );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SEntCodNomEsMayorIgLit ( SEntidadCodNom * p_entcnObj, const char * p_cVal )
{
	int iRes;

	if ( ES_VALIDO ( p_entcnObj ) ) 
	{
		iRes = SCodEsMayorIgLit ( SEntCodNomCodigo ( p_entcnObj ), p_cVal );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}


int SEntCodNomComparar ( SEntidadCodNom * p_entcnObj, SEntidadCodNom * p_entcnVal )
{
	int iRes;

	if ( ES_VALIDO ( p_entcnObj ) && ES_VALIDO ( p_entcnVal ) )
	{
        iRes = SEntCodCompararCodigo ( p_entcnObj->p_entcInfo, SEntCodNomCodigo ( p_entcnVal ) );
		if ( iRes == COMP_IGUAL )
        {
            iRes = SNomComparar ( p_entcnObj->p_nomEntidad, SEntCodNomNombre ( p_entcnVal ) );
        }
	}
	else if  ( ES_VALIDO ( p_entcnObj ) )
	{
		iRes = COMP_MAYOR;
	}
	else if  ( ES_VALIDO ( p_entcnVal ) )
	{
		iRes = COMP_MENOR;
	}
	else
	{
		iRes = COMP_IGUAL;
	}
	return ( iRes );
}

int SEntCodNomCompararEnt ( SEntidadCodNom * p_entcnObj, SEntidadCod * p_entcVal )
{
	int iRes;

	if ( ES_VALIDO ( p_entcnObj ) && ES_VALIDO ( p_entcVal ) )
	{
		iRes = SEntCodComparar ( p_entcnObj->p_entcInfo, p_entcVal );
	}
	else if  ( ES_VALIDO ( p_entcnObj ) )
	{
		iRes = COMP_MAYOR;
	}
	else if  ( ES_VALIDO ( p_entcVal ) )
	{
		iRes = COMP_MENOR;
	}
	else
	{
		iRes = COMP_IGUAL;
	}
	return ( iRes );
}

int SEntCodNomCompararId ( SEntidadCodNom * p_entcnObj, SCodigo * p_codVal )
{
	int iRes;

	if ( ES_VALIDO ( p_entcnObj ) )
	{
		iRes = SCodComparar ( SEntCodNomCodigo ( p_entcnObj ), p_codVal );
	}
	else if  ( ES_VALIDO ( p_codVal ) )
	{
		iRes = COMP_MENOR;
	}
	else
	{
		iRes = COMP_IGUAL;
	}
	return ( iRes );
}

int SEntCodNomCompararCad ( SEntidadCodNom * p_entcnObj, SCadena * p_cadVal )
{
	int iRes;

	if ( ES_VALIDO ( p_entcnObj ) ) 
	{
		iRes = SCodCompararCad ( SEntCodNomCodigo ( p_entcnObj ), p_cadVal );
	}
	else
	{
		iRes = COMP_MENOR;
	}
	return ( iRes );
}

int SEntCodNomCompararLit ( SEntidadCodNom * p_entcnObj, const char * p_cVal )
{
	int iRes;

	if ( ES_VALIDO ( p_entcnObj ) ) 
	{
		iRes = SCodCompararLit ( SEntCodNomCodigo ( p_entcnObj ), p_cVal );
	}
	else
	{
		iRes = COMP_MENOR;
	}
	return ( iRes );
}

unsigned int SEntCodNomHash ( SEntidadCodNom * p_entcnObj )
{
	unsigned int uiRes = 0;

	if ( ES_VALIDO ( p_entcnObj ) )
	{
		/* Solo el codigo, delegando en la clase base: el hash tiene que ir de la
		   mano de SEntCodNomEsIgual, que tampoco mira el nombre. Ademas el
		   nombre es mutable ( SEntCodNomEstablecerNombre y companeras ), asi
		   que meterlo aqui dejaria fuera de su cubeta a toda entidad a la que
		   se le cambie. Delegando, un SEntidadCodNom y su SEntidadCod base
		   reparten igual. */
		uiRes = SEntCodHash ( p_entcnObj->p_entcInfo );
	}
	return ( uiRes );
}


