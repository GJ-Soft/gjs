#include "SConjuntoLiterales.h"
          
#include "TiposBasicosConfig.h"


extern byte * _SLisLitDuplicar ( byte * p_byLiteral );

static SConjuntoLiterales * _SCnjLitEnvolver ( SConjuntoPtr * p_cnjDatos );
static SConjuntoLiterales * _SCnjLitEnvolverExtraidos ( SConjuntoLiterales * p_cnjObj, SConjuntoPtr * p_cnjExt );


int _CadComparar ( void * p_vVal1, void * p_vVal2 )
{
    int 	iRes;
    char * 	p_cVal1 = (char *) p_vVal1;
    char * 	p_cVal2 = (char *) p_vVal2;
    iRes = CadComparar ( p_cVal1, p_cVal2 );
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
    return ( iRes );
}


SConjuntoLiterales * SCnjLitCrear ()
{
	SConjuntoLiterales * p_cnjObj;
	
	p_cnjObj = (SConjuntoLiterales *) MemReservar ( sizeof ( SConjuntoLiterales ) );
	if ( ES_VALIDO ( p_cnjObj ) )
	{
		p_cnjObj->p_cnjDatos = SCnjpCrear ( _CadComparar );
		SCnjpActivarLiberacionMemoria ( p_cnjObj->p_cnjDatos );
	}
	return ( p_cnjObj );
}

void SCnjLitDestruir ( SConjuntoLiterales ** p_p_cnjObj )
{
	SConjuntoLiterales * p_cnjObj;
	
	if ( ES_VALIDO ( p_p_cnjObj ) )
	{
		p_cnjObj = *p_p_cnjObj;

		if ( ES_VALIDO ( p_cnjObj ) )
		{
			SCnjpDestruir ( &(p_cnjObj->p_cnjDatos) );
			MemLiberar ( (void **) p_p_cnjObj );
		}
	}
}

