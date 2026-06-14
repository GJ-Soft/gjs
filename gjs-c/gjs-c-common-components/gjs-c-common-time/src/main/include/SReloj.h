#ifndef _ORG_GJS_C_CC_SRELOJ
#define _ORG_GJS_C_CC_SRELOJ






typedef struct
{
	double dDesplazamiento;

} SReloj;



SReloj * SRljCrearDef ();
SReloj * SRljCrear ( long lHora );
SReloj * SRljCrearHHMMSS ( int iHH, int iMI, int iSS );

void SRljDestruir ( SReloj ** p_p_rljObj );

long SRljHora ( SReloj * p_rljObj );
long SRljHH ( SReloj * p_rljObj );
long SRljMI ( SReloj * p_rljObj );
long SRljSS ( SReloj * p_rljObj );

void SRljEstablecer ( SReloj * p_rljObj, long lHora );
void SRljEstablecerHHMMSS ( SReloj * p_rljObj, int iHH, int iMI, int iSS );

void SRljSincronizarConSistema ( SReloj * p_rljObj );
void SRljSincronizarConSistemaExt ( SReloj * p_rljObj, long lHoraSis, long lHora );


#endif


