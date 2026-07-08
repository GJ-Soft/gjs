
#include "SEntradaDirectorio.h"


#include "FicherosConfig.h"



SEntradaDirectorio * SEntDirCrearFichero ( SCadena * p_cadEntrada )
{
	SEntradaDirectorio *	p_entdirObj;
	
	p_entdirObj = (SEntradaDirectorio *) MemReservar ( sizeof ( SEntradaDirectorio ) );
	if ( ES_VALIDO ( p_entdirObj ) )
	{
		p_entdirObj->p_cadEntrada = SCadDuplicar ( p_cadEntrada );
		p_entdirObj->iDirectorio = 0;
	}
	return ( p_entdirObj );
}

SEntradaDirectorio * SEntDirCrearFicheroLit ( const char * p_cEntrada )
{
	SEntradaDirectorio *	p_entdirObj;
	
	p_entdirObj = (SEntradaDirectorio *) MemReservar ( sizeof ( SEntradaDirectorio ) );
	if ( ES_VALIDO ( p_entdirObj ) )
	{
		p_entdirObj->p_cadEntrada = SCadGenerar ( p_cEntrada );
		p_entdirObj->iDirectorio = 0;
	}
	return ( p_entdirObj );
}

SEntradaDirectorio * SEntDirCrearDirectorio ( SCadena * p_cadEntrada )
{
	SEntradaDirectorio *	p_entdirObj;
	
	p_entdirObj = (SEntradaDirectorio *) MemReservar ( sizeof ( SEntradaDirectorio ) );
	if ( ES_VALIDO ( p_entdirObj ) )
	{
		p_entdirObj->p_cadEntrada = SCadDuplicar ( p_cadEntrada );
		p_entdirObj->iDirectorio = 1;
	}
	return ( p_entdirObj );
}

SEntradaDirectorio * SEntDirCrearDirectorioLit ( const char * p_cEntrada )
{
	SEntradaDirectorio *	p_entdirObj;
	
	p_entdirObj = (SEntradaDirectorio *) MemReservar ( sizeof ( SEntradaDirectorio ) );
	if ( ES_VALIDO ( p_entdirObj ) )
	{
		p_entdirObj->p_cadEntrada = SCadGenerar ( p_cEntrada );
		p_entdirObj->iDirectorio = 1;
	}
	return ( p_entdirObj );
}


void SEntDirDestruir ( SEntradaDirectorio ** p_p_entdirObj )
{
	SEntradaDirectorio * p_entdirObj;
	
	if ( ES_VALIDO ( p_p_entdirObj ) )
	{
		p_entdirObj = *p_p_entdirObj;
		if ( ES_VALIDO ( p_entdirObj ) )
		{
			SCadDestruir ( &(p_entdirObj->p_cadEntrada) );
			MemLiberar ( (void **) p_p_entdirObj );
		}
	}
}

SCadena * SEntDirEntrada ( SEntradaDirectorio * p_entdirObj )
{
	SCadena *	p_cadRes;
	
	if ( ES_VALIDO ( p_entdirObj ) )
	{
		p_cadRes = p_entdirObj->p_cadEntrada;
	}
	else
	{
		p_cadRes = NULL;
	}
	return ( p_cadRes );
}

const char * SEntDirEntradaLit ( SEntradaDirectorio * p_entdirObj )
{
	const char * p_cRes;
	
	if ( ES_VALIDO ( p_entdirObj ) )
	{
		p_cRes = SCadValorConstante ( p_entdirObj->p_cadEntrada );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

int SEntDirEsValida ( SEntradaDirectorio * p_entdirObj )
{
	int iRes;
	
	if ( ES_VALIDO ( p_entdirObj ) )
	{
		if ( SCadLongitud ( p_entdirObj->p_cadEntrada ) > 0 )
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

int SEntDirEsDirectorio ( SEntradaDirectorio * p_entdirObj )
{
	int iRes;
	
	if ( ES_VALIDO ( p_entdirObj ) )
	{
		iRes = p_entdirObj->iDirectorio;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SEntDirEsFichero ( SEntradaDirectorio * p_entdirObj )
{
	int iRes;
	
	if ( ES_VALIDO ( p_entdirObj ) )
	{
		if ( p_entdirObj->iDirectorio == 0 )
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




