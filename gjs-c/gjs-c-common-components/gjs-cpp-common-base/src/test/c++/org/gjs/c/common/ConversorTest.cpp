#include "CppBase.h"

#include <iostream>


using namespace std;
using namespace org::gjs::cpp::common;



static bool TestConversor01 ()
{
	cout << "Test Coversor 01:" << endl;
	bool bRes = true;
	Conversor * obj1 = new Conversor( );
	if ( obj1->ConversionValida() )
	{
		cout << "Error caso 1" << endl;
		bRes = false;
	}
	if ( obj1->Cadena().compare ( "" ) != 0 )
	{
		cout << "Error caso 2" << endl;
		bRes = false;
	}
	if ( obj1->Entero() != 0 )
	{
		cout << "Error caso 3" << endl;
		bRes = false;
	}
	if ( obj1->EnteroLargo() != 0 )
	{
		cout << "Error caso 4" << endl;
		bRes = false;
	}
	if ( obj1->EnteroDobleLargo() != 0 )
	{
		cout << "Error caso 5" << endl;
		bRes = false;
	}
	if ( obj1->EnteroSinSigno() != 0 )
	{
		cout << "Error caso 6" << endl;
		bRes = false;
	}
	if ( obj1->EnteroLargoSinSigno() != 0 )
	{
		cout << "Error caso 7" << endl;
		bRes = false;
	}
	if ( obj1->EnteroDobleLargoSinSigno() != 0 )
	{
		cout << "Error caso 8" << endl;
		bRes = false;
	}
	if ( obj1->EnteroDobleLargoSinSigno() != 0 )
	{
		cout << "Error caso 10" << endl;
		bRes = false;
	}
	if ( obj1->Real() != 0 )
	{
		cout << "Error caso 11:" << obj1->Real() << endl;
		bRes = false;
	}
	if ( obj1->RealDoble() != 0 )
	{
		cout << "Error caso 12" << endl;
		bRes = false;
	}
	if ( obj1->RealDobleLargo() != 0 )
	{
		cout << "Error caso 13: " << obj1->RealDobleLargo() << endl;
		bRes = false;
	}
	string sHex = obj1->CadenaHex();
	if ( sHex.compare ( "00" ) != 0 )
	{
		cout << "Error caso 15: " << sHex << endl;
		bRes = false;
	}
	if ( obj1->EsCadenaNumerica () )
	{
		cout << "Error caso 16"  << endl;
		bRes = false;
	}
	if ( obj1->EsCadenaNumericaEntera () )
	{
		cout << "Error caso 17"  << endl;
		bRes = false;
	}
	if ( obj1->EsCadenaNumericaReal () )
	{
		cout << "Error caso 18"  << endl;
		bRes = false;
	}
	if ( obj1->EsCadenaNumericaHexadecimal () )
	{
		cout << "Error caso 19"  << endl;
		bRes = false;
	}
	delete obj1;
	return( bRes );
}

static bool TestConversor02 ()
{
	cout << "Test Coversor 02:" << endl;
	bool bRes = true;
	Conversor * obj1 = new Conversor( ( int ) 1 );
	if ( !obj1->ConversionValida() )
	{
		cout << "Error caso 1" << endl;
		bRes = false;
	}
	if ( obj1->Cadena().compare ( "1" ) != 0 )
	{
		cout << "Error caso 2" << endl;
		bRes = false;
	}
	if ( obj1->Entero() != 1 )
	{
		cout << "Error caso 3" << endl;
		bRes = false;
	}
	if ( obj1->EnteroLargo() != 1 )
	{
		cout << "Error caso 4" << endl;
		bRes = false;
	}
	if ( obj1->EnteroDobleLargo() != 1 )
	{
		cout << "Error caso 5" << endl;
		bRes = false;
	}
	if ( obj1->EnteroSinSigno() != 1 )
	{
		cout << "Error caso 6" << endl;
		bRes = false;
	}
	if ( obj1->EnteroLargoSinSigno() != 1 )
	{
		cout << "Error caso 7" << endl;
		bRes = false;
	}
	if ( obj1->EnteroDobleLargoSinSigno() != 1 )
	{
		cout << "Error caso 8" << endl;
		bRes = false;
	}
	if ( !real::equals ( obj1->Real(), 1.0f ) )
	{
		cout << "Error caso 9" << endl;
		bRes = false;
	}
	if ( !real::equals ( obj1->RealDoble(), 1.0 ) )
	{
		cout << "Error caso 10" << endl;
		bRes = false;
	}
	if ( !real::equals ( obj1->RealDobleLargo(), 1.0l ) )
	{
		cout << "Error caso 11" << obj1->RealDobleLargo() << endl;
		bRes = false;
	}
	string sHex = obj1->CadenaHex();
	if ( sHex.compare ( "01" ) != 0 )
	{
		cout << "Error caso 13" << endl;
		bRes = false;
	}
	if ( ! obj1->EsCadenaNumerica () )
	{
		cout << "Error caso 14" << endl;
		bRes = false;
	}
	if ( ! obj1->EsCadenaNumericaEntera () )
	{
		cout << "Error caso 15" << endl;
		bRes = false;
	}
	if ( ! obj1->EsCadenaNumericaReal () )
	{
		cout << "Error caso 16" << endl;
		bRes = false;
	}
	if ( obj1->EsCadenaNumericaHexadecimal () )
	{
		cout << "Error caso 17" << endl;
		bRes = false;
	}

	delete obj1;
	return( bRes );
}

