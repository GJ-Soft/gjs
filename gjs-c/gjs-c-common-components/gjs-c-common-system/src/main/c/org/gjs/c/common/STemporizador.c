
#include "STemporizador.h"

#include "SistemaConfig.h"





STemporizador * STmpCrear ( int iMiliSegs )
{
	STemporizador * p_tmpObj;
	
	p_tmpObj = (STemporizador *) MemReservar ( sizeof ( STemporizador ) );
	if ( ES_VALIDO ( p_tmpObj ) )
	{
		STmpEstablecerIntervalo ( p_tmpObj, iMiliSegs );
	}
	return ( p_tmpObj );
}

void STmpDestruir ( STemporizador ** p_p_tmpObj )
{
	STemporizador * p_tmpObj;
	
	if ( ES_VALIDO ( p_p_tmpObj ) )
	{
		p_tmpObj = *p_p_tmpObj;
		if ( ES_VALIDO ( p_tmpObj ) )
		{
			MemLiberar ( (void **) p_p_tmpObj );
		}
	}
}

int STmpIntervalo ( STemporizador * p_tmpObj )
{
	int iRes;
	
	if ( ES_VALIDO ( p_tmpObj ) )
	{
		iRes = p_tmpObj->iMiliSegs;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

void STmpEstablecerIntervalo (  STemporizador * p_tmpObj, int iMiliSegs )
{
	if ( ES_VALIDO ( p_tmpObj ) )
	{
		if ( iMiliSegs > 0 )
		{
			p_tmpObj->iMiliSegs = iMiliSegs;
		}
		else
		{
			p_tmpObj->iMiliSegs = 0;
		}
	}
}

void STmpEsperarDef ( STemporizador * p_tmpObj )
{
	if ( ES_VALIDO ( p_tmpObj ) )
	{
		if ( p_tmpObj->iMiliSegs > 0 )
		{
	#		if ( defined ( WIN ) )
				Sleep ( (DWORD) p_tmpObj->iMiliSegs );
	#		else
				usleep( p_tmpObj->iMiliSegs * 1000) ;
	#		endif
		}
	}
}

void STmpEsperar ( STemporizador * p_tmpObj, int iMiliSegs )
{
	if ( ES_VALIDO ( p_tmpObj ) )
	{
		STmpEstablecerIntervalo ( p_tmpObj, iMiliSegs );
		STmpEsperarDef ( p_tmpObj );
	}
}



 


