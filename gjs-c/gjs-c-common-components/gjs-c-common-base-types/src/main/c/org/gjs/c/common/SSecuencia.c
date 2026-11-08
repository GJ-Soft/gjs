#include "SSecuencia.h"


#include "TiposBasicosConfig.h"




SSecuencia * SSecCrear ()
{
	SSecuencia * p_secObj;
	
	p_secObj = (SSecuencia *) MemReservar ( sizeof ( SSecuencia ) );
	if ( ES_VALIDO ( p_secObj ) )
	{
		p_secObj->p_lisDatos = SLisCrear ();
	}
	return ( p_secObj );
}

/* Secuencia con COPIAS de los elementos de p_lisValores, que no se toca. */
SSecuencia * SSecCrearDesdeLista ( SLista * p_lisValores )
{
	SSecuencia *	p_secObj;
	SLista *		p_lisDatos;

	p_lisDatos = SLisDuplicar ( p_lisValores );
	if ( ES_VALIDO ( p_lisDatos ) )
	{
		p_secObj = SSecEncapsularLista ( p_lisDatos );
		if ( ES_NULO ( p_secObj ) )
		{
			SLisDestruir ( &p_lisDatos );
		}
	}
	else
	{
		p_secObj = NULL;
	}
	return ( p_secObj );
}

/* La lista pasa a ser de la secuencia, que la destruye con ella. Si la lista
   no es valida, o no se puede crear la secuencia, devuelve NULL y la lista
   sigue siendo del llamante. */
SSecuencia * SSecEncapsularLista ( SLista * p_lisValores )
{
	SSecuencia * p_secObj;

	if ( SLisEsValida ( p_lisValores ) == 1 )
	{
		p_secObj = (SSecuencia *) MemReservar ( sizeof ( SSecuencia ) );
		if ( ES_VALIDO ( p_secObj ) )
		{
			p_secObj->p_lisDatos = p_lisValores;
		}
	}
	else
	{
		p_secObj = NULL;
	}
	return ( p_secObj );
}

void SSecDestruir ( SSecuencia ** p_p_secObj )
{
	SSecuencia * p_secObj;
	
	if ( ES_VALIDO ( p_p_secObj ) )
	{
		p_secObj = *p_p_secObj;

		if ( ES_VALIDO ( p_secObj ) )
		{
			SLisDestruir ( &(p_secObj->p_lisDatos) );
			MemLiberar ( (void **) p_p_secObj );
		}
	}
}

