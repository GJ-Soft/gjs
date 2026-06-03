/******************************************************************************/
/*                                 ASCII.cpp                                  */
/*----------------------------------------------------------------------------*/
/* Librería:  GTexto                                                          */
/* Versión:   1.0.0                                                           */
/* Fecha:     30/06/2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Fichero de código fuente que contiene la implementación de las rutinas     */
/* de carácter general de consulta y conversión de carácteres en la           */
/* codificación ASCII.                                                        */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#include "ASCII.h"
#include <ASCIIEstandar.h>





#define ASCII_MIN_LETRA_MIN 		ASCII_A_MIN
#define ASCII_MAX_LETRA_MIN 		ASCII_Z_MIN
#define ASCII_MIN_LETRA_MAY			ASCII_A_MAY
#define ASCII_MAX_LETRA_MAY 		ASCII_Z_MAY
#define ASCII_DESPLAZAMIENTO_MAY	( ASCII_A_MAY - ASCII_A_MIN )






/* Rutinas: */
int ASCIIPerteneceAlJuegoPrincipal ( char cVal )
{
	int iRes; 
	int iCod;

	iCod = ASCIICodigo ( cVal );	
	if ( ( iCod >= 0 ) && ( iCod <= 127 ) ) 
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}


int ASCIIPerteneceAlJuegoSecundario ( char cVal )
{
	int iRes; 
	int iCod;

	iCod = ASCIICodigo ( cVal );	
	if ( iCod > 127 ) 
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}


int ASCIIEsLetra ( char cVal )
{
	int iRes;

	if ( ( ASCIIEsLetraMin ( cVal ) == 1 ) || 
		 ( ASCIIEsLetraMay ( cVal ) == 1 ) )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}


int ASCIIEsLetraMin ( char cVal )
{
	int iRes; 
	int iCod;

	iCod = ASCIICodigo ( cVal );	
	if ( ( ( iCod >= ASCII_MIN_LETRA_MIN ) && ( iCod <= ASCII_MAX_LETRA_MIN ) ) ||
		 ( ASCIIEsLetraMinConSigno ( cVal ) == 1 ) || 
		 ( ASCIIEsLetraMinNordica ( cVal ) == 1 ) || 
		 ( ASCIIEsLetraMinGriega ( cVal ) == 1 ) || 
		 ( ASCIIEsLetraMinEspecial ( cVal ) == 1 ) ) 
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}


