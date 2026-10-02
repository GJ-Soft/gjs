#include "SListaPtr.h"


#include "TiposBasicosConfig.h"




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

   Gemela de SLisElemento en SLista. Como ella, entra por el extremo mas cercano
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
			iRes = SLispInsertarDelante ( p_lisObj, p_byDatos);
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
	else
	{
		p_lisObj->iPos = -1;
		p_lisObj->p_elpActual = NULL;
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
	else
	{
		p_lisObj->iPos = -1;
		p_lisObj->p_elpActual = NULL;
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
	else
	{
		p_lisObj->iPos = -1;
		p_lisObj->p_elpActual = NULL;
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
	else
	{
		p_lisObj->iPos = -1;
		p_lisObj->p_elpActual = NULL;
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
	else
	{
		p_lisObj->iPos = -1;
		p_lisObj->p_elpActual = NULL;
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

int SLispBuscar ( SListaPtr * p_lisObj, byte * p_byDatos, int iNumBytes )
{
	int				iRes;
	int				iEnc;
	SElementoPtr *	p_elpObj;

	if ( ( SLispEsValida ( p_lisObj ) == 1 ) && ES_VALIDO ( p_byDatos ) )
	{
		p_elpObj = p_lisObj->p_elpPrimero;
		iRes = 0;
		iEnc = 0;
		while ( ( iRes < p_lisObj->iNumElementos ) && ( iEnc == 0 ) &&
			ES_VALIDO ( p_elpObj ) )
		{
			iEnc = SElpEsIgualExt ( p_elpObj, p_byDatos, iNumBytes );
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


