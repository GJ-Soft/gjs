#include "TiposResultado.h"


#include "TiposBasicosConfig.h"







int ResEsValido ( int iId )
{
	int iRes; 

	if ( ( iId == RES_ABORTADO ) ||
		 ( iId == RES_ERROR ) ||
 		 ( iId == RES_CORRECTO ) )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int ResEsAbortado ( int iId )
{
	int iRes;

	if ( iId == RES_ABORTADO ) 
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int ResEsError ( int iId )
{
	int iRes;

	if ( iId == RES_ERROR ) 
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int ResEsCorrecto ( int iId )
{
	int iRes;

	if ( iId == RES_CORRECTO ) 
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

