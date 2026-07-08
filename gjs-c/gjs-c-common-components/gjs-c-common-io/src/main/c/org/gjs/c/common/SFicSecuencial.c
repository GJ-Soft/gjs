
#include "SFicSecuencial.h"

#include "FicherosConfig.h"



SFicSecuencial * SFicSecCrear ( const char * p_cRuta )
{
	SFicSecuencial * p_ficObj;
	
	p_ficObj= (SFicSecuencial *) MemReservar ( sizeof ( SFicSecuencial ) );
	if ( ES_VALIDO ( p_ficObj ) )
	{
		p_ficObj->iAbierto = 0;
		p_ficObj->iModo = -1;
		p_ficObj->p_cRuta = NULL;
		p_ficObj->p_fObj = NULL;

		SFicSecEstablecerRuta ( p_ficObj, p_cRuta );
	}
	else
	{
		p_ficObj = NULL;
	}
	return ( p_ficObj );
}

SFicSecuencial * SFicSecCrearExt ( const char * p_cDir, const char * p_cFic )
{
	SFicSecuencial * p_ficObj;
	
	p_ficObj= (SFicSecuencial *) MemReservar ( sizeof ( SFicSecuencial ) );
	if ( ES_VALIDO ( p_ficObj ) )
	{
		p_ficObj->iAbierto = 0;
		p_ficObj->iModo = -1;
		p_ficObj->p_cRuta = NULL;
		p_ficObj->p_fObj = NULL;

		SFicSecEstablecerRutaExt ( p_ficObj, p_cDir, p_cFic );
	}
	else
	{
		p_ficObj = NULL;
	}
	return ( p_ficObj );
}

