#include "SFicEstructura.h"

#include "FicherosConfig.h"



#define TAM_CABECERA_FIC		sizeof ( unsigned long )




static int SFicEstCargar ( SFicEstructura * p_ficObj );
static int SFicEstGuardar ( SFicEstructura * p_ficObj ); 





SFicEstructura * SFicEstCrear ( const char * p_cRuta, int iTamElemento )
{
	SFicEstructura *	p_ficObj;
	
	if ( ( iTamElemento > 0 ) && ( SisEsRutaValida ( p_cRuta ) == 1 ) )
	{
		SisEliminarFichero ( p_cRuta );
		p_ficObj = (SFicEstructura *) MemReservar ( sizeof ( SFicEstructura ) );
		if ( ES_VALIDO ( p_ficObj ) )
		{	
			p_ficObj->p_ficDatos = SFicBloqCrear ( p_cRuta, iTamElemento, 0 );
			p_ficObj->p_blqBufDatos = SBlqCrear ( iTamElemento );
			if ( ( SFicBloqEsValido ( p_ficObj->p_ficDatos ) == 1 ) && ( SBlqEsValido ( p_ficObj->p_blqBufDatos ) == 1 )  )
			{
				if ( SFicBloqAbrir ( p_ficObj->p_ficDatos ) == 1 )
				{
					if ( SFicBloqEstablecerNumeroMagico ( p_ficObj->p_ficDatos, FIC_ESTR_NUM_MAG  ) == 1 )
					{
						if ( SFicEstGuardar ( p_ficObj ) == 1 )
						{
							SFicBloqCerrar ( p_ficObj->p_ficDatos );
						}
						else
						{
							SFicEstDestruir ( &p_ficObj );
						}
					}
					else
					{
						SFicEstDestruir ( &p_ficObj );
					}
				}
				else
				{
					SFicEstDestruir ( &p_ficObj );
				}
			}
			else
			{
				SFicEstDestruir ( &p_ficObj );
			}
		}
	}
	else
	{
		p_ficObj = NULL;
	}
	return ( p_ficObj );
}

SFicEstructura * SFicEstAbrir ( const char * p_cRuta )
{
	SFicEstructura *	p_ficObj;
	
	if ( SisExisteFichero ( p_cRuta ) == 1 )
	{
		p_ficObj = (SFicEstructura *) MemReservar ( sizeof ( SFicEstructura ) );
		if ( ES_VALIDO ( p_ficObj ) )
		{	
			p_ficObj->p_ficDatos = SFicBloqAsignar ( p_cRuta );
			if ( SFicBloqEsValido ( p_ficObj->p_ficDatos ) == 1 )
			{
				p_ficObj->p_blqBufDatos = SBlqCrear ( SFicBloqTamBloque ( p_ficObj->p_ficDatos ) );
				if ( SBlqEsValido ( p_ficObj->p_blqBufDatos ) == 1 )
				{
					if ( SFicBloqAbrir ( p_ficObj->p_ficDatos ) == 1 )
					{
						if ( SFicBloqNumeroMagico ( p_ficObj->p_ficDatos ) == FIC_ESTR_NUM_MAG ) 
						{
							if ( SFicEstCargar ( p_ficObj ) == 1 )
							{
								SFicBloqCerrar ( p_ficObj->p_ficDatos );
							}
							else
							{
								SFicEstDestruir ( &p_ficObj );
							}
						}
						else
						{
							SFicEstDestruir ( &p_ficObj );
						}
					}
					else
					{
						SFicEstDestruir ( &p_ficObj );
					}
				}
				else
				{
					SFicEstDestruir ( &p_ficObj );
				}
			}
			else
			{
				SFicEstDestruir ( &p_ficObj );
			}
		}
	}
	else
	{
		p_ficObj = NULL;
	}
	return ( p_ficObj );
}

