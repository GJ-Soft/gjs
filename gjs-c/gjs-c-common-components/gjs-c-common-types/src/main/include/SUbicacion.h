
#ifndef _ORG_GJS_C_CC_SUBICACION_H
#define _ORG_GJS_C_CC_SUBICACION_H












/* Marca de posicion sin establecer. Es el mayor unsigned long, asi que
   esa posicion concreta no se puede guardar. */
#define SUBC_SIN_POSICION		ULONG_MAX



typedef struct 
{
	unsigned long	ulPos;
	unsigned long	ulTam;
	
} SUbicacion;



SUbicacion * SUbcCrearDef ();
SUbicacion * SUbcCrear ( unsigned long ulPos, unsigned long ulTam );

void SUbcDestruir ( SUbicacion ** p_p_ubcObj );

unsigned long SUbcPos ( SUbicacion * p_ubcObj );
unsigned long SUbcTam ( SUbicacion * p_ubcObj );

void SUbcEstablecer ( SUbicacion * p_ubcObj, unsigned long ulPos, unsigned long ulTam );
void SUbcEstablecerPos ( SUbicacion * p_ubcObj, unsigned long ulPos );
void SUbcEstablecerTam ( SUbicacion * p_ubcObj, unsigned long ulTam );

int SUbcDesplazar ( SUbicacion * p_ubcObj, long lDesp );

int SUbcEsValida ( SUbicacion * p_ubcObj );




#endif