static bool TestConversor03 ()
{
	cout << "Test Coversor 03:" << endl;
	bool bRes = true;
	Conversor * obj1 = new Conversor( ( long ) 10 );
	if ( !obj1->ConversionValida() )
	{
		cout << "Error caso 1" << endl;
		bRes = false;
	}
	if ( obj1->Cadena().compare ( "10" ) != 0 )
	{
		cout << "Error caso 2" << endl;
		bRes = false;
	}
	if ( obj1->Entero() != 10 )
	{
		cout << "Error caso 3" << endl;
		bRes = false;
	}
	if ( obj1->EnteroLargo() != 10 )
	{
		cout << "Error caso 4" << endl;
		bRes = false;
	}
	if ( obj1->EnteroDobleLargo() != 10 )
	{
		cout << "Error caso 5" << endl;
		bRes = false;
	}
	if ( obj1->EnteroSinSigno() != 10 )
	{
		cout << "Error caso 6" << endl;
		bRes = false;
	}
	if ( obj1->EnteroLargoSinSigno() != 10 )
	{
		cout << "Error caso 7" << endl;
		bRes = false;
	}
	if ( obj1->EnteroDobleLargoSinSigno() != 10 )
	{
		cout << "Error caso 8" << endl;
		bRes = false;
	}
	if ( !real::equals ( obj1->Real(), 10.0f ) )
	{
		cout << "Error caso 9" << endl;
		bRes = false;
	}
	if ( !real::equals ( obj1->RealDoble(), 10.0 ) )
	{
		cout << "Error caso 10" << endl;
		bRes = false;
	}
	if ( !real::equals ( obj1->RealDobleLargo(), 10.0l ) )
	{
		cout << "Error caso 11" << endl;
		bRes = false;
	}
	string sHex = obj1->CadenaHex();
	if ( sHex.compare ( "0a" ) != 0 )
	{
		cout << "Error caso 13" << endl;
		bRes = false;
	}
	delete obj1;
	return( bRes );
}

static bool TestConversor04 ()
{
	cout << "Test Coversor 04:" << endl;
	bool bRes = true;
	Conversor * obj1 = new Conversor( ( long long ) 20 );
	if ( !obj1->ConversionValida() )
	{
		cout << "Error caso 1" << endl;
		bRes = false;
	}
	if ( obj1->Cadena().compare ( "20" ) != 0 )
	{
		cout << "Error caso 2" << endl;
		bRes = false;
	}
	if ( obj1->Entero() != 20 )
	{
		cout << "Error caso 3" << endl;
		bRes = false;
	}
	if ( obj1->EnteroLargo() != 20 )
	{
		cout << "Error caso 4" << endl;
		bRes = false;
	}
	if ( obj1->EnteroDobleLargo() != 20 )
	{
		cout << "Error caso 5" << endl;
		bRes = false;
	}
	if ( obj1->EnteroSinSigno() != 20 )
	{
		cout << "Error caso 6" << endl;
		bRes = false;
	}
	if ( obj1->EnteroLargoSinSigno() != 20 )
	{
		cout << "Error caso 7" << endl;
		bRes = false;
	}
	if ( obj1->EnteroDobleLargoSinSigno() != 20 )
	{
		cout << "Error caso 8" << endl;
		bRes = false;
	}
	if ( !real::equals ( obj1->Real(), 20.0f ) )
	{
		cout << "Error caso 9" << endl;
		bRes = false;
	}
	if ( !real::equals ( obj1->RealDoble(), 20.0 ) )
	{
		cout << "Error caso 10" << endl;
		bRes = false;
	}
	if ( !real::equals ( obj1->RealDobleLargo(), 20.0l ) )
	{
		cout << "Error caso 11" << endl;
		bRes = false;
	}
	string sHex = obj1->CadenaHex();
	if ( sHex.compare ( "14" ) != 0 )
	{
		cout << "Error caso 13" << endl;
		bRes = false;
	}
	delete obj1;
	return( bRes );
}

