
#ifndef _ORG_GJS_C_CC_C_COMMON_SARISTAGRAFO_H
#define _ORG_GJS_C_CC_C_COMMON_SARISTAGRAFO_H








#include <SNodoGrafo.h>




struct  SAristaGrafo  
{

	SNodoGrafo *	p_nodgInicial;
	SNodoGrafo *	p_nodgFinal;

	int				iRecorrida;
	
};


SAristaGrafo * SAriGrfCrear ();
SAristaGrafo * SAriGrfCrearExt ( SNodoGrafo * p_nodgInicial, SNodoGrafo * p_nodgFinal );

void SAriGrfDestruir ( SAristaGrafo ** p_p_arigObj );

SNodoGrafo * SAriGrfNodoInicial ( SAristaGrafo * p_arigObj );
SNodoGrafo * SAriGrfNodoFinal ( SAristaGrafo * p_arigObj );

int SAriGrfTieneNodoInicial ( SAristaGrafo * p_arigObj );
int SAriGrfTieneNodoFinal ( SAristaGrafo * p_arigObj );

int SAriGrfConectar ( SAristaGrafo * p_arigObj, SNodoGrafo * p_nodgInicial, SNodoGrafo * p_nodgFinal );
int SAriGrfConectarNodoInicial ( SAristaGrafo * p_arigObj, SNodoGrafo * p_nodgObj );
int SAriGrfConectarNodoFinal ( SAristaGrafo * p_arigObj, SNodoGrafo * p_nodgObj );

void SAriGrfDesconectar ( SAristaGrafo * p_arigObj );
SNodoGrafo * SAriGrfDesconectarNodoInicial ( SAristaGrafo * p_arigObj );
SNodoGrafo * SAriGrfDesconectarNodoFinal ( SAristaGrafo * p_arigObj );

void SAriGrfLimpiarNodoInicial ( SAristaGrafo * p_arigObj );
void SAriGrfLimpiarNodoFinal ( SAristaGrafo * p_arigObj, int iLiberar );

int SAriGrfEstaRecorrida ( SAristaGrafo * p_arigObj );
void SAriGrfMarcarComoRecorrida ( SAristaGrafo * p_arigObj );
void SAriGrfDesmarcarComoRecorrida ( SAristaGrafo * p_arigObj );


 




#endif

