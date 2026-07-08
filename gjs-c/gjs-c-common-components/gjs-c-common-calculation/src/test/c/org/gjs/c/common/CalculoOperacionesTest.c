#include "Base.h"

#include "CalculoOperaciones.h"



static int TestMatEnteros01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test MatEnteros 01:\n" );

	if ( MatEnteroEsPar ( 4 ) != 1 )
	{
		printf( "Error caso 1: 4 deberia ser par\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( MatEnteroEsPar ( 3 ) != 0 )
	{
		printf( "Error caso 2: 3 no deberia ser par\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( MatEnteroEsImpar ( 3 ) != 1 )
	{
		printf( "Error caso 3: 3 deberia ser impar\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( MatEnteroAbsoluto ( -5 ) != 5 )
	{
		printf( "Error caso 4: el absoluto de -5 deberia ser 5: %ld\n", MatEnteroAbsoluto ( -5 ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( MatEnteroSigno ( -3 ) != -1 )
	{
		printf( "Error caso 5: el signo de -3 deberia ser -1: %ld\n", MatEnteroSigno ( -3 ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( MatEnteroSigno ( 3 ) != 1 )
	{
		printf( "Error caso 6: el signo de 3 deberia ser 1: %ld\n", MatEnteroSigno ( 3 ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( MatModulo ( 7, 3 ) != 1 )
	{
		printf( "Error caso 7: 7 modulo 3 deberia ser 1: %ld\n", MatModulo ( 7, 3 ) );
		iRes = BOOL_VAL_FALSO;
	}
	/* El modulo de un negativo se lleva al rango positivo. */
	if ( MatModulo ( -1, 3 ) != 2 )
	{
		printf( "Error caso 8: -1 modulo 3 deberia ser 2: %ld\n", MatModulo ( -1, 3 ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( MatFactorial ( 0 ) != 1 )
	{
		printf( "Error caso 9: 0! deberia ser 1: %lu\n", MatFactorial ( 0 ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( MatFactorial ( 5 ) != 120 )
	{
		printf( "Error caso 10: 5! deberia ser 120: %lu\n", MatFactorial ( 5 ) );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestMatReales01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test MatReales 01:\n" );

	if ( MatEsIgual ( MatRealAbsoluto ( -2.5 ), 2.5 ) != 1 )
	{
		printf( "Error caso 1: el absoluto de -2.5 deberia ser 2.5: %f\n", MatRealAbsoluto ( -2.5 ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( MatEsIgual ( MatRealSigno ( -1.0 ), -1.0 ) != 1 )
	{
		printf( "Error caso 2: el signo de -1.0 deberia ser -1.0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* Redondeo al entero mas cercano ( 0.5 hacia arriba ). */
	if ( MatEsIgual ( MatRealRedondear ( 2.4 ), 2.0 ) != 1 )
	{
		printf( "Error caso 3: 2.4 deberia redondear a 2: %f\n", MatRealRedondear ( 2.4 ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( MatEsIgual ( MatRealRedondear ( 2.6 ), 3.0 ) != 1 )
	{
		printf( "Error caso 4: 2.6 deberia redondear a 3: %f\n", MatRealRedondear ( 2.6 ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( MatEsIgual ( MatRealRedondear ( 2.5 ), 3.0 ) != 1 )
	{
		printf( "Error caso 5: 2.5 deberia redondear a 3: %f\n", MatRealRedondear ( 2.5 ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( MatEsIgual ( MatMedia ( 4.0, 6.0 ), 5.0 ) != 1 )
	{
		printf( "Error caso 6: la media de 4 y 6 deberia ser 5: %f\n", MatMedia ( 4.0, 6.0 ) );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestMatPotencias01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test MatPotencias 01:\n" );

	if ( MatEsIgual ( MatCuadrado ( 3.0 ), 9.0 ) != 1 )
	{
		printf( "Error caso 1: el cuadrado de 3 deberia ser 9: %f\n", MatCuadrado ( 3.0 ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( MatEsIgual ( MatCubo ( 2.0 ), 8.0 ) != 1 )
	{
		printf( "Error caso 2: el cubo de 2 deberia ser 8: %f\n", MatCubo ( 2.0 ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( MatEsIgual ( MatRaiz ( 9.0, 2.0 ), 3.0 ) != 1 )
	{
		printf( "Error caso 3: la raiz cuadrada de 9 deberia ser 3: %f\n", MatRaiz ( 9.0, 2.0 ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( MatEsIgual ( MatRaizCubica ( 27.0 ), 3.0 ) != 1 )
	{
		printf( "Error caso 4: la raiz cubica de 27 deberia ser 3: %f\n", MatRaizCubica ( 27.0 ) );
		iRes = BOOL_VAL_FALSO;
	}
	/* Terna pitagorica 3-4-5. */
	if ( MatEsIgual ( MatHipotenusa2D ( 3.0, 4.0 ), 5.0 ) != 1 )
	{
		printf( "Error caso 5: la hipotenusa de 3 y 4 deberia ser 5: %f\n", MatHipotenusa2D ( 3.0, 4.0 ) );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestMatComparaciones01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test MatComparaciones 01:\n" );

	if ( MatEsIgual ( 1.0, 1.0 ) != 1 )
	{
		printf( "Error caso 1: 1.0 deberia ser igual a 1.0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* Diferencias por debajo de la precision se consideran iguales. */
	if ( MatEsIgual ( 1.0, 1.0000001 ) != 1 )
	{
		printf( "Error caso 2: 1.0 y 1.0000001 deberian ser iguales dentro de la precision\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( MatEsIgual ( 1.0, 1.001 ) != 0 )
	{
		printf( "Error caso 3: 1.0 y 1.001 no deberian ser iguales\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( MatEsMenor ( 1.0, 2.0 ) != 1 )
	{
		printf( "Error caso 4: 1.0 deberia ser menor que 2.0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( MatEsMayor ( 2.0, 1.0 ) != 1 )
	{
		printf( "Error caso 5: 2.0 deberia ser mayor que 1.0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( MatEsMenor ( 2.0, 1.0 ) != 0 )
	{
		printf( "Error caso 6: 2.0 no deberia ser menor que 1.0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestMatEcuaciones01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test MatEcuaciones 01:\n" );

	/* Ecuacion de primer grado: 2x - 4 = 0  ->  x = 2. */
	if ( MatEsIgual ( MatEc1GrdSolucion ( 2.0, -4.0 ), 2.0 ) != 1 )
	{
		printf( "Error caso 1: la solucion deberia ser 2: %f\n", MatEc1GrdSolucion ( 2.0, -4.0 ) );
		iRes = BOOL_VAL_FALSO;
	}
	/* Ecuacion de segundo grado: x^2 - 3x + 2 = 0  ->  x = 1 y x = 2. */
	if ( MatEc2GrdTieneSolucion ( 1.0, -3.0, 2.0 ) != 1 )
	{
		printf( "Error caso 2: la ecuacion deberia tener solucion\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( MatEsIgual ( MatEc2GrdSolucionMax ( 1.0, -3.0, 2.0 ), 2.0 ) != 1 )
	{
		printf( "Error caso 3: la solucion maxima deberia ser 2: %f\n", MatEc2GrdSolucionMax ( 1.0, -3.0, 2.0 ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( MatEsIgual ( MatEc2GrdSolucionMin ( 1.0, -3.0, 2.0 ), 1.0 ) != 1 )
	{
		printf( "Error caso 4: la solucion minima deberia ser 1: %f\n", MatEc2GrdSolucionMin ( 1.0, -3.0, 2.0 ) );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}



int TestCalculoOperaciones ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test CalculoOperaciones]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestMatEnteros01 () == BOOL_VAL_CIERTO ) &&
			( TestMatReales01 () == BOOL_VAL_CIERTO ) &&
			( TestMatPotencias01 () == BOOL_VAL_CIERTO ) &&
			( TestMatComparaciones01 () == BOOL_VAL_CIERTO ) &&
			( TestMatEcuaciones01 () == BOOL_VAL_CIERTO ) )
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