static bool TestConversor05 ()
{
	cout << "Test Coversor 05:" << endl;
	bool bRes = true;
	Conversor * obj1 = new Conversor( ( unsigned int ) 1 );
	if ( !obj1->ConversionValida() )
	{
		cout << "Error caso 1" << endl;
		bRes = false;
	}
	if ( obj1->Cadena().compare ( "1" ) != 0 )
	{
		cout << "Error caso 2" << endl;
		bRes = false;
	}
	if ( obj1->Entero() != 1 )
	{
		cout << "Error caso 3" << endl;
		bRes = false;
	}
	if ( obj1->EnteroLargo() != 1 )
	{
		cout << "Error caso 4" << endl;
		bRes = false;
	}
	if ( obj1->EnteroDobleLargo() != 1 )
	{
		cout << "Error caso 5" << endl;
		bRes = false;
	}
	if ( obj1->EnteroSinSigno() != 1 )
	{
		cout << "Error caso 6" << endl;
		bRes = false;
	}
	if ( obj1->EnteroLargoSinSigno() != 1 )
	{
		cout << "Error caso 7" << endl;
		bRes = false;
	}
	if ( obj1->EnteroDobleLargoSinSigno() != 1 )
	{
		cout << "Error caso 8" << endl;
		bRes = false;
	}
	if ( !real::equals ( obj1->Real(), 1.0f ) )
	{
		cout << "Error caso 9" << endl;
		bRes = false;
	}
	if ( !real::equals ( obj1->RealDoble(), 1.0 ) )
	{
		cout << "Error caso 10" << endl;
		bRes = false;
	}
	if ( !real::equals ( obj1->RealDobleLargo(), 1.0l ) )
	{
		cout << "Error caso 11" << endl;
		bRes = false;
	}
	string sHex = obj1->CadenaHex();
	if ( sHex.compare ( "01" ) != 0 )
	{
		cout << "Error caso 13" << endl;
		bRes = false;
	}
	delete obj1;
	return( bRes );
}

static bool TestConversor06 ()
{
	cout << "Test Coversor 06:" << endl;
	bool bRes = true;
	Conversor * obj1 = new Conversor( ( unsigned long ) 10 );
	if ( !obj1->ConversionValida() )
	{
		cout << "Error caso 1" << endl;
		bRes = false;
	}
	if ( obj1->Cadena().compare ( "10" ) != 0 )
	{
		cout << "Error caso 2" << endl;
		bRes = false;
	}
	if ( obj1->Entero() != 10 )
	{
		cout << "Error caso 3" << endl;
		bRes = false;
	}
	if ( obj1->EnteroLargo() != 10 )
	{
		cout << "Error caso 4" << endl;
		bRes = false;
	}
	if ( obj1->EnteroDobleLargo() != 10 )
	{
		cout << "Error caso 5" << endl;
		bRes = false;
	}
	if ( obj1->EnteroSinSigno() != 10 )
	{
		cout << "Error caso 6" << endl;
		bRes = false;
	}
	if ( obj1->EnteroLargoSinSigno() != 10 )
	{
		cout << "Error caso 7" << endl;
		bRes = false;
	}
	if ( obj1->EnteroDobleLargoSinSigno() != 10 )
	{
		cout << "Error caso 8: " << obj1->EnteroDobleLargoSinSigno() << endl;
		bRes = false;
	}
	if ( !real::equals ( obj1->Real(), 10.0f ) )
	{
		cout << "Error caso 9" << endl;
		bRes = false;
	}
	if ( !real::equals ( obj1->RealDoble(), 10.0 ) )
	{
		cout << "Error caso 10" << endl;
		bRes = false;
	}
	if ( !real::equals ( obj1->RealDobleLargo(), 10.0l ) )
	{
		cout << "Error caso 11" << endl;
		bRes = false;
	}
	string sHex = obj1->CadenaHex();
	if ( sHex.compare ( "0a" ) != 0 )
	{
		cout << "Error caso 13: " << sHex << endl;
		bRes = false;
	}
	delete obj1;
	return( bRes );
}

