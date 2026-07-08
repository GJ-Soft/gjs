
#ifndef _ORG_GJS_C_CC_C_COMMON_SNODOPORBLOQUESPTR_H
#define _ORG_GJS_C_CC_C_COMMON_SNODOPORBLOQUESPTR_H



#include <Base.h>
#include <TiposBasicosConstantes.h>




typedef struct SNodoBlqPtr SNodoBlqPtr;

struct SNodoBlqPtr
{
	SNodoBlqPtr *	p_nodpPadre;
	SNodoBlqPtr ***	p_p_p_nodpHijos;
	int				iNumBloques;
	int				iNumHijos;

	byte *			p_byDatos;
	int				iLiberar;

};




SNodoBlqPtr * SNodBlqPtrCrearCrearMem ( int iTamDatos );
SNodoBlqPtr * SNodBlqPtrCrear ( byte * p_byDatos, int iLiberar );

void SNodBlqPtrDestruir ( SNodoBlqPtr ** p_p_nodpObj, int iDestruirHijos );

byte * SNodBlqPtrDatos ( SNodoBlqPtr * p_nodpObj );

int SNodBlqPtrEsValido ( SNodoBlqPtr * p_nodpObj );
int SNodBlqPtrTieneDatos ( SNodoBlqPtr * p_nodpObj );

int SNodBlqPtrModificar ( SNodoBlqPtr * p_nodpObj, byte * p_byDatos, int iLiberar );

int SNodBlqPtrNumHijos ( SNodoBlqPtr * p_nodpObj );
SNodoBlqPtr * SNodBlqPtrPadre ( SNodoBlqPtr * p_nodpObj );
SNodoBlqPtr * SNodBlqPtrHijo ( SNodoBlqPtr * p_nodpObj, int iHijo );

int SNodBlqPtrTienePadre ( SNodoBlqPtr * p_nodpObj );
int SNodBlqPtrTieneHijos ( SNodoBlqPtr * p_nodpObj );
int SNodBlqPtrTieneHermanos ( SNodoBlqPtr * p_nodpObj );
int SNodBlqPtrTieneHermanosIzq ( SNodoBlqPtr * p_nodpObj );
int SNodBlqPtrTieneHermanosDer ( SNodoBlqPtr * p_nodpObj );

int SNodBlqPtrNodosInferiores ( SNodoBlqPtr * p_nodpObj );
int SNodBlqPtrProfundidad ( SNodoBlqPtr * p_nodpObj );
int SNodBlqPtrNivelesInferiores ( SNodoBlqPtr * p_nodpObj );

int SNodBlqPtrEmpadronar ( SNodoBlqPtr * p_nodpObj, SNodoBlqPtr * p_nodPadre );
int SNodBlqPtrInsertarHijo ( SNodoBlqPtr * p_nodpObj, SNodoBlqPtr * p_nodpHijo );
void SNodBlqPtrDesempadronar ( SNodoBlqPtr * p_nodpObj );
int SNodBlqPtrEliminarHijo ( SNodoBlqPtr * p_nodpObj, int iHijo, int iLiberar );
int SNodBlqPtrEstablecerHijo ( SNodoBlqPtr * p_nodpObj, int iHijo, SNodoBlqPtr * p_nodpHijo, int iLiberar );
void SNodBlqPtrLimpiarHijos ( SNodoBlqPtr * p_nodpObj, int iLiberar );

int	SNodBlqPtrEsHijo ( SNodoBlqPtr * p_nodpObj, SNodoBlqPtr * p_nodPposible );
int SNodBlqPtrOrdenDelHijo ( SNodoBlqPtr * p_nodpObj, SNodoBlqPtr * p_nodpHijo );

int SNodBlqPtrVerificar ( SNodoBlqPtr * p_nodpObj, int iCorregir );

int	SNodBlqPtrLiberacionMemoriaActivada ( SNodoBlqPtr * p_nodpObj );




#endif
