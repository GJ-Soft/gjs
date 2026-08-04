
#include "Tipos.h"


#include "BaseConfig.h"
#include "Memoria.h"




const char * TipLiteral ( int iCod )
{
	if ( iCod == TIP_NINGUNO )
	{
		return ( TIP_TXT_NINGUNO );
	}
	else if ( iCod == TIP_DESCONOCIDO )
	{
		return ( TIP_TXT_DESCONOCIDO );
	}
	else if ( iCod == TIP_NUMERO )
	{
		return ( TIP_TXT_NUMERO );
	}
	else if ( iCod == TIP_CADENA )	
	{
		return ( TIP_TXT_CADENA );
	}
	else if ( iCod == TIP_BOOLEANO )	
	{
		return ( TIP_TXT_BOOLEANO );
	}
	else if ( iCod == TIP_CARACTER )	
	{
		return ( TIP_TXT_CARACTER );
	}
	else if ( iCod == TIP_BYTE )	
	{
		return ( TIP_TXT_BYTE );
	}
	else if ( iCod == TIP_TIEMPO )	
	{
		return ( TIP_TXT_TIEMPO );
	}
	else if ( iCod == TIP_BINARIO )	
	{
		return ( TIP_TXT_BINARIO );
	}
	else if ( iCod == TIP_BINARIO_16 )	
	{
		return ( TIP_TXT_BINARIO_16 );
	}
	else if ( iCod == TIP_BINARIO_32 )	
	{
		return ( TIP_TXT_BINARIO_32 );
	}
	else if ( iCod == TIP_BINARIO_64 )	
	{
		return ( TIP_TXT_BINARIO_64 );
	}
	else if ( iCod == TIP_BINARIO_128 )	
	{
		return ( TIP_TXT_BINARIO_128 );
	}
	else if ( iCod == TIP_OBJETO )	
	{
		return ( TIP_TXT_OBJETO );
	}
	else if ( iCod == TIP_NUMERO_NATURAL )
	{
		return ( TIP_TXT_NUMERO_NATURAL );
	}
	else if ( iCod == TIP_NUMERO_ENTERO )
	{
		return ( TIP_TXT_NUMERO_ENTERO );
	}
	else if ( iCod == TIP_NUMERO_REAL )
	{
		return ( TIP_TXT_NUMERO_REAL );
	}
	else if ( iCod == TIP_NUMERO_HEXADECIMAL )
	{
		return ( TIP_TXT_NUMERO_HEXADECIMAL );
	}
	else if ( iCod == TIP_TIEMPO_FECHA )
	{
		return ( TIP_TXT_TIEMPO_FECHA );
	}
	else if ( iCod == TIP_TIEMPO_HORA )
	{
		return ( TIP_TXT_TIEMPO_HORA );
	}
	else if ( iCod == TIP_TIEMPO_FECHA_HORA )
	{
		return ( TIP_TXT_TIEMPO_FECHA_HORA );
	}
	else 
	{
		return ( NULL );
	}
}

