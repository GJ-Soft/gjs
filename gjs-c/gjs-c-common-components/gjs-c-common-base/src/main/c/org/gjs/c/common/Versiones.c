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
	int				iCampos;
	char *			p_cAux;
	char *			p_cRes;
	int				iTam;

	if ( iVersion >= 0 )
	{
		/* Cada campo es un int: hasta 11 caracteres con signo, mas el separador. */
		iTam = 11;
		if ( iSubversion >= 0 )
		{
			iTam = iTam + 12;
			if ( iRevision >= 0 )
			{
				iTam = iTam + 12;
				if ( iCorreccion >= 0 )
				{
					iTam = iTam + 12;
					iCampos = 4;
				}
				else
				{
					iCampos = 3;
				}
			}
			else
			{
				iCampos = 2;
			}
		}
		else
		{
			iCampos = 1;
		}
		p_cAux = CadCrear ( iTam );
		if ( ES_VALIDO ( p_cAux ) )
		{
			/* Un snprintf por patron, con el literal: con el patron en una
			   variable el compilador no puede comprobar el formato contra los
			   argumentos, y cada patron lleva los suyos y no cuatro siempre. */
			if ( iCampos == 4 )
			{
				snprintf ( p_cAux, iTam + 1, VERS_PAT_4, iVersion, iSubversion, iRevision, iCorreccion );
			}
			else if ( iCampos == 3 )
			{
				snprintf ( p_cAux, iTam + 1, VERS_PAT_3, iVersion, iSubversion, iRevision );
			}
			else if ( iCampos == 2 )
			{
				snprintf ( p_cAux, iTam + 1, VERS_PAT_2, iVersion, iSubversion );
			}
			else
			{
				snprintf ( p_cAux, iTam + 1, VERS_PAT_1, iVersion );
			}
			p_cRes = CadDuplicar ( p_cAux );
			MemLiberar ( (void **) &p_cAux );
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








