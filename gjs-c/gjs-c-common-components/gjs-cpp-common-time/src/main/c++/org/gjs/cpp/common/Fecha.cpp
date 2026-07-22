/******************************************************************************/
/*                                 Fecha.cpp                                  */
/*----------------------------------------------------------------------------*/
/* Libreria:  Tiempo                                                          */
/* Version:   3.0.0                                                           */
/*----------------------------------------------------------------------------*/
/* Descripcion:                                                               */
/* Implementacion de la clase de datos Fecha ( unificacion de Fecha + CFecha ).*/
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#include "Fecha.h"

#include "CommonTimeConfig.h"

#include "Fechas.h"




using namespace std;

namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {




Fecha::Fecha ()
{
	EstablecerValorDeHoy ();
}

Fecha::Fecha ( int iAAAA, int iMM, int iDD )
{
	Establecer ( iAAAA, iMM, iDD );
}

Fecha::Fecha ( long lValor )
{
	Establecer ( lValor );
}

Fecha::Fecha ( const string & sValor )
{
	Establecer ( sValor );
}

Fecha::Fecha ( const chrono::year_month_day & ymd )
{
	Establecer ( ymd );
}

Fecha::Fecha ( const chrono::year & y, const chrono::month & m, const chrono::day & d )
{
	Establecer ( y, m, d );
}

Fecha::~Fecha()
{
}

bool Fecha::Establecer ( int iAAAA, int iMM, int iDD )
{
	fecha = chrono::year_month_day ( chrono::year{ iAAAA },
									chrono::month{ static_cast<unsigned>( iMM ) },
									chrono::day{ static_cast<unsigned>( iDD ) } );
	return ( EsValida () );
}

bool Fecha::Establecer ( long lValor )
{
	int iAAAA = 0;
	int iMM = 0;
	int iDD = 0;
	FecFormDescomponer ( lValor, &iAAAA, &iMM, &iDD );
	return ( Establecer ( iAAAA, iMM, iDD ) );
}

bool Fecha::Establecer ( const string & sValor )
{
	return ( Establecer ( ToInt ( sValor ) ) );
}

bool Fecha::Establecer ( const chrono::year_month_day & ymd )
{
	fecha = ymd;
	return ( EsValida () );
}

bool Fecha::Establecer ( const chrono::year & y, const chrono::month & m, const chrono::day & d )
{
	return ( Establecer ( chrono::year_month_day ( y, m, d ) ) );
}

bool Fecha::EsValida () const
{
	return ( fecha.ok () );
}

long Fecha::Valor () const
{
	return ( FecFormConstruir ( AAAA (), MM (), DD () ) );
}

time_t Fecha::ValorTiempo () const
{
	chrono::system_clock::time_point tp = chrono::sys_days ( fecha );
	return ( chrono::system_clock::to_time_t ( tp ) );
}

string * Fecha::ValorCadena () const
{
	return ( new string ( to_string ( Valor () ) ) );
}

string Fecha::Formatear ( const string & sFormato ) const
{
	chrono::year_month_day ymd = fecha;
	return ( vformat ( sFormato, make_format_args ( ymd ) ) );
}

string * Fecha::Cadena ( const string & sFormato ) const
{
	return ( new string ( Formatear ( sFormato ) ) );
}

chrono::year_month_day Fecha::ToYMD () const
{
	return ( fecha );
}

int Fecha::AAAA () const
{
	return ( int ( fecha.year () ) );
}

int Fecha::MM () const
{
	return ( (int) static_cast<unsigned>( fecha.month () ) );
}

int Fecha::DD () const
{
	return ( (int) static_cast<unsigned>( fecha.day () ) );
}

void Fecha::EstablecerValorDeHoy ()
{
	chrono::system_clock::time_point ahora = chrono::system_clock::now ();
	chrono::sys_days dp = chrono::floor<chrono::days>( ahora );
	fecha = chrono::year_month_day ( dp );
}

bool Fecha::EsIgual ( const Fecha & fecValor ) const
{
	return ( EsIgual ( fecValor.Valor () ) );
}

bool Fecha::EsMenor ( const Fecha & fecValor ) const
{
	return ( EsMenor ( fecValor.Valor () ) );
}

bool Fecha::EsMayor ( const Fecha & fecValor ) const
{
	return ( EsMayor ( fecValor.Valor () ) );
}

bool Fecha::EsDiferente ( const Fecha & fecValor ) const
{
	return ( EsDiferente ( fecValor.Valor () ) );
}

bool Fecha::EsIgual ( const Fecha * p_fecValor ) const
{
	bool bRes = false;
	if ( ES_VALIDO ( p_fecValor ) )
	{
		bRes = EsIgual ( p_fecValor->Valor () );
	}
	return ( bRes );
}

bool Fecha::EsMenor ( const Fecha * p_fecValor ) const
{
	bool bRes = false;
	if ( ES_VALIDO ( p_fecValor ) )
	{
		bRes = EsMenor ( p_fecValor->Valor () );
	}
	return ( bRes );
}

bool Fecha::EsMayor ( const Fecha * p_fecValor ) const
{
	bool bRes = false;
	if ( ES_VALIDO ( p_fecValor ) )
	{
		bRes = EsMayor ( p_fecValor->Valor () );
	}
	return ( bRes );
}

bool Fecha::EsDiferente ( const Fecha * p_fecValor ) const
{
	bool bRes = false;
	if ( ES_VALIDO ( p_fecValor ) )
	{
		bRes = EsDiferente ( p_fecValor->Valor () );
	}
	return ( bRes );
}

bool Fecha::EsIgual ( const string & sValor ) const
{
	return ( EsIgual ( ToInt ( sValor ) ) );
}

bool Fecha::EsMenor ( const string & sValor ) const
{
	return ( EsMenor ( ToInt ( sValor ) ) );
}

bool Fecha::EsMayor ( const string & sValor ) const
{
	return ( EsMayor ( ToInt ( sValor ) ) );
}

bool Fecha::EsDiferente ( const string & sValor ) const
{
	return ( EsDiferente ( ToInt ( sValor ) ) );
}

bool Fecha::EsIgual ( long lValor ) const
{
	return ( Valor () == lValor );
}

bool Fecha::EsMenor ( long lValor ) const
{
	return ( Valor () < lValor );
}

bool Fecha::EsMayor ( long lValor ) const
{
	return ( Valor () > lValor );
}

bool Fecha::EsDiferente ( long lValor ) const
{
	return ( Valor () != lValor );
}

bool Fecha::EsIgual ( const chrono::year_month_day & ymd ) const
{
	return ( fecha == ymd );
}

bool Fecha::EsMenor ( const chrono::year_month_day & ymd ) const
{
	return ( fecha < ymd );
}

bool Fecha::EsMayor ( const chrono::year_month_day & ymd ) const
{
	return ( fecha > ymd );
}

bool Fecha::EsDiferente ( const chrono::year_month_day & ymd ) const
{
	return ( fecha != ymd );
}

long Fecha::Diferencia ( const Fecha & fecValor ) const
{
	chrono::sys_days dias1{ fecha };
	chrono::sys_days dias2{ fecValor.ToYMD () };

	auto diferencia = dias2 - dias1;
	return ( diferencia.count () );
}

long Fecha::Diferencia ( const Fecha * p_fecValor ) const
{
	long lRes = LLONG_MAX;
	if ( ES_VALIDO ( p_fecValor ) )
	{
		lRes = Diferencia ( *p_fecValor );
	}
	return ( lRes );
}

long Fecha::Diferencia ( const string & sValor ) const
{
	return ( Diferencia ( Fecha ( sValor ) ) );
}

long Fecha::Diferencia ( long lValor ) const
{
	return ( Diferencia ( Fecha ( lValor ) ) );
}

long Fecha::Diferencia ( const chrono::year_month_day & ymd ) const
{
	return ( Diferencia ( Fecha ( ymd ) ) );
}


bool Fecha::operator == ( const Fecha & fecValor ) const
{
	return ( EsIgual ( fecValor ) );
}

bool Fecha::operator != ( const Fecha & fecValor ) const
{
	return ( EsDiferente ( fecValor ) );
}

bool Fecha::operator < ( const Fecha & fecValor ) const
{
	return ( EsMenor ( fecValor ) );
}

bool Fecha::operator <= ( const Fecha & fecValor ) const
{
	return ( EsIgual ( fecValor ) || EsMenor ( fecValor ) );
}

bool Fecha::operator > ( const Fecha & fecValor ) const
{
	return ( EsMayor ( fecValor ) );
}

bool Fecha::operator >= ( const Fecha & fecValor ) const
{
	return ( EsIgual ( fecValor ) || EsMayor ( fecValor ) );
}

bool Fecha::operator == ( const Fecha * p_fecValor ) const
{
	return ( EsIgual ( p_fecValor ) );
}

bool Fecha::operator != ( const Fecha * p_fecValor ) const
{
	return ( EsDiferente ( p_fecValor ) );
}

bool Fecha::operator < ( const Fecha * p_fecValor ) const
{
	return ( EsMenor ( p_fecValor ) );
}

bool Fecha::operator <= ( const Fecha * p_fecValor ) const
{
	return ( EsIgual ( p_fecValor ) || EsMenor ( p_fecValor ) );
}

bool Fecha::operator > ( const Fecha * p_fecValor ) const
{
	return ( EsMayor ( p_fecValor ) );
}

bool Fecha::operator >= ( const Fecha * p_fecValor ) const
{
	return ( EsIgual ( p_fecValor ) || EsMayor ( p_fecValor ) );
}

bool Fecha::operator == ( const string & sValor ) const
{
	return ( EsIgual ( sValor ) );
}

bool Fecha::operator != ( const string & sValor ) const
{
	return ( EsDiferente ( sValor ) );
}

bool Fecha::operator < ( const string & sValor ) const
{
	return ( EsMenor ( sValor ) );
}

bool Fecha::operator <= ( const string & sValor ) const
{
	return ( EsIgual ( sValor ) || EsMenor ( sValor ) );
}

bool Fecha::operator > ( const string & sValor ) const
{
	return ( EsMayor ( sValor ) );
}

bool Fecha::operator >= ( const string & sValor ) const
{
	return ( EsIgual ( sValor ) || EsMayor ( sValor ) );
}

bool Fecha::operator == ( long lValor ) const
{
	return ( EsIgual ( lValor ) );
}

bool Fecha::operator != ( long lValor ) const
{
	return ( EsDiferente ( lValor ) );
}

bool Fecha::operator < ( long lValor ) const
{
	return ( EsMenor ( lValor ) );
}

bool Fecha::operator <= ( long lValor ) const
{
	return ( EsIgual ( lValor ) || EsMenor ( lValor ) );
}

bool Fecha::operator > ( long lValor ) const
{
	return ( EsMayor ( lValor ) );
}

bool Fecha::operator >= ( long lValor ) const
{
	return ( EsIgual ( lValor ) || EsMayor ( lValor ) );
}

bool Fecha::operator == ( const chrono::year_month_day & ymd ) const
{
	return ( EsIgual ( ymd ) );
}

bool Fecha::operator != ( const chrono::year_month_day & ymd ) const
{
	return ( EsDiferente ( ymd ) );
}

bool Fecha::operator < ( const chrono::year_month_day & ymd ) const
{
	return ( EsMenor ( ymd ) );
}

bool Fecha::operator <= ( const chrono::year_month_day & ymd ) const
{
	return ( EsIgual ( ymd ) || EsMenor ( ymd ) );
}

bool Fecha::operator > ( const chrono::year_month_day & ymd ) const
{
	return ( EsMayor ( ymd ) );
}

bool Fecha::operator >= ( const chrono::year_month_day & ymd ) const
{
	return ( EsIgual ( ymd ) || EsMayor ( ymd ) );
}

long Fecha::operator - ( const Fecha & fecValor ) const
{
	return ( Diferencia ( fecValor ) );
}

long Fecha::operator - ( const Fecha * p_fecValor ) const
{
	return ( Diferencia ( p_fecValor ) );
}

long Fecha::operator - ( const string & sValor ) const
{
	return ( Diferencia ( sValor ) );
}

long Fecha::operator - ( long lValor ) const
{
	return ( Diferencia ( lValor ) );
}

long Fecha::operator - ( const chrono::year_month_day & ymd ) const
{
	return ( Diferencia ( ymd ) );
}




 			}
		}
	}
}
