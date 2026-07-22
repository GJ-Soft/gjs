#include "BaseConfig.h"
#include "Cadenas.h"

#include <string_view>


using namespace std;


namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {

string ToLowerCase ( const string & sCadena )
{
	string sRes = string ( sCadena );
	transform ( sRes.begin(), sRes.end(), sRes.begin(),
					   [](unsigned char c){ return tolower( c ); });
	return ( sRes );
}

string ToUpperCase ( const string & sCadena )
{
	string sRes = string ( sCadena );
	transform ( sRes.begin(), sRes.end(), sRes.begin(),
					   [](unsigned char c){ return toupper( c ); });
	return ( sRes );
}

bool SonIgualesSinDistinguirTipoLetra ( const string & sCadena1, const string & sCadena2 )
{
    return ( sCadena1.size() == sCadena2.size() ) &&
           ranges::equal ( sCadena1, sCadena2, [](char x, char y) {
               return  tolower( (unsigned char)x ) ==
                       tolower( (unsigned char)y );
           });
}

string ReemplazarTodos ( const string & sCadena, char cBuscar, char cReemplazo )
{
	string sRes = sCadena;
	size_t pos;
    while ( ( pos = sRes.find( cBuscar ) ) != string::npos )
	{
        sRes.replace( pos, 1, 1, cReemplazo );
    }
	return ( sRes );
}

string ReemplazarTodos ( const string & sCadena, const string & sBuscar, const string & sReemplazo )
{
	string sRes = sCadena;
	size_t pos;
    while ( ( pos = sRes.find( sBuscar ) ) != string::npos )
	{
        sRes.replace( pos, sBuscar.size(), sReemplazo );
    }
	return ( sRes );
}

string EliminarTodos ( const string & sCadena, char cBuscar )
{
	string sRes = sCadena;
	size_t pos;
    while ( ( pos = sRes.find( cBuscar ) ) != string::npos )
	{
        sRes.erase( pos, 1 );
    }
	return ( sRes );
}

string EliminarTodos ( const string & sCadena, const string & sBuscar )
{
	string sRes = sCadena;
	size_t pos;
    while ( ( pos = sRes.find( sBuscar ) ) != string::npos )
	{
        sRes.erase( pos, sBuscar.size() );
    }
	return ( sRes );
}

string Limpiar( const string & sCadena )
{
	string sRes = sCadena;
	sRes.erase( remove_if( sRes.begin(), sRes.end(), []( char c ) { return iscntrl( c ); } ), sRes.end() );
	return ( sRes );
}

string FormatearBlancos ( const string & sCadena )
{
    regex patron ( "\\s+" );
    return ( Trim ( regex_replace( sCadena, patron, " " ) ) );
}


bool ContieneCaracter ( const string & sCadena, char c )
{
	return ( sCadena.find( c ) != string::npos );
}

bool ContieneBlancos ( const string & sCadena )
{
    regex patron ( "\\s" );
    return ( regex_search ( sCadena, patron ) );
}

bool ContieneTabuladores ( const string & sCadena )
{
    regex patron ( "\\t" );
    return ( regex_search ( sCadena, patron ) );
}

bool ContieneCaracteresNoImprimibles ( const string & sCadena )
{
    regex patron ( "(?![\\n\\t])[^[:print:]]" );
    return ( regex_search ( sCadena, patron ) );
}

bool ContieneCaracteresNoAlfanumericos ( const string & sCadena )
{
    regex patron ( "[^\\w:]" );
    return ( regex_search ( sCadena, patron ) );
}

bool ContieneCaracteresNoEstandar ( const string & sCadena )
{
    regex patron ( "[^\\u0020-\\u007F]" );
    return ( regex_search ( sCadena, patron ) );
}

bool CoherenciaParentesis ( const string & sCadena )
{
	return ( CoherenciaParejaSignos ( sCadena, '(', ')' ) );
}

bool CoherenciaLlaves ( const string & sCadena  )
{
	return ( CoherenciaParejaSignos ( sCadena, '{', '}' ) );
}

bool CoherenciaCorchetes ( const string & sCadena  )
{
	return ( CoherenciaParejaSignos ( sCadena, '[', ']' ) );
}

bool CoherenciaParejaSignos ( const string & sCadena, char cSigAp, char cSigCl )
{
  	int iAbiertos = 0;
	bool bCoherente = true;
    for ( size_t pos = 0; bCoherente && ( pos < sCadena.size() ); pos = pos + 1 )
    {
        if ( sCadena.at( pos ) == cSigAp )
        {
            iAbiertos = iAbiertos + 1;
        }
        else if ( sCadena.at( pos ) == cSigCl )
        {
			if ( iAbiertos > 0 )
			{
	            iAbiertos = iAbiertos - 1;
			}
			else
			{
				// Cierre sin apertura previa: incoherente.
				bCoherente = false;
			}
        }
    }
	return ( bCoherente && ( iAbiertos == 0 ) );
}

string EliminarCaracter ( const string & sCadena, int iCar )
{
    string sRes = sCadena;
    if ( ( iCar >= 0 ) && ( iCar < (int) sCadena.size() ) )
    {
        sRes.erase ( iCar, 1 );
    }
	return ( sRes );
}

string EliminarCaracteres ( const string & sCadena, int iPosIni, int iNumCars )
{
    string sRes = sCadena;
    if ( ( iPosIni >= 0 ) && ( iPosIni < (int) sCadena.size() ) && ( iNumCars > 0 ) )
    {
        if ( iPosIni + iNumCars > (int) sCadena.size() )
        {
            iNumCars = iNumCars - iPosIni - iNumCars + sCadena.size();
        }
        sRes.erase ( iPosIni, iNumCars );
    }
	return ( sRes );
}

string EliminarPrimerosCaracteres ( const string & sCadena, int iNumCars )
{
	if ( iNumCars > (int) sCadena.size() )
	{
		return ( string ( "" ) );
	}
 	return ( EliminarCaracteres ( sCadena, 0, iNumCars ) );
}

string EliminarUltimosCaracteres ( const string & sCadena, int iNumCars )
{
	if ( iNumCars > (int) sCadena.size() )
	{
		return ( string ( "" ) );
	}
	return ( EliminarCaracteres ( sCadena, sCadena.size() - iNumCars, iNumCars ) );
}

string EscaparRegex ( const string& s )
{
    static const regex caracteresEspeciales(R"([\.\^\$\*\+\?\(\)\[\]\{\}\|\\])");
    return regex_replace(s, caracteresEspeciales, R"(\$&)");
}

string EliminarApariciones ( const string & sCadena1, const string & sCadena2 )
{
	if ( sCadena2.size() == 0 ) 
	{
		return ( sCadena1 );
	}
    regex patron ( sCadena2 );
    return ( regex_replace( sCadena1, patron, "" ) );
}

string EliminarBlancos ( const string & sCadena )
{
	return ( EliminarTodos ( sCadena, ' ' ) );
}

string EliminarTabuladores ( const string & sCadena )
{
	return ( EliminarTodos ( sCadena, '\t' ) );
}

string EliminarCaracteresNoAlfanumericos ( const string & sCadena )
{
    regex patron ( "[^\\w]" );
    return ( regex_replace( sCadena, patron, "" ) );
}

string EliminarCaracteresNoEstandar ( const string & sCadena )
{
    regex patron ( "[^\\u0020-\\u007F]" );
    return ( regex_replace( sCadena, patron, "" ) );
}

string SubcadenaHasta ( const string & sCadena, char cBuscar )
{
	string sRes = sCadena;
    string::size_type pos = sCadena.find( cBuscar );
    if ( pos != string::npos )
    {
        sRes = sCadena.substr( 0, pos );
    }
    return ( sRes );
}

string SubcadenaDesde ( const string & sCadena, char cBuscar )
{
	string sRes = "";
    string::size_type pos = sCadena.find( cBuscar );
    if ( pos != string::npos )
    {
        sRes = sCadena.substr( pos + 1 );
    }
    return ( sRes );
}

string LTrim( const string & sCadena )
{
	string sRes = sCadena;
    sRes.erase( 0, sRes.find_first_not_of( " " ) );
    return ( sRes );
}

string RTrim( const string & sCadena )
{
	string sRes = sCadena;
    sRes.erase( sRes.find_last_not_of( " " ) + 1 );
    return ( sRes );
}

string Trim( const string & sCadena )
{
    return ( RTrim( LTrim ( sCadena ) ) );
}

bool TieneEspacios ( const string & sCadena )
{
	bool bRes = false;
	size_t pos = 0;
	while ( !bRes && ( pos < sCadena.size() ) )
	{
		bRes = isspace( sCadena[ pos ] );
		pos = pos + 1;
	}
	return ( bRes );
}

bool EmpiezaPor ( const string & sCadena, const string & sPrefijo )
{
	string_view sValor = string_view( sCadena );
	return ( sValor.starts_with( sPrefijo ) );
}

bool TerminaPor ( const string & sCadena, const string & sSufijo )
{
	string_view sValor = string_view( sCadena );
	return ( sValor.ends_with( sSufijo ) );
}

bool TerminaEnSaltoLinea ( const string & sCadena )
{
	string_view sValor = string_view( sCadena );
	return ( sValor.ends_with( "\n" ) || sValor.ends_with( "\r" ) );
}

string EliminarUltimoSaltoLinea( const string & sCadena )
{
    string::size_type pos = sCadena.size() - 1;
    while ( ( pos != string::npos ) && ( ( sCadena.at( pos ) == '\n' ) || ( sCadena.at( pos ) == '\r' ) ) )
    {
		pos = pos - 1;
	}
    string sRes = sCadena.substr( 0, pos + 1 );
    return ( sRes );
}

bool SonIgualesIn ( const string & sCadena1, const string & sCadena2 )
{
	return ( equal( sCadena1.begin(), sCadena1.end(),
                      sCadena2.begin(), sCadena2.end(),
                      []( char a, char b )
					  {
                          return tolower( a ) == tolower( b );
                      } ) );
}


bool EsPalabra ( const string & sCadena )
{
	bool bRes = false;
	if ( sCadena.size() > 0 )
	{
		bRes = regex_match( sCadena, regex( "^[A-Za-z]+$" ) );
	}
	return ( bRes );
}

bool EsToken ( const string & sCadena )
{
	bool bRes = false;
	if ( sCadena.size() > 0 )
	{
		bRes = regex_match( sCadena, regex( "^[A-Za-z]([A-Za-z_0-9])+$" ) );
	}
	return ( bRes );
}

bool EsNombreFichero ( const string & sCadena )
{
	bool bRes = false;
	if ( sCadena.size() > 0 )
	{
		// "^[A-Za-z_. $%¿?,;=+-*¡!()[]^{}ºª@\"]+$"
		bRes = regex_match( sCadena, regex( "^[A-Za-z_.0-9]+$" ) ) &&
				( sCadena.compare( "." ) != 0 ) && ( sCadena.compare( ".." ) != 0 );
	}
	return ( bRes );
}

bool EsNatural ( const string & sCadena )
{
	bool bRes = false;
	if ( sCadena.size() > 0 )
	{
		bRes = regex_match( sCadena, regex( "[0-9]+" ) );
	}
	return ( bRes );
}

bool EsEntero ( const string & sCadena )
{
	bool bRes = false;
	if ( sCadena.size() > 0 )
	{
		bRes = regex_match( sCadena, regex( "-?[0-9]+" ) );
	}
	return ( bRes );
}

bool EsReal ( const string & sCadena )
{
	bool bRes = false;
	if ( sCadena.size() > 0 )
	{
		bRes = regex_match( sCadena, regex( "-?[0-9]+([\\.][0-9]+)?" ) );
	}
	return ( bRes );
}

bool EsBooleano ( const string & sCadena )
{
	bool bRes = false;
	if ( sCadena.size() > 0 )
	{
		bRes = ( sCadena.compare( "0" ) == 0 ) ||
			   ( sCadena.compare( "1" ) == 0 ) ||
				SonIgualesIn( sCadena, "Cierto" ) ||
				SonIgualesIn( sCadena, "Falso" ) ||
				SonIgualesIn( sCadena, "True" ) ||
				SonIgualesIn( sCadena, "False" ) ||
				SonIgualesIn( sCadena, "C" ) ||
				SonIgualesIn( sCadena, "F" ) ||
				SonIgualesIn( sCadena, "T" );
	}
	return ( bRes );
}

bool EsURL ( const string & sCadena )
{
	bool bRes = false;
	if ( sCadena.size() > 0 )
	{
		try
		{
			bRes = regex_match( sCadena, regex( REGEX_URL ) );
		}
		catch( exception & ex )
		{
			cerr << ex.what() << endl;
		}
	}
	return ( bRes );
}

bool EsURN ( const string & sCadena )
{
	bool bRes = false;
	if ( sCadena.size() > 0 )
	{
		try
		{
			bRes = regex_match( sCadena, regex( REGEX_URN ) );
		}
		catch( exception & ex )
		{
			cerr << ex.what() << endl;
		}
	}
	return ( bRes );
}

bool EsURI ( const string & sCadena )
{
	bool bRes = false;
	if ( sCadena.size() > 0 )
	{
		try
		{
			bRes = regex_match( sCadena, regex( REGEX_URI ) );
		}
		catch( exception & ex )
		{
			cerr << ex.what() << endl;
		}
	}
	return ( bRes );
}

size_t BuscarPrimero( const string & sCadena, const initializer_list<string> & delimitadores, size_t * tamDelim, size_t posIni )
{
	size_t posRes = string::npos;
	size_t tam = 0;
	for ( auto const& delim : delimitadores )
	{
		size_t pos = sCadena.find ( delim, posIni );
		if ( pos != string::npos )
		{
			if ( posRes == string::npos )
			{
				posRes = pos;
				tam = delim.size();
			}
			else if ( posRes > pos )
			{
				posRes = pos;
				tam = delim.size();
			}
		}
	}
	if ( tamDelim != NULL )
	{
		*tamDelim = tam;
	}
	return( posRes );
}

size_t BuscarPrimero( const string & sCadena, const list<string> & delimitadores, size_t * tamDelim, size_t posIni )
{
	size_t posRes = string::npos;
	size_t tam = 0;
	for ( auto const& delim : delimitadores )
	{
		size_t pos = sCadena.find ( delim, posIni );
		if ( pos != string::npos )
		{
			if ( posRes == string::npos )
			{
				posRes = pos;
				tam = delim.size();
			}
			else if ( posRes > pos )
			{
				posRes = pos;
				tam = delim.size();
			}
		}
	}
	if ( tamDelim != NULL )
	{
		*tamDelim = tam;
	}
	return( posRes );
}

size_t BuscarDesdeAtrasCaracter( const string& sCadena, char c, size_t desde ) 
{
	if (desde == string::npos) 
	{
		desde = sCadena.length() - 1;
	}
	return ( sCadena.rfind(c, desde) );
}

vector<string> Separar ( string sCadena, const initializer_list<string> & delimitadores )
{
    size_t posIni = 0;
    size_t posFin = 0;
	size_t tamDelim = 0;
    vector<string> vecRes;
	if ( ! sCadena.empty() )
	{
		while ( ( posFin = BuscarPrimero( sCadena, delimitadores, &tamDelim, posIni ) ) != string::npos )
		{
			if ( posFin - posIni >=  0 )
			{
				string sToken = sCadena.substr( posIni, posFin - posIni );
				vecRes.push_back ( sToken );
			}
			posIni = posFin + tamDelim;
		}
		if ( posIni <= sCadena.size() )
		{
			string sToken = sCadena.substr ( posIni );
			vecRes.push_back ( sToken );
		}
	}
    return( vecRes );
}

vector<string> Separar ( string sCadena, const list<string> & delimitadores )
{
    size_t posIni = 0;
    size_t posFin = 0;
	size_t tamDelim = 0;
    vector<string> vecRes;
	if ( ! sCadena.empty() )
	{
		while ( ( posFin = BuscarPrimero( sCadena, delimitadores, &tamDelim, posIni ) ) != string::npos )
		{
			if ( posFin - posIni >=  0 )
			{
				string sToken = sCadena.substr( posIni, posFin - posIni );
				vecRes.push_back ( sToken );
			}
			posIni = posFin + tamDelim;
		}
		if ( posIni <= sCadena.size() )
		{
			string sToken = sCadena.substr ( posIni );
			vecRes.push_back ( sToken );
		}
	}
    return( vecRes );
}

int NumPalabras( const string & sCadena, char cDelimitador ) 
{
	int iRes = 0;
	if ( ! sCadena.empty() ) 
	{
		iRes = 1;
		for ( char c : sCadena ) 
		{
			if ( c == cDelimitador ) 
			{
				iRes = iRes + 1;
			}
		}
	}
	return ( iRes );
}

string ExtraerPalabra ( const string & sCadena, int iPos, char cDelimitador ) 
{
	string  sRes = "";
	int 	iInicio = 0;
	int 	iActual = 0;
	int 	iCar = 0; 
	bool 	bEnc = false;
	
	while ( ( iCar <= sCadena.length() ) && !bEnc )
	{
		if ( ( iCar == sCadena.length() ) || ( sCadena[ iCar ] == cDelimitador ) ) 
		{
			if ( iActual == iPos ) 
			{
				bEnc= true;
				sRes = sCadena.substr(iInicio, iCar - iInicio);
			}
			iActual = iActual + 1;
			iInicio = iCar + 1;
		}
		iCar = iCar + 1;
	}
	return ( sRes );
}


			}
		}
	}
}
