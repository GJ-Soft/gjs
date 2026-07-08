
#include "SNodoPorBloquesPtr.h"



#include "TiposBasicosConfig.h"




static void SNodBlqPtrInicializar ( SNodoBlqPtr * p_nodpObj, byte * p_byDirDatos, int iLiberar );



SNodoBlqPtr * SNodBlqPtrCrearMem ( int iTamDatos )
{
	SNodoBlqPtr * p_nodpObj;

	if ( iTamDatos > 0 )
	{
		p_nodpObj = SNodBlqPtrCrear( (byte *) MemReservar ( iTamDatos ), 1 );
	}
	else
	{
		p_nodpObj = NULL;
	}
	return ( p_nodpObj );
}


SNodoBlqPtr * SNodBlqPtrCrear ( byte * p_byDatos, int iLiberar )
{
	SNodoBlqPtr * p_nodpObj;

	if ( ES_VALIDO ( p_byDatos ) )
	{
		p_nodpObj= (SNodoBlqPtr *) MemReservar ( sizeof ( SNodoBlqPtr ) );
		if ( ES_VALIDO ( p_nodpObj ) )
		{
			p_nodpObj->p_p_p_nodpHijos = MemReservar ( ARB_NUM_BLOQUES_HIJOS_NODO * sizeof ( SNodoBlqPtr ** ) );
		    SNodBlqPtrInicializar ( p_nodpObj, p_byDatos, iLiberar );
		}
	}
	else
	{
		p_nodpObj = NULL;
	}
	return ( p_nodpObj );
}

void SNodBlqPtrDestruir ( SNodoBlqPtr ** p_p_nodpObj, int iDestruirHijos )
{
	 SNodoBlqPtr *   p_nodpObj;

	 if ( ES_VALIDO ( p_p_nodpObj ) )
	 {
		p_nodpObj = *p_p_nodpObj;
		if ( ES_VALIDO ( p_nodpObj ) )
		{
			SNodBlqPtrLimpiarHijos ( p_nodpObj, iDestruirHijos );
			MemLiberar ( (void **) &(p_nodpObj->p_p_p_nodpHijos) );
			if ( p_nodpObj->iLiberar == 1 )
			{
				MemLiberar ( (void **) &(p_nodpObj->p_byDatos) );
			}
			MemLiberar ( (void **) p_p_nodpObj );
		}
	 }
}