int TipCodigo ( const char * p_cTipo )
{
	int iTipo;

	if ( ES_VALIDO ( p_cTipo ) )
	{
		if ( strcmp ( p_cTipo, TIP_TXT_NINGUNO ) == 0 )
		{
			iTipo = TIP_NINGUNO;
		}
		else if ( strcmp ( p_cTipo, TIP_TXT_DESCONOCIDO ) == 0 )
		{
			iTipo = TIP_DESCONOCIDO;
		}
		else if ( strcmp ( p_cTipo, TIP_TXT_NUMERO ) == 0 )
		{
			iTipo = TIP_NUMERO;
		}
		else if ( strcmp ( p_cTipo, TIP_TXT_CADENA ) == 0 )	
		{
			iTipo = TIP_CADENA;
		}
		else if ( strcmp ( p_cTipo, TIP_TXT_BOOLEANO ) == 0 )	
		{
			iTipo = TIP_BOOLEANO;
		}
		else if ( strcmp ( p_cTipo, TIP_TXT_CARACTER ) == 0 )	
		{
			iTipo = TIP_CARACTER;
		}
		else if ( strcmp ( p_cTipo, TIP_TXT_BYTE ) == 0 )	
		{
			iTipo = TIP_BYTE;
		}
		else if ( strcmp ( p_cTipo, TIP_TXT_TIEMPO ) == 0 )
		{
			iTipo = TIP_TIEMPO;
		}
		else if ( strcmp ( p_cTipo, TIP_TXT_BINARIO ) == 0 )
		{
			iTipo = TIP_BINARIO;
		}
		else if ( strcmp ( p_cTipo, TIP_TXT_BINARIO_16 ) == 0 )
		{
			iTipo = TIP_BINARIO_16;
		}
		else if ( strcmp ( p_cTipo, TIP_TXT_BINARIO_32 ) == 0 )
		{
			iTipo = TIP_BINARIO_32;
		}
		else if ( strcmp ( p_cTipo, TIP_TXT_BINARIO_64 ) == 0 )
		{
			iTipo = TIP_BINARIO_64;
		}
		else if ( strcmp ( p_cTipo, TIP_TXT_BINARIO_128 ) == 0 )
		{
			iTipo = TIP_BINARIO_128;
		}
		else if ( strcmp ( p_cTipo, TIP_TXT_OBJETO ) == 0 )
		{
			iTipo = TIP_OBJETO;
		}
		else if ( strcmp ( p_cTipo, TIP_TXT_NUMERO_NATURAL ) == 0 )
		{
			iTipo = TIP_NUMERO_NATURAL;
		}
		else if ( strcmp ( p_cTipo, TIP_TXT_NUMERO_ENTERO ) == 0 )
		{
			iTipo = TIP_NUMERO_ENTERO;
		}
		else if ( strcmp ( p_cTipo, TIP_TXT_NUMERO_REAL ) == 0 )
		{
			iTipo = TIP_NUMERO_REAL;
		}
		else if ( strcmp ( p_cTipo, TIP_TXT_NUMERO_HEXADECIMAL ) == 0 )
		{
			iTipo = TIP_NUMERO_HEXADECIMAL;
		}
		else if ( strcmp ( p_cTipo, TIP_TXT_TIEMPO_FECHA ) == 0 )
		{
			iTipo = TIP_TIEMPO_FECHA;
		}
		else if ( strcmp ( p_cTipo, TIP_TXT_TIEMPO_HORA ) == 0 )
		{
			iTipo = TIP_TIEMPO_HORA;
		}
		else if ( strcmp ( p_cTipo, TIP_TXT_TIEMPO_FECHA_HORA ) == 0 )
		{
			iTipo = TIP_TIEMPO_FECHA_HORA;
		}
		else 
		{
			iTipo = TIP_DESCONOCIDO;
		}
	}
	else 
	{
		iTipo = TIP_NINGUNO;
	}
	return ( iTipo );
}

int TipEsValido ( int iCod )
{
	int iRes;

	if ( ( iCod == TIP_DESCONOCIDO ) ||
		 ( iCod == TIP_NUMERO ) ||
		 ( iCod == TIP_CARACTER ) ||
		 ( iCod == TIP_BYTE ) ||
		 ( iCod == TIP_CADENA ) ||
		 ( iCod == TIP_BOOLEANO ) ||
		 ( iCod == TIP_TIEMPO ) ||
		 ( iCod == TIP_BINARIO ) ||
		 ( iCod == TIP_OBJETO ) ||
		 ( iCod == TIP_NUMERO_NATURAL ) ||
		 ( iCod == TIP_NUMERO_ENTERO ) ||
		 ( iCod == TIP_NUMERO_REAL ) ||
		 ( iCod == TIP_NUMERO_HEXADECIMAL ) ||
		 ( iCod == TIP_BINARIO_16 ) ||
		 ( iCod == TIP_BINARIO_32 ) ||
		 ( iCod == TIP_BINARIO_64 ) ||
		 ( iCod == TIP_BINARIO_128 ) ||
		 ( iCod == TIP_TIEMPO_FECHA ) ||
		 ( iCod == TIP_TIEMPO_HORA ) ||
		 ( iCod == TIP_TIEMPO_FECHA_HORA ) )
	{
		iRes = 1;
	}
	else 
	{
		iRes = 0;
	}
	return ( iRes );
}