static bool TestConversor07 ()
{
	cout << "Test Coversor 07:" << endl;
	bool bRes = true;
	Conversor * obj1 = new Conversor( ( unsigned long long ) 20 );
	if ( !obj1->ConversionValida() )
	{
		cout << "Error caso 1" << endl;
		bRes = false;
	}
	if ( obj1->Cadena().compare ( "20" ) != 0 )
	{
		cout << "Error caso 2: " << obj1->Cadena() << endl;
		bRes = false;
	}
	if ( obj1->Entero() != 20 )
	{
		cout << "Error caso 3" << endl;
		bRes = false;
	}
	if ( obj1->EnteroLargo() != 20 )
	{
		cout << "Error caso 4" << endl;
		bRes = false;
	}
	if ( obj1->EnteroDobleLargo() != 20 )
	{
		cout << "Error caso 5" << endl;
		bRes = false;
	}
	if ( obj1->EnteroSinSigno() != 20 )
	{
		cout << "Error caso 6" << endl;
		bRes = false;
	}
	if ( obj1->EnteroLargoSinSigno() != 20 )
	{
		cout << "Error caso 7" << endl;
		bRes = false;
	}
	if ( obj1->EnteroDobleLargoSinSigno() != 20 )
	{
		cout << "Error caso 8" << endl;
		bRes = false;
	}
	if ( !real::equals ( obj1->Real(), 20.0f ) )
	{
		cout << "Error caso 9" << endl;
		bRes = false;
	}
	if ( !real::equals ( obj1->RealDoble(), 20.0 ) )
	{
		cout << "Error caso 10" << endl;
		bRes = false;
	}
	if ( !real::equals ( obj1->RealDobleLargo(), 20.0l ) )
	{
		cout << "Error caso 11" << endl;
		bRes = false;
	}
	string sHex = obj1->CadenaHex();
	if ( sHex.compare ( "14" ) != 0 )
	{
		cout << "Error caso 13" << endl;
		bRes = false;
	}
	delete obj1;
	return( bRes );
}

static bool TestConversor08 ()
{
	cout << "Test Coversor 08:" << endl;
	bool bRes = true;
	Conversor * obj1 = new Conversor( ( float ) 1.0 );
	if ( !obj1->ConversionValida() )
	{
		cout << "Error caso 1" << endl;
		bRes = false;
	}
	if ( !obj1->Cadena().starts_with ( "1.0" ) )
	{
		cout << "Error caso 2: " << obj1->Cadena() << endl;
		bRes = false;
	}
	if ( obj1->Entero() != 1 )
	{
		cout << "Error caso 3" << endl;
		bRes = false;
	}
	if ( obj1->EnteroLargo() != 1 )
	{
		cout << "Error caso 4" << endl;
		bRes = false;
	}
	if ( obj1->EnteroDobleLargo() != 1 )
	{
		cout << "Error caso 5" << endl;
		bRes = false;
	}
	if ( obj1->EnteroSinSigno() != 1 )
	{
		cout << "Error caso 6" << endl;
		bRes = false;
	}
	if ( obj1->EnteroLargoSinSigno() != 1 )
	{
		cout << "Error caso 7" << endl;
		bRes = false;
	}
	if ( obj1->EnteroDobleLargoSinSigno() != 1 )
	{
		cout << "Error caso 8" << endl;
		bRes = false;
	}
	if ( !real::equals ( obj1->Real(), 1.0f ) )
	{
		cout << "Error caso 9" << endl;
		bRes = false;
	}
	if ( !real::equals ( obj1->RealDoble(), 1.0 ) )
	{
		cout << "Error caso 10" << endl;
		bRes = false;
	}
	if ( !real::equals ( obj1->RealDobleLargo(), 1.0l ) )
	{
		cout << "Error caso 11" << endl;
		bRes = false;
	}
	string sHex = obj1->CadenaHex();
	if ( sHex.compare ( "01" ) != 0 )
	{
		cout << "Error caso 13" << endl;
		bRes = false;
	}
	if ( ! obj1->EsCadenaNumerica () )
	{
		cout << "Error caso 14" << endl;
		bRes = false;
	}
	if ( obj1->EsCadenaNumericaEntera () )
	{
		cout << "Error caso 15" << endl;
		bRes = false;
	}
	if ( ! obj1->EsCadenaNumericaReal () )
	{
		cout << "Error caso 16" << endl;
		bRes = false;
	}
	if ( obj1->EsCadenaNumericaHexadecimal () )
	{
		cout << "Error caso 17" << sHex << endl;
		bRes = false;
	}
	delete obj1;
	return( bRes );
}

static bool TestConversor09 ()
{
	cout << "Test Coversor 09:" << endl;
	bool bRes = true;
	Conversor * obj1 = new Conversor( ( double ) 10.1 );
	if ( !obj1->ConversionValida() )
	{
		cout << "Error caso 1" << endl;
		bRes = false;
	}
	if ( !obj1->Cadena().starts_with ( "10.1" ) )
	{
		cout << "Error caso 2: " << obj1->Cadena() << endl;
		bRes = false;
	}
	if ( obj1->Entero() != 10 )
	{
		cout << "Error caso 3" << endl;
		bRes = false;
	}
	if ( obj1->EnteroLargo() != 10 )
	{
		cout << "Error caso 4" << endl;
		bRes = false;
	}
	if ( obj1->EnteroDobleLargo() != 10 )
	{
		cout << "Error caso 5" << endl;
		bRes = false;
	}
	if ( obj1->EnteroSinSigno() != 10 )
	{
		cout << "Error caso 6" << endl;
		bRes = false;
	}
	if ( obj1->EnteroLargoSinSigno() != 10 )
	{
		cout << "Error caso 7" << endl;
		bRes = false;
	}
	if ( obj1->EnteroDobleLargoSinSigno() != 10 )
	{
		cout << "Error caso 8" << endl;
		bRes = false;
	}
	if ( !real::equals ( obj1->Real(), 10.1f ) )
	{
		cout << "Error caso 9: " << obj1->Real() << endl;
		bRes = false;
	}
	if ( !real::equals ( obj1->RealDoble(), 10.1 ) )
	{
		cout << "Error caso 10" << endl;
		bRes = false;
	}
	if ( !real::equalsWithPrec ( obj1->RealDobleLargo(), 10.1l, 3 ) )
	{
		cout << "Error caso 11: " << obj1->RealDobleLargo() << endl;
		bRes = false;
	}
	string sHex = obj1->CadenaHex();
	if ( sHex.compare ( "0a" ) != 0 )
	{
		cout << "Error caso 13" << endl;
		bRes = false;
	}
	delete obj1;
	return( bRes );
}

