#set( $symbol_pound = '#' )
#set( $symbol_dollar = '$' )
#set( $symbol_escape = '\' )
#set( $capitalizedName = $shortName.substring(0,1).toUpperCase() + $shortName.substring(1))

${symbol_pound}include <CTest.h>

${symbol_pound}include "${capitalizedName}.h"

${symbol_pound}include <Funciones.h>
${symbol_pound}include <SConjuntoReferencias.h>
${symbol_pound}include <CEntorno.h>

extern int TestSample ();
extern int TestSampleType ();


int main( int argc, char * argv[] )
{
	int iRes = 0;
	EntInicializar ( 1, "Test${capitalizedName}", 1, 0 );

	SConjuntoReferencias * p_cnjTests = SCnjRefCrear ();
	SCnjRefInsertarExt ( p_cnjTests, "Sample", (void *) TestSample );
	SCnjRefInsertarExt ( p_cnjTests, "SampleType", (void *) TestSampleType );


	char * p_cTest = NULL;
	if ( argc > 1 )
	{
		p_cTest = argv[1];
	}
	if ( ( CadLongitud( p_cTest ) > 0 ) && ( CadComparar ( p_cTest, "null" ) != 0 ) )
	{
		SReferencia * p_refObj = SCnjRefBuscar ( p_cnjTests, p_cTest );
		if ( ES_VALIDO ( p_refObj ) )
		{
			PFUNINTV fTest = ( PFUNINTV ) SRefObtenerDatos ( p_refObj );
			if( fTest() == 0 )
			{
				iRes = -1;
			}
		}
		else
		{
			printf ( "ERROR: Test [%s] no encontrado.\n", p_cTest );
			iRes = -1;
		}
		return( iRes );
	}

	if ( ( TestSample () == 0 ) ||
        ( TestSampleType () == 0 ) )
	{
		iRes = -1;
	}
	SCnjRefDestruir ( &p_cnjTests );
	EntFinalizar ();
	return ( iRes );
}
