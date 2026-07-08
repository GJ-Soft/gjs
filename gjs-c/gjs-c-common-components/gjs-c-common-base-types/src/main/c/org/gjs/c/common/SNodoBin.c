
#include "SNodoBin.h"


#include "TiposBasicosConfig.h"






static void SNodBinInicializar ( SNodoBin * p_nodbObj, int iTamDatos, SBloque * p_blqDatos, byte * p_byDirDatos, int iLiberar );




SNodoBin * SNodBinCrearMem ( int iTamDatos )
{
	SNodoBin * p_nodbObj;

	if ( iTamDatos > 0 )
	{
		p_nodbObj = (SNodoBin *) MemReservar ( sizeof ( SNodoBin ) );
		if ( p_nodbObj != NULL )
		{
			SNodBinInicializar ( p_nodbObj, iTamDatos, NULL, NULL, 1 );
		}
	}
	else
	{
		p_nodbObj = NULL;
	}
	return ( p_nodbObj );
}


SNodoBin * SNodBinCrearEntero ( int iValor )
{
	SNodoBin * p_nodbObj;

	p_nodbObj = SNodBinCrearMem ( sizeof ( int ) );
	SNodBinEstablecerEntero ( p_nodbObj, iValor );
	return ( p_nodbObj );
}

SNodoBin * SNodBinCrearEnteroLargo ( long lValor )
{
	SNodoBin * p_nodbObj;

	p_nodbObj = SNodBinCrearMem ( sizeof ( long ) );
	SNodBinEstablecerEnteroLargo ( p_nodbObj, lValor );
	return ( p_nodbObj );
}

SNodoBin * SNodBinCrearReal ( float fValor )
{
	SNodoBin * p_nodbObj;

	p_nodbObj = SNodBinCrearMem ( sizeof ( float ) );
	SNodBinEstablecerReal ( p_nodbObj, fValor );
	return ( p_nodbObj );
}

SNodoBin * SNodBinCrearRealDoble ( double dValor )
{
	SNodoBin * p_nodbObj;

	p_nodbObj = SNodBinCrearMem ( sizeof ( double ) );
	SNodBinEstablecerRealDoble ( p_nodbObj, dValor );
	return ( p_nodbObj );
}

SNodoBin * SNodBinCrearCadena ( const char * p_cValor )
{
	SNodoBin * p_nodbObj;

	if ( ES_VALIDO ( p_cValor ) )
	{
		p_nodbObj = SNodBinCrearMem ( CadLongitud ( p_cValor ) );
		SNodBinEstablecerCadena ( p_nodbObj, p_cValor );
	}
	else
	{
		p_nodbObj = NULL;
	}
	return ( p_nodbObj );
}

void SNodBinDestruir ( SNodoBin ** p_p_nodbObj, int iDestruirHijos )
{
    SNodoBin *   p_nodbObj;

    if ( ES_VALIDO ( p_p_nodbObj ) )
    {
        p_nodbObj = *p_p_nodbObj;
 		if ( ES_VALIDO ( p_nodbObj ) )
		{
			SNodBinLimpiarHijos ( p_nodbObj, iDestruirHijos );
			if ( p_nodbObj->iLiberar == 1 )
			{
				SBlqDestruir ( &(p_nodbObj->p_blqDatos) );
			}
			MemLiberar ( (void **) p_p_nodbObj );
		}
	}
}

