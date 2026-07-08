
#ifndef _ORG_GJS_C_CC_C_COMMON_SNODOBIN_H
#define _ORG_GJS_C_CC_C_COMMON_SNODOBIN_H







#include <SBloque.h>



typedef struct SNodoBin SNodoBin;

struct SNodoBin
{
	SNodoBin * p_nodbPadre;
	SNodoBin * p_nodbHijoIzq;
	SNodoBin * p_nodbHijoDer;

	SBloque *	p_blqDatos;
	int			iLiberar;
};



SNodoBin * SNodBinCrearMem ( int iTamDatos );
SNodoBin * SNodBinCrearEntero ( int iValor );
SNodoBin * SNodBinCrearEnteroLargo ( long lValor  );
SNodoBin * SNodBinCrearReal ( float fValor  );
SNodoBin * SNodBinCrearRealDoble ( double dValor  );
SNodoBin * SNodBinCrearCadena ( const char * p_cValor );
SNodoBin * SNodBinEncapsular ( SBloque * p_blqDatos );
SNodoBin * SNodBinEncapsularDir ( byte * p_byDirDatos, int iTamDatos, int iLiberar );

void SNodBinDestruir ( SNodoBin ** p_p_nodbObj, int iDestruirHijos );

SBloque * SNodBinDatos ( SNodoBin * p_nodbObj );
int SNodBinEntero ( SNodoBin * p_nodbObj );
long SNodBinEnteroLargo ( SNodoBin * p_nodbObj );
float SNodBinReal ( SNodoBin * p_nodbObj );
double SNodBinRealDoble ( SNodoBin * p_nodbObj );
char * SNodBinCadena ( SNodoBin * p_nodbObj );

int SNodBinEsValido ( SNodoBin * p_nodbObj );
int SNodBinTieneDatos ( SNodoBin * p_nodbObj );

int SNodBinModificar ( SNodoBin * p_nodbObj, SBloque * p_blqDatos );
int SNodBinModificarDir ( SNodoBin * p_nodbObj, byte * p_byDirDatos, int iTamDatos, int iLiberar );
int SNodBinEstablecerByte ( SNodoBin * p_nodbObj, int iPos, byte byValor );
int SNodBinEstablecerEntero ( SNodoBin * p_nodbObj, int iValor );
int SNodBinEstablecerEnteroLargo ( SNodoBin * p_nodbObj, long lValor );
int SNodBinEstablecerReal ( SNodoBin * p_nodbObj, float fValor );
int SNodBinEstablecerRealDoble ( SNodoBin * p_nodbObj, double dValor );
int SNodBinEstablecerCadena ( SNodoBin * p_nodbObj, const char * p_cValor );

SNodoBin * SNodBinPadre ( SNodoBin * p_nodbObj );
SNodoBin * SNodBinHijoDer ( SNodoBin * p_nodbObj );
SNodoBin * SNodBinHijoIzq ( SNodoBin * p_nodbObj );

int SNodBinTienePadre ( SNodoBin * p_nodbObj );
int SNodBinTieneHijos ( SNodoBin * p_nodbObj );
int SNodBinTieneHermano ( SNodoBin * p_nodbObj );
int SNodBinEsHijoIzqDelPadre ( SNodoBin * p_nodbObj );
int SNodBinEsHijoDerDelPadre ( SNodoBin * p_nodbObj );
int SNodBinTieneHijoIzq ( SNodoBin * p_nodbObj );
int SNodBinTieneHijoDer ( SNodoBin * p_nodbObj );
int SNodBinTieneHermanoIzq ( SNodoBin * p_nodbObj );
int SNodBinTieneHermanoDer ( SNodoBin * p_nodbObj );

int SNodBinNodosInferiores ( SNodoBin * p_nodbObj );
int SNodBinProfundidad ( SNodoBin * p_nodbObj );
int SNodBinNivelesInferiores ( SNodoBin * p_nodbObj );

int SNodBinEmpadronar ( SNodoBin * p_nodbObj, SNodoBin * p_nodbPadre );
void SNodBinDesempadronar ( SNodoBin * p_nodbObj );
int SNodBinEliminarHijoIzq ( SNodoBin * p_nodbObj, int iLiberar );
int SNodBinEliminarHijoDer ( SNodoBin * p_nodbObj, int iLiberar );
int SNodBinEstHijoIzq ( SNodoBin * p_nodbObj, SNodoBin * p_nodbHijo, int iLiberar );
int SNodBinEstHijoDer ( SNodoBin * p_nodbObj, SNodoBin * p_nodbHijo, int iLiberar );
void SNodBinLimpiarHijos ( SNodoBin * p_nodbObj, int iLiberar );

int	SNodBinEsHijo ( SNodoBin * p_nodbObj, SNodoBin * p_nodbHijo );
int	SNodBinEsHijoIzq ( SNodoBin * p_nodbObj, SNodoBin * p_nodbHijo );
int	SNodBinEsHijoDer ( SNodoBin * p_nodbObj, SNodoBin * p_nodbHijo );

int SNodBinVerificar ( SNodoBin * p_nodbObj, int iCorregir );

int	SNodBinLiberacionMemoriaActivada ( SNodoBin * p_nodbObj );
SNodoBin * SNodBinDuplicar ( SNodoBin * p_nodbObj );






#endif
