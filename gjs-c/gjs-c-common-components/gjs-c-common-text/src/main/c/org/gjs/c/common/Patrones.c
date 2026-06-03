/******************************************************************************/
/*                               Patrones.cpp                                 */
/*----------------------------------------------------------------------------*/
/* Librería:  GTexto                                                          */
/* Versión:   1.0.0                                                           */
/* Fecha:     30-06-2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Fichero de código fuente que contiene la implementación de las rutinas     */
/* de ...                                                                     */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#include "Patrones.h"

#include "Cadenas.h"

#include "TextoConfig.h"




char * PatCrear ( int iTam )
{
	char * p_cRes;		

	p_cRes = CadCrear ( iTam );
	if ( ES_VALIDO ( p_cRes ) )
	{
		CadLimpiarExt ( p_cRes, PAT_CAR_DEFECTO, iTam );
	}
	return ( p_cRes );
}

int PatEsValido ( const char * p_cPatron )
{
	int iRes;
	int iCar;
	int iLonPat;

	if ( ES_VALIDO ( p_cPatron ) )
	{
		iLonPat = CadLongitud ( p_cPatron );
		if ( iLonPat > 0 )
		{
			iRes = 1;
			iCar = 0;
			while ( ( iRes == 1 ) && ( iCar < iLonPat ) )
			{
				if ( TipCarEsValido ( p_cPatron [ iCar ] ) == 0 )
				{
					iRes = 0;
				}
				iCar = iCar + 1;
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

char PatCaracter ( char * p_cPatron, int iCar )
{
	return ( CadCaracter ( p_cPatron, iCar ) );
}

int PatEstablecerCaracter ( char * p_cPatron, int iCar, char cValor )
{
	int iRes;

	if ( TipCarEsValido ( cValor ) == 1 )
	{
		iRes = CadEstablecerCaracter ( p_cPatron, iCar, cValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int PatEsSubpatron ( const char * p_cPatron, const char * p_cSubpatron )
{
	int iRes;
	int iCar;
	int iLonPat;
	int iLonSub;

	if ( ES_VALIDO ( p_cPatron ) && ES_VALIDO ( p_cSubpatron ) )
	{
		iLonPat = CadLongitud ( p_cPatron );
		iLonSub = CadLongitud ( p_cSubpatron );
		if ( iLonPat == iLonSub )
		{
			iRes = 1;
			iCar = 0;
			while ( ( iRes == 1 ) && ( iCar < iLonPat ) )
			{
				if ( TipCarEsCualquiera ( p_cPatron [ iCar ] ) == 0 )
				{
					if ( TipCarEsDigito ( p_cPatron [ iCar ] ) == 1 )
					{
						iRes = TipCarEsDigito ( p_cSubpatron [ iCar ] );
					}
					else if ( TipCarEsLetra ( p_cPatron [ iCar ] ) == 1 )
					{
						iRes = TipCarEsLetra ( p_cSubpatron [ iCar ] );
					}
					else if ( TipCarEsLetraDigito ( p_cPatron [ iCar ] ) == 1 )
					{
						if ( ( TipCarEsDigito ( p_cSubpatron [ iCar ] ) == 0 ) &&
							 ( TipCarEsLetra ( p_cSubpatron [ iCar ] ) == 0 ) && 
							 ( TipCarEsLetraDigito ( p_cSubpatron [ iCar ] ) == 0 ) )
						{
							iRes = 0;
						}
					}
					else if ( TipCarEsAlfanumerico ( p_cPatron [ iCar ] ) == 1 )
					{
						if ( ( TipCarEsDigito ( p_cSubpatron [ iCar ] ) == 0 ) &&
							 ( TipCarEsLetra ( p_cSubpatron [ iCar ] ) == 0 ) && 
							 ( TipCarEsLetraDigito ( p_cSubpatron [ iCar ] ) == 0 ) &&
							 ( TipCarEsAlfanumerico ( p_cSubpatron [ iCar ] ) == 0 ) )
						{
							iRes = 0;
						}
					}
					else
					{
						iRes = 0;
					}
				}
				iCar = iCar + 1;
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

int PatEvaluar ( const char * p_cPatron, const char * p_cCadena )
{
	int iRes;
	int iCar;
	int iLonPat;
	int iLonCad;

	if ( ES_VALIDO ( p_cPatron ) && ES_VALIDO ( p_cCadena ) )
	{
		iLonPat = CadLongitud ( p_cPatron );
		iLonCad = CadLongitud ( p_cCadena );
		if ( iLonPat <= iLonCad )
		{
			iRes = 1;
			iCar = 0;
			while ( ( iRes == 1 ) && ( iCar < iLonPat ) )
			{
				if ( TipCarEsCualquiera ( p_cPatron [ iCar ] ) == 0 )
				{
					if ( TipCarEsDigito ( p_cPatron [ iCar ] ) == 1 )
					{
						iRes = ASCIIEsDigito ( p_cCadena [ iCar ] );
					}
					else if ( TipCarEsLetra ( p_cPatron [ iCar ] ) == 1 )
					{
						iRes = ASCIIEsLetra ( p_cCadena [ iCar ] );
					}
					else if ( TipCarEsLetraDigito ( p_cPatron [ iCar ] ) == 1 )
					{
						if ( ( ASCIIEsDigito ( p_cCadena [ iCar ] ) == 0 ) &&
							 ( ASCIIEsLetra ( p_cCadena [ iCar ] ) == 0 ) )
						{
							iRes = 0;
						}
					}
					else if ( TipCarEsAlfanumerico ( p_cPatron [ iCar ] ) == 1 )
					{
						if ( ( ASCIIEsDigito ( p_cCadena [ iCar ] ) == 0 ) &&
							 ( ASCIIEsLetra ( p_cCadena [ iCar ] ) == 0 ) && 
							 ( ASCIIEsEspacio ( p_cCadena [ iCar ] ) == 0 ) &&
							 ( ASCIIEsSigno ( p_cCadena [ iCar ] ) == 0 ) )
						{
							iRes = 0;
						}
					}
					else
					{
						iRes = 0;
					}
				}
				iCar = iCar + 1;
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

char * PatValorInicial ( const char * p_cPatron )
{
	char *	p_cRes;
	int		iCar;
	int		iLon;

	if ( ES_VALIDO ( p_cPatron ) )
	{
		iLon = CadLongitud ( p_cPatron );
		if ( iLon > 0 )
		{
			p_cRes = CadCrear ( iLon );
			if ( ES_VALIDO ( p_cRes ) )
			{
				iCar = 0;
				while ( iCar < iLon )
				{
					if ( TipCarEsCualquiera ( p_cPatron [ iCar ] ) == 1 )
					{
						p_cRes [ iCar ] = '0';
					}
					else if ( TipCarEsDigito ( p_cPatron [ iCar ] ) == 1 )
					{
						p_cRes [ iCar ] = '0';
					}
					else if ( TipCarEsLetra ( p_cPatron [ iCar ] ) == 1 )
					{
						p_cRes [ iCar ] = 'A';
					}
					else if ( TipCarEsLetraDigito ( p_cPatron [ iCar ] ) == 1 )
					{
						p_cRes [ iCar ] = '0';
					}
					else if ( TipCarEsAlfanumerico ( p_cPatron [ iCar ] ) == 1 )
					{
						p_cRes [ iCar ] = '0';
					}
					else
					{
						p_cRes [ iCar ] = '0';
					}
					iCar = iCar + 1;
				}
			}
		}
		else
		{
			p_cRes = NULL;
		}
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

char * PatValorFinal ( const char * p_cPatron )
{
	char *	p_cRes;
	int		iCar;
	int		iLon;

	if ( ES_VALIDO ( p_cPatron ) )
	{
		iLon = CadLongitud ( p_cPatron );
		if ( iLon > 0 )
		{
			p_cRes = CadCrear ( iLon );
			if ( ES_VALIDO ( p_cRes ) )
			{
				iCar = 0;
				while ( iCar < iLon )
				{
					if ( TipCarEsCualquiera ( p_cPatron [ iCar ] ) == 1 )
					{
						p_cRes [ iCar ] = 'Z';
					}
					else if ( TipCarEsDigito ( p_cPatron [ iCar ] ) == 1 )
					{
						p_cRes [ iCar ] = '9';
					}
					else if ( TipCarEsLetra ( p_cPatron [ iCar ] ) == 1 )
					{
						p_cRes [ iCar ] = 'Z';
					}
					else if ( TipCarEsLetraDigito ( p_cPatron [ iCar ] ) == 1 )
					{
						p_cRes [ iCar ] = 'Z';
					}
					else if ( TipCarEsAlfanumerico ( p_cPatron [ iCar ] ) == 1 )
					{
						p_cRes [ iCar ] = 'Z';
					}
					else
					{
						p_cRes [ iCar ] = 'Z';
					}
					iCar = iCar + 1;
				}
			}
		}
		else
		{
			p_cRes = NULL;
		}
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

int PatIncrementarValor ( const char * p_cPatron, char * p_cCadena )
{
	return ( PatIncrementarValorDesde ( p_cPatron, p_cCadena, CadLongitud ( p_cPatron ) - 1 ) );
}

int PatDecrementarValor ( const char * p_cPatron, char * p_cCadena )
{
	return ( PatDecrementarValorDesde ( p_cPatron, p_cCadena, CadLongitud ( p_cPatron ) - 1 ) );
}

int PatIncrementarValorDesde ( const char * p_cPatron, char * p_cCadena, int iPos )
{
	int iRes;
	int iCar;
	int iLon;
	int iAcarreo;

	if ( ES_VALIDO ( p_cPatron ) && ES_VALIDO ( p_cCadena ) )
	{
		iLon = CadLongitud ( p_cPatron );
		if ( ( CadLongitud ( p_cCadena ) == iLon ) && ( iPos >= 0 ) && ( iPos < iLon ) )
		{
			iAcarreo = 1;
			iRes = 1;
			iCar = iPos;
			while ( ( iRes == 1 ) && ( iCar >= 0 ) && ( iAcarreo == 1 ) )
			{
				if ( ASCIIPerteneceAlJuegoPrincipal ( p_cCadena [ iCar ] ) == 1 )
				{
					if ( ASCIIEsDigito ( p_cCadena [ iCar ] ) == 1 )
					{
						if ( TipCarEsLetra ( p_cPatron [ iCar ] ) == 0 )
						{
							if ( p_cCadena [ iCar ] != '9' )
							{
								iAcarreo = 0;
								p_cCadena [ iCar ] = p_cCadena [ iCar ] + 1;
							}
							else
							{
								if ( TipCarEsDigito ( p_cPatron [ iCar ] ) == 1 )
								{
									iAcarreo = 1;
									p_cCadena [ iCar ] = '0';
								}
								else 
								{
									iAcarreo = 0;
									p_cCadena [ iCar ] = 'A';
								}
							}
						}
						else
						{
							iRes = 0;
						}
					}
					else if ( ASCIIEsLetra ( p_cCadena [ iCar ] ) == 1 )
					{
						if ( TipCarEsDigito ( p_cPatron [ iCar ] ) == 0 )
						{
							if ( ( p_cCadena [ iCar ] != 'Z' ) && 
								 ( p_cCadena [ iCar ] != 'z' ) )
							{
								iAcarreo = 0;
								p_cCadena [ iCar ] = p_cCadena [ iCar ] + 1;
							}
							else
							{
								iAcarreo = 1;
								if ( TipCarEsLetra ( p_cPatron [ iCar ] ) == 1 )
								{
									p_cCadena [ iCar ] = 'A';
								}
								else 
								{
									p_cCadena [ iCar ] = '0';
								}
							}
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
				iCar = iCar - 1;
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

int PatDecrementarValorDesde ( const char * p_cPatron, char * p_cCadena, int iPos )
{
	int iRes;
	int iCar;
	int iLon;
	int iAcarreo;

	if ( ES_VALIDO ( p_cPatron ) && ES_VALIDO ( p_cCadena ) )
	{
		iLon = CadLongitud ( p_cPatron );
		if ( ( CadLongitud ( p_cCadena ) == iLon ) && ( iPos >= 0 ) && ( iPos < iLon ) )
		{
			iAcarreo = 1;
			iRes = 1;
			iCar = iPos;
			while ( ( iRes == 1 ) && ( iCar >= 0 ) && ( iAcarreo == 1 ) )
			{
				if ( ASCIIPerteneceAlJuegoPrincipal ( p_cCadena [ iCar ] ) == 1 )
				{
					if ( ASCIIEsDigito ( p_cCadena [ iCar ] ) == 1 )
					{
						if ( TipCarEsLetra ( p_cPatron [ iCar ] ) == 0 )
						{
							if ( p_cCadena [ iCar ] != '0' )
							{
								iAcarreo = 0;
								p_cCadena [ iCar ] = p_cCadena [ iCar ] - 1;
							}
							else
							{
								iAcarreo = 1;
								if ( TipCarEsDigito ( p_cPatron [ iCar ] ) == 1 )
								{
									p_cCadena [ iCar ] = '9';
								}
								else 
								{
									iAcarreo = 0;
									p_cCadena [ iCar ] = 'Z';
								}
							}
						}
						else
						{
							iRes = 0;
						}
					}
					else if ( ASCIIEsLetra ( p_cCadena [ iCar ] ) == 1 )
					{
						if ( TipCarEsDigito ( p_cPatron [ iCar ] ) == 0 )
						{
							if ( ( p_cCadena [ iCar ] != 'a' ) && 
								 ( p_cCadena [ iCar ] != 'A' ) )
							{
								iAcarreo = 0;
								p_cCadena [ iCar ] = p_cCadena [ iCar ] - 1;
							}
							else
							{
								if ( TipCarEsLetra ( p_cPatron [ iCar ] ) == 1 )
								{
									iAcarreo = 1;
									p_cCadena [ iCar ] = 'Z';
								}
								else 
								{
									iAcarreo = 0;
									p_cCadena [ iCar ] = '9';
								}
							}
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
				iCar = iCar - 1;
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

