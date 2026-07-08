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
	const char *	p_cSubExpReg;
	const char *	p_cSubCadena;
	char *			p_cSubExpRegAux;
	int				iCumple;
	int				iLiteral;
	int				iSubliteral;
	int				iIniSubPat;
	int				iFinSubPat;
	int				iSubPats;
	int				iIncCarCad;

	if ( ES_VALIDO ( p_cExpRegNorm ) && ES_VALIDO ( p_cCadena ) && ES_VALIDO ( p_iUltPos ) )
	{
		iTamCad = CadLongitud ( p_cCadena );
		if ( iTamCad > 0 )
		{
			iTamReg = CadLongitud ( p_cExpRegNorm );
			if ( ( iTamReg == 1 ) && ( p_cExpRegNorm [ 0 ] == '*' ) )
			{
				iRes = 1;
			}
			else if ( iTamReg > 0 ) 
			{
				*p_iUltPos = 0;
				iCarReg = 0;
				iLiteral = 0;
				iRes = 1;
				while ( ( *p_iUltPos < iTamCad ) && ( iCarReg < iTamReg ) && ( iRes == 1 ) )
				{
					cReg = p_cExpRegNorm [ iCarReg ];
					if ( (int)cReg == ASCII_COMILLA_SIMPLE )
					{
						if ( iLiteral == 0 )
						{
							iLiteral = 1;
						}
						else
						{
							iLiteral = 0;
						}
					}
					else if ( iLiteral == 1 )
					{
						if ( cReg != p_cCadena [ *p_iUltPos ] )
						{
							iRes = 0;
						}
						*p_iUltPos = *p_iUltPos + 1;
					}
					else if ( cReg == '*' )
					{
						// En el normalizado no debe haber * seguidos
						if ( iCarReg + 1 < iTamReg )
						{
							// Si no se verifica el resto de la cadena:
							p_cSubExpReg = &(p_cExpRegNorm [ iCarReg + 1]);
							iCumple = 0;
							while ( ( iCumple == 0 ) && ( *p_iUltPos < iTamCad ) ) 
							{
								p_cSubCadena = &(p_cCadena [ *p_iUltPos ]);
								iCumple = ExpRegSeCumple ( p_cSubExpReg, p_cSubCadena );
								*p_iUltPos = *p_iUltPos + 1;
							}
						} 
						else
						{
							iCumple = 1;
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
					else if ( cReg == '(' )
					{
						iSubPats = 1;
						iIniSubPat = iCarReg;
						iFinSubPat = iIniSubPat + 1;
						iSubliteral = 0;
						while ( ( iSubPats > 0 ) && ( iFinSubPat < iTamReg ) )
						{
							if ( p_cExpRegNorm [ iFinSubPat ]== ASCII_COMILLA_SIMPLE )
							{
								if ( iSubliteral == 0 )
								{
									iSubliteral = 1;
								}
								else
								{
									iSubliteral = 0;
								}
							}
							else if ( iSubliteral == 0 )
							{
								if ( p_cExpRegNorm [ iFinSubPat ] == ')' ) 
								{
									iSubPats = iSubPats - 1;
								}
								else if ( p_cExpRegNorm [ iFinSubPat ] == '(' ) 
								{
									iSubPats = iSubPats + 1;
								}
							}
							iFinSubPat = iFinSubPat + 1;
						}
						iCarReg = iFinSubPat - 1;
						if ( ( iSubliteral == 0 ) && ( iSubPats == 0 ) && ( iFinSubPat - iIniSubPat - 2 > 0 ) )
						{
							// Hay subpatron:
							p_cSubExpRegAux = CadExtraer ( p_cExpRegNorm, iIniSubPat + 1, iFinSubPat - iIniSubPat - 2 );
							if ( ES_VALIDO ( p_cSubExpRegAux ) )
							{
								p_cSubCadena = &(p_cCadena [ *p_iUltPos ]);
								iCumple = 1;
								while ( ( iCumple == 1 ) && ( *p_iUltPos < iTamCad ) )
								{
									iIncCarCad = ExpRegSeCumpleAlInicio ( p_cSubExpRegAux, p_cSubCadena );
									if ( iIncCarCad > 0 )
									{
										*p_iUltPos = *p_iUltPos + iIncCarCad;
									}
									else
									{
										iCumple = 0;
									}
								}
								MemLiberar ( (void **) &p_cSubExpRegAux );
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
					else if ( cReg == '?' )
					{
						*p_iUltPos = *p_iUltPos + 1;
					}
					else 
					{
						if ( cReg != p_cCadena [ *p_iUltPos ] )
						{
							iRes = 0;
						}
						*p_iUltPos = *p_iUltPos + 1;
					}
				
					iCarReg = iCarReg + 1;
				}

				if ( iRes == 1 )
				{
					if ( iLiteral == 1 ) 
					{
						if ( ( iCarReg < iTamReg - 1 ) || 
								( p_cExpRegNorm [ iCarReg ] != '\'' ) )
						{
							iRes = 0;
						}
					}
					else if ( iCarReg < iTamReg )
					{
						iLiteral = 0;
						iSubPats = 0;
						while ( ( iCarReg < iTamReg ) && ( iRes == 1 ) )
						{
							cReg = p_cExpRegNorm [ iCarReg ];	
							if ( iSubPats == 0 )
							{
								if ( cReg == ASCII_COMILLA_SIMPLE )
								{
									if ( iLiteral == 0 )
									{
										iLiteral = 1;
									}
									else
									{
										iLiteral = 0;
									}
								} 
								else if ( iLiteral == 1 )
								{
									iRes = 0;
								}
								else if ( ( cReg != '*' ) && ( cReg != '(') && ( cReg != ')') ) 
								{
									iRes = 0;
								}
							}
							if ( cReg == '(' )
							{
								iSubPats = iSubPats + 1;
							}
							else if ( cReg == ')' )
							{
								iSubPats = iSubPats - 1;
								if ( iSubPats < 0 )
								{
									iRes = 0;
								}
							}
							iCarReg = iCarReg + 1;
						} 
					}
				}
				if ( ( *p_iUltPos < iTamCad ) && ( iRes == 1 ) )
				{
					if ( cReg == '*' )
					{
						*p_iUltPos = iTamCad;
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
		iAsterisco = 0;
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
			else
			{
				iAsterisco = 0;
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
