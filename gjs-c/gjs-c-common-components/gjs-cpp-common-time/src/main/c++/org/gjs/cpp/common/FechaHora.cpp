/******************************************************************************/
/*                               FechaHora.cpp                               */
/*----------------------------------------------------------------------------*/
/* Librer�a:  Tiempo                                                          */
/* Versi�n:   3.0.0                                                           */
/* Fecha:     25/03/2008                                                      */
/* Autor:     Gin�s Jim�nez S�nchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripci�n:                                                               */
/* Fichero de c�digo fuente que contiene la implementaci�n de la clase de     */
/* datos FechaHora.                                                          */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#include "FechaHora.h"





#include "CommonTimeConfig.h"



using namespace std;



namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {


FechaHora::FechaHora ()
{
	EstablecerValorDeAhora ();
}

FechaHora::FechaHora ( long long llValor )
{
	Establecer ( llValor );
}

FechaHora::FechaHora ( const string & sValor )
{
	Establecer ( sValor );
}

FechaHora::FechaHora ( long lFecha, long lHora )
{
	Establecer ( lFecha, lHora );
}

FechaHora::FechaHora ( int iA, int iM, int iD, int iHH, int iMI, int iSS )
{
	Establecer ( iA, iM, iD, iHH, iMI, iSS );
}


FechaHora::FechaHora ( const chrono::system_clock::time_point & tp )
{
	Establecer ( tp );
}

FechaHora::FechaHora ( ::org::gjs::cpp::common::Fecha & fecFecha, ::org::gjs::cpp::common::Hora & horHora )
{
	Establecer ( fecFecha, horHora );
}

FechaHora::FechaHora ( const chrono::year_month_day & ymd, const chrono::hh_mm_ss<chrono::seconds> & hms )
{
	Establecer ( ymd, hms );
}

FechaHora::FechaHora ( const chrono::year & y, const chrono::month & m, const chrono::day & d,
               const chrono::hours & hh, const chrono::minutes & mi, const chrono::seconds & ss )
{
	Establecer ( y, m, d, hh, mi, ss );
}

FechaHora::~FechaHora()
{
}

void FechaHora::Establecer ( long long llValor )
{
    long lValorDia = llValor / 1000000;
    long lValorHora = llValor % 1000000;
	Establecer ( lValorDia, lValorHora );
}

void FechaHora::Establecer ( const string & sValor )
{
    Establecer ( ToLLong ( sValor ) );
}

void FechaHora::Establecer ( int iA, int iM, int iD, int iHH, int iMI, int iSS )
{
    Establecer ( chrono::year ( iA ), chrono::month ( iM ), chrono::day ( iD ),
                chrono::hours ( iHH ), chrono::minutes ( iMI ), chrono::seconds ( iSS ) );
}

void FechaHora::Establecer ( long lFecha, long lHora )
{
	int iA = lFecha / 10000;
	long lAux = lFecha % 10000;
	int iM = lAux / 100;
	int iD = lAux % 100;
	int iHH = lHora / 10000;
	lAux = lHora % 10000;
	int iMI = lAux / 100;
	int iSS = lAux % 100;
	Establecer ( iA, iM, iD, iHH, iMI, iSS );
}

void FechaHora::Establecer ( const chrono::system_clock::time_point & tp )
{
    tpFechaHora = tp;
}

void FechaHora::Establecer ( ::org::gjs::cpp::common::Fecha & fecFecha, ::org::gjs::cpp::common::Hora & horHora )
{
    Establecer ( fecFecha.Valor(), horHora.Valor() );
}

void FechaHora::Establecer ( const chrono::year_month_day & ymd, const chrono::hh_mm_ss<chrono::seconds> & hms )
{
    Establecer ( chrono::system_clock::time_point ( chrono::sys_days( ymd ) + hms.to_duration() ) );
}

void FechaHora::Establecer ( const chrono::year & y, const chrono::month & m, const chrono::day & d,
            const chrono::hours & hh, const chrono::minutes & mi, const chrono::seconds & ss )
{
    Establecer ( chrono::sys_days ( chrono::year_month_day ( y, m, d ) ) +
                hh + mi + ss );
}

bool FechaHora::EsValida ()
{
    chrono::sys_days dias = chrono::floor<chrono::days>( tpFechaHora );
    chrono::year_month_day ymd = chrono::year_month_day ( dias );
    chrono::hh_mm_ss hms = chrono::hh_mm_ss{ tpFechaHora - dias };
    return ( ymd.ok() &&
        ( hms.hours().count() >= 0 ) && ( hms.hours().count() < 24 ) &&
        ( hms.minutes().count() >= 0 ) && ( hms.minutes().count() < 60 ) &&
        ( hms.seconds().count() >= 0 ) && ( hms.seconds().count() < 60 ) );
}

long long FechaHora::Valor ()
{
    chrono::sys_days dias = chrono::floor<chrono::days>( tpFechaHora );
    chrono::year_month_day ymdFecha = chrono::year_month_day ( dias );
    chrono::hh_mm_ss hmsHora = chrono::hh_mm_ss{ tpFechaHora - dias };
	long long llFecha = int( ymdFecha.year() ) * 10000 +
        (int) static_cast<unsigned>( ymdFecha.month() )  * 100 +
        (int) static_cast<unsigned>( ymdFecha.day() );
	long long llHora = hmsHora.hours().count() * 10000 +
        hmsHora.minutes().count()  * 100 +
        hmsHora.seconds().count();
    return ( llFecha * 1000000 + llHora );
}

long FechaHora::ValorFecha ()
{
    chrono::sys_days dias = chrono::floor<chrono::days>( tpFechaHora );
    chrono::year_month_day ymdFecha = chrono::year_month_day ( dias );
	return ( int( ymdFecha.year() ) * 10000 +
        (int) static_cast<unsigned>( ymdFecha.month() )  * 100 +
        (int) static_cast<unsigned>( ymdFecha.day() ) );
}

long FechaHora::ValorHora ()
{
    chrono::sys_days dias = chrono::floor<chrono::days>( tpFechaHora );
    chrono::hh_mm_ss hmsHora = chrono::hh_mm_ss{ tpFechaHora - dias };
	return ( hmsHora.hours().count() * 10000 +
        hmsHora.minutes().count()  * 100 +
        hmsHora.seconds().count() );
}

string * FechaHora::ValorCadena ()
{
    return ( new string ( to_string ( Valor() ) ) );
}

string * FechaHora::Cadena ( const string & formato )
{
	/* Dos correcciones sobre el time_point crudo:

	   - Truncado a segundos. system_clock tiene precision de nanosegundos y %S
	     los sacaba todos: una linea de log salia con "17:00:01.517053600" y un
	     nombre de fichero por instante.
	   - Pasado a hora LOCAL. std::format sobre un system_clock::time_point
	     formatea en UTC, asi que con el reloj en las 19:00 escribia las 17:00.
	     No se usa current_zone (): no esta en la libstdc++ de Cygwin. Se
	     reconstruye el instante desde los campos de localtime, que es lo que ya
	     usa TiempoSistema, y se formatea como local_time; asi no hay aritmetica
	     de desfases ni casos raros de horario de verano. */
	auto	tpSegundos = chrono::floor < chrono::seconds > ( tpFechaHora );
	time_t	ttValor = chrono::system_clock::to_time_t ( tpSegundos );
	tm		tmLocal = *localtime ( &ttValor );

	auto tpLocal = chrono::local_days ( chrono::year ( tmLocal.tm_year + 1900 ) /
										( tmLocal.tm_mon + 1 ) / tmLocal.tm_mday ) +
				   chrono::hours ( tmLocal.tm_hour ) +
				   chrono::minutes ( tmLocal.tm_min ) +
				   chrono::seconds ( tmLocal.tm_sec );

	return ( new string ( vformat ( formato, make_format_args ( tpLocal ) ) ) );
}

Fecha * FechaHora::Fecha ()
{
	return ( new ::org::gjs::cpp::common::Fecha ( ValorFecha() ) );
}

Hora * FechaHora::Hora ()
{
	return ( new ::org::gjs::cpp::common::Hora ( ValorHora() ) );
}


int FechaHora::AAAA ()
{
    chrono::sys_days dias = chrono::floor<chrono::days>( tpFechaHora );
    chrono::year_month_day ymd = chrono::year_month_day ( dias );
	return ( int( ymd.year() ) );
}

int FechaHora::MM ()
{
    chrono::sys_days dias = chrono::floor<chrono::days>( tpFechaHora );
    chrono::year_month_day ymd = chrono::year_month_day ( dias );
	return ( (int) static_cast<unsigned>( ymd.month() ) );
}

int FechaHora::DD ()
{
    chrono::sys_days dias = chrono::floor<chrono::days>( tpFechaHora );
    chrono::year_month_day ymd = chrono::year_month_day ( dias );
	return ( (int) static_cast<unsigned>(  ymd.day() ) );
}

int FechaHora::HH ()
{
    chrono::sys_days dias = chrono::floor<chrono::days>( tpFechaHora );
    chrono::hh_mm_ss hms= chrono::hh_mm_ss{ tpFechaHora - dias };
	return ( hms.hours().count() );
}

int FechaHora::MI ()
{
    chrono::sys_days dias = chrono::floor<chrono::days>( tpFechaHora );
    chrono::hh_mm_ss hms= chrono::hh_mm_ss{ tpFechaHora - dias };
	return ( hms.minutes().count() );
}

int FechaHora::SS ()
{
    chrono::sys_days dias = chrono::floor<chrono::days>( tpFechaHora );
    chrono::hh_mm_ss hms= chrono::hh_mm_ss{ tpFechaHora - dias };
	return ( hms.seconds().count() );
}

void FechaHora::EstablecerValorDeAhora ()
{
    tpFechaHora = chrono::system_clock::now();
}

bool FechaHora::EsIgual ( FechaHora & fecValor )
{
	return ( EsIgual ( fecValor.Valor () ) );
}

bool FechaHora::EsMenor( FechaHora & fecValor )
{
	return ( EsMenor ( fecValor.Valor () ) );
}

bool FechaHora::EsMayor ( FechaHora & fecValor )
{
	return ( EsMayor ( fecValor.Valor () ) );
}

bool FechaHora::EsDiferente ( FechaHora & fecValor )
{
	return ( EsDiferente ( fecValor.Valor () ) );
}

bool FechaHora::EsIgual ( FechaHora * p_fecValor )
{
    bool bRes = false;
    if ( ES_VALIDO ( p_fecValor ) )
    {
        bRes = EsIgual ( p_fecValor->Valor () );
    }
	return ( bRes );
}

bool FechaHora::EsMenor( FechaHora * p_fecValor )
{
    bool bRes = false;
    if ( ES_VALIDO ( p_fecValor ) )
    {
        bRes = EsMenor( p_fecValor->Valor () );
    }
	return ( bRes );
}

bool FechaHora::EsMayor ( FechaHora * p_fecValor )
{
    bool bRes = false;
    if ( ES_VALIDO ( p_fecValor ) )
    {
        bRes = EsMayor ( p_fecValor->Valor () );
    }
	return ( bRes );
}

bool FechaHora::EsDiferente ( FechaHora * p_fecValor )
{
    bool bRes = false;
    if ( ES_VALIDO ( p_fecValor ) )
    {
        bRes = EsDiferente ( p_fecValor->Valor () );
    }
	return ( bRes );
}

bool FechaHora::EsIgual ( const string & sValor )
{
	return ( EsIgual ( ToLLong ( sValor ) ) );
}

bool FechaHora::EsMenor( const string & sValor )
{
	return ( EsMenor ( ToLLong ( sValor ) ) );
}

bool FechaHora::EsMayor ( const string & sValor )
{
	return ( EsMayor ( ToLLong ( sValor ) ) );
}

bool FechaHora::EsDiferente ( const string & sValor )
{
	return ( EsDiferente ( ToLLong ( sValor ) ) );
}

bool FechaHora::EsIgual ( long long llValor )
{
	return ( Valor() == llValor );
}

bool FechaHora::EsMenor( long long llValor )
{
	return (  Valor() < llValor );
}

bool FechaHora::EsMayor ( long long llValor )
{
	return (  Valor() > llValor );
}

bool FechaHora::EsDiferente ( long long llValor )
{
	return (  Valor() != llValor );
}

long FechaHora::Diferencia ( FechaHora & fecValor )
{
	return ( Diferencia ( fecValor.Valor () ) );
}

long FechaHora::Diferencia ( FechaHora * p_fecValor )
{
    long lRes = LLONG_MAX;
    if ( ES_VALIDO ( p_fecValor ) )
    {
        lRes = Diferencia ( p_fecValor->Valor () );
    }
	return ( lRes );
}

long FechaHora::Diferencia ( const string & sValor )
{
	return ( Diferencia ( ToLLong ( sValor ) ) );
}

long FechaHora::Diferencia ( long long llValor )
{
	return ( Valor () - llValor );
}

bool FechaHora::operator == ( FechaHora & fecValor )
{
	return ( EsIgual ( fecValor ) );
}

bool FechaHora::operator != ( FechaHora & fecValor )
{
	return ( EsDiferente ( fecValor ) );
}

bool FechaHora::operator < ( FechaHora & fecValor )
{
	return ( EsMenor ( &fecValor ) );
}

bool FechaHora::operator <= ( FechaHora & fecValor )
{
	return ( EsIgual ( fecValor) || EsMenor ( fecValor ) );
}

bool FechaHora::operator > ( FechaHora & fecValor )
{
	return ( EsMayor ( fecValor) );
}

bool FechaHora::operator >= ( FechaHora & fecValor )
{
	return ( EsIgual ( fecValor) || EsMayor ( fecValor ) );
}

bool FechaHora::operator == ( FechaHora * p_fecValor )
{
	return ( EsIgual ( p_fecValor ) );
}

bool FechaHora::operator != ( FechaHora * p_fecValor )
{
	return ( EsDiferente ( p_fecValor ) );
}

bool FechaHora::operator < ( FechaHora * p_fecValor )
{
	return ( EsMenor ( p_fecValor ) );
}

bool FechaHora::operator <= ( FechaHora * p_fecValor )
{
	return ( EsIgual ( p_fecValor) || EsMenor ( p_fecValor ) );
}

bool FechaHora::operator > ( FechaHora * p_fecValor )
{
	return ( EsMayor ( p_fecValor ) );
}

bool FechaHora::operator >= ( FechaHora * p_fecValor )
{
	return ( EsIgual ( p_fecValor) || EsMayor ( p_fecValor ) );
}

bool FechaHora::operator == ( const string & sValor )
{
	return ( EsIgual ( sValor ) );
}

bool FechaHora::operator != ( const string & sValor )
{
	return ( EsDiferente ( sValor ) );
}

bool FechaHora::operator < ( const string & sValor )
{
	return ( EsMenor ( sValor ) );
}

bool FechaHora::operator <= ( const string & sValor )
{
	return ( EsIgual ( sValor) || EsMenor ( sValor ) );
}

bool FechaHora::operator > ( const string &  sValor )
{
	return ( EsMayor ( sValor ) );
}

bool FechaHora::operator >= ( const string &  sValor )
{
	return ( EsIgual ( sValor) || EsMayor ( sValor ) );
}

bool FechaHora::operator == ( long long llValor )
{
	return ( EsIgual ( llValor ) );
}

bool FechaHora::operator != ( long long llValor )
{
	return ( EsDiferente ( llValor ) );
}

bool FechaHora::operator < ( long long llValor )
{
	return ( EsMenor ( llValor ) );
}

bool FechaHora::operator <= ( long long llValor )
{
	return ( EsIgual ( llValor ) || EsMenor ( llValor ) );
}

bool FechaHora::operator > ( long long llValor )
{
	return ( EsMayor ( llValor ) );
}

bool FechaHora::operator >= ( long long llValor )
{
	return ( EsIgual ( llValor ) || EsMayor ( llValor ) );
}

long FechaHora::operator - ( FechaHora & fecValor )
{
	return ( Diferencia ( fecValor ) );
}

long FechaHora::operator - ( FechaHora * p_fecValor )
{
	return ( Diferencia ( p_fecValor ) );
}

long FechaHora::operator - ( const string & sValor )
{
	return ( Diferencia ( sValor ) );
}

long FechaHora::operator - ( long long llValor )
{
	return ( Diferencia ( llValor ) );
}





 			}
		}
	}
}



