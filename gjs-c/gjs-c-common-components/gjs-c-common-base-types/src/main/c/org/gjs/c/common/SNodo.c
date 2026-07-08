
#include <SNodo.h>


#include "TiposBasicosConfig.h"





static void SNodInicializar ( SNodo * p_nodObj, int iTamDatos, SBloque * p_blqDatos, byte * p_byDirDatos, int iLiberar );




SNodo * SNodCrear ( int iTamDatos )
{
	SNodo * p_nodObj;

	if ( iTamDatos > 0 )
	{
		p_nodObj = (SNodo *) MemReservar ( sizeof ( SNodo ) );
		if ( ES_VALIDO ( p_nodObj ) )
		{
			 SNodInicializar ( p_nodObj, iTamDatos, NULL, NULL, 0 );
		}
	}
	else
	{
		p_nodObj = NULL;
	}
	return ( p_nodObj );
}

SNodo * SNodCrearEntero ( int iValor )
{
	SNodo * p_nodObj;

	p_nodObj = SNodCrear ( sizeof ( int ) );
	SNodEstablecerEntero ( p_nodObj, iValor );
	return ( p_nodObj );
}

SNodo * SNodCrearEnteroLargo ( long lValor )
{
	SNodo * p_nodObj;

	p_nodObj = SNodCrear ( sizeof ( long ) );
	SNodEstablecerEnteroLargo ( p_nodObj, lValor );
	return ( p_nodObj );
}

SNodo * SNodCrearReal ( float fValor )
{
	SNodo * p_nodObj;

	p_nodObj = SNodCrear ( sizeof ( float ) );
	SNodEstablecerReal ( p_nodObj, fValor );
	return ( p_nodObj );
}

SNodo * SNodCrearRealDoble ( double dValor )
{
	SNodo * p_nodObj;

	p_nodObj = SNodCrear ( sizeof ( double ) );
	SNodEstablecerRealDoble ( p_nodObj, dValor );
	return ( p_nodObj );
}

SNodo * SNodCrearCadena ( const char * p_cValor )
{
	SNodo * p_nodObj;

	if ( ES_VALIDO ( p_cValor ) )
	{
		p_nodObj = SNodCrear ( CadLongitud ( p_cValor ) );
		SNodEstablecerCadena ( p_nodObj, p_cValor );
	}
	else
	{
		p_nodObj = NULL;
	}
	return ( p_nodObj );
}

SNodo * SNodEncapsular ( SBloque * p_blqDatos )
{
	SNodo * p_nodObj;

	if ( ES_VALIDO ( p_blqDatos ) )
	{
		p_nodObj= (SNodo *) MemReservar ( sizeof ( SNodo ) );
		if ( ES_VALIDO ( p_nodObj ) )
		{
		    SNodInicializar ( p_nodObj, SBlqTam ( p_blqDatos ), p_blqDatos, NULL, 0 );
		}
	}
	else
	{
		p_nodObj = NULL;
	}
	return ( p_nodObj );
}

SNodo * SNodEncapsularDir ( byte * p_byDirDatos, int iTamDatos, int iLiberar )
{
	SNodo * p_nodObj;

	if ( ES_VALIDO ( p_byDirDatos ) && ( iTamDatos > 0 ) && BOOL_VALIDO ( iLiberar ) )
	{
		p_nodObj= (SNodo *) MemReservar ( sizeof ( SNodo ) );
		if ( ES_VALIDO ( p_nodObj ) )
		{
		    SNodInicializar ( p_nodObj, iTamDatos, NULL, p_byDirDatos, iLiberar );
		}
	}
	else
	{
		p_nodObj = NULL;
	}
	return ( p_nodObj );
}

