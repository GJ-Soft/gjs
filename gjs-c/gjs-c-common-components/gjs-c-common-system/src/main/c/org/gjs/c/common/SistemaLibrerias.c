/******************************************************************************/
/*                            SistemaLibrerias.c                              */
/*----------------------------------------------------------------------------*/
/* Librería:  Sistema                                                         */
/* Versión:   3.0.0                                                           */
/* Fecha:     25/03/2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Fichero de código fuente que contiene la implementación de las rutinas     */
/* de carácter general de información acerca de los procesos en ejecución,    */
/* así como algunas rutinas de gestión de los mismos.                         */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#include "SistemaLibrerias.h"


#include "SistemaConfig.h"





/*
typedef struct _DllVersionInfo
{
	DWORD cbSize;
	DWORD dwMajorVersion;
	DWORD dwMinorVersion;
	DWORD dwBuildNumber;
	DWORD dwPlatformID;
} DLLVERSIONINFO;
#endif

#ifndef DLLGETVERSIONPROC
	typedef int (FAR WINAPI *DLLGETVERSIONPROC) (DLLVERSIONINFO *);
#endif

*/





# if ( ! defined ( WIN ) )

/******************************************************************************/
/* Soporte de la rama POSIX                                                   */
/*----------------------------------------------------------------------------*/
/* POSIX da dlopen / dlsym / dlclose para cargar y resolver, pero NO da nada   */
/* equivalente a EnumProcessModules ni a GetModuleInformation: no hay forma    */
/* estandar de preguntar que librerias hay cargadas, donde estan ni cuanto     */
/* ocupan. glibc tiene dl_iterate_phdr y dlinfo, pero Cygwin NO los trae       */
/* ( comprobado el 2026-09-18: no existe ni link.h ), asi que no sirven si se  */
/* quieren los dos mundos.                                                    */
/*                                                                            */
/* Lo que si tienen los dos, y con el mismo formato, es /proc/self/maps. De    */
/* ahi salen la enumeracion, la ruta, la direccion base y el tamano. Si algun  */
/* dia hay un POSIX sin /proc, esas cuatro devolveran "nada", que es lo mismo  */
/* que devolvian antes.                                                       */
/******************************************************************************/

#include <dlfcn.h>

#define SIS_LIB_FIC_MAPA			"/proc/self/maps"
#define SIS_LIB_TAM_LINEA_MAPA		( MAXPATHLEN + 128 )
#define SIS_LIB_SUFIJO_SO			".so."

/* El separador de directorios y el punto de la extension. En POSIX son
   siempre estos dos; el modulo de ficheros los tiene en su cabecera privada
   y desde aqui no se ven. */
#define SIS_LIB_SEP_DIRECTORIO		'/'
#define SIS_LIB_SEP_EXTENSION			'.'


/* Devuelve donde empieza el nombre del fichero dentro de la ruta. No copia. */
static const char * _SisLibNombreEnRuta ( const char * p_cRuta )
{
	const char *	p_cRes;

	p_cRes = strrchr ( p_cRuta, SIS_LIB_SEP_DIRECTORIO );
	if ( p_cRes != NULL )
	{
		p_cRes = p_cRes + 1;
	}
	else
	{
		p_cRes = p_cRuta;
	}
	return ( p_cRes );
}

/* Coincide si el nombre del fichero es exactamente el pedido, o si es el
   pedido seguido de un punto. Asi "libm" encuentra "libm.so.6" y
   "cygpcre2-8-0" encuentra "cygpcre2-8-0.dll", que es lo que viene a hacer
   GetModuleHandle en la rama de Windows. A diferencia de aquella, aqui se
   distinguen mayusculas y minusculas, que es lo propio de POSIX. */
