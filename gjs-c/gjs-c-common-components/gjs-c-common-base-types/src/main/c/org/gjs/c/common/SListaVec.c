
#include "SListaVec.h"


#include "TiposBasicosConfig.h"



typedef struct
{
	void * 	p_vValor;

	int		iAnt;
	int		iSig;
} SVLisElem;


SVLisElem * SVLisElCrear ( void * p_vValor )
{
	SVLisElem * p_liselObj;

	p_liselObj = (SVLisElem *) MemReservar ( sizeof ( SVLisElem ) );
	if ( ES_VALIDO ( p_liselObj ) && ES_VALIDO ( p_vValor ) )
	{
		p_liselObj->p_vValor = p_vValor;

		p_liselObj->iAnt = -1;
		p_liselObj->iSig = -1;
	}
	return ( p_liselObj );
}

void SVLisElDestruir ( SVLisElem ** p_p_liselObj )
{
	SVLisElem * p_liselObj;

	if ( ES_VALIDO ( p_p_liselObj ) )
	{
		p_liselObj = *p_p_liselObj;
		if ( ES_VALIDO ( p_liselObj ) )
		{
			MemLiberar ( (void **) p_p_liselObj );
		}
	}
}

int SVLisElEsValido ( SVLisElem * p_liselObj )
{
	int iRes;

	if ( ES_VALIDO ( p_liselObj ) )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

void * SVLisElValor ( SVLisElem * p_liselObj )
{
	void * p_vRes;

	if ( ES_VALIDO ( p_liselObj ) )
	{
		p_vRes = p_liselObj->p_vValor;
	}
	else
	{
		p_vRes = NULL;
	}
	return ( p_vRes );
}

int SVLisElEstablecerValor ( SVLisElem * p_liselObj, void * p_vValor )
{
	int iRes;

	if ( ES_VALIDO ( p_liselObj ) )
	{
		p_liselObj->p_vValor = p_vValor;
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SVLisElAnterior ( SVLisElem * p_liselObj )
{
	int iRes;

	if ( ES_VALIDO ( p_liselObj ) )
	{
		iRes = p_liselObj->iAnt;
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int SVLisElSiguiente ( SVLisElem * p_liselObj )
{
	int iRes;

	if ( ES_VALIDO ( p_liselObj ) )
	{
		iRes = p_liselObj->iSig;
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

void SVLisElEncadenarAnterior ( SVLisElem * p_liselObj, int iAnt )
{
	if ( ES_VALIDO ( p_liselObj ) )
	{
		p_liselObj->iAnt = iAnt;
	}
}

void SVLisElEncadenarSiguiente ( SVLisElem * p_liselObj, int iSig )
{
	if ( ES_VALIDO ( p_liselObj ) )
	{
		p_liselObj->iSig = iSig;
	}
}

void SVLisElDesencadenarAnterior ( SVLisElem * p_liselObj )
{
	if ( ES_VALIDO ( p_liselObj ) )
	{
		p_liselObj->iAnt = -1;
	}
}

void SVLisElDesencadenarSiguiente ( SVLisElem * p_liselObj )
{
	if ( ES_VALIDO ( p_liselObj ) )
	{
		p_liselObj->iSig = -1;
	}
}

SVLisElem ** SVLisContenido ( SVLista * p_lisObj )
{
  return ( ( SVLisElem ** ) p_lisObj->p_vContenido );
}

SVLista * SVLisCrear ( int iMaxElems, int iLiberar )
{
	SVLista * p_lisObj;

	if ( iMaxElems > 0 )
	{
		p_lisObj = (SVLista *) MemReservar ( sizeof ( SVLista ) );
		if ( ES_VALIDO ( p_lisObj ) )
		{
			p_lisObj->iMaxElems = iMaxElems;

			p_lisObj->p_vContenido = MemReservar ( iMaxElems * sizeof ( SVLisElem * ) );
			p_lisObj->iNumElems = 0;
			p_lisObj->iPrim = -1;
			p_lisObj->iUlt = -1;
			p_lisObj->iLib = 0;
			p_lisObj->iAct = -1;
			p_lisObj->iLiberar = BoolNormalizar ( iLiberar );
		}
	}
	else
	{
		p_lisObj = NULL;
	}
	return ( p_lisObj );
}

void SVLisDestruir ( SVLista ** p_p_lisObj )
{
	SVLista * p_lisObj;

	if ( ES_VALIDO ( p_p_lisObj ) )
	{
		p_lisObj = *p_p_lisObj;

		if ( ES_VALIDO ( p_lisObj ) )
		{
			SVLisVaciar ( p_lisObj );
			MemLiberar ( (void **) &(p_lisObj->p_vContenido) );
			MemLiberar ( (void **) p_p_lisObj );
		}
	}
}

int SVLisEsValida ( SVLista * p_lisObj )
{
	int iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		if ( ( p_lisObj->iMaxElems > 0 ) && ES_VALIDO ( p_lisObj->p_vContenido ) )
		{
			if ( p_lisObj->iNumElems < p_lisObj->iMaxElems )
			{
				if ( p_lisObj->iLib >= 0 )
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
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SVLisNumElementos ( SVLista * p_lisObj )
{
	int iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iRes = p_lisObj->iNumElems;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SVLisMaxElementos ( SVLista * p_lisObj )
{
	int iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iRes = p_lisObj->iMaxElems;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SVLisEstaLlena ( SVLista * p_lisObj )
{
	int iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		if ( p_lisObj->iNumElems == p_lisObj->iMaxElems )
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

int SVLisEstaVacia ( SVLista * p_lisObj )
{
	int iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		if ( p_lisObj->iNumElems == 0 )
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

int SVLisInsertar ( SVLista * p_lisObj, void * p_vValor )
{
	SVLisElem *	p_liselAux;
	SVLisElem *	p_liselObj;
	int			iRes;
	int			iEnc;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		if ( p_lisObj->iNumElems < p_lisObj->iMaxElems )
		{
			p_liselObj = SVLisElCrear ( p_vValor );
			if ( ES_VALIDO ( p_liselObj ) )
			{
				if ( p_lisObj->iNumElems == 0 )
				{
					SVLisContenido ( p_lisObj ) [ 0 ] = p_liselObj;
					p_lisObj->iPrim = 0;
					p_lisObj->iUlt = 0;
					p_lisObj->iLib = 1;
					p_lisObj->iNumElems = 1;
					p_lisObj->iAct = 0;

					iRes = 1;
				}
				else
				{
					if ( p_lisObj->iAct >= 0 )
					{
						p_liselAux = SVLisContenido ( p_lisObj ) [ p_lisObj->iAct ];
						if ( ES_VALIDO ( p_liselAux ) )
						{
							SVLisContenido ( p_lisObj ) [ p_lisObj->iLib ] = p_liselObj;
							p_liselObj->iSig = p_liselAux->iSig;
							p_liselAux->iSig = p_lisObj->iLib;

							p_lisObj->iNumElems = p_lisObj->iNumElems + 1;
							if ( p_lisObj->iUlt == p_lisObj->iAct )
							{
								p_lisObj->iUlt = p_lisObj->iLib;
							}
							p_lisObj->iAct = p_lisObj->iLib;

							iRes = 1;
						}
						else
						{
							MemLiberar ( (void **) &p_liselObj );
							iRes = 0;
						}
					}
					else
					{
						p_liselAux =SVLisContenido ( p_lisObj ) [ p_lisObj->iPrim ];
						if ( ES_VALIDO ( p_liselAux ) )
						{
							SVLisContenido ( p_lisObj ) [ p_lisObj->iLib ] = p_liselObj;

							p_liselObj->iAnt = p_lisObj->iPrim;
							p_liselAux->iAnt = p_lisObj->iLib;

							p_lisObj->iNumElems = p_lisObj->iNumElems + 1;
							p_lisObj->iPrim = p_lisObj->iLib;
							p_lisObj->iAct = p_lisObj->iLib;

							iRes = 1;
						}
						else
						{
							MemLiberar ( (void **) &p_liselObj );
							iRes = 0;
						}
					}

					if ( iRes == 1 )
					{
						if ( p_lisObj->iNumElems == p_lisObj->iMaxElems )
						{
							p_lisObj->iLib = -1;
						}
						else
						{
							iEnc = 0;
							while ( ( iEnc == 0 ) && ( iRes == 1 ) )
							{
								p_lisObj->iLib = p_lisObj->iLib + 1;
								if ( p_lisObj->iLib == p_lisObj->iMaxElems )
								{
									p_lisObj->iLib = 0;
								}
								p_liselAux = SVLisContenido ( p_lisObj ) [ p_lisObj->iLib ];
								if ( ES_NULO ( p_liselAux ) )
								{
									iEnc = 1;
								}
								else
								{
									if ( p_lisObj->iLib == p_lisObj->iAct )
									{
										iRes = 0;
									}
								}
							}
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
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

void SVLisInicio ( SVLista * p_lisObj )
{
	if ( ES_VALIDO ( p_lisObj ) )
	{
		p_lisObj->iAct = p_lisObj->iPrim;
	}
}

void SVLisFinal ( SVLista * p_lisObj )
{
	if ( ES_VALIDO ( p_lisObj ) )
	{
		p_lisObj->iAct = p_lisObj->iUlt;
	}
}

void SVLisSiguiente ( SVLista * p_lisObj )
{
	SVLisElem *	p_liselObj;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		if ( p_lisObj->iAct < 0 )
		{
			p_lisObj->iAct = p_lisObj->iPrim;
		}

		if ( p_lisObj->iAct >= 0 )
		{
			p_liselObj = SVLisContenido ( p_lisObj ) [ p_lisObj->iAct ];
			if ( ES_VALIDO ( p_liselObj ) )
			{
				p_lisObj->iAct = p_liselObj->iSig;
			}
			else
			{
				p_lisObj->iAct = -1;
			}
		}
	}
}

void SVLisAnterior ( SVLista * p_lisObj )
{
	SVLisElem *	p_liselObj;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		if ( p_lisObj->iAct < 0 )
		{
			p_lisObj->iAct = p_lisObj->iUlt;
		}

		if ( p_lisObj->iAct >= 0 )
		{
			p_liselObj = SVLisContenido ( p_lisObj ) [ p_lisObj->iAct ];
			if ( ES_VALIDO ( p_liselObj ) )
			{
				p_lisObj->iAct = p_liselObj->iAnt;
			}
			else
			{
				p_lisObj->iAct = -1;
			}
		}
	}
}

int SVListaEstaEnPrincipio ( SVLista * p_lisObj )
{
	int iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		if ( ( p_lisObj->iAct >= 0 ) && ( p_lisObj->iAct == p_lisObj->iPrim ) )
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

int SVListaEstaEnFinal ( SVLista * p_lisObj )
{
	int iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		if ( ( p_lisObj->iAct >= 0 ) && ( p_lisObj->iAct == p_lisObj->iUlt ) )
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

int SVListaEstaPosicionado ( SVLista * p_lisObj )
{
	int			iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		if ( p_lisObj->iAct >= 0 )
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

void * SVLisElementoActual ( SVLista * p_lisObj )
{
	SVLisElem *   p_liselObj;
	void *  p_vRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		if ( p_lisObj->iAct >= 0 )
		{
			p_liselObj = SVLisContenido ( p_lisObj ) [ p_lisObj->iAct ];
			if ( ES_VALIDO ( p_liselObj ) )
			{
				p_vRes = p_liselObj->p_vValor;
			}
			else
			{
				ERROR_ESTABLECER( ERR_ESTRUCTURA_INVALIDA );
				p_vRes = NULL;
			}
		}
		else
		{
			ERROR_ESTABLECER( ERR_POSICION_INVALIDA );
			p_vRes = NULL;
		}
	}
	else
	{
		p_vRes = NULL;
	}
	return ( p_vRes );
}

SVLisElem * SVLisObtenerElemento ( SVLista * p_lisObj, int iPos, int * p_iIndice )
{
	SVLisElem * p_liselObj;
	int     	iElem;

	if ( ( iPos >= 0 ) && ( iPos < p_lisObj->iNumElems ) )
	{
		iElem = 0;
		p_liselObj = SVLisContenido ( p_lisObj ) [ p_lisObj->iPrim ];
		*p_iIndice = p_lisObj->iPrim;
		while ( ES_VALIDO ( p_liselObj ) && ( iElem < iPos ) && ( p_liselObj->iSig >= 0 ) )
		{
			iElem = iElem + 1;
			*p_iIndice = p_liselObj->iSig;
			p_liselObj = SVLisContenido ( p_lisObj ) [ p_liselObj->iSig ];
		}
		if ( iElem != iPos )
		{
			p_liselObj = NULL;
		}
	}
	else
	{
		p_liselObj = NULL;
	}
	return ( p_liselObj );
}

void * SVLisElemento ( SVLista * p_lisObj, int iPos )
{
	void *  p_vRes;
	int       iIndice;
	SVLisElem *   p_liselObj;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		p_liselObj = SVLisObtenerElemento ( p_lisObj, iPos, &iIndice );
		if ( ES_VALIDO ( p_liselObj ) )
		{
			p_vRes = p_liselObj->p_vValor;
		}
		else
		{
			p_vRes = NULL;
		}
	}
	else
	{
		p_vRes = NULL;
	}
	return ( p_vRes );
}

int SVLisEliminar ( SVLista * p_lisObj, int iPos )
{
	int     		iRes;
	int    		 	iIndice;
	SVLisElem * 	p_liselObj;
	SVLisElem * 	p_liselAnt;
	SVLisElem * 	p_liselPos;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		p_liselObj = SVLisObtenerElemento ( p_lisObj, iPos, &iIndice );
		if ( ES_VALIDO ( p_liselObj ) )
		{
			if ( p_liselObj->iAnt >= 0 )
			{
				p_liselAnt = SVLisContenido ( p_lisObj ) [ p_liselObj->iAnt ];
				p_liselAnt->iSig = p_liselObj->iSig;
			}
			if ( p_liselObj->iSig >= 0 )
			{
				p_liselPos = SVLisContenido ( p_lisObj ) [ p_liselObj->iSig ];
				p_liselPos->iAnt = p_liselObj->iAnt;
			}
			if ( p_lisObj->iAct == iIndice )
			{
				p_lisObj->iAct = p_liselObj->iSig;
			}
			if ( p_lisObj->iPrim == iIndice )
			{
				p_lisObj->iPrim = p_liselObj->iSig;
			}
			if ( p_lisObj->iUlt == iIndice )
			{
				p_lisObj->iUlt = p_liselObj->iAnt;
			}
			if ( p_lisObj->iLiberar == 1 )
			{
				MemLiberar ( (void **) &(p_liselObj->p_vValor) );
			}
			SVLisElDestruir ( &p_liselObj );
			SVLisContenido ( p_lisObj ) [ iIndice ] = NULL;
			p_lisObj->iNumElems = p_lisObj->iNumElems - 1;
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

void SVLisVaciar ( SVLista * p_lisObj )
{
	if ( ES_VALIDO ( p_lisObj ) )
	{
		for ( int iElem = 0; iElem < p_lisObj->iMaxElems; iElem = iElem + 1 )
		{
			SVLisElem * p_liselObj = SVLisContenido( p_lisObj ) [ iElem ];
			if ( ES_VALIDO ( p_liselObj ) )
			{
				if ( p_lisObj->iLiberar == 1 )
				{
					MemLiberar ( (void **) &(p_liselObj->p_vValor) );
				}
				SVLisElDestruir ( &p_liselObj );
			}
			SVLisContenido ( p_lisObj ) [ iElem ] = NULL;
		}
		p_lisObj->iNumElems = 0;
		p_lisObj->iPrim = -1;
		p_lisObj->iUlt = -1;
		p_lisObj->iAct = -1;
	}

}

int	SVLisLiberacionMemoriaActivada ( SVLista * p_lisObj )
{
	int	iRes;

	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		iRes = p_lisObj->iLiberar;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

void SVLisActivarLiberacionMemoria ( SVLista * p_lisObj )
{
	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		p_lisObj->iLiberar = 1;
	}
}

void SVLisDesactivarLiberacionMemoria ( SVLista * p_lisObj )
{
	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		p_lisObj->iLiberar = 0;
	}
}

