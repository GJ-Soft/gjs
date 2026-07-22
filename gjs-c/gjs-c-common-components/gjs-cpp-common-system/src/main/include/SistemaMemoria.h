/******************************************************************************/
/*                              SistemaMemoria.h                              */
/*----------------------------------------------------------------------------*/
/* Librería:  Sistema                                                         */
/* Versión:   3.0.0                                                           */
/* Fecha:     25/03/2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Fichero de cabecera que contiene los prototipos de algunas rutinas de      */
/* de carácter general de reserva y liberación de espacios de memoria.        */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#ifndef _ORG_GJS_C_CC_CPP_SISTEMAMEMORIA_H
#define _ORG_GJS_C_CC_CPP_SISTEMAMEMORIA_H




namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {






unsigned long long SisMemoriaTotal ();
unsigned long long SisMemoriaDisponible ();
unsigned long long SisMemoriaOcupada ();

double SisMemoriaDisponiblePorc ();
double SisMemoriaOcupadaPorc ();

unsigned long long SisMemoriaFisicaTotal ();
unsigned long long SisMemoriaFisicaDisponible ();
unsigned long long SisMemoriaFisicaOcupada ();

unsigned long long SisMemoriaFicPaginacionTotal ();
unsigned long long SisMemoriaFicPaginacionDisponible ();
unsigned long long SisMemoriaFicPaginacionOcupada ();

unsigned long long SisMemoriaHeapTotal ();
unsigned long long SisMemoriaHeapMin ();
unsigned long long SisMemoriaHeapMax ();


 			}
		}
	}
}


#endif




