#ifndef _ORG_GJS_C_CC_SLISTAENTIDADESCOD_H
#define _ORG_GJS_C_CC_SLISTAENTIDADESCOD_H







#include <SEntidadCod.h>
#include <SListaPtr.h>



// NOTA: La lista se queda con las entidades: las destruye al eliminar, vaciar, destruir y sustituir.
//       Si una insercion falla, la entidad sigue siendo del llamador.
//       SLisEntCodExtraerElem saca la entidad sin destruirla; pasa a ser del llamador.


typedef struct
{
	SListaPtr * p_lisDatos;

} SListaEntidadesCod;


SListaEntidadesCod * SLisEntCodCrear ();


void SLisEntCodDestruir ( SListaEntidadesCod ** p_p_lisObj );

int SLisEntCodEsValida ( SListaEntidadesCod * p_lisObj );
int SLisEntCodEstaVacia ( SListaEntidadesCod * p_lisObj );

// Operaciones sin cursor:
int SLisEntCodNumElementos ( SListaEntidadesCod * p_lisObj );
SEntidadCod * SLisEntCodElemento ( SListaEntidadesCod * p_lisObj, int iElem );

int SLisEntCodEstablecerElem ( SListaEntidadesCod * p_lisObj, int iElem, SEntidadCod * p_entcDatos );
int SLisEntCodInsertarElem ( SListaEntidadesCod * p_lisObj, int iPosAnt, SEntidadCod * p_entcDatos );
int SLisEntCodInsertarAlInicio ( SListaEntidadesCod * p_lisObj, SEntidadCod * p_entcDatos );
int SLisEntCodInsertarAlFinal ( SListaEntidadesCod * p_lisObj, SEntidadCod * p_entcDatos );

int SLisEntCodEliminarElem ( SListaEntidadesCod * p_lisObj, int iElem );
SEntidadCod * SLisEntCodExtraerElem ( SListaEntidadesCod * p_lisObj, int iElem );

int SLisEntCodVaciar ( SListaEntidadesCod * p_lisObj );

// Operaciones dependientes del cursor:
int SLisEntCodPosicion ( SListaEntidadesCod * p_lisObj );
SEntidadCod * SLisEntCodActual ( SListaEntidadesCod * p_lisObj );

void SLisEntCodInicio ( SListaEntidadesCod * p_lisObj );
void SLisEntCodFinal ( SListaEntidadesCod * p_lisObj );
void SLisEntCodSiguiente ( SListaEntidadesCod * p_lisObj );
void SLisEntCodAnterior ( SListaEntidadesCod * p_lisObj );
void SLisEntCodMoverA ( SListaEntidadesCod * p_lisObj, int iElem );
void SLisEntCodDeposicionar ( SListaEntidadesCod * p_lisObj );

int SLisEntCodEsNulo ( SListaEntidadesCod * p_lisObj );
int SLisEntCodEstaEnFinal ( SListaEntidadesCod * p_lisObj );
int SLisEntCodEstaEnInicio ( SListaEntidadesCod * p_lisObj );

int SLisEntCodEstablecer ( SListaEntidadesCod * p_lisObj, SEntidadCod * p_entcDatos );
int SLisEntCodInsertar ( SListaEntidadesCod * p_lisObj, SEntidadCod * p_entcDatos );
int SLisEntCodInsertarDelante ( SListaEntidadesCod * p_lisObj, SEntidadCod * p_entcDatos );
int SLisEntCodInsertarDetras ( SListaEntidadesCod * p_lisObj, SEntidadCod * p_entcDatos );
int SLisEntCodEliminar ( SListaEntidadesCod * p_lisObj );

// Busqueda por codigo:
int SLisEntCodExiste ( SListaEntidadesCod * p_lisObj, SEntidadCod * p_entcDatos );
int SLisEntCodBuscar ( SListaEntidadesCod * p_lisObj, SEntidadCod * p_entcDatos );
int SLisEntCodExisteCodigo ( SListaEntidadesCod * p_lisObj, SCodigo * p_codEntidad );
int SLisEntCodBuscarCodigo ( SListaEntidadesCod * p_lisObj, SCodigo * p_codEntidad );
int SLisEntCodExisteValorCodigo ( SListaEntidadesCod * p_lisObj, SCadena * p_cadValor );
int SLisEntCodBuscarValorCodigo ( SListaEntidadesCod * p_lisObj, SCadena * p_cadValor );
int SLisEntCodExisteValorCodigoLit ( SListaEntidadesCod * p_lisObj, const char * p_cValor );
int SLisEntCodBuscarValorCodigoLit ( SListaEntidadesCod * p_lisObj, const char * p_cValor );



#endif



