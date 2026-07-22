/******************************************************************************/
/*                               Versiones.cpp                                */
/*----------------------------------------------------------------------------*/
/* Librería:  GBase                                                           */
/* Versión:   1.0.0                                                           */
/* Fecha:     28/06/2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Fichero de código fuente que contiene la implementación de las rutinas     */
/* de manejo de cadenas de información de versión.                            */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#include "Versiones.h"
#include "Memoria.h"
#include "CadenasBase.h"
#include "Errores.h"







char * VersCadena ( int iVersion, int iSubversion, int iRevision, int iCorreccion )
{
	const char *	p_cPatron;
	char *			p_cAux;
	char *			p_cRes;
	int				iTam;

	if ( iVersion >= 0 )
	{
		iTam = 5;
		if ( iSubversion >= 0 )
		{
			iTam = iTam + 6;
			if ( iRevision >= 0 )
			{
				iTam = iTam + 6;
				if ( iCorreccion >= 0 )
				{
					iTam = iTam + 6;
					p_cPatron = VERS_PAT_4;
				}
				else
				{
					p_cPatron = VERS_PAT_3;
				}
			}
			else
			{
				p_cPatron = VERS_PAT_2;
			}
		}
		else
		{
			p_cPatron = VERS_PAT_1;
		}
		p_cAux = CadCrear ( iTam );
		if ( ES_VALIDO ( p_cAux ) )
		{
			sprintf ( p_cAux, p_cPatron, iVersion, iSubversion, iRevision, iCorreccion );
			p_cRes = CadDuplicar ( p_cAux );
		}
		else
		{
			p_cRes = NULL;
		}
	}
	else
	{
		p_cRes = NULL;
		ERROR_ESTABLECER ( ERR_PARAMETROS );
	}
	return ( p_cRes );
}

int VersProcesar ( const char * p_cCadena, int * p_iVersion, int * p_iSubversion, int * p_iRevision, int * p_iCorreccion )
{
	int iVersion; 
	int iSubversion;
	int iRevision;
	int iCorreccion;
	int	iRes;
	int iCampos;
	
	if ( ES_VALIDO ( p_cCadena ) )
	{
		iCampos = sscanf ( p_cCadena, VERS_PAT_4, &iVersion, &iSubversion, &iRevision, &iCorreccion );
		if ( iCampos > 0 )
		{
			if ( ES_VALIDO ( p_iVersion ) )
			{
				*p_iVersion = iVersion;
			}
			if ( ( iCampos > 1 ) && ES_VALIDO ( p_iSubversion ) )
			{
				*p_iSubversion = iSubversion;
			}
			if ( ( iCampos > 2 ) && ES_VALIDO ( p_iRevision ) )
			{
				*p_iRevision = iRevision;
			}
			if ( ( iCampos > 3 ) && ES_VALIDO ( p_iCorreccion ) )
			{
				*p_iCorreccion = iCorreccion;
			}
			iRes = 1;
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








