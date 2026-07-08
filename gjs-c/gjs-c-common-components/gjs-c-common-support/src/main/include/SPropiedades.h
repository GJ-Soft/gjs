#ifndef _ORG_GJS_C_CC_C_SPROPIEDADES_H
#define _ORG_GJS_C_CC_C_SPROPIEDADES_H

#include <SListaEntradas.h>
#include <SListaLiterales.h>



typedef struct
{
	SListaLiterales * 	p_lislitClaves;
	SListaEntradas * 	p_lisentPropiedades;
	
} SPropiedades;
 
 
 
SPropiedades * SPropCrearDef ();
SPropiedades * SPropCrear ( const char * p_cRuta );
void SPropDestruir ( SPropiedades ** p_p_propObj );

const char * SPropObtPropiedad ( SPropiedades * p_propObj, const char * p_cClave );
const char * SPropObtPropiedadExt ( SPropiedades * p_propObj, const char * p_cClave, const char * p_cValorDef );
int SPropEstPropiedad ( SPropiedades * p_propObj, const char * p_cClave, const char * p_cValor );

SListaLiterales * SPropPropiedades ( SPropiedades * p_propObj ) ;
int SPropExistePropiedad ( SPropiedades * p_propObj, const char * p_cClave );
int SPropNumPropiedades ( SPropiedades * p_propObj );

void SPropEliminarPropiedad ( SPropiedades * p_propObj, const char * p_cClave );

int SPropCargar ( SPropiedades * p_propObj, const char * p_cRuta );
int SPropGuardar (  SPropiedades * p_propObj, const char * p_cRuta );



#endif
