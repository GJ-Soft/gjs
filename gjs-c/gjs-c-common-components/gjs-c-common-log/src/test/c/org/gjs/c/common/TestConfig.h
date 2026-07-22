#ifndef _ORG_GJS_C_CC_TEST_CONFIG_H
#define _ORG_GJS_C_CC_TEST_CONFIG_H



/* Rutas relativas usadas por los tests. Se centralizan aqui para poder
   cambiarlas facilmente cuando se fije la estrategia de directorios.
   Todas las rutas quedan dentro de /target (el cwd en ejecucion es
   /target/test-nar/test-reports). */


/* Recursos de entrada: maven-resources-plugin los copia (tratados como
   binarios) desde src/test/resources/data a /target/test-nar/data. Desde el
   cwd: */
#define FIC_TEST_DIR_DATA			"../data"

/* Salidas de los tests: /target/test-nar/results. Desde el cwd: */
#define FIC_TEST_DIR_RESULTS		"../results"




/* Utilidades de test compartidas (definidas en SPropiedadesTest.c). */

/* Simula una entrada de usuario por consola (para codigo que lee de stdin de
   forma bloqueante). "" simula pulsar solo <retorno>. Hay que restaurar con
   RestaurarEntradaConsola tras la lectura. Devuelve 1 si prepara la entrada. */
int SimularEntradaConsola ( const char * p_cEntrada );
void RestaurarEntradaConsola ();



#endif
