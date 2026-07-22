#include "Base.h"

#include "CadenasBase.h"



static int TestCadCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test CadCrear 01:\n" );
	char * p_cRes = CadCrear ( -1 );
	if ( p_cRes != NULL )
	{
		printf( "Error caso 1: se esperaba nulo\n" );
		iRes = BOOL_VAL_FALSO;
		MemLiberar ( (void **) &p_cRes );
	}
	p_cRes = CadCrear ( 0 );
	if ( p_cRes != NULL )
	{
		int iLong = strlen ( p_cRes );
		if ( iLong != 0 )
		{
			printf( "Error caso 2: se esperaba cadena de longitud 0: %d\n", iLong );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 2: no se esperaba valor nulo\n" );
		iRes = BOOL_VAL_FALSO;
	} 
	MemLiberar ( (void **) &p_cRes );
	p_cRes = CadCrear ( 10 );
	if ( p_cRes != NULL )
	{
		int iLong = strlen ( p_cRes );
		if ( iLong == 0 )
		{
			p_cRes[ 0 ] = 'A';
			iLong = strlen ( p_cRes );
			if ( iLong == 1 )
			{
				p_cRes[ 1 ] = 'B';
				p_cRes[ 2 ] = 'C';
				p_cRes[ 3 ] = 'D';
				p_cRes[ 4 ] = 'E';
				p_cRes[ 5 ] = 'F';
				p_cRes[ 5 ] = 'G';
				p_cRes[ 6 ] = 'H';
				p_cRes[ 7 ] = 'I';
				p_cRes[ 8 ] = 'J';
				p_cRes[ 9 ] = 'K';
				iLong = strlen ( p_cRes );
				if ( iLong != 10 )
				{
					printf( "Error caso 3: se esperaba cadena de longitud 10: %d\n", iLong );
					iRes = BOOL_VAL_FALSO;
				}
			}
			else
			{
				printf( "Error caso 3: se esperaba cadena de longitud 1: %d\n", iLong );
				iRes = BOOL_VAL_FALSO;
			}
		}
		else
		{
			printf( "Error caso 3: se esperaba cadena de longitud 0: %d\n", iLong );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 3: no se esperaba valor nulo\n" );
		iRes = BOOL_VAL_FALSO;
	} 
	MemLiberar ( (void **) &p_cRes );
	return ( iRes );
}

static int TestCadLongitud01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test CadLongitud 01:\n" );
	char * p_cRes = NULL;
	int iLong = CadLongitud ( p_cRes );
	if ( iLong == -1 )
	{
		if ( ErrHayError () == 1 )
		{
			printf( "[%s:%d] %d-%s\n", ErrModulo (), ErrLinea(), ErrCodigo (), ErrDescripcion () );
		}
		else
		{
			printf( "Error caso 1: se esperaba que se generade error\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 1: se esperaba cadena de longitud -1: %d\n", iLong );
		iRes = BOOL_VAL_FALSO;
	}
	p_cRes = CadCrear ( 10 );
	iLong = CadLongitud ( p_cRes );
	if ( iLong != 0 )
	{
		printf( "Error caso 1: se esperaba cadena de longitud 0: %d\n", iLong );
		iRes = BOOL_VAL_FALSO;
	}	
	strcpy ( p_cRes, "01234" );
	iLong = CadLongitud ( p_cRes );
	if ( iLong != 5 )
	{
		printf( "Error caso 1: se esperaba cadena de longitud 5: %d\n", iLong );
		iRes = BOOL_VAL_FALSO;
	}	
	MemLiberar ( (void **) &p_cRes );
	return ( iRes );
}

static int TestCadLongitudSeg01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test CadLongitudSeg 01:\n" );
	char * p_cRes = NULL;
	int iLong = CadLongitudSeg ( p_cRes, 10 );
	if ( iLong == -1 )
	{
		if ( ErrHayError () == 1 )
		{
			printf( "[%s:%d] %d-%s\n", ErrModulo (), ErrLinea(), ErrCodigo (), ErrDescripcion () );
		}
		else
		{
			printf( "Error caso 1: se esperaba que se generade error\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 1: se esperaba cadena de longitud -1: %d\n", iLong );
		iRes = BOOL_VAL_FALSO;
	}
	p_cRes = CadCrear ( 10 );
	iLong = CadLongitudSeg ( p_cRes, 10 );
	if ( iLong != 0 )
	{
		printf( "Error caso 2: se esperaba cadena de longitud 0: %d\n", iLong );
		iRes = BOOL_VAL_FALSO;
	}	
	strcpy ( p_cRes, "01234" );
	iLong = CadLongitudSeg ( p_cRes, 10 );
	if ( iLong != 5 )
	{
		printf( "Error caso 3: se esperaba cadena de longitud 5: %d\n", iLong );
		iRes = BOOL_VAL_FALSO;
	}	
	strcpy ( p_cRes, "0123456789" );
	iLong = CadLongitudSeg ( p_cRes, 10 );
	if ( iLong != 10 )
	{
		printf( "Error caso 4: se esperaba cadena de longitud 10: %d\n", iLong );
		iRes = BOOL_VAL_FALSO;
	}	
	iLong = CadLongitudSeg ( p_cRes, 5 );
	if ( iLong != 5 )
	{
		printf( "Error caso 5: se esperaba cadena de longitud 5: %d\n", iLong );
		iRes = BOOL_VAL_FALSO;
	}	
	MemLiberar ( (void **) &p_cRes );
	return ( iRes );
}

static int TestCadInicializar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test CadInicializar 01:\n" );
	char * p_cRes = NULL;
	CadInicializar ( p_cRes, 10 );
	p_cRes = CadCrear ( 10 );
	CadInicializar ( p_cRes, 10 );
	int iLong = CadLongitud ( p_cRes );
	if ( iLong != 0 )
	{
		printf( "Error caso 1: se esperaba cadena de longitud 0: %d\n", iLong );
		iRes = BOOL_VAL_FALSO;
	}	
	strcpy ( p_cRes, "0123456789" );
	CadInicializar ( p_cRes, 10 );
	iLong = CadLongitud ( p_cRes );
	if ( iLong != 0 )
	{
		printf( "Error caso 1: se esperaba cadena de longitud 0: %d\n", iLong );
		iRes = BOOL_VAL_FALSO;
	}	
	MemLiberar ( (void **) &p_cRes );
	return ( iRes );
}