void SNodDestruir ( SNodo ** p_p_nodObj, int iDestruirHijos )
{
    SNodo *  p_nodObj;

    if ( ES_VALIDO ( p_p_nodObj ) )
    {
        p_nodObj = *p_p_nodObj;
 		if ( ES_VALIDO ( p_nodObj ) )
		{
			SNodLimpiarHijos ( p_nodObj, iDestruirHijos );
			if ( p_nodObj->iLiberar == 1 )
			{
				SBlqDestruir ( &(p_nodObj->p_blqDatos) );
			}
			MemLiberar ( (void **) p_p_nodObj );
		}
    }
}

int SNodEsValido ( SNodo * p_nodObj )
{
	int iRes;

	if ( ES_VALIDO ( p_nodObj ) )
	{
		if ( ES_VALIDO ( p_nodObj->p_blqDatos ) )
		{
			if ( SBlqEsValido ( p_nodObj->p_blqDatos ) == 1 )
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

int SNodTieneDatos ( SNodo * p_nodObj )
{
	int iRes;

	if ( SNodEsValido ( p_nodObj ) )
	{
		if ( SBlqTam ( p_nodObj->p_blqDatos ) > 0 )
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

SBloque * SNodDatos ( SNodo * p_nodObj )
{
	SBloque * p_blqRes;

	if ( ES_VALIDO ( p_nodObj ) )
	{
		p_blqRes = p_nodObj->p_blqDatos;
	}
	else
	{
		p_blqRes = NULL;
	}
	return ( p_blqRes );
}

int SNodEntero ( SNodo * p_nodObj )
{
	int	iRes;

	if ( ES_VALIDO ( p_nodObj ) )
	{
		iRes = SBlqEntero ( p_nodObj->p_blqDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

long SNodEnteroLargo ( SNodo * p_nodObj )
{
	long lRes;

	if ( ES_VALIDO ( p_nodObj ) )
	{
		lRes = SBlqEnteroLargo ( p_nodObj->p_blqDatos );
	}
	else
	{
		lRes = 0;
	}
	return ( lRes );
}

float SNodReal ( SNodo * p_nodObj )
{
	float fRes;

	if ( ES_VALIDO ( p_nodObj ) )
	{
		fRes = SBlqReal ( p_nodObj->p_blqDatos );
	}
	else
	{
		fRes = 0;
	}
	return ( fRes );
}

double SNodRealDoble ( SNodo * p_nodObj )
{
	double dRes;

	if ( ES_VALIDO ( p_nodObj ) )
	{
		dRes = SBlqRealDoble ( p_nodObj->p_blqDatos );
	}
	else
	{
		dRes = 0;
	}
	return ( dRes );
}

char * SNodCadena ( SNodo * p_nodObj )
{
	char * p_cRes;

	if ( ES_VALIDO ( p_nodObj ) )
	{
		p_cRes = SBlqCadena ( p_nodObj->p_blqDatos );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

int SNodModificar ( SNodo * p_nodObj, SBloque * p_blqDatos )
{
	int iRes;

	if ( ES_VALIDO ( p_nodObj ) && ES_VALIDO ( p_blqDatos ) )
	{
		if ( p_nodObj->iLiberar == 1 )
		{
			SBlqDestruir ( &(p_nodObj->p_blqDatos) );
		}

		p_nodObj->p_blqDatos = p_blqDatos;
		p_nodObj->iLiberar = SBlqLiberacionMemoriaActivada ( p_blqDatos );
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SNodModificarDir ( SNodo * p_nodObj, byte * p_byDirDatos, int iTamDatos, int iLiberar )
{
	int iRes;

	if ( ES_VALIDO ( p_nodObj ) && ES_VALIDO ( p_byDirDatos ) && ( iTamDatos > 0 ) &&
		 BOOL_VALIDO ( iLiberar ) )
	{
		if ( p_nodObj->iLiberar == 1 )
		{
			SBlqDestruir ( &(p_nodObj->p_blqDatos) );
		}

		p_nodObj->p_blqDatos = SBlqAsignar ( p_byDirDatos, iTamDatos, iLiberar );
		if ( ES_VALIDO ( p_nodObj->p_blqDatos ) )
		{
			iRes = 1;
			p_nodObj->iLiberar = SBlqLiberacionMemoriaActivada ( p_nodObj->p_blqDatos );
		}
		else
		{
			iRes = 0;
			p_nodObj->iLiberar = 0;
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SNodEstablecerByte ( SNodo * p_nodObj, int iPos, byte byValor )
{
	int iRes;

	if ( ES_VALIDO ( p_nodObj ) )
	{
		iRes = SBlqEscribirByte ( p_nodObj->p_blqDatos, iPos, byValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SNodEstablecerEntero ( SNodo * p_nodObj, int iValor )
{
	int iRes;

	if ( ES_VALIDO ( p_nodObj ) )
	{
		iRes = SBlqEscribirEntero ( p_nodObj->p_blqDatos, iValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SNodEstablecerEnteroLargo ( SNodo * p_nodObj, long lValor )
{
	int iRes;

	if ( ES_VALIDO ( p_nodObj ) )
	{
		iRes = SBlqEscribirEnteroLargo ( p_nodObj->p_blqDatos, lValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SNodEstablecerReal ( SNodo * p_nodObj, float fValor )
{
	int iRes;

	if ( ES_VALIDO ( p_nodObj ) )
	{
		iRes = SBlqEscribirReal ( p_nodObj->p_blqDatos, fValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SNodEstablecerRealDoble ( SNodo * p_nodObj, double dValor )
{
	int iRes;

	if ( ES_VALIDO ( p_nodObj ) )
	{
		iRes = SBlqEscribirRealDoble ( p_nodObj->p_blqDatos, dValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SNodEstablecerCadena ( SNodo * p_nodObj, const char * p_cValor )
{
	int iRes;

	if ( ES_VALIDO ( p_nodObj ) )
	{
		iRes = SBlqEscribirCadena ( p_nodObj->p_blqDatos, p_cValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SNodNumHijos ( SNodo * p_nodObj )
{
    int iRes;

    if ( ES_VALIDO ( p_nodObj ) )
    {
        iRes = p_nodObj->iNumHijos;
    }
    else
    {
        iRes = 0;
    }
	return ( iRes );
}

SNodo * SNodPadre ( SNodo * p_nodObj )
{
    SNodo * p_nodRes;

    if ( ES_VALIDO ( p_nodObj ) )
    {
        p_nodRes = p_nodObj->p_nodPadre;
    }
    else
    {
        p_nodRes = NULL;
    }
	return ( p_nodRes );
}

SNodo * SNodHijo ( SNodo * p_nodObj, int iHijo )
{
	SNodo *	p_nodHijo;

    if ( ES_VALIDO ( p_nodObj ) )
    {
     	if ( ( iHijo >= 0 ) && ( iHijo < p_nodObj->iNumHijos ) )
     	{
			p_nodHijo = p_nodObj->p_p_nodHijos [ iHijo ];
     	}
     	else
     	{
     		p_nodHijo = NULL;
     	}
	}
	else
	{
		p_nodHijo = NULL;
	}
	return ( p_nodHijo );
}

int SNodTienePadre ( SNodo * p_nodObj )
{
	int iRes;

    if ( ES_VALIDO ( p_nodObj ) )
    {
     	if ( ES_VALIDO ( p_nodObj->p_nodPadre ) )
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

int SNodTieneHijos ( SNodo * p_nodObj )
{
	int iRes;

    if ( ES_VALIDO ( p_nodObj ) )
    {
     	if ( p_nodObj->iNumHijos > 0 )
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

int SNodTieneHermanos ( SNodo * p_nodObj )
{
	int iRes;

    if ( ES_VALIDO ( p_nodObj ) )
    {
     	if ( ES_VALIDO ( p_nodObj->p_nodPadre ) )
     	{
     		if ( SNodNumHijos ( p_nodObj->p_nodPadre ) > 1 )
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

int SNodTieneHermanosIzq ( SNodo * p_nodObj )
{
	int iRes;

    if ( ES_VALIDO ( p_nodObj ) )
    {
     	if ( ES_VALIDO ( p_nodObj->p_nodPadre ) )
     	{
     		if ( SNodOrdenDelHijo ( p_nodObj->p_nodPadre, p_nodObj ) > 0 )
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

int SNodTieneHermanosDer ( SNodo * p_nodObj )
{
	int iOrden;
	int iRes;

     if ( ES_VALIDO ( p_nodObj ) )
     {
     	if ( ES_VALIDO ( p_nodObj->p_nodPadre ) )
     	{
     		iOrden = SNodOrdenDelHijo ( p_nodObj->p_nodPadre, p_nodObj );
     		if ( ( iOrden >= 0 ) && ( iOrden < SNodNumHijos ( p_nodObj->p_nodPadre ) - 1 ) )
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

int SNodNodosInferiores ( SNodo * p_nodObj )
{
	SNodo *	p_nodHijo;
	int		iHijo;
	int		iNodos;

     if ( ES_VALIDO ( p_nodObj ) )
     {
     	iNodos = 0;
     	for ( iHijo = 0; iHijo < p_nodObj->iNumHijos; iHijo = iHijo + 1 )
     	{
     		p_nodHijo = SNodHijo ( p_nodObj, iHijo );
     		if ( ES_VALIDO ( p_nodHijo  ) )
     		{
     			iNodos = iNodos + 1 + SNodNodosInferiores ( p_nodHijo );
     		}
     	}
     }
     else
     {
          iNodos = 0;
     }
	return ( iNodos );
}

int SNodNivelesInferiores ( SNodo * p_nodObj )
{
	SNodo *	p_nodHijo;
	int		iHijo;
	int		iNiveles;
	int		iNivelesMax;

     if ( ES_VALIDO ( p_nodObj ) )
     {
     	iNivelesMax = 0;
     	for ( iHijo = 0; iHijo < p_nodObj->iNumHijos; iHijo = iHijo + 1 )
     	{
     		p_nodHijo = SNodHijo ( p_nodObj, iHijo );
     		if ( ES_VALIDO ( p_nodHijo ) )
     		{
     			iNiveles = 1 + SNodNivelesInferiores ( p_nodHijo );
     			if ( iNiveles > iNivelesMax )
     			{
     				iNivelesMax = iNiveles;
     			}
     		}
     	}
     }
     else
     {
          iNivelesMax = 0;
     }
	return ( iNivelesMax );
}

int SNodProfundidad ( SNodo * p_nodObj )
{
	int	iProfundidad;

     if ( ES_VALIDO ( p_nodObj ) )
     {
     	if ( ES_NULO ( p_nodObj->p_nodPadre ) )
     	{
     		iProfundidad = 0;
     	}
     	else
     	{
     		iProfundidad = SNodProfundidad ( p_nodObj->p_nodPadre ) + 1;
     	}
     }
     else
     {
          iProfundidad = 0;
     }
	return ( iProfundidad );
}

int SNodEmpadronar ( SNodo * p_nodObj, SNodo * p_nodPadre )
{
	int iRes;

     if ( ES_VALIDO ( p_nodObj ) )
     {
     	p_nodObj->p_nodPadre = p_nodPadre;
     	if ( ES_VALIDO ( p_nodObj->p_nodPadre ) )
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

int SNodInsertarHijo ( SNodo * p_nodObj, SNodo * p_nodHijo )
{
	int	iRes;

     if ( ES_VALIDO ( p_nodObj ) )
     {
     	if ( ( p_nodObj->iNumHijos < ARB_MAX_HIJOS_NODO ) && ES_VALIDO ( p_nodHijo ) )
     	{
            if ( MemRedimensionar ( (void **) &(p_nodObj->p_p_nodHijos), sizeof ( SNodo * ) * ( p_nodObj->iNumHijos + 1 ) ) == 1 )
            {
  			    p_nodObj->iNumHijos = p_nodObj->iNumHijos + 1;
				p_nodObj->p_p_nodHijos [ p_nodObj->iNumHijos - 1 ] = p_nodHijo;
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

void SNodDesempadronar ( SNodo * p_nodObj )
{
     if ( ES_VALIDO ( p_nodObj ) )
     {
          p_nodObj->p_nodPadre = NULL;
     }
}

int SNodEliminarHijo ( SNodo * p_nodObj, int iHijo, int iLiberarHijos )
{
	int	iHijoAux;
	int	iRes;

     if ( ES_VALIDO ( p_nodObj ) )
     {
     	if ( ( iHijo >= 0 ) && ( iHijo < p_nodObj->iNumHijos ) )
     	{
			if ( iLiberarHijos == 1 )
			{
				if ( ES_VALIDO ( p_nodObj->p_p_nodHijos [ iHijo ] ) )
				{
					SNodDestruir ( &(p_nodObj->p_p_nodHijos [ iHijo ]), 1 );
				}
			}

			for ( iHijoAux = iHijo + 1; iHijoAux < p_nodObj->iNumHijos; iHijoAux = iHijoAux + 1 )
			{
				p_nodObj->p_p_nodHijos [ iHijoAux - 1 ] = p_nodObj->p_p_nodHijos [ iHijoAux ];
			}
			p_nodObj->iNumHijos = p_nodObj->iNumHijos - 1;
			iRes = MemRedimensionar ( (void **)&(p_nodObj->p_p_nodHijos), sizeof ( SNodo * ) * ( p_nodObj->iNumHijos ) );
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

int SNodEstablecerHijo ( SNodo * p_nodObj, int iHijo, SNodo * p_nodHijo, int iLiberarHijos  )
{
	int		iRes;

     if ( ES_VALIDO ( p_nodObj ) )
     {
     	if ( ( iHijo >= 0 ) && ( iHijo < p_nodObj->iNumHijos ) && ES_VALIDO ( p_nodHijo ) )
     	{
			if ( iLiberarHijos == 1 )
			{
				if ( ES_VALIDO ( p_nodObj->p_p_nodHijos [ iHijo ] ) )
				{
					SNodDestruir ( &(p_nodObj->p_p_nodHijos [ iHijo ]), 1 );
				}
			}
			p_nodObj->p_p_nodHijos [ iHijo ] = p_nodHijo;
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

void SNodLimpiarHijos ( SNodo * p_nodObj, int iLiberarHijos )
{
	int iHijo;

    if ( ES_VALIDO ( p_nodObj ) )
    {
		for ( iHijo = 0; iHijo < p_nodObj->iNumHijos; iHijo = iHijo + 1 )
		{
			if ( iLiberarHijos == 1 )
			{
				if ( ES_VALIDO ( p_nodObj->p_p_nodHijos [ iHijo ] ) )
				{
					SNodDestruir ( &(p_nodObj->p_p_nodHijos [ iHijo ]), 1 );
				}
			}
			p_nodObj->p_p_nodHijos [ iHijo ] = NULL;
		}
		MemLiberar ( (void **) &(p_nodObj->p_p_nodHijos) );
	}
}

int	SNodEsHijo ( SNodo * p_nodObj )
{
	SNodo * p_nodPadre;
	int		iEnc;

     if ( ES_VALIDO ( p_nodObj ) )
     {
     	p_nodPadre = SNodPadre ( p_nodObj );
     	if ( ES_VALIDO ( p_nodPadre ) && ( SNodOrdenDelHijo ( p_nodPadre, p_nodObj ) >= 0 ) )
     	{
     		iEnc = 1;
     	}
     	else
     	{
     		iEnc = 0;
     	}
     }
     else
     {
          iEnc = 0;
     }
	return ( iEnc );
}

int SNodOrdenDelHijo ( SNodo * p_nodObj, SNodo * p_nodHijo )
{
	SNodo *		p_nodHijoAux;
	int			iHijo;
	int			iEnc;

     if ( ES_VALIDO ( p_nodObj ) )
     {
     	iEnc = 0;
     	iHijo = 0;
     	while ( ( iHijo < p_nodObj->iNumHijos ) && ( iEnc == 0 ) )
     	{
     		p_nodHijoAux = SNodHijo ( p_nodObj, iHijo );
     		if ( p_nodHijoAux == p_nodHijo )
     		{
     			iEnc = 1;
     		}
     		else
     		{
     			iHijo = iHijo + 1;
     		}
     	}

     	if ( iEnc == 0 )
     	{
     		iHijo = -1;
     	}
     }
     else
     {
          iHijo = -1;
     }
	return ( iHijo );
}

int SNodVerificar ( SNodo * p_nodObj, int iCorregir )
{
	int      iRes;
	SNodo *  p_nodHijo;
	int	    iHijo;

     if ( ES_VALIDO ( p_nodObj ) )
     {
     	iRes = 1;
     	for ( iHijo = 0; iHijo < p_nodObj->iNumHijos; iHijo = iHijo + 1 )
     	{
     		p_nodHijo = SNodHijo ( p_nodObj, iHijo );
     		if ( SNodPadre ( p_nodHijo ) != p_nodObj )
     		{
     			if ( iCorregir == 1 )
     			{
     				SNodEmpadronar ( p_nodHijo, p_nodObj );
     			}
     			iRes = 0;
     		}
     		if ( SNodVerificar ( p_nodHijo, iCorregir ) == 0 )
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

int	SNodLiberacionMemoriaActivada ( SNodo * p_nodObj )
{
	int iRes;

	if ( ES_VALIDO ( p_nodObj ) )
	{
		iRes = p_nodObj->iLiberar;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

// NOTA:Retorna un elemento duplicado pero desencadenado:
SNodo * SNodDuplicar ( SNodo * p_nodObj )
{
	SBloque *	p_blqDatos;
	SNodo * p_nodDup;

	if ( SNodEsValido ( p_nodObj ) == 1 )
	{
		p_blqDatos = p_nodObj->p_blqDatos;
		if ( ES_VALIDO ( p_blqDatos ) )
		{
			p_nodDup = SNodCrear ( SBlqTam ( p_blqDatos ) );
			if ( ES_VALIDO ( p_nodDup ) )
			{
				SBlqCopiar ( p_nodDup->p_blqDatos, p_blqDatos );
				p_nodDup->iLiberar = 1;
			}
		}
		else
		{
			p_nodDup = NULL;
		}
	}
	else
	{
		p_nodDup = NULL;
	}
	return ( p_nodDup );
}

static void SNodInicializar ( SNodo * p_nodObj, int iTamDatos, SBloque * p_blqDatos, byte * p_byDirDatos, int iLiberar )
{
    if ( ES_VALIDO ( p_nodObj ) )
    {
   		p_nodObj->p_p_nodHijos = NULL;
     	p_nodObj->p_nodPadre = NULL;
     	p_nodObj->iNumHijos = 0;
		if ( ES_VALIDO ( p_nodObj->p_blqDatos ) )
		{
			p_nodObj->p_blqDatos = p_blqDatos;
			p_nodObj->iLiberar = SBlqLiberacionMemoriaActivada ( p_blqDatos );
		}
		else if ( ES_VALIDO ( p_byDirDatos ) )
		{
			p_nodObj->p_blqDatos = SBlqAsignar ( p_byDirDatos, iTamDatos, iLiberar );
			if ( ES_VALIDO ( p_nodObj->p_blqDatos ) )
			{
				p_nodObj->iLiberar = SBlqLiberacionMemoriaActivada ( p_nodObj->p_blqDatos );
			}
			else
			{
				p_nodObj->iLiberar = 0;
			}
		}
		else
		{
			p_nodObj->p_blqDatos = SBlqCrear ( iTamDatos );
			if ( ES_VALIDO ( p_nodObj->p_blqDatos ) )
			{
				p_nodObj->iLiberar = 1;
			}
			else
			{
				p_nodObj->iLiberar = 0;
			}
		}
	}
}



