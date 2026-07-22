#include "Base.h"

#include "SPropiedades.h"
#include "UtilidadesFicheros.h"
#include "SFicTexto.h"
#include "SistemaFicheros.h"
#include "TestConfig.h"



/* Ficheros de propiedades de entrada (solo lectura). */
#define FIC_TEST_PROP_PRUEBA		FIC_TEST_DIR_DATA "/prueba.properties"
#define FIC_TEST_PROP_VACIO			FIC_TEST_DIR_DATA "/vacio.properties"

/* Fichero de propiedades generado por los tests (salida). */
#define FIC_TEST_PROP_SALIDA		FIC_TEST_DIR_RESULTS "/salida.properties"



static int TestSPropCicloVida01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SPropCicloVida 01:\n" );
	SPropiedades * p_propObj = SPropCrearDef ();
	if ( ES_NULO ( p_propObj ) )
	{
		printf( "Error caso 0: no se pudo crear el objeto de propiedades\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SPropNumPropiedades ( p_propObj ) != 0 )
		{
			printf( "Error caso 1: un objeto recien creado no debe tener propiedades\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SPropExistePropiedad ( p_propObj, "clave1" ) != 0 )
		{
			printf( "Error caso 2: no debe existir una propiedad no insertada\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SPropEstPropiedad ( p_propObj, "clave1", "valor1" ) != 1 )
		{
			printf( "Error caso 3: no se pudo establecer la propiedad\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SPropNumPropiedades ( p_propObj ) != 1 )
		{
			printf( "Error caso 4: se esperaba 1 propiedad: %d\n", SPropNumPropiedades ( p_propObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SPropExistePropiedad ( p_propObj, "clave1" ) != 1 )
		{
			printf( "Error caso 5: la propiedad insertada deberia existir\n" );
			iRes = BOOL_VAL_FALSO;
		}
		const char * p_cValor = SPropObtPropiedad ( p_propObj, "clave1" );
		if ( ES_NULO ( p_cValor ) || ( strcmp ( p_cValor, "valor1" ) != 0 ) )
		{
			printf( "Error caso 6: se esperaba \"valor1\": [%s]\n", ES_VALIDO ( p_cValor ) ? p_cValor : "(nulo)" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Valor por defecto para clave inexistente. */
		const char * p_cDef = SPropObtPropiedadExt ( p_propObj, "inexistente", "porDefecto" );
		if ( ES_NULO ( p_cDef ) || ( strcmp ( p_cDef, "porDefecto" ) != 0 ) )
		{
			printf( "Error caso 7: se esperaba el valor por defecto\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Actualizar una propiedad existente no crea una nueva. */
		if ( SPropEstPropiedad ( p_propObj, "clave1", "nuevoValor" ) != 1 )
		{
			printf( "Error caso 8: no se pudo actualizar la propiedad\n" );
			iRes = BOOL_VAL_FALSO;
		}
		p_cValor = SPropObtPropiedad ( p_propObj, "clave1" );
		if ( ES_NULO ( p_cValor ) || ( strcmp ( p_cValor, "nuevoValor" ) != 0 ) )
		{
			printf( "Error caso 9: se esperaba \"nuevoValor\"\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SPropNumPropiedades ( p_propObj ) != 1 )
		{
			printf( "Error caso 10: actualizar no debe aumentar el numero de propiedades\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Segunda propiedad y eliminacion. */
		SPropEstPropiedad ( p_propObj, "clave2", "valor2" );
		if ( SPropNumPropiedades ( p_propObj ) != 2 )
		{
			printf( "Error caso 11: se esperaban 2 propiedades\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SPropEliminarPropiedad ( p_propObj, "clave1" );
		if ( SPropExistePropiedad ( p_propObj, "clave1" ) != 0 )
		{
			printf( "Error caso 12: la propiedad eliminada no deberia existir\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SPropNumPropiedades ( p_propObj ) != 1 )
		{
			printf( "Error caso 13: se esperaba 1 propiedad tras eliminar\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	SPropDestruir ( &p_propObj );
	return ( iRes );
}

static int TestSPropCargar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SPropCargar 01:\n" );
	SPropiedades * p_propObj = SPropCrearDef ();
	if ( ES_NULO ( p_propObj ) )
	{
		printf( "Error caso 0: no se pudo crear el objeto de propiedades\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		char * p_cBase = SisDirectorioActual ();
		char * p_cFicTest = SisComponerRuta ( p_cBase, FIC_TEST_PROP_PRUEBA, 0 );
		if ( SPropCargar ( p_propObj, p_cFicTest ) != 1 )
		{
			printf( "Error caso 1: no se pudo cargar el fichero de propiedades\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* El fichero tiene 3 propiedades (la linea de comentario se ignora). */
		if ( SPropNumPropiedades ( p_propObj ) != 3 )
		{
			printf( "Error caso 2: se esperaban 3 propiedades: %d\n", SPropNumPropiedades ( p_propObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		const char * p_cNombre = SPropObtPropiedad ( p_propObj, "nombre" );
		if ( ES_NULO ( p_cNombre ) || ( strcmp ( p_cNombre, "aplicacion" ) != 0 ) )
		{
			printf( "Error caso 3: se esperaba nombre \"aplicacion\": [%s]\n", ES_VALIDO ( p_cNombre ) ? p_cNombre : "(nulo)" );
			iRes = BOOL_VAL_FALSO;
		}
		const char * p_cVersion = SPropObtPropiedad ( p_propObj, "version" );
		if ( ES_NULO ( p_cVersion ) || ( strcmp ( p_cVersion, "3.2.1" ) != 0 ) )
		{
			printf( "Error caso 4: se esperaba version \"3.2.1\": [%s]\n", ES_VALIDO ( p_cVersion ) ? p_cVersion : "(nulo)" );
			iRes = BOOL_VAL_FALSO;
		}
		const char * p_cAutor = SPropObtPropiedad ( p_propObj, "autor" );
		if ( ES_NULO ( p_cAutor ) || ( strcmp ( p_cAutor, "gjs" ) != 0 ) )
		{
			printf( "Error caso 5: se esperaba autor \"gjs\": [%s]\n", ES_VALIDO ( p_cAutor ) ? p_cAutor : "(nulo)" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SPropExistePropiedad ( p_propObj, "inexistente" ) != 0 )
		{
			printf( "Error caso 6: no debe existir una propiedad no presente en el fichero\n" );
			iRes = BOOL_VAL_FALSO;
		}
		MemLiberar ( (void **) &p_cBase );
		MemLiberar ( (void **) &p_cFicTest );
	}
	SPropDestruir ( &p_propObj );
	return ( iRes );
}

static int TestSPropCargarVacio01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SPropCargarVacio 01:\n" );
	SPropiedades * p_propObj = SPropCrearDef ();
	if ( ES_NULO ( p_propObj ) )
	{
		printf( "Error caso 0: no se pudo crear el objeto de propiedades\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		char * p_cBase = SisDirectorioActual ();
		char * p_cFicTest = SisComponerRuta ( p_cBase, FIC_TEST_PROP_VACIO, 0 );
		/* Un fichero vacio se carga correctamente pero no aporta propiedades. */
		if ( SPropCargar ( p_propObj, p_cFicTest ) != 1 )
		{
			printf( "Error caso 1: no se pudo cargar el fichero de propiedades vacio\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SPropNumPropiedades ( p_propObj ) != 0 )
		{
			printf( "Error caso 2: un fichero vacio no debe aportar propiedades: %d\n", SPropNumPropiedades ( p_propObj ) );
			iRes = BOOL_VAL_FALSO;
		}
		MemLiberar ( (void **) &p_cBase );
		MemLiberar ( (void **) &p_cFicTest );
	}
	SPropDestruir ( &p_propObj );
	return ( iRes );
}

static int TestSPropGuardar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SPropGuardar 01:\n" );
	SisCrearDirectorio ( FIC_TEST_DIR_RESULTS );

	SPropiedades * p_propObj = SPropCrearDef ();
	if ( ES_NULO ( p_propObj ) )
	{
		printf( "Error caso 0: no se pudo crear el objeto de propiedades\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		char * p_cBase = SisDirectorioActual ();
		char * p_cFicTest = SisComponerRuta ( p_cBase, FIC_TEST_PROP_PRUEBA, 0 );
		char * p_cFicSalida = SisComponerRuta ( p_cBase, FIC_TEST_PROP_SALIDA, 0 );
		/* Se parte del fichero de ejemplo y se modifica: se actualiza "version"
		   y se anade "descripcion". */
		if ( SPropCargar ( p_propObj, p_cFicTest ) != 1 )
		{
			printf( "Error caso 1: no se pudo cargar el fichero de partida\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SPropEstPropiedad ( p_propObj, "version", "4.0.0" ) != 1 )
		{
			printf( "Error caso 2: no se pudo actualizar la propiedad version\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SPropEstPropiedad ( p_propObj, "descripcion", "appDePrueba" ) != 1 )
		{
			printf( "Error caso 3: no se pudo anadir la propiedad descripcion\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SPropGuardar ( p_propObj, p_cFicSalida ) != 1 )
		{
			printf( "Error caso 4: no se pudo guardar el fichero de propiedades\n" );
			iRes = BOOL_VAL_FALSO;
		}

		/* Las propiedades se guardan ordenadas por clave (case-insensitive):
		   autor, descripcion, nombre, version. */
		const char * p_p_cEsperadas [] = { "autor=gjs",
										   "descripcion=appDePrueba",
										   "nombre=aplicacion",
										   "version=4.0.0" };
		if ( FicTxtContenidoCoincide ( p_cFicSalida, p_p_cEsperadas, 4 ) != BOOL_VAL_CIERTO )
		{
			printf( "Error caso 5: el contenido del fichero guardado no coincide con lo esperado\n" );
			iRes = BOOL_VAL_FALSO;
		}
		MemLiberar ( (void **) &p_cBase );
		MemLiberar ( (void **) &p_cFicTest );
		MemLiberar ( (void **) &p_cFicSalida );
	}
	SPropDestruir ( &p_propObj );

	/* Recarga del fichero guardado para comprobar la ida y vuelta. */
	SPropiedades * p_propRecarga = SPropCrearDef ();
	if ( ES_VALIDO ( p_propRecarga ) )
	{
		SPropCargar ( p_propRecarga, FIC_TEST_PROP_SALIDA );
		if ( SPropNumPropiedades ( p_propRecarga ) != 4 )
		{
			printf( "Error caso 6: se esperaban 4 propiedades tras recargar: %d\n", SPropNumPropiedades ( p_propRecarga ) );
			iRes = BOOL_VAL_FALSO;
		}
		const char * p_cVersion = SPropObtPropiedad ( p_propRecarga, "version" );
		if ( ES_NULO ( p_cVersion ) || ( strcmp ( p_cVersion, "4.0.0" ) != 0 ) )
		{
			printf( "Error caso 7: se esperaba version \"4.0.0\" tras recargar\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	SPropDestruir ( &p_propRecarga );
	return ( iRes );
}

static int TestSPropNulo01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SPropNulo 01:\n" );
	if ( ES_VALIDO ( SPropObtPropiedad ( NULL, "clave" ) ) )
	{
		printf( "Error caso 1: se esperaba nulo al obtener de un objeto nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SPropNumPropiedades ( NULL ) != 0 )
	{
		printf( "Error caso 2: se esperaba 0 propiedades en un objeto nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SPropEstPropiedad ( NULL, "clave", "valor" ) != 0 )
	{
		printf( "Error caso 3: se esperaba 0 al establecer en un objeto nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SPropExistePropiedad ( NULL, "clave" ) != 0 )
	{
		printf( "Error caso 4: se esperaba 0 al comprobar en un objeto nulo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}



int TestSPropiedades ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SPropiedades]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSPropCicloVida01 () == BOOL_VAL_CIERTO ) &&
			( TestSPropCargar01 () == BOOL_VAL_CIERTO ) &&
			( TestSPropCargarVacio01 () == BOOL_VAL_CIERTO ) &&
			( TestSPropGuardar01 () == BOOL_VAL_CIERTO ) &&
			( TestSPropNulo01 () == BOOL_VAL_CIERTO ) )
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
