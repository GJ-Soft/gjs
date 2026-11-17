#include "SBloqueMultiPlataforma.h"


#include "TiposBasicosConfig.h"


/* Zona de iTam bytes a partir de iPos, si cabe entera en el bloque; si no,
   NULL. */
static byte * _SBlqMplZona ( SBloqueMultiPlataforma * p_blqObj, int iPos, int iTam )
{
	byte * p_byRes;

	if ( ES_VALIDO ( p_blqObj ) )
	{
		if ( iPos >= 0 )
		{
			if ( iTam <= SBlqTam ( p_blqObj->p_blqDatos ) - iPos )
			{
				p_byRes = SBlqDatosEnPos ( p_blqObj->p_blqDatos, iPos );
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
	}
	else
	{
		p_byRes = NULL;
	}
	return ( p_byRes );
}

/* Como _SBlqMplZona en *p_iPos, sin moverla. */
static byte * _SBlqMplZonaEnPuntero ( SBloqueMultiPlataforma * p_blqObj, int * p_iPos, int iTam )
{
	byte * p_byRes;

	if ( ES_VALIDO ( p_iPos ) )
	{
		p_byRes = _SBlqMplZona ( p_blqObj, *p_iPos, iTam );
	}
	else
	{
		p_byRes = NULL;
	}
	return ( p_byRes );
}

/* Como _SBlqMplZona en *p_iPos, y si la zona cabe deja *p_iPos detrás de
   ella. */
static byte * _SBlqMplZonaExt ( SBloqueMultiPlataforma * p_blqObj, int * p_iPos, int iTam )
{
	byte * p_byRes;

	p_byRes = _SBlqMplZonaEnPuntero ( p_blqObj, p_iPos, iTam );
	if ( ES_VALIDO ( p_byRes ) )
	{
		*p_iPos = *p_iPos + iTam;
	}
	return ( p_byRes );
}

/* El bloque entero, si mide exactamente iTam bytes; si no, NULL. */
static byte * _SBlqMplZonaTotal ( SBloqueMultiPlataforma * p_blqObj, int iTam )
{
	byte * p_byRes;

	if ( SBlqMplTam ( p_blqObj ) == iTam )
	{
		p_byRes = _SBlqMplZona ( p_blqObj, 0, iTam );
	}
	else
	{
		p_byRes = NULL;
	}
	return ( p_byRes );
}

/* Envuelve un bloque recién creado. Si no se puede, lo destruye para que no
   se pierda. */
static SBloqueMultiPlataforma * _SBlqMplEnvolverNuevo ( SBloque * p_blqDatos )
{
	SBloqueMultiPlataforma * p_blqObj;

	p_blqObj = SBlqMplEncapsular ( p_blqDatos );
	if ( ES_NULO ( p_blqObj ) )
	{
		SBlqDestruir ( &p_blqDatos );
	}
	return ( p_blqObj );
}




SBloqueMultiPlataforma * SBlqMplCrear ( int iTam )
{
	return ( _SBlqMplEnvolverNuevo ( SBlqCrear ( iTam ) ) );
}

SBloqueMultiPlataforma * SBlqMplAsignar ( byte * p_byDirDatos, int iTam, int iLiberar )
{
	return ( _SBlqMplEnvolverNuevo ( SBlqAsignar ( p_byDirDatos, iTam, iLiberar ) ) );
}

/* El objeto pasa a ser dueño de p_blqDatos: SBlqMplDestruir lo destruye. */
SBloqueMultiPlataforma * SBlqMplEncapsular ( SBloque * p_blqDatos )
{
	SBloqueMultiPlataforma * p_blqObj;

	if ( ES_VALIDO ( p_blqDatos ) )
	{
		p_blqObj = (SBloqueMultiPlataforma *) MemReservar ( sizeof ( SBloqueMultiPlataforma ) );
		if ( ES_VALIDO ( p_blqObj ) )
		{
			p_blqObj->p_blqDatos = p_blqDatos;
		}
	}
	else
	{
		p_blqObj = NULL;
	}
	return ( p_blqObj );
}

SBloqueMultiPlataforma * SBlqMplCrearEntero ()
{
	return ( SBlqMplCrear ( MplTamInt () ) );
}

SBloqueMultiPlataforma * SBlqMplCrearEnteroLargo ()
{
	return ( SBlqMplCrear ( MplTamLong () ) );
}

SBloqueMultiPlataforma * SBlqMplCrearEnteroSinSigno ()
{
	return ( SBlqMplCrear ( MplTamUInt () ) );
}

SBloqueMultiPlataforma * SBlqMplCrearEnteroLargoSinSigno ()
{
	return ( SBlqMplCrear ( MplTamULong () ) );
}

SBloqueMultiPlataforma * SBlqMplCrearReal ()
{
	return ( SBlqMplCrear ( MplTamReal () ) );
}

SBloqueMultiPlataforma * SBlqMplCrearRealDoble ()
{
	return ( SBlqMplCrear ( MplTamRealDoble () ) );
}

/* Bloque justo de la medida de la cadena con su nulo, con ella escrita. */
SBloqueMultiPlataforma * SBlqMplCrearCadena ( const char * p_cValor )
{
	SBloqueMultiPlataforma * p_blqObj;

	if ( ES_VALIDO ( p_cValor ) )
	{
		p_blqObj = SBlqMplCrear ( CadLongitud ( p_cValor ) + 1 );
		if ( ES_VALIDO ( p_blqObj ) )
		{
			SBlqEscribirCadenaEnPos ( p_blqObj->p_blqDatos, 0, p_cValor );
		}
	}
	else
	{
		ERROR_ESTABLECER ( ERR_PARAMETROS );
		p_blqObj = NULL;
	}
	return ( p_blqObj );
}

void SBlqMplDestruir ( SBloqueMultiPlataforma ** p_p_blqObj )
{
	SBloqueMultiPlataforma * p_blqObj;

	if ( ES_VALIDO ( p_p_blqObj ) )
	{
		p_blqObj = *p_p_blqObj;

		if ( ES_VALIDO ( p_blqObj ) )
		{
			SBlqDestruir ( &p_blqObj->p_blqDatos );
			MemLiberar ( (void **) p_p_blqObj );
		}
	}
}


int SBlqMplEsValido ( SBloqueMultiPlataforma * p_blqObj )
{
	int iRes;

	if ( ES_VALIDO ( p_blqObj ) )
	{
		iRes = SBlqEsValido ( p_blqObj->p_blqDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SBlqMplTam ( SBloqueMultiPlataforma * p_blqObj )
{
	int iRes;

	if ( ES_VALIDO ( p_blqObj ) )
	{
		iRes = SBlqTam ( p_blqObj->p_blqDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

byte * SBlqMplDatos ( SBloqueMultiPlataforma * p_blqObj )
{
	byte *p_byRes;

	if ( ES_VALIDO ( p_blqObj ) )
	{
		p_byRes = SBlqDatos ( p_blqObj->p_blqDatos );
	}
	else
	{
		p_byRes = NULL;
	}
	return ( p_byRes );
}

byte * SBlqMplDuplicarDatos ( SBloqueMultiPlataforma * p_blqObj )
{
	byte *p_byRes;

	if ( ES_VALIDO ( p_blqObj ) )
	{
		p_byRes = SBlqDuplicarDatos ( p_blqObj->p_blqDatos );
	}
	else
	{
		p_byRes = NULL;
	}
	return ( p_byRes );
}

byte * SBlqMplDatosEnPos ( SBloqueMultiPlataforma * p_blqObj, int iPos )
{
	byte *p_byRes;

	if ( ES_VALIDO ( p_blqObj ) )
	{
		p_byRes = SBlqDatosEnPos ( p_blqObj->p_blqDatos, iPos );
	}
	else
	{
		p_byRes = NULL;
	}
	return ( p_byRes );
}

int SBlqMplEntero ( SBloqueMultiPlataforma * p_blqObj )
{
	int iRes;
	byte * p_byDatos;

	p_byDatos = _SBlqMplZonaTotal ( p_blqObj, MplTamInt () );
	if ( ES_VALIDO ( p_byDatos ) )
	{
		iRes = MplLeerInt ( p_byDatos );
	}
	else
	{
		ERROR_ESTABLECER ( ERR_LECTURA_MEMORIA );
		iRes = 0;
	}
	return ( iRes );
}

long SBlqMplEnteroLargo ( SBloqueMultiPlataforma * p_blqObj )
{
	long lRes;
	byte * p_byDatos;

	p_byDatos = _SBlqMplZonaTotal ( p_blqObj, MplTamLong () );
	if ( ES_VALIDO ( p_byDatos ) )
	{
		lRes = MplLeerLong ( p_byDatos );
	}
	else
	{
		ERROR_ESTABLECER ( ERR_LECTURA_MEMORIA );
		lRes = 0;
	}
	return ( lRes );
}

unsigned int SBlqMplEnteroSinSigno ( SBloqueMultiPlataforma * p_blqObj )
{
	unsigned int uiRes;
	byte * p_byDatos;

	p_byDatos = _SBlqMplZonaTotal ( p_blqObj, MplTamUInt () );
	if ( ES_VALIDO ( p_byDatos ) )
	{
		uiRes = MplLeerUInt ( p_byDatos );
	}
	else
	{
		ERROR_ESTABLECER ( ERR_LECTURA_MEMORIA );
		uiRes = 0;
	}
	return ( uiRes );
}

unsigned long SBlqMplEnteroLargoSinSigno ( SBloqueMultiPlataforma * p_blqObj )
{
	unsigned long ulRes;
	byte * p_byDatos;

	p_byDatos = _SBlqMplZonaTotal ( p_blqObj, MplTamULong () );
	if ( ES_VALIDO ( p_byDatos ) )
	{
		ulRes = MplLeerULong ( p_byDatos );
	}
	else
	{
		ERROR_ESTABLECER ( ERR_LECTURA_MEMORIA );
		ulRes = 0;
	}
	return ( ulRes );
}

float SBlqMplReal ( SBloqueMultiPlataforma * p_blqObj )
{
	float fRes;
	byte * p_byDatos;

	p_byDatos = _SBlqMplZonaTotal ( p_blqObj, MplTamReal () );
	if ( ES_VALIDO ( p_byDatos ) )
	{
		fRes = MplLeerReal ( p_byDatos );
	}
	else
	{
		ERROR_ESTABLECER ( ERR_LECTURA_MEMORIA );
		fRes = 0;
	}
	return ( fRes );
}

double SBlqMplRealDoble ( SBloqueMultiPlataforma * p_blqObj )
{
	double dRes;
	byte * p_byDatos;

	p_byDatos = _SBlqMplZonaTotal ( p_blqObj, MplTamRealDoble () );
	if ( ES_VALIDO ( p_byDatos ) )
	{
		dRes = MplLeerRealDoble ( p_byDatos );
	}
	else
	{
		ERROR_ESTABLECER ( ERR_LECTURA_MEMORIA );
		dRes = 0;
	}
	return ( dRes );
}

/* La cadena del principio del bloque, nueva y del llamante. */
char * SBlqMplCadena ( SBloqueMultiPlataforma * p_blqObj )
{
	return ( SBlqMplLeerCadenaEnPos ( p_blqObj, 0 ) );
}

int SBlqMplEsIgual ( SBloqueMultiPlataforma * p_blqObj1, SBloqueMultiPlataforma * p_blqObj2 )
{
	int iRes;

	if ( ES_VALIDO ( p_blqObj2 ) )
	{
		iRes = SBlqMplEsIgualBloque ( p_blqObj1, p_blqObj2->p_blqDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SBlqMplEsIgualBloque ( SBloqueMultiPlataforma * p_blqObj1, SBloque * p_blqObj2 )
{
	int iRes;

	if ( ES_VALIDO ( p_blqObj1 ) )
	{
		iRes = SBlqEsIgual ( p_blqObj1->p_blqDatos, p_blqObj2 );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SBlqMplEsIgualExt ( SBloqueMultiPlataforma * p_blqObj, byte * p_byDatos )
{
	int iRes;

	if ( ES_VALIDO ( p_blqObj ) )
	{
		iRes = SBlqEsIgualExt ( p_blqObj->p_blqDatos, p_byDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SBlqMplLiberacionMemoriaActivada ( SBloqueMultiPlataforma * p_blqObj )
{
	int iRes;

	if ( ES_VALIDO ( p_blqObj ) )
	{
		iRes = SBlqLiberacionMemoriaActivada ( p_blqObj->p_blqDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SBlqMplLimpiar ( SBloqueMultiPlataforma * p_blqObj )
{
	int iRes;

	if ( ES_VALIDO ( p_blqObj ) )
	{
		iRes = SBlqLimpiar ( p_blqObj->p_blqDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

byte SBlqMplLeerByte ( SBloqueMultiPlataforma * p_blqObj, int iPos )
{
	byte byRes;

	if ( ES_VALIDO ( p_blqObj ) )
	{
		byRes = SBlqLeerByte ( p_blqObj->p_blqDatos, iPos );
	}
	else
	{
		byRes = 0x00;
	}
	return ( byRes );
}

int SBlqMplEscribirByte ( SBloqueMultiPlataforma * p_blqObj, int iPos, byte byValor )
{
	int iRes;

	if ( ES_VALIDO ( p_blqObj ) )
	{
		iRes = SBlqEscribirByte ( p_blqObj->p_blqDatos, iPos, byValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SBlqMplEscribirEntero ( SBloqueMultiPlataforma * p_blqObj, int iValor )
{
	int iRes;
	byte * p_byDatos;

	p_byDatos = _SBlqMplZonaTotal ( p_blqObj, MplTamInt () );
	if ( ES_VALIDO ( p_byDatos ) )
	{
		MplEscribirInt ( p_byDatos, iValor );
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SBlqMplEscribirEnteroLargo ( SBloqueMultiPlataforma * p_blqObj, long lValor )
{
	int iRes;
	byte * p_byDatos;

	p_byDatos = _SBlqMplZonaTotal ( p_blqObj, MplTamLong () );
	if ( ES_VALIDO ( p_byDatos ) )
	{
		MplEscribirLong ( p_byDatos, lValor );
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SBlqMplEscribirReal ( SBloqueMultiPlataforma * p_blqObj, float fValor )
{
	int iRes;
	byte * p_byDatos;

	p_byDatos = _SBlqMplZonaTotal ( p_blqObj, MplTamReal () );
	if ( ES_VALIDO ( p_byDatos ) )
	{
		MplEscribirReal ( p_byDatos, fValor );
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SBlqMplEscribirEnteroSinSigno ( SBloqueMultiPlataforma * p_blqObj, unsigned int uiValor )
{
	int iRes;
	byte * p_byDatos;

	p_byDatos = _SBlqMplZonaTotal ( p_blqObj, MplTamUInt () );
	if ( ES_VALIDO ( p_byDatos ) )
	{
		MplEscribirUInt ( p_byDatos, uiValor );
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SBlqMplEscribirEnteroLargoSinSigno ( SBloqueMultiPlataforma * p_blqObj, unsigned long ulValor )
{
	int iRes;
	byte * p_byDatos;

	p_byDatos = _SBlqMplZonaTotal ( p_blqObj, MplTamULong () );
	if ( ES_VALIDO ( p_byDatos ) )
	{
		MplEscribirULong ( p_byDatos, ulValor );
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SBlqMplEscribirRealDoble ( SBloqueMultiPlataforma * p_blqObj, double dValor )
{
	int iRes;
	byte * p_byDatos;

	p_byDatos = _SBlqMplZonaTotal ( p_blqObj, MplTamRealDoble () );
	if ( ES_VALIDO ( p_byDatos ) )
	{
		MplEscribirRealDoble ( p_byDatos, dValor );
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

/* Escribe la cadena con su nulo al principio del bloque, si cabe entera. */
int SBlqMplEscribirCadena ( SBloqueMultiPlataforma * p_blqObj, const char * p_cValor )
{
	return ( SBlqMplEscribirCadenaEnPos ( p_blqObj, 0, p_cValor ) );
}

int SBlqMplLeerEnteroEnPos ( SBloqueMultiPlataforma * p_blqObj, int iPos )
{
	int iRes;
	byte * p_byDatos;

	p_byDatos = _SBlqMplZona ( p_blqObj, iPos, MplTamInt () );
	if ( ES_VALIDO ( p_byDatos ) )
	{
		iRes = MplLeerInt ( p_byDatos );
	}
	else
	{
		ERROR_ESTABLECER ( ERR_LECTURA_MEMORIA );
		iRes = 0;
	}
	return ( iRes );
}

long SBlqMplLeerEnteroLargoEnPos ( SBloqueMultiPlataforma * p_blqObj, int iPos )
{
	long lRes;
	byte * p_byDatos;

	p_byDatos = _SBlqMplZona ( p_blqObj, iPos, MplTamLong () );
	if ( ES_VALIDO ( p_byDatos ) )
	{
		lRes = MplLeerLong ( p_byDatos );
	}
	else
	{
		ERROR_ESTABLECER ( ERR_LECTURA_MEMORIA );
		lRes = 0;
	}
	return ( lRes );
}

float SBlqMplLeerRealEnPos ( SBloqueMultiPlataforma * p_blqObj, int iPos )
{
	float fRes;
	byte * p_byDatos;

	p_byDatos = _SBlqMplZona ( p_blqObj, iPos, MplTamReal () );
	if ( ES_VALIDO ( p_byDatos ) )
	{
		fRes = MplLeerReal ( p_byDatos );
	}
	else
	{
		ERROR_ESTABLECER ( ERR_LECTURA_MEMORIA );
		fRes = 0;
	}
	return ( fRes );
}

unsigned int SBlqMplLeerEnteroSinSignoEnPos ( SBloqueMultiPlataforma * p_blqObj, int iPos )
{
	unsigned int uiRes;
	byte * p_byDatos;

	p_byDatos = _SBlqMplZona ( p_blqObj, iPos, MplTamUInt () );
	if ( ES_VALIDO ( p_byDatos ) )
	{
		uiRes = MplLeerUInt ( p_byDatos );
	}
	else
	{
		ERROR_ESTABLECER ( ERR_LECTURA_MEMORIA );
		uiRes = 0;
	}
	return ( uiRes );
}

unsigned long SBlqMplLeerEnteroLargoSinSignoEnPos ( SBloqueMultiPlataforma * p_blqObj, int iPos )
{
	unsigned long ulRes;
	byte * p_byDatos;

	p_byDatos = _SBlqMplZona ( p_blqObj, iPos, MplTamULong () );
	if ( ES_VALIDO ( p_byDatos ) )
	{
		ulRes = MplLeerULong ( p_byDatos );
	}
	else
	{
		ERROR_ESTABLECER ( ERR_LECTURA_MEMORIA );
		ulRes = 0;
	}
	return ( ulRes );
}

double SBlqMplLeerRealDobleEnPos ( SBloqueMultiPlataforma * p_blqObj, int iPos )
{
	double dRes;
	byte * p_byDatos;

	p_byDatos = _SBlqMplZona ( p_blqObj, iPos, MplTamRealDoble () );
	if ( ES_VALIDO ( p_byDatos ) )
	{
		dRes = MplLeerRealDoble ( p_byDatos );
	}
	else
	{
		ERROR_ESTABLECER ( ERR_LECTURA_MEMORIA );
		dRes = 0;
	}
	return ( dRes );
}

char * SBlqMplLeerCadenaEnPos ( SBloqueMultiPlataforma * p_blqObj, int iPos )
{
	char *p_cRes;

	if ( ES_VALIDO ( p_blqObj ) )
	{
		p_cRes = SBlqLeerCadenaEnPos ( p_blqObj->p_blqDatos, iPos );
	}
	else
	{
		ERROR_ESTABLECER ( ERR_LECTURA_MEMORIA );
		p_cRes = NULL;
	}
	return ( p_cRes );
}

int SBlqMplEscribirEnteroEnPos ( SBloqueMultiPlataforma * p_blqObj, int iPos, int iValor )
{
	int iRes;
	byte * p_byDatos;

	p_byDatos = _SBlqMplZona ( p_blqObj, iPos, MplTamInt () );
	if ( ES_VALIDO ( p_byDatos ) )
	{
		MplEscribirInt ( p_byDatos, iValor );
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SBlqMplEscribirEnteroLargoEnPos ( SBloqueMultiPlataforma * p_blqObj, int iPos, long lValor )
{
	int iRes;
	byte * p_byDatos;

	p_byDatos = _SBlqMplZona ( p_blqObj, iPos, MplTamLong () );
	if ( ES_VALIDO ( p_byDatos ) )
	{
		MplEscribirLong ( p_byDatos, lValor );
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SBlqMplEscribirRealEnPos ( SBloqueMultiPlataforma * p_blqObj, int iPos, float fValor )
{
	int iRes;
	byte * p_byDatos;

	p_byDatos = _SBlqMplZona ( p_blqObj, iPos, MplTamReal () );
	if ( ES_VALIDO ( p_byDatos ) )
	{
		MplEscribirReal ( p_byDatos, fValor );
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SBlqMplEscribirEnteroSinSignoEnPos ( SBloqueMultiPlataforma * p_blqObj, int iPos, unsigned int uiValor )
{
	int iRes;
	byte * p_byDatos;

	p_byDatos = _SBlqMplZona ( p_blqObj, iPos, MplTamUInt () );
	if ( ES_VALIDO ( p_byDatos ) )
	{
		MplEscribirUInt ( p_byDatos, uiValor );
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SBlqMplEscribirEnteroLargoSinSignoEnPos ( SBloqueMultiPlataforma * p_blqObj, int iPos, unsigned long ulValor )
{
	int iRes;
	byte * p_byDatos;

	p_byDatos = _SBlqMplZona ( p_blqObj, iPos, MplTamULong () );
	if ( ES_VALIDO ( p_byDatos ) )
	{
		MplEscribirULong ( p_byDatos, ulValor );
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SBlqMplEscribirRealDobleEnPos ( SBloqueMultiPlataforma * p_blqObj, int iPos, double dValor )
{
	int iRes;
	byte * p_byDatos;

	p_byDatos = _SBlqMplZona ( p_blqObj, iPos, MplTamRealDoble () );
	if ( ES_VALIDO ( p_byDatos ) )
	{
		MplEscribirRealDoble ( p_byDatos, dValor );
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SBlqMplEscribirCadenaEnPos ( SBloqueMultiPlataforma * p_blqObj, int iPos, const char * p_cValor )
{
	int iRes;

	if ( ES_VALIDO ( p_blqObj ) )
	{
		iRes = SBlqEscribirCadenaEnPos ( p_blqObj->p_blqDatos, iPos, p_cValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SBlqMplLeerBuffer ( SBloqueMultiPlataforma * p_blqObj, int iPos, byte * p_byValor, int iTam )
{
	int iRes;

	if ( ES_VALIDO ( p_blqObj ) )
	{
		iRes = SBlqLeerBuffer ( p_blqObj->p_blqDatos, iPos, p_byValor, iTam );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SBlqMplEscribirBuffer ( SBloqueMultiPlataforma * p_blqObj, int iPos, byte * p_byValor, int iTam )
{
	int iRes;

	if ( ES_VALIDO ( p_blqObj ) )
	{
		iRes = SBlqEscribirBuffer ( p_blqObj->p_blqDatos, iPos, p_byValor, iTam );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

byte SBlqMplLeerByteExt ( SBloqueMultiPlataforma * p_blqObj, int * p_iPos )
{
	byte byRes;

	if ( ES_VALIDO ( p_blqObj ) )
	{
		byRes = SBlqLeerByteExt ( p_blqObj->p_blqDatos, p_iPos );
	}
	else
	{
		byRes = 0x00;
	}
	return ( byRes );
}

int SBlqMplEscribirByteExt ( SBloqueMultiPlataforma * p_blqObj, int * p_iPos, byte byValor )
{
	int iRes;

	if ( ES_VALIDO ( p_blqObj ) )
	{
		iRes = SBlqEscribirByteExt ( p_blqObj->p_blqDatos, p_iPos, byValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SBlqMplLeerEnteroEnPosExt ( SBloqueMultiPlataforma * p_blqObj, int * p_iPos )
{
	int iRes;
	byte * p_byDatos;

	p_byDatos = _SBlqMplZonaExt ( p_blqObj, p_iPos, MplTamInt () );
	if ( ES_VALIDO ( p_byDatos ) )
	{
		iRes = MplLeerInt ( p_byDatos );
	}
	else
	{
		ERROR_ESTABLECER ( ERR_LECTURA_MEMORIA );
		iRes = 0;
	}
	return ( iRes );
}

/* Si el valor no cabe en el long de esta máquina, falla como cualquier
   otra lectura: 0, ERR_CONVERSION_IMPOSIBLE y la posición sin mover. */
long SBlqMplLeerEnteroLargoEnPosExt ( SBloqueMultiPlataforma * p_blqObj, int * p_iPos )
{
	long lRes;
	byte * p_byDatos;

	p_byDatos = _SBlqMplZonaEnPuntero ( p_blqObj, p_iPos, MplTamLong () );
	if ( ES_VALIDO ( p_byDatos ) )
	{
		lRes = MplLeerLong ( p_byDatos );
		if ( MplCabeLong ( p_byDatos ) == 1 )
		{
			*p_iPos = *p_iPos + MplTamLong ();
		}
	}
	else
	{
		ERROR_ESTABLECER ( ERR_LECTURA_MEMORIA );
		lRes = 0;
	}
	return ( lRes );
}

float SBlqMplLeerRealEnPosExt ( SBloqueMultiPlataforma * p_blqObj, int * p_iPos )
{
	float fRes;
	byte * p_byDatos;

	p_byDatos = _SBlqMplZonaExt ( p_blqObj, p_iPos, MplTamReal () );
	if ( ES_VALIDO ( p_byDatos ) )
	{
		fRes = MplLeerReal ( p_byDatos );
	}
	else
	{
		ERROR_ESTABLECER ( ERR_LECTURA_MEMORIA );
		fRes = 0;
	}
	return ( fRes );
}

unsigned int SBlqMplLeerEnteroSinSignoEnPosExt ( SBloqueMultiPlataforma * p_blqObj, int * p_iPos )
{
	unsigned int uiRes;
	byte * p_byDatos;

	p_byDatos = _SBlqMplZonaExt ( p_blqObj, p_iPos, MplTamUInt () );
	if ( ES_VALIDO ( p_byDatos ) )
	{
		uiRes = MplLeerUInt ( p_byDatos );
	}
	else
	{
		ERROR_ESTABLECER ( ERR_LECTURA_MEMORIA );
		uiRes = 0;
	}
	return ( uiRes );
}

/* Si el valor no cabe en el unsigned long de esta máquina, falla como cualquier
   otra lectura: 0, ERR_CONVERSION_IMPOSIBLE y la posición sin mover. */
unsigned long SBlqMplLeerEnteroLargoSinSignoEnPosExt ( SBloqueMultiPlataforma * p_blqObj, int * p_iPos )
{
	unsigned long ulRes;
	byte * p_byDatos;

	p_byDatos = _SBlqMplZonaEnPuntero ( p_blqObj, p_iPos, MplTamULong () );
	if ( ES_VALIDO ( p_byDatos ) )
	{
		ulRes = MplLeerULong ( p_byDatos );
		if ( MplCabeULong ( p_byDatos ) == 1 )
		{
			*p_iPos = *p_iPos + MplTamULong ();
		}
	}
	else
	{
		ERROR_ESTABLECER ( ERR_LECTURA_MEMORIA );
		ulRes = 0;
	}
	return ( ulRes );
}

double SBlqMplLeerRealDobleEnPosExt ( SBloqueMultiPlataforma * p_blqObj, int * p_iPos )
{
	double dRes;
	byte * p_byDatos;

	p_byDatos = _SBlqMplZonaExt ( p_blqObj, p_iPos, MplTamRealDoble () );
	if ( ES_VALIDO ( p_byDatos ) )
	{
		dRes = MplLeerRealDoble ( p_byDatos );
	}
	else
	{
		ERROR_ESTABLECER ( ERR_LECTURA_MEMORIA );
		dRes = 0;
	}
	return ( dRes );
}

char * SBlqMplLeerCadenaEnPosExt ( SBloqueMultiPlataforma * p_blqObj, int * p_iPos )
{
	char *p_cRes;

	if ( ES_VALIDO ( p_blqObj ) )
	{
		p_cRes = SBlqLeerCadenaEnPosExt ( p_blqObj->p_blqDatos, p_iPos );
	}
	else
	{
		ERROR_ESTABLECER ( ERR_LECTURA_MEMORIA );
		p_cRes = NULL;
	}
	return ( p_cRes );
}

int SBlqMplEscribirEnteroEnPosExt ( SBloqueMultiPlataforma * p_blqObj, int * p_iPos, int iValor )
{
	int iRes;
	byte * p_byDatos;

	p_byDatos = _SBlqMplZonaExt ( p_blqObj, p_iPos, MplTamInt () );
	if ( ES_VALIDO ( p_byDatos ) )
	{
		MplEscribirInt ( p_byDatos, iValor );
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SBlqMplEscribirEnteroLargoEnPosExt ( SBloqueMultiPlataforma * p_blqObj, int * p_iPos, long lValor )
{
	int iRes;
	byte * p_byDatos;

	p_byDatos = _SBlqMplZonaExt ( p_blqObj, p_iPos, MplTamLong () );
	if ( ES_VALIDO ( p_byDatos ) )
	{
		MplEscribirLong ( p_byDatos, lValor );
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SBlqMplEscribirRealEnPosExt ( SBloqueMultiPlataforma * p_blqObj, int * p_iPos, float fValor )
{
	int iRes;
	byte * p_byDatos;

	p_byDatos = _SBlqMplZonaExt ( p_blqObj, p_iPos, MplTamReal () );
	if ( ES_VALIDO ( p_byDatos ) )
	{
		MplEscribirReal ( p_byDatos, fValor );
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SBlqMplEscribirEnteroSinSignoEnPosExt ( SBloqueMultiPlataforma * p_blqObj, int * p_iPos, unsigned int uiValor )
{
	int iRes;
	byte * p_byDatos;

	p_byDatos = _SBlqMplZonaExt ( p_blqObj, p_iPos, MplTamUInt () );
	if ( ES_VALIDO ( p_byDatos ) )
	{
		MplEscribirUInt ( p_byDatos, uiValor );
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SBlqMplEscribirEnteroLargoSinSignoEnPosExt ( SBloqueMultiPlataforma * p_blqObj, int * p_iPos, unsigned long ulValor )
{
	int iRes;
	byte * p_byDatos;

	p_byDatos = _SBlqMplZonaExt ( p_blqObj, p_iPos, MplTamULong () );
	if ( ES_VALIDO ( p_byDatos ) )
	{
		MplEscribirULong ( p_byDatos, ulValor );
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SBlqMplEscribirRealDobleEnPosExt ( SBloqueMultiPlataforma * p_blqObj, int * p_iPos, double dValor )
{
	int iRes;
	byte * p_byDatos;

	p_byDatos = _SBlqMplZonaExt ( p_blqObj, p_iPos, MplTamRealDoble () );
	if ( ES_VALIDO ( p_byDatos ) )
	{
		MplEscribirRealDoble ( p_byDatos, dValor );
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SBlqMplEscribirCadenaEnPosExt ( SBloqueMultiPlataforma * p_blqObj, int * p_iPos, const char * p_cValor )
{
	int iRes;

	if ( ES_VALIDO ( p_blqObj ) )
	{
		iRes = SBlqEscribirCadenaEnPosExt ( p_blqObj->p_blqDatos, p_iPos, p_cValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SBlqMplLeerBufferExt ( SBloqueMultiPlataforma * p_blqObj, int * p_iPos, byte * p_byValor, int iTam )
{
	int iRes;

	if ( ES_VALIDO ( p_blqObj ) )
	{
		iRes = SBlqLeerBufferExt ( p_blqObj->p_blqDatos, p_iPos, p_byValor, iTam );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SBlqMplEscribirBufferExt ( SBloqueMultiPlataforma * p_blqObj, int * p_iPos, byte * p_byValor, int iTam )
{
	int iRes;

	if ( ES_VALIDO ( p_blqObj ) )
	{
		iRes = SBlqEscribirBufferExt ( p_blqObj->p_blqDatos, p_iPos, p_byValor, iTam );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SBlqMplCopiarDe ( SBloqueMultiPlataforma * p_blqObj, byte * p_byValor )
{
	int iRes;

	if ( ES_VALIDO ( p_blqObj ) )
	{
		iRes = SBlqCopiarDe ( p_blqObj->p_blqDatos, p_byValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SBlqMplCopiarEn ( SBloqueMultiPlataforma * p_blqObj, byte * p_byValor )
{
	int iRes;

	if ( ES_VALIDO ( p_blqObj ) )
	{
		iRes = SBlqCopiarEn ( p_blqObj->p_blqDatos, p_byValor );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SBlqMplCopiar ( SBloqueMultiPlataforma * p_blqDest, SBloqueMultiPlataforma * p_blqOrig )
{
	int iRes;

	if ( ES_VALIDO ( p_blqOrig ) )
	{
		iRes = SBlqMplCopiarBloque ( p_blqDest, p_blqOrig->p_blqDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SBlqMplCopiarBloque ( SBloqueMultiPlataforma * p_blqDest, SBloque * p_blqOrig )
{
	int iRes;

	if ( ES_VALIDO ( p_blqDest ) )
	{
		iRes = SBlqCopiar ( p_blqDest->p_blqDatos, p_blqOrig );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

SBloqueMultiPlataforma * SBlqMplDuplicar ( SBloqueMultiPlataforma * p_blqObj )
{
	SBloqueMultiPlataforma * p_blqDup;

	if ( ES_VALIDO ( p_blqObj ) )
	{
		p_blqDup = _SBlqMplEnvolverNuevo ( SBlqDuplicar ( p_blqObj->p_blqDatos ) );
	}
	else
	{
		p_blqDup = NULL;
	}
	return ( p_blqDup );
}

int SBlqMplEsCompatible ( SBloqueMultiPlataforma * p_blqObj, SBloqueMultiPlataforma * p_blqComp )
{
	int iRes;

	if ( ES_VALIDO ( p_blqComp ) )
	{
		iRes = SBlqMplEsCompatibleBloque ( p_blqObj, p_blqComp->p_blqDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SBlqMplEsCompatibleBloque ( SBloqueMultiPlataforma * p_blqObj, SBloque * p_blqComp )
{
	int iRes;

	if ( ES_VALIDO ( p_blqObj ) )
	{
		iRes = SBlqEsCompatible ( p_blqObj->p_blqDatos, p_blqComp );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SBlqMplTamCompatible ( SBloqueMultiPlataforma * p_blqObj, int iTam )
{
	int iRes;

	if ( ES_VALIDO ( p_blqObj ) )
	{
		iRes = SBlqTamCompatible ( p_blqObj->p_blqDatos, iTam );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SBlqMplVolcar ( SBloqueMultiPlataforma * p_blqObj, int iPos, SBloqueMultiPlataforma * p_blqDatos )
{
	int iRes;

	if ( ES_VALIDO ( p_blqDatos ) )
	{
		iRes = SBlqMplVolcarBloque ( p_blqObj, iPos, p_blqDatos->p_blqDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SBlqMplVolcarBloque ( SBloqueMultiPlataforma * p_blqObj, int iPos, SBloque * p_blqDatos )
{
	int iRes;

	if ( ES_VALIDO ( p_blqObj ) )
	{
		iRes = SBlqVolcar ( p_blqObj->p_blqDatos, iPos, p_blqDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

SBloqueMultiPlataforma * SBlqMplExtraer ( SBloqueMultiPlataforma * p_blqObj, int iPos, int iTam )
{
	SBloqueMultiPlataforma * p_blqDatos;

	if ( ES_VALIDO ( p_blqObj ) )
	{
		p_blqDatos = _SBlqMplEnvolverNuevo ( SBlqExtraer ( p_blqObj->p_blqDatos, iPos, iTam ) );
	}
	else
	{
		p_blqDatos = NULL;
	}
	return ( p_blqDatos );
}

int SBlqMplVolcarExt ( SBloqueMultiPlataforma * p_blqObj, int * p_iPos, SBloqueMultiPlataforma * p_blqDatos )
{
	int iRes;

	if ( ES_VALIDO ( p_blqDatos ) )
	{
		iRes = SBlqMplVolcarBloqueExt ( p_blqObj, p_iPos, p_blqDatos->p_blqDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SBlqMplVolcarBloqueExt ( SBloqueMultiPlataforma * p_blqObj, int * p_iPos, SBloque * p_blqDatos )
{
	int iRes;

	if ( ES_VALIDO ( p_blqObj ) )
	{
		iRes = SBlqVolcarExt ( p_blqObj->p_blqDatos, p_iPos, p_blqDatos );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

SBloqueMultiPlataforma * SBlqMplExtraerExt ( SBloqueMultiPlataforma * p_blqObj, int * p_iPos, int iTam )
{
	SBloqueMultiPlataforma * p_blqDatos;

	if ( ES_VALIDO ( p_iPos ) )
	{
		p_blqDatos = SBlqMplExtraer ( p_blqObj, *p_iPos, iTam );
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

unsigned int SBlqMplHash ( SBloqueMultiPlataforma * p_blqObj )
{
	unsigned int uiRes;

	if ( ES_VALIDO ( p_blqObj ) )
	{
		uiRes = SBlqHash ( p_blqObj->p_blqDatos );
	}
	else
	{
		uiRes = 0;
	}
	return ( uiRes );
}

/* El bloque envuelto, que sigue siendo del objeto. */
SBloque * SBlqMplBloque ( SBloqueMultiPlataforma * p_blqObj )
{
	SBloque * p_blqRes;

	if ( ES_VALIDO ( p_blqObj ) )
	{
		p_blqRes = p_blqObj->p_blqDatos;
	}
	else
	{
		p_blqRes = NULL;
	}
	return ( p_blqRes );
}
