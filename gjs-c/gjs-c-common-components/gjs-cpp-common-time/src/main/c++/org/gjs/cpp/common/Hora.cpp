/******************************************************************************/
/*                                 Hora.cpp                                 */
/*----------------------------------------------------------------------------*/
/* Librería:  Tiempo                                                          */
/* Versión:   3.0.0                                                           */
/* Fecha:     25/03/2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Fichero de código fuente que contiene la implementación de la clase de     */
/* datos Hora.                                                              */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#include "Hora.h"



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

Hora::Hora ()
{
	EstablecerValorDeAhora ();
}

Hora::Hora ( long lValor )
{
	Establecer ( lValor );
}

Hora::Hora ( const string & sValor )
{
	Establecer ( sValor );
}

Hora::Hora ( int iHH, int iMI, int iSS )
{
	Establecer ( iHH, iMI, iSS );
}


Hora::Hora ( const chrono::hh_mm_ss<chrono::seconds> & hms )
{
	Establecer ( hms );
}


Hora::Hora ( const chrono::hours & hh, const chrono::minutes& mi, const chrono::seconds& ss )
{
	Establecer ( hh, mi, ss );
}

Hora::~Hora()
{
}

void Hora::Establecer ( long lValor )
{
	int iHH = lValor / 10000;
	long lAux = lValor % 10000;
	int iMI = lAux / 100;
	int iSS = lAux % 100;
	Establecer ( iHH, iMI, iSS );
}

void Hora::Establecer ( const string & sValor )
{
    Establecer ( ToInt ( sValor ) );
}

void Hora::Establecer ( int iHH, int iMI, int iSS )
{
    Establecer ( chrono::hours ( iHH ), chrono::minutes ( iMI ), chrono::seconds ( iSS ) );
}

void Hora::Establecer ( const chrono::hh_mm_ss<chrono::seconds> & hms )
{
    hmsHora = hms;
}

void Hora::Establecer ( const chrono::hours & hh, const chrono::minutes & mi, const chrono::seconds & ss )
{
    Establecer ( chrono::hh_mm_ss<chrono::seconds> ( hh + mi + ss ) );
}

bool Hora::EsValida ()
{
	return ( ( hmsHora.hours().count() >= 0 ) && ( hmsHora.hours().count() < 24 ) &&
        ( hmsHora.minutes().count() >= 0 ) && ( hmsHora.minutes().count() < 60 ) &&
        ( hmsHora.seconds().count() >= 0 ) && ( hmsHora.seconds().count() < 60 ) );
}

long Hora::Valor ()
{
	return ( hmsHora.hours().count() * 10000 + hmsHora.minutes().count() * 100 + hmsHora.seconds().count() );
}

string * Hora::ValorCadena ()
{
    return ( new string ( to_string ( Valor() ) ) );
}

string * Hora::Cadena ( const string & formato )
{
    return ( new string ( vformat ( formato, make_format_args( hmsHora ) ) ) );
}

int Hora::HH ()
{
	return ( hmsHora.hours().count() );
}

int Hora::MI ()
{
	return ( hmsHora.minutes().count() );
}

int Hora::SS ()
{
	return ( hmsHora.seconds().count() );
}

void Hora::EstablecerValorDeAhora ()
{
    chrono::system_clock::time_point ahora = chrono::system_clock::now();
    chrono::sys_days dias = chrono::floor<chrono::days>(ahora);
    hmsHora = chrono::hh_mm_ss{ floor<chrono::seconds>( ahora - dias ) };
}

bool Hora::EsIgual ( Hora & horValor )
{
	return ( EsIgual ( horValor.Valor () ) );
}

bool Hora::EsMenor( Hora & horValor )
{
	return ( EsMenor ( horValor.Valor () ) );
}

bool Hora::EsMayor ( Hora & horValor )
{
	return ( EsMayor ( horValor.Valor () ) );
}

bool Hora::EsDiferente ( Hora & horValor )
{
	return ( EsDiferente ( horValor.Valor () ) );
}

