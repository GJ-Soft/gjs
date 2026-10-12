#include "CppCommonIo.h"
#include "URI.h"

#include <CppBase.h>



using namespace std;
using namespace org::gjs::cpp::common;




static bool TestURI01 ()
{
	cout << "Test URI 01:" << endl;
	bool bRes = true;

	try
	{
		URI * uri = new URI();
		if ( uri->EsValido() ||
			 ( uri->getProtocolo().size() != 0 ) ||
			 ( uri->getPuerto().size() != 0 ) ||
			 ( uri->getDominio().size() != 0 ) ||
			 ( uri->getRuta().size() != 0 ) ||
			 ( uri->NumParametros() != 0 ) ||
			 ( uri->toString().compare( "" ) != 0 ) )
		{
			cout << "Error caso 1 URI=[" << uri->toString() << "]" << endl;
			bRes = false;
		}
		uri->setProtocolo( "ftp" );
		if ( uri->EsValido() ||
			 ( uri->getProtocolo().compare( "ftp" ) != 0 ) ||
			 ( uri->getPuerto().size() != 0 ) ||
			 ( uri->getDominio().size() != 0 ) ||
			 ( uri->getRuta().size() != 0 ) ||
			 ( uri->NumParametros() != 0 ) ||
			 ( uri->toString().compare( "ftp://" ) != 0 ) )
		{
			cout << "Error caso 2 URI=[" << uri->toString() << "]" << endl;
			bRes = false;
		}
		uri->setDominio( "sobrarbe.ara" );
		if ( !uri->EsValido() ||
			 ( uri->getProtocolo().compare( "ftp" ) != 0 ) ||
			 ( uri->getPuerto().size() != 0 ) ||
			 ( uri->getDominio().compare( "sobrarbe.ara" ) != 0 ) ||
			 ( uri->getRuta().size() != 0 ) ||
			 ( uri->NumParametros() != 0 ) ||
			 ( uri->toString().compare( "ftp://sobrarbe.ara" ) != 0 ) )
		{
			cout << "Error caso 2 URI=[" << uri->toString() << "]" << endl;
			bRes = false;
		}
		uri->addParametro( "usuario", "garcia" );
		if ( !uri->EsValido() ||
			 ( uri->getProtocolo().compare( "ftp" ) != 0 ) ||
			 ( uri->getPuerto().size() != 0 ) ||
			 ( uri->getDominio().compare( "sobrarbe.ara" ) != 0 ) ||
			 ( uri->getRuta().size() != 0 ) ||
			 ( uri->NumParametros() != 1 ) ||
			 ( uri->toString().compare( "ftp://sobrarbe.ara?usuario=garcia" ) != 0 ) )
		{
			cout << "Error caso 3 URI=[" << uri->toString() << "]" << endl;
			bRes = false;
		}
		if ( uri->ExisteParametro( "usuario" ) )
		{
			string valor = uri->getValorParametro( "usuario" );
			if ( valor.compare( "garcia" ) != 0 )
			{
				cout << "Error caso 3c URI=[" << uri->toString() << "]" << endl;
				bRes = false;
			}
		}
		else
		{
			cout << "Error caso 3b URI=[" << uri->toString() << "]" << endl;
			bRes = false;
		}
		uri->addParametro( "clave", "philipoussis" );
		if ( !uri->EsValido() ||
			 ( uri->getProtocolo().compare( "ftp" ) != 0 ) ||
			 ( uri->getPuerto().size() != 0 ) ||
			 ( uri->getDominio().compare( "sobrarbe.ara" ) != 0 ) ||
			 ( uri->getRuta().size() != 0 ) ||
			 ( uri->NumParametros() != 2 ) ||
			 ( uri->toString().compare( "ftp://sobrarbe.ara?usuario=garcia&clave=philipoussis" ) != 0 ) )
		{
			cout << "Error caso 4 URI=[" << uri->toString() << "]" << endl;
			bRes = false;
		}
		uri->setRuta( "reyno/fuero" );
		if ( !uri->EsValido() ||
			 ( uri->getProtocolo().compare( "ftp" ) != 0 ) ||
			 ( uri->getPuerto().size() != 0 ) ||
			 ( uri->getDominio().compare( "sobrarbe.ara" ) != 0 ) ||
			 ( uri->getRuta().compare( "reyno/fuero" ) != 0 ) ||
			 ( uri->NumParametros() != 2 ) ||
			 ( uri->toString().compare( "ftp://sobrarbe.ara/reyno/fuero?usuario=garcia&clave=philipoussis" ) != 0 ) )
		{
			cout << "Error caso 5 URI=[" << uri->toString() << "]" << endl;
			bRes = false;
		}
		uri->setPuerto( "erroneo" );
		if ( !uri->EsValido() ||
			 ( uri->getProtocolo().compare( "ftp" ) != 0 ) ||
			 ( uri->getPuerto().compare( "erroneo" ) != 0 ) ||
			 ( uri->getDominio().compare( "sobrarbe.ara" ) != 0 ) ||
			 ( uri->getRuta().compare( "reyno/fuero" ) != 0 ) ||
			 ( uri->NumParametros() != 2 ) ||
			 ( uri->toString().compare( "ftp://sobrarbe.ara/reyno/fuero?usuario=garcia&clave=philipoussis" ) != 0 ) )
		{
			cout << "Error caso 6 URI=[" << uri->toString() << "]" << endl;
			bRes = false;
		}
		uri->setPuerto( "1021" );
		if ( !uri->EsValido() ||
			 ( uri->getProtocolo().compare( "ftp" ) != 0 ) ||
			 ( uri->getPuerto().compare( "1021" ) != 0 ) ||
			 ( uri->getDominio().compare( "sobrarbe.ara" ) != 0 ) ||
			 ( uri->getRuta().compare( "reyno/fuero" ) != 0 ) ||
			 ( uri->NumParametros() != 2 ) ||
			 ( uri->toString().compare( "ftp://sobrarbe.ara:1021/reyno/fuero?usuario=garcia&clave=philipoussis" ) != 0 ) )
		{
			cout << ToString( EsURI( uri->toString() ) ) << endl;
			cout << "Error caso 7 URI=[" << uri->toString() << "]" << endl;
			bRes = false;
		}
		uri->EliminarParametro( "clave" );
		if ( !uri->EsValido() ||
			 ( uri->getProtocolo().compare( "ftp" ) != 0 ) ||
			 ( uri->getPuerto().compare( "1021" ) != 0 ) ||
			 ( uri->getDominio().compare( "sobrarbe.ara" ) != 0 ) ||
			 ( uri->getRuta().compare( "reyno/fuero" ) != 0 ) ||
			 ( uri->NumParametros() != 1 ) ||
			 ( uri->toString().compare( "ftp://sobrarbe.ara:1021/reyno/fuero?usuario=garcia" ) != 0 ) )
		{
			cout << "Error caso 8 URI=[" << uri->toString() << "]" << endl;
			bRes = false;
		}
		uri->LimpiarParametros();
		if ( !uri->EsValido() ||
			 ( uri->getProtocolo().compare( "ftp" ) != 0 ) ||
			 ( uri->getPuerto().compare( "1021" ) != 0 ) ||
			 ( uri->getDominio().compare( "sobrarbe.ara" ) != 0 ) ||
			 ( uri->getRuta().compare( "reyno/fuero" ) != 0 ) ||
			 ( uri->NumParametros() != 0 ) ||
			 ( uri->toString().compare( "ftp://sobrarbe.ara:1021/reyno/fuero" ) != 0 ) )
		{
			cout << "Error caso 9 URI=[" << uri->toString() << "]" << endl;
			bRes = false;
		}
		uri->setURI( "gopher://fermilab.edu" );
		if ( !uri->EsValido() ||
			 ( uri->getProtocolo().compare( "gopher" ) != 0 ) ||
			 ( uri->getPuerto().compare( "" ) != 0 ) ||
			 ( uri->getDominio().compare( "fermilab.edu" ) != 0 ) ||
			 ( uri->getRuta().compare( "" ) != 0 ) ||
			 ( uri->NumParametros() != 0 ) ||
			 ( uri->toString().compare( "gopher://fermilab.edu" ) != 0 ) )
		{
			cout << "Error caso 10 URI=[" << uri->toString() << "]" << endl;
			bRes = false;
		}
		uri->setURI( "vuaitjous.gov" );
		if ( !uri->EsValido() ||
			 ( uri->getProtocolo().compare( "" ) != 0 ) ||
			 ( uri->getPuerto().compare( "" ) != 0 ) ||
			 ( uri->getDominio().compare( "vuaitjous.gov" ) != 0 ) ||
			 ( uri->getRuta().compare( "" ) != 0 ) ||
			 ( uri->NumParametros() != 0 ) ||
			 ( uri->toString().compare( "vuaitjous.gov" ) != 0 ) )
		{
			cout << "Error caso 11 URI=[" << uri->toString() << "]" << endl;
			bRes = false;
		}
		uri = new URI( "protocolo://dominio.com:8080/ruta1/ruta2" );
		if ( !uri->EsValido() ||
			 ( uri->getProtocolo().compare( "protocolo" ) != 0 ) ||
			 ( uri->getPuerto().compare( "8080" ) != 0 ) ||
			 ( uri->getDominio().compare( "dominio.com" ) != 0 ) ||
			 ( uri->getRuta().compare( "ruta1/ruta2" ) != 0 ) ||
			 ( uri->NumParametros() != 0 ) ||
			 ( uri->toString().compare( "protocolo://dominio.com:8080/ruta1/ruta2" ) != 0 ) )
		{
			cout << "Error caso 12 URI=[" << uri->toString() << "]" << endl;
			bRes = false;
		}
		uri->setURI( "ftp://legalegalizacion.pr" );
		if ( !uri->EsValido() ||
			 ( uri->getProtocolo().compare( "ftp" ) != 0 ) ||
			 ( uri->getPuerto().compare( "" ) != 0 ) ||
			 ( uri->getDominio().compare( "legalegalizacion.pr" ) != 0 ) ||
			 ( uri->getRuta().compare( "" ) != 0 ) ||
			 ( uri->NumParametros() != 0 ) ||
			 ( uri->toString().compare( "ftp://legalegalizacion.pr" ) != 0 ) )
		{
			cout << "Error caso 13 URI=[" << uri->toString() << "]" << endl;
			bRes = false;
		}
		uri = new URI( "www.dominio.com" );
		if ( !uri->EsValido() ||
			 ( uri->getProtocolo().compare( "http" ) != 0 ) ||
			 ( uri->getPuerto().compare( "" ) != 0 ) ||
			 ( uri->getDominio().compare( "www.dominio.com" ) != 0 ) ||
			 ( uri->getRuta().compare( "" ) != 0 ) ||
			 ( uri->NumParametros() != 0 ) ||
			 ( uri->toString().compare( "http://www.dominio.com" ) != 0 ) )
		{
			cout << "Error caso 14 URI=[" << uri->toString() << "]" << endl;
			bRes = false;
		}
		delete uri;
	}
	catch ( exception & ex )
	{
		cout << "Se ha producido una excepcion :" << ex.what () << endl;
		bRes = false;
	}
	catch ( ... )
	{
		cout << "Excepcion indefinida" << endl;
		bRes = false;
	}
	return( bRes );
}

