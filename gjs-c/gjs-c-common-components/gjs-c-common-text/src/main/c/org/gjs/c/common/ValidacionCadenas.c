
#include "ValidacionCadenas.h"

#include "TextoConfig.h"



int SCadEsCodigoValido ( SCadena * p_cadObj )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		if ( SCadLongitud ( p_cadObj ) > 0 )
		{
			if ( ( SCadContieneCaracteresNoAlfanumericos ( p_cadObj ) == 0 ) &&
				 ( ASCIIEsLetra ( SCadCaracter ( p_cadObj, 0 ) ) == 1 ) )
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

int SCadEsNombreValido ( SCadena * p_cadObj )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		if ( SCadLongitud ( p_cadObj ) > 0 )
		{
			if ( ( SCadContieneBlancos ( p_cadObj ) == 0 ) &&
				 ( SCadContieneCaracteresNoImprimibles ( p_cadObj ) == 0 ) &&
				 ( SCadContieneCaracteresNoEstandar ( p_cadObj ) == 0 ) &&
				 ( ASCIIEsLetra ( SCadCaracter ( p_cadObj, 0 ) ) == 1 ) )
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

int SCadEsDescripcionValida ( SCadena * p_cadObj )
{
	int iRes;

	if ( ES_VALIDO ( p_cadObj ) )
	{
		if ( SCadContieneCaracteresNoImprimibles ( p_cadObj ) == 0 )
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

int CadEsCodigoValido ( const char * p_cObj )
{
	int iRes;

	if ( ES_VALIDO ( p_cObj ) )
	{
		if ( CadLongitud ( p_cObj ) > 0 )
		{
			if ( ( CadContieneCaracteresNoAlfanumericos ( p_cObj ) == 0 ) &&
				 ( ASCIIEsLetra ( p_cObj [ 0 ] ) == 1 ) )
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

int CadEsNombreValido ( const char * p_cObj )
{
	int iRes;

	if ( ES_VALIDO ( p_cObj ) )
	{
		if ( CadLongitud ( p_cObj ) > 0 )
		{
			if ( ( CadContieneBlancos ( p_cObj ) == 0 ) &&
				 ( CadContieneCaracteresNoImprimibles ( p_cObj ) == 0 ) &&
				 ( CadContieneCaracteresNoEstandar ( p_cObj ) == 0 ) &&
				 ( ASCIIEsLetra ( p_cObj [ 0 ] ) == 1 ) )
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

int CadEsDescripcionValida ( const char * p_cObj )
{
	int iRes;

	if ( ES_VALIDO ( p_cObj ) )
	{
		if ( CadContieneCaracteresNoImprimibles ( p_cObj ) == 0 )
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


