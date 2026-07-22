#ifndef _ORG_GJS_C_CC_CPP_FECHAS_H
#define _ORG_GJS_C_CC_CPP_FECHAS_H



namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {








long FecFormConstruir ( int iA, int iM, int iD );

bool FecEsValida ( int iA, int iM, int iD );
bool FecFormEsValida ( long lFecha );

void FecFormDescomponer ( long lFecha, int * p_iA, int * p_iM, int * p_iD );
int FecFormAnos ( long lFecha );
int FecFormMeses ( long lFecha );
int FecFormDias ( long lFecha );

int FecNumDiasAnualesHasta ( int iA, int iM, int iD ); 
int FecNumDiasAnualesDesde ( int iA, int iM, int iD ); 
int FecFormNumDiasAnualesHasta ( long lFecha ); 
int FecFormNumDiasAnualesDesde ( long lFecha ); 

int FecSumar ( int * p_iA, int * p_iM, int * p_iD, int iA, int iM, int iD );
int FecRestar ( int * p_iA, int * p_iM, int * p_iD, int iA, int iM, int iD );
long FecFormSumar ( long lFecha1, long lFecha2 );
long FecFormRestar ( long lFecha1, long lFecha2 );

// En años:
bool FecValEsValido ( double dValor );
double FecObtenerValor ( int iA, int iM, int iD );
double FecFormObtenerValor ( long lFecha );
int FecEstablecerValor ( double dValor, int * p_iA, int * p_iM, int * p_iD ); 
long FecFormEstablecerValor ( double dValor );



 			}
		}
	}
}

#endif


