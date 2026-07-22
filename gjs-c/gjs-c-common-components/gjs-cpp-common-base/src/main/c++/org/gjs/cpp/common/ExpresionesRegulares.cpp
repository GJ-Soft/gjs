#include "BaseConfig.h"
#include "ExpresionesRegulares.h"



using namespace std;


namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {

bool CumpleExpresionRegular( const string& cadena, const string& patron ) {
	bool bRes = false;
	try {
		// Se traduce el patron estilo glob/DOS a una expresion regular estandar:
		//   '?'      -> '.'         ( un caracter cualquiera )
		//   '*'      -> '.*'        ( cualquier numero de caracteres )
		//   '(' ')'  -> grupo opcional no capturador '(?:' ... ')?'
		//   el resto -> literal, escapando los metacaracteres de regex
		//               ( . \ + ^ $ | [ ] { } ) para que no se interpreten.
		string patronRegex;
		patronRegex.reserve( patron.size() * 2 );
		for ( char c : patron ) {
			switch ( c ) {
				case '?':
					patronRegex += '.';
					break;
				case '*':
					patronRegex += ".*";
					break;
				case '(':
					patronRegex += "(?:";
					break;
				case ')':
					patronRegex += ")?";
					break;
				case '.':
				case '\\':
				case '+':
				case '^':
				case '$':
				case '|':
				case '[':
				case ']':
				case '{':
				case '}':
					patronRegex += '\\';
					patronRegex += c;
					break;
				default:
					patronRegex += c;
					break;
			}
		}

		regex re( patronRegex );
		bRes = regex_match( cadena, re );
	}
	catch (...) {
	}
	return ( bRes );
}



            }
		}
	}
}
