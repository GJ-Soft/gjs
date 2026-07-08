
#ifndef _ORG_GJS_C_CC_C_COMMON_SNODOPORBLOQUES_H
#define _ORG_GJS_C_CC_C_COMMON_SNODOPORBLOQUES_H








#include <TiposBasicosConstantes.h>
#include <SBloque.h>





typedef struct SNodoBlq SNodoBlq;

struct SNodoBlq
{
	SNodoBlq *		p_nodPadre;
	SNodoBlq ***	p_p_p_nodHijos;
	int				iNumBloques;
	int				iNumHijos;

	SBloque *		p_blqDatos;
	int				iLiberar;

};


SNodoBlq * SNodBlqCrear ( int iTamDatos );
SNodoBlq * SNodBlqCrearEntero ();
SNodoBlq * SNodBlqCrearEnteroLargo ();
SNodoBlq * SNodBlqCrearReal ();
SNodoBlq * SNodBlqCrearRealDoble ();
SNodoBlq * SNodBlqCrearCadena ();
SNodoBlq * SNodBlqEncapsular ( SBloque * p_blqDatos );
SNodoBlq * SNodBlqEncapsularDir ( byte * p_byDirDatos, int iTamDatos, int iLiberar );

void SNodBlqDestruir ( SNodoBlq ** p_p_nodObj, int iDestruirHijos );

SBloque * SNodBlqDatos ( SNodoBlq * p_nodObj );
int SNodBlqEntero ( SNodoBlq * p_nodObj );
long SNodBlqEnteroLargo ( SNodoBlq * p_nodObj );
float SNodBlqReal ( SNodoBlq * p_nodObj );
double SNodBlqRealDoble ( SNodoBlq * p_nodObj );
char * SNodBlqCadena ( SNodoBlq * p_nodObj );

int SNodBlqEsValido ( SNodoBlq * p_nodObj );
int SNodBlqTieneDatos ( SNodoBlq * p_nodObj );

int SNodBlqModificar ( SNodoBlq * p_nodObj, SBloque * p_blqDatos );
int SNodBlqModificarDir ( SNodoBlq * p_nodObj, byte * p_byDirDatos, int iTamDatos, int iLiberar );
int SNodBlqEscribirByte ( SNodoBlq * p_nodObj, int iPos, byte byValor );
int SNodBlqEscribirEntero ( SNodoBlq * p_nodObj, int iValor );
int SNodBlqEscribirEnteroLargo ( SNodoBlq * p_nodObj, long lValor );
int SNodBlqEscribirReal ( SNodoBlq * p_nodObj, float fValor );
int SNodBlqEscribirRealDoble ( SNodoBlq * p_nodObj, double dValor );
int SNodBlqEscribirCadena ( SNodoBlq * p_nodObj, const char * p_cValor );

int SNodBlqNumHijos ( SNodoBlq * p_nodObj );
SNodoBlq * SNodBlqPadre ( SNodoBlq * p_nodObj );
SNodoBlq * SNodBlqHijo ( SNodoBlq * p_nodObj, int iHijo );

int SNodBlqTienePadre ( SNodoBlq * p_nodObj );
int SNodBlqTieneHijos ( SNodoBlq * p_nodObj );
int SNodBlqTieneHermanos ( SNodoBlq * p_nodObj );
int SNodBlqTieneHermanosIzq ( SNodoBlq * p_nodObj );
int SNodBlqTieneHermanosDer ( SNodoBlq * p_nodObj );

int SNodBlqNodosInferiores ( SNodoBlq * p_nodObj );
int SNodBlqProfundidad ( SNodoBlq * p_nodObj );
int SNodBlqNivelesInferiores ( SNodoBlq * p_nodObj );

int SNodBlqEmpadronar ( SNodoBlq * p_nodObj, SNodoBlq * p_nodPadre );
int SNodBlqInsertarHijo ( SNodoBlq * p_nodObj, SNodoBlq * p_nodHijo );
void SNodBlqDesempadronar ( SNodoBlq * p_nodObj );
int SNodBlqEliminarHijo ( SNodoBlq * p_nodObj, int iHijo, int iLiberar );
int SNodBlqEstablecerHijo ( SNodoBlq * p_nodObj, int iHijo, SNodoBlq * p_nodHijo, int iLiberar );
void SNodBlqLimpiarHijos ( SNodoBlq * p_nodObj, int iLiberar );

int	SNodBlqEsHijo ( SNodoBlq * p_nodObj, SNodoBlq * p_nodPosible );
int SNodoBlqOrdenDelHijo ( SNodoBlq * p_nodObj, SNodoBlq * p_nodHijo );

int SNodBlqVerificar ( SNodoBlq * p_nodObj, int iCorregir );

int	SNodBlqLiberacionMemoriaActivada ( SNodoBlq * p_nodObj );
SNodoBlq * SNodBlqDuplicar ( SNodoBlq * p_nodObj );



#endif
