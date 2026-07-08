#include "SElemento.h"


#include "TiposBasicosConfig.h"




SElemento * SElmCrear ( int iTam )
{
	SElemento * p_elmObj;
	
	if ( iTam > 0 )
	{
		p_elmObj = (SElemento *) MemReservar ( sizeof ( SElemento ) );
		if ( ES_VALIDO ( p_elmObj ) )
		{
			p_elmObj->p_elmAnt = NULL;
			p_elmObj->p_elmSig = NULL;

			p_elmObj->p_blqDatos = SBlqCrear ( iTam );
			if ( ES_VALIDO ( p_elmObj->p_blqDatos ) )
			{
				p_elmObj->iLiberar = 1;
			}
			else
			{
				p_elmObj->iLiberar = 0;
			}
		}
	}
	else
	{
		p_elmObj = NULL;
	}
	return ( p_elmObj );
}

SElemento * SElmCrearEntero ()
{
	return ( SElmCrear ( sizeof ( int ) ) );
}

SElemento * SElmCrearEnteroSinSigno ()
{
	return ( SElmCrear ( sizeof ( unsigned int ) ) );
}

SElemento * SElmCrearEnteroLargo ()
{
	return ( SElmCrear ( sizeof ( long ) ) );
}

SElemento * SElmCrearEnteroLargoSinSigno ()
{
	return ( SElmCrear ( sizeof ( unsigned long ) ) );
}

SElemento * SElmCrearReal ()
{
	return ( SElmCrear ( sizeof ( float ) ) );
}

SElemento * SElmCrearRealDoble ()
{
	return ( SElmCrear ( sizeof ( double ) ) );
}

SElemento * SElmCrearCadena ()
{
	return ( SElmCrear ( sizeof ( char * ) ) );
}

SElemento * SElmEncapsular ( SBloque * p_blqDatos )
{
	SElemento * p_elmObj;
	
	if ( ES_VALIDO ( p_blqDatos ) )
	{
		p_elmObj= (SElemento *) MemReservar ( sizeof ( SElemento ) );
		if ( ES_VALIDO ( p_elmObj ) )
		{
			p_elmObj->p_elmAnt = NULL;
			p_elmObj->p_elmSig = NULL;

			p_elmObj->p_blqDatos = p_blqDatos;
			p_elmObj->iLiberar = SBlqLiberacionMemoriaActivada ( p_blqDatos );
		}
	}
	else
	{
		p_elmObj = NULL;
	}
	return ( p_elmObj );
}

SElemento * SElmEncapsularDir ( byte * p_byDirDatos, int iTamDatos, int iLiberar )
{
	SElemento * p_elmObj;
	
	if ( ES_VALIDO ( p_byDirDatos ) && ( iTamDatos > 0 ) && BOOL_VALIDO ( iLiberar ) )
	{
		p_elmObj= (SElemento *) MemReservar ( sizeof ( SElemento ) );
		if ( ES_VALIDO ( p_elmObj ) )
		{
			p_elmObj->p_elmAnt = NULL;
			p_elmObj->p_elmSig = NULL;

			p_elmObj->p_blqDatos = SBlqAsignar ( p_byDirDatos, iTamDatos, iLiberar );
			if ( ES_VALIDO ( p_elmObj->p_blqDatos ) )
			{
				p_elmObj->iLiberar = SBlqLiberacionMemoriaActivada ( p_elmObj->p_blqDatos );
			}
			else
			{
				p_elmObj->iLiberar = 0;
			}
		}
	}
	else
	{
		p_elmObj = NULL;
	}
	return ( p_elmObj );
}

void SElmDestruir ( SElemento ** p_p_elmObj )
{
	SElemento * p_elmObj;
	
	if ( ES_VALIDO ( p_p_elmObj ) )
	{
		p_elmObj = *p_p_elmObj;

		if ( ES_VALIDO ( p_elmObj ) )
		{
			if ( p_elmObj->iLiberar == 1 )
			{
				SBlqDestruir ( &(p_elmObj->p_blqDatos) );
			}
			MemLiberar ( (void **) p_p_elmObj );
		}
	}
}

