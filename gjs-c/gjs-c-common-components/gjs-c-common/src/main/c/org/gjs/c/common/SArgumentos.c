#include "SArgumentos.h"

#include "CommonConfig.h"





SArgumentos * SArgCrearDef ()
{
# if ( defined ( WIN ) )
	int				iNumArg; 
	unichar **		p_p_cArg;
	char *			p_cArg;
	int				iNumArgsEnt;
	int				iArg;
# endif
	SArgumentos *	p_argObj;

	p_argObj = (SArgumentos *) MemReservar ( sizeof ( SArgumentos ) );
	if ( ES_VALIDO ( p_argObj ) )
	{
		p_argObj->p_seclitArgumentos = NULL;

#	 if ( defined ( WIN ) )
		p_p_cArg = (unichar **) CommandLineToArgvW ( GetCommandLineW (), &iNumArg );
		if ( ES_VALIDO ( p_p_cArg ) )
		{
		  if ( iNumArg > 1 )
		  {
			iNumArgsEnt = iNumArg - 1;
			p_argObj->p_seclitArgumentos = SSecLitCrear ();
			if ( ES_VALIDO ( p_argObj->p_seclitArgumentos ) )
			{
				for ( iArg = 0; iArg < iNumArgsEnt; iArg = iArg + 1 )
				{
					p_cArg = CadUnicodeAAsciiz ( p_p_cArg [ iArg + 1 ] );
					if ( ES_VALIDO ( p_cArg ) )
					{
						CadEliminarCaracteresNoImprimibles ( p_cArg );
						CadEliminarBlancos ( p_cArg );
						if ( CadLongitud ( p_cArg ) > 0 ) 
						{
							if ( SSecLitInsertar ( p_argObj->p_seclitArgumentos, p_cArg ) == 0 )
							{
								MemLiberar ( (void **) &p_cArg );
							}
						} 
						else
						{
							MemLiberar ( (void **) &p_cArg );
						}
					}
				}
			}
		  }
			/* CommandLineToArgvW reserva el vector con LocalAlloc: hay que
			   soltarlo con LocalFree aunque no se haya usado. */
			LocalFree ( (HLOCAL) p_p_cArg );
		}
#	 endif
	}
	return ( p_argObj );
}

SArgumentos * SArgCrear ( int iNumArg, char ** p_p_cArg )
{
	int				iNumArgsEnt;
	int				iArg;
	char *			p_cArg;
	SArgumentos *	p_argObj;

	p_argObj = (SArgumentos *) MemReservar ( sizeof ( SArgumentos ) );
	if ( ES_VALIDO ( p_argObj ) )
	{
		p_argObj->p_seclitArgumentos = NULL;

		// NOTA: en Unix/Linux suelen pertenecer al espacio de direcciones reservado. No usar ES_VALIDO:
		if ( ( iNumArg > 1 ) && ( p_p_cArg != NULL ) )
		{
			iNumArgsEnt = iNumArg - 1;

			p_argObj->p_seclitArgumentos = SSecLitCrear ();
			if ( ES_VALIDO ( p_argObj->p_seclitArgumentos ) )
			{
				for ( iArg = 0; iArg < iNumArgsEnt; iArg = iArg + 1 )
				{
					p_cArg = CadDuplicar ( p_p_cArg [ iArg + 1 ] );
					if ( ES_VALIDO ( p_cArg ) )
					{
						CadEliminarCaracteresNoImprimibles ( p_cArg );
						CadEliminarBlancos ( p_cArg );
						if ( CadLongitud ( p_cArg ) > 0 )
						{
							if ( SSecLitInsertar ( p_argObj->p_seclitArgumentos, p_cArg ) == 0 )
							{
								MemLiberar ( (void **) &p_cArg );
							}
						}
						else
						{
							MemLiberar ( (void **) &p_cArg );
						}
					}
				}
			}
		}
	}
	return ( p_argObj );
}

void SArgDestruir ( SArgumentos ** p_p_argObj )
{
	SArgumentos * p_argObj;

	if ( ES_VALIDO ( p_p_argObj ) )
	{
		p_argObj = *p_p_argObj;

		if ( ES_VALIDO ( p_argObj ) )
		{
			SSecLitVaciar ( p_argObj->p_seclitArgumentos );
			SSecLitDestruir ( &(p_argObj->p_seclitArgumentos) );
			MemLiberar ( (void **) p_p_argObj );
		}
	}
}

int SArgNumArgumentos ( SArgumentos * p_argObj )
{
	int iRes;

	if ( ES_VALIDO ( p_argObj ) )
	{
		iRes = SSecLitNumElementos ( p_argObj->p_seclitArgumentos ); 
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

char * SArgArgumento ( SArgumentos * p_argObj, int iArg )
{
	char *	p_cArg;

	if ( ES_VALIDO ( p_argObj ) )
	{
		p_cArg = SSecLitElemento ( p_argObj->p_seclitArgumentos, iArg );
	}
	else
	{
		p_cArg = NULL;
	}
	return ( p_cArg );
}

int SArgEsArgumentoNumerico ( SArgumentos * p_argObj, int iArg )
{
	int		iRes;
	char *	p_cArg;

	if ( ES_VALIDO ( p_argObj ) )
	{
		p_cArg = SSecLitElemento ( p_argObj->p_seclitArgumentos, iArg );
		if ( CadEsNumerica ( p_cArg ) == 1 )
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

int SArgArgumentoEntero ( SArgumentos * p_argObj, int iArg )
{
	int		iRes;
	char *	p_cArg;

	if ( ES_VALIDO ( p_argObj ) )
	{
		p_cArg = SSecLitElemento ( p_argObj->p_seclitArgumentos, iArg );
		if ( CadEsNumeroEntero ( p_cArg ) == 1 )
		{
			iRes = ConvCadenaAEntero ( p_cArg );
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

long SArgArgumentoEnteroLargo ( SArgumentos * p_argObj, int iArg )
{
	long	lRes;
	char *	p_cArg;

	if ( ES_VALIDO ( p_argObj ) )
	{
		p_cArg = SSecLitElemento ( p_argObj->p_seclitArgumentos, iArg );
		if ( CadEsNumeroEntero ( p_cArg ) == 1 )
		{
			lRes = ConvCadenaAEnteroLargo ( p_cArg );
		}
		else
		{
			lRes = 0;
		}
	}
	else
	{
		lRes = 0;
	}
	return ( lRes );
}

float SArgArgumentoReal ( SArgumentos * p_argObj, int iArg )
{
	float	fRes;
	char *	p_cArg;

	if ( ES_VALIDO ( p_argObj ) )
	{
		p_cArg = SSecLitElemento ( p_argObj->p_seclitArgumentos, iArg );
		if ( CadEsNumeroReal ( p_cArg ) == 1 )
		{
			fRes = (float) atof ( p_cArg );
		}
		else
		{
			fRes = 0.0;
		}
	}
	else
	{
		fRes = 0.0;
	}
	return ( fRes );
}

double SArgArgumentoRealDoble ( SArgumentos * p_argObj, int iArg )
{
	double	dRes;
	char *	p_cArg;

	if ( ES_VALIDO ( p_argObj ) )
	{
		p_cArg = SSecLitElemento ( p_argObj->p_seclitArgumentos, iArg );
		if ( CadEsNumeroReal ( p_cArg ) == 1 )
		{
			dRes = atof ( p_cArg );
		}
		else
		{
			dRes = 0.0;
		}
	}
	else
	{
		dRes = 0.0;
	}
	return ( dRes );
}



