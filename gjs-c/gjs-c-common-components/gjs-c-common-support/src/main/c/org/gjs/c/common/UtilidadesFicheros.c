#include "AplicacionConfig.h"
#include "UtilidadesFicheros.h"



/* Valida que un fichero de texto contiene exactamente las lineas esperadas, en
   ese orden. Se ignoran las lineas vacias (p. ej. un salto final), de modo que
   la comprobacion es robusta frente al terminador de linea. Devuelve
   BOOL_VAL_CIERTO si coincide, BOOL_VAL_FALSO en caso contrario. */
int FicTxtContenidoCoincide ( const char * p_cRuta, const char ** p_p_cLineas, int iNumLineas )
{
	int iRes = BOOL_VAL_CIERTO;
	int iLinea = 0;

	SFicTexto * p_ficObj = SFicTxtCrear ( p_cRuta );
	if ( ES_NULO ( p_ficObj ) )
	{
		return ( BOOL_VAL_FALSO );
	}
	if ( SFicTxtAbrir ( p_ficObj, MOD_APR_LECTURA ) != 1 )
	{
		SFicTxtDestruir ( &p_ficObj );
		return ( BOOL_VAL_FALSO );
	}
	while ( SFicTxtEstaEnFinal ( p_ficObj ) == 0 )
	{
		char * p_cLinea = SFicTxtLeerLinea ( p_ficObj );
		if ( ES_VALIDO ( p_cLinea ) && ( CadLongitud ( p_cLinea ) > 0 ) )
		{
			if ( ( iLinea >= iNumLineas ) || ( CadComparar ( p_cLinea, p_p_cLineas [ iLinea ] ) != COMP_IGUAL ) )
			{
				iRes = BOOL_VAL_FALSO;
			}
			iLinea = iLinea + 1;
		}
		MemLiberar ( (void **) &p_cLinea );
	}
	SFicTxtCerrar ( p_ficObj );
	SFicTxtDestruir ( &p_ficObj );

	if ( iLinea != iNumLineas )
	{
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

