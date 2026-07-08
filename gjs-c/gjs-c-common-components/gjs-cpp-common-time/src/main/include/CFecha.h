/******************************************************************************/
/*                                  CFecha.h                                  */
/*----------------------------------------------------------------------------*/
/* Librería:  Tiempo                                                          */
/* Versión:   3.0.0                                                           */
/* Fecha:     25/03/2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Fichero de cabecera que contiene la definición de la clase de datos        */
/* CFecha, destinada a almacenar un valor de fecha.                           */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#ifndef _ORG_GJS_C_CC_CPP_CFECHA_H
#define _ORG_GJS_C_CC_CPP_CFECHA_H


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

class CFecha
{
private:
     std::chrono::year_month_day ymdFecha;

public:
	CFecha ();
	CFecha ( long lValor );
	CFecha ( const std::string & sValor );
	CFecha ( int iA, int iM, int iD );
	CFecha ( const std::chrono::year_month_day & ymd );
	CFecha ( const std::chrono::year & y, const std::chrono::month & m, const std::chrono::day & d );
	~CFecha();

	void Establecer ( long lValor );
	void Establecer ( const std::string & sValor );
	void Establecer ( int iA, int iM, int iD );
	void Establecer ( const std::chrono::year_month_day & ymd );
	void Establecer ( const std::chrono::year & y, const std::chrono::month & m, const std::chrono::day & d );

	bool EsValida ();

	long Valor ();
	time_t ValorTiempo ();
	std::string * ValorCadena ();
	std::string * Cadena ( const std::string & formato );

	int AAAA ();
	int MM ();
	int DD ();

	void EstablecerValorDeHoy ();

	bool EsIgual ( CFecha & fecValor );
	bool EsMenor ( CFecha & fecValor );
	bool EsMayor ( CFecha & fecValor );
	bool EsDiferente ( CFecha & fecValor );
	bool EsIgual ( CFecha * p_fecValor );
	bool EsMenor ( CFecha * p_fecValor );
	bool EsMayor ( CFecha * p_fecValor );
	bool EsDiferente ( CFecha * p_fecValor );
	bool EsIgual ( const std::string & sValor );
	bool EsMenor ( const std::string & sValor );
	bool EsMayor ( const std::string & sValor );
	bool EsDiferente ( const std::string & sValor );
	bool EsIgual ( long lValor );
	bool EsMenor ( long lValor );
	bool EsMayor ( long lValor );
	bool EsDiferente ( long lValor );
	bool EsIgual ( const std::chrono::year_month_day & ymd  );
	bool EsMenor ( const std::chrono::year_month_day & ymd  );
	bool EsMayor ( const std::chrono::year_month_day & ymd  );
	bool EsDiferente ( const std::chrono::year_month_day & ymd  );

	long Diferencia ( CFecha & fecValor );
	long Diferencia ( CFecha * p_fecValor );
	long Diferencia ( const std::string & sValor );
	long Diferencia ( long lValor );
	long Diferencia ( const std::chrono::year_month_day & ymd );

public:
	bool operator == ( CFecha & fecValor );
	bool operator != ( CFecha & fecValor );
	bool operator > ( CFecha & fecValor );
	bool operator >= ( CFecha & fecValor );
	bool operator < ( CFecha & fecValor );
	bool operator <= ( CFecha & fecValor );
	bool operator == ( CFecha * p_fecValor );
	bool operator != ( CFecha * p_fecValor );
	bool operator > ( CFecha * p_fecValor );
	bool operator >= ( CFecha * p_fecValor );
	bool operator < ( CFecha * p_fecValor );
	bool operator <= ( CFecha * p_fecValor );
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
	bool operator == ( const std::chrono::year_month_day & ymd );
	bool operator != ( const std::chrono::year_month_day & ymd );
	bool operator > ( const std::chrono::year_month_day & ymd );
	bool operator >= ( const std::chrono::year_month_day & ymd );
	bool operator < ( const std::chrono::year_month_day & ymd );
	bool operator <= ( const std::chrono::year_month_day & ymd );

	long operator - ( CFecha & fecValor );
	long operator - ( CFecha * p_fecValor );
	long operator - ( const std::string & sValor );
	long operator - ( long lValor );
	long operator - ( const std::chrono::year_month_day & ymd );

};


 			}
		}
	}
}




#endif


