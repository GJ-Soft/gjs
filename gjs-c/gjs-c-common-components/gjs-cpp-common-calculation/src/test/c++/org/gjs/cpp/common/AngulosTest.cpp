#include <CppBase.h>

#include <iostream>


using namespace std;
using namespace org::gjs::cpp::common;



#include "Angulos.h"
#include "ConstantesMatematicas.h"
#include "CalculoOperaciones.h"



static bool TestAngRangos01 ()
{
	bool bRes = true;
	cout << "Test AngRangos 01:" << endl;

	/* Los angulos se expresan en grados. */
	if ( ! AngEntreCeroY2Pi ( 90.0 ) )
	{
		cout << "Error caso 1: 90 deberia estar en [0, 360)" << endl;
		bRes = false;
	}
	if ( AngEntreCeroY2Pi ( 400.0 ) )
	{
		cout << "Error caso 2: 400 no deberia estar en [0, 360)" << endl;
		bRes = false;
	}
	if ( ! AngEntreMenosPiYPi ( -100.0 ) )
	{
		cout << "Error caso 3: -100 deberia estar en [-180, 180]" << endl;
		bRes = false;
	}
	if ( AngEntreMenosPiYPi ( 200.0 ) )
	{
		cout << "Error caso 4: 200 no deberia estar en [-180, 180]" << endl;
		bRes = false;
	}
	if ( ! AngEntreCeroYPiMedios ( 45.0 ) )
	{
		cout << "Error caso 5: 45 deberia estar en [0, 90]" << endl;
		bRes = false;
	}
	if ( AngEntreCeroYPiMedios ( 100.0 ) )
	{
		cout << "Error caso 6: 100 no deberia estar en [0, 90]" << endl;
		bRes = false;
	}
	if ( ! AngEntreMenosPiMediosYPiMedios ( -45.0 ) )
	{
		cout << "Error caso 7: -45 deberia estar en [-90, 90]" << endl;
		bRes = false;
	}
	if ( AngEntreMenosPiMediosYPiMedios ( 120.0 ) )
	{
		cout << "Error caso 8: 120 no deberia estar en [-90, 90]" << endl;
		bRes = false;
	}
	return ( bRes );
}

static bool TestAngNormalizar01 ()
{
	bool bRes = true;
	cout << "Test AngNormalizar 01:" << endl;

	if ( ! MatEsIgual ( AngNormalizar ( 370.0, 0 ), 10.0 ) )
	{
		cout << "Error caso 1: 370 deberia normalizarse a 10: " << AngNormalizar ( 370.0, 0 ) << endl;
		bRes = false;
	}
	/* Sin negativos, -10 se lleva al rango [0, 360). */
	if ( ! MatEsIgual ( AngNormalizar ( -10.0, 0 ), 350.0 ) )
	{
		cout << "Error caso 2: -10 deberia normalizarse a 350: " << AngNormalizar ( -10.0, 0 ) << endl;
		bRes = false;
	}
	/* Con negativos permitidos, -10 se conserva. */
	if ( ! MatEsIgual ( AngNormalizar ( -10.0, 1 ), -10.0 ) )
	{
		cout << "Error caso 3: -10 deberia conservarse: " << AngNormalizar ( -10.0, 1 ) << endl;
		bRes = false;
	}
	/* Normalizar a media vuelta ( modulo 180 ). */
	if ( ! MatEsIgual ( AngNormalizarPi ( 190.0 ), 10.0 ) )
	{
		cout << "Error caso 4: 190 deberia normalizarse a 10 modulo 180: " << AngNormalizarPi ( 190.0 ) << endl;
		bRes = false;
	}
	/* Normalizar a cuarto de vuelta ( modulo 90 ). */
	if ( ! MatEsIgual ( AngNormalizarPiMedios ( 100.0 ), 10.0 ) )
	{
		cout << "Error caso 5: 100 deberia normalizarse a 10 modulo 90: " << AngNormalizarPiMedios ( 100.0 ) << endl;
		bRes = false;
	}
	return ( bRes );
}

