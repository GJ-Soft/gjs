#include "AplicacionConfig.h"
#include "SPropiedades.h"



int _EsPropiedad ( char * p_cLinea );
int _ParsearPropiedad ( char * p_cLinea, char ** p_p_cClave, char ** p_p_cValor );


SPropiedades * SPropCrearDef ()
{
	SPropiedades * p_propObj;
	
	p_propObj = (SPropiedades *) MemReservar ( sizeof ( SPropiedades ) );
	if ( ES_VALIDO ( p_propObj ) )
	{
		p_propObj->p_lislitClaves = SLisLitCrear();
		p_propObj->p_lisentPropiedades = SLisEtrCrear();
		if ( ES_NULO ( p_propObj->p_lislitClaves ) || ES_NULO ( p_propObj->p_lisentPropiedades ) )
		{
			SPropDestruir ( &p_propObj );
		}
	}
	return ( p_propObj );
}

SPropiedades * SPropCrear ( const char * p_cRuta )
{
	SPropiedades * p_propObj;
	
	p_propObj = SPropCrearDef ();
	if ( ES_VALIDO ( p_propObj ) )
	{
		SPropCargar ( p_propObj, p_cRuta ); 
	}
	return ( p_propObj );
}

void SPropDestruir ( SPropiedades ** p_p_propObj )
{
	SPropiedades * p_propObj;
	
	if ( ES_VALIDO ( p_p_propObj ) )
	{
		p_propObj = *p_p_propObj;

		if ( ES_VALIDO ( p_propObj ) )
		{
			SLisLitDestruir ( &(p_propObj->p_lislitClaves) );
			//SLisEtrDestruir ( &(p_propObj->p_lisentPropiedades) );
			MemLiberar ( (void **) p_p_propObj );
		}
	}
}

const char * SPropObtPropiedad ( SPropiedades * p_propObj, const char * p_cClave )
{
    return ( SPropObtPropiedadExt ( p_propObj, p_cClave, NULL ) );
}

const char * SPropObtPropiedadExt ( SPropiedades * p_propObj, const char * p_cClave, const char * p_cValorDef )
{
	SEntrada * 		p_etrObj;
	const char * 	p_cRes;
	
	if ( ES_VALIDO ( p_propObj ) && ES_VALIDO ( p_cClave ) )
	{	
		p_etrObj = SLisEtrBuscar ( p_propObj->p_lisentPropiedades, p_cClave );
		if ( ES_VALIDO ( p_etrObj ) )
		{
			p_cRes = SEtrDefinicion ( p_etrObj );
		}
		else
		{
			p_cRes = p_cValorDef;
		}
	}
	else
	{
		p_cRes = p_cValorDef;
	}
    return ( p_cRes );
}

