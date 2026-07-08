
#ifndef _ORG_GJS_C_CC_C_COMMON_SNODOBINPTR_H
#define _ORG_GJS_C_CC_C_COMMON_SNODOBINPTR_H






#include <Base.h>





typedef struct SNodoBinPtr SNodoBinPtr;

struct SNodoBinPtr
{
	SNodoBinPtr * 	p_nodbpPadre;
	SNodoBinPtr * 	p_nodbpHijoIzq;
	SNodoBinPtr * 	p_nodbpHijoDer;

	byte *			p_byDatos;
	int				iLiberar;

};



SNodoBinPtr * SNodBinPtrCrearMem ( int iTamDatos );
SNodoBinPtr * SNodBinPtrCrear ( byte * p_byDatos, int iLiberar );

void SNodBinPtrDestruir ( SNodoBinPtr ** p_p_nodbpObj, int iDestruirHijos );

byte * SNodBinPtrDatos ( SNodoBinPtr * p_nodbpObj );

int SNodBinPtrEsValido ( SNodoBinPtr * p_nodbpObj );
int SNodBinPtrTieneDatos ( SNodoBinPtr * p_nodbpObj );

int SNodBinPtrModificar ( SNodoBinPtr * p_nodbpObj, byte * p_byDatos, int iLiberar );

SNodoBinPtr * SNodBinPtrPadre ( SNodoBinPtr * p_nodbpObj );
SNodoBinPtr * SNodBinPtrHijoDer ( SNodoBinPtr * p_nodbpObj );
SNodoBinPtr * SNodBinPtrHijoIzq ( SNodoBinPtr * p_nodbpObj );

int SNodBinPtrTienePadre ( SNodoBinPtr * p_nodbpObj );
int SNodBinPtrTieneHijos ( SNodoBinPtr * p_nodbpObj );
int SNodBinPtrTieneHermano ( SNodoBinPtr * p_nodbpObj );
int SNodBinPtrEsHijoIzqDelPadre ( SNodoBinPtr * p_nodbpObj );
int SNodBinPtrEsHijoDerDelPadre ( SNodoBinPtr * p_nodbpObj );
int SNodBinPtrTieneHijoIzq ( SNodoBinPtr * p_nodbpObj );
int SNodBinPtrTieneHijoDer ( SNodoBinPtr * p_nodbpObj );
int SNodBinPtrTieneHermanoIzq ( SNodoBinPtr * p_nodbpObj );
int SNodBinPtrTieneHermanoDer ( SNodoBinPtr * p_nodbpObj );

int SNodBinPtrNodosInferiores ( SNodoBinPtr * p_nodbpObj );
int SNodBinPtrProfundidad ( SNodoBinPtr * p_nodbpObj );
int SNodBinPtrNivelesInferiores ( SNodoBinPtr * p_nodbpObj );

int SNodBinPtrEmpadronar ( SNodoBinPtr * p_nodbpObj, SNodoBinPtr * p_nodbpPadre );
void SNodBinPtrDesempadronar ( SNodoBinPtr * p_nodbpObj );
int SNodBinPtrEliminarHijoIzq ( SNodoBinPtr * p_nodbpObj, int iLiberar );
int SNodBinPtrEliminarHijoDer ( SNodoBinPtr * p_nodbpObj, int iLiberar );
int SNodBinPtrEstHijoIzq ( SNodoBinPtr * p_nodbpObj, SNodoBinPtr * p_nodbpHijo, int iLiberar );
int SNodBinPtrEstHijoDer ( SNodoBinPtr * p_nodbpObj, SNodoBinPtr * p_nodbpHijo, int iLiberar );
void SNodBinPtrLimpiarHijos ( SNodoBinPtr * p_nodbpObj, int iLiberar );

int	SNodBinPtrEsHijo ( SNodoBinPtr * p_nodbpObj, SNodoBinPtr * p_nodbpHijo );
int	SNodBinPtrEsHijoIzq ( SNodoBinPtr * p_nodbpObj, SNodoBinPtr * p_nodbpHijo );
int	SNodBinPtrEsHijoDer ( SNodoBinPtr * p_nodbpObj, SNodoBinPtr * p_nodbpHijo );

int SNodBinPtrVerificar ( SNodoBinPtr * p_nodbpObj, int iCorregir );

int	SNodBinPtrLiberacionMemoriaActivada ( SNodoBinPtr * p_nodbpObj );







#endif
