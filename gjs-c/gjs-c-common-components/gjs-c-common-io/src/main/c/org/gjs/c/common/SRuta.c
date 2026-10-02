
#include "SRuta.h"
#include "SistemaFicheros.h"

#include "FicherosConfig.h"




SRuta * SRutCrearFichero ( SCadena * p_cadDirectorio, SCadena * p_cadFichero )
{
	SRuta *	p_rutObj;
	
	p_rutObj = (SRuta *) MemReservar ( sizeof ( SRuta ) );
	if ( ES_VALIDO ( p_rutObj ) )
	{
		p_rutObj->p_cadDirectorio = SCadDuplicar ( p_cadDirectorio );
		p_rutObj->p_cadFichero = SCadDuplicar ( p_cadFichero );
		SCadEliminarBlancosLaterales ( p_rutObj->p_cadDirectorio );
		SCadEliminarBlancosLaterales ( p_rutObj->p_cadFichero );
	}
	return ( p_rutObj );
}

SRuta * SRutCrearFicheroLit ( const char * p_cDirectorio, const char * p_cFichero )
{
	SRuta *	p_rutObj;
	
	p_rutObj = (SRuta *) MemReservar ( sizeof ( SRuta ) );
	if ( ES_VALIDO ( p_rutObj ) )
	{
		p_rutObj->p_cadDirectorio = SCadGenerar ( p_cDirectorio );
		p_rutObj->p_cadFichero = SCadGenerar ( p_cFichero );
		SCadEliminarBlancosLaterales ( p_rutObj->p_cadDirectorio );
		SCadEliminarBlancosLaterales ( p_rutObj->p_cadFichero );
	}
	return ( p_rutObj );
}

SRuta * SRutCrearDirectorio ( SCadena * p_cadDirectorio )
{
	SRuta *	p_rutObj;
	
	p_rutObj = (SRuta *) MemReservar ( sizeof ( SRuta ) );
	if ( ES_VALIDO ( p_rutObj ) )
	{
		p_rutObj->p_cadDirectorio = SCadDuplicar ( p_cadDirectorio );
		SCadEliminarBlancosLaterales ( p_rutObj->p_cadDirectorio );
		p_rutObj->p_cadFichero = NULL;
	}
	return ( p_rutObj );
}

SRuta * SRutCrearDirectorioLit ( const char * p_cDirectorio )
{
	SRuta *	p_rutObj;
	
	p_rutObj = (SRuta *) MemReservar ( sizeof ( SRuta ) );
	if ( ES_VALIDO ( p_rutObj ) )
	{
		p_rutObj->p_cadDirectorio = SCadGenerar ( p_cDirectorio );
		SCadEliminarBlancosLaterales ( p_rutObj->p_cadDirectorio );
		p_rutObj->p_cadFichero = NULL;
	}
	return ( p_rutObj );
}

SRuta * SRutCrearDirectorioActual ()
{
    return ( SRutCrearDirectorioLit ( SisDirectorioActual () ) );
}

void SRutDestruir ( SRuta ** p_p_rutObj )
{
	SRuta * p_rutObj;
	
	if ( ES_VALIDO ( p_p_rutObj ) )
	{
		p_rutObj = *p_p_rutObj;
		if ( ES_VALIDO ( p_rutObj ) )
		{
			SCadDestruir ( &(p_rutObj->p_cadDirectorio) );			
			SCadDestruir ( &(p_rutObj->p_cadFichero) );
			MemLiberar ( (void **) p_p_rutObj );
		}
	}
}

SCadena * SRutDirectorio ( SRuta * p_rutObj )
{
	SCadena *	p_cadRes;
	
	if ( ES_VALIDO ( p_rutObj ) )
	{
		p_cadRes = p_rutObj->p_cadDirectorio;
	}
	else
	{
		p_cadRes = NULL;
	}
	return ( p_cadRes );
}

