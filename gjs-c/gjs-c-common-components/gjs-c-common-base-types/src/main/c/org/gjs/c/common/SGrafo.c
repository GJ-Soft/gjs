
#include "SGrafo.h"



#include "TiposBasicosConfig.h"




static void SGrfInicializarAristas ( SGrafo  * p_grfObj );
static void SGrfInicializar ( SGrafo  * p_grfObj );
static int SGrfAltaNodo ( SGrafo  * p_grfObj, SNodoGrafo * p_nodgObj );
static int SGrfIndiceNodo ( SGrafo  * p_grfObj, SNodoGrafo * p_nodgObj );




SGrafo * SGrfCrear ( int iMaxNodos, int iMaxAristasNodo )
{
	SGrafo * p_grfObj;

	if ( ( iMaxNodos > 0 ) && ( iMaxNodos <= GRAF_MAX_NODOS ) && ( iMaxAristasNodo > 0 ) && ( iMaxAristasNodo < GRAF_MAX_ARISTAS_NODO ) )
	{
		p_grfObj = (SGrafo *) MemReservar ( sizeof ( SGrafo ) );
		if ( ES_VALIDO (  p_grfObj ) )
		{
			p_grfObj->iMaxNodos = iMaxNodos;
			p_grfObj->iMaxAristasNodo = iMaxAristasNodo;
			SGrfInicializar ( p_grfObj );
		}
	}
	else
	{
		 p_grfObj = NULL;
	}
	return (  p_grfObj );
}

void SGrfDestruir ( SGrafo ** p_p_grfObj )
{
	SGrafo * p_grfObj;

	if ( ES_VALIDO ( p_p_grfObj ) )
	{
		p_grfObj = *p_p_grfObj;
		if ( ES_VALIDO ( p_grfObj ) )
		{
			SGrfVaciar ( p_grfObj );
			MemLiberar ( ( void **) p_p_grfObj );
		}
	}
}

SNodoGrafo * SGrfInicial ( SGrafo * p_grfObj )
{
	SNodoGrafo * p_nodgRes;

	if ( ES_VALIDO ( p_grfObj ) )
	{
		p_nodgRes = p_grfObj->p_nodgInicial;
	}
	else
	{
		p_nodgRes = NULL;
	}
	return ( p_nodgRes );
}

