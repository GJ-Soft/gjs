#ifndef _ORG_GJS_C_CC_C_COMMON_SELEMENTO_H
#define _ORG_GJS_C_CC_C_COMMON_SELEMENTO_H



#include <SBloque.h>






typedef struct 
{
	void *		p_elmAnt;  // SElemento
	void *		p_elmSig;  // SElemento

	SBloque *	p_blqDatos;
	int			iLiberar;

} SElemento; 




SElemento * SElmCrear ( int iTam );
SElemento * SElmCrearEntero ();
SElemento * SElmCrearEnteroSinSigno ();
SElemento * SElmCrearEnteroLargo ();
SElemento * SElmCrearEnteroLargoSinSigno ();
SElemento * SElmCrearReal ();
SElemento * SElmCrearRealDoble ();
SElemento * SElmCrearCadena ();
SElemento * SElmEncapsular ( SBloque * p_blqDatos );
SElemento * SElmEncapsularDir ( byte * p_byDirDatos, int iTamDatos, int iLiberar );

void SElmDestruir ( SElemento ** p_p_elmObj );

int SElmEsValido ( SElemento * p_elmObj );

SBloque * SElmDatos ( SElemento * p_elmObj );
int SElmEntero ( SElemento * p_elmObj );
unsigned int SElmEnteroSinSigno ( SElemento * p_elmObj );
long SElmEnteroLargo ( SElemento * p_elmObj );
unsigned long SElmEnteroLargoSinSigno ( SElemento * p_elmObj );
float SElmReal ( SElemento * p_elmObj );
double SElmRealDoble ( SElemento * p_elmObj );
char * SElmCadena ( SElemento * p_elmObj );
int SElmTieneDatos ( SElemento * p_elmObj );

int SElmModificar ( SElemento * p_elmObj, SBloque * p_blqDatos );
int SElmModificarDir ( SElemento * p_elmObj, byte * p_byDirDatos, int iTamDatos, int iLiberar );
int SElmEscribirByte ( SElemento * p_elmObj, int iPos, byte byValor );
int SElmEscribirEntero ( SElemento * p_elmObj, int iValor );
int SElmEscribirEnteroSinSigno ( SElemento * p_elmObj, unsigned int uiValor );
int SElmEscribirEnteroLargo ( SElemento * p_elmObj, long lValor );
int SElmEscribirEnteroLargoSinSigno ( SElemento * p_elmObj, unsigned long ulValor );
int SElmEscribirReal ( SElemento * p_elmObj, float fValor );
int SElmEscribirRealDoble ( SElemento * p_elmObj, double dValor );
int SElmEscribirCadena ( SElemento * p_elmObj, const char * p_cValor );

SElemento * SElmAntecesor ( SElemento * p_elmObj );	
SElemento * SElmSucesor ( SElemento * p_elmObj );	
int SElmTieneAntecesor ( SElemento * p_elmObj );
int SElmTieneSucesor ( SElemento * p_elmObj );
int SElmEncadenarAntecesor ( SElemento * p_elmObj, SElemento * p_elmAnt );
int SElmEncadenarSucesor ( SElemento * p_elmObj, SElemento * p_elmSuc );
int SElmDesencadenarAntecesor ( SElemento * p_elmObj );
int SElmDesencadenarSucesor ( SElemento * p_elmObj );
int SElmDesencadenar ( SElemento * p_elmObj );
void SElmDeposicionar ( SElemento * p_elmObj );

int SElmEsIgual ( SElemento * p_elmObj1, SElemento * p_elmObj2 );
int SElmEsIgualBlq ( SElemento * p_elmObj, SBloque * p_blqObj );
int SElmEsIgualExt ( SElemento * p_elmObj, byte * p_byObj );

int	SElmLiberacionMemoriaActivada ( SElemento * p_elmObj );
//void SElmActivarLiberacionMemoria ( SElemento * p_elmObj );
//void SElmDesactivarLiberacionMemoria ( SElemento * p_elmObj );

SElemento * SElmDuplicar ( SElemento * p_elmObj );

unsigned int SElmHash ( SElemento * p_elmObj );

/* iInc eslabones hacia atras o hacia delante. Con iInc = 0 devuelven el propio
   elemento; NULL si se sale por el extremo o si iInc es negativo. Sus gemelas
   de SElementoPtr se comportan igual. */
SElemento * SElmAntecesorExt ( SElemento * p_elmObj, int iInc );
SElemento * SElmSucesorExt ( SElemento * p_elmObj, int iInc );

#endif
