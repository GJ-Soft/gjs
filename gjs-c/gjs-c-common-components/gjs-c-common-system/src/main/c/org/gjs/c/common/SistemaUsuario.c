
#include "SistemaUsuario.h"     

#include "SistemaConfig.h"


#define REAL_ID             0           
#define EFFECTIVE_ID        1




/* Las consultas de usuarios y grupos van por las variantes _r: escriben en un
   buffer del llamante, no en uno estatico que comparten todos los hilos. El
   buffer empieza con el tamano que recomienda el sistema ( 16 KB si no lo dice )
   y se dobla mientras la consulta conteste ERANGE, hasta 1 MB. */
#if ( defined ( POSIX ) )

#define SIS_USR_TAM_BUFFER_DEF		16384
#define SIS_USR_TAM_BUFFER_MAX		1048576

/* Una consulta: busca p_vClave con el buffer dado y deja el resultado en
   p_vSalida. Devuelve 0, ERANGE si el buffer no basta, u otro errno. */
typedef int ( * SIS_USR_CONSULTA ) ( const void * p_vClave, char * p_cBuffer, size_t tTam, void * p_vSalida );

static int _SisUsrConsultar ( SIS_USR_CONSULTA fConsulta, int iSysconf, const void * p_vClave, void * p_vSalida )
{
	long	lTam;
	char *	p_cBuffer;
	int		iErr;

	lTam = sysconf ( iSysconf );
	if ( lTam <= 0 )
	{
		lTam = SIS_USR_TAM_BUFFER_DEF;
	}
	iErr = ERANGE;
	while ( ( iErr == ERANGE ) && ( lTam <= SIS_USR_TAM_BUFFER_MAX ) )
	{
		p_cBuffer = (char *) MemReservar ( (int) lTam );
		if ( ES_VALIDO ( p_cBuffer ) )
		{
			iErr = fConsulta ( p_vClave, p_cBuffer, (size_t) lTam, p_vSalida );
			MemLiberar ( (void **) &p_cBuffer );
		}
		else
		{
			iErr = ENOMEM;
		}
		lTam = lTam * 2;
	}
	return ( iErr );
}

static int _SisUsrNombreDeUid ( const void * p_vClave, char * p_cBuffer, size_t tTam, void * p_vSalida )
{
	struct passwd	pwdDatos;
	struct passwd *	p_pwdRes = NULL;
	int				iErr;

	iErr = getpwuid_r ( *(const uid_t *) p_vClave, &pwdDatos, p_cBuffer, tTam, &p_pwdRes );
	if ( ( iErr == 0 ) && ( p_pwdRes != NULL ) )
	{
		*(char **) p_vSalida = CadDuplicar ( p_pwdRes->pw_name );
	}
	return ( iErr );
}

static int _SisUsrNombreDeGid ( const void * p_vClave, char * p_cBuffer, size_t tTam, void * p_vSalida )
{
	struct group	grpDatos;
	struct group *	p_grpRes = NULL;
	int				iErr;

	iErr = getgrgid_r ( *(const gid_t *) p_vClave, &grpDatos, p_cBuffer, tTam, &p_grpRes );
	if ( ( iErr == 0 ) && ( p_grpRes != NULL ) )
	{
		*(char **) p_vSalida = CadDuplicar ( p_grpRes->gr_name );
	}
	return ( iErr );
}

/* p_vSalida apunta a un uid_t; solo se escribe si el usuario existe. */
static int _SisUsrUidDeNombre ( const void * p_vClave, char * p_cBuffer, size_t tTam, void * p_vSalida )
{
	struct passwd	pwdDatos;
	struct passwd *	p_pwdRes = NULL;
	int				iErr;

	iErr = getpwnam_r ( (const char *) p_vClave, &pwdDatos, p_cBuffer, tTam, &p_pwdRes );
	if ( iErr == 0 )
	{
		if ( p_pwdRes != NULL )
		{
			*(uid_t *) p_vSalida = p_pwdRes->pw_uid;
		}
		else
		{
			iErr = ENOENT;
		}
	}
	return ( iErr );
}

