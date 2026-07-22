#include <CppBase.h>

#include <iostream>


using namespace std;
using namespace org::gjs::cpp::common;


#include "Gradianes.h"
#include "ConstantesMatematicas.h"
#include "CalculoOperaciones.h"



static bool TestGradValido01 ()
{
	bool bRes = true;
	cout << "Test GradValido 01:" << endl;

	if ( ! GradEsValido ( 45, 30, 0 ) )
	{
		cout << "Error caso 1: 45o 30' 0'' deberia ser valido" << endl;
		bRes = false;
	}
	/* Los minutos deben estar en [0, 60). */
	if ( GradEsValido ( 45, 70, 0 ) )
	{
		cout << "Error caso 2: 70 minutos no deberian ser validos" << endl;
		bRes = false;
	}
	/* Los segundos deben estar en [0, 60). */
	if ( GradEsValido ( 45, 0, 70 ) )
	{
		cout << "Error caso 3: 70 segundos no deberian ser validos" << endl;
		bRes = false;
	}
	/* Rango [0, 360): el grado tambien cuenta aqui. */
	if ( ! GradEntreCeroY2Pi ( 45, 30, 0 ) )
	{
		cout << "Error caso 4: 45o 30' deberia estar en [0, 360)" << endl;
		bRes = false;
	}
	if ( GradEntreCeroY2Pi ( 400, 0, 0 ) )
	{
		cout << "Error caso 5: 400o no deberia estar en [0, 360)" << endl;
		bRes = false;
	}
	/* Rango [-180, 180]: los extremos solo valen con 0' 0''. */
	if ( ! GradEntreMenosPiYPi ( 45, 0, 0 ) )
	{
		cout << "Error caso 6: 45o deberia estar en [-180, 180]" << endl;
		bRes = false;
	}
	if ( ! GradEntreMenosPiYPi ( 180, 0, 0 ) )
	{
		cout << "Error caso 7: 180o 0' 0'' deberia estar en [-180, 180]" << endl;
		bRes = false;
	}
	if ( GradEntreMenosPiYPi ( 200, 0, 0 ) )
	{
		cout << "Error caso 8: 200o no deberia estar en [-180, 180]" << endl;
		bRes = false;
	}
	return ( bRes );
}

static bool TestGradConversion01 ()
{
	bool bRes = true;
	int	iGrad;
	int	iMin;
	int	iSeg;
	cout << "Test GradConversion 01:" << endl;

	if ( ! MatEsIgual ( GradObtenerAngulo ( 90, 0, 0 ), 90.0 ) )
	{
		cout << "Error caso 1: 90o deberian ser 90 grados decimales: " << GradObtenerAngulo ( 90, 0, 0 ) << endl;
		bRes = false;
	}
	/* 30 minutos son medio grado. */
	if ( ! MatEsIgual ( GradObtenerAngulo ( 0, 30, 0 ), 0.5 ) )
	{
		cout << "Error caso 2: 30' deberian ser 0.5 grados: " << GradObtenerAngulo ( 0, 30, 0 ) << endl;
		bRes = false;
	}
	if ( ! MatEsIgual ( GradObtenerRadianes ( 180, 0, 0 ), PI ) )
	{
		cout << "Error caso 3: 180o deberian ser PI radianes: " << GradObtenerRadianes ( 180, 0, 0 ) << endl;
		bRes = false;
	}
	/* Establecer desde un angulo decimal: 45.5o -> 45o 30' 0''. */
	iGrad = 0;
	iMin = 0;
	iSeg = 0;
	if ( ! GradEstablecerAngulo ( 45.5, &iGrad, &iMin, &iSeg ) )
	{
		cout << "Error caso 4: establecer 45.5 grados deberia devolver cierto" << endl;
		bRes = false;
	}
	if ( ( iGrad != 45 ) || ( iMin != 30 ) || ( iSeg != 0 ) )
	{
		cout << "Error caso 5: 45.5 grados deberian ser 45/30/0: " << iGrad << "/" << iMin << "/" << iSeg << endl;
		bRes = false;
	}
	/* Defensivo: punteros nulos devuelven falso. */
	if ( GradEstablecerAngulo ( 45.5, NULL, &iMin, &iSeg ) )
	{
		cout << "Error caso 6: establecer con puntero nulo deberia devolver falso" << endl;
		bRes = false;
	}
	/* Establecer desde radianes: PI -> aprox 180o ( con perdida por la resolucion de segundos ). */
	iGrad = 0;
	iMin = 0;
	iSeg = 0;
	if ( ! GradEstablecerRadianes ( PI, &iGrad, &iMin, &iSeg ) )
	{
		cout << "Error caso 7: establecer PI radianes deberia devolver cierto" << endl;
		bRes = false;
	}
	if ( ! GradEsValido ( iGrad, iMin, iSeg ) )
	{
		cout << "Error caso 8: el resultado de establecer radianes deberia ser valido" << endl;
		bRes = false;
	}
	if ( MatRealAbsoluto ( GradObtenerAngulo ( iGrad, iMin, iSeg ) - 180.0 ) > 0.01 )
	{
		cout << "Error caso 9: PI radianes deberian ser aprox 180o: " << GradObtenerAngulo ( iGrad, iMin, iSeg ) << endl;
		bRes = false;
	}
	/* Los segundos se redondean con acarreo: un residuo de 59.8'' redondea a 60''
	   y debe arrastrar +1 al minuto, dando 0o 1' 0'' ( triple valido ), no (0,0,60). */
	iGrad = 0;
	iMin = 0;
	iSeg = 0;
	if ( ! GradEstablecerAngulo ( 59.8 / 3600.0, &iGrad, &iMin, &iSeg ) )
	{
		cout << "Error caso 10: establecer 59.8'' deberia devolver cierto" << endl;
		bRes = false;
	}
	if ( ( iGrad != 0 ) || ( iMin != 1 ) || ( iSeg != 0 ) )
	{
		cout << "Error caso 11: 59.8'' deberian redondear con acarreo a 0/1/0: " << iGrad << "/" << iMin << "/" << iSeg << endl;
		bRes = false;
	}
	if ( ! GradEsValido ( iGrad, iMin, iSeg ) )
	{
		cout << "Error caso 12: el triple resultante deberia ser valido: " << iGrad << "/" << iMin << "/" << iSeg << endl;
		bRes = false;
	}
	return ( bRes );
}

