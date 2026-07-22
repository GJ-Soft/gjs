#include "SDirectorio.h"


#include "FicherosConfig.h"





void _SDirVaciar ( SDirectorio * p_dirObj );



SDirectorio * SDirCrear ( SCadena * p_cadDirectorio )
{
	SDirectorio *	p_dirObj;
	
	p_dirObj = (SDirectorio *) MemReservar ( sizeof ( SDirectorio ) );
	if ( ES_VALIDO ( p_dirObj ) )
	{
		p_dirObj->p_rutObj = SRutCrearDirectorio ( p_cadDirectorio );
		if ( SRutEsDirectorio ( p_dirObj->p_rutObj ) == 1 )
		{
			p_dirObj->p_cadNombre = SCadDuplicar ( SRutSubdirectorio( p_dirObj->p_rutObj ) );
			p_dirObj->p_lisEntradas = SLispCrear ();
			SLispDesactivarLiberacionMemoria ( p_dirObj->p_lisEntradas );
			SDirRefrescar ( p_dirObj );
		}
		else
		{
			SRutDestruir ( &(p_dirObj->p_rutObj) );
			MemLiberar ( (void **) &p_dirObj );
		}	
	}
	return ( p_dirObj );
}

SDirectorio * SDirCrearLit ( const char * p_cDirectorio )
{
	SDirectorio *	p_dirObj;
	
	p_dirObj = (SDirectorio *) MemReservar ( sizeof ( SDirectorio ) );
	if ( ES_VALIDO ( p_dirObj ) )
	{
		p_dirObj->p_rutObj = SRutCrearDirectorioLit ( p_cDirectorio );
		if ( SRutEsDirectorio ( p_dirObj->p_rutObj ) == 1 )
		{
			p_dirObj->p_cadNombre = SCadDuplicar ( SRutSubdirectorio( p_dirObj->p_rutObj ) );
			p_dirObj->p_lisEntradas = SLispCrear ();
			SLispDesactivarLiberacionMemoria ( p_dirObj->p_lisEntradas );
			SDirRefrescar ( p_dirObj );
		}
		else
		{
			SRutDestruir ( &(p_dirObj->p_rutObj) );
			MemLiberar ( (void **) &p_dirObj );
		}	
	}
	return ( p_dirObj );
}

SDirectorio * SDirCrearRuta ( SRuta * p_rutDirectorio )
{
	SDirectorio *	p_dirObj;
	
	if ( SRutEsDirectorio ( p_rutDirectorio ) == 1 )
	{
		p_dirObj = (SDirectorio *) MemReservar ( sizeof ( SDirectorio ) );
		if ( ES_VALIDO ( p_dirObj ) )
		{
			p_dirObj->p_rutObj = SRutDuplicar ( p_rutDirectorio );
			if ( SRutEsDirectorio ( p_dirObj->p_rutObj ) == 1 )
			{
				p_dirObj->p_cadNombre = SCadDuplicar ( SRutSubdirectorio( p_dirObj->p_rutObj ) );
				p_dirObj->p_lisEntradas = SLispCrear ();
				SLispDesactivarLiberacionMemoria ( p_dirObj->p_lisEntradas );
				SDirRefrescar ( p_dirObj );
			}
			else
			{
				SRutDestruir ( &(p_dirObj->p_rutObj) );
				MemLiberar ( (void **) &p_dirObj );
			}	
		}
	}
	else
	{
		p_dirObj = NULL;
	}
	return ( p_dirObj );
}

SDirectorio * SDirCrearExt ( SCadena * p_cadDirectorio, SCadena * p_cadSubdirectorio )
{
	SDirectorio * p_dirObj = SDirCrear ( p_cadDirectorio );
	if ( ES_VALIDO ( p_dirObj ) && ES_VALIDO ( p_cadSubdirectorio ) )
	{
		SRutMoverA ( SDirRuta ( p_dirObj ), p_cadSubdirectorio );
	}
	else
	{
		SDirDestruir ( &p_dirObj );
	}
	return ( p_dirObj );
}

SDirectorio * SDirCrearLitExt ( const char * p_cDirectorio, const char * p_cSubdirectorio )
{
	SDirectorio * p_dirObj = SDirCrearLit ( p_cDirectorio );
	if ( ES_VALIDO ( p_dirObj ) && ES_VALIDO ( p_cSubdirectorio ) )
	{
		SRutMoverALit ( SDirRuta ( p_dirObj ), p_cSubdirectorio );
	}
	else
	{
		SDirDestruir ( &p_dirObj );
	}
	return ( p_dirObj );
}

