
#ifndef _ORG_GJS_C_CC_SRELOJPROGRAMABLE
#define _ORG_GJS_C_CC_SRELOJPROGRAMABLE



#include <Funciones.h>
#include <SReloj.h>
#include <SistemaProcesos.h>




typedef struct  
{
	SReloj *		p_rljObj;		
	long			lHoraAlarma;
	PPRCV			fAlarma;
	thread 			thTID;
	void *			p_vParams;
	int				iAlarma;
	volatile int	iParar;
	
} SRelojProgramable;


SRelojProgramable * SRljPrgCrear ( long lHora );
SRelojProgramable * SRljPrgCrearExt ( long lHora, long lHoraAlarma, PPRCV fAlarma );

void SRljPrgDestruir ( SRelojProgramable ** p_p_rljprgObj );

long SRljPrgHoraAlarma ( SRelojProgramable * p_rljprgObj );
PPRCV SRljPrgProcedimientoAlarma ( SRelojProgramable * p_rljprgObj );
void SRljPrgEstablecerAlarma (  SRelojProgramable * p_rljprgObj, long lHora, PPRCV fAlarma );

int SRljPrgAlarmaActivada ( SRelojProgramable * p_rljprgObj );
int SRljPrgActivarAlarma ( SRelojProgramable * p_rljprgObj );
void SRljPrgDesactivarAlarma ( SRelojProgramable * p_rljprgObj );






#endif

