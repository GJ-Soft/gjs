#include "AplicacionValidaciones.h"

#include "AplicacionConfig.h"



int AplicCodigoValido ( const char * p_cCod, int iTam )
{
	int iLong;
	int iRes;
	int iCar;

	iLong = CadLongitud ( p_cCod );
	if ( ( iTam > 0 ) && ( iLong == iTam ) )
	{
		iRes = 1;
		iCar = 0; 
		while ( ( iCar < iLong ) && ( iRes == 1 ) )  
		{
			if ( ( ASCIIPerteneceAlJuegoPrincipal ( p_cCod [ iCar ] ) == 0 ) ||
				 ( ( ASCIIEsLetra ( p_cCod [ iCar ] ) == 0 ) && ( ASCIIEsDigito ( p_cCod [ iCar ] ) == 0 ) ) )
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
	return ( iRes );
}

int AplicCodigoUsuarioValido ( const char * p_cCod )
{
	int iLong;
	int iRes;
	int iCar;

	iLong = CadLongitud ( p_cCod );
	if ( ( iLong >= APL_MIN_TAM_COD_USUARIO ) && ( iLong <= APL_MAX_TAM_COD_USUARIO ) )
	{
		iRes = 1;
		iCar = 0; 
		while ( ( iCar < iLong ) && ( iRes == 1 ) )  
		{
			if ( ( ASCIIPerteneceAlJuegoPrincipal ( p_cCod [ iCar ] ) == 0 ) ||
				 ( ( ASCIIEsLetra ( p_cCod [ iCar ] ) == 0 ) && ( ASCIIEsDigito ( p_cCod [ iCar ] ) == 0 ) && 
				   ( ASCIIEsGuionBajo ( p_cCod [ iCar ] ) == 0 ) ) )
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
	return ( iRes );
}

int AplicClaveUsuarioValido ( const char * p_cClave )
{
	int iLong;
	int iRes;
	int iCar;

	iLong = CadLongitud ( p_cClave );
	// NOTA: Se admite clave vacia
	if ( iLong <= APL_MAX_TAM_CLV_USUARIO )
	{
		iRes = 1;
		iCar = 0; 
		while ( ( iCar < iLong ) && ( iRes == 1 ) )  
		{
			if ( ( ASCIIPerteneceAlJuegoPrincipal ( p_cClave [ iCar ] ) == 0 ) ||
				 ( ( ASCIIEsLetra ( p_cClave [ iCar ] ) == 0 ) && ( ASCIIEsDigito ( p_cClave [ iCar ] ) == 0 ) && 
				   ( ASCIIEsGuionBajo ( p_cClave [ iCar ] ) == 0 ) ) )
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
	return ( iRes );
}


