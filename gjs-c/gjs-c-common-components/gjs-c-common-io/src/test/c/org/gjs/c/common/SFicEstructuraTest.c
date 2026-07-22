#include "Base.h"

#include "SFicEstructura.h"
#include "SistemaFicheros.h"
#include "TestConfig.h"



static int TestSFicEstGuardarCargar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SFicEstGuardarCargar 01:\n" );
	byte p_byDatos[ 8 ] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08 };
	/* SFicEstCrear exige una ruta valida del sistema: se usa una ruta absoluta
	   (bajo el directorio de trabajo) porque en Windows debe llevar unidad. */
	char * p_cBase = SisDirectorioActual ();
	char * p_cDir = SisComponerRuta ( p_cBase, FIC_TEST_DIR_RESULTS, 0 );
	if ( ES_VALIDO ( p_cBase ) && ES_VALIDO ( p_cDir ) )
	{
		SisCrearDirectorio ( FIC_TEST_DIR_RESULTS );

		SFicEstructura * p_ficObj = SFicEstCrearExt ( p_cDir, "sfest_test.bin", 8 );
		if ( ES_VALIDO ( p_ficObj ) )
		{
			if ( SFicEstEsValido ( p_ficObj ) != 1 )
			{
				printf( "Error caso 1: se esperaba valido\n" );
				iRes = BOOL_VAL_FALSO;
			}
			/* Escribir el contenido en el buffer y guardarlo. */
			SBloque * p_blqCont = SFicEstContenido ( p_ficObj );
			if ( ES_NULO ( p_blqCont ) || ( SBlqTam ( p_blqCont ) != 8 ) )
			{
				printf( "Error caso 2: contenido invalido o tam inesperado\n" );
				iRes = BOOL_VAL_FALSO;
			}
			else
			{
				SBlqEscribirBuffer ( p_blqCont, 0, p_byDatos, 8 );
			}
			if ( SFicEstGuardarCambios ( p_ficObj ) != 1 )
			{
				printf( "Error caso 3: no se pudieron guardar los cambios\n" );
				iRes = BOOL_VAL_FALSO;
			}
			SFicEstDestruir ( &p_ficObj );
		}
		else
		{
			printf( "Error caso 0: no se pudo crear el objeto\n" );
			iRes = BOOL_VAL_FALSO;
		}

		/* Reabrir y verificar que el contenido se persistio. */
		int iTamElem = 0;
		SFicEstructura * p_ficRe = SFicEstAbrirExt ( p_cDir, "sfest_test.bin", &iTamElem );
		if ( ES_VALIDO ( p_ficRe ) )
		{
			if ( iTamElem != 8 )
			{
				printf( "Error caso 4: se esperaba tam de elemento 8: %d\n", iTamElem );
				iRes = BOOL_VAL_FALSO;
			}
			SBloque * p_blqRe = SFicEstContenido ( p_ficRe );
			if ( ES_NULO ( p_blqRe ) )
			{
				printf( "Error caso 5: contenido nulo tras reabrir\n" );
				iRes = BOOL_VAL_FALSO;
			}
			else
			{
				for ( int iByte = 0; iByte < 8; iByte = iByte + 1 )
				{
					if ( SBlqLeerByte ( p_blqRe, iByte ) != p_byDatos[ iByte ] )
					{
						printf( "Error caso 6: byte %d se esperaba 0x%02X: 0x%02X\n", iByte, (int) p_byDatos[ iByte ], (int) SBlqLeerByte ( p_blqRe, iByte ) );
						iRes = BOOL_VAL_FALSO;
					}
				}
			}
			SFicEstEliminar ( &p_ficRe );
		}
		else
		{
			printf( "Error caso 4: no se pudo reabrir el fichero\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo obtener el directorio de trabajo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	MemLiberar ( (void **) &p_cBase );
	MemLiberar ( (void **) &p_cDir );
	return ( iRes );
}

static int TestSFicEstNulo01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SFicEstNulo 01:\n" );
	if ( SFicEstEsValido ( NULL ) != 0 )
	{
		printf( "Error caso 1: se esperaba no valido con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( SFicEstContenido ( NULL ) ) )
	{
		printf( "Error caso 2: se esperaba contenido nulo con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SFicEstGuardarCambios ( NULL ) != 0 )
	{
		printf( "Error caso 3: se esperaba fallo al guardar con nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

static int TestSFicEstAbrirVacio01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SFicEstAbrirVacio 01:\n" );
	/* Abrir un fichero vacio (sin numero magico ni estructura) no debe dar un
	   objeto valido. */
	SFicEstructura * p_ficObj = SFicEstAbrir ( FIC_TEST_FIC_VACIO );
	if ( SFicEstEsValido ( p_ficObj ) != 0 )
	{
		printf( "Error caso 1: no se esperaba objeto valido desde un fichero vacio\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* Recurso de entrada compartido: solo destruir, nunca eliminar. */
	SFicEstDestruir ( &p_ficObj );
	return ( iRes );
}

int TestSFicEstructura ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SFicEstructura]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSFicEstGuardarCargar01 () == BOOL_VAL_CIERTO ) &&
			( TestSFicEstAbrirVacio01 () == BOOL_VAL_CIERTO ) &&
			( TestSFicEstNulo01 () == BOOL_VAL_CIERTO ) )
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