/* p_vSalida apunta a un gid_t; solo se escribe si el grupo existe. */
static int _SisUsrGidDeNombre ( const void * p_vClave, char * p_cBuffer, size_t tTam, void * p_vSalida )
{
	struct group	grpDatos;
	struct group *	p_grpRes = NULL;
	int				iErr;

	iErr = getgrnam_r ( (const char *) p_vClave, &grpDatos, p_cBuffer, tTam, &p_grpRes );
	if ( iErr == 0 )
	{
		if ( p_grpRes != NULL )
		{
			*(gid_t *) p_vSalida = p_grpRes->gr_gid;
		}
		else
		{
			iErr = ENOENT;
		}
	}
	return ( iErr );
}

#endif


/* El nombre es siempre una copia que libera el llamante ( MemLiberar ), en
   todas las plataformas. Antes se devolvia un puntero a una cache static de
   UID_CACHE_MAX entradas que, al llenarse, liberaba la mas antigua: el nombre
   que hubiera guardado el llamante quedaba liberado en cuanto se consultaban
   diez uid distintos mas, y entre hilos la cache se corrompia. En WIN eran
   literales, que no se podian liberar. */
char * SisUsrObtenerNombre ( unsigned int uiId )
{
	char *	p_cRes = NULL;
#   if ( defined ( POSIX ) )
	uid_t	uidValor = (uid_t) uiId;

	_SisUsrConsultar ( _SisUsrNombreDeUid, _SC_GETPW_R_SIZE_MAX, &uidValor, &p_cRes );
	if ( p_cRes == NULL )
	{
		p_cRes = CadDuplicar ( "<none>" );
	}
#   else
	if ( uiId == 0 )
	{
		p_cRes = CadDuplicar ( "user" );
	}
	else
	{
		p_cRes = CadDuplicar ( "<none>" );
	}
#   endif
	return ( p_cRes );
}



char * SisUsrObtenerNombreGrupo ( unsigned int uiIdGrupo )
{
	char *	p_cRes = NULL;
#   if ( defined ( POSIX ) )
	gid_t	gidValor = (gid_t) uiIdGrupo;

	_SisUsrConsultar ( _SisUsrNombreDeGid, _SC_GETGR_R_SIZE_MAX, &gidValor, &p_cRes );
	if ( p_cRes == NULL )
	{
		p_cRes = CadDuplicar ( "<none>" );
	}
#   else
	if ( uiIdGrupo == 0 )
	{
		p_cRes = CadDuplicar ( "group" );
	}
	else
	{
		p_cRes = CadDuplicar ( "<none>" );
	}
#   endif
	return ( p_cRes );
}


int SisUsrDesactivarRoot ()
{
#if (defined (POSIX))
#   if (defined (__UTYPE_HPUX) || defined (__UTYPE_BEOS))
    return (setuid (SisUsrObtenerUsuario (REAL_ID)));
#   elif (defined (__OS2__))            /*  OS/2 only supports one UID       */
    return ( 0 );
#   elif (defined (__VMS__))            /*  No setuid under OpenVMS          */
    return ( 0 );
#   else
    return (seteuid (SisUsrObtenerUsuario (REAL_ID)));
#   endif
#else
    return ( 0 );
#endif
}


int SisUsrActivarRoot ()
{
#if (defined (POSIX))
#   if (defined (__UTYPE_HPUX) || defined (__UTYPE_BEOS))
    return (setuid (SisUsrObtenerUsuario (EFFECTIVE_ID)));
#   elif (defined (__OS2__))            /*  OS/2 only supports one UID       */
    return ( 0 );
#   elif (defined (__VMS__))            /*  No setuid under OpenVMS          */
    return ( 0 );
#   else
    return (seteuid (SisUsrObtenerUsuario (EFFECTIVE_ID)));
#   endif
#else
    return ( 0 );
#endif
}



unsigned int SisUsrObtenerUsuario ( int type )
{
#if (defined (POSIX) )
    static int
        ruid = -1,
        euid = -1;

    if (ruid == -1)
        ruid = getuid ();
    if (euid == -1)
#   if (defined (__UTYPE_HPUX) || defined (__UTYPE_BEOS))
        euid = getuid ();
#   else
        euid = geteuid ();
#   endif

    if (type == REAL_ID)
        return (ruid);
    else
    if (type == EFFECTIVE_ID)
        return (euid);
    else
        return (-1);
#else
	return (-1);
#endif
}



