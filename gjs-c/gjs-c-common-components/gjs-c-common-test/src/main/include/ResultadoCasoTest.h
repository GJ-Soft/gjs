#ifndef _ORG_GJS_C_CC_C_TEST_RESULTADO_CASO_TEST_H
#define _ORG_GJS_C_CC_C_TEST_RESULTADO_CASO_TEST_H



#define RESULTADO_CASO_TEST_OK 			0
#define RESULTADO_CASO_TEST_KO			1
#define RESULTADO_CASO_TEST_FAIL		2
/* El caso no se puede ejecutar en esta plataforma. Ni correcto ni erroneo:
   se cuenta aparte para no dar por bueno lo que no se ha ejecutado. */
#define RESULTADO_CASO_TEST_NO_SOPORTADO	3

 
#endif