#include "SArbolBin.h"


#include "TiposBasicosConfig.h"








SArbolBin * SArbBinCrear ()
{
	SArbolBin * p_arbbObj;

	p_arbbObj = (SArbolBin *) MemReservar ( sizeof ( SArbolBin ) );
	if ( ES_VALIDO ( p_arbbObj ) )
	{
		p_arbbObj->p_nodbRaiz = NULL;
		p_arbbObj->p_nodbActual = NULL;
	}
	return ( p_arbbObj );
}

void SArbBinDestruir ( SArbolBin ** p_p_arbbObj )
{
	SArbolBin * p_arbbObj;

	if ( ES_VALIDO ( p_p_arbbObj ) )
	{
		p_arbbObj = *p_p_arbbObj;
		if ( ES_VALIDO ( p_arbbObj ) )
		{
			SArbBinVaciar ( p_arbbObj );
			MemLiberar ( (void **) p_p_arbbObj );
		}
	}
}

SNodoBin * SArbBinRaiz ( SArbolBin * p_arbbObj )
{
	SNodoBin * p_nodbRes;

	if ( ES_VALIDO ( p_arbbObj ) )
	{
		p_nodbRes = p_arbbObj->p_nodbRaiz;
	}
	else
	{
		p_nodbRes = NULL;
	}
	return ( p_nodbRes );
}

