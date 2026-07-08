
#ifndef _ORG_GJS_C_CC_C_COMMON_SNODO_H
#define _ORG_GJS_C_CC_C_COMMON_SNODO_H









#include <SBloque.h>





typedef struct SNodo SNodo;

struct SNodo
{
	SNodo *		p_nodPadre;
	SNodo **	p_p_nodHijos;
	int			iNumHijos;

	SBloque *	p_blqDatos;
	int			iLiberar;

};




SNodo * SNodCrear ( int iTamDatos );
SNodo * SNodCrearEntero ( int iValor );
SNodo * SNodCrearEnteroLargo ( long lValor  );
SNodo * SNodCrearReal ( float fValor  );
SNodo * SNodCrearRealDoble ( double dValor  );
SNodo * SNodCrearCadena ( const char * p_cValor );
SNodo * SNodEncapsular ( SBloque * p_blqDatos );
SNodo * SNodEncapsularDir ( byte * p_byDirDatos, int iTamDatos, int iLiberar );

void SNodDestruir ( SNodo ** p_p_nodObj, int iDestruirHijos );

SBloque * SNodDatos ( SNodo * p_nodObj );
int SNodEntero ( SNodo * p_nodObj );
long SNodEnteroLargo ( SNodo * p_nodObj );
float SNodReal ( SNodo * p_nodObj );
double SNodRealDoble ( SNodo * p_nodObj );
char * SNodCadena ( SNodo * p_nodObj );

int SNodEsValido ( SNodo * p_nodObj );
int SNodTieneDatos ( SNodo * p_nodObj );

int SNodModificar ( SNodo * p_nodObj, SBloque * p_blqDatos );
int SNodModificarDir ( SNodo * p_nodObj, byte * p_byDirDatos, int iTamDatos, int iLiberar );
int SNodEstablecerByte ( SNodo * p_nodObj, int iPos, byte byValor );
int SNodEstablecerEntero ( SNodo * p_nodObj, int iValor );
int SNodEstablecerEnteroLargo ( SNodo * p_nodObj, long lValor );
int SNodEstablecerReal ( SNodo * p_nodObj, float fValor );
int SNodEstablecerRealDoble ( SNodo * p_nodObj, double dValor );
int SNodEstablecerCadena ( SNodo * p_nodObj, const char * p_cValor );

int SNodNumHijos ( SNodo * p_nodObj );
SNodo * SNodPadre ( SNodo * p_nodObj );
SNodo * SNodHijo ( SNodo * p_nodObj, int iHijo );

int SNodTienePadre ( SNodo * p_nodObj );
int SNodTieneHijos ( SNodo * p_nodObj );
int SNodTieneHermanos ( SNodo * p_nodObj );
int SNodTieneHermanosIzq ( SNodo * p_nodObj );
int SNodTieneHermanosDer ( SNodo * p_nodObj );

int SNodNodosInferiores ( SNodo * p_nodObj );
int SNodProfundidad ( SNodo * p_nodObj );
int SNodNivelesInferiores ( SNodo * p_nodObj );

int SNodEmpadronar ( SNodo * p_nodObj, SNodo * p_nodPadre );
int SNodInsertarHijo ( SNodo * p_nodObj, SNodo * p_nodHijo );
void SNodDesempadronar ( SNodo * p_nodObj );
int SNodEliminarHijo ( SNodo * p_nodObj, int iHijo, int iLiberarHijos );
int SNodEstablecerHijo ( SNodo * p_nodObj, int iHijo, SNodo * p_nodHijo, int iLiberarHijos );
void SNodLimpiarHijos ( SNodo * p_nodObj, int iLiberarHijos );

int	SNodEsHijo ( SNodo * p_nodObj );
int SNodOrdenDelHijo ( SNodo * p_nodObj, SNodo * p_nodHijo );

int SNodVerificar ( SNodo * p_nodObj, int iCorregir );

int	SNodLiberacionMemoriaActivada ( SNodo * p_nodObj );
SNodo * SNodDuplicar ( SNodo * p_nodObj );




#endif
