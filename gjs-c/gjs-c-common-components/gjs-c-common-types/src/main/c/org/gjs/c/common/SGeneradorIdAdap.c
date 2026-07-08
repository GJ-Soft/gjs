/***************************************************************************/
/*                        SGeneradorIdAdap.cpp                             */
/*-------------------------------------------------------------------------*/
/* Librería: TiposDatos                                                    */
/* Versión:  1.1.0                                                         */
/* Fecha:    24/10/2006                                                    */
/* Autor:    Ginés Jiménez Sánchez                                         */
/*-------------------------------------------------------------------------*/
/* Descripción:                                                            */
/* Fichero de código fuente que contiene la implementación de la clase de  */
/* datos SGeneradorIdAdap.                                                 */
/*-------------------------------------------------------------------------*/
/***************************************************************************/

#include "SGeneradorIdAdap.h"

#include "TiposDatosConfig.h"




SGeneradorIdAdap * SGenIdAdpCrear ( int iTam, const char * p_cPatron )
{
	return ( SGenIdAdpCrearExt ( iTam, p_cPatron, NULL, NULL ) );
}



SGeneradorIdAdap * SGenIdAdpCrearExt ( int iTam, const char * p_cPatron, const char * p_cInicial, const char * p_cFinal )
{
	SGeneradorIdAdap * p_genidObj;
	
	if ( ( iTam > 0 ) && ( PatEsValido ( p_cPatron ) == 1 ) && ( CadLongitud ( p_cPatron ) == iTam ) ) 
	{
		p_genidObj = (SGeneradorIdAdap *) MemReservar ( sizeof ( SGeneradorIdAdap ) );
		if ( ES_VALIDO ( p_genidObj ) )
		{
			p_genidObj->p_idInicial = SIdAdpCrearExt ( iTam, p_cPatron );
			p_genidObj->p_idFinal = SIdAdpCrearExt ( iTam, p_cPatron );
			p_genidObj->p_idUltimo = NULL;
			if ( ES_VALIDO ( p_genidObj->p_idInicial ) && ES_VALIDO ( p_genidObj->p_idFinal ) )	
			{
				if ( ES_VALIDO ( p_cInicial ) )
				{
					if ( SIdAdpEstablecer ( p_genidObj->p_idInicial, p_cInicial ) == 0 )
					{
						SIdAdpEstablecerValorInicial (p_genidObj->p_idInicial );
					}
				}
				else
				{
					SIdAdpEstablecerValorInicial (p_genidObj->p_idInicial );
				}

				if ( ES_VALIDO ( p_cFinal ) )
				{
					if ( SIdAdpEstablecer ( p_genidObj->p_idFinal,  p_cFinal ) == 0 )
					{
						SIdAdpEstablecerValorFinal ( p_genidObj->p_idFinal );
					}
				}
				else
				{
					SIdAdpEstablecerValorFinal ( p_genidObj->p_idFinal );
				}
			}
			else
			{
				SGenIdAdpDestruir ( &p_genidObj );
			}
		}
	}
	else
	{
		p_genidObj = NULL;
	}
	return ( p_genidObj );
}

void SGenIdAdpDestruir ( SGeneradorIdAdap ** p_p_genidObj )
{
	SGeneradorIdAdap * p_genidObj;
	
	if ( ES_VALIDO ( p_p_genidObj ) )
	{
		p_genidObj = *p_p_genidObj;

		if ( ES_VALIDO ( p_genidObj ) )
		{
			SIdAdpDestruir ( &(p_genidObj->p_idInicial) );
			SIdAdpDestruir ( &(p_genidObj->p_idFinal) );
			SIdAdpDestruir ( &(p_genidObj->p_idUltimo) );
			MemLiberar ( (void **) p_p_genidObj );
		}
	}
}

