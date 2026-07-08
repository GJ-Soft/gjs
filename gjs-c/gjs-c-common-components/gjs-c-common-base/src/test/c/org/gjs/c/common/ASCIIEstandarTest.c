#include "Base.h"

#include "ASCIIEstandar.h"
#include "ASCIICodigos.h"



static int TestASCIICodigo01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test ASCIICodigo 01:\n" );
	if ( ASCIICodigo ( 'A' ) != 65 )
	{
		printf( "Error caso 1: se esperaba 65: %d\n", ASCIICodigo ( 'A' ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ASCIICodigo ( '0' ) != 48 )
	{
		printf( "Error caso 2: se esperaba 48: %d\n", ASCIICodigo ( '0' ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ASCIICaracter ( 65 ) != 'A' )
	{
		printf( "Error caso 3: se esperaba 'A': %c\n", ASCIICaracter ( 65 ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ASCIICaracter ( 48 ) != '0' )
	{
		printf( "Error caso 4: se esperaba '0': %c\n", ASCIICaracter ( 48 ) );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestASCIIEsControl01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test ASCIIEsControl 01:\n" );
	if ( ASCIIEsCodigoControl ( (char) ASCII_NUL ) != 1 )
	{
		printf( "Error caso 1: NUL deberia ser codigo de control\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ASCIIEsCodigoControl ( (char) ASCII_DEL ) != 1 )
	{
		printf( "Error caso 2: DEL deberia ser codigo de control\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ASCIIEsCodigoControl ( 'A' ) != 0 )
	{
		printf( "Error caso 3: 'A' no deberia ser codigo de control\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* TAB es un control imprimible. */
	if ( ASCIIEsCodigoControlImprimible ( (char) ASCII_TAB ) != 1 )
	{
		printf( "Error caso 4: TAB deberia ser control imprimible\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ASCIIEsCodigoControlImprimible ( 'A' ) != 0 )
	{
		printf( "Error caso 5: 'A' no deberia ser control imprimible\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* NUL es control no imprimible; TAB es control imprimible. */
	if ( ASCIIEsCodigoNoImprimible ( (char) ASCII_NUL ) != 1 )
	{
		printf( "Error caso 6: NUL deberia ser no imprimible\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ASCIIEsCodigoNoImprimible ( (char) ASCII_TAB ) != 0 )
	{
		printf( "Error caso 7: TAB no deberia contar como no imprimible\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestASCIIEsCodigos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test ASCIIEsCodigos 01:\n" );

	if ( ASCIIEsNUL ( (char) ASCII_NUL ) != 1 ) { printf( "Error NUL\n" ); iRes = BOOL_VAL_FALSO; }
	if ( ASCIIEsSOH ( (char) ASCII_SOH ) != 1 ) { printf( "Error SOH\n" ); iRes = BOOL_VAL_FALSO; }
	if ( ASCIIEsSTX ( (char) ASCII_STX ) != 1 ) { printf( "Error STX\n" ); iRes = BOOL_VAL_FALSO; }
	if ( ASCIIEsETX ( (char) ASCII_ETX ) != 1 ) { printf( "Error ETX\n" ); iRes = BOOL_VAL_FALSO; }
	if ( ASCIIEsEOT ( (char) ASCII_EOT ) != 1 ) { printf( "Error EOT\n" ); iRes = BOOL_VAL_FALSO; }
	if ( ASCIIEsENQ ( (char) ASCII_ENQ ) != 1 ) { printf( "Error ENQ\n" ); iRes = BOOL_VAL_FALSO; }
	if ( ASCIIEsACK ( (char) ASCII_ACK ) != 1 ) { printf( "Error ACK\n" ); iRes = BOOL_VAL_FALSO; }
	if ( ASCIIEsBEL ( (char) ASCII_BEL ) != 1 ) { printf( "Error BEL\n" ); iRes = BOOL_VAL_FALSO; }
	if ( ASCIIEsBS  ( (char) ASCII_BS  ) != 1 ) { printf( "Error BS\n"  ); iRes = BOOL_VAL_FALSO; }
	if ( ASCIIEsTAB ( (char) ASCII_TAB ) != 1 ) { printf( "Error TAB\n" ); iRes = BOOL_VAL_FALSO; }
	if ( ASCIIEsLF  ( (char) ASCII_LF  ) != 1 ) { printf( "Error LF\n"  ); iRes = BOOL_VAL_FALSO; }
	if ( ASCIIEsVT  ( (char) ASCII_VT  ) != 1 ) { printf( "Error VT\n"  ); iRes = BOOL_VAL_FALSO; }
	if ( ASCIIEsFF  ( (char) ASCII_FF  ) != 1 ) { printf( "Error FF\n"  ); iRes = BOOL_VAL_FALSO; }
	if ( ASCIIEsCR  ( (char) ASCII_CR  ) != 1 ) { printf( "Error CR\n"  ); iRes = BOOL_VAL_FALSO; }
	if ( ASCIIEsSO  ( (char) ASCII_SO  ) != 1 ) { printf( "Error SO\n"  ); iRes = BOOL_VAL_FALSO; }
	if ( ASCIIEsST  ( (char) ASCII_ST  ) != 1 ) { printf( "Error ST\n"  ); iRes = BOOL_VAL_FALSO; }
	if ( ASCIIEsSLE ( (char) ASCII_SLE ) != 1 ) { printf( "Error SLE\n" ); iRes = BOOL_VAL_FALSO; }
	if ( ASCIIEsDC1 ( (char) ASCII_DC1 ) != 1 ) { printf( "Error DC1\n" ); iRes = BOOL_VAL_FALSO; }
	if ( ASCIIEsDC2 ( (char) ASCII_DC2 ) != 1 ) { printf( "Error DC2\n" ); iRes = BOOL_VAL_FALSO; }
	if ( ASCIIEsDC3 ( (char) ASCII_DC3 ) != 1 ) { printf( "Error DC3\n" ); iRes = BOOL_VAL_FALSO; }
	if ( ASCIIEsDC4 ( (char) ASCII_DC4 ) != 1 ) { printf( "Error DC4\n" ); iRes = BOOL_VAL_FALSO; }
	if ( ASCIIEsNAK ( (char) ASCII_NAK ) != 1 ) { printf( "Error NAK\n" ); iRes = BOOL_VAL_FALSO; }
	if ( ASCIIEsSYN ( (char) ASCII_SYN ) != 1 ) { printf( "Error SYN\n" ); iRes = BOOL_VAL_FALSO; }
	if ( ASCIIEsETB ( (char) ASCII_ETB ) != 1 ) { printf( "Error ETB\n" ); iRes = BOOL_VAL_FALSO; }
	if ( ASCIIEsCAN ( (char) ASCII_CAN ) != 1 ) { printf( "Error CAN\n" ); iRes = BOOL_VAL_FALSO; }
	if ( ASCIIEsEM  ( (char) ASCII_EM  ) != 1 ) { printf( "Error EM\n"  ); iRes = BOOL_VAL_FALSO; }
	if ( ASCIIEsSTB ( (char) ASCII_STB ) != 1 ) { printf( "Error STB\n" ); iRes = BOOL_VAL_FALSO; }
	if ( ASCIIEsESC ( (char) ASCII_ESC ) != 1 ) { printf( "Error ESC\n" ); iRes = BOOL_VAL_FALSO; }
	if ( ASCIIEsFS  ( (char) ASCII_FS  ) != 1 ) { printf( "Error FS\n"  ); iRes = BOOL_VAL_FALSO; }
	if ( ASCIIEsGS  ( (char) ASCII_GS  ) != 1 ) { printf( "Error GS\n"  ); iRes = BOOL_VAL_FALSO; }
	if ( ASCIIEsRS  ( (char) ASCII_RS  ) != 1 ) { printf( "Error RS\n"  ); iRes = BOOL_VAL_FALSO; }
	if ( ASCIIEsUS  ( (char) ASCII_US  ) != 1 ) { printf( "Error US\n"  ); iRes = BOOL_VAL_FALSO; }
	if ( ASCIIEsDEL ( (char) ASCII_DEL ) != 1 ) { printf( "Error DEL\n" ); iRes = BOOL_VAL_FALSO; }

	/* Un caracter normal no debe coincidir con ningun codigo de control. */
	if ( ASCIIEsNUL ( 'A' ) != 0 ) { printf( "Error caso normal NUL\n" ); iRes = BOOL_VAL_FALSO; }
	if ( ASCIIEsESC ( 'A' ) != 0 ) { printf( "Error caso normal ESC\n" ); iRes = BOOL_VAL_FALSO; }

	return ( iRes );
}



int TestASCIIEstandar ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test ASCIIEstandar]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestASCIICodigo01 () == BOOL_VAL_CIERTO ) &&
			( TestASCIIEsControl01 () == BOOL_VAL_CIERTO ) &&
			( TestASCIIEsCodigos01 () == BOOL_VAL_CIERTO ) )
	{
		printf ( "%sResultado: OK%s\n", ANSI_VERDE, ANSI_RESETEAR );
	}
	else
	{
		printf ( "%sResultado: KO%s\n", ANSI_ROJO, ANSI_RESETEAR );
		iRes = BOOL_VAL_FALSO;
	}
	printf ( "%s[Fin]%s\n", ANSI_AMARILLO, ANSI_RESETEAR );
	return ( iRes );
}