int SPropEstPropiedad ( SPropiedades * p_propObj, const char * p_cClave, const char * p_cValor )
{
	SEntrada * 	p_etrObj;
	int 		iRes;
	
	if ( ES_VALIDO ( p_propObj ) && ES_VALIDO ( p_cClave ) && ES_VALIDO ( p_cValor ) )
	{	
		p_etrObj = SLisEtrBuscar ( p_propObj->p_lisentPropiedades, p_cClave );
		if ( ES_VALIDO ( p_etrObj ) )
		{
			iRes = SEtrEstablecerDefinicion ( p_etrObj, p_cValor );
		}
		else
		{
			p_etrObj = SEtrCrearExt ( p_cClave, p_cValor );
			if ( ES_VALIDO ( p_etrObj ) )
			{
				if ( SLisEtrInsertar ( p_propObj->p_lisentPropiedades, p_etrObj ) == 1 )
				{
					SLisLitInsertarDupAlFinal ( p_propObj->p_lislitClaves, p_cClave );
					iRes = 1;
				} 
				else
				{
					SEtrDestruir ( &p_etrObj );
					iRes = 0;
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
	return ( iRes );
}

SListaLiterales * SPropPropiedades ( SPropiedades * p_propObj )
{
 	SListaLiterales * p_lislitRes;
	
	if ( ES_VALIDO ( p_propObj ) )
	{	
		p_lislitRes = p_propObj->p_lislitClaves;
	}
	else
	{
		p_lislitRes = NULL;
	}
    return ( p_lislitRes );
}

int SPropExistePropiedad ( SPropiedades * p_propObj, const char * p_cClave )
{
 	int iRes;
	
	if ( ES_VALIDO ( p_propObj ) )
	{	
		iRes = SLisLitExiste ( p_propObj->p_lislitClaves, p_cClave );
	}
	else
	{
		iRes = 0;
	}
    return ( iRes );
}

int SPropNumPropiedades ( SPropiedades * p_propObj )
{
 	int iRes;
	
	if ( ES_VALIDO ( p_propObj ) )
	{	
		iRes = SLisLitNumElementos ( p_propObj->p_lislitClaves);
	}
	else
	{
		iRes = 0;
	}
    return ( iRes );
}

void SPropEliminarPropiedad ( SPropiedades * p_propObj, const char * p_cClave )
{
	if ( ES_VALIDO ( p_propObj ) && ES_VALIDO ( p_cClave ) )
	{	
		if ( SLisEtrEliminar ( p_propObj->p_lisentPropiedades, p_cClave ) == 1 )
		{
			SLisLitEliminarElem ( p_propObj->p_lislitClaves, SLisLitBuscar ( p_propObj->p_lislitClaves, p_cClave ) );
		}
	}
}


int _EsPropiedad ( char * p_cLinea )
{
	int iRes;
	int iPos;

	CadFormatearBlancos ( p_cLinea );
	iPos = CadBuscarCaracter ( p_cLinea, '=', 0 );
	if ( iPos > 0 )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
    return ( iRes );
}

int _ParsearPropiedad ( char * p_cLinea, char ** p_p_cClave, char ** p_p_cValor )
{
	int iRes;
	int iPos;

	CadFormatearBlancos ( p_cLinea );
	iPos = CadBuscarCaracter ( p_cLinea, '=', 0 );
	if ( iPos > 0 )
	{
		*p_p_cClave = CadExtraerPrimeros ( p_cLinea, iPos );
		*p_p_cValor = CadExtraerUltimos ( p_cLinea, CadLongitud ( p_cLinea ) - iPos - 1 );
		CadFormatearBlancos ( *p_p_cClave );
		CadFormatearBlancos ( *p_p_cValor );
		if ( ( CadEmpiezaPorCaracter ( *p_p_cValor, '"' ) == 1 ) && 
			( CadAcabaPorCaracter ( *p_p_cValor, '"' ) == 1 ) )
		{
			*p_p_cValor = CadExtraer ( *p_p_cValor, 1, CadLongitud ( *p_p_cValor ) - 2 );
		}
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SPropCargar ( SPropiedades * p_propObj, const char * p_cRuta )
{
	int			iRes;
	SFicTexto * p_ficProp;
	char *		p_cLinea;
	char *		p_cClave;
	char *		p_cValor;
	int			iNumLinea;

	if ( ES_VALIDO ( p_propObj ) )
	{
		p_ficProp = SFicTxtCrear ( p_cRuta );
		if ( ES_VALIDO ( p_ficProp ) )
		{
			if ( SFicTxtAbrir ( p_ficProp, MOD_APR_LECTURA ) == 1 )
			{
				iNumLinea = 0;
				iRes = 1;
				p_cClave = NULL;
				p_cValor = NULL;
				p_cLinea = NULL;
				while ( SFicTxtEstaEnFinal ( p_ficProp ) == 0 )
				{
					MemLiberarCadena ( &p_cLinea );
					p_cLinea = SFicTxtLeerLinea ( p_ficProp );
					if ( ES_VALIDO ( p_cLinea ) )
					{
						if ( _EsPropiedad ( p_cLinea ) == 1 )
						{
							if ( _ParsearPropiedad ( p_cLinea, &p_cClave, &p_cValor ) == 1 )
							{
								SPropEstPropiedad ( p_propObj, p_cClave, p_cValor );
							}
							MemLiberar ( (void **) &p_cClave );
							MemLiberar ( (void **) &p_cValor );
						}
						iNumLinea = iNumLinea + 1;
					}
				}
				SFicTxtCerrar ( p_ficProp );
			}
			else
			{
				ERROR_ESTABLECER ( ERR_IMPOSIBLE_ABRIR_FICHERO );
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
		ERROR_ESTABLECER ( ERR_PARAMETROS );
		iRes = 0;
	}
	return ( iRes );
}

int SPropGuardar ( SPropiedades * p_propObj, const char * p_cRuta )
{
	int			iRes;
	SFicTexto * p_ficProp;
	SEntrada *	p_etrObj;
	char *		p_cLinea;
	char *		p_cClave;
	char *		p_cValor;
	int			iLiberar;
	int			iNumElems;

	if ( ES_VALIDO ( p_propObj ) )
	{
		p_ficProp = SFicTxtCrear ( p_cRuta );
		if ( ES_VALIDO ( p_ficProp ) )
		{
			if ( SFicTxtAbrir ( p_ficProp, MOD_APR_REESCRITURA ) == 1 )
			{
				iRes = 1;
				iNumElems = SLisEtrNumElementos ( p_propObj->p_lisentPropiedades );
				for ( int iElem = 0; iElem < iNumElems; iElem = iElem + 1 )
				{
					iLiberar = 0;
					p_etrObj = SLisEtrElemento ( p_propObj->p_lisentPropiedades, iElem );
					if ( ES_VALIDO ( p_etrObj ) )
					{
						p_cClave = (char *) SEtrNombre ( p_etrObj );
						p_cValor = (char *) SEtrDefinicion ( p_etrObj );
						if ( ( CadEmpiezaPorCaracter ( p_cValor, ' ' ) == 1 ) ||
							( CadAcabaPorCaracter ( p_cValor, ' ' ) == 1 ) )
						{
							iLiberar = 1;
							p_cValor = CadEnvolver ( p_cValor, '"' );
						}
						p_cLinea = CadComponer ( p_cClave, p_cValor, '=' );
						if ( SFicTxtEscribirLinea ( p_ficProp, p_cLinea ) == 0 )
						{
							iRes = 0;
						}
						MemLiberar ( ( void ** ) &p_cLinea );
						if ( iLiberar == 1 )
						{
							MemLiberar ( ( void ** ) &p_cValor );
						}
					}
					else
					{
						iRes = 0;
					}
				}
				SFicTxtCerrar ( p_ficProp );
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


