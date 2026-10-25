#include "Base.h"

#include "SConjuntoEntidadesCod.h"



#define TAM_CODIGO		10

static SEntidadCod * CrearEntidad ( const char * p_cCodigo )
{
	return ( SEntCodCrearLit ( p_cCodigo, TAM_CODIGO ) );
}

static int CodigoEs ( SEntidadCod * p_entcObj, const char * p_cCodigo )
{
	return ( SEntCodEsIgualLit ( p_entcObj, p_cCodigo ) == 1 );
}

/* Inserta BETA, GAMMA y ALFA en desorden: el conjunto queda ALFA, BETA, GAMMA. */
static void LlenarConjunto ( SConjuntoEntidadesCod * p_cnjObj )
{
	SCnjEntCodInsertar ( p_cnjObj, CrearEntidad ( "BETA" ) );
	SCnjEntCodInsertar ( p_cnjObj, CrearEntidad ( "GAMMA" ) );
	SCnjEntCodInsertar ( p_cnjObj, CrearEntidad ( "ALFA" ) );
}



static int TestSCnjEntCodCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCnjEntCodCrear 01:\n" );
# if ( defined ( MODO_DEPURACION ) )
	unsigned long ulBloquesAntes = MemNumBloquesActuales ();
# endif

	SConjuntoEntidadesCod * p_cnjObj = SCnjEntCodCrear ();
	if ( ES_NULO ( p_cnjObj ) )
	{
		printf( "Error caso 1: no se esperaba nulo al crear\n" );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		if ( SCnjEntCodEsValido ( p_cnjObj ) != 1 )
		{
			printf( "Error caso 2: el conjunto recien creado deberia ser valido\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SCnjEntCodEstaVacio ( p_cnjObj ) != 1 ) || ( SCnjEntCodNumElementos ( p_cnjObj ) != 0 ) )
		{
			printf( "Error caso 3: el conjunto recien creado deberia estar vacio\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( SCnjEntCodPrimero ( p_cnjObj ) ) || ES_VALIDO ( SCnjEntCodUltimo ( p_cnjObj ) ) )
		{
			printf( "Error caso 4: un conjunto vacio no tiene primero ni ultimo\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	SCnjEntCodDestruir ( &p_cnjObj );
	if ( ES_VALIDO ( p_cnjObj ) )
	{
		printf( "Error caso 5: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
# if ( defined ( MODO_DEPURACION ) )
	if ( MemNumBloquesActuales () != ulBloquesAntes )
	{
		printf( "Error caso 6: quedan %ld bloques sin liberar\n", (long) ( MemNumBloquesActuales () - ulBloquesAntes ) );
		iRes = BOOL_VAL_FALSO;
	}
# endif
	return ( iRes );
}

static int TestSCnjEntCodInsertar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCnjEntCodInsertar 01:\n" );
# if ( defined ( MODO_DEPURACION ) )
	unsigned long ulBloquesAntes = MemNumBloquesActuales ();
# endif

	SConjuntoEntidadesCod * p_cnjObj = SCnjEntCodCrear ();
	if ( ES_VALIDO ( p_cnjObj ) )
	{
		/* El conjunto guarda el puntero, sin copiar, y ordena por codigo. */
		SEntidadCod * p_entcBeta = CrearEntidad ( "BETA" );
		if ( ( SCnjEntCodInsertar ( p_cnjObj, p_entcBeta ) != 1 ) ||
			 ( SCnjEntCodInsertar ( p_cnjObj, CrearEntidad ( "GAMMA" ) ) != 1 ) ||
			 ( SCnjEntCodInsertar ( p_cnjObj, CrearEntidad ( "ALFA" ) ) != 1 ) )
		{
			printf( "Error caso 1: se esperaba poder insertar las tres entidades\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SCnjEntCodNumElementos ( p_cnjObj ) != 3 ) ||
			 ( ! CodigoEs ( SCnjEntCodElemento ( p_cnjObj, 0 ), "ALFA" ) ) ||
			 ( ! CodigoEs ( SCnjEntCodElemento ( p_cnjObj, 1 ), "BETA" ) ) ||
			 ( ! CodigoEs ( SCnjEntCodElemento ( p_cnjObj, 2 ), "GAMMA" ) ) )
		{
			printf( "Error caso 2: las entidades deberian quedar ordenadas por codigo ( ALFA, BETA, GAMMA )\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCnjEntCodElemento ( p_cnjObj, 1 ) != p_entcBeta )
		{
			printf( "Error caso 3: el conjunto deberia guardar la misma entidad, no una copia\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Un codigo ya presente se rechaza, y la entidad sigue siendo del llamador. */
		SEntidadCod * p_entcDup = CrearEntidad ( "BETA" );
		if ( SCnjEntCodInsertar ( p_cnjObj, p_entcDup ) != -1 )
		{
			printf( "Error caso 4: insertar un codigo duplicado deberia devolver -1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SCnjEntCodNumElementos ( p_cnjObj ) != 3 ) || ( ! CodigoEs ( p_entcDup, "BETA" ) ) )
		{
			printf( "Error caso 5: el duplicado no deberia entrar ni tocarse\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SEntCodDestruir ( &p_entcDup );
		if ( SCnjEntCodInsertar ( p_cnjObj, NULL ) != -1 )
		{
			printf( "Error caso 6: insertar una entidad nula deberia devolver -1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( ! CodigoEs ( SCnjEntCodPrimero ( p_cnjObj ), "ALFA" ) ) || ( ! CodigoEs ( SCnjEntCodUltimo ( p_cnjObj ), "GAMMA" ) ) )
		{
			printf( "Error caso 7: el primero deberia ser ALFA y el ultimo GAMMA\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el conjunto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* Destruir el conjunto destruye sus entidades. */
	SCnjEntCodDestruir ( &p_cnjObj );
# if ( defined ( MODO_DEPURACION ) )
	if ( MemNumBloquesActuales () != ulBloquesAntes )
	{
		printf( "Error caso 8: quedan %ld bloques sin liberar\n", (long) ( MemNumBloquesActuales () - ulBloquesAntes ) );
		iRes = BOOL_VAL_FALSO;
	}
# endif
	return ( iRes );
}

static int TestSCnjEntCodBuscar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCnjEntCodBuscar 01:\n" );
# if ( defined ( MODO_DEPURACION ) )
	unsigned long ulBloquesAntes = MemNumBloquesActuales ();
# endif

	SConjuntoEntidadesCod * p_cnjObj = SCnjEntCodCrear ();
	SEntidadCod * p_entcBuscar = CrearEntidad ( "BETA" );
	SCodigo * p_codBuscar = SCodCrearValorLit ( "GAMMA" );
	SCadena * p_cadBuscar = SCadGenerar ( "ALFA" );
	if ( ES_VALIDO ( p_cnjObj ) && ES_VALIDO ( p_entcBuscar ) && ES_VALIDO ( p_codBuscar ) && ES_VALIDO ( p_cadBuscar ) )
	{
		LlenarConjunto ( p_cnjObj );

		/* Por codigo: lo buscado no es ninguna de las entidades del conjunto. */
		if ( ( SCnjEntCodExiste ( p_cnjObj, p_entcBuscar ) != 1 ) || ( SCnjEntCodBuscar ( p_cnjObj, p_entcBuscar ) != 1 ) ||
			 ( SCnjEntCodPosicion ( p_cnjObj, p_entcBuscar ) != 1 ) )
		{
			printf( "Error caso 1: la entidad BETA deberia estar en la posicion 1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SCnjEntCodExisteCodigo ( p_cnjObj, p_codBuscar ) != 1 ) || ( SCnjEntCodBuscarCodigo ( p_cnjObj, p_codBuscar ) != 2 ) )
		{
			printf( "Error caso 2: el codigo GAMMA deberia estar en la posicion 2\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SCnjEntCodExisteValorCodigo ( p_cnjObj, p_cadBuscar ) != 1 ) ||
			 ( SCnjEntCodBuscarValorCodigo ( p_cnjObj, p_cadBuscar ) != 0 ) )
		{
			printf( "Error caso 3: la cadena ALFA deberia estar en la posicion 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Por literal: se busca con una entidad de sonda de tope exacto. */
		if ( ( SCnjEntCodExisteValorCodigoLit ( p_cnjObj, "GAMMA" ) != 1 ) ||
			 ( SCnjEntCodBuscarValorCodigoLit ( p_cnjObj, "GAMMA" ) != 2 ) )
		{
			printf( "Error caso 4: el literal GAMMA deberia estar en la posicion 2\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Lo que no esta: menor, intermedio, mayor y un prefijo. */
		const char * p_cAusentes [ 4 ] = { "AAA", "BAAA", "ZETA", "ALF" };
		int iAus = 0;
		while ( iAus < 4 )
		{
			SEntidadCod * p_entcAus = CrearEntidad ( p_cAusentes [ iAus ] );
			SCodigo * p_codAus = SCodCrearValorLit ( p_cAusentes [ iAus ] );
			SCadena * p_cadAus = SCadGenerar ( p_cAusentes [ iAus ] );
			if ( ES_NULO ( p_entcAus ) || ES_NULO ( p_codAus ) || ES_NULO ( p_cadAus ) )
			{
				printf( "Error caso 5: no se pudieron crear las sondas de \"%s\"\n", p_cAusentes [ iAus ] );
				iRes = BOOL_VAL_FALSO;
			}
			else if ( ( SCnjEntCodExiste ( p_cnjObj, p_entcAus ) != 0 ) || ( SCnjEntCodBuscar ( p_cnjObj, p_entcAus ) != -1 ) ||
					  ( SCnjEntCodPosicion ( p_cnjObj, p_entcAus ) != -1 ) ||
					  ( SCnjEntCodExisteCodigo ( p_cnjObj, p_codAus ) != 0 ) || ( SCnjEntCodBuscarCodigo ( p_cnjObj, p_codAus ) != -1 ) ||
					  ( SCnjEntCodExisteValorCodigo ( p_cnjObj, p_cadAus ) != 0 ) ||
					  ( SCnjEntCodBuscarValorCodigo ( p_cnjObj, p_cadAus ) != -1 ) ||
					  ( SCnjEntCodExisteValorCodigoLit ( p_cnjObj, p_cAusentes [ iAus ] ) != 0 ) ||
					  ( SCnjEntCodBuscarValorCodigoLit ( p_cnjObj, p_cAusentes [ iAus ] ) != -1 ) )
			{
				printf( "Error caso 5: \"%s\" no deberia encontrarse\n", p_cAusentes [ iAus ] );
				iRes = BOOL_VAL_FALSO;
			}
			SEntCodDestruir ( &p_entcAus );
			SCodDestruir ( &p_codAus );
			SCadDestruir ( &p_cadAus );
			iAus = iAus + 1;
		}
		/* Literales que no son codigos validos: la sonda no se crea y no se encuentra nada. */
		const char * p_cNoValidos [ 3 ] = { "", "1ABC", "AB-C" };
		int iNoVal = 0;
		while ( iNoVal < 3 )
		{
			if ( ( SCnjEntCodExisteValorCodigoLit ( p_cnjObj, p_cNoValidos [ iNoVal ] ) != 0 ) ||
				 ( SCnjEntCodBuscarValorCodigoLit ( p_cnjObj, p_cNoValidos [ iNoVal ] ) != -1 ) )
			{
				printf( "Error caso 6: \"%s\" no deberia encontrarse\n", p_cNoValidos [ iNoVal ] );
				iRes = BOOL_VAL_FALSO;
			}
			iNoVal = iNoVal + 1;
		}
		/* Nulos: "no esta" es -1, no 0, que seria la primera posicion. */
		if ( ( SCnjEntCodExiste ( p_cnjObj, NULL ) != 0 ) || ( SCnjEntCodBuscar ( p_cnjObj, NULL ) != -1 ) ||
			 ( SCnjEntCodPosicion ( p_cnjObj, NULL ) != -1 ) ||
			 ( SCnjEntCodExisteCodigo ( p_cnjObj, NULL ) != 0 ) || ( SCnjEntCodBuscarCodigo ( p_cnjObj, NULL ) != -1 ) ||
			 ( SCnjEntCodExisteValorCodigo ( p_cnjObj, NULL ) != 0 ) || ( SCnjEntCodBuscarValorCodigo ( p_cnjObj, NULL ) != -1 ) ||
			 ( SCnjEntCodExisteValorCodigoLit ( p_cnjObj, NULL ) != 0 ) || ( SCnjEntCodBuscarValorCodigoLit ( p_cnjObj, NULL ) != -1 ) )
		{
			printf( "Error caso 7: con un dato nulo no deberia encontrarse nada\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SCnjEntCodBuscar ( NULL, p_entcBuscar ) != -1 ) || ( SCnjEntCodBuscarValorCodigoLit ( NULL, "ALFA" ) != -1 ) ||
			 ( SCnjEntCodPosicion ( NULL, p_entcBuscar ) != -1 ) )
		{
			printf( "Error caso 8: en un conjunto nulo buscar deberia devolver -1\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudieron crear el conjunto o los datos de busqueda\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SCnjEntCodDestruir ( &p_cnjObj );
	SEntCodDestruir ( &p_entcBuscar );
	SCodDestruir ( &p_codBuscar );
	SCadDestruir ( &p_cadBuscar );
# if ( defined ( MODO_DEPURACION ) )
	/* Las entidades de sonda de las busquedas por valor se destruyen dentro. */
	if ( MemNumBloquesActuales () != ulBloquesAntes )
	{
		printf( "Error caso 9: quedan %ld bloques sin liberar\n", (long) ( MemNumBloquesActuales () - ulBloquesAntes ) );
		iRes = BOOL_VAL_FALSO;
	}
# endif
	return ( iRes );
}

static int TestSCnjEntCodEliminar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCnjEntCodEliminar 01:\n" );
# if ( defined ( MODO_DEPURACION ) )
	unsigned long ulBloquesAntes = MemNumBloquesActuales ();
# endif

	SConjuntoEntidadesCod * p_cnjObj = SCnjEntCodCrear ();
	if ( ES_VALIDO ( p_cnjObj ) )
	{
		LlenarConjunto ( p_cnjObj );

		/* Eliminar destruye la entidad. */
		if ( SCnjEntCodEliminar ( p_cnjObj, 1 ) != 1 )
		{
			printf( "Error caso 1: se esperaba resultado 1 al eliminar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SCnjEntCodNumElementos ( p_cnjObj ) != 2 ) || ( SCnjEntCodExisteValorCodigoLit ( p_cnjObj, "BETA" ) != 0 ) )
		{
			printf( "Error caso 2: tras eliminar BETA ya no deberia estar\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SCnjEntCodEliminar ( p_cnjObj, -1 ) != 0 ) || ( SCnjEntCodEliminar ( p_cnjObj, 2 ) != 0 ) )
		{
			printf( "Error caso 3: eliminar fuera de rango deberia devolver 0\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* El codigo eliminado puede volver a entrar. */
		if ( SCnjEntCodInsertar ( p_cnjObj, CrearEntidad ( "BETA" ) ) != 1 )
		{
			printf( "Error caso 4: se esperaba poder reinsertar BETA\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SCnjEntCodVaciar ( p_cnjObj ) != 1 ) || ( SCnjEntCodEstaVacio ( p_cnjObj ) != 1 ) )
		{
			printf( "Error caso 5: tras vaciar el conjunto deberia estar vacio\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Tras vaciar sigue siendo utilizable. */
		LlenarConjunto ( p_cnjObj );
		if ( SCnjEntCodNumElementos ( p_cnjObj ) != 3 )
		{
			printf( "Error caso 6: tras vaciar deberia poder llenarse de nuevo\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el conjunto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SCnjEntCodDestruir ( &p_cnjObj );
# if ( defined ( MODO_DEPURACION ) )
	if ( MemNumBloquesActuales () != ulBloquesAntes )
	{
		printf( "Error caso 7: quedan %ld bloques sin liberar\n", (long) ( MemNumBloquesActuales () - ulBloquesAntes ) );
		iRes = BOOL_VAL_FALSO;
	}
# endif
	return ( iRes );
}

static int TestSCnjEntCodExtraer01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCnjEntCodExtraer 01:\n" );
# if ( defined ( MODO_DEPURACION ) )
	unsigned long ulBloquesAntes = MemNumBloquesActuales ();
# endif

	SConjuntoEntidadesCod * p_cnjObj = SCnjEntCodCrear ();
	if ( ES_VALIDO ( p_cnjObj ) )
	{
		if ( ES_VALIDO ( SCnjEntCodExtraer ( p_cnjObj, 0 ) ) )
		{
			printf( "Error caso 1: extraer de un conjunto vacio deberia devolver nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		LlenarConjunto ( p_cnjObj );

		/* Sale la misma entidad, viva; desde ahora es del llamador. */
		SEntidadCod * p_entcEsp = SCnjEntCodElemento ( p_cnjObj, 1 );
		SEntidadCod * p_entcExt = SCnjEntCodExtraer ( p_cnjObj, 1 );
		if ( ES_NULO ( p_entcExt ) || ( p_entcExt != p_entcEsp ) || ( ! CodigoEs ( p_entcExt, "BETA" ) ) )
		{
			printf( "Error caso 2: se esperaba extraer BETA de la posicion 1\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ( SCnjEntCodNumElementos ( p_cnjObj ) != 2 ) || ( SCnjEntCodExiste ( p_cnjObj, p_entcExt ) != 0 ) )
		{
			printf( "Error caso 3: tras extraer BETA ya no deberia estar en el conjunto\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( ES_VALIDO ( SCnjEntCodExtraer ( p_cnjObj, -1 ) ) || ES_VALIDO ( SCnjEntCodExtraer ( p_cnjObj, 2 ) ) )
		{
			printf( "Error caso 4: extraer fuera de rango deberia devolver nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
		if ( SCnjEntCodNumElementos ( p_cnjObj ) != 2 )
		{
			printf( "Error caso 5: extraer fuera de rango no deberia cambiar el conjunto\n" );
			iRes = BOOL_VAL_FALSO;
		}
		/* Se puede devolver al conjunto, que la toma otra vez y la coloca en su sitio. */
		if ( ES_VALIDO ( p_entcExt ) )
		{
			if ( SCnjEntCodInsertar ( p_cnjObj, p_entcExt ) != 1 )
			{
				printf( "Error caso 6: la entidad extraida deberia poder volver a insertarse\n" );
				iRes = BOOL_VAL_FALSO;
				SEntCodDestruir ( &p_entcExt );
			}
			else if ( SCnjEntCodElemento ( p_cnjObj, 1 ) != p_entcExt )
			{
				printf( "Error caso 7: al reinsertarla deberia volver a la posicion 1\n" );
				iRes = BOOL_VAL_FALSO;
			}
		}
		/* Una extraida que no se devuelve la destruye el llamador. */
		p_entcExt = SCnjEntCodExtraer ( p_cnjObj, 0 );
		if ( ! CodigoEs ( p_entcExt, "ALFA" ) )
		{
			printf( "Error caso 8: extraer la posicion 0 deberia dar ALFA\n" );
			iRes = BOOL_VAL_FALSO;
		}
		SEntCodDestruir ( &p_entcExt );
		if ( ES_VALIDO ( SCnjEntCodExtraer ( NULL, 0 ) ) )
		{
			printf( "Error caso 9: extraer de un conjunto nulo deberia devolver nulo\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el conjunto\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SCnjEntCodDestruir ( &p_cnjObj );
# if ( defined ( MODO_DEPURACION ) )
	if ( MemNumBloquesActuales () != ulBloquesAntes )
	{
		printf( "Error caso 10: quedan %ld bloques sin liberar\n", (long) ( MemNumBloquesActuales () - ulBloquesAntes ) );
		iRes = BOOL_VAL_FALSO;
	}
# endif
	return ( iRes );
}

static int TestSCnjEntCodInvalidos01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SCnjEntCodInvalidos 01:\n" );

	if ( ( SCnjEntCodEsValido ( NULL ) != 0 ) || ( SCnjEntCodNumElementos ( NULL ) != 0 ) || ( SCnjEntCodEstaVacio ( NULL ) != 1 ) )
	{
		printf( "Error caso 1: un conjunto nulo no es valido, tiene 0 elementos y esta vacio\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( SCnjEntCodElemento ( NULL, 0 ) ) || ES_VALIDO ( SCnjEntCodPrimero ( NULL ) ) || ES_VALIDO ( SCnjEntCodUltimo ( NULL ) ) )
	{
		printf( "Error caso 2: un conjunto nulo no tiene elementos\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SEntidadCod * p_entcObj = CrearEntidad ( "ALFA" );
	if ( SCnjEntCodInsertar ( NULL, p_entcObj ) != -1 )
	{
		printf( "Error caso 3: insertar en un conjunto nulo deberia devolver -1\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SEntCodDestruir ( &p_entcObj );
	if ( ( SCnjEntCodEliminar ( NULL, 0 ) != 0 ) || ( SCnjEntCodVaciar ( NULL ) != 0 ) )
	{
		printf( "Error caso 4: eliminar o vaciar un conjunto nulo deberia devolver 0\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SConjuntoEntidadesCod * p_cnjNulo = NULL;
	SCnjEntCodDestruir ( &p_cnjNulo );
	SCnjEntCodDestruir ( NULL );
	return ( iRes );
}



int TestSConjuntoEntidadesCod ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SConjuntoEntidadesCod]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSCnjEntCodCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSCnjEntCodInsertar01 () == BOOL_VAL_CIERTO ) &&
			( TestSCnjEntCodBuscar01 () == BOOL_VAL_CIERTO ) &&
			( TestSCnjEntCodEliminar01 () == BOOL_VAL_CIERTO ) &&
			( TestSCnjEntCodExtraer01 () == BOOL_VAL_CIERTO ) &&
			( TestSCnjEntCodInvalidos01 () == BOOL_VAL_CIERTO ) )
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