SDirectorio * SDirCrearRutaExt ( SRuta * p_rutDirectorio, const char * p_cSubdirectorio )
{
	SDirectorio * p_dirObj = SDirCrearRuta ( p_rutDirectorio );
	if ( ES_VALIDO ( p_dirObj ) && ES_VALIDO ( p_cSubdirectorio ) )
	{
		SRutMoverALit ( SDirRuta ( p_dirObj ), p_cSubdirectorio );
	}
	else
	{
		SDirDestruir ( &p_dirObj );
	}
	return ( p_dirObj );
}

SDirectorio * SDirCrearRaiz ()
{
	return ( SDirCrearLit ( SisDirectorioRaiz () ) );
}

SDirectorio * SDirCrearActual ()
{
	return ( SDirCrearLit ( SisDirectorioActual () ) );
}

void SDirDestruir ( SDirectorio ** p_p_dirObj )
{
	SDirectorio * p_dirObj;
	
	if ( ES_VALIDO ( p_p_dirObj ) )
	{
		p_dirObj = *p_p_dirObj;
		if ( ES_VALIDO ( p_dirObj ) )
		{
			SCadDestruir ( &(p_dirObj->p_cadNombre) );
			_SDirVaciar ( p_dirObj );
			SLispDestruir ( &(p_dirObj->p_lisEntradas) );
			SRutDestruir ( &(p_dirObj->p_rutObj) );
			MemLiberar ( (void **) p_p_dirObj );
		}
	}
}

SRuta * SDirRuta ( SDirectorio * p_dirObj )
{
	SRuta *	p_rutRes;
	
	if ( ES_VALIDO ( p_dirObj ) )
	{
		p_rutRes = p_dirObj->p_rutObj;
	}
	else
	{
		p_rutRes = NULL;
	}
	return ( p_rutRes );
}

SCadena * SDirNombre ( SDirectorio * p_dirObj )
{
	SCadena *	p_cadRes;
	
	if ( ES_VALIDO ( p_dirObj ) )
	{
		p_cadRes = p_dirObj->p_cadNombre;
	}
	else
	{
		p_cadRes = NULL;
	}
	return ( p_cadRes );
}

