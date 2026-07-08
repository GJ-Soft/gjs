#include "SHiloAriadna.h"

#include "TiposDatosConfig.h"



SHiloAriadna * SHilAriCrear ()
{
	SHiloAriadna * p_pilObj;
	
	p_pilObj = (SHiloAriadna *) MemReservar ( sizeof ( SHiloAriadna ) );
	if ( ES_VALIDO ( p_pilObj ) )
	{
		p_pilObj->p_pilTextos = SPilLitCrear ();
	}
	return ( p_pilObj );
}

void SHilAriDestruir ( SHiloAriadna ** p_p_pilObj )
{
	SHiloAriadna * p_pilObj;
	
	if ( ES_VALIDO ( p_p_pilObj ) )
	{
		p_pilObj = *p_p_pilObj;

		if ( ES_VALIDO ( p_pilObj ) )
		{
			SPilLitDestruir ( &(p_pilObj->p_pilTextos) );
			MemLiberar ( (void **) p_p_pilObj );
		}
	}
}

int SHilAriEsValido ( SHiloAriadna * p_pilObj )
{
	int iRes;

	if ( ES_VALIDO ( p_pilObj ) )
	{
		iRes = SPilLitEsValida ( p_pilObj->p_pilTextos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SHilAriEstaVacio ( SHiloAriadna * p_pilObj )
{
	int iRes;

	if ( ES_VALIDO ( p_pilObj ) )
	{
		iRes = SPilLitEstaVacia ( p_pilObj->p_pilTextos );
	}
	else
	{
		iRes = 1;
	}
	return ( iRes );
}

int SHilAriNumElementos ( SHiloAriadna * p_pilObj )
{
	int iRes;

	if ( ES_VALIDO ( p_pilObj ) )
	{
		iRes = SPilLitNumElementos ( p_pilObj->p_pilTextos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SHilAriDesapilar ( SHiloAriadna * p_pilObj )
{
	char *	p_cTexto;
	int		iRes;

	if ( ES_VALIDO ( p_pilObj ) )
	{
		p_cTexto = SPilLitDesapilar ( p_pilObj->p_pilTextos );
		if ( ES_VALIDO ( p_cTexto ) )
		{
			MemLiberar ( (void **) &p_cTexto );
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

int SHilAriApilar ( SHiloAriadna * p_pilObj, char * p_cTexto )
{
	int	iRes;

	if ( ES_VALIDO ( p_pilObj ) && ES_VALIDO ( p_cTexto ) )
	{
		iRes = SPilLitApilar ( p_pilObj->p_pilTextos, p_cTexto );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int SHilAriVaciar ( SHiloAriadna * p_pilObj )
{
	int iRes;

	if ( ES_VALIDO ( p_pilObj ) )
	{
		iRes = SPilLitVaciar ( p_pilObj->p_pilTextos );
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int SHilAriImprimir ( SHiloAriadna * p_pilObj )
{
	int			iRes;
	SListaPtr * p_lispTextos;
	int			iElem;
	char *		p_cTexto;

	if ( ES_VALIDO ( p_pilObj ) )
	{
		iRes = 1;
		p_lispTextos = p_pilObj->p_pilTextos->p_pilDatos->p_lisObjetos;
		iElem = SLispNumElementos ( p_lispTextos ) - 1; 
		while ( iElem >= 0 )
		{
			p_cTexto = (char *) SLispElemento ( p_lispTextos, iElem );
			printf ( ">%s ", p_cTexto ); 
			iElem = iElem - 1;
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}