static bool TestURI02 ()
{
	cout << "Test URI 02:" << endl;
	bool bRes = true;

	try
	{
		URI uri( "http://localhost:80/aplicacion1?usuario=vladimiro&clave=patin1&operacion=1" );
		if ( !uri.EsValido() ||
			 ( uri.getProtocolo().compare( "http" ) != 0 ) ||
			 ( uri.getPuerto().compare( "80" ) != 0 ) ||
			 ( uri.getDominio().compare( "localhost" ) != 0 ) ||
			 ( uri.getRuta().compare( "aplicacion1" ) != 0 ) ||
			 ( uri.NumParametros() != 3 ) ||
			 ( uri.toString().compare( "http://localhost:80/aplicacion1?usuario=vladimiro&clave=patin1&operacion=1" ) != 0 ) )
		{
			cout << "Error caso 1 URI=[" << uri.toString() << "]" << endl;
			bRes = false;
		}
		if ( bRes )
		{
			if ( !uri.ExisteParametro( "clave" ) || !uri.ExisteParametro( "usuario" ) ||
				 !uri.ExisteParametro( "operacion" ) || uri.ExisteParametro( "noexiste" ) )
			{
				cout << "Error caso 1a URI=[" << uri.toString() << "]" << endl;
				bRes = false;
			}
			if ( ( uri.getValorParametro( "clave" ).compare( "patin1" ) != 0 ) || ( uri.getValorParametro( "usuario" ).compare( "vladimiro" ) != 0 ) ||
				 ( uri.getValorParametro( "operacion" ).compare( "1" ) != 0 ) )
			{
				cout << "Error caso 1b URI=[" << uri.toString() << "]" << endl;
				bRes = false;
			}
		}
		if ( bRes )
		{
			uri.EliminarParametro( "clave" );
			if ( !uri.EsValido() ||
				 ( uri.getProtocolo().compare( "http" ) != 0 ) ||
				 ( uri.getPuerto().compare( "80" ) != 0 ) ||
				 ( uri.getDominio().compare( "localhost" ) != 0 ) ||
				 ( uri.getRuta().compare( "aplicacion1" ) != 0 ) ||
				 ( uri.NumParametros() != 2 ) ||
				 ( uri.toString().compare( "http://localhost:80/aplicacion1?usuario=vladimiro&operacion=1" ) != 0 ) )
			{
				cout << "Error caso 2 URI=[" << uri.toString() << "]" << endl;
				bRes = false;
			}
			if ( bRes )
			{
				if ( uri.ExisteParametro( "clave" ) || !uri.ExisteParametro( "usuario" ) ||
					 !uri.ExisteParametro( "operacion" ) )
				{
					cout << "Error caso 2a URI=[" << uri.toString() << "]" << endl;
					bRes = false;
				}
				if ( ( uri.getValorParametro( "usuario" ).compare( "vladimiro" ) != 0 ) ||
					 ( uri.getValorParametro( "operacion" ).compare( "1" ) != 0 ) )
				{
					cout << "Error caso 2b URI=[" << uri.toString() << "]" << endl;
					bRes = false;
				}
			}
		}
		uri.LimpiarParametros();
		if ( !uri.EsValido() ||
			 ( uri.getProtocolo().compare( "http" ) != 0 ) ||
			 ( uri.getPuerto().compare( "80" ) != 0 ) ||
			 ( uri.getDominio().compare( "localhost" ) != 0 ) ||
			 ( uri.getRuta().compare( "aplicacion1" ) != 0 ) ||
			 ( uri.NumParametros() != 0 ) ||
			 ( uri.toString().compare( "http://localhost:80/aplicacion1" ) != 0 ) )
		{
			cout << "Error caso 3 URI=[" << uri.toString() << "]" << endl;
			bRes = false;
		}
	}
	catch ( exception & ex )
	{
		cout << "Se ha producido una excepcion :" << ex.what () << endl;
		bRes = false;
	}
	catch ( ... )
	{
		cout << "Excepcion indefinida" << endl;
		bRes = false;
	}
	return( bRes );
}

