/******************************************************************************/
/*                                Errores.cpp                                 */
/*----------------------------------------------------------------------------*/
/* Librería:  GBase                                                           */
/* Versión:   1.0.0                                                           */
/* Fecha:     28/06/2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Fichero de código fuente que contiene la implementación de las rutinas     */
/* de gestión del subsistema general de manejo de errores.                    */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#include "Errores.h"

#include "BaseConfig.h"

#include "Memoria.h"
#include "CadenasBase.h"
#include "FormatoCadena.h"
#include "BaseErrores.h"



/* Descripción de los errores : */
#define ERR_TXT_OK							"No se ha producido ningun error."
#define ERR_TXT_MEMORIA_INVALIDA			"Direccion de memoria invalida."
#define ERR_TXT_MEMORIA_INSUFICIENTE		"Memoria insuficiente para realizar la operacion."
#define ERR_TXT_MEMORIA_PROCESO				"La memoria (heap) del proceso esta corrompida o es invalida."
#define ERR_TXT_PARAMETROS					"Uno o mas parametros son nulos, o no son validos."
#define ERR_TXT_POSICION_INVALIDA			"La posicion indicada es invalida"
#define ERR_TXT_ESTRUCTURA_INVALIDA			"La estructura es invalida."
#define ERR_TXT_CONVERSION_IMPOSIBLE		"No se puede realizar la conversion del valor indicado."

#define ERR_TXT_GENERAL_OPERATIVO			"Se ha producido un error al realizar la operacion."





/* Tipos de datos: */
/*
typedef struct
{
	int				iCodigo;
	const char *	p_cDescripcion;
	int				iGrave;
	void *			p_vSig;
} SInfoError;
*/


/* Variables globales: */
/*
static SInfoError * g_p_inferrLista = NULL;
static SInfoError * g_p_inferrActual = NULL;

static int			g_iGInicializado = 0;
*/

static int			g_iGError = ERR_OK;
static const char *	g_p_cGErrDescripcion = NULL;
static const char *	g_p_cGErrModulo = NULL;
static unsigned int g_uiGErrLinea = 0;





//static void ErrInicializar ();
//static void InfErrLimpiar ();
static const char * _ErrDescripcion ( int iCod );
static int _ErrPredefinido ( int iCod );




