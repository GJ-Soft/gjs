#include "AplicacionConfig.h"
#include "UtilidadesRecursos.h"


static char * _ResBuscarEnDir ( const char * p_cDirectorio, const char * p_cRecurso );



int ResExiste ( const char * p_cRecurso )
{
	int		iRes;
	char *	p_cRuta;
	
	p_cRuta = ResBuscar ( p_cRecurso );
	if ( ES_VALIDO ( p_cRuta ) )
	{
		iRes = 1;
		MemLiberarCadena ( &p_cRuta );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

char * ResBuscar ( const char * p_cRecurso )
{
	/* A NULL de entrada: si SisDirectorioEjecutable fallase, p_cRes se quedaba
	   sin asignar y mas abajo se leia, se normalizaba y se liberaba basura. */
	char * p_cRes = NULL;
	char * p_cDirectorio;

	/* Un recurso se nombra al estilo de Java: una ruta RELATIVA con barras
	   normales y sin unidad ni raiz, como "data/prueba.properties". Se rechaza lo
	   demas: una ruta absoluta o de estilo Windows no tiene sentido componerla con
	   el directorio del ejecutable.

	   La comprobacion era SisRutaEstiloUnix ( p_cRecurso ) == 1, y esa funcion no
	   es un predicado: devuelve un char * con la ruta convertida. Comparar ese
	   puntero con 1 es siempre falso, asi que ResBuscar devolvia NULL para TODO, y
	   ademas se perdia la cadena que reservaba. El predicado que hay es
	   SisRutaEsEstiloWindows. */
	if ( ES_VALIDO ( p_cRecurso ) && ( CadLongitud ( p_cRecurso ) > 0 ) &&
		 ( SisRutaEsEstiloWindows ( p_cRecurso ) == 0 ) &&
		 ( SisEsRutaAbsoluta ( p_cRecurso ) == 0 ) )
	{
		/* SisDirectorioEjecutable ya da el directorio: no hace falta pedir la ruta
		   completa y sacarle el directorio a mano, con dos reservas en vez de una. */
		p_cDirectorio = SisDirectorioEjecutable ();
		if ( ES_VALIDO ( p_cDirectorio ) )
		{
			p_cRes = _ResBuscarEnDir ( p_cDirectorio, p_cRecurso );
			MemLiberarCadena ( &p_cDirectorio );
			if ( ES_NULO ( p_cRes ) )
			{
				p_cDirectorio = SisDirectorioActual ();
				if ( ES_VALIDO ( p_cDirectorio ) )
				{
					p_cRes = _ResBuscarEnDir ( p_cDirectorio, p_cRecurso );
					MemLiberarCadena ( &p_cDirectorio );
				}
			}
		}
		/* Aqui no hace falta volver a normalizar ni a comprobar que existe:
		   _ResBuscarEnDir ya devuelve NULL si el recurso no esta. */
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

static char * _ResBuscarEnDir ( const char * p_cDirectorio, const char * p_cRecurso )
{
	char * p_cRes;

	p_cRes = SisComponerRuta ( p_cDirectorio, p_cRecurso, 0 );
	if ( ES_VALIDO ( p_cRes ) )
	{
		SisNormalizarRuta ( p_cRes );
		/* Como el getResource de Java: si el recurso no esta, no se devuelve
		   ruta. Sin esto ResExiste contestaba que si a cualquier nombre bien
		   formado, porque solo miraba si ResBuscar habia devuelto algo. */
		if ( SisExisteFichero ( p_cRes ) == 0 )
		{
			MemLiberarCadena ( &p_cRes );
			p_cRes = NULL;
		}
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}
