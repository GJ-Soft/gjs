
#include "SEntidadCod.h"

#include "TiposBaseDatosConfig.h"



SEntidadCod * SEntCodCrearDef ( int iMaxTam )
{
	SEntidadCod *  p_entcObj;
	SPtr *         p_ptrContenido;
    SCodigo *      p_codEntidad;

    p_codEntidad = SCodCrear ( iMaxTam );
	p_ptrContenido = SPtrCrearDef ( NULL );
	p_entcObj = SEntCodEncapsularExt ( p_codEntidad, p_ptrContenido );
    if ( ES_NULO ( p_entcObj ) )
    {
		SPtrDestruir ( &p_ptrContenido );
        SCodDestruir ( &p_codEntidad );
    }
    return ( p_entcObj );
}

SEntidadCod * SEntCodCrear ( SCadena * p_cadValor, int iMaxTam )
{
	SEntidadCod *	p_entcObj;
	SPtr *	p_ptrContenido;

	p_ptrContenido = SPtrCrearDef ( NULL );
	p_entcObj = SEntCodCrearExt ( p_cadValor, iMaxTam, p_ptrContenido );
	if ( ES_NULO ( p_entcObj ) )
	{
		SPtrDestruir ( &p_ptrContenido );
	}
	return ( p_entcObj );
}

SEntidadCod * SEntCodCrearLit ( const char * p_cValor, int iMaxTam )
{
	SEntidadCod *	p_entcObj;
	SPtr *	p_ptrContenido;

	p_ptrContenido = SPtrCrearDef ( NULL );
	p_entcObj = SEntCodCrearLitExt ( p_cValor, iMaxTam, p_ptrContenido );
	if ( ES_NULO ( p_entcObj ) )
	{
		SPtrDestruir ( &p_ptrContenido );
	}
	return ( p_entcObj );
}

SEntidadCod * SEntCodCrearExt ( SCadena * p_cadValor, int iMaxTam, SPtr * p_ptrContenido )
{
	SEntidadCod *  p_entcObj;
    SCodigo *      p_codEntidad;

    p_codEntidad = SCodCrearValorExt ( p_cadValor, iMaxTam );
	p_entcObj = SEntCodEncapsularExt ( p_codEntidad, p_ptrContenido );
    if ( ES_NULO ( p_entcObj ) )
    {
        SCodDestruir ( &p_codEntidad );
    }
    return ( p_entcObj );
}

SEntidadCod * SEntCodCrearLitExt ( const char * p_cValor, int iMaxTam, SPtr * p_ptrContenido )
{
	SEntidadCod *  p_entcObj;
    SCodigo *      p_codEntidad;

    p_codEntidad = SCodCrearValorLitExt ( p_cValor, iMaxTam );
	p_entcObj = SEntCodEncapsularExt ( p_codEntidad, p_ptrContenido );
    if ( ES_NULO ( p_entcObj ) )
    {
        SCodDestruir ( &p_codEntidad );
    }
    return ( p_entcObj );
}

SEntidadCod * SEntCodEncapsular ( SCodigo * p_codEntidad )
{
	SEntidadCod *	p_entcObj;
	SPtr *	p_ptrContenido;

	p_ptrContenido = SPtrCrearDef ( NULL );
	p_entcObj = SEntCodEncapsularExt ( p_codEntidad, p_ptrContenido );
	if ( ES_NULO ( p_entcObj ) )
	{
		SPtrDestruir ( &p_ptrContenido );
	}
	return ( p_entcObj );
}

SEntidadCod * SEntCodEncapsularExt ( SCodigo * p_codEntidad, SPtr * p_ptrContenido )
{
	SEntidadCod *	p_entcObj;
	
	p_entcObj = NULL;
    if ( ES_VALIDO ( p_codEntidad ) )
    {
		/* El contenido siempre es un SPtr, aunque este vacio: SPtrCrearDef ( NULL ). */
		if ( ES_VALIDO ( p_ptrContenido ) )
        {
			p_entcObj= (SEntidadCod *) MemReservar ( sizeof ( SEntidadCod ) );
			if ( ES_VALIDO ( p_entcObj ) )
			{
				p_entcObj->p_codEntidad = p_codEntidad;
				p_entcObj->p_ptrContenido = p_ptrContenido;
			}
        }
    }
	return ( p_entcObj );
}

