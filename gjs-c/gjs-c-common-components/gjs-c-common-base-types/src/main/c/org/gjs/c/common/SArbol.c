#include "SArbol.h"




#include "TiposBasicosConfig.h"



SArbol * SArbCrear () 
{
	SArbol * p_arbObj;
	
	p_arbObj = (SArbol *) MemReservar ( sizeof ( SArbol ) );
	if ( ES_VALIDO ( p_arbObj ) )
	{
		p_arbObj->p_nodRaiz = NULL;
		p_arbObj->p_nodActual = NULL;
	}
	return ( p_arbObj );
}

void SArbDestruir ( SArbol ** p_p_arbObj )
{
	SArbol * p_arbObj;
	
	if ( ES_VALIDO ( p_p_arbObj ) )
	{
		p_arbObj = *p_p_arbObj;
		if ( ES_VALIDO ( p_arbObj ) )
		{
			SArbVaciar ( p_arbObj );
			MemLiberar ( (void **) p_p_arbObj );
		}
	}
}

SNodo * SArbRaiz ( SArbol * p_arbObj )
{
	SNodo * p_nodRes;
	
	if ( ES_VALIDO ( p_arbObj ) )
	{
		p_nodRes = p_arbObj->p_nodRaiz;
	}
	else
	{
		p_nodRes = NULL;
	}
	return ( p_nodRes );
}

