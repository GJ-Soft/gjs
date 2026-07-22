#include "Base.h"

#include "SCronometro.h"



static int TestSCronCiclo01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	SCronometro * p_cronObj;
	double dComputo;
	printf( "Test SCronCiclo 01:\n" );

	p_cronObj = SCronCrear ();
	if ( ES_NULO ( p_cronObj ) )
	{
		printf( "Error caso 0: no se pudo crear el cronometro\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		/* recien creado, el tiempo inicial es 0 */
		if ( p_cronObj->dTiempoIni != 0 )
		{
			printf( "Error caso 1: el tiempo inicial deberia ser 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* sin iniciar, el computo es 0 */
		if ( SCronComputo ( p_cronObj ) != 0 )
		{
			printf( "Error caso 2: el computo sin iniciar deberia ser 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* al iniciar, el tiempo inicial pasa a ser positivo */
		SCronIniciar ( p_cronObj );
		if ( p_cronObj->dTiempoIni <= 0 )
		{
			printf( "Error caso 3: tras iniciar el tiempo inicial deberia ser positivo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* el computo no puede ser negativo */
		dComputo = SCronComputo ( p_cronObj );
		if ( dComputo < 0 )
		{
			printf( "Error caso 4: el computo no deberia ser negativo: %f\n", dComputo );
			iRes = BOOL_VAL_FALSO;
		}
		/* al parar se devuelve el computo y se resetea el tiempo inicial */
		dComputo = SCronParar ( p_cronObj );
		if ( dComputo < 0 )
		{
			printf( "Error caso 5: el computo al parar no deberia ser negativo: %f\n", dComputo );
			iRes = BOOL_VAL_FALSO;
		}
		if ( p_cronObj->dTiempoIni != 0 )
		{
			printf( "Error caso 6: tras parar el tiempo inicial deberia ser 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	SCronDestruir ( (SCronometro **) &p_cronObj );
	if ( ES_VALIDO ( p_cronObj ) )
	{
		printf( "Error caso 7: tras destruir el puntero deberia ser nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}

	/* comportamiento defensivo con nulo */
	if ( SCronParar ( NULL ) != 0 )
	{
		printf( "Error caso 8: SCronParar de nulo deberia dar 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SCronComputo ( NULL ) != 0 )
	{
		printf( "Error caso 9: SCronComputo de nulo deberia dar 0\n" );
		iRes = BOOL_VAL_FALSO;
	}

	return ( iRes );
}



int TestSCronometro ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SCronometro]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSCronCiclo01 () == BOOL_VAL_CIERTO ) )
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
