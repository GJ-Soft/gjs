#include "SVectorLiterales.h"

#include "TiposBasicosConfig.h"



SVectorLiterales * SVecLitCrear ( int iNumElementos )
{
	SVectorLiterales * p_vecObj;
	
	if ( iNumElementos > 0 )
	{
		p_vecObj = (SVectorLiterales *) MemReservar ( sizeof ( SVectorLiterales ) );
		if ( ES_VALIDO ( p_vecObj ) )
		{
			p_vecObj->p_vecDatos = SVecpCrear ( iNumElementos );
			if ( ES_VALIDO ( p_vecObj->p_vecDatos ) )
			{
				SVecpActivarLiberacionMemoria ( p_vecObj->p_vecDatos );
			}
			else
			{
				SVecLitDestruir ( &p_vecObj );
			}
		}
	}
	else
	{
		p_vecObj = NULL;
	}
	return ( p_vecObj );
}

/* Vector de iNumValores posiciones con copias de las primeras cadenas de
   p_p_cValores, en orden y con la liberacion activada: una cadena nula deja
   su posicion vacia. NULL si el vector es nulo, el numero no es positivo (un
   vector no tiene 0 posiciones) o falla alguna copia. */
SVectorLiterales * SVecLitCrearDesdeVector ( const char * const * p_p_cValores, int iNumValores )
{
	SVectorLiterales *	p_vecRes;
	int		iPos;
	int		iError;

	if ( ES_VALIDO ( p_p_cValores ) )
	{
		p_vecRes = SVecLitCrear ( iNumValores );
		if ( ES_VALIDO ( p_vecRes ) )
		{
			iError = 0;
			iPos = 0;
			while ( ( iError == 0 ) && ( iPos < iNumValores ) )
			{
				if ( ES_VALIDO ( p_p_cValores [ iPos ] ) )
				{
					if ( SVecLitAsignarDup ( p_vecRes, iPos, p_p_cValores [ iPos ] ) != 1 )
					{
						iError = 1;
					}
				}
				iPos = iPos + 1;
			}
			if ( iError == 1 )
			{
				SVecLitDestruir ( &p_vecRes );
			}
		}
	}
	else
	{
		p_vecRes = NULL;
	}
	return ( p_vecRes );
}

void SVecLitDestruir ( SVectorLiterales ** p_p_vecObj )
{
	SVectorLiterales * p_vecObj;
	
	if ( ES_VALIDO ( p_p_vecObj ) )
	{
		p_vecObj = *p_p_vecObj;

		if ( ES_VALIDO ( p_vecObj ) )
		{
			SVecpDestruir ( &(p_vecObj->p_vecDatos) );
			MemLiberar ( (void **) p_p_vecObj );
		}
	}
}

int SVecLitEsValido ( SVectorLiterales * p_vecObj )
{
	int iRes;

	if ( ES_VALIDO ( p_vecObj ) )
	{
		iRes = SVecpEsValido ( p_vecObj->p_vecDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SVecLitNumElementos ( SVectorLiterales * p_vecObj )
{
	int iRes;

	if ( ES_VALIDO ( p_vecObj ) )
	{
		iRes = SVecpNumElementos ( p_vecObj->p_vecDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

char * SVecLitElemento ( SVectorLiterales * p_vecObj, int iElem )
{
	char *	p_cRes;

	if ( ES_VALIDO ( p_vecObj ) )
	{
		p_cRes = (char *) SVecpElemento ( p_vecObj->p_vecDatos, iElem );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

int SVecLitAsignar ( SVectorLiterales * p_vecObj, int iElem, char * p_cDato )
{
	int		iRes;

	if ( ES_VALIDO ( p_vecObj ) && ES_VALIDO ( p_cDato ) )
	{
		iRes = SVecpAsignar ( p_vecObj->p_vecDatos, iElem, (byte *) p_cDato );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int SVecLitAsignarDup ( SVectorLiterales * p_vecObj, int iElem, const char * p_cDato )
{
	int		iRes;
	char *	p_cElem;
	int		iActLib;

	if ( ES_VALIDO ( p_vecObj ) && ES_VALIDO ( p_cDato ) )
	{
		p_cElem = CadDuplicar ( p_cDato );
		if ( ES_VALIDO ( p_cElem ) )
		{
			iActLib = SVecpLiberacionMemoriaActivada ( p_vecObj->p_vecDatos );
			SVecpActivarLiberacionMemoria ( p_vecObj->p_vecDatos );
			iRes = SVecpAsignar ( p_vecObj->p_vecDatos, iElem, (byte *) p_cElem );
			if ( iRes != 1 )
			{
				MemLiberar ( (void **) &p_cElem );
			}
			if ( iActLib == 0 )
			{
				SVecpDesactivarLiberacionMemoria ( p_vecObj->p_vecDatos );
			}
		}
		else
		{
			iRes = -1;
		}
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int SVecLitLimpiarElemento ( SVectorLiterales * p_vecObj, int iElem )
{
	int iRes;

	if ( ES_VALIDO ( p_vecObj ) )
	{
		iRes = SVecpLimpiarElemento ( p_vecObj->p_vecDatos, iElem );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int SVecLitLimpiar ( SVectorLiterales * p_vecObj )
{
	int iRes;

	if ( ES_VALIDO ( p_vecObj ) )
	{
		iRes = SVecpLimpiar ( p_vecObj->p_vecDatos );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int	SVecLitLiberacionMemoriaActivada ( SVectorLiterales * p_vecObj )
{
	int	iRes;

	if ( ES_VALIDO ( p_vecObj ) ) 
	{
		iRes = SVecpLiberacionMemoriaActivada ( p_vecObj->p_vecDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

void SVecLitActivarLiberacionMemoria ( SVectorLiterales * p_vecObj )
{
	if ( ES_VALIDO ( p_vecObj ) ) 
	{
		SVecpActivarLiberacionMemoria ( p_vecObj->p_vecDatos );
	}
}

void SVecLitDesactivarLiberacionMemoria ( SVectorLiterales * p_vecObj )
{
	if ( ES_VALIDO ( p_vecObj ) ) 
	{
		SVecpDesactivarLiberacionMemoria ( p_vecObj->p_vecDatos );
	}
}

int SVecLitExiste ( SVectorLiterales * p_vecObj, const char * p_cDato )
{
	int iRes;
	int iElem;
	int iNumElems;

	if ( ES_VALIDO ( p_vecObj ) && ES_VALIDO ( p_cDato )  ) 
	{
		iRes = 0;
		iElem = 0;
		iNumElems = SVecLitNumElementos ( p_vecObj );
		while ( ( iElem < iNumElems ) && ( iRes == 0 ) )
		{
			if ( CadComparar ( SVecLitElemento ( p_vecObj, iElem ), p_cDato ) == COMP_IGUAL )
			{
				iRes = 1;
			}
			iElem = iElem + 1;
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}
