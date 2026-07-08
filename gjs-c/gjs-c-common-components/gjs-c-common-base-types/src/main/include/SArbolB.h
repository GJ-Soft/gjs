/******************************************************************************/
/*  APLICACIÓN:  SMCT                                                         */
/*----------------------------------------------------------------------------*/
/*  MÓDULO:      mt_rc_libs_arbol_b                                           */
/*----------------------------------------------------------------------------*/
/*  FICHERO:     mt_rc_libs_arbol_b.h                                         */
/*----------------------------------------------------------------------------*/
/*  DESCRIPCIÓN: Fichero de cabecera que contiene la definición de los        */
/*               constantes de precompilación, las estructuras de datos       */
/*               y los prototipos de las primitivas que definen el tipo       */
/*               abstracto de datos TArbolB.                                  */
/*               Es un árbol balanceado que admite diferentes variantes       */
/*               ( B+, B*, B ) pudiendo variar el alamcenamiento de las       */
/*               hojas en memoría principal o en disco.                       */
/*----------------------------------------------------------------------------*/
/*  HISTORIA:    ginesjs - Creado el 06/04/2001                               */
/******************************************************************************/

#ifndef _ORG_GJS_C_CC_C_COMMON_ARBOL_B_H
#define _ORG_GJS_C_CC_C_COMMON_ARBOL_B_H

// TODO:
/*
#include "cm_ap_cdefines.h"

#include "mt_rc_libs_macros_aux.h"

#include "mt_rc_libs_arbol_b_param.h"
#include "mt_rc_libs_arbol_b_almacen_hojas.h"

#include "mt_rc_libs_resultado.h"




typedef struct SArbBRaiz
          {
               TARB_B_CLAVE    sclvDiscriminantes [ ARB_B_NUM_CLAVES_RAIZ ];
               TPTR_ARB_B_NODO spabnHijos         [ ARB_B_NUM_HIJOS_RAIZ + 1 ];
               long            lNumClaves;
          } TArbBRaiz;


typedef struct SArbBNodo
          {
               TARB_B_CLAVE    *pclvDiscriminantes;
               TPTR_ARB_B_NODO *ppabnHijos;
               TPTR_ARB_B_NODO pabnSigHermano;
               long            lNumClaves;
          } TArbBNodo;



typedef struct SArbolB
          {
               int             iTipo;
               int             iOrden;
               int             iOrdenacionElems;
               int             iCtlElemsLibres;
               int             iTipoApuntadores;
               int             iTamClave;
               TArbBRaiz       abrRaiz;
               TArbBNodo       *pabnTronco;
               long            lNumNodos;
               long            lNumHojas;
               long            lNumClaves;
               TPTR_ARB_B_NODO pabnSigLibre;
          } TArbolB;




GLOBAL TArbolB *ArbCrear ( int iTipo, int iOrden, int iOrdenacionElems,
                           int iCtlElemsLibres, int iTipoApuntadores,
                           int iTamClave );



GLOBAL TRESULTADO ArbBVacio ( TArbolB *parbObj );
GLOBAL TRESULTADO ArbBInsertar ( TArbolB *parbObj, TARB_B_CLAVE clvElem,
                                 TARB_B_VALOR valElem );



GLOBAL TRESULTADO ArbBConsultar ( TArbolB *parbObj, TARB_B_CLAVE clvElem,
                                  TARB_B_VALOR *pvalElem );
GLOBAL TRESULTADO ArbBModificar ( TArbolB *parbObj, TARB_B_CLAVE clvElem,
                                  TARB_B_VALOR valElem );
GLOBAL TRESULTADO ArbBEliminar ( TArbolB *parbObj, TARB_B_CLAVE clvElem );



GLOBAL TRESULTADO ArbBSeleccionarTodos ( TArbolB *parbObj );
GLOBAL TRESULTADO ArbBSeleccionarRango ( TArbolB *parbObj, TARB_B_CLAVE clvElem1,
                                         TARB_B_CLAVE clvElem2 );
GLOBAL TRESULTADO ArbBSeleccionarFiltro ( TArbolB *parbObj, TARB_B_CLAVE clvFiltro );

GLOBAL TRESULTADO ArbBAnularSeleccion ( TArbolB *parbObj );

GLOBAL TRESULTADO ArbBBuscarPrimero ( TArbolB *parbObj, TARB_B_VALOR *pvalElem );
GLOBAL TRESULTADO ArbBBuscarSiguiente ( TArbolB *parbObj, TARB_B_VALOR *pvalElem );
GLOBAL TRESULTADO ArbBBuscarAnterior ( TArbolB *parbObj, TARB_B_VALOR *pvalElem );
GLOBAL TRESULTADO ArbBBuscarUltimo ( TArbolB *parbObj, TARB_B_VALOR *pvalElem );


GLOBAL TARB_B_CLAVE ArbBValorMaximo ( TArbolB *parbObj );
GLOBAL TARB_B_CLAVE ArbBValorMinimo ( TArbolB *parbObj );
GLOBAL int  ArbBExiste ( TArbolB *parbObj, TARB_B_CLAVE clvElem  );



GLOBAL int  ArbBEsValido ( TArbolB *parbObj );
GLOBAL int  ArbBEstaVacio ( TArbolB *parbObj );
GLOBAL long ArbBNumNodos ( TArbolB *parbObj );
GLOBAL long ArbBNumNiveles ( TArbolB *parbObj );
GLOBAL long ArbBNumClaves ( TArbolB *parbObj );
GLOBAL long ArbBNumHojas ( TArbolB *parbObj );


GLOBAL TRESULTADO ArbBDestruir ( TArbolB **parbObj );


GLOBAL void ArbBImprimir ( TArbolB *parbObj );

*/

#endif

