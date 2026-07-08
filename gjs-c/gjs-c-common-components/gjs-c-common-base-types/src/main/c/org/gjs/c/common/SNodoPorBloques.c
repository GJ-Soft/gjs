
#include "SNodoPorBloques.h"



#include "TiposBasicosConfig.h"




static void SNodBlqInicializar ( SNodoBlq * p_nodObj, int iTamDatos, SBloque * p_blqDatos, byte * p_byDirDatos, int iLiberar );




SNodoBlq * SNodBlqCrear ( int iTamDatos )
{
	SNodoBlq * p_nodObj;

	if ( iTamDatos > 0 )
	{
		p_nodObj = (SNodoBlq *) MemReservar ( sizeof ( SNodoBlq ) );
		if ( ES_VALIDO ( p_nodObj ) )
		{
			p_nodObj->p_p_p_nodHijos = MemReservar ( ARB_NUM_BLOQUES_HIJOS_NODO * sizeof ( SNodoBlq ** ) );
			SNodBlqInicializar ( p_nodObj, iTamDatos, NULL, NULL, 1 );
		}
	}
	else
	{
		p_nodObj = NULL;
	}
	return ( p_nodObj );
}

SNodoBlq * SNodBlqCrearEntero ()
{
	return ( SNodBlqCrear ( sizeof ( int ) ) );
}

SNodoBlq * SNodBlqCrearEnteroLargo ()
{
	return ( SNodBlqCrear ( sizeof ( long ) ) );
}

SNodoBlq * SNodBlqCrearReal ()
{
	return ( SNodBlqCrear ( sizeof ( float ) ) );
}

SNodoBlq * SNodBlqCrearRealDoble ()
{
	return ( SNodBlqCrear ( sizeof ( double ) ) );
}

SNodoBlq * SNodBlqCrearCadena ()
{
	return ( SNodBlqCrear ( sizeof ( char * ) ) );
}

SNodoBlq * SNodBlqEncapsular ( SBloque * p_blqDatos )
{
	SNodoBlq * p_nodObj;

	if ( ES_VALIDO ( p_blqDatos ) )
	{
		p_nodObj= (SNodoBlq *) MemReservar ( sizeof ( SNodoBlq ) );
		if ( ES_VALIDO ( p_nodObj ) )
		{
			p_nodObj->p_p_p_nodHijos = MemReservar ( ARB_NUM_BLOQUES_HIJOS_NODO * sizeof ( SNodoBlq ** ) );
		    SNodBlqInicializar ( p_nodObj, SBlqTam ( p_blqDatos ), p_blqDatos, NULL, 0 );
		}
	}
	else
	{
		p_nodObj = NULL;
	}
	return ( p_nodObj );
}

SNodoBlq * SNodBlqEncapsularDir ( byte * p_byDirDatos, int iTamDatos, int iLiberar )
{
	SNodoBlq * p_nodObj;

	if ( ES_VALIDO ( p_byDirDatos ) && ( iTamDatos > 0 ) && BOOL_VALIDO ( iLiberar ) )
	{
		p_nodObj= (SNodoBlq *) MemReservar ( sizeof ( SNodoBlq ) );
		if ( ES_VALIDO ( p_nodObj ) )
		{
			p_nodObj->p_p_p_nodHijos = MemReservar ( ARB_NUM_BLOQUES_HIJOS_NODO * sizeof ( SNodoBlq ** ) );
		    SNodBlqInicializar ( p_nodObj, iTamDatos, NULL, p_byDirDatos, iLiberar );
		}
	}
	else
	{
		p_nodObj = NULL;
	}
	return ( p_nodObj );
}

void SNodBlqDestruir ( SNodoBlq ** p_p_nodObj, int iDestruirHijos )
{
	 SNodoBlq *   p_nodObj;

	 if ( ES_VALIDO ( p_p_nodObj ) )
	 {
		p_nodObj = *p_p_nodObj;
		if ( ES_VALIDO ( p_nodObj ) )
		{
			SNodBlqLimpiarHijos ( p_nodObj, iDestruirHijos );
			MemLiberar ( (void **) &(p_nodObj->p_p_p_nodHijos) );
			if ( p_nodObj->iLiberar == 1 )
			{
				SBlqDestruir ( &(p_nodObj->p_blqDatos) );
			}
			MemLiberar ( (void **) p_p_nodObj );
		}
	 }
}