const char * SDirNombreLit ( SDirectorio * p_dirObj )
{
	const char * p_cRes;
	
	if ( ES_VALIDO ( p_dirObj ) )
	{
		p_cRes = SCadValorConstante ( p_dirObj->p_cadNombre );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

int SDirEsValido ( SDirectorio * p_dirObj )
{
	int iRes;
	
	if ( ES_VALIDO ( p_dirObj ) )
	{
		if ( ( SRutEsValida ( p_dirObj->p_rutObj ) == 1 ) &&
			 ( SRutEsDirectorio ( p_dirObj->p_rutObj ) == 1 ) && 
			 ( SCadLongitud ( p_dirObj->p_cadNombre ) > 0 ) &&
		     ( SLispEsValida ( p_dirObj->p_lisEntradas ) == 1 ) )
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
	return ( iRes );
}


int SDirCambiar ( SDirectorio * p_dirObj, SCadena * p_cadDirectorio )
{
	int iRes;
	
	if ( ES_VALIDO ( p_dirObj ) )
	{
		if ( SRutEstablecerDirectorio ( p_dirObj->p_rutObj, p_cadDirectorio ) == 1 )
		{
			iRes = SDirRefrescar ( p_dirObj );
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

int SDirCambiarLit ( SDirectorio * p_dirObj, const char * p_cDirectorio )
{
	int iRes;
	
	if ( ES_VALIDO ( p_dirObj ) )
	{
		if ( SRutEstablecerDirectorioLit ( p_dirObj->p_rutObj, p_cDirectorio ) == 1 )
		{
			iRes = SDirRefrescar ( p_dirObj );
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

// PENDIENTE: Probar int fnmatch(const char *_pattern, const char *_string, int _flags);
// con int  glob(const char *_pattern, int _flags, int (*_errfunc)(const char *_epath, int _eerrno), glob_t *_pglob);
// para GNU de forma que retorne ordenos alfabéticamente los ficheros: 
// PENDIENTE2: FindFirstFile no garantiza que estén en orden alfabético, pues depende del
// sistema operativo concreto.
int SDirRefrescar ( SDirectorio * p_dirObj )
{
	SEntradaDirectorio *	p_entdirDatos;
	SCadena *				p_cadBusqueda;
	int						iRes;
	
# if ( defined ( WIN ) )
	WIN32_FIND_DATA			fndfildatObj;
	HANDLE					hBusqueda;
	int						iResBusq;
   
# else
	DIR *					p_dirInfo;
	SEntradaDirectorio *	p_entdirElem;
	int						iEnc;
	int						iEntrada;
	int						iError;
	int						iFin;
    struct dirent *			p_directInfo;
#endif
	
	if ( SDirEsValido ( p_dirObj ) == 1 )
	{
		_SDirVaciar ( p_dirObj );
		if ( SRutExiste ( p_dirObj->p_rutObj ) == 1 )
		{
# if ( defined ( WIN ) )
			p_cadBusqueda = SRutMascaraBusqueda ( p_dirObj->p_rutObj );
			if ( ES_VALIDO ( p_cadBusqueda ) )
			{
				hBusqueda = FindFirstFile ( SCadValorConstante ( p_cadBusqueda ), &fndfildatObj );
				if ( hBusqueda != INVALID_HANDLE_VALUE ) 
				{
					iRes = 1;
					iResBusq = 1;
					while ( ( iResBusq != 0 ) && ( iRes == 1 ) )
					{
						if ( fndfildatObj.cFileName [ 0 ] != '.' )
						{
							if ( SisExisteDirectorioExt ( SRutDirectorioLit ( p_dirObj->p_rutObj ), fndfildatObj.cFileName ) == 1)
							{
								p_entdirDatos = SEntDirCrearDirectorioLit ( fndfildatObj.cFileName );
							}
							else
							{
								p_entdirDatos = SEntDirCrearFicheroLit ( fndfildatObj.cFileName );
							}
							if ( ES_VALIDO ( p_entdirDatos ) )
							{
								iRes = SLispInsertarAlFinal ( p_dirObj->p_lisEntradas, (void *) p_entdirDatos );
							}
							else
							{
								iRes = 0;
							}
						}
						iResBusq = FindNextFile ( hBusqueda, &fndfildatObj );
					}
					if ( ( iResBusq == 0 ) && ( GetLastError () !=  ERROR_NO_MORE_FILES ) )
					{
						// ERROR:
						iRes = 0;
					}
					FindClose ( hBusqueda );
				}
				else
				{
					iRes = 0;
				}
# else
			p_cadBusqueda = SRutRutaAbsoluta ( p_dirObj->p_rutObj );
			if ( ES_VALIDO ( p_cadBusqueda ) )
			{
				p_dirInfo = opendir ( SCadValorConstante ( p_cadBusqueda ) );
				if ( ES_VALIDO ( p_dirInfo ) )
				{
					iFin = 0;
					iRes = 1;
					while ( ( iFin == 0 ) && ( iRes == 1 ) )
					{
						p_directInfo = readdir ( p_dirInfo );
						if ( ES_VALIDO ( p_directInfo ) )
						{
							if ( p_directInfo->d_name[0] != '.' )
							{
								if ( SisExisteDirectorioExt ( SRutDirectorioLit ( p_dirObj->p_rutObj ), p_directInfo->d_name ) == 1)
								{
									p_entdirDatos = SEntDirCrearDirectorioLit ( p_directInfo->d_name );
								}
								else
								{
									p_entdirDatos = SEntDirCrearFicheroLit ( p_directInfo->d_name );
								}
								if ( ES_VALIDO ( p_entdirDatos ) )
								{
									iError = 0;
									iEnc = 0;
									iEntrada = 0;
									int iNumEntradas = SLispNumElementos ( p_dirObj->p_lisEntradas );
									while ( ( iEnc == 0 ) && ( iEntrada < iNumEntradas ) && ( iError == 0 ) )
									{
										p_entdirElem = (SEntradaDirectorio *) SLispElemento( p_dirObj->p_lisEntradas, iEntrada );
										if ( ES_VALIDO ( p_entdirElem ) )
										{
											if ( SCadEsMayor ( SEntDirEntrada ( p_entdirDatos ), SEntDirEntrada ( p_entdirElem ) ) == 1 )
											{
												iEntrada = iEntrada + 1;
											}
											else
											{
												iEnc = 1;
											}
										}
										else
										{
											iError = 1;
										}
									}
									if ( iEnc == 1 )
									{
										SLispMoverA ( p_dirObj->p_lisEntradas, iEntrada );
										iRes = SLispInsertarDelante ( p_dirObj->p_lisEntradas, (void *) p_entdirDatos );
									}
									else
									{
										iRes = SLispInsertarAlFinal ( p_dirObj->p_lisEntradas, (void *) p_entdirDatos );
									}
								}
								else
								{
									iRes = 0;
								}
							}
						}
						else
						{
							iFin = 1;
						}
					}
				}
				else
				{
					iRes = 0;
				}
				closedir ( p_dirInfo );
# endif
				SCadDestruir ( &p_cadBusqueda );
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
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SDirNumEntradas ( SDirectorio * p_dirObj )
{
	int iRes;
	
	if ( ES_VALIDO ( p_dirObj ) )
	{
		iRes = SLispNumElementos ( p_dirObj->p_lisEntradas );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

SEntradaDirectorio * SDirEntrada ( SDirectorio * p_dirObj, int iEntrada )
{
	SEntradaDirectorio * p_entdirRes;

	if ( ES_VALIDO ( p_dirObj ) )
	{
		p_entdirRes = (SEntradaDirectorio *) SLispElemento ( p_dirObj->p_lisEntradas, iEntrada );
	}
	else
	{
		p_entdirRes = NULL;
	}
	return ( p_entdirRes );
}

SDirectorio * SDirAbrirSubdirectorio ( SDirectorio * p_dirObj, int iEntrada )
{
	return ( SDirAbrirSubdirectorioExt ( p_dirObj, SDirEntrada ( p_dirObj, iEntrada ) ) );
}

SDirectorio * SDirAbrirSubdirectorioExt ( SDirectorio * p_dirObj, SEntradaDirectorio * p_entdirEntrada )
{
	SDirectorio * p_dirRes;

	if ( ES_VALIDO ( p_dirObj ) && ES_VALIDO ( p_entdirEntrada ) )
	{
		if ( SEntDirEsDirectorio (  p_entdirEntrada ) == 1 )
		{
			p_dirRes = SDirCrearRutaExt ( SDirRuta ( p_dirObj ), SEntDirEntradaLit ( p_entdirEntrada ) );
		}
		else
		{
			p_dirRes = NULL;
		}
	}
	else
	{
		p_dirRes = NULL;
	}
	return ( p_dirRes );
}

int SDirCrearSubdirectorio ( SDirectorio * p_dirObj, SCadena * p_cadSubdirectorio )
{
	return ( SDirCrearSubdirectorioLit ( p_dirObj, SCadValorConstante ( p_cadSubdirectorio ) ) );
}

int SDirCrearSubdirectorioLit ( SDirectorio * p_dirObj, const char * p_cSubdirectorio )
{
	SEntradaDirectorio *	p_entdirDatos;
	int						iRes;

	if ( ( SDirEsValido ( p_dirObj ) == 1 ) && ( CadLongitud ( p_cSubdirectorio ) > 0 ) )
	{
		if ( SisCrearDirectorioExt ( SRutDirectorioLit ( p_dirObj->p_rutObj ), p_cSubdirectorio ) == 1 )
		{
			p_entdirDatos = SEntDirCrearDirectorioLit ( p_cSubdirectorio );
			if ( ES_VALIDO ( p_entdirDatos ) )
			{
				SLispInsertarAlFinal ( p_dirObj->p_lisEntradas, (void *) p_entdirDatos );
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
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

void SDirLiberarEntradas ( SDirectorio * p_dirObj )
{
	_SDirVaciar ( p_dirObj );
}

void _SDirVaciar ( SDirectorio * p_dirObj )
{
	int 					iNumElems;
	SEntradaDirectorio *	p_entdirObj;
	
	if ( ES_VALIDO ( p_dirObj ) )
	{
		iNumElems = SLispNumElementos ( p_dirObj->p_lisEntradas );
		for ( int iElem = 0; iElem < iNumElems; iElem = iElem + 1 )
		{
			p_entdirObj = (SEntradaDirectorio *) SLispElemento ( p_dirObj->p_lisEntradas, iElem );
			SEntDirDestruir ( &p_entdirObj );
		}
		SLispVaciar ( p_dirObj->p_lisEntradas );
	}
}




