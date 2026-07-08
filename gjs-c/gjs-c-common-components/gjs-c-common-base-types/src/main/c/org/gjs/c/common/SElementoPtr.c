#include "SElementoPtr.h"



#include "TiposBasicosConfig.h"



SElementoPtr * SElpCrear ( byte * p_byDatos, int iLiberar )
{
	SElementoPtr * p_elpObj;
	
	if ( ES_VALIDO ( p_byDatos ) && BOOL_VALIDO ( iLiberar ) )
	{
		p_elpObj = (SElementoPtr *) MemReservar ( sizeof ( SElementoPtr ) );
		if ( ES_VALIDO ( p_elpObj ) )
		{
			p_elpObj->p_elpAnt = NULL;
			p_elpObj->p_elpSig = NULL;

			p_elpObj->p_byDatos = p_byDatos;
			if ( ES_VALIDO ( p_elpObj->p_byDatos ) )
			{
				if ( MemEsValida ( (void *) p_byDatos ) == 0 )
				{
					p_elpObj->iLiberar = 0;
				}
				else
				{
					p_elpObj->iLiberar = iLiberar;
				}
			}
			else
			{
				p_elpObj->iLiberar = 0;
			}
		}
	}
	else
	{
		p_elpObj = NULL;
	}
	return ( p_elpObj );
}

void SElpDestruir ( SElementoPtr ** p_p_elpObj )
{
	SElementoPtr * p_elpObj;
	
	if ( ES_VALIDO ( p_p_elpObj ) )
	{
		p_elpObj = *p_p_elpObj;

		if ( ES_VALIDO ( p_elpObj ) )
		{
			if ( p_elpObj->iLiberar == 1 )
			{
				MemLiberar ( (void **) &(p_elpObj->p_byDatos) );
			}
			MemLiberar ( (void **) p_p_elpObj );
		}
	}
}

