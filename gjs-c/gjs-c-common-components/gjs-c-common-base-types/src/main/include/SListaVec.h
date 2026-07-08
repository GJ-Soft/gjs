

#ifndef _ORG_GJS_C_CC_C_COMMON_SVLISTA_H
#define _ORG_GJS_C_CC_C_COMMON_SVLISTA_H



typedef struct
{
	int					iMaxElems;
	int					iNumElems;

	void *				p_vContenido;

	int					iPrim;
	int					iUlt;
	int					iLib;
	int					iAct;
	
	int 				iLiberar;
} SVLista;



SVLista * SVLisCrear ( int iMaxElems, int iLiberar );

void SVLisDestruir ( SVLista ** p_p_lisObj );

int SVLisEsValida ( SVLista * p_lisObj );
int SVLisNumElementos ( SVLista * p_lisObj );
int SVLisMaxElementos ( SVLista * p_lisObj );
int SVLisEstaLlena ( SVLista * p_lisObj );
int SVLisEstaVacia ( SVLista * p_lisObj );

int SVLisInsertar ( SVLista * p_lisObj, void * p_vValor );

void SVLisInicio ( SVLista * p_lisObj );
void SVLisFinal ( SVLista * p_lisObj );
void SVLisSiguiente ( SVLista * p_lisObj );
void SVLisAnterior ( SVLista * p_lisObj );
int SVListaEstaEnPrincipio ( SVLista * p_lisObj );
int SVListaEstaEnFinal ( SVLista * p_lisObj );
int SVListaEstaPosicionado ( SVLista * p_lisObj );

void * SVLisElementoActual ( SVLista * p_lisObj );
void * SVLisElemento ( SVLista * p_lisObj, int iPos );

int SVLisEliminar ( SVLista * p_lisObj, int iPos );

void SVLisVaciar ( SVLista * p_lisObj );

int	SVLisLiberacionMemoriaActivada ( SVLista * p_lisObj );
void SVLisActivarLiberacionMemoria ( SVLista * p_lisObj );
void SVLisDesactivarLiberacionMemoria ( SVLista * p_lisObj );


#endif
