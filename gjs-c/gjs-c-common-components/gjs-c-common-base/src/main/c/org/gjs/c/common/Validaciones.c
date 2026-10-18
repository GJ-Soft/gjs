
#include "Validaciones.h"


#include "BaseConfig.h"

#include "Memoria.h"
#include "Errores.h"




int ValidarCadena ( const char * p_cValor, FUN_VALIDAR_CADENA fValidacion )
{
	int iRes;

	if ( ES_VALIDO ( p_cValor ) )
	{
		if ( ES_VALIDO ( fValidacion ) )
		{
			iRes = fValidacion ( p_cValor );
		}
		else
		{
			iRes = 0;
			ERROR_ESTABLECER ( ERR_PARAMETROS );
		}
	}
	else
	{
		iRes = 0;
		ERROR_ESTABLECER ( ERR_PARAMETROS );
	}
	return ( iRes );
}
