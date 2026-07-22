#include "CppCommonSupport.h"
#include <CppBase.h>

#include <AplicacionValidaciones.h>

#include <iostream>


using namespace std;
using namespace org::gjs::cpp::common;




static bool TestAplicCodigoValido01 ()
{
	cout << "Test AplicCodigoValido 01:" << endl;
	bool bRes = true;

	// Codigo alfanumerico de la longitud exacta -> valido.
	if ( ! AplicCodigoValido ( "ABC", 3 ) )
	{
		cout << "Error caso 1: ABC ( 3 ) deberia ser valido" << endl;
		bRes = false;
	}
	// El subrayado esta permitido.
	if ( ! AplicCodigoValido ( "A_C", 3 ) )
	{
		cout << "Error caso 2: A_C ( 3 ) deberia ser valido" << endl;
		bRes = false;
	}
	// Longitud distinta de iTam -> invalido.
	if ( AplicCodigoValido ( "AB", 3 ) )
	{
		cout << "Error caso 3: AB no tiene longitud 3, deberia ser invalido" << endl;
		bRes = false;
	}
	// Un caracter no alfanumerico en medio -> invalido.
	if ( AplicCodigoValido ( "A C", 3 ) )
	{
		cout << "Error caso 4: A C ( con espacio ) deberia ser invalido" << endl;
		bRes = false;
	}
	// iTam <= 0 -> invalido.
	if ( AplicCodigoValido ( "", 0 ) )
	{
		cout << "Error caso 5: iTam 0 deberia ser invalido" << endl;
		bRes = false;
	}
	// El PRIMER caracter tambien se valida ( regresion del off-by-one iCar=1 -> 0 ).
	if ( AplicCodigoValido ( "@BC", 3 ) )
	{
		cout << "Error caso 6: @BC deberia ser invalido ( el primer caracter debe validarse )" << endl;
		bRes = false;
	}
	return ( bRes );
}

static bool TestAplicCodigoUsuario01 ()
{
	cout << "Test AplicCodigoUsuarioValido 01:" << endl;
	bool bRes = true;

	// Longitud dentro de [ 4, 30 ] y alfanumerico -> valido.
	if ( ! AplicCodigoUsuarioValido ( "usuario1" ) )
	{
		cout << "Error caso 1: usuario1 deberia ser valido" << endl;
		bRes = false;
	}
	// Demasiado corto ( < 4 ) -> invalido.
	if ( AplicCodigoUsuarioValido ( "abc" ) )
	{
		cout << "Error caso 2: abc ( 3 ) es demasiado corto" << endl;
		bRes = false;
	}
	// Caracter no valido en medio -> invalido.
	if ( AplicCodigoUsuarioValido ( "us er" ) )
	{
		cout << "Error caso 3: us er ( con espacio ) deberia ser invalido" << endl;
		bRes = false;
	}
	// Primer caracter invalido -> invalido ( regresion del off-by-one ).
	if ( AplicCodigoUsuarioValido ( "@user" ) )
	{
		cout << "Error caso 4: @user deberia ser invalido ( primer caracter )" << endl;
		bRes = false;
	}
	return ( bRes );
}

static bool TestAplicClaveUsuario01 ()
{
	cout << "Test AplicClaveUsuarioValido 01:" << endl;
	bool bRes = true;

	// Cadena imprimible dentro del limite -> valida ( el espacio es imprimible ).
	if ( ! AplicClaveUsuarioValido ( "Clave con espacios 123" ) )
	{
		cout << "Error caso 1: una clave imprimible deberia ser valida" << endl;
		bRes = false;
	}
	// Un caracter de control ( tabulador ) en medio -> invalida.
	if ( AplicClaveUsuarioValido ( "a\tb" ) )
	{
		cout << "Error caso 2: una clave con tabulador deberia ser invalida" << endl;
		bRes = false;
	}
	// Demasiado larga ( > 30 ) -> invalida.
	if ( AplicClaveUsuarioValido ( "0123456789012345678901234567890" ) )
	{
		cout << "Error caso 3: una clave de 31 caracteres deberia ser invalida" << endl;
		bRes = false;
	}
	return ( bRes );
}



bool TestAplicacionValidaciones ()
{
	bool bRes = true;
	cout << endl << ANSI::AMARILLO << "[Test AplicacionValidaciones]" << ANSI::RESETEAR << endl;

	if ( TestAplicCodigoValido01 () )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}

	if ( TestAplicCodigoUsuario01 () )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}

	if ( TestAplicClaveUsuario01 () )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}

	cout << ANSI::AMARILLO << "[Fin]" << ANSI::RESETEAR << endl;
	return ( bRes );
}
