/******************************************************************************/
/*                                Funciones.h                                 */
/*----------------------------------------------------------------------------*/
/* Librería:  GBase                                                           */
/* Versión:   1.0.0                                                           */
/* Fecha:     28/06/2008                                                      */
/* Autor:     Ginés Jiménez Sánchez                                           */
/*----------------------------------------------------------------------------*/
/* Descripción:                                                               */
/* Fichero de cabecera que contiene los tipos necesarios para manejar los     */
/* punteros a procedimeitnos y funciones.                                     */
/*----------------------------------------------------------------------------*/
/*                        gines_jimenez@safe-mail.net                         */
/******************************************************************************/

#ifndef _FUNCIONES_H
#define _FUNCIONES_H


/* HANDLE, HWND y DWORD de los punteros a funcion de la rama WIN salen de
   windows.h, que entra por BaseConfig.h. El espejo de C++ ya lo incluia. */
#include <BaseConfig.h>
#include <UniChar.h>


//  V = void
//  I = int
//  L = long
//  S = short
// LL = long long
//  UI = unsigned int
//  UL = unsigned long
//  US = unsigned short
// ULL = unsigned long long
// F = float
// D = double
// LD = long double
// C = char
// PC = char * X
// T = const char * X
// 
// P[X] = * X
// PP[X] = ** X

// NOTA: Ir añadiendio conforme se vayan necesitando:

typedef void (* PPRCV)(void);
typedef void (* PPRCI)(int);
typedef void (* PPRCL)(long);
typedef void (* PPRCS)(short);
typedef void (* PPRCUI)(unsigned int);
typedef void (* PPRCUL)(unsigned long);
typedef void (* PPRCUS)(unsigned short);
typedef void (* PPRCF)(float);
typedef void (* PPRCD)(double);
typedef void (* PPRCC)(char);
typedef void (* PPRCPC)(char *);
typedef void (* PPRCT)(const char *);

typedef void (* PPRCPV)(void *);
typedef void (* PPRCPPV)(void **);

typedef void (* PPRCLL)(long long);
typedef void (* PPRCULL)(unsigned long long);

typedef int (* PFUNINTV)(void);
typedef int (* PFUNINTI)(int);
typedef int (* PFUNINTL)(long);
typedef int (* PFUNINTS)(short);
typedef int (* PFUNINTF)(float);
typedef int (* PFUNINTD)(double);
typedef int (* PFUNINTC)(char);
typedef int (* PFUNINTUI)(unsigned int);
typedef int (* PFUNINTUL)(unsigned long);
typedef int (* PFUNINTUS)(unsigned short);
typedef int (* PFUNINTPC)(char *);
typedef int (* PFUNINTT)(const char *);

typedef int (* PFUNINTPV)(void *);
typedef int (* PFUNINTPPV)(void **);

typedef int (* PFUNINTLL)(long long);
typedef int (* PFUNINTULL)(unsigned long long);

typedef int (* PFUNINTII)(int,int);
typedef int (* PFUNINTIII)(int,int,int);
typedef int (* PFUNINTIIII)(int,int,int,int);
typedef int (* PFUNINTIIIII)(int,int,int,int,int);
typedef int (* PFUNINTIIIIII)(int,int,int,int,int,int);

typedef int (* PFUNINTPVPV)(void *,void *);



typedef long (* PFUNLONGV)(void);
typedef long (* PFUNLONGI)(int);
typedef long (* PFUNLONGL)(long);
typedef long (* PFUNLONGS)(short);
typedef long (* PFUNLONGF)(float);
typedef long (* PFUNLONGD)(double);
typedef long (* PFUNLONGC)(char);
typedef long (* PFUNLONGUI)(unsigned int);
typedef long (* PFUNLONGUL)(unsigned long);
typedef long (* PFUNLONGUS)(unsigned short);
typedef long (* PFUNLONGPC)(char *);
typedef long (* PFUNLONGT)(const char *);

typedef long (* PFUNLONGPV)(void *);
typedef long (* PFUNLONGPPV)(void **);

typedef long (* PFUNLONGLL)(long long);
typedef long (* PFUNLONGULL)(unsigned long long);


