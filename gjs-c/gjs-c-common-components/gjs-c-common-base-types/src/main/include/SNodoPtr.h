
#ifndef _ORG_GJS_C_CC_C_COMMON_SNODOPTR_H
#define _ORG_GJS_C_CC_C_COMMON_SNODOPTR_H





#include <Base.h>





typedef struct SNodoPtr SNodoPtr;


struct SNodoPtr
{
	SNodoPtr *		p_nodpPadre;			// SNodoPtr *
	SNodoPtr **		p_p_nodpHijos;			// SNodoPtr **
	int				iNumHijos;

	byte *			p_byDatos;
	int				iLiberar;

};




SNodoPtr * SNodBinCrearMem ( int iTamDatos );
SNodoPtr * SNodPtrCrear ( byte * p_byDatos, int iLiberar );

void SNodPtrDestruir ( SNodoPtr ** p_p_nodpObj, int iDestruirHijos );

byte * SNodPtrDatos ( SNodoPtr * p_nodpObj );

int SNodPtrEsValido ( SNodoPtr * p_elmObj );
int SNodPtrTieneDatos ( SNodoPtr * p_elmObj );

int SNodPtrModificar ( SNodoPtr * p_elmObj, byte * p_byDatos, int iLiberar );

int SNodPtrNumHijos ( SNodoPtr * p_nodpObj );
SNodoPtr * SNodPtrPadre ( SNodoPtr * p_nodpObj );
SNodoPtr * SNodPtrHijo ( SNodoPtr * p_nodpObj, int iHijo );

int SNodPtrTienePadre ( SNodoPtr * p_nodpObj );
int SNodPtrTieneHijos ( SNodoPtr * p_nodpObj );
int SNodPtrTieneHermanos ( SNodoPtr * p_nodpObj );
int SNodPtrTieneHermanosIzq ( SNodoPtr * p_nodpObj );
int SNodPtrTieneHermanosDer ( SNodoPtr * p_nodpObj );

int SNodPtrNodosInferiores ( SNodoPtr * p_nodpObj );
int SNodPtrProfundidad ( SNodoPtr * p_nodpObj );
int SNodPtrNivelesInferiores ( SNodoPtr * p_nodpObj );

int SNodPtrEmpadronar ( SNodoPtr * p_nodpObj, SNodoPtr * p_nodPadre );
int SNodPtrInsertarHijo ( SNodoPtr * p_nodpObj, SNodoPtr * p_nodHijo );
void SNodPtrDesempadronar ( SNodoPtr * p_nodpObj );
int SNodPtrEliminarHijo ( SNodoPtr * p_nodpObj, int iHijo, int iLiberarHijos );
int SNodPtrEstablecerHijo ( SNodoPtr * p_nodpObj, int iHijo, SNodoPtr * p_nodHijo, int iLiberarHijos );
void SNodPtrLimpiarHijos ( SNodoPtr * p_nodpObj, int iLiberarHijos );

int	SNodPtrEsHijo ( SNodoPtr * p_nodpObj );
int SNodPtrOrdenDelHijo ( SNodoPtr * p_nodpObj, SNodoPtr *  p_nodpHijo );

int SNodPtrVerificar ( SNodoPtr * p_nodpObj, int iCorregir );

int	SNodPtrLiberacionMemoriaActivada ( SNodoPtr * p_elmObj );





#endif
