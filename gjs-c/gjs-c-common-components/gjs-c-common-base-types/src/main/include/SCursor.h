#ifndef _SCURSOR_H
#define _SCURSOR_H








typedef struct 
{
	int iLinea;
	int iColumna;

} SCursor;





SCursor * SCurCrear ( int iLinea, int iColumna );

void SCurDestruir ( SCursor ** p_p_curObj );

int SCurLinea ( SCursor * p_curObj );
int SCurColumna ( SCursor * p_curObj );

int SCurEsValido ( SCursor * p_curObj );

int SCurEstablecer ( SCursor * p_curObj, int iLinea, int iColumna );
int SCurEstablecerLinea ( SCursor * p_curObj, int iLinea );
int SCurEstablecerColumna ( SCursor * p_curObj, int iColumna );

int SCurAsignar ( SCursor * p_curObj, SCursor * p_curVal );

int SCurEsIgual ( SCursor * p_curObj, SCursor * p_curVal );
int SCurEsMenor ( SCursor * p_curObj, SCursor * p_curVal );
int SCurEsMayor ( SCursor * p_curObj, SCursor * p_curVal );

int SCurEsIgualExt ( SCursor * p_curObj, int iLinea, int iColumna );
int SCurEsMenorExt ( SCursor * p_curObj, int iLinea, int iColumna );
int SCurEsMayorExt ( SCursor * p_curObj, int iLinea, int iColumna );

int SCurDesplazar ( SCursor * p_curObj, int iLinea, int iColumna );


SCursor * SCurDuplicar ( SCursor * p_curObj );



#endif

