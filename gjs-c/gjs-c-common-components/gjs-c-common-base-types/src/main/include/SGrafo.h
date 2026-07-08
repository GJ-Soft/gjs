
#ifndef _ORG_GJS_C_CC_C_COMMON_SGRAFO_H
#define _ORG_GJS_C_CC_C_COMMON_SGRAFO_H








#include <SAristaGrafo.h>
#include <SNodoGrafo.h>




typedef struct
{

	SNodoGrafo *	p_nodgInicial;
	SNodoGrafo *	p_nodgActual;

	SNodoGrafo **	p_p_nodgLista;
	int				iNumNodos;
	int 			iMaxNodos;
	int				iMaxAristasNodo;

} SGrafo;




SGrafo * SGrfCrear ( int iMaxNodos, int iMaxAristasNodo );

void SGrfDestruir ( SGrafo ** p_p_grfObj );

SNodoGrafo * SGrfInicial ( SGrafo * p_grfObj );
int SGrfEstInicial ( SGrafo * p_grfObj, SNodoGrafo * p_nodgObj );

int SGrfEstaVacio ( SGrafo * p_grfObj );
int SGrfNumNodos ( SGrafo * p_grfObj );

int SGrfVaciar ( SGrafo * p_grfObj );

SNodoGrafo * SGrfCrearNodo ( SGrafo * p_grfObj );
SNodoGrafo * SGrfActual ( SGrafo * p_grfObj );
int	SGrfDato ( SGrafo * p_grfObj );

int SGrfNumEntradas ( SGrafo * p_grfObj );
int SGrfNumSalidas ( SGrafo * p_grfObj );
int SGrfEsEntradaValida ( SGrafo * p_grfObj, int iArista );
int SGrfEsSalidaValida ( SGrafo * p_grfObj, int iArista );
int SGrfTieneEntradasPorRecorrer ( SGrafo * p_grfObj );
int SGrfTieneSalidasPorRecorrer ( SGrafo * p_grfObj );
int SGrfTieneEntradasRecorridas ( SGrafo * p_grfObj );
int SGrfTieneSalidasRecorridas ( SGrafo * p_grfObj );

void SGrfMoverAInicial ( SGrafo * p_grfObj );
void SGrfMoverAEntrada ( SGrafo * p_grfObj, int iArista );
void SGrfMoverASalida ( SGrafo * p_grfObj, int iArista );
int SGrfMoverAPrimeraEntrada ( SGrafo * p_grfObj );
int SGrfMoverAPrimeraSalida ( SGrafo * p_grfObj );
int SGrfMoverAUltimaEntrada ( SGrafo * p_grfObj );
int SGrfMoverAUltimaSalida ( SGrafo * p_grfObj );
int SGrfMoverAPrimeraEntradaPorRecorrer ( SGrafo * p_grfObj );
int SGrfMoverAPrimeraSalidaPorRecorrer ( SGrafo * p_grfObj );
int SGrfMoverAUltimaEntradaRecorrida ( SGrafo * p_grfObj );
int SGrfMoverAUltimaSalidaRecorrida ( SGrafo * p_grfObj );
int SGrfMoverANodo ( SGrafo * p_grfObj, int iId );

void SGrfDesposicionar ( SGrafo * p_grfObj );
int	SGrfEstaPosicionado ( SGrafo * p_grfObj );
int	SGrfEstaEnInicial ( SGrafo * p_grfObj );

int SGrfConectar ( SGrafo * p_grfObj, SAristaGrafo * p_arigObj );
int SGrfConectarConNodo ( SGrafo * p_grfObj, SAristaGrafo * p_arigObj, SNodoGrafo * p_nodObj );
int SGrfConectarANodo ( SGrafo * p_grfObj, SAristaGrafo * p_arigObj, int iIdNodo );
int SGrfConectarANodoInicial ( SGrafo * p_grfObj, SAristaGrafo * p_arigObj );



SNodoGrafo * SGrfNodo ( SGrafo * p_grfObj, int iIndice );


#endif



