#include "SMensajes.h"

#include "CommonConfig.h"

#include <SMensaje.h>
#include <SFicTexto.h>




SMensajes * SMsjsCrear ()
{
	SMensajes * p_msjsObj;

	p_msjsObj = ( SMensajes * ) MemReservar ( sizeof ( SMensajes ) );
	if ( ES_VALIDO ( p_msjsObj ) )
	{
		p_msjsObj->p_lisMensajes = SLispCrear ();
		if ( ES_VALIDO ( p_msjsObj->p_lisMensajes ) )
		{
			SLispDesactivarLiberacionMemoria ( p_msjsObj->p_lisMensajes );
		}
		else
		{
			MemLiberar ( ( void ** ) &p_msjsObj );
		}
	}
	return ( p_msjsObj );
}

void SMsjsDestruir ( SMensajes ** p_p_msjsObj )
{
	SMensajes * 	p_msjsObj;

	if ( ES_VALIDO ( p_p_msjsObj ) )
	{
		p_msjsObj = *p_p_msjsObj;
		if ( ES_VALIDO ( p_msjsObj ) )
		{
			SMsjsLimpiar ( p_msjsObj );
			SLispDestruir ( &( p_msjsObj->p_lisMensajes ) );
			MemLiberar ( ( void ** ) p_p_msjsObj );
		}
	}
}