int SisUsrDesactivarGrupoRoot ()
{
#if (defined (POSIX))
#   if (defined (__UTYPE_HPUX) || defined (__UTYPE_BEOS))
    return (setgid (getgid ()));
#   elif (defined (__OS2__))            /*  OS/2 only supports one UID       */
    return ( 0 );
#   elif (defined (__VMS__))            /*  No setgid under OpenVMS          */
    return ( 0 );
#   else
    /* Directamente con el gid: buscar su grupo para sacar de el el mismo gid
       era una vuelta de mas, y con getgrgid, no reentrante. */
    return ( setegid ( (gid_t) SisUsrObtenerGrupo ( REAL_ID ) ) );
#   endif
#else
    return ( 0 );
#endif
}

int SisUsrActivarGrupoRoot ()
{
#if (defined (POSIX))
#   if (defined (__UTYPE_HPUX) || defined (__UTYPE_BEOS))
    return (setgid (getgid ()));
#   elif (defined (__OS2__))            /*  OS/2 only supports one UID       */
    return ( 0 );
#   elif (defined (__VMS__))            /*  No setgid under OpenVMS          */
    return ( 0 );
#   else
    return ( setegid ( (gid_t) SisUsrObtenerGrupo ( EFFECTIVE_ID ) ) );
#   endif
#else
    return ( 0 );
#endif
}



unsigned int SisUsrObtenerGrupo ( int type )
{
#if (defined (POSIX) )
    static int
        rgid = -1,
        egid = -1;

    if (rgid == -1)
        rgid = getgid ();
    if (egid == -1)
#   if (defined (__UTYPE_HPUX) || defined (__UTYPE_BEOS))
        egid = getgid ();
#   else
        egid = getegid ();
#   endif

    if (type == REAL_ID)
        return (rgid);
    else
    if (type == EFFECTIVE_ID)
        return (egid);
    else
        return ( 0 );
#else
	return ( 0 );
#endif
}


int SisUsrEstablecerUsuario ( const char *p_cUsuario, const char *p_cGrupo )
{
#if (defined (POSIX))
    uid_t	uidValor;
    gid_t	gidValor;

#   if (defined (__VMS__))
    return ( 0 );
#   else
    if (p_cGrupo && *p_cGrupo)
      {
        if ( _SisUsrConsultar ( _SisUsrGidDeNombre, _SC_GETGR_R_SIZE_MAX, p_cGrupo, &gidValor ) != 0 )
            return (-1);
        else
        if (setgid (gidValor) == -1)
            return (-2);
      }
    if ( _SisUsrConsultar ( _SisUsrUidDeNombre, _SC_GETPW_R_SIZE_MAX, p_cUsuario, &uidValor ) != 0 )
        return (-1);
    else
    if (setuid (uidValor) == -1)
        return (-2);
#   endif
#endif
    return ( 0 );
}

char * SisUsrObtenerUsuarioLogin ()
{
#if (defined (WIN))
#   if (defined (WIN32))
    /* Local, no static: el buffer compartido entre llamadas no servia de nada,
       porque se devuelve una copia, y entre hilos se pisaba. */
    DWORD user_name_max = 255;
    char  user_name [256];

    if ( !GetUserName (user_name, &user_name_max) )
	{
        strncpy (user_name, "unknown", sizeof (user_name));
	}
    return ( CadDuplicar ( user_name ) );
#   else
    return ( CadDuplicar ( "none" ) );
#   endif
#else
    /* getlogin_r en lugar de getlogin, que devuelve un buffer estatico. Si no
       hay usuario de sesion ( un servicio, un proceso sin terminal ) devuelve
       NULL, como antes. */
    char *	p_cRes = NULL;
    long	lTam = sysconf ( _SC_LOGIN_NAME_MAX );
    char *	p_cBuffer;

    if ( lTam <= 0 )
    {
        lTam = 256;
    }
    p_cBuffer = (char *) MemReservar ( (int) lTam + 1 );
    if ( ES_VALIDO ( p_cBuffer ) )
    {
        if ( getlogin_r ( p_cBuffer, (size_t) lTam + 1 ) == 0 )
        {
            p_cRes = CadDuplicar ( p_cBuffer );
        }
        MemLiberar ( (void **) &p_cBuffer );
    }
    return ( p_cRes );
#endif
}
