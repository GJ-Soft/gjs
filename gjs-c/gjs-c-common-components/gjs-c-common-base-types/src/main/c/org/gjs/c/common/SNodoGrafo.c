

#include "SNodoGrafo.h"
#include "SAristaGrafo.h"


#include "TiposBasicosConfig.h"



static void SNodGfrInicializar ( SNodoGrafo * p_nodgObj );



SNodoGrafo * SNodGrfCrear ( int iMaxAristas )
{
	SNodoGrafo * p_nodgObj;

	if ( ( iMaxAristas > 0 ) && ( iMaxAristas <= GRAF_MAX_ARISTAS_NODO ) )
	{
		p_nodgObj = (SNodoGrafo *) MemReservar ( sizeof ( SNodoGrafo ) );
		if ( ES_VALIDO ( p_nodgObj ) )
		{
			p_nodgObj->iMaxAristas = iMaxAristas;
			p_nodgObj->p_p_arigEntrada = NULL;
			p_nodgObj->p_p_arigSalida = NULL;
			SNodGfrInicializar ( p_nodgObj );
		}
	}
	else
	{
		p_nodgObj = NULL;
	}
	return ( p_nodgObj );
}

void SNodGrfDestruir ( SNodoGrafo ** p_p_nodgObj )
{
	SNodoGrafo * p_nodgObj;

	if ( ES_VALIDO ( p_p_nodgObj ) )
	{
		p_nodgObj = *p_p_nodgObj;
		if ( ES_VALIDO ( p_nodgObj ) )
		{
			SNodGrfLimpiarAristasEntrada ( p_nodgObj );
			SNodGrfLimpiarAristasSalida ( p_nodgObj, 1 );
			MemLiberar ( (void **) &(p_nodgObj->p_p_arigEntrada) );
			MemLiberar ( (void **) &(p_nodgObj->p_p_arigSalida) );
			MemLiberar ( (void **) p_p_nodgObj );
		}
	}
}

