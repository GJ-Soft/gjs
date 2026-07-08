
#include "SInterfaz.h"


#include "TiposBasicosConfig.h"





SInterfaz * SIntrfzCrear ( unsigned long ulId, const char * p_cNombre )
{
	SInterfaz *	p_intrfzObj;
	
	if ( ( ulId > 0 ) && ES_VALIDO ( p_cNombre ) )
	{
		p_intrfzObj= (SInterfaz *) MemReservar ( sizeof ( SInterfaz ) );
		if ( ES_VALIDO ( p_intrfzObj ) )
		{
			p_intrfzObj->ulId = ulId;
			p_intrfzObj->p_cNombre = CadDuplicar ( p_cNombre );
			p_intrfzObj->p_secPrimitivas = SSecpCrear ();
			SSecpDesactivarLiberacionMemoria ( p_intrfzObj->p_secPrimitivas  );
		}
	}
	else
	{
		p_intrfzObj = NULL;
	}
	return ( p_intrfzObj );
}

void SIntrfzDestruir ( SInterfaz ** p_p_intrfzObj )
{
	SInterfaz *		p_intrfzObj;
	int				iNumPrimitivas;
	int				iPrimitiva;
	SDefPrimitiva *	p_dprimObj;
	
	if ( ES_VALIDO ( p_p_intrfzObj ) )
	{
		p_intrfzObj = *p_p_intrfzObj;

		if ( ES_VALIDO ( p_intrfzObj ) )
		{
			MemLiberar ( (void **) &(p_intrfzObj->p_cNombre) );
			iNumPrimitivas = SSecpNumElementos ( p_intrfzObj->p_secPrimitivas );
			for ( iPrimitiva = 0; iPrimitiva < iNumPrimitivas; iPrimitiva = iPrimitiva + 1 )
			{
				p_dprimObj = (SDefPrimitiva *) SSecpElemento ( p_intrfzObj->p_secPrimitivas, iPrimitiva );
				SDefPrimDestruir ( &p_dprimObj ); 				
			}
			SSecpDestruir ( &(p_intrfzObj->p_secPrimitivas) );
			MemLiberar ( (void **) p_p_intrfzObj );
		}
	}
}

int SIntrfzEsValido ( SInterfaz * p_intrfzObj )
{
	int iRes;

	if ( ES_VALIDO ( p_intrfzObj ) )
	{
		if ( ( p_intrfzObj->ulId > 0 ) && ES_VALIDO ( p_intrfzObj->p_cNombre ) )
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

unsigned long SIntrfzId ( SInterfaz * p_intrfzObj )
{
	unsigned long ulRes;

	if ( ES_VALIDO ( p_intrfzObj ) )
	{
		ulRes = p_intrfzObj->ulId;
	}
	else
	{
		ulRes = 0;
	}
	return ( ulRes );
}

const char * SIntrfzNombre ( SInterfaz * p_intrfzObj )
{
	const char * p_cRes;

	if ( ES_VALIDO ( p_intrfzObj ) )
	{
		p_cRes = (const char *) p_intrfzObj->p_cNombre;
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

/*
int SIntrfzEstablecerNombre ( SInterfaz * p_intrfzObj, const char * p_cNombre )
{
	int iRes;

	if ( ES_VALIDO ( p_intrfzObj ) )
	{
		MemLiberar ( (void **) &(p_intrfzObj->p_cNombre [0]) );
		if ( ES_VALIDO ( p_cNombre ) )
		{
			p_intrfzObj->p_cNombre = CadDuplicar ( p_cNombre );
			if ( ES_VALIDO ( p_intrfzObj->p_cNombre ) )
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
int SIntrfzCrearPrimitiva ( SInterfaz * p_intrfzObj, const char * p_cNombre, int iTipo )
{
	SDefPrimitiva *	p_dprimObj;
	int				iPrimitiva;
	int				iRes;

	if ( ES_VALIDO ( p_intrfzObj ) )
	{
		iPrimitiva = SSecpNumElementos ( p_intrfzObj->p_secPrimitivas ) + 1;
		p_dprimObj = SDefPrimCrear ( iPrimitiva, p_cNombre, iTipo );
		if ( SDefPrimEsValida ( p_dprimObj ) == 1 )
		{
			iRes = SSecpInsertar ( p_intrfzObj->p_secPrimitivas, (byte *) p_dprimObj );
		}
		else
		{
			iRes = 0;
		}
		if ( iRes == 0 )
		{
			SDefPrimDestruir ( &(p_dprimObj) );
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SIntrfzNumPrimitivas ( SInterfaz * p_intrfzObj )
{
	int	iRes;

	if ( ES_VALIDO ( p_intrfzObj ) )
	{
		iRes = SSecpNumElementos ( p_intrfzObj->p_secPrimitivas );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

SDefPrimitiva * SIntrfzPrimitiva ( SInterfaz * p_intrfzObj, int iPrimitiva )
{
	SDefPrimitiva *	p_dprimRes;

	if ( ES_VALIDO ( p_intrfzObj ) )
	{
		p_dprimRes = (SDefPrimitiva *) SSecpElemento ( p_intrfzObj->p_secPrimitivas, iPrimitiva );
	}
	else
	{
		p_dprimRes = NULL;
	}
	return ( p_dprimRes );
}

