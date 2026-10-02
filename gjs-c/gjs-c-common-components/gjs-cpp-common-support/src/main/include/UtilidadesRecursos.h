
#ifndef _ORG_GJS_C_CC_CPP_UTILIDADESRECURSOS_H
#define _ORG_GJS_C_CC_CPP_UTILIDADESRECURSOS_H



#include <string>


namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {



/* Recursos al estilo del classpath de Java: el recurso se nombra con una ruta
   RELATIVA y barras normales ( "data/ejemplo.properties" ), y se resuelve contra el
   directorio del ejecutable.

   ResBuscar devuelve la ruta completa, o la cadena VACIA si el recurso no esta,
   que es lo que aqui hace de null del getResource de Java. Por valor, no por
   puntero: la version anterior declaraba string y definia string *, asi que ni
   compilaba ni enlazaba.

   Se rechazan las rutas absolutas y las de estilo Windows: componerlas con el
   directorio del ejecutable no tendria sentido.

   std:: explicito, que aqui dentro no hay using namespace std. */
bool ResExiste ( const std::string & sRecurso );
std::string ResBuscar ( const std::string & sRecurso );




 			}
		}
	}
}






#endif
