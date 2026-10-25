#ifndef _ORG_GJS_C_CC_SCONJUNTOENTIDADESCOD_H
#define _ORG_GJS_C_CC_SCONJUNTOENTIDADESCOD_H








#include <SConjuntoPtr.h>
#include <SEntidadCod.h>



// NOTA: El conjunto se queda con las entidades: las destruye al eliminar, vaciar y destruir.
//       Ordena por codigo y no admite codigos repetidos. Si una insercion falla, la entidad
//       sigue siendo del llamador.
//       SCnjEntCodExtraer saca la entidad sin destruirla; pasa a ser del llamador.


typedef struct
{
	SConjuntoPtr * p_cnjDatos;

} SConjuntoEntidadesCod;





SConjuntoEntidadesCod * SCnjEntCodCrear ();


void SCnjEntCodDestruir ( SConjuntoEntidadesCod ** p_p_cnjObj );

int SCnjEntCodEsValido ( SConjuntoEntidadesCod * p_cnjObj );

int SCnjEntCodNumElementos ( SConjuntoEntidadesCod * p_cnjObj );
int SCnjEntCodEstaVacio ( SConjuntoEntidadesCod * p_cnjObj );

SEntidadCod * SCnjEntCodElemento ( SConjuntoEntidadesCod * p_cnjObj, int iElem );
SEntidadCod * SCnjEntCodPrimero ( SConjuntoEntidadesCod * p_cnjObj );
SEntidadCod * SCnjEntCodUltimo ( SConjuntoEntidadesCod * p_cnjObj );
int SCnjEntCodPosicion ( SConjuntoEntidadesCod * p_cnjObj, SEntidadCod * p_entcDato );

int SCnjEntCodInsertar ( SConjuntoEntidadesCod * p_cnjObj, SEntidadCod * p_entcDato );
int SCnjEntCodEliminar ( SConjuntoEntidadesCod * p_cnjObj, int iElem );
SEntidadCod * SCnjEntCodExtraer ( SConjuntoEntidadesCod * p_cnjObj, int iElem );
int SCnjEntCodVaciar ( SConjuntoEntidadesCod * p_cnjObj );

int SCnjEntCodExiste ( SConjuntoEntidadesCod * p_cnjObj, SEntidadCod * p_entcDato );
int SCnjEntCodBuscar ( SConjuntoEntidadesCod * p_cnjObj, SEntidadCod * p_entcDato );
int SCnjEntCodExisteCodigo ( SConjuntoEntidadesCod * p_cnjObj, SCodigo * p_codEntidad );
int SCnjEntCodBuscarCodigo ( SConjuntoEntidadesCod * p_cnjObj, SCodigo * p_codEntidad );
int SCnjEntCodExisteValorCodigo ( SConjuntoEntidadesCod * p_cnjObj, SCadena * p_cadValor );
int SCnjEntCodBuscarValorCodigo ( SConjuntoEntidadesCod * p_cnjObj, SCadena * p_cadValor );
int SCnjEntCodExisteValorCodigoLit ( SConjuntoEntidadesCod * p_cnjObj, const char * p_cValor );
int SCnjEntCodBuscarValorCodigoLit ( SConjuntoEntidadesCod * p_cnjObj, const char * p_cValor );

#endif