int SNodBinEsValido ( SNodoBin * p_nodbObj )
{
	int iRes;

	if ( ES_VALIDO ( p_nodbObj ) )
	{
		if ( SBlqEsValido ( p_nodbObj->p_blqDatos ) == 1 )
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

int SNodBinTieneDatos ( SNodoBin * p_nodbObj )
{
	int iRes;

	if ( SNodBinEsValido ( p_nodbObj ) == 1 )
	{
		if ( SBlqTam ( p_nodbObj->p_blqDatos ) > 0 )
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

SBloque * SNodBinDatos ( SNodoBin * p_nodbObj )
{
	SBloque * p_blqRes;

	if ( ES_VALIDO ( p_nodbObj ) )
	{
		p_blqRes = p_nodbObj->p_blqDatos;
	}
	else
	{
		p_blqRes = NULL;
	}
	return ( p_blqRes );
}

int SNodBinEntero ( SNodoBin * p_nodbObj )
{
	int	iRes;

	if ( ES_VALIDO ( p_nodbObj ) )
	{
		iRes = SBlqEntero ( p_nodbObj->p_blqDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

long SNodBinEnteroLargo ( SNodoBin * p_nodbObj )
{
	long lRes;

	if ( ES_VALIDO ( p_nodbObj ) )
	{
		lRes = SBlqEnteroLargo ( p_nodbObj->p_blqDatos );
	}
	else
	{
		lRes = 0;
	}
	return ( lRes );
}

float SNodBinReal ( SNodoBin * p_nodbObj )
{
	float fRes;

	if ( ES_VALIDO ( p_nodbObj ) )
	{
		fRes = SBlqReal ( p_nodbObj->p_blqDatos );
	}
	else
	{
		fRes = 0;
	}
	return ( fRes );
}

double SNodBinRealDoble ( SNodoBin * p_nodbObj )
{
	double dRes;

	if ( ES_VALIDO ( p_nodbObj ) )
	{
		dRes = SBlqRealDoble ( p_nodbObj->p_blqDatos );
	}
	else
	{
		dRes = 0;
	}
	return ( dRes );
}

char * SNodBinCadena ( SNodoBin * p_nodbObj )
{
	char * p_cRes;

	if ( ES_VALIDO ( p_nodbObj ) )
	{
		p_cRes = SBlqCadena ( p_nodbObj->p_blqDatos );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

int SNodBinModificar ( SNodoBin * p_nodbObj, SBloque * p_blqDatos )
{
	int iRes;

	if ( ES_VALIDO ( p_nodbObj ) && ES_VALIDO ( p_blqDatos ) )
	{
		if ( p_nodbObj->iLiberar == 1 )
		{
			SBlqDestruir ( &(p_nodbObj->p_blqDatos) );
		}

		p_nodbObj->p_blqDatos = p_blqDatos;
		p_nodbObj->iLiberar = SBlqLiberacionMemoriaActivada ( p_blqDatos );
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SNodBinModificarDir ( SNodoBin * p_nodbObj, byte * p_byDirDatos, int iTamDatos, int iLiberar )
{
	int iRes;

	if ( ES_VALIDO ( p_nodbObj ) && ES_VALIDO ( p_byDirDatos ) && ( iTamDatos > 0 ) &&
		 BOOL_VALIDO ( iLiberar ) )
	{
		if ( p_nodbObj->iLiberar == 1 )
		{
			SBlqDestruir ( &(p_nodbObj->p_blqDatos) );
		}

		p_nodbObj->p_blqDatos = SBlqAsignar ( p_byDirDatos, iTamDatos, iLiberar );
		if ( ES_VALIDO ( p_nodbObj->p_blqDatos ) )
		{
			iRes = 1;
			p_nodbObj->iLiberar = SBlqLiberacionMemoriaActivada ( p_nodbObj->p_blqDatos );
		}
		else
		{
			iRes = 0;
			p_nodbObj->iLiberar = 0;
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SNodBinEstablecerByte ( SNodoBin * p_nodbObj, int iPos, byte byValor )
{
	int iRes;

	if ( ES_VALIDO ( p_nodbObj ) )
	{
		iRes = SBlqEscribirByte ( p_nodbObj->p_blqDatos, iPos, byValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SNodBinEstablecerEntero ( SNodoBin * p_nodbObj, int iValor )
{
	int iRes;

	if ( ES_VALIDO ( p_nodbObj ) )
	{
		iRes = SBlqEscribirEntero ( p_nodbObj->p_blqDatos, iValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SNodBinEstablecerEnteroLargo ( SNodoBin * p_nodbObj, long lValor )
{
	int iRes;

	if ( ES_VALIDO ( p_nodbObj ) )
	{
		iRes = SBlqEscribirEnteroLargo ( p_nodbObj->p_blqDatos, lValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SNodBinEstablecerReal ( SNodoBin * p_nodbObj, float fValor )
{
	int iRes;

	if ( ES_VALIDO ( p_nodbObj ) )
	{
		iRes = SBlqEscribirReal ( p_nodbObj->p_blqDatos, fValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SNodBinEstablecerRealDoble ( SNodoBin * p_nodbObj, double dValor )
{
	int iRes;

	if ( ES_VALIDO ( p_nodbObj ) )
	{
		iRes = SBlqEscribirRealDoble ( p_nodbObj->p_blqDatos, dValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SNodBinEstablecerCadena ( SNodoBin * p_nodbObj, const char * p_cValor )
{
	int iRes;

	if ( ES_VALIDO ( p_nodbObj ) )
	{
		iRes = SBlqEscribirCadena ( p_nodbObj->p_blqDatos, p_cValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

SNodoBin * SNodBinPadre ( SNodoBin * p_nodbObj )
{
     SNodoBin * p_nodbRes;

     if ( ES_VALIDO ( p_nodbObj ) )
     {
          p_nodbRes = p_nodbObj->p_nodbPadre;
     }
     else
     {
          p_nodbRes = NULL;
     }
	return ( p_nodbRes );
}

SNodoBin * SNodBinHijoIzq ( SNodoBin * p_nodbObj )
{
     SNodoBin * p_nodbRes;

     if ( ES_VALIDO ( p_nodbObj ) )
     {
          p_nodbRes = p_nodbObj->p_nodbHijoIzq;
     }
     else
     {
          p_nodbRes = NULL;
     }
	return ( p_nodbRes );
}

SNodoBin * SNodBinHijoDer ( SNodoBin * p_nodbObj )
{
     SNodoBin * p_nodbRes;

     if ( ES_VALIDO ( p_nodbObj ) )
     {
          p_nodbRes = p_nodbObj->p_nodbHijoDer;
     }
     else
     {
          p_nodbRes = NULL;
     }
	return ( p_nodbRes );
}

int SNodBinTienePadre ( SNodoBin * p_nodbObj )
{
	int iRes;

     if ( ES_VALIDO ( p_nodbObj ) )
     {
     	if ( ES_VALIDO ( p_nodbObj->p_nodbPadre ) )
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

int SNodBinTieneHijos ( SNodoBin * p_nodbObj )
{
	int iRes;

     if ( ES_VALIDO ( p_nodbObj ) )
     {
     	if ( ES_VALIDO ( p_nodbObj->p_nodbHijoIzq ) || ES_VALIDO ( p_nodbObj->p_nodbHijoDer ) )
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

int SNodBinTieneHermano ( SNodoBin * p_nodbObj )
{
	int iRes;

     if ( ES_VALIDO ( p_nodbObj ) )
     {
     	if ( ES_VALIDO ( p_nodbObj->p_nodbPadre ) )
     	{
     		if ( ( SNodBinTieneHijoIzq ( p_nodbObj->p_nodbPadre ) == 1 ) &&
     			 ( SNodBinTieneHijoDer ( p_nodbObj->p_nodbPadre ) == 1 ) )
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

int SNodBinEsHijoIzqDelPadre ( SNodoBin * p_nodbObj )
{
	int iRes;

     if ( ES_VALIDO ( p_nodbObj ) )
     {
     	if ( ES_VALIDO ( p_nodbObj->p_nodbPadre ) )
     	{
     		if ( SNodBinHijoIzq ( p_nodbObj->p_nodbPadre ) == p_nodbObj )
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

int SNodBinEsHijoDerDelPadre ( SNodoBin * p_nodbObj )
{
	int iRes;

     if ( ES_VALIDO ( p_nodbObj ) )
     {
     	if ( ES_VALIDO ( p_nodbObj->p_nodbPadre ) )
     	{
     		if ( SNodBinHijoDer ( p_nodbObj->p_nodbPadre ) == p_nodbObj )
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

int SNodBinTieneHijoIzq ( SNodoBin * p_nodbObj )
{
	int iRes;

     if ( ES_VALIDO ( p_nodbObj ) )
     {
     	if ( ES_VALIDO ( p_nodbObj->p_nodbHijoIzq ) )
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

int SNodBinTieneHijoDer ( SNodoBin * p_nodbObj )
{
	int iRes;

     if ( ES_VALIDO ( p_nodbObj ) )
     {
     	if ( ES_VALIDO ( p_nodbObj->p_nodbHijoDer ) )
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

int SNodBinTieneHermanoIzq ( SNodoBin * p_nodbObj )
{
	int iRes;

     if ( ES_VALIDO ( p_nodbObj ) )
     {
     	if ( ( SNodBinTieneHermano ( p_nodbObj ) == 1 ) && ( SNodBinEsHijoDerDelPadre ( p_nodbObj ) == 1 ) )
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

int SNodBinTieneHermanoDer ( SNodoBin * p_nodbObj )
{
	int iRes;

     if ( ES_VALIDO ( p_nodbObj ) )
     {
     	if ( ( SNodBinTieneHermano ( p_nodbObj ) == 1 ) && ( SNodBinEsHijoIzqDelPadre ( p_nodbObj ) == 1 ) )
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

int SNodBinNodosInferiores ( SNodoBin * p_nodbObj )
{
	int	iNodos;

     if ( ES_VALIDO ( p_nodbObj ) )
     {
     	iNodos = 0;
     	if ( ES_VALIDO ( p_nodbObj->p_nodbHijoIzq  ) )
     	{
     		iNodos = iNodos + 1 + SNodBinNodosInferiores ( p_nodbObj->p_nodbHijoIzq );
     	}
     	if ( ES_VALIDO ( p_nodbObj->p_nodbHijoDer  ) )
     	{
     		iNodos = iNodos + 1 + SNodBinNodosInferiores ( p_nodbObj->p_nodbHijoDer );
     	}
	}
	else
	{
		iNodos = 0;
	}
	return ( iNodos );
}

int SNodBinNivelesInferiores ( SNodoBin * p_nodbObj )
{
	int	iNiveles;
	int	iNivelesMax;

     if ( ES_VALIDO ( p_nodbObj ) )
     {
     	iNivelesMax = 0;
     	if ( ES_VALIDO ( p_nodbObj->p_nodbHijoIzq  ) )
     	{
     		iNiveles = 1 + SNodBinNivelesInferiores ( p_nodbObj->p_nodbHijoIzq );
     		if ( iNiveles > iNivelesMax )
     		{
     			iNivelesMax = iNiveles;
     		}
     	}
     	if ( ES_VALIDO ( p_nodbObj->p_nodbHijoDer  ) )
     	{
     		iNiveles = 1 + SNodBinNivelesInferiores ( p_nodbObj->p_nodbHijoDer );
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

int SNodBinProfundidad ( SNodoBin * p_nodbObj )
{
	int	iProfundidad;

     if ( ES_VALIDO ( p_nodbObj ) )
     {
     	if ( ES_VALIDO ( p_nodbObj->p_nodbPadre  ) )
     	{
     		iProfundidad = SNodBinProfundidad ( p_nodbObj->p_nodbPadre ) + 1;
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

int SNodBinEmpadronar ( SNodoBin * p_nodbObj, SNodoBin * p_nodbPadre )
{
	int iRes;

     if ( ES_VALIDO ( p_nodbObj ) )
     {
     	p_nodbObj->p_nodbPadre = p_nodbPadre;
     	if ( ES_VALIDO ( p_nodbObj->p_nodbPadre ) )
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

void SNodBinDesempadronar ( SNodoBin * p_nodbObj )
{
     if ( ES_VALIDO ( p_nodbObj ) )
     {
     	 p_nodbObj->p_nodbPadre = NULL;
     }
}

int SNodBinEliminarHijoIzq ( SNodoBin * p_nodbObj, int iLiberar )
{
	int iRes;

     if ( ES_VALIDO ( p_nodbObj ) )
     {
     	if ( ES_VALIDO ( p_nodbObj->p_nodbHijoIzq ) )
     	{
     		if ( iLiberar == 1 )
     		{
     			SNodBinDestruir ( &(p_nodbObj->p_nodbHijoIzq), 1 );
     		}
     		p_nodbObj->p_nodbHijoIzq = NULL;
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

int SNodBinEliminarHijoDer ( SNodoBin * p_nodbObj, int iLiberar )
{
	int iRes;

     if ( ES_VALIDO ( p_nodbObj ) )
     {
     	if ( ES_VALIDO ( p_nodbObj->p_nodbHijoDer ) )
     	{
     		if ( iLiberar == 1 )
     		{
     			SNodBinDestruir ( &(p_nodbObj->p_nodbHijoDer), 1 );
     		}
     		p_nodbObj->p_nodbHijoDer = NULL;
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

int SNodBinEstHijoIzq ( SNodoBin * p_nodbObj, SNodoBin * p_nodbHijo, int iLiberar )
{
	int iRes;

     if ( ES_VALIDO ( p_nodbObj ) )
     {
		if ( iLiberar == 1 )
		{
			SNodBinDestruir ( &(p_nodbObj->p_nodbHijoIzq), 1 );
		}
		if ( ES_VALIDO ( p_nodbHijo ) )
		{
			p_nodbHijo->p_nodbPadre = p_nodbObj;
		}
    	p_nodbObj->p_nodbHijoIzq = p_nodbHijo;
     	if ( ES_VALIDO ( p_nodbObj->p_nodbHijoIzq ) )
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

int SNodBinEstHijoDer ( SNodoBin * p_nodbObj, SNodoBin * p_nodbHijo, int iLiberar )
{
	int iRes;

     if ( ES_VALIDO ( p_nodbObj ) )
     {
		if ( iLiberar == 1 )
		{
			SNodBinDestruir ( &(p_nodbObj->p_nodbHijoDer), 1 );
		}
		if ( ES_VALIDO ( p_nodbHijo ) )
		{
			p_nodbHijo->p_nodbPadre = p_nodbObj;
		}
     	p_nodbObj->p_nodbHijoDer = p_nodbHijo;
     	if ( ES_VALIDO ( p_nodbObj->p_nodbHijoDer ) )
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

void SNodBinLimpiarHijos ( SNodoBin * p_nodbObj, int iLiberar )
{
     if ( ES_VALIDO ( p_nodbObj ) )
     {
     	SNodBinEstHijoIzq ( p_nodbObj, NULL, iLiberar );
     	SNodBinEstHijoDer ( p_nodbObj, NULL, iLiberar );
     }
}

int	SNodBinEsHijo ( SNodoBin * p_nodbObj, SNodoBin * p_nodbHijo )
{
	int iRes;

     if ( ES_VALIDO ( p_nodbObj ) )
     {
     	if ( ( p_nodbObj->p_nodbHijoIzq == p_nodbHijo ) ||
     		 ( p_nodbObj->p_nodbHijoDer == p_nodbHijo ) )
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

int	SNodBinEsHijoIzq ( SNodoBin * p_nodbObj, SNodoBin * p_nodbHijo )
{
	int iRes;

     if ( ES_VALIDO ( p_nodbObj ) )
     {
     	if ( p_nodbObj->p_nodbHijoIzq == p_nodbHijo )
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

int	SNodBinEsHijoDer ( SNodoBin * p_nodbObj, SNodoBin * p_nodbHijo )
{
	int iRes;

     if ( ES_VALIDO ( p_nodbObj ) )
     {
     	if ( p_nodbObj->p_nodbHijoDer == p_nodbHijo )
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

int SNodBinVerificar ( SNodoBin * p_nodbObj, int iCorregir )
{
	int			iRes;

     if ( ES_VALIDO ( p_nodbObj ) )
     {
     	iRes = 1;
		if ( ES_VALIDO ( p_nodbObj->p_nodbHijoIzq ) )
		{
			if ( SNodBinPadre ( p_nodbObj->p_nodbHijoIzq ) != p_nodbObj )
			{
				if ( iCorregir == 1 )
				{
					SNodBinEmpadronar ( p_nodbObj->p_nodbHijoIzq, p_nodbObj );
				}
				iRes = 0;
			}
			if ( SNodBinVerificar ( p_nodbObj->p_nodbHijoIzq, iCorregir ) == 0 )
			{
				iRes = 0;
			}
		}
 		if ( ES_VALIDO ( p_nodbObj->p_nodbHijoDer ) )
		{
			if ( SNodBinPadre ( p_nodbObj->p_nodbHijoDer ) != p_nodbObj )
			{
				if ( iCorregir == 1 )
				{
					SNodBinEmpadronar ( p_nodbObj->p_nodbHijoDer, p_nodbObj );
				}
				iRes = 0;
			}
			if ( SNodBinVerificar ( p_nodbObj->p_nodbHijoDer, iCorregir ) == 0 )
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

int	SNodBinLiberacionMemoriaActivada ( SNodoBin * p_nodbObj )
{
	int iRes;

	if ( ES_VALIDO ( p_nodbObj ) )
	{
		iRes = p_nodbObj->iLiberar;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

// NOTA:Retorna un elemento duplicado pero desencadenado:
SNodoBin * SNodBinDuplicar ( SNodoBin * p_nodbObj )
{
	SBloque *	p_blqDatos;
	SNodoBin * 	p_nodbDup;

	if ( SNodBinEsValido ( p_nodbObj ) == 1 )
	{
		p_blqDatos = p_nodbObj->p_blqDatos;
		if ( ES_VALIDO ( p_blqDatos ) )
		{
			p_nodbDup = SNodBinCrearMem ( SBlqTam ( p_blqDatos ) );
			if ( ES_VALIDO ( p_nodbDup ) )
			{
				SBlqCopiar ( p_nodbDup->p_blqDatos, p_blqDatos );
				p_nodbDup->iLiberar = 1;
			}
		}
		else
		{
			p_nodbDup = NULL;
		}
	}
	else
	{
		p_nodbDup = NULL;
	}
	return ( p_nodbDup );
}

static void SNodBinInicializar ( SNodoBin * p_nodbObj, int iTamDatos, SBloque * p_blqDatos, byte * p_byDirDatos, int iLiberar )
{
     if ( ES_VALIDO ( p_nodbObj ) )
     {
     	p_nodbObj->p_nodbPadre = NULL;
     	p_nodbObj->p_nodbHijoIzq = NULL;
     	p_nodbObj->p_nodbHijoDer = NULL;
		if ( ES_VALIDO ( p_blqDatos ) )
		{
			p_nodbObj->p_blqDatos = p_blqDatos;
			p_nodbObj->iLiberar = SBlqLiberacionMemoriaActivada ( p_blqDatos );
		}
		else if ( ES_VALIDO ( p_byDirDatos ) )
		{
			p_nodbObj->p_blqDatos = SBlqAsignar ( p_byDirDatos, iTamDatos, iLiberar );
			if ( ES_VALIDO ( p_nodbObj->p_blqDatos ) )
			{
				p_nodbObj->iLiberar = SBlqLiberacionMemoriaActivada ( p_nodbObj->p_blqDatos );
			}
			else
			{
				p_nodbObj->iLiberar = 0;
			}
		}
		else
		{
			p_nodbObj->p_blqDatos = SBlqCrear ( iTamDatos );
			if ( ES_VALIDO ( p_nodbObj->p_blqDatos ) )
			{
				p_nodbObj->iLiberar = 1;
			}
			else
			{
				p_nodbObj->iLiberar = 0;
			}
		}
     }
}