typedef unsigned int (* PFUNUINTV)(void);
typedef unsigned int (* PFUNUINTI)(int);
typedef unsigned int (* PFUNUINTL)(long);
typedef unsigned int (* PFUNUINTS)(short);
typedef unsigned int (* PFUNUINTF)(float);
typedef unsigned int (* PFUNUINTD)(double);
typedef unsigned int (* PFUNUINTC)(char);
typedef unsigned int (* PFUNUINTUI)(unsigned int);
typedef unsigned int (* PFUNUINTUL)(unsigned long);
typedef unsigned int (* PFUNUINTUS)(unsigned short);
typedef unsigned int (* PFUNUINTPC)(char *);
typedef unsigned int (* PFUNUINTT)(const char *);

typedef unsigned int (* PFUNUINTPV)(void *);
typedef unsigned int (* PFUNUINTPPV)(void **);

typedef unsigned int (* PFUNUINTLL)(long long);
typedef unsigned int (* PFUNUINTULL)(unsigned long long);


typedef unsigned long (* PFUNULONGV)(void);
typedef unsigned long (* PFUNULONGI)(int);
typedef unsigned long (* PFUNULONGL)(long);
typedef unsigned long (* PFUNULONGS)(short);
typedef unsigned long (* PFUNULONGF)(float);
typedef unsigned long (* PFUNULONGD)(double);
typedef unsigned long (* PFUNULONGC)(char);
typedef unsigned long (* PFUNULONGUI)(unsigned int);
typedef unsigned long (* PFUNULONGUL)(unsigned long);
typedef unsigned long (* PFUNULONGUS)(unsigned short);
typedef unsigned long (* PFUNULONGPC)(char *);
typedef unsigned long (* PFUNULONGT)(const char *);

typedef unsigned long (* PFUNULONGPV)(void *);
typedef unsigned long (* PFUNULONGPPV)(void **);

typedef unsigned long (* PFUNULONGLL)(long long);
typedef unsigned long (* PFUNULONGULL)(unsigned long long);


typedef char (* PFUNCHARV)(void);
typedef char (* PFUNCHARI)(char);
typedef char (* PFUNCHARL)(long);
typedef char (* PFUNCHARS)(short);
typedef char (* PFUNCHARF)(float);
typedef char (* PFUNCHARD)(double);
typedef char (* PFUNCHARC)(char);
typedef char (* PFUNCHARUI)(unsigned int);
typedef char (* PFUNCHARUL)(unsigned long);
typedef char (* PFUNCHARUS)(unsigned short);
typedef char (* PFUNCHARPC)(char *);
typedef char (* PFUNCHART)(const char *);

typedef char (* PFUNCHARPV)(void *);
typedef char (* PFUNCHARPPV)(void **);

#if ( defined ( LCHAR ) )	
typedef char (* PFUNCHARLL)(char char);
typedef char (* PFUNCHARULL)(unsigned char char);
#endif

typedef char (* PFUNCHARTI)(const char *, int );
typedef char (* PFUNCHARTPI)(const char *, int * );

typedef char * (* PFUNPCHARS)(short);
typedef char * (* PFUNPCHARF)(float);
typedef char * (* PFUNPCHARD)(double);
typedef char * (* PFUNPCHARC)(char);
typedef char * (* PFUNPCHARUI)(unsigned int);
typedef char * (* PFUNPCHARUL)(unsigned long);
typedef char * (* PFUNPCHARUS)(unsigned short);
typedef char * (* PFUNPCHARPC)(char *);
typedef char * (* PFUNPCHART)(const char *);

typedef char * (* PFUNPCHARPV)(void *);
typedef char * (* PFUNPCHARPPV)(void **);

#if ( defined ( LPCHAR ) )	
typedef char * (* PFUNPCHARLL)(char char);
typedef char * (* PFUNPCHARULL)(unsigned char char);
#endif

typedef char * (* PFUNPCHARTI)(const char *, int );
typedef char * (* PFUNPCHARTPI)(const char *, int * );


