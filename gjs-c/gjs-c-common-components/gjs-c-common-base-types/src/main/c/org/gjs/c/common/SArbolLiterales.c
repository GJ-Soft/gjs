#include "SArbolLiterales.h"

#include "TiposBasicosConfig.h"



void _SArbLitImprimirSubarbol  ( SNodoPtr * p_nodpObj, int iNivel );



SArbolLiterales * SArbLitCrear () 
{
	SArbolLiterales * p_arbObj;
	
	p_arbObj = (SArbolLiterales *) MemReservar ( sizeof ( SArbolLiterales ) );
	if ( ES_VALIDO ( p_arbObj ) )
	{
		p_arbObj->p_arbContenido = SArbPtrCrear ();
	}
	return ( p_arbObj );
}

void SArbLitDestruir ( SArbolLiterales ** p_p_arbObj )
{
	SArbolLiterales * p_arbObj;
	
	if ( ES_VALIDO ( p_p_arbObj ) )
	{
		p_arbObj = *p_p_arbObj;
		if ( ES_VALIDO ( p_arbObj ) )
		{
			/* El arbol de contenido lo reserva SArbLitCrear, asi que hay que
			   destruirlo, no solo vaciarlo: vaciandolo se fugaba el SArbolPtr en
			   cada crear/destruir. Es lo que hace SLisLitDestruir con su lista */
			SArbPtrDestruir ( &(p_arbObj->p_arbContenido) );
			MemLiberar ( (void **) p_p_arbObj );
		}
	}
}

