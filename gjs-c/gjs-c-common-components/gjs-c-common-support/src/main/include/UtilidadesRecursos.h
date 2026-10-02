
#ifndef _ORG_GJS_C_CC_UTILIDADESRECURSOS_H
#define _ORG_GJS_C_CC_UTILIDADESRECURSOS_H








/* Recursos al estilo del classpath de Java: el recurso se nombra con una ruta
   RELATIVA y barras normales ( "data/prueba.properties" ), y se resuelve contra
   el directorio del ejecutable.

   ResBuscar devuelve la ruta completa, o NULL si el recurso no esta, igual que
   el getResource de Java. La cadena la reserva la funcion: el llamante la suelta
   con MemLiberarCadena.

   ResExiste responde lo mismo en forma de 1 / 0.

   Se rechazan las rutas absolutas y las de estilo Windows: componerlas con el
   directorio del ejecutable no tendria sentido. */
int ResExiste ( const char * p_cRecurso );
char * ResBuscar ( const char * p_cRecurso );







#endif
