
#include "SEntidadIdCod.h"

#include "TiposBaseDatosConfig.h"





SEntidadIdCod * SEntIdCodCrearDef ( int iMaxTamCod )
{
	SEntidadIdCod * p_enticObj;
    SId *           p_idEntidad;
    SCodigo *       p_codEntidad;

    p_idEntidad = SIdCrearDef ();
    p_codEntidad = SCodCrear ( iMaxTamCod );
    p_enticObj = SEntIdCodEncapsularExt ( p_idEntidad, p_codEntidad, NULL );
    if ( ES_NULO ( p_enticObj ) )
    {
        SIdDestruir ( &p_idEntidad );
        SCodDestruir ( &p_codEntidad );
    }
    return ( p_enticObj );
}

SEntidadIdCod * SEntIdCodCrear ( unsigned long ulId, SCadena * p_cadCodigo, int iMaxTamCod )
{
	return ( SEntIdCodCrearExt ( ulId, p_cadCodigo, iMaxTamCod, NULL ) );
}

SEntidadIdCod * SEntIdCodCrearLit ( unsigned long ulId, const char * p_cCodigo, int iMaxTamCod )
{
	return ( SEntIdCodCrearLitExt ( ulId, p_cCodigo, iMaxTamCod, NULL ) );
}

SEntidadIdCod * SEntIdCodCrearExt ( unsigned long ulId, SCadena * p_cadCodigo, int iMaxTamCod, void * p_vContenido )
{
	SEntidadIdCod * p_enticObj;
    SId *           p_idEntidad;
    SCodigo *       p_codEntidad;

    p_idEntidad = SIdCrear ( ulId );
    p_codEntidad = SCodCrearValorExt ( p_cadCodigo, iMaxTamCod );
    p_enticObj = SEntIdCodEncapsularExt ( p_idEntidad, p_codEntidad, p_vContenido );
    if ( ES_NULO ( p_enticObj ) )
    {
        SIdDestruir ( &p_idEntidad );
        SCodDestruir ( &p_codEntidad );
    }
    return ( p_enticObj );
}

SEntidadIdCod * SEntIdCodCrearLitExt ( unsigned long ulId, const char * p_cCodigo, int iMaxTamCod, void * p_vContenido )
{
	SEntidadIdCod * p_enticObj;
    SId *           p_idEntidad;
    SCodigo *       p_codEntidad;

    p_idEntidad = SIdCrear ( ulId );
    p_codEntidad = SCodCrearValorLitExt ( p_cCodigo, iMaxTamCod );
    p_enticObj = SEntIdCodEncapsularExt ( p_idEntidad, p_codEntidad, p_vContenido );
    if ( ES_NULO ( p_enticObj ) )
    {
        SIdDestruir ( &p_idEntidad );
        SCodDestruir ( &p_codEntidad );
    }
    return ( p_enticObj );
}

SEntidadIdCod * SEntIdCodEncapsular ( SId * p_idEntidad, SCodigo * p_codEntidad )
{
	return ( SEntIdCodEncapsularExt ( p_idEntidad, p_codEntidad, NULL ) );
}

SEntidadIdCod * SEntIdCodEncapsularExt ( SId * p_idEntidad, SCodigo * p_codEntidad, void * p_vContenido )
{
	SEntidadIdCod *	p_enticObj;
	
    if ( ES_VALIDO ( p_idEntidad ) && ES_VALIDO ( p_codEntidad ) )
    {
        p_enticObj = (SEntidadIdCod *) MemReservar ( sizeof ( SEntidadIdCod ) );
        if ( ES_VALIDO ( p_enticObj ) )
        {
            p_enticObj->p_entInfo = SEntEncapsularExt ( p_idEntidad, p_vContenido );
            if ( ES_VALIDO ( p_enticObj->p_entInfo ) )
            {
                p_enticObj->p_codEntidad = p_codEntidad;
            }
            else
            {
                MemLiberar ( (void **) &p_enticObj );
            }
        }
    }
	else
	{
		p_enticObj = NULL;
	}
	return ( p_enticObj );
}

