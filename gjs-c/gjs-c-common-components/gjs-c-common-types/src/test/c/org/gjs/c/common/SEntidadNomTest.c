#include "Base.h"

#include "SEntidadNom.h"



static int TestSEntNomCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	char cCarga [] = "carga";
	printf( "Test SEntNomCrear 01:\n" );

	/* Por defecto: id 0 y nombre vacio, asi que aun no es valida. */
	SEntidadNom * p_entnObj = SEntNomCrearDef ();
	if ( ES_VALIDO ( p_entnObj ) )
	{
		if ( SEntNomValorId ( p_entnObj ) != 0 )
		{
			printf( "Error caso 1: se esperaba id 0: %lu\n", SEntNomValorId ( p_entnObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntNomEsValida ( p_entnObj ) != 0 )
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
	SEntNomDestruir ( &p_entnObj );

	/* Con id y nombre. La validez la da el identificador, no el nombre. */
	p_entnObj = SEntNomCrearLit ( 42, "cliente_uno" );
	if ( ES_VALIDO ( p_entnObj ) )
	{
		if ( SEntNomValorId ( p_entnObj ) != 42 )
		{
			printf( "Error caso 3: se esperaba id 42: %lu\n", SEntNomValorId ( p_entnObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( CadComparar ( SEntNomValorNombreLit ( p_entnObj ), "cliente_uno" ) != COMP_IGUAL )
		{
			printf( "Error caso 4: se esperaba nombre \"cliente_uno\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntNomEsValida ( p_entnObj ) != 1 )
		{
			printf( "Error caso 5: con id asignado deberia ser valida\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_NULO ( SEntNomBase ( p_entnObj ) ) )
		{
			printf( "Error caso 6: se esperaba la entidad base\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la entidad con nombre\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SEntNomDestruir ( &p_entnObj );

	/* Destruir devuelve el contenido y anula el puntero. */
	p_entnObj = SEntNomCrearLitExt ( 7, "cliente_dos", cCarga );
	if ( ES_NULO ( p_entnObj ) )
	{
		printf( "Error caso 0: no se pudo crear la entidad con contenido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SEntNomDestruir ( &p_entnObj ) != (void *) cCarga )
	{
		printf( "Error caso 7: destruir deberia devolver el contenido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( p_entnObj ) )
	{
		printf( "Error caso 8: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSEntNomNombreOpcional01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SEntNomNombreOpcional 01:\n" );

	/* Un nombre con blancos no supera la validacion de SNombre. La entidad se
	   crea igualmente: solo se exige el id, y en lugar del nombre invalido se
	   pone uno vacio. */
	SEntidadNom * p_entnObj = SEntNomCrearLit ( 5, "con blanco" );
	if ( ES_VALIDO ( p_entnObj ) )
	{
		if ( ES_NULO ( SEntNomNombre ( p_entnObj ) ) )
		{
			printf( "Error caso 1: se esperaba un SNombre vacio, no nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( CadLongitud ( SEntNomValorNombreLit ( p_entnObj ) ) != 0 )
		{
			printf( "Error caso 2: se esperaba el nombre vacio\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Vacio no es lo mismo que valido: el nombre no pasa SNomEsValido. */
		if ( SNomEsValido ( SEntNomNombre ( p_entnObj ) ) != 0 )
		{
			printf( "Error caso 3: un nombre vacio no deberia ser valido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Pero la entidad si lo es: la validez es cosa del identificador. */
		if ( SEntNomEsValida ( p_entnObj ) != 1 )
		{
			printf( "Error caso 4: deberia ser valida aunque el nombre este vacio\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Y como el SNombre existe, se le puede poner uno despues. */
		if ( SEntNomEstablecerValorNombreLit ( p_entnObj, "cliente_uno" ) != 1 )
		{
			printf( "Error caso 5: se esperaba poder establecer el nombre despues\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( CadComparar ( SEntNomValorNombreLit ( p_entnObj ), "cliente_uno" ) != COMP_IGUAL )
		{
			printf( "Error caso 6: se esperaba nombre \"cliente_uno\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear la entidad\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SEntNomDestruir ( &p_entnObj );

	/* Sin identificador no hay entidad, aunque el nombre sea correcto. Y al
	   fallar, Encapsular no se queda con el nombre: sigue siendo del llamante,
	   que es quien lo destruye. */
	SNombre * p_nomSuelto = SNomCrearValorLit ( "cliente_uno" );
	p_entnObj = SEntNomEncapsular ( NULL, p_nomSuelto );
	if ( ES_VALIDO ( p_entnObj ) )
	{
		printf( "Error caso 7: encapsular sin id deberia dar nulo\n" );
		iRes = BOOL_VAL_FALSO;
		SEntNomDestruir ( &p_entnObj );
	}
	SNomDestruir ( &p_nomSuelto );
	return ( iRes );
}

static int TestSEntNomEstablecer01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SEntNomEstablecer 01:\n" );

	SEntidadNom * p_entnObj = SEntNomCrearLit ( 1, "cliente_uno" );
	if ( ES_VALIDO ( p_entnObj ) )
	{
		if ( SEntNomEstablecerValorId ( p_entnObj, 99 ) != 1 )
		{
			printf( "Error caso 1: se esperaba 1 al establecer el valor del id\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntNomValorId ( p_entnObj ) != 99 )
		{
			printf( "Error caso 2: se esperaba id 99: %lu\n", SEntNomValorId ( p_entnObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntNomEstablecerValorNombreLit ( p_entnObj, "cliente_dos" ) != 1 )
		{
			printf( "Error caso 3: se esperaba 1 al establecer el nombre\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( CadComparar ( SEntNomValorNombreLit ( p_entnObj ), "cliente_dos" ) != COMP_IGUAL )
		{
			printf( "Error caso 4: se esperaba nombre \"cliente_dos\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* El cambio de id se ve tambien desde la base, que es el mismo objeto. */
		if ( SEntValorId ( SEntNomBase ( p_entnObj ) ) != 99 )
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
	SEntNomDestruir ( &p_entnObj );
	return ( iRes );
}

static int TestSEntNomIdentidad01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SEntNomIdentidad 01:\n" );

	/* Mismo id y distinto nombre: la identidad es el id, y nada mas. */
	SEntidadNom * p_entnA = SEntNomCrearLit ( 10, "cliente_uno" );
	SEntidadNom * p_entnB = SEntNomCrearLit ( 10, "cliente_dos" );
	if ( ES_VALIDO ( p_entnA ) && ES_VALIDO ( p_entnB ) )
	{
		if ( SEntNomEsIgual ( p_entnA, p_entnB ) != 1 )
		{
			printf( "Error caso 1: mismo id deberia ser igual pese al nombre\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Contrato hash-igualdad: si son iguales, mismo hash. El nombre es
		   mutable, asi que no puede entrar en el reparto. */
		if ( SEntNomHash ( p_entnA ) != SEntNomHash ( p_entnB ) )
		{
			printf( "Error caso 2: entidades iguales deberian tener el mismo hash\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Y reparte igual que su base, para poder convivir en la misma tabla. */
		if ( SEntNomHash ( p_entnA ) != SEntHash ( SEntNomBase ( p_entnA ) ) )
		{
			printf( "Error caso 3: deberia repartir igual que su entidad base\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Cambiar el nombre no cambia ni la identidad ni el hash. */
		SEntNomEstablecerValorNombreLit ( p_entnA, "cliente_tres" );
		if ( SEntNomHash ( p_entnA ) != SEntNomHash ( p_entnB ) )
		{
			printf( "Error caso 4: cambiar el nombre no deberia cambiar el hash\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Ids distintos: ya no son iguales. */
		SEntNomEstablecerValorId ( p_entnB, 20 );
		if ( SEntNomEsIgual ( p_entnA, p_entnB ) != 0 )
		{
			printf( "Error caso 5: ids distintos no deberian ser iguales\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntNomEsMenor ( p_entnA, p_entnB ) != 1 )
		{
			printf( "Error caso 6: 10 deberia ser menor que 20\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntNomEsIgualNum ( p_entnA, 10 ) != 1 )
		{
			printf( "Error caso 7: deberia ser igual a 10\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Contra la clase base, por el id. */
		if ( SEntNomEsIgualEnt ( p_entnA, SEntNomBase ( p_entnB ) ) != 0 )
		{
			printf( "Error caso 8: no deberia ser igual a una base con otro id\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear las entidades\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SEntNomDestruir ( &p_entnA );
	SEntNomDestruir ( &p_entnB );
	return ( iRes );
}

static int TestSEntNomComparar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SEntNomComparar 01:\n" );

	/* Nombres "cliente_a" y "cliente_b" para que el orden alfabetico del
	   desempate no dependa de como se lean. */
	SEntidadNom * p_entnA = SEntNomCrearLit ( 10, "cliente_a" );
	SEntidadNom * p_entnB = SEntNomCrearLit ( 20, "cliente_b" );
	if ( ES_VALIDO ( p_entnA ) && ES_VALIDO ( p_entnB ) )
	{
		if ( SEntNomComparar ( p_entnA, p_entnB ) != COMP_MENOR )
		{
			printf( "Error caso 1: 10 frente a 20 deberia dar COMP_MENOR: %d\n", SEntNomComparar ( p_entnA, p_entnB ) );
			iRes = BOOL_VAL_FALSO;
		}
		/* Con el mismo id, Comparar desempata por nombre. Es deliberado y
		   provisional: sirve para ordenar listas cuyos ids aun no estan
		   asignados o estan repetidos. No es el criterio de identidad, que es
		   solo el id: por eso EsIgual sigue diciendo que son iguales. */
		SEntNomEstablecerValorId ( p_entnB, 10 );
		if ( SEntNomComparar ( p_entnA, p_entnB ) != COMP_MENOR )
		{
			printf( "Error caso 2: con el mismo id deberia desempatar por nombre: %d\n", SEntNomComparar ( p_entnA, p_entnB ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntNomEsIgual ( p_entnA, p_entnB ) != 1 )
		{
			printf( "Error caso 3: el desempate no deberia afectar a EsIgual\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Mismo id y mismo nombre: iguales tambien para Comparar. */
		SEntNomEstablecerValorNombreLit ( p_entnB, "cliente_a" );
		if ( SEntNomComparar ( p_entnA, p_entnB ) != COMP_IGUAL )
		{
			printf( "Error caso 4: mismo id y nombre deberia dar COMP_IGUAL: %d\n", SEntNomComparar ( p_entnA, p_entnB ) );
			iRes = BOOL_VAL_FALSO;
		}
		/* Orden con nulos. */
		if ( SEntNomComparar ( p_entnA, NULL ) != COMP_MAYOR )
		{
			printf( "Error caso 5: frente a una entidad nula deberia dar COMP_MAYOR\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntNomComparar ( NULL, p_entnA ) != COMP_MENOR )
		{
			printf( "Error caso 6: una entidad nula deberia dar COMP_MENOR\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntNomComparar ( NULL, NULL ) != COMP_IGUAL )
		{
			printf( "Error caso 7: dos entidades nulas deberian dar COMP_IGUAL\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SEntNomCompararNum ( p_entnA, 5 ) != COMP_MAYOR )
		{
			printf( "Error caso 8: 10 frente a 5 deberia dar COMP_MAYOR: %d\n", SEntNomCompararNum ( p_entnA, 5 ) );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear las entidades\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SEntNomDestruir ( &p_entnA );
	SEntNomDestruir ( &p_entnB );
	return ( iRes );
}



int TestSEntidadNom ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SEntidadNom]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSEntNomCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSEntNomNombreOpcional01 () == BOOL_VAL_CIERTO ) &&
			( TestSEntNomEstablecer01 () == BOOL_VAL_CIERTO ) &&
			( TestSEntNomIdentidad01 () == BOOL_VAL_CIERTO ) &&
			( TestSEntNomComparar01 () == BOOL_VAL_CIERTO ) )
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