static int _SisLibNombreCoincide ( const char * p_cRuta, const char * p_cLibreria )
{
	int				iRes;
	const char *	p_cNombre;
	const char *	p_cPedido;
	size_t			uLongitud;

	p_cNombre = _SisLibNombreEnRuta ( p_cRuta );
	/* Del lado del que pregunta tambien se coge solo el nombre: asi vale
	   igual que le pasen "cygwin1.dll" que "/usr/bin/cygwin1.dll", que es
	   lo que admite GetModuleHandle en la rama de Windows. */
	p_cPedido = _SisLibNombreEnRuta ( p_cLibreria );
	if ( CadComparar ( p_cNombre, p_cPedido ) == COMP_IGUAL )
	{
		iRes = 1;
	}
	else
	{
		uLongitud = strlen ( p_cPedido );
		if ( strncmp ( p_cNombre, p_cPedido, uLongitud ) == 0 )
		{
			if ( p_cNombre [ uLongitud ] == SIS_LIB_SEP_EXTENSION )
			{
				iRes = 1;
			}
			else
			{
				iRes = 0;
			}
		}
		else
		{
			iRes = 0;
		}
	}
	return ( iRes );
}

/* Parte una linea de /proc/self/maps. Devuelve 1 solo si la linea corresponde
   a un fichero mapeado: las anonimas y las [heap], [stack] y companeras no
   llevan ruta y no interesan. p_iCodigo puede ser NULL si no hace falta.
   Ojo: la ruta que devuelve apunta DENTRO de la linea, que ademas se modifica
   para quitarle el salto de linea final. */
