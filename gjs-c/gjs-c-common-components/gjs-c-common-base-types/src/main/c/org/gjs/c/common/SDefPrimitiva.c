
#include "SDefPrimitiva.h"


#include "TiposBasicosConfig.h"





SDefPrimitiva * SDefPrimCrear ( unsigned long ulId, const char * p_cNombre, int iTipo )
{
	SDefPrimitiva *	p_dprimObj;

	if ( ( ulId > 0 ) && ( TipPrimEsValido ( iTipo ) == 1 ) &&
		 ES_VALIDO ( p_cNombre ) == 1 )
	{
		p_dprimObj= (SDefPrimitiva *) MemReservar ( sizeof ( SDefPrimitiva ) );
		if ( ES_VALIDO ( p_dprimObj ) )
		{
			p_dprimObj->ulId = ulId;
			p_dprimObj->iTipo = iTipo;
			p_dprimObj->p_cNombre = CadDuplicar ( p_cNombre );
			p_dprimObj->p_secParametros = SSecpCrear ();
			SSecpDesactivarLiberacionMemoria ( p_dprimObj->p_secParametros );
			p_dprimObj->p_ddatRetorno = NULL;
		}
	}
	else
	{
		p_dprimObj = NULL;
	}
	return ( p_dprimObj );
}

void SDefPrimDestruir ( SDefPrimitiva ** p_p_dprimObj )
{
	SDefPrimitiva * p_dprimObj;
	int				iNumParams;
	int				iParam;
	SDefDato *		p_ddatObj;

	if ( ES_VALIDO ( p_p_dprimObj ) )
	{
		p_dprimObj = *p_p_dprimObj;

		if ( ES_VALIDO ( p_dprimObj ) )
		{
			MemLiberar ( (void **) &(p_dprimObj->p_cNombre) );
			iNumParams = SSecpNumElementos ( p_dprimObj->p_secParametros );
			for ( iParam = 0; iParam < iNumParams; iParam = iParam + 1 )
			{
				p_ddatObj = (SDefDato *) SSecpElemento ( p_dprimObj->p_secParametros, iParam );
				SDefDatDestruir ( &p_ddatObj ); 				
			}
			SSecpDestruir ( &(p_dprimObj->p_secParametros) );
			SDefDatDestruir ( &(p_dprimObj->p_ddatRetorno) );
			MemLiberar ( (void **) p_p_dprimObj );
		}
	}
}

int SDefPrimEsValida ( SDefPrimitiva * p_dprimObj )
{
	int iRes;

	if ( ES_VALIDO ( p_dprimObj ) )
	{
		if ( ( p_dprimObj->ulId > 0 ) && ( TipPrimEsValido ( p_dprimObj->iTipo ) == 1 ) &&
			 ES_VALIDO ( p_dprimObj->p_cNombre ) )
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

unsigned long SDefPrimId ( SDefPrimitiva * p_dprimObj )
{
	unsigned long ulRes;

	if ( ES_VALIDO ( p_dprimObj ) )
	{
		ulRes = p_dprimObj->ulId;
	}
	else
	{
		ulRes = 0;
	}
	return ( ulRes );
}

int SDefPrimTipo ( SDefPrimitiva * p_dprimObj )
{
	int iRes;

	if ( ES_VALIDO ( p_dprimObj ) )
	{
		iRes = p_dprimObj->iTipo;
	}
	else
	{
		iRes = TIP_NINGUNO;
	}
	return ( iRes );
}

int SDefPrimEsFuncion ( SDefPrimitiva * p_dprimObj )
{
	int iRes;

	if ( ES_VALIDO ( p_dprimObj ) )
	{
		iRes = TipPrimEsFuncion ( p_dprimObj->iTipo );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SDefPrimEsProcedimiento ( SDefPrimitiva * p_dprimObj )
{
	int iRes;

	if ( ES_VALIDO ( p_dprimObj ) )
	{
		iRes = TipPrimEsProcedimiento ( p_dprimObj->iTipo );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

const char * SDefPrimNombre ( SDefPrimitiva * p_dprimObj )
{
	const char * p_cRes;

	if ( ES_VALIDO ( p_dprimObj ) )
	{
		p_cRes = (const char *) p_dprimObj->p_cNombre;
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

/*
int SDefPrimEstablecerNombre ( SDefPrimitiva * p_dprimObj, const char * p_cNombre )
{
	int iRes;

	if ( ES_VALIDO ( p_dprimObj ) )
	{
		MemLiberar ( (void **) &(p_dprimObj->p_cNombre [0]) );
		if ( ES_VALIDO ( p_cNombre ) )
		{
			p_dprimObj->p_cNombre = CadDuplicar ( p_cNombre );
			if ( ES_VALIDO ( p_dprimObj->p_cNombre ) )
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
	return ( iRes );
}
*/
int SDefPrimDefinirValorRetorno ( SDefPrimitiva * p_dprimObj, int iTipo, int iReferencia, int iTam, int iDecimales )
{
	int iRes;

	if ( ES_VALIDO ( p_dprimObj ) )
	{
		SDefDatDestruir ( &(p_dprimObj->p_ddatRetorno) );
		p_dprimObj->p_ddatRetorno = SDefDatCrear ( p_dprimObj->ulId, p_dprimObj->p_cNombre, iTipo, iReferencia, iTam, iDecimales, NULL );
		iRes = SDefDatEsValido ( p_dprimObj->p_ddatRetorno );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

SDefDato * SDefPrimValorRetorno ( SDefPrimitiva * p_dprimObj )
{
	SDefDato *	p_ddatRes;

	if ( ES_VALIDO ( p_dprimObj ) )
	{
		p_ddatRes = p_dprimObj->p_ddatRetorno;
	}
	else
	{
		p_ddatRes = NULL;
	}
	return ( p_ddatRes );
}

int SDefPrimCrearParametro ( SDefPrimitiva * p_dprimObj, const char * p_cNombre, int iTipo, int iReferencia, int iTam, int iDecimales, const char * p_cValorDef )
{
	SDefDato *	p_ddatObj;
	int			iParam;
	int			iRes;

	if ( ES_VALIDO ( p_dprimObj ) )
	{
		iParam = SSecpNumElementos ( p_dprimObj->p_secParametros ) + 1;
		p_ddatObj = SDefDatCrear ( iParam, p_cNombre, iTipo, iReferencia, iTam, iDecimales, p_cValorDef );
		if ( SDefDatEsValido ( p_ddatObj ) == 1 )
		{
			iRes = SSecpInsertar ( p_dprimObj->p_secParametros, (byte *) p_ddatObj );
		}
		else
		{
			iRes = 0;
		}
		if ( iRes == 0 )
		{
			SDefDatDestruir ( &(p_ddatObj) );
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SDefPrimNumParametros ( SDefPrimitiva * p_dprimObj )
{
	int	iRes;

	if ( ES_VALIDO ( p_dprimObj ) )
	{
		iRes = SSecpNumElementos ( p_dprimObj->p_secParametros );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

SDefDato * SDefPrimParametro ( SDefPrimitiva * p_dprimObj, int iParametro )
{
	SDefDato *	p_ddatRes;

	if ( ES_VALIDO ( p_dprimObj ) )
	{
		p_ddatRes = (SDefDato *) SSecpElemento ( p_dprimObj->p_secParametros, iParametro );
	}
	else
	{
		p_ddatRes = NULL;
	}
	return ( p_ddatRes );
}

