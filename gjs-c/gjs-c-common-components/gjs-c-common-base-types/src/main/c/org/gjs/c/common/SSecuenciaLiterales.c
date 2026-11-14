#include "SSecuenciaLiterales.h"

#include "TiposBasicosConfig.h"


extern int _SLisLitSonIguales ( byte * p_byLiteral1, byte * p_byLiteral2 );
extern byte * _SLisLitDuplicar ( byte * p_byLiteral );
extern SListaPtr * _SLisLitExtraerUnicos ( SListaPtr * p_lisDatos, int iOrdenar );
extern int _SLisLitTieneRepetidos ( SListaPtr * p_lisDatos );

static SSecuenciaLiterales * _SSecLitEnvolver ( SSecuenciaPtr * p_secDatos );
static SSecuenciaLiterales * _SSecLitEnvolverExtraidos ( SSecuenciaLiterales * p_secObj, SSecuenciaPtr * p_secExt );



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

/* Lista nueva con COPIAS de las cadenas, en el mismo orden. */
SListaLiterales * SSecLitListaLit ( SSecuenciaLiterales * p_secObj )
{
	SListaLiterales *	p_lisRes;
	SListaPtr *			p_lisDatos;

	if ( ES_VALIDO ( p_secObj ) )
	{
		p_lisDatos = SLispDuplicarExt ( SSecLitLista ( p_secObj ), _SLisLitDuplicar );
		p_lisRes = SLisLitEncapsular ( p_lisDatos );
		if ( ES_NULO ( p_lisRes ) )
		{
			SLispDestruir ( &p_lisDatos );
		}
	}
	else
	{
		p_lisRes = NULL;
	}
	return ( p_lisRes );
}


/* Las operaciones con otras secuencias y listas de literales comparan el
   contenido de las cadenas y delegan en las Ext de SSecuenciaPtr, con su
   misma semantica ( ver Secuencias.md ). */