static bool TestURI03 ()
{
	cout << "Test URI 03:" << endl;
	bool bRes = true;

	try
	{
		URI uri( "http://localhost:45301", "site1/index.html" );
		if ( !uri.EsValido() ||
			 ( uri.getProtocolo().compare( "http" ) != 0 ) ||
			 ( uri.getPuerto().compare( "45301" ) != 0 ) ||
			 ( uri.getDominio().compare( "localhost" ) != 0 ) ||
			 ( uri.getRuta().compare( "site1/index.html" ) != 0 ) ||
			 ( uri.NumParametros() != 0 ) ||
			 ( uri.toString().compare( "http://localhost:45301/site1/index.html" ) != 0 ) )
		{
			cout << "Error caso 1 URI=[" << uri.toString() << "]" << endl;

			bRes = false;
		}
		uri.setURI( "http://localhost:45301/", "/site1/index.html" );
		if ( !uri.EsValido() ||
			 ( uri.getProtocolo().compare( "http" ) != 0 ) ||
			 ( uri.getPuerto().compare( "45301" ) != 0 ) ||
			 ( uri.getDominio().compare( "localhost" ) != 0 ) ||
			 ( uri.getRuta().compare( "site1/index.html" ) != 0 ) ||
			 ( uri.NumParametros() != 0 ) ||
			 ( uri.toString().compare( "http://localhost:45301/site1/index.html" ) != 0 ) )
		{
			cout << "Error caso 2 URI=[" << uri.toString() << "]" << endl;
			bRes = false;
		}
	}
	catch ( exception & ex )
	{
		cout << "Se ha producido una excepcion :" << ex.what () << endl;
		bRes = false;
	}
	catch ( ... )
	{
		cout << "Excepcion indefinida" << endl;
		bRes = false;
	}
	return( bRes );
}