static bool TestGradValor01 ()
{
	bool bRes = true;
	cout << "Test GradValor 01:" << endl;

	if ( GradObtenerValor ( 45, 30, 15 ) != 453015 )
	{
		cout << "Error caso 1: se esperaba 453015: " << GradObtenerValor ( 45, 30, 15 ) << endl;
		bRes = false;
	}
	int iGrad = 0;
	int iMin = 0;
	int iSeg = 0;
	if ( ! GradEstablecerValor ( 453015, &iGrad, &iMin, &iSeg ) )
	{
		cout << "Error caso 2: se esperaba resultado cierto al establecer el valor" << endl;
		bRes = false;
	}
	if ( ( iGrad != 45 ) || ( iMin != 30 ) || ( iSeg != 15 ) )
	{
		cout << "Error caso 3: se esperaba 45/30/15: " << iGrad << "/" << iMin << "/" << iSeg << endl;
		bRes = false;
	}
	return ( bRes );
}

static bool TestGradAritmetica01 ()
{
	bool bRes = true;
	int	iGrad;
	int	iMin;
	int	iSeg;
	cout << "Test GradAritmetica 01:" << endl;

	/* Suma con acarreo de minutos: 45o 45' + 0o 20' = 46o 5'. */
	iGrad = 45;
	iMin = 45;
	iSeg = 0;
	if ( ! GradSumar ( &iGrad, &iMin, &iSeg, 0, 20, 0 ) )
	{
		cout << "Error caso 1: la suma deberia devolver cierto" << endl;
		bRes = false;
	}
	if ( ( iGrad != 46 ) || ( iMin != 5 ) || ( iSeg != 0 ) )
	{
		cout << "Error caso 2: 45o45' + 20' deberian ser 46o5': " << iGrad << "/" << iMin << "/" << iSeg << endl;
		bRes = false;
	}
	/* La resta es la operacion inversa: 46o 5' - 0o 20' = 45o 45'. */
	if ( ! GradRestar ( &iGrad, &iMin, &iSeg, 0, 20, 0 ) )
	{
		cout << "Error caso 3: la resta deberia devolver cierto" << endl;
		bRes = false;
	}
	if ( ( iGrad != 45 ) || ( iMin != 45 ) || ( iSeg != 0 ) )
	{
		cout << "Error caso 4: 46o5' - 20' deberian ser 45o45': " << iGrad << "/" << iMin << "/" << iSeg << endl;
		bRes = false;
	}
	/* Sumar sobre un valor invalido devuelve falso. */
	iGrad = 45;
	iMin = 70;
	iSeg = 0;
	if ( GradSumar ( &iGrad, &iMin, &iSeg, 0, 10, 0 ) )
	{
		cout << "Error caso 5: sumar sobre un valor invalido deberia devolver falso" << endl;
		bRes = false;
	}
	/* Normalizar 370o al rango [0, 360) da 10o. */
	iGrad = 370;
	iMin = 0;
	iSeg = 0;
	if ( ! GradNormalizar ( &iGrad, &iMin, &iSeg ) )
	{
		cout << "Error caso 6: normalizar deberia devolver cierto" << endl;
		bRes = false;
	}
	if ( ( iGrad != 10 ) || ( iMin != 0 ) || ( iSeg != 0 ) )
	{
		cout << "Error caso 7: 370o deberian normalizarse a 10o: " << iGrad << "/" << iMin << "/" << iSeg << endl;
		bRes = false;
	}
	/* Defensivo: punteros nulos devuelven falso. */
	if ( GradNormalizar ( NULL, &iMin, &iSeg ) )
	{
		cout << "Error caso 8: normalizar con puntero nulo deberia devolver falso" << endl;
		bRes = false;
	}
	return ( bRes );
}



bool TestGradianes ()
{
	bool bRes = true;
	cout  << ANSI::AMARILLO << "[Test Gradianes]" << ANSI::RESETEAR << endl;
	if ( TestGradValido01 () &&
			TestGradConversion01 () &&
			TestGradValor01 () &&
			TestGradAritmetica01 () )
	{
		cout << ANSI::VERDE << "Resultado: OK" << ANSI::RESETEAR << endl;
	}
	else
	{
		cout  << ANSI::ROJO <<  "Resultado: KO" << ANSI::RESETEAR << endl;
		bRes = false;
	}
	cout << ANSI::AMARILLO << "[Fin]" << ANSI::RESETEAR << endl;
	return ( bRes );
}
