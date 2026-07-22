#ifndef _ORG_GJS_C_CC_TEST_CONFIG_H
#define _ORG_GJS_C_CC_TEST_CONFIG_H



/* Rutas relativas usadas por los tests. Se centralizan aqui para poder
   cambiarlas facilmente cuando se fije la estrategia de directorios.
   Todas las rutas quedan dentro de /target (el cwd en ejecucion es
   /target/test-nar/test-reports).

   PENDIENTE (autor): confirmar ubicaciones definitivas. */


/* Recursos de entrada: maven-resources-plugin los copia (tratados como
   binarios) a /target/test-classes/data. Desde el cwd: */
#define FIC_TEST_DIR_DATA			"../data"

/* Salidas de los tests: idealmente /target/test-nar/results. Desde el cwd: */
#define FIC_TEST_DIR_RESULTS		"../results"

/* Fichero vacio de prueba disponible en los recursos de entrada. */
#define FIC_TEST_FIC_VACIO			FIC_TEST_DIR_DATA "/vacio.info"



#endif