SFicEstructura * SFicEstCrearExt ( const char * p_cDir, const char * p_cFic, int iTamElemento )
{
	SFicEstructura *	p_ficObj;
	char *				p_cRuta;

	if ( ES_VALIDO ( p_cDir ) && ES_VALIDO ( p_cFic ) )
	{
		p_cRuta = SisComponerRuta ( p_cDir, p_cFic, 0 );
		p_ficObj = SFicEstCrear ( p_cRuta, iTamElemento );
		MemLiberar ( (void **) &p_cRuta );
	}
	else
	{
		p_ficObj = NULL;
	}
	return ( p_ficObj );
}

SFicEstructura * SFicEstAbrirExt ( const char * p_cDir, const char * p_cFic, int * p_iTamElemento )
{
	SFicEstructura *	p_ficObj;
	char *				p_cRuta;

	if ( ES_VALIDO ( p_cDir ) && ES_VALIDO ( p_cFic ) )
	{
		p_cRuta = SisComponerRuta ( p_cDir, p_cFic, 0 );
		p_ficObj = SFicEstAbrir ( p_cRuta );
		if ( ES_VALIDO ( p_ficObj ) )
		{
			if ( ES_VALIDO ( p_iTamElemento ) )
			{
				*p_iTamElemento = SFicBloqTamBloque ( p_ficObj->p_ficDatos );
			}
		}
		MemLiberar ( (void **) &p_cRuta );
	}
	else
	{
		p_ficObj = NULL;
	}
	return ( p_ficObj );
}

SFicEstructura * SFicEstAbrirOCrear ( const char * p_cRuta, int iTamElemento )
{
	SFicEstructura * p_ficObj;
	
	if ( SisExisteFichero ( p_cRuta ) == 1 )
	{
		p_ficObj = SFicEstAbrir ( p_cRuta );
	}
	else
	{
		p_ficObj = SFicEstCrear ( p_cRuta, iTamElemento );
	}
	return ( p_ficObj );
}

SFicEstructura * SFicEstAbrirOCrearExt ( const char * p_cDir, const char * p_cFic, int * p_iTamElemento )
{
	SFicEstructura *	p_ficObj;
	char *				p_cRuta;

	if ( ES_VALIDO ( p_cDir ) && ES_VALIDO ( p_cFic ) )
	{
		p_cRuta = SisComponerRuta ( p_cDir, p_cFic, 0 );
		if ( SisExisteFichero ( p_cRuta ) == 1 )
		{
			p_ficObj = SFicEstAbrirExt ( p_cDir, p_cFic, p_iTamElemento );
		}
		else if ( ES_VALIDO ( p_iTamElemento ) )
		{
			p_ficObj = SFicEstCrearExt ( p_cDir, p_cFic, *p_iTamElemento );
		}
		else
		{
			p_ficObj = NULL;
		}
		MemLiberar ( (void **) &p_cRuta );
	}
	else
	{
		p_ficObj = NULL;
	}
	return ( p_ficObj );
}

SFicEstructura * SFicEstCrearRuta ( SRuta * p_rutRuta, int iTamElemento )
{
	SFicEstructura *	p_ficObj;
	char *				p_cRuta;
	
	if ( SRutEsValida ( p_rutRuta ) == 1 )
	{
		if ( SRutEsFichero ( p_rutRuta ) == 1 )
		{
			p_cRuta = SRutRutaAbsolutaLit ( p_rutRuta );
			if ( SRutExiste ( p_rutRuta ) == 1 )
			{
				p_ficObj = SFicEstAbrir ( p_cRuta );
			}
			else
			{
				p_ficObj = SFicEstCrear ( p_cRuta, iTamElemento );
			}
			MemLiberar ( (void **) &p_cRuta );
		}
		else
		{
			p_ficObj = NULL;
		}
	}
	else
	{
		p_ficObj = NULL;
	}
	return ( p_ficObj );
}

void SFicEstDestruir ( SFicEstructura ** p_p_ficObj )
{
	SFicEstructura *	p_ficObj;
	if ( ES_VALIDO ( p_p_ficObj ) )
	{
		p_ficObj = *p_p_ficObj;

		if ( ES_VALIDO ( p_ficObj ) )
		{
			SBlqDestruir ( &(p_ficObj->p_blqBufDatos) );
			SFicBloqCerrar ( p_ficObj->p_ficDatos );
			SFicBloqDestruir ( &(p_ficObj->p_ficDatos) );
			MemLiberar ( (void **) p_p_ficObj );
		}
	}
}

