#include "TiposPrimitiva.h"


#include "TiposBasicosConfig.h"







int TipPrimEsValido ( int iId )
{
	int iRes; 

	if ( ( iId == TIP_PRIM_PROCEDIMIENTO ) ||
 		 ( iId == TIP_PRIM_FUNCION ) )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int TipPrimEsProcedimiento ( int iId )
{
	int iRes;

	if ( iId == TIP_PRIM_PROCEDIMIENTO ) 
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int TipPrimEsFuncion( int iId )
{
	int iRes;

	if ( iId == TIP_PRIM_FUNCION ) 
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

