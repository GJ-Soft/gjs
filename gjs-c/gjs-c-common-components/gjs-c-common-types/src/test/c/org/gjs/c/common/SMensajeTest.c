#include "Base.h"
#include "Texto.h"

#include "SMensaje.h"



static int TestSMsjCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SMsjCrear 01:\n" );

	SMensaje * p_msjObj = SMsjCrearLit ( 100, "Fichero no encontrado" );
	if ( ES_VALIDO ( p_msjObj ) )
	{
		if ( SMsjValorId ( p_msjObj ) != 100 )
		{
			printf( "Error caso 1: se esperaba id 100: %lu\n", SMsjValorId ( p_msjObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( CadComparar ( SMsjValorTextoLit ( p_msjObj ), "Fichero no encontrado" ) != COMP_IGUAL )
		{
			printf( "Error caso 2: se esperaba el texto del mensaje\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SMsjEsValido ( p_msjObj ) != 1 )
		{
			printf( "Error caso 3: con id asignado deberia ser valido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_NULO ( SMsjTexto ( p_msjObj ) ) )
		{
			printf( "Error caso 4: se esperaba la SDescripcion interna\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_NULO ( SMsjId ( p_msjObj ) ) )
		{
			printf( "Error caso 5: se esperaba el SId interno\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el mensaje\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SMsjDestruir ( &p_msjObj );

	if ( ES_VALIDO ( p_msjObj ) )
	{
		printf( "Error caso 6: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}

	/* Un id sin asignar ( 0 ) no da un mensaje valido. */
	p_msjObj = SMsjCrearLit ( 0, "Sin codigo" );
	if ( ES_VALIDO ( p_msjObj ) )
	{
		if ( SMsjEsValido ( p_msjObj ) != 0 )
		{
			printf( "Error caso 7: con id 0 no deberia ser valido\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el mensaje con id 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SMsjDestruir ( &p_msjObj );
	return ( iRes );
}

static int TestSMsjTextoOpcional01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SMsjTextoOpcional 01:\n" );

	/* Solo se exige el identificador: sin texto el mensaje se crea igual. */
	SMensaje * p_msjObj = SMsjCrearLit ( 5, NULL );
	if ( ES_VALIDO ( p_msjObj ) )
	{
		if ( ES_VALIDO ( SMsjTexto ( p_msjObj ) ) )
		{
			printf( "Error caso 1: se esperaba texto nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( SMsjValorTextoLit ( p_msjObj ) ) )
		{
			printf( "Error caso 2: se esperaba literal nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SMsjEsValido ( p_msjObj ) != 1 )
		{
			printf( "Error caso 3: deberia ser valido aunque no tenga texto\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el mensaje sin texto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SMsjDestruir ( &p_msjObj );

	/* Sin identificador no hay mensaje, aunque el texto sea correcto. Y al
	   fallar, Encapsular no se queda con la descripcion: sigue siendo del
	   llamante, que es quien la destruye. */
	SDescripcion * p_descSuelta = SDescCrearValorLit ( "Texto suelto" );
	p_msjObj = SMsjEncapsular ( NULL, p_descSuelta );
	if ( ES_VALIDO ( p_msjObj ) )
	{
		printf( "Error caso 4: encapsular sin id deberia dar nulo\n" );
		iRes = BOOL_VAL_FALSO;
		SMsjDestruir ( &p_msjObj );
	}
	SDescDestruir ( &p_descSuelta );
	return ( iRes );
}

static int TestSMsjComparaciones01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SMsjComparaciones 01:\n" );

	SMensaje * p_msjA = SMsjCrearLit ( 10, "Primero" );
	SMensaje * p_msjB = SMsjCrearLit ( 20, "Segundo" );
	if ( ES_VALIDO ( p_msjA ) && ES_VALIDO ( p_msjB ) )
	{
		if ( SMsjEsMenor ( p_msjA, p_msjB ) != 1 )
		{
			printf( "Error caso 1: 10 deberia ser menor que 20\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SMsjEsMayor ( p_msjB, p_msjA ) != 1 )
		{
			printf( "Error caso 2: 20 deberia ser mayor que 10\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SMsjEsIgual ( p_msjA, p_msjB ) != 0 )
		{
			printf( "Error caso 3: 10 y 20 no deberian ser iguales\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SMsjEsMenorIg ( p_msjA, p_msjB ) != 1 )
		{
			printf( "Error caso 4: 10 deberia ser menor o igual que 20\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SMsjEsIgualNum ( p_msjA, 10 ) != 1 )
		{
			printf( "Error caso 5: deberia ser igual a 10\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SMsjEsMayorIgNum ( p_msjA, 10 ) != 1 )
		{
			printf( "Error caso 6: 10 deberia ser mayor o igual que 10\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Contra un SId suelto. */
		if ( SMsjEsIgualId ( p_msjA, SMsjId ( p_msjA ) ) != 1 )
		{
			printf( "Error caso 7: deberia ser igual a su propio id\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SMsjEsMenorId ( p_msjA, SMsjId ( p_msjB ) ) != 1 )
		{
			printf( "Error caso 8: 10 deberia ser menor que el id 20\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear los mensajes\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SMsjDestruir ( &p_msjA );
	SMsjDestruir ( &p_msjB );
	return ( iRes );
}

static int TestSMsjComparar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SMsjComparar 01:\n" );

	SMensaje * p_msjA = SMsjCrearLit ( 10, "Aaa" );
	SMensaje * p_msjB = SMsjCrearLit ( 20, "Bbb" );
	SMensaje * p_msjC = SMsjCrearLit ( 10, "Zzz" );
	if ( ES_VALIDO ( p_msjA ) && ES_VALIDO ( p_msjB ) && ES_VALIDO ( p_msjC ) )
	{
		if ( SMsjComparar ( p_msjA, p_msjB ) != COMP_MENOR )
		{
			printf( "Error caso 1: 10 frente a 20 deberia dar COMP_MENOR: %d\n", SMsjComparar ( p_msjA, p_msjB ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SMsjComparar ( p_msjB, p_msjA ) != COMP_MAYOR )
		{
			printf( "Error caso 2: 20 frente a 10 deberia dar COMP_MAYOR: %d\n", SMsjComparar ( p_msjB, p_msjA ) );
			iRes = BOOL_VAL_FALSO;
		}
		/* A diferencia de las derivadas de SEntidad, SMensaje NO desempata por
		   el segundo campo: mismo id es COMP_IGUAL aunque el texto difiera, y
		   eso concuerda con lo que dice SMsjEsIgual. */
		if ( SMsjComparar ( p_msjA, p_msjC ) != COMP_IGUAL )
		{
			printf( "Error caso 3: mismo id deberia dar COMP_IGUAL pese al texto: %d\n", SMsjComparar ( p_msjA, p_msjC ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SMsjEsIgual ( p_msjA, p_msjC ) != 1 )
		{
			printf( "Error caso 4: mismo id deberia ser igual pese al texto\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Orden con nulos. */
		if ( SMsjComparar ( p_msjA, NULL ) != COMP_MAYOR )
		{
			printf( "Error caso 5: frente a un mensaje nulo deberia dar COMP_MAYOR\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SMsjComparar ( NULL, p_msjA ) != COMP_MENOR )
		{
			printf( "Error caso 6: un mensaje nulo deberia dar COMP_MENOR\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SMsjComparar ( NULL, NULL ) != COMP_IGUAL )
		{
			printf( "Error caso 7: dos mensajes nulos deberian dar COMP_IGUAL\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SMsjCompararNum ( p_msjA, 5 ) != COMP_MAYOR )
		{
			printf( "Error caso 8: 10 frente a 5 deberia dar COMP_MAYOR: %d\n", SMsjCompararNum ( p_msjA, 5 ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SMsjCompararId ( p_msjA, SMsjId ( p_msjB ) ) != COMP_MENOR )
		{
			printf( "Error caso 9: 10 frente al id 20 deberia dar COMP_MENOR: %d\n", SMsjCompararId ( p_msjA, SMsjId ( p_msjB ) ) );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear los mensajes\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SMsjDestruir ( &p_msjA );
	SMsjDestruir ( &p_msjB );
	SMsjDestruir ( &p_msjC );
	return ( iRes );
}

static int TestSMsjHash01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SMsjHash 01:\n" );

	SMensaje * p_msjA = SMsjCrearLit ( 12345, "Un texto" );
	SMensaje * p_msjB = SMsjCrearLit ( 12345, "Otro texto distinto" );
	SMensaje * p_msjC = SMsjCrearLit ( 999, "Un texto" );
	if ( ES_VALIDO ( p_msjA ) && ES_VALIDO ( p_msjB ) && ES_VALIDO ( p_msjC ) )
	{
		/* Contrato hash-igualdad: la identidad es el id, asi que el texto no
		   puede entrar en el reparto. */
		if ( SMsjEsIgual ( p_msjA, p_msjB ) != 1 )
		{
			printf( "Error caso 1: mismo id deberia ser igual\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SMsjHash ( p_msjA ) != SMsjHash ( p_msjB ) )
		{
			printf( "Error caso 2: mensajes iguales deberian tener el mismo hash\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Ids distintos con el mismo texto: hash distinto. */
		if ( SMsjHash ( p_msjA ) == SMsjHash ( p_msjC ) )
		{
			printf( "Error caso 3: ids distintos deberian dar hash distinto\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Un mensaje nulo hashea a 0. */
		if ( SMsjHash ( NULL ) != 0 )
		{
			printf( "Error caso 4: un mensaje nulo deberia hashear a 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear los mensajes\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SMsjDestruir ( &p_msjA );
	SMsjDestruir ( &p_msjB );
	SMsjDestruir ( &p_msjC );
	return ( iRes );
}



int TestSMensaje ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SMensaje]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSMsjCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSMsjTextoOpcional01 () == BOOL_VAL_CIERTO ) &&
			( TestSMsjComparaciones01 () == BOOL_VAL_CIERTO ) &&
			( TestSMsjComparar01 () == BOOL_VAL_CIERTO ) &&
			( TestSMsjHash01 () == BOOL_VAL_CIERTO ) )
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
