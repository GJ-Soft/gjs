#include "SListaRealesDobles.h"

#include "CalculoConfig.h"
#include "CalculoOperaciones.h"



SListaRealesDobles * SLisRealdCrear ()
{
	SListaRealesDobles * p_lisObj;
	
	p_lisObj = (SListaRealesDobles *) MemReservar ( sizeof ( SListaRealesDobles ) );
	if ( ES_VALIDO ( p_lisObj ) )
	{
		p_lisObj->p_lisDatos = SLisCrear ();
	}
	return ( p_lisObj );
}

/* La lista pasa a ser de la lista de reales, que la destruye con ella. Si
   la lista no es valida, o no se puede crear, devuelve NULL y la lista sigue
   siendo del llamante. */
SListaRealesDobles * SLisRealdEncapsular ( SLista * p_lisDatos )
{
	SListaRealesDobles * p_lisRes;

	if ( SLisEsValida ( p_lisDatos ) == 1 )
	{
		p_lisRes = (SListaRealesDobles *) MemReservar ( sizeof ( SListaRealesDobles ) );
		if ( ES_VALIDO ( p_lisRes ) )
		{
			p_lisRes->p_lisDatos = p_lisDatos;
		}
	}
	else
	{
		p_lisRes = NULL;
	}
	return ( p_lisRes );
}

/* Copia los iNumValores primeros de p_dValores, en orden, con el cursor al
   inicio. Con 0 valores da una lista vacia; NULL si el vector es nulo, el
   numero es negativo o falla alguna insercion. */
