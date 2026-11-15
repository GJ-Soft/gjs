#include "SSecuenciaUnica.h"

#include "TiposBasicosConfig.h"


static int _SSecUnTieneRepetidos ( SLista * p_lisDatos );
static int _SSecUnCopiar ( SSecuencia * p_secDest, SLista * p_lisValores );
static int _SSecUnMover ( SSecuencia * p_secDest, SLista * p_lisValores );
static SSecuenciaUnica * _SSecUnEnvolver ( SSecuencia * p_secDatos );
static SSecuenciaUnica * _SSecUnEnvolverExtraidos ( SSecuenciaUnica * p_secObj, SSecuencia * p_secExt );



SSecuenciaUnica * SSecUnCrear ()
{
	SSecuenciaUnica * p_secObj;

	p_secObj = (SSecuenciaUnica *) MemReservar ( sizeof ( SSecuenciaUnica ) );
	if ( ES_VALIDO ( p_secObj ) )
	{
		p_secObj->p_secDatos = SSecCrear ();
	}
	return ( p_secObj );
}

/* Secuencia con COPIAS de los elementos de la lista, que no se toca; los
   repetidos se copian una vez, en el orden de su primera aparicion. Si falla
   alguna copia, NULL. */
SSecuenciaUnica * SSecUnCrearDesdeLista ( SLista * p_lisValores )
{
	SSecuenciaUnica *	p_secRes;

	if ( SLisEsValida ( p_lisValores ) == 1 )
	{
		p_secRes = SSecUnCrear ();
		if ( _SSecUnCopiar ( SSecUnSecuencia ( p_secRes ), p_lisValores ) != 1 )
		{
			SSecUnDestruir ( &p_secRes );
		}
	}
	else
	{
		p_secRes = NULL;
	}
	return ( p_secRes );
}

SSecuenciaUnica * SSecUnCrearDesdeSecuencia ( SSecuencia * p_secValores )
{
	return ( SSecUnCrearDesdeLista ( SSecLista ( p_secValores ) ) );
}

void SSecUnDestruir ( SSecuenciaUnica ** p_p_secObj )
{
	SSecuenciaUnica * p_secObj;

	if ( ES_VALIDO ( p_p_secObj ) )
	{
		p_secObj = *p_p_secObj;

		if ( ES_VALIDO ( p_secObj ) )
		{
			SSecDestruir ( &(p_secObj->p_secDatos) );
			MemLiberar ( (void **) p_p_secObj );
		}
	}
}

/* Valida, y sin repetidos. Comprobarlo recorre la secuencia para cada
   elemento: las demas funciones no la llaman, porque Insertar y las
   operaciones ya mantienen la secuencia sin repetidos. */
