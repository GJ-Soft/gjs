#include "SAccion.h"

#include "TiposDatosConfig.h"


SAccion * SAccCrear ( int iTipo )
{
	return ( SAccCrearExt ( iTipo, COD_ACC_NULO, NULL ) );
}

SAccion * SAccCrearExt ( int iTipo, int iCodigo, PFUNINTI p_fAccion )
{
	SAccion * p_accObj;
	
	if ( TipAccEsValido ( iTipo ) == 1 )
	{
		p_accObj = (SAccion *) MemReservar ( sizeof ( SAccion ) );
		if ( ES_VALIDO ( p_accObj ) )
		{
			if ( SAccEstablecerExt ( p_accObj, iTipo, iCodigo, p_fAccion ) == 0 )
			{
				SAccDestruir ( &p_accObj );
			}
		}
	}
	else
	{
		p_accObj = NULL;
	}
	return ( p_accObj );
}

void SAccDestruir ( SAccion ** p_p_accObj )
{
	SAccion * p_accObj;
	
	if ( ES_VALIDO ( p_p_accObj ) )
	{
		p_accObj = *p_p_accObj;

		if ( ES_VALIDO ( p_accObj ) )
		{
			MemLiberar ( (void **) p_p_accObj );
		}
	}
}

int SAccEsValida ( SAccion * p_accObj )
{
	int iRes;

	if ( ES_VALIDO ( p_accObj ) )
	{
		if ( ( TipAccEsValido ( p_accObj->iTipo ) == 1 ) && ( CodAccEsValido ( p_accObj->iCodigo ) == 1 ) )
		{
			if ( ( TipAccEsCodigo ( p_accObj->iTipo ) == 1 ) || ( TipAccEsMenu ( p_accObj->iTipo ) == 1 ) )
			{
				iRes = 1;
			}
			else if ( TipAccEsFuncion ( p_accObj->iTipo ) == 1 )
			{
				if ( ES_VALIDO ( p_accObj->p_fAccion ) )
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
				iRes = 1;
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

int SAccTipo ( SAccion * p_accObj )
{
	int iRes;

	if ( ES_VALIDO ( p_accObj ) )
	{
		iRes = p_accObj->iTipo;
	}
	else
	{
		iRes = TIP_ACC_NULO;
	}
	return ( iRes );
}

int SAccRetornaCodigo ( SAccion * p_accObj )
{
	int iRes;

	if ( ES_VALIDO ( p_accObj ) )
	{
		iRes = TipAccEsCodigo ( p_accObj->iTipo );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SAccInvocaMenu ( SAccion * p_accObj )
{
	int iRes;

	if ( ES_VALIDO ( p_accObj ) )
	{
		iRes = TipAccEsMenu ( p_accObj->iTipo );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SAccEjecutaFuncion ( SAccion * p_accObj )
{
	int iRes;

	if ( ES_VALIDO ( p_accObj ) )
	{
		iRes = TipAccEsFuncion ( p_accObj->iTipo );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SAccOrdenaSalir ( SAccion * p_accObj )
{
	int iRes;

	if ( ES_VALIDO ( p_accObj ) )
	{
		iRes = TipAccEsSalir ( p_accObj->iTipo );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SAccOrdenaVolver ( SAccion * p_accObj )
{
	int iRes;

	if ( ES_VALIDO ( p_accObj ) )
	{
		iRes = TipAccEsVolver ( p_accObj->iTipo );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SAccCodigo ( SAccion * p_accObj )
{
	int iRes;

	if ( ES_VALIDO ( p_accObj ) )
	{
		iRes = p_accObj->iCodigo;
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

PFUNINTI SAccFuncion ( SAccion * p_accObj )
{
	PFUNINTI p_fRes;

	if ( ES_VALIDO ( p_accObj ) )
	{
		p_fRes = p_accObj->p_fAccion;
	}
	else
	{
		p_fRes = NULL;
	}
	return ( p_fRes );
}

int SAccEstablecer ( SAccion * p_accObj, int iTipo )
{
	return ( SAccEstablecerExt ( p_accObj, iTipo, COD_ACC_NULO, NULL ) );
}

int SAccEstablecerExt ( SAccion * p_accObj, int iTipo, int iCodigo, PFUNINTI p_fAccion )
{
	int iRes;

	if ( ( TipAccEsValido ( iTipo ) == 1 ) && 
		 ( ( CodAccEsValido ( iCodigo ) == 1 ) || 
		   ( ( TipAccEsCodigo ( iTipo ) == 0 ) && ( TipAccEsMenu ( iTipo ) == 0 ) ) ) )
	{
		p_accObj->iTipo = iTipo;
		p_accObj->iCodigo = -1;
		p_accObj->p_fAccion = NULL;
		if ( ( TipAccEsCodigo ( iTipo ) == 1 ) || ( TipAccEsMenu ( iTipo ) == 1 ) )
		{
			p_accObj->iCodigo = iCodigo;
		}
		else if ( TipAccEsFuncion ( iTipo ) == 1 )
		{
			p_accObj->iCodigo = iCodigo;
			p_accObj->p_fAccion = p_fAccion;
		}
		else if ( TipAccEsSalir ( iTipo ) == 1 )
		{
			p_accObj->iCodigo = COD_ACC_SALIR;
		}
		else
		{
			p_accObj->iCodigo = COD_ACC_VOLVER;
		}
		iRes = SAccEsValida ( p_accObj );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SAccEstablecerCodigo ( SAccion * p_accObj, int iCodigo )
{
	int iRes;

	if ( ( ( SAccRetornaCodigo ( p_accObj ) == 1 ) || ( SAccInvocaMenu ( p_accObj ) == 1 ) || ( SAccEjecutaFuncion ( p_accObj ) == 1 ) ) && 
		 ( CodAccEsValido ( iCodigo ) == 1 ) )
	{
		p_accObj->iCodigo = iCodigo;
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SAccEstablecerFuncion ( SAccion * p_accObj, PFUNINTI p_fAccion )
{
	int iRes;

	if ( ( SAccEjecutaFuncion ( p_accObj ) == 1 ) && ES_VALIDO ( p_fAccion ) )
	{
		p_accObj->p_fAccion = p_fAccion;
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SAccEjecutar ( SAccion * p_accObj )
{
	int iRes;

	if ( SAccEsValida ( p_accObj ) == 1 ) 
	{
		if ( TipAccEsCodigo ( p_accObj->iTipo ) == 1 )
		{
			iRes = p_accObj->iCodigo;
		}
		else if ( TipAccEsMenu ( p_accObj->iTipo ) == 1 )
		{
			iRes = p_accObj->iCodigo;
		}
		else if ( TipAccEsFuncion ( p_accObj->iTipo ) == 1 )
		{
			iRes = p_accObj->p_fAccion ( p_accObj->iCodigo );
		}
		else
		{
			iRes = p_accObj->iCodigo;
		}
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

SAccion * SAccDuplicar (  SAccion * p_accObj )
{
	SAccion * p_accRes;

	if ( SAccEsValida ( p_accObj ) == 1 ) 
	{
		p_accRes = SAccCrearExt ( p_accObj->iTipo, p_accObj->iCodigo, p_accObj->p_fAccion );
	}
	else
	{
		p_accRes = NULL;
	}
	return ( p_accRes );
}

