#include "Base.h"
#include "Texto.h"

#include "SEntidadCodNom.h"



static int TestSEntCodNomCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	char cCarga [] = "carga";
	printf( "Test SEntCodNomCrear 01:\n" );

	/* Por defecto el codigo esta vacio, y un codigo vacio no es valido. */
	SEntidadCodNom * p_entcnObj = SEntCodNomCrearDef ( COD_MAX_TAM_DEF );
	if ( ES_VALIDO ( p_entcnObj ) )
	{
		if ( SEntCodNomEsValida ( p_entcnObj ) != 0 )
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
	SEntCodNomDestruir ( &p_entcnObj );

	/* Con codigo y nombre. La validez la da el codigo, que es el identificador. */
	p_entcnObj = SEntCodNomCrearLit ( "COD001", COD_MAX_TAM_DEF, "cliente_a" );
	if ( ES_VALIDO ( p_entcnObj ) )
	{
		if ( CadComparar ( SEntCodNomValorCodigoLit ( p_entcnObj ), "COD001" ) != COMP_IGUAL )
		{
			printf( "Error caso 2: se esperaba codigo \"COD001\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( CadComparar ( SEntCodNomValorNombreLit ( p_entcnObj ), "cliente_a" ) != COMP_IGUAL )
		{
			printf( "Error caso 3: se esperaba nombre \"cliente_a\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntCodNomEsValida ( p_entcnObj ) != 1 )
		{
			printf( "Error caso 4: con codigo asignado deberia ser valida\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_NULO ( SEntCodNomBase ( p_entcnObj ) ) )
		{
			printf( "Error caso 5: se esperaba la entidad base\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la entidad con codigo y nombre\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SEntCodNomDestruir ( &p_entcnObj );

	/* Destruir devuelve el contenido y anula el puntero. */
	p_entcnObj = SEntCodNomCrearLitExt ( "COD002", COD_MAX_TAM_DEF, "cliente_b", cCarga );
	if ( ES_NULO ( p_entcnObj ) )
	{
		printf( "Error caso 0: no se pudo crear la entidad con contenido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SEntCodNomDestruir ( &p_entcnObj ) != (void *) cCarga )
	{
		printf( "Error caso 6: destruir deberia devolver el contenido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( p_entcnObj ) )
	{
		printf( "Error caso 7: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSEntCodNomNombreOpcional01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SEntCodNomNombreOpcional 01:\n" );

	/* Un nombre con blancos no supera la validacion de SNombre. La entidad se
	   crea igualmente: solo se exige el codigo, y en lugar del nombre invalido
	   se pone uno vacio. */
	SEntidadCodNom * p_entcnObj = SEntCodNomCrearLit ( "COD001", COD_MAX_TAM_DEF, "con blanco" );
	if ( ES_VALIDO ( p_entcnObj ) )
	{
		if ( ES_NULO ( SEntCodNomNombre ( p_entcnObj ) ) )
		{
			printf( "Error caso 1: se esperaba un SNombre vacio, no nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( CadLongitud ( SEntCodNomValorNombreLit ( p_entcnObj ) ) != 0 )
		{
			printf( "Error caso 2: se esperaba el nombre vacio\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntCodNomEsValida ( p_entcnObj ) != 1 )
		{
			printf( "Error caso 3: deberia ser valida aunque el nombre este vacio\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Y como el SNombre existe, se le puede poner uno despues. */
		if ( SEntCodNomEstablecerValorNombreLit ( p_entcnObj, "cliente_a" ) != 1 )
		{
			printf( "Error caso 4: se esperaba poder establecer el nombre despues\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la entidad\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SEntCodNomDestruir ( &p_entcnObj );

	/* Sin identificador no hay entidad, aunque el nombre sea correcto. Y al
	   fallar, Encapsular no se queda con el nombre: sigue siendo del llamante,
	   que es quien lo destruye. */
	SNombre * p_nomSuelto = SNomCrearValorLit ( "cliente_a" );
	p_entcnObj = SEntCodNomEncapsular ( NULL, p_nomSuelto );
	if ( ES_VALIDO ( p_entcnObj ) )
	{
		printf( "Error caso 5: encapsular sin codigo deberia dar nulo\n" );
		iRes = BOOL_VAL_FALSO;
		SEntCodNomDestruir ( &p_entcnObj );
	}
	SNomDestruir ( &p_nomSuelto );
	return ( iRes );
}

static int TestSEntCodNomEstablecer01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SEntCodNomEstablecer 01:\n" );

	SEntidadCodNom * p_entcnObj = SEntCodNomCrearLit ( "COD001", COD_MAX_TAM_DEF, "cliente_a" );
	if ( ES_VALIDO ( p_entcnObj ) )
	{
		if ( SEntCodNomEstablecerValorCodigoLit ( p_entcnObj, "COD999" ) != 1 )
		{
			printf( "Error caso 1: se esperaba 1 al establecer el codigo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( CadComparar ( SEntCodNomValorCodigoLit ( p_entcnObj ), "COD999" ) != COMP_IGUAL )
		{
			printf( "Error caso 2: se esperaba codigo \"COD999\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntCodNomEstablecerValorNombreLit ( p_entcnObj, "cliente_b" ) != 1 )
		{
			printf( "Error caso 3: se esperaba 1 al establecer el nombre\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( CadComparar ( SEntCodNomValorNombreLit ( p_entcnObj ), "cliente_b" ) != COMP_IGUAL )
		{
			printf( "Error caso 4: se esperaba nombre \"cliente_b\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* El cambio de codigo se ve tambien desde la base, que es el mismo objeto. */
		if ( CadComparar ( SEntCodValorCodigoLit ( SEntCodNomBase ( p_entcnObj ) ), "COD999" ) != COMP_IGUAL )
		{
			printf( "Error caso 5: la base deberia ver el codigo nuevo\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la entidad\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SEntCodNomDestruir ( &p_entcnObj );
	return ( iRes );
}

static int TestSEntCodNomIdentidad01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SEntCodNomIdentidad 01:\n" );

	/* Mismo codigo y distinto nombre: la identidad es el codigo, y nada mas. */
	SEntidadCodNom * p_entcnA = SEntCodNomCrearLit ( "CODA", COD_MAX_TAM_DEF, "cliente_a" );
	SEntidadCodNom * p_entcnB = SEntCodNomCrearLit ( "CODA", COD_MAX_TAM_DEF, "cliente_b" );
	if ( ES_VALIDO ( p_entcnA ) && ES_VALIDO ( p_entcnB ) )
	{
		if ( SEntCodNomEsIgual ( p_entcnA, p_entcnB ) != 1 )
		{
			printf( "Error caso 1: mismo codigo deberia ser igual pese al nombre\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Contrato hash-igualdad: el nombre es mutable, asi que no puede entrar
		   en el reparto. */
		if ( SEntCodNomHash ( p_entcnA ) != SEntCodNomHash ( p_entcnB ) )
		{
			printf( "Error caso 2: entidades iguales deberian tener el mismo hash\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Y reparte igual que su base, para poder convivir en la misma tabla. */
		if ( SEntCodNomHash ( p_entcnA ) != SEntCodHash ( SEntCodNomBase ( p_entcnA ) ) )
		{
			printf( "Error caso 3: deberia repartir igual que su entidad base\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Cambiar el nombre no cambia ni la identidad ni el hash. */
		SEntCodNomEstablecerValorNombreLit ( p_entcnA, "cliente_c" );
		if ( SEntCodNomHash ( p_entcnA ) != SEntCodNomHash ( p_entcnB ) )
		{
			printf( "Error caso 4: cambiar el nombre no deberia cambiar el hash\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Codigos distintos: ya no son iguales. */
		SEntCodNomEstablecerValorCodigoLit ( p_entcnB, "CODB" );
		if ( SEntCodNomEsIgual ( p_entcnA, p_entcnB ) != 0 )
		{
			printf( "Error caso 5: codigos distintos no deberian ser iguales\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntCodNomEsMenor ( p_entcnA, p_entcnB ) != 1 )
		{
			printf( "Error caso 6: CODA deberia ser menor que CODB\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntCodNomEsIgualLit ( p_entcnA, "CODA" ) != 1 )
		{
			printf( "Error caso 7: deberia ser igual al literal CODA\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear las entidades\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SEntCodNomDestruir ( &p_entcnA );
	SEntCodNomDestruir ( &p_entcnB );
	return ( iRes );
}

static int TestSEntCodNomComparar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SEntCodNomComparar 01:\n" );

	SEntidadCodNom * p_entcnA = SEntCodNomCrearLit ( "CODA", COD_MAX_TAM_DEF, "cliente_a" );
	SEntidadCodNom * p_entcnB = SEntCodNomCrearLit ( "CODB", COD_MAX_TAM_DEF, "cliente_b" );
	if ( ES_VALIDO ( p_entcnA ) && ES_VALIDO ( p_entcnB ) )
	{
		if ( SEntCodNomComparar ( p_entcnA, p_entcnB ) != COMP_MENOR )
		{
			printf( "Error caso 1: CODA frente a CODB deberia dar COMP_MENOR: %d\n", SEntCodNomComparar ( p_entcnA, p_entcnB ) );
			iRes = BOOL_VAL_FALSO;
		}
		/* Con el mismo codigo, Comparar desempata por nombre. Es deliberado y
		   provisional: sirve para ordenar listas cuyos codigos aun no estan
		   asignados o estan repetidos. No es el criterio de identidad, que es
		   solo el codigo: por eso EsIgual sigue diciendo que son iguales. */
		SEntCodNomEstablecerValorCodigoLit ( p_entcnB, "CODA" );
		if ( SEntCodNomComparar ( p_entcnA, p_entcnB ) != COMP_MENOR )
		{
			printf( "Error caso 2: con el mismo codigo deberia desempatar por nombre: %d\n", SEntCodNomComparar ( p_entcnA, p_entcnB ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntCodNomEsIgual ( p_entcnA, p_entcnB ) != 1 )
		{
			printf( "Error caso 3: el desempate no deberia afectar a EsIgual\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Mismo codigo y mismo nombre: iguales tambien para Comparar. */
		SEntCodNomEstablecerValorNombreLit ( p_entcnB, "cliente_a" );
		if ( SEntCodNomComparar ( p_entcnA, p_entcnB ) != COMP_IGUAL )
		{
			printf( "Error caso 4: mismo codigo y nombre deberia dar COMP_IGUAL: %d\n", SEntCodNomComparar ( p_entcnA, p_entcnB ) );
			iRes = BOOL_VAL_FALSO;
		}
		/* Orden con nulos. */
		if ( SEntCodNomComparar ( p_entcnA, NULL ) != COMP_MAYOR )
		{
			printf( "Error caso 5: frente a una entidad nula deberia dar COMP_MAYOR\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntCodNomComparar ( NULL, p_entcnA ) != COMP_MENOR )
		{
			printf( "Error caso 6: una entidad nula deberia dar COMP_MENOR\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntCodNomComparar ( NULL, NULL ) != COMP_IGUAL )
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
	SEntCodNomDestruir ( &p_entcnA );
	SEntCodNomDestruir ( &p_entcnB );
	return ( iRes );
}



int TestSEntidadCodNom ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SEntidadCodNom]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSEntCodNomCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSEntCodNomNombreOpcional01 () == BOOL_VAL_CIERTO ) &&
			( TestSEntCodNomEstablecer01 () == BOOL_VAL_CIERTO ) &&
			( TestSEntCodNomIdentidad01 () == BOOL_VAL_CIERTO ) &&
			( TestSEntCodNomComparar01 () == BOOL_VAL_CIERTO ) )
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
