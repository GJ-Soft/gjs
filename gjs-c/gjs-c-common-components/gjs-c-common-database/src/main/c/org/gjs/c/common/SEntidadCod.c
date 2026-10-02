
#include "SEntidadCod.h"

#include "TiposBaseDatosConfig.h"



SEntidadCod * SEntCodCrearDef ( int iMaxTam )
{
	SEntidadCod *  p_entcObj;
    SCodigo *      p_codEntidad;

    p_codEntidad = SCodCrear ( iMaxTam );
    p_entcObj = SEntCodEncapsularExt ( p_codEntidad, NULL );
    if ( ES_NULO ( p_entcObj ) )
    {
        SCodDestruir ( &p_codEntidad );
    }
    return ( p_entcObj );
}

SEntidadCod * SEntCodCrear ( SCadena * p_cadValor, int iMaxTam )
{
	return ( SEntCodCrearExt ( p_cadValor, iMaxTam, NULL ) );
}

SEntidadCod * SEntCodCrearLit ( const char * p_cValor, int iMaxTam )
{
	return ( SEntCodCrearLitExt ( p_cValor, iMaxTam, NULL ) );
}

SEntidadCod * SEntCodCrearExt ( SCadena * p_cadValor, int iMaxTam, void * p_vContenido )
{
	SEntidadCod *  p_entcObj;
    SCodigo *      p_codEntidad;

    p_codEntidad = SCodCrearValorExt ( p_cadValor, iMaxTam );
    p_entcObj = SEntCodEncapsularExt ( p_codEntidad, p_vContenido );
    if ( ES_NULO ( p_entcObj ) )
    {
        SCodDestruir ( &p_codEntidad );
    }
    return ( p_entcObj );
}

SEntidadCod * SEntCodCrearLitExt ( const char * p_cValor, int iMaxTam, void * p_vContenido )
{
	SEntidadCod *  p_entcObj;
    SCodigo *      p_codEntidad;

    p_codEntidad = SCodCrearValorLitExt ( p_cValor, iMaxTam );
    p_entcObj = SEntCodEncapsularExt ( p_codEntidad, p_vContenido );
    if ( ES_NULO ( p_entcObj ) )
    {
        SCodDestruir ( &p_codEntidad );
    }
    return ( p_entcObj );
}

SEntidadCod * SEntCodEncapsular ( SCodigo * p_codEntidad )
{
	return ( SEntCodEncapsularExt ( p_codEntidad, NULL ) );
}

SEntidadCod * SEntCodEncapsularExt ( SCodigo * p_codEntidad, void * p_vContenido )
{
	SEntidadCod *	p_entcObj;
	
    if ( ES_VALIDO ( p_codEntidad ) )
    {
        p_entcObj= (SEntidadCod *) MemReservar ( sizeof ( SEntidadCod ) );
        if ( ES_VALIDO ( p_entcObj ) )
        {
            p_entcObj->p_codEntidad = p_codEntidad;
            p_entcObj->p_vContenido = p_vContenido;
        }
    }
    else
    {
        p_entcObj = NULL;
    }
	return ( p_entcObj );
}