/*
int InfErrDarDeAlta ( int iCod, const char * p_cDesc, int iGrave )
{
	SInfoError *	p_inferrObj;
	SInfoError *	p_inferrAnt;
	SInfoError *	p_inferrNuevo;
	int				iAlta;
	int				iExiste;
	int				iRes;

	if ( g_iGInicializado == 0 )
	{
		ErrInicializar ();
	}

	if ( ES_VALIDO ( p_cDesc ) )
	{
		if ( ES_VALIDO ( g_p_inferrLista ) )
		{
			iAlta = 0;
			iExiste = 0;
			p_inferrAnt = NULL;
			p_inferrObj = g_p_inferrLista;
			while ( ( iAlta == 0 ) && ( iExiste == 0 ) )
			{
				if ( p_inferrObj->iCodigo < iCod )
				{
					iAlta = 1;
				}
				else if ( p_inferrObj->iCodigo == iCod )
				{
					iExiste = 1;
				}
				else if ( ES_VALIDO ( p_inferrObj->p_vSig ) )
				{
					p_inferrAnt = p_inferrObj;
					p_inferrObj = (SInfoError *) p_inferrObj->p_vSig;
				}
				else
				{
					iAlta = 2;
				}
			}

			if ( iExiste == 0 )
			{
				p_inferrNuevo = (SInfoError *) MemReservar ( sizeof ( SInfoError ) );

				if ( ES_VALIDO ( p_inferrNuevo ) )
				{
					p_inferrNuevo->iCodigo = iCod;
					p_inferrNuevo->p_cDescripcion = CadDuplicar ( p_cDesc );
					p_inferrNuevo->iGrave = iGrave;

					if ( iAlta == 1 )
					{
						p_inferrNuevo->p_vSig = p_inferrObj;
						if ( ES_VALIDO ( p_inferrAnt ) )
						{
							p_inferrAnt->p_vSig = (void *) p_inferrNuevo;
						}
						else
						{
							g_p_inferrLista = p_inferrNuevo;
						}
					}
					else // ( iAlta == 2 )
					{
						p_inferrNuevo->p_vSig = p_inferrObj->p_vSig;
						p_inferrObj->p_vSig = (void *) p_inferrNuevo;
					}

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
			g_p_inferrLista = (SInfoError *) MemReservar ( sizeof ( SInfoError ) );

			if ( ES_VALIDO ( g_p_inferrLista ) )
			{
				g_p_inferrLista->iCodigo = iCod;
				g_p_inferrLista->p_cDescripcion = CadDuplicar ( p_cDesc );
				g_p_inferrLista->iGrave = iGrave;
				g_p_inferrLista->p_vSig = NULL;

				iRes = 1;
			}
			else
			{
				iRes = 0;
			}
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int InfErrExiste ( int iCod )
{
	SInfoError *	p_inferrObj;
	int				iExiste;
	int				iFin;

	if ( g_iGInicializado == 0 )
	{
		ErrInicializar ();
	}

	iExiste = 0;
	iFin = 0;

	if ( ES_VALIDO ( g_p_inferrActual ) )
	{
		if ( g_p_inferrActual->iCodigo <= iCod )
		{
			p_inferrObj = g_p_inferrActual;
		}
		else
		{
			p_inferrObj = g_p_inferrLista;
		}
	}
	else
	{
		p_inferrObj = g_p_inferrLista;
	}

	while ( ( iFin == 0 ) && ( iExiste == 0 ) )
	{
		if ( p_inferrObj->iCodigo > iCod )
		{
			iFin = 1;
		}
		else if ( p_inferrObj->iCodigo == iCod )
		{
			iExiste = 1;
			g_p_inferrActual = p_inferrObj;
		}
		else if ( ES_VALIDO ( p_inferrObj->p_vSig ) )
		{
			p_inferrObj = (SInfoError *) p_inferrObj->p_vSig;
		}
		else
		{
			iFin = 1;
		}
	}
	return ( iExiste );
}

const char * InfErrDescripcion ( int iCod )
{
	SInfoError *	p_inferrObj;
	int				iExiste;
	int				iFin;
	const char *	p_cRes;

	if ( g_iGInicializado == 0 )
	{
		ErrInicializar ();
	}

	iExiste = 0;
	iFin = 0;
	p_cRes = NULL;
	if ( ES_VALIDO ( g_p_inferrActual ) )
	{
		if ( g_p_inferrActual->iCodigo <= iCod )
		{
			p_inferrObj = g_p_inferrActual;
		}
		else
		{
			p_inferrObj = g_p_inferrLista;
		}
	}
	else
	{
		p_inferrObj = g_p_inferrLista;
	}

	if ( ES_VALIDO ( p_inferrObj ) )
	{
		while ( ( iFin == 0 ) && ( iExiste == 0 ) )
		{
			if ( p_inferrObj->iCodigo > iCod )
			{
				iFin = 1;
			}
			else if ( p_inferrObj->iCodigo == iCod )
			{
				p_cRes = p_inferrObj->p_cDescripcion;
				g_p_inferrActual = p_inferrObj;
				iExiste = 1;
			}
			else if ( ES_VALIDO ( p_inferrObj->p_vSig ) )
			{
				p_inferrObj = (SInfoError *) p_inferrObj->p_vSig;
			}
			else
			{
				iFin = 1;
			}
		}
	}
	return ( p_cRes );
}

int InfErrEsGrave ( int iCod )
{
	SInfoError *	p_inferrObj;
	int				iExiste;
	int				iFin;
	int				iRes;

	if ( g_iGInicializado == 0 )
	{
		ErrInicializar ();
	}

	iExiste = 0;
	iFin = 0;
	iRes = 0;
	if ( ES_VALIDO ( g_p_inferrActual ) )
	{
		if ( g_p_inferrActual->iCodigo <= iCod )
		{
			p_inferrObj = g_p_inferrActual;
		}
		else
		{
			p_inferrObj = g_p_inferrLista;
		}
	}
	else
	{
		p_inferrObj = g_p_inferrLista;
	}

	while ( ( iFin == 0 ) && ( iExiste == 0 ) )
	{
		if ( p_inferrObj->iCodigo > iCod )
		{
			iFin = 1;
		}
		else if ( p_inferrObj->iCodigo == iCod )
		{
			iRes = p_inferrObj->iGrave;
			g_p_inferrActual = p_inferrObj;
			iExiste = 1;
		}
		else if ( ES_VALIDO ( p_inferrObj->p_vSig ) )
		{
			p_inferrObj = (SInfoError *) p_inferrObj->p_vSig;
		}
		else
		{
			iFin = 1;
		}
	}
	return ( iRes );
}
*/