static bool TestConversor10 ()
{
	cout << "Test Coversor 10:" << endl;
	bool bRes = true;
	Conversor * obj1 = new Conversor( ( long double) 20.4 );
	if ( !obj1->ConversionValida() )
	{
		cout << "Error caso 1" << endl;
		bRes = false;
	}
	if ( !obj1->Cadena().starts_with ( "20.4" ) )
	{
		cout << "Error caso 2: " << obj1->Cadena() << endl;
		bRes = false;
	}
	if ( obj1->Entero() != 20 )
	{
		cout << "Error caso 3" << endl;
		bRes = false;
	}
	if ( obj1->EnteroLargo() != 20 )
	{
		cout << "Error caso 4" << endl;
		bRes = false;
	}
	if ( obj1->EnteroDobleLargo() != 20 )
	{
		cout << "Error caso 5" << endl;
		bRes = false;
	}
	if ( obj1->EnteroSinSigno() != 20 )
	{
		cout << "Error caso 6" << endl;
		bRes = false;
	}
	if ( obj1->EnteroLargoSinSigno() != 20 )
	{
		cout << "Error caso 7" << endl;
		bRes = false;
	}
	if ( obj1->EnteroDobleLargoSinSigno() != 20 )
	{
		cout << "Error caso 8" << endl;
		bRes = false;
	}
	if ( !real::equals ( obj1->Real(), 20.4f ) )
	{
		cout << "Error caso 9: " << obj1->Real() << endl;
		bRes = false;
	}
	if ( !real::equals ( obj1->RealDoble(), 20.4 ) )
	{
		cout << "Error caso 10" << endl;
		bRes = false;
	}
	if ( !real::equalsWithPrec ( obj1->RealDobleLargo(), 20.4l, 3 ) )
	{
		cout << "Error caso 11: " << obj1->RealDobleLargo() << endl;
		bRes = false;
	}
	string sHex = obj1->CadenaHex();
	if ( sHex.compare ( "14" ) != 0 )
	{
		cout << "Error caso 13" << endl;
		bRes = false;
	}
	delete obj1;
	return( bRes );
}

static bool TestConversor11 ()
{
	cout << "Test Coversor 11:" << endl;
	bool bRes = true;
	Conversor * obj1 = new Conversor( "-1.0" );
	if ( obj1->ConversionValida() )
	{
		cout << "Error caso 1" << endl;
		bRes = false;
	}
	if ( !obj1->Cadena().starts_with ( "-1.0" ) != 0 )
	{
		cout << "Error caso 2" << endl;
		bRes = false;
	}
	if ( obj1->Entero() != -1 )
	{
		cout << "Error caso 3" << endl;
		bRes = false;
	}
	if ( obj1->EnteroLargo() != -1 )
	{
		cout << "Error caso 4" << endl;
		bRes = false;
	}
	if ( obj1->EnteroDobleLargo() != -1 )
	{
		cout << "Error caso 5: " << obj1->EnteroDobleLargo() << endl;
		bRes = false;
	}
	if ( obj1->EnteroSinSigno() != 0 )
	{
		cout << "Error caso 6" << endl;
		bRes = false;
	}
	if ( obj1->EnteroLargoSinSigno() != 0 )
	{
		cout << "Error caso 7" << endl;
		bRes = false;
	}
	if ( obj1->EnteroDobleLargoSinSigno() != 0 )
	{
		cout << "Error caso 8" << endl;
		bRes = false;
	}
	if ( !real::equals ( obj1->Real(), -1.0f ) )
	{
		cout << "Error caso 9" << endl;
		bRes = false;
	}
	if ( !real::equals ( obj1->RealDoble(), -1.0 ) )
	{
		cout << "Error caso 10: " << obj1->RealDoble() << endl;
		bRes = false;
	}
	if ( !real::equals ( obj1->RealDobleLargo(), -1.0l ) )
	{
		cout << "Error caso 11: " << obj1->RealDobleLargo() << endl;
		bRes = false;
	}
	string sHex = obj1->CadenaHex();
	if ( sHex.compare ( "00" ) != 0 )
	{
		cout << "Error caso 13: " << sHex << endl;
		bRes = false;
	}
	delete obj1;
	return( bRes );
}