int SSecLitExistenTodos ( SSecuenciaLiterales * p_secObj, SSecuenciaLiterales * p_secValores )
{
	int	iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		if ( ES_VALIDO ( p_secValores ) )
		{
			iRes = SSecpExistenTodosExt ( p_secObj->p_secDatos, p_secValores->p_secDatos, _SLisLitSonIguales );
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

int SSecLitExisteAlguno ( SSecuenciaLiterales * p_secObj, SSecuenciaLiterales * p_secValores )
{
	int	iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		if ( ES_VALIDO ( p_secValores ) )
		{
			iRes = SSecpExisteAlgunoExt ( p_secObj->p_secDatos, p_secValores->p_secDatos, _SLisLitSonIguales );
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

int SSecLitExistenTodosLista ( SSecuenciaLiterales * p_secObj, SListaLiterales * p_lisValores )
{
	int	iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		if ( ES_VALIDO ( p_lisValores ) )
		{
			iRes = SSecpExistenTodosListaExt ( p_secObj->p_secDatos, p_lisValores->p_lisDatos, _SLisLitSonIguales );
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

int SSecLitExisteAlgunoLista ( SSecuenciaLiterales * p_secObj, SListaLiterales * p_lisValores )
{
	int	iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		if ( ES_VALIDO ( p_lisValores ) )
		{
			iRes = SSecpExisteAlgunoListaExt ( p_secObj->p_secDatos, p_lisValores->p_lisDatos, _SLisLitSonIguales );
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

/* Concatenar anade al final COPIAS de las cadenas, como todo lo que entra en
   la secuencia: los valores no se tocan. */
int SSecLitConcatenar ( SSecuenciaLiterales * p_secObj, SSecuenciaLiterales * p_secValores )
{
	int	iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		if ( ES_VALIDO ( p_secValores ) )
		{
			iRes = SSecpConcatenarDupExt ( p_secObj->p_secDatos, p_secValores->p_secDatos, _SLisLitDuplicar );
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

int SSecLitConcatenarLista ( SSecuenciaLiterales * p_secObj, SListaLiterales * p_lisValores )
{
	int	iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		if ( ES_VALIDO ( p_lisValores ) )
		{
			iRes = SSecpConcatenarListaDupExt ( p_secObj->p_secDatos, p_lisValores->p_lisDatos, _SLisLitDuplicar );
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

int SSecLitEliminarSecuencia ( SSecuenciaLiterales * p_secObj, SSecuenciaLiterales * p_secValores )
{
	int	iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		if ( ES_VALIDO ( p_secValores ) )
		{
			iRes = SSecpEliminarSecuenciaExt ( p_secObj->p_secDatos, p_secValores->p_secDatos, _SLisLitSonIguales );
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

int SSecLitEliminarLista ( SSecuenciaLiterales * p_secObj, SListaLiterales * p_lisValores )
{
	int	iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		if ( ES_VALIDO ( p_lisValores ) )
		{
			iRes = SSecpEliminarListaExt ( p_secObj->p_secDatos, p_lisValores->p_lisDatos, _SLisLitSonIguales );
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

/* Las Extraer MUEVEN las cadenas a una secuencia nueva. Si no se puede
   crear, vuelven al final de p_secObj y se devuelve NULL. */
SSecuenciaLiterales * SSecLitExtraerSecuencia ( SSecuenciaLiterales * p_secObj, SSecuenciaLiterales * p_secValores )
{
	SSecuenciaLiterales *	p_secRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		if ( ES_VALIDO ( p_secValores ) )
		{
			p_secRes = _SSecLitEnvolverExtraidos ( p_secObj, SSecpExtraerSecuenciaExt ( p_secObj->p_secDatos, p_secValores->p_secDatos, _SLisLitSonIguales ) );
		}
		else
		{
			p_secRes = NULL;
		}
	}
	else
	{
		p_secRes = NULL;
	}
	return ( p_secRes );
}

SSecuenciaLiterales * SSecLitExtraerLista ( SSecuenciaLiterales * p_secObj, SListaLiterales * p_lisValores )
{
	SSecuenciaLiterales *	p_secRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		if ( ES_VALIDO ( p_lisValores ) )
		{
			p_secRes = _SSecLitEnvolverExtraidos ( p_secObj, SSecpExtraerListaExt ( p_secObj->p_secDatos, p_lisValores->p_lisDatos, _SLisLitSonIguales ) );
		}
		else
		{
			p_secRes = NULL;
		}
	}
	else
	{
		p_secRes = NULL;
	}
	return ( p_secRes );
}

/* Union, Interseccion y Diferencia crean una secuencia nueva con COPIAS de
   las cadenas, comparando su contenido; si algo falla, NULL. */
SSecuenciaLiterales * SSecLitUnion ( SSecuenciaLiterales * p_secValores1, SSecuenciaLiterales * p_secValores2 )
{
	SSecuenciaLiterales *	p_secRes;

	if ( ES_VALIDO ( p_secValores1 ) )
	{
		if ( ES_VALIDO ( p_secValores2 ) )
		{
			p_secRes = _SSecLitEnvolver ( SSecpUnionExt ( p_secValores1->p_secDatos, p_secValores2->p_secDatos, _SLisLitDuplicar ) );
		}
		else
		{
			p_secRes = NULL;
		}
	}
	else
	{
		p_secRes = NULL;
	}
	return ( p_secRes );
}

SSecuenciaLiterales * SSecLitInterseccion ( SSecuenciaLiterales * p_secValores1, SSecuenciaLiterales * p_secValores2 )
{
	SSecuenciaLiterales *	p_secRes;

	if ( ES_VALIDO ( p_secValores1 ) )
	{
		if ( ES_VALIDO ( p_secValores2 ) )
		{
			p_secRes = _SSecLitEnvolver ( SSecpInterseccionExt ( p_secValores1->p_secDatos, p_secValores2->p_secDatos, _SLisLitSonIguales, _SLisLitDuplicar ) );
		}
		else
		{
			p_secRes = NULL;
		}
	}
	else
	{
		p_secRes = NULL;
	}
	return ( p_secRes );
}

SSecuenciaLiterales * SSecLitDiferencia ( SSecuenciaLiterales * p_secValores1, SSecuenciaLiterales * p_secValores2 )
{
	SSecuenciaLiterales *	p_secRes;

	if ( ES_VALIDO ( p_secValores1 ) )
	{
		if ( ES_VALIDO ( p_secValores2 ) )
		{
			p_secRes = _SSecLitEnvolver ( SSecpDiferenciaExt ( p_secValores1->p_secDatos, p_secValores2->p_secDatos, _SLisLitSonIguales, _SLisLitDuplicar ) );
		}
		else
		{
			p_secRes = NULL;
		}
	}
	else
	{
		p_secRes = NULL;
	}
	return ( p_secRes );
}

SSecuenciaLiterales * SSecLitUnionLista ( SSecuenciaLiterales * p_secValores1, SListaLiterales * p_lisValores2 )
{
	SSecuenciaLiterales *	p_secRes;

	if ( ES_VALIDO ( p_secValores1 ) )
	{
		if ( ES_VALIDO ( p_lisValores2 ) )
		{
			p_secRes = _SSecLitEnvolver ( SSecpUnionListaExt ( p_secValores1->p_secDatos, p_lisValores2->p_lisDatos, _SLisLitDuplicar ) );
		}
		else
		{
			p_secRes = NULL;
		}
	}
	else
	{
		p_secRes = NULL;
	}
	return ( p_secRes );
}

SSecuenciaLiterales * SSecLitInterseccionLista ( SSecuenciaLiterales * p_secValores1, SListaLiterales * p_lisValores2 )
{
	SSecuenciaLiterales *	p_secRes;

	if ( ES_VALIDO ( p_secValores1 ) )
	{
		if ( ES_VALIDO ( p_lisValores2 ) )
		{
			p_secRes = _SSecLitEnvolver ( SSecpInterseccionListaExt ( p_secValores1->p_secDatos, p_lisValores2->p_lisDatos, _SLisLitSonIguales, _SLisLitDuplicar ) );
		}
		else
		{
			p_secRes = NULL;
		}
	}
	else
	{
		p_secRes = NULL;
	}
	return ( p_secRes );
}

SSecuenciaLiterales * SSecLitDiferenciaLista ( SSecuenciaLiterales * p_secValores1, SListaLiterales * p_lisValores2 )
{
	SSecuenciaLiterales *	p_secRes;

	if ( ES_VALIDO ( p_secValores1 ) )
	{
		if ( ES_VALIDO ( p_lisValores2 ) )
		{
			p_secRes = _SSecLitEnvolver ( SSecpDiferenciaListaExt ( p_secValores1->p_secDatos, p_lisValores2->p_lisDatos, _SLisLitSonIguales, _SLisLitDuplicar ) );
		}
		else
		{
			p_secRes = NULL;
		}
	}
	else
	{
		p_secRes = NULL;
	}
	return ( p_secRes );
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

/* Envuelve lo que haya sacado una Extraer de SSecuenciaPtr. Si no se puede,
   las cadenas vuelven al final de p_secObj: no se pierden. */
static SSecuenciaLiterales * _SSecLitEnvolverExtraidos ( SSecuenciaLiterales * p_secObj, SSecuenciaPtr * p_secExt )
{
	SSecuenciaLiterales * p_secRes;

	if ( ES_VALIDO ( p_secExt ) )
	{
		p_secRes = (SSecuenciaLiterales *) MemReservar ( sizeof ( SSecuenciaLiterales ) );
		if ( ES_VALIDO ( p_secRes ) )
		{
			p_secRes->p_secDatos = p_secExt;
		}
		else
		{
			SSecpConcatenar ( p_secObj->p_secDatos, p_secExt );
			SSecpDestruir ( &p_secExt );
		}
	}
	else
	{
		p_secRes = NULL;
	}
	return ( p_secRes );
}