int SArbBinEstablecerRaiz ( SArbolBin * p_arbbObj, SNodoBin * p_nodbObj )
{
	int iRes;

	if ( ES_VALIDO ( p_arbbObj ) )
	{
		p_arbbObj->p_nodbRaiz = p_nodbObj;
		if ( ES_VALIDO ( p_arbbObj->p_nodbRaiz ) )
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

int SArbBinEstaVacio ( SArbolBin * p_arbbObj )
{
	int iRes;

	if ( ES_VALIDO ( p_arbbObj ) )
	{
		if ( ES_NULO ( p_arbbObj->p_nodbRaiz ) )
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
	return ( iRes );
}

int SArbBinNiveles ( SArbolBin * p_arbbObj )
{
	int iNiveles;

	if ( ES_VALIDO ( p_arbbObj ) )
	{
		if ( ES_VALIDO ( p_arbbObj->p_nodbRaiz ) )
		{
			iNiveles = SNodBinNivelesInferiores ( p_arbbObj->p_nodbRaiz ) + 1;
		}
		else
		{
			iNiveles = 0;
		}
	}
	else
	{
		iNiveles = 0;
	}
	return ( iNiveles );
}

int SArbBinNumNodos ( SArbolBin * p_arbbObj )
{
	int iNodos;

	if ( ES_VALIDO ( p_arbbObj ) )
	{
		if ( ES_VALIDO ( p_arbbObj->p_nodbRaiz ) )
		{
			iNodos = SNodBinNodosInferiores ( p_arbbObj->p_nodbRaiz ) + 1;
		}
		else
		{
			iNodos = 0;
		}
	}
	else
	{
		iNodos = 0;
	}
	return ( iNodos );
}

void SArbBinVaciar ( SArbolBin * p_arbbObj )
{
	if ( ES_VALIDO ( p_arbbObj ) )
	{
		if ( ES_VALIDO ( p_arbbObj->p_nodbRaiz ) )
		{
			SArbBinMoverARaiz ( p_arbbObj );
			SNodBinDestruir ( &(p_arbbObj->p_nodbActual), 1 );
			p_arbbObj->p_nodbRaiz = NULL;
		}
	}
}

SNodoBin * SArbBinActual ( SArbolBin * p_arbbObj )
{
	SNodoBin * p_nodbRes;

	if ( ES_VALIDO ( p_arbbObj ) )
	{
		p_nodbRes = p_arbbObj->p_nodbActual;
	}
	else
	{
		p_nodbRes = NULL;
	}
	return ( p_nodbRes );
}

SNodoBin * SArbBinPadre ( SArbolBin * p_arbbObj )
{
	SNodoBin * p_nodbRes;

	if ( ES_VALIDO ( p_arbbObj ) )
	{
		if ( ES_VALIDO ( p_arbbObj->p_nodbActual ) )
		{
			p_nodbRes = SNodBinPadre ( p_arbbObj->p_nodbActual );
		}
		else
		{
			p_nodbRes = NULL;
		}
	}
	else
	{
		p_nodbRes = NULL;
	}
	return ( p_nodbRes );
}

SNodoBin * SArbBinHijoDer ( SArbolBin * p_arbbObj )
{
	SNodoBin * p_nodbRes;

	if ( ES_VALIDO ( p_arbbObj ) )
	{
		if ( ES_VALIDO ( p_arbbObj->p_nodbActual ) )
		{
			p_nodbRes = SNodBinHijoDer ( p_arbbObj->p_nodbActual );
		}
		else
		{
			p_nodbRes = NULL;
		}
	}
	else
	{
		p_nodbRes = NULL;
	}
	return ( p_nodbRes );
}

SNodoBin * SArbBinHijoIzq ( SArbolBin * p_arbbObj )
{
	SNodoBin * p_nodbRes;

	if ( ES_VALIDO ( p_arbbObj ) )
	{
		if ( ES_VALIDO ( p_arbbObj->p_nodbActual ) )
		{
			p_nodbRes = SNodBinHijoIzq ( p_arbbObj->p_nodbActual );
		}
		else
		{
			p_nodbRes = NULL;
		}
	}
	else
	{
		p_nodbRes = NULL;
	}
	return ( p_nodbRes );
}

int SArbBinTienePadre ( SArbolBin * p_arbbObj )
{
	int iRes;

	if ( ES_VALIDO ( p_arbbObj ) )
	{
		if ( ES_VALIDO ( p_arbbObj->p_nodbActual ) )
		{
			iRes = SNodBinTienePadre ( p_arbbObj->p_nodbActual );
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

int SArbBinTieneHijos ( SArbolBin * p_arbbObj )
{
	int iRes;

	if ( ES_VALIDO ( p_arbbObj ) )
	{
		if ( ES_VALIDO ( p_arbbObj->p_nodbActual ) )
		{
			iRes = SNodBinTieneHijos( p_arbbObj->p_nodbActual );
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

int SArbBinTieneHermano ( SArbolBin * p_arbbObj )
{
	int iRes;

	if ( ES_VALIDO ( p_arbbObj ) )
	{
		if ( ES_VALIDO ( p_arbbObj->p_nodbActual ) )
		{
			iRes = SNodBinTieneHermano ( p_arbbObj->p_nodbActual );
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

int SArbBinEsHijoIzqDelPadre ( SArbolBin * p_arbbObj )
{
	int iRes;

	if ( ES_VALIDO ( p_arbbObj ) )
	{
		if ( ES_VALIDO ( p_arbbObj->p_nodbActual ) )
		{
			iRes = SNodBinEsHijoIzqDelPadre ( p_arbbObj->p_nodbActual );
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

int SArbBinEsHijoDerDelPadre ( SArbolBin * p_arbbObj )
{
	int iRes;

	if ( ES_VALIDO ( p_arbbObj ) )
	{
		if ( ES_VALIDO ( p_arbbObj->p_nodbActual ) )
		{
			iRes = SNodBinEsHijoDerDelPadre ( p_arbbObj->p_nodbActual );
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

int SArbBinTieneHijoIzq ( SArbolBin * p_arbbObj )
{
	int iRes;

	if ( ES_VALIDO ( p_arbbObj ) )
	{
		if ( ES_VALIDO ( p_arbbObj->p_nodbActual ) )
		{
			iRes = SNodBinTieneHijoIzq ( p_arbbObj->p_nodbActual );
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

int SArbBinTieneHijoDer ( SArbolBin * p_arbbObj )
{
	int iRes;

	if ( ES_VALIDO ( p_arbbObj ) )
	{
		if ( ES_VALIDO ( p_arbbObj->p_nodbActual ) )
		{
			iRes = SNodBinTieneHijoDer ( p_arbbObj->p_nodbActual );
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

int SArbBinTieneHermanoIzq ( SArbolBin * p_arbbObj )
{
	int iRes;

	if ( ES_VALIDO ( p_arbbObj ) )
	{
		if ( ES_VALIDO ( p_arbbObj->p_nodbActual ) )
		{
			iRes = SNodBinTieneHermanoIzq ( p_arbbObj->p_nodbActual );
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

int SArbBinTieneHermanoDer ( SArbolBin * p_arbbObj )
{
	int iRes;

	if ( ES_VALIDO ( p_arbbObj ) )
	{
		if ( ES_VALIDO ( p_arbbObj->p_nodbActual ) )
		{
			iRes = SNodBinTieneHermanoDer ( p_arbbObj->p_nodbActual );
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

int SArbBinMoverARaiz ( SArbolBin * p_arbbObj )
{
	int iRes;
	
	if ( ES_VALIDO ( p_arbbObj ) )
	{
		p_arbbObj->p_nodbActual = p_arbbObj->p_nodbRaiz;
		if ( ES_VALIDO ( p_arbbObj->p_nodbActual ) )
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

int SArbBinMoverAPadre ( SArbolBin * p_arbbObj )
{
	int iRes;
	
	if ( ES_VALIDO ( p_arbbObj ) )
	{
		if ( ES_VALIDO ( p_arbbObj->p_nodbActual ) )
		{
			p_arbbObj->p_nodbActual = SNodBinPadre ( p_arbbObj->p_nodbActual );
			if ( ES_VALIDO ( p_arbbObj->p_nodbActual ) )
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

int SArbBinMoverAHijoIzq ( SArbolBin * p_arbbObj )
{
	int iRes;
	
	if ( ES_VALIDO ( p_arbbObj ) )
	{
		if ( ES_VALIDO ( p_arbbObj->p_nodbActual ) )
		{
			p_arbbObj->p_nodbActual = SNodBinHijoIzq ( p_arbbObj->p_nodbActual );
			if ( ES_VALIDO ( p_arbbObj->p_nodbActual ) )
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

int SArbBinMoverAHijoDer ( SArbolBin * p_arbbObj )
{
	int iRes;
	
	if ( ES_VALIDO ( p_arbbObj ) )
	{
		if ( ES_VALIDO ( p_arbbObj->p_nodbActual ) )
		{
			p_arbbObj->p_nodbActual = SNodBinHijoDer ( p_arbbObj->p_nodbActual );
			if ( ES_VALIDO ( p_arbbObj->p_nodbActual ) )
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

int SArbBinMoverAHermano ( SArbolBin * p_arbbObj )
{
	int iRes;
	
	if ( ES_VALIDO ( p_arbbObj ) )
	{
		if ( ES_VALIDO ( p_arbbObj->p_nodbActual ) )
		{
			if ( SNodBinEsHijoIzqDelPadre ( p_arbbObj->p_nodbActual ) == 1 )
			{
				if ( SArbBinMoverAPadre ( p_arbbObj ) == 1 )
				{
					iRes = SArbBinMoverAHijoDer ( p_arbbObj );
				}
				else
				{
					iRes = 0;
				}
			}
			else
			{
				if ( SArbBinMoverAPadre ( p_arbbObj ) == 1 )
				{
					iRes = SArbBinMoverAHijoIzq ( p_arbbObj );
				}
				else
				{
					iRes = 0;
				}
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

int SArbBinMoverAPrimPreorden ( SArbolBin * p_arbbObj )
{
	return ( SArbBinMoverARaiz ( p_arbbObj ) );
}

int SArbBinMoverASigPreorden ( SArbolBin * p_arbbObj )
{
	int iRes;

	if ( ES_VALIDO ( p_arbbObj ) )
	{
		if ( ES_VALIDO ( p_arbbObj->p_nodbActual ) )
		{
			if ( SNodBinTieneHijoIzq ( p_arbbObj->p_nodbActual ) == 1 )
			{
				iRes = SArbBinMoverAHijoIzq ( p_arbbObj );
			}
			else if ( SNodBinTieneHijoDer ( p_arbbObj->p_nodbActual ) == 1 )
			{
				iRes = SArbBinMoverAHijoDer ( p_arbbObj );
			}
			else
			{
				/* Hoja: subir hasta un antecesor que sea hijo izquierdo con hermano
				   derecho, y pasar a ese hermano. Si no lo hay, se acabo el recorrido. */
				iRes = 0;
				while ( ( iRes == 0 ) && ( SNodBinTienePadre ( p_arbbObj->p_nodbActual ) == 1 ) )
				{
					if ( ( SNodBinEsHijoIzqDelPadre ( p_arbbObj->p_nodbActual ) == 1 ) &&
						 ( SNodBinTieneHermano ( p_arbbObj->p_nodbActual ) == 1 ) )
					{
						iRes = SArbBinMoverAHermano ( p_arbbObj );
					}
					else
					{
						SArbBinMoverAPadre ( p_arbbObj );
					}
				}
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

int SArbBinMoverAPrimPostorden ( SArbolBin * p_arbbObj )
{
	int iRes;
	
	if ( ES_VALIDO ( p_arbbObj ) )
	{
		iRes = SArbBinMoverARaiz ( p_arbbObj );
		while ( ( iRes == 1 ) && ( SNodBinTieneHijoIzq ( p_arbbObj->p_nodbActual ) == 1 ) )
		{
			iRes = SArbBinMoverAHijoIzq ( p_arbbObj );
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SArbBinMoverASigPostorden ( SArbolBin * p_arbbObj )
{
	int iRes;
	int iMovido;
	
	if ( ES_VALIDO ( p_arbbObj ) )
	{
		if ( ES_VALIDO ( p_arbbObj->p_nodbActual ) )
		{
			iMovido = 0;
			if ( SNodBinEsHijoIzqDelPadre ( p_arbbObj->p_nodbActual ) == 1 )
			{
				if ( SNodBinTieneHermano ( p_arbbObj->p_nodbActual ) == 1 )
				{
					iRes = SArbBinMoverAHermano ( p_arbbObj );
					while ( ( iRes == 1 ) && ( SNodBinTieneHijoIzq ( p_arbbObj->p_nodbActual ) == 1 ) )
					{
						iRes = SArbBinMoverAHijoIzq ( p_arbbObj );
					}
					iMovido = 1;
				}
			}
			if ( iMovido == 0 )
			{
				iRes = SArbBinMoverAPadre ( p_arbbObj );
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

int SArbBinMoverAPrimInorden ( SArbolBin * p_arbbObj )
{
	return ( SArbBinMoverAPrimPostorden ( p_arbbObj ) );
}

int SArbBinMoverASigInorden ( SArbolBin * p_arbbObj )
{
	int iRes;
	
	if ( ES_VALIDO ( p_arbbObj ) )
	{
		if ( ES_VALIDO ( p_arbbObj->p_nodbActual ) )
		{
			if ( SNodBinTieneHijoDer ( p_arbbObj->p_nodbActual ) == 1 )
			{
				/* Con hijo derecho: el mas a la izquierda de ese subarbol. */
				iRes = SArbBinMoverAHijoDer ( p_arbbObj );
				while ( ( iRes == 1 ) && ( SNodBinTieneHijoIzq ( p_arbbObj->p_nodbActual ) == 1 ) )
				{
					iRes = SArbBinMoverAHijoIzq ( p_arbbObj );
				}
			}
			else
			{
				/* Sin hijo derecho: subir mientras se sea hijo derecho, y pasar al padre. */
				iRes = 1;
				while ( ( iRes == 1 ) && ( SNodBinEsHijoDerDelPadre ( p_arbbObj->p_nodbActual ) == 1 ) )
				{
					iRes = SArbBinMoverAPadre ( p_arbbObj );
				}
				iRes = SArbBinMoverAPadre ( p_arbbObj );
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

void SArbBinDesposicionar ( SArbolBin * p_arbbObj )
{
	if ( ES_VALIDO ( p_arbbObj ) )
	{
		p_arbbObj->p_nodbActual = NULL;
	}
}

int	SArbBinEstaPosicionado ( SArbolBin * p_arbbObj )
{
	int iRes;

	if ( ES_VALIDO ( p_arbbObj ) )
	{
		if ( ES_VALIDO ( p_arbbObj->p_nodbActual ) )
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

int SArbBinEnraizar ( SArbolBin * p_arbbObj, SNodoBin * p_nodbObj )
{
	int iRes;

	if ( ES_VALIDO ( p_arbbObj ) )
	{
		if ( ES_VALIDO ( p_arbbObj->p_nodbActual ) && ES_VALIDO ( p_nodbObj ) )
		{
			if ( SNodBinTieneHijoDer ( p_arbbObj->p_nodbActual ) == 1 )
			{
				iRes = 0;
			}
			else
			{
				SNodBinEmpadronar ( p_nodbObj, p_arbbObj->p_nodbActual );
				if ( SNodBinTieneHijoIzq ( p_arbbObj->p_nodbActual ) == 0 )
				{
					if ( SNodBinEstHijoIzq ( p_arbbObj->p_nodbActual, p_nodbObj, 1 ) == 1 )
					{
						iRes = SArbBinMoverAHijoIzq ( p_arbbObj );
					}
					else
					{
						iRes = 0;
					}
				}
				else
				{
					if ( SNodBinEstHijoDer ( p_arbbObj->p_nodbActual, p_nodbObj, 0 ) == 1 )
					{
						iRes = SArbBinMoverAHijoDer ( p_arbbObj );
					}
					else
					{
						iRes = 0;
					}
				}
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

int SArbBinVerificar ( SArbolBin * p_arbbObj, int iCorregir )
{
	int iRes;

	if ( ES_VALIDO ( p_arbbObj ) )
	{
		if ( ES_VALIDO ( p_arbbObj->p_nodbRaiz ) )
		{
			iRes = SNodBinVerificar ( p_arbbObj->p_nodbRaiz, iCorregir );
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



