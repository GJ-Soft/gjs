#include "SBloque.h"


#include "TiposBasicosConfig.h"


SBloque * SBlqCrear ( int iTam )
{
	SBloque * p_blqObj;

	if ( iTam > 0 )
	{
		p_blqObj = (SBloque *) MemReservar ( sizeof ( SBloque ) );
		if ( ES_VALIDO ( p_blqObj ) )
		{
			p_blqObj->iLiberar = 1;
			p_blqObj->p_byDatos = (byte *) MemReservar ( iTam );
			if ( ES_VALIDO ( p_blqObj->p_byDatos ) )
			{
				p_blqObj->iTam = iTam;
			}
			else
			{
				p_blqObj->iTam = 0;
			}
		}
	}
	else
	{
		p_blqObj = NULL;
	}
	return ( p_blqObj );
}

SBloque * SBlqAsignar ( byte * p_byDirDatos, int iTam, int iLiberar )
{
	SBloque * p_blqObj;

	if ( ES_VALIDO ( p_byDirDatos ) && ( iTam > 0 ) && BOOL_VALIDO ( iLiberar ) &&
		 ( MemEsValida ( (void *) p_byDirDatos ) == 1 ) )
	{
		p_blqObj= (SBloque *) MemReservar ( sizeof ( SBloque ) );
		if ( ES_VALIDO ( p_blqObj ) )
		{
			p_blqObj->iLiberar = iLiberar;
			p_blqObj->p_byDatos = p_byDirDatos;
			p_blqObj->iTam = iTam;
		}
	}
	else
	{
		p_blqObj = NULL;
	}
	return ( p_blqObj );
}

SBloque * SBlqCrearEntero ()
{
	return ( SBlqCrear ( sizeof ( int ) ) );
}

SBloque * SBlqCrearEnteroLargo ()
{
	return ( SBlqCrear ( sizeof ( long ) ) );
}

SBloque * SBlqCrearEnteroSinSigno ()
{
	return ( SBlqCrear ( sizeof ( unsigned int ) ) );
}

SBloque * SBlqCrearEnteroLargoSinSigno ()
{
	return ( SBlqCrear ( sizeof ( unsigned long ) ) );
}

SBloque * SBlqCrearReal ()
{
	return ( SBlqCrear ( sizeof ( float ) ) );
}

SBloque * SBlqCrearRealDoble ()
{
	return ( SBlqCrear ( sizeof ( double ) ) );
}

SBloque * SBlqCrearCadena ()
{
	return ( SBlqCrear ( sizeof ( char * ) ) );
}

void SBlqDestruir ( SBloque ** p_p_blqObj )
{
	SBloque * p_blqObj;

	if ( ES_VALIDO ( p_p_blqObj ) )
	{
		p_blqObj = *p_p_blqObj;

		if ( ES_VALIDO ( p_blqObj ) )
		{
			if ( p_blqObj->iLiberar == 1 )
			{
				MemLiberar ( (void **) &(p_blqObj->p_byDatos) );
			}
			MemLiberar ( (void **) p_p_blqObj );
		}
	}
}

