
#include "SDefDato.h"


#include "TiposBasicosConfig.h"





SDefDato * SDefDatCrear ( unsigned long	ulId, const char * p_cNombre, int iTipo, int iReferencia, int iTam, int iDecimales, const char * p_cValorDef )
{
	SDefDato *	p_ddatObj;
	int			iError;
	
	if ( ( ulId > 0 ) && ( TipEsValido ( iTipo ) == 1 ) && 
		 ES_VALIDO ( p_cNombre ) == 1 )
	{
		if ( ( ( TipEsBinario ( iTipo ) == 1 ) || ( TipEsObjeto ( iTipo ) == 1 ) ) &&
			 ( iTam <= 0 ) )
		{
			iError = 1;
		}
		else
		{
			iError = 0;
		}

		if ( iError == 0 )
		{
			p_ddatObj= (SDefDato *) MemReservar ( sizeof ( SDefDato ) );
			if ( ES_VALIDO ( p_ddatObj ) )
			{
				p_ddatObj->ulId = ulId;
				p_ddatObj->iTipo = iTipo;
				if ( iReferencia > 0 )
				{
					p_ddatObj->iReferencia = 1;
				}
				else
				{
					p_ddatObj->iReferencia = 0;
				}
				p_ddatObj->p_cNombre = CadDuplicar ( p_cNombre );
				if ( iTam > 0 )
				{
					p_ddatObj->iTam = iTam;
				}
				else
				{
					p_ddatObj->iTam = -1;
				}
				if ( TipEsReal ( p_ddatObj->iTipo ) )
				{
					if ( iDecimales > 0 )
					{
						p_ddatObj->iDecimales = iDecimales;
					}
					else
					{
						p_ddatObj->iDecimales = -1;
					}
				}
				else
				{
					p_ddatObj->iDecimales = -1;
				}
				if ( p_ddatObj->iReferencia == 0 )
				{
					p_ddatObj->p_cValorDef = CadDuplicar ( p_cValorDef );
				}
				else
				{
					p_ddatObj->p_cValorDef = NULL;
				}
			}
		}
		else
		{
			p_ddatObj = NULL;
		}
	}
	else
	{
		p_ddatObj = NULL;
	}
	return ( p_ddatObj );
}

void SDefDatDestruir ( SDefDato ** p_p_ddatObj )
{
	SDefDato * p_ddatObj;
	
	if ( ES_VALIDO ( p_p_ddatObj ) )
	{
		p_ddatObj = *p_p_ddatObj;

		if ( ES_VALIDO ( p_ddatObj ) )
		{
			MemLiberar ( (void **) &(p_ddatObj->p_cNombre) );
			MemLiberar ( (void **) &(p_ddatObj->p_cValorDef) );
			MemLiberar ( (void **) p_p_ddatObj );
		}
	}
}

int SDefDatEsValido ( SDefDato * p_ddatObj )
{
	int iRes;

	if ( ES_VALIDO ( p_ddatObj ) )
	{
		if ( ( p_ddatObj->ulId > 0 ) && ( TipEsValido ( p_ddatObj->iTipo ) == 1 ) &&
			 ES_VALIDO ( p_ddatObj->p_cNombre ) )
		{
			if ( ( ( TipEsBinario ( p_ddatObj->iTipo ) == 1 ) || ( TipEsObjeto ( p_ddatObj->iTipo ) == 1 ) ) &&
				 ( p_ddatObj->iTam <= 0 ) )
			{
				iRes = 0;
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

unsigned long SDefDatId ( SDefDato * p_ddatObj )
{
	unsigned long ulRes;

	if ( ES_VALIDO ( p_ddatObj ) )
	{
		ulRes = p_ddatObj->ulId;
	}
	else
	{
		ulRes = 0;
	}
	return ( ulRes );
}

int SDefDatTipo ( SDefDato * p_ddatObj )
{
	int iRes;

	if ( ES_VALIDO ( p_ddatObj ) )
	{
		iRes = p_ddatObj->iTipo;
	}
	else
	{
		iRes = TIP_NINGUNO;
	}
	return ( iRes );
}

int SDefDatEsValor ( SDefDato * p_ddatObj )
{
	int iRes;

	if ( ES_VALIDO ( p_ddatObj ) )
	{
		if ( p_ddatObj->iReferencia == 1 )
		{
			iRes = 0;
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

int SDefDatEsReferencia ( SDefDato * p_ddatObj )
{
	int iRes;

	if ( ES_VALIDO ( p_ddatObj ) )
	{
		if ( p_ddatObj->iReferencia == 1 )
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

const char * SDefDatNombre ( SDefDato * p_ddatObj )
{
	const char * p_cRes;

	if ( ES_VALIDO ( p_ddatObj ) )
	{
		p_cRes = (const char *) p_ddatObj->p_cNombre;
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

/*
int SDefDatEstablecerNombre ( SDefDato * p_ddatObj, const char * p_cNombre )
{
	int iRes;

	if ( ES_VALIDO ( p_ddatObj ) )
	{
		MemLiberar ( (void **) &(p_ddatObj->p_cNombre [0]) );
		if ( ES_VALIDO ( p_cNombre ) )
		{
			p_ddatObj->p_cNombre = CadDuplicar ( p_cNombre );
			if ( ES_VALIDO ( p_ddatObj->p_cNombre ) )
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
int SDefDatTam ( SDefDato * p_ddatObj )
{
	int iRes;

	if ( ES_VALIDO ( p_ddatObj ) )
	{
		iRes = p_ddatObj->iTam;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SDefDatDecimales ( SDefDato * p_ddatObj )
{
	int iRes;

	if ( ES_VALIDO ( p_ddatObj ) )
	{
		iRes = p_ddatObj->iDecimales;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

const char * SDefDatValorDefecto ( SDefDato * p_ddatObj )
{
	const char *	p_cRes;

	if ( ES_VALIDO ( p_ddatObj ) )
	{
		p_cRes = (const char *) p_ddatObj->p_cValorDef;
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

