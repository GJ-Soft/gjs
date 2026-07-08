#include "TiposAccion.h"

#include "TiposDatosConfig.h"







int TipAccEsValido ( int iId )
{
	int iRes; 

	if ( ( iId == TIP_ACC_CODIGO ) ||
 		 ( iId == TIP_ACC_FUNCION ) ||
		 ( iId == TIP_ACC_MENU ) ||
		 ( iId == TIP_ACC_SALIR ) ||
 		 ( iId == TIP_ACC_VOLVER ) )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int TipAccEsCodigo ( int iId )
{
	int iRes;

	if ( iId == TIP_ACC_CODIGO ) 
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int TipAccEsFuncion ( int iId )
{
	int iRes;

	if ( iId == TIP_ACC_FUNCION ) 
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int TipAccEsMenu ( int iId )
{
	int iRes;

	if ( iId == TIP_ACC_MENU ) 
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int TipAccEsSalir ( int iId )
{
	int iRes;

	if ( iId == TIP_ACC_SALIR ) 
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int TipAccEsVolver ( int iId )
{
	int iRes;

	if ( iId == TIP_ACC_VOLVER ) 
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int CodAccEsValido ( int iCod )
{
	int iRes;

	if ( ( iCod >= 0 ) && ( iCod <= 100 ) ) 
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int CodAccEsSalir ( int iCod )
{
	int iRes;

	if ( iCod == COD_ACC_SALIR ) 
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int CodAccEsVolver ( int iCod )
{
	int iRes;

	if ( iCod == COD_ACC_VOLVER ) 
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