void SEntCodDestruir ( SEntidadCod ** p_p_entcObj )
{
	SEntidadCod *   p_entcObj;

	if ( ES_VALIDO ( p_p_entcObj ) )
	{
		p_entcObj = *p_p_entcObj;

		if ( ES_VALIDO ( p_entcObj ) )
		{
			SPtrDestruir ( &(p_entcObj->p_ptrContenido) );
            SCodDestruir ( &(p_entcObj->p_codEntidad) );
			MemLiberar ( (void **) p_p_entcObj );
		}
	}
}

int SEntCodEsValida ( SEntidadCod * p_entcObj )
{
	int iRes;

	if ( ES_VALIDO ( p_entcObj ) )
	{
		/* El identificador y que haya SPtr de contenido. El SPtr puede estar
		   vacio: el contenido es opcional a proposito ( para eso estan
		   SEntCodCrear y SEntCodCrearExt ), asi que exigirlo haria invalida a
		   toda entidad creada sin el. */
		if ( SCodEsValido ( p_entcObj->p_codEntidad ) == 1 )
		{
			if ( ES_VALIDO ( p_entcObj->p_ptrContenido ) )
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

int SEntCodTieneContenido ( SEntidadCod * p_entcObj )
{
	int iRes;

	if ( ES_VALIDO ( p_entcObj ) )
	{
		if ( SPtrEstaVacio ( p_entcObj->p_ptrContenido ) == 0 )
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
		p_vRes = SPtrObjeto ( p_entcObj->p_ptrContenido );
	}
	else
	{
		p_vRes = NULL;
	}
	return ( p_vRes );
}

int SEntCodEstablecerContenido ( SEntidadCod * p_entcObj, void * p_vContenido )
{
	int iRes;

	if ( ES_VALIDO ( p_entcObj ) )
	{
		iRes = SPtrEstablecer ( p_entcObj->p_ptrContenido, p_vContenido );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SEntCodEstablecerContenidoExt ( SEntidadCod * p_entcObj, void * p_vContenido, PRC_DESTRUCTOR fDestructor )
{
	int 	iRes;
	SPtr *	p_ptrContenido;

	if ( ES_VALIDO ( p_entcObj ) )
	{
		/* Con el mismo objeto que ya tiene solo cambia el destructor: otro SPtr */
		/* destruiria el objeto al sustituir al actual.                         */
		if ( SPtrObjeto ( p_entcObj->p_ptrContenido ) == p_vContenido )
		{
			if ( ES_VALIDO ( fDestructor ) )
			{
				p_entcObj->p_ptrContenido->p_fDestructor = fDestructor;
				iRes = 1;
			}
			else
			{
				iRes = 0;
			}
		}
		else
		{
			p_ptrContenido = SPtrCrear ( p_vContenido, fDestructor );
			iRes = SEntCodAsignarContenido ( p_entcObj, p_ptrContenido );
			if ( iRes == 0 )
			{
				SPtrDestruirSinLiberar ( &p_ptrContenido );
			}
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SEntCodAsignarContenido ( SEntidadCod * p_entcObj, SPtr * p_ptrContenido )
{
	int iRes;

	iRes = 0;
	if ( ES_VALIDO ( p_entcObj ) )
	{
		if ( ES_VALIDO ( p_ptrContenido ) )
		{
			/* El mismo SPtr que ya tiene no se destruye: se quedaria con uno liberado. */
			if ( p_entcObj->p_ptrContenido != p_ptrContenido )
			{
				SPtrDestruir ( &(p_entcObj->p_ptrContenido) );
				p_entcObj->p_ptrContenido = p_ptrContenido;
			}
			iRes = 1;
		}
	}
	return ( iRes );
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

SPtr * SEntCodPtr ( SEntidadCod * p_entcObj )
{
	return ( SPtrCrear ( p_entcObj, (PRC_DESTRUCTOR) SEntCodDestruir ) );
}


