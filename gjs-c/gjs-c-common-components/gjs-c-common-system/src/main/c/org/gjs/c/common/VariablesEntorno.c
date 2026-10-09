/******************************************************************************/
/*                           VariablesEntorno.c                               */
/*----------------------------------------------------------------------------*/
/* Librería:  Sistema                                                         */
/* Versión:   3.0.0                                                           */
/* Fecha:     25/03/2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Fichero de código fuente que contiene la implementación de la clase de     */
/* datos CVariablesEntorno.                                                   */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#include "VariablesEntorno.h"


#include "SistemaConfig.h"


#include <SBuffer.h>
#include <SCadena.h>




#define _ENTORNO_FORM_EST_VARIABLE		"%s=%s"
#define _ENTORNO_MAX_TAM_CAD_DEF		( SIS_MAX_TAM_VARIABLE + SIS_MAX_TAM_VALOR + 1 )





char * VarEntObtValor ( const char * p_cVariable )
{
	char *		p_cValor;
	SCadena *	p_cadValor;

	if ( ES_VALIDO ( p_cVariable ) )
	{
		p_cadValor = SCadGenerar ( getenv ( p_cVariable ) );
		if ( ES_VALIDO ( p_cadValor ) )
		{
			SCadEliminarCaracteresNoAlfanumericos ( p_cadValor );
			SCadEliminarBlancosLaterales ( p_cadValor );
			if ( SCadLongitud ( p_cadValor ) > 0 )
			{
				p_cValor = SCadDuplicarValor ( p_cadValor );
			}
			else
			{
				p_cValor = NULL;
			}
			SCadDestruir ( &p_cadValor );
		}
		else
		{
			p_cValor = NULL;
		}
	}
	else
	{
		p_cValor = NULL;
	}
	return ( p_cValor );
}

int VarEntEstValor ( const char * p_cVariable, const char * p_cValor )
{
	int iRes;

	if ( ES_VALIDO ( p_cVariable ) )
	{
#	 if ( defined ( WIN ) )
		/* _putenv_s copia las cadenas en el entorno del CRT (getenv las lee);
		   no hay problema de tiempo de vida como con putenv sobre un buffer
		   que despues se libera. */
		if ( _putenv_s ( p_cVariable, ES_NULO ( p_cValor ) ? "" : p_cValor ) == 0 )
#	 else
		/* setenv copia el valor. putenv guardaba el puntero al buffer y, al
		   liberarlo, la entrada del entorno quedaba colgando (fallo POSIX/Cygwin). */
		if ( setenv ( p_cVariable, ES_NULO ( p_cValor ) ? "" : p_cValor, 1 ) == 0 )
#	 endif
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

int VarEntExiste ( const char * p_cVariable )
{
	int 	iRes;
	char *	p_cValor;

	p_cValor = VarEntObtValor ( p_cVariable );
	if ( ES_VALIDO ( p_cValor ) )
	{
		MemLiberar ( (void **) &p_cValor );
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}




