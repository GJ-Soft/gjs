#ifndef _ORG_GJS_C_CC_SCONVERSOR_H
#define _ORG_GJS_C_CC_SCONVERSOR_H



#include <BaseConfig.h>




typedef struct
{
	int				iValor;
	long			lValor;
	unsigned int	uiValor;
	unsigned long	ulValor;
	float			fValor;
	double			dValor;
	char *			p_cValor;

	long long		llValor;
	unsigned long long	ullValor;

	int				iConvValida;
} SConversor;


SConversor * SConvCrearDef ();
SConversor * SConvCrearEntero ( int iValor );
SConversor * SConvCrearEnteroLargo ( long lValor );
SConversor * SConvCrearEnteroSinSigno ( unsigned int uiValor );
SConversor * SConvCrearEnteroLargoSinSigno ( unsigned long ulValor );
SConversor * SConvCrearReal ( float fValor );
SConversor * SConvCrearRealDoble ( double dValor );
SConversor * SConvCrearCadena ( char * p_cValor );
SConversor * SConvCrearCadenaConstante ( const char * p_cValor );
SConversor * SConvCrearEnteroDobleLargo ( long long llValor );
SConversor * SConvCrearEnteroDobleLargoSinSigno ( unsigned long long ullValor );

#   define SConvCrear(x) _Generic((x), \
        int : SConvCrearEntero, \
        long: SConvCrearEnteroLargo, \
        unsigned int: SConvCrearEnteroSinSigno, \
        unsigned long: SConvCrearEnteroLargoSinSigno, \
        float: SConvCrearReal, \
        double: SConvCrearRealDoble, \
        char *: SConvCrearCadena, \
        const char *: SConvCrearCadenaConstante, \
        long long: SConvCrearEnteroDobleLargo, \
        unsigned long long: SConvCrearEnteroDobleLargoSinSigno, \
        default: SConvCrearDef \
    )(x)


void SConvDestruir ( SConversor ** p_p_convObj );

int SConvEntero ( SConversor * p_convObj );
long SConvEnteroLargo ( SConversor * p_convObj );
unsigned int SConvEnteroSinSigno ( SConversor * p_convObj );
unsigned long SConvEnteroLargoSinSigno ( SConversor * p_convObj );
float SConvReal ( SConversor * p_convObj );
double SConvRealDoble ( SConversor * p_convObj );
const char * SConvCadena ( SConversor * p_convObj );
const char * SConvCadenaHex ( SConversor * p_convObj );
long long SConvEnteroDobleLargo ( SConversor * p_convObj );
unsigned long long SConvEnteroDobleLargoSinSigno ( SConversor * p_convObj );

void SConvEstablecerValorEntero (  SConversor * p_convObj, int iValor );
void SConvEstablecerValorEnteroLargo ( SConversor * p_convObj, long lValor );
void SConvEstablecerValorEnteroSinSigno ( SConversor * p_convObj, unsigned int uiValor );
void SConvEstablecerValorEnteroLargoSinSigno ( SConversor * p_convObj, unsigned long ulValor );
void SConvEstablecerValorReal ( SConversor * p_convObj, float fValor );
void SConvEstablecerValorRealDoble ( SConversor * p_convObj, double dValor );
void SConvEstablecerValorCadena ( SConversor * p_convObj, char * p_cValor );
void SConvEstablecerValorCadenaConstante ( SConversor * p_convObj, const char * p_cValor );
void SConvEstablecerValorCadenaHex ( SConversor * p_convObj, char * p_cValor );
void SConvEstablecerValorCadenaHexConstante ( SConversor * p_convObj, const char * p_cValor );
void SConvEstablecerValorEnteroDobleLargo ( SConversor * p_convObj, long long llValor );
void SConvEstablecerValorEnteroDobleLargoSinSigno ( SConversor * p_convObj, unsigned long long ullValor );

#   define SConvEstablecerValor(x, y) _Generic((x), \
        default: _Generic((y), \
            int : SConvEstablecerValorEntero, \
            long: SConvEstablecerValorEnteroLargo, \
            unsigned int: SConvEstablecerValorEnteroSinSigno, \
            unsigned long: SConvEstablecerValorEnteroLargoSinSigno, \
            float: SConvEstablecerValorReal, \
            double: SConvEstablecerValorRealDoble, \
            char *: SConvEstablecerValorCadena, \
            const char *: SConvEstablecerValorCadenaConstante, \
            long long: SConvEstablecerValorEnteroDobleLargo, \
            unsigned long long: SConvEstablecerValorEnteroDobleLargoSinSigno ) \
    )(x, y)



int SConvEsCadenaNumerica ( SConversor * p_convObj );
int SConvEsCadenaNumericaEntera ( SConversor * p_convObj );
int SConvEsCadenaNumericaReal ( SConversor * p_convObj );
int SConvEsCadenaNumericaHexadecimal ( SConversor * p_convObj );
int SConvConversionValida ( SConversor * p_convObj );


#endif