int SBlqEsValido ( SBloque * p_blqObj )
{
	int iRes;

	if ( ES_VALIDO ( p_blqObj ) )
	{
		if ( ES_VALIDO ( p_blqObj->p_byDatos ) &&
			 ( p_blqObj->iTam > 0 ) )
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

int SBlqTam ( SBloque * p_blqObj )
{
	int iRes;

	if ( ES_VALIDO ( p_blqObj ) )
	{
		iRes = p_blqObj->iTam;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

byte * SBlqDatos ( SBloque * p_blqObj )
{
	byte * p_byRes;

	if ( ES_VALIDO ( p_blqObj ) )
	{
		p_byRes = p_blqObj->p_byDatos;
	}
	else
	{
		p_byRes = NULL;
	}
	return ( p_byRes );
}

byte * SBlqDuplicarDatos ( SBloque * p_blqObj )
{
	byte * p_byRes;

	if ( ES_VALIDO ( p_blqObj ) )
	{
		p_byRes = (byte *) MemReservar ( p_blqObj->iTam );
		if ( ES_VALIDO ( p_byRes ) )
		{
			MemCopiar ( (void *) p_byRes, (void *) p_blqObj->p_byDatos, p_blqObj->iTam );
		}
	}
	else
	{
		p_byRes = NULL;
	}
	return ( p_byRes );
}

byte * SBlqDatosEnPos ( SBloque * p_blqObj, int iPos )
{
	byte * p_byRes;

	if ( ES_VALIDO ( p_blqObj ) )
	{
		if ( ( iPos >= 0 ) && ( iPos < p_blqObj->iTam ) )
		{
			p_byRes = &(p_blqObj->p_byDatos [ iPos ]);
		}
		else
		{
			p_byRes = NULL;
		}
	}
	else
	{
		p_byRes = NULL;
	}
	return ( p_byRes );
}

int SBlqEntero ( SBloque * p_blqObj )
{
	int		iRes;
	int *	p_iVal;

	p_iVal = (int *) SBlqDatos ( p_blqObj );
	if ( ES_VALIDO ( p_iVal ) )
	{
		iRes = *p_iVal;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

long SBlqEnteroLargo ( SBloque * p_blqObj )
{
	long	lRes;
	long *	p_lVal;

	p_lVal = (long *) SBlqDatos ( p_blqObj );
	if ( ES_VALIDO ( p_lVal ) )
	{
		lRes = *p_lVal;
	}
	else
	{
		lRes = 0;
	}
	return ( lRes );
}

unsigned int SBlqEnteroSinSigno ( SBloque * p_blqObj )
{
	unsigned int	uiRes;
	unsigned int *	p_iVal;

	p_iVal = (unsigned int *) SBlqDatos ( p_blqObj );
	if ( ES_VALIDO ( p_iVal ) )
	{
		uiRes = *p_iVal;
	}
	else
	{
		uiRes = 0;
	}
	return ( uiRes );
}

unsigned long SBlqEnteroLargoSinSigno ( SBloque * p_blqObj )
{
	unsigned long	ulRes;
	unsigned long *	p_lVal;

	p_lVal = (unsigned long *) SBlqDatos ( p_blqObj );
	if ( ES_VALIDO ( p_lVal ) )
	{
		ulRes = *p_lVal;
	}
	else
	{
		ulRes = 0;
	}
	return ( ulRes );
}

float SBlqReal ( SBloque * p_blqObj )
{
	float	fRes;
	float *	p_fVal;

	p_fVal = (float *) SBlqDatos ( p_blqObj );
	if ( ES_VALIDO ( p_fVal ) )
	{
		fRes = *p_fVal;
	}
	else
	{
		fRes = 0;
	}
	return ( fRes );
}

double SBlqRealDoble ( SBloque * p_blqObj )
{
	double		dRes;
	double *	p_dVal;

	p_dVal = (double *) SBlqDatos ( p_blqObj );
	if ( ES_VALIDO ( p_dVal ) )
	{
		dRes = *p_dVal;
	}
	else
	{
		dRes = 0;
	}
	return ( dRes );
}

char * SBlqCadena ( SBloque * p_blqObj )
{
	char *	p_cRes;
	char **	p_p_cVal;

	p_p_cVal = (char **) SBlqDatos ( p_blqObj );
	if ( ES_VALIDO ( p_p_cVal ) )
	{
		p_cRes = *p_p_cVal;
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

int SBlqEsIgual ( SBloque * p_blqObj1, SBloque * p_blqObj2 )
{
	int	iRes;

	if ( ES_VALIDO ( p_blqObj1 ) && ES_VALIDO ( p_blqObj2 ) )
	{
		if ( SBlqTam ( p_blqObj1 ) == SBlqTam ( p_blqObj2 ) )
		{
			iRes = MemEsIgual ( ( void * ) SBlqDatos ( p_blqObj1 ), ( void * ) SBlqDatos ( p_blqObj2 ), SBlqTam ( p_blqObj1 ) );
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

int SBlqEsIgualExt ( SBloque * p_blqObj, byte * p_byDatos )
{
	int	iRes;

	if ( ES_VALIDO ( p_blqObj ) && ES_VALIDO ( p_byDatos ) )
	{
		if ( SBlqTam ( p_blqObj ) >= 0 )
		{
			iRes = MemEsIgual ( ( void * ) SBlqDatos ( p_blqObj ), ( void * ) p_byDatos, SBlqTam ( p_blqObj ) );
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

int SBlqLiberacionMemoriaActivada ( SBloque * p_blqObj )
{
	int iRes;

	if ( ES_VALIDO ( p_blqObj ) )
	{
		iRes = p_blqObj->iLiberar;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SBlqLimpiar ( SBloque * p_blqObj )
{
	int	iRes;

	if ( ES_VALIDO ( p_blqObj ) )
	{
		if ( ES_VALIDO ( p_blqObj->p_byDatos ) )
		{
			MemLimpiar ( (void *) &(p_blqObj->p_byDatos [0]), p_blqObj->iTam );
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

byte SBlqLeerByte ( SBloque * p_blqObj, int iPos )
{
	byte byRes;

	byRes = 0x00;
	if ( ES_VALIDO ( p_blqObj ) )
	{
		if ( ( iPos >= 0 ) && ( iPos < p_blqObj->iTam ) && ES_VALIDO ( p_blqObj->p_byDatos ) )
		{
			byRes = p_blqObj->p_byDatos [ iPos ];
		}
	}
	return ( byRes );
}

int SBlqEscribirByte ( SBloque * p_blqObj, int iPos, byte byValor )
{
	int iRes;

	if ( ES_VALIDO ( p_blqObj ) )
	{
		if ( ( iPos >= 0 ) && ( iPos < p_blqObj->iTam ) && ES_VALIDO ( p_blqObj->p_byDatos ) )
		{
			p_blqObj->p_byDatos [ iPos ] = byValor;
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

int SBlqEscribirEntero ( SBloque * p_blqObj, int iValor )
{
	int iRes;

	if ( ES_VALIDO ( p_blqObj ) )
	{
		if ( p_blqObj->iTam == sizeof ( int ) )
		{
			MemCopiar ( &(p_blqObj->p_byDatos [0]), (byte *) &iValor, sizeof ( int ) );
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

int SBlqEscribirEnteroLargo ( SBloque * p_blqObj, long lValor )
{
	int iRes;

	if ( ES_VALIDO ( p_blqObj ) )
	{
		if ( p_blqObj->iTam == sizeof ( long ) )
		{
			MemCopiar ( &(p_blqObj->p_byDatos [0]), (byte *) &lValor, sizeof ( long ) );
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

int SBlqEscribirEnteroSinSigno ( SBloque * p_blqObj, unsigned int uiValor )
{
	int iRes;

	if ( ES_VALIDO ( p_blqObj ) )
	{
		if ( p_blqObj->iTam == sizeof ( unsigned int ) )
		{
			MemCopiar ( &(p_blqObj->p_byDatos [0]), (byte *) &uiValor, sizeof ( unsigned int ) );
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

int SBlqEscribirEnteroLargoSinSigno ( SBloque * p_blqObj, unsigned long ulValor )
{
	int iRes;

	if ( ES_VALIDO ( p_blqObj ) )
	{
		if ( p_blqObj->iTam == sizeof ( unsigned long ) )
		{
			MemCopiar ( &(p_blqObj->p_byDatos [0]), (byte *) &ulValor, sizeof ( unsigned long ) );
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

int SBlqEscribirReal ( SBloque * p_blqObj, float fValor )
{
	int iRes;

	if ( ES_VALIDO ( p_blqObj ) )
	{
		if ( p_blqObj->iTam == sizeof ( float) )
		{
			MemCopiar ( &(p_blqObj->p_byDatos [0]), (byte *) &fValor, sizeof ( float ) );
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

int SBlqEscribirRealDoble ( SBloque * p_blqObj, double dValor )
{
	int iRes;

	if ( ES_VALIDO ( p_blqObj ) )
	{
		if ( p_blqObj->iTam == sizeof ( double ) )
		{
			MemCopiar ( &(p_blqObj->p_byDatos [0]), (byte *) &dValor, sizeof ( double ) );
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

int SBlqEscribirCadena ( SBloque * p_blqObj, const char * p_cValor )
{
	int iTam;
	int iRes;

	if ( ES_VALIDO ( p_blqObj ) && ES_VALIDO ( p_cValor ) )
	{
		MemLimpiar ( (void *) &(p_blqObj->p_byDatos [0]), p_blqObj->iTam );
		if ( p_blqObj->iTam <= CadLongitud ( p_cValor ) + 1 )
		{
			iTam = p_blqObj->iTam;
		}
		else
		{
			iTam = CadLongitud ( p_cValor );
		}
		MemCopiar ( &(p_blqObj->p_byDatos [0]), (byte *) p_cValor, iTam );
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

static char * _SBlqLeerCadena ( SBloque * p_blqObj, int iPos, int * p_iLong )
{
	char *	p_cRes;
	int		iLong;

	p_cRes = NULL;
	*p_iLong = -1;
	if ( SBlqEsValido ( p_blqObj ) == 1 )
	{
		if ( iPos >= 0 )
		{
			if ( iPos < p_blqObj->iTam )
			{
				// El nulo tiene que estar dentro del bloque:
				iLong = MemDistanciaAPrimerNulo ( (void *) &(p_blqObj->p_byDatos [ iPos ]), p_blqObj->iTam - iPos );
				if ( iLong >= 0 )
				{
					p_cRes = CadCrear ( iLong );
					if ( ES_VALIDO ( p_cRes ) )
					{
						MemCopiar ( (void *) p_cRes, (void *) &(p_blqObj->p_byDatos [ iPos ]), iLong );
						*p_iLong = iLong;
					}
				}
			}
			else
			{
				ERROR_ESTABLECER ( ERR_LECTURA_MEMORIA );
			}
		}
		else
		{
			ERROR_ESTABLECER ( ERR_LECTURA_MEMORIA );
		}
	}
	else
	{
		ERROR_ESTABLECER ( ERR_LECTURA_MEMORIA );
	}
	return ( p_cRes );
}

int SBlqLeerEnteroEnPos ( SBloque * p_blqObj, int iPos )
{
	int iRes;

	if ( SBlqLeerBuffer ( p_blqObj, iPos, (byte *) &iRes, sizeof ( iRes ) ) == 0 )
	{
		ERROR_ESTABLECER ( ERR_LECTURA_MEMORIA );
		iRes = 0;
	}
	return ( iRes );
}

long SBlqLeerEnteroLargoEnPos ( SBloque * p_blqObj, int iPos )
{
	long lRes;

	if ( SBlqLeerBuffer ( p_blqObj, iPos, (byte *) &lRes, sizeof ( lRes ) ) == 0 )
	{
		ERROR_ESTABLECER ( ERR_LECTURA_MEMORIA );
		lRes = 0;
	}
	return ( lRes );
}

float SBlqLeerRealEnPos ( SBloque * p_blqObj, int iPos )
{
	float fRes;

	if ( SBlqLeerBuffer ( p_blqObj, iPos, (byte *) &fRes, sizeof ( fRes ) ) == 0 )
	{
		ERROR_ESTABLECER ( ERR_LECTURA_MEMORIA );
		fRes = 0;
	}
	return ( fRes );
}

unsigned int SBlqLeerEnteroSinSignoEnPos ( SBloque * p_blqObj, int iPos )
{
	unsigned int uiRes;

	if ( SBlqLeerBuffer ( p_blqObj, iPos, (byte *) &uiRes, sizeof ( uiRes ) ) == 0 )
	{
		ERROR_ESTABLECER ( ERR_LECTURA_MEMORIA );
		uiRes = 0;
	}
	return ( uiRes );
}

unsigned long SBlqLeerEnteroLargoSinSignoEnPos ( SBloque * p_blqObj, int iPos )
{
	unsigned long ulRes;

	if ( SBlqLeerBuffer ( p_blqObj, iPos, (byte *) &ulRes, sizeof ( ulRes ) ) == 0 )
	{
		ERROR_ESTABLECER ( ERR_LECTURA_MEMORIA );
		ulRes = 0;
	}
	return ( ulRes );
}

double SBlqLeerRealDobleEnPos ( SBloque * p_blqObj, int iPos )
{
	double dRes;

	if ( SBlqLeerBuffer ( p_blqObj, iPos, (byte *) &dRes, sizeof ( dRes ) ) == 0 )
	{
		ERROR_ESTABLECER ( ERR_LECTURA_MEMORIA );
		dRes = 0;
	}
	return ( dRes );
}

char * SBlqLeerCadenaEnPos ( SBloque * p_blqObj, int iPos )
{
	int iLong;

	return ( _SBlqLeerCadena ( p_blqObj, iPos, &iLong ) );
}

int SBlqEscribirEnteroEnPos ( SBloque * p_blqObj, int iPos, int iValor )
{
	return ( SBlqEscribirBuffer ( p_blqObj, iPos, (byte *) &iValor, sizeof ( int ) ) );
}

int SBlqEscribirEnteroLargoEnPos ( SBloque * p_blqObj, int iPos, long lValor )
{
	return ( SBlqEscribirBuffer ( p_blqObj, iPos, (byte *) &lValor, sizeof ( long ) ) );
}

int SBlqEscribirRealEnPos ( SBloque * p_blqObj, int iPos, float fValor )
{
	return ( SBlqEscribirBuffer ( p_blqObj, iPos, (byte *) &fValor, sizeof ( float ) ) );
}

int SBlqEscribirEnteroSinSignoEnPos ( SBloque * p_blqObj, int iPos, unsigned int uiValor )
{
	return ( SBlqEscribirBuffer ( p_blqObj, iPos, (byte *) &uiValor, sizeof ( unsigned int ) ) );
}

int SBlqEscribirEnteroLargoSinSignoEnPos ( SBloque * p_blqObj, int iPos, unsigned long ulValor )
{
	return ( SBlqEscribirBuffer ( p_blqObj, iPos, (byte *) &ulValor, sizeof ( unsigned long) ) );
}

int SBlqEscribirRealDobleEnPos ( SBloque * p_blqObj, int iPos, double dValor )
{
	return ( SBlqEscribirBuffer ( p_blqObj, iPos, (byte *) &dValor, sizeof ( double ) ) );
}

int SBlqEscribirCadenaEnPos ( SBloque * p_blqObj, int iPos, const char * p_cValor )
{
	int iRes;

	// Con el nulo, para que SBlqLeerCadenaEnPos sepa donde acaba:
	if ( ES_VALIDO ( p_cValor ) )
	{
		iRes = SBlqEscribirBuffer ( p_blqObj, iPos, (byte *) p_cValor, CadLongitud ( p_cValor ) + 1 );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SBlqLeerBuffer ( SBloque * p_blqObj, int iPos, byte * p_byValor, int iTam )
{
	int iRes;

	if ( SBlqEsValido ( p_blqObj ) == 1 )
	{
		if ( ES_VALIDO ( p_byValor ) )
		{
			if ( iTam > 0 )
			{
				if ( iPos >= 0 )
				{
					// Restando no se desborda con posiciones grandes:
					if ( iTam <= p_blqObj->iTam - iPos )
					{
						MemCopiar ( (void *) p_byValor, (void *) &(p_blqObj->p_byDatos [ iPos ]), iTam );
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

int SBlqEscribirBuffer ( SBloque * p_blqObj, int iPos, byte * p_byValor, int iTam )
{
	int iRes;

	if ( ES_VALIDO ( p_blqObj ) && ES_VALIDO ( p_byValor ) )
	{
		if ( ( iPos >= 0 ) && ( iPos + iTam <= p_blqObj->iTam ) )
		{
			MemCopiar ( &(p_blqObj->p_byDatos [ iPos ]), &(p_byValor [ 0 ]), iTam );
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

byte SBlqLeerByteExt ( SBloque * p_blqObj, int * p_iPos )
{
	byte byRes;

	if ( SBlqLeerBufferExt ( p_blqObj, p_iPos, &byRes, 1 ) == 0 )
	{
		byRes = 0x00;
	}
	return ( byRes );
}

int SBlqEscribirByteExt ( SBloque * p_blqObj, int * p_iPos, byte byValor )
{
	return ( SBlqEscribirBufferExt ( p_blqObj, p_iPos, &byValor, 1 ) );
}

int SBlqLeerEnteroEnPosExt ( SBloque * p_blqObj, int * p_iPos )
{
	int iRes;

	if ( SBlqLeerBufferExt ( p_blqObj, p_iPos, (byte *) &iRes, sizeof ( iRes ) ) == 0 )
	{
		ERROR_ESTABLECER ( ERR_LECTURA_MEMORIA );
		iRes = 0;
	}
	return ( iRes );
}

long SBlqLeerEnteroLargoEnPosExt ( SBloque * p_blqObj, int * p_iPos )
{
	long lRes;

	if ( SBlqLeerBufferExt ( p_blqObj, p_iPos, (byte *) &lRes, sizeof ( lRes ) ) == 0 )
	{
		ERROR_ESTABLECER ( ERR_LECTURA_MEMORIA );
		lRes = 0;
	}
	return ( lRes );
}

float SBlqLeerRealEnPosExt ( SBloque * p_blqObj, int * p_iPos )
{
	float fRes;

	if ( SBlqLeerBufferExt ( p_blqObj, p_iPos, (byte *) &fRes, sizeof ( fRes ) ) == 0 )
	{
		ERROR_ESTABLECER ( ERR_LECTURA_MEMORIA );
		fRes = 0;
	}
	return ( fRes );
}

unsigned int SBlqLeerEnteroSinSignoEnPosExt ( SBloque * p_blqObj, int * p_iPos )
{
	unsigned int uiRes;

	if ( SBlqLeerBufferExt ( p_blqObj, p_iPos, (byte *) &uiRes, sizeof ( uiRes ) ) == 0 )
	{
		ERROR_ESTABLECER ( ERR_LECTURA_MEMORIA );
		uiRes = 0;
	}
	return ( uiRes );
}

unsigned long SBlqLeerEnteroLargoSinSignoEnPosExt ( SBloque * p_blqObj, int * p_iPos )
{
	unsigned long ulRes;

	if ( SBlqLeerBufferExt ( p_blqObj, p_iPos, (byte *) &ulRes, sizeof ( ulRes ) ) == 0 )
	{
		ERROR_ESTABLECER ( ERR_LECTURA_MEMORIA );
		ulRes = 0;
	}
	return ( ulRes );
}

double SBlqLeerRealDobleEnPosExt ( SBloque * p_blqObj, int * p_iPos )
{
	double dRes;

	if ( SBlqLeerBufferExt ( p_blqObj, p_iPos, (byte *) &dRes, sizeof ( dRes ) ) == 0 )
	{
		ERROR_ESTABLECER ( ERR_LECTURA_MEMORIA );
		dRes = 0;
	}
	return ( dRes );
}

char * SBlqLeerCadenaEnPosExt ( SBloque * p_blqObj, int * p_iPos )
{
	char *	p_cRes;
	int		iLong;

	if ( ES_VALIDO ( p_iPos ) )
	{
		p_cRes = _SBlqLeerCadena ( p_blqObj, *p_iPos, &iLong );
		if ( ES_VALIDO ( p_cRes ) )
		{
			// Avanza tambien el nulo:
			*p_iPos = *p_iPos + iLong + 1;
		}
	}
	else
	{
		ERROR_ESTABLECER ( ERR_LECTURA_MEMORIA );
		p_cRes = NULL;
	}
	return ( p_cRes );
}

int SBlqEscribirEnteroEnPosExt ( SBloque * p_blqObj, int * p_iPos, int iValor )
{
	return ( SBlqEscribirBufferExt ( p_blqObj, p_iPos, (byte *) &iValor, sizeof ( int ) ) );
}

int SBlqEscribirEnteroLargoEnPosExt ( SBloque * p_blqObj, int * p_iPos, long lValor )
{
	return ( SBlqEscribirBufferExt ( p_blqObj, p_iPos, (byte *) &lValor, sizeof ( long ) ) );
}

int SBlqEscribirRealEnPosExt ( SBloque * p_blqObj, int * p_iPos, float fValor )
{
	return ( SBlqEscribirBufferExt ( p_blqObj, p_iPos, (byte *) &fValor, sizeof ( float ) ) );
}

int SBlqEscribirEnteroSinSignoEnPosExt ( SBloque * p_blqObj, int * p_iPos, unsigned int uiValor )
{
	return ( SBlqEscribirBufferExt ( p_blqObj, p_iPos, (byte *) &uiValor, sizeof ( unsigned int ) ) );
}

int SBlqEscribirEnteroLargoSinSignoEnPosExt ( SBloque * p_blqObj, int * p_iPos, unsigned long ulValor )
{
	return ( SBlqEscribirBufferExt ( p_blqObj, p_iPos, (byte *) &ulValor, sizeof ( unsigned long ) ) );
}

int SBlqEscribirRealDobleEnPosExt ( SBloque * p_blqObj, int * p_iPos, double dValor )
{
	return ( SBlqEscribirBufferExt ( p_blqObj, p_iPos, (byte *) &dValor, sizeof ( double ) ) );
}

int SBlqEscribirCadenaEnPosExt ( SBloque * p_blqObj, int * p_iPos, const char * p_cValor )
{
	int iRes;

	// Con el nulo, para que SBlqLeerCadenaEnPosExt sepa donde acaba:
	if ( ES_VALIDO ( p_cValor ) )
	{
		iRes = SBlqEscribirBufferExt ( p_blqObj, p_iPos, (byte *) p_cValor, CadLongitud ( p_cValor ) + 1 );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SBlqLeerBufferExt ( SBloque * p_blqObj, int * p_iPos, byte * p_byValor, int iTam )
{
	int iRes;

	if ( ES_VALIDO ( p_iPos ) )
	{
		iRes = SBlqLeerBuffer ( p_blqObj, *p_iPos, p_byValor, iTam );
		if ( iRes == 1 )
		{
			*p_iPos = *p_iPos + iTam;
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SBlqEscribirBufferExt ( SBloque * p_blqObj, int * p_iPos, byte * p_byValor, int iTam )
{
	int iRes;

	if ( ES_VALIDO ( p_iPos ) )
	{
		if ( iTam > 0 )
		{
			iRes = SBlqEscribirBuffer ( p_blqObj, *p_iPos, p_byValor, iTam );
			if ( iRes == 1 )
			{
				*p_iPos = *p_iPos + iTam;
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

int SBlqCopiarDe ( SBloque * p_blqObj, byte * p_byValor )
{
	int iRes;

	if ( ES_VALIDO ( p_blqObj ) && ES_VALIDO ( p_byValor ) )
	{
		if ( p_blqObj->iTam > 0 )
		{
			MemCopiar ( &(p_blqObj->p_byDatos [0]), p_byValor, p_blqObj->iTam );
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

int SBlqCopiarEn ( SBloque * p_blqObj, byte * p_byValor )
{
	int iRes;

	if ( ES_VALIDO ( p_blqObj ) && ES_VALIDO ( p_byValor ) )
	{
		if ( p_blqObj->iTam > 0 )
		{
			MemCopiar ( p_byValor, &(p_blqObj->p_byDatos [0]), p_blqObj->iTam );
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

int SBlqCopiar ( SBloque * p_blqDest, SBloque * p_blqOrig )
{
	int iRes;

	if ( ES_VALIDO ( p_blqOrig ) && ES_VALIDO ( p_blqDest ) )
	{
		if ( ( p_blqOrig->iTam > 0 ) && ( p_blqOrig->iTam <= p_blqDest->iTam  ) )
		{
			MemCopiar ( &(p_blqDest->p_byDatos [0]), &(p_blqOrig->p_byDatos [0]), p_blqOrig->iTam );
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

SBloque * SBlqDuplicar ( SBloque * p_blqObj )
{
	SBloque * p_blqDup;

	if ( ES_VALIDO ( p_blqObj ) )
	{
		p_blqDup = SBlqCrear ( p_blqObj->iTam );
		if ( ES_VALIDO ( p_blqDup ) )
		{
			SBlqCopiar ( p_blqDup, p_blqObj );
		}
	}
	else
	{
		p_blqDup = NULL;
	}
	return ( p_blqDup );
}

int SBlqEsCompatible ( SBloque * p_blqObj, SBloque * p_blqComp )
{
	int iRes;

	if ( ES_VALIDO ( p_blqObj ) && ES_VALIDO ( p_blqComp ) )
	{
		if ( ( p_blqObj->iTam > 0 ) && ( p_blqObj->iTam == p_blqComp->iTam  ) )
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

int SBlqTamCompatible ( SBloque * p_blqObj, int iTam )
{
	int iRes;

	if ( ES_VALIDO ( p_blqObj ) )
	{
		if ( ( p_blqObj->iTam > 0 ) && ( p_blqObj->iTam == iTam  ) )
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

int SBlqVolcar ( SBloque * p_blqObj, int iPos, SBloque * p_blqDatos )
{
	int iRes;

	if ( ES_VALIDO ( p_blqObj ) && ES_VALIDO ( p_blqDatos ) )
	{
		if ( ( p_blqObj->iTam > 0 ) && ( SBlqTam ( p_blqDatos ) > 0 ) && ( iPos >= 0 ) &&
			 ( SBlqTam ( p_blqDatos ) + iPos <= p_blqObj->iTam ) )
		{
			iRes = SBlqEscribirBuffer ( p_blqObj, iPos, SBlqDatos ( p_blqDatos ), SBlqTam ( p_blqDatos ) );
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

SBloque * SBlqExtraer ( SBloque * p_blqObj, int iPos, int iTam )
{
	SBloque * p_blqDatos;

	if ( ES_VALIDO ( p_blqObj ) )
	{
		if ( ( p_blqObj->iTam > 0 ) && ( iTam > 0 ) && ( iPos >= 0 ) &&
			 ( iTam + iPos <= p_blqObj->iTam ) )
		{
			p_blqDatos = SBlqCrear ( iTam );
			if ( ES_VALIDO ( p_blqDatos ) )
			{
				if ( SBlqEscribirBuffer ( p_blqDatos, 0, SBlqDatosEnPos ( p_blqObj, iPos ), iTam ) == 0 )
				{
					SBlqDestruir ( &p_blqDatos );
				}
			}
		}
		else
		{
			p_blqDatos = NULL;
		}
	}
	else
	{
		p_blqDatos = NULL;
	}
	return ( p_blqDatos );
}

int SBlqVolcarExt ( SBloque * p_blqObj, int * p_iPos, SBloque * p_blqDatos )
{
	int iRes;

	if ( ES_VALIDO ( p_iPos ) )
	{
		iRes = SBlqVolcar ( p_blqObj, *p_iPos, p_blqDatos );
		if ( iRes == 1 )
		{
			*p_iPos = *p_iPos + SBlqTam ( p_blqDatos );
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

SBloque * SBlqExtraerExt ( SBloque * p_blqObj, int * p_iPos, int iTam )
{
	SBloque * p_blqDatos;

	if ( ES_VALIDO ( p_iPos ) )
	{
		p_blqDatos = SBlqExtraer ( p_blqObj, *p_iPos, iTam );
		if ( ES_VALIDO ( p_blqDatos ) )
		{
			*p_iPos = *p_iPos + iTam;
		}
	}
	else
	{
		p_blqDatos = NULL;
	}
	return ( p_blqDatos );
}

unsigned int SBlqHash ( SBloque * p_blqObj )
{
	unsigned int uiRes = 0;

	if ( ES_VALIDO ( p_blqObj ) )
	{
		uiRes = HashBinario ( p_blqObj->p_byDatos, p_blqObj->iTam );
	}
	return ( uiRes );
}
