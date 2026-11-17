#ifndef _ORG_GJS_C_CC_SSECUENCIAID_H
#define _ORG_GJS_C_CC_SSECUENCIAID_H








#include <SSecuencia.h>
#include <SId.h>



/* Secuencia de identificadores, en orden de insercion y con repetidos. No
   guarda los SId: guarda una copia de su contenido ( SIdBloqueBin ). El
   llamante sigue siendo dueño de los SId que pasa, y es dueño de los que
   devuelve SSecIdElemento. */
typedef struct
{
	SSecuencia * p_secDatos;

} SSecuenciaId;


SSecuenciaId * SSecIdCrear ();


void SSecIdDestruir ( SSecuenciaId ** p_p_secObj );

int SSecIdEsValida ( SSecuenciaId * p_secObj );
int SSecIdEstaVacia ( SSecuenciaId * p_secObj );

int SSecIdNumElementos ( SSecuenciaId * p_secObj );
int SSecIdExiste ( SSecuenciaId * p_secObj, SId * p_idDato );
int SSecIdBuscar ( SSecuenciaId * p_secObj, SId * p_idDato );
int SSecIdRepeticiones ( SSecuenciaId * p_secObj, SId * p_idDato );
int SSecIdBuscarPrimero ( SSecuenciaId * p_secObj, SId * p_idDato );
int SSecIdBuscarSiguiente ( SSecuenciaId * p_secObj, SId * p_idDato, int iPos );
int SSecIdExisteExt ( SSecuenciaId * p_secObj, unsigned long ulDato );
int SSecIdBuscarExt ( SSecuenciaId * p_secObj, unsigned long ulDato );
int SSecIdRepeticionesExt ( SSecuenciaId * p_secObj, unsigned long ulDato );
int SSecIdBuscarPrimeroExt ( SSecuenciaId * p_secObj, unsigned long ulDato );
int SSecIdBuscarSiguienteExt ( SSecuenciaId * p_secObj, unsigned long ulDato, int iPos );

SId * SSecIdElemento ( SSecuenciaId * p_secObj, int iElem );
unsigned long SSecIdValorElemento ( SSecuenciaId * p_secObj, int iElem );

int SSecIdInsertar ( SSecuenciaId * p_secObj, SId * p_idDato );
int SSecIdInsertarExt ( SSecuenciaId * p_secObj, unsigned long ulDato );

int SSecIdEliminarElem ( SSecuenciaId * p_secObj, int iElem );

int SSecIdVaciar ( SSecuenciaId * p_secObj );

SSecuencia * SSecIdSecuencia ( SSecuenciaId * p_secObj );


#endif
