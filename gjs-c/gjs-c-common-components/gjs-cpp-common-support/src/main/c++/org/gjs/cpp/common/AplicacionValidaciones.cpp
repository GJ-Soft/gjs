#include "AplicacionValidaciones.h"

#include "CommonSupportConfig.h"



using namespace std;

namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {



bool AplicCodigoValido ( const string & sCod, int iTam )
{
	int iLong;
	bool bRes = false;
	int iCar;

	iLong = sCod.length ();
	if ( ( iTam > 0 ) && ( iLong == iTam ) )
	{
		bRes = true;
		iCar = 0;
		while ( ( iCar < iLong ) && bRes )  
		{
			if ( !isalnum( sCod [ iCar ] ) &&  ( sCod [ iCar ] != '_' ) ) 
			{
				bRes = false;
			}
			iCar = iCar + 1;
		}
	}
	return ( bRes );
}

bool AplicCodigoUsuarioValido ( const string & sCod )
{
	int iLong;
	bool bRes = false;
	int iCar;

	iLong = sCod.length ();
	if ( ( iLong >= APL_MIN_TAM_COD_USUARIO ) && ( iLong <= APL_MAX_TAM_COD_USUARIO ) )
	{
		bRes = true;
		iCar = 0;
		while ( ( iCar < iLong ) && bRes )  
		{
			if ( !isalnum( sCod [ iCar ] ) &&  ( sCod [ iCar ] != '_' ) ) 
			{
				bRes = false;
			}
			iCar = iCar + 1;
		}
	}
	return ( bRes );
}

bool AplicClaveUsuarioValido ( const string & sClave )
{
	int iLong;
	bool bRes = false;
	int iCar;

	iLong = sClave.length ();
	if ( iLong <= APL_MAX_TAM_CLV_USUARIO )
	{
		bRes = true;
		iCar = 0;
		while ( ( iCar < iLong ) && bRes )  
		{
			if ( ! isprint( sClave [ iCar ] ) )
			{
				bRes = false;
			}
			iCar = iCar + 1;
		}
	}
	return ( bRes );
}



 			}
		}
	}
}
