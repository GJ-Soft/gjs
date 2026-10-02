#include "ExpresionesRegulares.h"
#include "Cadenas.h"

#include "TextoConfig.h"


int _ExpRegSeCumpleAlInicio ( const char * p_cExpReg, const char * p_cCadena, int * p_iUltPos );
char * _ExpRegNormalizar ( const char * p_cExpReg );
static int _ExpRegRepeticiones ( const char * p_cSubExpReg, const char * p_cResto,
								 const char * p_cCadena, int * p_iUltPos );

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

	if ( ES_VALIDO ( p_cExpRegNorm ) && ES_VALIDO ( p_cCadena ) && ES_VALIDO ( p_iUltPos ) )
	{
		// Las ramas que devuelven FALSO no llegan a fijarlo, y aunque hoy ningun
		// llamante lo mire en ese caso, el parametro de salida queda definido siempre.
		*p_iUltPos = 0;
		iTamCad = CadLongitud ( p_cCadena );
		iTamReg = CadLongitud ( p_cExpRegNorm );
		if ( ( iTamReg == 1 ) && ( p_cExpRegNorm [ 0 ] == '*' ) )
		{
			// El comodin suelto consume la cadena entera, tambien la vacia. Sin esta linea el atajo
			// devolvia CIERTO sin escribir p_iUltPos, y ExpRegSeCumple lo leia con
			// lo que hubiera en la pila: si salia menor que la longitud, daba FALSO.
			*p_iUltPos = iTamCad;
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
						// <= y no <: el resto tambien se prueba contra el sufijo vacio, que
						// encaja si el resto es * o ( … ).
						while ( ( iCumple == 0 ) && ( *p_iUltPos <= iTamCad ) ) 
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
						// Hay subpatron: ( x ) es cero o mas repeticiones de x. Lo que
						// sigue al parentesis lo evalua _ExpRegRepeticiones, que es quien
						// sabe cuantas repeticiones dejarle.
						p_cSubExpRegAux = CadExtraer ( p_cExpRegNorm, iIniSubPat + 1, iFinSubPat - iIniSubPat - 2 );
						if ( ES_VALIDO ( p_cSubExpRegAux ) )
						{
							iRes = _ExpRegRepeticiones ( p_cSubExpRegAux, &(p_cExpRegNorm [ iFinSubPat ]), p_cCadena, p_iUltPos );
							iCarReg = iTamReg;
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
	return ( iRes );
}

/* Evalua un subpatron ( x ) -- cero o mas repeticiones de x -- desde la
   posicion *p_iUltPos de la cadena, junto con el resto del patron que va
   detras del parentesis. Las repeticiones son voraces pero con vuelta atras:
   se prueban de la mas larga a la mas corta hasta que el resto encaja, y se
   prefiere la que deja consumida la cadena entera. Una repeticion que no
   consume nada termina la serie ( si no, no acabaria nunca ). Devuelve 1 si
   encaja y deja en *p_iUltPos la posicion final. */
static int _ExpRegRepeticiones ( const char * p_cSubExpReg, const char * p_cResto,
								 const char * p_cCadena, int * p_iUltPos )
{
	int		iRes;
	int		iTamCad;
	int *	p_iPosiciones;
	int		iNumPos;
	int		iPos;
	int		iConsumido;
	int		iFin;
	int		iCandidato;
	int		iEncontrado;

	iTamCad = CadLongitud ( p_cCadena );
	/* Cada repeticion consume al menos un caracter: como mucho hay tantas
	   posiciones como caracteres quedan, mas la de partida. */
	p_iPosiciones = (int *) MemReservar ( ( iTamCad - *p_iUltPos + 1 ) * sizeof ( int ) );
	if ( ES_VALIDO ( p_iPosiciones ) )
	{
		p_iPosiciones [ 0 ] = *p_iUltPos;
		iNumPos = 1;
		iFin = 0;
		while ( iFin == 0 )
		{
			iPos = p_iPosiciones [ iNumPos - 1 ];
			if ( iPos < iTamCad )
			{
				if ( _ExpRegSeCumpleAlInicio ( p_cSubExpReg, &(p_cCadena [ iPos ]), &iConsumido ) == 1 )
				{
					if ( iConsumido > 0 )
					{
						p_iPosiciones [ iNumPos ] = iPos + iConsumido;
						iNumPos = iNumPos + 1;
					}
					else
					{
						iFin = 1;
					}
				}
				else
				{
					iFin = 1;
				}
			}
			else
			{
				iFin = 1;
			}
		}
		if ( CadLongitud ( p_cResto ) == 0 )
		{
			/* Nada detras: todas las repeticiones posibles. */
			*p_iUltPos = p_iPosiciones [ iNumPos - 1 ];
			iRes = 1;
		}
		else
		{
			iRes = 0;
			iEncontrado = 0;
			iCandidato = iNumPos - 1;
			while ( ( iCandidato >= 0 ) && ( iEncontrado == 0 ) )
			{
				iPos = p_iPosiciones [ iCandidato ];
				if ( _ExpRegSeCumpleAlInicio ( p_cResto, &(p_cCadena [ iPos ]), &iConsumido ) == 1 )
				{
					if ( iRes == 0 )
					{
						/* La primera que encaja vale para el encaje al inicio. */
						*p_iUltPos = iPos + iConsumido;
						iRes = 1;
					}
					if ( iPos + iConsumido == iTamCad )
					{
						/* Y si alguna llega al final, esa. */
						*p_iUltPos = iTamCad;
						iEncontrado = 1;
					}
				}
				iCandidato = iCandidato - 1;
			}
		}
		MemLiberar ( (void **) &p_iPosiciones );
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
