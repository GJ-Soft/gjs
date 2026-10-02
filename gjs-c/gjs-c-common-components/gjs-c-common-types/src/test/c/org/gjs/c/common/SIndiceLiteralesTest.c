#include "Base.h"

#include "SIndiceLiterales.h"



/* Primer valor que un long con signo ya no puede representar: LONG_MAX + 1. */
#define ULONG_MITAD		( (unsigned long) LONG_MAX + 1UL )



static int TestSIndLitCrear01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SIndLitCrear 01:\n" );
	SIndiceLiterales * p_indlObj = SIndLitCrear ();
	if ( ES_VALIDO ( p_indlObj ) )
	{
		if ( ( SIndLitEsValido ( p_indlObj ) != 1 ) || ( SIndLitEstaVacio ( p_indlObj ) != 1 ) ||
			 ( SIndLitNumElementos ( p_indlObj ) != 0 ) )
		{
			printf( "Error caso 1: recien creado deberia ser valido y estar vacio\n" );
			iRes = BOOL_VAL_FALSO;
		}
	}
	else
	{
		printf( "Error caso 0: no se pudo crear el indice\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SIndLitDestruir ( &p_indlObj );
	if ( ES_VALIDO ( p_indlObj ) )
	{
		printf( "Error caso 2: se esperaba puntero nulo tras destruir\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}

/* Insercion y orden: el indice mantiene las claves ordenadas, y no admite
   repetidas ni localizadores sin clave o sin posicion. */
static int TestSIndLitInsertar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SIndLitInsertar 01:\n" );
	SIndiceLiterales * p_indlObj = SIndLitCrear ();

	if ( ( SIndLitInsertarExt ( p_indlObj, "pera", 30UL ) != 1 ) ||
		 ( SIndLitInsertarExt ( p_indlObj, "manzana", 10UL ) != 1 ) ||
		 ( SIndLitInsertarExt ( p_indlObj, "uva", 50UL ) != 1 ) )
	{
		printf( "Error caso 1: no se pudieron insertar las tres claves\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* Insertar recibe el localizador y se queda con el. */
	if ( SIndLitInsertar ( p_indlObj, SLczCrearExt ( "kiwi", ULONG_MITAD ) ) != 1 )
	{
		printf( "Error caso 2: no se pudo insertar el localizador \"kiwi\"\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SIndLitNumElementos ( p_indlObj ) != 4 )
	{
		printf( "Error caso 3: se esperaban 4 elementos: %d\n", SIndLitNumElementos ( p_indlObj ) );
		iRes = BOOL_VAL_FALSO;
	}
	/* Orden por clave: kiwi, manzana, pera, uva. */
	if ( ( CadComparar ( SIndLitElementoClave ( p_indlObj, 0 ), "kiwi" ) != COMP_IGUAL ) ||
		 ( CadComparar ( SIndLitElementoClave ( p_indlObj, 1 ), "manzana" ) != COMP_IGUAL ) ||
		 ( CadComparar ( SIndLitElementoClave ( p_indlObj, 2 ), "pera" ) != COMP_IGUAL ) ||
		 ( CadComparar ( SIndLitElementoClave ( p_indlObj, 3 ), "uva" ) != COMP_IGUAL ) )
	{
		printf( "Error caso 4: se esperaba el orden kiwi, manzana, pera, uva\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ( SIndLitElementoPosicion ( p_indlObj, 0 ) != ULONG_MITAD ) ||
		 ( SIndLitElementoPosicion ( p_indlObj, 2 ) != 30UL ) )
	{
		printf( "Error caso 5: posiciones por indice mal: %lu y %lu\n",
				SIndLitElementoPosicion ( p_indlObj, 0 ), SIndLitElementoPosicion ( p_indlObj, 2 ) );
		iRes = BOOL_VAL_FALSO;
	}
	/* Repetida: se rechaza y la que habia no cambia. */
	if ( SIndLitInsertarExt ( p_indlObj, "pera", 99UL ) != -1 )
	{
		printf( "Error caso 6: una clave repetida deberia rechazarse\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ( SIndLitNumElementos ( p_indlObj ) != 4 ) || ( SIndLitPosicion ( p_indlObj, "pera" ) != 30UL ) )
	{
		printf( "Error caso 7: tras rechazar la repetida deberia seguir \"pera\" en 30: %lu\n", SIndLitPosicion ( p_indlObj, "pera" ) );
		iRes = BOOL_VAL_FALSO;
	}
	/* Sin clave o sin posicion, no entra. */
	if ( ( SIndLitInsertarExt ( p_indlObj, NULL, 5UL ) != -1 ) ||
		 ( SIndLitInsertarExt ( p_indlObj, "fresa", SLCZ_SIN_POSICION ) != -1 ) )
	{
		printf( "Error caso 8: sin clave o sin posicion no deberia insertarse\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* Si Insertar rechaza el localizador, sigue siendo del llamante. */
	SLocalizador * p_lczRepetido = SLczCrearExt ( "uva", 1UL );
	if ( SIndLitInsertar ( p_indlObj, p_lczRepetido ) != -1 )
	{
		printf( "Error caso 9: el localizador repetido deberia rechazarse\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SLczDestruir ( &p_lczRepetido );
	if ( SIndLitNumElementos ( p_indlObj ) != 4 )
	{
		printf( "Error caso 10: se esperaban 4 elementos: %d\n", SIndLitNumElementos ( p_indlObj ) );
		iRes = BOOL_VAL_FALSO;
	}
	SIndLitDestruir ( &p_indlObj );
	return ( iRes );
}

/* Busqueda por clave. Existe y Buscar pasaban la cadena al conjunto, cuyo
   comparador la trata como un SLocalizador: no encontraban nada, o leian
   memoria que no era suya. */
static int TestSIndLitBuscar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SIndLitBuscar 01:\n" );
	SIndiceLiterales * p_indlObj = SIndLitCrear ();
	SIndLitInsertarExt ( p_indlObj, "pera", 30UL );
	SIndLitInsertarExt ( p_indlObj, "manzana", 10UL );
	SIndLitInsertarExt ( p_indlObj, "uva", ULONG_MAX - 1UL );

	if ( ( SIndLitExiste ( p_indlObj, "pera" ) != 1 ) || ( SIndLitExiste ( p_indlObj, "fresa" ) != 0 ) )
	{
		printf( "Error caso 1: deberia existir \"pera\" y no \"fresa\"\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ( SIndLitBuscar ( p_indlObj, "manzana" ) != 0 ) ||
		 ( SIndLitBuscar ( p_indlObj, "uva" ) != 2 ) ||
		 ( SIndLitBuscar ( p_indlObj, "fresa" ) != -1 ) )
	{
		printf( "Error caso 2: se esperaba manzana 0, uva 2 y fresa -1: %d %d %d\n",
				SIndLitBuscar ( p_indlObj, "manzana" ), SIndLitBuscar ( p_indlObj, "uva" ), SIndLitBuscar ( p_indlObj, "fresa" ) );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ( SIndLitPosicion ( p_indlObj, "uva" ) != ULONG_MAX - 1UL ) ||
		 ( SIndLitPosicion ( p_indlObj, "fresa" ) != SLCZ_SIN_POSICION ) )
	{
		printf( "Error caso 3: se esperaba uva en ULONG_MAX - 1 y fresa sin posicion: %lu\n", SIndLitPosicion ( p_indlObj, "uva" ) );
		iRes = BOOL_VAL_FALSO;
	}
	/* El indice distingue mayusculas. */
	if ( SIndLitExiste ( p_indlObj, "PERA" ) != 0 )
	{
		printf( "Error caso 4: \"PERA\" no deberia encontrarse\n" );
		iRes = BOOL_VAL_FALSO;
	}
	/* Una clave que no es valida no se encuentra, sin fallar. */
	if ( ( SIndLitExiste ( p_indlObj, NULL ) != 0 ) || ( SIndLitBuscar ( p_indlObj, "" ) != -1 ) )
	{
		printf( "Error caso 5: con clave nula o vacia no deberia encontrarse nada\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SIndLitDestruir ( &p_indlObj );
	return ( iRes );
}

/* Eliminar y Vaciar. Vaciar eliminaba por indice creciente mientras los
   indices se desplazaban: se saltaba la mitad y la perdia sin destruirla.
   Con MODO_DEPURACION se comprueba que no queda memoria reservada. */
static int TestSIndLitEliminar01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SIndLitEliminar 01:\n" );
# if ( defined ( MODO_DEPURACION ) )
	unsigned long ulBloquesAntes = MemNumBloquesActuales ();
# endif
	SIndiceLiterales * p_indlObj = SIndLitCrear ();
	SIndLitInsertarExt ( p_indlObj, "kiwi", 1UL );
	SIndLitInsertarExt ( p_indlObj, "manzana", 2UL );
	SIndLitInsertarExt ( p_indlObj, "pera", 3UL );
	SIndLitInsertarExt ( p_indlObj, "uva", 4UL );
	SIndLitInsertarExt ( p_indlObj, "pera", 5UL );		/* repetida: no entra */

	if ( ( SIndLitEliminarClave ( p_indlObj, "manzana" ) != 1 ) ||
		 ( SIndLitNumElementos ( p_indlObj ) != 3 ) ||
		 ( SIndLitExiste ( p_indlObj, "manzana" ) != 0 ) )
	{
		printf( "Error caso 1: tras eliminar \"manzana\" deberian quedar 3 sin ella\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ( CadComparar ( SIndLitElementoClave ( p_indlObj, 0 ), "kiwi" ) != COMP_IGUAL ) ||
		 ( CadComparar ( SIndLitElementoClave ( p_indlObj, 1 ), "pera" ) != COMP_IGUAL ) )
	{
		printf( "Error caso 2: se esperaba kiwi, pera al principio\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( SIndLitEliminarClave ( p_indlObj, "fresa" ) != 0 )
	{
		printf( "Error caso 3: eliminar una clave que no esta deberia fallar\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ( SIndLitEliminar ( p_indlObj, 7 ) != 0 ) || ( SIndLitNumElementos ( p_indlObj ) != 3 ) )
	{
		printf( "Error caso 4: eliminar un indice fuera de rango deberia fallar\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SIndLitVaciar ( p_indlObj );
	if ( ( SIndLitEstaVacio ( p_indlObj ) != 1 ) || ( SIndLitNumElementos ( p_indlObj ) != 0 ) )
	{
		printf( "Error caso 5: tras vaciar deberia estar vacio: %d\n", SIndLitNumElementos ( p_indlObj ) );
		iRes = BOOL_VAL_FALSO;
	}
	/* Sigue sirviendo tras vaciarlo. */
	if ( ( SIndLitInsertarExt ( p_indlObj, "uva", 6UL ) != 1 ) || ( SIndLitPosicion ( p_indlObj, "uva" ) != 6UL ) )
	{
		printf( "Error caso 6: tras vaciar deberia poder insertarse de nuevo\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SIndLitDestruir ( &p_indlObj );
# if ( defined ( MODO_DEPURACION ) )
	if ( MemNumBloquesActuales () != ulBloquesAntes )
	{
		printf( "Error caso 7: quedan %ld bloques sin liberar\n", (long) ( MemNumBloquesActuales () - ulBloquesAntes ) );
		iRes = BOOL_VAL_FALSO;
	}
# endif
	return ( iRes );
}

static int TestSIndLitNulo01 ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf( "Test SIndLitNulo 01:\n" );
	if ( ( SIndLitEsValido ( NULL ) != 0 ) || ( SIndLitNumElementos ( NULL ) != 0 ) ||
		 ( SIndLitEstaVacio ( NULL ) != 1 ) )
	{
		printf( "Error caso 1: un indice nulo no es valido y esta vacio\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ( SIndLitInsertarExt ( NULL, "pera", 1UL ) != -1 ) || ( SIndLitBuscar ( NULL, "pera" ) != -1 ) ||
		 ( SIndLitExiste ( NULL, "pera" ) != 0 ) || ( SIndLitPosicion ( NULL, "pera" ) != SLCZ_SIN_POSICION ) )
	{
		printf( "Error caso 2: las operaciones sobre nulo deberian fallar sin colgarse\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ES_VALIDO ( SIndLitElemento ( NULL, 0 ) ) || ES_VALIDO ( SIndLitElementoClave ( NULL, 0 ) ) ||
		 ( SIndLitElementoPosicion ( NULL, 0 ) != SLCZ_SIN_POSICION ) )
	{
		printf( "Error caso 3: los accesos sobre nulo deberian dar nulo o sin posicion\n" );
		iRes = BOOL_VAL_FALSO;
	}
	SIndiceLiterales * p_indlNulo = NULL;
	SIndLitDestruir ( &p_indlNulo );
	ErrLimpiar ();
	return ( iRes );
}

int TestSIndiceLiterales ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test SIndiceLiterales]%s\n", ANSI_AMARILLO,  ANSI_RESETEAR );
	if ( ( TestSIndLitCrear01 () == BOOL_VAL_CIERTO ) &&
			( TestSIndLitInsertar01 () == BOOL_VAL_CIERTO ) &&
			( TestSIndLitBuscar01 () == BOOL_VAL_CIERTO ) &&
			( TestSIndLitEliminar01 () == BOOL_VAL_CIERTO ) &&
			( TestSIndLitNulo01 () == BOOL_VAL_CIERTO ) )
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
