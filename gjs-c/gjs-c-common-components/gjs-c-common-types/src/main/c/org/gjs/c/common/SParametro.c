

#include "SParametro.h"


#include "TiposDatosConfig.h"







SParametro * SParCrearDef () 
{
	SParametro * p_parObj;
	
	p_parObj = (SParametro *) MemReservar ( sizeof ( SParametro ) );
	if ( ES_VALIDO ( p_parObj ) )
	{
		p_parObj->p_valContenido = SValCrearDef ();
		if ( ES_VALIDO( p_parObj->p_valContenido ) )
		{
			p_parObj->p_cadNombre = NULL;
		}
		else
		{
			MemLiberar ( (void **) &p_parObj );
		}
	}
	return ( p_parObj );
}

SParametro * SParCrear ( int iTipo ) 
{
	SParametro * p_parObj;
	
	p_parObj = (SParametro *) MemReservar ( sizeof ( SParametro ) );
	if ( ES_VALIDO ( p_parObj ) )
	{
		p_parObj->p_valContenido = SValCrear ( iTipo );
		if ( ES_VALIDO( p_parObj->p_valContenido ) )
		{
			p_parObj->p_cadNombre = NULL;
		}
		else
		{
			MemLiberar ( (void **) &p_parObj );
		}
	}
	return ( p_parObj );
}

SParametro * SParCrearExt  ( int iTipo, SCadena * p_cadNombre )
{
	SParametro * p_parObj;
	
	p_parObj = (SParametro *) MemReservar ( sizeof ( SParametro ) );
	if ( ES_VALIDO ( p_parObj ) )
	{
		p_parObj->p_valContenido = SValCrear ( iTipo );
		if ( ES_VALIDO( p_parObj->p_valContenido ) )
		{
			p_parObj->p_cadNombre = NULL;
			SParEstablecerNombre ( p_parObj, p_cadNombre );
		}
		else
		{
			MemLiberar ( (void **) &p_parObj );
		}
	}
	return ( p_parObj );
}

SParametro * SParCrearExtLit  ( int iTipo, const char * p_cNombre )
{
	SParametro * p_parObj;
	
	p_parObj = (SParametro *) MemReservar ( sizeof ( SParametro ) );
	if ( ES_VALIDO ( p_parObj ) )
	{
		p_parObj->p_valContenido = SValCrear ( iTipo );
		if ( ES_VALIDO( p_parObj->p_valContenido ) )
		{
			p_parObj->p_cadNombre = NULL;
			SParEstablecerNombreLit ( p_parObj, p_cNombre );
		}
		else
		{
			MemLiberar ( (void **) &p_parObj );
		}
	}
	return ( p_parObj );
}

void SParDestruir ( SParametro ** p_p_parObj )
{
	SParametro * p_parObj;
	
	if ( ES_VALIDO ( p_p_parObj ) )
	{
		p_parObj = *p_p_parObj;
		if ( ES_VALIDO ( p_parObj ) )
		{
			SValDestruir ( &(p_parObj->p_valContenido) );
			SCadDestruir ( &(p_parObj->p_cadNombre) );
		}
		MemLiberar ( (void **) p_p_parObj );
	}
}

int SParTipo ( SParametro * p_parObj )
{
	int iRes;
	
	if ( ES_VALIDO ( p_parObj ) )
	{
		iRes = SValTipo ( p_parObj->p_valContenido );
	}
	else
	{
		iRes = TIP_NINGUNO;
	}
	return ( iRes );
}

SCadena * SParNombre ( SParametro * p_parObj )
{
	SCadena * p_cadRes;
	
	if ( ES_VALIDO ( p_parObj ) )
	{
		p_cadRes = p_parObj->p_cadNombre;
	}
	else
	{
		p_cadRes = NULL;
	}
	return ( p_cadRes );
}

SValor * SParValor ( SParametro * p_parObj )
{	
	SValor * p_valRes;
	
	if ( ES_VALIDO ( p_parObj ) )
	{
		p_valRes = p_parObj->p_valContenido;
	}
	else
	{
		p_valRes = NULL;
	}
	return ( p_valRes );
}

int SParEsValido ( SParametro * p_parObj )
{
	int iRes;
	
	if ( ES_VALIDO ( p_parObj ) )
	{
		if ( ( SCadLongitud ( p_parObj->p_cadNombre ) > 0 ) && ( SValEsValido ( p_parObj->p_valContenido ) == 1 ) )
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

int SParEstablecerNombre ( SParametro * p_parObj, SCadena * p_cadNombre )
{
	int iRes;
	
	if ( ES_VALIDO ( p_parObj ) )
	{
		SCadDestruir ( &(p_parObj->p_cadNombre) );
		if ( ES_VALIDO ( p_cadNombre ) )
		{
			p_parObj->p_cadNombre = SCadDuplicar ( p_cadNombre ); 
			SCadEliminarBlancos ( p_parObj->p_cadNombre );
		}
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SParEstablecerNombreLit ( SParametro * p_parObj, const char * p_cNombre )
{
	int iRes;
	
	if ( ES_VALIDO ( p_parObj ) )
	{
		SCadDestruir ( &(p_parObj->p_cadNombre) );
		if ( ES_VALIDO ( p_cNombre ) )
		{
			p_parObj->p_cadNombre = SCadGenerar ( p_cNombre  ); 
			SCadEliminarBlancos ( p_parObj->p_cadNombre );
		}
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SParEstablecerValor ( SParametro * p_parObj, SValor * p_valDato )
{
	int iRes;
	
	if ( ES_VALIDO ( p_parObj ) )
	{
		if ( SValTipo ( p_parObj->p_valContenido ) == SValTipo ( p_valDato ) )
		{
			SValAsignar ( p_parObj->p_valContenido, p_valDato ); 
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

int SParEstablecerValorExt (  SParametro * p_parObj, SCadena * p_cadValor )
{
	int iRes;
	
	if ( ES_VALIDO ( p_parObj ) )
	{
		SValEstablecerValorCadena ( p_parObj->p_valContenido, p_cadValor ); 
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SParEstablecerValorExtLit (  SParametro * p_parObj, const char * p_cValor )
{
	int iRes;
	
	if ( ES_VALIDO ( p_parObj ) )
	{
		SValEstablecerValorLiteral ( p_parObj->p_valContenido, p_cValor ); 
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

SParametro * SParDuplicar ( SParametro * p_parObj )
{
    SParametro * p_parRes;

	if ( ES_VALIDO ( p_parObj ) )
    {
		  p_parRes = SParCrearExt ( SParTipo ( p_parObj ), SParNombre ( p_parObj ) );
		  if ( ES_VALIDO ( p_parRes ) )
		  {
			  SParEstablecerValor ( p_parRes, SParValor ( p_parObj ) );
		  }
	}
	else
	{
		p_parRes = NULL;
	}
	return ( p_parRes );
}