void * SEntIdCodDestruir ( SEntidadIdCod ** p_p_enticObj )
{
	SEntidadIdCod * p_enticObj;
    void *          p_vRes;

	if ( ES_VALIDO ( p_p_enticObj ) )
	{
		p_enticObj = *p_p_enticObj;

		if ( ES_VALIDO ( p_enticObj ) )
		{
			p_vRes = SEntDestruir ( &(p_enticObj->p_entInfo) );
            SCodDestruir ( &(p_enticObj->p_codEntidad) );
			MemLiberar ( (void **) p_p_enticObj );
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

int SEntIdCodEsValida ( SEntidadIdCod * p_enticObj )
{
	int iRes;

	if ( ES_VALIDO ( p_enticObj ) )
	{
		/* Solo el identificador, delegando en la base. El codigo es opcional,
		   como el contenido: preguntarle a SCodEsValido si hace falta. */
		if ( SEntEsValida ( p_enticObj->p_entInfo ) == 1 )
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

SId * SEntIdCodId ( SEntidadIdCod * p_enticObj )
{
	SId * p_idRes;

	if ( ES_VALIDO ( p_enticObj ) )
	{
		p_idRes = SEntId ( p_enticObj->p_entInfo );
	}
	else
	{
		p_idRes = NULL;
	}
	return ( p_idRes );
}

unsigned long SEntIdCodValorId ( SEntidadIdCod * p_enticObj )
{
	unsigned long ulRes;

	if ( ES_VALIDO ( p_enticObj ) )
	{
		ulRes = SEntValorId ( p_enticObj->p_entInfo );
	}
	else
	{
		ulRes = 0;
	}
	return ( ulRes );
}

SCodigo * SEntIdCodCodigo ( SEntidadIdCod * p_enticObj )
{
	SCodigo * p_codRes;

	if ( ES_VALIDO ( p_enticObj ) )
	{
		p_codRes = p_enticObj->p_codEntidad;
	}
	else
	{
		p_codRes = NULL;
	}
	return ( p_codRes );
}

SCadena * SEntIdCodValorCodigo ( SEntidadIdCod * p_enticObj )
{
	SCadena * p_cadRes;

	if ( ES_VALIDO ( p_enticObj ) )
	{
		p_cadRes = SCodValor ( p_enticObj->p_codEntidad );
	}
	else
	{
		p_cadRes = NULL;
	}
	return ( p_cadRes );
}

const char * SEntIdCodValorCodigoLit ( SEntidadIdCod * p_enticObj )
{
	const char * p_cRes;

	if ( ES_VALIDO ( p_enticObj ) )
	{
		p_cRes = SCodValorLit ( p_enticObj->p_codEntidad );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

void * SEntIdCodContenido ( SEntidadIdCod * p_enticObj )
{
	void * p_vRes;

	if ( ES_VALIDO ( p_enticObj ) )
	{
		p_vRes = SEntContenido ( p_enticObj->p_entInfo );
	}
	else
	{
		p_vRes = NULL;
	}
	return ( p_vRes );
}

SEntidad * SEntIdCodBase ( SEntidadIdCod * p_enticObj )
{
	SEntidad * p_entRes;

	if ( ES_VALIDO ( p_enticObj ) )
	{
		p_entRes = p_enticObj->p_entInfo;
	}
	else
	{
		p_entRes = NULL;
	}
	return ( p_entRes );
}

int SEntIdCodEstablecerId ( SEntidadIdCod * p_enticObj, SId * p_idEntidad )
{
	int iRes;

	if ( ES_VALIDO ( p_enticObj ) )
	{
		if ( SEntEstablecerId ( p_enticObj->p_entInfo, p_idEntidad ) == 1 )
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

int SEntIdCodEstablecerValorId ( SEntidadIdCod * p_enticObj, unsigned long ulId )
{
	int iRes;

	if ( ES_VALIDO ( p_enticObj ) )
	{
		if ( SEntEstablecerValorId ( p_enticObj->p_entInfo, ulId ) == 1 )
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

void * SEntIdCodEstablecerContenido ( SEntidadIdCod * p_enticObj, void * p_vContenido )
{
	void * p_vRes;

	if ( ES_VALIDO ( p_enticObj ) )
	{
        p_vRes = SEntEstablecerContenido ( p_enticObj->p_entInfo, p_vContenido );
	}
	else
	{
		p_vRes = NULL;
	}
	return ( p_vRes );
}

int SEntIdCodEstablecerCodigo ( SEntidadIdCod * p_enticObj, SCodigo * p_codEntidad )
{
	int iRes;

	if ( ES_VALIDO ( p_enticObj ) )
	{
		if ( SCodAsignar ( p_enticObj->p_codEntidad, p_codEntidad ) == 1 )
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

int SEntIdCodEstablecerValorCodigo ( SEntidadIdCod * p_enticObj, SCadena * p_cadCodigo )
{
	int iRes;

	if ( ES_VALIDO ( p_enticObj ) )
	{
		if ( SCodEstablecer ( p_enticObj->p_codEntidad, p_cadCodigo ) == 1 )
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

int SEntIdCodEstablecerValorCodigoLit ( SEntidadIdCod * p_enticObj, const char * p_cCodigo )
{
	int iRes;

	if ( ES_VALIDO ( p_enticObj ) )
	{
		if ( SCodEstablecerLit ( p_enticObj->p_codEntidad, p_cCodigo ) == 1 )
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

int SEntIdCodEsIgual ( SEntidadIdCod * p_enticObj, SEntidadIdCod * p_enticVal )
{
	int iRes;

	if ( ES_VALIDO ( p_enticObj ) && ES_VALIDO ( p_enticVal ) )
	{
		iRes = SIdEsIgual ( SEntIdCodId ( p_enticObj ), SEntIdCodId ( p_enticVal ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SEntIdCodEsMenor ( SEntidadIdCod * p_enticObj, SEntidadIdCod * p_enticVal )
{
	int iRes;

	if ( ES_VALIDO ( p_enticObj ) && ES_VALIDO ( p_enticVal ) )
	{
		iRes = SIdEsMenor ( SEntIdCodId ( p_enticObj ), SEntIdCodId ( p_enticVal ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SEntIdCodEsMayor ( SEntidadIdCod * p_enticObj, SEntidadIdCod * p_enticVal )
{
	int iRes;

	if ( ES_VALIDO ( p_enticObj ) && ES_VALIDO ( p_enticVal ) )
	{
		iRes = SIdEsMayor ( SEntIdCodId ( p_enticObj ), SEntIdCodId ( p_enticVal ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SEntIdCodEsMenorIg ( SEntidadIdCod * p_enticObj, SEntidadIdCod * p_enticVal )
{
	int iRes;

	if ( ES_VALIDO ( p_enticObj ) && ES_VALIDO ( p_enticVal ) )
	{
		iRes = SIdEsMenorIg ( SEntIdCodId ( p_enticObj ), SEntIdCodId ( p_enticVal ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SEntIdCodEsMayorIg ( SEntidadIdCod * p_enticObj, SEntidadIdCod * p_enticVal )
{
	int iRes;

	if ( ES_VALIDO ( p_enticObj ) && ES_VALIDO ( p_enticVal ) )
	{
		iRes = SIdEsMayorIg ( SEntIdCodId ( p_enticObj ), SEntIdCodId ( p_enticVal ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SEntIdCodEsIgualEnt ( SEntidadIdCod * p_enticObj, SEntidad * p_entVal )
{
	int iRes;

	if ( ES_VALIDO ( p_enticObj ) && ES_VALIDO ( p_entVal ) )
	{
		iRes = SIdEsIgual ( SEntIdCodId ( p_enticObj ), SEntId ( p_entVal ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SEntIdCodEsMenorEnt ( SEntidadIdCod * p_enticObj, SEntidad * p_entVal )
{
	int iRes;

	if ( ES_VALIDO ( p_enticObj ) && ES_VALIDO ( p_entVal ) )
	{
		iRes = SIdEsMenor ( SEntIdCodId ( p_enticObj ), SEntId ( p_entVal ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SEntIdCodEsMayorEnt ( SEntidadIdCod * p_enticObj, SEntidad * p_entVal )
{
	int iRes;

	if ( ES_VALIDO ( p_enticObj ) && ES_VALIDO ( p_entVal ) )
	{
		iRes = SIdEsMayor ( SEntIdCodId ( p_enticObj ), SEntId ( p_entVal ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SEntIdCodEsMenorIgEnt ( SEntidadIdCod * p_enticObj, SEntidad * p_entVal )
{
	int iRes;

	if ( ES_VALIDO ( p_enticObj ) && ES_VALIDO ( p_entVal ) )
	{
		iRes = SIdEsMenorIg ( SEntIdCodId ( p_enticObj ), SEntId ( p_entVal ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SEntIdCodEsMayorIgEnt ( SEntidadIdCod * p_enticObj, SEntidad * p_entVal )
{
	int iRes;

	if ( ES_VALIDO ( p_enticObj ) && ES_VALIDO ( p_entVal ) )
	{
		iRes = SIdEsMayorIg ( SEntIdCodId ( p_enticObj ), SEntId ( p_entVal ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SEntIdCodEsIgualId ( SEntidadIdCod * p_enticObj, SId * p_idVal )
{
	int iRes;

	if ( ES_VALIDO ( p_enticObj ) && ES_VALIDO ( p_idVal ) )
	{
		iRes = SIdEsIgualNum ( SEntIdCodId ( p_enticObj ), SIdValor ( p_idVal ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SEntIdCodEsMenorId ( SEntidadIdCod * p_enticObj, SId * p_idVal )
{
	int iRes;

	if ( ES_VALIDO ( p_enticObj ) && ES_VALIDO ( p_idVal ) )
	{
		iRes = SIdEsMenorNum ( SEntIdCodId ( p_enticObj ), SIdValor ( p_idVal ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SEntIdCodEsMayorId ( SEntidadIdCod * p_enticObj, SId * p_idVal )
{
	int iRes;

	if ( ES_VALIDO ( p_enticObj ) && ES_VALIDO ( p_idVal ) )
	{
		iRes = SIdEsMayorNum ( SEntIdCodId ( p_enticObj ), SIdValor ( p_idVal ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SEntIdCodEstaEnRangoId ( SEntidadIdCod * p_enticObj, SId * p_idVal1, SId * p_idVal2 )
{
	int iRes;

	if ( ES_VALIDO ( p_enticObj ) && ( SIdEsValido ( p_idVal1 ) == 1 ) && 
		 ( SIdEsValido ( p_idVal2 ) == 1 ) )
	{
		iRes = SIdEstaEnRangoNum ( SEntIdCodId ( p_enticObj ), SIdValor ( p_idVal1 ), SIdValor ( p_idVal2 ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SEntIdCodEsMenorIgId ( SEntidadIdCod * p_enticObj, SId * p_idVal )
{
	int iRes;

	if ( ES_VALIDO ( p_enticObj ) && ES_VALIDO ( p_idVal ) )
	{
		iRes = SIdEsMenorIgNum ( SEntIdCodId ( p_enticObj ), SIdValor ( p_idVal ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SEntIdCodEsMayorIgId ( SEntidadIdCod * p_enticObj, SId * p_idVal )
{
	int iRes;

	if ( ES_VALIDO ( p_enticObj ) && ES_VALIDO ( p_idVal ) )
	{
		iRes = SIdEsMayorIgNum ( SEntIdCodId ( p_enticObj ), SIdValor ( p_idVal ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SEntIdCodEstaEnRangoIgId ( SEntidadIdCod * p_enticObj, SId * p_idVal1, SId * p_idVal2 )
{
	int iRes;

	if ( ES_VALIDO ( p_enticObj ) && ( SIdEsValido ( p_idVal1 ) == 1 ) && 
		 ( SIdEsValido ( p_idVal2 ) == 1 ) )
	{
		iRes = SIdEstaEnRangoIgNum ( SEntIdCodId ( p_enticObj ), SIdValor ( p_idVal1 ), SIdValor ( p_idVal2 ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SEntIdCodEsIgualNum ( SEntidadIdCod * p_enticObj, unsigned long ulId )
{
	int iRes;

	if ( ES_VALIDO ( p_enticObj ) ) 
	{
		iRes = SIdEsIgualNum ( SEntIdCodId ( p_enticObj ), ulId );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SEntIdCodEsMenorNum ( SEntidadIdCod * p_enticObj, unsigned long ulId )
{
	int iRes;

	if ( ES_VALIDO ( p_enticObj ) ) 
	{
		iRes = SIdEsMenorNum ( SEntIdCodId ( p_enticObj ), ulId );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SEntIdCodEsMayorNum ( SEntidadIdCod * p_enticObj, unsigned long ulId )
{
	int iRes;

	if ( ES_VALIDO ( p_enticObj ) ) 
	{
		iRes = SIdEsMayorNum ( SEntIdCodId ( p_enticObj ), ulId );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SEntIdCodEstaEnRangoNum ( SEntidadIdCod * p_enticObj, unsigned long ulId1, unsigned long ulId2 )
{
	int iRes;

	if ( ES_VALIDO ( p_enticObj ) ) 
	{
		iRes = SIdEstaEnRangoNum ( SEntIdCodId ( p_enticObj ), ulId1, ulId2 );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SEntIdCodEsMenorIgNum ( SEntidadIdCod * p_enticObj, unsigned long ulId )
{
	int iRes;

	if ( ES_VALIDO ( p_enticObj ) ) 
	{
		iRes = SIdEsMenorIgNum ( SEntIdCodId ( p_enticObj ), ulId );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SEntIdCodEsMayorIgNum ( SEntidadIdCod * p_enticObj, unsigned long ulId )
{
	int iRes;

	if ( ES_VALIDO ( p_enticObj ) ) 
	{
		iRes = SIdEsMayorIgNum ( SEntIdCodId ( p_enticObj ), ulId );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SEntIdCodEstaEnRangoIgNum ( SEntidadIdCod * p_enticObj, unsigned long ulId1, unsigned long ulId2 )
{
	int iRes;

	if ( ES_VALIDO ( p_enticObj ) ) 
	{
		iRes = SIdEstaEnRangoIgNum ( SEntIdCodId ( p_enticObj ), ulId1, ulId2 );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SEntIdCodComparar ( SEntidadIdCod * p_enticObj, SEntidadIdCod * p_enticVal )
{
	int iRes;

	if ( ES_VALIDO ( p_enticObj ) && ES_VALIDO ( p_enticVal ) )
	{
        iRes = SEntIdCodCompararId ( p_enticObj, SEntIdCodId ( p_enticVal ) );
		if ( iRes == COMP_IGUAL )
        {
            iRes = SCodComparar ( p_enticObj->p_codEntidad, SEntIdCodCodigo ( p_enticVal ) );
        }
	}
	else if  ( ES_VALIDO ( p_enticObj ) )
	{
		iRes = COMP_MAYOR;
	}
	else if  ( ES_VALIDO ( p_enticVal ) )
	{
		iRes = COMP_MENOR;
	}
	else
	{
		iRes = COMP_IGUAL;
	}
	return ( iRes );
}

int SEntIdCodCompararEnt ( SEntidadIdCod * p_enticObj, SEntidad * p_entVal )
{
	int iRes;

	if ( ES_VALIDO ( p_enticObj ) && ES_VALIDO ( p_entVal ) )
	{
		iRes = SEntComparar ( p_enticObj->p_entInfo, p_entVal );
	}
	else if  ( ES_VALIDO ( p_enticObj ) )
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

int SEntIdCodCompararId ( SEntidadIdCod * p_enticObj, SId * p_idVal )
{
	int iRes;

	if ( ES_VALIDO ( p_enticObj ) )
	{
		iRes = SIdComparar ( SEntIdCodId ( p_enticObj ), p_idVal );
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

int SEntIdCodCompararNum ( SEntidadIdCod * p_enticObj, unsigned long ulId )
{
	int iRes;

	if ( ES_VALIDO ( p_enticObj ) ) 
	{
		iRes = SIdCompararNum ( SEntIdCodId ( p_enticObj ), ulId );
	}
	else
	{
		iRes = COMP_MENOR;
	}
	return ( iRes );
}

unsigned int SEntIdCodHash ( SEntidadIdCod * p_enticObj )
{
	unsigned int uiRes = 0;

	if ( ES_VALIDO ( p_enticObj ) )
	{
		/* Solo el id, delegando en la clase base: el hash tiene que ir de la
		   mano de SEntIdCodEsIgual, que tampoco mira el codigo. Ademas el
		   codigo es mutable ( SEntIdCodEstablecerCodigo y companeras ), asi que
		   meterlo aqui dejaria fuera de su cubeta a toda entidad a la que se le
		   cambie. Delegando, un SEntidadIdCod y su SEntidad base reparten
		   igual. */
		uiRes = SEntHash ( p_enticObj->p_entInfo );
	}
	return ( uiRes );
}