int SNodBlqEsValido ( SNodoBlq * p_nodObj )
{
	int iRes;

	if ( ES_VALIDO ( p_nodObj ) )
	{
		if ( ES_VALIDO ( p_nodObj->p_blqDatos ) )
		{
			if ( SBlqEsValido ( p_nodObj->p_blqDatos ) == 1 )
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

int SNodBlqTieneDatos ( SNodoBlq * p_nodObj )
{
	int iRes;

	if ( SNodBlqEsValido ( p_nodObj ) )
	{
		if ( SBlqTam ( p_nodObj->p_blqDatos ) > 0 )
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

SBloque * SNodBlqDatos ( SNodoBlq * p_nodObj )
{
	SBloque * p_blqRes;

	if ( ES_VALIDO ( p_nodObj ) )
	{
		p_blqRes = p_nodObj->p_blqDatos;
	}
	else
	{
		p_blqRes = NULL;
	}
	return ( p_blqRes );
}

int SNodBlqEntero ( SNodoBlq * p_nodObj )
{
	int	iRes;

	if ( ES_VALIDO ( p_nodObj ) )
	{
		iRes = SBlqEntero ( p_nodObj->p_blqDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

long SNodBlqEnteroLargo ( SNodoBlq * p_nodObj )
{
	long lRes;

	if ( ES_VALIDO ( p_nodObj ) )
	{
		lRes = SBlqEnteroLargo ( p_nodObj->p_blqDatos );
	}
	else
	{
		lRes = 0;
	}
	return ( lRes );
}

float SNodBlqReal ( SNodoBlq * p_nodObj )
{
	float fRes;

	if ( ES_VALIDO ( p_nodObj ) )
	{
		fRes = SBlqReal ( p_nodObj->p_blqDatos );
	}
	else
	{
		fRes = 0;
	}
	return ( fRes );
}

double SNodBlqRealDoble ( SNodoBlq * p_nodObj )
{
	double dRes;

	if ( ES_VALIDO ( p_nodObj ) )
	{
		dRes = SBlqRealDoble ( p_nodObj->p_blqDatos );
	}
	else
	{
		dRes = 0;
	}
	return ( dRes );
}

char * SNodBlqCadena ( SNodoBlq * p_nodObj )
{
	char * p_cRes;

	if ( ES_VALIDO ( p_nodObj ) )
	{
		p_cRes = SBlqCadena ( p_nodObj->p_blqDatos );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

int SNodBlqModificar ( SNodoBlq * p_nodObj, SBloque * p_blqDatos )
{
	int iRes;

	if ( ES_VALIDO ( p_nodObj ) && ES_VALIDO ( p_blqDatos ) )
	{
		if ( p_nodObj->iLiberar == 1 )
		{
			SBlqDestruir ( &(p_nodObj->p_blqDatos) );
		}

		p_nodObj->p_blqDatos = p_blqDatos;
		p_nodObj->iLiberar = SBlqLiberacionMemoriaActivada ( p_blqDatos );
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SNodBlqModificarDir ( SNodoBlq * p_nodObj, byte * p_byDirDatos, int iTamDatos, int iLiberar )
{
	int iRes;

	if ( ES_VALIDO ( p_nodObj ) && ES_VALIDO ( p_byDirDatos ) && ( iTamDatos > 0 ) &&
		 BOOL_VALIDO ( iLiberar ) )
	{
		if ( p_nodObj->iLiberar == 1 )
		{
			SBlqDestruir ( &(p_nodObj->p_blqDatos) );
		}

		p_nodObj->p_blqDatos = SBlqAsignar ( p_byDirDatos, iTamDatos, iLiberar );
		if ( ES_VALIDO ( p_nodObj->p_blqDatos ) )
		{
			iRes = 1;
			p_nodObj->iLiberar = SBlqLiberacionMemoriaActivada ( p_nodObj->p_blqDatos );
		}
		else
		{
			iRes = 0;
			p_nodObj->iLiberar = 0;
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SNodBlqEscribirByte ( SNodoBlq * p_nodObj, int iPos, byte byValor )
{
	int iRes;

	if ( ES_VALIDO ( p_nodObj ) )
	{
		iRes = SBlqEscribirByte ( p_nodObj->p_blqDatos, iPos, byValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SNodBlqEscribirEntero ( SNodoBlq * p_nodObj, int iValor )
{
	int iRes;

	if ( ES_VALIDO ( p_nodObj ) )
	{
		iRes = SBlqEscribirEntero ( p_nodObj->p_blqDatos, iValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SNodBlqEscribirEnteroLargo ( SNodoBlq * p_nodObj, long lValor )
{
	int iRes;

	if ( ES_VALIDO ( p_nodObj ) )
	{
		iRes = SBlqEscribirEnteroLargo ( p_nodObj->p_blqDatos, lValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SNodBlqEscribirReal ( SNodoBlq * p_nodObj, float fValor )
{
	int iRes;

	if ( ES_VALIDO ( p_nodObj ) )
	{
		iRes = SBlqEscribirReal ( p_nodObj->p_blqDatos, fValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SNodBlqEscribirRealDoble ( SNodoBlq * p_nodObj, double dValor )
{
	int iRes;

	if ( ES_VALIDO ( p_nodObj ) )
	{
		iRes = SBlqEscribirRealDoble ( p_nodObj->p_blqDatos, dValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SNodBlqEscribirCadena ( SNodoBlq * p_nodObj, const char * p_cValor )
{
	int iRes;

	if ( ES_VALIDO ( p_nodObj ) )
	{
		iRes = SBlqEscribirCadena ( p_nodObj->p_blqDatos, p_cValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SNodBlqNumHijos ( SNodoBlq * p_nodObj )
{
	int iRes;

	if ( ES_VALIDO ( p_nodObj ) )
	{
		iRes = p_nodObj->iNumHijos;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

SNodoBlq * SNodBlqPadre ( SNodoBlq * p_nodObj )
{
	SNodoBlq * p_nodRes;

	if ( ES_VALIDO ( p_nodObj ) )
	{
		p_nodRes = p_nodObj->p_nodPadre;
	}
	else
	{
		p_nodRes = NULL;
	}
	return ( p_nodRes );
}

SNodoBlq * SNodBlqHijo ( SNodoBlq * p_nodObj, int iHijo )
{
	int		iBloque;
	int		iPos;
	SNodoBlq *	p_nodpHijo;
	SNodoBlq **	p_p_nodBloque;

	if ( ES_VALIDO ( p_nodObj ) )
	{
		if ( ( iHijo >= 0 ) && ( iHijo < p_nodObj->iNumHijos ) )
		{
			iBloque = iHijo / ARB_TAM_BLOQUE_HIJOS_NODO;
			iPos = iHijo % ARB_TAM_BLOQUE_HIJOS_NODO;
			if ( ( iBloque >= 0 ) && ( iBloque < p_nodObj->iNumBloques ) )
			{
				p_p_nodBloque = p_nodObj->p_p_p_nodHijos [ iBloque ];
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

int SNodBlqTienePadre ( SNodoBlq * p_nodObj )
{
	int iRes;

	if ( ES_VALIDO ( p_nodObj ) )
	{
		if ( ES_VALIDO ( p_nodObj->p_nodPadre ) )
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

int SNodBlqTieneHijos ( SNodoBlq * p_nodObj )
{
	int iRes;

	if ( ES_VALIDO ( p_nodObj ) )
	{
		if ( p_nodObj->iNumHijos > 0 )
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

int SNodBlqTieneHermanos ( SNodoBlq * p_nodObj )
{
	int iRes;

	if ( ES_VALIDO ( p_nodObj ) )
	{
		if ( ES_VALIDO ( p_nodObj->p_nodPadre ) )
		{
			if ( SNodBlqNumHijos ( p_nodObj->p_nodPadre ) > 1 )
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

int SNodBlqTieneHermanosIzq ( SNodoBlq * p_nodObj )
{
	int iRes;

	if ( ES_VALIDO ( p_nodObj ) )
	{
		if ( ES_VALIDO ( p_nodObj->p_nodPadre ) )
		{
			if ( SNodoBlqOrdenDelHijo ( p_nodObj->p_nodPadre, p_nodObj ) > 0 )
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

int SNodBlqTieneHermanosDer ( SNodoBlq * p_nodObj )
{
	int iOrden;
	int iRes;

	if ( ES_VALIDO ( p_nodObj ) )
	{
		if ( ES_VALIDO ( p_nodObj->p_nodPadre ) )
		{
			iOrden = SNodoBlqOrdenDelHijo ( p_nodObj->p_nodPadre, p_nodObj );
			if ( ( iOrden >= 0 ) && ( iOrden < SNodBlqNumHijos ( p_nodObj->p_nodPadre ) - 1 ) )
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

int SNodBlqNodosInferiores ( SNodoBlq * p_nodObj )
{
	SNodoBlq *	p_nodpHijo;
	int		iHijo;
	int		iNodos;

	if ( ES_VALIDO ( p_nodObj ) )
	{
		iNodos = 0;
		for ( iHijo = 0; iHijo < p_nodObj->iNumHijos; iHijo = iHijo + 1 )
		{
			p_nodpHijo = SNodBlqHijo ( p_nodObj, iHijo );
			if ( ES_VALIDO ( p_nodpHijo  ) )
			{
				iNodos = iNodos + 1 + SNodBlqNodosInferiores ( p_nodpHijo );
			}
		}
	}
	else
	{
		iNodos = 0;
	}
	return ( iNodos );
}

int SNodBlqNivelesInferiores ( SNodoBlq * p_nodObj )
{
	SNodoBlq *	p_nodpHijo;
	int		iHijo;
	int		iNiveles;
	int		iNivelesMax;

	if ( ES_VALIDO ( p_nodObj ) )
	{
		iNivelesMax = 0;
		for ( iHijo = 0; iHijo < p_nodObj->iNumHijos; iHijo = iHijo + 1 )
		{
			p_nodpHijo = SNodBlqHijo ( p_nodObj, iHijo );
			if ( ES_VALIDO ( p_nodpHijo ) )
			{
				iNiveles = 1 + SNodBlqNivelesInferiores ( p_nodpHijo );
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

int SNodBlqProfundidad ( SNodoBlq * p_nodObj )
{
	int	iProfundidad;

	if ( ES_VALIDO ( p_nodObj ) )
	{
		if ( ES_NULO ( p_nodObj->p_nodPadre ) )
		{
			iProfundidad = 0;
		}
		else
		{
			iProfundidad = SNodBlqProfundidad ( p_nodObj->p_nodPadre ) + 1;
		}
	}
	else
	{
		iProfundidad = 0;
	}
	return ( iProfundidad );
}

int SNodBlqEmpadronar ( SNodoBlq * p_nodObj, SNodoBlq * p_nodPadre )
{
	int iRes;

	if ( ES_VALIDO ( p_nodObj ) )
	{
		p_nodObj->p_nodPadre = p_nodPadre;
		if ( ES_VALIDO ( p_nodObj->p_nodPadre ) )
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

int SNodBlqInsertarHijo ( SNodoBlq * p_nodObj, SNodoBlq * p_nodpHijo )
{
	int			iRes;
	int			iBloque;
	int			iPos;
	SNodoBlq **	p_p_nodBloque;

	if ( ES_VALIDO ( p_nodObj ) )
	{
		if ( ( p_nodObj->iNumHijos < ARB_MAX_HIJOS_NODO ) && ES_VALIDO ( p_nodpHijo ) )
		{
			iBloque = p_nodObj->iNumHijos / ARB_TAM_BLOQUE_HIJOS_NODO;
			iPos = p_nodObj->iNumHijos % ARB_TAM_BLOQUE_HIJOS_NODO;

			iRes = 1;
			if ( ( iPos == 0 ) && ( iBloque > p_nodObj->iNumBloques - 1 ) )
			{
				if ( p_nodObj->iNumBloques < ARB_NUM_BLOQUES_HIJOS_NODO )
				{
					p_nodObj->p_p_p_nodHijos [ p_nodObj->iNumBloques ] = (SNodoBlq **) MemReservar ( ARB_TAM_BLOQUE_HIJOS_NODO * sizeof ( SNodoBlq * ) );
					if ( ES_VALIDO ( p_nodObj->p_p_p_nodHijos [ p_nodObj->iNumBloques ] ) )
					{
						p_nodObj->iNumBloques = p_nodObj->iNumBloques + 1;
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
				p_p_nodBloque = p_nodObj->p_p_p_nodHijos [ iBloque ];
				if ( ES_VALIDO ( p_p_nodBloque ) )
				{
					p_nodObj->iNumHijos = p_nodObj->iNumHijos + 1;
					p_nodpHijo->p_nodPadre = p_nodObj;
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

void SNodBlqDesempadronar ( SNodoBlq * p_nodObj )
{
	if ( ES_VALIDO ( p_nodObj ) )
	{
		p_nodObj->p_nodPadre = NULL;
	}
}

int SNodBlqEliminarHijo ( SNodoBlq * p_nodObj, int iHijo, int iLiberar )
{
	int		   	 	iHijoAux;
	int		   		iRes;
	int		   	 	iBloque;
	int		    	iPos;
	int				iFin;
	SNodoBlq **   	p_p_nodBloque;

	if ( ES_VALIDO ( p_nodObj ) )
	{
		if ( ( iHijo >= 0 ) && ( iHijo < p_nodObj->iNumHijos ) )
		{
			iBloque = iHijo / ARB_TAM_BLOQUE_HIJOS_NODO;
			iPos = iHijo % ARB_TAM_BLOQUE_HIJOS_NODO;
			if ( ( iBloque >= 0 ) && ( iBloque < p_nodObj->iNumBloques ) )
			{
				p_p_nodBloque = p_nodObj->p_p_p_nodHijos [ iBloque ];
				if ( ES_VALIDO ( p_p_nodBloque ) )
				{
					if ( iLiberar == 1 )
					{
						if ( ES_VALIDO ( p_p_nodBloque [ iPos ] ) )
						{
							SNodBlqDestruir ( &(p_p_nodBloque [ iPos ]), 1 );
						}
					}

					iFin = 0;
					while ( ( iBloque < p_nodObj->iNumBloques ) && ( iFin == 0 ) )
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
						if ( ( iBloque < p_nodObj->iNumBloques - 1 ) && ( iFin == 0 ) )
						{
							p_p_nodBloque [ ARB_TAM_BLOQUE_HIJOS_NODO - 1 ] = (p_nodObj->p_p_p_nodHijos [ iBloque + 1 ]) [ 0 ];
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

					p_nodObj->iNumHijos = p_nodObj->iNumHijos - 1;
					p_nodObj->iNumBloques = ( p_nodObj->iNumHijos / ARB_TAM_BLOQUE_HIJOS_NODO ) + 1;
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

int SNodBlqEstablecerHijo ( SNodoBlq * p_nodObj, int iHijo, SNodoBlq * p_nodpHijo, int iLiberar )
{
	int		iRes;
	int		iBloque;
	int		iPos;
	SNodoBlq **	p_p_nodBloque;

	if ( ES_VALIDO ( p_nodObj ) )
	{
		if ( ( iHijo >= 0 ) && ( iHijo < p_nodObj->iNumHijos ) && ES_VALIDO ( p_nodpHijo ) )
		{
			iBloque = iHijo / ARB_TAM_BLOQUE_HIJOS_NODO;
			iPos = iHijo % ARB_TAM_BLOQUE_HIJOS_NODO;
			if ( ( iBloque >= 0 ) && ( iBloque < p_nodObj->iNumBloques ) )
			{
				p_p_nodBloque = p_nodObj->p_p_p_nodHijos [ iBloque ];
				if ( ES_VALIDO ( p_p_nodBloque ) )
				{
    				  if ( iLiberar == 1 )
					  {
							if ( ES_VALIDO ( p_p_nodBloque [ iPos ] ) )
							{
							    SNodBlqDestruir ( &(p_p_nodBloque [ iPos ]), 1 );
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

void SNodBlqLimpiarHijos ( SNodoBlq * p_nodObj, int iLiberar )
{
	int			iHijo;
	int			iBloque;
	SNodoBlq **	p_p_nodBloque;
	SNodoBlq *	p_nodBloque;

    if ( ES_VALIDO ( p_nodObj ) )
    {
		for ( iBloque = 0; iBloque < p_nodObj->iNumBloques; iBloque = iBloque + 1 )
		{
			p_p_nodBloque = p_nodObj->p_p_p_nodHijos [ iBloque ];
			if ( ES_VALIDO ( p_p_nodBloque ) )
			{
				for ( iHijo = 0; iHijo < ARB_TAM_BLOQUE_HIJOS_NODO; iHijo = iHijo + 1 )
				{
					if ( iLiberar == 1 )
					{
						if ( ES_VALIDO ( p_p_nodBloque [ iHijo ] ) )
						{
							p_nodBloque = p_p_nodBloque [ iHijo ];
							SNodBlqDestruir ( &p_nodBloque, 1 );
						}
					}
					p_p_nodBloque [ iHijo ] = NULL;
				}
				MemLiberar ( (void **) &p_p_nodBloque );
			}
		}
    }
}

int	SNodBlqEsHijo ( SNodoBlq * p_nodObj, SNodoBlq * p_nodPosible )
{
	SNodoBlq *	p_nodpHijo;
	int			iHijo;
	int			iEnc;

    if ( ES_VALIDO ( p_nodObj ) && ES_VALIDO ( p_nodPosible ) )
    {
		iEnc = 0;
		iHijo = 0;
		while ( ( iHijo < p_nodObj->iNumHijos ) && ( iEnc == 0 ) )
		{
			p_nodpHijo = SNodBlqHijo ( p_nodObj, iHijo );
			if ( p_nodpHijo == p_nodPosible )
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

int SNodoBlqOrdenDelHijo ( SNodoBlq * p_nodObj, SNodoBlq * p_nodpHijo )
{
	SNodoBlq *  p_nodpHijoAux;
	int			iHijo;
	int			iEnc;

    if ( ES_VALIDO ( p_nodObj ) )
    {
		iEnc = 0;
		iHijo = 0;
		while ( ( iHijo < p_nodObj->iNumHijos ) && ( iEnc == 0 ) )
		{
			p_nodpHijoAux = SNodBlqHijo ( p_nodObj, iHijo );
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

int SNodBlqVerificar ( SNodoBlq * p_nodObj, int iCorregir )
{
	int			iRes;
	SNodoBlq *  p_nodpHijo;
	int			iHijo;

    if ( ES_VALIDO ( p_nodObj ) )
    {
		iRes = 1;
		for ( iHijo = 0; iHijo < p_nodObj->iNumHijos; iHijo = iHijo + 1 )
		{
			p_nodpHijo = SNodBlqHijo ( p_nodObj, iHijo );
			if ( SNodBlqPadre ( p_nodpHijo ) != p_nodObj )
			{
				if ( iCorregir == 1 )
				{
					SNodBlqEmpadronar ( p_nodpHijo, p_nodObj );
				}
				iRes = 0;
			}
			if ( SNodBlqVerificar ( p_nodpHijo, iCorregir ) == 0 )
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

int	SNodBlqLiberacionMemoriaActivada ( SNodoBlq * p_nodObj )
{
	int iRes;

	if ( ES_VALIDO ( p_nodObj ) )
	{
		iRes = p_nodObj->iLiberar;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

// NOTA:Retorna un elemento duplicado pero desencadenado:
SNodoBlq * SNodBlqDuplicar ( SNodoBlq * p_nodObj )
{
	SBloque *	p_blqDatos;
	SNodoBlq * p_nodDup;

	if ( SNodBlqEsValido ( p_nodObj ) == 1 )
	{
		p_blqDatos = p_nodObj->p_blqDatos;
		if ( ES_VALIDO ( p_blqDatos ) )
		{
			p_nodDup = SNodBlqCrear ( SBlqTam ( p_blqDatos ) );
			if ( ES_VALIDO ( p_nodDup ) )
			{
				SBlqCopiar ( p_nodDup->p_blqDatos, p_blqDatos );
				p_nodDup->iLiberar = 1;
			}
		}
		else
		{
			p_nodDup = NULL;
		}
	}
	else
	{
		p_nodDup = NULL;
	}
	return ( p_nodDup );
}

static void SNodBlqInicializar ( SNodoBlq * p_nodObj, int iTamDatos, SBloque * p_blqDatos, byte * p_byDirDatos, int iLiberar )
{
	int iBloque;

	if ( ES_VALIDO ( p_nodObj ) )
	{
		for ( iBloque = 0; iBloque < ARB_NUM_BLOQUES_HIJOS_NODO; iBloque = iBloque + 1 )
		{
			p_nodObj->p_p_p_nodHijos [ iBloque ] = NULL;
		}
		p_nodObj->p_nodPadre = NULL;
		p_nodObj->iNumBloques = 0;
		p_nodObj->iNumHijos = 0;
 		if ( ES_VALIDO ( p_blqDatos ) )
		{
			p_nodObj->p_blqDatos = p_blqDatos;
			p_nodObj->iLiberar = SBlqLiberacionMemoriaActivada ( p_blqDatos );
		}
		else if ( ES_VALIDO ( p_byDirDatos ) )
		{
			p_nodObj->p_blqDatos = SBlqAsignar ( p_byDirDatos, iTamDatos, iLiberar );
			if ( ES_VALIDO ( p_nodObj->p_blqDatos ) )
			{
				p_nodObj->iLiberar = SBlqLiberacionMemoriaActivada ( p_nodObj->p_blqDatos );
			}
			else
			{
				p_nodObj->iLiberar = 0;
			}
		}
		else
		{
			p_nodObj->p_blqDatos = SBlqCrear ( iTamDatos );
			if ( ES_VALIDO ( p_nodObj->p_blqDatos ) )
			{
				p_nodObj->iLiberar = 1;
			}
			else
			{
				p_nodObj->iLiberar = 0;
			}
		}
    }
}



