
#include "SSistema.h"

#include "SistemaConfig.h"

/*
#include <sys/system.h>
extern int _is_unixy_shell (const char *_prog);
extern int _is_dos_shell   (const char *_prog);
*/

#define _SSISTEMA_SEG_BASE_DEF			0x01ec0000
#define _SSISTEMA_SEG_LIMIT_MAX_DEF		0x0010FFFF
#define _SSISTEMA_SEG_LIMIT_MIN_DEF		0x00000000


#define _SSISTEMA_FEC_INI_UNIX			19700101 
#define _SSISTEMA_FEC_INI_IBM			19000101 
#define _SSISTEMA_FEC_INI_MAC			19040101 
#define _SSISTEMA_FEC_INI_DOS			19800101 
#define _SSISTEMA_FEC_INI_WIN32			16010101 


#define _SSISTEMA_UINT_PRUEBA_BYTE_1	0x4D
#define _SSISTEMA_UINT_PRUEBA_BYTE_2	0x7B
#define _SSISTEMA_UINT_PRUEBA_BYTE_3	0xB7
#define _SSISTEMA_UINT_PRUEBA_BYTE_4	0xD4

#define _SSISTEMA_UINT_PRUEBA			0x4D7BB7D4
#define _SSISTEMA_UINT_PRUEBA_INV		0xD4B77B4D

#define _SSISTEMA_FIC_PRUEBA			"_SSISTEMA_PRUEBA.tmp"

#define _SSISTEMA_WIN_BUFFER_SIZE		32767




static const char * _p_p_cVersionesDos [] = { "IBMPcDos",
											"CompqDOS",
											"MsoftDOS",
											"AT&T DOS",
											"ZenitDOS",
											"HP DOS",
											"GrBulDOS",
											"PBellDOS",
											"DEC DOS",
											"OlivtDOS",
											"TI DOS",
											"Toshiba",
											"NWin3Dev",
											"MSWinDev",
											"MSWinDev",
											"HP DOS",
											"RxDOS",
											"PTS-DOS",
											"GenSoft",
											"DR-DOS",
											"NovelDOS",
											"MS-DOS",
											(char *) NULL };

//static const char * _p_p_cVersionesWindows [] = {	"Windows95",
//													"Windows98",
//													"Windows98SE",
//													"WindowsMe",
//													"Windows2000",
//													"WindowsXP",
//													"WindowsXPProfessional",
//													"WindowsNT",
//													"WindowsServer2003",
//													"WindowsVista",
//													(char *) NULL };

static const char * _p_p_cVersionesLinux [] = { "GNU/Linux",
												(char *) NULL };

static const char * _p_p_cVersionesUNIX [] = { "SunOS",
												"OS/390",
												(char *) NULL };

//static const char * _p_p_cVersionesMac [] = { "MacOS",
//												(char *) NULL };

//static const char * _p_p_cVariablesEntornoDOS [] = { "%OS%", "%PATH%",  "%HOMEPATH%", "%TEMP%" };



static void SSisInicializar ( SSistema * p_sisObj );
static void SSisObtenerOrdenBytes ( SSistema * p_sisObj );
static void SSisVerificarSubprocesos ( SSistema * p_sisObj );

static int _EstaEnLista ( const char * p_cValor, const char * * p_p_cLista );



//extern int __djgpp_selector_limit;	/* Limit on CS and on DS if prot */
//extern int __djgpp_base_address;	/* Used in calculation below */


SSistema * SSisCrear ()
{
	SSistema * p_sisObj;
	
	p_sisObj = (SSistema *) MemReservar ( sizeof ( SSistema ) );
	if ( ES_VALIDO ( p_sisObj ) )
	{
		SSisInicializar ( p_sisObj );
	}
	return ( p_sisObj );
}

void SSisDestruir ( SSistema ** p_p_sisObj )
{
	SSistema * p_sisObj;
	
	if ( ES_VALIDO ( p_p_sisObj ) )
	{
		p_sisObj = *p_p_sisObj;
		if ( ES_VALIDO ( p_sisObj ) )
		{
			SCadDestruir ( &(p_sisObj->p_cadDirSistema) );
			SCadDestruir ( &(p_sisObj->p_cadDirFuentes) );
			SCadDestruir ( &(p_sisObj->p_cadDirTemporal) );
			MemLiberar ( (void **) p_p_sisObj );
		}
	}
}

