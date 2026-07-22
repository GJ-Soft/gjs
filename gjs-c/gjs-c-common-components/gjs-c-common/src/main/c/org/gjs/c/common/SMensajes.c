#include "SMensajes.h"

#include "CommonConfig.h"

#include <SEntidadId.h>
#include <SFicTexto.h>




SMensajes * SMsjCrear ()
{
	SMensajes * p_msjObj;

	p_msjObj = ( SMensajes * ) MemReservar ( sizeof ( SMensajes ) );
	if ( ES_VALIDO ( p_msjObj ) )
	{
		p_msjObj->p_lisMensajes = SLispCrear ();
		if ( ES_VALIDO ( p_msjObj->p_lisMensajes ) )
		{
			SLispDesactivarLiberacionMemoria ( p_msjObj->p_lisMensajes );
		}
		else
		{
			MemLiberar ( ( void ** ) &p_msjObj );
		}
	}
	return ( p_msjObj );
}

void SMsjDestruir ( SMensajes ** p_p_msjObj )
{
	SMensajes * 	p_msjObj;

	if ( ES_VALIDO ( p_p_msjObj ) )
	{
		p_msjObj = *p_p_msjObj;
		if ( ES_VALIDO ( p_msjObj ) )
		{
			SMsjLimpiar ( p_msjObj );
			SLispDestruir ( &( p_msjObj->p_lisMensajes ) );
			MemLiberar ( ( void ** ) p_p_msjObj );
		}
	}
}

int SMsjInsertar ( SMensajes * p_msjObj, unsigned long ulCodigo, SCadena * p_cadTexto )
{
	int				iRes;
	SEntidadId *	p_entDatos;

	if ( ES_VALIDO ( p_msjObj ) && ( ulCodigo > 0 ) && ( SCadLongitud ( p_cadTexto ) > 0 ) )
	{
		if ( SMsjExisteCodigo ( p_msjObj, ulCodigo ) == 0 )
		{
			p_entDatos = SEntIdEncapsular ( ulCodigo, p_cadTexto );
			if ( ES_VALIDO ( p_entDatos ) )
			{
				iRes = SLispInsertarDetras ( p_msjObj->p_lisMensajes, ( void * ) p_entDatos );
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

int SMsjInsertarLit ( SMensajes * p_msjObj, unsigned long ulCodigo, const char * p_cTexto )
{
	int 		iRes;
	SCadena *	p_cadTexto;
	
	p_cadTexto = SCadGenerar ( p_cTexto );
	if ( SMsjInsertar ( p_msjObj, ulCodigo, p_cadTexto ) == 1 )
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

int SMsjExisteCodigo ( SMensajes * p_msjObj, unsigned long ulCodigo )
{
	int				iRes;
	int				iEnc;
	int 			iFin;
	SEntidadId *	p_entDatos;

	if ( ES_VALIDO ( p_msjObj ) )
	{
		iEnc = 0;
		iFin = 0;
		SLispInicio ( p_msjObj->p_lisMensajes );
		while ( ( iEnc == 0 ) && ( iFin == 0 ) )
		{
			p_entDatos = ( SEntidadId * ) SLispActual ( p_msjObj->p_lisMensajes );
			if ( SEntIdId ( p_entDatos ) == ulCodigo )
			{
				iEnc = 1;
			}
			else if ( SLispEstaEnFinal ( p_msjObj->p_lisMensajes ) == 1 )
			{
				iFin = 1;
			}
			else
			{
				SLispSiguiente ( p_msjObj->p_lisMensajes );
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

int SMsjNumMensajes ( SMensajes * p_msjObj )
{
	int	iRes;

	if ( ES_VALIDO ( p_msjObj ) )
	{
		iRes = SLispNumElementos ( p_msjObj->p_lisMensajes );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}


SCadena * SMsjTexto ( SMensajes * p_msjObj, unsigned long ulCodigo )
{
	SEntidadId *	p_entDatos;
	SCadena *		p_cadTexto;
	int				iEnc;
	int 			iFin;

	if ( ES_VALIDO ( p_msjObj ) )
	{
		p_cadTexto = NULL;
		iEnc = 0;
		iFin = 0;
		SLispInicio ( p_msjObj->p_lisMensajes );
		while ( ( iEnc == 0 ) && ( iFin == 0 ) )
		{
			p_entDatos = ( SEntidadId * ) SLispActual ( p_msjObj->p_lisMensajes );
			if ( SEntIdId ( p_entDatos ) == ulCodigo )
			{
				iEnc = 1;
				p_cadTexto = SEntIdNombre ( p_entDatos );
			}
			else if ( SLispEstaEnFinal ( p_msjObj->p_lisMensajes ) == 1 )
			{
				iFin = 1;
			}
			else
			{
				SLispSiguiente ( p_msjObj->p_lisMensajes );
			}
		}
	}
	else
	{
		p_cadTexto = NULL;
	}
	return ( p_cadTexto );
}

void SMsjLimpiar ( SMensajes * p_msjObj )
{
	SEntidadId *	p_entObj;
	int				iNumElems;

	if ( ES_VALIDO ( p_msjObj ) )
	{
		iNumElems = SLispNumElementos ( p_msjObj->p_lisMensajes );
		for ( int iElem = 0; iElem < iNumElems; iElem = iElem + 1 )
		{
			p_entObj = ( SEntidadId * ) SLispElemento ( p_msjObj->p_lisMensajes, iElem );
			SEntIdDestruir ( &p_entObj );
		}
		SLispVaciar ( p_msjObj->p_lisMensajes );
	}
}

int SMsjCargar ( SMensajes * p_msjObj, const char * p_cFichero )
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
						SCadEliminarBlancos ( p_cadLinea );
						if ( SCadLongitud ( p_cadLinea ) > 0 )
						{
							iSep = SCadBuscarCaracter ( p_cadLinea, ' ', 0 );
							if ( iSep > 0 )
							{
								p_cadCodigoAux = SCadExtraerPrimeros ( p_cadLinea, iSep );
								p_cadTexto = SCadExtraerUltimos ( p_cadLinea, SCadLongitud ( p_cadLinea ) - iSep - 1 );

								SCadEliminarBlancos ( p_cadCodigoAux );
								SCadEliminarBlancos ( p_cadTexto );

								p_cadCodigo = SCadcCrearCad ( p_cadCodigoAux );
								if ( SCadcEsNumerica ( p_cadCodigo ) == 1 )
								{
									ulCodigo = SCadcValorEntero ( p_cadCodigo );
									iCargado = SMsjInsertar ( p_msjObj, ulCodigo, p_cadTexto );
								}

								SCadcDestruir ( & p_cadCodigo );
								SCadDestruir ( &p_cadCodigoAux );
								if ( iCargado == 0 )
								{
									SCadDestruir ( &p_cadTexto );
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