int ASCIIEsLetraMay ( char cVal )
{
	int iRes; 
	int iCod;

	iCod = ASCIICodigo ( cVal );	
	if ( ( ( iCod >= ASCII_MIN_LETRA_MAY ) && ( iCod <= ASCII_MAX_LETRA_MAY ) ) ||
		 ( ASCIIEsLetraMayConSigno ( cVal ) == 1 ) || 
		 ( ASCIIEsLetraMayNordica ( cVal ) == 1 ) || 
		 ( ASCIIEsLetraMayGriega ( cVal ) == 1 ) || 
		 ( ASCIIEsLetraMayEspecial ( cVal ) == 1 ) ) 
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int ASCIIEsVocal ( char cVal )
{
	int iRes;

	if ( ( ASCIIEsVocalMin ( cVal ) == 1 ) || 
		 ( ASCIIEsVocalMay ( cVal ) == 1 ) )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}


int ASCIIEsVocalMin ( char cVal )
{
	int iRes; 
	int iCod;

	iCod = ASCIICodigo ( cVal );	
	if ( ( iCod == ASCII_A_MIN ) ||
		 ( iCod == ASCII_E_MIN ) ||
		 ( iCod == ASCII_I_MIN ) ||
		 ( iCod == ASCII_O_MIN ) ||
		 ( iCod == ASCII_U_MIN ) ||
  		 ( iCod == ASCII_A_MIN_CER ) ||
		 ( iCod == ASCII_E_MIN_CER ) ||
		 ( iCod == ASCII_I_MIN_CER ) ||
		 ( iCod == ASCII_O_MIN_CER ) ||
		 ( iCod == ASCII_U_MIN_CER ) ||	
  		 ( iCod == ASCII_A_MIN_ABI ) ||
		 ( iCod == ASCII_E_MIN_ABI ) ||
		 ( iCod == ASCII_I_MIN_ABI ) ||
		 ( iCod == ASCII_O_MIN_ABI ) ||
		 ( iCod == ASCII_U_MIN_ABI ) ||	
  		 ( iCod == ASCII_A_MIN_CIR ) ||
		 ( iCod == ASCII_E_MIN_CIR ) ||
		 ( iCod == ASCII_I_MIN_CIR ) ||
		 ( iCod == ASCII_O_MIN_CIR ) ||
		 ( iCod == ASCII_U_MIN_CIR ) ||	
  		 ( iCod == ASCII_A_MIN_DIE ) ||
		 ( iCod == ASCII_E_MIN_DIE ) ||
		 ( iCod == ASCII_I_MIN_DIE ) ||
		 ( iCod == ASCII_O_MIN_DIE ) ||
		 ( iCod == ASCII_U_MIN_DIE ) ||	
  		 ( iCod == ASCII_A_MIN_TIL ) ||
		 ( iCod == ASCII_E_MIN_TIL ) ||
		 ( iCod == ASCII_I_MIN_TIL ) ||
		 ( iCod == ASCII_O_MIN_TIL ) ||
		 ( iCod == ASCII_U_MIN_TIL ) ||	
  		 ( iCod == ASCII_A_MIN_ANI ) ||
		 ( iCod == ASCII_O_MIN_BAR ) )	
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}


int ASCIIEsVocalMay ( char cVal )
{
	int iRes; 
	int iCod;

	iCod = ASCIICodigo ( cVal );	
	if ( ( iCod == ASCII_A_MAY ) ||
		 ( iCod == ASCII_E_MAY ) ||
		 ( iCod == ASCII_I_MAY ) ||
		 ( iCod == ASCII_O_MAY ) ||
		 ( iCod == ASCII_U_MAY ) ||
  		 ( iCod == ASCII_A_MAY_CER ) ||
		 ( iCod == ASCII_E_MAY_CER ) ||
		 ( iCod == ASCII_I_MAY_CER ) ||
		 ( iCod == ASCII_O_MAY_CER ) ||
		 ( iCod == ASCII_U_MAY_CER ) ||	
  		 ( iCod == ASCII_A_MAY_ABI ) ||
		 ( iCod == ASCII_E_MAY_ABI ) ||
		 ( iCod == ASCII_I_MAY_ABI ) ||
		 ( iCod == ASCII_O_MAY_ABI ) ||
		 ( iCod == ASCII_U_MAY_ABI ) ||	
  		 ( iCod == ASCII_A_MAY_CIR ) ||
		 ( iCod == ASCII_E_MAY_CIR ) ||
		 ( iCod == ASCII_I_MAY_CIR ) ||
		 ( iCod == ASCII_O_MAY_CIR ) ||
		 ( iCod == ASCII_U_MAY_CIR ) ||	
  		 ( iCod == ASCII_A_MAY_DIE ) ||
		 ( iCod == ASCII_E_MAY_DIE ) ||
		 ( iCod == ASCII_I_MAY_DIE ) ||
		 ( iCod == ASCII_O_MAY_DIE ) ||
		 ( iCod == ASCII_U_MAY_DIE ) ||	
  		 ( iCod == ASCII_A_MAY_TIL ) ||
		 ( iCod == ASCII_E_MAY_TIL ) ||
		 ( iCod == ASCII_I_MAY_TIL ) ||
		 ( iCod == ASCII_O_MAY_TIL ) ||
		 ( iCod == ASCII_U_MAY_TIL ) ||	
  		 ( iCod == ASCII_A_MAY_ANI ) ||
		 ( iCod == ASCII_O_MAY_BAR ) )	
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}


int ASCIIEsConsonante ( char cVal )
{
	int iRes;

	if ( ( ASCIIEsConsonanteMin ( cVal ) == 1 ) || 
		 ( ASCIIEsConsonanteMay ( cVal ) == 1 ) )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}


int ASCIIEsConsonanteMin ( char cVal )
{
	int iRes; 
	int iCod;

	iCod = ASCIICodigo ( cVal );	
	if ( ( iCod == ASCII_B_MIN ) ||
		 ( iCod == ASCII_C_MIN ) ||
		 ( iCod == ASCII_D_MIN ) ||
		 ( iCod == ASCII_F_MIN ) ||
		 ( iCod == ASCII_G_MIN ) ||
		 ( iCod == ASCII_H_MIN ) ||
		 ( iCod == ASCII_J_MIN ) ||
		 ( iCod == ASCII_K_MIN ) ||
		 ( iCod == ASCII_L_MIN ) ||
		 ( iCod == ASCII_M_MIN ) ||
		 ( iCod == ASCII_N_MIN ) ||
		 ( iCod == ASCII_P_MIN ) ||
		 ( iCod == ASCII_Q_MIN ) ||
		 ( iCod == ASCII_R_MIN ) ||
		 ( iCod == ASCII_S_MIN ) ||
		 ( iCod == ASCII_T_MIN ) ||
		 ( iCod == ASCII_V_MIN ) ||
		 ( iCod == ASCII_W_MIN ) ||
		 ( iCod == ASCII_X_MIN ) ||
		 ( iCod == ASCII_Y_MIN ) ||
		 ( iCod == ASCII_Z_MIN ) ||
		 ( iCod == ASCII_N_MIN_TIL ) ||
		 ( iCod == ASCII_C_MIN_CED ) ||
		 ( iCod == ASCII_Y_MIN_DIE ) )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}


int ASCIIEsConsonanteMay ( char cVal )
{
	int iRes; 
	int iCod;

	iCod = ASCIICodigo ( cVal );	
	if ( ( iCod == ASCII_B_MAY ) ||
		 ( iCod == ASCII_C_MAY ) ||
		 ( iCod == ASCII_D_MAY ) ||
		 ( iCod == ASCII_F_MAY ) ||
		 ( iCod == ASCII_G_MAY ) ||
		 ( iCod == ASCII_H_MAY ) ||
		 ( iCod == ASCII_J_MAY ) ||
		 ( iCod == ASCII_K_MAY ) ||
		 ( iCod == ASCII_L_MAY ) ||
		 ( iCod == ASCII_M_MAY ) ||
		 ( iCod == ASCII_N_MAY ) ||
		 ( iCod == ASCII_P_MAY ) ||
		 ( iCod == ASCII_Q_MAY ) ||
		 ( iCod == ASCII_R_MAY ) ||
		 ( iCod == ASCII_S_MAY ) ||
		 ( iCod == ASCII_T_MAY ) ||
		 ( iCod == ASCII_V_MAY ) ||
		 ( iCod == ASCII_W_MAY ) ||
		 ( iCod == ASCII_X_MAY ) ||
		 ( iCod == ASCII_Y_MAY ) ||
		 ( iCod == ASCII_Z_MAY ) ||
		 ( iCod == ASCII_N_MAY_TIL ) ||
		 ( iCod == ASCII_C_MAY_CED ) ||
		 ( iCod == ASCII_Y_MAY_DIE ) )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}


int ASCIIEsLetraConSigno ( char cVal )
{
	int iRes;

	if ( ( ASCIIEsLetraMinConSigno ( cVal ) == 1 ) || 
		 ( ASCIIEsLetraMayConSigno ( cVal ) == 1 ) )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}


int ASCIIEsLetraMinConSigno ( char cVal )
{
	int iRes;

	if ( ( ASCIIEsLetraMinAcentuada ( cVal ) == 1 ) || 
		 ( ASCIIEsLetraMinConDieresis ( cVal ) == 1 ) ||
		 ( ASCIIEsLetraMinConAnillo ( cVal ) == 1 ) ||
		 ( ASCIIEsLetraMinConCedilla ( cVal ) == 1 ) ||
		 ( ASCIIEsLetraMinBarrada ( cVal ) == 1 ) ||
		 ( ASCIIEsLetraMinConTilde ( cVal ) == 1 ) )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}


int ASCIIEsLetraMayConSigno ( char cVal )
{
	int iRes;

	if ( ( ASCIIEsLetraMayAcentuada ( cVal ) == 1 ) || 
		 ( ASCIIEsLetraMayConDieresis ( cVal ) == 1 ) ||
		 ( ASCIIEsLetraMayConAnillo ( cVal ) == 1 ) ||
		 ( ASCIIEsLetraMayConCedilla ( cVal ) == 1 ) ||
		 ( ASCIIEsLetraMayBarrada ( cVal ) == 1 ) ||
		 ( ASCIIEsLetraMayConTilde ( cVal ) == 1 ) )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}


int ASCIIEsLetraAcentuada ( char cVal )
{
	int iRes;

	if ( ( ASCIIEsLetraMinAcentuada ( cVal ) == 1 ) || 
		 ( ASCIIEsLetraMayAcentuada ( cVal ) == 1 ) )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}


int ASCIIEsLetraMinAcentuada ( char cVal )
{
	int iRes;

	if ( ( ASCIIEsLetraMinConAcentoAbi ( cVal ) == 1 ) || 
		 ( ASCIIEsLetraMinConAcentoCer ( cVal ) == 1 ) ||
		 ( ASCIIEsLetraMinConAcentoCir ( cVal ) == 1 ) )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}


int ASCIIEsLetraMayAcentuada ( char cVal )
{
	int iRes;

	if ( ( ASCIIEsLetraMayConAcentoAbi ( cVal ) == 1 ) || 
		 ( ASCIIEsLetraMayConAcentoCer ( cVal ) == 1 ) ||
		 ( ASCIIEsLetraMayConAcentoCir ( cVal ) == 1 ) )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}



int ASCIIEsLetraConAcentoAbi ( char cVal )
{
	int iRes;

	if ( ( ASCIIEsLetraMinConAcentoAbi ( cVal ) == 1 ) || 
		 ( ASCIIEsLetraMayConAcentoAbi ( cVal ) == 1 ) )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}


int ASCIIEsLetraMinConAcentoAbi ( char cVal )
{
	int iRes; 
	int iCod;

	iCod = ASCIICodigo ( cVal );	
	if ( ( iCod == ASCII_A_MIN_ABI ) ||
		 ( iCod == ASCII_E_MIN_ABI ) ||
		 ( iCod == ASCII_I_MIN_ABI ) ||
		 ( iCod == ASCII_O_MIN_ABI ) ||
		 ( iCod == ASCII_U_MIN_ABI ) )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}


int ASCIIEsLetraMayConAcentoAbi ( char cVal )
{
	int iRes; 
	int iCod;

	iCod = ASCIICodigo ( cVal );	
	if ( ( iCod == ASCII_A_MAY_ABI ) ||
		 ( iCod == ASCII_E_MAY_ABI ) ||
		 ( iCod == ASCII_I_MAY_ABI ) ||
		 ( iCod == ASCII_O_MAY_ABI ) ||
		 ( iCod == ASCII_U_MAY_ABI ) )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}


int ASCIIEsLetraConAcentoCer ( char cVal )
{
	int iRes;

	if ( ( ASCIIEsLetraMinConAcentoCer ( cVal ) == 1 ) || 
		 ( ASCIIEsLetraMayConAcentoCer ( cVal ) == 1 ) )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}


int ASCIIEsLetraMinConAcentoCer ( char cVal )
{
	int iRes; 
	int iCod;

	iCod = ASCIICodigo ( cVal );	
	if ( ( iCod == ASCII_A_MIN_CER ) ||
		 ( iCod == ASCII_E_MIN_CER ) ||
		 ( iCod == ASCII_I_MIN_CER ) ||
		 ( iCod == ASCII_O_MIN_CER ) ||
		 ( iCod == ASCII_U_MIN_CER ) )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}


int ASCIIEsLetraMayConAcentoCer ( char cVal )
{
	int iRes; 
	int iCod;

	iCod = ASCIICodigo ( cVal );	
	if ( ( iCod == ASCII_A_MAY_CER ) ||
		 ( iCod == ASCII_E_MAY_CER ) ||
		 ( iCod == ASCII_I_MAY_CER ) ||
		 ( iCod == ASCII_O_MAY_CER ) ||
		 ( iCod == ASCII_U_MAY_CER ) )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}


int ASCIIEsLetraConAcentoCir ( char cVal )
{
	int iRes;

	if ( ( ASCIIEsLetraMinConAcentoCir ( cVal ) == 1 ) || 
		 ( ASCIIEsLetraMayConAcentoCir ( cVal ) == 1 ) )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}


int ASCIIEsLetraMinConAcentoCir ( char cVal )
{
	int iRes; 
	int iCod;

	iCod = ASCIICodigo ( cVal );	
	if ( ( iCod == ASCII_A_MIN_CIR ) ||
		 ( iCod == ASCII_E_MIN_CIR ) ||
		 ( iCod == ASCII_I_MIN_CIR ) ||
		 ( iCod == ASCII_O_MIN_CIR ) ||
		 ( iCod == ASCII_U_MIN_CIR ) )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}


int ASCIIEsLetraMayConAcentoCir ( char cVal )
{
	int iRes; 
	int iCod;

	iCod = ASCIICodigo ( cVal );	
	if ( ( iCod == ASCII_A_MAY_CIR ) ||
		 ( iCod == ASCII_E_MAY_CIR ) ||
		 ( iCod == ASCII_I_MAY_CIR ) ||
		 ( iCod == ASCII_O_MAY_CIR ) ||
		 ( iCod == ASCII_U_MAY_CIR ) )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}


int ASCIIEsLetraConDieresis ( char cVal )
{
	int iRes;

	if ( ( ASCIIEsLetraMinConDieresis ( cVal ) == 1 ) || 
		 ( ASCIIEsLetraMayConDieresis ( cVal ) == 1 ) )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}


int ASCIIEsLetraMinConDieresis ( char cVal )
{
	int iRes; 
	int iCod;

	iCod = ASCIICodigo ( cVal );	
	if ( ( iCod == ASCII_A_MIN_DIE ) ||
		 ( iCod == ASCII_E_MIN_DIE ) ||
		 ( iCod == ASCII_I_MIN_DIE ) ||
		 ( iCod == ASCII_O_MIN_DIE ) ||
		 ( iCod == ASCII_U_MIN_DIE ) ||
		 ( iCod == ASCII_Y_MIN_DIE ) )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}


int ASCIIEsLetraMayConDieresis ( char cVal )
{
	int iRes; 
	int iCod;

	iCod = ASCIICodigo ( cVal );	
	if ( ( iCod == ASCII_A_MAY_DIE ) ||
		 ( iCod == ASCII_E_MAY_DIE ) ||
		 ( iCod == ASCII_I_MAY_DIE ) ||
		 ( iCod == ASCII_O_MAY_DIE ) ||
		 ( iCod == ASCII_U_MAY_DIE ) ||
		 ( iCod == ASCII_Y_MAY_DIE ) )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}


int ASCIIEsLetraConTilde ( char cVal )
{
	int iRes;

	if ( ( ASCIIEsLetraMinConTilde ( cVal ) == 1 ) || 
		 ( ASCIIEsLetraMayConTilde ( cVal ) == 1 ) )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}


int ASCIIEsLetraMinConTilde ( char cVal )
{
	int iRes; 
	int iCod;

	iCod = ASCIICodigo ( cVal );	
	if ( ( iCod == ASCII_A_MIN_TIL ) ||
		 ( iCod == ASCII_E_MIN_TIL ) ||
		 ( iCod == ASCII_I_MIN_TIL ) ||
		 ( iCod == ASCII_O_MIN_TIL ) ||
		 ( iCod == ASCII_U_MIN_TIL ) ||
		 ( iCod == ASCII_N_MIN_TIL ) )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}


int ASCIIEsLetraMayConTilde ( char cVal )
{
	int iRes; 
	int iCod;

	iCod = ASCIICodigo ( cVal );	
	if ( ( iCod == ASCII_A_MAY_TIL ) ||
		 ( iCod == ASCII_E_MAY_TIL ) ||
		 ( iCod == ASCII_I_MAY_TIL ) ||
		 ( iCod == ASCII_O_MAY_TIL ) ||
		 ( iCod == ASCII_U_MAY_TIL ) ||
		 ( iCod == ASCII_N_MAY_TIL ) )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}


int ASCIIEsLetraConCedilla ( char cVal )
{
	int iRes;

	if ( ( ASCIIEsLetraMinConCedilla ( cVal ) == 1 ) || 
		 ( ASCIIEsLetraMayConCedilla ( cVal ) == 1 ) )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}


int ASCIIEsLetraMinConCedilla ( char cVal )
{
	int iRes; 
	int iCod;

	iCod = ASCIICodigo ( cVal );	
	if ( ( iCod == ASCII_C_MIN_CED ) )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}


int ASCIIEsLetraMayConCedilla ( char cVal )
{
	int iRes; 
	int iCod;

	iCod = ASCIICodigo ( cVal );	
	if ( ( iCod == ASCII_C_MAY_CED ) )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}


int ASCIIEsLetraConAnillo ( char cVal )
{
	int iRes;

	if ( ( ASCIIEsLetraMinConAnillo ( cVal ) == 1 ) || 
		 ( ASCIIEsLetraMayConAnillo ( cVal ) == 1 ) )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}


int ASCIIEsLetraMinConAnillo ( char cVal )
{
	int iRes; 
	int iCod;

	iCod = ASCIICodigo ( cVal );	
	if ( ( iCod == ASCII_A_MIN_ANI ) )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}


int ASCIIEsLetraMayConAnillo ( char cVal )
{
	int iRes; 
	int iCod;

	iCod = ASCIICodigo ( cVal );	
	if ( ( iCod == ASCII_A_MAY_ANI ) )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}


int ASCIIEsLetraBarrada ( char cVal )
{
	int iRes;

	if ( ( ASCIIEsLetraMinBarrada ( cVal ) == 1 ) || 
		 ( ASCIIEsLetraMayBarrada ( cVal ) == 1 ) )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}


int ASCIIEsLetraMinBarrada ( char cVal )
{
	int iRes; 
	int iCod;

	iCod = ASCIICodigo ( cVal );	
	if ( ( iCod == ASCII_O_MIN_BAR ) )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}


int ASCIIEsLetraMayBarrada ( char cVal )
{
	int iRes; 
	int iCod;

	iCod = ASCIICodigo ( cVal );	
	if ( ( iCod == ASCII_O_MAY_BAR ) )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}


int ASCIIEsLetraNordica ( char cVal )
{
	int iRes;

	if ( ( ASCIIEsLetraMinNordica ( cVal ) == 1 ) || 
		 ( ASCIIEsLetraMayNordica ( cVal ) == 1 ) )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}


int ASCIIEsLetraMinNordica ( char cVal )
{
	int iRes; 
	int iCod;

	iCod = ASCIICodigo ( cVal );	
	if ( ( iCod == ASCII_ETH_MIN ) ||
		 ( iCod == ASCII_THORN_MIN ) )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}


int ASCIIEsLetraMayNordica ( char cVal )
{
	int iRes; 
	int iCod;

	iCod = ASCIICodigo ( cVal );	
	if ( ( iCod == ASCII_ETH_MAY ) ||
		 ( iCod == ASCII_THORN_MAY ) )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}


int ASCIIEsLetraGriega ( char cVal )
{
	int iRes;

	if ( ( ASCIIEsLetraMinGriega ( cVal ) == 1 ) || 
		 ( ASCIIEsLetraMayGriega ( cVal ) == 1 ) )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}


int ASCIIEsLetraMinGriega ( char cVal )
{
	int iRes; 
	int iCod;

	iCod = ASCIICodigo ( cVal );	
	if ( ( iCod == ASCII_BETA_MIN ) ||
		 ( iCod == ASCII_MU_MIN ) )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}


int ASCIIEsLetraMayGriega ( char cVal )
{
	int iRes; 
	int iCod;

	iCod = ASCIICodigo ( cVal );	
	if ( ( iCod == ASCII_BETA_MAY ) ||
		 ( iCod == ASCII_MU_MAY ) )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}


int ASCIIEsLetraEspecial ( char cVal )
{
	int iRes;

	if ( ( ASCIIEsLetraMinEspecial ( cVal ) == 1 ) || 
		 ( ASCIIEsLetraMayEspecial ( cVal ) == 1 ) )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}


int ASCIIEsLetraMinEspecial ( char cVal )
{
	int iRes; 
	int iCod;

	iCod = ASCIICodigo ( cVal );	
	if ( ( iCod == ASCII_AE_MIN ) )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}


int ASCIIEsLetraMayEspecial ( char cVal )
{
	int iRes; 
	int iCod;

	iCod = ASCIICodigo ( cVal );	
	if ( ( iCod == ASCII_AE_MAY ) )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}



/*
int ASCIIPerteneceAlAlfabetoEsp ( char cVal )
int ASCIIPerteneceAlAlfabetoIng ( char cVal )
int ASCIIPerteneceAlAlfabetoFra ( char cVal )
int ASCIIPerteneceAlAlfabetoAle ( char cVal )
int ASCIIPerteneceAlAlfabetoCat ( char cVal )
int ASCIIPerteneceAlAlfabetoPor ( char cVal )
*/

char ASCIILetraMinAMay ( char cVal )
{
	char cRes;
	int iCod;

	iCod = ASCIICodigo ( cVal );	
	if ( ASCIIEsLetraMin ( cVal ) )
	{
		if ( ASCIIPerteneceAlJuegoPrincipal ( cVal ) == 1 )
		{
			cRes = (char)( iCod + ASCII_DESPLAZAMIENTO_MAY );
		}
		else
		{
			if ( iCod == ASCII_A_MIN_ABI ) 
			{
				cRes = (char) ASCII_A_MAY_ABI;
			}
			else if ( iCod == ASCII_E_MIN_ABI ) 
			{
				cRes = (char) ASCII_E_MAY_ABI;
			}
			else if ( iCod == ASCII_I_MIN_ABI ) 
			{
				cRes = (char) ASCII_I_MAY_ABI;
			}
			else if ( iCod == ASCII_O_MIN_ABI )
			{
				cRes = (char) ASCII_O_MAY_ABI;
			}
			else if ( iCod == ASCII_U_MIN_ABI )
			{
				cRes = (char) ASCII_U_MAY_ABI;
			}
			else if ( iCod == ASCII_A_MIN_CER ) 
			{
				cRes = (char) ASCII_A_MAY_CER;
			}
			else if ( iCod == ASCII_E_MIN_CER ) 
			{
				cRes = (char) ASCII_E_MAY_CER;
			}
			else if ( iCod == ASCII_I_MIN_CER ) 
			{
				cRes = (char) ASCII_I_MAY_CER;
			}
			else if ( iCod == ASCII_O_MIN_CER )
			{
				cRes = (char) ASCII_O_MAY_CER;
			}
			else if ( iCod == ASCII_U_MIN_CER )
			{
				cRes = (char) ASCII_U_MAY_CER;
			}
			else if ( iCod == ASCII_A_MIN_CIR ) 
			{
				cRes = (char) ASCII_A_MAY_CIR;
			}
			else if ( iCod == ASCII_E_MIN_CIR ) 
			{
				cRes = (char) ASCII_E_MAY_CIR;
			}
			else if ( iCod == ASCII_I_MIN_CIR ) 
			{
				cRes = (char) ASCII_I_MAY_CIR;
			}
			else if ( iCod == ASCII_O_MIN_CIR )
			{
				cRes = (char) ASCII_O_MAY_CIR;
			}
			else if ( iCod == ASCII_U_MIN_CIR )
			{
				cRes = (char) ASCII_U_MAY_CIR;
			}
			if ( iCod == ASCII_A_MIN_DIE ) 
			{
				cRes = (char) ASCII_A_MAY_DIE;
			}
			else if ( iCod == ASCII_E_MIN_DIE ) 
			{
				cRes = (char) ASCII_E_MAY_DIE;
			}
			else if ( iCod == ASCII_I_MIN_DIE ) 
			{
				cRes = (char) ASCII_I_MAY_DIE;
			}
			else if ( iCod == ASCII_O_MIN_DIE )
			{
				cRes = (char) ASCII_O_MAY_DIE;
			}
			else if ( iCod == ASCII_U_MIN_DIE )
			{
				cRes = (char) ASCII_U_MAY_DIE;
			}
			else if ( iCod == ASCII_A_MIN_TIL ) 
			{
				cRes = (char) ASCII_A_MAY_TIL;
			}
			else if ( iCod == ASCII_E_MIN_TIL ) 
			{
				cRes = (char) ASCII_E_MAY_TIL;
			}
			else if ( iCod == ASCII_I_MIN_TIL ) 
			{
				cRes = (char) ASCII_I_MAY_TIL;
			}
			else if ( iCod == ASCII_O_MIN_TIL )
			{
				cRes = (char) ASCII_O_MAY_TIL;
			}
			else if ( iCod == ASCII_U_MIN_TIL )
			{
				cRes = (char) ASCII_U_MAY_TIL;
			}
			else if ( iCod == ASCII_A_MIN_ANI ) 
			{
				cRes = (char) ASCII_A_MAY_ANI;
			}
			else if ( iCod == ASCII_O_MIN_BAR )
			{
				cRes = (char) ASCII_O_MAY_BAR;
			}
			else if ( iCod == ASCII_N_MIN_TIL )
			{
				cRes = (char) ASCII_N_MAY_TIL;
			}
			else if ( iCod == ASCII_C_MIN_CED )
			{
				cRes = (char) ASCII_C_MAY_CED;
			}
			else if ( iCod == ASCII_Y_MIN_DIE )
			{
				cRes = (char) ASCII_Y_MAY_DIE;
			}
			else
			{
				cRes = cVal;
			}
			if ( (int) cRes == -1 )
			{
				cRes = (char) ASCII_ESPACIO;
			}
		}
	}
	else
	{
		cRes = cVal;
	}
	return ( cRes );
}


char ASCIILetraMayAMin ( char cVal )
{
	char cRes;
	int iCod;

	iCod = ASCIICodigo ( cVal );	
	if ( ASCIIEsLetraMay ( cVal ) )
	{
		if ( ASCIIPerteneceAlJuegoPrincipal ( cVal ) == 1 )
		{
			cRes = (char)( iCod - ASCII_DESPLAZAMIENTO_MAY );
		}
		else
		{
			if ( iCod == ASCII_A_MAY_ABI ) 
			{
				cRes = (char) ASCII_A_MIN_ABI;
			}
			else if ( iCod == ASCII_E_MAY_ABI ) 
			{
				cRes = (char) ASCII_E_MIN_ABI;
			}
			else if ( iCod == ASCII_I_MAY_ABI ) 
			{
				cRes = (char) ASCII_I_MIN_ABI;
			}
			else if ( iCod == ASCII_O_MAY_ABI )
			{
				cRes = (char) ASCII_O_MIN_ABI;
			}
			else if ( iCod == ASCII_U_MAY_ABI )
			{
				cRes = (char) ASCII_U_MIN_ABI;
			}
			else if ( iCod == ASCII_A_MAY_CER ) 
			{
				cRes = (char) ASCII_A_MIN_CER;
			}
			else if ( iCod == ASCII_E_MAY_CER ) 
			{
				cRes = (char) ASCII_E_MIN_CER;
			}
			else if ( iCod == ASCII_I_MAY_CER ) 
			{
				cRes = (char) ASCII_I_MIN_CER;
			}
			else if ( iCod == ASCII_O_MAY_CER )
			{
				cRes = (char) ASCII_O_MIN_CER;
			}
			else if ( iCod == ASCII_U_MAY_CER )
			{
				cRes = (char) ASCII_U_MIN_CER;
			}
			else if ( iCod == ASCII_A_MAY_CIR ) 
			{
				cRes = (char) ASCII_A_MIN_CIR;
			}
			else if ( iCod == ASCII_E_MAY_CIR ) 
			{
				cRes = (char) ASCII_E_MIN_CIR;
			}
			else if ( iCod == ASCII_I_MAY_CIR ) 
			{
				cRes = (char) ASCII_I_MIN_CIR;
			}
			else if ( iCod == ASCII_O_MAY_CIR )
			{
				cRes = (char) ASCII_O_MIN_CIR;
			}
			else if ( iCod == ASCII_U_MAY_CIR )
			{
				cRes = (char) ASCII_U_MIN_CIR;
			}
			else if ( iCod == ASCII_A_MAY_DIE ) 
			{
				cRes = (char) ASCII_A_MIN_DIE;
			}
			else if ( iCod == ASCII_E_MAY_DIE ) 
			{
				cRes = (char) ASCII_E_MIN_DIE;
			}
			else if ( iCod == ASCII_I_MAY_DIE ) 
			{
				cRes = (char) ASCII_I_MIN_DIE;
			}
			else if ( iCod == ASCII_O_MAY_DIE )
			{
				cRes = (char) ASCII_O_MIN_DIE;
			}
			else if ( iCod == ASCII_U_MAY_DIE )
			{
				cRes = (char) ASCII_U_MIN_DIE;
			}
			else if ( iCod == ASCII_A_MAY_TIL ) 
			{
				cRes = (char) ASCII_A_MIN_TIL;
			}
			else if ( iCod == ASCII_E_MAY_TIL ) 
			{
				cRes = (char) ASCII_E_MIN_TIL;
			}
			else if ( iCod == ASCII_I_MAY_TIL ) 
			{
				cRes = (char) ASCII_I_MIN_TIL;
			}
			else if ( iCod == ASCII_O_MAY_TIL )
			{
				cRes = (char) ASCII_O_MIN_TIL;
			}
			else if ( iCod == ASCII_U_MAY_TIL )
			{
				cRes = (char) ASCII_U_MIN_TIL;
			}
			else if ( iCod == ASCII_A_MAY_ANI ) 
			{
				cRes = (char) ASCII_A_MIN_ANI;
			}
			else if ( iCod == ASCII_O_MAY_BAR )
			{
				cRes = (char) ASCII_O_MIN_BAR;
			}
			else if ( iCod == ASCII_N_MAY_TIL )
			{
				cRes = (char) ASCII_N_MIN_TIL;
			}
			else if ( iCod == ASCII_C_MAY_CED )
			{
				cRes = (char) ASCII_C_MIN_CED;
			}
			else if ( iCod == ASCII_Y_MAY_DIE )
			{
				cRes = (char) ASCII_Y_MIN_DIE;
			}
			else
			{
				cRes = cVal;
			}
			if ( (int) cRes == -1 )
			{
				cRes = (char) ASCII_ESPACIO;
			}
		}
	}
	else
	{
		cRes = cVal;
	}
	return ( cRes );
}

char ASCIILetraSinSigno ( char cVal )
{
	char cRes;
	int iCod;

	iCod = ASCIICodigo ( cVal );	
	if ( ASCIIPerteneceAlJuegoPrincipal ( cVal ) == 1 )
	{
		cRes = cVal;
	}
	else
	{
		if ( iCod == ASCII_A_MIN_ABI ) 
		{
			cRes = (char) ASCII_A_MIN;
		}
		else if ( iCod == ASCII_E_MIN_ABI ) 
		{
			cRes = (char) ASCII_E_MIN;
		}
		else if ( iCod == ASCII_I_MIN_ABI ) 
		{
			cRes = (char) ASCII_I_MIN;
		}
		else if ( iCod == ASCII_O_MIN_ABI )
		{
			cRes = (char) ASCII_O_MIN;
		}
		else if ( iCod == ASCII_U_MIN_ABI )
		{
			cRes = (char) ASCII_U_MIN;
		}
		else if ( iCod == ASCII_A_MIN_CER ) 
		{
			cRes = (char) ASCII_A_MIN;     ;
		}
		else if ( iCod == ASCII_E_MIN_CER ) 
		{
			cRes = (char) ASCII_E_MIN;
		}
		else if ( iCod == ASCII_I_MIN_CER ) 
		{
			cRes = (char) ASCII_I_MIN;
		}
		else if ( iCod == ASCII_O_MIN_CER )
		{
			cRes = (char) ASCII_O_MIN;
		}
		else if ( iCod == ASCII_U_MIN_CER )
		{
			cRes = (char) ASCII_U_MIN;
		}
		else if ( iCod == ASCII_A_MIN_CIR ) 
		{
			cRes = (char) ASCII_A_MIN;
		}
		else if ( iCod == ASCII_E_MIN_CIR ) 
		{
			cRes = (char) ASCII_E_MIN;
		}
		else if ( iCod == ASCII_I_MIN_CIR ) 
		{
			cRes = (char) ASCII_I_MIN;
		}
		else if ( iCod == ASCII_O_MIN_CIR )
		{
			cRes = (char) ASCII_O_MIN;
		}
		else if ( iCod == ASCII_U_MIN_CIR )
		{
			cRes = (char) ASCII_U_MIN;
		}
		else if ( iCod == ASCII_A_MIN_DIE ) 
		{
			cRes = (char) ASCII_A_MIN;
		}
		else if ( iCod == ASCII_E_MIN_DIE ) 
		{
			cRes = (char) ASCII_E_MIN;
		}
		else if ( iCod == ASCII_I_MIN_DIE ) 
		{
			cRes = (char) ASCII_I_MIN;
		}
		else if ( iCod == ASCII_O_MIN_DIE )
		{
			cRes = (char) ASCII_O_MIN;
		}
		else if ( iCod == ASCII_U_MIN_DIE )
		{
			cRes = (char) ASCII_U_MIN;
		}
		else if ( iCod == ASCII_A_MIN_TIL ) 
		{
			cRes = (char) ASCII_A_MIN;
		}
		else if ( iCod == ASCII_E_MIN_TIL ) 
		{
			cRes = (char) ASCII_E_MIN;
		}
		else if ( iCod == ASCII_I_MIN_TIL ) 
		{
			cRes = (char) ASCII_I_MIN;
		}
		else if ( iCod == ASCII_O_MIN_TIL )
		{
			cRes = (char) ASCII_O_MIN;
		}
		else if ( iCod == ASCII_U_MIN_TIL )
		{
			cRes = (char) ASCII_U_MIN;
		}
		else if ( iCod == ASCII_A_MIN_ANI ) 
		{
			cRes = (char) ASCII_A_MIN;
		}
		else if ( iCod == ASCII_O_MIN_BAR )
		{
			cRes = (char) ASCII_O_MIN;
		}
		else if ( iCod == ASCII_N_MIN_TIL )
		{
			cRes = (char) ASCII_N_MIN;
		}
		else if ( iCod == ASCII_C_MIN_CED )
		{
			cRes = (char) ASCII_C_MIN;
		}
		else if ( iCod == ASCII_Y_MIN_DIE )
		{
			cRes = (char) ASCII_Y_MIN;
		}
		else if ( iCod == ASCII_A_MAY_ABI ) 
		{
			cRes = (char) ASCII_A_MAY;
		}
		else if ( iCod == ASCII_E_MAY_ABI ) 
		{
			cRes = (char) ASCII_E_MAY;
		}
		else if ( iCod == ASCII_I_MAY_ABI ) 
		{
			cRes = (char) ASCII_I_MAY;
		}
		else if ( iCod == ASCII_O_MAY_ABI )
		{
			cRes = (char) ASCII_O_MAY;
		}
		else if ( iCod == ASCII_U_MAY_ABI )
		{
			cRes = (char) ASCII_U_MAY;
		}
		else if ( iCod == ASCII_A_MAY_CER ) 
		{
			cRes = (char) ASCII_A_MAY;
		}
		else if ( iCod == ASCII_E_MAY_CER ) 
		{
			cRes = (char) ASCII_E_MAY;
		}
		else if ( iCod == ASCII_I_MAY_CER ) 
		{
			cRes = (char) ASCII_I_MAY;
		}
		else if ( iCod == ASCII_O_MAY_CER )
		{
			cRes = (char) ASCII_O_MAY;
		}
		else if ( iCod == ASCII_U_MAY_CER )
		{
			cRes = (char) ASCII_U_MAY;
		}
		else if ( iCod == ASCII_A_MAY_CIR ) 
		{
			cRes = (char) ASCII_A_MAY;
		}
		else if ( iCod == ASCII_E_MAY_CIR ) 
		{
			cRes = (char) ASCII_E_MAY;
		}
		else if ( iCod == ASCII_I_MAY_CIR ) 
		{
			cRes = (char) ASCII_I_MAY;
		}
		else if ( iCod == ASCII_O_MAY_CIR )
		{
			cRes = (char) ASCII_O_MAY;
		}
		else if ( iCod == ASCII_U_MAY_CIR )
		{
			cRes = (char) ASCII_U_MAY;
		}
		else if ( iCod == ASCII_A_MAY_DIE ) 
		{
			cRes = (char) ASCII_A_MAY;
		}
		else if ( iCod == ASCII_E_MAY_DIE ) 
		{
			cRes = (char) ASCII_E_MAY;
		}
		else if ( iCod == ASCII_I_MAY_DIE ) 
		{
			cRes = (char) ASCII_I_MAY;
		}
		else if ( iCod == ASCII_O_MAY_DIE )
		{
			cRes = (char) ASCII_O_MAY;
		}
		else if ( iCod == ASCII_U_MAY_DIE )
		{
			cRes = (char) ASCII_U_MAY;
		}
		else if ( iCod == ASCII_A_MAY_TIL ) 
		{
			cRes = (char) ASCII_A_MAY;
		}
		else if ( iCod == ASCII_E_MAY_TIL ) 
		{
			cRes = (char) ASCII_E_MAY;
		}
		else if ( iCod == ASCII_I_MAY_TIL ) 
		{
			cRes = (char) ASCII_I_MAY;
		}
		else if ( iCod == ASCII_O_MAY_TIL )
		{
			cRes = (char) ASCII_O_MAY;
		}
		else if ( iCod == ASCII_U_MAY_TIL )
		{
			cRes = (char) ASCII_U_MAY;
		}
		else if ( iCod == ASCII_A_MAY_ANI ) 
		{
			cRes = (char) ASCII_A_MAY;
		}
		else if ( iCod == ASCII_O_MAY_BAR )
		{
			cRes = (char) ASCII_O_MAY;
		}
		else if ( iCod == ASCII_N_MAY_TIL )
		{
			cRes = (char) ASCII_N_MAY;
		}
		else if ( iCod == ASCII_C_MAY_CED )
		{
			cRes = (char) ASCII_C_MAY;
		}
		else if ( iCod == ASCII_Y_MAY_DIE )
		{
			cRes = (char) ASCII_Y_MAY;
		}
		else
		{
			cRes = cVal;
		}
		if ( (int) cRes == -1 )
		{
			cRes = (char) ASCII_ESPACIO;
		}
	}
	return ( cRes );
}

int ASCIIEsDigito ( char cVal )
{
	int iRes; 
	int iCod;

	iCod = ASCIICodigo ( cVal );	
	if ( ( iCod >= ASCII_0 ) && ( iCod <= ASCII_9 ) )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int ASCIIEsEspacio ( char cVal )
{
	int iRes; 
	int iCod;

	iCod = ASCIICodigo ( cVal );	
	if ( ( iCod == ASCII_ESPACIO ) ||
		 ( iCod == ASCII_ESPACIO_2 ) )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int ASCIIEsGuion ( char cVal )
{
	int iRes; 
	int iCod;

	iCod = ASCIICodigo ( cVal );	
	if ( iCod == ASCII_GUION ) 
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int ASCIIEsGuionBajo ( char cVal )
{
	int iRes; 
	int iCod;

	iCod = ASCIICodigo ( cVal );	
	if ( iCod == ASCII_RALLA_INF )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int ASCIIEsSigno ( char cVal )
{
	int iRes; 

	if ( ( ASCIIEsSignoPunt ( cVal ) == 1 ) || 
		 ( ASCIIEsSignoArit ( cVal ) == 1 ) ||
		 ( ASCIIEsSignoCont ( cVal ) == 1 ) ||
		 ( ASCIIEsSignoComp ( cVal ) == 1 ) ||
		 ( ASCIIEsSignoEsp ( cVal ) == 1 ) ||
		 ( ASCIIEsSignoModif ( cVal ) == 1 ) ||
		 ( ASCIIEsSignoMoneda ( cVal ) == 1 ) )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}


int ASCIIEsSignoPunt ( char cVal )
{
	int iRes; 
	int iCod;

	iCod = ASCIICodigo ( cVal );	
	if ( ( iCod == ASCII_COMA ) ||
	     ( iCod == ASCII_PUNTO ) ||
	     ( iCod == ASCII_DOS_PUNTOS ) ||
	     ( iCod == ASCII_PUNTO_COMA ) ||
	     ( iCod == ASCII_GUION ) )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}


int ASCIIEsSignoArit ( char cVal )
{
	int iRes; 
	int iCod;

	iCod = ASCIICodigo ( cVal );	
	if ( ( iCod == ASCII_MAS ) ||
	     ( iCod == ASCII_MENOS ) ||
	     ( iCod == ASCII_PRODUCTO ) ||
	     ( iCod == ASCII_DIVISION ) ||
	     ( iCod == ASCII_MULTIPLICADOR ) ||
	     ( iCod == ASCII_DIVISOR ) ||
	     ( iCod == ASCII_FUNCION ) ||
	     ( iCod == ASCII_MAS_MENOS ) )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}


int ASCIIEsSignoCont ( char cVal )
{
	int iRes; 
	int iCod;

	iCod = ASCIICodigo ( cVal );	
	if ( ( iCod == ASCII_COMILLA_SIMPLE ) ||
	     ( iCod == ASCII_COMILLA_DOBLE ) ||
	     ( iCod == ASCII_EXCLAMACION_ABR ) ||
	     ( iCod == ASCII_EXCLAMACION_CER ) ||
	     ( iCod == ASCII_INTERROGACION_ABR ) ||
	     ( iCod == ASCII_INTERROGACION_CER ) ||
	     ( iCod == ASCII_PARENTESIS_ABR ) ||
	     ( iCod == ASCII_PARENTESIS_CER ) ||
	     ( iCod == ASCII_CORCHETE_ABR ) ||
	     ( iCod == ASCII_CORCHETE_CER ) ||
	     ( iCod == ASCII_LLAVE_ABR ) ||
	     ( iCod == ASCII_LLAVE_CER ) )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}


int ASCIIEsSignoComp ( char cVal )
{
	int iRes; 
	int iCod;

	iCod = ASCIICodigo ( cVal );	
	if ( ( iCod == ASCII_IGUAL) ||
	     ( iCod == ASCII_MENOR) ||
	     ( iCod == ASCII_MAYOR ) ||
	     ( iCod == ASCII_DOBLE_MENOR ) ||
	     ( iCod == ASCII_DOBLE_MAYOR ) )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}


int ASCIIEsSignoEsp ( char cVal )
{
	int iRes; 
	int iCod;

	iCod = ASCIICodigo ( cVal );	
	if ( ( iCod == ASCII_SOSTENIDO ) ||
	     ( iCod == ASCII_PORCIENTO ) ||
	     ( iCod == ASCII_ET ) ||
	     ( iCod == ASCII_ASTERISCO ) ||
	     ( iCod == ASCII_ARROBA ) ||
	     ( iCod == ASCII_RALLA_INF ) ||
	     ( iCod == ASCII_BARRA ) ||
	     ( iCod == ASCII_BARRA_INCL_DER ) ||
	     ( iCod == ASCII_BARRA_INCL_IZQ ) ||
		 ( iCod == ASCII_ORDINAL_FEM ) ||
		 ( iCod == ASCII_ORDINAL_MAS ) ||
		 ( iCod == ASCII_MARCA_REG ) ||
		 ( iCod == ASCII_DERECHOS_AUT ) ||
		 ( iCod == ASCII_NEGACION ) ||
		 ( iCod == ASCII_FRACCION_1_2 ) ||
		 ( iCod == ASCII_FRACCION_1_4 ) ||
		 ( iCod == ASCII_FRACCION_3_4 ) ||
		 ( iCod == ASCII_BARRA_ALTA ) ||
		 ( iCod == ASCII_BARR_MEDIA ) ||
		 ( iCod == ASCII_BARRA_VERTICAL ) ||
		 ( iCod == ASCII_DOBLE_BARRA_BAJA ) ||
		 ( iCod == ASCII_PARAGRAFO ) ||
		 ( iCod == ASCII_SECCION ) ||
		 ( iCod == ASCII_SUPERINDICE_1 ) ||
		 ( iCod == ASCII_SUPERINDICE_2 ) ||
		 ( iCod == ASCII_SUPERINDICE_3 ) ||
		 ( iCod == ASCII_GRADO ) ||
		 ( iCod == ASCII_PUNTO_MEDIO ) )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}


int ASCIIEsSignoModif ( char cVal )
{
	int iRes; 
	int iCod;

	iCod = ASCIICodigo ( cVal );	
	if ( ( iCod == ASCII_ACENTO_CER ) ||
	     ( iCod == ASCII_ACENTO_ABI ) ||
	     ( iCod == ASCII_ACENTO_CIR ) ||
	     ( iCod == ASCII_TILDE ) ||
	     ( iCod == ASCII_DIERESIS ) )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}


int ASCIIEsSignoMoneda ( char cVal )
{
	int iRes; 
	int iCod;

	iCod = ASCIICodigo ( cVal );	
	if ( ( iCod == ASCII_DOLAR ) || 
		 ( iCod == ASCII_EURO ) ||
		 ( iCod == ASCII_LIBRA ) ||
		 ( iCod == ASCII_YEN ) ||
		 ( iCod == ASCII_CENTIMO ) ||
		 ( iCod == ASCII_DIVISA ) )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int ASCIIEsImprimible ( char cVal )
{
	int iRes; 

	if ( ASCIIEsCodigoControl ( cVal ) == 1 ) 
	{
		if ( ASCIIEsCodigoControlImprimible ( cVal ) == 1 ) 
		{
			iRes = 1;
		}
		else
		{
			iRes = 0;
		}
	}
	else
	{
		iRes = 1;
	}
	return ( iRes );
}

int ASCIIEsValidoToken ( char cVal )
{
	int iRes; 

	if ( ASCIIPerteneceAlJuegoPrincipal ( cVal ) == 1 ) 
	{
		if ( ( ASCIIEsLetra ( cVal ) == 1 ) ||
			 ( ASCIIEsDigito ( cVal ) == 1 ) ||
			 ( ASCIIEsGuionBajo ( cVal ) == 1 ) )
		{
			iRes = 1;
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

int ASCIIEsValidoInicioToken ( char cVal )
{
	int iRes; 

	if ( ASCIIPerteneceAlJuegoPrincipal ( cVal ) == 1 ) 
	{
		if ( ASCIIEsLetra ( cVal ) == 1 ) 
		{
			iRes = 1;
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

int ASCIIEsAlfanumerico ( char cVal )
{
	int iRes; 

	if ( ASCIIPerteneceAlJuegoPrincipal ( cVal ) == 1 ) 
	{
		if ( ( ASCIIEsLetra ( cVal ) == 1 ) ||
			 ( ASCIIEsDigito ( cVal ) == 1 ) )
		{
			iRes = 1;
		}
		else
		{
			iRes = 0;
		}
	}
	else
	{
		iRes = 1;
	}
	return ( iRes );
}

int ASCIIEsValidoIdentificador ( char cVal )
{
	return ( ASCIIEsAlfanumerico ( cVal ) );
}

