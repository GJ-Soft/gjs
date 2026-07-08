
#ifndef _ORG_GJS_C_CC_SSISTEMA_H
#define _ORG_GJS_C_CC_SSISTEMA_H






#include <Precompilacion.h>

#include <SCadena.h>
#include <TiposSistema.h>



//extern int _is_unixy_shell (const char *_prog);
//extern int _is_dos_shell   (const char *_prog);



//PENDIENTE: Falta terminar de adaptar de CPP

typedef struct  
{
	int	iTipo;
	int	iSistema;
	int iEjecComando;
	int	iOrdenBytes;
	int	iAdmiteSubprocesos;

	long lFechaInicial;

	SCadena * p_cadDirSistema;
	SCadena * p_cadDirFuentes;
	SCadena * p_cadDirTemporal;
	
} SSistema;


SSistema * SSisCrear ();

void SSisDestruir ( SSistema ** p_p_sisObj );

int SSisTipo ( SSistema * p_sisObj );
int SSisSistema ( SSistema * p_sisObj );

int SSisEsDos ( SSistema * p_sisObj );
int SSisEsWindows ( SSistema * p_sisObj );
int SSisEsPosix ( SSistema * p_sisObj );
int SSisEsMackintosh ( SSistema * p_sisObj );

/*
PENDIENTE
int SSisTamPalabraMemoria ( SSistema * p_sisObj );
int SSisEsArquitectura64Bits ( SSistema * p_sisObj );
int SSisEsArquitectura32Bits ( SSistema * p_sisObj );
*/

int SSisOrdenBytes ( SSistema * p_sisObj );
int SSisOrdenBytesEsNormal ( SSistema * p_sisObj );
int SSisOrdenBytesEsInvertido ( SSistema * p_sisObj );

int SSisAdmiteSubprocesos ( SSistema * p_sisObj );

long SSisFechaInicial ( SSistema * p_sisObj );

SCadena * SSisDirSistema ( SSistema * p_sisObj );
SCadena * SSisDirFuentes ( SSistema * p_sisObj );
SCadena * SSisDirTemporal ( SSistema * p_sisObj );

int SSisAdmiteEjecucionDeComandos ( SSistema * p_sisObj );
int SSisEjecutarComando ( SSistema * p_sisObj, const char * p_cComando );
int SSisEjecutarComandoExt ( SSistema * p_sisObj, const char * p_cPrograma, const char * p_cParametros );

/*
int SSisEsEjecutableDOS ( SSistema * p_sisObj, const char * p_cPrograma );
int SSisEsEjecutableUNIX ( SSistema * p_sisObj, const char * p_cPrograma );

long SSisTamPagina ( SSistema * p_sisObj );

long SSisDirSegmentoCodigo ( SSistema * p_sisObj );
long SSisDirSegmentoDatos ( SSistema * p_sisObj );
long SSisDirSegmentoPila ( SSistema * p_sisObj );

long SSisDirBaseSegmentos ( SSistema * p_sisObj );
long SSisLimInfSegmentos ( SSistema * p_sisObj );
long SSisLimSupSegmentos ( SSistema * p_sisObj );

int SSisDirValida ( SSistema * p_sisObj, long lDir );
int SSisDirAbsValida ( SSistema * p_sisObj, long lDir );
int SSisDirAbsCodigoValida ( SSistema * p_sisObj, long lDir );
int SSisDirAbsDatosValida ( SSistema * p_sisObj, long lDir );
int SSisDirAbsPilaValida ( SSistema * p_sisObj, long lDir );

long SSisMemoriaTotal ( SSistema * p_sisObj );
long SSisMemoriaUtilizada ( SSistema * p_sisObj );
long SSisMemoriaDisponible ( SSistema * p_sisObj );
long SSisMemoriaDatosTotal ( SSistema * p_sisObj );
long SSisMemoriaDatosUtilizada ( SSistema * p_sisObj );
long SSisMemoriaDatosDisponible ( SSistema * p_sisObj );
long SSisMemoriaPilaTotal ( SSistema * p_sisObj );
long SSisMemoriaPilaUtilizada ( SSistema * p_sisObj );
long SSisMemoriaPilaDisponible ( SSistema * p_sisObj );
long SSisMemoriaBloqueadaTotal ( SSistema * p_sisObj );
long SSisMemoriaBloqueadaUtilizada ( SSistema * p_sisObj );
long SSisMemoriaBloqueadaDisponible ( SSistema * p_sisObj );
long SSisMemoriaFisica ( SSistema * p_sisObj );

long SSisDescriptoresESTotales ( SSistema * p_sisObj );
long SSisDescriptoresESUtilizados ( SSistema * p_sisObj );
long SSisDescriptoresESDisponibles ( SSistema * p_sisObj );

long SSisMaxTamFichero ( SSistema * p_sisObj );
long SSisMaxTiempoCPU ( SSistema * p_sisObj );

long MSSisaxNumProcesosPorUsuario ( SSistema * p_sisObj );
*/





#endif
