


#include "SConjuntoId.h"

#include "TiposBasicosConfig.h"


static SId * _SCnjIdLeer ( void * p_vDatos );
static int _SCnjIdComparar ( void * p_vVal1, void * p_vVal2 );



SConjuntoId * SCnjIdCrear ()
{
	SConjuntoId * p_cnjObj;

	p_cnjObj = (SConjuntoId *) MemReservar ( sizeof ( SConjuntoId ) );
	if ( ES_VALIDO ( p_cnjObj ) )
	{
		p_cnjObj->p_cnjDatos = SCnjCrear ( _SCnjIdComparar );
		if ( ES_NULO ( p_cnjObj->p_cnjDatos ) )
		{
			MemLiberar ( (void **) &p_cnjObj );
		}
	}
	return ( p_cnjObj );
}

void SCnjIdDestruir ( SConjuntoId ** p_p_cnjObj )
{
	SConjuntoId * p_cnjObj;

	if ( ES_VALIDO ( p_p_cnjObj ) )
	{
		p_cnjObj = *p_p_cnjObj;

		if ( ES_VALIDO ( p_cnjObj ) )
		{
			SCnjDestruir ( &(p_cnjObj->p_cnjDatos) );
			MemLiberar ( (void **) p_p_cnjObj );
		}
	}
}