const char * SGenIdAdpPatron ( SGeneradorIdAdap * p_genidObj )
{
	const char * p_cRes;

	if ( ES_VALIDO ( p_genidObj ) )
	{
		p_cRes = SIdAdpPatron ( p_genidObj->p_idInicial );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

const char * SGenIdAdpInicial ( SGeneradorIdAdap * p_genidObj )
{
	const char * p_cRes;

	if ( ES_VALIDO ( p_genidObj ) )
	{
		p_cRes = SIdAdpValor ( p_genidObj->p_idInicial );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

const char * SGenIdAdpFinal ( SGeneradorIdAdap * p_genidObj )
{
	const char * p_cRes;

	if ( ES_VALIDO ( p_genidObj ) )
	{
		p_cRes = SIdAdpValor ( p_genidObj->p_idFinal );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

const char * SGenIdAdpUltimo ( SGeneradorIdAdap * p_genidObj )
{
	const char * p_cRes;

	if ( ES_VALIDO ( p_genidObj ) )
	{
		p_cRes = SIdAdpValor ( p_genidObj->p_idUltimo );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

const char * SGenIdAdpAsignarSig ( SGeneradorIdAdap * p_genidObj )
{
	const char *	p_cRes;

	if ( SGenIdAdpEsValido ( p_genidObj ) == 1 )
	{
		if ( ES_NULO ( p_genidObj->p_idUltimo ) )
		{
			p_genidObj->p_idUltimo = SIdAdpDuplicar ( p_genidObj->p_idInicial );
			p_cRes = SIdAdpValor ( p_genidObj->p_idUltimo );
		}
		else
		{
			if ( SIdAdpEsMenor ( p_genidObj->p_idUltimo, p_genidObj->p_idFinal ) == 1 )
			{
				if ( SIdAdpIncrementar ( p_genidObj->p_idUltimo ) == 1 )
				{
					p_cRes = SIdAdpValor ( p_genidObj->p_idUltimo );
				}
				else
				{
					p_cRes = NULL;
				}
			}
			else
			{
				p_cRes = NULL;
			}
		}
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

int SGenIdAdpEsValido ( SGeneradorIdAdap * p_genidObj )
{
	int iRes;

	if ( ES_VALIDO ( p_genidObj ) )
	{
		if ( ( SIdAdpEsValido ( p_genidObj->p_idInicial ) == 1 ) && 
			 ( SIdAdpEsCompatible ( p_genidObj->p_idInicial, p_genidObj->p_idFinal ) == 1 ) &&
			 ( ES_NULO ( p_genidObj->p_idUltimo ) ||
			 ( SIdAdpEstaEnRangoIg ( p_genidObj->p_idUltimo, p_genidObj->p_idInicial, p_genidObj->p_idFinal ) == 1 ) ) )
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

int SGenIdAdpIniciar ( SGeneradorIdAdap * p_genidObj )
{
	int iRes;

	if ( ( SIdAdpEsValido ( p_genidObj->p_idInicial ) == 1 ) && 
		 ( SIdAdpEsCompatible ( p_genidObj->p_idInicial, p_genidObj->p_idFinal ) == 1 ) )
	{
		SIdAdpDestruir ( &p_genidObj->p_idUltimo );
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SGenIdAdpEstablecerUltimo ( SGeneradorIdAdap * p_genidObj, const char * p_cValor )
{
	int iRes;

	if ( ( SGenIdAdpEsValido ( p_genidObj ) == 1 ) && 
		 ( SGenIdAdpEsCompatibleValor ( p_genidObj, p_cValor ) == 1 ) )
	{
		if ( ES_NULO ( p_genidObj->p_idUltimo ) )
		{
			p_genidObj->p_idUltimo = SIdAdpDuplicar ( p_genidObj->p_idInicial );
		}
		iRes = SIdAdpEstablecer ( p_genidObj->p_idUltimo, p_cValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SGenIdAdpEsCompatibleValor ( SGeneradorIdAdap * p_genidObj, const char * p_cValor )
{
	int iRes;

	if ( ( SGenIdAdpEsValido ( p_genidObj ) == 1 ) && ES_VALIDO ( p_cValor ) )
	{
		iRes = SIdAdpEsCompatibleValor ( p_genidObj->p_idInicial, p_cValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}