/* Los segmentos . y .. no son validos: es lo que impide que ServidorHTTP
   sirva algo fuera de su directorio raiz. %2e%2e si lo es, pero URI no
   decodifica porcentajes, asi que llega al disco como un nombre literal. */
static bool TestURI04 ()
{
	cout << "Test URI 04:" << endl;
	bool bRes = true;

	try
	{
		int iCaso = 0;
		for ( const string & sUrn : { "../secreto.html", "/../secreto.html", "site1/../../secreto.html",
									  "site1/..", "..", "site1/./index.html", "..\\secreto.html" } )
		{
			iCaso = iCaso + 1;
			URI uri( "http://localhost", sUrn );
			if ( uri.EsValido() )
			{
				cout << "Error caso " << iCaso << ": [" << sUrn << "] se ha aceptado" << endl;
				bRes = false;
			}
			if ( uri.getRuta().size() != 0 )
			{
				cout << "Error caso " << iCaso << ": [" << sUrn << "] deja la ruta [" << uri.getRuta() << "]" << endl;
				bRes = false;
			}
		}
		URI uriCodificada( "http://localhost", "%2e%2e/secreto.html" );
		if ( !uriCodificada.EsValido() )
		{
			cout << "Error caso 8: %2e%2e deberia ser valida" << endl;
			bRes = false;
		}
		if ( uriCodificada.getRuta().compare( "%2e%2e/secreto.html" ) != 0 )
		{
			cout << "Error caso 9: ruta [" << uriCodificada.getRuta() << "], se esperaba sin decodificar" << endl;
			bRes = false;
		}
	}
	catch ( exception & ex )
	{
		cout << "Se ha producido una excepcion :" << ex.what () << endl;
		bRes = false;
	}
	catch ( ... )
	{
		cout << "Excepcion indefinida" << endl;
		bRes = false;
	}
	return( bRes );
}


bool TestURI ()
{
	bool bRes = true;
	cout << endl << ANSI::AMARILLO << "[Test URI]" << ANSI::RESETEAR << endl;
	if ( TestURI01() )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout  << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}
	if ( TestURI02() )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout  << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}
	if ( TestURI03() )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout  << ANSI::ROJO << "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}
	if ( TestURI04() )
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
