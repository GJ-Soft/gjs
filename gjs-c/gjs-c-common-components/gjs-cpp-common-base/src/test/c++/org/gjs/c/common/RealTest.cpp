#include "CppBase.h"


#include <iostream>
#include <cfloat>



using namespace std;
using namespace org::gjs::cpp::common;




static bool TestReal01 ()
{
	cout << "Test Real01:" << endl;
	bool bRes = true;

	// equals ( double ): igualdad exacta y tolerancia relativa.
	if ( ! real::equals ( 1.0, 1.0 ) )
	{
		cout << "Error caso 1" << endl;
		bRes = false;
	}
	if ( ! real::equals ( 0.1 + 0.2, 0.3 ) )
	{
		cout << "Error caso 2: [" << ( 0.1 + 0.2 ) << "]" << endl;
		bRes = false;
	}
	if ( real::equals ( 1.0, 2.0 ) )
	{
		cout << "Error caso 3" << endl;
		bRes = false;
	}
	if ( ! real::equals ( 0.0, 0.0 ) )
	{
		cout << "Error caso 4" << endl;
		bRes = false;
	}
	return ( bRes );
}

static bool TestReal02 ()
{
	cout << "Test Real02:" << endl;
	bool bRes = true;

	// equals ( float ): la tolerancia debe basarse en el epsilon de float,
	// de modo que la suma imprecisa de floats siga considerandose igual.
	if ( ! real::equals ( 1.0f, 1.0f ) )
	{
		cout << "Error caso 1" << endl;
		bRes = false;
	}
	if ( ! real::equals ( 0.1f + 0.2f, 0.3f ) )
	{
		cout << "Error caso 2: [" << ( 0.1f + 0.2f ) << "]" << endl;
		bRes = false;
	}
	if ( real::equals ( 1.0f, 1.5f ) )
	{
		cout << "Error caso 3" << endl;
		bRes = false;
	}
	return ( bRes );
}

static bool TestReal03 ()
{
	cout << "Test Real03:" << endl;
	bool bRes = true;

	// equalsWithPrec ( double ): comparacion por digitos significativos.
	if ( ! real::equalsWithPrec ( 100.0, 100.05, 3 ) )
	{
		cout << "Error caso 1" << endl;
		bRes = false;
	}
	if ( real::equalsWithPrec ( 100.0, 105.0, 3 ) )
	{
		cout << "Error caso 2" << endl;
		bRes = false;
	}
	if ( ! real::equalsWithPrec ( 0.0, 0.0, 3 ) )
	{
		cout << "Error caso 3" << endl;
		bRes = false;
	}
	return ( bRes );
}

static bool TestReal04 ()
{
	cout << "Test Real04:" << endl;
	bool bRes = true;

	// equalsWithPrec: si solo uno de los operandos es cero, deben ser distintos.
	if ( real::equalsWithPrec ( 0.0, 5.0, 3 ) )
	{
		cout << "Error caso 1" << endl;
		bRes = false;
	}
	if ( real::equalsWithPrec ( 5.0, 0.0, 3 ) )
	{
		cout << "Error caso 2" << endl;
		bRes = false;
	}
	if ( real::equalsWithPrec ( 0.0f, 5.0f, 3 ) )
	{
		cout << "Error caso 3" << endl;
		bRes = false;
	}
	return ( bRes );
}

bool TestReal ()
{
	bool bRes = true;
	cout << endl << ANSI::AMARILLO << "[Test Real]" << ANSI::RESETEAR << endl;
	if ( TestReal01() )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout  << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}
	if ( TestReal02() )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout  << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}
	if ( TestReal03() )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout  << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}
	if ( TestReal04() )
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