bool Hora::EsIgual ( Hora * p_horValor )
{
    bool bRes = false;
    if ( ES_VALIDO ( p_horValor ) )
    {
        bRes = EsIgual ( p_horValor->Valor () );
    }
	return ( bRes );
}

bool Hora::EsMenor( Hora * p_horValor )
{
    bool bRes = false;
    if ( ES_VALIDO ( p_horValor ) )
    {
        bRes = EsMenor( p_horValor->Valor () );
    }
	return ( bRes );
}

bool Hora::EsMayor ( Hora * p_horValor )
{
    bool bRes = false;
    if ( ES_VALIDO ( p_horValor ) )
    {
        bRes = EsMayor ( p_horValor->Valor () );
    }
	return ( bRes );
}

bool Hora::EsDiferente ( Hora * p_horValor )
{
    bool bRes = false;
    if ( ES_VALIDO ( p_horValor ) )
    {
        bRes = EsDiferente ( p_horValor->Valor () );
    }
	return ( bRes );
}

bool Hora::EsIgual ( const string & sValor )
{
	return ( EsIgual ( ToInt ( sValor ) ) );
}

bool Hora::EsMenor( const string & sValor )
{
	return ( EsMenor ( ToInt ( sValor ) ) );
}

bool Hora::EsMayor ( const string & sValor )
{
	return ( EsMayor ( ToInt ( sValor ) ) );
}

bool Hora::EsDiferente ( const string & sValor )
{
	return ( EsDiferente ( ToInt ( sValor ) ) );
}

bool Hora::EsIgual ( long lValor )
{
	return ( Valor() == lValor );
}

bool Hora::EsMenor( long lValor )
{
	return (  Valor() < lValor );
}

bool Hora::EsMayor ( long lValor )
{
	return (  Valor() > lValor );
}

bool Hora::EsDiferente ( long lValor )
{
	return (  Valor() != lValor );
}

bool Hora::EsIgual ( const chrono::hh_mm_ss<chrono::seconds> & hms  )
{
	return (  hmsHora.to_duration() == hms.to_duration() );
}

bool Hora::EsMenor ( const chrono::hh_mm_ss<chrono::seconds> & hms  )
{
	return (  hmsHora.to_duration() < hms.to_duration() );
}

bool Hora::EsMayor ( const chrono::hh_mm_ss<chrono::seconds> & hms  )
{
	return (  hmsHora.to_duration() > hms.to_duration() );
}

bool Hora::EsDiferente ( const chrono::hh_mm_ss<chrono::seconds> & hms  )
{
	return (  hmsHora.to_duration() != hms.to_duration() );
}

long Hora::Diferencia ( Hora & horValor )
{
	return ( Diferencia ( horValor.Valor () ) );
}

long Hora::Diferencia ( Hora * p_horValor )
{
    long lRes = LLONG_MAX;
    if ( ES_VALIDO ( p_horValor ) )
    {
        lRes = Diferencia ( p_horValor->Valor () );
    }
	return ( lRes );
}

long Hora::Diferencia ( const string & sValor )
{
	return ( Diferencia ( ToInt ( sValor ) ) );
}

long Hora::Diferencia ( long lValor )
{
	return ( Valor () - lValor );
}

long Hora::Diferencia ( const chrono::hh_mm_ss<chrono::seconds> & hms )
{
	long lValor = hms.hours().count() * 10000 + hms.minutes().count() * 100 + hms.seconds().count();
	return ( Diferencia( lValor ) );
}

bool Hora::operator == ( Hora & hmsHora )
{
	return ( EsIgual ( hmsHora ) );
}

bool Hora::operator != ( Hora & hmsHora )
{
	return ( EsDiferente ( hmsHora ) );
}

bool Hora::operator < ( Hora & hmsHora )
{
	return ( EsMenor ( &hmsHora ) );
}

bool Hora::operator <= ( Hora & hmsHora )
{
	return ( EsIgual ( hmsHora) || EsMenor ( hmsHora ) );
}