int SNodBlqPtrEsValido ( SNodoBlqPtr * p_nodpObj )
{
	int iRes;

	if ( ES_VALIDO ( p_nodpObj ) )
	{
		if ( ES_VALIDO ( p_nodpObj->p_byDatos ) == 1 )
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

int SNodBlqPtrTieneDatos ( SNodoBlqPtr * p_nodpObj )
{
	int iRes;

	if ( SNodBlqPtrEsValido ( p_nodpObj ) )
	{
		if ( ES_VALIDO ( p_nodpObj->p_byDatos ) )
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

byte * SNodBlqPtrDatos ( SNodoBlqPtr * p_nodpObj )
{
	byte * p_byRes;

	if ( ES_VALIDO ( p_nodpObj ) )
	{
		p_byRes = p_nodpObj->p_byDatos;
	}
	else
	{
		p_byRes = NULL;
	}
	return ( p_byRes );
}

int SNodBlqPtrModificar ( SNodoBlqPtr * p_nodpObj, byte * p_byDatos, int iLiberar )
{
	int iRes;

	if ( ES_VALIDO ( p_nodpObj ) && ES_VALIDO ( p_byDatos ) && BOOL_VALIDO ( iLiberar ) )
	{
		if ( p_nodpObj->iLiberar == 1 )
		{
			MemLiberar ( (void **) &(p_nodpObj->p_byDatos) );
		}

		p_nodpObj->p_byDatos = p_byDatos;
		if ( ES_VALIDO ( p_nodpObj->p_byDatos ) )
		{
			iRes = 1;
			p_nodpObj->iLiberar = iLiberar;
		}
		else
		{
			iRes = 0;
			p_nodpObj->iLiberar = 0;
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SNodBlqPtrNumHijos ( SNodoBlqPtr * p_nodpObj )
{
     int iRes;

     if ( ES_VALIDO ( p_nodpObj ) )
     {
          iRes = p_nodpObj->iNumHijos;
     }
     else
     {
          iRes = 0;
     }
	return ( iRes );
}

SNodoBlqPtr * SNodBlqPtrPadre ( SNodoBlqPtr * p_nodpObj )
{
     SNodoBlqPtr * p_nodRes;

     if ( ES_VALIDO ( p_nodpObj ) )
     {
          p_nodRes = p_nodpObj->p_nodpPadre;
     }
     else
     {
          p_nodRes = NULL;
     }
	return ( p_nodRes );
}

SNodoBlqPtr * SNodBlqPtrHijo ( SNodoBlqPtr * p_nodpObj, int iHijo )
{
	int		iBloque;
	int		iPos;
	SNodoBlqPtr *	p_nodpHijo;
	SNodoBlqPtr **	p_p_nodBloque;

     if ( ES_VALIDO ( p_nodpObj ) )
     {
     	if ( ( iHijo >= 0 ) && ( iHijo < p_nodpObj->iNumHijos ) )
     	{
     		iBloque = iHijo / ARB_TAM_BLOQUE_HIJOS_NODO;
     		iPos = iHijo % ARB_TAM_BLOQUE_HIJOS_NODO;
     		if ( ( iBloque >= 0 ) && ( iBloque < p_nodpObj->iNumBloques ) )
     		{
     			p_p_nodBloque = p_nodpObj->p_p_p_nodpHijos [ iBloque ];
     			if ( ES_VALIDO ( p_p_nodBloque ) )
     			{
     				p_nodpHijo = p_p_nodBloque [ iPos ];
     			}
     			else
     			{
     				p_nodpHijo = NULL;
     			}
     		}
     		else
     		{
     			p_nodpHijo = NULL;
     		}
     	}
     	else
     	{
     		p_nodpHijo = NULL;
     	}
	}
	else
	{
		p_nodpHijo = NULL;
	}
	return ( p_nodpHijo );
}

int SNodBlqPtrTienePadre ( SNodoBlqPtr * p_nodpObj )
{
	int iRes;

     if ( ES_VALIDO ( p_nodpObj ) )
     {
     	if ( ES_VALIDO ( p_nodpObj->p_nodpPadre ) )
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

int SNodBlqPtrTieneHijos ( SNodoBlqPtr * p_nodpObj )
{
	int iRes;

     if ( ES_VALIDO ( p_nodpObj ) )
     {
     	if ( p_nodpObj->iNumHijos > 0 )
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

int SNodBlqPtrTieneHermanos ( SNodoBlqPtr * p_nodpObj )
{
	int iRes;

     if ( ES_VALIDO ( p_nodpObj ) )
     {
     	if ( ES_VALIDO ( p_nodpObj->p_nodpPadre ) )
     	{
     		if ( SNodBlqPtrNumHijos ( p_nodpObj->p_nodpPadre ) > 1 )
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

int SNodBlqPtrTieneHermanosIzq ( SNodoBlqPtr * p_nodpObj )
{
	int iRes;

     if ( ES_VALIDO ( p_nodpObj ) )
     {
     	if ( ES_VALIDO ( p_nodpObj->p_nodpPadre ) )
     	{
     		if ( SNodBlqPtrOrdenDelHijo ( p_nodpObj->p_nodpPadre, p_nodpObj ) > 0 )
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

int SNodBlqPtrTieneHermanosDer ( SNodoBlqPtr * p_nodpObj )
{
	int iOrden;
	int iRes;

     if ( ES_VALIDO ( p_nodpObj ) )
     {
     	if ( ES_VALIDO ( p_nodpObj->p_nodpPadre ) )
     	{
     		iOrden = SNodBlqPtrOrdenDelHijo ( p_nodpObj->p_nodpPadre, p_nodpObj );
     		if ( ( iOrden >= 0 ) && ( iOrden < SNodBlqPtrNumHijos ( p_nodpObj->p_nodpPadre ) - 1 ) )
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

int SNodBlqPtrNodosInferiores ( SNodoBlqPtr * p_nodpObj )
{
	SNodoBlqPtr *	p_nodpHijo;
	int		iHijo;
	int		iNodos;

     if ( ES_VALIDO ( p_nodpObj ) )
     {
     	iNodos = 0;
     	for ( iHijo = 0; iHijo < p_nodpObj->iNumHijos; iHijo = iHijo + 1 )
     	{
     		p_nodpHijo = SNodBlqPtrHijo ( p_nodpObj, iHijo );
     		if ( ES_VALIDO ( p_nodpHijo  ) )
     		{
     			iNodos = iNodos + 1 + SNodBlqPtrNodosInferiores ( p_nodpHijo );
     		}
     	}
     }
     else
     {
          iNodos = 0;
     }
	return ( iNodos );
}

int SNodBlqPtrNivelesInferiores ( SNodoBlqPtr * p_nodpObj )
{
	SNodoBlqPtr *	p_nodpHijo;
	int		iHijo;
	int		iNiveles;
	int		iNivelesMax;

     if ( ES_VALIDO ( p_nodpObj ) )
     {
     	iNivelesMax = 0;
     	for ( iHijo = 0; iHijo < p_nodpObj->iNumHijos; iHijo = iHijo + 1 )
     	{
     		p_nodpHijo = SNodBlqPtrHijo ( p_nodpObj, iHijo );
     		if ( ES_VALIDO ( p_nodpHijo ) )
     		{
     			iNiveles = 1 + SNodBlqPtrNivelesInferiores ( p_nodpHijo );
     			if ( iNiveles > iNivelesMax )
     			{
     				iNivelesMax = iNiveles;
     			}
     		}
     	}
     }
     else
     {
          iNivelesMax = 0;
     }
	return ( iNivelesMax );
}

int SNodBlqPtrProfundidad ( SNodoBlqPtr * p_nodpObj )
{
	int	iProfundidad;

     if ( ES_VALIDO ( p_nodpObj ) )
     {
     	if ( ES_NULO ( p_nodpObj->p_nodpPadre ) )
     	{
     		iProfundidad = 0;
     	}
     	else
     	{
     		iProfundidad = SNodBlqPtrProfundidad ( p_nodpObj->p_nodpPadre ) + 1;
     	}
     }
     else
     {
          iProfundidad = 0;
     }
	return ( iProfundidad );
}

int SNodBlqPtrEmpadronar ( SNodoBlqPtr * p_nodpObj, SNodoBlqPtr * p_nodpPadre )
{
	int iRes;

     if ( ES_VALIDO ( p_nodpObj ) )
     {
     	p_nodpObj->p_nodpPadre = p_nodpPadre;
     	if ( ES_VALIDO ( p_nodpObj->p_nodpPadre ) )
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

int SNodBlqPtrInsertarHijo ( SNodoBlqPtr * p_nodpObj, SNodoBlqPtr * p_nodpHijo )
{
	int	     		iRes;
	int	     		iBloque;
	int				iPos;
	SNodoBlqPtr **	p_p_nodBloque;

     if ( ES_VALIDO ( p_nodpObj ) )
     {
     	if ( ( p_nodpObj->iNumHijos < ARB_MAX_HIJOS_NODO ) && ES_VALIDO ( p_nodpHijo ) )
     	{
     		iBloque = p_nodpObj->iNumHijos / ARB_TAM_BLOQUE_HIJOS_NODO;
     		iPos = p_nodpObj->iNumHijos % ARB_TAM_BLOQUE_HIJOS_NODO;

     		iRes = 1;
     		if ( ( iPos == 0 ) && ( iBloque > p_nodpObj->iNumBloques - 1 ) )
     		{
     			if ( p_nodpObj->iNumBloques < ARB_NUM_BLOQUES_HIJOS_NODO )
     			{
     				p_nodpObj->p_p_p_nodpHijos [ p_nodpObj->iNumBloques ] = (SNodoBlqPtr **) MemReservar ( ARB_TAM_BLOQUE_HIJOS_NODO * sizeof ( SNodoBlqPtr * ) );
     				if ( ES_VALIDO ( p_nodpObj->p_p_p_nodpHijos [ p_nodpObj->iNumBloques ] ) )
     				{
     					p_nodpObj->iNumBloques = p_nodpObj->iNumBloques + 1;
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

     		if ( iRes == 1 )
     		{
     			p_p_nodBloque = p_nodpObj->p_p_p_nodpHijos [ iBloque ];
     			if ( ES_VALIDO ( p_p_nodBloque ) )
     			{
     				p_nodpObj->iNumHijos = p_nodpObj->iNumHijos + 1;
					p_nodpHijo->p_nodpPadre = p_nodpObj;
    				p_p_nodBloque [ iPos ] = p_nodpHijo;
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

void SNodBlqPtrDesempadronar ( SNodoBlqPtr * p_nodpObj )
{
     if ( ES_VALIDO ( p_nodpObj ) )
     {
          p_nodpObj->p_nodpPadre = NULL;
     }
}

int SNodBlqPtrEliminarHijo ( SNodoBlqPtr * p_nodpObj, int iHijo, int iLiberar )
{
	int		    	iHijoAux;
	int		    	iRes;
	int		    	iBloque;
	int		    	iPos;
	int				iFin;
	SNodoBlqPtr **  p_p_nodBloque;

     if ( ES_VALIDO ( p_nodpObj ) )
     {
     	if ( ( iHijo >= 0 ) && ( iHijo < p_nodpObj->iNumHijos ) )
     	{
     		iBloque = iHijo / ARB_TAM_BLOQUE_HIJOS_NODO;
     		iPos = iHijo % ARB_TAM_BLOQUE_HIJOS_NODO;
     		if ( ( iBloque >= 0 ) && ( iBloque < p_nodpObj->iNumBloques ) )
     		{
     			p_p_nodBloque = p_nodpObj->p_p_p_nodpHijos [ iBloque ];
     			if ( ES_VALIDO ( p_p_nodBloque ) )
     			{
     				if ( iLiberar == 1 )
     				{
     					if ( ES_VALIDO ( p_p_nodBloque [ iPos ] ) )
     					{
     						SNodBlqPtrDestruir ( &(p_p_nodBloque [ iPos ]), 1 );
     					}
     				}

					iFin = 0;
     				while ( ( iBloque < p_nodpObj->iNumBloques ) && ( iFin == 0 ) )
     				{
						iHijoAux = iPos + 1;
						while ( ( iHijoAux < ARB_TAM_BLOQUE_HIJOS_NODO ) && ( iFin == 0 ) )
						{
							p_p_nodBloque [ iHijoAux - 1 ] = p_p_nodBloque [ iHijoAux ];
							if ( ES_NULO ( p_p_nodBloque [ iHijoAux ] ) )
							{
								iFin = 1;
							}
							iHijoAux = iHijoAux + 1;
    					}
						if ( ( iBloque < p_nodpObj->iNumBloques - 1 ) && ( iFin == 0 ) )
     					{
     						p_p_nodBloque [ ARB_TAM_BLOQUE_HIJOS_NODO - 1 ] = (p_nodpObj->p_p_p_nodpHijos [ iBloque + 1 ]) [ 0 ];
 							if ( ES_NULO ( p_p_nodBloque [ ARB_TAM_BLOQUE_HIJOS_NODO - 1 ] ) )
							{
								iFin = 1;
							}
    					}
     					else
     					{
     						p_p_nodBloque [ ARB_TAM_BLOQUE_HIJOS_NODO - 1 ] = NULL;
     					}
						iBloque = iBloque + 1;
						iPos = 0;
     	     		}

     				p_nodpObj->iNumHijos = p_nodpObj->iNumHijos - 1;
 					p_nodpObj->iNumBloques = ( p_nodpObj->iNumHijos / ARB_TAM_BLOQUE_HIJOS_NODO ) + 1;
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
     }
     else
     {
          iRes = 0;
     }
	return ( iRes );
}

int SNodBlqPtrEstablecerHijo ( SNodoBlqPtr * p_nodpObj, int iHijo, SNodoBlqPtr * p_nodpHijo, int iLiberar )
{
	int		iRes;
	int		iBloque;
	int		iPos;
	SNodoBlqPtr **	p_p_nodBloque;

     if ( ES_VALIDO ( p_nodpObj ) )
     {
     	if ( ( iHijo >= 0 ) && ( iHijo < p_nodpObj->iNumHijos ) && ES_VALIDO ( p_nodpHijo ) )
     	{
     		iBloque = iHijo / ARB_TAM_BLOQUE_HIJOS_NODO;
     		iPos = iHijo % ARB_TAM_BLOQUE_HIJOS_NODO;
     		if ( ( iBloque >= 0 ) && ( iBloque < p_nodpObj->iNumBloques ) )
     		{
     			p_p_nodBloque = p_nodpObj->p_p_p_nodpHijos [ iBloque ];
     			if ( ES_VALIDO ( p_p_nodBloque ) )
                    {
    				       if ( iLiberar == 1 )
     				  {
     					     if ( ES_VALIDO ( p_p_nodBloque [ iPos ] ) )
     					     {
     						    SNodBlqPtrDestruir ( &(p_p_nodBloque [ iPos ]), 1 );
     					     }
     				  }
   				       p_p_nodBloque [ iPos ] = p_nodpHijo;
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
     }
     else
     {
          iRes = 0;
     }
	return ( iRes );
}

void SNodBlqPtrLimpiarHijos ( SNodoBlqPtr * p_nodpObj, int iLiberar )
{
	int				iHijo;
	int				iBloque;
	SNodoBlqPtr **	p_p_nodBloque;

     if ( ES_VALIDO ( p_nodpObj ) )
     {
     	for ( iBloque = 0; iBloque < p_nodpObj->iNumBloques; iBloque = iBloque + 1 )
     	{
     		p_p_nodBloque = p_nodpObj->p_p_p_nodpHijos [ iBloque ];
     		if ( ES_VALIDO ( p_p_nodBloque ) )
     		{
     			for ( iHijo = 0; iHijo < ARB_TAM_BLOQUE_HIJOS_NODO; iHijo = iHijo + 1 )
     			{
     				if ( iLiberar == 1 )
     				{
     					if ( ES_VALIDO ( p_p_nodBloque [ iHijo ] ) )
     					{
     						SNodBlqPtrDestruir ( &(p_p_nodBloque [ iHijo ]), 1 );
     					}
     				}
     				p_p_nodBloque [ iHijo ] = NULL;
     			}
     			MemLiberar ( (void **) &p_p_nodBloque );
     		}
     	}
     }
 }

int	SNodBlqPtrEsHijo ( SNodoBlqPtr * p_nodpObj, SNodoBlqPtr * p_nodpPosible )
{
	SNodoBlqPtr *	p_nodpHijo;
	int				iHijo;
	int				iEnc;

    if ( ES_VALIDO ( p_nodpObj ) && ES_VALIDO ( p_nodpPosible ) )
    {
     	iEnc = 0;
     	iHijo = 0;
     	while ( ( iHijo < p_nodpObj->iNumHijos ) && ( iEnc == 0 ) )
     	{
     		p_nodpHijo = SNodBlqPtrHijo ( p_nodpObj, iHijo );
     		if ( p_nodpHijo == p_nodpPosible )
     		{
     			iEnc = 1;
     		}
     		else
     		{
     			iHijo = iHijo + 1;
     		}
     	}
    }
    else
    {
        iEnc = 0;
    }
	return ( iEnc );
}

int SNodBlqPtrOrdenDelHijo ( SNodoBlqPtr * p_nodpObj, SNodoBlqPtr *	p_nodpHijo )
{
	SNodoBlqPtr *	p_nodpHijoAux;
	int				iHijo;
	int				iEnc;

    if ( ES_VALIDO ( p_nodpObj ) )
    {
     	iEnc = 0;
     	iHijo = 0;
     	while ( ( iHijo < p_nodpObj->iNumHijos ) && ( iEnc == 0 ) )
     	{
     		p_nodpHijoAux = SNodBlqPtrHijo ( p_nodpObj, iHijo );
     		if ( p_nodpHijoAux == p_nodpHijo )
     		{
     			iEnc = 1;
     		}
     		else
     		{
     			iHijo = iHijo + 1;
     		}
     	}

     	if ( iEnc == 0 )
     	{
     		iHijo = -1;
     	}
    }
    else
    {
        iHijo = -1;
    }
	return ( iHijo );
}

int SNodBlqPtrVerificar ( SNodoBlqPtr * p_nodpObj, int iCorregir )
{
	int				iRes;
	SNodoBlqPtr *	p_nodpHijo;
	int				iHijo;

    if ( ES_VALIDO ( p_nodpObj ) )
    {
     	iRes = 1;
     	for ( iHijo = 0; iHijo < p_nodpObj->iNumHijos; iHijo = iHijo + 1 )
     	{
     		p_nodpHijo = SNodBlqPtrHijo ( p_nodpObj, iHijo );
     		if ( SNodBlqPtrPadre ( p_nodpHijo ) != p_nodpObj )
     		{
     			if ( iCorregir == 1 )
     			{
     				SNodBlqPtrEmpadronar ( p_nodpHijo, p_nodpObj );
     			}
     			iRes = 0;
     		}
     		if ( SNodBlqPtrVerificar ( p_nodpHijo, iCorregir ) == 0 )
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

int	SNodBlqPtrLiberacionMemoriaActivada ( SNodoBlqPtr * p_nodpObj )
{
	int iRes;

	if ( ES_VALIDO ( p_nodpObj ) )
	{
		iRes = p_nodpObj->iLiberar;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

static void SNodBlqPtrInicializar ( SNodoBlqPtr * p_nodpObj, byte * p_byDirDatos, int iLiberar )
{
	int iBloque;

     if ( ES_VALIDO ( p_nodpObj ) )
     {
     	for ( iBloque = 0; iBloque < ARB_NUM_BLOQUES_HIJOS_NODO; iBloque = iBloque + 1 )
     	{
     		p_nodpObj->p_p_p_nodpHijos [ iBloque ] = NULL;
     	}
     	p_nodpObj->p_nodpPadre = NULL;
     	p_nodpObj->iNumBloques = 0;
     	p_nodpObj->iNumHijos = 0;
		p_nodpObj->p_byDatos = p_byDirDatos;
		if ( ES_VALIDO ( p_nodpObj->p_byDatos ) )
		{
			p_nodpObj->iLiberar = iLiberar;
		}
		else
		{
			p_nodpObj->iLiberar = 0;
		}
    }
}



