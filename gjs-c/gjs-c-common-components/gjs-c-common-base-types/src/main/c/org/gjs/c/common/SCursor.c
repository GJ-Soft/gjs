#include "SCursor.h"



#include "TiposBasicosConfig.h"




SCursor * SCurCrear ( int iLinea, int iColumna )
{
	SCursor * p_curObj;
	
	p_curObj = (SCursor *) MemReservar ( sizeof ( SCursor ) );
	if ( ES_VALIDO ( p_curObj ) )
	{
		p_curObj->iLinea = iLinea;
		p_curObj->iColumna = iColumna;
	}
	return ( p_curObj );
}

void SCurDestruir ( SCursor ** p_p_curObj )
{
	SCursor * p_curObj;
	
	if ( ES_VALIDO ( p_p_curObj ) )
	{
		p_curObj = *p_p_curObj;

		if ( ES_VALIDO ( p_curObj ) )
		{
			MemLiberar ( (void **) p_p_curObj );
		}
	}
}

int SCurLinea ( SCursor * p_curObj )
{
	int iRes;

	if ( ES_VALIDO ( p_curObj ) )
	{
		iRes = p_curObj->iLinea;
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int SCurColumna ( SCursor * p_curObj )
{
	int iRes;

	if ( ES_VALIDO ( p_curObj ) )
	{
		iRes = p_curObj->iColumna;
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int SCurEsValido ( SCursor * p_curObj )
{
	int iRes;

	if ( ES_VALIDO ( p_curObj ) )
	{
		if ( ( p_curObj->iLinea >= 0 ) && ( p_curObj->iColumna >= 0 ) )
		{
			iRes = 1;
		}
		else
		{
			iRes = 0;
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCurEstablecer ( SCursor * p_curObj, int iLinea, int iColumna )
{
	int iRes;

	if ( ES_VALIDO ( p_curObj ) )
	{
		p_curObj->iLinea = iLinea;
		p_curObj->iColumna = iColumna;
		iRes = SCurEsValido ( p_curObj );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCurEstablecerLinea ( SCursor * p_curObj, int iLinea )
{
	int iRes;

	if ( ES_VALIDO ( p_curObj ) )
	{
		p_curObj->iLinea = iLinea;
		iRes = SCurEsValido ( p_curObj );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCurEstablecerColumna ( SCursor * p_curObj, int iColumna )
{
	int iRes;

	if ( ES_VALIDO ( p_curObj ) )
	{
		p_curObj->iColumna = iColumna;
		iRes = SCurEsValido ( p_curObj );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCurAsignar ( SCursor * p_curObj, SCursor * p_curVal )
{
	int iRes;

	if ( ES_VALIDO ( p_curObj ) && ES_VALIDO ( p_curVal ) )
	{
		iRes = SCurEstablecer ( p_curObj, SCurLinea ( p_curVal ), SCurColumna ( p_curVal ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCurEsIgual ( SCursor * p_curObj, SCursor * p_curVal  )
{
	int iRes;

	if ( ES_VALIDO ( p_curObj ) && ES_VALIDO ( p_curVal ) )
	{
		iRes = SCurEsIgualExt ( p_curObj, SCurLinea ( p_curVal ), SCurColumna ( p_curVal ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCurEsMenor ( SCursor * p_curObj, SCursor * p_curVal  )
{
	int iRes;

	if ( ES_VALIDO ( p_curObj ) && ES_VALIDO ( p_curVal ) )
	{
		iRes = SCurEsMenorExt ( p_curObj, SCurLinea ( p_curVal ), SCurColumna ( p_curVal ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCurEsMayor ( SCursor * p_curObj, SCursor * p_curVal  )
{
	int iRes;

	if ( ES_VALIDO ( p_curObj ) && ES_VALIDO ( p_curVal ) )
	{
		iRes = SCurEsMayorExt ( p_curObj, SCurLinea ( p_curVal ), SCurColumna ( p_curVal ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCurEsIgualExt ( SCursor * p_curObj, int iLinea, int iColumna )
{
	int iRes;

	if ( ES_VALIDO ( p_curObj ) )
	{
		if ( ( p_curObj->iLinea == iLinea )  && 
			 ( p_curObj->iColumna == iColumna ) )
		{
			iRes = 1;
		}
		else
		{
			iRes = 0;
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCurEsMenorExt ( SCursor * p_curObj, int iLinea, int iColumna )
{
	int		iRes;

	if ( ES_VALIDO ( p_curObj ) )
	{
		if ( ( p_curObj->iLinea < iLinea ) ||  
			 ( ( p_curObj->iLinea == iLinea ) && ( p_curObj->iColumna < iColumna ) ) )
		{
			iRes = 1;
		}
		else
		{
			iRes = 0;
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SCurEsMayorExt ( SCursor * p_curObj, int iLinea, int iColumna )
{
	int		iRes;

	if ( ES_VALIDO ( p_curObj ) )
	{
		if ( ( p_curObj->iLinea > iLinea ) ||  
			 ( ( p_curObj->iLinea == iLinea ) && ( p_curObj->iColumna > iColumna ) ) )
		{
			iRes = 1;
		}
		else
		{
			iRes = 0;
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

SCursor * SCurDuplicar ( SCursor * p_curObj )
{
	SCursor * p_curRes;

	if ( ES_VALIDO ( p_curObj ) )
	{
		p_curRes = SCurCrear ( p_curObj->iLinea, p_curObj->iColumna );
	}
	else
	{
		p_curRes = NULL;
	}
	return ( p_curRes );
}

