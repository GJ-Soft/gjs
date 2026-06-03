#include "ExpresionesRegulares.h"
#include "Cadenas.h"

#include "TextoConfig.h"


int _ExpRegSeCumpleAlInicio ( const char * p_cExpReg, const char * p_cCadena, int * p_iUltPos );
char * _ExpRegNormalizar ( const char * p_cExpReg );

int ExpRegSeCumple ( const char * p_cExpReg, const char * p_cCadena )
{
	int 	iRes;
	int		iUltPos;
	char * 	p_cExpRegNorm;
	
	p_cExpRegNorm = _ExpRegNormalizar ( p_cExpReg );
	iRes = _ExpRegSeCumpleAlInicio ( p_cExpRegNorm, p_cCadena, &iUltPos );
	MemLiberar ( (void **) &p_cExpRegNorm );
	if ( ( iRes == 1 ) && ( iUltPos < CadLongitud ( p_cCadena ) ) )
	{
		iRes = 0;
	}
	return ( iRes );
}


int ExpRegSeCumpleAlInicio ( const char * p_cExpReg, const char * p_cCadena )
{
	int 	iRes;
	int		iUltPos;
	char * 	p_cExpRegNorm;
	
	p_cExpRegNorm = _ExpRegNormalizar ( p_cExpReg );
	iRes = _ExpRegSeCumpleAlInicio ( p_cExpRegNorm, p_cCadena, &iUltPos );
	MemLiberar ( (void **) &p_cExpRegNorm );
	return ( iRes );
}