typedef const char * (* PFUNLITV)(void);
typedef const char * (* PFUNLITI)(char);
typedef const char * (* PFUNLITL)(long);
typedef const char * (* PFUNLITS)(short);
typedef const char * (* PFUNLITF)(float);
typedef const char * (* PFUNLITD)(double);
typedef const char * (* PFUNLITC)(char);
typedef const char * (* PFUNLITUI)(unsigned int);
typedef const char * (* PFUNLITUL)(unsigned long);
typedef const char * (* PFUNLITUS)(unsigned short);
typedef const char * (* PFUNLITPC)(char *);
typedef const char * (* PFUNLITT)(const char *);

typedef const char * (* PFUNLITPV)(void *);
typedef const char * (* PFUNLITPPV)(void **);

#if ( defined ( LLIT ) )	
typedef const char * (* PFUNLITLL)(char char);
typedef const char * (* PFUNLITULL)(unsigned char char);
#endif

typedef const char * (* PFUNLITTI)(const char *, int );
typedef const char * (* PFUNLITTPI)(const char *, int * );

typedef float (* PFUNFLTV)(void);
typedef float (* PFUNFLTI)(int);
typedef float (* PFUNFLTL)(long);
typedef float (* PFUNFLTS)(short);
typedef float (* PFUNFLTF)(float);
typedef float (* PFUNFLTD)(double);
typedef float (* PFUNFLTC)(char);
typedef float (* PFUNFLTUI)(unsigned int);
typedef float (* PFUNFLTUL)(unsigned long);
typedef float (* PFUNFLTUS)(unsigned short);
typedef float (* PFUNFLTPC)(char *);
typedef float (* PFUNFLTT)(const char *);

typedef float (* PFUNFLTPV)(void *);
typedef float (* PFUNFLTPPV)(void **);

#if ( defined ( LFLT ) )	
typedef float (* PFUNFLTLL)(char char);
typedef float (* PFUNFLTULL)(unsigned char char);
#endif


typedef double (* PFUNDBLV)(void);
typedef double (* PFUNDBLI)(char);
typedef double (* PFUNDBLL)(long);
typedef double (* PFUNDBLS)(short);
typedef double (* PFUNDBLF)(float);
typedef double (* PFUNDBLD)(double);
typedef double (* PFUNDBLC)(char);
typedef double (* PFUNDBLUI)(unsigned int);
typedef double (* PFUNDBLUL)(unsigned long);
typedef double (* PFUNDBLUS)(unsigned short);
typedef double (* PFUNDBLPC)(char *);
typedef double (* PFUNDBLT)(const char *);

typedef double (* PFUNDBLPV)(void *);
typedef double (* PFUNDBLPPV)(void **);

#if ( defined ( LDBL ) )	
typedef double (* PFUNDBLLL)(char char);
typedef double (* PFUNDBLULL)(unsigned char char);
#endif


typedef void * (* PFUNPVOIDV)(void); 
typedef void * (* PFUNPVOIDI)(int);
typedef void * (* PFUNPVOIDL)(long);
typedef void * (* PFUNPVOIDS)(short);
typedef void * (* PFUNPVOIDUI)(unsigned int);
typedef void * (* PFUNPVOIDUL)(unsigned long);
typedef void * (* PFUNPVOIDUS)(unsigned short);
typedef void * (* PFUNPVOIDF)(float);
typedef void * (* PFUNPVOIDD)(double);
typedef void * (* PFUNPVOIDC)(char);
typedef void * (* PFUNPVOIDPC)(char *);
typedef void * (* PFUNPVOIDT)(const char *);

typedef void * (* PFUNPVOIDPV)(void *);
typedef void * (* PFUNPVOIDPPV)(void **);

typedef void * (* PFUNPVOIDLL)(long long);
typedef void * (* PFUNPVOIDULL)(unsigned long long);

typedef void * (* PFUNPVOIDULIUL)(unsigned long, int, unsigned long); 


#if ( defined ( WIN ) )

typedef HANDLE (* PFUNHNDDWBDW)(DWORD, BOOL, DWORD);
typedef int (* PFUNINTHWN)(HWND);

#endif


/* Tipo de datos especiales para los casos más sencillos: */ 
typedef int (*PTR_FUNCION)();
typedef void (*PTR_PROCEDIMIENTO)();




#endif







