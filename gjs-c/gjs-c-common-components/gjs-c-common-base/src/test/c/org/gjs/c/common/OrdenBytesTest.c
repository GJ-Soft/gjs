#include "Base.h"

#include "OrdenBytes.h"



static int TestBytesOrden01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test BytesOrden 01:\n" );
	/* El orden es dependiente de la maquina, pero debe ser uno y solo uno. */
	int iNum = BytesOrdenNormal () + BytesOrdenInvertido () + BytesOrdenMixto ();
	if ( iNum != 1 )
	{
		printf( "Error caso 1: se esperaba exactamente un tipo de orden: %d\n", iNum );
		iRes = BOOL_VAL_FALSO;
	}
	/* El numero de bytes analizado debe ser 2 o 4. */
	if ( ( BytesOrden4 () != 1 ) && ( BytesOrden2 () != 1 ) )
	{
		printf( "Error caso 2: se esperaba orden de 2 o 4 bytes\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( BytesOrden () == NULL )
	{
		printf( "Error caso 3: no se esperaba nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestBytesInvertir01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test BytesInvertir 01:\n" );
	byte byBuffer [ 4 ] = { 1, 2, 3, 4 };
	int iResult = BytesInvertir ( byBuffer, 4, 0 );
	if ( iResult != 1 )
	{
		printf( "Error caso 1: se esperaba resultado 1: %d\n", iResult );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ( byBuffer[ 0 ] != 4 ) || ( byBuffer[ 1 ] != 3 ) ||
			( byBuffer[ 2 ] != 2 ) || ( byBuffer[ 3 ] != 1 ) )
	{
		printf( "Error caso 2: buffer no invertido correctamente: %d %d %d %d\n",
				byBuffer[ 0 ], byBuffer[ 1 ], byBuffer[ 2 ], byBuffer[ 3 ] );
		iRes = BOOL_VAL_FALSO;
	}
	/* Con puntero nulo o tamano <= 1 debe fallar y generar error. */
	ErrLimpiar ();
	iResult = BytesInvertir ( NULL, 4, 0 );
	if ( iResult != 0 )
	{
		printf( "Error caso 3: se esperaba resultado 0: %d\n", iResult );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ErrHayError () != 1 )
	{
		printf( "Error caso 4: se esperaba que se generase error\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestBytesInvertirEntero01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test BytesInvertirEntero 01:\n" );
	int iValor = 0x12345678;
	int iOriginal = iValor;
	BytesInvertirEntero ( &iValor, 0 );
	if ( iValor == iOriginal )
	{
		printf( "Error caso 1: se esperaba un valor invertido\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* Al invertir dos veces se debe recuperar el valor original. */
	BytesInvertirEntero ( &iValor, 0 );
	if ( iValor != iOriginal )
	{
		printf( "Error caso 2: se esperaba recuperar el valor original: 0x%08X\n", iValor );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestBytesOrdenar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test BytesOrdenar 01:\n" );
	int iValor = 0x12345678;
	int iOriginal = iValor;
	/* Ordenar al orden actual de la maquina no debe modificar el valor. */
	int iOrdenActual;
	if ( BytesOrdenNormal () == 1 )
	{
		iOrdenActual = BYTE_ORDEN_NORMAL;
	}
	else
	{
		iOrdenActual = BYTE_ORDEN_INVERTIDO;
	}
	int iResult = BytesOrdenarEntero ( &iValor, iOrdenActual );
	if ( iResult != 1 )
	{
		printf( "Error caso 1: se esperaba resultado 1: %d\n", iResult );
		iRes = BOOL_VAL_FALSO;
	}
	if ( iValor != iOriginal )
	{
		printf( "Error caso 2: no se esperaba modificacion: 0x%08X\n", iValor );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}



int TestOrdenBytes ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test OrdenBytes]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestBytesOrden01 () == BOOL_VAL_CIERTO ) &&
			( TestBytesInvertir01 () == BOOL_VAL_CIERTO ) &&
			( TestBytesInvertirEntero01 () == BOOL_VAL_CIERTO ) &&
			( TestBytesOrdenar01 () == BOOL_VAL_CIERTO ) )
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
