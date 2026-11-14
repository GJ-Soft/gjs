#include "SLista.h"


#include "TiposBasicosConfig.h"

static SElemento * _SLisLocalizarPosicion ( SLista * p_lisObj, int iPos );

SLista * SLisCrear ()
{
	SLista * p_lisObj;
	
	p_lisObj = (SLista *) MemReservar ( sizeof ( SLista ) );
	if ( ES_VALIDO ( p_lisObj ) )
	{
		p_lisObj->p_elmPrimero = NULL;
		p_lisObj->p_elmUltimo = NULL;
		p_lisObj->p_elmActual = NULL;
		p_lisObj->iNumElementos = 0;
		p_lisObj->iPos = -1;
	}
	return ( p_lisObj );
}

void SLisDestruir ( SLista ** p_p_lisObj )
{
	SLista * p_lisObj;
	
	if ( ES_VALIDO ( p_p_lisObj ) )
	{
		p_lisObj = *p_p_lisObj;

		if ( ES_VALIDO ( p_lisObj ) )
		{
			SLisVaciar ( p_lisObj );
			MemLiberar ( (void **) p_p_lisObj );
		}
	}
}

int SLisEsValida ( SLista * p_lisObj )
{
	int iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		if ( p_lisObj->iNumElementos > 0 )
		{
			if ( ES_VALIDO ( p_lisObj->p_elmPrimero ) &&
				 ES_VALIDO ( p_lisObj->p_elmUltimo  ) )
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
			if ( ( p_lisObj->p_elmPrimero == NULL ) &&
				 ( p_lisObj->p_elmUltimo == NULL ) &&
				 ( p_lisObj->iPos == -1 ) && 
				 ( p_lisObj->p_elmActual == NULL ) )
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

int SLisNumElementos ( SLista * p_lisObj )
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

int SLisEstaVacia ( SLista * p_lisObj )
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

/* Acceso por indice SIN tocar el cursor. Antes se resolvia con SLisMoverA, que
   mueve el cursor de la lista, y eso convertia cualquier consulta —Elemento,
   Min, Max, EstaOrdenada…— en una operacion que le cambiaba la posicion al que
   estuviera iterando.

   Se entra por el extremo mas cercano al indice pedido, asi que una llamada
   suelta cuesta como mucho media lista. OJO: eso hace que recorrer la lista
   ENTERA por indice sea cuadratico, porque ya no se aprovecha la posicion de la
   llamada anterior. Para recorrer de principio a fin hay que usar el cursor
   ( SLisInicio / SLisSiguiente / SLisActual ), no esta. */
SElemento * SLisElemento ( SLista * p_lisObj, int iElem )
{
	SElemento * p_elmRes;
	int			iPos;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		if ( ( iElem >= 0 ) && ( iElem < p_lisObj->iNumElementos ) )
		{
			if ( iElem < p_lisObj->iNumElementos / 2 )
			{
				p_elmRes = p_lisObj->p_elmPrimero;
				iPos = 0;
				while ( ( iPos < iElem ) && 
						ES_VALIDO ( p_elmRes ) )
				{
					p_elmRes = SElmSucesor ( p_elmRes );
					iPos = iPos + 1;
				}
			}
			else
			{
				p_elmRes = p_lisObj->p_elmUltimo;
				iPos = p_lisObj->iNumElementos - 1;
				/* > y no >=: con >= se da un paso de mas y se acaba en
				   iElem - 1. La rama de arriba, la que entra por el principio,
				   ya usaba la comparacion estricta. */
				while ( ( iPos > iElem ) &&
						ES_VALIDO ( p_elmRes ) )
				{
					p_elmRes = SElmAntecesor ( p_elmRes );
					iPos = iPos - 1;
				}
			}
		}
		else
		{
			p_elmRes = NULL;
		}
	}
	else
	{
		p_elmRes = NULL;
	}
	return ( p_elmRes );
}

int SLisEstablecerElem ( SLista * p_lisObj, int iElem, SElemento * p_elmObj )
{
	int iRes;

	if ( ( SLisEsValida ( p_lisObj ) == 1 ) && ES_VALIDO ( p_elmObj ) )
	{
		if ( ( iElem >= 0 ) && ( iElem < p_lisObj->iNumElementos ) )
		{
			SLisMoverA ( p_lisObj, iElem );
			iRes = SLisEstablecer ( p_lisObj, p_elmObj );
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

int SLisInsertarElem ( SLista * p_lisObj, int iPosAnt, SElemento * p_elmObj )
{
	int iRes;

	if ( ( SLisEsValida ( p_lisObj ) == 1 ) && ES_VALIDO ( p_elmObj ) )
	{
		if ( iPosAnt < 0 ) 
		{
			SLisInicio ( p_lisObj );
			iRes = SLisInsertarDelante ( p_lisObj, p_elmObj );
		}
		else if ( iPosAnt >= p_lisObj->iNumElementos )
		{
			SLisFinal ( p_lisObj );
			iRes = SLisInsertarDetras ( p_lisObj, p_elmObj );
		}
		else  
		{
			SLisMoverA ( p_lisObj, iPosAnt );
			if ( ES_NULO ( p_lisObj->p_elmActual ) ) 
			{
				iRes = 0;
			}
			else 
			{
				iRes = SLisInsertar ( p_lisObj, p_elmObj );
			}
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLisInsertarAlInicio ( SLista * p_lisObj, SElemento * p_elmObj )
{
	return ( SLisInsertarElem ( p_lisObj, -1, p_elmObj ) );
}

int SLisInsertarAlFinal ( SLista * p_lisObj, SElemento * p_elmObj )
{
	int iRes;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		iRes = SLisInsertarElem ( p_lisObj, p_lisObj->iNumElementos, p_elmObj );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLisEliminarElem ( SLista * p_lisObj, int iElem )
{
	int	iRes;

	if ( SLisEsValida ( p_lisObj ) == 1 ) 
	{
		SLisMoverA ( p_lisObj, iElem );
		iRes = SLisEliminar ( p_lisObj );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

SElemento * SLisExtraerElem ( SLista * p_lisObj, int iElem )
{
	SElemento * p_elmRes;

	if ( SLisEsValida ( p_lisObj ) == 1 ) 
	{
		SLisMoverA ( p_lisObj, iElem );
		p_elmRes = SLisExtraer ( p_lisObj );
	}
	else
	{
		p_elmRes = NULL;
	}
	return ( p_elmRes );
}

int SLisVaciar ( SLista * p_lisObj )
{
	int	iRes;

	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		iRes = 1;
		while ( ( p_lisObj->iNumElementos > 0 ) && ( iRes == 1 ) )
		{
			SLisInicio ( p_lisObj );
			iRes = SLisEliminar ( p_lisObj );
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLisPosicion ( SLista * p_lisObj )
{
	int	iRes;

	if ( SLisEsValida ( p_lisObj ) == 1 ) 
	{
		iRes = p_lisObj->iPos;
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

SElemento * SLisActual ( SLista * p_lisObj )
{
	SElemento * p_elmRes;

	if ( SLisEsValida ( p_lisObj ) == 1 ) 
	{
		p_elmRes = p_lisObj->p_elmActual;
		if ( ES_NULO ( p_elmRes ) )
		{
			ERROR_ESTABLECER( ERR_POSICION_INVALIDA );
		}
	}
	else
	{
		p_elmRes = NULL;
	}
	return ( p_elmRes );
}

/* 1 si el cursor esta sobre un elemento; 0 si no, o si la lista no es valida. */
int SLisEstaPosicionada ( SLista * p_lisObj )
{
	int iRes;

	if ( SLisEsValida ( p_lisObj ) == 1 )
	{
		if ( ES_VALIDO ( p_lisObj->p_elmActual ) )
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

void SLisInicio ( SLista * p_lisObj )
{
	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		if ( p_lisObj->iNumElementos > 0 )
		{
			p_lisObj->iPos = 0;
			p_lisObj->p_elmActual = p_lisObj->p_elmPrimero;
		}
		else
		{
			p_lisObj->iPos = -1;
			p_lisObj->p_elmActual = NULL;
		}
	}
}

void SLisFinal ( SLista * p_lisObj )
{
	if ( ES_VALIDO ( p_lisObj ) ) 
	{
		if ( p_lisObj->iNumElementos > 0 )
		{
			p_lisObj->iPos = p_lisObj->iNumElementos - 1;
			p_lisObj->p_elmActual = p_lisObj->p_elmUltimo;
		}
		else
		{
			p_lisObj->iPos = -1;
			p_lisObj->p_elmActual = NULL;
		}
	}
}

void SLisSiguiente ( SLista * p_lisObj )
{
	if ( SLisEsValida ( p_lisObj ) == 1 ) 
	{
		if ( ES_VALIDO ( p_lisObj->p_elmActual ) )
		{
			p_lisObj->iPos = p_lisObj->iPos + 1;
			p_lisObj->p_elmActual = SElmSucesor ( p_lisObj->p_elmActual );
		}
		else
		{
			p_lisObj->iPos = -1;
			p_lisObj->p_elmActual = NULL;
		}
	}
}

void SLisAnterior ( SLista * p_lisObj )
{
	if ( SLisEsValida ( p_lisObj ) == 1 ) 
	{
		if ( ES_VALIDO ( p_lisObj->p_elmActual ) )
		{
			p_lisObj->iPos = p_lisObj->iPos - 1;
			p_lisObj->p_elmActual = SElmAntecesor ( p_lisObj->p_elmActual );
		}
		else
		{
			p_lisObj->iPos = -1;
			p_lisObj->p_elmActual = NULL;
		}
	}
}

void SLisMoverA ( SLista * p_lisObj, int iElem )
{
	if ( SLisEsValida ( p_lisObj ) == 1 ) 
	{
		if ( ( iElem >= 0 ) && ( iElem < p_lisObj->iNumElementos ) )
		{
			if ( ES_VALIDO ( p_lisObj->p_elmActual ) && 
				 ( p_lisObj->iPos >= 0 ) && 
				 ( p_lisObj->iPos < p_lisObj->iNumElementos ) )
			{
				while ( ( iElem > p_lisObj->iPos ) &&
						ES_VALIDO ( p_lisObj->p_elmActual ) )
				{
					p_lisObj->p_elmActual = SElmSucesor ( p_lisObj->p_elmActual );
					p_lisObj->iPos = p_lisObj->iPos + 1;
				}

				while ( ( iElem < p_lisObj->iPos ) && 
						ES_VALIDO ( p_lisObj->p_elmActual ) )
				{
					p_lisObj->p_elmActual = SElmAntecesor ( p_lisObj->p_elmActual );
					p_lisObj->iPos = p_lisObj->iPos - 1;
				}
			}
			else
			{
				if ( iElem < p_lisObj->iNumElementos / 2 )
				{
					p_lisObj->p_elmActual = p_lisObj->p_elmPrimero;
					p_lisObj->iPos = 0;
					while ( ( p_lisObj->iPos < iElem ) && 
							ES_VALIDO ( p_lisObj->p_elmActual ) )
					{
						p_lisObj->p_elmActual = SElmSucesor ( p_lisObj->p_elmActual );
						p_lisObj->iPos = p_lisObj->iPos + 1;
					}
				}
				else
				{
					p_lisObj->p_elmActual = p_lisObj->p_elmUltimo;
					p_lisObj->iPos = p_lisObj->iNumElementos - 1;
					/* > y no >=: con >= se da un paso de mas y se acaba en
					   iElem - 1. La rama de arriba, la que entra por el principio,
					   ya usaba la comparacion estricta. */
					while ( ( p_lisObj->iPos > iElem ) &&
							ES_VALIDO ( p_lisObj->p_elmActual ) )
					{
						p_lisObj->p_elmActual = SElmAntecesor ( p_lisObj->p_elmActual );
						p_lisObj->iPos = p_lisObj->iPos - 1;
					}
				}
			}
		}
		else
		{
			p_lisObj->iPos = -1;
			p_lisObj->p_elmActual = NULL;
		}
	}
}

void SLisDeposicionar ( SLista * p_lisObj )
{
	if ( ES_VALIDO ( p_lisObj ) )
	{
		p_lisObj->iPos = -1;
		p_lisObj->p_elmActual = NULL;
	}
}

/* Existe: 1 si hay algun elemento igual y 0 si no, tambien con una lista o un
   dato no validos. Las Elem comparan con el contenido de p_elmObj, que no
   hace falta que este en la lista; las Ext, con memoria cruda. */
int SLisExisteElem ( SLista * p_lisObj, SElemento * p_elmObj )
{
	int	iRes;

	if ( SLisBuscarPrimeroElem ( p_lisObj, p_elmObj ) >= 0 )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLisExiste ( SLista * p_lisObj, SBloque * p_blqDatos )
{
	int	iRes;

	if ( SLisBuscarPrimero ( p_lisObj, p_blqDatos ) >= 0 )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLisExisteExt ( SLista * p_lisObj, byte * p_byDatos )
{
	int	iRes;

	if ( SLisBuscarPrimeroExt ( p_lisObj, p_byDatos ) >= 0 )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

/* Repeticiones: cuantos elementos iguales hay; 0 si ninguno, tambien con una
   lista o un dato no validos. Recorren la cadena una sola vez. */
int SLisRepeticionesElem ( SLista * p_lisObj, SElemento * p_elmObj )
{
	int	iRes;

	if ( ES_VALIDO ( p_elmObj ) )
	{
		iRes = SLisRepeticiones ( p_lisObj, SElmDatos ( p_elmObj ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLisRepeticiones ( SLista * p_lisObj, SBloque * p_blqDatos )
{
	SElemento *	p_elmObj;
	int			iRes;

	iRes = 0;
	if ( SLisEsValida ( p_lisObj ) == 1 )
	{
		if ( ES_VALIDO ( p_blqDatos ) )
		{
			p_elmObj = p_lisObj->p_elmPrimero;
			while ( ES_VALIDO ( p_elmObj ) )
			{
				if ( SElmEsIgualBlq ( p_elmObj, p_blqDatos ) == 1 )
				{
					iRes = iRes + 1;
				}
				p_elmObj = SElmSucesor ( p_elmObj );
			}
		}
	}
	return ( iRes );
}

int SLisRepeticionesExt ( SLista * p_lisObj, byte * p_byDatos )
{
	SElemento *	p_elmObj;
	int			iRes;

	iRes = 0;
	if ( SLisEsValida ( p_lisObj ) == 1 )
	{
		if ( ES_VALIDO ( p_byDatos ) )
		{
			p_elmObj = p_lisObj->p_elmPrimero;
			while ( ES_VALIDO ( p_elmObj ) )
			{
				if ( SElmEsIgualExt ( p_elmObj, p_byDatos ) == 1 )
				{
					iRes = iRes + 1;
				}
				p_elmObj = SElmSucesor ( p_elmObj );
			}
		}
	}
	return ( iRes );
}

/* Buscar es BuscarPrimero: posicion del primer elemento igual, o -1. */
int SLisBuscarElem ( SLista * p_lisObj, SElemento * p_elmObj )
{
	return ( SLisBuscarPrimeroElem ( p_lisObj, p_elmObj ) );
}

int SLisBuscar ( SLista * p_lisObj, SBloque * p_blqDatos )
{
	return ( SLisBuscarPrimero ( p_lisObj, p_blqDatos ) );
}

int SLisBuscarExt ( SLista * p_lisObj, byte * p_byDatos )
{
	return ( SLisBuscarPrimeroExt ( p_lisObj, p_byDatos ) );
}

int SLisBuscarPrimeroElem ( SLista * p_lisObj, SElemento * p_elmObj )
{
	return ( SLisBuscarSiguienteElem ( p_lisObj, p_elmObj, -1 ) );
}

int SLisBuscarPrimero ( SLista * p_lisObj, SBloque * p_blqDatos )
{
	return ( SLisBuscarSiguiente ( p_lisObj, p_blqDatos, -1 ) );
}

int SLisBuscarPrimeroExt ( SLista * p_lisObj, byte * p_byDatos )
{
	return ( SLisBuscarSiguienteExt ( p_lisObj, p_byDatos, -1 ) );
}

/* Posicion del siguiente elemento igual DETRAS de iPos, o -1 si no hay mas.
   Con iPos = -1 se busca desde el principio, y un iPos menor da -1. No mueve
   el cursor. Para recorrer los repetidos:

	   iPos = SLisBuscarPrimero ( p_lisObj, p_blqDatos );
	   while ( iPos >= 0 )
	   {
		   ...
		   iPos = SLisBuscarSiguiente ( p_lisObj, p_blqDatos, iPos );
	   }

   Sin elemento, la Elem devuelve -1. */
int SLisBuscarSiguienteElem ( SLista * p_lisObj, SElemento * p_elmObj, int iPos )
{
	int iRes;

	if ( ES_VALIDO ( p_elmObj ) )
	{
		iRes = SLisBuscarSiguiente ( p_lisObj, SElmDatos ( p_elmObj ), iPos );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int SLisBuscarSiguiente ( SLista * p_lisObj, SBloque * p_blqDatos, int iPos )
{
	int			iRes;
	int			iEnc;
	SElemento * p_elmObj;

	if ( ( SLisEsValida ( p_lisObj ) == 1 ) && ES_VALIDO ( p_blqDatos ) && ( iPos >= -1 ) )
	{
		iRes = iPos + 1;
		p_elmObj = _SLisLocalizarPosicion ( p_lisObj, iRes );
		iEnc = 0;
		while ( ( iRes < p_lisObj->iNumElementos ) && ( iEnc == 0 ) &&
			ES_VALIDO ( p_elmObj ) )
		{
			iEnc = SElmEsIgualBlq ( p_elmObj, p_blqDatos );
			if ( iEnc == 0 )
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

int SLisBuscarSiguienteExt ( SLista * p_lisObj, byte * p_byDatos, int iPos )
{
	int			iRes;
	int			iEnc;
	SElemento * p_elmObj;

	if ( ( SLisEsValida ( p_lisObj ) == 1 ) && ES_VALIDO ( p_byDatos ) && ( iPos >= -1 ) )
	{
		iRes = iPos + 1;
		p_elmObj = _SLisLocalizarPosicion ( p_lisObj, iRes );
		iEnc = 0;
		while ( ( iRes < p_lisObj->iNumElementos ) && ( iEnc == 0 ) &&
			ES_VALIDO ( p_elmObj ) )
		{
			iEnc = SElmEsIgualExt ( p_elmObj, p_byDatos );
			if ( iEnc == 0 )
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

int SLisEsNulo ( SLista * p_lisObj )
{
	int iRes;

	if ( SLisEsValida ( p_lisObj ) == 1 ) 
	{
		if ( ES_VALIDO ( p_lisObj->p_elmActual ) )
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

int SLisEstaEnFinal ( SLista * p_lisObj )
{
	int iRes;

	if ( SLisEsValida ( p_lisObj ) == 1 ) 
	{
		if ( ES_VALIDO ( p_lisObj->p_elmActual ) && 
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

int SLisEstaEnInicio ( SLista * p_lisObj )
{
	int iRes;

	if ( SLisEsValida ( p_lisObj ) == 1 ) 
	{
		if ( ES_VALIDO ( p_lisObj->p_elmActual ) && ( p_lisObj->iPos == 0 ) )
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

int SLisEstablecer ( SLista * p_lisObj, SElemento * p_elmObj )
{
	int iRes;

	if ( ( SLisEsValida ( p_lisObj ) == 1 ) && ES_VALIDO ( p_elmObj ) )
	{
		if ( ( p_lisObj->iPos >= 0 ) && 
			 ( p_lisObj->iPos < p_lisObj->iNumElementos ) && 
			 ES_VALIDO ( p_lisObj->p_elmActual ) )
		{
			SElmEncadenarSucesor ( p_elmObj, SElmSucesor ( p_lisObj->p_elmActual ) );
			SElmEncadenarAntecesor ( p_elmObj, SElmAntecesor ( p_lisObj->p_elmActual ) );

			SElmDestruir ( &(p_lisObj->p_elmActual) ); 
			p_lisObj->p_elmActual = p_elmObj;
			
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


int SLisInsertar ( SLista * p_lisObj, SElemento * p_elmObj )
{
	return ( SLisInsertarDetras ( p_lisObj, p_elmObj ) );
}

int SLisInsertarDelante ( SLista * p_lisObj, SElemento * p_elmObj )
{
	int iRes;

	if ( ( SLisEsValida ( p_lisObj ) == 1 ) && ES_VALIDO ( p_elmObj ) )
	{
		SElmDesencadenar ( p_elmObj );

		if ( p_lisObj->iNumElementos <= 0 )
		{
			p_lisObj->p_elmPrimero = p_elmObj;
			p_lisObj->p_elmUltimo = p_elmObj;
			p_lisObj->iNumElementos = 1;

			SLisInicio ( p_lisObj );
			iRes = 1;
		}
		else if ( ( p_lisObj->iPos >= 0 ) && 
				  ( p_lisObj->iPos < p_lisObj->iNumElementos ) && 
				  ES_VALIDO ( p_lisObj->p_elmActual ) )
		{
			/* Empalme: antiguo antecesor -> p_elmObj -> actual. */
			SElmEncadenarAntecesor ( p_elmObj, SElmAntecesor ( p_lisObj->p_elmActual ) );
			SElmEncadenarAntecesor ( p_lisObj->p_elmActual, p_elmObj );

			if ( p_lisObj->p_elmPrimero == p_lisObj->p_elmActual )
			{
				p_lisObj->p_elmPrimero = p_elmObj;
			}
			p_lisObj->p_elmActual = p_elmObj;

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

int SLisInsertarDetras ( SLista * p_lisObj, SElemento * p_elmObj )
{
	int iRes;

	if ( ( SLisEsValida ( p_lisObj ) == 1 ) && ES_VALIDO ( p_elmObj ) )
	{
		SElmDesencadenar ( p_elmObj );

		if ( p_lisObj->iNumElementos <= 0 )
		{
			p_lisObj->p_elmPrimero = p_elmObj;
			p_lisObj->p_elmUltimo = p_elmObj;
			p_lisObj->iNumElementos = 1;

			SLisInicio ( p_lisObj );
			iRes = 1;
		}
		else if ( ( p_lisObj->iPos >= 0 ) && 
				  ( p_lisObj->iPos < p_lisObj->iNumElementos ) && 
				  ES_VALIDO ( p_lisObj->p_elmActual ) )
		{
			/* Empalme: actual -> p_elmObj -> antiguo sucesor. */
			SElmEncadenarSucesor ( p_elmObj, SElmSucesor ( p_lisObj->p_elmActual ) );
			SElmEncadenarSucesor ( p_lisObj->p_elmActual, p_elmObj );

			if ( p_lisObj->p_elmUltimo == p_lisObj->p_elmActual )
			{
				p_lisObj->p_elmUltimo = p_elmObj;
			}
			p_lisObj->p_elmActual = p_elmObj;
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

int SLisEliminar ( SLista * p_lisObj )
{
	int			iRes;
	SElemento * p_elmAnt;
	SElemento * p_elmSig;

	if ( SLisEsValida ( p_lisObj ) == 1 ) 
	{
		if ( ( p_lisObj->iPos >= 0 ) && 
			 ( p_lisObj->iPos < p_lisObj->iNumElementos ) && 
			 ES_VALIDO ( p_lisObj->p_elmActual ) )
		{
			p_elmAnt = SElmAntecesor ( p_lisObj->p_elmActual );
			p_elmSig = SElmSucesor ( p_lisObj->p_elmActual );

			SElmDestruir ( &(p_lisObj->p_elmActual) );
			p_lisObj->iNumElementos = p_lisObj->iNumElementos - 1;

			if ( ES_VALIDO ( p_elmAnt ) )
			{
				SElmEncadenarSucesor ( p_elmAnt, p_elmSig );
			}
			else
			{
				SElmEncadenarAntecesor ( p_elmSig, p_elmAnt );
				p_lisObj->p_elmPrimero = p_elmSig;
			}

			if ( ES_VALIDO ( p_elmSig ) )
			{
				p_lisObj->p_elmActual = p_elmSig;
			}
			else
			{
				p_lisObj->p_elmUltimo = p_elmAnt;
				p_lisObj->p_elmActual = p_elmAnt;
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

SElemento * SLisExtraer ( SLista * p_lisObj )
{
	SElemento *	p_elmRes;
	SElemento * p_elmAnt;
	SElemento * p_elmSig;

	if ( SLisEsValida ( p_lisObj ) == 1 ) 
	{
		if ( ( p_lisObj->iPos >= 0 ) && 
			 ( p_lisObj->iPos < p_lisObj->iNumElementos ) && 
			 ES_VALIDO ( p_lisObj->p_elmActual ) )
		{
			p_elmRes = p_lisObj->p_elmActual;
			p_elmAnt = SElmAntecesor ( p_lisObj->p_elmActual );
			p_elmSig = SElmSucesor ( p_lisObj->p_elmActual );

			p_lisObj->iNumElementos = p_lisObj->iNumElementos - 1;

			if ( ES_VALIDO ( p_elmAnt ) )
			{
				SElmEncadenarSucesor ( p_elmAnt, p_elmSig );
			}
			else
			{
				SElmEncadenarAntecesor ( p_elmSig, p_elmAnt );
				p_lisObj->p_elmPrimero = p_elmSig;
			}

			if ( ES_VALIDO ( p_elmSig ) )
			{
				p_lisObj->p_elmActual = p_elmSig;
			}
			else
			{
				p_lisObj->p_elmUltimo = p_elmAnt;
				p_lisObj->p_elmActual = p_elmAnt;
				p_lisObj->iPos = p_lisObj->iPos - 1;
			}

			/* El extraido se devuelve limpio: solo se anulan sus enlaces propios. */
			SElmDeposicionar ( p_elmRes );
		}
		else
		{
			p_elmRes = NULL;
		}
	}
	else
	{
		p_elmRes = NULL;
	}
	return ( p_elmRes );
}

/* Lista nueva con COPIAS de los elementos ( SElmDuplicar ), en el mismo orden;
   p_lisObj no se toca, ni su cursor. Si falla alguna copia se destruye lo
   copiado y se devuelve NULL: nunca una copia a medias. */
SLista * SLisDuplicar ( SLista * p_lisObj )
{
	SLista *	p_lisRes;
	SElemento * p_elmObj;
	SElemento * p_elmNuevo;
	int			iError;

	if ( SLisEsValida ( p_lisObj ) == 1 )
	{
		p_lisRes = SLisCrear ();
		if ( ES_VALIDO ( p_lisRes ) )
		{
			iError = 0;
			p_elmObj = p_lisObj->p_elmPrimero;
			while ( ES_VALIDO ( p_elmObj ) && ( iError == 0 ) )
			{
				p_elmNuevo = SElmDuplicar ( p_elmObj );
				if ( SLisInsertarAlFinal ( p_lisRes, p_elmNuevo ) != 1 )
				{
					SElmDestruir ( &p_elmNuevo );
					iError = 1;
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
	return ( p_lisRes );
}

/* Operaciones con otras listas.

   Todas recorren la CADENA de p_lisValores, no su cursor ni su indice: asi no se
   le cambia la posicion a quien la este iterando y el recorrido es lineal. Ver
   la nota de SLisElemento.

   Con la lista de valores vacia, ExistenTodos da 1 ( no falta ninguno ) y
   ExisteAlguno da 0. */
int SLisExistenTodos ( SLista * p_lisObj, SLista * p_lisValores )
{
	SElemento * p_elmObj;
	int			iRes;

	if ( SLisEsValida ( p_lisObj ) == 1 )
	{
		if ( SLisEsValida ( p_lisValores ) == 1 )
		{
			iRes = 1;
			p_elmObj = p_lisValores->p_elmPrimero;
			while ( ES_VALIDO ( p_elmObj ) && ( iRes == 1 ) )
			{
				/* SLisBuscar da la posicion o -1, no un booleano. */
				if ( SLisBuscar ( p_lisObj, SElmDatos ( p_elmObj ) ) < 0 )
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

int SLisExisteAlguno ( SLista * p_lisObj, SLista * p_lisValores )
{
	SElemento * p_elmObj;
	int			iRes;

	if ( SLisEsValida ( p_lisObj ) == 1 )
	{
		if ( SLisEsValida ( p_lisValores ) == 1 )
		{
			iRes = 0;
			p_elmObj = p_lisValores->p_elmPrimero;
			while ( ES_VALIDO ( p_elmObj ) && ( iRes == 0 ) )
			{
				if ( SLisBuscar ( p_lisObj, SElmDatos ( p_elmObj ) ) >= 0 )
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

/* MUEVE los elementos de p_lisValores a p_lisObj, detras del cursor y en su
   orden; p_lisValores queda vacia.

   Si un elemento no se puede insertar ( p_lisObj no vacia y sin cursor ) se
   devuelve a la cabeza de p_lisValores y se para: lo movido hasta ahi se queda
   movido y lo que falta sigue en p_lisValores, sin perder nada.

   Con la misma lista en los dos argumentos se devuelve 0 sin tocar nada: la
   lista se iria vaciando y llenando a la vez. */
int SLisInsertarLista ( SLista * p_lisObj, SLista * p_lisValores )
{
	SElemento * p_elmObj;
	int			iRes;

	if ( SLisEsValida ( p_lisObj ) == 1 )
	{
		if ( SLisEsValida ( p_lisValores ) == 1 )
		{
			if ( p_lisObj != p_lisValores )
			{
				iRes = 1;
				while ( ( iRes == 1 ) && ( p_lisValores->iNumElementos > 0 ) )
				{
					SLisInicio ( p_lisValores );
					p_elmObj = SLisExtraer ( p_lisValores );
					if ( ES_VALIDO ( p_elmObj ) )
					{
						if ( SLisInsertar ( p_lisObj, p_elmObj ) != 1 )
						{
							SLisInsertarAlInicio ( p_lisValores, p_elmObj );
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

/* Como SLisInsertarLista, pero al final de p_lisObj: no depende del cursor. */
int SLisConcatenarLista ( SLista * p_lisObj, SLista * p_lisValores )
{
	SElemento * p_elmObj;
	int			iRes;

	if ( SLisEsValida ( p_lisObj ) == 1 )
	{
		if ( SLisEsValida ( p_lisValores ) == 1 )
		{
			if ( p_lisObj != p_lisValores )
			{
				iRes = 1;
				while ( ( iRes == 1 ) && ( p_lisValores->iNumElementos > 0 ) )
				{
					SLisInicio ( p_lisValores );
					p_elmObj = SLisExtraer ( p_lisValores );
					if ( ES_VALIDO ( p_elmObj ) )
					{
						if ( SLisInsertarAlFinal ( p_lisObj, p_elmObj ) != 1 )
						{
							SLisInsertarAlInicio ( p_lisValores, p_elmObj );
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

/* Las Dup insertan COPIAS ( SElmDuplicar ) y no tocan p_lisValores. Con la
   misma lista en los dos argumentos se devuelve 0: se insertaria en la cadena
   que se esta recorriendo. Si falla una copia o una insercion se para, y lo
   insertado hasta ahi se queda. */
int SLisInsertarListaDup ( SLista * p_lisObj, SLista * p_lisValores )
{
	SElemento * p_elmObj;
	SElemento * p_elmNuevo;
	int			iRes;

	if ( SLisEsValida ( p_lisObj ) == 1 )
	{
		if ( SLisEsValida ( p_lisValores ) == 1 )
		{
			if ( p_lisObj != p_lisValores )
			{
				iRes = 1;
				p_elmObj = p_lisValores->p_elmPrimero;
				while ( ES_VALIDO ( p_elmObj ) && ( iRes == 1 ) )
				{
					p_elmNuevo = SElmDuplicar ( p_elmObj );
					if ( SLisInsertar ( p_lisObj, p_elmNuevo ) != 1 )
					{
						SElmDestruir ( &p_elmNuevo );
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
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SLisConcatenarListaDup ( SLista * p_lisObj, SLista * p_lisValores )
{
	SElemento * p_elmObj;
	SElemento * p_elmNuevo;
	int			iRes;

	if ( SLisEsValida ( p_lisObj ) == 1 )
	{
		if ( SLisEsValida ( p_lisValores ) == 1 )
		{
			if ( p_lisObj != p_lisValores )
			{
				iRes = 1;
				p_elmObj = p_lisValores->p_elmPrimero;
				while ( ES_VALIDO ( p_elmObj ) && ( iRes == 1 ) )
				{
					p_elmNuevo = SElmDuplicar ( p_elmObj );
					if ( SLisInsertarAlFinal ( p_lisObj, p_elmNuevo ) != 1 )
					{
						SElmDestruir ( &p_elmNuevo );
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
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

/* Elimina ( destruye ) de p_lisObj todas las apariciones de cada valor de
   p_lisValores: que un valor se repita en p_lisValores no cambia nada. Lo que
   no se encuentra se ignora. p_lisValores no se toca.

   Devuelve 1 si ha podido eliminar todo lo encontrado; si falla una eliminacion
   se para y devuelve 0, y lo eliminado hasta ahi se queda eliminado. Con la
   misma lista en los dos argumentos se devuelve 0 sin tocar nada: se
   destruirian los elementos que se estan recorriendo. */
int SLisEliminarLista ( SLista * p_lisObj, SLista * p_lisValores )
{
	SElemento * p_elmObj;
	int			iPos;
	int			iRes;

	if ( SLisEsValida ( p_lisObj ) == 1 )
	{
		if ( SLisEsValida ( p_lisValores ) == 1 )
		{
			if ( p_lisObj != p_lisValores )
			{
				iRes = 1;
				p_elmObj = p_lisValores->p_elmPrimero;
				while ( ES_VALIDO ( p_elmObj ) && ( iRes == 1 ) )
				{
					iPos = SLisBuscarPrimero ( p_lisObj, SElmDatos ( p_elmObj ) );
					while ( ( iPos >= 0 ) && ( iRes == 1 ) )
					{
						if ( SLisEliminarElem ( p_lisObj, iPos ) == 1 )
						{
							/* El siguiente ha pasado a ocupar iPos: se sigue buscando desde ahi. */
							iPos = SLisBuscarSiguiente ( p_lisObj, SElmDatos ( p_elmObj ), iPos - 1 );
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
   p_lisValores: van por el orden de p_lisValores y, las de un mismo valor, en
   el que tenian en p_lisObj. Que un valor se repita en p_lisValores no cambia
   nada. Lo que no se encuentra se ignora. Los elementos se mueven, no se
   copian.

   Con la misma lista en los dos argumentos se devuelve NULL. */
SLista * SLisExtraerLista ( SLista * p_lisObj, SLista * p_lisValores )
{
	SLista *	p_lisRes;
	SElemento * p_elmObj;
	SElemento * p_elmExt;
	int			iPos;
	int			iError;

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
					p_elmObj = p_lisValores->p_elmPrimero;
					while ( ES_VALIDO ( p_elmObj ) && ( iError == 0 ) )
					{
						iPos = SLisBuscarPrimero ( p_lisObj, SElmDatos ( p_elmObj ) );
						while ( ( iPos >= 0 ) && ( iError == 0 ) )
						{
							p_elmExt = SLisExtraerElem ( p_lisObj, iPos );
							if ( SLisInsertarAlFinal ( p_lisRes, p_elmExt ) == 1 )
							{
								/* El siguiente ha pasado a ocupar iPos: se sigue buscando desde ahi. */
								iPos = SLisBuscarSiguiente ( p_lisObj, SElmDatos ( p_elmObj ), iPos - 1 );
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

/* Las que generan una lista nueva la devuelven con COPIAS; si algo falla, NULL.
   La union es la concatenacion de las dos: lo que este en ambas sale dos veces. */
SLista * SLisUnion ( SLista * p_lisValores1, SLista * p_lisValores2 )
{
	SLista *	p_lisRes;

	if ( SLisEsValida ( p_lisValores1 ) == 1 )
	{
		if ( SLisEsValida ( p_lisValores2 ) == 1 )
		{
			p_lisRes = SLisCrear ();
			if ( ES_VALIDO ( p_lisRes ) )
			{
				if ( SLisConcatenarListaDup ( p_lisRes, p_lisValores1 ) == 1 )
				{
					if ( SLisConcatenarListaDup ( p_lisRes, p_lisValores2 ) != 1 )
					{
						SLisDestruir ( &p_lisRes );
					}
				}
				else
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
SLista * SLisInterseccion ( SLista * p_lisValores1, SLista * p_lisValores2 )
{
	SLista *	p_lisRes;
	SElemento * p_elmObj;
	SElemento * p_elmNuevo;
	int			iError;

	if ( SLisEsValida ( p_lisValores1 ) == 1 )
	{
		if ( SLisEsValida ( p_lisValores2 ) == 1 )
		{
			p_lisRes = SLisCrear ();
			if ( ES_VALIDO ( p_lisRes ) )
			{
				iError = 0;
				p_elmObj = p_lisValores1->p_elmPrimero;
				while ( ES_VALIDO ( p_elmObj ) && ( iError == 0 ) )
				{
					if ( SLisBuscar ( p_lisValores2, SElmDatos ( p_elmObj ) ) >= 0 )
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

/* Los de p_lisValores1 que NO estan en p_lisValores2, en el orden de p_lisValores1. */
SLista * SLisDiferencia ( SLista * p_lisValores1, SLista * p_lisValores2 )
{
	SLista *	p_lisRes;
	SElemento * p_elmObj;
	SElemento * p_elmNuevo;
	int			iError;

	if ( SLisEsValida ( p_lisValores1 ) == 1 )
	{
		if ( SLisEsValida ( p_lisValores2 ) == 1 )
		{
			p_lisRes = SLisCrear ();
			if ( ES_VALIDO ( p_lisRes ) )
			{
				iError = 0;
				p_elmObj = p_lisValores1->p_elmPrimero;
				while ( ES_VALIDO ( p_elmObj ) && ( iError == 0 ) )
				{
					if ( SLisBuscar ( p_lisValores2, SElmDatos ( p_elmObj ) ) < 0 )
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

/* Elemento de la posicion iPos, o NULL fuera de rango. Parte del cursor si
   esta posicionado y, si no, del extremo mas cercano. No mueve el cursor. */
static SElemento * _SLisLocalizarPosicion ( SLista * p_lisObj, int iPos )
{
	SElemento * p_elmRes;

	if ( ( iPos >= 0 ) && ( iPos < p_lisObj->iNumElementos ) )
	{
		if ( ES_VALIDO ( p_lisObj->p_elmActual ) &&
			 ( p_lisObj->iPos >= 0 ) &&
			 ( p_lisObj->iPos < p_lisObj->iNumElementos ) )
		{
			if ( iPos > p_lisObj->iPos )
			{
				p_elmRes = SElmSucesorExt ( p_lisObj->p_elmActual, iPos - p_lisObj->iPos );
			}
			else if ( iPos < p_lisObj->iPos )
			{
				p_elmRes = SElmAntecesorExt ( p_lisObj->p_elmActual, p_lisObj->iPos - iPos );
			}
			else
			{
				p_elmRes = p_lisObj->p_elmActual;
			}
		}
		else
		{
			if ( iPos < p_lisObj->iNumElementos / 2 )
			{
				p_elmRes = SElmSucesorExt ( p_lisObj->p_elmPrimero, iPos );
			}
			else
			{
				/* El ultimo es iNumElementos - 1: hasta iPos hay
				   iNumElementos - 1 - iPos eslabones, no iNumElementos - iPos. */
				p_elmRes = SElmAntecesorExt ( p_lisObj->p_elmUltimo, p_lisObj->iNumElementos - 1 - iPos );
			}
		}
	}
	else
	{
		p_elmRes = NULL;
	}
	return ( p_elmRes );
}