int SMsjsInsertar ( SMensajes * p_msjsObj, unsigned long ulCodigo, SCadena * p_cadTexto )
{
	int			iRes;
	SMensaje *	p_msjDatos;

	if ( ES_VALIDO ( p_msjsObj ) && ( ulCodigo > 0 ) && ( SCadLongitud ( p_cadTexto ) > 0 ) )
	{
		if ( SMsjsExisteCodigo ( p_msjsObj, ulCodigo ) == 0 )
		{
			p_msjDatos = SMsjCrear ( ulCodigo, p_cadTexto );
			if ( ES_VALIDO ( p_msjDatos ) )
			{
				iRes = SLispInsertarDetras ( p_msjsObj->p_lisMensajes, ( void * ) p_msjDatos );
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

int SMsjsInsertarLit ( SMensajes * p_msjsObj, unsigned long ulCodigo, const char * p_cTexto )
{
	int 		iRes;
	SCadena *	p_cadTexto;
	
	p_cadTexto = SCadGenerar ( p_cTexto );
	if ( SMsjsInsertar ( p_msjsObj, ulCodigo, p_cadTexto ) == 1 )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
		SCadDestruir ( &p_cadTexto );
	}
	return ( iRes );
}

int SMsjsExisteCodigo ( SMensajes * p_msjsObj, unsigned long ulCodigo )
{
	int				iRes;
	int				iEnc;
	int 			iFin;
	SMensaje *	p_msjDatos;

	if ( ES_VALIDO ( p_msjsObj ) )
	{
		iEnc = 0;
		iFin = 0;
		SLispInicio ( p_msjsObj->p_lisMensajes );
		while ( ( iEnc == 0 ) && ( iFin == 0 ) )
		{
			p_msjDatos = ( SMensaje * ) SLispActual ( p_msjsObj->p_lisMensajes );
			if ( SMsjValorId ( p_msjDatos ) == ulCodigo )
			{
				iEnc = 1;
			}
			else if ( SLispEstaEnFinal ( p_msjsObj->p_lisMensajes ) == 1 )
			{
				iFin = 1;
			}
			else
			{
				SLispSiguiente ( p_msjsObj->p_lisMensajes );
			}
		}
		iRes = iEnc;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SMsjsNumMensajes ( SMensajes * p_msjsObj )
{
	int	iRes;

	if ( ES_VALIDO ( p_msjsObj ) )
	{
		iRes = SLispNumElementos ( p_msjsObj->p_lisMensajes );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}


SCadena * SMsjsTexto ( SMensajes * p_msjsObj, unsigned long ulCodigo )
{
	SMensaje *	p_msjDatos;
	SCadena *	p_cadTexto;
	int			iEnc;
	int 		iFin;

	if ( ES_VALIDO ( p_msjsObj ) )
	{
		p_cadTexto = NULL;
		iEnc = 0;
		iFin = 0;
		SLispInicio ( p_msjsObj->p_lisMensajes );
		while ( ( iEnc == 0 ) && ( iFin == 0 ) )
		{
			p_msjDatos = ( SMensaje * ) SLispActual ( p_msjsObj->p_lisMensajes );
			if ( SMsjValorId ( p_msjDatos ) == ulCodigo )
			{
				iEnc = 1;
				p_cadTexto = SMsjValorTexto ( p_msjDatos );
			}
			else if ( SLispEstaEnFinal ( p_msjsObj->p_lisMensajes ) == 1 )
			{
				iFin = 1;
			}
			else
			{
				SLispSiguiente ( p_msjsObj->p_lisMensajes );
			}
		}
	}
	else
	{
		p_cadTexto = NULL;
	}
	return ( p_cadTexto );
}

void SMsjsLimpiar ( SMensajes * p_msjsObj )
{
	SMensaje *	p_msjObj;
	int			iNumElems;

	if ( ES_VALIDO ( p_msjsObj ) )
	{
		iNumElems = SLispNumElementos ( p_msjsObj->p_lisMensajes );
		for ( int iElem = 0; iElem < iNumElems; iElem = iElem + 1 )
		{
			p_msjObj = ( SMensaje * ) SLispElemento ( p_msjsObj->p_lisMensajes, iElem );
			SMsjDestruir ( &p_msjObj );
		}
		SLispVaciar ( p_msjsObj->p_lisMensajes );
	}
}

int SMsjsCargar ( SMensajes * p_msjsObj, const char * p_cFichero )
{
	int					iRes;
	SFicTexto *			p_ficMsj;
	const char *		p_cLinea;
	SCadena *			p_cadLinea;
	SCadena *			p_cadCodigoAux;
	SCadenaConv *		p_cadCodigo;
	SCadena *			p_cadTexto;
	int					iSep;
	unsigned long		ulCodigo;
	int					iCargado;
	
	p_ficMsj = SFicTxtCrear ( p_cFichero );
	if ( ES_VALIDO ( p_ficMsj ) )
	{
		if ( SFicTxtAbrir ( p_ficMsj, MOD_APR_LECTURA ) == 1 )
		{
			iRes = 1;
			while ( ( SFicTxtEstaEnFinal ( p_ficMsj ) == 0 ) && ( iRes == 1 ) )
			{
				p_cLinea = SFicTxtLeerLinea ( p_ficMsj );
				if ( ES_VALIDO ( p_cLinea ) )
				{
					iCargado = 0;
					p_cadLinea = SCadGenerar ( p_cLinea );
					if ( ES_VALIDO ( p_cadLinea ) )
					{
						SCadEliminarBlancosLaterales ( p_cadLinea );
						if ( SCadLongitud ( p_cadLinea ) > 0 )
						{
							iSep = SCadBuscarCaracter ( p_cadLinea, ' ', 0 );
							if ( iSep > 0 )
							{
								p_cadCodigoAux = SCadExtraerPrimeros ( p_cadLinea, iSep );
								p_cadTexto = SCadExtraerUltimos ( p_cadLinea, SCadLongitud ( p_cadLinea ) - iSep - 1 );

								SCadEliminarBlancosLaterales ( p_cadCodigoAux );
								SCadEliminarBlancosLaterales ( p_cadTexto );

								p_cadCodigo = SCadcCrearCad ( p_cadCodigoAux );
								if ( SCadcEsNumerica ( p_cadCodigo ) == 1 )
								{
									ulCodigo = SCadcValorEntero ( p_cadCodigo );
									iCargado = SMsjsInsertar ( p_msjsObj, ulCodigo, p_cadTexto );
								}

								SCadcDestruir ( & p_cadCodigo );
								SCadDestruir ( &p_cadCodigoAux );
								if ( iCargado == 0 )
								{
									SCadDestruir ( &p_cadTexto );
									iRes = 0;
								}
							}
						}
						
						SCadDestruir ( &p_cadLinea );
					}
					else
					{
						iRes = 0;
					}
					MemLiberar ( (void **) &p_cLinea );
				}
			}
			SFicTxtCerrar ( p_ficMsj );
		}
		else
		{
			iRes = 0;
		}
		SFicTxtDestruir ( &p_ficMsj );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

