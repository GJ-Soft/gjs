#include "SListaLiterales.h"

#include "TiposBasicosConfig.h"




SListaLiterales * SLisLitCrear ()
{
	SListaLiterales * p_lisObj;
	
	p_lisObj = (SListaLiterales *) MemReservar ( sizeof ( SListaLiterales ) );
	if ( ES_VALIDO ( p_lisObj ) )
	{
		p_lisObj->p_lisDatos = SLispCrear ();
	}
	return ( p_lisObj );
}

void SLisLitDestruir ( SListaLiterales ** p_p_lisObj )
{
	SListaLiterales * p_lisObj;
	
	if ( ES_VALIDO ( p_p_lisObj ) )
	{
		p_lisObj = *p_p_lisObj;

		if ( ES_VALIDO ( p_lisObj ) )
		{
			SLispDestruir ( &(p_lisObj->p_lisDatos) );
			MemLiberar ( (void **) p_p_lisObj );
		}
	}
}

int SLisLitEsValida ( SListaLiterales * p_lisObj )
{
	int iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iRes = SLispEsValida ( p_lisObj->p_lisDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLisLitEstaVacia ( SListaLiterales * p_lisObj )
{
	int iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iRes = SLispEstaVacia ( p_lisObj->p_lisDatos );
	}
	else
	{
		iRes = 1;
	}
	return ( iRes );
}

int SLisLitNumElementos ( SListaLiterales * p_lisObj )
{
	int iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iRes = SLispNumElementos ( p_lisObj->p_lisDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

char * SLisLitElemento ( SListaLiterales * p_lisObj, int iElem )
{
	char *	p_cRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		p_cRes = (char *) SLispElemento ( p_lisObj->p_lisDatos, iElem );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

int SLisLitEstablecerElem ( SListaLiterales * p_lisObj, int iElem, char * p_cDatos )
{
	int		iRes;
	char *	p_cAnt;	

	if ( ES_VALIDO ( p_lisObj ) )
	{
		// NOTA: El elemento ya se libera automaticamente
		p_cAnt = (char *) SLispElemento ( p_lisObj->p_lisDatos, iElem );
		if ( SLispEstablecerElem ( p_lisObj->p_lisDatos, iElem, (byte *) p_cDatos ) == 1 )
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

int SLisLitInsertarElem ( SListaLiterales * p_lisObj, int iPosAnt, char * p_cDatos )
{
	int iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iRes = SLispInsertarElem ( p_lisObj->p_lisDatos, iPosAnt, (byte *) p_cDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLisLitInsertarAlInicio ( SListaLiterales * p_lisObj, char * p_cDatos )
{
	return ( SLisLitInsertarElem ( p_lisObj, -1, p_cDatos ) );
}

int SLisLitInsertarAlFinal ( SListaLiterales * p_lisObj, char * p_cDatos )
{
	int iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iRes = SLisLitInsertarElem ( p_lisObj, SLisLitNumElementos ( p_lisObj ), p_cDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLisLitEstablecerElemDup ( SListaLiterales * p_lisObj, int iElem, const char * p_cDatos )
{
	char *	p_cElem;
	int		iRes;

	if ( ES_VALIDO ( p_lisObj ) && ES_VALIDO ( p_cDatos ) )
	{
		p_cElem = CadDuplicar ( p_cDatos );
		if ( ES_VALIDO ( p_cElem ) )
		{
			if ( SLisLitEstablecerElem ( p_lisObj, iElem, p_cElem ) == 1 )
			{
				iRes = 1;
			}
			else
			{
				MemLiberar ( (void **) &p_cElem );
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

int SLisLitInsertarElemDup ( SListaLiterales * p_lisObj, int iPosAnt, const char * p_cDatos )
{
	char *	p_cElem;
	int		iRes;

	if ( ES_VALIDO ( p_lisObj ) && ES_VALIDO ( p_cDatos ) )
	{
		p_cElem = CadDuplicar ( p_cDatos );
		if ( ES_VALIDO ( p_cElem ) )
		{
			iRes = SLispInsertarElem ( p_lisObj->p_lisDatos, iPosAnt, (byte *) p_cElem );
			if ( iRes != 1 )
			{
				MemLiberar ( (void **) &p_cElem );
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

int SLisLitInsertarDupAlInicio ( SListaLiterales * p_lisObj, const char * p_cDatos )
{
	char *	p_cElem;
	int		iRes;

	if ( ES_VALIDO ( p_lisObj ) && ES_VALIDO ( p_cDatos ) )
	{
		p_cElem = CadDuplicar ( p_cDatos );
		if ( ES_VALIDO ( p_cElem ) )
		{
			iRes = SLispInsertarElem ( p_lisObj->p_lisDatos, -1, (byte *) p_cElem );
			if ( iRes != 1 )
			{
				MemLiberar ( (void **) &p_cElem );
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

int SLisLitInsertarDupAlFinal ( SListaLiterales * p_lisObj, const char * p_cDatos )
{
	char *	p_cElem;
	int		iRes;

	if ( ES_VALIDO ( p_lisObj ) && ES_VALIDO ( p_cDatos ) )
	{
		p_cElem = CadDuplicar ( p_cDatos );
		if ( ES_VALIDO ( p_cElem ) )
		{
			iRes = SLispInsertarElem ( p_lisObj->p_lisDatos, 
									   SLisLitNumElementos ( p_lisObj ), 
									   (byte *) p_cElem );
			if ( iRes != 1 )
			{
				MemLiberar ( (void **) &p_cElem );
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

int SLisLitEliminarElem ( SListaLiterales * p_lisObj, int iElem )
{
	int iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iRes = SLispEliminarElem ( p_lisObj->p_lisDatos, iElem );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLisLitVaciar ( SListaLiterales * p_lisObj )
{
	int iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iRes = SLispVaciar ( p_lisObj->p_lisDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLisLitPosicion ( SListaLiterales * p_lisObj )
{
	int	iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iRes = SLispPosicion ( p_lisObj->p_lisDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

char * SLisLitActual ( SListaLiterales * p_lisObj )
{
	char *	p_cRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		p_cRes = (char *) SLispActual ( p_lisObj->p_lisDatos );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

void SLisLitInicio ( SListaLiterales * p_lisObj )
{
	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		SLispInicio ( p_lisObj->p_lisDatos );
	}
}

void SLisLitFinal ( SListaLiterales * p_lisObj )
{
	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		SLispFinal ( p_lisObj->p_lisDatos );
	}
}

void SLisLitSiguiente ( SListaLiterales * p_lisObj )
{
	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		SLispSiguiente ( p_lisObj->p_lisDatos );
	}
}

void SLisLitAnterior ( SListaLiterales * p_lisObj )
{
	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		SLispAnterior ( p_lisObj->p_lisDatos );
	}
}

void SLisLitMoverA ( SListaLiterales * p_lisObj, int iElem )
{
	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		SLispMoverA ( p_lisObj->p_lisDatos, iElem );
	}
}

void SLisLitDeposicionar ( SListaLiterales * p_lisObj )
{
	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		SLispDeposicionar ( p_lisObj->p_lisDatos );
	}
}

int SLisLitEsNulo ( SListaLiterales * p_lisObj )
{
	int iRes;

	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		iRes = SLispEsNulo ( p_lisObj->p_lisDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLisLitEstaEnFinal ( SListaLiterales * p_lisObj )
{
	int iRes;

	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		iRes = SLispEstaEnFinal ( p_lisObj->p_lisDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLisLitEstaEnInicio ( SListaLiterales * p_lisObj )
{
	int iRes;

	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		iRes = SLispEstaEnInicio ( p_lisObj->p_lisDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLisLitEstablecer ( SListaLiterales * p_lisObj, char * p_cDatos )
{
	char *	p_cAnt;  
	int		iRes;

	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		// NOTA: El elemento ya se libera automaticamente
		p_cAnt = (char *) SLispActual ( p_lisObj->p_lisDatos );
		iRes = SLispEstablecer ( p_lisObj->p_lisDatos, (byte *) p_cDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}


int SLisLitInsertar ( SListaLiterales * p_lisObj, char * p_cDatos )
{
	return ( SLisLitInsertarDetras ( p_lisObj, p_cDatos ) );
}

int SLisLitInsertarDelante ( SListaLiterales * p_lisObj, char * p_cDatos )
{
	int iRes;

	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		iRes = SLispInsertarDelante ( p_lisObj->p_lisDatos, (byte *) p_cDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLisLitInsertarDetras ( SListaLiterales * p_lisObj, char * p_cDatos )
{
	int iRes;

	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		iRes = SLispInsertarDetras ( p_lisObj->p_lisDatos, (byte *) p_cDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLisLitEstablecerDup ( SListaLiterales * p_lisObj, const char * p_cDatos )
{
	char *	p_cElem;
	int		iRes;

	if ( ES_VALIDO ( p_cDatos ) )
	{
		p_cElem = CadDuplicar ( p_cDatos );
		if ( ES_VALIDO ( p_cElem ) )
		{
			iRes = SLisLitEstablecer ( p_lisObj, p_cElem );
			if ( iRes != 1 )
			{
				MemLiberar ( (void **) &p_cElem );
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

int SLisLitInsertarDup ( SListaLiterales * p_lisObj, const char * p_cDatos )
{
	return ( SLisLitInsertarDupDetras ( p_lisObj, p_cDatos ) );
}

int SLisLitInsertarDupDelante ( SListaLiterales * p_lisObj, const char * p_cDatos )
{
	char *	p_cElem;
	int		iRes;

	if ( ES_VALIDO ( p_lisObj ) && ES_VALIDO ( p_cDatos ) )
	{
		p_cElem = CadDuplicar ( p_cDatos );
		if ( ES_VALIDO ( p_cElem ) )
		{
			iRes = SLispInsertarDelante ( p_lisObj->p_lisDatos, (byte *) p_cElem );
			if ( iRes != 1 )
			{
				MemLiberar ( (void **) &p_cElem );
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

int SLisLitInsertarDupDetras ( SListaLiterales * p_lisObj, const char * p_cDatos )
{
	char *	p_cElem;
	int		iRes;

	if ( ES_VALIDO ( p_lisObj ) && ES_VALIDO ( p_cDatos ) )
	{
		p_cElem = CadDuplicar ( p_cDatos );
		if ( ES_VALIDO ( p_cElem ) )
		{
			iRes = SLispInsertarDetras ( p_lisObj->p_lisDatos, (byte *) p_cElem );
			if ( iRes != 1 )
			{
				MemLiberar ( (void **) &p_cElem );
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

int SLisLitEliminar ( SListaLiterales * p_lisObj )
{
	int iRes;

	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		iRes = SLispEliminar ( p_lisObj->p_lisDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLisLitExiste ( SListaLiterales * p_lisObj, const char * p_cDatos )
{
	int iRes;
	int iElem;
	int iNumElems;

	if ( ES_VALIDO ( p_lisObj ) && ES_VALIDO ( p_cDatos )  ) 
	{
		iRes = 0;
		iElem = 0;
		iNumElems = SLisLitNumElementos ( p_lisObj );
		while ( ( iElem < iNumElems ) && ( iRes == 0 ) )
		{
			if ( CadComparar ( SLisLitElemento ( p_lisObj, iElem ), p_cDatos ) == COMP_IGUAL )
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

int SLisLitBuscar ( SListaLiterales * p_lisObj, const char * p_cDatos )
{
	int iRes;
	int iElem;
	int iNumElems;

	if ( ES_VALIDO ( p_lisObj ) && ES_VALIDO ( p_cDatos ) )
	{
		iRes = -1;
		iElem = 0;
		iNumElems = SLisLitNumElementos ( p_lisObj );
		while ( ( iElem < iNumElems ) && ( iRes == -1 ) )
		{
			if ( CadComparar ( SLisLitElemento ( p_lisObj, iElem ), p_cDatos ) == COMP_IGUAL )
			{
				iRes = iElem;
			}
			iElem = iElem + 1;
		}
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int	SLisLitLiberacionMemoriaActivada ( SListaLiterales * p_lisObj )
{
	int	iRes;

	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		iRes = SLispLiberacionMemoriaActivada ( p_lisObj->p_lisDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

void SLisLitActivarLiberacionMemoria ( SListaLiterales * p_lisObj )
{
	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		SLispActivarLiberacionMemoria ( p_lisObj->p_lisDatos );
	}
}

void SLisLitDesactivarLiberacionMemoria ( SListaLiterales * p_lisObj )
{
	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		SLispDesactivarLiberacionMemoria ( p_lisObj->p_lisDatos );
	}
}

void SLisLitImprimir  ( SListaLiterales * p_lisObj )
{
	int iElem;
	int iNumElems;
	
	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		printf ( "Contenido de la lista: [\n" );
		iElem = 0;
		iNumElems = SLisLitNumElementos ( p_lisObj );
		while ( iElem < iNumElems )
		{
			printf ( "\t[%s], \n", SLisLitElemento ( p_lisObj, iElem ) );
			iElem = iElem + 1;
		}
		printf ( "]\n" );
	}
	else
	{
		printf ( "%s\n", VALOR_NULO );
	}
}