static bool TestAngCuadrantes01 ()
{
	bool bRes = true;
	cout << "Test AngCuadrantes 01:" << endl;

	/* Numero de vueltas completas. */
	if ( AngNumeroVueltas ( 720.0 ) != 2 )
	{
		cout << "Error caso 1: 720 grados son 2 vueltas: " << AngNumeroVueltas ( 720.0 ) << endl;
		bRes = false;
	}
	if ( AngNumeroVueltas ( 90.0 ) != 0 )
	{
		cout << "Error caso 2: 90 grados son 0 vueltas: " << AngNumeroVueltas ( 90.0 ) << endl;
		bRes = false;
	}
	/* Truncamiento ( no redondeo ): 340 grados es 0 vueltas, no 1. */
	if ( AngNumeroVueltas ( 340.0 ) != 0 )
	{
		cout << "Error caso 3: 340 grados deberian ser 0 vueltas ( truncando ): " << AngNumeroVueltas ( 340.0 ) << endl;
		bRes = false;
	}
	/* Cuadrante estandar: Q1..Q4 -> 1..4 ( pasos de 90 grados ). */
	if ( AngCuadrante ( 45.0 ) != 1 )
	{
		cout << "Error caso 4: 45 grados estan en el cuadrante 1: " << AngCuadrante ( 45.0 ) << endl;
		bRes = false;
	}
	if ( AngCuadrante ( 135.0 ) != 2 )
	{
		cout << "Error caso 5: 135 grados estan en el cuadrante 2: " << AngCuadrante ( 135.0 ) << endl;
		bRes = false;
	}
	if ( AngCuadrante ( 225.0 ) != 3 )
	{
		cout << "Error caso 6: 225 grados estan en el cuadrante 3: " << AngCuadrante ( 225.0 ) << endl;
		bRes = false;
	}
	if ( AngCuadrante ( 315.0 ) != 4 )
	{
		cout << "Error caso 7: 315 grados estan en el cuadrante 4: " << AngCuadrante ( 315.0 ) << endl;
		bRes = false;
	}
	/* Se toma por truncamiento: 54 grados sigue en el primer cuadrante. */
	if ( AngCuadrante ( 54.0 ) != 1 )
	{
		cout << "Error caso 8: 54 grados siguen en el cuadrante 1 ( truncando ): " << AngCuadrante ( 54.0 ) << endl;
		bRes = false;
	}
	/* SemiplanoX ( respecto al eje X, signo de y ): [0,180) -> 1, [180,360) -> 2. */
	if ( AngSemiplanoX ( 45.0 ) != 1 )
	{
		cout << "Error caso 9: 45 grados ( y>0 ) estan en el semiplano X 1: " << AngSemiplanoX ( 45.0 ) << endl;
		bRes = false;
	}
	if ( AngSemiplanoX ( 225.0 ) != 2 )
	{
		cout << "Error caso 10: 225 grados ( y<0 ) estan en el semiplano X 2: " << AngSemiplanoX ( 225.0 ) << endl;
		bRes = false;
	}
	/* SemiplanoY ( respecto al eje Y, signo de x ): Q1 y Q4 -> 1, Q2 y Q3 -> 2. */
	if ( AngSemiplanoY ( 45.0 ) != 1 )
	{
		cout << "Error caso 11: 45 grados ( x>0 ) estan en el semiplano Y 1: " << AngSemiplanoY ( 45.0 ) << endl;
		bRes = false;
	}
	if ( AngSemiplanoY ( 135.0 ) != 2 )
	{
		cout << "Error caso 12: 135 grados ( x<0 ) estan en el semiplano Y 2: " << AngSemiplanoY ( 135.0 ) << endl;
		bRes = false;
	}
	/* La entrada se normaliza a [0, 360): vale fuera de rango y negativa. */
	if ( AngCuadrante ( 45.0 + 360.0 ) != 1 )
	{
		cout << "Error caso 13: 45 grados + una vuelta siguen en el cuadrante 1: " << AngCuadrante ( 45.0 + 360.0 ) << endl;
		bRes = false;
	}
	if ( AngCuadrante ( -45.0 ) != 4 )
	{
		cout << "Error caso 14: -45 grados estan en el cuadrante 4: " << AngCuadrante ( -45.0 ) << endl;
		bRes = false;
	}
	if ( AngCuadrante ( -315.0 ) != 1 )
	{
		cout << "Error caso 15: -315 grados equivalen a 45 ( cuadrante 1 ): " << AngCuadrante ( -315.0 ) << endl;
		bRes = false;
	}
	if ( AngSemiplanoX ( -45.0 ) != 2 )
	{
		cout << "Error caso 16: -45 grados ( y<0 ) estan en el semiplano X 2: " << AngSemiplanoX ( -45.0 ) << endl;
		bRes = false;
	}
	return ( bRes );
}

static bool TestAngConversion01 ()
{
	bool bRes = true;
	cout << "Test AngConversion 01:" << endl;

	if ( ! MatEsIgual ( AngObtenerRadianes ( 180.0 ), PI ) )
	{
		cout << "Error caso 1: 180 grados deberian ser PI radianes: " << AngObtenerRadianes ( 180.0 ) << endl;
		bRes = false;
	}
	if ( ! MatEsIgual ( AngObtenerRadianes ( 90.0 ), PI / 2.0 ) )
	{
		cout << "Error caso 2: 90 grados deberian ser PI/2 radianes: " << AngObtenerRadianes ( 90.0 ) << endl;
		bRes = false;
	}
	if ( ! MatEsIgual ( AngEstablecerRadianes ( PI ), 180.0 ) )
	{
		cout << "Error caso 3: PI radianes deberian ser 180 grados: " << AngEstablecerRadianes ( PI ) << endl;
		bRes = false;
	}
	return ( bRes );
}



bool TestAngulos ()
{
	bool bRes = true;
	cout  << ANSI::AMARILLO << "[Test Angulos]" << ANSI::RESETEAR << endl;
	if ( TestAngRangos01 () &&
			TestAngNormalizar01 () &&
			TestAngCuadrantes01 () &&
			TestAngConversion01 () )
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