static bool TestConversor12 ()
{
	cout << "Test Coversor 12:" << endl;
	bool bRes = true;
	string valor = string( "1.0" );
	Conversor * obj1 = new Conversor( valor );
	if ( !obj1->ConversionValida() )
	{
		cout << "Error caso 1" << endl;
		bRes = false;
	}
	if ( obj1->Cadena().compare ( "1.0" ) != 0 )
	{
		cout << "Error caso 2" << endl;
		bRes = false;
	}
	if ( obj1->Entero() != 1 )
	{
		cout << "Error caso 3" << endl;
		bRes = false;
	}
	if ( obj1->EnteroLargo() != 1 )
	{
		cout << "Error caso 4" << endl;
		bRes = false;
	}
	if ( obj1->EnteroDobleLargo() != 1 )
	{
		cout << "Error caso 5" << endl;
		bRes = false;
	}
	if ( obj1->EnteroSinSigno() != 1 )
	{
		cout << "Error caso 6" << endl;
		bRes = false;
	}
	if ( obj1->EnteroLargoSinSigno() != 1 )
	{
		cout << "Error caso 7" << endl;
		bRes = false;
	}
	if ( obj1->EnteroDobleLargoSinSigno() != 1 )
	{
		cout << "Error caso 8" << endl;
		bRes = false;
	}
	if ( !real::equals ( obj1->Real(), 1.0f ) )
	{
		cout << "Error caso 9" << endl;
		bRes = false;
	}
	if ( !real::equals ( obj1->RealDoble(), 1.0 ) )
	{
		cout << "Error caso 10: " << obj1->RealDoble() << endl;
		bRes = false;
	}
	if ( !real::equals ( obj1->RealDobleLargo(), 1.0l ) )
	{
		cout << "Error caso 11" << endl;
		bRes = false;
	}
	string sHex = obj1->CadenaHex();
	if ( sHex.compare ( "01" ) != 0 )
	{
		cout << "Error caso 13" << endl;
		bRes = false;
	}
	delete obj1;
	return( bRes );
}

static bool TestConversor13 ()
{
	cout << "Test Coversor 13:" << endl;
	bool bRes = true;
	string valor = string( "-1.0" );
	Conversor * obj1 = new Conversor( (const string &) valor );
	if ( obj1->ConversionValida() )
	{
		cout << "Error caso 1" << endl;
		bRes = false;
	}
	if ( obj1->Cadena().compare ( "-1.0" ) != 0 )
	{
		cout << "Error caso 2" << endl;
		bRes = false;
	}
	if ( obj1->Entero() != -1 )
	{
		cout << "Error caso 3" << endl;
		bRes = false;
	}
	if ( obj1->EnteroLargo() != -1 )
	{
		cout << "Error caso 4" << endl;
		bRes = false;
	}
	if ( obj1->EnteroDobleLargo() != -1 )
	{
		cout << "Error caso 5" << endl;
		bRes = false;
	}
	if ( obj1->EnteroSinSigno() != 0 )
	{
		cout << "Error caso 6" << endl;
		bRes = false;
	}
	if ( obj1->EnteroLargoSinSigno() != 0 )
	{
		cout << "Error caso 7" << endl;
		bRes = false;
	}
	if ( obj1->EnteroDobleLargoSinSigno() != 0 )
	{
		cout << "Error caso 8" << endl;
		bRes = false;
	}
	if ( !real::equals ( obj1->Real(), -1.0f ) )
	{
		cout << "Error caso 9" << endl;
		bRes = false;
	}
	if ( !real::equals ( obj1->RealDoble(), -1.0 ) )
	{
		cout << "Error caso 10" << endl;
		bRes = false;
	}
	if ( !real::equals ( obj1->RealDobleLargo(), -1.0l ) )
	{
		cout << "Error caso 11" << endl;
		bRes = false;
	}
	string sHex = obj1->CadenaHex();
	if ( sHex.compare ( "00" ) != 0 )
	{
		cout << "Error caso 13" << endl;
		bRes = false;
	}
	delete obj1;
	return( bRes );
}

