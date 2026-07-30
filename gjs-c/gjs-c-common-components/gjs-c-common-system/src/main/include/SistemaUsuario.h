
#ifndef _ORG_GJS_C_CC_SISTEMA_USUARIO_H
#define _ORG_GJS_C_CC_SISTEMA_USUARIO_H




unsigned int SisUsrObtenerUsuario ( int type );
unsigned int SisUsrObtenerGrupo ( int type );
char * SisUsrObtenerNombre ( unsigned int uiId );
char * SisUsrObtenerNombreGrupo ( unsigned int uiIdGrupo ) ;
int   SisUsrDesactivarRoot ();
int   SisUsrActivarRoot ();
int   SisUsrDesactivarGrupoRoot  ();
int   SisUsrActivarGrupoRoot ();
int   SisUsrEstablecerUsuario ( const char * p_cUsuario, const char * p_cGrupo );
char * SisUsrObtenerUsuarioLogin ();





#endif
