#ifndef _ORG_GJS_C_CC_FECHAS_H
#define _ORG_GJS_C_CC_FECHAS_H









long FecFormConstruir ( int iA, int iM, int iD );

int FecEsValida ( int iA, int iM, int iD );
int FecFormEsValida ( long lFecha );

void FecFormDescomponer ( long lFecha, int * p_iA, int * p_iM, int * p_iD );
int FecFormAnos ( long lFecha );
int FecFormMeses ( long lFecha );
int FecFormDias ( long lFecha );

int FecNumDiasAnualesHasta ( int iA, int iM, int iD ); 
int FecNumDiasAnualesDesde ( int iA, int iM, int iD ); 
int FecFormNumDiasAnualesHasta ( long lFecha ); 
int FecFormNumDiasAnualesDesde ( long lFecha ); 

int FecDiferencia ( int iA1, int iM1, int iD1, int iA2, int iM2, int iD2 );
int FecFormDiferencia (  long lFecha1, long lFecha2 );

int FecSumar ( int * p_iA, int * p_iM, int * p_iD, int iA, int iM, int iD );
int FecRestar ( int * p_iA, int * p_iM, int * p_iD, int iA, int iM, int iD );
int FecSumarDias ( int * p_iA, int * p_iM, int * p_iD, int iD );
int FecRestarDias ( int * p_iA, int * p_iM, int * p_iD, int iD );
int FecSumarMeses ( int * p_iA, int * p_iM, int * p_iD, int iM );
int FecRestarMeses ( int * p_iA, int * p_iM, int * p_iD, int iM );
int FecSumarAnos ( int * p_iA, int * p_iM, int * p_iD, int iA );
int FecRestarAnos ( int * p_iA, int * p_iM, int * p_iD, int iA );
long FecFormSumar ( long lFecha, int iA, int iM, int iD );
long FecFormRestar ( long lFecha, int iA, int iM, int iD );
long FecFormSumarDias ( long lFecha, int iD );
long FecFormRestarDias ( long lFecha, int iD );
long FecFormSumarMeses ( long lFecha, int iM );
long FecFormRestarMeses ( long lFecha, int iM );
long FecFormSumarAnos ( long lFecha, int iA );
long FecFormRestarAnos ( long lFecha, int iA );

int FecEsIgual ( int iA1, int iM1, int iD1, int iA2, int iM2, int iD2 );
int FecFormEsIgual ( long lFecha1, long lFecha2 );
int FecEsMenor ( int iA1, int iM1, int iD1, int iA2, int iM2, int iD2 );
int FecFormEsMenor ( long lFecha1, long lFecha2 );
int FecEsMayor ( int iA1, int iM1, int iD1, int iA2, int iM2, int iD2 );
int FecFormEsMayor ( long lFecha1, long lFecha2 );
int FecEsMenorIgual ( int iA1, int iM1, int iD1, int iA2, int iM2, int iD2 );
int FecFormEsMenorIgual ( long lFecha1, long lFecha2 );
int FecEsMayorIgual ( int iA1, int iM1, int iD1, int iA2, int iM2, int iD2 );
int FecFormEsMayorIgual ( long lFecha1, long lFecha2 );


// En años:
int FecValEsValido ( double dValor );
double FecObtenerValor ( int iA, int iM, int iD );
double FecFormObtenerValor ( long lFecha );
int FecEstablecerValor ( double dValor, int * p_iA, int * p_iM, int * p_iD ); 
long FecFormEstablecerValor ( double dValor );

#endif


