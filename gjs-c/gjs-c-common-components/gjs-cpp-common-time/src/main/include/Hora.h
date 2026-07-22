/******************************************************************************/
/*                                  Hora.h                                  */
/*----------------------------------------------------------------------------*/
/* Librería:  Tiempo                                                          */
/* Versión:   3.0.0                                                           */
/* Fecha:     25/03/2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Fichero de cabecera que contiene la definición de la clase de datos        */
/* Hora, destinada a almacenar un valor de fecha.                           */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#ifndef _ORG_GJS_C_CC_CPP_HORA_H
#define _ORG_GJS_C_CC_CPP_HORA_H


#include <string>
#include <chrono>


namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {
//PENDIENTE: adaptar para distinguir entre valor formateado y valor numerable,
// especialmente en las comparativas. De momento se trabaja con valores formateados
// subsegundos, duration, mili, micro nano

class Hora
{
private:
     std::chrono::hh_mm_ss<std::chrono::seconds> hmsHora;

public:
	Hora ();
	Hora ( long lValor );
	Hora ( const std::string & sValor );
	Hora ( int iHH, int iMI, int iSS );
	Hora ( const std::chrono::hh_mm_ss<std::chrono::seconds> & hms );
	Hora ( const std::chrono::hours & hh, const std::chrono::minutes & mi, const std::chrono::seconds & ss );
	~Hora();

	void Establecer ( long lValor );
	void Establecer ( const std::string & sValor );
	void Establecer ( int iHH, int iMI, int iSS );
	void Establecer ( const std::chrono::hh_mm_ss<std::chrono::seconds> & hms );
	void Establecer ( const std::chrono::hours & hh, const std::chrono::minutes & mi, const std::chrono::seconds & ss );

	bool EsValida ();

	long Valor ();
	std::string * ValorCadena ();
	std::string * Cadena ( const std::string & formato );

	int HH ();
	int MI ();
	int SS ();

	void EstablecerValorDeAhora ();

	bool EsIgual ( Hora & horValor );
	bool EsMenor ( Hora & horValor );
	bool EsMayor ( Hora & horValor );
	bool EsDiferente ( Hora & horValor );
	bool EsIgual ( Hora * p_horValor );
	bool EsMenor ( Hora * p_horValor );
	bool EsMayor ( Hora * p_horValor );
	bool EsDiferente ( Hora * p_horValor );
	bool EsIgual ( const std::string & sValor );
	bool EsMenor ( const std::string & sValor );
	bool EsMayor ( const std::string & sValor );
	bool EsDiferente ( const std::string & sValor );
	bool EsIgual ( long lValor );
	bool EsMenor ( long lValor );
	bool EsMayor ( long lValor );
	bool EsDiferente ( long lValor );
	bool EsIgual ( const std::chrono::hh_mm_ss<std::chrono::seconds> & hms );
	bool EsMenor ( const std::chrono::hh_mm_ss<std::chrono::seconds> & hms );
	bool EsMayor ( const std::chrono::hh_mm_ss<std::chrono::seconds> & hms );
	bool EsDiferente ( const std::chrono::hh_mm_ss<std::chrono::seconds> & hms );

	long Diferencia ( Hora & horValor );
	long Diferencia ( Hora * p_horValor );
	long Diferencia ( const std::string & sValor );
	long Diferencia ( long lValor );
	long Diferencia ( const std::chrono::hh_mm_ss<std::chrono::seconds> & hms );

public:
	bool operator == ( Hora & horValor );
	bool operator != ( Hora & horValor );
	bool operator > ( Hora & horValor );
	bool operator >= ( Hora & horValor );
	bool operator < ( Hora & horValor );
	bool operator <= ( Hora & horValor );
	bool operator == ( Hora * p_horValor );
	bool operator != ( Hora * p_horValor );
	bool operator > ( Hora * p_horValor );
	bool operator >= ( Hora * p_horValor );
	bool operator < ( Hora * p_horValor );
	bool operator <= ( Hora * p_horValor );
	bool operator == ( const std::string & sValor );
	bool operator != ( const std::string & sValor );
	bool operator > ( const std::string & sValor );
	bool operator >= ( const std::string & sValor );
	bool operator < ( const std::string & sValor );
	bool operator <= ( const std::string & sValor );
	bool operator == ( long lValor );
	bool operator != ( long lValor );
	bool operator > ( long lValor );
	bool operator >= ( long lValor );
	bool operator < ( long lValor );
	bool operator <= ( long lValor );
	bool operator == ( const std::chrono::hh_mm_ss<std::chrono::seconds> & hms );
	bool operator != ( const std::chrono::hh_mm_ss<std::chrono::seconds> & hms );
	bool operator > ( const std::chrono::hh_mm_ss<std::chrono::seconds> & hms );
	bool operator >= ( const std::chrono::hh_mm_ss<std::chrono::seconds> & hms );
	bool operator < ( const std::chrono::hh_mm_ss<std::chrono::seconds> & hms );
	bool operator <= ( const std::chrono::hh_mm_ss<std::chrono::seconds> & hms );

	long operator - ( Hora & horValor );
	long operator - ( Hora * p_horValor );
	long operator - ( const std::string & sValor );
	long operator - ( long lValor );
	long operator - ( const std::chrono::hh_mm_ss<std::chrono::seconds> & hms );

};


 			}
		}
	}
}




#endif


