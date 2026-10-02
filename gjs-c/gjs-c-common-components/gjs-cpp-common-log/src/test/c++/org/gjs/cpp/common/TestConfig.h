#ifndef _ORG_GJS_C_CC_CPP_LOG_TEST_CONFIG_H
#define _ORG_GJS_C_CC_CPP_LOG_TEST_CONFIG_H


/* El test corre con el directorio de trabajo en target/test-nar/test-reports,
   asi que ".." es target/test-nar, que es donde el build deja los recursos de
   src/test/resources ya filtrados ( con ${project.artifactId} y compania
   sustituidos ). Misma convencion que el "../data" de los otros modulos. */
#define FIC_TEST_DIR_CONFIG				"../config"
#define FIC_TEST_DIR_LOG				"../log"

#define FIC_TEST_CFG_COMPLETA			FIC_TEST_DIR_CONFIG "/logjs.properties"
#define FIC_TEST_CFG_CONSOLA			FIC_TEST_DIR_CONFIG "/logjs-consola.properties"
#define FIC_TEST_CFG_FICHERO			FIC_TEST_DIR_CONFIG "/logjs-fichero.properties"


#endif
