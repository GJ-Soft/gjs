#include "SConjuntoEnteros.h"

#include "TiposBasicosConfig.h"



static SConjuntoEnteros * _SCnjIntEnvolver ( SConjunto * p_cnjDatos );
static SConjuntoEnteros * _SCnjIntEnvolverExtraidos ( SConjuntoEnteros * p_cnjObj, SConjunto * p_cnjExt );

/* El conjunto compara los datos de sus elementos: dos int. */
static int _SCnjIntComparar ( void * p_vVal1, void * p_vVal2 )
{
	int iVal1;
	int iVal2;
	int iRes;

	iVal1 = *( (int *) p_vVal1 );
	iVal2 = *( (int *) p_vVal2 );
	if ( iVal1 < iVal2 )
	{
		iRes = -1;
	}
	else if ( iVal1 > iVal2 )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

SConjuntoEnteros * SCnjIntCrear ()
{
	return ( _SCnjIntEnvolver ( SCnjCrear ( _SCnjIntComparar ) ) );
}

SConjuntoEnteros * SCnjIntCrearDesdeLista ( SListaEnteros * p_lisValores )
{
	SConjuntoEnteros * p_cnjRes;

	if ( ES_VALIDO ( p_lisValores ) )
	{
		p_cnjRes = _SCnjIntEnvolver ( SCnjCrearDesdeLista ( p_lisValores->p_lisDatos, _SCnjIntComparar ) );
	}
	else
	{
		p_cnjRes = NULL;
	}
	return ( p_cnjRes );
}

SConjuntoEnteros * SCnjIntCrearDesdeVector ( const int * p_iValores, int iNumValores )
{
	SConjuntoEnteros *	p_cnjRes;
	int					iPos;
	int					iError;

	if ( ES_VALIDO ( p_iValores ) )
	{
		if ( iNumValores >= 0 )
		{
			p_cnjRes = SCnjIntCrear ();
			if ( ES_VALIDO ( p_cnjRes ) )
			{
				iError = 0;
				iPos = 0;
				while ( ( iError == 0 ) && ( iPos < iNumValores ) )
				{
					/* Un repetido no es un error: ya esta dentro. */
					if ( SCnjIntExiste ( p_cnjRes, p_iValores [ iPos ] ) == 0 )
					{
						if ( SCnjIntInsertar ( p_cnjRes, p_iValores [ iPos ] ) == 0 )
						{
							iError = 1;
						}
					}
					iPos = iPos + 1;
				}
				if ( iError == 1 )
				{
					SCnjIntDestruir ( &p_cnjRes );
				}
			}
		}
		else
		{
			p_cnjRes = NULL;
		}
	}
	else
	{
		p_cnjRes = NULL;
	}
	return ( p_cnjRes );
}

void SCnjIntDestruir ( SConjuntoEnteros ** p_p_cnjObj )
{
	SConjuntoEnteros * p_cnjObj;

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

int SCnjIntEsValido ( SConjuntoEnteros * p_cnjObj )
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

int SCnjIntNumElementos ( SConjuntoEnteros * p_cnjObj )
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

int SCnjIntEstaVacio ( SConjuntoEnteros * p_cnjObj )
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

int SCnjIntElemento ( SConjuntoEnteros * p_cnjObj, int iElem )
{
	int			iRes;
	SElemento *	p_elmObj;

	if ( ES_VALIDO ( p_cnjObj ) )
	{
		p_elmObj = SCnjElemento ( p_cnjObj->p_cnjDatos, iElem );
		if ( ES_VALIDO ( p_elmObj ) )
		{
			iRes = SElmEntero ( p_elmObj );
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

int SCnjIntInsertar ( SConjuntoEnteros * p_cnjObj, int iDato )
{
	int			iRes;
	SElemento *	p_elmObj;

	if ( ES_VALIDO ( p_cnjObj ) )
	{
		p_elmObj = SElmCrearEntero ();
		if ( ES_VALIDO ( p_elmObj ) )
		{
			if ( SElmEscribirEntero ( p_elmObj, iDato ) == 1 )
			{
				iRes = SCnjInsertarElem ( p_cnjObj->p_cnjDatos, p_elmObj );
			}
			else
			{
				iRes = 0;
			}
			if ( iRes != 1 )
			{
				SElmDestruir ( &p_elmObj );
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

/* El valor no se puede cambiar en su sitio: el orden lo decide el valor. Se
   saca el elemento, se reescribe y se vuelve a meter; si no entra, vuelve con
   el valor que tenia. */
int SCnjIntModificar ( SConjuntoEnteros * p_cnjObj, int iElem, int iDato )
{
	int			iRes;
	int			iAnterior;
	SElemento *	p_elmObj;

	if ( ES_VALIDO ( p_cnjObj ) )
	{
		p_elmObj = SCnjElemento ( p_cnjObj->p_cnjDatos, iElem );
		if ( ES_VALIDO ( p_elmObj ) )
		{
			iAnterior = SElmEntero ( p_elmObj );
			if ( iAnterior == iDato )
			{
				iRes = 1;
			}
			else if ( SCnjIntExiste ( p_cnjObj, iDato ) == 1 )
			{
				iRes = 0;
			}
			else
			{
				p_elmObj = SCnjExtraerElem ( p_cnjObj->p_cnjDatos, iElem );
				SElmEscribirEntero ( p_elmObj, iDato );
				iRes = SCnjInsertarElem ( p_cnjObj->p_cnjDatos, p_elmObj );
				if ( iRes != 1 )
				{
					SElmEscribirEntero ( p_elmObj, iAnterior );
					if ( SCnjInsertarElem ( p_cnjObj->p_cnjDatos, p_elmObj ) != 1 )
					{
						SElmDestruir ( &p_elmObj );
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
	return ( iRes );
}

int SCnjIntEliminar ( SConjuntoEnteros * p_cnjObj, int iElem )
{
	int iRes;

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

int SCnjIntVaciar ( SConjuntoEnteros * p_cnjObj )
{
	int iRes;

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

int SCnjIntExiste ( SConjuntoEnteros * p_cnjObj, int iDato )
{
	int	 iRes;

	if ( ES_VALIDO ( p_cnjObj ) )
	{
		iRes = SCnjExisteExt ( p_cnjObj->p_cnjDatos, (byte *) &iDato );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCnjIntBuscar ( SConjuntoEnteros * p_cnjObj, int iDato )
{
	int	 iRes;

	if ( ES_VALIDO ( p_cnjObj ) )
	{
		iRes = SCnjBuscarExt ( p_cnjObj->p_cnjDatos, (byte *) &iDato );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

/* Ordenado: el minimo es el primero y el maximo el ultimo. */
int SCnjIntMin ( SConjuntoEnteros * p_cnjObj )
{
	int			iRes;
	SElemento *	p_elmObj;

	if ( ES_VALIDO ( p_cnjObj ) )
	{
		p_elmObj = SCnjPrimero ( p_cnjObj->p_cnjDatos );
		if ( ES_VALIDO ( p_elmObj ) )
		{
			iRes = SElmEntero ( p_elmObj );
		}
		else
		{
			iRes = INT_MAX;
		}
	}
	else
	{
		ERROR_ESTABLECER ( ERR_PARAMETROS );
		iRes = 0;
	}
	return ( iRes );
}

int SCnjIntMax ( SConjuntoEnteros * p_cnjObj )
{
	int			iRes;
	SElemento *	p_elmObj;

	if ( ES_VALIDO ( p_cnjObj ) )
	{
		p_elmObj = SCnjUltimo ( p_cnjObj->p_cnjDatos );
		if ( ES_VALIDO ( p_elmObj ) )
		{
			iRes = SElmEntero ( p_elmObj );
		}
		else
		{
			iRes = INT_MIN;
		}
	}
	else
	{
		ERROR_ESTABLECER ( ERR_PARAMETROS );
		iRes = 0;
	}
	return ( iRes );
}

void SCnjIntObtenerParametros ( SConjuntoEnteros * p_cnjObj, int * p_iMin, int * p_iMax, double * p_dMed )
{
	int			iNumElems;
	SElemento *	p_elmObj;

	if ( ES_VALIDO ( p_cnjObj ) )
	{
		if ( ES_VALIDO ( p_iMin ) )
		{
			if ( ES_VALIDO ( p_iMax ) )
			{
				if ( ES_VALIDO ( p_dMed ) )
				{
					*p_iMin = SCnjIntMin ( p_cnjObj );
					*p_iMax = SCnjIntMax ( p_cnjObj );
					*p_dMed = 0.0;
					iNumElems = SCnjIntNumElementos ( p_cnjObj );
					/* Se recorre la CADENA de elementos, no por indice: un barrido
					   por indice seria cuadratico. Igual que en SListaEnteros. */
					p_elmObj = SCnjPrimero ( p_cnjObj->p_cnjDatos );
					while ( ES_VALIDO ( p_elmObj ) )
					{
						*p_dMed = *p_dMed + (double) SElmEntero ( p_elmObj );
						p_elmObj = SElmSucesor ( p_elmObj );
					}
					if ( iNumElems > 0 )
					{
						*p_dMed = *p_dMed / iNumElems;
					}
				}
				else
				{
					ERROR_ESTABLECER ( ERR_PARAMETROS );
				}
			}
			else
			{
				ERROR_ESTABLECER ( ERR_PARAMETROS );
			}
		}
		else
		{
			ERROR_ESTABLECER ( ERR_PARAMETROS );
		}
	}
	else
	{
		ERROR_ESTABLECER ( ERR_PARAMETROS );
	}
}

int SCnjIntDefinidaPositiva ( SConjuntoEnteros * p_cnjObj )
{
	int	 iRes;

	if ( ES_VALIDO ( p_cnjObj ) )
	{
		if ( SCnjIntMin ( p_cnjObj ) > 0 )
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
		ERROR_ESTABLECER ( ERR_PARAMETROS );
		iRes = 0;
	}
	return ( iRes );
}

int SCnjIntSemidefinidaPositiva ( SConjuntoEnteros * p_cnjObj )
{
	int	 iRes;

	if ( ES_VALIDO ( p_cnjObj ) )
	{
		if ( SCnjIntMin ( p_cnjObj ) >= 0 )
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
		ERROR_ESTABLECER ( ERR_PARAMETROS );
		iRes = 0;
	}
	return ( iRes );
}

SConjunto * SCnjIntConjunto ( SConjuntoEnteros * p_cnjObj )
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

SListaOrdenada * SCnjIntLista ( SConjuntoEnteros * p_cnjObj )
{
	SListaOrdenada * p_lisRes;

	if ( ES_VALIDO ( p_cnjObj ) )
	{
		p_lisRes = SCnjLista ( p_cnjObj->p_cnjDatos );
	}
	else
	{
		p_lisRes = NULL;
	}
	return ( p_lisRes );
}

SListaEnteros * SCnjIntListaInt ( SConjuntoEnteros * p_cnjObj )
{
	SListaEnteros *	p_lisRes;
	SLista *		p_lisDatos;

	if ( ES_VALIDO ( p_cnjObj ) )
	{
		p_lisDatos = SLisOrdDuplicarLista ( SCnjIntLista ( p_cnjObj ) );
		p_lisRes = SLisIntEncapsular ( p_lisDatos );
		if ( ES_NULO ( p_lisRes ) )
		{
			SLisDestruir ( &p_lisDatos );
		}
	}
	else
	{
		p_lisRes = NULL;
	}
	return ( p_lisRes );
}

/* Las operaciones con otros conjuntos y listas delegan en las de SConjunto,
   con su misma semantica ( ver Conjuntos.md ). */
int SCnjIntExistenTodos ( SConjuntoEnteros * p_cnjObj, SConjuntoEnteros * p_cnjValores )
{
	int	iRes;

	if ( ES_VALIDO ( p_cnjObj ) )
	{
		if ( ES_VALIDO ( p_cnjValores ) )
		{
			iRes = SCnjExistenTodos ( p_cnjObj->p_cnjDatos, p_cnjValores->p_cnjDatos );
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

int SCnjIntExisteAlguno ( SConjuntoEnteros * p_cnjObj, SConjuntoEnteros * p_cnjValores )
{
	int	iRes;

	if ( ES_VALIDO ( p_cnjObj ) )
	{
		if ( ES_VALIDO ( p_cnjValores ) )
		{
			iRes = SCnjExisteAlguno ( p_cnjObj->p_cnjDatos, p_cnjValores->p_cnjDatos );
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

int SCnjIntExistenTodosLista ( SConjuntoEnteros * p_cnjObj, SListaEnteros * p_lisValores )
{
	int	iRes;

	if ( ES_VALIDO ( p_cnjObj ) )
	{
		if ( ES_VALIDO ( p_lisValores ) )
		{
			iRes = SCnjExistenTodosLista ( p_cnjObj->p_cnjDatos, p_lisValores->p_lisDatos );
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

int SCnjIntExisteAlgunoLista ( SConjuntoEnteros * p_cnjObj, SListaEnteros * p_lisValores )
{
	int	iRes;

	if ( ES_VALIDO ( p_cnjObj ) )
	{
		if ( ES_VALIDO ( p_lisValores ) )
		{
			iRes = SCnjExisteAlgunoLista ( p_cnjObj->p_cnjDatos, p_lisValores->p_lisDatos );
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

/* Eliminar destruye los valores que encuentre. */
int SCnjIntEliminarConjunto ( SConjuntoEnteros * p_cnjObj, SConjuntoEnteros * p_cnjValores )
{
	int	iRes;

	if ( ES_VALIDO ( p_cnjObj ) )
	{
		if ( ES_VALIDO ( p_cnjValores ) )
		{
			iRes = SCnjEliminarConjunto ( p_cnjObj->p_cnjDatos, p_cnjValores->p_cnjDatos );
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

int SCnjIntEliminarLista ( SConjuntoEnteros * p_cnjObj, SListaEnteros * p_lisValores )
{
	int	iRes;

	if ( ES_VALIDO ( p_cnjObj ) )
	{
		if ( ES_VALIDO ( p_lisValores ) )
		{
			iRes = SCnjEliminarLista ( p_cnjObj->p_cnjDatos, p_lisValores->p_lisDatos );
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

int SCnjIntConcatenar ( SConjuntoEnteros * p_cnjObj, SConjuntoEnteros * p_cnjValores )
{
	int	iRes;

	if ( ES_VALIDO ( p_cnjObj ) )
	{
		if ( ES_VALIDO ( p_cnjValores ) )
		{
			iRes = SCnjInsertarConjunto ( p_cnjObj->p_cnjDatos, p_cnjValores->p_cnjDatos );
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

int SCnjIntConcatenarLista ( SConjuntoEnteros * p_cnjObj, SListaEnteros * p_lisValores )
{
	int	iRes;

	if ( ES_VALIDO ( p_cnjObj ) )
	{
		if ( ES_VALIDO ( p_lisValores ) )
		{
			iRes = SCnjInsertarLista ( p_cnjObj->p_cnjDatos, p_lisValores->p_lisDatos );
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

/* Las Extraer MUEVEN los valores a un conjunto nuevo. Si no se puede crear,
   vuelven a p_cnjObj y se devuelve NULL. */
SConjuntoEnteros * SCnjIntExtraerConjunto ( SConjuntoEnteros * p_cnjObj, SConjuntoEnteros * p_cnjValores )
{
	SConjuntoEnteros *	p_cnjRes;

	if ( ES_VALIDO ( p_cnjObj ) )
	{
		if ( ES_VALIDO ( p_cnjValores ) )
		{
			p_cnjRes = _SCnjIntEnvolverExtraidos ( p_cnjObj, SCnjExtraerConjunto ( p_cnjObj->p_cnjDatos, p_cnjValores->p_cnjDatos ) );
		}
		else
		{
			p_cnjRes = NULL;
		}
	}
	else
	{
		p_cnjRes = NULL;
	}
	return ( p_cnjRes );
}

SConjuntoEnteros * SCnjIntExtraerLista ( SConjuntoEnteros * p_cnjObj, SListaEnteros * p_lisValores )
{
	SConjuntoEnteros *	p_cnjRes;

	if ( ES_VALIDO ( p_cnjObj ) )
	{
		if ( ES_VALIDO ( p_lisValores ) )
		{
			p_cnjRes = _SCnjIntEnvolverExtraidos ( p_cnjObj, SCnjExtraerLista ( p_cnjObj->p_cnjDatos, p_lisValores->p_lisDatos ) );
		}
		else
		{
			p_cnjRes = NULL;
		}
	}
	else
	{
		p_cnjRes = NULL;
	}
	return ( p_cnjRes );
}

/* Union, Interseccion y Diferencia crean un conjunto nuevo con COPIAS de los
   valores; si algo falla, NULL. */
SConjuntoEnteros * SCnjIntUnion ( SConjuntoEnteros * p_cnjValores1, SConjuntoEnteros * p_cnjValores2 )
{
	SConjuntoEnteros *	p_cnjRes;

	if ( ES_VALIDO ( p_cnjValores1 ) )
	{
		if ( ES_VALIDO ( p_cnjValores2 ) )
		{
			p_cnjRes = _SCnjIntEnvolver ( SCnjUnion ( p_cnjValores1->p_cnjDatos, p_cnjValores2->p_cnjDatos ) );
		}
		else
		{
			p_cnjRes = NULL;
		}
	}
	else
	{
		p_cnjRes = NULL;
	}
	return ( p_cnjRes );
}

SConjuntoEnteros * SCnjIntInterseccion ( SConjuntoEnteros * p_cnjValores1, SConjuntoEnteros * p_cnjValores2 )
{
	SConjuntoEnteros *	p_cnjRes;

	if ( ES_VALIDO ( p_cnjValores1 ) )
	{
		if ( ES_VALIDO ( p_cnjValores2 ) )
		{
			p_cnjRes = _SCnjIntEnvolver ( SCnjInterseccion ( p_cnjValores1->p_cnjDatos, p_cnjValores2->p_cnjDatos ) );
		}
		else
		{
			p_cnjRes = NULL;
		}
	}
	else
	{
		p_cnjRes = NULL;
	}
	return ( p_cnjRes );
}

SConjuntoEnteros * SCnjIntDiferencia ( SConjuntoEnteros * p_cnjValores1, SConjuntoEnteros * p_cnjValores2 )
{
	SConjuntoEnteros *	p_cnjRes;

	if ( ES_VALIDO ( p_cnjValores1 ) )
	{
		if ( ES_VALIDO ( p_cnjValores2 ) )
		{
			p_cnjRes = _SCnjIntEnvolver ( SCnjDiferencia ( p_cnjValores1->p_cnjDatos, p_cnjValores2->p_cnjDatos ) );
		}
		else
		{
			p_cnjRes = NULL;
		}
	}
	else
	{
		p_cnjRes = NULL;
	}
	return ( p_cnjRes );
}

SConjuntoEnteros * SCnjIntUnionLista ( SConjuntoEnteros * p_cnjValores1, SListaEnteros * p_lisValores2 )
{
	SConjuntoEnteros *	p_cnjRes;

	if ( ES_VALIDO ( p_cnjValores1 ) )
	{
		if ( ES_VALIDO ( p_lisValores2 ) )
		{
			p_cnjRes = _SCnjIntEnvolver ( SCnjUnionLista ( p_cnjValores1->p_cnjDatos, p_lisValores2->p_lisDatos ) );
		}
		else
		{
			p_cnjRes = NULL;
		}
	}
	else
	{
		p_cnjRes = NULL;
	}
	return ( p_cnjRes );
}

SConjuntoEnteros * SCnjIntInterseccionLista ( SConjuntoEnteros * p_cnjValores1, SListaEnteros * p_lisValores2 )
{
	SConjuntoEnteros *	p_cnjRes;

	if ( ES_VALIDO ( p_cnjValores1 ) )
	{
		if ( ES_VALIDO ( p_lisValores2 ) )
		{
			p_cnjRes = _SCnjIntEnvolver ( SCnjInterseccionLista ( p_cnjValores1->p_cnjDatos, p_lisValores2->p_lisDatos ) );
		}
		else
		{
			p_cnjRes = NULL;
		}
	}
	else
	{
		p_cnjRes = NULL;
	}
	return ( p_cnjRes );
}

SConjuntoEnteros * SCnjIntDiferenciaLista ( SConjuntoEnteros * p_cnjValores1, SListaEnteros * p_lisValores2 )
{
	SConjuntoEnteros *	p_cnjRes;

	if ( ES_VALIDO ( p_cnjValores1 ) )
	{
		if ( ES_VALIDO ( p_lisValores2 ) )
		{
			p_cnjRes = _SCnjIntEnvolver ( SCnjDiferenciaLista ( p_cnjValores1->p_cnjDatos, p_lisValores2->p_lisDatos ) );
		}
		else
		{
			p_cnjRes = NULL;
		}
	}
	else
	{
		p_cnjRes = NULL;
	}
	return ( p_cnjRes );
}

/* Envuelve un conjunto ya creado; si no hay, no es valido o no se puede
   envolver, NULL y el conjunto se destruye. */
static SConjuntoEnteros * _SCnjIntEnvolver ( SConjunto * p_cnjDatos )
{
	SConjuntoEnteros * p_cnjRes;

	if ( SCnjEsValido ( p_cnjDatos ) == 1 )
	{
		p_cnjRes = (SConjuntoEnteros *) MemReservar ( sizeof ( SConjuntoEnteros ) );
		if ( ES_VALIDO ( p_cnjRes ) )
		{
			p_cnjRes->p_cnjDatos = p_cnjDatos;
		}
		else
		{
			SCnjDestruir ( &p_cnjDatos );
		}
	}
	else
	{
		SCnjDestruir ( &p_cnjDatos );
		p_cnjRes = NULL;
	}
	return ( p_cnjRes );
}

/* Envuelve lo que haya sacado una Extraer de SConjunto. Si no se puede, los
   valores vuelven a p_cnjObj: no se pierden. */
static SConjuntoEnteros * _SCnjIntEnvolverExtraidos ( SConjuntoEnteros * p_cnjObj, SConjunto * p_cnjExt )
{
	SConjuntoEnteros * p_cnjRes;

	if ( ES_VALIDO ( p_cnjExt ) )
	{
		p_cnjRes = (SConjuntoEnteros *) MemReservar ( sizeof ( SConjuntoEnteros ) );
		if ( ES_VALIDO ( p_cnjRes ) )
		{
			p_cnjRes->p_cnjDatos = p_cnjExt;
		}
		else
		{
			SLisOrdInsertarListaOrd ( SCnjLista ( p_cnjObj->p_cnjDatos ), SCnjLista ( p_cnjExt ) );
			SCnjDestruir ( &p_cnjExt );
		}
	}
	else
	{
		p_cnjRes = NULL;
	}
	return ( p_cnjRes );
}
