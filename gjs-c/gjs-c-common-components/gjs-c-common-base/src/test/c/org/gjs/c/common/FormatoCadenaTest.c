#include "Base.h"

#include "FormatoCadena.h"

va_list _ObtenerArgumentos ( const char * p_cFormato, ... )
{
	va_list		valArgumentos;

	va_start ( valArgumentos,  p_cFormato );
	return ( valArgumentos );
}



static int TestFrmCadena01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test FrmCadena 01:\n" );
	char * p_cDestino = CadCrear ( 30 );
	if ( p_cDestino != NULL )
	{
		va_list	valArgumentos = _ObtenerArgumentos ( "Entero=%d", 1 );
		int iResult = FrmCadena ( p_cDestino, "Entero=%d", valArgumentos, 30 );
		va_end ( valArgumentos );
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
		valArgumentos = _ObtenerArgumentos ( "Cadena=%s", "Valor" );
		iResult = FrmCadena ( p_cDestino, "Cadena=%s", valArgumentos, 30 );
		va_end ( valArgumentos );
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
		valArgumentos = _ObtenerArgumentos ( "Real=%f", 1.01 );
		iResult = FrmCadena ( p_cDestino, "Real=%f", valArgumentos, 30 );
		va_end ( valArgumentos );
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
		va_list	valArgumentos = _ObtenerArgumentos ( "Cadena" );
		int iResult = FrmCadena ( p_cDestino, "Cadena", valArgumentos, 30 );
		va_end ( valArgumentos );
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

int TestFormatoCadena ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test FormatoCadena]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestFrmCadena01 () == BOOL_VAL_CIERTO ) &&
			( TestFrmCadena02 () == BOOL_VAL_CIERTO ))
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