int SCnjLitEsValido ( SConjuntoLiterales * p_cnjObj )
{
	int iRes;

	if ( ES_VALIDO ( p_cnjObj ) )
	{
		iRes = SCnjpEsValido ( p_cnjObj->p_cnjDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCnjLitEstaVacio ( SConjuntoLiterales * p_cnjObj )
{
	int iRes;

	if ( ES_VALIDO ( p_cnjObj ) )
	{
		iRes = SCnjpEstaVacio ( p_cnjObj->p_cnjDatos );
	}
	else
	{
		iRes = 1;
	}
	return ( iRes );
}

int SCnjLitNumElementos ( SConjuntoLiterales * p_cnjObj )
{
	int iRes;

	if ( ES_VALIDO ( p_cnjObj ) )
	{
		iRes = SCnjpNumElementos ( p_cnjObj->p_cnjDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

char * SCnjLitElemento ( SConjuntoLiterales * p_cnjObj, int iElem )
{
	char *	p_cRes;

	if ( ES_VALIDO ( p_cnjObj ) )
	{
		p_cRes = (char *) SCnjpElemento ( p_cnjObj->p_cnjDatos, iElem );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

char * SCnjLitPrimero ( SConjuntoLiterales * p_cnjObj )
{
	char * p_cRes;

	if ( ES_VALIDO ( p_cnjObj ) )
	{
		p_cRes = (char *) SCnjpPrimero ( p_cnjObj->p_cnjDatos );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

char * SCnjLitUltimo ( SConjuntoLiterales * p_cnjObj )
{
	char * p_cRes;

	if ( ES_VALIDO ( p_cnjObj ) )
	{
		p_cRes = (char *) SCnjpUltimo ( p_cnjObj->p_cnjDatos );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

int SCnjLitPosicion ( SConjuntoLiterales * p_cnjObj, const char * p_cDato )
{
	int iRes;

	if ( ES_VALIDO ( p_cnjObj ) )
	{
		iRes = SCnjpPosicion ( p_cnjObj->p_cnjDatos, (byte *) p_cDato );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int SCnjLitInsertar ( SConjuntoLiterales * p_cnjObj, const char * p_cDato )
{
	int		iRes;
	char *	p_cElem;

	if ( ES_VALIDO ( p_cnjObj ) && ES_VALIDO ( p_cDato ) )
	{
		p_cElem = CadDuplicar ( p_cDato );
		if ( ES_VALIDO ( p_cElem ) )
		{
			iRes = SCnjpInsertarElem ( p_cnjObj->p_cnjDatos, (byte *) p_cElem );
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

int SCnjLitEliminar ( SConjuntoLiterales * p_cnjObj, int iElem )
{
	int iRes;

	if ( ES_VALIDO ( p_cnjObj ) )
	{
		iRes = SCnjpEliminarElem ( p_cnjObj->p_cnjDatos, iElem );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCnjLitVaciar ( SConjuntoLiterales * p_cnjObj )
{
	int iRes;

	if ( ES_VALIDO ( p_cnjObj ) )
	{
		iRes = SCnjpVaciar ( p_cnjObj->p_cnjDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCnjLitExiste ( SConjuntoLiterales * p_cnjObj, const char * p_cDato )
{
	int iRes;

	if ( ES_VALIDO ( p_cnjObj ) ) 
	{
		iRes = SCnjpExiste ( p_cnjObj->p_cnjDatos, (byte *) p_cDato );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCnjLitBuscar ( SConjuntoLiterales * p_cnjObj, const char * p_cDato )
{
	int iRes;
	
	if ( ES_VALIDO ( p_cnjObj ) ) 
	{
		iRes = SCnjpBuscar ( p_cnjObj->p_cnjDatos, (byte *) p_cDato );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

SConjuntoPtr * SCnjLitConjunto ( SConjuntoLiterales * p_cnjObj )
{
	SConjuntoPtr * p_cnjRes;

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

SListaOrdenadaPtr * SCnjLitLista ( SConjuntoLiterales * p_cnjObj )
{
	SListaOrdenadaPtr * p_lisRes;

	if ( ES_VALIDO ( p_cnjObj ) )
	{
		p_lisRes = SCnjpLista ( p_cnjObj->p_cnjDatos );
	}
	else
	{
		p_lisRes = NULL;
	}
	return ( p_lisRes );
}

/* Las operaciones con otros conjuntos y listas de literales delegan en las
   de SConjuntoPtr, con su misma semantica ( ver Conjuntos.md ): la igualdad
   la decide la comparacion de cadenas del conjunto. */
int SCnjLitExistenTodos ( SConjuntoLiterales * p_cnjObj, SConjuntoLiterales * p_cnjValores )
{
	int	iRes;

	if ( ES_VALIDO ( p_cnjObj ) )
	{
		if ( ES_VALIDO ( p_cnjValores ) )
		{
			iRes = SCnjpExistenTodos ( p_cnjObj->p_cnjDatos, p_cnjValores->p_cnjDatos );
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

int SCnjLitExisteAlguno ( SConjuntoLiterales * p_cnjObj, SConjuntoLiterales * p_cnjValores )
{
	int	iRes;

	if ( ES_VALIDO ( p_cnjObj ) )
	{
		if ( ES_VALIDO ( p_cnjValores ) )
		{
			iRes = SCnjpExisteAlguno ( p_cnjObj->p_cnjDatos, p_cnjValores->p_cnjDatos );
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

int SCnjLitExistenTodosLista ( SConjuntoLiterales * p_cnjObj, SListaLiterales * p_lisValores )
{
	int	iRes;

	if ( ES_VALIDO ( p_cnjObj ) )
	{
		if ( ES_VALIDO ( p_lisValores ) )
		{
			iRes = SCnjpExistenTodosLista ( p_cnjObj->p_cnjDatos, p_lisValores->p_lisDatos );
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

int SCnjLitExisteAlgunoLista ( SConjuntoLiterales * p_cnjObj, SListaLiterales * p_lisValores )
{
	int	iRes;

	if ( ES_VALIDO ( p_cnjObj ) )
	{
		if ( ES_VALIDO ( p_lisValores ) )
		{
			iRes = SCnjpExisteAlgunoLista ( p_cnjObj->p_cnjDatos, p_lisValores->p_lisDatos );
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

/* Concatenar inserta COPIAS de las cadenas que no esten ya; las demas se
   ignoran. Los valores no se tocan. */
int SCnjLitConcatenarConjunto ( SConjuntoLiterales * p_cnjObj, SConjuntoLiterales * p_cnjValores )
{
	int	iRes;

	if ( ES_VALIDO ( p_cnjObj ) )
	{
		if ( ES_VALIDO ( p_cnjValores ) )
		{
			iRes = SCnjpInsertarExt ( p_cnjObj->p_cnjDatos, p_cnjValores->p_cnjDatos, _SLisLitDuplicar );
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

int SCnjLitConcatenarLista ( SConjuntoLiterales * p_cnjObj, SListaLiterales * p_lisValores )
{
	int	iRes;

	if ( ES_VALIDO ( p_cnjObj ) )
	{
		if ( ES_VALIDO ( p_lisValores ) )
		{
			iRes = SCnjpInsertarListaExt ( p_cnjObj->p_cnjDatos, p_lisValores->p_lisDatos, _SLisLitDuplicar );
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

int SCnjLitEliminarConjunto ( SConjuntoLiterales * p_cnjObj, SConjuntoLiterales * p_cnjValores )
{
	int	iRes;

	if ( ES_VALIDO ( p_cnjObj ) )
	{
		if ( ES_VALIDO ( p_cnjValores ) )
		{
			iRes = SCnjpEliminarConjunto ( p_cnjObj->p_cnjDatos, p_cnjValores->p_cnjDatos );
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

int SCnjLitEliminarLista ( SConjuntoLiterales * p_cnjObj, SListaLiterales * p_lisValores )
{
	int	iRes;

	if ( ES_VALIDO ( p_cnjObj ) )
	{
		if ( ES_VALIDO ( p_lisValores ) )
		{
			iRes = SCnjpEliminarLista ( p_cnjObj->p_cnjDatos, p_lisValores->p_lisDatos );
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

/* Las Extraer MUEVEN las cadenas a un conjunto nuevo. Si no se puede crear,
   vuelven a p_cnjObj y se devuelve NULL. */
SConjuntoLiterales * SCnjLitExtraerConjunto ( SConjuntoLiterales * p_cnjObj, SConjuntoLiterales * p_cnjValores )
{
	SConjuntoLiterales *	p_cnjRes;

	if ( ES_VALIDO ( p_cnjObj ) )
	{
		if ( ES_VALIDO ( p_cnjValores ) )
		{
			p_cnjRes = _SCnjLitEnvolverExtraidos ( p_cnjObj, SCnjpExtraerConjunto ( p_cnjObj->p_cnjDatos, p_cnjValores->p_cnjDatos ) );
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

SConjuntoLiterales * SCnjLitExtraerLista ( SConjuntoLiterales * p_cnjObj, SListaLiterales * p_lisValores )
{
	SConjuntoLiterales *	p_cnjRes;

	if ( ES_VALIDO ( p_cnjObj ) )
	{
		if ( ES_VALIDO ( p_lisValores ) )
		{
			p_cnjRes = _SCnjLitEnvolverExtraidos ( p_cnjObj, SCnjpExtraerLista ( p_cnjObj->p_cnjDatos, p_lisValores->p_lisDatos ) );
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

/* Union, Interseccion y Diferencia crean un conjunto nuevo con COPIAS de
   las cadenas; si algo falla, NULL. */
SConjuntoLiterales * SCnjLitUnion ( SConjuntoLiterales * p_cnjValores1, SConjuntoLiterales * p_cnjValores2 )
{
	SConjuntoLiterales *	p_cnjRes;

	if ( ES_VALIDO ( p_cnjValores1 ) )
	{
		if ( ES_VALIDO ( p_cnjValores2 ) )
		{
			p_cnjRes = _SCnjLitEnvolver ( SCnjpUnionExt ( p_cnjValores1->p_cnjDatos, p_cnjValores2->p_cnjDatos, _SLisLitDuplicar ) );
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

SConjuntoLiterales * SCnjLitInterseccion ( SConjuntoLiterales * p_cnjValores1, SConjuntoLiterales * p_cnjValores2 )
{
	SConjuntoLiterales *	p_cnjRes;

	if ( ES_VALIDO ( p_cnjValores1 ) )
	{
		if ( ES_VALIDO ( p_cnjValores2 ) )
		{
			p_cnjRes = _SCnjLitEnvolver ( SCnjpInterseccionExt ( p_cnjValores1->p_cnjDatos, p_cnjValores2->p_cnjDatos, _SLisLitDuplicar ) );
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

SConjuntoLiterales * SCnjLitDiferencia ( SConjuntoLiterales * p_cnjValores1, SConjuntoLiterales * p_cnjValores2 )
{
	SConjuntoLiterales *	p_cnjRes;

	if ( ES_VALIDO ( p_cnjValores1 ) )
	{
		if ( ES_VALIDO ( p_cnjValores2 ) )
		{
			p_cnjRes = _SCnjLitEnvolver ( SCnjpDiferenciaExt ( p_cnjValores1->p_cnjDatos, p_cnjValores2->p_cnjDatos, _SLisLitDuplicar ) );
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

SConjuntoLiterales * SCnjLitUnionLista ( SConjuntoLiterales * p_cnjValores1, SListaLiterales * p_lisValores2 )
{
	SConjuntoLiterales *	p_cnjRes;

	if ( ES_VALIDO ( p_cnjValores1 ) )
	{
		if ( ES_VALIDO ( p_lisValores2 ) )
		{
			p_cnjRes = _SCnjLitEnvolver ( SCnjpUnionListaExt ( p_cnjValores1->p_cnjDatos, p_lisValores2->p_lisDatos, _SLisLitDuplicar ) );
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

SConjuntoLiterales * SCnjLitInterseccionLista ( SConjuntoLiterales * p_cnjValores1, SListaLiterales * p_lisValores2 )
{
	SConjuntoLiterales *	p_cnjRes;

	if ( ES_VALIDO ( p_cnjValores1 ) )
	{
		if ( ES_VALIDO ( p_lisValores2 ) )
		{
			p_cnjRes = _SCnjLitEnvolver ( SCnjpInterseccionListaExt ( p_cnjValores1->p_cnjDatos, p_lisValores2->p_lisDatos, _SLisLitDuplicar ) );
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

SConjuntoLiterales * SCnjLitDiferenciaLista ( SConjuntoLiterales * p_cnjValores1, SListaLiterales * p_lisValores2 )
{
	SConjuntoLiterales *	p_cnjRes;

	if ( ES_VALIDO ( p_cnjValores1 ) )
	{
		if ( ES_VALIDO ( p_lisValores2 ) )
		{
			p_cnjRes = _SCnjLitEnvolver ( SCnjpDiferenciaListaExt ( p_cnjValores1->p_cnjDatos, p_lisValores2->p_lisDatos, _SLisLitDuplicar ) );
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

/* Envuelve un conjunto ya creado; si no hay o no se puede envolver, NULL y el
   conjunto se destruye. */
static SConjuntoLiterales * _SCnjLitEnvolver ( SConjuntoPtr * p_cnjDatos )
{
	SConjuntoLiterales * p_cnjRes;

	if ( ES_VALIDO ( p_cnjDatos ) )
	{
		p_cnjRes = (SConjuntoLiterales *) MemReservar ( sizeof ( SConjuntoLiterales ) );
		if ( ES_VALIDO ( p_cnjRes ) )
		{
			p_cnjRes->p_cnjDatos = p_cnjDatos;
		}
		else
		{
			SCnjpDestruir ( &p_cnjDatos );
		}
	}
	else
	{
		p_cnjRes = NULL;
	}
	return ( p_cnjRes );
}

/* Envuelve lo que haya sacado una Extraer de SConjuntoPtr. Si no se puede,
   las cadenas vuelven a p_cnjObj: no se pierden. */
static SConjuntoLiterales * _SCnjLitEnvolverExtraidos ( SConjuntoLiterales * p_cnjObj, SConjuntoPtr * p_cnjExt )
{
	SConjuntoLiterales * p_cnjRes;

	if ( ES_VALIDO ( p_cnjExt ) )
	{
		p_cnjRes = (SConjuntoLiterales *) MemReservar ( sizeof ( SConjuntoLiterales ) );
		if ( ES_VALIDO ( p_cnjRes ) )
		{
			p_cnjRes->p_cnjDatos = p_cnjExt;
		}
		else
		{
			SLispOrdInsertarListaOrd ( SCnjpLista ( p_cnjObj->p_cnjDatos ), SCnjpLista ( p_cnjExt ) );
			SCnjpDestruir ( &p_cnjExt );
		}
	}
	else
	{
		p_cnjRes = NULL;
	}
	return ( p_cnjRes );
}