int SNodGrfId ( SNodoGrafo * p_nodgObj )
{
	int iRes;

	if ( ES_VALIDO ( p_nodgObj ) )
	{
		iRes = p_nodgObj->iId;
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

void SNodGrfEstablecerId ( SNodoGrafo * p_nodgObj, int iId )
{
	if ( ES_VALIDO ( p_nodgObj ) )
	{
		p_nodgObj->iId = iId;
	}
}

int SNodGrfDato ( SNodoGrafo * p_nodgObj )
{
	int iRes;

	if ( ES_VALIDO ( p_nodgObj ) )
	{
		iRes = p_nodgObj->iDato;
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

void SNodGrfEstablecerDato ( SNodoGrafo * p_nodgObj, int iValor )
{
	if ( ES_VALIDO ( p_nodgObj ) )
	{
		p_nodgObj->iDato = iValor;
	}
}

int SNodGrfMaxAristas ( SNodoGrafo * p_nodgObj )
{
	int iRes;

	if ( ES_VALIDO ( p_nodgObj ) )
	{
		iRes = p_nodgObj->iMaxAristas;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SNodGrfNumAristasEntrada ( SNodoGrafo * p_nodgObj )
{
	int iRes;

	if ( ES_VALIDO ( p_nodgObj ) )
	{
		iRes = p_nodgObj->iNumAristasEnt;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SNodGrfNumAristasSalida ( SNodoGrafo * p_nodgObj )
{
	int iRes;

	if ( ES_VALIDO ( p_nodgObj ) )
	{
		iRes = p_nodgObj->iNumAristasSal;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SNodGrfAristaEntradaEsValida ( SNodoGrafo * p_nodgObj, int iArista )
{
	int iRes;

	if ( ES_VALIDO ( p_nodgObj ) )
	{
		if ( ( iArista >= 0 ) && ( iArista < p_nodgObj->iNumAristasEnt ) )
		{
			if ( ES_VALIDO ( p_nodgObj->p_p_arigEntrada [ iArista ] ) )
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

int SNodGrfAristaSalidaEsValida ( SNodoGrafo * p_nodgObj, int iArista )
{
	int iRes;

	if ( ES_VALIDO ( p_nodgObj ) )
	{
		if ( ( iArista >= 0 ) && ( iArista < p_nodgObj->iNumAristasSal ) )
		{
			if ( ES_VALIDO ( p_nodgObj->p_p_arigSalida [ iArista ] ) )
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

SAristaGrafo * SNodGrfAristaEntrada ( SNodoGrafo * p_nodgObj, int iArista )
{
	SAristaGrafo *	p_arigArista;

	if ( ES_VALIDO ( p_nodgObj ) )
	{
		if ( ( iArista >= 0 ) && ( iArista < p_nodgObj->iNumAristasEnt ) )
		{
			p_arigArista = p_nodgObj->p_p_arigEntrada [ iArista ];
		}
		else
		{
			p_arigArista = NULL;
		}
	}
	else
	{
		p_arigArista = NULL;
	}
	return ( p_arigArista );
}

SAristaGrafo * SNodGrfAristaSalida ( SNodoGrafo * p_nodgObj, int iArista )
{
	SAristaGrafo *	p_arigArista;

	if ( ES_VALIDO ( p_nodgObj ) )
	{
		if ( ( iArista >= 0 ) && ( iArista < p_nodgObj->iNumAristasSal ) )
		{
			p_arigArista = p_nodgObj->p_p_arigSalida [ iArista ];
		}
		else
		{
			p_arigArista = NULL;
		}
	}
	else
	{
		p_arigArista = NULL;
	}
	return ( p_arigArista );
}

int SNodGrfTieneAristasEntrada ( SNodoGrafo * p_nodgObj )
{
	int iRes;

	if ( ES_VALIDO ( p_nodgObj ) )
	{
		if ( p_nodgObj->iNumAristasEnt > 0 )
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

int SNodGrfTieneAristasSalida ( SNodoGrafo * p_nodgObj )
{
	int iRes;

	if ( ES_VALIDO ( p_nodgObj ) )
	{
		if ( p_nodgObj->iNumAristasSal > 0 )
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

int SNodGrfTieneAristasEntradaPorRecorrer ( SNodoGrafo * p_nodgObj )
{
	int				iRes;
	int				iArista;
	SAristaGrafo * 	p_arigRes;

	if ( ES_VALIDO ( p_nodgObj ) )
	{
		iRes = 0;
		iArista = 0;
		while ( ( iArista < p_nodgObj->iNumAristasEnt ) && ( iRes == 0 ) )
		{
			p_arigRes = p_nodgObj->p_p_arigEntrada [ iArista ];
			if ( SAriGrfEstaRecorrida ( p_arigRes ) == 0 )
			{
				iRes = 1;
			}
			iArista = iArista + 1;
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SNodGrfTieneAristasSalidaPorRecorrer ( SNodoGrafo * p_nodgObj )
{
	int				iRes;
	int				iArista;
	SAristaGrafo * 	p_arigRes;

	if ( ES_VALIDO ( p_nodgObj ) )
	{
		iRes = 0;
		iArista = 0;
		while ( ( iArista < p_nodgObj->iNumAristasSal ) && ( iRes == 0 ) )
		{
			p_arigRes = p_nodgObj->p_p_arigSalida [ iArista ];
			if ( SAriGrfEstaRecorrida ( p_arigRes ) == 0 )
			{
				iRes = 1;
			}
			iArista = iArista + 1;
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SNodGrfTieneAristasEntradaRecorridas ( SNodoGrafo * p_nodgObj )
{
	int				iRes;
	int				iArista;
	SAristaGrafo * 	p_arigRes;

	if ( ES_VALIDO ( p_nodgObj ) )
	{
		iRes = 0;
		iArista = 0;
		while ( ( iArista < p_nodgObj->iNumAristasEnt ) && ( iRes == 0 ) )
		{
			p_arigRes = p_nodgObj->p_p_arigEntrada [ iArista ];
			if ( SAriGrfEstaRecorrida ( p_arigRes ) == 1 )
			{
				iRes = 1;
			}
			iArista = iArista + 1;
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SNodGrfTieneAristasSalidaRecorridas ( SNodoGrafo * p_nodgObj )
{
	int				iRes;
	int				iArista;
	SAristaGrafo * 	p_arigRes;

	if ( ES_VALIDO ( p_nodgObj ) )
	{
		iRes = 0;
		iArista = 0;
		while ( ( iArista < p_nodgObj->iNumAristasSal ) && ( iRes == 0 ) )
		{
			p_arigRes = p_nodgObj->p_p_arigSalida [ iArista ];
			if ( SAriGrfEstaRecorrida ( p_arigRes ) == 1 )
			{
				iRes = 1;
			}
			iArista = iArista + 1;
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SNodGrfPrimeraAristaEntradaPorRecorrer ( SNodoGrafo * p_nodgObj )
{
	int				iRes;
	int				iArista;
	SAristaGrafo * 	p_arigRes;

	if ( ES_VALIDO ( p_nodgObj ) )
	{
		iRes = -1;
		iArista = 0;
		while ( ( iArista < p_nodgObj->iNumAristasEnt ) && ( iRes < 0 ) )
		{
			p_arigRes = p_nodgObj->p_p_arigEntrada [ iArista ];
			if ( SAriGrfEstaRecorrida ( p_arigRes ) == 0 )
			{
				iRes = iArista;
			}
			iArista = iArista + 1;
		}
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int SNodGrfPrimeraAristaSalidaPorRecorrer ( SNodoGrafo * p_nodgObj )
{
	int				iRes;
	int				iArista;
	SAristaGrafo * 	p_arigRes;

	if ( ES_VALIDO ( p_nodgObj ) )
	{
		iRes = -1;
		iArista = 0;
		while ( ( iArista < p_nodgObj->iNumAristasSal ) && ( iRes < 0 ) )
		{
			p_arigRes = p_nodgObj->p_p_arigSalida [ iArista ];
			if ( SAriGrfEstaRecorrida ( p_arigRes ) == 0 )
			{
				iRes = iArista;
			}
			iArista = iArista + 1;
		}
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int SNodGrfUltimaAristaEntradaRecorrida ( SNodoGrafo * p_nodgObj )
{
	int				iRes;
	int				iArista;
	SAristaGrafo * p_arigRes;

	if ( ES_VALIDO ( p_nodgObj ) )
	{
		iRes = -1;
		iArista = p_nodgObj->iNumAristasEnt - 1;
		while ( ( iArista >= 0 ) && ( iRes < 0 ) )
		{
			p_arigRes = p_nodgObj->p_p_arigEntrada [ iArista ];
			if ( SAriGrfEstaRecorrida ( p_arigRes ) == 1 )
			{
				iRes = iArista;
			}
			iArista = iArista - 1;
		}
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int SNodGrfUltimaAristaSalidaRecorrida ( SNodoGrafo * p_nodgObj )
{
	int				iRes;
	int				iArista;
	SAristaGrafo * p_arigRes;

	if ( ES_VALIDO ( p_nodgObj ) )
	{
		iRes = -1;
		iArista = p_nodgObj->iNumAristasSal;
		while ( ( iArista >= 0 ) && ( iRes < 0 ) )
		{
			p_arigRes = p_nodgObj->p_p_arigSalida [ iArista ];
			if ( SAriGrfEstaRecorrida ( p_arigRes ) == 1 )
			{
				iRes = iArista;
			}
			iArista = iArista - 1;
		}
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int SNodGrfConectarAristaEntrada ( SNodoGrafo * p_nodgObj, SAristaGrafo * p_arigObj )
{
	int	iRes;

	if ( ES_VALIDO ( p_nodgObj ) )
	{
		if ( ( p_nodgObj->iNumAristasEnt < p_nodgObj->iMaxAristas ) && ES_VALIDO ( p_arigObj ) )
		{
			p_nodgObj->iNumAristasEnt = p_nodgObj->iNumAristasEnt + 1;
			p_nodgObj->p_p_arigEntrada [ p_nodgObj->iNumAristasEnt - 1 ] = p_arigObj;
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

int SNodGrfConectarAristaSalida ( SNodoGrafo * p_nodgObj, SAristaGrafo * p_arigObj )
{
	int	iRes;

	if ( ES_VALIDO ( p_nodgObj ) )
	{
		if ( ( p_nodgObj->iNumAristasSal < p_nodgObj->iMaxAristas ) && ES_VALIDO ( p_arigObj ) )
		{
			p_nodgObj->iNumAristasSal = p_nodgObj->iNumAristasSal + 1;
			p_nodgObj->p_p_arigSalida [ p_nodgObj->iNumAristasSal - 1 ] = p_arigObj;
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

SAristaGrafo * SNodGrfDesconectarAristaEntrada ( SNodoGrafo * p_nodgObj, int iArista )
{
	int				iAristaAux;
	SAristaGrafo * 	p_arigRes;

	if ( ES_VALIDO ( p_nodgObj ) )
	{
		if ( ( iArista >= 0 ) && ( iArista < p_nodgObj->iNumAristasEnt ) )
		{
			p_arigRes = p_nodgObj->p_p_arigEntrada [ iArista ];
			p_nodgObj->p_p_arigEntrada [ iArista ] = NULL;

			for ( iAristaAux = iArista + 1; iAristaAux < p_nodgObj->iNumAristasEnt; iAristaAux = iAristaAux + 1 )
			{
				p_nodgObj->p_p_arigEntrada [ iAristaAux - 1 ] = p_nodgObj->p_p_arigEntrada [ iAristaAux ];
			}
			p_nodgObj->p_p_arigEntrada [ p_nodgObj->iNumAristasEnt - 1 ] = NULL;
			p_nodgObj->iNumAristasEnt = p_nodgObj->iNumAristasEnt - 1;
		}
		else
		{
			p_arigRes = NULL;
		}
	}
	else
	{
		p_arigRes = NULL;
	}
	return ( p_arigRes );
}

SAristaGrafo * SNodGrfDesconectarAristaSalida ( SNodoGrafo * p_nodgObj, int iArista )
{
	int				iAristaAux;
	SAristaGrafo * 	p_arigRes;

	if ( ES_VALIDO ( p_nodgObj ) )
	{
		if ( ( iArista >= 0 ) && ( iArista < p_nodgObj->iNumAristasSal ) )
		{
			p_arigRes = p_nodgObj->p_p_arigSalida [ iArista ];
			p_nodgObj->p_p_arigSalida [ iArista ] = NULL;

			for ( iAristaAux = iArista + 1; iAristaAux < p_nodgObj->iNumAristasSal; iAristaAux = iAristaAux + 1 )
			{
				p_nodgObj->p_p_arigSalida [ iAristaAux - 1 ] = p_nodgObj->p_p_arigSalida [ iAristaAux ];
			}
			p_nodgObj->p_p_arigSalida [ p_nodgObj->iNumAristasSal - 1 ] = NULL;
			p_nodgObj->iNumAristasSal = p_nodgObj->iNumAristasSal - 1;
		}
		else
		{
			p_arigRes = NULL;
		}
	}
	else
	{
		p_arigRes = NULL;
	}
	return ( p_arigRes );
}

int SNodGrfDesconectarAristaEntradaObj ( SNodoGrafo * p_nodgObj, SAristaGrafo * p_arigObj )
{
	int	iRes;
	int	iAristaDesc;
	int	iArista;

	if ( ES_VALIDO ( p_nodgObj ) )
	{
		if ( ( p_nodgObj->iNumAristasEnt > 0 ) && ES_VALIDO ( p_arigObj ) )
		{
			iArista = 0;
			iAristaDesc = -1;
			while ( ( iArista < p_nodgObj->iNumAristasEnt ) && ( iAristaDesc < 0 ) )
			{
				if ( p_nodgObj->p_p_arigEntrada [ iArista ] == p_arigObj )
				{
					iAristaDesc = iArista;
				}
				iArista = iArista + 1;
			}

			if ( iAristaDesc >= 0 )
			{
				p_nodgObj->p_p_arigEntrada [ iAristaDesc ] = NULL;

				for ( iArista = iAristaDesc + 1; iArista < p_nodgObj->iNumAristasEnt; iArista = iArista + 1 )
				{
					p_nodgObj->p_p_arigEntrada [ iArista - 1 ] = p_nodgObj->p_p_arigEntrada [ iArista ];
				}
				p_nodgObj->p_p_arigEntrada [ p_nodgObj->iNumAristasEnt - 1 ] = NULL;
				p_nodgObj->iNumAristasEnt = p_nodgObj->iNumAristasEnt - 1;
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

int SNodGrfDesconectarAristaSalidaObj ( SNodoGrafo * p_nodgObj, SAristaGrafo * p_arigObj )
{
	int	iRes;
	int	iAristaDesc;
	int	iArista;

	if ( ES_VALIDO ( p_nodgObj ) )
	{
		if ( ( p_nodgObj->iNumAristasSal > 0 ) && ES_VALIDO ( p_arigObj ) )
		{
			iArista = 0;
			iAristaDesc = -1;
			while ( ( iArista < p_nodgObj->iNumAristasSal ) && ( iAristaDesc < 0 ) )
			{
				if ( p_nodgObj->p_p_arigSalida [ iArista ] == p_arigObj )
				{
					iAristaDesc = iArista;
				}
				iArista = iArista + 1;
			}

			if ( iAristaDesc >= 0 )
			{
				p_nodgObj->p_p_arigSalida [ iAristaDesc ] = NULL;
				for ( iArista = iAristaDesc + 1; iArista < p_nodgObj->iNumAristasSal; iArista = iArista + 1 )
				{
					p_nodgObj->p_p_arigSalida [ iArista - 1 ] = p_nodgObj->p_p_arigSalida [ iArista ];
				}
				p_nodgObj->p_p_arigSalida [ p_nodgObj->iNumAristasSal - 1 ] = NULL;
				p_nodgObj->iNumAristasSal = p_nodgObj->iNumAristasSal - 1;
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

void SNodGrfInicializarAristasSalida ( SNodoGrafo * p_nodgObj )
{
	SAristaGrafo *	p_arigObj;
	SNodoGrafo *	p_nodgFin;
	int				iArista;

	if ( ES_VALIDO ( p_nodgObj ) )
	{
		for ( iArista = 0; iArista < p_nodgObj->iNumAristasSal; iArista = iArista + 1 )
		{
			p_arigObj = p_nodgObj->p_p_arigSalida [ iArista ];
			if ( ES_VALIDO ( p_arigObj ) )
			{
				if ( SAriGrfEstaRecorrida ( p_arigObj ) == 1 )
				{
					SAriGrfDesmarcarComoRecorrida ( p_arigObj );
					p_nodgFin = SAriGrfNodoFinal ( p_arigObj );
					if ( ES_VALIDO ( p_nodgFin ) )
					{
						SNodGrfLimpiarAristasSalida ( p_nodgFin, 0 );
					}
				}
			}
		}
	}
}

void SNodGrfLimpiarAristasEntrada ( SNodoGrafo * p_nodgObj )
{
	int	iArista;

	if ( ES_VALIDO ( p_nodgObj ) )
	{
		/* Las aristas de entrada solo se referencian ( las posee el nodo origen ),
		   asi que aqui solo se limpian las referencias, sin desreferenciar la arista. */
		for ( iArista = 0; iArista < p_nodgObj->iNumAristasEnt; iArista = iArista + 1 )
		{
			p_nodgObj->p_p_arigEntrada [ iArista ] = NULL;
		}
		p_nodgObj->iNumAristasEnt = 0;
	}
}

void SNodGrfLimpiarAristasSalida ( SNodoGrafo * p_nodgObj, int iLiberar )
{
	int	iArista;

	if ( ES_VALIDO ( p_nodgObj ) )
	{
		for ( iArista = 0; iArista < p_nodgObj->iNumAristasSal; iArista = iArista + 1 )
		{
			/* El nodo origen posee sus aristas de salida: se libera la arista, pero
			   NO se destruye en cascada su nodo final ( eso rompia con ciclos y
			   nodos compartidos ). SAriGrfDestruir desconecta ambos extremos. */
			if ( iLiberar == 1 )
			{
				if ( ES_VALIDO ( p_nodgObj->p_p_arigSalida [ iArista ] ) )
				{
					SAriGrfDestruir ( &(p_nodgObj->p_p_arigSalida [ iArista ]) );
				}
			}
			p_nodgObj->p_p_arigSalida [ iArista ] = NULL;
		}
		p_nodgObj->iNumAristasSal = 0;
	}
}

static void SNodGfrInicializar ( SNodoGrafo * p_nodgObj )
{
	if ( ES_VALIDO ( p_nodgObj ) )
	{
		MemLiberar ( (void **) &(p_nodgObj->p_p_arigEntrada) );
		MemLiberar ( (void **) &(p_nodgObj->p_p_arigSalida) );
		p_nodgObj->p_p_arigEntrada = (SAristaGrafo **) MemReservarVector ( p_nodgObj->iMaxAristas, sizeof ( SAristaGrafo *) );
		p_nodgObj->p_p_arigSalida = (SAristaGrafo **) MemReservarVector ( p_nodgObj->iMaxAristas, sizeof ( SAristaGrafo *) );
		p_nodgObj->iNumAristasEnt = 0;
		p_nodgObj->iNumAristasSal = 0;
		p_nodgObj->iId = -1;
		p_nodgObj->iDato = 0;
	}
}