char * SArbLitRaiz ( SArbolLiterales * p_arbObj )
{
	char * p_cRes;
	
	if ( ES_VALIDO ( p_arbObj ) )
	{
		p_cRes = (char *) SNodPtrDatos ( SArbPtrRaiz ( p_arbObj->p_arbContenido ) );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

int SArbLitEstablecerRaiz ( SArbolLiterales * p_arbObj, const char * p_cValor )
{
	int 		iRes;
	SNodoPtr * 	p_nodpObj;
	char *		p_cDatos;

	if ( ES_VALIDO ( p_arbObj ) )
	{
		p_cDatos = CadDuplicar ( p_cValor );
		p_nodpObj = SNodPtrCrear ( (byte *) p_cDatos, 1 );
		if ( SNodPtrEsValido ( p_nodpObj ) == 1 )
		{
			iRes = SArbPtrEstablecerRaiz ( p_arbObj->p_arbContenido, p_nodpObj );
		}
		else
		{
			SNodPtrDestruir ( &p_nodpObj, 0 );
			MemLiberar ( (void **) &p_cDatos );
			iRes = 0;
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SArbLitEstaVacio ( SArbolLiterales * p_arbObj )
{
	int iRes;

	if ( ES_VALIDO ( p_arbObj ) )
	{
		iRes = SArbPtrEstaVacio ( p_arbObj->p_arbContenido );
	}
	else
	{
		iRes = 1;
	}
	return ( iRes );
}

int SArbLitNiveles ( SArbolLiterales * p_arbObj )
{
	int iNiveles;

	if ( ES_VALIDO ( p_arbObj ) )
	{
		iNiveles = SArbPtrNiveles ( p_arbObj->p_arbContenido );
	}
	else
	{
		iNiveles = 0;
	}
	return ( iNiveles );
}

int SArbLitNumNodos ( SArbolLiterales * p_arbObj )
{
	int iNodos;

	if ( ES_VALIDO ( p_arbObj ) )
	{
		iNodos = SArbPtrNumNodos ( p_arbObj->p_arbContenido );
	}
	else
	{
		iNodos = 0;
	}
	return ( iNodos );
}

int SArbLitVaciar ( SArbolLiterales * p_arbObj )
{
	int		iRes;

	if ( ES_VALIDO ( p_arbObj ) )
	{
		iRes = SArbPtrVaciar ( p_arbObj->p_arbContenido );
	}
	else
	{
		iRes = 1;
	}
	return ( iRes );
}

char * SArbLitActual ( SArbolLiterales * p_arbObj )
{
	char * p_cRes;
	
	if ( ES_VALIDO ( p_arbObj ) )
	{
		p_cRes = (char *) SNodPtrDatos ( SArbPtrActual ( p_arbObj->p_arbContenido ) );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

int SArbLitMoverARaiz ( SArbolLiterales * p_arbObj )
{
	int iRes;
	
	if ( ES_VALIDO ( p_arbObj ) )
	{
		iRes = SArbPtrMoverARaiz ( p_arbObj->p_arbContenido );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SArbLitMoverAPadre ( SArbolLiterales * p_arbObj )
{
	int iRes;
	
	if ( ES_VALIDO ( p_arbObj ) )
	{
		iRes = SArbPtrMoverAPadre ( p_arbObj->p_arbContenido );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SArbLitMoverAHijo ( SArbolLiterales * p_arbObj, int iHijo )
{
	int iRes;
	
	if ( ES_VALIDO ( p_arbObj ) )
	{
		iRes = SArbPtrMoverAHijo ( p_arbObj->p_arbContenido, iHijo );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SArbLitMoverAPrimHijo ( SArbolLiterales * p_arbObj )
{
	int iRes;
	
	if ( ES_VALIDO ( p_arbObj ) )
	{
		iRes = SArbPtrMoverAPrimHijo ( p_arbObj->p_arbContenido );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SArbLitMoverAUltHijo ( SArbolLiterales * p_arbObj )
{
	int iRes;
	
	if ( ES_VALIDO ( p_arbObj ) )
	{
		iRes = SArbPtrMoverAUltHijo ( p_arbObj->p_arbContenido );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SArbLitMoverAPrimHermano ( SArbolLiterales * p_arbObj )
{
	int iRes;
	
	if ( ES_VALIDO ( p_arbObj ) )
	{
		iRes = SArbPtrMoverAPrimHermano ( p_arbObj->p_arbContenido );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SArbLitMoverASigHermano ( SArbolLiterales * p_arbObj )
{
	int iRes;
	
	if ( ES_VALIDO ( p_arbObj ) )
	{
		iRes = SArbPtrMoverASigHermano ( p_arbObj->p_arbContenido );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SArbLitMoverAAntHermano ( SArbolLiterales * p_arbObj )
{
	int iRes;
	
	if ( ES_VALIDO ( p_arbObj ) )
	{
		iRes = SArbPtrMoverAAntHermano ( p_arbObj->p_arbContenido );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SArbLitMoverAUltHermano ( SArbolLiterales * p_arbObj )
{
	int iRes;
	
	if ( ES_VALIDO ( p_arbObj ) )
	{
		iRes = SArbPtrMoverAUltHermano ( p_arbObj->p_arbContenido );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SArbLitMoverAPrimPreorden ( SArbolLiterales * p_arbObj )
{
	int iRes;
	
	if ( ES_VALIDO ( p_arbObj ) )
	{
		iRes = SArbPtrMoverAPrimPreorden ( p_arbObj->p_arbContenido );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SArbLitMoverASigPreorden ( SArbolLiterales * p_arbObj )
{
	int iRes;
	
	if ( ES_VALIDO ( p_arbObj ) )
	{
		iRes = SArbPtrMoverASigPreorden ( p_arbObj->p_arbContenido );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SArbLitMoverAPrimPostorden ( SArbolLiterales * p_arbObj )
{
	int iRes;
	
	if ( ES_VALIDO ( p_arbObj ) )
	{
		iRes = SArbPtrMoverAPrimPostorden ( p_arbObj->p_arbContenido );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SArbLitMoverASigPostorden ( SArbolLiterales * p_arbObj )
{
	int iRes;
	
	if ( ES_VALIDO ( p_arbObj ) )
	{
		iRes = SArbPtrMoverASigPostorden ( p_arbObj->p_arbContenido );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int	SArbLitEstaPosicionado ( SArbolLiterales * p_arbObj )
{
	int iRes;

	if ( ES_VALIDO ( p_arbObj ) )
	{
		iRes = SArbPtrEstaPosicionado ( p_arbObj->p_arbContenido );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SArbLitEnraizar ( SArbolLiterales * p_arbObj, const char * p_cValor )
{
	int 		iRes;
	SNodoPtr * 	p_nodpObj;
	char *		p_cDatos;

	if ( ES_VALIDO ( p_arbObj ) && ES_VALIDO ( p_cValor ) )
	{
		p_cDatos = CadDuplicar ( p_cValor );
		p_nodpObj = SNodPtrCrear ( (byte *) p_cDatos, 1 );
		if ( SNodPtrEsValido ( p_nodpObj ) == 1 )
		{
			iRes = SArbPtrEnraizar ( p_arbObj->p_arbContenido, p_nodpObj );
		}
		else
		{
			SNodPtrDestruir ( &p_nodpObj, 0 );
			MemLiberar ( (void **) &p_cDatos );
			iRes = 0;
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SArbLitActualEsValido ( SArbolLiterales * p_arbObj )
{
	int iRes;

	if ( ES_VALIDO ( p_arbObj ) )
	{
		iRes = SNodPtrEsValido ( SArbPtrActual ( p_arbObj->p_arbContenido ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SArbLitActualTieneDatos ( SArbolLiterales * p_arbObj )
{
	int iRes;

	if ( ES_VALIDO ( p_arbObj ) )
	{
		iRes = SNodPtrEsValido ( SArbPtrActual ( p_arbObj->p_arbContenido ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SArbLitActualModificar ( SArbolLiterales * p_arbObj, const char * p_cValor )
{
	int		iRes;
	char *	p_cDatos;

	if ( ES_VALIDO ( p_arbObj ) && ES_VALIDO ( p_cValor ) )
	{
		p_cDatos = CadDuplicar ( p_cValor );
		iRes = SNodPtrModificar ( SArbPtrActual ( p_arbObj->p_arbContenido ), (byte *) p_cDatos, 1 );
		if ( iRes != 1 )
		{
			MemLiberar ( (void **) &p_cDatos );
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}


int SArbLitActualNumHijos ( SArbolLiterales * p_arbObj )
{
	int iRes;

	if ( ES_VALIDO ( p_arbObj ) )
	{
		iRes = SNodPtrNumHijos ( SArbPtrActual ( p_arbObj->p_arbContenido ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

char * SArbLitActualPadre ( SArbolLiterales * p_arbObj )
{
	char * p_cRes;

	if ( ES_VALIDO ( p_arbObj ) )
	{
		p_cRes = (char *) SNodPtrDatos ( SNodPtrPadre ( SArbPtrActual ( p_arbObj->p_arbContenido ) ) );
	}
	else
	{
		p_cRes = 0;
	}
	return ( p_cRes );
}

char * SArbLitActualHijo ( SArbolLiterales * p_arbObj, int iHijo )
{
	char * p_cRes;

	if ( ES_VALIDO ( p_arbObj ) )
	{
		p_cRes = (char *) SNodPtrDatos ( SNodPtrHijo ( SArbPtrActual ( p_arbObj->p_arbContenido ), iHijo ) );
	}
	else
	{
		p_cRes = 0;
	}
	return ( p_cRes );
}


int SArbLitActualTienePadre ( SArbolLiterales * p_arbObj )
{
	int iRes;

	if ( ES_VALIDO ( p_arbObj ) )
	{
		iRes = SNodPtrTienePadre ( SArbPtrActual ( p_arbObj->p_arbContenido ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SArbLitActualTieneHijos ( SArbolLiterales * p_arbObj )
{
	int iRes;

	if ( ES_VALIDO ( p_arbObj ) )
	{
		iRes = SNodPtrTieneHijos ( SArbPtrActual ( p_arbObj->p_arbContenido ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SArbLitActualTieneHermanos ( SArbolLiterales * p_arbObj )
{
	int iRes;

	if ( ES_VALIDO ( p_arbObj ) )
	{
		iRes = SNodPtrTieneHermanos ( SArbPtrActual ( p_arbObj->p_arbContenido ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SArbLitActualTieneHermanosIzq ( SArbolLiterales * p_arbObj )
{
	int iRes;

	if ( ES_VALIDO ( p_arbObj ) )
	{
		iRes = SNodPtrTieneHermanosIzq ( SArbPtrActual ( p_arbObj->p_arbContenido ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SArbLitActualTieneHermanosDer ( SArbolLiterales * p_arbObj )
{
	int iRes;

	if ( ES_VALIDO ( p_arbObj ) )
	{
		iRes = SNodPtrTieneHermanosDer ( SArbPtrActual ( p_arbObj->p_arbContenido ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SArbLitActualNodosInferiores ( SArbolLiterales * p_arbObj )
{
	int iRes;

	if ( ES_VALIDO ( p_arbObj ) )
	{
		iRes = SNodPtrNodosInferiores ( SArbPtrActual ( p_arbObj->p_arbContenido ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SArbLitActualProfundidad ( SArbolLiterales * p_arbObj )
{
	int iRes;

	if ( ES_VALIDO ( p_arbObj ) )
	{
		iRes = SNodPtrProfundidad ( SArbPtrActual ( p_arbObj->p_arbContenido ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SArbLitActualNivelesInferiores ( SArbolLiterales * p_arbObj )
{
	int iRes;

	if ( ES_VALIDO ( p_arbObj ) )
	{
		iRes = SNodPtrNivelesInferiores ( SArbPtrActual ( p_arbObj->p_arbContenido ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SArbLitActualInsertarHijo ( SArbolLiterales * p_arbObj, const char * p_cValor )
{
	int 		iRes;
	SNodoPtr * 	p_nodHijo;
	char *		p_cDatos;

	if ( ES_VALIDO ( p_arbObj ) && ES_VALIDO ( p_cValor ) )
	{
		p_cDatos = CadDuplicar ( p_cValor );
		p_nodHijo = SNodPtrCrear ( (byte *) p_cDatos, 1 );
		if ( SNodPtrEsValido ( p_nodHijo ) == 1 )
		{
			iRes = SNodPtrInsertarHijo ( SArbPtrActual ( p_arbObj->p_arbContenido ), p_nodHijo );
		}
		else
		{
			SNodPtrDestruir ( &p_nodHijo, 0 );
			MemLiberar ( (void **) &p_cDatos );
			iRes = 0;
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SArbLitActualEliminarHijo ( SArbolLiterales * p_arbObj, int iHijo )
{
	int 		iRes;

	if ( ES_VALIDO ( p_arbObj ) )
	{
		iRes = SNodPtrEliminarHijo ( SArbPtrActual ( p_arbObj->p_arbContenido ),  iHijo,  1 );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SArbLitActualEstablecerHijo ( SArbolLiterales * p_arbObj, int iHijo, const char * p_cValor )
{
	int 		iRes;
	SNodoPtr * 	p_nodHijo;

	if ( ES_VALIDO ( p_arbObj ) && ES_VALIDO ( p_cValor ) )
	{
		p_nodHijo = SNodPtrHijo ( SArbPtrActual ( p_arbObj->p_arbContenido ), iHijo );
		if ( ES_VALIDO ( p_nodHijo ) )
		{
			iRes = SNodPtrModificar ( SArbPtrActual ( p_arbObj->p_arbContenido ), 
				(byte *) CadDuplicar ( p_cValor ), 1 );
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

void SArbLitActualLimpiarHijos ( SArbolLiterales * p_arbObj )
{
	if ( ES_VALIDO ( p_arbObj ) )
	{
		SNodPtrLimpiarHijos ( SArbPtrActual ( p_arbObj->p_arbContenido ), 1 );
	}
}

int	SArbLitActualEsHijo ( SArbolLiterales * p_arbObj )
{
	int iRes;

	if ( ES_VALIDO ( p_arbObj ) )
	{
		iRes = SNodPtrEsHijo ( SArbPtrActual ( p_arbObj->p_arbContenido ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SArbLitVerificar ( SArbolLiterales * p_arbObj, int iCorregir )
{
	int iRes;

	if ( ES_VALIDO ( p_arbObj ) )
	{
		iRes = SArbPtrVerificar ( p_arbObj->p_arbContenido, iCorregir );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}


void SArbLitImprimir  ( SArbolLiterales * p_arbObj )
{
	SNodoPtr * 	p_nodpObj;
	
	if ( ES_VALIDO ( p_arbObj ) ) 
	{
		printf ( "Contenido del arbol: [\n" );
		p_nodpObj = SArbPtrRaiz ( p_arbObj->p_arbContenido );
		_SArbLitImprimirSubarbol  ( p_nodpObj, 0 );
		printf ( "]\n" );
	}
	else
	{
		printf ( "%s\n", VALOR_NULO );
	}
}

void _SArbLitImprimirSubarbol  ( SNodoPtr * p_nodpObj, int iNivel )
{
	int 		iHijo;
	SNodoPtr * 	p_nodpHijo;
	
	if ( ES_VALIDO ( p_nodpObj ) ) 
	{
		for ( int i = 0; i < iNivel; i = i + 1 )
		{
			printf ( "\t" );	
		}
		printf ( "[%s]\n", (char *) SNodPtrDatos ( p_nodpObj ) );
		for ( iHijo = 0; iHijo < SNodPtrNumHijos ( p_nodpObj ); iHijo = iHijo + 1 )
		{
     		p_nodpHijo = SNodPtrHijo ( p_nodpObj, iHijo );
     		if ( ES_VALIDO ( p_nodpHijo  ) )
     		{
				_SArbLitImprimirSubarbol  ( p_nodpHijo, iNivel + 1 );
			}
			else
			{
				printf ( "%s\n", VALOR_NULO );
			}
		}
	}
	else
	{
		printf ( "%s\n", VALOR_NULO );
	}
}