static bool TestConversor14 ()
{
	cout << "Test Coversor 14:" << endl;
	bool bRes = true;
	string valor = string( "1.0" );
	Conversor * obj1 = new Conversor( (char *) valor.c_str() );
	if ( !obj1->ConversionValida() )
	{
		cout << "Error caso 1" << endl;
		bRes = false;
	}
	if ( obj1->Cadena().compare ( "1.0" ) != 0 )
	{
		cout << "Error caso 2" << endl;
		bRes = false;
	}
	if ( obj1->Entero() != 1 )
	{
		cout << "Error caso 3" << endl;
		bRes = false;
	}
	if ( obj1->EnteroLargo() != 1 )
	{
		cout << "Error caso 4" << endl;
		bRes = false;
	}
	if ( obj1->EnteroDobleLargo() != 1 )
	{
		cout << "Error caso 5" << endl;
		bRes = false;
	}
	if ( obj1->EnteroSinSigno() != 1)
	{
		cout << "Error caso 6" << endl;
		bRes = false;
	}
	if ( obj1->EnteroLargoSinSigno() != 1 )
	{
		cout << "Error caso 7" << endl;
		bRes = false;
	}
	if ( obj1->EnteroDobleLargoSinSigno() != 1 )
	{
		cout << "Error caso 8" << endl;
		bRes = false;
	}
	if ( !real::equals ( obj1->Real(), 1.0f ) )
	{
		cout << "Error caso 9" << endl;
		bRes = false;
	}
	if ( !real::equals ( obj1->RealDoble(), 1.0 ) )
	{
		cout << "Error caso 10" << endl;
		bRes = false;
	}
	if ( !real::equals ( obj1->RealDobleLargo(), 1.0l ) )
	{
		cout << "Error caso 11" << endl;
		bRes = false;
	}
	string sHex = obj1->CadenaHex();
	if ( sHex.compare ( "01" ) != 0 )
	{
		cout << "Error caso 13" << endl;
		bRes = false;
	}
	delete obj1;
	return( bRes );
}

static bool TestConversor15 ()
{
	cout << "Test Coversor 15:" << endl;
	bool bRes = true;
	Conversor * obj1 = new Conversor( "XX" );
	if ( obj1->ConversionValida() )
	{
		cout << "Error caso 1" << endl;
		bRes = false;
	}
	if ( obj1->Cadena().compare ( "XX" ) != 0 )
	{
		cout << "Error caso 2" << endl;
		bRes = false;
	}
	if ( obj1->Entero() != 0 )
	{
		cout << "Error caso 3" << endl;
		bRes = false;
	}
	if ( obj1->EnteroLargo() != 0 )
	{
		cout << "Error caso 4" << endl;
		bRes = false;
	}
	if ( obj1->EnteroDobleLargo() != 0 )
	{
		cout << "Error caso 5" << endl;
		bRes = false;
	}
	if ( obj1->EnteroSinSigno() != 0 )
	{
		cout << "Error caso 6" << endl;
		bRes = false;
	}
	if ( obj1->EnteroLargoSinSigno() != 0 )
	{
		cout << "Error caso 7" << endl;
		bRes = false;
	}
	if ( obj1->EnteroDobleLargoSinSigno() != 0 )
	{
		cout << "Error caso 8" << endl;
		bRes = false;
	}
	if ( obj1->Real() != 0 )
	{
		cout << "Error caso 9" << endl;
		bRes = false;
	}
	if ( obj1->RealDoble() != 0 )
	{
		cout << "Error caso 10" << endl;
		bRes = false;
	}
	if ( obj1->RealDobleLargo() != 0 )
	{
		cout << "Error caso 11" << endl;
		bRes = false;
	}
	string sHex = obj1->CadenaHex();
	if ( sHex.compare ( "00" ) != 0 )
	{
		cout << "Error caso 13" << endl;
		bRes = false;
	}
	delete obj1;
	return( bRes );
}

static bool TestConversor16 ()
{
	cout << "Test Coversor 16:" << endl;
	bool bRes = true;
	Conversor * obj1 = new Conversor( (char *) NULL );
	if ( obj1->ConversionValida() )
	{
		cout << "Error caso 1" << endl;
		bRes = false;
	}
	if ( obj1->Cadena().compare ( "" ) != 0 )
	{
		cout << "Error caso 2" << endl;
		bRes = false;
	}
	if ( obj1->Entero() != 0 )
	{
		cout << "Error caso 3" << endl;
		bRes = false;
	}
	if ( obj1->EnteroLargo() != 0 )
	{
		cout << "Error caso 4" << endl;
		bRes = false;
	}
	if ( obj1->EnteroDobleLargo() != 0 )
	{
		cout << "Error caso 5" << endl;
		bRes = false;
	}
	if ( obj1->EnteroSinSigno() != 0 )
	{
		cout << "Error caso 6" << endl;
		bRes = false;
	}
	if ( obj1->EnteroLargoSinSigno() != 0 )
	{
		cout << "Error caso 7" << endl;
		bRes = false;
	}
	if ( obj1->EnteroDobleLargoSinSigno() != 0 )
	{
		cout << "Error caso 8" << endl;
		bRes = false;
	}
	if ( obj1->Real() != 0 )
	{
		cout << "Error caso 9" << endl;
		bRes = false;
	}
	if ( obj1->RealDoble() != 0 )
	{
		cout << "Error caso 10" << endl;
		bRes = false;
	}
	if ( obj1->RealDobleLargo() != 0 )
	{
		cout << "Error caso 11" << endl;
		bRes = false;
	}
	string sHex = obj1->CadenaHex();
	if ( sHex.compare ( "00" ) != 0 )
	{
		cout << "Error caso 13" << endl;
		bRes = false;
	}
	if ( obj1->EsCadenaNumerica () )
	{
		cout << "Error caso 14" << endl;
		bRes = false;
	}
	if ( obj1->EsCadenaNumericaEntera () )
	{
		cout << "Error caso 15" << endl;
		bRes = false;
	}
	if ( obj1->EsCadenaNumericaReal () )
	{
		cout << "Error caso 16" << endl;
		bRes = false;
	}
	if ( obj1->EsCadenaNumericaHexadecimal () )
	{
		cout << "Error caso 17" << endl;
		bRes = false;
	}
	delete obj1;
	return( bRes );
}


