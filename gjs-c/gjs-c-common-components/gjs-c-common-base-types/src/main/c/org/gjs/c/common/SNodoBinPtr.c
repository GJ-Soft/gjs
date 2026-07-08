
#include "SNodoBinPtr.h"


#include "TiposBasicosConfig.h"






static void SNodBinPtrInicializar ( SNodoBinPtr * p_nodbpObj, byte * p_byDirDatos, int iLiberar );




SNodoBinPtr * SNodBinPtrCrearMem ( int iTamDatos )
{
	SNodoBinPtr * p_nodbpObj;

	if ( iTamDatos > 0 )
	{
		p_nodbpObj = SNodBinPtrCrear( (byte *) MemReservar ( iTamDatos ), 1 );
	}
	else
	{
		p_nodbpObj = NULL;
	}
	return ( p_nodbpObj );
}

SNodoBinPtr * SNodBinPtrCrear ( byte * p_byDatos, int iLiberar ) {
	SNodoBinPtr * p_nodbpObj;

	if ( ES_VALIDO( p_byDatos ) )
	{
		p_nodbpObj = (SNodoBinPtr *) MemReservar ( sizeof ( SNodoBinPtr ) );
		if ( p_nodbpObj != NULL )
		{
			SNodBinPtrInicializar ( p_nodbpObj, p_byDatos, iLiberar );
		}
	}
	else
	{
		p_nodbpObj = NULL;
	}
	return ( p_nodbpObj );
}

void SNodBinPtrDestruir ( SNodoBinPtr ** p_p_nodbpObj, int iDestruirHijos )
{
    SNodoBinPtr *   p_nodbpObj;

    if ( ES_VALIDO ( p_p_nodbpObj ) )
    {
        p_nodbpObj = *p_p_nodbpObj;
 		if ( ES_VALIDO ( p_nodbpObj ) )
		{
			SNodBinPtrLimpiarHijos ( p_nodbpObj, iDestruirHijos );
			if ( p_nodbpObj->iLiberar == 1 )
			{
				MemLiberar ( (void **) &(p_nodbpObj->p_byDatos) );
			}
			MemLiberar ( (void **) p_p_nodbpObj );
		}
    }
}

