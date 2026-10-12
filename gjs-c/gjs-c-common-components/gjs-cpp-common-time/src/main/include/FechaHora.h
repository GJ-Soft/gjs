/******************************************************************************/
/*                                FechaHora.h                                */
/*----------------------------------------------------------------------------*/
/* Librería:  Tiempo                                                          */
/* Versión:   3.0.0                                                           */
/* Fecha:     25/03/2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Fichero de cabecera que contiene la definición de la clase de datos        */
/* FechaHora, destinada a gestionar valores que almacenen un valor           */
/* horario.                                                                   */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#ifndef _ORG_GJS_C_CC_CPP_FECHAHORA_H
#define _ORG_GJS_C_CC_CPP_FECHAHORA_H


#include <Fecha.h>
#include <Hora.h>




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

class FechaHora
{
private:
	std::chrono::system_clock::time_point tpFechaHora;

public:
	FechaHora ();
	FechaHora ( long long llValor );
	FechaHora ( const std::string & sValor );
	FechaHora ( long lFecha, long lHora );
	FechaHora ( int iA, int iM, int iD, int iHH, int iMI, int iSS );
	FechaHora ( const std::chrono::system_clock::time_point & tp );
	FechaHora ( Fecha & fecFecha, Hora & horHora );
	FechaHora ( const std::chrono::year_month_day & ymd, const std::chrono::hh_mm_ss<std::chrono::seconds> & hms );
	FechaHora ( const std::chrono::year & y, const std::chrono::month & m, const std::chrono::day & d,
                const std::chrono::hours & hh, const std::chrono::minutes & mi, const std::chrono::seconds & ss );

	~FechaHora();

	void Establecer ( long long llValor );
	void Establecer ( const std::string & sValor );
	void Establecer ( long lFecha, long lHora );
	void Establecer ( int iA, int iM, int iD, int iHH, int iMI, int iSS );
	void Establecer ( const std::chrono::system_clock::time_point & tp );
	void Establecer ( Fecha & fecFecha, Hora & horHora );
	void Establecer ( const std::chrono::year_month_day & ymd, const std::chrono::hh_mm_ss<std::chrono::seconds> & hms );
	void Establecer ( const std::chrono::year & y, const std::chrono::month & m, const std::chrono::day & d,
                const std::chrono::hours & hh, const std::chrono::minutes & mi, const std::chrono::seconds & ss );

	bool EsValida ();

	int AAAA ();
	int MM ();
	int DD ();
	int HH ();
	int MI ();
	int SS ();

	long ValorFecha ();
	long ValorHora ();
	long long Valor ();
	std::string * ValorCadena ();
	std::string * Cadena ( const std::string & formato );

	Fecha * Fecha ();
	Hora * Hora ();

	void EstablecerValorDeAhora ();

	bool EsIgual ( FechaHora & fechValor );
	bool EsMenor ( FechaHora & fechValor );
	bool EsMayor ( FechaHora & fechValor );
	bool EsDiferente ( FechaHora & fechValor );
	bool EsIgual ( FechaHora * p_horValor );
	bool EsMenor ( FechaHora * p_horValor );
	bool EsMayor ( FechaHora * p_horValor );
	bool EsDiferente ( FechaHora * p_horValor );
	bool EsIgual ( const std::string & sValor );
	bool EsMenor ( const std::string & sValor );
	bool EsMayor ( const std::string & sValor );
	bool EsDiferente ( const std::string & sValor );
	bool EsIgual ( long long llValor );
	bool EsMenor ( long long llValor );
	bool EsMayor ( long long llValor );
	bool EsDiferente ( long long llValor );

	long long Diferencia ( FechaHora & fechValor );
	long long Diferencia ( FechaHora * p_horValor );
	long long Diferencia ( const std::string & sValor );
	long long Diferencia ( long long llValor );

public:
	bool operator == ( FechaHora & fechValor );
	bool operator != ( FechaHora & fechValor );
	bool operator > ( FechaHora & fechValor );
	bool operator >= ( FechaHora & fechValor );
	bool operator < ( FechaHora & fechValor );
	bool operator <= ( FechaHora & fechValor );
	bool operator == ( FechaHora * p_horValor );
	bool operator != ( FechaHora * p_horValor );
	bool operator > ( FechaHora * p_horValor );
	bool operator >= ( FechaHora * p_horValor );
	bool operator < ( FechaHora * p_horValor );
	bool operator <= ( FechaHora * p_horValor );
	bool operator == ( const std::string & sValor );
	bool operator != ( const std::string & sValor );
	bool operator > ( const std::string & sValor );
	bool operator >= ( const std::string & sValor );
	bool operator < ( const std::string & sValor );
	bool operator <= ( const std::string & sValor );
	bool operator == ( long long llValor );
	bool operator != ( long long llValor );
	bool operator > ( long long llValor );
	bool operator >= ( long long llValor );
	bool operator < ( long long llValor );
	bool operator <= ( long long llValor );

	long long operator - ( FechaHora & fechValor );
	long long operator - ( FechaHora * fechValor );
	long long operator - ( const std::string & sValor );
	long long operator - ( long long llValor );

};


 			}
		}
	}
}




#endif


