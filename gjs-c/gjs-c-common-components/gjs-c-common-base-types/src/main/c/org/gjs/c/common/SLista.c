#include "SLista.h"


#include "TiposBasicosConfig.h"




SLista * SLisCrear ()
{
	SLista * p_lisObj;
	
	p_lisObj = (SLista *) MemReservar ( sizeof ( SLista ) );
	if ( ES_VALIDO ( p_lisObj ) )
	{
		p_lisObj->p_elmPrimero = NULL;
		p_lisObj->p_elmUltimo = NULL;
		p_lisObj->p_elmActual = NULL;
		p_lisObj->iNumElementos = 0;
		p_lisObj->iPos = -1;
	}
	return ( p_lisObj );
}

void SLisDestruir ( SLista ** p_p_lisObj )
{
	SLista * p_lisObj;
	
	if ( ES_VALIDO ( p_p_lisObj ) )
	{
		p_lisObj = *p_p_lisObj;

		if ( ES_VALIDO ( p_lisObj ) )
		{
			SLisVaciar ( p_lisObj );
			MemLiberar ( (void **) p_p_lisObj );
		}
	}
}

int SLisEsValida ( SLista * p_lisObj )
{
	int iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		if ( p_lisObj->iNumElementos > 0 )
		{
			if ( ES_VALIDO ( p_lisObj->p_elmPrimero ) &&
				 ES_VALIDO ( p_lisObj->p_elmUltimo  ) )
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
			if ( ( p_lisObj->p_elmPrimero == NULL ) &&
				 ( p_lisObj->p_elmUltimo == NULL ) &&
				 ( p_lisObj->iPos == -1 ) && 
				 ( p_lisObj->p_elmActual == NULL ) )
			{
				iRes = 1;
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
	return ( iRes );
}

int SLisNumElementos ( SLista * p_lisObj )
{
	int iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iRes = p_lisObj->iNumElementos;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLisEstaVacia ( SLista * p_lisObj )
{
	int iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		if ( p_lisObj->iNumElementos <= 0 )
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

/* Acceso por indice SIN tocar el cursor. Antes se resolvia con SLisMoverA, que
   mueve el cursor de la lista, y eso convertia cualquier consulta —Elemento,
   Min, Max, EstaOrdenada…— en una operacion que le cambiaba la posicion al que
   estuviera iterando.

   Se entra por el extremo mas cercano al indice pedido, asi que una llamada
   suelta cuesta como mucho media lista. OJO: eso hace que recorrer la lista
   ENTERA por indice sea cuadratico, porque ya no se aprovecha la posicion de la
   llamada anterior. Para recorrer de principio a fin hay que usar el cursor
   ( SLisInicio / SLisSiguiente / SLisActual ), no esta. */
SElemento * SLisElemento ( SLista * p_lisObj, int iElem )
{
	SElemento * p_elmRes;
	int			iPos;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		if ( ( iElem >= 0 ) && ( iElem < p_lisObj->iNumElementos ) )
		{
			if ( iElem < p_lisObj->iNumElementos / 2 )
			{
				p_elmRes = p_lisObj->p_elmPrimero;
				iPos = 0;
				while ( ( iPos < iElem ) && 
						ES_VALIDO ( p_elmRes ) )
				{
					p_elmRes = SElmSucesor ( p_elmRes );
					iPos = iPos + 1;
				}
			}
			else
			{
				p_elmRes = p_lisObj->p_elmUltimo;
				iPos = p_lisObj->iNumElementos - 1;
				/* > y no >=: con >= se da un paso de mas y se acaba en
				   iElem - 1. La rama de arriba, la que entra por el principio,
				   ya usaba la comparacion estricta. */
				while ( ( iPos > iElem ) &&
						ES_VALIDO ( p_elmRes ) )
				{
					p_elmRes = SElmAntecesor ( p_elmRes );
					iPos = iPos - 1;
				}
			}
		}
		else
		{
			p_elmRes = NULL;
		}
	}
	else
	{
		p_elmRes = NULL;
	}
	return ( p_elmRes );
}

int SLisEstablecerElem ( SLista * p_lisObj, int iElem, SElemento * p_elmObj )
{
	int iRes;

	if ( ( SLisEsValida ( p_lisObj ) == 1 ) && ES_VALIDO ( p_elmObj ) )
	{
		if ( ( iElem >= 0 ) && ( iElem < p_lisObj->iNumElementos ) )
		{
			SLisMoverA ( p_lisObj, iElem );
			iRes = SLisEstablecer ( p_lisObj, p_elmObj );
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

int SLisInsertarElem ( SLista * p_lisObj, int iPosAnt, SElemento * p_elmObj )
{
	int iRes;

	if ( ( SLisEsValida ( p_lisObj ) == 1 ) && ES_VALIDO ( p_elmObj ) )
	{
		if ( iPosAnt < 0 ) 
		{
			SLisInicio ( p_lisObj );
			iRes = SLisInsertarDelante ( p_lisObj, p_elmObj );
		}
		else if ( iPosAnt >= p_lisObj->iNumElementos )
		{
			SLisFinal ( p_lisObj );
			iRes = SLisInsertarDetras ( p_lisObj, p_elmObj );
		}
		else  
		{
			SLisMoverA ( p_lisObj, iPosAnt );
			if ( ES_NULO ( p_lisObj->p_elmActual ) ) 
			{
				iRes = -1;
			}
			else 
			{
				iRes = SLisInsertar ( p_lisObj, p_elmObj );
			}
		}
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int SLisInsertarAlInicio ( SLista * p_lisObj, SElemento * p_elmObj )
{
	return ( SLisInsertarElem ( p_lisObj, -1, p_elmObj ) );
}

int SLisInsertarAlFinal ( SLista * p_lisObj, SElemento * p_elmObj )
{
	int iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iRes = SLisInsertarElem ( p_lisObj, p_lisObj->iNumElementos, p_elmObj );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int SLisEliminarElem ( SLista * p_lisObj, int iElem )
{
	int	iRes;

	if ( SLisEsValida ( p_lisObj ) == 1 ) 
	{
		SLisMoverA ( p_lisObj, iElem );
		iRes = SLisEliminar ( p_lisObj );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

SElemento * SLisExtraerElem ( SLista * p_lisObj, int iElem )
{
	SElemento * p_elmRes;

	if ( SLisEsValida ( p_lisObj ) == 1 ) 
	{
		SLisMoverA ( p_lisObj, iElem );
		p_elmRes = SLisExtraer ( p_lisObj );
	}
	else
	{
		p_elmRes = NULL;
	}
	return ( p_elmRes );
}

int SLisVaciar ( SLista * p_lisObj )
{
	int	iRes;

	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		iRes = 1;
		while ( ( p_lisObj->iNumElementos > 0 ) && ( iRes == 1 ) )
		{
			SLisInicio ( p_lisObj );
			iRes = SLisEliminar ( p_lisObj );
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLisPosicion ( SLista * p_lisObj )
{
	int	iRes;

	if ( SLisEsValida ( p_lisObj ) == 1 ) 
	{
		iRes = p_lisObj->iPos;
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

SElemento * SLisActual ( SLista * p_lisObj )
{
	SElemento * p_elmRes;

	if ( SLisEsValida ( p_lisObj ) == 1 ) 
	{
		p_elmRes = p_lisObj->p_elmActual;
		if ( ES_NULO ( p_elmRes ) )
		{
			ERROR_ESTABLECER( ERR_POSICION_INVALIDA );
		}
	}
	else
	{
		p_elmRes = NULL;
	}
	return ( p_elmRes );
}

void SLisInicio ( SLista * p_lisObj )
{
	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		if ( p_lisObj->iNumElementos > 0 )
		{
			p_lisObj->iPos = 0;
			p_lisObj->p_elmActual = p_lisObj->p_elmPrimero;
		}
		else
		{
			p_lisObj->iPos = -1;
			p_lisObj->p_elmActual = NULL;
		}
	}
}

void SLisFinal ( SLista * p_lisObj )
{
	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		if ( p_lisObj->iNumElementos > 0 )
		{
			p_lisObj->iPos = p_lisObj->iNumElementos - 1;
			p_lisObj->p_elmActual = p_lisObj->p_elmUltimo;
		}
		else
		{
			p_lisObj->iPos = -1;
			p_lisObj->p_elmActual = NULL;
		}
	}
}

void SLisSiguiente ( SLista * p_lisObj )
{
	if ( SLisEsValida ( p_lisObj ) == 1 ) 
	{
		if ( ES_VALIDO ( p_lisObj->p_elmActual ) )
		{
			p_lisObj->iPos = p_lisObj->iPos + 1;
			p_lisObj->p_elmActual = SElmSucesor ( p_lisObj->p_elmActual );
		}
		else
		{
			p_lisObj->iPos = -1;
			p_lisObj->p_elmActual = NULL;
		}
	}
}

void SLisAnterior ( SLista * p_lisObj )
{
	if ( SLisEsValida ( p_lisObj ) == 1 ) 
	{
		if ( ES_VALIDO ( p_lisObj->p_elmActual ) )
		{
			p_lisObj->iPos = p_lisObj->iPos - 1;
			p_lisObj->p_elmActual = SElmAntecesor ( p_lisObj->p_elmActual );
		}
		else
		{
			p_lisObj->iPos = -1;
			p_lisObj->p_elmActual = NULL;
		}
	}
}

void SLisMoverA ( SLista * p_lisObj, int iElem )
{
	if ( SLisEsValida ( p_lisObj ) == 1 ) 
	{
		if ( ( iElem >= 0 ) && ( iElem < p_lisObj->iNumElementos ) )
		{
			if ( ES_VALIDO ( p_lisObj->p_elmActual ) && 
				 ( p_lisObj->iPos >= 0 ) && 
				 ( p_lisObj->iPos < p_lisObj->iNumElementos ) )
			{
				while ( ( iElem > p_lisObj->iPos ) &&
						ES_VALIDO ( p_lisObj->p_elmActual ) )
				{
					p_lisObj->p_elmActual = SElmSucesor ( p_lisObj->p_elmActual );
					p_lisObj->iPos = p_lisObj->iPos + 1;
				}

				while ( ( iElem < p_lisObj->iPos ) && 
						ES_VALIDO ( p_lisObj->p_elmActual ) )
				{
					p_lisObj->p_elmActual = SElmAntecesor ( p_lisObj->p_elmActual );
					p_lisObj->iPos = p_lisObj->iPos - 1;
				}
			}
			else
			{
				if ( iElem < p_lisObj->iNumElementos / 2 )
				{
					p_lisObj->p_elmActual = p_lisObj->p_elmPrimero;
					p_lisObj->iPos = 0;
					while ( ( p_lisObj->iPos < iElem ) && 
							ES_VALIDO ( p_lisObj->p_elmActual ) )
					{
						p_lisObj->p_elmActual = SElmSucesor ( p_lisObj->p_elmActual );
						p_lisObj->iPos = p_lisObj->iPos + 1;
					}
				}
				else
				{
					p_lisObj->p_elmActual = p_lisObj->p_elmUltimo;
					p_lisObj->iPos = p_lisObj->iNumElementos - 1;
					/* > y no >=: con >= se da un paso de mas y se acaba en
					   iElem - 1. La rama de arriba, la que entra por el principio,
					   ya usaba la comparacion estricta. */
					while ( ( p_lisObj->iPos > iElem ) &&
							ES_VALIDO ( p_lisObj->p_elmActual ) )
					{
						p_lisObj->p_elmActual = SElmAntecesor ( p_lisObj->p_elmActual );
						p_lisObj->iPos = p_lisObj->iPos - 1;
					}
				}
			}
		}
		else
		{
			p_lisObj->iPos = -1;
			p_lisObj->p_elmActual = NULL;
		}
	}
}

void SLisDeposicionar ( SLista * p_lisObj )
{
	if ( ES_VALIDO ( p_lisObj ) )
	{
		p_lisObj->iPos = -1;
		p_lisObj->p_elmActual = NULL;
	}
}

int SLisBuscar ( SLista * p_lisObj, SBloque * p_blqDatos )
{
	int			iRes;
	int			iEnc;
	SElemento * p_elmObj;

	if ( ( SLisEsValida ( p_lisObj ) == 1 ) && ES_VALIDO ( p_blqDatos ) )
	{
		p_elmObj = p_lisObj->p_elmPrimero;
		iRes = 0;
		iEnc = 0;
		while ( ( iRes < p_lisObj->iNumElementos ) && ( iEnc == 0 ) &&
			ES_VALIDO ( p_elmObj ) )
		{
			iEnc = SElmEsIgualBlq ( p_elmObj, p_blqDatos );
			if ( iEnc == 0 )
			{
				p_elmObj = SElmSucesor ( p_elmObj );
				iRes = iRes + 1;
			}
		}
		if ( iEnc == 0 )
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

int SLisBuscarExt ( SLista * p_lisObj, byte * p_byDatos )
{
	int			iRes;
	int			iEnc;
	SElemento * p_elmObj;

	if ( ( SLisEsValida ( p_lisObj ) == 1 ) && ES_VALIDO ( p_byDatos ) )
	{
		p_elmObj = p_lisObj->p_elmPrimero;
		iRes = 0;
		iEnc = 0;
		while ( ( iRes < p_lisObj->iNumElementos ) && ( iEnc == 0 ) &&
			ES_VALIDO ( p_elmObj ) )
		{
			iEnc = SElmEsIgualExt ( p_elmObj, p_byDatos );
			if ( iEnc == 0 )
			{
				p_elmObj = SElmSucesor ( p_elmObj );
				iRes = iRes + 1;
			}
		}
		if ( iEnc == 0 )
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

int SLisEsNulo ( SLista * p_lisObj )
{
	int iRes;

	if ( SLisEsValida ( p_lisObj ) == 1 ) 
	{
		if ( ES_VALIDO ( p_lisObj->p_elmActual ) )
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

int SLisEstaEnFinal ( SLista * p_lisObj )
{
	int iRes;

	if ( SLisEsValida ( p_lisObj ) == 1 ) 
	{
		if ( ES_VALIDO ( p_lisObj->p_elmActual ) && 
			 ( p_lisObj->iPos == p_lisObj->iNumElementos - 1 ) )
		{
			iRes = 1;
		}
		else if ( ( p_lisObj->iNumElementos == 0 ) && ( p_lisObj->iPos == -1 ) )
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

int SLisEstaEnInicio ( SLista * p_lisObj )
{
	int iRes;

	if ( SLisEsValida ( p_lisObj ) == 1 ) 
	{
		if ( ES_VALIDO ( p_lisObj->p_elmActual ) && ( p_lisObj->iPos == 0 ) )
		{
			iRes = 1;
		}
		else if ( ( p_lisObj->iNumElementos == 0 ) && ( p_lisObj->iPos == -1 ) )
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

int SLisEstablecer ( SLista * p_lisObj, SElemento * p_elmObj )
{
	int iRes;

	if ( ( SLisEsValida ( p_lisObj ) == 1 ) && ES_VALIDO ( p_elmObj ) )
	{
		if ( ( p_lisObj->iPos >= 0 ) && 
			 ( p_lisObj->iPos < p_lisObj->iNumElementos ) && 
			 ES_VALIDO ( p_lisObj->p_elmActual ) )
		{
			SElmEncadenarSucesor ( p_elmObj, SElmSucesor ( p_lisObj->p_elmActual ) );
			SElmEncadenarAntecesor ( p_elmObj, SElmAntecesor ( p_lisObj->p_elmActual ) );

			SElmDestruir ( &(p_lisObj->p_elmActual) ); 
			p_lisObj->p_elmActual = p_elmObj;
			
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


int SLisInsertar ( SLista * p_lisObj, SElemento * p_elmObj )
{
	return ( SLisInsertarDetras ( p_lisObj, p_elmObj ) );
}

int SLisInsertarDelante ( SLista * p_lisObj, SElemento * p_elmObj )
{
	int iRes;

	if ( ( SLisEsValida ( p_lisObj ) == 1 ) && ES_VALIDO ( p_elmObj ) )
	{
		SElmDesencadenar ( p_elmObj );

		if ( p_lisObj->iNumElementos <= 0 )
		{
			p_lisObj->p_elmPrimero = p_elmObj;
			p_lisObj->p_elmUltimo = p_elmObj;
			p_lisObj->iNumElementos = 1;

			SLisInicio ( p_lisObj );
			iRes = 1;
		}
		else if ( ( p_lisObj->iPos >= 0 ) && 
				  ( p_lisObj->iPos < p_lisObj->iNumElementos ) && 
				  ES_VALIDO ( p_lisObj->p_elmActual ) )
		{
			/* Empalme: antiguo antecesor -> p_elmObj -> actual. */
			SElmEncadenarAntecesor ( p_elmObj, SElmAntecesor ( p_lisObj->p_elmActual ) );
			SElmEncadenarAntecesor ( p_lisObj->p_elmActual, p_elmObj );

			if ( p_lisObj->p_elmPrimero == p_lisObj->p_elmActual )
			{
				p_lisObj->p_elmPrimero = p_elmObj;
			}
			p_lisObj->p_elmActual = p_elmObj;

			p_lisObj->iNumElementos = p_lisObj->iNumElementos + 1;
			
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

int SLisInsertarDetras ( SLista * p_lisObj, SElemento * p_elmObj )
{
	int iRes;

	if ( ( SLisEsValida ( p_lisObj ) == 1 ) && ES_VALIDO ( p_elmObj ) )
	{
		SElmDesencadenar ( p_elmObj );

		if ( p_lisObj->iNumElementos <= 0 )
		{
			p_lisObj->p_elmPrimero = p_elmObj;
			p_lisObj->p_elmUltimo = p_elmObj;
			p_lisObj->iNumElementos = 1;

			SLisInicio ( p_lisObj );
			iRes = 1;
		}
		else if ( ( p_lisObj->iPos >= 0 ) && 
				  ( p_lisObj->iPos < p_lisObj->iNumElementos ) && 
				  ES_VALIDO ( p_lisObj->p_elmActual ) )
		{
			/* Empalme: actual -> p_elmObj -> antiguo sucesor. */
			SElmEncadenarSucesor ( p_elmObj, SElmSucesor ( p_lisObj->p_elmActual ) );
			SElmEncadenarSucesor ( p_lisObj->p_elmActual, p_elmObj );

			if ( p_lisObj->p_elmUltimo == p_lisObj->p_elmActual )
			{
				p_lisObj->p_elmUltimo = p_elmObj;
			}
			p_lisObj->p_elmActual = p_elmObj;
			p_lisObj->iPos = p_lisObj->iPos + 1;

			p_lisObj->iNumElementos = p_lisObj->iNumElementos + 1;
			
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

int SLisEliminar ( SLista * p_lisObj )
{
	int			iRes;
	SElemento * p_elmAnt;
	SElemento * p_elmSig;

	if ( SLisEsValida ( p_lisObj ) == 1 ) 
	{
		if ( ( p_lisObj->iPos >= 0 ) && 
			 ( p_lisObj->iPos < p_lisObj->iNumElementos ) && 
			 ES_VALIDO ( p_lisObj->p_elmActual ) )
		{
			p_elmAnt = SElmAntecesor ( p_lisObj->p_elmActual );
			p_elmSig = SElmSucesor ( p_lisObj->p_elmActual );

			SElmDestruir ( &(p_lisObj->p_elmActual) );
			p_lisObj->iNumElementos = p_lisObj->iNumElementos - 1;

			if ( ES_VALIDO ( p_elmAnt ) )
			{
				SElmEncadenarSucesor ( p_elmAnt, p_elmSig );
			}
			else
			{
				SElmEncadenarAntecesor ( p_elmSig, p_elmAnt );
				p_lisObj->p_elmPrimero = p_elmSig;
			}

			if ( ES_VALIDO ( p_elmSig ) )
			{
				p_lisObj->p_elmActual = p_elmSig;
			}
			else
			{
				p_lisObj->p_elmUltimo = p_elmAnt;
				p_lisObj->p_elmActual = p_elmAnt;
				p_lisObj->iPos = p_lisObj->iPos - 1;
			}

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

SElemento * SLisExtraer ( SLista * p_lisObj )
{
	SElemento *	p_elmRes;
	SElemento * p_elmAnt;
	SElemento * p_elmSig;

	if ( SLisEsValida ( p_lisObj ) == 1 ) 
	{
		if ( ( p_lisObj->iPos >= 0 ) && 
			 ( p_lisObj->iPos < p_lisObj->iNumElementos ) && 
			 ES_VALIDO ( p_lisObj->p_elmActual ) )
		{
			p_elmRes = p_lisObj->p_elmActual;
			p_elmAnt = SElmAntecesor ( p_lisObj->p_elmActual );
			p_elmSig = SElmSucesor ( p_lisObj->p_elmActual );

			p_lisObj->iNumElementos = p_lisObj->iNumElementos - 1;

			if ( ES_VALIDO ( p_elmAnt ) )
			{
				SElmEncadenarSucesor ( p_elmAnt, p_elmSig );
			}
			else
			{
				SElmEncadenarAntecesor ( p_elmSig, p_elmAnt );
				p_lisObj->p_elmPrimero = p_elmSig;
			}

			if ( ES_VALIDO ( p_elmSig ) )
			{
				p_lisObj->p_elmActual = p_elmSig;
			}
			else
			{
				p_lisObj->p_elmUltimo = p_elmAnt;
				p_lisObj->p_elmActual = p_elmAnt;
				p_lisObj->iPos = p_lisObj->iPos - 1;
			}

			/* El extraido se devuelve limpio: solo se anulan sus enlaces propios. */
			SElmDeposicionar ( p_elmRes );
		}
		else
		{
			p_elmRes = NULL;
		}
	}
	else
	{
		p_elmRes = NULL;
	}
	return ( p_elmRes );
}

