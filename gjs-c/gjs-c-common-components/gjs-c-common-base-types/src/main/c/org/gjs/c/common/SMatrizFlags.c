
#include "SMatrizFlags.h"


#include "TiposBasicosConfig.h"



SMatrizFlags * SMatFlgCrear ( unsigned long	ulNumFilas, unsigned long ulNumColumnas )
{
	SMatrizFlags * p_matfObj;

	if ( ( ulNumFilas > 0 ) && ( ulNumColumnas > 0 ) )
	{
		p_matfObj= (SMatrizFlags *) MemReservar ( sizeof ( SMatrizFlags ) );
		if ( ES_VALIDO ( p_matfObj ) )
		{
			p_matfObj->p_bufContenido = SBufCrear ( ulNumFilas * ulNumColumnas );
			if ( ES_VALIDO ( p_matfObj->p_bufContenido ) )
			{
				p_matfObj->ulNumFilas = ulNumFilas;
				p_matfObj->ulNumColumnas = ulNumColumnas;
			}
			else
			{
				SMatFlgDestruir ( &p_matfObj );
			}
		}
	}
	else
	{
		p_matfObj = NULL;
	}
	return ( p_matfObj );
}

void SMatFlgDestruir ( SMatrizFlags ** p_p_matfObj )
{
	SMatrizFlags * p_matfObj;

	if ( ES_VALIDO ( p_p_matfObj ) )
	{
		p_matfObj = *p_p_matfObj;

		if ( ES_VALIDO ( p_matfObj ) )
		{
			SBufDestruir ( &(p_matfObj->p_bufContenido) );
			MemLiberar ( (void **) p_p_matfObj );
		}
	}
}

int SMatFlgEsValida ( SMatrizFlags * p_matfObj )
{
	int iRes;

	if ( ES_VALIDO ( p_matfObj ) )
	{
		if ( ( SBufEsValido ( p_matfObj->p_bufContenido ) == 1 ) &&
			 ( p_matfObj->ulNumFilas * p_matfObj->ulNumColumnas == SBufTam ( p_matfObj->p_bufContenido ) ) )
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

unsigned long SMatFlgNumFilas( SMatrizFlags * p_matfObj )
{
	unsigned long ulRes;

	if ( ES_VALIDO ( p_matfObj ) )
	{
		ulRes = p_matfObj->ulNumFilas;
	}
	else
	{
		ulRes = 0;
	}
	return ( ulRes );
}

unsigned long SMatFlgNumColumnas( SMatrizFlags * p_matfObj )
{
	unsigned long ulRes;

	if ( ES_VALIDO ( p_matfObj ) )
	{
		ulRes = p_matfObj->ulNumColumnas;
	}
	else
	{
		ulRes = 0;
	}
	return ( ulRes );
}

int SMatFlgFlag ( SMatrizFlags * p_matfObj, unsigned long ulFil, unsigned long ulCol )
{
	int iRes;

	if ( ES_VALIDO ( p_matfObj ) )
	{
		if ( ulFil < p_matfObj->ulNumFilas && ulCol < p_matfObj->ulNumColumnas )
		{
			iRes = (int) SBufLeer ( p_matfObj->p_bufContenido, ulFil * p_matfObj->ulNumColumnas + ulCol );
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

int SMatFlgFlagEstaActivo ( SMatrizFlags * p_matfObj, unsigned long ulFil, unsigned long ulCol )
{
	int iRes;

	if ( ES_VALIDO ( p_matfObj ) )
	{
		if ( ulFil < p_matfObj->ulNumFilas && ulCol < p_matfObj->ulNumColumnas )
		{
			if ( (int) SBufLeer ( p_matfObj->p_bufContenido, ulFil * p_matfObj->ulNumColumnas + ulCol ) == 1 )
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

int SMatFlgActivarFlag ( SMatrizFlags * p_matfObj, unsigned long ulFil, unsigned long ulCol )
{
	int iRes;

	if ( ES_VALIDO ( p_matfObj ) )
	{
		if ( ulFil < p_matfObj->ulNumFilas && ulCol < p_matfObj->ulNumColumnas )
		{
			iRes = SBufEscribir ( p_matfObj->p_bufContenido, ulFil * p_matfObj->ulNumColumnas + ulCol, 0x01 );
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

int SMatFlgDesactivarFlag ( SMatrizFlags * p_matfObj, unsigned long ulFil, unsigned long ulCol )
{
	int iRes;

	if ( ES_VALIDO ( p_matfObj ) )
	{
		if ( ulFil < p_matfObj->ulNumFilas && ulCol < p_matfObj->ulNumColumnas )
		{
			iRes = SBufEscribir ( p_matfObj->p_bufContenido, ulFil * p_matfObj->ulNumColumnas + ulCol, 0x00 );
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

int SMatFlgLimpiar ( SMatrizFlags * p_matfObj )
{
	int	iRes;

	if ( ES_VALIDO ( p_matfObj ) )
	{
		iRes = SBufLimpiar ( p_matfObj->p_bufContenido );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}