void _ErrEstablecer ( const char * p_cModulo, int iLinea, int iCodigo, const char * p_cDescripcion )
{
	//if ( g_iGInicializado == 0 )
	//{
	//	ErrInicializar ();
	//}
	if ( _ErrPredefinido ( iCodigo ) == 1 )
	{
		g_iGError = iCodigo;
		MemLiberar ( (void **) &g_p_cGErrDescripcion );
		g_p_cGErrDescripcion = _ErrDescripcion ( iCodigo );
		MemLiberar ( (void **) &g_p_cGErrModulo );
		g_p_cGErrModulo = CadDuplicar ( p_cModulo );
		g_uiGErrLinea = iLinea;
	}
	else
	{
		g_iGError = iCodigo;
		MemLiberar ( (void **) &g_p_cGErrDescripcion );
		g_p_cGErrDescripcion = CadDuplicar ( p_cDescripcion );
		MemLiberar ( (void **) &g_p_cGErrModulo );
		g_p_cGErrModulo = CadDuplicar ( p_cModulo );
		g_uiGErrLinea = iLinea;
	}
}

void ErrEstablecer ( const char * p_cModulo, int iLinea,int iCodigo )
{
    _ErrEstablecer ( p_cModulo, iLinea, iCodigo, NULL );
}

void ErrEstablecerConFormato ( const char * p_cModulo, int iLinea, int iCodigo, const char * p_cDescripcion, ... )
{
	char *		p_cValor;
	va_list		valArgumentos;

	if ( ES_VALIDO ( p_cDescripcion ) )
	{
        p_cValor = CadCrear ( ERR_MAX_TAM_MSJ );
        if ( ES_VALIDO ( p_cValor ) )
        {
            va_start ( valArgumentos, p_cDescripcion );
            if ( FrmCadena ( p_cValor, p_cDescripcion, valArgumentos, ERR_MAX_TAM_MSJ ) == 1 )
            {
                _ErrEstablecer ( p_cModulo, iLinea, iCodigo, p_cValor );
            }

            MemLiberar ( (void **) &p_cValor );
            va_end ( valArgumentos );
        }
	}
	else {
        _ErrEstablecer ( p_cModulo, iLinea, iCodigo, NULL );
	}
}

