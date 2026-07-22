
#include "ModosApertura.h"

#include "FicherosConfig.h"




int ModAprEsValido ( int iModo )
{
	int iRes;

	if ( ( iModo == MOD_APR_LECTURA ) || 
		 ( iModo == MOD_APR_ESCRITURA ) || 
		 ( iModo == MOD_APR_REESCRITURA ) )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int ModAprPermiteEscritura ( int iModo )
{
	int iRes;

	if ( ( iModo == MOD_APR_ESCRITURA ) || 
		 ( iModo == MOD_APR_REESCRITURA ) )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