int SSecEsValida ( SSecuencia * p_secObj )
{
	int iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		iRes = SLisEsValida ( p_secObj->p_lisDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SSecNumElementos ( SSecuencia * p_secObj )
{
	int iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		iRes = SLisNumElementos ( p_secObj->p_lisDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SSecEstaVacia ( SSecuencia * p_secObj )
{
	int iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		iRes = SLisEstaVacia ( p_secObj->p_lisDatos );
	}
	else
	{
		iRes = 1;
	}
	return ( iRes );
}

SElemento * SSecElemento ( SSecuencia * p_secObj, int iElem )
{
	SElemento * p_elmRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		p_elmRes = SLisElemento ( p_secObj->p_lisDatos, iElem );
	}
	else
	{
		p_elmRes = NULL;
	}
	return ( p_elmRes );
}

/* Busquedas por el contenido de p_elmObj, que no hace falta que este en la
   secuencia; delegan en las Elem de SLista. Existe da 1 o 0, Repeticiones
   cuantos iguales hay ( 0 si ninguno ), y Buscar ( que es BuscarPrimero ) y
   BuscarSiguiente la posicion o -1. BuscarSiguiente busca DETRAS de iPos: con
   -1, desde el principio. */
int SSecExiste ( SSecuencia * p_secObj, SElemento * p_elmObj )
{
	int	iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		iRes = SLisExisteElem ( p_secObj->p_lisDatos, p_elmObj );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SSecRepeticiones ( SSecuencia * p_secObj, SElemento * p_elmObj )
{
	int	iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		iRes = SLisRepeticionesElem ( p_secObj->p_lisDatos, p_elmObj );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SSecBuscar ( SSecuencia * p_secObj, SElemento * p_elmObj )
{
	int	iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		iRes = SLisBuscarElem ( p_secObj->p_lisDatos, p_elmObj );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int SSecBuscarPrimero ( SSecuencia * p_secObj, SElemento * p_elmObj )
{
	int	iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		iRes = SLisBuscarPrimeroElem ( p_secObj->p_lisDatos, p_elmObj );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int SSecBuscarSiguiente ( SSecuencia * p_secObj, SElemento * p_elmObj, int iPos )
{
	int	iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		iRes = SLisBuscarSiguienteElem ( p_secObj->p_lisDatos, p_elmObj, iPos );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int SSecInsertar ( SSecuencia * p_secObj, SElemento * p_elmObj )
{
	int iRes;

	if ( ES_VALIDO ( p_secObj ) && ES_VALIDO ( p_elmObj ) )
	{
		iRes = SLisInsertarAlFinal ( p_secObj->p_lisDatos, p_elmObj );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SSecEliminar ( SSecuencia * p_secObj, int iElem )
{
	int	iRes;

	if ( ES_VALIDO ( p_secObj ) ) 
	{
		iRes = SLisEliminarElem ( p_secObj->p_lisDatos, iElem );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

SElemento * SSecExtraer ( SSecuencia * p_secObj, int iElem )
{
	SElemento * p_elmRes;

	if ( ES_VALIDO ( p_secObj ) ) 
	{
		p_elmRes = SLisExtraerElem ( p_secObj->p_lisDatos, iElem );
	}
	else
	{
		p_elmRes = NULL;
	}
	return ( p_elmRes );
}

int SSecVaciar ( SSecuencia * p_secObj )
{
	int	iRes;

	if ( ES_VALIDO ( p_secObj ) ) 
	{
		iRes = SLisVaciar ( p_secObj->p_lisDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

/* Secuencia nueva con copias de los elementos, en el mismo orden. */
SSecuencia * SSecDuplicar ( SSecuencia * p_secObj )
{
	SSecuencia * p_secRes;

	if ( SSecEsValida ( p_secObj ) == 1 )
	{
		p_secRes = SSecCrearDesdeLista ( p_secObj->p_lisDatos );
	}
	else
	{
		p_secRes = NULL;
	}
	return ( p_secRes );
}

SLista * SSecLista ( SSecuencia * p_secObj )
{
	SLista * p_lisRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		p_lisRes = p_secObj->p_lisDatos;
	}
	else
	{
		p_lisRes = NULL;
	}
	return ( p_lisRes );
}

/* Las operaciones con otras secuencias y listas delegan en las de SLista, con
   su misma semantica ( ver Listas.md ); las de secuencia pasan la lista de la
   segunda. Las que crean una secuencia nueva devuelven NULL si la de SLista
   falla, nunca una secuencia sin lista. */
int SSecExistenTodos ( SSecuencia * p_secObj, SSecuencia * p_secValores )
{
	int iRes;

	if ( SSecEsValida ( p_secValores ) == 1 )
	{
		iRes = SSecExistenTodosLista ( p_secObj, p_secValores->p_lisDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SSecExisteAlguno ( SSecuencia * p_secObj, SSecuencia * p_secValores )
{
	int iRes;

	if ( SSecEsValida ( p_secValores ) == 1 )
	{
		iRes = SSecExisteAlgunoLista ( p_secObj, p_secValores->p_lisDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SSecExistenTodosLista ( SSecuencia * p_secObj, SLista * p_lisValores )
{
	int	iRes;

	if ( SSecEsValida ( p_secObj ) == 1 )
	{
		iRes = SLisExistenTodos ( p_secObj->p_lisDatos, p_lisValores );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SSecExisteAlgunoLista ( SSecuencia * p_secObj, SLista * p_lisValores )
{
	int iRes;

	if ( SSecEsValida ( p_secObj ) == 1 )
	{
		iRes = SLisExisteAlguno ( p_secObj->p_lisDatos, p_lisValores );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SSecEliminarSecuencia ( SSecuencia * p_secObj, SSecuencia * p_secValores )
{
	int	iRes;

	if ( SSecEsValida ( p_secValores ) == 1 )
	{
		iRes = SSecEliminarLista ( p_secObj, p_secValores->p_lisDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SSecEliminarLista ( SSecuencia * p_secObj, SLista * p_lisValores )
{
	int iRes;

	if ( SSecEsValida ( p_secObj ) == 1 )
	{
		iRes = SLisEliminarLista ( p_secObj->p_lisDatos, p_lisValores );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SSecConcatenar ( SSecuencia * p_secObj, SSecuencia * p_secValores )
{
	int iRes;

	if ( SSecEsValida ( p_secValores ) == 1 )
	{
		iRes = SSecConcatenarLista ( p_secObj, p_secValores->p_lisDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SSecConcatenarLista ( SSecuencia * p_secObj, SLista * p_lisValores )
{
	int iRes;

	if ( SSecEsValida ( p_secObj ) == 1 )
	{
		iRes = SLisConcatenarLista ( p_secObj->p_lisDatos, p_lisValores );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SSecConcatenarDup ( SSecuencia * p_secObj, SSecuencia * p_secValores )
{
	int iRes;

	if ( SSecEsValida ( p_secValores ) == 1 )
	{
		iRes = SSecConcatenarListaDup ( p_secObj, p_secValores->p_lisDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SSecConcatenarListaDup ( SSecuencia * p_secObj, SLista * p_lisValores )
{
	int iRes;

	if ( SSecEsValida ( p_secObj ) == 1 )
	{
		iRes = SLisConcatenarListaDup ( p_secObj->p_lisDatos, p_lisValores );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

SSecuencia * SSecExtraerSecuencia ( SSecuencia * p_secObj, SSecuencia * p_secValores )
{
	SSecuencia *	p_secRes;

	if ( SSecEsValida ( p_secValores ) == 1 )
	{
		p_secRes = SSecExtraerLista ( p_secObj, p_secValores->p_lisDatos );
	}
	else
	{
		p_secRes = NULL;
	}
	return ( p_secRes );
}

SSecuencia * SSecExtraerLista ( SSecuencia * p_secObj, SLista * p_lisValores )
{
	SSecuencia *	p_secRes;
	SLista *		p_lisDatos;

	if ( SSecEsValida ( p_secObj ) == 1 )
	{
		p_lisDatos = SLisExtraerLista ( p_secObj->p_lisDatos, p_lisValores );
		p_secRes = SSecEncapsularLista ( p_lisDatos );
		if ( ES_NULO ( p_secRes ) )
		{
			/* No se pierde lo extraido: vuelve al final de p_secObj. */
			SLisConcatenarLista ( p_secObj->p_lisDatos, p_lisDatos );
			SLisDestruir ( &p_lisDatos );
		}
	}
	else
	{
		p_secRes = NULL;
	}
	return ( p_secRes );
}

SSecuencia * SSecUnion ( SSecuencia * p_secValores1, SSecuencia * p_secValores2 )
{
	SSecuencia *	p_secRes;

	if ( SSecEsValida ( p_secValores2 ) == 1 )
	{
		p_secRes = SSecUnionLista ( p_secValores1, p_secValores2->p_lisDatos );
	}
	else
	{
		p_secRes = NULL;
	}
	return ( p_secRes );
}

SSecuencia * SSecInterseccion ( SSecuencia * p_secValores1, SSecuencia * p_secValores2 )
{
	SSecuencia *	p_secRes;

	if ( SSecEsValida ( p_secValores2 ) == 1 )
	{
		p_secRes = SSecInterseccionLista ( p_secValores1, p_secValores2->p_lisDatos );
	}
	else
	{
		p_secRes = NULL;
	}
	return ( p_secRes );
}

SSecuencia * SSecDiferencia ( SSecuencia * p_secValores1, SSecuencia * p_secValores2 )
{
	SSecuencia *	p_secRes;

	if ( SSecEsValida ( p_secValores2 ) == 1 )
	{
		p_secRes = SSecDiferenciaLista ( p_secValores1, p_secValores2->p_lisDatos );
	}
	else
	{
		p_secRes = NULL;
	}
	return ( p_secRes );
}

SSecuencia * SSecUnionLista ( SSecuencia * p_secValores1, SLista * p_lisValores2 )
{
	SSecuencia *	p_secRes;
	SLista *		p_lisDatos;

	if ( SSecEsValida ( p_secValores1 ) == 1 )
	{
		p_lisDatos = SLisUnion ( p_secValores1->p_lisDatos, p_lisValores2 );
		p_secRes = SSecEncapsularLista ( p_lisDatos );
		if ( ES_NULO ( p_secRes ) )
		{
			SLisDestruir ( &p_lisDatos );
		}
	}
	else
	{
		p_secRes = NULL;
	}
	return ( p_secRes );
}

SSecuencia * SSecInterseccionLista ( SSecuencia * p_secValores1, SLista * p_lisValores2 )
{
	SSecuencia *	p_secRes;
	SLista *		p_lisDatos;

	if ( SSecEsValida ( p_secValores1 ) == 1 )
	{
		p_lisDatos = SLisInterseccion ( p_secValores1->p_lisDatos, p_lisValores2 );
		p_secRes = SSecEncapsularLista ( p_lisDatos );
		if ( ES_NULO ( p_secRes ) )
		{
			SLisDestruir ( &p_lisDatos );
		}
	}
	else
	{
		p_secRes = NULL;
	}
	return ( p_secRes );
}

SSecuencia * SSecDiferenciaLista ( SSecuencia * p_secValores1, SLista * p_lisValores2 )
{
	SSecuencia *	p_secRes;
	SLista *		p_lisDatos;

	if ( SSecEsValida ( p_secValores1 ) == 1 )
	{
		p_lisDatos = SLisDiferencia ( p_secValores1->p_lisDatos, p_lisValores2 );
		p_secRes = SSecEncapsularLista ( p_lisDatos );
		if ( ES_NULO ( p_secRes ) )
		{
			SLisDestruir ( &p_lisDatos );
		}
	}
	else
	{
		p_secRes = NULL;
	}
	return ( p_secRes );
}

