#include "SListaLiterales.h"

#include "TiposBasicosConfig.h"


static SListaLiterales * _SLisLitEnvolver ( SListaPtr * p_lisDatos );


/* Igualdad y copia de literales para las Ext de SListaPtr: CadComparar y
   CadDuplicar, que reserva con MemReservar y se libera con MemLiberar. */
int _SLisLitSonIguales ( byte * p_byLiteral1, byte * p_byLiteral2 )
{
	int iRes;

	if ( CadComparar ( (char *) p_byLiteral1, (char *) p_byLiteral2 ) == COMP_IGUAL )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

byte * _SLisLitDuplicar ( byte * p_byLiteral )
{
	return ( (byte *) CadDuplicar ( (const char *) p_byLiteral ) );
}


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

	if ( ES_VALIDO ( p_lisObj ) )
	{
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

int SLisLitEstaPosicionada ( SListaLiterales * p_lisObj )
{
	int iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iRes = SLispEstaPosicionada ( p_lisObj->p_lisDatos );
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
	int		iRes;

	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		// NOTA: El elemento ya se libera automaticamente
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

	if ( SLisLitBuscar ( p_lisObj, p_cDatos ) >= 0 )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

/* Busquedas: comparan el CONTENIDO con CadComparar y delegan en las Ext de
   SListaPtr. Repeticiones: cuantas iguales hay, 0 si ninguna. Buscar es
   BuscarPrimero: la posicion de la primera igual, o -1. BuscarSiguiente busca
   DETRAS de iPos: con -1, desde el principio. */
int SLisLitRepeticiones ( SListaLiterales * p_lisObj, const char * p_cDatos )
{
	int	iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iRes = SLispRepeticionesExt ( p_lisObj->p_lisDatos, (byte *) p_cDatos, _SLisLitSonIguales );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLisLitBuscar ( SListaLiterales * p_lisObj, const char * p_cDatos )
{
	return ( SLisLitBuscarPrimero ( p_lisObj, p_cDatos ) );
}

int SLisLitBuscarPrimero ( SListaLiterales * p_lisObj, const char * p_cDatos )
{
	return ( SLisLitBuscarSiguiente ( p_lisObj, p_cDatos, -1 ) );
}

int SLisLitBuscarSiguiente ( SListaLiterales * p_lisObj, const char * p_cDatos, int iPos )
{
	int	iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iRes = SLispBuscarSiguienteExt ( p_lisObj->p_lisDatos, (byte *) p_cDatos, iPos, _SLisLitSonIguales );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

/* Lista nueva con COPIAS de las cadenas distintas de p_lisDatos: en el orden
   de su primera aparicion o, con iOrdenar distinto de 0, ordenadas con
   CadComparar ( por bytes ). Compartida con SSecuenciaLiterales. Si falla una
   copia o una insercion, NULL y ERR_GENERAL_OPERATIVO, como en las de enteros. */
SListaPtr * _SLisLitExtraerUnicos ( SListaPtr * p_lisDatos, int iOrdenar )
{
	SListaPtr *		p_lisRes;
	SElementoPtr *	p_elpObj;
	SElementoPtr *	p_elpRes;
	char *			p_cDato;
	char *			p_cCopia;
	int				iPosAnt;
	int				iError;

	if ( SLispEsValida ( p_lisDatos ) == 1 )
	{
		p_lisRes = SLispCrear ();
		iError = MemEsInvalida ( p_lisRes );
		p_elpObj = SLispElementoPtr ( p_lisDatos, 0 );
		while ( ES_VALIDO ( p_elpObj ) && ( iError == 0 ) )
		{
			p_cDato = (char *) SElpDatos ( p_elpObj );
			if ( SLispExisteExt ( p_lisRes, (byte *) p_cDato, _SLisLitSonIguales ) == 0 )
			{
				/* Sin ordenar va detras del ultimo; ordenada, detras del ultimo
				   menor que ella. Con -1 SLispInsertarElem la pone al principio. */
				iPosAnt = SLispNumElementos ( p_lisRes ) - 1;
				if ( iOrdenar != 0 )
				{
					iPosAnt = -1;
					p_elpRes = SLispElementoPtr ( p_lisRes, 0 );
					while ( ES_VALIDO ( p_elpRes ) &&
							( CadComparar ( (char *) SElpDatos ( p_elpRes ), p_cDato ) == COMP_MENOR ) )
					{
						iPosAnt = iPosAnt + 1;
						p_elpRes = SElpSucesor ( p_elpRes );
					}
				}
				p_cCopia = CadDuplicar ( p_cDato );
				if ( ES_VALIDO ( p_cCopia ) )
				{
					if ( SLispInsertarElem ( p_lisRes, iPosAnt, (byte *) p_cCopia ) != 1 )
					{
						MemLiberar ( (void **) &p_cCopia );
						iError = 1;
					}
				}
				else
				{
					iError = 1;
				}
			}
			p_elpObj = SElpSucesor ( p_elpObj );
		}
		if ( iError == 1 )
		{
			SLispDestruir ( &p_lisRes );
			ERROR_ESTABLECER ( ERR_GENERAL_OPERATIVO );
		}
	}
	else
	{
		p_lisRes = NULL;
	}
	return ( p_lisRes );
}

/* 1 si alguna cadena esta repetida, comparando el contenido. Compartida con
   SSecuenciaLiterales. */
int _SLisLitTieneRepetidos ( SListaPtr * p_lisDatos )
{
	int				iRes;
	int				iPos;
	SElementoPtr *	p_elpObj;

	iRes = 0;
	iPos = 0;
	p_elpObj = SLispElementoPtr ( p_lisDatos, 0 );
	while ( ES_VALIDO ( p_elpObj ) && ( iRes == 0 ) )
	{
		if ( SLispBuscarSiguienteExt ( p_lisDatos, SElpDatos ( p_elpObj ), iPos, _SLisLitSonIguales ) >= 0 )
		{
			iRes = 1;
		}
		p_elpObj = SElpSucesor ( p_elpObj );
		iPos = iPos + 1;
	}
	return ( iRes );
}

SListaLiterales * SLisLitExtraerUnicos ( SListaLiterales * p_lisObj )
{
	return ( SLisLitExtraerUnicosExt ( p_lisObj, 0 ) );
}

SListaLiterales * SLisLitExtraerUnicosExt ( SListaLiterales * p_lisObj, int iOrdenar )
{
	SListaLiterales * p_lisRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		p_lisRes = _SLisLitEnvolver ( _SLisLitExtraerUnicos ( p_lisObj->p_lisDatos, iOrdenar ) );
	}
	else
	{
		p_lisRes = NULL;
	}
	return ( p_lisRes );
}

int SLisLitTieneRepetidos ( SListaLiterales * p_lisObj )
{
	int	iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iRes = _SLisLitTieneRepetidos ( p_lisObj->p_lisDatos );
	}
	else
	{
		iRes = 0;
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
	SElementoPtr *	p_elpObj;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		printf ( "Contenido de la lista: [\n" );
		/* Por la CADENA, no por indice: el indice entra por el extremo mas
		   cercano, asi que un recorrido completo sale cuadratico. */
		p_elpObj = SLispElementoPtr ( p_lisObj->p_lisDatos, 0 );
		while ( ES_VALIDO ( p_elpObj ) )
		{
			printf ( "\t[%s], \n", (char *) SElpDatos ( p_elpObj ) );
			p_elpObj = SElpSucesor ( p_elpObj );
		}
		printf ( "]\n" );
	}
	else
	{
		printf ( "%s\n", VALOR_NULO );
	}
}

/* Copia de los valores, en el mismo orden; NULL si falla alguna copia. */
SListaLiterales * SLisLitDuplicar ( SListaLiterales * p_lisObj )
{
	SListaLiterales * p_lisRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		p_lisRes = _SLisLitEnvolver ( SLispDuplicarExt ( p_lisObj->p_lisDatos, _SLisLitDuplicar ) );
	}
	else
	{
		p_lisRes = NULL;
	}
	return ( p_lisRes );
}

/* Operaciones con otras listas: delegan en las Ext de SListaPtr, comparando con
   CadComparar y copiando con CadDuplicar. Ver Listas.md. */
int SLisLitExistenTodos ( SListaLiterales * p_lisObj, SListaLiterales * p_lisValores )
{
	int	iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		if ( ES_VALIDO ( p_lisValores ) )
		{
			iRes = SLispExistenTodosExt ( p_lisObj->p_lisDatos, p_lisValores->p_lisDatos, _SLisLitSonIguales );
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

int SLisLitExisteAlguno ( SListaLiterales * p_lisObj, SListaLiterales * p_lisValores )
{
	int	iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		if ( ES_VALIDO ( p_lisValores ) )
		{
			iRes = SLispExisteAlgunoExt ( p_lisObj->p_lisDatos, p_lisValores->p_lisDatos, _SLisLitSonIguales );
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

/* Mueven las cadenas: no hace falta copiarlas, pasan a ser de p_lisObj. */
int SLisLitInsertarLista ( SListaLiterales * p_lisObj, SListaLiterales * p_lisValores )
{
	int	iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		if ( ES_VALIDO ( p_lisValores ) )
		{
			iRes = SLispInsertarLista ( p_lisObj->p_lisDatos, p_lisValores->p_lisDatos );
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

int SLisLitConcatenarLista ( SListaLiterales * p_lisObj, SListaLiterales * p_lisValores )
{
	int	iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		if ( ES_VALIDO ( p_lisValores ) )
		{
			iRes = SLispConcatenarLista ( p_lisObj->p_lisDatos, p_lisValores->p_lisDatos );
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

int SLisLitInsertarListaDup ( SListaLiterales * p_lisObj, SListaLiterales * p_lisValores )
{
	int	iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		if ( ES_VALIDO ( p_lisValores ) )
		{
			iRes = SLispInsertarListaDupExt ( p_lisObj->p_lisDatos, p_lisValores->p_lisDatos, _SLisLitDuplicar );
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

int SLisLitConcatenarListaDup ( SListaLiterales * p_lisObj, SListaLiterales * p_lisValores )
{
	int	iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		if ( ES_VALIDO ( p_lisValores ) )
		{
			iRes = SLispConcatenarListaDupExt ( p_lisObj->p_lisDatos, p_lisValores->p_lisDatos, _SLisLitDuplicar );
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

/* Mueve las cadenas; la lista nueva hereda la liberacion de p_lisObj. */
SListaLiterales * SLisLitExtraerLista ( SListaLiterales * p_lisObj, SListaLiterales * p_lisValores )
{
	SListaLiterales * p_lisRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		if ( ES_VALIDO ( p_lisValores ) )
		{
			p_lisRes = _SLisLitEnvolver ( SLispExtraerListaExt ( p_lisObj->p_lisDatos, p_lisValores->p_lisDatos, _SLisLitSonIguales ) );
		}
		else
		{
			p_lisRes = NULL;
		}
	}
	else
	{
		p_lisRes = NULL;
	}
	return ( p_lisRes );
}

/* Destruye la primera aparicion de cada valor de p_lisValores, comparando el
   contenido; las cadenas se liberan segun la liberacion de p_lisObj. */
int SLisLitEliminarLista ( SListaLiterales * p_lisObj, SListaLiterales * p_lisValores )
{
	int	iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		if ( ES_VALIDO ( p_lisValores ) )
		{
			iRes = SLispEliminarListaExt ( p_lisObj->p_lisDatos, p_lisValores->p_lisDatos, _SLisLitSonIguales );
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

/* Las tres devuelven una lista con COPIAS de las cadenas, duena de ellas. */
SListaLiterales * SLisLitUnion ( SListaLiterales * p_lisValores1, SListaLiterales * p_lisValores2 )
{
	SListaLiterales * p_lisRes;

	if ( ES_VALIDO ( p_lisValores1 ) )
	{
		if ( ES_VALIDO ( p_lisValores2 ) )
		{
			p_lisRes = _SLisLitEnvolver ( SLispUnionExt ( p_lisValores1->p_lisDatos, p_lisValores2->p_lisDatos, _SLisLitDuplicar ) );
		}
		else
		{
			p_lisRes = NULL;
		}
	}
	else
	{
		p_lisRes = NULL;
	}
	return ( p_lisRes );
}

SListaLiterales * SLisLitInterseccion ( SListaLiterales * p_lisValores1, SListaLiterales * p_lisValores2 )
{
	SListaLiterales * p_lisRes;

	if ( ES_VALIDO ( p_lisValores1 ) )
	{
		if ( ES_VALIDO ( p_lisValores2 ) )
		{
			p_lisRes = _SLisLitEnvolver ( SLispInterseccionExt ( p_lisValores1->p_lisDatos, p_lisValores2->p_lisDatos, _SLisLitSonIguales, _SLisLitDuplicar ) );
		}
		else
		{
			p_lisRes = NULL;
		}
	}
	else
	{
		p_lisRes = NULL;
	}
	return ( p_lisRes );
}

SListaLiterales * SLisLitDiferencia ( SListaLiterales * p_lisValores1, SListaLiterales * p_lisValores2 )
{
	SListaLiterales * p_lisRes;

	if ( ES_VALIDO ( p_lisValores1 ) )
	{
		if ( ES_VALIDO ( p_lisValores2 ) )
		{
			p_lisRes = _SLisLitEnvolver ( SLispDiferenciaExt ( p_lisValores1->p_lisDatos, p_lisValores2->p_lisDatos, _SLisLitSonIguales, _SLisLitDuplicar ) );
		}
		else
		{
			p_lisRes = NULL;
		}
	}
	else
	{
		p_lisRes = NULL;
	}
	return ( p_lisRes );
}


/* Envuelve en una SListaLiterales la SListaPtr que devuelve una operacion de
   SListaPtr, y se queda con ella. No se usa SLisLitCrear porque ese crea su
   propia SListaPtr vacia, que al sustituirla quedaria sin liberar. Con
   p_lisDatos nula devuelve NULL, y si no puede reservar la envoltura destruye
   p_lisDatos. */
static SListaLiterales * _SLisLitEnvolver ( SListaPtr * p_lisDatos )
{
	SListaLiterales * p_lisRes;

	if ( ES_VALIDO ( p_lisDatos ) )
	{
		p_lisRes = (SListaLiterales *) MemReservar ( sizeof ( SListaLiterales ) );
		if ( ES_VALIDO ( p_lisRes ) )
		{
			p_lisRes->p_lisDatos = p_lisDatos;
		}
		else
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


