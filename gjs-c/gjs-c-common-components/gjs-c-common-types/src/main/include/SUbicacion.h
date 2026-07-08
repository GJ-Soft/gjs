
#ifndef _ORG_GJS_C_CC_SUBICACION_H
#define _ORG_GJS_C_CC_SUBICACION_H












typedef struct 
{
    long	lPos;
	long	lTam;
	
} SUbicacion;



SUbicacion * SUbcCrearDef ();
SUbicacion * SUbcCrear ( long lPos, long lTam );

void SUbcDestruir ( SUbicacion ** p_p_ubcObj );

long SUbcPos ( SUbicacion * p_ubcObj );
long SUbcTam ( SUbicacion * p_ubcObj );

void SUbcEstablecer ( SUbicacion * p_ubcObj, long lPos, long lTam );
void SUbcEstablecerPos ( SUbicacion * p_ubcObj, long lPos );
void SUbcEstablecerTam ( SUbicacion * p_ubcObj, long lTam );

int SUbcDesplazar ( SUbicacion * p_ubcObj, long lDesp );

int SUbcEsValida ( SUbicacion * p_ubcObj );




#endif







