#include "Base.h"

#include "FormatoCadena.h"

/*
 * FrmCadena recibe el va_list ya construido, al estilo de vsnprintf, asi que para
 * probarla hace falta una funcion variadica que lo arme. Tiene que ser ella misma
 * la que llame a FrmCadena: un va_list solo vale dentro de la funcion que hizo el
 * va_start, porque apunta a la zona donde esa llamada dejo los argumentos, y esa
 * zona se reutiliza en cuanto el marco hace la siguiente llamada. El ayudante
 * anterior lo devolvia, que es comportamiento indefinido: funcionaba de casualidad
 * hasta que -ftrivial-auto-var-init=pattern del perfil debug cambio el codigo
 * generado y el %s paso a leer la propia cadena de formato.
 */
static int _FrmCadena ( char * p_cDestino, const char * p_cFormato, int iMaxTam, ... )
{
	va_list		valArgumentos;
	int			iRes;

	va_start ( valArgumentos, iMaxTam );
	iRes = FrmCadena ( p_cDestino, p_cFormato, valArgumentos, iMaxTam );
	va_end ( valArgumentos );
	return ( iRes );
}



static int TestFrmCadena01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test FrmCadena 01:\n" );
	char * p_cDestino = CadCrear ( 30 );
	if ( p_cDestino != NULL )
	{
		int iResult = _FrmCadena ( p_cDestino, "Entero=%d", 30, 1 );
		if ( iResult == 1 ) 
		{
			if ( strcmp ( p_cDestino, "Entero=1" ) != 0 ) 
			{
				printf( "Error caso 1: La cadena formateada no es la esperada: [%s]\n", p_cDestino );
				iRes = BOOL_VAL_FALSO;
			}
		}
		else
		{
			printf( "Error: Se esperada resultado 1 pero se ha recibido %d\n", iResult );
			iRes = BOOL_VAL_FALSO;
		} 
		CadInicializar ( p_cDestino, 30 );
		iResult = _FrmCadena ( p_cDestino, "Cadena=%s", 30, "Valor" );
		if ( iResult == 1 ) 
		{
			if ( strcmp ( p_cDestino, "Cadena=Valor" ) != 0 ) 
			{
			printf( "Error caso 2: La cadena formateada no es la esperada: [%s]\n", p_cDestino );
				iRes = BOOL_VAL_FALSO;
			}
		}
		else
		{
			printf( "Error: Se esperada resultado 1 pero se ha recibido %d\n", iResult );
			iRes = BOOL_VAL_FALSO;
		} 
		CadInicializar ( p_cDestino, 30 );
		iResult = _FrmCadena ( p_cDestino, "Real=%f", 30, 1.01 );
		if ( iResult == 1 ) 
		{
			if ( strcmp ( p_cDestino, "Real=1.010000" ) != 0 ) 
			{
			printf( "Error caso 3: La cadena formateada no es la esperada: [%s]\n", p_cDestino );
				iRes = BOOL_VAL_FALSO;
			}
		}
		else
		{
			printf( "Error: Se esperada resultado 1 pero se ha recibido %d\n", iResult );
			iRes = BOOL_VAL_FALSO;
		} 
		MemLiberar ( (void **) &p_cDestino );
	}
	else
	{
		printf( "Error: No se ha podido crear el objeto\n" );
		iRes = BOOL_VAL_FALSO;
	} 
	return ( iRes );
}

static int TestFrmCadena02 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test FrmCadena 02:\n" );
	char * p_cDestino = CadCrear ( 30 );
	if ( p_cDestino != NULL )
	{
		int iResult = _FrmCadena ( p_cDestino, "Cadena", 30 );
		if ( iResult == 1 ) 
		{
			if ( strcmp ( p_cDestino, "Cadena" ) != 0 ) 
			{
				printf( "Error caso 1: La cadena formateada no es la esperada: [%s]\n", p_cDestino );
				iRes = BOOL_VAL_FALSO;
			}
		}
		else
		{
			printf( "Error: Se esperada resultado 1 pero se ha recibido %d\n", iResult );
			iRes = BOOL_VAL_FALSO;
		} 
		MemLiberar ( (void **) &p_cDestino );
	}
	return ( iRes );
}

/*
 * Un %f de un double grande saca hasta 309 cifras enteras, y la comprobacion de
 * anchura de FrmCadena solo reserva 64 caracteres para el numero. Con "%.8000f" y
 * 1e308 la salida ( 8310 caracteres ) pasaba esa comprobacion y se escribia fuera
 * del buffer interno de 8192: el proceso abortaba por corrupcion del heap. Ahora
 * tiene que fallar como cuando no cabe la anchura, sin escribir nada.
 */
static int TestFrmCadena03 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test FrmCadena 03:\n" );
	char * p_cDestino = CadCrear ( 64 );
	if ( p_cDestino != NULL )
	{
		int iResult = _FrmCadena ( p_cDestino, "%.2f", 64, 1e20 );
		if ( iResult == 1 )
		{
			if ( strcmp ( p_cDestino, "100000000000000000000.00" ) != 0 )
			{
				printf( "Error caso 1: La cadena formateada no es la esperada: [%s]\n", p_cDestino );
				iRes = BOOL_VAL_FALSO;
			}
		}
		else
		{
			printf( "Error caso 1: Se esperada resultado 1 pero se ha recibido %d\n", iResult );
			iRes = BOOL_VAL_FALSO;
		}
		CadInicializar ( p_cDestino, 64 );
		iResult = _FrmCadena ( p_cDestino, "%.8000f", 64, 1e308 );
		if ( iResult == 0 )
		{
			if ( strcmp ( p_cDestino, "" ) != 0 )
			{
				printf( "Error caso 2: No se esperaba salida y se ha recibido: [%.60s]\n", p_cDestino );
				iRes = BOOL_VAL_FALSO;
			}
		}
		else
		{
			printf( "Error caso 2: Se esperada resultado 0 pero se ha recibido %d\n", iResult );
			iRes = BOOL_VAL_FALSO;
		}
		MemLiberar ( (void **) &p_cDestino );
	}
	return ( iRes );
}

int TestFormatoCadena ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test FormatoCadena]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestFrmCadena01 () == BOOL_VAL_CIERTO ) &&
			( TestFrmCadena02 () == BOOL_VAL_CIERTO ) &&
			( TestFrmCadena03 () == BOOL_VAL_CIERTO ))
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
