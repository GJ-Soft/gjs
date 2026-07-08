/******************************************************************************/
/*                                  CHora.h                                  */
/*----------------------------------------------------------------------------*/
/* Librería:  Tiempo                                                          */
/* Versión:   3.0.0                                                           */
/* Fecha:     25/03/2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Fichero de cabecera que contiene la definición de la clase de datos        */
/* CHora, destinada a almacenar un valor de fecha.                           */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#ifndef _ORG_GJS_C_CC_CPP_CHORA_H
#define _ORG_GJS_C_CC_CPP_CHORA_H


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

class CHora
{
private:
     std::chrono::hh_mm_ss<std::chrono::seconds> hmsHora;

public:
	CHora ();
	CHora ( long lValor );
	CHora ( const std::string & sValor );
	CHora ( int iHH, int iMI, int iSS );
	CHora ( const std::chrono::hh_mm_ss<std::chrono::seconds> & hms );
	CHora ( const std::chrono::hours & hh, const std::chrono::minutes & mi, const std::chrono::seconds & ss );
	~CHora();

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

	bool EsIgual ( CHora & horValor );
	bool EsMenor ( CHora & horValor );
	bool EsMayor ( CHora & horValor );
	bool EsDiferente ( CHora & horValor );
	bool EsIgual ( CHora * p_horValor );
	bool EsMenor ( CHora * p_horValor );
	bool EsMayor ( CHora * p_horValor );
	bool EsDiferente ( CHora * p_horValor );
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

	long Diferencia ( CHora & horValor );
	long Diferencia ( CHora * p_horValor );
	long Diferencia ( const std::string & sValor );
	long Diferencia ( long lValor );
	long Diferencia ( const std::chrono::hh_mm_ss<std::chrono::seconds> & hms );

public:
	bool operator == ( CHora & horValor );
	bool operator != ( CHora & horValor );
	bool operator > ( CHora & horValor );
	bool operator >= ( CHora & horValor );
	bool operator < ( CHora & horValor );
	bool operator <= ( CHora & horValor );
	bool operator == ( CHora * p_horValor );
	bool operator != ( CHora * p_horValor );
	bool operator > ( CHora * p_horValor );
	bool operator >= ( CHora * p_horValor );
	bool operator < ( CHora * p_horValor );
	bool operator <= ( CHora * p_horValor );
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

	long operator - ( CHora & horValor );
	long operator - ( CHora * p_horValor );
	long operator - ( const std::string & sValor );
	long operator - ( long lValor );
	long operator - ( const std::chrono::hh_mm_ss<std::chrono::seconds> & hms );

};


 			}
		}
	}
}




#endif


