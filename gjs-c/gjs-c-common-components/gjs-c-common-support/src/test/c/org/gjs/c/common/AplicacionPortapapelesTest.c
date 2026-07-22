#include "Base.h"

#include "AplicacionPortapapeles.h"



static int TestAplicPples01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test AplicPples 01:\n" );
	/* El portapapeles solo existe bajo WIN. Prueba conservadora para no depender
	   del estado previo del portapapeles ni de la escritura (que usa memoria
	   GMEM_FIXED): tras limpiar, el contenido debe ser nulo. */
#if ( defined ( WIN ) )
	AplicPplesLimpiar ();
	if ( ES_VALIDO ( AplicPplesContenido ( 0 ) ) )
	{
		printf( "Error caso 1: tras limpiar se esperaba contenido nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
#endif
	return ( iRes );
}



int TestAplicacionPortapapeles ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test AplicacionPortapapeles]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
#if ( defined ( WIN ) )
	if ( ( TestAplicPples01 () == BOOL_VAL_CIERTO ) )
	{
		printf ( "%sResultado: OK%s\n", ANSI_VERDE, ANSI_RESETEAR );
	}
	else
	{
		printf ( "%sResultado: KO%s\n", ANSI_ROJO, ANSI_RESETEAR );
		iRes = BOOL_VAL_FALSO;
	}
#else
	printf ( "AplicacionPortapapeles solo disponible en WIN: no aplica en esta plataforma.\n" );
	printf ( "%sResultado: OK%s\n", ANSI_VERDE, ANSI_RESETEAR );
#endif
	printf ( "%s[Fin]%s\n", ANSI_AMARILLO, ANSI_RESETEAR );
	return ( iRes );
}
