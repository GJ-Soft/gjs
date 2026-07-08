#include "SArbolPtr.h"



#include "TiposBasicosConfig.h"




SArbolPtr * SArbPtrCrear () 
{
	SArbolPtr * p_arbpObj;
	
	p_arbpObj = (SArbolPtr *) MemReservar ( sizeof ( SArbolPtr ) );
	if ( ES_VALIDO ( p_arbpObj ) )
	{
		p_arbpObj->p_nodpRaiz = NULL;
		p_arbpObj->p_nodpActual = NULL;
	}
	return ( p_arbpObj );
}

void SArbPtrDestruir ( SArbolPtr ** p_p_arbpObj )
{
	SArbolPtr * p_arbpObj;
	
	if ( ES_VALIDO ( p_p_arbpObj ) )
	{
		p_arbpObj = *p_p_arbpObj;
		if ( ES_VALIDO ( p_arbpObj ) )
		{
			SArbPtrVaciar ( p_arbpObj );
			MemLiberar ( (void **) p_p_arbpObj );
		}
	}
}

SNodoPtr * SArbPtrRaiz ( SArbolPtr * p_arbpObj )
{
	SNodoPtr * p_nodRes;
	
	if ( ES_VALIDO ( p_arbpObj ) )
	{
		p_nodRes = p_arbpObj->p_nodpRaiz;
	}
	else
	{
		p_nodRes = NULL;
	}
	return ( p_nodRes );
}

