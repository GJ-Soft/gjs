#ifndef _ORG_GJS_CC_CPP_BASE_REAL_H
#define _ORG_GJS_CC_CPP_BASE_REAL_H





namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {
				namespace real
				{
					
bool equals ( float fValor1, float fValor2, int iTolerancia = 4 );
bool equals ( double dValor1, double dValor2, int iTolerancia = 4 );
bool equals ( long double ldValor1, long double ldValor2, int iTolerancia = 4 );

bool equalsWithPrec ( float fValor1, float fValor2, int iDigitosSignificativos = 3 );
bool equalsWithPrec ( double dValor1, double dValor2, int iDigitosSignificativos = 3 );
bool equalsWithPrec ( long double ldValor1, long double ldValor2, int iDigitosSignificativos = 3 );

				}
 			}
		}
	}
}


#endif
