#include "UtilesColecciones.h"


#include "TiposBasicosConfig.h"




static byte * _UtlColDuplicar ( byte * p_byDatos, int iNumBytes, PFUNPBYTEPB fDuplicar )
{
	byte * p_byRes;

	if ( ES_VALIDO ( p_byDatos ) )
	{
		if ( ES_VALIDO ( fDuplicar ) )
		{
			p_byRes = fDuplicar ( p_byDatos );
		}
		else
		{
			p_byRes = (byte *) MemDuplicar ( (void *) p_byDatos, iNumBytes );
		}
	}
	else
	{
		p_byRes = NULL;
	}
	return ( p_byRes );
}

static SVectorPtr * _SLispConvertirAVector ( SListaPtr * p_lisObj, int iNumBytes, PFUNPBYTEPB fDuplicar )
{
	SVectorPtr *	p_vecRes;
	SElementoPtr *	p_elpObj;
	byte *			p_byDatos;
	int				iElem;
	int				iError;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		p_vecRes = SVecpCrear ( SLispNumElementos ( p_lisObj ) );
		if ( ES_VALIDO ( p_vecRes ) )
		{
			// El vector es duenno de las copias:
			SVecpActivarLiberacionMemoria ( p_vecRes );
			iElem = 0;
			iError = 0;
			p_elpObj = p_lisObj->p_elpPrimero;
			while ( ES_VALIDO ( p_elpObj ) && ( iError == 0 ) )
			{
				p_byDatos = _UtlColDuplicar ( SElpDatos ( p_elpObj ), iNumBytes, fDuplicar );
				if ( ES_VALIDO ( p_byDatos ) )
				{
					if ( SVecpAsignar ( p_vecRes, iElem, p_byDatos ) != 1 )
					{
						MemLiberar ( (void **) &p_byDatos );
						iError = 1;
					}
				}
				else
				{
					iError = 1;
				}
				iElem = iElem + 1;
				p_elpObj = SElpSucesor ( p_elpObj );
			}
			if ( iError == 1 )
			{
				SVecpDestruir ( &p_vecRes );
			}
		}
	}
	else
	{
		p_vecRes = NULL;
	}
	return ( p_vecRes );
}