int SSisTipo ( SSistema * p_sisObj )
{
	int iRes;

	if ( ES_VALIDO ( p_sisObj ) )
	{
		iRes = p_sisObj->iTipo;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SSisSistema ( SSistema * p_sisObj )
{
	int iRes;

	if ( ES_VALIDO ( p_sisObj ) )
	{
		iRes = p_sisObj->iSistema;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SSisEsDos ( SSistema * p_sisObj )
{
	int iRes;

	if ( ES_VALIDO ( p_sisObj ) )
	{
		if ( p_sisObj->iSistema == TIP_SIS_DOS )
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

int SSisEsWindows ( SSistema * p_sisObj )
{
	int iRes;

	if ( ES_VALIDO ( p_sisObj ) )
	{
		if ( p_sisObj->iSistema == TIP_SIS_WINDOWS )
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

int SSisEsPosix ( SSistema * p_sisObj )
{
	int iRes;

	if ( ES_VALIDO ( p_sisObj ) )
	{
		if ( p_sisObj->iSistema == TIP_SIS_POSIX )
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

int SSisEsMackintosh ( SSistema * p_sisObj )
{
	int iRes;

	if ( ES_VALIDO ( p_sisObj ) )
	{
		if ( p_sisObj->iSistema == TIP_SIS_MACKINTOSH )
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

/*
int SSisTamPalabraMemoria ( SSistema * p_sisObj )
{
	return ( TIP_TAM_LONG );
}

int SSisEsArquitectura64Bits ( SSistema * p_sisObj )
{
	int iRes;

	if ( TIP_TAM_LONG == 8 )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SSisEsArquitectura32Bits ( SSistema * p_sisObj )
{
	int iRes;

	if ( TIP_TAM_LONG == 4 )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}
*/

int SSisOrdenBytes ( SSistema * p_sisObj )
{
	int iRes;

	if ( ES_VALIDO ( p_sisObj ) )
	{
		iRes = p_sisObj->iOrdenBytes;
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int SSisOrdenBytesEsNormal ( SSistema * p_sisObj )
{
	int iRes;
	
	if ( ES_VALIDO ( p_sisObj ) )
	{
		if ( p_sisObj->iOrdenBytes == 0 )
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

int SSisOrdenBytesEsInvertido ( SSistema * p_sisObj )
{
	int iRes;
	
	if ( ES_VALIDO ( p_sisObj ) )
	{
		if ( p_sisObj->iOrdenBytes == 1 )
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

int SSisAdmiteSubprocesos ( SSistema * p_sisObj )
{
	int iRes;

	if ( ES_VALIDO ( p_sisObj ) )
	{
		iRes = p_sisObj->iAdmiteSubprocesos;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

long SSisFechaInicial ( SSistema * p_sisObj )
{
	long lRes;

	if ( ES_VALIDO ( p_sisObj ) )
	{
		lRes = p_sisObj->lFechaInicial;
	}
	else
	{
		lRes = 0;
	}
	return ( lRes );
}

SCadena * SSisDirSistema ( SSistema * p_sisObj )
{
	SCadena * p_cadRes;

	if ( ES_VALIDO ( p_sisObj ) )
	{
		p_cadRes = p_sisObj->p_cadDirSistema;
	}
	else
	{
		p_cadRes = NULL;
	}
	return ( p_cadRes );
}

SCadena * SSisDirFuentes ( SSistema * p_sisObj )
{
	SCadena * p_cadRes;

	if ( ES_VALIDO ( p_sisObj ) )
	{
		p_cadRes = p_sisObj->p_cadDirFuentes;
	}
	else
	{
		p_cadRes = NULL;
	}
	return ( p_cadRes );
}

SCadena * SSisDirTemporal ( SSistema * p_sisObj )
{
	SCadena * p_cadRes;

	if ( ES_VALIDO ( p_sisObj ) )
	{
		p_cadRes = p_sisObj->p_cadDirTemporal;
	}
	else
	{
		p_cadRes = NULL;
	}
	return ( p_cadRes );
}

int SSisAdmiteEjecucionDeComandos ( SSistema * p_sisObj )
{
	int iRes;

	if ( ES_VALIDO ( p_sisObj ) )
	{
		iRes = p_sisObj->iEjecComando;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SSisEjecutarComando ( SSistema * p_sisObj, const char * p_cComando )
{
	int iRes;

	if ( ES_VALIDO ( p_sisObj ) )
	{
		if ( ( p_sisObj->iEjecComando == 1 ) && ( ES_VALIDO ( p_cComando ) ) )
		{
			iRes = system ( p_cComando );
		}
		else
		{
			iRes = -1;
		}
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

int SSisEjecutarComandoExt ( SSistema * p_sisObj, const char * p_cPrograma, const char * p_cParametros )
{
	int iRes;

	if ( ES_VALIDO ( p_sisObj ) )
	{
		if ( ( p_sisObj->iEjecComando == 1 ) && ES_VALIDO ( p_cPrograma ) )
		{
			char * p_cComando = CadCrearConFormato ( "%s %s", p_cPrograma, p_cParametros );
			iRes = system( p_cComando );
			MemLiberarCadena ( &p_cComando );
		}
		else
		{
			iRes = -1;
		}
	}
	else
	{
		iRes = -1;
	}
	return ( iRes );
}

/*
int SSisEsEjecutableDOS ( SSistema * p_sisObj, const char * p_cPrograma )
{
	int iRes;

	if ( ES_VALIDO ( p_cPrograma ) )
	{
#		if ( !defined ( POSIX ) )
			if ( _is_dos_shell ( p_cPrograma ) )
			{
				iRes = 1;
			}
			else
			{
				iRes = 0;
			}
#		else
			iRes = 0;
#		endif
	}	
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SSisEsEjecutableUNIX ( SSistema * p_sisObj, const char * p_cPrograma )
{
	int iRes;

	if ( ES_VALIDO ( p_cPrograma ) )
	{
#		if ( !defined ( POSIX ) )
			if ( _is_unixy_shell ( p_cPrograma ) )
			{
				iRes = 1;
			}
			else
			{
				iRes = 0;
			}
#		else
			iRes = 0;
#		endif
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

long SSisTamPagina ( SSistema * p_sisObj )
{
	long lRes;

#		if ( !defined ( POSIX ) )
		lRes = getpagesize ();
#		else
			lRes = 0;
#		endif
	return ( lRes ); 
}

long SSisDirSegmentoCodigo ( SSistema * p_sisObj )
{
#		if ( !defined ( POSIX ) )
		//return ( DirBaseSegmentos () + _my_cs () );
		return ( _my_cs () );
#	else
		return ( 0 );
#	endif
}

long SSisDirSegmentoDatos ( SSistema * p_sisObj )
{
#		if ( !defined ( POSIX ) )
		//return ( DirBaseSegmentos () + _my_ds () );
		return ( _my_ds () );
#	else
		return ( 0 );
#	endif
}

long SSisDirSegmentoPila ( SSistema * p_sisObj )
{
#		if ( !defined ( POSIX ) )
		//return ( DirBaseSegmentos () + _my_ss () );
		return ( _my_ss () );
#	else
		return ( 0 );
#	endif
}

long SSisDirBaseSegmentos ( SSistema * p_sisObj )
{
	// Pendiente:
	return ( 0 );
	//return ( __djgpp_base_address ); // _SSISTEMA_SEG_BASE_DEF );
}

long SSisLimInfSegmentos( SSistema * p_sisObj )
{
	// Pendiente:
	return ( _SSISTEMA_SEG_LIMIT_MIN_DEF );
}

long SSisLimSupSegmentos( SSistema * p_sisObj )
{
	// Pendiente:
	return ( 0 );
	//return ( __djgpp_selector_limit ); //_SSISTEMA_SEG_LIMIT_MAX_DEF );
}

int SSisDirValida ( long lDir )
{
	int iRes;

	printf ( "%ld   %ld\n", lDir, LimSupSegmentos() );
	if ( ( lDir >= LimInfSegmentos() ) &&
		 ( lDir < LimSupSegmentos() ) )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SSisDirAbsValida ( SSistema * p_sisObj, long lDir )
{
	int iRes;

	if ( ( DirAbsDatosValida ( lDir ) == 1 ) ||
		 ( DirAbsPilaValida ( lDir ) == 1 ) ||
		 ( DirAbsCodigoValida ( lDir ) == 1 ) )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SSisDirAbsCodigoValida ( SSistema * p_sisObj, long lDir )
{
	int iRes;

	if ( ( lDir >= DirSegmentoCodigo () + LimInfSegmentos () ) &&
		 ( lDir < LimSupSegmentos() ) )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SSisDirAbsDatosValida ( SSistema * p_sisObj, long lDir )
{
	int iRes;

	if ( ( lDir >= DirSegmentoDatos () + LimInfSegmentos () ) &&
		 ( lDir < LimSupSegmentos() ) )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

int SSisDirAbsPilaValida ( SSistema * p_sisObj, long lDir )
{
	int iRes;

	if ( ( lDir >= DirSegmentoPila () + LimInfSegmentos () ) &&
		 ( lDir < LimSupSegmentos() ) )
	{
		iRes = 1;
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

long SSisMemoriaTotal ( SSistema * p_sisObj )
{
	long			lRes;
#		if ( !defined ( POSIX ) )
	lRes = 0;
		struct rlimit	rlimInfo; 

		if ( getrlimit ( RLIMIT_AS, &rlimInfo ) == 0 )
		{
			lRes = rlimInfo.rlim_cur; 
		}
		else
		{
			lRes = 0;
		}
#	else
		lRes = 0;
#	endif
	return ( lRes );
}

long SSisMemoriaUtilizada ( SSistema * p_sisObj )
{
	long			lRes;
#		if ( !defined ( POSIX ) )
		lRes = 0;
		struct rlimit	rlimInfo; 

		if ( getrlimit ( RLIMIT_AS, &rlimInfo ) == 0 )
		{
			lRes = rlimInfo.rlim_cur; 
		}
		else
		{
			lRes = 0;
		}
#	else
		lRes = 0;
#	endif
	return ( lRes );
}

long SSisMemoriaDisponible ( SSistema * p_sisObj )
{
	long			lRes;
#	if ( !defined ( POSIX ) )
		lRes = 0;
		struct rlimit	rlimInfo; 

		if ( getrlimit ( RLIMIT_AS, &rlimInfo ) == 0 )
		{
			lRes = rlimInfo.rlim_cur; 
		}
		else
		{
			lRes = 0;
		}
#	else
		lRes = 0;
#	endif
	return ( lRes );
}

long SSisMemoriaDatosTotal ( SSistema * p_sisObj )
{
	long			lRes;
#		if ( !defined ( POSIX ) )
		lRes = 0;
		struct rlimit	rlimInfo; 

		if ( getrlimit ( RLIMIT_DATA, &rlimInfo ) == 0 )
		{
			lRes = rlimInfo.rlim_cur; 
		}
		else
		{
			lRes = -1;
		}
#	else
		lRes = 0;
#	endif
	return ( lRes );
}

long SSisMemoriaDatosUtilizada ( SSistema * p_sisObj )
{
	long			lRes;
#	if ( !defined ( POSIX ) )
		struct rusage 	rusgInfo; 

		if ( getrusage ( RUSAGE_SELF, &rusgInfo ) == 0 )
		{
			lRes = rusgInfo.ru_idrss + rusgInfo.ru_ixrss; 
		}
		else
		{
			lRes = -1;
		}
#	else
		lRes = 0;
#	endif
	return ( lRes );
}

long SSisMemoriaDatosDisponible ( SSistema * p_sisObj )
{
	long lTotal;
	long lUtilizada;
	long lRes;

	lTotal = MemoriaDatosTotal ();
	lUtilizada = MemoriaDatosUtilizada ();
	if ( ( lTotal >= 0 ) && ( lUtilizada >= 0 ) )
	{
		lRes = lTotal - lUtilizada;
	}
	else
	{
		lRes = -1;
	}
	return ( lRes );
}

long SSisMemoriaPilaTotal ( SSistema * p_sisObj )
{
	long			lRes;
#	if ( !defined ( POSIX ) )
	struct rlimit	rlimInfo; 

	if ( getrlimit ( RLIMIT_STACK, &rlimInfo ) == 0 )
	{
		lRes = rlimInfo.rlim_cur; 
	}
	else
	{
		lRes = -1;
	}
#	else
		lRes = 0;
#	endif
	return ( lRes );
}

long SSisMemoriaPilaUtilizada ( SSistema * p_sisObj )
{
	long			lRes;
#	if ( !defined ( POSIX ) )
		struct rusage 	rusgInfo; 

		if ( getrusage ( RUSAGE_SELF, &rusgInfo ) == 0 )
		{
			lRes = rusgInfo.ru_isrss; 
		}
		else
		{
			lRes = -1;
		}
#	else
		lRes = 0;
#	endif
	return ( lRes );
}

long SSisMemoriaPilaDisponible ( SSistema * p_sisObj )
{
	long lTotal;
	long lUtilizada;
	long lRes;

	lTotal = MemoriaPilaTotal ();
	lUtilizada = MemoriaPilaUtilizada ();
	if ( ( lTotal >= 0 ) && ( lUtilizada >= 0 ) )
	{
		lRes = lTotal - lUtilizada;
	}
	else
	{
		lRes = -1;
	}
	return ( lRes );
}

long SSisMemoriaBloqueadaTotal ( SSistema * p_sisObj )
{
	long			lRes;
#	if ( !defined ( POSIX ) )
	struct rlimit	rlimInfo; 

	if ( getrlimit ( RLIMIT_MEMLOCK, &rlimInfo ) == 0 )
	{
		lRes = rlimInfo.rlim_cur; 
	}
	else
	{
		lRes = -1;
	}
#	else
		lRes = 0;
#	endif
	return ( lRes );
}

long SSisMemoriaBloqueadaUtilizada ( SSistema * p_sisObj )
{
	long			lRes;
#	if ( !defined ( POSIX ) )
		struct rlimit	rlimInfo; 

		if ( getrlimit ( RLIMIT_MEMLOCK, &rlimInfo ) == 0 )
		{
			lRes = rlimInfo.rlim_cur; 
		}
		else
		{
			lRes = -1;
		}
#	else
		lRes = 0;
#	endif
	return ( lRes );
}

long SSisMemoriaBloqueadaDisponible ( SSistema * p_sisObj )
{
	long lTotal;
	long lUtilizada;
	long lRes;

	lTotal = MemoriaBloqueadaTotal ();
	lUtilizada = MemoriaBloqueadaUtilizada ();
	if ( ( lTotal >= 0 ) && ( lUtilizada >= 0 ) )
	{
		lRes = lTotal - lUtilizada;
	}
	else
	{
		lRes = -1;
	}
	return ( lRes );
}

long SSisMemoriaFisica ( SSistema * p_sisObj )
{
	long			lRes;
#	if ( !defined ( POSIX ) )
	struct rlimit	rlimInfo; 

	if ( getrlimit ( RLIMIT_RSS, &rlimInfo ) == 0 )
	{
		lRes = rlimInfo.rlim_cur; 
	}
	else
	{
		lRes = -1;
	}
#	else
		lRes = 0;
#	endif
	return ( lRes );
}

long SSisDescriptoresESTotales ( SSistema * p_sisObj )
{
	long			lRes;
#	if ( !defined ( POSIX ) )
	struct rlimit	rlimInfo; 

	if ( getrlimit ( RLIMIT_NOFILE, &rlimInfo ) == 0 )
	{
		lRes = rlimInfo.rlim_cur; 
	}
	else
	{
		lRes = -1;
	}
#	else
		lRes = 0;
#	endif
	return ( lRes );
}

long SSisDescriptoresESUtilizados ( SSistema * p_sisObj )
{
	long			lRes;
#	if ( !defined ( POSIX ) )
	struct rlimit	rlimInfo; 

	if ( getrlimit ( RLIMIT_NOFILE, &rlimInfo ) == 0 )
	{
		lRes = rlimInfo.rlim_cur; 
	}
	else
	{
		lRes = -1;
	}
#	else
		lRes = 0;
#	endif
	return ( lRes );
}

long SSisDescriptoresESDisponibles ( SSistema * p_sisObj )
{
	long lTotales;
	long lUtilizados;
	long lRes;

	lTotales = DescriptoresESTotales ();
	lUtilizados = DescriptoresESUtilizados ();
	if ( ( lTotales >= 0 ) && ( lUtilizados >= 0 ) )
	{
		lRes = lTotales - lUtilizados;
	}
	else
	{
		lRes = -1;
	}
	return ( lRes );
}

long SSisMaxTamFichero ( SSistema * p_sisObj )
{
	long			lRes;
#	if ( !defined ( POSIX ) )
		struct rlimit	rlimInfo; 

		if ( getrlimit ( RLIMIT_FSIZE, &rlimInfo ) == 0 )
		{
			lRes = rlimInfo.rlim_max; 
		}
		else
		{
			lRes = -1;
		}
#	else
		lRes = 0;
#	endif
	return ( lRes );
}

long SSisMaxTiempoCPU ( SSistema * p_sisObj )
{
	long			lRes;
#	if ( !defined ( POSIX ) )
		struct rlimit	rlimInfo; 

		if ( getrlimit ( RLIMIT_SPU, &rlimInfo ) == 0 )
		{
			lRes = rlimInfo.rlim_cur; 
		}
		else
		{
			lRes = -1;
		}
#	else
		lRes = 0;
#	endif
	return ( lRes );
}

long SSisMaxNumProcesosPorUsuario ( SSistema * p_sisObj )
{
	long			lRes;
#	if ( !defined ( POSIX ) )
		struct rlimit	rlimInfo; 

		if ( getrlimit ( RLIMIT_NPROC, &rlimInfo ) == 0 )
		{
			lRes = rlimInfo.rlim_cur; 
		}
		else
		{
			lRes = -1;
		}
#	else
		lRes = 0;
#	endif
	return ( lRes );
}
*/

static void SSisInicializar ( SSistema * p_sisObj )
{
# if ( defined ( WIN ) )
	DWORD			dwVersion;
	DWORD			dwVersionMin;
	DWORD			dwVersionMay;

	p_sisObj->iTipo = TIP_SIS_WINDOWS;
	p_sisObj->iSistema = SIS_DESCONOCIDO;

	dwVersion = GetVersion();
 
	dwVersionMin = (DWORD)( LOBYTE ( LOWORD ( dwVersion ) ) );
	dwVersionMay = (DWORD)( HIBYTE ( LOWORD ( dwVersion ) ) );

	if ( dwVersionMay == 4 ) // The operating system is Windows NT 4.0, Windows Me, Windows 98, or Windows 95. 
	{
		if ( dwVersionMin == 0 ) // Windows NT 4.0, or Windows 95
		{
		}
		else if ( dwVersionMin == 10 ) // Windows 98
		{
		}
		else if ( dwVersionMin == 90 ) // Windows Me
		{
		}
		else
		{
			// ERROR
		}
	}
	else if ( dwVersionMay == 5 ) // The operating system is Windows Server 2003 R2, Windows Server 2003, Windows XP, or Windows 2000. 
	{
		if ( dwVersionMin == 1 ) // Windows XP
		{
		}
		else if ( dwVersionMin == 2 ) // Windows Server 2003 R2, Windows Server 2003, or Windows XP Professional x64 Edition.
		{
		}
		else
		{
			// ERROR
		}
	}
	else if ( dwVersionMay == 6 ) // The operating system is Windows Vista or Windows Server "Longhorn". 
	{
		if ( dwVersionMin == 0 ) // Windows Vista, Windows Server "Longhorn"
		{
		}
		else
		{
			// ERROR
		}
	}
	else
	{
		// ERROR:
	}

	p_sisObj->iEjecComando = 0;

# else
	struct utsname	utsnInfo;
	struct tm *		p_tmFecha;
	time_t			timFecha;
	int				iSisDetec;

	// Por la fecha se pueden reconocer si es DOS o UNIX, y diferentes versiones de LINUX/UNIX:
	p_sisObj->iOrdenBytes = -1;
	p_sisObj->iAdmiteSubprocesos = 0;
	iSisDetec = 0;
	p_sisObj->iSistema = SIS_DESCONOCIDO;
	p_sisObj->iTipo = TIP_SIS_DESCONOCIDO;

	timFecha = 0;
	p_tmFecha = localtime ( &timFecha );
	p_sisObj->lFechaInicial = ( 1900 + p_tmFecha->tm_year ) * 10000 + ( p_tmFecha->tm_mon + 1 ) * 100 + p_tmFecha->tm_mday;

	if ( system ( NULL ) != 0 )
	{
		p_sisObj->iEjecComando = 1;
	}
	else
	{
		p_sisObj->iEjecComando = 0;
	}

	if ( p_sisObj->lFechaInicial == _SSISTEMA_FEC_INI_MAC )
	{
		p_sisObj->iTipo = TIP_SIS_MACKINTOSH;
		p_sisObj->iSistema = SIS_DESCONOCIDO;
		iSisDetec = 1;
	}
	else if ( p_sisObj->lFechaInicial == _SSISTEMA_FEC_INI_WIN32 )
	{
		p_sisObj->iTipo = TIP_SIS_WINDOWS;
		p_sisObj->iSistema = SIS_DESCONOCIDO;
		iSisDetec = 1;
	}
	else if ( p_sisObj->lFechaInicial == _SSISTEMA_FEC_INI_DOS )
	{
		// Puede ser cualquier DOS o WIN16:
	}
	else if ( p_sisObj->lFechaInicial == _SSISTEMA_FEC_INI_IBM )
	{
		// Puede ser cualquier cosa (OS/2...) y también hay una version de MAC:
	}
	else if ( p_sisObj->lFechaInicial == _SSISTEMA_FEC_INI_UNIX )
	{
		// También puede ser LINUX, el simulador de DOS de las últminas versiones de WINDOWS
	}

	if ( iSisDetec == 0 )
	{
		if ( uname ( &utsnInfo ) != -1 )
		{
			if ( p_sisObj->lFechaInicial == _SSISTEMA_FEC_INI_UNIX )
			{
				if ( _EstaEnLista ( utsnInfo.sysname, _p_p_cVersionesDos ) == 1 )
				{
					p_sisObj->iTipo = TIP_SIS_DOS;
					p_sisObj->iSistema = SIS_DESCONOCIDO;
				}
				else
				{
					p_sisObj->iTipo = TIP_SIS_WINDOWS;
					p_sisObj->iSistema = SIS_DESCONOCIDO;
				}
			}
			else if ( p_sisObj->lFechaInicial == _SSISTEMA_FEC_INI_DOS )
			{
				if ( _EstaEnLista ( utsnInfo.sysname, _p_p_cVersionesDos ) == 1 )
				{
					p_sisObj->iTipo = TIP_SIS_DOS;
					p_sisObj->iSistema = SIS_DESCONOCIDO;
				}
				else if ( _EstaEnLista ( utsnInfo.sysname, _p_p_cVersionesLinux ) == 1 )
				{
					p_sisObj->iTipo = TIP_SIS_POSIX;
					p_sisObj->iSistema = SIS_DESCONOCIDO;
				}
				else
				{
					p_sisObj->iTipo = TIP_SIS_POSIX;
					p_sisObj->iSistema = SIS_DESCONOCIDO;
				}
			}
			else
			{
				if ( _EstaEnLista ( utsnInfo.sysname, _p_p_cVersionesLinux ) == 1 )
				{
					p_sisObj->iTipo = TIP_SIS_POSIX;
					p_sisObj->iSistema = SIS_DESCONOCIDO ;
				}
				else if ( _EstaEnLista ( utsnInfo.sysname, _p_p_cVersionesUNIX ) == 1 )
				{
					p_sisObj->iTipo = TIP_SIS_POSIX;
					p_sisObj->iSistema = SIS_DESCONOCIDO;
				}
			}
		}
	}
# endif

# if ( defined ( WIN ) )
	TCHAR  p_tcBuffer [ SIS_MAX_TAM_PATH + 1 ];

	p_sisObj->p_cadDirSistema = NULL;
	p_sisObj->p_cadDirFuentes = NULL;
	p_sisObj->p_cadDirTemporal = NULL;

	if ( GetSystemDirectory ( p_tcBuffer, SIS_MAX_TAM_PATH + 1 ) > 0 )
	{
		p_sisObj->p_cadDirSistema = SCadGenerar ( p_tcBuffer );
	}

# endif

	SSisObtenerOrdenBytes ( p_sisObj );
	SSisVerificarSubprocesos ( p_sisObj );
}

static void SSisObtenerOrdenBytes ( SSistema * p_sisObj )
{
	FILE *			p_fPrueba;
	unsigned int	uiValor;
	unsigned char	ucValor;

    uiValor = (unsigned int) _SSISTEMA_UINT_PRUEBA;
	p_fPrueba = fopen ( _SSISTEMA_FIC_PRUEBA, "w+" );
	if ( ES_VALIDO ( p_fPrueba ) )
	{
		ucValor = _SSISTEMA_UINT_PRUEBA_BYTE_4;
		fwrite ( &ucValor, 1, 1, p_fPrueba );
		ucValor = _SSISTEMA_UINT_PRUEBA_BYTE_3;
		fwrite ( &ucValor, 1, 1, p_fPrueba );
		ucValor = _SSISTEMA_UINT_PRUEBA_BYTE_2;
		fwrite ( &ucValor, 1, 1, p_fPrueba );
		ucValor = _SSISTEMA_UINT_PRUEBA_BYTE_1;
		fwrite ( &ucValor, 1, 1, p_fPrueba );
		//uiValor = _SSISTEMA_UINT_PRUEBA;
		//fwrite ( &uiValor, 4, 4, p_fPrueba );
		fclose ( p_fPrueba );

		p_fPrueba = fopen ( _SSISTEMA_FIC_PRUEBA, "r" );
		if ( ES_VALIDO ( p_fPrueba ) )
		{
			uiValor = 0;
			fread ( &uiValor, sizeof ( unsigned int ), 1, p_fPrueba );
			if ( uiValor == _SSISTEMA_UINT_PRUEBA )
			{
				p_sisObj->iOrdenBytes = 0;
			}
			else if ( uiValor == _SSISTEMA_UINT_PRUEBA_INV )
			{
				p_sisObj->iOrdenBytes = 1;
			}
		}
		fclose ( p_fPrueba );
		remove ( _SSISTEMA_FIC_PRUEBA );
	}
}

static void SSisVerificarSubprocesos ( SSistema * p_sisObj )
{
# if ( defined ( WIN ) )
	// No existe algo parecido a un fork, pero suponemos que funciona la creación de subprocesos:
	p_sisObj->iAdmiteSubprocesos = 1;
# else
    pid_t	pidProc;

	p_sisObj->iAdmiteSubprocesos = 0;
	pidProc = fork ();
	if ( pidProc > 0 ) 
	{
		p_sisObj->iAdmiteSubprocesos = 1;
	}
	else if ( pidProc == 0 )
	{
		exit ( 0 );
	}
# endif
}


static int _EstaEnLista ( const char * p_cValor, const char * * p_p_cLista )
{
	int				iRes;
	int				iElem;
	const char *	p_cElem;

	if ( ES_VALIDO ( p_cValor ) && ES_VALIDO ( p_p_cLista ) )
	{
		iElem = 0;
		p_cElem = p_p_cLista [ 0 ];
		iRes = 0;
		while ( ES_VALIDO ( p_cElem ) && ( iRes == 0 ) )
		{
			if ( CadCompararSinDistinguirTipoLetra ( p_cValor, p_cElem ) == COMP_IGUAL )
			{
				iRes = 1;
			}
			iElem = iElem + 1;
			p_cElem = p_p_cLista [ iElem ];
		}
	}
	else
	{
		iRes = 0;
	}
	return ( iRes );
}

/*
Public Structure MEMORYSTATUS
    Public dwLength As UInt32
    Public dwMemoryLoad As UInt32
    Public dwTotalPhys As UInt32
    Public dwAvailPhys As UInt32
    Public dwTotalPageFile As UInt32
    Public dwAvailPageFile As UInt32
    Public dwTotalVirtual As UInt32
    Public dwAvailVirtual As UInt32
End Structure 

Public Declare Function GlobalMemoryStatus Lib "CoreDll.Dll" _
    (ByRef ms As MEMORYSTATUS) As Integer

Public Declare Function GetSystemMemoryDivision Lib "CoreDll.Dll" _
    (ByRef lpdwStorePages As UInt32, _
    ByRef ldpwRamPages As UInt32, _
    ByRef ldpwPageSize As UInt32) As Integer
    
Public Shared Sub ShowMemory()
    Dim storePages As UInt32
    Dim ramPages As UInt32
    Dim pageSize As UInt32
    Dim res As Integer = _
        GetSystemMemoryDivision(storePages, ramPages, pageSize)


Int 31H Function 050BH 

Get Memory Information 
Returns information about available physical and virtual memory. Since DPMI clients will often run in multitasking environments, some of information related to shared resources returned by this function should only be considered as advisory.
Call With

AX = 050BH
ES:(E)DI = selector:offset of 128-byte buffer

Returns

if function successful
Carry flag = clear (this function always succeeds in DPMI 1.0)
and the buffer pointed to by ES:(E)DI is filled in with the following information: 

Offset Length Contents 
00H 4 Total allocated bytes of physical memory controlled by DPMI host 
04H 4 Total allocated bytes of virtual memory controlled by DPMI host 
08H 4 Total available bytes of virtual memory controlled by DPMI host 
0CH 4 Total allocated bytes of virtual memory for this virtual machine 
10H 4 Total available bytes of virtual memory for this virtual machine 
14H 4 Total allocated bytes of virtual memory for this client 
18H 4 Total available bytes of virtual memory for this client 
1CH 4 Total locked bytes of memory for this client 
20H 4 Maximum locked bytes of memory for this client 
24H 4 Highest linear address available to this client 
28H 4 Size in bytes of largest available free memory block 
2CH 4 Size of minimum allocation unit in bytes 
30H 4 Size of the allocation alignment unit in bytes 
34H 4CH Reserved, currently zero 

if function unsuccessful
Carry flag = set (this function always fails in DPMI 0.9)

Notes
DPMI 1.0 clients should use this function in preference to Int 31H Function 0500H.

The "total available bytes" field of the data structure pointed by ES:(E)DI means the total bytes minus all of the allocated bytes.

*/



/*
#include <unistd.h>

long sysconf(int name);

Variable
 Value of Name
 
{AIO_LISTIO_MAX}
 _SC_AIO_LISTIO_MAX
 
{AIO_MAX}
 _SC_AIO_MAX
 
{AIO_PRIO_DELTA_MAX}
 _SC_AIO_PRIO_DELTA_MAX
 
{ARG_MAX}
 _SC_ARG_MAX
 
{ATEXIT_MAX}
 _SC_ATEXIT_MAX
 
{BC_BASE_MAX}
 _SC_BC_BASE_MAX
 
{BC_DIM_MAX}
 _SC_BC_DIM_MAX
 
{BC_SCALE_MAX}
 _SC_BC_SCALE_MAX
 
{BC_STRING_MAX}
 _SC_BC_STRING_MAX
 
{CHILD_MAX}
 _SC_SHILD_MAX
 
Clock ticks/second
 _SC_SLK_TCK
 
{COLL_WEIGHTS_MAX}
 _SC_SOLL_WEIGHTS_MAX
 
{DELAYTIMER_MAX}
 _SC_DELAYTIMER_MAX
 
{EXPR_NEST_MAX}
 _SC_EXPR_NEST_MAX
 
{HOST_NAME_MAX}
 _SC_HOST_NAME_MAX
 
{IOV_MAX}
 _SC_IOV_MAX
 
{LINE_MAX}
 _SC_LINE_MAX
 
{LOGIN_NAME_MAX}
 _SC_LOGIN_NAME_MAX
 
{NGROUPS_MAX}
 _SC_NGROUPS_MAX
 
Maximum size of getgrgid_r() and
 _SC_GETGR_R_SIZE_MAX
 
getgrnam_r() data buffers
  
 
Maximum size of getpwuid_r() and
 _SC_GETPW_R_SIZE_MAX
 
getpwnam_r() data buffers
  
 
{MQ_OPEN_MAX}
 _SC_MQ_OPEN_MAX
 
{MQ_PRIO_MAX}
 _SC_MQ_PRIO_MAX
 
{OPEN_MAX}
 _SC_OPEN_MAX
 
_POSIX_ADVISORY_INFO
 _SC_ADVISORY_INFO
 
_POSIX_BARRIERS
 _SC_BARRIERS
 
_POSIX_ASYNCHRONOUS_IO
 _SC_ASYNCHRONOUS_IO
 
_POSIX_SLOCK_SELECTION
 _SC_SLOCK_SELECTION
 
_POSIX_SPUTIME
 _SC_SPUTIME
 
_POSIX_FSYNC
 _SC_FSYNC
 
_POSIX_IPV6
 _SC_IPV6
 
_POSIX_JOB_SONTROL
 _SC_JOB_SONTROL
 
_POSIX_MAPPED_FILES
 _SC_MAPPED_FILES
 
_POSIX_MEMLOCK
 _SC_MEMLOCK
 
_POSIX_MEMLOCK_RANGE
 _SC_MEMLOCK_RANGE
 
_POSIX_MEMORY_PROTECTION
 _SC_MEMORY_PROTECTION
 
_POSIX_MESSAGE_PASSING
 _SC_MESSAGE_PASSING
 
_POSIX_MONOTONIC_SLOCK
 _SC_MONOTONIC_SLOCK
 
_POSIX_PRIORITIZED_IO
 _SC_PRIORITIZED_IO
 
_POSIX_PRIORITY_SCHEDULING
 _SC_PRIORITY_SCHEDULING
 
_POSIX_RAW_SOCKETS
 _SC_RAW_SOCKETS
 
_POSIX_READER_WRITER_LOCKS
 _SC_READER_WRITER_LOCKS
 
_POSIX_REALTIME_SIGNALS
 _SC_REALTIME_SIGNALS
 
_POSIX_REGEXP
 _SC_REGEXP
 
_POSIX_SAVED_IDS
 _SC_SAVED_IDS
 
_POSIX_SEMAPHORES
 _SC_SEMAPHORES
 
_POSIX_SHARED_MEMORY_OBJECTS
 _SC_SHARED_MEMORY_OBJECTS
 
_POSIX_SHELL
 _SC_SHELL
 
_POSIX_SPAWN
 _SC_SPAWN
 
_POSIX_SPIN_LOCKS
 _SC_SPIN_LOCKS
 
_POSIX_SPORADIC_SERVER
 _SC_SPORADIC_SERVER
 
_POSIX_SS_REPL_MAX
 _SC_SS_REPL_MAX
 
_POSIX_SYNCHRONIZED_IO
 _SC_SYNCHRONIZED_IO
 
_POSIX_THREAD_ATTR_STACKADDR
 _SC_THREAD_ATTR_STACKADDR
 
_POSIX_THREAD_ATTR_STACKSIZE
 _SC_THREAD_ATTR_STACKSIZE
 
_POSIX_THREAD_SPUTIME
 _SC_THREAD_SPUTIME
 
_POSIX_THREAD_PRIO_INHERIT
 _SC_THREAD_PRIO_INHERIT
 
_POSIX_THREAD_PRIO_PROTECT
 _SC_THREAD_PRIO_PROTECT
 
_POSIX_THREAD_PRIORITY_SCHEDULING
 _SC_THREAD_PRIORITY_SCHEDULING
 
_POSIX_THREAD_PROCESS_SHARED
 _SC_THREAD_PROCESS_SHARED
 
_POSIX_THREAD_SAFE_FUNCTIONS
 _SC_THREAD_SAFE_FUNCTIONS
 
_POSIX_THREAD_SPORADIC_SERVER
 _SC_THREAD_SPORADIC_SERVER
 
_POSIX_THREADS
 _SC_THREADS
 
_POSIX_TIMEOUTS
 _SC_TIMEOUTS
 
_POSIX_TIMERS
 _SC_TIMERS
 
_POSIX_TRACE
 _SC_TRACE
 
_POSIX_TRACE_EVENT_FILTER
 _SC_TRACE_EVENT_FILTER
 
_POSIX_TRACE_EVENT_NAME_MAX
 _SC_TRACE_EVENT_NAME_MAX
 
_POSIX_TRACE_INHERIT
 _SC_TRACE_INHERIT
 
_POSIX_TRACE_LOG
 _SC_TRACE_LOG
 
_POSIX_TRACE_NAME_MAX
 _SC_TRACE_NAME_MAX
 
_POSIX_TRACE_SYS_MAX
 _SC_TRACE_SYS_MAX
 
_POSIX_TRACE_USER_EVENT_MAX
 _SC_TRACE_USER_EVENT_MAX
 
_POSIX_TYPED_MEMORY_OBJECTS
 _SC_TYPED_MEMORY_OBJECTS
 
_POSIX_VERSION
 _SC_VERSION
 
_POSIX_V6_ILP32_OFF32
 _SC_V6_ILP32_OFF32
 
_POSIX_V6_ILP32_OFFBIG
 _SC_V6_ILP32_OFFBIG
 
_POSIX_V6_LP64_OFF64
 _SC_V6_LP64_OFF64
 
_POSIX_V6_LPBIG_OFFBIG
 _SC_V6_LPBIG_OFFBIG
 
_POSIX2_S_BIND
 _SC_2_S_BIND
 
_POSIX2_S_DEV
 _SC_2_S_DEV
 
_POSIX2_SHAR_TERM
 _SC_2_SHAR_TERM
 
_POSIX2_FORT_DEV
 _SC_2_FORT_DEV
 
_POSIX2_FORT_RUN
 _SC_2_FORT_RUN
 
_POSIX2_LOCALEDEF
 _SC_2_LOCALEDEF
 
_POSIX2_PBS
 _SC_2_PBS
 
_POSIX2_PBS_ACCOUNTING
 _SC_2_PBS_ACCOUNTING
 
_POSIX2_PBS_SHECKPOINT
 _SC_2_PBS_SHECKPOINT
 
_POSIX2_PBS_LOCATE
 _SC_2_PBS_LOCATE
 
_POSIX2_PBS_MESSAGE
 _SC_2_PBS_MESSAGE
 
_POSIX2_PBS_TRACK
 _SC_2_PBS_TRACK
 
_POSIX2_SW_DEV
 _SC_2_SW_DEV
 
_POSIX2_UPE
 _SC_2_UPE
 
_POSIX2_VERSION
 _SC_2_VERSION
 
{PAGE_SIZE}
 _SC_PAGE_SIZE
 
{PAGESIZE}
 _SC_PAGESIZE
 
{PTHREAD_DESTRUCTOR_ITERATIONS}
 _SC_THREAD_DESTRUCTOR_ITERATIONS
 
{PTHREAD_KEYS_MAX}
 _SC_THREAD_KEYS_MAX
 
{PTHREAD_STACK_MIN}
 _SC_THREAD_STACK_MIN
 
{PTHREAD_THREADS_MAX}
 _SC_THREAD_THREADS_MAX
 
{RE_DUP_MAX}
 _SC_RE_DUP_MAX
 
{RTSIG_MAX}
 _SC_RTSIG_MAX
 
{SEM_NSEMS_MAX}
 _SC_SEM_NSEMS_MAX
 
{SEM_VALUE_MAX}
 _SC_SEM_VALUE_MAX
 
{SIGQUEUE_MAX}
 _SC_SIGQUEUE_MAX
 
{STREAM_MAX}
 _SC_STREAM_MAX
 
{SYMLOOP_MAX}
 _SC_SYMLOOP_MAX
 
{TIMER_MAX}
 _SC_TIMER_MAX
 
{TTY_NAME_MAX}
 _SC_TTY_NAME_MAX
 
{TZNAME_MAX}
 _SC_TZNAME_MAX
 
_XBS5_ILP32_OFF32 (LEGACY)
 _SC_XBS5_ILP32_OFF32 (LEGACY)
 
_XBS5_ILP32_OFFBIG (LEGACY)
 _SC_XBS5_ILP32_OFFBIG (LEGACY)
 
_XBS5_LP64_OFF64 (LEGACY)
 _SC_XBS5_LP64_OFF64 (LEGACY)
 
_XBS5_LPBIG_OFFBIG (LEGACY)
 _SC_XBS5_LPBIG_OFFBIG (LEGACY)
 
_XOPEN_SRYPT
 _SC_XOPEN_SRYPT
 
_XOPEN_ENH_I18N
 _SC_XOPEN_ENH_I18N
 
_XOPEN_LEGACY
 _SC_XOPEN_LEGACY
 
_XOPEN_REALTIME
 _SC_XOPEN_REALTIME
 
_XOPEN_REALTIME_THREADS
 _SC_XOPEN_REALTIME_THREADS
 
_XOPEN_SHM
 _SC_XOPEN_SHM
 
_XOPEN_STREAMS
 _SC_XOPEN_STREAMS
 
_XOPEN_UNIX
 _SC_XOPEN_UNIX
 
_XOPEN_VERSION
 _SC_XOPEN_VERSION
 

RETURN VALUE
If name is an invalid value, sysconf() shall return -1 and set errno to indicate the error. If the variable corresponding to name has no limit, sysconf() shall return -1 without changing the value of errno. Note that indefinite limits do not imply infinite limits; see <limits.h>.

Otherwise, sysconf() shall return the current variable value on the system. The value returned shall not be more restrictive than the corresponding value described to the application when it was compiled with the implementation's <limits.h> or <unistd.h>. The value shall not change during the lifetime of the calling process, [XSI]   except that sysconf(_SC_OPEN_MAX) may return different values before and after a call to setrlimit() which changes the RLIMIT_NOFILE soft limit. 

*/

/*
WindowsVersion::WindowsVersion()
{
    m_info.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
    GetVersionEx(&m_info);
}

WindowsVersion::~WindowsVersion()
{

}

bool WindowsVersion::isWindows95()
    {
    if (m_info.dwPlatformId != VER_PLATFORM_WIN32_WINDOWS)
        {
        return false;
        }
    return m_info.dwMinorVersion == 0;
    }

bool WindowsVersion::isWindows98()
    {
    if (m_info.dwPlatformId != VER_PLATFORM_WIN32_WINDOWS)
        {
        return false;
        }
    return m_info.dwMinorVersion == 10;
    }

bool WindowsVersion::isWindowsME()
    {
    if (m_info.dwPlatformId != VER_PLATFORM_WIN32_WINDOWS)
        {
        return false;
        }
    return m_info.dwMinorVersion == 90;
    }

bool WindowsVersion::isWindowsXP()
    {
    if (m_info.dwPlatformId != VER_PLATFORM_WIN32_NT)
        {
        return false;
        }
    return m_info.dwMajorVersion == 5 && m_info.dwMinorVersion >= 1;
    }

bool WindowsVersion::isWindows2000()
    {
    if (m_info.dwPlatformId != VER_PLATFORM_WIN32_NT)
        {
        return false;
        }
    return m_info.dwMajorVersion == 5 && m_info.dwMinorVersion == 0;
    }

bool WindowsVersion::isWindowsNT4()
    {
    if (m_info.dwPlatformId != VER_PLATFORM_WIN32_NT)
        {
        return false;
        }
    return m_info.dwMajorVersion == 4;
    }

*/


