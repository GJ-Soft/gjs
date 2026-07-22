/******************************************************************************/
/*                            CalculoOperaciones.h                            */
/*----------------------------------------------------------------------------*/
/* Librer�a:  Calculo                                                         */
/* Versi�n:   3.0.0                                                           */
/* Fecha:     25/03/2008                                                      */
/* Autor:     Gin�s Jim�nez S�nchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripci�n:                                                               */
/* Fichero de cabecera que contiene los prototipos de algunas rutinas         */
/* que implementan algunas funciones sencillas de c�lculo matem�tico.         */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#ifndef _ORG_GJS_C_CC_CALCULOOPERACIONES_H
#define _ORG_GJS_C_CC_CALCULOOPERACIONES_H




bool MatEnteroEsPar ( long lValor );
bool MatEnteroEsImpar ( long lValor );
long MatEnteroAbsoluto ( long lValor );
long MatEnteroSigno ( long lValor );
long MatModulo ( long lValor, long lModulo );

unsigned long MatFactorial ( unsigned long ulValor );

double MatRealAbsoluto ( double dValor );
double MatRealRedondear ( double dValor );
double MatRealSigno ( double dValor );
double MatRealNegar ( double dValor );
double MatRealInvertir ( double dValor );

double MatDividirRealDoble ( double dDividendo, double dDivisor, bool * p_bIndeterminacion );
float MatDividir ( float fDividendo, float fDivisor, bool * p_bIndeterminacion );
bool MatEsMaximoRealDoble ( double dValor );
bool MatEsMinimoRealDoble ( double dValor );
bool MatEsMaximo ( float fValor );
bool MatEsMinimo ( float fValor );

double MatMedia ( double dValor1, double dValor2 );

double MatExponecialNatural ( double dValor );
double MatExponencialConExponenteEntero ( double dBase, long lExponente );
double MatCuadrado ( double dValor ); 
double MatCubo ( double dValor ); 
double MatRaiz ( double dValor, double dRadical ); 
double MatRaizCubica ( double dValor ); 

double MatPendiente ( double dX, double dY );

double MatSumaCuadratica2D ( double dValor1, double dValor2 ); 
double MatSumaCuadratica3D ( double dValor1, double dValor2, double dValor3 ); 

double MatHipotenusa2D ( double dValor1, double dValor2 ); 
double MatHipotenusa3D ( double dValor1, double dValor2, double dValor3 ); 
double MatHipotenusaND ( int iDims, double * p_dValores );

// Trigonometricas:
double MatArcoTangente ( double dVal, int iCuadrante ); 
double MatArcoSeno ( double dVal, int iCuadrante ); 
double MatArcoCoseno ( double dVal, int iCuadrante ); 
double MatArcoTangenteExt ( double dNum, double dDen, int iEntreMenosPiyPi ); 

// Comparaciones de n�meros reales con precisi�n determinada:
double MatPresicion ();
void MatEstablecerPresicion ( double dPrecision );

bool MatEsIgual ( double dValor1, double dValor2 );
bool MatEsMenor ( double dValor1, double dValor2 );
bool MatEsMayor ( double dValor1, double dValor2 );
bool MatEsMenorIg ( double dValor1, double dValor2 );
bool MatEsMayorIg ( double dValor1, double dValor2 );


// Ecuaciones:
bool MatEc1GrdTieneSolucion ( double dA, double dB );
bool MatEc2GrdTieneSolucion ( double dA, double dB, double dC );
double MatEc1GrdSolucion ( double dA, double dB );
double MatEc2GrdSolucion1 ( double dA, double dB, double dC );
double MatEc2GrdSolucion2 ( double dA, double dB, double dC );
double MatEc2GrdSolucionMax ( double dA, double dB, double dC );
double MatEc2GrdSolucionMin ( double dA, double dB, double dC );

// Series:
double MatCalcularSumaSeriePotencias ( double dValor, int iTerminos );


//Esferas:
double MatRadioLatitudinalEsfera ( double dRadio, double dLatitud );
double MatDistanciaLongitudinalEsfera ( double dRadio, double dLat1, double dLat2 );
double MatDistanciaLatitudinalEsfera ( double dRadio, double dLat, double dLon1, double dLon2 );
double MatDistanciaSuperficieEsfera ( double dRadio, double dLon1, double dLat1, double dLon2, double dLat2 );
double MatHipotenusaSuperficieEsfera ( double dValor1, double dValor2 );
// Lado1 es el lado opuesto al angulo buscado, el 2 el lado siguiente en sentido contrario al de avance de las agujas del reloj:
double MatAnguloTrianguloSuperficieEsfera ( double dLado1, double dLado2, double dLado3 ); 

// Excentricidad y esferoidales:
bool MatExcentricidadEsValida ( double dValor );
double MatExcentricidad ( double dSemiEje1, double dSemiEje2 );
double MatExcentricidadCuadrada ( double dSemiEje1, double dSemiEje2 );
double MatRadioCurvaturaEsfereoidal ( double dSemiejeMayor, double dSemiejeMenor, double dLatitud );
double MatRadioCurvaturaEsfereoidalPerpendicular ( double dSemiejeMayor, double dSemiejeMenor, double dLatitud );
double MatArcoMeridional ( double dSemiejeMayor, double dSemiejeMenor, double dLatitud );


// Funciones exponenciales
double MatFuncionAproximacionNatural ( double dT, double dX );
double MatFuncionGaussiana ( double dA, double dB, double dC, double dX );
double MatFuncionGaussianaNormalizada ( double dB, double dC, double dX );
double MatFuncionGaussianaDoble ( double dA1, double dB1, double dC1, double dA2, double dB2, double dC2, double dX );
double MatFuncionGaussianaDobleNormalizada ( double dB1, double dC1, double dB2, double dC2, double dX );


// Funciones especiales
double MatFuncionErrorGauss ( double dX );
double MatFuncionDistribucionProbabilidadNormal ( double dX );

#endif