static int _SisLibPartirLineaMapa ( char * p_cLinea, unsigned long * p_ulIni,
									unsigned long * p_ulFin, int * p_iCodigo,
									const char ** p_p_cRuta )
{
	int			iRes;
	char		cPermisos [ 8 ];
	char *		p_cBarra;
	char *		p_cSalto;

	if ( sscanf ( p_cLinea, "%lx-%lx %7s", p_ulIni, p_ulFin, cPermisos ) == 3 )
	{
		p_cBarra = strchr ( p_cLinea, SIS_LIB_SEP_DIRECTORIO );
		if ( p_cBarra != NULL )
		{
			p_cSalto = strchr ( p_cBarra, ASCII_LF );
			if ( p_cSalto != NULL )
			{
				*p_cSalto = ASCII_NUL;
			}
			if ( ES_VALIDO ( p_iCodigo ) )
			{
				if ( strchr ( cPermisos, 'x' ) != NULL )
				{
					*p_iCodigo = 1;
				}
				else
				{
					*p_iCodigo = 0;
				}
			}
			*p_p_cRuta = p_cBarra;
			iRes = 1;
		}
		else
		{
			iRes = 0;
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

/* Recorre el mapa buscando la libreria. Deja en los parametros de salida la
   primera direccion y la ultima de todos sus tramos ( una libreria aparece en
   varios: codigo, datos, solo lectura... ), y devuelve la ruta completa
   duplicada, que hay que liberar, o NULL si no esta mapeada. */
static char * _SisLibBuscarEnMapa ( const char * p_cLibreria,
									unsigned long * p_ulIni, unsigned long * p_ulFin )
{
	char *			p_cRes;
	FILE *			p_filMapa;
	char			cLinea [ SIS_LIB_TAM_LINEA_MAPA ];
	unsigned long	ulIni;
	unsigned long	ulFin;
	const char *	p_cRuta;

	p_cRes = NULL;
	*p_ulIni = 0;
	*p_ulFin = 0;
	p_filMapa = fopen ( SIS_LIB_FIC_MAPA, "r" );
	if ( p_filMapa != NULL )
	{
		while ( fgets ( cLinea, sizeof ( cLinea ), p_filMapa ) != NULL )
		{
			if ( _SisLibPartirLineaMapa ( cLinea, &ulIni, &ulFin, NULL, &p_cRuta ) == 1 )
			{
				if ( _SisLibNombreCoincide ( p_cRuta, p_cLibreria ) == 1 )
				{
					if ( ES_NULO ( p_cRes ) )
					{
						p_cRes = CadDuplicar ( p_cRuta );
						*p_ulIni = ulIni;
						*p_ulFin = ulFin;
					}
					else
					{
						if ( ulIni < *p_ulIni )
						{
							*p_ulIni = ulIni;
						}
						if ( ulFin > *p_ulFin )
						{
							*p_ulFin = ulFin;
						}
					}
				}
			}
		}
		fclose ( p_filMapa );
	}
	return ( p_cRes );
}

/* En POSIX no hay nada como DllGetVersion, que es una convencion de las DLL
   del shell de Windows. Lo que si es convencion aqui es llevar la version en
   el propio nombre del fichero ( libfoo.so.1.2.3 ), y de ahi se saca. Si la
   libreria no la lleva, como pasa con los .dll de Cygwin, no hay version que
   dar y se devuelve 0, igual que cuando una DLL no exporta DllGetVersion. */
static int _SisLibVersionDelNombre ( const char * p_cRuta, int * p_iVersion,
									 int * p_iSubversion, int * p_iRevision,
									 int * p_iBug )
{
	int				iRes;
	const char *	p_cNombre;
	const char *	p_cSufijo;
	int				iValor [ 4 ];

	p_cNombre = _SisLibNombreEnRuta ( p_cRuta );
	p_cSufijo = strstr ( p_cNombre, SIS_LIB_SUFIJO_SO );
	if ( p_cSufijo != NULL )
	{
		iValor [ 0 ] = 0;
		iValor [ 1 ] = 0;
		iValor [ 2 ] = 0;
		iValor [ 3 ] = 0;
		if ( sscanf ( p_cSufijo + strlen ( SIS_LIB_SUFIJO_SO ), "%d.%d.%d.%d",
					  &iValor [ 0 ], &iValor [ 1 ], &iValor [ 2 ], &iValor [ 3 ] ) >= 1 )
		{
			if ( ES_VALIDO ( p_iVersion ) )
			{
				*p_iVersion = iValor [ 0 ];
			}
			if ( ES_VALIDO ( p_iSubversion ) )
			{
				*p_iSubversion = iValor [ 1 ];
			}
			if ( ES_VALIDO ( p_iRevision ) )
			{
				*p_iRevision = iValor [ 2 ];
			}
			if ( ES_VALIDO ( p_iBug ) )
			{
				*p_iBug = iValor [ 3 ];
			}
			iRes = 1;
		}
		else
		{
			iRes = 0;
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

# endif


int SisLibCargar ( const char * p_cLibreria )
{
	int			iRes;

# if ( defined ( WIN ) )
	HMODULE		hmodLib;
# else
	void *		p_vLib;
# endif

	if ( ES_VALIDO ( p_cLibreria ) )
	{
		if ( SisLibEstaCargada ( p_cLibreria ) == 0 )
		{
#		  if ( defined ( WIN ) )
			hmodLib = LoadLibrary ( p_cLibreria );
			if ( hmodLib != NULL )
			{
				iRes = 1;
			}
			else
			{
				iRes = 0;
			}
#		  else
			/* RTLD_GLOBAL para que lo que traiga quede visible a las
			   resoluciones posteriores, que es lo que hace LoadLibrary.
			   El manejador no se guarda ni se cierra a proposito: la rama de
			   Windows tampoco llama a FreeLibrary, y la libreria se queda
			   cargada mientras viva el proceso. */
			p_vLib = dlopen ( p_cLibreria, RTLD_NOW | RTLD_GLOBAL );
			if ( p_vLib != NULL )
			{
				iRes = 1;
			}
			else
			{
				iRes = 0;
			}
#	      endif
		}
		else
		{
			iRes = 1;
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SisLibEstaCargada ( const char * p_cLibreria )
{
	int		iRes;

# if ( defined ( WIN ) )
	HMODULE	hmodLib;
# else
	char *			p_cRuta;
	unsigned long	ulIni;
	unsigned long	ulFin;
# endif

	if ( ES_VALIDO ( p_cLibreria ) )
	{
#	  if ( defined ( WIN ) )
		hmodLib = GetModuleHandle ( p_cLibreria );
		if ( hmodLib != NULL )
		{
			// GetModuleHandle no incrementa el contador de referencias de la libreria
			// No hace falta liberar
			iRes = 1;
		}
		else
		{
			iRes = 0;
		}
#	  else
		/* Se mira el mapa de memoria, y NO se le pregunta al enlazador
		   dinamico. Lo natural seria dlopen con RTLD_NOLOAD, que da manejador
		   solo si la libreria ya estaba cargada; pero CYGWIN NO RESPETA ESA
		   BANDERA ( comprobado el 2026-09-18: la carga igualmente y queda
		   mapeada ). Usarla convertiria esta consulta en una carga, y ademas
		   contestaria que si a cualquier libreria que exista en el disco.
		   El mapa, de paso, ve tambien las que cargo el sistema al arrancar el
		   proceso y nunca pasaron por dlopen, que es lo que se quiere. */
		p_cRuta = _SisLibBuscarEnMapa ( p_cLibreria, &ulIni, &ulFin );
		if ( ES_VALIDO ( p_cRuta ) )
		{
			MemLiberarCadena ( &p_cRuta );
			iRes = 1;
		}
		else
		{
			iRes = 0;
		}
#     endif
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

void * SisLibPrimitiva ( const char * p_cLibreria, const char * p_cPrimitiva )
{
	void *		p_vRes;

# if ( defined ( WIN ) )
	HMODULE		hmodLib;
# else
	void *			p_vLib;
	char *			p_cRuta;
	unsigned long	ulIni;
	unsigned long	ulFin;
# endif

	if ( ES_VALIDO ( p_cLibreria ) && ES_VALIDO ( p_cPrimitiva ) )
	{
#	  if ( defined ( WIN ) )
		//hmodLib = LoadLibrary ( p_cLibreria );
		hmodLib = GetModuleHandle ( p_cLibreria );
		if ( hmodLib != NULL )
		{
			// GetModuleHandle no incrementa el contador de referencias de la libreria
			// No hace falta liberar
			p_vRes = (void *) GetProcAddress ( hmodLib, p_cPrimitiva );
		}
		else
		{
			p_vRes = NULL;
		}
#	  else
		/* La rama de Windows resuelve con GetModuleHandle, que NO carga nada:
		   si la libreria no esta, no hay simbolo. Aqui hay que conseguir lo
		   mismo, y RTLD_NOLOAD no sirve porque Cygwin no lo respeta
		   ( comprobado ), asi que la comprobacion se hace contra el mapa.
		   Hecha esa, el dlopen solo sube el contador de algo que ya estaba
		   cargado, y el dlclose lo baja sin llegar a descargarlo ( tambien
		   comprobado ), con lo que la direccion devuelta sigue siendo valida. */
		p_cRuta = _SisLibBuscarEnMapa ( p_cLibreria, &ulIni, &ulFin );
		if ( ES_VALIDO ( p_cRuta ) )
		{
			/* Con la ruta completa que dio el mapa y no con el nombre que
			   llego: asi vale igual cuando se pidio sin extension. */
			p_vLib = dlopen ( p_cRuta, RTLD_NOW );
			if ( p_vLib != NULL )
			{
				p_vRes = dlsym ( p_vLib, p_cPrimitiva );
				dlclose ( p_vLib );
			}
			else
			{
				p_vRes = NULL;
			}
			MemLiberarCadena ( &p_cRuta );
		}
		else
		{
			p_vRes = NULL;
		}
#	  endif
	}
	else
	{
		p_vRes = NULL;
	}
	return ( p_vRes );
}

SListaLiterales * SisLibCargadas ()
{
	SListaLiterales *	p_lisLibrerias;
 	SBuffer	*			p_bufLibrerias;
 	SBuffer	*			p_bufNombre;
	int					iError;
	char *				p_cNombre;

# if ( defined ( WIN ) )
	int					iNumLibs;
	int					iLib;
	HANDLE				hProceso;
	HMODULE *			p_hmodLib;
	DWORD				dwTamOcupado;
#else
	FILE *				p_filMapa;
	char				cLinea [ SIS_LIB_TAM_LINEA_MAPA ];
	unsigned long		ulIni;
	unsigned long		ulFin;
	int					iCodigo;
	const char *		p_cRuta;
#endif

	p_lisLibrerias = SLisLitCrear ();
 	p_bufLibrerias = SBufCrear ( SIS_SO_MAX_TAM_BUFFER );
 	p_bufNombre = SBufCrear ( MAXPATHLEN );
	if ( ES_VALIDO ( p_bufLibrerias ) && ES_VALIDO ( p_bufNombre ) && ES_VALIDO ( p_lisLibrerias ) )
	{
# if ( defined ( WIN ) )
		hProceso = OpenProcess ( PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, GetCurrentProcessId () );
		if ( hProceso != NULL )
		{
			p_hmodLib = (HMODULE *) SBufDireccion ( p_bufLibrerias );
			if ( EnumProcessModules ( hProceso, p_hmodLib, (DWORD) SBufTam ( p_bufLibrerias ), &dwTamOcupado ) != 0 )
			{
				/* Si lo ocupado llega a lo que cabe, EnumProcessModules ha
				   truncado la lista y faltan modulos. Antes esto pasaba en
				   silencio y se devolvia una lista incompleta como si fuera
				   buena; ahora se dice que fallo, que es lo honesto mientras
				   no se reintente con un buffer mayor. */
				if ( dwTamOcupado >= (DWORD) SBufTam ( p_bufLibrerias ) )
				{
					iError = 1;
				}
				else
				{
					iNumLibs = dwTamOcupado / sizeof ( HMODULE );
					iLib = 0;
					iError = 0;
					while ( ( iLib < iNumLibs ) && ( iError == 0 ) )
					{
						if ( p_hmodLib [ iLib ] != 0 )
						{
							SBufLimpiar ( p_bufNombre );
							if ( GetModuleBaseName ( hProceso, p_hmodLib [ iLib ], (LPTSTR)SBufDireccion ( p_bufNombre ), (DWORD) SBufTam ( p_bufNombre ) / sizeof ( char ) ) > 0 )
							{
								p_cNombre = SBufDuplicarCadena ( p_bufNombre );
								if ( ES_VALIDO  ( p_cNombre ) )
								{
									/* Con InsertarDup, no con Insertar: la lista
									   se queda el puntero que se le pasa, y aqui
									   debajo se libera. Tal y como estaba, la
									   lista se quedaba con memoria ya liberada. */
									if ( SLisLitInsertarDupAlFinal ( p_lisLibrerias, p_cNombre ) == 0 )
									{
										iError = 1;
									}
									MemLiberar ( (void **) &p_cNombre );
								}
								else
								{
									iError = 1;
								}
							}
							else
							{
								iError = 1;
							}
						}
						iLib = iLib + 1;
					}
				}
				if ( iError == 1 )
				{
					SLisLitVaciar ( p_lisLibrerias );
				}
			}
			else
			{
				SLisLitDestruir ( &p_lisLibrerias );
			}
			CloseHandle ( hProceso );
		}
		else
		{
			SLisLitDestruir ( &p_lisLibrerias );
		}
# else
		p_filMapa = fopen ( SIS_LIB_FIC_MAPA, "r" );
		if ( p_filMapa != NULL )
		{
			iError = 0;
			while ( ( iError == 0 ) && ( fgets ( cLinea, sizeof ( cLinea ), p_filMapa ) != NULL ) )
			{
				if ( _SisLibPartirLineaMapa ( cLinea, &ulIni, &ulFin, &iCodigo, &p_cRuta ) == 1 )
				{
					/* Solo los ficheros que tienen algun tramo con codigo: asi
					   quedan fuera los datos que el sistema tambien mapea, como
					   las .NLS de Windows bajo Cygwin. Y solo una vez cada uno,
					   que cada libreria aparece en varios tramos. */
					if ( iCodigo == 1 )
					{
						p_cNombre = SisRutaFichero ( p_cRuta );
						if ( ES_VALIDO ( p_cNombre ) )
						{
							if ( SLisLitExiste ( p_lisLibrerias, p_cNombre ) == 0 )
							{
								if ( SLisLitInsertarDupAlFinal ( p_lisLibrerias, p_cNombre ) == 0 )
								{
									iError = 1;
								}
							}
							MemLiberarCadena ( &p_cNombre );
						}
						else
						{
							iError = 1;
						}
					}
				}
			}
			fclose ( p_filMapa );
			if ( iError == 1 )
			{
				SLisLitVaciar ( p_lisLibrerias );
			}
		}
		else
		{
			SLisLitDestruir ( &p_lisLibrerias );
		}
# endif
	}
	else
	{
		SLisLitDestruir ( &p_lisLibrerias );
	}
	SBufDestruir ( &p_bufLibrerias );
	SBufDestruir ( &p_bufNombre );
	return ( p_lisLibrerias );
}


char * SisLibRutaFichero ( const char * p_cLibreria )
{
	char *		p_cRes;
 	SBuffer	*	p_bufDatos;
	int			iLibOk;

# if ( defined ( WIN ) )
	int			iTam;
	HMODULE		hmodLib;
# else
	char *			p_cRutaMapa;
	unsigned long	ulIni;
	unsigned long	ulFin;
# endif

	if ( ES_VALIDO ( p_cLibreria ) )
	{
#	  if ( defined ( WIN ) )
		//hmodLib = LoadLibrary ( p_cLibreria );
		hmodLib = GetModuleHandle ( p_cLibreria );
		if ( hmodLib != NULL )
		{
			iLibOk = 1;
		}
		else
		{
			iLibOk = 0;
		}
#	  else
		/* El mapa ya trae la ruta completa, asi que la busqueda y la respuesta
		   son la misma operacion: se guarda aqui y abajo solo se entrega. */
		p_cRutaMapa = _SisLibBuscarEnMapa ( p_cLibreria, &ulIni, &ulFin );
		if ( ES_VALIDO ( p_cRutaMapa ) )
		{
			iLibOk = 1;
		}
		else
		{
			iLibOk = 0;
		}
#	  endif
	}
	else
	{
		iLibOk = 0;
	}

	if ( iLibOk == 1 )
	{
 		p_bufDatos = SBufCrear ( MAXPATHLEN );
		if ( ES_VALIDO ( p_bufDatos ) )
		{

	# if ( defined ( WIN ) )
			iTam = (int) GetModuleFileName ( hmodLib, (LPTSTR) SBufDireccion ( p_bufDatos ), ((DWORD) SBufTam ( p_bufDatos )) / sizeof ( char ) );
			if ( iTam > 0 )
			{
				p_cRes = SBufDuplicarCadena ( p_bufDatos );
			}
			else
			{
				p_cRes = NULL;
			}
	# else
			p_cRes = p_cRutaMapa;
	# endif
			SBufDestruir ( &p_bufDatos );
		}
		else
		{
			p_cRes = NULL;
	# if ( ! defined ( WIN ) )
			MemLiberarCadena ( &p_cRutaMapa );
	# endif
		}
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

char * SisLibDirectorioFichero ( const char * p_cLibreria )
{
	char * p_cRuta;
	char * p_cRes;

	p_cRuta = SisLibRutaFichero ( p_cLibreria );
	if ( ES_VALIDO ( p_cRuta ) )
	{
		p_cRes = SisRutaDirectorio ( p_cRuta );
		MemLiberar ( (void **) &p_cRuta );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

char * SisLibFichero ( const char * p_cLibreria )
{
	char * p_cRuta;
	char * p_cRes;

	p_cRuta = SisLibRutaFichero ( p_cLibreria );
	if ( ES_VALIDO ( p_cRuta ) )
	{
		p_cRes = SisRutaFichero ( p_cRuta );
		MemLiberar ( (void **) &p_cRuta );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

#if ( defined ( WIN ) )
void * SisLibRutinaPuntoDeEntrada ( const char * p_cLibreria )
{
	void *				p_vRes;
	int					iLibOk;
	HMODULE				hmodLib;
	struct _MODULEINFO 	modinfLib;
	HANDLE				hProceso;

	if ( ES_VALIDO ( p_cLibreria ) )
	{
		hmodLib = GetModuleHandle ( p_cLibreria );
		if ( hmodLib != NULL )
		{
			iLibOk = 1;
		}
		else
		{
			iLibOk = 0;
		}
	}
	else
	{
		iLibOk = 0;
	}

	if ( iLibOk == 1 )
	{
		hProceso = OpenProcess ( PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, GetCurrentProcessId () );
		if ( hProceso != NULL )
		{
			if ( GetModuleInformation ( hProceso, hmodLib, &modinfLib, sizeof ( struct _MODULEINFO ) ) != 0 )
			{
				p_vRes = modinfLib.EntryPoint;
			}
			else
			{
				p_vRes = NULL;
			}
			CloseHandle ( hProceso );
		}
		else
		{
			p_vRes = NULL;
		}
	}
	else
	{
		p_vRes = NULL;
	}
	return ( p_vRes );
}
#endif

void * SisLibDireccionMemoria ( const char * p_cLibreria )
{
	void *		p_vRes;
	int			iLibOk;

# if ( defined ( WIN ) )
	HMODULE				hmodLib;
	struct _MODULEINFO 	modinfLib;
	HANDLE				hProceso;
# else
	char *			p_cRutaMapa;
	unsigned long	ulIni;
	unsigned long	ulFin;
# endif

	if ( ES_VALIDO ( p_cLibreria ) )
	{
# if ( defined ( WIN ) )
		//hmodLib = LoadLibrary ( p_cLibreria );
		hmodLib = GetModuleHandle ( p_cLibreria );
		if ( hmodLib != NULL )
		{
			iLibOk = 1;
		}
		else
		{
			iLibOk = 0;
		}
#	  else
		p_cRutaMapa = _SisLibBuscarEnMapa ( p_cLibreria, &ulIni, &ulFin );
		if ( ES_VALIDO ( p_cRutaMapa ) )
		{
			MemLiberarCadena ( &p_cRutaMapa );
			iLibOk = 1;
		}
		else
		{
			iLibOk = 0;
		}
#	  endif
	}
	else
	{
		iLibOk = 0;
	}

	if ( iLibOk == 1 )
	{
# if ( defined ( WIN ) )
		hProceso = OpenProcess ( PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, GetCurrentProcessId () );
		if ( hProceso != NULL )
		{
			if ( GetModuleInformation ( hProceso, hmodLib, &modinfLib, sizeof ( struct _MODULEINFO ) ) != 0 )
			{
				p_vRes = modinfLib.lpBaseOfDll;
			}
			else
			{
				p_vRes = NULL;
			}
			CloseHandle ( hProceso );
		}
		else
		{
			p_vRes = NULL;
		}
#	  else
		/* La direccion mas baja de todos los tramos de la libreria, que es lo
		   que en Windows llaman lpBaseOfDll. */
		p_vRes = (void *) ulIni;
#	  endif
	}
	else
	{
		p_vRes = NULL;
	}
	return ( p_vRes );
}

unsigned long SisLibTamMemoria ( const char * p_cLibreria )
{
	unsigned long	ulRes;
	int				iLibOk;

# if ( defined ( WIN ) )
	HMODULE				hmodLib;
	struct _MODULEINFO 	modinfLib;
	HANDLE				hProceso;
# else
	char *			p_cRutaMapa;
	unsigned long	ulIni;
	unsigned long	ulFin;
# endif

	if ( ES_VALIDO ( p_cLibreria ) )
	{
# if ( defined ( WIN ) )
		//hmodLib = LoadLibrary ( p_cLibreria );
		hmodLib = GetModuleHandle ( p_cLibreria );
		if ( hmodLib != NULL )
		{
			iLibOk = 1;
		}
		else
		{
			iLibOk = 0;
		}
#	  else
		p_cRutaMapa = _SisLibBuscarEnMapa ( p_cLibreria, &ulIni, &ulFin );
		if ( ES_VALIDO ( p_cRutaMapa ) )
		{
			MemLiberarCadena ( &p_cRutaMapa );
			iLibOk = 1;
		}
		else
		{
			iLibOk = 0;
		}
#	  endif
	}
	else
	{
		iLibOk = 0;
	}

	if ( iLibOk == 1 )
	{
# if ( defined ( WIN ) )
		hProceso = OpenProcess ( PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, GetCurrentProcessId () );
		if ( hProceso != NULL )
		{
			if ( GetModuleInformation ( hProceso, hmodLib, &modinfLib, sizeof ( struct _MODULEINFO ) ) != 0 )
			{
				ulRes = (unsigned long) modinfLib.SizeOfImage;
			}
			else
			{
				ulRes = 0;
			}
			CloseHandle ( hProceso );
		}
		else
		{
			ulRes = 0;
		}
	# else
		/* De la primera direccion a la ultima de sus tramos. No es exactamente
		   el SizeOfImage de Windows: puede haber huecos entre tramos y aqui van
		   contados, igual que los cuenta aquel. */
		ulRes = ulFin - ulIni;
	# endif
	}
	else
	{
		ulRes = 0;
	}
	return ( ulRes );
}

char * SisLibCadenaVersion ( const char * p_cLibreria )
{
	char *	p_cRes;
	int		iVersion;
	int		iSubversion;
	int		iRevision;
	int		iCorreccion;

	iVersion = 0;
	iSubversion = 0;
	iRevision = 0;
	iCorreccion = 0;
	if ( SisLibVersion ( p_cLibreria, &iVersion, &iSubversion, &iRevision, &iCorreccion ) == 1 )
	{
		p_cRes = VersCadena ( iVersion, iSubversion, iRevision, iCorreccion );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

int SisLibVersion ( const char * p_cLibreria, int * p_iVersion, int * p_iSubversion, int * p_iRevision, int * p_iBug )
{
	int					iRes;
	int					iLibOk;

# if ( defined ( WIN ) )
	HMODULE				hmodLib;
    DLLGETVERSIONPROC	p_fDllGetVersion;
    DLLVERSIONINFO		dllverinfDatos;
	HRESULT				hresEjec;
# else
	char *			p_cRutaMapa;
	unsigned long	ulIni;
	unsigned long	ulFin;
# endif

	if ( ES_VALIDO ( p_cLibreria ) )
	{
#	  if ( defined ( WIN ) )
		//hmodLib = LoadLibrary ( p_cLibreria );
		hmodLib = GetModuleHandle ( p_cLibreria );
		if ( hmodLib != NULL )
		{
			iLibOk = 1;
		}
		else
		{
			iLibOk = 0;
		}
#	  else
		p_cRutaMapa = _SisLibBuscarEnMapa ( p_cLibreria, &ulIni, &ulFin );
		if ( ES_VALIDO ( p_cRutaMapa ) )
		{
			iLibOk = 1;
		}
		else
		{
			iLibOk = 0;
		}
#	  endif
	}
	else
	{
		iLibOk = 0;
	}

	if ( iLibOk == 1 )
	{
	# if ( defined ( WIN ) )

        p_fDllGetVersion = (DLLGETVERSIONPROC) GetProcAddress ( hmodLib, "DllGetVersion" );
        if ( ES_VALIDO ( p_fDllGetVersion ) )
        {
            ZeroMemory ( &dllverinfDatos, sizeof ( dllverinfDatos ) );
            dllverinfDatos.cbSize = sizeof ( dllverinfDatos );
            hresEjec = (*p_fDllGetVersion)( &dllverinfDatos );

            if( SUCCEEDED ( hresEjec ) )
            {
				if ( ES_VALIDO ( p_iVersion ) )
				{
					*p_iVersion = (int) dllverinfDatos.dwMajorVersion;
				}
				if ( ES_VALIDO ( p_iSubversion ) )
				{
	                *p_iSubversion = (int) dllverinfDatos.dwMinorVersion;
				}
				if ( ES_VALIDO ( p_iRevision ) )
				{
		            *p_iRevision = (int) dllverinfDatos.dwBuildNumber;
				}
				if ( ES_VALIDO ( p_iBug ) )
				{
		            *p_iBug = (int) dllverinfDatos.dwBuildNumber;
				}
				iRes = 1;
            }
            else
			{
				iRes = 0;
	        }
        }
        else
		{
			iRes = 0;
	    }
	# else
		iRes = _SisLibVersionDelNombre ( p_cRutaMapa, p_iVersion, p_iSubversion,
										 p_iRevision, p_iBug );
		MemLiberarCadena ( &p_cRutaMapa );
	# endif
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

