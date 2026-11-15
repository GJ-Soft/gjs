#include "SSecuenciaParejas.h"

#include "TiposBasicosConfig.h"




SSecuenciaParejas * SSecPrjCrear ()
{
	SSecuenciaParejas * p_secObj;
	
	p_secObj = (SSecuenciaParejas *) MemReservar ( sizeof ( SSecuenciaParejas ) );
	if ( ES_VALIDO ( p_secObj ) )
	{
		p_secObj->p_secDatos = SSecpCrear ();
		SSecpDesactivarLiberacionMemoria ( p_secObj->p_secDatos );
	}
	return ( p_secObj );
}

void SSecPrjDestruir ( SSecuenciaParejas ** p_p_secObj )
{
	SSecuenciaParejas * p_secObj;
	
	if ( ES_VALIDO ( p_p_secObj ) )
	{
		p_secObj = *p_p_secObj;

		if ( ES_VALIDO ( p_secObj ) )
		{
			SSecPrjVaciar ( p_secObj );
			SSecpDestruir ( &(p_secObj->p_secDatos) );
			MemLiberar ( (void **) p_p_secObj );
		}
	}
}

int SSecPrjEsValida ( SSecuenciaParejas * p_secObj )
{
	int iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		iRes = SSecpEsValida ( p_secObj->p_secDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SSecPrjEstaVacia ( SSecuenciaParejas * p_secObj )
{
	int iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		iRes = SSecpEstaVacia ( p_secObj->p_secDatos );
	}
	else
	{
		iRes = 1;
	}
	return ( iRes );
}

int SSecPrjNumElementos ( SSecuenciaParejas * p_secObj )
{
	int iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		iRes = SSecpNumElementos ( p_secObj->p_secDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

SPareja * SSecPrjElemento ( SSecuenciaParejas * p_secObj, int iElem )
{
	SPareja *	p_prjRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		p_prjRes = (SPareja *) SSecpElemento ( p_secObj->p_secDatos, iElem );
	}
	else
	{
		p_prjRes = NULL;
	}
	return ( p_prjRes );
}

int SSecPrjInsertar ( SSecuenciaParejas * p_secObj, SPareja * p_prjDatos )
{
	int iRes;

	if ( ES_VALIDO ( p_secObj ) )
	{
		iRes = SSecpInsertar ( p_secObj->p_secDatos, ( byte * ) p_prjDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

/* La pareja pasa a ser de la secuencia, que la destruye con ella. Si no se
   puede insertar, 0 y sigue siendo del llamante; InsertarExt la crea y, si no
   entra, la destruye. */
int SSecPrjInsertarExt ( SSecuenciaParejas * p_secObj, void * p_vPrimero, void * p_vSegundo )
{
	int 		iRes;
	SPareja * 	p_prjObj;
	
	p_prjObj = SPrjCrearSoloPtr ( p_vPrimero, p_vSegundo );
	if ( ES_VALIDO ( p_prjObj ) )
	{
		iRes = SSecPrjInsertar ( p_secObj, p_prjObj );
		if ( iRes != 1 )
		{
			SPrjDestruir ( &p_prjObj );
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SSecPrjVaciar ( SSecuenciaParejas * p_secObj )
{
	int				iRes;
	SPareja *		p_prjObj;
	SElementoPtr *	p_elpObj;

	if ( ES_VALIDO ( p_secObj ) )
	{
		/* Por la CADENA, no por indice: el indice entra por el extremo mas
		   cercano, asi que un recorrido completo sale cuadratico. Aqui solo se
		   suelta el dato; los nodos los quita SSecpVaciar. */
		p_elpObj = SSecpElementoPtr ( p_secObj->p_secDatos, 0 );
		while ( ES_VALIDO ( p_elpObj ) )
		{
			p_prjObj = (SPareja *) SElpDatos ( p_elpObj );
			SPrjDestruir ( &p_prjObj );
			p_elpObj = SElpSucesor ( p_elpObj );
		}
		iRes = SSecpVaciar ( p_secObj->p_secDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

/* Destruye la pareja; 0 si no hay ninguna en esa posicion. */
int SSecPrjEliminarElem ( SSecuenciaParejas * p_secObj, int iElem )
{
	int			iRes;
	SPareja *	p_prjObj;

	if ( ES_VALIDO ( p_secObj ) )
	{
		p_prjObj = (SPareja *) SSecpExtraer ( p_secObj->p_secDatos, iElem );
		if ( ES_VALIDO ( p_prjObj ) )
		{
			SPrjDestruir ( &p_prjObj );
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
