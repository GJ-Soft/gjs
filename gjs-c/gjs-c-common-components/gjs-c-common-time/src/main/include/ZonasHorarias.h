#ifndef _ORG_GJS_C_CC_ZONASHORARIAS_H
#define _ORG_GJS_C_CC_ZONASHORARIAS_H




#include <HusosHorarios.h>





#define ZNH_NINGUNA					GEO_HUS_NINGUNO

#define ZNH_UTC						GEO_HUS_0				
#define ZNH_UTC_1					GEO_HUS_15					
#define ZNH_UTC_2					GEO_HUS_30				
#define ZNH_UTC_3					GEO_HUS_45					
#define ZNH_UTC_4					GEO_HUS_60					
#define ZNH_UTC_5					GEO_HUS_75					
#define ZNH_UTC_6					GEO_HUS_90				
#define ZNH_UTC_7					GEO_HUS_105					
#define ZNH_UTC_8					GEO_HUS_120				
#define ZNH_UTC_9					GEO_HUS_135					
#define ZNH_UTC_10					GEO_HUS_150					
#define ZNH_UTC_11					GEO_HUS_165					
#define ZNH_UTC_12					GEO_HUS_180					
#define ZNH_UTC_M12					GEO_HUS_195					
#define ZNH_UTC_M11					GEO_HUS_210					
#define ZNH_UTC_M10					GEO_HUS_225					
#define ZNH_UTC_M9					GEO_HUS_240					
#define ZNH_UTC_M8					GEO_HUS_255					
#define ZNH_UTC_M7					GEO_HUS_270						
#define ZNH_UTC_M6					GEO_HUS_285						
#define ZNH_UTC_M5					GEO_HUS_300					
#define ZNH_UTC_M4					GEO_HUS_315					
#define ZNH_UTC_M3					GEO_HUS_330					
#define ZNH_UTC_M2					GEO_HUS_345					
#define ZNH_UTC_M1					GEO_HUS_360					



// Zonas especiales:
#define ZNH_WET						ZNH_UTC			// Hora de Europa Occidental (N) 
#define ZNH_CET						ZNH_UTC_1		// Hora Central Europea (N)  
#define ZNH_EET						ZNH_UTC_2		// Hora de Europa Oriental (N) 
#define ZNH_CEST					ZNH_UTC_2		// Hora de verano de Europa Central (N) 

#define ZNH_HST						ZNH_UTC_M10		// Hora estándar de Hawai y Aleutianas 
#define ZNH_AKST					ZNH_UTC_M9		// Alaska Standard Time: Tiempo Estándar de Alaska (N) 
#define ZNH_HDT						ZNH_UTC_M9		// Hora de verano de las Aleutianas (N) 
#define ZNH_PST						ZNH_UTC_M8		// Pacific Standard Time: Tiempo Estándar del Pacífico (N) 
#define ZNH_NW						ZNH_UTC_M8		// Tiempo de la Zona Noroeste (N) 
#define ZNH_AKDT					ZNH_UTC_M8		// Hora de verano de Alaska (N) 
#define ZNH_MST						ZNH_UTC_M7		// Mountain Standard Time: Hora Estándar de la Montaña (N) 
#define ZNH_PAC						ZNH_UTC_M7		// Tiempo de la Zona Pacífico (N) 
#define ZNH_PDT						ZNH_UTC_M7		// Hora de verano del Pacífico (N) / Hora de verano del Noroeste (N) 
#define ZNH_CST						ZNH_UTC_M6		// Central Standard Time: Tiempo Estándar del Centro (N) 
#define ZNH_CEN						ZNH_UTC_M6		// Tiempo de la Zona Centro (N) 
#define ZNH_MDT						ZNH_UTC_M6		// Hora de verano de las Montañas (N) / Hora de verano del Pacífico (N) 
#define ZNH_SP						ZNH_UTC_M5		// Hora Estándar del Pacífico (S) 
#define ZNH_EST						ZNH_UTC_M5		// East Standard Time: Tiempo Estándar del Este (N) 
#define ZNH_CDT						ZNH_UTC_M5		// Hora de verano de Centro (N) / Hora de verano del Centro (N) 
#define ZNH_AST						ZNH_UTC_M4		// Hora estándar del Atlántico (N) 
#define ZNH_EDT						ZNH_UTC_M4		// Hora de verano del Este (N) 
  
#define ZNH_NST						(100+ZNH_UTC_M3)// Hora estándar de Labrador (UTC-3:30)

#define ZNH_MSK						ZNH_UTC_3		// Hora de Moscú (N) 
#define ZNH_AWST					ZNH_UTC_8		// Hora estándar de Australia Occidental 
#define ZNH_JST						ZNH_UTC_9		// Hora estándar de Japón 
#define ZNH_ACST					(100+ZNH_UTC_9)	// Hora estándar de Australia Central (UTC+9:30) 
#define ZNH_AEST					ZNH_UTC_10		// Hora estándar del Este de Australia 



#define ZNH_DIF_UTC					0				
#define ZNH_DIF_UTC_1				1					
#define ZNH_DIF_UTC_2				2				
#define ZNH_DIF_UTC_3				3					
#define ZNH_DIF_UTC_4				4					
#define ZNH_DIF_UTC_5				5					
#define ZNH_DIF_UTC_6				6				
#define ZNH_DIF_UTC_7				7					
#define ZNH_DIF_UTC_8				8				
#define ZNH_DIF_UTC_9				9					
#define ZNH_DIF_UTC_10				10					
#define ZNH_DIF_UTC_11				11					
#define ZNH_DIF_UTC_12				12					
#define ZNH_DIF_UTC_M12				-12					
#define ZNH_DIF_UTC_M11				-11					
#define ZNH_DIF_UTC_M10				-10					
#define ZNH_DIF_UTC_M9				-9					
#define ZNH_DIF_UTC_M8				-8					
#define ZNH_DIF_UTC_M7				-7						
#define ZNH_DIF_UTC_M6				-6						
#define ZNH_DIF_UTC_M5				-5					
#define ZNH_DIF_UTC_M4				-4					
#define ZNH_DIF_UTC_M3				-2					
#define ZNH_DIF_UTC_M2				-2					
#define ZNH_DIF_UTC_M1				-1					



int ZnhEsValida ( int iZona );
int ZnhId ( int iGrad, int iMin, int iSeg );
int ZnhIdAng ( double dAng );
int ZnhHuso ( int iZona );
int ZnhEsUTCMas ( int iZona );
int ZnhEsUTCMenos ( int iZona );
int ZnhDiferenciaHorasUTCExacta ( int iZona );
int ZnhDiferenciaHorasUTC ( int iZona );
int ZnhDiferenciaMinutosUTC ( int iZona );
int ZnhDiferenciaHoras ( int iZona1, int iZona2 );
int ZnhDiferenciaMinutos ( int iZona1, int iZona2 );


#endif