bool Hora::operator > ( Hora & hmsHora )
{
	return ( EsMayor ( hmsHora) );
}

bool Hora::operator >= ( Hora & hmsHora )
{
	return ( EsIgual ( hmsHora) || EsMayor ( hmsHora ) );
}

bool Hora::operator == ( Hora * p_horValor )
{
	return ( EsIgual ( p_horValor ) );
}

bool Hora::operator != ( Hora * p_horValor )
{
	return ( EsDiferente ( p_horValor ) );
}

bool Hora::operator < ( Hora * p_horValor )
{
	return ( EsMenor ( p_horValor ) );
}

bool Hora::operator <= ( Hora * p_horValor )
{
	return ( EsIgual ( p_horValor) || EsMenor ( p_horValor ) );
}

bool Hora::operator > ( Hora * p_horValor )
{
	return ( EsMayor ( p_horValor ) );
}

bool Hora::operator >= ( Hora * p_horValor )
{
	return ( EsIgual ( p_horValor) || EsMayor ( p_horValor ) );
}

bool Hora::operator == ( const string & sValor )
{
	return ( EsIgual ( sValor ) );
}

bool Hora::operator != ( const string & sValor )
{
	return ( EsDiferente ( sValor ) );
}

bool Hora::operator < ( const string & sValor )
{
	return ( EsMenor ( sValor ) );
}

bool Hora::operator <= ( const string & sValor )
{
	return ( EsIgual ( sValor) || EsMenor ( sValor ) );
}

bool Hora::operator > ( const string &  sValor )
{
	return ( EsMayor ( sValor ) );
}

bool Hora::operator >= ( const string &  sValor )
{
	return ( EsIgual ( sValor) || EsMayor ( sValor ) );
}

bool Hora::operator == ( long lValor )
{
	return ( EsIgual ( lValor ) );
}

bool Hora::operator != ( long lValor )
{
	return ( EsDiferente ( lValor ) );
}

bool Hora::operator < ( long lValor )
{
	return ( EsMenor ( lValor ) );
}

bool Hora::operator <= ( long lValor )
{
	return ( EsIgual ( lValor ) || EsMenor ( lValor ) );
}

bool Hora::operator > ( long lValor )
{
	return ( EsMayor ( lValor ) );
}

bool Hora::operator >= ( long lValor )
{
	return ( EsIgual ( lValor ) || EsMayor ( lValor ) );
}

bool Hora::operator == ( const chrono::hh_mm_ss<chrono::seconds> & hms )
{
	return ( EsIgual ( hms ) );
}

bool Hora::operator != ( const chrono::hh_mm_ss<chrono::seconds> & hms )
{
	return ( EsDiferente ( hms ) );
}

bool Hora::operator < ( const chrono::hh_mm_ss<chrono::seconds> & hms )
{
	return ( EsMenor ( hms ) );
}

bool Hora::operator <= ( const chrono::hh_mm_ss<chrono::seconds> & hms )
{
	return ( EsIgual ( hms ) || EsMenor ( hms ) );
}

bool Hora::operator > ( const chrono::hh_mm_ss<chrono::seconds> & hms )
{
	return ( EsMayor ( hms ) );
}

bool Hora::operator >= ( const chrono::hh_mm_ss<chrono::seconds> & hms )
{
	return ( EsIgual ( hms ) || EsMayor ( hms ) );
}

long Hora::operator - ( Hora & hmsHora )
{
	return ( Diferencia ( hmsHora ) );
}

long Hora::operator - ( Hora * p_horValor )
{
	return ( Diferencia ( p_horValor ) );
}

long Hora::operator - ( const string & sValor )
{
	return ( Diferencia ( sValor ) );
}

long Hora::operator - ( long lValor )
{
	return ( Diferencia ( lValor ) );
}

long Hora::operator - ( const chrono::hh_mm_ss<chrono::seconds> & hms )
{
	return ( Diferencia ( hms ) );
}


 			}
		}
	}
}





