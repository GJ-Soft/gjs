#include "Base.h"

#include "Epsilon.h"



static int TestEpsilon01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test Epsilon 01:\n" );

	double dEps = Epsilon ();
	/* El epsilon de la maquina es un valor positivo muy pequeno. */
	if ( dEps <= 0.0 )
	{
		printf( "Error caso 1: el epsilon deberia ser positivo: %g\n", dEps );
		iRes = BOOL_VAL_FALSO;
	}
	if ( dEps >= 0.001 )
	{
		printf( "Error caso 2: el epsilon deberia ser muy pequeno: %g\n", dEps );
		iRes = BOOL_VAL_FALSO;
	}
	/* 1 + epsilon deja de ser distinguible de 1 ( propiedad del epsilon ). */
	if ( ( 1.0 + dEps ) != 1.0 )
	{
		printf( "Error caso 3: 1 + epsilon deberia ser mayor que 1 (%lf)\n", 1.0 + dEps );
		iRes = BOOL_VAL_FALSO;
	}
	/* El valor se cachea: dos llamadas devuelven lo mismo. */
	if ( Epsilon () != dEps )
	{
		printf( "Error caso 4: llamadas sucesivas deberian devolver el mismo epsilon\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}



int TestEpsilon ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test Epsilon]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestEpsilon01 () == BOOL_VAL_CIERTO ) )
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
