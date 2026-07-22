#include "Base.h"

#include "SReloj.h"



static int TestSRljCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	SReloj * p_rljObj;
	printf( "Test SRljCrear 01:\n" );

	p_rljObj = SRljCrearDef ();
	if ( ES_NULO ( p_rljObj ) )
	{
		printf( "Error caso 0: no se pudo crear el reloj\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		/* por defecto el reloj esta sincronizado con el sistema (desplazamiento 0) */
		if ( p_rljObj->dDesplazamiento != 0 )
		{
			printf( "Error caso 1: el desplazamiento inicial deberia ser 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* sincronizacion externa: desplazamiento = valor(hora) - valor(horaSis) = 12h - 10h = 2h */
		SRljSincronizarConSistemaExt ( p_rljObj, 100000, 120000 );
		if ( ( p_rljObj->dDesplazamiento < 1.9999 ) || ( p_rljObj->dDesplazamiento > 2.0001 ) )
		{
			printf( "Error caso 2: el desplazamiento deberia ser 2.0: %f\n", p_rljObj->dDesplazamiento );
			iRes = BOOL_VAL_FALSO;
		}
		/* volver a sincronizar con el sistema deja el desplazamiento a 0 */
		SRljSincronizarConSistema ( p_rljObj );
		if ( p_rljObj->dDesplazamiento != 0 )
		{
			printf( "Error caso 3: el desplazamiento deberia volver a 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	SRljDestruir ( (SReloj **) &p_rljObj );
	if ( ES_VALIDO ( p_rljObj ) )
	{
		printf( "Error caso 4: tras destruir el puntero deberia ser nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}

	/* comportamiento defensivo con nulo */
	if ( SRljHora ( NULL ) != -1 )
	{
		printf( "Error caso 5: SRljHora de nulo deberia dar -1\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SRljHH ( NULL ) != -1 )
	{
		printf( "Error caso 6: SRljHH de nulo deberia dar -1\n" );
		iRes = BOOL_VAL_FALSO;
	}

	return ( iRes );
}



int TestSReloj ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SReloj]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSRljCrear01 () == BOOL_VAL_CIERTO ) )
	{
		printf ( "%sResultado: OK%s\n", ANSI_VERDE, ANSI_RESETEAR );
	}
	else
	{
		printf ( "%sResultado: KO%s\n", ANSI_ROJO, ANSI_RESETEAR );
		iRes = BOOL_VAL_FALSO;
	}
	printf ( "%s[Fin]%s\n", ANSI_AMARILLO, ANSI_RESETEAR );
	return ( iRes );
}
