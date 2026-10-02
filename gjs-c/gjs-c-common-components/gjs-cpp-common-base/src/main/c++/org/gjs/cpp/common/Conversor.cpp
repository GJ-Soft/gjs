/***************************************************************************/
/*                          Conversor.cpp                                 */
/*-------------------------------------------------------------------------*/
/* Librer�a: ClasesBase                                                    */
/* Versi�n:  2.0.0                                                         */
/* Fecha:    01/09/2007                                                    */
/* Autor:    Gin�s Jim�nez S�nchez                                         */
/*-------------------------------------------------------------------------*/
/* Descripci�n:                                                            */
/* Fichero de c�digo fuente que contiene la implementaci�n de la clase de  */
/* datos Conversor, destinada a gestionar la conversi�n autom�tica entre  */
/* los diferentes tipos de datos b�sicos.                                  */
/*-------------------------------------------------------------------------*/
/*                    ginesjimenez@safe-mail.net                          */
/***************************************************************************/

/* BaseConfig.h va PRIMERO, antes que cualquier otra cabecera: en modo WIN es
   quien mete winsock2.h, y tiene que llegar antes de que nada arrastre
   sys/types.h. El <string> de las cabeceras de aqui abajo ya lo hace, via
   pthread.h, y entonces Cygwin declara el select POSIX y winsock2 choca. */
#include "BaseConfig.h"

#include "Conversor.h"


using namespace std;


namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {



Conversor::Conversor ()
{
	Inicializar ();
}

Conversor::Conversor ( int iValor )
{
	Inicializar ();
	EstablecerValor ( iValor );
}

Conversor::Conversor ( long lValor )
{
	Inicializar ();
	EstablecerValor ( lValor );
}


Conversor::Conversor ( unsigned int uiValor )
{
	Inicializar ();
	EstablecerValor ( uiValor );
}

Conversor::Conversor ( long long llValor )
{
	Inicializar ();
	EstablecerValor ( llValor );
}

Conversor::Conversor ( unsigned long ulValor )
{
	Inicializar ();
	EstablecerValor ( ulValor );
}

Conversor::Conversor ( unsigned long long ullValor )
{
	Inicializar ();
	EstablecerValor ( ullValor );
}

Conversor::Conversor ( float fValor )
{
	Inicializar ();
	EstablecerValor ( fValor );
}

Conversor::Conversor ( double dValor )
{
	Inicializar ();
	EstablecerValor ( dValor );
}

Conversor::Conversor ( long double ldValor )
{
	Inicializar ();
	EstablecerValor ( ldValor );
}

Conversor::Conversor ( string & sValor )
{
	Inicializar ();
	EstablecerValor ( sValor );
}

Conversor::Conversor ( const string & sValor )
{
	Inicializar ();
	EstablecerValor ( sValor );
}

Conversor::Conversor ( char * p_cValor )
{
	Inicializar ();
	EstablecerValor ( p_cValor );
}

Conversor::Conversor ( const char * p_cValor )
{
	Inicializar ();
	EstablecerValor ( p_cValor );
}

Conversor::~Conversor ()
{
}

int Conversor::Entero ()
{
	return ( iValor );
}

long Conversor::EnteroLargo ()
{
	return ( lValor );
}

long long Conversor::EnteroDobleLargo ()
{
	return ( llValor );
}

unsigned int Conversor::EnteroSinSigno ()
{
	return ( uiValor );
}

unsigned long Conversor::EnteroLargoSinSigno ()
{
	return ( ulValor );
}

unsigned long long Conversor::EnteroDobleLargoSinSigno ()
{
	return ( ullValor );
}

float Conversor::Real ()
{
	return ( fValor );
}

double Conversor::RealDoble ()
{
	return ( dValor );
}

long double Conversor::RealDobleLargo ()
{
	return ( ldValor );
}

const string & Conversor::Cadena ()
{
	return ( sValor );
}

string Conversor::CadenaHex ()
{
    stringstream conversor;
    conversor << std::hex << this->EnteroDobleLargoSinSigno();
    std::string sHex = conversor.str();
    if ( sHex.size() % 2 != 0 ) 
	{
        sHex.insert ( sHex.begin(), '0' );
	}
    return( sHex );
}


void Conversor::EstablecerValor ( int iValor )
{
	bConvValida = true;
	this->iValor = iValor;
	this->lValor = (long) this->iValor;
	this->llValor = (long long) this->iValor;

	if ( this->iValor > 0 )
	{
		this->uiValor = (unsigned int) this->iValor;
		this->ulValor = (unsigned long) this->lValor;
		this->ullValor = (unsigned long long) this->llValor;
	}
	else
	{
		bConvValida = false;
		this->uiValor = 0;
		this->ulValor = 0;
		this->ullValor = 0;
	}
	this->ldValor = (long double) ( iValor );
	this->dValor = (double) ( iValor );
	this->fValor = (float) ( iValor );
	this->sValor = to_string ( lValor );
}

void Conversor::EstablecerValor ( long lValor )
{
	bConvValida = true;
	this->lValor = lValor;
	this->llValor = (long long) lValor;
	if ( ( this->lValor >= INT_MIN ) && ( this->lValor <= INT_MAX ) )
	{
		this->iValor = (int) this->lValor;
	}
	else
	{
		bConvValida = false;
		this->iValor = 0;
	}
	if ( ( this->lValor >= 0 ) && ( (unsigned int) this->lValor <= UINT_MAX ) )
	{
		this->uiValor = (unsigned int) lValor;
	}
	else
	{
		bConvValida = false;
		this->uiValor = 0;
	}
	if ( this->lValor >= 0 )
	{
		this->ulValor = (unsigned long) lValor;
		this->ullValor = (unsigned long long) lValor;
	}
	else
	{
		bConvValida = false;
		this->ulValor = 0;
		this->ullValor = 0;
	}
	this->ldValor = (long double) ( lValor );
	this->dValor = (double) ( lValor );
	this->fValor = (float) ( lValor );
	this->sValor = to_string ( lValor );
}

void Conversor::EstablecerValor ( long long llValor )
{
	bConvValida = true;
	this->llValor = llValor;
	if ( ( this->llValor >= LONG_MIN ) && ( this->llValor <= LONG_MAX ) )
	{
		this->lValor = (long) this->llValor;
	}
	else
	{
		bConvValida = false;
		this->lValor = 0;
	}
	if ( ( this->llValor >= INT_MIN ) && ( this->llValor <= INT_MAX ) )
	{
		this->iValor = (int) this->llValor;
	}
	else
	{
		bConvValida = false;
		this->iValor = 0;
	}
	if ( ( this->llValor >= 0 ) && ( (unsigned int) this->llValor <= UINT_MAX ) )
	{
		this->uiValor = (unsigned int) this->llValor;
	}
	else
	{
		bConvValida = false;
		this->uiValor = 0;
	}
	if ( ( this->llValor >= 0 ) && ( (unsigned int) this->llValor <= ULONG_MAX ) )
	{
		this->ulValor = (unsigned long) this->llValor;
	}
	else
	{
		bConvValida = false;
		this->ulValor = 0;
	}
	if ( this->llValor >= 0 )
	{
		this->ullValor = (unsigned long long) this->llValor;
	}
	else
	{
		bConvValida = false;
		this->ullValor = 0;
	}
	this->ldValor = (long double) ( this->llValor );
	this->dValor = (double) ( this->llValor );
	this->fValor = (float) ( this->llValor );
    this-> sValor = to_string ( this->llValor );
}


void Conversor::EstablecerValor ( unsigned int uiValor )
{
	bConvValida = true;
	this->uiValor = uiValor;
	this->ulValor = (unsigned long) this->uiValor;
	this->ullValor = (unsigned long long) this->uiValor;
	if ( this->uiValor <= INT_MAX )
	{
		this->iValor = (int) this->uiValor;
	}
	else
	{
		bConvValida = false;
		this->iValor = 0;
	}
	if ( this->uiValor <= LONG_MAX )
	{
		this->lValor = (long) this->uiValor;
	}
	else
	{
		bConvValida = false;
		this->lValor = 0;
	}
	if ( this->uiValor <= LLONG_MAX )
	{
		this->llValor = (long long) this->uiValor;
	}
	else
	{
		bConvValida = false;
		this->llValor = 0;
	}
	this->ldValor = (long double) ( this->uiValor );
	this->dValor = (double) ( this->uiValor );
	this->fValor = (float) ( this->uiValor );
	this->sValor = to_string ( this->uiValor );
}

void Conversor::EstablecerValor ( unsigned long ulValor )
{
	bConvValida = true;
	this->ulValor = ulValor;
	this->ullValor = (unsigned long long) ulValor;
	if ( ( this->ulValor <= UINT_MAX ) )
	{
		this->uiValor = (unsigned int) this->ulValor;
	}
	else
	{
		bConvValida = false;
		this->uiValor = 0;
	}
	if ( this->ulValor <= INT_MAX )
	{
		this->iValor = (int) this->ulValor;
	}
	else
	{
		bConvValida = false;
		this->iValor = 0;
	}
	if ( this->ulValor <= LONG_MAX )
	{
		this->lValor = (long) this->ulValor;
	}
	else
	{
		bConvValida = false;
		this->lValor = 0;
	}
	if ( this->ulValor <= LLONG_MAX )
	{
		this->llValor = (long long) this->ulValor;
	}
	else
	{
		bConvValida = false;
		this->llValor = 0;
	}
	this->ldValor = (long double) ( this->ulValor );
	this->dValor = (double) ( this->ulValor );
	this->fValor = (float) ( this->ulValor );
	this->sValor = to_string ( this->ulValor );
}

void Conversor::EstablecerValor ( unsigned long long ullValor )
{
	bConvValida = true;
	this->ullValor = ullValor;
	if ( ( this->ullValor <= UINT_MAX ) )
	{
		this->uiValor = (unsigned int) this->ullValor;
	}
	else
	{
		bConvValida = false;
		this->uiValor = 0;
	}
	if ( ( this->ullValor <= ULONG_MAX ) )
	{
		this->ulValor = (unsigned long) this->ullValor;
	}
	else
	{
		bConvValida = false;
		this->ulValor = 0;
	}
	if ( this->ullValor <= INT_MAX )
	{
		this->iValor = (int) this->ullValor;
	}
	else
	{
		bConvValida = false;
		this->iValor = 0;
	}
	if ( this->ullValor <= LONG_MAX )
	{
		this->lValor = (long) this->ullValor;
	}
	else
	{
		bConvValida = false;
		this->lValor = 0;
	}
	if ( this->ullValor <= LLONG_MAX )
	{
		this->llValor = (long long) this->ullValor;
	}
	else
	{
		bConvValida = false;
		this->llValor = 0;
	}
	this->ldValor = (long double) ( this->ullValor );
	this->dValor = (double) ( this->ullValor );
	this->fValor = (float) ( this->ullValor );
	this->sValor = to_string ( this->ullValor );
}

void Conversor::EstablecerValor ( float fValor )
{
	bConvValida = true;
	this->fValor = fValor;
	this->dValor = (double) this->fValor;
	this->ldValor = (long double) this->fValor;
	if ( ( this->fValor >= LLONG_MIN ) && ( this->fValor <= LLONG_MAX ) )
	{
		this->llValor = llround ( ldValor );
	}
	else
	{
		bConvValida = false;
		this->llValor = 0;
	}
	if ( ( this->fValor >= LONG_MIN ) && ( this->fValor <= LONG_MAX ) )
	{
		this->lValor = lround ( this->ldValor );
	}
	else
	{
		bConvValida = false;
		this->lValor = 0;
	}
    if ( ( this->fValor >= INT_MIN ) && ( this->fValor <= INT_MAX ) )
    {
        this->iValor = round ( this->ldValor );
    }
    else
    {
        bConvValida = false;
        this->iValor = 0;
    }
	if ( ( this->fValor >= 0 ) && ( this->fValor <= ULLONG_MAX ) )
	{
		this->ullValor = (unsigned long long) llround ( this->ldValor );
	}
	else
	{
		bConvValida = false;
		this->ullValor = 0;
	}
	if ( ( this->fValor >= 0 ) && ( this->fValor <= ULONG_MAX ) )
	{
		this->ulValor = (unsigned long) lround ( this->ldValor );
	}
	else
	{
		bConvValida = false;
		this->ulValor = 0;
	}
	if ( ( this->fValor >= 0 ) && ( this->fValor <= UINT_MAX ) )
	{
		this->uiValor = (unsigned int) round ( this->ldValor );
	}
	else
	{
		bConvValida = false;
		this->uiValor = 0;
	}
	this->sValor = to_string ( this->fValor );
}

void Conversor::EstablecerValor ( double dValor )
{
	bConvValida = true;
	this->dValor = dValor;
	this->ldValor = (long double) this->dValor;
	if ( ( fabs ( this->dValor ) >= FLT_MIN ) && ( fabs ( this->dValor ) <= FLT_MAX ) )
	{
		this->fValor = (float) this->dValor;
	}
	else
	{
		bConvValida = false;
		this->fValor = 0.0;
	}
	if ( ( this->dValor >= LLONG_MIN ) && ( this->dValor <= LLONG_MAX ) )
	{
		this->llValor = llround ( ldValor );
	}
	else
	{
		bConvValida = false;
		this->llValor = 0;
	}
	if ( ( this->dValor >= LONG_MIN ) && ( this->dValor <= LONG_MAX ) )
	{
		this->lValor = lround ( this->ldValor );
	}
	else
	{
		bConvValida = false;
		this->lValor = 0;
	}
    if ( ( this->dValor >= INT_MIN ) && ( this->dValor <= INT_MAX ) )
    {
        this->iValor = round ( this->ldValor );
    }
    else
    {
        bConvValida = false;
        this->iValor = 0;
    }
	if ( ( this->dValor >= 0 ) && ( this->dValor <= ULLONG_MAX ) )
	{
		this->ullValor = (unsigned long long) llround ( this->ldValor );
	}
	else
	{
		bConvValida = false;
		this->ullValor = 0;
	}
	if ( ( this->dValor >= 0 ) && ( this->dValor <= ULONG_MAX ) )
	{
		this->ulValor = (unsigned long) lround ( this->ldValor );
	}
	else
	{
		bConvValida = false;
		this->ulValor = 0;
	}
	if ( ( this->dValor >= 0 ) && ( this->dValor <= UINT_MAX ) )
	{
		this->uiValor = (unsigned int) round ( this->ldValor );
	}
	else
	{
		bConvValida = false;
		this->uiValor = 0;
	}
	this->sValor = to_string ( this->dValor );
}

void Conversor::EstablecerValor ( long double ldValor )
{
	bConvValida = true;
	this->ldValor = ldValor;
	if ( ( fabs ( this->ldValor ) >= DBL_MIN ) && ( fabs ( this->ldValor ) <= DBL_MAX ) )
	{
		this->dValor = (double) this->ldValor;
	}
	else
	{
		bConvValida = false;
		this->dValor = 0.0;
	}
	if ( ( fabs ( this->ldValor ) >= FLT_MIN ) && ( fabs ( this->ldValor ) <= FLT_MAX ) )
	{
		this->fValor = (float) this->ldValor;
	}
	else
	{
		bConvValida = false;
		this->fValor = 0.0;
	}
	if ( ( this->ldValor >= LLONG_MIN ) && ( this->ldValor <= LLONG_MAX ) )
	{
		this->llValor = llround ( ldValor );
	}
	else
	{
		bConvValida = false;
		this->llValor = 0;
	}
	if ( ( this->ldValor >= LONG_MIN ) && ( this->ldValor <= LONG_MAX ) )
	{
		this->lValor = lround ( this->ldValor );
	}
	else
	{
		bConvValida = false;
		this->lValor = 0;
	}
    if ( ( this->ldValor >= INT_MIN ) && ( this->ldValor <= INT_MAX ) )
    {
        this->iValor = round ( this->ldValor );
    }
    else
    {
        bConvValida = false;
        this->iValor = 0;
    }
	if ( ( this->ldValor >= 0 ) && ( this->ldValor <= ULLONG_MAX ) )
	{
		this->ullValor = (unsigned long long) llround ( this->ldValor );
	}
	else
	{
		bConvValida = false;
		this->ullValor = 0;
	}
	if ( ( this->ldValor >= 0 ) && ( this->ldValor <= ULONG_MAX ) )
	{
		this->ulValor = (unsigned long) lround ( this->ldValor );
	}
	else
	{
		bConvValida = false;
		this->ulValor = 0;
	}
	if ( ( this->ldValor >= 0 ) && ( this->ldValor <= UINT_MAX ) )
	{
		this->uiValor = (unsigned int) round ( this->ldValor );
	}
	else
	{
		bConvValida = false;
		this->uiValor = 0;
	}
	this->sValor = to_string ( this->ldValor );
}

void Conversor::EstablecerValor ( char * p_cValor )
{
	EstablecerValor ( static_cast < const char * > ( p_cValor ) );
}

void Conversor::EstablecerValor ( const char * p_cValor )
{
    string sValor = "";
    if ( ES_VALIDO ( p_cValor ) )
    {
        sValor = string( p_cValor );
    }
	EstablecerValor ( sValor );
}

void Conversor::EstablecerValor ( string & sValor )
{
	EstablecerValor ( (const string &) sValor );
}

void Conversor::EstablecerValor ( const string & sValor )
{
	bConvValida = true;
    this->sValor = sValor;
	if ( EsCadenaNumerica () )
	{
		try
		{
			this->ldValor = stold ( this->sValor );
		}
		catch ( ... )
		{
			// Cadena numerica valida pero fuera del rango de long double.
			this->ldValor = HUGE_VALL;
		}
		if ( this->ldValor == HUGE_VALL )
 		{
			bConvValida = false;
			this->ldValor = 0.0;
		}
		if ( ( fabs ( this->ldValor ) >= DBL_MIN ) && ( fabs ( this->ldValor ) <= DBL_MAX ) )
		{
			this->dValor = (double) this->ldValor;
		}
		else
		{
			bConvValida = false;
			this->dValor = 0.0;
		}
       if ( ( fabs ( this->ldValor ) >= FLT_MIN ) && ( fabs ( this->ldValor ) <= FLT_MAX ) )
        {
            this->fValor = (float) this->ldValor;
        }
        else
        {
           bConvValida = false;
            this->fValor = 0.0;
        }
        if ( ( this->ldValor >= LLONG_MIN ) && ( this->ldValor <= LLONG_MAX ) )
        {
            this->llValor = llround ( ldValor );
        }
        else
        {
			bConvValida = false;
            this->llValor = 0;
        }
         if ( ( this->ldValor >= LLONG_MIN ) && ( this->ldValor <= LLONG_MAX ) )
        {
            this->llValor = llround ( ldValor );
        }
        else
        {
			bConvValida = false;
            this->llValor = 0;
        }
       if ( ( this->ldValor >= LONG_MIN ) && ( this->ldValor <= LONG_MAX ) )
        {
            this->lValor = lround ( this->ldValor );
        }
        else
        {
            bConvValida = false;
            this->lValor = 0;
        }
        if ( ( this->ldValor >= INT_MIN ) && ( this->ldValor <= INT_MAX ) )
        {
            this->iValor = round ( this->ldValor );
        }
        else
        {
            bConvValida = false;
            this->iValor = 0;
        }
        if ( ( this->ldValor >= 0 ) && ( this->ldValor <= ULLONG_MAX ) )
        {
            this->ullValor = (unsigned long long) llround ( this->ldValor );
        }
        else
        {
            bConvValida = false;
            this->ullValor = 0;
        }
        if ( ( this->ldValor >= 0 ) && ( this->ldValor <= ULONG_MAX ) )
        {
            this->ulValor = (unsigned long) lround ( this->ldValor );
        }
        else
        {
            bConvValida = false;
            this->ulValor = 0;
        }
        if ( ( this->ldValor >= 0 ) && ( this->ldValor <= UINT_MAX ) )
        {
            this->uiValor = (unsigned int) round ( this->ldValor );
        }
        else
        {
            bConvValida = false;
            this->uiValor = 0;
        }
	}
	else
	{
	    EstablecerValorHex ( sValor );
	}
}


void Conversor::EstablecerValorHex ( char * p_cValor )
{
	EstablecerValorHex ( static_cast < const char * > ( p_cValor ) );
}

void Conversor::EstablecerValorHex ( const char * p_cValor )
{
    string sValor = "";
    if ( ES_VALIDO ( p_cValor ) )
    {
        sValor = string( p_cValor );
    }
	EstablecerValorHex ( sValor );
}


void Conversor::EstablecerValorHex ( string & sValor )
{
	EstablecerValorHex ( (const string &) sValor );
}

void Conversor::EstablecerValorHex ( const string & sValor )
{
	bConvValida = true;
	this->sValor = sValor;
	if ( EsCadenaNumericaHexadecimal () )
	{
        istringstream conversor( sValor );
        conversor >> std::hex >> this->ullValor;
        if ( ( this->ullValor <= UINT_MAX ) )
        {
            this->uiValor = (unsigned int) this->ullValor;
        }
        else
        {
            bConvValida = false;
            this->uiValor = 0;
        }
        if ( ( this->ullValor <= ULONG_MAX ) )
        {
            this->ulValor = (unsigned long) this->ullValor;
        }
        else
        {
            bConvValida = false;
            this->ulValor = 0;
        }
        if ( this->ullValor <= INT_MAX )
        {
            this->iValor = (int) this->ullValor;
        }
        else
        {
            bConvValida = false;
            this->iValor = 0;
        }
        if ( this->ullValor <= LONG_MAX )
        {
            this->lValor = (long) this->ullValor;
        }
        else
        {
            bConvValida = false;
            this->lValor = 0;
        }
        if ( this->ullValor <= LLONG_MAX )
        {
            this->llValor = (long long) this->ullValor;
        }
        else
        {
            bConvValida = false;
            this->llValor = 0;
        }
        this->ldValor = (long double) ( this->ullValor );
        this->dValor = (double) ( this->ullValor );
        this->fValor = (float) ( this->ullValor );
        this->ldValor = (long double) ( this->ullValor );
	}
	else
	{
		ldValor = 0.0;
		dValor = 0.0;
		fValor = 0.0;
		llValor = 0;
		lValor = 0;
		iValor = 0;
		ullValor = 0;
		ulValor = 0;
		uiValor = 0;
		bConvValida = false;
	}
}


bool Conversor::EsCadenaNumerica ()
{
    return regex_match( sValor , std::regex( REGEX_NUM_REAL ) );
}

bool Conversor::EsCadenaNumericaEntera ()
{
    return regex_match( sValor, std::regex( REGEX_NUM_ENTERO ) );
}


bool Conversor::EsCadenaNumericaReal ()
{
	return ( EsCadenaNumerica () );
}

bool Conversor::EsCadenaNumericaHexadecimal ()
{
    return regex_match( sValor, std::regex( REGEX_NUM_HEXADECIMAL ) );
}

bool Conversor::ConversionValida ()
{
	return ( bConvValida );
}

void Conversor::Inicializar ()
{
	bConvValida = false;
	iValor = 0;
	lValor = 0;
	llValor = 0;
	uiValor = 0;
	ulValor = 0;
	ullValor = 0;
	fValor = 0.0;
	dValor = 0.0;
	ldValor = 0.0;
	sValor = "";
}


            }
		}
	}
}



