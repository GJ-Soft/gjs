
#include "UtilidadesRecursos.h"

#include "CommonSupportConfig.h"



using namespace std;

namespace org
{
	namespace gjs
	{
		namespace cpp
		{
            namespace common
            {




bool ResExiste ( const string & sRecurso )
{
	/* La cadena vacia es el "no encontrado" de ResBuscar. */
	return ( ! ResBuscar ( sRecurso ).empty () );
}

string ResBuscar ( const string & sRecurso )
{
	string sRes ( "" );

	/* Una comprobacion por if, y no fundidas en una condicion compuesta: cada una
	   llevara su codigo y su descripcion de error. */
	if ( ! sRecurso.empty () )
	{
		/* Las dos condiciones iban sin negar, pidiendo justo lo contrario de lo que
		   se queria: que el recurso FUERA de estilo Windows y absoluto. */
		if ( ! SisRutaEsEstiloWindows ( sRecurso ) )
		{
			if ( ! SisEsRutaAbsoluta ( sRecurso ) )
			{
				/* SisDirectorioEjecutable da el directorio de una vez; no hace falta
				   pedir la ruta completa y sacarle el directorio aparte. */
				string sDirectorio = SisDirectorioEjecutable ();

				if ( ! sDirectorio.empty () )
				{
					/* Ojo: en C++ SisNormalizarRuta DEVUELVE la ruta, no la cambia en
					   el sitio como su hermana de C. Llamarla sin recoger el resultado
					   no hacia nada. */
					string sRuta = SisNormalizarRuta ( SisComponerRuta ( sDirectorio, sRecurso, 0 ) );

					if ( SisExisteFichero ( sRuta ) )
					{
						sRes = sRuta;
					}
				}
			}
		}
	}
	return ( sRes );
}


            }
		}
	}
}
