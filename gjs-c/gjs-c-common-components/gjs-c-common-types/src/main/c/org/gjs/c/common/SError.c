#include "SError.h"

#include "TiposDatosConfig.h"





SError * SErrCrear ( const char * p_cCodigo, const char * p_cDescripcion )
{
	SError *	p_errObj;
	
	p_errObj = (SError *) MemReservar ( sizeof ( SError ) );
	if ( ES_VALIDO ( p_errObj ) )
	{
		p_errObj->p_cCodigo = CadDuplicar ( p_cCodigo );
		p_errObj->p_cDescripcion = CadDuplicar ( p_cDescripcion );
		p_errObj->iAdvertencia = 0;
	}
	return ( p_errObj );
}

SError * SErrCrearAdvertencia ( const char * p_cCodigo, const char * p_cDescripcion )
{
	SError *	p_errObj;
	
	p_errObj = SErrCrear ( p_cCodigo, p_cDescripcion );
	if ( ES_VALIDO ( p_errObj ) )
	{
		p_errObj->iAdvertencia = 1;
	}
	return ( p_errObj );
}

SError * SErrCrearForm ( const char * p_cCodigo, const char * p_cFormato, ... )
{
 	SError *	p_errObj;
	char  *		p_cMensaje;
	va_list		valArgumentos;

	va_start ( valArgumentos, p_cFormato );
	p_cMensaje = CadCrearConFormatoExt ( p_cFormato, valArgumentos );
	p_errObj = SErrCrear ( p_cCodigo, p_cMensaje );
	MemLiberar ( (void **) &(p_cMensaje) );
	va_end ( valArgumentos );
	return ( p_errObj );
}

SError * SErrCrearAdvertenciaForm ( const char * p_cCodigo, const char * p_cFormato, ... )
{
 	SError *	p_errObj;
	char  *		p_cMensaje;
	va_list		valArgumentos;

	va_start ( valArgumentos, p_cFormato );
	p_cMensaje = CadCrearConFormatoExt ( p_cFormato, valArgumentos );
	p_errObj = SErrCrearAdvertencia ( p_cCodigo, p_cMensaje );
	MemLiberar ( (void **) &(p_cMensaje) );
	va_end ( valArgumentos );
	return ( p_errObj );
}

void SErrDestruir ( SError ** p_p_errObj )
{
	SError *	p_errObj;

	if ( ES_VALIDO ( p_p_errObj ) )
	{
		p_errObj = *p_p_errObj;
		if ( ES_VALIDO ( p_errObj ) )
		{
			MemLiberar ( (void **) &(p_errObj->p_cCodigo) );
			MemLiberar ( (void **) &(p_errObj->p_cDescripcion) );
			MemLiberar ( (void **) p_p_errObj );
		}
	}
}

const char * SErrCodigo ( SError * p_errObj )
{
	const char * p_cRes;

	if ( ES_VALIDO ( p_errObj ) )
	{
		p_cRes = (const char *) p_errObj->p_cCodigo;
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

const char * SErrDescripcion ( SError * p_errObj )
{
	const char * p_cRes;

	if ( ES_VALIDO ( p_errObj ) )
	{
		p_cRes = (const char *) p_errObj->p_cDescripcion;
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

int SErrEsAdvertencia ( SError * p_errObj )
{
	int iRes;

	if ( ES_VALIDO ( p_errObj ) )
	{
		if ( p_errObj->iAdvertencia == 1 ) 
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

int SErrEsValido ( SError * p_errObj )
{
	int iRes;

	if ( ES_VALIDO ( p_errObj ) )
	{
		if ( ( CadLongitud ( p_errObj->p_cCodigo ) > 0 ) &&
			( CadLongitud ( p_errObj->p_cDescripcion ) > 0 ) )	
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

SError * SErrClonar ( SError * p_errObj )
{
	SError *	p_errRes;
	
	if ( ES_VALIDO ( p_errObj ) )
	{
		p_errRes = SErrCrear ( SErrCodigo( p_errObj ), SErrDescripcion( p_errObj ) );
		if ( ES_VALIDO ( p_errRes ) )
		{
			p_errRes->iAdvertencia = SErrEsAdvertencia ( p_errObj );
		}
	}
	else
	{
		p_errRes = NULL;
	}
	return ( p_errRes );
}
