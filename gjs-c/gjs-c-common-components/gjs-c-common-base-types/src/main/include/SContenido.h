#ifndef _ORG_GJS_C_CC_C_COMMON_SCONTENIDO_H
#define _ORG_GJS_C_CC_C_COMMON_SCONTENIDO_H




#include <SBloque.h>




typedef struct
{
	SBloque *	p_blqDatos;
	int			iLiberar;

} SContenido;




SContenido * SConCrear ( int iTam );
SContenido * SConCrearEntero ();
SContenido * SConCrearEnteroLargo ();
SContenido * SConCrearReal ();
SContenido * SConCrearRealDoble ();
SContenido * SConCrearCadena ();
SContenido * SConEncapsular ( SBloque * p_blqDatos );
SContenido * SConEncapsularDir ( byte * p_byDirDatos, int iTamDatos, int iLiberar );

void SConDestruir ( SContenido ** p_p_conObj );

int SConEsValido ( SContenido * p_conObj );

SBloque * SConDatos ( SContenido * p_conObj );
int SConEntero ( SContenido * p_conObj );
long SConEnteroLargo ( SContenido * p_conObj );
float SConReal ( SContenido * p_conObj );
double SConRealDoble ( SContenido * p_conObj );
char * SConCadena ( SContenido * p_conObj );
int SConTieneDatos ( SContenido * p_conObj );

int SConModificar ( SContenido * p_conObj, SBloque * p_blqDatos );
int SConModificarDir ( SContenido * p_conObj, byte * p_byDirDatos, int iTamDatos, int iLiberar );
int SConEscribirByte ( SContenido * p_conObj, int iPos, byte byValor );
int SConEscribirEntero ( SContenido * p_conObj, int iValor );
int SConEscribirEnteroLargo ( SContenido * p_conObj, long lValor );
int SConEscribirReal ( SContenido * p_conObj, float fValor );
int SConEscribirRealDoble ( SContenido * p_conObj, double dValor );
int SConEscribirCadena ( SContenido * p_conObj, const char * p_cValor );

int	SConLiberacionMemoriaActivada ( SContenido * p_conObj );
//void SConActivarLiberacionMemoria ( SContenido * p_conObj );
//void SConDesactivarLiberacionMemoria ( SContenido * p_conObj );

SContenido * SConDuplicar ( SContenido * p_conObj );





#endif