static bool TestConversor17 ()
{
	cout << "Test Coversor 17:" << endl;
	bool bRes = true;
	Conversor * obj1 = new Conversor();
	obj1->EstablecerValorHex ( "01" );
	if ( !obj1->ConversionValida() )
	{
		cout << "Error caso 1" << endl;
		bRes = false;
	}
	if ( obj1->Cadena().compare ( "01" ) != 0 )
	{
		cout << "Error caso 2" << endl;
		bRes = false;
	}
	if ( obj1->Entero() != 1 )
	{
		cout << "Error caso 3" << endl;
		bRes = false;
	}
	if ( obj1->EnteroLargo() != 1 )
	{
		cout << "Error caso 4" << endl;
		bRes = false;
	}
	if ( obj1->EnteroDobleLargo() != 1 )
	{
		cout << "Error caso 5: " << obj1->EnteroDobleLargo() << endl;
		bRes = false;
	}
	if ( obj1->EnteroSinSigno() != 1 )
	{
		cout << "Error caso 6" << endl;
		bRes = false;
	}
	if ( obj1->EnteroLargoSinSigno() != 1 )
	{
		cout << "Error caso 7" << endl;
		bRes = false;
	}
	if ( obj1->EnteroDobleLargoSinSigno() != 1 )
	{
		cout << "Error caso 8" << endl;
		bRes = false;
	}
	if ( !real::equals ( obj1->Real(), 1.0f ) )
	{
		cout << "Error caso 9" << endl;
		bRes = false;
	}
	if ( !real::equals ( obj1->RealDoble(), 1.0 ) )
	{
		cout << "Error caso 10" << endl;
		bRes = false;
	}
	if ( !real::equals ( obj1->RealDobleLargo(), 1.0l ) )
	{
		cout << "Error caso 11" << endl;
		bRes = false;
	}
	string sHex = obj1->CadenaHex();
	if ( sHex.compare ( "01" ) != 0 )
	{
		cout << "Error caso 13" << endl;
		bRes = false;
	}
	if ( ! obj1->EsCadenaNumerica () )
	{
		cout << "Error caso 14" << endl;
		bRes = false;
	}
	if ( ! obj1->EsCadenaNumericaEntera () )
	{
		cout << "Error caso 15" << endl;
		bRes = false;
	}
	if ( ! obj1->EsCadenaNumericaReal () )
	{
		cout << "Error caso 16" << endl;
		bRes = false;
	}
	if ( ! obj1->EsCadenaNumericaHexadecimal () )
	{
		cout << "Error caso 17" << endl;
		bRes = false;
	}
	delete obj1;
	return( bRes );
}


bool TestConversor ()
{
	bool bRes = true;
	cout << endl << ANSI::AMARILLO << "[Test Conversor]" << ANSI::RESETEAR << endl;
	if ( TestConversor01() )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout  << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}
	if ( TestConversor02() )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout  << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}
	if ( TestConversor03() )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout  << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}
	if ( TestConversor04() )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout  << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}
	if ( TestConversor05() )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout  << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}
	if ( TestConversor06() )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout  << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}
	if ( TestConversor07() )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout  << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}
	if ( TestConversor08() )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout  << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}
	if ( TestConversor09() )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout  << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}
	if ( TestConversor10() )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout  << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}
	if ( TestConversor11() )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout  << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}
	if ( TestConversor12() )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout  << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}
	if ( TestConversor13() )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout  << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}
	if ( TestConversor14() )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout  << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}
	if ( TestConversor15() )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout  << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}
	if ( TestConversor16() )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout  << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}
	if ( TestConversor17() )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout  << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}
	cout << ANSI::AMARILLO << "[Fin]" << ANSI::RESETEAR << endl;
	return ( bRes );
}
