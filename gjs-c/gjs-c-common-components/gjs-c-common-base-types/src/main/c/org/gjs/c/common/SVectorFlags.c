
#include "SVectorFlags.h"


#include "TiposBasicosConfig.h"



SVectorFlags * SVecFlgCrear ( unsigned long	ulNumFlags )
{
	SVectorFlags * p_vecfObj;

	if ( ulNumFlags > 0 )
	{
		p_vecfObj= (SVectorFlags *) MemReservar ( sizeof ( SVectorFlags ) );
		if ( ES_VALIDO ( p_vecfObj ) )
		{
			p_vecfObj->p_bufContenido = SBufCrear ( ulNumFlags );
			if ( ES_NULO ( p_vecfObj->p_bufContenido ) )
			{
				SVecFlgDestruir ( &p_vecfObj );
			}
		}
	}
	else
	{
		p_vecfObj = NULL;
	}
	return ( p_vecfObj );
}

SVectorFlags * SVecFlgEncapsular ( SBuffer * p_bufContenido )
{
	SVectorFlags * p_vecfObj;

	if ( SBufEsValido ( p_bufContenido ) == 1 )
	{
		p_vecfObj= (SVectorFlags *) MemReservar ( sizeof ( SVectorFlags ) );
		if ( ES_VALIDO ( p_vecfObj ) )
		{
			p_vecfObj->p_bufContenido = p_bufContenido;
		}
	}
	else
	{
		p_vecfObj = NULL;
	}
	return ( p_vecfObj );
}


void SVecFlgDestruir ( SVectorFlags ** p_p_vecfObj )
{
	SVectorFlags * p_vecfObj;

	if ( ES_VALIDO ( p_p_vecfObj ) )
	{
		p_vecfObj = *p_p_vecfObj;

		if ( ES_VALIDO ( p_vecfObj ) )
		{
			SBufDestruir ( &(p_vecfObj->p_bufContenido) );
			MemLiberar ( (void **) p_p_vecfObj );
		}
	}
}

int SVecFlgEsValido ( SVectorFlags * p_vecfObj )
{
	int iRes;

	if ( ES_VALIDO ( p_vecfObj ) )
	{
		iRes = SBufEsValido ( p_vecfObj->p_bufContenido );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

unsigned long SVecFlgNumFlags ( SVectorFlags * p_vecfObj )
{
	unsigned long ulRes;

	if ( ES_VALIDO ( p_vecfObj ) )
	{
		ulRes = SBufTam ( p_vecfObj->p_bufContenido );
	}
	else
	{
		ulRes = 0;
	}
	return ( ulRes );
}

int SVecFlgFlag ( SVectorFlags * p_vecfObj, unsigned long ulPos )
{
	int iRes;

	if ( ES_VALIDO ( p_vecfObj ) )
	{
		iRes = (int) SBufLeer ( p_vecfObj->p_bufContenido, ulPos );
	}
    else
    {
        iRes = 0;
    }
	return ( iRes );
}

int SVecFlgFlagEstaActivo ( SVectorFlags * p_vecfObj, unsigned long ulPos )
{
	int iRes;

	if ( ES_VALIDO ( p_vecfObj ) )
	{
		if ( (int) SBufLeer ( p_vecfObj->p_bufContenido, ulPos ) == 1 )
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

int SVecFlgActivarFlag ( SVectorFlags * p_vecfObj, unsigned long ulPos )
{
	int iRes;

	if ( ES_VALIDO ( p_vecfObj ) )
	{
		iRes = SBufEscribir ( p_vecfObj->p_bufContenido,  ulPos, 0x01 );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SVecFlgDesactivarFlag ( SVectorFlags * p_vecfObj, unsigned long ulPos )
{
	int iRes;

	if ( ES_VALIDO ( p_vecfObj ) )
	{
		iRes = SBufEscribir ( p_vecfObj->p_bufContenido,  ulPos, 0x00 );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}


int SVecFlgLimpiar ( SVectorFlags * p_vecfObj )
{
	int	iRes;

	if ( ES_VALIDO ( p_vecfObj ) )
	{
		iRes = SBufLimpiar ( p_vecfObj->p_bufContenido );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}