int SArbPtrEstablecerRaiz ( SArbolPtr * p_arbpObj, SNodoPtr * p_nodpObj )
{
	int iRes;

	if ( ES_VALIDO ( p_arbpObj ) )
	{
		p_arbpObj->p_nodpRaiz = p_nodpObj;
		if ( ES_VALIDO ( p_arbpObj->p_nodpRaiz ) )
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

int SArbPtrEstaVacio ( SArbolPtr * p_arbpObj )
{
	int iRes;

	if ( ES_VALIDO ( p_arbpObj ) )
	{
		if ( ES_NULO ( p_arbpObj->p_nodpRaiz ) )
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

int SArbPtrNiveles ( SArbolPtr * p_arbpObj )
{
	int iNiveles;

	if ( ES_VALIDO ( p_arbpObj ) )
	{
		if ( ES_VALIDO ( p_arbpObj->p_nodpRaiz ) )
		{
			iNiveles = SNodPtrNivelesInferiores ( p_arbpObj->p_nodpRaiz ) + 1;
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

int SArbPtrNumNodos ( SArbolPtr * p_arbpObj )
{
	int iNodos;

	if ( ES_VALIDO ( p_arbpObj ) )
	{
		if ( ES_VALIDO ( p_arbpObj->p_nodpRaiz ) )
		{
			iNodos = SNodPtrNodosInferiores ( p_arbpObj->p_nodpRaiz ) + 1;
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

int SArbPtrVaciar ( SArbolPtr * p_arbpObj )
{
	int		iRes;

	if ( ES_VALIDO ( p_arbpObj ) )
	{
		if ( ES_VALIDO ( p_arbpObj->p_nodpRaiz ) )
		{
			SNodPtrDestruir ( &(p_arbpObj->p_nodpRaiz), 1 );
			p_arbpObj->p_nodpActual = NULL;
			if ( SArbPtrNumNodos ( p_arbpObj ) == 0 )
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

SNodoPtr * SArbPtrActual ( SArbolPtr * p_arbpObj )
{
	SNodoPtr * p_nodRes;
	
	if ( ES_VALIDO ( p_arbpObj ) )
	{
		p_nodRes = p_arbpObj->p_nodpActual;
	}
	else
	{
		p_nodRes = NULL;
	}
	return ( p_nodRes );
}

int SArbPtrMoverARaiz ( SArbolPtr * p_arbpObj )
{
	int iRes;
	
	if ( ES_VALIDO ( p_arbpObj ) )
	{
		p_arbpObj->p_nodpActual = p_arbpObj->p_nodpRaiz;
		if ( ES_VALIDO ( p_arbpObj->p_nodpActual ) )
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

int SArbPtrMoverAPadre ( SArbolPtr * p_arbpObj )
{
	int iRes;
	
	if ( ES_VALIDO ( p_arbpObj ) )
	{
		if ( ES_VALIDO ( p_arbpObj->p_nodpActual ) )
		{
			p_arbpObj->p_nodpActual = SNodPtrPadre ( p_arbpObj->p_nodpActual );
			if ( ES_VALIDO ( p_arbpObj->p_nodpActual ) )
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

int SArbPtrMoverAHijo ( SArbolPtr * p_arbpObj, int iHijo )
{
	int iRes;
	
	if ( ES_VALIDO ( p_arbpObj ) )
	{
		if ( ES_VALIDO ( p_arbpObj->p_nodpActual ) )
		{
			p_arbpObj->p_nodpActual = SNodPtrHijo ( p_arbpObj->p_nodpActual, iHijo );
			if ( ES_VALIDO ( p_arbpObj->p_nodpActual ) )
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

int SArbPtrMoverAPrimHijo ( SArbolPtr * p_arbpObj )
{
	int iRes;
	
	if ( ES_VALIDO ( p_arbpObj ) )
	{
		iRes = SArbPtrMoverAHijo ( p_arbpObj, 0 );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SArbPtrMoverAUltHijo ( SArbolPtr * p_arbpObj )
{
	int iRes;
	
	if ( ES_VALIDO ( p_arbpObj ) )
	{
		if ( ES_VALIDO ( p_arbpObj->p_nodpActual ) )
		{
			iRes = SArbPtrMoverAHijo ( p_arbpObj, SNodPtrNumHijos ( p_arbpObj->p_nodpActual ) - 1 );
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

int SArbPtrMoverAPrimHermano ( SArbolPtr * p_arbpObj )
{
	int 		iRes;
	SNodoPtr * 	p_nodpPadre;
	
	if ( ES_VALIDO ( p_arbpObj ) )
	{
		if ( ES_VALIDO ( p_arbpObj->p_nodpActual ) )
		{
			p_nodpPadre = SNodPtrPadre ( p_arbpObj->p_nodpActual );
			if ( ES_VALIDO ( p_nodpPadre ) )
			{
				p_arbpObj->p_nodpActual = SNodPtrHijo ( p_nodpPadre, 0 );
				if ( ES_VALIDO ( p_arbpObj->p_nodpActual ) )
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

int SArbPtrMoverASigHermano ( SArbolPtr * p_arbpObj )
{
	int 		iRes;
	int			iHijo;
	SNodoPtr * 	p_nodpPadre;

	if ( ES_VALIDO ( p_arbpObj ) )
	{
		if ( ES_VALIDO ( p_arbpObj->p_nodpActual ) )
		{
			if ( SNodPtrTienePadre ( p_arbpObj->p_nodpActual ) == 1 )
			{
				p_nodpPadre = SNodPtrPadre ( p_arbpObj->p_nodpActual );
				iHijo = SNodPtrOrdenDelHijo ( p_nodpPadre, p_arbpObj->p_nodpActual );
				if ( iHijo >= 0 )
				{
					p_arbpObj->p_nodpActual = SNodPtrHijo ( p_nodpPadre, iHijo + 1 );
					if ( ES_VALIDO ( p_arbpObj->p_nodpActual ) )
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

int SArbPtrMoverAAntHermano ( SArbolPtr * p_arbpObj )
{
	int 		iRes;
	int			iHijo;
	SNodoPtr *	 p_nodpPadre;

	if ( ES_VALIDO ( p_arbpObj ) )
	{
		if ( ES_VALIDO ( p_arbpObj->p_nodpActual ) )
		{
			if ( SNodPtrTienePadre ( p_arbpObj->p_nodpActual ) == 1 )
			{
				p_nodpPadre = SNodPtrPadre ( p_arbpObj->p_nodpActual );
				iHijo = SNodPtrOrdenDelHijo ( p_nodpPadre, p_arbpObj->p_nodpActual );
				if ( iHijo > 0 )
				{
					p_arbpObj->p_nodpActual = SNodPtrHijo ( p_nodpPadre, iHijo - 1 );
					if ( ES_VALIDO ( p_arbpObj->p_nodpActual ) )
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

int SArbPtrMoverAUltHermano ( SArbolPtr * p_arbpObj )
{
	int			iRes;
	SNodoPtr * 	p_nodpPadre;
	
	if ( ES_VALIDO ( p_arbpObj ) )
	{
		p_nodpPadre = SNodPtrPadre ( p_arbpObj->p_nodpActual );
		if ( ES_VALIDO ( p_nodpPadre ) )
		{
			p_arbpObj->p_nodpActual = SNodPtrHijo ( p_nodpPadre, SNodPtrNumHijos ( p_nodpPadre ) - 1 );
			if ( ES_VALIDO ( p_arbpObj->p_nodpActual ) )
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

int SArbPtrMoverAPrimPreorden ( SArbolPtr * p_arbpObj )
{
	int iRes;
	
	if ( ES_VALIDO ( p_arbpObj ) )
	{
		iRes = SArbPtrMoverARaiz ( p_arbpObj );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SArbPtrMoverASigPreorden ( SArbolPtr * p_arbpObj )
{
	int 	iRes;
	
	if ( ES_VALIDO ( p_arbpObj ) )
	{
		if ( ES_VALIDO ( p_arbpObj->p_nodpActual ) )
		{
			if ( SNodPtrTieneHijos ( p_arbpObj->p_nodpActual ) == 1 )
			{
				iRes = SArbPtrMoverAHijo ( p_arbpObj, 0 );
			}
			else if ( SNodPtrTieneHermanosDer ( p_arbpObj->p_nodpActual ) == 1 )
			{
				iRes = SArbPtrMoverASigHermano ( p_arbpObj );
			} 
			else 
			{
				iRes = 1;
				while ( ( iRes == 1 ) && ( SNodPtrTieneHermanosDer ( p_arbpObj->p_nodpActual ) == 0 ) )
				{
					iRes = SArbPtrMoverAPadre ( p_arbpObj );
				}
				if ( iRes == 1 )
				{
					iRes = SArbPtrMoverASigHermano ( p_arbpObj );
				}
				else
				{
					p_arbpObj->p_nodpActual = NULL;
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

int SArbPtrMoverAPrimPostorden ( SArbolPtr * p_arbpObj )
{
	int 	iRes;

	if ( ES_VALIDO ( p_arbpObj ) )
	{
		iRes = SArbPtrMoverARaiz ( p_arbpObj );
		while ( ES_VALIDO ( p_arbpObj->p_nodpActual ) && ( SNodPtrTieneHijos ( p_arbpObj->p_nodpActual ) == 1 ) )
		{
			SArbPtrMoverAHijo ( p_arbpObj, 0 );
		}
		if ( ES_VALIDO ( p_arbpObj->p_nodpActual ) )
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

int SArbPtrMoverASigPostorden ( SArbolPtr * p_arbpObj )
{
	int 	iRes;

	if ( ES_VALIDO ( p_arbpObj ) )
	{
		if ( ES_VALIDO ( p_arbpObj->p_nodpActual ) )
		{
			if ( SNodPtrTieneHermanosDer ( p_arbpObj->p_nodpActual ) == 1 )
			{
				iRes = SArbPtrMoverASigHermano ( p_arbpObj );
				while ( ( iRes == 1 ) && ( SNodPtrTieneHijos ( p_arbpObj->p_nodpActual ) == 1 ) )
				{
					iRes = SArbPtrMoverAHijo ( p_arbpObj, 0 );
				}
			}
			else if ( SNodPtrTienePadre ( p_arbpObj->p_nodpActual ) == 1 )
			{
				iRes = SArbPtrMoverAPadre ( p_arbpObj );
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

void SArbPtrDesposicionar ( SArbolPtr * p_arbpObj )
{
	if ( ES_VALIDO ( p_arbpObj ) )
	{
		p_arbpObj->p_nodpActual = NULL;
	}
}

int	SArbPtrEstaPosicionado ( SArbolPtr * p_arbpObj )
{
	int iRes;

	if ( ES_VALIDO ( p_arbpObj ) )
	{
		if ( ES_VALIDO ( p_arbpObj->p_nodpActual ) )
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

int SArbPtrEnraizar ( SArbolPtr * p_arbpObj, SNodoPtr * p_nodpObj )
{
	int iRes;

	if ( ES_VALIDO ( p_arbpObj ) )
	{
		if ( ES_VALIDO ( p_arbpObj->p_nodpActual ) && ES_VALIDO ( p_nodpObj ) )
		{
			SNodPtrEmpadronar ( p_nodpObj, p_arbpObj->p_nodpActual );
			if (  SNodPtrInsertarHijo ( p_arbpObj->p_nodpActual, p_nodpObj ) == 1 )
			{
				iRes = 1;
				SArbPtrMoverAUltHijo ( p_arbpObj );
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

int SArbPtrVerificar ( SArbolPtr * p_arbpObj, int iCorregir )
{
	int iRes;

	if ( ES_VALIDO ( p_arbpObj ) )
	{
		if ( ES_VALIDO ( p_arbpObj->p_nodpRaiz ) )
		{
			iRes = SNodPtrVerificar ( p_arbpObj->p_nodpRaiz, iCorregir );
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




