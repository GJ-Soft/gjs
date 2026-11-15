#include "SBancoTests.h"
#include "ContextoTests.h"
#include "CTestConfig.h"






SBancoTests * SBanTstCrear ()
{
	SBancoTests * p_bantstObj;

	p_bantstObj = ( SBancoTests * ) MemReservar ( sizeof ( SBancoTests ) );
	if ( ES_VALIDO ( p_bantstObj ) )
	{
		p_bantstObj->p_cnjTests = SCnjRefCrear ();
		if ( ES_NULO ( p_bantstObj->p_cnjTests ) )
		{
			MemLiberar ( (void **) &p_bantstObj );
		}
	}
	return ( p_bantstObj );
}


void SBanTstDestruir ( SBancoTests ** p_p_bantstObj )
{
	SBancoTests * p_bantstObj;

	if ( ES_VALIDO ( p_p_bantstObj ) )
	{
		p_bantstObj = *p_p_bantstObj;
		if ( ES_VALIDO ( p_bantstObj ) )
		{
			SCnjRefDestruir ( &( p_bantstObj->p_cnjTests ) );
			MemLiberar ( (void **) p_p_bantstObj );
		}
	}
}

void SBanTstNuevoTest ( SBancoTests * p_bantstObj, const char * p_cNombre, PFUNINTV p_fTest )
{
	if ( ES_VALIDO ( p_bantstObj ) )
	{
		SCnjRefInsertarExt ( p_bantstObj->p_cnjTests, p_cNombre, (void *) p_fTest );
	}
}

int SBanTstNumTests ( SBancoTests * p_bantstObj )
{
	int iRes;

	if ( ES_VALIDO ( p_bantstObj ) )
	{
		iRes = SCnjRefNumElementos ( p_bantstObj->p_cnjTests );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SBanTstEjecutar ( SBancoTests * p_bantstObj )
{
	int iRes;
	int iTest;
	int iNumTests;

	if ( ES_VALIDO ( p_bantstObj ) )
	{
		printf ( "%s[Inicio de los test]%s\n", ANSI_AZUL, ANSI_RESETEAR );
		printf ( "%sInicializando Entorno de Test%s\n", ANSI_MAGENTA, ANSI_RESETEAR );
		InicializarEntorno ();
		iRes = 1;
		iTest = 0;
		iNumTests = SCnjRefNumElementos ( p_bantstObj->p_cnjTests );
		while ( iTest < iNumTests )
		{
			PFUNINTV fTest = (PFUNINTV) SCnjRefDatosElemento ( p_bantstObj->p_cnjTests, iTest );
			if ( ES_VALIDO ( fTest ) )
			{
				if ( fTest () == 1 )
				{
					printf ( "%sResultado: OK%s\n", ANSI_VERDE, ANSI_RESETEAR );
				}
				else
				{
					printf ( "%sResultado: KO%s\n", ANSI_ROJO, ANSI_RESETEAR );
					iRes = 0;
				}
			}
			else
			{
				printf ( "%sEl test esta mal definido: KO%s\n", ANSI_ROJO, ANSI_RESETEAR );
				iRes = 0;
			}
			iTest = iTest + 1;
		}
		FinalizarEntorno ();
		printf ( "%s[Fin de los test]%s\n", ANSI_AZUL, ANSI_RESETEAR );
	}
	else
	{
		iRes = 0;
	}
	return( iRes );
}

int SBanTstEjecutarTest ( SBancoTests * p_bantstObj, const char * p_cTest )
{
	int iRes;

	if ( ES_VALIDO ( p_bantstObj ) )
	{
		if ( CadLongitud ( p_cTest ) > 0 )
		{
			SReferencia * p_refObj = SCnjRefBuscar ( p_bantstObj->p_cnjTests, p_cTest );
			if ( ES_VALIDO ( p_refObj ) )
			{
				PFUNINTV fTest = ( PFUNINTV ) SRefObtenerDatos ( p_refObj );
				if ( fTest () == 1 )
				{
					iRes = 1;
				}
				else
				{
					iRes = 0;
				}
			}
			else
			{
				printf ( "%sTest [%s] no encontrado.%s\n", ANSI_ROJO, p_cTest, ANSI_RESETEAR );
				iRes = 0;
			}
		}
		else
		{
			iRes = SBanTstEjecutar ( p_bantstObj );
		}
	}
	else
	{
		iRes = 0;
	}
	return( iRes );
}


int SBanTstEjecutarTextExe ( SBancoTests * p_bantstObj, int argc, char * argv[] )
{
	int iRes;

	if ( ES_VALIDO ( p_bantstObj ) )
	{
		if ( argc > 1 )
		{
			char * p_cTest = argv[1];
			iRes = SBanTstEjecutarTest ( p_bantstObj, p_cTest );
		} 
		else
		{
			iRes = SBanTstEjecutar ( p_bantstObj );
		}
	}
	else
	{
		iRes = 0;
	}
	return( iRes );
}