int SElmEsValido ( SElemento * p_elmObj )
{
	int iRes;

	if ( ES_VALIDO ( p_elmObj ) )
	{
		if ( ES_VALIDO ( p_elmObj->p_blqDatos ) )
		{
			if ( SBlqEsValido ( p_elmObj->p_blqDatos ) == 1 )
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
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

SBloque * SElmDatos ( SElemento * p_elmObj )
{
	SBloque * p_blqRes;

	if ( ES_VALIDO ( p_elmObj ) )
	{
		p_blqRes = p_elmObj->p_blqDatos;
	}
	else
	{
		p_blqRes = NULL;
	}
	return ( p_blqRes );
}

int SElmEntero ( SElemento * p_elmObj )
{
	int	iRes;

	if ( ES_VALIDO ( p_elmObj ) )
	{
		iRes = SBlqEntero ( p_elmObj->p_blqDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

unsigned int SElmEnteroSinSigno ( SElemento * p_elmObj )
{
	unsigned int uiRes;

	if ( ES_VALIDO ( p_elmObj ) )
	{
		uiRes = SBlqEnteroSinSigno ( p_elmObj->p_blqDatos );
	}
	else
	{
		uiRes = 0;
	}
	return ( uiRes );
}

long SElmEnteroLargo ( SElemento * p_elmObj )
{
	long lRes;

	if ( ES_VALIDO ( p_elmObj ) )
	{
		lRes = SBlqEnteroLargo ( p_elmObj->p_blqDatos );
	}
	else
	{
		lRes = 0;
	}
	return ( lRes );
}

unsigned long SElmEnteroLargoSinSigno ( SElemento * p_elmObj )
{
	unsigned long ulRes;

	if ( ES_VALIDO ( p_elmObj ) )
	{
		ulRes = SBlqEnteroLargoSinSigno ( p_elmObj->p_blqDatos );
	}
	else
	{
		ulRes = 0;
	}
	return ( ulRes );
}

float SElmReal ( SElemento * p_elmObj )
{
	float fRes;

	if ( ES_VALIDO ( p_elmObj ) )
	{
		fRes = SBlqReal ( p_elmObj->p_blqDatos );
	}
	else
	{
		fRes = 0;
	}
	return ( fRes );
}

double SElmRealDoble ( SElemento * p_elmObj )
{
	double dRes;

	if ( ES_VALIDO ( p_elmObj ) )
	{
		dRes = SBlqRealDoble ( p_elmObj->p_blqDatos );
	}
	else
	{
		dRes = 0;
	}
	return ( dRes );
}

char * SElmCadena ( SElemento * p_elmObj )
{
	char * p_cRes;

	if ( ES_VALIDO ( p_elmObj ) )
	{
		p_cRes = SBlqCadena ( p_elmObj->p_blqDatos );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

int SElmTieneDatos ( SElemento * p_elmObj )
{
	int iRes;

	if ( SElmEsValido ( p_elmObj ) )
	{
		if ( SBlqTam ( p_elmObj->p_blqDatos ) > 0 )
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

int SElmModificar ( SElemento * p_elmObj, SBloque * p_blqDatos )
{
	int iRes;

	if ( ES_VALIDO ( p_elmObj ) && ES_VALIDO ( p_blqDatos ) )
	{
		if ( p_elmObj->iLiberar == 1 )
		{
			SBlqDestruir ( &(p_elmObj->p_blqDatos) );
		}

		p_elmObj->p_blqDatos = p_blqDatos;
		p_elmObj->iLiberar = SBlqLiberacionMemoriaActivada ( p_blqDatos );
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SElmModificarDir ( SElemento * p_elmObj, byte * p_byDirDatos, int iTamDatos, int iLiberar )
{
	int iRes;

	if ( ES_VALIDO ( p_elmObj ) && ES_VALIDO ( p_byDirDatos ) && ( iTamDatos > 0 ) && 
		 BOOL_VALIDO ( iLiberar ) )
	{
		if ( p_elmObj->iLiberar == 1 )
		{
			SBlqDestruir ( &(p_elmObj->p_blqDatos) );
		}

		p_elmObj->p_blqDatos = SBlqAsignar ( p_byDirDatos, iTamDatos, iLiberar );
		if ( ES_VALIDO ( p_elmObj->p_blqDatos ) )
		{
			iRes = 1;
			p_elmObj->iLiberar = SBlqLiberacionMemoriaActivada ( p_elmObj->p_blqDatos );
		}
		else
		{
			iRes = 0;
			p_elmObj->iLiberar = 0;
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SElmEscribirByte ( SElemento * p_elmObj, int iPos, byte byValor )
{
	int iRes;

	if ( ES_VALIDO ( p_elmObj ) )
	{
		iRes = SBlqEscribirByte ( p_elmObj->p_blqDatos, iPos, byValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SElmEscribirEntero ( SElemento * p_elmObj, int iValor )
{
	int iRes;

	if ( ES_VALIDO ( p_elmObj ) )
	{
		iRes = SBlqEscribirEntero ( p_elmObj->p_blqDatos, iValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SElmEscribirEnteroSinSigno ( SElemento * p_elmObj, unsigned int uiValor )
{
	int iRes;

	if ( ES_VALIDO ( p_elmObj ) )
	{
		iRes = SBlqEscribirEnteroSinSigno ( p_elmObj->p_blqDatos, uiValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SElmEscribirEnteroLargo ( SElemento * p_elmObj, long lValor )
{
	int iRes;

	if ( ES_VALIDO ( p_elmObj ) )
	{
		iRes = SBlqEscribirEnteroLargo ( p_elmObj->p_blqDatos, lValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SElmEscribirEnteroLargoSinSigno ( SElemento * p_elmObj, unsigned long ulValor )
{
	int iRes;

	if ( ES_VALIDO ( p_elmObj ) )
	{
		iRes = SBlqEscribirEnteroLargoSinSigno ( p_elmObj->p_blqDatos, ulValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SElmEscribirReal ( SElemento * p_elmObj, float fValor )
{
	int iRes;

	if ( ES_VALIDO ( p_elmObj ) )
	{
		iRes = SBlqEscribirReal ( p_elmObj->p_blqDatos, fValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SElmEscribirRealDoble ( SElemento * p_elmObj, double dValor )
{
	int iRes;

	if ( ES_VALIDO ( p_elmObj ) )
	{
		iRes = SBlqEscribirRealDoble ( p_elmObj->p_blqDatos, dValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SElmEscribirCadena ( SElemento * p_elmObj, const char * p_cValor )
{
	int iRes;

	if ( ES_VALIDO ( p_elmObj ) )
	{
		iRes = SBlqEscribirCadena ( p_elmObj->p_blqDatos, p_cValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

SElemento * SElmAntecesor ( SElemento * p_elmObj )
{
	SElemento * p_elmRes;

	if ( ES_VALIDO ( p_elmObj ) )
	{
		p_elmRes = (SElemento *) p_elmObj->p_elmAnt;
	}
	else
	{
		p_elmRes = NULL;
	}
	return ( p_elmRes );
}

SElemento * SElmSucesor ( SElemento * p_elmObj )
{
	SElemento * p_elmRes;

	if ( ES_VALIDO ( p_elmObj ) )
	{
		p_elmRes = (SElemento *) p_elmObj->p_elmSig;
	}
	else
	{
		p_elmRes = NULL;
	}
	return ( p_elmRes );
}

int SElmTieneAntecesor ( SElemento * p_elmObj )
{
	int iRes;

	if ( ES_VALIDO ( p_elmObj ) )
	{
		if ( ES_VALIDO ( p_elmObj->p_elmAnt ) )
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

int SElmTieneSucesor ( SElemento * p_elmObj )
{
	int iRes;

	if ( ES_VALIDO ( p_elmObj ) )
	{
		if ( ES_VALIDO ( p_elmObj->p_elmSig ) )
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

int SElmEncadenarAntecesor ( SElemento * p_elmObj, SElemento * p_elmAnt )
{
	int iRes;

	if ( ES_VALIDO ( p_elmObj ) )
	{
		if ( p_elmObj->p_elmAnt != p_elmAnt )
		{
			p_elmObj->p_elmAnt = (void *) p_elmAnt;
			SElmEncadenarSucesor ( p_elmAnt, p_elmObj );
		}
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SElmEncadenarSucesor ( SElemento * p_elmObj, SElemento * p_elmSuc )
{
	int iRes;

	if ( ES_VALIDO ( p_elmObj ) )
	{
		if ( p_elmObj->p_elmSig != p_elmSuc )
		{
			p_elmObj->p_elmSig = (void *) p_elmSuc;
			iRes = SElmEncadenarAntecesor ( p_elmSuc, p_elmObj );
		}
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SElmDesencadenarAntecesor ( SElemento * p_elmObj )
{
	int iRes;

	if ( ES_VALIDO ( p_elmObj ) )
	{
		if ( ES_VALIDO ( p_elmObj->p_elmAnt ) )
		{
			((SElemento *) p_elmObj->p_elmAnt)->p_elmSig = NULL;
		}
		p_elmObj->p_elmAnt = NULL;
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SElmDesencadenarSucesor ( SElemento * p_elmObj )
{
	int iRes;

	if ( ES_VALIDO ( p_elmObj ) )
	{
		if ( ES_VALIDO ( p_elmObj->p_elmSig ) )
		{
			((SElemento *) p_elmObj->p_elmSig)->p_elmAnt = NULL;
		}
		p_elmObj->p_elmSig = NULL;
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SElmDesencadenar ( SElemento * p_elmObj )
{
	int iRes;

	if ( ES_VALIDO ( p_elmObj ) )
	{
		if ( ES_VALIDO ( p_elmObj->p_elmSig ) )
		{
			SElmDesencadenarAntecesor ( (SElemento *) p_elmObj->p_elmSig );
		}
		if ( ES_VALIDO ( p_elmObj->p_elmAnt ) )
		{
			SElmDesencadenarSucesor ( (SElemento *) p_elmObj->p_elmAnt );
		}
		p_elmObj->p_elmAnt = NULL;
		p_elmObj->p_elmSig = NULL;
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

// Anula solo los enlaces propios del elemento, sin tocar a sus vecinos.
// Se usa al extraer un elemento de una lista para devolverlo desligado.
void SElmDeposicionar ( SElemento * p_elmObj )
{
	if ( ES_VALIDO ( p_elmObj ) )
	{
		p_elmObj->p_elmAnt = NULL;
		p_elmObj->p_elmSig = NULL;
	}
}

int SElmEsIgual ( SElemento * p_elmObj1, SElemento * p_elmObj2 )
{
	int	iRes;

	if ( ES_VALIDO ( p_elmObj1 ) && ES_VALIDO ( p_elmObj2 ) )
	{
		iRes = SBlqEsIgual ( SElmDatos ( p_elmObj1 ), SElmDatos ( p_elmObj2 ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SElmEsIgualBlq ( SElemento * p_elmObj, SBloque * p_blqObj )
{
	int	iRes;

	if ( ES_VALIDO ( p_elmObj ) && ES_VALIDO ( p_blqObj ) )
	{
		iRes = SBlqEsIgual ( SElmDatos ( p_elmObj ), p_blqObj );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SElmEsIgualExt ( SElemento * p_elmObj, byte * p_byObj )
{
	int	iRes;

	if ( ES_VALIDO ( p_elmObj ) && ES_VALIDO ( p_byObj ) )
	{
		iRes = SBlqEsIgualExt ( SElmDatos ( p_elmObj ), p_byObj );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int	SElmLiberacionMemoriaActivada ( SElemento * p_elmObj )
{
	int iRes;

	if ( ES_VALIDO ( p_elmObj ) )
	{
		iRes = p_elmObj->iLiberar;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

// NOTA:Retorna un elemento duplicado pero desencadenado:
SElemento * SElmDuplicar ( SElemento * p_elmObj )
{
	SBloque *	p_blqDatos;
	SBloque *	p_blqDatosDup;
	SElemento * p_elmDup;

	if ( SElmEsValido ( p_elmObj ) == 1 )
	{
		p_blqDatos = p_elmObj->p_blqDatos;
		if ( ES_VALIDO ( p_blqDatos ) )
		{
			p_blqDatosDup = SBlqDuplicar ( p_blqDatos );
			if ( ES_VALIDO ( p_blqDatosDup ) )
			{
				p_elmDup = SElmEncapsular ( p_blqDatosDup );
				if ( ES_NULO ( p_elmDup ) )
				{
					SBlqDestruir ( &p_blqDatosDup );
				}
			}
			else
			{
				p_elmDup = NULL;
			}
		}
		else
		{
			p_elmDup = NULL;
		}
	}
	else
	{
		p_elmDup = NULL;
	}
	return ( p_elmDup );
}

unsigned int SElmHash ( SElemento * p_elmObj )
{
	unsigned int uiRes = 0;

	if ( ES_VALIDO ( p_elmObj ) )
	{
		uiRes = SBlqHash ( p_elmObj->p_blqDatos );
	}
	return ( uiRes );
}


