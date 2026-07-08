/***************************************************************************/
/*                         SGeneradorId.h                                  */
/*-------------------------------------------------------------------------*/
/* Librería:  TiposDatos                                                   */
/* Versión:   3.0.0                                                        */
/* Fecha:     25/03/2008                                                   */
/* Autor:     Ginés Jiménez Sánchez                                        */
/*-------------------------------------------------------------------------*/
/* Descripción:                                                            */
/* Fichero de cabecera que contiene la definición de la clase de datos     */
/* SGeneradorId, destinada a gestionar la producción de identificadorec    */
/* únicos dentro de una aplicación.                                        */
/*-------------------------------------------------------------------------*/
/***************************************************************************/

#ifndef _ORG_GJS_C_CC_C_COMMON_SGENERADORID_H
#define _ORG_GJS_C_CC_C_COMMON_SGENERADORID_H













typedef struct
{
	unsigned long	ulIdInicial;
	unsigned long	ulIdFinal;
	unsigned long	ulUltimoId;

}  SGeneradorId;




SGeneradorId * SGenIdCrear ( unsigned long ulIdInicial, unsigned long ulUltimoId, unsigned long ulIdFinal );
SGeneradorId * SGenIdCrearDef ();

void SGenIdDestruir ( SGeneradorId ** p_p_genidObj );

unsigned long SGenIdInicial ( SGeneradorId * p_genidObj );
unsigned long SGenIdFinal ( SGeneradorId * p_genidObj );
unsigned long SGenIdUltimo ( SGeneradorId * p_genidObj );
unsigned long SGenIdSig ( SGeneradorId * p_genidObj );
unsigned long SGenIdAsignarSig ( SGeneradorId * p_genidObj );

int SGenIdEsValido ( SGeneradorId * p_genidObj );

int SGenIdIniciar ( SGeneradorId * p_genidObj );

int SGenIdEsIgual ( SGeneradorId * p_genidObj, SGeneradorId * p_genidValor );

SGeneradorId * SGenIdDuplicar ( SGeneradorId * p_genidObj );

#endif
