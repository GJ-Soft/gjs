


#include "SSecuenciaId.h"

#include "TiposBasicosConfig.h"




SSecuenciaId * SSecIdCrear ()
{
	SSecuenciaId * p_secObj;

	p_secObj = (SSecuenciaId *) MemReservar ( sizeof ( SSecuenciaId ) );
	if ( ES_VALIDO ( p_secObj ) )
	{
		p_secObj->p_secDatos = SSecCrear ();
		if ( ES_NULO ( p_secObj->p_secDatos ) )
		{
			MemLiberar ( (void **) &p_secObj );
		}
	}
	return ( p_secObj );
}

void SSecIdDestruir ( SSecuenciaId ** p_p_secObj )
{
	SSecuenciaId * p_secObj;

	if ( ES_VALIDO ( p_p_secObj ) )
	{
		p_secObj = *p_p_secObj;

		if ( ES_VALIDO ( p_secObj ) )
		{
			SSecDestruir ( &(p_secObj->p_secDatos) );
			MemLiberar ( (void **) p_p_secObj );
		}
	}
}

int SSecIdEsValida ( SSecuenciaId * p_secObj )
{
	int iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		iRes = SSecEsValida ( p_secObj->p_secDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SSecIdEstaVacia ( SSecuenciaId * p_secObj )
{
	int iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		iRes = SSecEstaVacia ( p_secObj->p_secDatos );
	}
	else
	{
		iRes = 1;
	}
	return ( iRes );
}

int SSecIdNumElementos ( SSecuenciaId * p_secObj )
{
	int iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		iRes = SSecNumElementos ( p_secObj->p_secDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

/* Buscan por el contenido de p_idDato, que no hace falta que este en la
   secuencia. Existe y Repeticiones dan 0 con un nulo; las de buscar, -1.
   BuscarSiguiente busca DETRAS de iPos: con -1, desde el principio. */
int SSecIdExiste ( SSecuenciaId * p_secObj, SId * p_idDato )
{
	int			iRes;
	SBloque *	p_blqDato;

	if ( ES_VALIDO ( p_secObj ) )
	{
		p_blqDato = SIdBloqueBin ( p_idDato );
		if ( ES_VALIDO ( p_blqDato ) )
		{
			iRes = SSecExiste ( p_secObj->p_secDatos, p_blqDato );
			SBlqDestruir ( &p_blqDato );
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

int SSecIdBuscar ( SSecuenciaId * p_secObj, SId * p_idDato )
{
	return ( SSecIdBuscarSiguiente ( p_secObj, p_idDato, -1 ) );
}

int SSecIdRepeticiones ( SSecuenciaId * p_secObj, SId * p_idDato )
{
	int			iRes;
	SBloque *	p_blqDato;

	if ( ES_VALIDO ( p_secObj ) )
	{
		p_blqDato = SIdBloqueBin ( p_idDato );
		if ( ES_VALIDO ( p_blqDato ) )
		{
			iRes = SSecRepeticiones ( p_secObj->p_secDatos, p_blqDato );
			SBlqDestruir ( &p_blqDato );
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

int SSecIdBuscarPrimero ( SSecuenciaId * p_secObj, SId * p_idDato )
{
	return ( SSecIdBuscarSiguiente ( p_secObj, p_idDato, -1 ) );
}

int SSecIdBuscarSiguiente ( SSecuenciaId * p_secObj, SId * p_idDato, int iPos )
{
	int			iRes;
	SBloque *	p_blqDato;

	if ( ES_VALIDO ( p_secObj ) )
	{
		p_blqDato = SIdBloqueBin ( p_idDato );
		if ( ES_VALIDO ( p_blqDato ) )
		{
			iRes = SSecBuscarSiguiente ( p_secObj->p_secDatos, p_blqDato, iPos );
			SBlqDestruir ( &p_blqDato );
		}
		else
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

int SSecIdExisteExt ( SSecuenciaId * p_secObj, unsigned long ulDato )
{
	SId	idDato;

	SIdEstablecer ( &idDato, ulDato );
	return ( SSecIdExiste ( p_secObj, &idDato ) );
}

int SSecIdBuscarExt ( SSecuenciaId * p_secObj, unsigned long ulDato )
{
	SId	idDato;

	SIdEstablecer ( &idDato, ulDato );
	return ( SSecIdBuscar ( p_secObj, &idDato ) );
}

int SSecIdRepeticionesExt ( SSecuenciaId * p_secObj, unsigned long ulDato )
{
	SId	idDato;

	SIdEstablecer ( &idDato, ulDato );
	return ( SSecIdRepeticiones ( p_secObj, &idDato ) );
}

int SSecIdBuscarPrimeroExt ( SSecuenciaId * p_secObj, unsigned long ulDato )
{
	SId	idDato;

	SIdEstablecer ( &idDato, ulDato );
	return ( SSecIdBuscarPrimero ( p_secObj, &idDato ) );
}

int SSecIdBuscarSiguienteExt ( SSecuenciaId * p_secObj, unsigned long ulDato, int iPos )
{
	SId	idDato;

	SIdEstablecer ( &idDato, ulDato );
	return ( SSecIdBuscarSiguiente ( p_secObj, &idDato, iPos ) );
}

/* SId nuevo leido de la copia guardada: es del llamante, que lo destruye. */
SId * SSecIdElemento ( SSecuenciaId * p_secObj, int iElem )
{
	SId *		p_idRes;
	SElemento *	p_elmDato;

	if ( ES_VALIDO ( p_secObj ) )
	{
		p_elmDato = SSecElemento ( p_secObj->p_secDatos, iElem );
		if ( ES_VALIDO ( p_elmDato ) )
		{
			p_idRes = SIdLeerDeBloqueBin ( SElmDatos ( p_elmDato ) );
		}
		else
		{
			p_idRes = NULL;
		}
	}
	else
	{
		p_idRes = NULL;
	}
	return ( p_idRes );
}

/* 0 si no hay elemento en iElem: no se distingue de un identificador 0. */
unsigned long SSecIdValorElemento ( SSecuenciaId * p_secObj, int iElem )
{
	unsigned long	ulRes;
	SId *			p_idObj;

	p_idObj = SSecIdElemento ( p_secObj, iElem );
	if ( ES_VALIDO ( p_idObj ) )
	{
		ulRes = SIdValor ( p_idObj );
		SIdDestruir ( &p_idObj );
	}
	else
	{
		ulRes = 0;
	}
	return ( ulRes );
}

/* Añade al final una copia: p_idDato sigue siendo del llamante. */
int SSecIdInsertar ( SSecuenciaId * p_secObj, SId * p_idDato )
{
	int			iRes;
	SBloque *	p_blqDato;
	SElemento *	p_elmDato;

	if ( ES_VALIDO ( p_secObj ) )
	{
		p_blqDato = SIdBloqueBin ( p_idDato );
		if ( ES_VALIDO ( p_blqDato ) )
		{
			p_elmDato = SElmEncapsular ( p_blqDato );
			if ( ES_VALIDO ( p_elmDato ) )
			{
				/* Si no entra, el elemento se lleva el bloque. */
				iRes = SSecInsertar ( p_secObj->p_secDatos, p_elmDato );
				if ( iRes == 0 )
				{
					SElmDestruir ( &p_elmDato );
				}
			}
			else
			{
				SBlqDestruir ( &p_blqDato );
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

int SSecIdInsertarExt ( SSecuenciaId * p_secObj, unsigned long ulDato )
{
	SId	idDato;

	SIdEstablecer ( &idDato, ulDato );
	return ( SSecIdInsertar ( p_secObj, &idDato ) );
}

int SSecIdEliminarElem ( SSecuenciaId * p_secObj, int iElem )
{
	int	iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		iRes = SSecEliminar ( p_secObj->p_secDatos, iElem );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SSecIdVaciar ( SSecuenciaId * p_secObj )
{
	int iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		iRes = SSecVaciar ( p_secObj->p_secDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

SSecuencia * SSecIdSecuencia ( SSecuenciaId * p_secObj )
{
	SSecuencia * p_secRes;

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
