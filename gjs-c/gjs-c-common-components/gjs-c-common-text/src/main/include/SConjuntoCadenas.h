#ifndef _ORG_GJS_C_CC_SCONJUNTOCADENAS_H
#define _ORG_GJS_C_CC_SCONJUNTOCADENAS_H








#include <SConjuntoPtr.h>
#include <SCadena.h>



// NOTA: El conjunto se queda con las cadenas: las destruye al eliminar, vaciar y destruir.
//       SCnjCadInsertar toma la cadena dada; si no la inserta (duplicada), sigue siendo del llamador.
//       SCnjCadInsertarDup inserta una copia; la original sigue siendo del llamador.
//       SCnjCadExtraer saca la cadena sin destruirla; pasa a ser del llamador.


typedef struct
{
	SConjuntoPtr * p_cnjDatos;

} SConjuntoCadenas;





SConjuntoCadenas * SCnjCadCrear ();


void SCnjCadDestruir ( SConjuntoCadenas ** p_p_cnjObj );

int SCnjCadEsValido ( SConjuntoCadenas * p_cnjObj );

int SCnjCadNumElementos ( SConjuntoCadenas * p_cnjObj );
int SCnjCadEstaVacio ( SConjuntoCadenas * p_cnjObj );

SCadena * SCnjCadElemento ( SConjuntoCadenas * p_cnjObj, int iElem );
SCadena * SCnjCadPrimero ( SConjuntoCadenas * p_cnjObj );
SCadena * SCnjCadUltimo ( SConjuntoCadenas * p_cnjObj );
int SCnjCadPosicion ( SConjuntoCadenas * p_cnjObj, SCadena * p_cadDato );

int SCnjCadInsertar ( SConjuntoCadenas * p_cnjObj, SCadena * p_cadDato );
int SCnjCadInsertarDup ( SConjuntoCadenas * p_cnjObj, SCadena * p_cadDato );
int SCnjCadEliminar ( SConjuntoCadenas * p_cnjObj, int iElem );
SCadena * SCnjCadExtraer ( SConjuntoCadenas * p_cnjObj, int iElem );
int SCnjCadVaciar ( SConjuntoCadenas * p_cnjObj );

int SCnjCadExiste ( SConjuntoCadenas * p_cnjObj, SCadena * p_cadDato );
int SCnjCadBuscar ( SConjuntoCadenas * p_cnjObj, SCadena * p_cadDato );

#endif