SListaRealesDobles * SLisRealdCrearDesdeVector ( const double * p_dValores, int iNumValores )
{
	SListaRealesDobles *	p_lisRes;
	int						iPos;
	int						iError;

	if ( ES_VALIDO ( p_dValores ) )
	{
		if ( iNumValores >= 0 )
		{
			p_lisRes = SLisRealdCrear ();
			if ( ES_VALIDO ( p_lisRes ) )
			{
				iError = 0;
				iPos = 0;
				while ( ( iError == 0 ) && ( iPos < iNumValores ) )
				{
					if ( SLisRealdInsertarDetras ( p_lisRes, p_dValores [ iPos ] ) == 1 )
					{
						iPos = iPos + 1;
					}
					else
					{
						iError = 1;
					}
				}
				if ( iError == 1 )
				{
					SLisRealdDestruir ( &p_lisRes );
				}
				else
				{
					SLisRealdInicio ( p_lisRes );
				}
			}
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

void SLisRealdDestruir ( SListaRealesDobles ** p_p_lisObj )
{
	SListaRealesDobles * p_lisObj;
	
	if ( ES_VALIDO ( p_p_lisObj ) )
	{
		p_lisObj = *p_p_lisObj;

		if ( ES_VALIDO ( p_lisObj ) )
		{
			SLisDestruir ( &(p_lisObj->p_lisDatos) );
			MemLiberar ( (void **) p_p_lisObj );
		}
	}
}

int SLisRealdEsValida ( SListaRealesDobles * p_lisObj )
{
	int iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iRes = SLisEsValida ( p_lisObj->p_lisDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLisRealdEstaVacia ( SListaRealesDobles * p_lisObj )
{
	int iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iRes = SLisEstaVacia ( p_lisObj->p_lisDatos );
	}
	else
	{
		iRes = 1;
	}
	return ( iRes );
}

int SLisRealdNumElementos ( SListaRealesDobles * p_lisObj )
{
	int iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iRes = SLisNumElementos ( p_lisObj->p_lisDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

double SLisRealdElemento ( SListaRealesDobles * p_lisObj, int iElem )
{
	double		dRes;
	SElemento *	p_elmObj;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		p_elmObj = SLisElemento ( p_lisObj->p_lisDatos, iElem );
		if ( ES_VALIDO ( p_elmObj ) )
		{
			dRes = SElmRealDoble ( p_elmObj );
		}
		else
		{
			dRes = 0;
		}
	}
	else
	{
		dRes = 0;
	}
	return ( dRes );
}

int SLisRealdEstablecerElem ( SListaRealesDobles * p_lisObj, int iPos, double dDato )
{
	int			iRes;
	SElemento *	p_elmObj;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		p_elmObj = SLisElemento ( p_lisObj->p_lisDatos, iPos );
		if ( ES_VALIDO ( p_elmObj ) )
		{
			iRes = SElmEscribirRealDoble ( p_elmObj, dDato );
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

int SLisRealdInsertarElem ( SListaRealesDobles * p_lisObj, int iPosAnt, double dDato )
{
	int			iRes;
	SElemento *	p_elmObj;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		p_elmObj = SElmCrearRealDoble ();
		if ( ES_VALIDO ( p_elmObj ) )
		{
			if ( SElmEscribirRealDoble ( p_elmObj, dDato ) == 1 )
			{
				iRes = SLisInsertarElem ( p_lisObj->p_lisDatos, iPosAnt, p_elmObj );
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

int SLisRealdInsertarAlInicio ( SListaRealesDobles * p_lisObj, double dDato )
{
	return ( SLisRealdInsertarElem ( p_lisObj, -1, dDato ) );
}

int SLisRealdInsertarAlFinal ( SListaRealesDobles * p_lisObj, double dDato )
{
	int iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iRes = SLisRealdInsertarElem ( p_lisObj, SLisRealdNumElementos ( p_lisObj ), dDato );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLisRealdEliminarElem ( SListaRealesDobles * p_lisObj, int iElem )
{
	int iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iRes = SLisEliminarElem ( p_lisObj->p_lisDatos, iElem );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int SLisRealdVaciar ( SListaRealesDobles * p_lisObj )
{
	int iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iRes = SLisVaciar ( p_lisObj->p_lisDatos );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int SLisRealdPosicion ( SListaRealesDobles * p_lisObj )
{
	int	iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iRes = SLisPosicion ( p_lisObj->p_lisDatos );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

double SLisRealdActual ( SListaRealesDobles * p_lisObj )
{
	double		dRes;
	SElemento * p_elmObj;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		p_elmObj = SLisActual ( p_lisObj->p_lisDatos );
		if ( ES_VALIDO ( p_elmObj ) )
		{
			dRes = SElmRealDoble ( p_elmObj );
		}
		else
		{
			ERROR_ESTABLECER( ERR_POSICION_INVALIDA );
			dRes = 0.0;
		}
	}
	else
	{
		dRes = 0.0;
	}
	return ( dRes );
}

void SLisRealdInicio ( SListaRealesDobles * p_lisObj )
{
	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		SLisInicio ( p_lisObj->p_lisDatos );
	}
}

void SLisRealdFinal ( SListaRealesDobles * p_lisObj )
{
	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		SLisFinal ( p_lisObj->p_lisDatos );
	}
}

void SLisRealdSiguiente ( SListaRealesDobles * p_lisObj )
{
	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		SLisSiguiente ( p_lisObj->p_lisDatos );
	}
}

void SLisRealdAnterior ( SListaRealesDobles * p_lisObj )
{
	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		SLisAnterior ( p_lisObj->p_lisDatos );
	}
}

void SLisRealdMoverA ( SListaRealesDobles * p_lisObj, int iElem )
{
	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		SLisMoverA ( p_lisObj->p_lisDatos, iElem );
	}
}

void SLisRealdDeposicionar ( SListaRealesDobles * p_lisObj )
{
	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		SLisDeposicionar ( p_lisObj->p_lisDatos );
	}
}

int SLisRealdEsNulo ( SListaRealesDobles * p_lisObj )
{
	int iRes;

	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		iRes = SLisEsNulo ( p_lisObj->p_lisDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLisRealdEstaEnFinal ( SListaRealesDobles * p_lisObj )
{
	int iRes;

	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		iRes = SLisEstaEnFinal ( p_lisObj->p_lisDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLisRealdEstaEnInicio ( SListaRealesDobles * p_lisObj )
{
	int iRes;

	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		iRes = SLisEstaEnInicio ( p_lisObj->p_lisDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLisRealdInsertar ( SListaRealesDobles * p_lisObj, double dDato )
{
	return ( SLisRealdInsertarDetras ( p_lisObj, dDato ) );
}

int SLisRealdInsertarOrdenado ( SListaRealesDobles * p_lisObj, double dDato )
{
	int			iRes;
	int			iElem;
	int			iNumElems;
	SElemento *	p_elmObj;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iRes = 0;
		iNumElems = SLisRealdNumElementos ( p_lisObj );
		if ( iNumElems > 0 )
		{
			/* La busqueda va POR LA CADENA, no por indice: cada acceso por
			   indice cuesta media lista, y Ordenar llama a esta una vez por
			   elemento ( ver SListaEnteros ).

			   Se para en el primer elemento MAYOR que el dato, o al final de la
			   cadena; el sitio donde insertar es iElem - 1 ( -1 es "al
			   principio" ). Compara sin tolerancia: solo decide el sitio, y asi
			   un valor casi igual a otros queda detras de ellos. */
			iElem = 0;
			p_elmObj = SLisElemento ( p_lisObj->p_lisDatos, 0 );
			while ( ES_VALIDO ( p_elmObj ) && ( dDato >= SElmRealDoble ( p_elmObj ) ) )
			{
				iElem = iElem + 1;
				p_elmObj = SElmSucesor ( p_elmObj );
			}
			iRes = SLisRealdInsertarElem ( p_lisObj, iElem - 1, dDato );
		}
		else
		{
			iRes = SLisRealdInsertar ( p_lisObj, dDato );
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLisRealdInsertarDelante ( SListaRealesDobles * p_lisObj, double dDato )
{
	int			iRes;
	SElemento *	p_elmObj;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		p_elmObj = SElmCrearRealDoble ();
		if ( ES_VALIDO ( p_elmObj ) )
		{
			if ( SElmEscribirRealDoble ( p_elmObj, dDato ) == 1 )
			{
				iRes = SLisInsertarDelante ( p_lisObj->p_lisDatos, p_elmObj );
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

int SLisRealdInsertarDetras ( SListaRealesDobles * p_lisObj, double dDato )
{
	int			iRes;
	SElemento *	p_elmObj;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		p_elmObj = SElmCrearRealDoble ();
		if ( ES_VALIDO ( p_elmObj ) )
		{
			if ( SElmEscribirRealDoble ( p_elmObj, dDato ) == 1 )
			{
				iRes = SLisInsertarDetras ( p_lisObj->p_lisDatos, p_elmObj );
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

int SLisRealdEliminar ( SListaRealesDobles * p_lisObj )
{
	int iRes;

	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		iRes = SLisEliminar ( p_lisObj->p_lisDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

/* IGUALDAD ENTRE REALES. Dos valores son iguales cuando MatEsIgual lo dice,
   es decir, con la tolerancia de la libreria ( g_dMatPrecision ): todo lo que
   busca, cuenta, quita valores repetidos o compara con otra lista usa esa
   igualdad, para que Existe y ExistenTodos no se contradigan sobre el mismo
   valor. Por eso las operaciones con otras listas que comparan no delegan en
   las de SLista, que comparan los bytes: se hacen aqui, sobre la cadena, con
   la misma semantica que aquellas ( ver Listas.md ).

   Las que estan sobre SLista son compartidas con SSecuenciaRealesDobles ( por
   eso no son static ). Todas recorren la CADENA de elementos, no el indice:
   SLisElemento entra por el extremo mas cercano, y un barrido por indice
   seria cuadratico. Entran por la generica, no por SLisRealdElemento, que
   devuelve el VALOR. */

/* La posicion del siguiente igual DETRAS de iPos, o -1: con iPos = -1 busca
   desde el principio, y un iPos menor da -1. */
int _SLisRealdBuscarSiguiente ( SLista * p_lisDatos, double dDato, int iPos )
{
	int			iRes;
	int			iEnc;
	SElemento *	p_elmObj;

	if ( iPos >= -1 )
	{
		iRes = iPos + 1;
		p_elmObj = SLisElemento ( p_lisDatos, iRes );
		iEnc = 0;
		while ( ES_VALIDO ( p_elmObj ) && ( iEnc == 0 ) )
		{
			if ( MatEsIgual ( SElmRealDoble ( p_elmObj ), dDato ) == 1 )
			{
				iEnc = 1;
			}
			else
			{
				p_elmObj = SElmSucesor ( p_elmObj );
				iRes = iRes + 1;
			}
		}
		if ( iEnc == 0 )
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

/* Cuantos iguales hay, 0 si ninguno. */
int _SLisRealdRepeticiones ( SLista * p_lisDatos, double dDato )
{
	int			iRes;
	SElemento *	p_elmObj;

	iRes = 0;
	p_elmObj = SLisElemento ( p_lisDatos, 0 );
	while ( ES_VALIDO ( p_elmObj ) )
	{
		if ( MatEsIgual ( SElmRealDoble ( p_elmObj ), dDato ) == 1 )
		{
			iRes = iRes + 1;
		}
		p_elmObj = SElmSucesor ( p_elmObj );
	}
	return ( iRes );
}

/* 1 si todos los valores de p_lisValores estan en p_lisObj; con los valores
   vacios, 1. 0 con alguna de las dos invalida. */
int _SLisRealdExistenTodos ( SLista * p_lisObj, SLista * p_lisValores )
{
	int			iRes;
	SElemento *	p_elmObj;

	if ( SLisEsValida ( p_lisObj ) == 1 )
	{
		if ( SLisEsValida ( p_lisValores ) == 1 )
		{
			iRes = 1;
			p_elmObj = SLisElemento ( p_lisValores, 0 );
			while ( ES_VALIDO ( p_elmObj ) && ( iRes == 1 ) )
			{
				if ( _SLisRealdBuscarSiguiente ( p_lisObj, SElmRealDoble ( p_elmObj ), -1 ) < 0 )
				{
					iRes = 0;
				}
				p_elmObj = SElmSucesor ( p_elmObj );
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

/* 1 si alguno de los valores de p_lisValores esta en p_lisObj; con los
   valores vacios, 0. 0 con alguna de las dos invalida. */
int _SLisRealdExisteAlguno ( SLista * p_lisObj, SLista * p_lisValores )
{
	int			iRes;
	SElemento *	p_elmObj;

	if ( SLisEsValida ( p_lisObj ) == 1 )
	{
		if ( SLisEsValida ( p_lisValores ) == 1 )
		{
			iRes = 0;
			p_elmObj = SLisElemento ( p_lisValores, 0 );
			while ( ES_VALIDO ( p_elmObj ) && ( iRes == 0 ) )
			{
				if ( _SLisRealdBuscarSiguiente ( p_lisObj, SElmRealDoble ( p_elmObj ), -1 ) >= 0 )
				{
					iRes = 1;
				}
				p_elmObj = SElmSucesor ( p_elmObj );
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

/* Destruye de p_lisObj todas las apariciones de cada valor de p_lisValores,
   que no se toca. Lo que no se encuentra se ignora. 1 si ha podido eliminar
   todo lo encontrado; si falla una eliminacion se para y da 0, y lo eliminado
   se queda eliminado. 0 sin tocar nada con la misma lista en los dos
   argumentos o con alguna invalida. */
int _SLisRealdEliminarLista ( SLista * p_lisObj, SLista * p_lisValores )
{
	int			iRes;
	int			iPos;
	double		dDato;
	SElemento *	p_elmObj;

	if ( SLisEsValida ( p_lisObj ) == 1 )
	{
		if ( SLisEsValida ( p_lisValores ) == 1 )
		{
			if ( p_lisObj != p_lisValores )
			{
				iRes = 1;
				p_elmObj = SLisElemento ( p_lisValores, 0 );
				while ( ES_VALIDO ( p_elmObj ) && ( iRes == 1 ) )
				{
					dDato = SElmRealDoble ( p_elmObj );
					iPos = _SLisRealdBuscarSiguiente ( p_lisObj, dDato, -1 );
					while ( ( iPos >= 0 ) && ( iRes == 1 ) )
					{
						if ( SLisEliminarElem ( p_lisObj, iPos ) == 1 )
						{
							/* El siguiente ha pasado a ocupar iPos: se sigue buscando desde ahi. */
							iPos = _SLisRealdBuscarSiguiente ( p_lisObj, dDato, iPos - 1 );
						}
						else
						{
							iRes = 0;
						}
					}
					p_elmObj = SElmSucesor ( p_elmObj );
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

/* Saca de p_lisObj, a una lista nueva, todas las apariciones de cada valor de
   p_lisValores: por el orden de p_lisValores y, las de un mismo valor, en el
   que tenian. Lo que no se encuentra se ignora. Los elementos se mueven, no se
   copian. Si falla una insercion, ese elemento vuelve al final de p_lisObj y
   se para: la extraccion queda a medias. NULL con la misma lista en los dos
   argumentos, con alguna invalida o si no se puede crear la nueva. */
SLista * _SLisRealdExtraerLista ( SLista * p_lisObj, SLista * p_lisValores )
{
	SLista *	p_lisRes;
	SElemento *	p_elmObj;
	SElemento *	p_elmExt;
	int			iPos;
	int			iError;
	double		dDato;

	if ( SLisEsValida ( p_lisObj ) == 1 )
	{
		if ( SLisEsValida ( p_lisValores ) == 1 )
		{
			if ( p_lisObj != p_lisValores )
			{
				p_lisRes = SLisCrear ();
				if ( ES_VALIDO ( p_lisRes ) )
				{
					iError = 0;
					p_elmObj = SLisElemento ( p_lisValores, 0 );
					while ( ES_VALIDO ( p_elmObj ) && ( iError == 0 ) )
					{
						dDato = SElmRealDoble ( p_elmObj );
						iPos = _SLisRealdBuscarSiguiente ( p_lisObj, dDato, -1 );
						while ( ( iPos >= 0 ) && ( iError == 0 ) )
						{
							p_elmExt = SLisExtraerElem ( p_lisObj, iPos );
							if ( SLisInsertarAlFinal ( p_lisRes, p_elmExt ) == 1 )
							{
								/* El siguiente ha pasado a ocupar iPos: se sigue buscando desde ahi. */
								iPos = _SLisRealdBuscarSiguiente ( p_lisObj, dDato, iPos - 1 );
							}
							else
							{
								/* No se pierde: vuelve a p_lisObj, aunque al final. */
								SLisInsertarAlFinal ( p_lisObj, p_elmExt );
								iError = 1;
							}
						}
						p_elmObj = SElmSucesor ( p_elmObj );
					}
				}
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
	}
	else
	{
		p_lisRes = NULL;
	}
	return ( p_lisRes );
}

/* Lista nueva con COPIAS de los de p_lisValores1 que estan ( iEstan = 1 ) o
   que no estan ( iEstan = 0 ) en p_lisValores2, en el orden de p_lisValores1.
   NULL si algo falla. */
static SLista * _SLisRealdFiltrar ( SLista * p_lisValores1, SLista * p_lisValores2, int iEstan )
{
	SLista *	p_lisRes;
	SElemento *	p_elmObj;
	SElemento *	p_elmNuevo;
	int			iError;
	int			iEsta;

	if ( SLisEsValida ( p_lisValores1 ) == 1 )
	{
		if ( SLisEsValida ( p_lisValores2 ) == 1 )
		{
			p_lisRes = SLisCrear ();
			if ( ES_VALIDO ( p_lisRes ) )
			{
				iError = 0;
				p_elmObj = SLisElemento ( p_lisValores1, 0 );
				while ( ES_VALIDO ( p_elmObj ) && ( iError == 0 ) )
				{
					if ( _SLisRealdBuscarSiguiente ( p_lisValores2, SElmRealDoble ( p_elmObj ), -1 ) >= 0 )
					{
						iEsta = 1;
					}
					else
					{
						iEsta = 0;
					}
					if ( iEsta == iEstan )
					{
						p_elmNuevo = SElmDuplicar ( p_elmObj );
						if ( SLisInsertarAlFinal ( p_lisRes, p_elmNuevo ) != 1 )
						{
							SElmDestruir ( &p_elmNuevo );
							iError = 1;
						}
					}
					p_elmObj = SElmSucesor ( p_elmObj );
				}
				if ( iError == 1 )
				{
					SLisDestruir ( &p_lisRes );
				}
			}
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

/* Los de p_lisValores1 que estan en p_lisValores2, en el orden de p_lisValores1. */
SLista * _SLisRealdInterseccion ( SLista * p_lisValores1, SLista * p_lisValores2 )
{
	return ( _SLisRealdFiltrar ( p_lisValores1, p_lisValores2, 1 ) );
}

/* Los de p_lisValores1 que NO estan en p_lisValores2, en el orden de p_lisValores1. */
SLista * _SLisRealdDiferencia ( SLista * p_lisValores1, SLista * p_lisValores2 )
{
	return ( _SLisRealdFiltrar ( p_lisValores1, p_lisValores2, 0 ) );
}

int SLisRealdExiste ( SListaRealesDobles * p_lisObj, double dDato )
{
	int iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		if ( _SLisRealdBuscarSiguiente ( p_lisObj->p_lisDatos, dDato, -1 ) >= 0 )
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

/* Repeticiones: cuantos iguales hay, 0 si ninguno. Buscar es BuscarPrimero:
   la posicion del primero igual, o -1. */
int SLisRealdRepeticiones ( SListaRealesDobles * p_lisObj, double dDato )
{
	int	iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iRes = _SLisRealdRepeticiones ( p_lisObj->p_lisDatos, dDato );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLisRealdBuscar ( SListaRealesDobles * p_lisObj, double dDato )
{
	return ( SLisRealdBuscarPrimero ( p_lisObj, dDato ) );
}

int SLisRealdBuscarPrimero ( SListaRealesDobles * p_lisObj, double dDato )
{
	return ( SLisRealdBuscarSiguiente ( p_lisObj, dDato, -1 ) );
}

int SLisRealdBuscarSiguiente ( SListaRealesDobles * p_lisObj, double dDato, int iPos )
{
	int	iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iRes = _SLisRealdBuscarSiguiente ( p_lisObj->p_lisDatos, dDato, iPos );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

/* Ordenada si ningun elemento es menor que el anterior: con la tolerancia de
   MatEsMenor, asi que dos casi iguales en cualquier orden no la desordenan. */
int SLisRealdEstaOrdenada ( SListaRealesDobles * p_lisObj )
{
	double		dDatoAnt;
	double		dDato;
	SElemento *	p_elmObj;
	int			iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iRes = 1;
		dDatoAnt = 0.0;
		p_elmObj = SLisElemento ( p_lisObj->p_lisDatos, 0 );
		if ( ES_VALIDO ( p_elmObj ) )
		{
			dDatoAnt = SElmRealDoble ( p_elmObj );
			p_elmObj = SElmSucesor ( p_elmObj );
		}
		while ( ES_VALIDO ( p_elmObj ) && ( iRes == 1 ) )
		{
			dDato = SElmRealDoble ( p_elmObj );
			if ( MatEsMenor ( dDato, dDatoAnt ) == 1 )
			{
				iRes = 0;
			}
			dDatoAnt = dDato;
			p_elmObj = SElmSucesor ( p_elmObj );
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

/* Lista nueva con los mismos valores, de menor a mayor; la de entrada no se
   toca. NULL si falla alguna insercion. */
SListaRealesDobles * SLisRealdOrdenar ( SListaRealesDobles * p_lisObj )
{
	int						iError;
	SElemento *				p_elmObj;
	SListaRealesDobles *	p_lisRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		p_lisRes = SLisRealdCrear ();
		iError = MemEsInvalida ( p_lisRes );
		p_elmObj = SLisElemento ( p_lisObj->p_lisDatos, 0 );
		while ( ES_VALIDO ( p_elmObj ) && ( iError == 0 ) )
		{
			if ( SLisRealdInsertarOrdenado ( p_lisRes, SElmRealDoble ( p_elmObj ) ) != 1 )
			{
				iError = 1;
			}
			p_elmObj = SElmSucesor ( p_elmObj );
		}
		if ( iError == 1 )
		{
			SLisRealdDestruir ( &p_lisRes );
			ERROR_ESTABLECER ( ERR_GENERAL_OPERATIVO );
		}
	}
	else
	{
		p_lisRes = NULL;
	}
	return ( p_lisRes );
}

SListaRealesDobles * SLisRealdExtraerUnicos ( SListaRealesDobles * p_lisObj )
{
	return ( SLisRealdExtraerUnicosExt ( p_lisObj, 0 ) );
}

/* Lista nueva con un valor por cada grupo de iguales: el primero que
   aparece. Con iOrdenar distinto de 0, de menor a mayor. */
SListaRealesDobles * SLisRealdExtraerUnicosExt ( SListaRealesDobles * p_lisObj, int iOrdenar )
{
	int						iError;
	double					dDato;
	SElemento *				p_elmObj;
	SListaRealesDobles *	p_lisRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		p_lisRes = SLisRealdCrear ();
		iError = MemEsInvalida ( p_lisRes );
		p_elmObj = SLisElemento ( p_lisObj->p_lisDatos, 0 );
		while ( ES_VALIDO ( p_elmObj ) && ( iError == 0 ) )
		{
			dDato = SElmRealDoble ( p_elmObj );
			if ( SLisRealdExiste ( p_lisRes, dDato ) == 0 )
			{
				if ( iOrdenar == 0 )
				{
					if ( SLisRealdInsertar ( p_lisRes, dDato ) != 1 )
					{
						iError = 1;
					}
				}
				else
				{
					if ( SLisRealdInsertarOrdenado ( p_lisRes, dDato ) != 1 )
					{
						iError = 1;
					}
				}
			}
			p_elmObj = SElmSucesor ( p_elmObj );
		}
		if ( iError == 1 )
		{
			SLisRealdDestruir ( &p_lisRes );
			ERROR_ESTABLECER ( ERR_GENERAL_OPERATIVO );
		}
	}
	else
	{
		p_lisRes = NULL;
	}
	return ( p_lisRes );
}

int SLisRealdTieneRepetidos ( SListaRealesDobles * p_lisObj )
{
	int						iRes;
	int						iError;
	double					dDato;
	SElemento *				p_elmObj;
	SListaRealesDobles *	p_lisDistintos;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iRes = 0;
		p_lisDistintos = SLisRealdCrear ();
		iError = MemEsInvalida ( p_lisDistintos );
		p_elmObj = SLisElemento ( p_lisObj->p_lisDatos, 0 );
		while ( ES_VALIDO ( p_elmObj ) && ( iError == 0 ) && ( iRes == 0 ) )
		{
			dDato = SElmRealDoble ( p_elmObj );
			if ( SLisRealdExiste ( p_lisDistintos, dDato ) == 1 )
			{
				iRes = 1;
			}
			else
			{
				if ( SLisRealdInsertarOrdenado ( p_lisDistintos, dDato ) != 1 )
				{
					iError = 1;
				}
			}
			p_elmObj = SElmSucesor ( p_elmObj );
		}
		SLisRealdDestruir ( &p_lisDistintos );
		if ( iError == 1 )
		{
			ERROR_ESTABLECER ( ERR_GENERAL_OPERATIVO );
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

/* Con la lista vacia, Min da DBL_MAX y Max -DBL_MAX, como los de enteros dan
   INT_MAX e INT_MIN. Ojo: el "minimo" de los double es -DBL_MAX; DBL_MIN es el
   menor POSITIVO. */
double SLisRealdMin ( SListaRealesDobles * p_lisObj )
{
	double		dDato;
	double		dRes;
	SElemento *	p_elmObj;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		dRes = DBL_MAX;
		p_elmObj = SLisElemento ( p_lisObj->p_lisDatos, 0 );
		while ( ES_VALIDO ( p_elmObj ) )
		{
			dDato = SElmRealDoble ( p_elmObj );
			if ( dDato < dRes )
			{
				dRes = dDato;
			}
			p_elmObj = SElmSucesor ( p_elmObj );
		}
	}
	else
	{
		ERROR_ESTABLECER ( ERR_PARAMETROS );
		dRes = 0.0;
	}
	return ( dRes );
}

double SLisRealdMax ( SListaRealesDobles * p_lisObj )
{
	double		dDato;
	double		dRes;
	SElemento *	p_elmObj;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		dRes = -DBL_MAX;
		p_elmObj = SLisElemento ( p_lisObj->p_lisDatos, 0 );
		while ( ES_VALIDO ( p_elmObj ) )
		{
			dDato = SElmRealDoble ( p_elmObj );
			if ( dDato > dRes )
			{
				dRes = dDato;
			}
			p_elmObj = SElmSucesor ( p_elmObj );
		}
	}
	else
	{
		ERROR_ESTABLECER ( ERR_PARAMETROS );
		dRes = 0.0;
	}
	return ( dRes );
}

void SLisRealdObtenerParametros ( SListaRealesDobles * p_lisObj, double * p_dMin, double * p_dMax, double * p_dMed )
{
	double		dDato;
	int			iNumElems;
	SElemento *	p_elmObj;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		if ( ES_VALIDO ( p_dMin ) )
		{
			if ( ES_VALIDO ( p_dMax ) )
			{
				if ( ES_VALIDO ( p_dMed ) )
				{
					*p_dMin = DBL_MAX;
					*p_dMax = -DBL_MAX;
					*p_dMed = 0.0;
					iNumElems = SLisRealdNumElementos ( p_lisObj );
					p_elmObj = SLisElemento ( p_lisObj->p_lisDatos, 0 );
					while ( ES_VALIDO ( p_elmObj ) )
					{
						dDato = SElmRealDoble ( p_elmObj );
						if ( dDato > *p_dMax )
						{
							*p_dMax = dDato;
						}
						if ( dDato < *p_dMin )
						{
							*p_dMin = dDato;
						}
						*p_dMed = *p_dMed + dDato;
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

/* Con tolerancia: definida si todos son mayores que 0 ( MatEsMayor ), y
   semidefinida si ninguno es menor ( MatEsMenor ), de modo que un valor casi
   cero cuenta como cero. */
int SLisRealdDefinidaPositiva ( SListaRealesDobles * p_lisObj )
{
	int			iRes;
	SElemento *	p_elmObj;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iRes = 1;
		p_elmObj = SLisElemento ( p_lisObj->p_lisDatos, 0 );
		while ( ES_VALIDO ( p_elmObj ) && ( iRes == 1 ) )
		{
			if ( MatEsMayor ( SElmRealDoble ( p_elmObj ), 0.0 ) == 0 )
			{
				iRes = 0;
			}
			p_elmObj = SElmSucesor ( p_elmObj );
		}
	}
	else
	{
		ERROR_ESTABLECER ( ERR_PARAMETROS );
		iRes = 0;
	}
	return ( iRes );
}

int SLisRealdSemidefinidaPositiva ( SListaRealesDobles * p_lisObj )
{
	int			iRes;
	SElemento *	p_elmObj;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iRes = 1;
		p_elmObj = SLisElemento ( p_lisObj->p_lisDatos, 0 );
		while ( ES_VALIDO ( p_elmObj ) && ( iRes == 1 ) )
		{
			if ( MatEsMenor ( SElmRealDoble ( p_elmObj ), 0.0 ) == 1 )
			{
				iRes = 0;
			}
			p_elmObj = SElmSucesor ( p_elmObj );
		}
	}
	else
	{
		ERROR_ESTABLECER ( ERR_PARAMETROS );
		iRes = 0;
	}
	return ( iRes );
}

/* Copia de los valores, en el mismo orden; NULL si falla alguna copia. */
SListaRealesDobles * SLisRealdDuplicar ( SListaRealesDobles * p_lisObj )
{
	SListaRealesDobles *	p_lisRes;
	SLista *				p_lisDatos;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		p_lisDatos = SLisDuplicar ( p_lisObj->p_lisDatos );
		p_lisRes = SLisRealdEncapsular ( p_lisDatos );
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

/* Operaciones con otras listas. Las que comparan valores van por las de
   arriba, con tolerancia; las que solo mueven o copian, Union incluida,
   delegan en las de SLista. */
int SLisRealdExistenTodos ( SListaRealesDobles * p_lisObj, SListaRealesDobles * p_lisValores )
{
	int	iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		if ( ES_VALIDO ( p_lisValores ) )
		{
			iRes = _SLisRealdExistenTodos ( p_lisObj->p_lisDatos, p_lisValores->p_lisDatos );
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

int SLisRealdExisteAlguno ( SListaRealesDobles * p_lisObj, SListaRealesDobles * p_lisValores )
{
	int	iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		if ( ES_VALIDO ( p_lisValores ) )
		{
			iRes = _SLisRealdExisteAlguno ( p_lisObj->p_lisDatos, p_lisValores->p_lisDatos );
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

int SLisRealdInsertarLista ( SListaRealesDobles * p_lisObj, SListaRealesDobles * p_lisValores )
{
	int	iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		if ( ES_VALIDO ( p_lisValores ) )
		{
			iRes = SLisInsertarLista ( p_lisObj->p_lisDatos, p_lisValores->p_lisDatos );
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

int SLisRealdConcatenarLista ( SListaRealesDobles * p_lisObj, SListaRealesDobles * p_lisValores )
{
	int	iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		if ( ES_VALIDO ( p_lisValores ) )
		{
			iRes = SLisConcatenarLista ( p_lisObj->p_lisDatos, p_lisValores->p_lisDatos );
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

int SLisRealdInsertarListaDup ( SListaRealesDobles * p_lisObj, SListaRealesDobles * p_lisValores )
{
	int	iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		if ( ES_VALIDO ( p_lisValores ) )
		{
			iRes = SLisInsertarListaDup ( p_lisObj->p_lisDatos, p_lisValores->p_lisDatos );
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

int SLisRealdConcatenarListaDup ( SListaRealesDobles * p_lisObj, SListaRealesDobles * p_lisValores )
{
	int	iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		if ( ES_VALIDO ( p_lisValores ) )
		{
			iRes = SLisConcatenarListaDup ( p_lisObj->p_lisDatos, p_lisValores->p_lisDatos );
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

/* Destruye todas las apariciones de cada valor de p_lisValores; ver
   _SLisRealdEliminarLista. */
int SLisRealdEliminarLista ( SListaRealesDobles * p_lisObj, SListaRealesDobles * p_lisValores )
{
	int	iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		if ( ES_VALIDO ( p_lisValores ) )
		{
			iRes = _SLisRealdEliminarLista ( p_lisObj->p_lisDatos, p_lisValores->p_lisDatos );
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

SListaRealesDobles * SLisRealdExtraerLista ( SListaRealesDobles * p_lisObj, SListaRealesDobles * p_lisValores )
{
	SListaRealesDobles *	p_lisRes;
	SLista *				p_lisDatos;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		if ( ES_VALIDO ( p_lisValores ) )
		{
			p_lisDatos = _SLisRealdExtraerLista ( p_lisObj->p_lisDatos, p_lisValores->p_lisDatos );
			p_lisRes = SLisRealdEncapsular ( p_lisDatos );
			if ( ES_NULO ( p_lisRes ) )
			{
				/* No se pierde lo extraido: vuelve al final de p_lisObj. */
				SLisConcatenarLista ( p_lisObj->p_lisDatos, p_lisDatos );
				SLisDestruir ( &p_lisDatos );
			}
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

/* Las que generan una lista nueva la devuelven con COPIAS; si algo falla,
   NULL. La union es la concatenacion de las dos: lo que este en ambas sale
   dos veces. */
SListaRealesDobles * SLisRealdUnion ( SListaRealesDobles * p_lisValores1, SListaRealesDobles * p_lisValores2 )
{
	SListaRealesDobles *	p_lisRes;
	SLista *				p_lisDatos;

	if ( ES_VALIDO ( p_lisValores1 ) )
	{
		if ( ES_VALIDO ( p_lisValores2 ) )
		{
			p_lisDatos = SLisUnion ( p_lisValores1->p_lisDatos, p_lisValores2->p_lisDatos );
			p_lisRes = SLisRealdEncapsular ( p_lisDatos );
			if ( ES_NULO ( p_lisRes ) )
			{
				SLisDestruir ( &p_lisDatos );
			}
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

SListaRealesDobles * SLisRealdInterseccion ( SListaRealesDobles * p_lisValores1, SListaRealesDobles * p_lisValores2 )
{
	SListaRealesDobles *	p_lisRes;
	SLista *				p_lisDatos;

	if ( ES_VALIDO ( p_lisValores1 ) )
	{
		if ( ES_VALIDO ( p_lisValores2 ) )
		{
			p_lisDatos = _SLisRealdInterseccion ( p_lisValores1->p_lisDatos, p_lisValores2->p_lisDatos );
			p_lisRes = SLisRealdEncapsular ( p_lisDatos );
			if ( ES_NULO ( p_lisRes ) )
			{
				SLisDestruir ( &p_lisDatos );
			}
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

SListaRealesDobles * SLisRealdDiferencia ( SListaRealesDobles * p_lisValores1, SListaRealesDobles * p_lisValores2 )
{
	SListaRealesDobles *	p_lisRes;
	SLista *				p_lisDatos;

	if ( ES_VALIDO ( p_lisValores1 ) )
	{
		if ( ES_VALIDO ( p_lisValores2 ) )
		{
			p_lisDatos = _SLisRealdDiferencia ( p_lisValores1->p_lisDatos, p_lisValores2->p_lisDatos );
			p_lisRes = SLisRealdEncapsular ( p_lisDatos );
			if ( ES_NULO ( p_lisRes ) )
			{
				SLisDestruir ( &p_lisDatos );
			}
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

