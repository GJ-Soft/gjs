#include "SListaPtr.h"


#include "TiposBasicosConfig.h"


SElementoPtr * _SLispExtraerElemPtr ( SListaPtr * p_lisObj, int iElem );
SElementoPtr * _SLispExtraerPtr ( SListaPtr * p_lisObj );
int _SLispInsertarElemPtr ( SListaPtr * p_lisObj, int iPosAnt, SElementoPtr * p_elpDatos );
int _SLispInsertarAlInicioPtr ( SListaPtr * p_lisObj, SElementoPtr * p_elpDatos );
int _SLispInsertarAlFinalPtr ( SListaPtr * p_lisObj, SElementoPtr * p_elpDatos );
int _SLispInsertarPtr ( SListaPtr * p_lisObj, SElementoPtr * p_elpDatos );
static SElementoPtr * _SLispLocalizarPosicion ( SListaPtr * p_lisObj, int iPos );
int _SLispInsertarDelantePtr ( SListaPtr * p_lisObj, SElementoPtr * p_elpDatos );
int _SLispInsertarDetrasPtr ( SListaPtr * p_lisObj, SElementoPtr * p_elpDatos );


SListaPtr * SLispCrear ()
{
	SListaPtr * p_lisObj;
	
	p_lisObj = (SListaPtr *) MemReservar ( sizeof ( SListaPtr ) );
	if ( ES_VALIDO ( p_lisObj ) )
	{
		p_lisObj->p_elpPrimero = NULL;
		p_lisObj->p_elpUltimo = NULL;
		p_lisObj->p_elpActual = NULL;
		p_lisObj->iNumElementos = 0;
		p_lisObj->iPos = -1;
		p_lisObj->iLiberar = 1;
	}
	return ( p_lisObj );
}

void SLispDestruir ( SListaPtr ** p_p_lisObj )
{
	SListaPtr * p_lisObj;
	
	if ( ES_VALIDO ( p_p_lisObj ) )
	{
		p_lisObj = *p_p_lisObj;

		if ( ES_VALIDO ( p_lisObj ) )
		{
			SLispVaciar ( p_lisObj );
			MemLiberar ( (void **) p_p_lisObj );
		}
	}
}

int SLispEsValida ( SListaPtr * p_lisObj )
{
	int iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		if ( p_lisObj->iNumElementos > 0 )
		{
			if ( ES_VALIDO ( p_lisObj->p_elpPrimero ) &&
				 ES_VALIDO ( p_lisObj->p_elpUltimo  ) )
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
			if ( ( p_lisObj->p_elpPrimero == NULL ) &&
				 ( p_lisObj->p_elpUltimo == NULL ) &&
				 ( p_lisObj->iPos == -1 ) && 
				 ( p_lisObj->p_elpActual == NULL ) )
			{
				iRes = 1;
			}
			else
			{
				iRes = 0;
			}
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLispNumElementos ( SListaPtr * p_lisObj )
{
	int iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iRes = p_lisObj->iNumElementos;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLispEstaVacia ( SListaPtr * p_lisObj )
{
	int iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		if ( p_lisObj->iNumElementos <= 0 )
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
		iRes = 1;
	}
	return ( iRes );
}

/* Acceso por indice SIN tocar el cursor. Antes se resolvia con SLispMoverA, que
   mueve el cursor de la lista, y eso convertia cualquier consulta —Elemento,
   Min, Max, EstaOrdenada…— en una operacion que le cambiaba la posicion al que
   estuviera iterando.

   Se entra por el extremo mas cercano al indice pedido, asi que una llamada
   suelta cuesta como mucho media lista. OJO: eso hace que recorrer la lista
   ENTERA por indice sea cuadratico, porque ya no se aprovecha la posicion de la
   llamada anterior. Para recorrer de principio a fin hay que usar el cursor
   ( SLispInicio / SLispSiguiente / SLispActual ), no esta. */
byte * SLispElemento ( SListaPtr * p_lisObj, int iElem )
{
	byte *			p_byRes;
	SElementoPtr *	p_elpDatos;
	int				iPos;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		if ( ( iElem >= 0 ) && ( iElem < p_lisObj->iNumElementos ) )
		{
			if ( iElem < p_lisObj->iNumElementos / 2 )
			{
				p_elpDatos = p_lisObj->p_elpPrimero;
				iPos = 0;
				while ( ( iPos < iElem ) && 
						ES_VALIDO ( p_elpDatos ) )
				{
					p_elpDatos = SElpSucesor ( p_elpDatos );
					iPos = iPos + 1;
				}
			}
			else
			{
				p_elpDatos = p_lisObj->p_elpUltimo;
				iPos = p_lisObj->iNumElementos - 1;
				/* > y no >=: con >= se da un paso de mas y se acaba en
				   iElem - 1. La rama de arriba, la que entra por el principio,
				   ya usaba la comparacion estricta. */
				while ( ( iPos > iElem ) &&
						ES_VALIDO ( p_elpDatos ) )
				{
					p_elpDatos = SElpAntecesor ( p_elpDatos );
					iPos = iPos - 1;
				}
			}
			if ( ES_VALIDO ( p_elpDatos ) )
			{
				p_byRes = SElpDatos ( p_elpDatos );
			}
			else
			{
				p_byRes = NULL;
			}
		}
		else
		{
			p_byRes = NULL;
		}
	}
	else
	{
		p_byRes = NULL;
	}
	return ( p_byRes );
}

/* El ELEMENTO en esa posicion, no el dato: para eso esta SLispElemento, que
   devuelve el byte * guardado. Hace falta para poder recorrer la cadena desde
   los tipos que se montan encima —literales, referencias, parejas—, que si no
   tienen que ir por indice y eso sale cuadratico.

   Gemela de SLisElemento en SListaPtr. Como ella, entra por el extremo mas cercano
   y NO toca el cursor. */
SElementoPtr * SLispElementoPtr ( SListaPtr * p_lisObj, int iElem )
{
	SElementoPtr *	p_elpRes;
	int				iPos;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		if ( ( iElem >= 0 ) && ( iElem < p_lisObj->iNumElementos ) )
		{
			if ( iElem < p_lisObj->iNumElementos / 2 )
			{
				p_elpRes = p_lisObj->p_elpPrimero;
				iPos = 0;
				while ( ( iPos < iElem ) && 
						ES_VALIDO ( p_elpRes ) )
				{
					p_elpRes = SElpSucesor ( p_elpRes );
					iPos = iPos + 1;
				}
			}
			else
			{
				p_elpRes = p_lisObj->p_elpUltimo;
				iPos = p_lisObj->iNumElementos - 1;
				while ( ( iPos > iElem ) &&
						ES_VALIDO ( p_elpRes ) )
				{
					p_elpRes = SElpAntecesor ( p_elpRes );
					iPos = iPos - 1;
				}
			}
		}
		else
		{
			p_elpRes = NULL;
		}
	}
	else
	{
		p_elpRes = NULL;
	}
	return ( p_elpRes );
}