int SElpEsValido ( SElementoPtr * p_elpObj )
{
	int iRes;

	if ( ES_VALIDO ( p_elpObj ) )
	{
		if ( ES_VALIDO ( p_elpObj->p_byDatos ) )
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

byte * SElpDatos ( SElementoPtr * p_elpObj )
{
	byte * p_byRes;

	if ( ES_VALIDO ( p_elpObj ) )
	{
		p_byRes = p_elpObj->p_byDatos;
	}
	else
	{
		p_byRes = NULL;
	}
	return ( p_byRes );
}

int SElpModificar ( SElementoPtr * p_elpObj, byte * p_byDatos, int iLiberar )
{
	int iRes;

	if ( ES_VALIDO ( p_elpObj ) && ES_VALIDO ( p_byDatos ) && BOOL_VALIDO ( iLiberar ) )
	{
		if ( p_elpObj->iLiberar == 1 )
		{
			MemLiberar ( (void **) &(p_elpObj->p_byDatos) );
		}

		p_elpObj->p_byDatos = p_byDatos;
		if ( ES_VALIDO ( p_elpObj->p_byDatos ) )
		{
			p_elpObj->iLiberar = iLiberar;
		}
		else
		{
			p_elpObj->iLiberar = 0;
		}
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

SElementoPtr * SElpAntecesor ( SElementoPtr * p_elpObj )
{
	SElementoPtr * p_elpRes;

	if ( ES_VALIDO ( p_elpObj ) )
	{
		p_elpRes = (SElementoPtr *) p_elpObj->p_elpAnt;
	}
	else
	{
		p_elpRes = NULL;
	}
	return ( p_elpRes );
}

SElementoPtr * SElpSucesor ( SElementoPtr * p_elpObj )
{
	SElementoPtr * p_elpRes;

	if ( ES_VALIDO ( p_elpObj ) )
	{
		p_elpRes = (SElementoPtr *) p_elpObj->p_elpSig;
	}
	else
	{
		p_elpRes = NULL;
	}
	return ( p_elpRes );
}

int SElpTieneAntecesor ( SElementoPtr * p_elpObj )
{
	int iRes;

	if ( ES_VALIDO ( p_elpObj ) )
	{
		if ( ES_VALIDO ( p_elpObj->p_elpAnt ) )
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

int SElpTieneSucesor ( SElementoPtr * p_elpObj )
{
	int iRes;

	if ( ES_VALIDO ( p_elpObj ) )
	{
		if ( ES_VALIDO ( p_elpObj->p_elpSig ) )
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

int SElpEncadenarAntecesor ( SElementoPtr * p_elpObj, SElementoPtr * p_elpAnt )
{
	int iRes;

	if ( ES_VALIDO ( p_elpObj ) )
	{
		if ( p_elpObj->p_elpAnt != (void *) p_elpAnt )
		{
			p_elpObj->p_elpAnt = (void *) p_elpAnt;
			SElpEncadenarSucesor ( p_elpAnt, p_elpObj );
		}
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SElpEncadenarSucesor ( SElementoPtr * p_elpObj, SElementoPtr * p_elpSuc )
{
	int iRes;

	if ( ES_VALIDO ( p_elpObj ) )
	{
		if ( p_elpObj->p_elpSig != (void *) p_elpSuc )
		{
			p_elpObj->p_elpSig = (void *) p_elpSuc;
			SElpEncadenarAntecesor ( p_elpSuc, p_elpObj );
		}
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SElpDesencadenarAntecesor ( SElementoPtr * p_elpObj )
{
	int iRes;

	if ( ES_VALIDO ( p_elpObj ) )
	{
		if ( ES_VALIDO ( p_elpObj->p_elpAnt ) )
		{
			((SElementoPtr *) p_elpObj->p_elpAnt)->p_elpSig = NULL;
		}
		p_elpObj->p_elpAnt = NULL;
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SElpDesencadenarSucesor ( SElementoPtr * p_elpObj )
{
	int iRes;

	if ( ES_VALIDO ( p_elpObj ) )
	{
		if ( ES_VALIDO ( p_elpObj->p_elpSig ) )
		{
			((SElementoPtr *) p_elpObj->p_elpSig)->p_elpAnt = NULL;
		}
		p_elpObj->p_elpSig = NULL;
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SElpDesencadenar ( SElementoPtr * p_elpObj )
{
	int iRes;

	if ( ES_VALIDO ( p_elpObj ) )
	{
		if ( ES_VALIDO ( p_elpObj->p_elpSig ) )
		{
			SElpDesencadenarAntecesor ( (SElementoPtr *) p_elpObj->p_elpSig );
		}
		if ( ES_VALIDO ( p_elpObj->p_elpAnt ) )
		{
			SElpDesencadenarSucesor ( (SElementoPtr *) p_elpObj->p_elpAnt );
		}

		p_elpObj->p_elpAnt = NULL;
		p_elpObj->p_elpSig = NULL;
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SElpEsIgual ( SElementoPtr * p_elpObj1, SElementoPtr * p_elpObj2, int iNumBytes )
{
	int	iRes;

	if ( ES_VALIDO ( p_elpObj1 ) && ES_VALIDO ( p_elpObj2 ) )
	{
		iRes = MemEsIgual ( (void *) SElpDatos ( p_elpObj1 ), (void *) SElpDatos ( p_elpObj2 ), iNumBytes );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SElpEsIgualExt ( SElementoPtr * p_elpObj, byte * p_byObj, int iNumBytes )
{
	int	iRes;

	if ( ES_VALIDO ( p_elpObj ) && ES_VALIDO ( p_byObj ) )
	{
		iRes = MemEsIgual ( (void *) SElpDatos ( p_elpObj ), (void *) p_byObj, iNumBytes );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int	SElpLiberacionMemoriaActivada ( SElementoPtr * p_elpObj )
{
	int iRes;

	if ( ES_VALIDO ( p_elpObj ) )
	{
		iRes = p_elpObj->iLiberar;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

// NOTA:No se duplica el contenido, se copia el puntero (Liberar=0).
//      Retorna un elemento duplicado pero desencadenado:
SElementoPtr * SElpDuplicar ( SElementoPtr * p_elpObj )
{
	byte *	p_byDatos;
	SElementoPtr * p_elpDup;

	if ( SElpEsValido ( p_elpObj ) == 1 )
	{
		p_byDatos = p_elpObj->p_byDatos;
		if ( ES_VALIDO ( p_byDatos ) )
		{
			p_elpDup = SElpCrear ( p_elpObj->p_byDatos, 0 );
		}
		else
		{
			p_elpDup = NULL;
		}
	}
	else
	{
		p_elpDup = NULL;
	}
	return ( p_elpDup );
}