int _ExpRegSeCumpleAlInicio ( const char * p_cExpRegNorm, const char * p_cCadena, int * p_iUltPos )
{
	int				iRes;
	int				iCarReg;
	int				iTamReg;
	int				iTamCad;
	char			cReg;
	char			cCad;
	const char *	p_cSubExpReg;
	const char *	p_cSubCadena;
	char *			p_cSubExpRegAux;
	char *			p_cSubCadenaAux;
	int				iCumple;
	int				iLiteral;
	int				iIniSubPat;
	int				iFinSubPat;
	int				iSubPats;
	int				iCarIniSubPat;
	int				iCarFinSubPat;
	int				iIncCarCad;

	if ( ES_VALIDO ( p_cExpRegNorm ) && ES_VALIDO ( p_cCadena ) && ES_VALIDO ( p_iUltPos ) )
	{
		iTamCad = CadLongitud ( p_cCadena );
		if ( iTamCad > 0 )
		{
			iTamReg = CadLongitud ( p_cExpRegNorm );
			if ( ( iTamReg == 1 ) && ( p_cExpRegNorm [ 0 ] == '*' ) )
			{
				iRes = iTamCad;
			}
			else if ( iTamReg > 0 ) 
			{
				*p_iUltPos = 0;
				iCarReg = 0;
				iIniSubPat = -1;
				iFinSubPat = -1;
				iCarIniSubPat = -1;
				iRes = 1;
				while ( ( *p_iUltPos < iTamCad ) && ( iCarReg < iTamReg ) && ( iRes == 1 ) )
				{
					iLiteral = 0;
					cReg = p_cExpRegNorm [ iCarReg ];
					if ( ( (int)cReg == ASCII_COMILLA_SIMPLE ) && ( iCarReg + 2 < iTamReg ) )
					{
						if ( p_cExpRegNorm [ iCarReg + 2 ] == ASCII_COMILLA_SIMPLE ) 
						{
							cReg = p_cExpRegNorm [ iCarReg + 1 ];
							iCarReg = iCarReg + 2;
							iLiteral = 1;
						}
					}
					else if ( cReg == '(' )
					{
						iSubPats = 1;
						iIniSubPat = iCarReg;
						iFinSubPat = iIniSubPat + 1;
						while ( ( iSubPats > 0 ) && ( iFinSubPat < iTamReg ) )
						{
							if ( ( p_cExpRegNorm [ iFinSubPat ]== ASCII_COMILLA_SIMPLE ) && ( iFinSubPat + 2 < iTamReg ) )
							{
								if ( p_cExpRegNorm [ iFinSubPat + 2 ] == ASCII_COMILLA_SIMPLE ) 
								{
									iFinSubPat = iFinSubPat + 2;
								}
							}
							else if ( p_cExpRegNorm [ iFinSubPat ] == ')' ) 
							{
								iSubPats = iSubPats - 1;
							}
							else if ( p_cExpRegNorm [ iFinSubPat ] == '(' ) 
							{
								iSubPats = iSubPats + 1;
							}
							iFinSubPat = iFinSubPat + 1;
						} 
						if ( ( iSubPats == 0 ) && ( iFinSubPat - iIniSubPat - 1 > 1 ) )
						{
							// Hay subpatron:
							iCarIniSubPat = *p_iUltPos;
							iCarReg = iFinSubPat + 1;
							if ( iCarReg < iTamReg ) 
							{
								cReg = p_cExpRegNorm [ iCarReg ];
							}
							else
							{
								iRes = 1;
							}
						}
						else
						{
							iIniSubPat = -1;
							iFinSubPat = -1;
						}
					}

					if ( iCarReg < iTamReg ) 
					{
						cCad = p_cCadena [ *p_iUltPos ];

						if ( iLiteral == 1 )
						{
							if ( cReg != cCad )
							{
								iRes = 0;
							}
						}
						else if ( cReg == '*' )
						{
							// Saltar posibles * seguidos:
							while ( ( cReg == '*' ) && ( iCarReg < iTamReg - 1 ) )
							{
								iCarReg = iCarReg + 1;
								cReg = p_cExpRegNorm [ iCarReg ];
							} 

							// Si la espreg termina por * ya está.
							if ( cReg != '*' )
							{
								// Si no se verifica el resto de la cadena:
								p_cSubExpReg = &(p_cExpRegNorm [ iCarReg ]);

								iCumple = 0;
								while ( ( *p_iUltPos < iTamCad ) && ( iCumple == 0 ) )
								{
									p_cSubCadena = &(p_cCadena [ *p_iUltPos ]);
									int iAuxPos;
									if ( _ExpRegSeCumpleAlInicio ( p_cSubExpReg, p_cSubCadena, &iAuxPos ) == 1 )
									{
										iCumple = 1;
									}
									*p_iUltPos = *p_iUltPos + 1;
								}

								// Debe finalizar siempre el bucle:
								if ( iCumple == 1 )
								{
									*p_iUltPos = iTamCad;
									iCarReg = iTamReg;
								}
								else
								{
									iRes = 0;
								}
							}
						}
						else if ( cReg != '?' )
						{
							if ( cReg != cCad )
							{
								iRes = 0;
							}
						}

						iCarReg = iCarReg + 1;
						*p_iUltPos = *p_iUltPos + 1;
					}
				}

				if ( iRes == 1 )
				{
					if ( iCarReg < iTamReg )
					{
						while ( ( iCarReg < iTamReg ) && ( p_cExpRegNorm [ iCarReg ] == '*' ) )
						{
							iCarReg = iCarReg + 1;
						} 
						if ( iCarReg < iTamReg )
						{
							iRes = 0;
						}
					}
					else if ( ( *p_iUltPos < iTamCad ) && ( cReg == '*' ) )
					{
						*p_iUltPos = iTamCad;
					}
				}
				else if ( iIniSubPat >= 0 )
				{
					// Procesamiento con subpatrón:
					if ( iFinSubPat < iTamReg )
					{
						p_cSubExpReg = &(p_cExpRegNorm [ iFinSubPat ]);
						iCumple = 0;
						iCarFinSubPat = iCarIniSubPat;
						while ( ( iCarFinSubPat < iTamCad ) && ( iCumple == 0 ) )
						{
							p_cSubCadena = &(p_cCadena [ iCarFinSubPat ]);
							iIncCarCad = ExpRegSeCumpleAlInicio ( p_cSubExpReg, p_cSubCadena );
							if ( iIncCarCad > 0 )
							{
								iRes = iCarFinSubPat + iIncCarCad;
								iCumple = 1;
							}
							else
							{
								iCarFinSubPat = iCarFinSubPat + 1;
							}
						}
					}
					else
					{
						iCumple = 1;
						iCarFinSubPat = iTamCad;
						iRes = 1;
					}
					if ( iCumple == 1 )
					{
						// Comprobar repeticion subpatrón:
						p_cSubExpRegAux = CadExtraer ( p_cExpRegNorm, iIniSubPat + 1, iFinSubPat - iIniSubPat - 2 );
						p_cSubCadenaAux = CadExtraer ( p_cCadena, iCarIniSubPat, iCarFinSubPat - iCarIniSubPat );
						if ( ES_VALIDO ( p_cSubExpRegAux ) && ES_VALIDO ( p_cSubCadenaAux ) )
						{
							iTamCad = CadLongitud ( p_cSubCadenaAux );
							*p_iUltPos = 0;
							while ( ( iCumple == 1 ) && ( *p_iUltPos < iTamCad ) )
							{
								iIncCarCad = ExpRegSeCumpleAlInicio ( p_cSubExpRegAux, &(p_cSubCadenaAux [ *p_iUltPos ]) );
								if ( iIncCarCad > 0 )
								{
									*p_iUltPos = *p_iUltPos + iIncCarCad;
								}
								else
								{
									iCumple = 0;
								}
							}
							iRes = iCumple;
						}
						MemLiberar ( (void **) &p_cSubExpRegAux );
						MemLiberar ( (void **) &p_cSubCadenaAux );
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
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

char * _ExpRegNormalizar ( const char * p_cExpReg )
{
	char * 	p_cRes;
	int 	iLong;
	int		iCar;
	int		iCarNorm;
	int		iIncluir;
	int 	iAsterisco;
	
	if ( ES_VALIDO ( p_cExpReg ) )
	{
		iLong = CadLongitud ( p_cExpReg );
		p_cRes = CadCrear ( iLong );
		iCarNorm = 0;
		for ( iCar = 0; iCar < iLong; iCar = iCar + 1 )
		{
			iIncluir = 1;
			if ( p_cExpReg [ iCar ] == '*' )
			{
				if ( iAsterisco == 1 )
				{
					iIncluir = 0;
				} 
				else
				{
					iAsterisco = 1;
				}
			}
			if ( iIncluir == 1 )
			{
				p_cRes [ iCarNorm ] = p_cExpReg [ iCar ];
				iCarNorm = iCarNorm + 1; 
			}
		}
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}
