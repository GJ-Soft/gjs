#include "BaseConfig.h"
#include "Sistema.h"

#include "FinExcepcion.h"
#include <stdlib.h>

using namespace std;

using namespace org::gjs::cpp::common;

// NOTA: No funciona bien con exit() ni abort() por la definición con _ATTRIBUTE ((__noreturn__))
void __wrap_exit( int iCodigo )
{
	throw ( FinExcepcion ( "EnvolturasSistema", "__wrap_exit", iCodigo ) );
}

/*char * __wrap_getenv( const char * p_cNombre )
{
	return ( (char *) VariableEntorno( p_cNombre ).c_str() );
}
*/
