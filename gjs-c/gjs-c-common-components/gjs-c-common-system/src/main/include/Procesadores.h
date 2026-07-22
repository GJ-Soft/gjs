/******************************************************************************/
/*                               Procesadores.h                               */
/*----------------------------------------------------------------------------*/
/* Libreria:  Sistema                                                         */
/* Version:   3.0.0                                                           */
/* Fecha:     25/03/2008                                                      */
/* Autor:     Gines Jimenez Sanchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripcion:                                                               */
/* Fichero de cabecera que contiene la definicion de los diferentes tipos     */
/* de procesador reconocidos.                                                 */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#ifndef _ORG_GJS_C_CC_PROCESADORES_H
#define _ORG_GJS_C_CC_PROCESADORES_H




#define PROC_DESCONOCIDO					-1


#define PROC_INTEL_8086						0
#define PROC_INTEL_8088						1
#define PROC_INTEL_80286					2
#define PROC_INTEL_80386					3
#define PROC_INTEL_80486					4
#define PROC_INTEL_PENTIUM					5

#define PROC_INTEL_PENTIUM_PRO				6
#define PROC_INTEL_PENTIUM_II				7
#define PROC_INTEL_PENTIUM_III				8
#define PROC_INTEL_PENTIUM_4				9
#define PROC_INTEL_CORE						10		// Core / Core2 / Core iX / Xeon / Atom ( familia 6 moderna )
#define PROC_INTEL							49		// Intel x86 no clasificado

#define PROC_AMD							50		// AMD x86
#define PROC_AMD_64							51		// AMD x86-64 ( Athlon 64 / Opteron / Ryzen ... )

#define PROC_X86							100		// x86 generico ( otro fabricante )
#define PROC_X86_64							101		// x86-64 generico

#define PROC_ARM							500
#define PROC_ARM64							501

#define PROC_MIPS_R4000						200

#define PROC_ALPHA_21064					300
#define PROC_ALPHA_21066					301
#define PROC_ALPHA_21164					302

#define PROC_PPC_601						400
#define PROC_PPC_603						401
#define PROC_PPC_604						402
#define PROC_PPC_603_PLUS					403
#define PROC_PPC_604_PLUS					404
#define PROC_PPC_620						405




#endif
