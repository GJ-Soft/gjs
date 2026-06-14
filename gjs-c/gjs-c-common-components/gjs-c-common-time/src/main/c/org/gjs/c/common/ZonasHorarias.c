#include "ZonasHorarias.h"
#include "TiempoConfig.h"



int ZnhEsValida ( int iZona )
{
	int iRes;

	if ( ( HusEsValido ( iZona ) == 1 ) ||
		 ( iZona == ZNH_NST	) ||
		 ( iZona == ZNH_ACST ) )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int ZnhId ( int iGrad, int iMin, int iSeg )
{
	int iHus;
	int iRes;

	iHus = HusId ( iGrad, iMin, iSeg );
	if ( HusEsValido ( iHus ) == 1 )
	{
		iRes = iHus;
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int ZnhIdAng ( double dAng )
{
	int iHus;
	int iRes;

	iHus = HusIdAng ( dAng );
	if ( HusEsValido ( iHus ) == 1 )
	{
		iRes = iHus;
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int ZnhHuso ( int iZona )
{
	int iRes;

	if ( ZnhEsValida ( iZona ) == 1 ) 
	{
		iRes = iZona % 100;
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int ZnhEsUTCMas ( int iZona )
{
	int iRes;

	iZona = iZona % 100;
	if ( ( iZona == ZNH_UTC ) ||			
		 ( iZona == ZNH_UTC_1) ||						
		 ( iZona == ZNH_UTC_2 ) ||				
		 ( iZona == ZNH_UTC_3 ) ||				
		 ( iZona == ZNH_UTC_4 ) ||				
		 ( iZona == ZNH_UTC_5 ) ||		
		 ( iZona == ZNH_UTC_6 ) ||		
		 ( iZona == ZNH_UTC_7 ) ||		
		 ( iZona == ZNH_UTC_8 ) ||		
		 ( iZona == ZNH_UTC_9 ) ||					
		 ( iZona == ZNH_UTC_10 ) ||					
		 ( iZona == ZNH_UTC_11 ) ||				
		 ( iZona == ZNH_UTC_12 ) )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int ZnhEsUTCMenos ( int iZona )
{
	int iRes;

	iZona = iZona % 100;
	if ( ( iZona == ZNH_UTC_M12 ) ||				
		 ( iZona == ZNH_UTC_M11 ) ||				
		 ( iZona == ZNH_UTC_M10 ) ||					
		 ( iZona == ZNH_UTC_M9 ) ||				
		 ( iZona == ZNH_UTC_M8 ) ||				
		 ( iZona == ZNH_UTC_M7 ) ||						
		 ( iZona == ZNH_UTC_M6 ) ||						
		 ( iZona == ZNH_UTC_M5 ) ||				
		 ( iZona == ZNH_UTC_M4 ) ||				
		 ( iZona == ZNH_UTC_M3 ) ||					
		 ( iZona == ZNH_UTC_M2 ) ||				
		 ( iZona == ZNH_UTC_M1 ) )			
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int ZnhDiferenciaHorasUTCExacta ( int iZona )
{
	int iRes;

	if ( ( iZona == ZNH_NST ) ||
		 ( iZona == ZNH_ACST ) )
	{
		iRes = 0;
	}
	else
	{
		iRes = 1;
	}
	return ( iRes );
}

int ZnhDiferenciaHorasUTC ( int iZona )
{
	int	iRes;

	iZona = iZona % 100;
	if ( iZona == ZNH_UTC )			
	{
		iRes = ZNH_DIF_UTC;
	}
	else if ( iZona == ZNH_UTC_1)						
	{
		iRes = ZNH_DIF_UTC_1;
	}
	else if ( iZona == ZNH_UTC_2 )				
	{
		iRes = ZNH_DIF_UTC_2;
	}
	else if ( iZona == ZNH_UTC_3 )				
	{
		iRes = ZNH_DIF_UTC_3;
	}
	else if ( iZona == ZNH_UTC_4 )				
	{
		iRes = ZNH_DIF_UTC_4;
	}
	else if ( iZona == ZNH_UTC_5 )		
	{
		iRes = ZNH_DIF_UTC_5;
	}
	else if ( iZona == ZNH_UTC_6 )		
	{
		iRes = ZNH_DIF_UTC_6;
	}
	else if ( iZona == ZNH_UTC_7 )		
	{
		iRes = ZNH_DIF_UTC_7;
	}
	else if ( iZona == ZNH_UTC_8 )		
	{
		iRes = ZNH_DIF_UTC_8;
	}
 	else if ( iZona == ZNH_UTC_9 )					
	{
		iRes = ZNH_DIF_UTC_9;
	}
 	else if ( iZona == ZNH_UTC_10 )					
	{
		iRes = ZNH_DIF_UTC_10;
	}
	else if ( iZona == ZNH_UTC_11 )				
	{
		iRes = ZNH_DIF_UTC_11;
	}
	else if ( iZona == ZNH_UTC_12 )
	{
		iRes = ZNH_DIF_UTC_12;
	}
	else if ( iZona == ZNH_UTC_M12 )				
	{
		iRes = ZNH_DIF_UTC_M12;
	}
	else if ( iZona == ZNH_UTC_M11 )				
	{
		iRes = ZNH_DIF_UTC_M11;
	}
	else if ( iZona == ZNH_UTC_M10 )					
	{
		iRes = ZNH_DIF_UTC_M10;
	}
	else if ( iZona == ZNH_UTC_M9 )				
	{
		iRes = ZNH_DIF_UTC_M9;
	}
	else if ( iZona == ZNH_UTC_M8 )				
	{
		iRes = ZNH_DIF_UTC_M8;
	}
	else if ( iZona == ZNH_UTC_M7 )						
	{
		iRes = ZNH_DIF_UTC_M7;
	}
	else if ( iZona == ZNH_UTC_M6 )						
	{
		iRes = ZNH_DIF_UTC_M6;
	}
	else if ( iZona == ZNH_UTC_M5 )				
	{
		iRes = ZNH_DIF_UTC_M5;
	}
	else if ( iZona == ZNH_UTC_M4 )				
	{
		iRes = ZNH_DIF_UTC_M4;
	}
	else if ( iZona == ZNH_UTC_M3 )					
	{
		iRes = ZNH_DIF_UTC_M3;
	}
	else if ( iZona == ZNH_UTC_M2 )				
	{
		iRes = ZNH_DIF_UTC_M2;
	}
	else if ( iZona == ZNH_UTC_M1 )			
	{
		iRes = ZNH_DIF_UTC_M1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int ZnhDiferenciaMinutosUTC ( int iZona )
{
	int	iRes;

	if ( ZnhEsValida ( iZona ) == 1 )
	{
		iRes = ZnhDiferenciaHorasUTC ( iZona ) * 60;
		if ( iZona == ZNH_NST ) 
		{
			iRes = iRes - 30;
		}
		else if ( iZona == ZNH_ACST )
		{
			iRes = iRes + 30;
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int ZnhDiferenciaHoras ( int iZona1, int iZona2 )
{
	int	iRes;

	iRes = ZnhDiferenciaHorasUTC ( iZona2 ) - ZnhDiferenciaHorasUTC ( iZona1 );
	return ( iRes );
}

int ZnhDiferenciaMinutos ( int iZona1, int iZona2 )
{
	int	iRes;

	iRes = ZnhDiferenciaMinutosUTC ( iZona2 ) - ZnhDiferenciaMinutosUTC ( iZona1 );
	return ( iRes );
}

