
#ifndef _ORG_GJS_C_CC_UTILIDADESFICHEROS_H
#define _ORG_GJS_C_CC_UTILIDADESFICHEROS_H








/* Valida que un fichero de texto contiene exactamente las lineas esperadas, en
   ese orden. Se ignoran las lineas vacias (p. ej. un salto final), de modo que
   la comprobacion es robusta frente al terminador de linea. Devuelve
   BOOL_VAL_CIERTO si coincide, BOOL_VAL_FALSO en caso contrario. */
int FicTxtContenidoCoincide ( const char * p_cRuta, const char ** p_p_cLineas, int iNumLineas );







#endif