int SGrfEstInicial ( SGrafo * p_grfObj, SNodoGrafo * p_nodgObj )
{
	int	iNodo;
	int iRes;

	if ( ES_VALIDO ( p_grfObj ) )
	{
		p_grfObj->p_nodgInicial = p_nodgObj;
		if ( ES_VALIDO ( p_grfObj->p_nodgInicial ) )
		{
			iRes = 1;
			iNodo = SGrfIndiceNodo ( p_grfObj, p_nodgObj );
			if ( iNodo < 0 )
			{
				if ( SGrfAltaNodo ( p_grfObj, p_nodgObj ) == 0 )
				{
					iRes = 0;
				}
			}
			if ( iRes == 1 )
			{
				p_grfObj->p_nodgInicial = p_nodgObj;
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

int SGrfEstaVacio ( SGrafo * p_grfObj )
{
	int iRes;

	if ( ES_VALIDO ( p_grfObj ) )
	{
		if ( ES_NULO ( p_grfObj->p_nodgInicial ) )
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
		iRes = 1;
	}
	return ( iRes );
}

int SGrfNumNodos ( SGrafo * p_grfObj )
{
	int iRes;

	if ( ES_VALIDO ( p_grfObj ) )
	{
		if ( ES_VALIDO ( p_grfObj->p_nodgInicial ) )
		{
			iRes = p_grfObj->iNumNodos;
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

int SGrfVaciar ( SGrafo * p_grfObj )
{
	int	iRes;
	int	iNodo;

	if ( ES_VALIDO ( p_grfObj ) )
	{
		/* Se destruye cada nodo de la lista. Cada nodo libera sus aristas de salida
		   ( de las que es dueno ) y limpia sus referencias de entrada sin liberarlas,
		   de modo que cada arista se libera exactamente una vez y no hay
		   use-after-free aunque el grafo tenga ciclos o nodos compartidos. */
		for ( iNodo = 0; iNodo < p_grfObj->iNumNodos; iNodo = iNodo + 1 )
		{
			SNodGrfDestruir ( &(p_grfObj->p_p_nodgLista [ iNodo ]) );
		}
		p_grfObj->iNumNodos = 0;
		p_grfObj->p_nodgInicial = NULL;
		p_grfObj->p_nodgActual = NULL;
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

SNodoGrafo * SGrfCrearNodo ( SGrafo * p_grfObj )
{
	SNodoGrafo * p_nodgRes;

	if ( ES_VALIDO ( p_grfObj ) )
	{
		p_nodgRes = SNodGrfCrear ( p_grfObj->iMaxAristasNodo );
	}
	else
	{
		p_nodgRes = NULL;
	}
	return ( p_nodgRes );
}

SNodoGrafo * SGrfActual ( SGrafo * p_grfObj )
{
	SNodoGrafo * p_nodgRes;

	if ( ES_VALIDO ( p_grfObj ) )
	{
		p_nodgRes = p_grfObj->p_nodgActual;
	}
	else
	{
		p_nodgRes = NULL;
	}
	return ( p_nodgRes );
}

int	SGrfDato ( SGrafo * p_grfObj )
{
	int iRes;

	if ( ES_VALIDO ( p_grfObj ) )
	{
		if ( ES_VALIDO ( p_grfObj->p_nodgActual ) )
		{
			iRes = SNodGrfDato ( p_grfObj->p_nodgActual );
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

int SGrfNumEntradas ( SGrafo * p_grfObj )
{
	int iRes;

	if ( ES_VALIDO ( p_grfObj ) )
	{
		if ( ES_VALIDO ( p_grfObj->p_nodgActual ) )
		{
			iRes = SNodGrfNumAristasEntrada ( p_grfObj->p_nodgActual );
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

int SGrfNumSalidas ( SGrafo * p_grfObj )
{
	int iRes;

	if ( ES_VALIDO ( p_grfObj ) )
	{
		if ( ES_VALIDO ( p_grfObj->p_nodgActual ) )
		{
			iRes = SNodGrfNumAristasSalida ( p_grfObj->p_nodgActual );
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

int SGrfEsEntradaValida ( SGrafo * p_grfObj, int iArista )
{
	int iRes;

	if ( ES_VALIDO ( p_grfObj ) )
	{
		if ( ES_VALIDO ( p_grfObj->p_nodgActual ) )
		{
			iRes = SNodGrfAristaEntradaEsValida (  p_grfObj->p_nodgActual, iArista );
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

int SGrfEsSalidaValida ( SGrafo * p_grfObj, int iArista )
{
	int iRes;

	if ( ES_VALIDO ( p_grfObj ) )
	{
		if ( ES_VALIDO ( p_grfObj->p_nodgActual ) )
		{
			iRes = SNodGrfAristaSalidaEsValida ( p_grfObj->p_nodgActual, iArista );
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

int SGrfTieneEntradasPorRecorrer ( SGrafo * p_grfObj )
{
	int iRes;

	if ( ES_VALIDO ( p_grfObj ) )
	{
		if ( ES_VALIDO ( p_grfObj->p_nodgActual ) )
		{
			iRes = SNodGrfTieneAristasEntradaPorRecorrer ( p_grfObj->p_nodgActual );
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

int SGrfTieneSalidasPorRecorrer ( SGrafo * p_grfObj )
{
	int iRes;

	if ( ES_VALIDO ( p_grfObj ) )
	{
		if ( ES_VALIDO ( p_grfObj->p_nodgActual ) )
		{
			iRes = SNodGrfTieneAristasSalidaPorRecorrer ( p_grfObj->p_nodgActual );
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

int SGrfTieneEntradasRecorridas ( SGrafo * p_grfObj )
{
	int iRes;

	if ( ES_VALIDO ( p_grfObj ) )
	{
		if ( ES_VALIDO ( p_grfObj->p_nodgActual ) )
		{
			iRes = SNodGrfTieneAristasEntradaRecorridas ( p_grfObj->p_nodgActual );
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

int SGrfTieneSalidasRecorridas ( SGrafo * p_grfObj )
{
	int iRes;

	if ( ES_VALIDO ( p_grfObj ) )
	{
		if ( ES_VALIDO ( p_grfObj->p_nodgActual ) )
		{
			iRes = SNodGrfTieneAristasSalidaRecorridas ( p_grfObj->p_nodgActual );
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

void SGrfMoverAInicial ( SGrafo * p_grfObj )
{
	if ( ES_VALIDO ( p_grfObj ) )
	{
		SGrfInicializarAristas ( p_grfObj );
		p_grfObj->p_nodgActual = p_grfObj->p_nodgInicial;
	}
}

void SGrfMoverAEntrada ( SGrafo * p_grfObj, int iArista )
{
	SAristaGrafo *	p_arigObj;

	if ( ES_VALIDO ( p_grfObj ) )
	{
		if ( ES_VALIDO ( p_grfObj->p_nodgActual ) )
		{
			p_arigObj = SNodGrfAristaEntrada ( p_grfObj->p_nodgActual, iArista );
			if ( ES_VALIDO ( p_arigObj ) )
			{
				SAriGrfMarcarComoRecorrida ( p_arigObj );
				p_grfObj->p_nodgActual = SAriGrfNodoInicial ( p_arigObj );
			}
			else
			{
				p_grfObj->p_nodgActual = NULL;
			}
		}
	}
}

void SGrfMoverASalida ( SGrafo * p_grfObj, int iArista )
{
	SAristaGrafo *	p_arigObj;

	if ( ES_VALIDO ( p_grfObj ) )
	{
		if ( ES_VALIDO ( p_grfObj->p_nodgActual ) )
		{
			p_arigObj = SNodGrfAristaSalida ( p_grfObj->p_nodgActual, iArista );
			if ( ES_VALIDO ( p_arigObj ) )
			{
				SAriGrfMarcarComoRecorrida ( p_arigObj );
				p_grfObj->p_nodgActual = SAriGrfNodoFinal ( p_arigObj );
			}
			else
			{
				p_grfObj->p_nodgActual = NULL;
			}
		}
	}
}

int SGrfMoverAPrimeraEntrada ( SGrafo * p_grfObj )
{
	int				iRes;
	SAristaGrafo *	p_arigObj;

	if ( ES_VALIDO ( p_grfObj ) )
	{
		if ( ES_VALIDO ( p_grfObj->p_nodgActual ) )
		{
			p_arigObj = SNodGrfAristaEntrada ( p_grfObj->p_nodgActual, 0 );
			if ( ES_VALIDO ( p_arigObj ) )
			{
				SAriGrfMarcarComoRecorrida ( p_arigObj );
				p_grfObj->p_nodgActual = SAriGrfNodoInicial ( p_arigObj );
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

int SGrfMoverAPrimeraSalida ( SGrafo * p_grfObj )
{
	int				iRes;
	SAristaGrafo *	p_arigObj;

	if ( ES_VALIDO ( p_grfObj ) )
	{
		if ( ES_VALIDO ( p_grfObj->p_nodgActual ) )
		{
			p_arigObj = SNodGrfAristaSalida ( p_grfObj->p_nodgActual, 0 );
			if ( ES_VALIDO ( p_arigObj ) )
			{
				SAriGrfMarcarComoRecorrida ( p_arigObj );
				p_grfObj->p_nodgActual = SAriGrfNodoFinal ( p_arigObj );
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

int SGrfMoverAUltimaEntrada ( SGrafo * p_grfObj )
{
	int				iRes;
	SAristaGrafo *	p_arigObj;

	if ( ES_VALIDO ( p_grfObj ) )
	{
		if ( ES_VALIDO ( p_grfObj->p_nodgActual ) )
		{
			p_arigObj = SNodGrfAristaEntrada ( p_grfObj->p_nodgActual, SNodGrfNumAristasEntrada ( p_grfObj->p_nodgActual ) - 1 );
			if ( ES_VALIDO ( p_arigObj ) )
			{
				p_grfObj->p_nodgActual = SAriGrfNodoInicial ( p_arigObj );
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

int SGrfMoverAUltimaSalida ( SGrafo * p_grfObj )
{
	int				iRes;
	SAristaGrafo *	p_arigObj;

	if ( ES_VALIDO ( p_grfObj ) )
	{
		if ( ES_VALIDO ( p_grfObj->p_nodgActual ) )
		{
			p_arigObj =SNodGrfAristaSalida ( p_grfObj->p_nodgActual, SNodGrfNumAristasSalida ( p_grfObj->p_nodgActual ) - 1 );
			if ( ES_VALIDO ( p_arigObj ) )
			{
				p_grfObj->p_nodgActual = SAriGrfNodoFinal ( p_arigObj );
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

int SGrfMoverAPrimeraEntradaPorRecorrer ( SGrafo * p_grfObj )
{
	int				iRes;
	int				iArista;
	SAristaGrafo *	p_arigObj;

	if ( ES_VALIDO ( p_grfObj ) )
	{
		if ( ES_VALIDO ( p_grfObj->p_nodgActual ) )
		{
			iArista = SNodGrfPrimeraAristaEntradaPorRecorrer ( p_grfObj->p_nodgActual );
			p_arigObj = SNodGrfAristaEntrada ( p_grfObj->p_nodgActual, iArista );
			if ( ES_VALIDO ( p_arigObj ) )
			{
				SAriGrfMarcarComoRecorrida ( p_arigObj );
				p_grfObj->p_nodgActual = SAriGrfNodoInicial ( p_arigObj );
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

int SGrfMoverAPrimeraSalidaPorRecorrer ( SGrafo * p_grfObj )
{
	int				iRes;
	int				iArista;
	SAristaGrafo *	p_arigObj;

	if ( ES_VALIDO ( p_grfObj ) )
	{
		if ( ES_VALIDO ( p_grfObj->p_nodgActual ) )
		{
			iArista = SNodGrfPrimeraAristaSalidaPorRecorrer ( p_grfObj->p_nodgActual );
			p_arigObj = SNodGrfAristaSalida ( p_grfObj->p_nodgActual, iArista );
			if ( ES_VALIDO ( p_arigObj ) )
			{
				SAriGrfMarcarComoRecorrida ( p_arigObj );
				p_grfObj->p_nodgActual = SAriGrfNodoFinal ( p_arigObj );
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

int SGrfMoverAUltimaEntradaRecorrida ( SGrafo * p_grfObj )
{
	int				iRes;
	int				iArista;
	SAristaGrafo *	p_arigObj;

	if ( ES_VALIDO ( p_grfObj ) )
	{
		if ( ES_VALIDO ( p_grfObj->p_nodgActual ) )
		{
			iArista = SNodGrfUltimaAristaEntradaRecorrida ( p_grfObj->p_nodgActual );
			p_arigObj = SNodGrfAristaEntrada ( p_grfObj->p_nodgActual, iArista );
			if ( ES_VALIDO ( p_arigObj ) )
			{
				p_grfObj->p_nodgActual = SAriGrfNodoInicial ( p_arigObj );
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

int SGrfMoverAUltimaSalidaRecorrida ( SGrafo * p_grfObj )
{
	int				iRes;
	int				iArista;
	SAristaGrafo *	p_arigObj;

	if ( ES_VALIDO ( p_grfObj ) )
	{
		if ( ES_VALIDO ( p_grfObj->p_nodgActual ) )
		{
			iArista = SNodGrfUltimaAristaSalidaRecorrida ( p_grfObj->p_nodgActual );
			p_arigObj = SNodGrfAristaSalida ( p_grfObj->p_nodgActual, iArista );
			if ( ES_VALIDO ( p_arigObj ) )
			{
				p_grfObj->p_nodgActual = SAriGrfNodoFinal ( p_arigObj );
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

int SGrfMoverANodo ( SGrafo * p_grfObj, int iIndice )
{
	int				iRes;
	SNodoGrafo *	p_nodgObj;

	if ( ES_VALIDO ( p_grfObj ) )
	{
		p_nodgObj = SGrfNodo ( p_grfObj, iIndice );
		if ( ES_VALIDO ( p_nodgObj ) )
		{
			p_grfObj->p_nodgActual = p_nodgObj;
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

void SGrfDesposicionar ( SGrafo * p_grfObj )
{
	if ( ES_VALIDO ( p_grfObj ) )
	{
		p_grfObj->p_nodgActual = NULL;
	}
}

int	SGrfEstaPosicionado ( SGrafo * p_grfObj )
{
	int iRes;

	if ( ES_VALIDO ( p_grfObj ) )
	{
		if ( ES_VALIDO ( p_grfObj->p_nodgActual ) )
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

int	SGrfEstaEnInicial ( SGrafo * p_grfObj )
{
	int iRes;

	if ( ES_VALIDO ( p_grfObj ) )
	{
		if ( ES_VALIDO ( p_grfObj->p_nodgActual ) )
		{
			if ( p_grfObj->p_nodgActual == p_grfObj->p_nodgInicial )
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

int SGrfConectar ( SGrafo * p_grfObj, SAristaGrafo * p_arigObj )
{
	int iRes;

	if ( ES_VALIDO ( p_grfObj ) )
	{
		if ( ES_VALIDO ( p_arigObj ) )
		{
			iRes = SGrfConectarConNodo ( p_grfObj, p_arigObj, SAriGrfNodoFinal ( p_arigObj ) );
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

int SGrfConectarConNodo ( SGrafo * p_grfObj, SAristaGrafo * p_arigObj, SNodoGrafo * p_nodgObj )
{
	int	iNodo;
	int iRes;

	if ( ES_VALIDO ( p_grfObj ) )
	{
		if ( ES_VALIDO ( p_grfObj->p_nodgActual ) && ES_VALIDO ( p_arigObj ) )
		{
			iRes = 1;
			iNodo = SGrfIndiceNodo ( p_grfObj, p_nodgObj );
			if ( iNodo < 0 )
			{
				if ( SGrfAltaNodo ( p_grfObj, p_nodgObj ) == 0 )
				{
					iRes = 0;
				}
			}

			if ( iRes == 1 )
			{
				SAriGrfConectarNodoInicial ( p_arigObj, p_grfObj->p_nodgActual );
				SAriGrfConectarNodoFinal ( p_arigObj, p_nodgObj );
				if ( SNodGrfConectarAristaSalida ( p_grfObj->p_nodgActual, p_arigObj ) == 1 )
				{
					if ( ES_VALIDO ( p_nodgObj ) )
					{
						if ( SNodGrfConectarAristaEntrada ( p_nodgObj, p_arigObj ) == 1 )
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
						iRes = 1;
					}
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
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SGrfConectarANodo ( SGrafo * p_grfObj, SAristaGrafo * p_arigObj, int iIdNodo )
{
	SNodoGrafo *	p_nodgObj;
	int				iRes;

	if ( ES_VALIDO ( p_grfObj ) )
	{
		p_nodgObj = SGrfNodo ( p_grfObj, iIdNodo );
		if ( ES_VALIDO ( p_nodgObj ) )
		{
			iRes = SGrfConectarConNodo ( p_grfObj, p_arigObj, p_nodgObj );
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

int SGrfConectarANodoInicial ( SGrafo * p_grfObj, SAristaGrafo * p_arigObj )
{
	int iRes;

	if ( ES_VALIDO ( p_grfObj ) )
	{
		iRes = SGrfConectarConNodo ( p_grfObj, p_arigObj, p_grfObj->p_nodgInicial );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

void SGrfInicializarAristas ( SGrafo * p_grfObj )
{
	if ( ES_VALIDO ( p_grfObj ) )
	{
		if ( ES_VALIDO ( p_grfObj->p_nodgInicial ) )
		{
			SNodGrfInicializarAristasSalida ( p_grfObj->p_nodgInicial );
		}
	}
}

static void SGrfInicializar ( SGrafo * p_grfObj )
{
	if ( ES_VALIDO ( p_grfObj ) )
	{
		MemLiberar ( (void **) &(p_grfObj->p_p_nodgLista) );
		p_grfObj->p_p_nodgLista = (SNodoGrafo **) MemReservarVector ( p_grfObj->iMaxNodos, sizeof ( SNodoGrafo * ) );
		p_grfObj->p_nodgInicial = NULL;
		p_grfObj->p_nodgActual = NULL;
		p_grfObj->iNumNodos = 0;
	}
}

static int SGrfAltaNodo ( SGrafo * p_grfObj, SNodoGrafo * p_nodgObj )
{
	int iRes;

	if ( ES_VALIDO ( p_grfObj ) )
	{
		if ( ES_VALIDO ( p_nodgObj ) )
		{
			if ( p_grfObj->iNumNodos < GRAF_MAX_NODOS )
			{
				SNodGrfEstablecerId ( p_nodgObj, p_grfObj->iNumNodos );
				p_grfObj->p_p_nodgLista [ p_grfObj->iNumNodos ] = p_nodgObj;
				p_grfObj->iNumNodos = p_grfObj->iNumNodos + 1;
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

static int SGrfIndiceNodo ( SGrafo * p_grfObj, SNodoGrafo * p_nodgObj )
{
	int iRes;
	int iNodo;

	if ( ES_VALIDO ( p_grfObj ) )
	{
		if ( ES_VALIDO ( p_nodgObj ) )
		{
			if ( ( SNodGrfId ( p_nodgObj ) >= 0 ) && ( SNodGrfId ( p_nodgObj ) < p_grfObj->iNumNodos ) )
			{
				iRes = SNodGrfId ( p_nodgObj );
			}
			else
			{
				iRes = -1;
				iNodo = 0;
				while ( ( iNodo < p_grfObj->iNumNodos ) && ( iRes < 0 ) )
				{
					if ( p_grfObj->p_p_nodgLista [ iNodo ] == p_nodgObj )
					{
						iRes = iNodo;
						SNodGrfEstablecerId ( p_nodgObj, iNodo );
					}
					iNodo = iNodo + 1;
				}
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

SNodoGrafo * SGrfNodo ( SGrafo * p_grfObj, int iIndice )
{
	SNodoGrafo * p_nodgRes;

	if ( ES_VALIDO ( p_grfObj ) )
	{
		if ( ( iIndice >= 0 ) && ( iIndice < p_grfObj->iNumNodos ) )
		{
			p_nodgRes = p_grfObj->p_p_nodgLista [ iIndice ];
		}
		else
		{
			p_nodgRes = NULL;
		}
	}
	else
	{
		p_nodgRes = NULL;
	}
	return ( p_nodgRes );
}