void * SEntCodDestruir ( SEntidadCod ** p_p_entcObj )
{
	SEntidadCod *   p_entcObj;
    void *          p_vRes;

	if ( ES_VALIDO ( p_p_entcObj ) )
	{
		p_entcObj = *p_p_entcObj;

		if ( ES_VALIDO ( p_entcObj ) )
		{
			p_vRes = p_entcObj->p_vContenido;
            SCodDestruir ( &(p_entcObj->p_codEntidad) );
			MemLiberar ( (void **) p_p_entcObj );
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

int SEntCodEsValida ( SEntidadCod * p_entcObj )
{
	int iRes;

	if ( ES_VALIDO ( p_entcObj ) )
	{
		/* Solo el identificador. El contenido es opcional a proposito ( para eso
		   estan SEntCodCrear y SEntCodCrearExt ), asi que exigirlo aqui haria
		   invalida a toda entidad creada sin el. */
		if ( SCodEsValido ( p_entcObj->p_codEntidad ) == 1 )
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

SCodigo * SEntCodCodigo ( SEntidadCod * p_entcObj )
{
	SCodigo * p_codRes;

	if ( ES_VALIDO ( p_entcObj ) )
	{
		p_codRes = p_entcObj->p_codEntidad;
	}
	else
	{
		p_codRes = NULL;
	}
	return ( p_codRes );
}

SCadena * SEntCodValorCodigo ( SEntidadCod * p_entcObj )
{
	SCadena * p_cadRes;

	if ( ES_VALIDO ( p_entcObj ) )
	{
		p_cadRes = SCodValor ( p_entcObj->p_codEntidad );
	}
	else
	{
		p_cadRes = NULL;
	}
	return ( p_cadRes );
}

const char * SEntCodValorCodigoLit ( SEntidadCod * p_entcObj )
{
	const char * p_cRes;

	if ( ES_VALIDO ( p_entcObj ) )
	{
		p_cRes = SCodValorLit ( p_entcObj->p_codEntidad );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

int SEntCodEstablecerCodigo ( SEntidadCod * p_entcObj, SCodigo * p_codEntidad )
{
	int iRes;

	if ( ES_VALIDO ( p_entcObj ) )
	{
		if ( SCodAsignar ( p_entcObj->p_codEntidad, p_codEntidad ) == 1 )
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

int SEntCodEstablecerValorCodigo ( SEntidadCod * p_entcObj, SCadena * p_cadValor )
{
	int iRes;

	if ( ES_VALIDO ( p_entcObj ) )
	{
		if ( SCodEstablecer ( p_entcObj->p_codEntidad, p_cadValor ) == 1 )
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

int SEntCodEstablecerValorCodigoLit ( SEntidadCod * p_entcObj, const char * p_cValor )
{
	int iRes;

	if ( ES_VALIDO ( p_entcObj ) )
	{
		if ( SCodEstablecerLit ( p_entcObj->p_codEntidad, p_cValor ) == 1 )
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

void * SEntCodContenido ( SEntidadCod * p_entcObj )
{
	void * p_vRes;

	if ( ES_VALIDO ( p_entcObj ) )
	{
		p_vRes = p_entcObj->p_vContenido;
	}
	else
	{
		p_vRes = NULL;
	}
	return ( p_vRes );
}

void * SEntCodEstablecerContenido ( SEntidadCod * p_entcObj, void * p_vContenido )
{
	void * p_vRes;

	if ( ES_VALIDO ( p_entcObj ) )
	{
		p_vRes = p_entcObj->p_vContenido;
        p_entcObj->p_vContenido = p_vContenido;
	}
	else
	{
		p_vRes = NULL;
	}
	return ( p_vRes );
}

int SEntCodEsIgual ( SEntidadCod * p_entcObj, SEntidadCod * p_entcVal )
{
	int iRes;

	if ( ES_VALIDO ( p_entcObj ) && ES_VALIDO ( p_entcVal ) )
	{
		iRes = SCodEsIgual ( p_entcObj->p_codEntidad, SEntCodCodigo ( p_entcVal ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SEntCodEsMenor ( SEntidadCod * p_entcObj, SEntidadCod * p_entcVal )
{
	int iRes;

	if ( ES_VALIDO ( p_entcObj ) && ES_VALIDO ( p_entcVal ) )
	{
		iRes = SCodEsMenor ( p_entcObj->p_codEntidad, SEntCodCodigo ( p_entcVal ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SEntCodEsMayor ( SEntidadCod * p_entcObj, SEntidadCod * p_entcVal )
{
	int iRes;

	if ( ES_VALIDO ( p_entcObj ) && ES_VALIDO ( p_entcVal ) )
	{
		iRes = SCodEsMayor ( p_entcObj->p_codEntidad, SEntCodCodigo ( p_entcVal ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SEntCodEsMenorIg ( SEntidadCod * p_entcObj, SEntidadCod * p_entcVal )
{
	int iRes;

	if ( ES_VALIDO ( p_entcObj ) && ES_VALIDO ( p_entcVal ) )
	{
		iRes = SCodEsMenorIg ( p_entcObj->p_codEntidad, SEntCodCodigo ( p_entcVal ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SEntCodEsMayorIg ( SEntidadCod * p_entcObj, SEntidadCod * p_entcVal )
{
	int iRes;

	if ( ES_VALIDO ( p_entcObj ) && ES_VALIDO ( p_entcVal ) )
	{
		iRes = SCodEsMayorIg ( p_entcObj->p_codEntidad, SEntCodCodigo ( p_entcVal ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SEntCodEsIgualCodigo ( SEntidadCod * p_entcObj, SCodigo * p_codVal )
{
	int iRes;

	if ( ES_VALIDO ( p_entcObj ) && ES_VALIDO ( p_codVal ) )
	{
		iRes = SCodEsIgualLit ( p_entcObj->p_codEntidad, SCodValorLit ( p_codVal ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SEntCodEsMenorCodigo ( SEntidadCod * p_entcObj, SCodigo * p_codVal )
{
	int iRes;

	if ( ES_VALIDO ( p_entcObj ) && ES_VALIDO ( p_codVal ) )
	{
		iRes = SCodEsMenorLit ( p_entcObj->p_codEntidad, SCodValorLit ( p_codVal ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SEntCodEsMayorCodigo ( SEntidadCod * p_entcObj, SCodigo * p_codVal )
{
	int iRes;

	if ( ES_VALIDO ( p_entcObj ) && ES_VALIDO ( p_codVal ) )
	{
		iRes = SCodEsMayorLit ( p_entcObj->p_codEntidad, SCodValorLit ( p_codVal ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SEntCodEsMenorIgCodigo ( SEntidadCod * p_entcObj, SCodigo * p_codVal )
{
	int iRes;

	if ( ES_VALIDO ( p_entcObj ) && ES_VALIDO ( p_codVal ) )
	{
		iRes = SCodEsMenorIgLit ( p_entcObj->p_codEntidad, SCodValorLit ( p_codVal ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SEntCodEsMayorIgCodigo ( SEntidadCod * p_entcObj, SCodigo * p_codVal )
{
	int iRes;

	if ( ES_VALIDO ( p_entcObj ) && ES_VALIDO ( p_codVal ) )
	{
		iRes = SCodEsMayorIgLit ( p_entcObj->p_codEntidad, SCodValorLit ( p_codVal ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SEntCodEsIgualCad ( SEntidadCod * p_entcObj, SCadena * p_cadVal )
{
	int iRes;

	if ( ES_VALIDO ( p_entcObj ) && ES_VALIDO ( p_cadVal ) )
	{
		iRes = SCodEsIgualCad ( p_entcObj->p_codEntidad, p_cadVal );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SEntCodEsMenorCad ( SEntidadCod * p_entcObj, SCadena * p_cadVal )
{
	int iRes;

	if ( ES_VALIDO ( p_entcObj ) && ES_VALIDO ( p_cadVal ) )
	{
		iRes = SCodEsMenorCad ( p_entcObj->p_codEntidad, p_cadVal );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SEntCodEsMayorCad ( SEntidadCod * p_entcObj, SCadena * p_cadVal )
{
	int iRes;

	if ( ES_VALIDO ( p_entcObj ) && ES_VALIDO ( p_cadVal ) )
	{
		iRes = SCodEsMayorCad ( p_entcObj->p_codEntidad, p_cadVal );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SEntCodEsMenorIgCad ( SEntidadCod * p_entcObj, SCadena * p_cadVal )
{
	int iRes;

	if ( ES_VALIDO ( p_entcObj ) && ES_VALIDO ( p_cadVal ) )
	{
		iRes = SCodEsMenorIgCad ( p_entcObj->p_codEntidad, p_cadVal );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SEntCodEsMayorIgCad ( SEntidadCod * p_entcObj, SCadena * p_cadVal )
{
	int iRes;

	if ( ES_VALIDO ( p_entcObj ) && ES_VALIDO ( p_cadVal ) )
	{
		iRes = SCodEsMayorIgCad ( p_entcObj->p_codEntidad, p_cadVal );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SEntCodEsIgualLit ( SEntidadCod * p_entcObj, const char * p_cVal )
{
	int iRes;

	if ( ES_VALIDO ( p_entcObj ) ) 
	{
		iRes = SCodEsIgualLit ( p_entcObj->p_codEntidad, p_cVal );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SEntCodEsMenorLit ( SEntidadCod * p_entcObj, const char * p_cVal )
{
	int iRes;

	if ( ES_VALIDO ( p_entcObj ) ) 
	{
		iRes = SCodEsMenorLit ( p_entcObj->p_codEntidad, p_cVal );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SEntCodEsMayorLit ( SEntidadCod * p_entcObj, const char * p_cVal )
{
	int iRes;

	if ( ES_VALIDO ( p_entcObj ) ) 
	{
		iRes = SCodEsMayorLit ( p_entcObj->p_codEntidad, p_cVal );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SEntCodEsMenorIgLit ( SEntidadCod * p_entcObj, const char * p_cVal )
{
	int iRes;

	if ( ES_VALIDO ( p_entcObj ) ) 
	{
		iRes = SCodEsMenorIgLit ( p_entcObj->p_codEntidad, p_cVal );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SEntCodEsMayorIgLit ( SEntidadCod * p_entcObj, const char * p_cVal )
{
	int iRes;

	if ( ES_VALIDO ( p_entcObj ) ) 
	{
		iRes = SCodEsMayorIgLit ( p_entcObj->p_codEntidad, p_cVal );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SEntCodComparar ( SEntidadCod * p_entcObj, SEntidadCod * p_entcVal )
{
	int iRes;

	if ( ES_VALIDO ( p_entcObj ) && ES_VALIDO ( p_entcVal ) )
	{
		iRes = SEntCodCompararCodigo ( p_entcObj, SEntCodCodigo ( p_entcVal ) );
	}
	else if  ( ES_VALIDO ( p_entcObj ) )
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

int SEntCodCompararCodigo ( SEntidadCod * p_entcObj, SCodigo * p_codVal )
{
	int iRes;

	if ( ES_VALIDO ( p_entcObj ) )
	{
		iRes = SCodComparar ( SEntCodCodigo ( p_entcObj ), p_codVal );
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


int SEntCodCompararCad ( SEntidadCod * p_entcObj, SCadena * p_cadVal )
{
	int iRes;

	if ( ES_VALIDO ( p_entcObj ) )
	{
		iRes = SCadComparar ( SEntCodValorCodigo ( p_entcObj ), p_cadVal );
	}
	else if  ( ES_VALIDO ( p_cadVal ) )
	{
		iRes = COMP_MENOR;
	}
	else
	{
		iRes = COMP_IGUAL;
	}
	return ( iRes );
}

int SEntCodCompararLit ( SEntidadCod * p_entcObj, const char * p_cVal )
{
	int iRes;

	if ( ES_VALIDO ( p_entcObj ) ) 
	{
		iRes = SCodCompararLit ( SEntCodCodigo ( p_entcObj ), p_cVal );
	}
	else
	{
		iRes = COMP_MENOR;
	}
	return ( iRes );
}

unsigned int SEntCodHash ( SEntidadCod * p_entcObj )
{
	unsigned int uiRes = 0;

	if ( ES_VALIDO ( p_entcObj ) )
	{
		uiRes = SCodHash ( p_entcObj->p_codEntidad );
	}
	return ( uiRes );
}


