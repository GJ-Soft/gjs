
#include "../CommonSupportConfig.h"

#include <Configuracion.h>
#include <ESExcepcion.h>

#include <fstream>



using namespace std;

namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {
				namespace config
				{


/* ---------------------------------------------------------------------------
   Lectura de ficheros en formato properties de Java:

   - Se ignoran las lineas en blanco y las que empiezan, tras los blancos, por
     '#' o '!'.
   - La clave acaba en el primer '=', ':' o blanco SIN ESCAPAR. Despues se
     descartan los blancos, un unico '=' o ':' si lo hay, y mas blancos; el
     resto es el valor.
   - Una linea que acaba en un numero IMPAR de barras invertidas continua en la
     siguiente, a la que se le quitan los blancos iniciales.
   - Escapes en clave y valor: \t \n \r \f, \uXXXX ( con pares suplentes ), y
     \<cualquier otro>, que da ese caracter tal cual: asi funcionan la barra
     doble, los dos puntos y el igual escapados, y el blanco escapado.
   --------------------------------------------------------------------------- */

static bool _EsBlanco ( char cVal )
{
	return ( ( cVal == ' ' ) || ( cVal == '\t' ) || ( cVal == '\f' ) );
}

/* Barras invertidas seguidas al final: si son impares, la ultima es de
   continuacion; si son pares, estan todas escapadas entre si. */
static size_t _ContarBarrasFinales ( const string & sLinea )
{
	size_t uCuenta = 0;

	while ( ( uCuenta < sLinea.length () ) &&
			( sLinea [ sLinea.length () - 1 - uCuenta ] == '\\' ) )
	{
		uCuenta = uCuenta + 1;
	}
	return ( uCuenta );
}

static void _AnadirUtf8 ( string & sDestino, unsigned long ulCodigo )
{
	if ( ulCodigo < 0x80 )
	{
		sDestino += ( char ) ulCodigo;
	}
	else if ( ulCodigo < 0x800 )
	{
		sDestino += ( char ) ( 0xC0 | ( ulCodigo >> 6 ) );
		sDestino += ( char ) ( 0x80 | ( ulCodigo & 0x3F ) );
	}
	else if ( ulCodigo < 0x10000 )
	{
		sDestino += ( char ) ( 0xE0 | ( ulCodigo >> 12 ) );
		sDestino += ( char ) ( 0x80 | ( ( ulCodigo >> 6 ) & 0x3F ) );
		sDestino += ( char ) ( 0x80 | ( ulCodigo & 0x3F ) );
	}
	else
	{
		sDestino += ( char ) ( 0xF0 | ( ulCodigo >> 18 ) );
		sDestino += ( char ) ( 0x80 | ( ( ulCodigo >> 12 ) & 0x3F ) );
		sDestino += ( char ) ( 0x80 | ( ( ulCodigo >> 6 ) & 0x3F ) );
		sDestino += ( char ) ( 0x80 | ( ulCodigo & 0x3F ) );
	}
}

/* Lee la secuencia unicode a partir de uPos, que apunta a la 'u'. Devuelve
   falso si no hay cuatro digitos hexadecimales detras. */
static bool _LeerUnicode ( const string & sTexto, size_t uPos, unsigned long & ulCodigo )
{
	if ( ( uPos + 4 ) >= sTexto.length () )
	{
		return ( false );
	}
	ulCodigo = 0;
	for ( size_t uDig = 1; uDig <= 4; uDig = uDig + 1 )
	{
		char			cVal = sTexto [ uPos + uDig ];
		unsigned long	ulDigito;

		if ( ( cVal >= '0' ) && ( cVal <= '9' ) )
		{
			ulDigito = ( unsigned long ) ( cVal - '0' );
		}
		else if ( ( cVal >= 'a' ) && ( cVal <= 'f' ) )
		{
			ulDigito = ( unsigned long ) ( cVal - 'a' + 10 );
		}
		else if ( ( cVal >= 'A' ) && ( cVal <= 'F' ) )
		{
			ulDigito = ( unsigned long ) ( cVal - 'A' + 10 );
		}
		else
		{
			return ( false );
		}
		ulCodigo = ( ulCodigo * 16 ) + ulDigito;
	}
	return ( true );
}

static string _Desescapar ( const string & sTexto )
{
	string	sRes;
	size_t	uPos = 0;

	while ( uPos < sTexto.length () )
	{
		if ( ( sTexto [ uPos ] != '\\' ) || ( ( uPos + 1 ) >= sTexto.length () ) )
		{
			sRes += sTexto [ uPos ];
			uPos = uPos + 1;
		}
		else
		{
			char cEscapado = sTexto [ uPos + 1 ];

			if ( cEscapado == 'u' )
			{
				unsigned long ulCodigo;

				if ( _LeerUnicode ( sTexto, uPos + 1, ulCodigo ) )
				{
					uPos = uPos + 6;
					/* Un suplente alto solo vale acompanado del bajo. */
					if ( ( ulCodigo >= 0xD800 ) && ( ulCodigo <= 0xDBFF ) &&
						 ( ( uPos + 1 ) < sTexto.length () ) &&
						 ( sTexto [ uPos ] == '\\' ) && ( sTexto [ uPos + 1 ] == 'u' ) )
					{
						unsigned long ulBajo;

						if ( _LeerUnicode ( sTexto, uPos + 1, ulBajo ) &&
							 ( ulBajo >= 0xDC00 ) && ( ulBajo <= 0xDFFF ) )
						{
							ulCodigo = 0x10000 + ( ( ulCodigo - 0xD800 ) << 10 )
											   + ( ulBajo - 0xDC00 );
							uPos = uPos + 6;
						}
					}
					_AnadirUtf8 ( sRes, ulCodigo );
				}
				else
				{
					/* Secuencia mal formada: se deja la 'u', como hace Java. */
					sRes += 'u';
					uPos = uPos + 2;
				}
			}
			else
			{
				switch ( cEscapado )
				{
					case 't':	sRes += '\t';		break;
					case 'n':	sRes += '\n';		break;
					case 'r':	sRes += '\r';		break;
					case 'f':	sRes += '\f';		break;
					default:	sRes += cEscapado;	break;
				}
				uPos = uPos + 2;
			}
		}
	}
	return ( sRes );
}

/* Parte la linea logica en clave y valor siguiendo las reglas de Java. */
static void _PartirPropiedad ( const string & sLinea, string & sClave, string & sValor )
{
	size_t uFinClave = sLinea.length ();
	size_t uPos = 0;

	while ( uPos < sLinea.length () )
	{
		char cVal = sLinea [ uPos ];

		if ( cVal == '\\' )
		{
			uPos = uPos + 2;					/* el siguiente esta escapado */
			continue;
		}
		if ( ( cVal == '=' ) || ( cVal == ':' ) || _EsBlanco ( cVal ) )
		{
			uFinClave = uPos;
			break;
		}
		uPos = uPos + 1;
	}
	sClave = _Desescapar ( sLinea.substr ( 0, uFinClave ) );

	/* Blancos, un separador explicito opcional, y mas blancos. */
	uPos = uFinClave;
	while ( ( uPos < sLinea.length () ) && _EsBlanco ( sLinea [ uPos ] ) )
	{
		uPos = uPos + 1;
	}
	if ( ( uPos < sLinea.length () ) &&
		 ( ( sLinea [ uPos ] == '=' ) || ( sLinea [ uPos ] == ':' ) ) )
	{
		uPos = uPos + 1;
		while ( ( uPos < sLinea.length () ) && _EsBlanco ( sLinea [ uPos ] ) )
		{
			uPos = uPos + 1;
		}
	}
	sValor = _Desescapar ( sLinea.substr ( uPos ) );
}

static void _GuardarPropiedad ( const string & sLogica, map<string, string> & mapDestino )
{
	string sClave;
	string sValor;

	_PartirPropiedad ( sLogica, sClave, sValor );
	if ( ! sClave.empty () )
	{
		mapDestino [ sClave ] = sValor;
	}
}


map<string, string> LeerPropiedades ( string sRutaFichero )
{
	map<string, string>	mapRes;
	ifstream			ifsFichero;

	try
	{
		/* failbit solo para la apertura: getline lo activa al llegar al final del
		   fichero, asi que dejarlo puesto convertiria el final normal de la
		   lectura en una excepcion. Despues solo interesan los errores de verdad. */
		ifsFichero.exceptions ( std::ios::failbit | std::ios::badbit );
		ifsFichero.open ( sRutaFichero );
		ifsFichero.exceptions ( std::ios::badbit );

		string sLogica;
		string sLinea;

		while ( getline ( ifsFichero, sLinea ) )
		{
			/* Un fichero con finales CRLF leido en POSIX deja el retorno de carro. */
			if ( ( ! sLinea.empty () ) && ( sLinea.back () == '\r' ) )
			{
				sLinea.pop_back ();
			}

			size_t uIni = 0;
			while ( ( uIni < sLinea.length () ) && _EsBlanco ( sLinea [ uIni ] ) )
			{
				uIni = uIni + 1;
			}

			if ( sLogica.empty () )
			{
				if ( uIni >= sLinea.length () )
				{
					continue;					/* linea en blanco */
				}
				if ( ( sLinea [ uIni ] == '#' ) || ( sLinea [ uIni ] == '!' ) )
				{
					continue;					/* comentario */
				}
				sLogica = sLinea.substr ( uIni );
			}
			else
			{
				sLogica = sLogica + sLinea.substr ( uIni );
			}

			if ( ( _ContarBarrasFinales ( sLogica ) % 2 ) == 1 )
			{
				sLogica.pop_back ();			/* la barra de continuacion no es dato */
				continue;
			}

			_GuardarPropiedad ( sLogica, mapRes );
			sLogica.clear ();
		}
		/* El fichero puede acabar con una continuacion sin cerrar. */
		if ( ! sLogica.empty () )
		{
			_GuardarPropiedad ( sLogica, mapRes );
		}
		ifsFichero.close ();
	}
	catch ( const std::ios_base::failure & exFallo )
	{
		throw ( ESExcepcion ( "Configuracion", "LeerPropiedades", exFallo ) );
	}
	return ( mapRes );
}

				}
 			}
		}
	}
}