int SArbEstablecerRaiz ( SArbol * p_arbObj, SNodo * p_nodObj )
{
	int iRes;

	if ( ES_VALIDO ( p_arbObj ) )
	{
		p_arbObj->p_nodRaiz = p_nodObj;
		if ( ES_VALIDO ( p_arbObj->p_nodRaiz ) )
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

int SArbEstaVacio ( SArbol * p_arbObj )
{
	int iRes;

	if ( ES_VALIDO ( p_arbObj ) )
	{
		if ( ES_NULO ( p_arbObj->p_nodRaiz ) )
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

int SArbNiveles ( SArbol * p_arbObj )
{
	int iNiveles;

	if ( ES_VALIDO ( p_arbObj ) )
	{
		if ( ES_VALIDO ( p_arbObj->p_nodRaiz ) )
		{
			iNiveles = SNodNivelesInferiores ( p_arbObj->p_nodRaiz ) + 1;
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

int SArbNumNodos ( SArbol * p_arbObj )
{
	int iNodos;

	if ( ES_VALIDO ( p_arbObj ) )
	{
		if ( ES_VALIDO ( p_arbObj->p_nodRaiz ) )
		{
			iNodos = SNodNodosInferiores ( p_arbObj->p_nodRaiz ) + 1;
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

int SArbVaciar ( SArbol * p_arbObj )
{
	int		iRes;

	if ( ES_VALIDO ( p_arbObj ) )
	{
		if ( ES_VALIDO ( p_arbObj->p_nodRaiz ) )
		{
			SNodDestruir ( &(p_arbObj->p_nodRaiz), 1 );
			p_arbObj->p_nodActual = NULL;
			if ( SArbNumNodos ( p_arbObj ) == 0 )
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
		iRes = 1;
	}
	return ( iRes );
}

SNodo * SArbActual ( SArbol * p_arbObj )
{
	SNodo * p_nodRes;
	
	if ( ES_VALIDO ( p_arbObj ) )
	{
		p_nodRes = p_arbObj->p_nodActual;
	}
	else
	{
		p_nodRes = NULL;
	}
	return ( p_nodRes );
}

int SArbMoverARaiz ( SArbol * p_arbObj )
{
	int iRes;
	
	if ( ES_VALIDO ( p_arbObj ) )
	{
		p_arbObj->p_nodActual = p_arbObj->p_nodRaiz;
		if ( ES_VALIDO ( p_arbObj->p_nodActual ) )
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

int SArbMoverAPadre ( SArbol * p_arbObj )
{
	int iRes;
	
	if ( ES_VALIDO ( p_arbObj ) )
	{
		if ( ES_VALIDO ( p_arbObj->p_nodActual ) )
		{
			p_arbObj->p_nodActual = SNodPadre ( p_arbObj->p_nodActual );
			if ( ES_VALIDO ( p_arbObj->p_nodActual ) )
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

int SArbMoverAHijo ( SArbol * p_arbObj, int iHijo )
{
	int iRes;
	
	if ( ES_VALIDO ( p_arbObj ) )
	{
		if ( ES_VALIDO ( p_arbObj->p_nodActual ) )
		{
			p_arbObj->p_nodActual = SNodHijo ( p_arbObj->p_nodActual, iHijo );
			if ( ES_VALIDO ( p_arbObj->p_nodActual ) )
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

int SArbMoverAPrimHijo ( SArbol * p_arbObj )
{
	int iRes;
	
	if ( ES_VALIDO ( p_arbObj ) )
	{
		iRes = SArbMoverAHijo ( p_arbObj, 0 );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SArbMoverAUltHijo ( SArbol * p_arbObj )
{
	int iRes;
	
	if ( ES_VALIDO ( p_arbObj ) )
	{
		if ( ES_VALIDO ( p_arbObj->p_nodActual ) )
		{
			iRes = SArbMoverAHijo ( p_arbObj, SNodNumHijos ( p_arbObj->p_nodActual ) - 1 );
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

int SArbMoverAPrimHermano ( SArbol * p_arbObj )
{
	int 	iRes;
	SNodo * p_nodPadre;
	
	if ( ES_VALIDO ( p_arbObj ) )
	{
		if ( ES_VALIDO ( p_arbObj->p_nodActual ) )
		{
			p_nodPadre = SNodPadre ( p_arbObj->p_nodActual );
			if ( ES_VALIDO ( p_nodPadre ) )
			{
				p_arbObj->p_nodActual = SNodHijo ( p_nodPadre, 0 );
				if ( ES_VALIDO ( p_arbObj->p_nodActual ) )
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
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SArbMoverASigHermano ( SArbol * p_arbObj )
{
	int 	iRes;
	int		iHijo;
	SNodo * p_nodPadre;

	if ( ES_VALIDO ( p_arbObj ) )
	{
		if ( ES_VALIDO ( p_arbObj->p_nodActual ) )
		{
			if ( SNodTienePadre ( p_arbObj->p_nodActual ) == 1 )
			{
				p_nodPadre = SNodPadre ( p_arbObj->p_nodActual );
				iHijo = SNodOrdenDelHijo ( p_nodPadre, p_arbObj->p_nodActual );
				if ( iHijo >= 0 )
				{
					p_arbObj->p_nodActual = SNodHijo ( p_nodPadre, iHijo + 1 );
					if ( ES_VALIDO ( p_arbObj->p_nodActual ) )
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

int SArbMoverAAntHermano ( SArbol * p_arbObj )
{
	int 	iRes;
	int		iHijo;
	SNodo * p_nodPadre;

	if ( ES_VALIDO ( p_arbObj ) )
	{
		if ( ES_VALIDO ( p_arbObj->p_nodActual ) )
		{
			if ( SNodTienePadre ( p_arbObj->p_nodActual ) == 1 )
			{
				p_nodPadre = SNodPadre ( p_arbObj->p_nodActual );
				iHijo = SNodOrdenDelHijo ( p_nodPadre, p_arbObj->p_nodActual );
				if ( iHijo > 0 )
				{
					p_arbObj->p_nodActual = SNodHijo ( p_nodPadre, iHijo - 1 );
					if ( ES_VALIDO ( p_arbObj->p_nodActual ) )
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

int SArbMoverAUltHermano ( SArbol * p_arbObj )
{
	int		iRes;
	SNodo * p_nodPadre;
	
	if ( ES_VALIDO ( p_arbObj ) )
	{
		p_nodPadre = SNodPadre ( p_arbObj->p_nodActual );
		if ( ES_VALIDO ( p_nodPadre ) )
		{
			p_arbObj->p_nodActual = SNodHijo ( p_nodPadre, SNodNumHijos ( p_nodPadre ) - 1 );
			if ( ES_VALIDO ( p_arbObj->p_nodActual ) )
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

int SArbMoverAPrimPreorden ( SArbol * p_arbObj )
{
	int iRes;
	
	if ( ES_VALIDO ( p_arbObj ) )
	{
		iRes = SArbMoverARaiz ( p_arbObj );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SArbMoverASigPreorden ( SArbol * p_arbObj )
{
	int 	iRes;
	
	if ( ES_VALIDO ( p_arbObj ) )
	{
		if ( ES_VALIDO ( p_arbObj->p_nodActual ) )
		{
			if ( SNodTieneHijos ( p_arbObj->p_nodActual ) == 1 )
			{
				iRes = SArbMoverAHijo ( p_arbObj, 0 );
			}
			else if ( SNodTieneHermanosDer ( p_arbObj->p_nodActual ) == 1 )
			{
				iRes = SArbMoverASigHermano ( p_arbObj );
			} 
			else 
			{
				iRes = 1;
				while ( ( iRes == 1 ) && ( SNodTieneHermanosDer ( p_arbObj->p_nodActual ) == 0 ) )
				{
					iRes = SArbMoverAPadre ( p_arbObj );
				}
				if ( iRes == 1 )
				{
					iRes = SArbMoverASigHermano ( p_arbObj );
				}
				else
				{
					p_arbObj->p_nodActual = NULL;
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

int SArbMoverAPrimPostorden ( SArbol * p_arbObj )
{
	int 	iRes;

	if ( ES_VALIDO ( p_arbObj ) )
	{
		iRes = SArbMoverARaiz ( p_arbObj );
		while ( ES_VALIDO ( p_arbObj->p_nodActual ) && ( SNodTieneHijos ( p_arbObj->p_nodActual ) == 1 ) )
		{
			SArbMoverAHijo ( p_arbObj, 0 );
		}
		if ( ES_VALIDO ( p_arbObj->p_nodActual ) )
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

int SArbMoverASigPostorden ( SArbol * p_arbObj )
{
	int 	iRes;

	if ( ES_VALIDO ( p_arbObj ) )
	{
		if ( ES_VALIDO ( p_arbObj->p_nodActual ) )
		{
			if ( SNodTieneHermanosDer ( p_arbObj->p_nodActual ) == 1 )
			{
				iRes = SArbMoverASigHermano ( p_arbObj );
				while ( ( iRes == 1 ) && ( SNodTieneHijos ( p_arbObj->p_nodActual ) == 1 ) )
				{
					iRes = SArbMoverAHijo ( p_arbObj, 0 );
				}
			}
			else if ( SNodTienePadre ( p_arbObj->p_nodActual ) == 1 )
			{
				iRes = SArbMoverAPadre ( p_arbObj );
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

void SArbDesposicionar ( SArbol * p_arbObj )
{
	if ( ES_VALIDO ( p_arbObj ) )
	{
		p_arbObj->p_nodActual = NULL;
	}
}

int	SArbEstaPosicionado ( SArbol * p_arbObj )
{
	int iRes;

	if ( ES_VALIDO ( p_arbObj ) )
	{
		if ( ES_VALIDO ( p_arbObj->p_nodActual ) )
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

int SArbEnraizar ( SArbol * p_arbObj, SNodo * p_nodObj )
{
	int iRes;

	if ( ES_VALIDO ( p_arbObj ) )
	{
		if ( ES_VALIDO ( p_arbObj->p_nodActual ) && ES_VALIDO ( p_nodObj ) )
		{
			SNodEmpadronar ( p_nodObj, p_arbObj->p_nodActual );
			if (  SNodInsertarHijo ( p_arbObj->p_nodActual, p_nodObj ) == 1 )
			{
				iRes = 1;
				SArbMoverAUltHijo ( p_arbObj );
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

int SArbVerificar ( SArbol * p_arbObj, int iCorregir )
{
	int iRes;

	if ( ES_VALIDO ( p_arbObj ) )
	{
		if ( ES_VALIDO ( p_arbObj->p_nodRaiz ) )
		{
			iRes = SNodVerificar ( p_arbObj->p_nodRaiz, iCorregir );
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