static int TestCadDuplicar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test CadDuplicar 01:\n" );
	char * p_cRes = CadDuplicar ( NULL );
	if ( p_cRes != NULL )
	{
		printf( "Error caso 1: se esperaba nulo\n" );
		iRes = BOOL_VAL_FALSO;
		MemLiberar ( (void **) &p_cRes );
	}
	p_cRes = CadDuplicar ( "ABC" );
	if ( p_cRes != NULL )
	{
		int iLong = strlen ( p_cRes );
		if ( iLong == 3 )
		{
			if ( strcmp ( p_cRes, "ABC" ) != 0 )
			{
				printf( "Error caso 3: la cadena duplicada es diferente: [%s]/[ABC]\n", p_cRes );
				iRes = BOOL_VAL_FALSO;
			}
		}
		else
		{
			printf( "Error caso 2: se esperaba cadena de longitud 3: %d\n", iLong );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 2: no se esperaba nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	char * p_cRes2 = CadDuplicar ( p_cRes );
	if ( p_cRes2 != NULL )
	{
		int iLong = strlen ( p_cRes2 );
		if ( iLong == 3 )
		{
			if ( strcmp ( p_cRes2, p_cRes ) != 0 )
			{
				printf( "Error caso 3: la cadena duplicada es diferente: [%s]/[%s]\n", p_cRes, p_cRes2 );
				iRes = BOOL_VAL_FALSO;
			}
		}
		else
		{
			printf( "Error caso 2: se esperaba cadena de longitud 3: %d\n", iLong );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 2: no se esperaba nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	MemLiberar ( (void **) &p_cRes );
	MemLiberar ( (void **) &p_cRes2 );
	return ( iRes );
}


static int TestCadDuplicarSeg01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test CadDuplicarSeg 01:\n" );
	char * p_cRes = CadDuplicarSeg ( NULL, 10 );
	if ( p_cRes != NULL )
	{
		printf( "Error caso 1: se esperaba nulo\n" );
		iRes = BOOL_VAL_FALSO;
		MemLiberar ( (void **) &p_cRes );
	}
	p_cRes = CadDuplicarSeg ( "ABC", 10 );
	if ( p_cRes != NULL )
	{
		int iLong = strlen ( p_cRes );
		if ( iLong == 3 )
		{
			if ( strcmp ( p_cRes, "ABC" ) != 0 )
			{
				printf( "Error caso 3: la cadena duplicada es diferente: [%s]/[ABC]\n", p_cRes );
				iRes = BOOL_VAL_FALSO;
			}
		}
		else
		{
			printf( "Error caso 2: se esperaba cadena de longitud 3: %d\n", iLong );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 2: no se esperaba nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	char * p_cRes2 = CadDuplicarSeg ( p_cRes, 10 );
	if ( p_cRes2 != NULL )
	{
		int iLong = strlen ( p_cRes2 );
		if ( iLong == 3 )
		{
			if ( strcmp ( p_cRes2, p_cRes ) != 0 )
			{
				printf( "Error caso 3: la cadena duplicada es diferente: [%s]/[%s]\n", p_cRes, p_cRes2 );
				iRes = BOOL_VAL_FALSO;
			}
		}
		else
		{
			printf( "Error caso 2: se esperaba cadena de longitud 3: %d\n", iLong );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 2: no se esperaba nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	MemLiberar ( (void **) &p_cRes );
	MemLiberar ( (void **) &p_cRes2 );
	p_cRes = CadDuplicarSeg ( "ABCDEFGHIJKLMN", 10 );
	if ( p_cRes != NULL )
	{
		int iLong = strlen ( p_cRes );
		if ( iLong == 10 )
		{
			if ( strcmp ( p_cRes, "ABCDEFGHIJKLMN" ) == 0 )
			{
				printf( "Error caso 3: la cadena duplicada debe ser diferente: [%s]/[ABCDEFGHIJKLMN]\n", p_cRes );
				iRes = BOOL_VAL_FALSO;
			}
			else if ( strcmp ( p_cRes, "ABCDEFGHIJ" ) != 0 )
			{
				printf( "Error caso 3: la cadena duplicada debe ser igual: [%s]/[ABCDEFGHIJ]\n", p_cRes );
				iRes = BOOL_VAL_FALSO;
			}
		}
		else
		{
			printf( "Error caso 2: se esperaba cadena de longitud 3: %d\n", iLong );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 2: no se esperaba nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	MemLiberar ( (void **) &p_cRes );
	return ( iRes );
}

static int TestCadComparar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test CadComparar 01:\n" );
	char * p_cCadena1 = NULL;
	char * p_cCadena2 = NULL;
	int iResult = CadComparar ( p_cCadena1, p_cCadena2 );
	if ( iResult != COMP_IGUAL )
	{
		printf( "Error caso 1: se esperaban iguales el resultado es %d \n", iResult );
		iRes = BOOL_VAL_FALSO;
	}
	p_cCadena1 = CadCrear ( 10 );
	iResult = CadComparar ( p_cCadena1, p_cCadena2 );
	if ( iResult != COMP_MAYOR )
	{
		printf( "Error caso 2: se esperaba mayor el resultado es %d \n", iResult );
		iRes = BOOL_VAL_FALSO;
	}
	iResult = CadComparar ( p_cCadena2, p_cCadena1 );
	if ( iResult != COMP_MENOR )
	{
		printf( "Error caso 3: se esperaba menor el resultado es %d \n", iResult );
		iRes = BOOL_VAL_FALSO;
	}
	p_cCadena2 = CadCrear ( 10 );
	iResult = CadComparar ( p_cCadena1, p_cCadena2 );
	if ( iResult != COMP_IGUAL )
	{
		printf( "Error caso 4: se esperaban iguales el resultado es %d \n", iResult );
		iRes = BOOL_VAL_FALSO;
	}
	MemLiberar ( (void **) &p_cCadena1 );
	MemLiberar ( (void **) &p_cCadena2 );
	return ( iRes );
}

static int TestCadComparar02 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test CadComparar 01:\n" );
	char * p_cCadena1 = CadDuplicar ( "Cadena1" );
	char * p_cCadena2 = CadDuplicar ( "Cadena1 Mas Larga 2 " );
	char * p_cCadena3 = CadDuplicar ( "Cadena2" );
	char * p_cCadena4 = CadDuplicar ( "Cadena1" );
	char * p_cCadena5 = CadDuplicar ( "Cad4na5" );
	int iResult = CadComparar ( p_cCadena1, p_cCadena2 );
	if ( iResult != COMP_MENOR )
	{
		printf( "Error caso 1: se esperaba menor el resultado es %d \n", iResult );
		iRes = BOOL_VAL_FALSO;
	}
	iResult = CadComparar ( p_cCadena2, p_cCadena1 );
	if ( iResult != COMP_MAYOR )
	{
		printf( "Error caso 2: se esperaba mayor el resultado es %d \n", iResult );
		iRes = BOOL_VAL_FALSO;
	}
	iResult = CadComparar ( p_cCadena1, p_cCadena3 );
	if ( iResult != COMP_MENOR )
	{
		printf( "Error caso 3: se esperaba menor el resultado es %d \n", iResult );
		iRes = BOOL_VAL_FALSO;
	}
	iResult = CadComparar ( p_cCadena3, p_cCadena1 );
	if ( iResult != COMP_MAYOR )
	{
		printf( "Error caso 4: se esperaba mayor el resultado es %d \n", iResult );
		iRes = BOOL_VAL_FALSO;
	}
	iResult = CadComparar ( p_cCadena1, p_cCadena4 );
	if ( iResult != COMP_IGUAL )
	{
		printf( "Error caso 4: se esperaban iguales el resultado es %d \n", iResult );
		iRes = BOOL_VAL_FALSO;
	}
	iResult = CadComparar ( p_cCadena1, p_cCadena5 );
	if ( iResult != COMP_MAYOR )
	{
		printf( "Error caso 5: se esperaba mayor el resultado es %d \n", iResult );
		iRes = BOOL_VAL_FALSO;
	}
	iResult = CadComparar ( p_cCadena5, p_cCadena1 );
	if ( iResult != COMP_MENOR )
	{
		printf( "Error caso 6: se esperaba mayor el resultado es %d \n", iResult );
		iRes = BOOL_VAL_FALSO;
	}
	MemLiberar ( (void **) &p_cCadena1 );
	MemLiberar ( (void **) &p_cCadena2 );
	MemLiberar ( (void **) &p_cCadena3 );
	MemLiberar ( (void **) &p_cCadena4 );
	MemLiberar ( (void **) &p_cCadena5 );
	return ( iRes );
}



int TestCadenasBase ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test CadenasBase]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestCadCrear01() == BOOL_VAL_CIERTO ) &&
			( TestCadLongitud01 () == BOOL_VAL_CIERTO ) &&
			( TestCadLongitudSeg01 () == BOOL_VAL_CIERTO ) &&
			( TestCadInicializar01 () == BOOL_VAL_CIERTO ) &&
			( TestCadDuplicar01 () == BOOL_VAL_CIERTO ) &&
			( TestCadDuplicarSeg01 () == BOOL_VAL_CIERTO ) &&
			( TestCadComparar01 () == BOOL_VAL_CIERTO ) &&
			( TestCadComparar02 () == BOOL_VAL_CIERTO ) )
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
