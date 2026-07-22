/******************************************************************************/
/*                               ASCIIOEM850.h                                */
/*----------------------------------------------------------------------------*/
/* Librería:  GTexto                                                          */
/* Versión:   1.0.0                                                           */
/* Fecha:     30/06/2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Fichero de cabecera que contiene la definición de constantes para los      */
/* carácteres del específioos del código ASCII correspondientes al juego      */
/* carácteres OEM850.                                                         */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#ifndef _ORG_GJS_C_CC_ASCIIOEM850_H
#define _ORG_GJS_C_CC_ASCIIOEM850_H



// Códigos no estándar fijos para páginas de códigos preparadas para 
// idioma español (128-255):

// Signos de englobamiento:
#define ASCII_EXCLAMACION_ABR 	173
#define ASCII_INTERROGACION_ABR	168

// Acentos:
#define ASCII_ACENTO_CER		239
#define ASCII_DIERESIS			248


// Monedas:
#define ASCII_EURO				-1
#define ASCII_CENTIMO			189
#define ASCII_LIBRA				163
#define ASCII_YEN				190
#define ASCII_DIVISA			207


// Letras mayúsculas:
#define ASCII_N_MAY_TIL	 		165
#define ASCII_C_MAY_CED			128


// Letras minúsculas:
#define ASCII_N_MIN_TIL			164
#define ASCII_C_MIN_CED			135



// Letrás mayúsculas acentuadas:
#define ASCII_A_MAY_ABI			183
#define ASCII_E_MAY_ABI			138
#define ASCII_I_MAY_ABI 		141
#define ASCII_O_MAY_ABI 		149
#define ASCII_U_MAY_ABI 		151

#define ASCII_A_MAY_CER			181
#define ASCII_E_MAY_CER 		144
#define ASCII_I_MAY_CER 		161
#define ASCII_O_MAY_CER  		162
#define ASCII_U_MAY_CER 		163

#define ASCII_A_MAY_CIR			131
#define ASCII_E_MAY_CIR			136
#define ASCII_I_MAY_CIR 		140
#define ASCII_O_MAY_CIR 		147
#define ASCII_U_MAY_CIR 		150

#define ASCII_A_MAY_DIE			142
#define ASCII_E_MAY_DIE			-1
#define ASCII_I_MAY_DIE			-1
#define ASCII_O_MAY_DIE 		153
#define ASCII_U_MAY_DIE 		154

#define ASCII_A_MAY_TIL			199
#define ASCII_E_MAY_TIL			-1
#define ASCII_I_MAY_TIL 		-1
#define ASCII_O_MAY_TIL 		229
#define ASCII_U_MAY_TIL 		-1

#define ASCII_Y_MAY_DIE 		-1

#define ASCII_A_MAY_ANI 		143


// Letrás minúsculas acentuadas:
#define ASCII_A_MIN_ABI			133
#define ASCII_E_MIN_ABI			138
#define ASCII_I_MIN_ABI 		141
#define ASCII_O_MIN_ABI 		149
#define ASCII_U_MIN_ABI 		151

#define ASCII_A_MIN_CER			160
#define ASCII_E_MIN_CER			130
#define ASCII_I_MIN_CER 		161
#define ASCII_O_MIN_CER  		162
#define ASCII_U_MIN_CER 		163

#define ASCII_A_MIN_CIR			131
#define ASCII_E_MIN_CIR			136
#define ASCII_I_MIN_CIR 		140
#define ASCII_O_MIN_CIR 		147
#define ASCII_U_MIN_CIR 		150

#define ASCII_A_MIN_DIE  		132
#define ASCII_E_MIN_DIE			137
#define ASCII_I_MIN_DIE 		139
#define ASCII_O_MIN_DIE 		148
#define ASCII_U_MIN_DIE			129

#define ASCII_A_MIN_TIL			198
#define ASCII_E_MIN_TIL			-1
#define ASCII_I_MIN_TIL 		-1
#define ASCII_O_MIN_TIL 		224
#define ASCII_U_MIN_TIL 		-1

#define ASCII_Y_MIN_DIE 		152

#define ASCII_A_MIN_ANI			134


// Letras especiales:
#define ASCII_AE_MIN			145
#define ASCII_AE_MAY			146

#define ASCII_O_MIN_BAR			155
#define ASCII_O_MAY_BAR			157

#define ASCII_ETH_MIN			208
#define ASCII_ETH_MAY			209
#define ASCII_THORN_MIN			231
#define ASCII_THORN_MAY			232

#define ASCII_BETA_MIN			225
#define ASCII_MU_MIN			230
#define ASCII_BETA_MAY			-1
#define ASCII_MU_MAY			-1


// Otros signos:
#define ASCII_ORDINAL_FEM		166
#define ASCII_ORDINAL_MAS		167

#define ASCII_MULTIPLICADOR		158
#define ASCII_DIVISOR			246
#define ASCII_FUNCION			159

#define ASCII_MARCA_REG			169
#define ASCII_DERECHOS_AUT		184

#define ASCII_NEGACION			170

#define ASCII_FRACCION_1_2		171
#define ASCII_FRACCION_1_4		172
#define ASCII_FRACCION_3_4		243

#define ASCII_DOBLE_MENOR		174
#define ASCII_DOBLE_MAYOR		175

#define ASCII_BARRA_ALTA		237		
#define ASCII_BARR_MEDIA		239
#define ASCII_BARRA_VERTICAL	221
#define ASCII_DOBLE_BARRA_BAJA	240

#define ASCII_MAS_MENOS			239

#define ASCII_PARAGRAFO			244
#define ASCII_SECCION			245

#define ASCII_SUPERINDICE_1		251
#define ASCII_SUPERINDICE_2		252
#define ASCII_SUPERINDICE_3		253

#define ASCII_GRADO				248

#define ASCII_PUNTO_MEDIO		250	

#define ASCII_ESPACIO_2			255


#endif



