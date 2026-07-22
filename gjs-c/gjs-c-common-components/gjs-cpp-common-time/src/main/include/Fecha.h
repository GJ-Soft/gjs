/******************************************************************************/
/*                                  Fecha.h                                   */
/*----------------------------------------------------------------------------*/
/* Libreria:  Tiempo                                                          */
/* Version:   3.0.0                                                           */
/*----------------------------------------------------------------------------*/
/* Descripcion:                                                               */
/* Clase de datos Fecha, para almacenar un valor de fecha. Unifica la antigua */
/* CFecha ( API rica: constructores y comparaciones con chrono/puntero,       */
/* ValorTiempo/ValorCadena/Cadena ) con el diseno de Fecha ( Establecer       */
/* devuelve bool, accesores const, destructor virtual para poder heredarla,   */
/* y Diferencia en dias reales ). La antigua CFecha se ha eliminado.          */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#ifndef _ORG_GJS_C_CC_CPP_FECHA_H
#define _ORG_GJS_C_CC_CPP_FECHA_H

#include <string>
#include <chrono>
#include <ctime>



namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {



class Fecha
{
private:
	std::chrono::year_month_day fecha;

public:
	Fecha ();
	Fecha ( int iAAAA, int iMM, int iDD );
	Fecha ( long lValor );
	Fecha ( const std::string & sValor );
	Fecha ( const std::chrono::year_month_day & ymd );
	Fecha ( const std::chrono::year & y, const std::chrono::month & m, const std::chrono::day & d );

	virtual ~Fecha();

	bool Establecer ( int iAAAA, int iMM, int iDD );
	bool Establecer ( long lValor );
	bool Establecer ( const std::string & sValor );
	bool Establecer ( const std::chrono::year_month_day & ymd );
	bool Establecer ( const std::chrono::year & y, const std::chrono::month & m, const std::chrono::day & d );

	bool EsValida () const;

	long Valor () const;
	time_t ValorTiempo () const;
	std::string * ValorCadena () const;
	/*
	 *   "%d-%m-%Y", "%d/%m/%Y"
	 */
	std::string Formatear ( const std::string & sFormato ) const;
	std::string * Cadena ( const std::string & sFormato ) const;

	std::chrono::year_month_day ToYMD () const;
	int AAAA () const;
	int MM () const;
	int DD () const;

	void EstablecerValorDeHoy ();

	bool EsIgual ( const Fecha & fecValor ) const;
	bool EsMenor ( const Fecha & fecValor ) const;
	bool EsMayor ( const Fecha & fecValor ) const;
	bool EsDiferente ( const Fecha & fecValor ) const;
	bool EsIgual ( const Fecha * p_fecValor ) const;
	bool EsMenor ( const Fecha * p_fecValor ) const;
	bool EsMayor ( const Fecha * p_fecValor ) const;
	bool EsDiferente ( const Fecha * p_fecValor ) const;
	bool EsIgual ( const std::string & sValor ) const;
	bool EsMenor ( const std::string & sValor ) const;
	bool EsMayor ( const std::string & sValor ) const;
	bool EsDiferente ( const std::string & sValor ) const;
	bool EsIgual ( long lValor ) const;
	bool EsMenor ( long lValor ) const;
	bool EsMayor ( long lValor ) const;
	bool EsDiferente ( long lValor ) const;
	bool EsIgual ( const std::chrono::year_month_day & ymd ) const;
	bool EsMenor ( const std::chrono::year_month_day & ymd ) const;
	bool EsMayor ( const std::chrono::year_month_day & ymd ) const;
	bool EsDiferente ( const std::chrono::year_month_day & ymd ) const;

	// Diferencia en dias reales ( calendario ), no resta del valor YYYYMMDD.
	long Diferencia ( const Fecha & fecValor ) const;
	long Diferencia ( const Fecha * p_fecValor ) const;
	long Diferencia ( const std::string & sValor ) const;
	long Diferencia ( long lValor ) const;
	long Diferencia ( const std::chrono::year_month_day & ymd ) const;

public:
	bool operator == ( const Fecha & fecValor ) const;
	bool operator != ( const Fecha & fecValor ) const;
	bool operator > ( const Fecha & fecValor ) const;
	bool operator >= ( const Fecha & fecValor ) const;
	bool operator < ( const Fecha & fecValor ) const;
	bool operator <= ( const Fecha & fecValor ) const;
	bool operator == ( const Fecha * p_fecValor ) const;
	bool operator != ( const Fecha * p_fecValor ) const;
	bool operator > ( const Fecha * p_fecValor ) const;
	bool operator >= ( const Fecha * p_fecValor ) const;
	bool operator < ( const Fecha * p_fecValor ) const;
	bool operator <= ( const Fecha * p_fecValor ) const;
	bool operator == ( const std::string & sValor ) const;
	bool operator != ( const std::string & sValor ) const;
	bool operator > ( const std::string & sValor ) const;
	bool operator >= ( const std::string & sValor ) const;
	bool operator < ( const std::string & sValor ) const;
	bool operator <= ( const std::string & sValor ) const;
	bool operator == ( long lValor ) const;
	bool operator != ( long lValor ) const;
	bool operator > ( long lValor ) const;
	bool operator >= ( long lValor ) const;
	bool operator < ( long lValor ) const;
	bool operator <= ( long lValor ) const;
	bool operator == ( const std::chrono::year_month_day & ymd ) const;
	bool operator != ( const std::chrono::year_month_day & ymd ) const;
	bool operator > ( const std::chrono::year_month_day & ymd ) const;
	bool operator >= ( const std::chrono::year_month_day & ymd ) const;
	bool operator < ( const std::chrono::year_month_day & ymd ) const;
	bool operator <= ( const std::chrono::year_month_day & ymd ) const;

	long operator - ( const Fecha & fecValor ) const;
	long operator - ( const Fecha * p_fecValor ) const;
	long operator - ( const std::string & sValor ) const;
	long operator - ( long lValor ) const;
	long operator - ( const std::chrono::year_month_day & ymd ) const;
};



 			}
		}
	}
}



#endif
