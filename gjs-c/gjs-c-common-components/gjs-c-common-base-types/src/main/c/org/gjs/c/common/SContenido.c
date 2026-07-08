#include "SContenido.h"


#include "TiposBasicosConfig.h"




SContenido * SConCrear ( int iTam )
{
	SContenido * p_conObj;
	
	if ( iTam > 0 )
	{
		p_conObj = (SContenido *) MemReservar ( sizeof ( SContenido ) );
		if ( ES_VALIDO ( p_conObj ) )
		{
			p_conObj->p_blqDatos = SBlqCrear ( iTam );
			if ( ES_VALIDO ( p_conObj->p_blqDatos ) )
			{
				p_conObj->iLiberar = 1;
			}
			else
			{
				p_conObj->iLiberar = 0;
			}
		}
	}
	else
	{
		p_conObj = NULL;
	}
	return ( p_conObj );
}

SContenido * SConCrearEntero ()
{
	return ( SConCrear ( sizeof ( int ) ) );
}

SContenido * SConCrearEnteroLargo ()
{
	return ( SConCrear ( sizeof ( long ) ) );
}

SContenido * SConCrearReal ()
{
	return ( SConCrear ( sizeof ( float ) ) );
}

SContenido * SConCrearRealDoble ()
{
	return ( SConCrear ( sizeof ( double ) ) );
}

SContenido * SConCrearCadena ()
{
	return ( SConCrear ( sizeof ( char * ) ) );
}

SContenido * SConEncapsular ( SBloque * p_blqDatos )
{
	SContenido * p_conObj;
	
	if ( ES_VALIDO ( p_blqDatos ) )
	{
		p_conObj= (SContenido *) MemReservar ( sizeof ( SContenido ) );
		if ( ES_VALIDO ( p_conObj ) )
		{
			p_conObj->p_blqDatos = p_blqDatos;
			p_conObj->iLiberar = SBlqLiberacionMemoriaActivada ( p_blqDatos );
		}
	}
	else
	{
		p_conObj = NULL;
	}
	return ( p_conObj );
}

SContenido * SConEncapsularDir ( byte * p_byDirDatos, int iTamDatos, int iLiberar )
{
	SContenido * p_conObj;
	
	if ( ES_VALIDO ( p_byDirDatos ) && ( iTamDatos > 0 ) && BOOL_VALIDO ( iLiberar ) )
	{
		p_conObj= (SContenido *) MemReservar ( sizeof ( SContenido ) );
		if ( ES_VALIDO ( p_conObj ) )
		{
			p_conObj->p_blqDatos = SBlqAsignar ( p_byDirDatos, iTamDatos, iLiberar );
			if ( ES_VALIDO ( p_conObj->p_blqDatos ) )
			{
				p_conObj->iLiberar = SBlqLiberacionMemoriaActivada ( p_conObj->p_blqDatos );
			}
			else
			{
				p_conObj->iLiberar = 0;
			}
		}
	}
	else
	{
		p_conObj = NULL;
	}
	return ( p_conObj );
}

void SConDestruir ( SContenido ** p_p_conObj )
{
	SContenido * p_conObj;
	
	if ( ES_VALIDO ( p_p_conObj ) )
	{
		p_conObj = *p_p_conObj;

		if ( ES_VALIDO ( p_conObj ) )
		{
			if ( p_conObj->iLiberar == 1 )
			{
				SBlqDestruir ( &(p_conObj->p_blqDatos) );
			}
			MemLiberar ( (void **) p_p_conObj );
		}
	}
}

