#ifndef _ORG_GJS_C_CC_SENTRADADIRECTORIO_H
#define _ORG_GJS_C_CC_SENTRADADIRECTORIO_H


#include <SCadena.h>




typedef struct     
{
	SCadena *		p_cadEntrada;
	int				iDirectorio;
	
} SEntradaDirectorio;


SEntradaDirectorio * SEntDirCrearFichero ( SCadena * p_cadEntrada );
SEntradaDirectorio * SEntDirCrearFicheroLit ( const char * p_cEntrada );
SEntradaDirectorio * SEntDirCrearDirectorio ( SCadena * p_cadEntrada );
SEntradaDirectorio * SEntDirCrearDirectorioLit ( const char * p_cEntrada );

void SEntDirDestruir ( SEntradaDirectorio ** p_p_entdirObj );

SCadena * SEntDirEntrada ( SEntradaDirectorio * p_entdirObj );
const char * SEntDirEntradaLit ( SEntradaDirectorio * p_entdirObj );

int SEntDirEsValida ( SEntradaDirectorio * p_entdirObj );
int SEntDirEsDirectorio ( SEntradaDirectorio * p_entdirObj );
int SEntDirEsFichero ( SEntradaDirectorio * p_entdirObj );



#endif

