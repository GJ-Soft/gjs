#include "Base.h"
#include "Texto.h"

#include "SEntidadIdCod.h"



static int TestSEntIdCodCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	char cCarga [] = "carga";
	printf( "Test SEntIdCodCrear 01:\n" );

	/* Por defecto: id 0, que todavia no es un identificador asignado. */
	SEntidadIdCod * p_enticObj = SEntIdCodCrearDef ( COD_MAX_TAM_DEF );
	if ( ES_VALIDO ( p_enticObj ) )
	{
		if ( SEntIdCodValorId ( p_enticObj ) != 0 )
		{
			printf( "Error caso 1: se esperaba id 0: %lu\n", SEntIdCodValorId ( p_enticObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntIdCodEsValida ( p_enticObj ) != 0 )
		{
			printf( "Error caso 2: con id 0 no deberia ser valida\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la entidad por defecto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SEntIdCodDestruir ( &p_enticObj );

	/* Con id y codigo. La validez la da el id, que es el identificador. */
	p_enticObj = SEntIdCodCrearLit ( 42, "COD001", COD_MAX_TAM_DEF );
	if ( ES_VALIDO ( p_enticObj ) )
	{
		if ( SEntIdCodValorId ( p_enticObj ) != 42 )
		{
			printf( "Error caso 3: se esperaba id 42: %lu\n", SEntIdCodValorId ( p_enticObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( CadComparar ( SEntIdCodValorCodigoLit ( p_enticObj ), "COD001" ) != COMP_IGUAL )
		{
			printf( "Error caso 4: se esperaba codigo \"COD001\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntIdCodEsValida ( p_enticObj ) != 1 )
		{
			printf( "Error caso 5: con id asignado deberia ser valida\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_NULO ( SEntIdCodBase ( p_enticObj ) ) )
		{
			printf( "Error caso 6: se esperaba la entidad base\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la entidad con codigo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SEntIdCodDestruir ( &p_enticObj );

	/* Destruir devuelve el contenido y anula el puntero. */
	p_enticObj = SEntIdCodCrearLitExt ( 7, "COD002", COD_MAX_TAM_DEF, cCarga );
	if ( ES_NULO ( p_enticObj ) )
	{
		printf( "Error caso 0: no se pudo crear la entidad con contenido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SEntIdCodDestruir ( &p_enticObj ) != (void *) cCarga )
	{
		printf( "Error caso 7: destruir deberia devolver el contenido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( p_enticObj ) )
	{
		printf( "Error caso 8: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSEntIdCodCodigoObligatorio01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SEntIdCodCodigoObligatorio 01:\n" );

	/* A diferencia de SEntidadNom y SEntidadCodNom, aqui el codigo es el
	   segundo identificador y es obligatorio: un codigo que no supera la
	   validacion de SCodigo no da una entidad sin codigo, no da entidad. */
	SEntidadIdCod * p_enticObj = SEntIdCodCrearLit ( 5, "COD-001", COD_MAX_TAM_DEF );
	if ( ES_VALIDO ( p_enticObj ) )
	{
		printf( "Error caso 1: con un codigo invalido no deberia crearse la entidad\n" );
		iRes = BOOL_VAL_FALSO;
		SEntIdCodDestruir ( &p_enticObj );
	}

	/* Sin identificador tampoco, aunque el codigo sea correcto. Y al fallar,
	   Encapsular no se queda con el codigo: sigue siendo del llamante, que es
	   quien lo destruye. */
	SCodigo * p_codSuelto = SCodCrearValorLitExt ( "COD001", COD_MAX_TAM_DEF );
	p_enticObj = SEntIdCodEncapsular ( NULL, p_codSuelto );
	if ( ES_VALIDO ( p_enticObj ) )
	{
		printf( "Error caso 2: encapsular sin id deberia dar nulo\n" );
		iRes = BOOL_VAL_FALSO;
		SEntIdCodDestruir ( &p_enticObj );
	}
	SCodDestruir ( &p_codSuelto );

	/* Y al reves: con id valido pero sin codigo, tampoco. */
	SId * p_idSuelto = SIdCrear ( 5 );
	p_enticObj = SEntIdCodEncapsular ( p_idSuelto, NULL );
	if ( ES_VALIDO ( p_enticObj ) )
	{
		printf( "Error caso 3: encapsular sin codigo deberia dar nulo\n" );
		iRes = BOOL_VAL_FALSO;
		SEntIdCodDestruir ( &p_enticObj );
	}
	SIdDestruir ( &p_idSuelto );
	return ( iRes );
}

static int TestSEntIdCodEstablecer01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SEntIdCodEstablecer 01:\n" );

	SEntidadIdCod * p_enticObj = SEntIdCodCrearLit ( 1, "COD001", COD_MAX_TAM_DEF );
	if ( ES_VALIDO ( p_enticObj ) )
	{
		if ( SEntIdCodEstablecerValorId ( p_enticObj, 99 ) != 1 )
		{
			printf( "Error caso 1: se esperaba 1 al establecer el valor del id\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntIdCodValorId ( p_enticObj ) != 99 )
		{
			printf( "Error caso 2: se esperaba id 99: %lu\n", SEntIdCodValorId ( p_enticObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntIdCodEstablecerValorCodigoLit ( p_enticObj, "COD999" ) != 1 )
		{
			printf( "Error caso 3: se esperaba 1 al establecer el codigo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( CadComparar ( SEntIdCodValorCodigoLit ( p_enticObj ), "COD999" ) != COMP_IGUAL )
		{
			printf( "Error caso 4: se esperaba codigo \"COD999\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* El cambio de id se ve tambien desde la base, que es el mismo objeto. */
		if ( SEntValorId ( SEntIdCodBase ( p_enticObj ) ) != 99 )
		{
			printf( "Error caso 5: la base deberia ver el id nuevo\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la entidad\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SEntIdCodDestruir ( &p_enticObj );
	return ( iRes );
}

static int TestSEntIdCodIdentidad01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SEntIdCodIdentidad 01:\n" );

	/* Mismo id y distinto codigo: la identidad es el id, y nada mas. */
	SEntidadIdCod * p_enticA = SEntIdCodCrearLit ( 10, "CODA", COD_MAX_TAM_DEF );
	SEntidadIdCod * p_enticB = SEntIdCodCrearLit ( 10, "CODB", COD_MAX_TAM_DEF );
	if ( ES_VALIDO ( p_enticA ) && ES_VALIDO ( p_enticB ) )
	{
		if ( SEntIdCodEsIgual ( p_enticA, p_enticB ) != 1 )
		{
			printf( "Error caso 1: mismo id deberia ser igual pese al codigo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Contrato hash-igualdad: el codigo es mutable, asi que no puede entrar
		   en el reparto. */
		if ( SEntIdCodHash ( p_enticA ) != SEntIdCodHash ( p_enticB ) )
		{
			printf( "Error caso 2: entidades iguales deberian tener el mismo hash\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Y reparte igual que su base, para poder convivir en la misma tabla. */
		if ( SEntIdCodHash ( p_enticA ) != SEntHash ( SEntIdCodBase ( p_enticA ) ) )
		{
			printf( "Error caso 3: deberia repartir igual que su entidad base\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Cambiar el codigo no cambia ni la identidad ni el hash. */
		SEntIdCodEstablecerValorCodigoLit ( p_enticA, "CODC" );
		if ( SEntIdCodHash ( p_enticA ) != SEntIdCodHash ( p_enticB ) )
		{
			printf( "Error caso 4: cambiar el codigo no deberia cambiar el hash\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Ids distintos: ya no son iguales. */
		SEntIdCodEstablecerValorId ( p_enticB, 20 );
		if ( SEntIdCodEsIgual ( p_enticA, p_enticB ) != 0 )
		{
			printf( "Error caso 5: ids distintos no deberian ser iguales\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntIdCodEsMenor ( p_enticA, p_enticB ) != 1 )
		{
			printf( "Error caso 6: 10 deberia ser menor que 20\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntIdCodEsIgualNum ( p_enticA, 10 ) != 1 )
		{
			printf( "Error caso 7: deberia ser igual a 10\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear las entidades\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SEntIdCodDestruir ( &p_enticA );
	SEntIdCodDestruir ( &p_enticB );
	return ( iRes );
}

static int TestSEntIdCodComparar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SEntIdCodComparar 01:\n" );

	SEntidadIdCod * p_enticA = SEntIdCodCrearLit ( 10, "CODA", COD_MAX_TAM_DEF );
	SEntidadIdCod * p_enticB = SEntIdCodCrearLit ( 20, "CODB", COD_MAX_TAM_DEF );
	if ( ES_VALIDO ( p_enticA ) && ES_VALIDO ( p_enticB ) )
	{
		if ( SEntIdCodComparar ( p_enticA, p_enticB ) != COMP_MENOR )
		{
			printf( "Error caso 1: 10 frente a 20 deberia dar COMP_MENOR: %d\n", SEntIdCodComparar ( p_enticA, p_enticB ) );
			iRes = BOOL_VAL_FALSO;
		}
		/* Con el mismo id, Comparar desempata por codigo. Es deliberado y
		   provisional: sirve para ordenar listas cuyos ids aun no estan
		   asignados o estan repetidos. No es el criterio de identidad, que es
		   solo el id: por eso EsIgual sigue diciendo que son iguales. */
		SEntIdCodEstablecerValorId ( p_enticB, 10 );
		if ( SEntIdCodComparar ( p_enticA, p_enticB ) != COMP_MENOR )
		{
			printf( "Error caso 2: con el mismo id deberia desempatar por codigo: %d\n", SEntIdCodComparar ( p_enticA, p_enticB ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntIdCodEsIgual ( p_enticA, p_enticB ) != 1 )
		{
			printf( "Error caso 3: el desempate no deberia afectar a EsIgual\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Mismo id y mismo codigo: iguales tambien para Comparar. */
		SEntIdCodEstablecerValorCodigoLit ( p_enticB, "CODA" );
		if ( SEntIdCodComparar ( p_enticA, p_enticB ) != COMP_IGUAL )
		{
			printf( "Error caso 4: mismo id y codigo deberia dar COMP_IGUAL: %d\n", SEntIdCodComparar ( p_enticA, p_enticB ) );
			iRes = BOOL_VAL_FALSO;
		}
		/* Orden con nulos. */
		if ( SEntIdCodComparar ( p_enticA, NULL ) != COMP_MAYOR )
		{
			printf( "Error caso 5: frente a una entidad nula deberia dar COMP_MAYOR\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntIdCodComparar ( NULL, p_enticA ) != COMP_MENOR )
		{
			printf( "Error caso 6: una entidad nula deberia dar COMP_MENOR\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntIdCodComparar ( NULL, NULL ) != COMP_IGUAL )
		{
			printf( "Error caso 7: dos entidades nulas deberian dar COMP_IGUAL\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear las entidades\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SEntIdCodDestruir ( &p_enticA );
	SEntIdCodDestruir ( &p_enticB );
	return ( iRes );
}



int TestSEntidadIdCod ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SEntidadIdCod]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSEntIdCodCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSEntIdCodCodigoObligatorio01 () == BOOL_VAL_CIERTO ) &&
			( TestSEntIdCodEstablecer01 () == BOOL_VAL_CIERTO ) &&
			( TestSEntIdCodIdentidad01 () == BOOL_VAL_CIERTO ) &&
			( TestSEntIdCodComparar01 () == BOOL_VAL_CIERTO ) )
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