int TipEsEstrictamenteValido ( int iCod )
{
	int iRes;

	if ( ( iCod == TIP_NUMERO ) ||
		 ( iCod == TIP_CARACTER ) ||
		 ( iCod == TIP_BYTE ) ||
		 ( iCod == TIP_CADENA ) ||
		 ( iCod == TIP_BOOLEANO ) ||
		 ( iCod == TIP_TIEMPO ) ||
		 ( iCod == TIP_BINARIO ) ||
		 ( iCod == TIP_OBJETO ) ||
		 ( iCod == TIP_NUMERO_NATURAL ) ||
		 ( iCod == TIP_NUMERO_ENTERO ) ||
		 ( iCod == TIP_NUMERO_REAL ) ||
		 ( iCod == TIP_NUMERO_HEXADECIMAL ) ||
		 ( iCod == TIP_BINARIO_16 ) ||
		 ( iCod == TIP_BINARIO_32 ) ||
		 ( iCod == TIP_BINARIO_64 ) ||
		 ( iCod == TIP_BINARIO_128 ) ||
		 ( iCod == TIP_TIEMPO_FECHA ) ||
		 ( iCod == TIP_TIEMPO_HORA ) ||
		 ( iCod == TIP_TIEMPO_FECHA_HORA ) )
	{
		iRes = 1;
	}
	else 
	{
		iRes = 0;
	}
	return ( iRes );
}

int TipEsNinguno ( int iCod )
{
	int iRes;

	if ( iCod == TIP_NINGUNO ) 
	{
		iRes = 1;
	}
	else 
	{
		iRes = 0;
	}
	return ( iRes );
}

int TipEsDesconocido ( int iCod )
{
	int iRes;

	if ( iCod == TIP_DESCONOCIDO ) 
	{
		iRes = 1;
	}
	else 
	{
		iRes = 0;
	}
	return ( iRes );
}

int TipEsNumero ( int iCod )
{
	int iRes;

	if ( ( iCod == TIP_NUMERO ) ||
		 ( iCod == TIP_NUMERO_NATURAL ) ||
		 ( iCod == TIP_NUMERO_ENTERO ) ||
		 ( iCod == TIP_NUMERO_REAL ) ||
		 ( iCod == TIP_NUMERO_HEXADECIMAL ) )
	{
		iRes = 1;
	}
	else 
	{
		iRes = 0;
	}
	return ( iRes );
}

int TipEsCaracter ( int iCod )
{
	int iRes;

	if ( iCod == TIP_CARACTER ) 
	{
		iRes = 1;
	}
	else 
	{
		iRes = 0;
	}
	return ( iRes );
}

int TipEsCadena ( int iCod )
{
	int iRes;

	if ( iCod == TIP_CADENA ) 
	{
		iRes = 1;
	}
	else 
	{
		iRes = 0;
	}
	return ( iRes );
}

int TipEsByte ( int iCod )
{
	int iRes;

	if ( iCod == TIP_BYTE )
	{
		iRes = 1;
	}
	else 
	{
		iRes = 0;
	}
	return ( iRes );
}

int TipEsBooleano ( int iCod )
{
	int iRes;

	if ( iCod == TIP_BOOLEANO )
	{
		iRes = 1;
	}
	else 
	{
		iRes = 0;
	}
	return ( iRes );
}

int TipEsTiempo ( int iCod )
{
	int iRes;

	if ( ( iCod == TIP_TIEMPO ) ||
		 ( iCod == TIP_TIEMPO_FECHA ) ||
		 ( iCod == TIP_TIEMPO_HORA ) ||
		 ( iCod == TIP_TIEMPO_FECHA_HORA ) )
	{
		iRes = 1;
	}
	else 
	{
		iRes = 0;
	}
	return ( iRes );
}

int TipEsBinario ( int iCod )
{
	int iRes;

	if ( ( iCod == TIP_BINARIO ) ||
		 ( iCod == TIP_BINARIO_16 ) ||
		 ( iCod == TIP_BINARIO_32 ) ||
		 ( iCod == TIP_BINARIO_64 ) ||
		 ( iCod == TIP_BINARIO_128 ) )
	{
		iRes = 1;
	}
	else 
	{
		iRes = 0;
	}
	return ( iRes );
}

int TipEsObjeto ( int iCod )
{
	int iRes;

	if ( iCod == TIP_OBJETO )
	{
		iRes = 1;
	}
	else 
	{
		iRes = 0;
	}
	return ( iRes );
}

int TipEsNatural ( int iCod )
{
	int iRes;

	if ( iCod == TIP_NUMERO_NATURAL )
	{
		iRes = 1;
	}
	else 
	{
		iRes = 0;
	}
	return ( iRes );
}

