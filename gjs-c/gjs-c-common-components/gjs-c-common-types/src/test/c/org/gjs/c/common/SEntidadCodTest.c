#include "Base.h"
#include "Texto.h"

#include "SEntidadCod.h"




static int TestSEntCodCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	char cCarga [] = "carga";
	printf( "Test SEntCodCrear 01:\n" );

	/* Por defecto el codigo esta vacio, y un codigo vacio no es valido. */
	SEntidadCod * p_entcObj = SEntCodCrearDef ( COD_MAX_TAM_DEF );
	if ( ES_VALIDO ( p_entcObj ) )
	{
		if ( SEntCodEsValida ( p_entcObj ) != 0 )
		{
			printf( "Error caso 1: con el codigo vacio no deberia ser valida\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la entidad por defecto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SEntCodDestruir ( &p_entcObj );

	/* Con codigo y sin contenido: el contenido es opcional. */
	p_entcObj = SEntCodCrearLit ( "COD001", COD_MAX_TAM_DEF );
	if ( ES_VALIDO ( p_entcObj ) )
	{
		if ( CadComparar ( SEntCodValorCodigoLit ( p_entcObj ), "COD001" ) != COMP_IGUAL )
		{
			printf( "Error caso 2: se esperaba codigo \"COD001\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntCodEsValida ( p_entcObj ) != 1 )
		{
			printf( "Error caso 3: con codigo y sin contenido deberia ser valida\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( SEntCodContenido ( p_entcObj ) ) )
		{
			printf( "Error caso 4: se esperaba contenido nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la entidad con codigo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SEntCodDestruir ( &p_entcObj );

	/* Destruir devuelve el contenido y anula el puntero. */
	p_entcObj = SEntCodCrearLitExt ( "COD002", COD_MAX_TAM_DEF, cCarga );
	if ( ES_NULO ( p_entcObj ) )
	{
		printf( "Error caso 0: no se pudo crear la entidad con contenido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SEntCodDestruir ( &p_entcObj ) != (void *) cCarga )
	{
		printf( "Error caso 5: destruir deberia devolver el contenido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( p_entcObj ) )
	{
		printf( "Error caso 6: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}

	/* Sin identificador no hay entidad. */
	p_entcObj = SEntCodEncapsular ( NULL );
	if ( ES_VALIDO ( p_entcObj ) )
	{
		printf( "Error caso 7: encapsular sin codigo deberia dar nulo\n" );
		iRes = BOOL_VAL_FALSO;
		SEntCodDestruir ( &p_entcObj );
	}
	return ( iRes );
}

static int TestSEntCodEstablecer01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	char cUno [] = "uno";
	printf( "Test SEntCodEstablecer 01:\n" );

	SEntidadCod * p_entcObj = SEntCodCrearLit ( "COD001", COD_MAX_TAM_DEF );
	if ( ES_VALIDO ( p_entcObj ) )
	{
		/* El retorno dice si se guardo, no si la entidad quedo completa. */
		if ( SEntCodEstablecerValorCodigoLit ( p_entcObj, "COD999" ) != 1 )
		{
			printf( "Error caso 1: se esperaba 1 al establecer el codigo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( CadComparar ( SEntCodValorCodigoLit ( p_entcObj ), "COD999" ) != COMP_IGUAL )
		{
			printf( "Error caso 2: se esperaba codigo \"COD999\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Establecer el contenido devuelve el anterior. */
		if ( ES_VALIDO ( SEntCodEstablecerContenido ( p_entcObj, cUno ) ) )
		{
			printf( "Error caso 3: el contenido anterior deberia ser nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntCodContenido ( p_entcObj ) != (void *) cUno )
		{
			printf( "Error caso 4: se esperaba el contenido nuevo\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la entidad\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SEntCodDestruir ( &p_entcObj );

	/* Sobre una entidad nula debe fallar. */
	if ( SEntCodEstablecerValorCodigoLit ( NULL, "COD001" ) != 0 )
	{
		printf( "Error caso 5: establecer sobre una entidad nula deberia fallar\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSEntCodComparaciones01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SEntCodComparaciones 01:\n" );

	SEntidadCod * p_entcA = SEntCodCrearLit ( "CODA", COD_MAX_TAM_DEF );
	SEntidadCod * p_entcB = SEntCodCrearLit ( "CODB", COD_MAX_TAM_DEF );
	if ( ES_VALIDO ( p_entcA ) && ES_VALIDO ( p_entcB ) )
	{
		if ( SEntCodEsMenor ( p_entcA, p_entcB ) != 1 )
		{
			printf( "Error caso 1: CODA deberia ser menor que CODB\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntCodEsMayor ( p_entcB, p_entcA ) != 1 )
		{
			printf( "Error caso 2: CODB deberia ser mayor que CODA\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntCodEsIgual ( p_entcA, p_entcB ) != 0 )
		{
			printf( "Error caso 3: CODA y CODB no deberian ser iguales\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntCodEsIgualLit ( p_entcA, "CODA" ) != 1 )
		{
			printf( "Error caso 4: deberia ser igual al literal CODA\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntCodComparar ( p_entcA, p_entcB ) != COMP_MENOR )
		{
			printf( "Error caso 5: CODA frente a CODB deberia dar COMP_MENOR: %d\n", SEntCodComparar ( p_entcA, p_entcB ) );
			iRes = BOOL_VAL_FALSO;
		}
		SEntCodEstablecerValorCodigoLit ( p_entcB, "CODA" );
		if ( SEntCodComparar ( p_entcA, p_entcB ) != COMP_IGUAL )
		{
			printf( "Error caso 6: dos codigos iguales deberian dar COMP_IGUAL: %d\n", SEntCodComparar ( p_entcA, p_entcB ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntCodEsIgual ( p_entcA, p_entcB ) != 1 )
		{
			printf( "Error caso 7: deberian ser iguales tras igualar el codigo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Orden con nulos. */
		if ( SEntCodComparar ( p_entcA, NULL ) != COMP_MAYOR )
		{
			printf( "Error caso 8: frente a una entidad nula deberia dar COMP_MAYOR\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntCodComparar ( NULL, p_entcA ) != COMP_MENOR )
		{
			printf( "Error caso 9: una entidad nula deberia dar COMP_MENOR\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntCodComparar ( NULL, NULL ) != COMP_IGUAL )
		{
			printf( "Error caso 10: dos entidades nulas deberian dar COMP_IGUAL\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear las entidades\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SEntCodDestruir ( &p_entcA );
	SEntCodDestruir ( &p_entcB );
	return ( iRes );
}

static int TestSEntCodHash01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	char cUno [] = "uno";
	char cDos [] = "dos";
	printf( "Test SEntCodHash 01:\n" );

	SEntidadCod * p_entcA = SEntCodCrearLitExt ( "COD001", COD_MAX_TAM_DEF, cUno );
	SEntidadCod * p_entcB = SEntCodCrearLitExt ( "COD001", COD_MAX_TAM_DEF, cDos );
	if ( ES_VALIDO ( p_entcA ) && ES_VALIDO ( p_entcB ) )
	{
		/* Contrato hash-igualdad: el contenido no entra en la identidad, asi
		   que tampoco entra en el hash. */
		if ( SEntCodEsIgual ( p_entcA, p_entcB ) != 1 )
		{
			printf( "Error caso 1: mismo codigo deberia ser igual\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntCodHash ( p_entcA ) != SEntCodHash ( p_entcB ) )
		{
			printf( "Error caso 2: entidades iguales deberian tener el mismo hash\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SEntCodEstablecerValorCodigoLit ( p_entcB, "COD999" );
		if ( SEntCodHash ( p_entcA ) == SEntCodHash ( p_entcB ) )
		{
			printf( "Error caso 3: codigos distintos deberian dar hash distinto\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear las entidades\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SEntCodDestruir ( &p_entcA );
	SEntCodDestruir ( &p_entcB );
	return ( iRes );
}



int TestSEntidadCod ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SEntidadCod]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSEntCodCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSEntCodEstablecer01 () == BOOL_VAL_CIERTO ) &&
			( TestSEntCodComparaciones01 () == BOOL_VAL_CIERTO ) &&
			( TestSEntCodHash01 () == BOOL_VAL_CIERTO ) )
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