int ErrHayError ()
{
	int iRes;

	if ( g_iGError != ERR_OK )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int ErrCodigo ()
{
	return ( g_iGError );
}

const char * ErrDescripcion ()
{
	const char * p_cRes;

	p_cRes = g_p_cGErrDescripcion; //InfErrDescripcion ( g_iGError );
	return ( p_cRes );
}

const char * ErrModulo ()
{
	return ( g_p_cGErrModulo );
}

unsigned int ErrLinea ()
{
	return ( g_uiGErrLinea );
}

void ErrLimpiar ()
{
	MemLiberar ( (void **) &g_p_cGErrDescripcion );
	MemLiberar ( (void **) &g_p_cGErrModulo );
	g_iGError = ERR_OK;
	g_uiGErrLinea = 0;
}

const char * ErrMensaje ()
{
	const char * p_cDesc;
	char *		 p_cRes = NULL;

	if ( g_iGError != ERR_OK )
	{
		p_cRes = CadCrear ( ERR_MAX_TAM_MSJ );
		if ( ES_VALIDO ( p_cRes ) )
		{
			p_cDesc = g_p_cGErrDescripcion; //InfErrDescripcion ( g_iGError );
			snprintf ( p_cRes, ERR_MAX_TAM_MSJ + 1, "Error %d - %s (%s:%u)", g_iGError,
					   CadValorSeguro ( p_cDesc ), CadValorSeguro ( g_p_cGErrModulo ), g_uiGErrLinea );
		}
	}
	return ( (const char *) p_cRes );
}

void ErrImprimir ()
{
	const char * p_cMsj;

	p_cMsj = ErrMensaje ();
	if ( ES_VALIDO ( p_cMsj ) )
	{
		printf ( "%s\n", p_cMsj );
		MemLiberar ( (void **) &p_cMsj );
	}
}

static const char * _ErrDescripcion ( int iCod )
{
	const char * p_cRes;

	if ( iCod == ERR_OK )
	{
		p_cRes = CadDuplicar ( ERR_TXT_OK );
	}
	else if ( iCod == ERR_MEMORIA_INVALIDA )
	{
		p_cRes = CadDuplicar ( ERR_TXT_MEMORIA_INVALIDA );
	}
	else if ( iCod == ERR_MEMORIA_INSUFICIENTE )
	{
		p_cRes = CadDuplicar ( ERR_TXT_MEMORIA_INSUFICIENTE );
	}
	else if ( iCod == ERR_MEMORIA_PROCESO )
	{
		p_cRes = CadDuplicar ( ERR_TXT_MEMORIA_PROCESO );
	}
	else if ( iCod == ERR_PARAMETROS )
	{
		p_cRes = CadDuplicar ( ERR_TXT_PARAMETROS );
	}
	else if ( iCod == ERR_POSICION_INVALIDA )
	{
		p_cRes = CadDuplicar ( ERR_TXT_POSICION_INVALIDA );
	}
	else if ( iCod == ERR_ESTRUCTURA_INVALIDA )
	{
		p_cRes = CadDuplicar ( ERR_TXT_ESTRUCTURA_INVALIDA );
	}
	else if ( iCod == ERR_CONVERSION_IMPOSIBLE )
	{
		p_cRes = CadDuplicar ( ERR_TXT_CONVERSION_IMPOSIBLE );
	}
	else if ( iCod == ERR_GENERAL_OPERATIVO )
	{
		p_cRes = CadDuplicar ( ERR_TXT_GENERAL_OPERATIVO );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

static int _ErrPredefinido ( int iCod )
{
	int iRes;

	if ( ( iCod == ERR_OK ) ||
		 ( iCod == ERR_MEMORIA_INVALIDA ) ||
		 ( iCod == ERR_MEMORIA_INSUFICIENTE ) ||
		 ( iCod == ERR_MEMORIA_PROCESO ) ||
		 ( iCod == ERR_PARAMETROS ) ||
		 ( iCod == ERR_POSICION_INVALIDA ) ||
		 ( iCod == ERR_ESTRUCTURA_INVALIDA ) ||
		 ( iCod == ERR_CONVERSION_IMPOSIBLE ) ||
		 ( iCod == ERR_GENERAL_OPERATIVO ) )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

/*
static void ErrInicializar ()
{
	InfErrLimpiar ();
	g_iGInicializado = 1;
	InfErrDarDeAlta ( ERR_OK, ERR_TXT_OK, ERR_GRV_OK );
	InfErrDarDeAlta ( ERR_MEMORIA_INVALIDA, ERR_TXT_MEMORIA_INVALIDA, ERR_GRV_MEMORIA_INVALIDA );
	InfErrDarDeAlta ( ERR_MEMORIA_INSUFICIENTE, ERR_TXT_MEMORIA_INSUFICIENTE, ERR_GRV_MEMORIA_INSUFICIENTE );
	InfErrDarDeAlta ( ERR_MEMORIA_PROCESO, ERR_TXT_MEMORIA_PROCESO, ERR_GRV_MEMORIA_PROCESO );
	InfErrDarDeAlta ( ERR_PARAMETROS, ERR_TXT_PARAMETROS, ERR_GRV_PARAMETROS );
}

static void InfErrLimpiar ()
{
	SInfoError * p_inferrObj;

	while ( ES_VALIDO ( g_p_inferrLista ) )
	{
		p_inferrObj = g_p_inferrLista;
		g_p_inferrLista = (SInfoError *) g_p_inferrLista->p_vSig;

		if ( ES_VALIDO ( p_inferrObj->p_cDescripcion ) )
		{
			MemLiberar ( (void **) &(p_inferrObj->p_cDescripcion) );
		}
		MemLiberar ( (void **) &p_inferrObj );
	}
	g_p_inferrActual = NULL;
}
*/





