#ifndef _ORG_GJS_C_CC_REGISTRO_CONSTANTES_H
#define _ORG_GJS_C_CC_REGISTRO_CONSTANTES_H





#define REG_CLV_CLASSES_ROOT				0
#define REG_CLV_CURRENT_CONFIG				1
#define REG_CLV_CURRENT_USER				2
#define REG_CLV_LOCAL_MACHINE				3
#define REG_CLV_USERS						4



/* Formatos de */
#define REG_VERSION_FORMATO		"%d.%d"
#define REG_PROG_ID_FORMATO		"%s.%s"
#define REG_PROG_ID_ACT_FORMATO	"%s.%s.%d"
		


/* Secciones de HKEY_CLASSES_ROOT: */
#define REG_SEC_LIBRERIAS		"TypeLib"
#define REG_SEC_CLASES			"CLSID"

/* Claves de la definición de módulo: */
#define REG_CLV_LIB_FICHERO		"Win32"
#define REG_CLV_LIB_ATRIBUTOS	"Flags"
#define REG_CLV_LIB_FIC_AYUDA	"HelpDir"
 

/* Claves de la definición clases/interfases por GUID: */
#define REG_CLV_CLS_CAT_IMP		"ImplementedCategories"
#define REG_CLV_CLS_SERVIDOR	"InprocServer32"
#define REG_CLV_CLS_PROG_ID		"ProgId"
#define REG_CLV_CLS_LIBRERIA	"TypeLib"
#define REG_CLV_CLS_VERSION		"Version"
#define REG_CLV_CLS_MOD_HEBRAS	"ThreadingModel"
#define REG_CLV_CLS_IND_PROG_ID	"VersionIndependentProgId"


/* Claves de la definición clases/interfases por PROGID: */
#define REG_CLV_CLS_ID			"CLSID"
#define REG_CLV_VERSION_ACT		"CURVER"


/* Valores por defecto: */
#define REG_LIB_REVISION_DEF		"0"
#define REG_CLS_VERSION_DEF			 1
#define REG_VAL_NUM_DEF				"0"
#define REG_VAL_DEF					""


/* Valores máximos para las variables auxiliares: */
#define REG_MAX_TAM_GUID		38
#define REG_MAX_TAM_CLAVE		63
#define REG_MAX_TAM_VALOR		1023


/* Número máximo de niveles jerárquicos: */
#define REG_MAX_NIVELES			10



#endif 