void SFicEstEliminar ( SFicEstructura ** p_p_ficObj )
{
	SFicEstructura *	p_ficObj;

	if ( ES_VALIDO ( p_p_ficObj ) )
	{
		p_ficObj = *p_p_ficObj;

		if ( ES_VALIDO ( p_ficObj ) )
		{
			SFicBloqCerrar ( p_ficObj->p_ficDatos );
			SFicBloqEliminar ( &(p_ficObj->p_ficDatos) ); 
			SFicEstDestruir ( p_p_ficObj );
		}
	}
}

int SFicEstEsValido ( SFicEstructura * p_ficObj )
{
	int iRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		iRes = SFicBloqEsValido ( p_ficObj->p_ficDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

const char * SFicEstRuta ( SFicEstructura * p_ficObj )
{
	const char * p_cRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		p_cRes = SFicBloqRuta ( p_ficObj->p_ficDatos );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

char * SFicEstDirectorio ( SFicEstructura * p_ficObj ) 
{
	char * p_cRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		p_cRes = SFicBloqDirectorio ( p_ficObj->p_ficDatos );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

char * SFicEstFichero ( SFicEstructura * p_ficObj ) 
{
	char * p_cRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		p_cRes = SFicBloqFichero ( p_ficObj->p_ficDatos );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

int SFicEstEstablecerRuta ( SFicEstructura * p_ficObj, const char * p_cRuta )
{
	int iRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		iRes = SFicBloqEstablecerRuta ( p_ficObj->p_ficDatos, p_cRuta );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SFicEstEstablecerRutaExt ( SFicEstructura * p_ficObj, const char * p_cDir, const char * p_cFic )
{
	int iRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		iRes = SFicBloqEstablecerRutaExt ( p_ficObj->p_ficDatos, p_cDir, p_cFic );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

SBloque * SFicEstContenido ( SFicEstructura * p_ficObj )
{
	SBloque *	p_blqRes;

	if ( SFicEstEsValido ( p_ficObj ) == 1 )
	{
		p_blqRes = p_ficObj->p_blqBufDatos;
	}
	else
	{
		p_blqRes = NULL;
	}
	return ( p_blqRes );
}

int SFicEstAsignar ( SFicEstructura * p_ficObj, SBloque * p_blqObj )
{
	int	iRes;

	if ( SFicEstEsValido ( p_ficObj ) == 1 )
	{
		SBlqCopiar ( p_ficObj->p_blqBufDatos, p_blqObj );
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SFicEstGuardarCambios ( SFicEstructura * p_ficObj )
{
	int	iRes;

	if ( SFicEstEsValido ( p_ficObj ) == 1 )
	{
		if ( SFicBloqAbrirExt ( p_ficObj->p_ficDatos, 0 ) == 1 )
		{
			iRes = SFicEstGuardar ( p_ficObj );
			SFicBloqCerrar ( p_ficObj->p_ficDatos);
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

int SFicEstLimpiar ( SFicEstructura * p_ficObj )
{
	int	iRes;
	
	if ( SFicEstEsValido ( p_ficObj ) == 1 )
	{
		SBlqLimpiar ( p_ficObj->p_blqBufDatos );
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

static int SFicEstCargar ( SFicEstructura * p_ficObj )
{
	int			iRes;
	byte *		p_byBuffer;

	p_byBuffer = SBlqDatos ( p_ficObj->p_blqBufDatos );
	if ( ES_VALIDO ( p_byBuffer ) )
	{
		if ( SFicBloqLeerExt ( p_ficObj->p_ficDatos, 0, p_byBuffer ) == 1 )
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

static int SFicEstGuardar ( SFicEstructura * p_ficObj )
{
	int			iRes;
	byte *		p_byBuffer;

	p_byBuffer = SBlqDatos ( p_ficObj->p_blqBufDatos );
	if ( ES_VALIDO ( p_byBuffer ) )
	{
		if ( SFicBloqEscribir ( p_ficObj->p_ficDatos, 0, p_byBuffer ) == 1 )
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