static SListaPtr * _SVecpConvertirALista ( SVectorPtr * p_vecObj, int iNumBytes, PFUNPBYTEPB fDuplicar )
{
	SListaPtr *	p_lisRes;
	byte *		p_byDatos;
	int			iNumElementos;
	int			iElem;
	int			iError;

	if ( SVecpEsValido ( p_vecObj ) == 1 )
	{
		p_lisRes = SLispCrear ();
		if ( ES_VALIDO ( p_lisRes ) )
		{
			iNumElementos = SVecpNumElementos ( p_vecObj );
			iElem = 0;
			iError = 0;
			while ( ( iElem < iNumElementos ) && ( iError == 0 ) )
			{
				// Una posicion vacia del vector tambien es un error:
				p_byDatos = _UtlColDuplicar ( SVecpElemento ( p_vecObj, iElem ), iNumBytes, fDuplicar );
				if ( ES_VALIDO ( p_byDatos ) )
				{
					if ( SLispInsertarAlFinal ( p_lisRes, p_byDatos ) != 1 )
					{
						MemLiberar ( (void **) &p_byDatos );
						iError = 1;
					}
				}
				else
				{
					iError = 1;
				}
				iElem = iElem + 1;
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




SContenido * SElmConvertirAContenido ( SElemento * p_elmObj )
{
	SContenido *	p_conRes;
	SBloque *		p_blqDatos;

	if ( ES_VALIDO ( p_elmObj ) )
	{
		p_blqDatos = SBlqDuplicar ( SElmDatos ( p_elmObj ) );
		if ( ES_VALIDO ( p_blqDatos ) )
		{
			p_conRes = SConEncapsular ( p_blqDatos );
			if ( ES_NULO ( p_conRes ) )
			{
				SBlqDestruir ( &p_blqDatos );
			}
		}
		else
		{
			p_conRes = NULL;
		}
	}
	else
	{
		p_conRes = NULL;
	}
	return ( p_conRes );
}

SElemento * SConConvertirAElemento ( SContenido * p_conObj )
{
	SElemento *	p_elmRes;
	SBloque *	p_blqDatos;

	if ( ES_VALIDO ( p_conObj ) )
	{
		p_blqDatos = SBlqDuplicar ( SConDatos ( p_conObj ) );
		if ( ES_VALIDO ( p_blqDatos ) )
		{
			p_elmRes = SElmEncapsular ( p_blqDatos );
			if ( ES_NULO ( p_elmRes ) )
			{
				SBlqDestruir ( &p_blqDatos );
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

SVector * SLisConvertirAVector ( SLista * p_lisObj )
{
	SVector *		p_vecRes;
	SElemento *		p_elmObj;
	SContenido *	p_conDatos;
	int				iElem;
	int				iError;

	if ( ES_VALIDO ( p_lisObj ) )
	{
		p_vecRes = SVecCrear ( SLisNumElementos ( p_lisObj ) );
		if ( ES_VALIDO ( p_vecRes ) )
		{
			iElem = 0;
			iError = 0;
			p_elmObj = p_lisObj->p_elmPrimero;
			while ( ES_VALIDO ( p_elmObj ) && ( iError == 0 ) )
			{
				p_conDatos = SElmConvertirAContenido ( p_elmObj );
				if ( ES_VALIDO ( p_conDatos ) )
				{
					if ( SVecAsignar ( p_vecRes, iElem, p_conDatos ) != 1 )
					{
						SConDestruir ( &p_conDatos );
						iError = 1;
					}
				}
				else
				{
					iError = 1;
				}
				iElem = iElem + 1;
				p_elmObj = SElmSucesor ( p_elmObj );
			}
			if ( iError == 1 )
			{
				SVecDestruir ( &p_vecRes );
			}
		}
	}
	else
	{
		p_vecRes = NULL;
	}
	return ( p_vecRes );
}

SLista * SVecConvertirALista ( SVector * p_vecObj )
{
	SLista *	p_lisRes;
	SElemento *	p_elmDatos;
	int			iNumElementos;
	int			iElem;
	int			iError;

	if ( SVecEsValido ( p_vecObj ) == 1 )
	{
		p_lisRes = SLisCrear ();
		if ( ES_VALIDO ( p_lisRes ) )
		{
			iNumElementos = SVecNumElementos ( p_vecObj );
			iElem = 0;
			iError = 0;
			while ( ( iElem < iNumElementos ) && ( iError == 0 ) )
			{
				// Una posicion vacia del vector tambien es un error:
				p_elmDatos = SConConvertirAElemento ( SVecElemento ( p_vecObj, iElem ) );
				if ( ES_VALIDO ( p_elmDatos ) )
				{
					if ( SLisInsertarAlFinal ( p_lisRes, p_elmDatos ) != 1 )
					{
						SElmDestruir ( &p_elmDatos );
						iError = 1;
					}
				}
				else
				{
					iError = 1;
				}
				iElem = iElem + 1;
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

SVectorPtr * SLispConvertirAVector ( SListaPtr * p_lisObj, int iNumBytes )
{
	SVectorPtr * p_vecRes;

	if ( iNumBytes > 0 )
	{
		p_vecRes = _SLispConvertirAVector ( p_lisObj, iNumBytes, NULL );
	}
	else
	{
		p_vecRes = NULL;
	}
	return ( p_vecRes );
}

SListaPtr * SVecpConvertirALista ( SVectorPtr * p_vecObj, int iNumBytes )
{
	SListaPtr * p_lisRes;

	if ( iNumBytes > 0 )
	{
		p_lisRes = _SVecpConvertirALista ( p_vecObj, iNumBytes, NULL );
	}
	else
	{
		p_lisRes = NULL;
	}
	return ( p_lisRes );
}

SVectorPtr * SLispConvertirAVectorExt ( SListaPtr * p_lisObj, PFUNPBYTEPB fDuplicar )
{
	SVectorPtr * p_vecRes;

	if ( ES_VALIDO ( fDuplicar ) )
	{
		p_vecRes = _SLispConvertirAVector ( p_lisObj, 0, fDuplicar );
	}
	else
	{
		p_vecRes = NULL;
	}
	return ( p_vecRes );
}

SListaPtr * SVecpConvertirAListaExt ( SVectorPtr * p_vecObj, PFUNPBYTEPB fDuplicar )
{
	SListaPtr * p_lisRes;

	if ( ES_VALIDO ( fDuplicar ) )
	{
		p_lisRes = _SVecpConvertirALista ( p_vecObj, 0, fDuplicar );
	}
	else
	{
		p_lisRes = NULL;
	}
	return ( p_lisRes );
}

/* Secuencia y conjunto envuelven una lista: las conversiones delegan en las
   copias de lista que ya existen. A conjunto, SCnj(p)CrearDesdeLista copia
   los datos distintos y descarta los repetidos; a secuencia, se duplica la
   lista del conjunto, que sale en su orden, y la secuencia se queda con la
   copia. Si falla cualquier copia, NULL. */
SConjunto * SSecConvertirAConjunto ( SSecuencia * p_secObj, PFUNINTPVPV fComparar )
{
	SConjunto *	p_cnjRes;

	if ( SSecEsValida ( p_secObj ) == 1 )
	{
		p_cnjRes = SCnjCrearDesdeLista ( SSecLista ( p_secObj ), fComparar );
	}
	else
	{
		p_cnjRes = NULL;
	}
	return ( p_cnjRes );
}

SSecuencia * SCnjConvertirASecuencia ( SConjunto * p_cnjObj )
{
	SSecuencia *	p_secRes;
	SLista *		p_lisCopia;

	if ( SCnjEsValido ( p_cnjObj ) == 1 )
	{
		p_lisCopia = SLisOrdDuplicarLista ( SCnjLista ( p_cnjObj ) );
		p_secRes = SSecEncapsularLista ( p_lisCopia );
		if ( ES_NULO ( p_secRes ) )
		{
			SLisDestruir ( &p_lisCopia );
		}
	}
	else
	{
		p_secRes = NULL;
	}
	return ( p_secRes );
}

/* En las Ptr el resultado es dueno de sus copias: el conjunto y la lista
   duplicada salen con la liberacion activada. */
SConjuntoPtr * SSecpConvertirAConjunto ( SSecuenciaPtr * p_secObj, PFUNINTPVPV fComparar, int iNumBytes )
{
	SConjuntoPtr *	p_cnjRes;

	if ( SSecpEsValida ( p_secObj ) == 1 )
	{
		p_cnjRes = SCnjpCrearDesdeLista ( SSecpLista ( p_secObj ), fComparar, iNumBytes );
	}
	else
	{
		p_cnjRes = NULL;
	}
	return ( p_cnjRes );
}

SSecuenciaPtr * SCnjpConvertirASecuencia ( SConjuntoPtr * p_cnjObj, int iNumBytes )
{
	SSecuenciaPtr *	p_secRes;
	SListaPtr *		p_lisCopia;

	if ( SCnjpEsValido ( p_cnjObj ) == 1 )
	{
		p_lisCopia = SLispOrdDuplicarLista ( SCnjpLista ( p_cnjObj ), iNumBytes );
		p_secRes = SSecpEncapsularLista ( p_lisCopia );
		if ( ES_NULO ( p_secRes ) )
		{
			SLispDestruir ( &p_lisCopia );
		}
	}
	else
	{
		p_secRes = NULL;
	}
	return ( p_secRes );
}

SConjuntoPtr * SSecpConvertirAConjuntoExt ( SSecuenciaPtr * p_secObj, PFUNINTPVPV fComparar, PFUNPBYTEPB fDuplicar )
{
	SConjuntoPtr *	p_cnjRes;

	if ( SSecpEsValida ( p_secObj ) == 1 )
	{
		p_cnjRes = SCnjpCrearDesdeListaExt ( SSecpLista ( p_secObj ), fComparar, fDuplicar );
	}
	else
	{
		p_cnjRes = NULL;
	}
	return ( p_cnjRes );
}

SSecuenciaPtr * SCnjpConvertirASecuenciaExt ( SConjuntoPtr * p_cnjObj, PFUNPBYTEPB fDuplicar )
{
	SSecuenciaPtr *	p_secRes;
	SListaPtr *		p_lisCopia;

	if ( SCnjpEsValido ( p_cnjObj ) == 1 )
	{
		p_lisCopia = SLispOrdDuplicarListaExt ( SCnjpLista ( p_cnjObj ), fDuplicar );
		p_secRes = SSecpEncapsularLista ( p_lisCopia );
		if ( ES_NULO ( p_secRes ) )
		{
			SLispDestruir ( &p_lisCopia );
		}
	}
	else
	{
		p_secRes = NULL;
	}
	return ( p_secRes );
}
