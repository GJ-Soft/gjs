/******************************************************************************/
/*  APLICACIÓN:  SMCT                                                         */
/*----------------------------------------------------------------------------*/
/*  MÓDULO:      mt_rc_libs_arbol_b                                           */
/*----------------------------------------------------------------------------*/
/*  FICHERO:     mt_rc_libs_arbol_b.c                                         */
/*----------------------------------------------------------------------------*/
/*  DESCRIPCIÓN: Implementación del tipo abstracto de datos TArbolB.          */
/*----------------------------------------------------------------------------*/
/*  HISTORIA:    ginesjs - Creado el 06/04/2001                               */
/******************************************************************************/


#include "TiposBasicosConfig.h"


/*
TODO:
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "cm_ap_libs_local.h"
#include "mt_rc_libs_arbol_b.h"




LOCAL void ArbBNodoInicializar ( TArbBNodo *pabnObj )
{
     long lClave;

     if ( pabnObj != NULL )
     {
          for ( lClave = 0; lClave < ARB_B_MAX_HIJOS_POR_NODO;
                lCalve = lClave + 1 )
          {
               pabnObj->sclvDiscriminante [ lClave ] = ARB_B_CLAVE_NULA;
               pabnObj->spabnHijos        [ lClave ] = ARB_B_NODO_NULO;
          }
          pabhObj->pabnSigHermano = ARB_B_NODO_NULO;
          pabhObj->lNumClaves = 0;
     }
}


LOCAL int ArbBNodoVacio ( TArbBNodo *pabnObj )
{
     int iRet;

     if ( pabnObj != NULL )
     {
          if ( pabnObj->lNumClaves == 0 )
          {
               iRet = TRUE;
          }
          else
          {
               iRet = FALSE;
          }
     }
     else
     {
          iRet = FALSE;
     }
     return ( iRet );
}


LOCAL int ArbBNodoCompleto ( TArbBNodo *pabnObj )
{
     int iRet;

     if ( pabnObj != NULL )
     {
          if ( pabnObj->lNumClaves >= ARB_B_MAX_HIJOS_POR_NODO )
          {
               iRet = TRUE;
          }
          else
          {
               iRet = FALSE;
          }
     }
     else
     {
          iRet = FALSE;
     }
     return ( iRet );
}


LOCAL TPTR_ARB_B_NODO ArbBNodoBuscar ( TArbBNodo *pabnObj, TARB_B_CLAVE clvBus )
{
     int             iEnc;
     long            lClave;
     TPTR_ARB_B_NODO pabnSig;

     if ( pabnObj != NULL )
     {
          if ( pabnObj->lNumClaves > 0 )
          {
               if ( clvBus < pabnObj->sclvDiscriminantes [ 0 ] )
               {
                    pabnSig = pabnObj->spabnHijos [ 0 ];
               }
               else
               {
                    lClave = 1;
                    iEnc = FALSE;
                    while ( ( lClave < pabnObj->lNumClaves ) && ( iEnc == FALSE ) )
                    {
                         if ( clvBus <= pabnObj->sclvDiscriminantes [ lClave ] )
                         {
                              pabnSig = pabnObj->spabnHijos [ lClave ];
                              iEnc = TRUE;
                         }
                         lClave = lClave + 1;
                    }

                    if ( iEnc == FALSE )
                    {
                         pabnSig = pabnObj->pabnSigHermano;
                    }
               }
          }
          else
          {
               pabeElem = ARB_B_ELEM_NULO;
          }
     }
     else
     {
          pabeElem = ARB_B_ELEM_NULO;
     }
     return ( pabeElem );
}



LOCAL TPTR_ARB_B_NODO ArbBSigLibre( TArbolB *parbObj )
{
     long            lRet;
     TPTR_ARB_B_NODO pabnNodoAct;

     if ( parbObj != NULL )
     {

          if ( parbObj->lNumNodos < ARB_B_MAX_NODOS )
          {
               lRet = TRUE;
               if ( ! ARB_B_NODO_CORRECTO ( parbObj->pabnSigLibre ) )
               {
                    parbObj->pabnSigLibre = 0;
               }
               else
               {
                    parbObj->pabnSigLibre =
                              ARB_B_NODO_INC_CIR ( parbObj->pabnSigLibre );
               }
               pabnNodoAct = parbObj->pabnSigLibre;

               while ( ( parbObj->sabnJerarquia[ parbObj->pabnSigLibre ].lNumClaves
                         <= 0 ) ) &&
                       ( lRet == TRUE ) )
               {
                    parbObj->pabnSigLibre =
                              ARB_B_NODO_INC_CIR ( parbObj->pabnSigLibre );
                    if ( parbObj->pabnSigLibre == pabnNodoAct )
                    {
                         parbObj->ptnSigLibre = ARB_B_NODO_NULO;
                         lRet = FALSE;
                    }
               }
          }
          else
          {
               parbObj->ptnSigLibre = ARB_B_NODO_NULO;
               lRet = FALSE;
          }
     }
     else
     {
          lRet = FALSE;
     }
     return ( lRet );
}



GLOBAL TArbolB *ArbCrear ( TArbolB *parbObj, int iTipo, int iOrden, int iOrdenacionElems,
                           int iCtlElemsLibres, int iTipoApuntadores,
                           int iTamClave )
{
     TArbolB         *parbObj;


     if ( ARB_B_TIPO_VALIDO ( iTipo ) && ARB_B_CTL_LIB_VALIDO ( iCtlElemsLibres ) &&
          ARB_B_ORDENACION_VALIDA ( iOrdenacionElems ) &&
     if ( parbObj != NULL )
     {
          parbAux = parbObj;
     }
     else
     {
          parbAux = (TArbolB *) malloc ( sizeof ( TArbolB ) );
     }

     if ( parbAux != NULL )
     {
          parbAux->iTipo = iTipo;
          ArbBVacio ( parbAux );
          return ( parbAux );
     }
     else
     {
          return ( NULL );
     }
}



GLOBAL TRESULTADO  ArbBVacio ( TArbolB *parbObj )
{
     TRESULTADO      resInfo;
     TPTR_ARB_B_NODO pabnNodo;
     TPTR_ARB_B_HOJA pabhHoja;

     if ( parbObj != NULL )
     {
          parbObj->lNumNodos = 0;
          parbObj->lNumHojas = 0;
          parbObj->pabnRaiz = ARB_B_NODO_NULO;
          parbObj->pabnSigLibre = 0;

          for ( pabnNodo = ARB_B_NODO_PRIMERO; pabnNodo <= ARB_B_NODO_ULTIMO;
                pabnNodo = ARB_B_NODO_INC ( pabnNodo ) )
          {
               ArbBNodoVaciar ( &( parbObj->sabnJerarquia [ ptnNodo ] ) );
          }
          resInfo = ARB_B_RES_OPE_REALIZADA;
     }
     else
     {
          resInfo = ARB_B_RES_ERR_ESTRUCTURA;
     }
     return ( resInfo );
}


GLOBAL TRESULTADO ArbBInsertar ( TArbolB *parbObj, TARB_B_CLAVE clvElem,
                                 TARB_B_VALOR valElem )
{
     TRESULTADO            resInfo;
     TArbBNodo             *pnabIns;
     TPTR_ARB_B_NODO       ptaPadre;
     TPTR_ARB_B_NODO       ptnNodo;
     TPTR_ARB_B_NODO       ptaDeseq;

     if ( parbObj != NULL )
     {
          if ( parbObj->ptnSigLibre != ARB_B_NODO_NULO )
          {
          }
     }
     else
     {
          resInfo = ARB_B_RES_ERR_ESTRUCTURA;
     }
     return ( resInfo );
}


GLOBAL TRESULTADO ArbBConsultar ( TArbolB *parbObj, TARB_B_CLAVE clvElem,
                                  TARB_B_VALOR *pvalElem )
{
     TRESULTADO resInfo;
     TPTR_ARB_B_NODO ptnNodo;
     TPTR_ARB_B_NODO ptaPadre;

     if ( ( parbObj != NULL ) && ( pvalElem != NULL ) )
     {
     }
     else
     {
          resInfo = ARB_B_RES_ERR_ESTRUCTURA;
     }
     return ( resInfo );
}


GLOBAL TRESULTADO ArbBModificar ( TArbolB *parbObj, TARB_B_CLAVE clvElem,
                                  TARB_B_VALOR valElem )
{
     TRESULTADO      resInfo;
     TPTR_ARB_B_NODO ptnNodo;
     TPTR_ARB_B_NODO ptaPadre;

     if ( parbObj != NULL )
     {
     }
     else
     {
          resInfo = ARB_B_RES_ERR_ESTRUCTURA;
     }
     return ( resInfo );
}


GLOBAL TRESULTADO ArbBEliminar ( TArbolB *parbObj, TARB_B_CLAVE clvElem )
{
     TRESULTADO      resInfo;
     TPTR_ARB_B_NODO ptnNodo;
     TPTR_ARB_B_NODO ptaSubarbolDer;
     TPTR_ARB_B_NODO ptaSubarbolIzq;
     TPTR_ARB_B_NODO ptnNodoSust;
     TPTR_ARB_B_NODO ptaPadre;
     TPTR_ARB_B_NODO ptaDeseq;

     if ( parbObj != NULL )
     {
          if ( parbObj->lNumNodos > 0 )
          {
          }
          else
          {
               resInfo = ARB_B_RES_ERR_NO_EXISTE;
          }
     }
     else
     {
          resInfo = ARB_B_RES_ERR_ESTRUCTURA;
     }
     return ( resInfo );
}



GLOBAL TARB_B_CLAVE ArbBValorMaximo ( TArbolB *parbObj )
{
     long    lRes;

     if ( parbObj == NULL )
     {
          lRes = FALSE;
     }
     else
     {
          lRes = TRUE;
     }
     return ( lRes );
}


GLOBAL TARB_B_CLAVE ArbBValorMinimo ( TArbolB *parbObj )
{
     long    lRes;

     if ( parbObj == NULL )
     {
          lRes = FALSE;
     }
     else
     {
          lRes = TRUE;
     }
     return ( lRes );
}


GLOBAL int ArbBExiste ( TArbolB *parbObj, TARB_B_CLAVE clvElem  )
{
     long    lRes;
     TPTR_ARB_B_NODO ptaPadre;

     if ( ( parbObj == NULL ) && ( clvElem == NULL ) )
     {
          lRes = FALSE;
     }
     else
     {
          if ( parbObj->lNumNodos <=0 )
          {
                lRes = FALSE;
          }
          else
          {

          //     if ( ARB_B_NODO_CORRECTO ( ArbBuscarPosicion ( parbObj, pbyClave,
         //                                                   lTamClave, &ptaPadre,
                                                           &abdNodo ) ) )
         //       {
          //           lRes = TRUE;
         //       }
         //       else
         //       {
         //            lRes = FALSE;
          //      }

         }
     }
     return ( lRes );
}



GLOBAL long ArbBEsvalido ( TArbolB *parbObj )
{
     long lRes;

     if ( parbObj == NULL )
     {
          lRes = FALSE;
     }
     else
     {
          if ( ( parbObj->lNumNodos > 0 ) && ( parbObj->lNumNodos <= ARB_B_MAX_NODOS ) )
          {
               lRes = TRUE;
          }
     }
     return ( lRes );
}


GLOBAL int ArbBEstaVacio ( TArbolB *parbObj )
{
     int iRes;

     if ( parbObj == NULL )
     {
          iRes = FALSE;
     }
     else
     {
          if ( parbObj->ptnRaiz == ARB_B_NODO_NULO )
          {
               iRes = TRUE;
          }
          else
          {
               iRes = FALSE;
          }
     }
     return ( iRes );
}



GLOBAL long ArbBNumNodos ( TArbolB *parbObj )
{
     long    lRes;

     if ( parbObj == NULL )
     {
          lRes = FALSE;
     }
     else
     {
          lRes = TRUE;
     }
     return ( lRes );
}


GLOBAL long ArbBNumNiveles ( TArbolB *parbObj )
{
     long    lRes;

     if ( parbObj == NULL )
     {
          lRes = FALSE;
     }
     else
     {
          lRes = TRUE;
     }
     return ( lRes );
}


GLOBAL long ArbBNumClaves ( TArbolB *parbObj )
{
     long    lRes;

     if ( parbObj == NULL )
     {
          lRes = FALSE;
     }
     else
     {
          lRes = TRUE;
     }
     return ( lRes );
}




GLOBAL void ArbBDestruir ( TArbolB **pparbObj )
{
     TArbolB     *parbObj;

     if ( pparbObj != NULL )
     {
             if ( *pparbObj != NULL )
             {
               parbObj = *pparbObj;
               free ( parbObj );
               *pparbObj = NULL;
          }
     }
}

*/

