#include "SSecuenciaLiterales.h"

#include "TiposBasicosConfig.h"


extern int _SLisLitSonIguales ( byte * p_byLiteral1, byte * p_byLiteral2 );
extern byte * _SLisLitDuplicar ( byte * p_byLiteral );
extern SListaPtr * _SLisLitExtraerUnicos ( SListaPtr * p_lisDatos, int iOrdenar );
extern int _SLisLitTieneRepetidos ( SListaPtr * p_lisDatos );

static SSecuenciaLiterales * _SSecLitEnvolver ( SSecuenciaPtr * p_secDatos );



SSecuenciaLiterales * SSecLitCrear ()
{
	SSecuenciaLiterales * p_secObj;
	
	p_secObj = (SSecuenciaLiterales *) MemReservar ( sizeof ( SSecuenciaLiterales ) );
	if ( ES_VALIDO ( p_secObj ) )
	{
		p_secObj->p_secDatos = SSecpCrear ();
		SSecpActivarLiberacionMemoria ( p_secObj->p_secDatos );
	}
	return ( p_secObj );
}

/* Secuencia con COPIAS de las cadenas de la lista, que no se toca. */
SSecuenciaLiterales * SSecLitCrearDesdeLista ( SListaLiterales * p_lisValores )
{
	SSecuenciaLiterales * p_secRes;

	if ( ES_VALIDO ( p_lisValores ) )
	{
		p_secRes = _SSecLitEnvolver ( SSecpCrearDesdeListaExt ( p_lisValores->p_lisDatos, _SLisLitDuplicar ) );
	}
	else
	{
		p_secRes = NULL;
	}
	return ( p_secRes );
}

void SSecLitDestruir ( SSecuenciaLiterales ** p_p_secObj )
{
	SSecuenciaLiterales * p_secObj;
	
	if ( ES_VALIDO ( p_p_secObj ) )
	{
		p_secObj = *p_p_secObj;

		if ( ES_VALIDO ( p_secObj ) )
		{
			SSecpDestruir ( &(p_secObj->p_secDatos) );
			MemLiberar ( (void **) p_p_secObj );
		}
	}
}

