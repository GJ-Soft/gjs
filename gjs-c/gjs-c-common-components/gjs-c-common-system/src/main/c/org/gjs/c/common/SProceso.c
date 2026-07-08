
#include "SProceso.h"

#include "SistemaConfig.h"





void _SPrcInicializar ( SProceso * p_prcObj );



SProceso * SPrcCrear ()
{
	SProceso * p_prcObj;
	
	p_prcObj = (SProceso *) MemReservar ( sizeof ( SProceso ) );
	if ( ES_VALIDO ( p_prcObj ) )
	{
		_SPrcInicializar ( p_prcObj );
	}
	return ( p_prcObj );
}

void SPrcDestruir ( SProceso ** p_p_prcObj )
{
	SProceso * p_prcObj;
	
	if ( ES_VALIDO ( p_p_prcObj ) )
	{
		p_prcObj = *p_p_prcObj;
		if ( ES_VALIDO ( p_prcObj ) )
		{
			MemLiberar ( (void **) p_p_prcObj );
		}
	}
}



long SPrcPID ( SProceso * p_prcObj )
{
	long lRes;

	if ( ES_VALIDO ( p_prcObj ) )
	{
		lRes = p_prcObj->lPID;
	}
	else
	{
		lRes = -1;
	}
	return ( lRes );
}

void _SPrcInicializar ( SProceso * p_prcObj )
{
	if ( ES_VALIDO ( p_prcObj ) )
	{
# if ( defined ( WIN ) )
		p_prcObj->lPID = (long) GetCurrentProcessId ();
# else
		p_prcObj->lPID = (long) getpid ();
# endif
	}
}