int TipEsEntero ( int iCod )
{
	int iRes;

	if ( iCod == TIP_NUMERO_ENTERO )
	{
		iRes = 1;
	}
	else 
	{
		iRes = 0;
	}
	return ( iRes );
}

int TipEsReal ( int iCod )
{
	int iRes;

	if ( iCod == TIP_NUMERO_REAL )
	{
		iRes = 1;
	}
	else 
	{
		iRes = 0;
	}
	return ( iRes );
}

int TipEsHexadecimal ( int iCod )
{
	int iRes;

	if ( iCod == TIP_NUMERO_HEXADECIMAL )
	{
		iRes = 1;
	}
	else 
	{
		iRes = 0;
	}
	return ( iRes );
}

int TipEsFecha ( int iCod )
{
	int iRes;

	if ( iCod == TIP_TIEMPO_FECHA )
	{
		iRes = 1;
	}
	else 
	{
		iRes = 0;
	}
	return ( iRes );
}

int TipEsHora ( int iCod )
{
	int iRes;

	if ( iCod == TIP_TIEMPO_HORA )
	{
		iRes = 1;
	}
	else 
	{
		iRes = 0;
	}
	return ( iRes );
}

int TipEsFechaHora ( int iCod )
{
	int iRes;

	if ( iCod == TIP_TIEMPO_FECHA_HORA )
	{
		iRes = 1;
	}
	else 
	{
		iRes = 0;
	}
	return ( iRes );
}

int TipEsDeTamVariable ( int iCod )
{
	int iRes;

	if ( ( iCod == TIP_DESCONOCIDO ) ||
		 ( iCod == TIP_CADENA ) ||
		 ( iCod == TIP_BINARIO ) ||
		 ( iCod == TIP_NUMERO ) ||
		 ( iCod == TIP_NUMERO_NATURAL ) ||
		 ( iCod == TIP_NUMERO_ENTERO ) ||
		 ( iCod == TIP_NUMERO_REAL ) ||
		 ( iCod == TIP_NUMERO_HEXADECIMAL ) )
	{
		iRes = 1;
	}
	else 
	{
		iRes = 0;
	}
	return ( iRes );
}

int TipTam ( int iCod )
{
	int iRes;

	// -1=Ninguno/error; 0=Variable
	if ( iCod == TIP_NINGUNO )
	{
		iRes = -1;
	}
	else if ( iCod == TIP_DESCONOCIDO )
	{
		iRes = 0;
	}
	else if ( iCod == TIP_NUMERO )
	{
		iRes = 0;
	}
	else if ( iCod == TIP_CADENA )	
	{
		iRes = 0;
	}
	else if ( iCod == TIP_BOOLEANO )	
	{
		iRes = 1;
	}
	else if ( iCod == TIP_CARACTER )	
	{
		iRes = 1;
	}
	else if ( iCod == TIP_BYTE )	
	{
		iRes = 1;
	}
	else if ( iCod == TIP_TIEMPO )	
	{
		iRes = 14;
	}
	else if ( iCod == TIP_NUMERO_NATURAL )
	{
		iRes = 0;
	}
	else if ( iCod == TIP_NUMERO_ENTERO )
	{
		iRes = 0;
	}
	else if ( iCod == TIP_NUMERO_REAL )
	{
		iRes = 0;
	}
	else if ( iCod == TIP_NUMERO_HEXADECIMAL )
	{
		iRes = 0;
	}
	else if ( iCod == TIP_BINARIO )
	{
		iRes = 0;
	}
	else if ( iCod == TIP_BINARIO_16 )
	{
		iRes = 2;
	}
	else if ( iCod == TIP_BINARIO_32 ) 
	{
		iRes = 4;
	}
	else if ( iCod == TIP_BINARIO_64 ) 
	{
		iRes = 8;
	}
	else if ( iCod == TIP_BINARIO_128 ) 
	{
		iRes = 16;
	}
	else if ( iCod == TIP_TIEMPO_FECHA )
	{
		iRes = 8;
	}
	else if ( iCod == TIP_TIEMPO_HORA )
	{
		iRes = 6;
	}
	else if ( iCod == TIP_TIEMPO_FECHA_HORA )
	{
		iRes = 14;
	}
	else 
	{
		iRes = -1;
	}
	return ( iRes );
}





