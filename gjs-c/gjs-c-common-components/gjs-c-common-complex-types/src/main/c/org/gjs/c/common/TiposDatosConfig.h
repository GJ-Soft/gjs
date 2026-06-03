

#ifndef _ORG_GJS_C_CC_TIPOSDATOSCONFIG_H
#define _ORG_GJS_C_CC_TIPOSDATOSCONFIG_H








#include <Tipos.h>
#include <Texto.h>
#include <Tiempo.h>



#include <TiposAccion.h>




/* Parametrización de árboles B */
#define ARB_B_MIN_ORDEN           2
#define ARB_B_MAX_ORDEN           50

#define ARB_B_ORDEN_VALIDO         ( ( iOrd >= ARB_B_MIN_ORDEN ) && ( iOrd <= ARB_B_MAX_ORDEN ) )

#define ARB_B_MAX_ELEMS_POR_HOJA     	100
#define ARB_B_NUM_ELEM_POR_HOJA_DEF		30

#define ARB_B_MAX_CLAVES_NODO( iOrd )    2 * iOrd
#define ARB_B_MIN_CLAVES_NODO( iOrd )    iOrd
#define ARB_B_MAX_HIJOS_NODO( iOrd )     ARB_B_MAX_CLAVES_NODO( iOrd ) + 1

#define ARB_B_NUM_CLAVES_RAIZ        1
#define ARB_B_NUM_HIJOS_RAIZ         ARB_B_NUM_CLAVES_RAIZ + 1 
     
		 

/* Operaciones sobres claves: */
#define ARB_B_CLAVE COMP(abcCmp1,abcCmp2) 	memcmp( abcCmp1, abcCmp2, ARB_B_TAM_CLAVE )
#define ARB_B_CLAVE_ASIG(abcDest,abcOrig) 	memcpy( abcDest, abcOrig, ARB_B_TAM_CLAVE )
#define ARB_B_CLAVE_INIC(abcIni)    	 	memset( absInic, 0x0, ARB_B_TAM_CLAVE )


/* Macros para cálcular parámtros en función del orden del árbol. */
#define ARB_B_MAX_HIJOS_POR_NODO( iOrden )  2 * iOrden

#define ARB_B_MAX_PTR_POR_NODO        	ARB_B_MAX_HIJOS_POR_NODO + 1
#define ARB_B_NUM_HOJAS_POR_NODO       	ARB_MAX_HIJOS_POR_NODO    

/* Tipos de árboles B. */
#define ARB_B_TIPO_NORMAL          	0
#define ARB_B_TIPO_MAS          	1
#define ARB_B_TIPO_AST          	2

#define ARB_B_TIPO_VALIDO( iTipo )     ( ( iTipo == ARB_B_TIPO_NORMAL ) || ( iTipo == ARB_B_TIPO_MAS ) || ( iTipo == ARB_B_TIPO_AST ) )


/* Tipo de gestión de posiciones libres en las hojas. */
#define ARB_B_CTL_LIB_NO           0
#define ARB_B_CTL_LIB_SIG          1
#define ARB_B_CTL_LIB_ENC          2
#define ARB_B_CTL_LIB_BMP          3

#define ARB_B_CTL_LIB_VALIDO( iCtl )    ( ( iCtl == ARB_B_CTL_LIB_NO ) || ( iCtl == ARB_B_CTL_LIB_SIG ) || ( iCtl == ARB_B_CTL_LIB_ENC ) || ( iCtl == ARB_B_CTL_LIB_BMP ) ) 


/* Tipo de gestión de la ordenación de los elementos en las hojas. */
#define ARB_B_ORDENACION_NO         0
#define ARB_B_ORDENACION_POS        1
#define ARB_B_ORDENACION_ENC        2

#define ARB_B_ORDENACION_VALIDA( iOrd )   ( ( iOrd == ARB_B_ORDEN_NO ) || ( iOrd == ARB_B_ORDEN_POS ) || ( iOrd == ARB_B_ORDEN_ENC ) )


/* Tipo de apuntadores internos. */
#define ARB_B_APUNT_SIMPLES        0
#define ARB_B_APUNT_DOBLES         1

#define ARB_B_APUNT_VALIDO( iApunt )     ( ( iApunt == ARB_B_APUNT_SIMPLES ) || ( iApunt == ARB_B_APUNT_DOBLES ) )





#endif