int SCnjIdEsValido ( SConjuntoId * p_cnjObj )
{
	int iRes;

	if ( ES_VALIDO ( p_cnjObj ) )
	{
		iRes = SCnjEsValido ( p_cnjObj->p_cnjDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCnjIdEstaVacio ( SConjuntoId * p_cnjObj )
{
	int iRes;

	if ( ES_VALIDO ( p_cnjObj ) )
	{
		iRes = SCnjEstaVacio ( p_cnjObj->p_cnjDatos );
	}
	else
	{
		iRes = 1;
	}
	return ( iRes );
}

int SCnjIdNumElementos ( SConjuntoId * p_cnjObj )
{
	int iRes;

	if ( ES_VALIDO ( p_cnjObj ) )
	{
		iRes = SCnjNumElementos ( p_cnjObj->p_cnjDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

/* Buscan por el contenido de p_idDato, que no hace falta que este en el
   conjunto. */
int SCnjIdExiste ( SConjuntoId * p_cnjObj, SId * p_idDato )
{
	int			iRes;
	SBloque *	p_blqDato;

	if ( ES_VALIDO ( p_cnjObj ) )
	{
		p_blqDato = SIdBloqueBin ( p_idDato );
		if ( ES_VALIDO ( p_blqDato ) )
		{
			iRes = SCnjExiste ( p_cnjObj->p_cnjDatos, p_blqDato );
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

int SCnjIdBuscar ( SConjuntoId * p_cnjObj, SId * p_idDato )
{
	int			iRes;
	SBloque *	p_blqDato;

	if ( ES_VALIDO ( p_cnjObj ) )
	{
		p_blqDato = SIdBloqueBin ( p_idDato );
		if ( ES_VALIDO ( p_blqDato ) )
		{
			iRes = SCnjBuscar ( p_cnjObj->p_cnjDatos, p_blqDato );
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

int SCnjIdExisteExt ( SConjuntoId * p_cnjObj, unsigned long ulDato )
{
	SId	idDato;

	SIdEstablecer ( &idDato, ulDato );
	return ( SCnjIdExiste ( p_cnjObj, &idDato ) );
}

int SCnjIdBuscarExt ( SConjuntoId * p_cnjObj, unsigned long ulDato )
{
	SId	idDato;

	SIdEstablecer ( &idDato, ulDato );
	return ( SCnjIdBuscar ( p_cnjObj, &idDato ) );
}

/* SId nuevo leido de la copia guardada: es del llamante, que lo destruye. */
SId * SCnjIdElemento ( SConjuntoId * p_cnjObj, int iElem )
{
	SId *		p_idRes;
	SElemento *	p_elmDato;

	if ( ES_VALIDO ( p_cnjObj ) )
	{
		p_elmDato = SCnjElemento ( p_cnjObj->p_cnjDatos, iElem );
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
unsigned long SCnjIdValorElemento ( SConjuntoId * p_cnjObj, int iElem )
{
	unsigned long	ulRes;
	SId *			p_idObj;

	p_idObj = SCnjIdElemento ( p_cnjObj, iElem );
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

/* Guarda una copia: p_idDato sigue siendo del llamante. */
int SCnjIdInsertar ( SConjuntoId * p_cnjObj, SId * p_idDato )
{
	int			iRes;
	SBloque *	p_blqDato;
	SElemento *	p_elmDato;

	if ( ES_VALIDO ( p_cnjObj ) )
	{
		p_blqDato = SIdBloqueBin ( p_idDato );
		if ( ES_VALIDO ( p_blqDato ) )
		{
			p_elmDato = SElmEncapsular ( p_blqDato );
			if ( ES_VALIDO ( p_elmDato ) )
			{
				/* Si no entra ( repetido ), el elemento se lleva el bloque. */
				iRes = SCnjInsertarElem ( p_cnjObj->p_cnjDatos, p_elmDato );
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

int SCnjIdInsertarExt ( SConjuntoId * p_cnjObj, unsigned long ulDato )
{
	SId	idDato;

	SIdEstablecer ( &idDato, ulDato );
	return ( SCnjIdInsertar ( p_cnjObj, &idDato ) );
}

/* 0 si no esta. */
int SCnjIdEliminar ( SConjuntoId * p_cnjObj, SId * p_idDato )
{
	int	iRes;
	int	iPos;

	iPos = SCnjIdBuscar ( p_cnjObj, p_idDato );
	if ( iPos >= 0 )
	{
		iRes = SCnjEliminarElem ( p_cnjObj->p_cnjDatos, iPos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCnjIdEliminarExt ( SConjuntoId * p_cnjObj, unsigned long ulDato )
{
	SId	idDato;

	SIdEstablecer ( &idDato, ulDato );
	return ( SCnjIdEliminar ( p_cnjObj, &idDato ) );
}

int SCnjIdEliminarElem ( SConjuntoId * p_cnjObj, int iElem )
{
	int	iRes;

	if ( ES_VALIDO ( p_cnjObj ) )
	{
		iRes = SCnjEliminarElem ( p_cnjObj->p_cnjDatos, iElem );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCnjIdVaciar ( SConjuntoId * p_cnjObj )
{
	int	iRes;

	if ( ES_VALIDO ( p_cnjObj ) )
	{
		iRes = SCnjVaciar ( p_cnjObj->p_cnjDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

SConjunto * SCnjIdConjunto ( SConjuntoId * p_cnjObj )
{
	SConjunto * p_cnjRes;

	if ( ES_VALIDO ( p_cnjObj ) )
	{
		p_cnjRes = p_cnjObj->p_cnjDatos;
	}
	else
	{
		p_cnjRes = NULL;
	}
	return ( p_cnjRes );
}

/* Lee como SId la copia guardada en p_vDatos. El comparador solo recibe la
   direccion: el tamaño es el de SIdBloqueBin, y el bloque se arma en la pila
   sin hacerse dueño de los datos. */
static SId * _SCnjIdLeer ( void * p_vDatos )
{
	SBloque	blqDatos;

	blqDatos.p_byDatos = (byte *) p_vDatos;
	blqDatos.iTam = SIdTamBloqueBin ();
	blqDatos.iLiberar = 0;
	return ( SIdLeerDeBloqueBin ( &blqDatos ) );
}

/* Compara como SId, no como bytes: el orden es el de SIdComparar. */
static int _SCnjIdComparar ( void * p_vVal1, void * p_vVal2 )
{
	int		iRes;
	SId *	p_idVal1;
	SId *	p_idVal2;

	p_idVal1 = _SCnjIdLeer ( p_vVal1 );
	p_idVal2 = _SCnjIdLeer ( p_vVal2 );
	iRes = SIdComparar ( p_idVal1, p_idVal2 );
	if ( iRes == COMP_MENOR )
	{
		iRes = -1;
	}
	else if ( iRes == COMP_MAYOR )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	SIdDestruir ( &p_idVal1 );
	SIdDestruir ( &p_idVal2 );
	return ( iRes );
}