int SSecUnEsValida ( SSecuenciaUnica * p_secObj )
{
	int	iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		if ( SSecEsValida ( p_secObj->p_secDatos ) == 1 )
		{
			iRes = 1 - _SSecUnTieneRepetidos ( SSecLista ( p_secObj->p_secDatos ) );
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

int SSecUnNumElementos ( SSecuenciaUnica * p_secObj )
{
	int	iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		iRes = SSecNumElementos ( p_secObj->p_secDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SSecUnEstaVacia ( SSecuenciaUnica * p_secObj )
{
	int	iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		iRes = SSecEstaVacia ( p_secObj->p_secDatos );
	}
	else
	{
		iRes = 1;
	}
	return ( iRes );
}

SElemento * SSecUnElemento ( SSecuenciaUnica * p_secObj, int iElem )
{
	SElemento *	p_elmRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		p_elmRes = SSecElemento ( p_secObj->p_secDatos, iElem );
	}
	else
	{
		p_elmRes = NULL;
	}
	return ( p_elmRes );
}

/* Buscan por el contenido de p_elmObj, que no hace falta que este en la
   secuencia. Buscar da la posicion, o -1: como no hay repetidos, es la
   unica. */
int SSecUnExiste ( SSecuenciaUnica * p_secObj, SElemento * p_elmObj )
{
	int	iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		iRes = SSecExiste ( p_secObj->p_secDatos, p_elmObj );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SSecUnBuscar ( SSecuenciaUnica * p_secObj, SElemento * p_elmObj )
{
	int	iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		iRes = SSecBuscar ( p_secObj->p_secDatos, p_elmObj );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

/* Inserta al final si no hay otro igual; si lo hay, 0 y el elemento sigue
   siendo del llamante. */
int SSecUnInsertar ( SSecuenciaUnica * p_secObj, SElemento * p_elmObj )
{
	int	iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		if ( ES_VALIDO ( p_elmObj ) )
		{
			if ( SSecExiste ( p_secObj->p_secDatos, p_elmObj ) == 0 )
			{
				iRes = SSecInsertar ( p_secObj->p_secDatos, p_elmObj );
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

int SSecUnEliminar ( SSecuenciaUnica * p_secObj, int iElem )
{
	int	iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		iRes = SSecEliminar ( p_secObj->p_secDatos, iElem );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

SElemento * SSecUnExtraer ( SSecuenciaUnica * p_secObj, int iElem )
{
	SElemento *	p_elmRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		p_elmRes = SSecExtraer ( p_secObj->p_secDatos, iElem );
	}
	else
	{
		p_elmRes = NULL;
	}
	return ( p_elmRes );
}

int SSecUnVaciar ( SSecuenciaUnica * p_secObj )
{
	int	iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		iRes = SSecVaciar ( p_secObj->p_secDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

/* Secuencia nueva con copias de los elementos, en el mismo orden. */
SSecuenciaUnica * SSecUnDuplicar ( SSecuenciaUnica * p_secObj )
{
	SSecuenciaUnica *	p_secRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		p_secRes = _SSecUnEnvolver ( SSecDuplicar ( p_secObj->p_secDatos ) );
	}
	else
	{
		p_secRes = NULL;
	}
	return ( p_secRes );
}

/* La secuencia interna, y la lista de esa secuencia. */
SSecuencia * SSecUnSecuencia ( SSecuenciaUnica * p_secObj )
{
	SSecuencia *	p_secRes;

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

SLista * SSecUnLista ( SSecuenciaUnica * p_secObj )
{
	return ( SSecLista ( SSecUnSecuencia ( p_secObj ) ) );
}

/* Las operaciones con otras secuencias y listas tienen tres formas: con otra
   secuencia unica, con una secuencia y con una lista; las dos primeras pasan
   la lista de la segunda. Comparan el contenido, como las de SSecuencia. */
int SSecUnExistenTodos ( SSecuenciaUnica * p_secObj, SSecuenciaUnica * p_secValores )
{
	int	iRes;

	if ( ES_VALIDO ( p_secValores ) )
	{
		iRes = SSecUnExistenTodosSecuencia ( p_secObj, p_secValores->p_secDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SSecUnExistenTodosSecuencia ( SSecuenciaUnica * p_secObj, SSecuencia * p_secValores )
{
	int	iRes;

	if ( ES_VALIDO ( p_secValores ) )
	{
		iRes = SSecUnExistenTodosLista ( p_secObj, SSecLista ( p_secValores ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SSecUnExistenTodosLista ( SSecuenciaUnica * p_secObj, SLista * p_lisValores )
{
	int	iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		if ( ES_VALIDO ( p_lisValores ) )
		{
			iRes = SSecExistenTodosLista ( p_secObj->p_secDatos, p_lisValores );
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

int SSecUnExisteAlguno ( SSecuenciaUnica * p_secObj, SSecuenciaUnica * p_secValores )
{
	int	iRes;

	if ( ES_VALIDO ( p_secValores ) )
	{
		iRes = SSecUnExisteAlgunoSecuencia ( p_secObj, p_secValores->p_secDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SSecUnExisteAlgunoSecuencia ( SSecuenciaUnica * p_secObj, SSecuencia * p_secValores )
{
	int	iRes;

	if ( ES_VALIDO ( p_secValores ) )
	{
		iRes = SSecUnExisteAlgunoLista ( p_secObj, SSecLista ( p_secValores ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SSecUnExisteAlgunoLista ( SSecuenciaUnica * p_secObj, SLista * p_lisValores )
{
	int	iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		if ( ES_VALIDO ( p_lisValores ) )
		{
			iRes = SSecExisteAlgunoLista ( p_secObj->p_secDatos, p_lisValores );
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

int SSecUnEliminarSecuenciaUn ( SSecuenciaUnica * p_secObj, SSecuenciaUnica * p_secValores )
{
	int	iRes;

	if ( ES_VALIDO ( p_secValores ) )
	{
		iRes = SSecUnEliminarSecuencia ( p_secObj, p_secValores->p_secDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SSecUnEliminarSecuencia ( SSecuenciaUnica * p_secObj, SSecuencia * p_secValores )
{
	int	iRes;

	if ( ES_VALIDO ( p_secValores ) )
	{
		iRes = SSecUnEliminarLista ( p_secObj, SSecLista ( p_secValores ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SSecUnEliminarLista ( SSecuenciaUnica * p_secObj, SLista * p_lisValores )
{
	int	iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		if ( ES_VALIDO ( p_lisValores ) )
		{
			iRes = SSecEliminarLista ( p_secObj->p_secDatos, p_lisValores );
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

/* Concatenar MUEVE al final los valores que no esten ya; los que estan se
   quedan en la de entrada, y de los repetidos de esta solo pasa el primero.
   Las Dup anaden COPIAS de los que falten y no tocan la de entrada. */
int SSecUnConcatenar ( SSecuenciaUnica * p_secObj, SSecuenciaUnica * p_secValores )
{
	int	iRes;

	if ( ES_VALIDO ( p_secValores ) )
	{
		iRes = SSecUnConcatenarSecuencia ( p_secObj, p_secValores->p_secDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SSecUnConcatenarSecuencia ( SSecuenciaUnica * p_secObj, SSecuencia * p_secValores )
{
	int	iRes;

	if ( ES_VALIDO ( p_secValores ) )
	{
		iRes = SSecUnConcatenarLista ( p_secObj, SSecLista ( p_secValores ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SSecUnConcatenarLista ( SSecuenciaUnica * p_secObj, SLista * p_lisValores )
{
	int	iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		if ( ES_VALIDO ( p_lisValores ) )
		{
			iRes = _SSecUnMover ( p_secObj->p_secDatos, p_lisValores );
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

int SSecUnConcatenarDup ( SSecuenciaUnica * p_secObj, SSecuenciaUnica * p_secValores )
{
	int	iRes;

	if ( ES_VALIDO ( p_secValores ) )
	{
		iRes = SSecUnConcatenarSecuenciaDup ( p_secObj, p_secValores->p_secDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SSecUnConcatenarSecuenciaDup ( SSecuenciaUnica * p_secObj, SSecuencia * p_secValores )
{
	int	iRes;

	if ( ES_VALIDO ( p_secValores ) )
	{
		iRes = SSecUnConcatenarListaDup ( p_secObj, SSecLista ( p_secValores ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SSecUnConcatenarListaDup ( SSecuenciaUnica * p_secObj, SLista * p_lisValores )
{
	int	iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		if ( ES_VALIDO ( p_lisValores ) )
		{
			iRes = _SSecUnCopiar ( p_secObj->p_secDatos, p_lisValores );
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

/* Las Extraer MUEVEN los valores a una secuencia unica nueva. Si no se puede
   crear, vuelven al final de p_secObj y se devuelve NULL. */
SSecuenciaUnica * SSecUnExtraerSecuenciaUn ( SSecuenciaUnica * p_secObj, SSecuenciaUnica * p_secValores )
{
	SSecuenciaUnica *	p_secRes;

	if ( ES_VALIDO ( p_secValores ) )
	{
		p_secRes = SSecUnExtraerSecuencia ( p_secObj, p_secValores->p_secDatos );
	}
	else
	{
		p_secRes = NULL;
	}
	return ( p_secRes );
}

SSecuenciaUnica * SSecUnExtraerSecuencia ( SSecuenciaUnica * p_secObj, SSecuencia * p_secValores )
{
	SSecuenciaUnica *	p_secRes;

	if ( ES_VALIDO ( p_secValores ) )
	{
		p_secRes = SSecUnExtraerLista ( p_secObj, SSecLista ( p_secValores ) );
	}
	else
	{
		p_secRes = NULL;
	}
	return ( p_secRes );
}

SSecuenciaUnica * SSecUnExtraerLista ( SSecuenciaUnica * p_secObj, SLista * p_lisValores )
{
	SSecuenciaUnica *	p_secRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		if ( ES_VALIDO ( p_lisValores ) )
		{
			p_secRes = _SSecUnEnvolverExtraidos ( p_secObj, SSecExtraerLista ( p_secObj->p_secDatos, p_lisValores ) );
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

/* Union: copias de la primera y, detras, de las de la segunda que no estan
   en la primera. Interseccion y Diferencia, copias en el orden de la
   primera. Si algo falla, NULL. */
SSecuenciaUnica * SSecUnUnion ( SSecuenciaUnica * p_secValores1, SSecuenciaUnica * p_secValores2 )
{
	SSecuenciaUnica *	p_secRes;

	if ( ES_VALIDO ( p_secValores1 ) )
	{
		if ( ES_VALIDO ( p_secValores2 ) )
		{
			p_secRes = SSecUnDuplicar ( p_secValores1 );
			if ( _SSecUnCopiar ( SSecUnSecuencia ( p_secRes ), SSecUnLista ( p_secValores2 ) ) != 1 )
			{
				SSecUnDestruir ( &p_secRes );
			}
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

SSecuenciaUnica * SSecUnInterseccion ( SSecuenciaUnica * p_secValores1, SSecuenciaUnica * p_secValores2 )
{
	SSecuenciaUnica *	p_secRes;

	if ( ES_VALIDO ( p_secValores1 ) )
	{
		if ( ES_VALIDO ( p_secValores2 ) )
		{
			p_secRes = _SSecUnEnvolver ( SSecInterseccion ( p_secValores1->p_secDatos, p_secValores2->p_secDatos ) );
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

SSecuenciaUnica * SSecUnDiferencia ( SSecuenciaUnica * p_secValores1, SSecuenciaUnica * p_secValores2 )
{
	SSecuenciaUnica *	p_secRes;

	if ( ES_VALIDO ( p_secValores1 ) )
	{
		if ( ES_VALIDO ( p_secValores2 ) )
		{
			p_secRes = _SSecUnEnvolver ( SSecDiferencia ( p_secValores1->p_secDatos, p_secValores2->p_secDatos ) );
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


/* 1 si algun elemento tiene otro igual detras. */
static int _SSecUnTieneRepetidos ( SLista * p_lisDatos )
{
	int			iRes;
	int			iPos;
	SElemento *	p_elmObj;

	iRes = 0;
	iPos = 0;
	/* Por la CADENA, no por indice: el indice entra por el extremo mas
	   cercano, asi que un recorrido completo sale cuadratico. */
	p_elmObj = SLisElemento ( p_lisDatos, 0 );
	while ( ES_VALIDO ( p_elmObj ) && ( iRes == 0 ) )
	{
		if ( SLisBuscarSiguienteElem ( p_lisDatos, p_elmObj, iPos ) >= 0 )
		{
			iRes = 1;
		}
		iPos = iPos + 1;
		p_elmObj = SElmSucesor ( p_elmObj );
	}
	return ( iRes );
}

/* Anade al final de p_secDest copias de los elementos de p_lisValores que no
   esten ya. 0 si p_secDest no es valida, si es la misma lista o si falla una
   copia; lo copiado hasta ahi se queda. */
static int _SSecUnCopiar ( SSecuencia * p_secDest, SLista * p_lisValores )
{
	int			iRes;
	SElemento *	p_elmObj;
	SElemento *	p_elmNuevo;

	if ( SSecEsValida ( p_secDest ) == 1 )
	{
		if ( SSecLista ( p_secDest ) != p_lisValores )
		{
			iRes = 1;
			p_elmObj = SLisElemento ( p_lisValores, 0 );
			while ( ES_VALIDO ( p_elmObj ) && ( iRes == 1 ) )
			{
				if ( SSecExiste ( p_secDest, p_elmObj ) == 0 )
				{
					p_elmNuevo = SElmDuplicar ( p_elmObj );
					if ( SSecInsertar ( p_secDest, p_elmNuevo ) != 1 )
					{
						SElmDestruir ( &p_elmNuevo );
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
	return ( iRes );
}

/* Mueve al final de p_secDest los elementos de p_lisValores que no esten ya;
   los demas se quedan en p_lisValores. Si no se puede insertar uno, vuelve al
   final de p_lisValores: no se pierde. */
static int _SSecUnMover ( SSecuencia * p_secDest, SLista * p_lisValores )
{
	int			iRes;
	int			iPos;
	SElemento *	p_elmObj;
	SElemento *	p_elmSig;
	SElemento *	p_elmExt;

	if ( SSecEsValida ( p_secDest ) == 1 )
	{
		if ( SSecLista ( p_secDest ) != p_lisValores )
		{
			iRes = 1;
			iPos = 0;
			p_elmObj = SLisElemento ( p_lisValores, 0 );
			while ( ES_VALIDO ( p_elmObj ) && ( iRes == 1 ) )
			{
				/* El sucesor, ANTES de extraer. */
				p_elmSig = SElmSucesor ( p_elmObj );
				if ( SSecExiste ( p_secDest, p_elmObj ) == 0 )
				{
					p_elmExt = SLisExtraerElem ( p_lisValores, iPos );
					if ( SSecInsertar ( p_secDest, p_elmExt ) != 1 )
					{
						SLisInsertarAlFinal ( p_lisValores, p_elmExt );
						iRes = 0;
					}
				}
				else
				{
					iPos = iPos + 1;
				}
				p_elmObj = p_elmSig;
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

/* Envuelve una secuencia ya creada, que no tiene repetidos; si no hay o no se
   puede envolver, NULL y la secuencia se destruye. */
static SSecuenciaUnica * _SSecUnEnvolver ( SSecuencia * p_secDatos )
{
	SSecuenciaUnica * p_secRes;

	if ( ES_VALIDO ( p_secDatos ) )
	{
		p_secRes = (SSecuenciaUnica *) MemReservar ( sizeof ( SSecuenciaUnica ) );
		if ( ES_VALIDO ( p_secRes ) )
		{
			p_secRes->p_secDatos = p_secDatos;
		}
		else
		{
			SSecDestruir ( &p_secDatos );
		}
	}
	else
	{
		p_secRes = NULL;
	}
	return ( p_secRes );
}

/* Envuelve lo que haya sacado una Extraer de SSecuencia. Si no se puede, los
   elementos vuelven al final de p_secObj: no se pierden. */
static SSecuenciaUnica * _SSecUnEnvolverExtraidos ( SSecuenciaUnica * p_secObj, SSecuencia * p_secExt )
{
	SSecuenciaUnica * p_secRes;

	if ( ES_VALIDO ( p_secExt ) )
	{
		p_secRes = (SSecuenciaUnica *) MemReservar ( sizeof ( SSecuenciaUnica ) );
		if ( ES_VALIDO ( p_secRes ) )
		{
			p_secRes->p_secDatos = p_secExt;
		}
		else
		{
			SSecConcatenar ( p_secObj->p_secDatos, p_secExt );
			SSecDestruir ( &p_secExt );
		}
	}
	else
	{
		p_secRes = NULL;
	}
	return ( p_secRes );
}