int SConEsValido ( SContenido * p_conObj )
{
	int iRes;

	if ( ES_VALIDO ( p_conObj ) )
	{
		if ( ES_VALIDO ( p_conObj->p_blqDatos ) )
		{
			if ( SBlqEsValido ( p_conObj->p_blqDatos ) == 1 )
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

SBloque * SConDatos ( SContenido * p_conObj )
{
	SBloque * p_blqRes;

	if ( ES_VALIDO ( p_conObj ) )
	{
		p_blqRes = p_conObj->p_blqDatos;
	}
	else
	{
		p_blqRes = NULL;
	}
	return ( p_blqRes );
}

int SConEntero ( SContenido * p_conObj )
{
	int	iRes;

	if ( ES_VALIDO ( p_conObj ) )
	{
		iRes = SBlqEntero ( p_conObj->p_blqDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

long SConEnteroLargo ( SContenido * p_conObj )
{
	long lRes;

	if ( ES_VALIDO ( p_conObj ) )
	{
		lRes = SBlqEnteroLargo ( p_conObj->p_blqDatos );
	}
	else
	{
		lRes = 0;
	}
	return ( lRes );
}

float SConReal ( SContenido * p_conObj )
{
	float fRes;

	if ( ES_VALIDO ( p_conObj ) )
	{
		fRes = SBlqReal ( p_conObj->p_blqDatos );
	}
	else
	{
		fRes = 0;
	}
	return ( fRes );
}

double SConRealDoble ( SContenido * p_conObj )
{
	double dRes;

	if ( ES_VALIDO ( p_conObj ) )
	{
		dRes = SBlqRealDoble ( p_conObj->p_blqDatos );
	}
	else
	{
		dRes = 0;
	}
	return ( dRes );
}

char * SConCadena ( SContenido * p_conObj )
{
	char * p_cRes;

	if ( ES_VALIDO ( p_conObj ) )
	{
		p_cRes = SBlqCadena ( p_conObj->p_blqDatos );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}
int SConTieneDatos ( SContenido * p_conObj )
{
	int iRes;

	if ( SConEsValido ( p_conObj ) )
	{
		if ( SBlqTam ( p_conObj->p_blqDatos ) > 0 )
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

int SConModificar ( SContenido * p_conObj, SBloque * p_blqDatos )
{
	int iRes;

	if ( ES_VALIDO ( p_conObj ) && ES_VALIDO ( p_blqDatos ) )
	{
		if ( p_conObj->iLiberar == 1 )
		{
			SBlqDestruir ( &(p_conObj->p_blqDatos) );
		}

		p_conObj->p_blqDatos = p_blqDatos;
		p_conObj->iLiberar = SBlqLiberacionMemoriaActivada ( p_blqDatos );
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SConModificarDir ( SContenido * p_conObj, byte * p_byDirDatos, int iTamDatos, int iLiberar )
{
	int iRes;

	if ( ES_VALIDO ( p_conObj ) && ES_VALIDO ( p_byDirDatos ) && ( iTamDatos > 0 ) && 
		 BOOL_VALIDO ( iLiberar ) )
	{
		if ( p_conObj->iLiberar == 1 )
		{
			SBlqDestruir ( &(p_conObj->p_blqDatos) );
		}

		p_conObj->p_blqDatos = SBlqAsignar ( p_byDirDatos, iTamDatos, iLiberar );
		if ( ES_VALIDO ( p_conObj->p_blqDatos ) )
		{
			iRes = 1;
			p_conObj->iLiberar = SBlqLiberacionMemoriaActivada ( p_conObj->p_blqDatos );
		}
		else
		{
			iRes = 0;
			p_conObj->iLiberar = 0;
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SConEscribirByte ( SContenido * p_conObj, int iPos, byte byValor )
{
	int iRes;

	if ( ES_VALIDO ( p_conObj ) )
	{
		iRes = SBlqEscribirByte ( p_conObj->p_blqDatos, iPos, byValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SConEscribirEntero ( SContenido * p_conObj, int iValor )
{
	int iRes;

	if ( ES_VALIDO ( p_conObj ) )
	{
		iRes = SBlqEscribirEntero ( p_conObj->p_blqDatos, iValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SConEscribirEnteroLargo ( SContenido * p_conObj, long lValor )
{
	int iRes;

	if ( ES_VALIDO ( p_conObj ) )
	{
		iRes = SBlqEscribirEnteroLargo ( p_conObj->p_blqDatos, lValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SConEscribirReal ( SContenido * p_conObj, float fValor )
{
	int iRes;

	if ( ES_VALIDO ( p_conObj ) )
	{
		iRes = SBlqEscribirReal ( p_conObj->p_blqDatos, fValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SConEscribirRealDoble ( SContenido * p_conObj, double dValor )
{
	int iRes;

	if ( ES_VALIDO ( p_conObj ) )
	{
		iRes = SBlqEscribirRealDoble ( p_conObj->p_blqDatos, dValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SConEscribirCadena ( SContenido * p_conObj, const char * p_cValor )
{
	int iRes;

	if ( ES_VALIDO ( p_conObj ) )
	{
		iRes = SBlqEscribirCadena ( p_conObj->p_blqDatos, p_cValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int	SConLiberacionMemoriaActivada ( SContenido * p_conObj )
{
	int iRes;

	if ( ES_VALIDO ( p_conObj ) )
	{
		iRes = p_conObj->iLiberar;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

SContenido * SConDuplicar ( SContenido * p_conObj )
{
	SBloque *	p_blqDatos;
	SContenido * p_conDup;

	if ( SConEsValido ( p_conObj ) == 1 )
	{
		p_blqDatos = p_conObj->p_blqDatos;
		if ( ES_VALIDO ( p_blqDatos ) )
		{
			p_conDup = SConCrear ( SBlqTam ( p_blqDatos ) );
			if ( ES_VALIDO ( p_conDup ) )
			{
				SBlqCopiar ( p_conDup->p_blqDatos, p_blqDatos );
				p_conDup->iLiberar = 1;
			}
		}
		else
		{
			p_conDup = NULL;
		}
	}
	else
	{
		p_conDup = NULL;
	}
	return ( p_conDup );
}


