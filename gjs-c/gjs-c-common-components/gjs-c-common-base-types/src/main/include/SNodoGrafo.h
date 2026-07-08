
#ifndef _ORG_GJS_C_CC_C_COMMON_SNODOGRAFO_H
#define _ORG_GJS_C_CC_C_COMMON_SNODOGRAFO_H








typedef struct SAristaGrafo SAristaGrafo;




typedef struct
{
	SAristaGrafo **	p_p_arigEntrada;
	SAristaGrafo **	p_p_arigSalida;

	int 			iMaxAristas;
	int				iNumAristasEnt;
	int				iNumAristasSal;

	int				iId;
	int				iDato;

} SNodoGrafo;



SNodoGrafo * SNodGrfCrear ( int iMaxAristas );

void SNodGrfDestruir ( SNodoGrafo ** p_p_nodgObj );

int SNodGrfId ( SNodoGrafo * p_nodgObj );
void SNodGrfEstablecerId ( SNodoGrafo * p_nodgObj, int iId );

int SNodGrfDato ( SNodoGrafo * p_nodgObj );
void SNodGrfEstablecerDato ( SNodoGrafo * p_nodgObj, int iValor );

int SNodGrfMaxAristas ( SNodoGrafo * p_nodgObj );
int SNodGrfNumAristasEntrada ( SNodoGrafo * p_nodgObj );
int SNodGrfNumAristasSalida ( SNodoGrafo * p_nodgObj );
int SNodGrfAristaEntradaEsValida ( SNodoGrafo * p_nodgObj, int iArista );
int SNodGrfAristaSalidaEsValida ( SNodoGrafo * p_nodgObj, int iArista );
SAristaGrafo * SNodGrfAristaEntrada ( SNodoGrafo * p_nodgObj, int iArista );
SAristaGrafo * SNodGrfAristaSalida ( SNodoGrafo * p_nodgObj, int iArista );

int SNodGrfTieneAristasEntrada ( SNodoGrafo * p_nodgObj );
int SNodGrfTieneAristasSalida ( SNodoGrafo * p_nodgObj );
int SNodGrfTieneAristasEntradaPorRecorrer ( SNodoGrafo * p_nodgObj );
int SNodGrfTieneAristasSalidaPorRecorrer ( SNodoGrafo * p_nodgObj );
int SNodGrfTieneAristasEntradaRecorridas ( SNodoGrafo * p_nodgObj );
int SNodGrfTieneAristasSalidaRecorridas ( SNodoGrafo * p_nodgObj );
int SNodGrfPrimeraAristaEntradaPorRecorrer ( SNodoGrafo * p_nodgObj );
int SNodGrfPrimeraAristaSalidaPorRecorrer ( SNodoGrafo * p_nodgObj );
int SNodGrfUltimaAristaEntradaRecorrida ( SNodoGrafo * p_nodgObj );
int SNodGrfUltimaAristaSalidaRecorrida ( SNodoGrafo * p_nodgObj );

int SNodGrfConectarAristaEntrada ( SNodoGrafo * p_nodgObj, SAristaGrafo * p_arigObj );
int SNodGrfConectarAristaSalida ( SNodoGrafo * p_nodgObj, SAristaGrafo * p_arigObj );

SAristaGrafo * SNodGrfDesconectarAristaEntrada ( SNodoGrafo * p_nodgObj, int iArista );
SAristaGrafo * SNodGrfDesconectarAristaSalida ( SNodoGrafo * p_nodgObj, int iArista );
int SNodGrfDesconectarAristaEntradaObj ( SNodoGrafo * p_nodgObj, SAristaGrafo * p_arigObj );
int SNodGrfDesconectarAristaSalidaObj ( SNodoGrafo * p_nodgObj, SAristaGrafo * p_arigObj );

void SNodGrfInicializarAristasSalida ( SNodoGrafo * p_nodgObj );

void SNodGrfLimpiarAristasEntrada ( SNodoGrafo * p_nodgObj );
void SNodGrfLimpiarAristasSalida ( SNodoGrafo * p_nodgObj, int iLiberar );








#endif

