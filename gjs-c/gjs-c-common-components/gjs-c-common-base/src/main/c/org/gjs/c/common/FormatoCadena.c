/******************************************************************************/
/*                             FormatoCadena.cpp                              */
/*----------------------------------------------------------------------------*/
/* Librería:  GBase                                                           */
/* Versión:   1.0.0                                                           */
/* Fecha:     28/06/2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Fichero de código fuente que contiene la implementación de una rutina      */
/* general espacial para generar cadenas formateadas a partir de un           */
/* formato y una serie indeterminada de argumentos.                           */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#include "FormatoCadena.h"




#include "BaseConfig.h"
#include "Memoria.h"
#include "CadenasBase.h"
#include "Errores.h"







#define _FRM_CODIGOS			"dioxXucsSfeEgGpn"
#define _FRM_MAX_TAM_TMP		63






static int _EsCadenaValida ( char * p_cCad );





int FrmCadena ( char * p_cCadena, const char * p_cFormato, va_list valArgumentos, int iMaxTam )
{
	int			iRes;
	int			iPosFrm;
	int			iPosCad;
	int			iEstado;
	char		cCarFrm;
	int			iAnchura;
	int			iPrecision;
	int			iMaxAncho;
	int			iPosFrmP;
	int			iPosTmp;
	int			iPosCod;
	void *		p_vArg;
	char *	    p_cArg;
	//void *	p_vCod;
	int			iPosBuf;
	int			iArg;
	double		dArg;
	long		lArg;
	int			iIndLargo;
	char *	    p_cTmp;
	char *		p_cFrmProc;
	char *		p_cCod;
	char *		p_cBuffer;
	int			iPosPun;
	int			iLongBuf;
	int			iLongEsc;

	/* Se inicializan a NULL porque solo se reservan dentro del if; si el guard
	   falla (p.ej. iMaxTam <= 0 con la salida redirigida) los MemLiberar del
	   final se ejecutan igualmente y sobre punteros sin inicializar abortarian. */
	p_cTmp = NULL;
	p_cFrmProc = NULL;
	p_cCod = NULL;
	p_cBuffer = NULL;
	if ( ES_VALIDO ( p_cCadena ) && ES_VALIDO ( p_cFormato ) && ( iMaxTam > 0 ) )
	{
		p_cTmp = CadCrear ( _FRM_MAX_TAM_TMP );
		p_cFrmProc = CadCrear ( CAD_BASE_MAX_TAM );
		p_cCod = CadCrear ( 127 );
		p_cBuffer = CadCrear ( CAD_BASE_MAX_TAM );
		if ( ES_VALIDO ( p_cTmp ) && ES_VALIDO ( p_cFrmProc ) && ES_VALIDO ( p_cCod ) && ES_VALIDO ( p_cBuffer ) )
		{
			iRes = 1;
			iEstado = 0;
			iPosTmp = 0;
			iPosFrm = 0;
			iPosCad = 0;
			iPosFrmP = 0;
			iMaxAncho = -1;
			while ( ( iPosFrm < CadLongitud ( p_cFormato ) ) &&
					( iPosCad < iMaxTam ) && ( iRes == 1 ) )
			{
			    iAnchura = 0;
			    iPrecision = 0;
				cCarFrm = p_cFormato [ iPosFrm ];
				switch ( iEstado )
				{
					case 0: // Espera de indicador de argumento:
					{
						if ( cCarFrm != '%' )
						{
							p_cCadena [ iPosCad ] = cCarFrm;
							iPosCad = iPosCad + 1;
						}
						else
						{
							iIndLargo = 0;
							iAnchura = 0;
							iPrecision = 0;
							CadInicializar ( p_cTmp, iPosTmp );
							iPosTmp = 0;
							p_cFrmProc [ 0 ] = cCarFrm;
							iPosFrmP = 1;
							iEstado = 1;
						}
						break;
					}
					case 1: // Procesando el flag:
					{
						if ( ( cCarFrm >= '0' ) && ( cCarFrm <= '9' ) )
						{
							p_cTmp [ iPosTmp ] = cCarFrm;
							iPosTmp = iPosTmp + 1;
							p_cFrmProc [ iPosFrmP ] = cCarFrm;
							iPosFrmP = iPosFrmP + 1;
							iEstado = 2;
						}
						else if ( cCarFrm == 'l' )
						{
							if ( iIndLargo == 1 )
							{
								iRes = 0;
							}
							else
							{
								iIndLargo = 1;
								p_cFrmProc [ iPosFrmP ] = cCarFrm;
								iPosFrmP = iPosFrmP + 1;
								iEstado = 1;
							}
						}
						else if ( strchr ( _FRM_CODIGOS, cCarFrm ) != NULL )
						{
							if ( iIndLargo == 1 )
							{
								if ( ( cCarFrm != 'd' ) && ( cCarFrm != 'f' ) && ( cCarFrm != 'u' ) )
								{
									iRes = 0;
								}
							}
							iPosFrm = iPosFrm - 1;
							iEstado = 8;
						}
						else if ( cCarFrm == '*' )
						{
							iAnchura  = va_arg ( valArgumentos, int );
							CadInicializar ( p_cTmp, iPosTmp );
							snprintf ( p_cTmp, _FRM_MAX_TAM_TMP + 1, "%d", iAnchura );
							for ( iPosTmp = 0; iPosTmp < CadLongitud ( p_cTmp ); iPosTmp = iPosTmp + 1 )
							{
								p_cFrmProc [ iPosFrmP ] = p_cTmp [ iPosTmp ];
								iPosFrmP = iPosFrmP + 1;
							}
							CadInicializar ( p_cTmp, iPosTmp );
							iPosTmp = 0;
							iEstado = 3;
						}
						else if ( cCarFrm == '%' )
						{
							p_cCadena [ iPosCad ] = cCarFrm;
							iPosCad = iPosCad + 1;
							iEstado = 0;
						}
						else if ( cCarFrm == '(' )
						{
							CadInicializar ( p_cCod, 127 );
							iPosCod = 0;
							iEstado = 7;
						}
						else
						{
							p_cFrmProc [ iPosFrmP ] = cCarFrm;
							iPosFrmP = iPosFrmP + 1;
						}
						break;
					}
					case 2: // Procesando la anchura:
					{
						if ( ( cCarFrm >= '0' ) && ( cCarFrm <= '9' ) )
						{
							p_cTmp [ iPosTmp ] = cCarFrm;
							iPosTmp = iPosTmp + 1;
							p_cFrmProc [ iPosFrmP ] = cCarFrm;
							iPosFrmP = iPosFrmP + 1;
						}
						else if ( strchr ( _FRM_CODIGOS, cCarFrm ) != NULL )
						{
							iAnchura = atoi ( p_cTmp );
							CadInicializar ( p_cTmp, iPosTmp );
							iPosTmp = 0;
							iPosFrm = iPosFrm - 1;
							iEstado = 8;
						}
						else if ( cCarFrm == '.' )
						{
							iAnchura = atoi ( p_cTmp );
							CadInicializar ( p_cTmp, iPosTmp );
							iPosTmp = 0;
							p_cFrmProc [ iPosFrmP ] = cCarFrm;
							iPosFrmP = iPosFrmP + 1;
							iEstado = 4;
						}
						else
						{
							/* Posible error: */
							iAnchura = atoi ( p_cTmp );
							CadInicializar ( p_cTmp, iPosTmp );
							iPosTmp = 0;
							iEstado = 6;
						}
						break;
					}
					case 3: // Casos después de flag *:
					{
						if ( cCarFrm == '.' )
						{
							p_cFrmProc [ iPosFrmP ] = cCarFrm;
							iPosFrmP = iPosFrmP + 1;
							iEstado = 4;
						}
						else if ( strchr ( _FRM_CODIGOS, cCarFrm ) != NULL )
						{
							iPosFrm = iPosFrm - 1;
							iEstado = 8;
						}
						else
						{
							iEstado = 6;
      					}
						break;
					}
					case 4: // Procesando la precisión:
					{
						if ( ( cCarFrm >= '0' ) && ( cCarFrm <= '9' ) )
						{
							p_cTmp [ iPosTmp ] = cCarFrm;
							iPosTmp = iPosTmp + 1;
							p_cFrmProc [ iPosFrmP ] = cCarFrm;
							iPosFrmP = iPosFrmP + 1;
							iEstado = 5;
						}
						else if ( cCarFrm == '*' )
						{
							iPrecision  = va_arg ( valArgumentos, int );
							CadInicializar ( p_cTmp, iPosTmp );
							snprintf ( p_cTmp, _FRM_MAX_TAM_TMP + 1, "%d", iPrecision );
							for ( iPosTmp = 0; iPosTmp < CadLongitud ( p_cTmp ); iPosTmp = iPosTmp + 1 )
							{
								p_cFrmProc [ iPosFrmP ] = p_cTmp [ iPosTmp ];
								iPosFrmP = iPosFrmP + 1;
							}
							CadInicializar ( p_cTmp, iPosTmp );
							iPosTmp = 0;
							iEstado = 6;
						}
						else if ( strchr ( _FRM_CODIGOS, cCarFrm ) != NULL )
						{
							iPosFrm = iPosFrm - 1;
							iEstado = 8;
						}
						else
						{
							p_cFrmProc [ iPosFrmP ] = cCarFrm;
							iPosFrmP = iPosFrmP + 1;
							iEstado = 6;
						}
						break;
					}
					case 5: // Procesando la precisión:
					{
						if ( ( cCarFrm >= '0' ) && ( cCarFrm <= '9' ) )
						{
							p_cTmp [ iPosTmp ] = cCarFrm;
							iPosTmp = iPosTmp + 1;
							p_cFrmProc [ iPosFrmP ] = cCarFrm;
							iPosFrmP = iPosFrmP + 1;
							//iEstado = 4;
						}
						else if ( strchr ( _FRM_CODIGOS, cCarFrm ) != NULL )
						{
							iPrecision = atoi ( p_cTmp );
							CadInicializar ( p_cTmp, iPosTmp );
							iPosTmp = 0;
							iPosFrm = iPosFrm - 1;
							iEstado = 8;
						}
						else
						{
							iPrecision = atoi ( p_cTmp );
							CadInicializar ( p_cTmp, iPosTmp );
							iPosTmp = 0;
							p_cFrmProc [ iPosFrmP ] = cCarFrm;
							iPosFrmP = iPosFrmP + 1;
							iEstado = 6;
						}
 						break;
					}
					case 6: // Procesando Fin de precision ():
					{
						if ( strchr ( _FRM_CODIGOS, cCarFrm ) != NULL )
						{
							iPosFrm = iPosFrm - 1;
							iEstado = 8;
						}
						else
						{
							p_cFrmProc [ iPosFrmP ] = cCarFrm;
							iPosFrmP = iPosFrmP + 1;
						}
						break;
					}
					case 7: // Procesando Fin de codificacion ():
					{
						if ( cCarFrm == ')' )
						{
							iPosCod = 0;
							iEstado = 8;
						}
						else
						{
							p_cCod [ iPosCod ] = cCarFrm;
							iPosCod = iPosCod + 1;
						}
						break;
					}
					case 8: // Procsesando el tipo:
					{
						if ( iAnchura < iPrecision )
						{
							iMaxAncho = iPrecision;
						}
						else
						{
							iMaxAncho = iAnchura;
						}
						CadInicializar ( p_cBuffer, CAD_BASE_MAX_TAM );
						if ( ( cCarFrm == 's' ) || ( cCarFrm == 'S' ) )
						{
							//p_vArg = va_arg (valArgumentos, void * );
							p_cArg = va_arg ( valArgumentos, char * );

							if ( _EsCadenaValida ( p_cArg ) == 1 )
							{
								/*
								if ( CadLongitud ( p_cArg, 127 ) > 0 )
								{
									// FALTA:
									//p_vCod = Codificar ( p_cCod, p_vArg );
									//iMaxAncho = iMaxAncho + CadLongitud ( p_cFrmProc, CAD_BASE_MAX_TAM ) + Len ( p_vCod );
									//p_vCod = NULL;

								iMaxAncho = iMaxAncho + CadLongitud ( p_cFrmProc, CAD_BASE_MAX_TAM ) + CadLongitud ( p_cArg, 255 );
								}
								else
								{
									//p_vCod = NULL;
									iMaxAncho = iMaxAncho + CadLongitud ( p_cFrmProc, CAD_BASE_MAX_TAM ) + CadLongitud ( p_cArg, );
								}
								*/
								p_cFrmProc [ iPosFrmP ] = 's';
								iPosFrmP = iPosFrmP + 1;
								p_cFrmProc [ iPosFrmP ] = (char) 0;
								if ( iMaxAncho < CAD_BASE_MAX_TAM )
								{
									/*
									if ( ES_VALIDO ( p_vCod ) )
									{
										snprintf ( p_cBuffer, CAD_BASE_MAX_TAM + 1, p_cFrmProc, p_vCod );
										??MemLiberar ( &p_vCod );
									}
									else
									{
									*/
									snprintf ( p_cBuffer, CAD_BASE_MAX_TAM + 1, p_cFrmProc, p_cArg );
									CadInicializar ( p_cFrmProc, iPosFrmP );
									//}
								}
								else
								{
									snprintf ( p_cBuffer, CAD_BASE_MAX_TAM + 1, "%s", CAD_BASE_TXT_DEMASIADO_LARGO );
									CadInicializar ( p_cFrmProc, iPosFrmP );
								}
							}
							else
							{
								snprintf ( p_cBuffer, CAD_BASE_MAX_TAM + 1, "%s", CAD_BASE_TXT_VALOR_NULO );
								CadInicializar ( p_cFrmProc, iPosFrmP );
							}
							iPosBuf = 0;
							while ( ( iPosBuf < CadLongitud ( p_cBuffer ) ) &&
									( iPosCad < iMaxTam ) )
							{
								p_cCadena [ iPosCad ] = p_cBuffer [ iPosBuf ];
								iPosCad = iPosCad + 1;
								iPosBuf = iPosBuf + 1;
							}
							iEstado = 0;
						}
						else
						{
							p_cFrmProc [ iPosFrmP ] = cCarFrm;
							iPosFrmP = iPosFrmP + 1;
							iMaxAncho = iMaxAncho + CadLongitud ( p_cFrmProc ) + 64;
							if ( iMaxAncho < CAD_BASE_MAX_TAM )
							{
								iLongEsc = 0;
								switch( cCarFrm )
								{
									case 'd':
									case 'i':
									case 'o':
									case 'u':
									case 'x':
									case 'X':
									case 'c':
									{
										if ( iIndLargo == 0 )
										{
											iArg = va_arg ( valArgumentos, int );
											iLongEsc = snprintf ( p_cBuffer, CAD_BASE_MAX_TAM + 1, p_cFrmProc, iArg );
										}
										else
										{
											lArg = va_arg ( valArgumentos, long );
											iLongEsc = snprintf ( p_cBuffer, CAD_BASE_MAX_TAM + 1, p_cFrmProc, lArg );
										}
										break;
									}
									case 'f':
									case 'g':
									case 'e':
									case 'E':
									case 'G':
									{
										dArg = va_arg ( valArgumentos, double );
										iLongEsc = snprintf ( p_cBuffer, CAD_BASE_MAX_TAM + 1, p_cFrmProc, dArg );
										break;
									}
									case 'p':
									{
										p_vArg = va_arg ( valArgumentos, void * );
										iLongEsc = snprintf ( p_cBuffer, CAD_BASE_MAX_TAM + 1, p_cFrmProc, p_vArg );
										break;
									}
									default:
									{
										iRes = 0;
									}
								}

								CadInicializar ( p_cFrmProc, iPosFrmP );

								/* snprintf devuelve lo que ocupaba la salida entera, y si no cabia la ha
								   truncado. La comprobacion de iMaxAncho de arriba no basta: un %f de un
								   double grande lleva hasta 309 cifras enteras y el margen es de 64. Antes
								   se escribia fuera de p_cBuffer; ahora falla como cuando no cabe la anchura. */
								if ( iLongEsc < 0 )
								{
									iRes = 0;
									iAnchura = 0;
									CadInicializar ( p_cBuffer, CAD_BASE_MAX_TAM );
								}
								else if ( iLongEsc > CAD_BASE_MAX_TAM )
								{
									iRes = 0;
									iAnchura = 0;
									CadInicializar ( p_cBuffer, CAD_BASE_MAX_TAM );
								}

								iLongBuf = CadLongitud ( p_cBuffer );
								iPosPun = 0;
								while ( ( iPosPun < iLongBuf )  && ( p_cBuffer [ iPosPun ] != '.' ) )
								{
									iPosPun = iPosPun + 1;
								}
								if ( iPosPun < iLongBuf )
								{
									if ( iAnchura <= 0 )
									{
										if ( iPrecision <= 0 )
										{
											iAnchura = iLongBuf;
										}
										else
										{
											if ( iPosPun + iPrecision <= iLongBuf )
											{
												iAnchura = iPosPun + iPrecision;
											}
											else
											{
												iAnchura = iLongBuf;
											}
										}
									}
									else if ( iAnchura < iLongBuf )
									{
										if ( iAnchura >= iPosPun )
										{
											iAnchura = iAnchura + 1;
											if ( iPrecision > 0 )
											{
												if ( iAnchura + iPrecision <= iLongBuf )
												{
													iAnchura = iAnchura + iPrecision;
												}
												else
												{
													iAnchura = iLongBuf;
												}
											}
											else
											{
												iAnchura = iAnchura + 1;
											}
										}
									}
									else
									{
										iAnchura = iLongBuf;
									}
								}
								else //No es real:
								{
									if ( iAnchura <= 0 )
									{
										iAnchura = iLongBuf;
									}
								}
								iPosBuf = 0;
								while ( ( iPosBuf < iAnchura ) &&
										( iPosCad < iMaxTam ) )
								{
									p_cCadena [ iPosCad ] = p_cBuffer [ iPosBuf ];
									iPosCad = iPosCad + 1;
									iPosBuf = iPosBuf + 1;
								}
								iEstado = 0;
								iAnchura = -1;
							}
							else
							{
								iRes = 0;
							}
						}
						break;
					}
					default:
					{
						iRes = 0;
					}
				}
				iPosFrm = iPosFrm + 1;
			}

			if ( ( iRes == 1 ) && ( iPosFrm < CadLongitud ( p_cFormato ) ) )
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
		ERROR_ESTABLECER ( ERR_PARAMETROS );
	}
	MemLiberar ( (void **) &p_cTmp );
	MemLiberar ( (void **) &p_cFrmProc );
	MemLiberar ( (void **) &p_cCod );
	MemLiberar ( (void **) &p_cBuffer );
	return ( iRes );
}


/* NOTA: Esta rutina es una estimación. Habría que hacerlo utilizando la codificación interna
   de representación de tipos */
static int _EsCadenaValida ( char * p_cCad )
{
	int		iPos;
	int		iRes;
	byte	byCod;

	if ( ES_VALIDO ( p_cCad ) )
	{
		iPos = 0;
		iRes = 1;
		while ( ( *( p_cCad + iPos ) != (char) 0 ) && ( iPos < CAD_BASE_MAX_TAM ) && ( iRes == 1 ) )
		{
			byCod = (byte)(*( p_cCad + iPos ));
			if ( ( byCod == 127 )  || ( ( byCod < 32 ) &&  ( ( byCod < 8 ) || ( byCod > 13 ) ) ) )
			{
				iRes = 0;
			}
			iPos = iPos + 1;
		}
		if ( iPos >= CAD_BASE_MAX_TAM )
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