int SSecLitEsValida ( SSecuenciaLiterales * p_secObj )
{
	int iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		iRes = SSecpEsValida ( p_secObj->p_secDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SSecLitEstaVacia ( SSecuenciaLiterales * p_secObj )
{
	int iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		iRes = SSecpEstaVacia ( p_secObj->p_secDatos );
	}
	else
	{
		iRes = 1;
	}
	return ( iRes );
}

int SSecLitNumElementos ( SSecuenciaLiterales * p_secObj )
{
	int iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		iRes = SSecpNumElementos ( p_secObj->p_secDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

char * SSecLitElemento ( SSecuenciaLiterales * p_secObj, int iElem )
{
	char *	p_cRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		p_cRes = (char *) SSecpElemento ( p_secObj->p_secDatos, iElem );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

int SSecLitInsertar ( SSecuenciaLiterales * p_secObj, const char * p_cDatos )
{
	int		iRes;
	char *	p_cElem;

	if ( ES_VALIDO ( p_secObj ) && ES_VALIDO ( p_cDatos ) )
	{
		p_cElem = CadDuplicar ( p_cDatos );
		if ( ES_VALIDO ( p_cElem ) )
		{
			iRes = SSecpInsertar ( p_secObj->p_secDatos, (byte *) p_cElem );
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

int SSecLitEliminar ( SSecuenciaLiterales * p_secObj, int iElem )
{
	int iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		iRes = SSecpEliminar ( p_secObj->p_secDatos, iElem );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SSecLitVaciar ( SSecuenciaLiterales * p_secObj )
{
	int iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		iRes = SSecpVaciar ( p_secObj->p_secDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SSecLitExiste ( SSecuenciaLiterales * p_secObj, const char * p_cDato )
{
	int				iRes;
	SElementoPtr *	p_elpObj;

	if ( ES_VALIDO ( p_secObj ) && ES_VALIDO ( p_cDato )  )
	{
		iRes = 0;
		/* Por la CADENA, no por indice: el indice entra por el extremo mas
		   cercano, asi que un recorrido completo sale cuadratico. */
		p_elpObj = SSecpElementoPtr ( p_secObj->p_secDatos, 0 );
		while ( ES_VALIDO ( p_elpObj ) && ( iRes == 0 ) )
		{
			if ( CadComparar ( (char *) SElpDatos ( p_elpObj ), p_cDato ) == COMP_IGUAL )
			{
				iRes = 1;
			}
			p_elpObj = SElpSucesor ( p_elpObj );
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

/* Busquedas: comparan el CONTENIDO con CadComparar y delegan en las Ext de
   SSecuenciaPtr. Repeticiones: cuantas iguales hay, 0 si ninguna. Buscar es
   BuscarPrimero: la posicion de la primera igual, o -1. BuscarSiguiente busca
   DETRAS de iPos: con -1, desde el principio. */
int SSecLitRepeticiones ( SSecuenciaLiterales * p_secObj, const char * p_cDato )
{
	int	iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		iRes = SSecpRepeticionesExt ( p_secObj->p_secDatos, (byte *) p_cDato, _SLisLitSonIguales );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SSecLitBuscar ( SSecuenciaLiterales * p_secObj, const char * p_cDato )
{
	return ( SSecLitBuscarPrimero ( p_secObj, p_cDato ) );
}

int SSecLitBuscarPrimero ( SSecuenciaLiterales * p_secObj, const char * p_cDato )
{
	return ( SSecLitBuscarSiguiente ( p_secObj, p_cDato, -1 ) );
}

int SSecLitBuscarSiguiente ( SSecuenciaLiterales * p_secObj, const char * p_cDato, int iPos )
{
	int	iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		iRes = SSecpBuscarSiguienteExt ( p_secObj->p_secDatos, (byte *) p_cDato, iPos, _SLisLitSonIguales );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

/* Secuencia nueva con COPIAS de las cadenas distintas, en el orden de su
   primera aparicion; NULL si falla, con ERR_GENERAL_OPERATIVO. */
SSecuenciaLiterales * SSecLitExtraerUnicos ( SSecuenciaLiterales * p_secObj )
{
	SSecuenciaLiterales *	p_secRes;
	SListaPtr *				p_lisUnicos;
	SSecuenciaPtr *			p_secUnicos;

	if ( ES_VALIDO ( p_secObj ) )
	{
		p_lisUnicos = _SLisLitExtraerUnicos ( SSecpLista ( p_secObj->p_secDatos ), 0 );
		p_secUnicos = SSecpEncapsularLista ( p_lisUnicos );
		if ( ES_NULO ( p_secUnicos ) )
		{
			SLispDestruir ( &p_lisUnicos );
		}
		p_secRes = _SSecLitEnvolver ( p_secUnicos );
	}
	else
	{
		p_secRes = NULL;
	}
	return ( p_secRes );
}

int SSecLitTieneRepetidos ( SSecuenciaLiterales * p_secObj )
{
	int	iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		iRes = _SLisLitTieneRepetidos ( SSecpLista ( p_secObj->p_secDatos ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

/* La secuencia interna, y la lista de esa secuencia. */
SSecuenciaPtr * SSecLitSecuencia ( SSecuenciaLiterales * p_secObj )
{
	SSecuenciaPtr * p_secRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		p_secRes = p_secObj->p_secDatos;
	}
	else
	{
		p_secRes = NULL;
	}
	return ( p_secRes );
}

SListaPtr * SSecLitLista ( SSecuenciaLiterales * p_secObj )
{
	SListaPtr * p_lisRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		p_lisRes = SSecpLista ( p_secObj->p_secDatos );
	}
	else
	{
		p_lisRes = NULL;
	}
	return ( p_lisRes );
}

/* Envuelve una secuencia ya creada; si no hay o no se puede envolver, NULL y
   la secuencia se destruye. */
static SSecuenciaLiterales * _SSecLitEnvolver ( SSecuenciaPtr * p_secDatos )
{
	SSecuenciaLiterales * p_secRes;

	if ( ES_VALIDO ( p_secDatos ) )
	{
		p_secRes = (SSecuenciaLiterales *) MemReservar ( sizeof ( SSecuenciaLiterales ) );
		if ( ES_VALIDO ( p_secRes ) )
		{
			p_secRes->p_secDatos = p_secDatos;
		}
		else
		{
			SSecpDestruir ( &p_secDatos );
		}
	}
	else
	{
		p_secRes = NULL;
	}
	return ( p_secRes );
}