const char * SRutDirectorioLit ( SRuta * p_rutObj )
{
	const char * p_cRes;
	
	if ( ES_VALIDO ( p_rutObj ) )
	{
		p_cRes = SCadValorConstante ( p_rutObj->p_cadDirectorio );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

SCadena * SRutFichero ( SRuta * p_rutObj )
{
	SCadena *	p_cadRes;
	
	if ( ES_VALIDO ( p_rutObj ) )
	{
		p_cadRes = p_rutObj->p_cadFichero;
	}
	else
	{
		p_cadRes = NULL;
	}
	return ( p_cadRes );
}

const char * SRutFicheroLit ( SRuta * p_rutObj )
{
	const char * p_cRes;
	
	if ( ES_VALIDO ( p_rutObj ) )
	{
		p_cRes = SCadValorConstante ( p_rutObj->p_cadFichero );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

int SRutEsValida ( SRuta * p_rutObj )
{
	int iRes;
	
	if ( ES_VALIDO ( p_rutObj ) )
	{
		if ( ( SRutEsDirectorioValido ( p_rutObj ) == 1 ) &&
		     ( ( SRutEsFicheroValido ( p_rutObj ) == 1 )  || ES_NULO ( p_rutObj->p_cadFichero ) ) )
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

int SRutEsDirectorioValido ( SRuta * p_rutObj )
{
	int	iRes;

	if ( ES_VALIDO ( p_rutObj ) )
	{
        iRes = SisEsRutaValida ( SCadValorConstante ( p_rutObj->p_cadDirectorio ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SRutEsFicheroValido ( SRuta * p_rutObj )
{
	int	iRes;

	if ( ES_VALIDO ( p_rutObj ) )
	{
        iRes = SisEsFicheroValido ( SCadValorConstante ( p_rutObj->p_cadFichero ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SRutEsDirectorio ( SRuta * p_rutObj )
{
	int iRes;
	
	if ( ES_VALIDO ( p_rutObj ) )
	{
		if ( ES_VALIDO ( p_rutObj->p_cadFichero ) )
		{
			iRes = 0;
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

int SRutEsFichero ( SRuta * p_rutObj )
{
	int iRes;
	
	if ( ES_VALIDO ( p_rutObj ) )
	{
		if ( ES_VALIDO ( p_rutObj->p_cadFichero ) )
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

int SRutEsAbsoluta ( SRuta * p_rutObj )
{
	int iRes;
	
	if ( ES_VALIDO ( p_rutObj ) )
	{
        iRes = SisEsRutaAbsoluta ( SCadValorConstante ( p_rutObj->p_cadDirectorio ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SRutEsRelativa ( SRuta * p_rutObj )
{
	int iRes;
	
	if ( ES_VALIDO ( p_rutObj ) )
	{
        iRes = SisEsRutaRelativa ( SCadValorConstante ( p_rutObj->p_cadDirectorio ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

/* Las dos siguientes miraban el directorio con expresiones de estilo PCRE
   ( ^, [^/], +, $ ) que ExpRegSeCumple no entiende, y devolvian siempre 0.
   Ahora usan su sintaxis: SF_PATRON_DIR_UNIX / SF_PATRON_DIR_DOS. Un
   directorio sin separadores ni unidad ( "tmp" ) es de los dos estilos. */
int SRutEsEstiloUNIX ( SRuta * p_rutObj )
{
	int				iRes;
	const char *	p_cDir;

	if ( ES_VALIDO ( p_rutObj ) )
	{
		p_cDir = SCadValorConstante ( p_rutObj->p_cadDirectorio );
		if ( CadContieneCaracter ( p_cDir, '\\' ) == 0 )
		{
			if ( CadCaracter ( p_cDir, 1 ) != ':' )
			{
				iRes = ExpRegSeCumple ( SF_PATRON_DIR_UNIX, p_cDir );
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

int SRutEsEstiloDOS ( SRuta * p_rutObj )
{
	int				iRes;
	const char *	p_cDir;

	if ( ES_VALIDO ( p_rutObj ) )
	{
		p_cDir = SCadValorConstante ( p_rutObj->p_cadDirectorio );
		if ( CadContieneCaracter ( p_cDir, '/' ) == 0 )
		{
			iRes = ExpRegSeCumple ( SF_PATRON_DIR_DOS, p_cDir );
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

int SRutExiste ( SRuta * p_rutObj )
{
	int iRes;
	
	if ( ES_VALIDO ( p_rutObj ) )
	{
        if ( SRutEsFichero ( p_rutObj ) == 1 )
        {
            iRes = SRutExisteFichero ( p_rutObj );
        }
        else if ( SRutEsDirectorio ( p_rutObj ) == 1 )
        {
            iRes = SRutExisteDirectorio ( p_rutObj );
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

int SRutExisteDirectorio ( SRuta * p_rutObj )
{
	int iRes;

	if ( ES_VALIDO ( p_rutObj ) )
	{
        if ( ES_VALIDO ( p_rutObj->p_cadDirectorio ) )
        {
            iRes = SisExisteDirectorio ( SCadValorConstante ( p_rutObj->p_cadDirectorio ) );
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

int SRutExisteFichero ( SRuta * p_rutObj )
{
	int     iRes;
	char *	p_cRuta;
	
	if ( ES_VALIDO ( p_rutObj ) )
	{
        if ( ES_VALIDO ( p_rutObj->p_cadFichero ) )
        {
            p_cRuta = SRutRutaAbsolutaLit ( p_rutObj );
            if ( ES_VALIDO ( p_cRuta ) )
            {
                iRes = SisExisteFichero ( p_cRuta );
                MemLiberar ( (void **) &p_cRuta );
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

int SRutTieneExtension ( SRuta * p_rutObj )
{
	int iRes;
	
	if ( ES_VALIDO ( p_rutObj ) )
	{
		if ( SCadBuscarCaracterDesc ( p_rutObj->p_cadFichero, '.', SCadLongitud ( p_rutObj->p_cadFichero ) - 1 ) > 0 )
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

int SRutTieneExtensionExt ( SRuta * p_rutObj, const char * p_cExt )
{
	int     iRes;
    char *  p_cFinal;
	
	if ( ES_VALIDO ( p_rutObj ) )
	{
		if ( ES_VALIDO ( p_cExt ) )
		{
            p_cFinal = CadCrearConFormato ( ".%s", p_cExt );
            iRes = SCadAcabaPorLiteral ( p_rutObj->p_cadFichero, p_cFinal );
            MemLiberar ( (void **) &p_cFinal );
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

SCadena * SRutRuta ( SRuta * p_rutObj )
{
	SCadena * p_cadRes;

	if ( ES_VALIDO ( p_rutObj ) )
	{
        if ( SRutEsFichero ( p_rutObj ) == 1 )
        {
		    p_cadRes = SCadGenerarConFormato ( "%s%c%s", p_rutObj->p_cadDirectorio, SisSeparadorRutaFicheros (), p_rutObj->p_cadFichero );
        }
        else
        {
		    p_cadRes = SCadDuplicar ( p_rutObj->p_cadDirectorio );
        }
	}
	else
	{
		p_cadRes = NULL;
	}
	return ( p_cadRes );
}

char * SRutRutaLit ( SRuta * p_rutObj )
{
	char *	p_cRes;

	if ( ES_VALIDO ( p_rutObj ) )
	{
		p_cRes = SisComponerRuta ( SCadValorConstante ( p_rutObj->p_cadDirectorio ), SCadValorConstante ( p_rutObj->p_cadFichero ), 0 );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

SCadena * SRutRutaAbsoluta ( SRuta * p_rutObj )
{
	SCadena *   p_cadRes;
    char *      p_cDirAbsoluto;

	if ( ES_VALIDO ( p_rutObj ) )
	{
        if ( SRutEsRelativa ( p_rutObj ) == 1 )
        {
            p_cDirAbsoluto = SisResolverDirectorioRelativo ( SisDirectorioActual (), SCadValorConstante ( p_rutObj->p_cadDirectorio ) );
		    p_cadRes = SCadGenerarConFormato ( "%s%c%s", p_cDirAbsoluto, SisSeparadorRutaFicheros (), p_rutObj->p_cadFichero );
            MemLiberar ( (void **) &p_cDirAbsoluto );
        }
        else
        {
		    p_cadRes = SRutRuta ( p_rutObj );
        }
	}
	else
	{
		p_cadRes = NULL;
	}
	return ( p_cadRes );
}

char * SRutRutaAbsolutaLit ( SRuta * p_rutObj )
{
	char *	p_cRes;
    char *  p_cDirAbsoluto;

	if ( ES_VALIDO ( p_rutObj ) )
	{
        if ( SRutEsRelativa ( p_rutObj ) == 1 )
        {
            p_cDirAbsoluto = SisResolverDirectorioRelativo ( SisDirectorioActual (), SCadValorConstante ( p_rutObj->p_cadDirectorio ) );
    		p_cRes = SisComponerRuta ( p_cDirAbsoluto, SCadValorConstante ( p_rutObj->p_cadFichero ), 0 );
            MemLiberar ( (void **) &p_cDirAbsoluto );
        }
        else
        {
		    p_cRes = SRutRutaLit ( p_rutObj );
        }
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

SCadena * SRutSubdirectorio ( SRuta * p_rutObj )
{
	int			iPos;
	SCadena *	p_cadRes;

	if ( ES_VALIDO ( p_rutObj ) )
	{
		iPos = SCadBuscarCaracterDesc ( p_rutObj->p_cadDirectorio, '/', SCadLongitud ( p_rutObj->p_cadDirectorio ) - 1 );
		if ( iPos < 0 )
		{
			iPos = SCadBuscarCaracterDesc ( p_rutObj->p_cadDirectorio, '\\', SCadLongitud ( p_rutObj->p_cadDirectorio ) - 1 );
		}
		if ( iPos >= 0 )
		{
			p_cadRes = SCadExtraerUltimos ( p_rutObj->p_cadDirectorio, SCadLongitud ( p_rutObj->p_cadDirectorio )  - iPos - 1 );
		}
		else
		{
			p_cadRes = NULL;
		}
	}
	else
	{
		p_cadRes = NULL;
	}
	return ( p_cadRes );
}

char * SRutSubdirectorioLit ( SRuta * p_rutObj )
{
	int		iPos;
	char *	p_cRes;

	if ( ES_VALIDO ( p_rutObj ) )
	{
		iPos = CadBuscarDescCaracter ( SCadValor ( p_rutObj->p_cadDirectorio ), '/', SCadLongitud ( p_rutObj->p_cadDirectorio ) - 1 );
		if ( iPos < 0 )
		{
			iPos = CadBuscarDescCaracter ( SCadValor ( p_rutObj->p_cadDirectorio ), '\\', SCadLongitud ( p_rutObj->p_cadDirectorio ) - 1 );
		}
		if ( iPos >= 0 )
		{
			 p_cRes = CadExtraerUltimos ( SCadValor ( p_rutObj->p_cadDirectorio ), SCadLongitud ( p_rutObj->p_cadDirectorio )  - iPos - 1 );
		}
		else
		{
			p_cRes = NULL;
		}
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

SCadena * SRutFicheroExtension ( SRuta * p_rutObj )
{
	int			iPosPunto;
	SCadena *	p_cadExt;

	if ( SRutEsFichero ( p_rutObj ) == 1 )
	{
		iPosPunto = SCadBuscarCaracter ( p_rutObj->p_cadFichero, '.', 0 );
		if ( iPosPunto > 0 )
		{
			p_cadExt = SCadExtraerUltimos ( p_rutObj->p_cadFichero, SCadLongitud ( p_rutObj->p_cadFichero ) - iPosPunto - 1 );
		}
		else
		{
			p_cadExt = NULL;
		}
	}
	else
	{
		p_cadExt = NULL;
	}
	return ( p_cadExt );
}

char * SRutFicheroExtensionLit ( SRuta * p_rutObj )
{
	int		iPosPunto;
	char *	p_cExt;

	if ( SRutEsFichero ( p_rutObj ) == 1 )
	{
		iPosPunto = SCadBuscarCaracter ( p_rutObj->p_cadFichero, '.', 0 );
		if ( iPosPunto > 0 )
		{
			p_cExt = CadExtraerUltimos ( SCadValor ( p_rutObj->p_cadFichero ), SCadLongitud ( p_rutObj->p_cadFichero ) - iPosPunto - 1 );
		}
		else
		{
			p_cExt = NULL;
		}
	}
	else
	{
		p_cExt = NULL;
	}
	return ( p_cExt );
}

SCadena * SRutFicheroSinExtension ( SRuta * p_rutObj )
{
	int			iPosPunto;
	SCadena *	p_cadExt;

	if ( SRutEsFichero ( p_rutObj ) == 1 )
	{
		iPosPunto = SCadBuscarCaracter ( p_rutObj->p_cadFichero, '.', 0 );
		if ( iPosPunto > 0 )
		{
			p_cadExt = SCadExtraerPrimeros ( p_rutObj->p_cadFichero, iPosPunto );
		}
		else
		{
			p_cadExt = NULL;
		}
	}
	else
	{
		p_cadExt = NULL;
	}
	return ( p_cadExt );
}

char * SRutFicheroSinExtensionLit ( SRuta * p_rutObj )
{
	int		iPosPunto;
	char *	p_cExt;

	if ( SRutEsFichero ( p_rutObj ) == 1 )
	{
		iPosPunto = SCadBuscarCaracter ( p_rutObj->p_cadFichero, '.', 0 );
		if ( iPosPunto > 0 )
		{
			p_cExt = CadExtraerPrimeros (  SCadValor ( p_rutObj->p_cadFichero ), iPosPunto );
		}
		else
		{
			p_cExt = NULL;
		}
	}
	else
	{
		p_cExt = NULL;
	}
	return ( p_cExt );
}

SCadena * SRutMascaraBusqueda ( SRuta * p_rutObj )
{
	SCadena * p_cadRes;

	if ( ES_VALIDO ( p_rutObj ) )
	{
		p_cadRes = SCadGenerarConFormato ( "%s%c*.*", SCadValorConstante ( p_rutObj->p_cadDirectorio ), SisSeparadorRutaFicheros () );
	}
	else
	{
		p_cadRes = NULL;
	}
	return ( p_cadRes );
}

char * SRutMascaraBusquedaLit ( SRuta * p_rutObj )
{
	char * p_cRes;

	if ( ES_VALIDO ( p_rutObj ) )
	{
		p_cRes = CadCrearConFormato ( "%s%c*.*", SCadValorConstante ( p_rutObj->p_cadDirectorio ), SisSeparadorRutaFicheros () );
	}
	else
	{
		p_cRes = NULL;
	}
	return ( p_cRes );
}

int SRutEstablecerDirectorio ( SRuta * p_rutObj, SCadena * p_cadDirectorio )
{
	int iRes;
	
	if ( ES_VALIDO ( p_rutObj ) && ES_VALIDO ( p_cadDirectorio ) )
	{
		iRes = SCadAsignar ( p_rutObj->p_cadDirectorio, p_cadDirectorio );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SRutEstablecerDirectorioLit ( SRuta * p_rutObj, const char * p_cDirectorio )
{
	int iRes;
	
	if ( ES_VALIDO ( p_rutObj ) && ES_VALIDO ( p_cDirectorio ) )
	{
		iRes = SCadAsignarLiteral ( p_rutObj->p_cadDirectorio, p_cDirectorio );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SRutEstablecerFichero ( SRuta * p_rutObj, SCadena * p_cadFichero )
{
	int iRes;
	
	if ( ES_VALIDO ( p_rutObj )  )
	{
        if ( ES_VALIDO ( p_cadFichero ) )
        {
		    iRes = SCadAsignar ( p_rutObj->p_cadFichero, p_cadFichero );
        }
        else
        {
            p_rutObj->p_cadFichero = NULL;
            iRes = 1;
        }
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SRutEstablecerFicheroLit ( SRuta * p_rutObj, const char * p_cFichero )
{
	int iRes;
	
	if ( ES_VALIDO ( p_rutObj )  )
	{
        if ( ES_VALIDO ( p_cFichero ) )
        {
		    iRes = SCadAsignarLiteral ( p_rutObj->p_cadFichero, p_cFichero );
        }
        else
        {
            p_rutObj->p_cadFichero = NULL;
            iRes = 1;
        }
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SRutEstablecer ( SRuta * p_rutObj, SCadena * p_cadDirectorio, SCadena * p_cadFichero )
{
	int iRes;
	
	if ( ( SRutEstablecerDirectorio ( p_rutObj, p_cadDirectorio ) == 1 ) &&
         ( SRutEstablecerFichero ( p_rutObj, p_cadFichero ) == 1 ) )
	{
        iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SRutEstablecerLit ( SRuta * p_rutObj, const char * p_cDirectorio, const char * p_cFichero )
{
	int iRes;
	
	if ( ( SRutEstablecerDirectorioLit ( p_rutObj, p_cDirectorio ) == 1 ) &&
         ( SRutEstablecerFicheroLit ( p_rutObj, p_cFichero ) == 1 ) )
	{
        iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SRutEstablecerDirectorioActual ( SRuta * p_rutObj )
{
    int             iRes;
	const char *    p_cDir;

	p_cDir = SisDirectorioActual ();
	iRes = SRutEstablecerDirectorioLit ( p_rutObj, p_cDir );
    return ( iRes );
}

int SRutAsignar ( SRuta * p_rutObj, SRuta * p_rutValor )
{
	int iRes;
	
	if ( ES_VALIDO ( p_rutValor ) )
	{
 	    iRes = SRutEstablecer ( p_rutObj, SRutDirectorio ( p_rutValor ), SRutFichero ( p_rutValor ) );
 	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SRutEstablecerExtension ( SRuta * p_rutObj, SCadena * p_cadExt )
{
	int         iRes;
	SCadena *	p_cadNuevo;
	
	if ( SRutEsFichero ( p_rutObj ) == 1 )
	{
		p_cadNuevo = SRutFicheroSinExtension ( p_rutObj );
		if ( ES_VALIDO ( p_cadNuevo ) )
		{
            if ( ES_VALIDO ( p_cadExt ) )
            {
                SCadConcatenarCaracter ( p_cadNuevo, '.' );
                SCadConcatenar ( p_cadNuevo, p_cadExt );
            }
            SCadAsignar ( p_rutObj->p_cadFichero, p_cadNuevo );
			SCadDestruir ( &p_cadNuevo );
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

int SRutEstablecerExtensionLit ( SRuta * p_rutObj, const char * p_cExt )
{
	int         iRes;
	SCadena *	p_cadNuevo;
	
	if ( SRutEsFichero ( p_rutObj ) == 1 )
	{
		p_cadNuevo = SRutFicheroSinExtension ( p_rutObj );
		if ( ES_VALIDO ( p_cadNuevo ) )
		{
            if ( ES_VALIDO ( p_cExt ) )
            {
                SCadConcatenarCaracter ( p_cadNuevo, '.' );
                SCadConcatenarLiteral ( p_cadNuevo, p_cExt );
            }
            SCadAsignar ( p_rutObj->p_cadFichero, p_cadNuevo );
			SCadDestruir ( &p_cadNuevo );
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

int SRutAgregarExtension ( SRuta * p_rutObj, SCadena * p_cadExt )
{
	int  iRes;
	
	if ( ( SRutEsFichero ( p_rutObj ) == 1 ) && ES_VALIDO ( p_cadExt ) )
    {
        SCadConcatenarCaracter ( p_rutObj->p_cadFichero, '.' );
        SCadConcatenar ( p_rutObj->p_cadFichero, p_cadExt );
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SRutAgregarExtensionLit ( SRuta * p_rutObj, const char * p_cExt )
{
	int iRes;
	int iLong;
	int	iCaracteres;
	
	if ( ( SRutEsFichero ( p_rutObj ) == 1 ) && ES_VALIDO ( p_cExt ) )
    {
		iLong = SCadLongitud ( p_rutObj->p_cadFichero );
		iCaracteres = CadLongitud ( p_cExt ) + 1;
		if ( SCadMaxTam ( p_rutObj->p_cadFichero ) < iLong + iCaracteres ) 
		{
			SCadEstablecerMaxTam ( p_rutObj->p_cadFichero, iLong + iCaracteres );
		}
        SCadConcatenarCaracter ( p_rutObj->p_cadFichero, '.' );
        SCadConcatenarLiteral ( p_rutObj->p_cadFichero, p_cExt );
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SRutEliminarExtension ( SRuta * p_rutObj )
{
	int iRes;
	int	iPosPunto;

	if ( SRutEsFichero ( p_rutObj ) == 1 )
	{
		iPosPunto = SCadBuscarCaracterDesc ( p_rutObj->p_cadFichero, '.', SCadLongitud ( p_rutObj->p_cadFichero ) - 1 );
		if ( iPosPunto > 0 )
		{
			iRes = SCadEliminarUltimosCaracteres ( p_rutObj->p_cadFichero, SCadLongitud ( p_rutObj->p_cadFichero ) - iPosPunto );
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

int SRutMoverA ( SRuta * p_rutObj, SCadena * p_cadSubdirectorio )
{
	int     iRes;

	if ( ( SRutEsValida ( p_rutObj ) == 1 ) && ( SCadLongitud ( p_cadSubdirectorio ) > 0 ) )
	{
		iRes = SCadConcatenarConFormato ( p_rutObj->p_cadDirectorio, "/%s", SCadValorConstante ( p_cadSubdirectorio ) );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SRutMoverALit ( SRuta * p_rutObj, const char * p_cSubdirectorio )
{
	int     iRes;
 
	if ( ( SRutEsValida ( p_rutObj ) == 1 ) && ( CadLongitud ( p_cSubdirectorio ) > 0 ) )
	{
		iRes = SCadConcatenarConFormato ( p_rutObj->p_cadDirectorio, "/%s", p_cSubdirectorio );
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SRutEliminar ( SRuta * p_rutObj )
{
	int     iRes;
    char *  p_cRuta;

	if ( SRutEsValida ( p_rutObj ) == 1 )
	{
        p_cRuta = SRutRutaAbsolutaLit ( p_rutObj );
        if ( ES_VALIDO ( p_cRuta ) )
        {
            if ( SRutEsFichero ( p_rutObj ) == 1 )
            {
                if ( SRutExisteFichero ( p_rutObj ) == 1 )
                {
                    #if ( defined ( WIN ) )
                    if ( DeleteFileA ( p_cRuta ) != 0 )
                    #else
                    if ( remove ( p_cRuta ) == 0 )
                    #endif
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
                    iRes = 1;
                }
            }
            else if ( SRutEsDirectorio ( p_rutObj ) == 1 )
            {
                if ( SRutExisteDirectorio ( p_rutObj ) == 1 )
                {
                    #if ( defined ( WIN ) )
                    if ( RemoveDirectory ( p_cRuta ) != 0 )
                    #else
                    if ( rmdir ( p_cRuta ) == 0 )
                    #endif
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
                    iRes = 1;
                }
            }
            else
            {
                iRes = 0;
            }
            MemLiberar ( (void **) &p_cRuta );
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

SRuta * SRutDuplicar ( SRuta * p_rutObj )
{
   SRuta *  p_rutCopia;

	if ( ES_VALIDO ( p_rutObj ) )
	{
	    p_rutCopia = SRutCrearFichero ( SRutDirectorio ( p_rutObj ), SRutFichero ( p_rutObj ) );
    }
    else
    {
        p_rutCopia = NULL;
    }
	return ( p_rutCopia );
}


int SRutEsOculto ( SRuta * p_rutObj )
{
	int     iRes;
    char *  p_cRuta;

	if ( ES_VALIDO ( p_rutObj ) )
	{
        p_cRuta = SRutRutaAbsolutaLit ( p_rutObj );
        if ( ES_VALIDO ( p_cRuta ) )
        {
		    iRes = SisRutaOculta ( p_cRuta );
            MemLiberar ( (void **) &p_cRuta );
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

int SRutEsAccesible ( SRuta * p_rutObj )
{
	int     iRes;
    char *  p_cRuta;

	if ( ES_VALIDO ( p_rutObj ) )
	{
        p_cRuta = SRutRutaAbsolutaLit ( p_rutObj );
        if ( ES_VALIDO ( p_cRuta ) )
        {
		    iRes = SisFicheroEsAccesible ( p_cRuta );
            MemLiberar ( (void **) &p_cRuta );
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

int SRutEsDeSoloLectura ( SRuta * p_rutObj )
{
	int     iRes;
    char *  p_cRuta;

	if ( ES_VALIDO ( p_rutObj ) )
	{
        p_cRuta = SRutRutaAbsolutaLit ( p_rutObj );
        if ( ES_VALIDO ( p_cRuta ) )
        {
		    iRes = SisRutaDeSoloLectura ( p_cRuta );
            MemLiberar ( (void **) &p_cRuta );
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

int SRutEsDelSistema ( SRuta * p_rutObj )
{
	int     iRes;
    char *  p_cRuta;

	if ( ES_VALIDO ( p_rutObj ) )
	{
        p_cRuta = SRutRutaAbsolutaLit ( p_rutObj );
        if ( ES_VALIDO ( p_cRuta ) )
        {
		    iRes = SisRutaDelSistema ( p_cRuta );
            MemLiberar ( (void **) &p_cRuta );
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

int SRutEsTemporal ( SRuta * p_rutObj )
{
	int     iRes;
    char *  p_cRuta;

	if ( ES_VALIDO ( p_rutObj ) )
	{
        p_cRuta = SRutRutaAbsolutaLit ( p_rutObj );
        if ( ES_VALIDO ( p_cRuta ) )
        {
		    iRes = SisFicheroEsTemporal ( p_cRuta );
            MemLiberar ( (void **) &p_cRuta );
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

int SRutDesactivarDeSoloLectura ( SRuta * p_rutObj )
{
	int     iRes;
    char *  p_cRuta;

	if ( SRutEsDeSoloLectura ( p_rutObj ) == 1 )
	{
        p_cRuta = SRutRutaAbsolutaLit ( p_rutObj );
        if ( ES_VALIDO ( p_cRuta ) )
        {
		    iRes = SisRutaDesactivarModoSoloLectura ( p_cRuta );
            MemLiberar ( (void **) &p_cRuta );
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