SFicSecuencial * SFicSecCrearRuta ( SRuta * p_rutRuta )
{
	SFicSecuencial *	p_ficObj;
	char *			p_cRuta;
	
	if ( SRutEsValida ( p_rutRuta ) == 1 )
	{
		if ( SRutEsFichero ( p_rutRuta ) == 1 )
		{
			p_cRuta = SRutRutaAbsolutaLit ( p_rutRuta );
			p_ficObj = SFicSecCrear ( p_cRuta );
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

void SFicSecDestruir ( SFicSecuencial ** p_p_ficObj )
{
	SFicSecuencial * p_ficObj;
	
	if ( ES_VALIDO ( p_p_ficObj ) )
	{
		p_ficObj = *p_p_ficObj;

		if ( ES_VALIDO ( p_ficObj ) )
		{
			SFicSecCerrar ( p_ficObj );
			MemLiberar ( (void **) &(p_ficObj->p_cRuta) );
			MemLiberar ( (void **) p_p_ficObj );
		}
	}
}

void SFicSecEliminar ( SFicSecuencial ** p_p_ficObj )
{
	SFicSecuencial * p_ficObj;
	
	if ( ES_VALIDO ( p_p_ficObj ) )
	{
		p_ficObj = *p_p_ficObj;

		if ( ES_VALIDO ( p_ficObj ) )
		{
			SisEliminarFichero ( p_ficObj->p_cRuta );
			SFicSecDestruir ( p_p_ficObj );
		}
	}
}

int SFicSecEsValido ( SFicSecuencial * p_ficObj )
{
	int iRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		if ( ES_VALIDO ( p_ficObj->p_cRuta ) )
		{
			if ( p_ficObj->iAbierto == 1 )
			{
				if ( ES_VALIDO ( p_ficObj->p_fObj ) &&
					 ( ModAprEsValido ( p_ficObj->iModo ) == 1 ) && 
					 ( SisExisteFichero ( p_ficObj->p_cRuta ) == 1 ) )
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
				if ( SisEsRutaValida ( p_ficObj->p_cRuta ) == 1 )
				{
					iRes = 1;
				}
				else
				{
					iRes = 0;
				}
			}
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

const char * SFicSecRuta ( SFicSecuencial * p_ficObj )
{
	const char * p_cRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		p_cRes = (const char *)(p_ficObj->p_cRuta);
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

char * SFicSecDirectorio ( SFicSecuencial * p_ficObj )
{
	char * p_cRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		p_cRes = SisRutaDirectorio ( p_ficObj->p_cRuta );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

char * SFicSecFichero ( SFicSecuencial * p_ficObj )
{
	char * p_cRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		p_cRes = SisRutaFichero ( p_ficObj->p_cRuta );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

int SFicSecEstablecerRuta ( SFicSecuencial * p_ficObj, const char * p_cRuta )
{
	int iRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		if ( p_ficObj->iAbierto == 0 )
		{
			MemLiberar ( (void **) &(p_ficObj->p_cRuta) );
			p_ficObj->p_cRuta = CadDuplicar ( p_cRuta );
			if ( SisEsRutaValida ( p_ficObj->p_cRuta ) == 1 )
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
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SFicSecEstablecerRutaExt ( SFicSecuencial * p_ficObj, const char * p_cDir, const char * p_cFic )
{
	int iRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		if ( p_ficObj->iAbierto == 0 )
		{
			MemLiberar ( (void **) &(p_ficObj->p_cRuta) );
			p_ficObj->p_cRuta = SisComponerRuta ( p_cDir, p_cFic, 0 );
			if ( SisEsRutaValida ( p_ficObj->p_cRuta ) == 1 )
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
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}


int SFicSecAbrir ( SFicSecuencial * p_ficObj, int iModo )
{
	return ( SFicSecAbrirExt ( p_ficObj, iModo, 0 ) );
}

int SFicSecAbrirExt ( SFicSecuencial * p_ficObj, int iModo, int iVaciar )
{
	int iRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		if ( ( p_ficObj->iAbierto == 0 ) && ( ModAprEsValido ( iModo ) == 1 ) )
		{
			if ( iModo == MOD_APR_LECTURA )
			{
				if ( ( SisExisteFichero ( p_ficObj->p_cRuta ) == 1 ) && ( iVaciar == 0 ) )
				{
					p_ficObj->p_fObj = fopen ( p_ficObj->p_cRuta, "r" );

					if ( ES_VALIDO ( p_ficObj->p_fObj ) )
					{
						p_ficObj->iAbierto = 1;
						p_ficObj->iModo = iModo;
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
			}
			else
			{
				if ( iVaciar == 1 )
				{
					p_ficObj->p_fObj = fopen ( p_ficObj->p_cRuta, "w" );
				}
				else
				{
					p_ficObj->p_fObj = fopen ( p_ficObj->p_cRuta, "a" );
				}

				if ( ES_VALIDO ( p_ficObj->p_fObj ) )
				{
					p_ficObj->iAbierto = 1;
					p_ficObj->iModo = iModo;
					iRes = 1;
				}
				else
				{
					iRes = 0;
				}
			}
		}
		else
		{
			iRes = 1;
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SFicSecCerrar ( SFicSecuencial * p_ficObj )
{
	int iRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		if ( ( p_ficObj->iAbierto == 1 ) && ES_VALIDO ( p_ficObj->p_fObj ) )
		{
			if ( fclose ( p_ficObj->p_fObj ) == 0 )
			{
				p_ficObj->p_fObj = NULL;
				p_ficObj->iAbierto = 0;
				iRes = 1;
			}
			else
			{
				iRes = 0;
			}
		}
		else
		{
			p_ficObj->iAbierto = 0;
			iRes = 1;
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SFicSecEstaAbierto ( SFicSecuencial * p_ficObj )
{
	int iRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		if ( ( p_ficObj->iAbierto == 1 ) && ES_VALIDO ( p_ficObj->p_fObj ) )
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

int SFicSecModoApertura ( SFicSecuencial * p_ficObj )
{
	int iRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		if ( ( p_ficObj->iAbierto == 1 ) && ES_VALIDO ( p_ficObj->p_fObj ) )
		{
			iRes = p_ficObj->iModo;
		}
		else
		{
			iRes = MOD_APR_NINGUNO;
		}
	}
	else
	{
		iRes = MOD_APR_NINGUNO;
	}
	return ( iRes );
}

int SFicSecEstaAbiertoParaLectura ( SFicSecuencial * p_ficObj )
{
	int iRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		if ( ( p_ficObj->iAbierto == 1 ) && ES_VALIDO ( p_ficObj->p_fObj ) &&
			 ( p_ficObj->iModo == MOD_APR_LECTURA ) )
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

int SFicSecEstaAbiertoParaEscritura ( SFicSecuencial * p_ficObj )
{
	int iRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		if ( ( p_ficObj->iAbierto == 1 ) && ES_VALIDO ( p_ficObj->p_fObj ) &&
			 ( p_ficObj->iModo == MOD_APR_ESCRITURA ) )
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

int SFicSecEstaEnFinal ( SFicSecuencial * p_ficObj )
{
	int iRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		if ( ( p_ficObj->iAbierto == 1 ) && ES_VALIDO ( p_ficObj->p_fObj ) )
		{
			if ( p_ficObj->iModo == MOD_APR_ESCRITURA )
			{
				iRes = 1;
			}
			else
			{
				// NOTA: feof no retorna algo si no se ha hecho un intento de lectura previo
				if ( feof ( p_ficObj->p_fObj ) != 0 )
				{
					iRes = 1;
				}
				else
				{
					iRes = 0;
				}
			}
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


byte SFicSecLeer ( SFicSecuencial * p_ficObj )
{
	byte byRes;

	byRes = 0x00;
	if ( ES_VALIDO ( p_ficObj ) )
	{
		if ( ( p_ficObj->iAbierto == 1 ) && ES_VALIDO ( p_ficObj->p_fObj ) )
		{
			if ( p_ficObj->iModo == MOD_APR_LECTURA )
			{
				fread ( &byRes, sizeof ( byte ), 1, p_ficObj->p_fObj );
			}
		}
	}
	return ( byRes );
}

int SFicSecLeerBuffer ( SFicSecuencial * p_ficObj, byte * p_byContenido, unsigned long * p_ulTam )
{
	int iRes;

	if ( ES_VALIDO ( p_ficObj ) && ES_VALIDO ( p_byContenido ) && ES_VALIDO ( p_ulTam ) )
	{
		if ( ( *p_ulTam > 0 ) && ( p_ficObj->iAbierto == 1 ) && ES_VALIDO ( p_ficObj->p_fObj ) )
		{
			if ( p_ficObj->iModo == MOD_APR_LECTURA )
			{
				*p_ulTam = fread ( p_byContenido, sizeof ( byte ), *p_ulTam, p_ficObj->p_fObj );
				if ( *p_ulTam > 0 )
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

int SFicSecEscribir ( SFicSecuencial * p_ficObj, byte byValor )
{
	int iRes;

	if ( ES_VALIDO ( p_ficObj ) )
	{
		if ( ( p_ficObj->iAbierto == 1 ) && ES_VALIDO ( p_ficObj->p_fObj ) )
		{
			if ( p_ficObj->iModo == MOD_APR_ESCRITURA )
			{
				if ( fwrite ( &byValor, sizeof ( byte ), 1, p_ficObj->p_fObj ) == 1 )
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

int SFicSecEscribirBuffer ( SFicSecuencial * p_ficObj, byte * p_byContenido, unsigned long * p_ulTam )
{
	int iRes;

	if ( ES_VALIDO ( p_ficObj ) && ES_VALIDO ( p_byContenido ) && ES_VALIDO ( p_ulTam ) )
	{
		if ( ( *p_ulTam > 0 ) && ( p_ficObj->iAbierto == 1 ) && ES_VALIDO ( p_ficObj->p_fObj ) )
		{
			if ( p_ficObj->iModo == MOD_APR_ESCRITURA ) 
			{
				*p_ulTam = fwrite ( p_byContenido, sizeof ( byte ), *p_ulTam, p_ficObj->p_fObj );
				if ( *p_ulTam > 0 )
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