int SLispEstablecerElem ( SListaPtr * p_lisObj, int iElem, byte * p_byDatos )
{
	int iRes;

	if ( ( SLispEsValida ( p_lisObj ) == 1 ) && ES_VALIDO ( p_byDatos ) )
	{
		if ( ( iElem >= 0 ) && ( iElem < p_lisObj->iNumElementos ) )
		{
			SLispMoverA ( p_lisObj, iElem );
			iRes = SLispEstablecer ( p_lisObj, p_byDatos ) ;
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


int SLispInsertarElem ( SListaPtr * p_lisObj, int iPosAnt, byte * p_byDatos )
{
	int iRes;

	if ( ( SLispEsValida ( p_lisObj ) == 1 ) && ES_VALIDO ( p_byDatos ) )
	{
		if ( iPosAnt < 0 ) 
		{
			SLispInicio ( p_lisObj );
			iRes = SLispInsertarDelante ( p_lisObj, p_byDatos );
		}
		else if ( iPosAnt >= p_lisObj->iNumElementos )
		{
			SLispFinal ( p_lisObj );
			iRes = SLispInsertarDetras ( p_lisObj, p_byDatos );
		}
		else  
		{
			SLispMoverA ( p_lisObj, iPosAnt );
			if ( ES_NULO ( p_lisObj->p_elpActual ) ) 
			{
				iRes = 0;
			}
			else 
			{
				iRes = SLispInsertar ( p_lisObj, p_byDatos );
			}
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLispInsertarAlInicio ( SListaPtr * p_lisObj, byte * p_byDatos )
{
	return ( SLispInsertarElem ( p_lisObj, -1, p_byDatos ) );
}

int SLispInsertarAlFinal ( SListaPtr * p_lisObj, byte * p_byDatos )
{
	int iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iRes = SLispInsertarElem ( p_lisObj, p_lisObj->iNumElementos, p_byDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLispEliminarElem ( SListaPtr * p_lisObj, int iElem )
{
	int	iRes;

	if ( SLispEsValida ( p_lisObj ) == 1 ) 
	{
		SLispMoverA ( p_lisObj, iElem );
		iRes = SLispEliminar ( p_lisObj );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

byte * SLispExtraerElem ( SListaPtr * p_lisObj, int iElem )
{
	SElementoPtr *	p_elpObj;
	byte *			p_byRes;

	p_elpObj = _SLispExtraerElemPtr ( p_lisObj, iElem );
	if ( ES_VALIDO ( p_elpObj ) ) 
	{
		p_byRes = SElpDatos ( p_elpObj );
		/* Los datos pasan al que llama: se destruye solo el nodo. */
		p_elpObj->iLiberar = 0;
		SElpDestruir ( &p_elpObj );
	}
	else
	{
		p_byRes = NULL;
	}
	return ( p_byRes );
}

int SLispVaciar ( SListaPtr * p_lisObj )
{
	int	iRes;

	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		iRes = 1;
		while ( ( p_lisObj->iNumElementos > 0 ) && ( iRes == 1 ) )
		{
			SLispInicio ( p_lisObj );
			iRes = SLispEliminar ( p_lisObj );
		}
		p_lisObj->iPos = -1;
		p_lisObj->p_elpActual = NULL;
		if ( iRes == 1 )
		{
			p_lisObj->p_elpPrimero = NULL;
			p_lisObj->p_elpUltimo = NULL;
		}
		else
		{
			SLispInicio ( p_lisObj );
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLispPosicion ( SListaPtr * p_lisObj )
{
	int	iRes;

	if ( SLispEsValida ( p_lisObj ) == 1 ) 
	{
		iRes = p_lisObj->iPos;
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

byte * SLispActual ( SListaPtr * p_lisObj )
{
	byte *			p_byRes;
	SElementoPtr *	p_elpDatos;

	if ( SLispEsValida ( p_lisObj ) == 1 ) 
	{
		p_elpDatos = p_lisObj->p_elpActual;
		if ( ES_VALIDO ( p_elpDatos ) )
		{
			p_byRes = SElpDatos ( p_elpDatos );
		}
		else
		{
			ERROR_ESTABLECER( ERR_POSICION_INVALIDA );
			p_byRes = NULL;
		}
	}
	else
	{
		p_byRes = NULL;
	}
	return ( p_byRes );
}

SElementoPtr * SLispActualPtr ( SListaPtr * p_lisObj )
{
	SElementoPtr *	p_elpRes;

	if ( SLispEsValida ( p_lisObj ) == 1 ) 
	{
		p_elpRes = p_lisObj->p_elpActual;
	}
	else
	{
		p_elpRes = NULL;
	}
	return ( p_elpRes );
}

/* 1 si el cursor esta sobre un elemento; 0 si no, o si la lista no es valida. */
int SLispEstaPosicionada ( SListaPtr * p_lisObj )
{
	int iRes;

	if ( SLispEsValida ( p_lisObj ) == 1 )
	{
		if ( ES_VALIDO ( p_lisObj->p_elpActual ) )
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

void SLispInicio ( SListaPtr * p_lisObj )
{
	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		if ( p_lisObj->iNumElementos > 0 )
		{
			p_lisObj->iPos = 0;
			p_lisObj->p_elpActual = p_lisObj->p_elpPrimero;
		}
		else
		{
			p_lisObj->iPos = -1;
			p_lisObj->p_elpActual = NULL;
		}
	}
}

void SLispFinal ( SListaPtr * p_lisObj )
{
	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		if ( p_lisObj->iNumElementos > 0 )
		{
			p_lisObj->iPos = p_lisObj->iNumElementos - 1;
			p_lisObj->p_elpActual = p_lisObj->p_elpUltimo;
		}
		else
		{
			p_lisObj->iPos = -1;
			p_lisObj->p_elpActual = NULL;
		}
	}
}

void SLispSiguiente ( SListaPtr * p_lisObj )
{
	if ( SLispEsValida ( p_lisObj ) == 1 ) 
	{
		if ( ES_VALIDO ( p_lisObj->p_elpActual ) )
		{
			p_lisObj->iPos = p_lisObj->iPos + 1;
			p_lisObj->p_elpActual = SElpSucesor ( p_lisObj->p_elpActual );
		}
		else
		{
			p_lisObj->iPos = -1;
			p_lisObj->p_elpActual = NULL;
		}
	}
}

void SLispAnterior ( SListaPtr * p_lisObj )
{
	if ( SLispEsValida ( p_lisObj ) == 1 ) 
	{
		if ( ES_VALIDO ( p_lisObj->p_elpActual ) )
		{
			p_lisObj->iPos = p_lisObj->iPos - 1;
			p_lisObj->p_elpActual = SElpAntecesor ( p_lisObj->p_elpActual );
		}
		else
		{
			p_lisObj->iPos = -1;
			p_lisObj->p_elpActual = NULL;
		}
	}
}

void SLispMoverA ( SListaPtr * p_lisObj, int iElem )
{
	if ( ES_VALIDO ( p_lisObj ) )
	{
		if ( ( iElem >= 0 ) && ( iElem < p_lisObj->iNumElementos ) )
		{
			if ( ES_VALIDO ( p_lisObj->p_elpActual ) && 
				 ( p_lisObj->iPos >= 0 ) && 
				 ( p_lisObj->iPos < p_lisObj->iNumElementos ) )
			{
				while ( ( iElem > p_lisObj->iPos ) &&
						ES_VALIDO ( p_lisObj->p_elpActual ) )
				{
					p_lisObj->p_elpActual = SElpSucesor ( p_lisObj->p_elpActual );
					p_lisObj->iPos = p_lisObj->iPos + 1;
				}

				while ( ( iElem < p_lisObj->iPos ) && 
						ES_VALIDO ( p_lisObj->p_elpActual ) )
				{
					p_lisObj->p_elpActual = SElpAntecesor ( p_lisObj->p_elpActual );
					p_lisObj->iPos = p_lisObj->iPos - 1;
				}
			}
			else
			{
				if ( iElem < p_lisObj->iNumElementos / 2 )
				{
					p_lisObj->p_elpActual = p_lisObj->p_elpPrimero;
					p_lisObj->iPos = 0;
					while ( ( p_lisObj->iPos < iElem ) && 
							ES_VALIDO ( p_lisObj->p_elpActual ) )
					{
						p_lisObj->p_elpActual = SElpSucesor ( p_lisObj->p_elpActual );
						p_lisObj->iPos = p_lisObj->iPos + 1;
					}
				}
				else
				{
					p_lisObj->p_elpActual = p_lisObj->p_elpUltimo;
					p_lisObj->iPos = p_lisObj->iNumElementos - 1;
					/* > y no >=: con >= se da un paso de mas y se acaba en
					   iElem - 1. La rama de arriba, la que entra por el principio,
					   ya usaba la comparacion estricta. */
					while ( ( p_lisObj->iPos > iElem ) &&
							ES_VALIDO ( p_lisObj->p_elpActual ) )
					{
						p_lisObj->p_elpActual = SElpAntecesor ( p_lisObj->p_elpActual );
						p_lisObj->iPos = p_lisObj->iPos - 1;
					}
				}
			}
		}
		else
		{
			p_lisObj->iPos = -1;
			p_lisObj->p_elpActual = NULL;
		}
	}
}

void SLispDeposicionar ( SListaPtr * p_lisObj )
{
	if ( ES_VALIDO ( p_lisObj ) )
	{
		p_lisObj->iPos = -1;
		p_lisObj->p_elpActual = NULL;
	}
}

/* Existe: 1 si hay algun dato igual y 0 si no, tambien con una lista o un dato
   no validos. Comparan iNumBytes, o con fSonIguales en las Ext; las Ptr, con
   los datos de un elemento, que no hace falta que este en la lista. */
int SLispExiste ( SListaPtr * p_lisObj, byte * p_byDatos, int iNumBytes )
{
	int	iRes;

	if ( SLispBuscarPrimero ( p_lisObj, p_byDatos, iNumBytes ) >= 0 )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLispExistePtr ( SListaPtr * p_lisObj, SElementoPtr * p_elpDatos, int iNumBytes )
{
	int	iRes;

	if ( SLispBuscarPrimeroPtr ( p_lisObj, p_elpDatos, iNumBytes ) >= 0 )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLispExisteExt ( SListaPtr * p_lisObj, byte * p_byDatos, PFUNINTPBPB fSonIguales )
{
	int	iRes;

	if ( SLispBuscarPrimeroExt ( p_lisObj, p_byDatos, fSonIguales ) >= 0 )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLispExisteExtPtr ( SListaPtr * p_lisObj, SElementoPtr * p_elpDatos, PFUNINTPBPB fSonIguales )
{
	int	iRes;

	if ( SLispBuscarPrimeroExtPtr ( p_lisObj, p_elpDatos, fSonIguales ) >= 0 )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

/* Repeticiones: cuantos datos iguales hay; 0 si ninguno, tambien con una lista,
   un dato o una funcion no validos. Recorren la cadena una sola vez. */
int SLispRepeticiones ( SListaPtr * p_lisObj, byte * p_byDatos, int iNumBytes )
{
	SElementoPtr *	p_elpObj;
	int				iRes;

	iRes = 0;
	if ( SLispEsValida ( p_lisObj ) == 1 )
	{
		if ( ES_VALIDO ( p_byDatos ) )
		{
			p_elpObj = p_lisObj->p_elpPrimero;
			while ( ES_VALIDO ( p_elpObj ) )
			{
				if ( SElpEsIgualDatos ( p_elpObj, p_byDatos, iNumBytes ) == 1 )
				{
					iRes = iRes + 1;
				}
				p_elpObj = SElpSucesor ( p_elpObj );
			}
		}
	}
	return ( iRes );
}

int SLispRepeticionesPtr ( SListaPtr * p_lisObj, SElementoPtr * p_elpDatos, int iNumBytes )
{
	int	iRes;

	if ( ES_VALIDO ( p_elpDatos ) )
	{
		iRes = SLispRepeticiones ( p_lisObj, SElpDatos ( p_elpDatos ), iNumBytes );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLispRepeticionesExt ( SListaPtr * p_lisObj, byte * p_byDatos, PFUNINTPBPB fSonIguales )
{
	SElementoPtr *	p_elpObj;
	int				iRes;

	iRes = 0;
	if ( SLispEsValida ( p_lisObj ) == 1 )
	{
		if ( ES_VALIDO ( p_byDatos ) )
		{
			p_elpObj = p_lisObj->p_elpPrimero;
			while ( ES_VALIDO ( p_elpObj ) )
			{
				if ( SElpEsIgualDatosExt ( p_elpObj, p_byDatos, fSonIguales ) == 1 )
				{
					iRes = iRes + 1;
				}
				p_elpObj = SElpSucesor ( p_elpObj );
			}
		}
	}
	return ( iRes );
}

int SLispRepeticionesExtPtr ( SListaPtr * p_lisObj, SElementoPtr * p_elpDatos, PFUNINTPBPB fSonIguales )
{
	int	iRes;

	if ( ES_VALIDO ( p_elpDatos ) )
	{
		iRes = SLispRepeticionesExt ( p_lisObj, SElpDatos ( p_elpDatos ), fSonIguales );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

/* Buscar es BuscarPrimero: posicion del primer dato igual, o -1. */
int SLispBuscar ( SListaPtr * p_lisObj, byte * p_byDatos, int iNumBytes )
{
	return ( SLispBuscarPrimero ( p_lisObj, p_byDatos, iNumBytes ) );
}

int SLispBuscarPtr ( SListaPtr * p_lisObj, SElementoPtr * p_elpDatos, int iNumBytes )
{
	return ( SLispBuscarPrimeroPtr ( p_lisObj, p_elpDatos, iNumBytes ) );
}

int SLispBuscarExt ( SListaPtr * p_lisObj, byte * p_byDatos, PFUNINTPBPB fSonIguales )
{
	return ( SLispBuscarPrimeroExt ( p_lisObj, p_byDatos, fSonIguales ) );
}

int SLispBuscarExtPtr ( SListaPtr * p_lisObj, SElementoPtr * p_elpDatos, PFUNINTPBPB fSonIguales )
{
	return ( SLispBuscarPrimeroExtPtr ( p_lisObj, p_elpDatos, fSonIguales ) );
}

int SLispBuscarPrimero ( SListaPtr * p_lisObj, byte * p_byDatos, int iNumBytes )
{
	return ( SLispBuscarSiguiente ( p_lisObj, p_byDatos, -1, iNumBytes ) );
}

int SLispBuscarPrimeroPtr ( SListaPtr * p_lisObj, SElementoPtr * p_elpDatos, int iNumBytes )
{
	return ( SLispBuscarSiguientePtr ( p_lisObj, p_elpDatos, -1, iNumBytes ) );
}

int SLispBuscarPrimeroExt ( SListaPtr * p_lisObj, byte * p_byDatos, PFUNINTPBPB fSonIguales )
{
	return ( SLispBuscarSiguienteExt ( p_lisObj, p_byDatos, -1, fSonIguales ) );
}

int SLispBuscarPrimeroExtPtr ( SListaPtr * p_lisObj, SElementoPtr * p_elpDatos, PFUNINTPBPB fSonIguales )
{
	return ( SLispBuscarSiguienteExtPtr ( p_lisObj, p_elpDatos, -1, fSonIguales ) );
}

/* Posicion del siguiente dato igual DETRAS de iPos, o -1 si no hay mas. Con
   iPos = -1 se busca desde el principio, y un iPos menor da -1. No mueve el
   cursor. Para recorrer los repetidos:

	   iPos = SLispBuscarPrimero ( p_lisObj, p_byDatos, iNumBytes );
	   while ( iPos >= 0 )
	   {
		   ...
		   iPos = SLispBuscarSiguiente ( p_lisObj, p_byDatos, iPos, iNumBytes );
	   }

   Las Ptr buscan con los datos del elemento; sin elemento devuelven -1. */
int SLispBuscarSiguiente ( SListaPtr * p_lisObj, byte * p_byDatos, int iPos, int iNumBytes )
{
	int				iRes;
	int				iEnc;
	SElementoPtr *	p_elpObj;

	if ( ( SLispEsValida ( p_lisObj ) == 1 ) && ES_VALIDO ( p_byDatos ) && ( iPos >= -1 ) )
	{
		iRes = iPos + 1;
		p_elpObj = _SLispLocalizarPosicion ( p_lisObj, iRes );
		iEnc = 0;
		while ( ( iRes < p_lisObj->iNumElementos ) && ( iEnc == 0 ) &&
			ES_VALIDO ( p_elpObj ) )
		{
			iEnc = SElpEsIgualDatos ( p_elpObj, p_byDatos, iNumBytes );
			if ( iEnc == 0 )
			{
				p_elpObj = SElpSucesor ( p_elpObj );
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

int SLispBuscarSiguientePtr ( SListaPtr * p_lisObj, SElementoPtr * p_elpDatos, int iPos, int iNumBytes )
{
	int	iRes;

	if ( ES_VALIDO ( p_elpDatos ) )
	{
		iRes = SLispBuscarSiguiente ( p_lisObj, SElpDatos ( p_elpDatos ), iPos, iNumBytes );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int SLispBuscarSiguienteExt ( SListaPtr * p_lisObj, byte * p_byDatos, int iPos, PFUNINTPBPB fSonIguales )
{
	int				iRes;
	int				iEnc;
	SElementoPtr *	p_elpObj;

	if ( ( SLispEsValida ( p_lisObj ) == 1 ) && ES_VALIDO ( p_byDatos ) && ES_VALIDO ( fSonIguales ) &&
		 ( iPos >= -1 ) )
	{
		iRes = iPos + 1;
		p_elpObj = _SLispLocalizarPosicion ( p_lisObj, iRes );
		iEnc = 0;
		while ( ( iRes < p_lisObj->iNumElementos ) && ( iEnc == 0 ) &&
			ES_VALIDO ( p_elpObj ) )
		{
			iEnc = SElpEsIgualDatosExt ( p_elpObj, p_byDatos, fSonIguales );
			if ( iEnc == 0 )
			{
				p_elpObj = SElpSucesor ( p_elpObj );
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

int SLispBuscarSiguienteExtPtr ( SListaPtr * p_lisObj, SElementoPtr * p_elpDatos, int iPos, PFUNINTPBPB fSonIguales )
{
	int	iRes;

	if ( ES_VALIDO ( p_elpDatos ) )
	{
		iRes = SLispBuscarSiguienteExt ( p_lisObj, SElpDatos ( p_elpDatos ), iPos, fSonIguales );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int SLispEsNulo ( SListaPtr * p_lisObj )
{
	int iRes;

	if ( SLispEsValida ( p_lisObj ) == 1 ) 
	{
		if ( ES_VALIDO ( p_lisObj->p_elpActual ) )
		{
			iRes = 0;
		}
		else
		{
			iRes = 1;
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLispEstaEnFinal ( SListaPtr * p_lisObj )
{
	int iRes;

	if ( SLispEsValida ( p_lisObj ) == 1 ) 
	{
		if ( ES_VALIDO ( p_lisObj->p_elpActual ) && 
			 ( p_lisObj->iPos == p_lisObj->iNumElementos - 1 ) )
		{
			iRes = 1;
		}
		else if ( ( p_lisObj->iNumElementos == 0 ) && ( p_lisObj->iPos == -1 ) )
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

int SLispEstaEnInicio ( SListaPtr * p_lisObj )
{
	int iRes;

	if ( SLispEsValida ( p_lisObj ) == 1 ) 
	{
		if ( ES_VALIDO ( p_lisObj->p_elpActual ) && ( p_lisObj->iPos == 0 ) )
		{
			iRes = 1;
		}
		else if ( ( p_lisObj->iNumElementos == 0 ) && ( p_lisObj->iPos == -1 ) )
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

int SLispEstablecer ( SListaPtr * p_lisObj, byte * p_byDatos )
{
	int				iRes;
	SElementoPtr *	p_elpObj;

	if ( ( SLispEsValida ( p_lisObj ) == 1 ) && ES_VALIDO ( p_byDatos ) )
	{
		p_elpObj = SElpCrear ( p_byDatos, p_lisObj->iLiberar );
		if ( ES_VALIDO ( p_elpObj ) )
		{
			if ( ( p_lisObj->iPos >= 0 ) && 
			     ( p_lisObj->iPos < p_lisObj->iNumElementos ) && 
				  ES_VALIDO ( p_lisObj->p_elpActual ) )
			{
				SElpEncadenarAntecesor ( p_elpObj, SElpAntecesor ( p_lisObj->p_elpActual )  );
				SElpEncadenarSucesor ( p_elpObj, SElpSucesor ( p_lisObj->p_elpActual ) );
				p_lisObj->p_elpActual->iLiberar = p_lisObj->iLiberar;
				
				if ( p_lisObj->p_elpPrimero == p_lisObj->p_elpActual )
				{
					p_lisObj->p_elpPrimero = p_elpObj;
				}
				if ( p_lisObj->p_elpUltimo == p_lisObj->p_elpActual )
				{
					p_lisObj->p_elpUltimo = p_elpObj;
				}
				SElpDestruir ( &(p_lisObj->p_elpActual) );
				p_lisObj->p_elpActual = p_elpObj;
				iRes = 1;
			}
			else
			{
				iRes = 0;
			}

			if ( iRes == 0 )
			{
				SElpDestruir ( &p_elpObj );
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

int SLispInsertar ( SListaPtr * p_lisObj, byte * p_byDatos )
{
	return ( SLispInsertarDetras ( p_lisObj, p_byDatos ) );
}

int SLispInsertarDelante ( SListaPtr * p_lisObj, byte * p_byDatos )
{
	int				iRes;
	SElementoPtr *	p_elpObj;

	if ( ( SLispEsValida ( p_lisObj ) == 1 ) && ES_VALIDO ( p_byDatos ) )
	{
		p_elpObj = SElpCrear ( p_byDatos, p_lisObj->iLiberar );
		if ( ES_VALIDO ( p_elpObj ) )
		{
			SElpDesencadenar ( p_elpObj );

			if ( p_lisObj->iNumElementos <= 0 )
			{
				p_lisObj->p_elpPrimero = p_elpObj;
				p_lisObj->p_elpUltimo = p_elpObj;
				p_lisObj->iNumElementos = 1;

				SLispInicio ( p_lisObj );
				iRes = 1;
			}
			else if ( ( p_lisObj->iPos >= 0 ) && 
					  ( p_lisObj->iPos < p_lisObj->iNumElementos ) && 
					  ES_VALIDO ( p_lisObj->p_elpActual ) )
			{
				/* Empalme: antiguo antecesor -> p_elpObj -> actual. */
				SElpEncadenarAntecesor ( p_elpObj, SElpAntecesor ( p_lisObj->p_elpActual ) );
				SElpEncadenarAntecesor ( p_lisObj->p_elpActual, p_elpObj );

				if ( p_lisObj->p_elpPrimero == p_lisObj->p_elpActual )
				{
					p_lisObj->p_elpPrimero = p_elpObj;
				}
				p_lisObj->p_elpActual = p_elpObj;

				p_lisObj->iNumElementos = p_lisObj->iNumElementos + 1;
				
				iRes = 1;
			}
			else
			{
				iRes = 0;
			}

			if ( iRes == 0 )
			{
				SElpDestruir ( &p_elpObj );
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

int SLispInsertarDetras ( SListaPtr * p_lisObj, byte * p_byDatos )
{
	int				iRes;
	SElementoPtr *	p_elpObj;

	if ( ( SLispEsValida ( p_lisObj ) == 1 ) && ES_VALIDO ( p_byDatos ) )
	{
		p_elpObj = SElpCrear ( p_byDatos, p_lisObj->iLiberar );
		if ( ES_VALIDO ( p_elpObj ) )
		{
			SElpDesencadenar ( p_elpObj );
			if ( p_lisObj->iNumElementos <= 0 )
			{
				p_lisObj->p_elpPrimero = p_elpObj;
				p_lisObj->p_elpUltimo = p_elpObj;
				p_lisObj->iNumElementos = 1;

				SLispInicio ( p_lisObj );
				iRes = 1;
			}
			else if ( ( p_lisObj->iPos >= 0 ) && 
					  ( p_lisObj->iPos < p_lisObj->iNumElementos ) && 
					  ES_VALIDO ( p_lisObj->p_elpActual ) )
			{
				/* Empalme: actual -> p_elpObj -> antiguo sucesor. */
				SElpEncadenarSucesor ( p_elpObj, SElpSucesor ( p_lisObj->p_elpActual ) );
				SElpEncadenarSucesor ( p_lisObj->p_elpActual, p_elpObj );

				if ( p_lisObj->p_elpUltimo == p_lisObj->p_elpActual )
				{
					p_lisObj->p_elpUltimo = p_elpObj;
				}
				p_lisObj->p_elpActual = p_elpObj;
				p_lisObj->iPos = p_lisObj->iPos + 1;

				p_lisObj->iNumElementos = p_lisObj->iNumElementos + 1;
				
				iRes = 1;
			}
			else
			{
				iRes = 0;
			}

			if ( iRes == 0 )
			{
				SElpDestruir ( &p_elpObj );
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

int SLispEliminar ( SListaPtr * p_lisObj )
{
	int				iRes;
	SElementoPtr *	p_elpAnt;
	SElementoPtr *	p_elpSig;

	if ( SLispEsValida ( p_lisObj ) == 1 ) 
	{
		if ( ( p_lisObj->iPos >= 0 ) && 
			 ( p_lisObj->iPos < p_lisObj->iNumElementos ) && 
			 ES_VALIDO ( p_lisObj->p_elpActual ) )
		{
			p_elpAnt = SElpAntecesor ( p_lisObj->p_elpActual );
			p_elpSig = SElpSucesor ( p_lisObj->p_elpActual );

			p_lisObj->p_elpActual->iLiberar = p_lisObj->iLiberar;
			SElpDestruir ( &(p_lisObj->p_elpActual) );
			p_lisObj->iNumElementos = p_lisObj->iNumElementos - 1;

			if ( ES_VALIDO ( p_elpAnt ) )
			{
				SElpEncadenarSucesor ( p_elpAnt, p_elpSig );
			}
			else
			{
				p_lisObj->p_elpPrimero = p_elpSig;
			}

			if ( p_lisObj->iNumElementos == 0 )
			{
				p_lisObj->p_elpPrimero = NULL;
				p_lisObj->p_elpUltimo = NULL;
				p_lisObj->p_elpActual = NULL;
				p_lisObj->iPos = -1;
			}
			else if ( ES_VALIDO ( p_elpSig ) )
			{
				SElpEncadenarAntecesor ( p_elpSig, p_elpAnt );
				p_lisObj->p_elpActual = p_elpSig;
			}
			else
			{
				p_lisObj->p_elpUltimo = p_elpAnt;
				p_lisObj->p_elpActual = p_elpAnt;
				p_lisObj->iPos = p_lisObj->iPos - 1;
			}
			
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

byte * SLispExtraer ( SListaPtr * p_lisObj )
{
	SElementoPtr *	p_elpObj;
	byte *			p_byRes;

	p_elpObj = _SLispExtraerPtr ( p_lisObj );
	if ( ES_VALIDO ( p_elpObj ) ) 
	{
		p_byRes = SElpDatos ( p_elpObj );
		/* Los datos pasan al que llama: se destruye solo el nodo. */
		p_elpObj->iLiberar = 0;
		SElpDestruir ( &p_elpObj );
	}
	else
	{
		p_byRes = NULL;
	}
	return ( p_byRes );
}

int	SLispLiberacionMemoriaActivada ( SListaPtr * p_lisObj )
{
	int	iRes;

	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		iRes = p_lisObj->iLiberar;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

void SLispActivarLiberacionMemoria ( SListaPtr * p_lisObj )
{
	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		p_lisObj->iLiberar = 1;
	}
}

void SLispDesactivarLiberacionMemoria ( SListaPtr * p_lisObj )
{
	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		p_lisObj->iLiberar = 0;
	}
}

/* Lista nueva con COPIAS del contenido de cada elemento, en el mismo orden y
   duena de ellas ( iLiberar = 1 ): SLispDuplicar copia iNumBytes con
   SElpDuplicar y SLispDuplicarExt usa fDuplicar. p_lisObj no se toca, ni su
   cursor. Si falla alguna copia se destruye lo copiado y se devuelve NULL. */
SListaPtr * SLispDuplicar ( SListaPtr * p_lisObj, int iNumBytes )
{
	SListaPtr *		p_lisRes;
	SElementoPtr *	p_elpObj;
	SElementoPtr *	p_elpNuevo;
	int				iError;

	if ( SLispEsValida ( p_lisObj ) == 1 )
	{
		p_lisRes = SLispCrear ();
		if ( ES_VALIDO ( p_lisRes ) )
		{
			iError = 0;
			p_elpObj = p_lisObj->p_elpPrimero;
			while ( ES_VALIDO ( p_elpObj ) && ( iError == 0 ) )
			{
				p_elpNuevo = SElpDuplicar ( p_elpObj, iNumBytes );
				if ( _SLispInsertarAlFinalPtr ( p_lisRes, p_elpNuevo ) != 1 )
				{
					SElpDestruir ( &p_elpNuevo );
					iError = 1;
				}
				p_elpObj = SElpSucesor ( p_elpObj );
			}
			if ( iError == 1 )
			{
				SLispDestruir ( &p_lisRes );
			}
		}
	}
	else
	{
		p_lisRes = NULL;
	}
	return ( p_lisRes );
}

SListaPtr * SLispDuplicarExt ( SListaPtr * p_lisObj, PFUNPBYTEPB fDuplicar )
{
	SListaPtr *		p_lisRes;
	SElementoPtr *	p_elpObj;
	SElementoPtr *	p_elpNuevo;
	int				iError;

	if ( SLispEsValida ( p_lisObj ) == 1 )
	{
		if ( ES_VALIDO ( fDuplicar ) )
		{
			p_lisRes = SLispCrear ();
			if ( ES_VALIDO ( p_lisRes ) )
			{
				iError = 0;
				p_elpObj = p_lisObj->p_elpPrimero;
				while ( ES_VALIDO ( p_elpObj ) && ( iError == 0 ) )
				{
					p_elpNuevo = SElpDuplicarExt ( p_elpObj, fDuplicar );
					if ( _SLispInsertarAlFinalPtr ( p_lisRes, p_elpNuevo ) != 1 )
					{
						SElpDestruir ( &p_elpNuevo );
						iError = 1;
					}
					p_elpObj = SElpSucesor ( p_elpObj );
				}
				if ( iError == 1 )
				{
					SLispDestruir ( &p_lisRes );
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

/* Operaciones con otras listas.

   Todas recorren la CADENA de p_lisValores, no su cursor ni su indice: asi no se
   le cambia la posicion a quien la este iterando y el recorrido es lineal. Ver
   la nota de SLispElemento.

   Con la lista de valores vacia, ExistenTodos da 1 ( no falta ninguno ) y
   ExisteAlguno da 0. */
int SLispExistenTodos ( SListaPtr * p_lisObj, SListaPtr * p_lisValores, int iNumBytes )
{
	SElementoPtr *	p_elpObj;
	int				iRes;

	if ( SLispEsValida ( p_lisObj ) == 1 )
	{
		if ( SLispEsValida ( p_lisValores ) == 1 )
		{
			iRes = 1;
			p_elpObj = p_lisValores->p_elpPrimero;
			while ( ES_VALIDO ( p_elpObj ) && ( iRes == 1 ) )
			{
				/* SLispBuscar da la posicion o -1, no un booleano. */
				if ( SLispBuscar ( p_lisObj, SElpDatos ( p_elpObj ), iNumBytes ) < 0 )
				{
					iRes = 0;
				}
				p_elpObj = SElpSucesor ( p_elpObj );
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

int SLispExisteAlguno ( SListaPtr * p_lisObj, SListaPtr * p_lisValores, int iNumBytes )
{
	SElementoPtr *	p_elpObj;
	int				iRes;

	if ( SLispEsValida ( p_lisObj ) == 1 )
	{
		if ( SLispEsValida ( p_lisValores ) == 1 )
		{
			iRes = 0;
			p_elpObj = p_lisValores->p_elpPrimero;
			while ( ES_VALIDO ( p_elpObj ) && ( iRes == 0 ) )
			{
				if ( SLispBuscar ( p_lisObj, SElpDatos ( p_elpObj ), iNumBytes ) >= 0 )
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
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLispExistenTodosExt ( SListaPtr * p_lisObj, SListaPtr * p_lisValores, PFUNINTPBPB fSonIguales )
{
	SElementoPtr *	p_elpObj;
	int				iRes;

	if ( SLispEsValida ( p_lisObj ) == 1 )
	{
		if ( SLispEsValida ( p_lisValores ) == 1 )
		{
			if ( ES_VALIDO ( fSonIguales ) )
			{
				iRes = 1;
				p_elpObj = p_lisValores->p_elpPrimero;
				while ( ES_VALIDO ( p_elpObj ) && ( iRes == 1 ) )
				{
					if ( SLispBuscarExt ( p_lisObj, SElpDatos ( p_elpObj ), fSonIguales ) < 0 )
					{
						iRes = 0;
					}
					p_elpObj = SElpSucesor ( p_elpObj );
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

int SLispExisteAlgunoExt ( SListaPtr * p_lisObj, SListaPtr * p_lisValores, PFUNINTPBPB fSonIguales )
{
	SElementoPtr *	p_elpObj;
	int				iRes;

	if ( SLispEsValida ( p_lisObj ) == 1 )
	{
		if ( SLispEsValida ( p_lisValores ) == 1 )
		{
			if ( ES_VALIDO ( fSonIguales ) )
			{
				iRes = 0;
				p_elpObj = p_lisValores->p_elpPrimero;
				while ( ES_VALIDO ( p_elpObj ) && ( iRes == 0 ) )
				{
					if ( SLispBuscarExt ( p_lisObj, SElpDatos ( p_elpObj ), fSonIguales ) >= 0 )
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

/* Elimina ( destruye ) de p_lisObj la primera aparicion de cada valor de
   p_lisValores: un valor repetido en p_lisValores elimina dos apariciones. Lo
   que no se encuentra se ignora. p_lisValores no se toca.

   Devuelve 1 si ha podido eliminar todo lo encontrado; si falla una eliminacion
   se para y devuelve 0, y lo eliminado hasta ahi se queda eliminado. Con la
   misma lista en los dos argumentos se devuelve 0 sin tocar nada: se
   destruirian los elementos que se estan recorriendo.

   Los datos se liberan o no segun la liberacion de p_lisObj. */
int SLispEliminarLista ( SListaPtr * p_lisObj, SListaPtr * p_lisValores, int iNumBytes )
{
	SElementoPtr *	p_elpObj;
	int				iPos;
	int				iRes;

	if ( SLispEsValida ( p_lisObj ) == 1 )
	{
		if ( SLispEsValida ( p_lisValores ) == 1 )
		{
			if ( p_lisObj != p_lisValores )
			{
				iRes = 1;
				p_elpObj = p_lisValores->p_elpPrimero;
				while ( ES_VALIDO ( p_elpObj ) && ( iRes == 1 ) )
				{
					iPos = SLispBuscar ( p_lisObj, SElpDatos ( p_elpObj ), iNumBytes );
					if ( iPos >= 0 )
					{
						if ( SLispEliminarElem ( p_lisObj, iPos ) != 1 )
						{
							iRes = 0;
						}
					}
					p_elpObj = SElpSucesor ( p_elpObj );
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

/* Como SLispEliminarLista, comparando con fSonIguales. Sin funcion de
   comparacion devuelve 0 sin tocar nada. */
int SLispEliminarListaExt ( SListaPtr * p_lisObj, SListaPtr * p_lisValores, PFUNINTPBPB fSonIguales )
{
	SElementoPtr *	p_elpObj;
	int				iPos;
	int				iRes;

	if ( SLispEsValida ( p_lisObj ) == 1 )
	{
		if ( SLispEsValida ( p_lisValores ) == 1 )
		{
			if ( ES_VALIDO ( fSonIguales ) )
			{
				if ( p_lisObj != p_lisValores )
				{
					iRes = 1;
					p_elpObj = p_lisValores->p_elpPrimero;
					while ( ES_VALIDO ( p_elpObj ) && ( iRes == 1 ) )
					{
						iPos = SLispBuscarExt ( p_lisObj, SElpDatos ( p_elpObj ), fSonIguales );
						if ( iPos >= 0 )
						{
							if ( SLispEliminarElem ( p_lisObj, iPos ) != 1 )
							{
								iRes = 0;
							}
						}
						p_elpObj = SElpSucesor ( p_elpObj );
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
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

/* MUEVE los nodos de p_lisValores a p_lisObj, detras del cursor y en su orden;
   p_lisValores queda vacia. Los datos pasan a ser de p_lisObj, que los libera
   segun SU liberacion de memoria, no la de la lista de la que vienen.

   Si un nodo no se puede insertar ( p_lisObj no vacia y sin cursor ) se devuelve
   a la cabeza de p_lisValores y se para: lo movido hasta ahi se queda movido y
   lo que falta sigue en p_lisValores, sin perder nada.

   Con la misma lista en los dos argumentos se devuelve 0 sin tocar nada: la
   lista se iria vaciando y llenando a la vez. */
int SLispInsertarLista ( SListaPtr * p_lisObj, SListaPtr * p_lisValores )
{
	SElementoPtr *	p_elpObj;
	int				iRes;

	if ( SLispEsValida ( p_lisObj ) == 1 )
	{
		if ( SLispEsValida ( p_lisValores ) == 1 )
		{
			if ( p_lisObj != p_lisValores )
			{
				iRes = 1;
				while ( ( iRes == 1 ) && ( p_lisValores->iNumElementos > 0 ) )
				{
					SLispInicio ( p_lisValores );
					p_elpObj = _SLispExtraerPtr ( p_lisValores );
					if ( ES_VALIDO ( p_elpObj ) )
					{
						if ( _SLispInsertarPtr ( p_lisObj, p_elpObj ) != 1 )
						{
							_SLispInsertarAlInicioPtr ( p_lisValores, p_elpObj );
							iRes = 0;
						}
					}
					else
					{
						iRes = 0;
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
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

/* Como SLispInsertarLista, pero al final de p_lisObj: no depende del cursor. */
int SLispConcatenarLista ( SListaPtr * p_lisObj, SListaPtr * p_lisValores )
{
	SElementoPtr *	p_elpObj;
	int				iRes;

	if ( SLispEsValida ( p_lisObj ) == 1 )
	{
		if ( SLispEsValida ( p_lisValores ) == 1 )
		{
			if ( p_lisObj != p_lisValores )
			{
				iRes = 1;
				while ( ( iRes == 1 ) && ( p_lisValores->iNumElementos > 0 ) )
				{
					SLispInicio ( p_lisValores );
					p_elpObj = _SLispExtraerPtr ( p_lisValores );
					if ( ES_VALIDO ( p_elpObj ) )
					{
						if ( _SLispInsertarAlFinalPtr ( p_lisObj, p_elpObj ) != 1 )
						{
							_SLispInsertarAlInicioPtr ( p_lisValores, p_elpObj );
							iRes = 0;
						}
					}
					else
					{
						iRes = 0;
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
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

/* Las Dup insertan COPIAS del contenido ( SElpDuplicar / SElpDuplicarExt ) y no
   tocan p_lisValores. Las copias son memoria nueva: p_lisObj deberia tener la
   liberacion activada, o se quedan sin liberar.

   Con la misma lista en los dos argumentos se devuelve 0: se insertaria en la
   cadena que se esta recorriendo. Si falla una copia o una insercion se para,
   y lo insertado hasta ahi se queda. */
int SLispInsertarListaDup ( SListaPtr * p_lisObj, SListaPtr * p_lisValores, int iNumBytes )
{
	SElementoPtr *	p_elpObj;
	SElementoPtr *	p_elpNuevo;
	int				iRes;

	if ( SLispEsValida ( p_lisObj ) == 1 )
	{
		if ( SLispEsValida ( p_lisValores ) == 1 )
		{
			if ( p_lisObj != p_lisValores )
			{
				iRes = 1;
				p_elpObj = p_lisValores->p_elpPrimero;
				while ( ES_VALIDO ( p_elpObj ) && ( iRes == 1 ) )
				{
					p_elpNuevo = SElpDuplicar ( p_elpObj, iNumBytes );
					if ( _SLispInsertarPtr ( p_lisObj, p_elpNuevo ) != 1 )
					{
						SElpDestruir ( &p_elpNuevo );
						iRes = 0;
					}
					p_elpObj = SElpSucesor ( p_elpObj );
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

int SLispConcatenarListaDup ( SListaPtr * p_lisObj, SListaPtr * p_lisValores, int iNumBytes )
{
	SElementoPtr *	p_elpObj;
	SElementoPtr *	p_elpNuevo;
	int				iRes;

	if ( SLispEsValida ( p_lisObj ) == 1 )
	{
		if ( SLispEsValida ( p_lisValores ) == 1 )
		{
			if ( p_lisObj != p_lisValores )
			{
				iRes = 1;
				p_elpObj = p_lisValores->p_elpPrimero;
				while ( ES_VALIDO ( p_elpObj ) && ( iRes == 1 ) )
				{
					p_elpNuevo = SElpDuplicar ( p_elpObj, iNumBytes );
					if ( _SLispInsertarAlFinalPtr ( p_lisObj, p_elpNuevo ) != 1 )
					{
						SElpDestruir ( &p_elpNuevo );
						iRes = 0;
					}
					p_elpObj = SElpSucesor ( p_elpObj );
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

int SLispInsertarListaDupExt ( SListaPtr * p_lisObj, SListaPtr * p_lisValores, PFUNPBYTEPB fDuplicar )
{
	SElementoPtr *	p_elpObj;
	SElementoPtr *	p_elpNuevo;
	int				iRes;

	if ( SLispEsValida ( p_lisObj ) == 1 )
	{
		if ( SLispEsValida ( p_lisValores ) == 1 )
		{
			if ( ES_VALIDO ( fDuplicar ) )
			{
				if ( p_lisObj != p_lisValores )
				{
					iRes = 1;
					p_elpObj = p_lisValores->p_elpPrimero;
					while ( ES_VALIDO ( p_elpObj ) && ( iRes == 1 ) )
					{
						p_elpNuevo = SElpDuplicarExt ( p_elpObj, fDuplicar );
						if ( _SLispInsertarPtr ( p_lisObj, p_elpNuevo ) != 1 )
						{
							SElpDestruir ( &p_elpNuevo );
							iRes = 0;
						}
						p_elpObj = SElpSucesor ( p_elpObj );
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
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLispConcatenarListaDupExt ( SListaPtr * p_lisObj, SListaPtr * p_lisValores, PFUNPBYTEPB fDuplicar )
{
	SElementoPtr *	p_elpObj;
	SElementoPtr *	p_elpNuevo;
	int				iRes;

	if ( SLispEsValida ( p_lisObj ) == 1 )
	{
		if ( SLispEsValida ( p_lisValores ) == 1 )
		{
			if ( ES_VALIDO ( fDuplicar ) )
			{
				if ( p_lisObj != p_lisValores )
				{
					iRes = 1;
					p_elpObj = p_lisValores->p_elpPrimero;
					while ( ES_VALIDO ( p_elpObj ) && ( iRes == 1 ) )
					{
						p_elpNuevo = SElpDuplicarExt ( p_elpObj, fDuplicar );
						if ( _SLispInsertarAlFinalPtr ( p_lisObj, p_elpNuevo ) != 1 )
						{
							SElpDestruir ( &p_elpNuevo );
							iRes = 0;
						}
						p_elpObj = SElpSucesor ( p_elpObj );
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
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

/* Saca de p_lisObj, a una lista nueva, la primera aparicion de cada valor de
   p_lisValores, en el orden de p_lisValores: un valor repetido en p_lisValores
   saca dos apariciones. Lo que no se encuentra se ignora.

   Los NODOS se mueven, no se copian, y la lista nueva hereda la liberacion de
   p_lisObj: si p_lisObj no era duena de sus datos, la nueva tampoco.

   Con la misma lista en los dos argumentos se devuelve NULL. */
SListaPtr * SLispExtraerLista ( SListaPtr * p_lisObj, SListaPtr * p_lisValores, int iNumBytes )
{
	SListaPtr *		p_lisRes;
	SElementoPtr *	p_elpObj;
	SElementoPtr *	p_elpExt;
	int				iPos;
	int				iError;

	if ( SLispEsValida ( p_lisObj ) == 1 )
	{
		if ( SLispEsValida ( p_lisValores ) == 1 )
		{
			if ( p_lisObj != p_lisValores )
			{
				p_lisRes = SLispCrear ();
				if ( ES_VALIDO ( p_lisRes ) )
				{
					p_lisRes->iLiberar = p_lisObj->iLiberar;
					iError = 0;
					p_elpObj = p_lisValores->p_elpPrimero;
					while ( ES_VALIDO ( p_elpObj ) && ( iError == 0 ) )
					{
						iPos = SLispBuscar ( p_lisObj, SElpDatos ( p_elpObj ), iNumBytes );
						if ( iPos >= 0 )
						{
							p_elpExt = _SLispExtraerElemPtr ( p_lisObj, iPos );
							if ( _SLispInsertarAlFinalPtr ( p_lisRes, p_elpExt ) != 1 )
							{
								/* No se pierde: vuelve a p_lisObj, aunque al final. */
								_SLispInsertarAlFinalPtr ( p_lisObj, p_elpExt );
								iError = 1;
							}
						}
						p_elpObj = SElpSucesor ( p_elpObj );
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

SListaPtr * SLispExtraerListaExt ( SListaPtr * p_lisObj, SListaPtr * p_lisValores, PFUNINTPBPB fSonIguales )
{
	SListaPtr *		p_lisRes;
	SElementoPtr *	p_elpObj;
	SElementoPtr *	p_elpExt;
	int				iPos;
	int				iError;

	if ( SLispEsValida ( p_lisObj ) == 1 )
	{
		if ( SLispEsValida ( p_lisValores ) == 1 )
		{
			if ( ES_VALIDO ( fSonIguales ) )
			{
				if ( p_lisObj != p_lisValores )
				{
					p_lisRes = SLispCrear ();
					if ( ES_VALIDO ( p_lisRes ) )
					{
						p_lisRes->iLiberar = p_lisObj->iLiberar;
						iError = 0;
						p_elpObj = p_lisValores->p_elpPrimero;
						while ( ES_VALIDO ( p_elpObj ) && ( iError == 0 ) )
						{
							iPos = SLispBuscarExt ( p_lisObj, SElpDatos ( p_elpObj ), fSonIguales );
							if ( iPos >= 0 )
							{
								p_elpExt = _SLispExtraerElemPtr ( p_lisObj, iPos );
								if ( _SLispInsertarAlFinalPtr ( p_lisRes, p_elpExt ) != 1 )
								{
									_SLispInsertarAlFinalPtr ( p_lisObj, p_elpExt );
									iError = 1;
								}
							}
							p_elpObj = SElpSucesor ( p_elpObj );
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
	}
	else
	{
		p_lisRes = NULL;
	}
	return ( p_lisRes );
}

/* Las que generan una lista nueva la devuelven con COPIAS del contenido y la
   liberacion activada; si algo falla, NULL. La union es la concatenacion de las
   dos: lo que este en ambas sale dos veces. */
SListaPtr * SLispUnion ( SListaPtr * p_lisValores1, SListaPtr * p_lisValores2, int iNumBytes )
{
	SListaPtr *	p_lisRes;

	if ( SLispEsValida ( p_lisValores1 ) == 1 )
	{
		if ( SLispEsValida ( p_lisValores2 ) == 1 )
		{
			p_lisRes = SLispCrear ();
			if ( ES_VALIDO ( p_lisRes ) )
			{
				if ( SLispConcatenarListaDup ( p_lisRes, p_lisValores1, iNumBytes ) == 1 )
				{
					if ( SLispConcatenarListaDup ( p_lisRes, p_lisValores2, iNumBytes ) != 1 )
					{
						SLispDestruir ( &p_lisRes );
					}
				}
				else
				{
					SLispDestruir ( &p_lisRes );
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

SListaPtr * SLispUnionExt ( SListaPtr * p_lisValores1, SListaPtr * p_lisValores2, PFUNPBYTEPB fDuplicar )
{
	SListaPtr *	p_lisRes;

	if ( SLispEsValida ( p_lisValores1 ) == 1 )
	{
		if ( SLispEsValida ( p_lisValores2 ) == 1 )
		{
			if ( ES_VALIDO ( fDuplicar ) )
			{
				p_lisRes = SLispCrear ();
				if ( ES_VALIDO ( p_lisRes ) )
				{
					if ( SLispConcatenarListaDupExt ( p_lisRes, p_lisValores1, fDuplicar ) == 1 )
					{
						if ( SLispConcatenarListaDupExt ( p_lisRes, p_lisValores2, fDuplicar ) != 1 )
						{
							SLispDestruir ( &p_lisRes );
						}
					}
					else
					{
						SLispDestruir ( &p_lisRes );
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

/* Los de p_lisValores1 que estan en p_lisValores2, en el orden de p_lisValores1. */
SListaPtr * SLispInterseccion ( SListaPtr * p_lisValores1, SListaPtr * p_lisValores2, int iNumBytes )
{
	SListaPtr *		p_lisRes;
	SElementoPtr *	p_elpObj;
	SElementoPtr *	p_elpNuevo;
	int				iError;

	if ( SLispEsValida ( p_lisValores1 ) == 1 )
	{
		if ( SLispEsValida ( p_lisValores2 ) == 1 )
		{
			p_lisRes = SLispCrear ();
			if ( ES_VALIDO ( p_lisRes ) )
			{
				iError = 0;
				p_elpObj = p_lisValores1->p_elpPrimero;
				while ( ES_VALIDO ( p_elpObj ) && ( iError == 0 ) )
				{
					if ( SLispBuscar ( p_lisValores2, SElpDatos ( p_elpObj ), iNumBytes ) >= 0 )
					{
						p_elpNuevo = SElpDuplicar ( p_elpObj, iNumBytes );
						if ( _SLispInsertarAlFinalPtr ( p_lisRes, p_elpNuevo ) != 1 )
						{
							SElpDestruir ( &p_elpNuevo );
							iError = 1;
						}
					}
					p_elpObj = SElpSucesor ( p_elpObj );
				}
				if ( iError == 1 )
				{
					SLispDestruir ( &p_lisRes );
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

/* Los de p_lisValores1 que NO estan en p_lisValores2, en el orden de p_lisValores1. */
SListaPtr * SLispDiferencia ( SListaPtr * p_lisValores1, SListaPtr * p_lisValores2, int iNumBytes )
{
	SListaPtr *		p_lisRes;
	SElementoPtr *	p_elpObj;
	SElementoPtr *	p_elpNuevo;
	int				iError;

	if ( SLispEsValida ( p_lisValores1 ) == 1 )
	{
		if ( SLispEsValida ( p_lisValores2 ) == 1 )
		{
			p_lisRes = SLispCrear ();
			if ( ES_VALIDO ( p_lisRes ) )
			{
				iError = 0;
				p_elpObj = p_lisValores1->p_elpPrimero;
				while ( ES_VALIDO ( p_elpObj ) && ( iError == 0 ) )
				{
					if ( SLispBuscar ( p_lisValores2, SElpDatos ( p_elpObj ), iNumBytes ) < 0 )
					{
						p_elpNuevo = SElpDuplicar ( p_elpObj, iNumBytes );
						if ( _SLispInsertarAlFinalPtr ( p_lisRes, p_elpNuevo ) != 1 )
						{
							SElpDestruir ( &p_elpNuevo );
							iError = 1;
						}
					}
					p_elpObj = SElpSucesor ( p_elpObj );
				}
				if ( iError == 1 )
				{
					SLispDestruir ( &p_lisRes );
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

SListaPtr * SLispInterseccionExt ( SListaPtr * p_lisValores1, SListaPtr * p_lisValores2, PFUNINTPBPB fSonIguales, PFUNPBYTEPB fDuplicar )
{
	SListaPtr *		p_lisRes;
	SElementoPtr *	p_elpObj;
	SElementoPtr *	p_elpNuevo;
	int				iError;

	if ( SLispEsValida ( p_lisValores1 ) == 1 )
	{
		if ( SLispEsValida ( p_lisValores2 ) == 1 )
		{
			if ( ES_VALIDO ( fSonIguales ) )
			{
				if ( ES_VALIDO ( fDuplicar ) )
				{
					p_lisRes = SLispCrear ();
					if ( ES_VALIDO ( p_lisRes ) )
					{
						iError = 0;
						p_elpObj = p_lisValores1->p_elpPrimero;
						while ( ES_VALIDO ( p_elpObj ) && ( iError == 0 ) )
						{
							if ( SLispBuscarExt ( p_lisValores2, SElpDatos ( p_elpObj ), fSonIguales ) >= 0 )
							{
								p_elpNuevo = SElpDuplicarExt ( p_elpObj, fDuplicar );
								if ( _SLispInsertarAlFinalPtr ( p_lisRes, p_elpNuevo ) != 1 )
								{
									SElpDestruir ( &p_elpNuevo );
									iError = 1;
								}
							}
							p_elpObj = SElpSucesor ( p_elpObj );
						}
						if ( iError == 1 )
						{
							SLispDestruir ( &p_lisRes );
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
	}
	else
	{
		p_lisRes = NULL;
	}
	return ( p_lisRes );
}

SListaPtr * SLispDiferenciaExt ( SListaPtr * p_lisValores1, SListaPtr * p_lisValores2, PFUNINTPBPB fSonIguales, PFUNPBYTEPB fDuplicar )
{
	SListaPtr *		p_lisRes;
	SElementoPtr *	p_elpObj;
	SElementoPtr *	p_elpNuevo;
	int				iError;

	if ( SLispEsValida ( p_lisValores1 ) == 1 )
	{
		if ( SLispEsValida ( p_lisValores2 ) == 1 )
		{
			if ( ES_VALIDO ( fSonIguales ) )
			{
				if ( ES_VALIDO ( fDuplicar ) )
				{
					p_lisRes = SLispCrear ();
					if ( ES_VALIDO ( p_lisRes ) )
					{
						iError = 0;
						p_elpObj = p_lisValores1->p_elpPrimero;
						while ( ES_VALIDO ( p_elpObj ) && ( iError == 0 ) )
						{
							if ( SLispBuscarExt ( p_lisValores2, SElpDatos ( p_elpObj ), fSonIguales ) < 0 )
							{
								p_elpNuevo = SElpDuplicarExt ( p_elpObj, fDuplicar );
								if ( _SLispInsertarAlFinalPtr ( p_lisRes, p_elpNuevo ) != 1 )
								{
									SElpDestruir ( &p_elpNuevo );
									iError = 1;
								}
							}
							p_elpObj = SElpSucesor ( p_elpObj );
						}
						if ( iError == 1 )
						{
							SLispDestruir ( &p_lisRes );
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
	}
	else
	{
		p_lisRes = NULL;
	}
	return ( p_lisRes );
}

SElementoPtr * _SLispExtraerElemPtr ( SListaPtr * p_lisObj, int iElem )
{
	SElementoPtr * p_elpRes;

	if ( SLispEsValida ( p_lisObj ) == 1 )
	{
		SLispMoverA ( p_lisObj, iElem );
		p_elpRes = _SLispExtraerPtr ( p_lisObj );
	}
	else
	{
		p_elpRes = NULL;
	}
	return ( p_elpRes );
}

/* Saca el nodo del cursor sin destruirlo. El cursor queda en el sucesor, o en
   el antecesor si se saco el ultimo, igual que en SLispEliminar. */
SElementoPtr * _SLispExtraerPtr ( SListaPtr * p_lisObj )
{
	SElementoPtr * p_elpRes;
	SElementoPtr * p_elpAnt;
	SElementoPtr * p_elpSig;

	if ( SLispEsValida ( p_lisObj ) == 1 )
	{
		if ( ( p_lisObj->iPos >= 0 ) &&
			 ( p_lisObj->iPos < p_lisObj->iNumElementos ) &&
			 ES_VALIDO ( p_lisObj->p_elpActual ) )
		{
			p_elpRes = p_lisObj->p_elpActual;
			p_elpAnt = SElpAntecesor ( p_lisObj->p_elpActual );
			p_elpSig = SElpSucesor ( p_lisObj->p_elpActual );

			p_lisObj->iNumElementos = p_lisObj->iNumElementos - 1;

			if ( ES_VALIDO ( p_elpAnt ) )
			{
				SElpEncadenarSucesor ( p_elpAnt, p_elpSig );
			}
			else
			{
				SElpEncadenarAntecesor ( p_elpSig, p_elpAnt );
				p_lisObj->p_elpPrimero = p_elpSig;
			}

			if ( ES_VALIDO ( p_elpSig ) )
			{
				p_lisObj->p_elpActual = p_elpSig;
			}
			else
			{
				p_lisObj->p_elpUltimo = p_elpAnt;
				p_lisObj->p_elpActual = p_elpAnt;
				p_lisObj->iPos = p_lisObj->iPos - 1;
			}

			/* El extraido se devuelve limpio: solo se anulan sus enlaces propios.
			   SElpDesencadenar no sirve aqui: ve todavia a los antiguos vecinos,
			   que ya estan enganchados entre si, y les cortaria ese enlace. */
			SElpDeposicionar ( p_elpRes );
		}
		else
		{
			p_elpRes = NULL;
		}
	}
	else
	{
		p_elpRes = NULL;
	}
	return ( p_elpRes );
}

int _SLispInsertarElemPtr ( SListaPtr * p_lisObj, int iPosAnt, SElementoPtr * p_elpDatos )
{
	int iRes;

	if ( ( SLispEsValida ( p_lisObj ) == 1 ) && ES_VALIDO ( p_elpDatos ) )
	{
		if ( iPosAnt < 0 )
		{
			SLispInicio ( p_lisObj );
			iRes = _SLispInsertarDelantePtr ( p_lisObj, p_elpDatos );
		}
		else if ( iPosAnt >= p_lisObj->iNumElementos )
		{
			SLispFinal ( p_lisObj );
			iRes = _SLispInsertarDetrasPtr ( p_lisObj, p_elpDatos );
		}
		else
		{
			SLispMoverA ( p_lisObj, iPosAnt );
			if ( ES_NULO ( p_lisObj->p_elpActual ) )
			{
				iRes = 0;
			}
			else
			{
				iRes = _SLispInsertarPtr ( p_lisObj, p_elpDatos );
			}
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int _SLispInsertarAlInicioPtr ( SListaPtr * p_lisObj, SElementoPtr * p_elpDatos )
{
	return ( _SLispInsertarElemPtr ( p_lisObj, -1, p_elpDatos ) );
}

int _SLispInsertarAlFinalPtr ( SListaPtr * p_lisObj, SElementoPtr * p_elpDatos )
{
	int iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iRes = _SLispInsertarElemPtr ( p_lisObj, p_lisObj->iNumElementos, p_elpDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int _SLispInsertarPtr ( SListaPtr * p_lisObj, SElementoPtr * p_elpDatos )
{
	return ( _SLispInsertarDetrasPtr ( p_lisObj, p_elpDatos ) );
}

/* Las dos de abajo enganchan el NODO tal cual: tiene que venir suelto ( recien
   creado o extraido ), porque SElpDesencadenar corta los enlaces que traiga. */
int _SLispInsertarDelantePtr ( SListaPtr * p_lisObj, SElementoPtr * p_elpDatos )
{
	int iRes;

	if ( ( SLispEsValida ( p_lisObj ) == 1 ) && ES_VALIDO ( p_elpDatos ) )
	{
		SElpDesencadenar ( p_elpDatos );

		if ( p_lisObj->iNumElementos <= 0 )
		{
			p_lisObj->p_elpPrimero = p_elpDatos;
			p_lisObj->p_elpUltimo = p_elpDatos;
			p_lisObj->iNumElementos = 1;

			SLispInicio ( p_lisObj );
			iRes = 1;
		}
		else if ( ( p_lisObj->iPos >= 0 ) &&
				  ( p_lisObj->iPos < p_lisObj->iNumElementos ) &&
				  ES_VALIDO ( p_lisObj->p_elpActual ) )
		{
			/* Empalme: antiguo antecesor -> p_elpDatos -> actual. */
			SElpEncadenarAntecesor ( p_elpDatos, SElpAntecesor ( p_lisObj->p_elpActual ) );
			SElpEncadenarAntecesor ( p_lisObj->p_elpActual, p_elpDatos );

			if ( p_lisObj->p_elpPrimero == p_lisObj->p_elpActual )
			{
				p_lisObj->p_elpPrimero = p_elpDatos;
			}
			p_lisObj->p_elpActual = p_elpDatos;

			p_lisObj->iNumElementos = p_lisObj->iNumElementos + 1;

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

int _SLispInsertarDetrasPtr ( SListaPtr * p_lisObj, SElementoPtr * p_elpDatos )
{
	int	iRes;

	if ( ( SLispEsValida ( p_lisObj ) == 1 ) && ES_VALIDO ( p_elpDatos ) )
	{
		SElpDesencadenar ( p_elpDatos );
		if ( p_lisObj->iNumElementos <= 0 )
		{
			p_lisObj->p_elpPrimero = p_elpDatos;
			p_lisObj->p_elpUltimo = p_elpDatos;
			p_lisObj->iNumElementos = 1;

			SLispInicio ( p_lisObj );
			iRes = 1;
		}
		else if ( ( p_lisObj->iPos >= 0 ) &&
				  ( p_lisObj->iPos < p_lisObj->iNumElementos ) &&
				  ES_VALIDO ( p_lisObj->p_elpActual ) )
		{
			/* Empalme: actual -> p_elpDatos -> antiguo sucesor. */
			SElpEncadenarSucesor ( p_elpDatos, SElpSucesor ( p_lisObj->p_elpActual ) );
			SElpEncadenarSucesor ( p_lisObj->p_elpActual, p_elpDatos );

			if ( p_lisObj->p_elpUltimo == p_lisObj->p_elpActual )
			{
				p_lisObj->p_elpUltimo = p_elpDatos;
			}
			p_lisObj->p_elpActual = p_elpDatos;
			p_lisObj->iPos = p_lisObj->iPos + 1;

			p_lisObj->iNumElementos = p_lisObj->iNumElementos + 1;

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

/* Elemento de la posicion iPos, o NULL fuera de rango. Parte del cursor si
   esta posicionado y, si no, del extremo mas cercano. No mueve el cursor. */
static SElementoPtr * _SLispLocalizarPosicion ( SListaPtr * p_lisObj, int iPos )
{
	SElementoPtr * p_elpRes;

	if ( ( iPos >= 0 ) && ( iPos < p_lisObj->iNumElementos ) )
	{
		if ( ES_VALIDO ( p_lisObj->p_elpActual ) &&
			 ( p_lisObj->iPos >= 0 ) &&
			 ( p_lisObj->iPos < p_lisObj->iNumElementos ) )
		{
			if ( iPos > p_lisObj->iPos )
			{
				p_elpRes = SElpSucesorExt ( p_lisObj->p_elpActual, iPos - p_lisObj->iPos );
			}
			else if ( iPos < p_lisObj->iPos )
			{
				p_elpRes = SElpAntecesorExt ( p_lisObj->p_elpActual, p_lisObj->iPos - iPos );
			}
			else
			{
				p_elpRes = p_lisObj->p_elpActual;
			}
		}
		else
		{
			if ( iPos < p_lisObj->iNumElementos / 2 )
			{
				p_elpRes = SElpSucesorExt ( p_lisObj->p_elpPrimero, iPos );
			}
			else
			{
				/* El ultimo es iNumElementos - 1: hasta iPos hay
				   iNumElementos - 1 - iPos eslabones. */
				p_elpRes = SElpAntecesorExt ( p_lisObj->p_elpUltimo, p_lisObj->iNumElementos - 1 - iPos );
			}
		}
	}
	else
	{
		p_elpRes = NULL;
	}
	return ( p_elpRes );
}

