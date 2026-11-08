#ifndef _ORG_GJS_C_CC_C_COMMON_SLISTA_H
#define _ORG_GJS_C_CC_C_COMMON_SLISTA_H




#include <SElemento.h>
#include <SBloque.h>



typedef struct
{
	SElemento * p_elmPrimero;
	SElemento * p_elmUltimo;
	
	SElemento * p_elmActual;

	int			iPos;
	int			iNumElementos;

} SLista;


SLista * SLisCrear ();


void SLisDestruir ( SLista ** p_p_lisObj );

int SLisEsValida ( SLista * p_lisObj );

// Operaciones sin cursor:
int SLisNumElementos ( SLista * p_lisObj );
int SLisEstaVacia ( SLista * p_lisObj );
SElemento * SLisElemento ( SLista * p_lisObj, int iElem );


// La operativa alta, modificacion, baja altera el cursor
int SLisEstablecerElem ( SLista * p_lisObj, int iElem, SElemento * p_elmObj );
int SLisInsertarElem ( SLista * p_lisObj, int iPosAnt, SElemento * p_elmObj );
int SLisInsertarAlInicio ( SLista * p_lisObj, SElemento * p_elmObj );
int SLisInsertarAlFinal ( SLista * p_lisObj, SElemento * p_elmObj );

int SLisEliminarElem ( SLista * p_lisObj, int iElem );
SElemento * SLisExtraerElem ( SLista * p_lisObj, int iElem );

int SLisVaciar ( SLista * p_lisObj );

// Operaciones dependientes del cursor:
int SLisPosicion ( SLista * p_lisObj );
int SLisEstaPosicionada ( SLista * p_lisObj );
SElemento * SLisActual ( SLista * p_lisObj );

void SLisInicio ( SLista * p_lisObj );
void SLisFinal ( SLista * p_lisObj );
void SLisSiguiente ( SLista * p_lisObj );
void SLisAnterior ( SLista * p_lisObj );
void SLisMoverA ( SLista * p_lisObj, int iElem );
void SLisDeposicionar ( SLista * p_lisObj );

int SLisExisteElem ( SLista * p_lisObj, SElemento * p_elmObj );
int SLisExiste ( SLista * p_lisObj, SBloque * p_blqDatos );
int SLisExisteExt ( SLista * p_lisObj, byte * p_byDatos );
int SLisRepeticionesElem ( SLista * p_lisObj, SElemento * p_elmObj );
int SLisRepeticiones ( SLista * p_lisObj, SBloque * p_blqDatos );
int SLisRepeticionesExt ( SLista * p_lisObj, byte * p_byDatos );

int SLisBuscarElem ( SLista * p_lisObj, SElemento * p_elmObj );
int SLisBuscar ( SLista * p_lisObj, SBloque * p_blqDatos );
int SLisBuscarExt ( SLista * p_lisObj, byte * p_byDatos );
int SLisBuscarPrimeroElem ( SLista * p_lisObj, SElemento * p_elmObj );
int SLisBuscarPrimero ( SLista * p_lisObj, SBloque * p_blqDatos );
int SLisBuscarPrimeroExt ( SLista * p_lisObj, byte * p_byDatos );
int SLisBuscarSiguienteElem ( SLista * p_lisObj, SElemento * p_elmObj, int iPos );
int SLisBuscarSiguiente ( SLista * p_lisObj, SBloque * p_blqDatos, int iPos );
int SLisBuscarSiguienteExt ( SLista * p_lisObj, byte * p_byDatos, int iPos );

int SLisEsNulo ( SLista * p_lisObj );
int SLisEstaEnFinal ( SLista * p_lisObj );
int SLisEstaEnInicio ( SLista * p_lisObj );

int SLisEstablecer ( SLista * p_lisObj, SElemento * p_elmObj );
int SLisInsertar ( SLista * p_lisObj, SElemento * p_elmObj );
int SLisInsertarDelante ( SLista * p_lisObj, SElemento * p_elmObj );
int SLisInsertarDetras ( SLista * p_lisObj, SElemento * p_elmObj );
int SLisEliminar ( SLista * p_lisObj );
SElemento * SLisExtraer ( SLista * p_lisObj );

SLista * SLisDuplicar ( SLista * p_lisObj );

//Operaciones con otras listas
int SLisExistenTodos ( SLista * p_lisObj, SLista * p_lisValores );
int SLisExisteAlguno ( SLista * p_lisObj, SLista * p_lisValores );

// Extrae los valores de la lista de entrada
int SLisInsertarLista ( SLista * p_lisObj, SLista * p_lisValores );
int SLisConcatenarLista ( SLista * p_lisObj, SLista * p_lisValores );
// Duplica los valores de la lista de entrada
int SLisInsertarListaDup ( SLista * p_lisObj, SLista * p_lisValores );
int SLisConcatenarListaDup ( SLista * p_lisObj, SLista * p_lisValores );

int SLisEliminarLista ( SLista * p_lisObj, SLista * p_lisValores );

// Operaciones que generan listas nuevas
// NOTA: Si hay algún error puede realizar una extracción parcial
SLista * SLisExtraerLista ( SLista * p_lisObj, SLista * p_lisValores );

SLista * SLisUnion ( SLista * p_lisValores1, SLista * p_lisValores2 );
SLista * SLisInterseccion ( SLista * p_lisValores1, SLista * p_lisValores2 );
SLista * SLisDiferencia ( SLista * p_lisValores1, SLista * p_lisValores2 );

#endif
