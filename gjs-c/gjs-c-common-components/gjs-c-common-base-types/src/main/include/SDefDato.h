#ifndef _ORG_GJS_C_CC_C_COMMON_SDEFDATO_H
#define _ORG_GJS_C_CC_C_COMMON_SDEFDATO_H








typedef struct
{
	int				iTipo;
	unsigned long	ulId;
	char *			p_cNombre;
	int				iReferencia;
	int				iTam;
	int				iDecimales;
	char *			p_cValorDef;

} SDefDato;




SDefDato * SDefDatCrear ( unsigned long	ulId, const char * p_cNombre, int iTipo, int iReferencia, int iTam, int iDecimales, const char * p_cValorDef );

void SDefDatDestruir ( SDefDato ** p_p_ddatObj );

int SDefDatEsValido ( SDefDato * p_ddatObj );

unsigned long SDefDatId ( SDefDato * p_ddatObj );
int SDefDatTipo ( SDefDato * p_ddatObj );
const char * SDefDatNombre ( SDefDato * p_ddatObj );
int SDefDatEsValor ( SDefDato * p_ddatObj );
int SDefDatEsReferencia ( SDefDato * p_ddatObj );
int SDefDatTam ( SDefDato * p_ddatObj );
int SDefDatDecimales ( SDefDato * p_ddatObj );
const char * SDefDatValorDefecto ( SDefDato * p_ddatObj );




#endif
