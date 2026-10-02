#include "Base.h"

#include <Sistema.h>		/* SisFicheroEjecutable */
#include <Ficheros.h>	/* SisRutaFichero */

#include "UtilidadesRecursos.h"
#include "TestConfig.h"



/* Un recurso que no existe en ningun sitio. */
#define REC_TEST_INEXISTENTE		"data/no-existe-este-recurso.properties"

/* El recurso de prueba. NO esta al lado del ejecutable: maven-resources-plugin
   copia src/test/resources a /target/test-nar y nar deja el ejecutable en
   /target/test-nar/bin/<AOL>, dos niveles mas abajo.

   Se resuelve igualmente porque ResBuscar, si no lo encuentra junto al
   ejecutable, lo busca en el DIRECTORIO ACTUAL, y los tests se lanzan desde
   /target/test-nar/test-reports, donde tambien se copia. O sea que este caso
   comprueba de paso ese respaldo. */
#define REC_TEST_DATOS				"data/prueba.properties"


/* Recurso que no existe: ResBuscar no devuelve ruta y ResExiste dice que no. */
static int TestResInexistente01 ()
{
	int		iRes = BOOL_VAL_CIERTO;
	char *	p_cRuta;

	printf ( "Test ResInexistente 01:\n" );

	p_cRuta = ResBuscar ( REC_TEST_INEXISTENTE );
	if ( ES_VALIDO ( p_cRuta ) )
	{
		printf ( "Error caso 1: ResBuscar devolvio ruta para un recurso inexistente: [%s]\n", p_cRuta );
		MemLiberarCadena ( &p_cRuta );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ResExiste ( REC_TEST_INEXISTENTE ) != 0 )
	{
		printf ( "Error caso 2: ResExiste dice que existe un recurso inexistente\n" );
		iRes = BOOL_VAL_FALSO;
	}

	/* Parametros que no son un recurso valido. */
	if ( ResExiste ( NULL ) != 0 )
	{
		printf ( "Error caso 3: ResExiste con NULL deberia decir que no\n" );
		iRes = BOOL_VAL_FALSO;
	}
	if ( ResExiste ( "" ) != 0 )
	{
		printf ( "Error caso 4: ResExiste con cadena vacia deberia decir que no\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}
static int TestResExistente01 ()
{
	int		iRes = BOOL_VAL_CIERTO;
	char *	p_cRuta;

	printf ( "Test ResExistente 01:\n" );

	/* Este caso tenia tres defectos, y el primero reventaba el test entero en
	   Windows:

	   - Se declaraba un p_cRecurso que nunca se asignaba y se soltaba al final
	     con MemLiberarCadena: liberar basura de la pila. En POSIX colaba; en
	     Windows el proceso moria con STATUS_HEAP_CORRUPTION ( 0xC0000374 ) y se
	     llevaba por delante los nueve bloques de test del componente.
	   - La ruta buena no se soltaba nunca: solo se liberaba en la rama de error,
	     que es justo donde vale NULL.
	   - Y en esa rama se imprimia con %s un puntero que se acababa de comprobar
	     que es NULL. */
	p_cRuta = ResBuscar ( REC_TEST_DATOS );
	if ( ES_NULO ( p_cRuta ) )
	{
		printf ( "Error caso 1: ResBuscar no devolvio ruta para [%s]\n", REC_TEST_DATOS );
		iRes = BOOL_VAL_FALSO;
	}
	else
	{
		MemLiberarCadena ( &p_cRuta );
	}
	if ( ResExiste ( REC_TEST_DATOS ) == 0 )
	{
		printf ( "Error caso 2: ResExiste dice que no existe un recurso existente\n" );
		iRes = BOOL_VAL_FALSO;
	}
	return ( iRes );
}


int TestUtilidadesRecursos ()
{
	int iRes = BOOL_VAL_CIERTO;
	printf ( "%s[Test UtilidadesRecursos]%s\n", ANSI_AMARILLO, ANSI_RESETEAR );
	if ( ( TestResInexistente01 () == BOOL_VAL_CIERTO ) &&
			( TestResExistente01 () == BOOL_VAL_CIERTO ) )
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