int SNodBinPtrEsValido ( SNodoBinPtr * p_nodbpObj )
{
	int iRes;

	if ( ES_VALIDO ( p_nodbpObj ) )
	{
		if ( ES_VALIDO ( p_nodbpObj->p_byDatos ) )
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

int SNodBinPtrTieneDatos ( SNodoBinPtr * p_nodbpObj )
{
	int iRes;

	if ( SNodBinPtrEsValido ( p_nodbpObj ) )
	{
		if ( ES_VALIDO ( p_nodbpObj->p_byDatos ) )
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

byte * SNodBinPtrDatos ( SNodoBinPtr * p_nodbpObj )
{
	byte * p_byRes;

	if ( ES_VALIDO ( p_nodbpObj ) )
	{
		p_byRes = p_nodbpObj->p_byDatos;
	}
	else
	{
		p_byRes = NULL;
	}
	return ( p_byRes );
}

int SNodBinPtrModificar ( SNodoBinPtr * p_nodbpObj, byte * p_byDatos, int iLiberar )
{
	int iRes;

	if ( ES_VALIDO ( p_nodbpObj ) && ES_VALIDO ( p_byDatos ) && BOOL_VALIDO ( iLiberar ) )
	{
		if ( p_nodbpObj->iLiberar == 1 )
		{
			MemLiberar ( (void **) &(p_nodbpObj->p_byDatos) );
		}

		p_nodbpObj->p_byDatos = p_byDatos;
		if ( ES_VALIDO ( p_nodbpObj->p_byDatos ) )
		{
			iRes = 1;
			p_nodbpObj->iLiberar = iLiberar;
		}
		else
		{
			iRes = 0;
			p_nodbpObj->iLiberar = 0;
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

SNodoBinPtr * SNodBinPtrPadre ( SNodoBinPtr * p_nodbpObj )
{
     SNodoBinPtr * p_nodbpRes;

     if ( ES_VALIDO ( p_nodbpObj ) )
     {
          p_nodbpRes = p_nodbpObj->p_nodbpPadre;
     }
     else
     {
          p_nodbpRes = NULL;
     }
	return ( p_nodbpRes );
}

SNodoBinPtr * SNodBinPtrHijoIzq ( SNodoBinPtr * p_nodbpObj )
{
     SNodoBinPtr * p_nodbpRes;

     if ( ES_VALIDO ( p_nodbpObj ) )
     {
          p_nodbpRes = p_nodbpObj->p_nodbpHijoIzq;
     }
     else
     {
          p_nodbpRes = NULL;
     }
	return ( p_nodbpRes );
}

SNodoBinPtr * SNodBinPtrHijoDer ( SNodoBinPtr * p_nodbpObj )
{
     SNodoBinPtr * p_nodbpRes;

     if ( ES_VALIDO ( p_nodbpObj ) )
     {
          p_nodbpRes = p_nodbpObj->p_nodbpHijoDer;
     }
     else
     {
          p_nodbpRes = NULL;
     }
	return ( p_nodbpRes );
}

int SNodBinPtrTienePadre ( SNodoBinPtr * p_nodbpObj )
{
	int iRes;

     if ( ES_VALIDO ( p_nodbpObj ) )
     {
     	if ( ES_VALIDO ( p_nodbpObj->p_nodbpPadre ) )
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

int SNodBinPtrTieneHijos ( SNodoBinPtr * p_nodbpObj )
{
	int iRes;

     if ( ES_VALIDO ( p_nodbpObj ) )
     {
     	if ( ES_VALIDO ( p_nodbpObj->p_nodbpHijoIzq ) || ES_VALIDO ( p_nodbpObj->p_nodbpHijoDer ) )
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

int SNodBinPtrTieneHermano ( SNodoBinPtr * p_nodbpObj )
{
	int iRes;

     if ( ES_VALIDO ( p_nodbpObj ) )
     {
     	if ( ES_VALIDO ( p_nodbpObj->p_nodbpPadre ) )
     	{
     		if ( ( SNodBinPtrTieneHijoIzq ( p_nodbpObj->p_nodbpPadre ) == 1 ) &&
     			 ( SNodBinPtrTieneHijoDer ( p_nodbpObj->p_nodbpPadre ) == 1 ) )
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

int SNodBinPtrEsHijoIzqDelPadre ( SNodoBinPtr * p_nodbpObj )
{
	int iRes;

     if ( ES_VALIDO ( p_nodbpObj ) )
     {
     	if ( ES_VALIDO ( p_nodbpObj->p_nodbpPadre ) )
     	{
     		if ( SNodBinPtrHijoIzq ( p_nodbpObj->p_nodbpPadre ) == p_nodbpObj )
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

int SNodBinPtrEsHijoDerDelPadre ( SNodoBinPtr * p_nodbpObj )
{
	int iRes;

     if ( ES_VALIDO ( p_nodbpObj ) )
     {
     	if ( ES_VALIDO ( p_nodbpObj->p_nodbpPadre ) )
     	{
     		if ( SNodBinPtrHijoDer ( p_nodbpObj->p_nodbpPadre ) == p_nodbpObj )
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

int SNodBinPtrTieneHijoIzq ( SNodoBinPtr * p_nodbpObj )
{
	int iRes;

     if ( ES_VALIDO ( p_nodbpObj ) )
     {
     	if ( ES_VALIDO ( p_nodbpObj->p_nodbpHijoIzq ) )
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

int SNodBinPtrTieneHijoDer ( SNodoBinPtr * p_nodbpObj )
{
	int iRes;

     if ( ES_VALIDO ( p_nodbpObj ) )
     {
     	if ( ES_VALIDO ( p_nodbpObj->p_nodbpHijoDer ) )
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

int SNodBinPtrTieneHermanoIzq ( SNodoBinPtr * p_nodbpObj )
{
	int iRes;

     if ( ES_VALIDO ( p_nodbpObj ) )
     {
     	if ( ( SNodBinPtrTieneHermano ( p_nodbpObj ) == 1 ) && ( SNodBinPtrEsHijoDerDelPadre ( p_nodbpObj ) == 1 ) )
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

int SNodBinPtrTieneHermanoDer ( SNodoBinPtr * p_nodbpObj )
{
	int iRes;

     if ( ES_VALIDO ( p_nodbpObj ) )
     {
     	if ( ( SNodBinPtrTieneHermano ( p_nodbpObj ) == 1 ) && ( SNodBinPtrEsHijoIzqDelPadre ( p_nodbpObj ) == 1 ) )
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

int SNodBinPtrNodosInferiores ( SNodoBinPtr * p_nodbpObj )
{
	int	iNodos;

     if ( ES_VALIDO ( p_nodbpObj ) )
     {
     	iNodos = 0;
     	if ( ES_VALIDO ( p_nodbpObj->p_nodbpHijoIzq  ) )
     	{
     		iNodos = iNodos + 1 + SNodBinPtrNodosInferiores ( p_nodbpObj->p_nodbpHijoIzq );
     	}
     	if ( ES_VALIDO ( p_nodbpObj->p_nodbpHijoDer  ) )
     	{
     		iNodos = iNodos + 1 + SNodBinPtrNodosInferiores ( p_nodbpObj->p_nodbpHijoDer );
     	}
	}
	else
	{
		iNodos = 0;
	}
	return ( iNodos );
}

int SNodBinPtrNivelesInferiores ( SNodoBinPtr * p_nodbpObj )
{
	int	iNiveles;
	int	iNivelesMax;

     if ( ES_VALIDO ( p_nodbpObj ) )
     {
     	iNivelesMax = 0;
     	if ( ES_VALIDO ( p_nodbpObj->p_nodbpHijoIzq  ) )
     	{
     		iNiveles = 1 + SNodBinPtrNivelesInferiores ( p_nodbpObj->p_nodbpHijoIzq );
     		if ( iNiveles > iNivelesMax )
     		{
     			iNivelesMax = iNiveles;
     		}
     	}
     	if ( ES_VALIDO ( p_nodbpObj->p_nodbpHijoDer  ) )
     	{
     		iNiveles = 1 + SNodBinPtrNivelesInferiores ( p_nodbpObj->p_nodbpHijoDer );
     		if ( iNiveles > iNivelesMax )
     		{
     			iNivelesMax = iNiveles;
     		}
     	}
	}
	else
	{
		iNivelesMax = 0;
	}
	return ( iNivelesMax );
}

int SNodBinPtrProfundidad ( SNodoBinPtr * p_nodbpObj )
{
	int	iProfundidad;

     if ( ES_VALIDO ( p_nodbpObj ) )
     {
     	if ( ES_VALIDO ( p_nodbpObj->p_nodbpPadre  ) )
     	{
     		iProfundidad = SNodBinPtrProfundidad ( p_nodbpObj->p_nodbpPadre ) + 1;
     	}
     	else
     	{
     		iProfundidad = 0;
     	}
	}
	else
	{
		iProfundidad = 0;
	}
	return ( iProfundidad );
}

int SNodBinPtrEmpadronar ( SNodoBinPtr * p_nodbpObj, SNodoBinPtr * p_nodbpPadre )
{
	int iRes;

     if ( ES_VALIDO ( p_nodbpObj ) )
     {
     	p_nodbpObj->p_nodbpPadre = p_nodbpPadre;
     	if ( ES_VALIDO ( p_nodbpObj->p_nodbpPadre ) )
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

void SNodBinPtrDesempadronar ( SNodoBinPtr * p_nodbpObj )
{
     if ( ES_VALIDO ( p_nodbpObj ) )
     {
     	 p_nodbpObj->p_nodbpPadre = NULL;
     }
}

int SNodBinPtrEliminarHijoIzq ( SNodoBinPtr * p_nodbpObj, int iLiberar )
{
	int iRes;

     if ( ES_VALIDO ( p_nodbpObj ) )
     {
     	if ( ES_VALIDO ( p_nodbpObj->p_nodbpHijoIzq ) )
     	{
     		if ( iLiberar == 1 )
     		{
     			SNodBinPtrDestruir ( &(p_nodbpObj->p_nodbpHijoIzq), 1 );
     		}
     		p_nodbpObj->p_nodbpHijoIzq = NULL;
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

int SNodBinPtrEliminarHijoDer ( SNodoBinPtr * p_nodbpObj, int iLiberar )
{
	int iRes;

     if ( ES_VALIDO ( p_nodbpObj ) )
     {
     	if ( ES_VALIDO ( p_nodbpObj->p_nodbpHijoDer ) )
     	{
     		if ( iLiberar == 1 )
     		{
     			SNodBinPtrDestruir ( &(p_nodbpObj->p_nodbpHijoDer), 1 );
     		}
     		p_nodbpObj->p_nodbpHijoDer = NULL;
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

int SNodBinPtrEstHijoIzq ( SNodoBinPtr * p_nodbpObj, SNodoBinPtr * p_nodbpHijo, int iLiberar )
{
	int iRes;

     if ( ES_VALIDO ( p_nodbpObj ) )
     {
		if ( iLiberar == 1 )
		{
			SNodBinPtrDestruir ( &(p_nodbpObj->p_nodbpHijoIzq), 1 );
		}
		if ( ES_VALIDO ( p_nodbpHijo ) )
		{
			p_nodbpHijo->p_nodbpPadre = p_nodbpObj;
		}
		p_nodbpObj->p_nodbpHijoIzq = p_nodbpHijo;
     	if ( ES_VALIDO ( p_nodbpObj->p_nodbpHijoIzq ) )
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

int SNodBinPtrEstHijoDer ( SNodoBinPtr * p_nodbpObj, SNodoBinPtr * p_nodbpHijo, int iLiberar )
{
	int iRes;

     if ( ES_VALIDO ( p_nodbpObj ) )
     {
		if ( iLiberar == 1 )
		{
			SNodBinPtrDestruir ( &(p_nodbpObj->p_nodbpHijoDer), 1 );
		}
		if ( ES_VALIDO ( p_nodbpHijo ) )
		{
			p_nodbpHijo->p_nodbpPadre = p_nodbpObj;
		}
    	p_nodbpObj->p_nodbpHijoDer = p_nodbpHijo;
     	if ( ES_VALIDO ( p_nodbpObj->p_nodbpHijoDer ) )
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

void SNodBinPtrLimpiarHijos ( SNodoBinPtr * p_nodbpObj, int iLiberar )
{
     if ( ES_VALIDO ( p_nodbpObj ) )
     {
     	SNodBinPtrEstHijoIzq ( p_nodbpObj, NULL, iLiberar );
     	SNodBinPtrEstHijoDer ( p_nodbpObj, NULL, iLiberar );
     }
}

int	SNodBinPtrEsHijo ( SNodoBinPtr * p_nodbpObj, SNodoBinPtr * p_nodbpHijo )
{
	int iRes;

     if ( ES_VALIDO ( p_nodbpObj ) )
     {
     	if ( ( p_nodbpObj->p_nodbpHijoIzq == p_nodbpHijo ) ||
     		 ( p_nodbpObj->p_nodbpHijoDer == p_nodbpHijo ) )
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

int	SNodBinPtrEsHijoIzq ( SNodoBinPtr * p_nodbpObj, SNodoBinPtr * p_nodbpHijo )
{
	int iRes;

     if ( ES_VALIDO ( p_nodbpObj ) )
     {
     	if ( p_nodbpObj->p_nodbpHijoIzq == p_nodbpHijo )
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

int	SNodBinPtrEsHijoDer ( SNodoBinPtr * p_nodbpObj, SNodoBinPtr * p_nodbpHijo )
{
	int iRes;

     if ( ES_VALIDO ( p_nodbpObj ) )
     {
     	if ( p_nodbpObj->p_nodbpHijoDer == p_nodbpHijo )
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

int SNodBinPtrVerificar ( SNodoBinPtr * p_nodbpObj, int iCorregir )
{
	int			iRes;

     if ( ES_VALIDO ( p_nodbpObj ) )
     {
     	iRes = 1;
		if ( ES_VALIDO ( p_nodbpObj->p_nodbpHijoIzq ) )
		{
			if ( SNodBinPtrPadre ( p_nodbpObj->p_nodbpHijoIzq ) != p_nodbpObj )
			{
				if ( iCorregir == 1 )
				{
					SNodBinPtrEmpadronar ( p_nodbpObj->p_nodbpHijoIzq, p_nodbpObj );
				}
				iRes = 0;
			}
			if ( SNodBinPtrVerificar ( p_nodbpObj->p_nodbpHijoIzq, iCorregir ) == 0 )
			{
				iRes = 0;
			}
		}
		if ( ES_VALIDO ( p_nodbpObj->p_nodbpHijoDer ) )
		{
			if ( SNodBinPtrPadre ( p_nodbpObj->p_nodbpHijoDer ) != p_nodbpObj )
			{
				if ( iCorregir == 1 )
				{
					SNodBinPtrEmpadronar ( p_nodbpObj->p_nodbpHijoDer, p_nodbpObj );
				}
				iRes = 0;
			}
			if ( SNodBinPtrVerificar ( p_nodbpObj->p_nodbpHijoDer, iCorregir ) == 0 )
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

int	SNodBinPtrLiberacionMemoriaActivada ( SNodoBinPtr * p_nodbpObj )
{
	int iRes;

	if ( ES_VALIDO ( p_nodbpObj ) )
	{
		iRes = p_nodbpObj->iLiberar;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

static void SNodBinPtrInicializar ( SNodoBinPtr * p_nodbpObj, byte * p_byDirDatos, int iLiberar )
{
     if ( ES_VALIDO ( p_nodbpObj ) )
     {
     	p_nodbpObj->p_nodbpPadre = NULL;
     	p_nodbpObj->p_nodbpHijoIzq = NULL;
     	p_nodbpObj->p_nodbpHijoDer = NULL;
		p_nodbpObj->p_byDatos = p_byDirDatos;
		if ( ES_VALIDO ( p_nodbpObj->p_byDatos ) )
		{
			p_nodbpObj->iLiberar = iLiberar;
		}
		else
		{
			p_nodbpObj->iLiberar = 0;
		}
    }
}

